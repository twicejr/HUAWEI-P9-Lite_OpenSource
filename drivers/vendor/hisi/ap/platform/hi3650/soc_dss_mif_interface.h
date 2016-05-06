/******************************************************************************

                 版权所有 (C), 2001-2015, 华为技术有限公司

 ******************************************************************************
  文 件 名   : soc_dss_mif_interface.h
  版 本 号   : 初稿
  作    者   : Excel2Code
  生成日期   : 2015-03-10 11:20:13
  最近修改   :
  功能描述   : 接口头文件
  函数列表   :
  修改历史   :
  1.日    期   : 2015年3月10日
    作    者   : fWX220878
    修改内容   : 从《Hi3650V100 SOC寄存器手册_DSS_MIF.xml》自动生成

******************************************************************************/

/*****************************************************************************
  1 其他头文件包含
*****************************************************************************/

#ifndef __SOC_DSS_MIF_INTERFACE_H__
#define __SOC_DSS_MIF_INTERFACE_H__

#ifdef __cplusplus
    #if __cplusplus
        extern "C" {
    #endif
#endif



/*****************************************************************************
  2 宏定义
*****************************************************************************/

/****************************************************************************
                     (1/1) reg_MIF
 ****************************************************************************/
/* 寄存器说明：MIF全局控制寄存器
   位域定义UNION结构:  SOC_DSS_MIF_MIF_ENABLE_UNION */
#define SOC_DSS_MIF_MIF_ENABLE_ADDR(base)             ((base) + (0x0000))

/* 寄存器说明：MEM低功耗控制寄存器
   位域定义UNION结构:  SOC_DSS_MIF_MIF_MEM_CTRL_UNION */
#define SOC_DSS_MIF_MIF_MEM_CTRL_ADDR(base)           ((base) + (0x0004))

/* 寄存器说明：MMU_CTRL控制寄存器0
   位域定义UNION结构:  SOC_DSS_MIF_MIF_CTRL0_UNION */
#define SOC_DSS_MIF_MIF_CTRL0_ADDR(base, j)           ((base) + (0x0000+32*(j)))

/* 寄存器说明：MMU_CTRL控制寄存器1
   位域定义UNION结构:  SOC_DSS_MIF_MIF_CTRL1_UNION */
#define SOC_DSS_MIF_MIF_CTRL1_ADDR(base, j)           ((base) + (0x0004+32*(j)))

/* 寄存器说明：MMU_CTRL控制寄存器2
   位域定义UNION结构:  SOC_DSS_MIF_MIF_CTRL2_UNION */
#define SOC_DSS_MIF_MIF_CTRL2_ADDR(base, j)           ((base) + (0x0008+32*(j)))

/* 寄存器说明：MMU_CTRL控制寄存器3
   位域定义UNION结构:  SOC_DSS_MIF_MIF_CTRL3_UNION */
#define SOC_DSS_MIF_MIF_CTRL3_ADDR(base, j)           ((base) + (0x000C+32*(j)))

/* 寄存器说明：MMU_CTRL控制寄存器4
   位域定义UNION结构:  SOC_DSS_MIF_MIF_CTRL4_UNION */
#define SOC_DSS_MIF_MIF_CTRL4_ADDR(base, j)           ((base) + (0x0010+32*(j)))

/* 寄存器说明：MMU_CTRL控制寄存器5
   位域定义UNION结构:  SOC_DSS_MIF_MIF_CTRL5_UNION */
#define SOC_DSS_MIF_MIF_CTRL5_ADDR(base, j)           ((base) + (0x0014+32*(j)))

/* 寄存器说明：MMU_CTRL状态寄存器0
   位域定义UNION结构:  SOC_DSS_MIF_MIF_STAT0_UNION */
#define SOC_DSS_MIF_MIF_STAT0_ADDR(base, k)           ((base) + (0x0160+16*(k)))

/* 寄存器说明：MMU_CTRL状态寄存器1
   位域定义UNION结构:  SOC_DSS_MIF_MIF_STAT1_UNION */
#define SOC_DSS_MIF_MIF_STAT1_ADDR(base, k)           ((base) + (0x0164+16*(k)))

/* 寄存器说明：MMU_CTRL状态寄存器2
   位域定义UNION结构:  SOC_DSS_MIF_MIF_STAT2_UNION */
#define SOC_DSS_MIF_MIF_STAT2_ADDR(base, k)           ((base) + (0x0168+16*(k)))

/* 寄存器说明：模块影子寄存器恢复到默认值
   位域定义UNION结构:  SOC_DSS_MIF_REG_DEFAULT_UNION */
#define SOC_DSS_MIF_REG_DEFAULT_ADDR(base)            ((base) + (0x0500))

/* 寄存器说明：影子寄存器读选择寄存器
   位域定义UNION结构:  SOC_DSS_MIF_MIF_SHADOW_READ_UNION */
#define SOC_DSS_MIF_MIF_SHADOW_READ_ADDR(base)        ((base) + (0x0504))

/* 寄存器说明：影子寄存器读选择寄存器
   位域定义UNION结构:  SOC_DSS_MIF_MIF_CLK_CTL_UNION */
#define SOC_DSS_MIF_MIF_CLK_CTL_ADDR(base)            ((base) + (0x0508))





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
                     (1/1) reg_MIF
 ****************************************************************************/
/*****************************************************************************
 结构名    : SOC_DSS_MIF_MIF_ENABLE_UNION
 结构说明  : MIF_ENABLE 寄存器结构定义。地址偏移量:0x0000，初值:0x00000000，宽度:32
 寄存器说明: MIF全局控制寄存器
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  enable      : 1;  /* bit[0]   : MIF使能信号：
                                                      1：使能
                                                      0：禁止 */
        unsigned int  tagcache_en : 1;  /* bit[1]   : tag compare cache使能：
                                                      1：使能
                                                      0：禁止 */
        unsigned int  reserved    : 30; /* bit[2-31]:  */
    } reg;
} SOC_DSS_MIF_MIF_ENABLE_UNION;
#endif
#define SOC_DSS_MIF_MIF_ENABLE_enable_START       (0)
#define SOC_DSS_MIF_MIF_ENABLE_enable_END         (0)
#define SOC_DSS_MIF_MIF_ENABLE_tagcache_en_START  (1)
#define SOC_DSS_MIF_MIF_ENABLE_tagcache_en_END    (1)


