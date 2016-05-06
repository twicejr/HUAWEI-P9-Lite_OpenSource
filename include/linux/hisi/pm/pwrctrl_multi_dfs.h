#ifndef __PWRCTRL_MULTI_DFS_H__
#define __PWRCTRL_MULTI_DFS_H__

#include <linux/hisi/pm/pwrctrl_multi_def.h>
/*#include "drv_dpm.h"*/

/*
 *  DFS return types
 */
#define dfs_ret                 int
#define DFS_INVALID_ID          (-1)

/*
 *  DFS Logs
 */
#define DFS_LOG_INFO(fmt, arg0, arg1, arg2)     \
    PWC_TRACE(PWC_LOG_INFO,    fmt, arg0, arg1, arg2, 0, 0, 0)

#define DFS_LOG_WARNING(fmt, arg0, arg1, arg2)  \
    PWC_TRACE(PWC_LOG_WARNING, fmt, arg0, arg1, arg2, 0, 0, 0)

#define DFS_LOG_ERROR(fmt, arg0, arg1, arg2)    \
    PWC_TRACE(PWC_LOG_ERROR,   fmt, arg0, arg1, arg2, 0, 0, 0)

#define DFS_LOG_MEM(info, addr, size)           \
    PWC_LOG_MEM(info, addr, size)

/*
 *  DFS state mask and operations.
 */
typedef enum
{
    INITED      = 0x1,
    DVFS_ENABLE = 0x2,
    AVS_ENABLE  = 0x4,
    DFS_ENABLE  = 0x8,
    LOCKED      = 0x10
} dfs_state_mask;

typedef enum
{
    BUS_DFS_BIT_ACPU = 0,
    BUS_DFS_BIT_CCPU = 16,
    BUS_DFS_BIT_MAX  = 32
}BUS_DFS_BIT_DEF;

typedef enum
{
    DFS_CORE_MCU  = 0x0,
    DFS_CORE_CCPU = 0x1,
    DFS_CORE_ACPU = 0x2,
    DFS_CORE_HIFI = 0x3,
    DFS_CORE_MAX
}DFS_CORE_ID;

#define BUS_DFS_BIT_MASK (0x10001)

#define DFS_STATE_INIT(x, v)        ((x) = (v))
#define DFS_STATE_SET(x, s)         (pwc_set_bits((u32_t)&(x), (s)))
#define DFS_STATE_CLR(x, s)         (pwc_clr_bits((u32_t)&(x), (s)))
#define DFS_STATE_IS(x, s)          (pwc_is_bits_set((u32_t)&(x), (s)))

/*
 *  DFS Device
 */
#define DFS_DEVICE_ID_ACPU          (0)
#define DFS_DEVICE_ID_CCPU          (1)
#define DFS_DEVICE_ID_DDR           (2)
#define DFS_DEVICE_ID_GPU           (3)
#define DFS_DEVICE_ID_BUS           (4)
#define DFS_DEVICE_ID_BUSLOW        (5)
#define DFS_DEVICE_ID_MDMNOC        (6)
/*如果增加，请更新END*/
#define DFS_DEVICE_ID_END           DFS_DEVICE_ID_MDMNOC

/*
 *  DFS Device Policy
 */
#define DFS_POLICY_ID_ACPU          (0)
#define DFS_POLICY_ID_CCPU          (1)
#define DFS_POLICY_ID_DDR           (2)
#define DFS_POLICY_ID_GPU           (3)
#define DFS_POLICY_ID_BUS           (4)
#define DFS_POLICY_ID_BUSLOW        (5)
#define DFS_POLICY_ID_MDMNOC        (6)

/*
 *  DFS Device QoS
 */
#define DFS_QOS_ID_ACPU_MINFREQ     (0 /*与 DFS_QOS_ID_ACPU_MINFREQ_E 一致*/)
#define DFS_QOS_ID_ACPU_MAXFREQ     (1 /*与 DFS_QOS_ID_ACPU_MAXFREQ_E 一致*/)
#define DFS_QOS_ID_CCPU_MINFREQ     (2 /*与 DFS_QOS_ID_CCPU_MINFREQ_E 一致*/)
#define DFS_QOS_ID_CCPU_MAXFREQ     (3 /*与 DFS_QOS_ID_CCPU_MAXFREQ_E 一致*/)
#define DFS_QOS_ID_DDR_MINFREQ      (4 /*与 DFS_QOS_ID_DDR_MINFREQ_E 一致*/)
#define DFS_QOS_ID_DDR_MAXFREQ      (5 /*与 DFS_QOS_ID_DDR_MAXFREQ_E 一致*/)
#define DFS_QOS_ID_GPU_MINFREQ      (6 /*与 DFS_QOS_ID_GPU_MINFREQ_E 一致*/)
#define DFS_QOS_ID_GPU_MAXFREQ      (7 /*与 DFS_QOS_ID_GPU_MAXFREQ_E 一致*/)
#define DFS_QOS_ID_BUS_MINFREQ      (8 /*与 DFS_QOS_ID_BUS_MINFREQ_E 一致*/)
#define DFS_QOS_ID_BUS_MAXFREQ      (9 /*与 DFS_QOS_ID_BUS_MAXFREQ_E 一致*/)

