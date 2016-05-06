

/******************************************************************************

                  版权所有 (C), 2001-2013, 华为技术有限公司

 ******************************************************************************
  文 件 名      : bbp_colltion.h
  版 本 号      : 初稿
  作    者      : j00174725
  生成日期      : 2012年11月06日
  最近修改      :
  功能描述      : 该头文件为BBP采数的头文件
  函数列表      :
  修改历史      :
  1.日    期    : 2012年11月06日
    作    者    : 蒋德彬 00174725
    修改内容    : 创建文件

******************************************************************************/
#ifndef _OM_BBP_LOG_H_
#define _OM_BBP_LOG_H_

/*****************************************************************************
  1 其他头文件包含
*****************************************************************************/
#include "vos.h"
#include "mdrv.h"

#ifdef __cplusplus
#if __cplusplus
extern "C"{
#endif
#endif

/*****************************************************************************
  2 宏定义
*****************************************************************************/
#define OM_BBP_REG(reg)   (*(volatile VOS_UINT32 *)((VOS_UINT32)(reg)))

#define OM_BBP_REG_SETBITS(reg, pos, bits, val) (OM_BBP_REG(reg) = (OM_BBP_REG(reg) \
                                        & (~((((VOS_UINT32)1 << (bits)) - 1) << (pos)))) \
                                        | ((VOS_UINT32)((val) & (((VOS_UINT32)1 << (bits)) - 1)) << (pos)))

#define OM_BBP_WRITE_REG(reg,value)                 (OM_BBP_REG(reg) = (value))

#define OM_BBP_READ_REG(value,reg)                  ((value) = OM_BBP_REG(reg))

/* BBP可维可测每个通道需要挂接的结点数 */
#define BBP_DBG_NODE_NUM                            (4)

#define OM_BBP_BITN(n)                              (0x1 << n)

/* 用于BBP可维可测的SOCP通道个数 */
#define BBP_DBG_CODER_SRC_NUM                       (2)

/* 每个链表结点的空间大小 4Kbyte */
#define BBP_DBG_NODE_SIZE                           (2 * 1024)

/* 每个SOCP通道编码源空间的大小 8K  */
#define BBP_DBG_CODER_SRC_SIZE                      (BBP_DBG_NODE_NUM * BBP_DBG_NODE_SIZE)

/* BBP可维可测需要分配的总空间大小 16K*/
#define BBP_DBG_TOTAL_MEM_LENTH                     (BBP_DBG_CODER_SRC_SIZE * BBP_DBG_CODER_SRC_NUM)

/* BBP 数采最小长度 30.75 * 1024 KB:原本最小的采数长度为30.72MB,但不满足32KB的整数倍 */
#define BBP_DUMP_MIN_LEN                            (31488)

/* BBP 数采最大长度 2G */
#define BBP_DUMP_MAX_LEN                            (2 * 1024 * 1024)

/* BBP 数采长度必须是32KB的整数倍 */
#define BBP_DUMP_UNIT_LEN                           (32)

/* BBP需要备份恢复的寄存器个数 */
#define BBP_DBG_BACK_REG_NUM                        (20)

#define BBP_DUMP_EDMA_INT                           (BALONG_DMA_INT_DONE \
                                                    | BALONG_DMA_INT_TRANSFER_ERR \
                                                    | BALONG_DMA_INT_CONFIG_ERR)

#define BBP_DBG_EDMA_INT                            (BALONG_DMA_INT_DONE \
                                                    | BALONG_DMA_INT_TRANSFER_ERR \
                                                    | BALONG_DMA_INT_CONFIG_ERR \
                                                    | BALONG_DMA_INT_LLT_DONE \
                                                    | BALONG_DMA_INT_READ_ERR)

#define MAX_BBP_OFFSET_ADDR                         (0xFFFFFF)

#define BBP_DBG_MAGIC_SIGN                          (0x48495349)

#define BBP_DBG_PACKAGE_LENTH                       (2040)

#define BBP_DBG_ERR_PACKAGE_SIGN                    (0x5555AAAA)

#define OM_BBP_DBG_START                            (0x5555aaaa)   /* 启动 */
#define OM_BBP_DBG_STOP                             (0xaaaa5555)   /* 停止 */

