/******************************************************************************

                 版权所有 (C), 2001-2015, 华为技术有限公司

 ******************************************************************************
  文 件 名   : soc_dss_ifbc_interface.h
  版 本 号   : 初稿
  作    者   : Excel2Code
  生成日期   : 2015-03-10 11:20:08
  最近修改   :
  功能描述   : 接口头文件
  函数列表   :
  修改历史   :
  1.日    期   : 2015年3月10日
    作    者   : fWX220878
    修改内容   : 从《Hi3650V100 SOC寄存器手册_DSS_IFBC.xml》自动生成

******************************************************************************/

/*****************************************************************************
  1 其他头文件包含
*****************************************************************************/

#ifndef __SOC_DSS_IFBC_INTERFACE_H__
#define __SOC_DSS_IFBC_INTERFACE_H__

#ifdef __cplusplus
    #if __cplusplus
        extern "C" {
    #endif
#endif



/*****************************************************************************
  2 宏定义
*****************************************************************************/

/****************************************************************************
                     (1/1) reg_IFBC
 ****************************************************************************/
/* 寄存器说明：IFBC图像尺寸
   位域定义UNION结构:  SOC_DSS_IFBC_IFBC_SIZE_UNION */
#define SOC_DSS_IFBC_IFBC_SIZE_ADDR(base)             ((base) + (0x0000))

/* 寄存器说明：IFBC控制
   位域定义UNION结构:  SOC_DSS_IFBC_IFBC_CTRL_UNION */
#define SOC_DSS_IFBC_IFBC_CTRL_ADDR(base)             ((base) + (0x0004))

/* 寄存器说明：IFBC Himax控制
   位域定义UNION结构:  SOC_DSS_IFBC_IFBC_HIMAX_CTRL0_UNION */
#define SOC_DSS_IFBC_IFBC_HIMAX_CTRL0_ADDR(base)      ((base) + (0x0008))

/* 寄存器说明：IFBC Himax控制
   位域定义UNION结构:  SOC_DSS_IFBC_IFBC_HIMAX_CTRL1_UNION */
#define SOC_DSS_IFBC_IFBC_HIMAX_CTRL1_ADDR(base)      ((base) + (0x000C))

/* 寄存器说明：IFBC Himax控制
   位域定义UNION结构:  SOC_DSS_IFBC_IFBC_HIMAX_CTRL2_UNION */
#define SOC_DSS_IFBC_IFBC_HIMAX_CTRL2_ADDR(base)      ((base) + (0x0010))

/* 寄存器说明：IFBC Himax控制
   位域定义UNION结构:  SOC_DSS_IFBC_IFBC_HIMAX_CTRL3_UNION */
#define SOC_DSS_IFBC_IFBC_HIMAX_CTRL3_ADDR(base)      ((base) + (0x0014))

/* 寄存器说明：低功耗控制
   位域定义UNION结构:  SOC_DSS_IFBC_IFBC_EN_UNION */
#define SOC_DSS_IFBC_IFBC_EN_ADDR(base)               ((base) + (0x0018))

/* 寄存器说明：MEM低功耗控制寄存器
   位域定义UNION结构:  SOC_DSS_IFBC_IFBC_MEM_CTRL_UNION */
#define SOC_DSS_IFBC_IFBC_MEM_CTRL_ADDR(base)         ((base) + (0x001C))

/* 寄存器说明：
   位域定义UNION结构:  SOC_DSS_IFBC_IFBC_INSERT_UNION */
#define SOC_DSS_IFBC_IFBC_INSERT_ADDR(base)           ((base) + (0x0020))

/* 寄存器说明：
   位域定义UNION结构:  SOC_DSS_IFBC_HIMAX_TEST_MODE_UNION */
#define SOC_DSS_IFBC_HIMAX_TEST_MODE_ADDR(base)       ((base) + (0x0024))

/* 寄存器说明：
   位域定义UNION结构:  SOC_DSS_IFBC_IFBC_CORE_GT_UNION */
#define SOC_DSS_IFBC_IFBC_CORE_GT_ADDR(base)          ((base) + (0x0028))

/* 寄存器说明：MEM低功耗控制寄存器
   位域定义UNION结构:  SOC_DSS_IFBC_IFBC_PM_CTRL_UNION */
#define SOC_DSS_IFBC_IFBC_PM_CTRL_ADDR(base)          ((base) + (0x002C))

/* 寄存器说明：读影子寄存器选择信号
   位域定义UNION结构:  SOC_DSS_IFBC_IFBC_RD_SHADOW_UNION */
#define SOC_DSS_IFBC_IFBC_RD_SHADOW_ADDR(base)        ((base) + (0x0030))

/* 寄存器说明：Orise控制寄存器
   位域定义UNION结构:  SOC_DSS_IFBC_ORISE_CTL_UNION */
#define SOC_DSS_IFBC_ORISE_CTL_ADDR(base)             ((base) + (0x0034))

/* 寄存器说明：Orise debug寄存器
   位域定义UNION结构:  SOC_DSS_IFBC_ORSISE_DEBUG0_UNION */
#define SOC_DSS_IFBC_ORSISE_DEBUG0_ADDR(base)         ((base) + (0x0038))

/* 寄存器说明：Orise debug寄存器
   位域定义UNION结构:  SOC_DSS_IFBC_ORSISE_DEBUG1_UNION */
#define SOC_DSS_IFBC_ORSISE_DEBUG1_ADDR(base)         ((base) + (0x003C))

/* 寄存器说明：RSP测试信号
   位域定义UNION结构:  SOC_DSS_IFBC_rsp_comp_test_UNION */
#define SOC_DSS_IFBC_rsp_comp_test_ADDR(base)         ((base) + (0x0040))

/* 寄存器说明：一级模块时钟选择信号
   位域定义UNION结构:  SOC_DSS_IFBC_IFBC_CLK_SEL_UNION */
#define SOC_DSS_IFBC_IFBC_CLK_SEL_ADDR(base)          ((base) + (0x044))

/* 寄存器说明：一级模块时钟使能信号
   位域定义UNION结构:  SOC_DSS_IFBC_IFBC_CLK_EN_UNION */
#define SOC_DSS_IFBC_IFBC_CLK_EN_ADDR(base)           ((base) + (0x048))

/* 寄存器说明：PAD寄存器
   位域定义UNION结构:  SOC_DSS_IFBC_IFBC_PAD_UNION */
#define SOC_DSS_IFBC_IFBC_PAD_ADDR(base)              ((base) + (0x004C))

/* 寄存器说明：模块影子寄存器恢复到默认值
   位域定义UNION结构:  SOC_DSS_IFBC_REG_DEFAULT_UNION */
#define SOC_DSS_IFBC_REG_DEFAULT_ADDR(base)           ((base) + (0x0050))





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
                     (1/1) reg_IFBC
 ****************************************************************************/
/*****************************************************************************
 结构名    : SOC_DSS_IFBC_IFBC_SIZE_UNION
 结构说明  : IFBC_SIZE 寄存器结构定义。地址偏移量:0x0000，初值:0x04FF02CF，宽度:32
 寄存器说明: IFBC图像尺寸
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  ifbc_size_vrt : 16; /* bit[0-15] : IFBC读入图像的像素高度(垂直方向)-1(以像素为单位)；只能是偶数 */
        unsigned int  ifbc_size_hrz : 16; /* bit[16-31]: IFBC读入图像的像素宽度(水平方向)-1(以像素为单位)；只能是偶数 */
    } reg;
} SOC_DSS_IFBC_IFBC_SIZE_UNION;
#endif
#define SOC_DSS_IFBC_IFBC_SIZE_ifbc_size_vrt_START  (0)
#define SOC_DSS_IFBC_IFBC_SIZE_ifbc_size_vrt_END    (15)
#define SOC_DSS_IFBC_IFBC_SIZE_ifbc_size_hrz_START  (16)
#define SOC_DSS_IFBC_IFBC_SIZE_ifbc_size_hrz_END    (31)


