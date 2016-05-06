/******************************************************************************

                  版权所有 (C), 2001-2011, 华为技术有限公司

 ******************************************************************************
  文 件 名   : MnMsgSmCommProc.h
  版 本 号   : 初稿
  作    者   : 周君 40661
  生成日期   : 2008年2月20日
  最近修改   :
  功能描述   : 提供短信模块公共的定义和接口
  函数列表   :
  修改历史   :
  1.日    期   : 2008年2月20日
    作    者   : 周君 40661
    修改内容   : 创建文件
  2.日    期   : 2008年6月16日
    作    者   : 傅映君 62575
    修改内容   : 问题单号：AT2D03830, 修改en_NV_Item_SMS_SERVICE_Para项读写相关代码
  3.日    期   : 2008年8月14日
    作    者   : 傅映君 62575
    修改内容   : 问题单号 AT2D03741,编程规范问题：   1。枚举类型定义   2。全局变量的外部声名   3。文件或函数的注释问题；   打印信息不完整   1。增加调试打印代码
  4.日    期   : 2008年8月14日
    作    者   : 傅映君 62575
    修改内容   : 问题单号 AT2D04609,CMMS命令的增加；
  5.日    期   : 2008年10月10日
    作    者   : f62575
    修改内容   : 问题单号：AT2D06152（AT2D06151）, USIMM优化合入后，SMSP文件相关读写操作失败
  6.日    期   : 2008年12月25日
    作    者   : 傅映君 62575
    修改内容   : 问题单号 AT2D07869, SIM卡中短信息存储区满后接收一条需要存储的短信溢出，短信模块写(U)SIM卡的SMSS文件失败
  7.日    期   : 2009年3月25日
    作    者   : 周君 40661
    修改内容   : 问题单号 AT2D08875,PS优先域发送短信，失败
  8.日    期   : 2009年4月1日
    作    者   : 周君 40661
    修改内容   : 问题单号:AT2D09786, 用AT+CMGD=,4删除短信时，长时间不回应，导致自动化脚本检测不到单板
  9.日    期   : 2009年05月11日
    作    者   : f62575
    修改内容   : 问题单号：AT2D11136，PICS表设置为仅支持SM存储，执行GCF测试用例34.2.5.3，测试用例失败
 10.日    期   : 2009年05月15日
    作    者   : f62575
    修改内容   : 问题单号：AT2D11703，由于勾包过大,申请内存失败,导致单板复位
 11.日    期   : 2009年7月18日
    作    者   : z40661
    修改内容   : 终端可配置需求合入
 12.日    期   : 2009年07月24日
    作    者   : f62575
    修改内容   : 问题单号：AT2D13258，执行AT&F0恢复出厂设置后，短信功能不可用
 13.日    期   : 2009年08月02日
    作    者   : f62575
    修改内容   : 问题单号：AT2D13420，短信SIM卡相关设置过程中，UE软复位导致设置操作无返回；
 14.日    期   : 2009年08月7日
    作    者   : f62575
    修改内容   : STK特性合入
 15.日    期   : 2009年10月28日
    作    者   : f62575
    修改内容   : AT2D15641, STK短信发送需要支持长短信的分段发送功能
 16.日    期   : 2009年12月31日
    作    者   : f62575
    修改内容   : PC工程桩合入；
 17.日    期   : 2009年12月16日
    作    者   : f62575
    修改内容   : AT2D16304, STK PP DOWN功能完善和SMS相关的(U)SIM文件REFRESH
 18.日    期   : 2010年2月23日
    作    者   : f62575
    修改内容   : 问题单号: AT2D16941：增加短信功能任意点回放功能
 19.日    期   : 2010年04月30日
    作    者   : F62575
    修改内容   : 问题单号AT2D15403
                 短信以CMT方式上报且CSMS配置为1时若应用不下发CNMA命令确认新短信接收,
                 则后续短信既不上报也不存储到本地;
 20.日    期   : 2010年6月30日
    作    者   : 傅映君
    修改内容   : 问题单号DTS2010071500596，STK短信的定制缓存
******************************************************************************/
#ifndef __MNMSGCOMMPROC_H__
#define __MNMSGCOMMPROC_H__


/*****************************************************************************
  1 头文件包含
*****************************************************************************/
#include  "vos.h"
#include  "TafTypeDef.h"
#include  "MnMsgApi.h"
#include  "UsimPsInterface.h"
#include  "MnComm.h"

/* Modified by z00161729 for DCM定制需求和遗留问题, 2012-8-20, begin */
#include "NasSms.h"

#if (FEATURE_ON == FEATURE_LTE)
#include "LmmSmsInterface.h"
#endif
/* Modified by z00161729 for DCM定制需求和遗留问题, 2012-8-20, end */

/* Added by Y00213812 for VoLTE_PhaseI 项目, 2013-07-08, begin */
#include "siappstk.h"
/* Added by Y00213812 for VoLTE_PhaseI 项目, 2013-07-08, end */

#include "TafMmaInterface.h"