#define WAITING_ACPU_CNF_TIMEOUT_LEN                (5000)
/* CCPU向ACPU发送的请求消息,需等待回复 */
#define BBP_QUERY_DUMP_INFO_REQ                     (0xFA01)
#define BBP_QUERY_DUMP_INFO_CNF                     (0xFA02)


/* PC侧下发BBP采数配置 */
#define APP_OM_BBP_DUMP_SET_REQ                   0x8103
#define OM_APP_BBP_DUMP_SET_CNF                   0x8104

/* PC侧下发BBP 可维可测配置 */
#define APP_OM_BBP_DBG_SET_REQ                    0x8105
#define OM_APP_BBP_DBG_SET_CNF                    0x8106

/* 在BBP 数采中断中模拟工具下发的一条消息，通知CCPU OM 数采结束 */
#define APP_OM_BBP_DUMP_END_REQ                   0x8107

/* 单板侧采数完成 */
#define OM_APP_BBP_DUMP_END_CNF                   0x8110

/* BBP可维可测EDMA上报异常，模似工具发送消息通知CCPU OM */
#define APP_OM_BBP_EDMA_ERR_REQ                   0x8113

/* 通知工具EDMA 错误 */
#define OM_APP_BBP_EDMA_ERR_CNF                   0x8114

/* BPP dump数据选择 */
#define APP_OM_BBP_DUMP_DUMP_REQ                  0x8115
#define OM_APP_BBP_DUMP_DUMP_CNF                  0x8116

/* 通知工具C核已经复位 */
#define OM_APP_CCORE_RESET_CNF                    0x8118

/*****************************************************************************
  3 枚举定义
*****************************************************************************/

/*****************************************************************************
  枚举名    : OM_TOOL_CPUID_ENUM
  结构说明  : OM和TOOL CPU ID枚举
1.日    期  : 2012年08月08日
  作    者  : J00168360
  修改内容  : V9R1 MSP拆分和可维可测开发项目新增结构
*****************************************************************************/
enum OM_TOOL_CPUID_ENUM
{
     OM_TOOL_RSV_ID,
     OM_TOOL_ACPU_ID,
     OM_TOOL_CCPU_ID,
     OM_TOOL_LDSP_ID,
     OM_TOOL_LBBP_ID,
     OM_TOOL_HIFI_ID,
     OM_TOOL_GUDSP_ID,
     OM_TOOL_TDSDSP_ID,
     OM_TOOL_TDSBBP_ID,
     OM_TOOL_MCU_ID,
     OM_TOOL_GPU_ID,
     OM_TOOL_GUBBP_ID,
     OM_TOOL_CPUID_BUTT
};
typedef VOS_UINT8 OM_TOOL_CPUID_ENUM_UINT8;

/*****************************************************************************
枚举名    : BBP_DUMP_FIFO_WATERMARKER_ENUM
枚举说明  : BBP采数水线配置

  1.日    期   : 2012年11月06日
    作    者   : j00174725
    修改内容   : BBP采数项目新增
*****************************************************************************/
typedef enum
{
    BBP_DUMP_WATERMARKER0 = 0,      /* 0：表示水线深度2 */
    BBP_DUMP_WATERMARKER1,          /* 1：表示水线深度4 */
    BBP_DUMP_WATERMARKER2,          /* 2：表示水线深度8 */
    BBP_DUMP_WATERMARKER3,          /* 3：表示水线深度16 */
    BBP_DUMP_WATERMARKER4,          /* 4：表示水线深度32 */
    BBP_DUMP_WATERMARKER5,          /* 5：表示水线深度64 */
    BBP_DUMP_WATERMARKER6,          /* 6：表示水线深度128 */
    BBP_DUMP_WATERMARKER_BUTT
}BBP_DUMP_FIFO_WATERMARKER_ENUM;

typedef VOS_UINT32 BBP_DUMP_FIFO_WATERMARKER_ENUM_U32;

/*****************************************************************************
枚举名    : OM_BBP_STATUS_ENUM
枚举说明  : BBP DBG和DUMP状态

  1.日    期   : 2012年11月06日
    作    者   : j00174725
    修改内容   : BBP采数项目新增
*****************************************************************************/
typedef enum
{
    OM_BBP_START = 0,   /* 启动 */
    OM_BBP_STOP,        /* 停止 */
    OM_BBP_BUTT
}OM_BBP_STATUS_ENUM;

