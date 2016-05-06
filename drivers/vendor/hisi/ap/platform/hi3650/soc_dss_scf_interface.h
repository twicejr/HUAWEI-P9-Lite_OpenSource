/******************************************************************************

                 版权所有 (C), 2001-2015, 华为技术有限公司

 ******************************************************************************
  文 件 名   : soc_dss_scf_interface.h
  版 本 号   : 初稿
  作    者   : Excel2Code
  生成日期   : 2015-03-10 11:20:24
  最近修改   :
  功能描述   : 接口头文件
  函数列表   :
  修改历史   :
  1.日    期   : 2015年3月10日
    作    者   : fWX220878
    修改内容   : 从《Hi3650V100 SOC寄存器手册_DSS_SCF.xml》自动生成

******************************************************************************/

/*****************************************************************************
  1 其他头文件包含
*****************************************************************************/

#ifndef __SOC_DSS_SCF_INTERFACE_H__
#define __SOC_DSS_SCF_INTERFACE_H__

#ifdef __cplusplus
    #if __cplusplus
        extern "C" {
    #endif
#endif



/*****************************************************************************
  2 宏定义
*****************************************************************************/

/****************************************************************************
                     (1/1) reg_SCF
 ****************************************************************************/
/* 寄存器说明：水平丢点缩放使能
   位域定义UNION结构:  SOC_DSS_SCF_SCF_EN_HSCL_STR_UNION */
#define SOC_DSS_SCF_SCF_EN_HSCL_STR_ADDR(base)        ((base) + (0x0000))

/* 寄存器说明：垂直丢点缩放使能
   位域定义UNION结构:  SOC_DSS_SCF_SCF_EN_VSCL_STR_UNION */
#define SOC_DSS_SCF_SCF_EN_VSCL_STR_ADDR(base)        ((base) + (0x0004))

/* 寄存器说明：水平和垂直滤波以及video处理模式配置
   位域定义UNION结构:  SOC_DSS_SCF_SCF_H_V_ORDER_UNION */
#define SOC_DSS_SCF_SCF_H_V_ORDER_ADDR(base)          ((base) + (0x0008))

/* 寄存器说明：输入宽高
   位域定义UNION结构:  SOC_DSS_SCF_SCF_INPUT_WIDTH_HEIGHT_UNION */
#define SOC_DSS_SCF_SCF_INPUT_WIDTH_HEIGHT_ADDR(base) ((base) + (0x0010))

/* 寄存器说明：输出宽高
   位域定义UNION结构:  SOC_DSS_SCF_SCF_OUTPUT_WIDTH_HEIGHT_UNION */
#define SOC_DSS_SCF_SCF_OUTPUT_WIDTH_HEIGHT_ADDR(base) ((base) + (0x0014))

/* 寄存器说明：缩放系数MEM低功耗控制
   位域定义UNION结构:  SOC_DSS_SCF_SCF_COEF_MEM_CTRL_UNION */
#define SOC_DSS_SCF_SCF_COEF_MEM_CTRL_ADDR(base)      ((base) + (0x0018))

/* 寄存器说明：水平缩放使能信号
   位域定义UNION结构:  SOC_DSS_SCF_SCF_EN_HSCL_UNION */
#define SOC_DSS_SCF_SCF_EN_HSCL_ADDR(base)            ((base) + (0x001C))

/* 寄存器说明：垂直缩放使能信号
   位域定义UNION结构:  SOC_DSS_SCF_SCF_EN_VSCL_UNION */
#define SOC_DSS_SCF_SCF_EN_VSCL_ADDR(base)            ((base) + (0x0020))

/* 寄存器说明：水平初始相位
   位域定义UNION结构:  SOC_DSS_SCF_SCF_ACC_HSCL_UNION */
#define SOC_DSS_SCF_SCF_ACC_HSCL_ADDR(base)           ((base) + (0x0024))

/* 寄存器说明：通道1水平相位的相对偏移量
   位域定义UNION结构:  SOC_DSS_SCF_SCF_ACC_HSCL1_UNION */
#define SOC_DSS_SCF_SCF_ACC_HSCL1_ADDR(base)          ((base) + (0x0028))

/* 寄存器说明：水平缩放比例
   位域定义UNION结构:  SOC_DSS_SCF_SCF_INC_HSCL_UNION */
#define SOC_DSS_SCF_SCF_INC_HSCL_ADDR(base)           ((base) + (0x0034))

/* 寄存器说明：垂直初始相位
   位域定义UNION结构:  SOC_DSS_SCF_SCF_ACC_VSCL_UNION */
#define SOC_DSS_SCF_SCF_ACC_VSCL_ADDR(base)           ((base) + (0x0038))

/* 寄存器说明：通道1垂直相位的相对偏移量
   位域定义UNION结构:  SOC_DSS_SCF_SCF_ACC_VSCL1_UNION */
#define SOC_DSS_SCF_SCF_ACC_VSCL1_ADDR(base)          ((base) + (0x003C))

/* 寄存器说明：垂直缩放比例
   位域定义UNION结构:  SOC_DSS_SCF_SCF_INC_VSCL_UNION */
#define SOC_DSS_SCF_SCF_INC_VSCL_ADDR(base)           ((base) + (0x0048))

/* 寄存器说明：软复位寄存器
   位域定义UNION结构:  SOC_DSS_SCF_SCF_EN_NONLINEAR_UNION */
#define SOC_DSS_SCF_SCF_EN_NONLINEAR_ADDR(base)       ((base) + (0x004C))

/* 寄存器说明：过冲处理使能信号
   位域定义UNION结构:  SOC_DSS_SCF_SCF_EN_MMP_UNION */
#define SOC_DSS_SCF_SCF_EN_MMP_ADDR(base)             ((base) + (0x007C))

/* 寄存器说明：水平滤波器的内部状态寄存器0
   位域定义UNION结构:  SOC_DSS_SCF_SCF_DB_H0_UNION */
#define SOC_DSS_SCF_SCF_DB_H0_ADDR(base)              ((base) + (0x0080))

/* 寄存器说明：水平滤波器的内部状态寄存器1
   位域定义UNION结构:  SOC_DSS_SCF_SCF_DB_H1_UNION */
#define SOC_DSS_SCF_SCF_DB_H1_ADDR(base)              ((base) + (0x0084))

/* 寄存器说明：垂直滤波器的内部状态寄存器0
   位域定义UNION结构:  SOC_DSS_SCF_SCF_DB_V0_UNION */
#define SOC_DSS_SCF_SCF_DB_V0_ADDR(base)              ((base) + (0x0088))

/* 寄存器说明：垂直滤波器的内部状态寄存器1
   位域定义UNION结构:  SOC_DSS_SCF_SCF_DB_V1_UNION */
#define SOC_DSS_SCF_SCF_DB_V1_ADDR(base)              ((base) + (0x008C))

/* 寄存器说明：Line Buf MEM低功耗控制
   位域定义UNION结构:  SOC_DSS_SCF_SCF_LB_MEM_CTRL_UNION */
#define SOC_DSS_SCF_SCF_LB_MEM_CTRL_ADDR(base)        ((base) + (0x0090))

/* 寄存器说明：读寄存器选择
   位域定义UNION结构:  SOC_DSS_SCF_SCF_RD_SHADOW_UNION */
#define SOC_DSS_SCF_SCF_RD_SHADOW_ADDR(base)          ((base) + (0x00F0))

/* 寄存器说明：一级模块时钟选择信号
   位域定义UNION结构:  SOC_DSS_SCF_SCF_CLK_SEL_UNION */
#define SOC_DSS_SCF_SCF_CLK_SEL_ADDR(base)            ((base) + (0x00F8))

/* 寄存器说明：一级模块时钟使能信号
   位域定义UNION结构:  SOC_DSS_SCF_SCF_CLK_EN_UNION */
#define SOC_DSS_SCF_SCF_CLK_EN_ADDR(base)             ((base) + (0x00FC))

/* 寄存器说明：模块影子寄存器恢复到默认值
   位域定义UNION结构:  SOC_DSS_SCF_REG_DEFAULT_UNION */
#define SOC_DSS_SCF_REG_DEFAULT_ADDR(base)            ((base) + (0x00F4))

/* 寄存器说明：SCF 6tap滤波系数
   位域定义UNION结构:  SOC_DSS_SCF_V0_SCF_VIDEO_6TAP_COEF_UNION */
#define SOC_DSS_SCF_V0_SCF_VIDEO_6TAP_COEF_ADDR(base) ((base) + (0x1000))

/* 寄存器说明：SCF 5tap滤波系数
   位域定义UNION结构:  SOC_DSS_SCF_V0_SCF_VIDEO_5TAP_COEF_UNION */
#define SOC_DSS_SCF_V0_SCF_VIDEO_5TAP_COEF_ADDR(base) ((base) + (0x3000))

/* 寄存器说明：SCF 4tap滤波系数
   位域定义UNION结构:  SOC_DSS_SCF_V0_SCF_VIDEO_4TAP_COEF_UNION */
#define SOC_DSS_SCF_V0_SCF_VIDEO_4TAP_COEF_ADDR(base) ((base) + (0x3800))





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
                     (1/1) reg_SCF
 ****************************************************************************/
/*****************************************************************************
 结构名    : SOC_DSS_SCF_SCF_EN_HSCL_STR_UNION
 结构说明  : SCF_EN_HSCL_STR 寄存器结构定义。地址偏移量:0x0000，初值:0x00000000，宽度:32
 寄存器说明: 水平丢点缩放使能
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  scf_en_hscl_str   : 1;  /* bit[0]   : 水平丢点缩放使能，仅当EN_HSCL有效时有效
                                                            0：水平滤波缩放
                                                            1：水平丢点缩放 */
        unsigned int  scf_en_hscl_str_a : 1;  /* bit[1]   : alpha水平丢点缩放使能，仅当EN_HSCL有效时有效
                                                            0：水平滤波缩放
                                                            1：水平丢点缩放 */
        unsigned int  reserved          : 30; /* bit[2-31]: 保留 */
    } reg;
} SOC_DSS_SCF_SCF_EN_HSCL_STR_UNION;
#endif
#define SOC_DSS_SCF_SCF_EN_HSCL_STR_scf_en_hscl_str_START    (0)
#define SOC_DSS_SCF_SCF_EN_HSCL_STR_scf_en_hscl_str_END      (0)
#define SOC_DSS_SCF_SCF_EN_HSCL_STR_scf_en_hscl_str_a_START  (1)
#define SOC_DSS_SCF_SCF_EN_HSCL_STR_scf_en_hscl_str_a_END    (1)


