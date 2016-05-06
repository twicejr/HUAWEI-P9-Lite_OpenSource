/******************************************************************************

                 版权所有 (C), 2001-2013, 华为技术有限公司

 ******************************************************************************
  文 件 名   : soc_hdlc_interface.h
  版 本 号   : 初稿
  作    者   : Excel2Code
  生成日期   : 2013-08-02 16:05:06
  最近修改   :
  功能描述   : 接口头文件
  函数列表   :
  修改历史   :
  1.日    期   : 2013年8月2日
    作    者   : d00246513
    修改内容   : 从《Hi6930V200 SOC寄存器手册_HDLC.xml》自动生成

******************************************************************************/

/*****************************************************************************
  1 其他头文件包含
*****************************************************************************/

#ifndef __SOC_HDLC_INTERFACE_H__
#define __SOC_HDLC_INTERFACE_H__

#ifdef __cplusplus
    #if __cplusplus
        extern "C" {
    #endif
#endif



/*****************************************************************************
  2 宏定义
*****************************************************************************/

/****************************************************************************
                     (1/1) Register_define
 ****************************************************************************/
/* 寄存器说明：状态软复位寄存器。
   位域定义UNION结构:  SOC_HDLC_STATE_SW_RST_UNION */
#define SOC_HDLC_STATE_SW_RST_ADDR(base)              ((base) + (0x0000))

/* 寄存器说明：HDLC封装、解封装优先级配置和AXI总线读写请求超时判断使能及timeout值配置寄存器。
   位域定义UNION结构:  SOC_HDLC_PRIOR_TIMEOUT_CTRL_UNION */
#define SOC_HDLC_PRIOR_TIMEOUT_CTRL_ADDR(base)        ((base) + (0x0004))

/* 寄存器说明：AXI读操作错误时被读地址。
   位域定义UNION结构:  SOC_HDLC_RD_ERR_CURR_ADDR_UNION */
#define SOC_HDLC_RD_ERR_CURR_ADDR_ADDR(base)          ((base) + (0x0008))

/* 寄存器说明：AXI写操作错误时被写地址。
   位域定义UNION结构:  SOC_HDLC_WR_ERR_CURR_ADDR_UNION */
#define SOC_HDLC_WR_ERR_CURR_ADDR_ADDR(base)          ((base) + (0x000C))

/* 寄存器说明：HDLC封装相关使能寄存器（包括封装使能、封装参数配置错误中断使能、AXI读写错误中断使能、AXI读写timeout中断使能、封装外部输出存储空间不足中断使能、封装外部正确帧长度上报空间不足中断使能、封装结束中断使能，删除实际下发数据多于、少于配置长度的异常中断使能）。
   位域定义UNION结构:  SOC_HDLC_FRM_EN_UNION */
#define SOC_HDLC_FRM_EN_ADDR(base)                    ((base) + (0x0010))

/* 寄存器说明：HDLC封装原始中断状态寄存器（增加AXI读写错误原始中断、AXI读写timeout原始中断、封装外部输出存储空间不足原始中断、封装外部正确帧长度上报空间不足原始中断、封装结束原始中断，删除实际下发数据多于、少于配置长度的原始中断）。
   位域定义UNION结构:  SOC_HDLC_FRM_RAW_INT_UNION */
#define SOC_HDLC_FRM_RAW_INT_ADDR(base)               ((base) + (0x0014))

/* 寄存器说明：HDLC封装屏蔽后中断状态寄存器（增加AXI读写错误屏蔽后中断、AXI读写timeout屏蔽后中断、封装外部输出存储空间不足屏蔽后中断状态、封装外部正确帧长度上报空间不足屏蔽后中断状态、封装结束屏蔽后中断状态，删除实际下发数据多于、少于配置长度的屏蔽后中断状态）。
   位域定义UNION结构:  SOC_HDLC_FRM_INT_STATUS_UNION */
#define SOC_HDLC_FRM_INT_STATUS_ADDR(base)            ((base) + (0x0018))

/* 寄存器说明：HDLC封装中断清除寄存器（增加AXI读写错误中断清除、AXI读写timeout中断清除、封装外部输出存储空间不足中断清除、封装外部正确帧长度上报空间不足中断清除、封装结束中断清除，删除实际下发数据多于、少于配置长度的中断清除）。
   位域定义UNION结构:  SOC_HDLC_FRM_INT_CLR_UNION */
#define SOC_HDLC_FRM_INT_CLR_ADDR(base)               ((base) + (0x001C))

/* 寄存器说明：封装子模块配置寄存器
            (将最低位改为封装输入一维链表或二位链表选择指示frm_in_lli_1dor2d)。
   位域定义UNION结构:  SOC_HDLC_FRM_CFG_UNION */
#define SOC_HDLC_FRM_CFG_ADDR(base)                   ((base) + (0x0020))

/* 寄存器说明：封装子模块转义使能(LCP协议该寄存器无效)。
   位域定义UNION结构:  SOC_HDLC_FRM_ACCM_UNION */
#define SOC_HDLC_FRM_ACCM_ADDR(base)                  ((base) + (0x0024))

/* 寄存器说明：封装子模块状态寄存器（将frm_frm_len删除，增加frm_out_seg_num，和frm_valid_num，将frm_blk_done改为frm_all_pkt_done）。
   位域定义UNION结构:  SOC_HDLC_FRM_STATUS_UNION */
#define SOC_HDLC_FRM_STATUS_ADDR(base)                ((base) + (0x0028))

/* 寄存器说明：封装输入链表起始地址寄存器。
   位域定义UNION结构:  SOC_HDLC_FRM_IN_LLI_ADDR_UNION */
#define SOC_HDLC_FRM_IN_LLI_ADDR_ADDR(base)           ((base) + (0x0030))

/* 寄存器说明：当frm_in_lii_1dor2d为0，表示待封装输入数据包起始地址寄存器；
            当frm_in_lii_1dor2d为1，表示封装输入副链表参数起始地址寄存器。
   位域定义UNION结构:  SOC_HDLC_FRM_IN_SUBLLI_ADDR_UNION */
#define SOC_HDLC_FRM_IN_SUBLLI_ADDR_ADDR(base)        ((base) + (0x0034))

/* 寄存器说明：封装输入主链表节点所指待封装输入数据包长度寄存器。
   位域定义UNION结构:  SOC_HDLC_FRM_IN_PKT_LEN_UNION */
#define SOC_HDLC_FRM_IN_PKT_LEN_ADDR(base)            ((base) + (0x0038))

/* 寄存器说明：封装输入副链表节点所指待封装输入数据分组起始地址寄存器。
   位域定义UNION结构:  SOC_HDLC_FRM_IN_BLK_ADDR_UNION */
#define SOC_HDLC_FRM_IN_BLK_ADDR_ADDR(base)           ((base) + (0x003C))

/* 寄存器说明：封装输入副链表节点所指待封装输入数据分组长度寄存器。
   位域定义UNION结构:  SOC_HDLC_FRM_IN_BLK_LEN_UNION */
#define SOC_HDLC_FRM_IN_BLK_LEN_ADDR(base)            ((base) + (0x0040))

/* 寄存器说明：封装输出链表起始地址寄存器。
   位域定义UNION结构:  SOC_HDLC_FRM_OUT_LLI_ADDR_UNION */
#define SOC_HDLC_FRM_OUT_LLI_ADDR_ADDR(base)          ((base) + (0x0044))

/* 寄存器说明：封装输出链表节点所指存储空间起始地址寄存器。
   位域定义UNION结构:  SOC_HDLC_FRM_OUT_SPC_ADDR_UNION */
#define SOC_HDLC_FRM_OUT_SPC_ADDR_ADDR(base)          ((base) + (0x0048))

/* 寄存器说明：封装输出链表节点所指存储空间深度寄存器。
   位域定义UNION结构:  SOC_HDLC_FRM_OUT_SPC_DEP_UNION */
#define SOC_HDLC_FRM_OUT_SPC_DEP_ADDR(base)           ((base) + (0x004C))

/* 寄存器说明：封装各输出正确帧长度存储空间起始地址寄存器。
   位域定义UNION结构:  SOC_HDLC_FRM_RPT_ADDR_UNION */
#define SOC_HDLC_FRM_RPT_ADDR_ADDR(base)              ((base) + (0x0050))

/* 寄存器说明：封装各输出正确帧长度存储空间深度寄存器。
   位域定义UNION结构:  SOC_HDLC_FRM_RPT_DEP_UNION */
#define SOC_HDLC_FRM_RPT_DEP_ADDR(base)               ((base) + (0x0054))

/* 寄存器说明：HDLC解封装相关使能寄存器（包括解封装使能、解封装参数配置错误中断使能、AXI读写错误中断使能、AXI读写timeout中断使能、解封装解出有效LCP帧暂停中断使能、解封装外部输出存储空间存满暂停中断使能、解封装外部正确帧信息上报空间存满暂停中断使能、解封装结束中断使能，删除实际下发数据多于、少于配置长度的异常中断使能）。
   位域定义UNION结构:  SOC_HDLC_DEF_EN_UNION */
#define SOC_HDLC_DEF_EN_ADDR(base)                    ((base) + (0x0060))

/* 寄存器说明：HDLC原始中断状态寄存器（增加AXI读写错误原始中断、AXI读写timeout原始中断、解封装解出有效LCP帧原始暂停中断、解封装外部输出存储空间存满暂停原始中断、解封装外部正确帧信息上报空间存满暂停原始中断、解封装结束原始中断，删除实际下发数据多于、少于配置长度的原始中断）。
   位域定义UNION结构:  SOC_HDLC_DEF_RAW_INT_UNION */
#define SOC_HDLC_DEF_RAW_INT_ADDR(base)               ((base) + (0x0064))

/* 寄存器说明：HDLC屏蔽后中断状态寄存器（增加AXI读写错误屏蔽后中断状态、AXI读写timeout屏蔽后中断状态、解封装解出有效LCP帧暂停屏蔽后中断状态、解封装外部输出存储空间存满暂停屏蔽后中断状态、解封装外部正确帧信息上报空间存满暂停屏蔽后中断状态、解封装结束屏蔽后中断状态，删除实际下发数据多于、少于配置长度的屏蔽后中断状态）。
   位域定义UNION结构:  SOC_HDLC_DEF_INT_STATUS_UNION */
#define SOC_HDLC_DEF_INT_STATUS_ADDR(base)            ((base) + (0x0068))

/* 寄存器说明：HDLC中断清除寄存器（增加AXI读写错误中断清除、AXI读写timeout中断清除、解封装解出有效LCP帧暂停中断清除、解封装外部输出存储空间存满暂停中断清除、解封装外部正确帧信息上报空间存满暂停中断清除、解封装结束中断清除，删除实际下发数据多于、少于配置长度的中断清除）。
   位域定义UNION结构:  SOC_HDLC_DEF_INT_CLR_UNION */
#define SOC_HDLC_DEF_INT_CLR_ADDR(base)               ((base) + (0x006C))

/* 寄存器说明：解封装子模块配置寄存器
            (将最低位改为def_uncompleted_ago，用于指示对应当前解封装输入链表，同一PPP/IP拨号的以前最近解封装输入链表是否有解出非完整帧，为了支持多个PPP/IP拨号而增加的配置：0，没有；1，有)。
   位域定义UNION结构:  SOC_HDLC_DEF_CFG_UNION */
#define SOC_HDLC_DEF_CFG_ADDR(base)                   ((base) + (0x0070))

/* 寄存器说明：对应当前解封装输入链表，同一PPP/IP拨号的以前最近解封装输入链表解出非完整帧的长度，为了支持多个PPP/IP拨号而增加的配置。
   位域定义UNION结构:  SOC_HDLC_DEF_UNCOMPLETED_LEN_UNION */
#define SOC_HDLC_DEF_UNCOMPLETED_LEN_ADDR(base)       ((base) + (0x0074))

/* 寄存器说明：对应当前解封装输入链表，同一PPP/IP拨号的以前最近解封装输入链表解出非完整帧的协议，为了支持多个PPP/IP拨号而增加的配置（可能其中的0Byte、1Byte或2Byte有效）。
   位域定义UNION结构:  SOC_HDLC_DEF_UNCOMPLETED_PRO_UNION */
#define SOC_HDLC_DEF_UNCOMPLETED_PRO_ADDR(base)       ((base) + (0x0078))

/* 寄存器说明：对应当前解封装输入链表，同一PPP/IP拨号的以前最近解封装输入链表解出非完整帧的外部存储起始地址，为了支持多个PPP/IP拨号而增加的配置（该地址可能是与原来上报不同的新地址）。
   位域定义UNION结构:  SOC_HDLC_DEF_UNCOMPLETED_ADDR_UNION */
#define SOC_HDLC_DEF_UNCOMPLETED_ADDR_ADDR(base)      ((base) + (0x007C))

/* 寄存器说明：与当前解封装输入链表同一PPP/IP拨号的以前最近那套解封装输入链表处理完解出非完整帧时的数据状态机当前状态和CRC校验值。
   位域定义UNION结构:  SOC_HDLC_DEF_UNCOMPLET_ST_AGO_UNION */
#define SOC_HDLC_DEF_UNCOMPLET_ST_AGO_ADDR(base)      ((base) + (0x0080))

/* 寄存器说明：暂停状态解除寄存器（解出一个合法LCP帧导致的解封装子模块暂停状态解除、解封装外部输出存储空间存满暂停解除、解封装外部正确帧信息上报空间存满暂停解除）。
   位域定义UNION结构:  SOC_HDLC_DEF_GO_ON_UNION */
#define SOC_HDLC_DEF_GO_ON_ADDR(base)                 ((base) + (0x0084))

/* 寄存器说明：解封装子模块状态寄存器（增加def_uncompleted_now，用于指示当前链表是否有解出非完整帧，为了支持多个PPP/IP拨号而增加的配置：0，没有；1，有；增加def_out_spc_ful和def_rpt_ful；将def_blk_pro_stat改为def_all_pkt_pro_stat）。
   位域定义UNION结构:  SOC_HDLC_DEF_STATUS_UNION */
#define SOC_HDLC_DEF_STATUS_ADDR(base)                ((base) + (0x0088))

/* 寄存器说明：当前解封装输入链表处理完解出非完整帧时的数据状态机当前状态和CRC校验值。
   位域定义UNION结构:  SOC_HDLC_DEF_UNCOMPLET_ST_NOW_UNION */
#define SOC_HDLC_DEF_UNCOMPLET_ST_NOW_ADDR(base)      ((base) + (0x008C))

/* 寄存器说明：解封装输入链表参数起始地址寄存器。
   位域定义UNION结构:  SOC_HDLC_DEF_IN_LLI_ADDR_UNION */
#define SOC_HDLC_DEF_IN_LLI_ADDR_ADDR(base)           ((base) + (0x0090))

/* 寄存器说明：解封装输入链表节点所指待解封装输入数据包起始地址寄存器。
   位域定义UNION结构:  SOC_HDLC_DEF_IN_PKT_ADDR_UNION */
#define SOC_HDLC_DEF_IN_PKT_ADDR_ADDR(base)           ((base) + (0x0094))

/* 寄存器说明：解封装输入链表节点所指待解封装输入数据包长度寄存器。
   位域定义UNION结构:  SOC_HDLC_DEF_IN_PKT_LEN_UNION */
#define SOC_HDLC_DEF_IN_PKT_LEN_ADDR(base)            ((base) + (0x0098))

/* 寄存器说明：一个解封装输入链表节点所指待解封装输入数据包最大允许长度寄存器。
   位域定义UNION结构:  SOC_HDLC_DEF_IN_PKT_LEN_MAX_UNION */
#define SOC_HDLC_DEF_IN_PKT_LEN_MAX_ADDR(base)        ((base) + (0x009C))

/* 寄存器说明：解封装输出数据存储空间起始地址寄存器
   位域定义UNION结构:  SOC_HDLC_DEF_OUT_SPC_ADDR_UNION */
#define SOC_HDLC_DEF_OUT_SPC_ADDR_ADDR(base)          ((base) + (0x00A0))

/* 寄存器说明：解封装输出数据存储空间深度寄存器。
   位域定义UNION结构:  SOC_HDLC_DEF_OUT_SPC_DEP_UNION */
#define SOC_HDLC_DEF_OUT_SPC_DEP_ADDR(base)           ((base) + (0x00A4))

/* 寄存器说明：解封装输出正确帧上报信息存储空间起始地址。
   位域定义UNION结构:  SOC_HDLC_DEF_RPT_ADDR_UNION */
#define SOC_HDLC_DEF_RPT_ADDR_ADDR(base)              ((base) + (0x00A8))

/* 寄存器说明：解封装输出正确帧上报信息存储空间深度。
   位域定义UNION结构:  SOC_HDLC_DEF_RPT_DEP_UNION */
#define SOC_HDLC_DEF_RPT_DEP_ADDR(base)               ((base) + (0x00AC))

/* 寄存器说明：解封装错误帧信息寄存器（组0）。
   位域定义UNION结构:  SOC_HDLC_DEF_ERR_INFO_0_UNION */
#define SOC_HDLC_DEF_ERR_INFO_0_ADDR(base)            ((base) + (0x00B0))

/* 寄存器说明：解封装错误帧信息寄存器（组1）。
   位域定义UNION结构:  SOC_HDLC_DEF_ERR_INFO_1_UNION */
#define SOC_HDLC_DEF_ERR_INFO_1_ADDR(base)            ((base) + (0x00B4))

/* 寄存器说明：解封装错误帧信息寄存器（组2）。
   位域定义UNION结构:  SOC_HDLC_DEF_ERR_INFO_2_UNION */
#define SOC_HDLC_DEF_ERR_INFO_2_ADDR(base)            ((base) + (0x00B8))

/* 寄存器说明：解封装错误帧信息寄存器（组3）。
   位域定义UNION结构:  SOC_HDLC_DEF_ERR_INFO_3_UNION */
#define SOC_HDLC_DEF_ERR_INFO_3_ADDR(base)            ((base) + (0x00BC))

/* 寄存器说明：与当前解封装输入链表同一PPP/IP拨号的以前最近那套解封装输入链表处理完解出非完整帧时的信息长度和帧长度。
   位域定义UNION结构:  SOC_HDLC_DEF_INFO_FRL_CNT_AGO_UNION */
#define SOC_HDLC_DEF_INFO_FRL_CNT_AGO_ADDR(base)      ((base) + (0x00C0))

/* 寄存器说明：当前解封装输入链表处理完解出非完整帧时的信息长度和帧长度。
   位域定义UNION结构:  SOC_HDLC_DEF_INFO_FRL_CNT_NOW_UNION */
#define SOC_HDLC_DEF_INFO_FRL_CNT_NOW_ADDR(base)      ((base) + (0x00C4))





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
                     (1/1) Register_define
 ****************************************************************************/
/*****************************************************************************
 结构名    : SOC_HDLC_STATE_SW_RST_UNION
 结构说明  : STATE_SW_RST 寄存器结构定义。地址偏移量:0x0000，初值:0x00000000，宽度:32
 寄存器说明: 状态软复位寄存器。
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  state_sw_rst : 1;  /* bit[0]   : 状态软复位：
                                                       0：状态不软复位；
                                                       1：状态软复位 */
        unsigned int  reserved     : 31; /* bit[1-31]: 保留 */
    } reg;
} SOC_HDLC_STATE_SW_RST_UNION;
#endif
#define SOC_HDLC_STATE_SW_RST_state_sw_rst_START  (0)
#define SOC_HDLC_STATE_SW_RST_state_sw_rst_END    (0)