typedef VOS_UINT32 OM_BBP_STATUS_ENUM_U32;

/*****************************************************************************
枚举名    : OM_BBP_DUMP_MODE_ENUM
枚举说明  : BBP DUMP模式选择

  1.日    期   : 2012年11月06日
    作    者   : j00174725
    修改内容   : BBP采数项目新增
*****************************************************************************/
typedef enum
{
    OM_BBP_DUMP_MODE_W = 0,   /* W模 */
    OM_BBP_DUMP_MODE_G1,      /* G1模 */
    OM_BBP_DUMP_MODE_Rev,
    OM_BBP_DUMP_MODE_G2,      /* G2模 */
    OM_BBP_DUMP_MODE_BUTT
}OM_BBP_DUMP_MODE_ENUM;

typedef VOS_UINT32 OM_BBP_DUMP_MODE_ENUM_U32;

/*****************************************************************************
枚举名    : BBP_DBG_IF_SEL_ENUM
枚举说明  : BBP DBG 接口选择信号

  1.日    期   : 2012年11月06日
    作    者   : j00174725
    修改内容   : BBP采数项目新增
*****************************************************************************/
typedef enum
{
    BBP_IF_SEL_LOCALBUS = 0,    /* 0：表示选择LocalBus，即监测所有BBP配置信息 */
    BBP_IF_SEL_WBBP_IMI,        /* 1：表示选择WBBP IMI接口，即仅监测WBBP配置信息 */
    BBP_IF_SEL_GBBP_IMI,        /* 2：表示选择GBBP IMI接口，即仅监测GBBP配置信息 */
    BBP_IF_SEL_REV,             /* 3：保留不用 */
    BBP_IF_SEL_BUTT
}BBP_DBG_IF_SEL_ENUM;

typedef VOS_UINT32 BBP_DBG_IF_SEL_ENUM_U32;

/*****************************************************************************
枚举名    : BBP_DBG_CLK_IN_SEL_EN_ENUM
枚举说明  : BBP DBG输入时钟选择

  1.日    期   : 2012年11月06日
    作    者   : j00174725
    修改内容   : BBP采数项目新增
*****************************************************************************/
typedef enum
{
    BBP_DBG_CLK_IN_SEL0 = 0,    /* 0：表示使用模式一时钟； */
    BBP_DBG_CLK_IN_SEL1,        /* 1：表示使用模式二时钟； */
    BBP_DBG_CLK_IN_SEL2,        /* 2：表示使用模式三时钟； */
    BBP_DBG_CLK_IN_SEL_BUTT
}BBP_DBG_CLK_IN_SEL_EN_ENUM;

typedef VOS_UINT32 BBP_DBG_CLK_IN_SEL_ENUM_U32;

/*****************************************************************************
枚举名    : BBP_DBG_FIFO_WATERMARKER_ENUM
枚举说明  : BBP DBG水线配置

  1.日    期   : 2012年11月06日
    作    者   : j00174725
    修改内容   : BBP采数项目新增
*****************************************************************************/
typedef enum
{
    BBP_DBG_WATERMARKER0 = 0,   /* 0：表示水线深度2 */
    BBP_DBG_WATERMARKER1,       /* 1：表示水线深度4 */
    BBP_DBG_WATERMARKER2,       /* 2：表示水线深度8 */
    BBP_DBG_WATERMARKER3,       /* 3：表示水线深度16 */
    BBP_DBG_WATERMARKER4,       /* 4：表示水线深度32 */
    BBP_DBG_WATERMARKER5,       /* 5：表示水线深度64 */
    BBP_DBG_WATERMARKER_BUTT
}BBP_DBG_FIFO_WATERMARKER_ENUM;

typedef VOS_UINT32 BBP_DBG_FIFO_WATERMARKER_ENUM_U32;

/*****************************************************************************
枚举名    : OM_APP_BBP_DUMP_CHOOSE_ENUM
枚举说明  : BBP DUMP 导出数据选择

  1.日    期   : 2012年11月06日
    作    者   : j00174725
    修改内容   : BBP采数项目新增
*****************************************************************************/
typedef enum
{
    BBP_DUMP_CHOOSE_YES = 0,    /* 用户选择导出数据 */
    BBP_DUMP_CHOOSE_NO,         /* 用户放弃数据 */
    BBP_DUMP_CHOOSE_BUTT
}OM_APP_BBP_DUMP_CHOOSE_ENUM;

