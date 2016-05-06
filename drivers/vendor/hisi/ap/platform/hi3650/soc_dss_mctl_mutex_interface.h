/******************************************************************************

                 版权所有 (C), 2001-2015, 华为技术有限公司

 ******************************************************************************
  文 件 名   : soc_dss_mctl_mutex_interface.h
  版 本 号   : 初稿
  作    者   : Excel2Code
  生成日期   : 2015-03-10 11:20:10
  最近修改   :
  功能描述   : 接口头文件
  函数列表   :
  修改历史   :
  1.日    期   : 2015年3月10日
    作    者   : fWX220878
    修改内容   : 从《Hi3650V100 SOC寄存器手册_DSS_MCTL_MUTEX.xml》自动生成

******************************************************************************/

/*****************************************************************************
  1 其他头文件包含
*****************************************************************************/

#ifndef __SOC_DSS_MCTL_MUTEX_INTERFACE_H__
#define __SOC_DSS_MCTL_MUTEX_INTERFACE_H__

#ifdef __cplusplus
    #if __cplusplus
        extern "C" {
    #endif
#endif



/*****************************************************************************
  2 宏定义
*****************************************************************************/

/****************************************************************************
                     (1/1) reg_MCTL_MUTEX
 ****************************************************************************/
/* 寄存器说明：主控使能寄存器
   位域定义UNION结构:  SOC_DSS_MCTL_MUTEX_CTL_EN_UNION */
#define SOC_DSS_MCTL_MUTEX_CTL_EN_ADDR(base)          ((base) + (0x0000))

/* 寄存器说明：MUTEX控制寄存器
   位域定义UNION结构:  SOC_DSS_MCTL_MUTEX_CTL_MUTEX_UNION */
#define SOC_DSS_MCTL_MUTEX_CTL_MUTEX_ADDR(base)       ((base) + (0x0004))

/* 寄存器说明：MUTEX状态寄存器
   位域定义UNION结构:  SOC_DSS_MCTL_MUTEX_CTL_MUTEX_STATUS_UNION */
#define SOC_DSS_MCTL_MUTEX_CTL_MUTEX_STATUS_ADDR(base) ((base) + (0x0008))

/* 寄存器说明：ITF选择寄存器
   位域定义UNION结构:  SOC_DSS_MCTL_MUTEX_CTL_MUTEX_ITF_UNION */
#define SOC_DSS_MCTL_MUTEX_CTL_MUTEX_ITF_ADDR(base)   ((base) + (0x000C))

/* 寄存器说明：DBUF选择寄存器
   位域定义UNION结构:  SOC_DSS_MCTL_MUTEX_CTL_MUTEX_DBUF_UNION */
#define SOC_DSS_MCTL_MUTEX_CTL_MUTEX_DBUF_ADDR(base)  ((base) + (0x0010))

/* 寄存器说明：OV0后的scf选择寄存器
   位域定义UNION结构:  SOC_DSS_MCTL_MUTEX_CTL_MUTEX_SCF_UNION */
#define SOC_DSS_MCTL_MUTEX_CTL_MUTEX_SCF_ADDR(base)   ((base) + (0x0014))

/* 寄存器说明：OV的选择寄存器
   位域定义UNION结构:  SOC_DSS_MCTL_MUTEX_CTL_MUTEX_OV_UNION */
#define SOC_DSS_MCTL_MUTEX_CTL_MUTEX_OV_ADDR(base)    ((base) + (0x0018))

/* 寄存器说明：WCH0选择寄存器
   位域定义UNION结构:  SOC_DSS_MCTL_MUTEX_CTL_MUTEX_WCH0_UNION */
#define SOC_DSS_MCTL_MUTEX_CTL_MUTEX_WCH0_ADDR(base)  ((base) + (0x0020))

/* 寄存器说明：WCH1的选择寄存器
   位域定义UNION结构:  SOC_DSS_MCTL_MUTEX_CTL_MUTEX_WCH1_UNION */
#define SOC_DSS_MCTL_MUTEX_CTL_MUTEX_WCH1_ADDR(base)  ((base) + (0x0024))

/* 寄存器说明：RCH0的选择寄存器
   位域定义UNION结构:  SOC_DSS_MCTL_MUTEX_CTL_MUTEX_RCH0_UNION */
#define SOC_DSS_MCTL_MUTEX_CTL_MUTEX_RCH0_ADDR(base)  ((base) + (0x0030))

/* 寄存器说明：RCH1的选择寄存器
   位域定义UNION结构:  SOC_DSS_MCTL_MUTEX_CTL_MUTEX_RCH1_UNION */
#define SOC_DSS_MCTL_MUTEX_CTL_MUTEX_RCH1_ADDR(base)  ((base) + (0x0034))

/* 寄存器说明：RCH2的选择寄存器
   位域定义UNION结构:  SOC_DSS_MCTL_MUTEX_CTL_MUTEX_RCH2_UNION */
#define SOC_DSS_MCTL_MUTEX_CTL_MUTEX_RCH2_ADDR(base)  ((base) + (0x0038))

/* 寄存器说明：RCH3的选择寄存器
   位域定义UNION结构:  SOC_DSS_MCTL_MUTEX_CTL_MUTEX_RCH3_UNION */
#define SOC_DSS_MCTL_MUTEX_CTL_MUTEX_RCH3_ADDR(base)  ((base) + (0x003C))

/* 寄存器说明：RCH4的选择寄存器
   位域定义UNION结构:  SOC_DSS_MCTL_MUTEX_CTL_MUTEX_RCH4_UNION */
#define SOC_DSS_MCTL_MUTEX_CTL_MUTEX_RCH4_ADDR(base)  ((base) + (0x0040))

/* 寄存器说明：RCH5的选择寄存器
   位域定义UNION结构:  SOC_DSS_MCTL_MUTEX_CTL_MUTEX_RCH5_UNION */
#define SOC_DSS_MCTL_MUTEX_CTL_MUTEX_RCH5_ADDR(base)  ((base) + (0x0044))

/* 寄存器说明：RCH6的选择寄存器
   位域定义UNION结构:  SOC_DSS_MCTL_MUTEX_CTL_MUTEX_RCH6_UNION */
#define SOC_DSS_MCTL_MUTEX_CTL_MUTEX_RCH6_ADDR(base)  ((base) + (0x0048))

/* 寄存器说明：RCH7的选择寄存器
   位域定义UNION结构:  SOC_DSS_MCTL_MUTEX_CTL_MUTEX_RCH7_UNION */
#define SOC_DSS_MCTL_MUTEX_CTL_MUTEX_RCH7_ADDR(base)  ((base) + (0x004C))

/* 寄存器说明：CTL TOP寄存器
   位域定义UNION结构:  SOC_DSS_MCTL_MUTEX_CTL_TOP_UNION */
#define SOC_DSS_MCTL_MUTEX_CTL_TOP_ADDR(base)         ((base) + (0x0050))

/* 寄存器说明：MOD配置刷新状态
   位域定义UNION结构:  SOC_DSS_MCTL_MUTEX_CTL_FLUSH_STATUS_UNION */
#define SOC_DSS_MCTL_MUTEX_CTL_FLUSH_STATUS_ADDR(base) ((base) + (0x0054))

/* 寄存器说明：软件清场配置
   位域定义UNION结构:  SOC_DSS_MCTL_MUTEX_CTL_CLEAR_UNION */
#define SOC_DSS_MCTL_MUTEX_CTL_CLEAR_ADDR(base)       ((base) + (0x0058))

/* 寄存器说明：Clear ACK超时配置寄存器
   位域定义UNION结构:  SOC_DSS_MCTL_MUTEX_CTL_CACK_TOUT_UNION */
#define SOC_DSS_MCTL_MUTEX_CTL_CACK_TOUT_ADDR(base)   ((base) + (0x0060))

/* 寄存器说明：MUTEX超时配置寄存器
   位域定义UNION结构:  SOC_DSS_MCTL_MUTEX_CTL_MUTEX_TOUT_UNION */
#define SOC_DSS_MCTL_MUTEX_CTL_MUTEX_TOUT_ADDR(base)  ((base) + (0x0064))

/* 寄存器说明：主控状态
   位域定义UNION结构:  SOC_DSS_MCTL_MUTEX_CTL_STATUS_UNION */
#define SOC_DSS_MCTL_MUTEX_CTL_STATUS_ADDR(base)      ((base) + (0x0068))

/* 寄存器说明：主控中断使能
   位域定义UNION结构:  SOC_DSS_MCTL_MUTEX_CTL_INTEN_UNION */
#define SOC_DSS_MCTL_MUTEX_CTL_INTEN_ADDR(base)       ((base) + (0x006C))

/* 寄存器说明：一级模块时钟选择信号
   位域定义UNION结构:  SOC_DSS_MCTL_MUTEX_CTL_CLK_SEL_UNION */
#define SOC_DSS_MCTL_MUTEX_CTL_CLK_SEL_ADDR(base)     ((base) + (0x0080))

/* 寄存器说明：一级模块时钟使能信号
   位域定义UNION结构:  SOC_DSS_MCTL_MUTEX_CTL_CLK_EN_UNION */
#define SOC_DSS_MCTL_MUTEX_CTL_CLK_EN_ADDR(base)      ((base) + (0x0084))

/* 寄存器说明：可维可测寄存器
   位域定义UNION结构:  SOC_DSS_MCTL_MUTEX_CTL_DBG_UNION */
#define SOC_DSS_MCTL_MUTEX_CTL_DBG_ADDR(base)         ((base) + (0x00E0))





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
                     (1/1) reg_MCTL_MUTEX
 ****************************************************************************/
/*****************************************************************************
 结构名    : SOC_DSS_MCTL_MUTEX_CTL_EN_UNION
 结构说明  : CTL_EN 寄存器结构定义。地址偏移量:0x0000，初值:0x00000000，宽度:32
 寄存器说明: 主控使能寄存器
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  ctl_en   : 1;  /* bit[0]   : 1'b1 : CTL使能
                                                   1'b0 : CTL禁止 */
        unsigned int  reserved : 31; /* bit[1-31]: 保留 */
    } reg;
} SOC_DSS_MCTL_MUTEX_CTL_EN_UNION;
#endif
#define SOC_DSS_MCTL_MUTEX_CTL_EN_ctl_en_START    (0)
#define SOC_DSS_MCTL_MUTEX_CTL_EN_ctl_en_END      (0)


