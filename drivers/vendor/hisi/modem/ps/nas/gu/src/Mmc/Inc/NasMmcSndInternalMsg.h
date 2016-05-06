/******************************************************************************

                  版权所有 (C), 2001-2011, 华为技术有限公司

 ******************************************************************************
  文 件 名   : NasMmcSndInternalmsg.h
  版 本 号   : 初稿
  作    者   : w00176964
  生成日期   : 2011年5月9日
  最近修改   :
  功能描述   : 定义内部消息发送处理头文件
  函数列表   :
  修改历史   :
  1.日    期   : 2011年5月9日
    作    者   : w00176964
    修改内容   : 创建文件

******************************************************************************/
#ifndef _NAS_MMC_SND_INTERNAL_MSG_H_
#define _NAS_MMC_SND_INTERNAL_MSG_H_

/*****************************************************************************
  1 其他头文件包含
*****************************************************************************/
#include  "vos.h"
#include  "NasMmcCtx.h"
#include  "NasCommDef.h"

#ifdef __cplusplus
#if __cplusplus
extern "C" {
#endif
#endif


#pragma pack(4)

/*****************************************************************************
  2 宏定义
*****************************************************************************/

/*****************************************************************************
  3 枚举定义
*****************************************************************************/

/*****************************************************************************
 枚举名    : NAS_MMLAYER_INTERNAL_MSG_ID_ENUM
 结构说明  : 内部消息ID
 1.日    期   : 2011年5月9日
   作    者   : zhoujun 40661
   修改内容   : MMC内部消息ID枚举
 2.日    期   : 2011年7月19日
   作    者   : sunxibo 46746
   修改内容   : V7R1 phase II,autoplmnsrch状态机调整为PlmnSelection状态机
*****************************************************************************/
enum NAS_MMC_INTERNAL_MSG_ID_ENUM
{
    /* MMC收到的内部消息ID,MMC内部收到的消息ID从0x000到0x199 */
    MMCMMC_ABORT_FSM_REQ                       = 0,
    MMCMMC_INTER_PLMN_SEARCH_REQ               = 1,                                  /* 内部搜网请求 ,重新初始化，发出搜网请求 */
    MMCMMC_INTER_ANYCELL_SEARCH_REQ            = 2,                                  /* 内部搜网请求 ,重新初始化，发出搜网请求 */
    MMCMMC_INTER_PLMN_LIST_REQ                 = 3,

    MMCMMC_SWITCH_ON_RSLT_CNF                  = 4,
    MMCMMC_POWER_OFF_RSLT_CNF                  = 5,
    MMCMMC_SUSPEND_RSLT_CNF                    = 6,
    MMCMMC_PLMN_LIST_RSLT_CNF                  = 7,

    MMCMMC_PLMN_SELECTION_RSLT_CNF             = 8,

    MMCMMC_ANYCELL_SEARCH_RSLT_CNF             = 9,

    MMCMMC_SYSCFG_RSLT_CNF                     = 10,

    MMCMMC_BG_PLMN_SEARCH_RSLT_CNF             = 11,

    MMCMMC_INTER_NVIM_OPLMN_REFRESH_IND        = 12,

    MMCMMC_INTER_SKIP_SEARCH_W_IND             = 13,

    MMCMMC_INTER_SKIP_SEARCH_TDS_IND           = 14,
    MMCMMC_INTER_ABORT_UTRAN_CTRL_PLMN_SEARCH_REQ = 15,
    MMCMMC_INTER_ABORT_UTRAN_CTRL_PLMN_SEARCH_CNF = 16,

    MMCMMC_GET_GEO_RSLT_CNF                    = 17,
    MMCMMC_INTER_DPLMN_SET_REQ                 = 18,

    MMCMMC_INTER_UTRAN_CTRL_PLMN_SELECTION_ABORT_FINISH_IND = 19,

    MMCMMC_INTERNAL_MSG_ID_BUTT
};
typedef VOS_UINT32 NAS_MMC_INTERNAL_MSG_ID_ENUM_U32;


/*****************************************************************************
枚举名    : NAS_MMC_ANYCELL_SEARCH_RESULT_ENUM
结构说明  : Anycell 搜网状态机产生的结果
1.日    期   : 2011年7月11日
  作    者   : l00130025
  修改内容   : 新增
2.日    期   : 2014年4月24日
  作    者   : w00242748
  修改内容   : DTS2014042405819:无卡状态下，紧急呼被拒#5，后发起ANYCELL搜，导致退状态机
                后下发RRMM_UE_OOC_STATUS_NOTIFY_IND，导致网络不断下发CM SERVICE REJ

*****************************************************************************/
enum NAS_MMC_ANYCELL_SEARCH_RESULT_ENUM
{
    NAS_MMC_ANYCELL_SEARCH_SUCC         = 0,
    NAS_MMC_ANYCELL_SEARCH_FAIL         = 1,
    NAS_MMC_ANYCELL_SEARCH_ABORTED      = 2,
    NAS_MMC_ANYCELL_SEARCH_REJECT       = 3,
    NAS_MMC_PLMN_SEARCH_BUTT
};
typedef VOS_UINT32 NAS_MMC_ANYCELL_SEARCH_RESULT_ENUM_UINT32;

/*****************************************************************************
枚举名    : NAS_MMC_PLMN_SELECTION_RESULT_ENUM
结构说明  : plmnSelection状态机产生的结果
1.日    期   : 2011年7月11日
  作    者   : l00130025
  修改内容   : 新增
2.日    期   : 2014年1月27日
  作    者   : s00246516
  修改内容   : L-C互操作项目:增加异系统到HRPD的处理
*****************************************************************************/
enum NAS_MMC_PLMN_SELECTION_RESULT_ENUM
{
    NAS_MMC_PLMN_SELECTION_SUCC            = 0,                                    /*正常或限制驻留*/
    NAS_MMC_PLMN_SELECTION_FAIL            = 1,                                    /*无网络或注册导致卡无效*/
    NAS_MMC_PLMN_SELECTION_ABORTED         = 2,                                    /* PlmnSelection状态机被打断*/
    /* Added by s00246516 for L-C互操作项目, 2014-01-27, Begin */
    NAS_MMC_PLMN_SELECTION_INTER_SYS_HRPD  = 3,                                 /* 搜索过程中重选到HRPD */
    /* Added by s00246516 for L-C互操作项目, 2014-01-27, End */
    NAS_MMC_PLMN_SELECTION_BUTT
};
typedef VOS_UINT32 NAS_MMC_PLMN_SELECTION_RESULT_ENUM_UINT32;


/*****************************************************************************
 枚举名    : NAS_MMC_SUSPEND_RSLT_ENUM_UINT32
 结构说明  : 重选/HO/CCO状态机产生的结果
 1.日    期   : 2011年7月18日
   作    者   : W00176964
   修改内容   : 新增
*****************************************************************************/
enum NAS_MMC_SUSPEND_RSLT_ENUM
{
    NAS_MMC_SUSPEND_SUCCESS            = 0,
    NAS_MMC_SUSPEND_FAIL               = 1,
    NAS_MMC_SUSPEND_ABORTED            = 2,
    NAS_MMC_SUSPEND_BUTT
};
typedef VOS_UINT32 NAS_MMC_SUSPEND_RSLT_ENUM_UINT32;


/*****************************************************************************
 枚举名    : NAS_MMC_GET_GEO_RSLT_ENUM_UINT32
 结构说明  : GET GEO状态机产生的结果
 1.日    期   : 2015年05月08日
   作    者   : sunjitan 00193151
   修改内容   : 新增
*****************************************************************************/
enum NAS_MMC_GET_GEO_RSLT_ENUM
{
    NAS_MMC_GET_GEO_SUCCESS             = 0,
    NAS_MMC_GET_GEO_FAIL                = 1,
    NAS_MMC_GET_GEO_ABORTED             = 2,
    NAS_MMC_GET_GEO_ABNORMAL            = 3,                /* 状态机被异常终止 */
    NAS_MMC_GET_GEO_NO_RF               = 4,                /* GET GEO返回结果为NO_RF */
    NAS_MMC_GET_GEO_BUTT
};
typedef VOS_UINT32 NAS_MMC_GET_GEO_RSLT_ENUM_UINT32;

/*****************************************************************************
 枚举名    : NAS_MMC_SUSPEND_FAIL_CAUSE_ENUM
 结构说明  : InterSys状态机失败原因, 当前InterSys状态机退出结果为NAS_MMC_SUSPEND_FAIL时此项才生效
 1.日    期   : 2011年9月29日
   作    者   : W00176964
   修改内容   : 新增
*****************************************************************************/
enum NAS_MMC_SUSPEND_FAIL_CAUSE_ENUM
{
    NAS_MMC_SUSPEND_FAIL_CAUSE_AREA_LOST        = 0,
    NAS_MMC_SUSPEND_FAIL_CAUSE_BUTT
};
typedef VOS_UINT8 NAS_MMC_SUSPEND_FAIL_CAUSE_ENUM_UINT8;

/*****************************************************************************
枚举名    : NAS_MMC_PLMN_LIST_RESULT_ENUM
结构说明  : LIST搜网状态机产生的结果
1.日    期   : 2011年9月05日
  作    者   : w00176964
  修改内容   : 新增
2.日    期   : 2014年5月15日
  作    者   : w00167002
  修改内容   : DTS2014051501018:DSDS副MODEM发起电话，主MODEM搜网失败启动AVAILABLE
               定时器，用户发起列表搜，在列表搜过程中，周期搜网定时器超时，列表搜
               结束后，MMC没有启动周期搜网定时器。
               修改为:在列表搜NO RF后，都启动AVAILABLE定时器，在AVAILABLE定时器
               超时后，增加如果当前被拒#12则不搜网，当前ACCESS BAR则不搜网。
*****************************************************************************/
enum NAS_MMC_PLMN_LIST_RESULT_ENUM
{
    NAS_MMC_PLMN_LIST_SUCC         = 0,
    NAS_MMC_PLMN_LIST_FAIL         = 1,
    NAS_MMC_PLMN_LIST_ABORTED      = 2,

    NAS_MMC_PLMN_LIST_NO_RF_FAIL    = 3,

    NAS_MMC_PLMN_LIST_BUTT
};
typedef VOS_UINT32 NAS_MMC_PLMN_LIST_RESULT_ENUM_UINT32;

/*****************************************************************************
枚举名    : NAS_MMC_BG_PLMN_SEARCH_RSLT_ENUM
结构说明  : BgPlmnSearch状态机退出结果
1.日    期   : 2011年9月20日
  作    者   : s46746
  修改内容   : 新增
2.日    期   : 2014年1月27日
  作    者   : s00246516
  修改内容   : L-C互操作项目:增加异系统到HRPD的处理
*****************************************************************************/
enum NAS_MMC_BG_PLMN_SEARCH_RSLT_ENUM
{
    NAS_MMC_BG_PLMN_SEARCH_SUCC         = 0,                                    /* BG搜索成功完成 */
    NAS_MMC_BG_PLMN_SEARCH_FAIL         = 1,                                    /* BG搜索未完成 */
    NAS_MMC_BG_PLMN_SEARCH_ABORTED      = 2,                                    /* BG搜索被Abort */

    /* Added by s00246516 for L-C互操作项目, 2014-01-27, Begin */
    NAS_MMC_BG_PLMN_SEARCH_INTER_SYS_HRPD  = 3,                                 /* BG搜索过程中重选到HRPD */
    /* Added by s00246516 for L-C互操作项目, 2014-01-27, End */

    NAS_MMC_BG_PLMN_SEARCH_BUTT
};
typedef VOS_UINT32 NAS_MMC_BG_PLMN_SEARCH_RSLT_ENUM_UINT32;


/*****************************************************************************
枚举名    : NAS_MMC_HIGH_PRIO_PLMN_SEARCH_RSLT_ENUM
结构说明  : HighPrioPlmnSearch状态机退出结果
1.日    期   : 2011年9月20日
  作    者   : w00167002
  修改内容   : 新增
*****************************************************************************/
enum NAS_MMC_HIGH_PRIO_PLMN_SEARCH_RSLT_ENUM
{
    NAS_MMC_HIGH_PRIO_PLMN_SEARCH_SUCC         = 0,                             /* 高优先级搜索成功完成 */
    NAS_MMC_HIGH_PRIO_PLMN_SEARCH_FAIL         = 1,                             /* 高优先级搜索未完成 */
    NAS_MMC_HIGH_PRIO_PLMN_SEARCH_ABORTED      = 2,                             /* 高优先级搜索被Abort */
    NAS_MMC_HIGH_PRIO_PLMN_SEARCH_BUTT
};
typedef VOS_UINT32 NAS_MMC_HIGH_PRIO_PLMN_SEARCH_RSLT_ENUM_UINT32;


/*****************************************************************************
 枚举名    : NAS_MMC_SEARCHED_LIST_INFO_TYPE_ENUM_UINT8
 结构说明  : LIST搜网状态机退出带的列表搜网结果类型
 1.日    期   : 2015年9月18日
   作    者   : z00161729
   修改内容   : 支持LTE CSG功能新增
*****************************************************************************/
enum NAS_MMC_SEARCHED_LIST_INFO_TYPE_ENUM
{
    NAS_MMC_SEARCHED_LIST_INFO_TYPE_NOT_CSG_LIST = 0,  /* list搜网结果是普通用户列表搜网或内部列表搜网类型 */
    NAS_MMC_SEARCHED_LIST_INFO_TYPE_CSG_LIST     = 1,  /* list搜网结果是CSG LIST搜网类型 */
    NAS_MMC_SEARCHED_LIST_INFO_TYPE_BUTT
};
typedef VOS_UINT8 NAS_MMC_SEARCHED_LIST_INFO_TYPE_ENUM_UINT8;

/* Added by s00246516 for L-C互操作项目, 2014-01-28, Begin */
/*****************************************************************************
枚举名    : NAS_MMC_POWEROFF_RSLT_ENUM
结构说明  : POWEROFF状态机退出结果
1.日    期   : 2014年1月28日
  作    者   : s00246516
  修改内容   : 新增
*****************************************************************************/
enum NAS_MMC_POWEROFF_RSLT_ENUM
{
    NAS_MMC_POWEROFF_RSLT_POWER_OFF            = 0,
    NAS_MMC_POWEROFF_RSLT_POWER_SAVE           = 1,
    NAS_MMC_POWEROFF_RSLT_BUTT
};
typedef VOS_UINT32 NAS_MMC_POWEROFF_RSLT_ENUM_UINT32;
/* Added by s00246516 for L-C互操作项目, 2014-01-28, End */

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
 结构名    : NAS_MMC_ABORT_FSM_STRU
 结构说明  : MMC发送终止状态机消息的结构
 1.日    期   : 2011年7月12日
   作    者   : zhoujun 40661
   修改内容   : 终止状态机消息的结构

 2.日    期   : 2011年11月29日
   作    者   : w00167002
   修改内容   : DTS2011112301233:增加打断事件ID，状态机可以知道是什么事件
                打断自己的。
                修改原因:用户下发关机命令后，当前可能在等注册结果或者在等连接
                释放，可能需要比较久的时间才能处理关机命令，通过增加打断事件，
                如归当前在等注册结果或者等链接释放状态，若收到关机命令，则直接
                退出当前状态机，处理用户的关机命令。
*****************************************************************************/

typedef struct
{
    VOS_MSG_HEADER
    VOS_UINT32                          ulMsgID;                                /* 消息ID */

    VOS_UINT32                          ulEventType;                            /* 打断事件ID */

    NAS_MMC_ABORT_FSM_TYPE_UINT8        enAbortFsmType;
    VOS_UINT8                           aucReserved[3];
}NAS_MMC_ABORT_FSM_STRU;

/*****************************************************************************
 结构名称: NAS_MMC_INTER_ANYCELL_SEARCH_REQ_STRU
 结构说明:  MMC->MMC,内部Anycell搜网类型标识

  1.日    期   : 2011年7月19日
    作    者   : l00130025
    修改内容   : 内部搜网消息的结构
  2.日    期   : 2014年6月23日
    作    者   : z00161729
    修改内容   : DSDS III新增
*****************************************************************************/
typedef struct
{
    MSG_HEADER_STRU                     stMsgHeader;
    NAS_MML_PLMN_RAT_PRIO_STRU          stAnycellSrchRatList;                   /* 当前要搜索的接入技术列表 */

    NAS_MMC_ANYCELL_SEARCH_SCENE_ENUM_UINT8  enAnycellSearchScene;
    VOS_UINT8                            aucReserved[3];
}NAS_MMC_INTER_ANYCELL_SEARCH_REQ_STRU;


/*****************************************************************************
 结构名称: NAS_MMC_INTER_PLMN_SEARCH_REQ_STRU
 结构说明: MMC->MMC,内部搜网消息的结构
 1.日    期   : 2011年7月11日
   作    者   : sunxibo 46746
   修改内容   : 新增
*****************************************************************************/
typedef struct
{
    MSG_HEADER_STRU                         stMsgHeader;            /* 消息头 */
    NAS_MMC_PLMN_SEARCH_SCENE_ENUM_UINT32   enPlmnSearchScene;      /* 搜网场景 */
    NAS_MMC_SEARCHED_PLMN_LIST_INFO_STRU    astInterPlmnSearchInfo[NAS_MML_MAX_RAT_NUM]; /* 携带网络信息 */
}NAS_MMC_INTER_PLMN_SEARCH_REQ_STRU;

/*****************************************************************************
 结构名称: NAS_MMC_INTER_PLMN_LIST_REQ_STRU
 结构说明: MMC->MMC,内部LIST搜网消息的结构
 1.日    期   : 2011年9月19日
   作    者   : w00176964
   修改内容   : 新增
*****************************************************************************/
typedef struct
{
    MSG_HEADER_STRU                     MsgHeader;                        /* 消息头 */
}NAS_MMC_INTER_PLMN_LIST_REQ_STRU;

/*****************************************************************************
 结构名称: NAS_MMC_INTER_DPLMN_SET_REQ_STRU
 结构说明: MMC->MMC,内部DPLMN SET REQ消息的结构
  1.日    期   : 2015年11月9日
    作    者   : s00217060
    修改内容   : 新增
*****************************************************************************/
typedef struct
{
    MSG_HEADER_STRU                     stMsgHeader;                                        /* 消息头 */
    VOS_UINT8                           aucVersionId[NAS_MSCC_PIF_INFO_VERSION_LEN];        /* 版本号，固定为xx.xx.xxx */
    VOS_UINT8                           ucEhPlmnNum;                                        /* EHPLMN的个数*/
    VOS_UINT8                           aucReserve[2];
    NAS_MML_PLMN_ID_STRU                astEhPlmnInfo[NAS_MML_MAX_EHPLMN_NUM + 1];          /* EHPLMN ID列表 */
}NAS_MMC_INTER_DPLMN_SET_REQ_STRU;

/*****************************************************************************
 结构名称: NAS_MMCMMC_GET_GEO_RSLT_STRU
 结构说明: MMC->MMC,内部获取地理信息结果消息的结构
 1.日    期   : 2015年05月08日
   作    者   : sunjitan 00193151
   修改内容   : 新增
*****************************************************************************/
typedef struct
{
    MSG_HEADER_STRU                               stMsgHeader;  /* 消息头 */

    NAS_MMC_GET_GEO_RSLT_ENUM_UINT32              enGetGeoRslt; /* 获取地理信息结果 */
    NAS_MML_PLMN_ID_STRU                          stGetGeoPlmn; /* 获取地理信息成功时有效，获取到的PLMN */
}NAS_MMCMMC_GET_GEO_RSLT_STRU;

/*****************************************************************************
 结构名称: NAS_MMC_SWITCHON_RLST_STRU
 协议表格:
 ASN.1 描述:
 结构说明:  MMC->MMC,开机结果

  1.日    期   : 2011年5月9日
    作    者   : zhoujun 40661
    修改内容   : 开机消息的结构
*****************************************************************************/
typedef struct
{
    MSG_HEADER_STRU                            MsgHeader;
    VOS_UINT32                                 ulResult;
} NAS_MMC_SWITCHON_RLST_STRU;


/*****************************************************************************
 结构名称: NAS_MMCMMC_ANYCELL_SEARCH_RSLT_STRU
 结构说明:  MMC->MMC,Anycell搜网结果

  1.日    期   : 2011年7月11日
    作    者   : l00130025
    修改内容   : Anycell搜网结果
*****************************************************************************/
typedef struct
{
    MSG_HEADER_STRU                             MsgHeader;
    NAS_MMC_ANYCELL_SEARCH_RESULT_ENUM_UINT32   enResult;
} NAS_MMCMMC_ANYCELL_SEARCH_RSLT_STRU;

/*****************************************************************************
 结构名称: NAS_MMCMMC_PLMN_SELECTION_RSLT_STRU
 结构说明:  MMC->MMC,PlmnSelection搜网结果

  1.日    期   : 2011年7月11日
    作    者   : l00130025
    修改内容   : 选网结果内部消息结果
*****************************************************************************/
typedef struct
{
    MSG_HEADER_STRU                             MsgHeader;                              /*消息头*/
    NAS_MMC_PLMN_SELECTION_RESULT_ENUM_UINT32   enResult;                               /*选网结果*/
    VOS_UINT32                                  ulCampFlg;                              /*当前是否驻留标志,VOS_TRUE:已驻留,VOS_FALSE:未驻留*/
    VOS_UINT32                                  ulRatNum;                               /*有覆盖的接入技术个数*/
    NAS_MMC_RAT_SEARCH_INFO_STRU                astSearchRatInfo[NAS_MML_MAX_RAT_NUM];  /*保存不同接入技术的搜索信息*/
    /* Added by c00318887 for 预置频点搜网优化, 2015-9-2, begin */
    NAS_MMC_PLMN_SEARCH_SCENE_ENUM_UINT32       ulPlmnSearchScene;                      /* 搜网场景 */
    /* Added by c00318887 for 预置频点搜网优化, 2015-9-2, end */
} NAS_MMCMMC_PLMN_SELECTION_RSLT_STRU;

/*****************************************************************************
 结构名称: NAS_MMCMMC_INTER_SKIP_SEARCH_W_IND_STRU
 结构说明:  MMC->MMC,通知UTRANCTRL跳过搜W结果

  1.日    期   : 2014年2月11日
    作    者   : w00167002
    修改内容   : 通知UTRANCTRL跳过搜网W结果.
                 注:SVLTE共天线，在W下搜网NO RF后，在G下搜网成功国内驻留成功后，
                 后续再发起搜网时候不能搜WAS,否则G会丢网。但在UTRANCTRL状态机时候
                 ，NO RF时候当前是FDD模式的，因而MMC再发起搜网时候，会先给WAS发送，
                 UTRAN构造SKIP W消息，在UTRANCTRL状态机搜索TDD.
*****************************************************************************/
typedef struct
{
    MSG_HEADER_STRU                             MsgHeader;
    VOS_UINT8                                   aucReserved[4];
} NAS_MMCMMC_INTER_SKIP_SEARCH_W_IND_STRU;

/*****************************************************************************
 结构名称: NAS_MMCMMC_INTER_SKIP_SEARCH_TDS_IND_STRU
 结构说明:  MMC->MMC,通知UTRANCTRL跳过搜tds结果

  1.日    期   : 2014年11月3日
    作    者   : z00161729
    修改内容   : 新增函数
*****************************************************************************/
typedef struct
{
    MSG_HEADER_STRU                             MsgHeader;
    VOS_UINT8                                   aucReserved[4];
} NAS_MMCMMC_INTER_SKIP_SEARCH_TDS_IND_STRU;

/*****************************************************************************
 结构名称: MMCMMC_INTER_ABORT_UTRAN_CTRL_PLMN_SEARCH_REQ_STRU
 结构说明:  MMC->MMC,通知UTRANCTRL停止搜网更新utran ctrl mode消息

  1.日    期   : 2014年11月3日
    作    者   : z00161729
    修改内容   : 新增函数
*****************************************************************************/
typedef struct
{
    MSG_HEADER_STRU                             MsgHeader;
    VOS_UINT8                                   aucReserved[4];
} NAS_MMCMMC_INTER_ABORT_UTRAN_CTRL_PLMN_SEARCH_REQ_STRU;

/*****************************************************************************
 结构名称: MMCMMC_INTER_ABORT_UTRAN_CTRL_PLMN_SEARCH_CNF_STRU
 结构说明:  MMC->MMC,utran ctrl 回复mmc MMCMMC_INTER_ABORT_UTRAN_CTRL_PLMN_SEARCH_REQ

  1.日    期   : 2014年11月3日
    作    者   : z00161729
    修改内容   : 新增函数
*****************************************************************************/
typedef struct
{
    MSG_HEADER_STRU                             MsgHeader;
    VOS_UINT8                                   aucReserved[4];
} NAS_MMCMMC_INTER_ABORT_UTRAN_CTRL_PLMN_SEARCH_CNF_STRU;



/*****************************************************************************
 结构名称: NAS_MMCMMC_INTER_UTRAN_CTRL_PLMN_SELECTION_ABORT_FINISH_IND_STRU
 结构说明: MMC->MMC,通知UTRANCTRL已被ABORT

  1.日    期   : 2015年12月17日
    作    者   : w00167002
    修改内容   : 新增函数
*****************************************************************************/
typedef struct
{
    MSG_HEADER_STRU                             MsgHeader;
    VOS_UINT8                                   aucReserved[4];
} NAS_MMCMMC_INTER_UTRAN_CTRL_PLMN_SELECTION_ABORT_FINISH_IND_STRU;


/*****************************************************************************
 结构名称: NAS_MMCMMC_SUSPEND_RSLT_STRU
 结构说明:  MMC->MMC,重选,HO,CCO状态机结果

  1.日    期   : 2011年7月18日
    作    者   : w00176964
    修改内容   : 新建
*****************************************************************************/
typedef struct
{
    MSG_HEADER_STRU                                         stMsgHeader;

    /* 挂起类型 */
    MMC_SUSPEND_CAUSE_ENUM_UINT8                            enSuspendCause;

    /* 状态机失败原因 */
    NAS_MMC_SUSPEND_FAIL_CAUSE_ENUM_UINT8                   enFailCause;

    VOS_UINT8                                               ucReserve[2];

    /*状态机完成的结果 */
    NAS_MMC_SUSPEND_RSLT_ENUM_UINT32                        enRslt;


    /* 接入层上报的网络列表 */
    NAS_MMC_SEARCHED_PLMN_LIST_INFO_STRU                    astPlmnSearchInfo[NAS_MML_MAX_RAT_NUM];
}NAS_MMCMMC_SUSPEND_RSLT_STRU;


/*****************************************************************************
 结构名称: NAS_MMCMMC_PLMN_LIST_RSLT_STRU
 结构说明:  MMC->MMC,user list搜网状态机结果
 1.日    期   : 2011年8月30日
   作    者   : w00176964
   修改内容   : 新建
 2.日    期   : 2012年5月8日
   作    者   : t00212959
   修改内容   : GUL BG项目调整
*****************************************************************************/
typedef struct
{
    MSG_HEADER_STRU                                         stMsgHeader;

    /* 状态机完成的结果 */
    NAS_MMC_PLMN_LIST_RESULT_ENUM_UINT32                    enRslt;

    /* 是否需要搜网 */
    VOS_UINT8                                               ucNeedPlmnSearch;

    /* 当前网络CS域注册结果的附加处理 */
    NAS_MMC_ADDITIONAL_ACTION_ENUM_UINT8                    enCsRegAdditionalAction;

    /* 当前网络PS域注册结果的附加处理 */
    NAS_MMC_ADDITIONAL_ACTION_ENUM_UINT8                    enPsRegAdditionalAction;

    VOS_UINT8                                               aucReserve[1];

    /* plmn list搜网状态机的结果 */
    NAS_MMC_SEARCHED_PLMN_LIST_INFO_STRU                    astPlmnSearchInfo[NAS_MML_MAX_RAT_NUM];

    NAS_MMC_PLMN_LIST_SEARCH_SCENE_ENUM_UINT8               enPlmnListSearchScene;            /* 携带搜网场景*/
    VOS_UINT8                                               aucReserved[3];

}NAS_MMCMMC_PLMN_LIST_RSLT_STRU;


typedef struct
{
    MSG_HEADER_STRU                     stMsgHeader;

    /* Added by s00246516 for L-C互操作项目, 2014-01-28, Begin */
    NAS_MMC_POWEROFF_RSLT_ENUM_UINT32   enRslt;
    /* Added by s00246516 for L-C互操作项目, 2014-01-28, End */
}NAS_MMCMMC_POWEROFF_RSLT_STRU;


/*****************************************************************************
 结构名称:  NAS_MMCMMC_SysCfg_RSLT_STRU
 结构说明:  MMC->MMC,SYSCFG状态机完成结果消息

 1.日    期   : 2011年7月18日
   作    者   : w00167002
   修改内容   : 新增结构
 2.日    期   : 2015年2月26日
   作    者   : w00167002
   修改内容   : DTS2015021604972:在SYSCFG设置完后，MMA进行ATTACH流程。MMC已经退出
                 SYSCFG状态机，并触发搜网。在搜网时候，如果PS不准许ATTACH，则不搜索LTE.
                 现修改为在SYSCFG后,如果需要搜网，则判别是否ATTACH PS需要先ENABLE LTE。
*****************************************************************************/
typedef struct
{
    MSG_HEADER_STRU                     stMsgHeader;        /* 消息头 */
    VOS_UINT32                          ulRslt;             /* SYSCFG状态机完成结果:VOS_TRUE:SYSCFG设置成功，VOS_FALSE:SYSCFG设置失败 */
    VOS_UINT32                          ulNeedPlmnSrch;     /* SYSCFG状态机完成是否需要搜网:VOS_TRUE:SYSCFG设置成功后需要搜网，VOS_FALSE:YSCFG设置成功后不需要搜网 */

    VOS_UINT32                          ulIsNeedAttachPs;

    NAS_MML_PLMN_RAT_PRIO_STRU          stPrePrioRatList;   /* 进syscfg状态机前的接入技术和优先级 */


} NAS_MMCMMC_SysCfg_RSLT_STRU;

/*****************************************************************************
 结构名称: NAS_MMCMMC_BG_PLMN_SEARCH_RSLT_STRU
 结构说明:  MMC->MMC,BgPlmnSearch状态机退出结果
 1.日    期   : 2011年9月20日
   作    者   : s46746
   修改内容   : 新增结构
 2.日    期   : 2012年5月8日
   作    者   : z00161729
   修改内容   : V7R1C50 GUL BG搜网修改
*****************************************************************************/
typedef struct
{
    MSG_HEADER_STRU                             stMsgHeader;                    /* 消息头 */
    NAS_MMC_BG_PLMN_SEARCH_RSLT_ENUM_UINT32     enRslt;                         /* BG搜索结果 */
    VOS_UINT32                                  ulNeedPlmnSearch;               /* 是否需要搜网标志,VOS_TRUE:需要搜网,VOS_FALSE:不需要搜网 */
    VOS_UINT32                                  ulSearchCompleted;              /* 是否完成高优先级搜网标志,VOS_TRUE::本轮高优先级搜网结束；VOS_FALSE:本轮高优先级搜网未结束 */
    NAS_MMC_SEARCHED_PLMN_LIST_INFO_STRU        stSearchedPlmnListInfo;         /* 携带网络信息 */

    NAS_MMC_BG_PLMN_SEARCH_SCENE_ENUM_UINT8     enBgPlmnSearchScene;            /* 携带搜网场景*/
    VOS_UINT8                                   aucReserved[3];
} NAS_MMCMMC_BG_PLMN_SEARCH_RSLT_STRU;

typedef struct
{
    MSG_HEADER_STRU                     MsgHeader;                        /* 消息头 */
}NAS_MMC_INTER_NVIM_OPLMN_REFRESH_IND_STRU;

/*****************************************************************************
 结构名称: NAS_MMC_INTER_UPDATE_UPLMN_NTF_STRU
 结构说明: MMC->MMC,更新UPLMN消息的结构
 1.日    期   : 2015年02月09日
   作    者   : y00307564
   修改内容   : 新增
*****************************************************************************/
typedef struct
{
    MSG_HEADER_STRU                     MsgHeader;                        /* 消息头 */
}NAS_MMC_INTER_UPDATE_UPLMN_NTF_STRU;

/*****************************************************************************
  8 UNION定义
*****************************************************************************/


/*****************************************************************************
  9 OTHERS定义
*****************************************************************************/


/*****************************************************************************
  10 函数声明
*****************************************************************************/
VOS_VOID  NAS_MMC_SndAbortFsmMsg(
    VOS_UINT32                          ulEventType,
    NAS_MMC_ABORT_FSM_TYPE_UINT8        enAbortFsmType
);
VOS_VOID NAS_MMC_SndSwitchOnRlst(VOS_UINT32 ulResult);

VOS_VOID  NAS_MMC_SndSuspendRsltMsg(
    MMC_SUSPEND_CAUSE_ENUM_UINT8                            enSuspendCause,
    NAS_MMC_SUSPEND_RSLT_ENUM_UINT32                        enSuspendRslt,
    NAS_MMC_SUSPEND_FAIL_CAUSE_ENUM_UINT8                   enSuspendFailCause,
    NAS_MMC_SEARCHED_PLMN_LIST_INFO_STRU                   *pstListInfo
);


/* Modified by c00318887 for 预置频点搜网优化, 2015-9-2, begin */
VOS_VOID  NAS_MMC_SndPlmnSelectionRslt(
    NAS_MMC_PLMN_SELECTION_RESULT_ENUM_UINT32               enPlmnSelectionRslt,
    VOS_UINT32                                              ulCampFlg,
    NAS_MMC_RAT_SEARCH_INFO_STRU                           *pstSearchRatInfo,
    VOS_UINT32                                              ulRatNum,
    NAS_MMC_PLMN_SEARCH_SCENE_ENUM_UINT32                   ulPlmnSearchScene
);
/* Modified by c00318887 for 预置频点搜网优化, 2015-9-2, end */

VOS_VOID  NAS_MMC_SndInterSkipSearchWIndMsg(VOS_VOID);

VOS_VOID  NAS_MMC_SndInterSkipSearchTdsIndMsg(VOS_VOID);

VOS_VOID  NAS_MMC_SndInterAbortUtranCtrlPlmnSearchCnfMsg(VOS_VOID);

VOS_VOID  NAS_MMC_SndInterAbortUtranCtrlPlmnSearchReqMsg(VOS_VOID);



VOS_VOID NAS_MMC_SndAnycellSearchRslt(
    NAS_MMC_ANYCELL_SEARCH_RESULT_ENUM_UINT32               enResult
);

VOS_VOID  NAS_MMC_SndBgPlmnSearchRslt(
    NAS_MMC_BG_PLMN_SEARCH_RSLT_ENUM_UINT32                 enPlmnSelectionRslt,
    VOS_UINT32                                              ulNeedPlmnSearch,
    NAS_MMC_BG_PLMN_SEARCH_SCENE_ENUM_UINT8                 enBgPlmnSearchScene,
    VOS_UINT32                                              ulBgSearchCompleted,
    NAS_MMC_SEARCHED_PLMN_LIST_INFO_STRU                   *pstSearchedPlmnListInfo
);



VOS_VOID  NAS_MMC_SndSysCfgRslt(
    VOS_UINT32                          ulSysCfgRslt,
    VOS_UINT32                          ulNeedPlmnSrch,
    VOS_UINT32                          ulIsNeedAttachPs,
    NAS_MML_PLMN_RAT_PRIO_STRU         *pstPrePrioRatList
);

VOS_VOID NAS_MMC_SndInterPlmnSearchReq(
    NAS_MMC_PLMN_SEARCH_SCENE_ENUM_UINT32    enPlmnSearchScene,
    NAS_MMC_SEARCHED_PLMN_LIST_INFO_STRU    *pstIntraPlmnSrchInfo,
    VOS_UINT8                                ucRatNum
);

VOS_VOID NAS_MMC_SndInterPlmnListReq(VOS_VOID);

VOS_VOID NAS_MMC_SndInterAnyCellSearchReq(
    NAS_MML_PLMN_RAT_PRIO_STRU                             *pstAnycellSrchRatList,
    NAS_MMC_ANYCELL_SEARCH_SCENE_ENUM_UINT8                 enAnycellSearchScene
);


VOS_VOID NAS_MMC_BulidInterPlmnSearchReqMsg(
    NAS_MMC_PLMN_SEARCH_SCENE_ENUM_UINT32                   enPlmnSearchScene,
    NAS_MMC_SEARCHED_PLMN_LIST_INFO_STRU                   *pstIntraPlmnSrchInfo,
    VOS_UINT8                                               ucRatNum,
    NAS_MMC_INTER_PLMN_SEARCH_REQ_STRU                     *pstMsg
);

VOS_VOID NAS_MMC_BuildInterDplmnSetReqMsg(
    VOS_UINT8                                              *pucVersion,
    VOS_UINT8                                               ucEhPlmnNum,
    NAS_MSCC_PIF_PLMN_ID_STRU                              *pstEhPlmnInfo,
    NAS_MMC_INTER_DPLMN_SET_REQ_STRU                       *pstMsg
);
/* Modified by s00246516 for L-C互操作项目, 2014-02-14, Begin */
VOS_VOID NAS_MMC_SndPowerOffRslt(
    NAS_MMC_POWEROFF_RSLT_ENUM_UINT32   enRslt
);
/* Modified by s00246516 for L-C互操作项目, 2014-02-14, End */

VOS_VOID NAS_MMC_SndPlmnListRslt(
    NAS_MMC_PLMN_LIST_RESULT_ENUM_UINT32                    enRslt,
    VOS_UINT8                                               ulNeedPlmnSearch,
    NAS_MMC_PLMN_LIST_SEARCH_SCENE_ENUM_UINT8               enPlmnListSearchScene,
    NAS_MMC_SEARCHED_PLMN_LIST_INFO_STRU                    *pstListInfo,
    NAS_MMC_PLMN_LIST_REG_RSLT_INFO_STRU                    *pstRegRsltInfo
);

VOS_VOID NAS_MMC_SndInterNvimOPlmnRefreshInd(VOS_VOID);

VOS_VOID  NAS_MMC_SndGetGeoRsltMsg(
    NAS_MMC_GET_GEO_RSLT_ENUM_UINT32    enGetGeoRslt,
    NAS_MML_PLMN_ID_STRU               *pstGetGeoPlmn
);

VOS_VOID NAS_MMC_SndInterUpdateUplmnNtf(VOS_VOID);

#if (VOS_OS_VER == VOS_WIN32)
#pragma pack()
#else
#pragma pack(0)
#endif




#ifdef __cplusplus
    #if __cplusplus
        }
    #endif
#endif

#endif

