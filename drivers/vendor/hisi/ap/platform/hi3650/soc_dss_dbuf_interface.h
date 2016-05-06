/******************************************************************************

                 版权所有 (C), 2001-2015, 华为技术有限公司

 ******************************************************************************
  文 件 名   : soc_dss_dbuf_interface.h
  版 本 号   : 初稿
  作    者   : Excel2Code
  生成日期   : 2015-03-10 11:20:00
  最近修改   :
  功能描述   : 接口头文件
  函数列表   :
  修改历史   :
  1.日    期   : 2015年3月10日
    作    者   : fWX220878
    修改内容   : 从《Hi3650V100 SOC寄存器手册_DSS_DBUF.xml》自动生成

******************************************************************************/

/*****************************************************************************
  1 其他头文件包含
*****************************************************************************/

#ifndef __SOC_DSS_DBUF_INTERFACE_H__
#define __SOC_DSS_DBUF_INTERFACE_H__

#ifdef __cplusplus
    #if __cplusplus
        extern "C" {
    #endif
#endif



/*****************************************************************************
  2 宏定义
*****************************************************************************/

/****************************************************************************
                     (1/1) reg_DBUF
 ****************************************************************************/
/* 寄存器说明：帧尺寸寄存器
   位域定义UNION结构:  SOC_DSS_DBUF_FRM_SIZE_UNION */
#define SOC_DSS_DBUF_FRM_SIZE_ADDR(base)              ((base) + (0x0000))

/* 寄存器说明：行尺寸寄存器
   位域定义UNION结构:  SOC_DSS_DBUF_FRM_HSIZE_UNION */
#define SOC_DSS_DBUF_FRM_HSIZE_ADDR(base)             ((base) + (0x0004))

/* 寄存器说明：有效SRAM数目寄存器
   位域定义UNION结构:  SOC_DSS_DBUF_SRAM_VALID_NUM_UNION */
#define SOC_DSS_DBUF_SRAM_VALID_NUM_ADDR(base)        ((base) + (0x0008))

/* 寄存器说明：
   位域定义UNION结构:  SOC_DSS_DBUF_WBE_EN_UNION */
#define SOC_DSS_DBUF_WBE_EN_ADDR(base)                ((base) + (0x000C))

/* 寄存器说明：统计水限1
   位域定义UNION结构:  SOC_DSS_DBUF_THD_FILL_LEV0_UNION */
#define SOC_DSS_DBUF_THD_FILL_LEV0_ADDR(base)         ((base) + (0x0010))

/* 寄存器说明：统计水限2
   位域定义UNION结构:  SOC_DSS_DBUF_DFS_FILL_LEV1_UNION */
#define SOC_DSS_DBUF_DFS_FILL_LEV1_ADDR(base)         ((base) + (0x0014))

/* 寄存器说明：RQoS阈值寄存器
   位域定义UNION结构:  SOC_DSS_DBUF_THD_RQOS_UNION */
#define SOC_DSS_DBUF_THD_RQOS_ADDR(base)              ((base) + (0x0018))

/* 寄存器说明：WQoS阈值寄存器
   位域定义UNION结构:  SOC_DSS_DBUF_THD_WQOS_UNION */
#define SOC_DSS_DBUF_THD_WQOS_ADDR(base)              ((base) + (0x001C))

/* 寄存器说明：CG阈值寄存器
   位域定义UNION结构:  SOC_DSS_DBUF_THD_CG_UNION */
#define SOC_DSS_DBUF_THD_CG_ADDR(base)                ((base) + (0x0020))

/* 寄存器说明：控制相关数值寄存器
   位域定义UNION结构:  SOC_DSS_DBUF_THD_OTHER_UNION */
#define SOC_DSS_DBUF_THD_OTHER_ADDR(base)             ((base) + (0x0024))

/* 寄存器说明：检测水限0统计值
   位域定义UNION结构:  SOC_DSS_DBUF_FILL_LEV0_CNT_UNION */
#define SOC_DSS_DBUF_FILL_LEV0_CNT_ADDR(base)         ((base) + (0x0028))

/* 寄存器说明：检测水限1统计值
   位域定义UNION结构:  SOC_DSS_DBUF_FILL_LEV1_CNT_UNION */
#define SOC_DSS_DBUF_FILL_LEV1_CNT_ADDR(base)         ((base) + (0x002C))

/* 寄存器说明：检测水限2统计值
   位域定义UNION结构:  SOC_DSS_DBUF_FILL_LEV2_CNT_UNION */
#define SOC_DSS_DBUF_FILL_LEV2_CNT_ADDR(base)         ((base) + (0x0030))

/* 寄存器说明：检测水限3统计值
   位域定义UNION结构:  SOC_DSS_DBUF_FILL_LEV3_CNT_UNION */
#define SOC_DSS_DBUF_FILL_LEV3_CNT_ADDR(base)         ((base) + (0x0034))

/* 寄存器说明：检测水限4统计值
   位域定义UNION结构:  SOC_DSS_DBUF_FILL_LEV4_CNT_UNION */
#define SOC_DSS_DBUF_FILL_LEV4_CNT_ADDR(base)         ((base) + (0x0038))

/* 寄存器说明：在线通路填充水限寄存器
   位域定义UNION结构:  SOC_DSS_DBUF_ONLINE_FILL_LEVEL_UNION */
#define SOC_DSS_DBUF_ONLINE_FILL_LEVEL_ADDR(base)     ((base) + (0x003C))

/* 寄存器说明：回写通路填充水限寄存器
   位域定义UNION结构:  SOC_DSS_DBUF_WB_FILL_LEVEL_UNION */
#define SOC_DSS_DBUF_WB_FILL_LEVEL_ADDR(base)         ((base) + (0x0040))

/* 寄存器说明：状态寄存器
   位域定义UNION结构:  SOC_DSS_DBUF_DFS_STATUS_UNION */
#define SOC_DSS_DBUF_DFS_STATUS_ADDR(base)            ((base) + (0x0044))

/* 寄存器说明：SRAM低功耗控制寄存器
   位域定义UNION结构:  SOC_DSS_DBUF_DFS_LP_CTRL_UNION */
#define SOC_DSS_DBUF_DFS_LP_CTRL_ADDR(base)           ((base) + (0x004C))

/* 寄存器说明：读寄存器选择信号
   位域定义UNION结构:  SOC_DSS_DBUF_DBUF_RD_SHADOW_SEL_UNION */
#define SOC_DSS_DBUF_DBUF_RD_SHADOW_SEL_ADDR(base)    ((base) + (0x0050))

/* 寄存器说明：MEM低功耗控制寄存器
   位域定义UNION结构:  SOC_DSS_DBUF_DBUF_MEM_CTRL_UNION */
#define SOC_DSS_DBUF_DBUF_MEM_CTRL_ADDR(base)         ((base) + (0x0054))

/* 寄存器说明：一级模块时钟选择信号
   位域定义UNION结构:  SOC_DSS_DBUF_DBUF_CLK_SEL_UNION */
#define SOC_DSS_DBUF_DBUF_CLK_SEL_ADDR(base)          ((base) + (0x005C))

/* 寄存器说明：一级模块时钟使能信号
   位域定义UNION结构:  SOC_DSS_DBUF_DBUF_CLK_EN_UNION */
#define SOC_DSS_DBUF_DBUF_CLK_EN_ADDR(base)           ((base) + (0x0060))

/* 寄存器说明：CPU读写memory使能寄存器
   位域定义UNION结构:  SOC_DSS_DBUF_DBG_CPU_EN_UNION */
#define SOC_DSS_DBUF_DBG_CPU_EN_ADDR(base)            ((base) + (0x0070))

/* 寄存器说明：SRAM低功耗控制寄存器
   位域定义UNION结构:  SOC_DSS_DBUF_DBG_CPU_START_UNION */
#define SOC_DSS_DBUF_DBG_CPU_START_ADDR(base)         ((base) + (0x0074))

/* 寄存器说明：CPU控制memory读写寄存器
   位域定义UNION结构:  SOC_DSS_DBUF_DBG_CPU_CTL_UNION */
#define SOC_DSS_DBUF_DBG_CPU_CTL_ADDR(base)           ((base) + (0x0078))

/* 寄存器说明：MEM读数据0
   位域定义UNION结构:  SOC_DSS_DBUF_DBG_CPU_RDATA0_UNION */
#define SOC_DSS_DBUF_DBG_CPU_RDATA0_ADDR(base)        ((base) + (0x007C))

/* 寄存器说明：MEM读数据0
   位域定义UNION结构:  SOC_DSS_DBUF_DBG_CPU_RDATA1_UNION */
#define SOC_DSS_DBUF_DBG_CPU_RDATA1_ADDR(base)        ((base) + (0x0080))

/* 寄存器说明：MEM读数据0
   位域定义UNION结构:  SOC_DSS_DBUF_DBG_CPU_RDATA2_UNION */
#define SOC_DSS_DBUF_DBG_CPU_RDATA2_ADDR(base)        ((base) + (0x0084))

/* 寄存器说明：MEM读数据0
   位域定义UNION结构:  SOC_DSS_DBUF_DBG_CPU_RDATA3_UNION */
#define SOC_DSS_DBUF_DBG_CPU_RDATA3_ADDR(base)        ((base) + (0x0088))

/* 寄存器说明：MEM读数据0
   位域定义UNION结构:  SOC_DSS_DBUF_DBG_CPU_RDATA4_UNION */
#define SOC_DSS_DBUF_DBG_CPU_RDATA4_ADDR(base)        ((base) + (0x008C))

/* 寄存器说明：MEM读数据0
   位域定义UNION结构:  SOC_DSS_DBUF_DBG_CPU_WDATA0_UNION */
#define SOC_DSS_DBUF_DBG_CPU_WDATA0_ADDR(base)        ((base) + (0x0090))

/* 寄存器说明：MEM读数据0
   位域定义UNION结构:  SOC_DSS_DBUF_DBG_CPU_WDATA1_UNION */
#define SOC_DSS_DBUF_DBG_CPU_WDATA1_ADDR(base)        ((base) + (0x0094))

/* 寄存器说明：MEM读数据0
   位域定义UNION结构:  SOC_DSS_DBUF_DBG_CPU_WDATA2_UNION */
#define SOC_DSS_DBUF_DBG_CPU_WDATA2_ADDR(base)        ((base) + (0x0098))

/* 寄存器说明：MEM读数据0
   位域定义UNION结构:  SOC_DSS_DBUF_DBG_CPU_WDATA3_UNION */
#define SOC_DSS_DBUF_DBG_CPU_WDATA3_ADDR(base)        ((base) + (0x009C))

/* 寄存器说明：MEM读数据0
   位域定义UNION结构:  SOC_DSS_DBUF_DBG_CPU_WDATA4_UNION */
#define SOC_DSS_DBUF_DBG_CPU_WDATA4_ADDR(base)        ((base) + (0x00A0))

/* 寄存器说明：模块影子寄存器恢复到默认值
   位域定义UNION结构:  SOC_DSS_DBUF_REG_DEFAULT_UNION */
#define SOC_DSS_DBUF_REG_DEFAULT_ADDR(base)           ((base) + (0x00A4))





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
                     (1/1) reg_DBUF
 ****************************************************************************/
/*****************************************************************************
 结构名    : SOC_DSS_DBUF_FRM_SIZE_UNION
 结构说明  : FRM_SIZE 寄存器结构定义。地址偏移量:0x0000，初值:0x00000000，宽度:32
 寄存器说明: 帧尺寸寄存器
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  frm_size : 27; /* bit[0-26] : 一帧图像的像素个数，例如，如果图像分辨率为16x16，则frm_size为256 */
        unsigned int  reserved : 5;  /* bit[27-31]: 保留 */
    } reg;
} SOC_DSS_DBUF_FRM_SIZE_UNION;
#endif
#define SOC_DSS_DBUF_FRM_SIZE_frm_size_START  (0)
#define SOC_DSS_DBUF_FRM_SIZE_frm_size_END    (26)


