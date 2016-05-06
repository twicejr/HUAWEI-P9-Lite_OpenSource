/******************************************************************************

                 版权所有 (C), 2001-2015, 华为技术有限公司

 ******************************************************************************
  文 件 名   : soc_mmbuf_interface.h
  版 本 号   : 初稿
  作    者   : Excel2Code
  生成日期   : 2015-03-10 11:22:18
  最近修改   :
  功能描述   : 接口头文件
  函数列表   :
  修改历史   :
  1.日    期   : 2015年3月10日
    作    者   : fWX220878
    修改内容   : 从《Hi3650V100 SOC寄存器手册_MMBUF.xml》自动生成

******************************************************************************/

/*****************************************************************************
  1 其他头文件包含
*****************************************************************************/

#ifndef __SOC_MMBUF_INTERFACE_H__
#define __SOC_MMBUF_INTERFACE_H__

#ifdef __cplusplus
    #if __cplusplus
        extern "C" {
    #endif
#endif



/*****************************************************************************
  2 宏定义
*****************************************************************************/

/****************************************************************************
                     (1/1) reg_define
 ****************************************************************************/
/* 寄存器说明：SMC Lock寄存器。
   位域定义UNION结构:  SOC_MMBUF_SMC_LOCK_UNION */
#define SOC_MMBUF_SMC_LOCK_ADDR(base)                 ((base) + (0x0000))

/* 寄存器说明：SRAM低功耗light sleep时序控制寄存器。
   位域定义UNION结构:  SOC_MMBUF_SMC_MEM_LP_UNION */
#define SOC_MMBUF_SMC_MEM_LP_ADDR(base)               ((base) + (0x0004))

/* 寄存器说明：AXI slave 口clock gate设置。
   位域定义UNION结构:  SOC_MMBUF_GCLK_CS_UNION */
#define SOC_MMBUF_GCLK_CS_ADDR(base)                  ((base) + (0x000C))

/* 寄存器说明：Slave口QOS后门修改寄存器。
   位域定义UNION结构:  SOC_MMBUF_SMC_QOS_BACKDOOR_UNION */
#define SOC_MMBUF_SMC_QOS_BACKDOOR_ADDR(base)         ((base) + (0x0010))

/* 寄存器说明：还剩余的未完成的AXI命令数，单位为AXI命令。
   位域定义UNION结构:  SOC_MMBUF_SMC_DFX_WCMD_CNT_1ST_UNION */
#define SOC_MMBUF_SMC_DFX_WCMD_CNT_1ST_ADDR(base)     ((base) + (0x0014))

/* 寄存器说明：还剩余的未完成的AXI命令数，单位为AXI命令。
   位域定义UNION结构:  SOC_MMBUF_SMC_DFX_WCMD_CNT_2ND_UNION */
#define SOC_MMBUF_SMC_DFX_WCMD_CNT_2ND_ADDR(base)     ((base) + (0x0018))

/* 寄存器说明：还剩余的未完成的AXI命令数，单位为AXI命令。
   位域定义UNION结构:  SOC_MMBUF_SMC_DFX_WCMD_CNT_3RD_UNION */
#define SOC_MMBUF_SMC_DFX_WCMD_CNT_3RD_ADDR(base)     ((base) + (0x001C))

/* 寄存器说明：还剩余的未完成的AXI命令数，单位为AXI命令。
   位域定义UNION结构:  SOC_MMBUF_SMC_DFX_WCMD_CNT_4TH_UNION */
#define SOC_MMBUF_SMC_DFX_WCMD_CNT_4TH_ADDR(base)     ((base) + (0x0020))

/* 寄存器说明：还剩余的未完成的AXI命令数，单位为AXI命令。
   位域定义UNION结构:  SOC_MMBUF_SMC_DFX_RCMD_CNT_1ST_UNION */
#define SOC_MMBUF_SMC_DFX_RCMD_CNT_1ST_ADDR(base)     ((base) + (0x0024))

/* 寄存器说明：还剩余的未完成的AXI命令数，单位为AXI命令。
   位域定义UNION结构:  SOC_MMBUF_SMC_DFX_RCMD_CNT_2ND_UNION */
#define SOC_MMBUF_SMC_DFX_RCMD_CNT_2ND_ADDR(base)     ((base) + (0x0028))

/* 寄存器说明：还剩余的未完成的AXI命令数，单位为AXI命令。
   位域定义UNION结构:  SOC_MMBUF_SMC_DFX_RCMD_CNT_3RD_UNION */
#define SOC_MMBUF_SMC_DFX_RCMD_CNT_3RD_ADDR(base)     ((base) + (0x002C))

/* 寄存器说明：还剩余的未完成的AXI命令数，单位为AXI命令。
   位域定义UNION结构:  SOC_MMBUF_SMC_DFX_RCMD_CNT_4TH_UNION */
#define SOC_MMBUF_SMC_DFX_RCMD_CNT_4TH_ADDR(base)     ((base) + (0x0030))

/* 寄存器说明：AXI slave口的状态。
   位域定义UNION结构:  SOC_MMBUF_SMC_CS_IDLE_UNION */
#define SOC_MMBUF_SMC_CS_IDLE_ADDR(base)              ((base) + (0x0034))

/* 寄存器说明：AXI slave口中写响应FIFO中存储的AXI写响应命令个数。
   位域定义UNION结构:  SOC_MMBUF_SMC_DFX_BFIFO_CNT0_UNION */
#define SOC_MMBUF_SMC_DFX_BFIFO_CNT0_ADDR(base)       ((base) + (0x0038))

/* 寄存器说明：AXI slave口中读数据FIFO中存储的AXI读数据个数。
   位域定义UNION结构:  SOC_MMBUF_SMC_DFX_RDFIFO_CNT1_UNION */
#define SOC_MMBUF_SMC_DFX_RDFIFO_CNT1_ADDR(base)      ((base) + (0x003C))

/* 寄存器说明：交织bank的sram memory的状态。
   位域定义UNION结构:  SOC_MMBUF_SP_SRAM_STATE0_UNION */
#define SOC_MMBUF_SP_SRAM_STATE0_ADDR(base)           ((base) + (0x0040))

/* 寄存器说明：交织bank的sram memory的状态。
   位域定义UNION结构:  SOC_MMBUF_SP_SRAM_STATE1_UNION */
#define SOC_MMBUF_SP_SRAM_STATE1_ADDR(base)           ((base) + (0x0044))





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
                     (1/1) reg_define
 ****************************************************************************/
/*****************************************************************************
 结构名    : SOC_MMBUF_SMC_LOCK_UNION
 结构说明  : SMC_LOCK 寄存器结构定义。地址偏移量:0x0000，初值:0x00000000，宽度:32
 寄存器说明: SMC Lock寄存器。
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  smc_lock : 32; /* bit[0-31]: 写lock寄存器：
                                                   向Lock寄存器写32bits密钥（密钥为0x5A5A_5A5A），解锁寄存器，表示所有寄存器可写；向Lock寄存器写其他任意值，锁定寄存器，Lock保护范围内的寄存器不能写，Lock保护范围外的寄存器可以写；
                                                   读任何寄存器不受Lock寄存器的影响，任何时刻都可以读。
                                                   读lock寄存器（Lock寄存器读出值表示寄存器的锁定状态）：
                                                   0x0000_0000表示寄存器处于解锁状态;
                                                   0x0000_0001表示寄存器处于锁定状态。
                                                   Lock寄存器锁定范围请见每个寄存器的描述 */
    } reg;
} SOC_MMBUF_SMC_LOCK_UNION;
#endif
#define SOC_MMBUF_SMC_LOCK_smc_lock_START  (0)
#define SOC_MMBUF_SMC_LOCK_smc_lock_END    (31)


/*****************************************************************************
 结构名    : SOC_MMBUF_SMC_MEM_LP_UNION
 结构说明  : SMC_MEM_LP 寄存器结构定义。地址偏移量:0x0004，初值:0x00000000，宽度:32
 寄存器说明: SRAM低功耗light sleep时序控制寄存器。
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  smc_ls_en      : 1;  /* bit[0]    : SMC SRAM Light Sleep功能块使能
                                                          1'b0: SMC硬件LS功能关闭，在任何状态下，SRAM都不会进入LS模式
                                                          1'b1: SMC硬件自动进入LS模式功能开启
                                                          注意1：该寄存器受写锁lock保护。
                                                          注意2：若smc_ls_en和smc_ds_en同时有效，则smc_ls_en有效。
                                                          注意3：在 light sleep 向 deep sleep 切换过程中，有如下流程约束（以 light sleep 切换到 deep sleep 为例）：
                                                          （1）、配置寄存器到 light sleep 和 deep sleep 都不使能的状态（即配置 smc_ls_en = 0）；
                                                          （2）、检查所有的 memory 都处于 normal 态（即全部退出了 light sleep）；
                                                          （3）、寄存器配置低功耗模式到 deep sleep或者 light sleep（即配置 smc_ds_en = 1） */
        unsigned int  smc_ds_en      : 1;  /* bit[1]    : SMC SRAM Light Sleep功能块使能
                                                          1'b0: SMC硬件LS功能关闭，在任何状态下，SRAM都不会进入LS模式
                                                          1'b1: SMC硬件自动进入LS模式功能开启
                                                          注意1：该寄存器受写锁lock保护。
                                                          注意2：若smc_ls_en和smc_ds_en同时有效，则smc_ls_en有效。
                                                          注意3：在 light sleep 向 deep sleep 切换过程中，有如下流程约束（以 light sleep 切换到 deep sleep 为例）：
                                                          （1）、配置寄存器到 light sleep 和 deep sleep 都不使能的状态（即配置 smc_ls_en = 0）；
                                                          （2）、检查所有的 memory 都处于 normal 态（即全部退出了 light sleep）；
                                                          （3）、寄存器配置低功耗模式到 deep sleep或者 light sleep（即配置 smc_ds_en = 1） */
        unsigned int  reserved_0     : 2;  /* bit[2-3]  : Reserved. */
        unsigned int  lp_exit_cycle  : 4;  /* bit[4-7]  : memory从retention状态唤醒需要的时间，单位为AXI总线cycle。
                                                          此值的设定需要查看对应memory原型的light sleep参数，模块要求此值大于等于1。
                                                          注1：该寄存器受写锁lock保护。
                                                          注2：实际有效的值是此设定值加1，如：设定为2，实际模块表示3个时钟。
                                                          注3：当smc_ls_en有效时，此值为light sleep退出时间；当smc_ds_en有效时，此值为deep sleep退出时间。 */
        unsigned int  lp_enter_cycle : 16; /* bit[8-23] : 模块空闲后，等待进入retention的时间，即空闲日后在改时间内继续空闲，则memory进入retention状态，单位为AXI总线cycle。
                                                          此值的设定需要查看对应memory原型的light sleep参数，模块要求此值大于等于配置的 lp_exit_cycle 加6。
                                                          注1：该寄存器受写锁lock保护。
                                                          注2：实际有效的值是此设定值加1，如：设定为2，实际模块表示3个时钟。
                                                          注3：当smc_ls_en有效时，此值为light sleep进入时间；当smc_ds_en有效时，此值为deep sleep进入时间。 */
        unsigned int  reserved_1     : 8;  /* bit[24-31]: Reserved. */
    } reg;
} SOC_MMBUF_SMC_MEM_LP_UNION;
#endif
#define SOC_MMBUF_SMC_MEM_LP_smc_ls_en_START       (0)
#define SOC_MMBUF_SMC_MEM_LP_smc_ls_en_END         (0)
#define SOC_MMBUF_SMC_MEM_LP_smc_ds_en_START       (1)
#define SOC_MMBUF_SMC_MEM_LP_smc_ds_en_END         (1)
#define SOC_MMBUF_SMC_MEM_LP_lp_exit_cycle_START   (4)
#define SOC_MMBUF_SMC_MEM_LP_lp_exit_cycle_END     (7)
#define SOC_MMBUF_SMC_MEM_LP_lp_enter_cycle_START  (8)
#define SOC_MMBUF_SMC_MEM_LP_lp_enter_cycle_END    (23)