/*****************************************************************************
 结构名    : SOC_HDLC_PRIOR_TIMEOUT_CTRL_UNION
 结构说明  : PRIOR_TIMEOUT_CTRL 寄存器结构定义。地址偏移量:0x0004，初值:0x00000000，宽度:32
 寄存器说明: HDLC封装、解封装优先级配置和AXI总线读写请求超时判断使能及timeout值配置寄存器。
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  hdlc_prior_ctrl      : 2;  /* bit[0-1]  : HDLC封装、解封装优先级配置寄存器：
                                                                00：一个在工作中，另一个也被使能情况下，先将已处于工作中的那个处理完，即谁先被使能则先将谁处理完；01：下行封装优先级高；
                                                                10：上行解封装优先级高；
                                                                11：无效。
                                                                (HDLC内部控制被暂停者的继续开始工作：当解封装被暂停，封装整套链表被处理完后，解封装就开始继续工作；当封装被暂停，解封装整个数据包被处理完后，封装就开始继续工作。) */
        unsigned int  reserved_0           : 6;  /* bit[2-7]  : 保留 */
        unsigned int  axireq_timeout_en    : 1;  /* bit[8]    : 是否允许硬件判断AXI总线读写请求超时，由软件配置：
                                                                0不允许
                                                                1允许 */
        unsigned int  reserved_1           : 7;  /* bit[9-15] : 保留 */
        unsigned int  axireq_timeout_value : 8;  /* bit[16-23]: 软件配置AXI总线读写请求超时的判断值 */
        unsigned int  reserved_2           : 8;  /* bit[24-31]: 保留 */
    } reg;
} SOC_HDLC_PRIOR_TIMEOUT_CTRL_UNION;
#endif
#define SOC_HDLC_PRIOR_TIMEOUT_CTRL_hdlc_prior_ctrl_START       (0)
#define SOC_HDLC_PRIOR_TIMEOUT_CTRL_hdlc_prior_ctrl_END         (1)
#define SOC_HDLC_PRIOR_TIMEOUT_CTRL_axireq_timeout_en_START     (8)
#define SOC_HDLC_PRIOR_TIMEOUT_CTRL_axireq_timeout_en_END       (8)
#define SOC_HDLC_PRIOR_TIMEOUT_CTRL_axireq_timeout_value_START  (16)
#define SOC_HDLC_PRIOR_TIMEOUT_CTRL_axireq_timeout_value_END    (23)


/*****************************************************************************
 结构名    : SOC_HDLC_RD_ERR_CURR_ADDR_UNION
 结构说明  : RD_ERR_CURR_ADDR 寄存器结构定义。地址偏移量:0x0008，初值:0x00000000，宽度:32
 寄存器说明: AXI读操作错误时被读地址。
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  rd_err_curr_addr : 32; /* bit[0-31]: AXI读操作错误时被读地址 */
    } reg;
} SOC_HDLC_RD_ERR_CURR_ADDR_UNION;
#endif
#define SOC_HDLC_RD_ERR_CURR_ADDR_rd_err_curr_addr_START  (0)
#define SOC_HDLC_RD_ERR_CURR_ADDR_rd_err_curr_addr_END    (31)


/*****************************************************************************
 结构名    : SOC_HDLC_WR_ERR_CURR_ADDR_UNION
 结构说明  : WR_ERR_CURR_ADDR 寄存器结构定义。地址偏移量:0x000C，初值:0x00000000，宽度:32
 寄存器说明: AXI写操作错误时被写地址。
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  wr_err_curr_addr : 32; /* bit[0-31]: AXI写操作错误时被写地址 */
    } reg;
} SOC_HDLC_WR_ERR_CURR_ADDR_UNION;
#endif
#define SOC_HDLC_WR_ERR_CURR_ADDR_wr_err_curr_addr_START  (0)
#define SOC_HDLC_WR_ERR_CURR_ADDR_wr_err_curr_addr_END    (31)


/*****************************************************************************
 结构名    : SOC_HDLC_FRM_EN_UNION
 结构说明  : FRM_EN 寄存器结构定义。地址偏移量:0x0010，初值:0x00000000，宽度:32
 寄存器说明: HDLC封装相关使能寄存器（包括封装使能、封装参数配置错误中断使能、AXI读写错误中断使能、AXI读写timeout中断使能、封装外部输出存储空间不足中断使能、封装外部正确帧长度上报空间不足中断使能、封装结束中断使能，删除实际下发数据多于、少于配置长度的异常中断使能）。
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  frm_en             : 1;  /* bit[0]    : 一套链表封装使能，软件向frm_en写入1'b1启动封装工作；
                                                              一套链表封装完成后，由硬件自动对frm_en清零；
                                                              封装过程出错时，硬件也会对frm_en自动清零，使内部状态机返回IDLE状态；
                                                              读该寄存器返回封装处理状态。
                                                              写时设置一套链表封装使能：
                                                              0：不使能封装处理；
                                                              1：使能封装处理；
                                                              读时返回一套链表封装处理状态：
                                                              0：没在进行封装处理；
                                                              1：正在进行封装处理。 */
        unsigned int  reserved_0         : 7;  /* bit[1-7]  : 保留 */
        unsigned int  frm_rd_err_en      : 1;  /* bit[8]    : 封装时AXI总线读操作错误中断使能：
                                                              0：中断禁止；
                                                              1：中断使能； */
        unsigned int  frm_wr_err_en      : 1;  /* bit[9]    : 封装时AXI总线写操作错误中断使能：
                                                              0：中断禁止；
                                                              1：中断使能； */
        unsigned int  frm_rd_timeout_en  : 1;  /* bit[10]   : 封装时AXI总线读请求timeout中断使能：
                                                              0：中断禁止；
                                                              1：中断使能； */
        unsigned int  frm_wr_timeout_en  : 1;  /* bit[11]   : 封装时AXI总线写请求timeout中断使能：
                                                              0：中断禁止；
                                                              1：中断使能； */
        unsigned int  frm_cfg_err_en     : 1;  /* bit[12]   : 封装模块异常中断(表示参数配置错误)使能：
                                                              0：中断禁止；
                                                              1：中断使能； */
        unsigned int  frm_in_prm_err_en  : 1;  /* bit[13]   : 封装输入链表相关参数错误中断使能：
                                                              0：中断禁止；
                                                              1：中断使能； */
        unsigned int  frm_out_prm_err_en : 1;  /* bit[14]   : 封装输出链表相关参数错误中断使能：
                                                              0：中断禁止；
                                                              1：中断使能； */
        unsigned int  frm_rpt_prm_err_en : 1;  /* bit[15]   : 封装上报空间相关参数错误中断使能：
                                                              0：中断禁止；
                                                              1：中断使能； */
        unsigned int  frm_out_spc_err_en : 1;  /* bit[16]   : 封装外部输出存储空间不足中断使能：
                                                              0：中断禁止；
                                                              1：中断使能； */
        unsigned int  frm_rpt_dep_err_en : 1;  /* bit[17]   : 封装外部正确帧长度上报空间不足中断使能：
                                                              0：中断禁止；
                                                              1：中断使能； */
        unsigned int  reserved_1         : 6;  /* bit[18-23]: 保留 */
        unsigned int  frm_over_int_en    : 1;  /* bit[24]   : 一套链表封装结束中断使能：
                                                              0：中断禁止；
                                                              1：中断使能； */
        unsigned int  reserved_2         : 7;  /* bit[25-31]: 保留 */
    } reg;
} SOC_HDLC_FRM_EN_UNION;
#endif
#define SOC_HDLC_FRM_EN_frm_en_START              (0)
#define SOC_HDLC_FRM_EN_frm_en_END                (0)
#define SOC_HDLC_FRM_EN_frm_rd_err_en_START       (8)
#define SOC_HDLC_FRM_EN_frm_rd_err_en_END         (8)
#define SOC_HDLC_FRM_EN_frm_wr_err_en_START       (9)
#define SOC_HDLC_FRM_EN_frm_wr_err_en_END         (9)
#define SOC_HDLC_FRM_EN_frm_rd_timeout_en_START   (10)
#define SOC_HDLC_FRM_EN_frm_rd_timeout_en_END     (10)
#define SOC_HDLC_FRM_EN_frm_wr_timeout_en_START   (11)
#define SOC_HDLC_FRM_EN_frm_wr_timeout_en_END     (11)
#define SOC_HDLC_FRM_EN_frm_cfg_err_en_START      (12)
#define SOC_HDLC_FRM_EN_frm_cfg_err_en_END        (12)
#define SOC_HDLC_FRM_EN_frm_in_prm_err_en_START   (13)
#define SOC_HDLC_FRM_EN_frm_in_prm_err_en_END     (13)
#define SOC_HDLC_FRM_EN_frm_out_prm_err_en_START  (14)
#define SOC_HDLC_FRM_EN_frm_out_prm_err_en_END    (14)
#define SOC_HDLC_FRM_EN_frm_rpt_prm_err_en_START  (15)
#define SOC_HDLC_FRM_EN_frm_rpt_prm_err_en_END    (15)
#define SOC_HDLC_FRM_EN_frm_out_spc_err_en_START  (16)
#define SOC_HDLC_FRM_EN_frm_out_spc_err_en_END    (16)
#define SOC_HDLC_FRM_EN_frm_rpt_dep_err_en_START  (17)
#define SOC_HDLC_FRM_EN_frm_rpt_dep_err_en_END    (17)
#define SOC_HDLC_FRM_EN_frm_over_int_en_START     (24)
#define SOC_HDLC_FRM_EN_frm_over_int_en_END       (24)


/*****************************************************************************
 结构名    : SOC_HDLC_FRM_RAW_INT_UNION
 结构说明  : FRM_RAW_INT 寄存器结构定义。地址偏移量:0x0014，初值:0x00000000，宽度:32
 寄存器说明: HDLC封装原始中断状态寄存器（增加AXI读写错误原始中断、AXI读写timeout原始中断、封装外部输出存储空间不足原始中断、封装外部正确帧长度上报空间不足原始中断、封装结束原始中断，删除实际下发数据多于、少于配置长度的原始中断）。
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  reserved_0          : 8;  /* bit[0-7]  : 保留 */
        unsigned int  frm_rd_err_raw      : 1;  /* bit[8]    : 封装时AXI总线读操作错误原始中断：
                                                               0：无中断；
                                                               1：有中断； */
        unsigned int  frm_wr_err_raw      : 1;  /* bit[9]    : 封装时AXI总线写操作错误原始中断：
                                                               0：无中断；
                                                               1：有中断； */
        unsigned int  frm_rd_timeout_raw  : 1;  /* bit[10]   : 封装时AXI总线读请求timeout原始中断：
                                                               0：无中断；
                                                               1：有中断； */
        unsigned int  frm_wr_timeout_raw  : 1;  /* bit[11]   : 封装时AXI总线写请求timeout原始中断：
                                                               0：无中断；
                                                               1：有中断； */
        unsigned int  frm_cfg_err_raw     : 1;  /* bit[12]   : 封装协议及其压缩指示配置错误原始中断：
                                                               0：无中断；
                                                               1：有中断； */
        unsigned int  frm_in_prm_err_raw  : 1;  /* bit[13]   : 封装输入链表相关参数错误原始中断：
                                                               0：无中断；
                                                               1：有中断； */
        unsigned int  frm_out_prm_err_raw : 1;  /* bit[14]   : 封装输出链表相关参数错误原始中断：
                                                               0：无中断；
                                                               1：有中断； */
        unsigned int  frm_rpt_prm_err_raw : 1;  /* bit[15]   : 封装上报空间相关参数错误原始中断：
                                                               0：无中断；
                                                               1：有中断； */
        unsigned int  frm_out_spc_err_raw : 1;  /* bit[16]   : 封装外部输出存储空间不足原始中断：
                                                               0：无中断；
                                                               1：有中断； */
        unsigned int  frm_rpt_dep_err_raw : 1;  /* bit[17]   : 封装外部正确帧长度上报空间不足原始中断：
                                                               0：无中断；
                                                               1：有中断； */
        unsigned int  reserved_1          : 6;  /* bit[18-23]: 保留 */
        unsigned int  frm_over_int_raw    : 1;  /* bit[24]   : 一套链表封装结束原始中断：
                                                               0：无中断；
                                                               1：有中断； */
        unsigned int  reserved_2          : 7;  /* bit[25-31]: 保留 */
    } reg;
} SOC_HDLC_FRM_RAW_INT_UNION;
#endif
#define SOC_HDLC_FRM_RAW_INT_frm_rd_err_raw_START       (8)
#define SOC_HDLC_FRM_RAW_INT_frm_rd_err_raw_END         (8)
#define SOC_HDLC_FRM_RAW_INT_frm_wr_err_raw_START       (9)
#define SOC_HDLC_FRM_RAW_INT_frm_wr_err_raw_END         (9)
#define SOC_HDLC_FRM_RAW_INT_frm_rd_timeout_raw_START   (10)
#define SOC_HDLC_FRM_RAW_INT_frm_rd_timeout_raw_END     (10)
#define SOC_HDLC_FRM_RAW_INT_frm_wr_timeout_raw_START   (11)
#define SOC_HDLC_FRM_RAW_INT_frm_wr_timeout_raw_END     (11)
#define SOC_HDLC_FRM_RAW_INT_frm_cfg_err_raw_START      (12)
#define SOC_HDLC_FRM_RAW_INT_frm_cfg_err_raw_END        (12)
#define SOC_HDLC_FRM_RAW_INT_frm_in_prm_err_raw_START   (13)
#define SOC_HDLC_FRM_RAW_INT_frm_in_prm_err_raw_END     (13)
#define SOC_HDLC_FRM_RAW_INT_frm_out_prm_err_raw_START  (14)
#define SOC_HDLC_FRM_RAW_INT_frm_out_prm_err_raw_END    (14)
#define SOC_HDLC_FRM_RAW_INT_frm_rpt_prm_err_raw_START  (15)
#define SOC_HDLC_FRM_RAW_INT_frm_rpt_prm_err_raw_END    (15)
#define SOC_HDLC_FRM_RAW_INT_frm_out_spc_err_raw_START  (16)
#define SOC_HDLC_FRM_RAW_INT_frm_out_spc_err_raw_END    (16)
#define SOC_HDLC_FRM_RAW_INT_frm_rpt_dep_err_raw_START  (17)
#define SOC_HDLC_FRM_RAW_INT_frm_rpt_dep_err_raw_END    (17)
#define SOC_HDLC_FRM_RAW_INT_frm_over_int_raw_START     (24)
#define SOC_HDLC_FRM_RAW_INT_frm_over_int_raw_END       (24)