/*****************************************************************************
 结构名    : SOC_DSS_DBUF_FRM_HSIZE_UNION
 结构说明  : FRM_HSIZE 寄存器结构定义。地址偏移量:0x0004，初值:0x00000000，宽度:32
 寄存器说明: 行尺寸寄存器
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  frm_hsize : 13; /* bit[0-12] : 一行的像素个数，为实际值减1。例如，如果图像分辨率为16x16，则frm_size为15 */
        unsigned int  reserved  : 19; /* bit[13-31]: 保留 */
    } reg;
} SOC_DSS_DBUF_FRM_HSIZE_UNION;
#endif
#define SOC_DSS_DBUF_FRM_HSIZE_frm_hsize_START  (0)
#define SOC_DSS_DBUF_FRM_HSIZE_frm_hsize_END    (12)


/*****************************************************************************
 结构名    : SOC_DSS_DBUF_SRAM_VALID_NUM_UNION
 结构说明  : SRAM_VALID_NUM 寄存器结构定义。地址偏移量:0x0008，初值:0x00000000，宽度:32
 寄存器说明: 有效SRAM数目寄存器
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  sram_valid_num : 2;  /* bit[0-1] : 对于DBUF0，有效memory的个数
                                                         0:DFS最大深度为1408x144bits
                                                         1:DFS最大深度为2816x144bits
                                                         2:DFS最大深度为4224x144bits
                                                         3:保留
                                                         
                                                         对于DBUF1，有效memory的个数
                                                         0:DFS最大深度为512x144bits
                                                         1:DFS最大深度为1024x144bits
                                                         2,3:保留 */
        unsigned int  reserved       : 30; /* bit[2-31]: DBUF0独有 */
    } reg;
} SOC_DSS_DBUF_SRAM_VALID_NUM_UNION;
#endif
#define SOC_DSS_DBUF_SRAM_VALID_NUM_sram_valid_num_START  (0)
#define SOC_DSS_DBUF_SRAM_VALID_NUM_sram_valid_num_END    (1)