/*****************************************************************************
 结构名    : SOC_DSS_SCF_SCF_EN_VSCL_STR_UNION
 结构说明  : SCF_EN_VSCL_STR 寄存器结构定义。地址偏移量:0x0004，初值:0x00000000，宽度:32
 寄存器说明: 垂直丢点缩放使能
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  scf_en_vscl_str   : 1;  /* bit[0]   : 垂直丢点缩放使能，仅当EN_VSCL有效时有效
                                                            0：垂直滤波缩放
                                                            1：垂直丢点缩放
                                                            如果考虑节省带宽，可在RDMA模块作垂直方向的整数倍丢点缩小 */
        unsigned int  scf_en_vscl_str_a : 1;  /* bit[1]   : alpha垂直丢点缩放使能，仅当EN_VSCL有效时有效
                                                            0：垂直滤波缩放
                                                            1：垂直丢点缩放
                                                            如果考虑节省带宽，可在RDMA模块作垂直方向的整数倍丢点缩小 */
        unsigned int  reserved          : 30; /* bit[2-31]: 保留 */
    } reg;
} SOC_DSS_SCF_SCF_EN_VSCL_STR_UNION;
#endif
#define SOC_DSS_SCF_SCF_EN_VSCL_STR_scf_en_vscl_str_START    (0)
#define SOC_DSS_SCF_SCF_EN_VSCL_STR_scf_en_vscl_str_END      (0)
#define SOC_DSS_SCF_SCF_EN_VSCL_STR_scf_en_vscl_str_a_START  (1)
#define SOC_DSS_SCF_SCF_EN_VSCL_STR_scf_en_vscl_str_a_END    (1)