/*****************************************************************************
 结构名    : SOC_MMBUF_GCLK_CS_UNION
 结构说明  : GCLK_CS 寄存器结构定义。地址偏移量:0x000C，初值:0x0000，宽度:32
 寄存器说明: AXI slave 口clock gate设置。
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  axi_s0_clock_disable  : 1;  /* bit[0]    : 软件控制对应AXI slave口的时钟gate
                                                                 1'b0: 该AXI slave口的时钟为freerun
                                                                 1'b1: 该AXI slave口的时钟关闭，此时需要软件保证该端口的数据访问完成且无新的数据访问 */
        unsigned int  axi_s1_clock_disable  : 1;  /* bit[1]    : 软件控制对应AXI slave口的时钟gate
                                                                 1'b0: 该AXI slave口的时钟为freerun
                                                                 1'b1: 该AXI slave口的时钟关闭，此时需要软件保证该端口的数据访问完成且无新的数据访问 */
        unsigned int  axi_s2_clock_disable  : 1;  /* bit[2]    : 软件控制对应AXI slave口的时钟gate
                                                                 1'b0: 该AXI slave口的时钟为freerun
                                                                 1'b1: 该AXI slave口的时钟关闭，此时需要软件保证该端口的数据访问完成且无新的数据访问 */
        unsigned int  axi_s3_clock_disable  : 1;  /* bit[3]    : 软件控制对应AXI slave口的时钟gate
                                                                 1'b0: 该AXI slave口的时钟为freerun
                                                                 1'b1: 该AXI slave口的时钟关闭，此时需要软件保证该端口的数据访问完成且无新的数据访问 */
        unsigned int  axi_s4_clock_disable  : 1;  /* bit[4]    : 软件控制对应AXI slave口的时钟gate
                                                                 1'b0: 该AXI slave口的时钟为freerun
                                                                 1'b1: 该AXI slave口的时钟关闭，此时需要软件保证该端口的数据访问完成且无新的数据访问 */
        unsigned int  axi_s5_clock_disable  : 1;  /* bit[5]    : 软件控制对应AXI slave口的时钟gate
                                                                 1'b0: 该AXI slave口的时钟为freerun
                                                                 1'b1: 该AXI slave口的时钟关闭，此时需要软件保证该端口的数据访问完成且无新的数据访问 */
        unsigned int  axi_s6_clock_disable  : 1;  /* bit[6]    : 软件控制对应AXI slave口的时钟gate
                                                                 1'b0: 该AXI slave口的时钟为freerun
                                                                 1'b1: 该AXI slave口的时钟关闭，此时需要软件保证该端口的数据访问完成且无新的数据访问 */
        unsigned int  axi_s7_clock_disable  : 1;  /* bit[7]    : 软件控制对应AXI slave口的时钟gate
                                                                 1'b0: 该AXI slave口的时钟为freerun
                                                                 1'b1: 该AXI slave口的时钟关闭，此时需要软件保证该端口的数据访问完成且无新的数据访问 */
        unsigned int  axi_s8_clock_disable  : 1;  /* bit[8]    : 软件控制对应AXI slave口的时钟gate
                                                                 1'b0: 该AXI slave口的时钟为freerun
                                                                 1'b1: 该AXI slave口的时钟关闭，此时需要软件保证该端口的数据访问完成且无新的数据访问 */
        unsigned int  axi_s9_clock_disable  : 1;  /* bit[9]    : 软件控制对应AXI slave口的时钟gate
                                                                 1'b0: 该AXI slave口的时钟为freerun
                                                                 1'b1: 该AXI slave口的时钟关闭，此时需要软件保证该端口的数据访问完成且无新的数据访问 */
        unsigned int  axi_s10_clock_disable : 1;  /* bit[10]   : 软件控制对应AXI slave口的时钟gate
                                                                 1'b0: 该AXI slave口的时钟为freerun
                                                                 1'b1: 该AXI slave口的时钟关闭，此时需要软件保证该端口的数据访问完成且无新的数据访问 */
        unsigned int  axi_s11_clock_disable : 1;  /* bit[11]   : 软件控制对应AXI slave口的时钟gate
                                                                 1'b0: 该AXI slave口的时钟为freerun
                                                                 1'b1: 该AXI slave口的时钟关闭，此时需要软件保证该端口的数据访问完成且无新的数据访问 */
        unsigned int  axi_s12_clock_disable : 1;  /* bit[12]   : 软件控制对应AXI slave口的时钟gate
                                                                 1'b0: 该AXI slave口的时钟为freerun
                                                                 1'b1: 该AXI slave口的时钟关闭，此时需要软件保证该端口的数据访问完成且无新的数据访问 */
        unsigned int  axi_s13_clock_disable : 1;  /* bit[13]   : 软件控制对应AXI slave口的时钟gate
                                                                 1'b0: 该AXI slave口的时钟为freerun
                                                                 1'b1: 该AXI slave口的时钟关闭，此时需要软件保证该端口的数据访问完成且无新的数据访问 */
        unsigned int  axi_s14_clock_disable : 1;  /* bit[14]   : 软件控制对应AXI slave口的时钟gate
                                                                 1'b0: 该AXI slave口的时钟为freerun
                                                                 1'b1: 该AXI slave口的时钟关闭，此时需要软件保证该端口的数据访问完成且无新的数据访问 */
        unsigned int  axi_s15_clock_disable : 1;  /* bit[15]   : 软件控制对应AXI slave口的时钟gate
                                                                 1'b0: 该AXI slave口的时钟为freerun
                                                                 1'b1: 该AXI slave口的时钟关闭，此时需要软件保证该端口的数据访问完成且无新的数据访问 */
        unsigned int  reserved              : 16; /* bit[16-31]:  */
    } reg;
} SOC_MMBUF_GCLK_CS_UNION;
#endif
#define SOC_MMBUF_GCLK_CS_axi_s0_clock_disable_START   (0)
#define SOC_MMBUF_GCLK_CS_axi_s0_clock_disable_END     (0)
#define SOC_MMBUF_GCLK_CS_axi_s1_clock_disable_START   (1)
#define SOC_MMBUF_GCLK_CS_axi_s1_clock_disable_END     (1)
#define SOC_MMBUF_GCLK_CS_axi_s2_clock_disable_START   (2)
#define SOC_MMBUF_GCLK_CS_axi_s2_clock_disable_END     (2)
#define SOC_MMBUF_GCLK_CS_axi_s3_clock_disable_START   (3)
#define SOC_MMBUF_GCLK_CS_axi_s3_clock_disable_END     (3)
#define SOC_MMBUF_GCLK_CS_axi_s4_clock_disable_START   (4)
#define SOC_MMBUF_GCLK_CS_axi_s4_clock_disable_END     (4)
#define SOC_MMBUF_GCLK_CS_axi_s5_clock_disable_START   (5)
#define SOC_MMBUF_GCLK_CS_axi_s5_clock_disable_END     (5)
#define SOC_MMBUF_GCLK_CS_axi_s6_clock_disable_START   (6)
#define SOC_MMBUF_GCLK_CS_axi_s6_clock_disable_END     (6)
#define SOC_MMBUF_GCLK_CS_axi_s7_clock_disable_START   (7)
#define SOC_MMBUF_GCLK_CS_axi_s7_clock_disable_END     (7)
#define SOC_MMBUF_GCLK_CS_axi_s8_clock_disable_START   (8)
#define SOC_MMBUF_GCLK_CS_axi_s8_clock_disable_END     (8)
#define SOC_MMBUF_GCLK_CS_axi_s9_clock_disable_START   (9)
#define SOC_MMBUF_GCLK_CS_axi_s9_clock_disable_END     (9)
#define SOC_MMBUF_GCLK_CS_axi_s10_clock_disable_START  (10)
#define SOC_MMBUF_GCLK_CS_axi_s10_clock_disable_END    (10)
#define SOC_MMBUF_GCLK_CS_axi_s11_clock_disable_START  (11)
#define SOC_MMBUF_GCLK_CS_axi_s11_clock_disable_END    (11)
#define SOC_MMBUF_GCLK_CS_axi_s12_clock_disable_START  (12)
#define SOC_MMBUF_GCLK_CS_axi_s12_clock_disable_END    (12)
#define SOC_MMBUF_GCLK_CS_axi_s13_clock_disable_START  (13)
#define SOC_MMBUF_GCLK_CS_axi_s13_clock_disable_END    (13)
#define SOC_MMBUF_GCLK_CS_axi_s14_clock_disable_START  (14)
#define SOC_MMBUF_GCLK_CS_axi_s14_clock_disable_END    (14)
#define SOC_MMBUF_GCLK_CS_axi_s15_clock_disable_START  (15)
#define SOC_MMBUF_GCLK_CS_axi_s15_clock_disable_END    (15)