/*****************************************************************************
 结构名    : SOC_DSS_DBUF_WBE_EN_UNION
 结构说明  : WBE_EN 寄存器结构定义。地址偏移量:0x000C，初值:0x00000000，宽度:32
 寄存器说明: 
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  wbe_en   : 1;  /* bit[0]   :  */
        unsigned int  reserved : 31; /* bit[1-31]: 保留 */
    } reg;
} SOC_DSS_DBUF_WBE_EN_UNION;
#endif
#define SOC_DSS_DBUF_WBE_EN_wbe_en_START    (0)
#define SOC_DSS_DBUF_WBE_EN_wbe_en_END      (0)


/*****************************************************************************
 结构名    : SOC_DSS_DBUF_THD_FILL_LEV0_UNION
 结构说明  : THD_FILL_LEV0 寄存器结构定义。地址偏移量:0x0010，初值:0x0258012C，宽度:32
 寄存器说明: 统计水限1
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  thd_fill_lev1 : 14; /* bit[0-13] : 监测水限1，此处填充水限的单位为memory深度，例如深度1对应与1x144bits = 6像素 */
        unsigned int  reserved_0    : 2;  /* bit[14-15]: 保留 */
        unsigned int  thd_fill_lev2 : 14; /* bit[16-29]: 监测水限2，此处填充水限的单位为memory深度，例如深度1对应与1x144bits = 6像素 */
        unsigned int  reserved_1    : 2;  /* bit[30-31]: 保留 */
    } reg;
} SOC_DSS_DBUF_THD_FILL_LEV0_UNION;
#endif
#define SOC_DSS_DBUF_THD_FILL_LEV0_thd_fill_lev1_START  (0)
#define SOC_DSS_DBUF_THD_FILL_LEV0_thd_fill_lev1_END    (13)
#define SOC_DSS_DBUF_THD_FILL_LEV0_thd_fill_lev2_START  (16)
#define SOC_DSS_DBUF_THD_FILL_LEV0_thd_fill_lev2_END    (29)


/*****************************************************************************
 结构名    : SOC_DSS_DBUF_DFS_FILL_LEV1_UNION
 结构说明  : DFS_FILL_LEV1 寄存器结构定义。地址偏移量:0x0014，初值:0x04B00384，宽度:32
 寄存器说明: 统计水限2
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  thd_fill_lev3 : 14; /* bit[0-13] : 监测水限3，此处填充水限的单位为memory深度，例如深度1对应与1x144bits = 6像素 */
        unsigned int  reserved_0    : 2;  /* bit[14-15]: 保留 */
        unsigned int  thd_fill_lev4 : 14; /* bit[16-29]: 监测水限4，此处填充水限的单位为memory深度，例如深度1对应与1x144bits = 6像素 */
        unsigned int  reserved_1    : 2;  /* bit[30-31]: 保留 */
    } reg;
} SOC_DSS_DBUF_DFS_FILL_LEV1_UNION;
#endif
#define SOC_DSS_DBUF_DFS_FILL_LEV1_thd_fill_lev3_START  (0)
#define SOC_DSS_DBUF_DFS_FILL_LEV1_thd_fill_lev3_END    (13)
#define SOC_DSS_DBUF_DFS_FILL_LEV1_thd_fill_lev4_START  (16)
#define SOC_DSS_DBUF_DFS_FILL_LEV1_thd_fill_lev4_END    (29)


