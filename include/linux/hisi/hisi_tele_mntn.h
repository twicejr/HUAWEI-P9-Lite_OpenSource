/******************************************************************************

                  版权所有 (C), 2001-2011, 华为技术有限公司

 ******************************************************************************
  文 件 名   : hisi_tele_mntn.h
  版 本 号   : 初稿
  作    者   : hisi_tele_mntn.h
  生成日期   : 2014年11月22日
  最近修改   :
  功能描述   : bsp_tele_mntn.h 的头文件
  函数列表   :
  修改历史   :
  1.日    期   : 2014年11月22日
    作    者   : hisi_tele_mntn.h
    修改内容   : 创建文件
  2.注    意   : 如下几个文件内容必须完全相同
                 vendor\hisi\confidential\lpmcu\include\hisi_tele_mntn.h
                 bootable\bootloader\legacy\include\hisi_tele_mntn.h
                 kernel\include\linux\hisi\hisi_tele_mntn.h

******************************************************************************/

/*****************************************************************************
  1 其他头文件包含
*****************************************************************************/

#ifndef __HISI_TELE_MNTN_H__
#define __HISI_TELE_MNTN_H__

#ifdef __cplusplus
#if __cplusplus
extern "C" {
#endif
#endif



/*****************************************************************************
  2 宏定义
*****************************************************************************/
#define ACORE_CPUIDLE_CUR_CPU_NUM       (8)
#define PERI_SLEEP_CUR_STATE_NUM        (5)
#define VOTE_STAT_LOCK                  (1)   /*投票不允许单板睡*/
#define VOTE_STAT_UNLOCK                (0)   /*去投票允许单板睡*/
#define LPMCU_TICKMARK_BUF_SIZE         (32)

/*****************************************************************************
  3 枚举定义
*****************************************************************************/
/*

说明:

extern int DRV_TELE_MNTN_WRITE_LOG(
            TELE_MNTN_TYPE_ID type_id,
            unsigned int len,
            void *data);

def type_id 与  最大len长度 data解析类型 的对应关系:

    TELE_MNTN_DEF_STR 对应的data解析类型 和 最大len长度:
            U8 tmp[64]
            len = 64 Bytes

    TELE_MNTN_DEF_U8 对应的data解析类型 和 最大len长度:
            struct
            {
                U8 tmp0;
                U8 tmp1;
                U8 tmp2;
                U8 tmp3;
                U8 tmp4;
                U8 tmp5;
                U8 tmp6;
                U8 tmp7;
            }
            len = 8 Bytes

    TELE_MNTN_DEF_U16 对应的data解析类型 和 最大len长度:
            struct
            {
                U16 tmp0;
                U16 tmp1;
                U16 tmp2;
                U16 tmp3;
                U16 tmp4;
                U16 tmp5;
                U16 tmp6;
                U16 tmp7;
            }
            len = 16 Bytes

    TELE_MNTN_DEF_U32 对应的data解析类型 和 最大len长度:
            struct
            {
                U32 tmp0;
                U32 tmp1;
                U32 tmp2;
                U32 tmp3;
                U32 tmp4;
                U32 tmp5;
                U32 tmp6;
                U32 tmp7;
            }
            len = 32 Bytes

    TELE_MNTN_DEF_U64 对应的data解析类型 和 最大len长度:
            struct
            {
                U64 tmp0;
                U64 tmp1;
                U64 tmp2;
                U64 tmp3;
            }
            len = 32 Bytes

*/
typedef enum
{
    TELE_MNTN_TYPE_RESERVED = -1,
    /*其他用途，保留*/
    TELE_MNTN_NVME_LOGCAT = 0,
    TELE_MNTN_NVME_WAKEUP_ACPU,

    /*默认type_id 对应固定的数据解析类型和默认的数据最大长度，
    工具已默认的数据解析类型解析，多模块可重复使用*/
    TELE_MNTN_DEF_STR = 5,    /*见说明*/
    TELE_MNTN_DEF_U8,         /*见说明*/
    TELE_MNTN_DEF_U16,        /*见说明*/
    TELE_MNTN_DEF_U32,        /*见说明*/
    TELE_MNTN_DEF_U64,        /*见说明*/

    /*各模块自定义type_id 对应的数据解析类型和数据长度由各模块自己定义的结构体决定，
    如果没有结构体定义，工具以码流方式解析*/
    TELE_MNTN_SLEEPWAKE_CCPU = 15,
    TELE_MNTN_NOTSLEEPREASON_CCPU,
    TELE_MNTN_SLEEPWAKE_MCU,
    TELE_MNTN_NOTSLEEPREASON_MCU,
    TELE_MNTN_PUPD_CCPU,
    TELE_MNTN_WFIFAIL_CCPU,  /*20*/
    TELE_MNTN_PUPD_ACPU,
    TELE_MNTN_WFIFAIL_ACPU,
    TELE_MNTN_PUPD_HIFI,
    TELE_MNTN_WFIFAIL_HIFI,
    TELE_MNTN_CPUIDLE,  /*25*/
    TELE_MNTN_VOTE_CCPU,
    TELE_MNTN_VOTE_MCU,
    TELE_MNTN_ICC_WAKE_ACPU,
    TELE_MNTN_ICC_WAKE_CCPU,
    TELE_MNTN_IPC_MCU,  /*30*/
    TELE_MNTN_DFS_DDR,
    TELE_MNTN_PLI_DDR,
    TELE_MNTN_MAXFREQ_REQ_DDR,
    TELE_MNTN_MINFREQ_REQ_DDR,
    TELE_MNTN_QOS_DDR_MCU,  /*35*/
    TELE_MNTN_QOS_DDR_CCPU,
    TELE_MNTN_QOS_DDR_ACPU,
    TELE_MNTN_DFS_CCPU,
    TELE_MNTN_PLI_CCPU,
    TELE_MNTN_QOS_CCPU,  /*40*/
    TELE_MNTN_DFS_ACPU,
    TELE_MNTN_DRX,
    TELE_MNTN_PLI_ACPU,
    TELE_MNTN_SR_ACPU,
	TELE_MNTN_DFS_GPU,
	TELE_MNTN_RESET_HIFI,
    TELE_MNTN_PUPD_IOMCU,
    TELE_MNTN_WFIFAIL_IOMCU,
    TELE_MNTN_PUPD_REGULATOR,

    TELE_MNTN_TEMPERATURE = 52,

	TELE_MNTN_LPREG_SAVE = 62,
    TELE_MNTN_LPREG_DUMP = 63,
    TELE_MNTN_TYPE_BUTT
}TELE_MNTN_TYPE_ID;

/*****************************************************************************
  4 消息头定义
*****************************************************************************/


/*****************************************************************************
  5 消息定义
*****************************************************************************/


/*****************************************************************************
  6 STRUCT定义
*****************************************************************************/

/*************************LPMCU telemntn log begin***************************/
typedef struct LPMCU_TELE_MNTN_PU_STRU_S
{
    unsigned int wakeCount;
    unsigned int wakeSrc;
}LPMCU_TELE_MNTN_PU_STRU;

typedef struct LPMCU_TELE_MNTN_PD_STRU_S
{
    unsigned int sleepCount;
    unsigned int sleepFlag;
}LPMCU_TELE_MNTN_PD_STRU;

typedef struct LPMCU_TELE_MNTN_WFIFAIL_STRU_S
{
    unsigned int WFIFailCount;
}LPMCU_TELE_MNTN_WFIFAIL_STRU;

typedef struct LPMCU_TELE_MNTN_PUPD_STRU_S
{
    LPMCU_TELE_MNTN_PD_STRU pdStat;
    LPMCU_TELE_MNTN_PU_STRU puStat;
    LPMCU_TELE_MNTN_WFIFAIL_STRU WFIFailStat;
    unsigned int pdSliceTime;
    unsigned int puSliceTime;
    unsigned int WFIFailSliceTime;
}LPMCU_TELE_MNTN_PUPD_STRU;

typedef struct LPMCU_TELE_MNTN_SLEEPWAKESTAT_STRU_S
{
    int sX;
    unsigned int sleepCount;
    unsigned int wakeCount;
    unsigned int sleepSliceTime;
    unsigned int wakeSliceTime;
    unsigned int wakeSrc0;
    unsigned int wakeSrc1;
}LPMCU_TELE_MNTN_SLEEPWAKESTAT_STRU;

typedef struct LPMCU_TELE_MNTN_NOTSLEEPREASON_STRU_S
{
    int canSleepRet;
}LPMCU_TELE_MNTN_NOTSLEEPREASON_STRU;

typedef struct LPMCU_TELE_MNTN_SLEEPWAKEINFO_STRU_S
{
    LPMCU_TELE_MNTN_SLEEPWAKESTAT_STRU stat;
    LPMCU_TELE_MNTN_NOTSLEEPREASON_STRU notSleepReason;
}LPMCU_TELE_MNTN_SLEEPWAKEINFO_STRU;

typedef struct LPMCU_TELE_MNTN_SLEEPWAKE_STRU_S
{
    int sX;
    LPMCU_TELE_MNTN_SLEEPWAKEINFO_STRU info;
}LPMCU_TELE_MNTN_SLEEPWAKE_STRU;


typedef struct LPMCU_TELE_MNTN_DFS_QOSINFO_STRU_S
{
    short cmd_id;
    short qos_id;
    int req_id;
    int ret;
    unsigned int task_id;  /*CCPU:task_id; MCU:core_id*/
    unsigned int tag_freq;
    unsigned int new_freq;
    unsigned int max_freq;
    unsigned int min_freq;
}LPMCU_TELE_MNTN_DFS_QOSINFO_STRU;

typedef struct LPMCU_TELE_MNTN_DFS_QOS_STRU_S
{
    LPMCU_TELE_MNTN_DFS_QOSINFO_STRU info;
    unsigned int qosSliceTime;
}LPMCU_TELE_MNTN_DFS_QOS_STRU;

typedef struct LPMCU_TELE_MNTN_DFS_POLICYINFO_STRU_S
{
    unsigned int load;
    unsigned int target_freq;
}LPMCU_TELE_MNTN_DFS_POLICYINFO_STRU;

typedef struct LPMCU_TELE_MNTN_DFS_POLICY_STRU_S
{
    LPMCU_TELE_MNTN_DFS_POLICYINFO_STRU info;
    unsigned int policySliceTime;
}LPMCU_TELE_MNTN_DFS_POLICY_STRU;

typedef struct LPMCU_TELE_MNTN_DFS_TARGETINFO_STRU_S
{
    char old_freq;
    char new_freq;
    char tag_freq;
    char id;
}LPMCU_TELE_MNTN_DFS_TARGETINFO_STRU;

typedef struct LPMCU_TELE_MNTN_DFS_TARGET_STRU_S
{
    LPMCU_TELE_MNTN_DFS_TARGETINFO_STRU info;
    unsigned int targetSliceTime;
}LPMCU_TELE_MNTN_DFS_TARGET_STRU;

typedef struct LPMCU_TELE_MNTN_DFS_DDR_STRU_S
{
    LPMCU_TELE_MNTN_DFS_QOS_STRU qos;
    LPMCU_TELE_MNTN_DFS_POLICY_STRU policy;
    LPMCU_TELE_MNTN_DFS_TARGET_STRU target;
}LPMCU_TELE_MNTN_DFS_DDR_STRU;

typedef struct LPMCU_TELE_MNTN_DFS_ACPU_STRU_S
{
    LPMCU_TELE_MNTN_DFS_TARGET_STRU target;
}LPMCU_TELE_MNTN_DFS_ACPU_STRU;

typedef struct LPMCU_TELE_MNTN_DFS_GPU_STRU_S
{
    LPMCU_TELE_MNTN_DFS_TARGET_STRU target;
}LPMCU_TELE_MNTN_DFS_GPU_STRU;

typedef struct LPMCU_TELE_MNTN_IPCRECVSTATINFO_STRU_S
{
    unsigned char ipc_id;
    unsigned char mailbox_id;
    unsigned char obj;  /*表示目标方，即接收方*/
    unsigned char mode; /*表示接收模式，即同步接收或异步接收*/
    unsigned int data0;
    unsigned int data1;
    unsigned int handle_slice;
}LPMCU_TELE_MNTN_IPCRECVSTATINFO_STRU;

typedef struct LPMCU_TELE_MNTN_IPCSENDSTATINFO_STRU_S
{
    unsigned char ipc_id;
    unsigned char mailbox_id;
    unsigned char obj;  /*表示目标方，即发送目的地*/
    unsigned char mode; /*表示发送模式*/
    unsigned int msg;
}LPMCU_TELE_MNTN_IPCSENDSTATINFO_STRU;

typedef struct LPMCU_TELE_MNTN_IPCSENDEXCEPTION_STRU_S
{
    unsigned char ipc;
    unsigned char mbx;
    unsigned char iclr;
    unsigned char mode;
    unsigned int data0;
    unsigned int data1;
}LPMCU_TELE_MNTN_IPCSENDEXCEPTION_STRU;

typedef struct LPMCU_TELE_MNTN_IPCSTAT_STRU_S
{
    LPMCU_TELE_MNTN_IPCRECVSTATINFO_STRU recv;
    LPMCU_TELE_MNTN_IPCSENDSTATINFO_STRU send;
    LPMCU_TELE_MNTN_IPCSENDEXCEPTION_STRU exp;
    unsigned int recvSliceTime;
    unsigned int sendSliceTime;
}LPMCU_TELE_MNTN_IPCSTAT_STRU;



typedef struct LPMCU_TELE_MNTN_TICKMARK_STRU_S
{
    unsigned int tick[LPMCU_TICKMARK_BUF_SIZE];

}LPMCU_TELE_MNTN_TICKMARK_STRU;

typedef struct LPMCU_TELE_MNTN_NCORE_PU_STRU_S
{
    unsigned int  state;
    unsigned int  up_cnt;
    unsigned short wake_irq;
    unsigned char wake_mbx_id;
    unsigned char wake_mbx_mode;
    unsigned int wake_mbx_data0;
} LPMCU_TELE_MNTN_NCORE_PU_STRU;

typedef struct LPMCU_TELE_MNTN_NCORE_PD_STRU_S
{
    unsigned int  state;
    unsigned int  dn_cnt;
} LPMCU_TELE_MNTN_NCORE_PD_STRU;

/*hifi/iomcu etc*/
typedef struct LPMCU_TELE_MNTN_NCORE_PUPD_STRU_S
{
    LPMCU_TELE_MNTN_NCORE_PU_STRU pu;
    LPMCU_TELE_MNTN_NCORE_PD_STRU pd;
}LPMCU_TELE_MNTN_NCORE_PUPD_STRU;

typedef struct LPMCU_TELE_MNTN_MBX_EXP_STATE_STRU_S
{
	unsigned char source;
	unsigned char dstatus;
	unsigned char mode;
	unsigned char iclr;
	unsigned int data0;
	unsigned int data1;
} LPMCU_TELE_MNTN_MBX_EXP_STATE_STRU;

typedef struct LPMCU_TELE_MNTN_IOMCU_RESET_STRU_S
{
    LPMCU_TELE_MNTN_MBX_EXP_STATE_STRU mailbox;
    //add vote peri\sys_state state
} LPMCU_TELE_MNTN_IOMCU_RESET_STRU;

typedef struct LPMCU_TELE_MNTN_VOTESTAT_STRU_S
{
    unsigned char stat;             /*VOTE_STAT_LOCK 或者 VOTE_STAT_UNLOCK*/
    unsigned char clientId;
    unsigned char stateId;
    unsigned char reserved;
    unsigned int voteMap;
}LPMCU_TELE_MNTN_VOTESTAT_STRU;

typedef struct LPMCU_TELE_MNTN_VOTE_STRU_S
{
    LPMCU_TELE_MNTN_VOTESTAT_STRU voteStat;
    unsigned int sliceTime;
}LPMCU_TELE_MNTN_VOTE_STRU;

typedef struct LPMCU_TELE_MNTN_TEMPERATURE_INFO_STRU_S
{
    unsigned short vol;
    short tem;
    unsigned int chan;
}LPMCU_TELE_MNTN_TEMPERATURE_INFO_STRU;

typedef struct LPMCU_TELE_MNTN_TEMPERATURE_STRU_S
{
    LPMCU_TELE_MNTN_TEMPERATURE_INFO_STRU info;
    unsigned int temSliceTime;
}LPMCU_TELE_MNTN_TEMPERATURE_STRU;

typedef struct LPMCU_TELE_MNTN_STRU_S
{
    LPMCU_TELE_MNTN_TICKMARK_STRU tickMask;
    LPMCU_TELE_MNTN_PUPD_STRU ccore;
    LPMCU_TELE_MNTN_PUPD_STRU acore;
    LPMCU_TELE_MNTN_SLEEPWAKE_STRU mcu;
    LPMCU_TELE_MNTN_DFS_DDR_STRU dfsDdr;
    LPMCU_TELE_MNTN_DFS_ACPU_STRU dfsAcpu;
    LPMCU_TELE_MNTN_DFS_GPU_STRU dfsGpu;
    LPMCU_TELE_MNTN_IPCSTAT_STRU ipc;
    LPMCU_TELE_MNTN_NCORE_PUPD_STRU hifi;
    LPMCU_TELE_MNTN_NCORE_PUPD_STRU iomcu;
    LPMCU_TELE_MNTN_VOTE_STRU vote[PERI_SLEEP_CUR_STATE_NUM];
    LPMCU_TELE_MNTN_TEMPERATURE_STRU tem;
    LPMCU_TELE_MNTN_IOMCU_RESET_STRU iomcu_rst;
    /*请在此处添加新的结构体*/
}LPMCU_TELE_MNTN_STRU;

/*************************LPMCU telemntn log end*****************************/


/*************************ACORE telemntn log begin***************************/
typedef struct ACORE_TELE_MNTN_DFS_ACPU_BOOSTINFO_STRU_S
{
    unsigned int cpu;
    unsigned int tag_freq;
    unsigned int new_freq;
    unsigned int min_freq;
    unsigned int max_freq;
}ACORE_TELE_MNTN_DFS_ACPU_BOOSTINFO_STRU;


typedef struct ACORE_TELE_MNTN_DFS_ACPU_POLICYINFO_STRU_S
{
    unsigned int cpu;
    unsigned int tag_freq;
    unsigned int new_freq;
    unsigned int min_freq;
    unsigned int max_freq;
    unsigned char load[ACORE_CPUIDLE_CUR_CPU_NUM];
}ACORE_TELE_MNTN_DFS_ACPU_POLICYINFO_STRU;

typedef struct ACORE_TELE_MNTN_DFS_ACPU_BOOST_STRU_S
{
    ACORE_TELE_MNTN_DFS_ACPU_BOOSTINFO_STRU info;
    unsigned int boostSliceTime;
}ACORE_TELE_MNTN_DFS_ACPU_BOOST_STRU;

typedef struct ACORE_TELE_MNTN_DFS_ACPU_POLICY_STRU_S
{
    ACORE_TELE_MNTN_DFS_ACPU_POLICYINFO_STRU info;
    unsigned int policySliceTime;
}ACORE_TELE_MNTN_DFS_ACPU_POLICY_STRU;

typedef struct ACORE_TELE_MNTN_DFS_ACPU_STRU_S
{
    ACORE_TELE_MNTN_DFS_ACPU_BOOST_STRU boost;
    ACORE_TELE_MNTN_DFS_ACPU_POLICY_STRU policy;
}ACORE_TELE_MNTN_DFS_ACPU_STRU;

typedef struct ACORE_TELE_MNTN_DFS_DDR_QOSINFO_STRU_S
{
    short           cmd_id;
    short           qos_id;
    unsigned short  pid;
    unsigned short  ppid;
    int             tag_val;
    unsigned int    new_freq;
    unsigned int    min_freq;
    unsigned int    max_freq;
}ACORE_TELE_MNTN_DFS_DDR_QOSINFO_STRU;


typedef struct PWC_TELE_MNTN_DFS_DDR_QOS_STRU_S
{
    ACORE_TELE_MNTN_DFS_DDR_QOSINFO_STRU info;
    unsigned int qosSliceTime;
}ACORE_TELE_MNTN_DFS_DDR_QOS_STRU;

typedef struct ACORE_TELE_MNTN_DFS_DDR_STRU_S
{
    ACORE_TELE_MNTN_DFS_DDR_QOS_STRU qos;
}ACORE_TELE_MNTN_DFS_DDR_STRU;

typedef struct ACORE_TELE_MNTN_STRU_S
{
    ACORE_TELE_MNTN_DFS_DDR_STRU dfsDdr;
    ACORE_TELE_MNTN_DFS_ACPU_STRU dfsAcpu;
}ACORE_TELE_MNTN_STRU;

/*****************************************************************************
  7 UNION定义
*****************************************************************************/


/*****************************************************************************
  8 OTHERS定义
*****************************************************************************/


/*****************************************************************************
  9 全局变量声明
*****************************************************************************/
/*注意: 使用前请先判断指针是否为空*/
extern LPMCU_TELE_MNTN_STRU *p_lpmcu_tele_mntn;
extern LPMCU_TELE_MNTN_STRU *p_fastboot_lpmcu_tele_mntn;
extern ACORE_TELE_MNTN_STRU *p_acore_tele_mntn;
/*****************************************************************************
  10 函数声明
*****************************************************************************/
/*****************************************************************************
 函 数 名  : tele_mntn_write_log
 功能描述  : 保存log接口
 输入参数  : TELE_MNTN_TYPE_ID type_id
             u32_t len
             void_t * data
 输出参数  : 无
 返 回 值  : s32_t
 调用函数  :
 被调函数  :
 说    明  : 该函数一次传输len最大值为64字节，建议len为8字节对齐。
             未避免多次调用影响性能，建议一个type_id一次流程的数据封装成结构体，一次性存入telemntn
 举    例  : hifi上电，该完整流程的log记录

             hifi上下电的typeid为 TELE_MNTN_PUPD_HIFI 表示上电和下电，可以分解为两个流程，上电和下电。
             对于上电流程，建议将PWC_TELE_MNTN_PU_STRU填充满后再调用执行tele_mntn_write_log接口，
             不建议一个流程调用执行多次tele_mntn_write_log接口。


             typedef struct PWC_TELE_MNTN_PU_STRU_S
             {
                 u32_t  wakeCount;
                 u32_t  wakeSrc0;
                 u32_t  wakeSrc1;
                 u32_t  wakeSrcIPC;
                 u8_t   wakeSrcGPIO[8];
             }PWC_TELE_MNTN_PU_STRU;

     	     typedef struct PWC_TELE_MNTN_PD_STRU_S
     	     {
     	         u32_t  sleepCount;
     	     }PWC_TELE_MNTN_PD_STRU;

             typedef struct PWC_TELE_MNTN_PUPD_STRU_S
             {
                 PWC_TELE_MNTN_PD_STRU pdStat;
                 PWC_TELE_MNTN_PU_STRU puStat; //该结构体数据log会记录到telemntn中
                 u32_t pdSliceTime;
                 u32_t puSliceTime;  //该时间为本地记录时间
             }PWC_TELE_MNTN_PUPD_STRU;

             g_hifi_log = (PWC_TELE_MNTN_PUPD_STRU *)0x25000; //全局变量，指向固定内存空间
             s32_t  pwc_power_up_hifi( void_t )
             {
                 //可维可测部分，先将一次完整流程的log记录到本地
                 g_hifi_log->puStat.wakeCount++;

                 上电处理……

                 //可维可测部分，先将一次完整流程的log记录到本地
                 g_hifi_log->puStat.wakeSrc0 = xxx;
                 g_hifi_log->puStat.wakeSrcIPC = xxx;
                 g_hifi_log->puStat.wakeSrcGPIO = xxx;
                 g_hifi_log->puSliceTime = get_slice_time();

                 //将该次完整流程记录到telemntn中，不带时间信息
                 (void)tele_mntn_write_log(TELE_MNTN_PUPD_HIFI,sizeof(g_hifi_log->puStat),&(g_hifi_log->puStat));

                 return RET_OK;
             }

 修改历史      :
  1.日    期   : 2014年5月19日
    作    者   : 李彬彬 00186593
    修改内容   : 新生成函数

*****************************************************************************/
#if (defined FASTBOOT_MNTN)
#else
extern int tele_mntn_write_log(TELE_MNTN_TYPE_ID type_id, unsigned int len, const void *data);
#if defined(__CMSIS_RTOS)
extern int tele_mntn_init(void);
extern int tele_mntn_wake_up_acore(void);
#endif
#endif









#ifdef __cplusplus
    #if __cplusplus
        }
    #endif
#endif

#endif /* end of hi6xxx_tele_mntn.h */