/*****************************************************************************
 结构名    : SOC_DSS_MIF_MIF_MEM_CTRL_UNION
 结构说明  : MIF_MEM_CTRL 寄存器结构定义。地址偏移量:0x0004，初值:0x01A80050，宽度:32
 寄存器说明: MEM低功耗控制寄存器
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  mif_mem_ctrl_s : 16; /* bit[0-15] : Single Port类型MEM低功耗软件配置模式下有效：
                                                          [6:5]: WTSEL,默认为2'b10;
                                                          [4:3]: RTSEL,默认为2'b10;
                                                          [2]: 为1表示进入Shut Down模式
                                                          [1]: 为1表示进入Deep Sleep模式
                                                          [0]: 为1表示进入Sleep模式 */
        unsigned int  mif_mem_ctrl_t : 16; /* bit[16-31]: Two Port类型MEM低功耗软件配置模式下有效：
                                                          [9:7]: KP,默认为3'b011;
                                                          [6:5]: WCT,默认为2'b01;
                                                          [4:3]: RCT,默认为2'b01;
                                                          [2]: 为1表示进入Shut Down模式
                                                          [1]: 为1表示进入Deep Sleep模式
                                                          [0]: 为1表示进入Sleep模式 */
    } reg;
} SOC_DSS_MIF_MIF_MEM_CTRL_UNION;
#endif
#define SOC_DSS_MIF_MIF_MEM_CTRL_mif_mem_ctrl_s_START  (0)
#define SOC_DSS_MIF_MIF_MEM_CTRL_mif_mem_ctrl_s_END    (15)
#define SOC_DSS_MIF_MIF_MEM_CTRL_mif_mem_ctrl_t_START  (16)
#define SOC_DSS_MIF_MIF_MEM_CTRL_mif_mem_ctrl_t_END    (31)