typedef VOS_UINT32 OM_APP_BBP_DUMP_CHOOSE_ENUM_U32;

/*****************************************************************************
枚举名    : OM_APP_BBP_DBG_ERRCODE_ENUM
枚举说明  : BBP 可维可测与PC约定的错误码

  1.日    期   : 2012年11月06日
    作    者   : j00174725
    修改内容   : BBP采数项目新增
*****************************************************************************/
typedef enum
{
    BBP_DBG_OK = 0,             /* 成功 */
    BBP_DBG_ALLOC_ERR,          /* 分配环形buffer失败 */
    BBP_DBG_ALLOC_MSG_ERR,      /* 分配消息内存失败 */
    BBP_DBG_INIT_SOCP_ERR,      /* 初始化SOCP失败 */
    BBP_DBG_START_SOCP_ERR,     /* 使能SOCP通道失败 */
    BBP_DBG_ENABLE_EDMA_ERR,    /* 使能EDMA通道失败 */
    BBP_DBG_STOP_EDMA_ERR,      /* 关闭EDMA失败 */
    BBP_DBG_IF_SEL_ERR,         /* 接口选择信息错误 */
    BBP_DBG_CLK_IN_SEL_ERR,     /* 时钟选择信息错误 */
    BBP_DBG_INIT_EDMA_ERR,      /* 初始化EDMA失败 */
    BBP_DBG_CONFIG_EDMA_ERR,    /* 配置EDMA失败 */
    BBP_DBG_ALLOC_CYC_ERR,      /* 分配环形buff失败 */
    BBP_DBG_GET_CONFIGADD_ERR,  /* 获取EDMA配置地址失败 */
    BBP_DBG_CREATE_SEM_ERR,     /* 创建信号量失败 */
    BBP_DBG_ADDR_ERR,           /* 地址范围不正确 */
    BBP_DBG_MODE_ERR,           /* 模式选择错误 */
    BBP_DBG_BUTT
}OM_APP_BBP_DBG_ERRCODE_ENUM;

typedef VOS_UINT32 OM_APP_BBP_DBG_ERRCODE_ENUM_U32;

/*****************************************************************************
枚举名    : OM_APP_BBP_DUMP_ERRCODE_ENUM
枚举说明  : BBP 数采与PC约定的错误码

  1.日    期   : 2012年11月06日
    作    者   : j00174725
    修改内容   : BBP采数项目新增
*****************************************************************************/
typedef enum
{
    BBP_DUMP_OK = 0,              /* 设置成功 */
    BBP_DUMP_MEM_SMALL,           /* 下发数采长度过小 */
    BBP_DUMP_MEM_BIG,             /* 下发数采长度太大*/
    BBP_DUMP_MEM_NOT_32KB,        /* 非32kB的整数倍 */
    BBP_DUMP_ALLOC_MEM_ERR,       /* 分配数采内存失败 */
    BBP_DUMP_START_EDMA_ERR,      /* 启动EDMA失败 */
    BBP_DUMP_ACORE_MSG_NULL,      /* A核发来的MSG为空 */
    BBP_DUMP_END,                 /* 数采停止 */
    BBP_DUMP_READ_NV_ERR,         /* 读NV失败 */
    BBP_DUMP_DISABLE,             /* NV项禁止BBP数采*/
    BBP_DUMP_STOP_EDMA_ERR,       /* 停止EDMA失败 */
    BBP_DUMP_MODE_ERR,            /* 模式错误 */
    BBP_DUMP_WAITING_CNF_TIMEOUT, /* 等待回复超时 */
    BBP_DUMP_RCV_MSG_NOT_MATCH,   /* 收到消息不匹配 */
    BBP_DUMP_BUTT
}OM_APP_BBP_DUMP_ERRCODE_ENUM;

typedef VOS_UINT32 OM_APP_BBP_DUMP_ERRCODE_ENUM_U32;

