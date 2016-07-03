

/*****************************************************************************
  1 其他头文件包含
*****************************************************************************/

#ifndef __SOC_DMSS_INTERFACE_H__
#define __SOC_DMSS_INTERFACE_H__

#ifdef __cplusplus
    #if __cplusplus
        extern "C" {
    #endif
#endif



/*****************************************************************************
  2 宏定义
*****************************************************************************/

/****************************************************************************
                     (1/1) register_DMSS
 ****************************************************************************/
/* 寄存器说明：RTL配置信息0
   位域定义UNION结构:  SOC_DMSS_ASI_RTL_INF0_UNION */
#define SOC_DMSS_ASI_RTL_INF0_ADDR(base, asi_base)    ((base) + (0x000+0x800*(asi_base)))

/* 寄存器说明：RTL配置信息1
   位域定义UNION结构:  SOC_DMSS_ASI_RTL_INF1_UNION */
#define SOC_DMSS_ASI_RTL_INF1_ADDR(base, asi_base)    ((base) + (0x004+0x800*(asi_base)))

/* 寄存器说明：RTL配置信息2
   位域定义UNION结构:  SOC_DMSS_ASI_RTL_INF2_UNION */
#define SOC_DMSS_ASI_RTL_INF2_ADDR(base, asi_base)    ((base) + (0x008+0x800*(asi_base)))

/* 寄存器说明：RTL配置信息3
   位域定义UNION结构:  SOC_DMSS_ASI_RTL_INF3_UNION */
#define SOC_DMSS_ASI_RTL_INF3_ADDR(base, asi_base)    ((base) + (0x00C+0x800*(asi_base)))

/* 寄存器说明：静态时钟门控
   位域定义UNION结构:  SOC_DMSS_ASI_STA_CKG_UNION */
#define SOC_DMSS_ASI_STA_CKG_ADDR(base, asi_base)     ((base) + (0x010+0x800*(asi_base)))

/* 寄存器说明：动态时钟门控
   位域定义UNION结构:  SOC_DMSS_ASI_DYN_CKG_UNION */
#define SOC_DMSS_ASI_DYN_CKG_ADDR(base, asi_base)     ((base) + (0x014+0x800*(asi_base)))

/* 寄存器说明：异步桥时钟门控
   位域定义UNION结构:  SOC_DMSS_ASI_ASYNC_BRG_UNION */
#define SOC_DMSS_ASI_ASYNC_BRG_ADDR(base, asi_base)   ((base) + (0x018+0x800*(asi_base)))

/* 寄存器说明：地址移位
   位域定义UNION结构:  SOC_DMSS_ASI_ADDR_SHIFT_UNION */
#define SOC_DMSS_ASI_ADDR_SHIFT_ADDR(base, asi_base)  ((base) + (0x020+0x800*(asi_base)))

/* 寄存器说明：写数据速率匹配
   位域定义UNION结构:  SOC_DMSS_ASI_RATE_ADPT_UNION */
#define SOC_DMSS_ASI_RATE_ADPT_ADDR(base, asi_base)   ((base) + (0x030+0x800*(asi_base)))

/* 寄存器说明：读保序控制0
   位域定义UNION结构:  SOC_DMSS_ASI_RDR_CTRL0_UNION */
#define SOC_DMSS_ASI_RDR_CTRL0_ADDR(base, asi_base)   ((base) + (0x040+0x800*(asi_base)))

/* 寄存器说明：读保序控制1
   位域定义UNION结构:  SOC_DMSS_ASI_RDR_CTRL1_UNION */
#define SOC_DMSS_ASI_RDR_CTRL1_ADDR(base, asi_base)   ((base) + (0x044+0x800*(asi_base)))

/* 寄存器说明：读保序控制2
   位域定义UNION结构:  SOC_DMSS_ASI_RDR_CTRL2_UNION */
#define SOC_DMSS_ASI_RDR_CTRL2_ADDR(base, asi_base)   ((base) + (0x048+0x800*(asi_base)))

/* 寄存器说明：RBUF的间插模式配置0
   位域定义UNION结构:  SOC_DMSS_ASI_RBUF_INTLV0_UNION */
#define SOC_DMSS_ASI_RBUF_INTLV0_ADDR(base, asi_base)  ((base) + (0x060+0x800*(asi_base)))

/* 寄存器说明：RBUF的间插模式配置1
   位域定义UNION结构:  SOC_DMSS_ASI_RBUF_INTLV1_UNION */
#define SOC_DMSS_ASI_RBUF_INTLV1_ADDR(base, asi_base)  ((base) + (0x064+0x800*(asi_base)))

/* 寄存器说明：命令优先级控制
   位域定义UNION结构:  SOC_DMSS_ASI_QOS_CTRL_UNION */
#define SOC_DMSS_ASI_QOS_CTRL_ADDR(base, asi_base)    ((base) + (0x100+0x800*(asi_base)))

/* 寄存器说明：写命令优先级映射表
   位域定义UNION结构:  SOC_DMSS_ASI_QOS_WRPRI_UNION */
#define SOC_DMSS_ASI_QOS_WRPRI_ADDR(base, asi_base)   ((base) + (0x104+0x800*(asi_base)))

/* 寄存器说明：读命令优先级映射表
   位域定义UNION结构:  SOC_DMSS_ASI_QOS_RDPRI_UNION */
#define SOC_DMSS_ASI_QOS_RDPRI_ADDR(base, asi_base)   ((base) + (0x108+0x800*(asi_base)))

/* 寄存器说明：命令优先级自适应周期映射表
   位域定义UNION结构:  SOC_DMSS_ASI_QOS_ADPT_UNION */
#define SOC_DMSS_ASI_QOS_ADPT_ADDR(base, asi_base)    ((base) + (0x10C+0x800*(asi_base)))

/* 寄存器说明：读命令的latency控制
   位域定义UNION结构:  SOC_DMSS_ASI_QOS_LATENCY_UNION */
#define SOC_DMSS_ASI_QOS_LATENCY_ADDR(base, asi_base)  ((base) + (0x110+0x800*(asi_base)))

/* 寄存器说明：带宽优先级控制0
            （可单独控制读命令优先级，或同时控制读写命令优先级）
   位域定义UNION结构:  SOC_DMSS_ASI_QOS_RGLR0_UNION */
#define SOC_DMSS_ASI_QOS_RGLR0_ADDR(base, asi_base)   ((base) + (0x120+0x800*(asi_base)))

/* 寄存器说明：带宽配置优先级0
   位域定义UNION结构:  SOC_DMSS_ASI_QOS_RGLR0_PRI_UNION */
#define SOC_DMSS_ASI_QOS_RGLR0_PRI_ADDR(base, asi_base)  ((base) + (0x124+0x800*(asi_base)))

/* 寄存器说明：带宽优先级控制1
            （只可单独控制写命令优先级）
   位域定义UNION结构:  SOC_DMSS_ASI_QOS_RGLR1_UNION */
#define SOC_DMSS_ASI_QOS_RGLR1_ADDR(base, asi_base)   ((base) + (0x128+0x800*(asi_base)))

/* 寄存器说明：带宽配置优先级1
   位域定义UNION结构:  SOC_DMSS_ASI_QOS_RGLR1_PRI_UNION */
#define SOC_DMSS_ASI_QOS_RGLR1_PRI_ADDR(base, asi_base)  ((base) + (0x12C+0x800*(asi_base)))

/* 寄存器说明：带宽限流控制0
            （可单独控制读带宽，或同时控制读写总带宽）
   位域定义UNION结构:  SOC_DMSS_ASI_QOS_LMTR0_UNION */
#define SOC_DMSS_ASI_QOS_LMTR0_ADDR(base, asi_base)   ((base) + (0x140+0x800*(asi_base)))

/* 寄存器说明：带宽限流控制1
            （只可单独控制写带宽）
   位域定义UNION结构:  SOC_DMSS_ASI_QOS_LMTR1_UNION */
#define SOC_DMSS_ASI_QOS_LMTR1_ADDR(base, asi_base)   ((base) + (0x144+0x800*(asi_base)))

/* 寄存器说明：带宽限流控制2
            （只可同时控制读写带宽，需与GLB_DCQ_PRILVL0/1配合使用）
   位域定义UNION结构:  SOC_DMSS_ASI_QOS_LMTR2_UNION */
#define SOC_DMSS_ASI_QOS_LMTR2_ADDR(base, asi_base)   ((base) + (0x148+0x800*(asi_base)))

/* 寄存器说明：带宽限流控制0的配置重载
   位域定义UNION结构:  SOC_DMSS_ASI_QOS_LMTR0_OVRD_UNION */
#define SOC_DMSS_ASI_QOS_LMTR0_OVRD_ADDR(base, asi_base)  ((base) + (0x150+0x800*(asi_base)))

/* 寄存器说明：带宽限流控制1的配置重载
   位域定义UNION结构:  SOC_DMSS_ASI_QOS_LMTR1_OVRD_UNION */
#define SOC_DMSS_ASI_QOS_LMTR1_OVRD_ADDR(base, asi_base)  ((base) + (0x154+0x800*(asi_base)))

/* 寄存器说明：基于DDRC命令队列状态的允许命令个数水线
   位域定义UNION结构:  SOC_DMSS_ASI_DCQ_CMDLVL_UNION */
#define SOC_DMSS_ASI_DCQ_CMDLVL_ADDR(base, asi_base)  ((base) + (0x15C+0x800*(asi_base)))

/* 寄存器说明：读命令OSTD限制
   位域定义UNION结构:  SOC_DMSS_ASI_QOS_RDOSTD_UNION */
#define SOC_DMSS_ASI_QOS_RDOSTD_ADDR(base, asi_base)  ((base) + (0x160+0x800*(asi_base)))

/* 寄存器说明：读命令OSTD状态统计
   位域定义UNION结构:  SOC_DMSS_ASI_QOS_RDOSTD_ST_UNION */
#define SOC_DMSS_ASI_QOS_RDOSTD_ST_ADDR(base, asi_base)  ((base) + (0x164+0x800*(asi_base)))

/* 寄存器说明：写命令同MID命令优先级传递使能
   位域定义UNION结构:  SOC_DMSS_ASI_PUSH_WRMID_UNION */
#define SOC_DMSS_ASI_PUSH_WRMID_ADDR(base, asi_base)  ((base) + (0x180+0x800*(asi_base)))

/* 寄存器说明：读命令同MID命令优先级传递使能
   位域定义UNION结构:  SOC_DMSS_ASI_PUSH_RDMID_UNION */
#define SOC_DMSS_ASI_PUSH_RDMID_ADDR(base, asi_base)  ((base) + (0x184+0x800*(asi_base)))

/* 寄存器说明：统计功能屏蔽
   位域定义UNION结构:  SOC_DMSS_ASI_STAT_MASK_UNION */
#define SOC_DMSS_ASI_STAT_MASK_ADDR(base, asi_base)   ((base) + (0x200+0x800*(asi_base)))

/* 寄存器说明：统计周期
   位域定义UNION结构:  SOC_DMSS_ASI_STAT_CYCLE_UNION */
#define SOC_DMSS_ASI_STAT_CYCLE_ADDR(base, asi_base)  ((base) + (0x208+0x800*(asi_base)))

/* 寄存器说明：流量统计过滤配置0
   位域定义UNION结构:  SOC_DMSS_ASI_STAT_FLUX_FILTER0_UNION */
#define SOC_DMSS_ASI_STAT_FLUX_FILTER0_ADDR(base, asi_base)  ((base) + (0x210+0x800*(asi_base)))

/* 寄存器说明：流量统计过滤配置1
   位域定义UNION结构:  SOC_DMSS_ASI_STAT_FLUX_FILTER1_UNION */
#define SOC_DMSS_ASI_STAT_FLUX_FILTER1_ADDR(base, asi_base)  ((base) + (0x214+0x800*(asi_base)))

/* 寄存器说明：写流量统计
   位域定义UNION结构:  SOC_DMSS_ASI_STAT_FLUX_WR_UNION */
#define SOC_DMSS_ASI_STAT_FLUX_WR_ADDR(base, asi_base)  ((base) + (0x218+0x800*(asi_base)))

/* 寄存器说明：读流量统计
   位域定义UNION结构:  SOC_DMSS_ASI_STAT_FLUX_RD_UNION */
#define SOC_DMSS_ASI_STAT_FLUX_RD_ADDR(base, asi_base)  ((base) + (0x21C+0x800*(asi_base)))

/* 寄存器说明：带宽控制器0统计
   位域定义UNION结构:  SOC_DMSS_ASI_STAT_LMTR0_UNION */
#define SOC_DMSS_ASI_STAT_LMTR0_ADDR(base, asi_base)  ((base) + (0x220+0x800*(asi_base)))

/* 寄存器说明：带宽控制器1统计
   位域定义UNION结构:  SOC_DMSS_ASI_STAT_LMTR1_UNION */
#define SOC_DMSS_ASI_STAT_LMTR1_ADDR(base, asi_base)  ((base) + (0x224+0x800*(asi_base)))

/* 寄存器说明：带宽控制器2统计
   位域定义UNION结构:  SOC_DMSS_ASI_STAT_LMTR2_UNION */
#define SOC_DMSS_ASI_STAT_LMTR2_ADDR(base, asi_base)  ((base) + (0x228+0x800*(asi_base)))

/* 寄存器说明：读latency统计
   位域定义UNION结构:  SOC_DMSS_ASI_STAT_RDLAT_UNION */
#define SOC_DMSS_ASI_STAT_RDLAT_ADDR(base, asi_base)  ((base) + (0x22C+0x800*(asi_base)))

/* 寄存器说明：命令优先级0统计
   位域定义UNION结构:  SOC_DMSS_ASI_STAT_PRI0_UNION */
#define SOC_DMSS_ASI_STAT_PRI0_ADDR(base, asi_base)   ((base) + (0x230+0x800*(asi_base)))

/* 寄存器说明：命令优先级1统计
   位域定义UNION结构:  SOC_DMSS_ASI_STAT_PRI1_UNION */
#define SOC_DMSS_ASI_STAT_PRI1_ADDR(base, asi_base)   ((base) + (0x234+0x800*(asi_base)))

/* 寄存器说明：命令优先级2统计
   位域定义UNION结构:  SOC_DMSS_ASI_STAT_PRI2_UNION */
#define SOC_DMSS_ASI_STAT_PRI2_ADDR(base, asi_base)   ((base) + (0x238+0x800*(asi_base)))

/* 寄存器说明：命令优先级3统计
   位域定义UNION结构:  SOC_DMSS_ASI_STAT_PRI3_UNION */
#define SOC_DMSS_ASI_STAT_PRI3_ADDR(base, asi_base)   ((base) + (0x23C+0x800*(asi_base)))

/* 寄存器说明：命令优先级4统计
   位域定义UNION结构:  SOC_DMSS_ASI_STAT_PRI4_UNION */
#define SOC_DMSS_ASI_STAT_PRI4_ADDR(base, asi_base)   ((base) + (0x240+0x800*(asi_base)))

/* 寄存器说明：命令优先级5统计
   位域定义UNION结构:  SOC_DMSS_ASI_STAT_PRI5_UNION */
#define SOC_DMSS_ASI_STAT_PRI5_ADDR(base, asi_base)   ((base) + (0x244+0x800*(asi_base)))

/* 寄存器说明：命令优先级6统计
   位域定义UNION结构:  SOC_DMSS_ASI_STAT_PRI6_UNION */
#define SOC_DMSS_ASI_STAT_PRI6_ADDR(base, asi_base)   ((base) + (0x248+0x800*(asi_base)))

/* 寄存器说明：命令优先级7统计
   位域定义UNION结构:  SOC_DMSS_ASI_STAT_PRI7_UNION */
#define SOC_DMSS_ASI_STAT_PRI7_ADDR(base, asi_base)   ((base) + (0x24C+0x800*(asi_base)))

/* 寄存器说明：锁定安全属性相关配置寄存器
            （当secur_boot_lock信号被拉高超过一个时钟周期时，此寄存器自身及其选定的相关寄存器被锁定为只读，只可通过系统复位解除锁定）
   位域定义UNION结构:  SOC_DMSS_ASI_SEC_LD_SEL_UNION */
#define SOC_DMSS_ASI_SEC_LD_SEL_ADDR(base, asi_base)  ((base) + (0x410+0x800*(asi_base)))

/* 寄存器说明：安全中断使能
   位域定义UNION结构:  SOC_DMSS_ASI_SEC_INT_EN_UNION */
#define SOC_DMSS_ASI_SEC_INT_EN_ADDR(base, asi_base)  ((base) + (0x420+0x800*(asi_base)))

/* 寄存器说明：安全中断状态
   位域定义UNION结构:  SOC_DMSS_ASI_SEC_INT_STATUS_UNION */
#define SOC_DMSS_ASI_SEC_INT_STATUS_ADDR(base, asi_base)  ((base) + (0x424+0x800*(asi_base)))

/* 寄存器说明：记录首个越权命令的信息0
   位域定义UNION结构:  SOC_DMSS_ASI_SEC_FAIL_CMD_INF0_UNION */
#define SOC_DMSS_ASI_SEC_FAIL_CMD_INF0_ADDR(base, asi_base)  ((base) + (0x480+0x800*(asi_base)))

/* 寄存器说明：记录首个越权命令的信息1
   位域定义UNION结构:  SOC_DMSS_ASI_SEC_FAIL_CMD_INF1_UNION */
#define SOC_DMSS_ASI_SEC_FAIL_CMD_INF1_ADDR(base, asi_base)  ((base) + (0x484+0x800*(asi_base)))

/* 寄存器说明：记录首个越权命令的信息2
   位域定义UNION结构:  SOC_DMSS_ASI_SEC_FAIL_CMD_INF2_UNION */
#define SOC_DMSS_ASI_SEC_FAIL_CMD_INF2_ADDR(base, asi_base)  ((base) + (0x488+0x800*(asi_base)))

/* 寄存器说明：集成测试控制寄存器
   位域定义UNION结构:  SOC_DMSS_ASI_SEC_ITCRG_UNION */
#define SOC_DMSS_ASI_SEC_ITCRG_ADDR(base, asi_base)   ((base) + (0x4C0+0x800*(asi_base)))

/* 寄存器说明：集成测试输入寄存器
   位域定义UNION结构:  SOC_DMSS_ASI_SEC_ITIP_UNION */
#define SOC_DMSS_ASI_SEC_ITIP_ADDR(base, asi_base)    ((base) + (0x4C4+0x800*(asi_base)))

/* 寄存器说明：集成测试输出寄存器
   位域定义UNION结构:  SOC_DMSS_ASI_SEC_ITOP_UNION */
#define SOC_DMSS_ASI_SEC_ITOP_ADDR(base, asi_base)    ((base) + (0x4C8+0x800*(asi_base)))

/* 寄存器说明：地址区域映射
            （被锁定条件：sucure_boot_lock信号被拉高过，且ld_region_map配置为1，且对应region在ld_regions的选定范围内。）
   位域定义UNION结构:  SOC_DMSS_ASI_SEC_RGN_MAP_UNION */
#define SOC_DMSS_ASI_SEC_RGN_MAP_ADDR(base, sec_rgns, asi_base)  ((base) + (0x500+0x10*(sec_rgns)+0x800*(asi_base)))

/* 寄存器说明：各地址区域的权限属性设置
            （被锁定条件：sucure_boot_lock信号被拉高过，且ld_region_attrib配置为1，且对应region在ld_regions的选定范围内。）
   位域定义UNION结构:  SOC_DMSS_ASI_SEC_RGN_ATTRIB_UNION */
#define SOC_DMSS_ASI_SEC_RGN_ATTRIB_ADDR(base, sec_rgns, asi_base)  ((base) + (0x504+0x10*(sec_rgns)+0x800*(asi_base)))

/* 寄存器说明：写命令匹配MasterID及其掩码
            （被锁定条件：sucure_boot_lock信号被拉高过，且ld_mid_wr配置为1，且对应region在ld_regions的选定范围内。）
   位域定义UNION结构:  SOC_DMSS_ASI_SEC_MID_WR_UNION */
#define SOC_DMSS_ASI_SEC_MID_WR_ADDR(base, sec_rgns, asi_base)  ((base) + (0x508+0x10*(sec_rgns)+0x800*(asi_base)))

/* 寄存器说明：读命令匹配MasterID及其掩码
            （被锁定条件：sucure_boot_lock信号被拉高过，且ld_mid_rd配置为1，且对应region在ld_regions的选定范围内。）
   位域定义UNION结构:  SOC_DMSS_ASI_SEC_MID_RD_UNION */
#define SOC_DMSS_ASI_SEC_MID_RD_ADDR(base, sec_rgns, asi_base)  ((base) + (0x50C+0x10*(sec_rgns)+0x800*(asi_base)))

/* 寄存器说明：DFX：主要模块工作状态
   位域定义UNION结构:  SOC_DMSS_ASI_DFX_MODULE_UNION */
#define SOC_DMSS_ASI_DFX_MODULE_ADDR(base, asi_base)  ((base) + (0x700+0x800*(asi_base)))

/* 寄存器说明：DFX：FIFO工作状态
   位域定义UNION结构:  SOC_DMSS_ASI_DFX_FIFO_UNION */
#define SOC_DMSS_ASI_DFX_FIFO_ADDR(base, asi_base)    ((base) + (0x704+0x800*(asi_base)))

/* 寄存器说明：DFX：状态机工作状态
   位域定义UNION结构:  SOC_DMSS_ASI_DFX_FSM_UNION */
#define SOC_DMSS_ASI_DFX_FSM_ADDR(base, asi_base)     ((base) + (0x708+0x800*(asi_base)))

/* 寄存器说明：DFX：写OSTD状态
   位域定义UNION结构:  SOC_DMSS_ASI_DFX_WROSTD_UNION */
#define SOC_DMSS_ASI_DFX_WROSTD_ADDR(base, asi_base)  ((base) + (0x70C+0x800*(asi_base)))

/* 寄存器说明：DFX：REORDER模块状态0
   位域定义UNION结构:  SOC_DMSS_ASI_DFX_RDR0_UNION */
#define SOC_DMSS_ASI_DFX_RDR0_ADDR(base, asi_base)    ((base) + (0x710+0x800*(asi_base)))

/* 寄存器说明：DFX：REORDER模块状态1
   位域定义UNION结构:  SOC_DMSS_ASI_DFX_RDR1_UNION */
#define SOC_DMSS_ASI_DFX_RDR1_ADDR(base, asi_base)    ((base) + (0x714+0x800*(asi_base)))

/* 寄存器说明：DFX：异常命令信息中断使能
   位域定义UNION结构:  SOC_DMSS_ASI_DFX_INT_EN_UNION */
#define SOC_DMSS_ASI_DFX_INT_EN_ADDR(base, asi_base)  ((base) + (0x720+0x800*(asi_base)))

/* 寄存器说明：DFX：异常命令信息中断
   位域定义UNION结构:  SOC_DMSS_ASI_DFX_INT_STATUS_UNION */
#define SOC_DMSS_ASI_DFX_INT_STATUS_ADDR(base, asi_base)  ((base) + (0x724+0x800*(asi_base)))

/* 寄存器说明：DFX：异常命令信息记录
   位域定义UNION结构:  SOC_DMSS_ASI_DFX_ABNM_INF_UNION */
#define SOC_DMSS_ASI_DFX_ABNM_INF_ADDR(base, asi_base)  ((base) + (0x728+0x800*(asi_base)))

/* 寄存器说明：DFX：仿真流量冲击状态
            （若RTL中配置DMSS_SIM_DFX_EN为0（通常ASIC版本配置为0，FPGA和EMULATOR版本定义为1），则此寄存器不存在）
   位域定义UNION结构:  SOC_DMSS_ASI_DFX_LOAD_UNION */
#define SOC_DMSS_ASI_DFX_LOAD_ADDR(base, asi_base)    ((base) + (0x760+0x800*(asi_base)))

/* 寄存器说明：代码版本信息
   位域定义UNION结构:  SOC_DMSS_GLB_RTL_VER_UNION */
#define SOC_DMSS_GLB_RTL_VER_ADDR(base)               ((base) + (0x6000))

/* 寄存器说明：代码配置信息0
   位域定义UNION结构:  SOC_DMSS_GLB_RTL_INF0_UNION */
#define SOC_DMSS_GLB_RTL_INF0_ADDR(base)              ((base) + (0x6004))

/* 寄存器说明：代码配置信息1
   位域定义UNION结构:  SOC_DMSS_GLB_RTL_INF1_UNION */
#define SOC_DMSS_GLB_RTL_INF1_ADDR(base)              ((base) + (0x6008))

/* 寄存器说明：MEMORY配置
   位域定义UNION结构:  SOC_DMSS_GLB_RAM_TMOD_UNION */
#define SOC_DMSS_GLB_RAM_TMOD_ADDR(base)              ((base) + (0x6018))

/* 寄存器说明：配置寄存器锁定
   位域定义UNION结构:  SOC_DMSS_GLB_CFG_LOCK_UNION */
#define SOC_DMSS_GLB_CFG_LOCK_ADDR(base)              ((base) + (0x6020))

/* 寄存器说明：动态时钟门控
   位域定义UNION结构:  SOC_DMSS_GLB_DYN_CKG_UNION */
#define SOC_DMSS_GLB_DYN_CKG_ADDR(base)               ((base) + (0x6024))

/* 寄存器说明：全局中断状态查看
   位域定义UNION结构:  SOC_DMSS_GLB_INT_STATUS_UNION */
#define SOC_DMSS_GLB_INT_STATUS_ADDR(base)            ((base) + (0x6030))

/* 寄存器说明：全局中断状态清除
   位域定义UNION结构:  SOC_DMSS_GLB_INT_CLEAR_UNION */
#define SOC_DMSS_GLB_INT_CLEAR_ADDR(base)             ((base) + (0x6034))

/* 寄存器说明：exclusive命令配置
   位域定义UNION结构:  SOC_DMSS_GLB_EXCLU_UNION */
#define SOC_DMSS_GLB_EXCLU_ADDR(base)                 ((base) + (0x6040))

/* 寄存器说明：全局地址交织模式
   位域定义UNION结构:  SOC_DMSS_GLB_ADDR_INTLV_UNION */
#define SOC_DMSS_GLB_ADDR_INTLV_ADDR(base)            ((base) + (0x6100))

/* 寄存器说明：全局地址加扰模式
   位域定义UNION结构:  SOC_DMSS_GLB_ADDR_SCRMBL_UNION */
#define SOC_DMSS_GLB_ADDR_SCRMBL_ADDR(base)           ((base) + (0x6110))

/* 寄存器说明：RBUF的传输起始水线配置0
   位域定义UNION结构:  SOC_DMSS_GLB_RBUF_TRSFR_WL0_UNION */
#define SOC_DMSS_GLB_RBUF_TRSFR_WL0_ADDR(base)        ((base) + (0x6140))

/* 寄存器说明：RBUF的传输起始水线配置1
   位域定义UNION结构:  SOC_DMSS_GLB_RBUF_TRSFR_WL1_UNION */
#define SOC_DMSS_GLB_RBUF_TRSFR_WL1_ADDR(base)        ((base) + (0x6144))

/* 寄存器说明：RBUF的bypass通路使能
   位域定义UNION结构:  SOC_DMSS_GLB_RBUF_BYP_PATH_UNION */
#define SOC_DMSS_GLB_RBUF_BYP_PATH_ADDR(base)         ((base) + (0x6148))

/* 寄存器说明：RBUF的命令反压配置
   位域定义UNION结构:  SOC_DMSS_GLB_RBUF_BP_UNION */
#define SOC_DMSS_GLB_RBUF_BP_ADDR(base, rbuf_bp_grps)  ((base) + (0x6150+0x4*(rbuf_bp_grps)))

/* 寄存器说明：DDRC的命令队列状态统计控制
   位域定义UNION结构:  SOC_DMSS_GLB_DCQ_CTRL_UNION */
#define SOC_DMSS_GLB_DCQ_CTRL_ADDR(base)              ((base) + (0x6200))

/* 寄存器说明：DDRC的命令队列状态
   位域定义UNION结构:  SOC_DMSS_GLB_DCQ_ST_UNION */
#define SOC_DMSS_GLB_DCQ_ST_ADDR(base)                ((base) + (0x6204))

/* 寄存器说明：基于DDRC命令队列状态的允许优先级水线0
   位域定义UNION结构:  SOC_DMSS_GLB_DCQ_PRILVL0_UNION */
#define SOC_DMSS_GLB_DCQ_PRILVL0_ADDR(base)           ((base) + (0x6208))

/* 寄存器说明：基于DDRC命令队列状态的允许优先级水线1
   位域定义UNION结构:  SOC_DMSS_GLB_DCQ_PRILVL1_UNION */
#define SOC_DMSS_GLB_DCQ_PRILVL1_ADDR(base)           ((base) + (0x620C))

/* 寄存器说明：外部master的流控功能
            （【Dallas】
            0x6210：ISP
            0x6214：DSS
            0x6218：ASI0 MODEM）
   位域定义UNION结构:  SOC_DMSS_GLB_DCQ_MST_UNION */
#define SOC_DMSS_GLB_DCQ_MST_ADDR(base, dcq_msts)     ((base) + (0x6210+0x4*(dcq_msts)))

/* 寄存器说明：允许优先级的跳变中断使能
   位域定义UNION结构:  SOC_DMSS_GLB_DCQ_INT_EN_UNION */
#define SOC_DMSS_GLB_DCQ_INT_EN_ADDR(base)            ((base) + (0x6250))

/* 寄存器说明：统计功能控制
   位域定义UNION结构:  SOC_DMSS_GLB_STAT_CTRL_UNION */
#define SOC_DMSS_GLB_STAT_CTRL_ADDR(base)             ((base) + (0x6260))

/* 寄存器说明：所有优先级都允许的统计
   位域定义UNION结构:  SOC_DMSS_GLB_STAT_ALL_ALLOW_UNION */
#define SOC_DMSS_GLB_STAT_ALL_ALLOW_ADDR(base)        ((base) + (0x6270))

/* 寄存器说明：允许优先级为1的统计
   位域定义UNION结构:  SOC_DMSS_GLB_STAT_PRI1_ALLOW_UNION */
#define SOC_DMSS_GLB_STAT_PRI1_ALLOW_ADDR(base)       ((base) + (0x6274))

/* 寄存器说明：允许优先级为2的统计
   位域定义UNION结构:  SOC_DMSS_GLB_STAT_PRI2_ALLOW_UNION */
#define SOC_DMSS_GLB_STAT_PRI2_ALLOW_ADDR(base)       ((base) + (0x6278))

/* 寄存器说明：允许优先级为3的统计
   位域定义UNION结构:  SOC_DMSS_GLB_STAT_PRI3_ALLOW_UNION */
#define SOC_DMSS_GLB_STAT_PRI3_ALLOW_ADDR(base)       ((base) + (0x627C))

/* 寄存器说明：允许优先级为4的统计
   位域定义UNION结构:  SOC_DMSS_GLB_STAT_PRI4_ALLOW_UNION */
#define SOC_DMSS_GLB_STAT_PRI4_ALLOW_ADDR(base)       ((base) + (0x6280))

/* 寄存器说明：允许优先级为5的统计
   位域定义UNION结构:  SOC_DMSS_GLB_STAT_PRI5_ALLOW_UNION */
#define SOC_DMSS_GLB_STAT_PRI5_ALLOW_ADDR(base)       ((base) + (0x6284))

/* 寄存器说明：允许优先级为6的统计
   位域定义UNION结构:  SOC_DMSS_GLB_STAT_PRI6_ALLOW_UNION */
#define SOC_DMSS_GLB_STAT_PRI6_ALLOW_ADDR(base)       ((base) + (0x6288))

/* 寄存器说明：允许优先级为7的统计
   位域定义UNION结构:  SOC_DMSS_GLB_STAT_PRI7_ALLOW_UNION */
#define SOC_DMSS_GLB_STAT_PRI7_ALLOW_ADDR(base)       ((base) + (0x628C))

/* 寄存器说明：DFX：RBUF状态0
   位域定义UNION结构:  SOC_DMSS_GLB_DFX_RBUF0_UNION */
#define SOC_DMSS_GLB_DFX_RBUF0_ADDR(base, chans)      ((base) + (0x6700+0x10*(chans)))

/* 寄存器说明：DFX：RBUF状态1
   位域定义UNION结构:  SOC_DMSS_GLB_DFX_RBUF1_UNION */
#define SOC_DMSS_GLB_DFX_RBUF1_ADDR(base, chans)      ((base) + (0x6704+0x10*(chans)))

/* 寄存器说明：DFX：RBUF状态2
   位域定义UNION结构:  SOC_DMSS_GLB_DFX_RBUF2_UNION */
#define SOC_DMSS_GLB_DFX_RBUF2_ADDR(base, chans)      ((base) + (0x6708+0x10*(chans)))

/* 寄存器说明：DFX：RBUF状态3
   位域定义UNION结构:  SOC_DMSS_GLB_DFX_RBUF3_UNION */
#define SOC_DMSS_GLB_DFX_RBUF3_ADDR(base, chans)      ((base) + (0x670C+0x10*(chans)))

/* 寄存器说明：DFX：DMI的命令仲裁状态
   位域定义UNION结构:  SOC_DMSS_GLB_DFX_DMI_GRNT_UNION */
#define SOC_DMSS_GLB_DFX_DMI_GRNT_ADDR(base)          ((base) + (0x6740))

/* 寄存器说明：DFX：DCQ的状态
   位域定义UNION结构:  SOC_DMSS_GLB_DFX_DCQ_UNION */
#define SOC_DMSS_GLB_DFX_DCQ_ADDR(base)               ((base) + (0x6744))

/* 寄存器说明：DFX：各个ASI的工作状态
   位域定义UNION结构:  SOC_DMSS_GLB_DFX_ASI_BUSY_UNION */
#define SOC_DMSS_GLB_DFX_ASI_BUSY_ADDR(base)          ((base) + (0x6750))

/* 寄存器说明：DFX：仿真流量冲击状态
            （若RTL中配置DMSS_SIM_DFX_EN为0（通常ASIC版本配置为0，FPGA和EMULATOR版本定义为1），则此寄存器不存在）
   位域定义UNION结构:  SOC_DMSS_GLB_DFX_LOAD_UNION */
#define SOC_DMSS_GLB_DFX_LOAD_ADDR(base)              ((base) + (0x6760))





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
                     (1/1) register_DMSS
 ****************************************************************************/
/*****************************************************************************
 结构名    : SOC_DMSS_ASI_RTL_INF0_UNION
 结构说明  : ASI_RTL_INF0 寄存器结构定义。地址偏移量:0x000+0x800*(asi_base)，初值:0x00000000，宽度:32
 寄存器说明: RTL配置信息0
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  rtl_data_width    : 1;  /* bit[0]    : 对接的AXI总线地址位宽：
                                                             0：64bits
                                                             1：128bits。 */
        unsigned int  reserved_0        : 3;  /* bit[1-3]  : 保留 */
        unsigned int  rtl_clk_mode      : 2;  /* bit[4-5]  : 对接AXI总线时钟与DMSS主时钟的关系：
                                                             0x0：低频同步（低频的AXI总线侧不可以设置multicycle，需以高频时钟收时序）；
                                                             0x1：低频同步（低频的AXI总线侧可以设置multicycle，可按低频时钟收时序）；
                                                             0x2：异步；
                                                             0x3：同频同步。
                                                             注意：当对接时钟关系不是异步时，异步相关寄存器无效。 */
        unsigned int  reserved_1        : 10; /* bit[6-15] : 保留 */
        unsigned int  rtl_rdr_que_depth : 2;  /* bit[16-17]: 保序模块的读命令队列监控深度（等效为允许的最大读命令outstanding）：
                                                             0： 8 read cmd；
                                                             1：16 read cmd；
                                                             2：24 read cmd；
                                                             3：32 read cmd。 */
        unsigned int  reserved_2        : 2;  /* bit[18-19]: 保留 */
        unsigned int  rtl_rdr_buf_num   : 2;  /* bit[20-21]: 保序模块的保序buffer深度：
                                                             0： 8 read burst；
                                                             1：16 read burst；
                                                             2：24 read burst；
                                                             3：32 read burst。 */
        unsigned int  reserved_3        : 2;  /* bit[22-23]: 保留 */
        unsigned int  rtl_rdr_en        : 1;  /* bit[24]   : 同ID读保序功能：
                                                             0：不支持；
                                                             1：支持。
                                                             注意：
                                                             1.只有在系统层面保证当前ASI不会收到outstanding的同ID读命令，且任何读命令也不会被ASI拆分成多个同ID的读命令时，才可以RTL配置为不支持保序功能；
                                                             2.当不支持同ID读保序功能，读保序相关寄存器无效。 */
        unsigned int  reserved_4        : 7;  /* bit[25-31]: 保留 */
    } reg;
} SOC_DMSS_ASI_RTL_INF0_UNION;
#endif
#define SOC_DMSS_ASI_RTL_INF0_rtl_data_width_START     (0)
#define SOC_DMSS_ASI_RTL_INF0_rtl_data_width_END       (0)
#define SOC_DMSS_ASI_RTL_INF0_rtl_clk_mode_START       (4)
#define SOC_DMSS_ASI_RTL_INF0_rtl_clk_mode_END         (5)
#define SOC_DMSS_ASI_RTL_INF0_rtl_rdr_que_depth_START  (16)
#define SOC_DMSS_ASI_RTL_INF0_rtl_rdr_que_depth_END    (17)
#define SOC_DMSS_ASI_RTL_INF0_rtl_rdr_buf_num_START    (20)
#define SOC_DMSS_ASI_RTL_INF0_rtl_rdr_buf_num_END      (21)
#define SOC_DMSS_ASI_RTL_INF0_rtl_rdr_en_START         (24)
#define SOC_DMSS_ASI_RTL_INF0_rtl_rdr_en_END           (24)


