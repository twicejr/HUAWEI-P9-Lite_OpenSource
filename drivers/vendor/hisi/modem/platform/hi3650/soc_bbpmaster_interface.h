#ifndef __SOC_BBP_MASTER_INTERFACE_H__
#define __SOC_BBP_MASTER_INTERFACE_H__

#define SOC_BBPMASTER_REG_ADDR(base, offset)                ((base)+(offset))

/* 用于拉高写清脉冲的寄存器 */
#define W_BBP_MASTER_RPT_CLR_HIGH_VALUE                     (0x00000001)

/* 屏蔽中断寄存器值 */
#define W_BBP_MASTER_ISR_SHIELD_VALUE                       (0x00000001)

/* 不屏蔽中断寄存器值 */
#define W_BBP_MASTER_ISR_UNSHIELD_VALUE                     (0x0)

/* 水线中断寄存器MASK */
#define W_BBP_MASTER_ISR_WL_MASK_VALUE                      (0x00000001)

/* 黄线中断寄存器MASK */
#define W_BBP_MASTER_ISR_YL_MASK_VALUE                      (0x00000002)

/* 定时器中断寄存器MASK */
#define W_BBP_MASTER_ISR_TIMER_MASK_VALUE                   (0x00000004)

/* BBPMST总线返回错误中断寄存器MASK */
#define W_BBP_MASTER_ISR_BUS_ERROR_MASK_VALUE               (0x00000008)

/* BBPMST主载波译码超时中断寄存器MASK */
#define W_BBP_MASTER_ISR_MAIN_STEM_OVETIME_MASK_VALUE       (0x00000010)

/* BBPMST辅载波译码超时中断寄存器MASK */
#define W_BBP_MASTER_ISR_SUB_STEM_OVETIME_MASK_VALUE        (0x00000020)

/* 主载波主流HSDPA数据上报，对于CRC校验错误的数据不上报中断寄存器MASK */
#define W_BBP_MASTER_ISR_MAIN_HSDPA_MASK_VALUE              (0x00000040)

/* 辅载波主流HSDPA数据上报，对于CRC校验错误的数据不上报中断寄存器MASK */
#define W_BBP_MASTER_ISR_SUB_HSDPA_MASK_VALUE               (0x00000080)

/* 寄存器W_BBP_MASTER_HEAD_BUFFER_SIZE_REG(0x940C)的大小，按照V9R1芯片规格，TB Head大小由256字节裁剪为128字节 */
#define W_BBP_MASTER_TB_HEAD_SIZE_VALUE                     (0x10000000)

/* 水线值 */
#define W_BBP_MASTER_RPT_WATER_LINE_VALUE                   (0xFFFFFFFF)

/* 译码上报定时器默认时长值 */
#define W_BBP_MASTER_RPT_OVERTIME_DEFAULT_VALUE             (0x00001C80)

/* BBP MASTER寄存器基址 */
#define W_BBP_MASTER_MODE_FG_REG(BaseAddr)                  SOC_BBPMASTER_REG_ADDR(BaseAddr, 0x9400)

/* 在对0x9408~0x9414，0x94A0~0x94A4配置好后配置该寄存器，产生写清脉冲使其生效 */
#define W_BBP_MASTER_RPT_CLR_REG(BaseAddr)                  SOC_BBPMASTER_REG_ADDR(BaseAddr, 0x9404)

/* 存储TB块头部的DDR空间的首地址，是物理地址 */
#define W_BBP_MASTER_HEAD_BUFFER_BASE_ADDR_REG(BaseAddr)    SOC_BBPMASTER_REG_ADDR(BaseAddr, 0x9408)

/*  [31:24]TB块头的存储区大小，64words即256byte，最小单位是8byte
    [23:0]存储TB块头的DDR区间所能存储的TB块头的最大个数 */
#define W_BBP_MASTER_HEAD_BUFFER_SIZE_REG(BaseAddr)         SOC_BBPMASTER_REG_ADDR(BaseAddr, 0x940C)

/* 存储TB块数据的DDR空间的首地址，是物理地址 */
#define W_BBP_MASTER_DATA_BUFFER_BASE_ADDR_REG(BaseAddr)    SOC_BBPMASTER_REG_ADDR(BaseAddr, 0x9410)

/* 存储TB块数据区的DDR空间的大小，最小单位是8byte，例如data_buffer_size配置为100，则TB块数据区的DDR空间大小为800byte */
#define W_BBP_MASTER_DATA_BUFFER_SIZE_REG(BaseAddr)         SOC_BBPMASTER_REG_ADDR(BaseAddr, 0x9414)

