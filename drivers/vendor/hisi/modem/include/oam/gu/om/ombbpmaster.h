

/******************************************************************************

                  版权所有 (C), 2001-2011, 华为技术有限公司

 ******************************************************************************
  文 件 名   : OmBbpMaster.h
  版 本 号   : 初稿
  作    者   : 李霄 00246515
  生成日期   : 2014年12月31日

  最近修改   :
  功能描述   : BBE16上OmBbpMaster.c 的头文件
  函数列表   :
  修改历史   :
  1.日    期   : 2014年12月31日
    作    者   : 李霄 00246515
    修改内容   : 创建文件

******************************************************************************/

#ifndef __OMBBPMASTER_H__
#define __OMBBPMASTER_H__

#ifdef __cplusplus
#if __cplusplus
extern "C" {
#endif
#endif


/*****************************************************************************
  1 其他头文件包含
*****************************************************************************/

#include "vos.h"

#pragma pack(4)

/*****************************************************************************
  2 宏定义
*****************************************************************************/
#define OM_BBPMASTER_DBG_ON                             (0x1234)

#define OM_BBPMASTER_WR_CHANNEL                         (0) /* BBP Master写通道 */
#define OM_BBPMASTER_RD_CHANNEL                         (1) /* BBP Master写通道 */

#define OM_BBPMASTER_IPC_LOCK_IDLE                      (0)
#define OM_BBPMASTER_IPC_LOCK_BUSY                      (9)

#define OM_BBPMASTER_V8R1_WR_CHAN_CNT                   (5) /* 分配给V8R1 GUX的写通道数目 */
#define OM_BBPMASTER_V8R1_RD_CHAN_CNT                   (4) /* 分配给V8R1 GUX的读通道数目 */

#define OM_BBPMASTER_V7R5_WR_CHAN_CNT                   (6) /* 分配给V7R5 GUX的写通道数目 */
#define OM_BBPMASTER_V7R5_RD_CHAN_CNT                   (4) /* 分配给V7R5 GUX的读通道数目 */

#define OM_BBPMASTER_V8R5_WR_CHAN_CNT                   (14) /* 分配给V8R5 GUX的写通道数目 */
#define OM_BBPMASTER_V8R5_RD_CHAN_CNT                   (11) /* 分配给V8R5 GUX的读通道数目 */

#define OM_BBPMASTER_K3V6_WR_CHAN_CNT                   (24) /* 分配给V8R5 GUX的写通道数目 */
#define OM_BBPMASTER_K3V6_RD_CHAN_CNT                   (16) /* 分配给V8R5 GUX的读通道数目 */

#define OM_BBPMASTER_MAX_WR_CHAN_CNT                    OM_BBPMASTER_K3V6_WR_CHAN_CNT /* 最大写通道数目 */
#define OM_BBPMASTER_MAX_RD_CHAN_CNT                    OM_BBPMASTER_K3V6_RD_CHAN_CNT /* 最大读通道数目 */

#define OM_BBP_MASTER_CHAN_REG_OFFSET                   (4)

#define OM_BBP_MASTER_CHAN_REG_WIDTH                    (16)

#define OM_BBPMASTER_MASK_BIT_0                         (1 << 0)
#define OM_BBPMASTER_MASK_BIT_1                         (1 << 1)
#define OM_BBPMASTER_MASK_BIT_2                         (1 << 2)
#define OM_BBPMASTER_MASK_BIT_6                         (1 << 6)
#define OM_BBPMASTER_MASK_BIT_8                         (1 << 8)
#define OM_BBPMASTER_MASK_BIT_16                        (1 << 16)
#define OM_BBPMASTER_MASK_BIT_17                        (1 << 17)
#define OM_BBPMASTER_MASK_BIT_24                        (1 << 24)

#define OM_BBPMASTER_MASK_INTMODE                       (0x30000)

#define OM_IPC_SEM_INT_MASK(i)                          (0x604 + (i * 0x10))                /* 信号量释放中断掩码寄存器 */
#define OM_IPC_SEM_INT_CLR(i)                           (0x60C + (i * 0x10))                /* 信号量释放中断清除寄存器 */
#define OM_IPC_HS_CTRL(i,j)                             (0x800 + (i * 0x100) + (j * 0x8 ))  /* 信号量请求寄存器 */

#define OM_BBPMASTER_NULL_PTR                           (0)

#define OM_BBPMASTER_WR_MODE_OFFSET                     (0)
#define OM_BBPMASTER_WR_CLK_SEL_OFFSET                  (0x4)
#define OM_BBPMASTER_WR_BASE_ADDR_OFFSET                (0x8)
#define OM_BBPMASTER_WR_END_ADDR_OFFSET                 (0xC)
#define OM_BBPMASTER_WR_BURST_BEAT_OFFSET               (0x10)
#define OM_BBPMASTER_WR_AXI_SEL_OFFSET                  (0x14)
#define OM_BBPMASTER_WR_INTR_MODE_OFFSET                (0x18)

#define OM_BBPMASTER_RD_MODE_OFFSET                     (0)
#define OM_BBPMASTER_RD_CLK_SEL_OFFSET                  (0x4)
#define OM_BBPMASTER_RD_INIT_ADDR_OFFSET                (0x8)
#define OM_BBPMASTER_RD_BURST_BEAT_OFFSET               (0xC)
#define OM_BBPMASTER_RD_AXI_SEL_OFFSET                  (0x10)
#define OM_BBPMASTER_RD_INTR_MODE_OFFSET                (0x14)
#define OM_BBPMASTER_RD_BIT_WIDTH_IND_OFFSET            (0x18)
#if ( VOS_WIN32 == VOS_OS_VER )
#define IPC_SEM_BBPMASTER_0                             (10)    /* IPC资源锁10，用于写通道0互斥保护 */
#define IPC_SEM_BBPMASTER_5                             (15)    /* IPC资源锁15，用于读通道0互斥保护 */
#endif

#ifdef CSDR_FEATURE_ON
#define IPC_SEM_BBPMASTER_0                             (10)    /* IPC资源锁10，用于写通道0互斥保护 */

#define IPC_SEM_BBPMASTER_5                             (15)    /* IPC资源锁15，用于读通道0互斥保护 */

#define BBE16_PID_RESERVED                              (19)

#define IPC_CORE_COMARM                                 (1)

#define OM_BBPMASTER_READ_REG( M_uwCbbpAddr )               CSDR_CbbpReg32Rd( M_uwCbbpAddr )
#define OM_BBPMASTER_WRITE_REG( M_uwCbbpAddr, M_uwValue )   CSDR_CbbpReg32Wr( M_uwCbbpAddr, M_uwValue )

#define OM_BBPMASTER_YES                                (1)
#define OM_BBPMASTER_NO                                 (0)

#define OM_BBPMASTER_OK                                 (0)

typedef PHY_INT                                         OM_BBPMASTER_INT;
typedef PHY_UINT32                                      OM_BBPMASTER_UINT32;
typedef PHY_VOID                                        OM_BBPMASTER_VOID;
typedef CSDR_VOID_ISR_FUN                               VOS_VOIDFUNCPTR;
typedef PHY_UINT32                                      OM_BBPMASTER_CFG_DECFG_TYPE_ENUM_UINT32;

#else

#define OM_BBPMASTER_READ_REG( ulRegAddr )                  HPA_Read32Reg( ulRegAddr )
#define OM_BBPMASTER_WRITE_REG( ulRegAddr, ulRegVal )       HPA_Write32Reg( ulRegAddr, ulRegVal )

#define OM_BBPMASTER_YES                                VOS_YES
#define OM_BBPMASTER_NO                                 VOS_NO

#define OM_BBPMASTER_OK                                 VOS_OK

typedef VOS_INT                                         OM_BBPMASTER_INT;
typedef VOS_UINT32                                      OM_BBPMASTER_UINT32;
typedef VOS_PID                                         OM_BBPMASTER_UINT32;
typedef VOS_VOID                                        OM_BBPMASTER_VOID;
typedef VOS_UINT32                                      OM_BBPMASTER_CFG_DECFG_TYPE_ENUM_UINT32;

#endif

/*****************************************************************************
  3 枚举定义
*****************************************************************************/
enum OM_BBPMASTER_CFG_DECFG_TYPE_ENUM
{
    OM_BBPMASTER_CONFIG_NONE                = 0,    /* 配置通道接口返回值枚举: 未配置 */
    OM_BBPMASTER_CONFIG_SUCC                = 1,    /* 使能配置通道接口返回值枚举: 配置成功 */
    OM_BBPMASTER_PARA_CHANID_INVALID        = 2,    /* 使能配置通道接口返回值枚举: 配置通道号无效 */
    OM_BBPMASTER_PARA_CFG_NULL              = 3,    /* 使能配置通道接口返回值枚举: 配置参数为空指针 */
    OM_BBPMASTER_LOCK_IPC_FAIL              = 4,    /* 使能配置通道接口返回值枚举: 获取IPC资源锁失败 */
    OM_BBPMASTER_DECFG_SUCC                 = 5,    /* 去使能配置通道接口返回值枚举: 配置成功 */
    OM_BBPMASTER_NOT_SUPPORT                = 6,    /* 不支持BBP Master适配接口(仅V7R5/V8RX/K3V5上支持) */
    OM_BBPMASTER_CFG_DECFG_TYPE_BUTT
};

enum OM_BBPMASTER_IP_TYPE_ENUM
{
     OM_BBPMASTER_IP_V8R1                    = 0,    /* V8R1 BBP Master IP */
     OM_BBPMASTER_IP_V7R5,                           /* V7R5 BBP Master IP */
     OM_BBPMASTER_IP_V8R5,                           /* V8R5 BBP Master IP */
     OM_BBPMASTER_IP_K3V6,                           /* K3V5 BBP Master IP */
     OM_BBPMASTER_NO_IP                              /* 不支持BBP Master IP */
};

enum OM_BBPMASTER_CHAN_STATE_ENUM
{
    OM_BBPMASTER_CHAN_STATE_IDLE            = 0,    /* 通道状态:未使能状态 */
    OM_BBPMASTER_CHAN_STATE_BUSY            = 1,    /* 通道状态:已使能状态 */
    OM_BBPMASTER_CHAN_STATE_BUTT
};

#ifdef CSDR_FEATURE_ON
typedef unsigned long OM_BBPMASTER_CHAN_STATE_ENUM_UINT32;
#else
typedef VOS_UINT32 OM_BBPMASTER_CHAN_STATE_ENUM_UINT32;
#endif
/*****************************************************************************
  4 全局变量声明
*****************************************************************************/

/*****************************************************************************
  7 STRUCT定义
*****************************************************************************/
typedef struct
{
    OM_BBPMASTER_UINT32                         ulShared;       /* 通道是否复用 */
    VOS_VOIDFUNCPTR                             pfnIntFunc;
}BBPMASTER_ENTITY_STRU;

typedef struct
{
    OM_BBPMASTER_UINT32                         ulWorkMode;     /* 使能写通道配置参数:工作模式 */
    OM_BBPMASTER_UINT32                         ulClockSel;     /* 使能写通道配置参数:时钟选择; V7R5无效，V8R1有效 */
    OM_BBPMASTER_UINT32                         ulStartAddr;    /* 使能写通道配置参数:写通道起始地址 */
    OM_BBPMASTER_UINT32                         ulEndAddr;      /* 使能写通道配置参数:写通道终止地址 */
    OM_BBPMASTER_UINT32                         ulBurstLen;     /* 使能写通道配置参数:Burst长度类型 */
    OM_BBPMASTER_UINT32                         ulAxiSel;       /* 使能写通道配置参数:AXI通道选择 */
    OM_BBPMASTER_UINT32                         ulIntMode;      /* 中断模式 */
    VOS_VOIDFUNCPTR                             pfnIntFunc;     /* 需要挂接的中断处理函数 */
}BBPMASTER_WR_CHANNEL_CONFIG_STRU;

typedef struct
{
    OM_BBPMASTER_UINT32                         ulWorkModeAddr; /* 写通道配置参数:工作模式配置寄存器，使能、去使能接口复用 */
    OM_BBPMASTER_UINT32                         ulClockSelAddr; /* 写通道配置参数:时钟选择配置寄存器，使能、去使能接口复用 */
    OM_BBPMASTER_UINT32                         ulStartAddr;    /* 写通道配置参数:写通道起始地址配置寄存器，使能、去使能接口复用 */
    OM_BBPMASTER_UINT32                         ulEndAddr;      /* 写通道配置参数:写通道终止地址配置寄存器，使能、去使能接口复用 */
    OM_BBPMASTER_UINT32                         ulBurstLenAddr; /* 写通道配置参数:Burst长度类型配置寄存器，使能、去使能接口复用 */
    OM_BBPMASTER_UINT32                         ulAxiSelAddr;   /* 写通道配置参数:AXI通道选择配置寄存器，使能、去使能接口复用 */
    OM_BBPMASTER_UINT32                         ulIntModeAddr;  /* 写通道配置参数:中断模式寄存器 */
}BBPMASTER_WR_CHANNEL_CONFIG_ADDR_STRU;

typedef struct
{
    OM_BBPMASTER_UINT32                         ulWorkMode;     /* 去使能通道配置参数:工作模式配置寄存器 */
    OM_BBPMASTER_UINT32                         ulClockSel;     /* 去使能通道配置参数:时钟选择配置寄存器 */
}BBPMASTER_CHANNEL_DECONFIG_STRU;

typedef struct
{
    OM_BBPMASTER_UINT32                         ulWorkMode;     /* 使能读通道配置参数:工作模式 */
    OM_BBPMASTER_UINT32                         ulClockSel;     /* 使能读通道配置参数:时钟选择 V7R5无效，V8R1有效 */
    OM_BBPMASTER_UINT32                         ulStartAddr;    /* 使能读通道配置参数:读通道起始地址 */
    OM_BBPMASTER_UINT32                         ulBurstLen;     /* 通道配置参数:Burst长度类型 */
    OM_BBPMASTER_UINT32                         ulAxiSel;       /* 使能读通道配置参数:AXI通道选择 */
    OM_BBPMASTER_UINT32                         ulIntMode;      /* 中断模式 */
    OM_BBPMASTER_UINT32                         ulValidLen;     /* 使能读通道配置参数:读通道 V7R5有效，V8R1无效  */
    VOS_VOIDFUNCPTR                             pfnIntFunc;     /* 需要挂接的中断处理函数 */
}BBPMASTER_RD_CHANNEL_CONFIG_STRU;

typedef struct
{
    OM_BBPMASTER_UINT32                         ulWorkModeAddr; /* 读通道配置参数:工作模式配置寄存器，使能、去使能接口复用 */
    OM_BBPMASTER_UINT32                         ulClockSelAddr; /* 读通道配置参数:时钟选择配置寄存器，使能、去使能接口复用 */
    OM_BBPMASTER_UINT32                         ulStartAddr;    /* 读通道配置参数:读通道起始地址配置寄存器，使能、去使能接口复用 */
    OM_BBPMASTER_UINT32                         ulBurstLenAddr; /* 读通道配置参数:Burst长度类型配置寄存器，使能、去使能接口复用 */
    OM_BBPMASTER_UINT32                         ulAxiSelAddr;   /* 读通道配置参数:AXI通道选择配置寄存器，使能、去使能接口复用 */
    OM_BBPMASTER_UINT32                         ulValidLenAddr; /* 有效长度配置地址 */
    OM_BBPMASTER_UINT32                         ulIntModeAddr;  /* 中断模式 */
}BBPMASTER_RD_CHANNEL_CONFIG_ADDR_STRU;

/*****************************************************************************
  5 消息头定义
*****************************************************************************/

/*****************************************************************************
  6 消息定义
*****************************************************************************/

/*****************************************************************************
  8 UNION定义
*****************************************************************************/


/*****************************************************************************
  9 OTHERS定义
*****************************************************************************/


/*****************************************************************************
  10 函数声明
*****************************************************************************/
extern OM_BBPMASTER_UINT32 OM_BbpMasterInit( OM_BBPMASTER_VOID );

extern OM_BBPMASTER_CFG_DECFG_TYPE_ENUM_UINT32 OM_BbpMasterRdChannelConfig(OM_BBPMASTER_UINT32 ulPID,
                                                               OM_BBPMASTER_UINT32 ulChanId,
                                                               BBPMASTER_RD_CHANNEL_CONFIG_STRU *pstRdChanCfg);

extern OM_BBPMASTER_CFG_DECFG_TYPE_ENUM_UINT32 OM_BbpMasterRdChannelDeConfig(OM_BBPMASTER_UINT32 ulPID,
                                                               OM_BBPMASTER_UINT32 ulChanId,
                                                               BBPMASTER_CHANNEL_DECONFIG_STRU *pstChanDeCfg);

extern OM_BBPMASTER_CFG_DECFG_TYPE_ENUM_UINT32 OM_BbpMasterWrChannelConfig(OM_BBPMASTER_UINT32 ulPID,
                                                               OM_BBPMASTER_UINT32 ulChanId,
                                                               BBPMASTER_WR_CHANNEL_CONFIG_STRU *pstWrChanCfg);
extern OM_BBPMASTER_CFG_DECFG_TYPE_ENUM_UINT32 OM_BbpMasterWrChannelDeConfig(OM_BBPMASTER_UINT32 ulPID,
                                                               OM_BBPMASTER_UINT32 ulChanId,
                                                               BBPMASTER_CHANNEL_DECONFIG_STRU *pstChanDeCfg);

extern OM_BBPMASTER_UINT32 OM_BbpMasterGetIpInfo(OM_BBPMASTER_VOID);

#if ((VOS_OS_VER == VOS_WIN32) || (VOS_OS_VER == VOS_NUCLEUS))
#pragma pack()
#else
#pragma pack(0)
#endif


#ifdef __cplusplus
    #if __cplusplus
        }
    #endif
#endif

#endif /* end of omnosig.h */