#ifdef __cplusplus
#if __cplusplus
extern "C" {
#endif
#endif

#pragma pack(4)

/*****************************************************************************
  2 常量定义
*****************************************************************************/
/*----------------------------EF ID(31.102)-------------------------------------*/
#define  EF_SMS_INVALID_ID                                  0xFFFF

/*----------------------------EF SMS STATUS(31.102)-----------------------------*/
#define  EF_SMS_STATUS_FREE_SPACE                           0x00                /*空位置*/
#define  EF_SMS_STATUS_USED_SPACE                           0x01                /*已使用的位置*/
#define  EF_SMS_STATUS_MT_READ                              0x01                /*已收到且阅读的消息*/
#define  EF_SMS_STATUS_MT_TO_BE_READ                        0x03                /*已收到未阅读的消息*/
#define  EF_SMS_STATUS_MO_TO_BE_SEND                        0x07                /*MO未发送的消息*/
#define  EF_SMS_STATUS_MO_SEND_TO_NT                        0x05                /*MO已发送到网侧的消息*/
#define  EF_SMS_STATUS_NO_SRR                               0x05                /*未请求状态报告的消息*/
#define  EF_SMS_STATUS_SRR_NOT_RCV                          0x0D                /*请求状态报告但未收到状态报告的消息*/
#define  EF_SMS_STATUS_SRR_RCV_NOT_STOR                     0x15                /*已收到状态报告未存储的消息*/
#define  EF_SMS_STATUS_SRR_RCV_STOR                         0x1D                /*已收到状态报告且存储的消息*/

/*-------------------------EF SMS STATUS REPORT(31.102)-------------------------*/
#define  EF_SMS_STATUS_REPORT_EMPTY                         0x00                /*状态报告为空*/

#define  MN_MSG_MAX_TPDU_LEN                                232
#define  MN_MSG_TPMR_POS                                    0x01

#define  MN_MSG_EFSMS_LEN                                   176                 /*EFSMS文件的长度*/
#define  MN_MSG_EFSMSR_LEN                                  30                  /*EFSMSR文件的长度*/

#define  MN_MSG_NO_AVAILABLE_REC                            0xff                /*查看USIM或NVIM中空闲的记录数*/
#define  MN_MSG_NO_AVAILABLE_SMS_REC                        0xffffffff                /*查看USIM或NVIM中空闲的记录数*/

#define  MN_MSG_SIM_EXIST                                   1                   /*存在SIM卡*/
#define  MN_MSG_SIM_NOT_EXIST                               0                   /*不存在SIM卡*/

#define  MN_MSG_MAX_DELETE_REC_NUM                          10                  /*SMA一次能够删除的记录数目*/
#define  MN_MSG_MAX_ORG_REC_NUM                             10                  /*保留内存中原始短信的条数*/

#define  MN_MSG_MAX_RPDATA_LEN                              248                 /*23040 7.3.1.2 RP DATA (Mobile Station to Network)长度*/

#define  MN_MSG_USIM_DEF_REC                                0

#define MN_MSG_SIM_MEM_FULL_SET                             0xFE
#define MN_MSG_SIM_MEM_FULL_UNSET                           0xFF

/*DEVICE ID*/
#define  MN_MSG_DEVICE_NETWORK                              83
#define  MN_MSG_DEVICE_UICC                                 81

#define  MN_MSG_NV_SMSP_VOLUME                              1
#define  MN_MSG_FILE_NONE_REC                               0

#define MN_MSG_PC_REPLAY_MSG_PART1                          (ID_TAF_PC_REPLAY_BASE + 0x01)              /* 为PC工程回放定义的消息 */
#define MN_MSG_PC_REPLAY_MSG_PART2                          (ID_TAF_PC_REPLAY_BASE + 0x02)              /* 为PC工程回放定义的消息 */
#define MN_MSG_PC_REPLAY_MSG_PART3                          (ID_TAF_PC_REPLAY_BASE + 0x03)              /* 为PC工程回放定义的消息 */

#define MN_MSG_USIM_ENVELOPE_RSP_UNKNOWN_ERROR              (0x6F00)            /* 规避联通SIM卡MO SMS Ctrl错误 */

#ifdef __PS_WIN32_RECUR__
VOS_UINT32 NAS_MSG_RestoreContextData(struct MsgCB * pMsg);
#endif

#define MN_MSG_MAX_CHG_SM_STATE_NUM                         20
/*****************************************************************************
  3 类型定义
*****************************************************************************/
/*****************************************************************************
 枚举名    : MN_MSG_MT_CUSTOMIZE_ENUM
 结构说明  : 短信接收定制类型
  1.日    期   : 2012年11月07日
    作    者   : f62575
    修改内容   : 短信接收定制标志
                 MN_MSG_MT_CUSTOMIZE_NONE       无定制；
                 MN_MSG_MT_CUSTOMIZE_DCM        DCM定制
*****************************************************************************/
enum MN_MSG_MT_CUSTOMIZE_ENUM
{
    MN_MSG_MT_CUSTOMIZE_NONE,
    MN_MSG_MT_CUSTOMIZE_DCM,
    MN_MSG_MT_CUSTOMIZE_BUTT
} ;
typedef VOS_UINT8 MN_MSG_MT_CUSTOMIZE_ENUM_UINT8;

/*****************************************************************************
 枚举名    : MN_MSG_MO_STATE_ENUM
 结构说明  : 短信发送实体状态
             MN_MSG_MO_STATE_WAIT_FDN_CHECK_RSP: 等待FDN 检查结果；
             MN_MSG_MO_STATE_WAIT_SMS_CTRL_RSP:  等待SMS MO CONTROL 检查结果；
             MN_MSG_MO_STATE_WAIT_REPORT_IND:    等待短信发送网络的确认结果；
1.日    期   : 2012年02月23日
  作    者   : 傅映君/f62575
  修改内容   : 新增MN_MSG_MO_STATE_WAIT_FDN_CHECK_RSP状态
*****************************************************************************/
enum MN_MSG_MO_STATE_ENUM
{
    MN_MSG_MO_STATE_NULL                                    = 0,                /*空闲*/
    MN_MSG_MO_STATE_WAIT_FDN_CHECK_RSP                      = 1,
    MN_MSG_MO_STATE_WAIT_SMS_CTRL_RSP                       = 2,                /*等待USIM的MO SMS CONTROL 过程响应消息*/
    MN_MSG_MO_STATE_WAIT_REPORT_IND                         = 3,                /*等待报告指示*/
    MN_MSG_MO_STATE_MAX
} ;
typedef VOS_UINT8   MN_MSG_MO_STATE_ENUM_U8;

enum MN_MSG_MT_STATE_ENUM
{
    MN_MSG_MT_STATE_NULL                                    = 0,                /*空闲*/
    MN_MSG_MT_STATE_WAIT_REPORT_REQ                         = 2,                /*等待报告指示*/
    MN_MSG_MT_STATE_MAX
};
typedef VOS_UINT8   MN_MSG_MT_STATE_ENUM_U8;

enum MN_MSG_MO_TYPE_ENUM
{
    MN_MSG_MO_TYPE_MO,
    MN_MSG_MO_TYPE_SMMA,
    MN_MSG_MO_TYPE_BUFFER_STK,
    MN_MSG_MO_TYPE_MAX
};
typedef VOS_UINT8   MN_MSG_MO_TYPE_ENUM_U8;

enum MN_MSG_MO_SEND_FROM_ENUM
{
    MN_MSG_MO_SEND_FROM_CLIENT,
    MN_MSG_MO_SEND_FROM_MEM,
    MN_MSG_MO_SEND_FROM_MAX
};
typedef VOS_UINT8 MN_MSG_MO_SEND_FROM_ENUM_U8;

enum MN_MSG_USIM_ACTION_ENUM
{
    MN_MSG_USIM_READ,
    MN_MSG_USIM_LIST,
    MN_MSG_USIM_WRITE,
    MN_MSG_USIM_DELETE,
    MN_MSG_USIM_WRITE_EFSMSP,
    MN_MSG_USIM_DELETE_EFSMSP,
    MN_MSG_USIM_MODIFYSTATUS,
    MN_MSG_USIM_DELETE_STARPT,
    MN_MSG_USIM_RCVNEWMSG,
    MN_MSG_USIM_RCVSTARPT,
    MN_MSG_USIM_SEND,
    MN_MSG_USIM_RCVMORPT,
    MN_MSG_USIM_SET_EFSMSS,
    MN_MSG_USIM_MAX
};
typedef VOS_UINT8 MN_MSG_USIM_ACTION_ENUM_U8;

enum MN_MSG_SET_USIM_ENUM
{
    MN_MSG_SET_USIM_LIST,
    MN_MSG_SET_USIM_DELETE,
    MN_MSG_SET_USIM_DELETE_BEGIN,
    MN_MSG_SET_USIM_DELETE_STARPT,
    MN_MSG_SET_USIM_DELETE_STARPT_BEGIN,
    MN_MSG_SET_USIM_DELETE_EFSMSP,
    MN_MSG_SET_USIM_MAX
};
typedef VOS_UINT8 MN_MSG_SET_USIM_ENUM_U8;

enum MN_MSG_USIM_POWER_STATE_ENUM
{
    MN_MSG_USIM_POWER_BEGIN,
    MN_MSG_USIM_POWER_WAIT_EFSMSS,
    MN_MSG_USIM_POWER_WAIT_EFSMSP,
    MN_MSG_USIM_POWER_WAIT_EFSMSREC,
    MN_MSG_USIM_POWER_WAIT_EFSMS,
    MN_MSG_USIM_POWER_WAIT_EFSMSR,
    MN_MSG_USIM_POWER_ON
};
typedef VOS_UINT8 MN_MSG_USIM_POWER_STATE_ENUM_U8;

enum MN_MSG_SEND_FAIL_FLAG
{
    MN_MSG_SEND_FAIL_NO_DOMAIN,
    MN_MSG_SEND_FAIL_PS_DOMAIN,
    MN_MSG_SEND_FAIL_CS_DOMAIN,
    MN_MSG_SEND_FAIL_CSPS_DOMAIN
};
typedef VOS_UINT8 MN_MSG_SEND_FAIL_FLAG_U8;

enum MN_MSG_DOMAIN_AVAIL_FLAG
{
    MN_MSG_NO_DOMAIN_AVAIL,
    MN_MSG_PS_DOMAIN_AVAIL,
    MN_MSG_CS_DOMAIN_AVAIL,
    MN_MSG_CSPS_DOMAIN_AVAIL
};
typedef VOS_UINT8 MN_MSG_DOMAIN_AVAIL_FLAG_U8;

enum MN_MSG_RETRY_FLAG
{
    MN_MSG_RETRY_OFF,                                                           /* 重发功能未开启 */
    MN_MSG_RETRY_BEGIN,                                                         /* 重发开始 */
    MN_MSG_RETRY_END                                                            /* 重发结束 */
};
typedef VOS_UINT8 MN_MSG_RETRY_FLAG_U8;



/*****************************************************************************
 结构名    : MN_MSG_SMS_BUFFER_CAP_STRU
 结构说明  : MSG的短信发送实体缓存能力
             ucBufferNum 最多可以缓存的待发送短信数
  1.日    期   : 2012年09月07日
    作    者   : f62575
    修改内容   : 创建
*****************************************************************************/
typedef struct
{
    VOS_UINT8                           ucBufferNum;
    VOS_UINT8                           aucReserved1[3];
}MN_MSG_SMS_BUFFER_CAP_STRU;

typedef struct
{
    MN_CLIENT_ID_T                      clientId;
    MN_OPERATION_ID_T                   opId;
    VOS_UINT8                           ucRecIndex;                             /*操作USIM的记录数*/
    VOS_UINT16                          usEfId;                                 /*操作文件的ID*/
    MN_MSG_DELETE_TYPE_ENUM_U8          enDeleteType;                           /*操作是Delete时才有效*/
    MN_MSG_USIM_ACTION_ENUM_U8          enSmaUsimAction;                        /*对USIM进行的操作调用的函数*/
}MN_MSG_USIM_INFO_STRU;

typedef struct
{
    VOS_BOOL                            bCreateNode;                                  /*该记录是否已被使用*/
    MN_MSG_USIM_INFO_STRU               stUsimInfo;
}MN_MSG_WRITE_USIM_INFO_STRU;

typedef struct
{
    VOS_BOOL                            bUsed;                                  /*该记录是否已被使用*/
    MN_MSG_USIM_INFO_STRU               stUsimInfo;
}MN_MSG_SET_USIM_INFO_STRU;

typedef struct
{
    VOS_UINT8                           ucUsimStatus;                           /*SIM卡状态*/
    MN_MSG_USIM_POWER_STATE_ENUM_U8     enPowerState;                           /*标识是否在上电过程中*/
    VOS_UINT8                           aucReserve[2];
} MN_MSG_USIM_STATUS_INFO_STRU;

typedef struct
{
    VOS_BOOL                            bEfSmssFlag;                            /*是否支持EFSMSS文件*/
    VOS_BOOL                            bEfSmsFlag;                             /*SMS Storage 存在与否*/
    VOS_BOOL                            bEfSmsrFlag;                            /*SMSR Storage 存在与否*/
    VOS_BOOL                            bEfSmspFlag;                            /*SMSP 存在与否*/
    VOS_BOOL                            bMoSmsCtrlFlag;                         /*是否支持MO-SMS Control by USIM*/
    VOS_BOOL                            bSmsPpDataFlag;                         /*是否支持Data download via SMS-PP*/
}MN_MSG_USIM_EFUST_INFO_STRU;

 /* Added by l00208543 for V9R1 STK升级, 2013-07-09, begin */
typedef struct
{
    VOS_UINT8                           ucEfSmssNeedRefreshFlag;                            /*EFSMSS文件是否需要更新*/
    VOS_UINT8                           ucEfSmsNeedRefreshFlag;                             /*SMS Storage 文件是否需要更新*/
    VOS_UINT8                           ucEfSmsrNeedRefreshFlag;                        /*SMSR Storage文件是否需要更新*/
    VOS_UINT8                           ucEfSmspNeedRefreshFlag;                            /*SMSP文件是否需要更新*/
}MN_MSG_USIM_EFUST_NEED_REFRESH_STRU;

 /* Added by l00208543 for V9R1 STK升级, 2013-07-09, end */


typedef struct
{
    VOS_BOOL                            bUsed;                                  /*该记录是否有效*/
    MN_MSG_SRV_PARAM_STRU               stParm;                                 /*EFSMSP的内容*/
}MN_MSG_USIM_EFSMSP_DTL_INFO_STRU;

typedef struct
{
    VOS_UINT8                           ucLastUsedTpMr;                         /*前一次使用的MR值*/
    MN_MSG_MEM_FLAG_ENUM_U8             enMemCapExcNotFlag;                     /*存储器能力溢出通知标志*/
    VOS_UINT8                           aucRFU[253];
}MN_MSG_SMSS_INFO_STRU;

typedef struct
{
    MN_CLIENT_ID_T                      clientId;
    MN_OPERATION_ID_T                   opId;
    MN_MSG_MO_STATE_ENUM_U8             enSmaMoState;                           /*Mo时SMA状态*/
    VOS_BOOL                            bEnvelopePending;                       /*MO SMS CONTROL功能启动时,是否正在等待USIM的回复*/
    VOS_UINT8                           ucMr;                                   /*Msg Reference*/
    MN_MSG_SEND_DOMAIN_ENUM_U8          enHopeSendDomain;
    MN_MSG_SEND_DOMAIN_ENUM_U8          enSendDomain;
    MN_MSG_MEM_STORE_ENUM_U8            enSaveArea;                             /*保存的位置,USIM,NVIM或是不保存*/
    VOS_UINT32                          ulSaveIndex;                            /*存入USIM或NVIM的索引号*/
    MN_MSG_TPDU_TYPE_ENUM_U8            enTpduType;
    MN_MSG_MO_TYPE_ENUM_U8              enSmsMoType;                            /*表明是发送短信还是SMMA*/
    VOS_UINT8                           aucReserve1[2];
    VOS_BOOL                            bReportFlag;                            /*表明是否需要上报,仅对SMMA有效*/
    VOS_BOOL                            bStaRptInd;
    VOS_UINT8                           aucRpDataInfo[MN_MSG_MAX_RPDATA_LEN];   /*23040 7.3.1.2 RP DATA (Mobile Station to Network)的数据或23040 7.3.2 RP SMMA的数据*/
    VOS_UINT8                           ucRpDataLen;
    VOS_UINT8                           aucReserve2[3];
    /* Added by y00245242 for VoLTE_PhaseI  项目, 2013-7-11, begin */
    TAF_MSG_SIGNALLING_TYPE_ENUM_UINT32 enMsgSignallingType;
    /* Added by y00245242 for VoLTE_PhaseI  项目, 2013-7-11, end */
} MN_MSG_MO_ENTITY_STRU;

typedef struct
{
    MN_MSG_MT_STATE_ENUM_U8             enSmaMtState;
    MN_MSG_TP_PID_TYPE_ENUM_U8          enPid;
    MN_MSG_RCV_DOMAIN_ENUM_U8           enRcvDomain;
    VOS_UINT8                           aucReserve[1];
    MN_MSG_DCS_CODE_STRU                stDcs;
    /* Added by y00245242 for VoLTE_PhaseI  项目, 2013-7-11, begin */
    TAF_MSG_SIGNALLING_TYPE_ENUM_UINT32 enMsgSignallingType;
    /* Added by y00245242 for VoLTE_PhaseI  项目, 2013-7-11, end */
}MN_MSG_MT_ENTITY_STRU;

typedef struct
{
    VOS_BOOL                            bUsed;                                  /*是否使用*/
    MN_MSG_MO_ENTITY_STRU               stMoInfo;                               /*短信信息*/
    VOS_UINT8                           aucEfSmContent[MN_MSG_EFSMS_LEN];
}MN_MSG_STORE_MSG_STRU;

/*****************************************************************************
 结构名    : MN_MSG_MO_BUFFER_STRU
 结构说明  : 发送短信的缓存结构体
				ulTotal		允许缓存的短信总数；
				pstMoBuffer 缓存的短信指针；
  1.日    期   : 2012年04月12日
    作    者   : f62575
    修改内容   : 创建
*****************************************************************************/
typedef struct
{
    VOS_UINT32                          ulTotal;
    MN_MSG_STORE_MSG_STRU              *pstMoBuffer;
}MN_MSG_MO_BUFFER_STRU;

typedef struct
{
    VOS_UINT32                          ulRetryPeriod;                          /*短信重发的周期*/
    VOS_UINT32                          ulRetryInterval;                        /*短信重发的时间间隔*/
    VOS_UINT8                           ucSmsRetryCmSrvRejNum;
    VOS_UINT8                           aucSmsRetryCmSrvRejCause[TAF_NVIM_SMS_RETRY_CAUSE_MAX_NUM];
}MN_MSG_RETRY_INFO_STRU;

typedef struct
{
    VOS_UINT8                           aucRpDataInfo[MN_MSG_MAX_RPDATA_LEN];   /*23040 7.3.1.2 RP DATA (Network to Mobile Station*/
    VOS_UINT8                           ucRpDataLen;
    VOS_UINT8                           aucReserve[3];
}MN_MSG_RP_ERR_INFO_STRU;

typedef struct
{
    VOS_UINT8                           ucRpMsgType;
    VOS_UINT8                           ucRpMr;
    MN_MSG_BCD_ADDR_STRU                stOrgAddr;
    MN_MSG_BCD_ADDR_STRU                stDestAddr;
    VOS_UINT8                           ucRpUserDataLen;
    VOS_UINT8                           aucRpUserData[MN_MSG_MAX_TPDU_LEN];
}MN_MSG_RP_DATA_STRU;

typedef struct
{
    VOS_BOOL                            bRpUserDataExist;
    VOS_UINT8                           ucRpMsgType;
    VOS_UINT8                           ucRpMr;
    VOS_UINT8                           ucRpUserDataIei;
    VOS_UINT8                           ucRpUserDataLen;
    VOS_UINT8                           aucRpUserData[MN_MSG_MAX_TPDU_LEN];
}MN_MSG_RP_ACK_STRU;


typedef struct
{
    VOS_BOOL                            bRpUserDataExist;
    VOS_UINT8                           ucRpMsgType;
    VOS_UINT8                           ucRpMr;                                 /*无意义待删除*/
    VOS_UINT8                           ucRpUserDataIei;
    VOS_UINT8                           ucRpUserDataLen;
    VOS_UINT8                           aucRpUserData[MN_MSG_MAX_TPDU_LEN];
    VOS_UINT8                           ucRpCauseLen;
    MN_MSG_RP_CAUSE_STRU                stRpCause;
}MN_MSG_RP_ERR_STRU;

enum
{
    MN_MSG_WRITE_EFSMS_CAUSE_OK,
    MN_MSG_WRITE_EFSMS_CAUSE_MEM_FULL,
    MN_MSG_WRITE_EFSMS_CAUSE_MEM_PROBLEM,
    MN_MSG_WRITE_EFSMS_CAUSE_UNSEPCIFIC,
    MN_MSG_WRITE_EFSMS_CAUSE_MAX
};
typedef VOS_UINT32 MN_MSG_WRITE_EFSMS_CAUSE_ENUM_U32;

/*******************************************************************************
 结构名    : MN_MSG_STORAGE_INFO_STRU
 协议表格  :
 ASN.1描述 :
 结构说明  : 短信或状态报告接收处理方式,存储介质,文件ID,记录在文件中的索引
*******************************************************************************/
typedef struct
{
    MN_MSG_RCVMSG_ACT_ENUM_U8           enRcvSmAct;                             /* action of received status report */
    MN_MSG_MEM_STORE_ENUM_U8            enMemStore;                             /* memory store: NVIM or USIM of received msg*/
    VOS_UINT16                          usFileIndex;                            /* file id: EFSMS or EFSMSR */
    VOS_UINT8                           aucReserved1[2];
    VOS_UINT32                          ulIndex;                                /* index of  status report in file */
}MN_MSG_STORAGE_INFO_STRU;

/*****************************************************************************
 结构名    : TAF_MSG_FDN_INFO_STRU
 结构说明  : SMS业务模块FDN业务特性参数结构
             ulFdnStatus        (U)SIM的FDN业务使能状态
             stFdnConfig        ME的FDN业务NV配置
1.日    期   : 2012年02月23日
  作    者   : f62575
  修改内容   : 创建
2.日    期   : 2013年6月5日
  作    者   : z00161729
  修改内容  : SVLTE 和usim接口调整修改

*****************************************************************************/
typedef struct
{

    TAF_FDN_CONFIG_STRU                 stFdnConfig;
}TAF_MSG_FDN_INFO_STRU;

/*****************************************************************************
  4 宏定义
*****************************************************************************/

/*****************************************************************************
  5 接口函数声明
*****************************************************************************/
/* Added by f62575 for AT Project，2011-10-03,  Begin*/
extern VOS_UINT8                            g_ucSetEfSmsFail;
extern VOS_UINT8                            g_ucNasSmsPsConcatencateFlag;
#if ( VOS_WIN32 == VOS_OS_VER )
extern VOS_UINT8                            g_ucSetEfSmsCapacity;
extern VOS_UINT8                            g_ucSetEfSmssClear;
extern VOS_UINT8                            g_ucSetEfSmspNoRsp;
extern VOS_UINT8                            g_ucSetEfSmsNoResponse;
extern VOS_UINT8                            g_ucDisableMoRetry;
extern MN_MSG_CLASS0_TAILOR_U8              g_enClass0Tailor;
extern VOS_UINT8                            g_ucPpDownloadStub;
#endif
/* Added by f62575 for AT Project，2011-10-03,  End*/



 /* Added by l00208543 for V9R1 STK升级, 2013-07-09, begin */
/*****************************************************************************
 函 数 名  : MN_MSG_SetSmsFileRefreshFlag
 功能描述  : 设置SMS文件是否需要更新的标示
 输入参数  : VOS_BOOL mnFileRefreshFlag,
                          VOS_UINT16    usEfId
 输出参数  : 无
 返 回 值  : 无
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2013年7月9日
    作    者   : l00208543
    修改内容   : V9R1 STK升级

*****************************************************************************/

VOS_VOID MN_MSG_SetSmsFileRefreshFlag (VOS_UINT16 usEfId, VOS_UINT8 ucFileRefreshFlag);
 /* Added by l00208543 for V9R1 STK升级, 2013-07-09, end */

 /* Added by l00208543 for V9R1 STK升级, 2013-07-09, begin */
/*****************************************************************************
 函 数 名  : MN_MSG_GetSmsFileRefreshFlag
 功能描述  : 设置SMS文件是否需要更新的标示
 输入参数  : VOS_UINT16    usEfId
 输出参数  : VOS_BOOL
 返 回 值  : 无
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2013年7月9日
    作    者   : l00208543
    修改内容   : V9R1 STK升级

*****************************************************************************/
VOS_UINT8 MN_MSG_GetSmsFileRefreshFlag (VOS_UINT16 usEfId);
 /* Added by l00208543 for V9R1 STK升级, 2013-07-09, end */


/***********************************************************************
函 数 名  : MN_MSG_CheckUsimStatus
功能描述  : 检查当前USIM的状态是否可以正常发送接收短信
输入参数  : 无
输出参数  : 无
返 回 值  : MN_ERR_NO_ERROR:USIM卡状态正常
            其他:USIM卡状态不正常

调用函数  :
被调函数  :

修改历史      :
 1.日    期   : 2007年12月06日
   作    者   : z40661
   修改内容   : 新生成函数
************************************************************************/
VOS_UINT32 MN_MSG_CheckUsimStatus(VOS_VOID);

/*****************************************************************************
 函 数 名  : MN_MSG_GetMoState
 功能描述  : 获取当前是否有短信正在发送
 输入参数  : 无
 输出参数  : 无
 返 回 值  : MN_MSG_MO_STATE_ENUM_U8  - 当前的enSmaMoState状态

 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2007年12月05日
    作    者   : z40661
    修改内容   : 新生成函数
*****************************************************************************/
MN_MSG_MO_STATE_ENUM_U8 MN_MSG_GetMoState(VOS_VOID);

/* Added by y00245242 for VoLTE_PhaseI  项目, 2013-7-11, begin */
/*****************************************************************************
 函 数 名  : MN_MSG_SetMoRouteStackType
 功能描述  : 设置MO MSG消息从哪种栈路由，即IMS or PS stack
 输入参数  : enSendOnStackType  短消息路由类型
 输出参数  : 无
 返 回 值  : 无

 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2013年7月9日
    作    者   : y0024524
    修改内容   : 新生成函数
*****************************************************************************/
VOS_VOID MN_MSG_SetMoRouteStackType(
    TAF_MSG_SIGNALLING_TYPE_ENUM_UINT32  enMsgSignallingType
);

/*****************************************************************************
 函 数 名  : MN_MSG_GetMoRouteStackType
 功能描述  : 获取MO MSG消息从哪种栈路由，IMS or PS stack
 输入参数  : 无
 输出参数  : 无
 返 回 值  : MN_MSG_ROUTE_STACK_TYPE_ENUM_UINT32  - 消息路由栈类型

 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2013年7月9日
    作    者   : y0024524
    修改内容   : 新生成函数
*****************************************************************************/
TAF_MSG_SIGNALLING_TYPE_ENUM_UINT32 MN_MSG_GetMoRouteStackType(VOS_VOID);
/* Added by y00245242 for VoLTE_PhaseI  项目, 2013-7-11, end */

/*****************************************************************************
 函 数 名  : MN_MSG_GetMtState
 功能描述  : 获取当前是否有短信增长接收
 输入参数  : 无
 输出参数  : 无
 返 回 值  : MN_MSG_MT_STATE_ENUM_U8  - 当前的enSmaMtState状态

 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2007年12月05日
    作    者   : z40661
    修改内容   : 新生成函数
*****************************************************************************/
MN_MSG_MT_STATE_ENUM_U8 MN_MSG_GetMtState(VOS_VOID);

/* Added by s00217060 for VoLTE_PhaseII  项目, 2013-10-21, begin */
VOS_VOID TAF_MSG_SetMtState(
    MN_MSG_MT_STATE_ENUM_U8             enSmaMtState
);
/* Added by s00217060 for VoLTE_PhaseII  项目, 2013-10-21, end */

/* Added by y00245242 for VoLTE_PhaseI  项目, 2013-7-11, begin */
/*****************************************************************************
 函 数 名  : MN_MSG_SetMtRouteStackType
 功能描述  : 设置MT MSG消息从哪种栈路由，即IMS or PS stack
 输入参数  : enSendOnStackType  短消息路由类型
 输出参数  : 无
 返 回 值  : 无

 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2013年7月9日
    作    者   : y0024524
    修改内容   : 新生成函数
*****************************************************************************/
VOS_VOID MN_MSG_SetMtRouteStackType(
    TAF_MSG_SIGNALLING_TYPE_ENUM_UINT32  enMsgSignallingType
);

/*****************************************************************************
 函 数 名  : MN_MSG_GetMtRouteStackType
 功能描述  : 获取MT MSG消息从哪种栈路由，IMS or PS stack
 输入参数  : 无
 输出参数  : 无
 返 回 值  : MN_MSG_ROUTE_STACK_TYPE_ENUM_UINT32  - 消息路由栈类型

 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2013年7月9日
    作    者   : y0024524
    修改内容   : 新生成函数
*****************************************************************************/
TAF_MSG_SIGNALLING_TYPE_ENUM_UINT32 MN_MSG_GetMtRouteStackType(VOS_VOID);
/* Added by y00245242 for VoLTE_PhaseI  项目, 2013-7-11, end */

/*****************************************************************************
 函 数 名  : MN_MSG_GetMoEntity
 功能描述  : 获取当前发送短信的相关状态
 输入参数  : 无
 输出参数  : pstMoEntity:当前发送短信的相关状态
 返 回 值  : 无

 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2007年12月05日
    作    者   : z40661
    修改内容   : 新生成函数
*****************************************************************************/
VOS_VOID MN_MSG_GetMoEntity(
    MN_MSG_MO_ENTITY_STRU               *pstMoEntity
);

/*****************************************************************************
 函 数 名  : MN_MSG_CreateMoInfo
 功能描述  : 根据输入参数创建f_stMsgMoEntity中相关参数
 输入参数  : pstMoEntity    - 当前发送短信相关信息
 输出参数  : 无
 返 回 值  : 无
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2007年12月05日
    作    者   : z40661
    修改内容   : 新生成函数
*****************************************************************************/
VOS_VOID MN_MSG_CreateMoInfo(
    const MN_MSG_MO_ENTITY_STRU         *pstMoEntity
);

/***********************************************************************
函 数 名  : MN_MSG_GetTpMR
功能描述  : 获取当前EFSMSS文件中的TP-MR的值
输入参数  : 无
输出参数  : pucTpMr:当前TP-MR的值,获取USIM,NVIM都失败后,从内存中取
返 回 值  : 无

调用函数  :
被调函数  :

修改历史      :
 1.日    期   : 2007年12月12日
   作    者   : z40661
   修改内容   : 新生成函数
************************************************************************/
VOS_VOID MN_MSG_GetTpMR(
    VOS_UINT8                           *pucTpMr
);

/***********************************************************************
函 数 名  : MN_MSG_AddTpMR
功能描述  : 更新当前EFSMSS文件中的TP-MR的值
输入参数  : 无
输出参数  : 无
返 回 值  : 无

调用函数  :
被调函数  :

修改历史      :
 1.日    期   : 2007年12月12日
   作    者   : z40661
   修改内容   : 新生成函数
************************************************************************/
VOS_VOID MN_MSG_AddTpMR(VOS_VOID);

/*****************************************************************************
 函 数 名  : MN_MSG_GetStoreMsgIndex
 功能描述  : 获取当前是否还有空间缓存短信
 输入参数  : 无
 输出参数  : 无
 返 回 值  : 当前缓存短信的位置

 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2007年12月05日
    作    者   : z40661
    修改内容   : 新生成函数
  2.日    期   : 2010年6月29日
    作    者   : 傅映君
    修改内容   : STK特殊缓存修改
*****************************************************************************/
VOS_UINT32 MN_MSG_GetStoreMsgIndex(VOS_VOID);

/*****************************************************************************
 函 数 名  : MN_MSG_SaveStoreMsg
 功能描述  : 将短信存入缓存空间
 输入参数  : ulIndex:存入短信的位置
             pstMoEntity:存入短信的相关参数
             pucEfSmContent:存入EFSMS文件中短信的内容
 输出参数  : 无
 返 回 值  : 无

 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2007年12月05日
    作    者   : z40661
    修改内容   : 新生成函数
*****************************************************************************/
VOS_VOID  MN_MSG_SaveStoreMsg(
    VOS_UINT32                          ulIndex,
    const MN_MSG_MO_ENTITY_STRU         *pstMoEntity,
    const VOS_UINT8                     *pucEfSmContent
);

/*****************************************************************************
 函 数 名  : MN_MSG_GetStoreMsg
 功能描述  : 获取缓存中的一条短信
 输入参数  : 无
 输出参数  : pstStoreMsg:缓存中的消息内容
 返 回 值  : 缓存所在的索引,如果为MN_MSG_NO_AVAILABLE_REC,则表明没有缓存消息

 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2007年12月05日
    作    者   : z40661
    修改内容   : 新生成函数
*****************************************************************************/
VOS_UINT32  MN_MSG_GetStoreMsg(
    MN_MSG_STORE_MSG_STRU               *pstStoreMsg
);

/*****************************************************************************
 函 数 名  : MN_MSG_FreeStoreMsg
 功能描述  : 释放缓存中的一条消息
 输入参数  : ulIndex:释放消息的索引
 输出参数  : 无
 返 回 值  : 无

 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2007年12月05日
    作    者   : z40661
    修改内容   : 新生成函数
*****************************************************************************/
VOS_VOID  MN_MSG_FreeStoreMsg(
    VOS_UINT32                          ulIndex
);

/*****************************************************************************
 函 数 名  : MN_MSG_ProcMoCtrl
 功能描述  : 根据发送短信内容,构造Envelop 命令到USIM卡中
 输入参数  : pucEfSmContent       - 短信的内容
 输出参数  : 无
 返 回 值  : MN_ERR_NO_ERROR:解析发送参数成功
             其他:解析发送参数失败
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2008年2月14日
    作    者   : 周君 40661
    修改内容   : 新生成函数

*****************************************************************************/
VOS_UINT32 MN_MSG_ProcMoCtrl(
    MN_CLIENT_ID_T                      ClientId,
    MN_OPERATION_ID_T                   OpId,
    const VOS_UINT8                     aucRpDataInfo[]
);

/*****************************************************************************
 函 数 名  : MN_MSG_DestroyMoInfo
 功能描述  : 清空f_stMsgMoEntity中相关参数
 输入参数  : 无
 输出参数  : 无
 返 回 值  : 无

 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2007年12月05日
    作    者   : z40661
    修改内容   : 新生成函数
*****************************************************************************/
VOS_VOID MN_MSG_DestroyMoInfo(VOS_VOID);

/*****************************************************************************
 函 数 名  : MN_MSG_CreateMtInfo
 功能描述  : 创建g_stSmaMtEntity中相关参数
 输入参数  : 无
 输出参数  : 无
 返 回 值  : 无
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2007年12月05日
    作    者   : z40661
    修改内容   : 新生成函数
*****************************************************************************/
VOS_VOID MN_MSG_CreateMtInfo(VOS_VOID);

/*****************************************************************************
 函 数 名  : MN_MSG_DestroyMtInfo
 功能描述  : 清空g_stSmaMtEntity中相关参数
 输入参数  : 无
 输出参数  : 无
 返 回 值  : 无

 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2007年12月05日
    作    者   : z40661
    修改内容   : 新生成函数
*****************************************************************************/
VOS_VOID MN_MSG_DestroyMtInfo(VOS_VOID);

/*****************************************************************************
 函 数 名  : MN_MSG_CreateNewUsimNode
 功能描述  : 向USIM发起异步操作,由于USIM的节点数有限,调用此函数查看是否有空闲的节点数,
             如果有空闲节点,则填写该节点相关信息
 输入参数  : pstSmaUsimInfo  - 创建节点相关信息
 输出参数  : pulIndex        - 节点所在索引
 返 回 值  : VOS_TRUE        - 找到空闲的f_astMsgSetUsimInfo
             VOS_FALSE       - 未找到空闲的f_astMsgSetUsimInfo

 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2007年12月05日
    作    者   : z40661
    修改内容   : 新生成函数
*****************************************************************************/
VOS_UINT32 MN_MSG_CreateNewUsimNode(
    const MN_MSG_USIM_INFO_STRU         *pstSmaUsimInfo,
    VOS_UINT32                          *pulIndex
);

/*清空内存中索引为ucIndex的USIM节点相关信息*/
/*****************************************************************************
 函 数 名  : MN_MSG_DestroyUsimNode
 功能描述  : 清空内存中索引为ucIndex的USIM节点相关信息
 输入参数  : ulIndex - 操作USIM节点的记录数
 输出参数  : 无
 返 回 值  : 无
 调用函数  :
 被调函数  :
 修改历史      :
  1.日    期   : 2007年12月14日
    作    者   : z40661
    修改内容   : 新生成函数
*****************************************************************************/
VOS_VOID MN_MSG_DestroyUsimNode(
    VOS_UINT32                          ulIndex
);
/***********************************************************************
函 数 名  : MN_MSG_UpdateUstInfo
功能描述  : 更新内存中保留的EFSMSS文件存在的标志以
输入参数  : pstSmsUstInfo:EFSMSS文件的内容
输出参数  : 无
返 回 值  : 无

调用函数  :
被调函数  :

修改历史      :
 1.日    期   : 2007年12月12日
   作    者   : z40661
   修改内容   : 新生成函数
************************************************************************/
VOS_VOID MN_MSG_UpdateUstInfo(
);
/***********************************************************************
函 数 名  : MN_MSG_MoFeatureAvailable
功能描述  : 获取MO功能可用标志
输入参数  : VOS_VOID
输出参数  : 无
返 回 值  : MN_ERR_NO_ERROR - MO功能可用
            其他            - MO功能不可用
调用函数  :
被调函数  :

修改历史      :
 1.日    期   : 2008年4月13日
   作    者   : f62575
   修改内容   : 新生成函数
************************************************************************/
VOS_UINT32 MN_MSG_MoFeatureAvailable(VOS_VOID);

/***********************************************************************
函 数 名  : MN_MSG_UpdateSmssInfo
功能描述  : 更新内存中保留的EFSMSS文件存在的标志以及文件的内容
输入参数  : bEfSmssState:文件存在的标志
            pstSmssInfo:EFSMSS文件的内容
输出参数  : 无
返 回 值  :

调用函数  :
被调函数  :

修改历史      :
 1.日    期   : 2007年12月12日
   作    者   : z40661
   修改内容   : 新生成函数
************************************************************************/
VOS_VOID MN_MSG_UpdateSmssInfo(
    VOS_BOOL                            bEfSmssState,
    const MN_MSG_SMSS_INFO_STRU         *pstSmssInfo,
    VOS_UINT32                          ulFileLen
);

/***********************************************************************
函 数 名  : MN_MSG_ReadSmssInfo
功能描述  : 获取保存在USIM或NVIM中的SMSS的内容,优先获取保存在USIM的EFSMSS文件的内容
输入参数  : 无
输出参数  : pstSmssInfo:获取EFSMSS的内容
返 回 值  : VOS_TRUE:获取成功
            VOS_FALSE:获取失败
调用函数  :
被调函数  :

修改历史      :
 1.日    期   : 2007年10月26日
   作    者   : z40661
   修改内容   : 新生成函数
************************************************************************/
VOS_UINT32  MN_MSG_ReadSmssInfo(
    MN_MSG_SMSS_INFO_STRU               *pstSmssInfo
);

/*****************************************************************************
 函 数 名  : MN_MSG_Internal_SendRpt
 功能描述  : 协议栈内部调用此函数发送RP-ACK或RP-ERROR消息到网侧
 输入参数  : bRpAck:是发送RpAck还是RpError
             enRpCause:发送RpError时有效,具体R层的原因值
             enTpCause:发送RpError时有效,具体T层的原因值
 输出参数  : 无
 返 回 值  :

 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2007年10月15日
    作    者   : z40661
    修改内容   : 新生成函数
*****************************************************************************/
VOS_VOID MN_MSG_Internal_SendRpt(
    VOS_BOOL                            bRpAck   ,                              /*is Rp-Ack or Rp-Error*/
    MN_MSG_RP_CAUSE_ENUM_U8             enRpCause,                              /*used when bRpAck==FALSE*/
    MN_MSG_TP_CAUSE_ENUM_U8             enTpCause                               /*TP-Cause*/
);

/***********************************************************************
函 数 名  : MN_MSG_GetCurRcvMsgPath
功能描述  : 获取当前接收短信的路径
输入参数  : NONE
输出参数  : pstCfgParm:当前接收短信的路径
返 回 值  :
调用函数  :
被调函数  :

修改历史      :
 1.日    期   : 2007年12月06日
   作    者   : z40661
   修改内容   : 新生成函数
************************************************************************/
VOS_VOID  MN_MSG_GetCurCfgParm(
    MN_MSG_CONFIG_PARM_STRU             *pstCfgParm
);

/***********************************************************************
函 数 名  : MN_MSG_UpdateRegState
功能描述  : 更新当前CS,PS域的注册情况
输入参数  : ucDomain:需要更新的域
            bAttachFlag:当前更新的标志
输出参数  : NONE
返 回 值  : 无
调用函数  :
被调函数  :

修改历史      :
 1.日    期   : 2007年12月06日
   作    者   : z40661
   修改内容   : 新生成函数
************************************************************************/
VOS_VOID  MN_MSG_UpdateRegState(
    VOS_UINT8                           ucDomain,
    VOS_BOOL                            bAttachFlag
);

/***********************************************************************
函 数 名  : MN_MSG_UpdateTotalSmspInfo
功能描述  : 收到USIM发送过来的EFSMSP的文件内容后,更新内存中EFSMSP的内容
输入参数  : bEfSmspState:EFSMSP文件存在标志
            ucNumofSmsp:EFSMSP文件的个数
            ucEfLen:EFSMSP文件的长度
            pucSmspContent:EFSMSP文件的内容
输出参数  : 无
返 回 值  :
调用函数  :
被调函数  :

修改历史      :
 1.日    期   : 2007年10月26日
   作    者   : z40661
   修改内容   : 新生成函数
************************************************************************/
VOS_VOID  MN_MSG_UpdateTotalSmspInfo(
    VOS_BOOL                            bEfSmspState,
    VOS_UINT8                           ucNumofSmsp,
    VOS_UINT8                           ucEfLen,
    const VOS_UINT8                     *pucSmspContent
);

/***********************************************************************
函 数 名  : MN_MSG_UpdateEachMemSmInfo
功能描述  : 更新USIM保存在内存中的短信内容
输入参数  : ucIndex:更新记录的index
            pucEFContent:EFSMS的文件内容
            ucEFSmsLen:EFSMS文件的长度
输出参数  : 无
返 回 值  : 无
调用函数  :
被调函数  :

修改历史      :
 1.日    期   : 2007年11月26日
   作    者   : z40661
   修改内容   : 新生成函数
************************************************************************/
VOS_VOID  MN_MSG_UpdateEachMemSmInfo(
    VOS_UINT32                          ulIndex,
    VOS_UINT8                           *pucEFContent,
    VOS_UINT8                           ucEFSmsLen
);

/***********************************************************************
函 数 名  : MN_MSG_UpdateSmsRecNumInfo
功能描述  : 收到USIM发送过来的EFSMS的文件内容后,更新内存中EFSMS的记录数和文件存在标志
输入参数  : bEfSmsState:文件存在标志
            ucEFSmNum:USIM中文件记录数,
输出参数  : 无
返 回 值  :
调用函数  :
被调函数  :
修改历史      :
 1.日    期   : 2007年11月26日
   作    者   : z40661
   修改内容   : 新生成函数
************************************************************************/
VOS_VOID  MN_MSG_UpdateSmsInfo(
    VOS_BOOL                            bEfSmsState,
    VOS_UINT8                           ucEFSmNum
);

/***********************************************************************
函 数 名  : MN_MSG_ReadUstInfo
功能描述  : 获取USIM保存在内存短信服务表
输入参数  : 无
输出参数  : pstEfUstInfo:USIM保留在内存的(U)SIM Service Table的内容
返 回 值  : 无

调用函数  :
被调函数  :

修改历史      :
 1.日    期   : 2007年11月26日
   作    者   : z40661
   修改内容   : 新生成函数
************************************************************************/
VOS_VOID   MN_MSG_ReadUstInfo(
    MN_MSG_USIM_EFUST_INFO_STRU         *pstEfUstInfo
);

/***********************************************************************
函 数 名  : MN_MSG_UpdateUsimStateInfo
功能描述  : 更新当前USIM卡及其USIM卡上电的状态
输入参数  : enPowerState:USIM卡的上电状态
输出参数  : 无
返 回 值  :

调用函数  :
被调函数  :

修改历史      :
 1.日    期   : 2007年10月26日
   作    者   : z40661
   修改内容   : 新生成函数
************************************************************************/
VOS_VOID  MN_MSG_UpdateUsimStateInfo(
    MN_MSG_USIM_POWER_STATE_ENUM_U8     enPowerState
);

/*****************************************************************************
 函 数 名  : MN_MSG_UpdateMoSaveInfo
 功能描述  : 更新f_stMsgMoEntity中存储的相关参数
 输入参数  : enSaveArea     - 发送短信的存储区域
             ucSaveIndex    - 发送短信的存储位置
 输出参数  : 无
 返 回 值  : 无

 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2007年12月05日
    作    者   : z40661
    修改内容   : 新生成函数
*****************************************************************************/
VOS_VOID MN_MSG_UpdateMoSaveInfo(
    MN_MSG_MEM_STORE_ENUM_U8            enSaveArea,
    VOS_UINT32                          ulSaveIndex
);

/***********************************************************************
函 数 名  : MN_MSG_StartMo
功能描述  : 发送完一条短信后,如果当前有消息缓存,调用此函数继续发送消息
输入参数  : 无
输出参数  : penSendDomain:当前发送短信的发送域
返 回 值  : VOS_TRUE:发送缓存消息成功
            VOS_FALSE:发送缓存消息失败

调用函数  :
被调函数  :

修改历史      :
 1.日    期   : 2007年11月26日
   作    者   : z40661
   修改内容   : 新生成函数
************************************************************************/
VOS_UINT32 MN_MSG_StartMo(
    MN_MSG_SEND_DOMAIN_ENUM_U8          *penSendDomain
);

/***********************************************************************
函 数 名  : MN_MSG_StartMemNotification
功能描述  : 根据当前存储器的情况决定是否要向网侧发起内存可用通知
输入参数  : 无
输出参数  : 无
返 回 值  :
调用函数  :
被调函数  :

修改历史      :
 1.日    期   : 2007年11月26日
   作    者   : z40661
   修改内容   : 新生成函数
************************************************************************/
VOS_VOID MN_MSG_StartMemNotification(VOS_VOID);

/***********************************************************************
函 数 名  : MN_MSG_SendMemAvail
功能描述  : 向网侧发起内存可用通知
输入参数  : 无
输出参数  : 无
返 回 值  :

调用函数  :
被调函数  :

修改历史      :
 1.日    期   : 2007年11月26日
   作    者   : z40661
   修改内容   : 新生成函数
************************************************************************/
VOS_VOID MN_MSG_SendMemAvail(VOS_VOID);

/***********************************************************************
函 数 名  : MN_MSG_IsUsimFileExist
功能描述  : 获取USIM中该文件是否存在
输入参数  : usEfId:USIM中的文件ID
输出参数  : NONE
返 回 值  : VOS_TRUE:该文件存在
            VOS_FALSE:该文件不存在
调用函数  :
被调函数  :
修改历史      :
 1.日    期   : 2007年12月06日
   作    者   : z40661
   修改内容   : 新生成函数
************************************************************************/
VOS_BOOL MN_MSG_IsUsimFileExist(
    VOS_UINT16                          usEfId
);

/***********************************************************************
函 数 名  : MN_MSG_ReadSmsInfo
功能描述  : 从内存中读取存在USIM的短信或读取NVIM中的短信
输入参数  : enMemStore:短信的存储位置,NVIM或USIM
            ulIndex:需要读取短信的索引号
输出参数  : pucSmsContent:该条短信的内容
返 回 值  : VOS_UINT32:函数执行结果
调用函数  :
被调函数  :
修改历史      :
 1.日    期   : 2007年12月06日
   作    者   : z40661
   修改内容   : 新生成函数
************************************************************************/
VOS_UINT32 MN_MSG_ReadSmsInfo(
    MN_MSG_MEM_STORE_ENUM_U8            enMemStore,
    VOS_UINT32                          ulIndex,
    VOS_UINT8                           *pucSmContent
);

/***********************************************************************
函 数 名  : MN_MSG_ReadSmsrInfo
功能描述  : 从内存中读取存在USIM的短信状态报告或读取NVIM中的短信状态报告
输入参数  : enMemStore:短信的存储位置,NVIM或USIM
            ulIndex:需要读取短信状态报告的索引号
输出参数  : pucSmsrContent:该条短信状态报告的内容
返 回 值  : VOS_UINT32:函数执行结果
调用函数  :
被调函数  :

修改历史      :
 1.日    期   : 2007年12月06日
   作    者   : z40661
   修改内容   : 新生成函数
************************************************************************/
VOS_UINT32 MN_MSG_ReadSmsrInfo(
    MN_MSG_MEM_STORE_ENUM_U8            enMemStore,
    VOS_UINT32                          ulIndex,
    VOS_UINT8                           *pucSmsrContent
);

/***********************************************************************
函 数 名  : MN_MSG_UpdateEachMemSmsrInfo
功能描述  : 更新USIM保存在内存中的短信状态报告内容
输入参数  : ucIndex:更新记录的index
            pucEFContent:EFSMSR的文件内容
            ucEFSmsLen:EFSMSR文件的长度
输出参数  : 无
返 回 值  : 无
调用函数  :
被调函数  :

修改历史      :
 1.日    期   : 2007年11月26日
   作    者   : z40661
   修改内容   : 新生成函数
************************************************************************/
VOS_VOID  MN_MSG_UpdateEachMemSmsrInfo(
    VOS_UINT8                           ucIndex,
    VOS_UINT8                           *pucEFContent,
    VOS_UINT8                           ucEFSmsrLen
);

/***********************************************************************
函 数 名  : MN_MSG_UpdateSmspInfo
功能描述  : 更新保留在内存中的USIM的短信参数
输入参数  : ucIndex:需要更新的短信参数索引
            bUsed:该短信参数是否有效
            pstScvParm:更新的内容
输出参数  : 无
返 回 值  : 无
调用函数  :
被调函数  :

修改历史      :
 1.日    期   : 2007年12月06日
   作    者   : z40661
   修改内容   : 新生成函数
************************************************************************/
VOS_VOID MN_MSG_UpdateEachMemSmspInfo(
    VOS_UINT8                           ucIndex,
    VOS_BOOL                            bUsed,
    const MN_MSG_SRV_PARAM_STRU         *pstScvParm
);

/***********************************************************************
函 数 名  : MN_MSG_ReadSmspInfo
功能描述  : 读出索引为usSmspIndex的短信参数的内容
输入参数  : enMemStore:短信参数的存储位置
            usSmspIndex:短信参数的索引
输出参数  : pstSmspPara:读出短信参数的内容
返 回 值  : MN_ERR_NO_ERROR:读取成功
            其他:读取失败
调用函数  :
被调函数  :

修改历史      :
 1.日    期   : 2007年12月06日
   作    者   : z40661
   修改内容   : 新生成函数
************************************************************************/
VOS_UINT32 MN_MSG_ReadSmspInfo(
    MN_MSG_MEM_STORE_ENUM_U8            enMemStore,
    VOS_UINT32                          ulIndex,
    MN_MSG_SRV_PARAM_STRU                *stSrvParm
);

/***********************************************************************
函 数 名  : MN_MSG_GetSmStorageList
功能描述  : 获取当前USIM或NVIM中短信的storage list
输入参数  : enMemStore:当前的存储器,USIM或NVIM
输出参数  : pusTotalRec:当前存储器的总容量
            psUsedRec:当前存储器的已用空间
            pulEachStatusRec:每种状态的短信的记录数
返 回 值  : 无
调用函数  :
被调函数  :

修改历史      :
 1.日    期   : 2007年12月06日
   作    者   : z40661
   修改内容   : 新生成函数
************************************************************************/
VOS_VOID MN_MSG_GetSmStorageList(
    MN_MSG_MEM_STORE_ENUM_U8            enMemStore,
    VOS_UINT32                          *pulTotalRec,
    VOS_UINT32                          *pulUsedRec,
    VOS_UINT32                          *pulEachStatusRec
);

/***********************************************************************
函 数 名  : MN_MSG_GetStatus
功能描述  : 获取存在USIM或NVIM中的短信状态
输入参数  : enMemStore:需要获取短信状态的存储位置,USIM或NVIM中
            ulIndex:需要获取短信状态的索引号
输出参数  : pucStatus:索引为ulIndex的短信状态
返 回 值  : MN_ERR_NO_ERROR:获取成功
            其他:获取失败
调用函数  :
被调函数  :

修改历史      :
 1.日    期   : 2007年12月06日
   作    者   : z40661
   修改内容   : 新生成函数
************************************************************************/
VOS_UINT32 MN_MSG_GetStatus(
    MN_MSG_MEM_STORE_ENUM_U8            enMemStore,
    VOS_UINT32                          ulIndex,
    VOS_UINT8                           *pucStatus
);

/***********************************************************************
函 数 名  : MN_MSG_GetAvailSmRecIndex
功能描述  : 获取存在USIM或NVIM中的一条空闲的短信索引
输入参数  : enMemStore:需要获取空闲短信索引的存储位置,USIM或NVIM中
输出参数  : NONE
返 回 值  : 空闲短信索引号,无空闲短信,则返回MSG_NO_AVAILABLE_REC
调用函数  :
被调函数  :

修改历史      :
 1.日    期   : 2007年12月06日
   作    者   : z40661
   修改内容   : 新生成函数
************************************************************************/
VOS_UINT32 MN_MSG_GetAvailSmRecIndex(
    MN_MSG_MEM_STORE_ENUM_U8            enMemStore
);

/***********************************************************************
函 数 名  : MN_MSG_GetAvailSmsrRecIndex
功能描述  : 获取存在USIM或NVIM中的空闲的短信状态报告索引
输入参数  : enMemStore:需要获取空闲短信状态报告索引的存储位置,USIM或NVIM中
输出参数  : NONE
返 回 值  : 空闲短信状态报告索引号,无空闲短信状态报告,则返回MSG_NO_AVAILABLE_REC
调用函数  :
被调函数  :

修改历史      :
 1.日    期   : 2007年12月06日
   作    者   : z40661
   修改内容   : 新生成函数
************************************************************************/
VOS_UINT32 MN_MSG_GetAvailSmsrRecIndex(
    MN_MSG_MEM_STORE_ENUM_U8            enMemStore
);

/***********************************************************************
函 数 名  : MN_MSG_GetAvailSmspRecIndex
功能描述  : 获取存在USIM中的空闲的短信参数索引
输入参数  : NONE
输出参数  : NONE
返 回 值  : 空闲短信参数索引号,无空闲短信参数,则返回MSG_NO_AVAILABLE_REC
调用函数  :
被调函数  :

修改历史      :
 1.日    期   : 2008年01月30日
   作    者   : z40661
   修改内容   : 新生成函数
************************************************************************/
VOS_UINT8 MN_MSG_GetAvailSmspRecIndex(VOS_VOID);

/***********************************************************************
函 数 名  : MN_MSG_GetReplaceSmsrRecIndex
功能描述  : 获取存在USIM或NVIM中的替换的短信状态报告索引,即寻找最老的一条短信状态报告索引记录
输入参数  : enMemStore:需要获取空闲短信状态报告索引的存储位置,USIM或NVIM中
输出参数  : NONE
返 回 值  : 最老的一条短信状态报告索引记录
调用函数  :
被调函数  :

修改历史      :
 1.日    期   : 2007年12月06日
   作    者   : z40661
   修改内容   : 新生成函数
************************************************************************/
VOS_UINT32 MN_MSG_GetReplaceSmsrRecIndex(
    MN_MSG_MEM_STORE_ENUM_U8            enMemStore
);

/***********************************************************************
函 数 名  : MN_MSG_GetUsimPowerState
功能描述  : 获取USIM当前的上电状态
输入参数  : 无
输出参数  : penPowerState:获取USIM当前的上电状态
返 回 值  : 无
调用函数  :
被调函数  :
修改历史      :
 1.日    期   : 2007年12月06日
   作    者   : z40661
   修改内容   : 新生成函数
************************************************************************/
VOS_VOID  MN_MSG_GetUsimPowerState(
    MN_MSG_USIM_POWER_STATE_ENUM_U8     *penPowerState
);

VOS_UINT32 MN_MSG_GetSmCapacity(
    MN_MSG_MEM_STORE_ENUM_U8            enMemStore
);

/***********************************************************************
函 数 名  : MN_MSG_GetSmspCapacity
功能描述  : 获取最大能存在USIM或NVIM中短信参数的容量
输入参数  : enMemStore:需要获取短信容量的存储位置,USIM或NVIM中
输出参数  : NONE
返 回 值  : 当前存储器的短信容量
调用函数  :
被调函数  :

修改历史      :
 1.日    期   : 2007年12月06日
   作    者   : z40661
   修改内容   : 新生成函数
************************************************************************/
VOS_UINT32 MN_MSG_GetSmspCapacity(
    MN_MSG_MEM_STORE_ENUM_U8            enMemStore
);

/***********************************************************************
函 数 名  : MN_MSG_GetSmsrCapacity
功能描述  : 获取最大存在USIM或NVIM中短信状态报告的容量
输入参数  : enMemStore:需要获取短信状态报告容量的存储位置,USIM或NVIM中
输出参数  : NONE
返 回 值  : 当前存储器的短信状态报告容量
调用函数  :
被调函数  :

修改历史      :
 1.日    期   : 2007年12月06日
   作    者   : z40661
   修改内容   : 新生成函数
************************************************************************/
VOS_UINT32 MN_MSG_GetSmsrCapacity(
    MN_MSG_MEM_STORE_ENUM_U8            enMemStore
);

/***********************************************************************
函 数 名  : MN_MSG_IsValidSmIndex
功能描述  : 判断当前输入的Index是合法的还是非法的
输入参数  : enMemStore:需要判断输入短信index的存储位置,USIM或NVIM中
            ucIndex:输入短信的索引
输出参数  : NONE
返 回 值  : VOS_TRUE:输入index合法
            VOS_FALSE:输入index非法
调用函数  :
被调函数  :

修改历史      :
 1.日    期   : 2007年12月06日
   作    者   : z40661
   修改内容   : 新生成函数
************************************************************************/
VOS_BOOL MN_MSG_IsValidSmIndex(
    MN_MSG_MEM_STORE_ENUM_U8            enMemStore,
    VOS_UINT32                          ulIndex
);

/***********************************************************************
函 数 名  : MN_MSG_IsValidSmspIndex
功能描述  : 判断当前输入的Index是合法的还是非法的
输入参数  : ucIndex:输入短信参数的索引
输出参数  : NONE
返 回 值  : VOS_TRUE:输入index合法
            VOS_FALSE:输入index非法
调用函数  :
被调函数  :

修改历史      :
 1.日    期   : 2007年12月06日
   作    者   : z40661
   修改内容   : 新生成函数
************************************************************************/
VOS_BOOL MN_MSG_IsValidSmspIndex(
    VOS_UINT8                           ucIndex
);

/***********************************************************************
函 数 名  : MN_MSG_IsEmptySmsp
功能描述  : 判断当前记录是否是空记录
输入参数  : usSmsIndex:输入短信参数的索引
输出参数  : NONE
返 回 值  : VOS_TRUE:输入索引合法
            VOS_FALSE:输入索引非法
调用函数  :
被调函数  :

修改历史      :
 1.日    期   : 2007年12月06日
   作    者   : z40661
   修改内容   : 新生成函数
************************************************************************/
VOS_BOOL MN_MSG_IsEmptySmsp(
    VOS_UINT8                           ucIndex
);

/***********************************************************************
函 数 名  : MN_MSG_UpdateRcvMsgPath
功能描述  : 获取当前接收短信的路径
输入参数  : 无
输出参数  : pstRcvPath:需要更新的接收短信的路径
返 回 值  : 无
调用函数  :
被调函数  :

修改历史      :
 1.日    期   : 2007年12月06日
   作    者   : z40661
   修改内容   : 新生成函数
************************************************************************/
VOS_VOID  MN_MSG_GetCurRcvMsgPath(
    MN_MSG_SET_RCVMSG_PATH_PARM_STRU    *pstRcvPath
);

/***********************************************************************
函 数 名  : MN_MSG_UpdateRcvMsgPath
功能描述  : 更新当前接收短信的路径
输入参数  : pstRcvPath:需要更新的接收短信的路径
输出参数  : NONE
返 回 值  : MN_ERR_NO_ERROR:更新成功
            其他:更新失败
调用函数  :
被调函数  :

修改历史      :
 1.日    期   : 2007年12月06日
   作    者   : z40661
   修改内容   : 新生成函数
************************************************************************/
VOS_UINT32  MN_MSG_UpdateRcvMsgPath(
    const MN_MSG_SET_RCVMSG_PATH_PARM_STRU *pstRcvPath
);

/***********************************************************************
函 数 名  : MN_MSG_GetDeleteReportFlag
功能描述  : 获取当前操作(如list,delete等等),是否已经上报
输入参数  : enType:当前操作的类型
输出参数  : 无
返 回 值  : 当前操作(如list,delete等等),是否已经上报
            VOS_TRUE:已经上报
            VOS_FALSE:未能上报
调用函数  :
被调函数  :
修改历史      :
 1.日    期   : 2007年12月19日
   作    者   : z40661
   修改内容   : 新生成函数
************************************************************************/
VOS_BOOL  MN_MSG_GetDeleteReportFlag(
    MN_MSG_SET_USIM_ENUM_U8                enType
);

/***********************************************************************
函 数 名  : MN_MSG_SetDeleteReportFlag
功能描述  : 设置当前操作(如list,delete等等),是否上报
输入参数  : enType:当前操作的类型
            bReportFlag:上报标志
输出参数  : 无
返 回 值  : 无
调用函数  :
被调函数  :
修改历史      :
 1.日    期   : 2007年12月19日
   作    者   : z40661
   修改内容   : 新生成函数
************************************************************************/
VOS_VOID  MN_MSG_SetDeleteReportFlag(
    MN_MSG_SET_USIM_ENUM_U8                enType,
    VOS_BOOL                            bReportFlag
);

/***********************************************************************
函 数 名  : MN_MSG_GetCurSendDomain
功能描述  : 获取当前发送短信时,短信的实际发送域
输入参数  : penHopeSendDomain:当前发送短信时,期望的短信发送域
输出参数  : penRealSendDomain:当前发送短信时,实际的短信发送域
返 回 值  :
调用函数  :
被调函数  :

修改历史      :
 1.日    期   : 2007年12月06日
   作    者   : z40661
   修改内容   : 新生成函数
************************************************************************/
VOS_VOID   MN_MSG_GetCurSendDomain(
    MN_MSG_SEND_DOMAIN_ENUM_U8          enHopeSendDomain,
    MN_MSG_SEND_DOMAIN_ENUM_U8          *penRealSendDomain
);

/***********************************************************************
函 数 名  : MN_MSG_GetCurAppMemStatus
功能描述  : 获取当前APP的内存使用状态
输入参数  : NONE
输出参数  : penMemStatus:当前APP的内存使用状态
返 回 值  :
调用函数  :
被调函数  :

修改历史      :
 1.日    期   : 2007年12月06日
   作    者   : z40661
   修改内容   : 新生成函数
************************************************************************/
VOS_VOID  MN_MSG_GetCurAppMemStatus(
    MN_MSG_MEM_FLAG_ENUM_U8             *penMemStatus
);

/***********************************************************************
函 数 名  : MN_MSG_UpdateAppMemStatus
功能描述  : 更新APP的内存使用状态
输入参数  : enMemStatus:需要更新的APP的内存使用状态
输出参数  : NONE
返 回 值  : VOS_TRUE:更新成功
            VOS_FALSE:更新失败
调用函数  :
被调函数  :

修改历史      :
 1.日    期   : 2007年12月06日
   作    者   : z40661
   修改内容   : 新生成函数
************************************************************************/
VOS_UINT32  MN_MSG_UpdateAppMemStatus(
    MN_MSG_MEM_FLAG_ENUM_U8             enMemStatus
);

/***********************************************************************
函 数 名  : MN_MSG_FindNodeByUsimResult
功能描述  : 收到从USIM返回的结果记录时,找到该条记录当前进行操作的节点信息f_astMsgSetUsimInfo
输入参数  : ucRecIndex:操作USIM的记录数
            usEfId:操作USIM的文件EFID
输出参数  : pSmaUsimInfo:找到的节点信息f_astMsgSetUsimInfo
            pucIndex:找到节点在USIM节点列表的索引
返 回 值  : VOS_TRUE:成功找到
            VOS_FALSE:未能找到
调用函数  :
被调函数  :

修改历史      :
 1.日    期   : 2007年12月06日
   作    者   : z40661
   修改内容   : 新生成函数
************************************************************************/
VOS_UINT32  MN_MSG_FindNodeByUsimResult(
    VOS_UINT8                           ucRecIndex,
    VOS_UINT16                          usEfId,
    MN_MSG_USIM_INFO_STRU               *pSmaUsimInfo,
    VOS_UINT32                          *pulIndex
);

/***********************************************************************
函 数 名  : MN_MSG_GetUsimRec
功能描述  : 获取当前同一种类型的操作(如list,delete等等),设置USIM的记录数
输入参数  : 无
输出参数  : 无
返 回 值  : 当前同一种类型的操作(如list,delete等等),设置USIM的记录数
调用函数  :
被调函数  :

修改历史      :
 1.日    期   : 2007年12月06日
   作    者   : z40661
   修改内容   : 新生成函数
************************************************************************/
VOS_UINT8  MN_MSG_GetUsimRec(
    MN_MSG_SET_USIM_ENUM_U8                enType
);

/***********************************************************************
函 数 名  : MN_MSG_SetUsimRec
功能描述  : 重新设置向USIM设置的记录数,
输入参数  : enType:当前操作类型
            ucRec:需要设置的记录数
输出参数  : 无
返 回 值  : 无
调用函数  :
被调函数  :

修改历史      :
 1.日    期   : 2007年12月06日
   作    者   : z40661
   修改内容   : 新生成函数
************************************************************************/
VOS_VOID  MN_MSG_SetUsimRec(
    MN_MSG_SET_USIM_ENUM_U8                enType,
    VOS_UINT8                           ucRec
);

/*****************************************************************************
 函 数 名  : MN_MSG_GetSmsMoCtrlPend
 功能描述  : 返回当前发送短信时,SMS MO CONTROL开启时,是否正在等待USIM的回复
 输入参数  : 无
 输出参数  : 无
 返 回 值  : 无

 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2007年12月27日
    作    者   : z40661
    修改内容   : 新生成函数
*****************************************************************************/
VOS_BOOL MN_MSG_GetSmsMoCtrlPend(VOS_VOID);

/*****************************************************************************
 函 数 名  : MN_MSG_UpdateSmaMoState
 功能描述  : 更新短信发送实体状态
 输入参数  : MN_MSG_MO_STATE_ENUM_U8             enSmaMoState  待更新的短信发送实体状态
 输出参数  : 无
 返 回 值  : VOS_VOID
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2011年6月22日
    作    者   : 傅映君/f62575
    修改内容   : 新生成函数

*****************************************************************************/
VOS_VOID MN_MSG_UpdateSmaMoState(
    MN_MSG_MO_STATE_ENUM_U8             enSmaMoState
);

/*****************************************************************************
 函 数 名  : MN_MSG_MoSmsControlEnvelopeReq
 功能描述  : SMS MO CONTROL功能开启时,下发Envelope datadownload到USIM卡
 输入参数  : pstAddrObj1: SC Addr
             pstAddrObj2: Dest Addr
             pucLI:       Location Information
 输出参数  : VOS_TRUE:返回成功
             VOS_FALSE:返回失败
 返 回 值  :

 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2007年10月15日
    作    者   : z40661
    修改内容   : 新生成函数
  2.日    期   : 2012年12月26日
    作    者   : 张鹏 id:00214637
    修改内容   : USIM对外接口函数变更的处理 ，Client ID 到 PID的转换处理 。
  3.日    期   : 2013年5月16日
    作    者   : w00176964
    修改内容   : SS FDN&Call Control项目:MN_MSG_MoSmsControlEnvelopeReq增加client ID参数
*****************************************************************************/
VOS_UINT32  MN_MSG_MoSmsControlEnvelopeReq(
    VOS_UINT16                          usClientId,
    MN_MSG_BCD_ADDR_STRU               *pstRpDestAddr,
    MN_MSG_BCD_ADDR_STRU               *pstTpDestAddr
);



/*****************************************************************************
 函 数 名  : MN_MSG_SmsPPEnvelopeReq
 功能描述  : 收到Class 2 和PID为USIM DataDownLad短信时,需要下发Envelope datadownload到USIM卡
 输入参数  : pstAddr:     SC Addr
             pucTpduData: SMS TPDU (SMS-DELIVER)
             ulTpduLen:   SMS TPDU (SMS-DELIVER) Length
 输出参数  : 无
 返 回 值  : VOS_TRUE; 返回成功
             VOS_FALSE:返回失败

 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2007年10月15日
    作    者   : z40661
    修改内容   : 新生成函数
*****************************************************************************/
VOS_UINT32  MN_MSG_SmsPPEnvelopeReq(
    const MN_MSG_BCD_ADDR_STRU          *pstAddr,
    const VOS_UINT8                     *pucTpduData,
    const VOS_UINT32                    ulTpduLen
);

/* Modified by y00245242 for VoLTE_PhaseI  项目, 2013-7-10, begin */
/***********************************************************************
函 数 名  : MN_MSG_SendSmma
功能描述  : 发送SMMA消息到网侧
输入参数  : clientId       - 发起该请求的Client的ID
            opId           - Operation ID, 标识本次操作
            bReportFlag    - 上报标志
输出参数  : 无
返 回 值  :
调用函数  :
被调函数  :

修改历史      :
 1.日    期   : 2007年11月26日
   作    者   : z40661
   修改内容   : 新生成函数
 1.日    期   : 2013年7月10日
   作    者   : y00245242
   修改内容   : 增加SMS发送路由判断，决定SMS发送给IMS栈还是PS栈
************************************************************************/
VOS_UINT32  MN_MSG_SendSmma(
    MN_CLIENT_ID_T                      clientId,
    MN_OPERATION_ID_T                   opId,
    VOS_BOOL                            bReportFlag,
    TAF_MSG_SIGNALLING_TYPE_ENUM_UINT32 enMsgSignallingType
);
/* Modified by y00245242 for VoLTE_PhaseI  项目, 2013-7-10, end */


/***********************************************************************
函 数 名  : MN_MSG_WriteSmssFile
功能描述  : 更新内存,USIM中和NVIM保留的SMSS文件值,无论USIM,NVIM是否更新成功,
            内存中更新成功,优先更新USIM中的EFSMSS的内容
输入参数  : pstSmssInfo:需要更新EFSMSS的内容
输出参数  : 无
返 回 值  : 无
调用函数  :
被调函数  :

修改历史      :
 1.日    期   : 2008年01月20日
   作    者   : z40661
   修改内容   : 新生成函数
************************************************************************/
VOS_VOID  MN_MSG_WriteSmssFile(
    const MN_MSG_SMSS_INFO_STRU         *pstSmssInfo
);

#if ((NAS_FEATURE_SMS_FLASH_SMSEXIST == FEATURE_ON) && (NAS_FEATURE_SMS_NVIM_SMSEXIST == FEATURE_ON))
VOS_UINT32  MN_MSG_WriteSmsFile(
    MN_MSG_MEM_STORE_ENUM_U8            enMemStore,
    const VOS_UINT32                   *pulMeIndex,
    const MN_MSG_WRITE_USIM_INFO_STRU  *pstWriteUsimInfo,
    VOS_UINT8                          *pucContentInfo
);

#else
/***********************************************************************
函 数 名  : MN_MSG_WriteSmsFile
功能描述  : 更新内存,USIM中和NVIM保留的SMS文件值
输入参数  : enMemStore:当前的存储器,USIM或NVIM
            bCreateNode:是否创建节点
            pstSmaUsimInfo:往USIM中写入信息时,USIM节点的相关信息
            pucContentInfo:需要存入的内容
输出参数  : 无
返 回 值  : MN_ERR_NO_ERROR:更新成功,
            其他:失败以及失败的原因值
调用函数  :
被调函数  :

修改历史      :
 1.日    期   : 2007年10月26日
   作    者   : z40661
   修改内容   : 新生成函数
************************************************************************/
VOS_UINT32  MN_MSG_WriteSmsFile(
    MN_MSG_MEM_STORE_ENUM_U8            enMemStore,
    VOS_BOOL                            bCreateNode,
    const MN_MSG_USIM_INFO_STRU         *pstSmaUsimInfo,
    VOS_UINT8                           *pucContentInfo
);
#endif


/***********************************************************************
函 数 名  : MN_MSG_WriteSmsrFile
功能描述  : 更新内存,USIM中和NVIM保留的EFSMSR文件值
输入参数  : enMemStore:当前的存储器,USIM或NVIM
            pstSmaUsimInfo:往USIM中写入信息时,USIM节点的相关信息
            pucContentInfo:需要存入的内容
输出参数  : 无
返 回 值  : MN_ERR_NO_ERROR:更新成功,
            其他:失败以及失败的原因值
调用函数  :
被调函数  :

修改历史      :
 1.日    期   : 2007年10月26日
   作    者   : z40661
   修改内容   : 新生成函数
************************************************************************/
VOS_UINT32  MN_MSG_WriteSmsrFile(
    MN_MSG_MEM_STORE_ENUM_U8            enMemStore,
    const MN_MSG_USIM_INFO_STRU         *pstSmaUsimInfo,
    VOS_UINT8                           *pucContentInfo
);

/***********************************************************************
函 数 名  : MN_MSG_WriteSmspFile
功能描述  : 更新内存,USIM中和NVIM保留的SMS文件值
输入参数  : enMemStore:当前的存储器,USIM或NVIM
            pstSmaUsimInfo:往USIM中写入信息时,USIM节点的相关信息
            pstSrvParm:需要存入的内容
输出参数  : 无
返 回 值  : MN_ERR_NO_ERROR:更新成功,
            其他:更新失败以及失败的原因值
调用函数  :
被调函数  :
修改历史      :
 1.日    期   : 2007年10月26日
   作    者   : z40661
   修改内容   : 新生成函数
************************************************************************/
VOS_UINT32  MN_MSG_WriteSmspFile(
    MN_MSG_MEM_STORE_ENUM_U8            enMemStore,
    const MN_MSG_USIM_INFO_STRU         *pstSmaUsimInfo,
    const MN_MSG_SRV_PARAM_STRU          *stSrvParm
);

/***********************************************************************
函 数 名  : MN_MSG_RecoverOrgSrvParm
功能描述  : 删除或写短信参数,USIM返回失败,需要将内存中的短信参数恢复回来
输入参数  : ucIndex:恢复短信参数存入的索引
输出参数  : pstSrvParm:需要恢复的短信参数的内容
返 回 值  : 无
调用函数  :
被调函数  :
修改历史      :
 1.日    期   : 2007年10月26日
   作    者   : z40661
   修改内容   : 新生成函数
************************************************************************/
VOS_VOID  MN_MSG_RecoverOrgSrvParm(
    VOS_UINT8                           ucIndex,
    MN_MSG_USIM_EFSMSP_DTL_INFO_STRU    *pstSrvParam
);

/***********************************************************************
函 数 名  : MN_MSG_RecoverOrgSm
功能描述  : 删除或写短信,USIM返回失败,需要将内存中的短信恢复回来
输入参数  : ucIndex:恢复短信存入的索引
输出参数  : pucSmsContent:需要恢复的短信的内容
返 回 值  : 无
调用函数  :
被调函数  :
修改历史      :
 1.日    期   : 2007年10月26日
   作    者   : z40661
   修改内容   : 新生成函数
************************************************************************/
VOS_VOID  MN_MSG_RecoverOrgSm(
    VOS_UINT8                           ucIndex,
    VOS_UINT8                           *pucSmContent
);

/***********************************************************************
函 数 名  : MN_MSG_RecoverOrgSmsr
功能描述  : 删除或写短信状态报告时,USIM返回失败,需要将内存中的短信状态报告恢复回来
输入参数  : ucIndex:恢复短信状态报告存入的索引
输出参数  : pucSmsrContent:需要恢复的短信状态报告的内容
返 回 值  : 无
调用函数  :
被调函数  :
修改历史      :
 1.日    期   : 2007年10月26日
   作    者   : z40661
   修改内容   : 新生成函数
************************************************************************/
VOS_VOID  MN_MSG_RecoverOrgSmsr(
    VOS_UINT8                           ucIndex,
    VOS_UINT8                           *pucSmsrContent
);

/*****************************************************************************
 函 数 名  : MN_MSG_CreateEFSmContent
 功能描述  : 根据SC Addr和TPDU创建一条短信,短信格式为USIM卡中EFSMS的格式
 输入参数  : pstScAddr:短信中心的地址
             pstRawData:TPDU的内容
             ucStatus:短信的状态
 输出参数  : pucContent:短信内容,USIM卡中EFSMS的格式
 返 回 值  :
 调用函数  :
 被调函数  :
 修改历史      :
  1.日    期   : 2008年01月18日
    作    者   : z40661
    修改内容   : 新生成函数
*****************************************************************************/
VOS_VOID MN_MSG_CreateEFSmContent(
    const MN_MSG_BCD_ADDR_STRU          *pstScAddr,
    const MN_MSG_RAW_TS_DATA_STRU       *pstRawData,
    VOS_UINT8                           ucStatus,
    VOS_UINT8                           *pucContent
);

/*****************************************************************************
 函 数 名  : MN_MSG_ParseEFSmContent
 功能描述  : 将短信格式为USIM卡中EFSMS的格式解析为SCAddr和TPDU
 输入参数  : pucContent:短信内容,USIM卡中EFSMS的格式
 输出参数  : pstScAddr:短信中心的地址
             pstRawData:TPDU的内容
             ucStatus:短信的状态
 返 回 值  : MN_ERR_NO_ERROR:解析成功
             其他:解析失败
 调用函数  :
 被调函数  :
 修改历史      :
  1.日    期   : 2008年01月18日
    作    者   : z40661
    修改内容   : 新生成函数
*****************************************************************************/
VOS_UINT32 MN_MSG_ParseEFSmContent(
    const VOS_UINT8                     *pucContent,
    MN_MSG_BCD_ADDR_STRU                *pstScAddr,
    MN_MSG_RAW_TS_DATA_STRU             *pstRawData,
    VOS_UINT8                           *pucStatus
);

/*****************************************************************************
 函 数 名  : MN_MSG_GetAppStatus
 功能描述  : 根据USIM卡中的短信状态获取对APP提供的短信状态
 输入参数  : ucStatus:USIM卡的短信状态
 输出参数  : penStatus:APP的短信状态
 返 回 值  : 无
 调用函数  :
 被调函数  :
 修改历史      :
  1.日    期   : 2008年01月18日
    作    者   : z40661
    修改内容   : 新生成函数
*****************************************************************************/
VOS_VOID MN_MSG_GetAppStatus(
    VOS_UINT8                           ucStatus,
    MN_MSG_STATUS_TYPE_ENUM_U8          *penStatus
);

/*****************************************************************************
 函 数 名  : MN_MSG_GetPsStatus
 功能描述  : 根据APP提供的短信状态获取USIM卡中的短信状态
 输入参数  : enStatus:APP的短信状态
 输出参数  : pucStatus:USIM卡的短信状态

 返 回 值  : 无
 调用函数  :
 被调函数  :
 修改历史      :
  1.日    期   : 2008年01月18日
    作    者   : z40661
    修改内容   : 新生成函数
*****************************************************************************/
VOS_VOID MN_MSG_GetPsStatus(
    MN_MSG_STATUS_TYPE_ENUM_U8          enStatus,
    VOS_UINT8                           *pucStatus
);

/***********************************************************************
函 数 名  : MN_MSG_UpdateTotalSmsrInfo
功能描述  : 收到USIM发送过来的EFSMSR的文件内容后,更新内存中EFSMSR的内容
输入参数  : bEfSmspState:EFSMSR的文件是否存在
            ucSmsrRec:EFSMSR的文件个数
            ucEfLen:EFSMSR文件的长度
            pucSmspContent:EFSMSR文件的内容
输出参数  : 无
返 回 值  :

调用函数  :
被调函数  :

修改历史      :
 1.日    期   : 2007年10月26日
   作    者   : z40661
   修改内容   : 新生成函数
************************************************************************/
VOS_VOID  MN_MSG_UpdateTotalSmsrInfo(
    VOS_BOOL                            bEfSmspState,
    VOS_UINT8                           ucSmsrRec,
    VOS_UINT16                          usEfLen,
    VOS_UINT8                           *pucSmspContent
);

/***********************************************************************
函 数 名  : MN_MSG_GetSmsrStorageList
功能描述  : 获取当前USIM或NVIM中SMS的storage list
输入参数  : enMemStore:当前的存储器,USIM或NVIM
输出参数  : pusTotalRec:当前存储器的总容量
            psUsedRec:当前存储器的已用空间
返 回 值  : 无
调用函数  :
被调函数  :

修改历史      :
 1.日    期   : 2007年12月06日
   作    者   : z40661
   修改内容   : 新生成函数
************************************************************************/
VOS_VOID MN_MSG_GetSmsrStorageList(
    MN_MSG_MEM_STORE_ENUM_U8            enMemStore,
    VOS_UINT32                          *pulTotalRec,
    VOS_UINT32                          *pulUsedRec
);

/***********************************************************************
函 数 名  : MN_MSG_GetSmspStorageList
功能描述  : 获取当前USIM或NVIM中短信参数的storage list
输入参数  : enMemStore:当前的存储器,USIM或NVIM
输出参数  : pusTotalRec:当前存储器的总容量
            psUsedRec:当前存储器的已用空间
返 回 值  : 无
************************************************************************/
VOS_VOID MN_MSG_GetSmspStorageList(
    MN_MSG_MEM_STORE_ENUM_U8            enMemStore,
    VOS_UINT32                          *pulTotalRec,
    VOS_UINT32                          *pulUsedRec,
    MN_MSG_SRV_PARAM_STRU                *pstSrvParam
);

/*****************************************************************************
 函 数 名  : MN_MSG_DeleteMultiSm
 功能描述  : 删除多条短信,NVIM:直接删除NVIM中的短信,USIM,下发删除命令到USIM中
 输入参数  : clientId        - 发起该请求的Client的ID
             opId            - Operation ID, 标识本次操作
             enMemStore      - 当前短信的存储位置
             enDeleteType    - 删除类型
 输出参数  : pbDeleteAll     - 是否已删除所有短信
             pucDeleteCount  - 本次删除的个数
 返 回 值  : MN_ERR_NO_ERROR - 删除成功或下发命令到USIM成功
             其他             - 删除出错

 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2007年10月15日
    作    者   : z40661
    修改内容   : 新生成函数
*****************************************************************************/
VOS_UINT32 MN_MSG_DeleteMultiSm(
    MN_CLIENT_ID_T                      clientId,
    MN_OPERATION_ID_T                   opId,
    MN_MSG_MEM_STORE_ENUM_U8            enMemStore,
    MN_MSG_DELETE_TYPE_ENUM_U8          enDeleteType,
    VOS_BOOL                            *pbDeleteAll,
    VOS_UINT32                          *pulDeleteCount
);

/*****************************************************************************
 函 数 名  : MN_MSG_DeleteMultiStaRpt
 功能描述  : 删除多条短信状态报告,NVIM:直接删除NVIM中的短信状态报告,USIM,下发删除命令到USIM中
 输入参数  : clientId        - 发起该请求的Client的ID
             opId            - Operation ID, 标识本次操作
             enMemStore      - 当前短信的存储位置
 输出参数  : pbDeleteAll     - 是否已删除所有短信状态报告
             pucDeleteCount  - 本次删除的个数
 返 回 值  : MN_ERR_NO_ERROR - 删除成功或下发命令到USIM成功
             其他             - 删除出错

 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2007年10月15日
    作    者   : z40661
    修改内容   : 新生成函数
*****************************************************************************/
VOS_UINT32  MN_MSG_DeleteMultiStaRpt(
    MN_CLIENT_ID_T                      clientId,
    MN_OPERATION_ID_T                   opId,
    MN_MSG_MEM_STORE_ENUM_U8            enMemStore,
    VOS_BOOL                            *pbDeleteAll,
    VOS_UINT8                           *pucDeleteCount
);


/*****************************************************************************
 函 数 名  : MSG_BuildDeliverEvtParm
 功能描述  : 构造Deliver事件上报的结构
 输入参数  : pstCfgParm:短信当前的接收路径
             pstScAddr:短信中心地址
             pstRawData:短信的TPDU的值
 输出参数  : pstDeliverEvt:Deliver事件上报的结构

 返 回 值  : 无
 调用函数  :
 被调函数  :
 修改历史      :
  1.日    期   : 2008年01月18日
    作    者   : z40661
    修改内容   : 新生成函数
*****************************************************************************/
VOS_VOID MSG_BuildDeliverEvtParm(
    const MN_MSG_CONFIG_PARM_STRU       *pstCfgParm,
    const MN_MSG_BCD_ADDR_STRU          *pstScAddr,
    const MN_MSG_RAW_TS_DATA_STRU       *pstRawData,
    MN_MSG_DELIVER_EVT_INFO_STRU        *pstDeliverEvt
);

/*****************************************************************************
 函 数 名  : MN_MSG_GetBCopId
 功能描述  : 广播上报时,获取OPID的值
 输入参数  : 无
 输出参数  : 无

 返 回 值  : 无
 调用函数  :
 被调函数  :
 修改历史      :
  1.日    期   : 2008年01月18日
    作    者   : z40661
    修改内容   : 新生成函数
*****************************************************************************/
MN_OPERATION_ID_T  MN_MSG_GetBCopId(VOS_VOID);

/***********************************************************************
函 数 名  : MN_MSG_GetUsimParmReq
功能描述  : 请求USIM获取相关文件的参数
输入参数  : 无
输出参数  : 无
返 回 值  : 无
调用函数  :
被调函数  :

修改历史      :
 1.日    期   : 2007年10月26日
   作    者   : z40661
   修改内容   : 新生成函数
************************************************************************/
VOS_VOID MN_MSG_GetUsimParmReq(
    VOS_UINT16                          usEfId
);

/***********************************************************************
函 数 名  : MN_MSG_Init
功能描述  : 初始化短信模块的静态变量
输入参数  : None
输出参数  : 无
返 回 值  :
调用函数  :
被调函数  :

修改历史      :
 1.日    期   : 2007年10月15日
   作    者   : z40661
   修改内容   : 新生成函数
************************************************************************/
VOS_VOID MN_MSG_SmInit(VOS_VOID);

VOS_VOID  MN_MSG_ReadMsgNvimInfo( VOS_VOID );

/***********************************************************************
函 数 名  : MN_MSG_SmCfgDataInit
功能描述  : TAF模块收到USIM卡在位与否的消息后,调用此函数初始化SM模块变量
            如果卡在位,则向USIM发送请求获取USIM中的SM相关参数,并获取NVIM中
            SM相关参数
输入参数  : ucUsimState:USIM卡是否在位
输出参数  : 无
返 回 值  : 无
调用函数  :
被调函数  :

修改历史      :
 1.日    期   : 2007年10月26日
   作    者   : z40661
   修改内容   : 新生成函数
************************************************************************/
VOS_VOID MN_MSG_SmCfgDataInit(
    MNPH_USIM_STATUS_ENUM_U32           enUsimStatus
);

/***********************************************************************
函 数 名  : MN_MSG_GetLinkCtrlParam
功能描述  : 获取中继协议链路连续性的控制标志
输入参数  : 无
输出参数  : 无
返 回 值  : 中继协议链路连续性的控制标志
调用函数  :
被调函数  :

修改历史      :
 1.日    期   : 2008年7月21日
   作    者   : f62575
   修改内容   : 新生成函数
************************************************************************/
MN_MSG_LINK_CTRL_U8 MN_MSG_GetLinkCtrlParam(VOS_VOID);

/***********************************************************************
函 数 名  : MN_MSG_UpdateLinkCtrlParam
功能描述  : 设置中继协议链路连续性的控制标志
输入参数  : setValue - 中继协议链路连续性的控制标志
输出参数  : 无
返 回 值  : MN_ERR_NO_ERROR - 设置操作成功
            其他            - 设置操作失败
调用函数  :
被调函数  :

修改历史      :
 1.日    期   : 2008年7月21日
   作    者   : f62575
   修改内容   : 新生成函数
************************************************************************/
VOS_UINT32 MN_MSG_UpdateLinkCtrlParam(
    MN_MSG_LINK_CTRL_U8                 setValue
);

/*****************************************************************************
 函 数 名  : MN_MSG_InitSmsServiceData
 功能描述  : 初始化短信业务参数数据结构
 输入参数  : MN_MSG_CONFIG_PARM_STRU  *pstServicePara  短信业务参数数据结构
 输出参数  : 无
 返 回 值  : VOS_VOID
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2011年2月11日
    作    者   : 傅映君/f62575
    修改内容   : 新生成函数

*****************************************************************************/
VOS_VOID MN_MSG_InitSmsServiceData(MN_MSG_CONFIG_PARM_STRU  *pstServicePara);


/*****************************************************************************
 函 数 名  : MN_MSG_UpdateNeedSendUsim
 功能描述  : 更新需要发送到USIM的结构
 输入参数  : ulInedx - 需要更新的发往USIM的结构
 输出参数  : 无

 返 回 值  : 无
 调用函数  :
 被调函数  :
 修改历史      :
  1.日    期   : 2008年01月18日
    作    者   : z40661
    修改内容   : 新生成函数
*****************************************************************************/
VOS_VOID MN_MSG_UpdateNeedSendUsim(
    VOS_UINT32                          ulInedx,
    VOS_BOOL                            bUpdateStatus
);

/*****************************************************************************
 函 数 名  : MN_MSG_GetNeedSendUsim
 功能描述  : 更新需要发送到USIM的结构
 输入参数  : 无
 输出参数  : pulRealRec - 当前实际的短信容量
             pbNeedSendUsim - 是否需要通知USIM修改短信状态
 返 回 值  : 无
 调用函数  :
 被调函数  :
 修改历史      :
  1.日    期   : 2008年01月18日
    作    者   : z40661
    修改内容   : 新生成函数
*****************************************************************************/
VOS_VOID MN_MSG_GetNeedSendUsim(
    VOS_UINT32                          *pulRealRec,
    VOS_BOOL                            *pbNeedSendUsim
);

/*****************************************************************************
*  Prototype       : MN_MSG_FailToWriteEfsms
*  Description     : 短信写SIM卡的EFSMS文件失败后,MS按协议要求回复网络RP-ERROR并修改EFSMSS文件；
*  Input           : enMemStore  --- 发生存储失败的存储介质类型
                     ucFailCause --- 当前存储失败的原因
                        存储区满；
                        存储区不可用；
*  Output          :
*  Return Value    : void
*  Calls           :
*  Called By       :
*  History         :
*  1. Date         : 2009-04-12
*     Author       : 傅映君
*     Modification : Created function
*****************************************************************************/
VOS_VOID MN_MSG_FailToWriteEfsms(
    MN_MSG_MEM_STORE_ENUM_U8            enMemStore,
    MN_MSG_WRITE_EFSMS_CAUSE_ENUM_U32   enFailCause
);

/*****************************************************************************
*  Prototype       : MN_MSG_UpdateSendFailFlag
*  Description     : 更新当前发送失败的域
*  Input           : enSendFailFlag --- 当前发送失败的域;
*  Output          :
*  Return Value    : void
*  Calls           :
*  Called By       :
*  History         :
*  1. Date         : 2009-07-13
*     Author       : z40661
*     Modification : Created function
*****************************************************************************/
 VOS_VOID MN_MSG_UpdateSendFailFlag(
 	MN_MSG_SEND_FAIL_FLAG_U8			enSendFailFlag
 );

/*****************************************************************************
 函 数 名  : MN_MSG_GetRetryPeriod
 功能描述  : 获取当前短信重发时间周期和时间间隔
 输入参数  : 无
 输出参数  :  当前短信重发时间周期
 返 回 值  :无

 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2009年7月06日
    作    者   : z40661
    修改内容   : 新生成函数
*****************************************************************************/
VOS_VOID MN_MSG_GetRetryInfo(
    MN_MSG_RETRY_INFO_STRU              *pstRetryInfo
);

/*****************************************************************************
*  Prototype       : MN_MSG_GetSendFailFlag
*  Description     : 获取当前发送失败的域
*  Input           : 无;
*  Output          :
*  Return Value    : 当前发送失败的域
*  Calls           :
*  Called By       :
*  History         :
*  1. Date         : 2009-07-13
*     Author       : z40661
*     Modification : Created function
*****************************************************************************/
 MN_MSG_SEND_FAIL_FLAG_U8 MN_MSG_GetSendFailFlag(VOS_VOID);

/* Modified by f62575 for V9R1 STK升级, 2013-6-26, begin */
/*****************************************************************************
 函 数 名  : MSG_RcvSmsRpRpt
 功能描述  : 处理收到NAS层SMS模块发送的RP-Report
 输入参数  : pRcvMsg:收到数据的内容,具体为协议24011中RP-REPORT的内容
             ucRcvLen:收到数据的长度
 输出参数  : 无
 返 回 值  :

 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2007年10月15日
    作    者   : z40661
    修改内容   : 新生成函数
*****************************************************************************/
VOS_VOID  MN_MSG_RcvSmsRpRpt(SMR_SMT_MO_REPORT_STRU *pstMsg);

/*****************************************************************************
 函 数 名  : MN_MSG_SaveRpErrInfo
 功能描述  : 保存最近一次网侧过来的rP-Error消息,定时器超时后无可用域时,取此消息上报
 输入参数  : ucDataLen:网侧过来的数据长度
             pucData:网侧过来的数据
 输出参数  :  无
 返 回 值  :无

 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2009年7月06日
    作    者   : z40661
    修改内容   : 新生成函数
*****************************************************************************/
VOS_VOID MN_MSG_SaveRpErrInfo(SMR_SMT_MO_REPORT_STRU *pstMsg);

/*****************************************************************************
 函 数 名  : MN_MSG_GetRpErrInfo
 功能描述  : 获取最近一次网侧过来的rP-Error消息,定时器超时后无可用域时,取此消息上报
 输入参数  : 无
 输出参数  : pstRpErrInfo:最近一次网侧过来的数据信息
 返 回 值  :无

 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2009年7月06日
    作    者   : z40661
    修改内容   : 新生成函数
*****************************************************************************/
VOS_VOID MN_MSG_GetRpErrInfo(SMR_SMT_MO_REPORT_STRU *pstMsg);
/* Modified by f62575 for V9R1 STK升级, 2013-6-26, end */

/*****************************************************************************
 函 数 名  : MN_MSG_GetClass0Tailor
 功能描述  : 获取Class0短信实现方式
 输入参数  : 无
 输出参数  : 无
 返 回 值  :Class0短信实现方式

 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2009年7月06日
    作    者   : z40661
    修改内容   : 新生成函数
*****************************************************************************/
MN_MSG_CLASS0_TAILOR_U8 MN_MSG_GetClass0Tailor(VOS_VOID);

/*****************************************************************************
 函 数 名  : MN_MSG_SetClass0Tailor
 功能描述  : 设置Class0短信实现方式
 输入参数  : enClass0Tailor Class0短信实现方式
 输出参数  : 无
 返 回 值  : 无

 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2009年12月31日
    作    者   : z40661
    修改内容   : 新生成函数
*****************************************************************************/
VOS_VOID MN_MSG_SetClass0Tailor(MN_MSG_CLASS0_TAILOR_U8                 enClass0Tailor);

/*****************************************************************************
 函 数 名  : MN_MSG_GetRealPrefSendDomain
 功能描述  : 获取当前实际的优先发送域
 输入参数  : enHopeDomain:当前的实际发送域
             enHopeDomain:当前期望的优先发送域
 输出参数  : 无
 返 回 值  :当前实际的优先发送域

 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2009年7月06日
    作    者   : z40661
    修改内容   : 新生成函数

当前如果支持CS+PS域发送短信,如果CS域发送失败,则下次发送短信时优先从PS域发送,反之
亦然,此时实际的优先发送域时PS域优先发送
*****************************************************************************/
MN_MSG_SEND_DOMAIN_ENUM_U8  MN_MSG_GetRealPrefSendDomain(
    MN_MSG_SEND_DOMAIN_ENUM_U8          enSendDomain,
    MN_MSG_SEND_DOMAIN_ENUM_U8          enHopeDomain
);

/*****************************************************************************
 函 数 名  : MN_MSG_GetMtTpPidAndDcs
 功能描述  : 获取当前接收到短信的TP-PID和TP-DCS
 输入参数  : 无
 输出参数  : MN_MSG_TP_PID_TYPE_ENUM_U8          *penPid 当前接收到短信的TP-PID
             MN_MSG_DCS_CODE_STRU                *pstDcs 当前接收到短信的TP-DCS解析获得的DCS结构
 返 回 值  : 无
 调用函数  :
 被调函数  :
 修改历史      :
  1.日    期   : 2009年12月16日
    作    者   : f62575
    修改内容   : 新生成函数
*****************************************************************************/
VOS_VOID  MN_MSG_GetMtTpPidAndDcs(
    MN_MSG_TP_PID_TYPE_ENUM_U8          *penPid,
    MN_MSG_DCS_CODE_STRU                *pstDcs
);

/*****************************************************************************
 函 数 名  : MN_MSG_SetMtTpPidAndDcs
 功能描述  : 保存当前接收到短信的TP-PID和TP-DCS到短信接收实体
 输入参数  : 无
 输出参数  : MN_MSG_TP_PID_TYPE_ENUM_U8          enPid 当前接收到短信的TP-PID
             MN_MSG_DCS_CODE_STRU                stDcs 当前接收到短信的TP-DCS解析获得的DCS结构
 返 回 值  : 无
 调用函数  :
 被调函数  :
 修改历史      :
  1.日    期   : 2009年12月16日
    作    者   : f62575
    修改内容   : 新生成函数
*****************************************************************************/
VOS_VOID  MN_MSG_SetMtTpPidAndDcs(
    MN_MSG_TP_PID_TYPE_ENUM_U8          enPid,
    MN_MSG_DCS_CODE_STRU                stDcs
);


VOS_VOID MN_MSG_RptMsg(
    MN_CLIENT_ID_T                      clientId,
    MN_OPERATION_ID_T                   opId,
    VOS_UINT32                          ulLeftReportNum,
    const MN_MSG_LIST_PARM_STRU         *pstList,
    MN_MSG_LIST_EVT_INFO_STRU           *pstListRptEvt
);


/*****************************************************************************
 函 数 名  : MN_MSG_InitRcvPath
 功能描述  : 初始化短信接收路径
 输入参数  : 无
 输出参数  : 无
 返 回 值  : 无
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2010年4月29日
    作    者   : f62575
    修改内容   : 新生成函数

*****************************************************************************/
VOS_VOID  MN_MSG_InitRcvPath( VOS_VOID );

/***  All the following functions are defined in MnMsgReqProc.c  ***/
extern VOS_UINT32  MSG_ChangeSmStatus(
    MN_MSG_MEM_STORE_ENUM_U8            enMemStore,
    MN_CLIENT_ID_T                      clientId,
    MN_OPERATION_ID_T                   opId,
    MN_MSG_USIM_ACTION_ENUM_U8          enAction,
    VOS_UINT32                          ulIndex,
    VOS_UINT8                           *pucSmsContent,
    VOS_UINT8                           *pucChangeNum
);

VOS_UINT32 MN_MSG_ReadMsgInFlashByIndex(
    VOS_UINT32                          ulIndex,
    VOS_UINT8                          *pucSmContent
);
VOS_UINT32 MN_MSG_WriteMsgInFlashByIndex(
    VOS_UINT32                          ulIndex,
    VOS_UINT8                          *pucSmContent
);

VOS_VOID MN_MSG_CsDomainAvailable(VOS_BOOL *pbCsDomainAvailable);

VOS_VOID MN_MSG_DeliverMsgNotSupport(
    const MN_MSG_TS_DATA_INFO_STRU      *pstTsData,
    VOS_BOOL                            *pbSupportFlag,
    MN_MSG_TP_CAUSE_ENUM_U8             *penTpCause
);

VOS_VOID MN_MSG_MtSpecificFeatureInit(VOS_VOID);

VOS_VOID MN_MSG_GetReplaceFeature(VOS_UINT8 *pucActFlg);


VOS_VOID MN_MSG_GetCloseSMSFeature(VOS_UINT8 *pucActFlg);

VOS_VOID MN_MSG_CloseSmsCapabilityFeatureInit(VOS_VOID);

VOS_VOID MN_MSG_SetCloseSMSFeature(VOS_UINT8 ucActFlg);

/*****************************************************************************
 函 数 名  : MN_MSG_MoCtrlAllowedWithModification
 功能描述  : MO SMS CONTROL过程的响应消息是ALLOWED MODIFY，更新短信中心或目
             的号码
 输入参数  : SI_STK_MOSMSCTRL_RSP_STRU          *pstMoCtrlRsp
             MN_MSG_MO_ENTITY_STRU              *pstMoEntity
 输出参数  : 无
 返 回 值  : VOS_UINT32
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2011年6月17日
    作    者   : 傅映君/f62575
    修改内容   : 新生成函数

*****************************************************************************/
VOS_UINT32 MN_MSG_MoCtrlAllowedWithModification(
    SI_STK_MOSMSCTRL_RSP_STRU          *pstMoCtrlRsp,
    MN_MSG_MO_ENTITY_STRU              *pstMoEntity
);

/*****************************************************************************
 Prototype      : GMM_GetCurNetwork
 Description    : 获取GMM的当前工作网络
                  HSS 4100 V200R001 新增
                  非GMM模块使用
 Input          :
 Output         :
 Return Value   : GMM工作网络
                  GMM_RABM_CURNET_3G    3G网络
                  GMM_RABM_CURNET_2G    2G网络
 Calls          :
 Called By      :

 History        :
  1.Date        : 2005-12-08
    Author      : Roger Leo
    Modification: Created function
*****************************************************************************/VOS_UINT8 GMM_GetCurNetwork (VOS_VOID);

VOS_VOID TAF_MMA_GetRegStateInfo( TAF_PH_REG_STATE_STRU *pstCurRegInf );

/*****************************************************************************
 函 数 名  : MN_MSG_SendMsgToSms
 功能描述  : 发送短信到SMS模块
 输入参数  : MN_MSG_MO_ENTITY_STRU              *pstMoEntity
 输出参数  : 无
 返 回 值  : VOS_VOID
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2011年6月16日
    作    者   : 傅映君/f62575
    修改内容   : 新生成函数
  2.日    期   : 2012年9月20日
    作    者   : f62575
    修改内容   : 2012082906141 解决数据卡STK短信群发失败问题，删除入参bRetryFlag

*****************************************************************************/
VOS_VOID MN_MSG_SendMsgToSms(
    MN_MSG_MO_ENTITY_STRU              *pstMoEntity
);

/*****************************************************************************
 函 数 名  : MN_MSG_UpdateMoEntityAccordingToMoSmsCtrl
 功能描述  : 根据USIM的MO SMS CONTROL响应消息确认拒绝，发送或修改发送短信
 输入参数  : SI_STK_ENVELOPEDWON_CNF_STRU          *pstEnvelope
             MN_MSG_MO_ENTITY_STRU               *pstMoEntity
 输出参数  : 无
 返 回 值  : VOS_UINT32
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2011年6月16日
    作    者   : 傅映君/f62575
    修改内容   : 新生成函数

*****************************************************************************/
VOS_UINT32 MN_MSG_UpdateMoEntityAccordingToMoSmsCtrl(
    SI_STK_ENVELOPEDWON_CNF_STRU        *pstEnvelope,
    MN_MSG_MO_ENTITY_STRU               *pstMoEntity
);

/*****************************************************************************
 函 数 名  : MN_MSG_RcvUsimMoControlRsp
 功能描述  : 处理MO SMS CONTROL过程USIM模块的响应消息
 输入参数  : SI_STK_ENVELOPEDWON_CNF_STRU          *pstEnvelope
 输出参数  : 无
 返 回 值  : VOS_VOID
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2011年6月15日
    作    者   : 傅映君/f62575
    修改内容   : 新生成函数

*****************************************************************************/
VOS_VOID MN_MSG_RcvUsimMoControlRsp(
    SI_STK_ENVELOPEDWON_CNF_STRU       *pstEnvelope
);

/*****************************************************************************
 函 数 名  : MN_MSG_RcvUsimEnvelopRsp
 功能描述  : 处理接收到USIM发送过来的SetFileRsp的原语
 输入参数  : pstEnvelope:USIM发送过来的设置文件的内容
 输出参数  : 无
 返 回 值  :
 调用函数  :
 被调函数  :
 修改历史      :
  1.日    期   : 2009年08月07日
    作    者   : f62575
    修改内容   : 新生成函数
  2.日    期   : 2009年12月16日
    作    者   : f62575
    修改内容   : AT2D16304, 增加对RP-ACK中带TPDU部分的处理
*****************************************************************************/
VOS_VOID  MN_MSG_RcvUsimEnvelopRsp(
    SI_STK_ENVELOPEDWON_CNF_STRU       *pstEnvelope
);

/*****************************************************************************
 函 数 名  : MN_MSG_SendFdnCheckInfo
 功能描述  : 发送短信FDN检查信息到(U)SIM模块
 输入参数  : MN_MSG_MO_ENTITY_STRU *pstMoEntity 短信发送实体
 输出参数  : 无
 返 回 值  : VOS_UINT32
                MN_ERR_NO_ERROR                 FDN检查数据发送成功
                其他，                          FDN检查数据发送失败
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2012年2月23日
    作    者   : 傅映君/f62575
    修改内容   : 新生成函数
*****************************************************************************/
VOS_UINT32 MN_MSG_SendFdnCheckInfo(MN_MSG_MO_ENTITY_STRU *pstMoEntity);

/*****************************************************************************
 函 数 名  : MN_MSG_CheckMoSmsCtrl
 功能描述  : 发送短信流程中的MO SMS CONTROL检查
 输入参数  : MN_MSG_MO_ENTITY_STRU              *pstMoEntity    短信发送信息结构
 输出参数  : VOS_BOOL                           *pCheckMoCtrl   是否检查MO SMS CONTROL
 返 回 值  : VOS_UINT32
                MN_ERR_NO_ERROR                 MO SMS CONTROL检查执行正确
                其他，                          MO SMS CONTROL检查执行失败，需要拒绝用户的短信发送请求
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2012年2月23日
    作    者   : 傅映君/f62575
    修改内容   : 新生成函数
  2.日    期   : 2012年9月20日
    作    者   : f62575
    修改内容   : 2012082906141 解决数据卡STK短信群发失败问题，修改函数命名及返回
*****************************************************************************/
VOS_UINT32 MN_MSG_CheckMoSmsCtrl(
    MN_MSG_MO_ENTITY_STRU              *pstMoEntity,
    VOS_BOOL                           *pbCheckMoCtrl
);

/* Modified by z00161729 for DCM定制需求和遗留问题, 2012-8-14, begin */
#if (FEATURE_ON == FEATURE_LTE)
/*****************************************************************************
 函 数 名  : MN_MSG_IsLteNeedSmsRetry
 功能描述  : 判断L下是否需要短信重发
 输入参数  : enErrCause - L LMM_SMS_ERR_IND回复的失败原因值
 输出参数  : 无
 返 回 值  : VOS_TRUE  - 短信需要重发
             VOS_FALSE - 短信无需重发
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2012年8月14日
    作    者   : z00161729
    修改内容   : 新生成函数
*****************************************************************************/
VOS_UINT32  MN_MSG_IsLteNeedSmsRetry(
    LMM_SMS_ERR_CAUSE_ENUM_UINT32       enErrCause
);

#endif
/* Modified by z00161729 for DCM定制需求和遗留问题, 2012-8-14, end */

VOS_UINT32  MN_MSG_IsGuNeedSmsRetry(
    SMR_SMT_ERROR_ENUM_UINT32           enErrCause
);

/*****************************************************************************
 函 数 名  : MN_MSG_InitMoBuffer
 功能描述  : 缓存发送短信实体初始化
 输入参数  : 无
 输出参数  : 无
 返回值    : 无
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2012年9月20日
    作    者   : f62575
    修改内容   : 新生成函数
*****************************************************************************/
VOS_VOID MN_MSG_InitMoBuffer(VOS_VOID);

/*****************************************************************************
 函 数 名  : MN_MSG_GetMoBufferCap
 功能描述  : 获取缓存发送短信实体容量
 输入参数  : 无
 输出参数  : 无
 返回值    : 缓存发送短信实体容量
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2012年9月20日
    作    者   : f62575
    修改内容   : 新生成函数
*****************************************************************************/
VOS_UINT32 MN_MSG_GetMoBufferCap(VOS_VOID);

/*****************************************************************************
 函 数 名  : MN_MSG_CheckMoMsg
 功能描述  : 获取指定状态的发送短息实体
 输入参数  : MN_MSG_MO_STATE_ENUM_U8             enMoStatus  要获取的短信实体状态
 输出参数  : MN_MSG_MO_ENTITY_STRU              *pstMoEntity 待发送的短信实体
             VOS_BOOL                           *pbBufferEntity 是否缓存实体
             VOS_UINT32                         *pulIndex       缓存实体索引
 返回值    : VOS_UINT32
                MN_ERR_NO_ERROR                 找到了指定的发送短息实体
                其他，                          没有找到指定的发送短息实体
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2012年9月20日
    作    者   : f62575
    修改内容   : 新生成函数
*****************************************************************************/
VOS_UINT32 MN_MSG_GetSpecificStatusMoEntity(
    MN_MSG_MO_STATE_ENUM_U8             enMoStatus,
    VOS_BOOL                           *pbBufferEntity,
    VOS_UINT32                         *pulIndex,
    MN_MSG_MO_ENTITY_STRU              *pstMoEntity
);

/*****************************************************************************
 函 数 名  : MN_MSG_UpdateSpecificMoEntityStatus
 功能描述  : 更新发送短息实体状态
 输入参数  : MN_MSG_MO_STATE_ENUM_U8             enMoStatus  短信实体状态
             VOS_BOOL                            bBufferEntity 是否缓存实体
             VOS_UINT32                          ulIndex       缓存实体索引
 输出参数  : 无
 返回值    : 无
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2012年9月20日
    作    者   : f62575
    修改内容   : 新生成函数
*****************************************************************************/
VOS_VOID MN_MSG_UpdateSpecificMoEntityStatus(
    VOS_BOOL                            bBufferEntity,
    VOS_UINT32                          ulIndex,
    MN_MSG_MO_STATE_ENUM_U8             enMoStatus
);

/*****************************************************************************
 函 数 名  : MN_MSG_CreateMoEntity
 功能描述  : 更新发送短息实体状态
 输入参数  : VOS_BOOL                            bBufferEntity 是否缓存实体
             VOS_UINT32                          ulIndex       缓存实体索引
             MN_MSG_MO_ENTITY_STRU              *pstMoEntity 待发送的短信实体
             VOS_UINT8                           aucEfSmContent[] 待发送的短信
 输出参数  : 无
 返回值    : 无
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2012年9月20日
    作    者   : f62575
    修改内容   : 新生成函数
*****************************************************************************/
VOS_VOID MN_MSG_CreateMoEntity(
    VOS_BOOL                            bBufferEntity,
    VOS_UINT32                          ulIndex,
    MN_MSG_MO_ENTITY_STRU              *pstMoEntity,
    VOS_UINT8                           aucEfSmContent[]
);

/*****************************************************************************
 函 数 名  : MN_MSG_UpdateSpecificMoEntityStatus
 功能描述  : 清空发送短息实体状态
 输入参数  : VOS_BOOL                            bBufferEntity 是否缓存实体
             VOS_UINT32                          ulIndex       缓存实体索引
 输出参数  : 无
 返回值    : 无
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2012年9月20日
    作    者   : f62575
    修改内容   : 新生成函数
*****************************************************************************/
VOS_VOID MN_MSG_DestroySpecificMoEntity(
    VOS_BOOL                            bBufferEntity,
    VOS_UINT32                          ulIndex
);

/*****************************************************************************
 函 数 名  : MN_MSG_CheckMoMsg
 功能描述  : 发送短信实体的本地检查，包括FDN 和MO SMS CONTROL
 输入参数  : MN_MSG_MO_ENTITY_STRU              *pstMoEntity 待发送的短信实体
             VOS_UINT8                           aucEfSmContent[] 待发送的短信内容
 输出参数  : VOS_BOOL                           *pbRequireCheck 是否要求等待检查结果
             VOS_BOOL                           *pbBufferEntity 待发送短信是否缓存
 返回值    : VOS_UINT32
                MN_ERR_NO_ERROR                 检查执行正确
                其他，                          检查执行失败，需要拒绝用户的短信发送请求
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2012年9月20日
    作    者   : f62575
    修改内容   : 新生成函数
*****************************************************************************/
VOS_UINT32 MN_MSG_CheckMoMsg(
    VOS_UINT8                           aucEfSmContent[],
    MN_MSG_MO_ENTITY_STRU              *pstMoEntity,
    VOS_BOOL                           *pbRequireCheck,
    VOS_BOOL                           *pbBufferEntity
);

/*****************************************************************************
 函 数 名  : MN_MSG_GetMtCustomizeInfo
 功能描述  : 获取短信接收运营商定制类型
 输入参数  : MN_MSG_MT_CUSTOMIZE_ENUM_UINT8 *penMtCustomize  短信接收运营商定制类型
 输出参数  : 无
 返 回 值  : VOS_VOID
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2012年11月8日
    作    者   : f62575
    修改内容   : 新生成函数

*****************************************************************************/
VOS_VOID MN_MSG_GetMtCustomizeInfo(MN_MSG_MT_CUSTOMIZE_ENUM_UINT8 *penMtCustomize);

/*****************************************************************************
 函 数 名  : MN_MSG_UpdateMemExceedFlag
 功能描述  : 更新短信存储溢出标志
 输入参数  : MN_MSG_MEM_FLAG_ENUM_U8 enMemCapExcNotFlag  存储溢出标志
 输出参数  : 无
 返 回 值  : VOS_VOID
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2012年11月10日
    作    者   : f62575
    修改内容   : 新生成函数

*****************************************************************************/
VOS_VOID MN_MSG_UpdateMemExceedFlag(MN_MSG_MEM_FLAG_ENUM_U8 enMemCapExcNotFlag);

/*****************************************************************************
 函 数 名  : MN_MSG_SetTpRd
 功能描述  : 置位发送实体中SUBMIT消息的TP-RD
 输入参数  : MN_MSG_MO_ENTITY_STRU *pstMoEntity 发送实体数据结构
 输出参数  : 无
 返 回 值  : VOS_VOID
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2012年11月10日
    作    者   : f62575
    修改内容   : 新生成函数

*****************************************************************************/
VOS_VOID MN_MSG_SetTpRd(MN_MSG_MO_ENTITY_STRU *pstMoEntity);

VOS_VOID TAF_MSG_SetUsimStatus(
    VOS_UINT8                           ucUsimStatus
);
VOS_UINT8 TAF_MSG_GetUsimStatus(VOS_VOID);
VOS_VOID TAF_MSG_UpdateMtRcvDomain(
    VOS_UINT8                           ucRcvDomain
);
MN_MSG_RCV_DOMAIN_ENUM_U8 TAF_MSG_GetMtRcvDomain(VOS_VOID);


VOS_UINT8 MN_MSG_StartLinkCtrl(VOS_VOID);

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

#endif /* __MNMSGCOMMPROC_H__ */

