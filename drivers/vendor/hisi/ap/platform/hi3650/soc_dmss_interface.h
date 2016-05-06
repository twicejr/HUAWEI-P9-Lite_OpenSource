/******************************************************************************

                 版权所有 (C), 2001-2015, 华为技术有限公司

 ******************************************************************************
  文 件 名   : soc_dmss_interface.h
  版 本 号   : 初稿
  作    者   : Excel2Code
  生成日期   : 2015-03-09 16:17:08
  最近修改   :
  功能描述   : 接口头文件
  函数列表   :
  修改历史   :
  1.日    期   : 2015年3月9日
    作    者   : fWX220878
    修改内容   : 从《Hi3650V100 SOC寄存器手册_DMSS.xml》自动生成

******************************************************************************/

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

/* 寄存器说明：读命令OSTD限制
   位域定义UNION结构:  SOC_DMSS_ASI_QOS_RDOSTD_UNION */
#define SOC_DMSS_ASI_QOS_RDOSTD_ADDR(base, asi_base)  ((base) + (0x160+0x800*(asi_base)))

/* 寄存器说明：读命令OSTD状态统计
   位域定义UNION结构:  SOC_DMSS_ASI_QOS_RDOSTD_ST_UNION */
#define SOC_DMSS_ASI_QOS_RDOSTD_ST_ADDR(base, asi_base)  ((base) + (0x164+0x800*(asi_base)))

/* 寄存器说明：流量统计控制
   位域定义UNION结构:  SOC_DMSS_ASI_FLUX_STAT_CTRL_UNION */
#define SOC_DMSS_ASI_FLUX_STAT_CTRL_ADDR(base, asi_base)  ((base) + (0x170+0x800*(asi_base)))

/* 寄存器说明：写流量统计
   位域定义UNION结构:  SOC_DMSS_ASI_FLUX_STAT_WR_UNION */
#define SOC_DMSS_ASI_FLUX_STAT_WR_ADDR(base, asi_base)  ((base) + (0x178+0x800*(asi_base)))

/* 寄存器说明：读流量统计
   位域定义UNION结构:  SOC_DMSS_ASI_FLUX_STAT_RD_UNION */
#define SOC_DMSS_ASI_FLUX_STAT_RD_ADDR(base, asi_base)  ((base) + (0x17C+0x800*(asi_base)))

/* 寄存器说明：写命令同MID命令优先级传递使能
   位域定义UNION结构:  SOC_DMSS_ASI_PUSH_WRMID_UNION */
#define SOC_DMSS_ASI_PUSH_WRMID_ADDR(base, asi_base)  ((base) + (0x180+0x800*(asi_base)))

/* 寄存器说明：读命令同MID命令优先级传递使能
   位域定义UNION结构:  SOC_DMSS_ASI_PUSH_RDMID_UNION */
#define SOC_DMSS_ASI_PUSH_RDMID_ADDR(base, asi_base)  ((base) + (0x184+0x800*(asi_base)))

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

/* 寄存器说明：RBUF的命令反压配置
   位域定义UNION结构:  SOC_DMSS_GLB_RBUF_BP_UNION */