/*****************************************************************************
 结构名    : SOC_DSS_DBUF_THD_RQOS_UNION
 结构说明  : THD_RQOS 寄存器结构定义。地址偏移量:0x0018，初值:0x00000000，宽度:32
 寄存器说明: RQoS阈值寄存器
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  thd_rqos_in  : 14; /* bit[0-13] : 在线通路填充水限小于此阈值时，rqos信号置1，此处填充水限的单位为memory深度，例如深度1对应与1x144bits = 6像素 */
        unsigned int  reserved_0   : 2;  /* bit[14-15]: 保留 */
        unsigned int  thd_rqos_out : 14; /* bit[16-29]: 在线通路填充水限大于此阈值时，rqos信号置0，此处填充水限的单位为memory深度，例如深度1对应与1x144bits = 6像素 */
        unsigned int  reserved_1   : 2;  /* bit[30-31]: 保留 */
    } reg;
} SOC_DSS_DBUF_THD_RQOS_UNION;
#endif
#define SOC_DSS_DBUF_THD_RQOS_thd_rqos_in_START   (0)
#define SOC_DSS_DBUF_THD_RQOS_thd_rqos_in_END     (13)
#define SOC_DSS_DBUF_THD_RQOS_thd_rqos_out_START  (16)
#define SOC_DSS_DBUF_THD_RQOS_thd_rqos_out_END    (29)


/*****************************************************************************
 结构名    : SOC_DSS_DBUF_THD_WQOS_UNION
 结构说明  : THD_WQOS 寄存器结构定义。地址偏移量:0x001C，初值:0x00000000，宽度:32
 寄存器说明: WQoS阈值寄存器
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  thd_wqos_in  : 14; /* bit[0-13] : wb通路填充水限大于此阈值时，wqos信号置1，此处填充水限的单位为memory深度，例如深度1对应与1x144bits = 6像素 */
        unsigned int  reserved_0   : 2;  /* bit[14-15]: 保留 */
        unsigned int  thd_wqos_out : 14; /* bit[16-29]: wb通路填充水限小于此阈值时，wqos信号置0，此处填充水限的单位为memory深度，例如深度1对应与1x144bits = 6像素 */
        unsigned int  reserved_1   : 2;  /* bit[30-31]: 保留 */
    } reg;
} SOC_DSS_DBUF_THD_WQOS_UNION;
#endif
#define SOC_DSS_DBUF_THD_WQOS_thd_wqos_in_START   (0)
#define SOC_DSS_DBUF_THD_WQOS_thd_wqos_in_END     (13)
#define SOC_DSS_DBUF_THD_WQOS_thd_wqos_out_START  (16)
#define SOC_DSS_DBUF_THD_WQOS_thd_wqos_out_END    (29)


/*****************************************************************************
 结构名    : SOC_DSS_DBUF_THD_CG_UNION
 结构说明  : THD_CG 寄存器结构定义。地址偏移量:0x0020，初值:0x00000000，宽度:32
 寄存器说明: CG阈值寄存器
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  thd_cg_in  : 14; /* bit[0-13] : 在线通道填充水限大于此阈值时，clock gate信号置1，此处填充水限的单位为memory深度，例如深度1对应与1x144bits = 6像素 */
        unsigned int  reserved_0 : 2;  /* bit[14-15]: 保留 */
        unsigned int  thd_cg_out : 14; /* bit[16-29]: 在线通道填充水限小于此阈值时，clock gate信号置0，此处填充水限的单位为memory深度，例如深度1对应与1x144bits = 6像素 */
        unsigned int  reserved_1 : 2;  /* bit[30-31]: 保留 */
    } reg;
} SOC_DSS_DBUF_THD_CG_UNION;
#endif
#define SOC_DSS_DBUF_THD_CG_thd_cg_in_START   (0)
#define SOC_DSS_DBUF_THD_CG_thd_cg_in_END     (13)
#define SOC_DSS_DBUF_THD_CG_thd_cg_out_START  (16)
#define SOC_DSS_DBUF_THD_CG_thd_cg_out_END    (29)


/*****************************************************************************
 结构名    : SOC_DSS_DBUF_THD_OTHER_UNION
 结构说明  : THD_OTHER 寄存器结构定义。地址偏移量:0x0024，初值:0x001015E0，宽度:32
 寄存器说明: 控制相关数值寄存器
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  thd_wr_wait : 14; /* bit[0-13] : wb通道填充水限大于在线通道填充水限，并且两者差值小于此阈值时，DFS采用离线通道的full信号作为FIFO的full信号，否则采用在线通道的full信号作为FIFO的full
                                                       默认值为5856-256=5600 */
        unsigned int  reserved_0  : 2;  /* bit[14-15]: 保留 */
        unsigned int  dfs_cg_hold : 8;  /* bit[16-23]: dfs_ret_en的下降沿与dfs_cg下降沿之间的延时周期数
                                                       TBD */
        unsigned int  reserved_1  : 8;  /* bit[24-31]: 保留 */
    } reg;
} SOC_DSS_DBUF_THD_OTHER_UNION;
#endif
#define SOC_DSS_DBUF_THD_OTHER_thd_wr_wait_START  (0)
#define SOC_DSS_DBUF_THD_OTHER_thd_wr_wait_END    (13)
#define SOC_DSS_DBUF_THD_OTHER_dfs_cg_hold_START  (16)
#define SOC_DSS_DBUF_THD_OTHER_dfs_cg_hold_END    (23)


/*****************************************************************************
 结构名    : SOC_DSS_DBUF_FILL_LEV0_CNT_UNION
 结构说明  : FILL_LEV0_CNT 寄存器结构定义。地址偏移量:0x0028，初值:0x00000000，宽度:32
 寄存器说明: 检测水限0统计值
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  fill_lev0_cnt : 32; /* bit[0-31]: 一帧内DFS FIFO的填充水限小于fill_lev1的周期数 */
    } reg;
} SOC_DSS_DBUF_FILL_LEV0_CNT_UNION;
#endif
#define SOC_DSS_DBUF_FILL_LEV0_CNT_fill_lev0_cnt_START  (0)
#define SOC_DSS_DBUF_FILL_LEV0_CNT_fill_lev0_cnt_END    (31)


