/******************************************************************************

                 版权所有 (C), 2001-2015, 华为技术有限公司

 ******************************************************************************
  文 件 名   : bbp_abb_cfg_interface.h
  版 本 号   : 初稿
  作    者   : Excel2Code
  生成日期   : 2015-05-14 16:10:44
  最近修改   :
  功能描述   : 接口头文件
  函数列表   :
  修改历史   :
  1.日    期   : 2015年5月14日
    作    者   : l00165286
    修改内容   : 从《K3V5 寄存器手册_ABB_CFG.xml》自动生成

******************************************************************************/

/*****************************************************************************
  1 其他头文件包含
*****************************************************************************/

#ifndef __BBP_ABB_CFG_INTERFACE_H__
#define __BBP_ABB_CFG_INTERFACE_H__

#ifdef __cplusplus
    #if __cplusplus
        extern "C" {
    #endif
#endif



/*****************************************************************************
  2 宏定义
*****************************************************************************/

/***======================================================================***
                     (1/1) register_define_abb_cfg
 ***======================================================================***/
/* 寄存器说明：软复位
 bit[31:1]   保留
 bit[0]      复位寄存器：
             1'b0：解除复位
             1'b1:进入复位
             配置时刻：任意
             生效时刻：立即
   UNION结构:  ABB_CFG_SOFT_RST_UNION */
#define ABB_CFG_SOFT_RST_ADDR                         (SOC_BBP_ABB_CFG_BASE_ADDR + 0x0)

/* 寄存器说明：abb配置模式
 bit[31:2]   保留
 bit[1]      abb配置模式：
             1'b0:软件间接配置abb寄存器
             1'b1:软件直接配置abb寄存器
 bit[0]      仲裁使能：
             1'b0:屏蔽仲裁功能
             1'b1:使能仲裁功能
   UNION结构:  ABB_CFG_CFG_CTRL0_UNION */
#define ABB_CFG_CFG_CTRL0_ADDR                        (SOC_BBP_ABB_CFG_BASE_ADDR + 0x4)

/* 寄存器说明：abb配置模式
 bit[31:1]   保留
 bit[0]      软件读写标志：
             1'b0:写
             1'b1:读
   UNION结构:  ABB_CFG_CFG_CTRL1_UNION */
#define ABB_CFG_CFG_CTRL1_ADDR                        (SOC_BBP_ABB_CFG_BASE_ADDR + 0x8)

/* 寄存器说明：abb配置模式
 bit[31:6]   保留
 bit[5:3]    接收fifo水线，当接收fifo当前存储深度大于该水线时，产生接收fifo中断。
             3'b000:1
             3'b001:2
             3'b010:3
             3'b011:4
             3'b100:5
             3'b101:6
             3'b110:7
             3'b111:8
 bit[2:0]    发送fifo水线，当发送fifo当前存储深度小于该水线时，产生发送fifo中断。
             3'b000:1
             3'b001:2
             3'b010:3
             3'b011:4
             3'b100:5
             3'b101:6
             3'b110:7
             3'b111:8
   UNION结构:  ABB_CFG_CFG_CTRL2_UNION */
#define ABB_CFG_CFG_CTRL2_ADDR                        (SOC_BBP_ABB_CFG_BASE_ADDR + 0xC)

/* 寄存器说明：非定时模式下软件配置ABB的数据
   详      述：非定时模式下软件配置ABB的数据，
            写格式：
            bit[12:0]：写地址
            bit[20:13]:写数据
            其余保留
            读格式：
            bit[12:0]：读地址
            bit[20:13]:回读数据
            其余保留
   UNION结构 ：无 */
#define ABB_CFG_CFG_DATA_ADDR                         (SOC_BBP_ABB_CFG_BASE_ADDR + 0x10)

/* 寄存器说明：中断屏蔽寄存器
 bit[31:4]   保留
 bit[3]      发送fifo中断屏蔽位
             1'b0:屏蔽
             1'b1:不屏蔽
 bit[2]      接收fifo中断屏蔽位
             1'b0:屏蔽
             1'b1:不屏蔽
 bit[1]      保留
 bit[0]      接收fifo溢出中断屏蔽位
             1'b0:屏蔽
             1'b1:不屏蔽
   UNION结构:  ABB_CFG_CFG_INT_MASK_UNION */
#define ABB_CFG_CFG_INT_MASK_ADDR                     (SOC_BBP_ABB_CFG_BASE_ADDR + 0x30)

/* 寄存器说明：中断清除寄存器
 bit[31:4]   保留
 bit[3]      发送fifo中断清除位
             1'b0:不清除
             1'b1:清除
 bit[2]      接收fifo中断清除位
             1'b0:不清除
             1'b1:清除
 bit[1]      保留
 bit[0]      接收fifo溢出中断清除位
             1'b0:不清除
             1'b1:清除
   UNION结构:  ABB_CFG_CFG_INT_CLR_UNION */
#define ABB_CFG_CFG_INT_CLR_ADDR                      (SOC_BBP_ABB_CFG_BASE_ADDR + 0x34)

/* 寄存器说明：中断告警寄存器
 bit[31:4]   保留
 bit[3]      发送fifo中断告警寄存器，当新的中断来临时，老的中断还没有清除，产生此告警信号，写1清除。
 bit[2]      接收fifo中断告警寄存器，当新的中断来临时，老的中断还没有清除，产生此告警信号，写1清除。
 bit[1]      保留
 bit[0]      接收fifo溢出中断告警寄存器，当新的中断来临时，老的中断还没有清除，产生此告警信号，写1清除。
             
   UNION结构:  ABB_CFG_CFG_INT_ALM_UNION */
#define ABB_CFG_CFG_INT_ALM_ADDR                      (SOC_BBP_ABB_CFG_BASE_ADDR + 0x38)

/* 寄存器说明：FIFO时钟门控
 bit[31:1]   保留
 bit[0]      FIFO时钟门控使能信号
             1'b0 : 不进行时钟门控
             1'b1 : 进行时钟门控
   UNION结构:  ABB_CFG_MEM_CTRL_UNION */
#define ABB_CFG_MEM_CTRL_ADDR                         (SOC_BBP_ABB_CFG_BASE_ADDR + 0x3C)

/* 寄存器说明：BBP配置使能
 bit[31:5]   保留
 bit[4:0]    软件屏蔽各BBP配置ABB线控信号，
             5'b1_1110:屏蔽LTE模；
             5'b1_1101:屏蔽W模；
             5'b1_1011:屏蔽TDS模；
             5'b1_0111:屏蔽G1模；
             5'b0_1111:屏蔽G2模；
             5'b0_0000:全屏蔽
             5'b1_1111:全不屏蔽（默认）
             
   UNION结构:  ABB_CFG_BBP_CFG_EN_UNION */
#define ABB_CFG_BBP_CFG_EN_ADDR                       (SOC_BBP_ABB_CFG_BASE_ADDR + 0xFC)

/* 寄存器说明：LTE模式定时操作控制寄存器
 bit[31:4]   保留
 bit[3:1]    lte模式定时操作读写寄存器个数：
             0：1
             1：2
             ...
             7: 8
 bit[0]      lte模式定时操作读写控制：
             1'b0：写操作
             1'b1：读操作
   UNION结构:  ABB_CFG_L_CFG_CTRL_UNION */
#define ABB_CFG_L_CFG_CTRL_ADDR                       (SOC_BBP_ABB_CFG_BASE_ADDR + 0x100)

/* 寄存器说明：TDS模式定时操作控制寄存器
 bit[31:4]   保留
 bit[3:1]    tds模式定时操作读写寄存器个数：
             0：1
             1：2
             ...
             7: 8
 bit[0]      tds模式定时操作读写控制：
             1'b0：写操作
             1'b1：读操作
   UNION结构:  ABB_CFG_T_CFG_CTRL_UNION */
#define ABB_CFG_T_CFG_CTRL_ADDR                       (SOC_BBP_ABB_CFG_BASE_ADDR + 0x104)

/* 寄存器说明：W模式定时操作控制寄存器
 bit[31:4]   保留
 bit[3:1]    wcdma模式定时操作读写寄存器个数：
             0：1
             1：2
             ...
             7: 8
 bit[0]      wcdma模式定时操作读写控制：
             1'b0：写操作
             1'b1：读操作
   UNION结构:  ABB_CFG_W_CFG_CTRL_UNION */
#define ABB_CFG_W_CFG_CTRL_ADDR                       (SOC_BBP_ABB_CFG_BASE_ADDR + 0x108)

/* 寄存器说明：G1模式定时操作控制寄存器
 bit[31:4]   保留
 bit[3:1]    gsm1模式定时操作读写寄存器个数：
             0：1
             1：2
             ...
             7: 8
 bit[0]      gsm1模式定时操作读写控制：
             1'b0：写操作
             1'b1：读操作
   UNION结构:  ABB_CFG_G1_CFG_CTRL_UNION */
#define ABB_CFG_G1_CFG_CTRL_ADDR                      (SOC_BBP_ABB_CFG_BASE_ADDR + 0x10C)

/* 寄存器说明：G2模式定时操作控制寄存器
 bit[31:4]   保留
 bit[3:1]    gsm2模式定时操作读写寄存器个数：
             0：1
             1：2
             ...
             7: 8
 bit[0]      gsm2模式定时操作读写控制：
             1'b0：写操作
             1'b1：读操作
   UNION结构:  ABB_CFG_G2_CFG_CTRL_UNION */
#define ABB_CFG_G2_CFG_CTRL_ADDR                      (SOC_BBP_ABB_CFG_BASE_ADDR + 0x110)

/* 寄存器说明：软件强配LTE模定时发送使能
 bit[31:1]   保留
 bit[0:0]    软件强配lte模定时发送使能
             1：强配发送有效
             0：强配发送无效
   UNION结构:  ABB_CFG_L_MODE_VLD_EN_UNION */
#define ABB_CFG_L_MODE_VLD_EN_ADDR                    (SOC_BBP_ABB_CFG_BASE_ADDR + 0x130)

/* 寄存器说明：软件强配TDS模定时发送使能
 bit[31:1]   保留
 bit[0:0]    软件强配tds模定时发送使能
             1：强配发送有效
             0：强配发送无效
   UNION结构:  ABB_CFG_T_MODE_VLD_EN_UNION */
#define ABB_CFG_T_MODE_VLD_EN_ADDR                    (SOC_BBP_ABB_CFG_BASE_ADDR + 0x134)

/* 寄存器说明：软件强配W模定时发送使能
 bit[31:1]   保留
 bit[0:0]    软件强配w模定时发送使能
             1：强配发送有效
             0：强配发送无效
   UNION结构:  ABB_CFG_W_MODE_VLD_EN_UNION */
#define ABB_CFG_W_MODE_VLD_EN_ADDR                    (SOC_BBP_ABB_CFG_BASE_ADDR + 0x138)

/* 寄存器说明：软件强配G1模定时发送使能
 bit[31:1]   保留
 bit[0:0]    软件强配g1模定时发送使能
             1：强配发送有效
             0：强配发送无效
   UNION结构:  ABB_CFG_G1_MODE_VLD_EN_UNION */
#define ABB_CFG_G1_MODE_VLD_EN_ADDR                   (SOC_BBP_ABB_CFG_BASE_ADDR + 0x13C)

/* 寄存器说明：软件强配G2模定时发送使能
 bit[31:1]   保留
 bit[0:0]    软件强配g2模定时发送使能
             1：强配发送有效
             0：强配发送无效
   UNION结构:  ABB_CFG_G2_MODE_VLD_EN_UNION */
#define ABB_CFG_G2_MODE_VLD_EN_ADDR                   (SOC_BBP_ABB_CFG_BASE_ADDR + 0x140)

/* 寄存器说明：定时模式下lte bbp配置ABB的数据
   详      述：定时模式下lte bbp配置ABB的数据，
            写格式：
            bit[12:0]：写地址
            bit[20:13]:写数据
            其余保留
            读格式：
            bit[12:0]：读地址
            bit[20:13]:回读数据
            其余保留
   UNION结构 ：无 */
#define ABB_CFG_L_CFG_DATA_ADDR                       (SOC_BBP_ABB_CFG_BASE_ADDR + 0x160)

/* 寄存器说明：定时模式下tds bbp配置ABB的数据
   详      述：定时模式下tds bbp配置ABB的数据，
            写格式：
            bit[12:0]：写地址
            bit[20:13]:写数据
            其余保留
            读格式：
            bit[12:0]：读地址
            bit[20:13]:回读数据
            其余保留
   UNION结构 ：无 */
#define ABB_CFG_T_CFG_DATA_ADDR                       (SOC_BBP_ABB_CFG_BASE_ADDR + 0x180)

/* 寄存器说明：定时模式下w bbp配置ABB的数据
   详      述：定时模式下wcdma bbp配置ABB的数据，
            写格式：
            bit[12:0]：写地址
            bit[20:13]:写数据
            其余保留
            读格式：
            bit[12:0]：读地址
            bit[20:13]:回读数据
            其余保留
   UNION结构 ：无 */
#define ABB_CFG_W_CFG_DATA_ADDR                       (SOC_BBP_ABB_CFG_BASE_ADDR + 0x1A0)

/* 寄存器说明：定时模式下gsm1 bbp配置ABB的数据
   详      述：定时模式下gsm1 bbp配置ABB的数据，
            写格式：
            bit[12:0]：写地址
            bit[20:13]:写数据
            其余保留
            读格式：
            bit[12:0]：读地址
            bit[20:13]:回读数据
            其余保留
   UNION结构 ：无 */
#define ABB_CFG_G1_CFG_DATA_ADDR                      (SOC_BBP_ABB_CFG_BASE_ADDR + 0x1C0)

/* 寄存器说明：定时模式下gsm2 bbp配置ABB的数据
   详      述：定时模式下gsm2 bbp配置ABB的数据，
            写格式：
            bit[12:0]：写地址
            bit[20:13]:写数据
            其余保留
            读格式：
            bit[12:0]：读地址
            bit[20:13]:回读数据
            其余保留
   UNION结构 ：无 */
#define ABB_CFG_G2_CFG_DATA_ADDR                      (SOC_BBP_ABB_CFG_BASE_ADDR + 0x1E0)

/* 寄存器说明：中断状态存器
 bit[31:4]   保留
 bit[3]      发送fifo中断标志：
             1'b0:无中断
             1'b1:有中断
 bit[2]      接收fifo中断标志：
             1'b0:无中断
             1'b1:有中断
 bit[1]      保留
 bit[0]      接收fifo溢出中断标志：
             1'b0:无中断
             1'b1:有中断
   UNION结构:  ABB_CFG_CFG_INT_STATE_UNION */
#define ABB_CFG_CFG_INT_STATE_ADDR                    (SOC_BBP_ABB_CFG_BASE_ADDR + 0x200)

/* 寄存器说明：FIFO状态存器
 bit[31:12]  保留
 bit[11:8]   rxfifo中数据个数
 bit[7:4]    txfifo中数据个数
 bit[3]      接收fifo满标志：
             1'b0:非满
             1'b1:满
 bit[2]      接收fifo空标志：
             1'b0:非空
             1'b1:空
 bit[1]      发送fifo满标志：
             1'b0:非满
             1'b1:满
 bit[0]      发送fifo空标志：
             1'b0:非空
             1'b1:空
   UNION结构:  ABB_CFG_FIFO_STATE_UNION */
#define ABB_CFG_FIFO_STATE_ADDR                       (SOC_BBP_ABB_CFG_BASE_ADDR + 0x204)

/* 寄存器说明：BBP当前配置状态指示
 bit[31:5]   保留
 bit[4]      g2模当前配置ABB状态指示：
             0：当前没有配置，可以启动新的配置
             1：当前正在配置，不能启动新的配置
 bit[3]      g1模当前配置ABB状态指示：
             0：当前没有配置，可以启动新的配置
             1：当前正在配置，不能启动新的配置
 bit[2]      t模当前配置ABB状态指示：
             0：当前没有配置，可以启动新的配置
             1：当前正在配置，不能启动新的配置
 bit[1]      w模当前配置ABB状态指示：
             0：当前没有配置，可以启动新的配置
             1：当前正在配置，不能启动新的配置
 bit[0]      l模当前配置ABB状态指示：
             0：当前没有配置，可以启动新的配置
             1：当前正在配置，不能启动新的配置
   UNION结构:  ABB_CFG_BBP_RW_STATE_UNION */
#define ABB_CFG_BBP_RW_STATE_ADDR                     (SOC_BBP_ABB_CFG_BASE_ADDR + 0x208)





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
                     (1/1) register_define_abb_cfg
 ***======================================================================***/
/*****************************************************************************
 结构名    : ABB_CFG_SOFT_RST_UNION
 结构说明  : SOFT_RST 寄存器结构定义。地址偏移量:0x0000，初值:0x00000000，宽度:32
 寄存器说明: 软复位
*****************************************************************************/
typedef union
{
    unsigned long      soft_rst_reg;
    struct
    {
        unsigned long  soft_rst : 1;  /* bit[0]   : 复位寄存器：
                                                    1'b0：解除复位
                                                    1'b1:进入复位
                                                    配置时刻：任意
                                                    生效时刻：立即 */
        unsigned long  reserved : 31; /* bit[1-31]: 保留 */
    } reg;
} ABB_CFG_SOFT_RST_UNION;
#define ABB_CFG_SOFT_RST_soft_rst_START  (0)
#define ABB_CFG_SOFT_RST_soft_rst_END    (0)


/*****************************************************************************
 结构名    : ABB_CFG_CFG_CTRL0_UNION
 结构说明  : CFG_CTRL0 寄存器结构定义。地址偏移量:0x0004，初值:0x00000003，宽度:32
 寄存器说明: abb配置模式
*****************************************************************************/
typedef union
{
    unsigned long      cfg_ctrl0_reg;
    struct
    {
        unsigned long  abt_en   : 1;  /* bit[0]   : 仲裁使能：
                                                    1'b0:屏蔽仲裁功能
                                                    1'b1:使能仲裁功能 */
        unsigned long  cfg_mode : 1;  /* bit[1]   : abb配置模式：
                                                    1'b0:软件间接配置abb寄存器
                                                    1'b1:软件直接配置abb寄存器 */
        unsigned long  reserved : 30; /* bit[2-31]: 保留 */
    } reg;
} ABB_CFG_CFG_CTRL0_UNION;
#define ABB_CFG_CFG_CTRL0_abt_en_START    (0)
#define ABB_CFG_CFG_CTRL0_abt_en_END      (0)
#define ABB_CFG_CFG_CTRL0_cfg_mode_START  (1)
#define ABB_CFG_CFG_CTRL0_cfg_mode_END    (1)


/*****************************************************************************
 结构名    : ABB_CFG_CFG_CTRL1_UNION
 结构说明  : CFG_CTRL1 寄存器结构定义。地址偏移量:0x0008，初值:0x00000000，宽度:32
 寄存器说明: abb配置模式
*****************************************************************************/
typedef union
{
    unsigned long      cfg_ctrl1_reg;
    struct
    {
        unsigned long  cfg_rw   : 1;  /* bit[0]   : 软件读写标志：
                                                    1'b0:写
                                                    1'b1:读 */
        unsigned long  reserved : 31; /* bit[1-31]: 保留 */
    } reg;
} ABB_CFG_CFG_CTRL1_UNION;
#define ABB_CFG_CFG_CTRL1_cfg_rw_START    (0)
#define ABB_CFG_CFG_CTRL1_cfg_rw_END      (0)


/*****************************************************************************
 结构名    : ABB_CFG_CFG_CTRL2_UNION
 结构说明  : CFG_CTRL2 寄存器结构定义。地址偏移量:0x000C，初值:0x00000000，宽度:32
 寄存器说明: abb配置模式
*****************************************************************************/
typedef union
{
    unsigned long      cfg_ctrl2_reg;
    struct
    {
        unsigned long  txfifo_wl : 3;  /* bit[0-2] : 发送fifo水线，当发送fifo当前存储深度小于该水线时，产生发送fifo中断。
                                                     3'b000:1
                                                     3'b001:2
                                                     3'b010:3
                                                     3'b011:4
                                                     3'b100:5
                                                     3'b101:6
                                                     3'b110:7
                                                     3'b111:8 */
        unsigned long  rxfifo_wl : 3;  /* bit[3-5] : 接收fifo水线，当接收fifo当前存储深度大于该水线时，产生接收fifo中断。
                                                     3'b000:1
                                                     3'b001:2
                                                     3'b010:3
                                                     3'b011:4
                                                     3'b100:5
                                                     3'b101:6
                                                     3'b110:7
                                                     3'b111:8 */
        unsigned long  reserved  : 26; /* bit[6-31]: 保留 */
    } reg;
} ABB_CFG_CFG_CTRL2_UNION;
#define ABB_CFG_CFG_CTRL2_txfifo_wl_START  (0)
#define ABB_CFG_CFG_CTRL2_txfifo_wl_END    (2)
#define ABB_CFG_CFG_CTRL2_rxfifo_wl_START  (3)
#define ABB_CFG_CFG_CTRL2_rxfifo_wl_END    (5)


/*****************************************************************************
 结构名    : ABB_CFG_CFG_INT_MASK_UNION
 结构说明  : CFG_INT_MASK 寄存器结构定义。地址偏移量:0x0030，初值:0x00000000，宽度:32
 寄存器说明: 中断屏蔽寄存器
*****************************************************************************/
typedef union
{
    unsigned long      cfg_int_mask_reg;
    struct
    {
        unsigned long  rorim    : 1;  /* bit[0]   : 接收fifo溢出中断屏蔽位
                                                    1'b0:屏蔽
                                                    1'b1:不屏蔽 */
        unsigned long  reserved_0: 1;  /* bit[1]   : 保留 */
        unsigned long  rxim     : 1;  /* bit[2]   : 接收fifo中断屏蔽位
                                                    1'b0:屏蔽
                                                    1'b1:不屏蔽 */
        unsigned long  txim     : 1;  /* bit[3]   : 发送fifo中断屏蔽位
                                                    1'b0:屏蔽
                                                    1'b1:不屏蔽 */
        unsigned long  reserved_1: 28; /* bit[4-31]: 保留 */
    } reg;
} ABB_CFG_CFG_INT_MASK_UNION;
#define ABB_CFG_CFG_INT_MASK_rorim_START     (0)
#define ABB_CFG_CFG_INT_MASK_rorim_END       (0)
#define ABB_CFG_CFG_INT_MASK_rxim_START      (2)
#define ABB_CFG_CFG_INT_MASK_rxim_END        (2)
#define ABB_CFG_CFG_INT_MASK_txim_START      (3)
#define ABB_CFG_CFG_INT_MASK_txim_END        (3)


/*****************************************************************************
 结构名    : ABB_CFG_CFG_INT_CLR_UNION
 结构说明  : CFG_INT_CLR 寄存器结构定义。地址偏移量:0x0034，初值:0x00000000，宽度:32
 寄存器说明: 中断清除寄存器
*****************************************************************************/
typedef union
{
    unsigned long      cfg_int_clr_reg;
    struct
    {
        unsigned long  roric    : 1;  /* bit[0]   : 接收fifo溢出中断清除位
                                                    1'b0:不清除
                                                    1'b1:清除 */
        unsigned long  reserved_0: 1;  /* bit[1]   : 保留 */
        unsigned long  rxic     : 1;  /* bit[2]   : 接收fifo中断清除位
                                                    1'b0:不清除
                                                    1'b1:清除 */
        unsigned long  txic     : 1;  /* bit[3]   : 发送fifo中断清除位
                                                    1'b0:不清除
                                                    1'b1:清除 */
        unsigned long  reserved_1: 28; /* bit[4-31]: 保留 */
    } reg;
} ABB_CFG_CFG_INT_CLR_UNION;
#define ABB_CFG_CFG_INT_CLR_roric_START     (0)
#define ABB_CFG_CFG_INT_CLR_roric_END       (0)
#define ABB_CFG_CFG_INT_CLR_rxic_START      (2)
#define ABB_CFG_CFG_INT_CLR_rxic_END        (2)
#define ABB_CFG_CFG_INT_CLR_txic_START      (3)
#define ABB_CFG_CFG_INT_CLR_txic_END        (3)


/*****************************************************************************
 结构名    : ABB_CFG_CFG_INT_ALM_UNION
 结构说明  : CFG_INT_ALM 寄存器结构定义。地址偏移量:0x0038，初值:0x00000000，宽度:32
 寄存器说明: 中断告警寄存器
*****************************************************************************/
typedef union
{
    unsigned long      cfg_int_alm_reg;
    struct
    {
        unsigned long  roria    : 1;  /* bit[0]   : 接收fifo溢出中断告警寄存器，当新的中断来临时，老的中断还没有清除，产生此告警信号，写1清除。 */
        unsigned long  reserved_0: 1;  /* bit[1]   : 保留 */
        unsigned long  rxia     : 1;  /* bit[2]   : 接收fifo中断告警寄存器，当新的中断来临时，老的中断还没有清除，产生此告警信号，写1清除。 */
        unsigned long  txia     : 1;  /* bit[3]   : 发送fifo中断告警寄存器，当新的中断来临时，老的中断还没有清除，产生此告警信号，写1清除。 */
        unsigned long  reserved_1: 28; /* bit[4-31]: 保留 */
    } reg;
} ABB_CFG_CFG_INT_ALM_UNION;
#define ABB_CFG_CFG_INT_ALM_roria_START     (0)
#define ABB_CFG_CFG_INT_ALM_roria_END       (0)
#define ABB_CFG_CFG_INT_ALM_rxia_START      (2)
#define ABB_CFG_CFG_INT_ALM_rxia_END        (2)
#define ABB_CFG_CFG_INT_ALM_txia_START      (3)
#define ABB_CFG_CFG_INT_ALM_txia_END        (3)


/*****************************************************************************
 结构名    : ABB_CFG_MEM_CTRL_UNION
 结构说明  : MEM_CTRL 寄存器结构定义。地址偏移量:0x003C，初值:0x00000000，宽度:32
 寄存器说明: FIFO时钟门控
*****************************************************************************/
typedef union
{
    unsigned long      mem_ctrl_reg;
    struct
    {
        unsigned long  clk_sel  : 1;  /* bit[0]   : FIFO时钟门控使能信号
                                                    1'b0 : 不进行时钟门控
                                                    1'b1 : 进行时钟门控 */
        unsigned long  reserved : 31; /* bit[1-31]: 保留 */
    } reg;
} ABB_CFG_MEM_CTRL_UNION;
#define ABB_CFG_MEM_CTRL_clk_sel_START   (0)
#define ABB_CFG_MEM_CTRL_clk_sel_END     (0)


/*****************************************************************************
 结构名    : ABB_CFG_BBP_CFG_EN_UNION
 结构说明  : BBP_CFG_EN 寄存器结构定义。地址偏移量:0x00FC，初值:0x0000001F，宽度:32
 寄存器说明: BBP配置使能
*****************************************************************************/
typedef union
{
    unsigned long      bbp_cfg_en_reg;
    struct
    {
        unsigned long  bbp_cfg_en : 5;  /* bit[0-4] : 软件屏蔽各BBP配置ABB线控信号，
                                                      5'b1_1110:屏蔽LTE模；
                                                      5'b1_1101:屏蔽W模；
                                                      5'b1_1011:屏蔽TDS模；
                                                      5'b1_0111:屏蔽G1模；
                                                      5'b0_1111:屏蔽G2模；
                                                      5'b0_0000:全屏蔽
                                                      5'b1_1111:全不屏蔽（默认） */
        unsigned long  reserved   : 27; /* bit[5-31]: 保留 */
    } reg;
} ABB_CFG_BBP_CFG_EN_UNION;
#define ABB_CFG_BBP_CFG_EN_bbp_cfg_en_START  (0)
#define ABB_CFG_BBP_CFG_EN_bbp_cfg_en_END    (4)


/*****************************************************************************
 结构名    : ABB_CFG_L_CFG_CTRL_UNION
 结构说明  : L_CFG_CTRL 寄存器结构定义。地址偏移量:0x100，初值:0x00000000，宽度:32
 寄存器说明: LTE模式定时操作控制寄存器
*****************************************************************************/
typedef union
{
    unsigned long      l_cfg_ctrl_reg;
    struct
    {
        unsigned long  l_cfg_rw  : 1;  /* bit[0]   : lte模式定时操作读写控制：
                                                     1'b0：写操作
                                                     1'b1：读操作 */
        unsigned long  l_cfg_num : 3;  /* bit[1-3] : lte模式定时操作读写寄存器个数：
                                                     0：1
                                                     1：2
                                                     ...
                                                     7: 8 */
        unsigned long  reserved  : 28; /* bit[4-31]: 保留 */
    } reg;
} ABB_CFG_L_CFG_CTRL_UNION;
#define ABB_CFG_L_CFG_CTRL_l_cfg_rw_START   (0)
#define ABB_CFG_L_CFG_CTRL_l_cfg_rw_END     (0)
#define ABB_CFG_L_CFG_CTRL_l_cfg_num_START  (1)
#define ABB_CFG_L_CFG_CTRL_l_cfg_num_END    (3)


/*****************************************************************************
 结构名    : ABB_CFG_T_CFG_CTRL_UNION
 结构说明  : T_CFG_CTRL 寄存器结构定义。地址偏移量:0x104，初值:0x00000000，宽度:32
 寄存器说明: TDS模式定时操作控制寄存器
*****************************************************************************/
typedef union
{
    unsigned long      t_cfg_ctrl_reg;
    struct
    {
        unsigned long  t_cfg_rw  : 1;  /* bit[0]   : tds模式定时操作读写控制：
                                                     1'b0：写操作
                                                     1'b1：读操作 */
        unsigned long  t_cfg_num : 3;  /* bit[1-3] : tds模式定时操作读写寄存器个数：
                                                     0：1
                                                     1：2
                                                     ...
                                                     7: 8 */
        unsigned long  reserved  : 28; /* bit[4-31]: 保留 */
    } reg;
} ABB_CFG_T_CFG_CTRL_UNION;
#define ABB_CFG_T_CFG_CTRL_t_cfg_rw_START   (0)
#define ABB_CFG_T_CFG_CTRL_t_cfg_rw_END     (0)
#define ABB_CFG_T_CFG_CTRL_t_cfg_num_START  (1)
#define ABB_CFG_T_CFG_CTRL_t_cfg_num_END    (3)


/*****************************************************************************
 结构名    : ABB_CFG_W_CFG_CTRL_UNION
 结构说明  : W_CFG_CTRL 寄存器结构定义。地址偏移量:0x108，初值:0x00000000，宽度:32
 寄存器说明: W模式定时操作控制寄存器
*****************************************************************************/
typedef union
{
    unsigned long      w_cfg_ctrl_reg;
    struct
    {
        unsigned long  w_cfg_rw  : 1;  /* bit[0]   : wcdma模式定时操作读写控制：
                                                     1'b0：写操作
                                                     1'b1：读操作 */
        unsigned long  w_cfg_num : 3;  /* bit[1-3] : wcdma模式定时操作读写寄存器个数：
                                                     0：1
                                                     1：2
                                                     ...
                                                     7: 8 */
        unsigned long  reserved  : 28; /* bit[4-31]: 保留 */
    } reg;
} ABB_CFG_W_CFG_CTRL_UNION;
#define ABB_CFG_W_CFG_CTRL_w_cfg_rw_START   (0)
#define ABB_CFG_W_CFG_CTRL_w_cfg_rw_END     (0)
#define ABB_CFG_W_CFG_CTRL_w_cfg_num_START  (1)
#define ABB_CFG_W_CFG_CTRL_w_cfg_num_END    (3)


/*****************************************************************************
 结构名    : ABB_CFG_G1_CFG_CTRL_UNION
 结构说明  : G1_CFG_CTRL 寄存器结构定义。地址偏移量:0x10C，初值:0x00000000，宽度:32
 寄存器说明: G1模式定时操作控制寄存器
*****************************************************************************/
typedef union
{
    unsigned long      g1_cfg_ctrl_reg;
    struct
    {
        unsigned long  g1_cfg_rw  : 1;  /* bit[0]   : gsm1模式定时操作读写控制：
                                                      1'b0：写操作
                                                      1'b1：读操作 */
        unsigned long  g1_cfg_num : 3;  /* bit[1-3] : gsm1模式定时操作读写寄存器个数：
                                                      0：1
                                                      1：2
                                                      ...
                                                      7: 8 */
        unsigned long  reserved   : 28; /* bit[4-31]: 保留 */
    } reg;
} ABB_CFG_G1_CFG_CTRL_UNION;
#define ABB_CFG_G1_CFG_CTRL_g1_cfg_rw_START   (0)
#define ABB_CFG_G1_CFG_CTRL_g1_cfg_rw_END     (0)
#define ABB_CFG_G1_CFG_CTRL_g1_cfg_num_START  (1)
#define ABB_CFG_G1_CFG_CTRL_g1_cfg_num_END    (3)


/*****************************************************************************
 结构名    : ABB_CFG_G2_CFG_CTRL_UNION
 结构说明  : G2_CFG_CTRL 寄存器结构定义。地址偏移量:0x110，初值:0x00000000，宽度:32
 寄存器说明: G2模式定时操作控制寄存器
*****************************************************************************/
typedef union
{
    unsigned long      g2_cfg_ctrl_reg;
    struct
    {
        unsigned long  g2_cfg_rw  : 1;  /* bit[0]   : gsm2模式定时操作读写控制：
                                                      1'b0：写操作
                                                      1'b1：读操作 */
        unsigned long  g2_cfg_num : 3;  /* bit[1-3] : gsm2模式定时操作读写寄存器个数：
                                                      0：1
                                                      1：2
                                                      ...
                                                      7: 8 */
        unsigned long  reserved   : 28; /* bit[4-31]: 保留 */
    } reg;
} ABB_CFG_G2_CFG_CTRL_UNION;
#define ABB_CFG_G2_CFG_CTRL_g2_cfg_rw_START   (0)
#define ABB_CFG_G2_CFG_CTRL_g2_cfg_rw_END     (0)
#define ABB_CFG_G2_CFG_CTRL_g2_cfg_num_START  (1)
#define ABB_CFG_G2_CFG_CTRL_g2_cfg_num_END    (3)


/*****************************************************************************
 结构名    : ABB_CFG_L_MODE_VLD_EN_UNION
 结构说明  : L_MODE_VLD_EN 寄存器结构定义。地址偏移量:0x0130，初值:0x00000000，宽度:32
 寄存器说明: 软件强配LTE模定时发送使能
*****************************************************************************/
typedef union
{
    unsigned long      l_mode_vld_en_reg;
    struct
    {
        unsigned long  l_mode_vld_en : 1;  /* bit[0-0] : 软件强配lte模定时发送使能
                                                         1：强配发送有效
                                                         0：强配发送无效 */
        unsigned long  reserved      : 31; /* bit[1-31]: 保留 */
    } reg;
} ABB_CFG_L_MODE_VLD_EN_UNION;
#define ABB_CFG_L_MODE_VLD_EN_l_mode_vld_en_START  (0)
#define ABB_CFG_L_MODE_VLD_EN_l_mode_vld_en_END    (0)


/*****************************************************************************
 结构名    : ABB_CFG_T_MODE_VLD_EN_UNION
 结构说明  : T_MODE_VLD_EN 寄存器结构定义。地址偏移量:0x0134，初值:0x00000000，宽度:32
 寄存器说明: 软件强配TDS模定时发送使能
*****************************************************************************/
typedef union
{
    unsigned long      t_mode_vld_en_reg;
    struct
    {
        unsigned long  t_mode_vld_en : 1;  /* bit[0-0] : 软件强配tds模定时发送使能
                                                         1：强配发送有效
                                                         0：强配发送无效 */
        unsigned long  reserved      : 31; /* bit[1-31]: 保留 */
    } reg;
} ABB_CFG_T_MODE_VLD_EN_UNION;
#define ABB_CFG_T_MODE_VLD_EN_t_mode_vld_en_START  (0)
#define ABB_CFG_T_MODE_VLD_EN_t_mode_vld_en_END    (0)


/*****************************************************************************
 结构名    : ABB_CFG_W_MODE_VLD_EN_UNION
 结构说明  : W_MODE_VLD_EN 寄存器结构定义。地址偏移量:0x0138，初值:0x00000000，宽度:32
 寄存器说明: 软件强配W模定时发送使能
*****************************************************************************/
typedef union
{
    unsigned long      w_mode_vld_en_reg;
    struct
    {
        unsigned long  w_mode_vld_en : 1;  /* bit[0-0] : 软件强配w模定时发送使能
                                                         1：强配发送有效
                                                         0：强配发送无效 */
        unsigned long  reserved      : 31; /* bit[1-31]: 保留 */
    } reg;
} ABB_CFG_W_MODE_VLD_EN_UNION;
#define ABB_CFG_W_MODE_VLD_EN_w_mode_vld_en_START  (0)
#define ABB_CFG_W_MODE_VLD_EN_w_mode_vld_en_END    (0)


/*****************************************************************************
 结构名    : ABB_CFG_G1_MODE_VLD_EN_UNION
 结构说明  : G1_MODE_VLD_EN 寄存器结构定义。地址偏移量:0x013C，初值:0x00000001，宽度:32
 寄存器说明: 软件强配G1模定时发送使能
*****************************************************************************/
typedef union
{
    unsigned long      g1_mode_vld_en_reg;
    struct
    {
        unsigned long  g1_mode_vld_en : 1;  /* bit[0-0] : 软件强配g1模定时发送使能
                                                          1：强配发送有效
                                                          0：强配发送无效 */
        unsigned long  reserved       : 31; /* bit[1-31]: 保留 */
    } reg;
} ABB_CFG_G1_MODE_VLD_EN_UNION;
#define ABB_CFG_G1_MODE_VLD_EN_g1_mode_vld_en_START  (0)
#define ABB_CFG_G1_MODE_VLD_EN_g1_mode_vld_en_END    (0)


/*****************************************************************************
 结构名    : ABB_CFG_G2_MODE_VLD_EN_UNION
 结构说明  : G2_MODE_VLD_EN 寄存器结构定义。地址偏移量:0x0140，初值:0x00000001，宽度:32
 寄存器说明: 软件强配G2模定时发送使能
*****************************************************************************/
typedef union
{
    unsigned long      g2_mode_vld_en_reg;
    struct
    {
        unsigned long  g2_mode_vld_en : 1;  /* bit[0-0] : 软件强配g2模定时发送使能
                                                          1：强配发送有效
                                                          0：强配发送无效 */
        unsigned long  reserved       : 31; /* bit[1-31]: 保留 */
    } reg;
} ABB_CFG_G2_MODE_VLD_EN_UNION;
#define ABB_CFG_G2_MODE_VLD_EN_g2_mode_vld_en_START  (0)
#define ABB_CFG_G2_MODE_VLD_EN_g2_mode_vld_en_END    (0)


/*****************************************************************************
 结构名    : ABB_CFG_CFG_INT_STATE_UNION
 结构说明  : CFG_INT_STATE 寄存器结构定义。地址偏移量:0x0200，初值:0x00000000，宽度:32
 寄存器说明: 中断状态存器
*****************************************************************************/
typedef union
{
    unsigned long      cfg_int_state_reg;
    struct
    {
        unsigned long  roris    : 1;  /* bit[0]   : 接收fifo溢出中断标志：
                                                    1'b0:无中断
                                                    1'b1:有中断 */
        unsigned long  reserved_0: 1;  /* bit[1]   : 保留 */
        unsigned long  rxis     : 1;  /* bit[2]   : 接收fifo中断标志：
                                                    1'b0:无中断
                                                    1'b1:有中断 */
        unsigned long  txis     : 1;  /* bit[3]   : 发送fifo中断标志：
                                                    1'b0:无中断
                                                    1'b1:有中断 */
        unsigned long  reserved_1: 28; /* bit[4-31]: 保留 */
    } reg;
} ABB_CFG_CFG_INT_STATE_UNION;
#define ABB_CFG_CFG_INT_STATE_roris_START     (0)
#define ABB_CFG_CFG_INT_STATE_roris_END       (0)
#define ABB_CFG_CFG_INT_STATE_rxis_START      (2)
#define ABB_CFG_CFG_INT_STATE_rxis_END        (2)
#define ABB_CFG_CFG_INT_STATE_txis_START      (3)
#define ABB_CFG_CFG_INT_STATE_txis_END        (3)


/*****************************************************************************
 结构名    : ABB_CFG_FIFO_STATE_UNION
 结构说明  : FIFO_STATE 寄存器结构定义。地址偏移量:0x0204，初值:0x00000000，宽度:32
 寄存器说明: FIFO状态存器
*****************************************************************************/
typedef union
{
    unsigned long      fifo_state_reg;
    struct
    {
        unsigned long  txfifo_empty : 1;  /* bit[0]    : 发送fifo空标志：
                                                         1'b0:非空
                                                         1'b1:空 */
        unsigned long  txfifo_full  : 1;  /* bit[1]    : 发送fifo满标志：
                                                         1'b0:非满
                                                         1'b1:满 */
        unsigned long  rxfifo_empty : 1;  /* bit[2]    : 接收fifo空标志：
                                                         1'b0:非空
                                                         1'b1:空 */
        unsigned long  rxfifo_full  : 1;  /* bit[3]    : 接收fifo满标志：
                                                         1'b0:非满
                                                         1'b1:满 */
        unsigned long  txfifo_cnt   : 4;  /* bit[4-7]  : txfifo中数据个数 */
        unsigned long  rxfifo_cnt   : 4;  /* bit[8-11] : rxfifo中数据个数 */
        unsigned long  reserved     : 20; /* bit[12-31]: 保留 */
    } reg;
} ABB_CFG_FIFO_STATE_UNION;
#define ABB_CFG_FIFO_STATE_txfifo_empty_START  (0)
#define ABB_CFG_FIFO_STATE_txfifo_empty_END    (0)
#define ABB_CFG_FIFO_STATE_txfifo_full_START   (1)
#define ABB_CFG_FIFO_STATE_txfifo_full_END     (1)
#define ABB_CFG_FIFO_STATE_rxfifo_empty_START  (2)
#define ABB_CFG_FIFO_STATE_rxfifo_empty_END    (2)
#define ABB_CFG_FIFO_STATE_rxfifo_full_START   (3)
#define ABB_CFG_FIFO_STATE_rxfifo_full_END     (3)
#define ABB_CFG_FIFO_STATE_txfifo_cnt_START    (4)
#define ABB_CFG_FIFO_STATE_txfifo_cnt_END      (7)
#define ABB_CFG_FIFO_STATE_rxfifo_cnt_START    (8)
#define ABB_CFG_FIFO_STATE_rxfifo_cnt_END      (11)


/*****************************************************************************
 结构名    : ABB_CFG_BBP_RW_STATE_UNION
 结构说明  : BBP_RW_STATE 寄存器结构定义。地址偏移量:0x0208，初值:0x00000000，宽度:32
 寄存器说明: BBP当前配置状态指示
*****************************************************************************/
typedef union
{
    unsigned long      bbp_rw_state_reg;
    struct
    {
        unsigned long  l_rw_state  : 1;  /* bit[0]   : l模当前配置ABB状态指示：
                                                       0：当前没有配置，可以启动新的配置
                                                       1：当前正在配置，不能启动新的配置 */
        unsigned long  w_rw_state  : 1;  /* bit[1]   : w模当前配置ABB状态指示：
                                                       0：当前没有配置，可以启动新的配置
                                                       1：当前正在配置，不能启动新的配置 */
        unsigned long  t_rw_state  : 1;  /* bit[2]   : t模当前配置ABB状态指示：
                                                       0：当前没有配置，可以启动新的配置
                                                       1：当前正在配置，不能启动新的配置 */
        unsigned long  g1_rw_state : 1;  /* bit[3]   : g1模当前配置ABB状态指示：
                                                       0：当前没有配置，可以启动新的配置
                                                       1：当前正在配置，不能启动新的配置 */
        unsigned long  g2_rw_state : 1;  /* bit[4]   : g2模当前配置ABB状态指示：
                                                       0：当前没有配置，可以启动新的配置
                                                       1：当前正在配置，不能启动新的配置 */
        unsigned long  reserved    : 27; /* bit[5-31]: 保留 */
    } reg;
} ABB_CFG_BBP_RW_STATE_UNION;
#define ABB_CFG_BBP_RW_STATE_l_rw_state_START   (0)
#define ABB_CFG_BBP_RW_STATE_l_rw_state_END     (0)
#define ABB_CFG_BBP_RW_STATE_w_rw_state_START   (1)
#define ABB_CFG_BBP_RW_STATE_w_rw_state_END     (1)
#define ABB_CFG_BBP_RW_STATE_t_rw_state_START   (2)
#define ABB_CFG_BBP_RW_STATE_t_rw_state_END     (2)
#define ABB_CFG_BBP_RW_STATE_g1_rw_state_START  (3)
#define ABB_CFG_BBP_RW_STATE_g1_rw_state_END    (3)
#define ABB_CFG_BBP_RW_STATE_g2_rw_state_START  (4)
#define ABB_CFG_BBP_RW_STATE_g2_rw_state_END    (4)




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

#endif /* end of bbp_abb_cfg_interface.h */
