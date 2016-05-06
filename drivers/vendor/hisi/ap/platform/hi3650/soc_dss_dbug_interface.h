/******************************************************************************

                 版权所有 (C), 2001-2015, 华为技术有限公司

 ******************************************************************************
  文 件 名   : soc_dss_dbug_interface.h
  版 本 号   : 初稿
  作    者   : Excel2Code
  生成日期   : 2015-03-10 11:20:01
  最近修改   :
  功能描述   : 接口头文件
  函数列表   :
  修改历史   :
  1.日    期   : 2015年3月10日
    作    者   : fWX220878
    修改内容   : 从《Hi3650V100 SOC寄存器手册_DSS_DBUG.xml》自动生成

******************************************************************************/

/*****************************************************************************
  1 其他头文件包含
*****************************************************************************/

#ifndef __SOC_DSS_DBUG_INTERFACE_H__
#define __SOC_DSS_DBUG_INTERFACE_H__

#ifdef __cplusplus
    #if __cplusplus
        extern "C" {
    #endif
#endif



/*****************************************************************************
  2 宏定义
*****************************************************************************/

/****************************************************************************
                     (1/1) reg_DBUG
 ****************************************************************************/
/* 寄存器说明：OV0的crc校验结果
   位域定义UNION结构:  SOC_DSS_DBUG_CRC_DBG_OV0_UNION */
#define SOC_DSS_DBUG_CRC_DBG_OV0_ADDR(base)           ((base) + (0x0000))

/* 寄存器说明：OV1的crc校验结果
   位域定义UNION结构:  SOC_DSS_DBUG_CRC_DBG_OV1_UNION */
#define SOC_DSS_DBUG_CRC_DBG_OV1_ADDR(base)           ((base) + (0x0004))

/* 寄存器说明：SUM的crc校验结果
   位域定义UNION结构:  SOC_DSS_DBUG_CRC_DBG_SUM_UNION */
#define SOC_DSS_DBUG_CRC_DBG_SUM_ADDR(base)           ((base) + (0x0008))

/* 寄存器说明：OV0的CRC启动使能信号
   位域定义UNION结构:  SOC_DSS_DBUG_CRC_OV0_EN_UNION */
#define SOC_DSS_DBUG_CRC_OV0_EN_ADDR(base)            ((base) + (0x000C))

/* 寄存器说明：软件读取OV0的CRC结果信号
   位域定义UNION结构:  SOC_DSS_DBUG_DSS_GLB_DBG_O_UNION */
#define SOC_DSS_DBUG_DSS_GLB_DBG_O_ADDR(base)         ((base) + (0x0010))

/* 寄存器说明：OV0的crc校验结果是否可读
   位域定义UNION结构:  SOC_DSS_DBUG_DSS_GLB_DBG_I_UNION */
#define SOC_DSS_DBUG_DSS_GLB_DBG_I_ADDR(base)         ((base) + (0x0014))

/* 寄存器说明：OV0上报的CRC校验的帧数
   位域定义UNION结构:  SOC_DSS_DBUG_CRC_OV0_FRM_UNION */
#define SOC_DSS_DBUG_CRC_OV0_FRM_ADDR(base)           ((base) + (0x0018))

/* 寄存器说明：OV1的CRC启动使能信号
   位域定义UNION结构:  SOC_DSS_DBUG_CRC_OV1_EN_UNION */
#define SOC_DSS_DBUG_CRC_OV1_EN_ADDR(base)            ((base) + (0x001C))

/* 寄存器说明：OV1上报的CRC校验的帧数
   位域定义UNION结构:  SOC_DSS_DBUG_CRC_OV1_FRM_UNION */
#define SOC_DSS_DBUG_CRC_OV1_FRM_ADDR(base)           ((base) + (0x0020))

/* 寄存器说明：SUM的CRC启动使能信号
   位域定义UNION结构:  SOC_DSS_DBUG_CRC_SUM_EN_UNION */
#define SOC_DSS_DBUG_CRC_SUM_EN_ADDR(base)            ((base) + (0x0024))

/* 寄存器说明：SUM上报的CRC校验的帧数
   位域定义UNION结构:  SOC_DSS_DBUG_CRC_SUM_FRM_UNION */
#define SOC_DSS_DBUG_CRC_SUM_FRM_ADDR(base)           ((base) + (0x0028))

/* 寄存器说明：
   位域定义UNION结构:  SOC_DSS_DBUG_REG2CTRL_LBS_EN_UNION */
#define SOC_DSS_DBUG_REG2CTRL_LBS_EN_ADDR(base)       ((base) + (0x0100))

/* 寄存器说明：
   位域定义UNION结构:  SOC_DSS_DBUG_REG2LBS_LBS_FRM_LEN_UNION */
#define SOC_DSS_DBUG_REG2LBS_LBS_FRM_LEN_ADDR(base)   ((base) + (0x0104))

/* 寄存器说明：
   位域定义UNION结构:  SOC_DSS_DBUG_DBG_BUS_MODE_UNION */
#define SOC_DSS_DBUG_DBG_BUS_MODE_ADDR(base)          ((base) + (0x0108))

/* 寄存器说明：
   位域定义UNION结构:  SOC_DSS_DBUG_REG2LBS_LBS_FRM_UNION */
#define SOC_DSS_DBUG_REG2LBS_LBS_FRM_ADDR(base)       ((base) + (0x010C))

/* 寄存器说明：
   位域定义UNION结构:  SOC_DSS_DBUG_REG2LBS_LBS_ID_UNION */
#define SOC_DSS_DBUG_REG2LBS_LBS_ID_ADDR(base)        ((base) + (0x0110))

/* 寄存器说明：
   位域定义UNION结构:  SOC_DSS_DBUG_REG2LBS_BUS_MSK_UNION */
#define SOC_DSS_DBUG_REG2LBS_BUS_MSK_ADDR(base)       ((base) + (0x0114))

/* 寄存器说明：
   位域定义UNION结构:  SOC_DSS_DBUG_REG2HEAD_DIAG_ID_UNION */
#define SOC_DSS_DBUG_REG2HEAD_DIAG_ID_ADDR(base)      ((base) + (0x0118))

/* 寄存器说明：
   位域定义UNION结构:  SOC_DSS_DBUG_REG2HEAD_HSRV_ID_UNION */
#define SOC_DSS_DBUG_REG2HEAD_HSRV_ID_ADDR(base)      ((base) + (0x011C))

/* 寄存器说明：
   位域定义UNION结构:  SOC_DSS_DBUG_REG2HEAD_LSRV_ID_UNION */
#define SOC_DSS_DBUG_REG2HEAD_LSRV_ID_ADDR(base)      ((base) + (0x0120))

/* 寄存器说明：
   位域定义UNION结构:  SOC_DSS_DBUG_REG2HEAD_SESSION_ID_UNION */
#define SOC_DSS_DBUG_REG2HEAD_SESSION_ID_ADDR(base)   ((base) + (0x0124))

/* 寄存器说明：
   位域定义UNION结构:  SOC_DSS_DBUG_REG2HEAD_MSG_TYPE_UNION */
#define SOC_DSS_DBUG_REG2HEAD_MSG_TYPE_ADDR(base)     ((base) + (0x0128))

/* 寄存器说明：
   位域定义UNION结构:  SOC_DSS_DBUG_DBG_BUS_BASE_ADDR_UNION */
#define SOC_DSS_DBUG_DBG_BUS_BASE_ADDR_ADDR(base)     ((base) + (0x012C))

/* 寄存器说明：
   位域定义UNION结构:  SOC_DSS_DBUG_DBG_BUS_END_ADDR_UNION */
#define SOC_DSS_DBUG_DBG_BUS_END_ADDR_ADDR(base)      ((base) + (0x0130))

/* 寄存器说明：
   位域定义UNION结构:  SOC_DSS_DBUG_DBG_PTR_ADDR_UNION */
#define SOC_DSS_DBUG_DBG_PTR_ADDR_ADDR(base)          ((base) + (0x0134))

/* 寄存器说明：
   位域定义UNION结构:  SOC_DSS_DBUG_DBG_BUS_TIMING_UNION */
#define SOC_DSS_DBUG_DBG_BUS_TIMING_ADDR(base)        ((base) + (0x0138))

/* 寄存器说明：
   位域定义UNION结构:  SOC_DSS_DBUG_DBG_BUS_LDI_SEL_UNION */
#define SOC_DSS_DBUG_DBG_BUS_LDI_SEL_ADDR(base)       ((base) + (0x013C))

/* 寄存器说明：
   位域定义UNION结构:  SOC_DSS_DBUG_DBG_BUS_END_UNION */
#define SOC_DSS_DBUG_DBG_BUS_END_ADDR(base)           ((base) + (0x0140))

/* 寄存器说明：
   位域定义UNION结构:  SOC_DSS_DBUG_REG2MEM_GATE_SEL_UNION */
#define SOC_DSS_DBUG_REG2MEM_GATE_SEL_ADDR(base)      ((base) + (0x0144))

/* 寄存器说明：
   位域定义UNION结构:  SOC_DSS_DBUG_SP_MEM_CTRL0_LOG_UNION */
#define SOC_DSS_DBUG_SP_MEM_CTRL0_LOG_ADDR(base)      ((base) + (0x0148))

/* 寄存器说明：MEM低功耗控制寄存器（TP）
   位域定义UNION结构:  SOC_DSS_DBUG_TP_MEM_CTRL0_UNION */
#define SOC_DSS_DBUG_TP_MEM_CTRL0_ADDR(base)          ((base) + (0x014C))

/* 寄存器说明：
   位域定义UNION结构:  SOC_DSS_DBUG_DBG_BUS_TIMING_SEL_UNION */
#define SOC_DSS_DBUG_DBG_BUS_TIMING_SEL_ADDR(base)    ((base) + (0x0150))

/* 寄存器说明：
   位域定义UNION结构:  SOC_DSS_DBUG_DSS_DBG_WPTR_UNION */
#define SOC_DSS_DBUG_DSS_DBG_WPTR_ADDR(base)          ((base) + (0x0154))





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
                     (1/1) reg_DBUG
 ****************************************************************************/
/*****************************************************************************
 结构名    : SOC_DSS_DBUG_CRC_DBG_OV0_UNION
 结构说明  : CRC_DBG_OV0 寄存器结构定义。地址偏移量:0x0000，初值:0x00000000，宽度:32
 寄存器说明: OV0的crc校验结果
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  crc_dbg_ov0 : 32; /* bit[0-31]: OV0的crc校验结果 */
    } reg;
} SOC_DSS_DBUG_CRC_DBG_OV0_UNION;
#endif
#define SOC_DSS_DBUG_CRC_DBG_OV0_crc_dbg_ov0_START  (0)
#define SOC_DSS_DBUG_CRC_DBG_OV0_crc_dbg_ov0_END    (31)