/*****************************************************************************
枚举名    : OM_APP_BBP_EDMA_ERR_ENUM
枚举说明  : 标识EDMA错误中断是由可维可测产生的，还是数采产生的

  1.日    期   : 2012年11月06日
    作    者   : j00174725
    修改内容   : BBP采数项目新增
*****************************************************************************/
typedef enum
{
    OM_BBP_DUMP_EDMA_ERR = 0, /* 数采EDMA报错 */
    OM_BBP_DBG_EDMA_ERR,      /* 可维可测EDMA报错 */
    OM_BBP_EDMA_ERR_BUTT
}OM_APP_BBP_EDMA_ERR_ENUM;

typedef VOS_UINT16 OM_APP_BBP_EDMA_ERR_ENUM_U16;

/*****************************************************************************
枚举名    : OM_BBP_DUMP_ENABLE_ENUM
枚举说明  : NV 中标注是否使能数采

  1.日    期   : 2012年11月06日
    作    者   : j00174725
    修改内容   : BBP采数项目新增
*****************************************************************************/
typedef enum
{
    OM_BBP_DUMP_DISABLE = 0, /* 禁止数采 */
    OM_BBP_DUMP_ENABLE,      /* 使能数采 */
    OM_BBP_DUMP_BUTT
}OM_BBP_DUMP_ENABLE_ENUM;

typedef VOS_UINT16 OM_BBP_DUMP_ENABLE_ENUM_U16;

/*****************************************************************************
  4 全局变量声明
*****************************************************************************/


/*****************************************************************************
  5 消息头定义
*****************************************************************************/

/*****************************************************************************
  6 消息定义
*****************************************************************************/


/*****************************************************************************
  7 STRUCT定义
*****************************************************************************/
/*****************************************************************************
结构名    : BBP_DBG_SOCP_INFO_STRU
结构说明  : BBP DBG SOCP错误信息

  1.日    期   : 2012年11月06日
    作    者   : j00174725
    修改内容   : BBP采数新增
*****************************************************************************/
typedef struct
{
    VOS_UINT32  ulWriteDoneOk;      /* 记录写成功的次数 */
    VOS_UINT32  ulWriteDoneErr;     /* 记录写失败的次数 */
    VOS_UINT32  ulGetWriteBuffErr;  /* 记录获取写buffer失败的次数 */
    VOS_UINT32  ulBuffNotEnough;    /* 记录空间不够的次数 */
    VOS_UINT32  ulWriteBufSize;     /* 记录剩余空间大小 */
}BBP_DBG_SOCP_INFO_STRU;

/*****************************************************************************
结构名    : BBP_DBG_ERR_INFO_STRU
结构说明  : BBP DBG 错误信息

  1.日    期   : 2012年11月06日
    作    者   : j00174725
    修改内容   : BBP采数新增
*****************************************************************************/
typedef struct
{
    VOS_UINT16                  usAllocErr;                                 /* 记录内存分配失败 */
    VOS_UINT16                  usInitSocpErr;                              /* 记录初始化SOCP失败 */
    VOS_UINT16                  usStartSocpErr;                             /* 记录启动SOCP失败 */
    VOS_UINT16                  usInitEdmaErr;                              /* 记录EDMA初始化失败 */
    VOS_UINT16                  usConfigEdmaErr;                            /* 记录EDMA配置失败 */
    VOS_UINT16                  usEdmaErrCode;                              /* 记录EDMA传输失败中断次数 */
    VOS_UINT16                  usAllocCycErr;                              /* 记录分配EDMA循环链表结点失败 */
    VOS_UINT16                  usGetConAddrErr;                            /* 记录获取EDMA配置地址失败*/
    VOS_UINT16                  usStartEdmaErrNum;                          /* 记录启动EDMA失败的次数 */
    VOS_UINT16                  usStopEdmaErrNum;                           /* 关闭EDMA失败 */
    VOS_UINT16                  usCreateSemErr;                             /* 创建信号量失败 */
    VOS_UINT16                  usRev;
    BBP_DBG_SOCP_INFO_STRU      astBbpDbgSocpInfo[BBP_DBG_CODER_SRC_NUM];   /* 记录SOCP的调试信息 */
}BBP_DBG_ERR_INFO_STRU;