/*****************************************************************************
 结构名    : SOC_DMSS_ASI_RTL_INF1_UNION
 结构说明  : ASI_RTL_INF1 寄存器结构定义。地址偏移量:0x004+0x800*(asi_base)，初值:0x00000000，宽度:32
 寄存器说明: RTL配置信息1
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  rtl_wcmd_fifo_depth : 5;  /* bit[0-4]  : 写命令FIFO配置深度：
                                                               0x0： 1 write cmd；
                                                               0x1： 2 write cmd；
                                                               ……
                                                               0x31：32 write cmd。 */
        unsigned int  reserved_0          : 3;  /* bit[5-7]  : 保留 */
        unsigned int  rtl_wd_fifo_depth   : 5;  /* bit[8-12] : 写数据FIFO配置深度：
                                                               0x0： 1 write transfer；
                                                               0x1： 2 write transfer；
                                                               ……
                                                               0x31：32 write transfer。 */
        unsigned int  reserved_1          : 3;  /* bit[13-15]: 保留 */
        unsigned int  rtl_b_fifo_depth    : 5;  /* bit[16-20]: 写响应FIFO配置深度：
                                                               0x0： 1 write response；
                                                               0x1： 2 write response；
                                                               ……
                                                               0x31：32 write response。 */
        unsigned int  reserved_2          : 3;  /* bit[21-23]: 保留 */
        unsigned int  rtl_ra_fifo_depth   : 5;  /* bit[24-28]: 速率匹配写数据FIFO配置深度：
                                                               0x0： 1 write transfer；
                                                               0x1： 2 write transfer；
                                                               ……
                                                               0x31：32 write transfer。 */
        unsigned int  reserved_3          : 3;  /* bit[29-31]: 保留 */
    } reg;
} SOC_DMSS_ASI_RTL_INF1_UNION;
#endif
#define SOC_DMSS_ASI_RTL_INF1_rtl_wcmd_fifo_depth_START  (0)
#define SOC_DMSS_ASI_RTL_INF1_rtl_wcmd_fifo_depth_END    (4)
#define SOC_DMSS_ASI_RTL_INF1_rtl_wd_fifo_depth_START    (8)
#define SOC_DMSS_ASI_RTL_INF1_rtl_wd_fifo_depth_END      (12)
#define SOC_DMSS_ASI_RTL_INF1_rtl_b_fifo_depth_START     (16)
#define SOC_DMSS_ASI_RTL_INF1_rtl_b_fifo_depth_END       (20)
#define SOC_DMSS_ASI_RTL_INF1_rtl_ra_fifo_depth_START    (24)
#define SOC_DMSS_ASI_RTL_INF1_rtl_ra_fifo_depth_END      (28)


/*****************************************************************************
 结构名    : SOC_DMSS_ASI_RTL_INF2_UNION
 结构说明  : ASI_RTL_INF2 寄存器结构定义。地址偏移量:0x008+0x800*(asi_base)，初值:0x00000000，宽度:32
 寄存器说明: RTL配置信息2
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  rtl_rbar_fifo_depth : 5;  /* bit[0-4]  : 读barrier命令FIFO配置深度：
                                                               0x0： 1 barrier cmd；
                                                               0x1： 2 barrier cmd；
                                                               ……
                                                               0x31：32 barrier cmd。 */
        unsigned int  reserved_0          : 3;  /* bit[5-7]  : 保留 */
        unsigned int  rtl_rd_fifo_depth   : 5;  /* bit[8-12] : 读数据FIFO配置深度：
                                                               0x0： 1 read transfer；
                                                               0x1： 2 read transfer；
                                                               ……
                                                               0x31：32 read transfer。 */
        unsigned int  reserved_1          : 19; /* bit[13-31]: 保留 */
    } reg;
} SOC_DMSS_ASI_RTL_INF2_UNION;
#endif
#define SOC_DMSS_ASI_RTL_INF2_rtl_rbar_fifo_depth_START  (0)
#define SOC_DMSS_ASI_RTL_INF2_rtl_rbar_fifo_depth_END    (4)
#define SOC_DMSS_ASI_RTL_INF2_rtl_rd_fifo_depth_START    (8)
#define SOC_DMSS_ASI_RTL_INF2_rtl_rd_fifo_depth_END      (12)


/*****************************************************************************
 结构名    : SOC_DMSS_ASI_RTL_INF3_UNION
 结构说明  : ASI_RTL_INF3 寄存器结构定义。地址偏移量:0x00C+0x800*(asi_base)，初值:0x00000000，宽度:32
 寄存器说明: RTL配置信息3
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  rtl_sec_rgn_num : 5;  /* bit[0-4] : 安全模块的regions个数：
                                                          5'd0：无安全模块；
                                                          5'd1：1regions；
                                                          5'd2：2regions；
                                                          5'd3：3regions；
                                                          ……
                                                          注意：当无安全模块时，安全功能相关寄存器无效。 */
        unsigned int  reserved        : 27; /* bit[5-31]: 保留 */
    } reg;
} SOC_DMSS_ASI_RTL_INF3_UNION;
#endif
#define SOC_DMSS_ASI_RTL_INF3_rtl_sec_rgn_num_START  (0)
#define SOC_DMSS_ASI_RTL_INF3_rtl_sec_rgn_num_END    (4)


/*****************************************************************************
 结构名    : SOC_DMSS_ASI_STA_CKG_UNION
 结构说明  : ASI_STA_CKG 寄存器结构定义。地址偏移量:0x010+0x800*(asi_base)，初值:0x00000000，宽度:32
 寄存器说明: 静态时钟门控
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  gt_en_asi : 1;  /* bit[0]   : ASI静态时钟门控：
                                                    0：禁止；
                                                    1：使能，关闭当前ASI整体时钟。
                                                    注意：
                                                    只有确保当前ASI空闲且其对接的master设备彻底无访问时，才可以使能ASI静态时钟门控，否则会导致系统挂死。 */
        unsigned int  reserved  : 31; /* bit[1-31]: 保留 */
    } reg;
} SOC_DMSS_ASI_STA_CKG_UNION;
#endif
#define SOC_DMSS_ASI_STA_CKG_gt_en_asi_START  (0)
#define SOC_DMSS_ASI_STA_CKG_gt_en_asi_END    (0)


/*****************************************************************************
 结构名    : SOC_DMSS_ASI_DYN_CKG_UNION
 结构说明  : ASI_DYN_CKG 寄存器结构定义。地址偏移量:0x014+0x800*(asi_base)，初值:0x00000000，宽度:32
 寄存器说明: 动态时钟门控
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  ckg_byp_asi     : 1;  /* bit[0]    : ASI模块的动态时钟门控：
                                                           0：模块idle时，自动关闭时钟；
                                                           1：时钟常开。 */
        unsigned int  ckg_byp_ra      : 1;  /* bit[1]    : RA模块的动态时钟门控：
                                                           0：模块idle时，自动关闭时钟；
                                                           1：时钟常开。 */
        unsigned int  ckg_byp_ax      : 1;  /* bit[2]    : AX模块的动态时钟门控：
                                                           0：模块idle时，自动关闭时钟；
                                                           1：时钟常开。 */
        unsigned int  ckg_byp_cs      : 1;  /* bit[3]    : CS模块的动态时钟门控：
                                                           0：模块idle时，自动关闭时钟；
                                                           1：时钟常开。 */
        unsigned int  ckg_byp_wd      : 1;  /* bit[4]    : WD模块的动态时钟门控：
                                                           0：模块idle时，自动关闭时钟；
                                                           1：时钟常开。 */
        unsigned int  ckg_byp_b       : 1;  /* bit[5]    : B模块的动态时钟门控：
                                                           0：模块idle时，自动关闭时钟；
                                                           1：时钟常开。 */
        unsigned int  ckg_byp_rd      : 1;  /* bit[6]    : RD模块的动态时钟门控：
                                                           0：模块idle时，自动关闭时钟；
                                                           1：时钟常开。 */
        unsigned int  ckg_byp_fkrd    : 1;  /* bit[7]    : FKRD模块的动态时钟门控：
                                                           0：模块idle时，自动关闭时钟；
                                                           1：时钟常开。 */
        unsigned int  ckg_byp_sec     : 1;  /* bit[8]    : SEC模块的动态时钟门控：
                                                           0：模块idle时，自动关闭时钟；
                                                           1：时钟常开。
                                                           注意：
                                                           当前ASI是否有安全模块，可以通过寄存器ASI_RTL_INF0.rtl_sec_rgn_num确认。 */
        unsigned int  ckg_byp_rdr_est : 1;  /* bit[9]    : RDR_EST模块的动态时钟门控：
                                                           0：模块idle时，自动关闭时钟；
                                                           1：时钟常开。
                                                           注意：
                                                           当前ASI是否有保序模块，可以通过寄存器ASI_RTL_INF0.rtl_rdr_en确认。 */
        unsigned int  ckg_byp_rdr_buf : 1;  /* bit[10]   : RDR_BUF模块的动态时钟门控：
                                                           0：模块idle时，自动关闭时钟；
                                                           1：时钟常开。
                                                           注意：
                                                           当前ASI是否有保序模块，可以通过寄存器ASI_RTL_INF0.rtl_rdr_en确认。 */
        unsigned int  ckg_byp_async   : 1;  /* bit[11]   : ASYNC模块的动态时钟门控：
                                                           0：模块idle时，自动关闭时钟；
                                                           1：时钟常开。
                                                           注意：
                                                           当前ASI是否有异步桥，可以通过寄存器ASI_RTL_INF0.rtl_clk_mode确认。 */
        unsigned int  reserved        : 20; /* bit[12-31]: 保留 */
    } reg;
} SOC_DMSS_ASI_DYN_CKG_UNION;
#endif
#define SOC_DMSS_ASI_DYN_CKG_ckg_byp_asi_START      (0)
#define SOC_DMSS_ASI_DYN_CKG_ckg_byp_asi_END        (0)
#define SOC_DMSS_ASI_DYN_CKG_ckg_byp_ra_START       (1)
#define SOC_DMSS_ASI_DYN_CKG_ckg_byp_ra_END         (1)
#define SOC_DMSS_ASI_DYN_CKG_ckg_byp_ax_START       (2)
#define SOC_DMSS_ASI_DYN_CKG_ckg_byp_ax_END         (2)
#define SOC_DMSS_ASI_DYN_CKG_ckg_byp_cs_START       (3)
#define SOC_DMSS_ASI_DYN_CKG_ckg_byp_cs_END         (3)
#define SOC_DMSS_ASI_DYN_CKG_ckg_byp_wd_START       (4)
#define SOC_DMSS_ASI_DYN_CKG_ckg_byp_wd_END         (4)
#define SOC_DMSS_ASI_DYN_CKG_ckg_byp_b_START        (5)
#define SOC_DMSS_ASI_DYN_CKG_ckg_byp_b_END          (5)
#define SOC_DMSS_ASI_DYN_CKG_ckg_byp_rd_START       (6)
#define SOC_DMSS_ASI_DYN_CKG_ckg_byp_rd_END         (6)
#define SOC_DMSS_ASI_DYN_CKG_ckg_byp_fkrd_START     (7)
#define SOC_DMSS_ASI_DYN_CKG_ckg_byp_fkrd_END       (7)
#define SOC_DMSS_ASI_DYN_CKG_ckg_byp_sec_START      (8)
#define SOC_DMSS_ASI_DYN_CKG_ckg_byp_sec_END        (8)
#define SOC_DMSS_ASI_DYN_CKG_ckg_byp_rdr_est_START  (9)
#define SOC_DMSS_ASI_DYN_CKG_ckg_byp_rdr_est_END    (9)
#define SOC_DMSS_ASI_DYN_CKG_ckg_byp_rdr_buf_START  (10)
#define SOC_DMSS_ASI_DYN_CKG_ckg_byp_rdr_buf_END    (10)
#define SOC_DMSS_ASI_DYN_CKG_ckg_byp_async_START    (11)
#define SOC_DMSS_ASI_DYN_CKG_ckg_byp_async_END      (11)


/*****************************************************************************
 结构名    : SOC_DMSS_ASI_ASYNC_BRG_UNION
 结构说明  : ASI_ASYNC_BRG 寄存器结构定义。地址偏移量:0x018+0x800*(asi_base)，初值:0x0000007F，宽度:32
 寄存器说明: 异步桥时钟门控
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  cactive_wl : 7;  /* bit[0-6] : 异步桥门控计数器水线设置：
                                                     n:当异步桥CACTIVE信号拉低并保持n个时钟周期后，关闭异步桥时钟
                                                     注意：
                                                     若异步桥动态时钟门控设置为常开，则此配置项无效。 */
        unsigned int  reserved   : 25; /* bit[7-31]: 保留 */
    } reg;
} SOC_DMSS_ASI_ASYNC_BRG_UNION;
#endif
#define SOC_DMSS_ASI_ASYNC_BRG_cactive_wl_START  (0)
#define SOC_DMSS_ASI_ASYNC_BRG_cactive_wl_END    (6)


/*****************************************************************************
 结构名    : SOC_DMSS_ASI_ADDR_SHIFT_UNION
 结构说明  : ASI_ADDR_SHIFT 寄存器结构定义。地址偏移量:0x020+0x800*(asi_base)，初值:0x00000000，宽度:32
 寄存器说明: 地址移位
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  addr_shift_mode : 2;  /* bit[0-1] : 地址移位模式：
                                                          0x0,0x3：不移位；
                                                          0x1：将总线访问的4~4.5GB地址，移为3.5~4GB地址；
                                                          0x2：将总线访问的8~8.5GB地址，移为3.5~4GB地址；
                                                          注意：
                                                          1.安全模块进行命令权限检查时，使用的地址是移位前的原始地址；
                                                          2.此寄存器只能在系统初始化时静态配置。 */
        unsigned int  reserved        : 30; /* bit[2-31]: 保留 */
    } reg;
} SOC_DMSS_ASI_ADDR_SHIFT_UNION;
#endif
#define SOC_DMSS_ASI_ADDR_SHIFT_addr_shift_mode_START  (0)
#define SOC_DMSS_ASI_ADDR_SHIFT_addr_shift_mode_END    (1)


/*****************************************************************************
 结构名    : SOC_DMSS_ASI_RATE_ADPT_UNION
 结构说明  : ASI_RATE_ADPT 寄存器结构定义。地址偏移量:0x030+0x800*(asi_base)，初值:0x00000000，宽度:32
 寄存器说明: 写数据速率匹配
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  ra_en       : 1;  /* bit[0]   : rate adapter使能：
                                                      0：禁止：不对写命令做任何限制；
                                                      1：使能：只有当接收到指定数目（ra_trsfr_wl+1）的写数据transfer个数或收到wlast之后，才允许其对应的写命令被发往后级模块。
                                                      注意：
                                                      1.若使能rate adapter，写命令必须等接收到其对应的写数据之后，才可向后级传输，此特性可避免多个ASI之间写命令和写数据乱序而可能导致的死锁（取决于具体的系统构架）；
                                                      2.此寄存器不可以动态配置，否则可能导致系统挂死。 */
        unsigned int  reserved_0  : 3;  /* bit[1-3] : 保留 */
        unsigned int  ra_trsfr_wl : 4;  /* bit[4-7] : rate adapter水线设置：
                                                      n：当接收到的写数据transfer个数达到n+1个时，其对应的写命令才可以被发往后级处理；
                                                      注意：
                                                      此寄存器可配置的最大值，为ra_fifo的深度减一。 */
        unsigned int  reserved_1  : 24; /* bit[8-31]: 保留 */
    } reg;
} SOC_DMSS_ASI_RATE_ADPT_UNION;
#endif
#define SOC_DMSS_ASI_RATE_ADPT_ra_en_START        (0)
#define SOC_DMSS_ASI_RATE_ADPT_ra_en_END          (0)
#define SOC_DMSS_ASI_RATE_ADPT_ra_trsfr_wl_START  (4)
#define SOC_DMSS_ASI_RATE_ADPT_ra_trsfr_wl_END    (7)


/*****************************************************************************
 结构名    : SOC_DMSS_ASI_RDR_CTRL0_UNION
 结构说明  : ASI_RDR_CTRL0 寄存器结构定义。地址偏移量:0x040+0x800*(asi_base)，初值:0x00000000，宽度:32
 寄存器说明: 读保序控制0
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  rdr_id_match : 32; /* bit[0-31]: 保序匹配ID：
                                                       与rdr_id_mask配合使用，当cmd_id & rdr_id_mask = rdr_id_match时，认为当前cmd_id被成功匹配。成功匹配的ID可参与或不参与（取决于rdr_id_mode）ID保序的监控。
                                                       注意：
                                                       1.实际可配置位宽取决于RTL的ID位宽配置，可通过GLB_RTL_INF寄存器中查询；
                                                       2.此寄存器不可以动态配置，否则可能导致系统挂死。 */
    } reg;
} SOC_DMSS_ASI_RDR_CTRL0_UNION;
#endif
#define SOC_DMSS_ASI_RDR_CTRL0_rdr_id_match_START  (0)
#define SOC_DMSS_ASI_RDR_CTRL0_rdr_id_match_END    (31)


/*****************************************************************************
 结构名    : SOC_DMSS_ASI_RDR_CTRL1_UNION
 结构说明  : ASI_RDR_CTRL1 寄存器结构定义。地址偏移量:0x044+0x800*(asi_base)，初值:0x00000000，宽度:32
 寄存器说明: 读保序控制1
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  rdr_id_mask : 32; /* bit[0-31]: 保序ID掩码：
                                                      与rdr_id_match配合使用，当cmd_id & rdr_id_mask = rdr_id_match时，认为当前cmd_id被成功匹配。成功匹配的ID可参与或不参与（取决于rdr_id_mode）ID保序的监控。
                                                      注意：
                                                      1.实际可配置位宽取决于RTL的ID位宽配置，可通过GLB_RTL_INF寄存器中查询；
                                                      2.此寄存器不可以动态配置，否则可能导致系统挂死。 */
    } reg;
} SOC_DMSS_ASI_RDR_CTRL1_UNION;
#endif
#define SOC_DMSS_ASI_RDR_CTRL1_rdr_id_mask_START  (0)
#define SOC_DMSS_ASI_RDR_CTRL1_rdr_id_mask_END    (31)


/*****************************************************************************
 结构名    : SOC_DMSS_ASI_RDR_CTRL2_UNION
 结构说明  : ASI_RDR_CTRL2 寄存器结构定义。地址偏移量:0x048+0x800*(asi_base)，初值:0x00000000，宽度:32
 寄存器说明: 读保序控制2
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  rdr_id_mode : 1;  /* bit[0]   : 保序ID模式：
                                                      0:匹配成功的ID，参与保序判定；
                                                      1:匹配失败的ID，参与保序判定。 */
        unsigned int  reserved    : 31; /* bit[1-31]: 保留 */
    } reg;
} SOC_DMSS_ASI_RDR_CTRL2_UNION;
#endif
#define SOC_DMSS_ASI_RDR_CTRL2_rdr_id_mode_START  (0)
#define SOC_DMSS_ASI_RDR_CTRL2_rdr_id_mode_END    (0)


/*****************************************************************************
 结构名    : SOC_DMSS_ASI_RBUF_INTLV0_UNION
 结构说明  : ASI_RBUF_INTLV0 寄存器结构定义。地址偏移量:0x060+0x800*(asi_base)，初值:0x00000000，宽度:32
 寄存器说明: RBUF的间插模式配置0
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  intlv_mid_0  : 2;  /* bit[0-1]  : 对MID（只识别最低五位）为0的读命令进行RBUF中数据间插模式的配置：
                                                        0x0，0x1：间插模式一，收到第一个transfer时便提起传输请求（保证首数据最小latency）；
                                                        0x2：间插模式二，收到最后一个transfer时才提起传输请求（保证数据不被间插）；
                                                        0x3：间插模式三，收到可配置的transfer个数或命令所有transfer时便提起传输请求，相关配置请参考传输起始水线ASI_RBUF_TRSFR_WL寄存器（合理配置，可保证到尾数据最小latency）。
                                                        说明：
                                                        间插模式三时，根据传输起始水线配置和数据写入到RBUF的速率：
                                                        1.若能保证数据发送过程中，所有剩余数据都能及时写入RBUF，则传输不会被间插；
                                                        2.若能保证数据发送到最后一个tansfer时，其数据正好被写入RBUF，则能保证尾数据的最小latency（RBUF静态latency为4或5cycles，取决于RTL配置）。 */
        unsigned int  intlv_mid_1  : 2;  /* bit[2-3]  : 同intlv_mid_0配置。 */
        unsigned int  intlv_mid_2  : 2;  /* bit[4-5]  : 同intlv_mid_0配置。 */
        unsigned int  intlv_mid_3  : 2;  /* bit[6-7]  : 同intlv_mid_0配置。 */
        unsigned int  intlv_mid_4  : 2;  /* bit[8-9]  : 同intlv_mid_0配置。 */
        unsigned int  intlv_mid_5  : 2;  /* bit[10-11]: 同intlv_mid_0配置。 */
        unsigned int  intlv_mid_6  : 2;  /* bit[12-13]: 同intlv_mid_0配置。 */
        unsigned int  intlv_mid_7  : 2;  /* bit[14-15]: 同intlv_mid_0配置。 */
        unsigned int  intlv_mid_8  : 2;  /* bit[16-17]: 同intlv_mid_0配置。 */
        unsigned int  intlv_mid_9  : 2;  /* bit[18-19]: 同intlv_mid_0配置。 */
        unsigned int  intlv_mid_10 : 2;  /* bit[20-21]: 同intlv_mid_0配置。 */
        unsigned int  intlv_mid_11 : 2;  /* bit[22-23]: 同intlv_mid_0配置。 */
        unsigned int  intlv_mid_12 : 2;  /* bit[24-25]: 同intlv_mid_0配置。 */
        unsigned int  intlv_mid_13 : 2;  /* bit[26-27]: 同intlv_mid_0配置。 */
        unsigned int  intlv_mid_14 : 2;  /* bit[28-29]: 同intlv_mid_0配置。 */
        unsigned int  intlv_mid_15 : 2;  /* bit[30-31]: 同intlv_mid_0配置。 */
    } reg;
} SOC_DMSS_ASI_RBUF_INTLV0_UNION;
#endif
#define SOC_DMSS_ASI_RBUF_INTLV0_intlv_mid_0_START   (0)
#define SOC_DMSS_ASI_RBUF_INTLV0_intlv_mid_0_END     (1)
#define SOC_DMSS_ASI_RBUF_INTLV0_intlv_mid_1_START   (2)
#define SOC_DMSS_ASI_RBUF_INTLV0_intlv_mid_1_END     (3)
#define SOC_DMSS_ASI_RBUF_INTLV0_intlv_mid_2_START   (4)
#define SOC_DMSS_ASI_RBUF_INTLV0_intlv_mid_2_END     (5)
#define SOC_DMSS_ASI_RBUF_INTLV0_intlv_mid_3_START   (6)
#define SOC_DMSS_ASI_RBUF_INTLV0_intlv_mid_3_END     (7)
#define SOC_DMSS_ASI_RBUF_INTLV0_intlv_mid_4_START   (8)
#define SOC_DMSS_ASI_RBUF_INTLV0_intlv_mid_4_END     (9)
#define SOC_DMSS_ASI_RBUF_INTLV0_intlv_mid_5_START   (10)
#define SOC_DMSS_ASI_RBUF_INTLV0_intlv_mid_5_END     (11)
#define SOC_DMSS_ASI_RBUF_INTLV0_intlv_mid_6_START   (12)
#define SOC_DMSS_ASI_RBUF_INTLV0_intlv_mid_6_END     (13)
#define SOC_DMSS_ASI_RBUF_INTLV0_intlv_mid_7_START   (14)
#define SOC_DMSS_ASI_RBUF_INTLV0_intlv_mid_7_END     (15)
#define SOC_DMSS_ASI_RBUF_INTLV0_intlv_mid_8_START   (16)
#define SOC_DMSS_ASI_RBUF_INTLV0_intlv_mid_8_END     (17)
#define SOC_DMSS_ASI_RBUF_INTLV0_intlv_mid_9_START   (18)
#define SOC_DMSS_ASI_RBUF_INTLV0_intlv_mid_9_END     (19)
#define SOC_DMSS_ASI_RBUF_INTLV0_intlv_mid_10_START  (20)
#define SOC_DMSS_ASI_RBUF_INTLV0_intlv_mid_10_END    (21)
#define SOC_DMSS_ASI_RBUF_INTLV0_intlv_mid_11_START  (22)
#define SOC_DMSS_ASI_RBUF_INTLV0_intlv_mid_11_END    (23)
#define SOC_DMSS_ASI_RBUF_INTLV0_intlv_mid_12_START  (24)
#define SOC_DMSS_ASI_RBUF_INTLV0_intlv_mid_12_END    (25)
#define SOC_DMSS_ASI_RBUF_INTLV0_intlv_mid_13_START  (26)
#define SOC_DMSS_ASI_RBUF_INTLV0_intlv_mid_13_END    (27)
#define SOC_DMSS_ASI_RBUF_INTLV0_intlv_mid_14_START  (28)
#define SOC_DMSS_ASI_RBUF_INTLV0_intlv_mid_14_END    (29)
#define SOC_DMSS_ASI_RBUF_INTLV0_intlv_mid_15_START  (30)
#define SOC_DMSS_ASI_RBUF_INTLV0_intlv_mid_15_END    (31)