/*****************************************************************************
 结构名    : SOC_DSS_IFBC_IFBC_CTRL_UNION
 结构说明  : IFBC_CTRL 寄存器结构定义。地址偏移量:0x0004，初值:0x00000006，宽度:32
 寄存器说明: IFBC控制
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  comp_mode     : 3;  /* bit[0-2]  : 压缩算法模式
                                                         3'b000: orise2x
                                                         3'b001: orise3x
                                                         3'b010: himax2x
                                                         3'b011: rsp2x
                                                         3'b100: rsp3x
                                                         3'b101: vesa dsc/1 pipe
                                                         3'b110: vesa dsc/2 pipe */
        unsigned int  ifbc_out_mode : 1;  /* bit[3]    : ifbc输出数据格式：
                                                         1: 24bit都为有效数据
                                                         0: 高8位补0，低16位有效数据 */
        unsigned int  cmp_dat_rev0  : 1;  /* bit[4]    : 要做24bit高低位反转
                                                         0：否
                                                         1：反转 */
        unsigned int  cmp_dat_rev1  : 1;  /* bit[5]    : 要做byte高低位反转
                                                         0：否
                                                         1：反转 */
        unsigned int  auto_sel      : 1;  /* bit[6]    : 1：硬件自动配置模式（硬件根据comp_mode,ifbc_size_hrz,out_mode自动配置dpk_mode_sel,dup_mode_sel,num_pad,insert_byte,insert_byte_num）
                                                         0：软件配置模式 */
        unsigned int  dpk_mode_sel  : 3;  /* bit[7-9]  : ifbc_dpk输入数据有效位宽
                                                         3'b0: 16bit，orise3x时使用
                                                         3'b1: 48bit，orise2x/himax2x/rsp2x时使用
                                                         3'b10:64bit，rsp3x时使用 */
        unsigned int  dup_mode_sel  : 3;  /* bit[10-12]: fbc_dup输出采用的模式
                                                         3'b0: 4x1 size输出，rsp2x时使用
                                                         3'b1: 4x2 size输出，rsp3x时使用
                                                         3'b10:2x2 size输出，himax2x/orise2x时使用
                                                         3'b11:2x1 size输出，orise3x时使用 */
        unsigned int  porch_num     : 8;  /* bit[13-20]: 每行需要行尾需要反压下行的周期数，同ifbc 输入像素的时钟 */
        unsigned int  reserved      : 11; /* bit[21-31]: 保留 */
    } reg;
} SOC_DSS_IFBC_IFBC_CTRL_UNION;
#endif
#define SOC_DSS_IFBC_IFBC_CTRL_comp_mode_START      (0)
#define SOC_DSS_IFBC_IFBC_CTRL_comp_mode_END        (2)
#define SOC_DSS_IFBC_IFBC_CTRL_ifbc_out_mode_START  (3)
#define SOC_DSS_IFBC_IFBC_CTRL_ifbc_out_mode_END    (3)
#define SOC_DSS_IFBC_IFBC_CTRL_cmp_dat_rev0_START   (4)
#define SOC_DSS_IFBC_IFBC_CTRL_cmp_dat_rev0_END     (4)
#define SOC_DSS_IFBC_IFBC_CTRL_cmp_dat_rev1_START   (5)
#define SOC_DSS_IFBC_IFBC_CTRL_cmp_dat_rev1_END     (5)
#define SOC_DSS_IFBC_IFBC_CTRL_auto_sel_START       (6)
#define SOC_DSS_IFBC_IFBC_CTRL_auto_sel_END         (6)
#define SOC_DSS_IFBC_IFBC_CTRL_dpk_mode_sel_START   (7)
#define SOC_DSS_IFBC_IFBC_CTRL_dpk_mode_sel_END     (9)
#define SOC_DSS_IFBC_IFBC_CTRL_dup_mode_sel_START   (10)
#define SOC_DSS_IFBC_IFBC_CTRL_dup_mode_sel_END     (12)
#define SOC_DSS_IFBC_IFBC_CTRL_porch_num_START      (13)
#define SOC_DSS_IFBC_IFBC_CTRL_porch_num_END        (20)