/*****************************************************************************
 结构名    : SOC_DSS_MCTL_MUTEX_CTL_MUTEX_UNION
 结构说明  : CTL_MUTEX 寄存器结构定义。地址偏移量:0x0004，初值:0x00000000，宽度:32
 寄存器说明: MUTEX控制寄存器
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  ctl_mutex_sw : 1;  /* bit[0]   : 1'b1 : 软件申请锁定配置在当前MUTEX的module
                                                       1'b0 : reserved */
        unsigned int  reserved     : 31; /* bit[1-31]: 保留 */
    } reg;
} SOC_DSS_MCTL_MUTEX_CTL_MUTEX_UNION;
#endif
#define SOC_DSS_MCTL_MUTEX_CTL_MUTEX_ctl_mutex_sw_START  (0)
#define SOC_DSS_MCTL_MUTEX_CTL_MUTEX_ctl_mutex_sw_END    (0)


/*****************************************************************************
 结构名    : SOC_DSS_MCTL_MUTEX_CTL_MUTEX_STATUS_UNION
 结构说明  : CTL_MUTEX_STATUS 寄存器结构定义。地址偏移量:0x0008，初值:0x00000000，宽度:32
 寄存器说明: MUTEX状态寄存器
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  ctl_mutex_status : 1;  /* bit[0]   : mutex当前状态
                                                           1'b1 : 软件已锁定配置在当前MUTEX的module
                                                           1'b0 : reserved
                                                           复位值：0x0 */
        unsigned int  reserved         : 31; /* bit[1-31]: 保留 */
    } reg;
} SOC_DSS_MCTL_MUTEX_CTL_MUTEX_STATUS_UNION;
#endif
#define SOC_DSS_MCTL_MUTEX_CTL_MUTEX_STATUS_ctl_mutex_status_START  (0)
#define SOC_DSS_MCTL_MUTEX_CTL_MUTEX_STATUS_ctl_mutex_status_END    (0)