/*****************************************************************************
 结构名    : SOC_HDLC_FRM_INT_STATUS_UNION
 结构说明  : FRM_INT_STATUS 寄存器结构定义。地址偏移量:0x0018，初值:0x00000000，宽度:32
 寄存器说明: HDLC封装屏蔽后中断状态寄存器（增加AXI读写错误屏蔽后中断、AXI读写timeout屏蔽后中断、封装外部输出存储空间不足屏蔽后中断状态、封装外部正确帧长度上报空间不足屏蔽后中断状态、封装结束屏蔽后中断状态，删除实际下发数据多于、少于配置长度的屏蔽后中断状态）。
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  reserved_0           : 8;  /* bit[0-7]  : 保留 */
        unsigned int  frm_rd_err_stat      : 1;  /* bit[8]    : 封装时AXI总线读操作错误屏蔽后中断状态：
                                                                0：无中断；
                                                                1：有中断； */
        unsigned int  frm_wr_err_stat      : 1;  /* bit[9]    : 封装时AXI总线写操作错误屏蔽后中断状态：
                                                                0：无中断；
                                                                1：有中断； */
        unsigned int  frm_rd_timeout_stat  : 1;  /* bit[10]   : 封装时AXI总线读请求timeout屏蔽后中断状态：
                                                                0：无中断；
                                                                1：有中断； */
        unsigned int  frm_wr_timeout_stat  : 1;  /* bit[11]   : 封装时AXI总线写请求timeout屏蔽后中断状态：
                                                                0：无中断；
                                                                1：有中断； */
        unsigned int  frm_cfg_err_stat     : 1;  /* bit[12]   : 封装协议及其压缩指示配置错误屏蔽后中断状态：
                                                                0：无中断；
                                                                1：有中断； */
        unsigned int  frm_in_prm_err_stat  : 1;  /* bit[13]   : 封装输入链表相关参数错误屏蔽后中断状态：
                                                                0：无中断；
                                                                1：有中断； */
        unsigned int  frm_out_prm_err_stat : 1;  /* bit[14]   : 封装输出链表相关参数错误屏蔽后中断状态：
                                                                0：无中断；
                                                                1：有中断； */
        unsigned int  frm_rpt_prm_err_stat : 1;  /* bit[15]   : 封装上报空间相关参数错误屏蔽后中断状态：
                                                                0：无中断；
                                                                1：有中断； */
        unsigned int  frm_out_spc_err_stat : 1;  /* bit[16]   : 封装外部输出存储空间不足屏蔽后中断状态：
                                                                0：无中断；
                                                                1：有中断； */
        unsigned int  frm_rpt_dep_err_stat : 1;  /* bit[17]   : 封装外部正确帧长度上报空间不足屏蔽后中断状态：
                                                                0：无中断；
                                                                1：有中断； */
        unsigned int  reserved_1           : 6;  /* bit[18-23]: 保留 */
        unsigned int  frm_over_int_stat    : 1;  /* bit[24]   : 一套链表封装结束屏蔽后中断状态：
                                                                0：无中断；
                                                                1：有中断； */
        unsigned int  reserved_2           : 7;  /* bit[25-31]: 保留 */
    } reg;
} SOC_HDLC_FRM_INT_STATUS_UNION;
#endif
#define SOC_HDLC_FRM_INT_STATUS_frm_rd_err_stat_START       (8)
#define SOC_HDLC_FRM_INT_STATUS_frm_rd_err_stat_END         (8)
#define SOC_HDLC_FRM_INT_STATUS_frm_wr_err_stat_START       (9)
#define SOC_HDLC_FRM_INT_STATUS_frm_wr_err_stat_END         (9)
#define SOC_HDLC_FRM_INT_STATUS_frm_rd_timeout_stat_START   (10)
#define SOC_HDLC_FRM_INT_STATUS_frm_rd_timeout_stat_END     (10)
#define SOC_HDLC_FRM_INT_STATUS_frm_wr_timeout_stat_START   (11)
#define SOC_HDLC_FRM_INT_STATUS_frm_wr_timeout_stat_END     (11)
#define SOC_HDLC_FRM_INT_STATUS_frm_cfg_err_stat_START      (12)
#define SOC_HDLC_FRM_INT_STATUS_frm_cfg_err_stat_END        (12)
#define SOC_HDLC_FRM_INT_STATUS_frm_in_prm_err_stat_START   (13)
#define SOC_HDLC_FRM_INT_STATUS_frm_in_prm_err_stat_END     (13)
#define SOC_HDLC_FRM_INT_STATUS_frm_out_prm_err_stat_START  (14)
#define SOC_HDLC_FRM_INT_STATUS_frm_out_prm_err_stat_END    (14)
#define SOC_HDLC_FRM_INT_STATUS_frm_rpt_prm_err_stat_START  (15)
#define SOC_HDLC_FRM_INT_STATUS_frm_rpt_prm_err_stat_END    (15)
#define SOC_HDLC_FRM_INT_STATUS_frm_out_spc_err_stat_START  (16)
#define SOC_HDLC_FRM_INT_STATUS_frm_out_spc_err_stat_END    (16)
#define SOC_HDLC_FRM_INT_STATUS_frm_rpt_dep_err_stat_START  (17)
#define SOC_HDLC_FRM_INT_STATUS_frm_rpt_dep_err_stat_END    (17)
#define SOC_HDLC_FRM_INT_STATUS_frm_over_int_stat_START     (24)
#define SOC_HDLC_FRM_INT_STATUS_frm_over_int_stat_END       (24)


/*****************************************************************************
 结构名    : SOC_HDLC_FRM_INT_CLR_UNION
 结构说明  : FRM_INT_CLR 寄存器结构定义。地址偏移量:0x001C，初值:0x00000000，宽度:32
 寄存器说明: HDLC封装中断清除寄存器（增加AXI读写错误中断清除、AXI读写timeout中断清除、封装外部输出存储空间不足中断清除、封装外部正确帧长度上报空间不足中断清除、封装结束中断清除，删除实际下发数据多于、少于配置长度的中断清除）。
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  reserved_0          : 8;  /* bit[0-7]  : 保留 */
        unsigned int  frm_rd_err_clr      : 1;  /* bit[8]    : frm_rd_err中断清除，写1清除中断； */
        unsigned int  frm_wr_err_clr      : 1;  /* bit[9]    : frm_wr_err中断清除，写1清除中断； */
        unsigned int  frm_rd_timeout_clr  : 1;  /* bit[10]   : frm_rd_timeout中断清除，写1清除中断； */
        unsigned int  frm_wr_timeout_clr  : 1;  /* bit[11]   : frm_wr_timeout中断清除，写1清除中断； */
        unsigned int  frm_cfg_err_clr     : 1;  /* bit[12]   : frm_cfg_err中断清除，写1清除中断； */
        unsigned int  frm_in_prm_err_clr  : 1;  /* bit[13]   : frm_in_prm_err中断清除，写1清除中断； */
        unsigned int  frm_out_prm_err_clr : 1;  /* bit[14]   : frm_out_prm_err中断清除，写1清除中断； */
        unsigned int  frm_rpt_prm_err_clr : 1;  /* bit[15]   : frm_rpt_prm_err中断清除，写1清除中断； */
        unsigned int  frm_out_spc_err_clr : 1;  /* bit[16]   : frm_out_spc_err 中断清除，写1清除中断； */
        unsigned int  frm_rpt_dep_err_clr : 1;  /* bit[17]   : frm_rpt_dep_err 中断清除，写1清除中断； */
        unsigned int  reserved_1          : 6;  /* bit[18-23]: 保留 */
        unsigned int  frm_over_int_clr    : 1;  /* bit[24]   : frm_over_int 中断清除，写1清除中断； */
        unsigned int  reserved_2          : 7;  /* bit[25-31]: 保留 */
    } reg;
} SOC_HDLC_FRM_INT_CLR_UNION;
#endif
#define SOC_HDLC_FRM_INT_CLR_frm_rd_err_clr_START       (8)
#define SOC_HDLC_FRM_INT_CLR_frm_rd_err_clr_END         (8)
#define SOC_HDLC_FRM_INT_CLR_frm_wr_err_clr_START       (9)
#define SOC_HDLC_FRM_INT_CLR_frm_wr_err_clr_END         (9)
#define SOC_HDLC_FRM_INT_CLR_frm_rd_timeout_clr_START   (10)
#define SOC_HDLC_FRM_INT_CLR_frm_rd_timeout_clr_END     (10)
#define SOC_HDLC_FRM_INT_CLR_frm_wr_timeout_clr_START   (11)
#define SOC_HDLC_FRM_INT_CLR_frm_wr_timeout_clr_END     (11)
#define SOC_HDLC_FRM_INT_CLR_frm_cfg_err_clr_START      (12)
#define SOC_HDLC_FRM_INT_CLR_frm_cfg_err_clr_END        (12)
#define SOC_HDLC_FRM_INT_CLR_frm_in_prm_err_clr_START   (13)
#define SOC_HDLC_FRM_INT_CLR_frm_in_prm_err_clr_END     (13)
#define SOC_HDLC_FRM_INT_CLR_frm_out_prm_err_clr_START  (14)
#define SOC_HDLC_FRM_INT_CLR_frm_out_prm_err_clr_END    (14)
#define SOC_HDLC_FRM_INT_CLR_frm_rpt_prm_err_clr_START  (15)
#define SOC_HDLC_FRM_INT_CLR_frm_rpt_prm_err_clr_END    (15)
#define SOC_HDLC_FRM_INT_CLR_frm_out_spc_err_clr_START  (16)
#define SOC_HDLC_FRM_INT_CLR_frm_out_spc_err_clr_END    (16)
#define SOC_HDLC_FRM_INT_CLR_frm_rpt_dep_err_clr_START  (17)
#define SOC_HDLC_FRM_INT_CLR_frm_rpt_dep_err_clr_END    (17)
#define SOC_HDLC_FRM_INT_CLR_frm_over_int_clr_START     (24)
#define SOC_HDLC_FRM_INT_CLR_frm_over_int_clr_END       (24)


/*****************************************************************************
 结构名    : SOC_HDLC_FRM_CFG_UNION
 结构说明  : FRM_CFG 寄存器结构定义。地址偏移量:0x0020，初值:0x00000000，宽度:32
 寄存器说明: 封装子模块配置寄存器
            (将最低位改为封装输入一维链表或二位链表选择指示frm_in_lli_1dor2d)。
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  frm_in_lli_1dor2d : 1;  /* bit[0]    : 封装输入一维链表或二位链表选择指示寄存器 */
        unsigned int  frm_acfc          : 1;  /* bit[1]    : AC域压缩指示：
                                                             l 0：AC域无压缩；
                                                             l 1：表示AC域压缩，即封装帧中无AC域； */
        unsigned int  frm_pfc           : 2;  /* bit[2-3]  : P域压缩指示：
                                                             l 00：硬件模块添加P域，P域无压缩；
                                                             l 01：硬件模块添加P域，P域压缩；
                                                             l 11：硬件模块不添加P域；
                                                             l 其他：无效； */
        unsigned int  reserved          : 12; /* bit[4-15] : 保留 */
        unsigned int  frm_protocol      : 16; /* bit[16-31]: 封装协议值。有效协议值规定参见规格列表。 */
    } reg;
} SOC_HDLC_FRM_CFG_UNION;
#endif
#define SOC_HDLC_FRM_CFG_frm_in_lli_1dor2d_START  (0)
#define SOC_HDLC_FRM_CFG_frm_in_lli_1dor2d_END    (0)
#define SOC_HDLC_FRM_CFG_frm_acfc_START           (1)
#define SOC_HDLC_FRM_CFG_frm_acfc_END             (1)
#define SOC_HDLC_FRM_CFG_frm_pfc_START            (2)
#define SOC_HDLC_FRM_CFG_frm_pfc_END              (3)
#define SOC_HDLC_FRM_CFG_frm_protocol_START       (16)
#define SOC_HDLC_FRM_CFG_frm_protocol_END         (31)


/*****************************************************************************
 结构名    : SOC_HDLC_FRM_ACCM_UNION
 结构说明  : FRM_ACCM 寄存器结构定义。地址偏移量:0x0024，初值:0x00000000，宽度:32
 寄存器说明: 封装子模块转义使能(LCP协议该寄存器无效)。
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  hdlc_frm_accm : 32; /* bit[0-31]: 转义使能，从bit 0至 bit 31 分别对应0x00~0x1F 32个字符：
                                                        0：转义禁止；
                                                        1：转义使能。 */
    } reg;
} SOC_HDLC_FRM_ACCM_UNION;
#endif
#define SOC_HDLC_FRM_ACCM_hdlc_frm_accm_START  (0)
#define SOC_HDLC_FRM_ACCM_hdlc_frm_accm_END    (31)


/*****************************************************************************
 结构名    : SOC_HDLC_FRM_STATUS_UNION
 结构说明  : FRM_STATUS 寄存器结构定义。地址偏移量:0x0028，初值:0x00000000，宽度:32
 寄存器说明: 封装子模块状态寄存器（将frm_frm_len删除，增加frm_out_seg_num，和frm_valid_num，将frm_blk_done改为frm_all_pkt_done）。
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  frm_all_pkt_done : 1;  /* bit[0]    : 封装完成标志
                                                            0：未完成一套链表数据处理；
                                                            1：完成一套链表数据处理； */
        unsigned int  frm_error_index  : 1;  /* bit[1]    : 封装发生错误指示 */
        unsigned int  reserved         : 6;  /* bit[2-7]  : 保留 */
        unsigned int  frm_valid_num    : 8;  /* bit[8-15] : 一套链表封装出的有效帧帧数 */
        unsigned int  frm_out_seg_num  : 16; /* bit[16-31]: 一套链表封装出的有效帧存放占用片段个数 */
    } reg;
} SOC_HDLC_FRM_STATUS_UNION;
#endif
#define SOC_HDLC_FRM_STATUS_frm_all_pkt_done_START  (0)
#define SOC_HDLC_FRM_STATUS_frm_all_pkt_done_END    (0)
#define SOC_HDLC_FRM_STATUS_frm_error_index_START   (1)
#define SOC_HDLC_FRM_STATUS_frm_error_index_END     (1)
#define SOC_HDLC_FRM_STATUS_frm_valid_num_START     (8)
#define SOC_HDLC_FRM_STATUS_frm_valid_num_END       (15)
#define SOC_HDLC_FRM_STATUS_frm_out_seg_num_START   (16)
#define SOC_HDLC_FRM_STATUS_frm_out_seg_num_END     (31)