/*****************************************************************************
 结构名    : SOC_MMBUF_SMC_QOS_BACKDOOR_UNION
 结构说明  : SMC_QOS_BACKDOOR 寄存器结构定义。地址偏移量:0x0010，初值:0x00000000，宽度:32
 寄存器说明: Slave口QOS后门修改寄存器。
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  s0_qos_modify_en     : 1;  /* bit[0] : slave 0 口 QOS 修改使能：
                                                             1'b0: QOS不做任何更改
                                                             1'b1: 更改此slave口的QOS，QOS值由bit[1]的设定
                                                             注意：该寄存器受写锁lock保护。 */
        unsigned int  s0_qos_modify_value  : 1;  /* bit[1] : Slave 0 口QOS设定修改后门
                                                             寄存器，该修改受使能控制：
                                                             1'b0: 当bit[0]=1时，此Slave口的QOS修改为2'b00(最低优先级)
                                                             1'b1: 当bit[0]=1时，此Slave口的QOS修改为2'b11(最高优先级)
                                                             注意：该寄存器受写锁lock保护。 */
        unsigned int  s1_qos_modify_en     : 1;  /* bit[2] : slave 1 口 QOS 修改使能：
                                                             1'b0: QOS不做任何更改
                                                             1'b1: 更改此slave口的QOS，QOS值由bit[3]的设定
                                                             注意：该寄存器受写锁lock保护。 */
        unsigned int  s1_qos_modify_value  : 1;  /* bit[3] : Slave 1 口QOS设定修改后门
                                                             寄存器，该修改受使能控制：
                                                             1'b0: 当bit[2]=1时，此Slave口的QOS修改为2'b00(最低优先级)
                                                             1'b1: 当bit[2]=1时，此Slave口的QOS修改为2'b11(最高优先级)
                                                             注意：该寄存器受写锁lock保护。 */
        unsigned int  s2_qos_modify_en     : 1;  /* bit[4] : slave 2 口 QOS 修改使能：
                                                             1'b0: QOS不做任何更改
                                                             1'b1: 更改此slave口的QOS，QOS值由bit[5]的设定
                                                             注意：该寄存器受写锁lock保护。 */
        unsigned int  s2_qos_modify_value  : 1;  /* bit[5] : Slave 2 口QOS设定修改后门
                                                             寄存器，该修改受使能控制：
                                                             1'b0: 当bit[4]=1时，此Slave口的QOS修改为2'b00(最低优先级)
                                                             1'b1: 当bit[4]=1时，此Slave口的QOS修改为2'b11(最高优先级)
                                                             注意：该寄存器受写锁lock保护。 */
        unsigned int  s3_qos_modify_en     : 1;  /* bit[6] : slave 3 口 QOS 修改使能：
                                                             1'b0: QOS不做任何更改
                                                             1'b1: 更改此slave口的QOS，QOS值由bit[7]的设定
                                                             注意：该寄存器受写锁lock保护。 */
        unsigned int  s3_qos_modify_value  : 1;  /* bit[7] : Slave 3 口QOS设定修改后门
                                                             寄存器，该修改受使能控制：
                                                             1'b0: 当bit[6]=1时，此Slave口的QOS修改为2'b00(最低优先级)
                                                             1'b1: 当bit[6]=1时，此Slave口的QOS修改为2'b11(最高优先级)
                                                             注意：该寄存器受写锁lock保护。 */
        unsigned int  s4_qos_modify_en     : 1;  /* bit[8] : slave 4 口 QOS 修改使能：
                                                             1'b0: QOS不做任何更改
                                                             1'b1: 更改此slave口的QOS，QOS值由bit[9]的设定
                                                             注意：该寄存器受写锁lock保护。 */
        unsigned int  s4_qos_modify_value  : 1;  /* bit[9] : Slave 4 口QOS设定修改后门
                                                             寄存器，该修改受使能控制：
                                                             1'b0: 当bit[8]=1时，此Slave口的QOS修改为2'b00(最低优先级)
                                                             1'b1: 当bit[8]=1时，此Slave口的QOS修改为2'b11(最高优先级)
                                                             注意：该寄存器受写锁lock保护。 */
        unsigned int  s5_qos_modify_en     : 1;  /* bit[10]: slave 5 口 QOS 修改使能：
                                                             1'b0: QOS不做任何更改
                                                             1'b1: 更改此slave口的QOS，QOS值由bit[11]的设定
                                                             注意：该寄存器受写锁lock保护。 */
        unsigned int  s5_qos_modify_value  : 1;  /* bit[11]: Slave 5 口QOS设定修改后门
                                                             寄存器，该修改受使能控制：
                                                             1'b0: 当bit[10]=1时，此Slave口的QOS修改为2'b00(最低优先级)
                                                             1'b1: 当bit[10]=1时，此Slave口的QOS修改为2'b11(最高优先级)
                                                             注意：该寄存器受写锁lock保护。 */
        unsigned int  s6_qos_modify_en     : 1;  /* bit[12]: slave 6 口 QOS 修改使能：
                                                             1'b0: QOS不做任何更改
                                                             1'b1: 更改此slave口的QOS，QOS值由bit[13]的设定
                                                             注意：该寄存器受写锁lock保护。 */
        unsigned int  s6_qos_modify_value  : 1;  /* bit[13]: Slave 6 口QOS设定修改后门
                                                             寄存器，该修改受使能控制：
                                                             1'b0: 当bit[12]=1时，此Slave口的QOS修改为2'b00(最低优先级)
                                                             1'b1: 当bit[12]=1时，此Slave口的QOS修改为2'b11(最高优先级)
                                                             注意：该寄存器受写锁lock保护。 */
        unsigned int  s7_qos_modify_en     : 1;  /* bit[14]: slave 7 口 QOS 修改使能：
                                                             1'b0: QOS不做任何更改
                                                             1'b1: 更改此slave口的QOS，QOS值由bit[15]的设定
                                                             注意：该寄存器受写锁lock保护。 */
        unsigned int  s7_qos_modify_value  : 1;  /* bit[15]: Slave 7 口QOS设定修改后门
                                                             寄存器，该修改受使能控制：
                                                             1'b0: 当bit[14]=1时，此Slave口的QOS修改为2'b00(最低优先级)
                                                             1'b1: 当bit[14]=1时，此Slave口的QOS修改为2'b11(最高优先级)
                                                             注意：该寄存器受写锁lock保护。 */
        unsigned int  s8_qos_modify_en     : 1;  /* bit[16]: slave 8 口 QOS 修改使能：
                                                             1'b0: QOS不做任何更改
                                                             1'b1: 更改此slave口的QOS，QOS值由bit[17]的设定
                                                             注意：该寄存器受写锁lock保护。 */
        unsigned int  s8_qos_modify_value  : 1;  /* bit[17]: Slave 8 口QOS设定修改后门
                                                             寄存器，该修改受使能控制：
                                                             1'b0: 当bit[16]=1时，此Slave口的QOS修改为2'b00(最低优先级)
                                                             1'b1: 当bit[16]=1时，此Slave口的QOS修改为2'b11(最高优先级)
                                                             注意：该寄存器受写锁lock保护。 */
        unsigned int  s9_qos_modify_en     : 1;  /* bit[18]: slave 9 口 QOS 修改使能：
                                                             1'b0: QOS不做任何更改
                                                             1'b1: 更改此slave口的QOS，QOS值由bit[19]的设定
                                                             注意：该寄存器受写锁lock保护。 */
        unsigned int  s9_qos_modify_value  : 1;  /* bit[19]: Slave 9 口QOS设定修改后门
                                                             寄存器，该修改受使能控制：
                                                             1'b0: 当bit[18]=1时，此Slave口的QOS修改为2'b00(最低优先级)
                                                             1'b1: 当bit[18]=1时，此Slave口的QOS修改为2'b11(最高优先级)
                                                             注意：该寄存器受写锁lock保护。 */
        unsigned int  s10_qos_modify_en    : 1;  /* bit[20]: slave 10 口 QOS 修改使能：
                                                             1'b0: QOS不做任何更改
                                                             1'b1: 更改此slave口的QOS，QOS值由bit[21]的设定 */
        unsigned int  s10_qos_modify_value : 1;  /* bit[21]: Slave 10 口QOS设定修改后门
                                                             寄存器，该修改受使能控制：
                                                             1'b0: 当bit[20]=1时，此Slave口的QOS修改为2'b00(最低优先级)
                                                             1'b1: 当bit20]=1时，此Slave口的QOS修改为2'b11(最高优先级)
                                                             注意：该寄存器受写锁lock保护。 */
        unsigned int  s11_qos_modify_en    : 1;  /* bit[22]: slave 11 口 QOS 修改使能：
                                                             1'b0: QOS不做任何更改
                                                             1'b1: 更改此slave口的QOS，QOS值由bit[23]的设定 */
        unsigned int  s11_qos_modify_value : 1;  /* bit[23]: Slave 11 口QOS设定修改后门
                                                             寄存器，该修改受使能控制：
                                                             1'b0: 当bit[22]=1时，此Slave口的QOS修改为2'b00(最低优先级)
                                                             1'b1: 当bit[22]=1时，此Slave口的QOS修改为2'b11(最高优先级)
                                                             注意：该寄存器受写锁lock保护。 */
        unsigned int  s12_qos_modify_en    : 1;  /* bit[24]: slave 15 口 QOS 修改使能：
                                                             1'b0: QOS不做任何更改
                                                             1'b1: 更改此slave口的QOS，QOS值由bit[25]的设定
                                                             注意：该寄存器受写锁lock保护。 */
        unsigned int  s12_qos_modify_value : 1;  /* bit[25]: Slave 12 口QOS设定修改后门
                                                             寄存器，该修改受使能控制：
                                                             1'b0: 当bit[24]=1时，此Slave口的QOS修改为2'b00(最低优先级)
                                                             1'b1: 当bit[24]=1时，此Slave口的QOS修改为2'b11(最高优先级)
                                                             注意：该寄存器受写锁lock保护。 */
        unsigned int  s13_qos_modify_en    : 1;  /* bit[26]: slave 13 口 QOS 修改使能：
                                                             1'b0: QOS不做任何更改
                                                             1'b1: 更改此slave口的QOS，QOS值由bit[27]的设定
                                                             注意：该寄存器受写锁lock保护。 */
        unsigned int  s13_qos_modify_value : 1;  /* bit[27]: Slave 13 口QOS设定修改后门
                                                             寄存器，该修改受使能控制：
                                                             1'b0: 当bit[26]=1时，此Slave口的QOS修改为2'b00(最低优先级)
                                                             1'b1: 当bit[26]=1时，此Slave口的QOS修改为2'b11(最高优先级)
                                                             注意：该寄存器受写锁lock保护。 */
        unsigned int  s14_qos_modify_en    : 1;  /* bit[28]: slave 14 口 QOS 修改使能：
                                                             1'b0: QOS不做任何更改
                                                             1'b1: 更改此slave口的QOS，QOS值由bit[29]的设定
                                                             注意：该寄存器受写锁lock保护。 */
        unsigned int  s14_qos_modify_value : 1;  /* bit[29]: Slave 14 口QOS设定修改后门
                                                             寄存器，该修改受使能控制：
                                                             1'b0: 当bit[28]=1时，此Slave口的QOS修改为2'b00(最低优先级)
                                                             1'b1: 当bit[28]=1时，此Slave口的QOS修改为2'b11(最高优先级)
                                                             注意：该寄存器受写锁lock保护。 */
        unsigned int  s15_qos_modify_en    : 1;  /* bit[30]: slave 15 口 QOS 修改使能：
                                                             1'b0: QOS不做任何更改
                                                             1'b1: 更改此slave口的QOS，QOS值由bit[31]的设定
                                                             注意：该寄存器受写锁lock保护。 */
        unsigned int  s15_qos_modify_value : 1;  /* bit[31]: Slave 15 口QOS设定修改后门
                                                             寄存器，该修改受使能控制：
                                                             1'b0: 当bit[30]=1时，此Slave口的QOS修改为2'b00(最低优先级)
                                                             1'b1: 当bit[30]=1时，此Slave口的QOS修改为2'b11(最高优先级)
                                                             注意：该寄存器受写锁lock保护。 */
    } reg;
} SOC_MMBUF_SMC_QOS_BACKDOOR_UNION;
#endif
#define SOC_MMBUF_SMC_QOS_BACKDOOR_s0_qos_modify_en_START      (0)
#define SOC_MMBUF_SMC_QOS_BACKDOOR_s0_qos_modify_en_END        (0)
#define SOC_MMBUF_SMC_QOS_BACKDOOR_s0_qos_modify_value_START   (1)
#define SOC_MMBUF_SMC_QOS_BACKDOOR_s0_qos_modify_value_END     (1)
#define SOC_MMBUF_SMC_QOS_BACKDOOR_s1_qos_modify_en_START      (2)
#define SOC_MMBUF_SMC_QOS_BACKDOOR_s1_qos_modify_en_END        (2)
#define SOC_MMBUF_SMC_QOS_BACKDOOR_s1_qos_modify_value_START   (3)
#define SOC_MMBUF_SMC_QOS_BACKDOOR_s1_qos_modify_value_END     (3)
#define SOC_MMBUF_SMC_QOS_BACKDOOR_s2_qos_modify_en_START      (4)
#define SOC_MMBUF_SMC_QOS_BACKDOOR_s2_qos_modify_en_END        (4)
#define SOC_MMBUF_SMC_QOS_BACKDOOR_s2_qos_modify_value_START   (5)
#define SOC_MMBUF_SMC_QOS_BACKDOOR_s2_qos_modify_value_END     (5)
#define SOC_MMBUF_SMC_QOS_BACKDOOR_s3_qos_modify_en_START      (6)
#define SOC_MMBUF_SMC_QOS_BACKDOOR_s3_qos_modify_en_END        (6)
#define SOC_MMBUF_SMC_QOS_BACKDOOR_s3_qos_modify_value_START   (7)
#define SOC_MMBUF_SMC_QOS_BACKDOOR_s3_qos_modify_value_END     (7)
#define SOC_MMBUF_SMC_QOS_BACKDOOR_s4_qos_modify_en_START      (8)
#define SOC_MMBUF_SMC_QOS_BACKDOOR_s4_qos_modify_en_END        (8)
#define SOC_MMBUF_SMC_QOS_BACKDOOR_s4_qos_modify_value_START   (9)
#define SOC_MMBUF_SMC_QOS_BACKDOOR_s4_qos_modify_value_END     (9)
#define SOC_MMBUF_SMC_QOS_BACKDOOR_s5_qos_modify_en_START      (10)
#define SOC_MMBUF_SMC_QOS_BACKDOOR_s5_qos_modify_en_END        (10)
#define SOC_MMBUF_SMC_QOS_BACKDOOR_s5_qos_modify_value_START   (11)
#define SOC_MMBUF_SMC_QOS_BACKDOOR_s5_qos_modify_value_END     (11)
#define SOC_MMBUF_SMC_QOS_BACKDOOR_s6_qos_modify_en_START      (12)
#define SOC_MMBUF_SMC_QOS_BACKDOOR_s6_qos_modify_en_END        (12)
#define SOC_MMBUF_SMC_QOS_BACKDOOR_s6_qos_modify_value_START   (13)
#define SOC_MMBUF_SMC_QOS_BACKDOOR_s6_qos_modify_value_END     (13)
#define SOC_MMBUF_SMC_QOS_BACKDOOR_s7_qos_modify_en_START      (14)
#define SOC_MMBUF_SMC_QOS_BACKDOOR_s7_qos_modify_en_END        (14)
#define SOC_MMBUF_SMC_QOS_BACKDOOR_s7_qos_modify_value_START   (15)
#define SOC_MMBUF_SMC_QOS_BACKDOOR_s7_qos_modify_value_END     (15)
#define SOC_MMBUF_SMC_QOS_BACKDOOR_s8_qos_modify_en_START      (16)
#define SOC_MMBUF_SMC_QOS_BACKDOOR_s8_qos_modify_en_END        (16)
#define SOC_MMBUF_SMC_QOS_BACKDOOR_s8_qos_modify_value_START   (17)
#define SOC_MMBUF_SMC_QOS_BACKDOOR_s8_qos_modify_value_END     (17)
#define SOC_MMBUF_SMC_QOS_BACKDOOR_s9_qos_modify_en_START      (18)
#define SOC_MMBUF_SMC_QOS_BACKDOOR_s9_qos_modify_en_END        (18)
#define SOC_MMBUF_SMC_QOS_BACKDOOR_s9_qos_modify_value_START   (19)
#define SOC_MMBUF_SMC_QOS_BACKDOOR_s9_qos_modify_value_END     (19)
#define SOC_MMBUF_SMC_QOS_BACKDOOR_s10_qos_modify_en_START     (20)
#define SOC_MMBUF_SMC_QOS_BACKDOOR_s10_qos_modify_en_END       (20)
#define SOC_MMBUF_SMC_QOS_BACKDOOR_s10_qos_modify_value_START  (21)
#define SOC_MMBUF_SMC_QOS_BACKDOOR_s10_qos_modify_value_END    (21)
#define SOC_MMBUF_SMC_QOS_BACKDOOR_s11_qos_modify_en_START     (22)
#define SOC_MMBUF_SMC_QOS_BACKDOOR_s11_qos_modify_en_END       (22)
#define SOC_MMBUF_SMC_QOS_BACKDOOR_s11_qos_modify_value_START  (23)
#define SOC_MMBUF_SMC_QOS_BACKDOOR_s11_qos_modify_value_END    (23)
#define SOC_MMBUF_SMC_QOS_BACKDOOR_s12_qos_modify_en_START     (24)
#define SOC_MMBUF_SMC_QOS_BACKDOOR_s12_qos_modify_en_END       (24)
#define SOC_MMBUF_SMC_QOS_BACKDOOR_s12_qos_modify_value_START  (25)
#define SOC_MMBUF_SMC_QOS_BACKDOOR_s12_qos_modify_value_END    (25)
#define SOC_MMBUF_SMC_QOS_BACKDOOR_s13_qos_modify_en_START     (26)
#define SOC_MMBUF_SMC_QOS_BACKDOOR_s13_qos_modify_en_END       (26)
#define SOC_MMBUF_SMC_QOS_BACKDOOR_s13_qos_modify_value_START  (27)
#define SOC_MMBUF_SMC_QOS_BACKDOOR_s13_qos_modify_value_END    (27)
#define SOC_MMBUF_SMC_QOS_BACKDOOR_s14_qos_modify_en_START     (28)
#define SOC_MMBUF_SMC_QOS_BACKDOOR_s14_qos_modify_en_END       (28)
#define SOC_MMBUF_SMC_QOS_BACKDOOR_s14_qos_modify_value_START  (29)
#define SOC_MMBUF_SMC_QOS_BACKDOOR_s14_qos_modify_value_END    (29)
#define SOC_MMBUF_SMC_QOS_BACKDOOR_s15_qos_modify_en_START     (30)
#define SOC_MMBUF_SMC_QOS_BACKDOOR_s15_qos_modify_en_END       (30)
#define SOC_MMBUF_SMC_QOS_BACKDOOR_s15_qos_modify_value_START  (31)
#define SOC_MMBUF_SMC_QOS_BACKDOOR_s15_qos_modify_value_END    (31)


/*****************************************************************************
 结构名    : SOC_MMBUF_SMC_DFX_WCMD_CNT_1ST_UNION
 结构说明  : SMC_DFX_WCMD_CNT_1ST 寄存器结构定义。地址偏移量:0x0014，初值:0x00000000，宽度:32
 寄存器说明: 还剩余的未完成的AXI命令数，单位为AXI命令。
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  dfx_cs0_wcmd_cnt_1st : 4;  /* bit[0-3]  : 此counter值表示还剩余的未被拆分的AXI命令数，单位为AXI命令。Cnt_2nd-cnt_1st的值表示当前已经被拆分的命令数，单位为AXI命令。 */
        unsigned int  dfx_cs0_wcmd_cnt_2nd : 4;  /* bit[4-7]  : 此counter值表示还剩余的未完成的AXI命令数，单位为AXI命令。 */
        unsigned int  dfx_cs1_wcmd_cnt_1st : 4;  /* bit[8-11] : 此counter值表示还剩余的未被拆分的AXI命令数，单位为AXI命令。Cnt_2nd-cnt_1st的值表示当前已经被拆分的命令数，单位为AXI命令。 */
        unsigned int  dfx_cs1_wcmd_cnt_2nd : 4;  /* bit[12-15]: 此counter值表示还剩余的未完成的AXI命令数，单位为AXI命令。 */
        unsigned int  dfx_cs2_wcmd_cnt_1st : 4;  /* bit[16-19]: 此counter值表示还剩余的未被拆分的AXI命令数，单位为AXI命令。Cnt_2nd-cnt_1st的值表示当前已经被拆分的命令数，单位为AXI命令。 */
        unsigned int  dfx_cs2_wcmd_cnt_2nd : 4;  /* bit[20-23]: 此counter值表示还剩余的未完成的AXI命令数，单位为AXI命令。 */
        unsigned int  dfx_cs3_wcmd_cnt_1st : 4;  /* bit[24-27]: 此counter值表示还剩余的未被拆分的AXI命令数，单位为AXI命令。Cnt_2nd-cnt_1st的值表示当前已经被拆分的命令数，单位为AXI命令。 */
        unsigned int  dfx_cs3_wcmd_cnt_2nd : 4;  /* bit[28-31]: 此counter值表示还剩余的未完成的AXI命令数，单位为AXI命令。 */
    } reg;
} SOC_MMBUF_SMC_DFX_WCMD_CNT_1ST_UNION;
#endif
#define SOC_MMBUF_SMC_DFX_WCMD_CNT_1ST_dfx_cs0_wcmd_cnt_1st_START  (0)
#define SOC_MMBUF_SMC_DFX_WCMD_CNT_1ST_dfx_cs0_wcmd_cnt_1st_END    (3)
#define SOC_MMBUF_SMC_DFX_WCMD_CNT_1ST_dfx_cs0_wcmd_cnt_2nd_START  (4)
#define SOC_MMBUF_SMC_DFX_WCMD_CNT_1ST_dfx_cs0_wcmd_cnt_2nd_END    (7)
#define SOC_MMBUF_SMC_DFX_WCMD_CNT_1ST_dfx_cs1_wcmd_cnt_1st_START  (8)
#define SOC_MMBUF_SMC_DFX_WCMD_CNT_1ST_dfx_cs1_wcmd_cnt_1st_END    (11)
#define SOC_MMBUF_SMC_DFX_WCMD_CNT_1ST_dfx_cs1_wcmd_cnt_2nd_START  (12)
#define SOC_MMBUF_SMC_DFX_WCMD_CNT_1ST_dfx_cs1_wcmd_cnt_2nd_END    (15)
#define SOC_MMBUF_SMC_DFX_WCMD_CNT_1ST_dfx_cs2_wcmd_cnt_1st_START  (16)
#define SOC_MMBUF_SMC_DFX_WCMD_CNT_1ST_dfx_cs2_wcmd_cnt_1st_END    (19)
#define SOC_MMBUF_SMC_DFX_WCMD_CNT_1ST_dfx_cs2_wcmd_cnt_2nd_START  (20)
#define SOC_MMBUF_SMC_DFX_WCMD_CNT_1ST_dfx_cs2_wcmd_cnt_2nd_END    (23)
#define SOC_MMBUF_SMC_DFX_WCMD_CNT_1ST_dfx_cs3_wcmd_cnt_1st_START  (24)
#define SOC_MMBUF_SMC_DFX_WCMD_CNT_1ST_dfx_cs3_wcmd_cnt_1st_END    (27)
#define SOC_MMBUF_SMC_DFX_WCMD_CNT_1ST_dfx_cs3_wcmd_cnt_2nd_START  (28)
#define SOC_MMBUF_SMC_DFX_WCMD_CNT_1ST_dfx_cs3_wcmd_cnt_2nd_END    (31)