/*****************************************************************************
 结构名    : SOC_DSS_DBUG_CRC_DBG_OV1_UNION
 结构说明  : CRC_DBG_OV1 寄存器结构定义。地址偏移量:0x0004，初值:0x00000000，宽度:32
 寄存器说明: OV1的crc校验结果
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  crc_dbg_ov1 : 32; /* bit[0-31]: OV1的crc校验结果 */
    } reg;
} SOC_DSS_DBUG_CRC_DBG_OV1_UNION;
#endif
#define SOC_DSS_DBUG_CRC_DBG_OV1_crc_dbg_ov1_START  (0)
#define SOC_DSS_DBUG_CRC_DBG_OV1_crc_dbg_ov1_END    (31)


/*****************************************************************************
 结构名    : SOC_DSS_DBUG_CRC_DBG_SUM_UNION
 结构说明  : CRC_DBG_SUM 寄存器结构定义。地址偏移量:0x0008，初值:0x00000000，宽度:32
 寄存器说明: SUM的crc校验结果
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  crc_dbg_sum : 32; /* bit[0-31]: 保留 */
    } reg;
} SOC_DSS_DBUG_CRC_DBG_SUM_UNION;
#endif
#define SOC_DSS_DBUG_CRC_DBG_SUM_crc_dbg_sum_START  (0)
#define SOC_DSS_DBUG_CRC_DBG_SUM_crc_dbg_sum_END    (31)