/*****************************************************************************
 结构名    : SOC_HDLC_FRM_IN_LLI_ADDR_UNION
 结构说明  : FRM_IN_LLI_ADDR 寄存器结构定义。地址偏移量:0x0030，初值:0x00000000，宽度:32
 寄存器说明: 封装输入链表起始地址寄存器。
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  frm_in_lli_addr : 32; /* bit[0-31]: 封装输入主链表起始地址寄存器:
                                                          软件配置该寄存器为主链表第一个节点的起始地址，HDLC根据该地址读入主链表第一个节点的参数，参数中下一个主链表节点起始地址会更新该寄存器，在当前主链表节点所指数据包处理完后，HDLC根据该寄存器值（下一个主链表节点起始地址）读入下一个主链表节点参数，最后一个主链表节点参数中的下一个主链表节点起始地址为0。 */
    } reg;
} SOC_HDLC_FRM_IN_LLI_ADDR_UNION;
#endif
#define SOC_HDLC_FRM_IN_LLI_ADDR_frm_in_lli_addr_START  (0)
#define SOC_HDLC_FRM_IN_LLI_ADDR_frm_in_lli_addr_END    (31)


/*****************************************************************************
 结构名    : SOC_HDLC_FRM_IN_SUBLLI_ADDR_UNION
 结构说明  : FRM_IN_SUBLLI_ADDR 寄存器结构定义。地址偏移量:0x0034，初值:0x00000000，宽度:32
 寄存器说明: 当frm_in_lii_1dor2d为0，表示待封装输入数据包起始地址寄存器；
            当frm_in_lii_1dor2d为1，表示封装输入副链表参数起始地址寄存器。
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  frm_in_sublli_addr : 32; /* bit[0-31]: 当frm_in_lii_1dor2d为0，表示待封装输入数据包起始地址寄存器；
                                                             当frm_in_lii_1dor2d为1，表示封装输入副链表参数起始地址寄存器；
                                                             主链表参数中含有副链表第一个节点的起始地址，HDLC根据该地址读入副链表第一个节点的参数，参数中下一个副链表节点起始地址会更新该寄存器，在当前副链表节点所对应数据包处理完后，HDLC根据该寄存器值（下一个副链表节点起始地址）读入下一个副链表节点参数，最后一个副链表节点参数中的下一个副链表节点起始地址为0。 */
    } reg;
} SOC_HDLC_FRM_IN_SUBLLI_ADDR_UNION;
#endif
#define SOC_HDLC_FRM_IN_SUBLLI_ADDR_frm_in_sublli_addr_START  (0)
#define SOC_HDLC_FRM_IN_SUBLLI_ADDR_frm_in_sublli_addr_END    (31)


/*****************************************************************************
 结构名    : SOC_HDLC_FRM_IN_PKT_LEN_UNION
 结构说明  : FRM_IN_PKT_LEN 寄存器结构定义。地址偏移量:0x0038，初值:0x00000000，宽度:32
 寄存器说明: 封装输入主链表节点所指待封装输入数据包长度寄存器。
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  frm_in_pkt_len : 16; /* bit[0-15] : 封装输入主链表节点所指待封装输入数据包长度寄存器：
                                                          规定不得超过1502B，该长度为0x001~0x5DE，即0x1表示长度为1B；
                                                          根据读入主链表节点参数中的封装输入数据包长度更新该寄存器 */
        unsigned int  reserved       : 16; /* bit[16-31]: 保留 */
    } reg;
} SOC_HDLC_FRM_IN_PKT_LEN_UNION;
#endif
#define SOC_HDLC_FRM_IN_PKT_LEN_frm_in_pkt_len_START  (0)
#define SOC_HDLC_FRM_IN_PKT_LEN_frm_in_pkt_len_END    (15)


/*****************************************************************************
 结构名    : SOC_HDLC_FRM_IN_BLK_ADDR_UNION
 结构说明  : FRM_IN_BLK_ADDR 寄存器结构定义。地址偏移量:0x003C，初值:0x00000000，宽度:32
 寄存器说明: 封装输入副链表节点所指待封装输入数据分组起始地址寄存器。
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  frm_in_blk_addr : 32; /* bit[0-31]: 封装输入副链表节点所指待封装输入数据分组起始地址寄存器：
                                                          根据读入副链表节点参数中的待封装输入数据分组起始地址更新该寄存器 */
    } reg;
} SOC_HDLC_FRM_IN_BLK_ADDR_UNION;
#endif
#define SOC_HDLC_FRM_IN_BLK_ADDR_frm_in_blk_addr_START  (0)
#define SOC_HDLC_FRM_IN_BLK_ADDR_frm_in_blk_addr_END    (31)


/*****************************************************************************
 结构名    : SOC_HDLC_FRM_IN_BLK_LEN_UNION
 结构说明  : FRM_IN_BLK_LEN 寄存器结构定义。地址偏移量:0x0040，初值:0x00000000，宽度:32
 寄存器说明: 封装输入副链表节点所指待封装输入数据分组长度寄存器。
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  frm_in_blk_len : 16; /* bit[0-15] : 封装输入副链表节点所指待封装输入数据分组长度寄存器 */
        unsigned int  reserved       : 16; /* bit[16-31]: 保留 */
    } reg;
} SOC_HDLC_FRM_IN_BLK_LEN_UNION;
#endif
#define SOC_HDLC_FRM_IN_BLK_LEN_frm_in_blk_len_START  (0)
#define SOC_HDLC_FRM_IN_BLK_LEN_frm_in_blk_len_END    (15)


/*****************************************************************************
 结构名    : SOC_HDLC_FRM_OUT_LLI_ADDR_UNION
 结构说明  : FRM_OUT_LLI_ADDR 寄存器结构定义。地址偏移量:0x0044，初值:0x00000000，宽度:32
 寄存器说明: 封装输出链表起始地址寄存器。
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  frm_out_lli_addr : 32; /* bit[0-31]: 封装输出链表起始地址寄存器：
                                                           软件配置该寄存器为链表第一个节点的起始地址，HDLC根据该地址读入链表第一个节点的参数，参数中下一个链表节点起始地址会更新该寄存器，在当前链表节点所指数据包处理完后，HDLC根据该寄存器值（下一个链表节点起始地址）读入下一个链表节点参数，最后一个链表节点参数中下一个链表节点起始地址为0。 */
    } reg;
} SOC_HDLC_FRM_OUT_LLI_ADDR_UNION;
#endif
#define SOC_HDLC_FRM_OUT_LLI_ADDR_frm_out_lli_addr_START  (0)
#define SOC_HDLC_FRM_OUT_LLI_ADDR_frm_out_lli_addr_END    (31)


/*****************************************************************************
 结构名    : SOC_HDLC_FRM_OUT_SPC_ADDR_UNION
 结构说明  : FRM_OUT_SPC_ADDR 寄存器结构定义。地址偏移量:0x0048，初值:0x00000000，宽度:32
 寄存器说明: 封装输出链表节点所指存储空间起始地址寄存器。
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  frm_out_spc_addr : 32; /* bit[0-31]: 封装输出链表节点所指存储空间起始地址寄存器：
                                                           根据读入链表节点参数中的存储空间起始地址更新该寄存器 */
    } reg;
} SOC_HDLC_FRM_OUT_SPC_ADDR_UNION;
#endif
#define SOC_HDLC_FRM_OUT_SPC_ADDR_frm_out_spc_addr_START  (0)
#define SOC_HDLC_FRM_OUT_SPC_ADDR_frm_out_spc_addr_END    (31)


/*****************************************************************************
 结构名    : SOC_HDLC_FRM_OUT_SPC_DEP_UNION
 结构说明  : FRM_OUT_SPC_DEP 寄存器结构定义。地址偏移量:0x004C，初值:0x00000000，宽度:32
 寄存器说明: 封装输出链表节点所指存储空间深度寄存器。
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  frm_out_spc_dep : 16; /* bit[0-15] : 封装输出链表节点所指存储空间深度寄存器：
                                                           根据读入链表节点参数中的存储空间深度更新该寄存器 */
        unsigned int  reserved        : 16; /* bit[16-31]: 保留 */
    } reg;
} SOC_HDLC_FRM_OUT_SPC_DEP_UNION;
#endif
#define SOC_HDLC_FRM_OUT_SPC_DEP_frm_out_spc_dep_START  (0)
#define SOC_HDLC_FRM_OUT_SPC_DEP_frm_out_spc_dep_END    (15)


/*****************************************************************************
 结构名    : SOC_HDLC_FRM_RPT_ADDR_UNION
 结构说明  : FRM_RPT_ADDR 寄存器结构定义。地址偏移量:0x0050，初值:0x00000000，宽度:32
 寄存器说明: 封装各输出正确帧长度存储空间起始地址寄存器。
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  frm_rpt_addr : 32; /* bit[0-31]: 封装各输出正确帧长度存储空间起始地址寄存器：
                                                       由软件配置 */
    } reg;
} SOC_HDLC_FRM_RPT_ADDR_UNION;
#endif
#define SOC_HDLC_FRM_RPT_ADDR_frm_rpt_addr_START  (0)
#define SOC_HDLC_FRM_RPT_ADDR_frm_rpt_addr_END    (31)


/*****************************************************************************
 结构名    : SOC_HDLC_FRM_RPT_DEP_UNION
 结构说明  : FRM_RPT_DEP 寄存器结构定义。地址偏移量:0x0054，初值:0x00000000，宽度:32
 寄存器说明: 封装各输出正确帧长度存储空间深度寄存器。
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  frm_rpt_dep : 16; /* bit[0-15] : 封装各输出正确帧长度存储空间深度寄存器：
                                                       由软件配置 */
        unsigned int  reserved    : 16; /* bit[16-31]: 保留 */
    } reg;
} SOC_HDLC_FRM_RPT_DEP_UNION;
#endif
#define SOC_HDLC_FRM_RPT_DEP_frm_rpt_dep_START  (0)
#define SOC_HDLC_FRM_RPT_DEP_frm_rpt_dep_END    (15)


/*****************************************************************************
 结构名    : SOC_HDLC_DEF_EN_UNION
 结构说明  : DEF_EN 寄存器结构定义。地址偏移量:0x0060，初值:0x00000000，宽度:32
 寄存器说明: HDLC解封装相关使能寄存器（包括解封装使能、解封装参数配置错误中断使能、AXI读写错误中断使能、AXI读写timeout中断使能、解封装解出有效LCP帧暂停中断使能、解封装外部输出存储空间存满暂停中断使能、解封装外部正确帧信息上报空间存满暂停中断使能、解封装结束中断使能，删除实际下发数据多于、少于配置长度的异常中断使能）。
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  def_en             : 1;  /* bit[0]    : 一套输入链表解封装使能，软件向def_en写入1'b1启动解封装工作；
                                                              一套输入链表解封装完成后，由硬件自动对def_en清零；
                                                              解封装过程出错时，硬件也会对def_en自动清零，使内部状态机返回IDLE状态；
                                                              读该寄存器返回解封装处理状态。
                                                              写时设置一套输入链表解封装使能：
                                                              0：不使能解封装处理；
                                                              1：使能解封装处理；
                                                              读时返回一套输入链表解封装处理状态：
                                                              0：没在进行解封装处理；
                                                              1：正在进行解封装处理。 */
        unsigned int  reserved_0         : 7;  /* bit[1-7]  : 保留 */
        unsigned int  def_rd_err_en      : 1;  /* bit[8]    : 解封装时AXI总线读操作错误中断使能：
                                                              0：中断禁止；
                                                              1：中断使能； */
        unsigned int  def_wr_err_en      : 1;  /* bit[9]    : 解封装时AXI总线写操作错误中断使能：
                                                              0：中断禁止；
                                                              1：中断使能； */
        unsigned int  def_rd_timeout_en  : 1;  /* bit[10]   : 解封装时AXI总线读请求timeout中断使能：
                                                              0：中断禁止；
                                                              1：中断使能； */
        unsigned int  def_wr_timeout_en  : 1;  /* bit[11]   : 解封装时AXI总线写请求timeout中断使能：
                                                              0：中断禁止；
                                                              1：中断使能； */
        unsigned int  def_cfg_err_en     : 1;  /* bit[12]   : 解封装协议压缩指示配置错误中断使能：
                                                              0：中断禁止；
                                                              1：中断使能； */
        unsigned int  def_in_prm_err_en  : 1;  /* bit[13]   : 解封装输入链表相关参数错误中断使能：
                                                              0：中断禁止；
                                                              1：中断使能； */
        unsigned int  def_out_prm_err_en : 1;  /* bit[14]   : 解封装输出空间相关参数错误中断使能：
                                                              0：中断禁止；
                                                              1：中断使能； */
        unsigned int  def_rpt_prm_err_en : 1;  /* bit[15]   : 解封装上报空间相关参数错误中断使能：
                                                              0：中断禁止；
                                                              1：中断使能； */
        unsigned int  def_lcp_int_en     : 1;  /* bit[16]   : 解封装解出LCP帧中断上报使能：
                                                              0：中断禁止；
                                                              1：中断使能； */
        unsigned int  def_out_spc_ful_en : 1;  /* bit[17]   : 解封装外部输出存储空间存满暂停中断使能：
                                                              0：中断禁止；
                                                              1：中断使能； */
        unsigned int  def_rpt_ful_en     : 1;  /* bit[18]   : 解封装外部正确帧信息上报空间存满暂停中断使能：
                                                              0：中断禁止；
                                                              1：中断使能； */
        unsigned int  reserved_1         : 5;  /* bit[19-23]: 保留 */
        unsigned int  def_over_int_en    : 1;  /* bit[24]   : 一套输入链表解封装结束中断使能：
                                                              0：中断禁止；
                                                              1：中断使能； */
        unsigned int  reserved_2         : 7;  /* bit[25-31]: 保留 */
    } reg;
} SOC_HDLC_DEF_EN_UNION;
#endif
#define SOC_HDLC_DEF_EN_def_en_START              (0)
#define SOC_HDLC_DEF_EN_def_en_END                (0)
#define SOC_HDLC_DEF_EN_def_rd_err_en_START       (8)
#define SOC_HDLC_DEF_EN_def_rd_err_en_END         (8)
#define SOC_HDLC_DEF_EN_def_wr_err_en_START       (9)
#define SOC_HDLC_DEF_EN_def_wr_err_en_END         (9)
#define SOC_HDLC_DEF_EN_def_rd_timeout_en_START   (10)
#define SOC_HDLC_DEF_EN_def_rd_timeout_en_END     (10)
#define SOC_HDLC_DEF_EN_def_wr_timeout_en_START   (11)
#define SOC_HDLC_DEF_EN_def_wr_timeout_en_END     (11)
#define SOC_HDLC_DEF_EN_def_cfg_err_en_START      (12)
#define SOC_HDLC_DEF_EN_def_cfg_err_en_END        (12)
#define SOC_HDLC_DEF_EN_def_in_prm_err_en_START   (13)
#define SOC_HDLC_DEF_EN_def_in_prm_err_en_END     (13)
#define SOC_HDLC_DEF_EN_def_out_prm_err_en_START  (14)
#define SOC_HDLC_DEF_EN_def_out_prm_err_en_END    (14)
#define SOC_HDLC_DEF_EN_def_rpt_prm_err_en_START  (15)
#define SOC_HDLC_DEF_EN_def_rpt_prm_err_en_END    (15)
#define SOC_HDLC_DEF_EN_def_lcp_int_en_START      (16)
#define SOC_HDLC_DEF_EN_def_lcp_int_en_END        (16)
#define SOC_HDLC_DEF_EN_def_out_spc_ful_en_START  (17)
#define SOC_HDLC_DEF_EN_def_out_spc_ful_en_END    (17)
#define SOC_HDLC_DEF_EN_def_rpt_ful_en_START      (18)
#define SOC_HDLC_DEF_EN_def_rpt_ful_en_END        (18)
#define SOC_HDLC_DEF_EN_def_over_int_en_START     (24)
#define SOC_HDLC_DEF_EN_def_over_int_en_END       (24)