#define SOC_DMSS_GLB_RBUF_BP_ADDR(base, rbuf_bp_grps)  ((base) + (0x6150+0x4*(rbuf_bp_grps)))

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
        unsigned int  rtl_data_width    : 1;  /* bit[0]    : 对接的AXI总线地址位宽。
                                                             0：64bits
                                                             1：128bits */
        unsigned int  reserved_0        : 3;  /* bit[1-3]  : 保留 */
        unsigned int  rtl_clk_mode      : 2;  /* bit[4-5]  : 对接AXI总线时钟与DMSS主时钟的关系
                                                             0x0：低频同步（低频的AXI总线侧不可以设置multicycle，需以高频时钟收时序）；
                                                             0x1：低频同步（低频的AXI总线侧可以设置multicycle，可按低频时钟收时序）；
                                                             0x2：异步；
                                                             0x3：同频同步。
                                                             注意：当对接时钟关系不是异步时，异步相关寄存器无效。 */
        unsigned int  reserved_1        : 10; /* bit[6-15] : 保留 */
        unsigned int  rtl_rdr_que_depth : 2;  /* bit[16-17]: 保序模块的读命令队列监控深度（等效为允许的最大读命令outstanding）。
                                                             0： 8 read cmd；
                                                             1：16 read cmd；
                                                             2：24 read cmd；
                                                             3：32 read cmd。 */
        unsigned int  reserved_2        : 2;  /* bit[18-19]: 保留 */
        unsigned int  rtl_rdr_buf_num   : 2;  /* bit[20-21]: 保序模块的保序buffer深度。
                                                             0： 8 read burst；
                                                             1：16 read burst；
                                                             2：24 read burst；
                                                             3：32 read burst。 */
        unsigned int  reserved_3        : 2;  /* bit[22-23]: 保留 */
        unsigned int  rtl_rdr_en        : 1;  /* bit[24]   : 同ID读保序功能。
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
        unsigned int  rtl_wcmd_fifo_depth : 5;  /* bit[0-4]  : 写命令FIFO配置深度。
                                                               0x0： 1 write cmd；
                                                               0x1： 2 write cmd；
                                                               ……
                                                               0x31：32 write cmd。 */
        unsigned int  reserved_0          : 3;  /* bit[5-7]  : 保留 */
        unsigned int  rtl_wd_fifo_depth   : 5;  /* bit[8-12] : 写数据FIFO配置深度。
                                                               0x0： 1 write transfer；
                                                               0x1： 2 write transfer；
                                                               ……
                                                               0x31：32 write transfer。 */
        unsigned int  reserved_1          : 3;  /* bit[13-15]: 保留 */
        unsigned int  rtl_b_fifo_depth    : 5;  /* bit[16-20]: 写响应FIFO配置深度。
                                                               0x0： 1 write response；
                                                               0x1： 2 write response；
                                                               ……
                                                               0x31：32 write response。 */
        unsigned int  reserved_2          : 3;  /* bit[21-23]: 保留 */
        unsigned int  rtl_ra_fifo_depth   : 5;  /* bit[24-28]: 速率匹配写数据FIFO配置深度。
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
        unsigned int  rtl_rbar_fifo_depth : 5;  /* bit[0-4]  : 读barrier命令FIFO配置深度。
                                                               0x0： 1 barrier cmd；
                                                               0x1： 2 barrier cmd；
                                                               ……
                                                               0x31：32 barrier cmd。 */
        unsigned int  reserved_0          : 3;  /* bit[5-7]  : 保留 */
        unsigned int  rtl_rd_fifo_depth   : 5;  /* bit[8-12] : 读数据FIFO配置深度。
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
        unsigned int  rtl_sec_rgn_num : 5;  /* bit[0-4] : 安全模块的regions个数。
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
                                                      1:匹配失败的ID，参与保序判定； */
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
        unsigned int  intlv_mid_0  : 2;  /* bit[0-1]  : 对MID（只识别最低五位）为0的读命令进行RBUF中数据间插模式的配置。
                                                        0x0，0x1：间插模式一，收到第一个transfer时便提起传输请求（保证首数据最小latency）；
                                                        0x2：间插模式二，收到最后一个transfer时才提起传输请求（保证数据不被间插）；
                                                        0x3：间插模式三，收到可配置的transfer个数或命令所有transfer时便提起传输请求，相关配置请参考传输起始水线ASI_RBUF_TRSFR_WL寄存器（合理配置，可保证到尾数据最小latency）。
                                                        说明：
                                                        间插模式三时，根据传输起始水线配置和数据写入到RBUF的速率：
                                                        1.若能保证数据发送过程中，所有剩余数据都能及时写入RBUF，则传输不会被间插；
                                                        2.若能保证数据发送到最后一个tansfer时，其数据正好被写入RBUF，则能保证尾数据的最小latency（RBUF静态latency为4或5cycles，取决于RTL配置） */
        unsigned int  intlv_mid_1  : 2;  /* bit[2-3]  : 同intlv_mid_0配置 */
        unsigned int  intlv_mid_2  : 2;  /* bit[4-5]  : 同intlv_mid_0配置 */
        unsigned int  intlv_mid_3  : 2;  /* bit[6-7]  : 同intlv_mid_0配置 */
        unsigned int  intlv_mid_4  : 2;  /* bit[8-9]  : 同intlv_mid_0配置 */
        unsigned int  intlv_mid_5  : 2;  /* bit[10-11]: 同intlv_mid_0配置 */
        unsigned int  intlv_mid_6  : 2;  /* bit[12-13]: 同intlv_mid_0配置 */
        unsigned int  intlv_mid_7  : 2;  /* bit[14-15]: 同intlv_mid_0配置 */
        unsigned int  intlv_mid_8  : 2;  /* bit[16-17]: 同intlv_mid_0配置 */
        unsigned int  intlv_mid_9  : 2;  /* bit[18-19]: 同intlv_mid_0配置 */
        unsigned int  intlv_mid_10 : 2;  /* bit[20-21]: 同intlv_mid_0配置 */
        unsigned int  intlv_mid_11 : 2;  /* bit[22-23]: 同intlv_mid_0配置 */
        unsigned int  intlv_mid_12 : 2;  /* bit[24-25]: 同intlv_mid_0配置 */
        unsigned int  intlv_mid_13 : 2;  /* bit[26-27]: 同intlv_mid_0配置 */
        unsigned int  intlv_mid_14 : 2;  /* bit[28-29]: 同intlv_mid_0配置 */
        unsigned int  intlv_mid_15 : 2;  /* bit[30-31]: 同intlv_mid_0配置 */
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
        unsigned int  intlv_mid_16 : 2;  /* bit[0-1]  : 对MID（只识别最低五位）为16的读命令进行RBUF中数据间插模式的配置。
                                                        0x0，0x1：间插模式一，收到第一个transfer时便提起传输请求（保证首数据最小latency）；
                                                        0x2：间插模式二，收到最后一个transfer时才提起传输请求（保证数据不被间插）；
                                                        0x3：间插模式三，收到可配置的transfer个数或该命令所有transfer时便提起传输请求，相关配置请参考传输起始水线ASI_RBUF_TRSFR_WL寄存器（合理配置，可保证到尾数据最小latency）。
                                                        说明：
                                                        间插模式三时，根据传输起始水线配置和数据写入到RBUF的速率：
                                                        1.若能保证数据发送过程中，所有剩余数据都能及时写入RBUF，则传输不会被间插；
                                                        2.若能保证数据发送到最后一个tansfer时，其数据正好被写入RBUF，则能保证尾数据的最小latency（RBUF静态latency为4或5cycles，取决于RTL配置） */
        unsigned int  intlv_mid_17 : 2;  /* bit[2-3]  : 同intlv_mid_16配置 */
        unsigned int  intlv_mid_18 : 2;  /* bit[4-5]  : 同intlv_mid_16配置 */
        unsigned int  intlv_mid_19 : 2;  /* bit[6-7]  : 同intlv_mid_16配置 */
        unsigned int  intlv_mid_20 : 2;  /* bit[8-9]  : 同intlv_mid_16配置 */
        unsigned int  intlv_mid_21 : 2;  /* bit[10-11]: 同intlv_mid_16配置 */
        unsigned int  intlv_mid_22 : 2;  /* bit[12-13]: 同intlv_mid_16配置 */
        unsigned int  intlv_mid_23 : 2;  /* bit[14-15]: 同intlv_mid_16配置 */
        unsigned int  intlv_mid_24 : 2;  /* bit[16-17]: 同intlv_mid_16配置 */
        unsigned int  intlv_mid_25 : 2;  /* bit[18-19]: 同intlv_mid_16配置 */
        unsigned int  intlv_mid_26 : 2;  /* bit[20-21]: 同intlv_mid_16配置 */
        unsigned int  intlv_mid_27 : 2;  /* bit[22-23]: 同intlv_mid_16配置 */
        unsigned int  intlv_mid_28 : 2;  /* bit[24-25]: 同intlv_mid_16配置 */
        unsigned int  intlv_mid_29 : 2;  /* bit[26-27]: 同intlv_mid_16配置 */
        unsigned int  intlv_mid_30 : 2;  /* bit[28-29]: 同intlv_mid_16配置 */
        unsigned int  intlv_mid_31 : 2;  /* bit[30-31]: 同intlv_mid_16配置 */
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
        unsigned int  reserved_2       : 19; /* bit[13-31]: 保留 */
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
        unsigned int  wr_pri1  : 3;  /* bit[4-6]  : 类同wr_pri0的配置 */
        unsigned int  reserved_1: 1;  /* bit[7]    : 保留 */
        unsigned int  wr_pri2  : 3;  /* bit[8-10] : 类同wr_pri0的配置 */
        unsigned int  reserved_2: 1;  /* bit[11]   : 保留 */
        unsigned int  wr_pri3  : 3;  /* bit[12-14]: 类同wr_pri0的配置 */
        unsigned int  reserved_3: 1;  /* bit[15]   : 保留 */
        unsigned int  wr_pri4  : 3;  /* bit[16-18]: 类同wr_pri0的配置 */
        unsigned int  reserved_4: 1;  /* bit[19]   : 保留 */
        unsigned int  wr_pri5  : 3;  /* bit[20-22]: 类同wr_pri0的配置 */
        unsigned int  reserved_5: 1;  /* bit[23]   : 保留 */
        unsigned int  wr_pri6  : 3;  /* bit[24-26]: 类同wr_pri0的配置 */
        unsigned int  reserved_6: 1;  /* bit[27]   : 保留 */
        unsigned int  wr_pri7  : 3;  /* bit[28-30]: 类同wr_pri0的配置 */
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
        unsigned int  rd_pri1  : 3;  /* bit[4-6]  : 类同rd_pri0的配置 */
        unsigned int  reserved_1: 1;  /* bit[7]    : 保留 */
        unsigned int  rd_pri2  : 3;  /* bit[8-10] : 类同rd_pri0的配置 */
        unsigned int  reserved_2: 1;  /* bit[11]   : 保留 */
        unsigned int  rd_pri3  : 3;  /* bit[12-14]: 类同rd_pri0的配置 */
        unsigned int  reserved_3: 1;  /* bit[15]   : 保留 */
        unsigned int  rd_pri4  : 3;  /* bit[16-18]: 类同rd_pri0的配置 */
        unsigned int  reserved_4: 1;  /* bit[19]   : 保留 */
        unsigned int  rd_pri5  : 3;  /* bit[20-22]: 类同rd_pri0的配置 */
        unsigned int  reserved_5: 1;  /* bit[23]   : 保留 */
        unsigned int  rd_pri6  : 3;  /* bit[24-26]: 类同rd_pri0的配置 */
        unsigned int  reserved_6: 1;  /* bit[27]   : 保留 */
        unsigned int  rd_pri7  : 3;  /* bit[28-30]: 类同rd_pri0的配置 */
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
        unsigned int  rd_adpt_low  : 4;  /* bit[0-3]  : 读命令优先级自适应周期配置（低档位）
                                                        0x0：禁止优先级自适应功能；
                                                        0x1～0xF：N×16个时钟周期。
                                                        说明：
                                                        每当自适应周期到达后，命令优先级自动提升一级，直到提升至次最高优先级（优先级6）。 */
        unsigned int  rd_adpt_lvl  : 3;  /* bit[4-6]  : 读命令优先级自适应周期配置水线
                                                        0x0～0x6：命令优先级高于此水线时，使用高档位配置，否则使用低档位配置；
                                                        0x7：reserved。
                                                        举例：
                                                        0x3：优先级4~5的读命令使用rd_pri_adpt_high，优先级0～3的读命令使用rd_pri_adpt_low。 */
        unsigned int  reserved_0   : 1;  /* bit[7]    : 保留 */
        unsigned int  rd_adpt_high : 4;  /* bit[8-11] : 读命令优先级自适应周期配置（高档位）
                                                        同rd_pri_adpt_low的配置。 */
        unsigned int  reserved_1   : 4;  /* bit[12-15]: 保留 */
        unsigned int  wr_adpt_low  : 4;  /* bit[16-19]: 写命令优先级自适应周期配置（低档位）
                                                        同rd_pri_adpt_low的配置。 */
        unsigned int  wr_adpt_lvl  : 3;  /* bit[20-22]: 写命令优先级自适应周期配置水线
                                                        同rd_pri_adpt_lvl的配置。 */
        unsigned int  reserved_2   : 1;  /* bit[23]   : 保留 */
        unsigned int  wr_adpt_high : 4;  /* bit[24-27]: 写命令优先级自适应周期配置（高档位）
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
                                                           乘256的目的是保留设定期望带宽的高8位小数； */
        unsigned int  reserved_1      : 1;  /* bit[29]   : 保留 */
        unsigned int  rglr_type       : 1;  /* bit[30]   : 带宽优先级控制的命令类型：
                                                           0：只控制读命令优先级；
                                                           1：同时控制读写命令优先级；
                                                           注意：
                                                           当配置为“同时控制读写命令优先级”时，ASI_QOS_RGLR1将被自动禁止使用。 */
        unsigned int  rglr_en         : 1;  /* bit[31]   : regulator使能：
                                                           0：禁止；
                                                           1：使能。 */
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
                                                           乘256的目的是保留设定期望带宽的高8位小数； */
        unsigned int  reserved_1      : 2;  /* bit[29-30]: 保留 */
        unsigned int  rglr_en         : 1;  /* bit[31]   : regulator使能：
                                                           0：禁止；
                                                           1：使能。
                                                           注意：
                                                           1.ASI_QOS_RGLR1只能控制写带宽；
                                                           2.当ASI_QOS_RGLR0配置为“同时控制读写命令带宽”时，ASI_QOS_RGLR1将被自动禁止使用。 */
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
                                                           1：同时控制读写总带宽。
                                                           注意：
                                                           当配置为“同时控制读写命令带宽”时，ASI_QOS_LMTR1将被自动禁止使用。 */
        unsigned int  lmtr_en         : 1;  /* bit[31]   : limiter使能：
                                                           0：禁止；
                                                           1：使能。
                                                           注意： */
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
                                                           1.ASI_QOS_LMTR1只能控制写带宽；
                                                           2.当ASI_QOS_LMTR0配置为“同时控制读写命令带宽”时，ASI_QOS_LMTR1将被自动禁止使用。 */
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
 结构名    : SOC_DMSS_ASI_FLUX_STAT_CTRL_UNION
 结构说明  : ASI_FLUX_STAT_CTRL 寄存器结构定义。地址偏移量:0x170+0x800*(asi_base)，初值:0x00000000，宽度:32
 寄存器说明: 流量统计控制
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  flux_stat_rd_en : 1;  /* bit[0]   : 读流量监测使能。
                                                          0：关闭；
                                                          1：使能。
                                                          说明：
                                                          1.流量统计结果记录在流量寄存器AXI_FLUX_STAT_RD中；
                                                          2.流量寄存器记满后会卷绕；
                                                          3.重新启动flux_stat_rd_en，流量寄存器自动清零。 */
        unsigned int  flux_stat_wr_en : 1;  /* bit[1]   : 写流量监测使能。
                                                          0：关闭；
                                                          1：使能。
                                                          说明：
                                                          1.流量统计结果记录在流量寄存器AXI_FLUX_STAT_WR中；
                                                          2.流量寄存器记满后会卷绕；
                                                          3.重新启动flux_stat_wr_en，流量寄存器自动清零。 */
        unsigned int  reserved        : 30; /* bit[2-31]: 保留 */
    } reg;
} SOC_DMSS_ASI_FLUX_STAT_CTRL_UNION;
#endif
#define SOC_DMSS_ASI_FLUX_STAT_CTRL_flux_stat_rd_en_START  (0)
#define SOC_DMSS_ASI_FLUX_STAT_CTRL_flux_stat_rd_en_END    (0)
#define SOC_DMSS_ASI_FLUX_STAT_CTRL_flux_stat_wr_en_START  (1)
#define SOC_DMSS_ASI_FLUX_STAT_CTRL_flux_stat_wr_en_END    (1)