/*****************************************************************************
 结构名    : SOC_DSS_DBUG_CRC_OV0_EN_UNION
 结构说明  : CRC_OV0_EN 寄存器结构定义。地址偏移量:0x000C，初值:0x00000000，宽度:32
 寄存器说明: OV0的CRC启动使能信号
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  crc_ov0_en : 1;  /* bit[0-0] : OV0的crc校验使能 */
        unsigned int  reserved   : 31; /* bit[1-31]: 保留 */
    } reg;
} SOC_DSS_DBUG_CRC_OV0_EN_UNION;
#endif
#define SOC_DSS_DBUG_CRC_OV0_EN_crc_ov0_en_START  (0)
#define SOC_DSS_DBUG_CRC_OV0_EN_crc_ov0_en_END    (0)


/*****************************************************************************
 结构名    : SOC_DSS_DBUG_DSS_GLB_DBG_O_UNION
 结构说明  : DSS_GLB_DBG_O 寄存器结构定义。地址偏移量:0x0010，初值:0x00000000，宽度:32
 寄存器说明: 软件读取OV0的CRC结果信号
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  dss_glb_dbg_o : 32; /* bit[0-31]: 保留 */
    } reg;
} SOC_DSS_DBUG_DSS_GLB_DBG_O_UNION;
#endif
#define SOC_DSS_DBUG_DSS_GLB_DBG_O_dss_glb_dbg_o_START  (0)
#define SOC_DSS_DBUG_DSS_GLB_DBG_O_dss_glb_dbg_o_END    (31)