/*****************************************************************************
 结构名    : SOC_HDLC_DEF_RAW_INT_UNION
 结构说明  : DEF_RAW_INT 寄存器结构定义。地址偏移量:0x0064，初值:0x00000000，宽度:32
 寄存器说明: HDLC原始中断状态寄存器（增加AXI读写错误原始中断、AXI读写timeout原始中断、解封装解出有效LCP帧原始暂停中断、解封装外部输出存储空间存满暂停原始中断、解封装外部正确帧信息上报空间存满暂停原始中断、解封装结束原始中断，删除实际下发数据多于、少于配置长度的原始中断）。
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  reserved_0          : 8;  /* bit[0-7]  : 保留 */
        unsigned int  def_rd_err_raw      : 1;  /* bit[8]    : 解封装时AXI总线读操作错误原始中断：
                                                               0：无中断；
                                                               1：有中断； */
        unsigned int  def_wr_err_raw      : 1;  /* bit[9]    : 解封装时AXI总线写操作错误原始中断：
                                                               0：无中断；
                                                               1：有中断； */
        unsigned int  def_rd_timeoutraw   : 1;  /* bit[10]   : 解封装时AXI总线读请求timeout原始中断：
                                                               0：无中断；
                                                               1：有中断； */
        unsigned int  def_wr_timeout_raw  : 1;  /* bit[11]   : 解封装时AXI总线写请求timeout原始中断：
                                                               0：无中断；
                                                               1：有中断； */
        unsigned int  def_cfg_err_raw     : 1;  /* bit[12]   : 解封装模块异常原始中断，表示参数配置错误，
                                                               0：无中断；
                                                               1：有中断； */
        unsigned int  def_in_prm_err_raw  : 1;  /* bit[13]   : 解封装输入链表相关参数错误原始中断：
                                                               0：无中断；
                                                               1：有中断； */
        unsigned int  def_out_prm_err_raw : 1;  /* bit[14]   : 解封装输出空间相关参数错误原始中断：
                                                               0：无中断；
                                                               1：有中断； */
        unsigned int  def_rpt_prm_err_raw : 1;  /* bit[15]   : 解封装上报空间相关参数错误原始中断：
                                                               0：无中断；
                                                               1：有中断； */
        unsigned int  def_lcp_int_raw     : 1;  /* bit[16]   : 解封装解出LCP帧原始中断：
                                                               0：无中断；
                                                               1：有中断； */
        unsigned int  def_out_spc_ful_raw : 1;  /* bit[17]   : 解封装外部输出存储空间存满暂停原始中断：
                                                               0：无中断；
                                                               1：有中断； */
        unsigned int  def_rpt_ful_raw     : 1;  /* bit[18]   : 解封装外部正确帧信息上报空间存满暂停原始中断：
                                                               0：无中断；
                                                               1：有中断； */
        unsigned int  reserved_1          : 5;  /* bit[19-23]: 保留 */
        unsigned int  def_over_int_raw    : 1;  /* bit[24]   : 一套输入链表解封装结束原始中断：
                                                               0：无中断；
                                                               1：有中断； */
        unsigned int  reserved_2          : 7;  /* bit[25-31]: 保留 */
    } reg;
} SOC_HDLC_DEF_RAW_INT_UNION;
#endif
#define SOC_HDLC_DEF_RAW_INT_def_rd_err_raw_START       (8)
#define SOC_HDLC_DEF_RAW_INT_def_rd_err_raw_END         (8)
#define SOC_HDLC_DEF_RAW_INT_def_wr_err_raw_START       (9)
#define SOC_HDLC_DEF_RAW_INT_def_wr_err_raw_END         (9)
#define SOC_HDLC_DEF_RAW_INT_def_rd_timeoutraw_START    (10)
#define SOC_HDLC_DEF_RAW_INT_def_rd_timeoutraw_END      (10)
#define SOC_HDLC_DEF_RAW_INT_def_wr_timeout_raw_START   (11)
#define SOC_HDLC_DEF_RAW_INT_def_wr_timeout_raw_END     (11)
#define SOC_HDLC_DEF_RAW_INT_def_cfg_err_raw_START      (12)
#define SOC_HDLC_DEF_RAW_INT_def_cfg_err_raw_END        (12)
#define SOC_HDLC_DEF_RAW_INT_def_in_prm_err_raw_START   (13)
#define SOC_HDLC_DEF_RAW_INT_def_in_prm_err_raw_END     (13)
#define SOC_HDLC_DEF_RAW_INT_def_out_prm_err_raw_START  (14)
#define SOC_HDLC_DEF_RAW_INT_def_out_prm_err_raw_END    (14)
#define SOC_HDLC_DEF_RAW_INT_def_rpt_prm_err_raw_START  (15)
#define SOC_HDLC_DEF_RAW_INT_def_rpt_prm_err_raw_END    (15)
#define SOC_HDLC_DEF_RAW_INT_def_lcp_int_raw_START      (16)
#define SOC_HDLC_DEF_RAW_INT_def_lcp_int_raw_END        (16)
#define SOC_HDLC_DEF_RAW_INT_def_out_spc_ful_raw_START  (17)
#define SOC_HDLC_DEF_RAW_INT_def_out_spc_ful_raw_END    (17)
#define SOC_HDLC_DEF_RAW_INT_def_rpt_ful_raw_START      (18)
#define SOC_HDLC_DEF_RAW_INT_def_rpt_ful_raw_END        (18)
#define SOC_HDLC_DEF_RAW_INT_def_over_int_raw_START     (24)
#define SOC_HDLC_DEF_RAW_INT_def_over_int_raw_END       (24)


/*****************************************************************************
 结构名    : SOC_HDLC_DEF_INT_STATUS_UNION
 结构说明  : DEF_INT_STATUS 寄存器结构定义。地址偏移量:0x0068，初值:0x00000000，宽度:32
 寄存器说明: HDLC屏蔽后中断状态寄存器（增加AXI读写错误屏蔽后中断状态、AXI读写timeout屏蔽后中断状态、解封装解出有效LCP帧暂停屏蔽后中断状态、解封装外部输出存储空间存满暂停屏蔽后中断状态、解封装外部正确帧信息上报空间存满暂停屏蔽后中断状态、解封装结束屏蔽后中断状态，删除实际下发数据多于、少于配置长度的屏蔽后中断状态）。
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  reserved_0           : 8;  /* bit[0-7]  : 保留 */
        unsigned int  def_rd_err_stat      : 1;  /* bit[8]    : 解封装时AXI总线读操作错误屏蔽后中断状态：
                                                                0：无中断；
                                                                1：有中断； */
        unsigned int  def_wr_err_stat      : 1;  /* bit[9]    : 解封装时AXI总线写操作错误屏蔽后中断状态：
                                                                0：无中断；
                                                                1：有中断； */
        unsigned int  def_rd_timeoutstat   : 1;  /* bit[10]   : 解封装时AXI总线读请求timeout屏蔽后中断状态：
                                                                0：无中断；
                                                                1：有中断； */
        unsigned int  def_wr_timeout_stat  : 1;  /* bit[11]   : 解封装时AXI总线写请求timeout屏蔽后中断状态：
                                                                0：无中断；
                                                                1：有中断； */
        unsigned int  def_cfg_err_stat     : 1;  /* bit[12]   : 解封装模块屏蔽后中断状态，表示参数配置错误中断，
                                                                0：无中断；
                                                                1：有中断； */
        unsigned int  def_in_prm_err_stat  : 1;  /* bit[13]   : 解封装输入链表相关参数错误屏蔽后中断状态：
                                                                0：无中断；
                                                                1：有中断； */
        unsigned int  def_out_prm_err_stat : 1;  /* bit[14]   : 解封装输出空间相关参数错误屏蔽后中断状态：
                                                                0：无中断；
                                                                1：有中断； */
        unsigned int  def_rpt_prm_err_stat : 1;  /* bit[15]   : 解封装上报空间相关参数错误屏蔽后中断状态：
                                                                0：无中断；
                                                                1：有中断； */
        unsigned int  def_lcp_int_stat     : 1;  /* bit[16]   : 解封装解出LCP帧屏蔽后中断状态：
                                                                0：无中断；
                                                                1：有中断； */
        unsigned int  def_out_spc_ful_stat : 1;  /* bit[17]   : 解封装外部输出存储空间存满暂停屏蔽后中断状态：
                                                                0：无中断；
                                                                1：有中断； */
        unsigned int  def_rpt_ful_stat     : 1;  /* bit[18]   : 解封装外部正确帧信息上报空间存满暂停屏蔽后中断状态：
                                                                0：无中断；
                                                                1：有中断； */
        unsigned int  reserved_1           : 5;  /* bit[19-23]: 保留 */
        unsigned int  def_over_int_stat    : 1;  /* bit[24]   : 一套输入链表解封装结束屏蔽后中断状态：
                                                                0：无中断；
                                                                1：有中断； */
        unsigned int  reserved_2           : 7;  /* bit[25-31]: 保留 */
    } reg;
} SOC_HDLC_DEF_INT_STATUS_UNION;
#endif
#define SOC_HDLC_DEF_INT_STATUS_def_rd_err_stat_START       (8)
#define SOC_HDLC_DEF_INT_STATUS_def_rd_err_stat_END         (8)
#define SOC_HDLC_DEF_INT_STATUS_def_wr_err_stat_START       (9)
#define SOC_HDLC_DEF_INT_STATUS_def_wr_err_stat_END         (9)
#define SOC_HDLC_DEF_INT_STATUS_def_rd_timeoutstat_START    (10)
#define SOC_HDLC_DEF_INT_STATUS_def_rd_timeoutstat_END      (10)
#define SOC_HDLC_DEF_INT_STATUS_def_wr_timeout_stat_START   (11)
#define SOC_HDLC_DEF_INT_STATUS_def_wr_timeout_stat_END     (11)
#define SOC_HDLC_DEF_INT_STATUS_def_cfg_err_stat_START      (12)
#define SOC_HDLC_DEF_INT_STATUS_def_cfg_err_stat_END        (12)
#define SOC_HDLC_DEF_INT_STATUS_def_in_prm_err_stat_START   (13)
#define SOC_HDLC_DEF_INT_STATUS_def_in_prm_err_stat_END     (13)
#define SOC_HDLC_DEF_INT_STATUS_def_out_prm_err_stat_START  (14)
#define SOC_HDLC_DEF_INT_STATUS_def_out_prm_err_stat_END    (14)
#define SOC_HDLC_DEF_INT_STATUS_def_rpt_prm_err_stat_START  (15)
#define SOC_HDLC_DEF_INT_STATUS_def_rpt_prm_err_stat_END    (15)
#define SOC_HDLC_DEF_INT_STATUS_def_lcp_int_stat_START      (16)
#define SOC_HDLC_DEF_INT_STATUS_def_lcp_int_stat_END        (16)
#define SOC_HDLC_DEF_INT_STATUS_def_out_spc_ful_stat_START  (17)
#define SOC_HDLC_DEF_INT_STATUS_def_out_spc_ful_stat_END    (17)
#define SOC_HDLC_DEF_INT_STATUS_def_rpt_ful_stat_START      (18)
#define SOC_HDLC_DEF_INT_STATUS_def_rpt_ful_stat_END        (18)
#define SOC_HDLC_DEF_INT_STATUS_def_over_int_stat_START     (24)
#define SOC_HDLC_DEF_INT_STATUS_def_over_int_stat_END       (24)


/*****************************************************************************
 结构名    : SOC_HDLC_DEF_INT_CLR_UNION
 结构说明  : DEF_INT_CLR 寄存器结构定义。地址偏移量:0x006C，初值:0x00000000，宽度:32
 寄存器说明: HDLC中断清除寄存器（增加AXI读写错误中断清除、AXI读写timeout中断清除、解封装解出有效LCP帧暂停中断清除、解封装外部输出存储空间存满暂停中断清除、解封装外部正确帧信息上报空间存满暂停中断清除、解封装结束中断清除，删除实际下发数据多于、少于配置长度的中断清除）。
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  reserved_0          : 8;  /* bit[0-7]  : 保留 */
        unsigned int  def_rd_err_clr      : 1;  /* bit[8]    : def_rd_err中断清除，写1清除中断； */
        unsigned int  def_wr_err_clr      : 1;  /* bit[9]    : def_wr_err中断清除，写1清除中断； */
        unsigned int  def_rd_timeoutclr   : 1;  /* bit[10]   : def_rd_timeout中断清除，写1清除中断； */
        unsigned int  def_wr_timeout_clr  : 1;  /* bit[11]   : def_wr_timeout中断清除，写1清除中断； */
        unsigned int  def_cfg_err_clr     : 1;  /* bit[12]   : def_cfg_err中断清除，写1清除中断； */
        unsigned int  def_in_prm_err_clr  : 1;  /* bit[13]   : def_in_prm_err中断清除，写1清除中断； */
        unsigned int  def_out_prm_err_clr : 1;  /* bit[14]   : def_out_prm_err中断清除，写1清除中断； */
        unsigned int  def_rpt_prm_err_clr : 1;  /* bit[15]   : def_rpt_prm_err中断清除，写1清除中断； */
        unsigned int  def_lcp_int_clr     : 1;  /* bit[16]   : def_lcp_int 中断清除，写1清除中断； */
        unsigned int  def_out_spc_ful_clr : 1;  /* bit[17]   : def_out_spc_ful 中断清除，写1清除中断； */
        unsigned int  def_rpt_ful_clr     : 1;  /* bit[18]   : def_rpt_ful 中断清除，写1清除中断； */
        unsigned int  reserved_1          : 5;  /* bit[19-23]: 保留 */
        unsigned int  def_over_int_clr    : 1;  /* bit[24]   : def_over_int 中断清除，写1清除中断； */
        unsigned int  reserved_2          : 7;  /* bit[25-31]: 保留 */
    } reg;
} SOC_HDLC_DEF_INT_CLR_UNION;
#endif
#define SOC_HDLC_DEF_INT_CLR_def_rd_err_clr_START       (8)
#define SOC_HDLC_DEF_INT_CLR_def_rd_err_clr_END         (8)
#define SOC_HDLC_DEF_INT_CLR_def_wr_err_clr_START       (9)
#define SOC_HDLC_DEF_INT_CLR_def_wr_err_clr_END         (9)
#define SOC_HDLC_DEF_INT_CLR_def_rd_timeoutclr_START    (10)
#define SOC_HDLC_DEF_INT_CLR_def_rd_timeoutclr_END      (10)
#define SOC_HDLC_DEF_INT_CLR_def_wr_timeout_clr_START   (11)
#define SOC_HDLC_DEF_INT_CLR_def_wr_timeout_clr_END     (11)
#define SOC_HDLC_DEF_INT_CLR_def_cfg_err_clr_START      (12)
#define SOC_HDLC_DEF_INT_CLR_def_cfg_err_clr_END        (12)
#define SOC_HDLC_DEF_INT_CLR_def_in_prm_err_clr_START   (13)
#define SOC_HDLC_DEF_INT_CLR_def_in_prm_err_clr_END     (13)
#define SOC_HDLC_DEF_INT_CLR_def_out_prm_err_clr_START  (14)
#define SOC_HDLC_DEF_INT_CLR_def_out_prm_err_clr_END    (14)
#define SOC_HDLC_DEF_INT_CLR_def_rpt_prm_err_clr_START  (15)
#define SOC_HDLC_DEF_INT_CLR_def_rpt_prm_err_clr_END    (15)
#define SOC_HDLC_DEF_INT_CLR_def_lcp_int_clr_START      (16)
#define SOC_HDLC_DEF_INT_CLR_def_lcp_int_clr_END        (16)
#define SOC_HDLC_DEF_INT_CLR_def_out_spc_ful_clr_START  (17)
#define SOC_HDLC_DEF_INT_CLR_def_out_spc_ful_clr_END    (17)
#define SOC_HDLC_DEF_INT_CLR_def_rpt_ful_clr_START      (18)
#define SOC_HDLC_DEF_INT_CLR_def_rpt_ful_clr_END        (18)
#define SOC_HDLC_DEF_INT_CLR_def_over_int_clr_START     (24)
#define SOC_HDLC_DEF_INT_CLR_def_over_int_clr_END       (24)