/*****************************************************************************
 结构名    : SOC_MMBUF_SMC_DFX_WCMD_CNT_2ND_UNION
 结构说明  : SMC_DFX_WCMD_CNT_2ND 寄存器结构定义。地址偏移量:0x0018，初值:0x00000000，宽度:32
 寄存器说明: 还剩余的未完成的AXI命令数，单位为AXI命令。
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  dfx_cs4_wcmd_cnt_1st : 4;  /* bit[0-3]  : 此counter值表示还剩余的未被拆分的AXI命令数，单位为AXI命令。Cnt_2nd-cnt_1st的值表示当前已经被拆分的命令数，单位为AXI命令。 */
        unsigned int  dfx_cs4_wcmd_cnt_2nd : 4;  /* bit[4-7]  : 此counter值表示还剩余的未完成的AXI命令数，单位为AXI命令。 */
        unsigned int  dfx_cs5_wcmd_cnt_1st : 4;  /* bit[8-11] : 此counter值表示还剩余的未被拆分的AXI命令数，单位为AXI命令。Cnt_2nd-cnt_1st的值表示当前已经被拆分的命令数，单位为AXI命令。 */
        unsigned int  dfx_cs5_wcmd_cnt_2nd : 4;  /* bit[12-15]: 此counter值表示还剩余的未完成的AXI命令数，单位为AXI命令。 */
        unsigned int  dfx_cs6_wcmd_cnt_1st : 4;  /* bit[16-19]: 此counter值表示还剩余的未被拆分的AXI命令数，单位为AXI命令。Cnt_2nd-cnt_1st的值表示当前已经被拆分的命令数，单位为AXI命令。 */
        unsigned int  dfx_cs6_wcmd_cnt_2nd : 4;  /* bit[20-23]: 此counter值表示还剩余的未完成的AXI命令数，单位为AXI命令。 */
        unsigned int  dfx_cs7_wcmd_cnt_1st : 4;  /* bit[24-27]: 此counter值表示还剩余的未被拆分的AXI命令数，单位为AXI命令。Cnt_2nd-cnt_1st的值表示当前已经被拆分的命令数，单位为AXI命令。 */
        unsigned int  dfx_cs7_wcmd_cnt_2nd : 4;  /* bit[28-31]: 此counter值表示还剩余的未完成的AXI命令数，单位为AXI命令。 */
    } reg;
} SOC_MMBUF_SMC_DFX_WCMD_CNT_2ND_UNION;
#endif
#define SOC_MMBUF_SMC_DFX_WCMD_CNT_2ND_dfx_cs4_wcmd_cnt_1st_START  (0)
#define SOC_MMBUF_SMC_DFX_WCMD_CNT_2ND_dfx_cs4_wcmd_cnt_1st_END    (3)
#define SOC_MMBUF_SMC_DFX_WCMD_CNT_2ND_dfx_cs4_wcmd_cnt_2nd_START  (4)
#define SOC_MMBUF_SMC_DFX_WCMD_CNT_2ND_dfx_cs4_wcmd_cnt_2nd_END    (7)
#define SOC_MMBUF_SMC_DFX_WCMD_CNT_2ND_dfx_cs5_wcmd_cnt_1st_START  (8)
#define SOC_MMBUF_SMC_DFX_WCMD_CNT_2ND_dfx_cs5_wcmd_cnt_1st_END    (11)
#define SOC_MMBUF_SMC_DFX_WCMD_CNT_2ND_dfx_cs5_wcmd_cnt_2nd_START  (12)
#define SOC_MMBUF_SMC_DFX_WCMD_CNT_2ND_dfx_cs5_wcmd_cnt_2nd_END    (15)
#define SOC_MMBUF_SMC_DFX_WCMD_CNT_2ND_dfx_cs6_wcmd_cnt_1st_START  (16)
#define SOC_MMBUF_SMC_DFX_WCMD_CNT_2ND_dfx_cs6_wcmd_cnt_1st_END    (19)
#define SOC_MMBUF_SMC_DFX_WCMD_CNT_2ND_dfx_cs6_wcmd_cnt_2nd_START  (20)
#define SOC_MMBUF_SMC_DFX_WCMD_CNT_2ND_dfx_cs6_wcmd_cnt_2nd_END    (23)
#define SOC_MMBUF_SMC_DFX_WCMD_CNT_2ND_dfx_cs7_wcmd_cnt_1st_START  (24)
#define SOC_MMBUF_SMC_DFX_WCMD_CNT_2ND_dfx_cs7_wcmd_cnt_1st_END    (27)
#define SOC_MMBUF_SMC_DFX_WCMD_CNT_2ND_dfx_cs7_wcmd_cnt_2nd_START  (28)
#define SOC_MMBUF_SMC_DFX_WCMD_CNT_2ND_dfx_cs7_wcmd_cnt_2nd_END    (31)


/*****************************************************************************
 结构名    : SOC_MMBUF_SMC_DFX_WCMD_CNT_3RD_UNION
 结构说明  : SMC_DFX_WCMD_CNT_3RD 寄存器结构定义。地址偏移量:0x001C，初值:0x00000000，宽度:32
 寄存器说明: 还剩余的未完成的AXI命令数，单位为AXI命令。
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  dfx_cs8_wcmd_cnt_1st  : 4;  /* bit[0-3]  : 此counter值表示还剩余的未被拆分的AXI命令数，单位为AXI命令。Cnt_2nd-cnt_1st的值表示当前已经被拆分的命令数，单位为AXI命令。 */
        unsigned int  dfx_cs8_wcmd_cnt_2nd  : 4;  /* bit[4-7]  : 此counter值表示还剩余的未完成的AXI命令数，单位为AXI命令。 */
        unsigned int  dfx_cs9_wcmd_cnt_1st  : 4;  /* bit[8-11] : 此counter值表示还剩余的未被拆分的AXI命令数，单位为AXI命令。Cnt_2nd-cnt_1st的值表示当前已经被拆分的命令数，单位为AXI命令。 */
        unsigned int  dfx_cs9_wcmd_cnt_2nd  : 4;  /* bit[12-15]: 此counter值表示还剩余的未完成的AXI命令数，单位为AXI命令。 */
        unsigned int  dfx_cs10_wcmd_cnt_1st : 4;  /* bit[16-19]: 此counter值表示还剩余的未被拆分的AXI命令数，单位为AXI命令。Cnt_2nd-cnt_1st的值表示当前已经被拆分的命令数，单位为AXI命令。 */
        unsigned int  dfx_cs10_wcmd_cnt_2nd : 4;  /* bit[20-23]: 此counter值表示还剩余的未完成的AXI命令数，单位为AXI命令。 */
        unsigned int  dfx_cs11_wcmd_cnt_1st : 4;  /* bit[24-27]: 此counter值表示还剩余的未被拆分的AXI命令数，单位为AXI命令。Cnt_2nd-cnt_1st的值表示当前已经被拆分的命令数，单位为AXI命令。 */
        unsigned int  dfx_cs11_wcmd_cnt_2nd : 4;  /* bit[28-31]: 此counter值表示还剩余的未完成的AXI命令数，单位为AXI命令。 */
    } reg;
} SOC_MMBUF_SMC_DFX_WCMD_CNT_3RD_UNION;
#endif
#define SOC_MMBUF_SMC_DFX_WCMD_CNT_3RD_dfx_cs8_wcmd_cnt_1st_START   (0)
#define SOC_MMBUF_SMC_DFX_WCMD_CNT_3RD_dfx_cs8_wcmd_cnt_1st_END     (3)
#define SOC_MMBUF_SMC_DFX_WCMD_CNT_3RD_dfx_cs8_wcmd_cnt_2nd_START   (4)
#define SOC_MMBUF_SMC_DFX_WCMD_CNT_3RD_dfx_cs8_wcmd_cnt_2nd_END     (7)
#define SOC_MMBUF_SMC_DFX_WCMD_CNT_3RD_dfx_cs9_wcmd_cnt_1st_START   (8)
#define SOC_MMBUF_SMC_DFX_WCMD_CNT_3RD_dfx_cs9_wcmd_cnt_1st_END     (11)
#define SOC_MMBUF_SMC_DFX_WCMD_CNT_3RD_dfx_cs9_wcmd_cnt_2nd_START   (12)
#define SOC_MMBUF_SMC_DFX_WCMD_CNT_3RD_dfx_cs9_wcmd_cnt_2nd_END     (15)
#define SOC_MMBUF_SMC_DFX_WCMD_CNT_3RD_dfx_cs10_wcmd_cnt_1st_START  (16)
#define SOC_MMBUF_SMC_DFX_WCMD_CNT_3RD_dfx_cs10_wcmd_cnt_1st_END    (19)
#define SOC_MMBUF_SMC_DFX_WCMD_CNT_3RD_dfx_cs10_wcmd_cnt_2nd_START  (20)
#define SOC_MMBUF_SMC_DFX_WCMD_CNT_3RD_dfx_cs10_wcmd_cnt_2nd_END    (23)
#define SOC_MMBUF_SMC_DFX_WCMD_CNT_3RD_dfx_cs11_wcmd_cnt_1st_START  (24)
#define SOC_MMBUF_SMC_DFX_WCMD_CNT_3RD_dfx_cs11_wcmd_cnt_1st_END    (27)
#define SOC_MMBUF_SMC_DFX_WCMD_CNT_3RD_dfx_cs11_wcmd_cnt_2nd_START  (28)
#define SOC_MMBUF_SMC_DFX_WCMD_CNT_3RD_dfx_cs11_wcmd_cnt_2nd_END    (31)


/*****************************************************************************
 结构名    : SOC_MMBUF_SMC_DFX_WCMD_CNT_4TH_UNION
 结构说明  : SMC_DFX_WCMD_CNT_4TH 寄存器结构定义。地址偏移量:0x0020，初值:0x00000000，宽度:32
 寄存器说明: 还剩余的未完成的AXI命令数，单位为AXI命令。
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  dfx_cs12_wcmd_cnt_1st : 4;  /* bit[0-3]  : 此counter值表示还剩余的未被拆分的AXI命令数，单位为AXI命令。Cnt_2nd-cnt_1st的值表示当前已经被拆分的命令数，单位为AXI命令。 */
        unsigned int  dfx_cs12_wcmd_cnt_2nd : 4;  /* bit[4-7]  : 此counter值表示还剩余的未完成的AXI命令数，单位为AXI命令。 */
        unsigned int  dfx_cs13_wcmd_cnt_1st : 4;  /* bit[8-11] : 此counter值表示还剩余的未被拆分的AXI命令数，单位为AXI命令。Cnt_2nd-cnt_1st的值表示当前已经被拆分的命令数，单位为AXI命令。 */
        unsigned int  dfx_cs13_wcmd_cnt_2nd : 4;  /* bit[12-15]: 此counter值表示还剩余的未完成的AXI命令数，单位为AXI命令。 */
        unsigned int  dfx_cs14_wcmd_cnt_1st : 4;  /* bit[16-19]: 此counter值表示还剩余的未被拆分的AXI命令数，单位为AXI命令。Cnt_2nd-cnt_1st的值表示当前已经被拆分的命令数，单位为AXI命令。 */
        unsigned int  dfx_cs14_wcmd_cnt_2nd : 4;  /* bit[20-23]: 此counter值表示还剩余的未完成的AXI命令数，单位为AXI命令。 */
        unsigned int  dfx_cs15_wcmd_cnt_1st : 4;  /* bit[24-27]: 此counter值表示还剩余的未被拆分的AXI命令数，单位为AXI命令。Cnt_2nd-cnt_1st的值表示当前已经被拆分的命令数，单位为AXI命令。 */
        unsigned int  dfx_cs15_wcmd_cnt_2nd : 4;  /* bit[28-31]: 此counter值表示还剩余的未完成的AXI命令数，单位为AXI命令。 */
    } reg;
} SOC_MMBUF_SMC_DFX_WCMD_CNT_4TH_UNION;
#endif
#define SOC_MMBUF_SMC_DFX_WCMD_CNT_4TH_dfx_cs12_wcmd_cnt_1st_START  (0)
#define SOC_MMBUF_SMC_DFX_WCMD_CNT_4TH_dfx_cs12_wcmd_cnt_1st_END    (3)
#define SOC_MMBUF_SMC_DFX_WCMD_CNT_4TH_dfx_cs12_wcmd_cnt_2nd_START  (4)
#define SOC_MMBUF_SMC_DFX_WCMD_CNT_4TH_dfx_cs12_wcmd_cnt_2nd_END    (7)
#define SOC_MMBUF_SMC_DFX_WCMD_CNT_4TH_dfx_cs13_wcmd_cnt_1st_START  (8)
#define SOC_MMBUF_SMC_DFX_WCMD_CNT_4TH_dfx_cs13_wcmd_cnt_1st_END    (11)
#define SOC_MMBUF_SMC_DFX_WCMD_CNT_4TH_dfx_cs13_wcmd_cnt_2nd_START  (12)
#define SOC_MMBUF_SMC_DFX_WCMD_CNT_4TH_dfx_cs13_wcmd_cnt_2nd_END    (15)
#define SOC_MMBUF_SMC_DFX_WCMD_CNT_4TH_dfx_cs14_wcmd_cnt_1st_START  (16)
#define SOC_MMBUF_SMC_DFX_WCMD_CNT_4TH_dfx_cs14_wcmd_cnt_1st_END    (19)
#define SOC_MMBUF_SMC_DFX_WCMD_CNT_4TH_dfx_cs14_wcmd_cnt_2nd_START  (20)
#define SOC_MMBUF_SMC_DFX_WCMD_CNT_4TH_dfx_cs14_wcmd_cnt_2nd_END    (23)
#define SOC_MMBUF_SMC_DFX_WCMD_CNT_4TH_dfx_cs15_wcmd_cnt_1st_START  (24)
#define SOC_MMBUF_SMC_DFX_WCMD_CNT_4TH_dfx_cs15_wcmd_cnt_1st_END    (27)
#define SOC_MMBUF_SMC_DFX_WCMD_CNT_4TH_dfx_cs15_wcmd_cnt_2nd_START  (28)
#define SOC_MMBUF_SMC_DFX_WCMD_CNT_4TH_dfx_cs15_wcmd_cnt_2nd_END    (31)