/*****************************************************************************
 结构名    : SOC_DSS_MCTL_MUTEX_CTL_MUTEX_ITF_UNION
 结构说明  : CTL_MUTEX_ITF 寄存器结构定义。地址偏移量:0x000C，初值:0x00000000，宽度:32
 寄存器说明: ITF选择寄存器
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  ctl_mutex_itf : 2;  /* bit[0-1] : 当前module状态
                                                        1'b1：module被选定在当前CTL
                                                        1'b0：reserved
                                                        [1:0]
                                                         2'h1:itf0 dpp ifbc
                                                         2'h2,itf1
                                                         2'h3,2'h0: 无效  */
        unsigned int  reserved      : 30; /* bit[2-31]: 保留 */
    } reg;
} SOC_DSS_MCTL_MUTEX_CTL_MUTEX_ITF_UNION;
#endif
#define SOC_DSS_MCTL_MUTEX_CTL_MUTEX_ITF_ctl_mutex_itf_START  (0)
#define SOC_DSS_MCTL_MUTEX_CTL_MUTEX_ITF_ctl_mutex_itf_END    (1)


/*****************************************************************************
 结构名    : SOC_DSS_MCTL_MUTEX_CTL_MUTEX_DBUF_UNION
 结构说明  : CTL_MUTEX_DBUF 寄存器结构定义。地址偏移量:0x0010，初值:0x00000000，宽度:32
 寄存器说明: DBUF选择寄存器
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  ctl_mutex_dbuf : 2;  /* bit[0-1] : 当前module状态
                                                          2'h1:dbuf0被选定在当前CTL
                                                          2'h2,dbuf1被选定在当前CTL
                                                          2'h3,2'h0: 无效  */
        unsigned int  reserved       : 30; /* bit[2-31]: 保留 */
    } reg;
} SOC_DSS_MCTL_MUTEX_CTL_MUTEX_DBUF_UNION;
#endif
#define SOC_DSS_MCTL_MUTEX_CTL_MUTEX_DBUF_ctl_mutex_dbuf_START  (0)
#define SOC_DSS_MCTL_MUTEX_CTL_MUTEX_DBUF_ctl_mutex_dbuf_END    (1)