/*****************************************************************************
 结构名    : SOC_DSS_DBUG_DSS_GLB_DBG_I_UNION
 结构说明  : DSS_GLB_DBG_I 寄存器结构定义。地址偏移量:0x0014，初值:0x00000000，宽度:32
 寄存器说明: OV0的crc校验结果是否可读
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  dss_glb_dbg_i : 32; /* bit[0-31]: 保留 */
    } reg;
} SOC_DSS_DBUG_DSS_GLB_DBG_I_UNION;
#endif
#define SOC_DSS_DBUG_DSS_GLB_DBG_I_dss_glb_dbg_i_START  (0)
#define SOC_DSS_DBUG_DSS_GLB_DBG_I_dss_glb_dbg_i_END    (31)


/*****************************************************************************
 结构名    : SOC_DSS_DBUG_CRC_OV0_FRM_UNION
 结构说明  : CRC_OV0_FRM 寄存器结构定义。地址偏移量:0x0018，初值:0x00000000，宽度:32
 寄存器说明: OV0上报的CRC校验的帧数
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  crc_ov0_frm : 32; /* bit[0-31]: OV0上报的CRC校验的帧数 */
    } reg;
} SOC_DSS_DBUG_CRC_OV0_FRM_UNION;
#endif
#define SOC_DSS_DBUG_CRC_OV0_FRM_crc_ov0_frm_START  (0)
#define SOC_DSS_DBUG_CRC_OV0_FRM_crc_ov0_frm_END    (31)


/*****************************************************************************
 结构名    : SOC_DSS_DBUG_CRC_OV1_EN_UNION
 结构说明  : CRC_OV1_EN 寄存器结构定义。地址偏移量:0x001C，初值:0x00000000，宽度:32
 寄存器说明: OV1的CRC启动使能信号
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  crc_ov1_en : 1;  /* bit[0-0] : OV1的CRC启动使能信号 */
        unsigned int  reserved   : 31; /* bit[1-31]: 保留 */
    } reg;
} SOC_DSS_DBUG_CRC_OV1_EN_UNION;
#endif
#define SOC_DSS_DBUG_CRC_OV1_EN_crc_ov1_en_START  (0)
#define SOC_DSS_DBUG_CRC_OV1_EN_crc_ov1_en_END    (0)


/*****************************************************************************
 结构名    : SOC_DSS_DBUG_CRC_OV1_FRM_UNION
 结构说明  : CRC_OV1_FRM 寄存器结构定义。地址偏移量:0x0020，初值:0x00000000，宽度:32
 寄存器说明: OV1上报的CRC校验的帧数
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  crc_ov1_frm : 32; /* bit[0-31]: OV1上报的CRC校验的帧数 */
    } reg;
} SOC_DSS_DBUG_CRC_OV1_FRM_UNION;
#endif
#define SOC_DSS_DBUG_CRC_OV1_FRM_crc_ov1_frm_START  (0)
#define SOC_DSS_DBUG_CRC_OV1_FRM_crc_ov1_frm_END    (31)


/*****************************************************************************
 结构名    : SOC_DSS_DBUG_CRC_SUM_EN_UNION
 结构说明  : CRC_SUM_EN 寄存器结构定义。地址偏移量:0x0024，初值:0x00000000，宽度:32
 寄存器说明: SUM的CRC启动使能信号
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  crc_sum_en : 1;  /* bit[0-0] : SUM的CRC启动使能信号 */
        unsigned int  reserved   : 31; /* bit[1-31]: 保留 */
    } reg;
} SOC_DSS_DBUG_CRC_SUM_EN_UNION;
#endif
#define SOC_DSS_DBUG_CRC_SUM_EN_crc_sum_en_START  (0)
#define SOC_DSS_DBUG_CRC_SUM_EN_crc_sum_en_END    (0)


/*****************************************************************************
 结构名    : SOC_DSS_DBUG_CRC_SUM_FRM_UNION
 结构说明  : CRC_SUM_FRM 寄存器结构定义。地址偏移量:0x0028，初值:0x00000000，宽度:32
 寄存器说明: SUM上报的CRC校验的帧数
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  crc_sum_frm : 32; /* bit[0-31]: SUM上报的CRC校验的帧数 */
    } reg;
} SOC_DSS_DBUG_CRC_SUM_FRM_UNION;
#endif
#define SOC_DSS_DBUG_CRC_SUM_FRM_crc_sum_frm_START  (0)
#define SOC_DSS_DBUG_CRC_SUM_FRM_crc_sum_frm_END    (31)