/*****************************************************************************
 结构名    : SOC_MMBUF_SMC_DFX_RCMD_CNT_1ST_UNION
 结构说明  : SMC_DFX_RCMD_CNT_1ST 寄存器结构定义。地址偏移量:0x0024，初值:0x00000000，宽度:32
 寄存器说明: 还剩余的未完成的AXI命令数，单位为AXI命令。
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  dfx_cs0_rcmd_cnt_1st : 4;  /* bit[0-3]  : 此counter值表示还剩余的未被拆分的AXI命令数，单位为AXI命令。Cnt_2nd-cnt_1st的值表示当前已经被拆分的命令数，单位为AXI命令。 */
        unsigned int  dfx_cs0_rcmd_cnt_2nd : 4;  /* bit[4-7]  : 此counter值表示还剩余的未完成的AXI命令数，单位为AXI命令。 */
        unsigned int  dfx_cs1_rcmd_cnt_1st : 4;  /* bit[8-11] : 此counter值表示还剩余的未被拆分的AXI命令数，单位为AXI命令。Cnt_2nd-cnt_1st的值表示当前已经被拆分的命令数，单位为AXI命令。 */
        unsigned int  dfx_cs1_rcmd_cnt_2nd : 4;  /* bit[12-15]: 此counter值表示还剩余的未完成的AXI命令数，单位为AXI命令。 */
        unsigned int  dfx_cs2_rcmd_cnt_1st : 4;  /* bit[16-19]: 此counter值表示还剩余的未被拆分的AXI命令数，单位为AXI命令。Cnt_2nd-cnt_1st的值表示当前已经被拆分的命令数，单位为AXI命令。 */
        unsigned int  dfx_cs2_rcmd_cnt_2nd : 4;  /* bit[20-23]: 此counter值表示还剩余的未完成的AXI命令数，单位为AXI命令。 */
        unsigned int  dfx_cs3_rcmd_cnt_1st : 4;  /* bit[24-27]: 此counter值表示还剩余的未被拆分的AXI命令数，单位为AXI命令。Cnt_2nd-cnt_1st的值表示当前已经被拆分的命令数，单位为AXI命令。 */
        unsigned int  dfx_cs3_rcmd_cnt_2nd : 4;  /* bit[28-31]: 此counter值表示还剩余的未完成的AXI命令数，单位为AXI命令。 */
    } reg;
} SOC_MMBUF_SMC_DFX_RCMD_CNT_1ST_UNION;
#endif
#define SOC_MMBUF_SMC_DFX_RCMD_CNT_1ST_dfx_cs0_rcmd_cnt_1st_START  (0)
#define SOC_MMBUF_SMC_DFX_RCMD_CNT_1ST_dfx_cs0_rcmd_cnt_1st_END    (3)
#define SOC_MMBUF_SMC_DFX_RCMD_CNT_1ST_dfx_cs0_rcmd_cnt_2nd_START  (4)
#define SOC_MMBUF_SMC_DFX_RCMD_CNT_1ST_dfx_cs0_rcmd_cnt_2nd_END    (7)
#define SOC_MMBUF_SMC_DFX_RCMD_CNT_1ST_dfx_cs1_rcmd_cnt_1st_START  (8)
#define SOC_MMBUF_SMC_DFX_RCMD_CNT_1ST_dfx_cs1_rcmd_cnt_1st_END    (11)
#define SOC_MMBUF_SMC_DFX_RCMD_CNT_1ST_dfx_cs1_rcmd_cnt_2nd_START  (12)
#define SOC_MMBUF_SMC_DFX_RCMD_CNT_1ST_dfx_cs1_rcmd_cnt_2nd_END    (15)
#define SOC_MMBUF_SMC_DFX_RCMD_CNT_1ST_dfx_cs2_rcmd_cnt_1st_START  (16)
#define SOC_MMBUF_SMC_DFX_RCMD_CNT_1ST_dfx_cs2_rcmd_cnt_1st_END    (19)
#define SOC_MMBUF_SMC_DFX_RCMD_CNT_1ST_dfx_cs2_rcmd_cnt_2nd_START  (20)
#define SOC_MMBUF_SMC_DFX_RCMD_CNT_1ST_dfx_cs2_rcmd_cnt_2nd_END    (23)
#define SOC_MMBUF_SMC_DFX_RCMD_CNT_1ST_dfx_cs3_rcmd_cnt_1st_START  (24)
#define SOC_MMBUF_SMC_DFX_RCMD_CNT_1ST_dfx_cs3_rcmd_cnt_1st_END    (27)
#define SOC_MMBUF_SMC_DFX_RCMD_CNT_1ST_dfx_cs3_rcmd_cnt_2nd_START  (28)
#define SOC_MMBUF_SMC_DFX_RCMD_CNT_1ST_dfx_cs3_rcmd_cnt_2nd_END    (31)


/*****************************************************************************
 结构名    : SOC_MMBUF_SMC_DFX_RCMD_CNT_2ND_UNION
 结构说明  : SMC_DFX_RCMD_CNT_2ND 寄存器结构定义。地址偏移量:0x0028，初值:0x00000000，宽度:32
 寄存器说明: 还剩余的未完成的AXI命令数，单位为AXI命令。
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  dfx_cs4_rcmd_cnt_1st : 4;  /* bit[0-3]  : 此counter值表示还剩余的未被拆分的AXI命令数，单位为AXI命令。Cnt_2nd-cnt_1st的值表示当前已经被拆分的命令数，单位为AXI命令。 */
        unsigned int  dfx_cs4_rcmd_cnt_2nd : 4;  /* bit[4-7]  : 此counter值表示还剩余的未完成的AXI命令数，单位为AXI命令。 */
        unsigned int  dfx_cs5_rcmd_cnt_1st : 4;  /* bit[8-11] : 此counter值表示还剩余的未被拆分的AXI命令数，单位为AXI命令。Cnt_2nd-cnt_1st的值表示当前已经被拆分的命令数，单位为AXI命令。 */
        unsigned int  dfx_cs5_rcmd_cnt_2nd : 4;  /* bit[12-15]: 此counter值表示还剩余的未完成的AXI命令数，单位为AXI命令。 */
        unsigned int  dfx_cs6_rcmd_cnt_1st : 4;  /* bit[16-19]: 此counter值表示还剩余的未被拆分的AXI命令数，单位为AXI命令。Cnt_2nd-cnt_1st的值表示当前已经被拆分的命令数，单位为AXI命令。 */
        unsigned int  dfx_cs6_rcmd_cnt_2nd : 4;  /* bit[20-23]: 此counter值表示还剩余的未完成的AXI命令数，单位为AXI命令。 */
        unsigned int  dfx_cs7_rcmd_cnt_1st : 4;  /* bit[24-27]: 此counter值表示还剩余的未被拆分的AXI命令数，单位为AXI命令。Cnt_2nd-cnt_1st的值表示当前已经被拆分的命令数，单位为AXI命令。 */
        unsigned int  dfx_cs7_rcmd_cnt_2nd : 4;  /* bit[28-31]: 此counter值表示还剩余的未完成的AXI命令数，单位为AXI命令。 */
    } reg;
} SOC_MMBUF_SMC_DFX_RCMD_CNT_2ND_UNION;
#endif
#define SOC_MMBUF_SMC_DFX_RCMD_CNT_2ND_dfx_cs4_rcmd_cnt_1st_START  (0)
#define SOC_MMBUF_SMC_DFX_RCMD_CNT_2ND_dfx_cs4_rcmd_cnt_1st_END    (3)
#define SOC_MMBUF_SMC_DFX_RCMD_CNT_2ND_dfx_cs4_rcmd_cnt_2nd_START  (4)
#define SOC_MMBUF_SMC_DFX_RCMD_CNT_2ND_dfx_cs4_rcmd_cnt_2nd_END    (7)
#define SOC_MMBUF_SMC_DFX_RCMD_CNT_2ND_dfx_cs5_rcmd_cnt_1st_START  (8)
#define SOC_MMBUF_SMC_DFX_RCMD_CNT_2ND_dfx_cs5_rcmd_cnt_1st_END    (11)
#define SOC_MMBUF_SMC_DFX_RCMD_CNT_2ND_dfx_cs5_rcmd_cnt_2nd_START  (12)
#define SOC_MMBUF_SMC_DFX_RCMD_CNT_2ND_dfx_cs5_rcmd_cnt_2nd_END    (15)
#define SOC_MMBUF_SMC_DFX_RCMD_CNT_2ND_dfx_cs6_rcmd_cnt_1st_START  (16)
#define SOC_MMBUF_SMC_DFX_RCMD_CNT_2ND_dfx_cs6_rcmd_cnt_1st_END    (19)
#define SOC_MMBUF_SMC_DFX_RCMD_CNT_2ND_dfx_cs6_rcmd_cnt_2nd_START  (20)
#define SOC_MMBUF_SMC_DFX_RCMD_CNT_2ND_dfx_cs6_rcmd_cnt_2nd_END    (23)
#define SOC_MMBUF_SMC_DFX_RCMD_CNT_2ND_dfx_cs7_rcmd_cnt_1st_START  (24)
#define SOC_MMBUF_SMC_DFX_RCMD_CNT_2ND_dfx_cs7_rcmd_cnt_1st_END    (27)
#define SOC_MMBUF_SMC_DFX_RCMD_CNT_2ND_dfx_cs7_rcmd_cnt_2nd_START  (28)
#define SOC_MMBUF_SMC_DFX_RCMD_CNT_2ND_dfx_cs7_rcmd_cnt_2nd_END    (31)


/*****************************************************************************
 结构名    : SOC_MMBUF_SMC_DFX_RCMD_CNT_3RD_UNION
 结构说明  : SMC_DFX_RCMD_CNT_3RD 寄存器结构定义。地址偏移量:0x002C，初值:0x00000000，宽度:32
 寄存器说明: 还剩余的未完成的AXI命令数，单位为AXI命令。
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  dfx_cs8_rcmd_cnt_1st  : 4;  /* bit[0-3]  : 此counter值表示还剩余的未被拆分的AXI命令数，单位为AXI命令。Cnt_2nd - cnt_1st的值表示当前已经被拆分的命令数，单位为AXI命令。 */
        unsigned int  dfx_cs8_rcmd_cnt_2nd  : 4;  /* bit[4-7]  : 此counter值表示还剩余的未完成的AXI命令数，单位为AXI命令。 */
        unsigned int  dfx_cs9_rcmd_cnt_1st  : 4;  /* bit[8-11] : 此counter值表示还剩余的未被拆分的AXI命令数，单位为AXI命令。Cnt_2nd-cnt_1st的值表示当前已经被拆分的命令数，单位为AXI命令。 */
        unsigned int  dfx_cs9_rcmd_cnt_2nd  : 4;  /* bit[12-15]: 此counter值表示还剩余的未完成的AXI命令数，单位为AXI命令。 */
        unsigned int  dfx_cs10_rcmd_cnt_1st : 4;  /* bit[16-19]: 此counter值表示还剩余的未被拆分的AXI命令数，单位为AXI命令。Cnt_2nd-cnt_1st的值表示当前已经被拆分的命令数，单位为AXI命令。 */
        unsigned int  dfx_cs10_rcmd_cnt_2nd : 4;  /* bit[20-23]: 此counter值表示还剩余的未完成的AXI命令数，单位为AXI命令。 */
        unsigned int  dfx_cs11_rcmd_cnt_1st : 4;  /* bit[24-27]: 此counter值表示还剩余的未被拆分的AXI命令数，单位为AXI命令。Cnt_2nd-cnt_1st的值表示当前已经被拆分的命令数，单位为AXI命令。 */
        unsigned int  dfx_cs11_rcmd_cnt_2nd : 4;  /* bit[28-31]: 此counter值表示还剩余的未完成的AXI命令数，单位为AXI命令。 */
    } reg;
} SOC_MMBUF_SMC_DFX_RCMD_CNT_3RD_UNION;
#endif
#define SOC_MMBUF_SMC_DFX_RCMD_CNT_3RD_dfx_cs8_rcmd_cnt_1st_START   (0)
#define SOC_MMBUF_SMC_DFX_RCMD_CNT_3RD_dfx_cs8_rcmd_cnt_1st_END     (3)
#define SOC_MMBUF_SMC_DFX_RCMD_CNT_3RD_dfx_cs8_rcmd_cnt_2nd_START   (4)
#define SOC_MMBUF_SMC_DFX_RCMD_CNT_3RD_dfx_cs8_rcmd_cnt_2nd_END     (7)
#define SOC_MMBUF_SMC_DFX_RCMD_CNT_3RD_dfx_cs9_rcmd_cnt_1st_START   (8)
#define SOC_MMBUF_SMC_DFX_RCMD_CNT_3RD_dfx_cs9_rcmd_cnt_1st_END     (11)
#define SOC_MMBUF_SMC_DFX_RCMD_CNT_3RD_dfx_cs9_rcmd_cnt_2nd_START   (12)
#define SOC_MMBUF_SMC_DFX_RCMD_CNT_3RD_dfx_cs9_rcmd_cnt_2nd_END     (15)
#define SOC_MMBUF_SMC_DFX_RCMD_CNT_3RD_dfx_cs10_rcmd_cnt_1st_START  (16)
#define SOC_MMBUF_SMC_DFX_RCMD_CNT_3RD_dfx_cs10_rcmd_cnt_1st_END    (19)
#define SOC_MMBUF_SMC_DFX_RCMD_CNT_3RD_dfx_cs10_rcmd_cnt_2nd_START  (20)
#define SOC_MMBUF_SMC_DFX_RCMD_CNT_3RD_dfx_cs10_rcmd_cnt_2nd_END    (23)
#define SOC_MMBUF_SMC_DFX_RCMD_CNT_3RD_dfx_cs11_rcmd_cnt_1st_START  (24)
#define SOC_MMBUF_SMC_DFX_RCMD_CNT_3RD_dfx_cs11_rcmd_cnt_1st_END    (27)
#define SOC_MMBUF_SMC_DFX_RCMD_CNT_3RD_dfx_cs11_rcmd_cnt_2nd_START  (28)
#define SOC_MMBUF_SMC_DFX_RCMD_CNT_3RD_dfx_cs11_rcmd_cnt_2nd_END    (31)