/*****************************************************************************
 结构名    : SOC_DSS_MCTL_MUTEX_CTL_MUTEX_SCF_UNION
 结构说明  : CTL_MUTEX_SCF 寄存器结构定义。地址偏移量:0x0014，初值:0x00000000，宽度:32
 寄存器说明: OV0后的scf选择寄存器
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  ctl_mutex_scf : 1;  /* bit[0]   : 当前module状态
                                                        1'b1：scf 被选定在当前CTL
                                                        1'b0：reserved  */
        unsigned int  reserved      : 31; /* bit[1-31]: 保留 */
    } reg;
} SOC_DSS_MCTL_MUTEX_CTL_MUTEX_SCF_UNION;
#endif
#define SOC_DSS_MCTL_MUTEX_CTL_MUTEX_SCF_ctl_mutex_scf_START  (0)
#define SOC_DSS_MCTL_MUTEX_CTL_MUTEX_SCF_ctl_mutex_scf_END    (0)


/*****************************************************************************
 结构名    : SOC_DSS_MCTL_MUTEX_CTL_MUTEX_OV_UNION
 结构说明  : CTL_MUTEX_OV 寄存器结构定义。地址偏移量:0x0018，初值:0x00000000，宽度:32
 寄存器说明: OV的选择寄存器
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  ctl_mutex_ov : 4;  /* bit[0-3] : 当前module状态
                                                        4'h1:ov0被选定在当前CTL,
                                                        4'h2:ov1被选定在当前CTL,
                                                        4'h4:ov2被选定在当前CTL,
                                                        4'h8:ov3被选定在当前CTL,
                                                        other 无效 */
        unsigned int  reserved     : 28; /* bit[4-31]: 保留 */
    } reg;
} SOC_DSS_MCTL_MUTEX_CTL_MUTEX_OV_UNION;
#endif
#define SOC_DSS_MCTL_MUTEX_CTL_MUTEX_OV_ctl_mutex_ov_START  (0)
#define SOC_DSS_MCTL_MUTEX_CTL_MUTEX_OV_ctl_mutex_ov_END    (3)


/*****************************************************************************
 结构名    : SOC_DSS_MCTL_MUTEX_CTL_MUTEX_WCH0_UNION
 结构说明  : CTL_MUTEX_WCH0 寄存器结构定义。地址偏移量:0x0020，初值:0x00000000，宽度:32
 寄存器说明: WCH0选择寄存器
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  ctl_mutex_wch0 : 1;  /* bit[0]   : 当前module状态
                                                         1'b1：wch0被选定在当前CTL
                                                         1'b0：reserved */
        unsigned int  reserved       : 31; /* bit[1-31]: 保留 */
    } reg;
} SOC_DSS_MCTL_MUTEX_CTL_MUTEX_WCH0_UNION;
#endif
#define SOC_DSS_MCTL_MUTEX_CTL_MUTEX_WCH0_ctl_mutex_wch0_START  (0)
#define SOC_DSS_MCTL_MUTEX_CTL_MUTEX_WCH0_ctl_mutex_wch0_END    (0)


/*****************************************************************************
 结构名    : SOC_DSS_MCTL_MUTEX_CTL_MUTEX_WCH1_UNION
 结构说明  : CTL_MUTEX_WCH1 寄存器结构定义。地址偏移量:0x0024，初值:0x00000000，宽度:32
 寄存器说明: WCH1的选择寄存器
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  ctl_mutex_wch1 : 1;  /* bit[0]   : 当前module状态
                                                         1'b1：wch1被选定在当前CTL
                                                         1'b0：reserved */
        unsigned int  reserved       : 31; /* bit[1-31]: 保留 */
    } reg;
} SOC_DSS_MCTL_MUTEX_CTL_MUTEX_WCH1_UNION;
#endif
#define SOC_DSS_MCTL_MUTEX_CTL_MUTEX_WCH1_ctl_mutex_wch1_START  (0)
#define SOC_DSS_MCTL_MUTEX_CTL_MUTEX_WCH1_ctl_mutex_wch1_END    (0)