/*****************************************************************************
 结构名    : SOC_DSS_IFBC_IFBC_HIMAX_CTRL0_UNION
 结构说明  : IFBC_HIMAX_CTRL0 寄存器结构定义。地址偏移量:0x0008，初值:0x04020100，宽度:32
 寄存器说明: IFBC Himax控制
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  cfg_hm_lut0 : 32; /* bit[0-31]: himax码表 */
    } reg;
} SOC_DSS_IFBC_IFBC_HIMAX_CTRL0_UNION;
#endif
#define SOC_DSS_IFBC_IFBC_HIMAX_CTRL0_cfg_hm_lut0_START  (0)
#define SOC_DSS_IFBC_IFBC_HIMAX_CTRL0_cfg_hm_lut0_END    (31)


/*****************************************************************************
 结构名    : SOC_DSS_IFBC_IFBC_HIMAX_CTRL1_UNION
 结构说明  : IFBC_HIMAX_CTRL1 寄存器结构定义。地址偏移量:0x000C，初值:0x18100A08，宽度:32
 寄存器说明: IFBC Himax控制
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  cfg_hm_lut1 : 32; /* bit[0-31]: himax码表 */
    } reg;
} SOC_DSS_IFBC_IFBC_HIMAX_CTRL1_UNION;
#endif
#define SOC_DSS_IFBC_IFBC_HIMAX_CTRL1_cfg_hm_lut1_START  (0)
#define SOC_DSS_IFBC_IFBC_HIMAX_CTRL1_cfg_hm_lut1_END    (31)