/*****************************************************************************
 结构名    : SOC_DMSS_ASI_FLUX_STAT_WR_UNION
 结构说明  : ASI_FLUX_STAT_WR 寄存器结构定义。地址偏移量:0x178+0x800*(asi_base)，初值:0x00000000，宽度:32
 寄存器说明: 写流量统计
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  flux_stat_wr : 32; /* bit[0-31]: 写流量统计（需配合ASI_FLUX_STAT_CTRL寄存器使用）：
                                                       说明：
                                                       1.累加所有写命令对应的数据流量，单位为Byte；
                                                       2.当下一次统计开始时自动清零；
                                                       3.溢出后卷绕计数；
                                                       4.32bit计数器，即量程为4GB。 */
    } reg;
} SOC_DMSS_ASI_FLUX_STAT_WR_UNION;
#endif
#define SOC_DMSS_ASI_FLUX_STAT_WR_flux_stat_wr_START  (0)
#define SOC_DMSS_ASI_FLUX_STAT_WR_flux_stat_wr_END    (31)


/*****************************************************************************
 结构名    : SOC_DMSS_ASI_FLUX_STAT_RD_UNION
 结构说明  : ASI_FLUX_STAT_RD 寄存器结构定义。地址偏移量:0x17C+0x800*(asi_base)，初值:0x00000000，宽度:32
 寄存器说明: 读流量统计
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  flux_stat_rd : 32; /* bit[0-31]: 读流量统计（需配合ASI_FLUX_STAT_CTRL寄存器使用）：
                                                       说明：
                                                       1.累加所有读命令对应的数据流量，单位为Byte；
                                                       2.当下一次统计开始时自动清零；
                                                       3.溢出后卷绕计数；
                                                       4.32bit计数器，即量程为4GB。 */
    } reg;
} SOC_DMSS_ASI_FLUX_STAT_RD_UNION;
#endif
#define SOC_DMSS_ASI_FLUX_STAT_RD_flux_stat_rd_START  (0)
#define SOC_DMSS_ASI_FLUX_STAT_RD_flux_stat_rd_END    (31)


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
        unsigned int  wr_mid_sel : 32; /* bit[0-31]: 写命令MID（最低五位）的比特匹配选择。
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
        unsigned int  rd_mid_sel : 32; /* bit[0-31]: 读命令MID（最低五位）的比特匹配选择。
                                                     rd_mid_sel[n]=0：对于MID=n的命令，在QOSBUF中禁止同MID读命令优先级传递功能；
                                                     rd_mid_sel[n]=1：对于MID=n的命令，在QOSBUF中使能同MID读命令优先级传递功能。 */
    } reg;
} SOC_DMSS_ASI_PUSH_RDMID_UNION;
#endif
#define SOC_DMSS_ASI_PUSH_RDMID_rd_mid_sel_START  (0)
#define SOC_DMSS_ASI_PUSH_RDMID_rd_mid_sel_END    (31)


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
        unsigned int  ld_rgn_map    : 1;  /* bit[0]    : 拉高sucure_boot_lock信号后，锁定被ld_rgns_sel选定region的ASI_SEC_REGION_MAP寄存器为只读。
                                                         0：不锁定；
                                                         1：锁定。
                                                         本寄存器自身被锁定条件：sucure_boot_lock信号被拉高过。 */
        unsigned int  ld_rgn_attrib : 1;  /* bit[1]    : 拉高sucure_boot_lock信号后，锁定被ld_rgns_sel选定region的ASI_SEC_REGION_ATTRIB寄存器为只读。
                                                         0：不锁定；
                                                         1：锁定。
                                                         本寄存器自身被锁定条件：sucure_boot_lock信号被拉高过。 */
        unsigned int  ld_mid_rd     : 1;  /* bit[2]    : 拉高sucure_boot_lock信号后，锁定被ld_rgns_sel选定region的ASI_SEC_MID_RD寄存器为只读。
                                                         0：不锁定；
                                                         1：锁定。
                                                         本寄存器自身被锁定条件：sucure_boot_lock信号被拉高过。 */
        unsigned int  ld_mid_wr     : 1;  /* bit[3]    : 拉高sucure_boot_lock信号后，锁定被ld_rgns_sel选定region的ASI_SEC_MID_WR寄存器为只读。
                                                         0：不锁定；
                                                         1：锁定。
                                                         本寄存器自身被锁定条件：sucure_boot_lock信号被拉高过。 */
        unsigned int  reserved_0    : 12; /* bit[4-15] : 保留 */
        unsigned int  ld_rgns_sel   : 5;  /* bit[16-20]: 选择需将相关配置寄存器锁定为只读的regions范围。
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
        unsigned int  int_status  : 1;  /* bit[0]   : 中断状态指示
                                                      0：中断未产生；
                                                      1：中断已产生。
                                                      注意：从GLOBAL模块的GLB_INT_STATUS寄存器中，可识别出中断来自于哪个ASI中的SEC模块 */
        unsigned int  int_overrun : 1;  /* bit[1]   : 多次中断指示
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
        unsigned int  address_low : 32; /* bit[0-31]: 中断状态清除前的首个越权命令的低32位地址 */
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
        unsigned int  address_high : 8;  /* bit[0-7]  : 中断状态清除前的首个越权命令的高位地址（如果存在高位地址） */
        unsigned int  reserved_0   : 8;  /* bit[8-15] : 保留 */
        unsigned int  privileged   : 1;  /* bit[16]   : 中断状态清除前首个越权命令的特权模式信息
                                                        0：unprivileged访问；
                                                        1：privileged访问。 */
        unsigned int  nonsecure    : 1;  /* bit[17]   : 中断状态清除前首个越权命令的安全模式信息
                                                        0：secure访问；
                                                        1：non-secure访问。 */
        unsigned int  reserved_1   : 2;  /* bit[18-19]: 保留 */
        unsigned int  access_type  : 1;  /* bit[20]   : 中断状态清除前首个越权命令的读写模式信息
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
        unsigned int  id  : 24; /* bit[0-23] : 中断状态清除前的首个越权命令的命令ID */
        unsigned int  mid : 8;  /* bit[24-31]: 中断状态清除前的首个越权命令的命令MasterID */
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
        unsigned int  int_test_en : 1;  /* bit[0]   : 中断测试使能。
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
        unsigned int  itip_secure_boot_lock : 1;  /* bit[0]   : 寄存器保护的锁定状态指示。
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
        unsigned int  itop_int : 1;  /* bit[0]   : 中断状态设置。
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
        unsigned int  rgn_base_addr : 24; /* bit[0-23] : 各个区域的起始地址设置（高位部分）
                                                         设置地址的[39:16]位。
                                                         注意：
                                                         1.rgn0不可配置，默认覆盖整个地址空间；
                                                         2.需保证exclusive命令访问的地址区域有响应的访问权限，否则exclusive命令无法被正常监控。 */
        unsigned int  rgn_size      : 6;  /* bit[24-29]: 当前区域的大小。
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
        unsigned int  rgn_en        : 1;  /* bit[31]   : 各个区域的使能控制
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
        unsigned int  mid_sel_wr : 32; /* bit[0-31]: MID的比特匹配选择（写命令）。
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
        unsigned int  mid_sel_rd : 32; /* bit[0-31]: MID的比特匹配选择（读命令）。
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
        unsigned int  wr_ostd_st : 5;  /* bit[0-4] : 写命令outstanding统计。
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
        unsigned int  dfx_int_en : 1;  /* bit[0]   : 异常命令的中断输出使能。
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
        unsigned int  dfx_int_status : 1;  /* bit[0]   : 中断状态指示
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
        unsigned int  abnm_cmd_mid   : 15; /* bit[16-30]: 首个异常命令的MasterID。
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
                                                    0x100：HiDMSSV100 */
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
        unsigned int  rtl_addr_width     : 4;  /* bit[0-3]  : AXI总线地址位宽。
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
        unsigned int  rtl_id_width       : 5;  /* bit[4-8]  : AXI命令ID位宽。
                                                              0:reserved；
                                                              1:1bits；
                                                              2:2bits；
                                                              ……
                                                              31:31bits。 */
        unsigned int  reserved_0         : 3;  /* bit[9-11] : 保留 */
        unsigned int  rtl_mid_width      : 4;  /* bit[12-15]: Master ID位宽。
                                                              0:reserved；
                                                              1:1bits；
                                                              2:2bits；
                                                              ……
                                                              15:15bits。 */
        unsigned int  rtl_dmi_num        : 1;  /* bit[16]   : DMI(DDRC Master Interface)个数
                                                              0：1个DMI；
                                                              1：2个DMI。 */
        unsigned int  reserved_1         : 1;  /* bit[17]   : 保留 */
        unsigned int  rtl_ch_num_pre_dmi : 1;  /* bit[18]   : 每个DMI对接的通道个数
                                                              0：1 channel per DMI；
                                                              1：2 channel per DMI。 */
        unsigned int  reserved_2         : 1;  /* bit[19]   : 保留 */
        unsigned int  rtl_asi_num        : 4;  /* bit[20-23]: ASI（AXI Slave Interface）个数：
                                                              0x0： 1个ASI；
                                                              ……
                                                              0xB：12个ASI；
                                                              其它：reserved */
        unsigned int  rtl_exclusive_num  : 6;  /* bit[24-29]: 可同时监视的不同exclusive命令的最大个数：
                                                              0x00：不支持exclusive命令；
                                                              0x01：1个；
                                                              0x02：2个；
                                                              ……
                                                              0x1F：31个；
                                                              0x20：32个；
                                                              其它：reserved */
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
        unsigned int  rtl_rbuf_buf_num : 6;  /* bit[0-5] : RBUF模块的数据buffer深度。
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
        unsigned int  ram_tmod : 16; /* bit[0-15] : 根据MEMORY的不同类型及工艺配置 */
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
        unsigned int  reserved           : 28; /* bit[4-31]: 保留 */
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
        unsigned int  asi_sec_int  : 12; /* bit[0-11] : 安全功能中断状态：
                                                        asi_sec_int[n]=1：安全中断来自ASIn。 */
        unsigned int  reserved_0   : 4;  /* bit[12-15]: 保留 */
        unsigned int  asi_dfx_int  : 12; /* bit[16-27]: DFX功能中断状态：
                                                        asi_dfx_int[n]=1：DFX中断来自ASIn。 */
        unsigned int  cfg_lock_int : 1;  /* bit[28]   : 寄存器锁定访问中断。
                                                        说明：
                                                        当寄存器锁定时，若有对寄存器的配置访问，则产生寄存器锁定访问中断。中断使能在GLB_CFG_LOCK寄存器中。 */
        unsigned int  reserved_1   : 3;  /* bit[29-31]: 保留 */
    } reg;
} SOC_DMSS_GLB_INT_STATUS_UNION;
#endif
#define SOC_DMSS_GLB_INT_STATUS_asi_sec_int_START   (0)
#define SOC_DMSS_GLB_INT_STATUS_asi_sec_int_END     (11)
#define SOC_DMSS_GLB_INT_STATUS_asi_dfx_int_START   (16)
#define SOC_DMSS_GLB_INT_STATUS_asi_dfx_int_END     (27)
#define SOC_DMSS_GLB_INT_STATUS_cfg_lock_int_START  (28)
#define SOC_DMSS_GLB_INT_STATUS_cfg_lock_int_END    (28)


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
        unsigned int  asi_sec_int_clear  : 12; /* bit[0-11] : 对应bit写1，可清除对应ASI的安全功能中断状态：
                                                              asi_sec_int_clear[n]=1：清除的安全功能中断状态来自ASIn。 */
        unsigned int  reserved_0         : 4;  /* bit[12-15]: 保留 */
        unsigned int  asi_dfx_int_clear  : 12; /* bit[16-27]: 对应bit写1，可清除对应ASI的DFX功能中断状态：
                                                              asi_dfx_int_clear[n]=1：清除的DFX中断状态来自ASIn。 */
        unsigned int  cfg_lock_int_clear : 1;  /* bit[28]   : 对应bit写1，可清除寄存器锁定访问中断。 */
        unsigned int  reserved_1         : 3;  /* bit[29-31]: 保留 */
    } reg;
} SOC_DMSS_GLB_INT_CLEAR_UNION;
#endif
#define SOC_DMSS_GLB_INT_CLEAR_asi_sec_int_clear_START   (0)
#define SOC_DMSS_GLB_INT_CLEAR_asi_sec_int_clear_END     (11)
#define SOC_DMSS_GLB_INT_CLEAR_asi_dfx_int_clear_START   (16)
#define SOC_DMSS_GLB_INT_CLEAR_asi_dfx_int_clear_END     (27)
#define SOC_DMSS_GLB_INT_CLEAR_cfg_lock_int_clear_START  (28)
#define SOC_DMSS_GLB_INT_CLEAR_cfg_lock_int_clear_END    (28)


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
                                                     1：addr[14:12] = addr[14:12] xor addr[20:18]（双通道）
                                                     2：addr[14:12] = addr[14:12] xor addr[21:19]（双通道）
                                                     3：addr[14:12] = addr[14:12] xor addr[22:20]（双通道）
                                                     4：addr[13:11] = addr[13:11] xor addr[19:17]（四通道）
                                                     5：addr[13:11] = addr[13:11] xor addr[20:18]（四通道）
                                                     6：addr[13:11] = addr[13:11] xor addr[21:19]（四通道）
                                                     7~15：reserved
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
                                                    1.这里的idle是指：ASI所有outstanding命令及其数据和响应，都已经彻底处理完；
                                                    2.当系统挂死且某asi_busy=1时，可检查其对应的写/读outstanding状态（wr_ostd_st和rd_ostd_st寄存器），若二者其中一个不为零，则很可能是写/读命令挂死；若二者均非零，则须检查对应DDRC中DMC的相关寄存器（dmc_cv/dmc_ct/wgntfifo_e/rdtimeout_intsts等）
                                                    3.Austin项目中，各个ASI对接的master为：
                                                    ASI0： MODEM
                                                    ASI1/2： VCODEC
                                                    ASI3/4： VIVO
                                                    ASI5： IVP32
                                                    ASI6/7： CCI（CPU）
                                                    ASI8： SYS_PERI
                                                    ASI9/10：GPU */
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