/*****************************************************************************
 结构名    : SOC_DSS_SCF_SCF_H_V_ORDER_UNION
 结构说明  : SCF_H_V_ORDER 寄存器结构定义。地址偏移量:0x0008，初值:0x00000000，宽度:32
 寄存器说明: 水平和垂直滤波以及video处理模式配置
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  scf_h_v_order : 1;  /* bit[0]   : 水平和垂直滤波的顺序
                                                        0：水平先做
                                                        1：水平后做 */
        unsigned int  reserved      : 31; /* bit[1-31]: 保留 */
    } reg;
} SOC_DSS_SCF_SCF_H_V_ORDER_UNION;
#endif
#define SOC_DSS_SCF_SCF_H_V_ORDER_scf_h_v_order_START  (0)
#define SOC_DSS_SCF_SCF_H_V_ORDER_scf_h_v_order_END    (0)


/*****************************************************************************
 结构名    : SOC_DSS_SCF_SCF_INPUT_WIDTH_HEIGHT_UNION
 结构说明  : SCF_INPUT_WIDTH_HEIGHT 寄存器结构定义。地址偏移量:0x0010，初值:0x00000000，宽度:32
 寄存器说明: 输入宽高
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  scf_input_height : 13; /* bit[0-12] : 实际输入高度 - 1
                                                            V5版本不需要配置 */
        unsigned int  reserved_0       : 3;  /* bit[13-15]: 保留 */
        unsigned int  scf_input_width  : 13; /* bit[16-28]: 实际输入宽度 - 1
                                                            V5版本不需要配置 */
        unsigned int  reserved_1       : 3;  /* bit[29-31]: 保留 */
    } reg;
} SOC_DSS_SCF_SCF_INPUT_WIDTH_HEIGHT_UNION;
#endif
#define SOC_DSS_SCF_SCF_INPUT_WIDTH_HEIGHT_scf_input_height_START  (0)
#define SOC_DSS_SCF_SCF_INPUT_WIDTH_HEIGHT_scf_input_height_END    (12)
#define SOC_DSS_SCF_SCF_INPUT_WIDTH_HEIGHT_scf_input_width_START   (16)
#define SOC_DSS_SCF_SCF_INPUT_WIDTH_HEIGHT_scf_input_width_END     (28)