/*****************************************************************************
 结构名    : SOC_DSS_IFBC_IFBC_HIMAX_CTRL2_UNION
 结构说明  : IFBC_HIMAX_CTRL2 寄存器结构定义。地址偏移量:0x0010，初值:0x40383020，宽度:32
 寄存器说明: IFBC Himax控制
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  cfg_hm_lut2 : 32; /* bit[0-31]: himax码表 */
    } reg;
} SOC_DSS_IFBC_IFBC_HIMAX_CTRL2_UNION;
#endif
#define SOC_DSS_IFBC_IFBC_HIMAX_CTRL2_cfg_hm_lut2_START  (0)
#define SOC_DSS_IFBC_IFBC_HIMAX_CTRL2_cfg_hm_lut2_END    (31)


/*****************************************************************************
 结构名    : SOC_DSS_IFBC_IFBC_HIMAX_CTRL3_UNION
 结构说明  : IFBC_HIMAX_CTRL3 寄存器结构定义。地址偏移量:0x0014，初值:0xFFC0A080，宽度:32
 寄存器说明: IFBC Himax控制
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  cfg_hm_lut3 : 32; /* bit[0-31]: himax码表 */
    } reg;
} SOC_DSS_IFBC_IFBC_HIMAX_CTRL3_UNION;
#endif
#define SOC_DSS_IFBC_IFBC_HIMAX_CTRL3_cfg_hm_lut3_START  (0)
#define SOC_DSS_IFBC_IFBC_HIMAX_CTRL3_cfg_hm_lut3_END    (31)


/*****************************************************************************
 结构名    : SOC_DSS_IFBC_IFBC_EN_UNION
 结构说明  : IFBC_EN 寄存器结构定义。地址偏移量:0x0018，初值:0x00000000，宽度:32
 寄存器说明: 低功耗控制
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  ifbc_en      : 1;  /* bit[0]   : 0: IFBC disable;
                                                       1: IFBC enable; */
        unsigned int  ifbc_out_sel : 1;  /* bit[1]   : 0: bypass;
                                                       1: 正常工作 */
        unsigned int  reserved     : 30; /* bit[2-31]: 保留 */
    } reg;
} SOC_DSS_IFBC_IFBC_EN_UNION;
#endif
#define SOC_DSS_IFBC_IFBC_EN_ifbc_en_START       (0)
#define SOC_DSS_IFBC_IFBC_EN_ifbc_en_END         (0)
#define SOC_DSS_IFBC_IFBC_EN_ifbc_out_sel_START  (1)
#define SOC_DSS_IFBC_IFBC_EN_ifbc_out_sel_END    (1)