/*****************************************************************************
 结构名    : SOC_DSS_MCTL_MUTEX_CTL_MUTEX_RCH0_UNION
 结构说明  : CTL_MUTEX_RCH0 寄存器结构定义。地址偏移量:0x0030，初值:0x00000000，宽度:32
 寄存器说明: RCH0的选择寄存器
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  ctl_mutex_rch0 : 1;  /* bit[0]   : 当前module状态
                                                         1'b1：rch0被选定在当前CTL
                                                         1'b0：reserved */
        unsigned int  reserved       : 31; /* bit[1-31]: 保留 */
    } reg;
} SOC_DSS_MCTL_MUTEX_CTL_MUTEX_RCH0_UNION;
#endif
#define SOC_DSS_MCTL_MUTEX_CTL_MUTEX_RCH0_ctl_mutex_rch0_START  (0)
#define SOC_DSS_MCTL_MUTEX_CTL_MUTEX_RCH0_ctl_mutex_rch0_END    (0)


/*****************************************************************************
 结构名    : SOC_DSS_MCTL_MUTEX_CTL_MUTEX_RCH1_UNION
 结构说明  : CTL_MUTEX_RCH1 寄存器结构定义。地址偏移量:0x0034，初值:0x00000000，宽度:32
 寄存器说明: RCH1的选择寄存器
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  ctl_mutex_rch1 : 1;  /* bit[0]   : 当前module状态
                                                         1'b1：rch1被选定在当前CTL
                                                         1'b0：reserved */
        unsigned int  reserved       : 31; /* bit[1-31]: 保留 */
    } reg;
} SOC_DSS_MCTL_MUTEX_CTL_MUTEX_RCH1_UNION;
#endif
#define SOC_DSS_MCTL_MUTEX_CTL_MUTEX_RCH1_ctl_mutex_rch1_START  (0)
#define SOC_DSS_MCTL_MUTEX_CTL_MUTEX_RCH1_ctl_mutex_rch1_END    (0)


/*****************************************************************************
 结构名    : SOC_DSS_MCTL_MUTEX_CTL_MUTEX_RCH2_UNION
 结构说明  : CTL_MUTEX_RCH2 寄存器结构定义。地址偏移量:0x0038，初值:0x00000000，宽度:32
 寄存器说明: RCH2的选择寄存器
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  ctl_mutex_rch2 : 1;  /* bit[0]   : 当前module状态
                                                         1'b1：rch2被选定在当前CTL
                                                         1'b0：reserved */
        unsigned int  reserved       : 31; /* bit[1-31]: 保留 */
    } reg;
} SOC_DSS_MCTL_MUTEX_CTL_MUTEX_RCH2_UNION;
#endif
#define SOC_DSS_MCTL_MUTEX_CTL_MUTEX_RCH2_ctl_mutex_rch2_START  (0)
#define SOC_DSS_MCTL_MUTEX_CTL_MUTEX_RCH2_ctl_mutex_rch2_END    (0)


/*****************************************************************************
 结构名    : SOC_DSS_MCTL_MUTEX_CTL_MUTEX_RCH3_UNION
 结构说明  : CTL_MUTEX_RCH3 寄存器结构定义。地址偏移量:0x003C，初值:0x00000000，宽度:32
 寄存器说明: RCH3的选择寄存器
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  ctl_mutex_rch3 : 1;  /* bit[0]   : 当前module状态
                                                         1'b1：rch3被选定在当前CTL
                                                         1'b0：reserved */
        unsigned int  reserved       : 31; /* bit[1-31]: 保留 */
    } reg;
} SOC_DSS_MCTL_MUTEX_CTL_MUTEX_RCH3_UNION;
#endif
#define SOC_DSS_MCTL_MUTEX_CTL_MUTEX_RCH3_ctl_mutex_rch3_START  (0)
#define SOC_DSS_MCTL_MUTEX_CTL_MUTEX_RCH3_ctl_mutex_rch3_END    (0)


/*****************************************************************************
 结构名    : SOC_DSS_MCTL_MUTEX_CTL_MUTEX_RCH4_UNION
 结构说明  : CTL_MUTEX_RCH4 寄存器结构定义。地址偏移量:0x0040，初值:0x00000000，宽度:32
 寄存器说明: RCH4的选择寄存器
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  ctl_mutex_rch4 : 1;  /* bit[0]   : 当前module状态
                                                         1'b1：rch4被选定在当前CTL
                                                         1'b0：reserved */
        unsigned int  reserved       : 31; /* bit[1-31]: 保留 */
    } reg;
} SOC_DSS_MCTL_MUTEX_CTL_MUTEX_RCH4_UNION;
#endif
#define SOC_DSS_MCTL_MUTEX_CTL_MUTEX_RCH4_ctl_mutex_rch4_START  (0)
#define SOC_DSS_MCTL_MUTEX_CTL_MUTEX_RCH4_ctl_mutex_rch4_END    (0)