/*****************************************************************************
 结构名    : SOC_HDLC_DEF_CFG_UNION
 结构说明  : DEF_CFG 寄存器结构定义。地址偏移量:0x0070，初值:0x00000000，宽度:32
 寄存器说明: 解封装子模块配置寄存器
            (将最低位改为def_uncompleted_ago，用于指示对应当前解封装输入链表，同一PPP/IP拨号的以前最近解封装输入链表是否有解出非完整帧，为了支持多个PPP/IP拨号而增加的配置：0，没有；1，有)。
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  def_uncompleted_ago : 1;  /* bit[0]   : 用于指示对应当前解封装输入链表，同一PPP/IP拨号的以前最近解封装输入链表是否有解出非完整帧，为了支持多个PPP/IP拨号而增加的配置：0，没有；1，有 */
        unsigned int  def_acfc            : 1;  /* bit[1]   : AC域压缩指示：
                                                              0：AC域无压缩；
                                                              1：表示AC域压缩； */
        unsigned int  def_pfc             : 2;  /* bit[2-3] : P域压缩指示：
                                                              l 00：P域无压缩，需剥离； 
                                                              l 01：P域压缩，需剥离；
                                                              l 11：P域不剥离；
                                                              l 其他：无效； */
        unsigned int  reserved            : 28; /* bit[4-31]: 保留 */
    } reg;
} SOC_HDLC_DEF_CFG_UNION;
#endif
#define SOC_HDLC_DEF_CFG_def_uncompleted_ago_START  (0)
#define SOC_HDLC_DEF_CFG_def_uncompleted_ago_END    (0)
#define SOC_HDLC_DEF_CFG_def_acfc_START             (1)
#define SOC_HDLC_DEF_CFG_def_acfc_END               (1)
#define SOC_HDLC_DEF_CFG_def_pfc_START              (2)
#define SOC_HDLC_DEF_CFG_def_pfc_END                (3)


/*****************************************************************************
 结构名    : SOC_HDLC_DEF_UNCOMPLETED_LEN_UNION
 结构说明  : DEF_UNCOMPLETED_LEN 寄存器结构定义。地址偏移量:0x0074，初值:0x00000000，宽度:32
 寄存器说明: 对应当前解封装输入链表，同一PPP/IP拨号的以前最近解封装输入链表解出非完整帧的长度，为了支持多个PPP/IP拨号而增加的配置。
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  def_uncompleted_len : 16; /* bit[0-15] : 对应当前解封装输入链表，同一PPP/IP拨号的以前最近解封装输入链表解出非完整帧的长度，为了支持多个PPP/IP拨号而增加的配置 */
        unsigned int  reserved            : 16; /* bit[16-31]: 保留 */
    } reg;
} SOC_HDLC_DEF_UNCOMPLETED_LEN_UNION;
#endif
#define SOC_HDLC_DEF_UNCOMPLETED_LEN_def_uncompleted_len_START  (0)
#define SOC_HDLC_DEF_UNCOMPLETED_LEN_def_uncompleted_len_END    (15)


/*****************************************************************************
 结构名    : SOC_HDLC_DEF_UNCOMPLETED_PRO_UNION
 结构说明  : DEF_UNCOMPLETED_PRO 寄存器结构定义。地址偏移量:0x0078，初值:0x00000000，宽度:32
 寄存器说明: 对应当前解封装输入链表，同一PPP/IP拨号的以前最近解封装输入链表解出非完整帧的协议，为了支持多个PPP/IP拨号而增加的配置（可能其中的0Byte、1Byte或2Byte有效）。
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  def_uncompleted_pro : 16; /* bit[0-15] : 对应当前解封装输入链表，同一PPP/IP拨号的以前最近解封装输入链表解出非完整帧的协议，为了支持多个PPP/IP拨号而增加的配置（可能其中的0Byte、1Byte或2Byte有效） */
        unsigned int  reserved            : 16; /* bit[16-31]: 保留 */
    } reg;
} SOC_HDLC_DEF_UNCOMPLETED_PRO_UNION;
#endif
#define SOC_HDLC_DEF_UNCOMPLETED_PRO_def_uncompleted_pro_START  (0)
#define SOC_HDLC_DEF_UNCOMPLETED_PRO_def_uncompleted_pro_END    (15)


/*****************************************************************************
 结构名    : SOC_HDLC_DEF_UNCOMPLETED_ADDR_UNION
 结构说明  : DEF_UNCOMPLETED_ADDR 寄存器结构定义。地址偏移量:0x007C，初值:0x00000000，宽度:32
 寄存器说明: 对应当前解封装输入链表，同一PPP/IP拨号的以前最近解封装输入链表解出非完整帧的外部存储起始地址，为了支持多个PPP/IP拨号而增加的配置（该地址可能是与原来上报不同的新地址）。
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  def_uncompleted_addr : 32; /* bit[0-31]: 对应当前解封装输入链表，同一PPP/IP拨号的以前最近解封装输入链表解出非完整帧的外部存储起始地址，为了支持多个PPP/IP拨号而增加的配置（该地址可能是与原来上报不同的新地址） */
    } reg;
} SOC_HDLC_DEF_UNCOMPLETED_ADDR_UNION;
#endif
#define SOC_HDLC_DEF_UNCOMPLETED_ADDR_def_uncompleted_addr_START  (0)
#define SOC_HDLC_DEF_UNCOMPLETED_ADDR_def_uncompleted_addr_END    (31)


/*****************************************************************************
 结构名    : SOC_HDLC_DEF_UNCOMPLET_ST_AGO_UNION
 结构说明  : DEF_UNCOMPLET_ST_AGO 寄存器结构定义。地址偏移量:0x0080，初值:0x00000000，宽度:32
 寄存器说明: 与当前解封装输入链表同一PPP/IP拨号的以前最近那套解封装输入链表处理完解出非完整帧时的数据状态机当前状态和CRC校验值。
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  def_data_st_curr_ago : 5;  /* bit[0-4]  : 与当前解封装输入链表同一PPP/IP拨号的以前最近那套解封装输入链表处理完后的数据状态机下一状态 */
        unsigned int  reserved             : 11; /* bit[5-15] : 保留 */
        unsigned int  crc16_result_ago     : 16; /* bit[16-31]: 与当前解封装输入链表同一PPP/IP拨号的以前最近那套解封装输入链表处理完解出非完整帧时的CRC校验值 */
    } reg;
} SOC_HDLC_DEF_UNCOMPLET_ST_AGO_UNION;
#endif
#define SOC_HDLC_DEF_UNCOMPLET_ST_AGO_def_data_st_curr_ago_START  (0)
#define SOC_HDLC_DEF_UNCOMPLET_ST_AGO_def_data_st_curr_ago_END    (4)
#define SOC_HDLC_DEF_UNCOMPLET_ST_AGO_crc16_result_ago_START      (16)
#define SOC_HDLC_DEF_UNCOMPLET_ST_AGO_crc16_result_ago_END        (31)


/*****************************************************************************
 结构名    : SOC_HDLC_DEF_GO_ON_UNION
 结构说明  : DEF_GO_ON 寄存器结构定义。地址偏移量:0x0084，初值:0x00000000，宽度:32
 寄存器说明: 暂停状态解除寄存器（解出一个合法LCP帧导致的解封装子模块暂停状态解除、解封装外部输出存储空间存满暂停解除、解封装外部正确帧信息上报空间存满暂停解除）。
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  def_lcp_goon        : 1;  /* bit[0]    : 解出一个合法LCP帧导致的硬件暂停状态清除。当解封装模块未处理完一组待解封装的数据（<=2KB(def_in_pkt_len_max)），解出一个合法LCP帧，则会暂停解帧，等待此软件向此寄存器写“1”，再继续处理剩余的数据。 */
        unsigned int  reserved_0          : 7;  /* bit[1-7]  : 保留 */
        unsigned int  def_outspc_ful_goon : 1;  /* bit[8]    : 外部解封装输出数据存储空间存满暂停状态清除 */
        unsigned int  reserved_1          : 7;  /* bit[9-15] : 保留 */
        unsigned int  def_rpt_ful_goon    : 1;  /* bit[16]   : 外部解封装有效帧信息上报空间存满暂停解除 */
        unsigned int  reserved_2          : 15; /* bit[17-31]: 保留 */
    } reg;
} SOC_HDLC_DEF_GO_ON_UNION;
#endif
#define SOC_HDLC_DEF_GO_ON_def_lcp_goon_START         (0)
#define SOC_HDLC_DEF_GO_ON_def_lcp_goon_END           (0)
#define SOC_HDLC_DEF_GO_ON_def_outspc_ful_goon_START  (8)
#define SOC_HDLC_DEF_GO_ON_def_outspc_ful_goon_END    (8)
#define SOC_HDLC_DEF_GO_ON_def_rpt_ful_goon_START     (16)
#define SOC_HDLC_DEF_GO_ON_def_rpt_ful_goon_END       (16)


/*****************************************************************************
 结构名    : SOC_HDLC_DEF_STATUS_UNION
 结构说明  : DEF_STATUS 寄存器结构定义。地址偏移量:0x0088，初值:0x00000000，宽度:32
 寄存器说明: 解封装子模块状态寄存器（增加def_uncompleted_now，用于指示当前链表是否有解出非完整帧，为了支持多个PPP/IP拨号而增加的配置：0，没有；1，有；增加def_out_spc_ful和def_rpt_ful；将def_blk_pro_stat改为def_all_pkt_pro_stat）。
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  def_all_pkt_pro_stat : 2;  /* bit[0-1]  : 一套输入链表处理状态：
                                                                l 00：未完成一套输入链表处理；
                                                                l 01：未完成一套输入链表处理，已解出LCP帧，硬件处于暂停状态；
                                                                l 10：完成一套输入链表处理，但无帧上报；
                                                                l 11: 完成一套输入链表处理，且有帧上报； */
        unsigned int  def_uncompleted_now  : 1;  /* bit[2]    : 用于指示当前链表是否有解出非完整帧，为了支持多个PPP/IP拨号而增加的配置：0，没有；1，有 */
        unsigned int  def_out_spc_ful      : 1;  /* bit[3]    : 解封装外部输出存储空间存满暂停指示 */
        unsigned int  def_rpt_ful          : 1;  /* bit[4]    : 解封装外部正确帧信息上报空间存满暂停指示 */
        unsigned int  def_error_index      : 1;  /* bit[5]    : 解封装发生错误指示 */
        unsigned int  reserved_0           : 2;  /* bit[6-7]  : 保留 */
        unsigned int  def_valid_num        : 16; /* bit[8-23] : 有帧上报时，有效帧数目；（不包括最后一个可能的非完整帧） */
        unsigned int  def_err_type         : 7;  /* bit[24-30]: 有帧上报时，错误帧类型，对应的bit位为1即表明发生该类型错误：
                                                                l bit 30：错误类型6，转义字符0x7D后紧接一个Flag域；
                                                                l bit 29：错误类型5，当AC域无压缩时，Address域值非0xFF；
                                                                l bit 28：错误类型4，当AC域无压缩时，Control域值非0x03；
                                                                l bit 27：错误类型3，当P域需剥离时，收到非法的Protocol域值；
                                                                l bit 26：错误类型2，解封装后帧字节数小于4bites；
                                                                l bit 25：错误类型1，解封装后帧字节数大于1502bytes（PPP帧的Information域不超过1500Bytes，加上协议域不超过1502Bytes）；
                                                                l bit 24：错误类型0， CRC校验错误。 */
        unsigned int  reserved_1           : 1;  /* bit[31]   : 保留 */
    } reg;
} SOC_HDLC_DEF_STATUS_UNION;
#endif
#define SOC_HDLC_DEF_STATUS_def_all_pkt_pro_stat_START  (0)
#define SOC_HDLC_DEF_STATUS_def_all_pkt_pro_stat_END    (1)
#define SOC_HDLC_DEF_STATUS_def_uncompleted_now_START   (2)
#define SOC_HDLC_DEF_STATUS_def_uncompleted_now_END     (2)
#define SOC_HDLC_DEF_STATUS_def_out_spc_ful_START       (3)
#define SOC_HDLC_DEF_STATUS_def_out_spc_ful_END         (3)
#define SOC_HDLC_DEF_STATUS_def_rpt_ful_START           (4)
#define SOC_HDLC_DEF_STATUS_def_rpt_ful_END             (4)
#define SOC_HDLC_DEF_STATUS_def_error_index_START       (5)
#define SOC_HDLC_DEF_STATUS_def_error_index_END         (5)
#define SOC_HDLC_DEF_STATUS_def_valid_num_START         (8)
#define SOC_HDLC_DEF_STATUS_def_valid_num_END           (23)
#define SOC_HDLC_DEF_STATUS_def_err_type_START          (24)
#define SOC_HDLC_DEF_STATUS_def_err_type_END            (30)


/*****************************************************************************
 结构名    : SOC_HDLC_DEF_UNCOMPLET_ST_NOW_UNION
 结构说明  : DEF_UNCOMPLET_ST_NOW 寄存器结构定义。地址偏移量:0x008C，初值:0x00000000，宽度:32
 寄存器说明: 当前解封装输入链表处理完解出非完整帧时的数据状态机当前状态和CRC校验值。
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  def_data_st_curr_now : 5;  /* bit[0-4]  : 当前解封装输入链表处理完解出非完整帧时的数据状态机当前状态 */
        unsigned int  reserved             : 11; /* bit[5-15] : 保留 */
        unsigned int  crc16_result_now     : 16; /* bit[16-31]: 当前解封装输入链表处理完解出非完整帧时的CRC校验值 */
    } reg;
} SOC_HDLC_DEF_UNCOMPLET_ST_NOW_UNION;
#endif
#define SOC_HDLC_DEF_UNCOMPLET_ST_NOW_def_data_st_curr_now_START  (0)
#define SOC_HDLC_DEF_UNCOMPLET_ST_NOW_def_data_st_curr_now_END    (4)
#define SOC_HDLC_DEF_UNCOMPLET_ST_NOW_crc16_result_now_START      (16)
#define SOC_HDLC_DEF_UNCOMPLET_ST_NOW_crc16_result_now_END        (31)


/*****************************************************************************
 结构名    : SOC_HDLC_DEF_IN_LLI_ADDR_UNION
 结构说明  : DEF_IN_LLI_ADDR 寄存器结构定义。地址偏移量:0x0090，初值:0x00000000，宽度:32
 寄存器说明: 解封装输入链表参数起始地址寄存器。
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  def_in_lli_addr : 32; /* bit[0-31]: 解封装输入链表参数起始地址寄存器 */
    } reg;
} SOC_HDLC_DEF_IN_LLI_ADDR_UNION;
#endif
#define SOC_HDLC_DEF_IN_LLI_ADDR_def_in_lli_addr_START  (0)
#define SOC_HDLC_DEF_IN_LLI_ADDR_def_in_lli_addr_END    (31)


/*****************************************************************************
 结构名    : SOC_HDLC_DEF_IN_PKT_ADDR_UNION
 结构说明  : DEF_IN_PKT_ADDR 寄存器结构定义。地址偏移量:0x0094，初值:0x00000000，宽度:32
 寄存器说明: 解封装输入链表节点所指待解封装输入数据包起始地址寄存器。
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  def_in_pkt_addr : 32; /* bit[0-31]: 解封装输入链表参数中待解封装输入数据包起始地址寄存器： */
    } reg;
} SOC_HDLC_DEF_IN_PKT_ADDR_UNION;
#endif
#define SOC_HDLC_DEF_IN_PKT_ADDR_def_in_pkt_addr_START  (0)
#define SOC_HDLC_DEF_IN_PKT_ADDR_def_in_pkt_addr_END    (31)