/*****************************************************************************
 结构名    : SOC_DSS_MIF_MIF_CTRL0_UNION
 结构说明  : MIF_CTRL0 寄存器结构定义。地址偏移量:0x0000+32*(j)，初值:0x00000000，宽度:32
 寄存器说明: MMU_CTRL控制寄存器0
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  ctrl_en  : 1;  /* bit[0]   : 1：通道使能
                                                   0：通道禁止 */
        unsigned int  reserved : 31; /* bit[1-31]:  */
    } reg;
} SOC_DSS_MIF_MIF_CTRL0_UNION;
#endif
#define SOC_DSS_MIF_MIF_CTRL0_ctrl_en_START   (0)
#define SOC_DSS_MIF_MIF_CTRL0_ctrl_en_END     (0)


/*****************************************************************************
 结构名    : SOC_DSS_MIF_MIF_CTRL1_UNION
 结构说明  : MIF_CTRL1 寄存器结构定义。地址偏移量:0x0004+32*(j)，初值:0x00000020，宽度:32
 寄存器说明: MMU_CTRL控制寄存器1
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  sid         : 4;  /* bit[0-3]  : sid标号：0~15 */
        unsigned int  qos_en      : 1;  /* bit[4]    : 预取qos使能信号：
                                                       1：使能
                                                       0：禁止 */
        unsigned int  bypass      : 1;  /* bit[5]    : 1：bypass
                                                       0：normal */
        unsigned int  reserved_0  : 4;  /* bit[6-9]  :  */
        unsigned int  invalid_sel : 2;  /* bit[10-11]: TAG invalid策略：
                                                       2'b00：VA跳转到新的TAG,
                                                       2'b01：tag比较时用右端点(大)
                                                       2'b10：上一个TAG可清掉tag比较时用左端点(小)
                                                       2'b11： */
        unsigned int  reserved_1  : 5;  /* bit[12-16]:  */
        unsigned int  rw_type     : 1;  /* bit[17]   : 1：写通道
                                                       0：读通道 */
        unsigned int  initial_en  : 1;  /* bit[18]   : 1：预取initial使能
                                                       0：预取initial禁止 */
        unsigned int  pref_va_ctl : 1;  /* bit[19]   : va和pref_va的顺序控制.小图旋转时，预取和真实VA请求之间可能会产生混乱。1：保证预取和真实VA请求之间的顺序. */
        unsigned int  reserved_2  : 12; /* bit[20-31]:  */
    } reg;
} SOC_DSS_MIF_MIF_CTRL1_UNION;
#endif
#define SOC_DSS_MIF_MIF_CTRL1_sid_START          (0)
#define SOC_DSS_MIF_MIF_CTRL1_sid_END            (3)
#define SOC_DSS_MIF_MIF_CTRL1_qos_en_START       (4)
#define SOC_DSS_MIF_MIF_CTRL1_qos_en_END         (4)
#define SOC_DSS_MIF_MIF_CTRL1_bypass_START       (5)
#define SOC_DSS_MIF_MIF_CTRL1_bypass_END         (5)
#define SOC_DSS_MIF_MIF_CTRL1_invalid_sel_START  (10)
#define SOC_DSS_MIF_MIF_CTRL1_invalid_sel_END    (11)
#define SOC_DSS_MIF_MIF_CTRL1_rw_type_START      (17)
#define SOC_DSS_MIF_MIF_CTRL1_rw_type_END        (17)
#define SOC_DSS_MIF_MIF_CTRL1_initial_en_START   (18)
#define SOC_DSS_MIF_MIF_CTRL1_initial_en_END     (18)
#define SOC_DSS_MIF_MIF_CTRL1_pref_va_ctl_START  (19)
#define SOC_DSS_MIF_MIF_CTRL1_pref_va_ctl_END    (19)


/*****************************************************************************
 结构名    : SOC_DSS_MIF_MIF_CTRL2_UNION
 结构说明  : MIF_CTRL2 寄存器结构定义。地址偏移量:0x0008+32*(j)，初值:0x00000000，宽度:32
 寄存器说明: MMU_CTRL控制寄存器2
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  stride0  : 20; /* bit[0-19] : 单位4KB，图像帧stride */
        unsigned int  reserved : 12; /* bit[20-31]:  */
    } reg;
} SOC_DSS_MIF_MIF_CTRL2_UNION;
#endif
#define SOC_DSS_MIF_MIF_CTRL2_stride0_START   (0)
#define SOC_DSS_MIF_MIF_CTRL2_stride0_END     (19)