/*****************************************************************************
结构名    : BBP_DBG_INFO_STRU
结构说明  : BBP DBG 错误信息

  1.日    期   : 2012年11月06日
    作    者   : j00174725
    修改内容   : BBP采数新增
*****************************************************************************/
typedef struct
{
    VOS_INT                             lBbpEdmaChanID;                         /* 记录可维可测EDMA通道号 */
    VOS_UINT32                          ulBbpDbgStatus;                         /* 记录可维可测的状态*/
    VOS_UINT32                          ulBbpErrCode;                           /* 记录BBP可维可测初始化错误码 */
    VOS_UINT32                          ulBbpSelfTaskNum;                       /* 记录自处理任务处理的次数 */
    VOS_UINT32                          ulBbpEdmaCallBackNum;                   /* 记录BBP可维可测EDMA 完成回调次数 */
    VOS_UINT32                          ulPhyAddr;                              /* 记录分配内存的物理地址 */
    VOS_UINT32                          ulIndexValue;                           /* 总包数 */
    VOS_UINT32                          ulLastAddr;                             /* EDMA前一次搬数的起始地址 */
    VOS_UINT32                          ulFlowNum;                              /* BBP溢出的次数 */
}BBP_DBG_INFO_STRU;

/*****************************************************************************
结构名    : BBP_DUMP_ERR_INFO_STRU
结构说明  : BBP DUMP 错误信息

  1.日    期   : 2012年11月06日
    作    者   : j00174725
    修改内容   : BBP采数新增
*****************************************************************************/
typedef struct
{
    VOS_UINT16  usInitEdmaErr;  /* 初始化EDMA失败 */
    VOS_UINT16  usConfigEdmaErr;/* 配置EDMA失败 */
    VOS_UINT16  usStartEdmaErr; /* 启动EDMA失败 */
    VOS_UINT16  usEdmaErrCode;  /* 错误中断类型 */
    VOS_UINT16  usAllocMsgErr;  /* 分配消息空间失败 */
    VOS_UINT16  usCloseEdmaErr; /* 关闭EDMA失败*/
    VOS_UINT16  usStopEdmaErr;  /* 停止EDMA失败 */
    VOS_UINT16  usRev;
}BBP_DUMP_ERR_INFO_STRU;


/*****************************************************************************
结构名    : BBP_DUMP_CHOOSE_STRU
结构说明  : BBP DUMP 导出数据选择

  1.日    期   : 2012年11月06日
    作    者   : j00174725
    修改内容   : BBP采数新增
*****************************************************************************/
typedef struct
{
    VOS_UINT32  ulChooseRelt;

}BBP_DUMP_CHOOSE_STRU;

/*****************************************************************************
结构名    : OM_APP_BBP_DUMP_EDMA_STRU
结构说明  : BBP DUMP 回复PC侧下发的EDMA配置信息

  1.日    期   : 2012年11月06日
    作    者   : j00174725
    修改内容   : BBP采数新增
*****************************************************************************/
typedef struct
{
    OM_APP_BBP_DUMP_ERRCODE_ENUM_U32    enErr;      /* 如果发生错误，则记录错误码，如果为OK,则表明配置一切正常 */
    VOS_UINT32                          ulPhyAddr;
}OM_APP_BBP_DUMP_EDMA_STRU;

/*****************************************************************************
结构名    : APP_OM_BBP_DUMP_SET_STRU
结构说明  : BBP DUMP PC下发的W模配置信息

  1.日    期   : 2012年11月06日
    作    者   : j00174725
    修改内容   : BBP采数新增
*****************************************************************************/
typedef struct
{
    OM_BBP_DUMP_MODE_ENUM_U32               enMode;             /* 0x5E820334表示配置G模还是W模 */
    VOS_UINT32                              ulDataLen;          /* 0x014c 采集数据的长度 ，0表示无限长,PC下发时，以KByte为单位 */

    /* W模式特有 start */
    BBP_DUMP_FIFO_WATERMARKER_ENUM_U32      enFifoWaterW;       /* 0x0154 表示水线深度 */
    VOS_UINT32                              ulStartTimeW;       /* 0x0150 采数起始位置 */
    VOS_UINT32                              ulDataModelSelW;    /* 0x12dc DMA基带数据搬运选择 */
    VOS_UINT32                              ulWtDbgEnW;         /* 0x96000 DBG数据进行工作使能*/
    /* W模式特有 end */

    /* G模式特有 start */
    VOS_UINT32                              ulStartLowTimeG;    /* 0xf00c 采数起始位置 */
    VOS_UINT32                              ulStartHiTimeG;     /* 0xf010 采数起始位置 */
    VOS_UINT32                              ulGenConfig;        /* 0xF004 G模采数配置 */
    /* G模式特有 end */
}APP_OM_BBP_DUMP_SET_STRU;