/*****************************************************************************
 结构名    : SOC_DSS_DBUG_REG2CTRL_LBS_EN_UNION
 结构说明  : REG2CTRL_LBS_EN 寄存器结构定义。地址偏移量:0x0100，初值:0x00000000，宽度:32
 寄存器说明: 
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  reg2ctrl_lbs_en : 1;  /* bit[0-0] : 采数使能信号 */
        unsigned int  reserved        : 31; /* bit[1-31]: 保留 */
    } reg;
} SOC_DSS_DBUG_REG2CTRL_LBS_EN_UNION;
#endif
#define SOC_DSS_DBUG_REG2CTRL_LBS_EN_reg2ctrl_lbs_en_START  (0)
#define SOC_DSS_DBUG_REG2CTRL_LBS_EN_reg2ctrl_lbs_en_END    (0)


/*****************************************************************************
 结构名    : SOC_DSS_DBUG_REG2LBS_LBS_FRM_LEN_UNION
 结构说明  : REG2LBS_LBS_FRM_LEN 寄存器结构定义。地址偏移量:0x0104，初值:0x00000800，宽度:32
 寄存器说明: 
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  reg2lbs_lbs_frm_len : 16; /* bit[0-15] : Bus采集数据帧长配置值，配置需满足burst8的倍数，单位byte，典型值2048 */
        unsigned int  reserved            : 16; /* bit[16-31]: 保留 */
    } reg;
} SOC_DSS_DBUG_REG2LBS_LBS_FRM_LEN_UNION;
#endif
#define SOC_DSS_DBUG_REG2LBS_LBS_FRM_LEN_reg2lbs_lbs_frm_len_START  (0)
#define SOC_DSS_DBUG_REG2LBS_LBS_FRM_LEN_reg2lbs_lbs_frm_len_END    (15)


/*****************************************************************************
 结构名    : SOC_DSS_DBUG_DBG_BUS_MODE_UNION
 结构说明  : DBG_BUS_MODE 寄存器结构定义。地址偏移量:0x0108，初值:0x00000000，宽度:32
 寄存器说明: 
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  dbg_bus_mode : 1;  /* bit[0-0] : Bus采集模式选择信号。
                                                       0：计数模式，与计数值组合使用；
                                                       1：开关模式 */
        unsigned int  reserved     : 31; /* bit[1-31]: 保留 */
    } reg;
} SOC_DSS_DBUG_DBG_BUS_MODE_UNION;
#endif
#define SOC_DSS_DBUG_DBG_BUS_MODE_dbg_bus_mode_START  (0)
#define SOC_DSS_DBUG_DBG_BUS_MODE_dbg_bus_mode_END    (0)


/*****************************************************************************
 结构名    : SOC_DSS_DBUG_REG2LBS_LBS_FRM_UNION
 结构说明  : REG2LBS_LBS_FRM 寄存器结构定义。地址偏移量:0x010C，初值:0x00000000，宽度:32
 寄存器说明: 
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  reg2lbs_lbs_frm : 16; /* bit[0-15] : 计数模式下Bus采集帧个数 */
        unsigned int  reserved        : 16; /* bit[16-31]: 保留 */
    } reg;
} SOC_DSS_DBUG_REG2LBS_LBS_FRM_UNION;
#endif
#define SOC_DSS_DBUG_REG2LBS_LBS_FRM_reg2lbs_lbs_frm_START  (0)
#define SOC_DSS_DBUG_REG2LBS_LBS_FRM_reg2lbs_lbs_frm_END    (15)


/*****************************************************************************
 结构名    : SOC_DSS_DBUG_REG2LBS_LBS_ID_UNION
 结构说明  : REG2LBS_LBS_ID 寄存器结构定义。地址偏移量:0x0110，初值:0x00000000，宽度:32
 寄存器说明: 
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  reg2lbs_lbs_id : 32; /* bit[0-31]: Bus采集数据帧ID标识 */
    } reg;
} SOC_DSS_DBUG_REG2LBS_LBS_ID_UNION;
#endif
#define SOC_DSS_DBUG_REG2LBS_LBS_ID_reg2lbs_lbs_id_START  (0)
#define SOC_DSS_DBUG_REG2LBS_LBS_ID_reg2lbs_lbs_id_END    (31)


/*****************************************************************************
 结构名    : SOC_DSS_DBUG_REG2LBS_BUS_MSK_UNION
 结构说明  : REG2LBS_BUS_MSK 寄存器结构定义。地址偏移量:0x0114，初值:0x00000000，宽度:32
 寄存器说明: 
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  reg2lbs_bus_msk : 2;  /* bit[0-1] : 读写数据采集屏蔽信号。
                                                          0：使能采集，1：屏蔽采集
                                                          bit0：读操作；
                                                          bit1：写操作； */
        unsigned int  reserved        : 30; /* bit[2-31]: 保留 */
    } reg;
} SOC_DSS_DBUG_REG2LBS_BUS_MSK_UNION;
#endif
#define SOC_DSS_DBUG_REG2LBS_BUS_MSK_reg2lbs_bus_msk_START  (0)
#define SOC_DSS_DBUG_REG2LBS_BUS_MSK_reg2lbs_bus_msk_END    (1)