/*****************************************************************************
 结构名    : SOC_DSS_SCF_SCF_OUTPUT_WIDTH_HEIGHT_UNION
 结构说明  : SCF_OUTPUT_WIDTH_HEIGHT 寄存器结构定义。地址偏移量:0x0014，初值:0x00000000，宽度:32
 寄存器说明: 输出宽高
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  scf_output_height : 13; /* bit[0-12] : 实际输出高度 - 1
                                                             V5版本不需要配置 */
        unsigned int  reserved_0        : 3;  /* bit[13-15]: 保留 */
        unsigned int  scf_output_width  : 13; /* bit[16-28]: 实际输出宽度 - 1;
                                                             V5版本不需要配置 */
        unsigned int  reserved_1        : 3;  /* bit[29-31]: 保留 */
    } reg;
} SOC_DSS_SCF_SCF_OUTPUT_WIDTH_HEIGHT_UNION;
#endif
#define SOC_DSS_SCF_SCF_OUTPUT_WIDTH_HEIGHT_scf_output_height_START  (0)
#define SOC_DSS_SCF_SCF_OUTPUT_WIDTH_HEIGHT_scf_output_height_END    (12)
#define SOC_DSS_SCF_SCF_OUTPUT_WIDTH_HEIGHT_scf_output_width_START   (16)
#define SOC_DSS_SCF_SCF_OUTPUT_WIDTH_HEIGHT_scf_output_width_END     (28)


/*****************************************************************************
 结构名    : SOC_DSS_SCF_SCF_COEF_MEM_CTRL_UNION
 结构说明  : SCF_COEF_MEM_CTRL 寄存器结构定义。地址偏移量:0x0018，初值:0x00000000，宽度:32
 寄存器说明: 缩放系数MEM低功耗控制
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  scf_hcoef_mem_ctrl : 4;  /* bit[0-3] : 调试用寄存器，水平滤波系数LUT软件配置：
                                                             [3] mem_ctrl_auto_en , 自动模式、软件配置模式选择,0自动模式，1软件配置模式 
                                                             [2]: 软件配置模式下有效，为1表示进入Shut Down模式
                                                             [1]: 软件配置模式下有效，为1表示进入Deep Sleep模式
                                                             [0]: 软件配置模式下有效，为1表示进入Sleep模式 */
        unsigned int  scf_vcoef_mem_ctrl : 4;  /* bit[4-7] : 调试用寄存器，垂直滤波系数LUT软件配置：
                                                             [3] mem_ctrl_auto_en , 自动模式、软件配置模式选择,0自动模式，1软件配置模式 
                                                             [2]: 软件配置模式下有效，为1表示进入Shut Down模式
                                                             [1]: 软件配置模式下有效，为1表示进入Deep Sleep模式
                                                             [0]: 软件配置模式下有效，为1表示进入Sleep模式 */
        unsigned int  reserved           : 24; /* bit[8-31]: 保留 */
    } reg;
} SOC_DSS_SCF_SCF_COEF_MEM_CTRL_UNION;
#endif
#define SOC_DSS_SCF_SCF_COEF_MEM_CTRL_scf_hcoef_mem_ctrl_START  (0)
#define SOC_DSS_SCF_SCF_COEF_MEM_CTRL_scf_hcoef_mem_ctrl_END    (3)
#define SOC_DSS_SCF_SCF_COEF_MEM_CTRL_scf_vcoef_mem_ctrl_START  (4)
#define SOC_DSS_SCF_SCF_COEF_MEM_CTRL_scf_vcoef_mem_ctrl_END    (7)


/*****************************************************************************
 结构名    : SOC_DSS_SCF_SCF_EN_HSCL_UNION
 结构说明  : SCF_EN_HSCL 寄存器结构定义。地址偏移量:0x001C，初值:0x00000000，宽度:32
 寄存器说明: 水平缩放使能信号
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  scf_en_hscl_en : 1;  /* bit[0]   : 水平缩放使能信号 */
        unsigned int  reserved       : 31; /* bit[1-31]: 保留 */
    } reg;
} SOC_DSS_SCF_SCF_EN_HSCL_UNION;
#endif
#define SOC_DSS_SCF_SCF_EN_HSCL_scf_en_hscl_en_START  (0)
#define SOC_DSS_SCF_SCF_EN_HSCL_scf_en_hscl_en_END    (0)