/*****************************************************************************
 结构名    : SOC_DSS_MIF_MIF_CTRL3_UNION
 结构说明  : MIF_CTRL3 寄存器结构定义。地址偏移量:0x000C+32*(j)，初值:0x00000000，宽度:32
 寄存器说明: MMU_CTRL控制寄存器3
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  stride1  : 20; /* bit[0-19] : 单位4KB，图像帧stride */
        unsigned int  reserved : 12; /* bit[20-31]:  */
    } reg;
} SOC_DSS_MIF_MIF_CTRL3_UNION;
#endif
#define SOC_DSS_MIF_MIF_CTRL3_stride1_START   (0)
#define SOC_DSS_MIF_MIF_CTRL3_stride1_END     (19)


/*****************************************************************************
 结构名    : SOC_DSS_MIF_MIF_CTRL4_UNION
 结构说明  : MIF_CTRL4 寄存器结构定义。地址偏移量:0x0010+32*(j)，初值:0x00000000，宽度:32
 寄存器说明: MMU_CTRL控制寄存器4
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  stride2  : 20; /* bit[0-19] : 单位4KB，图像帧stride */
        unsigned int  reserved : 12; /* bit[20-31]:  */
    } reg;
} SOC_DSS_MIF_MIF_CTRL4_UNION;
#endif
#define SOC_DSS_MIF_MIF_CTRL4_stride2_START   (0)
#define SOC_DSS_MIF_MIF_CTRL4_stride2_END     (19)


/*****************************************************************************
 结构名    : SOC_DSS_MIF_MIF_CTRL5_UNION
 结构说明  : MIF_CTRL5 寄存器结构定义。地址偏移量:0x0014+32*(j)，初值:0x00000000，宽度:32
 寄存器说明: MMU_CTRL控制寄存器5
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  stride3  : 20; /* bit[0-19] : 单位4KB，图像帧stride */
        unsigned int  reserved : 12; /* bit[20-31]:  */
    } reg;
} SOC_DSS_MIF_MIF_CTRL5_UNION;
#endif
#define SOC_DSS_MIF_MIF_CTRL5_stride3_START   (0)
#define SOC_DSS_MIF_MIF_CTRL5_stride3_END     (19)


/*****************************************************************************
 结构名    : SOC_DSS_MIF_MIF_STAT0_UNION
 结构说明  : MIF_STAT0 寄存器结构定义。地址偏移量:0x0160+16*(k)，初值:0x00000000，宽度:32
 寄存器说明: MMU_CTRL状态寄存器0
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  tag_status : 32; /* bit[0-31]: 每个tag所处的状态 */
    } reg;
} SOC_DSS_MIF_MIF_STAT0_UNION;
#endif
#define SOC_DSS_MIF_MIF_STAT0_tag_status_START  (0)
#define SOC_DSS_MIF_MIF_STAT0_tag_status_END    (31)


/*****************************************************************************
 结构名    : SOC_DSS_MIF_MIF_STAT1_UNION
 结构说明  : MIF_STAT1 寄存器结构定义。地址偏移量:0x0164+16*(k)，初值:0x00008400，宽度:32
 寄存器说明: MMU_CTRL状态寄存器1
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  pref_ostd   : 5;  /* bit[0-4]  : 当前预取index个数 */
        unsigned int  index_ostd  : 5;  /* bit[5-9]  : 当前有效index个数； */
        unsigned int  pref_state  : 5;  /* bit[10-14]: 当前预取状态机状态 */
        unsigned int  fetch_state : 4;  /* bit[15-18]: 当前实取状态机状态 */
        unsigned int  reserved    : 13; /* bit[19-31]:  */
    } reg;
} SOC_DSS_MIF_MIF_STAT1_UNION;
#endif
#define SOC_DSS_MIF_MIF_STAT1_pref_ostd_START    (0)
#define SOC_DSS_MIF_MIF_STAT1_pref_ostd_END      (4)
#define SOC_DSS_MIF_MIF_STAT1_index_ostd_START   (5)
#define SOC_DSS_MIF_MIF_STAT1_index_ostd_END     (9)
#define SOC_DSS_MIF_MIF_STAT1_pref_state_START   (10)
#define SOC_DSS_MIF_MIF_STAT1_pref_state_END     (14)
#define SOC_DSS_MIF_MIF_STAT1_fetch_state_START  (15)
#define SOC_DSS_MIF_MIF_STAT1_fetch_state_END    (18)