/*****************************************************************************
 结构名    : SOC_DSS_IFBC_IFBC_MEM_CTRL_UNION
 结构说明  : IFBC_MEM_CTRL 寄存器结构定义。地址偏移量:0x001C，初值:0x00000000，宽度:32
 寄存器说明: MEM低功耗控制寄存器
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  ifbc_mem_ctrl_0 : 4;  /* bit[0-3]  : 调试用寄存器，对应第一块spram512x48
                                                           [3] mem_ctrl_auto_en , 自动模式、软件配置模式选择,0自动模式，1软件配置模式 
                                                           [2]: 软件配置模式下有效，为1表示进入Shut Down模式
                                                           [1]: 软件配置模式下有效，为1表示进入Deep Sleep模式
                                                           [0]: 软件配置模式下有效，为1表示进入Sleep模式 */
        unsigned int  ifbc_mem_ctrl_1 : 4;  /* bit[4-7]  : 调试用寄存器，各bit含义如下 */
        unsigned int  ifbc_mem_ctrl_2 : 4;  /* bit[8-11] : 调试用寄存器，各bit含义如下 */
        unsigned int  ifbc_mem_ctrl_3 : 4;  /* bit[12-15]: 调试用寄存器，各bit含义如下 */
        unsigned int  ifbc_mem_ctrl_4 : 4;  /* bit[16-19]: 调试用寄存器，各bit含义如下 */
        unsigned int  ifbc_mem_ctrl_5 : 4;  /* bit[20-23]: 调试用寄存器，各bit含义如下 */
        unsigned int  ifbc_mem_ctrl_6 : 4;  /* bit[24-27]: 调试用寄存器，各bit含义如下 */
        unsigned int  ifbc_mem_ctrl_7 : 4;  /* bit[28-31]: 调试用寄存器，各bit含义如下 */
    } reg;
} SOC_DSS_IFBC_IFBC_MEM_CTRL_UNION;
#endif
#define SOC_DSS_IFBC_IFBC_MEM_CTRL_ifbc_mem_ctrl_0_START  (0)
#define SOC_DSS_IFBC_IFBC_MEM_CTRL_ifbc_mem_ctrl_0_END    (3)
#define SOC_DSS_IFBC_IFBC_MEM_CTRL_ifbc_mem_ctrl_1_START  (4)
#define SOC_DSS_IFBC_IFBC_MEM_CTRL_ifbc_mem_ctrl_1_END    (7)
#define SOC_DSS_IFBC_IFBC_MEM_CTRL_ifbc_mem_ctrl_2_START  (8)
#define SOC_DSS_IFBC_IFBC_MEM_CTRL_ifbc_mem_ctrl_2_END    (11)
#define SOC_DSS_IFBC_IFBC_MEM_CTRL_ifbc_mem_ctrl_3_START  (12)
#define SOC_DSS_IFBC_IFBC_MEM_CTRL_ifbc_mem_ctrl_3_END    (15)
#define SOC_DSS_IFBC_IFBC_MEM_CTRL_ifbc_mem_ctrl_4_START  (16)
#define SOC_DSS_IFBC_IFBC_MEM_CTRL_ifbc_mem_ctrl_4_END    (19)
#define SOC_DSS_IFBC_IFBC_MEM_CTRL_ifbc_mem_ctrl_5_START  (20)
#define SOC_DSS_IFBC_IFBC_MEM_CTRL_ifbc_mem_ctrl_5_END    (23)
#define SOC_DSS_IFBC_IFBC_MEM_CTRL_ifbc_mem_ctrl_6_START  (24)
#define SOC_DSS_IFBC_IFBC_MEM_CTRL_ifbc_mem_ctrl_6_END    (27)
#define SOC_DSS_IFBC_IFBC_MEM_CTRL_ifbc_mem_ctrl_7_START  (28)
#define SOC_DSS_IFBC_IFBC_MEM_CTRL_ifbc_mem_ctrl_7_END    (31)


/*****************************************************************************
 结构名    : SOC_DSS_IFBC_IFBC_INSERT_UNION
 结构说明  : IFBC_INSERT 寄存器结构定义。地址偏移量:0x0020，初值:0x00000000，宽度:32
 寄存器说明: 
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  insert_byte_num : 16; /* bit[0-15] : 压缩数据每次插入冗余数据的个数 */
        unsigned int  insert_byte     : 16; /* bit[16-31]: 压缩数据每行插入冗余数据的byte位置 */
    } reg;
} SOC_DSS_IFBC_IFBC_INSERT_UNION;
#endif
#define SOC_DSS_IFBC_IFBC_INSERT_insert_byte_num_START  (0)
#define SOC_DSS_IFBC_IFBC_INSERT_insert_byte_num_END    (15)
#define SOC_DSS_IFBC_IFBC_INSERT_insert_byte_START      (16)
#define SOC_DSS_IFBC_IFBC_INSERT_insert_byte_END        (31)


/*****************************************************************************
 结构名    : SOC_DSS_IFBC_HIMAX_TEST_MODE_UNION
 结构说明  : HIMAX_TEST_MODE 寄存器结构定义。地址偏移量:0x0024，初值:0x00000008，宽度:32
 寄存器说明: 
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  force_pat_ext_mode : 1;  /* bit[0]   : The compression is forced to only use "RGB truncation mode", default is disable. */
        unsigned int  force_pat_mode     : 1;  /* bit[1]   : The compression is forced to only use "pattern mode", default is disable. */
        unsigned int  force_yuv_mode     : 1;  /* bit[2]   : The compression is forced to only use "YUV truncation mode", default is disable. */
        unsigned int  mcmp_pat_ext_en    : 1;  /* bit[3]   : Use "RGB truncation mode" during compression, default is enable */
        unsigned int  reserved           : 28; /* bit[4-31]: 保留 */
    } reg;
} SOC_DSS_IFBC_HIMAX_TEST_MODE_UNION;
#endif
#define SOC_DSS_IFBC_HIMAX_TEST_MODE_force_pat_ext_mode_START  (0)
#define SOC_DSS_IFBC_HIMAX_TEST_MODE_force_pat_ext_mode_END    (0)
#define SOC_DSS_IFBC_HIMAX_TEST_MODE_force_pat_mode_START      (1)
#define SOC_DSS_IFBC_HIMAX_TEST_MODE_force_pat_mode_END        (1)
#define SOC_DSS_IFBC_HIMAX_TEST_MODE_force_yuv_mode_START      (2)
#define SOC_DSS_IFBC_HIMAX_TEST_MODE_force_yuv_mode_END        (2)
#define SOC_DSS_IFBC_HIMAX_TEST_MODE_mcmp_pat_ext_en_START     (3)
#define SOC_DSS_IFBC_HIMAX_TEST_MODE_mcmp_pat_ext_en_END       (3)