/*****************************************************************************
结构名    : BBP_DUMP_GET_FIX_DDR_ADDR
结构说明  : 存放底软分配的物理地址和内存大小

  1.日    期   : 2014年10月08日
    作    者   : d00212987
    修改内容   : BBP采数新增
*****************************************************************************/
typedef struct
{
    VOS_UINT32                          ulPhyAddr;    /* 记录BBP数采使用的EDMA通道号 */
    VOS_UINT32                          ulPhySize;    /* 记录数采状态 */
}BBP_DUMP_GET_FIX_DDR_ADDR;

/*****************************************************************************
结构名    : BBP_DUMP_MSG_STRU
结构说明  : 存放底软分配的物理地址和内存大小

  1.日    期   : 2014年10月08日
    作    者   : d00212987
    修改内容   : BBP采数新增
*****************************************************************************/
typedef struct
{
    VOS_MSG_HEADER
    VOS_UINT16                          usPrimId;
    VOS_UINT16                          ausRsv[3];
    BBP_DUMP_GET_FIX_DDR_ADDR           stDumpDdrInfo;
}BBP_DUMP_MSG_STRU;

/*****************************************************************************
结构名    : APP_OM_BBP_DBG_SET_W_STRU
结构说明  : BBP 可维可测 PC下发的配置信息

  1.日    期   : 2012年11月06日
    作    者   : j00174725
    修改内容   : BBP采数新增
*****************************************************************************/
typedef struct
{
    OM_BBP_DUMP_MODE_ENUM_U32           enMode;             /* 0x5E820334表示配置G模还是W模 */
    OM_BBP_STATUS_ENUM_U32              enStatus;           /* 关闭还是打开BBP DBG上报 */
    BBP_DBG_IF_SEL_ENUM_U32             enBBPIfSel;         /* 0x008 表示BBP接口选择信号*/
    BBP_DBG_CLK_IN_SEL_ENUM_U32         enClkInSel;         /* 0x010 DBG输入时钟选择 */
    VOS_UINT32                          ulTimeSel;          /* 0x01c 接口信息使用时间戳选择 */
    VOS_UINT32                          ulMaskAddrStart0;   /* 0x020 第一段屏蔽地址起始位置 */
    VOS_UINT32                          ulMaskAddrEnd0;     /* 0x024 第一段屏蔽地址结束位置 */
    VOS_UINT32                          ulMaskAddrStart1;   /* 0x028 第二段屏蔽地址起始位置 */
    VOS_UINT32                          ulMaskAddrEnd1;     /* 0x02c 第二段屏蔽地址结束位置 */
    VOS_UINT32                          ulMaskAddrStart2;   /* 0x030 第三段屏蔽地址起始位置 */
    VOS_UINT32                          ulMaskAddrEnd2;     /* 0x034 第三段屏蔽地址结束位置 */
    VOS_UINT32                          ulMaskAddrStart3;   /* 0x038 第四段屏蔽地址起始位置 */
    VOS_UINT32                          ulMaskAddrEnd3;     /* 0x03c 第四段屏蔽地址结束位置 */
    BBP_DBG_FIFO_WATERMARKER_ENUM_U32   enFifoWater;        /* 0x040 DBG FIFO水线选择 */
    VOS_UINT32                          ulDbgSwitch;        /* 0x044 DBG上报信息开关 如果配置为1或者2，则还需要配置 0x008和0x010*/
}APP_OM_BBP_DBG_SET_W_STRU;