/*****************************************************************************
 结构名    : SOC_DSS_SCF_SCF_EN_VSCL_UNION
 结构说明  : SCF_EN_VSCL 寄存器结构定义。地址偏移量:0x0020，初值:0x00000000，宽度:32
 寄存器说明: 垂直缩放使能信号
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  scf_en_vscl_en    : 1;  /* bit[0]   : 垂直缩放使能信号 */
        unsigned int  scf_out_buffer_en : 1;  /* bit[1]   : 当垂直方向的输出图像高度小于等于输入图像高度时，使用scf的行buffer作输出缓存使能配置寄存器：
                                                            1.使用行buffer作输出缓存；
                                                            0.不使用行buffer作输出缓存 */
        unsigned int  reserved          : 30; /* bit[2-31]: 保留 */
    } reg;
} SOC_DSS_SCF_SCF_EN_VSCL_UNION;
#endif
#define SOC_DSS_SCF_SCF_EN_VSCL_scf_en_vscl_en_START     (0)
#define SOC_DSS_SCF_SCF_EN_VSCL_scf_en_vscl_en_END       (0)
#define SOC_DSS_SCF_SCF_EN_VSCL_scf_out_buffer_en_START  (1)
#define SOC_DSS_SCF_SCF_EN_VSCL_scf_out_buffer_en_END    (1)


/*****************************************************************************
 结构名    : SOC_DSS_SCF_SCF_ACC_HSCL_UNION
 结构说明  : SCF_ACC_HSCL 寄存器结构定义。地址偏移量:0x0024，初值:0x00000000，宽度:32
 寄存器说明: 水平初始相位
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  scf_acc_hscl : 30; /* bit[0-29] : 水平初始相位，决定水平SC从什么位置开始做缩放。
                                                        其中低18位为小数部分，高12位为整数部分。 */
        unsigned int  reserved     : 2;  /* bit[30-31]: 保留 */
    } reg;
} SOC_DSS_SCF_SCF_ACC_HSCL_UNION;
#endif
#define SOC_DSS_SCF_SCF_ACC_HSCL_scf_acc_hscl_START  (0)
#define SOC_DSS_SCF_SCF_ACC_HSCL_scf_acc_hscl_END    (29)


/*****************************************************************************
 结构名    : SOC_DSS_SCF_SCF_ACC_HSCL1_UNION
 结构说明  : SCF_ACC_HSCL1 寄存器结构定义。地址偏移量:0x0028，初值:0x00000000，宽度:32
 寄存器说明: 通道1水平相位的相对偏移量
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  scf_acc_hscl1 : 19; /* bit[0-18] : 通道1水平相位的相对偏移量，相对于ACC_HSCL；
                                                         V5版本此处配置为UV分量相对于Y分量的相位偏移，且有效位宽为17bit有符号数 */
        unsigned int  reserved      : 13; /* bit[19-31]: 保留 */
    } reg;
} SOC_DSS_SCF_SCF_ACC_HSCL1_UNION;
#endif
#define SOC_DSS_SCF_SCF_ACC_HSCL1_scf_acc_hscl1_START  (0)
#define SOC_DSS_SCF_SCF_ACC_HSCL1_scf_acc_hscl1_END    (18)


/*****************************************************************************
 结构名    : SOC_DSS_SCF_SCF_INC_HSCL_UNION
 结构说明  : SCF_INC_HSCL 寄存器结构定义。地址偏移量:0x0034，初值:0x00005000，宽度:32
 寄存器说明: 水平缩放比例
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  scf_inc_hscl : 24; /* bit[0-23] : 水平缩放比例，计算公式为
                                                        hinc = (input_width*262144-acc_hscl)/(output_width)
                                                        其中input_width 和output_width分别为输入图像的宽度和输出图像宽度的寄存器配置值，注意，因为寄存器的配置值比实际的图像小1， 例如如果输入图像宽度是1920，那么input_width的寄存器配置为1919，acc_hscl是SCF配置的寄存器值“水平初始相位”
                                                        
                                                        hinc的低18比特为ratio的小数部分，高6比特为整数部分。整数部分6比特，支持64倍以下（不含64倍）的缩小。放大的倍数，原理上只受18比特的小数部分的限制，可达2的18次方；实际上受到宽度寄存器的限制，最多放大到8X1024. */
        unsigned int  reserved     : 8;  /* bit[24-31]: 保留 */
    } reg;
} SOC_DSS_SCF_SCF_INC_HSCL_UNION;
#endif
#define SOC_DSS_SCF_SCF_INC_HSCL_scf_inc_hscl_START  (0)
#define SOC_DSS_SCF_SCF_INC_HSCL_scf_inc_hscl_END    (23)


/*****************************************************************************
 结构名    : SOC_DSS_SCF_SCF_ACC_VSCL_UNION
 结构说明  : SCF_ACC_VSCL 寄存器结构定义。地址偏移量:0x0038，初值:0x00000000，宽度:32
 寄存器说明: 垂直初始相位
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  scf_acc_vscl : 30; /* bit[0-29] : 垂直初始相位，决定垂直SC从什么位置开始做缩放，其中低18位为小数部分，高12位为整数部分。 */
        unsigned int  reserved     : 2;  /* bit[30-31]: 保留 */
    } reg;
} SOC_DSS_SCF_SCF_ACC_VSCL_UNION;
#endif
#define SOC_DSS_SCF_SCF_ACC_VSCL_scf_acc_vscl_START  (0)
#define SOC_DSS_SCF_SCF_ACC_VSCL_scf_acc_vscl_END    (29)