/*****************************************************************************
 结构名    : SOC_DSS_DBUF_FILL_LEV1_CNT_UNION
 结构说明  : FILL_LEV1_CNT 寄存器结构定义。地址偏移量:0x002C，初值:0x00000000，宽度:32
 寄存器说明: 检测水限1统计值
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  fill_lev1_cnt : 32; /* bit[0-31]: 一帧内DFS FIFO的填充水限大于等于fill_lev1且小于fill_lev2的周期数 */
    } reg;
} SOC_DSS_DBUF_FILL_LEV1_CNT_UNION;
#endif
#define SOC_DSS_DBUF_FILL_LEV1_CNT_fill_lev1_cnt_START  (0)
#define SOC_DSS_DBUF_FILL_LEV1_CNT_fill_lev1_cnt_END    (31)


/*****************************************************************************
 结构名    : SOC_DSS_DBUF_FILL_LEV2_CNT_UNION
 结构说明  : FILL_LEV2_CNT 寄存器结构定义。地址偏移量:0x0030，初值:0x00000000，宽度:32
 寄存器说明: 检测水限2统计值
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  fill_lev2_cnt : 32; /* bit[0-31]: 一帧内DFS FIFO的填充水限大于等于fill_lev2且小于fill_lev3的周期数 */
    } reg;
} SOC_DSS_DBUF_FILL_LEV2_CNT_UNION;
#endif
#define SOC_DSS_DBUF_FILL_LEV2_CNT_fill_lev2_cnt_START  (0)
#define SOC_DSS_DBUF_FILL_LEV2_CNT_fill_lev2_cnt_END    (31)


/*****************************************************************************
 结构名    : SOC_DSS_DBUF_FILL_LEV3_CNT_UNION
 结构说明  : FILL_LEV3_CNT 寄存器结构定义。地址偏移量:0x0034，初值:0x00000000，宽度:32
 寄存器说明: 检测水限3统计值
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  fill_lev3_cnt : 32; /* bit[0-31]: 一帧内DFS FIFO的填充水限大于等于fill_lev3且小于fill_lev4的周期数 */
    } reg;
} SOC_DSS_DBUF_FILL_LEV3_CNT_UNION;
#endif
#define SOC_DSS_DBUF_FILL_LEV3_CNT_fill_lev3_cnt_START  (0)
#define SOC_DSS_DBUF_FILL_LEV3_CNT_fill_lev3_cnt_END    (31)


/*****************************************************************************
 结构名    : SOC_DSS_DBUF_FILL_LEV4_CNT_UNION
 结构说明  : FILL_LEV4_CNT 寄存器结构定义。地址偏移量:0x0038，初值:0x00000000，宽度:32
 寄存器说明: 检测水限4统计值
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  fill_lev4_cnt : 32; /* bit[0-31]: 一帧内DFS FIFO的填充水限大于等于fill_lev4的周期数 */
    } reg;
} SOC_DSS_DBUF_FILL_LEV4_CNT_UNION;
#endif
#define SOC_DSS_DBUF_FILL_LEV4_CNT_fill_lev4_cnt_START  (0)
#define SOC_DSS_DBUF_FILL_LEV4_CNT_fill_lev4_cnt_END    (31)


/*****************************************************************************
 结构名    : SOC_DSS_DBUF_ONLINE_FILL_LEVEL_UNION
 结构说明  : ONLINE_FILL_LEVEL 寄存器结构定义。地址偏移量:0x003C，初值:0x00000000，宽度:32
 寄存器说明: 在线通路填充水限寄存器
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  online_fill_lev : 14; /* bit[0-13] :  */
        unsigned int  reserved        : 18; /* bit[14-31]: 保留 */
    } reg;
} SOC_DSS_DBUF_ONLINE_FILL_LEVEL_UNION;
#endif
#define SOC_DSS_DBUF_ONLINE_FILL_LEVEL_online_fill_lev_START  (0)
#define SOC_DSS_DBUF_ONLINE_FILL_LEVEL_online_fill_lev_END    (13)


/*****************************************************************************
 结构名    : SOC_DSS_DBUF_WB_FILL_LEVEL_UNION
 结构说明  : WB_FILL_LEVEL 寄存器结构定义。地址偏移量:0x0040，初值:0x00000000，宽度:32
 寄存器说明: 回写通路填充水限寄存器
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  wb_fill_lev : 14; /* bit[0-13] :  */
        unsigned int  reserved    : 18; /* bit[14-31]: 保留 */
    } reg;
} SOC_DSS_DBUF_WB_FILL_LEVEL_UNION;
#endif
#define SOC_DSS_DBUF_WB_FILL_LEVEL_wb_fill_lev_START  (0)
#define SOC_DSS_DBUF_WB_FILL_LEVEL_wb_fill_lev_END    (13)