/*****************************************************************************
 结构名    : SOC_DSS_DBUG_REG2HEAD_DIAG_ID_UNION
 结构说明  : REG2HEAD_DIAG_ID 寄存器结构定义。地址偏移量:0x0118，初值:0x48495349，宽度:32
 寄存器说明: 
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  reg2head_diag_id : 32; /* bit[0-31]: 帧头诊断标识。缺省值=0x48495349 */
    } reg;
} SOC_DSS_DBUG_REG2HEAD_DIAG_ID_UNION;
#endif
#define SOC_DSS_DBUG_REG2HEAD_DIAG_ID_reg2head_diag_id_START  (0)
#define SOC_DSS_DBUG_REG2HEAD_DIAG_ID_reg2head_diag_id_END    (31)


/*****************************************************************************
 结构名    : SOC_DSS_DBUG_REG2HEAD_HSRV_ID_UNION
 结构说明  : REG2HEAD_HSRV_ID 寄存器结构定义。地址偏移量:0x011C，初值:0x00000000，宽度:32
 寄存器说明: 
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  reg2head_hsrv_id : 8;  /* bit[0-7] : Service ID的SID指示。 */
        unsigned int  reserved         : 24; /* bit[8-31]: 保留 */
    } reg;
} SOC_DSS_DBUG_REG2HEAD_HSRV_ID_UNION;
#endif
#define SOC_DSS_DBUG_REG2HEAD_HSRV_ID_reg2head_hsrv_id_START  (0)
#define SOC_DSS_DBUG_REG2HEAD_HSRV_ID_reg2head_hsrv_id_END    (7)


/*****************************************************************************
 结构名    : SOC_DSS_DBUG_REG2HEAD_LSRV_ID_UNION
 结构说明  : REG2HEAD_LSRV_ID 寄存器结构定义。地址偏移量:0x0120，初值:0x00000000，宽度:32
 寄存器说明: 
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  reg2head_lsrv_id : 4;  /* bit[0-3] : Service ID的SSID指示。 */
        unsigned int  reserved         : 28; /* bit[4-31]: 保留 */
    } reg;
} SOC_DSS_DBUG_REG2HEAD_LSRV_ID_UNION;
#endif
#define SOC_DSS_DBUG_REG2HEAD_LSRV_ID_reg2head_lsrv_id_START  (0)
#define SOC_DSS_DBUG_REG2HEAD_LSRV_ID_reg2head_lsrv_id_END    (3)


/*****************************************************************************
 结构名    : SOC_DSS_DBUG_REG2HEAD_SESSION_ID_UNION
 结构说明  : REG2HEAD_SESSION_ID 寄存器结构定义。地址偏移量:0x0124，初值:0x00000000，宽度:32
 寄存器说明: 
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  reg2head_session_id : 8;  /* bit[0-7] : Session ID指示。 */
        unsigned int  reserved            : 24; /* bit[8-31]: 保留 */
    } reg;
} SOC_DSS_DBUG_REG2HEAD_SESSION_ID_UNION;
#endif
#define SOC_DSS_DBUG_REG2HEAD_SESSION_ID_reg2head_session_id_START  (0)
#define SOC_DSS_DBUG_REG2HEAD_SESSION_ID_reg2head_session_id_END    (7)


/*****************************************************************************
 结构名    : SOC_DSS_DBUG_REG2HEAD_MSG_TYPE_UNION
 结构说明  : REG2HEAD_MSG_TYPE 寄存器结构定义。地址偏移量:0x0128，初值:0x00000000，宽度:32
 寄存器说明: 
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  reg2head_msg_type : 8;  /* bit[0-7] : Message type消息类型指示。 */
        unsigned int  reserved          : 24; /* bit[8-31]: 保留 */
    } reg;
} SOC_DSS_DBUG_REG2HEAD_MSG_TYPE_UNION;
#endif
#define SOC_DSS_DBUG_REG2HEAD_MSG_TYPE_reg2head_msg_type_START  (0)
#define SOC_DSS_DBUG_REG2HEAD_MSG_TYPE_reg2head_msg_type_END    (7)


