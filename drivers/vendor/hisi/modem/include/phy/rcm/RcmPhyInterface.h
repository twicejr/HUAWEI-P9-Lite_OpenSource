/******************************************************************************

                  版权所有 (C), 2011-2031, 华为技术有限公司

 ******************************************************************************
  文 件 名   : RcmPhyInterface.h
  版 本 号   : 初稿
  作    者   : 吴翔 138719
  生成日期   : 2014年1月20日
  最近修改   :
  功能描述   : RCM和PHY的接口头文件,接口中的时间都是以32K的clock为单位
  函数列表   :
  修改历史   :
  1.日    期   : 2014年1月20日
    作    者   : 吴翔 138719
    修改内容   : 创建文件

******************************************************************************/

#ifndef __RCMPHYINTERFACE_H__
#define __RCMPHYINTERFACE_H__

#ifdef __cplusplus
#if __cplusplus
extern "C" {
#endif
#endif

/*****************************************************************************
  1 其他头文件包含
*****************************************************************************/
#include "product_config.h"

#ifndef LPS_RTT
#include "vos.h"
#include "phyoaminterface.h"
#include "PhyCodecInterface.h"

#else
#define VOS_MSG_HEADER
#endif

#pragma pack(4)

/*****************************************************************************
  2 宏定义
*****************************************************************************/
/*最多支持的RF数目*/
#define RCM_RF_SUPPORT_NUM                      ( RCM_RF_ID_BUTT )

/*最多支持的PHY mode数目*/
#define RCM_MODE_SUPPORT_NUM                    ( RCM_MODE_ID_BUTT )

/*最多支持的MODEM数目*/
#define RCM_MODEM_SUPPORT_NUM                   ( RCM_MODEM_ID_BUTT )

/*最多支持的MODEM数目*/
#define RCM_TAS_MODEM_SUPPORT_NUM               ( RCM_TAS_MODEM_ID_BUTT )

/* 分配队列任务size */
#define RCM_PHY_ASSIGN_BUF_SIZE                 ( 32 )

/* 公共定时计数周期，以32K时钟为单位，必须是2的指数 */
#define RCM_CLOCK_PERIOD                        ( ((VOS_UINT32)0x1)<<31 )

/* 公共定时频率 */
#define RCM_CLOCK_FREQUENCY                     ( 32768 )

/* 无效定时 同时作为最大时长 */
#define RCM_CLOCK_INVALID_VALUE                 ( 0xffffffff )

/* 单次和累积被抢占门限,抢占统计周期无效值(非PS业务统一填此值) */
#define RCM_PRMPT_TH_INVALID_VALUE              ( RCM_CLOCK_INVALID_VALUE )

/* 时间ms转换为32K的计数 输入必须小于0x20000 ms*/
#define RCM_MsToClock( M_uhwTime )              ( (VOS_INT32)( ( ((VOS_UINT32)M_uhwTime) *RCM_CLOCK_FREQUENCY)/1000 ))

/* GPHY TASK ID 对应RCM TASK ID 起始枚举值 */
#define RCM_GPHY_TASK_ID_BEGIN_NUM              ( 0 )

/* WPHY TASK ID 对应RCM TASK ID 起始枚举值 */
#define RCM_WPHY_TASK_ID_BEGIN_NUM              ( 100 )

/* TPHY TASK ID 对应RCM TASK ID 起始枚举值 */
#define RCM_TPHY_TASK_ID_BEGIN_NUM              ( 200 )

/* LPHY TASK ID 对应RCM TASK ID 起始枚举值 */
#define RCM_LPHY_TASK_ID_BEGIN_NUM              ( 300 )

/* CPHY 1X TASK ID 对应RCM TASK ID 起始枚举值 */
#define RCM_CPHY_1X_TASK_ID_BEGIN_NUM           ( 400 )

/* CPHY HRPD TASK ID 对应RCM TASK ID 起始枚举值 */
#define RCM_CPHY_HRPD_TASK_ID_BEGIN_NUM         ( 500 )


/* 一次删除的任务ID最大个数 */
#define RCM_REL_TASK_ID_MAX_NUM                 ( 32 )

/* 各模统一寻呼任务的用于动态优先级调整的失败门限
   G模重选的任务优先级为260，每940ms希望收到一次系统消息。寻呼任务的优先级为300，并且寻呼周期为470ms。
   如果重选与寻呼冲突时，重选希望能够在一个940ms之内收到一次系统消息，即将寻呼任务的优先级提升速度降低
   到每失败两次才能超过重选。根据寻呼任务的优先级提升算法，这里必须将失败门限设置为6 */
#define RCM_PHY_PAGING_FAIL_THD                 ( 6 )

/* 各物理层和RCM间传递XO系数的规格 */
#define RCM_PHY_XO_COEF_NUM                     ( 4 )

/* 为了提高周期任务的精度，PHY传给RCM的周期值扩大的倍数 */
#define EXTEND_PERIOD_TASK_TIMES                ( ((VOS_UINT32)0x1)<<7 )

/* 获得周期任务的整数位 */
#define RCM_GetTaskPeriod( M_uwPeriod )         ( (((VOS_UINT32)M_uwPeriod) & (~( EXTEND_PERIOD_TASK_TIMES - 1 )))>>7 )

/* 获得周期任务的余数位 */
#define RCM_GetTaskRemainder( M_uwPeriod )      ( ((VOS_UINT32)M_uwPeriod) & ( EXTEND_PERIOD_TASK_TIMES - 1 )  )

/* 定义各任务属性，如优先级、是否独占等: GPHY */
#define RCM_GPHY_TASK_PROPERTY_TABLE  \
    { RCM_GPHY_TASK_START,                      RCM_TASK_PRIORITY_BUTT, RCM_TASK_PREEMPTIND_FLAG_BUTT   },\
    { RCM_GPHY_TASK_SEARCHING_MEA,              RCM_TASK_PRIORITY_3,    RCM_TASK_PREEMPTIND_FLAG_VALID  },\
    { RCM_GPHY_TASK_SEARCHING_FBSB,             RCM_TASK_PRIORITY_3,    RCM_TASK_PREEMPTIND_FLAG_INVALID},\
    { RCM_GPHY_TASK_SEARCHING_BCCH_PART,        RCM_TASK_PRIORITY_1_6,  RCM_TASK_PREEMPTIND_FLAG_VALID  },\
    { RCM_GPHY_TASK_SEARCHING_BCCH_WHOLE,       RCM_TASK_PRIORITY_5_5,  RCM_TASK_PREEMPTIND_FLAG_VALID  },\
    { RCM_GPHY_TASK_IDLE_PAGE_NORMAL,           RCM_TASK_PRIORITY_2,    RCM_TASK_PREEMPTIND_FLAG_INVALID},\
    { RCM_GPHY_TASK_IDLE_PAGE_EXT,              RCM_TASK_PRIORITY_2,    RCM_TASK_PREEMPTIND_FLAG_INVALID},\
    { RCM_GPHY_TASK_IDLE_PAGE_REORG,            RCM_TASK_PRIORITY_4,    RCM_TASK_PREEMPTIND_FLAG_VALID  },\
    { RCM_GPHY_TASK_IDLE_SCELL_BCCH_PERIOD,     RCM_TASK_PRIORITY_7,    RCM_TASK_PREEMPTIND_FLAG_VALID  },\
    { RCM_GPHY_TASK_IDLE_NCELL_BCCH_DECODE,     RCM_TASK_PRIORITY_3_7,  RCM_TASK_PREEMPTIND_FLAG_VALID  },\
    { RCM_GPHY_TASK_IDLE_BASIC_CBCH,            RCM_TASK_PRIORITY_3_4,  RCM_TASK_PREEMPTIND_FLAG_VALID  },\
    { RCM_GPHY_TASK_IDLE_EXT_CBCH,              RCM_TASK_PRIORITY_3_4,  RCM_TASK_PREEMPTIND_FLAG_VALID  },\
    { RCM_GPHY_TASK_IDLE_NCELL_FB,              RCM_TASK_PRIORITY_4,    RCM_TASK_PREEMPTIND_FLAG_VALID  },\
    { RCM_GPHY_TASK_IDLE_NCELL_SB,              RCM_TASK_PRIORITY_4,    RCM_TASK_PREEMPTIND_FLAG_INVALID},\
    { RCM_GPHY_TASK_IDLE_CELL_RESELECT,         RCM_TASK_PRIORITY_4,    RCM_TASK_PREEMPTIND_FLAG_VALID  },\
    { RCM_GPHY_TASK_IDLE_BG_MEA,                RCM_TASK_PRIORITY_6,    RCM_TASK_PREEMPTIND_FLAG_VALID  },\
    { RCM_GPHY_TASK_IDLE_BG_FBSB,               RCM_TASK_PRIORITY_5_9,  RCM_TASK_PREEMPTIND_FLAG_VALID  },\
    { RCM_GPHY_TASK_IDLE_BG_BCCH,               RCM_TASK_PRIORITY_5_9,  RCM_TASK_PREEMPTIND_FLAG_VALID  },\
    { RCM_GPHY_TASK_IDLE_INTERRAT_WMEA,         RCM_TASK_PRIORITY_4,    RCM_TASK_PREEMPTIND_FLAG_VALID  },\
    { RCM_GPHY_TASK_IDLE_INTERRAT_TMEA,         RCM_TASK_PRIORITY_4,    RCM_TASK_PREEMPTIND_FLAG_VALID  },\
    { RCM_GPHY_TASK_IDLE_INTERRAT_LMEA,         RCM_TASK_PRIORITY_4,    RCM_TASK_PREEMPTIND_FLAG_VALID  },\
    { RCM_GPHY_TASK_IDLE_BG_WMEA,               RCM_TASK_PRIORITY_6,    RCM_TASK_PREEMPTIND_FLAG_VALID  },\
    { RCM_GPHY_TASK_IDLE_BG_TMEA,               RCM_TASK_PRIORITY_6,    RCM_TASK_PREEMPTIND_FLAG_VALID  },\
    { RCM_GPHY_TASK_IDLE_BG_LMEA,               RCM_TASK_PRIORITY_6,    RCM_TASK_PREEMPTIND_FLAG_VALID  },\
    { RCM_GPHY_TASK_IDLE_FULLLIST_MEA,          RCM_TASK_PRIORITY_6,    RCM_TASK_PREEMPTIND_FLAG_VALID  },\
    { RCM_GPHY_TASK_TUNING_RACH,                RCM_TASK_PRIORITY_1,    RCM_TASK_PREEMPTIND_FLAG_INVALID},\
    { RCM_GPHY_TASK_TUNING_PRACH,               RCM_TASK_PRIORITY_1,    RCM_TASK_PREEMPTIND_FLAG_INVALID},\
    { RCM_GPHY_TASK_PBCCH,                      RCM_TASK_PRIORITY_5,    RCM_TASK_PREEMPTIND_FLAG_INVALID},\
    { RCM_GPHY_TASK_PPCH,                       RCM_TASK_PRIORITY_5,    RCM_TASK_PREEMPTIND_FLAG_INVALID},\
    { RCM_GPHY_TASK_TUNING_SINGLE_BLOCK,        RCM_TASK_PRIORITY_1,    RCM_TASK_PREEMPTIND_FLAG_INVALID},\
    { RCM_GPHY_TASK_DCH_CS,                     RCM_TASK_PRIORITY_1,    RCM_TASK_PREEMPTIND_FLAG_VALID  },\
    { RCM_GPHY_TASK_DCH_PS,                     RCM_TASK_PRIORITY_5,    RCM_TASK_PREEMPTIND_FLAG_VALID  },\
    { RCM_GPHY_TASK_LOST_NET,                   RCM_TASK_PRIORITY_2_5,  RCM_TASK_PREEMPTIND_FLAG_INVALID},\
    { RCM_GPHY_TASK_INACTIVE,                   RCM_TASK_PRIORITY_3_5,  RCM_TASK_PREEMPTIND_FLAG_INVALID},\
    { RCM_GPHY_TASK_IDLE_SCELL_BCCH_RESEL,      RCM_TASK_PRIORITY_1_6,  RCM_TASK_PREEMPTIND_FLAG_VALID  },\
    { RCM_GPHY_TASK_IDLE_SCELL_BCCH_ENH,        RCM_TASK_PRIORITY_3_5,  RCM_TASK_PREEMPTIND_FLAG_VALID  },\
    { RCM_GPHY_TASK_IDLE_NCELL_BCCH_RESEL,      RCM_TASK_PRIORITY_3,    RCM_TASK_PREEMPTIND_FLAG_VALID  },\
    { RCM_GPHY_TASK_IDLE_NCELL_BCCH_BG,         RCM_TASK_PRIORITY_5_9,  RCM_TASK_PREEMPTIND_FLAG_VALID  },\
    { RCM_GPHY_TASK_IDLE_UNFIX_NCELL_SB,        RCM_TASK_PRIORITY_4,    RCM_TASK_PREEMPTIND_FLAG_VALID  },\
    { RCM_GPHY_TASK_PSRCH_FIRST_CELL_FBSB,      RCM_TASK_PRIORITY_3,    RCM_TASK_PREEMPTIND_FLAG_INVALID},\
    { RCM_GPHY_TASK_PSRCH_FIRST_CELL_BCCH,      RCM_TASK_PRIORITY_1_6,  RCM_TASK_PREEMPTIND_FLAG_VALID  },\
    { RCM_GPHY_TASK_PSRCH_FIRST_CELL_PCH,       RCM_TASK_PRIORITY_3,    RCM_TASK_PREEMPTIND_FLAG_INVALID},\
    { RCM_GPHY_TASK_PSRCH_NEXT_CELL_FBSB,       RCM_TASK_PRIORITY_4,    RCM_TASK_PREEMPTIND_FLAG_VALID  },\
    { RCM_GPHY_TASK_PSRCH_NEXT_CELL_BCCH,       RCM_TASK_PRIORITY_4,    RCM_TASK_PREEMPTIND_FLAG_VALID  },\
    { RCM_GPHY_TASK_IDLE_PLMN_LIST_FBSB,        RCM_TASK_PRIORITY_4_9,  RCM_TASK_PREEMPTIND_FLAG_VALID  },\
    { RCM_GPHY_TASK_IDLE_NET_SCAN_FBSB,         RCM_TASK_PRIORITY_8,    RCM_TASK_PREEMPTIND_FLAG_VALID  },\
    { RCM_GPHY_TASK_IDLE_NBCCH_PLMN_LIST,       RCM_TASK_PRIORITY_4_9,  RCM_TASK_PREEMPTIND_FLAG_VALID  },\
    { RCM_GPHY_TASK_IDLE_NBCCH_NET_SCAN,        RCM_TASK_PRIORITY_8,    RCM_TASK_PREEMPTIND_FLAG_VALID  },\
    { RCM_GPHY_TASK_END,                        RCM_TASK_PRIORITY_BUTT, RCM_TASK_PREEMPTIND_FLAG_BUTT   }


/* 定义各任务属性，如优先级、是否独占等: WPHY */
#define RCM_WPHY_TASK_PROPERTY_TABLE  \
    { RCM_WPHY_TASK_LIST,                  RCM_TASK_PRIORITY_BUTT, RCM_TASK_PREEMPTIND_FLAG_BUTT    },\
    { RCM_WPHY_TASK_FREE,                  RCM_TASK_PRIORITY_3,    RCM_TASK_PREEMPTIND_FLAG_VALID   },\
    { RCM_WPHY_TASK_CPICH_PI,              RCM_TASK_PRIORITY_2,    RCM_TASK_PREEMPTIND_FLAG_INVALID },\
    { RCM_WPHY_TASK_CPICH_MEAS,            RCM_TASK_PRIORITY_4,    RCM_TASK_PREEMPTIND_FLAG_VALID   },\
    { RCM_WPHY_TASK_CPICH_PCCPCH,          RCM_TASK_PRIORITY_3,    RCM_TASK_PREEMPTIND_FLAG_VALID   },\
    { RCM_WPHY_TASK_CPICH_BG,              RCM_TASK_PRIORITY_6,    RCM_TASK_PREEMPTIND_FLAG_VALID   },\
    { RCM_WPHY_TASK_CPICH_CBS,             RCM_TASK_PRIORITY_8_1,  RCM_TASK_PREEMPTIND_FLAG_VALID   },\
    { RCM_WPHY_TASK_FACH_COMM,             RCM_TASK_PRIORITY_5,    RCM_TASK_PREEMPTIND_FLAG_VALID   },\
    { RCM_WPHY_TASK_FACH_RA,               RCM_TASK_PRIORITY_5,    RCM_TASK_PREEMPTIND_FLAG_VALID   },\
    { RCM_WPHY_TASK_FACH_PCCPCH,           RCM_TASK_PRIORITY_3,    RCM_TASK_PREEMPTIND_FLAG_VALID   },\
    { RCM_WPHY_TASK_DPCH_COMM,             RCM_TASK_PRIORITY_5,    RCM_TASK_PREEMPTIND_FLAG_VALID   },\
    { RCM_WPHY_TASK_END,                   RCM_TASK_PRIORITY_BUTT, RCM_TASK_PREEMPTIND_FLAG_BUTT    }

/* 定义各任务属性，如优先级、是否独占等: LPHY */
#define RCM_LPHY_TASK_PROPERTY_TABLE  \
    { RCM_LPHY_TASK_LIST,                   RCM_TASK_PRIORITY_BUTT, RCM_TASK_PREEMPTIND_FLAG_BUTT },\
    { RCM_LPHY_TASK_INIT_SEARCHING,         RCM_TASK_PRIORITY_3,    RCM_TASK_PREEMPTIND_FLAG_VALID },\
    { RCM_LPHY_TASK_INIT_PBCH_0,            RCM_TASK_PRIORITY_2_9,  RCM_TASK_PREEMPTIND_FLAG_INVALID },\
    { RCM_LPHY_TASK_INIT_PBCH_1,            RCM_TASK_PRIORITY_2_9,  RCM_TASK_PREEMPTIND_FLAG_INVALID },\
    { RCM_LPHY_TASK_INIT_SIB1,              RCM_TASK_PRIORITY_2_9,  RCM_TASK_PREEMPTIND_FLAG_INVALID },\
    { RCM_LPHY_TASK_INIT_SI_0,              RCM_TASK_PRIORITY_2_9,  RCM_TASK_PREEMPTIND_FLAG_INVALID },\
    { RCM_LPHY_TASK_INIT_SI_1,              RCM_TASK_PRIORITY_2_9,  RCM_TASK_PREEMPTIND_FLAG_INVALID },\
    { RCM_LPHY_TASK_IDLE_PAGE,              RCM_TASK_PRIORITY_2,    RCM_TASK_PREEMPTIND_FLAG_INVALID },\
    { RCM_LPHY_TASK_IDLE_MEA,               RCM_TASK_PRIORITY_4,    RCM_TASK_PREEMPTIND_FLAG_VALID },\
    { RCM_LPHY_TASK_IDLE_BG_SEARCHING,      RCM_TASK_PRIORITY_6,    RCM_TASK_PREEMPTIND_FLAG_VALID },\
    { RCM_LPHY_TASK_IDLE_PBCH_0,            RCM_TASK_PRIORITY_3,    RCM_TASK_PREEMPTIND_FLAG_INVALID },\
    { RCM_LPHY_TASK_IDLE_PBCH_1,            RCM_TASK_PRIORITY_3,    RCM_TASK_PREEMPTIND_FLAG_INVALID }, \
    { RCM_LPHY_TASK_IDLE_SIB1,              RCM_TASK_PRIORITY_3,    RCM_TASK_PREEMPTIND_FLAG_INVALID }, \
    { RCM_LPHY_TASK_IDLE_SI_0,              RCM_TASK_PRIORITY_3,    RCM_TASK_PREEMPTIND_FLAG_INVALID }, \
    { RCM_LPHY_TASK_IDLE_SI_1,              RCM_TASK_PRIORITY_3,    RCM_TASK_PREEMPTIND_FLAG_INVALID }, \
    { RCM_LPHY_TASK_IDLE_NCELL_PBCH_0,      RCM_TASK_PRIORITY_3,    RCM_TASK_PREEMPTIND_FLAG_INVALID }, \
    { RCM_LPHY_TASK_IDLE_NCELL_PBCH_1,      RCM_TASK_PRIORITY_3,    RCM_TASK_PREEMPTIND_FLAG_INVALID }, \
    { RCM_LPHY_TASK_IDLE_NCELL_SIB1,        RCM_TASK_PRIORITY_3,    RCM_TASK_PREEMPTIND_FLAG_INVALID }, \
    { RCM_LPHY_TASK_IDLE_NCELL_SI_0,        RCM_TASK_PRIORITY_3,    RCM_TASK_PREEMPTIND_FLAG_INVALID }, \
    { RCM_LPHY_TASK_IDLE_NCELL_SI_1,        RCM_TASK_PRIORITY_3,    RCM_TASK_PREEMPTIND_FLAG_INVALID },\
    { RCM_LPHY_TASK_CONN_TRAFFIC,           RCM_TASK_PRIORITY_5,    RCM_TASK_PREEMPTIND_FLAG_VALID },\
    { RCM_LPHY_TASK_CONN_PMCH,              RCM_TASK_PRIORITY_5,    RCM_TASK_PREEMPTIND_FLAG_VALID },\
    { RCM_LPHY_TASK_CONN_PBCH_0,            RCM_TASK_PRIORITY_3,    RCM_TASK_PREEMPTIND_FLAG_INVALID }, \
    { RCM_LPHY_TASK_CONN_PBCH_1,            RCM_TASK_PRIORITY_3,    RCM_TASK_PREEMPTIND_FLAG_INVALID }, \
    { RCM_LPHY_TASK_CONN_SIB1,              RCM_TASK_PRIORITY_3,    RCM_TASK_PREEMPTIND_FLAG_INVALID }, \
    { RCM_LPHY_TASK_CONN_SI_0,              RCM_TASK_PRIORITY_3,    RCM_TASK_PREEMPTIND_FLAG_INVALID }, \
    { RCM_LPHY_TASK_CONN_SI_1,              RCM_TASK_PRIORITY_3,    RCM_TASK_PREEMPTIND_FLAG_INVALID }, \
    { RCM_LPHY_TASK_CONN_MEA,               RCM_TASK_PRIORITY_5,    RCM_TASK_PREEMPTIND_FLAG_VALID }, \
    { RCM_LPHY_TASK_CONN_PAGE,              RCM_TASK_PRIORITY_2,    RCM_TASK_PREEMPTIND_FLAG_INVALID },   \
    { RCM_LPHY_TASK_ANR,                    RCM_TASK_PRIORITY_6,    RCM_TASK_PREEMPTIND_FLAG_VALID},   \
    { RCM_LPHY_TASK_PRESYNC,                RCM_TASK_PRIORITY_3,    RCM_TASK_PREEMPTIND_FLAG_INVALID}, \
    { RCM_LPHY_TASK_CAMPON,                 RCM_TASK_PRIORITY_2_9,  RCM_TASK_PREEMPTIND_FLAG_INVALID},\
    { RCM_LPHY_TASK_VOLTE,                  RCM_TASK_PRIORITY_1,    RCM_TASK_PREEMPTIND_FLAG_INVALID},\
    { RCM_LPHY_TASK_NO_SHARE_RF_IDLE_MEAS,  RCM_TASK_PRIORITY_5_5,  RCM_TASK_PREEMPTIND_FLAG_VALID}, \
    { RCM_LPHY_TASK_NO_SHARE_RF_CONN_MEAS,  RCM_TASK_PRIORITY_5_5,  RCM_TASK_PREEMPTIND_FLAG_VALID}, \
    { RCM_LPHY_TASK_NO_SHARE_RF_BGS,        RCM_TASK_PRIORITY_6,    RCM_TASK_PREEMPTIND_FLAG_VALID}


/* 定义各任务属性，如优先级、是否独占等: TPHY */
#define RCM_TPHY_TASK_PROPERTY_TABLE  \
    { RCM_TPHY_TASK_LIST,                   RCM_TASK_PRIORITY_BUTT, RCM_TASK_PREEMPTIND_FLAG_BUTT },\
    { RCM_TPHY_TASK_ICS_CELL_SEARCH,        RCM_TASK_PRIORITY_3,    RCM_TASK_PREEMPTIND_FLAG_VALID },\
    { RCM_TPHY_TASK_ICS_SWEEP_FREQ,         RCM_TASK_PRIORITY_3,    RCM_TASK_PREEMPTIND_FLAG_VALID },\
    { RCM_TPHY_TASK_ICS_CELL_MEASUREMENT,   RCM_TASK_PRIORITY_3,    RCM_TASK_PREEMPTIND_FLAG_VALID },\
    { RCM_TPHY_TASK_ICS_PCCPCH,             RCM_TASK_PRIORITY_3,    RCM_TASK_PREEMPTIND_FLAG_VALID },\
    { RCM_TPHY_TASK_IDLE_PICH,              RCM_TASK_PRIORITY_2,    RCM_TASK_PREEMPTIND_FLAG_INVALID },\
    { RCM_TPHY_TASK_IDLE_PCH,               RCM_TASK_PRIORITY_2,    RCM_TASK_PREEMPTIND_FLAG_INVALID },\
    { RCM_TPHY_TASK_IDLE_MEASUREMENT,       RCM_TASK_PRIORITY_4,    RCM_TASK_PREEMPTIND_FLAG_VALID },\
    { RCM_TPHY_TASK_IDLE_CELL_SEARCH,       RCM_TASK_PRIORITY_3,    RCM_TASK_PREEMPTIND_FLAG_VALID },\
    { RCM_TPHY_TASK_IDLE_PCCPCH,            RCM_TASK_PRIORITY_3,    RCM_TASK_PREEMPTIND_FLAG_VALID },\
    { RCM_TPHY_TASK_IDLE_FORCE_WAKE,        RCM_TASK_PRIORITY_2,    RCM_TASK_PREEMPTIND_FLAG_INVALID },\
    { RCM_TPHY_TASK_ACC_FACH_TRAFFIC,       RCM_TASK_PRIORITY_5,    RCM_TASK_PREEMPTIND_FLAG_VALID }, \
    { RCM_TPHY_TASK_ACC_PCCPCH,             RCM_TASK_PRIORITY_3,    RCM_TASK_PREEMPTIND_FLAG_VALID }, \
    { RCM_TPHY_TASK_DCH_TRAFFIC,            RCM_TASK_PRIORITY_5,    RCM_TASK_PREEMPTIND_FLAG_VALID }

#define RCM_CPHY_1X_TASK_PROPERTY_TABLE  \
    { RCM_CPHY_1X_TASK_LIST,                RCM_TASK_PRIORITY_BUTT, RCM_TASK_PREEMPTIND_FLAG_BUTT },\
    { RCM_CPHY_1X_TASK_NETWORK_SEARCH,      RCM_TASK_PRIORITY_1_7,    RCM_TASK_PREEMPTIND_FLAG_INVALID },\
    { RCM_CPHY_1X_TASK_IDLE_DRX,            RCM_TASK_PRIORITY_1_7,    RCM_TASK_PREEMPTIND_FLAG_INVALID },\
    { RCM_CPHY_1X_TASK_IDLE_DRX_MEAS,       RCM_TASK_PRIORITY_1_7,    RCM_TASK_PREEMPTIND_FLAG_INVALID },\
    { RCM_CPHY_1X_TASK_IDLE_NON_DRX,        RCM_TASK_PRIORITY_1_7,    RCM_TASK_PREEMPTIND_FLAG_INVALID },\
    { RCM_CPHY_1X_TASK_ACCESS_TCH,          RCM_TASK_PRIORITY_1_7,    RCM_TASK_PREEMPTIND_FLAG_INVALID },\
    { RCM_CPHY_1X_TASK_BSR,                 RCM_TASK_PRIORITY_6,      RCM_TASK_PREEMPTIND_FLAG_VALID },\
    { RCM_CPHY_1X_TASK_AGPS,                RCM_TASK_PRIORITY_1_7,    RCM_TASK_PREEMPTIND_FLAG_INVALID }


#define RCM_CPHY_HRPD_TASK_PROPERTY_TABLE  \
    { RCM_CPHY_HRPD_TASK_LIST,              RCM_TASK_PRIORITY_BUTT, RCM_TASK_PREEMPTIND_FLAG_BUTT },\
    { RCM_CPHY_HRPD_TASK_NETWORK_SEARCH,    RCM_TASK_PRIORITY_3,    RCM_TASK_PREEMPTIND_FLAG_VALID },\
    { RCM_CPHY_HRPD_TASK_DRX,               RCM_TASK_PRIORITY_2,    RCM_TASK_PREEMPTIND_FLAG_VALID },\
    { RCM_CPHY_HRPD_TASK_DRX_MEAS,          RCM_TASK_PRIORITY_4,    RCM_TASK_PREEMPTIND_FLAG_VALID },\
    { RCM_CPHY_HRPD_TASK_CC_MON_NON_DRX,    RCM_TASK_PRIORITY_4,    RCM_TASK_PREEMPTIND_FLAG_VALID },\
    { RCM_CPHY_HRPD_TASK_ACCESS_TCH,        RCM_TASK_PRIORITY_5,    RCM_TASK_PREEMPTIND_FLAG_VALID },\
    { RCM_CPHY_HRPD_TASK_BSR,               RCM_TASK_PRIORITY_6,    RCM_TASK_PREEMPTIND_FLAG_VALID },\
    { RCM_CPHY_HRPD_TASK_LTE_MEAS,          RCM_TASK_PRIORITY_4,    RCM_TASK_PREEMPTIND_FLAG_VALID },\
    { RCM_CPHY_HRPD_TASK_LTE_BSR,           RCM_TASK_PRIORITY_6,    RCM_TASK_PREEMPTIND_FLAG_VALID },\
    { RCM_CPHY_HRPD_TASK_AGPS,              RCM_TASK_PRIORITY_4,    RCM_TASK_PREEMPTIND_FLAG_VALID }

#define PHY_TAS_EN_BIT_MASK             (0x1)   /* bit0是TAS DPDT算法使能位,1表示使能 */
#define PHY_MAS_EN_BIT_MASK             (0x2)   /* bit1是MAS DPDT算法使能位,1表示使能 */

/*****************************************************************************
  3 枚举定义
*****************************************************************************/

/*****************************************************************************
 枚举名    : RCM_PHY_MSG_ID_ENUM_UINT16
 协议表格  :
 ASN.1描述 :
 枚举说明  : RCM <-> PHY 接口消息ID
*****************************************************************************/
enum RCM_PHY_MSG_ID_ENUM
{
    ID_PHY_RCM_TASK_APPLY_REQ               = 0x1801,                           /* _H2ASN_MsgChoice PHY_RCM_TASK_APPLY_REQ_STRU */
    ID_PHY_RCM_TASK_REL_REQ                 = 0x1802,                           /* _H2ASN_MsgChoice PHY_RCM_TASK_REL_REQ_STRU */
    ID_PHY_RCM_TASK_RELALL_REQ              = 0x1803,                           /* _H2ASN_MsgChoice PHY_RCM_TASK_RELALL_REQ_STRU */
    ID_PHY_RCM_TASK_PREEMPT_ACK             = 0x1804,                           /* _H2ASN_MsgChoice PHY_RCM_TASK_PREEMPT_ACK_STRU */
    ID_PHY_RCM_TASK_RESUME_ACK              = 0x1805,                           /* _H2ASN_MsgChoice PHY_RCM_TASK_RESUME_ACK_STRU */
    ID_PHY_RCM_AWAKE_REQ                    = 0x1807,                           /* _H2ASN_MsgChoice PHY_RCM_AWAKE_REQ_STRU */
    ID_PHY_RCM_SLEEP_REQ                    = 0x1808,                           /* _H2ASN_MsgChoice PHY_RCM_SLEEP_REQ_STRU */
    ID_PHY_RCM_ASSIGN_ACK                   = 0x1809,                           /* _H2ASN_MsgChoice PHY_RCM_ASSIGN_ACK_STRU */
    ID_PHY_RCM_CLOCK_CAL_ACK                = 0x180a,                           /* _H2ASN_MsgChoice PHY_RCM_CLOCK_CAL_ACK_STRU */
    ID_PHY_RCM_GET_MSGLISTADDR_REQ          = 0x180c,                           /* _H2ASN_MsgChoice PHY_RCM_GET_MSGLISTADDR_REQ_STRU */
    ID_PHY_RCM_PERIOD_TASK_COMPLETE_REQ     = 0x180d,                           /* _H2ASN_MsgChoice PHY_RCM_TASK_COMPLETE_REQ_STRU */
    ID_PHY_RCM_START_TAS_CNF                = 0x180e,                           /* _H2ASN_MsgChoice PHY_RCM_START_TAS_CNF_STRU */
    ID_PHY_RCM_STOP_TAS_CNF                 = 0x180f,                           /* _H2ASN_MsgChoice PHY_RCM_STOP_TAS_CNF_STRU */
    ID_PHY_RCM_SET_DPDT_CNF                 = 0x1810,                           /* _H2ASN_MsgChoice PHY_RCM_SET_DPDT_CNF_STRU */
    ID_PHY_RCM_TX_BLANKING_IND              = 0x1811,                           /* _H2ASN_MsgChoice PHY_RCM_TX_BLANKING_IND_STRU */
    ID_PHY_RCM_RATMODE_IND                  = 0x1812,                           /* _H2ASN_MsgChoice PHY_RCM_RATMODE_IND_STRU */
    ID_MSP_RCM_MAILBOX_READ_IND             = 0x1813,                           /* _H2ASN_MsgChoice RCM_PHY_MSG_HEADER_STRU */
    ID_PHY_RCM_ACCESS_STATE_IND             = 0x1814,                           /* _H2ASN_MsgChoice PHY_RCM_ACCESS_STATE_IND_STRU */
    ID_PHY_RCM_SEARCHING_STATE_IND          = 0x1815,                           /* _H2ASN_MsgChoice PHY_RCM_SEARCHING_STATE_IND_STRU */
    ID_PHY_RCM_SIGNAL_STATE_IND             = 0x1816,                           /* _H2ASN_MsgChoice PHY_RCM_SIGNAL_STATE_IND_STRU */
    ID_PHY_RCM_IDLE_HAPPY_IND               = 0x1817,                           /* _H2ASN_MsgChoice PHY_RCM_IDLE_HAPPY_IND_STRU */
                                                                                /* 0x1818已经分配给MTC -> RCM message使用 */
    ID_PHY_RCM_VOICE_CALL_STATE_CNF         = 0x1819,                           /* _H2ASN_MsgChoice PHY_RCM_VOICE_CALL_STATE_CNF_STRU */
    ID_PHY_RCM_SEARCHING_STATE_REQ          = 0x181a,                           /* _H2ASN_MsgChoice PHY_RCM_SEARCHING_STATE_REQ_STRU */
                                                                                /* 0x181b,0x181c已经分配给CMMCA -> RCM message使用 */
    ID_PHY_RCM_AGENT_SET_DPDT_CNF           = 0x181d,                           /* _H2ASN_MsgChoice PHY_RCM_AGENTC_SET_DPDT_CNF_STRU */
    ID_PHY_RCM_CPICH_STATE_IND              = 0x181e,                           /* _H2ASN_MsgChoice PHY_RCM_CPICH_STATE_IND_STRU */
                                                                                /* 0x181f已经分配给MTC -> RCM message使用 */
                                                                                /* 0x1820已经分配给MTC -> RCM message使用 */
    ID_PHY_RCM_ANT_SHARE_CNF                = 0x1821,                           /* _H2ASN_MsgChoice PHY_RCM_ANT_SHARE_CNF_STRU */
    ID_PHY_RCM_ONLY_START_MAS_CNF           = 0x1822,                           /* _H2ASN_MsgChoice PHY_RCM_ONLY_START_MAS_CNF_STRU */
    ID_PHY_RCM_ONLY_STOP_MAS_CNF            = 0x1823,                           /* _H2ASN_MsgChoice PHY_RCM_ONLY_STOP_MAS_CNF_STRU */
    ID_PHY_RCM_AVOID_PAGING_CFG_CNF         = 0x1824,                           /* _H2ASN_MsgChoice PHY_RCM_AVOID_PAGING_CFG_CNF_STRU */

    ID_PHY_RCM_INTERFERENCE_CHECK_REQ       = 0x1825,                           /* _H2ASN_MsgChoice PHY_RCM_INTERFE_CHECK_REQ_STRU */
    ID_PHY_RCM_GET_AFC_INFO_CNF             = 0x1826,
    ID_RCM_PHY_TASK_APPLY_CNF               = 0x1881,                           /* _H2ASN_MsgChoice RCM_PHY_TASK_APPLY_CNF_STRU */
    ID_RCM_PHY_TASK_REL_CNF                 = 0x1882,                           /* _H2ASN_MsgChoice RCM_PHY_TASK_REL_CNF_STRU */
    ID_RCM_PHY_TASK_RELALL_CNF              = 0x1883,                           /* _H2ASN_MsgChoice RCM_PHY_TASK_RELALL_CNF_STRU */
    ID_RCM_PHY_TASK_PREEMPT_IND             = 0x1884,                           /* _H2ASN_MsgChoice RCM_PHY_TASK_PREEMPT_IND_STRU */
    ID_RCM_PHY_TASK_RESUME_IND              = 0x1885,                           /* _H2ASN_MsgChoice RCM_PHY_TASK_RESUME_IND_STRU */
    ID_RCM_PHY_ASSIGN_IND                   = 0x1889,                           /* _H2ASN_MsgChoice RCM_PHY_ASSIGN_IND_STRU */
    ID_RCM_PHY_CLOCK_CAL_IND                = 0x188a,                           /* _H2ASN_MsgChoice RCM_PHY_CLOCK_CAL_IND_STRU */
    ID_RCM_PHY_OVERTIME_IND                 = 0x188b,                           /* _H2ASN_MsgChoice RCM_PHY_OVERTIME_IND_STRU */
    ID_RCM_PHY_GET_MSGLISTADDR_CNF          = 0x188c,                           /* _H2ASN_MsgChoice RCM_PHY_GET_MSGLISTADDR_CNF_STRU */
    ID_RCM_PHY_PERIOD_TASK_COMPLETE_CNF     = 0x188d,                           /* _H2ASN_MsgChoice RCM_PHY_TASK_COMPLETE_CNF_STRU */
    ID_RCM_PHY_START_TAS_REQ                = 0x188e,                           /* _H2ASN_MsgChoice RCM_PHY_START_TAS_REQ_STRU */
    ID_RCM_PHY_STOP_TAS_REQ                 = 0x188f,                           /* _H2ASN_MsgChoice RCM_PHY_STOP_TAS_REQ_STRU */
    ID_RCM_PHY_SET_DPDT_REQ                 = 0x1890,                           /* _H2ASN_MsgChoice RCM_PHY_SET_DPDT_REQ_STRU */
    ID_RCM_PHY_TX_BLANKING_IND              = 0x1891,                           /* _H2ASN_MsgChoice RCM_PHY_TX_BLANKING_IND */
    ID_PAGING_TASK_RF_RESOURCE_APPLY_FAIL   = 0x1892,                           /* _H2ASN_MsgChoice PHY_RCM_PAGING_TASK_FAIL_STRU */
    ID_RCM_PHY_SEARCHING_STATE_CNF          = 0x1893,                           /* _H2ASN_MsgChoice RCM_PHY_SEARCHING_STATE_CNF_STRU */
    ID_RCM_PHY_AGENT_SET_DPDT_REQ           = 0x1894,                           /* _H2ASN_MsgChoice RCM_PHY_AGENTC_SET_DPDT_REQ_STRU */
    ID_RCM_PHY_VOICE_CALL_STATE_IND         = 0x1895,                           /* _H2ASN_MsgChoice RCM_PHY_VOICE_CALL_STATE_IND_STRU */
    ID_RCM_PHY_ANT_SHARE_REQ                = 0x1896,                           /* _H2ASN_MsgChoice RCM_PHY_ANT_SHARE_REQ_STRU */
    ID_RCM_PHY_CDMA_WORK_STATE_IND          = 0x1897,                           /* _H2ASN_MsgChoice PHY_RCM_CDMA_WORK_STATE_IND_STRU */
    ID_RCM_PHY_ANT_SHARE_TX_BLANKING_IND    = 0x1898,                           /* _H2ASN_MsgChoice RCM_PHY_ANT_SHARE_TX_BLANKING_IND_STRU */
    ID_RCM_PHY_NOTICE_DSDS_INIT_IND         = 0x1899,                           /* _H2ASN_MsgChoice RCM_PHY_NOTICE_DSDS_INIT_IND_STRU */
    ID_RCM_PHY_ONLY_START_MAS_REQ           = 0x189a,                           /* _H2ASN_MsgChoice RCM_PHY_ONLY_START_MAS_REQ_STRU */
    ID_RCM_PHY_ONLY_STOP_MAS_REQ            = 0x189b,                           /* _H2ASN_MsgChoice RCM_PHY_ONLY_STOP_MAS_REQ_STRU */
    ID_RCM_PHY_AVOID_PAGING_CFG_REQ         = 0x189c,                           /* _H2ASN_MsgChoice RCM_PHY_AVOID_PAGING_CFG_REQ_STRU */

    /* 干扰判决新增消息 */
    ID_RCM_PHY_INTERFERENCE_CHECK_REQ       = 0x189d,                           /* _H2ASN_MsgChoice PHY_RCM_INTERFE_CHECK_REQ_STRU */
    ID_RCM_PHY_GET_AFC_INFO_REQ             = 0x189e,                           /* _H2ASN_MsgChoice RCM_PHY_NOTICE_DSDS_INIT_IND_STRU */
    ID_RCM_PHY_TASK_PROTECT_IND             = 0x18a1,                           /* _H2ASN_MsgChoice RCM_PHY_TASK_PROTECT_IND_STRU */
    ID_RCM_PHY_TASK_DEPROTECT_IND           = 0x18a2,                           /* _H2ASN_MsgChoice RCM_PHY_TASK_DEPROTECT_IND_STRU */

    ID_RCM_PHY_MSG_BUTT

};
typedef VOS_UINT16 RCM_PHY_MSG_ID_ENUM_UINT16;

/*****************************************************************************
 枚举名    : RCM_TASK_PRIORITY_ENUM_UINT16
 协议表格  :
 ASN.1描述 :
 枚举说明  : RCM中任务优先级 任务可以申请的值为优先级1~8(200~900)其余优先级由RCM内部使用
             优先级的值除以10必须小于RCM_TASK_PRIORITY_CALA_HIGHEST，所有的优先级必须是10的倍数
*****************************************************************************/
enum RCM_TASK_PRIORITY_ENUM
{
    RCM_TASK_PRIORITY_HIGHEST           = 1 ,                                   /* 任务最高优先级 1~99用于独占 */
    RCM_TASK_PRIORITY_CALA_HIGHEST      = 100,                                  /* 优先级100 任务优先级能够提升到的最大值 RCM计算得到 */
    RCM_TASK_PRIORITY_1                 = 200,                                  /* 优先级200 任务优先级申请值 */
    RCM_TASK_PRIORITY_1_5               = 250,                                  /* 优先级250 任务优先级申请值 */
    RCM_TASK_PRIORITY_1_6               = 260,                                  /* 优先级260 任务优先级申请值 */
    RCM_TASK_PRIORITY_1_7               = 270,                                  /* 优先级270 任务优先级申请值 */
    RCM_TASK_PRIORITY_2                 = 300,                                  /* 优先级300 */
    RCM_TASK_PRIORITY_2_5               = 350,                                  /* 优先级350 */
    RCM_TASK_PRIORITY_2_9               = 390,                                  /* 优先级390 */
    RCM_TASK_PRIORITY_3                 = 400,                                  /* 优先级400 */
    RCM_TASK_PRIORITY_3_4               = 440,                                  /* 优先级440 */
    RCM_TASK_PRIORITY_3_5               = 450,                                  /* 优先级450 */
    RCM_TASK_PRIORITY_3_7               = 470,                                  /* 优先级470 */
    RCM_TASK_PRIORITY_4                 = 500,                                  /* 优先级500 */
    RCM_TASK_PRIORITY_4_5               = 550,                                  /* 优先级550 */
    RCM_TASK_PRIORITY_4_9               = 590,                                  /* 优先级590 */
    RCM_TASK_PRIORITY_5                 = 600,                                  /* 优先级600 */
    RCM_TASK_PRIORITY_5_5               = 650,                                  /* 优先级650 */
    RCM_TASK_PRIORITY_5_9               = 690,                                  /* 优先级690 */
    RCM_TASK_PRIORITY_6                 = 700,                                  /* 优先级700 */
    RCM_TASK_PRIORITY_7                 = 800,                                  /* 优先级800 */
    RCM_TASK_PRIORITY_8                 = 900,                                  /* 优先级900 */
    RCM_TASK_PRIORITY_8_1               = 910,                                  /* 优先级910 */
    RCM_TASK_PRIORITY_LOWEST            = 1000,                                 /* 任务最低优先级 RCM使用 */
    RCM_TASK_PRIORITY_BUTT
};
typedef VOS_UINT16 RCM_TASK_PRIORITY_ENUM_UINT16;

/*****************************************************************************
 枚举名    : RCM_PHY_TASK_ID_ENUM_UINT16
 协议表格  :
 ASN.1描述 :
 枚举说明  : PHY 在RCM中注册的任务ID
*****************************************************************************/
enum RCM_PHY_TASK_ID_ENUM
{
    RCM_GPHY_TASK_START                     = RCM_GPHY_TASK_ID_BEGIN_NUM,       /* 虚拟的启动任务 */
    RCM_GPHY_TASK_SEARCHING_MEA             = 1,                                /* 1开机测量 */
    RCM_GPHY_TASK_SEARCHING_FBSB            = 2,                                /* 2开机同步 */
    RCM_GPHY_TASK_SEARCHING_BCCH_PART       = 3,                                /* 3开机解广播，部分读 */
    RCM_GPHY_TASK_SEARCHING_BCCH_WHOLE      = 4,                                /* 4开机解广播，全读 */
    RCM_GPHY_TASK_IDLE_PAGE_NORMAL          = 5,                                /* 5解寻呼任务 */
    RCM_GPHY_TASK_IDLE_PAGE_EXT             = 6,                                /* 6解扩展寻呼任务 */
    RCM_GPHY_TASK_IDLE_PAGE_REORG           = 7,                                /* 7Reorg态解寻呼 */
    RCM_GPHY_TASK_IDLE_SCELL_BCCH_PERIOD    = 8,                                /* 8读服务小区系统消息 */
    RCM_GPHY_TASK_IDLE_NCELL_BCCH_DECODE    = 9,                                /* 9读邻区系统消息 */
    RCM_GPHY_TASK_IDLE_BASIC_CBCH           = 10,                               /* 10BASIC类型CBS业务 */
    RCM_GPHY_TASK_IDLE_EXT_CBCH             = 11,                               /* 11EXT类型CBS业务 */
    RCM_GPHY_TASK_IDLE_NCELL_FB             = 12,                               /* 12邻区FB */
    RCM_GPHY_TASK_IDLE_NCELL_SB             = 13,                               /* 13邻区SB */
    RCM_GPHY_TASK_IDLE_CELL_RESELECT        = 14,                               /* 14小区重选 */
    RCM_GPHY_TASK_IDLE_BG_MEA               = 15,                               /* 15背景搜测量 */
    RCM_GPHY_TASK_IDLE_BG_FBSB              = 16,                               /* 16背景搜同步 */
    RCM_GPHY_TASK_IDLE_BG_BCCH              = 17,                               /* 17背景搜解广播 */
    RCM_GPHY_TASK_IDLE_INTERRAT_WMEA        = 18,                               /* 18异系统W测量 */
    RCM_GPHY_TASK_IDLE_INTERRAT_TMEA        = 19,                               /* 19异系统T测量 */
    RCM_GPHY_TASK_IDLE_INTERRAT_LMEA        = 20,                               /* 20异系统L测量 */
    RCM_GPHY_TASK_IDLE_BG_WMEA              = 21,                               /* 21背景搜W测量 */
    RCM_GPHY_TASK_IDLE_BG_TMEA              = 22,                               /* 22背景搜T测量 */
    RCM_GPHY_TASK_IDLE_BG_LMEA              = 23,                               /* 23背景搜L测量 */
    RCM_GPHY_TASK_IDLE_FULLLIST_MEA         = 24,                               /* 24FULLIS测量 */
    RCM_GPHY_TASK_TUNING_RACH               = 25,                               /* 25随机接入 */
    RCM_GPHY_TASK_TUNING_PRACH              = 26,                               /* 26PACKET随机接入 */
    RCM_GPHY_TASK_PBCCH                     = 27,                               /* 27PACKET系统消息 */
    RCM_GPHY_TASK_PPCH                      = 28,                               /* 28PACKET寻呼 */
    RCM_GPHY_TASK_TUNING_SINGLE_BLOCK       = 29,                               /* 29发送单块和多块 */
    RCM_GPHY_TASK_DCH_CS                    = 30,                               /* 30CS专用态 */
    RCM_GPHY_TASK_DCH_PS                    = 31,                               /* 31PS专用态 */
    RCM_GPHY_TASK_LOST_NET                  = 32,                               /* 32丢网用 */
    RCM_GPHY_TASK_INACTIVE                  = 33,                               /* 33去激活 */
    RCM_GPHY_TASK_IDLE_SCELL_BCCH_RESEL     = 34,                               /* 34重选过程中服务小区系统消息读取, 任务的优先级为260，跟寻呼任务的失败门限有关 */
    RCM_GPHY_TASK_IDLE_SCELL_BCCH_ENH       = 35,                               /* 35增强接收过程中系统消息读取 */
    RCM_GPHY_TASK_IDLE_NCELL_BCCH_RESEL     = 36,                               /* 36重选过程中系统消息读取 */
    RCM_GPHY_TASK_IDLE_NCELL_BCCH_BG        = 37,                               /* 37背景搜过程中系统消息读取 */
    RCM_GPHY_TASK_IDLE_UNFIX_NCELL_SB       = 38,                               /* 38邻区非固定的SB */
    RCM_GPHY_TASK_PSRCH_FIRST_CELL_FBSB     = 39,                               /* 39并行搜网第一小区同步 */
    RCM_GPHY_TASK_PSRCH_FIRST_CELL_BCCH     = 40,                               /* 40并行搜网第一小区系统消息读取 */
    RCM_GPHY_TASK_PSRCH_FIRST_CELL_PCH      = 41,                               /* 41并行搜网第一小区系统消息读取 */
    RCM_GPHY_TASK_PSRCH_NEXT_CELL_FBSB      = 42,                               /* 42并行搜网后续小区同步 */
    RCM_GPHY_TASK_PSRCH_NEXT_CELL_BCCH      = 43,                               /* 43并行搜网后续小区系统消息读取1 */
    RCM_GPHY_TASK_IDLE_PLMN_LIST_FBSB       = 44,                               /* 44背景PLMN LIST搜同步 */
    RCM_GPHY_TASK_IDLE_NET_SCAN_FBSB        = 45,                               /* 45 G NETSCAN搜同步 */
    RCM_GPHY_TASK_IDLE_NBCCH_PLMN_LIST      = 46,                               /* 46背景PLMN LIST读系统消息 */
    RCM_GPHY_TASK_IDLE_NBCCH_NET_SCAN       = 47,                               /* 47 G NETSCAN搜读系统消息 */
    RCM_GPHY_TASK_END                       ,                                   /* 虚拟的启动结束 */
    RCM_WPHY_TASK_LIST                      = RCM_WPHY_TASK_ID_BEGIN_NUM,
    RCM_WPHY_TASK_FREE                      = 101,                              /* Wphy free态任务 */
    RCM_WPHY_TASK_CPICH_PI                  = 102,                              /* Wphy cpich态PI任务 */
    RCM_WPHY_TASK_CPICH_MEAS                = 103,                              /* Wphy cpich态测量任务 */
    RCM_WPHY_TASK_CPICH_PCCPCH              = 104,                              /* Wphy cpich态同频重选场景下的广播任务 */
    RCM_WPHY_TASK_CPICH_BG                  = 105,                              /* Wphy cpich态背景搜任务 */
    RCM_WPHY_TASK_CPICH_CBS                 = 106,                              /* Wphy cpich态CBS任务 */
    RCM_WPHY_TASK_FACH_COMM                 = 107,                              /* Wphy fach态任务 */
    RCM_WPHY_TASK_FACH_RA                   = 108,                              /* Wphy fach态随机接入任务 */
    RCM_WPHY_TASK_FACH_PCCPCH               = 109,                              /* Wphy fach态同重选或系统消息变更任务 */
    RCM_WPHY_TASK_DPCH_COMM                 = 110,                              /* Wphy dch态任务 */
    RCM_WPHY_TASK_END                       ,
    RCM_TPHY_TASK_LIST                      = RCM_TPHY_TASK_ID_BEGIN_NUM,
    RCM_TPHY_TASK_ICS_CELL_SEARCH           = 201,                              /*  1  */
    RCM_TPHY_TASK_ICS_SWEEP_FREQ            = 202,                              /*  2  */
    RCM_TPHY_TASK_ICS_CELL_MEASUREMENT      = 203,                              /*  3  */
    RCM_TPHY_TASK_ICS_PCCPCH                = 204,                              /*  4  */
    RCM_TPHY_TASK_IDLE_PICH                 = 205,                              /*  5  */
    RCM_TPHY_TASK_IDLE_PCH                  = 206,                              /*  6  */
    RCM_TPHY_TASK_IDLE_MEASUREMENT          = 207,                              /*  7  */
    RCM_TPHY_TASK_IDLE_CELL_SEARCH          = 208,                              /*  8  */
    RCM_TPHY_TASK_IDLE_PCCPCH               = 209,                              /*  9  */
    RCM_TPHY_TASK_IDLE_FORCE_WAKE           = 210,                              /*  10  */
    RCM_TPHY_TASK_ACC_FACH_TRAFFIC          = 211,                              /*  11  */
    RCM_TPHY_TASK_ACC_PCCPCH                = 212,                              /*  12  */
    RCM_TPHY_TASK_DCH_TRAFFIC               = 213,                              /*  13  */
    RCM_TPHY_TASK_BUTT                      ,
    RCM_LPHY_TASK_LIST                      = RCM_LPHY_TASK_ID_BEGIN_NUM,
    RCM_LPHY_TASK_INIT_SEARCHING            = 301,                              /*  1  */
    RCM_LPHY_TASK_INIT_PBCH_0               = 302,                              /*  2  */
    RCM_LPHY_TASK_INIT_PBCH_1               = 303,                              /*  3  */
    RCM_LPHY_TASK_INIT_SIB1                 = 304,                              /*  4  */
    RCM_LPHY_TASK_INIT_SI_0                 = 305,                              /*  5  */
    RCM_LPHY_TASK_INIT_SI_1                 = 306,                              /*  6  */
    RCM_LPHY_TASK_IDLE_PAGE                 = 307,                              /*  7  */
    RCM_LPHY_TASK_IDLE_MEA                  = 308,                              /*  8  */
    RCM_LPHY_TASK_IDLE_BG_SEARCHING         = 309,                              /*  9  */
    RCM_LPHY_TASK_IDLE_PBCH_0               = 310,                              /*  10  */
    RCM_LPHY_TASK_IDLE_PBCH_1               = 311,                              /*  11  */
    RCM_LPHY_TASK_IDLE_SIB1                 = 312,                              /*  12  */
    RCM_LPHY_TASK_IDLE_SI_0                 = 313,                              /*  13  */
    RCM_LPHY_TASK_IDLE_SI_1                 = 314,                              /*  14  */
    RCM_LPHY_TASK_IDLE_NCELL_PBCH_0         = 315,                              /*  15  */
    RCM_LPHY_TASK_IDLE_NCELL_PBCH_1         = 316,                              /*  16  */
    RCM_LPHY_TASK_IDLE_NCELL_SIB1           = 317,                              /*  17  */
    RCM_LPHY_TASK_IDLE_NCELL_SI_0           = 318,                              /*  18  */
    RCM_LPHY_TASK_IDLE_NCELL_SI_1           = 319,                              /*  19  */
    RCM_LPHY_TASK_CONN_TRAFFIC              = 320,                              /*  20  */
    RCM_LPHY_TASK_CONN_PMCH                 = 321,                              /*  21  */
    RCM_LPHY_TASK_CONN_PBCH_0               = 322,                              /*  22  */
    RCM_LPHY_TASK_CONN_PBCH_1               = 323,                              /*  23  */
    RCM_LPHY_TASK_CONN_SIB1                 = 324,                              /*  24  */
    RCM_LPHY_TASK_CONN_SI_0                 = 325,                              /*  25  */
    RCM_LPHY_TASK_CONN_SI_1                 = 326,                              /*  26  */
    RCM_LPHY_TASK_CONN_MEA                  = 327,                              /*  27  */
    RCM_LPHY_TASK_CONN_PAGE                 = 328,                              /*  28  */
    RCM_LPHY_TASK_ANR                       = 329,                              /*  29  */
    RCM_LPHY_TASK_PRESYNC                   = 330,                              /*  30  */
    RCM_LPHY_TASK_CAMPON                    = 331,                              /*  31  */
    RCM_LPHY_TASK_VOLTE                     = 332,                              /*  32  */
    RCM_LPHY_TASK_NO_SHARE_RF_IDLE_MEAS     = 333,                              /*  33  */
    RCM_LPHY_TASK_NO_SHARE_RF_CONN_MEAS     = 334,                              /*  34  */
    RCM_LPHY_TASK_NO_SHARE_RF_BGS           = 335,                              /*  35  */
    RCM_LPHY_TASK_BUTT,
    RCM_CPHY_1X_TASK_LIST                   = RCM_CPHY_1X_TASK_ID_BEGIN_NUM,
    RCM_CPHY_1X_TASK_NETWORK_SEARCH         = 401,                              /*   1  */
    RCM_CPHY_1X_TASK_IDLE_DRX               = 402,                              /*   2  */
    RCM_CPHY_1X_TASK_IDLE_DRX_MEAS          = 403,                              /*   3  */
    RCM_CPHY_1X_TASK_IDLE_NON_DRX           = 404,                              /*   4  */
    RCM_CPHY_1X_TASK_ACCESS_TCH             = 405,                              /*   5  */
    RCM_CPHY_1X_TASK_BSR                    = 406,                              /*   6  */
    RCM_CPHY_1X_TASK_AGPS                   = 407,                              /*   7  */
    RCM_CPHY_1X_TASK_BUTT,
    RCM_CPHY_HRPD_TASK_LIST                 = RCM_CPHY_HRPD_TASK_ID_BEGIN_NUM,
    RCM_CPHY_HRPD_TASK_NETWORK_SEARCH       = 501,                              /*   1  */
    RCM_CPHY_HRPD_TASK_DRX                  = 502,                              /*   2  */
    RCM_CPHY_HRPD_TASK_DRX_MEAS             = 503,                              /*   3  */
    RCM_CPHY_HRPD_TASK_CC_MON_NON_DRX       = 504,                              /*   4  */
    RCM_CPHY_HRPD_TASK_ACCESS_TCH           = 505,                              /*   5  */
    RCM_CPHY_HRPD_TASK_BSR                  = 506,                              /*   6  */
    RCM_CPHY_HRPD_TASK_LTE_MEAS             = 507,                              /*   7  */
    RCM_CPHY_HRPD_TASK_LTE_BSR              = 508,                              /*   8  */
    RCM_CPHY_HRPD_TASK_AGPS                 = 509,                              /*   9  */
    RCM_PHY_TASK_BUTT                       ,
};
typedef VOS_UINT16 RCM_PHY_TASK_ID_ENUM_UINT16;

/*****************************************************************************
 枚举名    : RCM_MODE_ID_ENUM_UINT16
 协议表格  :
 ASN.1描述 :
 枚举说明  : 物理层模式标示 排列次序和校准次序一致
*****************************************************************************/
enum RCM_MODE_ID_ENUM
{
    RCM_LTE                             = 0,                                    /* LTE */
    RCM_WCDMA                           = 1,                                    /* WCDMA */
    RCM_1X                              = 2,                                    /* 1X */
    RCM_HRPD                            = 3,                                    /* HRPD */
    RCM_TD                              = 4,                                    /* TD */
    RCM_G0                              = 5,                                    /* G0 */
    RCM_G1                              = 6,                                    /* G1 */
    RCM_G2                              = 7,                                    /* G2 */
    RCM_MODE_ID_BUTT
};
typedef VOS_UINT16  RCM_MODE_ID_ENUM_UINT16;

/*****************************************************************************
 枚举名    : RCM_MODEM_ID_ENUM_UINT16
 协议表格  :
 ASN.1描述 :
 枚举说明  : MODEM ID
*****************************************************************************/
enum RCM_MODEM_ID_ENUM
{
    RCM_MODEM_1                         = 0,                                    /* MODEM0 */
    RCM_MODEM_2                         = 1,                                    /* MODEM1 */
    RCM_MODEM_3                         = 2,                                    /* MODEM2 */
    RCM_MODEM_1X                        = 3,                                    /* MODEM_1x */
    RCM_MODEM_OTHER                     = 4,                                    /* MODEM_OHTER */
    RCM_MODEM_ID_BUTT
};
typedef VOS_UINT16  RCM_MODEM_ID_ENUM_UINT16;

/*****************************************************************************
 枚举名    : RCM_TAS_MODEM_ID_ENUM_UINT16
 协议表格  :
 ASN.1描述 :
 枚举说明  : TAS_MODEM ID
*****************************************************************************/
enum RCM_TAS_MODEM_ID_ENUM
{
    RCM_TAS_MODEM_1                     = 0,                                    /* MODEM0 */
    RCM_TAS_MODEM_2                     = 1,                                    /* MODEM1 */
    RCM_TAS_MODEM_3                     = 2,                                    /* MODEM1 */
    RCM_TAS_MODEM_ID_BUTT
};
typedef VOS_UINT16  RCM_TAS_MODEM_ID_ENUM_UINT16;

/*****************************************************************************
 枚举名    : RCM_RF_ID_ENUM_UINT16
 协议表格  :
 ASN.1描述 :
 枚举说明  : RF ID
*****************************************************************************/
enum RCM_RF_ID_ENUM
{
    RCM_RF_0                            = 0,                                    /* RF0 */
    RCM_RF_1                            = 1,                                    /* RF1 */
    RCM_RF_ID_BUTT
};
typedef VOS_UINT16  RCM_RF_ID_ENUM_UINT16;

/*****************************************************************************
 枚举名    : RCM_DSDS_FLG_ENUM
 协议表格  :
 ASN.1描述 :
 枚举说明  : RCM_DSDS_FLG_ENUM
*****************************************************************************/
enum RCM_DSDS_FLG_ENUM
{
    RCM_DSDS_CLOSE                       = 0,                                   /* DSDS CLOSE */
    RCM_DSDS_OPEN                        = 1,                                   /* DSDS OPEN  */
    RCM_DSDS_BUTT
};
typedef VOS_UINT16  RCM_DSDS_FLG_ENUM_UINT16;

/*****************************************************************************
 枚举名    : RCM_RTT_STA_ENUM_UINT16
 协议表格  :
 ASN.1描述 :
 枚举说明  : RTT状态,用于时钟校准选择

*****************************************************************************/
enum RCM_RTT_STA_ENUM
{
    RCM_RTT_INITIAL                     = 0,                                    /* 初始态 ,没有驻留 */
    RCM_RTT_DRX                         = 1,                                    /* 非连续态，空闲态 */
    RCM_RTT_CONTINUE                    = 2,                                    /* 连续态 ，打电话数传*/
    RCM_RTT_STA_BUTT
};
typedef VOS_UINT16  RCM_RTT_STA_ENUM_UINT16;

/*****************************************************************************
 枚举名    : RCM_RSLT_ENUM_UINT16
 协议表格  :
 ASN.1描述 :
 枚举说明  : 接口中的有效性标识
*****************************************************************************/
enum RCM_RSLT_ENUM
{
    RCM_SUCC                            = 0,                                    /* 成功 */
    RCM_FAIL_PARA                       = 1,                                    /* 参数错误 */
    RCM_FAIL_OVERTIME                   = 2,                                    /* 申请提前量不够 */
    RCM_FAIL_OTHER                      = 3,                                    /* 操作节点为空 */
    RCM_RSLT_BUTT
};
typedef VOS_UINT16  RCM_RSLT_ENUM_UINT16;

/*****************************************************************************
 枚举名    : RCM_DIRECTION_ENUM_UINT16
 协议表格  :
 ASN.1描述 :
 枚举说明  : 接口中的调整方向标识
*****************************************************************************/
enum RCM_DIRECTION_ENUM
{
    RCM_DIRECTION_SLOWDOWN              = 0,                                    /* 减速1个周期 */
    RCM_DIRECTION_SPEEDUP               = 1,                                    /* 加速1个周期 */
    RCM_DIRECTION_KEEP                  = 2,                                    /* 不调整 */
    RCM_DIRECTION_BUTT
};
typedef VOS_UINT16 RCM_DIRECTION_ENUM_UINT16;

/*****************************************************************************
 枚举名    : RCM_TASK_PERIOD_FLAG_ENUM_UINT16
 协议表格  :
 ASN.1描述 :
 枚举说明  : 周期/非周期任务标识
*****************************************************************************/
enum RCM_TASK_PERIOD_FLAG_ENUM
{
    RCM_TASK_PERIOD_FLAG_INVALID        = 0,                                    /* 非周期任务 */
    RCM_TASK_PERIOD_FLAG_VALID          = 1,                                    /* 周期任务 */
    RCM_TASK_PERIOD_FLAG_BUTT
};
typedef VOS_UINT16  RCM_TASK_PERIOD_FLAG_ENUM_UINT16;

/*****************************************************************************
 枚举名    : RCM_TASK_FIXPOS_FLAG_ENUM_UINT16
 协议表格  :
 ASN.1描述 :
 枚举说明  : 固定/非固定启动时刻标识
*****************************************************************************/
enum RCM_TASK_FIXPOS_FLAG_ENUM
{
    RCM_TASK_FIXPOS_FLAG_INVALID        = 0,                                    /* 无固定启动时间 */
    RCM_TASK_FIXPOS_FLAG_VALID          = 1,                                    /* 有固定启动时间 */
    RCM_TASK_FIXPOS_FLAG_BUTT
};
typedef VOS_UINT16  RCM_TASK_FIXPOS_FLAG_ENUM_UINT16;

/*****************************************************************************
 枚举名    : RCM_TASK_LIMITLEN_FLAG_ENUM_UINT16
 协议表格  :
 ASN.1描述 :
 枚举说明  : 固定/非固定长度标识
*****************************************************************************/
enum RCM_TASK_LIMITLEN_FLAG_ENUM
{
    RCM_TASK_LIMITLEN_FLAG_INVALID      = 0,                                    /* 无限长任务 */
    RCM_TASK_LIMITLEN_FLAG_VALID        = 1,                                    /* 有限长任务 */
    RCM_TASK_LIMITLEN_FLAG_BUTT
};
typedef VOS_UINT16  RCM_TASK_LIMITLEN_FLAG_ENUM_UINT16;

/*****************************************************************************
 枚举名    : RCM_TASK_IMMEDIATE_ASSIGN_FLAG_ENUM_UINT16
 协议表格  :
 ASN.1描述 :
 枚举说明  : 立即/非立即分配任务标识
*****************************************************************************/
enum RCM_TASK_IMMEDIATE_ASSIGN_FLAG_ENUM
{
    RCM_TASK_IMMEDIATE_ASSIGN_FLAG_INVALID  = 0,                                /* 不需要立即分配任务 */
    RCM_TASK_IMMEDIATE_ASSIGN_FLAG_VALID    = 1,                                /* 需要立即分配任务 */
    RCM_TASK_IMMEDIATE_ASSIGN_FLAG_BUTT
};
typedef VOS_UINT16  RCM_TASK_IMMEDIATE_ASSIGN_FLAG_ENUM_UINT16;

/*****************************************************************************
 枚举名    : RCM_TASK_PREEMPTIND_FLAG_ENUM_UINT16
 协议表格  :
 ASN.1描述 :
 枚举说明  : 可打断/不可打断任务标识
*****************************************************************************/
enum RCM_TASK_PREEMPTIND_FLAG_ENUM
{
    RCM_TASK_PREEMPTIND_FLAG_INVALID        = 0,                                /* 不可打断任务 */
    RCM_TASK_PREEMPTIND_FLAG_VALID          = 1,                                /* 可打断任务 */
    RCM_TASK_PREEMPTIND_FLAG_BUTT
};
typedef VOS_UINT16  RCM_TASK_PREEMPTIND_FLAG_ENUM_UINT16;

/*****************************************************************************
 枚举名    : RCM_TASK_RELEASE_PRINCIPAL_FLAG_ENUM_UINT16
 协议表格  :
 ASN.1描述 :
 枚举说明  : 物理层/RCM 任务释放标识
*****************************************************************************/
enum RCM_TASK_RELEASE_PRINCIPAL_ENUM
{
    RCM_TASK_RELEASE_PRINCIPAL_PHY          = 0,                                /* 由物理层释放 */
    RCM_TASK_RELEASE_PRINCIPAL_RCM          = 1,                                /* 由RCM释放 */
    RCM_TASK_RELEASE_PRINCIPAL_ONLYPHY      = 2,                                /* 固定时刻无限长任务希望RCM不要释放，只能通过PHY释放 */
    RCM_TASK_RELEASE_PRINCIPAL_FLAG_BUTT
};
typedef VOS_UINT16  RCM_TASK_RELEASE_PRINCIPAL_ENUM_UINT16;

/*****************************************************************************
 枚举名    : RCM_CMD_ENUM_UINT16
 协议表格  :
 ASN.1描述 :
 枚举说明  : 消息队列中消息类型
*****************************************************************************/
enum RCM_CMD_ENUM
{
    RCM_CMD_TASK_ASSIGN_SUCC                = 0,                                /* 任务分配成功 */
    RCM_CMD_TASK_ASSIGN_FAIL_OTHER          = 1,                                /* 任务分配其他失败 */
    RCM_CMD_TASK_RECYCLE                    = 2,                                /* 已分配任务还没启动进行回收 */
    RCM_CMD_MSG_BUTT
};
typedef VOS_UINT16  RCM_CMD_ENUM_UINT16;

/*****************************************************************************
 枚举名    : RCM_CMODE_TYPE_ENUM_UINT16
 枚举说明  : C模的系统时间类型,00：1x定时，01：evdo定时，10： base_cnt ，11：无效。
*****************************************************************************/
enum RCM_CMODE_TYPE_ENUM
{
    RCM_CMODE_1X                        = 0,
    RCM_CMODE_EVDO                      = 1,
    RCM_CMODE_BASECNT                   = 2,
    RCM_CMODE_BUTT
};
typedef VOS_UINT16 RCM_CMODE_TYPE_ENUM_UINT16;

/*****************************************************************************
 枚举名    : RCM_WMODE_TYPE_ENUM_UINT16
 枚举说明  : W模的系统时间类型
             00：sys_cnt定时        01：base_cnt定时
             10：无效               11：无效
*****************************************************************************/
enum RCM_WMODE_TYPE_ENUM
{
    RCM_WMODE_SYSCNT                    = 0,
    RCM_WMODE_BASECNT                   = 1,
    RCM_WMODE_BUTT
};
typedef VOS_UINT16 RCM_WMODE_TYPE_ENUM_UINT16;

/*****************************************************************************
 枚举名    : RCM_PAGING_TASK_FAIL_REASON_ENUM_UINT16
 协议表格  :
 ASN.1描述 :
 枚举说明  : 物理层/RCM 任务释放原因
*****************************************************************************/
enum RCM_PAGING_TASK_FAIL_REASON_ENUM
{
    RCM_PAGING_TASK_FAIL_FOR_PROTECT        = 0,                                /* 另外一张卡保护了 */
    RCM_PAGING_TASK_FAIL_FOR_PREEMPTED      = 1,                                /* 其他任务优先级高 */
    RCM_PAGING_TASK_FAIL_FOR_OTHER          = 2,                                /* 需要分析log的场景 */
    RCM_PAGING_TASK_FAIL_BUTT
};
typedef VOS_UINT16  RCM_PAGING_TASK_FAIL_REASON_ENUM_UINT16;


/*****************************************************************************
 枚举名    : RCM_STOP_TAS_TYPE_ENUM_UINT16
 枚举说明  : RCM取消物理层TAS授权方式
             0:关闭TAS，将天线切回PHY默认态
             1:暂停TAS，将天线保持在当前状态
*****************************************************************************/
enum RCM_STOP_TAS_TYPE_ENUM
{
    RCM_STOP_TAS_TYPE_STOP                = 0,
    RCM_STOP_TAS_TYPE_KEEP                = 1,
    RCM_STOP_TAS_TYPE_BUTT
};
typedef VOS_UINT16 RCM_STOP_TAS_TYPE_ENUM_UINT16;

/*****************************************************************************
 枚举名    : RCM_TAS_CONNECT_STATE_ENUM_UINT16
 枚举说明  : modem业务连接状态
             0:非连接状态
             1:连接状态
*****************************************************************************/
enum RCM_TAS_CONNECT_STATE_ENUM
{
    RCM_TAS_CONNECT_NO_EXIST             = 0,
    RCM_TAS_CONNECT_EXIST                = 1,
    RCM_TAS_CONNECT_BUTT
};
typedef VOS_UINT16 RCM_TAS_CONNECT_STATE_ENUM_UINT16;

/*****************************************************************************
 枚举名    : RCM_TAS_POWER_STATE_ENUM_UINT16
 枚举说明  : modem_power上下电状态即是否处于飞行模式
             0:下电即飞行模式
             1:上电即非飞行模式
*****************************************************************************/
enum RCM_TAS_POWER_STATE_ENUM
{
    RCM_TAS_POWER_STATE_OFF           = 0,
    RCM_TAS_POWER_STATE_ON            = 1,
    RCM_TAS_POWER_STATE_BUTT
};
typedef VOS_UINT16 RCM_TAS_POWER_STATE_ENUM_UINT16;

/*****************************************************************************
 枚举名    : RCM_ACCESS_STATE_ENUM_UINT16
 枚举说明  : modem接入状态
             0:非接入状态
             1:接入状态
*****************************************************************************/
enum RCM_ACCESS_STATE_ENUM
{
    RCM_ACCESS_STATE_NON_ACCESS   = 0,
    RCM_ACCESS_STATE_ACCESS       = 1,
    RCM_ACCESS_STATE_UNHAPPY      = 2,
    RCM_ACCESS_STATE_BUTT
};
typedef VOS_UINT16 RCM_ACCESS_STATE_ENUM_UINT16;

/*****************************************************************************
 枚举名    : RCM_CPICH_STATE_ENUM
 枚举说明  : modemCPICH_STAT状态
             0:非CPICH状态
             1:CPICH状态
*****************************************************************************/
enum RCM_CPICH_STATE_ENUM
{
    RCM_CPICH_STATE_NON         = 0,
    RCM_CPICH_STATE             = 1,
    RCM_CPICH_STATE_BUTT
};
typedef VOS_UINT16 RCM_CPICH_STATE_ENUM_UINT16;



/*****************************************************************************
 枚举名    : RCM_SEARCHING_STATE_ENUM_UINT16
 枚举说明  : modem搜寻状态
             0:非搜寻状态
             1:搜寻状态
*****************************************************************************/
enum RCM_SEARCHING_STATE_ENUM
{
    RCM_SEARCHING_STATE_NON_SEARCH    = 0,
    RCM_SEARCHING_STATE_SEARCH        = 1,
    RCM_SEARCHING_STATE_BUTT
};
typedef VOS_UINT16 RCM_SEARCHING_STATE_ENUM_UINT16;

/*****************************************************************************
 枚举名    : RCM_SIGNAL_STATE_ENUM_UINT16
 枚举说明  : modem讯号状态
             0:讯号POOR状态
             1:讯号GOOD状态
*****************************************************************************/
enum RCM_SIGNAL_STATE_ENUM
{
    RCM_SIGNAL_STATE_POOR         = 0,
    RCM_SIGNAL_STATE_GOOD         = 1,
    RCM_SIGNAL_STATE_BUTT
};
typedef VOS_UINT16 RCM_SIGNAL_STATE_ENUM_UINT16;

/*****************************************************************************
 枚举名    : RCM_IDLE_HAPPY_ENUM_UINT16
 枚举说明  : modem Idle Happy状态
             0:Idle Unhappy状态
             1:Idle Happy状态
*****************************************************************************/
enum RCM_IDLE_HAPPY_ENUM
{
    RCM_IDLE_HAPPY_UNHAPPY        = 0,
    RCM_IDLE_HAPPY_HAPPY          = 1,
    RCM_IDLE_HAPPY_BUTT
};
typedef VOS_UINT16 RCM_IDLE_HAPPY_ENUM_UINT16;

/*****************************************************************************
 枚举名    : RCM_MAS_DPDT_CONTROL_ENUM_UINT16
 枚举说明  : DPDT命令对应控制模式
             0:TAS直通 & MAS直通
             1:TAS交叉 & MAS直通
             2:TAS直通 & MAS交叉
             3:TAS交叉 & MAS交叉
*****************************************************************************/
enum RCM_MAS_DPDT_CONTROL_ENUM
{
    RCM_MAS_DPDT_TAS_PASSTHROUGH_MAS_PASSTHROUGH   = 0,
    RCM_MAS_DPDT_TAS_SWAP_MAS_PASSTHROUGH          = 1,
    RCM_MAS_DPDT_TAS_PASSTHROUGH_MAS_SWAP          = 2,
    RCM_MAS_DPDT_TAS_SWAP_MAS_SWAP                 = 3,
    RCM_MAS_DPDT_BUTT
};
typedef VOS_UINT16 RCM_MAS_DPDT_CONTROL_ENUM_UINT16;

/*****************************************************************************
 枚举名    : RCM_TAS_MAS_CONTROL_ENUM_UINT16
 枚举说明  : MAS控制设置
             0:关闭MAS
             1:开启MAS
*****************************************************************************/
enum RCM_TAS_MAS_CONTROL_ENUM
{
    RCM_TAS_MAS_CTRL_STOP               = 0,
    RCM_TAS_MAS_CTRL_START              = 1,
    RCM_TAS_MAS_CTRL_BUTT
};
typedef VOS_UINT16 RCM_TAS_MAS_CONTROL_ENUM_UINT16;

/*****************************************************************************
 枚举名    : RCM_TAS_SEARCH_METHOD_ENUM_UINT16
 枚举说明  : 物理层的搜索方式
             0:进行原本搜索流程
             1:TAS专门搜索流程
*****************************************************************************/
enum RCM_TAS_SEARCH_METHOD_ENUM
{
    RCM_TAS_SEARCH_METHOD_ORIGINAL          = 0,
    RCM_TAS_SEARCH_METHOD_TAS               = 1,
    RCM_TAS_SEARCH_METHOD_BUTT
};
typedef VOS_UINT16 RCM_TAS_SEARCH_METHOD_ENUM_UINT16;

/*****************************************************************************
 枚举名    : RCM_AGENTC_DPDT_DELAY_CTRL_ENUM_UINT16
 枚举说明  : DPDT延迟切换操作指示:
             0:收到取消授权消息后停止一切dpdt操作
             1:取消DPDT延迟切换
             2:启动DPDT延迟切换
             3:更新最优DPDT值
             4:取消DPDT立即切换
             5:启动DPDT立即切换
             6:用于连接态下算法切换天线
*****************************************************************************/
enum RCM_AGENTC_DPDT_CTRL_ENUM
{
    RCM_AGENTC_DPDT_CTRL_STOP                  = 0,
    RCM_AGENTC_DPDT_DELAY_CTRL_STOP            = 1,
    RCM_AGENTC_DPDT_DELAY_CTRL_START           = 2,
    RCM_AGENTC_DPDT_DELAY_CTRL_UPDATE          = 3,
    RCM_AGENTC_DPDT_DIRECT_CTRL_STOP           = 4,
    RCM_AGENTC_DPDT_DIRECT_CTRL_START          = 5,
    RCM_AGENTC_DPDT_DIRECT_CTRL_UPDATE         = 6,
    RCM_AGENTC_DPDT_CTRL_BUTT
};
typedef VOS_UINT16 RCM_AGENTC_DPDT_CTRL_ENUM_UINT16;

/*****************************************************************************
 枚举名    : RCM_TAS_INHERIT_STATE_ENUM_UINT16
 枚举说明  : 主从模变更场景标记
             0:非主从模变更场景
             1:主从模变更场景
*****************************************************************************/
enum RCM_TAS_INHERIT_STATE_ENUM
{
    RCM_TAS_INHERIT_NONEXIST        = 0,
    RCM_TAS_INHERIT_EXIST           = 1,
    RCM_TAS_INHERIT_BUTT
};
typedef VOS_UINT16 RCM_TAS_INHERIT_STATE_ENUM_UINT16;

/*****************************************************************************
 枚举名    : RCM_TAS_AUTHORIZE_PHY_STATE_ENUM_UINT16
 枚举说明  : 物理层是否有授权
             0:无授权
             1:有授权
*****************************************************************************/
enum RCM_TAS_AUTHORIZE_PHY_STATE_ENUM
{
    RCM_TAS_AUTHORIZE_DISABLE        = 0,
    RCM_TAS_AUTHORIZE_ENABLE         = 1,
    RCM_TAS_AUTHORIZE_BUTT
};
typedef VOS_UINT16 RCM_TAS_AUTHORIZE_PHY_STATE_ENUM_UINT16;

/*****************************************************************************
 枚举名    : RCM_TAS_TX_BLANKING_TYPE_ENUM_UINT16
 枚举说明  : 物理层是否有授权
             0:无授权
             1:有授权
*****************************************************************************/
enum RCM_TAS_TX_BLANKING_TYPE_ENUM
{
    RCM_TAS_TX_BLANKING_TYPE_PROBE      = 0,
    RCM_TAS_TX_BLANKING_TYPE_SWITCH     = 1,
    RCM_TAS_TX_BLANKING_TYPE_MAS_PROBE  = 2,
    RCM_TAS_TX_BLANKING_TYPE_MAS_SWITCH = 3,
    RCM_TAS_TX_BLANKING_TYPE_BUTT
};
typedef VOS_UINT16 RCM_TAS_TX_BLANKING_TYPE_ENUM_UINT16;
/*****************************************************************************
枚举名    : RCM_PHY_ANT_DPDT_CTRL_ENUM
结构说明  : 天线DPDT控制类型的枚举

  1.日    期   : 2015年09月30日
    作    者   : shangguanshengchang 00266224
    修改内容   : MAS项目新增接口
*****************************************************************************/
enum RCM_PHY_ANT_DPDT_CTRL_ENUM
{
    RCM_PHY_ANT_DPDT_CTRL_00    = 0,                                            /* TAS DPDT=0,MAS DPDT=0 */
    RCM_PHY_ANT_DPDT_CTRL_01    = PHY_TAS_EN_BIT_MASK,                          /* TAS DPDT=1,MAS DPDT=0 */
    RCM_PHY_ANT_DPDT_CTRL_10    = PHY_MAS_EN_BIT_MASK,                          /* TAS DPDT=0,MAS DPDT=1 */
    RCM_PHY_ANT_DPDT_CTRL_11    = (PHY_MAS_EN_BIT_MASK | PHY_TAS_EN_BIT_MASK),  /* TAS DPDT=1,MAS DPDT=1 */
    RCM_PHY_ANT_DPDT_CTRL_BUTT
};
typedef VOS_UINT16  RCM_PHY_ANT_DPDT_CTRL_ENUM_UINT32;

/*****************************************************************************
 枚举名    : RCM_PHY_CALL_STATE_ENUM_UINT16
 枚举说明  : modem Background or Active Call状态
             0:Active Call状态
             1:Background Call状态
 注意      : 代码里有约束:背景call的枚举值必须为1，前景call的枚举值必须为0.
             不能任意修改。
*****************************************************************************/
enum RCM_PHY_CALL_STATE_ENUM
{
    RCM_PHY_CALL_ACTIVE           = 0,
    RCM_PHY_CALL_BACKGROUND       = 1,
    RCM_PHY_CALL_BUTT
};
typedef VOS_UINT16 RCM_PHY_CALL_STATE_ENUM_UINT16;

/*****************************************************************************
 枚举名    : RCM_PHY_CDMA_STATE_ENUM_UINT16
 枚举说明  : CDMA上下电标识
             0:CDMA Out Of Use
             1:CDMA In Use
*****************************************************************************/
enum RCM_PHY_CDMA_STATE_ENUM
{
    RCM_PHY_CDMA_OUT_OF_USE     = 0,
    RCM_PHY_CDMA_IN_USE         = 1,
    RCM_PHY_CDMA_STATE_BUTT
};
typedef VOS_UINT16 RCM_PHY_CDMA_STATE_ENUM_UINT16;

/*****************************************************************************
 枚举名    : RCM_PHY_ANT_SHARE_STATUS_ENUM_UINT16
 枚举说明  : CL+G1共天线状态标识
             0:L主集和G1副卡共天线，即S2开关直通
             1:L主集和CDMA共天线，即S2开关交叉
*****************************************************************************/
enum RCM_PHY_ANT_SHARE_STATUS
{
    RCM_PHY_ANT_SHARE_LTE_AND_G1PHY     = 0,
    RCM_PHY_ANT_SHARE_LTE_AND_CDMA      = 1,
    RCM_PHY_ANT_SHARE_BUTT
};
typedef VOS_UINT16 RCM_PHY_ANT_SHARE_STATUS_ENUM_UINT16;

/*****************************************************************************
 枚举名    : RCM_INTERFERENCE_ENUM_UINT16
 协议表格  :
 ASN.1描述 :
 枚举说明  : gphy1 进入连接态起启的标志
*****************************************************************************/
enum RCM_INTERFERENCE_ENUM
{
    RCM_GPHY1_INTERFERENCE_START        = 0,                                    /* START */
    RCM_GPHY1_INTERFERENCE_STOP         = 1,                                    /* STOP */
    RCM_GPHY1_INTERFERENCE_BUTT
};
typedef VOS_UINT16  RCM_INTERFERENCE_ENUM_UINT16;

/*****************************************************************************
 枚举名    : PHY_MTA_AFC_CLK_STATUS_ENUM
 枚举说明  : AFC时钟锁定状态枚举

  1.日    期   : 2015年9月7日
    作    者   : W00286360
    修改内容   : 新增枚举
*****************************************************************************/
enum RCM_PHY_AFC_CLK_STATUS_ENUM
{
    RCM_PHY_AFC_CLK_UNLOCKED           = 0,                                     /* AFC时钟频率非锁定状态 */
    RCM_PHY_AFC_CLK_LOCKED,                                                     /* AFC时钟频率锁定状态 */
    RCM_PHY_AFC_CLK_STATUS_BUTT
};
typedef VOS_UINT16 RCM_PHY_AFC_CLK_STATUS_ENUM_UINT16;


#ifdef LPS_RTT
/*****************************************************************************
 枚举名    :VOS_RATMODE_ENUM_UINT32
 协议表格  :
 ASN.1描述 :
 枚举说明  :睡眠唤醒时,接入模式定义
            注意；双卡双待的枚举值定义与协议栈和DRV协商为GULT;
            需要和DrvInterface.h中的PWC_COMM_MODE_E保持一致

*****************************************************************************/
enum VOS_RATMODE_ENUM
{
    VOS_RATMODE_GSM                         = 0,
    VOS_RATMODE_WCDMA                       = 1,
    VOS_RATMODE_LTE                         = 2,
    VOS_RATMODE_TDS                         = 3,
    VOS_RATMODE_1X                          = 4,
    VOS_RATMODE_HRPD                        = 5,
    VOS_RATMODE_BUTT
};
typedef VOS_UINT32 VOS_RATMODE_ENUM_UINT32;


#define VOS_VOID void
#endif
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
 结构名    : PHY_RCM_TASK_REQ_PARA_STRU
 协议表格  :
 ASN.1描述 :
 结构说明  : 任务请求消息数据结构
*****************************************************************************/
typedef struct
{
    RCM_MODE_ID_ENUM_UINT16                     enModeID;                       /* 模式ID */
    RCM_MODEM_ID_ENUM_UINT16                    enModemID;                      /* modem ID */
    RCM_RF_ID_ENUM_UINT16                       enRFID;                         /* RF ID */
    VOS_UINT16                                  usPriority;                     /* 任务优先级 */
    VOS_UINT16                                  usTaskID;                       /* 任务ID */
    RCM_RTT_STA_ENUM_UINT16                     enRttSta;                       /* RTT状态 */
    RCM_TASK_FIXPOS_FLAG_ENUM_UINT16            enFixPosFlag;                   /* 0-无固定启动时刻 1-有固定启动时刻 */
    RCM_TASK_LIMITLEN_FLAG_ENUM_UINT16          enLimitedLenFlag;               /* 0-无限长 1-有限长 */
    RCM_TASK_PERIOD_FLAG_ENUM_UINT16            enPeriodFlag;                   /* 0-无周期任务 1-周期任务 */
    RCM_TASK_PREEMPTIND_FLAG_ENUM_UINT16        enPreemptInd;                   /* 0-不可抢断 1-可抢断 */
    RCM_TASK_RELEASE_PRINCIPAL_ENUM_UINT16      enReleasePrincipal;             /* 0-PHY释放  1-RCM释放 2-只能通过PHY释放的固定时刻无限长任务 */
    RCM_TASK_IMMEDIATE_ASSIGN_FLAG_ENUM_UINT16  enImmediateAssignFlag;          /* 0-不需立即分配 1-需立即分配 */
    VOS_UINT16                                  usFailCnt;                      /* 连续失败次数 */
    VOS_UINT16                                  usFailThd;                      /* 最大容忍失败次数门限,如果填0表示不对当前任务进行优先级调整 */
    VOS_UINT32                                  ulStartPos;                     /* 任务启动时刻 必须填写有效值，如果无固定启动时刻则为最迟启动时刻，*/
    VOS_UINT32                                  ulLen;                          /* 任务长度.有限长任务必须填写有效值,不能超过(RCM_CLOCK_PERIOD/4), */
    VOS_UINT32                                  ulMinLen;                       /* 任务单次分配的最小长度,所有必须填写有效值,不能超过(RCM_CLOCK_PERIOD/4),如果有限长任务可以等于ulLen */
    VOS_UINT32                                  ulPeriod;                       /* 周期任务的周期，如果是周期任务必须填写有效值 */
    VOS_UINT32                                  ulPrmptPeriod;                  /* 无限长任务的抢占统计周期 如果是无限长任务必须填写有效值*/
    VOS_UINT32                                  ulPrmptTimeThd;                 /* 无限长任务单次被抢占时间门限 如果是无限长任务必须填写有效值*/
    VOS_UINT32                                  ulTotalPrmptTimeThd;            /* 无限长任务周期内累计被抢占时间门限 如果是无限长任务必须填写有效值*/
    VOS_UINT16                                  usTaskSnNum;                    /* 任务申请消息携带的Sn号码 */
    VOS_UINT16                                  usReserved;
}PHY_RCM_TASK_REQ_PARA_STRU;

/*****************************************************************************
 结构名    : PHY_RCM_TASK_APPLY_REQ_STRU
 协议表格  :
 ASN.1描述 :
 结构说明  : 任务请求消息数据结构
*****************************************************************************/
typedef struct
{
    VOS_MSG_HEADER                                                              /*_H2ASN_Skip*/
    RCM_PHY_MSG_ID_ENUM_UINT16                  enMsgID;                        /* 原语类型 */ /*_H2ASN_Skip*/
    VOS_UINT16                                  usRsv;                          /* 保留字段 */
    VOS_UINT16                                  usOPID;                         /* 操作标识 */
    VOS_UINT16                                  usRsv1;                         /* 保留字段 */
    PHY_RCM_TASK_REQ_PARA_STRU                  stTaskReqPara;                  /* 任务申请参数 */
}PHY_RCM_TASK_APPLY_REQ_STRU;

/*****************************************************************************
 结构名    : RCM_PHY_TASK_APPLY_CNF_STRU
 协议表格  :
 ASN.1描述 :
 结构说明  : 任务请求响应消息数据结构
*****************************************************************************/
typedef struct
{
    VOS_MSG_HEADER                                                              /*_H2ASN_Skip*/
    RCM_PHY_MSG_ID_ENUM_UINT16                  enMsgID;                        /* 原语类型 */ /*_H2ASN_Skip*/
    VOS_UINT16                                  usRsv;                          /* 保留字段 */
    VOS_UINT16                                  usOPID;                         /* 操作标识 */
    VOS_UINT16                                  usRsv1;                         /* 保留字段 */
    RCM_MODE_ID_ENUM_UINT16                     enModeID;                       /* 模式ID */
    RCM_MODEM_ID_ENUM_UINT16                    enModemID;                      /* modem ID */
    RCM_RSLT_ENUM_UINT16                        enResult;                       /* 确认结果 */
    RCM_PHY_TASK_ID_ENUM_UINT16                 usTaskID;                       /* 任务ID */
    VOS_UINT32                                  uw32KSysTime;                   /* 当前的32K 定时 */
}RCM_PHY_TASK_APPLY_CNF_STRU;

/*****************************************************************************
 结构名    : PHY_RCM_TASK_REL_REQ_STRU
 协议表格  :
 ASN.1描述 :
 结构说明  : 任务释放请求消息数据结构
*****************************************************************************/
typedef struct
{
    VOS_MSG_HEADER                                                              /*_H2ASN_Skip*/
    RCM_PHY_MSG_ID_ENUM_UINT16                  enMsgID;                        /* 原语类型 */ /*_H2ASN_Skip*/
    VOS_UINT16                                  usRsv;                          /* 保留字段 */
    VOS_UINT16                                  usOPID;                         /* 操作标识 */
    VOS_UINT16                                  usRsv1;                          /* 保留字段 */
    RCM_MODE_ID_ENUM_UINT16                     enModeID;                       /* 模式ID */
    RCM_MODEM_ID_ENUM_UINT16                    enModemID;                      /* modem ID */
    VOS_UINT32                                  uwRelTaskIdNum;                 /* 待删除任务个数，对应发ausRelTaskId的下标 */
    VOS_UINT16                                  ausRelTaskId[RCM_REL_TASK_ID_MAX_NUM]; /* 待删除任务数组 */
}PHY_RCM_TASK_REL_REQ_STRU;

/*****************************************************************************
 结构名    : RCM_PHY_TASK_REL_CNF_STRU
 协议表格  :
 ASN.1描述 :
 结构说明  : 单个任务释放请求响应消息数据结构
*****************************************************************************/
typedef struct
{
    VOS_MSG_HEADER                                                              /*_H2ASN_Skip*/
    RCM_PHY_MSG_ID_ENUM_UINT16                  enMsgID;                        /* 原语类型 */ /*_H2ASN_Skip*/
    VOS_UINT16                                  usRsv;                          /* 保留字段 */
    VOS_UINT16                                  usOPID;                         /* 操作标识 */
    VOS_UINT16                                  usRsv1;                         /* 保留字段 */
    RCM_MODE_ID_ENUM_UINT16                     enModeID;                       /* 模式ID */
    RCM_MODEM_ID_ENUM_UINT16                    enModemID;                      /* modem ID */
    VOS_UINT32                                  uw32KSysTime;                   /* 当前的32K 定时 */
    RCM_RSLT_ENUM_UINT16                        enResult;                       /* 确认结果,RCM只检测MODEM和MODEID的正确性  */
    VOS_UINT16                                  usRsv2;
}RCM_PHY_TASK_REL_CNF_STRU;

/*****************************************************************************
 结构名    : PHY_RCM_TASK_RELALL_REQ_STRU
 协议表格  :
 ASN.1描述 :
 结构说明  : 任务全部释放请求消息数据结构
*****************************************************************************/
typedef struct
{
    VOS_MSG_HEADER                                                              /*_H2ASN_Skip*/
    RCM_PHY_MSG_ID_ENUM_UINT16                  enMsgID;                        /* 原语类型 */ /*_H2ASN_Skip*/
    VOS_UINT16                                  usRsv;                          /* 保留字段 */
    VOS_UINT16                                  usOPID;                         /* 操作标识 */
    VOS_UINT16                                  usRsv1;                          /* 保留字段 */
    RCM_MODE_ID_ENUM_UINT16                     enModeID;                       /* 模式ID */
    RCM_MODEM_ID_ENUM_UINT16                    enModemID;                      /* modem ID */
}PHY_RCM_TASK_RELALL_REQ_STRU;

/*****************************************************************************
 结构名    : RCM_PHY_TASK_RELALL_CNF_STRU
 协议表格  :
 ASN.1描述 :
 结构说明  : 全部任务释放请求响应消息数据结构
*****************************************************************************/
typedef struct
{
    VOS_MSG_HEADER                                                              /*_H2ASN_Skip*/
    RCM_PHY_MSG_ID_ENUM_UINT16                  enMsgID;                        /* 原语类型 */ /*_H2ASN_Skip*/
    VOS_UINT16                                  usRsv;                          /* 保留字段 */
    VOS_UINT16                                  usOPID;                         /* 操作标识 */
    VOS_UINT16                                  usRsv1;                          /* 保留字段 */
    RCM_MODE_ID_ENUM_UINT16                     enModeID;                       /* 模式ID */
    RCM_MODEM_ID_ENUM_UINT16                    enModemID;                      /* modem ID */
    VOS_UINT32                                  uw32KSysTime;                   /* 当前的32K 定时 */
    RCM_RSLT_ENUM_UINT16                        enResult;                       /* 确认结果 */
    VOS_UINT16                                  usRsv2;                         /* 保留字 */
}RCM_PHY_TASK_RELALL_CNF_STRU;


/*****************************************************************************
 结构名    : PHY_RCM_AWAKE_REQ_STRU
 协议表格  :
 ASN.1描述 :
 结构说明  : wake请求消息数据结构
*****************************************************************************/
typedef struct
{
    VOS_MSG_HEADER                                                              /*_H2ASN_Skip*/
    RCM_PHY_MSG_ID_ENUM_UINT16                  enMsgID;                        /* 原语类型 */ /*_H2ASN_Skip*/
    VOS_UINT16                                  usRsv;                          /* 保留字段 */
    VOS_UINT16                                  usOPID;                         /* 操作标识 */
    VOS_UINT16                                  usRsv1;                         /* 保留字段 */
    RCM_MODE_ID_ENUM_UINT16                     enModeID;                       /* 模式ID */
    RCM_MODEM_ID_ENUM_UINT16                    enModemID;                      /* modem ID */
}PHY_RCM_AWAKE_REQ_STRU;

/*****************************************************************************
 结构名    : PHY_RCM_SLEEP_REQ_STRU
 协议表格  :
 ASN.1描述 :
 结构说明  : sleep请求消息数据结构
*****************************************************************************/
typedef struct
{
    VOS_MSG_HEADER                                                              /*_H2ASN_Skip*/
    RCM_PHY_MSG_ID_ENUM_UINT16                  enMsgID;                        /* 原语类型 */ /*_H2ASN_Skip*/
    VOS_UINT16                                  usRsv;                          /* 保留字段 */
    VOS_UINT16                                  usOPID;                         /* 操作标识 */
    VOS_UINT16                                  usRsv1;                         /* 保留字段 */
    RCM_MODE_ID_ENUM_UINT16                     enModeID;                       /* 模式ID */
    RCM_MODEM_ID_ENUM_UINT16                    enModemID;                      /* modem ID */
}PHY_RCM_SLEEP_REQ_STRU;

/*****************************************************************************
 结构名    : RCM_PHY_TASK_PREEMPT_IND_STRU
 协议表格  :
 ASN.1描述 :
 结构说明  : 任务抢占指示消息数据结构
*****************************************************************************/
typedef struct
{
    VOS_MSG_HEADER                                                              /*_H2ASN_Skip*/
    RCM_PHY_MSG_ID_ENUM_UINT16                  enMsgID;                        /* 原语类型 */ /*_H2ASN_Skip*/
    VOS_UINT16                                  usRsv;                          /* 保留字段 */
    VOS_UINT16                                  usOPID;                         /* 操作标识 */
    VOS_UINT16                                  usRsv1;                         /* 保留字段 */
    RCM_MODE_ID_ENUM_UINT16                     enModeID;                       /* 模式ID */
    RCM_MODEM_ID_ENUM_UINT16                    enModemID;                      /* modem ID */
    RCM_PHY_TASK_ID_ENUM_UINT16                 usTaskID;                       /* 任务ID */
    RCM_RF_ID_ENUM_UINT16                       enRfID;                         /* 被抢占的RFID */
    VOS_UINT32                                  ulPreemptPos;                   /* 任务抢占时刻*/
    VOS_UINT32                                  ul32KSysTime;                   /* 当前的32K 定时 */
}RCM_PHY_TASK_PREEMPT_IND_STRU;

/*****************************************************************************
 结构名    : PHY_RCM_TASK_PREEMPT_ACK_STRU
 协议表格  :
 ASN.1描述 :
 结构说明  : 任务抢占确认消息数据结构
*****************************************************************************/
typedef struct
{
    VOS_MSG_HEADER                                                              /*_H2ASN_Skip*/
    RCM_PHY_MSG_ID_ENUM_UINT16                  enMsgID;                        /* 原语类型 */ /*_H2ASN_Skip*/
    VOS_UINT16                                  usRsv;                          /* 保留字段 */
    VOS_UINT16                                  usOPID;                         /* 操作标识 */
    VOS_UINT16                                  usRsv1;                         /* 保留字段 */
    RCM_MODE_ID_ENUM_UINT16                     enModeID;                       /* 模式ID */
    RCM_MODEM_ID_ENUM_UINT16                    enModemID;                      /* modem ID */
    RCM_RF_ID_ENUM_UINT16                       enRfID;                         /* 被抢占的RFID */
    RCM_RSLT_ENUM_UINT16                        enResult;                       /* 确认结果 */
    RCM_PHY_TASK_ID_ENUM_UINT16                 usTaskID;                       /* 任务ID */
    VOS_UINT16                                  usReserved;                     /* 保留字 */
}PHY_RCM_TASK_PREEMPT_ACK_STRU;

/*****************************************************************************
 结构名    : RCM_PHY_TASK_RESUME_IND_STRU
 协议表格  :
 ASN.1描述 :
 结构说明  : 任务恢复指示消息数据结构
*****************************************************************************/
typedef struct
{
    VOS_MSG_HEADER                                                              /*_H2ASN_Skip*/
    RCM_PHY_MSG_ID_ENUM_UINT16                  enMsgID;                        /* 原语类型 */ /*_H2ASN_Skip*/
    VOS_UINT16                                  usRsv;                          /* 保留字段 */
    VOS_UINT16                                  usOPID;                         /* 操作标识 */
    VOS_UINT16                                  usRsv1;                         /* 保留字段 */
    RCM_MODE_ID_ENUM_UINT16                     enModeID;                       /* 模式ID */
    RCM_MODEM_ID_ENUM_UINT16                    enModemID;                      /* modem ID */
    VOS_UINT32                                  ulResumPos;                     /* 任务恢复时刻*/
    RCM_PHY_TASK_ID_ENUM_UINT16                 usTaskID;                       /* 任务ID */
    VOS_UINT16                                  usRsv2;                         /* 保留字 */
    VOS_UINT32                                  ul32KSysTime;                   /* 当前的32K 定时 */
}RCM_PHY_TASK_RESUME_IND_STRU;

/*****************************************************************************
 结构名    : PHY_RCM_TASK_RESUME_ACK_STRU
 协议表格  :
 ASN.1描述 :
 结构说明  : 任务恢复确认消息数据结构
*****************************************************************************/
typedef struct
{
    VOS_MSG_HEADER                                                              /*_H2ASN_Skip*/
    RCM_PHY_MSG_ID_ENUM_UINT16                  enMsgID;                        /* 原语类型 */ /*_H2ASN_Skip*/
    VOS_UINT16                                  usRsv;                          /* 保留字段 */
    VOS_UINT16                                  usOPID;                         /* 操作标识 */
    VOS_UINT16                                  usRsv1;                         /* 保留字段 */
    RCM_MODE_ID_ENUM_UINT16                     enModeID;                       /* 模式ID */
    RCM_MODEM_ID_ENUM_UINT16                    enModemID;                      /* modem ID */
    RCM_RSLT_ENUM_UINT16                        enResult;                       /* 确认结果 */
    RCM_PHY_TASK_ID_ENUM_UINT16                 usTaskID;                       /* 任务ID */
}PHY_RCM_TASK_RESUME_ACK_STRU;

/*****************************************************************************
 结构名    : RCM_PHY_MSG_STRU
 协议表格  :
 ASN.1描述 :
 结构说明  : 消息队列数据结构
*****************************************************************************/
typedef struct
{
    RCM_CMD_ENUM_UINT16                         enCmdID;                        /* 消息CMD类型 */
    VOS_UINT16                                  usTaskID;                       /* 任务ID */
    VOS_UINT32                                  ulStartPos;                     /* 任务分配的启动时刻 */
    VOS_UINT32                                  ulStopPos;                      /* 任务分配的结束时刻 */
}RCM_PHY_MSG_STRU;


/*****************************************************************************
 结构名    : RCM_PHY_RPT_MSG_STRU
 协议表格  :
 ASN.1描述 :
 结构说明  : 消息队列数据结构
*****************************************************************************/

typedef struct
{
    VOS_UINT16                                  usIndex;                        /* 任务ID */
    RCM_MODE_ID_ENUM_UINT16                     enModeID;                       /* 模式ID */
    RCM_CMD_ENUM_UINT16                         enCmdID;                        /* 消息CMD类型 */
    VOS_UINT16                                  usTaskID;                       /* 任务ID */
    VOS_UINT32                                  ulStartPos;                     /* 任务分配的启动时刻 */
    VOS_UINT32                                  ulStopPos;                      /* 任务分配的结束时刻 */
}RCM_PHY_RPT_MSG_STRU;


/*****************************************************************************
 结构名    : RCM_PHY_MSG_LIST_STRU
 协议表格  :
 ASN.1描述 :
 结构说明  : 各个MODE的消息缓存
*****************************************************************************/
typedef struct
{
    VOS_UINT16                                  usRdIdx;                        /* 读指针 */
    VOS_UINT16                                  usWrIdx;                        /* 写指针 */
    RCM_PHY_MSG_STRU                            astMsgList[RCM_PHY_ASSIGN_BUF_SIZE];    /* 消息队列 */
}RCM_PHY_MSG_LIST_STRU;

/*****************************************************************************
 结构名    : RCM_PHY_ASSIGN_IND_STRU
 协议表格  :
 ASN.1描述 :
 结构说明  : 任务分配指示消息数据结构
*****************************************************************************/
typedef struct
{
    VOS_MSG_HEADER                                                              /*_H2ASN_Skip*/
    RCM_PHY_MSG_ID_ENUM_UINT16                  enMsgID;                        /* 原语类型 */ /*_H2ASN_Skip*/
    VOS_UINT16                                  usRsv;                          /* 保留字 */
    VOS_UINT16                                  usOPID;                         /* 操作标识 */
    VOS_UINT16                                  usRsv1;                         /* 保留字 */
    RCM_MODE_ID_ENUM_UINT16                     enModeID;                       /* 模式ID */
    RCM_MODEM_ID_ENUM_UINT16                    enModemID;                      /* modem ID */
    VOS_UINT32                                  uw32KSysTime;                   /* 当前的32K 定时 */
    VOS_UINT16                                  usWrIdx;                        /* 当前发送assgin消息的时候，WrIdx的值 */
    VOS_UINT16                                  usRsv2;                         /* 保留字 */
}RCM_PHY_ASSIGN_IND_STRU;

/*****************************************************************************
 结构名    : RCM_PHY_TASK_PROTECT_IND_STRU
 协议表格  :
 ASN.1描述 :
 结构说明  : PROTECT消息数据结构
*****************************************************************************/
typedef struct
{
    VOS_MSG_HEADER                                                              /*_H2ASN_Skip*/
    RCM_PHY_MSG_ID_ENUM_UINT16                  enMsgID;                        /* 原语类型 */ /*_H2ASN_Skip*/
    VOS_UINT16                                  usRsv;                          /* 保留字 */
    VOS_UINT16                                  usOPID;                         /* 操作标识 */
    VOS_UINT16                                  usRsv1;                         /* 保留字 */
    RCM_MODE_ID_ENUM_UINT16                     enModeID;                       /* 模式ID */
    RCM_MODEM_ID_ENUM_UINT16                    enModemID;                      /* modem ID */
    VOS_UINT32                                  uw32KSysTime;                   /* 当前的32K 定时 */
}RCM_PHY_TASK_PROTECT_IND_STRU;

/*****************************************************************************
 结构名    : RCM_PHY_TASK_DEPROTECT_IND_STRU
 协议表格  :
 ASN.1描述 :
 结构说明  : DEPROTECT消息数据结构
*****************************************************************************/
typedef struct
{
    VOS_MSG_HEADER                                                              /*_H2ASN_Skip*/
    RCM_PHY_MSG_ID_ENUM_UINT16                  enMsgID;                        /* 原语类型 */ /*_H2ASN_Skip*/
    VOS_UINT16                                  usRsv;                          /* 保留字 */
    VOS_UINT16                                  usOPID;                         /* 操作标识 */
    VOS_UINT16                                  usRsv1;                         /* 保留字 */
    RCM_MODE_ID_ENUM_UINT16                     enModeID;                       /* 模式ID */
    RCM_MODEM_ID_ENUM_UINT16                    enModemID;                      /* modem ID */
    VOS_UINT32                                  uw32KSysTime;                   /* 当前的32K 定时 */
}RCM_PHY_TASK_DEPROTECT_IND_STRU;


/*****************************************************************************
 结构名    : RCM_PHY_ASSIGN_IND_FORTL_STRU
 协议表格  :
 ASN.1描述 :
 结构说明  : 任务分配指示消息数据结构发给TL
*****************************************************************************/
typedef struct
{
    VOS_MSG_HEADER                                                              /*_H2ASN_Skip*/
    RCM_PHY_MSG_ID_ENUM_UINT16                  enMsgID;                        /* 原语类型 */ /*_H2ASN_Skip*/
    VOS_UINT16                                  usRsv;                          /* 保留字 */
    VOS_UINT16                                  usOPID;                         /* 操作标识 */
    VOS_UINT16                                  usTaskSnNum;                    /* 任务的Sn序列号 */
    RCM_MODE_ID_ENUM_UINT16                     enModeID;                       /* 模式ID */
    RCM_MODEM_ID_ENUM_UINT16                    enModemID;                      /* modem ID */
    VOS_UINT32                                  uw32KSysTime;                   /* 当前的32K 定时 */
    RCM_PHY_MSG_STRU                            stMsg;
}RCM_PHY_ASSIGN_IND_FORTL_STRU;

/*****************************************************************************
 结构名    : PHY_RCM_ASSIGN_ACK_STRU
 协议表格  :
 ASN.1描述 :
 结构说明  : 任务分配确认消息数据结构
*****************************************************************************/
typedef struct
{
    VOS_MSG_HEADER                                                              /*_H2ASN_Skip*/
    RCM_PHY_MSG_ID_ENUM_UINT16                  enMsgID;                        /* 原语类型 */ /*_H2ASN_Skip*/
    VOS_UINT16                                  usRsv;                          /* 保留字段 */
    VOS_UINT16                                  usOPID;                         /* 操作标识 */
    VOS_UINT16                                  usRsv1;                         /* 保留字 */
    RCM_MODE_ID_ENUM_UINT16                     enModeID;                       /* 模式ID */
    RCM_MODEM_ID_ENUM_UINT16                    enModemID;                      /* modem ID */
    RCM_RSLT_ENUM_UINT16                        enResult;                       /* 确认结果 */
    VOS_UINT16                                  usRsv2;                         /* 保留字段 */
}PHY_RCM_ASSIGN_ACK_STRU;

/*****************************************************************************
 结构名    : RCM_PHY_CLOCK_CAL_IND_STRU
 协议表格  :
 ASN.1描述 :
 结构说明  : 时钟校准指示消息数据结构
*****************************************************************************/
typedef struct
{
    VOS_MSG_HEADER                                                              /*_H2ASN_Skip*/
    RCM_PHY_MSG_ID_ENUM_UINT16                  enMsgID;                        /* 原语类型 */ /*_H2ASN_Skip*/
    VOS_UINT16                                  usRsv;                          /* 保留字 */
    VOS_UINT16                                  usOPID;                         /* 操作标识 */
    VOS_UINT16                                  usRsv1;                         /* 保留字 */
    RCM_MODE_ID_ENUM_UINT16                     enModeID;                       /* 模式ID */
    RCM_MODEM_ID_ENUM_UINT16                    enModemID;                      /* modem ID */
}RCM_PHY_CLOCK_CAL_IND_STRU;

/*****************************************************************************
 结构名    : PHY_RCM_CLOCK_CAL_ACK_STRU
 协议表格  :
 ASN.1描述 :
 结构说明  : 时钟校准上报消息数据结构
*****************************************************************************/
typedef struct
{
    VOS_MSG_HEADER                                                              /*_H2ASN_Skip*/
    RCM_PHY_MSG_ID_ENUM_UINT16                  enMsgID;                        /* 原语类型 */ /*_H2ASN_Skip*/
    VOS_UINT16                                  usRsv;                          /* 保留字 */
    VOS_UINT16                                  usOPID;                         /* 操作标识 */
    VOS_UINT16                                  usRsv1;                         /* 保留字 */
    RCM_MODE_ID_ENUM_UINT16                     enModeID;                       /* 模式ID */
    RCM_MODEM_ID_ENUM_UINT16                    enModemID;                      /* modem ID */
    RCM_RSLT_ENUM_UINT16                        enResult;                       /* 确认结果 */
    RCM_DIRECTION_ENUM_UINT16                   enDirection;                    /* 调整方向 */
    VOS_UINT32                                  ulAdjustValue;                  /* 调整周期 */
}PHY_RCM_CLOCK_CAL_ACK_STRU;

/*****************************************************************************
 结构名    : RCM_PHY_OVERTIME_IND_STRU
 协议表格  :
 ASN.1描述 :
 结构说明  : 任务超时上报消息数据结构
*****************************************************************************/
typedef struct
{
    VOS_MSG_HEADER                                                              /*_H2ASN_Skip*/
    RCM_PHY_MSG_ID_ENUM_UINT16                  enMsgID;                        /* 原语类型 */ /*_H2ASN_Skip*/
    VOS_UINT16                                  usRsv;                          /* 保留字 */
    VOS_UINT16                                  usOPID;                         /* 操作标识 */
    VOS_UINT16                                  usRsv1;                         /* 保留字 */
    RCM_MODE_ID_ENUM_UINT16                     enModeID;                       /* 模式ID */
    RCM_MODEM_ID_ENUM_UINT16                    enModemID;                      /* modem ID */
    RCM_PHY_TASK_ID_ENUM_UINT16                 usTaskID;                       /* 任务ID */
    VOS_UINT16                                  usRsv2;                         /* 保留字 */
    VOS_UINT32                                  ulStartPos;                     /* 任务分配的启动时刻 */
    VOS_UINT32                                  ulStopPos;                      /* 任务分配的结束时刻 */
}RCM_PHY_OVERTIME_IND_STRU;

/*****************************************************************************
 结构名    : PHY_RCM_GET_MSGLISTADDR_REQ_STRU
 协议表格  :
 ASN.1描述 :
 结构说明  : 任务获取消息队列地址结构
*****************************************************************************/
typedef struct
{
    VOS_MSG_HEADER                                                              /*_H2ASN_Skip*/
    RCM_PHY_MSG_ID_ENUM_UINT16                  enMsgID;                        /*_H2ASN_Skip*/ /* 原语类型 */
    VOS_UINT16                                  usRsv;                          /* 保留字 */
    VOS_UINT16                                  usOPID;                         /* 操作标识 */
    VOS_UINT16                                  usRsv1;                         /* 保留字 */
    RCM_MODE_ID_ENUM_UINT16                     enModeID;                       /* 模式ID */
    RCM_MODEM_ID_ENUM_UINT16                    enModemID;                      /* modem ID */
}PHY_RCM_GET_MSGLISTADDR_REQ_STRU;

/*****************************************************************************
 结构名    : RCM_PHY_GET_MSGLISTADDR_CNF_STRU
 协议表格  :
 ASN.1描述 :
 结构说明  : 返回消息队列地址结构
*****************************************************************************/
typedef struct
{
    VOS_MSG_HEADER                                                              /*_H2ASN_Skip*/
    RCM_PHY_MSG_ID_ENUM_UINT16                  enMsgID;                        /*_H2ASN_Skip*/ /* 原语类型 */
    VOS_UINT16                                  usRsv;                          /* 保留字 */
    VOS_UINT16                                  usOPID;                         /* 操作标识 */
    VOS_UINT16                                  usRsv1;                         /* 保留字 */
    RCM_MODE_ID_ENUM_UINT16                     enModeID;                       /* 模式ID */
    RCM_MODEM_ID_ENUM_UINT16                    enModemID;                      /* modem ID */
    RCM_RSLT_ENUM_UINT16                        enResult;                       /* 确认结果 */
    VOS_UINT16                                  usRsv2;                         /* 保留字 */
    VOS_UINT32                                  uw32KSysTime;                   /* 当前的32K 定时 */
    RCM_PHY_MSG_LIST_STRU                      *pstMsgList;                     /* 消息队列首地址 */
}RCM_PHY_GET_MSGLISTADDR_CNF_STRU;

/*****************************************************************************
 结构名    : PHY_RCM_TASK_COMPLETE_REQ_STRU
 协议表格  :
 ASN.1描述 :
 结构说明  : 通知RCM任务执行完成
*****************************************************************************/
typedef struct
{
    VOS_MSG_HEADER                                                              /*_H2ASN_Skip*/
    RCM_PHY_MSG_ID_ENUM_UINT16                  enMsgID;                        /* 原语类型 */ /*_H2ASN_Skip*/
    VOS_UINT16                                  usRsv;                          /* 保留字 */
    VOS_UINT16                                  usOPID;                         /* 操作标识 */
    VOS_UINT16                                  usRsv1;                         /* 保留字 */
    RCM_MODE_ID_ENUM_UINT16                     enModeID;                       /* 模式ID */
    RCM_MODEM_ID_ENUM_UINT16                    enModemID;                      /* modem ID */
    RCM_PHY_TASK_ID_ENUM_UINT16                 usTaskID;                       /* 任务ID */
    RCM_RF_ID_ENUM_UINT16                       enRfID;                         /* 任务所在的RFID */
    VOS_UINT32                                  ulStartPos;                     /* 提前完成的周期任务的启动时刻 */
}PHY_RCM_TASK_COMPLETE_REQ_STRU;

/*****************************************************************************
 结构名    : RCM_PHY_TASK_COMPLETE_CNF_STRU
 协议表格  :
 ASN.1描述 :
 结构说明  : 通知PHY收到任务执行完成指示
*****************************************************************************/
typedef struct
{
    VOS_MSG_HEADER                                                              /*_H2ASN_Skip*/
    RCM_PHY_MSG_ID_ENUM_UINT16                  enMsgID;                        /* 原语类型 */ /*_H2ASN_Skip*/
    VOS_UINT16                                  usRsv;                          /* 保留字 */
    VOS_UINT16                                  usOPID;                         /* 操作标识 */
    VOS_UINT16                                  usRsv1;                         /* 保留字 */
    RCM_MODE_ID_ENUM_UINT16                     enModeID;                       /* 模式ID */
    RCM_MODEM_ID_ENUM_UINT16                    enModemID;                      /* modem ID */
    RCM_PHY_TASK_ID_ENUM_UINT16                 usTaskID;                       /* 任务ID */
    RCM_RF_ID_ENUM_UINT16                       enRfID;                         /* 任务所在的RFID */
    RCM_RSLT_ENUM_UINT16                        enResult;                       /* 确认结果 */
    VOS_UINT16                                  usRsv2;                         /* 保留字 */
    VOS_UINT32                                  uw32KSysTime;                   /* 当前32k时间 */
}RCM_PHY_TASK_COMPLETE_CNF_STRU;

/*****************************************************************************
 结构名    : RCM_WMODE_TIMING_STRU
 协议表格  :
 结构说明  : W模系统时间
*****************************************************************************/
typedef struct
{
    VOS_UINT16                          uhwSfnCnt;                              /* SFN计数，范围0~4095 */
    VOS_UINT16                          uhwSlotCnt;                             /* 时隙计数，范围0~14 */
    VOS_UINT16                          uhwChipCnt;                             /* chip计数，范围0~2559 */
    VOS_UINT16                          uhwClkCnt;                              /* chip内时钟计数，范围0~15 */
    RCM_WMODE_TYPE_ENUM_UINT16          enWMode;                                /* W模的时间类型 */
    VOS_UINT16                          uhwReserved;                            /* 保留位 */
}RCM_WMODE_TIMING_STRU;

/*****************************************************************************
 结构名    : RCM_GMODE_TIMING_STRU
 协议表格  :
 结构说明  : G模系统时间
*****************************************************************************/
typedef struct
{
    VOS_UINT32                          uwFnCnt;                                /* FN计数 */
    VOS_UINT16                          uhwQbCnt;                               /* 系统定时帧内Qb计数，范围0~4999 */
    VOS_UINT16                          uhwReserved;                            /* 保留位 */
}RCM_GMODE_TIMING_STRU;

/*****************************************************************************
 结构名    : RCM_LTEMODE_TIMING_STRU
 协议表格  :
 结构说明  : LTE模系统时间
*****************************************************************************/
typedef struct
{
    VOS_UINT16                          uwSfnCnt;                               /* SFN计数，范围0~1023 */
    VOS_UINT16                          uhwsubfrm_cnt;                          /* 子帧计数 */
    VOS_UINT16                          uhwTsCnt;                               /* 子帧内计数 */
    VOS_UINT16                          uhwReserved;                            /* 保留位 */
}RCM_LTEMODE_TIMING_STRU;

/*****************************************************************************
 结构名    : RCM_TDMODE_TIMING_STRU
 协议表格  :
 结构说明  : TD模系统时间
*****************************************************************************/
typedef struct
{
    VOS_UINT32                          uwSfnCnt;                               /* tcfsr系统子帧号0~65535循环计数，TDS实际有效子帧范围为0~8191 */
    VOS_UINT32                          uwSubFrmcnt;                            /* framc帧计数 */
}RCM_TDMODE_TIMING_STRU;

/*****************************************************************************
 结构名    : RCM_TIMING_STRU
 协议表格  :
 结构说明  : 各模系统时间和32K定时
*****************************************************************************/
typedef struct
{
    RCM_WMODE_TIMING_STRU               stWTime;                                /* W模系统时间 */
    VOS_UINT32                          uwCTime;                                /* C模系统时间 */
    RCM_GMODE_TIMING_STRU               stGmTime;                               /* Gm模系统时间 */
    RCM_GMODE_TIMING_STRU               stGsTime;                               /* Gs模系统时间 */
    RCM_LTEMODE_TIMING_STRU             stLTETime;                              /* LTE模系统时间 */
    RCM_TDMODE_TIMING_STRU              stTDSTime;                              /* TD模系统时间 */
    VOS_UINT32                          uw32KSysTime;                           /* 32K系统定时 */
}RCM_TIMING_STRU;

/*****************************************************************************
 结构名    : RCM_PHY_COM_AVOID_PAGING_CFG_REQ_STRU
 协议表格  :
 ASN.1描述 :
 结构说明  : 通知被控PHY把寻呼位置配置到CTU寄存器中, 让主控去避让寻呼
*****************************************************************************/
typedef struct
{
    VOS_MSG_HEADER                                                              /*_H2ASN_Skip*/
    RCM_PHY_MSG_ID_ENUM_UINT16                  enMsgID;                        /* 原语类型 */ /*_H2ASN_Skip*/
    VOS_UINT16                                  usRsv;                          /* 保留字段 */
    VOS_UINT16                                  usOPID;                         /* 操作标识 */
    VOS_UINT16                                  usRsv1;                         /* 保留字段 */
    RCM_MODE_ID_ENUM_UINT16                     enModeID;                       /* 模式ID */
    RCM_MODEM_ID_ENUM_UINT16                    enModemID;                      /* modem ID */
}RCM_PHY_AVOID_PAGING_CFG_REQ_STRU;

/*****************************************************************************
 结构名    : PHY_RCM_COM_AVOID_PAGING_CFG_CNF_STRU
 协议表格  :
 ASN.1描述 :
 结构说明  : 通知RCM寻呼位置配置完成
*****************************************************************************/
typedef struct
{
    VOS_MSG_HEADER                                                              /*_H2ASN_Skip*/
    RCM_PHY_MSG_ID_ENUM_UINT16                  enMsgID;                        /* 原语类型 */ /*_H2ASN_Skip*/
    VOS_UINT16                                  usRsv;                          /* 保留字段 */
    VOS_UINT16                                  usOPID;                         /* 操作标识 */
    VOS_UINT16                                  usRsv1;                         /* 保留字段 */
    RCM_MODE_ID_ENUM_UINT16                     enModeID;                       /* 模式ID */
    RCM_MODEM_ID_ENUM_UINT16                    enModemID;                      /* modem ID */
}PHY_RCM_AVOID_PAGING_CFG_CNF_STRU;

/*****************************************************************************
 结构名    : RCM_PHY_ONLY_START_MAS_REQ_STRU
 协议表格  :
 ASN.1描述 :
 结构说明  : 通知被控PHY给予MAS授权
*****************************************************************************/
typedef struct
{
    VOS_MSG_HEADER                                                              /*_H2ASN_Skip*/
    RCM_PHY_MSG_ID_ENUM_UINT16                  enMsgID;                        /* 原语类型 */ /*_H2ASN_Skip*/
    VOS_UINT16                                  usRsv;                          /* 保留字段 */
    VOS_UINT16                                  usOPID;                         /* 操作标识 */
    VOS_UINT16                                  usRsv1;                         /* 保留字段 */
    RCM_MODE_ID_ENUM_UINT16                     enModeID;                       /* 模式ID */
    RCM_MODEM_ID_ENUM_UINT16                    enModemID;                      /* modem ID */
}RCM_PHY_ONLY_START_MAS_REQ_STRU;

/*****************************************************************************
 结构名    : PHY_RCM_ONLY_START_MAS_CNF_STRU
 协议表格  :
 ASN.1描述 :
 结构说明  : 通知RCM授权完成指示
*****************************************************************************/
typedef struct
{
    VOS_MSG_HEADER                                                              /*_H2ASN_Skip*/
    RCM_PHY_MSG_ID_ENUM_UINT16                  enMsgID;                        /* 原语类型 */ /*_H2ASN_Skip*/
    VOS_UINT16                                  usRsv;                          /* 保留字段 */
    VOS_UINT16                                  usOPID;                         /* 操作标识 */
    VOS_UINT16                                  usRsv1;                         /* 保留字段 */
    RCM_MODE_ID_ENUM_UINT16                     enModeID;                       /* 模式ID */
    RCM_MODEM_ID_ENUM_UINT16                    enModemID;                      /* modem ID */
}PHY_RCM_ONLY_START_MAS_CNF_STRU;

/*****************************************************************************
 结构名    : RCM_PHY_ONLY_STOP_MAS_REQ_STRU
 协议表格  :
 ASN.1描述 :
 结构说明  : 通知被控PHY给予MAS授权
*****************************************************************************/
typedef struct
{
    VOS_MSG_HEADER                                                              /*_H2ASN_Skip*/
    RCM_PHY_MSG_ID_ENUM_UINT16                  enMsgID;                        /* 原语类型 */ /*_H2ASN_Skip*/
    VOS_UINT16                                  usRsv;                          /* 保留字段 */
    VOS_UINT16                                  usOPID;                         /* 操作标识 */
    VOS_UINT16                                  usRsv1;                         /* 保留字段 */
    RCM_MODE_ID_ENUM_UINT16                     enModeID;                       /* 模式ID */
    RCM_MODEM_ID_ENUM_UINT16                    enModemID;                      /* modem ID */
}RCM_PHY_ONLY_STOP_MAS_REQ_STRU;

/*****************************************************************************
 结构名    : PHY_RCM_ONLY_STOP_MAS_CNF_STRU
 协议表格  :
 ASN.1描述 :
 结构说明  : 通知RCM授权完成指示
*****************************************************************************/
typedef struct
{
    VOS_MSG_HEADER                                                              /*_H2ASN_Skip*/
    RCM_PHY_MSG_ID_ENUM_UINT16                  enMsgID;                        /* 原语类型 */ /*_H2ASN_Skip*/
    VOS_UINT16                                  usRsv;                          /* 保留字段 */
    VOS_UINT16                                  usOPID;                         /* 操作标识 */
    VOS_UINT16                                  usRsv1;                         /* 保留字段 */
    RCM_MODE_ID_ENUM_UINT16                     enModeID;                       /* 模式ID */
    RCM_MODEM_ID_ENUM_UINT16                    enModemID;                      /* modem ID */
}PHY_RCM_ONLY_STOP_MAS_CNF_STRU;


/*****************************************************************************
 结构名    : RCM_PHY_START_TAS_REQ_STRU
 协议表格  :
 ASN.1描述 :
 结构说明  : 通知PHY授权TAS
*****************************************************************************/
typedef struct
{
    VOS_MSG_HEADER                                                              /*_H2ASN_Skip*/
    RCM_PHY_MSG_ID_ENUM_UINT16                  enMsgID;                        /* 原语类型 */ /*_H2ASN_Skip*/
    VOS_UINT16                                  usRsv;                          /* 保留字段 */
    VOS_UINT16                                  usOPID;                         /* 操作标识 */
    VOS_UINT16                                  usRsv1;                         /* 保留字段 */
    RCM_MODE_ID_ENUM_UINT16                     enModeID;                       /* 模式ID */
    RCM_MODEM_ID_ENUM_UINT16                    enModemID;                      /* modem ID */
    RCM_MAS_DPDT_CONTROL_ENUM_UINT16            enMasterDpdt;                   /* 原主模dpdt状态 */
    RCM_TAS_INHERIT_STATE_ENUM_UINT16           enInheritCtrl;                  /* 主从模变更场景控制 */
    VOS_UINT16                                  usBlindTasPrefer;               /* 指示是否使用盲切 */
    RCM_TAS_MAS_CONTROL_ENUM_UINT16             enMasCtrl;                      /* 是否允许开启MAS(主控MAS授权) */
}RCM_PHY_START_TAS_REQ_STRU;

/*****************************************************************************
 结构名    : PHY_RCM_START_TAS_CNF_STRU
 协议表格  :
 ASN.1描述 :
 结构说明  : 通知RCM授权完成指示
*****************************************************************************/
typedef struct
{
    VOS_MSG_HEADER                                                              /*_H2ASN_Skip*/
    RCM_PHY_MSG_ID_ENUM_UINT16                  enMsgID;                        /* 原语类型 */ /*_H2ASN_Skip*/
    VOS_UINT16                                  usRsv;                          /* 保留字段 */
    VOS_UINT16                                  usOPID;                         /* 操作标识 */
    VOS_UINT16                                  usRsv1;                         /* 保留字段 */
    RCM_MODE_ID_ENUM_UINT16                     enModeID;                       /* 模式ID */
    RCM_MODEM_ID_ENUM_UINT16                    enModemID;                      /* modem ID */
    RCM_MAS_DPDT_CONTROL_ENUM_UINT16            enMasterDpdt;                   /* 原主模dpdt状态 */
    RCM_TAS_INHERIT_STATE_ENUM_UINT16           enInheritCtrl;                  /* 主从模变更场景控制 */
}PHY_RCM_START_TAS_CNF_STRU;

/*****************************************************************************
 结构名    : RCM_PHY_STOP_TAS_REQ_STRU
 协议表格  :
 ASN.1描述 :
 结构说明  : 通知PHY取消授权TAS
*****************************************************************************/
typedef struct
{
    VOS_MSG_HEADER                                                              /*_H2ASN_Skip*/
    RCM_PHY_MSG_ID_ENUM_UINT16                  enMsgID;                        /* 原语类型 */ /*_H2ASN_Skip*/
    VOS_UINT16                                  usRsv;                          /* 保留字段 */
    VOS_UINT16                                  usOPID;                         /* 操作标识 */
    VOS_UINT16                                  usRsv1;                         /* 保留字段 */
    RCM_MODE_ID_ENUM_UINT16                     enModeID;                       /* 模式ID */
    RCM_MODEM_ID_ENUM_UINT16                    enModemID;                      /* modem ID */
    RCM_STOP_TAS_TYPE_ENUM_UINT16               enStopTasType;                  /* 取消TAS授权方式 */
    VOS_UINT16                                  usRsv2;                         /* 保留字段 */
}RCM_PHY_STOP_TAS_REQ_STRU;

/*****************************************************************************
 结构名    : PHY_RCM_STOP_TAS_CNF_STRU
 协议表格  :
 ASN.1描述 :
 结构说明  : 通知RCM取消授权完成指示
*****************************************************************************/
typedef struct
{
    VOS_MSG_HEADER                                                              /*_H2ASN_Skip*/
    RCM_PHY_MSG_ID_ENUM_UINT16                  enMsgID;                        /* 原语类型 */ /*_H2ASN_Skip*/
    VOS_UINT16                                  usRsv;                          /* 保留字段 */
    VOS_UINT16                                  usOPID;                         /* 操作标识 */
    RCM_MODE_ID_ENUM_UINT16                     enModeID;                       /* 模式ID */
    RCM_MODEM_ID_ENUM_UINT16                    enModemID;                      /* modem ID */
    RCM_STOP_TAS_TYPE_ENUM_UINT16               enStopTasType;                  /* 取消TAS授权方式 */
}PHY_RCM_STOP_TAS_CNF_STRU;

/*****************************************************************************
 结构名    : RCM_PHY_SET_DPDT_REQ_STRU
 协议表格  :
 ASN.1描述 :
 结构说明  : 通知PHY设置DPDT控制字
*****************************************************************************/
typedef struct
{
    VOS_MSG_HEADER                                                              /*_H2ASN_Skip*/
    RCM_PHY_MSG_ID_ENUM_UINT16                  enMsgID;                        /* 原语类型 */ /*_H2ASN_Skip*/
    VOS_UINT16                                  usRsv;                          /* 保留字段 */
    VOS_UINT16                                  usOPID;                         /* 操作标识 */
    VOS_UINT16                                  usRsv1;                         /* 保留字段 */
    RCM_MODE_ID_ENUM_UINT16                     enModeID;                       /* 模式ID */
    RCM_MODEM_ID_ENUM_UINT16                    enModemID;                      /* modem ID */
    RCM_MAS_DPDT_CONTROL_ENUM_UINT16            enDpdtValue;                    /* DPDT控制状态 */
    VOS_UINT16                                  usRsv2;                         /* 保留字段 */
}RCM_PHY_SET_DPDT_REQ_STRU;

/*****************************************************************************
 结构名    : PHY_RCM_SET_DPDT_CNF_STRU
 协议表格  :
 ASN.1描述 :
 结构说明  : 通知RCM设置DPDT控制字完成指示
*****************************************************************************/
typedef struct
{
    VOS_MSG_HEADER                                                              /*_H2ASN_Skip*/
    RCM_PHY_MSG_ID_ENUM_UINT16                  enMsgID;                        /* 原语类型 */ /*_H2ASN_Skip*/
    VOS_UINT16                                  usRsv;                          /* 保留字段 */
    VOS_UINT16                                  usOPID;                         /* 操作标识 */
    VOS_UINT16                                  usRsv1;                         /* 保留字段 */
    RCM_MODE_ID_ENUM_UINT16                     enModeID;                       /* 模式ID */
    RCM_MODEM_ID_ENUM_UINT16                    enModemID;                      /* modem ID */
}PHY_RCM_SET_DPDT_CNF_STRU;

/*****************************************************************************
 结构名    : RCM_PHY_TX_BLANKING_IND_STRU
 协议表格  :
 ASN.1描述 :
 结构说明  : 通知被控modem TX_BLANKING起始时间和终止时间
*****************************************************************************/
typedef struct
{
    VOS_MSG_HEADER                                                              /*_H2ASN_Skip*/
    RCM_PHY_MSG_ID_ENUM_UINT16                  enMsgID;                        /* 原语类型 */ /*_H2ASN_Skip*/
    VOS_UINT16                                  usRsv;                          /* 保留字段 */
    VOS_UINT16                                  usOPID;                         /* 操作标识 */
    VOS_UINT16                                  usRsv1;                         /* 保留字段 */
    RCM_MODE_ID_ENUM_UINT16                     enModeID;                       /* 模式ID */
    RCM_MODEM_ID_ENUM_UINT16                    enModemID;                      /* modem ID */
    VOS_UINT32                                  ulStartSlice;                   /* 起始slice */
    VOS_UINT32                                  ulStopSlice;                    /* 终止slice */
    VOS_UINT16                                  usDpdtStatus;                   /* 切换后dpdt的状态 */
    RCM_TAS_TX_BLANKING_TYPE_ENUM_UINT16        enBlankingType;                 /* 切换类型: Probe or Switch */
}RCM_PHY_TX_BLANKING_IND_STRU;

/*****************************************************************************
 结构名    : PHY_RCM_TX_BLANKING_IND_STRU
 协议表格  :
 ASN.1描述 :
 结构说明  : 通知RCM主控modem TX_BLANKING起始时间和终止时间
*****************************************************************************/
typedef struct
{
    VOS_MSG_HEADER                                                              /*_H2ASN_Skip*/
    RCM_PHY_MSG_ID_ENUM_UINT16                  enMsgID;                        /* 原语类型 */ /*_H2ASN_Skip*/
    VOS_UINT16                                  usRsv;                          /* 保留字段 */
    VOS_UINT16                                  usOPID;                         /* 操作标识 */
    VOS_UINT16                                  usRsv1;                         /* 保留字段 */
    RCM_MODE_ID_ENUM_UINT16                     enModeID;                       /* 模式ID */
    RCM_MODEM_ID_ENUM_UINT16                    enModemID;                      /* modem ID */
    VOS_UINT32                                  ulStartSlice;                   /* 起始slice */
    VOS_UINT32                                  ulStopSlice;                    /* 终止slice */
    VOS_UINT16                                  usDpdtStatus;                   /* 切换后dpdt的状态 */
    RCM_TAS_TX_BLANKING_TYPE_ENUM_UINT16        enBlankingType;                 /* 切换类型: Probe or Switch */
    VOS_UINT16                                  ulDpdtSwitchReason;             /* 各PHY用来上报自己私有的切换原因(可维可测) */
    VOS_UINT16                                  usRsv2;                         /* 保留字段 */
}PHY_RCM_TX_BLANKING_IND_STRU;

/*****************************************************************************
 结构名    : PHY_RCM_RATMODE_IND_STRU
 协议表格  :
 ASN.1描述 :
 结构说明  : PHY通知RCM当前modem的主从模模式
*****************************************************************************/
typedef struct
{
    VOS_MSG_HEADER                                                              /*_H2ASN_Skip*/
    RCM_PHY_MSG_ID_ENUM_UINT16                  enMsgID;                        /* 原语类型 */ /*_H2ASN_Skip*/
    VOS_UINT16                                  usRsv;                          /* 保留字段 */
    VOS_UINT16                                  usOPID;                         /* 操作标识 */
    VOS_UINT16                                  usRsv1;                         /* 保留字段 */
    RCM_MODE_ID_ENUM_UINT16                     enModeID;                       /* 模式ID */
    RCM_MODEM_ID_ENUM_UINT16                    enModemID;                      /* modem ID */
    VOS_RATMODE_ENUM_UINT32                     enMasterMode;                   /* 主模模式 */
    VOS_RATMODE_ENUM_UINT32                     enSlaveMode;                    /* 从模模式 */
    RCM_MAS_DPDT_CONTROL_ENUM_UINT16            enMasterDpdt;                   /* 原主模dpdt状态 */
    RCM_TAS_AUTHORIZE_PHY_STATE_ENUM_UINT16     enPhyAuthorizeFlg;              /* 原主模授权状态 */
}PHY_RCM_RATMODE_IND_STRU;

/*****************************************************************************
 结构名    : RCM_PHY_MSG_HEADER_STRU
 协议表格  :
 ASN.1描述 :
 结构说明  : RCM与物理层交互消息结构头定义，必须确保rcm发给phy的消息结构如下定义，
             赋值时应将usRsv赋为0，因为msp邮箱的存储的消息包第一个四字节为消息id。
*****************************************************************************/
typedef struct
{
    VOS_MSG_HEADER                                                              /*_H2ASN_Skip*/
    RCM_PHY_MSG_ID_ENUM_UINT16                  enMsgID;                        /* 原语类型 */ /*_H2ASN_Skip*/
    VOS_UINT16                                  usRsv;                          /* 保留字段 */
    VOS_UINT16                                  usOPID;                         /* 操作标识 */
    VOS_UINT16                                  usRsv1;                         /* 保留字段 */
    RCM_MODE_ID_ENUM_UINT16                     enModeID;                       /* 模式ID */
    RCM_MODEM_ID_ENUM_UINT16                    enModemID;                      /* modem ID */
}RCM_PHY_MSG_HEADER_STRU;

/*****************************************************************************
 结构名    : PHY_RCM_ACCESS_STATE_IND_STRU
 协议表格  :
 ASN.1描述 :
 结构说明  : 通知RCM PHY Access 状态
*****************************************************************************/
typedef struct
{
    VOS_MSG_HEADER                                                              /*_H2ASN_Skip*/
    RCM_PHY_MSG_ID_ENUM_UINT16                  enMsgID;                        /* 原语类型 */ /*_H2ASN_Skip*/
    VOS_UINT16                                  usRsv;                          /* 保留字段 */
    VOS_UINT16                                  usOPID;                         /* 操作标识 */
    VOS_UINT16                                  usRsv1;                         /* 保留字段 */
    RCM_MODE_ID_ENUM_UINT16                     enModeID;                       /* 模式ID */
    RCM_MODEM_ID_ENUM_UINT16                    enModemID;                      /* modem ID */
    RCM_ACCESS_STATE_ENUM_UINT16                enAccessState;                  /* Access State */
    VOS_UINT16                                  usRsv2;
}PHY_RCM_ACCESS_STATE_IND_STRU;

/*****************************************************************************
 结构名    : PHY_RCM_CPICH_STATE_IND_STRU
 协议表格  :
 ASN.1描述 :
 结构说明  : 通知RCM PHY CPICH 状态
*****************************************************************************/
typedef struct
{
    VOS_MSG_HEADER                                                              /*_H2ASN_Skip*/
    RCM_PHY_MSG_ID_ENUM_UINT16                  enMsgID;                        /* 原语类型 */ /*_H2ASN_Skip*/
    VOS_UINT16                                  usRsv;                          /* 保留字段 */
    VOS_UINT16                                  usOPID;                         /* 操作标识 */
    VOS_UINT16                                  usRsv1;                         /* 保留字段 */
    RCM_MODE_ID_ENUM_UINT16                     enModeID;                       /* 模式ID */
    RCM_MODEM_ID_ENUM_UINT16                    enModemID;                      /* modem ID */
    RCM_CPICH_STATE_ENUM_UINT16                 enCPICHState;                   /* Access State */
    VOS_UINT16                                  usRsv2;
}PHY_RCM_CPICH_STATE_IND_STRU;


/*****************************************************************************
 结构名    : PHY_RCM_SEARCHING_STATE_IND_STRU
 协议表格  :
 ASN.1描述 :
 结构说明  : 通知RCM PHY Searching 状态
*****************************************************************************/
typedef struct
{
    VOS_MSG_HEADER                                                              /*_H2ASN_Skip*/
    RCM_PHY_MSG_ID_ENUM_UINT16                  enMsgID;                        /* 原语类型 */ /*_H2ASN_Skip*/
    VOS_UINT16                                  usRsv;                          /* 保留字段 */
    VOS_UINT16                                  usOPID;                         /* 操作标识 */
    VOS_UINT16                                  usRsv1;                         /* 保留字段 */
    RCM_MODE_ID_ENUM_UINT16                     enModeID;                       /* 模式ID */
    RCM_MODEM_ID_ENUM_UINT16                    enModemID;                      /* modem ID */
    RCM_SEARCHING_STATE_ENUM_UINT16             enSearchingState;               /* Searching State */
    VOS_UINT16                                  usRsv2;
}PHY_RCM_SEARCHING_STATE_IND_STRU;

/*****************************************************************************
 结构名    : PHY_RCM_SIGNAL_STATE_IND_STRU
 协议表格  :
 ASN.1描述 :
 结构说明  : 通知RCM PHY Signal 状态
*****************************************************************************/
typedef struct
{
    VOS_MSG_HEADER                                                              /*_H2ASN_Skip*/
    RCM_PHY_MSG_ID_ENUM_UINT16                  enMsgID;                        /* 原语类型 */ /*_H2ASN_Skip*/
    VOS_UINT16                                  usRsv;                          /* 保留字段 */
    VOS_UINT16                                  usOPID;                         /* 操作标识 */
    VOS_UINT16                                  usRsv1;                         /* 保留字段 */
    RCM_MODE_ID_ENUM_UINT16                     enModeID;                       /* 模式ID */
    RCM_MODEM_ID_ENUM_UINT16                    enModemID;                      /* modem ID */
    RCM_SIGNAL_STATE_ENUM_UINT16                enSignalState;                  /* Signal State */
    VOS_UINT16                                  usRsv2;
}PHY_RCM_SIGNAL_STATE_IND_STRU;

/*****************************************************************************
 结构名    : PHY_RCM_IDLE_HAPPY_IND_STRU
 协议表格  :
 ASN.1描述 :
 结构说明  : 通知RCM PHY Signal 状态
*****************************************************************************/
typedef struct
{
    VOS_MSG_HEADER                                                              /*_H2ASN_Skip*/
    RCM_PHY_MSG_ID_ENUM_UINT16                  enMsgID;                        /* 原语类型 */ /*_H2ASN_Skip*/
    VOS_UINT16                                  usRsv;                          /* 保留字段 */
    VOS_UINT16                                  usOPID;                         /* 操作标识 */
    VOS_UINT16                                  usRsv1;                         /* 保留字段 */
    RCM_MODE_ID_ENUM_UINT16                     enModeID;                       /* 模式ID */
    RCM_MODEM_ID_ENUM_UINT16                    enModemID;                      /* modem ID */
    RCM_IDLE_HAPPY_ENUM_UINT16                  enIdleHappy;                    /* Idle Happy State */
    VOS_UINT16                                  usRsv2;
}PHY_RCM_IDLE_HAPPY_IND_STRU;

/*****************************************************************************
 结构名    : RCM_PHY_VOICE_CALL_STATE_IND_STRU
 协议表格  :
 ASN.1描述 :
 结构说明  : RCM转发通知PHY BACKGROUND Call 状态
*****************************************************************************/
typedef struct
{
    VOS_MSG_HEADER                                                              /*_H2ASN_Skip*/
    RCM_PHY_MSG_ID_ENUM_UINT16                  enMsgID;                        /* 原语类型 */ /*_H2ASN_Skip*/
    VOS_UINT16                                  usRsv;                          /* 保留字段 */
    VOS_UINT16                                  usOPID;                         /* 操作标识 */
    VOS_UINT16                                  usRsv1;                         /* 保留字段 */
    RCM_MODE_ID_ENUM_UINT16                     enModeID;                       /* 模式ID */
    RCM_MODEM_ID_ENUM_UINT16                    enModemID;                      /* modem ID */
    RCM_PHY_CALL_STATE_ENUM_UINT16              enVoiceCallState;               /* Voice Call State */
    VOS_UINT16                                  usRsv2;
}RCM_PHY_VOICE_CALL_STATE_IND_STRU;


/*****************************************************************************
 结构名    : PHY_RCM_PAGING_TASK_FAIL_STRU
 协议表格  :
 ASN.1描述 :
 结构说明  : 用于统计PAGING失败的原因
*****************************************************************************/
typedef struct
{
    VOS_MSG_HEADER                                                              /*_H2ASN_Skip*/
    RCM_PHY_MSG_ID_ENUM_UINT16                  enMsgID;                        /* 原语类型 */ /*_H2ASN_Skip*/
    VOS_UINT16                                  usRsv;                          /* 保留字段 */
    VOS_UINT16                                  usOPID;                         /* 操作标识 */
    VOS_UINT16                                  usRsv1;                         /* 保留字段 */
    RCM_MODE_ID_ENUM_UINT16                     enModeID;                       /* 模式ID */
    RCM_MODEM_ID_ENUM_UINT16                    enModemID;                      /* modem ID */
    RCM_PAGING_TASK_FAIL_REASON_ENUM_UINT16     enFailReason;
    RCM_PHY_TASK_ID_ENUM_UINT16                 usTaskID;                       /* taskid 为0的时候表示当前不知道taskid是多少，需要分析LOG */
}PHY_RCM_PAGING_TASK_FAIL_STRU;

/*****************************************************************************
 结构名    : PHY_RCM_VOICE_CALL_STATE_CNF_STRU
 协议表格  :
 ASN.1描述 :
 结构说明  : RCM转发通知PHY BACKGROUND Call 状态
*****************************************************************************/
typedef struct
{
    VOS_MSG_HEADER                                                              /*_H2ASN_Skip*/
    RCM_PHY_MSG_ID_ENUM_UINT16                  enMsgID;                        /* 原语类型 */ /*_H2ASN_Skip*/
    VOS_UINT16                                  usRsv;                          /* 保留字段 */
    VOS_UINT16                                  usOPID;                         /* 操作标识 */
    VOS_UINT16                                  usRsv1;                         /* 保留字段 */
    RCM_MODE_ID_ENUM_UINT16                     enModeID;                       /* 模式ID */
    RCM_MODEM_ID_ENUM_UINT16                    enModemID;                      /* modem ID */
    RCM_PHY_CALL_STATE_ENUM_UINT16              enVoiceCallState;               /* Voice Call State */
    VOS_UINT16                                  usRsv2;
}PHY_RCM_VOICE_CALL_STATE_CNF_STRU;


/*****************************************************************************
 结构名    : PHY_RCM_SEARCHING_STATE_REQ_STRU
 协议表格  :
 ASN.1描述 :
 结构说明  : 通知RCM PHY Searching 状态
*****************************************************************************/
typedef struct
{
    VOS_MSG_HEADER                                                              /*_H2ASN_Skip*/
    RCM_PHY_MSG_ID_ENUM_UINT16                  enMsgID;                        /* 原语类型 */ /*_H2ASN_Skip*/
    VOS_UINT16                                  usRsv;                          /* 保留字段 */
    VOS_UINT16                                  usOPID;                         /* 操作标识 */
    VOS_UINT16                                  usRsv1;                         /* 保留字段 */
    RCM_MODE_ID_ENUM_UINT16                     enModeID;                       /* 模式ID */
    RCM_MODEM_ID_ENUM_UINT16                    enModemID;                      /* modem ID */
    RCM_SEARCHING_STATE_ENUM_UINT16             enSearchingState;               /* Searching State */
    VOS_UINT16                                  usRsv2;
}PHY_RCM_SEARCHING_STATE_REQ_STRU;

/*****************************************************************************
 结构名    : RCM_PHY_SEARCHING_STATE_CNF_STRU
 协议表格  :
 ASN.1描述 :
 结构说明  : 通知PHY可以执行Searching并用何种方式搜索
*****************************************************************************/
typedef struct
{
    VOS_MSG_HEADER                                                              /*_H2ASN_Skip*/
    RCM_PHY_MSG_ID_ENUM_UINT16                  enMsgID;                        /* 原语类型 */ /*_H2ASN_Skip*/
    VOS_UINT16                                  usRsv;                          /* 保留字段 */
    VOS_UINT16                                  usOPID;                         /* 操作标识 */
    VOS_UINT16                                  usRsv1;                         /* 保留字段 */
    RCM_MODE_ID_ENUM_UINT16                     enModeID;                       /* 模式ID */
    RCM_MODEM_ID_ENUM_UINT16                    enModemID;                      /* modem ID */
    RCM_TAS_SEARCH_METHOD_ENUM_UINT16           enSearchMethod;                 /* PHY Search Method */
    VOS_UINT16                                  usRsv2;
}RCM_PHY_SEARCHING_STATE_CNF_STRU;

/*****************************************************************************
 结构名    : RCM_PHY_AGENTC_SET_DPDT_REQ_STRU
 协议表格  :
 ASN.1描述 :
 结构说明  : 通知代理PHY切换DPDT任务控制信息
*****************************************************************************/
typedef struct
{
    VOS_MSG_HEADER                                                              /*_H2ASN_Skip*/
    RCM_PHY_MSG_ID_ENUM_UINT16                  enMsgID;                        /* 原语类型 */ /*_H2ASN_Skip*/
    VOS_UINT16                                  usRsv;                          /* 保留字段 */
    VOS_UINT16                                  usOPID;                         /* 操作标识 */
    VOS_UINT16                                  usRsv1;                         /* 保留字段 */
    RCM_MODE_ID_ENUM_UINT16                     enModeID;                       /* 模式ID */
    RCM_MODEM_ID_ENUM_UINT16                    enModemID;                      /* modem ID */
    RCM_AGENTC_DPDT_CTRL_ENUM_UINT16            enTaskCtrl;                     /* DPDT切换任务控制 */
    RCM_MAS_DPDT_CONTROL_ENUM_UINT16            enDpdtValue;                    /* DPDT控制状态 */
}RCM_PHY_AGENTC_SET_DPDT_REQ_STRU;

/*****************************************************************************
 结构名    : PHY_RCM_AGENTC_SET_DPDT_CNF_STRU
 协议表格  :
 ASN.1描述 :
 结构说明  : 代理PHY对切换DPDT任务控制请求信息的回复
*****************************************************************************/
typedef struct
{
    VOS_MSG_HEADER                                                              /*_H2ASN_Skip*/
    RCM_PHY_MSG_ID_ENUM_UINT16                  enMsgID;                        /* 原语类型 */ /*_H2ASN_Skip*/
    VOS_UINT16                                  usRsv;                          /* 保留字段 */
    VOS_UINT16                                  usOPID;                         /* 操作标识 */
    VOS_UINT16                                  usRsv1;                         /* 保留字段 */
    RCM_MODE_ID_ENUM_UINT16                     enModeID;                       /* 模式ID */
    RCM_MODEM_ID_ENUM_UINT16                    enModemID;                      /* modem ID */
    RCM_AGENTC_DPDT_CTRL_ENUM_UINT16            enTaskCtrl;                     /* DPDT切换任务控制 */
    RCM_MAS_DPDT_CONTROL_ENUM_UINT16            enDpdtValue;                    /* DPDT控制状态 */
}PHY_RCM_AGENTC_SET_DPDT_CNF_STRU;


/*****************************************************************************
 结构名    : PHY_RCM_CDMA_WORK_STATE_IND_STRU
 协议表格  :
 ASN.1描述 :
 结构说明  : CUse状态上报结构体
*****************************************************************************/
typedef struct
{
    RCM_PHY_MSG_HEADER_STRU                     stMsgHeader;
    RCM_PHY_CDMA_STATE_ENUM_UINT16              enCUseStatus;                   /* CDMA上下电状态，0-下电，1-上电 */
    VOS_UINT16                                  uhwCLineCtrlSel;                /* CUse的线控选择，0-用原有的18013nv项，1-用新增的18021nv项 */
}PHY_RCM_CDMA_WORK_STATE_IND_STRU;

/*****************************************************************************
 结构名    : RCM_PHY_ANT_SHARE_REQ_STRU
 协议表格  :
 ASN.1描述 :
 结构说明  : 共天线状态请求结构体
*****************************************************************************/
typedef struct
{
    RCM_PHY_MSG_HEADER_STRU                     stMsgHeader;
    RCM_PHY_ANT_SHARE_STATUS_ENUM_UINT16        enAntShareState;                /* 共天线状态，0:L主集和G1模，1:L主集和C模 */
    VOS_UINT16                                  uhwVoLteState;                  /* 网络支持VoLTE状态，0:不支持，1:支持 */
}RCM_PHY_ANT_SHARE_REQ_STRU;

/*****************************************************************************
 结构名    : PHY_RCM_ANT_SHARE_CNF_STRU
 协议表格  :
 ASN.1描述 :
 结构说明  : 共天线状态请求回复结构体
*****************************************************************************/
typedef struct
{
    RCM_PHY_MSG_HEADER_STRU                     stMsgHeader;
    RCM_PHY_ANT_SHARE_STATUS_ENUM_UINT16        enAntShareState;                /* 共天线状态，0:L主集和G1模，1:L主集和C模 */
    VOS_UINT16                                  uhwVoLteState;                  /* 网络支持VoLTE状态，0:不支持，1:支持 */
}PHY_RCM_ANT_SHARE_CNF_STRU;

/*****************************************************************************
 结构名    : RCM_PHY_ANT_SHARE_TX_BLANKING_IND_STRU
 协议表格  :
 ASN.1描述 :
 结构说明  : S3开关状态上报结构体
*****************************************************************************/
typedef struct
{
    RCM_PHY_MSG_HEADER_STRU                     stMsgHeader;
    RCM_PHY_ANT_SHARE_STATUS_ENUM_UINT16        enAntShareState;                /* 共天线状态，0:L主集和G1模，1:L主集和C模 */
    VOS_UINT16                                  uhwTxBlanking;                  /* 0--NoTxBlanking，即S3开关打开，1--TxBlanking，即S3开关接地 */
}RCM_PHY_ANT_SHARE_TX_BLANKING_IND_STRU;
/*******************************************************************************
 结构名    : RCM_MODE_ID_PARA_STRU
 协议表格  :
 ASN.1描述 :
 结构说明  : 各个模式的信息
*******************************************************************************/
typedef struct
{
    RCM_MODE_ID_ENUM_UINT16                     enModeID;
    RCM_MODEM_ID_ENUM_UINT16                    enModemID;                      /* Modem Id */
    RCM_RF_ID_ENUM_UINT16                       enRFId;                         /* Resource Id */
    RCM_DSDS_FLG_ENUM_UINT16                    enDsdsFlg;
} RCM_MODE_ID_PARA_STRU;

/*****************************************************************************
 结构名    : RCM_PHY_GET_MODE_INFO_STRU
 协议表格  :
 ASN.1描述 :
 结构说明  : PHY向RCM查询各个模式的配置信息返回结果
*****************************************************************************/
typedef struct
{
    VOS_UINT16                                  usModeIdNum;                    /* 模式总数 */
    VOS_UINT16                                  usRsv2;                         /* 保留字段 */
    RCM_MODE_ID_PARA_STRU                       astModeIdPara[RCM_MODE_ID_BUTT];/* 模式信息 */
}RCM_PHY_GET_MODE_INFO_STRU;


/*****************************************************************************
 结构名    : RCM_PHY_NOTICE_DSDS_INIT_IND_STRU
 协议表格  :
 ASN.1描述 :
 结构说明  : RCM通知GU物理层，RCM已经完成初始化
*****************************************************************************/
typedef struct
{
    VOS_MSG_HEADER                                                              /*_H2ASN_Skip*/
    RCM_PHY_MSG_ID_ENUM_UINT16                  enMsgID;                        /* 原语类型 */ /*_H2ASN_Skip*/
    VOS_UINT16                                  usDsdsInitFlag;                 /* 1表示已经完成初始化 */
}RCM_PHY_NOTICE_DSDS_INIT_IND_STRU;

/*****************************************************************************
 结构名    : PHY_RCM_INTERFE_CHECK_REQ_STRU
 协议表格  :
 ASN.1描述 :
 结构说明  : GPHY1通过RCM给TLPHY发送消息，通知其GPHY已经进出连接态的起启位置。
*****************************************************************************/
typedef struct
{
    VOS_MSG_HEADER                                                              /*_H2ASN_Skip*/
    RCM_PHY_MSG_ID_ENUM_UINT16                  enMsgID;                        /* 原语类型 */ /*_H2ASN_Skip*/
    VOS_UINT16                                  usRsv;                          /* 保留字段 */
    VOS_UINT16                                  usOPID;                         /* 操作标识 */
    VOS_UINT16                                  usRsv1;                         /* 保留字段 */
    RCM_MODE_ID_ENUM_UINT16                     enModeID;                       /* 模式ID */
    RCM_MODEM_ID_ENUM_UINT16                    enModemID;                      /* modem ID */
    VOS_UINT16                                  usRsv2;                         /* 操作标识 */
    RCM_INTERFERENCE_ENUM_UINT16                enInterfercnceCheckFlag;        /* 起停标志 */
}PHY_RCM_INTERFE_CHECK_REQ_STRU;

/*****************************************************************************
 结构名    : RCM_PHY_GET_AFC_INFO_REQ_STRU
 协议表格  :
 ASN.1描述 :
 结构说明  : 通知PHY查询AFC信息
*****************************************************************************/
typedef struct
{
    RCM_PHY_MSG_HEADER_STRU             stMsgHeader;
    VOS_UINT32                          usRsv1;                         /* 保留字段 */
}RCM_PHY_GET_AFC_INFO_REQ_STRU;


/*****************************************************************************
 结构名    : PHY_RCM_GET_AFC_INFO_CNF_STRU
 协议表格  :
 ASN.1描述 :
 结构说明  : 返回PHY查询到的AFC信息
*****************************************************************************/
typedef struct
{
    RCM_PHY_MSG_HEADER_STRU             stMsgHeader;
    RCM_PHY_AFC_CLK_STATUS_ENUM_UINT16  enStatus;
    VOS_INT32                           lDeviation;                             /* 频偏信息 */

    /* 温度范围 */
    VOS_INT16                           sCoeffStartTemp;
    VOS_INT16                           sCoeffEndTemp;

    /* 多项式系数 */
    VOS_UINT32                          aulCoeffMantissa[RCM_PHY_XO_COEF_NUM];  /* a0,a1,a2,a3的尾数 */
    VOS_UINT16                          ausCoeffExponent[RCM_PHY_XO_COEF_NUM];  /* a0,a1,a2,a3的指数 */
}PHY_RCM_GET_AFC_INFO_CNF_STRU;


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
#ifndef LPS_RTT
extern VOS_VOID RCM_DRV_SetWTimeMode( RCM_WMODE_TYPE_ENUM_UINT16 enWModeType );
extern VOS_UINT32 RCM_DRV_32KSysTimeInquire( VOS_VOID );
extern VOS_UINT32 RCM_DRV_TimingInquire( RCM_CMODE_TYPE_ENUM_UINT16 enCModemType,
                                                 RCM_TIMING_STRU* pstTiming );
extern VOS_INT32 RCM_SCHDL_CalcDistance( VOS_UINT32 uwTimeX,
                                                 VOS_UINT32 uwTimeY );
extern VOS_INT32 RCM_SCHDL_GetProtectState(RCM_MODEM_ID_ENUM_UINT16 enModemID);
extern RCM_PHY_GET_MODE_INFO_STRU * RCM_SCHDL_GetModeInfoAddr( VOS_VOID);
#endif

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

#endif /* end of RcmPhyInterface.h */