/*****************************************************************************
 结构名    : SOC_DSS_SCF_SCF_ACC_VSCL1_UNION
 结构说明  : SCF_ACC_VSCL1 寄存器结构定义。地址偏移量:0x003C，初值:0x00000000，宽度:32
 寄存器说明: 通道1垂直相位的相对偏移量
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  scf_acc_vscl1 : 19; /* bit[0-18] : 通道1垂直相位的相对偏移量，相对于ACC_VSCL；
                                                         V5版本为配置色度UV分量相对于Y分量的偏移值，且有效位宽为17bit有符号数 */
        unsigned int  reserved      : 13; /* bit[19-31]: 保留 */
    } reg;
} SOC_DSS_SCF_SCF_ACC_VSCL1_UNION;
#endif
#define SOC_DSS_SCF_SCF_ACC_VSCL1_scf_acc_vscl1_START  (0)
#define SOC_DSS_SCF_SCF_ACC_VSCL1_scf_acc_vscl1_END    (18)


/*****************************************************************************
 结构名    : SOC_DSS_SCF_SCF_INC_VSCL_UNION
 结构说明  : SCF_INC_VSCL 寄存器结构定义。地址偏移量:0x0048，初值:0x00005000，宽度:32
 寄存器说明: 垂直缩放比例
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  scf_inc_vscl : 24; /* bit[0-23] : 垂直缩放比例，计算公式为
                                                        INPUT_HEIGHT*262144/OUTPUT_HEIGHT
                                                        软件计算，配置该寄存器 这部分作废
                                                        
                                                        约束更新： 
                                                        inc_vscl的计算公式更新为
                                                         inc_vscl=floor( (262144*(intput_height_reg)+131072-acc_vscl)/(output_height_reg))
                                                        寄存器配置值output_height为实际输出高度-1
                                                        寄存器配置值input_height为实际输入高度-1
                                                        floor()为向下取整
                                                        acc_vscl是SCF配置的寄存器值“垂直初始相位” */
        unsigned int  reserved     : 8;  /* bit[24-31]: 保留 */
    } reg;
} SOC_DSS_SCF_SCF_INC_VSCL_UNION;
#endif
#define SOC_DSS_SCF_SCF_INC_VSCL_scf_inc_vscl_START  (0)
#define SOC_DSS_SCF_SCF_INC_VSCL_scf_inc_vscl_END    (23)


/*****************************************************************************
 结构名    : SOC_DSS_SCF_SCF_EN_NONLINEAR_UNION
 结构说明  : SCF_EN_NONLINEAR 寄存器结构定义。地址偏移量:0x004C，初值:0x00000000，宽度:32
 寄存器说明: 软复位寄存器
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  scf_sw_rst : 1;  /* bit[0]   : scf模块软复位配置寄存器，1有效 */
        unsigned int  reserved   : 31; /* bit[1-31]: 保留 */
    } reg;
} SOC_DSS_SCF_SCF_EN_NONLINEAR_UNION;
#endif
#define SOC_DSS_SCF_SCF_EN_NONLINEAR_scf_sw_rst_START  (0)
#define SOC_DSS_SCF_SCF_EN_NONLINEAR_scf_sw_rst_END    (0)


/*****************************************************************************
 结构名    : SOC_DSS_SCF_SCF_EN_MMP_UNION
 结构说明  : SCF_EN_MMP 寄存器结构定义。地址偏移量:0x007C，初值:0x00000001，宽度:32
 寄存器说明: 过冲处理使能信号
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  scf_en_mmp : 1;  /* bit[0]   : 过冲处理使能信号，1表示使能，0表示不使能 */
        unsigned int  reserved   : 31; /* bit[1-31]: 保留 */
    } reg;
} SOC_DSS_SCF_SCF_EN_MMP_UNION;
#endif
#define SOC_DSS_SCF_SCF_EN_MMP_scf_en_mmp_START  (0)
#define SOC_DSS_SCF_SCF_EN_MMP_scf_en_mmp_END    (0)


/*****************************************************************************
 结构名    : SOC_DSS_SCF_SCF_DB_H0_UNION
 结构说明  : SCF_DB_H0 寄存器结构定义。地址偏移量:0x0080，初值:0x00000000，宽度:32
 寄存器说明: 水平滤波器的内部状态寄存器0
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  scf_debug_h0 : 32; /* bit[0-31]:  */
    } reg;
} SOC_DSS_SCF_SCF_DB_H0_UNION;
#endif
#define SOC_DSS_SCF_SCF_DB_H0_scf_debug_h0_START  (0)
#define SOC_DSS_SCF_SCF_DB_H0_scf_debug_h0_END    (31)