/*****************************************************************************
 结构名    : SOC_DSS_DBUG_DBG_BUS_BASE_ADDR_UNION
 结构说明  : DBG_BUS_BASE_ADDR 寄存器结构定义。地址偏移量:0x012C，初值:0x00000000，宽度:32
 寄存器说明: 
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  reserved          : 4;  /* bit[0-3] :  */
        unsigned int  dbg_bus_base_addr : 28; /* bit[4-31]: 软件分配的bus数据在ddr中的基地址，128bit对齐。 */
    } reg;
} SOC_DSS_DBUG_DBG_BUS_BASE_ADDR_UNION;
#endif
#define SOC_DSS_DBUG_DBG_BUS_BASE_ADDR_dbg_bus_base_addr_START  (4)
#define SOC_DSS_DBUG_DBG_BUS_BASE_ADDR_dbg_bus_base_addr_END    (31)


/*****************************************************************************
 结构名    : SOC_DSS_DBUG_DBG_BUS_END_ADDR_UNION
 结构说明  : DBG_BUS_END_ADDR 寄存器结构定义。地址偏移量:0x0130，初值:0x00000000，宽度:32
 寄存器说明: 
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  reserved         : 4;  /* bit[0-3] :  */
        unsigned int  dbg_bus_end_addr : 28; /* bit[4-31]: 软件分配的bus数据在ddr中的尾地址，128bit对齐。最好要求配置为2048B的倍数 */
    } reg;
} SOC_DSS_DBUG_DBG_BUS_END_ADDR_UNION;
#endif
#define SOC_DSS_DBUG_DBG_BUS_END_ADDR_dbg_bus_end_addr_START  (4)
#define SOC_DSS_DBUG_DBG_BUS_END_ADDR_dbg_bus_end_addr_END    (31)


/*****************************************************************************
 结构名    : SOC_DSS_DBUG_DBG_PTR_ADDR_UNION
 结构说明  : DBG_PTR_ADDR 寄存器结构定义。地址偏移量:0x0134，初值:0x00000000，宽度:32
 寄存器说明: 
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  reserved     : 4;  /* bit[0-3] :  */
        unsigned int  dbg_ptr_addr : 28; /* bit[4-31]: 可维可测通道buffer写指针起始地址，存放bus数据写指针。 */
    } reg;
} SOC_DSS_DBUG_DBG_PTR_ADDR_UNION;
#endif
#define SOC_DSS_DBUG_DBG_PTR_ADDR_dbg_ptr_addr_START  (4)
#define SOC_DSS_DBUG_DBG_PTR_ADDR_dbg_ptr_addr_END    (31)


/*****************************************************************************
 结构名    : SOC_DSS_DBUG_DBG_BUS_TIMING_UNION
 结构说明  : DBG_BUS_TIMING 寄存器结构定义。地址偏移量:0x0138，初值:0x00000000，宽度:32
 寄存器说明: 
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  dbg_bus_timing : 32; /* bit[0-31]: 帧定时计数阈值，内部计数器达到该值时表示一帧 */
    } reg;
} SOC_DSS_DBUG_DBG_BUS_TIMING_UNION;
#endif
#define SOC_DSS_DBUG_DBG_BUS_TIMING_dbg_bus_timing_START  (0)
#define SOC_DSS_DBUG_DBG_BUS_TIMING_dbg_bus_timing_END    (31)


/*****************************************************************************
 结构名    : SOC_DSS_DBUG_DBG_BUS_LDI_SEL_UNION
 结构说明  : DBG_BUS_LDI_SEL 寄存器结构定义。地址偏移量:0x013C，初值:0x00000000，宽度:32
 寄存器说明: 
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  dbg_bus_ldi_sel : 1;  /* bit[0-0] :  */
        unsigned int  reserved        : 31; /* bit[1-31]: 保留 */
    } reg;
} SOC_DSS_DBUG_DBG_BUS_LDI_SEL_UNION;
#endif
#define SOC_DSS_DBUG_DBG_BUS_LDI_SEL_dbg_bus_ldi_sel_START  (0)
#define SOC_DSS_DBUG_DBG_BUS_LDI_SEL_dbg_bus_ldi_sel_END    (0)


/*****************************************************************************
 结构名    : SOC_DSS_DBUG_DBG_BUS_END_UNION
 结构说明  : DBG_BUS_END 寄存器结构定义。地址偏移量:0x0140，初值:0x00000000，宽度:32
 寄存器说明: 
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  dbg_bus_end : 1;  /* bit[0]   : 保留 */
        unsigned int  reserved    : 31; /* bit[1-31]: 保留 */
    } reg;
} SOC_DSS_DBUG_DBG_BUS_END_UNION;
#endif
#define SOC_DSS_DBUG_DBG_BUS_END_dbg_bus_end_START  (0)
#define SOC_DSS_DBUG_DBG_BUS_END_dbg_bus_end_END    (0)