/*****************************************************************************
 结构名    : SOC_HDLC_DEF_IN_PKT_LEN_UNION
 结构说明  : DEF_IN_PKT_LEN 寄存器结构定义。地址偏移量:0x0098，初值:0x00000000，宽度:32
 寄存器说明: 解封装输入链表节点所指待解封装输入数据包长度寄存器。
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  def_in_pkt_len : 16; /* bit[0-15] : 解封装输入链表参数中待解封装输入数据包长度寄存器： */
        unsigned int  reserved       : 16; /* bit[16-31]: 保留 */
    } reg;
} SOC_HDLC_DEF_IN_PKT_LEN_UNION;
#endif
#define SOC_HDLC_DEF_IN_PKT_LEN_def_in_pkt_len_START  (0)
#define SOC_HDLC_DEF_IN_PKT_LEN_def_in_pkt_len_END    (15)


/*****************************************************************************
 结构名    : SOC_HDLC_DEF_IN_PKT_LEN_MAX_UNION
 结构说明  : DEF_IN_PKT_LEN_MAX 寄存器结构定义。地址偏移量:0x009C，初值:0x00000000，宽度:32
 寄存器说明: 一个解封装输入链表节点所指待解封装输入数据包最大允许长度寄存器。
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  def_in_pkt_len_max : 16; /* bit[0-15] : 待解封装输入数据包最大允许长度寄存器：
                                                              由软件配置 */
        unsigned int  reserved           : 16; /* bit[16-31]: 保留 */
    } reg;
} SOC_HDLC_DEF_IN_PKT_LEN_MAX_UNION;
#endif
#define SOC_HDLC_DEF_IN_PKT_LEN_MAX_def_in_pkt_len_max_START  (0)
#define SOC_HDLC_DEF_IN_PKT_LEN_MAX_def_in_pkt_len_max_END    (15)


/*****************************************************************************
 结构名    : SOC_HDLC_DEF_OUT_SPC_ADDR_UNION
 结构说明  : DEF_OUT_SPC_ADDR 寄存器结构定义。地址偏移量:0x00A0，初值:0x00000000，宽度:32
 寄存器说明: 解封装输出数据存储空间起始地址寄存器
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  def_out_spc_addr : 32; /* bit[0-31]: 解封装输出数据存储空间起始地址寄存器：
                                                           由软件配置 */
    } reg;
} SOC_HDLC_DEF_OUT_SPC_ADDR_UNION;
#endif
#define SOC_HDLC_DEF_OUT_SPC_ADDR_def_out_spc_addr_START  (0)
#define SOC_HDLC_DEF_OUT_SPC_ADDR_def_out_spc_addr_END    (31)


/*****************************************************************************
 结构名    : SOC_HDLC_DEF_OUT_SPC_DEP_UNION
 结构说明  : DEF_OUT_SPC_DEP 寄存器结构定义。地址偏移量:0x00A4，初值:0x00000000，宽度:32
 寄存器说明: 解封装输出数据存储空间深度寄存器。
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  def_out_spc_dep : 16; /* bit[0-15] : 解封装输出数据存储空间深度寄存器：
                                                           由软件配置 */
        unsigned int  reserved        : 16; /* bit[16-31]: 保留 */
    } reg;
} SOC_HDLC_DEF_OUT_SPC_DEP_UNION;
#endif
#define SOC_HDLC_DEF_OUT_SPC_DEP_def_out_spc_dep_START  (0)
#define SOC_HDLC_DEF_OUT_SPC_DEP_def_out_spc_dep_END    (15)


/*****************************************************************************
 结构名    : SOC_HDLC_DEF_RPT_ADDR_UNION
 结构说明  : DEF_RPT_ADDR 寄存器结构定义。地址偏移量:0x00A8，初值:0x00000000，宽度:32
 寄存器说明: 解封装输出正确帧上报信息存储空间起始地址。
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  def_rpt_addr : 32; /* bit[0-31]: 解封装输出正确帧上报信息存储空间起始地址：
                                                       由软件配置 */
    } reg;
} SOC_HDLC_DEF_RPT_ADDR_UNION;
#endif
#define SOC_HDLC_DEF_RPT_ADDR_def_rpt_addr_START  (0)
#define SOC_HDLC_DEF_RPT_ADDR_def_rpt_addr_END    (31)


/*****************************************************************************
 结构名    : SOC_HDLC_DEF_RPT_DEP_UNION
 结构说明  : DEF_RPT_DEP 寄存器结构定义。地址偏移量:0x00AC，初值:0x00000000，宽度:32
 寄存器说明: 解封装输出正确帧上报信息存储空间深度。
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  def_out_result_dep : 16; /* bit[0-15] : 解封装输出正确帧上报信息存储空间深度：
                                                              由软件配置 */
        unsigned int  reserved           : 16; /* bit[16-31]: 保留 */
    } reg;
} SOC_HDLC_DEF_RPT_DEP_UNION;
#endif
#define SOC_HDLC_DEF_RPT_DEP_def_out_result_dep_START  (0)
#define SOC_HDLC_DEF_RPT_DEP_def_out_result_dep_END    (15)


/*****************************************************************************
 结构名    : SOC_HDLC_DEF_ERR_INFO_0_UNION
 结构说明  : DEF_ERR_INFO_0 寄存器结构定义。地址偏移量:0x00B0，初值:0x00000000，宽度:32
 寄存器说明: 解封装错误帧信息寄存器（组0）。
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  def_err0_num : 16; /* bit[0-15] : 当有帧上报时，类型0的错误帧数 */
        unsigned int  def_err1_num : 16; /* bit[16-31]: 当有帧上报时，类型1的错误帧数 */
    } reg;
} SOC_HDLC_DEF_ERR_INFO_0_UNION;
#endif
#define SOC_HDLC_DEF_ERR_INFO_0_def_err0_num_START  (0)
#define SOC_HDLC_DEF_ERR_INFO_0_def_err0_num_END    (15)
#define SOC_HDLC_DEF_ERR_INFO_0_def_err1_num_START  (16)
#define SOC_HDLC_DEF_ERR_INFO_0_def_err1_num_END    (31)


/*****************************************************************************
 结构名    : SOC_HDLC_DEF_ERR_INFO_1_UNION
 结构说明  : DEF_ERR_INFO_1 寄存器结构定义。地址偏移量:0x00B4，初值:0x00000000，宽度:32
 寄存器说明: 解封装错误帧信息寄存器（组1）。
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  def_err2_num : 16; /* bit[0-15] : 当有帧上报时，类型2的错误帧数 */
        unsigned int  def_err3_num : 16; /* bit[16-31]: 当有帧上报时，类型3的错误帧数 */
    } reg;
} SOC_HDLC_DEF_ERR_INFO_1_UNION;
#endif
#define SOC_HDLC_DEF_ERR_INFO_1_def_err2_num_START  (0)
#define SOC_HDLC_DEF_ERR_INFO_1_def_err2_num_END    (15)
#define SOC_HDLC_DEF_ERR_INFO_1_def_err3_num_START  (16)
#define SOC_HDLC_DEF_ERR_INFO_1_def_err3_num_END    (31)


/*****************************************************************************
 结构名    : SOC_HDLC_DEF_ERR_INFO_2_UNION
 结构说明  : DEF_ERR_INFO_2 寄存器结构定义。地址偏移量:0x00B8，初值:0x00000000，宽度:32
 寄存器说明: 解封装错误帧信息寄存器（组2）。
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  def_err4_num : 16; /* bit[0-15] : 当有帧上报时，类型4的错误帧数 */
        unsigned int  def_err5_num : 16; /* bit[16-31]: 当有帧上报时，类型5的错误帧数 */
    } reg;
} SOC_HDLC_DEF_ERR_INFO_2_UNION;
#endif
#define SOC_HDLC_DEF_ERR_INFO_2_def_err4_num_START  (0)
#define SOC_HDLC_DEF_ERR_INFO_2_def_err4_num_END    (15)
#define SOC_HDLC_DEF_ERR_INFO_2_def_err5_num_START  (16)
#define SOC_HDLC_DEF_ERR_INFO_2_def_err5_num_END    (31)


/*****************************************************************************
 结构名    : SOC_HDLC_DEF_ERR_INFO_3_UNION
 结构说明  : DEF_ERR_INFO_3 寄存器结构定义。地址偏移量:0x00BC，初值:0x00000000，宽度:32
 寄存器说明: 解封装错误帧信息寄存器（组3）。
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  def_err6_num : 16; /* bit[0-15] : 当有帧上报时，类型6的错误帧数 */
        unsigned int  reserved     : 16; /* bit[16-31]: 保留 */
    } reg;
} SOC_HDLC_DEF_ERR_INFO_3_UNION;
#endif
#define SOC_HDLC_DEF_ERR_INFO_3_def_err6_num_START  (0)
#define SOC_HDLC_DEF_ERR_INFO_3_def_err6_num_END    (15)


/*****************************************************************************
 结构名    : SOC_HDLC_DEF_INFO_FRL_CNT_AGO_UNION
 结构说明  : DEF_INFO_FRL_CNT_AGO 寄存器结构定义。地址偏移量:0x00C0，初值:0x00000000，宽度:32
 寄存器说明: 与当前解封装输入链表同一PPP/IP拨号的以前最近那套解封装输入链表处理完解出非完整帧时的信息长度和帧长度。
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  def_info_cnt_ago   : 11; /* bit[0-10] : 与当前解封装输入链表同一PPP/IP拨号的以前最近那套解封装输入链表处理完解出非完整帧时的信息长度 */
        unsigned int  reserved_0         : 5;  /* bit[11-15]: 保留 */
        unsigned int  def_framel_cnt_ago : 11; /* bit[16-26]: 与当前解封装输入链表同一PPP/IP拨号的以前最近那套解封装输入链表处理完解出非完整帧时的帧长度 */
        unsigned int  reserved_1         : 5;  /* bit[27-31]: 保留 */
    } reg;
} SOC_HDLC_DEF_INFO_FRL_CNT_AGO_UNION;
#endif
#define SOC_HDLC_DEF_INFO_FRL_CNT_AGO_def_info_cnt_ago_START    (0)
#define SOC_HDLC_DEF_INFO_FRL_CNT_AGO_def_info_cnt_ago_END      (10)
#define SOC_HDLC_DEF_INFO_FRL_CNT_AGO_def_framel_cnt_ago_START  (16)
#define SOC_HDLC_DEF_INFO_FRL_CNT_AGO_def_framel_cnt_ago_END    (26)


/*****************************************************************************
 结构名    : SOC_HDLC_DEF_INFO_FRL_CNT_NOW_UNION
 结构说明  : DEF_INFO_FRL_CNT_NOW 寄存器结构定义。地址偏移量:0x00C4，初值:0x00000000，宽度:32
 寄存器说明: 当前解封装输入链表处理完解出非完整帧时的信息长度和帧长度。
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  def_info_cnt_now   : 11; /* bit[0-10] : 当前解封装输入链表处理完解出非完整帧时的信息长度 */
        unsigned int  reserved_0         : 5;  /* bit[11-15]: 保留 */
        unsigned int  def_framel_cnt_now : 11; /* bit[16-26]: 当前解封装输入链表处理完解出非完整帧时的帧长度 */
        unsigned int  reserved_1         : 5;  /* bit[27-31]: 保留 */
    } reg;
} SOC_HDLC_DEF_INFO_FRL_CNT_NOW_UNION;
#endif
#define SOC_HDLC_DEF_INFO_FRL_CNT_NOW_def_info_cnt_now_START    (0)
#define SOC_HDLC_DEF_INFO_FRL_CNT_NOW_def_info_cnt_now_END      (10)
#define SOC_HDLC_DEF_INFO_FRL_CNT_NOW_def_framel_cnt_now_START  (16)
#define SOC_HDLC_DEF_INFO_FRL_CNT_NOW_def_framel_cnt_now_END    (26)

/* 以下为转定义寄存器，非自动生成 */

#define    SOC_HDLC_REG_ACTUAL_ADDR(base, offset) ((base)+(offset))

#define    FEATURE_HDLC_MASTER

#ifdef FEATURE_HDLC_MASTER
/*==================================================================================*/
/*===============PPP(HDLC)硬件加速功能相关的寄存器以及内存地址宏定义==============*/
/* 通用寄存器 */
#define     SOC_ARM_HDLC_STATE_SW_RST_ADDR(BaseAddr)                    SOC_HDLC_STATE_SW_RST_ADDR(BaseAddr)        /* 状态软复位寄存器地址 */
#define     SOC_ARM_HDLC_PRIROR_TIMEOUT_CTRL_ADDR(BaseAddr)             SOC_HDLC_PRIOR_TIMEOUT_CTRL_ADDR(BaseAddr)  /* 封装解封装优先级配置地址 */
#define     SOC_ARM_HDLC_RD_ERR_CURR_ADDR(BaseAddr)                     SOC_HDLC_RD_ERR_CURR_ADDR_ADDR(BaseAddr)    /* AXI读操作错误时被读地址 */
#define     SOC_ARM_HDLC_WR_ERR_CURR_ADDR(BaseAddr)                     SOC_HDLC_WR_ERR_CURR_ADDR_ADDR(BaseAddr)    /* AXI写操作错误时被写地址 */

/* 封装子模块寄存器 */
#define     SOC_ARM_HDLC_FRM_EN_ADDR(BaseAddr)                          SOC_HDLC_FRM_EN_ADDR(BaseAddr)              /* 封装使能寄存器地址 */
#define     SOC_ARM_HDLC_FRM_RAW_INT_ADDR(BaseAddr)                     SOC_HDLC_FRM_RAW_INT_ADDR(BaseAddr)         /* HDLC模块中断使能寄存器地址 */
#define     SOC_ARM_HDLC_FRM_INT_STATUS_ADDR(BaseAddr)                  SOC_HDLC_FRM_INT_STATUS_ADDR(BaseAddr)      /* 封装状态寄存器地址 */
#define     SOC_ARM_HDLC_FRM_INT_CLR_ADDR(BaseAddr)                     SOC_HDLC_FRM_INT_CLR_ADDR(BaseAddr)         /* 封装状态清除寄存器地址 */
#define     SOC_ARM_HDLC_FRM_CFG_ADDR(BaseAddr)                         SOC_HDLC_FRM_CFG_ADDR(BaseAddr)             /* 封装模块配置寄存器地址 */
#define     SOC_ARM_HDLC_FRM_ACCM_ADDR(BaseAddr)                        SOC_HDLC_FRM_ACCM_ADDR(BaseAddr)            /* 封装模块转义使能寄存器地址 */
#define     SOC_ARM_HDLC_FRM_STATUS_ADDR(BaseAddr)                      SOC_HDLC_FRM_STATUS_ADDR(BaseAddr)          /* 封装结果状态寄存器地址 */
#define     SOC_ARM_HDLC_FRM_IN_LLI_ADDR(BaseAddr)                      SOC_HDLC_FRM_IN_LLI_ADDR_ADDR(BaseAddr)     /* 封装输入主链表起始地址寄存器地址 */
#define     SOC_ARM_HDLC_FRM_IN_SUBLLI_ADDR(BaseAddr)                   SOC_HDLC_FRM_IN_SUBLLI_ADDR_ADDR(BaseAddr)  /* 待封装输入数据包或者输入副链表起始地址寄存器的地址 */
#define     SOC_ARM_HDLC_FRM_IN_PKT_LEN_ADDR(BaseAddr)                  SOC_HDLC_FRM_IN_PKT_LEN_ADDR(BaseAddr)      /* 封装输入主链表节点所指待封装输入数据包长度寄存器地址 */
#define     SOC_ARM_HDLC_FRM_IN_BLK_ADDR(BaseAddr)                      SOC_HDLC_FRM_IN_BLK_ADDR_ADDR(BaseAddr)     /* 封装输入副链表节点所指待封装输入数据分组起始地址寄存器地址 */
#define     SOC_ARM_HDLC_FRM_IN_BLK_LEN_ADDR(BaseAddr)                  SOC_HDLC_FRM_IN_BLK_LEN_ADDR(BaseAddr)      /* 封装输入副链表节点所指待封装输入数据分组长度寄存器地址 */
#define     SOC_ARM_HDLC_FRM_OUT_LLI_ADDR(BaseAddr)                     SOC_HDLC_FRM_OUT_LLI_ADDR_ADDR(BaseAddr)    /* 封装输出链表起始地址寄存器地址 */
#define     SOC_ARM_HDLC_FRM_OUT_SPACE_ADDR(BaseAddr)                   SOC_HDLC_FRM_OUT_SPC_ADDR_ADDR(BaseAddr)    /* 封装输出链表节点所指存储空间起始地址寄存器地址 */
#define     SOC_ARM_HDLC_FRM_OUT_SPACE_DEP_ADDR(BaseAddr)               SOC_HDLC_FRM_OUT_SPC_DEP_ADDR(BaseAddr)     /* 封装输出链表节点所指存储空间深度寄存器地址 */
#define     SOC_ARM_HDLC_FRM_RPT_ADDR(BaseAddr)                         SOC_HDLC_FRM_RPT_ADDR_ADDR(BaseAddr)        /* 封装各输出正确帧长度存储空间起始地址寄存器地址 */
#define     SOC_ARM_HDLC_FRM_RPT_DEP_ADDR(BaseAddr)                     SOC_HDLC_FRM_RPT_DEP_ADDR(BaseAddr)         /* 封装各输出正确帧长度存储空间深度寄存器地址 */

