


#ifndef __DRV_MAILBOX_CFG_H__
#define __DRV_MAILBOX_CFG_H__

#ifdef __cplusplus
#if __cplusplus
extern "C" {
#endif
#endif

/*****************************************************************************
  1 其他头文件包含
*****************************************************************************/
#include "product_config.h"
#if defined(CHIP_BB_HI6210)
#include "MemoryLayout.h"
#endif
#include "mdrv_ipc_enum.h"


#if defined(CHIP_BB_HI6210)
/*****************************************************************************
  2 宏定义
*****************************************************************************/

/* 邮件序列号的初始值 */
#define MAILBOX_SEQNUM_START            (0)

/* 邮箱占用memory基地址 */
#define MAILBOX_MEM_BASEADDR            (MEMORY_RAM_CORESHARE_MAILBOX_ADDR)

/* 邮箱占用memory预留总长度, 包括邮箱控制头和邮箱队列缓存 */
#define MAILBOX_MEM_LENGTH              MEMORY_RAM_CORESHARE_MAILBOX_SIZE

/*****************************************************************************
 实 体 名  : struct mb_head
 功能描述  : 核间邮箱缓存头, 通过保护字判断邮箱通道有没有被初始化, 此功能需要
             fastboot同步修改:上电初始化对邮箱共享内存头数据清零
*****************************************************************************/
typedef struct mb_head
{
    unsigned int       ulProtectWord1;     /*保护字 0x55AA55AA*/
    unsigned int       ulProtectWord2;     /*保护字 0x5A5A5A5A*/
    unsigned int       ulFront;            /*队列待写单元距离队列(不含保护字)头的长度，单位32bit */
    unsigned int       ulRear;             /*队列待读单元距离队列(不含保护字)头的长度，单位32bit */
    unsigned int       ulFrontslice;       /*更新邮箱环形队列的头指针系统时间*/
    unsigned int       ulRearslice;        /*更新邮箱环形队列的尾指针系统时间*/
    unsigned short      ausReserve[4];      /*保留*/
    unsigned int       ulProtectWord3;     /*保护字 0x55AA55AA*/
    unsigned int       ulProtectWord4;     /*保护字 0x5A5A5A5A*/
} MAILBOX_HEAD_STRU;

/* 邮箱头占用空间总长度定义*/
#define MAILBOX_HEAD_LEN                (sizeof(struct mb_head))
#define MAILBOX_MAX_CHANNEL             (30)
#define MAILBOX_MEM_HEAD_LEN            (MAILBOX_MAX_CHANNEL * MAILBOX_HEAD_LEN)

/* 各邮箱数据队列长度定义 */
#define MAILBOX_QUEUE_SIZE(src, dst, channel) \
    MAILBOX_QUEUE_SIZE_##src##2##dst##_##channel
enum MAILBOX_QUEUE_SIZE_ENUM
{
    /* 以下各枚举项按规则生成, 形如: MAILBOX_QUEUE_SIZE_MCU2ACPU_DEFAULT */
    MAILBOX_QUEUE_SIZE(MCU,  ACPU, MSG) = 0x00002000,
    MAILBOX_QUEUE_SIZE(ACPU, MCU,  MSG) = 0x00002000,
    MAILBOX_QUEUE_SIZE(MCU, ACPU, IFC)  = 0x00002000,
    MAILBOX_QUEUE_SIZE(ACPU, MCU, IFC)  = 0x00002000,

    MAILBOX_QUEUE_SIZE(MCU,  CCPU, MSG) = 0x00002000,
    MAILBOX_QUEUE_SIZE(CCPU, MCU,  MSG) = 0x00002000,
    MAILBOX_QUEUE_SIZE(MCU, CCPU, IFC)  = 0x00002000,
    MAILBOX_QUEUE_SIZE(CCPU, MCU, IFC)  = 0x00002000,

    MAILBOX_QUEUE_SIZE(ACPU, CCPU, MSG) = 0x00008000,
    MAILBOX_QUEUE_SIZE(CCPU, ACPU, MSG) = 0x00008000,
    MAILBOX_QUEUE_SIZE(ACPU, CCPU, IFC) = 0x00008000,
    MAILBOX_QUEUE_SIZE(CCPU, ACPU, IFC) = 0x00008000,

    MAILBOX_QUEUE_SIZE(ACPU, HIFI, MSG) = 0x00001800,
    MAILBOX_QUEUE_SIZE(HIFI, ACPU, MSG) = 0x00001800,

    MAILBOX_QUEUE_SIZE(CCPU, HIFI, MSG) = 0x00001800,
    MAILBOX_QUEUE_SIZE(HIFI, CCPU, MSG) = 0x00005000,

    MAILBOX_QUEUE_SIZE(BBE16, HIFI, MSG) = 0x00001800,
    MAILBOX_QUEUE_SIZE(HIFI, BBE16, MSG) = 0x00001800,

    MAILBOX_QUEUE_SIZE(MCU, HIFI, IFC) = 0x00002000,
    MAILBOX_QUEUE_SIZE(HIFI, MCU, IFC) = 0x00002000
};

/* 各邮箱控制头地址分配 */
#define MAILBOX_HEAD_ADDR(src, dst, channel) \
    MAILBOX_HEAD_ADDR_##src##2##dst##_##channel
enum MAILBOX_HEAD_ADDR_ENUM
{
    /* 以下各枚举项按规则生成, 形如: MAILBOX_HEAD_ADDR_MCU2ACPU_DEFAULT */
    MAILBOX_HEAD_ADDR(MCU,  ACPU, MSG)  = MAILBOX_MEM_BASEADDR,
    MAILBOX_HEAD_ADDR(ACPU, MCU,  MSG)  = MAILBOX_HEAD_ADDR(MCU,  ACPU, MSG) + MAILBOX_HEAD_LEN,
    MAILBOX_HEAD_ADDR(ACPU, HIFI, MSG)  = MAILBOX_HEAD_ADDR(ACPU, MCU,  MSG) + MAILBOX_HEAD_LEN,
    MAILBOX_HEAD_ADDR(HIFI, ACPU, MSG)  = MAILBOX_HEAD_ADDR(ACPU, HIFI, MSG) + MAILBOX_HEAD_LEN,
    MAILBOX_HEAD_ADDR(MCU,  CCPU, MSG)  = MAILBOX_HEAD_ADDR(HIFI, ACPU, MSG) + MAILBOX_HEAD_LEN,
    MAILBOX_HEAD_ADDR(CCPU, MCU,  MSG)  = MAILBOX_HEAD_ADDR(MCU,  CCPU, MSG) + MAILBOX_HEAD_LEN,
    MAILBOX_HEAD_ADDR(CCPU, HIFI, MSG)  = MAILBOX_HEAD_ADDR(CCPU, MCU,  MSG) + MAILBOX_HEAD_LEN,
    MAILBOX_HEAD_ADDR(HIFI, CCPU, MSG)  = MAILBOX_HEAD_ADDR(CCPU, HIFI, MSG) + MAILBOX_HEAD_LEN,

    MAILBOX_HEAD_ADDR(ACPU, CCPU, MSG)      = MAILBOX_HEAD_ADDR(HIFI, CCPU, MSG) + MAILBOX_HEAD_LEN,
    MAILBOX_HEAD_ADDR(CCPU, ACPU, MSG)      = MAILBOX_HEAD_ADDR(ACPU, CCPU, MSG) + MAILBOX_HEAD_LEN,
    MAILBOX_HEAD_ADDR(CCPU, ACPU, IFC)      = MAILBOX_HEAD_ADDR(CCPU, ACPU, MSG) + MAILBOX_HEAD_LEN,
    MAILBOX_HEAD_ADDR(ACPU, CCPU, IFC)      = MAILBOX_HEAD_ADDR(CCPU, ACPU, IFC) + MAILBOX_HEAD_LEN,

    MAILBOX_HEAD_ADDR(CCPU, MCU, IFC)      = MAILBOX_HEAD_ADDR(ACPU, CCPU, IFC) + MAILBOX_HEAD_LEN,
    MAILBOX_HEAD_ADDR(MCU, CCPU, IFC)      = MAILBOX_HEAD_ADDR(CCPU, MCU, IFC) + MAILBOX_HEAD_LEN,

    MAILBOX_HEAD_ADDR(ACPU, MCU, IFC)      = MAILBOX_HEAD_ADDR(MCU, CCPU, IFC) + MAILBOX_HEAD_LEN,
    MAILBOX_HEAD_ADDR(MCU, ACPU, IFC)      = MAILBOX_HEAD_ADDR(ACPU, MCU, IFC) + MAILBOX_HEAD_LEN,

    MAILBOX_HEAD_ADDR(BBE16, HIFI, MSG)  = MAILBOX_HEAD_ADDR(MCU, ACPU,  IFC) + MAILBOX_HEAD_LEN,
    MAILBOX_HEAD_ADDR(HIFI, BBE16, MSG)  = MAILBOX_HEAD_ADDR(BBE16, HIFI, MSG) + MAILBOX_HEAD_LEN,

    MAILBOX_HEAD_ADDR(MCU, HIFI, IFC)  = MAILBOX_HEAD_ADDR(HIFI, BBE16,  MSG) + MAILBOX_HEAD_LEN,
    MAILBOX_HEAD_ADDR(HIFI, MCU, IFC)  = MAILBOX_HEAD_ADDR(MCU, HIFI, IFC) + MAILBOX_HEAD_LEN,

    MAILBOX_HEAD_BOTTOM_ADDR                = MAILBOX_HEAD_ADDR(HIFI, MCU, IFC) + MAILBOX_HEAD_LEN

};

/* 各邮箱数据队列地址分配 */
#define MAILBOX_QUEUE_ADDR(src, dst, channel) \
    MAILBOX_QUEUE_ADDR_##src##2##dst##_##channel
#define MAILBOX_QUEUE_BOTTOM_ADDR(src, dst, channel) \
    (MAILBOX_QUEUE_ADDR(src, dst, channel) + MAILBOX_QUEUE_SIZE(src, dst, channel))
enum MAILBOX_QUEUE_ADDR_ENUM
{
    /* 以下各枚举项按规则生成, 形如: MAILBOX_QUEUE_ADDR_MCU2ACPU_DEFAULT */
    MAILBOX_QUEUE_ADDR(MCU,  ACPU, MSG) = MAILBOX_MEM_BASEADDR + MAILBOX_MEM_HEAD_LEN,
    MAILBOX_QUEUE_ADDR(ACPU, MCU,  MSG) = MAILBOX_QUEUE_BOTTOM_ADDR(MCU,  ACPU, MSG),
    MAILBOX_QUEUE_ADDR(ACPU, HIFI, MSG) = MAILBOX_QUEUE_BOTTOM_ADDR(ACPU, MCU,  MSG),
    MAILBOX_QUEUE_ADDR(HIFI, ACPU, MSG) = MAILBOX_QUEUE_BOTTOM_ADDR(ACPU, HIFI, MSG),
    MAILBOX_QUEUE_ADDR(MCU,  CCPU, MSG) = MAILBOX_QUEUE_BOTTOM_ADDR(HIFI, ACPU, MSG) ,
    MAILBOX_QUEUE_ADDR(CCPU, MCU,  MSG) = MAILBOX_QUEUE_BOTTOM_ADDR(MCU,  CCPU, MSG),
    MAILBOX_QUEUE_ADDR(CCPU, HIFI, MSG) = MAILBOX_QUEUE_BOTTOM_ADDR(CCPU, MCU,  MSG),
    MAILBOX_QUEUE_ADDR(HIFI, CCPU, MSG) = MAILBOX_QUEUE_BOTTOM_ADDR(CCPU, HIFI, MSG),

    MAILBOX_QUEUE_ADDR(ACPU, CCPU, MSG)  = MAILBOX_QUEUE_BOTTOM_ADDR(HIFI, CCPU, MSG),
    MAILBOX_QUEUE_ADDR(CCPU, ACPU, MSG)  = MAILBOX_QUEUE_BOTTOM_ADDR(ACPU, CCPU, MSG),
    MAILBOX_QUEUE_ADDR(CCPU, ACPU, IFC)  = MAILBOX_QUEUE_BOTTOM_ADDR(CCPU, ACPU, MSG),
    MAILBOX_QUEUE_ADDR(ACPU, CCPU, IFC)  = MAILBOX_QUEUE_BOTTOM_ADDR(CCPU, ACPU, IFC),

    MAILBOX_QUEUE_ADDR(CCPU, MCU, IFC)   = MAILBOX_QUEUE_BOTTOM_ADDR(ACPU, CCPU, IFC),
    MAILBOX_QUEUE_ADDR(MCU, CCPU, IFC)   = MAILBOX_QUEUE_BOTTOM_ADDR(CCPU, MCU, IFC),
    MAILBOX_QUEUE_ADDR(ACPU, MCU, IFC)   = MAILBOX_QUEUE_BOTTOM_ADDR(MCU, CCPU, IFC),
    MAILBOX_QUEUE_ADDR(MCU, ACPU, IFC)   = MAILBOX_QUEUE_BOTTOM_ADDR(ACPU, MCU, IFC),

    MAILBOX_QUEUE_ADDR(BBE16, HIFI, MSG) = MAILBOX_QUEUE_BOTTOM_ADDR(MCU, ACPU, IFC),
    MAILBOX_QUEUE_ADDR(HIFI, BBE16, MSG) = MAILBOX_QUEUE_BOTTOM_ADDR(BBE16, HIFI, MSG),

    MAILBOX_QUEUE_ADDR(MCU, HIFI, IFC) = MAILBOX_QUEUE_BOTTOM_ADDR(HIFI, BBE16, MSG),
    MAILBOX_QUEUE_ADDR(HIFI, MCU, IFC) = MAILBOX_QUEUE_BOTTOM_ADDR(MCU, HIFI, IFC),

    MAILBOX_MEMORY_BOTTOM_ADDR           = MAILBOX_QUEUE_BOTTOM_ADDR(HIFI, MCU, IFC)
};

/*共享内存中的保护字定义*/
#define MAILBOX_PROTECT1                (0x55AA55AA)    /* 邮箱保护字1，用于邮箱头及邮箱, 同时表示邮箱刚初始化没有接收过数据*/
#define MAILBOX_PROTECT2                (0x5A5A5A5A)    /* 邮箱保护字2，用于邮箱头及邮箱 */
#define MAILBOX_PROTECT_LEN             (sizeof(int))  /* 邮箱保护字长度，单位byte，邮箱头及邮箱头、尾均有两个这样的保护字 */
#define MAILBOX_MSGHEAD_NUMBER          (0xA5A5A5A5)    /* 跨核消息消息分隔字 */

#define MAILBOX_DATA_BASE_PROTECT_NUM         (2)    /* 邮箱通道共享内存数据区以首地址开始的保护字个数*/
#define MAILBOX_DATA_TAIL_PROTECT_NUM         (2)    /* 邮箱通道共享内存数据区以尾地址结束的保护字个数*/

/* 邮箱通道共享内存数据区长度中包含的保护字的个数，包括首地址开始的2个保护字，和末地址结束的2个保护字*/
#define MAILBOX_DATA_LEN_PROTECT_NUM          (MAILBOX_DATA_BASE_PROTECT_NUM + MAILBOX_DATA_TAIL_PROTECT_NUM)


/* hifi邮箱地址信息保护字 */
#define HIFI_MB_ADDR_PROTECT            (0x5a5a5a5a)

/*****************************************************************************
  3 枚举定义
*****************************************************************************/

/*****************************************************************************
  定义邮箱核与核之间的IPC中断号
*****************************************************************************/
#define MAILBOX_IPC_INT_NUM(src, dst, channel) \
    MAILBOX_IPC_INT_##src##2##dst##_##channel
enum IPC_MAILBOX_INT_ENUM
{
    /* 以下各枚举项按规则生成, 形如: MAILBOX_IPC_INT_CCPU2MCU_DEFAULT */
    MAILBOX_IPC_INT_NUM(CCPU, MCU, MSG)  = IPC_MCU_INT_SRC_CCPU_MSG,
    MAILBOX_IPC_INT_NUM(MCU, CCPU, MSG)  = IPC_CCPU_INT_SRC_MCU_MSG,

    MAILBOX_IPC_INT_NUM(CCPU, HIFI, MSG) = IPC_HIFI_INT_SRC_CCPU_MSG,
    MAILBOX_IPC_INT_NUM(HIFI, CCPU, MSG) = IPC_CCPU_INT_SRC_HIFI_MSG,

    MAILBOX_IPC_INT_NUM(ACPU, MCU, MSG)  = IPC_MCU_INT_SRC_ACPU_MSG,
    MAILBOX_IPC_INT_NUM(MCU, ACPU, MSG)  = IPC_ACPU_INT_SRC_MCU_MSG,

    MAILBOX_IPC_INT_NUM(ACPU, HIFI, MSG) = IPC_HIFI_INT_SRC_ACPU_MSG,
    MAILBOX_IPC_INT_NUM(HIFI, ACPU, MSG) = IPC_ACPU_INT_SRC_HIFI_MSG,

    MAILBOX_IPC_INT_NUM(HIFI, MCU, MSG)  = IPC_MCU_INT_SRC_HIFI_MSG,
    MAILBOX_IPC_INT_NUM(MCU, HIFI, MSG)  = IPC_HIFI_INT_SRC_MCU_MSG,

    MAILBOX_IPC_INT_NUM(CCPU, ACPU, MSG)    = IPC_ACPU_INT_SRC_CCPU_MSG,
    MAILBOX_IPC_INT_NUM(ACPU, CCPU, MSG)    = IPC_CCPU_INT_SRC_ACPU_MSG,

    MAILBOX_IPC_INT_NUM(CCPU, ACPU, IFC)    = IPC_ACPU_INT_SRC_CCPU_IFC,
    MAILBOX_IPC_INT_NUM(ACPU, CCPU, IFC)    = IPC_CCPU_INT_SRC_ACPU_IFC,

    MAILBOX_IPC_INT_NUM(CCPU, MCU, IFC)    = IPC_MCU_INT_SRC_CCPU_IFC,
    MAILBOX_IPC_INT_NUM(MCU, CCPU, IFC)    = IPC_CCPU_INT_SRC_MCU_IFC,

    MAILBOX_IPC_INT_NUM(ACPU, MCU, IFC)    = IPC_MCU_INT_SRC_ACPU_IFC,
    MAILBOX_IPC_INT_NUM(MCU, ACPU, IFC)    = IPC_ACPU_INT_SRC_MCU_IFC,

    MAILBOX_IPC_INT_NUM(BBE16, HIFI, MSG) = IPC_HIFI_INT_SRC_BBE_MSG,
    MAILBOX_IPC_INT_NUM(HIFI, BBE16, MSG) = IPC_BBE16_INT_SRC_HIFI_MSG,

	MAILBOX_IPC_INT_NUM(HIFI, MCU, IFC)  = IPC_MCU_INT_SRC_HIFI_IFC,
    MAILBOX_IPC_INT_NUM(MCU, HIFI, IFC)  = IPC_HIFI_INT_SRC_MCU_IFC
};

/* 各邮箱数据单个邮件最大长度定义 */
#define MAILBOX_MAILSIZE_MAX(src, dst, channel) \
    MAILBOX_MAILSIZE_MAX_##src##2##dst##_##channel
enum MAILBOX_MAILSIZE_MAX_ENUM
{
    /* 以下各枚举项按规则生成, 形如: MAILBOX_MAILSIZE_MAX_MCU2ACPU_DEFAULT */
    MAILBOX_MAILSIZE_MAX(MCU,  ACPU ,MSG)  = MAILBOX_QUEUE_SIZE(MCU,  ACPU ,MSG)/4, //DOTO:具体值需要分析
    MAILBOX_MAILSIZE_MAX(ACPU, MCU  ,MSG)  = MAILBOX_QUEUE_SIZE(ACPU, MCU  ,MSG)/4, //DOTO:具体值需要分析
    MAILBOX_MAILSIZE_MAX(ACPU, HIFI ,MSG)  = MAILBOX_QUEUE_SIZE(ACPU ,HIFI ,MSG)/4, //DOTO:具体值需要分析
    MAILBOX_MAILSIZE_MAX(HIFI, ACPU ,MSG)  = MAILBOX_QUEUE_SIZE(HIFI ,ACPU ,MSG)/4, //DOTO:具体值需要分析
    MAILBOX_MAILSIZE_MAX(MCU , CCPU ,MSG)  = MAILBOX_QUEUE_SIZE(MCU  ,CCPU ,MSG)/4,//DOTO:具体值需要分析
    MAILBOX_MAILSIZE_MAX(CCPU, MCU  ,MSG)  = MAILBOX_QUEUE_SIZE(CCPU ,MCU  ,MSG)/4,//DOTO:具体值需要分析
    MAILBOX_MAILSIZE_MAX(CCPU, HIFI ,MSG)  = MAILBOX_QUEUE_SIZE(CCPU ,HIFI ,MSG)/4,//DOTO:具体值需要分析
    MAILBOX_MAILSIZE_MAX(HIFI, CCPU ,MSG)  = MAILBOX_QUEUE_SIZE(HIFI ,CCPU ,MSG)/4,//DOTO:具体值需要分析

    MAILBOX_MAILSIZE_MAX(CCPU, ACPU ,MSG)  = MAILBOX_QUEUE_SIZE(CCPU, ACPU ,MSG)/4,//DOTO:具体值需要分析
    MAILBOX_MAILSIZE_MAX(ACPU, CCPU ,MSG)  = MAILBOX_QUEUE_SIZE(ACPU, CCPU ,MSG)/4,//DOTO:具体值需要分析
    MAILBOX_MAILSIZE_MAX(CCPU, ACPU ,IFC)  = MAILBOX_QUEUE_SIZE(CCPU, ACPU ,IFC)/4,//DOTO:具体值需要分析
    MAILBOX_MAILSIZE_MAX(ACPU, CCPU ,IFC)  = MAILBOX_QUEUE_SIZE(ACPU, CCPU ,IFC)/4,//DOTO:具体值需要分析

    MAILBOX_MAILSIZE_MAX(CCPU, MCU ,IFC)  = MAILBOX_QUEUE_SIZE(CCPU, MCU ,IFC)/4,//DOTO:具体值需要分析
    MAILBOX_MAILSIZE_MAX(MCU, CCPU ,IFC)  = MAILBOX_QUEUE_SIZE(MCU, CCPU ,IFC)/4,//DOTO:具体值需要分析

    MAILBOX_MAILSIZE_MAX(ACPU, MCU ,IFC)  = MAILBOX_QUEUE_SIZE(ACPU, MCU ,IFC)/4,//DOTO:具体值需要分析
    MAILBOX_MAILSIZE_MAX(MCU, ACPU ,IFC)  = MAILBOX_QUEUE_SIZE(MCU, ACPU ,IFC)/4,//DOTO:具体值需要分析

    MAILBOX_MAILSIZE_MAX(BBE16, HIFI ,MSG) = MAILBOX_QUEUE_SIZE(BBE16 ,HIFI ,MSG)/4,//DOTO:具体值需要分析
    MAILBOX_MAILSIZE_MAX(HIFI, BBE16 ,MSG) = MAILBOX_QUEUE_SIZE(HIFI ,BBE16 ,MSG)/4,//DOTO:具体值需要分析

    MAILBOX_MAILSIZE_MAX(MCU, HIFI ,IFC) = MAILBOX_QUEUE_SIZE(MCU ,HIFI ,IFC)/4,//DOTO:具体值需要分析
    MAILBOX_MAILSIZE_MAX(HIFI, MCU ,IFC) = MAILBOX_QUEUE_SIZE(HIFI ,MCU ,IFC)/4 //DOTO:具体值需要分析

};

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
 实 体 名  : struct mb_mail
 功能描述  : 核间邮件头
*****************************************************************************/
typedef struct mb_mail
{
    unsigned int       ulPartition;    /*消息分隔字 0xA5A5A5A5*/
    unsigned int       ulWriteSlice;   /*消息写入系统时间信息 */
    unsigned int       ulReadSlice;    /*消息读出系统时间信息 */
    unsigned int       ulSeqNum;       /*消息序列号 */
    unsigned int       ulPriority;     /*消息优先级：紧急、普通, 废弃*/
    unsigned int       ulMailCode;     /*邮编*/
    unsigned int       ausReserve[2];  /*保留*/
    unsigned int       ulMsgLength;    /*自ulMsgLength字段(不含本身)往后的消息长度*/
} MAILBOX_MSG_HEADER;

/************************************************************************
 结构名    : IPC_MAILBOX_QUEUE_STRU
 结构说明  : 核间邮箱缓存
 ************************************************************************/
/* 邮箱结构示意:
typedef struct
{
    unsigned long      ulProtectWord1;     //保护字 0x55aa55aa
    unsigned long      ulProtectWord2;     //保护字 0a5a5a5a5a
    unsigned long      aulMsgQueue[队列长度-4];//环形队列存放若干封邮件
    unsigned long      ulProtectWord3;     //保护字 0x55aa55aa
    unsigned long      ulProtectWord4;     //保护字 0x5a5a5a5a
} MAILBOX_QUEUE_STRU;
*/

/*****************************************************************************
 结构名    : AARM_HIFI_DYN_ADDR_SHARE_STRU
 协议表格  :
 ASN.1描述 :
 结构说明  :AARM和HIFI的共享地址，OAM需要赋值并拷贝至Hifi共享数据中的相应结构体
*****************************************************************************/
typedef struct
{
    unsigned int uwProtectWord;                /*0x5a5a5a5a*/
    unsigned int uwHifi2AarmMailBoxLen;        /* hifi到Aarm跨核邮箱长度 */
    unsigned int uwAarm2HifiMailBoxLen;        /* Aarm到hifi跨核邮箱长度 */
    unsigned int uwHifiAarmHeadAddr;
    unsigned int uwHifiAarmBodyAddr;
    unsigned int uwAarmHifiHeadAddr;
    unsigned int uwAarmHifiBodyAddr;
    unsigned int uwReserved[2];
}AARM_HIFI_MAILBOX_STRU;

/*****************************************************************************
 结构名    : CARM_HIFI_DYN_ADDR_SHARE_STRU
 协议表格  :
 ASN.1描述 :
 结构说明  :CARM和HIFI的共享地址，OAM需要赋值并拷贝至Hifi共享数据中的相应结构体
*****************************************************************************/
typedef struct
{
    unsigned int uwProtectWord;                /*0x5a5a5a5a*/
    unsigned int uwHifi2CarmMailBoxLen;        /* hifi到Carm跨核邮箱长度 */
    unsigned int uwCarm2HifiMailBoxLen;        /* Carm到hifi跨核邮箱长度 */
    unsigned int uwHifiCarmHeadAddr;
    unsigned int uwHifiCarmBodyAddr;
    unsigned int uwCarmHifiHeadAddr;
    unsigned int uwCarmHifiBodyAddr;
    unsigned int uwReserved[2];
}CARM_HIFI_MAILBOX_STRU;

/*****************************************************************************
 结构名    : CARM_HIFI_DYN_ADDR_SHARE_STRU
 协议表格  :
 ASN.1描述 :
 结构说明  :CARM和HIFI的共享地址，OAM需要赋值并拷贝至Hifi共享数据中的相应结构体
*****************************************************************************/
typedef struct
{
    unsigned int uwProtectWord;             /*0x5a5a5a5a*/
    CARM_HIFI_MAILBOX_STRU stCarmHifiMB;    /*CARM和HIFI的邮箱共享区定义*/
    AARM_HIFI_MAILBOX_STRU stAarmHifiMB;    /*AARM和HIFI的邮箱共享区定义*/
    unsigned int uwNvBaseAddrPhy;          /*DDR上NV备份区首地址的物理地址*/
    unsigned int uwNvBaseAddrVirt;         /*DDR上NV备份区首地址的ARM虚拟地址*/
    unsigned int uwReserved[2];
}CARM_HIFI_DYN_ADDR_SHARE_STRU;

/*****************************************************************************
  7 UNION定义
*****************************************************************************/


/*****************************************************************************
  8 OTHERS定义
*****************************************************************************/


/*****************************************************************************
  9 全局变量声明
*****************************************************************************/

/*****************************************************************************
  10 函数声明
*****************************************************************************/

#else
/*****************************************************************************
  2 宏定义
*****************************************************************************/

/* 定义源CPU 往 目标CPU的邮箱通道, 每通道对应独立的邮箱缓存 */

/* 按规则生成枚举项的宏定义 */
#define MAILBOX_CHANNEL_BEGIN(src, dst) \
    enum MAILBOX_CHANNEL_##src##2##dst##_ENUM \
    { \
        MAILBOX_CHANNEL_##src##2##dst##_RSERVED = -1,

#define MAILBOX_CHANNEL_ITEM(src, dst, channel)  \
    MAILBOX_CHANNEL_##src##2##dst##_##channel

#define MAILBOX_CHANNEL_END(src, dst) \
        MAILBOX_CHANNEL_##src##2##dst##_BUTT \
    };

/* CCPU -> HIFI */
MAILBOX_CHANNEL_BEGIN(CCPU, HIFI)
    /* 以下各枚举项按规则生成, 形如: MAILBOX_CHANNEL_CCPU2HIFI_DEFAULT */
    MAILBOX_CHANNEL_ITEM(CCPU, HIFI, MSG),
MAILBOX_CHANNEL_END(CCPU, HIFI)

/* CCPU -> MCU */
MAILBOX_CHANNEL_BEGIN(CCPU, MCU)
    MAILBOX_CHANNEL_ITEM(CCPU, MCU, MSG),
    MAILBOX_CHANNEL_ITEM(CCPU, MCU, IFC),
MAILBOX_CHANNEL_END(CCPU, MCU)

/* CCPU -> ACPU */
MAILBOX_CHANNEL_BEGIN(CCPU, ACPU)
    MAILBOX_CHANNEL_ITEM(CCPU, ACPU, MSG),
    MAILBOX_CHANNEL_ITEM(CCPU, ACPU, IFC),
MAILBOX_CHANNEL_END(CCPU, ACPU)

/* ACPU -> CCPU */
MAILBOX_CHANNEL_BEGIN(ACPU, CCPU)
    MAILBOX_CHANNEL_ITEM(ACPU, CCPU, MSG),
    MAILBOX_CHANNEL_ITEM(ACPU, CCPU, IFC),
MAILBOX_CHANNEL_END(ACPU, CCPU)

/* ACPU -> MCU */
MAILBOX_CHANNEL_BEGIN(ACPU, MCU)
    MAILBOX_CHANNEL_ITEM(ACPU, MCU, MSG),
    MAILBOX_CHANNEL_ITEM(ACPU, MCU, IFC),
MAILBOX_CHANNEL_END(ACPU, MCU)

/* ACPU -> HIFI */
MAILBOX_CHANNEL_BEGIN(ACPU, HIFI)
    MAILBOX_CHANNEL_ITEM(ACPU, HIFI, MSG),
MAILBOX_CHANNEL_END(ACPU, HIFI)

/* HIFI -> ACPU */
MAILBOX_CHANNEL_BEGIN(HIFI, ACPU)
    MAILBOX_CHANNEL_ITEM(HIFI, ACPU, MSG),
MAILBOX_CHANNEL_END(HIFI, ACPU)

/* HIFI -> CCPU */
MAILBOX_CHANNEL_BEGIN(HIFI, CCPU)
    MAILBOX_CHANNEL_ITEM(HIFI, CCPU, MSG),
MAILBOX_CHANNEL_END(HIFI, CCPU)

/* HIFI -> BBE16 */
MAILBOX_CHANNEL_BEGIN(HIFI, BBE16)
    MAILBOX_CHANNEL_ITEM(HIFI, BBE16, MSG),
MAILBOX_CHANNEL_END(HIFI, BBE16)

/* MCU -> ACPU */
MAILBOX_CHANNEL_BEGIN(MCU, ACPU)
    MAILBOX_CHANNEL_ITEM(MCU, ACPU, MSG),
    MAILBOX_CHANNEL_ITEM(MCU, ACPU, IFC),
MAILBOX_CHANNEL_END(MCU, ACPU)

/* MCU -> CCPU */
MAILBOX_CHANNEL_BEGIN(MCU, CCPU)
    MAILBOX_CHANNEL_ITEM(MCU, CCPU, MSG),
    MAILBOX_CHANNEL_ITEM(MCU, CCPU, IFC),
MAILBOX_CHANNEL_END(MCU, CCPU)

/* BBE16 -> HIFI */
MAILBOX_CHANNEL_BEGIN(BBE16, HIFI)
    MAILBOX_CHANNEL_ITEM(BBE16, HIFI, MSG),
MAILBOX_CHANNEL_END(BBE16, HIFI)

/* 有助SI解析, 利于阅读代码 */
enum MAILBOX_GAP_FOR_SI_PARSE {MAILBOX_GAP_FOR_SI_BUTT};

#define MAILBOX_ID_SRC_CPU_OFFSET       (24)        /*邮件ID中的源CPU ID bit位偏移地址*/
#define MAILBOX_ID_DST_CPU_OFFSET       (16)        /*邮件ID中的源CPU ID bit位偏移地址*/
#define MAILBOX_ID_CHANNEL_OFFSET       (8)         /*邮件ID中邮箱内存通道 ID bit位偏移地址*/

/* 邮编起始编号宏定义 */
#define MAILBOX_MAILCODE_CHANNEL(src, dst, channel) \
    ( ((unsigned int)(src) << MAILBOX_ID_SRC_CPU_OFFSET) \
    | ((unsigned int)(dst) << MAILBOX_ID_DST_CPU_OFFSET) \
    | ((unsigned int)(channel) << MAILBOX_ID_CHANNEL_OFFSET) )

#define MAILBOX_CPUID(cpu)   MAILBOX_CPUID_##cpu

#define MAILBOX_MAILCODE_RESERVED(src, dst, channel) \
    MAILBOX_MAILCODE_CHANNEL(MAILBOX_CPUID(src), \
                             MAILBOX_CPUID(dst), \
                            MAILBOX_CHANNEL_ITEM(src, dst, channel))

#define MAILBOX_MAILCODE_ITEM_RESERVED(src, dst, channel) \
    MAILBOX_MAILCODE_##src##2##dst##_##channel##_RESERVED

#define MAILBOX_MAILCODE_ITEM_END(src, dst, channel)    \
    MAILBOX_MAILCODE_##src##2##dst##_##channel##_BUTT

#define MAILBOX_MAILCODE_ITEM_BEGIN(src, dst, channel)  \
    MAILBOX_MAILCODE_ITEM_RESERVED(src, dst, channel) = MAILBOX_MAILCODE_RESERVED(src, dst, channel)

/*****************************************************************************
  3 枚举定义
*****************************************************************************/

/*****************************************************************************
 实 体 名  : MAILBOX_CPUID_E
 功能描述  : 定义邮箱涉及CPU编号
*****************************************************************************/
enum MAILBOX_CPUID_ENUM
{
    MAILBOX_CPUID_RESERVED  =   -1,
    MAILBOX_CPUID_ACPU      =   IPC_CORE_ACORE,
    MAILBOX_CPUID_CCPU      =   IPC_CORE_CCORE,
    MAILBOX_CPUID_MCU       =   IPC_CORE_ACORE,
    MAILBOX_CPUID_BBE16     =   IPC_CORE_LDSP,
    MAILBOX_CPUID_HIFI      =   IPC_CORE_HiFi,
    MAILBOX_CPUID_BUTT
};

/*****************************************************************************
 实体名称  : MAILBOX_MAILCODE_ENUM
 功能描述  : 邮编枚举定义, 邮编唯一标识邮件发送目标, 也即邮件数据接收处理者
*****************************************************************************/
enum MAILBOX_MAILCODE_ENUM
{
    /* CCPU->MCU 邮编号定义在这里 */
    MAILBOX_MAILCODE_ITEM_BEGIN(CCPU, MCU, MSG),
    MAILBOX_MAILCODE_CCPU_TO_MCU_VOS_MSG_NORMAL,
    MAILBOX_MAILCODE_CCPU_TO_MCU_VOS_MSG_URGENT,
    BSP_MAILBOX_CHANNEL_CCPU_TO_MCU_MCA_CH,

    MAILBOX_MAILCODE_ITEM_END(CCPU, MCU, MSG),

    /* CCPU->MCU IFC调用号定义在这里 */
    MAILBOX_MAILCODE_ITEM_BEGIN(CCPU, MCU, IFC),
    MAILBOX_IFC_CCPU_TO_MCU_TEST_CMP,
    MAILBOX_IFC_CCPU_TO_MCU_TEST,
    MAILBOX_IFC_CCPU_TO_MCU_MCA,
    MAILBOX_MAILCODE_ITEM_END(CCPU, MCU, IFC),

    /* CCPU->HIFI 邮编号定义在这里 */
    MAILBOX_MAILCODE_ITEM_BEGIN(CCPU, HIFI, MSG),
    MAILBOX_MAILCODE_CCPU_TO_HIFI_VOS_MSG_NORMAL,
    MAILBOX_MAILCODE_CCPU_TO_HIFI_VOS_MSG_URGENT,
    MAILBOX_MAILCODE_ITEM_END(CCPU, HIFI, MSG),

    /* CCPU->ACPU 邮编号定义在这里 */
    MAILBOX_MAILCODE_ITEM_BEGIN(CCPU, ACPU, MSG),
    MAILBOX_MAILCODE_ITEM_END(CCPU, ACPU, MSG),

    /* CCPU->ACPU IFC编号定义在这里 */
    MAILBOX_MAILCODE_ITEM_BEGIN(CCPU, ACPU, IFC),
    MAILBOX_IFC_CCPU_TO_ACPU_TEST_CMP,
    MAILBOX_IFC_CCPU_TO_ACPU_TEST,
    MAILBOX_IFC_CCPU_TO_ACPU_PRINT,
    MAILBOX_IFC_CCPU_TO_ACPU_FOPEN,
    MAILBOX_IFC_CCPU_TO_ACPU_FCLOSE,
    MAILBOX_IFC_CCPU_TO_ACPU_FREAD,
    MAILBOX_IFC_CCPU_TO_ACPU_FWRITE,
    MAILBOX_IFC_CCPU_TO_ACPU_FSEEK,
    MAILBOX_IFC_CCPU_TO_ACPU_REMOVE,
    MAILBOX_IFC_CCPU_TO_ACPU_FTELL,
    MAILBOX_IFC_CCPU_TO_ACPU_RENAME,
    MAILBOX_IFC_CCPU_TO_ACPU_ACCESS,
    MAILBOX_IFC_CCPU_TO_ACPU_MKDIR,
    MAILBOX_IFC_CCPU_TO_ACPU_RMDIR,
    MAILBOX_IFC_ACPU_TO_CCPU_PMIC_IRQEVENT_REPO,
    MAILBOX_MAILCODE_ITEM_END(CCPU, ACPU, IFC),

    /* ACPU->MCU 邮编号定义在这里 */
    MAILBOX_MAILCODE_ITEM_BEGIN(ACPU, MCU, MSG),
    MAILBOX_MAILCODE_ACPU_TO_MCU_VOS_MSG_NORMAL,
    MAILBOX_MAILCODE_ACPU_TO_MCU_VOS_MSG_URGENT,
    BSP_MAILBOX_CHANNEL_ACPU_TO_MCU_IFC_CH,
    BSP_MAILBOX_CHANNEL_ACPU_TO_MCU_IFC_RESPONSE_CH,
    BSP_MAILBOX_CHANNEL_ACPU_TO_MCU_SENSOR_CH,
    BSP_MAILBOX_CHANNEL_ACPU_TO_MCU_TP_CH,
    BSP_MAILBOX_CHANNEL_ACPU_TO_MCU_MCA_CH,
    BSP_MAILBOX_CHANNEL_ACPU_TO_MCU_RST_CH,
    MAILBOX_MAILCODE_ITEM_END(ACPU, MCU, MSG),

    /* ACPU->MCU IFC远程函数调用邮编号定义在这里 */
    MAILBOX_MAILCODE_ITEM_BEGIN(ACPU, MCU, IFC),
    MAILBOX_IFC_ACPU_TO_MCU_TEST_CMP,
    MAILBOX_IFC_ACPU_TO_MCU_TEST,
    MAILBOX_IFC_ACPU_TO_MCU_HUTAF_HLT,
	MAILBOX_IFC_ACPU_TO_MCU_MCA,
    MAILBOX_IFC_ACPU_TO_MCU_MNTN,
    MAILBOX_IFC_ACPU_TO_MCU_RUN_CMD,
    MAILBOX_MAILCODE_ITEM_END(ACPU, MCU, IFC),


    /* ACPU->HIFI 邮编号定义在这里 */
    MAILBOX_MAILCODE_ITEM_BEGIN(ACPU, HIFI, MSG),
    MAILBOX_MAILCODE_ACPU_TO_HIFI_VOS_MSG_NORMAL,
    MAILBOX_MAILCODE_ACPU_TO_HIFI_VOS_MSG_URGENT,
    MAILBOX_MAILCODE_ACPU_TO_HIFI_AUDIO,
    MAILBOX_MAILCODE_ACPU_TO_HIFI_MISC,
    MAILBOX_MAILCODE_ACPU_TO_HIFI_CCORE_RESET_ID,
    MAILBOX_MAILCODE_ITEM_END(ACPU, HIFI, MSG),

    /* ACPU->CCPU MSG号定义在这里 */
    MAILBOX_MAILCODE_ITEM_BEGIN(ACPU, CCPU, MSG),
    MAILBOX_IFC_ACPU_TO_CCPU_CSHELL_START,
    MAILBOX_MAILCODE_ITEM_END(ACPU, CCPU, MSG),

    /* ACPU->CCPU IFC号定义在这里 */
    MAILBOX_MAILCODE_ITEM_BEGIN(ACPU, CCPU, IFC),
    MAILBOX_IFC_ACPU_TO_CCPU_TEST_CMP,
    MAILBOX_IFC_ACPU_TO_CCPU_TEST,
    MAILBOX_IFC_ACPU_TO_CCPU_PRINT,
    MAILBOX_IFC_ACPU_TO_CCPU_FOPEN,
    MAILBOX_IFC_ACPU_TO_CCPU_FCLOSE,
    MAILBOX_IFC_ACPU_TO_CCPU_FREAD,
    MAILBOX_IFC_ACPU_TO_CCPU_FWRITE,
    MAILBOX_IFC_ACPU_TO_CCPU_FSEEK,
    MAILBOX_IFC_ACPU_TO_CCPU_REMOVE,
    MAILBOX_IFC_ACPU_TO_CCPU_FTELL,
    MAILBOX_IFC_ACPU_TO_CCPU_RENAME,
    MAILBOX_IFC_ACPU_TO_CCPU_ACCESS,
    MAILBOX_IFC_ACPU_TO_CCPU_MKDIR,
    MAILBOX_IFC_ACPU_TO_CCPU_RMDIR,
    MAILBOX_IFC_ACPU_TO_CCPU_BASE_TEST2,
    MAILBOX_IFC_ACPU_TO_CCPU_BASE_TEST1,
	MAILBOX_IFC_ACPU_TO_CCPU_PMIC_IRQEVENT,
    MAILBOX_IFC_ACPU_TO_CCPU_READ_EFUSE,
    MAILBOX_IFC_ACPU_TO_CCPU_SYSTEMERROR,
    MAILBOX_MAILCODE_ITEM_END(ACPU, CCPU, IFC),

    /* HIFI->CCPU 邮编号定义在这里 */
    MAILBOX_MAILCODE_ITEM_BEGIN(HIFI, CCPU, MSG),
    MAILBOX_MAILCODE_HIFI_TO_CCPU_VOS_MSG_NORMAL,
    MAILBOX_MAILCODE_HIFI_TO_CCPU_VOS_MSG_URGENT,
    MAILBOX_MAILCODE_ITEM_END(HIFI, CCPU, MSG),

    /* HIFI->ACPU 邮编号定义在这里 */
    MAILBOX_MAILCODE_ITEM_BEGIN(HIFI, ACPU, MSG),
    MAILBOX_MAILCODE_HIFI_TO_ACPU_VOS_MSG_NORMAL,
    MAILBOX_MAILCODE_HIFI_TO_ACPU_VOS_MSG_URGENT,
    MAILBOX_MAILCODE_HIFI_TO_ACPU_AUDIO,
    MAILBOX_MAILCODE_HIFI_TO_ACPU_MISC,
    MAILBOX_MAILCODE_HIFI_TO_ACPU_CCORE_RESET_ID,
    MAILBOX_MAILCODE_ITEM_END(HIFI, ACPU, MSG),

    /* HIFI->BBE16 邮编号定义在这里 */
    MAILBOX_MAILCODE_ITEM_BEGIN(HIFI, BBE16, MSG),
    MAILBOX_MAILCODE_HIFI_TO_BBE16_VOS_MSG_NORMAL,
    MAILBOX_MAILCODE_HIFI_TO_BBE16_VOS_MSG_URGENT,
    MAILBOX_MAILCODE_ITEM_END(HIFI, BBE16, MSG),

    /* MCU->CCPU 邮编号定义在这里 */
    MAILBOX_MAILCODE_ITEM_BEGIN(MCU, CCPU, MSG),
    MAILBOX_MAILCODE_MCU_TO_CCPU_VOS_MSG_NORMAL,
    MAILBOX_MAILCODE_MCU_TO_CCPU_VOS_MSG_URGENT,
    BSP_MAILBOX_CHANNEL_MCU_TO_CCPU_MCA_CH,
    MAILBOX_MAILCODE_ITEM_END(MCU, CCPU, MSG),

    /* MCU->CCPU ifc邮编号定义在这里 */
    MAILBOX_MAILCODE_ITEM_BEGIN(MCU, CCPU, IFC),
    MAILBOX_IFC_MCU_TO_CCPU_TEST_CMP,
    MAILBOX_IFC_MCU_TO_CCPU_BASE_TEST2,
    MAILBOX_IFC_MCU_TO_CCPU_BASE_TEST1,
    MAILBOX_IFC_MCU_TO_CCPU_TEST,
    MAILBOX_MAILCODE_ITEM_END(MCU, CCPU, IFC),

    /* MCU->ACPU 邮编号定义在这里 */
    MAILBOX_MAILCODE_ITEM_BEGIN(MCU, ACPU, MSG),
    MAILBOX_MAILCODE_MCU_TO_ACPU_VOS_MSG_NORMAL,
    MAILBOX_MAILCODE_MCU_TO_ACPU_VOS_MSG_URGENT,
    BSP_MAILBOX_CHANNEL_MCU_TO_ACPU_IFC_CH,
    BSP_MAILBOX_CHANNEL_MCU_TO_ACPU_IFC_RESPONSE_CH,
    BSP_MAILBOX_CHANNEL_MCU_TO_ACPU_SENSOR_CH,
    BSP_MAILBOX_CHANNEL_MCU_TO_ACPU_TP_CH,
    BSP_MAILBOX_CHANNEL_MCU_TO_ACPU_MCA_CH,
    BSP_MAILBOX_CHANNEL_MCU_TO_ACPU_MNTN_CH,
    MAILBOX_IFC_MCU_TO_ACPU_HUTAF_HLT,
    MAILBOX_MAILCODE_MCU_TO_ACPU_CCORE_RESET_ID,
    MAILBOX_MAILCODE_ITEM_END(MCU, ACPU, MSG),

    /* MCU->ACPU 远程函数调用邮编号定义在这里 */
    MAILBOX_MAILCODE_ITEM_BEGIN(MCU, ACPU, IFC),
    MAILBOX_IFC_MCU_TO_ACPU_TEST_CMP,
    MAILBOX_IFC_MCU_TO_ACPU_TEST,
    MAILBOX_IFC_MCU_TO_ACPU_PRINT,
    MAILBOX_MAILCODE_ITEM_END(MCU, ACPU, IFC),

    /* BBE16 -> HIFI 邮编号定义在这里 */
    MAILBOX_MAILCODE_ITEM_BEGIN(BBE16, HIFI, MSG),
    MAILBOX_MAILCODE_BBE16_TO_HIFI_VOS_MSG_NORMAL,
    MAILBOX_MAILCODE_BBE16_TO_HIFI_VOS_MSG_URGENT,
    MAILBOX_MAILCODE_ITEM_END(BBE16, HIFI, MSG),
};

/*****************************************************************************
 实 体 名  : MAILBOX_RET_ENUM
 功能描述  : 邮箱接口返回值
*****************************************************************************/
#define    MAILBOX_OK                       0
#define    MAILBOX_ERRO                     0xF7654321
#define    MAILBOX_FULL                     0xF7654322
#define    MAILBOX_NOT_READY                0xF7654323   /*目标CPU邮箱未初始化*/
#define    MAILBOX_TARGET_NOT_READY         MAILBOX_NOT_READY   /*目标CPU邮箱未初始化*/
#define    MAILBOX_TIME_OUT                 0xF7654324     /*发送等待返回超时*/

/* 邮件序列号的初始值 */
#define MAILBOX_SEQNUM_START            (0)

/* 邮箱占用memory基地址 */
#define MAILBOX_MEM_BASEADDR            (DDR_HIFI_MBX_ADDR)

/* 邮箱占用memory预留总长度, 包括邮箱控制头和邮箱队列缓存 */
#define MAILBOX_MEM_LENGTH              (DDR_HIFI_MBX_SIZE)

/*****************************************************************************
 实 体 名  : struct mb_head
 功能描述  : 核间邮箱缓存头, 通过保护字判断邮箱通道有没有被初始化, 此功能需要
             fastboot同步修改:上电初始化对邮箱共享内存头数据清零
*****************************************************************************/
typedef struct mb_head
{
    unsigned int       ulProtectWord1;     /*保护字 0x55AA55AA*/
    unsigned int       ulProtectWord2;     /*保护字 0x5A5A5A5A*/
    unsigned int       ulFront;            /*队列待写单元距离队列(不含保护字)头的长度，单位32bit */
    unsigned int       ulRear;             /*队列待读单元距离队列(不含保护字)头的长度，单位32bit */
    unsigned int       ulFrontslice;       /*更新邮箱环形队列的头指针系统时间*/
    unsigned int       ulRearslice;        /*更新邮箱环形队列的尾指针系统时间*/
    unsigned short      ausReserve[4];      /*保留*/
    unsigned int       ulProtectWord3;     /*保护字 0x55AA55AA*/
    unsigned int       ulProtectWord4;     /*保护字 0x5A5A5A5A*/
} MAILBOX_HEAD_STRU;

/* 邮箱头占用空间总长度定义*/
#define MAILBOX_HEAD_LEN                (sizeof(struct mb_head))
#define MAILBOX_MAX_CHANNEL             (30)
#define MAILBOX_MEM_HEAD_LEN            (MAILBOX_MAX_CHANNEL * MAILBOX_HEAD_LEN)

/* 各邮箱数据队列长度定义 */
#define MAILBOX_QUEUE_SIZE(src, dst, channel) \
    MAILBOX_QUEUE_SIZE_##src##2##dst##_##channel
enum MAILBOX_QUEUE_SIZE_ENUM
{
    /* 以下各枚举项按规则生成, 形如: MAILBOX_QUEUE_SIZE_MCU2ACPU_DEFAULT */
    MAILBOX_QUEUE_SIZE(MCU,  ACPU, MSG) = 0x00000000,
    MAILBOX_QUEUE_SIZE(ACPU, MCU,  MSG) = 0x00000000,
    MAILBOX_QUEUE_SIZE(MCU, ACPU, IFC)  = 0x00000000,
    MAILBOX_QUEUE_SIZE(ACPU, MCU, IFC)  = 0x00000000,

    MAILBOX_QUEUE_SIZE(MCU,  CCPU, MSG) = 0x00000000,
    MAILBOX_QUEUE_SIZE(CCPU, MCU,  MSG) = 0x00000000,
    MAILBOX_QUEUE_SIZE(MCU, CCPU, IFC)  = 0x00000000,
    MAILBOX_QUEUE_SIZE(CCPU, MCU, IFC)  = 0x00000000,

    MAILBOX_QUEUE_SIZE(ACPU, CCPU, MSG) = 0x00000000,
    MAILBOX_QUEUE_SIZE(CCPU, ACPU, MSG) = 0x00000000,
    MAILBOX_QUEUE_SIZE(ACPU, CCPU, IFC) = 0x00000000,
    MAILBOX_QUEUE_SIZE(CCPU, ACPU, IFC) = 0x00000000,

    MAILBOX_QUEUE_SIZE(ACPU, HIFI, MSG) = 0x00001800,
    MAILBOX_QUEUE_SIZE(HIFI, ACPU, MSG) = 0x00001800,

    MAILBOX_QUEUE_SIZE(CCPU, HIFI, MSG) = 0x00001800,
    MAILBOX_QUEUE_SIZE(HIFI, CCPU, MSG) = 0x00001800,

    MAILBOX_QUEUE_SIZE(BBE16, HIFI, MSG) = 0x00001800,
    MAILBOX_QUEUE_SIZE(HIFI, BBE16, MSG) = 0x00001800
};

/* 各邮箱控制头地址分配 */
#define MAILBOX_HEAD_ADDR(src, dst, channel) \
    MAILBOX_HEAD_ADDR_##src##2##dst##_##channel
enum MAILBOX_HEAD_ADDR_ENUM
{
    /* 以下各枚举项按规则生成, 形如: MAILBOX_HEAD_ADDR_MCU2ACPU_DEFAULT */
    MAILBOX_HEAD_ADDR(MCU,  ACPU, MSG)  = MAILBOX_MEM_BASEADDR,
    MAILBOX_HEAD_ADDR(ACPU, MCU,  MSG)  = MAILBOX_HEAD_ADDR(MCU,  ACPU, MSG) + MAILBOX_HEAD_LEN,
    MAILBOX_HEAD_ADDR(ACPU, HIFI, MSG)  = MAILBOX_HEAD_ADDR(ACPU, MCU,  MSG) + MAILBOX_HEAD_LEN,
    MAILBOX_HEAD_ADDR(HIFI, ACPU, MSG)  = MAILBOX_HEAD_ADDR(ACPU, HIFI, MSG) + MAILBOX_HEAD_LEN,
    MAILBOX_HEAD_ADDR(MCU,  CCPU, MSG)  = MAILBOX_HEAD_ADDR(HIFI, ACPU, MSG) + MAILBOX_HEAD_LEN,
    MAILBOX_HEAD_ADDR(CCPU, MCU,  MSG)  = MAILBOX_HEAD_ADDR(MCU,  CCPU, MSG) + MAILBOX_HEAD_LEN,
    MAILBOX_HEAD_ADDR(CCPU, HIFI, MSG)  = MAILBOX_HEAD_ADDR(CCPU, MCU,  MSG) + MAILBOX_HEAD_LEN,
    MAILBOX_HEAD_ADDR(HIFI, CCPU, MSG)  = MAILBOX_HEAD_ADDR(CCPU, HIFI, MSG) + MAILBOX_HEAD_LEN,

    MAILBOX_HEAD_ADDR(ACPU, CCPU, MSG)  = MAILBOX_HEAD_ADDR(HIFI, CCPU, MSG) + MAILBOX_HEAD_LEN,
    MAILBOX_HEAD_ADDR(CCPU, ACPU, MSG)  = MAILBOX_HEAD_ADDR(ACPU, CCPU, MSG) + MAILBOX_HEAD_LEN,
    MAILBOX_HEAD_ADDR(CCPU, ACPU, IFC)  = MAILBOX_HEAD_ADDR(CCPU, ACPU, MSG) + MAILBOX_HEAD_LEN,
    MAILBOX_HEAD_ADDR(ACPU, CCPU, IFC)  = MAILBOX_HEAD_ADDR(CCPU, ACPU, IFC) + MAILBOX_HEAD_LEN,

    MAILBOX_HEAD_ADDR(CCPU, MCU, IFC)   = MAILBOX_HEAD_ADDR(ACPU, CCPU, IFC) + MAILBOX_HEAD_LEN,
    MAILBOX_HEAD_ADDR(MCU, CCPU, IFC)   = MAILBOX_HEAD_ADDR(CCPU, MCU,  IFC) + MAILBOX_HEAD_LEN,
    MAILBOX_HEAD_ADDR(ACPU, MCU, IFC)   = MAILBOX_HEAD_ADDR(MCU,  CCPU, IFC) + MAILBOX_HEAD_LEN,
    MAILBOX_HEAD_ADDR(MCU, ACPU, IFC)   = MAILBOX_HEAD_ADDR(ACPU, MCU,  IFC) + MAILBOX_HEAD_LEN,

    MAILBOX_HEAD_ADDR(BBE16, HIFI, MSG) = MAILBOX_HEAD_ADDR(MCU, ACPU,  IFC) + MAILBOX_HEAD_LEN,
    MAILBOX_HEAD_ADDR(HIFI, BBE16, MSG) = MAILBOX_HEAD_ADDR(BBE16,HIFI, MSG) + MAILBOX_HEAD_LEN,

    MAILBOX_HEAD_BOTTOM_ADDR            = MAILBOX_HEAD_ADDR(HIFI, BBE16,MSG) + MAILBOX_HEAD_LEN

};

/* 各邮箱数据队列地址分配 */
#define MAILBOX_QUEUE_ADDR(src, dst, channel) \
    MAILBOX_QUEUE_ADDR_##src##2##dst##_##channel
#define MAILBOX_QUEUE_BOTTOM_ADDR(src, dst, channel) \
    (MAILBOX_QUEUE_ADDR(src, dst, channel) + MAILBOX_QUEUE_SIZE(src, dst, channel))
enum MAILBOX_QUEUE_ADDR_ENUM
{
    /* 以下各枚举项按规则生成, 形如: MAILBOX_QUEUE_ADDR_MCU2ACPU_DEFAULT */
    MAILBOX_QUEUE_ADDR(MCU,  ACPU, MSG)  = MAILBOX_MEM_BASEADDR + MAILBOX_MEM_HEAD_LEN,
    MAILBOX_QUEUE_ADDR(ACPU, MCU,  MSG)  = MAILBOX_QUEUE_BOTTOM_ADDR(MCU,  ACPU, MSG),
    MAILBOX_QUEUE_ADDR(ACPU, HIFI, MSG)  = MAILBOX_QUEUE_BOTTOM_ADDR(ACPU, MCU,  MSG),
    MAILBOX_QUEUE_ADDR(HIFI, ACPU, MSG)  = MAILBOX_QUEUE_BOTTOM_ADDR(ACPU, HIFI, MSG),
    MAILBOX_QUEUE_ADDR(MCU,  CCPU, MSG)  = MAILBOX_QUEUE_BOTTOM_ADDR(HIFI, ACPU, MSG) ,
    MAILBOX_QUEUE_ADDR(CCPU, MCU,  MSG)  = MAILBOX_QUEUE_BOTTOM_ADDR(MCU,  CCPU, MSG),
    MAILBOX_QUEUE_ADDR(CCPU, HIFI, MSG)  = MAILBOX_QUEUE_BOTTOM_ADDR(CCPU, MCU,  MSG),
    MAILBOX_QUEUE_ADDR(HIFI, CCPU, MSG)  = MAILBOX_QUEUE_BOTTOM_ADDR(CCPU, HIFI, MSG),

    MAILBOX_QUEUE_ADDR(ACPU, CCPU, MSG)  = MAILBOX_QUEUE_BOTTOM_ADDR(HIFI, CCPU, MSG),
    MAILBOX_QUEUE_ADDR(CCPU, ACPU, MSG)  = MAILBOX_QUEUE_BOTTOM_ADDR(ACPU, CCPU, MSG),
    MAILBOX_QUEUE_ADDR(CCPU, ACPU, IFC)  = MAILBOX_QUEUE_BOTTOM_ADDR(CCPU, ACPU, MSG),
    MAILBOX_QUEUE_ADDR(ACPU, CCPU, IFC)  = MAILBOX_QUEUE_BOTTOM_ADDR(CCPU, ACPU, IFC),

    MAILBOX_QUEUE_ADDR(CCPU, MCU, IFC)   = MAILBOX_QUEUE_BOTTOM_ADDR(ACPU, CCPU, IFC),
    MAILBOX_QUEUE_ADDR(MCU, CCPU, IFC)   = MAILBOX_QUEUE_BOTTOM_ADDR(CCPU, MCU, IFC),
    MAILBOX_QUEUE_ADDR(ACPU, MCU, IFC)   = MAILBOX_QUEUE_BOTTOM_ADDR(MCU, CCPU, IFC),
    MAILBOX_QUEUE_ADDR(MCU, ACPU, IFC)   = MAILBOX_QUEUE_BOTTOM_ADDR(ACPU, MCU, IFC),

    MAILBOX_QUEUE_ADDR(BBE16, HIFI, MSG) = MAILBOX_QUEUE_BOTTOM_ADDR(MCU, ACPU, IFC),
    MAILBOX_QUEUE_ADDR(HIFI, BBE16, MSG) = MAILBOX_QUEUE_BOTTOM_ADDR(BBE16, HIFI, MSG),

    MAILBOX_MEMORY_BOTTOM_ADDR           = MAILBOX_QUEUE_BOTTOM_ADDR(HIFI, BBE16, MSG)
};

/*共享内存中的保护字定义*/
#define MAILBOX_PROTECT1                (0x55AA55AA)    /* 邮箱保护字1，用于邮箱头及邮箱, 同时表示邮箱刚初始化没有接收过数据*/
#define MAILBOX_PROTECT2                (0x5A5A5A5A)    /* 邮箱保护字2，用于邮箱头及邮箱 */
#define MAILBOX_PROTECT_LEN             (sizeof(int))  /* 邮箱保护字长度，单位byte，邮箱头及邮箱头、尾均有两个这样的保护字 */
#define MAILBOX_MSGHEAD_NUMBER          (0xA5A5A5A5)    /* 跨核消息消息分隔字 */

#define MAILBOX_DATA_BASE_PROTECT_NUM         (2)    /* 邮箱通道共享内存数据区以首地址开始的保护字个数*/
#define MAILBOX_DATA_TAIL_PROTECT_NUM         (2)    /* 邮箱通道共享内存数据区以尾地址结束的保护字个数*/

/* 邮箱通道共享内存数据区长度中包含的保护字的个数，包括首地址开始的2个保护字，和末地址结束的2个保护字*/
#define MAILBOX_DATA_LEN_PROTECT_NUM          (MAILBOX_DATA_BASE_PROTECT_NUM + MAILBOX_DATA_TAIL_PROTECT_NUM)


/* hifi邮箱地址信息保护字 */
#define HIFI_MB_ADDR_PROTECT            (0x5a5a5a5a)

/*****************************************************************************
  3 枚举定义
*****************************************************************************/

/*****************************************************************************
  定义邮箱核与核之间的IPC中断号
*****************************************************************************/
#define MAILBOX_IPC_INT_NUM(src, dst, channel) \
    MAILBOX_IPC_INT_##src##2##dst##_##channel
enum IPC_MAILBOX_INT_ENUM
{
#if 0
    /* 以下各枚举项按规则生成, 形如: MAILBOX_IPC_INT_CCPU2MCU_DEFAULT */
    MAILBOX_IPC_INT_NUM(CCPU, MCU, MSG)  = IPC_MCU_INT_SRC_CCPU_MSG,
    MAILBOX_IPC_INT_NUM(MCU, CCPU, MSG)  = IPC_CCPU_INT_SRC_MCU_MSG,

    MAILBOX_IPC_INT_NUM(CCPU, HIFI, MSG) = IPC_HIFI_INT_SRC_CCPU_MSG,
    MAILBOX_IPC_INT_NUM(HIFI, CCPU, MSG) = IPC_CCPU_INT_SRC_HIFI_MSG,

    MAILBOX_IPC_INT_NUM(ACPU, MCU, MSG)  = IPC_MCU_INT_SRC_ACPU_MSG,
    MAILBOX_IPC_INT_NUM(MCU, ACPU, MSG)  = IPC_ACPU_INT_SRC_MCU_MSG,

    MAILBOX_IPC_INT_NUM(ACPU, HIFI, MSG) = IPC_HIFI_INT_SRC_ACPU_MSG,
    MAILBOX_IPC_INT_NUM(HIFI, ACPU, MSG) = IPC_ACPU_INT_SRC_HIFI_MSG,

    MAILBOX_IPC_INT_NUM(HIFI, MCU, MSG)  = IPC_MCU_INT_SRC_HIFI_MSG,
    MAILBOX_IPC_INT_NUM(MCU, HIFI, MSG)  = IPC_HIFI_INT_SRC_MCU_MSG,

    MAILBOX_IPC_INT_NUM(CCPU, ACPU, MSG)    = IPC_ACPU_INT_SRC_CCPU_MSG,
    MAILBOX_IPC_INT_NUM(ACPU, CCPU, MSG)    = IPC_CCPU_INT_SRC_ACPU_MSG,

    MAILBOX_IPC_INT_NUM(CCPU, ACPU, IFC)    = IPC_ACPU_INT_SRC_CCPU_IFC,
    MAILBOX_IPC_INT_NUM(ACPU, CCPU, IFC)    = IPC_CCPU_INT_SRC_ACPU_IFC,

    MAILBOX_IPC_INT_NUM(CCPU, MCU, IFC)    = IPC_MCU_INT_SRC_CCPU_IFC,
    MAILBOX_IPC_INT_NUM(MCU, CCPU, IFC)    = IPC_CCPU_INT_SRC_MCU_IFC,

    MAILBOX_IPC_INT_NUM(ACPU, MCU, IFC)    = IPC_MCU_INT_SRC_ACPU_IFC,
    MAILBOX_IPC_INT_NUM(MCU, ACPU, IFC)    = IPC_ACPU_INT_SRC_MCU_IFC,

    MAILBOX_IPC_INT_NUM(BBE16, HIFI, MSG) = IPC_HIFI_INT_SRC_BBE_MSG,
    MAILBOX_IPC_INT_NUM(HIFI, BBE16, MSG) = IPC_BBE16_INT_SRC_HIFI_MSG

#else
    MAILBOX_IPC_INT_NUM(CCPU, HIFI, MSG) = IPC_HIFI_INT_SRC_CCPU_MSG,
    MAILBOX_IPC_INT_NUM(HIFI, CCPU, MSG) = IPC_CCPU_INT_SRC_HIFI_MSG,

    MAILBOX_IPC_INT_NUM(ACPU, HIFI, MSG) = IPC_HIFI_INT_SRC_ACPU_MSG,
    MAILBOX_IPC_INT_NUM(HIFI, ACPU, MSG) = IPC_ACPU_INT_SRC_HIFI_MSG,
#endif
};

/* 各邮箱数据单个邮件最大长度定义 */
#define MAILBOX_MAILSIZE_MAX(src, dst, channel) \
    MAILBOX_MAILSIZE_MAX_##src##2##dst##_##channel
enum MAILBOX_MAILSIZE_MAX_ENUM
{
    /* 以下各枚举项按规则生成, 形如: MAILBOX_MAILSIZE_MAX_MCU2ACPU_DEFAULT */
    MAILBOX_MAILSIZE_MAX(MCU,  ACPU ,MSG)  = MAILBOX_QUEUE_SIZE(MCU,  ACPU ,MSG)/4, //DOTO:具体值需要分析
    MAILBOX_MAILSIZE_MAX(ACPU, MCU  ,MSG)  = MAILBOX_QUEUE_SIZE(ACPU, MCU  ,MSG)/4, //DOTO:具体值需要分析
    MAILBOX_MAILSIZE_MAX(ACPU, HIFI ,MSG)  = MAILBOX_QUEUE_SIZE(ACPU ,HIFI ,MSG)/4, //DOTO:具体值需要分析
    MAILBOX_MAILSIZE_MAX(HIFI, ACPU ,MSG)  = MAILBOX_QUEUE_SIZE(HIFI ,ACPU ,MSG)/4, //DOTO:具体值需要分析
    MAILBOX_MAILSIZE_MAX(MCU , CCPU ,MSG)  = MAILBOX_QUEUE_SIZE(MCU  ,CCPU ,MSG)/4,//DOTO:具体值需要分析
    MAILBOX_MAILSIZE_MAX(CCPU, MCU  ,MSG)  = MAILBOX_QUEUE_SIZE(CCPU ,MCU  ,MSG)/4,//DOTO:具体值需要分析
    MAILBOX_MAILSIZE_MAX(CCPU, HIFI ,MSG)  = MAILBOX_QUEUE_SIZE(CCPU ,HIFI ,MSG)/4,//DOTO:具体值需要分析
    MAILBOX_MAILSIZE_MAX(HIFI, CCPU ,MSG)  = MAILBOX_QUEUE_SIZE(HIFI ,CCPU ,MSG)/4,//DOTO:具体值需要分析

    MAILBOX_MAILSIZE_MAX(CCPU, ACPU ,MSG)  = MAILBOX_QUEUE_SIZE(CCPU, ACPU ,MSG)/4,//DOTO:具体值需要分析
    MAILBOX_MAILSIZE_MAX(ACPU, CCPU ,MSG)  = MAILBOX_QUEUE_SIZE(ACPU, CCPU ,MSG)/4,//DOTO:具体值需要分析
    MAILBOX_MAILSIZE_MAX(CCPU, ACPU ,IFC)  = MAILBOX_QUEUE_SIZE(CCPU, ACPU ,IFC)/4,//DOTO:具体值需要分析
    MAILBOX_MAILSIZE_MAX(ACPU, CCPU ,IFC)  = MAILBOX_QUEUE_SIZE(ACPU, CCPU ,IFC)/4,//DOTO:具体值需要分析

    MAILBOX_MAILSIZE_MAX(CCPU, MCU ,IFC)  = MAILBOX_QUEUE_SIZE(CCPU, MCU ,IFC)/4,//DOTO:具体值需要分析
    MAILBOX_MAILSIZE_MAX(MCU, CCPU ,IFC)  = MAILBOX_QUEUE_SIZE(MCU, CCPU ,IFC)/4,//DOTO:具体值需要分析

    MAILBOX_MAILSIZE_MAX(ACPU, MCU ,IFC)  = MAILBOX_QUEUE_SIZE(ACPU, MCU ,IFC)/4,//DOTO:具体值需要分析
    MAILBOX_MAILSIZE_MAX(MCU, ACPU ,IFC)  = MAILBOX_QUEUE_SIZE(MCU, ACPU ,IFC)/4,//DOTO:具体值需要分析

    MAILBOX_MAILSIZE_MAX(BBE16, HIFI ,MSG) = MAILBOX_QUEUE_SIZE(BBE16 ,HIFI ,MSG)/4,//DOTO:具体值需要分析
    MAILBOX_MAILSIZE_MAX(HIFI, BBE16 ,MSG) = MAILBOX_QUEUE_SIZE(HIFI ,BBE16 ,MSG)/4,//DOTO:具体值需要分析
};

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
 实 体 名  : struct mb_mail
 功能描述  : 核间邮件头
*****************************************************************************/
typedef struct mb_mail
{
    unsigned int       ulPartition;    /*消息分隔字 0xA5A5A5A5*/
    unsigned int       ulWriteSlice;   /*消息写入系统时间信息 */
    unsigned int       ulReadSlice;    /*消息读出系统时间信息 */
    unsigned int       ulSeqNum;       /*消息序列号 */
    unsigned int       ulPriority;     /*消息优先级：紧急、普通, 废弃*/
    unsigned int       ulMailCode;     /*邮编*/
    unsigned int       ausReserve[2];  /*保留*/
    unsigned int       ulMsgLength;    /*自ulMsgLength字段(不含本身)往后的消息长度*/
} MAILBOX_MSG_HEADER;

/************************************************************************
 结构名    : IPC_MAILBOX_QUEUE_STRU
 结构说明  : 核间邮箱缓存
 ************************************************************************/
/* 邮箱结构示意:
typedef struct
{
    unsigned int      ulProtectWord1;     //保护字 0x55aa55aa
    unsigned int      ulProtectWord2;     //保护字 0a5a5a5a5a
    unsigned int      aulMsgQueue[队列长度-4];//环形队列存放若干封邮件
    unsigned int      ulProtectWord3;     //保护字 0x55aa55aa
    unsigned int      ulProtectWord4;     //保护字 0x5a5a5a5a
} MAILBOX_QUEUE_STRU;
*/
enum
{
	HI_SYSCTRL_BASE_ADDR_ID = 0,
	HI_SOCP_REGBASE_ADDR_ID,
	SOC_IPC_S_BASE_ADDR_ID,
	SOC_AP_EDMAC_BASE_ADDR_ID,
	SOC_UART3_BASE_ADDR_ID,
	SOC_Watchdog1_BASE_ADDR_ID,
	SOC_AO_SCTRL_SC_SLICER_COUNT0_ADDR_0_ID,
	SOC_HIFI_Timer00_BASE_ADDR_ID,
	SOC_HIFI_Timer08_BASE_ADDR_ID,
	DDR_HIFI_ADDR_ID,
	SOC_BBP_TDS_BASE_ADDR_ID,
};

typedef struct
{
	unsigned int enID;				/*地址枚举值*/
	unsigned int uwAddress; 			/*地址物理值*/
} SOC_HIFI_ADDR_ITEM_STRU;

typedef struct
{
	unsigned int uwProtectWord; 				/*0x5a5a5a5a*/
	SOC_HIFI_ADDR_ITEM_STRU 	astSocAddr[64]; /*地址项定义*/
} SOC_HIFI_ADDR_SHARE_STRU;


typedef struct
{
	unsigned int uwProtectWord;
	unsigned int uwAddrPhy;
	unsigned int uwSize;
	unsigned int uwReserve;

}MODEM_HIFI_NV_SHARE_STRU;

typedef struct
{
    unsigned int uwProtectWord;                /*0x5a5a5a5a*/
    unsigned int uwHifi2AarmMailBoxLen;        /* hifi到Aarm跨核邮箱长度 */
    unsigned int uwAarm2HifiMailBoxLen;        /* Aarm到hifi跨核邮箱长度 */
    unsigned int uwHifiAarmHeadAddr;
    unsigned int uwHifiAarmBodyAddr;
    unsigned int uwAarmHifiHeadAddr;
    unsigned int uwAarmHifiBodyAddr;
    unsigned int uwReserved[2];
}AARM_HIFI_MAILBOX_STRU;

/*****************************************************************************
 结构名    : CARM_HIFI_DYN_ADDR_SHARE_STRU
 协议表格  :
 ASN.1描述 :
 结构说明  :CARM和HIFI的共享地址，OAM需要赋值并拷贝至Hifi共享数据中的相应结构体
*****************************************************************************/
typedef struct
{
    unsigned int uwProtectWord;                /*0x5a5a5a5a*/
    unsigned int uwHifi2CarmMailBoxLen;        /* hifi到Carm跨核邮箱长度 */
    unsigned int uwCarm2HifiMailBoxLen;        /* Carm到hifi跨核邮箱长度 */
    unsigned int uwHifiCarmHeadAddr;
    unsigned int uwHifiCarmBodyAddr;
    unsigned int uwCarmHifiHeadAddr;
    unsigned int uwCarmHifiBodyAddr;
    unsigned int uwReserved[2];
}CARM_HIFI_MAILBOX_STRU;

typedef struct
{
    unsigned int uwProtectWord;
    unsigned int uwHifi2CarmIccChannelLen;
    unsigned int uwHifi2TphyIccChannelLen;
    unsigned int uwHifi2CarmIccChannelAddr;
    unsigned int uwCarm2HifiIccChannelAddr;
    unsigned int uwHifi2TphyIccChannelAddr;
    unsigned int uwTphy2HifiIccChannelAddr;
    unsigned int uwReserved[2];
}CARM_HIFI_ICC_STRU;

/*****************************************************************************
 结构名    : AARM_HIFI_DYN_ADDR_SHARE_STRU
 协议表格  :
 ASN.1描述 :
 结构说明  :AARM和HIFI的共享地址，OAM需要赋值并拷贝至Hifi共享数据中的相应结构体
*****************************************************************************/
typedef struct
{
	unsigned int uwProtectWord; 		   /*0x5a5a5a5a*/
	CARM_HIFI_ICC_STRU stCarmHifiMB;	/*CARM和HIFI的邮箱共享区定义*/
	AARM_HIFI_MAILBOX_STRU stAarmHifiMB;	/*AARM和HIFI的邮箱共享区定义*/
	unsigned int uwNvBaseAddrPhy;		   /*DDR上NV备份区首地址的物理地址*/
	unsigned int uwNvBaseAddrVirt;		   /*DDR上NV备份区首地址的ARM虚拟地址*/
	MODEM_HIFI_NV_SHARE_STRU stNVShare;  /*Modem NV共享区定义*/
	SOC_HIFI_ADDR_SHARE_STRU	stSoCShare;  /*SoC共享区定义*/
	unsigned int uwReserved[2];
}CARM_HIFI_DYN_ADDR_SHARE_STRU;




#if 0

typedef struct
{
    unsigned int uwProtectWord;                /*0x5a5a5a5a*/
    unsigned int uwHifi2AarmMailBoxLen;        /* hifi到Aarm跨核邮箱长度 */
    unsigned int uwAarm2HifiMailBoxLen;        /* Aarm到hifi跨核邮箱长度 */
    unsigned int uwHifiAarmHeadAddr;
    unsigned int uwHifiAarmBodyAddr;
    unsigned int uwAarmHifiHeadAddr;
    unsigned int uwAarmHifiBodyAddr;
    unsigned int uwReserved[2];
}AARM_HIFI_MAILBOX_STRU;

/*****************************************************************************
 结构名    : CARM_HIFI_DYN_ADDR_SHARE_STRU
 协议表格  :
 ASN.1描述 :
 结构说明  :CARM和HIFI的共享地址，OAM需要赋值并拷贝至Hifi共享数据中的相应结构体
*****************************************************************************/
typedef struct
{
    unsigned int uwProtectWord;                /*0x5a5a5a5a*/
    unsigned int uwHifi2CarmMailBoxLen;        /* hifi到Carm跨核邮箱长度 */
    unsigned int uwCarm2HifiMailBoxLen;        /* Carm到hifi跨核邮箱长度 */
    unsigned int uwHifiCarmHeadAddr;
    unsigned int uwHifiCarmBodyAddr;
    unsigned int uwCarmHifiHeadAddr;
    unsigned int uwCarmHifiBodyAddr;
    unsigned int uwReserved[2];
}CARM_HIFI_MAILBOX_STRU;

/*****************************************************************************
 结构名    : CARM_HIFI_DYN_ADDR_SHARE_STRU
 协议表格  :
 ASN.1描述 :
 结构说明  :CARM和HIFI的共享地址，OAM需要赋值并拷贝至Hifi共享数据中的相应结构体
*****************************************************************************/
typedef struct
{
    unsigned int uwProtectWord;            /*0x5a5a5a5a*/
    CARM_HIFI_MAILBOX_STRU stCarmHifiMB;    /*CARM和HIFI的邮箱共享区定义*/
    AARM_HIFI_MAILBOX_STRU stAarmHifiMB;    /*AARM和HIFI的邮箱共享区定义*/
    unsigned int uwNvBaseAddrPhy;          /*DDR上NV备份区首地址的物理地址*/
    unsigned int uwNvBaseAddrVirt;         /*DDR上NV备份区首地址的ARM虚拟地址*/
    unsigned int uwReserved[2];
}CARM_HIFI_DYN_ADDR_SHARE_STRU;
#endif
/*****************************************************************************
  7 UNION定义
*****************************************************************************/


/*****************************************************************************
  8 OTHERS定义
*****************************************************************************/


/*****************************************************************************
  9 全局变量声明
*****************************************************************************/

/*****************************************************************************
  10 函数声明
*****************************************************************************/

/*****************************************************************************
 函 数 名  : mb_msg_cb
 功能描述  : 邮箱数据接收处理回调函数, 目标邮箱有邮件数据到达时被调用
             邮箱用户实现并通过MAILBOX_RegisterRecvFunc注册
 输入参数  : UserHandle -- 用户句柄
             MailHandle -- 邮箱句柄
             MailLen    -- 本次到达邮件数据长度
 输出参数  : 无
 返 回 值  : 无
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2012年9月24日
    作    者   : 莫南 00176101
    修改内容   : 新生成函数

*****************************************************************************/
typedef void (*mb_msg_cb)(
                void                   *user_handle,
                void                   *mail_handle,
                unsigned int           mail_len);

/*****************************************************************************
 函 数 名  : DRV_MAILBOX_SENDMAIL
 功能描述  : 邮箱用户发送邮件数据
 输入参数  : MailCode   -- 邮编, 指定邮件发送目标
             pData      -- 指向邮件数据的指针
             Length     -- 待发送数据长度, 单位byte
 输出参数  : 无
 返 回 值  : 正确:MAILBOX_OK / 错误:MAILBOX_ERRO或者其他错误码
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2012年9月28日
    作    者   : 莫南 00176101
    修改内容   : 新生成函数

*****************************************************************************/
unsigned int DRV_MAILBOX_SENDMAIL(
                unsigned int           MailCode,
                void                   *pData,
                unsigned int           Length);

/*****************************************************************************
 函 数 名  : DRV_MAILBOX_REGISTERRECVFUNC
 功能描述  : 注册邮件数据接收函数
 输入参数  : MailCode   -- 数据接收函数处理的对象邮编
             pFun       -- 邮件数据接收处理函数指针
             UserHandle -- 用户定义句柄, 数据接收函数被调用时会作为入参, 无则填空
 输出参数  : 无
 返 回 值  : 正确:MAILBOX_OK / 错误:MAILBOX_ERRO或者其他错误码
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2012年9月29日
    作    者   : 莫南 00176101
    修改内容   : 新生成函数

*****************************************************************************/
unsigned int DRV_MAILBOX_REGISTERRECVFUNC(
                unsigned int           MailCode,
                mb_msg_cb               pFun,
                void                   *UserHandle);

/*****************************************************************************
 函 数 名  : DRV_MAILBOX_READMAILDATA
 功能描述  : 邮箱用户在数据接收回调函数中调用, 从邮箱中读取一封最先到达的邮件
 输入参数  : MailHandle -- 邮箱句柄, 数据接收回调函数入参
             pData      -- 保存待读出数据的缓存地址
             *pSize     -- 缓存长度, 单位byte, 需要大于待读取邮件长度
 输出参数  : *pSize     -- 实际读取长度, 单位byte
 返 回 值  : 正确:MAILBOX_OK / 错误:MAILBOX_ERRO或者其他错误码
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2012年10月26日
    作    者   : 莫南 00176101
    修改内容   : 新生成函数

*****************************************************************************/
unsigned int DRV_MAILBOX_READMAILDATA(
                void                   *MailHandle,
                unsigned char          *pData,
                unsigned int          *pSize);

/*****************************************************************************
 函 数 名  : drv_hifi_fill_mb_info
 功能描述  : 邮箱信息设置接口
 输入参数  : addr 段信息地址(由HIFI加载模块传入)
 输出参数  :
 返 回 值  : void
 调用函数  : V9R1中在fastboot中调用，V7R2中与DSP一起加载调用
 被调函数  :

 修改历史      :
  1.日    期   : 2013年11月4日
    作    者   : 崔军强 64416
    修改内容   : 新生成函数

*****************************************************************************/
void drv_hifi_fill_mb_info(unsigned int addr);
#endif

#ifdef __cplusplus
#if __cplusplus
}
#endif
#endif

#endif /* end of drv_mailbox_cfg.h */