/*****************************************************************************
 结构名    : SOC_DSS_MCTL_MUTEX_CTL_MUTEX_RCH5_UNION
 结构说明  : CTL_MUTEX_RCH5 寄存器结构定义。地址偏移量:0x0044，初值:0x00000000，宽度:32
 寄存器说明: RCH5的选择寄存器
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  ctl_mutex_rch5 : 1;  /* bit[0]   : 当前module状态
                                                         1'b1：rch5被选定在当前CTL
                                                         1'b0：reserved */
        unsigned int  reserved       : 31; /* bit[1-31]: 保留 */
    } reg;
} SOC_DSS_MCTL_MUTEX_CTL_MUTEX_RCH5_UNION;
#endif
#define SOC_DSS_MCTL_MUTEX_CTL_MUTEX_RCH5_ctl_mutex_rch5_START  (0)
#define SOC_DSS_MCTL_MUTEX_CTL_MUTEX_RCH5_ctl_mutex_rch5_END    (0)


/*****************************************************************************
 结构名    : SOC_DSS_MCTL_MUTEX_CTL_MUTEX_RCH6_UNION
 结构说明  : CTL_MUTEX_RCH6 寄存器结构定义。地址偏移量:0x0048，初值:0x00000000，宽度:32
 寄存器说明: RCH6的选择寄存器
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  ctl_mutex_rch6 : 1;  /* bit[0]   : 当前module状态
                                                         1'b1：rch6被选定在当前CTL
                                                         1'b0：reserved */
        unsigned int  reserved       : 31; /* bit[1-31]: 保留 */
    } reg;
} SOC_DSS_MCTL_MUTEX_CTL_MUTEX_RCH6_UNION;
#endif
#define SOC_DSS_MCTL_MUTEX_CTL_MUTEX_RCH6_ctl_mutex_rch6_START  (0)
#define SOC_DSS_MCTL_MUTEX_CTL_MUTEX_RCH6_ctl_mutex_rch6_END    (0)


/*****************************************************************************
 结构名    : SOC_DSS_MCTL_MUTEX_CTL_MUTEX_RCH7_UNION
 结构说明  : CTL_MUTEX_RCH7 寄存器结构定义。地址偏移量:0x004C，初值:0x00000000，宽度:32
 寄存器说明: RCH7的选择寄存器
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  ctl_mutex_rch7 : 1;  /* bit[0]   : 当前module状态
                                                         1'b1：rch7被选定在当前CTL
                                                         1'b0：reserved */
        unsigned int  reserved       : 31; /* bit[1-31]: 保留 */
    } reg;
} SOC_DSS_MCTL_MUTEX_CTL_MUTEX_RCH7_UNION;
#endif
#define SOC_DSS_MCTL_MUTEX_CTL_MUTEX_RCH7_ctl_mutex_rch7_START  (0)
#define SOC_DSS_MCTL_MUTEX_CTL_MUTEX_RCH7_ctl_mutex_rch7_END    (0)


/*****************************************************************************
 结构名    : SOC_DSS_MCTL_MUTEX_CTL_TOP_UNION
 结构说明  : CTL_TOP 寄存器结构定义。地址偏移量:0x0050，初值:0x00000008，宽度:32
 寄存器说明: CTL TOP寄存器
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  ctl_sof_sel    : 2;  /* bit[0-1] : 选择MUTEX的模式
                                                         0x1：single模式
                                                         0x2：ITF0 自刷新模式
                                                         0x3：ITF1 自刷新模式
                                                         其他，无输出 */
        unsigned int  ctl_frm_st_sel : 1;  /* bit[2]   : 帧启动信号选择：
                                                         0:frame_start 做帧启动信号;
                                                         1:frame_end 做帧启动信号.
                                                         复位值0x0 */
        unsigned int  ctl_block_mode : 1;  /* bit[3]   : 保留 */
        unsigned int  reserved       : 28; /* bit[4-31]: 保留 */
    } reg;
} SOC_DSS_MCTL_MUTEX_CTL_TOP_UNION;
#endif
#define SOC_DSS_MCTL_MUTEX_CTL_TOP_ctl_sof_sel_START     (0)
#define SOC_DSS_MCTL_MUTEX_CTL_TOP_ctl_sof_sel_END       (1)
#define SOC_DSS_MCTL_MUTEX_CTL_TOP_ctl_frm_st_sel_START  (2)
#define SOC_DSS_MCTL_MUTEX_CTL_TOP_ctl_frm_st_sel_END    (2)
#define SOC_DSS_MCTL_MUTEX_CTL_TOP_ctl_block_mode_START  (3)
#define SOC_DSS_MCTL_MUTEX_CTL_TOP_ctl_block_mode_END    (3)