/*****************************************************************************
 结构名    : SOC_DSS_MIF_MIF_STAT2_UNION
 结构说明  : MIF_STAT2 寄存器结构定义。地址偏移量:0x0168+16*(k)，初值:0x00000000，宽度:32
 寄存器说明: MMU_CTRL状态寄存器2
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  pref_tag_hit  : 16; /* bit[0-15] : 当前预取命中值； */
        unsigned int  fetch_tag_hit : 16; /* bit[16-31]: 当前实取命中值； */
    } reg;
} SOC_DSS_MIF_MIF_STAT2_UNION;
#endif
#define SOC_DSS_MIF_MIF_STAT2_pref_tag_hit_START   (0)
#define SOC_DSS_MIF_MIF_STAT2_pref_tag_hit_END     (15)
#define SOC_DSS_MIF_MIF_STAT2_fetch_tag_hit_START  (16)
#define SOC_DSS_MIF_MIF_STAT2_fetch_tag_hit_END    (31)


/*****************************************************************************
 结构名    : SOC_DSS_MIF_REG_DEFAULT_UNION
 结构说明  : REG_DEFAULT 寄存器结构定义。地址偏移量:0x0500，初值:0x00000000，宽度:32
 寄存器说明: 模块影子寄存器恢复到默认值
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  reg_default : 1;  /* bit[0]   : 模块所有影子寄存器恢复到默认值，高有效 */
        unsigned int  reserved    : 31; /* bit[1-31]:  */
    } reg;
} SOC_DSS_MIF_REG_DEFAULT_UNION;
#endif
#define SOC_DSS_MIF_REG_DEFAULT_reg_default_START  (0)
#define SOC_DSS_MIF_REG_DEFAULT_reg_default_END    (0)


/*****************************************************************************
 结构名    : SOC_DSS_MIF_MIF_SHADOW_READ_UNION
 结构说明  : MIF_SHADOW_READ 寄存器结构定义。地址偏移量:0x0504，初值:0x00000000，宽度:32
 寄存器说明: 影子寄存器读选择寄存器
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  mif_rd_shadow : 1;  /* bit[0]   : 1'b0 :读工作寄存器
                                                        1'b1 :读影子寄存器 */
        unsigned int  reserved      : 31; /* bit[1-31]: 保留 */
    } reg;
} SOC_DSS_MIF_MIF_SHADOW_READ_UNION;
#endif
#define SOC_DSS_MIF_MIF_SHADOW_READ_mif_rd_shadow_START  (0)
#define SOC_DSS_MIF_MIF_SHADOW_READ_mif_rd_shadow_END    (0)


/*****************************************************************************
 结构名    : SOC_DSS_MIF_MIF_CLK_CTL_UNION
 结构说明  : MIF_CLK_CTL 寄存器结构定义。地址偏移量:0x0508，初值:0x00000003，宽度:32
 寄存器说明: 影子寄存器读选择寄存器
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  clk_en   : 1;  /* bit[0]   : MIF模块的软件时钟使能信号
                                                   1：表示软件时钟使能有效，允许硬件开钟
                                                   0：表示软件时钟使能无效，禁止硬件开钟 */
        unsigned int  clk_sel  : 1;  /* bit[1]   : MIF模块的时钟选择信号，
                                                   1：表示强制打开时钟。
                                                   0：表示需要根据软件和硬件的时钟使能来开启或关闭时钟 */
        unsigned int  reserved : 30; /* bit[2-31]: 保留 */
    } reg;
} SOC_DSS_MIF_MIF_CLK_CTL_UNION;
#endif
#define SOC_DSS_MIF_MIF_CLK_CTL_clk_en_START    (0)
#define SOC_DSS_MIF_MIF_CLK_CTL_clk_en_END      (0)
#define SOC_DSS_MIF_MIF_CLK_CTL_clk_sel_START   (1)
#define SOC_DSS_MIF_MIF_CLK_CTL_clk_sel_END     (1)






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

#endif /* end of soc_dss_mif_interface.h */