/*****************************************************************************
 结构名    : SOC_DSS_DBUF_DFS_STATUS_UNION
 结构说明  : DFS_STATUS 寄存器结构定义。地址偏移量:0x0044，初值:0x00000015，宽度:32
 寄存器说明: 状态寄存器
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  online_empty  : 1;  /* bit[0]   :  */
        unsigned int  online_full   : 1;  /* bit[1]   :  */
        unsigned int  offline_empty : 1;  /* bit[2]   :  */
        unsigned int  offline_full  : 1;  /* bit[3]   :  */
        unsigned int  dfs_cg        : 1;  /* bit[4]   :  */
        unsigned int  dfs_wqos      : 1;  /* bit[5]   :  */
        unsigned int  dfs_rqos      : 1;  /* bit[6]   :  */
        unsigned int  dfs_wb_error  : 1;  /* bit[7]   :  */
        unsigned int  reserved      : 24; /* bit[8-31]: 保留 */
    } reg;
} SOC_DSS_DBUF_DFS_STATUS_UNION;
#endif
#define SOC_DSS_DBUF_DFS_STATUS_online_empty_START   (0)
#define SOC_DSS_DBUF_DFS_STATUS_online_empty_END     (0)
#define SOC_DSS_DBUF_DFS_STATUS_online_full_START    (1)
#define SOC_DSS_DBUF_DFS_STATUS_online_full_END      (1)
#define SOC_DSS_DBUF_DFS_STATUS_offline_empty_START  (2)
#define SOC_DSS_DBUF_DFS_STATUS_offline_empty_END    (2)
#define SOC_DSS_DBUF_DFS_STATUS_offline_full_START   (3)
#define SOC_DSS_DBUF_DFS_STATUS_offline_full_END     (3)
#define SOC_DSS_DBUF_DFS_STATUS_dfs_cg_START         (4)
#define SOC_DSS_DBUF_DFS_STATUS_dfs_cg_END           (4)
#define SOC_DSS_DBUF_DFS_STATUS_dfs_wqos_START       (5)
#define SOC_DSS_DBUF_DFS_STATUS_dfs_wqos_END         (5)
#define SOC_DSS_DBUF_DFS_STATUS_dfs_rqos_START       (6)
#define SOC_DSS_DBUF_DFS_STATUS_dfs_rqos_END         (6)
#define SOC_DSS_DBUF_DFS_STATUS_dfs_wb_error_START   (7)
#define SOC_DSS_DBUF_DFS_STATUS_dfs_wb_error_END     (7)


/*****************************************************************************
 结构名    : SOC_DSS_DBUF_DFS_LP_CTRL_UNION
 结构说明  : DFS_LP_CTRL 寄存器结构定义。地址偏移量:0x004C，初值:0x00000003，宽度:32
 寄存器说明: SRAM低功耗控制寄存器
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  pd_upon_frm_end  : 1;  /* bit[0]   : 0：在DFS传输完一帧数据后DFS SRAM不进入低功耗模式
                                                           1：在DFS传输完一帧数据后DFS SRAM进入低功耗模式 */
        unsigned int  ret_aft_prefetch : 1;  /* bit[1]   : 0：一帧开始的预取完成后，DFS SRAM不进入retention模式
                                                           1：一帧开始的预取完成后，DFS SRAM进入retention模式。在这种模式下，预取完成后停止向WB通路输出数据 */
        unsigned int  reserved         : 30; /* bit[2-31]: 保留 */
    } reg;
} SOC_DSS_DBUF_DFS_LP_CTRL_UNION;
#endif
#define SOC_DSS_DBUF_DFS_LP_CTRL_pd_upon_frm_end_START   (0)
#define SOC_DSS_DBUF_DFS_LP_CTRL_pd_upon_frm_end_END     (0)
#define SOC_DSS_DBUF_DFS_LP_CTRL_ret_aft_prefetch_START  (1)
#define SOC_DSS_DBUF_DFS_LP_CTRL_ret_aft_prefetch_END    (1)


/*****************************************************************************
 结构名    : SOC_DSS_DBUF_DBUF_RD_SHADOW_SEL_UNION
 结构说明  : DBUF_RD_SHADOW_SEL 寄存器结构定义。地址偏移量:0x0050，初值:0x00000000，宽度:32
 寄存器说明: 读寄存器选择信号
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  dbuf_rd_shadow : 1;  /* bit[0]   : 1'b0 :读工作寄存器
                                                         1'b1 :读影子寄存器 */
        unsigned int  reserved       : 31; /* bit[1-31]: 保留 */
    } reg;
} SOC_DSS_DBUF_DBUF_RD_SHADOW_SEL_UNION;
#endif
#define SOC_DSS_DBUF_DBUF_RD_SHADOW_SEL_dbuf_rd_shadow_START  (0)
#define SOC_DSS_DBUF_DBUF_RD_SHADOW_SEL_dbuf_rd_shadow_END    (0)


/*****************************************************************************
 结构名    : SOC_DSS_DBUF_DBUF_MEM_CTRL_UNION
 结构说明  : DBUF_MEM_CTRL 寄存器结构定义。地址偏移量:0x0054，初值:0x00000000，宽度:32
 寄存器说明: MEM低功耗控制寄存器
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  dbuf_mem_ctrl : 4;  /* bit[0-3] : 调试用寄存器
                                                        [3] mem_ctrl_auto_en , 自动模式、软件配置模式选择,0自动模式，1软件配置模式 
                                                        [2]: 软件配置模式下有效，为1表示进入Shut Down模式
                                                        [1]: 软件配置模式下有效，为1表示进入Deep Sleep模式
                                                        [0]: 软件配置模式下有效，为1表示进入Sleep模式 */
        unsigned int  reserved      : 28; /* bit[4-31]: 保留 */
    } reg;
} SOC_DSS_DBUF_DBUF_MEM_CTRL_UNION;
#endif
#define SOC_DSS_DBUF_DBUF_MEM_CTRL_dbuf_mem_ctrl_START  (0)
#define SOC_DSS_DBUF_DBUF_MEM_CTRL_dbuf_mem_ctrl_END    (3)


/*****************************************************************************
 结构名    : SOC_DSS_DBUF_DBUF_CLK_SEL_UNION
 结构说明  : DBUF_CLK_SEL 寄存器结构定义。地址偏移量:0x005C，初值:0xFFFFFFFF，宽度:32
 寄存器说明: 一级模块时钟选择信号
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  dbuf_clk_sel : 32; /* bit[0-31]: 各一级模块的时钟选择信号，
                                                       1：表示强制打开时钟。
                                                       0：表示需要根据软件和硬件的时钟使能来开启或关闭时钟
                                                       bit0：用于apb；
                                                       bit1：用于reg；
                                                       bit2：用于dbuf_core；
                                                       bit3：用于dbuf_wb；
                                                       bit4：用于dbuf_pm；
                                                       bit5：用于dbuf_afifo */
    } reg;
} SOC_DSS_DBUF_DBUF_CLK_SEL_UNION;
#endif
#define SOC_DSS_DBUF_DBUF_CLK_SEL_dbuf_clk_sel_START  (0)
#define SOC_DSS_DBUF_DBUF_CLK_SEL_dbuf_clk_sel_END    (31)