/* 解封装子模块寄存器 */
#define     SOC_ARM_HDLC_DEF_EN_ADDR(BaseAddr)                          SOC_HDLC_DEF_EN_ADDR(BaseAddr)              /* 解封装使能寄存器地址 */
#define     SOC_ARM_HDLC_DEF_RAW_INT_ADDR(BaseAddr)                     SOC_HDLC_DEF_RAW_INT_ADDR(BaseAddr)         /* HDLC模块中断使能寄存器地址 */
#define     SOC_ARM_HDLC_DEF_INT_STATUS_ADDR(BaseAddr)                  SOC_HDLC_DEF_INT_STATUS_ADDR(BaseAddr)      /* 解封装状态寄存器地址 */
#define     SOC_ARM_HDLC_DEF_INT_CLR_ADDR(BaseAddr)                     SOC_HDLC_DEF_INT_CLR_ADDR(BaseAddr)         /* 解封装状态清除寄存器地址 */
#define     SOC_ARM_HDLC_DEF_CFG_ADDR(BaseAddr)                         SOC_HDLC_DEF_CFG_ADDR(BaseAddr)             /* 解封装模块配置寄存器地址 */
#define     SOC_ARM_HDLC_DEF_UNCOMPLETED_LEN_ADDR(BaseAddr)             SOC_HDLC_DEF_UNCOMPLETED_LEN_ADDR(BaseAddr) /* 最近解封装输入链表解出非完整帧的长度寄存器地址 */
#define     SOC_ARM_HDLC_DEF_UNCOMPLETED_PRO_ADDR(BaseAddr)             SOC_HDLC_DEF_UNCOMPLETED_PRO_ADDR(BaseAddr) /* 最近解封装输入链表解出非完整帧的协议寄存器地址 */
#define     SOC_ARM_HDLC_DEF_UNCOMPLETED_ADDR(BaseAddr)                 SOC_HDLC_DEF_UNCOMPLETED_ADDR_ADDR(BaseAddr)/* 最近解封装输入链表解出非完整帧的外部存储起始地址的寄存器地址 */
#define     SOC_ARM_HDLC_DEF_UNCOMPLETED_ST_AGO_ADDR(BaseAddr)          SOC_HDLC_DEF_UNCOMPLET_ST_AGO_ADDR(BaseAddr)/* 最近那套解封装输入链表处理完解出非完整帧时的CRC校验值以及数据状态机当前状态值的寄存器地址 */
#define     SOC_ARM_HDLC_DEF_GO_ON_ADDR(BaseAddr)                       SOC_HDLC_DEF_GO_ON_ADDR(BaseAddr)           /* 继续解封装指示寄存器地址 */
#define     SOC_ARM_HDLC_DEF_STATUS_ADDR(BaseAddr)                      SOC_HDLC_DEF_STATUS_ADDR(BaseAddr)          /* 解封装结果状态寄存器地址 */
#define     SOC_ARM_HDLC_DEF_UNCOMPLETED_ST_NOW_ADDR(BaseAddr)          SOC_HDLC_DEF_UNCOMPLET_ST_NOW_ADDR(BaseAddr)/* 当前解封装输入链表处理完解出非完整帧时的CRC校验值以及数据状态机当前状态值的寄存器地址 */
#define     SOC_ARM_HDLC_DEF_IN_LLI_ADDR(BaseAddr)                      SOC_HDLC_DEF_IN_LLI_ADDR_ADDR(BaseAddr)     /* 解封装输入链表参数起始地址寄存器地址 */
#define     SOC_ARM_HDLC_DEF_IN_PKT_ADDR(BaseAddr)                      SOC_HDLC_DEF_IN_PKT_ADDR_ADDR(BaseAddr)     /* 解封装输入链表参数中待解封装输入数据包起始地址寄存器地址 */
#define     SOC_ARM_HDLC_DEF_IN_PKT_LEN_ADDR(BaseAddr)                  SOC_HDLC_DEF_IN_PKT_LEN_ADDR(BaseAddr)      /* 解封装输入链表参数中待解封装输入数据包长度寄存器地址 */
#define     SOC_ARM_HDLC_DEF_IN_PKT_LEN_MAX_ADDR(BaseAddr)              SOC_HDLC_DEF_IN_PKT_LEN_MAX_ADDR(BaseAddr)  /* 待解封装输入数据包最大允许长度寄存器地址 */
#define     SOC_ARM_HDLC_DEF_OUT_SPC_ADDR(BaseAddr)                     SOC_HDLC_DEF_OUT_SPC_ADDR_ADDR(BaseAddr)    /* 解封装输出数据存储空间起始地址寄存器地址 */
#define     SOC_ARM_HDLC_DEF_OUT_SPACE_DEP_ADDR(BaseAddr)               SOC_HDLC_DEF_OUT_SPC_DEP_ADDR(BaseAddr)     /* 解封装输出数据存储空间深度寄存器地址 */
#define     SOC_ARM_HDLC_DEF_RPT_ADDR(BaseAddr)                         SOC_HDLC_DEF_RPT_ADDR_ADDR(BaseAddr)        /* 解封装输出正确帧上报信息存储空间起始地址寄存器地址 */
#define     SOC_ARM_HDLC_DEF_RPT_DEP_ADDR(BaseAddr)                     SOC_HDLC_DEF_RPT_DEP_ADDR(BaseAddr)         /* 解封装输出正确帧上报信息存储空间深度寄存器地址 */
#define     SOC_ARM_HDLC_DEF_ERR_INFO_0_ADDR(BaseAddr)                  SOC_HDLC_DEF_ERR_INFO_0_ADDR(BaseAddr)      /* 解封装错误帧统计寄存器第0组 */
#define     SOC_ARM_HDLC_DEF_ERR_INFO_1_ADDR(BaseAddr)                  SOC_HDLC_DEF_ERR_INFO_1_ADDR(BaseAddr)      /* 解封装错误帧统计寄存器第1组 */
#define     SOC_ARM_HDLC_DEF_ERR_INFO_2_ADDR(BaseAddr)                  SOC_HDLC_DEF_ERR_INFO_2_ADDR(BaseAddr)      /* 解封装错误帧统计寄存器第2组 */
#define     SOC_ARM_HDLC_DEF_ERR_INFO_3_ADDR(BaseAddr)                  SOC_HDLC_DEF_ERR_INFO_3_ADDR(BaseAddr)      /* 解封装错误帧统计寄存器第3组 */
#define     SOC_ARM_HDLC_DEF_INFO_FRL_CNT_AGO_ADDR(BaseAddr)            SOC_HDLC_DEF_INFO_FRL_CNT_AGO_ADDR(BaseAddr)/* 最近那套解封装输入链表处理完解出非完整帧时的帧长度以及信息长度寄存器地址 */
#define     SOC_ARM_HDLC_DEF_INFO_FRL_CNT_NOW_ADDR(BaseAddr)            SOC_HDLC_DEF_INFO_FRL_CNT_NOW_ADDR(BaseAddr)/* 当前解封装输入链表处理完解出非完整帧时的帧长度以及信息长度寄存器地址 */
#else

/*==================================================================================*/
/*===============PPP(HDLC)硬件加速功能相关的寄存器以及内存地址宏定义==============*/

/*HDLC 上下电宏定义*/
#define    SOC_ARM_HDLC_ENABLE_REG_ADDR                    SOC_HDLC_REG_ACTUAL_ADDR(SOC_ARM_SYSTEM_CONTROL_BASE_ADDR, 0x0038) /*HDLC上电寄存器地址*/
#define    SOC_ARM_HDLC_DISABLE_REG_ADDR                   SOC_HDLC_REG_ACTUAL_ADDR(SOC_ARM_SYSTEM_CONTROL_BASE_ADDR, 0x003C) /*HDLC下电寄存器地址*/
#define    SOC_ARM_HDLC_REG_BIT                            (9) /*HDLC上下电寄存器控制位*/

/*
FPGA资源有限，HDLC无单独时钟，ASIC版本需要修改PPP_HDLC_BY_HARDWARE使用
#define    SOC_AMR_HDLC_ENABLE()                           {*(volatile VOS_UINT32 *)SOC_ARM_HDLC_ENABLE_REG_ADDR    |= (1 << SOC_ARM_HDLC_REG_BIT);}
#define    SOC_AMR_HDLC_DISABLE()                          {*(volatile VOS_UINT32 *)SOC_ARM_HDLC_DISABLE_REG_ADDR   |= (1 << SOC_ARM_HDLC_REG_BIT);}

#else
*/
#define    SOC_AMR_HDLC_ENABLE()
#define    SOC_AMR_HDLC_DISABLE()

/* definition of input&output buffer address */
#define     SOC_ARM_HDLC_FRAMER_IN_DATA_ADDR(BaseAddr)                SOC_HDLC_REG_ACTUAL_ADDR(BaseAddr,0x1000)  /* 封装模块的数据写入地址: 每次写入不超过256字节数据的起始地址 */
#define     SOC_ARM_HDLC_FRAMER_OUT_DATA_ADDR(BaseAddr)               SOC_HDLC_REG_ACTUAL_ADDR(BaseAddr,0x2000)  /* 封装模块的数据读出地址: 封装完毕时数据存放的起始地址 */
#define     SOC_ARM_HDLC_DEFRAMER_IN_DATA_ADDR(BaseAddr)              SOC_HDLC_REG_ACTUAL_ADDR(BaseAddr,0x3000)  /* 解封装模块的数据写入地址: 每次写入不超过256字节数据的起始地址 */
#define     SOC_ARM_HDLC_DEFRAMER_OUT_DATA_BASE_ADDR(BaseAddr)        SOC_HDLC_REG_ACTUAL_ADDR(BaseAddr,0x4000)  /* 解封装模块的数据存放的基地址: 解封装所解出帧的数据存放数据的基地址 */
#define     SOC_ARM_HDLC_DEFRAMER_OUT_LIST_ADDR(BaseAddr)             SOC_HDLC_REG_ACTUAL_ADDR(BaseAddr,0x6000)  /* 解封装模块上报列表地址: 解封装所解出所有帧信息的起始地址 */
/* definition of registers' address */
#define     SOC_ARM_HDLC_INTERRUPT_ENABLE_ADDR(BaseAddr)              SOC_HDLC_REG_ACTUAL_ADDR(BaseAddr,0x0004)   /* HDLC模块中断使能寄存器地址: 相对偏移地址量0x04 */
#define     SOC_ARM_HDLC_INTERRUPT_FRAMER_RAW_INT_ADDR(BaseAddr)      SOC_HDLC_REG_ACTUAL_ADDR(BaseAddr,0x0008)   /* HDLC模块中断使能寄存器地址: 相对偏移地址量0x08 */
#define     SOC_ARM_HDLC_INTERRUPT_INT_STATUS_ADDR(BaseAddr)          SOC_HDLC_REG_ACTUAL_ADDR(BaseAddr,0x000C)   /* HDLC模块中断使能寄存器地址: 相对偏移地址量0x0C */
#define     SOC_ARM_HDLC_FRAMER_INTERRUPT_CLEAR_ADDR(BaseAddr)        SOC_HDLC_REG_ACTUAL_ADDR(BaseAddr,0x0010)   /* HDLC模块中断清除寄存器地址: 相对偏移地址量0x10 */
#define     SOC_ARM_HDLC_FRAMER_CFG_ADDR(BaseAddr)                    SOC_HDLC_REG_ACTUAL_ADDR(BaseAddr,0x0020)   /* 封装模块配置寄存器地址: 相对偏移地址量0x20 */
#define     SOC_ARM_HDLC_FRAMER_ACCM_ADDR(BaseAddr)                   SOC_HDLC_REG_ACTUAL_ADDR(BaseAddr,0x0024)   /* 封装模块转义使能寄存器地址: 相对偏移地址量0x24 */
#define     SOC_ARM_HDLC_FRAMER_CTRL_ADDR(BaseAddr)                   SOC_HDLC_REG_ACTUAL_ADDR(BaseAddr,0x0028)   /* 封装模块控制寄存器地址: 相对偏移地址量0x28 */
#define     SOC_ARM_HDLC_FRAMER_STATUS_ADDR(BaseAddr)                 SOC_HDLC_REG_ACTUAL_ADDR(BaseAddr,0x002C)   /* 封装模块状态寄存器地址: 相对偏移地址量0x2C */
#define     SOC_ARM_HDLC_DEFRAMER_CFG_ADDR(BaseAddr)                  SOC_HDLC_REG_ACTUAL_ADDR(BaseAddr,0x0040)   /* hdlc_def_cfg (0x40) */
#define     SOC_ARM_HDLC_DEFRAMER_CTRL_ADDR(BaseAddr)                 SOC_HDLC_REG_ACTUAL_ADDR(BaseAddr,0x0044)   /* hdlc_def_ctrl (0x44) */
#define     SOC_ARM_HDLC_DEFRAMER_GO_ON_ADDR(BaseAddr)                SOC_HDLC_REG_ACTUAL_ADDR(BaseAddr,0x0048)   /* hdlc_def_go_on(0x48) */
#define     SOC_ARM_HDLC_DEFRAMER_STATUS_ADDR(BaseAddr)               SOC_HDLC_REG_ACTUAL_ADDR(BaseAddr,0x004C)   /* 解封装状态寄存器地址: 相对偏移地址量0x4C */
#define     SOC_ARM_HDLC_DEFRAMER_ERROR_INFO_0_ADDR(BaseAddr)         SOC_HDLC_REG_ACTUAL_ADDR(BaseAddr,0x0050)   /* 解封装错误帧统计寄存器第0组 */
#define     SOC_ARM_HDLC_DEFRAMER_ERROR_INFO_1_ADDR(BaseAddr)         SOC_HDLC_REG_ACTUAL_ADDR(BaseAddr,0x0054)   /* 解封装错误帧统计寄存器第1组 */
#define     SOC_ARM_HDLC_DEFRAMER_ERROR_INFO_2_ADDR(BaseAddr)         SOC_HDLC_REG_ACTUAL_ADDR(BaseAddr,0x0058)   /* 解封装错误帧统计寄存器第2组 */
#define     SOC_ARM_HDLC_DEFRAMER_ERROR_INFO_3_ADDR(BaseAddr)         SOC_HDLC_REG_ACTUAL_ADDR(BaseAddr,0x005C)   /* 解封装错误帧统计寄存器第3组 */
#endif




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

#endif /* end of soc_hdlc_interface.h */