/*****************************************************************************
 结构名    : SOC_DMSS_ASI_RBUF_INTLV1_UNION
 结构说明  : ASI_RBUF_INTLV1 寄存器结构定义。地址偏移量:0x064+0x800*(asi_base)，初值:0x00000000，宽度:32
 寄存器说明: RBUF的间插模式配置1
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  intlv_mid_16 : 2;  /* bit[0-1]  : 对MID（只识别最低五位）为16的读命令进行RBUF中数据间插模式的配置：
                                                        0x0，0x1：间插模式一，收到第一个transfer时便提起传输请求（保证首数据最小latency）；
                                                        0x2：间插模式二，收到最后一个transfer时才提起传输请求（保证数据不被间插）；
                                                        0x3：间插模式三，收到可配置的transfer个数或该命令所有transfer时便提起传输请求，相关配置请参考传输起始水线ASI_RBUF_TRSFR_WL寄存器（合理配置，可保证到尾数据最小latency）。
                                                        说明：
                                                        间插模式三时，根据传输起始水线配置和数据写入到RBUF的速率：
                                                        1.若能保证数据发送过程中，所有剩余数据都能及时写入RBUF，则传输不会被间插；
                                                        2.若能保证数据发送到最后一个tansfer时，其数据正好被写入RBUF，则能保证尾数据的最小latency（RBUF静态latency为4或5cycles，取决于RTL配置。 */
        unsigned int  intlv_mid_17 : 2;  /* bit[2-3]  : 同intlv_mid_16配置。 */
        unsigned int  intlv_mid_18 : 2;  /* bit[4-5]  : 同intlv_mid_16配置。 */
        unsigned int  intlv_mid_19 : 2;  /* bit[6-7]  : 同intlv_mid_16配置。 */
        unsigned int  intlv_mid_20 : 2;  /* bit[8-9]  : 同intlv_mid_16配置。 */
        unsigned int  intlv_mid_21 : 2;  /* bit[10-11]: 同intlv_mid_16配置。 */
        unsigned int  intlv_mid_22 : 2;  /* bit[12-13]: 同intlv_mid_16配置。 */
        unsigned int  intlv_mid_23 : 2;  /* bit[14-15]: 同intlv_mid_16配置。 */
        unsigned int  intlv_mid_24 : 2;  /* bit[16-17]: 同intlv_mid_16配置。 */
        unsigned int  intlv_mid_25 : 2;  /* bit[18-19]: 同intlv_mid_16配置。 */
        unsigned int  intlv_mid_26 : 2;  /* bit[20-21]: 同intlv_mid_16配置。 */
        unsigned int  intlv_mid_27 : 2;  /* bit[22-23]: 同intlv_mid_16配置。 */
        unsigned int  intlv_mid_28 : 2;  /* bit[24-25]: 同intlv_mid_16配置。 */
        unsigned int  intlv_mid_29 : 2;  /* bit[26-27]: 同intlv_mid_16配置。 */
        unsigned int  intlv_mid_30 : 2;  /* bit[28-29]: 同intlv_mid_16配置。 */
        unsigned int  intlv_mid_31 : 2;  /* bit[30-31]: 同intlv_mid_16配置。 */
    } reg;
} SOC_DMSS_ASI_RBUF_INTLV1_UNION;
#endif
#define SOC_DMSS_ASI_RBUF_INTLV1_intlv_mid_16_START  (0)
#define SOC_DMSS_ASI_RBUF_INTLV1_intlv_mid_16_END    (1)
#define SOC_DMSS_ASI_RBUF_INTLV1_intlv_mid_17_START  (2)
#define SOC_DMSS_ASI_RBUF_INTLV1_intlv_mid_17_END    (3)
#define SOC_DMSS_ASI_RBUF_INTLV1_intlv_mid_18_START  (4)
#define SOC_DMSS_ASI_RBUF_INTLV1_intlv_mid_18_END    (5)
#define SOC_DMSS_ASI_RBUF_INTLV1_intlv_mid_19_START  (6)
#define SOC_DMSS_ASI_RBUF_INTLV1_intlv_mid_19_END    (7)
#define SOC_DMSS_ASI_RBUF_INTLV1_intlv_mid_20_START  (8)
#define SOC_DMSS_ASI_RBUF_INTLV1_intlv_mid_20_END    (9)
#define SOC_DMSS_ASI_RBUF_INTLV1_intlv_mid_21_START  (10)
#define SOC_DMSS_ASI_RBUF_INTLV1_intlv_mid_21_END    (11)
#define SOC_DMSS_ASI_RBUF_INTLV1_intlv_mid_22_START  (12)
#define SOC_DMSS_ASI_RBUF_INTLV1_intlv_mid_22_END    (13)
#define SOC_DMSS_ASI_RBUF_INTLV1_intlv_mid_23_START  (14)
#define SOC_DMSS_ASI_RBUF_INTLV1_intlv_mid_23_END    (15)
#define SOC_DMSS_ASI_RBUF_INTLV1_intlv_mid_24_START  (16)
#define SOC_DMSS_ASI_RBUF_INTLV1_intlv_mid_24_END    (17)
#define SOC_DMSS_ASI_RBUF_INTLV1_intlv_mid_25_START  (18)
#define SOC_DMSS_ASI_RBUF_INTLV1_intlv_mid_25_END    (19)
#define SOC_DMSS_ASI_RBUF_INTLV1_intlv_mid_26_START  (20)
#define SOC_DMSS_ASI_RBUF_INTLV1_intlv_mid_26_END    (21)
#define SOC_DMSS_ASI_RBUF_INTLV1_intlv_mid_27_START  (22)
#define SOC_DMSS_ASI_RBUF_INTLV1_intlv_mid_27_END    (23)
#define SOC_DMSS_ASI_RBUF_INTLV1_intlv_mid_28_START  (24)
#define SOC_DMSS_ASI_RBUF_INTLV1_intlv_mid_28_END    (25)
#define SOC_DMSS_ASI_RBUF_INTLV1_intlv_mid_29_START  (26)
#define SOC_DMSS_ASI_RBUF_INTLV1_intlv_mid_29_END    (27)
#define SOC_DMSS_ASI_RBUF_INTLV1_intlv_mid_30_START  (28)
#define SOC_DMSS_ASI_RBUF_INTLV1_intlv_mid_30_END    (29)
#define SOC_DMSS_ASI_RBUF_INTLV1_intlv_mid_31_START  (30)
#define SOC_DMSS_ASI_RBUF_INTLV1_intlv_mid_31_END    (31)


/*****************************************************************************
 结构名    : SOC_DMSS_ASI_QOS_CTRL_UNION
 结构说明  : ASI_QOS_CTRL 寄存器结构定义。地址偏移量:0x100+0x800*(asi_base)，初值:0x00000000，宽度:32
 寄存器说明: 命令优先级控制
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  pri_push_en      : 1;  /* bit[0]    : 端口优先级传递使能：
                                                            0：禁止；
                                                            1：使能。
                                                            注意：
                                                            优先级传递使能后，将命令流水线上以及外部送入的多个命令中的最高优先级，传递给当前正参与端口仲裁的命令，以帮助其快速赢得仲裁。是否改变被传递命令的自身优先级取决于配置项arb_pri_use。 */
        unsigned int  push_qos_en      : 1;  /* bit[1]    : Pushed优先级传递使能：
                                                            0：禁止；
                                                            1：使能。
                                                            注意：
                                                            1.NOC总线的Pressure信号，可在命令总线反压时传递优先级，参与DMSS内部的优先级传递；
                                                            2.当pri_push_en==1时，此寄存器有效。 */
        unsigned int  hurry_qos_en     : 1;  /* bit[2]    : Hurry优先级传递使能：
                                                            0：禁止；
                                                            1：使能。
                                                            注意：
                                                            1.NOC总线的Hurry信号，可在任何时刻传递优先级，参与DMSS内部的优先级传递；
                                                            2.当pri_push_en==1时，此寄存器有效。 */
        unsigned int  arb_pri_use      : 1;  /* bit[3]    : 使用仲裁优先级作为命令自身的优先级：
                                                            0：禁止：命令自身优先级只来自于AxQOS信号的映射，或regulator中配置的优先级；
                                                            1：使能：除了上述来源之外，命令自身优先级还可以来自优先级传递和优先级自适应等方式得到的优先级。 */
        unsigned int  rw_arb_mode      : 1;  /* bit[4]    : 同一端口内读写命令仲裁模式：
                                                            0：基于命令读写类型：
                                                             a.先到先仲裁；
                                                             b.同时到达（或被同时被反压）时，按照先读命令后写命令的顺序轮流仲裁；
                                                            1：基于命令优先级：
                                                             a.先到先仲裁；
                                                             b.同时到达（或被同时被反压）时，则按照命令优先级仲裁；
                                                             c.若优先级相同，则按照LRU原则仲裁给上一次未获得仲裁的命令。 */
        unsigned int  reserved_0       : 3;  /* bit[5-7]  : 保留 */
        unsigned int  rw_arb_dis       : 1;  /* bit[8]    : 读写命令仲裁禁止：
                                                            0：正常进行读写仲裁；
                                                            1：禁止读写仲裁（反压AXI总线的读写命令）。 */
        unsigned int  reserved_1       : 3;  /* bit[9-11] : 保留 */
        unsigned int  rd_wrap_split_en : 1;  /* bit[12]   : wrap读命令拆分使能：
                                                            0：不拆分，由DDRC自动完成wrap数据卷绕；
                                                            1：拆分，从地址卷绕上边界处将命令拆分成两个INCR命令。 */
        unsigned int  reserved_2       : 3;  /* bit[13-15]: 保留 */
        unsigned int  dcq_prilvl_en    : 1;  /* bit[16]   : DDRC命令队列中优先级控制水线的使能：
                                                            0：忽略寄存器GLB_DCQ_PRILVL0/1中的优先级水线；
                                                            1：依据GLB_DCQ_PRILVL0/1中的优先级水线对低优先级命令进行流量控制（基于limter2）。 */
        unsigned int  reserved_3       : 15; /* bit[17-31]: 保留 */
    } reg;
} SOC_DMSS_ASI_QOS_CTRL_UNION;
#endif
#define SOC_DMSS_ASI_QOS_CTRL_pri_push_en_START       (0)
#define SOC_DMSS_ASI_QOS_CTRL_pri_push_en_END         (0)
#define SOC_DMSS_ASI_QOS_CTRL_push_qos_en_START       (1)
#define SOC_DMSS_ASI_QOS_CTRL_push_qos_en_END         (1)
#define SOC_DMSS_ASI_QOS_CTRL_hurry_qos_en_START      (2)
#define SOC_DMSS_ASI_QOS_CTRL_hurry_qos_en_END        (2)
#define SOC_DMSS_ASI_QOS_CTRL_arb_pri_use_START       (3)
#define SOC_DMSS_ASI_QOS_CTRL_arb_pri_use_END         (3)
#define SOC_DMSS_ASI_QOS_CTRL_rw_arb_mode_START       (4)
#define SOC_DMSS_ASI_QOS_CTRL_rw_arb_mode_END         (4)
#define SOC_DMSS_ASI_QOS_CTRL_rw_arb_dis_START        (8)
#define SOC_DMSS_ASI_QOS_CTRL_rw_arb_dis_END          (8)
#define SOC_DMSS_ASI_QOS_CTRL_rd_wrap_split_en_START  (12)
#define SOC_DMSS_ASI_QOS_CTRL_rd_wrap_split_en_END    (12)
#define SOC_DMSS_ASI_QOS_CTRL_dcq_prilvl_en_START     (16)
#define SOC_DMSS_ASI_QOS_CTRL_dcq_prilvl_en_END       (16)


/*****************************************************************************
 结构名    : SOC_DMSS_ASI_QOS_WRPRI_UNION
 结构说明  : ASI_QOS_WRPRI 寄存器结构定义。地址偏移量:0x104+0x800*(asi_base)，初值:0x76543210，宽度:32
 寄存器说明: 写命令优先级映射表
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  wr_pri0  : 3;  /* bit[0-2]  : 当awqos[2:0]==0时，写命令的优先级配置值：
                                                    0x0：最低优先级；
                                                    ……
                                                    0x7：最高优先级。 */
        unsigned int  reserved_0: 1;  /* bit[3]    : 保留 */
        unsigned int  wr_pri1  : 3;  /* bit[4-6]  : 类同wr_pri0的配置。 */
        unsigned int  reserved_1: 1;  /* bit[7]    : 保留 */
        unsigned int  wr_pri2  : 3;  /* bit[8-10] : 类同wr_pri0的配置。 */
        unsigned int  reserved_2: 1;  /* bit[11]   : 保留 */
        unsigned int  wr_pri3  : 3;  /* bit[12-14]: 类同wr_pri0的配置。 */
        unsigned int  reserved_3: 1;  /* bit[15]   : 保留 */
        unsigned int  wr_pri4  : 3;  /* bit[16-18]: 类同wr_pri0的配置。 */
        unsigned int  reserved_4: 1;  /* bit[19]   : 保留 */
        unsigned int  wr_pri5  : 3;  /* bit[20-22]: 类同wr_pri0的配置。 */
        unsigned int  reserved_5: 1;  /* bit[23]   : 保留 */
        unsigned int  wr_pri6  : 3;  /* bit[24-26]: 类同wr_pri0的配置。 */
        unsigned int  reserved_6: 1;  /* bit[27]   : 保留 */
        unsigned int  wr_pri7  : 3;  /* bit[28-30]: 类同wr_pri0的配置。 */
        unsigned int  reserved_7: 1;  /* bit[31]   : 保留 */
    } reg;
} SOC_DMSS_ASI_QOS_WRPRI_UNION;
#endif
#define SOC_DMSS_ASI_QOS_WRPRI_wr_pri0_START   (0)
#define SOC_DMSS_ASI_QOS_WRPRI_wr_pri0_END     (2)
#define SOC_DMSS_ASI_QOS_WRPRI_wr_pri1_START   (4)
#define SOC_DMSS_ASI_QOS_WRPRI_wr_pri1_END     (6)
#define SOC_DMSS_ASI_QOS_WRPRI_wr_pri2_START   (8)
#define SOC_DMSS_ASI_QOS_WRPRI_wr_pri2_END     (10)
#define SOC_DMSS_ASI_QOS_WRPRI_wr_pri3_START   (12)
#define SOC_DMSS_ASI_QOS_WRPRI_wr_pri3_END     (14)
#define SOC_DMSS_ASI_QOS_WRPRI_wr_pri4_START   (16)
#define SOC_DMSS_ASI_QOS_WRPRI_wr_pri4_END     (18)
#define SOC_DMSS_ASI_QOS_WRPRI_wr_pri5_START   (20)
#define SOC_DMSS_ASI_QOS_WRPRI_wr_pri5_END     (22)
#define SOC_DMSS_ASI_QOS_WRPRI_wr_pri6_START   (24)
#define SOC_DMSS_ASI_QOS_WRPRI_wr_pri6_END     (26)
#define SOC_DMSS_ASI_QOS_WRPRI_wr_pri7_START   (28)
#define SOC_DMSS_ASI_QOS_WRPRI_wr_pri7_END     (30)


/*****************************************************************************
 结构名    : SOC_DMSS_ASI_QOS_RDPRI_UNION
 结构说明  : ASI_QOS_RDPRI 寄存器结构定义。地址偏移量:0x108+0x800*(asi_base)，初值:0x76543210，宽度:32
 寄存器说明: 读命令优先级映射表
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  rd_pri0  : 3;  /* bit[0-2]  : 当arqos[2:0]==0时，读命令的优先级配置值：
                                                    0x0：最低优先级；
                                                    ……
                                                    0x7：最高优先级。 */
        unsigned int  reserved_0: 1;  /* bit[3]    : 保留 */
        unsigned int  rd_pri1  : 3;  /* bit[4-6]  : 类同rd_pri0的配置。 */
        unsigned int  reserved_1: 1;  /* bit[7]    : 保留 */
        unsigned int  rd_pri2  : 3;  /* bit[8-10] : 类同rd_pri0的配置。 */
        unsigned int  reserved_2: 1;  /* bit[11]   : 保留 */
        unsigned int  rd_pri3  : 3;  /* bit[12-14]: 类同rd_pri0的配置。 */
        unsigned int  reserved_3: 1;  /* bit[15]   : 保留 */
        unsigned int  rd_pri4  : 3;  /* bit[16-18]: 类同rd_pri0的配置。 */
        unsigned int  reserved_4: 1;  /* bit[19]   : 保留 */
        unsigned int  rd_pri5  : 3;  /* bit[20-22]: 类同rd_pri0的配置。 */
        unsigned int  reserved_5: 1;  /* bit[23]   : 保留 */
        unsigned int  rd_pri6  : 3;  /* bit[24-26]: 类同rd_pri0的配置。 */
        unsigned int  reserved_6: 1;  /* bit[27]   : 保留 */
        unsigned int  rd_pri7  : 3;  /* bit[28-30]: 类同rd_pri0的配置。 */
        unsigned int  reserved_7: 1;  /* bit[31]   : 保留 */
    } reg;
} SOC_DMSS_ASI_QOS_RDPRI_UNION;
#endif
#define SOC_DMSS_ASI_QOS_RDPRI_rd_pri0_START   (0)
#define SOC_DMSS_ASI_QOS_RDPRI_rd_pri0_END     (2)
#define SOC_DMSS_ASI_QOS_RDPRI_rd_pri1_START   (4)
#define SOC_DMSS_ASI_QOS_RDPRI_rd_pri1_END     (6)
#define SOC_DMSS_ASI_QOS_RDPRI_rd_pri2_START   (8)
#define SOC_DMSS_ASI_QOS_RDPRI_rd_pri2_END     (10)
#define SOC_DMSS_ASI_QOS_RDPRI_rd_pri3_START   (12)
#define SOC_DMSS_ASI_QOS_RDPRI_rd_pri3_END     (14)
#define SOC_DMSS_ASI_QOS_RDPRI_rd_pri4_START   (16)
#define SOC_DMSS_ASI_QOS_RDPRI_rd_pri4_END     (18)
#define SOC_DMSS_ASI_QOS_RDPRI_rd_pri5_START   (20)
#define SOC_DMSS_ASI_QOS_RDPRI_rd_pri5_END     (22)
#define SOC_DMSS_ASI_QOS_RDPRI_rd_pri6_START   (24)
#define SOC_DMSS_ASI_QOS_RDPRI_rd_pri6_END     (26)
#define SOC_DMSS_ASI_QOS_RDPRI_rd_pri7_START   (28)
#define SOC_DMSS_ASI_QOS_RDPRI_rd_pri7_END     (30)


/*****************************************************************************
 结构名    : SOC_DMSS_ASI_QOS_ADPT_UNION
 结构说明  : ASI_QOS_ADPT 寄存器结构定义。地址偏移量:0x10C+0x800*(asi_base)，初值:0x00000000，宽度:32
 寄存器说明: 命令优先级自适应周期映射表
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  rd_adpt_low  : 4;  /* bit[0-3]  : 读命令优先级自适应周期配置（低档位）：
                                                        0x0：禁止优先级自适应功能；
                                                        0x1～0xF：N×16个时钟周期。
                                                        说明：
                                                        每当自适应周期到达后，命令优先级自动提升一级，直到提升至次最高优先级（优先级6）。 */
        unsigned int  rd_adpt_lvl  : 3;  /* bit[4-6]  : 读命令优先级自适应周期配置水线：
                                                        0x0～0x6：命令优先级高于此水线时，使用高档位配置，否则使用低档位配置；
                                                        0x7：reserved。
                                                        举例：
                                                        0x3：优先级4~5的读命令使用rd_pri_adpt_high，优先级0～3的读命令使用rd_pri_adpt_low。 */
        unsigned int  reserved_0   : 1;  /* bit[7]    : 保留 */
        unsigned int  rd_adpt_high : 4;  /* bit[8-11] : 读命令优先级自适应周期配置（高档位）：
                                                        同rd_pri_adpt_low的配置。 */
        unsigned int  reserved_1   : 4;  /* bit[12-15]: 保留 */
        unsigned int  wr_adpt_low  : 4;  /* bit[16-19]: 写命令优先级自适应周期配置（低档位）：
                                                        同rd_pri_adpt_low的配置。 */
        unsigned int  wr_adpt_lvl  : 3;  /* bit[20-22]: 写命令优先级自适应周期配置水线：
                                                        同rd_pri_adpt_lvl的配置。 */
        unsigned int  reserved_2   : 1;  /* bit[23]   : 保留 */
        unsigned int  wr_adpt_high : 4;  /* bit[24-27]: 写命令优先级自适应周期配置（高档位）：
                                                        同rd_pri_adpt_low的配置。 */
        unsigned int  reserved_3   : 4;  /* bit[28-31]: 保留 */
    } reg;
} SOC_DMSS_ASI_QOS_ADPT_UNION;
#endif
#define SOC_DMSS_ASI_QOS_ADPT_rd_adpt_low_START   (0)
#define SOC_DMSS_ASI_QOS_ADPT_rd_adpt_low_END     (3)
#define SOC_DMSS_ASI_QOS_ADPT_rd_adpt_lvl_START   (4)
#define SOC_DMSS_ASI_QOS_ADPT_rd_adpt_lvl_END     (6)
#define SOC_DMSS_ASI_QOS_ADPT_rd_adpt_high_START  (8)
#define SOC_DMSS_ASI_QOS_ADPT_rd_adpt_high_END    (11)
#define SOC_DMSS_ASI_QOS_ADPT_wr_adpt_low_START   (16)
#define SOC_DMSS_ASI_QOS_ADPT_wr_adpt_low_END     (19)
#define SOC_DMSS_ASI_QOS_ADPT_wr_adpt_lvl_START   (20)
#define SOC_DMSS_ASI_QOS_ADPT_wr_adpt_lvl_END     (22)
#define SOC_DMSS_ASI_QOS_ADPT_wr_adpt_high_START  (24)
#define SOC_DMSS_ASI_QOS_ADPT_wr_adpt_high_END    (27)


/*****************************************************************************
 结构名    : SOC_DMSS_ASI_QOS_LATENCY_UNION
 结构说明  : ASI_QOS_LATENCY 寄存器结构定义。地址偏移量:0x110+0x800*(asi_base)，初值:0x00000000，宽度:32
 寄存器说明: 读命令的latency控制
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  lat_target       : 12; /* bit[0-11] : 目标平均latency，单位为clk cycle。
                                                            说明：
                                                            将通过优先级调整和限制所有ASI的低优先级命令流量的方式，使得平均读latency逼近目标平均latency。 */
        unsigned int  lat_factor       : 3;  /* bit[12-14]: 优先级调整速率：
                                                            0~7：数值越大，优先级调整速率越缓慢。相邻两档配置值相比，同等条件下（相同读outstanding）优先级调整速率相差一倍。
                                                            说明：
                                                            当latency超过（未达到）设定的目标平均latency时，读命令优先级会逐级调高（调低），lat_factor决定了优先级连续的逐级调高（调低）时的速率。
                                                            优先级调整速率除了和此配置项有关外，还受到当前读outstanding的影响：outstanding越小，优先级调整速率越缓慢。 */
        unsigned int  reserved_0       : 1;  /* bit[15]   : 保留 */
        unsigned int  lat_pri_min      : 3;  /* bit[16-18]: 优先级的调整下限。 */
        unsigned int  reserved_1       : 1;  /* bit[19]   : 保留 */
        unsigned int  lat_pri_max      : 3;  /* bit[20-22]: 优先级的调整上限。 */
        unsigned int  reserved_2       : 1;  /* bit[23]   : 保留 */
        unsigned int  lat_flux_req_dly : 4;  /* bit[24-27]: 低优先级命令限流的功能的触发延迟周期：
                                                            n：(n+1)*(2^(lat_factor+2))个时钟周期
                                                            举例：
                                                            若lat_factor配为3，n配为5，则触发延迟周期为（5+1）*（2^(3+2)）=196。
                                                            说明：
                                                            若读命令优先级已被调整到上限值，且延迟周期后还不能达到目标latency，则触发低优先级命令的限流功能。 */
        unsigned int  lat_flux_req_en  : 1;  /* bit[28]   : 限制所有ASI端口的低优先级命令流量的功能使能：
                                                            0：禁止；
                                                            1：使能。
                                                            说明：
                                                            当读命令优先级被调整到上限值时，若还不能达到目标latency，则可进一步限制所有ASI的低优先级命令流量。
                                                            流量限制功能复用了外部master的流控功能，需要配置相关的寄存器GLB_DCQ_MST和ASI_QOS_LMTR2。
                                                            注意：
                                                            1.需要在RTL的define配置文件中，将当前ASI分配到某组外部master流控功能上，否则此功能无效；
                                                            2.此寄存器只能静态配置。 */
        unsigned int  lat_quiesce      : 1;  /* bit[29]   : Sets the mode for bandwidth regulation:
                                                            0：Normal mode.The QoS value is stable when the master is idle.
                                                            1：Quiesce High mode.The QoS value tends to the maximum when the master is idle。 */
        unsigned int  lat_mode         : 1;  /* bit[30]   : Configures the mode of the QoS value regulator for read transactions:
                                                            0：Latency mode.
                                                            1：Period mode, for bandwidth regulation。 */
        unsigned int  lat_en           : 1;  /* bit[31]   : latency控制使能：
                                                            0：禁止；
                                                            1：使能。
                                                            说明：
                                                            使能后，可统计读的命令平均latency，并通过自动调整命令的优先级（在上下限范围内调整，调整速率可配置）和限制所有ASI端口的低优先级命令流量等方式，使得读命令平均latency尽可能的逼近目标latency。
                                                            注意：
                                                            1.若使能此功能，则读命令的Regulator和优先级映射功能无效；
                                                            (相关寄存器为ASI_QOS_RGLR0/ASI_QOS_RGLR0_PRI/ASI_QOS_RDPRI)
                                                            2.此寄存器只能静态配置。 */
    } reg;
} SOC_DMSS_ASI_QOS_LATENCY_UNION;
#endif
#define SOC_DMSS_ASI_QOS_LATENCY_lat_target_START        (0)
#define SOC_DMSS_ASI_QOS_LATENCY_lat_target_END          (11)
#define SOC_DMSS_ASI_QOS_LATENCY_lat_factor_START        (12)
#define SOC_DMSS_ASI_QOS_LATENCY_lat_factor_END          (14)
#define SOC_DMSS_ASI_QOS_LATENCY_lat_pri_min_START       (16)
#define SOC_DMSS_ASI_QOS_LATENCY_lat_pri_min_END         (18)
#define SOC_DMSS_ASI_QOS_LATENCY_lat_pri_max_START       (20)
#define SOC_DMSS_ASI_QOS_LATENCY_lat_pri_max_END         (22)
#define SOC_DMSS_ASI_QOS_LATENCY_lat_flux_req_dly_START  (24)
#define SOC_DMSS_ASI_QOS_LATENCY_lat_flux_req_dly_END    (27)
#define SOC_DMSS_ASI_QOS_LATENCY_lat_flux_req_en_START   (28)
#define SOC_DMSS_ASI_QOS_LATENCY_lat_flux_req_en_END     (28)
#define SOC_DMSS_ASI_QOS_LATENCY_lat_quiesce_START       (29)
#define SOC_DMSS_ASI_QOS_LATENCY_lat_quiesce_END         (29)
#define SOC_DMSS_ASI_QOS_LATENCY_lat_mode_START          (30)
#define SOC_DMSS_ASI_QOS_LATENCY_lat_mode_END            (30)
#define SOC_DMSS_ASI_QOS_LATENCY_lat_en_START            (31)
#define SOC_DMSS_ASI_QOS_LATENCY_lat_en_END              (31)


/*****************************************************************************
 结构名    : SOC_DMSS_ASI_QOS_RGLR0_UNION
 结构说明  : ASI_QOS_RGLR0 寄存器结构定义。地址偏移量:0x120+0x800*(asi_base)，初值:0x00000000，宽度:32
 寄存器说明: 带宽优先级控制0
            （可单独控制读命令优先级，或同时控制读写命令优先级）
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  rglr_saturation : 14; /* bit[0-13] : 带宽容限：
                                                           配置值=带宽容限(B)/16；
                                                           说明：
                                                           可以将本带宽控制方式等效成基于滑动窗口的流量控制，带宽容限决定了滑窗宽度以及滑窗内的允许流量：带宽容限(B)/设定带宽水线(B/Hz)=滑窗宽度（cycle）。即在配置的设定带宽固定的情况下，带宽容限越大，滑窗越宽，对控制前的瞬时带宽变化越不敏感，长时间控制后的平均带宽也越接近配置的期望带宽，但控制后的瞬时带宽的变化也可能会越剧烈。
                                                           注意：regulator使能时，不可以配置为0。 */
        unsigned int  reserved_0      : 2;  /* bit[14-15]: 保留 */
        unsigned int  rglr_bandwidth  : 13; /* bit[16-28]: 设定期望带宽：
                                                           配置值=设定期望带宽(B/Hz)*256=期望带宽(MB/s)/工作频率（MHz）*256
                                                           例如：工作频率为400MHz，当前端口的设定带宽为1400MB/s，则带宽配置值为1400/400*256=896=0x380
                                                           说明：
                                                           乘256的目的是保留设定期望带宽的高8位小数。 */
        unsigned int  reserved_1      : 1;  /* bit[29]   : 保留 */
        unsigned int  rglr_type       : 1;  /* bit[30]   : 带宽优先级控制的命令类型：
                                                           0：只控制读命令优先级；
                                                           1：同时控制读写命令优先级；
                                                           注意：
                                                           当配置为“同时控制读写命令优先级”时，ASI_QOS_RGLR1将被自动禁止使用。 */
        unsigned int  rglr_en         : 1;  /* bit[31]   : regulator使能：
                                                           0：禁止；
                                                           1：使能。
                                                           注意：
                                                           若使能Regulator功能，则优先级映射功能无效
                                                           (相关寄存器为ASI_QOS_WRPRI/ASI_QOS_RDPRI)。 */
    } reg;
} SOC_DMSS_ASI_QOS_RGLR0_UNION;
#endif
#define SOC_DMSS_ASI_QOS_RGLR0_rglr_saturation_START  (0)
#define SOC_DMSS_ASI_QOS_RGLR0_rglr_saturation_END    (13)
#define SOC_DMSS_ASI_QOS_RGLR0_rglr_bandwidth_START   (16)
#define SOC_DMSS_ASI_QOS_RGLR0_rglr_bandwidth_END     (28)
#define SOC_DMSS_ASI_QOS_RGLR0_rglr_type_START        (30)
#define SOC_DMSS_ASI_QOS_RGLR0_rglr_type_END          (30)
#define SOC_DMSS_ASI_QOS_RGLR0_rglr_en_START          (31)
#define SOC_DMSS_ASI_QOS_RGLR0_rglr_en_END            (31)


/*****************************************************************************
 结构名    : SOC_DMSS_ASI_QOS_RGLR0_PRI_UNION
 结构说明  : ASI_QOS_RGLR0_PRI 寄存器结构定义。地址偏移量:0x124+0x800*(asi_base)，初值:0x00000000，宽度:32
 寄存器说明: 带宽配置优先级0
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  rglr_pri0 : 3;  /* bit[0-2]  : 当带宽未达到ASI_QOS_RGLR0的配置带宽时，命令的优先级配置值：
                                                     0x0：最低优先级；
                                                     ……
                                                     0x7：最高优先级。
                                                     注意：
                                                     若rglr_type配置为“只控制读命令优先级”，则只改变写命令优先级；若配置为“同时控制读写命令优先级”，则同时改变读和写命令优先级。 */
        unsigned int  reserved_0: 5;  /* bit[3-7]  : 保留 */
        unsigned int  rglr_pri1 : 3;  /* bit[8-10] : 当带宽达到ASI_QOS_RGLR0的配置带宽时，命令的优先级配置值：
                                                     0x0：最低优先级；
                                                     ……
                                                     0x7：最高优先级。
                                                     注意：
                                                     若rglr_type配置为“只控制读命令优先级”，则只改变写命令优先级；若配置为“同时控制读写命令优先级”，则同时改变读和写命令优先级。 */
        unsigned int  reserved_1: 21; /* bit[11-31]: 保留 */
    } reg;
} SOC_DMSS_ASI_QOS_RGLR0_PRI_UNION;
#endif
#define SOC_DMSS_ASI_QOS_RGLR0_PRI_rglr_pri0_START  (0)
#define SOC_DMSS_ASI_QOS_RGLR0_PRI_rglr_pri0_END    (2)
#define SOC_DMSS_ASI_QOS_RGLR0_PRI_rglr_pri1_START  (8)
#define SOC_DMSS_ASI_QOS_RGLR0_PRI_rglr_pri1_END    (10)


/*****************************************************************************
 结构名    : SOC_DMSS_ASI_QOS_RGLR1_UNION
 结构说明  : ASI_QOS_RGLR1 寄存器结构定义。地址偏移量:0x128+0x800*(asi_base)，初值:0x00000000，宽度:32
 寄存器说明: 带宽优先级控制1
            （只可单独控制写命令优先级）
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  rglr_saturation : 14; /* bit[0-13] : 带宽容限：
                                                           配置值=带宽容限(B)/16；
                                                           说明：
                                                           可以将本带宽控制方式等效成基于滑动窗口的流量控制，带宽容限决定了滑窗宽度以及滑窗内的允许流量：带宽容限(B)/设定带宽水线(B/Hz)=滑窗宽度（cycle）。即在配置的设定带宽固定的情况下，带宽容限越大，滑窗越宽，对控制前的瞬时带宽变化越不敏感，长时间控制后的平均带宽也越接近配置的期望带宽，但控制后的瞬时带宽的变化也可能会越剧烈。
                                                           注意：regulator使能时，不可以配置为0。 */
        unsigned int  reserved_0      : 2;  /* bit[14-15]: 保留 */
        unsigned int  rglr_bandwidth  : 13; /* bit[16-28]: 设定期望带宽：
                                                           配置值=设定期望带宽(B/Hz)*256=期望带宽(MB/s)/工作频率（MHz）*256
                                                           例如：工作频率为400MHz，当前端口的设定带宽为1400MB/s，则带宽配置值为1400/400*256=896=0x380
                                                           说明：
                                                           乘256的目的是保留设定期望带宽的高8位小数。 */
        unsigned int  reserved_1      : 2;  /* bit[29-30]: 保留 */
        unsigned int  rglr_en         : 1;  /* bit[31]   : regulator使能：
                                                           0：禁止；
                                                           1：使能。
                                                           注意：
                                                           1.ASI_QOS_RGLR1只能控制写带宽；
                                                           2.当ASI_QOS_RGLR0配置为“同时控制读写命令带宽”时，ASI_QOS_RGLR1将被自动禁止使用。
                                                           3.注意：
                                                           若使能Regulator功能，则优先级映射功能无效
                                                           (相关寄存器为ASI_QOS_WRPRI)。 */
    } reg;
} SOC_DMSS_ASI_QOS_RGLR1_UNION;
#endif
#define SOC_DMSS_ASI_QOS_RGLR1_rglr_saturation_START  (0)
#define SOC_DMSS_ASI_QOS_RGLR1_rglr_saturation_END    (13)
#define SOC_DMSS_ASI_QOS_RGLR1_rglr_bandwidth_START   (16)
#define SOC_DMSS_ASI_QOS_RGLR1_rglr_bandwidth_END     (28)
#define SOC_DMSS_ASI_QOS_RGLR1_rglr_en_START          (31)
#define SOC_DMSS_ASI_QOS_RGLR1_rglr_en_END            (31)