/*****************************************************************************
 结构名    : SOC_DSS_DBUF_DBUF_CLK_EN_UNION
 结构说明  : DBUF_CLK_EN 寄存器结构定义。地址偏移量:0x0060，初值:0xFFFFFFFF，宽度:32
 寄存器说明: 一级模块时钟使能信号
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  dbuf_clk_en : 32; /* bit[0-31]: 各一级模块的软件时钟使能信号
                                                      1：表示软件时钟使能有效，允许硬件开钟
                                                      0：表示软件时钟使能无效，禁止硬件开钟
                                                      bit0：保留；
                                                      bit1：用于reg；
                                                      bit2：用于dbuf_core；
                                                      bit3：用于dbuf_wb；
                                                      bit4：用于dbuf_pm；
                                                      bit5：用于dbuf_afifo */
    } reg;
} SOC_DSS_DBUF_DBUF_CLK_EN_UNION;
#endif
#define SOC_DSS_DBUF_DBUF_CLK_EN_dbuf_clk_en_START  (0)
#define SOC_DSS_DBUF_DBUF_CLK_EN_dbuf_clk_en_END    (31)


/*****************************************************************************
 结构名    : SOC_DSS_DBUF_DBG_CPU_EN_UNION
 结构说明  : DBG_CPU_EN 寄存器结构定义。地址偏移量:0x0070，初值:0x00000000，宽度:32
 寄存器说明: CPU读写memory使能寄存器
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  cpu_ctl  : 1;  /* bit[0]   : 调试用寄存器
                                                   1：cpu控制memory读写使能；
                                                   0：cpu控制memory读写不使能； */
        unsigned int  reserved : 31; /* bit[1-31]: 保留 */
    } reg;
} SOC_DSS_DBUF_DBG_CPU_EN_UNION;
#endif
#define SOC_DSS_DBUF_DBG_CPU_EN_cpu_ctl_START   (0)
#define SOC_DSS_DBUF_DBG_CPU_EN_cpu_ctl_END     (0)


/*****************************************************************************
 结构名    : SOC_DSS_DBUF_DBG_CPU_START_UNION
 结构说明  : DBG_CPU_START 寄存器结构定义。地址偏移量:0x0074，初值:0x00000000，宽度:32
 寄存器说明: SRAM低功耗控制寄存器
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  cpu_start : 1;  /* bit[0]   : cpu读写memory地址，调试用 */
        unsigned int  reserved  : 31; /* bit[1-31]: 保留 */
    } reg;
} SOC_DSS_DBUF_DBG_CPU_START_UNION;
#endif
#define SOC_DSS_DBUF_DBG_CPU_START_cpu_start_START  (0)
#define SOC_DSS_DBUF_DBG_CPU_START_cpu_start_END    (0)


/*****************************************************************************
 结构名    : SOC_DSS_DBUF_DBG_CPU_CTL_UNION
 结构说明  : DBG_CPU_CTL 寄存器结构定义。地址偏移量:0x0078，初值:0x00000000，宽度:32
 寄存器说明: CPU控制memory读写寄存器
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  cpu_addr : 13; /* bit[0-12] : cpu读写memory地址，调试用 */
        unsigned int  reserved_0: 3;  /* bit[13-15]: 保留 */
        unsigned int  cpu_we   : 1;  /* bit[16]   : 1：CPU 写，0：CPU 读 */
        unsigned int  reserved_1: 15; /* bit[17-31]: 保留 */
    } reg;
} SOC_DSS_DBUF_DBG_CPU_CTL_UNION;
#endif
#define SOC_DSS_DBUF_DBG_CPU_CTL_cpu_addr_START  (0)
#define SOC_DSS_DBUF_DBG_CPU_CTL_cpu_addr_END    (12)
#define SOC_DSS_DBUF_DBG_CPU_CTL_cpu_we_START    (16)
#define SOC_DSS_DBUF_DBG_CPU_CTL_cpu_we_END      (16)


/*****************************************************************************
 结构名    : SOC_DSS_DBUF_DBG_CPU_RDATA0_UNION
 结构说明  : DBG_CPU_RDATA0 寄存器结构定义。地址偏移量:0x007C，初值:0x00000000，宽度:32
 寄存器说明: MEM读数据0
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  cpu_rdata0 : 32; /* bit[0-31]: mem读端口，调试用 */
    } reg;
} SOC_DSS_DBUF_DBG_CPU_RDATA0_UNION;
#endif
#define SOC_DSS_DBUF_DBG_CPU_RDATA0_cpu_rdata0_START  (0)
#define SOC_DSS_DBUF_DBG_CPU_RDATA0_cpu_rdata0_END    (31)


/*****************************************************************************
 结构名    : SOC_DSS_DBUF_DBG_CPU_RDATA1_UNION
 结构说明  : DBG_CPU_RDATA1 寄存器结构定义。地址偏移量:0x0080，初值:0x00000000，宽度:32
 寄存器说明: MEM读数据0
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  cpu_rdata1 : 32; /* bit[0-31]: mem读端口，调试用 */
    } reg;
} SOC_DSS_DBUF_DBG_CPU_RDATA1_UNION;
#endif
#define SOC_DSS_DBUF_DBG_CPU_RDATA1_cpu_rdata1_START  (0)
#define SOC_DSS_DBUF_DBG_CPU_RDATA1_cpu_rdata1_END    (31)


/*****************************************************************************
 结构名    : SOC_DSS_DBUF_DBG_CPU_RDATA2_UNION
 结构说明  : DBG_CPU_RDATA2 寄存器结构定义。地址偏移量:0x0084，初值:0x00000000，宽度:32
 寄存器说明: MEM读数据0
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  cpu_rdata2 : 32; /* bit[0-31]: mem读端口，调试用 */
    } reg;
} SOC_DSS_DBUF_DBG_CPU_RDATA2_UNION;
#endif
#define SOC_DSS_DBUF_DBG_CPU_RDATA2_cpu_rdata2_START  (0)
#define SOC_DSS_DBUF_DBG_CPU_RDATA2_cpu_rdata2_END    (31)