/*****************************************************************************
 结构名    : SOC_DSS_IFBC_IFBC_CORE_GT_UNION
 结构说明  : IFBC_CORE_GT 寄存器结构定义。地址偏移量:0x0028，初值:0x00000000，宽度:32
 寄存器说明: 
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  ifbc_core_1_gt   : 2;  /* bit[0-1]  : 该寄存器用于控制是否配置orise3x初始化序列：
                                                            00：使能orise ctr初始化序列（推荐配置）；
                                                            10：不使能orise ctr初始化序列；
                                                            01,11：保留； */
        unsigned int  ifbc_core_2_gt   : 2;  /* bit[2-3]  : [1]：1'b1 表示，IFBC的工作时钟由软件门控，1'b0 表示，IFBC的工作时钟由硬件自动控制；
                                                            [0]：1'b0 表示，IFBC工作时钟运行，1'b1 表示，IFBC工作时钟关闭； */
        unsigned int  ifbc_core_2_gt_h : 2;  /* bit[4-5]  : [1]：1'b1 表示，IFBC的工作时钟由软件门控，1'b0 表示，IFBC的工作时钟由硬件自动控制；
                                                            [0]：1'b0 表示，IFBC工作时钟运行，1'b1 表示，IFBC工作时钟关闭； */
        unsigned int  ifbc_core_2_gt_o : 2;  /* bit[6-7]  : [1]：1'b1 表示，IFBC的工作时钟由软件门控，1'b0 表示，IFBC的工作时钟由硬件自动控制；
                                                            [0]：1'b0 表示，IFBC工作时钟运行，1'b1 表示，IFBC工作时钟关闭； */
        unsigned int  ifbc_core_2_gt_n : 2;  /* bit[8-9]  : [1]：1'b1 表示，IFBC的工作时钟由软件门控，1'b0 表示，IFBC的工作时钟由硬件自动控制；
                                                            [0]：1'b0 表示，IFBC工作时钟运行，1'b1 表示，IFBC工作时钟关闭； */
        unsigned int  ifbc_core_4_gt   : 2;  /* bit[10-11]: [1]： 1'b1 表示，IFBC的工作时钟由软件门控，1'b0 表示，IFBC的工作时钟由硬件自动控制；
                                                            [0]：1'b0 表示，IFBC工作时钟运行，1'b1 表示，IFBC工作时钟关闭； */
        unsigned int  reserved         : 20; /* bit[12-31]: 保留 */
    } reg;
} SOC_DSS_IFBC_IFBC_CORE_GT_UNION;
#endif
#define SOC_DSS_IFBC_IFBC_CORE_GT_ifbc_core_1_gt_START    (0)
#define SOC_DSS_IFBC_IFBC_CORE_GT_ifbc_core_1_gt_END      (1)
#define SOC_DSS_IFBC_IFBC_CORE_GT_ifbc_core_2_gt_START    (2)
#define SOC_DSS_IFBC_IFBC_CORE_GT_ifbc_core_2_gt_END      (3)
#define SOC_DSS_IFBC_IFBC_CORE_GT_ifbc_core_2_gt_h_START  (4)
#define SOC_DSS_IFBC_IFBC_CORE_GT_ifbc_core_2_gt_h_END    (5)
#define SOC_DSS_IFBC_IFBC_CORE_GT_ifbc_core_2_gt_o_START  (6)
#define SOC_DSS_IFBC_IFBC_CORE_GT_ifbc_core_2_gt_o_END    (7)
#define SOC_DSS_IFBC_IFBC_CORE_GT_ifbc_core_2_gt_n_START  (8)
#define SOC_DSS_IFBC_IFBC_CORE_GT_ifbc_core_2_gt_n_END    (9)
#define SOC_DSS_IFBC_IFBC_CORE_GT_ifbc_core_4_gt_START    (10)
#define SOC_DSS_IFBC_IFBC_CORE_GT_ifbc_core_4_gt_END      (11)