/*****************************************************************************
 结构名    : SOC_DSS_MCTL_MUTEX_CTL_FLUSH_STATUS_UNION
 结构说明  : CTL_FLUSH_STATUS 寄存器结构定义。地址偏移量:0x0054，初值:0x00000000，宽度:32
 寄存器说明: MOD配置刷新状态
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  ctl_mod_flush_status : 32; /* bit[0-31]: 保留 */
    } reg;
} SOC_DSS_MCTL_MUTEX_CTL_FLUSH_STATUS_UNION;
#endif
#define SOC_DSS_MCTL_MUTEX_CTL_FLUSH_STATUS_ctl_mod_flush_status_START  (0)
#define SOC_DSS_MCTL_MUTEX_CTL_FLUSH_STATUS_ctl_mod_flush_status_END    (31)


/*****************************************************************************
 结构名    : SOC_DSS_MCTL_MUTEX_CTL_CLEAR_UNION
 结构说明  : CTL_CLEAR 寄存器结构定义。地址偏移量:0x0058，初值:0x00000000，宽度:32
 寄存器说明: 软件清场配置
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  ctl_sw_clr : 1;  /* bit[0]   : 软件配置一次，对当前MUTEX，以及当前mutex控制的内的module完成一次清除动作 */
        unsigned int  reserved   : 31; /* bit[1-31]: 保留 */
    } reg;
} SOC_DSS_MCTL_MUTEX_CTL_CLEAR_UNION;
#endif
#define SOC_DSS_MCTL_MUTEX_CTL_CLEAR_ctl_sw_clr_START  (0)
#define SOC_DSS_MCTL_MUTEX_CTL_CLEAR_ctl_sw_clr_END    (0)


/*****************************************************************************
 结构名    : SOC_DSS_MCTL_MUTEX_CTL_CACK_TOUT_UNION
 结构说明  : CTL_CACK_TOUT 寄存器结构定义。地址偏移量:0x0060，初值:0x000003FF，宽度:32
 寄存器说明: Clear ACK超时配置寄存器
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  ctl_cack_tout : 16; /* bit[0-15] : CTL通路返回clear ack超时计数寄存器 */
        unsigned int  reserved      : 16; /* bit[16-31]: 保留 */
    } reg;
} SOC_DSS_MCTL_MUTEX_CTL_CACK_TOUT_UNION;
#endif
#define SOC_DSS_MCTL_MUTEX_CTL_CACK_TOUT_ctl_cack_tout_START  (0)
#define SOC_DSS_MCTL_MUTEX_CTL_CACK_TOUT_ctl_cack_tout_END    (15)


/*****************************************************************************
 结构名    : SOC_DSS_MCTL_MUTEX_CTL_MUTEX_TOUT_UNION
 结构说明  : CTL_MUTEX_TOUT 寄存器结构定义。地址偏移量:0x0064，初值:0x000003FF，宽度:32
 寄存器说明: MUTEX超时配置寄存器
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  ctl_mutex_tout : 16; /* bit[0-15] : mutex超时计数，从SOF到来，到所有寄存器reload结束的时间。 */
        unsigned int  reserved       : 16; /* bit[16-31]: 保留 */
    } reg;
} SOC_DSS_MCTL_MUTEX_CTL_MUTEX_TOUT_UNION;
#endif
#define SOC_DSS_MCTL_MUTEX_CTL_MUTEX_TOUT_ctl_mutex_tout_START  (0)
#define SOC_DSS_MCTL_MUTEX_CTL_MUTEX_TOUT_ctl_mutex_tout_END    (15)


/*****************************************************************************
 结构名    : SOC_DSS_MCTL_MUTEX_CTL_STATUS_UNION
 结构说明  : CTL_STATUS 寄存器结构定义。地址偏移量:0x0068，初值:0x00000000，宽度:32
 寄存器说明: 主控状态
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  ctl_status : 3;  /* bit[0-2] : [0] : 清场超时
                                                     [1] : mutex超时
                                                     [2] : all reload update完成 */
        unsigned int  reserved   : 29; /* bit[3-31]: 保留 */
    } reg;
} SOC_DSS_MCTL_MUTEX_CTL_STATUS_UNION;
#endif
#define SOC_DSS_MCTL_MUTEX_CTL_STATUS_ctl_status_START  (0)
#define SOC_DSS_MCTL_MUTEX_CTL_STATUS_ctl_status_END    (2)


/*****************************************************************************
 结构名    : SOC_DSS_MCTL_MUTEX_CTL_INTEN_UNION
 结构说明  : CTL_INTEN 寄存器结构定义。地址偏移量:0x006C，初值:0x00000000，宽度:32
 寄存器说明: 主控中断使能
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  ctl_inten : 3;  /* bit[0-2] : [0] : 清场超时中断使能
                                                    [1] : mutex超时中断使能
                                                    [2] : all reload update完成中断 */
        unsigned int  reserved  : 29; /* bit[3-31]: 保留 */
    } reg;
} SOC_DSS_MCTL_MUTEX_CTL_INTEN_UNION;
#endif
#define SOC_DSS_MCTL_MUTEX_CTL_INTEN_ctl_inten_START  (0)
#define SOC_DSS_MCTL_MUTEX_CTL_INTEN_ctl_inten_END    (2)


