/******************************************************************************

                  版权所有 (C), 2001-2012, 华为技术有限公司

 ******************************************************************************
  文 件 名   : MmaMsccInterface.h
  版 本 号   : 初稿
  作    者   : z00161729
  生成日期   : 2013年3月25日
  最近修改   :
  功能描述   : mma与mscc消息交互的头文件
  函数列表   :
  修改历史   :
  1.日    期   : 2013年3月25日
    作    者   : z00161729
    修改内容   : 创建文件

******************************************************************************/
#ifndef _MMA_MSCC_INTERFACE_H_
#define _MMA_MSCC_INTERFACE_H_

/*****************************************************************************
  1 其他头文件包含
*****************************************************************************/
#include "PsTypeDef.h"
#include "TafAppMma.h"
#include "NasMsccPifInterface.h"
#include "TafMmaInterface.h"




#ifdef __cplusplus
#if __cplusplus
extern "C" {
#endif
#endif


#pragma pack(4)

/*****************************************************************************
  2 宏定义
*****************************************************************************/
#define MSCC_MMA_SECOND_COLORCODE_MAX_LENGTH                ( 5 )
#define MSCC_MMA_SUBNET_ID_MAX_LENGTH                       ( 16 )

#define     MSCC_MMA_CAS_STA_INVALID_SUBSTA                 (0xFF)

#define     MSCC_MMA_MAX_SRCHED_LAI_NUM  (18)

/*****************************************************************************
  3 枚举定义
*****************************************************************************/



enum MSCC_MMA_HRPD_SERVICE_STATUS_ENUM
{
    MSCC_MMA_HRPD_SERVICE_STATUS_NORMAL_SERVICE         = 0,              /* HRPD is in normal service */
    MSCC_MMA_HRPD_SERVICE_STATUS_NO_SERVICE             = 1,              /* HRPD has no service */
    MSCC_MMA_HRPD_SERVICE_STATUS_BUTT
};
typedef VOS_UINT32 MSCC_MMA_HRPD_SERVICE_STATUS_ENUM_UINT32;


enum MSCC_MMA_HRPD_SYS_ACQ_RSLT_ENUM
{
    MSCC_MMA_HRPD_ACQUIRED_RESULT_SUCC        = 0x00000000,
    MSCC_MMA_HRPD_ACQUIRED_RESULT_FAIL        = 0x00000001,
    MSCC_MMA_HRPD_ACQUIRED_RESULT_ABORTED     = 0x00000002,
    MSCC_MMA_HRPD_ACQUIRED_RESULT_BUTT
};
typedef VOS_UINT32 MSCC_MMA_HRPD_SYS_ACQ_RSLT_ENUM_UINT32;


enum MSCC_MMA_HRPD_SESSION_RELEASE_TYPE_ENUM
{
    MSCC_MMA_SESSION_RELEASE_TYPE_0     = 0x00,
    MSCC_MMA_SESSION_RELEASE_TYPE_A     = 0x01,
    MSCC_MMA_SESSION_RELEASE_TYPE_BUTT  = 0x02
};
typedef VOS_UINT32 MSCC_MMA_HRPD_SESSION_RELEASE_TYPE_ENUM_UINT32;

/*****************************************************************************
 枚举名    : MSCC_MMA_ACQ_SYS_TYPE_ENUM
 枚举说明  : 系统捕获的类型
 1.日    期   : 2015年2月10日
   作    者   : h00246512
   修改内容   : 新建
*****************************************************************************/
enum MSCC_MMA_ACQ_SYS_TYPE_ENUM
{
    MSCC_MMA_ACQ_SYS_TYPE_3GPP,                                             /* GUL模式下3GPP下的搜网开始或结束指示的系统类型(包含LTE ONLY)*/
    MSCC_MMA_ACQ_SYS_TYPE_1X,                                               /* 1X的捕获开始或结束指示的系统类型 */
    MSCC_MMA_ACQ_SYS_TYPE_DO,                                               /* CL模式下且不支持LTE时,DO的捕获开始或结束指示的系统类型 */
    MSCC_MMA_ACQ_SYS_TYPE_DO_LTE,                                           /* CL模式下支持LTE时,DO或LTE捕获开始或结束指示的系统类型 */
    MSCC_MMA_ACQ_SYS_TYPE_BUTT
};
typedef VOS_UINT32 MSCC_MMA_ACQ_SYS_TYPE_ENUM_UINT32;

/*****************************************************************************
 枚举名    : MMA_MSCC_HANDSET_INFO_TYPE_ENUM
 枚举说明  : 查询的手机信息类型
 1.日    期   : 2015年5月18日
   作    者   : z00316370
   修改内容   : 新建
*****************************************************************************/
enum MMA_MSCC_HANDSET_INFO_TYPE_ENUM
{
    MMA_MSCC_HANDSET_INFO_TYPE_STATE,
    MMA_MSCC_HANDSET_INFO_TYPE_HVERSION,

    MMA_MSCC_HANDSET_INFO_TYPE_BUTT
};
typedef VOS_UINT32 MMA_MSCC_HANDSET_INFO_TYPE_ENUM_UINT32;

/** ****************************************************************************
 * Name        : MSCC_MMA_1X_CAS_P_REV_ENUM_UINT8
 *
 * Description : .
 * Refers to  C.S0017 2.6.5.5
 *******************************************************************************/
enum MSCC_MMA_1X_CAS_P_REV_ENUM
{
    MSCC_MMA_1X_CAS_P_REV_JST_008               = 0x01,
    MSCC_MMA_1X_CAS_P_REV_IS_95                 = 0x02,
    MSCC_MMA_1X_CAS_P_REV_IS_95A                = 0x03,
    MSCC_MMA_1X_CAS_P_REV_IS_95B_CUSTOM         = 0x04,
    MSCC_MMA_1X_CAS_P_REV_IS_95B                = 0x05,
    MSCC_MMA_1X_CAS_P_REV_IS_2000               = 0x06,
    MSCC_MMA_1X_CAS_P_REV_IS_2000A              = 0x07,

    MSCC_MMA_1X_CAS_P_REV_ENUM_BUTT
};
typedef VOS_UINT8 MSCC_MMA_1X_CAS_P_REV_ENUM_UINT8;

/** ****************************************************************************
 * Name        : MSCC_MMA_1X_CAS_STATE_ENUM_UINT8
 *
 * Description : When MS is in the different state, MS should perform
 * different actions.
 * Refers to  C.S0017 2.6.5.5
 *******************************************************************************/
enum MSCC_MMA_1X_CAS_STATE_ENUM
{
    MSCC_MMA_1X_CAS_INIT_STATE          = 0x00,
    MSCC_MMA_1X_CAS_IDLE_STATE          = 0x01,
    MSCC_MMA_1X_CAS_ACCESS_STATE        = 0x02,
    MSCC_MMA_1X_CAS_TCH_STATE           = 0x03,
    MSCC_MMA_1X_CAS_NO_SERVICE_STATE    = 0x04,
    MSCC_MMA_1X_CAS_STATE_ENUM_BUTT     = 0x05
};
typedef VOS_UINT8 MSCC_MMA_1X_CAS_STATE_ENUM_UINT8;

/** ****************************************************************************
 * Name        : MSCC_MMA_1X_CAS_SUB_STATE_ENUM_UINT8
 *
 * Description : .
 * Refers to  C.S0017 2.6.5.5
 *******************************************************************************/
enum MSCC_MMA_1X_CAS_SUB_STATE_ENUM
{
    MSCC_MMA_1X_CAS_SUB_STATE_NULL                          = 0x00,
    MSCC_MMA_1X_CAS_INIT_DETERM_SUB_STATE                   = 0x01,
    MSCC_MMA_1X_CAS_PILOT_CH_ACQ_SUB_STATE                  = 0x02,
    MSCC_MMA_1X_CAS_SYNC_CH_ACQ_SUB_STATE                   = 0x03,
    MSCC_MMA_1X_CAS_TIMING_CHNG_SUB_STATE                   = 0x04,
    MSCC_MMA_1X_CAS_IDLE_SUB_STATE                          = 0x10,
    MSCC_MMA_1X_CAS_UPDATE_OVERHEAD_SUB_STATE               = 0x20,
    MSCC_MMA_1X_CAS_MOB_STATION_ORIG_ATTEMPT_SUB_STATE      = 0x21,
    MSCC_MMA_1X_CAS_PAG_RESP_SUB_STATE                      = 0x22,
    MSCC_MMA_1X_CAS_MOB_STATION_ORDR_RESP_SUB_STATE         = 0x23,
    MSCC_MMA_1X_CAS_REG_ACCESS_SUB_STATE                    = 0x24,
    MSCC_MMA_1X_CAS_MOB_STATION_MSG_TRANS_SUB_STATE         = 0x25,
    MSCC_MMA_1X_CAS_TCH_INIT_SUB_STATE                      = 0x30,
    MSCC_MMA_1X_CAS_REL_SUB_STATE                           = 0x31,
    MSCC_MMA_1X_CAS_WAIT_FOR_SERVICE_SUB_STATE              = 0x40,
    MSCC_MMA_1X_CAS_SUB_STATE_ENUM_BUTT                     = 0x41
};
typedef VOS_UINT8 MSCC_MMA_1X_CAS_SUB_STATE_ENUM_UINT8;

/*****************************************************************************
 枚举名    : MSCC_MMA_1X_CALL_STATE_ENUM
 结构说明  : 1X呼叫状态

 1.日    期   : 2015年05月22日
   作    者   : z00316370
   修改内容   : 新增
*****************************************************************************/
enum MSCC_MMA_1X_CALL_STATE_ENUM
{
    MSCC_MMA_1X_CALL_STATE_WAIT_FOR_ORDER,
    MSCC_MMA_1X_CALL_STATE_WAIT_FOR_ANSWER,
    MSCC_MMA_1X_CALL_STATE_CONVERSATION,

    MSCC_MMA_1X_CALL_STATE_BUTT
};
typedef VOS_UINT8 MSCC_MMA_1X_CALL_STATE_ENUM_UINT8;





/*****************************************************************************
 枚举名    :  MSCC_MMA_CL_SYSTEM_ACQUIRE_RESULT_TYPE_ENUM_UINT32
 枚举说明  : CL系统捕获结果的类型
 1.日    期   : 2015年6月12日
   作    者   : w00176964
   修改内容   : 新建
*****************************************************************************/
enum  MSCC_MMA_CL_SYSTEM_ACQUIRE_RESULT_TYPE_ENUM
{
    MSCC_MMA_CL_SYSTEM_ACQUIRE_RESULT_TYPE_FAIL,
    MSCC_MMA_CL_SYSTEM_ACQUIRE_RESULT_TYPE_DO_SUCC,
    MSCC_MMA_CL_SYSTEM_ACQUIRE_RESULT_TYPE_LTE_SUCC,
    MSCC_MMA_CL_SYSTEM_ACQUIRE_RESULT_TYPE_BUTT
};
typedef VOS_UINT32  MSCC_MMA_CL_SYSTEM_ACQUIRE_RESULT_TYPE_ENUM_UINT32;



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
 结构名    : MMA_MSCC_PLMN_RAT_PRIO_STRU
 结构说明  : 当前支持接入技术和接入技术优先级的数据结构
 1.日    期: 2013年3月25日
   作    者: z00161729
   修改内容: 新增
 2.日    期   : 2015年5月122日
   作    者   : W00176964
   修改内容   : CDMA Iteration 10 modified
*****************************************************************************/
typedef  NAS_MSCC_PIF_RAT_PRIO_STRU MMA_MSCC_PLMN_RAT_PRIO_STRU;

/*****************************************************************************
 结构名    : MMA_MSCC_PLMN_ID_STRU
 结构说明  : plmn id的数据结构
 1.日    期: 2013年3月25日
   作    者: z00161729
   修改内容: 新增
*****************************************************************************/
typedef  NAS_MSCC_PIF_PLMN_ID_STRU MMA_MSCC_PLMN_ID_STRU;

/* Added by s00246516 for L-C互操作项目, 2014-01-26, Begin */
/*****************************************************************************
 结构名    : MMA_MSCC_3GPP2_RAT_STRU
 结构说明  : MS 3GPP2的接入技术能力
 1.日    期   : 2014年1月26日
   作    者   : s00246516
   修改内容   : 新建
*****************************************************************************/
typedef NAS_MSCC_PIF_3GPP2_RAT_STRU MMA_MSCC_3GPP2_RAT_STRU;
/* Added by s00246516 for L-C互操作项目, 2014-01-26, End */

/*****************************************************************************
 结构名    : MMA_MSCC_EPLMN_INFO_STRU
 结构说明  : MML当前EQUPLMN信息
 1.日    期   : 2013年12月24日
   作    者   : z00161729
   修改内容   : SVLTE支持NCELL搜网
*****************************************************************************/
typedef NAS_MSCC_PIF_EPLMN_INFO_STRU MMA_MSCC_EPLMN_INFO_STRU;


/*****************************************************************************
 结构名    : MMA_MSCC_CAMP_CELL_INFO_STRU
 结构说明  : 当前驻留小区的信息
 1.日    期   : 2013年3月25日
   作    者   : z00161729
   修改内容   : 新建
*****************************************************************************/
typedef NAS_MSCC_PIF_CAMP_CELL_INFO_STRU MMA_MSCC_CAMP_CELL_INFO_STRU;

/*****************************************************************************
 结构名    : MMA_MSCC_OPERATOR_NAME_INFO_STRU
 结构说明  : plmn id和运营商长短名信息
 1.日    期: 2013年3月25日
   作    者: z00161729
   修改内容: 新增
*****************************************************************************/
typedef NAS_MSCC_PIF_OPERATOR_NAME_INFO_STRU MMA_MSCC_OPERATOR_NAME_INFO_STRU;

/*****************************************************************************
 结构名    : MMA_MSCC_UE_SUPPORT_FREQ_BAND_STRU
 结构说明  : ue 支持band能力
 1.日    期: 2013年3月25日
   作    者: z00161729
   修改内容: 新增
*****************************************************************************/
typedef NAS_MSCC_PIF_UE_SUPPORT_FREQ_BAND_STRU MMA_MSCC_UE_SUPPORT_FREQ_BAND_STRU;

/*****************************************************************************
 结构名    : MMA_MSCC_RSSI_VALUE_STRU
 结构说明  : rssi值
 1.日    期: 2013年3月25日
   作    者: z00161729
   修改内容: 新增
*****************************************************************************/
typedef NAS_MSCC_PIF_RSSI_VALUE_STRU MMA_MSCC_RSSI_VALUE_STRU;

/*******************************************************************************
 结构名    :MMA_MSCC_SCELL_MEAS_TYPE_STRU
 结构说明  : union MMA_MSCC_SCELL_MEAS_TYPE_STRU成员stMeasReportType定义
             bit位置1表示该类型有效
1.日    期 : 2014年6月5日
  作    者 : b00269685
  修改内容 : 新建
*******************************************************************************/
typedef NAS_MSCC_PIF_SCELL_MEAS_TYPE_STRU MMA_MSCC_SCELL_MEAS_TYPE_STRU;

/*****************************************************************************
 枚举名    : MMA_MSCC_SCELL_MEAS_REPORT_TYPE_UN
 结构说明  : MMA_MSCC_SCELL_MEAS_REPORT_TYPE_UN unMeasType上报测量的类型
1. 日    期: 2014年6月5日
   作    者: b00269685
   修改内容: 新建
*****************************************************************************/
typedef NAS_MSCC_PIF_SCELL_MEAS_REPORT_TYPE_UN MMA_MSCC_SCELL_MEAS_REPORT_TYPE_UN;

/*****************************************************************************
 结构名    : MSCC_MMA_RSSI_INFO_STRU
 结构说明  : rssi信息
 1.日    期: 2013年3月25日
   作    者: z00161729
   修改内容: 新增
 2.日    期: 2014年6月4日
   作    者: b00269685
   修改内容: 增加上报类型
*****************************************************************************/
typedef NAS_MSCC_PIF_RSSI_IND_STRU MSCC_MMA_RSSI_IND_STRU;

/*****************************************************************************
 结构名    : MSCC_MMA_CQI_INFO_STRU
 结构说明  : LTE下的信道质量,两个码字分别代表子带CQI和宽带CQI
 1.日    期: 2014年11月28日
   作    者: w00281933
   修改内容: 新增
*****************************************************************************/
typedef NAS_MSCC_PIF_CQI_INFO_STRU MSCC_MMA_CQI_INFO_STRU;
/*****************************************************************************
 结构名    : MMA_MSCC_LMM_CELL_SIGN_INFO_STRU
 结构说明  : LTE下的信道质量,包括LTE下的Rssi及Rsrp，Rsrq,SINR,CQI
 1.日    期: 2014年11月28日
   作    者: w00281933
   修改内容: 新增
*****************************************************************************/
typedef NAS_MSCC_PIF_LMM_CELL_SIGN_INFO_STRU MMA_MSCC_LMM_CELL_SIGN_INFO_STRU;
/*****************************************************************************
 结构名    : MSCC_MMA_LMM_CELL_SIGN_INFO_REPORT_IND_STRU
 结构说明  : ID_MSCC_MMA_LMM_CELL_SIGN_INFO_REPORT_IND对应的结构体
 1.日    期: 2014年11月28日
   作    者: w00281933
   修改内容: 新增
*****************************************************************************/
typedef NAS_MSCC_PIF_LMM_CELL_SIGN_INFO_REPORT_IND_STRU MSCC_MMA_LMM_CELL_SIGN_INFO_REPORT_IND_STRU;

/*****************************************************************************
 结构名    : MMA_MSCC_START_REQ_STRU
 结构说明  : mma给mscc发送开机请求的消息结构
 1.日    期   : 2013年3月25日
   作    者   : z00161729
   修改内容   : 新建
 2.日    期   : 2014年2月8日
   作    者   : s00246516
   修改内容   : L-C互操作项目:增加异系统到HRPD的处理
 3.日    期   : 2015年5月122日
   作    者   : W00176964
   修改内容   : CDMA Iteration 10 modified
*****************************************************************************/
typedef struct
{
    MSCC_MSG_HEADER_STRU                                    MsgHeader;          /*_H2ASN_Skip*//* 消息头                                   */
    NAS_MSCC_PIF_CARD_STATUS_ENUM_UINT8                     enUsimStatus;
    NAS_MSCC_PIF_CARD_STATUS_ENUM_UINT8                     enCsimStatus;
    NAS_MSCC_PIF_ALLOWED_REG_DOMAIN_ENUM_UINT8              enRegDomain;        /* 在原接口新增开机允许注册的服务域 */
    NAS_MSCC_PIF_REG_CONTROL_ENUM_UINT8                     enRegCtrl;
    NAS_MSCC_PIF_RAT_PRIO_STRU                              stRatPrio;
    VOS_UINT8                                               aucImsi[NAS_MAX_IMSI_LENGTH];
    NAS_MSCC_PIF_CALL_MODE_ENUM_UINT8                       enCallMode;
    VOS_UINT8                                               ucIsCardChanged;    /* 卡的ICCID是否发生变化的标识 */
    VOS_UINT8                                               aucReserved[1];
}MMA_MSCC_START_REQ_STRU;

/*****************************************************************************
 结构名    : MSCC_MMA_START_CNF_STRU
 结构说明  : mscc给mma发送开机结果的消息结构
 1.日    期   : 2013年3月25日
   作    者   : z00161729
   修改内容   : 新建
*****************************************************************************/
typedef NAS_MSCC_PIF_START_CNF_STRU MSCC_MMA_START_CNF_STRU;

/*****************************************************************************
 结构名    : MSCC_MMA_3GPP_SYS_INFO_IND_STRU
 结构说明  : mscc给mma发送系统消息的消息结构
 1.日    期   : 2013年3月25日
   作    者   : z00161729
   修改内容   : 新建
 2.日    期   : 2013年11月25日
   作    者   : z00161729
   修改内容   : SVLTE优化G-TL ps切换性能修改
 3.日    期   : 2013年10月16日
   作    者   : w00176964
   修改内容   : VoLTE_PhaseII 项目:增加漫游信息参数
 4.日    期   : 2014年01月17日
   作    者   : l00198894
   修改内容   : V9R1C53 C+L 离网重选项目
 5.日    期   : 2014年2月20日
   作    者   : z00161729
   修改内容   : DTS2014022100125:单待驻留g的网络，切双待后tl无网络限制驻留g的网络，
               available超时做list搜网构造搜网列表把last rplmn rat排在最前面导致g排在第一个
               无法回l或tds的网络
 6.日    期   : 2014年2月8日
   作    者   : s00246516
   修改内容   : L-C互操作项目:增加异系统到HRPD的处理

*****************************************************************************/
typedef NAS_MSCC_PIF_3GPP_SYS_INFO_IND_STRU MSCC_MMA_3GPP_SYS_INFO_IND_STRU;

/*****************************************************************************
 结构名    : MSCC_MMA_REG_RESULT_IND_STRU
 结构说明  : mscc给mma发送拒绝原因值消息的消息结构
 1.日    期   : 2013年8月15日
   作    者   : l00208543
   修改内容   : 新建
 2.日    期   : 2013年12月13日
   作    者   : w00176964
   修改内容   : Volte_PhaseIII 项目:修改结构名
*****************************************************************************/
typedef NAS_MSCC_PIF_REG_RESULT_IND_STRU MSCC_MMA_REG_RESULT_IND_STRU;

/*****************************************************************************
 结构名    : MSCC_MMA_USIM_AUTH_FAIL_IND_STRU
 结构说明  : mscc给mma发送USIM鉴权失败原因值消息的消息结构
 1.日    期   : 2013年11月15日
   作    者   : m00217266
   修改内容   : 新建
*****************************************************************************/
typedef NAS_MSCC_PIF_USIM_AUTH_FAIL_IND_STRU MSCC_MMA_USIM_AUTH_FAIL_IND_STRU;

/*****************************************************************************
 结构名    : MSCC_MMA_SERVICE_STATUS_IND_STRU
 结构说明  : mscc给mma发送注册状态和服务状态的消息结构
 1.日    期   : 2013年3月25日
   作    者   : z00161729
   修改内容   : 新建
 2.日    期   : 2013年11月20日
   作    者   : w00176964
   修改内容   : Volte PhaseII项目修改:增加CSPS的SIM卡状态
*****************************************************************************/
typedef NAS_MSCC_PIF_SERVICE_STATUS_IND_STRU MSCC_MMA_SERVICE_STATUS_IND_STRU;

/*****************************************************************************
 结构名    : MSCC_MMA_MM_INFO_IND_STRU
 结构说明  : mscc给mma发送MM INFORMATION的消息结构
 1.日    期   : 2013年3月25日
   作    者   : z00161729
   修改内容   : 新建
*****************************************************************************/
typedef NAS_MSCC_PIF_MM_INFO_IND_STRU MSCC_MMA_MM_INFO_IND_STRU;

/*****************************************************************************
 结构名    : MMA_MSCC_SIGN_REPORT_REQ_STRU
 结构说明  : mma给mscc发送信号上报配置的消息结构
 1.日    期   : 2013年3月25日
   作    者   : z00161729
   修改内容   : 新建
*****************************************************************************/
typedef NAS_MSCC_PIF_SIGN_REPORT_REQ_STRU MMA_MSCC_SIGN_REPORT_REQ_STRU;

/*****************************************************************************
 结构名    : MMA_MSCC_MODE_CHANGE_REQ_STRU
 结构说明  : mma给mscc发送模式变更的消息结构
 1.日    期   : 2013年3月25日
   作    者   : z00161729
   修改内容   : 新建
*****************************************************************************/
typedef NAS_MSCC_PIF_MODE_CHANGE_REQ_STRU MMA_MSCC_MODE_CHANGE_REQ_STRU;

/*****************************************************************************
 结构名    : MMA_MSCC_ATTACH_REQ_STRU
 结构说明  : mma给mscc发送attach 请求的消息结构
 1.日    期   : 2013年3月25日
   作    者   : z00161729
   修改内容   : 新建
 2.日    期   : 2014年2月8日
   作    者   : s00246516
   修改内容   : L-C互操作项目:增加异系统到HRPD的处理
*****************************************************************************/
typedef NAS_MSCC_PIF_ATTACH_REQ_STRU MMA_MSCC_ATTACH_REQ_STRU;

/*****************************************************************************
 结构名    : MSCC_MMA_ATTACH_CNF_STRU
 结构说明  : mscc给mma发送attach 结果的消息结构
 1.日    期   : 2013年3月25日
   作    者   : z00161729
   修改内容   : 新建
*****************************************************************************/
typedef NAS_MSCC_PIF_ATTACH_CNF_STRU MSCC_MMA_ATTACH_CNF_STRU;

/*****************************************************************************
 结构名    : MMA_MSCC_DETACH_REQ_STRU
 结构说明  : mma给mscc发送detach请求的消息结构
 1.日    期   : 2013年3月25日
   作    者   : z00161729
   修改内容   : 新建
 2.日    期   : 2014年2月8日
   作    者   : s00246516
   修改内容   : L-C互操作项目:增加异系统到HRPD的处理
*****************************************************************************/
typedef NAS_MSCC_PIF_DETACH_REQ_STRU MMA_MSCC_DETACH_REQ_STRU;

/*****************************************************************************
 结构名    : MSCC_MMA_DETACH_CNF_STRU
 结构说明  : mscc给mma发送detach结果的消息结构
 1.日    期   : 2013年3月25日
   作    者   : z00161729
   修改内容   : 新建
*****************************************************************************/
typedef NAS_MSCC_PIF_DETACH_CNF_STRU MSCC_MMA_DETACH_CNF_STRU;

/*****************************************************************************
 结构名    : MSCC_MMA_DETACH_IND_STRU
 结构说明  : mscc给mma发送网络detach结果的消息结构
 1.日    期   : 2013年3月25日
   作    者   : z00161729
   修改内容   : 新建
 2.日    期   : 2014年4月1日
   作    者   : z00161729
   修改内容   : DTS2014040300125:service 被拒和网络detach ind被拒需要上报^rejinfo
*****************************************************************************/
typedef NAS_MSCC_PIF_DETACH_IND_STRU MSCC_MMA_DETACH_IND_STRU;

/*****************************************************************************
 结构名    : MMA_MSCC_PLMN_LIST_REQ_STRU
 结构说明  : mma给mscc发送list请求的消息结构
 1.日    期   : 2013年3月25日
   作    者   : z00161729
   修改内容   : 新建
*****************************************************************************/
typedef NAS_MSCC_PIF_PLMN_LIST_REQ_STRU MMA_MSCC_PLMN_LIST_REQ_STRU;

/*****************************************************************************
 结构名    : MSCC_MMA_PLMN_LIST_CNF_STRU
 结构说明  : mscc给mma发送list搜网结果的消息结构
 1.日    期   : 2013年3月25日
   作    者   : z00161729
   修改内容   : 新建
*****************************************************************************/
typedef NAS_MSCC_PIF_PLMN_LIST_CNF_STRU MSCC_MMA_PLMN_LIST_CNF_STRU;

/*****************************************************************************
 结构名    : MSCC_MMA_PLMN_LIST_REJ_STRU
 结构说明  : mscc给mma发送list搜网被接入层reject的消息结构
 1.日    期   : 2013年3月25日
   作    者   : z00161729
   修改内容   : 新建
*****************************************************************************/
typedef NAS_MSCC_PIF_PLMN_LIST_REJ_STRU MSCC_MMA_PLMN_LIST_REJ_STRU;

/*****************************************************************************
 结构名    : MMA_MSCC_PLMN_LIST_ABORT_REQ_STRU
 结构说明  : mma给mscc发送list搜网中止的消息结构
 1.日    期   : 2013年3月25日
   作    者   : z00161729
   修改内容   : 新建
*****************************************************************************/
typedef NAS_MSCC_PIF_PLMN_LIST_ABORT_REQ_STRU MMA_MSCC_PLMN_LIST_ABORT_REQ_STRU;

/*****************************************************************************
 结构名    : MMA_MSCC_PLMN_USER_RESEL_REQ_STRU
 结构说明  : mma给mscc发送用户重选搜网请求的消息结构
 1.日    期   : 2013年3月25日
   作    者   : z00161729
   修改内容   : 新建
*****************************************************************************/
typedef NAS_MSCC_PIF_PLMN_USER_RESEL_REQ_STRU MMA_MSCC_PLMN_USER_RESEL_REQ_STRU;

/*****************************************************************************
 结构名    : MMA_MSCC_PLMN_SPECIAL_REQ_STRU
 结构说明  : mma给mscc发送用户指定搜网请求的消息结构
 1.日    期   : 2013年3月25日
   作    者   : z00161729
   修改内容   : 新建
*****************************************************************************/
typedef NAS_MSCC_PIF_PLMN_SPECIAL_REQ_STRU MMA_MSCC_PLMN_SPECIAL_REQ_STRU;


/*****************************************************************************
 结构名    : MSCC_MMA_COVERAGE_AREA_IND_STRU
 结构说明  : mscc给mma发送进覆盖区还是离开覆盖区指示的消息结构
 1.日    期   : 2013年3月25日
   作    者   : z00161729
   修改内容   : 新建
*****************************************************************************/
typedef NAS_MSCC_PIF_COVERAGE_AREA_IND_STRU MSCC_MMA_COVERAGE_AREA_IND_STRU;

/*****************************************************************************
 结构名    : MMA_MSCC_POWER_OFF_REQ_STRU
 结构说明  : mma给mscc发送关机请求的消息结构
 1.日    期   : 2013年3月25日
   作    者   : z00161729
   修改内容   : 新建
*****************************************************************************/
typedef NAS_MSCC_PIF_POWER_OFF_REQ_STRU MMA_MSCC_POWER_OFF_REQ_STRU;

/*****************************************************************************
 结构名    : MSCC_MMA_POWER_OFF_CNF_STRU
 结构说明  : mscc给mma发送关机回复的消息结构
 1.日    期   : 2013年3月25日
   作    者   : z00161729
   修改内容   : 新建
*****************************************************************************/
typedef NAS_MSCC_PIF_POWER_OFF_CNF_STRU MSCC_MMA_POWER_OFF_CNF_STRU;

/*****************************************************************************
 结构名    : MSCC_MMA_SRCHED_PLMN_INFO_IND_STRU
 结构说明  : mscc给mma发送srched plmn的消息结构
 1.日    期   : 2015年9月1日
   作    者   : h00285180
   修改内容   : 新建
*****************************************************************************/
typedef NAS_MSCC_PIF_SRCHED_PLMN_INFO_IND_STRU MSCC_MMA_SRCHED_PLMN_INFO_IND_STRU;


typedef NAS_MSCC_PIF_SYSTEM_ACQUIRE_CNF_STRU MSCC_MMA_SYSTEM_ACQUIRE_CNF_STRU;

/*****************************************************************************
 结构名    : MSCC_MMA_PLMN_SPECIAL_SEL_CNF_STRU
 结构说明  : mscc给mma发送用户指定搜网回复的消息结构
 1.日    期   : 2013年3月25日
   作    者   : z00161729
   修改内容   : 新建
*****************************************************************************/
typedef NAS_MSCC_PIF_PLMN_SPECIAL_SEL_CNF_STRU MSCC_MMA_PLMN_SPECIAL_SEL_CNF_STRU;

/*****************************************************************************
 结构名    : MSCC_MMA_PLMN_RESEL_CNF_STRU
 结构说明  : mscc给mma发送at+cops=0回复的消息结构
 1.日    期   : 2013年3月25日
   作    者   : z00161729
   修改内容   : 新建
*****************************************************************************/
typedef NAS_MSCC_PIF_PLMN_RESEL_CNF_STRU MSCC_MMA_PLMN_RESEL_CNF_STRU;

/*****************************************************************************
 结构名    : MSCC_MMA_DATATRAN_ATTRI_IND_STRU
 结构说明  : mscc给mma发送pdp激活情况的消息结构
 1.日    期   : 2013年3月25日
   作    者   : z00161729
   修改内容   : 新建
*****************************************************************************/
typedef NAS_MSCC_PIF_DATATRAN_ATTRI_IND_STRU MSCC_MMA_DATATRAN_ATTRI_IND_STRU;

/*****************************************************************************
 结构名    : MMA_MSCC_SYS_CFG_SET_REQ_STRU
 结构说明  : mma给mscc发送syscfg设置请求的消息结构
 1.日    期   : 2013年3月25日
   作    者   : z00161729
   修改内容   : 新建
*****************************************************************************/
typedef NAS_MSCC_PIF_SYS_CFG_SET_REQ_STRU MMA_MSCC_SYS_CFG_SET_REQ_STRU;

/*****************************************************************************
 结构名    : MSCC_MMA_SYS_CFG_SET_CNF_STRU
 结构说明  : mscc给mma发送syscfg设置结果的消息结构
 1.日    期   : 2013年3月25日
   作    者   : z00161729
   修改内容   : 新建
*****************************************************************************/
typedef NAS_MSCC_PIF_SYS_CFG_SET_CNF_STRU MSCC_MMA_SYS_CFG_SET_CNF_STRU;

/*****************************************************************************
 结构名    : MMA_MSCC_PLMN_SEARCH_REQ_STRU
 结构说明  : mma给mscc发送搜网请求的消息结构
 1.日    期   : 2013年3月25日
   作    者   : z00161729
   修改内容   : 新建
*****************************************************************************/
typedef NAS_MSCC_PIF_PLMN_SEARCH_REQ_STRU MMA_MSCC_PLMN_SEARCH_REQ_STRU;


/*****************************************************************************
 结构名    : NAS_MSCC_PIF_PLMN_SELECTION_RLST_IND_STRU
 结构说明  : mmc给mma发送搜网结果的消息结构
 1.日    期   : 2013年3月25日
   作    者   : z00161729
   修改内容   : 新建
*****************************************************************************/
typedef struct
{
    MSG_HEADER_STRU                                         stMsgHeader;        /*_H2ASN_Skip*//* 消息头    */
    MSCC_MMA_ACQ_SYS_TYPE_ENUM_UINT32                       enAcqSysType;
    MSCC_MMA_SYSTEM_ACQUIRE_RESULT_ENUM_UINT32              enResult;
}MSCC_MMA_SYSTEM_ACQUIRE_IND_STRU;


/*****************************************************************************
 结构名    : MSCC_MMA_SYSTEM_ACQUIRE_END_IND_STRU
 结构说明  : mmc给mma发送搜网结果的消息结构
 1.日    期   : 2013年3月25日
   作    者   : z00161729
   修改内容   : 新建
*****************************************************************************/
typedef struct
{
    MSCC_MSG_HEADER_STRU                                    stMsgHeader;        /*_H2ASN_Skip*//* 消息头    */
    MSCC_MMA_ACQ_SYS_TYPE_ENUM_UINT32                       enAcqSysType;
    MSCC_MMA_SYSTEM_ACQUIRE_RESULT_ENUM_UINT32              enResult;
    MSCC_MMA_CL_SYSTEM_ACQUIRE_RESULT_TYPE_ENUM_UINT32      enAcqRsltType;    /* 指示系统类型为DO_LTE时系统捕获时,捕获结果类型是失败,HRPD成功还是LTE成功 */
}MSCC_MMA_SYSTEM_ACQUIRE_END_IND_STRU;




/*****************************************************************************
 结构名    : MSCC_MMA_PLMN_LIST_ABORT_CNF_STRU
 结构说明  : mscc给mma发送list搜网中止回复的消息结构
 1.日    期   : 2013年3月25日
   作    者   : z00161729
   修改内容   : 新建
*****************************************************************************/
typedef NAS_MSCC_PIF_PLMN_LIST_ABORT_CNF_STRU MSCC_MMA_PLMN_LIST_ABORT_CNF_STRU;

/*****************************************************************************
 结构名    : MMA_MSCC_SPEC_PLMN_SEARCH_ABORT_REQ_STRU
 结构说明  : mma给mscc发送指定搜网中止请求的消息结构
 1.日    期   : 2013年3月25日
   作    者   : z00161729
   修改内容   : 新建
*****************************************************************************/
typedef NAS_MSCC_PIF_SPEC_PLMN_SEARCH_ABORT_REQ_STRU MMA_MSCC_SPEC_PLMN_SEARCH_ABORT_REQ_STRU;

/*****************************************************************************
 结构名    : MSCC_MMA_SPEC_PLMN_SEARCH_ABORT_CNF_STRU
 结构说明  : mscc给mma发送中止指定搜网回复的消息结构
 1.日    期   : 2013年3月25日
   作    者   : z00161729
   修改内容   : 新建
*****************************************************************************/
typedef NAS_MSCC_PIF_SPEC_PLMN_SEARCH_ABORT_CNF_STRU MSCC_MMA_SPEC_PLMN_SEARCH_ABORT_CNF_STRU;

/*****************************************************************************
 结构名    : MSCC_MMA_UMTS_CIPHER_INFO_IND_STRU
 结构说明  : mscc给mma上报W的cipher信息的消息结构
 1.日    期   : 2013年3月25日
   作    者   : z00161729
   修改内容   : 新建
*****************************************************************************/
typedef NAS_MSCC_PIF_UMTS_CIPHER_INFO_IND_STRU MSCC_MMA_UMTS_CIPHER_INFO_IND_STRU;

/*****************************************************************************
 结构名    : MSCC_MMA_GPRS_CIPHER_INFO_IND_STRU
 结构说明  : mscc给mma上报G的cipher信息的消息结构
 1.日    期   : 2013年3月25日
   作    者   : z00161729
   修改内容   : 新建
*****************************************************************************/
typedef NAS_MSCC_PIF_GPRS_CIPHER_INFO_IND_STRU MSCC_MMA_GPRS_CIPHER_INFO_IND_STRU;

/*****************************************************************************
 结构名    : MSCC_MMA_PLMN_SPECIAL_SEL_REJ_STRU
 结构说明  : mscc给MMA发送用户指定搜拒绝结果的消息结构
 1.日    期   : 2013年3月25日
   作    者   : z00161729
   修改内容   : 新建
*****************************************************************************/
typedef NAS_MSCC_PIF_PLMN_SPECIAL_SEL_REJ_STRU MSCC_MMA_PLMN_SPECIAL_SEL_REJ_STRU;

/*****************************************************************************
 结构名    : MSCC_MMA_AC_INFO_CHANGE_IND_STRU
 结构说明  : MSCC给MMA发送小区接入信息变化指示的消息结构
 1.日    期   : 2013年3月25日
   作    者   : z00161729
   修改内容   : 新建
*****************************************************************************/
typedef NAS_MSCC_PIF_AC_INFO_CHANGE_IND_STRU MSCC_MMA_AC_INFO_CHANGE_IND_STRU;

/*******************************************************************************
 结构名    : MMA_MSCC_OM_MAINTAIN_INFO_IND_STRU
 结构说明  : MMA_MSCC_OM_MAINTAIN_INFO_IND_STRU消息结构
 1.日    期  : 2013年04月16日
   作    者  : z00161729
   修改内容  : 新增结构
*******************************************************************************/
typedef NAS_MSCC_PIF_OM_MAINTAIN_INFO_IND_STRU MMA_MSCC_OM_MAINTAIN_INFO_IND_STRU;

/*****************************************************************************
 结构名    : MMA_MSCC_UPDATE_UPLMN_NTF_STRU
 结构说明  : mma给mscc发送UPLMN更新通知的消息结构
 1.日    期   : 2013年7月31日
   作    者   : w00167002
   修改内容   : 新建结构体
*****************************************************************************/
typedef NAS_MSCC_PIF_UPDATE_UPLMN_NTF_STRU MMA_MSCC_UPDATE_UPLMN_NTF_STRU;

/*****************************************************************************
 结构名    : MMA_MSCC_EOPLMN_SET_REQ_STRU
 结构说明  : AT和MMA的EOPLMN设置接口
 1.日    期  : 2013年10月15日
   作    者  : s00190137
   修改内容  : 新增结构
 2.日    期  : 2013年11月26日
   作    者  : s00190137
   修改内容  : 添加分组机制，单组允许最大设置50个OPLMN
*****************************************************************************/
typedef NAS_MSCC_PIF_EOPLMN_SET_REQ_STRU MMA_MSCC_EOPLMN_SET_REQ_STRU;

/*****************************************************************************
 结构名    : MSCC_MMA_EOPLMN_SET_CNF_STRU
 结构说明  : mscc给mma发送AT^EOPLMN设置回复的消息结构
 1.日    期   : 2013年10月15日
   作    者   : x65241
   修改内容   : 新建
*****************************************************************************/
typedef NAS_MSCC_PIF_EOPLMN_SET_CNF_STRU MSCC_MMA_EOPLMN_SET_CNF_STRU;

/*****************************************************************************
 结构名    : MSCC_MMA_EOPLMN_SET_ABORT_STRU
 结构说明  : AT^EOPLMN设置超时通知MSCC中断消息处理的结构
 1.日    期   : 2013年10月15日
   作    者   : x65241
   修改内容   : 新建
*****************************************************************************/
typedef NAS_MSCC_PIF_EOPLMN_SET_ABORT_STRU MSCC_MMA_EOPLMN_SET_ABORT_STRU;

/*****************************************************************************
 结构名    : MMA_MSCC_NET_SCAN_REQ_STRU
 结构说明  : MMA和MSCC的NETSCAN设置接口
 1.日    期  : 2013年10月10日
   作    者  : w00242748
   修改内容  : 新增结构
*****************************************************************************/
typedef NAS_MSCC_PIF_NET_SCAN_REQ_STRU MMA_MSCC_NET_SCAN_REQ_STRU;

/*****************************************************************************
 结构名    : MSCC_MMA_NET_SCAN_INFO_STRU
 结构说明  : 扫描某个频点的网络信息
 1.日    期   : 2013年8月24日
   作    者   : w00242748
   修改内容   : 新建
*****************************************************************************/
typedef NAS_MSCC_PIF_NET_SCAN_INFO_STRU MSCC_MMA_NET_SCAN_INFO_STRU;

/*****************************************************************************
 结构名    : MSCC_MMA_NET_SCAN_CNF_STRU
 结构说明  : MSCC上报给MMA的NETSCAN CNF接口
 1.日    期  : 2013年10月10日
   作    者  : w00242748
   修改内容  : 新增结构
*****************************************************************************/
typedef NAS_MSCC_PIF_NET_SCAN_CNF_STRU MSCC_MMA_NET_SCAN_CNF_STRU;

/*****************************************************************************
 结构名    : MSCC_MMA_SERV_REJ_IND_STRU
 结构说明  : mscc给mma发送服务被拒的消息结构
 1.日    期   : 2014年4月1日
   作    者   : z00161729
   修改内容   : 新建
*****************************************************************************/
typedef NAS_MSCC_PIF_SERV_REJ_IND_STRU MSCC_MMA_SERV_REJ_IND_STRU;


/*****************************************************************************
 结构名    : MMA_MSCC_ABORT_NET_SCAN_REQ_STRU
 结构说明  : MMA和MSCC的NETSCAN设置接口
 1.日    期  : 2013年10月10日
   作    者  : w00242748
   修改内容  : 新增结构
*****************************************************************************/
typedef NAS_MSCC_PIF_ABORT_NET_SCAN_REQ_STRU MMA_MSCC_ABORT_NET_SCAN_REQ_STRU;

/*****************************************************************************
 结构名    : MSCC_MMA_ABORT_NET_SCAN_CNF_STRU
 结构说明  : MSCC上报给MMA的NETSCAN CNF接口
 1.日    期  : 2013年10月10日
   作    者  : w00242748
   修改内容  : 新增结构
*****************************************************************************/
typedef NAS_MSCC_PIF_ABORT_NET_SCAN_CNF_STRU MSCC_MMA_ABORT_NET_SCAN_CNF_STRU;

/* Added by y00245242 for VoLTE_PhaseI  项目, 2013-7-9, begin */
/*******************************************************************************
 结构名    : MSCC_MMA_NETWORK_CAPABILITY_INFO_IND_STRU
 结构说明  : 通知网络业务信息能力消息
 1.日    期  : 2013年7月9日
   作    者  : y00245242
   修改内容  : 新增结构
*******************************************************************************/
typedef NAS_MSCC_PIF_NETWORK_CAPABILITY_INFO_IND_STRU MSCC_MMA_NETWORK_CAPABILITY_INFO_IND_STRU;
/* Added by y00245242 for VoLTE_PhaseI  项目, 2013-7-9, end */

/* Added by w00176964 for VoLTE_PhaseII 项目, 2013-10-12, begin */
/*****************************************************************************
 结构名    : MSCC_MMA_CAMP_ON_IND_STRU
 结构说明  : MSCC发给MMA的驻留消息结构
 1.日    期   : 2013年10月12日
   作    者   : w00176964
   修改内容   : 新建结构体
*****************************************************************************/
typedef NAS_MSCC_PIF_CAMP_ON_IND_STRU_STRU MSCC_MMA_CAMP_ON_IND_STRU_STRU;
/* Added by w00176964 for VoLTE_PhaseII 项目, 2013-10-12, end */

/*****************************************************************************
 结构名    : MMA_MSCC_OTHER_MODEM_INFO_NOTIFY_STRU
 结构说明  : modem1的信息目前只有驻留信息
 1.日    期   : 2013年11月23日
   作    者   : z00161729
   修改内容   : 新建
 2.日    期   : 2013年12月24日
   作    者   : z00161729
   修改内容   : SVLTE支持NCELL搜网
*****************************************************************************/
typedef NAS_MSCC_PIF_OTHER_MODEM_INFO_NOTIFY_STRU MMA_MSCC_OTHER_MODEM_INFO_NOTIFY_STRU;

/*****************************************************************************
 结构名    : MMA_MSCC_OTHER_MODEM_DPLMN_NPLMN_INFO_NOTIFY_STRU
 结构说明  : modem1的dplmn/nplmn信息
 1.日    期   : 2014年11月3日
   作    者   : z00161729
   修改内容   : 开机漫游搜网项目修改

*****************************************************************************/
typedef NAS_MSCC_PIF_OTHER_MODEM_DPLMN_NPLMN_INFO_NOTIFY_STRU MMA_MSCC_OTHER_MODEM_DPLMN_NPLMN_INFO_NOTIFY_STRU;

/*******************************************************************************
 结构名    : MMA_MSCC_TDS_NCELL_INFO_STRU
 结构说明  : GSM下的TDS频点列表

 1.日    期   : 2013年12月24日
   作    者   : z00161729
   修改内容   : SVLTE支持NCELL搜网

*******************************************************************************/
typedef NAS_MSCC_PIF_TDS_NCELL_INFO_STRU MMA_MSCC_TDS_NCELL_INFO_STRU;

/*******************************************************************************
 结构名    : MMA_MSCC_LTE_NCELL_INFO_STRU
 结构说明  : GSM下的LTE频点列表

 1.日    期   : 2013年12月24日
   作    者   : z00161729
   修改内容   : SVLTE支持NCELL搜网

*******************************************************************************/
typedef NAS_MSCC_PIF_LTE_NCELL_INFO_STRU MMA_MSCC_LTE_NCELL_INFO_STRU;

/*******************************************************************************
 结构名    : MMA_MSCC_NCELL_INFO_NOTIFY_STRU
 结构说明  : ID_MMA_MSCC_NCELL_INFO_NOTIFY消息对应的结构，
             包括GSM下的TDS/LTE邻区结构中的TDS/LTE的频点列表

 1.日    期   : 2013年12月23日
   作    者   : z00161729
   修改内容   : 新生成结构

*******************************************************************************/
typedef NAS_MSCC_PIF_NCELL_INFO_NOTIFY_STRU MMA_MSCC_NCELL_INFO_NOTIFY_STRU;

/*****************************************************************************
 结构名    : MSCC_MMA_EPLMN_INFO_IND_STRU
 结构说明  : 等效plmn信息
 1.日    期   : 2013年12月23日
   作    者   : z00161729
   修改内容   : 新建
*****************************************************************************/
typedef NAS_MSCC_PIF_EPLMN_INFO_IND_STRU MSCC_MMA_EPLMN_INFO_IND_STRU;

/*****************************************************************************
 结构名    : MSCC_MMA_CS_SERVICE_CONN_STATUS_IND_STRU
 结构说明  : mscc上报cs业务信令连接状态指示消息结构
 1.日    期   : 2014年3月4日
   作    者   : z00161729
   修改内容   : 新建
*****************************************************************************/
typedef NAS_MSCC_PIF_CS_SERVICE_CONN_STATUS_IND_STRU MSCC_MMA_CS_SERVICE_CONN_STATUS_IND_STRU;

/*******************************************************************************
结构名    : MMA_MSCC_PS_TRANSFER_NOTIFY_STRU
结构说明  : ID_MMA_MSCC_PS_TRANSFER_NOTIFY消息结构
1.日    期   : 2014年1月5日
  作    者   : z00161729
  修改内容   : 新建
2.日    期   : 2014年01月17日
  作    者   : l00198894
  修改内容   : V9R1C53 C+L 离网重选项目
*******************************************************************************/
typedef NAS_MSCC_PIF_PS_TRANSFER_NOTIFY_STRU MMA_MSCC_PS_TRANSFER_NOTIFY_STRU;

/* Added by w00176964 for VoLTE_PhaseIII 项目, 2013-12-10, begin */
/*****************************************************************************
 结构名    : MMA_MSCC_IMS_VOICE_CAP_NOTIFY_STRU
 结构说明  : MMA通知MSCC当前IMS VOICE是否可用的消息
 1.日    期   : 2013年12月10日
   作    者   : w00176964
   修改内容   : 新建
*****************************************************************************/
typedef NAS_MSCC_PIF_IMS_VOICE_CAP_NOTIFY_STRU MMA_MSCC_IMS_VOICE_CAP_NOTIFY_STRU;
/* Added by w00176964 for VoLTE_PhaseIII 项目, 2013-12-10, end */

/* Added by s00246516 for L-C互操作项目, 2014-01-26, Begin */
/*****************************************************************************
 结构名    : MMA_MSCC_ACQ_REQ_STRU
 结构说明  : 获取消息的结构体
 1.日    期   : 2014年1月26日
   作    者   : s00246516
   修改内容   : 新建
*****************************************************************************/
typedef NAS_MSCC_PIF_ACQ_REQ_STRU MMA_MSCC_ACQ_REQ_STRU;

/*****************************************************************************
 结构名    : MSCC_MMA_ACQ_CNF_STRU
 结构说明  : 获取结果的结构体
 1.日    期   : 2014年1月26日
   作    者   : s00246516
   修改内容   : 新建
*****************************************************************************/
typedef NAS_MSCC_PIF_ACQ_CNF_STRU MSCC_MMA_ACQ_CNF_STRU;

/*****************************************************************************
 结构名    : MMA_MSCC_REG_CELL_INFO_STRU
 结构说明  : 注册消息中Cell Info的结构体
 1.日    期   : 2014年1月26日
   作    者   : s00246516
   修改内容   : 新建
*****************************************************************************/
typedef NAS_MSCC_PIF_REG_CELL_INFO_STRU MMA_MSCC_REG_CELL_INFO_STRU;

/*****************************************************************************
 结构名    : MMA_MSCC_REG_REQ_STRU
 结构说明  : 注册消息的结构体
 1.日    期   : 2014年1月26日
   作    者   : s00246516
   修改内容   : 新建
*****************************************************************************/
typedef NAS_MSCC_PIF_REG_REQ_STRU MMA_MSCC_REG_REQ_STRU;

/*****************************************************************************
 结构名    : MSCC_MMA_REG_CNF_STRU
 结构说明  : 注册结果的结构体
 1.日    期   : 2014年1月26日
   作    者   : s00246516
   修改内容   : 新建
*****************************************************************************/
typedef NAS_MSCC_PIF_REG_CNF_STRU MSCC_MMA_REG_CNF_STRU;

/*****************************************************************************
 结构名    : MMA_MSCC_POWER_SAVE_REQ_STRU
 结构说明  : Power save消息的结构体
 1.日    期   : 2014年1月26日
   作    者   : s00246516
   修改内容   : 新建
*****************************************************************************/
typedef NAS_MSCC_PIF_POWER_SAVE_REQ_STRU MMA_MSCC_POWER_SAVE_REQ_STRU;

/*****************************************************************************
 结构名    : MSCC_MMA_POWER_SAVE_CNF_STRU
 结构说明  : Power save结果的结构体
 1.日    期   : 2014年1月26日
   作    者   : s00246516
   修改内容   : 新建
*****************************************************************************/
typedef NAS_MSCC_PIF_POWER_SAVE_CNF_STRU MSCC_MMA_POWER_SAVE_CNF_STRU;

/*****************************************************************************
 结构名    : MSCC_MMA_ACQ_IND_STRU
 结构说明  : 获取指示的结构体
 1.日    期   : 2014年1月26日
   作    者   : s00246516
   修改内容   : 新建
*****************************************************************************/
typedef  NAS_MSCC_PIF_ACQ_CNF_STRU MSCC_MMA_ACQ_IND_STRU;
/* Added by s00246516 for L-C互操作项目, 2014-01-26, End */

/* Add by s00217060 for K3V3 多模多天线特性, 2014-06-27, Begin */
/*****************************************************************************
 结构名    : MSCC_MMA_PS_SERVICE_CONN_STATUS_IND_STRU
 结构说明  : mscc上报ps业务信令连接状态指示消息结构
 1.日    期   : 2014年6月27日
   作    者   : s00217060
   修改内容   : 新建
*****************************************************************************/
typedef  NAS_MSCC_PIF_PS_SERVICE_CONN_STATUS_IND_STRU MSCC_MMA_PS_SERVICE_CONN_STATUS_IND_STRU;
/* Add by s00217060 for K3V3 多模多天线特性, 2014-06-27, end */

/*****************************************************************************
 结构名    : MSCC_MMA_RF_AVAILABLE_IND_STRU
 结构说明  : MSCC通知MMA当前是否有RF资源可用
 1.日    期   : 2014年6月30日
   作    者   : W00176964
   修改内容   : 新建
*****************************************************************************/
typedef NAS_MSCC_PIF_RF_AVAILABLE_IND_STRU MSCC_MMA_RF_AVAILABLE_IND_STRU;

/*****************************************************************************
 结构名    : MMA_MSCC_SRV_ACQ_REQ_STRU
 结构说明  : 业务触发搜网指示
 1.日    期   : 2014年5月28日
   作    者   : h00246512
   修改内容   : 新建
*****************************************************************************/
typedef NAS_MSCC_PIF_SRV_ACQ_REQ_STRU MMA_MSCC_SRV_ACQ_REQ_STRU;

/*****************************************************************************
 结构名    : MSCC_MMA_SRV_ACQ_CNF_STRU
 结构说明  : 业务触发搜网结果
 1.日    期   : 2014年5月28日
   作    者   : h00246512
   修改内容   : 新建
*****************************************************************************/
typedef NAS_MSCC_PIF_SRV_ACQ_CNF_STRU MSCC_MMA_SRV_ACQ_CNF_STRU;

/*****************************************************************************
 结构名    : MMA_MSCC_BEGIN_SESSION_NOTIFY_STRU
 结构说明  : 业务触发搜网开始指示
 1.日    期   : 2014年5月28日
   作    者   : h00246512
   修改内容   : 新建
*****************************************************************************/
typedef NAS_MSCC_PIF_BEGIN_SESSION_NOTIFY_STRU MMA_MSCC_BEGIN_SESSION_NOTIFY_STRU;

/*****************************************************************************
 结构名    : MMA_MSCC_END_SESSION_NOTIFY_STRU
 结构说明  : 业务触发搜网结束指示
 1.日    期   : 2014年5月28日
   作    者   : h00246512
   修改内容   : 新建
*****************************************************************************/
typedef NAS_MSCC_PIF_END_SESSION_NOTIFY_STRU MMA_MSCC_END_SESSION_NOTIFY_STRU;

/*****************************************************************************
 结构名    : MMA_MSCC_IMS_SRV_INFO_NOTIFY_STRU
 结构说明  : ID_MMA_MSCC_IMS_SRV_INFO_NOTIFY的结构体
 1.日    期   : 2014年11月06日
   作    者   : s00217060
   修改内容   : 新建
*****************************************************************************/
typedef NAS_MSCC_PIF_IMS_SRV_INFO_NOTIFY_STRU MMA_MSCC_IMS_SRV_INFO_NOTIFY_STRU;

/*****************************************************************************
 结构名    : MSCC_MMA_IMS_VOICE_CAP_NOTIFY
 结构说明  : ID_MSCC_MMA_IMS_VOICE_CAP_NOTIFY的结构体
 1.日    期   : 2015年01月27日
   作    者   : y00245242
   修改内容   : 新建
*****************************************************************************/
typedef NAS_MSCC_PIF_IMS_VOICE_CAP_NOTIFY_STRU MSCC_MMA_IMS_VOICE_CAP_IND_STRU;


typedef struct
{
    MSCC_MSG_HEADER_STRU                                    stMsgHeader;        /*_H2ASN_Skip*//* 消息头                                   */
    MSCC_MMA_HRPD_SERVICE_STATUS_ENUM_UINT32                enSrvSta;
    VOS_UINT8                                               ucIsNewSession;
    VOS_UINT8                                               ucIsEhrpdSupport;   /* 表示当前Session类型是HRPD或EHRPD，当enSrvSta为NORMAL_SERVICE时有效 */
    VOS_UINT8                                               aucReserved[2];
    MSCC_MMA_HRPD_SESSION_RELEASE_TYPE_ENUM_UINT32          enCurrSessionRelType;
} MSCC_MMA_HRPD_SERVICE_STATUS_IND_STRU;


typedef struct
{
    MSCC_MSG_HEADER_STRU                        stMsgHeader;                    /*_H2ASN_Skip*//* 消息头                                   */
    VOS_UINT16                                  usBandClass;
    VOS_UINT16                                  usFreq;
    VOS_UINT32                                  ulMcc;
    VOS_UINT8                                   ucUATIColorCode;
    VOS_UINT8                                   ucSubNetMask;
    VOS_UINT8                                   ucSecondaryColorCodeCount;
    VOS_UINT8                                   aucSecondaryColorCode[MSCC_MMA_SECOND_COLORCODE_MAX_LENGTH];
    VOS_UINT8                                   aucSectorId[MSCC_MMA_SUBNET_ID_MAX_LENGTH];
    VOS_INT32                                   lLongitude;
    VOS_INT32                                   lLatitude;
    VOS_UINT32                                  ulSector24;
} MSCC_MMA_HRPD_OVERHEAD_MSG_IND_STRU;


typedef struct
{
    MSCC_MSG_HEADER_STRU                                    stMsgHeader;        /*_H2ASN_Skip*//* 消息头                                   */
    MSCC_MMA_HRPD_SYS_ACQ_RSLT_ENUM_UINT32                  enSysAcqRslt;
} MSCC_MMA_HRPD_SYS_ACQ_CNF_STRU;


/*****************************************************************************
 结构名    : MMA_MSCC_CDMA_MO_CALL_START_NTF_STRU
 结构说明  : ID_MMA_MSCC_CDMA_MO_CALL_START_NTF的结构体
 1.日    期   : 2015年02月4日
   作    者   : h00246512
   修改内容   : 新建
*****************************************************************************/
typedef NAS_MSCC_PIF_CDMA_MO_CALL_START_NTF_STRU MMA_MSCC_CDMA_MO_CALL_START_NTF_STRU;




/*****************************************************************************
 结构名    : MMA_MSCC_CDMA_MO_CALL_REDIAL_SYS_ACQ_NTF_STRU
 结构说明  : ID_MMA_MSCC_CDMA_MO_CALL_REDIAL_SYS_ACQ_NTF的结构体
 1.日    期   : 2015年02月4日
   作    者   : h00246512
   修改内容   : 新建
*****************************************************************************/
typedef NAS_MSCC_PIF_CDMA_MO_CALL_REDIAL_SYS_ACQ_NTF_STRU MMA_MSCC_CDMA_MO_CALL_REDIAL_SYS_ACQ_NTF_STRU;

/*****************************************************************************
 结构名    : MMA_MSCC_CDMA_MO_CALL_SUCCESS_NTF_STRU
 结构说明  : ID_MMA_MSCC_CDMA_MO_CALL_SUCCESS_NTF的结构体
 1.日    期   : 2015年02月4日
   作    者   : h00246512
   修改内容   : 新建
*****************************************************************************/
typedef NAS_MSCC_PIF_CDMA_MO_CALL_SUCCESS_NTF_STRU MMA_MSCC_CDMA_MO_CALL_SUCCESS_NTF_STRU;


/*****************************************************************************
 结构名    : MMA_MSCC_CDMA_MO_CALL_END_NTF_STRU
 结构说明  : ID_MMA_MSCC_CDMA_MO_CALL_END_NTF的结构体
 1.日    期   : 2015年02月4日
   作    者   : h00246512
   修改内容   : 新建
*****************************************************************************/
typedef NAS_MSCC_PIF_CDMA_MO_CALL_END_NTF_STRU MMA_MSCC_CDMA_MO_CALL_END_NTF_STRU;

/*****************************************************************************
 结构名    : MMA_MSCC_CDMACSQ_SET_REQ_STRU
 结构说明  : ID_MMA_MSCC_CDMACSQ_SET_REQ的结构体
 1.日    期   : 2015年02月4日
   作    者   : h00246512
   修改内容   : 新建
*****************************************************************************/
typedef NAS_MSCC_PIF_CDMACSQ_SET_REQ_STRU MMA_MSCC_CDMACSQ_SET_REQ_STRU;

/*****************************************************************************
 结构名    : MMA_MSCC_CFREQ_LOCK_NTF_STRU
 结构说明  : ID_MMA_MSCC_CFREQ_LOCK_NTF的结构体
 1.日    期   : 2015年02月4日
   作    者   : h00246512
   修改内容   : 新建
*****************************************************************************/
typedef NAS_MSCC_PIF_CFREQ_LOCK_NTF_STRU MMA_MSCC_CFREQ_LOCK_NTF_STRU;

/*****************************************************************************
 结构名    : MSCC_MMA_1X_SYSTEM_TIME_IND_STRU
 结构说明  : ID_MSCC_MMA_1X_SYSTEM_TIME_IND消息的结构体
 1.日    期   : 2015年03月4日
   作    者   : L00256032
   修改内容   : 新建
*****************************************************************************/
typedef NAS_MSCC_PIF_1X_SYSTEM_TIME_IND_STRU MSCC_MMA_1X_SYSTEM_TIME_IND_STRU;

/*****************************************************************************
 结构名    : MMA_MSCC_1X_SYSTEM_SERVICE_INFO_IND_STRU
 结构说明  : ID_MSCC_MMA_1X_SYSTEM_SERVICE_INFO_IND消息的结构体
 1.日    期   : 2015年02月4日
   作    者   : h00246512
   修改内容   : 新建
*****************************************************************************/
typedef NAS_MSCC_PIF_1X_SYSTEM_SERVICE_INFO_IND_STRU MSCC_MMA_1X_SYSTEM_SERVICE_INFO_IND_STRU;

/*****************************************************************************
 结构名    : MSCC_MMA_CDMACSQ_SET_CNF_STRU
 结构说明  : ID_MSCC_MMA_CDMACSQ_SET_CNF消息的结构体
 1.日    期   : 2015年02月4日
   作    者   : h00246512
   修改内容   : 新建
*****************************************************************************/
typedef NAS_MSCC_PIF_CDMACSQ_SET_CNF_STRU MSCC_MMA_CDMACSQ_SET_CNF_STRU;

/*****************************************************************************
 结构名    : MSCC_MMA_CDMACSQ_IND_STRU
 结构说明  : ID_MSCC_MMA_CDMACSQ_SIGNAL_QUALITY_IND消息的结构体
 1.日    期   : 2015年02月4日
   作    者   : h00246512
   修改内容   : 新建
*****************************************************************************/
typedef NAS_MSCC_PIF_CDMACSQ_IND_STRU MSCC_MMA_CDMACSQ_IND_STRU;




/*****************************************************************************
 结构名    : MMA_MSCC_CFPLMN_SET_REQ_STRUS
 结构说明  : ID_MMA_MSCC_CPLMN_REQ的结构体
 1.日    期   : 2015年2月4日
   作    者   : f00279542
   修改内容   : 新建
*****************************************************************************/
typedef NAS_MSCC_PIF_CFPLMN_SET_REQ_STRU MMA_MSCC_CFPLMN_SET_REQ_STRU;

/*****************************************************************************
 结构名    : MMA_MSCC_CFPLMN_QUERY_REQ_STRU
 结构说明  : ID_MMA_MSCC_CPLMN_REQ的结构体
 1.日    期   : 2015年2月4日
   作    者   : f00279542
   修改内容   : 新建
*****************************************************************************/
typedef NAS_MSCC_PIF_CFPLMN_QUERY_REQ_STRU MMA_MSCC_CFPLMN_QUERY_REQ_STRU;

/*****************************************************************************
 结构名    : MSCC_MMA_CFPLMN_SET_CNF_STRU
 结构说明  : ID_MMA_MSCC_CPLMN_SET_CNF的结构体
 1.日    期   : 2015年2月4日
   作    者   : f00279542
   修改内容   : 新建
*****************************************************************************/
typedef NAS_MSCC_PIF_CFPLMN_SET_CNF_STRU MSCC_MMA_CFPLMN_SET_CNF_STRU;

/*****************************************************************************
 结构名    : MSCC_MMA_CFPLMN_QUERY_CNF_STRU
 结构说明  : ID_MMA_MSCC_CPLMN_QRY_CNF的结构体
 1.日    期   : 2015年2月4日
   作    者   : f00279542
   修改内容   : 新建
*****************************************************************************/
typedef NAS_MSCC_PIF_CFPLMN_QUERY_CNF_STRU MSCC_MMA_CFPLMN_QUERY_CNF_STRU;

/*****************************************************************************
 结构名    : MSCC_MMA_CFPLMN_OPERATE_TYPE_ENUM_UINT8
 结构说明  : 操作类型
 1.日    期   : 2015年2月4日
   作    者   : f00279542
   修改内容   : 新建
*****************************************************************************/
typedef NAS_MSCC_PIF_CFPLMN_OPERATE_TYPE_ENUM_UINT8 MSCC_MMA_CFPLMN_OPERATE_TYPE_ENUM_UINT8;


/*****************************************************************************
 结构名    : MMA_MSCC_PREF_PLMN_QUERY_REQ_STRU
 结构说明  : ID_MMA_MSCC_PREF_PLMN_QUERY_REQ的结构体
 1.日    期   : 2015年2月3日
   作    者   : y00307564
   修改内容   : 新建
*****************************************************************************/
typedef NAS_MSCC_PIF_PREF_PLMN_QUERY_REQ_STRU MMA_MSCC_PREF_PLMN_QUERY_REQ_STRU;

/*****************************************************************************
 结构名    : MSCC_MMA_PREF_PLMN_QUERY_CNF_STRU
 结构说明  : ID_MSCC_MMA_PREF_PLMN_QUERY_CNF的结构体
 1.日    期   : 2015年02月04日
   作    者   : y00245242
   修改内容   : 新建
*****************************************************************************/
typedef NAS_MSCC_PIF_PREF_PLMN_QUERY_CNF_STRU MSCC_MMA_PREF_PLMN_QUERY_CNF_STRU;

/*****************************************************************************
 结构名    : MMA_MSCC_PREF_PLMN_SET_REQ_STRU
 结构说明  : ID_MMA_MSCC_PREF_PLMN_SET_REQ的结构体
 1.日    期   : 2015年2月3日
   作    者   : y00307564
   修改内容   : 新建
*****************************************************************************/
typedef NAS_MSCC_PIF_PREF_PLMN_SET_REQ_STRU MMA_MSCC_PREF_PLMN_SET_REQ_STRU;

/*****************************************************************************
 结构名    : MSCC_MMA_PREF_PLMN_SET_CNF_STRU
 结构说明  : ID_MSCC_MMA_PREF_PLMN_SET_CNF的结构体
 1.日    期   : 2015年02月04日
   作    者   : y00245242
   修改内容   : 新建
*****************************************************************************/
typedef NAS_MSCC_PIF_PREF_PLMN_SET_CNF_STRU MSCC_MMA_PREF_PLMN_SET_CNF_STRU;

/*****************************************************************************
 结构名    : MMA_MSCC_VOICE_DOMAIN_CHANGE_IND_STRU
 结构说明  : ID_MMA_MSCC_VOICE_DOMAIN_CHANGE_IND的结构体
 1.日    期   : 2015年04月13日
   作    者   : f00179208
   修改内容   : 新建
*****************************************************************************/
typedef NAS_MSCC_PIF_VOICE_DOMAIN_CHANGE_IND_STRU MMA_MSCC_VOICE_DOMAIN_CHANGE_IND_STRU;

/*****************************************************************************
 结构名    : MMA_MSCC_IMS_START_REQ_STRU
 结构说明  : ID_MMA_MSCC_IMS_START_REQ的结构体
 1.日    期   : 2015年04月13日
   作    者   : f00179208
   修改内容   : 新建
*****************************************************************************/
typedef NAS_MSCC_PIF_IMS_START_REQ_STRU MMA_MSCC_IMS_START_REQ_STRU;

/*****************************************************************************
 结构名    : MSCC_MMA_IMS_START_CNF_STRU
 结构说明  : ID_MSCC_MMA_IMS_START_CNF的结构体
 1.日    期   : 2015年04月13日
   作    者   : f00179208
   修改内容   : 新建
*****************************************************************************/
typedef NAS_MSCC_PIF_IMS_START_CNF_STRU MSCC_MMA_IMS_START_CNF_STRU;

/*****************************************************************************
 结构名    : MMA_MSCC_IMS_STOP_REQ_STRU
 结构说明  : ID_MMA_MSCC_IMS_STOP_REQ的结构体
 1.日    期   : 2015年04月13日
   作    者   : f00179208
   修改内容   : 新建
*****************************************************************************/
typedef NAS_MSCC_PIF_IMS_STOP_REQ_STRU MMA_MSCC_IMS_STOP_REQ_STRU;

/*****************************************************************************
 结构名    : MSCC_MMA_IMS_STOP_CNF_STRU
 结构说明  : ID_MSCC_MMA_IMS_STOP_CNF的结构体
 1.日    期   : 2015年04月13日
   作    者   : f00179208
   修改内容   : 新建
*****************************************************************************/
typedef NAS_MSCC_PIF_IMS_STOP_CNF_STRU MSCC_MMA_IMS_STOP_CNF_STRU;

/*****************************************************************************
 结构名    : MSCC_MMA_IMS_SWITCH_STATE_IND_STRU
 结构说明  : ID_MSCC_MMA_IMS_SWITCH_STATE_IND的结构体
 1.日    期   : 2015年04月15日
   作    者   : f00179208
   修改内容   : 新建
*****************************************************************************/
typedef NAS_MSCC_PIF_IMS_SWITCH_STATE_IND_STRU MSCC_MMA_IMS_SWITCH_STATE_IND_STRU;




/** ****************************************************************************
 * Name        : MSCC_MMA_SYSTEM_ACQUIRE_START_IND_STRU
 *
 * Description :
 *******************************************************************************/
typedef struct
{
    MSCC_MSG_HEADER_STRU                stMsgHeader;        /*_H2ASN_Skip*//* 消息头                                   */
    VOS_UINT16                          usOpId;
    VOS_UINT8                           aucReserve[2];
    MSCC_MMA_ACQ_SYS_TYPE_ENUM_UINT32   enSysType;
}MSCC_MMA_SYSTEM_ACQUIRE_START_IND_STRU;



/*****************************************************************************
 结构名    : MMA_MSCC_CDMA_PS_RATTYPE_NTF_STRU
 结构说明  : ID_MMA_MSCC_CDMA_PS_RATTYPE_NTF的结构体
 1.日    期   : 2015年05月11日
   作    者   : y00322978
   修改内容   : 新建
*****************************************************************************/
typedef NAS_MSCC_PIF_PS_RAT_TYPE_NTF_STRU MMA_MSCC_PS_RAT_TYPE_NTF_STRU;

/*****************************************************************************
 结构名    : MMA_MSCC_AUTO_RESEL_SET_STRU
 结构说明  : ID_MMA_MSCC_AUTO_RESEL_SET 的结构体
 1.日    期   : 2015年6月3日
   作    者   : B00269685
   修改内容   : 新建
*****************************************************************************/
typedef NAS_MSCC_PIF_AUTO_RESEL_SET_STRU MMA_MSCC_AUTO_RESEL_SET_STRU;

/*****************************************************************************
 结构名    : MMA_MSCC_CSG_LIST_SEARCH_REQ_STRU
 结构说明  : ID_MMA_MSCC_CSG_LIST_SEARCH_REQ 的结构体
 1.日    期   : 2015年9月6日
   作    者   : z00161729
   修改内容   : 支持LTE CSG功能新增
*****************************************************************************/
typedef NAS_MSCC_PIF_CSG_LIST_SEARCH_REQ_STRU MMA_MSCC_CSG_LIST_SEARCH_REQ_STRU;

/*****************************************************************************
 结构名    : MSCC_MMA_CSG_LIST_REJ_STRU
 结构说明  : Mscc给mma发送CSG list搜网被接入层reject的消息结构
 1.日    期   : 2015年9月6日
   作    者   : z00161729
   修改内容   : 支持LTE CSG功能新增
*****************************************************************************/
typedef NAS_MSCC_PIF_CSG_LIST_REJ_STRU MSCC_MMA_CSG_LIST_REJ_STRU;

/*****************************************************************************
 结构名    : MSCC_MMA_CSG_LIST_SEARCH_CFN_STRU
 结构说明  : mscc给mma发送CSG list搜网结果消息结构
 1.日    期   : 2015年9月6日
   作    者   : z00161729
   修改内容   : 支持LTE CSG功能新增
*****************************************************************************/
typedef NAS_MSCC_PIF_CSG_LIST_SEARCH_CNF_STRU MSCC_MMA_CSG_LIST_SEARCH_CFN_STRU;

/*****************************************************************************
 结构名    : MSCC_MMA_CSG_LIST_ABORT_CNF_STRU
 结构说明  : mscc给mma发送CSG list abort结果消息结构
 1.日    期   : 2015年9月6日
   作    者   : z00161729
   修改内容   : 支持LTE CSG功能新增
*****************************************************************************/
typedef NAS_MSCC_PIF_CSG_LIST_ABORT_CNF_STRU MSCC_MMA_CSG_LIST_ABORT_CNF_STRU;
/****************************************************************
 结构名    : MMA_MSCC_CSG_LIST_ABORT_REQ_STRU
 结构说明  : ID_MMA_MSCC_CSG_LIST_ABORT_REQ 的结构体
 1.日    期   : 2015年9月6日
   作    者   : z00161729
   修改内容   : 支持LTE CSG功能新增
*****************************************************************************/
typedef NAS_MSCC_PIF_CSG_LIST_ABORT_REQ_STRU MMA_MSCC_CSG_LIST_ABORT_REQ_STRU;

/** ****************************************************************************
 结构名    : MMA_MSCC_HANDSET_INFO_QRY_REQ_STRU
 结构说明  : mma给mscc发送获取手机状态信息的消息结构
 1.日    期   : 2015年5月16日
   作    者   : z00316370
   修改内容   : 新建
*******************************************************************************/
typedef struct
{
    MSCC_MSG_HEADER_STRU                                    stMsgHeader;                              /* _H2ASN_Skip */
    MMA_MSCC_HANDSET_INFO_TYPE_ENUM_UINT32                  enInfoType;
}MMA_MSCC_HANDSET_INFO_QRY_REQ_STRU;

/*****************************************************************************
 结构名    : MSCC_MMA_HANDSET_INFO_QRY_CNF_STRU
 结构说明  : MSCC给MMA回复的手机状态信息的消息结构
 1.日    期   : 2015年5月16日
   作    者   : z00316370
   修改内容   : 新建
*****************************************************************************/
typedef struct
{
    MSCC_MSG_HEADER_STRU                                    stMsgHeader;        /*_H2ASN_Skip*//* 消息头    */
    MMA_MSCC_HANDSET_INFO_TYPE_ENUM_UINT32                  enInfoType;         /* 请求的信息类型 */
    VOS_UINT8                                               ucCasState;         /* 主状态 */
    VOS_UINT8                                               ucCasSubSta;        /* 子状态 */
    MSCC_MMA_1X_CAS_P_REV_ENUM_UINT8                        enHighVer;          /* cas上报的所支持的最高的版本 */
    VOS_UINT8                                               aucRsv[1];
}MSCC_MMA_HANDSET_INFO_QRY_CNF_STRU;

/** ****************************************************************************
 * Name        : MSCC_MMA_UE_STATE_IND_STRU
 * Description : UE STATE indication
 *******************************************************************************/
typedef struct
{
    VOS_MSG_HEADER                                                      /* _H2ASN_Skip */
    MSCC_PIF_MSG_TYPE_ENUM_UINT32                           enMsgId;    /* _H2ASN_Skip */
    VOS_UINT8                                               ucUeMainState;
    VOS_UINT8                                               ucUeSubState;
    VOS_UINT8                                               aucReserve[2];
}MSCC_MMA_UE_STATE_IND_STRU;


/*****************************************************************************
 结构名    : MMA_MSCC_GET_GEO_REQ_STRU
 结构说明  : ID_MMA_MSCC_GET_GEO_REQ的结构体
 1.日    期   : 2015年05月12日
   作    者   : s00217060
   修改内容   : 新建
*****************************************************************************/
typedef NAS_MSCC_PIF_GET_GEO_REQ_STRU MMA_MSCC_GET_GEO_REQ_STRU;

/*****************************************************************************
 结构名    : MSCC_MMA_GET_GEO_CNF_STRU
 结构说明  : ID_MSCC_MMA_GET_GEO_CNF的结构体
 1.日    期   : 2015年05月12日
   作    者   : s00217060
   修改内容   : 新建
*****************************************************************************/
typedef NAS_MSCC_PIF_GET_GEO_CNF_STRU MSCC_MMA_GET_GEO_CNF_STRU;

/*****************************************************************************
 结构名    : MMA_MSCC_STOP_GET_GEO_REQ_STRU
 结构说明  : ID_MMA_MSCC_STOP_GET_GEO_REQ的结构体
 1.日    期   : 2015年06月01日
   作    者   : f00179208
   修改内容   : 新建
*****************************************************************************/
typedef NAS_MSCC_PIF_STOP_GET_GEO_REQ_STRU MMA_MSCC_STOP_GET_GEO_REQ_STRU;

/*****************************************************************************
 结构名    : MSCC_MMA_STOP_GET_GEO_CNF_STRU
 结构说明  : ID_MSCC_MMA_STOP_GET_GEO_CNF的结构体
 1.日    期   : 2015年06月01日
   作    者   : f00179208
   修改内容   : 新建
*****************************************************************************/
typedef NAS_MSCC_PIF_STOP_GET_GEO_CNF_STRU MSCC_MMA_STOP_GET_GEO_CNF_STRU;


/*****************************************************************************
 结构名    : MMA_MSCC_DPLMN_SET_REQ_STRU
 结构说明  : ID_MMA_MSCC_DPLMN_SET_REQ的结构体
  1.日    期   : 2015年10月12日
    作    者   : n00355355
    修改内容   : 新建
*****************************************************************************/
typedef NAS_MSCC_PIF_DPLMN_SET_REQ_STRU MMA_MSCC_DPLMN_SET_REQ_STRU;

/*****************************************************************************
 结构名    : MSCC_MMA_DPLMN_SET_CNF_STRU
 结构说明  : ID_MSCC_MMA_DPLMN_SET_CNF的结构体
  1.日    期   : 2015年10月12日
    作    者   : n00355355
    修改内容   : 新建
*****************************************************************************/
typedef NAS_MSCC_PIF_DPLMN_SET_CNF_STRU MSCC_MMA_DPLMN_SET_CNF_STRU;


/*****************************************************************************
 结构名    : MSCC_MMA_1X_SID_NID_IND_STRU
 结构说明  : MSCC给MMA上报的sid信息
 1.日    期   : 2015年5月16日
   作    者   : y00322978
   修改内容   : 新建
 2.日    期   : 2015年12月10日
   作    者   : l00324781
   修改内容   : CL_MUTIMODE_OPTIMIZE修改
*****************************************************************************/
typedef NAS_MSCC_PIF_SID_NID_IND_STRU MSCC_MMA_1X_SID_NID_IND_STRU;

/*****************************************************************************
 结构名    : MMA_MSCC_QUIT_CALL_BACK_IND_STRU
 结构说明  : mma  snd  mscc   QUIT CALL BACK MODE cnf msg stru
 1.日    期   : 2015年5月16日
   作    者   : y00322978
   修改内容   : 新建
*****************************************************************************/
typedef NAS_MSCC_PIF_END_EMC_CALLBACK_IND_STRU MMA_MSCC_QUIT_CALL_BACK_NTF_STRU;

/*****************************************************************************
 结构名    : MMA_MSCC_SET_CSIDLIST_REQ_STRU
 结构说明  : MMA SND MSCC REQ set csidlist
 1.日    期   : 2015年5月16日
   作    者   : y00322978
   修改内容   : 新建
*****************************************************************************/
typedef NAS_MSCC_PIF_SET_CSIDLIST_REQ_STRU MMA_MSCC_SET_CSIDLIST_REQ_STRU;
/*****************************************************************************
 结构名    : MSCC_MMA_SET_CSIDLIST_CNF_STRU
 结构说明  :  mscc snd  mma   set csidlist cnf msg stru
 1.日    期   : 2015年5月16日
   作    者   : y00322978
   修改内容   : 新建
*****************************************************************************/
typedef NAS_MSCC_PIF_SET_CSIDLIST_CNF_STRU MSCC_MMA_SET_CSIDLIST_CNF_STRU;

/*****************************************************************************
 结构名    : MSCC_MMA_SET_CSIDLIST_CNF_STRU
 结构说明  :  mscc snd  mma   set csidlist cnf msg stru
 1.日    期   : 2015年5月16日
   作    者   : y00322978
   修改内容   : 新建
*****************************************************************************/
typedef NAS_MSCC_PIF_SYNC_SERVICE_AVAILABLE_IND_STRU MSCC_MMA_SYNC_SERVICE_AVAIL_IND_STRU;


/*****************************************************************************
 结构名    : MSCC_MMA_1X_EMC_CALL_BACK_IND_STRU
 结构说明  : MSCC给MMA回复紧急呼CALLBACK模式状态的消息结构
 1.日    期   : 2015年07月02日
   作    者   : h00313353
   修改内容   : 新建
*****************************************************************************/
typedef NAS_MSCC_PIF_EMC_CALLBACK_IND_STRU MSCC_MMA_1X_EMC_CALL_BACK_IND_STRU;

/*****************************************************************************
  8 UNION定义
*****************************************************************************/

/*****************************************************************************
  9 OTHERS定义
*****************************************************************************/

/*****************************************************************************
  H2ASN顶级消息结构定义
*****************************************************************************/
typedef struct
{
    MSCC_PIF_MSG_TYPE_ENUM_UINT32       enMsgID;    /*_H2ASN_MsgChoice_Export MMA_MSCC_MSG_ID_ENUM_UINT32*/

    VOS_UINT8                           aucMsgBlock[4];
    /***************************************************************************
        _H2ASN_MsgChoice_When_Comment          MMA_MSCC_MSG_ID_ENUM_UINT32
    ****************************************************************************/
}MMA_MSCC_MSG_DATA;
/*_H2ASN_Length UINT32*/

typedef struct
{
    VOS_MSG_HEADER
    MMA_MSCC_MSG_DATA    stMsgData;
}MmaMsccInterface_MSG;


/*****************************************************************************
  10 函数声明
*****************************************************************************/


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
