/******************************************************************************

                  版权所有 (C), 2001-2012, 华为技术有限公司

 ******************************************************************************
  文 件 名   : MsccMmcInterface.h
  版 本 号   : 初稿
  作    者   : z00161729
  生成日期   : 2013年3月25日
  最近修改   :
  功能描述   : mscc与mmc消息交互的头文件
  函数列表   :
  修改历史   :
  1.日    期   : 2013年3月25日
    作    者   : z00161729
    修改内容   : 创建文件

******************************************************************************/
#ifndef _MSCC_MMC_INTERFACE_H_
#define _MSCC_MMC_INTERFACE_H_

/*****************************************************************************
  1 其他头文件包含
*****************************************************************************/
#include "PsTypeDef.h"
#include "NasCommDef.h"
#include "NasMsccPifInterface.h"


#ifdef __cplusplus
#if __cplusplus
extern "C" {
#endif
#endif


#pragma pack(4)

/*****************************************************************************
  2 宏定义
*****************************************************************************/
#define MSCC_MMC_HRPD_SUBNET_MAX_LEN             (16)
#define MSCC_MMC_BG_HRPD_MAX_SYS_NUM             (16)

#define MSCC_MMC_VERSION_LEN            (9)

/*****************************************************************************
  3 枚举定义
*****************************************************************************/

/*****************************************************************************
 枚举名    : MSCC_MMC_BG_SRCH_RESULT_ENUM
 协议表格  :
 ASN.1描述 :
 枚举说明  : BG搜索结果
*****************************************************************************/
enum MSCC_MMC_BG_SRCH_RESULT_ENUM
{
    MSCC_MMC_BG_SRCH_RESULT_SUCCESS            = 0,                /* 指定的PLMN搜索成功 */
    MSCC_MMC_BG_SRCH_RESULT_FAIL               = 1,                /* 实际发起了搜网，但是搜索失败 */
    MSCC_MMC_BG_SRCH_RESULT_ABORT              = 2,                /* 没有发起搜网，因为当前状态不允许，搜索被终止 */
    MSCC_MMC_BG_SRCH_RESULT_BUTT
};
typedef VOS_UINT32  MSCC_MMC_BG_SRCH_RESULT_ENUM_UINT32;



/*****************************************************************************
枚举名    : MSCC_MMC_IMS_VOICE_CAPABILITY_ENUM_UINT8
枚举说明  : IMS能力是否支持枚举
1.日    期   : 2015年4月28日
  作    者   : z00161729
  修改内容   : 24301 R11 CR升级项目修改
*****************************************************************************/
enum MSCC_MMC_IMS_VOICE_CAPABILITY_ENUM
{
    MSCC_MMC_IMS_VOICE_CAPABILITY_NOT_AVAIL = 0,
    MSCC_MMC_IMS_VOICE_CAPABILITY_AVAIL     = 1,
    MSCC_MMC_IMS_VOICE_CAPABILITY_BUTT
};
typedef VOS_UINT8 MSCC_MMC_IMS_VOICE_CAPABILITY_ENUM_UINT8;


/*****************************************************************************
枚举名    : MSCC_MMC_PERSISTENT_BEARER_STATE_ENUM_UINT8
枚举说明  : persistent bearer是否存在状态枚举
1.日    期   : 2015年4月28日
  作    者   : z00161729
  修改内容   : 24301 R11 CR升级项目修改
*****************************************************************************/
enum MSCC_MMC_PERSISTENT_BEARER_STATE_ENUM
{
    MSCC_MMC_PERSISTENT_BEARER_STATE_NOT_EXIST = 0,
    MSCC_MMC_PERSISTENT_BEARER_STATE_EXIST     = 1,
    MSCC_MMC_PERSISTENT_BEARER_STATE_BUTT
};
typedef VOS_UINT8 MSCC_MMC_PERSISTENT_BEARER_STATE_ENUM_UINT8;



/*****************************************************************************
枚举名    : MSCC_MMC_MMSS_LTE_UNAVIALBLE_REASON_ENUM_UINT8
枚举说明  : MMSS下LTE不可用原因值枚举

1.日    期   : 2016年1月20日
  作    者   : w00176964
  修改内容   : DTS2016011802320新建
*****************************************************************************/
enum MSCC_MMC_MMSS_LTE_UNAVIALBLE_REASON_ENUM
{
    MSCC_MMC_MMSS_LTE_UNAVIALBLE_REASON_REG_FAILURE         = 0, /* 注册失败导致Lte不可用*/
    MSCC_MMC_MMSS_LTE_UNAVIALBLE_REASON_SERVICE_FAILURE     = 1, /* service流程失败导致Lte不可用*/
    MSCC_MMC_MMSS_LTE_UNAVIALBLE_REASON_MT_DETACH           = 2, /* 网络触发的detach导致Lte不可用*/
    MSCC_MMC_MMSS_LTE_UNAVIALBLE_REASON_USER_DETACH         = 3, /* 用户触发的detach操作导致Lte不可用*/
    MSCC_MMC_MMSS_LTE_UNAVIALBLE_REASON_RAT_OR_BAND_DETACH  = 4, /* system configure中RAT或band触发的detach导致Lte不可用*/
    MSCC_MMC_MMSS_LTE_UNAVIALBLE_REASON_SRV_DOMAIN_DETACH   = 5, /* system configure中服务域触发的detach导致Lte不可用*/
    MSCC_MMC_MMSS_LTE_UNAVIALBLE_REASON_AREA_LOST           = 6, /* lte掉网导致Lte不可用*/
    MSCC_MMC_MMSS_LTE_UNAVIALBLE_REASON_NO_RF               = 7, /* Lte NO RF导致Lte不可用*/
    MSCC_MMC_MMSS_LTE_UNAVIALBLE_REASON_BUTT
};
typedef VOS_UINT8 MSCC_MMC_MMSS_LTE_UNAVIALBLE_REASON_ENUM_UINT8;


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
 结构名    : MSCC_MMC_PLMN_RAT_PRIO_STRU
 结构说明  : 当前支持接入技术和接入技术优先级的数据结构
 1.日    期: 2013年3月25日
   作    者: z00161729
   修改内容: 新增
 2.日    期   : 2015年5月122日
   作    者   : W00176964
   修改内容   : CDMA Iteration 10 modified
*****************************************************************************/
typedef  NAS_MSCC_PIF_RAT_PRIO_STRU MSCC_MMC_PLMN_RAT_PRIO_STRU;

/*****************************************************************************
 结构名    : MSCC_MMC_PLMN_ID_STRU
 结构说明  : plmn id的数据结构
 1.日    期: 2013年3月25日
   作    者: z00161729
   修改内容: 新增
*****************************************************************************/
typedef  NAS_MSCC_PIF_PLMN_ID_STRU MSCC_MMC_PLMN_ID_STRU;

/* Added by s00246516 for L-C互操作项目, 2014-01-26, Begin */
/*****************************************************************************
 结构名    : MSCC_MMC_3GPP2_RAT_STRU
 结构说明  : MS 3GPP2的接入技术能力
 1.日    期   : 2014年1月26日
   作    者   : s00246516
   修改内容   : 新建
*****************************************************************************/
typedef NAS_MSCC_PIF_3GPP2_RAT_STRU MSCC_MMC_3GPP2_RAT_STRU;
/* Added by s00246516 for L-C互操作项目, 2014-01-26, End */

/*****************************************************************************
 结构名    : MSCC_MMC_EPLMN_INFO_STRU
 结构说明  : MML当前EQUPLMN信息
 1.日    期   : 2013年12月24日
   作    者   : z00161729
   修改内容   : SVLTE支持NCELL搜网
*****************************************************************************/
typedef NAS_MSCC_PIF_EPLMN_INFO_STRU MSCC_MMC_EPLMN_INFO_STRU;


/*****************************************************************************
 结构名    : MSCC_MMC_CAMP_CELL_INFO_STRU
 结构说明  : 当前驻留小区的信息
 1.日    期   : 2013年3月25日
   作    者   : z00161729
   修改内容   : 新建
*****************************************************************************/
typedef NAS_MSCC_PIF_CAMP_CELL_INFO_STRU MSCC_MMC_CAMP_CELL_INFO_STRU;

/*****************************************************************************
 结构名    : MSCC_MMC_OPERATOR_NAME_INFO_STRU
 结构说明  : plmn id和运营商长短名信息
 1.日    期: 2013年3月25日
   作    者: z00161729
   修改内容: 新增
*****************************************************************************/
typedef  NAS_MSCC_PIF_OPERATOR_NAME_INFO_STRU MSCC_MMC_OPERATOR_NAME_INFO_STRU;

/*****************************************************************************
 结构名    : MSCC_MMC_UE_SUPPORT_FREQ_BAND_STRU
 结构说明  : ue 支持band能力
 1.日    期: 2013年3月25日
   作    者: z00161729
   修改内容: 新增
*****************************************************************************/
typedef NAS_MSCC_PIF_UE_SUPPORT_FREQ_BAND_STRU MSCC_MMC_UE_SUPPORT_FREQ_BAND_STRU;

/*****************************************************************************
 结构名    : MSCC_MMC_RSSI_VALUE_STRU
 结构说明  : rssi值
 1.日    期: 2013年3月25日
   作    者: z00161729
   修改内容: 新增
*****************************************************************************/
typedef NAS_MSCC_PIF_RSSI_VALUE_STRU MSCC_MMC_RSSI_VALUE_STRU;

/*******************************************************************************
 结构名    :MSCC_MMC_SCELL_MEAS_TYPE_STRU
 结构说明  : union MSCC_MMC_SCELL_MEAS_TYPE_STRU成员stMeasReportType定义
             bit位置1表示该类型有效
1.日    期 : 2014年6月5日
  作    者 : b00269685
  修改内容 : 新建
*******************************************************************************/
typedef NAS_MSCC_PIF_SCELL_MEAS_TYPE_STRU MSCC_MMC_SCELL_MEAS_TYPE_STRU;

/*****************************************************************************
 枚举名    : MSCC_MMC_SCELL_MEAS_REPORT_TYPE_UN
 结构说明  : MSCC_MMC_SCELL_MEAS_REPORT_TYPE_UN unMeasType上报测量的类型
1. 日    期: 2014年6月5日
   作    者: b00269685
   修改内容: 新建
*****************************************************************************/
typedef NAS_MSCC_PIF_SCELL_MEAS_REPORT_TYPE_UN MSCC_MMC_SCELL_MEAS_REPORT_TYPE_UN;
typedef NAS_MSCC_PIF_SRCHED_PLMN_INFO_IND_STRU MMC_MSCC_SRCHED_PLMN_INFO_IND_STRU;
/*****************************************************************************
 结构名    : MMC_MSCC_RSSI_INFO_STRU
 结构说明  : rssi信息
 1.日    期: 2013年3月25日
   作    者: z00161729
   修改内容: 新增
 2.日    期: 2014年6月4日
   作    者: b00269685
   修改内容: 增加上报类型
*****************************************************************************/
typedef NAS_MSCC_PIF_RSSI_IND_STRU MMC_MSCC_RSSI_IND_STRU;

/*****************************************************************************
 结构名    : MMC_MSCC_CQI_INFO_STRU
 结构说明  : LTE下的信道质量,两个码字分别代表子带CQI和宽带CQI
 1.日    期: 2014年11月28日
   作    者: w00281933
   修改内容: 新增
*****************************************************************************/
typedef NAS_MSCC_PIF_CQI_INFO_STRU MMC_MSCC_CQI_INFO_STRU;
/*****************************************************************************
 结构名    : MMA_MMC_LMM_CELL_SIGN_INFO_STRU
 结构说明  : LTE下的信道质量,包括LTE下的Rssi及Rsrp，Rsrq,SINR,CQI
 1.日    期: 2014年11月28日
   作    者: w00281933
   修改内容: 新增
*****************************************************************************/
typedef NAS_MSCC_PIF_LMM_CELL_SIGN_INFO_STRU MSCC_MMC_LMM_CELL_SIGN_INFO_STRU;
/*****************************************************************************
 结构名    : MMC_MSCC_LMM_CELL_SIGN_INFO_REPORT_IND_STRU
 结构说明  : ID_MMC_MMA_LMM_CELL_SIGN_INFO_REPORT_IND对应的结构体
 1.日    期: 2014年11月28日
   作    者: w00281933
   修改内容: 新增
*****************************************************************************/
typedef NAS_MSCC_PIF_LMM_CELL_SIGN_INFO_REPORT_IND_STRU MMC_MSCC_LMM_CELL_SIGN_INFO_REPORT_IND_STRU;


/*****************************************************************************
结构名    : MSCC_MMC_START_REQ_STRU
结构说明  : mscc给mmc发送开机请求的消息结构
1.日    期   : 2013年3月25日
  作    者   : z00161729
  修改内容   : 新建
2.日    期   : 2014年2月8日
  作    者   : s00246516
  修改内容   : L-C互操作项目:增加异系统到HRPD的处理
3.日    期   : 2015年5月12日
  作    者   : w00176964
  修改内容   : CDMA iteration 10 modified
****************************************************************************/
typedef struct
{
    MSCC_MSG_HEADER_STRU                                    MsgHeader;          /* _H2ASN_Skip */ /* 消息头                                   */
    NAS_MSCC_PIF_CARD_STATUS_ENUM_UINT8                     enUsimStatus;
    NAS_MSCC_PIF_CARD_STATUS_ENUM_UINT8                     enCsimStatus;
    NAS_MSCC_PIF_ALLOWED_REG_DOMAIN_ENUM_UINT8              enRegDomain;        /* 在原接口新增开机允许注册的服务域 */
    NAS_MSCC_PIF_REG_CONTROL_ENUM_UINT8                     enRegCtrl;
    NAS_MSCC_PIF_RAT_PRIO_STRU                              stPlmnRatPrio;
    NAS_MSCC_PIF_3GPP2_RAT_STRU                             st3Gpp2Rat;
    VOS_UINT8                                               aucImsi[NAS_MAX_IMSI_LENGTH];
    NAS_MSCC_PIF_CALL_MODE_ENUM_UINT8                       enCallMode;
    VOS_UINT8                                               aucReserved[2];
}MSCC_MMC_START_REQ_STRU;


/*****************************************************************************
 结构名    : MMC_MSCC_START_CNF_STRU
 结构说明  : mmc给mscc发送开机结果的消息结构
 1.日    期   : 2013年3月25日
   作    者   : z00161729
   修改内容   : 新建
*****************************************************************************/
typedef NAS_MSCC_PIF_START_CNF_STRU MMC_MSCC_START_CNF_STRU;

/*****************************************************************************
 结构名    : MMC_MSCC_SYS_INFO_IND_STRU
 结构说明  : mmc给mscc发送系统消息的消息结构
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
typedef NAS_MSCC_PIF_3GPP_SYS_INFO_IND_STRU MMC_MSCC_SYS_INFO_IND_STRU;

/*****************************************************************************
 结构名    : MMC_MSCC_REG_RESULT_IND_STRU
 结构说明  : mmc给mscc发送拒绝原因值消息的消息结构
 1.日    期   : 2013年8月15日
   作    者   : l00208543
   修改内容   : 新建
 2.日    期   : 2013年12月13日
   作    者   : w00176964
   修改内容   : Volte_PhaseIII 项目:修改结构名
*****************************************************************************/
typedef NAS_MSCC_PIF_REG_RESULT_IND_STRU MMC_MSCC_REG_RESULT_IND_STRU;

/*****************************************************************************
 结构名    : MMC_MSCC_USIM_AUTH_FAIL_IND_STRU
 结构说明  : mmc给mscc发送USIM鉴权失败原因值消息的消息结构
 1.日    期   : 2013年11月15日
   作    者   : m00217266
   修改内容   : 新建
*****************************************************************************/
typedef NAS_MSCC_PIF_USIM_AUTH_FAIL_IND_STRU MMC_MSCC_USIM_AUTH_FAIL_IND_STRU;

/*****************************************************************************
 结构名    : MMC_MSCC_SERVICE_STATUS_IND_STRU
 结构说明  : mmc给mscc发送注册状态和服务状态的消息结构
 1.日    期   : 2013年3月25日
   作    者   : z00161729
   修改内容   : 新建
 2.日    期   : 2013年11月20日
   作    者   : w00176964
   修改内容   : Volte PhaseII项目修改:增加CSPS的SIM卡状态
*****************************************************************************/
typedef NAS_MSCC_PIF_SERVICE_STATUS_IND_STRU MMC_MSCC_SERVICE_STATUS_IND_STRU;

/*****************************************************************************
 结构名    : MMC_MSCC_MM_INFO_IND_STRU
 结构说明  : mmc给mscc发送MM INFORMATION的消息结构
 1.日    期   : 2013年3月25日
   作    者   : z00161729
   修改内容   : 新建
*****************************************************************************/
typedef NAS_MSCC_PIF_MM_INFO_IND_STRU MMC_MSCC_MM_INFO_IND_STRU;

/*****************************************************************************
 结构名    : MSCC_MMC_SIGN_REPORT_REQ_STRU
 结构说明  : mscc给mmc发送信号上报配置的消息结构
 1.日    期   : 2013年3月25日
   作    者   : z00161729
   修改内容   : 新建
*****************************************************************************/
typedef NAS_MSCC_PIF_SIGN_REPORT_REQ_STRU MSCC_MMC_SIGN_REPORT_REQ_STRU;

/*****************************************************************************
 结构名    : MSCC_MMC_MODE_CHANGE_REQ_STRU
 结构说明  : mscc给mmc发送模式变更的消息结构
 1.日    期   : 2013年3月25日
   作    者   : z00161729
   修改内容   : 新建
*****************************************************************************/
typedef NAS_MSCC_PIF_MODE_CHANGE_REQ_STRU MSCC_MMC_MODE_CHANGE_REQ_STRU;

/*****************************************************************************
 结构名    : MSCC_MMC_ATTACH_REQ_STRU
 结构说明  : mscc给mmc发送attach 请求的消息结构
 1.日    期   : 2013年3月25日
   作    者   : z00161729
   修改内容   : 新建
 2.日    期   : 2014年2月8日
   作    者   : s00246516
   修改内容   : L-C互操作项目:增加异系统到HRPD的处理
*****************************************************************************/
typedef NAS_MSCC_PIF_ATTACH_REQ_STRU MSCC_MMC_ATTACH_REQ_STRU;

/*****************************************************************************
 结构名    : MMC_MSCC_ATTACH_CNF_STRU
 结构说明  : mmc给mscc发送attach 结果的消息结构
 1.日    期   : 2013年3月25日
   作    者   : z00161729
   修改内容   : 新建
*****************************************************************************/
typedef NAS_MSCC_PIF_ATTACH_CNF_STRU MMC_MSCC_ATTACH_CNF_STRU;

/*****************************************************************************
 结构名    : MSCC_MMC_DETACH_REQ_STRU
 结构说明  : mscc给mmc发送detach请求的消息结构
 1.日    期   : 2013年3月25日
   作    者   : z00161729
   修改内容   : 新建
 2.日    期   : 2014年2月8日
   作    者   : s00246516
   修改内容   : L-C互操作项目:增加异系统到HRPD的处理
*****************************************************************************/
typedef NAS_MSCC_PIF_DETACH_REQ_STRU MSCC_MMC_DETACH_REQ_STRU;

/*****************************************************************************
 结构名    : MMC_MSCC_DETACH_CNF_STRU
 结构说明  : mmc给mscc发送detach结果的消息结构
 1.日    期   : 2013年3月25日
   作    者   : z00161729
   修改内容   : 新建
*****************************************************************************/
typedef NAS_MSCC_PIF_DETACH_CNF_STRU MMC_MSCC_DETACH_CNF_STRU;

/*****************************************************************************
 结构名    : MMC_MSCC_DETACH_IND_STRU
 结构说明  : mmc给mscc发送网络detach结果的消息结构
 1.日    期   : 2013年3月25日
   作    者   : z00161729
   修改内容   : 新建
 2.日    期   : 2014年4月1日
   作    者   : z00161729
   修改内容   : DTS2014040300125:service 被拒和网络detach ind被拒需要上报^rejinfo
*****************************************************************************/
typedef NAS_MSCC_PIF_DETACH_IND_STRU MMC_MSCC_DETACH_IND_STRU;

/*****************************************************************************
 结构名    : MSCC_MMC_CSG_LIST_SEARCH_REQ_STRU
 结构说明  : mscc给mmc发送CSG list搜网小区
 1.日    期   : 2015年9月6日
   作    者   : z00161729
   修改内容   : 支持LTE CSG功能新增
*****************************************************************************/
typedef NAS_MSCC_PIF_CSG_LIST_SEARCH_REQ_STRU MSCC_MMC_CSG_LIST_SEARCH_REQ_STRU;

/*****************************************************************************
 结构名    : MMC_MSCC_CSG_LIST_SEARCH_CNF_STRU
 结构说明  : mmc给mscc发送CSG list搜网结果消息结构
 1.日    期   : 2015年9月6日
   作    者   : z00161729
   修改内容   : 支持LTE CSG功能新增
*****************************************************************************/
typedef NAS_MSCC_PIF_CSG_LIST_SEARCH_CNF_STRU MMC_MSCC_CSG_LIST_SEARCH_CNF_STRU;

/*****************************************************************************
 结构名    : MMC_MSCC_CSG_LIST_ABORT_CNF_STRU
 结构说明  : mmc给mscc发送CSG list abort结果消息结构
 1.日    期   : 2015年9月6日
   作    者   : z00161729
   修改内容   : 支持LTE CSG功能新增
*****************************************************************************/
typedef NAS_MSCC_PIF_CSG_LIST_ABORT_CNF_STRU MMC_MSCC_CSG_LIST_ABORT_CNF_STRU;

/*****************************************************************************
 结构名    : NAS_MSCC_PIF_CSG_LIST_REJ_STRU
 结构说明  : mmc给mscc发送CSG list rej消息结构
 1.日    期   : 2015年9月6日
   作    者   : z00161729
   修改内容   : 支持LTE CSG功能新增
*****************************************************************************/
typedef NAS_MSCC_PIF_CSG_LIST_REJ_STRU MMC_MSCC_CSG_LIST_REJ_STRU;
/*****************************************************************************
 结构名    : MSCC_MMC_CSG_LIST_ABORT_REQ_STRU
 结构说明  : mscc给mmc发送csg list abort消息
 1.日    期   : 2015年9月6日
   作    者   : z00161729
   修改内容   : 支持LTE CSG功能新增
*****************************************************************************/
typedef NAS_MSCC_PIF_CSG_LIST_ABORT_REQ_STRU MSCC_MMC_CSG_LIST_ABORT_REQ_STRU;

/*****************************************************************************
 结构名    : MSCC_MMC_PLMN_LIST_REQ_STRU
 结构说明  : mscc给mmc发送list请求的消息结构
 1.日    期   : 2013年3月25日
   作    者   : z00161729
   修改内容   : 新建
*****************************************************************************/
typedef NAS_MSCC_PIF_PLMN_LIST_REQ_STRU MSCC_MMC_PLMN_LIST_REQ_STRU;

/*****************************************************************************
 结构名    : MMC_MSCC_PLMN_LIST_CNF_STRU
 结构说明  : mmc给mscc发送list搜网结果的消息结构
 1.日    期   : 2013年3月25日
   作    者   : z00161729
   修改内容   : 新建
*****************************************************************************/
typedef NAS_MSCC_PIF_PLMN_LIST_CNF_STRU MMC_MSCC_PLMN_LIST_CNF_STRU;

/*****************************************************************************
 结构名    : MMC_MSCC_PLMN_LIST_REJ_STRU
 结构说明  : mmc给mscc发送list搜网被接入层reject的消息结构
 1.日    期   : 2013年3月25日
   作    者   : z00161729
   修改内容   : 新建
*****************************************************************************/
typedef NAS_MSCC_PIF_PLMN_LIST_REJ_STRU MMC_MSCC_PLMN_LIST_REJ_STRU;

/*****************************************************************************
 结构名    : MSCC_MMC_PLMN_LIST_ABORT_REQ_STRU
 结构说明  : mscc给mmc发送list搜网中止的消息结构
 1.日    期   : 2013年3月25日
   作    者   : z00161729
   修改内容   : 新建
*****************************************************************************/
typedef NAS_MSCC_PIF_PLMN_LIST_ABORT_REQ_STRU MSCC_MMC_PLMN_LIST_ABORT_REQ_STRU;

/*****************************************************************************
 结构名    : MSCC_MMC_PLMN_USER_RESEL_REQ_STRU
 结构说明  : mscc给mmc发送用户重选搜网请求的消息结构
 1.日    期   : 2013年3月25日
   作    者   : z00161729
   修改内容   : 新建
*****************************************************************************/
typedef NAS_MSCC_PIF_PLMN_USER_RESEL_REQ_STRU MSCC_MMC_PLMN_USER_RESEL_REQ_STRU;

/*****************************************************************************
 结构名    : MSCC_MMC_PLMN_SPECIAL_REQ_STRU
 结构说明  : mscc给mmc发送用户指定搜网请求的消息结构
 1.日    期   : 2013年3月25日
   作    者   : z00161729
   修改内容   : 新建
*****************************************************************************/
typedef NAS_MSCC_PIF_PLMN_SPECIAL_REQ_STRU MSCC_MMC_PLMN_SPECIAL_REQ_STRU;


/*****************************************************************************
 结构名    : MMC_MSCC_COVERAGE_AREA_IND_STRU
 结构说明  : mmc给mscc发送进覆盖区还是离开覆盖区指示的消息结构
 1.日    期   : 2013年3月25日
   作    者   : z00161729
   修改内容   : 新建
*****************************************************************************/
typedef NAS_MSCC_PIF_COVERAGE_AREA_IND_STRU MMC_MSCC_COVERAGE_AREA_IND_STRU;

/*****************************************************************************
 结构名    : MSCC_MMC_POWER_OFF_REQ_STRU
 结构说明  : mscc给mmc发送关机请求的消息结构
 1.日    期   : 2013年3月25日
   作    者   : z00161729
   修改内容   : 新建
*****************************************************************************/
typedef NAS_MSCC_PIF_POWER_OFF_REQ_STRU MSCC_MMC_POWER_OFF_REQ_STRU;

/*****************************************************************************
 结构名    : MMC_MSCC_POWER_OFF_CNF_STRU
 结构说明  : mmc给mscc发送关机回复的消息结构
 1.日    期   : 2013年3月25日
   作    者   : z00161729
   修改内容   : 新建
*****************************************************************************/
typedef NAS_MSCC_PIF_POWER_OFF_CNF_STRU MMC_MSCC_POWER_OFF_CNF_STRU;

/*****************************************************************************
 结构名    : MMC_MSCC_PLMN_SPECIAL_SEL_CNF_STRU
 结构说明  : mmc给mscc发送用户指定搜网回复的消息结构
 1.日    期   : 2013年3月25日
   作    者   : z00161729
   修改内容   : 新建
*****************************************************************************/
typedef NAS_MSCC_PIF_PLMN_SPECIAL_SEL_CNF_STRU MMC_MSCC_PLMN_SPECIAL_SEL_CNF_STRU;

/*****************************************************************************
 结构名    : MMC_MSCC_PLMN_RESEL_CNF_STRU
 结构说明  : mmc给mscc发送at+cops=0回复的消息结构
 1.日    期   : 2013年3月25日
   作    者   : z00161729
   修改内容   : 新建
*****************************************************************************/
typedef NAS_MSCC_PIF_PLMN_RESEL_CNF_STRU MMC_MSCC_PLMN_RESEL_CNF_STRU;

/*****************************************************************************
 结构名    : MMC_MSCC_DATATRAN_ATTRI_IND_STRU
 结构说明  : mmc给mscc发送pdp激活情况的消息结构
 1.日    期   : 2013年3月25日
   作    者   : z00161729
   修改内容   : 新建
*****************************************************************************/
typedef NAS_MSCC_PIF_DATATRAN_ATTRI_IND_STRU MMC_MSCC_DATATRAN_ATTRI_IND_STRU;

/*****************************************************************************
 结构名    : MSCC_MMC_SYS_CFG_SET_REQ_STRU
 结构说明  : mscc给mmc发送syscfg设置请求的消息结构
 1.日    期   : 2013年3月25日
   作    者   : z00161729
   修改内容   : 新建
*****************************************************************************/
typedef NAS_MSCC_PIF_SYS_CFG_SET_REQ_STRU MSCC_MMC_SYS_CFG_SET_REQ_STRU;

/*****************************************************************************
 结构名    : MMC_MSCC_SYS_CFG_SET_CNF_STRU
 结构说明  : mmc给mscc发送syscfg设置结果的消息结构
 1.日    期   : 2013年3月25日
   作    者   : z00161729
   修改内容   : 新建
*****************************************************************************/
typedef NAS_MSCC_PIF_SYS_CFG_SET_CNF_STRU MMC_MSCC_SYS_CFG_SET_CNF_STRU;

/*****************************************************************************
 结构名    : MSCC_MMC_PLMN_SEARCH_REQ_STRU
 结构说明  : mscc给mmc发送搜网请求的消息结构
 1.日    期   : 2013年3月25日
   作    者   : z00161729
   修改内容   : 新建
*****************************************************************************/
typedef NAS_MSCC_PIF_PLMN_SEARCH_REQ_STRU MSCC_MMC_PLMN_SEARCH_REQ_STRU;

/*****************************************************************************
 结构名    : MMC_MSCC_PLMN_SELECTION_RLST_IND_STRU
 结构说明  : mmc给mscc发送搜网结果的消息结构
 1.日    期   : 2013年3月25日
   作    者   : z00161729
   修改内容   : 新建
*****************************************************************************/
typedef NAS_MSCC_PIF_PLMN_SELECTION_RLST_IND_STRU MMC_MSCC_PLMN_SELECTION_RLST_IND_STRU;

/*****************************************************************************
 结构名    : MMC_MSCC_PLMN_SELECTION_START_IND_STRU
 结构说明  : mmc给mscc发送搜网开始标示的结构
 1.日    期   : 2013年10月09日
   作    者   : l00208543
   修改内容   : 新建,DTS2013100904573
*****************************************************************************/
typedef NAS_MSCC_PIF_PLMN_SELECTION_START_IND_STRU MMC_MSCC_PLMN_SELECTION_START_IND_STRU;

/*****************************************************************************
 结构名    : MMC_MSCC_PLMN_LIST_ABORT_CNF_STRU
 结构说明  : mmc给mscc发送list搜网中止回复的消息结构
 1.日    期   : 2013年3月25日
   作    者   : z00161729
   修改内容   : 新建
*****************************************************************************/
typedef NAS_MSCC_PIF_PLMN_LIST_ABORT_CNF_STRU MMC_MSCC_PLMN_LIST_ABORT_CNF_STRU;

/*****************************************************************************
 结构名    : MSCC_MMC_SPEC_PLMN_SEARCH_ABORT_REQ_STRU
 结构说明  : mscc给mmc发送指定搜网中止请求的消息结构
 1.日    期   : 2013年3月25日
   作    者   : z00161729
   修改内容   : 新建
*****************************************************************************/
typedef NAS_MSCC_PIF_SPEC_PLMN_SEARCH_ABORT_REQ_STRU MSCC_MMC_SPEC_PLMN_SEARCH_ABORT_REQ_STRU;

/*****************************************************************************
 结构名    : MMC_MSCC_SPEC_PLMN_SEARCH_ABORT_CNF_STRU
 结构说明  : mmc给mscc发送中止指定搜网回复的消息结构
 1.日    期   : 2013年3月25日
   作    者   : z00161729
   修改内容   : 新建
*****************************************************************************/
typedef NAS_MSCC_PIF_SPEC_PLMN_SEARCH_ABORT_CNF_STRU MMC_MSCC_SPEC_PLMN_SEARCH_ABORT_CNF_STRU;

/*****************************************************************************
 结构名    : MMC_MSCC_UMTS_CIPHER_INFO_IND_STRU
 结构说明  : mmc给mscc上报W的cipher信息的消息结构
 1.日    期   : 2013年3月25日
   作    者   : z00161729
   修改内容   : 新建
*****************************************************************************/
typedef NAS_MSCC_PIF_UMTS_CIPHER_INFO_IND_STRU MMC_MSCC_UMTS_CIPHER_INFO_IND_STRU;

/*****************************************************************************
 结构名    : MMC_MSCC_GPRS_CIPHER_INFO_IND_STRU
 结构说明  : mmc给mscc上报G的cipher信息的消息结构
 1.日    期   : 2013年3月25日
   作    者   : z00161729
   修改内容   : 新建
*****************************************************************************/
typedef NAS_MSCC_PIF_GPRS_CIPHER_INFO_IND_STRU MMC_MSCC_GPRS_CIPHER_INFO_IND_STRU;

/*****************************************************************************
 结构名    : MMC_MSCC_PLMN_SPECIAL_SEL_REJ_STRU
 结构说明  : MMC给MSCC发送用户指定搜拒绝结果的消息结构
 1.日    期   : 2013年3月25日
   作    者   : z00161729
   修改内容   : 新建
*****************************************************************************/
typedef NAS_MSCC_PIF_PLMN_SPECIAL_SEL_REJ_STRU MMC_MSCC_PLMN_SPECIAL_SEL_REJ_STRU;

/*****************************************************************************
 结构名    : MMC_MSCC_AC_INFO_CHANGE_IND_STRU
 结构说明  : MMC给MSCC发送小区接入信息变化指示的消息结构
 1.日    期   : 2013年3月25日
   作    者   : z00161729
   修改内容   : 新建
*****************************************************************************/
typedef NAS_MSCC_PIF_AC_INFO_CHANGE_IND_STRU MMC_MSCC_AC_INFO_CHANGE_IND_STRU;

/*******************************************************************************
 结构名    : MSCC_MMC_OM_MAINTAIN_INFO_IND_STRU
 结构说明  : MSCC_MMC_OM_MAINTAIN_INFO_IND_STRU消息结构
 1.日    期  : 2013年04月16日
   作    者  : z00161729
   修改内容  : 新增结构
*******************************************************************************/
typedef NAS_MSCC_PIF_OM_MAINTAIN_INFO_IND_STRU MSCC_MMC_OM_MAINTAIN_INFO_IND_STRU;

/*****************************************************************************
 结构名    : MSCC_MMC_UPDATE_UPLMN_NTF_STRU
 结构说明  : mscc给mmc发送UPLMN更新通知的消息结构
 1.日    期   : 2013年7月31日
   作    者   : w00167002
   修改内容   : 新建结构体
*****************************************************************************/
typedef NAS_MSCC_PIF_UPDATE_UPLMN_NTF_STRU MSCC_MMC_UPDATE_UPLMN_NTF_STRU;

/*****************************************************************************
 结构名    : MSCC_MMC_EOPLMN_SET_REQ_STRU
 结构说明  : AT和MSCC的EOPLMN设置接口
 1.日    期  : 2013年10月15日
   作    者  : s00190137
   修改内容  : 新增结构
 2.日    期  : 2013年11月26日
   作    者  : s00190137
   修改内容  : 添加分组机制，单组允许最大设置50个OPLMN
*****************************************************************************/
typedef NAS_MSCC_PIF_EOPLMN_SET_REQ_STRU MSCC_MMC_EOPLMN_SET_REQ_STRU;

/*****************************************************************************
 结构名    : MSCC_MMC_CL_ASSOCIATED_INFO_NTF_STRU
 结构说明  : mscc给mmc发的CL Associated info
 1.日    期   : 2015年9月14日
   作    者   : y00346957
   修改内容   : 新建
*****************************************************************************/
typedef NAS_MSCC_PIF_CL_ASSOCIATED_INFO_NTF_STRU MSCC_MMC_CL_ASSOCIATED_INFO_NTF_STRU;

/*****************************************************************************
 结构名    : NAS_MSCC_PIF_CL_INTERSYS_START_NTF_STRU
 结构说明  : mscc给mmc发的CL 异系统重选开始指示
 1.日    期   : 2016年1月27日
   作    者   : y00346957
   修改内容   : 新建
*****************************************************************************/
typedef struct
{
    MSCC_MSG_HEADER_STRU                                    stMsgHeader;          /* _H2ASN_Skip */
    VOS_UINT16                                              usOpId;
    VOS_UINT8                                               aucReserved[2];
    NAS_MSCC_PIF_INTERSYS_CAUSE_ENUM_UINT32                 enInterSysCause;
}MSCC_MMC_CL_INTERSYS_START_NTF_STRU;

/** ****************************************************************************
 * Name        : MMC_MSCC_INTERSYS_START_IND_STRU
 *
 * Description : MMC的异系统开始指示
 *******************************************************************************/
typedef struct
{
    MSCC_MSG_HEADER_STRU                                    stMsgHeader;        /* _H2ASN_Skip */
    VOS_RATMODE_ENUM_UINT32                                 enOrignRatMode;
    VOS_RATMODE_ENUM_UINT32                                 enDestRatMode;
    NAS_MSCC_PIF_INTERSYS_CAUSE_ENUM_UINT32                 enInterSysCause;
}MMC_MSCC_INTERSYS_START_IND_STRU;

/** ****************************************************************************
 * Name        : MMC_MSCC_INTERSYS_END_IND_STRU
 *
 * Description : MMC的异系统结束指示
 *******************************************************************************/
typedef struct
{
    MSCC_MSG_HEADER_STRU                stMsgHeader;        /* _H2ASN_Skip */
    VOS_RATMODE_ENUM_UINT32             enCurrRatMode;
}MMC_MSCC_INTERSYS_END_IND_STRU;

/*****************************************************************************
 结构名    : MMC_MSCC_EOPLMN_SET_CNF_STRU
 结构说明  : mmc给mscc发送AT^EOPLMN设置回复的消息结构
 1.日    期   : 2013年10月15日
   作    者   : x65241
   修改内容   : 新建
*****************************************************************************/
typedef NAS_MSCC_PIF_EOPLMN_SET_CNF_STRU MMC_MSCC_EOPLMN_SET_CNF_STRU;

/*****************************************************************************
 结构名    : MMC_MSCC_EOPLMN_SET_ABORT_STRU
 结构说明  : AT^EOPLMN设置超时通知MMC中断消息处理的结构
 1.日    期   : 2013年10月15日
   作    者   : x65241
   修改内容   : 新建
*****************************************************************************/
typedef NAS_MSCC_PIF_EOPLMN_SET_ABORT_STRU MMC_MSCC_EOPLMN_SET_ABORT_STRU;

/*****************************************************************************
 结构名    : MSCC_MMC_NET_SCAN_REQ_STRU
 结构说明  : MSCC和MMC的NETSCAN设置接口
 1.日    期  : 2013年10月10日
   作    者  : w00242748
   修改内容  : 新增结构
*****************************************************************************/
typedef NAS_MSCC_PIF_NET_SCAN_REQ_STRU MSCC_MMC_NET_SCAN_REQ_STRU;

/*****************************************************************************
 结构名    : MMC_MSCC_NET_SCAN_INFO_STRU
 结构说明  : 扫描某个频点的网络信息
 1.日    期   : 2013年8月24日
   作    者   : w00242748
   修改内容   : 新建
*****************************************************************************/
typedef NAS_MSCC_PIF_NET_SCAN_INFO_STRU MMC_MSCC_NET_SCAN_INFO_STRU;

/*****************************************************************************
 结构名    : MMC_MSCC_NET_SCAN_CNF_STRU
 结构说明  : MMC上报给MSCC的NETSCAN CNF接口
 1.日    期  : 2013年10月10日
   作    者  : w00242748
   修改内容  : 新增结构
*****************************************************************************/
typedef NAS_MSCC_PIF_NET_SCAN_CNF_STRU MMC_MSCC_NET_SCAN_CNF_STRU;

/*****************************************************************************
 结构名    : MMC_MSCC_SERV_REJ_IND_STRU
 结构说明  : mmc给mscc发送服务被拒的消息结构
 1.日    期   : 2014年4月1日
   作    者   : z00161729
   修改内容   : 新建
*****************************************************************************/
typedef NAS_MSCC_PIF_SERV_REJ_IND_STRU MMC_MSCC_SERV_REJ_IND_STRU;

/*****************************************************************************
 结构名    : MSCC_MMC_ABORT_NET_SCAN_REQ_STRU
 结构说明  : MSCC和MMC的NETSCAN设置接口
 1.日    期  : 2013年10月10日
   作    者  : w00242748
   修改内容  : 新增结构
*****************************************************************************/
typedef NAS_MSCC_PIF_ABORT_NET_SCAN_REQ_STRU MSCC_MMC_ABORT_NET_SCAN_REQ_STRU;

/*****************************************************************************
 结构名    : MMC_MSCC_ABORT_NET_SCAN_CNF_STRU
 结构说明  : MMC上报给MSCC的NETSCAN CNF接口
 1.日    期  : 2013年10月10日
   作    者  : w00242748
   修改内容  : 新增结构
*****************************************************************************/
typedef NAS_MSCC_PIF_ABORT_NET_SCAN_CNF_STRU MMC_MSCC_ABORT_NET_SCAN_CNF_STRU;

/* Added by y00245242 for VoLTE_PhaseI  项目, 2013-7-9, begin */
/*******************************************************************************
 结构名    : MMC_MSCC_NETWORK_CAPABILITY_INFO_IND_STRU
 结构说明  : 通知网络业务信息能力消息
 1.日    期  : 2013年7月9日
   作    者  : y00245242
   修改内容  : 新增结构
*******************************************************************************/
typedef NAS_MSCC_PIF_NETWORK_CAPABILITY_INFO_IND_STRU MMC_MSCC_NETWORK_CAPABILITY_INFO_IND_STRU;
/* Added by y00245242 for VoLTE_PhaseI  项目, 2013-7-9, end */

/* Added by w00176964 for VoLTE_PhaseII 项目, 2013-10-12, begin */
/*****************************************************************************
 结构名    : MMC_MSCC_CAMP_ON_IND_STRU
 结构说明  : MMC发给MSCC的驻留消息结构
 1.日    期   : 2013年10月12日
   作    者   : w00176964
   修改内容   : 新建结构体
*****************************************************************************/
typedef NAS_MSCC_PIF_CAMP_ON_IND_STRU_STRU MMC_MSCC_CAMP_ON_IND_STRU_STRU;
/* Added by w00176964 for VoLTE_PhaseII 项目, 2013-10-12, end */

/*****************************************************************************
 结构名    : MSCC_MMC_OTHER_MODEM_INFO_NOTIFY_STRU
 结构说明  : modem1的信息目前只有驻留信息
 1.日    期   : 2013年11月23日
   作    者   : z00161729
   修改内容   : 新建
 2.日    期   : 2013年12月24日
   作    者   : z00161729
   修改内容   : SVLTE支持NCELL搜网
*****************************************************************************/
typedef NAS_MSCC_PIF_OTHER_MODEM_INFO_NOTIFY_STRU MSCC_MMC_OTHER_MODEM_INFO_NOTIFY_STRU;

/*****************************************************************************
 结构名    : MSCC_MMC_OTHER_MODEM_DPLMN_NPLMN_INFO_NOTIFY_STRU
 结构说明  : modem1的dplmn/nplmn信息
 1.日    期   : 2014年11月3日
   作    者   : z00161729
   修改内容   : 开机漫游搜网项目修改

*****************************************************************************/
typedef NAS_MSCC_PIF_OTHER_MODEM_DPLMN_NPLMN_INFO_NOTIFY_STRU MSCC_MMC_OTHER_MODEM_DPLMN_NPLMN_INFO_NOTIFY_STRU;

/*******************************************************************************
 结构名    : MSCC_MMC_TDS_NCELL_INFO_STRU
 结构说明  : GSM下的TDS频点列表

 1.日    期   : 2013年12月24日
   作    者   : z00161729
   修改内容   : SVLTE支持NCELL搜网

*******************************************************************************/
typedef NAS_MSCC_PIF_TDS_NCELL_INFO_STRU MSCC_MMC_TDS_NCELL_INFO_STRU;

/*******************************************************************************
 结构名    : MSCC_MMC_LTE_NCELL_INFO_STRU
 结构说明  : GSM下的LTE频点列表

 1.日    期   : 2013年12月24日
   作    者   : z00161729
   修改内容   : SVLTE支持NCELL搜网

*******************************************************************************/
typedef NAS_MSCC_PIF_LTE_NCELL_INFO_STRU MSCC_MMC_LTE_NCELL_INFO_STRU;

/*******************************************************************************
 结构名    : MSCC_MMC_NCELL_INFO_NOTIFY_STRU
 结构说明  : ID_MSCC_MMC_NCELL_INFO_NOTIFY消息对应的结构，
             包括GSM下的TDS/LTE邻区结构中的TDS/LTE的频点列表

 1.日    期   : 2013年12月23日
   作    者   : z00161729
   修改内容   : 新生成结构

*******************************************************************************/
typedef NAS_MSCC_PIF_NCELL_INFO_NOTIFY_STRU MSCC_MMC_NCELL_INFO_NOTIFY_STRU;

/*****************************************************************************
 结构名    : MMC_MSCC_EPLMN_INFO_IND_STRU
 结构说明  : 等效plmn信息
 1.日    期   : 2013年12月23日
   作    者   : z00161729
   修改内容   : 新建
*****************************************************************************/
typedef NAS_MSCC_PIF_EPLMN_INFO_IND_STRU MMC_MSCC_EPLMN_INFO_IND_STRU;

/*****************************************************************************
 结构名    : MMC_MSCC_CS_SERVICE_CONN_STATUS_IND_STRU
 结构说明  : mmc上报cs业务信令连接状态指示消息结构
 1.日    期   : 2014年3月4日
   作    者   : z00161729
   修改内容   : 新建
*****************************************************************************/
typedef NAS_MSCC_PIF_CS_SERVICE_CONN_STATUS_IND_STRU MMC_MSCC_CS_SERVICE_CONN_STATUS_IND_STRU;

/*******************************************************************************
结构名    : MSCC_MMC_PS_TRANSFER_NOTIFY_STRU
结构说明  : ID_MSCC_MMC_PS_TRANSFER_NOTIFY消息结构
1.日    期   : 2014年1月5日
  作    者   : z00161729
  修改内容   : 新建
2.日    期   : 2014年01月17日
  作    者   : l00198894
  修改内容   : V9R1C53 C+L 离网重选项目
*******************************************************************************/
typedef NAS_MSCC_PIF_PS_TRANSFER_NOTIFY_STRU MSCC_MMC_PS_TRANSFER_NOTIFY_STRU;

/* Added by w00176964 for VoLTE_PhaseIII 项目, 2013-12-10, begin */
/*****************************************************************************
 结构名    : MSCC_MMC_IMS_VOICE_CAP_NOTIFY_STRU
 结构说明  : MSCC通知MMC当前IMS VOICE是否可用的消息
 1.日    期   : 2013年12月10日
   作    者   : w00176964
   修改内容   : 新建
*****************************************************************************/
typedef NAS_MSCC_PIF_IMS_VOICE_CAP_NOTIFY_STRU MSCC_MMC_IMS_VOICE_CAP_NOTIFY_STRU;
/* Added by w00176964 for VoLTE_PhaseIII 项目, 2013-12-10, end */

/* Added by s00246516 for L-C互操作项目, 2014-01-26, Begin */
/*****************************************************************************
 结构名    : MSCC_MMC_ACQ_REQ_STRU
 结构说明  : 获取消息的结构体
 1.日    期   : 2014年1月26日
   作    者   : s00246516
   修改内容   : 新建
*****************************************************************************/
typedef NAS_MSCC_PIF_ACQ_REQ_STRU MSCC_MMC_ACQ_REQ_STRU;

/*****************************************************************************
 结构名    : MMC_MSCC_ACQ_CNF_STRU
 结构说明  : 获取结果的结构体
 1.日    期   : 2014年1月26日
   作    者   : s00246516
   修改内容   : 新建
*****************************************************************************/
typedef NAS_MSCC_PIF_ACQ_CNF_STRU MMC_MSCC_ACQ_CNF_STRU;

/*****************************************************************************
 结构名    : MSCC_MMC_REG_CELL_INFO_STRU
 结构说明  : 注册消息中Cell Info的结构体
 1.日    期   : 2014年1月26日
   作    者   : s00246516
   修改内容   : 新建
*****************************************************************************/
typedef NAS_MSCC_PIF_REG_CELL_INFO_STRU MSCC_MMC_REG_CELL_INFO_STRU;

/*****************************************************************************
 结构名    : MSCC_MMC_REG_REQ_STRU
 结构说明  : 注册消息的结构体
 1.日    期   : 2014年1月26日
   作    者   : s00246516
   修改内容   : 新建
*****************************************************************************/
typedef NAS_MSCC_PIF_REG_REQ_STRU MSCC_MMC_REG_REQ_STRU;

/*****************************************************************************
 结构名    : MMC_MSCC_REG_CNF_STRU
 结构说明  : 注册结果的结构体
 1.日    期   : 2014年1月26日
   作    者   : s00246516
   修改内容   : 新建
*****************************************************************************/
typedef NAS_MSCC_PIF_REG_CNF_STRU MMC_MSCC_REG_CNF_STRU;

/*****************************************************************************
 结构名    : MSCC_MMC_POWER_SAVE_REQ_STRU
 结构说明  : Power save消息的结构体
 1.日    期   : 2014年1月26日
   作    者   : s00246516
   修改内容   : 新建
*****************************************************************************/
typedef NAS_MSCC_PIF_POWER_SAVE_REQ_STRU MSCC_MMC_POWER_SAVE_REQ_STRU;

/*****************************************************************************
 结构名    : MMC_MSCC_POWER_SAVE_CNF_STRU
 结构说明  : Power save结果的结构体
 1.日    期   : 2014年1月26日
   作    者   : s00246516
   修改内容   : 新建
*****************************************************************************/
typedef NAS_MSCC_PIF_POWER_SAVE_CNF_STRU MMC_MSCC_POWER_SAVE_CNF_STRU;

/*****************************************************************************
 结构名    : MMC_MSCC_ACQ_IND_STRU
 结构说明  : 获取指示的结构体
 1.日    期   : 2014年1月26日
   作    者   : s00246516
   修改内容   : 新建
*****************************************************************************/
typedef  NAS_MSCC_PIF_ACQ_CNF_STRU MMC_MSCC_ACQ_IND_STRU;
/* Added by s00246516 for L-C互操作项目, 2014-01-26, End */

/* Add by s00217060 for K3V3 多模多天线特性, 2014-06-27, Begin */
/*****************************************************************************
 结构名    : MMC_MSCC_PS_SERVICE_CONN_STATUS_IND_STRU
 结构说明  : mmc上报ps业务信令连接状态指示消息结构
 1.日    期   : 2014年6月27日
   作    者   : s00217060
   修改内容   : 新建
*****************************************************************************/
typedef NAS_MSCC_PIF_PS_SERVICE_CONN_STATUS_IND_STRU MMC_MSCC_PS_SERVICE_CONN_STATUS_IND_STRU;
/* Add by s00217060 for K3V3 多模多天线特性, 2014-06-27, end */

/*****************************************************************************
 结构名    : MMC_MSCC_RF_AVAILABLE_IND_STRU
 结构说明  : MMC通知MSCC当前是否有RF资源可用
 1.日    期   : 2014年6月30日
   作    者   : W00176964
   修改内容   : 新建
*****************************************************************************/
typedef NAS_MSCC_PIF_RF_AVAILABLE_IND_STRU MMC_MSCC_RF_AVAILABLE_IND_STRU;

/*****************************************************************************
 结构名    : MSCC_MMC_SRV_ACQ_REQ_STRU
 结构说明  : 业务触发搜网指示
 1.日    期   : 2014年5月28日
   作    者   : h00246512
   修改内容   : 新建
*****************************************************************************/
typedef NAS_MSCC_PIF_SRV_ACQ_REQ_STRU MSCC_MMC_SRV_ACQ_REQ_STRU;

/*****************************************************************************
 结构名    : MMC_MSCC_SRV_ACQ_CNF_STRU
 结构说明  : 业务触发搜网结果
 1.日    期   : 2014年5月28日
   作    者   : h00246512
   修改内容   : 新建
*****************************************************************************/
typedef NAS_MSCC_PIF_SRV_ACQ_CNF_STRU MMC_MSCC_SRV_ACQ_CNF_STRU;

/*****************************************************************************
 结构名    : MSCC_MMC_BEGIN_SESSION_NOTIFY_STRU
 结构说明  : 业务触发搜网开始指示
 1.日    期   : 2014年5月28日
   作    者   : h00246512
   修改内容   : 新建
*****************************************************************************/
typedef NAS_MSCC_PIF_BEGIN_SESSION_NOTIFY_STRU MSCC_MMC_BEGIN_SESSION_NOTIFY_STRU;

/*****************************************************************************
 结构名    : MSCC_MMC_END_SESSION_NOTIFY_STRU
 结构说明  : 业务触发搜网结束指示
 1.日    期   : 2014年5月28日
   作    者   : h00246512
   修改内容   : 新建
*****************************************************************************/
typedef NAS_MSCC_PIF_END_SESSION_NOTIFY_STRU MSCC_MMC_END_SESSION_NOTIFY_STRU;

/*****************************************************************************
 结构名    : MSCC_MMC_IMS_SRV_INFO_NOTIFY_STRU
 结构说明  : ID_MSCC_MMC_IMS_SRV_INFO_NOTIFY的结构体
 1.日    期   : 2014年11月06日
   作    者   : s00217060
   修改内容   : 新建
*****************************************************************************/
typedef NAS_MSCC_PIF_IMS_SRV_INFO_NOTIFY_STRU MSCC_MMC_IMS_SRV_INFO_NOTIFY_STRU;
/*****************************************************************************
 结构名    : MSCC_MMA_IMS_VOICE_CAP_NOTIFY
 结构说明  : ID_MSCC_MMA_IMS_VOICE_CAP_NOTIFY的结构体
 1.日    期   : 2015年01月27日
   作    者   : y00245242
   修改内容   : 新建
*****************************************************************************/
typedef NAS_MSCC_PIF_IMS_VOICE_CAP_NOTIFY_STRU MSCC_MMA_IMS_VOICE_CAP_NOTIFY_STRU;

/*****************************************************************************
 结构名    : MSCC_MMC_CFPLMN_SET_REQ_STRU
 结构说明  : ID_MSCC_MMC_CPLMN_SET_REQ的结构体
 1.日    期   : 2015年2月4日
   作    者   : f00279542
   修改内容   : 新建
*****************************************************************************/
typedef NAS_MSCC_PIF_CFPLMN_SET_REQ_STRU MSCC_MMC_CFPLMN_SET_REQ_STRU;

/*****************************************************************************
 结构名    : MSCC_MMC_CFPLMN_QUERY_REQ_STRU
 结构说明  : ID_MSCC_MMC_CPLMN_QUERY_REQ的结构体
 1.日    期   : 2015年2月4日
   作    者   : f00279542
   修改内容   : 新建
*****************************************************************************/
typedef NAS_MSCC_PIF_CFPLMN_QUERY_REQ_STRU MSCC_MMC_CFPLMN_QUERY_REQ_STRU;
/*****************************************************************************
 结构名    : MMC_MSCC_CFPLMN_SET_CNF_STRU
 结构说明  : ID_MSCC_MMC_CPLMN_CNF的结构体
 1.日    期   : 2015年2月4日
   作    者   : f00279542
   修改内容   : 新建
*****************************************************************************/
typedef NAS_MSCC_PIF_CFPLMN_SET_CNF_STRU MMC_MSCC_CFPLMN_SET_CNF_STRU;

/*****************************************************************************
 结构名    : MMC_MSCC_CFPLMN_QUERY_CNF_STRU
 结构说明  : ID_MSCC_MMC_CPLMN_QUERY_SCNF的结构体
 1.日    期   : 2015年2月4日
   作    者   : f00279542
   修改内容   : 新建
*****************************************************************************/
typedef NAS_MSCC_PIF_CFPLMN_QUERY_CNF_STRU MMC_MSCC_CFPLMN_QUERY_CNF_STRU;

/*****************************************************************************
 结构名    : MSCC_MMC_PREF_PLMN_QUERY_REQ_STRU
 结构说明  : ID_MSCC_MMC_PREF_PLMN_QUERY_REQ的结构体
 1.日    期   : 2015年02月04日
   作    者   : y00245242
   修改内容   : 新建
*****************************************************************************/
typedef NAS_MSCC_PIF_PREF_PLMN_QUERY_REQ_STRU MSCC_MMC_PREF_PLMN_QUERY_REQ_STRU;

/*****************************************************************************
 结构名    : MMC_MSCC_PREF_PLMN_QUERY_CNF_STRU
 结构说明  : ID_MMC_MSCC_PREF_PLMN_QUERY_CNF的结构体
 1.日    期   : 2015年02月04日
   作    者   : y00245242
   修改内容   : 新建
*****************************************************************************/
typedef NAS_MSCC_PIF_PREF_PLMN_QUERY_CNF_STRU MMC_MSCC_PREF_PLMN_QUERY_CNF_STRU;
/*****************************************************************************
 结构名    : MSCC_MMC_PREF_PLMN_SET_REQ_STRU
 结构说明  : ID_MSCC_MMC_PREF_PLMN_SET_REQ的结构体
 1.日    期   : 2015年02月04日
   作    者   : y00245242
   修改内容   : 新建
*****************************************************************************/
typedef NAS_MSCC_PIF_PREF_PLMN_SET_REQ_STRU MSCC_MMC_PREF_PLMN_SET_REQ_STRU;

/*****************************************************************************
 结构名    : MMC_MSCC_PREF_PLMN_SET_CNF_STRU
 结构说明  : ID_MMC_MSCC_PREF_PLMN_SET_CNF的结构体
 1.日    期   : 2015年02月04日
   作    者   : y00245242
   修改内容   : 新建
*****************************************************************************/
typedef NAS_MSCC_PIF_PREF_PLMN_SET_CNF_STRU MMC_MSCC_PREF_PLMN_SET_CNF_STRU;

/*****************************************************************************
 结构名    : MSCC_MMC_IMS_SWITCH_STATE_IND_STRU
 结构说明  : ID_MSCC_MMC_IMS_SWITCH_STATE_IND的结构体
 1.日    期   : 2015年04月13日
   作    者   : f00179208
   修改内容   : 新建
*****************************************************************************/
typedef NAS_MSCC_PIF_IMS_SWITCH_STATE_IND_STRU MSCC_MMC_IMS_SWITCH_STATE_IND_STRU;

/*****************************************************************************
 结构名    : MSCC_MMC_VOICE_DOMAIN_CHANGE_IND_STRU
 结构说明  : ID_MSCC_MMC_VOICE_DOMAIN_CHANGE_IND的结构体
 1.日    期   : 2015年04月13日
   作    者   : f00179208
   修改内容   : 新建
*****************************************************************************/
typedef NAS_MSCC_PIF_VOICE_DOMAIN_CHANGE_IND_STRU MSCC_MMC_VOICE_DOMAIN_CHANGE_IND_STRU;
/*****************************************************************************
 结构名    : MSCC_MMC_HRPD_SYS_STRU
 协议表格  :
 ASN.1描述 :
 结构说明  : HRPD下SubnetID
*****************************************************************************/
typedef struct
{
    VOS_UINT8                               aucSubnetId[MSCC_MMC_HRPD_SUBNET_MAX_LEN];
    VOS_UINT16                              usBandClass;
    VOS_UINT16                              usFreq;
}MSCC_MMC_HRPD_SYS_STRU;

/** ****************************************************************************
 * Name        : MSCC_MMC_BG_SEARCH_REQ_STRU
 *
 * Description :
 *******************************************************************************/
typedef struct
{
    MSCC_MSG_HEADER_STRU                stMsgHeader;        /* _H2ASN_Skip */
    VOS_UINT16                          usOpId;
    VOS_UINT8                           aucReserve[2];
    VOS_RATMODE_ENUM_UINT32             enRatMode;
}MSCC_MMC_BG_SEARCH_REQ_STRU;

/** ****************************************************************************
 * Name        : MSCC_MMC_INTERSYS_HRPD_NTF_STRU
 *
 * Description :
 *******************************************************************************/
typedef struct
{
    MSCC_MSG_HEADER_STRU                stMsgHeader;        /* _H2ASN_Skip */
    VOS_UINT16                          usOpId;
    VOS_UINT8                           aucReserve[2];
}MSCC_MMC_INTERSYS_HRPD_NTF_STRU;

/** ****************************************************************************
 * Name        : MSCC_MMC_MMSS_INFO_NTF_STRU
 *
 * Description : Feature GUL MMSS needs not be support at present, the content
 * of this interface is left.
 *******************************************************************************/
typedef struct
{
    MSCC_MSG_HEADER_STRU                stMsgHeader;        /* _H2ASN_Skip */
    VOS_UINT16                          usOpId;
    VOS_UINT8                           aucReserve[2];
}MSCC_MMC_MMSS_INFO_NTF_STRU;

/** ****************************************************************************
 * Name        : MMC_MSCC_BG_SEARCH_CNF_STRU
 *
 * Description : This message should contain all existed subnet of HRPD.
 *******************************************************************************/
typedef struct
{
    MSCC_MSG_HEADER_STRU                stMsgHeader;        /* _H2ASN_Skip */
    VOS_UINT16                          usOpId;
    VOS_UINT8                           ucHrpdSysNum;
    VOS_UINT8                           aucReserve[1];
    MSCC_MMC_BG_SRCH_RESULT_ENUM_UINT32 enRslt;
    MSCC_MMC_HRPD_SYS_STRU              astHrpdSysList[MSCC_MMC_BG_HRPD_MAX_SYS_NUM];
}MMC_MSCC_BG_SEARCH_CNF_STRU;

/** ****************************************************************************
 * Name        : MSCC_MMC_STOP_BG_SEARCH_REQ_STRU
 *
 * Description :
 *******************************************************************************/
typedef struct
{
    MSCC_MSG_HEADER_STRU                stMsgHeader;        /* _H2ASN_Skip */
    VOS_UINT16                          usOpId;
    VOS_UINT8                           aucReserve[2];
}MSCC_MMC_STOP_BG_SEARCH_REQ_STRU;

/** ****************************************************************************
 * Name        : MMC_MSCC_STOP_BG_SEARCH_CNF_STRU
 *
 * Description :
 *******************************************************************************/
typedef struct
{
    MSCC_MSG_HEADER_STRU                stMsgHeader;        /* _H2ASN_Skip */
    VOS_UINT16                          usOpId;
    VOS_UINT8                           aucReserve[2];
}MMC_MSCC_STOP_BG_SEARCH_CNF_STRU;

/** ****************************************************************************
 * Name        : MMC_MSCC_PREF_PLMN_INFO_IND_STRU
 *
 * Description : This message should contain pref plmn info:HPLMN/EHPLMN/UPLMN/OPLMN.
 *******************************************************************************/
typedef struct
{
    MSCC_MSG_HEADER_STRU                                    stMsgHeader;        /* _H2ASN_Skip */
    VOS_UINT16                                              usOpId;
    VOS_UINT8                                               aucReserve[1];
    NAS_MSCC_PIF_PREF_PLMN_TYPE_ENUM_UINT8                  enPrefPlmnType;
    NAS_MSCC_PIF_SIM_EHPLMN_INFO_STRU                       stEhplmnInfo;
    NAS_MSCC_PIF_SIM_USERPLMN_INFO_STRU                     stUplmnInfo;
    NAS_MSCC_PIF_SIM_OPERPLMN_INFO_STRU                     stOplmnInfo;
}MMC_MSCC_PREF_PLMN_INFO_IND_STRU;

/** ****************************************************************************
 * Name        : ID_MMC_MSCC_MMSS_LTE_UNAVAILABLE_STRU_IND
 *
 * Description : This message is used to notify mscc lte is not available for mmss
 *******************************************************************************/
typedef struct
{
    MSCC_MSG_HEADER_STRU                                    stMsgHeader;        /* _H2ASN_Skip */
    VOS_UINT16                                              usOpId;
    MSCC_MMC_MMSS_LTE_UNAVIALBLE_REASON_ENUM_UINT8          enReason;
    VOS_UINT8                                               aucReserve[1];
}MMC_MSCC_MMSS_LTE_UNAVAILABLE_IND_STRU;


/** ****************************************************************************
 * Name        : ID_MSCC_MMC_PLMN_PRI_CLASS_QUERY_REQ
 *
 * Description : specify the plmn list info to query each plmn pri class
 *******************************************************************************/
typedef struct
{
    MSCC_MSG_HEADER_STRU                                    stMsgHeader;        /* _H2ASN_Skip */
    VOS_UINT16                                              usOpId;
    VOS_UINT8                                               aucReserve[2];
    NAS_MSCC_PIF_SEARCHED_PLMN_LIST_INFO_STRU               stPlmnListInfo;
}MSCC_MMC_PLMN_PRI_CLASS_QUERY_REQ_STRU;

/** ****************************************************************************
 * Name        : ID_MMC_MSCC_PLMN_PRI_CLASS_QUERY_CNF
 *
 * Description : query the plmn list info with pri class type
 *******************************************************************************/
typedef struct
{
    MSCC_MSG_HEADER_STRU                                    stMsgHeader;        /* _H2ASN_Skip */
    VOS_UINT16                                              usOpId;
    VOS_UINT8                                               aucReserve[2];
    NAS_MSCC_PIF_PLMN_PRI_CLASS_LIST_INFO_STRU              stPlmnPriClassList;
}MMC_MSCC_PLMN_PRI_CLASS_QUERY_CNF_STRU;


/** ****************************************************************************
 * Name        : MSCC_MMC_AUTO_RESEL_SET_REQ_STRU
 *
 * Description : send mmc auto resel set
 *******************************************************************************/
typedef struct
{
    MSCC_MSG_HEADER_STRU                stMsgHeader;        /* _H2ASN_Skip */
    VOS_UINT8                           ucActiveFlg;
    VOS_UINT8                           aucReserved[3];
}MSCC_MMC_AUTO_RESEL_SET_REQ_STRU;

/*****************************************************************************
 结构名    : MSCC_MMC_DPLMN_SET_REQ_STRU
 结构说明  : ID_MSCC_MMC_DPLMN_SET_REQ的结构体
  1.日    期   : 2015年10月12日
    作    者   : n00355355
    修改内容   : 新建
*****************************************************************************/
typedef NAS_MSCC_PIF_DPLMN_SET_REQ_STRU MSCC_MMC_DPLMN_SET_REQ_STRU;

/*****************************************************************************
 结构名    : MMC_MSCC_DPLMN_SET_CNF_STRU
 结构说明  : ID_MMC_MSCC_DPLMN_SET_CNF的结构体
  1.日    期   : 2015年10月9日
    作    者   : n00355355
    修改内容   : 新建
*****************************************************************************/
typedef NAS_MSCC_PIF_DPLMN_SET_CNF_STRU MMC_MSCC_DPLMN_SET_CNF_STRU;

/*****************************************************************************
 结构名    : MSCC_MMC_GET_GEO_REQ_STRU
 结构说明  : ID_MSCC_MMC_GET_GEO_REQ的结构体
  1.日    期   : 2015年5月18日
    作    者   : s00217060
    修改内容   : 新建
*****************************************************************************/
typedef NAS_MSCC_PIF_GET_GEO_REQ_STRU MSCC_MMC_GET_GEO_REQ_STRU;

/*****************************************************************************
 结构名    : MMC_MSCC_GET_GEO_CNF_STRU
 结构说明  : ID_MMC_MSCC_GET_GEO_CNF的结构体
  1.日    期   : 2015年5月18日
    作    者   : s00217060
    修改内容   : 新建
*****************************************************************************/
typedef NAS_MSCC_PIF_GET_GEO_CNF_STRU MMC_MSCC_GET_GEO_CNF_STRU;

/*****************************************************************************
 结构名    : MSCC_MMC_STOP_GET_GEO_REQ_STRU
 结构说明  : ID_MSCC_MMC_STOP_GET_GEO_REQ的结构体
  1.日    期   : 2015年06月01日
    作    者   : f00179208
    修改内容   : 新建
*****************************************************************************/
typedef NAS_MSCC_PIF_STOP_GET_GEO_REQ_STRU MSCC_MMC_STOP_GET_GEO_REQ_STRU;

/*****************************************************************************
 结构名    : MMC_MSCC_STOP_GET_GEO_CNF_STRU
 结构说明  : ID_MMC_MSCC_STOP_GET_GEO_CNF的结构体
  1.日    期   : 2015年06月01日
    作    者   : f00179208
    修改内容   : 新建
*****************************************************************************/
typedef NAS_MSCC_PIF_STOP_GET_GEO_CNF_STRU MMC_MSCC_STOP_GET_GEO_CNF_STRU;


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
    VOS_UINT32   enMsgID;             /*_H2ASN_MsgChoice_Export MSCC_MMC_MSG_ID_ENUM_UINT32 */
    VOS_UINT8    aucMsgBlock[4];

    /***************************************************************************
        _H2ASN_MsgChoice_When_Comment          MSCC_MMC_MSG_ID_ENUM_UINT32
        ****************************************************************************/
}MSCC_MMC_MSG_DATA;
/*_H2ASN_Length UINT32*/

typedef struct
{
    VOS_MSG_HEADER
    MSCC_MMC_MSG_DATA   stMsgData;
}MsccMmcInterface_MSG;

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