/*****************************************************************************
 结构名    : SOC_MMBUF_SMC_DFX_RCMD_CNT_4TH_UNION
 结构说明  : SMC_DFX_RCMD_CNT_4TH 寄存器结构定义。地址偏移量:0x0030，初值:0x00000000，宽度:32
 寄存器说明: 还剩余的未完成的AXI命令数，单位为AXI命令。
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  dfx_cs12_rcmd_cnt_1st : 4;  /* bit[0-3]  : 此counter值表示还剩余的未被拆分的AXI命令数，单位为AXI命令。Cnt_2nd-cnt_1st的值表示当前已经被拆分的命令数，单位为AXI命令。 */
        unsigned int  dfx_cs12_rcmd_cnt_2nd : 4;  /* bit[4-7]  : 此counter值表示还剩余的未完成的AXI命令数，单位为AXI命令。 */
        unsigned int  dfx_cs13_rcmd_cnt_1st : 4;  /* bit[8-11] : 此counter值表示还剩余的未被拆分的AXI命令数，单位为AXI命令。Cnt_2nd-cnt_1st的值表示当前已经被拆分的命令数，单位为AXI命令。 */
        unsigned int  dfx_cs13_rcmd_cnt_2nd : 4;  /* bit[12-15]: 此counter值表示还剩余的未完成的AXI命令数，单位为AXI命令。 */
        unsigned int  dfx_cs14_rcmd_cnt_1st : 4;  /* bit[16-19]: 此counter值表示还剩余的未被拆分的AXI命令数，单位为AXI命令。Cnt_2nd-cnt_1st的值表示当前已经被拆分的命令数，单位为AXI命令。 */
        unsigned int  dfx_cs14_rcmd_cnt_2nd : 4;  /* bit[20-23]: 此counter值表示还剩余的未完成的AXI命令数，单位为AXI命令。 */
        unsigned int  dfx_cs15_rcmd_cnt_1st : 4;  /* bit[24-27]: 此counter值表示还剩余的未被拆分的AXI命令数，单位为AXI命令。Cnt_2nd-cnt_1st的值表示当前已经被拆分的命令数，单位为AXI命令。 */
        unsigned int  dfx_cs15_rcmd_cnt_2nd : 4;  /* bit[28-31]: 此counter值表示还剩余的未完成的AXI命令数，单位为AXI命令。 */
    } reg;
} SOC_MMBUF_SMC_DFX_RCMD_CNT_4TH_UNION;
#endif
#define SOC_MMBUF_SMC_DFX_RCMD_CNT_4TH_dfx_cs12_rcmd_cnt_1st_START  (0)
#define SOC_MMBUF_SMC_DFX_RCMD_CNT_4TH_dfx_cs12_rcmd_cnt_1st_END    (3)
#define SOC_MMBUF_SMC_DFX_RCMD_CNT_4TH_dfx_cs12_rcmd_cnt_2nd_START  (4)
#define SOC_MMBUF_SMC_DFX_RCMD_CNT_4TH_dfx_cs12_rcmd_cnt_2nd_END    (7)
#define SOC_MMBUF_SMC_DFX_RCMD_CNT_4TH_dfx_cs13_rcmd_cnt_1st_START  (8)
#define SOC_MMBUF_SMC_DFX_RCMD_CNT_4TH_dfx_cs13_rcmd_cnt_1st_END    (11)
#define SOC_MMBUF_SMC_DFX_RCMD_CNT_4TH_dfx_cs13_rcmd_cnt_2nd_START  (12)
#define SOC_MMBUF_SMC_DFX_RCMD_CNT_4TH_dfx_cs13_rcmd_cnt_2nd_END    (15)
#define SOC_MMBUF_SMC_DFX_RCMD_CNT_4TH_dfx_cs14_rcmd_cnt_1st_START  (16)
#define SOC_MMBUF_SMC_DFX_RCMD_CNT_4TH_dfx_cs14_rcmd_cnt_1st_END    (19)
#define SOC_MMBUF_SMC_DFX_RCMD_CNT_4TH_dfx_cs14_rcmd_cnt_2nd_START  (20)
#define SOC_MMBUF_SMC_DFX_RCMD_CNT_4TH_dfx_cs14_rcmd_cnt_2nd_END    (23)
#define SOC_MMBUF_SMC_DFX_RCMD_CNT_4TH_dfx_cs15_rcmd_cnt_1st_START  (24)
#define SOC_MMBUF_SMC_DFX_RCMD_CNT_4TH_dfx_cs15_rcmd_cnt_1st_END    (27)
#define SOC_MMBUF_SMC_DFX_RCMD_CNT_4TH_dfx_cs15_rcmd_cnt_2nd_START  (28)
#define SOC_MMBUF_SMC_DFX_RCMD_CNT_4TH_dfx_cs15_rcmd_cnt_2nd_END    (31)


/*****************************************************************************
 结构名    : SOC_MMBUF_SMC_CS_IDLE_UNION
 结构说明  : SMC_CS_IDLE 寄存器结构定义。地址偏移量:0x0034，初值:0x0000FFFF，宽度:32
 寄存器说明: AXI slave口的状态。
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  dfx_cs0_idle  : 1;  /* bit[0]    : 表示该AXI slave口的状态。
                                                         1'b0:表示AXI slave口正在工作，即还有AXI命令未完成。
                                                         1'b1:表示AXI slave口空闲，即命令FIFO中的AXI命令全部完成。 */
        unsigned int  dfx_cs1_idle  : 1;  /* bit[1]    : 表示该AXI slave口的状态。
                                                         1'b0:表示AXI slave口正在工作，即还有AXI命令未完成。
                                                         1'b1:表示AXI slave口空闲，即命令FIFO中的AXI命令全部完成。 */
        unsigned int  dfx_cs2_idle  : 1;  /* bit[2]    : 表示该AXI slave口的状态。
                                                         1'b0:表示AXI slave口正在工作，即还有AXI命令未完成。
                                                         1'b1:表示AXI slave口空闲，即命令FIFO中的AXI命令全部完成。 */
        unsigned int  dfx_cs3_idle  : 1;  /* bit[3]    : 表示该AXI slave口的状态。
                                                         1'b0:表示AXI slave口正在工作，即还有AXI命令未完成。
                                                         1'b1:表示AXI slave口空闲，即命令FIFO中的AXI命令全部完成。 */
        unsigned int  dfx_cs4_idle  : 1;  /* bit[4]    : 表示该AXI slave口的状态。
                                                         1'b0:表示AXI slave口正在工作，即还有AXI命令未完成。
                                                         1'b1:表示AXI slave口空闲，即命令FIFO中的AXI命令全部完成。 */
        unsigned int  dfx_cs5_idle  : 1;  /* bit[5]    : 表示该AXI slave口的状态。
                                                         1'b0:表示AXI slave口正在工作，即还有AXI命令未完成。
                                                         1'b1:表示AXI slave口空闲，即命令FIFO中的AXI命令全部完成。 */
        unsigned int  dfx_cs6_idle  : 1;  /* bit[6]    : 表示该AXI slave口的状态。
                                                         1'b0:表示AXI slave口正在工作，即还有AXI命令未完成。
                                                         1'b1:表示AXI slave口空闲，即命令FIFO中的AXI命令全部完成。 */
        unsigned int  dfx_cs7_idle  : 1;  /* bit[7]    : 表示该AXI slave口的状态。
                                                         1'b0:表示AXI slave口正在工作，即还有AXI命令未完成。
                                                         1'b1:表示AXI slave口空闲，即命令FIFO中的AXI命令全部完成。 */
        unsigned int  dfx_cs8_idle  : 1;  /* bit[8]    : 表示该AXI slave口的状态。
                                                         1'b0:表示AXI slave口正在工作，即还有AXI命令未完成。
                                                         1'b1:表示AXI slave口空闲，即命令FIFO中的AXI命令全部完成。 */
        unsigned int  dfx_cs9_idle  : 1;  /* bit[9]    : 表示该AXI slave口的状态。
                                                         1'b0:表示AXI slave口正在工作，即还有AXI命令未完成。
                                                         1'b1:表示AXI slave口空闲，即命令FIFO中的AXI命令全部完成。 */
        unsigned int  dfx_cs10_idle : 1;  /* bit[10]   : 表示该AXI slave口的状态。
                                                         1'b0:表示AXI slave口正在工作，即还有AXI命令未完成。
                                                         1'b1:表示AXI slave口空闲，即命令FIFO中的AXI命令全部完成。 */
        unsigned int  dfx_cs11_idle : 1;  /* bit[11]   : 表示该AXI slave口的状态。
                                                         1'b0:表示AXI slave口正在工作，即还有AXI命令未完成。
                                                         1'b1:表示AXI slave口空闲，即命令FIFO中的AXI命令全部完成。 */
        unsigned int  dfx_cs12_idle : 1;  /* bit[12]   : 表示该AXI slave口的状态。
                                                         1'b0:表示AXI slave口正在工作，即还有AXI命令未完成。
                                                         1'b1:表示AXI slave口空闲，即命令FIFO中的AXI命令全部完成。 */
        unsigned int  dfx_cs13_idle : 1;  /* bit[13]   : 表示该AXI slave口的状态。
                                                         1'b0:表示AXI slave口正在工作，即还有AXI命令未完成。
                                                         1'b1:表示AXI slave口空闲，即命令FIFO中的AXI命令全部完成。 */
        unsigned int  dfx_cs14_idle : 1;  /* bit[14]   : 表示该AXI slave口的状态。
                                                         1'b0:表示AXI slave口正在工作，即还有AXI命令未完成。
                                                         1'b1:表示AXI slave口空闲，即命令FIFO中的AXI命令全部完成。 */
        unsigned int  dfx_cs15_idle : 1;  /* bit[15]   : 表示该AXI slave口的状态。
                                                         1'b0:表示AXI slave口正在工作，即还有AXI命令未完成。
                                                         1'b1:表示AXI slave口空闲，即命令FIFO中的AXI命令全部完成。 */
        unsigned int  reserved      : 16; /* bit[16-31]: Reserved. */
    } reg;
} SOC_MMBUF_SMC_CS_IDLE_UNION;
#endif
#define SOC_MMBUF_SMC_CS_IDLE_dfx_cs0_idle_START   (0)
#define SOC_MMBUF_SMC_CS_IDLE_dfx_cs0_idle_END     (0)
#define SOC_MMBUF_SMC_CS_IDLE_dfx_cs1_idle_START   (1)
#define SOC_MMBUF_SMC_CS_IDLE_dfx_cs1_idle_END     (1)
#define SOC_MMBUF_SMC_CS_IDLE_dfx_cs2_idle_START   (2)
#define SOC_MMBUF_SMC_CS_IDLE_dfx_cs2_idle_END     (2)
#define SOC_MMBUF_SMC_CS_IDLE_dfx_cs3_idle_START   (3)
#define SOC_MMBUF_SMC_CS_IDLE_dfx_cs3_idle_END     (3)
#define SOC_MMBUF_SMC_CS_IDLE_dfx_cs4_idle_START   (4)
#define SOC_MMBUF_SMC_CS_IDLE_dfx_cs4_idle_END     (4)
#define SOC_MMBUF_SMC_CS_IDLE_dfx_cs5_idle_START   (5)
#define SOC_MMBUF_SMC_CS_IDLE_dfx_cs5_idle_END     (5)
#define SOC_MMBUF_SMC_CS_IDLE_dfx_cs6_idle_START   (6)
#define SOC_MMBUF_SMC_CS_IDLE_dfx_cs6_idle_END     (6)
#define SOC_MMBUF_SMC_CS_IDLE_dfx_cs7_idle_START   (7)
#define SOC_MMBUF_SMC_CS_IDLE_dfx_cs7_idle_END     (7)
#define SOC_MMBUF_SMC_CS_IDLE_dfx_cs8_idle_START   (8)
#define SOC_MMBUF_SMC_CS_IDLE_dfx_cs8_idle_END     (8)
#define SOC_MMBUF_SMC_CS_IDLE_dfx_cs9_idle_START   (9)
#define SOC_MMBUF_SMC_CS_IDLE_dfx_cs9_idle_END     (9)
#define SOC_MMBUF_SMC_CS_IDLE_dfx_cs10_idle_START  (10)
#define SOC_MMBUF_SMC_CS_IDLE_dfx_cs10_idle_END    (10)
#define SOC_MMBUF_SMC_CS_IDLE_dfx_cs11_idle_START  (11)
#define SOC_MMBUF_SMC_CS_IDLE_dfx_cs11_idle_END    (11)
#define SOC_MMBUF_SMC_CS_IDLE_dfx_cs12_idle_START  (12)
#define SOC_MMBUF_SMC_CS_IDLE_dfx_cs12_idle_END    (12)
#define SOC_MMBUF_SMC_CS_IDLE_dfx_cs13_idle_START  (13)
#define SOC_MMBUF_SMC_CS_IDLE_dfx_cs13_idle_END    (13)
#define SOC_MMBUF_SMC_CS_IDLE_dfx_cs14_idle_START  (14)
#define SOC_MMBUF_SMC_CS_IDLE_dfx_cs14_idle_END    (14)
#define SOC_MMBUF_SMC_CS_IDLE_dfx_cs15_idle_START  (15)
#define SOC_MMBUF_SMC_CS_IDLE_dfx_cs15_idle_END    (15)