/*****************************************************************************
 结构名    : SOC_DMSS_ASI_QOS_RGLR1_PRI_UNION
 结构说明  : ASI_QOS_RGLR1_PRI 寄存器结构定义。地址偏移量:0x12C+0x800*(asi_base)，初值:0x00000000，宽度:32
 寄存器说明: 带宽配置优先级1
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  rglr_pri0 : 3;  /* bit[0-2]  : 当带宽未达到ASI_QOS_RGLR0的配置带宽时，写命令的优先级配置值：
                                                     0x0：最低优先级；
                                                     ……
                                                     0x7：最高优先级。 */
        unsigned int  reserved_0: 5;  /* bit[3-7]  : 保留 */
        unsigned int  rglr_pri1 : 3;  /* bit[8-10] : 当带宽达到ASI_QOS_RGLR0的配置带宽时，写命令的优先级配置值：
                                                     0x0：最低优先级；
                                                     ……
                                                     0x7：最高优先级。 */
        unsigned int  reserved_1: 21; /* bit[11-31]: 保留 */
    } reg;
} SOC_DMSS_ASI_QOS_RGLR1_PRI_UNION;
#endif
#define SOC_DMSS_ASI_QOS_RGLR1_PRI_rglr_pri0_START  (0)
#define SOC_DMSS_ASI_QOS_RGLR1_PRI_rglr_pri0_END    (2)
#define SOC_DMSS_ASI_QOS_RGLR1_PRI_rglr_pri1_START  (8)
#define SOC_DMSS_ASI_QOS_RGLR1_PRI_rglr_pri1_END    (10)


/*****************************************************************************
 结构名    : SOC_DMSS_ASI_QOS_LMTR0_UNION
 结构说明  : ASI_QOS_LMTR0 寄存器结构定义。地址偏移量:0x140+0x800*(asi_base)，初值:0x00000000，宽度:32
 寄存器说明: 带宽限流控制0
            （可单独控制读带宽，或同时控制读写总带宽）
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  lmtr_saturation : 14; /* bit[0-13] : 带宽容限：
                                                           配置值=带宽容限(B)/16；
                                                           说明：
                                                           可以将本带宽控制方式等效成基于滑动窗口的流量控制，带宽容限决定了滑窗宽度以及滑窗内的允许流量：带宽容限(B)/允许平均带宽(B/Hz)=滑窗宽度（cycle）。即在配置的允许平均带宽固定的情况下，带宽容限越大，滑窗越宽，对控制前的瞬时带宽变化越不敏感，长时间控制后的平均带宽也越接近配置的允许平均带宽，但控制后的瞬时带宽的变化也可能会越剧烈。
                                                           例如，当允许带宽为理论带宽的1/3时（为便于说明，假设一个命令对应一拍数据，数据总线位宽16B。带宽控制实际是控制命令而非数据）：若带宽容限配置值为1，则任意连续的3拍内最多允许1拍数据通过；若带宽容限配置值为2，则任意连续的6拍内最多允许2拍数据通过，而这2拍数据就可能连续通过；以此类推。（由于硬件延迟等因素，建议带宽容限的有效配置值至少为2）
                                                           注意：带宽限流使能时，不可以配置为0。 */
        unsigned int  reserved_0      : 2;  /* bit[14-15]: 保留 */
        unsigned int  lmtr_bandwidth  : 13; /* bit[16-28]: 允许平均带宽：
                                                           配置值=允许平均带宽(B/Hz)*256=允许带宽(MB/s)/工作频率（MHz）*256
                                                           例如：工作频率为400MHz，当前端口的允许带宽为1400MB/s，则带宽配置值为1400/400*256=896=0x380
                                                           说明：
                                                           1.乘256的目的是保留允许平均带宽的高8位小数；
                                                           2.控制后的瞬时带宽可能会超过允许带宽，超过的范围取决于带宽容限的配置；
                                                           3.控制后的长时间平均带宽小于等于允许平均带宽。 */
        unsigned int  reserved_1      : 1;  /* bit[29]   : 保留 */
        unsigned int  lmtr_type       : 1;  /* bit[30]   : 带宽限流控制的命令类型：
                                                           0：只控制读带宽；
                                                           1：同时控制读写总带宽。 */
        unsigned int  lmtr_en         : 1;  /* bit[31]   : limiter使能：
                                                           0：禁止；
                                                           1：使能。 */
    } reg;
} SOC_DMSS_ASI_QOS_LMTR0_UNION;
#endif
#define SOC_DMSS_ASI_QOS_LMTR0_lmtr_saturation_START  (0)
#define SOC_DMSS_ASI_QOS_LMTR0_lmtr_saturation_END    (13)
#define SOC_DMSS_ASI_QOS_LMTR0_lmtr_bandwidth_START   (16)
#define SOC_DMSS_ASI_QOS_LMTR0_lmtr_bandwidth_END     (28)
#define SOC_DMSS_ASI_QOS_LMTR0_lmtr_type_START        (30)
#define SOC_DMSS_ASI_QOS_LMTR0_lmtr_type_END          (30)
#define SOC_DMSS_ASI_QOS_LMTR0_lmtr_en_START          (31)
#define SOC_DMSS_ASI_QOS_LMTR0_lmtr_en_END            (31)


/*****************************************************************************
 结构名    : SOC_DMSS_ASI_QOS_LMTR1_UNION
 结构说明  : ASI_QOS_LMTR1 寄存器结构定义。地址偏移量:0x144+0x800*(asi_base)，初值:0x00000000，宽度:32
 寄存器说明: 带宽限流控制1
            （只可单独控制写带宽）
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  lmtr_saturation : 14; /* bit[0-13] : 带宽容限：
                                                           配置值=带宽容限(B)/16；
                                                           说明：
                                                           可以将本带宽控制方式等效成基于滑动窗口的流量控制，带宽容限决定了滑窗宽度以及滑窗内的允许流量：带宽容限(B)/允许平均带宽(B/Hz)=滑窗宽度（cycle）。即在配置的允许平均带宽固定的情况下，带宽容限越大，滑窗越宽，对控制前的瞬时带宽变化越不敏感，长时间控制后的平均带宽也越接近配置的允许平均带宽，但控制后的瞬时带宽的变化也可能会越剧烈。
                                                           例如，当允许带宽为理论带宽的1/3时（为便于说明，假设一个命令对应一拍数据，数据总线位宽16B。带宽控制实际是控制命令而非数据）：若带宽容限配置值为1，则任意连续的3拍内最多允许1拍数据通过；若带宽容限配置值为2，则任意连续的6拍内最多允许2拍数据通过，而这2拍数据就可能连续通过；以此类推。（由于硬件延迟等因素，建议带宽容限的有效配置值至少为2）
                                                           注意：带宽限流使能时，不可以配置为0。 */
        unsigned int  reserved_0      : 2;  /* bit[14-15]: 保留 */
        unsigned int  lmtr_bandwidth  : 13; /* bit[16-28]: 允许平均带宽：
                                                           配置值=允许平均带宽(B/Hz)*256=允许带宽(MB/s)/工作频率（MHz）*256
                                                           例如：工作频率为400MHz，当前端口的允许带宽为1400MB/s，则带宽配置值为1400/400*256=896=0x380
                                                           说明：
                                                           1.乘256的目的是保留允许平均带宽的高8位小数；
                                                           2.控制后的瞬时带宽可能会超过允许带宽，超过的范围取决于带宽容限的配置；
                                                           3.控制后的长时间平均带宽小于等于允许平均带宽。 */
        unsigned int  reserved_1      : 2;  /* bit[29-30]: 保留 */
        unsigned int  lmtr_en         : 1;  /* bit[31]   : limiter使能：
                                                           0：禁止；
                                                           1：使能。
                                                           注意：
                                                           ASI_QOS_LMTR1只能控制写带宽； */
    } reg;
} SOC_DMSS_ASI_QOS_LMTR1_UNION;
#endif
#define SOC_DMSS_ASI_QOS_LMTR1_lmtr_saturation_START  (0)
#define SOC_DMSS_ASI_QOS_LMTR1_lmtr_saturation_END    (13)
#define SOC_DMSS_ASI_QOS_LMTR1_lmtr_bandwidth_START   (16)
#define SOC_DMSS_ASI_QOS_LMTR1_lmtr_bandwidth_END     (28)
#define SOC_DMSS_ASI_QOS_LMTR1_lmtr_en_START          (31)
#define SOC_DMSS_ASI_QOS_LMTR1_lmtr_en_END            (31)


/*****************************************************************************
 结构名    : SOC_DMSS_ASI_QOS_LMTR2_UNION
 结构说明  : ASI_QOS_LMTR2 寄存器结构定义。地址偏移量:0x148+0x800*(asi_base)，初值:0x00000000，宽度:32
 寄存器说明: 带宽限流控制2
            （只可同时控制读写带宽，需与GLB_DCQ_PRILVL0/1配合使用）
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  lmtr_saturation : 14; /* bit[0-13] : 带宽容限：
                                                           配置值=带宽容限(B)/16；
                                                           说明：
                                                           可以将本带宽控制方式等效成基于滑动窗口的流量控制，带宽容限决定了滑窗宽度以及滑窗内的允许流量：带宽容限(B)/允许平均带宽(B/Hz)=滑窗宽度（cycle）。即在配置的允许平均带宽固定的情况下，带宽容限越大，滑窗越宽，对控制前的瞬时带宽变化越不敏感，长时间控制后的平均带宽也越接近配置的允许平均带宽，但控制后的瞬时带宽的变化也可能会越剧烈。
                                                           例如，当允许带宽为理论带宽的1/3时（为便于说明，假设一个命令对应一拍数据，数据总线位宽16B。带宽控制实际是控制命令而非数据）：若带宽容限配置值为1，则任意连续的3拍内最多允许1拍数据通过；若带宽容限配置值为2，则任意连续的6拍内最多允许2拍数据通过，而这2拍数据就可能连续通过；以此类推。（由于硬件延迟等因素，建议带宽容限的有效配置值至少为2）
                                                           注意：带宽限流使能时，不可以配置为0。 */
        unsigned int  reserved_0      : 2;  /* bit[14-15]: 保留 */
        unsigned int  lmtr_bandwidth  : 13; /* bit[16-28]: 允许平均带宽：
                                                           配置值=允许平均带宽(B/Hz)*256=允许带宽(MB/s)/工作频率（MHz）*256
                                                           例如：工作频率为400MHz，当前端口的允许带宽为1400MB/s，则带宽配置值为1400/400*256=896=0x380
                                                           说明：
                                                           1.乘256的目的是保留允许平均带宽的高8位小数；
                                                           2.控制后的瞬时带宽可能会超过允许带宽，超过的范围取决于带宽容限的配置；
                                                           3.控制后的长时间平均带宽小于等于允许平均带宽。 */
        unsigned int  reserved_1      : 2;  /* bit[29-30]: 保留 */
        unsigned int  lmtr_en         : 1;  /* bit[31]   : limiter使能：
                                                           0：禁止；
                                                           1：使能。
                                                           注意：
                                                           1.ASI_QOS_LMTR2只能控制读写总带宽；
                                                           2.需与GLB_DCQ_PRILVL0/1等寄存器配合使用，实现控制低优先级命令流量的特性。 */
    } reg;
} SOC_DMSS_ASI_QOS_LMTR2_UNION;
#endif
#define SOC_DMSS_ASI_QOS_LMTR2_lmtr_saturation_START  (0)
#define SOC_DMSS_ASI_QOS_LMTR2_lmtr_saturation_END    (13)
#define SOC_DMSS_ASI_QOS_LMTR2_lmtr_bandwidth_START   (16)
#define SOC_DMSS_ASI_QOS_LMTR2_lmtr_bandwidth_END     (28)
#define SOC_DMSS_ASI_QOS_LMTR2_lmtr_en_START          (31)
#define SOC_DMSS_ASI_QOS_LMTR2_lmtr_en_END            (31)


/*****************************************************************************
 结构名    : SOC_DMSS_ASI_QOS_LMTR0_OVRD_UNION
 结构说明  : ASI_QOS_LMTR0_OVRD 寄存器结构定义。地址偏移量:0x150+0x800*(asi_base)，初值:0x00000000，宽度:32
 寄存器说明: 带宽限流控制0的配置重载
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  lmtr_ovrd_prd : 10; /* bit[0-9]  : limiter0的带宽配置在lmtr_bandwidth和lmtr_ovrd_bw之间切换的方式：
                                                         n：每隔n+1个时钟周期，便以2倍或1/2倍的配置值进行逐级逼近式的切换。（举例：若lmtr_bandwidth为400MB/s，lmtr_ovrd_bw为30MB/s，则limter的允许带宽会以400->200->100->50->30和30->60->120->240->400的方式进行逐级逼近式的配置，以避免允许带宽突变可能导致的系统异常）。 */
        unsigned int  reserved_0    : 6;  /* bit[10-15]: 保留 */
        unsigned int  lmtr_ovrd_bw  : 13; /* bit[16-28]: 重载后的允许平均带宽：
                                                         配置规则同寄存器ASI_QOS_LMTR0的lmtr_bandwidth。
                                                         注意：
                                                         1.lmtr_ovrd_bw的配置值必须比lmtr_bandwidth小；
                                                         2.带宽的读写类型，取决于ASI_QOS_LMTR0的lmtr_type。 */
        unsigned int  reserved_1    : 2;  /* bit[29-30]: 保留 */
        unsigned int  lmtr_ovrd_en  : 1;  /* bit[31]   : limiter0的配置重载使能：
                                                         0：禁止；
                                                         1：使能。
                                                         说明：
                                                         使能此功能后：若寄存器ASI_DCQ_CMD_LVL中的水线触发，则对limter0的配置允许带宽进行重载，以实现进一步限流的效果；反之则恢复limter0的原配置。 */
    } reg;
} SOC_DMSS_ASI_QOS_LMTR0_OVRD_UNION;
#endif
#define SOC_DMSS_ASI_QOS_LMTR0_OVRD_lmtr_ovrd_prd_START  (0)
#define SOC_DMSS_ASI_QOS_LMTR0_OVRD_lmtr_ovrd_prd_END    (9)
#define SOC_DMSS_ASI_QOS_LMTR0_OVRD_lmtr_ovrd_bw_START   (16)
#define SOC_DMSS_ASI_QOS_LMTR0_OVRD_lmtr_ovrd_bw_END     (28)
#define SOC_DMSS_ASI_QOS_LMTR0_OVRD_lmtr_ovrd_en_START   (31)
#define SOC_DMSS_ASI_QOS_LMTR0_OVRD_lmtr_ovrd_en_END     (31)


/*****************************************************************************
 结构名    : SOC_DMSS_ASI_QOS_LMTR1_OVRD_UNION
 结构说明  : ASI_QOS_LMTR1_OVRD 寄存器结构定义。地址偏移量:0x154+0x800*(asi_base)，初值:0x00000000，宽度:32
 寄存器说明: 带宽限流控制1的配置重载
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  lmtr_ovrd_prd : 10; /* bit[0-9]  : limiter1的带宽配置在lmtr_bandwidth和lmtr_ovrd_bw之间切换的方式：
                                                         n：每隔n+1个时钟周期，便以2倍或1/2倍的配置值进行逐级逼近式的切换。（举例：若lmtr_bandwidth为400MB/s，lmtr_ovrd_bw为30MB/s，则limter的允许带宽会以400->200->100->50->30和30->60->120->240->400的方式进行逐级逼近式的配置，以避免允许带宽突变可能导致的系统异常）。 */
        unsigned int  reserved_0    : 6;  /* bit[10-15]: 保留 */
        unsigned int  lmtr_ovrd_bw  : 13; /* bit[16-28]: 重载后的允许平均带宽：
                                                         配置规则同寄存器ASI_QOS_LMTR1的lmtr_bandwidth。
                                                         注意：
                                                         1.lmtr_ovrd_bw的配置值必须比lmtr_bandwidth小；
                                                         2.带宽的读写类型，取决于ASI_QOS_LMTR1的lmtr_type。 */
        unsigned int  reserved_1    : 2;  /* bit[29-30]: 保留 */
        unsigned int  lmtr_ovrd_en  : 1;  /* bit[31]   : limiter1的配置重载使能：
                                                         0：禁止；
                                                         1：使能。
                                                         说明：
                                                         使能此功能后：若寄存器ASI_DCQ_CMD_LVL中的水线触发，则对limter1的配置允许带宽进行重载，以实现进一步限流的效果；反之则恢复limter1的原配置。 */
    } reg;
} SOC_DMSS_ASI_QOS_LMTR1_OVRD_UNION;
#endif
#define SOC_DMSS_ASI_QOS_LMTR1_OVRD_lmtr_ovrd_prd_START  (0)
#define SOC_DMSS_ASI_QOS_LMTR1_OVRD_lmtr_ovrd_prd_END    (9)
#define SOC_DMSS_ASI_QOS_LMTR1_OVRD_lmtr_ovrd_bw_START   (16)
#define SOC_DMSS_ASI_QOS_LMTR1_OVRD_lmtr_ovrd_bw_END     (28)
#define SOC_DMSS_ASI_QOS_LMTR1_OVRD_lmtr_ovrd_en_START   (31)
#define SOC_DMSS_ASI_QOS_LMTR1_OVRD_lmtr_ovrd_en_END     (31)


/*****************************************************************************
 结构名    : SOC_DMSS_ASI_DCQ_CMDLVL_UNION
 结构说明  : ASI_DCQ_CMDLVL 寄存器结构定义。地址偏移量:0x15C+0x800*(asi_base)，初值:0x00000000，宽度:32
 寄存器说明: 基于DDRC命令队列状态的允许命令个数水线
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  dcq_wr_lvl : 8;  /* bit[0-7]  : 写命令个数的控制水线：
                                                      0x00：此水线关闭；
                                                      0x01~0xFF：当写命令个数达到或超过此控制水线时，通过对limter1进行重载（寄存器ASI_QOS_LMTR1_OVRD），实现对写命令带宽的进一步限制。
                                                      注意：
                                                      若有多个DDRC，则各个DDRC的命令队列命令状态均为“或”的关系，即任一DDRC命令队列的状态达到水线即可。 */
        unsigned int  dcq_rd_lvl : 8;  /* bit[8-15] : 读命令个数的控制水线：
                                                      0x00：此水线关闭；
                                                      0x01~0xFF：当读命令个数达到或超过此控制水线时，通过对limter0进行重载（寄存器ASI_QOS_LMTR0_OVRD），实现对读命令带宽的进一步限制。
                                                      注意：
                                                      1.若有多个DDRC，则各个DDRC的命令队列命令状态均为“或”的关系，即任一DDRC命令队列的状态达到水线即可；
                                                      2.只有当limter0被配置为只对读命令进行限流时（寄存器ASI_QOS_LMTR0的lmtr_type），此控制水线才可生效。 */
        unsigned int  dcq_lvl    : 8;  /* bit[16-23]: 读写命令总数的控制水线：
                                                      0x00：此水线关闭；
                                                      0x01~0xFF：当读写命令总数达到或超过此控制水线时，通过对limter0进行重载（寄存器ASI_QOS_LMTR0_OVRD），实现对读写命令总带宽的进一步限制。
                                                      注意：
                                                      1.若有多个DDRC，则各个DDRC的命令队列命令状态均为“或”的关系，即任一DDRC命令队列的状态达到水线即可；
                                                      2.只有当limter0被配置为同时对读写命令进行限流时（寄存器ASI_QOS_LMTR0的lmtr_type），此控制水线才可生效。 */
        unsigned int  reserved   : 8;  /* bit[24-31]: 保留 */
    } reg;
} SOC_DMSS_ASI_DCQ_CMDLVL_UNION;
#endif
#define SOC_DMSS_ASI_DCQ_CMDLVL_dcq_wr_lvl_START  (0)
#define SOC_DMSS_ASI_DCQ_CMDLVL_dcq_wr_lvl_END    (7)
#define SOC_DMSS_ASI_DCQ_CMDLVL_dcq_rd_lvl_START  (8)
#define SOC_DMSS_ASI_DCQ_CMDLVL_dcq_rd_lvl_END    (15)
#define SOC_DMSS_ASI_DCQ_CMDLVL_dcq_lvl_START     (16)
#define SOC_DMSS_ASI_DCQ_CMDLVL_dcq_lvl_END       (23)


/*****************************************************************************
 结构名    : SOC_DMSS_ASI_QOS_RDOSTD_UNION
 结构说明  : ASI_QOS_RDOSTD 寄存器结构定义。地址偏移量:0x160+0x800*(asi_base)，初值:0x00000000，宽度:32
 寄存器说明: 读命令OSTD限制
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  rd_ostd_lvl : 8;  /* bit[0-7] : 读命令outstanding（OSTD）水线：
                                                      0x00：不限制命令的OSTD个数；
                                                      0x01～0x7C：允许的最大读命令OSTD个数。
                                                      注意：
                                                      1.当读命令outstanding达到设定水线时，阻塞所有读命令；
                                                      2.写命令由于其fast response的特性，无法准确控制其outstanding。 */
        unsigned int  reserved    : 24; /* bit[8-31]: 保留 */
    } reg;
} SOC_DMSS_ASI_QOS_RDOSTD_UNION;
#endif
#define SOC_DMSS_ASI_QOS_RDOSTD_rd_ostd_lvl_START  (0)
#define SOC_DMSS_ASI_QOS_RDOSTD_rd_ostd_lvl_END    (7)


/*****************************************************************************
 结构名    : SOC_DMSS_ASI_QOS_RDOSTD_ST_UNION
 结构说明  : ASI_QOS_RDOSTD_ST 寄存器结构定义。地址偏移量:0x164+0x800*(asi_base)，初值:0x00000000，宽度:32
 寄存器说明: 读命令OSTD状态统计
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  rd_ostd_st : 8;  /* bit[0-7] : 读命令OSTD统计状态。 */
        unsigned int  reserved   : 24; /* bit[8-31]: 保留 */
    } reg;
} SOC_DMSS_ASI_QOS_RDOSTD_ST_UNION;
#endif
#define SOC_DMSS_ASI_QOS_RDOSTD_ST_rd_ostd_st_START  (0)
#define SOC_DMSS_ASI_QOS_RDOSTD_ST_rd_ostd_st_END    (7)


/*****************************************************************************
 结构名    : SOC_DMSS_ASI_PUSH_WRMID_UNION
 结构说明  : ASI_PUSH_WRMID 寄存器结构定义。地址偏移量:0x180+0x800*(asi_base)，初值:0x00000000，宽度:32
 寄存器说明: 写命令同MID命令优先级传递使能
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  wr_mid_sel : 32; /* bit[0-31]: 写命令MID（最低五位）的比特匹配选择：
                                                     wr_mid_sel[n]=0：对于MID=n的命令，在QOSBUF中禁止同MID写命令优先级传递功能；
                                                     wr_mid_sel[n]=1：对于MID=n的命令，在QOSBUF中使能同MID写命令优先级传递功能。 */
    } reg;
} SOC_DMSS_ASI_PUSH_WRMID_UNION;
#endif
#define SOC_DMSS_ASI_PUSH_WRMID_wr_mid_sel_START  (0)
#define SOC_DMSS_ASI_PUSH_WRMID_wr_mid_sel_END    (31)


/*****************************************************************************
 结构名    : SOC_DMSS_ASI_PUSH_RDMID_UNION
 结构说明  : ASI_PUSH_RDMID 寄存器结构定义。地址偏移量:0x184+0x800*(asi_base)，初值:0x00000000，宽度:32
 寄存器说明: 读命令同MID命令优先级传递使能
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  rd_mid_sel : 32; /* bit[0-31]: 读命令MID（最低五位）的比特匹配选择：
                                                     rd_mid_sel[n]=0：对于MID=n的命令，在QOSBUF中禁止同MID读命令优先级传递功能；
                                                     rd_mid_sel[n]=1：对于MID=n的命令，在QOSBUF中使能同MID读命令优先级传递功能。 */
    } reg;
} SOC_DMSS_ASI_PUSH_RDMID_UNION;
#endif
#define SOC_DMSS_ASI_PUSH_RDMID_rd_mid_sel_START  (0)
#define SOC_DMSS_ASI_PUSH_RDMID_rd_mid_sel_END    (31)


/*****************************************************************************
 结构名    : SOC_DMSS_ASI_STAT_MASK_UNION
 结构说明  : ASI_STAT_MASK 寄存器结构定义。地址偏移量:0x200+0x800*(asi_base)，初值:0x00000000，宽度:32
 寄存器说明: 统计功能屏蔽
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  stat_mask_flux_rd : 1;  /* bit[0]   : 读流量统计屏蔽：
                                                            0：参与统计；
                                                            1：不参与统计。
                                                            说明：
                                                            1.统计结果记录在寄存器ASI_STAT_FLUX_RD中；
                                                            2.只有寄存器ASI_STAT_FLUX_FILTER0/1中的ID和优先级匹配成功的命令，才参与统计；
                                                            3.统计的使能开关在寄存器GLB_STAT_CTRL中。 */
        unsigned int  stat_mask_flux_wr : 1;  /* bit[1]   : 写流量统计屏蔽：
                                                            配置方式同stat_flux_rd_en。 */
        unsigned int  reserved_0        : 2;  /* bit[2-3] : 保留 */
        unsigned int  stat_mask_lmtr0   : 1;  /* bit[4]   : LMTR0的生效周期统计屏蔽：
                                                            0：参与统计；
                                                            1：不参与统计。
                                                            说明：
                                                            1.统计结果记录在寄存器ASI_STAT_LMTR0中；
                                                            2.只有寄存器ASI_STAT_FLUX_FILTER0/1中的ID和优先级匹配成功的命令，才参与统计；
                                                            3.统计的使能开关在寄存器GLB_STAT_CTRL中。 */
        unsigned int  stat_mask_lmtr1   : 1;  /* bit[5]   : LMTR1的生效周期统计屏蔽：
                                                            配置方式同stat_lmtr0_en。 */
        unsigned int  stat_mask_lmtr2   : 1;  /* bit[6]   : LMTR2的生效周期统计屏蔽：
                                                            配置方式同stat_lmtr0_en。 */
        unsigned int  stat_mask_rdlat   : 1;  /* bit[7]   : 读命令latency统计屏蔽：
                                                            0：参与统计；
                                                            1：不参与统计。
                                                            说明：
                                                            1.统计结果记录在寄存器ASI_STAT_RDLAT中；
                                                            2.统计的使能开关在寄存器GLB_STAT_CTRL中。 */
        unsigned int  stat_mask_pri     : 1;  /* bit[8]   : 命令优先级统计屏蔽：
                                                            0：参与统计；
                                                            1：不参与统计。
                                                            说明：
                                                            1.统计结果记录在寄存器ASI_STAT_PRI中；
                                                            2.统计的使能开关在寄存器GLB_STAT_CTRL中。 */
        unsigned int  reserved_1        : 23; /* bit[9-31]: 保留 */
    } reg;
} SOC_DMSS_ASI_STAT_MASK_UNION;
#endif
#define SOC_DMSS_ASI_STAT_MASK_stat_mask_flux_rd_START  (0)
#define SOC_DMSS_ASI_STAT_MASK_stat_mask_flux_rd_END    (0)
#define SOC_DMSS_ASI_STAT_MASK_stat_mask_flux_wr_START  (1)
#define SOC_DMSS_ASI_STAT_MASK_stat_mask_flux_wr_END    (1)
#define SOC_DMSS_ASI_STAT_MASK_stat_mask_lmtr0_START    (4)
#define SOC_DMSS_ASI_STAT_MASK_stat_mask_lmtr0_END      (4)
#define SOC_DMSS_ASI_STAT_MASK_stat_mask_lmtr1_START    (5)
#define SOC_DMSS_ASI_STAT_MASK_stat_mask_lmtr1_END      (5)
#define SOC_DMSS_ASI_STAT_MASK_stat_mask_lmtr2_START    (6)
#define SOC_DMSS_ASI_STAT_MASK_stat_mask_lmtr2_END      (6)
#define SOC_DMSS_ASI_STAT_MASK_stat_mask_rdlat_START    (7)
#define SOC_DMSS_ASI_STAT_MASK_stat_mask_rdlat_END      (7)
#define SOC_DMSS_ASI_STAT_MASK_stat_mask_pri_START      (8)
#define SOC_DMSS_ASI_STAT_MASK_stat_mask_pri_END        (8)


/*****************************************************************************
 结构名    : SOC_DMSS_ASI_STAT_CYCLE_UNION
 结构说明  : ASI_STAT_CYCLE 寄存器结构定义。地址偏移量:0x208+0x800*(asi_base)，初值:0x00000000，宽度:32
 寄存器说明: 统计周期
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  stat_cycle : 32; /* bit[0-31]: 统计周期：
                                                     说明：
                                                     1.统计功能的统计时钟周期数；
                                                     2.统计的使能，参见寄存器GLB_STAT_CTRL；
                                                     3.统计停止后结果保持，统计再次开始时自动清零，溢出后卷绕计数；
                                                     4.32bit计数器，400MHz下的量程为2.5ns*2^32=10.74s。 */
    } reg;
} SOC_DMSS_ASI_STAT_CYCLE_UNION;
#endif
#define SOC_DMSS_ASI_STAT_CYCLE_stat_cycle_START  (0)
#define SOC_DMSS_ASI_STAT_CYCLE_stat_cycle_END    (31)


/*****************************************************************************
 结构名    : SOC_DMSS_ASI_STAT_FLUX_FILTER0_UNION
 结构说明  : ASI_STAT_FLUX_FILTER0 寄存器结构定义。地址偏移量:0x210+0x800*(asi_base)，初值:0x00000000，宽度:32
 寄存器说明: 流量统计过滤配置0
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  stat_flux_id_match : 32; /* bit[0-31]: 流量统计匹配ID：
                                                             与stat_flux_id_mask配合使用，当cmd_id & stat_flux_id_mask = stat_flux_id_match时，认为当前cmd_id被成功匹配。成功匹配ID的命令才会参与寄存器ASI_STAT_FLUX中的流量统计。
                                                             说明：
                                                             1.此处ID是命令的{MID,AXI_ID}拼合而成，具体位宽取决于RTL的配置，可在GLB_RTL_INF0寄存器中查询；
                                                             2.若stat_flux_id_match和stat_flux_id_mask都配为0，则可对所有命令进行流量统计；
                                                             3.此寄存器需在统计功能关闭时配置，否则会导致统计结果不准确。 */
    } reg;
} SOC_DMSS_ASI_STAT_FLUX_FILTER0_UNION;
#endif
#define SOC_DMSS_ASI_STAT_FLUX_FILTER0_stat_flux_id_match_START  (0)
#define SOC_DMSS_ASI_STAT_FLUX_FILTER0_stat_flux_id_match_END    (31)


/*****************************************************************************
 结构名    : SOC_DMSS_ASI_STAT_FLUX_FILTER1_UNION
 结构说明  : ASI_STAT_FLUX_FILTER1 寄存器结构定义。地址偏移量:0x214+0x800*(asi_base)，初值:0x00000000，宽度:32
 寄存器说明: 流量统计过滤配置1
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  stat_flux_id_mask : 32; /* bit[0-31]: 流量统计匹配ID的掩码：
                                                            与stat_flux_id_match配合使用，当cmd_id & stat_flux_id_mask = stat_flux_id_match时，认为当前cmd_id被成功匹配。成功匹配ID的命令才会参与寄存器ASI_STAT_FLUX中的流量统计。
                                                            说明：
                                                            1.此处ID是命令的{MID,AXI_ID}拼合而成，具体位宽取决于RTL的配置，可在GLB_RTL_INF0寄存器中查询；
                                                            2.若stat_flux_id_match和stat_flux_id_mask都配为0，则可对所有命令进行流量统计；
                                                            3.此寄存器需在统计功能关闭时配置，否则会导致统计结果不准确。 */
    } reg;
} SOC_DMSS_ASI_STAT_FLUX_FILTER1_UNION;
#endif
#define SOC_DMSS_ASI_STAT_FLUX_FILTER1_stat_flux_id_mask_START  (0)
#define SOC_DMSS_ASI_STAT_FLUX_FILTER1_stat_flux_id_mask_END    (31)


/*****************************************************************************
 结构名    : SOC_DMSS_ASI_STAT_FLUX_WR_UNION
 结构说明  : ASI_STAT_FLUX_WR 寄存器结构定义。地址偏移量:0x218+0x800*(asi_base)，初值:0x00000000，宽度:32
 寄存器说明: 写流量统计
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  stat_flux_wr : 32; /* bit[0-31]: 统计写流量：
                                                       说明：
                                                       1.累加所有写命令对应的数据流量，单位为Byte；
                                                       2.统计的使能、过滤及屏蔽，参见寄存器GLB_STAT_CTRL/ASI_STAT_FLUX_FILTER/ASI_STAT_MASK；
                                                       3.统计停止后结果保持，统计再次开始时自动清零，溢出后卷绕计数；
                                                       4.32bit计数器，即量程为4GB。 */
    } reg;
} SOC_DMSS_ASI_STAT_FLUX_WR_UNION;
#endif
#define SOC_DMSS_ASI_STAT_FLUX_WR_stat_flux_wr_START  (0)
#define SOC_DMSS_ASI_STAT_FLUX_WR_stat_flux_wr_END    (31)


