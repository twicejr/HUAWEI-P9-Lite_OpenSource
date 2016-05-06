/******************************************************************************

                 版权所有 (C), 2001-2014, 华为技术有限公司

 ******************************************************************************
  文 件 名   : bbp_glb_on_interface.h
  版 本 号   : 初稿
  作    者   : Excel2Code
  生成日期   : 2014-10-30 15:33:44
  最近修改   :
  功能描述   : 接口头文件
  函数列表   :
  修改历史   :
  1.日    期   : 2014年10月30日
    作    者   : p00277817
    修改内容   : 从《K3V5 MODEM寄存器手册_GLB_ON.xml》自动生成

******************************************************************************/

/*****************************************************************************
  1 其他头文件包含
*****************************************************************************/

#ifndef __BBP_GLB_ON_INTERFACE_H__
#define __BBP_GLB_ON_INTERFACE_H__

#ifdef __cplusplus
    #if __cplusplus
        extern "C" {
    #endif
#endif



/*****************************************************************************
  2 宏定义
*****************************************************************************/

/***======================================================================***
                     (1/1) register_define_bbp_on_glb
 ***======================================================================***/
/* 寄存器说明：
 bit[31:2]   保留
 bit[1:0]    BBP工作模式指示。0，W；1，TDS；2，1x；3，EV-DO。
   UNION结构:  GLB_ON_MODE_SEL_UNION */
#define GLB_ON_MODE_SEL_ADDR                          (SOC_BBP_GLB_ON_BASE_ADDR + 0x1A00)

/* 寄存器说明：
 bit[31:1]   保留
 bit[0]      软件配置的RFIC2复位信号，低有效。0，复位；1，解复位。
             上电初始化配置为0，根据RFIC手册要求，维持一段时间后配置为1。
             该寄存器仅供K3V5使用。
   UNION结构:  GLB_ON_RFIC2_RSTN_UNION */
#define GLB_ON_RFIC2_RSTN_ADDR                        (SOC_BBP_GLB_ON_BASE_ADDR + 0x1A0C)

/* 寄存器说明：
 bit[31:1]   保留
 bit[0]      软件配置的RFIC0复位信号，低有效。0，复位；1，解复位。
             上电初始化配置为0，根据RFIC手册要求，维持一段时间后配置为1。
             该寄存器从CTU接口0x002C移植过来。
   UNION结构:  GLB_ON_RFIC0_RSTN_UNION */
#define GLB_ON_RFIC0_RSTN_ADDR                        (SOC_BBP_GLB_ON_BASE_ADDR + 0x1A10)

/* 寄存器说明：
 bit[31:1]   保留
 bit[0]      软件配置的RFIC1复位信号，低有效。0，复位；1，解复位。
             上电初始化配置为0，根据RFIC手册要求，维持一段时间后配置为1。
             该寄存器从CTU接口0x032C移植过来。
   UNION结构:  GLB_ON_RFIC1_RSTN_UNION */
#define GLB_ON_RFIC1_RSTN_ADDR                        (SOC_BBP_GLB_ON_BASE_ADDR + 0x1A14)

/* 寄存器说明：
 bit[31:1]   保留
 bit[0]      32k公共定时器的校准参数更新使能信号，脉冲信号，需要调整校准周期或校准方向时，应先配置cpu_adjust_direction和cpu_adjust_period，再配置此信号
   UNION结构:  GLB_ON_COMM_TIMER_UPDATE_EN_UNION */
#define GLB_ON_COMM_TIMER_UPDATE_EN_ADDR              (SOC_BBP_GLB_ON_BASE_ADDR + 0x1A18)

/* 寄存器说明：
 bit[31]     32k公共定时器的时钟校准方向，1表示每cpu_adjust_period个时钟周期，加速1个周期
             0 表示每cpu_adjust_period个时钟周期，减速1个周期
 bit[30]     32k公共定时器的校准使能，该信号为1时，校准功能生效
 bit[29:24]  保留
 bit[23:0]   32k公共定时器的时钟校准周期，表示每cpu_adjust_period个时钟周期，加速或者减速1个周期
   UNION结构:  GLB_ON_COMM_TIMER_UPDATE_PARA_UNION */
#define GLB_ON_COMM_TIMER_UPDATE_PARA_ADDR            (SOC_BBP_GLB_ON_BASE_ADDR + 0x1A1C)

/* 寄存器说明：
 bit[31:1]   保留
 bit[0]      32k公共定时器的使能信号，需要使用公共定时器时，需配置为1
   UNION结构:  GLB_ON_COMM_TIMER_EN_UNION */
#define GLB_ON_COMM_TIMER_EN_ADDR                     (SOC_BBP_GLB_ON_BASE_ADDR + 0x1A20)

/* 寄存器说明：
   详      述：32k公共定时器上报，测试用。软件如果需要准确的定时，应当通过BBP_COMM提供的锁存定时功能，获取各模及公共定时器的定时信息
   UNION结构 ：无 */
#define GLB_ON_COMM_TIMER_RPT1_ADDR                   (SOC_BBP_GLB_ON_BASE_ADDR + 0x1A24)

/* 寄存器说明：
 bit[31:24]  保留
 bit[23:0]   32K校准定时器上报，测试用
   UNION结构:  GLB_ON_COMM_TIMER_RPT2_UNION */
#define GLB_ON_COMM_TIMER_RPT2_ADDR                   (SOC_BBP_GLB_ON_BASE_ADDR + 0x1A28)

/* 寄存器说明：
 bit[31:2]   保留
 bit[1]      SIM2占用标志，软件用于读写，BBP不使用
 bit[0]      SIM1占用标志，软件用于读写，BBP不使用
   UNION结构:  GLB_ON_DSDS_SIM_FLAG_UNION */
#define GLB_ON_DSDS_SIM_FLAG_ADDR                     (SOC_BBP_GLB_ON_BASE_ADDR + 0x1A2C)

/* 寄存器说明：
 bit[31:1]   保留
 bit[0]      32K公共定时器的定时中断
   UNION结构:  GLB_ON_COMM_32K_INT_UNION */
#define GLB_ON_COMM_32K_INT_ADDR                      (SOC_BBP_GLB_ON_BASE_ADDR + 0x1A30)

/* 寄存器说明：
 bit[31:1]   保留
 bit[0]      32K公共定时器的定时中断屏蔽寄存器，1表示屏蔽，0表示放开中断
   UNION结构:  GLB_ON_COMM_32K_INT_MASK_UNION */
#define GLB_ON_COMM_32K_INT_MASK_ADDR                 (SOC_BBP_GLB_ON_BASE_ADDR + 0x1A34)

/* 寄存器说明：
 bit[31:1]   保留
 bit[0]      32k公共定时器中断使能寄存器。1，表示使能中断；0，表示不使能中断。
   UNION结构:  GLB_ON_COMM_32K_INT_EN_UNION */
#define GLB_ON_COMM_32K_INT_EN_ADDR                   (SOC_BBP_GLB_ON_BASE_ADDR + 0x1A38)

/* 寄存器说明：
 bit[31:1]   保留
 bit[0]      32k公共定时器中断清除寄存器。1，表示清除相应比特位置中断；0，表示不清除相应比特位置的中断。
   UNION结构:  GLB_ON_COMM_32K_INT3_CLR_UNION */
#define GLB_ON_COMM_32K_INT3_CLR_ADDR                 (SOC_BBP_GLB_ON_BASE_ADDR + 0x1A3C)

/* 寄存器说明：
 bit[31:24]  保留
 bit[23:0]   32K时钟域的自定义中断周期，配置范围是0~512s。单位是32k时钟的周期个数。每隔cpu_int_period个32k时钟合周期，产生1次中断。注意：如果期望的调整周期是N，则应配置N-1
   UNION结构:  GLB_ON_COMM_32K_INT_PERIOD_UNION */
#define GLB_ON_COMM_32K_INT_PERIOD_ADDR               (SOC_BBP_GLB_ON_BASE_ADDR + 0x1A40)





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

/***======================================================================***
                     (1/1) register_define_bbp_on_glb
 ***======================================================================***/
/*****************************************************************************
 结构名    : GLB_ON_MODE_SEL_UNION
 结构说明  : MODE_SEL 寄存器结构定义。地址偏移量:0x00，初值:0x00000000，宽度:32
 寄存器说明: 
*****************************************************************************/
typedef union
{
    unsigned long      mode_sel_reg;
    struct
    {
        unsigned long  cpu_mode_sel : 2;  /* bit[0-1] : BBP工作模式指示。0，W；1，TDS；2，1x；3，EV-DO。 */
        unsigned long  reserved     : 30; /* bit[2-31]: 保留 */
    } reg;
} GLB_ON_MODE_SEL_UNION;
#define GLB_ON_MODE_SEL_cpu_mode_sel_START  (0)
#define GLB_ON_MODE_SEL_cpu_mode_sel_END    (1)


/*****************************************************************************
 结构名    : GLB_ON_RFIC2_RSTN_UNION
 结构说明  : RFIC2_RSTN 寄存器结构定义。地址偏移量:0x0C，初值:0x00000000，宽度:32
 寄存器说明: 
*****************************************************************************/
typedef union
{
    unsigned long      rfic2_rstn_reg;
    struct
    {
        unsigned long  rfic2_rstn : 1;  /* bit[0]   : 软件配置的RFIC2复位信号，低有效。0，复位；1，解复位。
                                                      上电初始化配置为0，根据RFIC手册要求，维持一段时间后配置为1。
                                                      该寄存器仅供K3V5使用。 */
        unsigned long  reserved   : 31; /* bit[1-31]: 保留 */
    } reg;
} GLB_ON_RFIC2_RSTN_UNION;
#define GLB_ON_RFIC2_RSTN_rfic2_rstn_START  (0)
#define GLB_ON_RFIC2_RSTN_rfic2_rstn_END    (0)


/*****************************************************************************
 结构名    : GLB_ON_RFIC0_RSTN_UNION
 结构说明  : RFIC0_RSTN 寄存器结构定义。地址偏移量:0x10，初值:0x00000000，宽度:32
 寄存器说明: 
*****************************************************************************/
typedef union
{
    unsigned long      rfic0_rstn_reg;
    struct
    {
        unsigned long  rfic0_rstn : 1;  /* bit[0]   : 软件配置的RFIC0复位信号，低有效。0，复位；1，解复位。
                                                      上电初始化配置为0，根据RFIC手册要求，维持一段时间后配置为1。
                                                      该寄存器从CTU接口0x002C移植过来。 */
        unsigned long  reserved   : 31; /* bit[1-31]: 保留 */
    } reg;
} GLB_ON_RFIC0_RSTN_UNION;
#define GLB_ON_RFIC0_RSTN_rfic0_rstn_START  (0)
#define GLB_ON_RFIC0_RSTN_rfic0_rstn_END    (0)


/*****************************************************************************
 结构名    : GLB_ON_RFIC1_RSTN_UNION
 结构说明  : RFIC1_RSTN 寄存器结构定义。地址偏移量:0x14，初值:0x00000000，宽度:32
 寄存器说明: 
*****************************************************************************/
typedef union
{
    unsigned long      rfic1_rstn_reg;
    struct
    {
        unsigned long  rfic1_rstn : 1;  /* bit[0]   : 软件配置的RFIC1复位信号，低有效。0，复位；1，解复位。
                                                      上电初始化配置为0，根据RFIC手册要求，维持一段时间后配置为1。
                                                      该寄存器从CTU接口0x032C移植过来。 */
        unsigned long  reserved   : 31; /* bit[1-31]: 保留 */
    } reg;
} GLB_ON_RFIC1_RSTN_UNION;
#define GLB_ON_RFIC1_RSTN_rfic1_rstn_START  (0)
#define GLB_ON_RFIC1_RSTN_rfic1_rstn_END    (0)


/*****************************************************************************
 结构名    : GLB_ON_COMM_TIMER_UPDATE_EN_UNION
 结构说明  : COMM_TIMER_UPDATE_EN 寄存器结构定义。地址偏移量:0x18，初值:0x00000000，宽度:32
 寄存器说明: 
*****************************************************************************/
typedef union
{
    unsigned long      comm_timer_update_en_reg;
    struct
    {
        unsigned long  cpu_adj_period_update_en : 1;  /* bit[0]   : 32k公共定时器的校准参数更新使能信号，脉冲信号，需要调整校准周期或校准方向时，应先配置cpu_adjust_direction和cpu_adjust_period，再配置此信号 */
        unsigned long  reserved                 : 31; /* bit[1-31]: 保留 */
    } reg;
} GLB_ON_COMM_TIMER_UPDATE_EN_UNION;
#define GLB_ON_COMM_TIMER_UPDATE_EN_cpu_adj_period_update_en_START  (0)
#define GLB_ON_COMM_TIMER_UPDATE_EN_cpu_adj_period_update_en_END    (0)


/*****************************************************************************
 结构名    : GLB_ON_COMM_TIMER_UPDATE_PARA_UNION
 结构说明  : COMM_TIMER_UPDATE_PARA 寄存器结构定义。地址偏移量:0x1C，初值:0x00000000，宽度:32
 寄存器说明: 
*****************************************************************************/
typedef union
{
    unsigned long      comm_timer_update_para_reg;
    struct
    {
        unsigned long  cpu_adjust_period    : 24; /* bit[0-23] : 32k公共定时器的时钟校准周期，表示每cpu_adjust_period个时钟周期，加速或者减速1个周期 */
        unsigned long  reserved             : 6;  /* bit[24-29]: 保留 */
        unsigned long  cpu_adjust_en        : 1;  /* bit[30]   : 32k公共定时器的校准使能，该信号为1时，校准功能生效 */
        unsigned long  cpu_adjust_direction : 1;  /* bit[31]   : 32k公共定时器的时钟校准方向，1表示每cpu_adjust_period个时钟周期，加速1个周期
                                                                 0 表示每cpu_adjust_period个时钟周期，减速1个周期 */
    } reg;
} GLB_ON_COMM_TIMER_UPDATE_PARA_UNION;
#define GLB_ON_COMM_TIMER_UPDATE_PARA_cpu_adjust_period_START     (0)
#define GLB_ON_COMM_TIMER_UPDATE_PARA_cpu_adjust_period_END       (23)
#define GLB_ON_COMM_TIMER_UPDATE_PARA_cpu_adjust_en_START         (30)
#define GLB_ON_COMM_TIMER_UPDATE_PARA_cpu_adjust_en_END           (30)
#define GLB_ON_COMM_TIMER_UPDATE_PARA_cpu_adjust_direction_START  (31)
#define GLB_ON_COMM_TIMER_UPDATE_PARA_cpu_adjust_direction_END    (31)


/*****************************************************************************
 结构名    : GLB_ON_COMM_TIMER_EN_UNION
 结构说明  : COMM_TIMER_EN 寄存器结构定义。地址偏移量:0x20，初值:0x00000000，宽度:32
 寄存器说明: 
*****************************************************************************/
typedef union
{
    unsigned long      comm_timer_en_reg;
    struct
    {
        unsigned long  cpu_comm_timer_en : 1;  /* bit[0]   : 32k公共定时器的使能信号，需要使用公共定时器时，需配置为1 */
        unsigned long  reserved          : 31; /* bit[1-31]: 保留 */
    } reg;
} GLB_ON_COMM_TIMER_EN_UNION;
#define GLB_ON_COMM_TIMER_EN_cpu_comm_timer_en_START  (0)
#define GLB_ON_COMM_TIMER_EN_cpu_comm_timer_en_END    (0)


/*****************************************************************************
 结构名    : GLB_ON_COMM_TIMER_RPT2_UNION
 结构说明  : COMM_TIMER_RPT2 寄存器结构定义。地址偏移量:0x28，初值:0x00000000，宽度:32
 寄存器说明: 
*****************************************************************************/
typedef union
{
    unsigned long      comm_timer_rpt2_reg;
    struct
    {
        unsigned long  adjust_timer : 24; /* bit[0-23] : 32K校准定时器上报，测试用 */
        unsigned long  reserved     : 8;  /* bit[24-31]: 保留 */
    } reg;
} GLB_ON_COMM_TIMER_RPT2_UNION;
#define GLB_ON_COMM_TIMER_RPT2_adjust_timer_START  (0)
#define GLB_ON_COMM_TIMER_RPT2_adjust_timer_END    (23)


/*****************************************************************************
 结构名    : GLB_ON_DSDS_SIM_FLAG_UNION
 结构说明  : DSDS_SIM_FLAG 寄存器结构定义。地址偏移量:0x2C，初值:0x00000000，宽度:32
 寄存器说明: 
*****************************************************************************/
typedef union
{
    unsigned long      dsds_sim_flag_reg;
    struct
    {
        unsigned long  cpu_sim1_en : 1;  /* bit[0]   : SIM1占用标志，软件用于读写，BBP不使用 */
        unsigned long  cpu_sim2_en : 1;  /* bit[1]   : SIM2占用标志，软件用于读写，BBP不使用 */
        unsigned long  reserved    : 30; /* bit[2-31]: 保留 */
    } reg;
} GLB_ON_DSDS_SIM_FLAG_UNION;
#define GLB_ON_DSDS_SIM_FLAG_cpu_sim1_en_START  (0)
#define GLB_ON_DSDS_SIM_FLAG_cpu_sim1_en_END    (0)
#define GLB_ON_DSDS_SIM_FLAG_cpu_sim2_en_START  (1)
#define GLB_ON_DSDS_SIM_FLAG_cpu_sim2_en_END    (1)


/*****************************************************************************
 结构名    : GLB_ON_COMM_32K_INT_UNION
 结构说明  : COMM_32K_INT 寄存器结构定义。地址偏移量:0x30，初值:0x00000000，宽度:32
 寄存器说明: 
*****************************************************************************/
typedef union
{
    unsigned long      comm_32k_int_reg;
    struct
    {
        unsigned long  comm_32k_int_sta : 1;  /* bit[0]   : 32K公共定时器的定时中断 */
        unsigned long  reserved         : 31; /* bit[1-31]: 保留 */
    } reg;
} GLB_ON_COMM_32K_INT_UNION;
#define GLB_ON_COMM_32K_INT_comm_32k_int_sta_START  (0)
#define GLB_ON_COMM_32K_INT_comm_32k_int_sta_END    (0)


/*****************************************************************************
 结构名    : GLB_ON_COMM_32K_INT_MASK_UNION
 结构说明  : COMM_32K_INT_MASK 寄存器结构定义。地址偏移量:0x34，初值:0x00000000，宽度:32
 寄存器说明: 
*****************************************************************************/
typedef union
{
    unsigned long      comm_32k_int_mask_reg;
    struct
    {
        unsigned long  comm_32k_int_mask : 1;  /* bit[0]   : 32K公共定时器的定时中断屏蔽寄存器，1表示屏蔽，0表示放开中断 */
        unsigned long  reserved          : 31; /* bit[1-31]: 保留 */
    } reg;
} GLB_ON_COMM_32K_INT_MASK_UNION;
#define GLB_ON_COMM_32K_INT_MASK_comm_32k_int_mask_START  (0)
#define GLB_ON_COMM_32K_INT_MASK_comm_32k_int_mask_END    (0)


/*****************************************************************************
 结构名    : GLB_ON_COMM_32K_INT_EN_UNION
 结构说明  : COMM_32K_INT_EN 寄存器结构定义。地址偏移量:0x38，初值:0x00000000，宽度:32
 寄存器说明: 
*****************************************************************************/
typedef union
{
    unsigned long      comm_32k_int_en_reg;
    struct
    {
        unsigned long  comm_32k_int_en : 1;  /* bit[0]   : 32k公共定时器中断使能寄存器。1，表示使能中断；0，表示不使能中断。 */
        unsigned long  reserved        : 31; /* bit[1-31]: 保留 */
    } reg;
} GLB_ON_COMM_32K_INT_EN_UNION;
#define GLB_ON_COMM_32K_INT_EN_comm_32k_int_en_START  (0)
#define GLB_ON_COMM_32K_INT_EN_comm_32k_int_en_END    (0)


/*****************************************************************************
 结构名    : GLB_ON_COMM_32K_INT3_CLR_UNION
 结构说明  : COMM_32K_INT3_CLR 寄存器结构定义。地址偏移量:0x3C，初值:0x00000000，宽度:32
 寄存器说明: 
*****************************************************************************/
typedef union
{
    unsigned long      comm_32k_int3_clr_reg;
    struct
    {
        unsigned long  comm_32k_int_clr : 1;  /* bit[0]   : 32k公共定时器中断清除寄存器。1，表示清除相应比特位置中断；0，表示不清除相应比特位置的中断。 */
        unsigned long  reserved         : 31; /* bit[1-31]: 保留 */
    } reg;
} GLB_ON_COMM_32K_INT3_CLR_UNION;
#define GLB_ON_COMM_32K_INT3_CLR_comm_32k_int_clr_START  (0)
#define GLB_ON_COMM_32K_INT3_CLR_comm_32k_int_clr_END    (0)


/*****************************************************************************
 结构名    : GLB_ON_COMM_32K_INT_PERIOD_UNION
 结构说明  : COMM_32K_INT_PERIOD 寄存器结构定义。地址偏移量:0x40，初值:0x00000000，宽度:32
 寄存器说明: 
*****************************************************************************/
typedef union
{
    unsigned long      comm_32k_int_period_reg;
    struct
    {
        unsigned long  cpu_int_period : 24; /* bit[0-23] : 32K时钟域的自定义中断周期，配置范围是0~512s。单位是32k时钟的周期个数。每隔cpu_int_period个32k时钟合周期，产生1次中断。注意：如果期望的调整周期是N，则应配置N-1 */
        unsigned long  reserved       : 8;  /* bit[24-31]: 保留 */
    } reg;
} GLB_ON_COMM_32K_INT_PERIOD_UNION;
#define GLB_ON_COMM_32K_INT_PERIOD_cpu_int_period_START  (0)
#define GLB_ON_COMM_32K_INT_PERIOD_cpu_int_period_END    (23)




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

#endif /* end of bbp_glb_on_interface.h */