/*****************************************************************************
 结构名    : SOC_DSS_IFBC_IFBC_PM_CTRL_UNION
 结构说明  : IFBC_PM_CTRL 寄存器结构定义。地址偏移量:0x002C，初值:0x80FFFFFF，宽度:32
 寄存器说明: MEM低功耗控制寄存器
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  ifbc_pm_ctrl : 32; /* bit[0-31]: [31] mem_ctrl_auto_en , 自动模式、软件配置模式选择,1自动模式，0软件配置模式 
                                                       [30] slp_mode 模式选择，1 slp模式，0 dslp模式 
                                                       [29:24] reserved
                                                       [23:21] SLP/DSLP模式t(d)slp延时寄存器 
                                                       [20:18] SLP/DSLP模式t(d)slpx延时寄存器 
                                                       [17:15] SLP/DSLP模式tx(d)slp延时寄存器 
                                                       [14:12] SLP/DSLP模式t(d)slpwk延时寄存器 
                                                       [11:9] SD模式tsd延时寄存器 
                                                       [8:6] SD模式tsdx延时寄存器 
                                                       [5:3] SD模式txsd延时寄存器 
                                                       [2:0] SD模式tsdwk延时寄存器 */
    } reg;
} SOC_DSS_IFBC_IFBC_PM_CTRL_UNION;
#endif
#define SOC_DSS_IFBC_IFBC_PM_CTRL_ifbc_pm_ctrl_START  (0)
#define SOC_DSS_IFBC_IFBC_PM_CTRL_ifbc_pm_ctrl_END    (31)


/*****************************************************************************
 结构名    : SOC_DSS_IFBC_IFBC_RD_SHADOW_UNION
 结构说明  : IFBC_RD_SHADOW 寄存器结构定义。地址偏移量:0x0030，初值:0x00000000，宽度:32
 寄存器说明: 读影子寄存器选择信号
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  ifbc_rd_shadow : 1;  /* bit[0]   : 1'b0 :读工作寄存器
                                                         1'b1 :读影子寄存器 */
        unsigned int  reserved       : 31; /* bit[1-31]: 保留 */
    } reg;
} SOC_DSS_IFBC_IFBC_RD_SHADOW_UNION;
#endif
#define SOC_DSS_IFBC_IFBC_RD_SHADOW_ifbc_rd_shadow_START  (0)
#define SOC_DSS_IFBC_IFBC_RD_SHADOW_ifbc_rd_shadow_END    (0)


/*****************************************************************************
 结构名    : SOC_DSS_IFBC_ORISE_CTL_UNION
 结构说明  : ORISE_CTL 寄存器结构定义。地址偏移量:0x0034，初值:0x00000000，宽度:32
 寄存器说明: Orise控制寄存器
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  i_param_value : 8;  /* bit[0-7]  : setting for internal */
        unsigned int  i_param_addr  : 8;  /* bit[8-15] : setting for internal */
        unsigned int  reserved      : 16; /* bit[16-31]:  */
    } reg;
} SOC_DSS_IFBC_ORISE_CTL_UNION;
#endif
#define SOC_DSS_IFBC_ORISE_CTL_i_param_value_START  (0)
#define SOC_DSS_IFBC_ORISE_CTL_i_param_value_END    (7)
#define SOC_DSS_IFBC_ORISE_CTL_i_param_addr_START   (8)
#define SOC_DSS_IFBC_ORISE_CTL_i_param_addr_END     (15)


/*****************************************************************************
 结构名    : SOC_DSS_IFBC_ORSISE_DEBUG0_UNION
 结构说明  : ORSISE_DEBUG0 寄存器结构定义。地址偏移量:0x0038，初值:0x00000000，宽度:32
 寄存器说明: Orise debug寄存器
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  orise_debug_l : 32; /* bit[0-31]: debug */
    } reg;
} SOC_DSS_IFBC_ORSISE_DEBUG0_UNION;
#endif
#define SOC_DSS_IFBC_ORSISE_DEBUG0_orise_debug_l_START  (0)
#define SOC_DSS_IFBC_ORSISE_DEBUG0_orise_debug_l_END    (31)