/*****************************************************************************
 结构名    : SOC_MMBUF_SMC_DFX_BFIFO_CNT0_UNION
 结构说明  : SMC_DFX_BFIFO_CNT0 寄存器结构定义。地址偏移量:0x0038，初值:0x00000000，宽度:32
 寄存器说明: AXI slave口中写响应FIFO中存储的AXI写响应命令个数。
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  dfx_cs0_bfifo_cnt  : 2;  /* bit[0-1]  : 第1个AXI slave口中写响应FIFO中存储的AXI写响应命令个数。 */
        unsigned int  dfx_cs1_bfifo_cnt  : 2;  /* bit[2-3]  : 第2个AXI slave口中写响应FIFO中存储的AXI写响应命令个数。 */
        unsigned int  dfx_cs2_bfifo_cnt  : 2;  /* bit[4-5]  : 第3个AXI slave口中写响应FIFO中存储的AXI写响应命令个数。 */
        unsigned int  dfx_cs3_bfifo_cnt  : 2;  /* bit[6-7]  : 第4个AXI slave口中写响应FIFO中存储的AXI写响应命令个数。 */
        unsigned int  dfx_cs4_bfifo_cnt  : 2;  /* bit[8-9]  : 第5个AXI slave口中写响应FIFO中存储的AXI写响应命令个数。 */
        unsigned int  dfx_cs5_bfifo_cnt  : 2;  /* bit[10-11]: 第6个AXI slave口中写响应FIFO中存储的AXI写响应命令个数。 */
        unsigned int  dfx_cs6_bfifo_cnt  : 2;  /* bit[12-13]: 第7个AXI slave口中写响应FIFO中存储的AXI写响应命令个数。 */
        unsigned int  dfx_cs7_bfifo_cnt  : 2;  /* bit[14-15]: 第8个AXI slave口中写响应FIFO中存储的AXI写响应命令个数。 */
        unsigned int  dfx_cs8_bfifo_cnt  : 2;  /* bit[16-17]: 第9个AXI slave口中写响应FIFO中存储的AXI写响应命令个数。 */
        unsigned int  dfx_cs9_bfifo_cnt  : 2;  /* bit[18-19]: 第10个AXI slave口中写响应FIFO中存储的AXI写响应命令个数。 */
        unsigned int  dfx_cs10_bfifo_cnt : 2;  /* bit[20-21]: 第11个AXI slave口中写响应FIFO中存储的AXI写响应命令个数。 */
        unsigned int  dfx_cs11_bfifo_cnt : 2;  /* bit[22-23]: 第12个AXI slave口中写响应FIFO中存储的AXI写响应命令个数。 */
        unsigned int  dfx_cs12_bfifo_cnt : 2;  /* bit[24-25]: 第13个AXI slave口中写响应FIFO中存储的AXI写响应命令个数。 */
        unsigned int  dfx_cs13_bfifo_cnt : 2;  /* bit[26-27]: 第14个AXI slave口中写响应FIFO中存储的AXI写响应命令个数。 */
        unsigned int  dfx_cs14_bfifo_cnt : 2;  /* bit[28-29]: 第15个AXI slave口中写响应FIFO中存储的AXI写响应命令个数。 */
        unsigned int  dfx_cs15_bfifo_cnt : 2;  /* bit[30-31]: 第16个AXI slave口中写响应FIFO中存储的AXI写响应命令个数。 */
    } reg;
} SOC_MMBUF_SMC_DFX_BFIFO_CNT0_UNION;
#endif
#define SOC_MMBUF_SMC_DFX_BFIFO_CNT0_dfx_cs0_bfifo_cnt_START   (0)
#define SOC_MMBUF_SMC_DFX_BFIFO_CNT0_dfx_cs0_bfifo_cnt_END     (1)
#define SOC_MMBUF_SMC_DFX_BFIFO_CNT0_dfx_cs1_bfifo_cnt_START   (2)
#define SOC_MMBUF_SMC_DFX_BFIFO_CNT0_dfx_cs1_bfifo_cnt_END     (3)
#define SOC_MMBUF_SMC_DFX_BFIFO_CNT0_dfx_cs2_bfifo_cnt_START   (4)
#define SOC_MMBUF_SMC_DFX_BFIFO_CNT0_dfx_cs2_bfifo_cnt_END     (5)
#define SOC_MMBUF_SMC_DFX_BFIFO_CNT0_dfx_cs3_bfifo_cnt_START   (6)
#define SOC_MMBUF_SMC_DFX_BFIFO_CNT0_dfx_cs3_bfifo_cnt_END     (7)
#define SOC_MMBUF_SMC_DFX_BFIFO_CNT0_dfx_cs4_bfifo_cnt_START   (8)
#define SOC_MMBUF_SMC_DFX_BFIFO_CNT0_dfx_cs4_bfifo_cnt_END     (9)
#define SOC_MMBUF_SMC_DFX_BFIFO_CNT0_dfx_cs5_bfifo_cnt_START   (10)
#define SOC_MMBUF_SMC_DFX_BFIFO_CNT0_dfx_cs5_bfifo_cnt_END     (11)
#define SOC_MMBUF_SMC_DFX_BFIFO_CNT0_dfx_cs6_bfifo_cnt_START   (12)
#define SOC_MMBUF_SMC_DFX_BFIFO_CNT0_dfx_cs6_bfifo_cnt_END     (13)
#define SOC_MMBUF_SMC_DFX_BFIFO_CNT0_dfx_cs7_bfifo_cnt_START   (14)
#define SOC_MMBUF_SMC_DFX_BFIFO_CNT0_dfx_cs7_bfifo_cnt_END     (15)
#define SOC_MMBUF_SMC_DFX_BFIFO_CNT0_dfx_cs8_bfifo_cnt_START   (16)
#define SOC_MMBUF_SMC_DFX_BFIFO_CNT0_dfx_cs8_bfifo_cnt_END     (17)
#define SOC_MMBUF_SMC_DFX_BFIFO_CNT0_dfx_cs9_bfifo_cnt_START   (18)
#define SOC_MMBUF_SMC_DFX_BFIFO_CNT0_dfx_cs9_bfifo_cnt_END     (19)
#define SOC_MMBUF_SMC_DFX_BFIFO_CNT0_dfx_cs10_bfifo_cnt_START  (20)
#define SOC_MMBUF_SMC_DFX_BFIFO_CNT0_dfx_cs10_bfifo_cnt_END    (21)
#define SOC_MMBUF_SMC_DFX_BFIFO_CNT0_dfx_cs11_bfifo_cnt_START  (22)
#define SOC_MMBUF_SMC_DFX_BFIFO_CNT0_dfx_cs11_bfifo_cnt_END    (23)
#define SOC_MMBUF_SMC_DFX_BFIFO_CNT0_dfx_cs12_bfifo_cnt_START  (24)
#define SOC_MMBUF_SMC_DFX_BFIFO_CNT0_dfx_cs12_bfifo_cnt_END    (25)
#define SOC_MMBUF_SMC_DFX_BFIFO_CNT0_dfx_cs13_bfifo_cnt_START  (26)
#define SOC_MMBUF_SMC_DFX_BFIFO_CNT0_dfx_cs13_bfifo_cnt_END    (27)
#define SOC_MMBUF_SMC_DFX_BFIFO_CNT0_dfx_cs14_bfifo_cnt_START  (28)
#define SOC_MMBUF_SMC_DFX_BFIFO_CNT0_dfx_cs14_bfifo_cnt_END    (29)
#define SOC_MMBUF_SMC_DFX_BFIFO_CNT0_dfx_cs15_bfifo_cnt_START  (30)
#define SOC_MMBUF_SMC_DFX_BFIFO_CNT0_dfx_cs15_bfifo_cnt_END    (31)


/*****************************************************************************
 结构名    : SOC_MMBUF_SMC_DFX_RDFIFO_CNT1_UNION
 结构说明  : SMC_DFX_RDFIFO_CNT1 寄存器结构定义。地址偏移量:0x003C，初值:0x00000000，宽度:32
 寄存器说明: AXI slave口中读数据FIFO中存储的AXI读数据个数。
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  dfx_cs0_rdfifo_cnt  : 2;  /* bit[0-1]  : 第1个AXI slave口中读数据FIFO中存储的AXI读数据个数。 */
        unsigned int  dfx_cs1_rdfifo_cnt  : 2;  /* bit[2-3]  : 第2个AXI slave口中读数据FIFO中存储的AXI读数据个数。 */
        unsigned int  dfx_cs2_rdfifo_cnt  : 2;  /* bit[4-5]  : 第3个AXI slave口中读数据FIFO中存储的AXI读数据个数。 */
        unsigned int  dfx_cs3_rdfifo_cnt  : 2;  /* bit[6-7]  : 第4个AXI slave口中读数据FIFO中存储的AXI读数据个数。 */
        unsigned int  dfx_cs4_rdfifo_cnt  : 2;  /* bit[8-9]  : 第5个AXI slave口中读数据FIFO中存储的AXI读数据个数。 */
        unsigned int  dfx_cs5_rdfifo_cnt  : 2;  /* bit[10-11]: 第6个AXI slave口中读数据FIFO中存储的AXI读数据个数。 */
        unsigned int  dfx_cs6_rdfifo_cnt  : 2;  /* bit[12-13]: 第7个AXI slave口中读数据FIFO中存储的AXI读数据个数。 */
        unsigned int  dfx_cs7_rdfifo_cnt  : 2;  /* bit[14-15]: 第8个AXI slave口中读数据FIFO中存储的AXI读数据个数。 */
        unsigned int  dfx_cs8_rdfifo_cnt  : 2;  /* bit[16-17]: 第9个AXI slave口中读数据FIFO中存储的AXI读数据个数。 */
        unsigned int  dfx_cs9_rdfifo_cnt  : 2;  /* bit[18-19]: 第10个AXI slave口中读数据FIFO中存储的AXI读数据个数。 */
        unsigned int  dfx_cs10_rdfifo_cnt : 2;  /* bit[20-21]: 第11个AXI slave口中读数据FIFO中存储的AXI读数据个数。 */
        unsigned int  dfx_cs11_rdfifo_cnt : 2;  /* bit[22-23]: 第12个AXI slave口中读数据FIFO中存储的AXI读数据个数。 */
        unsigned int  dfx_cs12_rdfifo_cnt : 2;  /* bit[24-25]: 第13个AXI slave口中读数据FIFO中存储的AXI读数据个数。 */
        unsigned int  dfx_cs13_rdfifo_cnt : 2;  /* bit[26-27]: 第14个AXI slave口中读数据FIFO中存储的AXI读数据个数。 */
        unsigned int  dfx_cs14_rdfifo_cnt : 2;  /* bit[28-29]: 第15个AXI slave口中读数据FIFO中存储的AXI读数据个数。 */
        unsigned int  dfx_cs15_rdfifo_cnt : 2;  /* bit[30-31]: 第16个AXI slave口中读数据FIFO中存储的AXI读数据个数。 */
    } reg;
} SOC_MMBUF_SMC_DFX_RDFIFO_CNT1_UNION;
#endif
#define SOC_MMBUF_SMC_DFX_RDFIFO_CNT1_dfx_cs0_rdfifo_cnt_START   (0)
#define SOC_MMBUF_SMC_DFX_RDFIFO_CNT1_dfx_cs0_rdfifo_cnt_END     (1)
#define SOC_MMBUF_SMC_DFX_RDFIFO_CNT1_dfx_cs1_rdfifo_cnt_START   (2)
#define SOC_MMBUF_SMC_DFX_RDFIFO_CNT1_dfx_cs1_rdfifo_cnt_END     (3)
#define SOC_MMBUF_SMC_DFX_RDFIFO_CNT1_dfx_cs2_rdfifo_cnt_START   (4)
#define SOC_MMBUF_SMC_DFX_RDFIFO_CNT1_dfx_cs2_rdfifo_cnt_END     (5)
#define SOC_MMBUF_SMC_DFX_RDFIFO_CNT1_dfx_cs3_rdfifo_cnt_START   (6)
#define SOC_MMBUF_SMC_DFX_RDFIFO_CNT1_dfx_cs3_rdfifo_cnt_END     (7)
#define SOC_MMBUF_SMC_DFX_RDFIFO_CNT1_dfx_cs4_rdfifo_cnt_START   (8)
#define SOC_MMBUF_SMC_DFX_RDFIFO_CNT1_dfx_cs4_rdfifo_cnt_END     (9)
#define SOC_MMBUF_SMC_DFX_RDFIFO_CNT1_dfx_cs5_rdfifo_cnt_START   (10)
#define SOC_MMBUF_SMC_DFX_RDFIFO_CNT1_dfx_cs5_rdfifo_cnt_END     (11)
#define SOC_MMBUF_SMC_DFX_RDFIFO_CNT1_dfx_cs6_rdfifo_cnt_START   (12)
#define SOC_MMBUF_SMC_DFX_RDFIFO_CNT1_dfx_cs6_rdfifo_cnt_END     (13)
#define SOC_MMBUF_SMC_DFX_RDFIFO_CNT1_dfx_cs7_rdfifo_cnt_START   (14)
#define SOC_MMBUF_SMC_DFX_RDFIFO_CNT1_dfx_cs7_rdfifo_cnt_END     (15)
#define SOC_MMBUF_SMC_DFX_RDFIFO_CNT1_dfx_cs8_rdfifo_cnt_START   (16)
#define SOC_MMBUF_SMC_DFX_RDFIFO_CNT1_dfx_cs8_rdfifo_cnt_END     (17)
#define SOC_MMBUF_SMC_DFX_RDFIFO_CNT1_dfx_cs9_rdfifo_cnt_START   (18)
#define SOC_MMBUF_SMC_DFX_RDFIFO_CNT1_dfx_cs9_rdfifo_cnt_END     (19)
#define SOC_MMBUF_SMC_DFX_RDFIFO_CNT1_dfx_cs10_rdfifo_cnt_START  (20)
#define SOC_MMBUF_SMC_DFX_RDFIFO_CNT1_dfx_cs10_rdfifo_cnt_END    (21)
#define SOC_MMBUF_SMC_DFX_RDFIFO_CNT1_dfx_cs11_rdfifo_cnt_START  (22)
#define SOC_MMBUF_SMC_DFX_RDFIFO_CNT1_dfx_cs11_rdfifo_cnt_END    (23)
#define SOC_MMBUF_SMC_DFX_RDFIFO_CNT1_dfx_cs12_rdfifo_cnt_START  (24)
#define SOC_MMBUF_SMC_DFX_RDFIFO_CNT1_dfx_cs12_rdfifo_cnt_END    (25)
#define SOC_MMBUF_SMC_DFX_RDFIFO_CNT1_dfx_cs13_rdfifo_cnt_START  (26)
#define SOC_MMBUF_SMC_DFX_RDFIFO_CNT1_dfx_cs13_rdfifo_cnt_END    (27)
#define SOC_MMBUF_SMC_DFX_RDFIFO_CNT1_dfx_cs14_rdfifo_cnt_START  (28)
#define SOC_MMBUF_SMC_DFX_RDFIFO_CNT1_dfx_cs14_rdfifo_cnt_END    (29)
#define SOC_MMBUF_SMC_DFX_RDFIFO_CNT1_dfx_cs15_rdfifo_cnt_START  (30)
#define SOC_MMBUF_SMC_DFX_RDFIFO_CNT1_dfx_cs15_rdfifo_cnt_END    (31)