/*新增DFS Device QOS ID*/
enum DFS_QOS_ID
{
    DFS_QOS_ID_START = DFS_QOS_ID_BUS_MAXFREQ,
    DFS_QOS_ID_BUSLOW_MINFREQ,
    DFS_QOS_ID_BUSLOW_MAXFREQ,
    DFS_QOS_ID_MDMNOC_MINFREQ,
    DFS_QOS_ID_MDMNOC_MAXFREQ,
    DFS_QOS_ID_END
};
/*新增PM Device QOS ID*/
enum PM_QOS_ID
{
    PM_QOS_ID_START = DFS_QOS_ID_END,
    PM_QOS_ID_HARQMEM,
    PM_QOS_ID_SYSNOC,
    PM_QOS_ID_END
};


#ifdef FORTEST
#define DFS_DEVICE_ACPU_NAME        "a"
#define DFS_DEVICE_CCPU_NAME        "c"
#define DFS_DEVICE_DDR_NAME         "d"
#define DFS_DEVICE_GPU_NAME         "g"
#define DFS_DEVICE_BUS_NAME         "b"
#define DFS_DEVICE_BUSLOW_NAME      "bl"
#define DFS_DEVICE_MDMNOC_NAME      "mdmnoc"

#define DFS_POLICY_ACPU_NAME        "ap"
#define DFS_POLICY_CCPU_NAME        "cp"
#define DFS_POLICY_DDR_NAME         "dp"
#define DFS_POLICY_GPU_NAME         "gp"
#define DFS_POLICY_BUS_NAME         "bp"
#define DFS_POLICY_BUSLOW_NAME      "blp"
#define DFS_POLICY_MDMNOC_NAME      "mdmnocp"

#define DFS_QOS_ACPU_MINFREQ_NAME   "ai"
#define DFS_QOS_ACPU_MAXFREQ_NAME   "aa"
#define DFS_QOS_CCPU_MINFREQ_NAME   "ci"
#define DFS_QOS_CCPU_MAXFREQ_NAME   "ca"
#define DFS_QOS_DDR_MINFREQ_NAME    "di"
#define DFS_QOS_DDR_MAXFREQ_NAME    "da"
#define DFS_QOS_GPU_MINFREQ_NAME    "gi"
#define DFS_QOS_GPU_MAXFREQ_NAME    "ga"
/*名字长度不能超过DFS_QOS_OBJ_NAME_SIZE*/
#define DFS_QOS_BUS_MINFREQ_NAME    "bi"
#define DFS_QOS_BUS_MAXFREQ_NAME    "ba"
#define DFS_QOS_BUSLOW_MINFREQ_NAME  "bli"
#define DFS_QOS_BUSLOW_MAXFREQ_NAME  "bla"
#define DFS_QOS_MDMNOC_MINFREQ_NAME   "mdmnoc_minfreq"
#define DFS_QOS_MDMNOC_MAXFREQ_NAME   "mdmnoc_maxfreq"

#else

#define DFS_DEVICE_ACPU_NAME        "acpu"
#define DFS_DEVICE_CCPU_NAME        "ccpu"
#define DFS_DEVICE_DDR_NAME         "ddr"
#define DFS_DEVICE_GPU_NAME         "gpu"
#define DFS_DEVICE_BUS_NAME         "bus"
#define DFS_DEVICE_BUSLOW_NAME      "buslow"
#define DFS_DEVICE_MDMNOC_NAME      "mdmnoc"

#define DFS_POLICY_ACPU_NAME        "acpu_policy"
#define DFS_POLICY_CCPU_NAME        "ccpu_policy"
#define DFS_POLICY_DDR_NAME         "ddr_policy"
#define DFS_POLICY_GPU_NAME         "gpu_policy"
#define DFS_POLICY_BUS_NAME         "bus_policy"
#define DFS_POLICY_BUSLOW_NAME      "buslow_policy"
#define DFS_POLICY_MDMNOC_NAME      "mdmnocp"

#define DFS_QOS_ACPU_MINFREQ_NAME   "acpu_minfreq"
#define DFS_QOS_ACPU_MAXFREQ_NAME   "acpu_maxfreq"
#define DFS_QOS_CCPU_MINFREQ_NAME   "ccpu_minfreq"
#define DFS_QOS_CCPU_MAXFREQ_NAME   "ccpu_maxfreq"
#define DFS_QOS_DDR_MINFREQ_NAME    "ddr_minfreq"
#define DFS_QOS_DDR_MAXFREQ_NAME    "ddr_maxfreq"
#define DFS_QOS_GPU_MINFREQ_NAME    "gpu_minfreq"
#define DFS_QOS_GPU_MAXFREQ_NAME    "gpu_maxfreq"
/*名字长度不能超过DFS_QOS_OBJ_NAME_SIZE*/
#define DFS_QOS_BUS_MINFREQ_NAME    "bus_minfreq"
#define DFS_QOS_BUS_MAXFREQ_NAME    "bus_maxfreq"
#define DFS_QOS_BUSLOW_MINFREQ_NAME  "buslow_minfreq"
#define DFS_QOS_BUSLOW_MAXFREQ_NAME  "buslow_maxfreq"
#define DFS_QOS_MDMNOC_MINFREQ_NAME   "mdmnoc_minfreq"
#define DFS_QOS_MDMNOC_MAXFREQ_NAME   "mdmnoc_maxfreq"
#endif

/*bus dfs freq def*/
#define DFS_BUS_FREQ_SYS (300*1000)
#define DFS_BUS_FREQ_MAX (150*1000)
#define DFS_BUS_FREQ_MIN (75*1000)
#define DFS_BUSLOW_FREQ_MAX (100*1000)
#define DFS_BUSLOW_FREQ_MIN (50*1000)

#endif