/*****************************************************************************
 结构名    : SOC_DSS_DBUF_DBG_CPU_RDATA3_UNION
 结构说明  : DBG_CPU_RDATA3 寄存器结构定义。地址偏移量:0x0088，初值:0x00000000，宽度:32
 寄存器说明: MEM读数据0
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  cpu_rdata3 : 32; /* bit[0-31]: mem读端口，调试用 */
    } reg;
} SOC_DSS_DBUF_DBG_CPU_RDATA3_UNION;
#endif
#define SOC_DSS_DBUF_DBG_CPU_RDATA3_cpu_rdata3_START  (0)
#define SOC_DSS_DBUF_DBG_CPU_RDATA3_cpu_rdata3_END    (31)


/*****************************************************************************
 结构名    : SOC_DSS_DBUF_DBG_CPU_RDATA4_UNION
 结构说明  : DBG_CPU_RDATA4 寄存器结构定义。地址偏移量:0x008C，初值:0x00000000，宽度:32
 寄存器说明: MEM读数据0
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  cpu_rdata4 : 16; /* bit[0-15] : mem读端口，调试用 */
        unsigned int  reserved   : 16; /* bit[16-31]: 保留 */
    } reg;
} SOC_DSS_DBUF_DBG_CPU_RDATA4_UNION;
#endif
#define SOC_DSS_DBUF_DBG_CPU_RDATA4_cpu_rdata4_START  (0)
#define SOC_DSS_DBUF_DBG_CPU_RDATA4_cpu_rdata4_END    (15)


/*****************************************************************************
 结构名    : SOC_DSS_DBUF_DBG_CPU_WDATA0_UNION
 结构说明  : DBG_CPU_WDATA0 寄存器结构定义。地址偏移量:0x0090，初值:0x00000000，宽度:32
 寄存器说明: MEM读数据0
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  cpu_wdata0 : 32; /* bit[0-31]: mem写端口，调试用 */
    } reg;
} SOC_DSS_DBUF_DBG_CPU_WDATA0_UNION;
#endif
#define SOC_DSS_DBUF_DBG_CPU_WDATA0_cpu_wdata0_START  (0)
#define SOC_DSS_DBUF_DBG_CPU_WDATA0_cpu_wdata0_END    (31)


/*****************************************************************************
 结构名    : SOC_DSS_DBUF_DBG_CPU_WDATA1_UNION
 结构说明  : DBG_CPU_WDATA1 寄存器结构定义。地址偏移量:0x0094，初值:0x00000000，宽度:32
 寄存器说明: MEM读数据0
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  cpu_wdata1 : 32; /* bit[0-31]: mem写端口，调试用 */
    } reg;
} SOC_DSS_DBUF_DBG_CPU_WDATA1_UNION;
#endif
#define SOC_DSS_DBUF_DBG_CPU_WDATA1_cpu_wdata1_START  (0)
#define SOC_DSS_DBUF_DBG_CPU_WDATA1_cpu_wdata1_END    (31)


/*****************************************************************************
 结构名    : SOC_DSS_DBUF_DBG_CPU_WDATA2_UNION
 结构说明  : DBG_CPU_WDATA2 寄存器结构定义。地址偏移量:0x0098，初值:0x00000000，宽度:32
 寄存器说明: MEM读数据0
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  cpu_wdata2 : 32; /* bit[0-31]: mem写端口，调试用 */
    } reg;
} SOC_DSS_DBUF_DBG_CPU_WDATA2_UNION;
#endif
#define SOC_DSS_DBUF_DBG_CPU_WDATA2_cpu_wdata2_START  (0)
#define SOC_DSS_DBUF_DBG_CPU_WDATA2_cpu_wdata2_END    (31)


/*****************************************************************************
 结构名    : SOC_DSS_DBUF_DBG_CPU_WDATA3_UNION
 结构说明  : DBG_CPU_WDATA3 寄存器结构定义。地址偏移量:0x009C，初值:0x00000000，宽度:32
 寄存器说明: MEM读数据0
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  cpu_wdata3 : 32; /* bit[0-31]: mem写端口，调试用 */
    } reg;
} SOC_DSS_DBUF_DBG_CPU_WDATA3_UNION;
#endif
#define SOC_DSS_DBUF_DBG_CPU_WDATA3_cpu_wdata3_START  (0)
#define SOC_DSS_DBUF_DBG_CPU_WDATA3_cpu_wdata3_END    (31)


/*****************************************************************************
 结构名    : SOC_DSS_DBUF_DBG_CPU_WDATA4_UNION
 结构说明  : DBG_CPU_WDATA4 寄存器结构定义。地址偏移量:0x00A0，初值:0x00000000，宽度:32
 寄存器说明: MEM读数据0
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  cpu_wdata4 : 16; /* bit[0-15] : mem写端口，调试用 */
        unsigned int  reserved   : 16; /* bit[16-31]: 保留 */
    } reg;
} SOC_DSS_DBUF_DBG_CPU_WDATA4_UNION;
#endif
#define SOC_DSS_DBUF_DBG_CPU_WDATA4_cpu_wdata4_START  (0)
#define SOC_DSS_DBUF_DBG_CPU_WDATA4_cpu_wdata4_END    (15)


/*****************************************************************************
 结构名    : SOC_DSS_DBUF_REG_DEFAULT_UNION
 结构说明  : REG_DEFAULT 寄存器结构定义。地址偏移量:0x00A4，初值:0x00000000，宽度:32
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
} SOC_DSS_DBUF_REG_DEFAULT_UNION;
#endif
#define SOC_DSS_DBUF_REG_DEFAULT_reg_default_START  (0)
#define SOC_DSS_DBUF_REG_DEFAULT_reg_default_END    (0)






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

#endif /* end of soc_dss_dbuf_interface.h */