/*****************************************************************************
 结构名    : SOC_DSS_SCF_SCF_DB_H1_UNION
 结构说明  : SCF_DB_H1 寄存器结构定义。地址偏移量:0x0084，初值:0x00000000，宽度:32
 寄存器说明: 水平滤波器的内部状态寄存器1
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  scf_debug_h1 : 32; /* bit[0-31]:  */
    } reg;
} SOC_DSS_SCF_SCF_DB_H1_UNION;
#endif
#define SOC_DSS_SCF_SCF_DB_H1_scf_debug_h1_START  (0)
#define SOC_DSS_SCF_SCF_DB_H1_scf_debug_h1_END    (31)


/*****************************************************************************
 结构名    : SOC_DSS_SCF_SCF_DB_V0_UNION
 结构说明  : SCF_DB_V0 寄存器结构定义。地址偏移量:0x0088，初值:0x00000000，宽度:32
 寄存器说明: 垂直滤波器的内部状态寄存器0
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  scf_debug_v0 : 32; /* bit[0-31]:  */
    } reg;
} SOC_DSS_SCF_SCF_DB_V0_UNION;
#endif
#define SOC_DSS_SCF_SCF_DB_V0_scf_debug_v0_START  (0)
#define SOC_DSS_SCF_SCF_DB_V0_scf_debug_v0_END    (31)


/*****************************************************************************
 结构名    : SOC_DSS_SCF_SCF_DB_V1_UNION
 结构说明  : SCF_DB_V1 寄存器结构定义。地址偏移量:0x008C，初值:0x00000000，宽度:32
 寄存器说明: 垂直滤波器的内部状态寄存器1
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  scf_debug_v1 : 32; /* bit[0-31]:  */
    } reg;
} SOC_DSS_SCF_SCF_DB_V1_UNION;
#endif
#define SOC_DSS_SCF_SCF_DB_V1_scf_debug_v1_START  (0)
#define SOC_DSS_SCF_SCF_DB_V1_scf_debug_v1_END    (31)


/*****************************************************************************
 结构名    : SOC_DSS_SCF_SCF_LB_MEM_CTRL_UNION
 结构说明  : SCF_LB_MEM_CTRL 寄存器结构定义。地址偏移量:0x0090，初值:0x00000000，宽度:32
 寄存器说明: Line Buf MEM低功耗控制
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  scf_lb_mem_ctrl : 4;  /* bit[0-3] : 调试用寄存器，对应Line Buf的MEM
                                                          [3] mem_ctrl_auto_en , 自动模式、软件配置模式选择,0自动模式，1软件配置模式 
                                                          [2]: 软件配置模式下有效，为1表示进入Shut Down模式
                                                          [1]: 软件配置模式下有效，为1表示进入Deep Sleep模式
                                                          [0]: 软件配置模式下有效，为1表示进入Sleep模式 */
        unsigned int  reserved        : 28; /* bit[4-31]: 保留 */
    } reg;
} SOC_DSS_SCF_SCF_LB_MEM_CTRL_UNION;
#endif
#define SOC_DSS_SCF_SCF_LB_MEM_CTRL_scf_lb_mem_ctrl_START  (0)
#define SOC_DSS_SCF_SCF_LB_MEM_CTRL_scf_lb_mem_ctrl_END    (3)


/*****************************************************************************
 结构名    : SOC_DSS_SCF_SCF_RD_SHADOW_UNION
 结构说明  : SCF_RD_SHADOW 寄存器结构定义。地址偏移量:0x00F0，初值:0x00000000，宽度:32
 寄存器说明: 读寄存器选择
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  scf_rd_shadow : 1;  /* bit[0]   : 读寄存器选择：
                                                        0：工作寄存器
                                                        1：影子寄存器 */
        unsigned int  reserved      : 31; /* bit[1-31]: 保留 */
    } reg;
} SOC_DSS_SCF_SCF_RD_SHADOW_UNION;
#endif
#define SOC_DSS_SCF_SCF_RD_SHADOW_scf_rd_shadow_START  (0)
#define SOC_DSS_SCF_SCF_RD_SHADOW_scf_rd_shadow_END    (0)


/*****************************************************************************
 结构名    : SOC_DSS_SCF_SCF_CLK_SEL_UNION
 结构说明  : SCF_CLK_SEL 寄存器结构定义。地址偏移量:0x00F8，初值:0xFFFFFFFF，宽度:32
 寄存器说明: 一级模块时钟选择信号
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  scf_clk_sel : 32; /* bit[0-31]: 各一级模块的时钟选择信号，
                                                      1：表示强制打开时钟。
                                                      0：表示需要根据软件和硬件的时钟使能来开启或关闭时钟
                                                      [0]:水平方向
                                                      [1]:垂直方向 */
    } reg;
} SOC_DSS_SCF_SCF_CLK_SEL_UNION;
#endif
#define SOC_DSS_SCF_SCF_CLK_SEL_scf_clk_sel_START  (0)
#define SOC_DSS_SCF_SCF_CLK_SEL_scf_clk_sel_END    (31)


