/******************************************************************************

                  版权所有 (C), 2001-2011, 华为技术有限公司

 ******************************************************************************
  文 件 名   : lte_sleepFlow.h
  版 本 号   : 初稿
  作    者   : fuxin 00221597
  生成日期   : 2005年3月7日
  最近修改   :
  功能描述   : SleepFlow.c 的头文件
  函数列表   :
  修改历史   :

******************************************************************************/
#ifndef __LTE_SLEEPFLOW_H__
#define __LTE_SLEEPFLOW_H__


#if __cplusplus
extern "C"
{
#endif

#include "product_config.h"


#if defined (CHIP_BB_HI6210)
#define MSP_IN_V9R1
#else
#undef MSP_IN_V9R1
#endif

#include "mdrv.h"
#include "vos.h"
#include <VosPidDef.h>
#include <RfNvId.h>
#include <PhyNvDefine.h>
#include <msp_diag.h>
#include <TLPhyInterface.h>
#include <msp_nv_id.h>
#include <msp_nv_def.h>
#include <mdrv_dsp.h>
#ifndef MSP_IN_V9R1
#include <drv_nv_id.h>
#include <drv_nv_def.h>
#include <soc_memmap_comm.h>
#include <hi_bbp_ltedrx.h>
#else
#include "NVIM_Interface.h"
#include <NvIdList.h>
#endif

/* 目前版本不会超过4通道 */
#define MSP_SLEEP_CHAN_NUM          3

/* 目前版本不会超过2TCXO */
#define MSP_SLEEP_TCXO_NUM          2

#define MSP_PWR_SYSTEM_RUN          (1<<0)      /*当前DSP状态为RUN*/
#define MSP_PWR_HALT_INT            (1<<1)      /*标志当前有halt中断到来，且对此中断还没有处理完成*/
#define MSP_PWR_FORCE_AWAKE         (1<<2)      /*标志当前有强制唤醒请求*/
#define MSP_PWR_WAIT_RESUMER        (1<<3)      /*标志当前已经完成唤醒操作，等待DSP恢复完成*/
#define MSP_PWR_WAKEUP              (1<<4)      /*标志是否有wakeup中断响应*/

/*用于可维可测*/
#define MSP_CREATE_TASK_SEM_FAIL    (1<<10)      /*标志初始化时初始化睡眠任务的信号量失败*/
#define MSP_CREATE_TASK_FAIL        (1<<11)      /*标志初始化时创建睡眠任务失败*/
#define MSP_INT_CONNECT_FAIL        (1<<12)      /*标志初始化时挂接中断失败*/
#define MSP_INT_ENABLE_FAIL         (1<<13)      /*标志初始化时使能中断失败*/
#define MSP_READ_NV_FAIL            (1<<14)      /*标志初始化时读取NV失败*/
#define MSP_DFS_REQUEST_FAIL        (1<<15)      /*标志初始化时申请DFS调频ID失败*/
#define MSP_DFS_HALT_UPDATE_FAIL    (1<<16)      /*标志在Halt中断中投票DFS失败*/
#define MSP_DFS_RUN_UPDATE_FAIL     (1<<17)       /*标志在RUN DSP时投票DFS失败*/
#define MSP_DFS_HW_UPDATE_FAIL      (1<<18)       /*标志在PS调用的接口中投票DFS失败*/
#define MSP_REPEAT_HALT_ERROR       (1<<19)       /*记录DSP重复发出halt中断*/
#define MSP_CREATE_TCXO0_SEM_FAIL   (1<<20)      /*标志初始化时初始化睡眠任务的信号量失败*/
#define MSP_CREATE_TCXO1_SEM_FAIL   (1<<21)      /*标志初始化时初始化睡眠任务的信号量失败*/


#define MSP_SLEEP_TASK_PRI          (2)         /*任务优先级*/
#define MSP_EXC_TASK_PRI            (63)       /*任务优先级*/
#define WAIT_FOR_EVER               (0)
#define SLEEP_RECORD_NUM            (100)
#define MSP_SLEEP_ERROR             (-1)

/* sleep模块消息ID */
#define ID_MSG_SLEEP_WAKEUP_SLICE_MNTN      0xf000f001

/*TL物理层进入低功耗的标志*/
#define MSP_TLPHY_IN_LOW_POWER        (0x5a5a5a5a)

typedef struct
{
    VOS_MSG_HEADER                     /*VOS头 */
    VOS_UINT32      ulMsgId;
    
    VOS_UINT32      ulHalt;
    VOS_UINT32      ulSleepStart;
    VOS_UINT32      ulSleepEnd;
    VOS_UINT32      ulWakeup;
    VOS_UINT32      ulForceAwake;
    VOS_UINT32      ulWakeupStart;
    VOS_UINT32      ulAwake_CB_0;
    VOS_UINT32      ulAwake_CB_1;
    VOS_UINT32      ulFORCE_AWAKE_INNER_0;
    VOS_UINT32      ulHWPOWERUP_0;
    VOS_UINT32      ulHWPOWERUP_1;
    VOS_UINT32      ulHWPOWERUP_2;
    VOS_UINT32      ulHWPOWERUP_3;
    VOS_UINT32      ulHWPOWERUP_4;
    VOS_UINT32      ulHWPOWERUP_5;
    VOS_UINT32      ulHWPOWERUP_6;
    VOS_UINT32      ulHWPOWERUP_7;
    VOS_UINT32      ulHWPOWERUP_8;
    VOS_UINT32      ulHWPOWERUP_9;
    VOS_UINT32      ulHWPOWERUP_MAX;
    VOS_UINT32      ulFORCE_AWAKE_INNER_1;
    VOS_UINT32      ulWakeupEnd;
    VOS_UINT32      ulResume;
}MSP_SLEEP_MNTN_MSG_STRU;

#ifndef MSP_IN_V9R1
/* 调试用的共享内存
#define DEBUG_TIMESTAMP_ADDR        (SHM_TIMESTAMP_ADDR + 0x200)
#define DEBUG_FOR_DSP_ADDR          (SHM_TIMESTAMP_ADDR + 0x8)
*/
#else

typedef struct
{
    VOS_UINT8 ucABBSwitch; /*对应模式使用的ABB物理通道，0 通道0, 1: 通道1, 2: 同时使用两个通道*/
    VOS_UINT8 ucRFSwitch;  /*对应模式使用的RF物理通道，0 通道0, 1: 通道1, 2: 同时使用两个通道*/
    VOS_UINT8 ucTCXOSwitch; /*对应模式使用的TCXO ID 0 TCXO0, 1: TCXO1*/
    VOS_UINT8 reserve;
}NV_TLMODE_BASIC_PARA_STRU;

typedef struct
{
    NV_TLMODE_BASIC_PARA_STRU stModeBasicParam[2];/*下标为0:LTE, 1:TDS*/
}NV_TLMODE_CHAN_PARA_STRU;

/* drx delay flag */
typedef struct
{
    VOS_UINT8         lpm3_flag;         /* 0x11 代表lpm3 */
    VOS_UINT8         lpm3_0;            /* 1打开delay,其他关闭delay */
    VOS_UINT8         lpm3_1;
    VOS_UINT8         lpm3_2;
    VOS_UINT8         lpm3_3;
    VOS_UINT8         lpm3_4;
    VOS_UINT8         lpm3_5;
    VOS_UINT8         drv_flag;          /* 0x22 代表drv */
    VOS_UINT8         drv_0;             /* 1打开delay,其他关闭delay */
    VOS_UINT8         drv_1;
    VOS_UINT8         drv_2;
    VOS_UINT8         drv_3;
    VOS_UINT8         drv_4;
    VOS_UINT8         drv_5;
    VOS_UINT8         msp_flag;          /* 0x33 代表msp */
    VOS_UINT8         msp_0;             /* 1打开delay,其他关闭delay */
    VOS_UINT8         msp_1;
    VOS_UINT8         msp_2;
    VOS_UINT8         msp_3;
    VOS_UINT8         msp_4;
}DRV_DRX_DELAY_STRU;

#endif
/*可维可测内存分配*/
/*当前的状态机*/
#define MSP_EXC_PWR_STATUS_OFFSET                   ((VOS_UINT)(g_msp_pwrctrl.dump_base))
#define MSP_EXC_PWR_STATUS_SIZE                     (0x4)
/*DSP深睡浅睡标志*/
#define MSP_EXC_SLEEP_FLAG_OFFSET                   (MSP_EXC_PWR_STATUS_OFFSET + MSP_EXC_PWR_STATUS_SIZE)
#define MSP_EXC_SLEEP_FLAG_SIZE                     (0x4)

#define MSP_EXC_FORBID_DSP_SLEEP_OFFSET             (MSP_EXC_SLEEP_FLAG_OFFSET + MSP_EXC_SLEEP_FLAG_SIZE)
#define MSP_EXC_FORBID_DSP_SLEEP_SIZE               (0x4)

#define MSP_EXC_DSP_STATE_OFFSET                    (MSP_EXC_FORBID_DSP_SLEEP_OFFSET + MSP_EXC_FORBID_DSP_SLEEP_SIZE)
#define MSP_EXC_DSP_STATE_SIZE                      (0x4)
/*时间队列记录*/
#define MSP_EXC_RECORED_TIME_OFFSET                 (MSP_EXC_DSP_STATE_OFFSET + MSP_EXC_DSP_STATE_SIZE)
#define MSP_EXC_RECORED_TIME_SIZE                   (MSP_EXC_STATE_SLICE_OFFSET - MSP_EXC_RECORED_TIME_OFFSET)
/*状态记录*/
#define MSP_EXC_STATE_SLICE_OFFSET                  (MSP_EXC_END_OFFSET - MSP_EXC_STATE_SLICE_SIZE)
#define MSP_EXC_STATE_SLICE_SIZE                    (DRX_STATE_BUTT*(sizeof(SLEEP_RECORD_STRU)))

#define MSP_EXC_END_OFFSET                          (MSP_EXC_PWR_STATUS_OFFSET + (g_msp_pwrctrl.dump_len))


typedef struct
{
    VOS_UINT32 ulTime;
    char acType[16];
} SLEEP_TIME_STRU;


typedef struct
{
    VOS_UINT32  ulCount;
    SLEEP_TIME_STRU astRecord[SLEEP_RECORD_NUM];
} TLSLEEP_RECORD_STRU;

/*正常流程记录*/
typedef enum tagDRX_STATE_SLICE
{
    DRX_HALT_INT = 0,               /* 记录DRX halt中断*/
    DRX_SLEEP_TASK = 1,             /* 记录DRX 进入睡眠任务开始执行睡眠操作 */
    SLEEP_TASK_NOT_NEED_DEAL = 2,   /* 记录同时收到睡眠唤醒请求，Sleep任务不需再处理 ，可以直接恢复*/
    DSP_DEEP_SLEEP_COUNT = 3,       /* DSP深睡记录*/
    DSP_LIGHT_SLEEP_COUNT =4,       /* DSP浅睡记录*/
    STORE_DSP_TCM_FAIL = 5,         /* 记录启动EDMA通道保存DSP TCM失败 */
    SLEEP_VOTE_UNLOCK = 6,          /* 记录投票睡眠的次数*/
    DRX_INVALID_WAKEUP_INT = 7,     /* 记录无效的唤醒中断 */
    DRX_WAKEUP_INT = 8,             /* 记录DRX正常wakeup唤醒中断 */
    RESTORE_DSP_TCM_FAIL = 9,       /* 记录启动EDMA通道恢复DSP TCM失败 */
    DRX_FORCE_AWAKE_API = 10,       /* 记录DRX强制唤醒流程接口调用 */
    DRX_FORCE_AWAKE_NOT_DEAL = 11,  /* 记录已经有唤醒操作不需要响应唤醒操作*/
    DRX_FORCE_AWAKE_RUN_RETURN = 12,/* 记录收到强制唤醒时DSP已经RUN*/
    DRX_FAIL_WAIT_TCXO_SEM = 13,    /* 等待TCXO稳定超过10ms*/
    RESUME_NOTIFY_MAILBOX = 14,     /* 记录RSUME中断中通知邮箱 DSP已经强制唤醒*/
    DRX_RESUME_INT = 15,            /* 记录DRX 唤醒恢复完成中断 */
    DRX_CHECK_DSP_STATUS = 16,      /* 记录DRX中外界查询当前DSP的状态的接口被调用 */
    DSP_SLEEP_FLAG_ERROR = 17,      /* 记录DSP深睡浅睡标志错误*/
    DRX_HALT_RESUME_CONFLICT = 18,  /* 记录DSP睡眠唤醒中断同时触发的情形错误*/

    DRX_SLAVE_WAKE_INT,             /* 记录LTE作为从模收到主模唤醒中断*/
    
    DRX_SLEEP_START,                /* 记录开始执行睡眠的时间 */
    DRX_SLEEP_END,                  /* 记录结束执行睡眠的时间*/
    
    DRX_WAKEUP_START,               /* 记录开始执行唤醒的时间*/
    DRX_WAKEUP_END,                 /* 记录结束执行唤醒的时间*/

    DRX_MASTER_WAKE_REQ_INT = 24,   /* TL作为主模，唤醒从模请求次数*/
    DRX_MASTER_WAKE_GSM = 25,       /* TL作为主模，唤醒GSM从模 */
    DRX_MASTER_WAKE_WCDMA = 26,     /* TL作为主模，唤醒WCDMA从模 */
    DRX_MASTER_WAKE_LTE = 27,       
    DRX_MASTER_WAKE_TDS = 28,
    DRX_MASTER_WAKE_CDMA_1X = 29,   /* TL作为主模，唤醒1X从模 */
    DRX_MASTER_WAKE_CDMA_HRPD = 30, /* TL作为主模，唤醒HRPD从模 */

    DRX_STATE_BUTT = 31
}DRX_STATE_SLICE;

typedef struct
{
    VOS_UINT32 ulCount;              /* 记录发生的次数 */
    VOS_UINT32 ulSlice;              /* 记录发生的Slice值 */
}SLEEP_RECORD_STRU;

/*****************************************************************************
 结构名    : SLEEP_NV_DRX_RESUME_TIME_STRU
 结构说明  : 流程记录扩展单元
*****************************************************************************/
typedef struct
{
    VOS_UINT32                          ulAbbPwrRsmTime;                        /* ABB AD/DA数字部分电源稳定时间,单位us */
    VOS_UINT32                          ulRfPwrRsmTime;                         /* RF 模拟域电源稳定时间,单位us */
    VOS_UINT32                          ulAntSwitchPwrRsmTime;                  /* 天线开关电源稳定时间,单位us */
    VOS_UINT32                          ulAbbWpllRsmTime;                       /* ABB WPLL稳定时间,单位us */
    VOS_UINT32                          ulAbbGpllRsmTime;                       /* ABB GPLL稳定时间 ,单位us*/
    VOS_UINT32                          ulBbpPllRsmTime;                        /* SOC BBP PLL稳定时间,单位us */
    VOS_UINT32                          ulReserved1;                            /* 保留字段 */
    VOS_UINT32                          ulSysProtectTime;                       /* 系统恢复保护时间 */
    VOS_UINT32                          ulTcxoRsmTime;                          /* TCXO稳定时间,单位us */
    VOS_UINT32                          ulDcxoRsmTime;                          /* DCXO稳定时间,单位us */
    VOS_UINT32                          ulSlowToMcpuRsmTime;                    /* 从SLOW到MCPU上电恢复时间,单位us */
    VOS_UINT32                          ulWphyRsmTime;                          /* W物理层唤醒恢复时间,单位us */
    VOS_UINT32                          ulGphyRsmTime;                          /* G物理层唤醒恢复时间,单位us */
    VOS_UINT32                          ulTaskSwitchTime;                       /* 操作系统任务切换时间,单位us */
    VOS_UINT32                          ulPaPwrRsmTime;                         /* PA电源稳定时间,单位us */
}WG_DRX_RESUME_TIME_STRU;

typedef struct TLMODE_CHANNEL_tag
{
    VOS_UINT16              abb_channel_id;
    VOS_UINT16              rf_channel_id;
    VOS_UINT16              tcxo_id;
    VOS_UINT16              rf_clk_id;
#ifdef CONFIG_PASwitch_V7R5
    VOS_UINT16              pa_switch_id;
    VOS_UINT16              reserved[3];
#else
    VOS_UINT16              reserved[4];
#endif
}TLMODE_CHANNEL_STRU;

typedef struct
{
    VOS_UINT32 ulSlice;              /* 记录发生的Slice值 */
    VOS_UINT32 ulState;              /* 发生的状态 */
}DRX_RECORD_STRU;

typedef struct
{
    VOS_UINT32      maxNum;
    VOS_UINT32      front;
    VOS_UINT32      rear;
    VOS_UINT32      num;
    DRX_RECORD_STRU data[1];
} drx_queue_t;
typedef enum tagDspState
{
    ENUM_DSP_IS_SLEEP = 0,          /*DSP已经投票睡眠*/
    ENUM_DSP_IS_RUN = 1,            /*MSP已经唤醒DSP*/
}DspState;
typedef enum tagPowerUpDownDsp
{
    ENUM_YES_UP_DOWN_DSP = 0,          /*0:进行上下电DSP*/
    ENUM_NO_UP_DOWN_DSP = 1,           /*1:不进行上下电DSP*/
    ENUM_UP_DOWN_DSP_BUTT,
}PowerUpDownDsp;
typedef enum tagVoteSleep
{
    ENUM_YES_VOTE_SLEEP = 0,          /*0:投票进行睡眠*/
    ENUM_NO_VOTE_SLEEP = 1,           /*1:不投票进行睡眠*/
    ENUM_VOTE_SLEEP_BUTT,
}VoteSleep;
typedef enum DSP_HALT_MARK
{
    FIRST_HALT_INT = 0,    /*标志没有过DSP睡眠中断*/
    HAD_HALT_INT = 1,   /*标志有过DSP 睡眠中断*/
    DSP_HALT_BUTT,
}DSP_HALT_MARK_ENUM;


typedef struct
{
    VOS_UINT32 timeOut;                   /*唤醒DSP的超时时间设置,默认为45*/
    VOS_UINT32 timeTaskId;                /*唤醒任务的id*/
    VOS_UINT32 ulReadMark;                /* 标志异常记录里面的值是否被取走了,1:表示有数据没有读走 0:表示数据被完全读走，可以重新写入*/
    VOS_SEM    time_sem;                  /*任务信号量,用于唤醒任务把异常信息写入文件系统*/
    VOS_UINT32 current_count;                  /*记录当前记录了多少次异常信息*/
    VOS_UINT32 ulTime[100];               /* 记录异常的时间信息 */
}DRX_OVERTIME_STRU;

struct msp_power_control
{
    VOS_UINT32                  pwr_status;             /*msp部分的状态信息*/
    VOS_SEM                     task_sem;               /*任务信号量*/
    VOS_SEM                     SleepTcxoSem[2];        /* TCXO稳定信号量 0:对应TCXO0,1 对应TCXO1*/
    VOS_UINT32                  RttIsSleepValue;        /*记录返LSLEEP_RttIsSleep查询时返回的值*/
    VOS_INT32                  	LteIntTimer;        	/*LTE timer int*/
    VOS_UINT32                  LteIntTimerFail;        /*LTE timer int fail cnt*/
    VOS_UINT32                  ForbidDspSleepValue;    /*记录睡眠时查询是否可以睡眠时返回的值*/
    DSP_HALT_MARK_ENUM          DspHaltIntMark;             /*标志是否有过DSP睡眠中断*/
    VOS_UINT32                  task_id;
    VOS_CHAR *                  dump_base;              /*用于可维可测的基地址*/
    VOS_UINT                    dump_len;               /*用于可维可测的长度*/
    DspState *                  dsp_state;               /*用于可维可测的基地址*/
    VOS_UINT32                  print_ctrl;             /*dbug 打印控制*/
    drx_queue_t*                time_queue_record;        /*调试时时间记录*/
    VOS_UINT32                  dbg_time_record[100];        /*调试时时间记录*/
    DRX_OVERTIME_STRU           exc_overtime;           /*记录超时时的时间，用于在mspExcTask里面记录到文件系统*/
    SLEEP_RECORD_STRU*           DrxStateSlice;         /*记录流程中的各个阶段的信息*/
    VOS_UINT32                  DrxStateEnd;            /*DrxStateSlice的结束地址*/
    TLMODE_CHANNEL_STRU         tlmode_channel[2];      /*便于将来支持T/L模分离，0-LTE;1-TDS*/
    NV_TL_DRX_RESUME_TIME_STRU  SleepDrxResumeTime;     /*NV*/
	LPHY_RTT_LPC_MODE_ENUM      dsp_sleep_flag;         /*DSP深睡浅睡标志,1 浅睡 2 深睡*/
    VOS_UINT32                  SleepRecordFlag;        /*开关记录sleepTimeRecord*/
    VOS_UINT32                  DspLowPowerFlag;        /*TL物理层进入低功耗标志，0x5a5a5a5a 已进入低功耗，0 未进入低功耗*/
    TLSLEEP_RECORD_STRU         SleepTimeRecord;        /*记录可维可测信息的结构体，*/
};
struct msp_delay_control
{
    VOS_UINT32            delay_control;                /*每一个bit用来控制一个地方是否delay*/
    VOS_UINT32            delay_ms;                     /*需要delay多少ms*/
};
#define DELAY_CTRL_BEFOR_WAKE               (1<<0)
#define DELAY_CTRL_AFTER_WAKE               (1<<1)
#define DELAY_CTRL_BEFOR_SLEEP              (1<<2)
#define DELAY_CTRL_AFTER_SLEEP              (1<<3)

struct msp_hids_control
{
    VOS_UINT32            print_control;                /*控制是否打印到hids*/
    VOS_UINT32            PrintVErrorNo;                /*print返回的错误码*/
};

typedef enum tagSLEEP_TIME_RECORD
{
    /*睡眠过程*/
    TLSLEEP_DSPHALTISR_0 = 0,

    TLSLEEP_RTTSLEEP_INNER_0,
    TLSLEEP_RTTSLEEP_INNER_1,

    TLSLEEP_HWPOWERDOWN_0,
    TLSLEEP_HWPOWERDOWN_1,
    TLSLEEP_HWPOWERDOWN_2 = 5,
    TLSLEEP_HWPOWERDOWN_3,
    TLSLEEP_HWPOWERDOWN_4,
    TLSLEEP_HWPOWERDOWN_5,
    TLSLEEP_HWPOWERDOWN_6,
    TLSLEEP_HWPOWERDOWN_7 = 10,
    TLSLEEP_HWPOWERDOWN_8,
    TLSLEEP_HWPOWERDOWN_9,
    TLSLEEP_HWPOWERDOWN_MAX,

    TLSLEEP_RTTSLEEP_INNER_2,
    TLSLEEP_RTTSLEEP_INNER_MAX = 15,
    
    TLSLEEP_SLEEP_CB_0,
    TLSLEEP_SLEEP_CB_1,

    /*唤醒过程*/
    TLSLEEP_AWAKEISR_0,
    TLSLEEP_AWAKEISR_1,
    TLSLEEP_AWAKEISR_MAX = 20,

    TLSLEEP_FORCE_AWAKE_INNER_0,

    TLSLEEP_AWAKE_CB_0,
    TLSLEEP_AWAKE_CB_1,

    TLSLEEP_OPENTCXO_0,
    TLSLEEP_OPENTCXO_1 = 25,
    TLSLEEP_OPENTCXO_2,
    TLSLEEP_OPENTCXO_3,
    TLSLEEP_OPENTCXO_MAX,

    TLSEEP_HWPOWERUP_0,
    TLSEEP_HWPOWERUP_1 = 30,
    TLSEEP_HWPOWERUP_2,
    TLSEEP_HWPOWERUP_3,
    TLSEEP_HWPOWERUP_4,
    TLSEEP_HWPOWERUP_5,
    TLSEEP_HWPOWERUP_6 = 35,
    TLSEEP_HWPOWERUP_7,
    TLSEEP_HWPOWERUP_8,
    TLSEEP_HWPOWERUP_9,
    TLSEEP_HWPOWERUP_MAX,

    TLSLEEP_FORCE_AWAKE_INNER_1 = 40,
    TLSLEEP_FORCE_AWAKE_INNER_2,
    TLSLEEP_FORCE_AWAKE_INNER_MAX,

    TLSLEEP_DSPRESUMERISR_0,
    TLSLEEP_DSPRESUMERISR_MAX,

    TLSLEEP_TIME_RECORD_MAX,

}EN_SLEEP_TIME_RECORD;

enum tagSLEEP_SR_STAMP
{
    TLSLEEP_SR_POWERUP_1 = 0,
    TLSLEEP_SR_POWERUP_2,
    TLSLEEP_SR_POWERUP_3,
    TLSLEEP_SR_POWERUP_4,
    TLSLEEP_SR_POWERDOWN_1,
    TLSLEEP_SR_POWERDOWN_2,
    TLSLEEP_SR_POWERDOWN_3,
    TLSLEEP_SR_POWERDOWN_4
};

#define  set_power_status_bit(bit)           (g_msp_pwrctrl.pwr_status = g_msp_pwrctrl.pwr_status | bit )
#define  clear_power_status_bit(bit)         (g_msp_pwrctrl.pwr_status = g_msp_pwrctrl.pwr_status & (~bit) )
#define  read_power_status_bit(bit)          (g_msp_pwrctrl.pwr_status & (bit))
#define  msp_set_error_bit(lock_flag, bit )\
do{\
    lock_flag = VOS_SplIMP();\
    set_power_status_bit(bit);\
    VOS_Splx(lock_flag);\
}while(0)
#define  mspsleep_print_error(fmt,...)      (vos_printf("[msp sleep]: <%s> <%d>"fmt"\n", __FUNCTION__, __LINE__, ##__VA_ARGS__))
#define  mspsleep_print_debug(fmt,...)\
do{\
    if(g_msp_pwrctrl.print_ctrl)\
    {\
        vos_printf("[msp sleep]: <%s> <%d>"fmt"\n", __FUNCTION__, __LINE__, ##__VA_ARGS__);\
    }\
}while(0);

#ifndef MSP_IN_V9R1
#define  mspsleep_print_info(fmt,...)\
do\
{\
    if(1 == g_msp_hidsctrl.print_control)\
    {\
        g_msp_hidsctrl.PrintVErrorNo = DIAG_LogReport(DIAG_GEN_LOG_MODULE(0, 0, 1), MSP_PID_DRX, (VOS_CHAR*)__FILE__, __LINE__,""fmt"\n", ##__VA_ARGS__);\
    }\
}while(0)
#define TLSLEEP_DFS_BUS_150M           (0)
#define TLSLEEP_DFS_DDR_120M           (120000)
#define TLSLEEP_DFS_DDR_150M           (0)
#define TLSLEEP_DFS_DDR_240M           (240000)
#define TLSLEEP_DFS_CCPU_600M          (0)

#define TLSLEEP_DFS_BUS_75M            (0)
#define TLSLEEP_DFS_DDR_75M            (0)
#define TLSLEEP_DFS_CCPU_150M          (0)

#define TLSLEEP_DfsQosRequest(qos_id, req_value, req_id)            mdrv_pm_dfs_qos_get(qos_id, req_value, req_id)
#define TLSLEEP_DfsQosRelease(qos_id, req_id)                       (0)
#define TLSLEEP_DfsQosUpdate(qos_id, req_id, req_value)             mdrv_pm_dfs_qos_update(qos_id, req_id, req_value)
#else
#define  mspsleep_print_info(fmt,...)
/*做DFS投票 V9R1需要 V7R2 不需要*/

#define TLSLEEP_DFS_BUS_150M            (150000)
#define TLSLEEP_DFS_DDR_150M            (150000)
#define TLSLEEP_DFS_CCPU_600M           (600000)

#define TLSLEEP_DFS_BUS_75M             (75000)
#define TLSLEEP_DFS_DDR_75M             (75000)
#define TLSLEEP_DFS_CCPU_150M           (150000)

#define TLSLEEP_DfsQosRequest(qos_id, req_value, req_id)           mdrv_pm_dfs_qos_get(qos_id, req_value, req_id)
#define TLSLEEP_DfsQosRelease(qos_id, req_id)                      mdrv_pm_dfs_qos_put(qos_id, req_id)
#define TLSLEEP_DfsQosUpdate(qos_id, req_id, req_value)            mdrv_pm_dfs_qos_update(qos_id, req_id, req_value)
#endif
#define TLSLEEP_GetTime(ulIndex)        (g_msp_pwrctrl.SleepTimeRecord.astRecord[ulIndex].ulTime)
#define TLSLEEP_GetType(ulIndex)        (g_msp_pwrctrl.SleepTimeRecord.astRecord[ulIndex].acType)

VOS_VOID TLSLEEP_ActivateHw(PWC_COMM_MODE_E modeId);
VOS_VOID TLSLEEP_TimeRecord(char * cString);
VOS_VOID TLSLEEP_StateRecord(DRX_STATE_SLICE state);
VOS_VOID TLSLEEP_PllEnable(PWC_COMM_MODE_E enCommMode, PWC_COMM_MODULE_E enCommModule);
VOS_VOID TLSLEEP_PllDisable(PWC_COMM_MODE_E enCommMode, PWC_COMM_MODULE_E enCommModule);
VOS_VOID TLSLEEP_PwrctrlUp(PWC_COMM_MODE_E enCommMode, PWC_COMM_MODULE_E enCommModule);
VOS_VOID TLSLEEP_PwrctrlDown(PWC_COMM_MODE_E enCommMode, PWC_COMM_MODULE_E enCommModule);
VOS_VOID TLSLEEP_TCXO0_IsrProc( VOS_VOID );
VOS_VOID TLSLEEP_TCXO1_IsrProc( VOS_VOID );
VOS_VOID TLSLEEP_MasterAwakeSlave(VOS_VOID);
VOS_VOID TLSLEEP_OpenTCXO(VOS_VOID );
VOS_VOID TLSLEEP_CloseTCXO(VOS_VOID );
VOS_INT32 TLSLEEP_RttForceAwake_Inner(VOS_VOID);
VOS_VOID TLSLEEP_RttSleep_Inner(VOS_VOID);
VOS_VOID TLSLEEP_SleepTask(VOS_UINT32 Para0, VOS_UINT32 Para1,VOS_UINT32 Para2, VOS_UINT32 Para3 );
VOS_VOID TLSLEEP_SetChanel(NV_TLMODE_BASIC_PARA_STRU astChan[2]);
VOS_VOID TLSLEEP_RttForceAwake(VOS_VOID);
VOS_VOID TLSLEEP_DebugRecordTime(VOS_VOID);
VOS_INT32 TLSLEEP_HwPowerUp(PWC_COMM_MODE_E modeId);
VOS_INT32 TLSLEEP_HwPowerDown(PWC_COMM_MODE_E modeId);
VOS_VOID TLSLEEP_DspHaltIsr(VOS_UINT param);
VOS_VOID TLSLEEP_DspResumeIsr(VOS_UINT param);
VOS_BOOL TLSLEEP_RttIsSleep(VOS_VOID);
VOS_INT TLSLEEP_AwakeIsr(VOS_INT enMode);
VOS_VOID TLSLEEP_ResumeDsp(VOS_VOID);
VOS_VOID TLSLEEP_DelayMs(VOS_UINT delay_ms, VOS_UINT flag);
VOS_VOID TLSLEEP_ShowStat(VOS_UINT32 ulIndex);
VOS_UINT32 TLSLEEP_Init(VOS_VOID);
VOS_VOID TLSLEEP_ShowDebugTime(VOS_INT mode);
VOS_UINT32 TLSLEEP_GetPreSfn(VOS_VOID);
VOS_VOID TLSLEEP_RunDsp(VOS_VOID);
VOS_VOID TLSLEEP_ExcTimeTask(VOS_UINT32 Para0, VOS_UINT32 Para1, VOS_UINT32 Para2, VOS_UINT32 Para3);
#if (FEATURE_MULTI_CHANNEL == FEATURE_ON)
VOS_VOID TLSLEEP_EnableRFTCXO(VOS_VOID );
VOS_VOID TLSLEEP_DisableRFTCXO(VOS_VOID );
#endif
VOS_VOID TLSLEEP_PWRCTRL_PWRUP(PWC_COMM_MODE_E enCommMode, PWC_COMM_MODULE_E enCommModule, PWC_COMM_MODEM_E enModemId);
VOS_VOID TLSLEEP_PWRCTRL_PWRDOWN(PWC_COMM_MODE_E enCommMode, PWC_COMM_MODULE_E enCommModule, PWC_COMM_MODEM_E enModemId);
VOS_VOID TLSLEEP_ShowSleepSwitch(VOS_VOID);

VOS_VOID TLSLEEP_ReportMntn(VOS_VOID);
VOS_VOID TLSLEEP_GetChannelInfo(VOS_VOID);


#ifdef __cplusplus
}
#endif


#endif /* __LTE_SLEEPFLOW_H__ */