/*****************************************************************************
 结构名    : SOC_MMBUF_SP_SRAM_STATE0_UNION
 结构说明  : SP_SRAM_STATE0 寄存器结构定义。地址偏移量:0x0040，初值:0x0000，宽度:32
 寄存器说明: 交织bank的sram memory的状态。
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  st_int0_sram0 : 2;  /* bit[0-1]  : 交织bank0的sram0 memory的状态。
                                                         2'b00: normal state
                                                         2'b01: in light sleep state
                                                         2'b10: in deep sleep state
                                                         2'b11: in shut down state */
        unsigned int  st_int0_sram1 : 2;  /* bit[2-3]  : 交织bank0的sram1 memory的状态。
                                                         2'b00: normal state
                                                         2'b01: in light sleep state
                                                         2'b10: in deep sleep state
                                                         2'b11: in shut down state */
        unsigned int  st_int1_sram0 : 2;  /* bit[4-5]  : 交织bank1的sram0 memory的状态。
                                                         2'b00: normal state
                                                         2'b01: in light sleep state
                                                         2'b10: in deep sleep state
                                                         2'b11: in shut down state */
        unsigned int  st_int1_sram1 : 2;  /* bit[6-7]  : 交织bank1的sram1 memory的状态。
                                                         2'b00: normal state
                                                         2'b01: in light sleep state
                                                         2'b10: in deep sleep state
                                                         2'b11: in shut down state */
        unsigned int  st_int2_sram0 : 2;  /* bit[8-9]  : 交织bank2的sram0 memory的状态。
                                                         2'b00: normal state
                                                         2'b01: in light sleep state
                                                         2'b10: in deep sleep state
                                                         2'b11: in shut down state */
        unsigned int  st_int2_sram1 : 2;  /* bit[10-11]: 交织bank2的sram1 memory的状态。
                                                         2'b00: normal state
                                                         2'b01: in light sleep state
                                                         2'b10: in deep sleep state
                                                         2'b11: in shut down state */
        unsigned int  st_int3_sram0 : 2;  /* bit[12-13]: 交织bank3的sram0 memory的状态。
                                                         2'b00: normal state
                                                         2'b01: in light sleep state
                                                         2'b10: in deep sleep state
                                                         2'b11: in shut down state */
        unsigned int  st_int3_sram1 : 2;  /* bit[14-15]: 交织bank3的sram1 memory的状态。
                                                         2'b00: normal state
                                                         2'b01: in light sleep state
                                                         2'b10: in deep sleep state
                                                         2'b11: in shut down state */
        unsigned int  st_int4_sram0 : 2;  /* bit[16-17]: 交织bank4的sram0 memory的状态。
                                                         2'b00: normal state
                                                         2'b01: in light sleep state
                                                         2'b10: in deep sleep state
                                                         2'b11: in shut down state */
        unsigned int  st_int4_sram1 : 2;  /* bit[18-19]: 交织bank4的sram1 memory的状态。
                                                         2'b00: normal state
                                                         2'b01: in light sleep state
                                                         2'b10: in deep sleep state
                                                         2'b11: in shut down state */
        unsigned int  st_int5_sram0 : 2;  /* bit[20-21]: 交织bank5的sram0 memory的状态。
                                                         2'b00: normal state
                                                         2'b01: in light sleep state
                                                         2'b10: in deep sleep state
                                                         2'b11: in shut down state */
        unsigned int  st_int5_sram1 : 2;  /* bit[22-23]: 交织bank5的sram1 memory的状态。
                                                         2'b00: normal state
                                                         2'b01: in light sleep state
                                                         2'b10: in deep sleep state
                                                         2'b11: in shut down state */
        unsigned int  st_int6_sram0 : 2;  /* bit[24-25]: 交织bank6的sram0 memory的状态。
                                                         2'b00: normal state
                                                         2'b01: in light sleep state
                                                         2'b10: in deep sleep state
                                                         2'b11: in shut down state */
        unsigned int  st_int6_sram1 : 2;  /* bit[26-27]: 交织bank6的sram1 memory的状态。
                                                         2'b00: normal state
                                                         2'b01: in light sleep state
                                                         2'b10: in deep sleep state
                                                         2'b11: in shut down state */
        unsigned int  st_int7_sram0 : 2;  /* bit[28-29]: 交织bank7的sram0 memory的状态。
                                                         2'b00: normal state
                                                         2'b01: in light sleep state
                                                         2'b10: in deep sleep state
                                                         2'b11: in shut down state */
        unsigned int  st_int7_sram1 : 2;  /* bit[30-31]: 交织bank7的sram1 memory的状态。
                                                         2'b00: normal state
                                                         2'b01: in light sleep state
                                                         2'b10: in deep sleep state
                                                         2'b11: in shut down state */
    } reg;
} SOC_MMBUF_SP_SRAM_STATE0_UNION;
#endif
#define SOC_MMBUF_SP_SRAM_STATE0_st_int0_sram0_START  (0)
#define SOC_MMBUF_SP_SRAM_STATE0_st_int0_sram0_END    (1)
#define SOC_MMBUF_SP_SRAM_STATE0_st_int0_sram1_START  (2)
#define SOC_MMBUF_SP_SRAM_STATE0_st_int0_sram1_END    (3)
#define SOC_MMBUF_SP_SRAM_STATE0_st_int1_sram0_START  (4)
#define SOC_MMBUF_SP_SRAM_STATE0_st_int1_sram0_END    (5)
#define SOC_MMBUF_SP_SRAM_STATE0_st_int1_sram1_START  (6)
#define SOC_MMBUF_SP_SRAM_STATE0_st_int1_sram1_END    (7)
#define SOC_MMBUF_SP_SRAM_STATE0_st_int2_sram0_START  (8)
#define SOC_MMBUF_SP_SRAM_STATE0_st_int2_sram0_END    (9)
#define SOC_MMBUF_SP_SRAM_STATE0_st_int2_sram1_START  (10)
#define SOC_MMBUF_SP_SRAM_STATE0_st_int2_sram1_END    (11)
#define SOC_MMBUF_SP_SRAM_STATE0_st_int3_sram0_START  (12)
#define SOC_MMBUF_SP_SRAM_STATE0_st_int3_sram0_END    (13)
#define SOC_MMBUF_SP_SRAM_STATE0_st_int3_sram1_START  (14)
#define SOC_MMBUF_SP_SRAM_STATE0_st_int3_sram1_END    (15)
#define SOC_MMBUF_SP_SRAM_STATE0_st_int4_sram0_START  (16)
#define SOC_MMBUF_SP_SRAM_STATE0_st_int4_sram0_END    (17)
#define SOC_MMBUF_SP_SRAM_STATE0_st_int4_sram1_START  (18)
#define SOC_MMBUF_SP_SRAM_STATE0_st_int4_sram1_END    (19)
#define SOC_MMBUF_SP_SRAM_STATE0_st_int5_sram0_START  (20)
#define SOC_MMBUF_SP_SRAM_STATE0_st_int5_sram0_END    (21)
#define SOC_MMBUF_SP_SRAM_STATE0_st_int5_sram1_START  (22)
#define SOC_MMBUF_SP_SRAM_STATE0_st_int5_sram1_END    (23)
#define SOC_MMBUF_SP_SRAM_STATE0_st_int6_sram0_START  (24)
#define SOC_MMBUF_SP_SRAM_STATE0_st_int6_sram0_END    (25)
#define SOC_MMBUF_SP_SRAM_STATE0_st_int6_sram1_START  (26)
#define SOC_MMBUF_SP_SRAM_STATE0_st_int6_sram1_END    (27)
#define SOC_MMBUF_SP_SRAM_STATE0_st_int7_sram0_START  (28)
#define SOC_MMBUF_SP_SRAM_STATE0_st_int7_sram0_END    (29)
#define SOC_MMBUF_SP_SRAM_STATE0_st_int7_sram1_START  (30)
#define SOC_MMBUF_SP_SRAM_STATE0_st_int7_sram1_END    (31)


/*****************************************************************************
 结构名    : SOC_MMBUF_SP_SRAM_STATE1_UNION
 结构说明  : SP_SRAM_STATE1 寄存器结构定义。地址偏移量:0x0044，初值:0x0000，宽度:32
 寄存器说明: 交织bank的sram memory的状态。
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  st_int8_sram0  : 2;  /* bit[0-1]  : 交织bank8的sram0 memory的状态。
                                                          2'b00: normal state
                                                          2'b01: in light sleep state
                                                          2'b10: in deep sleep state
                                                          2'b11: in shut down state */
        unsigned int  st_int8_sram1  : 2;  /* bit[2-3]  : 交织bank8的sram1 memory的状态。
                                                          2'b00: normal state
                                                          2'b01: in light sleep state
                                                          2'b10: in deep sleep state
                                                          2'b11: in shut down state */
        unsigned int  st_int9_sram0  : 2;  /* bit[4-5]  : 交织bank9的sram0 memory的状态。
                                                          2'b00: normal state
                                                          2'b01: in light sleep state
                                                          2'b10: in deep sleep state
                                                          2'b11: in shut down state */
        unsigned int  st_int9_sram1  : 2;  /* bit[6-7]  : 交织bank9的sram1 memory的状态。
                                                          2'b00: normal state
                                                          2'b01: in light sleep state
                                                          2'b10: in deep sleep state
                                                          2'b11: in shut down state */
        unsigned int  st_int10_sram0 : 2;  /* bit[8-9]  : 交织bank10的sram0 memory的状态。
                                                          2'b00: normal state
                                                          2'b01: in light sleep state
                                                          2'b10: in deep sleep state
                                                          2'b11: in shut down state */
        unsigned int  st_int10_sram1 : 2;  /* bit[10-11]: 交织bank10的sram1 memory的状态。
                                                          2'b00: normal state
                                                          2'b01: in light sleep state
                                                          2'b10: in deep sleep state
                                                          2'b11: in shut down state */
        unsigned int  st_int11_sram0 : 2;  /* bit[12-13]: 交织bank11的sram0 memory的状态。
                                                          2'b00: normal state
                                                          2'b01: in light sleep state
                                                          2'b10: in deep sleep state
                                                          2'b11: in shut down state */
        unsigned int  st_int11_sram1 : 2;  /* bit[14-15]: 交织bank11的sram1 memory的状态。
                                                          2'b00: normal state
                                                          2'b01: in light sleep state
                                                          2'b10: in deep sleep state
                                                          2'b11: in shut down state */
        unsigned int  st_int12_sram0 : 2;  /* bit[16-17]: 交织bank12的sram0 memory的状态。
                                                          2'b00: normal state
                                                          2'b01: in light sleep state
                                                          2'b10: in deep sleep state
                                                          2'b11: in shut down state */
        unsigned int  st_int12_sram1 : 2;  /* bit[18-19]: 交织bank12的sram1 memory的状态。
                                                          2'b00: normal state
                                                          2'b01: in light sleep state
                                                          2'b10: in deep sleep state
                                                          2'b11: in shut down state */
        unsigned int  st_int13_sram0 : 2;  /* bit[20-21]: 交织bank13的sram0 memory的状态。
                                                          2'b00: normal state
                                                          2'b01: in light sleep state
                                                          2'b10: in deep sleep state
                                                          2'b11: in shut down state */
        unsigned int  st_int13_sram1 : 2;  /* bit[22-23]: 交织bank13的sram1 memory的状态。
                                                          2'b00: normal state
                                                          2'b01: in light sleep state
                                                          2'b10: in deep sleep state
                                                          2'b11: in shut down state */
        unsigned int  st_int14_sram0 : 2;  /* bit[24-25]: 交织bank14的sram0 memory的状态。
                                                          2'b00: normal state
                                                          2'b01: in light sleep state
                                                          2'b10: in deep sleep state
                                                          2'b11: in shut down state */
        unsigned int  st_int14_sram1 : 2;  /* bit[26-27]: 交织bank14的sram1 memory的状态。
                                                          2'b00: normal state
                                                          2'b01: in light sleep state
                                                          2'b10: in deep sleep state
                                                          2'b11: in shut down state */
        unsigned int  st_int15_sram0 : 2;  /* bit[28-29]: 交织bank15的sram0 memory的状态。
                                                          2'b00: normal state
                                                          2'b01: in light sleep state
                                                          2'b10: in deep sleep state
                                                          2'b11: in shut down state */
        unsigned int  st_int15_sram1 : 2;  /* bit[30-31]: 交织bank15的sram1 memory的状态。
                                                          2'b00: normal state
                                                          2'b01: in light sleep state
                                                          2'b10: in deep sleep state
                                                          2'b11: in shut down state */
    } reg;
} SOC_MMBUF_SP_SRAM_STATE1_UNION;
#endif
#define SOC_MMBUF_SP_SRAM_STATE1_st_int8_sram0_START   (0)
#define SOC_MMBUF_SP_SRAM_STATE1_st_int8_sram0_END     (1)
#define SOC_MMBUF_SP_SRAM_STATE1_st_int8_sram1_START   (2)
#define SOC_MMBUF_SP_SRAM_STATE1_st_int8_sram1_END     (3)
#define SOC_MMBUF_SP_SRAM_STATE1_st_int9_sram0_START   (4)
#define SOC_MMBUF_SP_SRAM_STATE1_st_int9_sram0_END     (5)
#define SOC_MMBUF_SP_SRAM_STATE1_st_int9_sram1_START   (6)
#define SOC_MMBUF_SP_SRAM_STATE1_st_int9_sram1_END     (7)
#define SOC_MMBUF_SP_SRAM_STATE1_st_int10_sram0_START  (8)
#define SOC_MMBUF_SP_SRAM_STATE1_st_int10_sram0_END    (9)
#define SOC_MMBUF_SP_SRAM_STATE1_st_int10_sram1_START  (10)
#define SOC_MMBUF_SP_SRAM_STATE1_st_int10_sram1_END    (11)
#define SOC_MMBUF_SP_SRAM_STATE1_st_int11_sram0_START  (12)
#define SOC_MMBUF_SP_SRAM_STATE1_st_int11_sram0_END    (13)
#define SOC_MMBUF_SP_SRAM_STATE1_st_int11_sram1_START  (14)
#define SOC_MMBUF_SP_SRAM_STATE1_st_int11_sram1_END    (15)
#define SOC_MMBUF_SP_SRAM_STATE1_st_int12_sram0_START  (16)
#define SOC_MMBUF_SP_SRAM_STATE1_st_int12_sram0_END    (17)
#define SOC_MMBUF_SP_SRAM_STATE1_st_int12_sram1_START  (18)
#define SOC_MMBUF_SP_SRAM_STATE1_st_int12_sram1_END    (19)
#define SOC_MMBUF_SP_SRAM_STATE1_st_int13_sram0_START  (20)
#define SOC_MMBUF_SP_SRAM_STATE1_st_int13_sram0_END    (21)
#define SOC_MMBUF_SP_SRAM_STATE1_st_int13_sram1_START  (22)
#define SOC_MMBUF_SP_SRAM_STATE1_st_int13_sram1_END    (23)
#define SOC_MMBUF_SP_SRAM_STATE1_st_int14_sram0_START  (24)
#define SOC_MMBUF_SP_SRAM_STATE1_st_int14_sram0_END    (25)
#define SOC_MMBUF_SP_SRAM_STATE1_st_int14_sram1_START  (26)
#define SOC_MMBUF_SP_SRAM_STATE1_st_int14_sram1_END    (27)
#define SOC_MMBUF_SP_SRAM_STATE1_st_int15_sram0_START  (28)
#define SOC_MMBUF_SP_SRAM_STATE1_st_int15_sram0_END    (29)
#define SOC_MMBUF_SP_SRAM_STATE1_st_int15_sram1_START  (30)
#define SOC_MMBUF_SP_SRAM_STATE1_st_int15_sram1_END    (31)






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

#endif /* end of soc_mmbuf_interface.h */