/*****************************************************************************
 结构名    : SOC_DSS_SCF_SCF_CLK_EN_UNION
 结构说明  : SCF_CLK_EN 寄存器结构定义。地址偏移量:0x00FC，初值:0xFFFFFFFF，宽度:32
 寄存器说明: 一级模块时钟使能信号
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  scf_clk_en : 32; /* bit[0-31]: 各一级模块的软件时钟使能信号
                                                     1：表示软件时钟使能有效，允许硬件开钟
                                                     0：表示软件时钟使能无效，禁止硬件开钟
                                                     [0]:水平方向
                                                     [1]:垂直方向 */
    } reg;
} SOC_DSS_SCF_SCF_CLK_EN_UNION;
#endif
#define SOC_DSS_SCF_SCF_CLK_EN_scf_clk_en_START  (0)
#define SOC_DSS_SCF_SCF_CLK_EN_scf_clk_en_END    (31)


/*****************************************************************************
 结构名    : SOC_DSS_SCF_REG_DEFAULT_UNION
 结构说明  : REG_DEFAULT 寄存器结构定义。地址偏移量:0x00F4，初值:0x00000000，宽度:32
 寄存器说明: 模块影子寄存器恢复到默认值
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  reg_default : 1;  /* bit[0]   :  */
        unsigned int  reserved    : 31; /* bit[1-31]:  */
    } reg;
} SOC_DSS_SCF_REG_DEFAULT_UNION;
#endif
#define SOC_DSS_SCF_REG_DEFAULT_reg_default_START  (0)
#define SOC_DSS_SCF_REG_DEFAULT_reg_default_END    (0)


/*****************************************************************************
 结构名    : SOC_DSS_SCF_V0_SCF_VIDEO_6TAP_COEF_UNION
 结构说明  : V0_SCF_VIDEO_6TAP_COEF 寄存器结构定义。地址偏移量:0x1000，初值:0x00000000，宽度:32
 寄存器说明: SCF 6tap滤波系数
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  scf_video_6tap_coef : 32; /* bit[0-31]: 6tap缩放系数lut表的基地址，延用V3配置，地址范围0x1000～0x143F */
    } reg;
} SOC_DSS_SCF_V0_SCF_VIDEO_6TAP_COEF_UNION;
#endif
#define SOC_DSS_SCF_V0_SCF_VIDEO_6TAP_COEF_scf_video_6tap_coef_START  (0)
#define SOC_DSS_SCF_V0_SCF_VIDEO_6TAP_COEF_scf_video_6tap_coef_END    (31)


/*****************************************************************************
 结构名    : SOC_DSS_SCF_V0_SCF_VIDEO_5TAP_COEF_UNION
 结构说明  : V0_SCF_VIDEO_5TAP_COEF 寄存器结构定义。地址偏移量:0x3000，初值:0x00000000，宽度:32
 寄存器说明: SCF 5tap滤波系数
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  scf_video_5tap_coef : 32; /* bit[0-31]: 5tap缩放系数lut表的基地址，延用V3配置，地址范围0x3000～0x343F */
    } reg;
} SOC_DSS_SCF_V0_SCF_VIDEO_5TAP_COEF_UNION;
#endif
#define SOC_DSS_SCF_V0_SCF_VIDEO_5TAP_COEF_scf_video_5tap_coef_START  (0)
#define SOC_DSS_SCF_V0_SCF_VIDEO_5TAP_COEF_scf_video_5tap_coef_END    (31)


/*****************************************************************************
 结构名    : SOC_DSS_SCF_V0_SCF_VIDEO_4TAP_COEF_UNION
 结构说明  : V0_SCF_VIDEO_4TAP_COEF 寄存器结构定义。地址偏移量:0x3800，初值:0x00000000，宽度:32
 寄存器说明: SCF 4tap滤波系数
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  scf_video_4tap_coef : 32; /* bit[0-31]: 4tap缩放系数lut表的基地址，延用V3配置，地址范围0x3800～0x3A1F */
    } reg;
} SOC_DSS_SCF_V0_SCF_VIDEO_4TAP_COEF_UNION;
#endif
#define SOC_DSS_SCF_V0_SCF_VIDEO_4TAP_COEF_scf_video_4tap_coef_START  (0)
#define SOC_DSS_SCF_V0_SCF_VIDEO_4TAP_COEF_scf_video_4tap_coef_END    (31)






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

#endif /* end of soc_dss_scf_interface.h */