/*****************************************************************************
 结构名    : SOC_DSS_IFBC_ORSISE_DEBUG1_UNION
 结构说明  : ORSISE_DEBUG1 寄存器结构定义。地址偏移量:0x003C，初值:0x00000000，宽度:32
 寄存器说明: Orise debug寄存器
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  orise_debug_h : 32; /* bit[0-31]: debug */
    } reg;
} SOC_DSS_IFBC_ORSISE_DEBUG1_UNION;
#endif
#define SOC_DSS_IFBC_ORSISE_DEBUG1_orise_debug_h_START  (0)
#define SOC_DSS_IFBC_ORSISE_DEBUG1_orise_debug_h_END    (31)


/*****************************************************************************
 结构名    : SOC_DSS_IFBC_rsp_comp_test_UNION
 结构说明  : rsp_comp_test 寄存器结构定义。地址偏移量:0x0040，初值:0x00000000，宽度:32
 寄存器说明: RSP测试信号
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  rsp_comp_test : 4;  /* bit[0-3] : RSP测试信号，默认为0 */
        unsigned int  reserved      : 28; /* bit[4-31]: 保留 */
    } reg;
} SOC_DSS_IFBC_rsp_comp_test_UNION;
#endif
#define SOC_DSS_IFBC_rsp_comp_test_rsp_comp_test_START  (0)
#define SOC_DSS_IFBC_rsp_comp_test_rsp_comp_test_END    (3)


/*****************************************************************************
 结构名    : SOC_DSS_IFBC_IFBC_CLK_SEL_UNION
 结构说明  : IFBC_CLK_SEL 寄存器结构定义。地址偏移量:0x044，初值:0xFFFFFFFF，宽度:32
 寄存器说明: 一级模块时钟选择信号
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  ifbc_clk_sel : 32; /* bit[0-31]: 各一级模块的时钟选择信号，
                                                       1：表示强制打开时钟。
                                                       0：表示需要根据软件和硬件的时钟使能来开启或关闭时钟
                                                       bit0：用于apb；
                                                       bit1：用于reg； */
    } reg;
} SOC_DSS_IFBC_IFBC_CLK_SEL_UNION;
#endif
#define SOC_DSS_IFBC_IFBC_CLK_SEL_ifbc_clk_sel_START  (0)
#define SOC_DSS_IFBC_IFBC_CLK_SEL_ifbc_clk_sel_END    (31)


/*****************************************************************************
 结构名    : SOC_DSS_IFBC_IFBC_CLK_EN_UNION
 结构说明  : IFBC_CLK_EN 寄存器结构定义。地址偏移量:0x048，初值:0xFFFFFFFF，宽度:32
 寄存器说明: 一级模块时钟使能信号
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  ifbc_clk_en : 32; /* bit[0-31]: 各一级模块的软件时钟使能信号
                                                      1：表示软件时钟使能有效，允许硬件开钟
                                                      0：表示软件时钟使能无效，禁止硬件开钟
                                                      保留 */
    } reg;
} SOC_DSS_IFBC_IFBC_CLK_EN_UNION;
#endif
#define SOC_DSS_IFBC_IFBC_CLK_EN_ifbc_clk_en_START  (0)
#define SOC_DSS_IFBC_IFBC_CLK_EN_ifbc_clk_en_END    (31)


/*****************************************************************************
 结构名    : SOC_DSS_IFBC_IFBC_PAD_UNION
 结构说明  : IFBC_PAD 寄存器结构定义。地址偏移量:0x004C，初值:0x00000000，宽度:32
 寄存器说明: PAD寄存器
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  num_pad  : 3;  /* bit[0-2] : 末尾padding的像素数目 */
        unsigned int  reserved : 29; /* bit[3-31]: 保留 */
    } reg;
} SOC_DSS_IFBC_IFBC_PAD_UNION;
#endif
#define SOC_DSS_IFBC_IFBC_PAD_num_pad_START   (0)
#define SOC_DSS_IFBC_IFBC_PAD_num_pad_END     (2)


/*****************************************************************************
 结构名    : SOC_DSS_IFBC_REG_DEFAULT_UNION
 结构说明  : REG_DEFAULT 寄存器结构定义。地址偏移量:0x0050，初值:0x00000000，宽度:32
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
} SOC_DSS_IFBC_REG_DEFAULT_UNION;
#endif
#define SOC_DSS_IFBC_REG_DEFAULT_reg_default_START  (0)
#define SOC_DSS_IFBC_REG_DEFAULT_reg_default_END    (0)






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

#endif /* end of soc_dss_ifbc_interface.h */