/*****************************************************************************
 结构名    : SOC_DMSS_ASI_STAT_FLUX_RD_UNION
 结构说明  : ASI_STAT_FLUX_RD 寄存器结构定义。地址偏移量:0x21C+0x800*(asi_base)，初值:0x00000000，宽度:32
 寄存器说明: 读流量统计
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  stat_flux_rd : 32; /* bit[0-31]: 统计读流量：
                                                       说明：
                                                       1.累加所有读命令对应的数据流量，单位为Byte；
                                                       2.统计的使能、过滤及屏蔽，参见寄存器GLB_STAT_CTRL/ASI_STAT_FLUX_FILTER/ASI_STAT_MASK；
                                                       3.统计停止后结果保持，统计再次开始时自动清零，溢出后卷绕计数；
                                                       4.32bit计数器，即量程为4GB。 */
    } reg;
} SOC_DMSS_ASI_STAT_FLUX_RD_UNION;
#endif
#define SOC_DMSS_ASI_STAT_FLUX_RD_stat_flux_rd_START  (0)
#define SOC_DMSS_ASI_STAT_FLUX_RD_stat_flux_rd_END    (31)


/*****************************************************************************
 结构名    : SOC_DMSS_ASI_STAT_LMTR0_UNION
 结构说明  : ASI_STAT_LMTR0 寄存器结构定义。地址偏移量:0x220+0x800*(asi_base)，初值:0x00000000，宽度:32
 寄存器说明: 带宽控制器0统计
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  stat_lmtr0 : 32; /* bit[0-31]: 统计LMTR0的生效周期：
                                                     说明：
                                                     1.累加LMTR0的生效（反压命令）周期数，单位为cycle；
                                                     2.统计的使能及屏蔽，参见寄存器GLB_STAT_CTRL/ASI_STAT_MASK；
                                                     3.统计停止后结果保持，统计再次开始时自动清零，溢出后卷绕计数。 */
    } reg;
} SOC_DMSS_ASI_STAT_LMTR0_UNION;
#endif
#define SOC_DMSS_ASI_STAT_LMTR0_stat_lmtr0_START  (0)
#define SOC_DMSS_ASI_STAT_LMTR0_stat_lmtr0_END    (31)


/*****************************************************************************
 结构名    : SOC_DMSS_ASI_STAT_LMTR1_UNION
 结构说明  : ASI_STAT_LMTR1 寄存器结构定义。地址偏移量:0x224+0x800*(asi_base)，初值:0x00000000，宽度:32
 寄存器说明: 带宽控制器1统计
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  stat_lmtr1 : 32; /* bit[0-31]: 统计LMTR1的生效周期：
                                                     说明：
                                                     1.累加LMTR1的生效（反压命令）周期数，单位为cycle；
                                                     2.统计的使能及屏蔽，参见寄存器GLB_STAT_CTRL/ASI_STAT_MASK；
                                                     3.统计停止后结果保持，统计再次开始时自动清零，溢出后卷绕计数。 */
    } reg;
} SOC_DMSS_ASI_STAT_LMTR1_UNION;
#endif
#define SOC_DMSS_ASI_STAT_LMTR1_stat_lmtr1_START  (0)
#define SOC_DMSS_ASI_STAT_LMTR1_stat_lmtr1_END    (31)


/*****************************************************************************
 结构名    : SOC_DMSS_ASI_STAT_LMTR2_UNION
 结构说明  : ASI_STAT_LMTR2 寄存器结构定义。地址偏移量:0x228+0x800*(asi_base)，初值:0x00000000，宽度:32
 寄存器说明: 带宽控制器2统计
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  stat_lmtr2 : 32; /* bit[0-31]: 统计LMTR2的生效周期：
                                                     说明：
                                                     1.累加LMTR2的生效（反压命令）周期数，单位为cycle；
                                                     2.统计的使能及屏蔽，参见寄存器GLB_STAT_CTRL/ASI_STAT_MASK；
                                                     3.统计停止后结果保持，统计再次开始时自动清零，溢出后卷绕计数。 */
    } reg;
} SOC_DMSS_ASI_STAT_LMTR2_UNION;
#endif
#define SOC_DMSS_ASI_STAT_LMTR2_stat_lmtr2_START  (0)
#define SOC_DMSS_ASI_STAT_LMTR2_stat_lmtr2_END    (31)


/*****************************************************************************
 结构名    : SOC_DMSS_ASI_STAT_RDLAT_UNION
 结构说明  : ASI_STAT_RDLAT 寄存器结构定义。地址偏移量:0x22C+0x800*(asi_base)，初值:0x00000000，宽度:32
 寄存器说明: 读latency统计
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  stat_rdlat : 32; /* bit[0-31]: 统计累计读latency：
                                                     说明：
                                                     1.逐cycle累加读outstanding：累加结果/统计周期=读平均latency；
                                                     2.统计的使能及屏蔽，参见寄存器GLB_STAT_CTRL/ASI_STAT_MASK；
                                                     3.统计停止后结果保持，统计再次开始时自动清零，溢出后卷绕计数。 */
    } reg;
} SOC_DMSS_ASI_STAT_RDLAT_UNION;
#endif
#define SOC_DMSS_ASI_STAT_RDLAT_stat_rdlat_START  (0)
#define SOC_DMSS_ASI_STAT_RDLAT_stat_rdlat_END    (31)


/*****************************************************************************
 结构名    : SOC_DMSS_ASI_STAT_PRI0_UNION
 结构说明  : ASI_STAT_PRI0 寄存器结构定义。地址偏移量:0x230+0x800*(asi_base)，初值:0x00000000，宽度:32
 寄存器说明: 命令优先级0统计
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  stat_pri0 : 32; /* bit[0-31]: 统计优先级为0的命令个数：
                                                    说明：
                                                    1.此处统计的命令是拆分后发给DDRC的命令，非AXI命令；
                                                    2.若寄存器ASI_QOS_CTRL中的arb_pri_use为0，则此处统计的是命令优先级（来源是优先级重映射/Regulator/Latency自适应三种方式之一）；反之则统计的是仲裁优先级（在命令优先级的基础之上，优先级可能受优先级自适应及优先级传递等功能的作用而被提高）。 */
    } reg;
} SOC_DMSS_ASI_STAT_PRI0_UNION;
#endif
#define SOC_DMSS_ASI_STAT_PRI0_stat_pri0_START  (0)
#define SOC_DMSS_ASI_STAT_PRI0_stat_pri0_END    (31)


/*****************************************************************************
 结构名    : SOC_DMSS_ASI_STAT_PRI1_UNION
 结构说明  : ASI_STAT_PRI1 寄存器结构定义。地址偏移量:0x234+0x800*(asi_base)，初值:0x00000000，宽度:32
 寄存器说明: 命令优先级1统计
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  stat_pri1 : 32; /* bit[0-31]: 统计命令优先级为1的命令个数。 */
    } reg;
} SOC_DMSS_ASI_STAT_PRI1_UNION;
#endif
#define SOC_DMSS_ASI_STAT_PRI1_stat_pri1_START  (0)
#define SOC_DMSS_ASI_STAT_PRI1_stat_pri1_END    (31)


/*****************************************************************************
 结构名    : SOC_DMSS_ASI_STAT_PRI2_UNION
 结构说明  : ASI_STAT_PRI2 寄存器结构定义。地址偏移量:0x238+0x800*(asi_base)，初值:0x00000000，宽度:32
 寄存器说明: 命令优先级2统计
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  stat_pri2 : 32; /* bit[0-31]: 统计命令优先级为2的命令个数。 */
    } reg;
} SOC_DMSS_ASI_STAT_PRI2_UNION;
#endif
#define SOC_DMSS_ASI_STAT_PRI2_stat_pri2_START  (0)
#define SOC_DMSS_ASI_STAT_PRI2_stat_pri2_END    (31)


/*****************************************************************************
 结构名    : SOC_DMSS_ASI_STAT_PRI3_UNION
 结构说明  : ASI_STAT_PRI3 寄存器结构定义。地址偏移量:0x23C+0x800*(asi_base)，初值:0x00000000，宽度:32
 寄存器说明: 命令优先级3统计
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  stat_pri3 : 32; /* bit[0-31]: 统计命令优先级为3的命令个数。 */
    } reg;
} SOC_DMSS_ASI_STAT_PRI3_UNION;
#endif
#define SOC_DMSS_ASI_STAT_PRI3_stat_pri3_START  (0)
#define SOC_DMSS_ASI_STAT_PRI3_stat_pri3_END    (31)


/*****************************************************************************
 结构名    : SOC_DMSS_ASI_STAT_PRI4_UNION
 结构说明  : ASI_STAT_PRI4 寄存器结构定义。地址偏移量:0x240+0x800*(asi_base)，初值:0x00000000，宽度:32
 寄存器说明: 命令优先级4统计
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  stat_pri4 : 32; /* bit[0-31]: 统计命令优先级为4的命令个数。 */
    } reg;
} SOC_DMSS_ASI_STAT_PRI4_UNION;
#endif
#define SOC_DMSS_ASI_STAT_PRI4_stat_pri4_START  (0)
#define SOC_DMSS_ASI_STAT_PRI4_stat_pri4_END    (31)


/*****************************************************************************
 结构名    : SOC_DMSS_ASI_STAT_PRI5_UNION
 结构说明  : ASI_STAT_PRI5 寄存器结构定义。地址偏移量:0x244+0x800*(asi_base)，初值:0x00000000，宽度:32
 寄存器说明: 命令优先级5统计
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  stat_pri5 : 32; /* bit[0-31]: 统计命令优先级为5的命令个数。 */
    } reg;
} SOC_DMSS_ASI_STAT_PRI5_UNION;
#endif
#define SOC_DMSS_ASI_STAT_PRI5_stat_pri5_START  (0)
#define SOC_DMSS_ASI_STAT_PRI5_stat_pri5_END    (31)


/*****************************************************************************
 结构名    : SOC_DMSS_ASI_STAT_PRI6_UNION
 结构说明  : ASI_STAT_PRI6 寄存器结构定义。地址偏移量:0x248+0x800*(asi_base)，初值:0x00000000，宽度:32
 寄存器说明: 命令优先级6统计
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  stat_pri6 : 32; /* bit[0-31]: 统计命令优先级为6的命令个数。 */
    } reg;
} SOC_DMSS_ASI_STAT_PRI6_UNION;
#endif
#define SOC_DMSS_ASI_STAT_PRI6_stat_pri6_START  (0)
#define SOC_DMSS_ASI_STAT_PRI6_stat_pri6_END    (31)


/*****************************************************************************
 结构名    : SOC_DMSS_ASI_STAT_PRI7_UNION
 结构说明  : ASI_STAT_PRI7 寄存器结构定义。地址偏移量:0x24C+0x800*(asi_base)，初值:0x00000000，宽度:32
 寄存器说明: 命令优先级7统计
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  stat_pri7 : 32; /* bit[0-31]: 统计命令优先级为7的命令个数。 */
    } reg;
} SOC_DMSS_ASI_STAT_PRI7_UNION;
#endif
#define SOC_DMSS_ASI_STAT_PRI7_stat_pri7_START  (0)
#define SOC_DMSS_ASI_STAT_PRI7_stat_pri7_END    (31)


/*****************************************************************************
 结构名    : SOC_DMSS_ASI_SEC_LD_SEL_UNION
 结构说明  : ASI_SEC_LD_SEL 寄存器结构定义。地址偏移量:0x410+0x800*(asi_base)，初值:0x00000000，宽度:32
 寄存器说明: 锁定安全属性相关配置寄存器
            （当secur_boot_lock信号被拉高超过一个时钟周期时，此寄存器自身及其选定的相关寄存器被锁定为只读，只可通过系统复位解除锁定）
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  ld_rgn_map    : 1;  /* bit[0]    : 拉高sucure_boot_lock信号后，锁定被ld_rgns_sel选定region的ASI_SEC_REGION_MAP寄存器为只读：
                                                         0：不锁定；
                                                         1：锁定。
                                                         本寄存器自身被锁定条件：sucure_boot_lock信号被拉高过。 */
        unsigned int  ld_rgn_attrib : 1;  /* bit[1]    : 拉高sucure_boot_lock信号后，锁定被ld_rgns_sel选定region的ASI_SEC_REGION_ATTRIB寄存器为只读：
                                                         0：不锁定；
                                                         1：锁定。
                                                         本寄存器自身被锁定条件：sucure_boot_lock信号被拉高过。 */
        unsigned int  ld_mid_rd     : 1;  /* bit[2]    : 拉高sucure_boot_lock信号后，锁定被ld_rgns_sel选定region的ASI_SEC_MID_RD寄存器为只读：
                                                         0：不锁定；
                                                         1：锁定。
                                                         本寄存器自身被锁定条件：sucure_boot_lock信号被拉高过。 */
        unsigned int  ld_mid_wr     : 1;  /* bit[3]    : 拉高sucure_boot_lock信号后，锁定被ld_rgns_sel选定region的ASI_SEC_MID_WR寄存器为只读：
                                                         0：不锁定；
                                                         1：锁定。
                                                         本寄存器自身被锁定条件：sucure_boot_lock信号被拉高过。 */
        unsigned int  reserved_0    : 12; /* bit[4-15] : 保留 */
        unsigned int  ld_rgns_sel   : 5;  /* bit[16-20]: 选择需将相关配置寄存器锁定为只读的regions范围：
                                                         sec_ld_rgns_sel=N：从最高位起选定连续的N+1个rgn。
                                                         举例：
                                                         sec_ld_rgns_sel=5：rgn15~rgn10的相关寄存器被选定（假设no_of_rgns=16）。
                                                         注意：
                                                         1.若选定的rgn个数大于实际rgn总数no_of_rgns，则选定全部rgn；
                                                         2.若某rgn被选定，且ld_mid_wr/ld_mid_rd/lg_rgn_attrib/ld_rgn_map配置为锁定，则此rgn对应的如下相关配置寄存器皆被选定：
                                                         （1）ASI_SEC_RGN_MAP；
                                                         （2）ASI_SEC_RGN_ATTRIB；
                                                         （3）ASI_SEC_MID_WR；
                                                         （4）ASI_SEC_MID_RD；
                                                         本寄存器自身被锁定条件：sucure_boot_lock信号被拉高过。 */
        unsigned int  reserved_1    : 11; /* bit[21-31]: 保留 */
    } reg;
} SOC_DMSS_ASI_SEC_LD_SEL_UNION;
#endif
#define SOC_DMSS_ASI_SEC_LD_SEL_ld_rgn_map_START     (0)
#define SOC_DMSS_ASI_SEC_LD_SEL_ld_rgn_map_END       (0)
#define SOC_DMSS_ASI_SEC_LD_SEL_ld_rgn_attrib_START  (1)
#define SOC_DMSS_ASI_SEC_LD_SEL_ld_rgn_attrib_END    (1)
#define SOC_DMSS_ASI_SEC_LD_SEL_ld_mid_rd_START      (2)
#define SOC_DMSS_ASI_SEC_LD_SEL_ld_mid_rd_END        (2)
#define SOC_DMSS_ASI_SEC_LD_SEL_ld_mid_wr_START      (3)
#define SOC_DMSS_ASI_SEC_LD_SEL_ld_mid_wr_END        (3)
#define SOC_DMSS_ASI_SEC_LD_SEL_ld_rgns_sel_START    (16)
#define SOC_DMSS_ASI_SEC_LD_SEL_ld_rgns_sel_END      (20)


/*****************************************************************************
 结构名    : SOC_DMSS_ASI_SEC_INT_EN_UNION
 结构说明  : ASI_SEC_INT_EN 寄存器结构定义。地址偏移量:0x420+0x800*(asi_base)，初值:0x00000001，宽度:32
 寄存器说明: 安全中断使能
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  int_en   : 1;  /* bit[0]   : 越权命令的中断输出使能。
                                                   0：禁止；
                                                   1：使能。
                                                   说明：
                                                   1.当有越权命令访问时，可上报中断并记录越权命令信息（请参考ASI_SEC_FAIL_CMD_INF寄存器）；
                                                   2.只能禁止中断输出，但相关寄存器还是会正常记录中断状态及越权命令信息。 */
        unsigned int  reserved : 31; /* bit[1-31]: 保留 */
    } reg;
} SOC_DMSS_ASI_SEC_INT_EN_UNION;
#endif
#define SOC_DMSS_ASI_SEC_INT_EN_int_en_START    (0)
#define SOC_DMSS_ASI_SEC_INT_EN_int_en_END      (0)


/*****************************************************************************
 结构名    : SOC_DMSS_ASI_SEC_INT_STATUS_UNION
 结构说明  : ASI_SEC_INT_STATUS 寄存器结构定义。地址偏移量:0x424+0x800*(asi_base)，初值:0x00000000，宽度:32
 寄存器说明: 安全中断状态
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  int_status  : 1;  /* bit[0]   : 中断状态指示：
                                                      0：中断未产生；
                                                      1：中断已产生。
                                                      注意：从GLOBAL模块的GLB_INT_STATUS寄存器中，可识别出中断来自于哪个ASI中的SEC模块。 */
        unsigned int  int_overrun : 1;  /* bit[1]   : 多次中断指示：
                                                      0：中断未产生或只产生了一次；
                                                      1：中断已产生多次。 */
        unsigned int  reserved    : 30; /* bit[2-31]: 保留 */
    } reg;
} SOC_DMSS_ASI_SEC_INT_STATUS_UNION;
#endif
#define SOC_DMSS_ASI_SEC_INT_STATUS_int_status_START   (0)
#define SOC_DMSS_ASI_SEC_INT_STATUS_int_status_END     (0)
#define SOC_DMSS_ASI_SEC_INT_STATUS_int_overrun_START  (1)
#define SOC_DMSS_ASI_SEC_INT_STATUS_int_overrun_END    (1)


/*****************************************************************************
 结构名    : SOC_DMSS_ASI_SEC_FAIL_CMD_INF0_UNION
 结构说明  : ASI_SEC_FAIL_CMD_INF0 寄存器结构定义。地址偏移量:0x480+0x800*(asi_base)，初值:0x00000000，宽度:32
 寄存器说明: 记录首个越权命令的信息0
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  address_low : 32; /* bit[0-31]: 中断状态清除前的首个越权命令的低32位地址。 */
    } reg;
} SOC_DMSS_ASI_SEC_FAIL_CMD_INF0_UNION;
#endif
#define SOC_DMSS_ASI_SEC_FAIL_CMD_INF0_address_low_START  (0)
#define SOC_DMSS_ASI_SEC_FAIL_CMD_INF0_address_low_END    (31)


/*****************************************************************************
 结构名    : SOC_DMSS_ASI_SEC_FAIL_CMD_INF1_UNION
 结构说明  : ASI_SEC_FAIL_CMD_INF1 寄存器结构定义。地址偏移量:0x484+0x800*(asi_base)，初值:0x00000000，宽度:32
 寄存器说明: 记录首个越权命令的信息1
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  address_high : 8;  /* bit[0-7]  : 中断状态清除前的首个越权命令的高位地址（如果存在高位地址）。 */
        unsigned int  reserved_0   : 8;  /* bit[8-15] : 保留 */
        unsigned int  privileged   : 1;  /* bit[16]   : 中断状态清除前首个越权命令的特权模式信息：
                                                        0：unprivileged访问；
                                                        1：privileged访问。 */
        unsigned int  nonsecure    : 1;  /* bit[17]   : 中断状态清除前首个越权命令的安全模式信息：
                                                        0：secure访问；
                                                        1：non-secure访问。 */
        unsigned int  reserved_1   : 2;  /* bit[18-19]: 保留 */
        unsigned int  access_type  : 1;  /* bit[20]   : 中断状态清除前首个越权命令的读写模式信息：
                                                        0：read访问；
                                                        1：write访问。 */
        unsigned int  reserved_2   : 11; /* bit[21-31]: 保留 */
    } reg;
} SOC_DMSS_ASI_SEC_FAIL_CMD_INF1_UNION;
#endif
#define SOC_DMSS_ASI_SEC_FAIL_CMD_INF1_address_high_START  (0)
#define SOC_DMSS_ASI_SEC_FAIL_CMD_INF1_address_high_END    (7)
#define SOC_DMSS_ASI_SEC_FAIL_CMD_INF1_privileged_START    (16)
#define SOC_DMSS_ASI_SEC_FAIL_CMD_INF1_privileged_END      (16)
#define SOC_DMSS_ASI_SEC_FAIL_CMD_INF1_nonsecure_START     (17)
#define SOC_DMSS_ASI_SEC_FAIL_CMD_INF1_nonsecure_END       (17)
#define SOC_DMSS_ASI_SEC_FAIL_CMD_INF1_access_type_START   (20)
#define SOC_DMSS_ASI_SEC_FAIL_CMD_INF1_access_type_END     (20)


/*****************************************************************************
 结构名    : SOC_DMSS_ASI_SEC_FAIL_CMD_INF2_UNION
 结构说明  : ASI_SEC_FAIL_CMD_INF2 寄存器结构定义。地址偏移量:0x488+0x800*(asi_base)，初值:0x00000000，宽度:32
 寄存器说明: 记录首个越权命令的信息2
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  id  : 24; /* bit[0-23] : 中断状态清除前的首个越权命令的命令ID。 */
        unsigned int  mid : 8;  /* bit[24-31]: 中断状态清除前的首个越权命令的命令MasterID。 */
    } reg;
} SOC_DMSS_ASI_SEC_FAIL_CMD_INF2_UNION;
#endif
#define SOC_DMSS_ASI_SEC_FAIL_CMD_INF2_id_START   (0)
#define SOC_DMSS_ASI_SEC_FAIL_CMD_INF2_id_END     (23)
#define SOC_DMSS_ASI_SEC_FAIL_CMD_INF2_mid_START  (24)
#define SOC_DMSS_ASI_SEC_FAIL_CMD_INF2_mid_END    (31)


/*****************************************************************************
 结构名    : SOC_DMSS_ASI_SEC_ITCRG_UNION
 结构说明  : ASI_SEC_ITCRG 寄存器结构定义。地址偏移量:0x4C0+0x800*(asi_base)，初值:0x00000000，宽度:32
 寄存器说明: 集成测试控制寄存器
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  int_test_en : 1;  /* bit[0]   : 中断测试使能：
                                                      0：禁止；
                                                      1：使能。
                                                      注意：使能此寄存器后，模块的中断输出，由SEC_ITOP寄存器配置决定。 */
        unsigned int  reserved    : 31; /* bit[1-31]: 保留 */
    } reg;
} SOC_DMSS_ASI_SEC_ITCRG_UNION;
#endif
#define SOC_DMSS_ASI_SEC_ITCRG_int_test_en_START  (0)
#define SOC_DMSS_ASI_SEC_ITCRG_int_test_en_END    (0)


/*****************************************************************************
 结构名    : SOC_DMSS_ASI_SEC_ITIP_UNION
 结构说明  : ASI_SEC_ITIP 寄存器结构定义。地址偏移量:0x4C4+0x800*(asi_base)，初值:0x00000000，宽度:32
 寄存器说明: 集成测试输入寄存器
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  itip_secure_boot_lock : 1;  /* bit[0]   : 寄存器保护的锁定状态指示：
                                                                0：未锁定；
                                                                1：已锁定。 */
        unsigned int  reserved              : 31; /* bit[1-31]: 保留 */
    } reg;
} SOC_DMSS_ASI_SEC_ITIP_UNION;
#endif
#define SOC_DMSS_ASI_SEC_ITIP_itip_secure_boot_lock_START  (0)
#define SOC_DMSS_ASI_SEC_ITIP_itip_secure_boot_lock_END    (0)


/*****************************************************************************
 结构名    : SOC_DMSS_ASI_SEC_ITOP_UNION
 结构说明  : ASI_SEC_ITOP 寄存器结构定义。地址偏移量:0x4C8+0x800*(asi_base)，初值:0x00000000，宽度:32
 寄存器说明: 集成测试输出寄存器
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  itop_int : 1;  /* bit[0]   : 中断状态设置：
                                                   0：低电平；
                                                   1：高电平。
                                                   注意：只有当中断测试使能时，此寄存器设置有效。此时忽略模块内部产生的正常中断。 */
        unsigned int  reserved : 31; /* bit[1-31]: 保留 */
    } reg;
} SOC_DMSS_ASI_SEC_ITOP_UNION;
#endif
#define SOC_DMSS_ASI_SEC_ITOP_itop_int_START  (0)
#define SOC_DMSS_ASI_SEC_ITOP_itop_int_END    (0)


/*****************************************************************************
 结构名    : SOC_DMSS_ASI_SEC_RGN_MAP_UNION
 结构说明  : ASI_SEC_RGN_MAP 寄存器结构定义。地址偏移量:0x500+0x10*(sec_rgns)+0x800*(asi_base)，初值:0x00000000，宽度:32
 寄存器说明: 地址区域映射
            （被锁定条件：sucure_boot_lock信号被拉高过，且ld_region_map配置为1，且对应region在ld_regions的选定范围内。）
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  rgn_base_addr : 24; /* bit[0-23] : 各个区域的起始地址设置（高位部分）：
                                                         设置地址的[39:16]位。
                                                         注意：
                                                         1.rgn0不可配置，默认覆盖整个地址空间；
                                                         2.需保证exclusive命令访问的地址区域有响应的访问权限，否则exclusive命令无法被正常监控。 */
        unsigned int  rgn_size      : 6;  /* bit[24-29]: 当前区域的大小：
                                                         6'd15： 64KB；
                                                         6'd16：128KB；此时rgn_base_addr[ 0]必须配置为零；
                                                         6'd17：256KB；此时rgn_base_addr[ 1:0]必须配置为零；
                                                         6'd18：512KB；此时rgn_base_addr[ 2:0]必须配置为零；
                                                         6'd19： 1MB；此时rgn_base_addr[ 3:0]必须配置为零；
                                                         6'd20： 2MB；此时rgn_base_addr[ 4:0]必须配置为零；
                                                         6'd21： 4MB；此时rgn_base_addr[ 5:0]必须配置为零；
                                                         6'd22： 8MB；此时rgn_base_addr[ 6:0]必须配置为零；
                                                         6'd23： 16MB；此时rgn_base_addr[ 7:0]必须配置为零；
                                                         6'd24： 32MB；此时rgn_base_addr[ 8:0]必须配置为零；
                                                         6'd25： 64MB；此时rgn_base_addr[ 9:0]必须配置为零；
                                                         6'd26：128MB；此时rgn_base_addr[10:0]必须配置为零；
                                                         6'd27：256MB；此时rgn_base_addr[11:0]必须配置为零；
                                                         6'd28：512MB；此时rgn_base_addr[12:0]必须配置为零；
                                                         6'd29： 1GB；此时rgn_base_addr[13:0]必须配置为零；
                                                         6'd30： 2GB；此时rgn_base_addr[14:0]必须配置为零；
                                                         6'd31： 4GB；此时rgn_base_addr[15:0]必须配置为零；
                                                         6'd32： 8GB；此时rgn_base_addr[16:0]必须配置为零；
                                                         6'd33： 16GB；此时rgn_base_addr[17:0]必须配置为零；
                                                         6'd34： 32GB；此时rgn_base_addr[18:0]必须配置为零；
                                                         6'd35： 64GB；此时rgn_base_addr[19:0]必须配置为零；
                                                         6'd36：128GB；此时rgn_base_addr[20:0]必须配置为零；
                                                         6'd37：256GB；此时rgn_base_addr[21:0]必须配置为零；
                                                         6'd38：512GB；此时rgn_base_addr[22:0]必须配置为零；
                                                         6'd39：1TB； 此时rgn_base_addr[23:0]必须配置为零。
                                                         注意：
                                                         1.rgn0不可配置，默认覆盖整个地址空间；
                                                         2.为每个区域配置的区域大小，累加上其区域起始地址后，不允许超出总的地址空间大小。 */
        unsigned int  reserved      : 1;  /* bit[30]   : 保留 */
        unsigned int  rgn_en        : 1;  /* bit[31]   : 各个区域的使能控制：
                                                         0：不使能；
                                                         1：使能；
                                                         注意：region0不可配置，默认使能。 */
    } reg;
} SOC_DMSS_ASI_SEC_RGN_MAP_UNION;
#endif
#define SOC_DMSS_ASI_SEC_RGN_MAP_rgn_base_addr_START  (0)
#define SOC_DMSS_ASI_SEC_RGN_MAP_rgn_base_addr_END    (23)
#define SOC_DMSS_ASI_SEC_RGN_MAP_rgn_size_START       (24)
#define SOC_DMSS_ASI_SEC_RGN_MAP_rgn_size_END         (29)
#define SOC_DMSS_ASI_SEC_RGN_MAP_rgn_en_START         (31)
#define SOC_DMSS_ASI_SEC_RGN_MAP_rgn_en_END           (31)


/*****************************************************************************
 结构名    : SOC_DMSS_ASI_SEC_RGN_ATTRIB_UNION
 结构说明  : ASI_SEC_RGN_ATTRIB 寄存器结构定义。地址偏移量:0x504+0x10*(sec_rgns)+0x800*(asi_base)，初值:0x00000000，宽度:32
 寄存器说明: 各地址区域的权限属性设置
            （被锁定条件：sucure_boot_lock信号被拉高过，且ld_region_attrib配置为1，且对应region在ld_regions的选定范围内。）
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  sp             : 4;  /* bit[0-3]  : 当前区域的安全权限属性。
                                                          sp[3]：安全读属性；
                                                          sp[2]：安全写属性；
                                                          sp[1]：非安全读属性；
                                                          sp[0]：非安全写属性；
                                                          sp[n]=0：禁止访问；
                                                          sp[n]=1：允许访问。 */
        unsigned int  security_inv   : 1;  /* bit[4]    : 安全权限反转使能
                                                          0：禁止（若某region允许非安全的读/写，则也必定允许安全的读/写）
                                                          1：使能（非安全读/写和安全读/写权限之间无依赖关系，需各自设定） */
        unsigned int  reserved_0     : 3;  /* bit[5-7]  : 保留 */
        unsigned int  mid_en         : 1;  /* bit[8]    : MasterID匹配功能使能。
                                                          0：禁止；
                                                          1：使能。 */
        unsigned int  mid_inv        : 1;  /* bit[9]    : MasterID匹配权限反转
                                                          0：MID匹配成功的命令才可获得访问权限；
                                                          1：MID匹配失败的命令才可获得访问权限。 */
        unsigned int  reserved_1     : 6;  /* bit[10-15]: 保留 */
        unsigned int  subrgn_disable : 16; /* bit[16-31]: 当前区域的16个等大的子区域屏蔽。
                                                          subrgn_disable[n]=0：子区域n使能（当前子区域内的命令权限，取决于当前rgn）；
                                                          subrgn_disable[n]=1：子区域n屏蔽（当前子区域内的命令权限，取决于更低优先级rgn）。
                                                          注意：
                                                          rgn0不可设置子区域，默认覆盖整个地址空间。 */
    } reg;
} SOC_DMSS_ASI_SEC_RGN_ATTRIB_UNION;
#endif
#define SOC_DMSS_ASI_SEC_RGN_ATTRIB_sp_START              (0)
#define SOC_DMSS_ASI_SEC_RGN_ATTRIB_sp_END                (3)
#define SOC_DMSS_ASI_SEC_RGN_ATTRIB_security_inv_START    (4)
#define SOC_DMSS_ASI_SEC_RGN_ATTRIB_security_inv_END      (4)
#define SOC_DMSS_ASI_SEC_RGN_ATTRIB_mid_en_START          (8)
#define SOC_DMSS_ASI_SEC_RGN_ATTRIB_mid_en_END            (8)
#define SOC_DMSS_ASI_SEC_RGN_ATTRIB_mid_inv_START         (9)
#define SOC_DMSS_ASI_SEC_RGN_ATTRIB_mid_inv_END           (9)
#define SOC_DMSS_ASI_SEC_RGN_ATTRIB_subrgn_disable_START  (16)
#define SOC_DMSS_ASI_SEC_RGN_ATTRIB_subrgn_disable_END    (31)


/*****************************************************************************
 结构名    : SOC_DMSS_ASI_SEC_MID_WR_UNION
 结构说明  : ASI_SEC_MID_WR 寄存器结构定义。地址偏移量:0x508+0x10*(sec_rgns)+0x800*(asi_base)，初值:0xFFFFFFFF，宽度:32
 寄存器说明: 写命令匹配MasterID及其掩码
            （被锁定条件：sucure_boot_lock信号被拉高过，且ld_mid_wr配置为1，且对应region在ld_regions的选定范围内。）
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  mid_sel_wr : 32; /* bit[0-31]: MID的比特匹配选择（写命令）：
                                                     mid_sel_wr[n]=0：写命令MID的低五位为n时，此命令为MID匹配失败；
                                                     mid_sel_wr[n]=1：写命令MID的低五位为n时，此命令为MID匹配成功。
                                                     说明：
                                                     当使能MID匹配功能时，只有当MID成功匹配且获得安全权限时，相应的命令才允许通过。 */
    } reg;
} SOC_DMSS_ASI_SEC_MID_WR_UNION;
#endif
#define SOC_DMSS_ASI_SEC_MID_WR_mid_sel_wr_START  (0)
#define SOC_DMSS_ASI_SEC_MID_WR_mid_sel_wr_END    (31)


