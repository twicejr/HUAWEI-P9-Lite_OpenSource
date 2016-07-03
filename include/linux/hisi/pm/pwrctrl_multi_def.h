

/*****************************************************************************
  1 其他头文件包含
*****************************************************************************/

#ifndef __PWRCTRL_MULTI_DEF_H__
#define __PWRCTRL_MULTI_DEF_H__

#include <linux/hisi/pm/pwrctrl_multi_dfs_asm.h>

#ifdef __cplusplus
#if __cplusplus
extern "C" {
#endif
#endif



/*****************************************************************************
  2 宏定义
*****************************************************************************/
/*just for temp stub*/
/*
#ifndef FEATURE_ON
#define FEATURE_ON              1
#endif
#define FEATURE_POWER_DRV       FEATURE_ON
*/

#if defined (WIN32) || defined (GENERIC_PROJECT)
#define local_t
#else
#define local_t static
#endif

#define bool_t  unsigned int
#define void_t  void

#define s8_t    char
#define s16_t   short
#define s32_t   int

#define u8_t    unsigned char
#define u16_t   unsigned short
#define u32_t   unsigned int
#define u64_t   unsigned long long

#ifndef NULL
#define NULL ((void*)0)
#endif
#ifndef BIT
#define BIT(x)                      ((unsigned)0x1 << (x))
#endif
#define BITMSK(x)                   (BIT(x) << 16)

#ifdef WIN32
#define PWC_TASK_LOOP()
#else
#define PWC_TASK_LOOP()             for ( ; ; )
#endif

#if defined (WIN32) || defined (GENERIC_PROJECT)
#define RET_CODE_IF_NOT_OK(func)    (func)
#define RET_ERR_IF(cond)            (cond)
#define LOG_IF(cond)                (cond)
#else
#define RET_CODE_IF_NOT_OK(func)                             \
{                                                            \
    dfs_ret _ERR_CODE = func;                                \
    if(_ERR_CODE != RET_OK)                                  \
    {                                                        \
        PWC_TRACE(PWC_LOG_ERROR, #func" return %d (FILE:%s, LINE:%d)", _ERR_CODE, __FILE__, __LINE__, 0, 0, 0);  \
        return _ERR_CODE;                                    \
    }                                                        \
}

#define RET_ERR_IF(cond)                                     \
    if(cond)                                                 \
    {                                                        \
        PWC_TRACE(PWC_LOG_ERROR, #cond" (FILE:%s, LINE:%d)", __FILE__, __LINE__, 0, 0, 0, 0);  \
        return RET_ERR;                                      \
    }

#define LOG_IF(cond)                                         \
    if(cond)                                                 \
    {                                                        \
        PWC_TRACE(PWC_LOG_INFO,  #cond" (FILE:%s, LINE:%d)", __FILE__, __LINE__, 0, 0, 0, 0);  \
    }
#endif

/*log output*/
#define MODULE_PWRCTRL              (0x20)

/*****************************************************************************/
#define PWRCTRL_SWITCH_OFF          (0)
#define PWRCTRL_SWITCH_ON           (1)

#define PWRCTRL_FALSE               (0)
#define PWRCTRL_TRUE                (1)

#define PWRCTRL_BOOT_SYN_TIME       (100)            /*单位: slice timer 33us*/
#define PWRCTRL_BOOT_SYNC_BIT       (BIT(16))

/*^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^*/
#define PWRCTRL_DELAY_TCXO_1US(x)       (x*19)              /*单位-近似 1us    (19200000/1000000)*/
#define PWRCTRL_DELAY_32K_100US(x)      (x*3)               /*单位-近似 100 us  (32768/1000000)*100 */

#define PWRCTRL_REG_MAX_VALUE       (0xFFFFFFFF)


#define PWRCTRL_SLICETIMER_XLOAD    (PWRCTRL_REG_MAX_VALUE)
#define PWRCTRL_SLICE_CLK           (32)
#define PWRCTRL_SLICE_UNIT_CONV     (1000)           /*s -> us*/
#define PWC_SLICE_TIMER_ID          (10)


#define MCA_OBJ_BEGIN (0)
#define MCA_OBJ_CPU (0)
#define MCA_OBJ_GPU (1)
#define MCA_OBJ_DDR (2)
#define MCA_OBJ_CCPU (3)
#define MCA_OBJ_BUS (4)
#define MCA_OBJ_BUSLOW (5)
#define MCA_OBJ_END MCA_OBJ_BUSLOW /*如果增加OBJ，请更新END*/
#define MCA_OBJ_NUM (MCA_OBJ_END + 1)

#define MCA_PARAM_BEGIN (0)
#define MCA_PARAM_MAX (0)
#define MCA_PARAM_MIN (1)
#define MCA_PARAM_LOCK (2)
#define MCA_PARAM_SAFE (3)
#define MCA_PARAM_END MCA_PARAM_SAFE /*如果增加PARAM，请更新END*/
#define MCA_PARAM_NUM (MCA_PARAM_END + 1)

#define CPU_IDLE_STAT_VALID 0x55aa
#define CPU_IDLE_STAT_INVALID 0
/*       31~16                  15~0   */
/*       magic            cpuidle state*/
#define CPUIDLE_STATE_MAGIC_START_BIT 16
#define CPUIDLE_STATE_START_BIT 0

/*#define POLICY_MAX_TOTAL_SIZE (MAX_PROFILE_NUM * POLICY_LEN)*/

#define BYTES_PER_UINT32 (4)

/*更改profile size时请注意更新PROFILE_MAX_TOTAL_SIZE的值*/
#define ACPU_PROFILE_LEN (20)
#define ACPU_PROFILE_NUM (6)

#define DDR_PROFILE_LEN (22)
#define DDR_PROFILE_NUM (6)

#define GPU_PROFILE_LEN (1)
#define GPU_PROFILE_NUM (4)

#define CPU_PROFILE_SIZE (ACPU_PROFILE_LEN * ACPU_PROFILE_NUM * BYTES_PER_UINT32)
#define DDR_PROFILE_SIZE (DDR_PROFILE_LEN * DDR_PROFILE_NUM * BYTES_PER_UINT32)
#define GPU_PROFILE_SIZE (GPU_PROFILE_LEN * GPU_PROFILE_NUM * BYTES_PER_UINT32)

#define PROFILE_MAX_TOTAL_SIZE DDR_PROFILE_SIZE

#define HPM_SEARCH_VOLT_ENABLE
#define HPM_SEARCH_VOLT_ACPU_ENABLE
#if 0/*V8R1 ASIC回片使用*/
#define HPM_SEARCH_VOLT_DDR_ENABLE
#define HPM_SEARCH_VOLT_PERIPH_ENABLE /*y_todo:回片先不打开*/
#endif

#define FREQ_MAX_NUM 6
#define VALID_VOLTAGE_MAGIC 0x5a5ac5c5

#define ACPU_FREQ_208M 208000
#define ACPU_FREQ_432M 432000
#define ACPU_FREQ_729M 729000
#define ACPU_FREQ_960M 960000
#define ACPU_FREQ_1_2G 1200000
#define ACPU_FREQ_1_4G 1400000
#define ACPU_FREQ_1_5G 1500000

#define ACPU_FREQ_MAX_NUM  5

#define DFS_DDR_FREQ_533M    (533000)
#define DFS_ACPU_FREQ_700M    (700000)

#define ACPU_DFS_LOCK_FLAG      (0xAEAEAEAE)
#define ACPU_DFS_UNLOCK_FLAG    (0x0)
#define MEDIA_PLL_SEM_TIMEOUT   (0x100)

#define MEDIA_PLL_ON            (0x5E5E5E5E)
#define MEDIA_PLL_OFF           (0x0)
#define MEDIAPLL_WAIT_TIMEOUT       (0x10000)


#define  DDR_PD_PRD_64 0x40
#define  DDR_PD_PRD_256 0x100
#define  DDR_PD_PRD_CHANGE_FLAG (0x5F5F5F5F)
/*****************************************************************************
  3 枚举定义
*****************************************************************************/
/* 返回值定义 */
typedef enum
{
    RET_ERR_PARAM_NULL = -0xF000,
    RET_ERR_PARAM_INVALID,
    RET_ERR_OVERFLOW,
    RET_ERR_INSUFFICIENT,
    RET_ERR_LIMITED,
    RET_ERR_NOT_FOUND,
    RET_ERR_NOT_OPEN,
    RET_ERR_DUPLICATE,
    RET_ERR_CONNECT_FAIL,
    RET_ERR_TIME_OUT,
    RET_ERR_UNKNOWN,
    RET_ERR = -1,
    RET_OK = 0
} EM_PWC_RET;


/* 打印通道选择定义 */
typedef enum
{
    PWC_DEBUG_UART = 0,     /* 0x0:UART                                  */
    PWC_DEBUG_LOG,          /* 0x1:trace log                             */
    PWC_DEBUG_BUG,          /* 0x2:定位使用                              */
    PWC_DEBUG_DRX,          /* 0x3:通信模块                              */
    PWC_DEBUG_OFF = 0xff    /* 0x4:关闭                                  */
} EM_PWC_LOG_CHAN;


/* 低功耗特性开关定义 */
typedef enum
{
    PWC_SWITCH_CSLEEP = 0,      /* 0x0: C核上下电   */
    PWC_SWITCH_ASLEEP,          /* 0x1: A核上下电   */
    PWC_SWITCH_MSLEEP,          /* 0x2: 系统外设区上下电     */
    PWC_SWITCH_HIFI,            /* 0x3: hifi 上下电          */

    PWC_SWITCH_CDFS,            /* 0x4: C核动态调频          */
    PWC_SWITCH_ADFS,            /* 0x5: A核动态调频调压、AVS */
    PWC_SWITCH_DDFS,            /* 0x6: DDR 静态调频         */
    PWC_SWITCH_DAFS,            /* 0x7: DDR 自动调频       */

    PWC_SWITCH_CAVS,            /* 0x8: C核动态调压          */
    PWC_SWITCH_AAVS,            /* 0x9: A核动态调压 */
    PWC_SWITCH_DAVS,            /* 0xA: DDR 动态调压         */
    PWC_SWITCH_GAVS,            /* 0xB: GPU动态调压          */

    PWC_SWITCH_CPUIDLE,         /* 0xC: ACPU cpu IDLE        */
    PWC_SWITCH_BDFS,            /* 0xD: bus调频              */
    PWC_SWITCH_AUTOHOTPLUG,     /* 0xE: AUTO PLUG            */
    PWC_SWITCH_QOS,             /* 0xF: dvfs qos             */

    PWC_SWITCH_MNTN = 16,       /* bit16: 可维可测           */
    PWC_SWITCH_DEBPT,           /* bit17: 调试开关           */
    PWC_SWITCH_APNTFLAG,        /* bit18: 打印至A核          */
    PWC_SWITCH_PMQOS,           /* bit19: 上下电Qos          */

    PWC_SWITCH_BLOWDFS,         /* bit20: BUS100M调频        */
    PWC_SWITCH_BIDLE,           /* bit21: BUS IDLE自动降频   */
    PWC_SWITCH_BLOWIDLE,        /* bit22: BUS100M IDLE自动降频*/
    PWC_SWITCH_MNOCDFS,         /* bit23: MODEM NOC DFS      */

    PWC_SWITCH_MNOCIDLE,        /* bit24: MODEM NOC IDLE自动降频*/
    PWC_SWITCH_MGENERAL,        /* bit25: MCU低功耗总开关    */
    PWC_SWITCH_CGENERAL,        /* bit26: CCPU低功耗总开关   */
    PWC_SWITCH_AGENERAL,        /* bit27: ACPU低功耗总开关   */

    PWC_SWITCH_MCUSHELL,        /* bit28: ACPU调用MCU命令接口 */

    PWC_SWITCH_BUTT = 32        /* 边界值 */

} EM_PWC_SWITCH;

typedef enum {
    PWC_FUNC_INVALID = 0xFF,
    PWC_FUNC_DFS_ENABLE = 1,
    PWC_FUNC_AVS_ENABLE = 2,
    PWC_FUNC_DVFS_ENABLE = 4,
    PWC_FUNC_DFS_DISABLE = 8,
    PWC_FUNC_AVS_DISABLE = 0x10,
    PWC_FUNC_DVFS_DISABLE = 0x20,
    PWC_FUNC_BUTT
}EM_PWC_FUNC;

/* 模块的上电状态 */
typedef enum
{
    PWC_STATUS_ACORE = 0,       /* 0x0: A核上电标志   */
    PWC_STATUS_CCORE = 1,       /* 0x1: C核上电标志   */
    PWC_STATUS_HIFI =  2,       /* 0x2: HIFI核上电标志   */
    PWC_STATUS_BUTT = 32        /* 边界值 */

} EM_PWC_STATUS;

/* cpu idle status */
typedef enum
{
    CPU_IDLE_INVALID = -1,
    CPU_IDLE_C0,
    CPU_IDLE_C1,
    CPU_IDLE_C2,
    CPU_IDLE_C3, /*以上为IDLE状态*/
    CPU_IDLE_C4, /*表示全系统下电*/
    CPU_IDLE_MAX
} CPU_IDLE_STAT;

/*mediapll 使用者列表*/
typedef enum
{
    MEDIAPLL_HIFI = 0,
    MEDIAPLL_CCPU = 1
} MEDIAPLL_CLASS_ID;

/*****************************************************************************
  4 消息头定义
*****************************************************************************/


/*****************************************************************************
  5 消息定义
*****************************************************************************/


/*****************************************************************************
  6 STRUCT定义
*****************************************************************************/
typedef struct ST_PWC_SWITCH_STRU_S
{
    bool_t cSleep     :1; /*bit0*/
    bool_t aSleep     :1; /*bit1*/
    bool_t mSleep     :1; /*bit2*/
    bool_t hifi       :1; /*bit3*/

    bool_t cDfs       :1; /*bit4*/
    bool_t aDfs       :1; /*bit5*/
    bool_t dDfs       :1; /*bit6*/
    bool_t gDfs       :1; /*bit7*/

    bool_t cAvs       :1; /*bit8*/
    bool_t aAvs       :1; /*bit9*/
    bool_t dAvs       :1; /*bit10*/
    bool_t gAvs       :1; /*bit11*/

    bool_t cpuIdle    :1; /*bit12*/
    bool_t bDfs       :1; /*bit13*/
    bool_t aHotPlug   :1; /*bit14*/
    bool_t qos        :1; /*bit15*/

    bool_t mntn       :1; /*bit16*/
    bool_t debPt      :1; /*bit17*/
    bool_t apntFlag   :1; /*bit18*/
    bool_t pmqos      :1; /*bit19*/

    bool_t bLowDfs    :1; /*bit20*/
    bool_t bIdle      :1; /*bit21*/
    bool_t bLowIdle   :1; /*bit22*/
    bool_t mNocDfs    :1; /*bit23*/

    bool_t mNocIdle   :1; /*bit24*/
    bool_t mGeneral   :1; /*bit25*/
    bool_t cGeneral   :1; /*bit26*/
    bool_t aGeneral   :1; /*bit27*/

    bool_t amshell    :1; /*bit28*/

}ST_PWC_SWITCH_STRU;

typedef struct ST_PWC_STATUS_STRU_S
{
    bool_t ACore     :1; /*bit0*/
    bool_t CCore     :1; /*bit1*/
    bool_t HIFI      :1; /*bit2*/

}ST_PWC_STATUS_STRU;

struct acpu_freq_volt_stru
{
    unsigned int magic;
    unsigned int support_freq_num;
    unsigned int support_freq_max;
    unsigned int start_prof;
    unsigned int vol[FREQ_MAX_NUM + 1]; /*每个频点的电压*/
    unsigned int hpm_dly_threshold[FREQ_MAX_NUM + 1];/*积分检测电压模块电压控制门限: bit0~bit15,进入门限；bit16:32，退出门限*/
};

struct ddr_freq_volt_stru
{
    unsigned int magic;
    unsigned int support_freq_num;
    unsigned int support_freq_max;
    unsigned int start_prof;
    unsigned int vol[FREQ_MAX_NUM + 1]; /*每个频点的电压*/
};

struct freqdump
{
    unsigned int freq_acpu_freq_last;
    unsigned int freq_acpu_freq_cur;

    unsigned int freq_acpu_load;
    unsigned int freq_acpu_core_online;
    unsigned int freq_every_acpu_load[4];

    unsigned int freq_ddr_freq_last;
    unsigned int freq_ddr_freq_cur;
    unsigned int freq_ddr_data_load;
    unsigned int freq_ddr_cmd_load;

    unsigned int freq_ccpu_freq_last;
    unsigned int freq_ccpu_freq_cur;
    unsigned int freq_ccpu_load;

};

/******ACPU dfs freq&flag struct********/
struct acpufreqinfo
{
    unsigned int dfs_flag;
    unsigned int dfs_acpu_freq;
    unsigned int dfs_temp_freq;
};

/******MCU&CCPU control MEDPLL state struct********/
struct medpllstate
{
    unsigned int ccpu_medpll_state;
    unsigned int hifi_medpll_state;
};
/*****************************************************************************
  7 UNION定义
*****************************************************************************/


/*****************************************************************************
  8 OTHERS定义
*****************************************************************************/
typedef void_t          (*PWCVFUNCPTRV)(void_t);
typedef s32_t           (*PWCFUNCPTR0)(void_t);
typedef s32_t           (*PWCFUNCPTR2)(u32_t arg1, u32_t arg2);
typedef s32_t           (*PWCFUNCPTR3)(u32_t arg1, u32_t arg2, u32_t arg3);


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