/* 正常中断上报的水线 */
#define W_BBP_MASTER_HSD_RPT_WATERLINE_REG(BaseAddr)        SOC_BBPMASTER_REG_ADDR(BaseAddr, 0x9418)

/* 告警中断上报的水线--黄线 */
#define W_BBP_MASTER_HSD_RPT_ALARMLINE_REG(BaseAddr)        SOC_BBPMASTER_REG_ADDR(BaseAddr, 0x941C)

/*  软件设定的等待超时中断上报时长，
    定时器时长 = Hsd_rpt_overtime_value * 32 * Tclk，初始值为10ms，即10ms*245.76MHz/32 */
#define W_BBP_MASTER_HSD_RPT_OVERTIME_VALUE_REG(BaseAddr)   SOC_BBPMASTER_REG_ADDR(BaseAddr, 0x9420)

/* 在配置好0x9418~0x9420以及0x9428后拉高该寄存器，产生一个写清脉冲使其生效 */
#define W_BBP_MASTER_HSD_RPT_SUB_PULSE_REG(BaseAddr)        SOC_BBPMASTER_REG_ADDR(BaseAddr, 0x9424)

/* 一次数据搬移过程中取走的TB块个数，为零代表没有搬走任何数据，该值不应该大于软件读出的HSD_RPT_TB_CNT值 */
#define W_BBP_MASTER_HSD_RPT_SUB_REG(BaseAddr)              SOC_BBPMASTER_REG_ADDR(BaseAddr, 0x9428)

/* 在上报缓存中没被软件读走的TB块个数 */
#define W_BBP_MASTER_HSD_RPT_TB_CNT_REG(BaseAddr)           SOC_BBPMASTER_REG_ADDR(BaseAddr, 0x942C)

/* 在上报缓存HEAD区中的写地址指针，为物理地址 */
#define W_BBP_MASTER_HEAD_BUFFER_WR_INDEX_REG(BaseAddr)     SOC_BBPMASTER_REG_ADDR(BaseAddr, 0x9430)

/* TB_CNT初始值 */
#define W_BBP_MASTER_HSD_RPT_TB_CNT_INIT_REG(BaseAddr)      SOC_BBPMASTER_REG_ADDR(BaseAddr, 0x9460)

/* 在配置好0x9460后拉高该寄存器，产生一个写清脉冲使其生效 */
#define W_BBP_MASTER_HSD_RPT_TB_CNT_CLR_REG(BaseAddr)       SOC_BBPMASTER_REG_ADDR(BaseAddr, 0x94A8)

/* TB头部区地址偏移值 */
#define W_BBP_MASTER_HEAD_BUFFER_OFFSET_ADDR_REG(BaseAddr)  SOC_BBPMASTER_REG_ADDR(BaseAddr, 0x94A0)

/* 数据区地址偏移值 */
#define W_BBP_MASTER_DATA_BUFFER_OFFSET_ADDR_REG(BaseAddr)  SOC_BBPMASTER_REG_ADDR(BaseAddr, 0x94A4)

/* Dallas开始新增配置。
   每个TB块的数据在DDR区间占的空间大小（单位:8byte），DDR中整个数据循环存储区大小必须为该值的整数倍。
   即要求data_buffer_size=tb_data_fix_size*N，N由软件决定 */
#define W_BBP_MASTER_TB_DATA_SIZE_REG(BaseAddr)             SOC_BBPMASTER_REG_ADDR(BaseAddr, 0x94AC)

/* =====BBPMSTER中断寄存器相关===== */
/* BBPMSTER中断状态寄存器 */
#define W_BBP_MASTER_ISR_STATE_REG(BaseAddr)                SOC_BBPMASTER_REG_ADDR(BaseAddr, 0xC0)

/* BBPMSTER中断屏蔽MASK寄存器 */
#define W_BBP_MASTER_ISR_MASK_REG(BaseAddr)                 SOC_BBPMASTER_REG_ADDR(BaseAddr, 0xC4)

/* BBPMSTER中断使能寄存器 */
#define W_BBP_MASTER_ISR_ENABLE_REG(BaseAddr)               SOC_BBPMASTER_REG_ADDR(BaseAddr, 0xC8)

/* BBPMSTER中断清除寄存器 */
#define W_BBP_MASTER_ISR_CLR_REG(BaseAddr)                  SOC_BBPMASTER_REG_ADDR(BaseAddr, 0xCC)

#endif