/*****************************************************************************
 结构名    : SOC_DMSS_ASI_SEC_MID_RD_UNION
 结构说明  : ASI_SEC_MID_RD 寄存器结构定义。地址偏移量:0x50C+0x10*(sec_rgns)+0x800*(asi_base)，初值:0xFFFFFFFF，宽度:32
 寄存器说明: 读命令匹配MasterID及其掩码
            （被锁定条件：sucure_boot_lock信号被拉高过，且ld_mid_rd配置为1，且对应region在ld_regions的选定范围内。）
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  mid_sel_rd : 32; /* bit[0-31]: MID的比特匹配选择（读命令）：
                                                     mid_sel_rd[n]=0：读命令MID的低五位为n时，此命令为MID匹配失败；
                                                     mid_sel_rd[n]=1：读命令MID的低五位为n时，此命令为MID匹配成功。
                                                     说明：
                                                     当使能MID匹配功能时，只有当MID成功匹配且获得安全权限时，相应的命令才允许通过。 */
    } reg;
} SOC_DMSS_ASI_SEC_MID_RD_UNION;
#endif
#define SOC_DMSS_ASI_SEC_MID_RD_mid_sel_rd_START  (0)
#define SOC_DMSS_ASI_SEC_MID_RD_mid_sel_rd_END    (31)


/*****************************************************************************
 结构名    : SOC_DMSS_ASI_DFX_MODULE_UNION
 结构说明  : ASI_DFX_MODULE 寄存器结构定义。地址偏移量:0x700+0x800*(asi_base)，初值:0x00000000，宽度:32
 寄存器说明: DFX：主要模块工作状态
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  asi_busy      : 1;  /* bit[0]    : 整个ASI的状态：
                                                         0：idle；
                                                         1：busy。
                                                         说明：
                                                         idle时，所有子模块均已idle（未考虑异步桥状态），且所有命令和数据均已处理完毕。 */
        unsigned int  asi_temp_busy : 1;  /* bit[1]    : 整个ASI的状态：
                                                         0：idle；
                                                         1：busy。
                                                         说明：
                                                         idle时，所有子模块均已idle（未考虑异步桥状态），但可能有读数据还未从后级模块返回。 */
        unsigned int  reserved_0    : 2;  /* bit[2-3]  : 保留 */
        unsigned int  ra_busy       : 1;  /* bit[4]    : ASI_RA模块的状态：
                                                         0：idle；
                                                         1：busy。 */
        unsigned int  ax_busy       : 1;  /* bit[5]    : ASI_AX模块的状态：
                                                         0：idle；
                                                         1：busy。 */
        unsigned int  cs_busy       : 1;  /* bit[6]    : ASI_CS模块的状态：
                                                         0：idle；
                                                         1：busy。 */
        unsigned int  wd_busy       : 1;  /* bit[7]    : ASI_WD模块的状态：
                                                         0：idle；
                                                         1：busy。 */
        unsigned int  b_busy        : 1;  /* bit[8]    : ASI_B模块的状态：
                                                         0：idle；
                                                         1：busy。 */
        unsigned int  rd_busy       : 1;  /* bit[9]    : ASI_RD模块的状态：
                                                         0：idle；
                                                         1：busy。 */
        unsigned int  fkrd_busy     : 1;  /* bit[10]   : ASI_FKRD模块的状态：
                                                         0：idle；
                                                         1：busy。 */
        unsigned int  sec_busy      : 1;  /* bit[11]   : ASI_SEC模块的状态：
                                                         0：idle；
                                                         1：busy。 */
        unsigned int  rdr_est_busy  : 1;  /* bit[12]   : RDR_EST模块的状态：
                                                         0：idle；
                                                         1：busy。 */
        unsigned int  rdr_buf_busy  : 1;  /* bit[13]   : RDR_BUF模块的状态：
                                                         0：idle；
                                                         1：busy。 */
        unsigned int  reserved_1    : 18; /* bit[14-31]: 保留 */
    } reg;
} SOC_DMSS_ASI_DFX_MODULE_UNION;
#endif
#define SOC_DMSS_ASI_DFX_MODULE_asi_busy_START       (0)
#define SOC_DMSS_ASI_DFX_MODULE_asi_busy_END         (0)
#define SOC_DMSS_ASI_DFX_MODULE_asi_temp_busy_START  (1)
#define SOC_DMSS_ASI_DFX_MODULE_asi_temp_busy_END    (1)
#define SOC_DMSS_ASI_DFX_MODULE_ra_busy_START        (4)
#define SOC_DMSS_ASI_DFX_MODULE_ra_busy_END          (4)
#define SOC_DMSS_ASI_DFX_MODULE_ax_busy_START        (5)
#define SOC_DMSS_ASI_DFX_MODULE_ax_busy_END          (5)
#define SOC_DMSS_ASI_DFX_MODULE_cs_busy_START        (6)
#define SOC_DMSS_ASI_DFX_MODULE_cs_busy_END          (6)
#define SOC_DMSS_ASI_DFX_MODULE_wd_busy_START        (7)
#define SOC_DMSS_ASI_DFX_MODULE_wd_busy_END          (7)
#define SOC_DMSS_ASI_DFX_MODULE_b_busy_START         (8)
#define SOC_DMSS_ASI_DFX_MODULE_b_busy_END           (8)
#define SOC_DMSS_ASI_DFX_MODULE_rd_busy_START        (9)
#define SOC_DMSS_ASI_DFX_MODULE_rd_busy_END          (9)
#define SOC_DMSS_ASI_DFX_MODULE_fkrd_busy_START      (10)
#define SOC_DMSS_ASI_DFX_MODULE_fkrd_busy_END        (10)
#define SOC_DMSS_ASI_DFX_MODULE_sec_busy_START       (11)
#define SOC_DMSS_ASI_DFX_MODULE_sec_busy_END         (11)
#define SOC_DMSS_ASI_DFX_MODULE_rdr_est_busy_START   (12)
#define SOC_DMSS_ASI_DFX_MODULE_rdr_est_busy_END     (12)
#define SOC_DMSS_ASI_DFX_MODULE_rdr_buf_busy_START   (13)
#define SOC_DMSS_ASI_DFX_MODULE_rdr_buf_busy_END     (13)


/*****************************************************************************
 结构名    : SOC_DMSS_ASI_DFX_FIFO_UNION
 结构说明  : ASI_DFX_FIFO 寄存器结构定义。地址偏移量:0x704+0x800*(asi_base)，初值:0x00550555，宽度:32
 寄存器说明: DFX：FIFO工作状态
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  ra_wfifo_st    : 2;  /* bit[0-1]  : ASI_RA模块中写数据FIFO的状态：
                                                          0x0：busy；
                                                          0x1：emtpy；
                                                          0x2：full；
                                                          0x3：reserved。 */
        unsigned int  wd_cmdfifo_st  : 2;  /* bit[2-3]  : ASI_WD模块中写命令FIFO的状态：
                                                          0x0：busy；
                                                          0x1：emtpy；
                                                          0x2：full；
                                                          0x3：reserved。 */
        unsigned int  b_respfifo_st  : 2;  /* bit[4-5]  : ASI_B模块中写响应FIFO的状态：
                                                          0x0：busy；
                                                          0x1：emtpy；
                                                          0x2：full；
                                                          0x3：reserved。 */
        unsigned int  rd_rfifo_st    : 2;  /* bit[6-7]  : ASI_RD模块中读数据FIFO的状态：
                                                          0x0：busy；
                                                          0x1：emtpy；
                                                          0x2：full；
                                                          0x3：reserved。 */
        unsigned int  rd_barfifo_st  : 2;  /* bit[8-9]  : ASI_RD模块中读barrier命令FIFO的状态：
                                                          0x0：busy；
                                                          0x1：emtpy；
                                                          0x2：full；
                                                          0x3：reserved。 */
        unsigned int  fkrd_fkfifo_st : 2;  /* bit[10-11]: ASI_FKRD模块中假读命令FIFO的状态：
                                                          0x0：busy；
                                                          0x1：emtpy；
                                                          0x2：full；
                                                          0x3：reserved。 */
        unsigned int  reserved_0     : 4;  /* bit[12-15]: 保留 */
        unsigned int  dmi0_wfifo_st  : 2;  /* bit[16-17]: DMI0模块中写数据FIFO的状态：
                                                          0x0：busy；
                                                          0x1：emtpy；
                                                          0x2：full；
                                                          0x3：reserved。 */
        unsigned int  dmi1_wfifo_st  : 2;  /* bit[18-19]: DMI1模块中写数据FIFO的状态：
                                                          0x0：busy；
                                                          0x1：emtpy；
                                                          0x2：full；
                                                          0x3：reserved。 */
        unsigned int  dmi2_wfifo_st  : 2;  /* bit[20-21]: DMI2模块中写数据FIFO的状态：
                                                          0x0：busy；
                                                          0x1：emtpy；
                                                          0x2：full；
                                                          0x3：reserved。 */
        unsigned int  dmi3_wfifo_st  : 2;  /* bit[22-23]: DMI3模块中写数据FIFO的状态：
                                                          0x0：busy；
                                                          0x1：emtpy；
                                                          0x2：full；
                                                          0x3：reserved。 */
        unsigned int  reserved_1     : 8;  /* bit[24-31]: 保留 */
    } reg;
} SOC_DMSS_ASI_DFX_FIFO_UNION;
#endif
#define SOC_DMSS_ASI_DFX_FIFO_ra_wfifo_st_START     (0)
#define SOC_DMSS_ASI_DFX_FIFO_ra_wfifo_st_END       (1)
#define SOC_DMSS_ASI_DFX_FIFO_wd_cmdfifo_st_START   (2)
#define SOC_DMSS_ASI_DFX_FIFO_wd_cmdfifo_st_END     (3)
#define SOC_DMSS_ASI_DFX_FIFO_b_respfifo_st_START   (4)
#define SOC_DMSS_ASI_DFX_FIFO_b_respfifo_st_END     (5)
#define SOC_DMSS_ASI_DFX_FIFO_rd_rfifo_st_START     (6)
#define SOC_DMSS_ASI_DFX_FIFO_rd_rfifo_st_END       (7)
#define SOC_DMSS_ASI_DFX_FIFO_rd_barfifo_st_START   (8)
#define SOC_DMSS_ASI_DFX_FIFO_rd_barfifo_st_END     (9)
#define SOC_DMSS_ASI_DFX_FIFO_fkrd_fkfifo_st_START  (10)
#define SOC_DMSS_ASI_DFX_FIFO_fkrd_fkfifo_st_END    (11)
#define SOC_DMSS_ASI_DFX_FIFO_dmi0_wfifo_st_START   (16)
#define SOC_DMSS_ASI_DFX_FIFO_dmi0_wfifo_st_END     (17)
#define SOC_DMSS_ASI_DFX_FIFO_dmi1_wfifo_st_START   (18)
#define SOC_DMSS_ASI_DFX_FIFO_dmi1_wfifo_st_END     (19)
#define SOC_DMSS_ASI_DFX_FIFO_dmi2_wfifo_st_START   (20)
#define SOC_DMSS_ASI_DFX_FIFO_dmi2_wfifo_st_END     (21)
#define SOC_DMSS_ASI_DFX_FIFO_dmi3_wfifo_st_START   (22)
#define SOC_DMSS_ASI_DFX_FIFO_dmi3_wfifo_st_END     (23)


/*****************************************************************************
 结构名    : SOC_DMSS_ASI_DFX_FSM_UNION
 结构说明  : ASI_DFX_FSM 寄存器结构定义。地址偏移量:0x708+0x800*(asi_base)，初值:0x00000001，宽度:32
 寄存器说明: DFX：状态机工作状态
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  cs_fsm_st : 8;  /* bit[0-7] : ASI_CS模块中命令状态机的跳转状态：
                                                    0x001：st_idle；
                                                    0x002：st_bar；
                                                    0x004：st_ex_chk；
                                                    0x008：st_ex_wait；
                                                    0x010：st_ex_rw；
                                                    0x020：st_nar；
                                                    0x040：st_wrap；
                                                    0x080：st_realign；
                                                    其他：reserve。 */
        unsigned int  reserved  : 24; /* bit[8-31]: 保留 */
    } reg;
} SOC_DMSS_ASI_DFX_FSM_UNION;
#endif
#define SOC_DMSS_ASI_DFX_FSM_cs_fsm_st_START  (0)
#define SOC_DMSS_ASI_DFX_FSM_cs_fsm_st_END    (7)


/*****************************************************************************
 结构名    : SOC_DMSS_ASI_DFX_WROSTD_UNION
 结构说明  : ASI_DFX_WROSTD 寄存器结构定义。地址偏移量:0x70C+0x800*(asi_base)，初值:0x00000000，宽度:32
 寄存器说明: DFX：写OSTD状态
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  wr_ostd_st : 5;  /* bit[0-4] : 写命令outstanding统计：
                                                     注意：
                                                     由于DMSS是以fast-response方式处理写命令的，因而此处统计的outstanding不能代表真正的写命令及写数据的处理状态。例如，此处统计为零时，不代表所有写命令或写数据已被后级模块处理完毕。 */
        unsigned int  reserved   : 27; /* bit[5-31]: 保留 */
    } reg;
} SOC_DMSS_ASI_DFX_WROSTD_UNION;
#endif
#define SOC_DMSS_ASI_DFX_WROSTD_wr_ostd_st_START  (0)
#define SOC_DMSS_ASI_DFX_WROSTD_wr_ostd_st_END    (4)


/*****************************************************************************
 结构名    : SOC_DMSS_ASI_DFX_RDR0_UNION
 结构说明  : ASI_DFX_RDR0 寄存器结构定义。地址偏移量:0x710+0x800*(asi_base)，初值:0x00000000，宽度:32
 寄存器说明: DFX：REORDER模块状态0
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  rdr_cmd_que_cnt_st : 8;  /* bit[0-7]  : REORDER模块命令队列中的命令个数。 */
        unsigned int  rdr_buf_cnt_st     : 8;  /* bit[8-15] : REORDER模块数据buffer中的数据burst个数。 */
        unsigned int  rdr_bid_use_cnt_st : 8;  /* bit[16-23]: REORDER模块已分配的buffer ID个数。 */
        unsigned int  reserved           : 8;  /* bit[24-31]: 保留 */
    } reg;
} SOC_DMSS_ASI_DFX_RDR0_UNION;
#endif
#define SOC_DMSS_ASI_DFX_RDR0_rdr_cmd_que_cnt_st_START  (0)
#define SOC_DMSS_ASI_DFX_RDR0_rdr_cmd_que_cnt_st_END    (7)
#define SOC_DMSS_ASI_DFX_RDR0_rdr_buf_cnt_st_START      (8)
#define SOC_DMSS_ASI_DFX_RDR0_rdr_buf_cnt_st_END        (15)
#define SOC_DMSS_ASI_DFX_RDR0_rdr_bid_use_cnt_st_START  (16)
#define SOC_DMSS_ASI_DFX_RDR0_rdr_bid_use_cnt_st_END    (23)


/*****************************************************************************
 结构名    : SOC_DMSS_ASI_DFX_RDR1_UNION
 结构说明  : ASI_DFX_RDR1 寄存器结构定义。地址偏移量:0x714+0x800*(asi_base)，初值:0x00000000，宽度:32
 寄存器说明: DFX：REORDER模块状态1
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  rdr_buf_rcv_done_st : 32; /* bit[0-31]: REORDER模块数据buffer中的数据burst是否接收完毕：
                                                              rdr_buf_rcv_done_st[n]=0：数据buffer第n个entry未分配burst或者对应burst数据未接收完毕；
                                                              rdr_buf_rcv_done_st[n]=1：数据buffer第n个entry对应burst数据接收完毕。 */
    } reg;
} SOC_DMSS_ASI_DFX_RDR1_UNION;
#endif
#define SOC_DMSS_ASI_DFX_RDR1_rdr_buf_rcv_done_st_START  (0)
#define SOC_DMSS_ASI_DFX_RDR1_rdr_buf_rcv_done_st_END    (31)


/*****************************************************************************
 结构名    : SOC_DMSS_ASI_DFX_INT_EN_UNION
 结构说明  : ASI_DFX_INT_EN 寄存器结构定义。地址偏移量:0x720+0x800*(asi_base)，初值:0x00000001，宽度:32
 寄存器说明: DFX：异常命令信息中断使能
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  dfx_int_en : 1;  /* bit[0]   : 异常命令的中断输出使能：
                                                     0：禁止；
                                                     1：使能。
                                                     说明：
                                                     1.当有异常访问时，可上报中断并记录异常命令的相关信息(查询ASI_DFX_ABNM_INFO寄存器)；
                                                     2.只能禁止中断输出，但相关寄存器还是会正常记录中断状态及异常命令信息。 */
        unsigned int  reserved   : 31; /* bit[1-31]: 保留 */
    } reg;
} SOC_DMSS_ASI_DFX_INT_EN_UNION;
#endif
#define SOC_DMSS_ASI_DFX_INT_EN_dfx_int_en_START  (0)
#define SOC_DMSS_ASI_DFX_INT_EN_dfx_int_en_END    (0)


/*****************************************************************************
 结构名    : SOC_DMSS_ASI_DFX_INT_STATUS_UNION
 结构说明  : ASI_DFX_INT_STATUS 寄存器结构定义。地址偏移量:0x724+0x800*(asi_base)，初值:0x00000000，宽度:32
 寄存器说明: DFX：异常命令信息中断
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  dfx_int_status : 1;  /* bit[0]   : 中断状态指示：
                                                         0：中断未产生；
                                                         1：中断已产生。 */
        unsigned int  reserved       : 31; /* bit[1-31]: 保留 */
    } reg;
} SOC_DMSS_ASI_DFX_INT_STATUS_UNION;
#endif
#define SOC_DMSS_ASI_DFX_INT_STATUS_dfx_int_status_START  (0)
#define SOC_DMSS_ASI_DFX_INT_STATUS_dfx_int_status_END    (0)


/*****************************************************************************
 结构名    : SOC_DMSS_ASI_DFX_ABNM_INF_UNION
 结构说明  : ASI_DFX_ABNM_INF 寄存器结构定义。地址偏移量:0x728+0x800*(asi_base)，初值:0x00000000，宽度:32
 寄存器说明: DFX：异常命令信息记录
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  abnm_link_err  : 1;  /* bit[0]    : 路由错误：命令被发往了未连接的DMI（可能会导致系统挂死）。 */
        unsigned int  abnm_rdr_split : 1;  /* bit[1]    : 保序错误：未例化保序模块的情况下，读命令被拆分（可能会导致系统挂死）。 */
        unsigned int  abnm_ex_len    : 1;  /* bit[2]    : 违反命令约束：收到了非INCR1的exclusive命令（可能会导致exclusive命令无效）。 */
        unsigned int  abnm_nar_wrap  : 1;  /* bit[3]    : 违反命令约束：收到了narrow类型的WRAP命令（可能会导致系统挂死）。 */
        unsigned int  abnm_fix       : 1;  /* bit[4]    : 违反命令约束：收到了FIX类型的命令（强制转换成INCR命令处理）。 */
        unsigned int  abnm_len16     : 1;  /* bit[5]    : 违反命令约束：收到了大于burst16的命令（可能会导致系统挂死）。 */
        unsigned int  reserved       : 10; /* bit[6-15] : 保留 */
        unsigned int  abnm_cmd_mid   : 15; /* bit[16-30]: 首个异常命令的MasterID：
                                                          注意：
                                                          当中断清除，并产生下一次新的中断时，此寄存器信息才会被更新。 */
        unsigned int  abnm_cmd_type  : 1;  /* bit[31]   : 首个异常命令的读写类型：
                                                          0：读命令；
                                                          1：写命令。
                                                          注意：
                                                          当中断清除，并产生下一次新的中断时，此寄存器信息才会被更新。 */
    } reg;
} SOC_DMSS_ASI_DFX_ABNM_INF_UNION;
#endif
#define SOC_DMSS_ASI_DFX_ABNM_INF_abnm_link_err_START   (0)
#define SOC_DMSS_ASI_DFX_ABNM_INF_abnm_link_err_END     (0)
#define SOC_DMSS_ASI_DFX_ABNM_INF_abnm_rdr_split_START  (1)
#define SOC_DMSS_ASI_DFX_ABNM_INF_abnm_rdr_split_END    (1)
#define SOC_DMSS_ASI_DFX_ABNM_INF_abnm_ex_len_START     (2)
#define SOC_DMSS_ASI_DFX_ABNM_INF_abnm_ex_len_END       (2)
#define SOC_DMSS_ASI_DFX_ABNM_INF_abnm_nar_wrap_START   (3)
#define SOC_DMSS_ASI_DFX_ABNM_INF_abnm_nar_wrap_END     (3)
#define SOC_DMSS_ASI_DFX_ABNM_INF_abnm_fix_START        (4)
#define SOC_DMSS_ASI_DFX_ABNM_INF_abnm_fix_END          (4)
#define SOC_DMSS_ASI_DFX_ABNM_INF_abnm_len16_START      (5)
#define SOC_DMSS_ASI_DFX_ABNM_INF_abnm_len16_END        (5)
#define SOC_DMSS_ASI_DFX_ABNM_INF_abnm_cmd_mid_START    (16)
#define SOC_DMSS_ASI_DFX_ABNM_INF_abnm_cmd_mid_END      (30)
#define SOC_DMSS_ASI_DFX_ABNM_INF_abnm_cmd_type_START   (31)
#define SOC_DMSS_ASI_DFX_ABNM_INF_abnm_cmd_type_END     (31)


/*****************************************************************************
 结构名    : SOC_DMSS_ASI_DFX_LOAD_UNION
 结构说明  : ASI_DFX_LOAD 寄存器结构定义。地址偏移量:0x760+0x800*(asi_base)，初值:0x00000000，宽度:32
 寄存器说明: DFX：仿真流量冲击状态
            （若RTL中配置DMSS_SIM_DFX_EN为0（通常ASIC版本配置为0，FPGA和EMULATOR版本定义为1），则此寄存器不存在）
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  ra_wfifo_load_st    : 1;  /* bit[0]    : ASI_RA模块中写数据FIFO的仿真负载状态：
                                                               0x0：fifo未达到过full状态；
                                                               0x1：fifo达到过full状态。 */
        unsigned int  wd_cmdfifo_load_st  : 1;  /* bit[1]    : ASI_WD模块中写命令FIFO的仿真负载状态：
                                                               0x0：fifo未达到过full状态；
                                                               0x1：fifo达到过full状态。 */
        unsigned int  b_respfifo_load_st  : 1;  /* bit[2]    : ASI_B模块中写响应FIFO的仿真负载状态：
                                                               0x0：fifo未达到过full状态；
                                                               0x1：fifo达到过full状态。 */
        unsigned int  rd_rfifo_load_st    : 1;  /* bit[3]    : ASI_RD模块中读数据FIFO的仿真负载状态：
                                                               0x0：fifo未达到过full状态；
                                                               0x1：fifo达到过full状态。 */
        unsigned int  rd_barfifo_load_st  : 1;  /* bit[4]    : ASI_RD模块中读barrier命令FIFO的仿真负载状态：
                                                               0x0：fifo未达到过full状态；
                                                               0x1：fifo达到过full状态。 */
        unsigned int  fkrd_fkfifo_load_st : 1;  /* bit[5]    : ASI_FKRD模块中假读命令FIFO的仿真负载状态：
                                                               0x0：fifo未达到过full状态；
                                                               0x1：fifo达到过full状态。 */
        unsigned int  rdr_cmd_que_load_st : 1;  /* bit[6]    : REORDER模块中命令队列的仿真负载状态：
                                                               0x0：命令队列未达到过full状态；
                                                               0x1：命令队列达到过full状态。 */
        unsigned int  rdr_bid_use_load_st : 1;  /* bit[7]    : REORDER模块中已分配的buffer ID个数的仿真负载状态：
                                                               0x0：未达到过buffer ID分配耗尽状态；
                                                               0x1：达到过buffer ID分配耗尽状态。 */
        unsigned int  dmi0_wfifo_load_st  : 1;  /* bit[8]    : DMI0模块中写数据FIFO的仿真负载状态：
                                                               0x0：fifo未达到过full状态；
                                                               0x1：fifo达到过full状态。 */
        unsigned int  dmi1_wfifo_load_st  : 1;  /* bit[9]    : DMI1模块中写数据FIFO的仿真负载状态：
                                                               0x0：fifo未达到过full状态；
                                                               0x1：fifo达到过full状态。 */
        unsigned int  dmi2_wfifo_load_st  : 1;  /* bit[10]   : DMI2模块中写数据FIFO的仿真负载状态：
                                                               0x0：fifo未达到过full状态；
                                                               0x1：fifo达到过full状态。 */
        unsigned int  dmi3_wfifo_load_st  : 1;  /* bit[11]   : DMI3模块中写数据FIFO的仿真负载状态：
                                                               0x0：fifo未达到过full状态；
                                                               0x1：fifo达到过full状态。 */
        unsigned int  reserved            : 20; /* bit[12-31]: 保留 */
    } reg;
} SOC_DMSS_ASI_DFX_LOAD_UNION;
#endif
#define SOC_DMSS_ASI_DFX_LOAD_ra_wfifo_load_st_START     (0)
#define SOC_DMSS_ASI_DFX_LOAD_ra_wfifo_load_st_END       (0)
#define SOC_DMSS_ASI_DFX_LOAD_wd_cmdfifo_load_st_START   (1)
#define SOC_DMSS_ASI_DFX_LOAD_wd_cmdfifo_load_st_END     (1)
#define SOC_DMSS_ASI_DFX_LOAD_b_respfifo_load_st_START   (2)
#define SOC_DMSS_ASI_DFX_LOAD_b_respfifo_load_st_END     (2)
#define SOC_DMSS_ASI_DFX_LOAD_rd_rfifo_load_st_START     (3)
#define SOC_DMSS_ASI_DFX_LOAD_rd_rfifo_load_st_END       (3)
#define SOC_DMSS_ASI_DFX_LOAD_rd_barfifo_load_st_START   (4)
#define SOC_DMSS_ASI_DFX_LOAD_rd_barfifo_load_st_END     (4)
#define SOC_DMSS_ASI_DFX_LOAD_fkrd_fkfifo_load_st_START  (5)
#define SOC_DMSS_ASI_DFX_LOAD_fkrd_fkfifo_load_st_END    (5)
#define SOC_DMSS_ASI_DFX_LOAD_rdr_cmd_que_load_st_START  (6)
#define SOC_DMSS_ASI_DFX_LOAD_rdr_cmd_que_load_st_END    (6)
#define SOC_DMSS_ASI_DFX_LOAD_rdr_bid_use_load_st_START  (7)
#define SOC_DMSS_ASI_DFX_LOAD_rdr_bid_use_load_st_END    (7)
#define SOC_DMSS_ASI_DFX_LOAD_dmi0_wfifo_load_st_START   (8)
#define SOC_DMSS_ASI_DFX_LOAD_dmi0_wfifo_load_st_END     (8)
#define SOC_DMSS_ASI_DFX_LOAD_dmi1_wfifo_load_st_START   (9)
#define SOC_DMSS_ASI_DFX_LOAD_dmi1_wfifo_load_st_END     (9)
#define SOC_DMSS_ASI_DFX_LOAD_dmi2_wfifo_load_st_START   (10)
#define SOC_DMSS_ASI_DFX_LOAD_dmi2_wfifo_load_st_END     (10)
#define SOC_DMSS_ASI_DFX_LOAD_dmi3_wfifo_load_st_START   (11)
#define SOC_DMSS_ASI_DFX_LOAD_dmi3_wfifo_load_st_END     (11)


/*****************************************************************************
 结构名    : SOC_DMSS_GLB_RTL_VER_UNION
 结构说明  : GLB_RTL_VER 寄存器结构定义。地址偏移量:0x6000，初值:0x01000000，宽度:32
 寄存器说明: 代码版本信息
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  rtl_tag  : 8;  /* bit[0-7]  : RTL的设计TAG编号。 */
        unsigned int  reserved_0: 8;  /* bit[8-15] : 保留 */
        unsigned int  version  : 12; /* bit[16-27]: 版本编号：
                                                    0x100：HiDMSSV100；
                                                    0x110：HiDMSSV110 */
        unsigned int  reserved_1: 4;  /* bit[28-31]: 保留 */
    } reg;
} SOC_DMSS_GLB_RTL_VER_UNION;
#endif
#define SOC_DMSS_GLB_RTL_VER_rtl_tag_START   (0)
#define SOC_DMSS_GLB_RTL_VER_rtl_tag_END     (7)
#define SOC_DMSS_GLB_RTL_VER_version_START   (16)
#define SOC_DMSS_GLB_RTL_VER_version_END     (27)


/*****************************************************************************
 结构名    : SOC_DMSS_GLB_RTL_INF0_UNION
 结构说明  : GLB_RTL_INF0 寄存器结构定义。地址偏移量:0x6004，初值:0x00000000，宽度:32
 寄存器说明: 代码配置信息0
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  rtl_addr_width     : 4;  /* bit[0-3]  : AXI总线地址位宽：
                                                              0:32bits；
                                                              1:33bits；
                                                              2:34bits；
                                                              3:35bits；
                                                              4:36bits；
                                                              5:37bits；
                                                              6:38bits；
                                                              7:39bits；
                                                              8:40bits；
                                                              其它：reserved。 */
        unsigned int  rtl_id_width       : 5;  /* bit[4-8]  : AXI命令ID位宽：
                                                              0:reserved；
                                                              1:1bits；
                                                              2:2bits；
                                                              ……
                                                              31:31bits。 */
        unsigned int  reserved_0         : 3;  /* bit[9-11] : 保留 */
        unsigned int  rtl_mid_width      : 4;  /* bit[12-15]: Master ID位宽：
                                                              0:reserved；
                                                              1:1bits；
                                                              2:2bits；
                                                              ……
                                                              15:15bits。 */
        unsigned int  rtl_dmi_num        : 1;  /* bit[16]   : DMI(DDRC Master Interface)个数：
                                                              0：1个DMI；
                                                              1：2个DMI。 */
        unsigned int  reserved_1         : 1;  /* bit[17]   : 保留 */
        unsigned int  rtl_ch_num_pre_dmi : 1;  /* bit[18]   : 每个DMI对接的通道个数：
                                                              0：1 channel per DMI；
                                                              1：2 channel per DMI。 */
        unsigned int  reserved_2         : 1;  /* bit[19]   : 保留 */
        unsigned int  rtl_asi_num        : 4;  /* bit[20-23]: ASI（AXI Slave Interface）个数：
                                                              0x0： 1个ASI；
                                                              ……
                                                              0xB：12个ASI；
                                                              其它：reserved。 */
        unsigned int  rtl_exclusive_num  : 6;  /* bit[24-29]: 可同时监视的不同exclusive命令的最大个数：
                                                              0x00：不支持exclusive命令；
                                                              0x01：1个；
                                                              0x02：2个；
                                                              ……
                                                              0x1F：31个；
                                                              0x20：32个；
                                                              其它：reserved。 */
        unsigned int  reserved_3         : 2;  /* bit[30-31]: 保留 */
    } reg;
} SOC_DMSS_GLB_RTL_INF0_UNION;
#endif
#define SOC_DMSS_GLB_RTL_INF0_rtl_addr_width_START      (0)
#define SOC_DMSS_GLB_RTL_INF0_rtl_addr_width_END        (3)
#define SOC_DMSS_GLB_RTL_INF0_rtl_id_width_START        (4)
#define SOC_DMSS_GLB_RTL_INF0_rtl_id_width_END          (8)
#define SOC_DMSS_GLB_RTL_INF0_rtl_mid_width_START       (12)
#define SOC_DMSS_GLB_RTL_INF0_rtl_mid_width_END         (15)
#define SOC_DMSS_GLB_RTL_INF0_rtl_dmi_num_START         (16)
#define SOC_DMSS_GLB_RTL_INF0_rtl_dmi_num_END           (16)
#define SOC_DMSS_GLB_RTL_INF0_rtl_ch_num_pre_dmi_START  (18)
#define SOC_DMSS_GLB_RTL_INF0_rtl_ch_num_pre_dmi_END    (18)
#define SOC_DMSS_GLB_RTL_INF0_rtl_asi_num_START         (20)
#define SOC_DMSS_GLB_RTL_INF0_rtl_asi_num_END           (23)
#define SOC_DMSS_GLB_RTL_INF0_rtl_exclusive_num_START   (24)
#define SOC_DMSS_GLB_RTL_INF0_rtl_exclusive_num_END     (29)


