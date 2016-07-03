

/*****************************************************************************
  1 其他头文件包含
*****************************************************************************/
#include  <linux/hisi/pm/pwrctrl_multi_def.h>
#include  "soc_modem_sctrl_interface.h"
/*#include  "soc_baseaddr_interface.h"*/
#include  "soc_ao_sctrl_interface.h"
#include  "soc_acpu_sctrl_interface.h"
//#include  "product_config.h"


#ifndef __PWRCTRL_MULTI_SLEEP_H__
#define __PWRCTRL_MULTI_SLEEP_H__

#ifdef __cplusplus
#if __cplusplus
extern "C" {
#endif
#endif



/*****************************************************************************
  2 宏定义
*****************************************************************************/
#define PWC_VOTE_STAT_LOCK          (1)   /*投票不允许单板睡*/
#define PWC_VOTE_STAT_UNLOCK        (0)   /*去投票允许单板睡*/
#define PERI_SLEEP_STATE_MAX        (16)
#define PERI_SLEEP_CUR_STATE_NUM    (5)
#define ACPU_CPUIDLE_CUR_CPU_NUM    (8)
#define ACPU_CLUSTER_CUR_CPU_NUM    (2)

/*****************************************************************************
  3 枚举定义
*****************************************************************************/
typedef enum tagPWC_SC_RESERVED28_ID_E
{
    PWC_PD_SRAMBAK_RESTORE_ID_BIT      =    (0x1 << 0),

    PWC_SC_RESERVED28_ID_MAX           =    (0x1 << 31)
}PWC_SC_RESERVED28_ID_E;

typedef enum tagPWC_PD_MOUDLE_ID_E
{
    /*详细bit定义参考sc寄存器SC_MTCMOS_STAT0，SC_MTCMOS_STAT1*/
    PWC_PD_ID_PERI          = SOC_AO_SCTRL_SC_PW_MTCMOS_EN0_pw_en0_0peri_START,
    PWC_PD_ID_G3D           = SOC_AO_SCTRL_SC_PW_MTCMOS_EN0_pw_en0_1g3d_START,
    PWC_PD_ID_CODECISP      = SOC_AO_SCTRL_SC_PW_MTCMOS_EN0_pw_en0_2codecisp_START,
    PWC_PD_ID_RESERVE1      = SOC_AO_SCTRL_SC_PW_MTCMOS_EN0_pw_en0_3reserved_START,
    PWC_PD_ID_CCPU          = SOC_AO_SCTRL_SC_PW_MTCMOS_EN0_pw_en0_4mcpu_START,
    PWC_PD_ID_BBPHARQMEM    = SOC_AO_SCTRL_SC_PW_MTCMOS_EN0_pw_en0_5bbpharqmem_START,
    PWC_PD_ID_RESERVE2      = SOC_AO_SCTRL_SC_PW_MTCMOS_EN0_pw_en0_6reserved_START,
    PWC_PD_ID_RESERVE3      = SOC_AO_SCTRL_SC_PW_MTCMOS_EN0_pw_en0_7reserved_START,
    PWC_PD_ID_HIFI          = SOC_AO_SCTRL_SC_PW_MTCMOS_EN0_pw_en0_8hifi_START,
    PWC_PD_ID_RESERVE4      = SOC_AO_SCTRL_SC_PW_MTCMOS_EN0_pw_en0_9reserved_START,
    PWC_PD_ID_RESERVE5      = SOC_AO_SCTRL_SC_PW_MTCMOS_EN0_pw_en0_10reserved_START,
    PWC_PD_ID_RESERVE6      = SOC_AO_SCTRL_SC_PW_MTCMOS_EN0_pw_en0_11reserved_START,
    PWC_PD_ID_ACPUCLUSTER   = SOC_AO_SCTRL_SC_PW_MTCMOS_EN0_pw_en0_12acpucluster_START,
    PWC_PD_ID_ACPUL2MEM     = SOC_AO_SCTRL_SC_PW_MTCMOS_EN0_pw_en0_13reserved_START,

    /*MODEM SC*/
    PWC_PD_ID_DSPBBE        = 32 + SOC_MODEM_SCTRL_MDMSC_PW_MTCMOSEN_pw_mtcmosen_dspbbe_START,
    PWC_PD_ID_BBPCS         = 32 + SOC_MODEM_SCTRL_MDMSC_PW_MTCMOSEN_pw_mtcmosen_bbp_cs_START,
    PWC_PD_ID_LTE           = 32 + SOC_MODEM_SCTRL_MDMSC_PW_MTCMOSEN_pw_mtcmosen_lte_START,

    /*ACPU SC*/
    PWC_PD_ID_ACPU0         = 64 + SOC_ACPU_SCTRL_ACPU_SC_CPU0_MTCMOS_EN_pw_mtcmos_en_acpu0_START,
    PWC_PD_ID_ACPU1         = 65 + SOC_ACPU_SCTRL_ACPU_SC_CPU1_MTCMOS_EN_pw_mtcmos_en_acpu1_START,
    PWC_PD_ID_ACPU2         = 66 + SOC_ACPU_SCTRL_ACPU_SC_CPU2_MTCMOS_EN_pw_mtcmos_en_acpu2_START,
    PWC_PD_ID_ACPU3         = 67 + SOC_ACPU_SCTRL_ACPU_SC_CPU3_MTCMOS_EN_pw_mtcmos_en_acpu3_START,
    PWC_PD_ID_ACPU4         = 68 + SOC_ACPU_SCTRL_ACPU_SC_CPU4_MTCMOS_EN_pw_mtcmos_en_acpu4_START,
    PWC_PD_ID_ACPU5         = 69 + SOC_ACPU_SCTRL_ACPU_SC_CPU5_MTCMOS_EN_pw_mtcmos_en_acpu5_START,
    PWC_PD_ID_ACPU6         = 70 + SOC_ACPU_SCTRL_ACPU_SC_CPU6_MTCMOS_EN_pw_mtcmos_en_acpu6_START,
    PWC_PD_ID_ACPU7         = 71 + SOC_ACPU_SCTRL_ACPU_SC_CPU7_MTCMOS_EN_pw_mtcmos_en_acpu7_START,
    PWC_PD_ID_CLUSTER0      = 72 + SOC_ACPU_SCTRL_ACPU_SC_CPU0_MTCMOS_EN_pw_mtcmos_en_acpu0_START,
    PWC_PD_ID_CLUSTER1      = 73 + SOC_ACPU_SCTRL_ACPU_SC_CPU0_MTCMOS_EN_pw_mtcmos_en_acpu0_START,
    PWC_PD_ID_ACPU_SUBSYS   = 74 + SOC_ACPU_SCTRL_ACPU_SC_CPU0_MTCMOS_EN_pw_mtcmos_en_acpu0_START,

    PWC_PD_ID_BUTT          = 75

} PWC_PD_MOUDLE_ID;

/*****************************************************************************
  4 消息头定义
*****************************************************************************/


/*****************************************************************************
  5 消息定义
*****************************************************************************/


/*****************************************************************************
  6 STRUCT定义
*****************************************************************************/

typedef struct PWC_TELE_MNTN_PU_STRU_S
{
    u32_t  wakeCount;
    u32_t  wakeSrc0;
    u32_t  wakeSrc1;
    u32_t  wakeSrcIPC;
    u32_t  wake2ndInt;
    u8_t   wakeSrcGPIO[8];
}PWC_TELE_MNTN_PU_STRU;

typedef struct PWC_TELE_MNTN_PD_STRU_S
{
    u32_t  sleepCount;
}PWC_TELE_MNTN_PD_STRU;

typedef struct PWC_TELE_MNTN_WFIFAIL_STRU_S
{
    u32_t  WFIFailCount;
}PWC_TELE_MNTN_WFIFAIL_STRU;

typedef struct PWC_TELE_MNTN_PUPD_STRU_S
{
    PWC_TELE_MNTN_PD_STRU pdStat;
    PWC_TELE_MNTN_PU_STRU puStat;
    PWC_TELE_MNTN_WFIFAIL_STRU WFIFailStat;
    u32_t pdSliceTime;
    u32_t puSliceTime;
    u32_t WFIFailSliceTime;
}PWC_TELE_MNTN_PUPD_STRU;

typedef struct PWC_TELE_MNTN_SLEEPWAKESTAT_STRU_S
{
    s32_t  sX;
    u32_t  sleepCount;
    u32_t  wakeCount;
    u32_t  sleepSliceTime;
    u32_t  wakeSliceTime;
    u32_t  wakeSrc0;
    u32_t  wakeSrc1;
}PWC_TELE_MNTN_SLEEPWAKESTAT_STRU;

typedef struct PWC_TELE_MNTN_NOTSLEEPREASON_STRU_S
{
    s32_t  canSleepRet;
    u32_t  HWVoteMap;
    u32_t  voteMap;
    u32_t  socpStat[3];
}PWC_TELE_MNTN_NOTSLEEPREASON_STRU;

typedef struct PWC_TELE_MNTN_SLEEPWAKEINFO_STRU_S
{
    PWC_TELE_MNTN_SLEEPWAKESTAT_STRU stat;
    PWC_TELE_MNTN_NOTSLEEPREASON_STRU notSleepReason;
}PWC_TELE_MNTN_SLEEPWAKEINFO_STRU;

typedef struct PWC_TELE_MNTN_SLEEPWAKE_STRU_S
{
    s32_t  sX;
    PWC_TELE_MNTN_SLEEPWAKEINFO_STRU info[PERI_SLEEP_CUR_STATE_NUM];
}PWC_TELE_MNTN_SLEEPWAKE_STRU;

typedef struct PWC_TELE_MNTN_CPUIDLEPUPD_STRU_S
{
    u32_t  sleepCount;
    u32_t  wakeCount;
    u32_t  cpuId;
    u32_t  status;
}PWC_TELE_MNTN_CPUIDLEPUPD_STRU;

typedef struct PWC_TELE_MNTN_CPUIDLEWFIFAIL_STRU_S
{
    u32_t  WFIFailCount;
    u32_t  cpuId;
}PWC_TELE_MNTN_CPUIDLEWFIFAIL_STRU;
typedef struct PWC_TELE_MNTN_CPUIDLE_STRU_S
{
    PWC_TELE_MNTN_CPUIDLEPUPD_STRU cpuStat;
    PWC_TELE_MNTN_CPUIDLEWFIFAIL_STRU WFIFailStat;
    u32_t  sleepSliceTime;
    u32_t  wakeSliceTime;
    u32_t  WFIFailSliceTime;
}PWC_TELE_MNTN_CPUIDLE_STRU;

typedef struct PWC_TELE_MNTN_VOTESTAT_STRU_S
{
    u32_t stat;             /*PWC_VOTE_STAT_LOCK 或者 PWC_VOTE_STAT_UNLOCK*/
    u32_t voteMap;          /*软件投票值或者硬件投票值*/
    s32_t clientId;         /*含义为PWC_CLIENT_ID_E的低1个字节*/
    u32_t taskId;           /*此次投票的任务ID*/
}PWC_TELE_MNTN_VOTESTAT_STRU;

typedef struct PWC_TELE_MNTN_VOTE_STRU_S
{
    PWC_TELE_MNTN_VOTESTAT_STRU voteStat;
    u32_t  sliceTime;
}PWC_TELE_MNTN_VOTE_STRU;

typedef struct PWC_TELE_MNTN_DFS_QOSINFO_STRU_S
{
    s16_t  cmd_id;
    s16_t  qos_id;
    s32_t  req_id;
    s32_t  ret;
    u32_t  task_id;  /*CCPU:task_id; MCU:core_id*/
    u32_t  tag_freq;
    u32_t  new_freq;
    u32_t  max_freq;
    u32_t  min_freq;
}PWC_TELE_MNTN_DFS_QOSINFO_STRU;

typedef struct PWC_TELE_MNTN_DFS_QOS_STRU_S
{
    PWC_TELE_MNTN_DFS_QOSINFO_STRU info;
    u32_t  qosSliceTime;
}PWC_TELE_MNTN_DFS_QOS_STRU;

typedef struct PWC_TELE_MNTN_DFS_POLICYINFO_STRU_S
{
    s32_t  load;
    u32_t  new_freq;
}PWC_TELE_MNTN_DFS_POLICYINFO_STRU;

typedef struct PWC_TELE_MNTN_DFS_POLICY_STRU_S
{
    PWC_TELE_MNTN_DFS_POLICYINFO_STRU info;
    u32_t  policySliceTime;
}PWC_TELE_MNTN_DFS_POLICY_STRU;

typedef struct PWC_TELE_MNTN_DFS_TARGETINFO_STRU_S
{
    u32_t  old_freq;
    u32_t  new_freq;
    s32_t  reason;
}PWC_TELE_MNTN_DFS_TARGETINFO_STRU;

typedef struct PWC_TELE_MNTN_DFS_TARGET_STRU_S
{
    PWC_TELE_MNTN_DFS_TARGETINFO_STRU info;
    u32_t  targetSliceTime;
}PWC_TELE_MNTN_DFS_TARGET_STRU;

typedef struct PWC_TELE_MNTN_DFS_DDR_STRU_S
{
    PWC_TELE_MNTN_DFS_QOS_STRU qos;
    PWC_TELE_MNTN_DFS_POLICY_STRU policy;
    PWC_TELE_MNTN_DFS_TARGET_STRU target;
}PWC_TELE_MNTN_DFS_DDR_STRU;

typedef struct PWC_TELE_MNTN_DFS_ACPU_STRU_S
{
    PWC_TELE_MNTN_DFS_TARGET_STRU target;
}PWC_TELE_MNTN_DFS_ACPU_STRU;

typedef struct PWC_TELE_MNTN_IPCSTATINFO_STRU_S
{
    u32_t rawStat;
}PWC_TELE_MNTN_IPCSTATINFO_STRU;

typedef struct PWC_TELE_MNTN_IPCSTAT_STRU_S
{
    PWC_TELE_MNTN_IPCSTATINFO_STRU info;
    u32_t sliceTime;
}PWC_TELE_MNTN_IPCSTAT_STRU;



typedef struct PWC_MCU_LOG_STRU_S
{
    PWC_TELE_MNTN_PUPD_STRU ccpu;
    PWC_TELE_MNTN_PUPD_STRU acpu;
    PWC_TELE_MNTN_PUPD_STRU hifi;
    PWC_TELE_MNTN_SLEEPWAKE_STRU mcu;
    PWC_TELE_MNTN_CPUIDLE_STRU cpuIdle[ACPU_CPUIDLE_CUR_CPU_NUM+ACPU_CLUSTER_CUR_CPU_NUM];
    PWC_TELE_MNTN_VOTE_STRU vote[PERI_SLEEP_CUR_STATE_NUM];
    PWC_TELE_MNTN_DFS_DDR_STRU dfsDdr;
    PWC_TELE_MNTN_DFS_ACPU_STRU dfsAcpu;
    PWC_TELE_MNTN_IPCSTAT_STRU ipcStat;
}PWC_MCU_LOG_STRU;

typedef struct PWC_TELE_MNTN_CCPU_SLEEPWAKESTAT_STRU_S
{
    u32_t  cSleepCount;         /*+0X0*/
    u32_t  cWakeCount;          /*+0X4*/

    u32_t  cSleepMgrSliceTime;  /*+0X8*/
    u32_t  cSleepSliceTime;     /*+0XC*/
    u32_t  cWakeSliceTime;      /*+0X10*/
    u32_t  cWakeMgrSliceTime;   /*+0X14*/

    u32_t  cSleepIpcCount;      /*+0X18*/
    u32_t  cSleepIpcSliceTime;  /*+0X1C*/
    u32_t  cWFIRetCount;        /*+0X20*/
    u32_t  cWFIRetSliceTime;    /*+0X24*/
    u32_t  cASMRunningPoint;    /*+0X28*/
    u32_t  cTaskRunningPoint;   /*+0X2c*/
}PWC_TELE_MNTN_CCPU_SLEEPWAKESTAT_STRU;

typedef struct PWC_TELE_MNTN_CCPU_NOTSLEEPREASON_STRU_S
{
    s32_t  canSleepRet;
    u32_t  HWVoteMap;
    u32_t  voteMap;
    u32_t  nextSchTimeId:8;
    u32_t  nextSchTimeValue:24;
}PWC_TELE_MNTN_CCPU_NOTSLEEPREASON_STRU;

typedef struct PWC_TELE_MNTN_CCPU_SLEEPWAKE_STRU_S
{
    PWC_TELE_MNTN_CCPU_SLEEPWAKESTAT_STRU stat;
    PWC_TELE_MNTN_CCPU_NOTSLEEPREASON_STRU notSleepReason;
}PWC_TELE_MNTN_CCPU_SLEEPWAKE_STRU;


typedef struct PWC_TELE_MNTN_CCPU_DFS_DDR_STRU_S
{
    PWC_TELE_MNTN_DFS_QOS_STRU qos;
}PWC_TELE_MNTN_CCPU_DFS_DDR_STRU;

typedef struct PWC_TELE_MNTN_CCPU_DFS_CCPU_STRU_S
{
    PWC_TELE_MNTN_DFS_QOS_STRU qos;
    PWC_TELE_MNTN_DFS_POLICY_STRU policy;
    PWC_TELE_MNTN_DFS_TARGET_STRU target;
}PWC_TELE_MNTN_CCPU_DFS_CCPU_STRU;

typedef struct PWC_CCPU_LOG_STRU_S
{
    PWC_TELE_MNTN_CCPU_SLEEPWAKE_STRU ccpu;
    PWC_TELE_MNTN_VOTE_STRU vote;
    PWC_TELE_MNTN_CCPU_DFS_DDR_STRU dfsDdr;
    PWC_TELE_MNTN_CCPU_DFS_CCPU_STRU dfsCcpu;
}PWC_CCPU_LOG_STRU;


typedef struct PWC_TELE_MNTN_ACPU_DFS_BOOSTINFO_STRU_S
{
    u32_t  cpu;
    u32_t  tag_freq;
    u32_t  new_freq;
    u32_t  min_freq;
    u32_t  max_freq;
}PWC_TELE_MNTN_ACPU_DFS_BOOSTINFO_STRU;


typedef struct PWC_TELE_MNTN_ACPU_DFS_POLICYINFO_STRU_S
{
    u32_t  cpu;
    u32_t  tag_freq;
    u32_t  new_freq;
    u32_t  min_freq;
    u32_t  max_freq;
    u8_t   load[ACPU_CPUIDLE_CUR_CPU_NUM];
}PWC_TELE_MNTN_ACPU_DFS_POLICYINFO_STRU;

typedef struct PWC_TELE_MNTN_ACPU_DFS_BOOST_STRU_S
{
    PWC_TELE_MNTN_ACPU_DFS_BOOSTINFO_STRU info;
    u32_t  boostSliceTime;
}PWC_TELE_MNTN_ACPU_DFS_BOOST_STRU;

typedef struct PWC_TELE_MNTN_ACPU_DFS_POLICY_STRU_S
{
    PWC_TELE_MNTN_ACPU_DFS_POLICYINFO_STRU info;
    u32_t  policySliceTime;
}PWC_TELE_MNTN_ACPU_DFS_POLICY_STRU;

typedef struct PWC_TELE_MNTN_ACPU_DFS_CCPU_STRU_S
{
    PWC_TELE_MNTN_ACPU_DFS_BOOST_STRU boost;
    PWC_TELE_MNTN_ACPU_DFS_POLICY_STRU policy;
}PWC_TELE_MNTN_ACPU_DFS_ACPU_STRU;

typedef struct PWC_TELE_MNTN_ACPU_DFS_DDR_QOSINFO_STRU_S
{
    s16_t  cmd_id;
    s16_t  qos_id;
    u16_t  pid;
    u16_t  ppid;
    s32_t  tag_val;
    u32_t  new_freq;
    u32_t  min_freq;
    u32_t  max_freq;
}PWC_TELE_MNTN_ACPU_DFS_DDR_QOSINFO_STRU;


typedef struct PWC_TELE_MNTN_ACPU_DFS_DDR_QOS_STRU_S
{
    PWC_TELE_MNTN_ACPU_DFS_DDR_QOSINFO_STRU info;
    u32_t  qosSliceTime;
}PWC_TELE_MNTN_ACPU_DFS_DDR_QOS_STRU;

typedef struct PWC_TELE_MNTN_ACPU_DFS_DDR_STRU_S
{
    PWC_TELE_MNTN_ACPU_DFS_DDR_QOS_STRU qos;
}PWC_TELE_MNTN_ACPU_DFS_DDR_STRU;

typedef struct PWC_ACPU_LOG_STRU_S
{
    PWC_TELE_MNTN_ACPU_DFS_DDR_STRU dfsDdr;
    PWC_TELE_MNTN_ACPU_DFS_ACPU_STRU dfsAcpu;
}PWC_ACPU_LOG_STRU;


typedef struct ST_STORE_ADDR_INFO_S
{
    u32_t ulStartAddr;            /*需要备份的寄存器地址信息*/
    u32_t ulLength;               /*内容长度，需要4字节对齐,单位32bit*/
} ST_STORE_REG_ADDR_INFO;

typedef struct ST_STORE_BIT_ADDR_INFO_S
{
    u32_t ulAddr;               /*需要备份的寄存器地址信息*/
    u32_t ulToAddr;             /*恢复地址,单位32bit*/
    u32_t ulMask;               /*恢复屏蔽,单位32bit*/
    u32_t ulSetMask;            /*特殊写使能,单位32bit*/
} ST_STORE_BIT_ADDR_INFO;


typedef struct ST_VOTE_HW_INFO_S
{
    u32_t voteEn;                   /*唤醒投票，即禁止睡眠*/
    u32_t voteDis;                  /*睡眠投票，即允许睡眠*/
    u32_t voteStat;                 /*投票状态寄存器，屏蔽前*/
    u32_t voteSleepMsk;             /*睡眠投票屏蔽*/
    u32_t voteWakeMsk;              /*唤醒投票屏蔽*/
    u32_t voteSleepStat;            /*投票状态寄存器，屏蔽后*/
    u32_t voteWakeStat;             /*投票状态寄存器，屏蔽后*/
} ST_VOTE_HW_INFO;

#ifdef CHIP_BB_HI6210
typedef struct ST_SYSCTRL_INT_INFO_S
{
    u32_t intStatR;                 /*睡眠投票，即允许睡眠*/
    u32_t intStatM;                 /*投票状态寄存器，屏蔽前*/
    u32_t intClr;                   /*睡眠投票屏蔽*/
    u32_t intEn0;                   /*唤醒投票屏蔽*/
    u32_t intDis0;                  /*投票状态寄存器，屏蔽后*/
    u32_t intEnStat;                /*唤醒投票，即禁止睡眠*/
} ST_SYSCTRL_INT_HW_INFO;
#else
typedef struct ST_SYSCTRL_INT_INFO_S
{
    u32_t intEnStat;                /*唤醒投票，即禁止睡眠*/
    u32_t intStatR;                 /*睡眠投票，即允许睡眠*/
    u32_t intStatM;                 /*投票状态寄存器，屏蔽前*/
    u32_t intClr;                   /*睡眠投票屏蔽*/
    u32_t intEn0;                   /*唤醒投票屏蔽*/
    u32_t intDis0;                  /*投票状态寄存器，屏蔽后*/
} ST_SYSCTRL_INT_HW_INFO;
#endif

typedef struct ST_SET_BIT_ADDR_INFO_S
{
    u32_t ulAddr;               /*需要配置的寄存器地址信息*/
    u32_t ulMask;               /*屏蔽位,单位32bit*/
    u32_t ulvalue;              /*要写入的值,单位32bit*/
} ST_SET_BIT_ADDR_INFO;
/*****************************************************************************
  7 UNION定义
*****************************************************************************/
typedef enum tagPWC_TELE_SLEEP_MODE_ID_E
{
    /*BIT0-7 HW*/
    PWRCTRL_TELE_INVALID = -1,
    PWRCTRL_TELE_CCPU      = 0,
    PWRCTRL_TELE_PERI      = 1,
    PWRCTRL_TELE_ACPU      = 2,
    PWRCTRL_TELE_REV0      = 3,
    PWRCTRL_TELE_REV1      = 4,
    PWRCTRL_TELE_REV2      = 5
} PWC_TELE_SLEEP_MODE_ID_E;

typedef enum tagPWC_TELE_SLEEP_CLIENT_ID_E
{
    /*BIT0-7 HW*/
    PWRCTRL_TELE_CLIENT_INVALID    = -1,
    PWRCTRL_TELE_SLEEP_CSIGHT0      = 0,
    PWRCTRL_TELE_SLEEP_CSIGHT1      = 1,
    PWRCTRL_TELE_SLEEP_IPF          = 2,
    PWRCTRL_TELE_SLEEP_SOCP         = 3,

    /* Test */
    PWRCTRL_TELE_CLIENT_BUTT        = 32
} PWC_TELE_SLEEP_CLIENT_ID_E;



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

#endif /* end of pwrctrl_multi_sleep.h */