/*****************************************************************************
 结构名    : SOC_DSS_MCTL_MUTEX_CTL_CLK_SEL_UNION
 结构说明  : CTL_CLK_SEL 寄存器结构定义。地址偏移量:0x0080，初值:0xFFFFFFFF，宽度:32
 寄存器说明: 一级模块时钟选择信号
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  ctl_clk_sel : 32; /* bit[0-31]: 各一级模块的时钟选择信号，
                                                      1：表示强制打开时钟。
                                                      0：表示需要根据软件和硬件的时钟使能来开启或关闭时钟
                                                      [0] reg
                                                      [1] ctl/mutex
                                                      [31:2]：reserved */
    } reg;
} SOC_DSS_MCTL_MUTEX_CTL_CLK_SEL_UNION;
#endif
#define SOC_DSS_MCTL_MUTEX_CTL_CLK_SEL_ctl_clk_sel_START  (0)
#define SOC_DSS_MCTL_MUTEX_CTL_CLK_SEL_ctl_clk_sel_END    (31)


/*****************************************************************************
 结构名    : SOC_DSS_MCTL_MUTEX_CTL_CLK_EN_UNION
 结构说明  : CTL_CLK_EN 寄存器结构定义。地址偏移量:0x0084，初值:0xFFFFFFFF，宽度:32
 寄存器说明: 一级模块时钟使能信号
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  ctl_clk_en : 32; /* bit[0-31]: 各一级模块的软件时钟使能信号
                                                     1：表示软件时钟使能有效，允许硬件开钟
                                                     0：表示软件时钟使能无效，禁止硬件开钟
                                                     [0] reg
                                                     [1] ctl/mutex
                                                     [31:2]：reserved */
    } reg;
} SOC_DSS_MCTL_MUTEX_CTL_CLK_EN_UNION;
#endif
#define SOC_DSS_MCTL_MUTEX_CTL_CLK_EN_ctl_clk_en_START  (0)
#define SOC_DSS_MCTL_MUTEX_CTL_CLK_EN_ctl_clk_en_END    (31)


/*****************************************************************************
 结构名    : SOC_DSS_MCTL_MUTEX_CTL_DBG_UNION
 结构说明  : CTL_DBG 寄存器结构定义。地址偏移量:0x00E0，初值:0x00002600，宽度:32
 寄存器说明: 可维可测寄存器
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  ctl_dbg  : 24; /* bit[0-23] : [23] 1'b1：仅支持soft clear
                                                    [22] 1'b1：默认single mode不发clear，当该bit置1，single mode根据帧尾选择发出clear。
                                                    [18:16] reserved；
                                                    [21] 1'b1：holdclear ack信号，保持到下一帧帧头结束。
                                                    [20] 1'b1：cmdlist的帧event list选来自mctl的。
                                                     1'b0：cmdlist的帧event list选来自ldi的。
                                                    [19] 1'b1：支持unflow和帧尾clear同时生效。
                                                    [15] 1'b1：收到unflow立刻发起clear。
                                                     1'b0：收到unflow，记录，帧尾发起clear。
                                                    [14:13] 帧结束信号延时
                                                    [12:10] clear ack延时
                                                    [9:7] 帧起始信号延时
                                                    [6] 屏蔽single mode不启动主状态机模式
                                                    [5] 1'b1： 帧起始信号根据itf所在的ctl选择。
                                                     1'b0： 帧起始信号根据模式选择（ctl_sof_sel)
                                                    [4:3] 2'b*1： ctl_abt_if状态
                                                     2'b10： abt_ctl_if状态
                                                     2'b00： flush状态
                                                    [2] 1'b1：auto mode时，不根据帧头锁ctl_mutex_mod
                                                     1'b0：auto mode时，根据帧头锁ctl_mutex_mod
                                                    [1] reserved；
                                                    [0] 1'b1：每帧都启动clear
                                                    
                                                    典型场景推荐配置
                                                    1）cpu配置的在线，保持默认值
                                                    2）cmdlist的在线统一配置为：58A620
                                                    3）离线，保持默认值 */
        unsigned int  reserved : 8;  /* bit[24-31]: 保留 */
    } reg;
} SOC_DSS_MCTL_MUTEX_CTL_DBG_UNION;
#endif
#define SOC_DSS_MCTL_MUTEX_CTL_DBG_ctl_dbg_START   (0)
#define SOC_DSS_MCTL_MUTEX_CTL_DBG_ctl_dbg_END     (23)






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

#endif /* end of soc_dss_mctl_mutex_interface.h */