/*****************************************************************************
 结构名    : SOC_DMSS_GLB_RTL_INF1_UNION
 结构说明  : GLB_RTL_INF1 寄存器结构定义。地址偏移量:0x6008，初值:0x00000000，宽度:32
 寄存器说明: 代码配置信息1
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  rtl_rbuf_buf_num : 6;  /* bit[0-5] : RBUF模块的数据buffer深度：
                                                           0：未例化RBUF，使用了cross bar的交换结构；
                                                           1：2 read burst；
                                                           2：3 read burst；
                                                           ……
                                                           63：64 read burst。 */
        unsigned int  reserved         : 26; /* bit[6-31]: 保留 */
    } reg;
} SOC_DMSS_GLB_RTL_INF1_UNION;
#endif
#define SOC_DMSS_GLB_RTL_INF1_rtl_rbuf_buf_num_START  (0)
#define SOC_DMSS_GLB_RTL_INF1_rtl_rbuf_buf_num_END    (5)


/*****************************************************************************
 结构名    : SOC_DMSS_GLB_RAM_TMOD_UNION
 结构说明  : GLB_RAM_TMOD 寄存器结构定义。地址偏移量:0x6018，初值:0x00000000，宽度:32
 寄存器说明: MEMORY配置
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  ram_tmod : 16; /* bit[0-15] : 根据MEMORY的不同类型及工艺配置。 */
        unsigned int  reserved : 16; /* bit[16-31]: 保留 */
    } reg;
} SOC_DMSS_GLB_RAM_TMOD_UNION;
#endif
#define SOC_DMSS_GLB_RAM_TMOD_ram_tmod_START  (0)
#define SOC_DMSS_GLB_RAM_TMOD_ram_tmod_END    (15)


/*****************************************************************************
 结构名    : SOC_DMSS_GLB_CFG_LOCK_UNION
 结构说明  : GLB_CFG_LOCK 寄存器结构定义。地址偏移量:0x6020，初值:0x00000000，宽度:32
 寄存器说明: 配置寄存器锁定
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  cfg_lock        : 1;  /* bit[0]    : 锁定DMSS内所有的寄存器配置模块(含GLB和全部ASI内的配置寄存器)：
                                                           0：不锁定；
                                                           1：锁定（除本寄存器外的所有配置寄存器皆无法有效访问，可防止误操作并降低功耗；若此时强行读取，则可能读出未锁定时的最后一次寄存器读取值）。 */
        unsigned int  reserved_0      : 15; /* bit[1-15] : 保留 */
        unsigned int  cfg_lock_int_en : 1;  /* bit[16]   : 寄存器锁定访问中断使能：
                                                           0：禁止；
                                                           1：使能。
                                                           说明：
                                                           当寄存器锁定时，若有对寄存器的配置访问，则产生寄存器锁定访问中断。中断状态在GLB_INT_STATUS寄存器中。 */
        unsigned int  reserved_1      : 15; /* bit[17-31]: 保留 */
    } reg;
} SOC_DMSS_GLB_CFG_LOCK_UNION;
#endif
#define SOC_DMSS_GLB_CFG_LOCK_cfg_lock_START         (0)
#define SOC_DMSS_GLB_CFG_LOCK_cfg_lock_END           (0)
#define SOC_DMSS_GLB_CFG_LOCK_cfg_lock_int_en_START  (16)
#define SOC_DMSS_GLB_CFG_LOCK_cfg_lock_int_en_END    (16)


/*****************************************************************************
 结构名    : SOC_DMSS_GLB_DYN_CKG_UNION
 结构说明  : GLB_DYN_CKG 寄存器结构定义。地址偏移量:0x6024，初值:0x00000000，宽度:32
 寄存器说明: 动态时钟门控
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  ckg_byp_rbuf_src   : 1;  /* bit[0]   : RBUF_SRC模块的动态时钟门控：
                                                             0：模块idle时，自动关闭时钟；
                                                             1：时钟常开。 */
        unsigned int  ckg_byp_rbuf_dst   : 1;  /* bit[1]   : RBUF_DST模块的动态时钟门控：
                                                             0：模块idle时，自动关闭时钟；
                                                             1：时钟常开。 */
        unsigned int  ckg_byp_dmi_wdfifo : 1;  /* bit[2]   : DMI模块中写数据fifo的动态时钟门控：
                                                             0：模块idle时，自动关闭时钟；
                                                             1：时钟常开。 */
        unsigned int  ckg_byp_dmi        : 1;  /* bit[3]   : DMI模块的动态时钟门控：
                                                             0：模块idle时，自动关闭时钟；
                                                             1：时钟常开。 */
        unsigned int  ckg_byp_dmi_dcq    : 1;  /* bit[4]   : DMI模块中DCQ的动态时钟门控：
                                                             0：模块idle时，自动关闭时钟；
                                                             1：时钟常开。 */
        unsigned int  reserved           : 27; /* bit[5-31]: 保留 */
    } reg;
} SOC_DMSS_GLB_DYN_CKG_UNION;
#endif
#define SOC_DMSS_GLB_DYN_CKG_ckg_byp_rbuf_src_START    (0)
#define SOC_DMSS_GLB_DYN_CKG_ckg_byp_rbuf_src_END      (0)
#define SOC_DMSS_GLB_DYN_CKG_ckg_byp_rbuf_dst_START    (1)
#define SOC_DMSS_GLB_DYN_CKG_ckg_byp_rbuf_dst_END      (1)
#define SOC_DMSS_GLB_DYN_CKG_ckg_byp_dmi_wdfifo_START  (2)
#define SOC_DMSS_GLB_DYN_CKG_ckg_byp_dmi_wdfifo_END    (2)
#define SOC_DMSS_GLB_DYN_CKG_ckg_byp_dmi_START         (3)
#define SOC_DMSS_GLB_DYN_CKG_ckg_byp_dmi_END           (3)
#define SOC_DMSS_GLB_DYN_CKG_ckg_byp_dmi_dcq_START     (4)
#define SOC_DMSS_GLB_DYN_CKG_ckg_byp_dmi_dcq_END       (4)


/*****************************************************************************
 结构名    : SOC_DMSS_GLB_INT_STATUS_UNION
 结构说明  : GLB_INT_STATUS 寄存器结构定义。地址偏移量:0x6030，初值:0x00000000，宽度:32
 寄存器说明: 全局中断状态查看
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  asi_sec_int   : 12; /* bit[0-11] : 安全功能中断状态：
                                                         asi_sec_int[n]=1：安全中断来自ASIn。
                                                         说明：
                                                         1.中断状态可在对应ASI的寄存器ASI_SEC_INT_STATUS查看；
                                                         2.中断使能可在对应ASI的寄存器ASI_SEC_INT_EN中配置。 */
        unsigned int  reserved_0    : 4;  /* bit[12-15]: 保留 */
        unsigned int  asi_dfx_int   : 12; /* bit[16-27]: DFX功能中断状态：
                                                         asi_dfx_int[n]=1：DFX中断来自ASIn。
                                                         说明：
                                                         1.中断状态可在对应ASI的寄存器ASI_DFX_INT_STATUS查看；
                                                         2.中断使能可在对应ASI的寄存器ASI_DFX_INT_EN中配置。 */
        unsigned int  cfg_lock_int  : 1;  /* bit[28]   : 寄存器锁定访问中断：
                                                         说明：
                                                         1.当寄存器锁定时，若有对寄存器的配置访问，则产生寄存器锁定访问中断；
                                                         2.中断使能可在寄存器GLB_CFG_LOCK中配置。 */
        unsigned int  pri_allow_int : 1;  /* bit[29]   : 允许优先级跳变中断：
                                                         说明：
                                                         1.中断状态可在寄存器GLB_DFX_DCQ中查看；
                                                         2.中断使能可在寄存器GLB_DCQ_INT_EN中配置。 */
        unsigned int  reserved_1    : 2;  /* bit[30-31]: 保留 */
    } reg;
} SOC_DMSS_GLB_INT_STATUS_UNION;
#endif
#define SOC_DMSS_GLB_INT_STATUS_asi_sec_int_START    (0)
#define SOC_DMSS_GLB_INT_STATUS_asi_sec_int_END      (11)
#define SOC_DMSS_GLB_INT_STATUS_asi_dfx_int_START    (16)
#define SOC_DMSS_GLB_INT_STATUS_asi_dfx_int_END      (27)
#define SOC_DMSS_GLB_INT_STATUS_cfg_lock_int_START   (28)
#define SOC_DMSS_GLB_INT_STATUS_cfg_lock_int_END     (28)
#define SOC_DMSS_GLB_INT_STATUS_pri_allow_int_START  (29)
#define SOC_DMSS_GLB_INT_STATUS_pri_allow_int_END    (29)


/*****************************************************************************
 结构名    : SOC_DMSS_GLB_INT_CLEAR_UNION
 结构说明  : GLB_INT_CLEAR 寄存器结构定义。地址偏移量:0x6034，初值:0x00000000，宽度:32
 寄存器说明: 全局中断状态清除
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  asi_sec_int_clear   : 12; /* bit[0-11] : 对应bit写1，可清除对应ASI的安全功能中断状态：
                                                               asi_sec_int_clear[n]=1：清除的安全功能中断状态来自ASIn。 */
        unsigned int  reserved_0          : 4;  /* bit[12-15]: 保留 */
        unsigned int  asi_dfx_int_clear   : 12; /* bit[16-27]: 对应bit写1，可清除对应ASI的DFX功能中断状态：
                                                               asi_dfx_int_clear[n]=1：清除的DFX中断状态来自ASIn。 */
        unsigned int  cfg_lock_int_clear  : 1;  /* bit[28]   : 对应bit写1，可清除寄存器锁定访问中断。 */
        unsigned int  pri_allow_int_clear : 1;  /* bit[29]   : 对应bit写1，可清除允许优先级跳变中断。 */
        unsigned int  reserved_1          : 2;  /* bit[30-31]: 保留 */
    } reg;
} SOC_DMSS_GLB_INT_CLEAR_UNION;
#endif
#define SOC_DMSS_GLB_INT_CLEAR_asi_sec_int_clear_START    (0)
#define SOC_DMSS_GLB_INT_CLEAR_asi_sec_int_clear_END      (11)
#define SOC_DMSS_GLB_INT_CLEAR_asi_dfx_int_clear_START    (16)
#define SOC_DMSS_GLB_INT_CLEAR_asi_dfx_int_clear_END      (27)
#define SOC_DMSS_GLB_INT_CLEAR_cfg_lock_int_clear_START   (28)
#define SOC_DMSS_GLB_INT_CLEAR_cfg_lock_int_clear_END     (28)
#define SOC_DMSS_GLB_INT_CLEAR_pri_allow_int_clear_START  (29)
#define SOC_DMSS_GLB_INT_CLEAR_pri_allow_int_clear_END    (29)


/*****************************************************************************
 结构名    : SOC_DMSS_GLB_EXCLU_UNION
 结构说明  : GLB_EXCLU 寄存器结构定义。地址偏移量:0x6040，初值:0x00000001，宽度:32
 寄存器说明: exclusive命令配置
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  exclu_en : 1;  /* bit[0]   : exclusive命令使能：
                                                   0：禁止：忽略exclusive命令，当做普通命令处理；
                                                   1：使能：支持exclusive命令。 */
        unsigned int  reserved : 31; /* bit[1-31]: 保留 */
    } reg;
} SOC_DMSS_GLB_EXCLU_UNION;
#endif
#define SOC_DMSS_GLB_EXCLU_exclu_en_START  (0)
#define SOC_DMSS_GLB_EXCLU_exclu_en_END    (0)


/*****************************************************************************
 结构名    : SOC_DMSS_GLB_ADDR_INTLV_UNION
 结构说明  : GLB_ADDR_INTLV 寄存器结构定义。地址偏移量:0x6100，初值:0x00000000，宽度:32
 寄存器说明: 全局地址交织模式
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  intlv_mode    : 1;  /* bit[0]   : 通道映射模式：
                                                        0x0：双通道交织；
                                                        0x1：四通道交织。
                                                        注意：
                                                        此寄存器只能在系统初始化时静态配置。 */
        unsigned int  reserved_0    : 3;  /* bit[1-3] : 保留 */
        unsigned int  intlv_granule : 3;  /* bit[4-6] : 地址交织粒度：
                                                        0x0：128Byte；
                                                        0x1：256Byte；
                                                        0x2：512Byte；
                                                        0x3： 1KByte；
                                                        0x4： 2KByte；
                                                        0x5： 4KByte；
                                                        注意：
                                                        1.命令以此粒度为边界，被交替分发到多个通道；
                                                        2.地址交织粒度必须大于等于地址对齐粒度(由RTL宏定义)。
                                                        3.此寄存器只能在系统初始化时静态配置。 */
        unsigned int  reserved_1    : 25; /* bit[7-31]: 保留 */
    } reg;
} SOC_DMSS_GLB_ADDR_INTLV_UNION;
#endif
#define SOC_DMSS_GLB_ADDR_INTLV_intlv_mode_START     (0)
#define SOC_DMSS_GLB_ADDR_INTLV_intlv_mode_END       (0)
#define SOC_DMSS_GLB_ADDR_INTLV_intlv_granule_START  (4)
#define SOC_DMSS_GLB_ADDR_INTLV_intlv_granule_END    (6)


/*****************************************************************************
 结构名    : SOC_DMSS_GLB_ADDR_SCRMBL_UNION
 结构说明  : GLB_ADDR_SCRMBL 寄存器结构定义。地址偏移量:0x6110，初值:0x00000000，宽度:32
 寄存器说明: 全局地址加扰模式
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  bnk_scrmbl : 4;  /* bit[0-3] : BANK地址扰码模式：
                                                     0：无扰码；
                                                     1：addr[14:12] = addr[14:12] xor addr[19:17]（DDR pagesize=4KB）
                                                     2：addr[14:12] = addr[14:12] xor addr[20:18]（DDR pagesize=4KB）
                                                     3：addr[14:12] = addr[14:12] xor addr[21:19]（DDR pagesize=4KB）
                                                     4：addr[14:12] = addr[14:12] xor addr[22:20]（DDR pagesize=4KB）
                                                     5：addr[13:11] = addr[13:11] xor addr[18:16]（DDR pagesize=2KB）
                                                     6：addr[13:11] = addr[13:11] xor addr[19:17]（DDR pagesize=2KB）
                                                     7：addr[13:11] = addr[13:11] xor addr[20:18]（DDR pagesize=2KB）
                                                     8：addr[13:11] = addr[13:11] xor addr[21:19]（DDR pagesize=2KB）
                                                     9~15：reserved
                                                     说明：
                                                     1.此处的addr，是抽取交织位之后的通道内地址；
                                                     2.加扰规则为RTL定制。
                                                     3.此寄存器只能在系统初始化时静态配置。 */
        unsigned int  reserved   : 28; /* bit[4-31]: 保留 */
    } reg;
} SOC_DMSS_GLB_ADDR_SCRMBL_UNION;
#endif
#define SOC_DMSS_GLB_ADDR_SCRMBL_bnk_scrmbl_START  (0)
#define SOC_DMSS_GLB_ADDR_SCRMBL_bnk_scrmbl_END    (3)


/*****************************************************************************
 结构名    : SOC_DMSS_GLB_RBUF_TRSFR_WL0_UNION
 结构说明  : GLB_RBUF_TRSFR_WL0 寄存器结构定义。地址偏移量:0x6140，初值:0x00000000，宽度:32
 寄存器说明: RBUF的传输起始水线配置0
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  reserved_0    : 4;  /* bit[0-3]  : 保留 */
        unsigned int  trsfr_wl_bl_2 : 1;  /* bit[4]    : 当RBUF收到burst length为2（transfer总数为2）的读数据时，开始提传输请求的水线配置：
                                                         0x0：每接收积攒到1个transfer或该命令所有transfer时，便提起传输请求；
                                                         0x1：每接收积攒到2个transfer或该命令所有transfer时，便提起传输请求。
                                                         说明：
                                                         1.此配置只在当前数据所属MID的间插模式被配置为模式三时才生效。间插模式的配置请参考ASI部分的ASI_RBUF_INTLV寄存器；
                                                         2.配置为间插模式三时，每个长度为burst2的数据，每当在RBUF中积攒的transfer个数达到此寄存器配置的水线时，才能开始请求数据传输，直到当前burst全部传输完毕；在传输中途，若已接收的transfer已传输完毕而剩余数据还未接收到，则可间插传输其它通路的数据。 */
        unsigned int  reserved_1    : 3;  /* bit[5-7]  : 保留 */
        unsigned int  trsfr_wl_bl_3 : 2;  /* bit[8-9]  : 同wl_bl2的配置。 */
        unsigned int  reserved_2    : 2;  /* bit[10-11]: 保留 */
        unsigned int  trsfr_wl_bl_4 : 2;  /* bit[12-13]: 同wl_bl2的配置。 */
        unsigned int  reserved_3    : 2;  /* bit[14-15]: 保留 */
        unsigned int  trsfr_wl_bl_5 : 3;  /* bit[16-18]: 同wl_bl2的配置。 */
        unsigned int  reserved_4    : 1;  /* bit[19]   : 保留 */
        unsigned int  trsfr_wl_bl_6 : 3;  /* bit[20-22]: 同wl_bl2的配置。 */
        unsigned int  reserved_5    : 1;  /* bit[23]   : 保留 */
        unsigned int  trsfr_wl_bl_7 : 3;  /* bit[24-26]: 同wl_bl2的配置。 */
        unsigned int  reserved_6    : 1;  /* bit[27]   : 保留 */
        unsigned int  trsfr_wl_bl_8 : 3;  /* bit[28-30]: 同wl_bl2的配置。 */
        unsigned int  reserved_7    : 1;  /* bit[31]   : 保留 */
    } reg;
} SOC_DMSS_GLB_RBUF_TRSFR_WL0_UNION;
#endif
#define SOC_DMSS_GLB_RBUF_TRSFR_WL0_trsfr_wl_bl_2_START  (4)
#define SOC_DMSS_GLB_RBUF_TRSFR_WL0_trsfr_wl_bl_2_END    (4)
#define SOC_DMSS_GLB_RBUF_TRSFR_WL0_trsfr_wl_bl_3_START  (8)
#define SOC_DMSS_GLB_RBUF_TRSFR_WL0_trsfr_wl_bl_3_END    (9)
#define SOC_DMSS_GLB_RBUF_TRSFR_WL0_trsfr_wl_bl_4_START  (12)
#define SOC_DMSS_GLB_RBUF_TRSFR_WL0_trsfr_wl_bl_4_END    (13)
#define SOC_DMSS_GLB_RBUF_TRSFR_WL0_trsfr_wl_bl_5_START  (16)
#define SOC_DMSS_GLB_RBUF_TRSFR_WL0_trsfr_wl_bl_5_END    (18)
#define SOC_DMSS_GLB_RBUF_TRSFR_WL0_trsfr_wl_bl_6_START  (20)
#define SOC_DMSS_GLB_RBUF_TRSFR_WL0_trsfr_wl_bl_6_END    (22)
#define SOC_DMSS_GLB_RBUF_TRSFR_WL0_trsfr_wl_bl_7_START  (24)
#define SOC_DMSS_GLB_RBUF_TRSFR_WL0_trsfr_wl_bl_7_END    (26)
#define SOC_DMSS_GLB_RBUF_TRSFR_WL0_trsfr_wl_bl_8_START  (28)
#define SOC_DMSS_GLB_RBUF_TRSFR_WL0_trsfr_wl_bl_8_END    (30)


/*****************************************************************************
 结构名    : SOC_DMSS_GLB_RBUF_TRSFR_WL1_UNION
 结构说明  : GLB_RBUF_TRSFR_WL1 寄存器结构定义。地址偏移量:0x6144，初值:0x00000000，宽度:32
 寄存器说明: RBUF的传输起始水线配置1
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  trsfr_wl_bl_9  : 4;  /* bit[0-3]  : 当RBUF收到burst length为9（transfer总数为9）的读数据时，开始提传输请求的水线配置：
                                                          0x0：每接收积攒到1个transfer或该命令所有transfer时，便提起传输请求；
                                                          0x1：每接收积攒到2个transfer或该命令所有transfer时，便提起传输请求；
                                                          ……
                                                          0x8：每接收积攒到9个transfer或该命令所有transfer时，便提起传输请求。
                                                          说明：
                                                          1.此配置只在当前数据所属MID的间插模式被配置为模式三时才生效。间插模式的配置请参考ASI部分的ASI_RBUF_INTLV寄存器；
                                                          2.配置为间插模式三时，每个长度为burst9的数据，每当在RBUF中积攒的transfer个数达到此寄存器配置的水线时，才能开始请求数据传输，直到当前burst全部传输完毕；在传输中途，若已接收的transfer已传输完毕而剩余数据还未接收到，则可间插传输其它通路的数据。 */
        unsigned int  trsfr_wl_bl_10 : 4;  /* bit[4-7]  : 同wl_bl9的配置。 */
        unsigned int  trsfr_wl_bl_11 : 4;  /* bit[8-11] : 同wl_bl9的配置。 */
        unsigned int  trsfr_wl_bl_12 : 4;  /* bit[12-15]: 同wl_bl9的配置。 */
        unsigned int  trsfr_wl_bl_13 : 4;  /* bit[16-19]: 同wl_bl9的配置。 */
        unsigned int  trsfr_wl_bl_14 : 4;  /* bit[20-23]: 同wl_bl9的配置。 */
        unsigned int  trsfr_wl_bl_15 : 4;  /* bit[24-27]: 同wl_bl9的配置。 */
        unsigned int  trsfr_wl_bl_16 : 4;  /* bit[28-31]: 同wl_bl9的配置。 */
    } reg;
} SOC_DMSS_GLB_RBUF_TRSFR_WL1_UNION;
#endif
#define SOC_DMSS_GLB_RBUF_TRSFR_WL1_trsfr_wl_bl_9_START   (0)
#define SOC_DMSS_GLB_RBUF_TRSFR_WL1_trsfr_wl_bl_9_END     (3)
#define SOC_DMSS_GLB_RBUF_TRSFR_WL1_trsfr_wl_bl_10_START  (4)
#define SOC_DMSS_GLB_RBUF_TRSFR_WL1_trsfr_wl_bl_10_END    (7)
#define SOC_DMSS_GLB_RBUF_TRSFR_WL1_trsfr_wl_bl_11_START  (8)
#define SOC_DMSS_GLB_RBUF_TRSFR_WL1_trsfr_wl_bl_11_END    (11)
#define SOC_DMSS_GLB_RBUF_TRSFR_WL1_trsfr_wl_bl_12_START  (12)
#define SOC_DMSS_GLB_RBUF_TRSFR_WL1_trsfr_wl_bl_12_END    (15)
#define SOC_DMSS_GLB_RBUF_TRSFR_WL1_trsfr_wl_bl_13_START  (16)
#define SOC_DMSS_GLB_RBUF_TRSFR_WL1_trsfr_wl_bl_13_END    (19)
#define SOC_DMSS_GLB_RBUF_TRSFR_WL1_trsfr_wl_bl_14_START  (20)
#define SOC_DMSS_GLB_RBUF_TRSFR_WL1_trsfr_wl_bl_14_END    (23)
#define SOC_DMSS_GLB_RBUF_TRSFR_WL1_trsfr_wl_bl_15_START  (24)
#define SOC_DMSS_GLB_RBUF_TRSFR_WL1_trsfr_wl_bl_15_END    (27)
#define SOC_DMSS_GLB_RBUF_TRSFR_WL1_trsfr_wl_bl_16_START  (28)
#define SOC_DMSS_GLB_RBUF_TRSFR_WL1_trsfr_wl_bl_16_END    (31)


/*****************************************************************************
 结构名    : SOC_DMSS_GLB_RBUF_BYP_PATH_UNION
 结构说明  : GLB_RBUF_BYP_PATH 寄存器结构定义。地址偏移量:0x6148，初值:0x00000001，宽度:32
 寄存器说明: RBUF的bypass通路使能
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  rbuf_byp_path_en : 1;  /* bit[0]   : 单通道时，数据bypass通路的使能开关：
                                                           0：禁止：所有返回数据都必须经过数据BUF，RBUF的latency最小为4cycle；
                                                           1：使能：当数据BUF中无对应ASI的数据且通路不阻塞时，返回数据可绕过数据BUF直接返回ASI，RBUF的latency最小为0或1（取决于bypass通路是否插入RS）；
                                                           注意：
                                                           此配置仅在单通道配置下有效，多通道配置此寄存器无意义。 */
        unsigned int  reserved         : 31; /* bit[1-31]: 保留 */
    } reg;
} SOC_DMSS_GLB_RBUF_BYP_PATH_UNION;
#endif
#define SOC_DMSS_GLB_RBUF_BYP_PATH_rbuf_byp_path_en_START  (0)
#define SOC_DMSS_GLB_RBUF_BYP_PATH_rbuf_byp_path_en_END    (0)


/*****************************************************************************
 结构名    : SOC_DMSS_GLB_RBUF_BP_UNION
 结构说明  : GLB_RBUF_BP 寄存器结构定义。地址偏移量:0x6150+0x4*(rbuf_bp_grps)，初值:0x00000000，宽度:32
 寄存器说明: RBUF的命令反压配置
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  rbuf_bp_grp : 16; /* bit[0-15] : 命令反压分组的选择：
                                                       rbuf_bp_grp[n]=0：ASIn不包含到分组0；
                                                       rbuf_bp_grp[n]=1：ASIn包含到分组0。
                                                       说明：
                                                       被包含到同一个分组的ASI，当其在RBUF中的数据burst总数达到对应rbuf_bp_wl配置的水线时，送出反压信号给上游模块（DDRC），进行对应ASI的命令反压。
                                                       注意：
                                                       此寄存器只能在系统初始化时静态配置。 */
        unsigned int  rbuf_bp_wl  : 16; /* bit[16-31]: 命令反压分组的水线：
                                                       0：关闭命令反压功能；
                                                       ……
                                                       n：当前分组的命令反压水线。
                                                       说明：
                                                       1.当前分组中所有ASI对应的数据burst总数达到rubf_bp_wl时，送出反压信号给上游模块（DDRC），进行对应ASI的命令反压；
                                                       2.水线最大配置值为RBUF中的BUFFER深度。
                                                       注意：
                                                       不能动态开关命令反压功能，但可以在使能的情况下，动态调整水线。 */
    } reg;
} SOC_DMSS_GLB_RBUF_BP_UNION;
#endif
#define SOC_DMSS_GLB_RBUF_BP_rbuf_bp_grp_START  (0)
#define SOC_DMSS_GLB_RBUF_BP_rbuf_bp_grp_END    (15)
#define SOC_DMSS_GLB_RBUF_BP_rbuf_bp_wl_START   (16)
#define SOC_DMSS_GLB_RBUF_BP_rbuf_bp_wl_END     (31)


/*****************************************************************************
 结构名    : SOC_DMSS_GLB_DCQ_CTRL_UNION
 结构说明  : GLB_DCQ_CTRL 寄存器结构定义。地址偏移量:0x6200，初值:0x00000000，宽度:32
 寄存器说明: DDRC的命令队列状态统计控制
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  dcq_en   : 1;  /* bit[0]   : 统计使能：
                                                   0：禁止；
                                                   1：使能。
                                                   注意：
                                                   1.若配置为“禁止”，则所有基于DDRC命令队列状态统计的功能同时被禁止，即寄存器ASI_QOS_LMTR0_OVRD/ASI_QOS_LMTR1_OVRD/ASI_QOS_DCQ_ST等均无效；
                                                   2.此寄存器只能静态配置。 */
        unsigned int  reserved_0: 3;  /* bit[1-3] : 保留 */
        unsigned int  dcq_mode : 1;  /* bit[4]   : 统计模式：
                                                   0：合并统计QOSBUF和多个DMC的命令队列状态；
                                                   1：只统计QOSBUF的命令队列状态。
                                                   注意：
                                                   此寄存器只能静态配置。 */
        unsigned int  reserved_1: 27; /* bit[5-31]: 保留 */
    } reg;
} SOC_DMSS_GLB_DCQ_CTRL_UNION;
#endif
#define SOC_DMSS_GLB_DCQ_CTRL_dcq_en_START    (0)
#define SOC_DMSS_GLB_DCQ_CTRL_dcq_en_END      (0)
#define SOC_DMSS_GLB_DCQ_CTRL_dcq_mode_START  (4)
#define SOC_DMSS_GLB_DCQ_CTRL_dcq_mode_END    (4)


/*****************************************************************************
 结构名    : SOC_DMSS_GLB_DCQ_ST_UNION
 结构说明  : GLB_DCQ_ST 寄存器结构定义。地址偏移量:0x6204，初值:0x00000000，宽度:32
 寄存器说明: DDRC的命令队列状态
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  dcq0_wr_que_st : 8;  /* bit[0-7]  : DDRC0命令队列中停留的写命令个数。 */
        unsigned int  dcq0_rd_que_st : 8;  /* bit[8-15] : DDRC0命令队列中停留的读命令个数。 */
        unsigned int  dcq1_wr_que_st : 8;  /* bit[16-23]: DDRC1命令队列中停留的写命令个数。 */
        unsigned int  dcq1_rd_que_st : 8;  /* bit[24-31]: DDRC1命令队列中停留的读命令个数。 */
    } reg;
} SOC_DMSS_GLB_DCQ_ST_UNION;
#endif
#define SOC_DMSS_GLB_DCQ_ST_dcq0_wr_que_st_START  (0)
#define SOC_DMSS_GLB_DCQ_ST_dcq0_wr_que_st_END    (7)
#define SOC_DMSS_GLB_DCQ_ST_dcq0_rd_que_st_START  (8)
#define SOC_DMSS_GLB_DCQ_ST_dcq0_rd_que_st_END    (15)
#define SOC_DMSS_GLB_DCQ_ST_dcq1_wr_que_st_START  (16)
#define SOC_DMSS_GLB_DCQ_ST_dcq1_wr_que_st_END    (23)
#define SOC_DMSS_GLB_DCQ_ST_dcq1_rd_que_st_START  (24)
#define SOC_DMSS_GLB_DCQ_ST_dcq1_rd_que_st_END    (31)


/*****************************************************************************
 结构名    : SOC_DMSS_GLB_DCQ_PRILVL0_UNION
 结构说明  : GLB_DCQ_PRILVL0 寄存器结构定义。地址偏移量:0x6208，初值:0x00000000，宽度:32
 寄存器说明: 基于DDRC命令队列状态的允许优先级水线0
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  reserved     : 8;  /* bit[0-7]  : 保留 */
        unsigned int  dcq_pri1_lvl : 8;  /* bit[8-15] : 优先级1的DDRC命令队列状态允许水线：
                                                        0x00：此水线关闭；
                                                        0x01～0xFF：DDRC命令队列中读写命令总数达到此水线时，用LMTR2对低于优先级1的命令进行流控。
                                                        注意：
                                                        1.若有多个DDRC，则各个DDRC的命令队列命令状态均为“或”的关系，即任一DDRC命令队列的状态达到水线即可；
                                                        2.对于每个ASI，可在寄存器ASI_QOS_CTRL.dcq_prilvl_en中单独设置是否受此水线的影响。 */
        unsigned int  dcq_pri2_lvl : 8;  /* bit[16-23]: 优先级2的DDRC命令队列状态允许水线：
                                                        配置方式同dcq_pri1_lvl。 */
        unsigned int  dcq_pri3_lvl : 8;  /* bit[24-31]: 优先级3的DDRC命令队列状态允许水线：
                                                        配置方式同dcq_pri1_lvl。 */
    } reg;
} SOC_DMSS_GLB_DCQ_PRILVL0_UNION;
#endif
#define SOC_DMSS_GLB_DCQ_PRILVL0_dcq_pri1_lvl_START  (8)
#define SOC_DMSS_GLB_DCQ_PRILVL0_dcq_pri1_lvl_END    (15)
#define SOC_DMSS_GLB_DCQ_PRILVL0_dcq_pri2_lvl_START  (16)
#define SOC_DMSS_GLB_DCQ_PRILVL0_dcq_pri2_lvl_END    (23)
#define SOC_DMSS_GLB_DCQ_PRILVL0_dcq_pri3_lvl_START  (24)
#define SOC_DMSS_GLB_DCQ_PRILVL0_dcq_pri3_lvl_END    (31)