/*****************************************************************************
 结构名    : SOC_DSS_DBUG_REG2MEM_GATE_SEL_UNION
 结构说明  : REG2MEM_GATE_SEL 寄存器结构定义。地址偏移量:0x0144，初值:0x00000000，宽度:32
 寄存器说明: 
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  reg2mem_gate_sel : 1;  /* bit[0-0] : Ram的时钟门控选择信号。
                                                           0：时钟门控使能；1：时钟门控不使能 */
        unsigned int  reserved         : 31; /* bit[1-31]: 保留 */
    } reg;
} SOC_DSS_DBUG_REG2MEM_GATE_SEL_UNION;
#endif
#define SOC_DSS_DBUG_REG2MEM_GATE_SEL_reg2mem_gate_sel_START  (0)
#define SOC_DSS_DBUG_REG2MEM_GATE_SEL_reg2mem_gate_sel_END    (0)


/*****************************************************************************
 结构名    : SOC_DSS_DBUG_SP_MEM_CTRL0_LOG_UNION
 结构说明  : SP_MEM_CTRL0_LOG 寄存器结构定义。地址偏移量:0x0148，初值:0x00000000，宽度:32
 寄存器说明: 
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  sp_mem_ctrl0_log : 4;  /* bit[0-3] : 调试用寄存器，
                                                           [3]: reseverd; 
                                                           [2]: 软件配置模式下有效，为1表示进入Shut Down模式
                                                           [1]: 软件配置模式下有效，为1表示进入Deep Sleep模式
                                                           [0]: 软件配置模式下有效，为1表示进入Sleep模式 */
        unsigned int  reserved         : 28; /* bit[4-31]: 保留 */
    } reg;
} SOC_DSS_DBUG_SP_MEM_CTRL0_LOG_UNION;
#endif
#define SOC_DSS_DBUG_SP_MEM_CTRL0_LOG_sp_mem_ctrl0_log_START  (0)
#define SOC_DSS_DBUG_SP_MEM_CTRL0_LOG_sp_mem_ctrl0_log_END    (3)


/*****************************************************************************
 结构名    : SOC_DSS_DBUG_TP_MEM_CTRL0_UNION
 结构说明  : TP_MEM_CTRL0 寄存器结构定义。地址偏移量:0x014C，初值:0x00000000，宽度:32
 寄存器说明: MEM低功耗控制寄存器（TP）
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  tp_mem_ctrl0 : 4;  /* bit[0-3] : 调试用寄存器，
                                                       [3]: reseverd; 
                                                       [2]: 软件配置模式下有效，为1表示进入Shut Down模式
                                                       [1]: 软件配置模式下有效，为1表示进入Deep Sleep模式
                                                       [0]: 软件配置模式下有效，为1表示进入Sleep模式 */
        unsigned int  reserved     : 28; /* bit[4-31]: 保留 */
    } reg;
} SOC_DSS_DBUG_TP_MEM_CTRL0_UNION;
#endif
#define SOC_DSS_DBUG_TP_MEM_CTRL0_tp_mem_ctrl0_START  (0)
#define SOC_DSS_DBUG_TP_MEM_CTRL0_tp_mem_ctrl0_END    (3)


/*****************************************************************************
 结构名    : SOC_DSS_DBUG_DBG_BUS_TIMING_SEL_UNION
 结构说明  : DBG_BUS_TIMING_SEL 寄存器结构定义。地址偏移量:0x0150，初值:0x00000000，宽度:32
 寄存器说明: 
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  dbg_bus_timing_sel : 1;  /* bit[0-0] : 软件配置帧计数模式。
                                                             0：选择配置的帧内计数，1：选择ldi为帧计数 */
        unsigned int  reserved           : 31; /* bit[1-31]: 保留 */
    } reg;
} SOC_DSS_DBUG_DBG_BUS_TIMING_SEL_UNION;
#endif
#define SOC_DSS_DBUG_DBG_BUS_TIMING_SEL_dbg_bus_timing_sel_START  (0)
#define SOC_DSS_DBUG_DBG_BUS_TIMING_SEL_dbg_bus_timing_sel_END    (0)


/*****************************************************************************
 结构名    : SOC_DSS_DBUG_DSS_DBG_WPTR_UNION
 结构说明  : DSS_DBG_WPTR 寄存器结构定义。地址偏移量:0x0154，初值:0x00000000，宽度:32
 寄存器说明: 
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  dss_dbg_wptr : 32; /* bit[0-31]: 每帧dbg数据上报当前写入ddr的地址，字节为单位。 */
    } reg;
} SOC_DSS_DBUG_DSS_DBG_WPTR_UNION;
#endif
#define SOC_DSS_DBUG_DSS_DBG_WPTR_dss_dbg_wptr_START  (0)
#define SOC_DSS_DBUG_DSS_DBG_WPTR_dss_dbg_wptr_END    (31)






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

#endif /* end of soc_dss_dbug_interface.h */
