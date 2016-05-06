//******************************************************************************
// Copyright (C), 2008-2014, Hisilicon Technologies Co., Ltd.
// Project name   : Hi3630
// File name      : reg_offset.h
// Author         : xxx
// Abstract       : The offset address definition for the module ASP_IPC_NS
// Others         : Generated automatically by nManager 
//------------------------------------------------------------------------------
// Modification History: 
// 
//******************************************************************************

/* ASP_IPC_NS 模块寄存器基地址 */
#define HI3630_ASP_IPC_NS_BASE                    (0xE804C000)

/******************************************************************************/
/*                      Hi3630 ASP_IPC_NS 寄存器定义                          */
/******************************************************************************/
#define HI3630_ASP_IPC_NS_MBX_SOURCE_0_REG        (HI3630_ASP_IPC_NS_BASE + 0x0)   /* 源处理器配置寄存器 */
#define HI3630_ASP_IPC_NS_MBX_SOURCE_1_REG        (HI3630_ASP_IPC_NS_BASE + 0x40)  /* 源处理器配置寄存器 */
#define HI3630_ASP_IPC_NS_MBX_SOURCE_2_REG        (HI3630_ASP_IPC_NS_BASE + 0x80)  /* 源处理器配置寄存器 */
#define HI3630_ASP_IPC_NS_MBX_SOURCE_3_REG        (HI3630_ASP_IPC_NS_BASE + 0xC0)  /* 源处理器配置寄存器 */
#define HI3630_ASP_IPC_NS_MBX_DSET_0_REG          (HI3630_ASP_IPC_NS_BASE + 0x4)  /* 目的处理器设置寄存器 */
#define HI3630_ASP_IPC_NS_MBX_DSET_1_REG          (HI3630_ASP_IPC_NS_BASE + 0x44)  /* 目的处理器设置寄存器 */
#define HI3630_ASP_IPC_NS_MBX_DSET_2_REG          (HI3630_ASP_IPC_NS_BASE + 0x84)  /* 目的处理器设置寄存器 */
#define HI3630_ASP_IPC_NS_MBX_DSET_3_REG          (HI3630_ASP_IPC_NS_BASE + 0xC4)  /* 目的处理器设置寄存器 */
#define HI3630_ASP_IPC_NS_MBX_DCLEAR_0_REG        (HI3630_ASP_IPC_NS_BASE + 0x8)  /* 目的处理器清除寄存器 */
#define HI3630_ASP_IPC_NS_MBX_DCLEAR_1_REG        (HI3630_ASP_IPC_NS_BASE + 0x48)  /* 目的处理器清除寄存器 */
#define HI3630_ASP_IPC_NS_MBX_DCLEAR_2_REG        (HI3630_ASP_IPC_NS_BASE + 0x88)  /* 目的处理器清除寄存器 */
#define HI3630_ASP_IPC_NS_MBX_DCLEAR_3_REG        (HI3630_ASP_IPC_NS_BASE + 0xC8)  /* 目的处理器清除寄存器 */
#define HI3630_ASP_IPC_NS_MBX_DSTATUS_0_REG       (HI3630_ASP_IPC_NS_BASE + 0xC)  /* 目的处理器状态寄存器 */
#define HI3630_ASP_IPC_NS_MBX_DSTATUS_1_REG       (HI3630_ASP_IPC_NS_BASE + 0x4C)  /* 目的处理器状态寄存器 */
#define HI3630_ASP_IPC_NS_MBX_DSTATUS_2_REG       (HI3630_ASP_IPC_NS_BASE + 0x8C)  /* 目的处理器状态寄存器 */
#define HI3630_ASP_IPC_NS_MBX_DSTATUS_3_REG       (HI3630_ASP_IPC_NS_BASE + 0xCC)  /* 目的处理器状态寄存器 */
#define HI3630_ASP_IPC_NS_MBX_MODE_0_REG          (HI3630_ASP_IPC_NS_BASE + 0x10)  /* 邮箱通道模式状态机状态寄存器 */
#define HI3630_ASP_IPC_NS_MBX_MODE_1_REG          (HI3630_ASP_IPC_NS_BASE + 0x50)  /* 邮箱通道模式状态机状态寄存器 */
#define HI3630_ASP_IPC_NS_MBX_MODE_2_REG          (HI3630_ASP_IPC_NS_BASE + 0x90)  /* 邮箱通道模式状态机状态寄存器 */
#define HI3630_ASP_IPC_NS_MBX_MODE_3_REG          (HI3630_ASP_IPC_NS_BASE + 0xD0)  /* 邮箱通道模式状态机状态寄存器 */
#define HI3630_ASP_IPC_NS_MBX_IMASK_0_REG         (HI3630_ASP_IPC_NS_BASE + 0x14)  /* 处理器中断屏蔽寄存器 */
#define HI3630_ASP_IPC_NS_MBX_IMASK_1_REG         (HI3630_ASP_IPC_NS_BASE + 0x54)  /* 处理器中断屏蔽寄存器 */
#define HI3630_ASP_IPC_NS_MBX_IMASK_2_REG         (HI3630_ASP_IPC_NS_BASE + 0x94)  /* 处理器中断屏蔽寄存器 */
#define HI3630_ASP_IPC_NS_MBX_IMASK_3_REG         (HI3630_ASP_IPC_NS_BASE + 0xD4)  /* 处理器中断屏蔽寄存器 */
#define HI3630_ASP_IPC_NS_MBX_ICLR_0_REG          (HI3630_ASP_IPC_NS_BASE + 0x18)  /* 处理器中断状态清除寄存器 */
#define HI3630_ASP_IPC_NS_MBX_ICLR_1_REG          (HI3630_ASP_IPC_NS_BASE + 0x58)  /* 处理器中断状态清除寄存器 */
#define HI3630_ASP_IPC_NS_MBX_ICLR_2_REG          (HI3630_ASP_IPC_NS_BASE + 0x98)  /* 处理器中断状态清除寄存器 */
#define HI3630_ASP_IPC_NS_MBX_ICLR_3_REG          (HI3630_ASP_IPC_NS_BASE + 0xD8)  /* 处理器中断状态清除寄存器 */
#define HI3630_ASP_IPC_NS_MBX_SEND_0_REG          (HI3630_ASP_IPC_NS_BASE + 0x1C)  /* 发送寄存器 */
#define HI3630_ASP_IPC_NS_MBX_SEND_1_REG          (HI3630_ASP_IPC_NS_BASE + 0x5C)  /* 发送寄存器 */
#define HI3630_ASP_IPC_NS_MBX_SEND_2_REG          (HI3630_ASP_IPC_NS_BASE + 0x9C)  /* 发送寄存器 */
#define HI3630_ASP_IPC_NS_MBX_SEND_3_REG          (HI3630_ASP_IPC_NS_BASE + 0xDC)  /* 发送寄存器 */
#define HI3630_ASP_IPC_NS_MBX_DATA0_0_REG         (HI3630_ASP_IPC_NS_BASE + 0x20)  /* 数据0寄存器 */
#define HI3630_ASP_IPC_NS_MBX_DATA0_1_REG         (HI3630_ASP_IPC_NS_BASE + 0x60)  /* 数据0寄存器 */
#define HI3630_ASP_IPC_NS_MBX_DATA0_2_REG         (HI3630_ASP_IPC_NS_BASE + 0xA0)  /* 数据0寄存器 */
#define HI3630_ASP_IPC_NS_MBX_DATA0_3_REG         (HI3630_ASP_IPC_NS_BASE + 0xE0)  /* 数据0寄存器 */
#define HI3630_ASP_IPC_NS_MBX_DATA1_0_REG         (HI3630_ASP_IPC_NS_BASE + 0x24)  /* 数据1寄存器 */
#define HI3630_ASP_IPC_NS_MBX_DATA1_1_REG         (HI3630_ASP_IPC_NS_BASE + 0x64)  /* 数据1寄存器 */
#define HI3630_ASP_IPC_NS_MBX_DATA1_2_REG         (HI3630_ASP_IPC_NS_BASE + 0xA4)  /* 数据1寄存器 */
#define HI3630_ASP_IPC_NS_MBX_DATA1_3_REG         (HI3630_ASP_IPC_NS_BASE + 0xE4)  /* 数据1寄存器 */
#define HI3630_ASP_IPC_NS_CPU_IMST_0_REG          (HI3630_ASP_IPC_NS_BASE + 0x800)  /* 中断屏蔽状态寄存器 */
#define HI3630_ASP_IPC_NS_CPU_IMST_1_REG          (HI3630_ASP_IPC_NS_BASE + 0x808)  /* 中断屏蔽状态寄存器 */
#define HI3630_ASP_IPC_NS_CPU_IMST_2_REG          (HI3630_ASP_IPC_NS_BASE + 0x810)  /* 中断屏蔽状态寄存器 */
#define HI3630_ASP_IPC_NS_CPU_IMST_3_REG          (HI3630_ASP_IPC_NS_BASE + 0x818)  /* 中断屏蔽状态寄存器 */
#define HI3630_ASP_IPC_NS_CPU_IRST_0_REG          (HI3630_ASP_IPC_NS_BASE + 0x804)  /* 中断原始状态寄存器 */
#define HI3630_ASP_IPC_NS_CPU_IRST_1_REG          (HI3630_ASP_IPC_NS_BASE + 0x80C)  /* 中断原始状态寄存器 */
#define HI3630_ASP_IPC_NS_CPU_IRST_2_REG          (HI3630_ASP_IPC_NS_BASE + 0x814)  /* 中断原始状态寄存器 */
#define HI3630_ASP_IPC_NS_CPU_IRST_3_REG          (HI3630_ASP_IPC_NS_BASE + 0x81C)  /* 中断原始状态寄存器 */
#define HI3630_ASP_IPC_NS_IPC_MBX_ACTIVE_REG      (HI3630_ASP_IPC_NS_BASE + 0x900)  /* 有效通道状态寄存器 */
#define HI3630_ASP_IPC_NS_IPC_LOCK_REG            (HI3630_ASP_IPC_NS_BASE + 0xA00)  /* IPC lock寄存器。 */