/*****************************************************************************
结构名    : BBP_DUMP_INFO_STRU
结构说明  : 记录BBP数采信息

  1.日    期   : 2012年11月06日
    作    者   : j00174725
    修改内容   : BBP采数新增
*****************************************************************************/
typedef struct
{
    VOS_INT                             lEdmaChanID;    /* 记录BBP数采使用的EDMA通道号 */
    VOS_UINT16                          usDUMPStatus;   /* 记录数采状态 */
    VOS_UINT16                          usDUMPDone;     /* EDMA中断完成回调 */
    VOS_UINT16                          usDUMPMode;     /* 记录当前是那个模式 */
    VOS_UINT16                          usRev;
    VOS_UINT32                          ulPhyAddr;      /* 记录DRV分配的DUMP物理地址 */
    VOS_UINT32                          ulPhySize;      /* 记录DRV分配的DUMP空间大小 */
}BBP_DUMP_INFO_STRU;

/*****************************************************************************
结构名    : BBP_EDMA_ERR_STRU
结构说明  : 用于通知ACPU OM EDMA产生错误中断

  1.日    期   : 2012年11月06日
    作    者   : j00174725
    修改内容   : BBP采数新增
*****************************************************************************/
typedef struct
{
    OM_APP_BBP_EDMA_ERR_ENUM_U16        enEdmaErr;      /* 记录是可维可测产生的错误，还是数采产生的错误 */
    VOS_UINT16                          usRsv;
}BBP_EDMA_ERR_STRU;

/*****************************************************************************
结构名    : APP_BBP_DUMP_REQ_MSG_STRU
结构说明  : DIAG模块转发的PC侧BBP DUMP请求的透明消息结构

  1.日    期   : 2015年06月17日
    作    者   : H00300778
    修改内容   : BBP采数新增
*****************************************************************************/
typedef struct
{
    VOS_MSG_HEADER
    VOS_UINT32                          ulMsgName;

    /* PC侧透明消息下发的内容，在CNF消息里带回去 */
    VOS_UINT16                          usOriginalId;
    VOS_UINT16                          usTerminalId;
    VOS_UINT32                          ulTimeStamp;
    VOS_UINT32                          ulSN;

    VOS_UINT8                           aucValue[4];
}APP_BBP_DUMP_REQ_MSG_STRU;

/*****************************************************************************
结构名    : APP_BBP_DUMP_CNF_MSG_STRU
结构说明  : 给DIAG模块转发到PC侧的透明消息结构，用于指示PC侧UE已经收到之前发的
            BBP DUMP消息已经收到

  1.日    期   : 2015年06月17日
    作    者   : H00300778
    修改内容   : BBP采数新增
*****************************************************************************/
typedef struct
{
    VOS_MSG_HEADER
    VOS_UINT32                          ulMsgName;

    /* PC侧透明消息下发的内容，在CNF消息里带回去 */
    VOS_UINT16                          usOriginalId;
    VOS_UINT16                          usTerminalId;
    VOS_UINT32                          ulTimeStamp;
    VOS_UINT32                          ulSN;

    VOS_UINT32                          ulRslt;
}APP_BBP_DUMP_CNF_MSG_STRU;

/*****************************************************************************
  8 UNION定义
*****************************************************************************/


/*****************************************************************************
  9 OTHERS定义
*****************************************************************************/


/*****************************************************************************
  10 函数声明
*****************************************************************************/
extern VOS_VOID Om_CcpuBbpLogConfigCnf(
    APP_BBP_DUMP_REQ_MSG_STRU              *pstAppToOmMsg,
    VOS_UINT32                              ulMsgName,
    VOS_UINT32                              ulRslt);

extern VOS_VOID Om_CcpuBbpLogConfigMsgProc(MsgBlock *pRcvMsg);

extern VOS_UINT32 Om_ConfigBbpDump(
    APP_OM_BBP_DUMP_SET_STRU           *pstAppToOmMsg);

extern VOS_UINT32 Om_EndBbpDump(VOS_VOID);

extern VOS_UINT32 Om_ConfigBbpDbg(
    APP_OM_BBP_DBG_SET_W_STRU          *pstAppToOmMsg);

extern VOS_UINT32 Om_SendEdmaErrToPc(
    BBP_EDMA_ERR_STRU                  *pstEdmaErr,
    VOS_UINT16                          usReturnPrimId);

extern VOS_UINT32 Om_SendQueryDumpMsg(VOS_VOID);

extern VOS_VOID Om_BbpDumpAddrQueryMsgProc(MsgBlock *pMsg);

#ifdef __cplusplus
#if __cplusplus
}
#endif
#endif

#endif