/*****************************************************************************
 结构名    : SOC_DMSS_GLB_DCQ_PRILVL1_UNION
 结构说明  : GLB_DCQ_PRILVL1 寄存器结构定义。地址偏移量:0x620C，初值:0x00000000，宽度:32
 寄存器说明: 基于DDRC命令队列状态的允许优先级水线1
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  dcq_pri4_lvl : 8;  /* bit[0-7]  : 优先级4的DDRC命令队列状态允许水线：
                                                        0x00：此水线关闭；
                                                        0x01～0xFF：DDRC命令队列中读写命令总数达到此水线时，用LMTR2对低于优先级4的命令进行流控。
                                                        注意：
                                                        1.若有多个DDRC，则各个DDRC的命令队列命令状态均为“或”的关系，即任一DDRC命令队列的状态达到水线即可；
                                                        2.对于每个ASI，可在寄存器ASI_QOS_CTRL.dcq_prilvl_en中单独设置是否受此水线的影响。 */
        unsigned int  dcq_pri5_lvl : 8;  /* bit[8-15] : 优先级5的DDRC命令队列状态允许水线：
                                                        配置方式同dcq_pri4_lvl。 */
        unsigned int  dcq_pri6_lvl : 8;  /* bit[16-23]: 优先级6的DDRC命令队列状态允许水线：
                                                        配置方式同dcq_pri4_lvl。 */
        unsigned int  dcq_pri7_lvl : 8;  /* bit[24-31]: 优先级7的DDRC命令队列状态允许水线：
                                                        配置方式同dcq_pri4_lvl。 */
    } reg;
} SOC_DMSS_GLB_DCQ_PRILVL1_UNION;
#endif
#define SOC_DMSS_GLB_DCQ_PRILVL1_dcq_pri4_lvl_START  (0)
#define SOC_DMSS_GLB_DCQ_PRILVL1_dcq_pri4_lvl_END    (7)
#define SOC_DMSS_GLB_DCQ_PRILVL1_dcq_pri5_lvl_START  (8)
#define SOC_DMSS_GLB_DCQ_PRILVL1_dcq_pri5_lvl_END    (15)
#define SOC_DMSS_GLB_DCQ_PRILVL1_dcq_pri6_lvl_START  (16)
#define SOC_DMSS_GLB_DCQ_PRILVL1_dcq_pri6_lvl_END    (23)
#define SOC_DMSS_GLB_DCQ_PRILVL1_dcq_pri7_lvl_START  (24)
#define SOC_DMSS_GLB_DCQ_PRILVL1_dcq_pri7_lvl_END    (31)


/*****************************************************************************
 结构名    : SOC_DMSS_GLB_DCQ_MST_UNION
 结构说明  : GLB_DCQ_MST 寄存器结构定义。地址偏移量:0x6210+0x4*(dcq_msts)，初值:0x00000000，宽度:32
 寄存器说明: 外部master的流控功能
            （【Dallas】
            0x6210：ISP
            0x6214：DSS
            0x6218：ASI0 MODEM）
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  dcq_mst_req_pri  : 3;  /* bit[0-2] : master请求流控的允许优先级：
                                                           0：此功能关闭；
                                                           1～7：当外部master送入的mst_flux_req信号使能时，所有ASI的低于此允许优先级的命令，都将因limter2的带宽限制而可能被阻塞。
                                                           注意：
                                                           寄存器GLB_DCQ_MST_PRI和GLB_DCQ_PRILVL0/1的机制类似，都是用limter2去控制低优先级命令的带宽，其相互之间均为“或”的关系，即若任一机制条件满足，即可对命令进行控制。 */
        unsigned int  dcq_mst_req_en   : 1;  /* bit[3]   : master请求流控功能的使能：
                                                           0：禁止；
                                                           1：使能。 */
        unsigned int  dcq_mst_ctrl_pri : 3;  /* bit[4-6] : master源端流控的触发优先级：
                                                           0～6：若当前允许优先级高于此处设定的优先级时，将给外部master送出mst_flux_ctrl信号，通知其进行源端流控，以避免再发送低优先级命令而被对应的ASI阻塞；
                                                           7：reserved。 */
        unsigned int  dcq_mst_ctrl_en  : 1;  /* bit[7]   : master源端流控功能的使能：
                                                           0：禁止；
                                                           1：使能。 */
        unsigned int  reserved         : 24; /* bit[8-31]: 保留 */
    } reg;
} SOC_DMSS_GLB_DCQ_MST_UNION;
#endif
#define SOC_DMSS_GLB_DCQ_MST_dcq_mst_req_pri_START   (0)
#define SOC_DMSS_GLB_DCQ_MST_dcq_mst_req_pri_END     (2)
#define SOC_DMSS_GLB_DCQ_MST_dcq_mst_req_en_START    (3)
#define SOC_DMSS_GLB_DCQ_MST_dcq_mst_req_en_END      (3)
#define SOC_DMSS_GLB_DCQ_MST_dcq_mst_ctrl_pri_START  (4)
#define SOC_DMSS_GLB_DCQ_MST_dcq_mst_ctrl_pri_END    (6)
#define SOC_DMSS_GLB_DCQ_MST_dcq_mst_ctrl_en_START   (7)
#define SOC_DMSS_GLB_DCQ_MST_dcq_mst_ctrl_en_END     (7)


/*****************************************************************************
 结构名    : SOC_DMSS_GLB_DCQ_INT_EN_UNION
 结构说明  : GLB_DCQ_INT_EN 寄存器结构定义。地址偏移量:0x6250，初值:0x00000000，宽度:32
 寄存器说明: 允许优先级的跳变中断使能
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  reserved_0      : 1;  /* bit[0]    : 保留 */
        unsigned int  dcq_pri1_int_en : 1;  /* bit[1]    : 当dcq_pri_allow达到优先级1时的中断使能：
                                                           0：禁止；
                                                           1：使能。
                                                           说明：
                                                           1.dcq_pri_allow的状态，可在寄存器GLB_DFX_DCQ中查看；
                                                           2.中断状态的查看及清除，可参见寄存器GLB_INT_STATUS和GLB_INT_CLEAR。 */
        unsigned int  dcq_pri2_int_en : 1;  /* bit[2]    : 同dcq_pri1_int_en。 */
        unsigned int  dcq_pri3_int_en : 1;  /* bit[3]    : 同dcq_pri1_int_en。 */
        unsigned int  dcq_pri4_int_en : 1;  /* bit[4]    : 同dcq_pri1_int_en。 */
        unsigned int  dcq_pri5_int_en : 1;  /* bit[5]    : 同dcq_pri1_int_en。 */
        unsigned int  dcq_pri6_int_en : 1;  /* bit[6]    : 同dcq_pri1_int_en。 */
        unsigned int  dcq_pri7_int_en : 1;  /* bit[7]    : 同dcq_pri1_int_en。 */
        unsigned int  reserved_1      : 1;  /* bit[8]    : 保留 */
        unsigned int  mst_pri1_int_en : 1;  /* bit[9]    : 当mst_pri_allow达到优先级1时的中断使能：
                                                           0：禁止；
                                                           1：使能。
                                                           说明：
                                                           1.mst_pri_allow的状态，可在寄存器GLB_DFX_DCQ中查看；
                                                           2.中断状态的查看及清除，可参见寄存器GLB_INT_STATUS和GLB_INT_CLEAR。 */
        unsigned int  mst_pri2_int_en : 1;  /* bit[10]   : 同mst_pri1_int_en。 */
        unsigned int  mst_pri3_int_en : 1;  /* bit[11]   : 同mst_pri1_int_en。 */
        unsigned int  mst_pri4_int_en : 1;  /* bit[12]   : 同mst_pri1_int_en。 */
        unsigned int  mst_pri5_int_en : 1;  /* bit[13]   : 同mst_pri1_int_en。 */
        unsigned int  mst_pri6_int_en : 1;  /* bit[14]   : 同mst_pri1_int_en。 */
        unsigned int  mst_pri7_int_en : 1;  /* bit[15]   : 同mst_pri1_int_en。 */
        unsigned int  reserved_2      : 16; /* bit[16-31]: 保留 */
    } reg;
} SOC_DMSS_GLB_DCQ_INT_EN_UNION;
#endif
#define SOC_DMSS_GLB_DCQ_INT_EN_dcq_pri1_int_en_START  (1)
#define SOC_DMSS_GLB_DCQ_INT_EN_dcq_pri1_int_en_END    (1)
#define SOC_DMSS_GLB_DCQ_INT_EN_dcq_pri2_int_en_START  (2)
#define SOC_DMSS_GLB_DCQ_INT_EN_dcq_pri2_int_en_END    (2)
#define SOC_DMSS_GLB_DCQ_INT_EN_dcq_pri3_int_en_START  (3)
#define SOC_DMSS_GLB_DCQ_INT_EN_dcq_pri3_int_en_END    (3)
#define SOC_DMSS_GLB_DCQ_INT_EN_dcq_pri4_int_en_START  (4)
#define SOC_DMSS_GLB_DCQ_INT_EN_dcq_pri4_int_en_END    (4)
#define SOC_DMSS_GLB_DCQ_INT_EN_dcq_pri5_int_en_START  (5)
#define SOC_DMSS_GLB_DCQ_INT_EN_dcq_pri5_int_en_END    (5)
#define SOC_DMSS_GLB_DCQ_INT_EN_dcq_pri6_int_en_START  (6)
#define SOC_DMSS_GLB_DCQ_INT_EN_dcq_pri6_int_en_END    (6)
#define SOC_DMSS_GLB_DCQ_INT_EN_dcq_pri7_int_en_START  (7)
#define SOC_DMSS_GLB_DCQ_INT_EN_dcq_pri7_int_en_END    (7)
#define SOC_DMSS_GLB_DCQ_INT_EN_mst_pri1_int_en_START  (9)
#define SOC_DMSS_GLB_DCQ_INT_EN_mst_pri1_int_en_END    (9)
#define SOC_DMSS_GLB_DCQ_INT_EN_mst_pri2_int_en_START  (10)
#define SOC_DMSS_GLB_DCQ_INT_EN_mst_pri2_int_en_END    (10)
#define SOC_DMSS_GLB_DCQ_INT_EN_mst_pri3_int_en_START  (11)
#define SOC_DMSS_GLB_DCQ_INT_EN_mst_pri3_int_en_END    (11)
#define SOC_DMSS_GLB_DCQ_INT_EN_mst_pri4_int_en_START  (12)
#define SOC_DMSS_GLB_DCQ_INT_EN_mst_pri4_int_en_END    (12)
#define SOC_DMSS_GLB_DCQ_INT_EN_mst_pri5_int_en_START  (13)
#define SOC_DMSS_GLB_DCQ_INT_EN_mst_pri5_int_en_END    (13)
#define SOC_DMSS_GLB_DCQ_INT_EN_mst_pri6_int_en_START  (14)
#define SOC_DMSS_GLB_DCQ_INT_EN_mst_pri6_int_en_END    (14)
#define SOC_DMSS_GLB_DCQ_INT_EN_mst_pri7_int_en_START  (15)
#define SOC_DMSS_GLB_DCQ_INT_EN_mst_pri7_int_en_END    (15)


/*****************************************************************************
 结构名    : SOC_DMSS_GLB_STAT_CTRL_UNION
 结构说明  : GLB_STAT_CTRL 寄存器结构定义。地址偏移量:0x6260，初值:0x00000000，宽度:32
 寄存器说明: 统计功能控制
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  asi_stat_en       : 12; /* bit[0-11] : ASI统计功能使能。
                                                             asi_stat_en[n]=0：ASIn的统计功能关闭；
                                                             asi_stat_en[n]=1：ASIn的统计功能使能。
                                                             说明：
                                                             1.统计相关的配置在寄存器ASI_STAT_MODE/ASI_STAT_FILTER0/1/2中；
                                                             2.若关闭，则统计结果保持；若重新使能，则统计结果清零并重新统计。 */
        unsigned int  reserved_0        : 4;  /* bit[12-15]: 保留 */
        unsigned int  pri_allow_stat_en : 1;  /* bit[16]   : PRI_ALLOW统计功能使能。
                                                             0：关闭；
                                                             1：使能。
                                                             说明：
                                                             1.需使能DCQ相关功能，此统计功能才有意义；
                                                             2.统计相关的结果在寄存器GLB_STAT_PRI1/2/3/4/5/6/7_ALLOW中；
                                                             3.若关闭，则统计结果保持；若重新使能，则统计结果清零并重新统计。 */
        unsigned int  reserved_1        : 15; /* bit[17-31]: 保留 */
    } reg;
} SOC_DMSS_GLB_STAT_CTRL_UNION;
#endif
#define SOC_DMSS_GLB_STAT_CTRL_asi_stat_en_START        (0)
#define SOC_DMSS_GLB_STAT_CTRL_asi_stat_en_END          (11)
#define SOC_DMSS_GLB_STAT_CTRL_pri_allow_stat_en_START  (16)
#define SOC_DMSS_GLB_STAT_CTRL_pri_allow_stat_en_END    (16)


/*****************************************************************************
 结构名    : SOC_DMSS_GLB_STAT_ALL_ALLOW_UNION
 结构说明  : GLB_STAT_ALL_ALLOW 寄存器结构定义。地址偏移量:0x6270，初值:0x00000000，宽度:32
 寄存器说明: 所有优先级都允许的统计
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  stat_dcq_all_allow : 32; /* bit[0-31]: 统计当dcq_pri_allow为0(dcq_que未达到任何dcq_pri_lvl)的生效周期：
                                                             说明：
                                                             1.累加dcq_pri_allow为0的周期数，单位为cycle；
                                                             2.统计停止后结果保持，统计再次开始时自动清零，溢出后卷绕计数。 */
    } reg;
} SOC_DMSS_GLB_STAT_ALL_ALLOW_UNION;
#endif
#define SOC_DMSS_GLB_STAT_ALL_ALLOW_stat_dcq_all_allow_START  (0)
#define SOC_DMSS_GLB_STAT_ALL_ALLOW_stat_dcq_all_allow_END    (31)


/*****************************************************************************
 结构名    : SOC_DMSS_GLB_STAT_PRI1_ALLOW_UNION
 结构说明  : GLB_STAT_PRI1_ALLOW 寄存器结构定义。地址偏移量:0x6274，初值:0x00000000，宽度:32
 寄存器说明: 允许优先级为1的统计
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  stat_dcq_pri1_allow : 32; /* bit[0-31]: 统计当dcq_pri_allow为1(dcq_que达到水线dcq_pri1_lvl)的周期：
                                                              说明：
                                                              1.累加dcq_pri_allow为1的周期数，单位为cycle；
                                                              2.统计停止后结果保持，统计再次开始时自动清零，溢出后卷绕计数。 */
    } reg;
} SOC_DMSS_GLB_STAT_PRI1_ALLOW_UNION;
#endif
#define SOC_DMSS_GLB_STAT_PRI1_ALLOW_stat_dcq_pri1_allow_START  (0)
#define SOC_DMSS_GLB_STAT_PRI1_ALLOW_stat_dcq_pri1_allow_END    (31)


/*****************************************************************************
 结构名    : SOC_DMSS_GLB_STAT_PRI2_ALLOW_UNION
 结构说明  : GLB_STAT_PRI2_ALLOW 寄存器结构定义。地址偏移量:0x6278，初值:0x00000000，宽度:32
 寄存器说明: 允许优先级为2的统计
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  stat_dcq_pri2_allow : 32; /* bit[0-31]: 统计当优先级水线dcq_pri_allow为2的生效周期。 */
    } reg;
} SOC_DMSS_GLB_STAT_PRI2_ALLOW_UNION;
#endif
#define SOC_DMSS_GLB_STAT_PRI2_ALLOW_stat_dcq_pri2_allow_START  (0)
#define SOC_DMSS_GLB_STAT_PRI2_ALLOW_stat_dcq_pri2_allow_END    (31)


/*****************************************************************************
 结构名    : SOC_DMSS_GLB_STAT_PRI3_ALLOW_UNION
 结构说明  : GLB_STAT_PRI3_ALLOW 寄存器结构定义。地址偏移量:0x627C，初值:0x00000000，宽度:32
 寄存器说明: 允许优先级为3的统计
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  stat_dcq_pri3_allow : 32; /* bit[0-31]: 统计当优先级水线dcq_pri_allow为3的生效周期。 */
    } reg;
} SOC_DMSS_GLB_STAT_PRI3_ALLOW_UNION;
#endif
#define SOC_DMSS_GLB_STAT_PRI3_ALLOW_stat_dcq_pri3_allow_START  (0)
#define SOC_DMSS_GLB_STAT_PRI3_ALLOW_stat_dcq_pri3_allow_END    (31)


/*****************************************************************************
 结构名    : SOC_DMSS_GLB_STAT_PRI4_ALLOW_UNION
 结构说明  : GLB_STAT_PRI4_ALLOW 寄存器结构定义。地址偏移量:0x6280，初值:0x00000000，宽度:32
 寄存器说明: 允许优先级为4的统计
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  stat_dcq_pri4_allow : 32; /* bit[0-31]: 统计当优先级水线dcq_pri_allow为4的生效周期。 */
    } reg;
} SOC_DMSS_GLB_STAT_PRI4_ALLOW_UNION;
#endif
#define SOC_DMSS_GLB_STAT_PRI4_ALLOW_stat_dcq_pri4_allow_START  (0)
#define SOC_DMSS_GLB_STAT_PRI4_ALLOW_stat_dcq_pri4_allow_END    (31)


/*****************************************************************************
 结构名    : SOC_DMSS_GLB_STAT_PRI5_ALLOW_UNION
 结构说明  : GLB_STAT_PRI5_ALLOW 寄存器结构定义。地址偏移量:0x6284，初值:0x00000000，宽度:32
 寄存器说明: 允许优先级为5的统计
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  stat_dcq_pri5_allow : 32; /* bit[0-31]: 统计当优先级水线dcq_pri_allow为5的生效周期。 */
    } reg;
} SOC_DMSS_GLB_STAT_PRI5_ALLOW_UNION;
#endif
#define SOC_DMSS_GLB_STAT_PRI5_ALLOW_stat_dcq_pri5_allow_START  (0)
#define SOC_DMSS_GLB_STAT_PRI5_ALLOW_stat_dcq_pri5_allow_END    (31)


/*****************************************************************************
 结构名    : SOC_DMSS_GLB_STAT_PRI6_ALLOW_UNION
 结构说明  : GLB_STAT_PRI6_ALLOW 寄存器结构定义。地址偏移量:0x6288，初值:0x00000000，宽度:32
 寄存器说明: 允许优先级为6的统计
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  stat_dcq_pri6_allow : 32; /* bit[0-31]: 统计当优先级水线dcq_pri_allow为6的生效周期。 */
    } reg;
} SOC_DMSS_GLB_STAT_PRI6_ALLOW_UNION;
#endif
#define SOC_DMSS_GLB_STAT_PRI6_ALLOW_stat_dcq_pri6_allow_START  (0)
#define SOC_DMSS_GLB_STAT_PRI6_ALLOW_stat_dcq_pri6_allow_END    (31)


/*****************************************************************************
 结构名    : SOC_DMSS_GLB_STAT_PRI7_ALLOW_UNION
 结构说明  : GLB_STAT_PRI7_ALLOW 寄存器结构定义。地址偏移量:0x628C，初值:0x00000000，宽度:32
 寄存器说明: 允许优先级为7的统计
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  stat_dcq_pri7_allow : 32; /* bit[0-31]: 统计当优先级水线dcq_pri_allow为7的生效周期。 */
    } reg;
} SOC_DMSS_GLB_STAT_PRI7_ALLOW_UNION;
#endif
#define SOC_DMSS_GLB_STAT_PRI7_ALLOW_stat_dcq_pri7_allow_START  (0)
#define SOC_DMSS_GLB_STAT_PRI7_ALLOW_stat_dcq_pri7_allow_END    (31)


/*****************************************************************************
 结构名    : SOC_DMSS_GLB_DFX_RBUF0_UNION
 结构说明  : GLB_DFX_RBUF0 寄存器结构定义。地址偏移量:0x6700+0x10*(chans)，初值:0x00000000，宽度:32
 寄存器说明: DFX：RBUF状态0
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  vque0_cnt_st : 8;  /* bit[0-7]  : RBUF的buffer中待发往ASI0的数据burst个数。 */
        unsigned int  vque1_cnt_st : 8;  /* bit[8-15] : 同vque0_cnt。 */
        unsigned int  vque2_cnt_st : 8;  /* bit[16-23]: 同vque0_cnt。 */
        unsigned int  vque3_cnt_st : 8;  /* bit[24-31]: 同vque0_cnt。 */
    } reg;
} SOC_DMSS_GLB_DFX_RBUF0_UNION;
#endif
#define SOC_DMSS_GLB_DFX_RBUF0_vque0_cnt_st_START  (0)
#define SOC_DMSS_GLB_DFX_RBUF0_vque0_cnt_st_END    (7)
#define SOC_DMSS_GLB_DFX_RBUF0_vque1_cnt_st_START  (8)
#define SOC_DMSS_GLB_DFX_RBUF0_vque1_cnt_st_END    (15)
#define SOC_DMSS_GLB_DFX_RBUF0_vque2_cnt_st_START  (16)
#define SOC_DMSS_GLB_DFX_RBUF0_vque2_cnt_st_END    (23)
#define SOC_DMSS_GLB_DFX_RBUF0_vque3_cnt_st_START  (24)
#define SOC_DMSS_GLB_DFX_RBUF0_vque3_cnt_st_END    (31)


/*****************************************************************************
 结构名    : SOC_DMSS_GLB_DFX_RBUF1_UNION
 结构说明  : GLB_DFX_RBUF1 寄存器结构定义。地址偏移量:0x6704+0x10*(chans)，初值:0x00000000，宽度:32
 寄存器说明: DFX：RBUF状态1
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  vque4_cnt_st : 8;  /* bit[0-7]  : RBUF的buffer中待发往ASI4的数据burst个数。 */
        unsigned int  vque5_cnt_st : 8;  /* bit[8-15] : 同vque4_cnt。 */
        unsigned int  vque6_cnt_st : 8;  /* bit[16-23]: 同vque4_cnt。 */
        unsigned int  vque7_cnt_st : 8;  /* bit[24-31]: 同vque4_cnt。 */
    } reg;
} SOC_DMSS_GLB_DFX_RBUF1_UNION;
#endif
#define SOC_DMSS_GLB_DFX_RBUF1_vque4_cnt_st_START  (0)
#define SOC_DMSS_GLB_DFX_RBUF1_vque4_cnt_st_END    (7)
#define SOC_DMSS_GLB_DFX_RBUF1_vque5_cnt_st_START  (8)
#define SOC_DMSS_GLB_DFX_RBUF1_vque5_cnt_st_END    (15)
#define SOC_DMSS_GLB_DFX_RBUF1_vque6_cnt_st_START  (16)
#define SOC_DMSS_GLB_DFX_RBUF1_vque6_cnt_st_END    (23)
#define SOC_DMSS_GLB_DFX_RBUF1_vque7_cnt_st_START  (24)
#define SOC_DMSS_GLB_DFX_RBUF1_vque7_cnt_st_END    (31)


/*****************************************************************************
 结构名    : SOC_DMSS_GLB_DFX_RBUF2_UNION
 结构说明  : GLB_DFX_RBUF2 寄存器结构定义。地址偏移量:0x6708+0x10*(chans)，初值:0x00000000，宽度:32
 寄存器说明: DFX：RBUF状态2
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  vque8_cnt_st  : 8;  /* bit[0-7]  : RBUF的buffer中待发往ASI8的数据burst个数。 */
        unsigned int  vque9_cnt_st  : 8;  /* bit[8-15] : 同vque8_cnt。 */
        unsigned int  vque10_cnt_st : 8;  /* bit[16-23]: 同vque8_cnt。 */
        unsigned int  vque11_cnt_st : 8;  /* bit[24-31]: 同vque8_cnt。 */
    } reg;
} SOC_DMSS_GLB_DFX_RBUF2_UNION;
#endif
#define SOC_DMSS_GLB_DFX_RBUF2_vque8_cnt_st_START   (0)
#define SOC_DMSS_GLB_DFX_RBUF2_vque8_cnt_st_END     (7)
#define SOC_DMSS_GLB_DFX_RBUF2_vque9_cnt_st_START   (8)
#define SOC_DMSS_GLB_DFX_RBUF2_vque9_cnt_st_END     (15)
#define SOC_DMSS_GLB_DFX_RBUF2_vque10_cnt_st_START  (16)
#define SOC_DMSS_GLB_DFX_RBUF2_vque10_cnt_st_END    (23)
#define SOC_DMSS_GLB_DFX_RBUF2_vque11_cnt_st_START  (24)
#define SOC_DMSS_GLB_DFX_RBUF2_vque11_cnt_st_END    (31)


/*****************************************************************************
 结构名    : SOC_DMSS_GLB_DFX_RBUF3_UNION
 结构说明  : GLB_DFX_RBUF3 寄存器结构定义。地址偏移量:0x670C+0x10*(chans)，初值:0x00000000，宽度:32
 寄存器说明: DFX：RBUF状态3
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  vque_grp0_cnt_st : 8;  /* bit[0-7]  : RBUF的buffer中，命令反压分组0中的数据burst个数。 */
        unsigned int  vque_grp1_cnt_st : 8;  /* bit[8-15] : 同vque_grp0_cnt。 */
        unsigned int  vque_grp2_cnt_st : 8;  /* bit[16-23]: 同vque_grp0_cnt。 */
        unsigned int  vque_grp3_cnt_st : 8;  /* bit[24-31]: 同vque_grp0_cnt。 */
    } reg;
} SOC_DMSS_GLB_DFX_RBUF3_UNION;
#endif
#define SOC_DMSS_GLB_DFX_RBUF3_vque_grp0_cnt_st_START  (0)
#define SOC_DMSS_GLB_DFX_RBUF3_vque_grp0_cnt_st_END    (7)
#define SOC_DMSS_GLB_DFX_RBUF3_vque_grp1_cnt_st_START  (8)
#define SOC_DMSS_GLB_DFX_RBUF3_vque_grp1_cnt_st_END    (15)
#define SOC_DMSS_GLB_DFX_RBUF3_vque_grp2_cnt_st_START  (16)
#define SOC_DMSS_GLB_DFX_RBUF3_vque_grp2_cnt_st_END    (23)
#define SOC_DMSS_GLB_DFX_RBUF3_vque_grp3_cnt_st_START  (24)
#define SOC_DMSS_GLB_DFX_RBUF3_vque_grp3_cnt_st_END    (31)


/*****************************************************************************
 结构名    : SOC_DMSS_GLB_DFX_DMI_GRNT_UNION
 结构说明  : GLB_DFX_DMI_GRNT 寄存器结构定义。地址偏移量:0x6740，初值:0x00000000，宽度:32
 寄存器说明: DFX：DMI的命令仲裁状态
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  dmi0_grant : 16; /* bit[0-15] : DMI0的命令仲裁状态：
                                                      dmi_grant[n]=0：ASIn未获得DMI0的命令仲裁；
                                                      dmi_grant[n]=1：ASIn获得了DMI0的命令仲裁。 */
        unsigned int  dmi1_grant : 16; /* bit[16-31]: 同dmi0_grant。 */
    } reg;
} SOC_DMSS_GLB_DFX_DMI_GRNT_UNION;
#endif
#define SOC_DMSS_GLB_DFX_DMI_GRNT_dmi0_grant_START  (0)
#define SOC_DMSS_GLB_DFX_DMI_GRNT_dmi0_grant_END    (15)
#define SOC_DMSS_GLB_DFX_DMI_GRNT_dmi1_grant_START  (16)
#define SOC_DMSS_GLB_DFX_DMI_GRNT_dmi1_grant_END    (31)


/*****************************************************************************
 结构名    : SOC_DMSS_GLB_DFX_DCQ_UNION
 结构说明  : GLB_DFX_DCQ 寄存器结构定义。地址偏移量:0x6744，初值:0x00000000，宽度:32
 寄存器说明: DFX：DCQ的状态
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  dcq_pri_allow  : 3;  /* bit[0-2]  : DCQ的允许优先级的实时状态：
                                                          根据DCQ队列状态及优先级允许水线，得到的允许优先级。 */
        unsigned int  reserved_0     : 1;  /* bit[3]    : 保留 */
        unsigned int  mst_pri_allow  : 3;  /* bit[4-6]  : MST的允许优先级的实时状态：
                                                          根据mst_flux_req信号请求得到的允许优先级。若有多个mst_flux_req同时生效时，允许优先级为最大值。 */
        unsigned int  reserved_1     : 1;  /* bit[7]    : 保留 */
        unsigned int  dcq_pri_int_st : 3;  /* bit[8-10] : DCQ的允许优先级中断记录：
                                                          说明：
                                                          1.中断pri_allow_int触发时，将实时的dcq_pri_allow锁存到此寄存器；中断清除时清零；
                                                          2.中断的使能及清除，参考寄存器GLB_DCQ_INT_EN/GLB_INT_STATUS/GLB_INT_CLEAR。 */
        unsigned int  reserved_2     : 1;  /* bit[11]   : 保留 */
        unsigned int  mst_pri_int_st : 3;  /* bit[12-14]: MST的允许优先级中断记录：
                                                          说明：
                                                          1.中断pri_allow_int触发时，将实时的mst_pri_allow锁存到此寄存器；中断清除时清零；
                                                          2.中断的使能及清除，参考寄存器GLB_DCQ_INT_EN/GLB_INT_STATUS/GLB_INT_CLEAR。 */
        unsigned int  reserved_3     : 17; /* bit[15-31]: 保留 */
    } reg;
} SOC_DMSS_GLB_DFX_DCQ_UNION;
#endif
#define SOC_DMSS_GLB_DFX_DCQ_dcq_pri_allow_START   (0)
#define SOC_DMSS_GLB_DFX_DCQ_dcq_pri_allow_END     (2)
#define SOC_DMSS_GLB_DFX_DCQ_mst_pri_allow_START   (4)
#define SOC_DMSS_GLB_DFX_DCQ_mst_pri_allow_END     (6)
#define SOC_DMSS_GLB_DFX_DCQ_dcq_pri_int_st_START  (8)
#define SOC_DMSS_GLB_DFX_DCQ_dcq_pri_int_st_END    (10)
#define SOC_DMSS_GLB_DFX_DCQ_mst_pri_int_st_START  (12)
#define SOC_DMSS_GLB_DFX_DCQ_mst_pri_int_st_END    (14)


/*****************************************************************************
 结构名    : SOC_DMSS_GLB_DFX_ASI_BUSY_UNION
 结构说明  : GLB_DFX_ASI_BUSY 寄存器结构定义。地址偏移量:0x6750，初值:0x00000000，宽度:32
 寄存器说明: DFX：各个ASI的工作状态
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  asi_busy : 12; /* bit[0-11] : 各个ASI的工作状态：
                                                    asi_busy[n]=0：ASIn处于idle状态；
                                                    asi_busy[n]=1：ASIn处于busy状态。
                                                    说明：
                                                    这里的idle是指：ASI所有outstanding命令及其数据和响应，都已经彻底处理完。
                                                    【Dallas】：
                                                    ASI0：MODEM
                                                    ASI1：VCODEC
                                                    ASI2/3：VIVO
                                                    ASI4：CCI/CPU
                                                    ASI5：SYS_BUS
                                                    ASI6：GPU */
        unsigned int  reserved : 20; /* bit[12-31]: 保留 */
    } reg;
} SOC_DMSS_GLB_DFX_ASI_BUSY_UNION;
#endif
#define SOC_DMSS_GLB_DFX_ASI_BUSY_asi_busy_START  (0)
#define SOC_DMSS_GLB_DFX_ASI_BUSY_asi_busy_END    (11)


/*****************************************************************************
 结构名    : SOC_DMSS_GLB_DFX_LOAD_UNION
 结构说明  : GLB_DFX_LOAD 寄存器结构定义。地址偏移量:0x6760，初值:0x00000000，宽度:32
 寄存器说明: DFX：仿真流量冲击状态
            （若RTL中配置DMSS_SIM_DFX_EN为0（通常ASIC版本配置为0，FPGA和EMULATOR版本定义为1），则此寄存器不存在）
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  rbuf0_load_cnt_st : 8;  /* bit[0-7]  : RBUF的buffer0的仿真负载情况：
                                                             n：缓存到的数据burst达到过的最大个数。 */
        unsigned int  rbuf1_load_cnt_st : 8;  /* bit[8-15] : 同rbuf0_load_cnt_st。 */
        unsigned int  rbuf2_load_cnt_st : 8;  /* bit[16-23]: 同rbuf0_load_cnt_st。 */
        unsigned int  rbuf3_load_cnt_st : 8;  /* bit[24-31]: 同rbuf0_load_cnt_st。 */
    } reg;
} SOC_DMSS_GLB_DFX_LOAD_UNION;
#endif
#define SOC_DMSS_GLB_DFX_LOAD_rbuf0_load_cnt_st_START  (0)
#define SOC_DMSS_GLB_DFX_LOAD_rbuf0_load_cnt_st_END    (7)
#define SOC_DMSS_GLB_DFX_LOAD_rbuf1_load_cnt_st_START  (8)
#define SOC_DMSS_GLB_DFX_LOAD_rbuf1_load_cnt_st_END    (15)
#define SOC_DMSS_GLB_DFX_LOAD_rbuf2_load_cnt_st_START  (16)
#define SOC_DMSS_GLB_DFX_LOAD_rbuf2_load_cnt_st_END    (23)
#define SOC_DMSS_GLB_DFX_LOAD_rbuf3_load_cnt_st_START  (24)
#define SOC_DMSS_GLB_DFX_LOAD_rbuf3_load_cnt_st_END    (31)






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

#endif /* end of soc_dmss_interface.h */
