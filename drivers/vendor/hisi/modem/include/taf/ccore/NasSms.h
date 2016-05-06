/******************************************************************************

                  版权所有 (C), 2001-2011, 华为技术有限公司

 ******************************************************************************
  文 件 名   : NasSms.h
  版 本 号   : 初稿
  作    者   : 周君 40661
  生成日期   : 2008年2月22日
  最近修改   :
  功能描述   :
  函数列表   :
  修改历史   :
  1.日    期   : 2008年2月22日
    作    者   : 周君 40661
    修改内容   : 创建文件
 2.日    期   : 2009年3月23日
   作    者   : f62575
   修改内容   : AT2D08752, W接入方式下，信号较弱时连续发送多条短信会概率性出现发送操作失败；
 3.日    期   : 2011年04月23日
   作    者   : L00171473
   修改内容   : for V7R1 porting, 去掉枚举成员最后的逗号，避免编译WARNING
******************************************************************************/
#ifndef __NASSMS_H__
#define __NASSMS_H__

#ifdef __cplusplus
#if __cplusplus
extern "C" {
#endif
#endif


/*****************************************************************************
  1 头文件包含
*****************************************************************************/
#include "vos.h"



#pragma pack(4)

/*****************************************************************************
  2 常量定义
*****************************************************************************/

/* Added by f62575 for V9R1 STK升级, 2013-6-26, begin */
/*------------------------ TP Message type indicator (MTI) 23.040-------------------*/
#define NAS_SMS_TP_MTI_SUBMIT                              (0x01)               /* SMS-SUBMIT        */
#define NAS_SMS_TP_MTI_MASK                                (3)
#define NAS_SMS_TI_FLAG_MASK                               (0x80)
#define NAS_SMS_TI_VALUE_MASK                              (0x70)
#define NAS_SMS_LOCAL_TI_VALUE_MASK                        (0x07)
#define NAS_SMS_TI_VALUE_OFFSET                            (4)
#define NAS_SMS_TI_FLAG_OFFSET                             (7)
/* Added by f62575 for V9R1 STK升级, 2013-6-26, end */


/*------------------------------------------------------------------------------*/
/*------------------------Message type indicator (MTI) 24.011-------------------*/
/*------------------------------------------------------------------------------*/
#define MN_MSG_RP_MTI_UP_RP_DATA                            0x00                /* ms -> n RP-DATA */
#define MN_MSG_RP_MTI_UP_RP_ACK                             0x02                /* ms -> n RP-ACK  */
#define MN_MSG_RP_MTI_UP_RP_ERR                             0x04                /* ms -> n RP-ERROR*/
#define MN_MSG_RP_MTI_UP_RP_SMMA                            0x06                /* ms -> n RP-SMMA */
#define MN_MSG_RP_MTI_DOWN_RP_DATA                          0x01                /* n -> ms RP-DATA */
#define MN_MSG_RP_MTI_DOWN_RP_ACK                           0x03                /* n -> ms RP-ACK  */
#define MN_MSG_RP_MTI_DOWN_RP_ERR                           0x05                /* n -> ms RP-ERROR*/
/*------------------------------------------------------------------------------*/

/*------------------------------------------------------------------------------*/
#define  MN_MSG_RP_USER_DATA_IEI                            0x41                /* User data iei  */

#define SMT_SMR_ABORT_FLG_EXIST         1
#define SMT_SMR_ABORT_FLG_NO_EXIST      0

/* Deleted by f62575 for V9R1 STK升级, 2013-6-26, begin */
/* Deleted SMS_RP_RPT_STATUS_ENUM */
/* Deleted by f62575 for V9R1 STK升级, 2013-6-26, end */

/*****************************************************************************
  3 类型定义
*****************************************************************************/
/* 原语名定义 */
typedef enum
{
    SMT_SMR_DATA_REQ,
    SMT_SMR_REPORT_REQ,
    SMT_SMR_SMMA_REQ,
    SMT_SMR_CP_ACK_REQ,
    SMT_SMR_MAX
}SMT_SMR_REQ_ENUM;
typedef VOS_UINT32 SMT_SMR_REQ_ENUM_U32;

/* Modified by z00161729 for DCM定制需求和遗留问题, 2012-8-28, begin */
/* Deleted by f62575 for V9R1 STK升级, 2013-6-26, begin */
/* Del SMR_SMT_ERR_TYPE_ENUM_UINT8 */
/* Deleted by f62575 for V9R1 STK升级, 2013-6-26, end */
/* Modified by z00161729 for DCM定制需求和遗留问题, 2012-8-28, end */

typedef enum
{
    SMR_SMT_ATTACH_IND,
    SMR_SMT_DATA_IND,
    SMR_SMT_REPORT_IND,
    SMR_SMT_LINK_CLOSE_IND,
    SMR_SMT_MT_ERR_IND,
    SMR_SMT_MAX
}SMR_SMT_IND_ENUM;
typedef VOS_UINT32 SMR_SMT_IND_ENUM_U32;

/* 原语SMT_SMR_DATA_REQ,SMT_SMR_REPORT_REQ的结构体 */
typedef struct
{

    VOS_MSG_HEADER                                                              /*消息头*/
    VOS_UINT32                          ulMsgName;
    VOS_UINT32                          ulDataLen;                              /*用户数据的长度*/
    VOS_UINT8                           aucData[4];                           /*用户数据地址*/
}SMT_SMR_DATA_STRU;

/* 使用原语SMR_SMT_DATA_IND发送EST_IND时的结构体，新增接收域 */
typedef struct
{

    VOS_MSG_HEADER                                                              /*消息头*/
    VOS_UINT32                          ulMsgName;
    VOS_UINT32                          ulDataLen;                              /*用户数据的长度*/
    VOS_UINT8                           ucRcvDomain;                            /*接收域*/
    VOS_UINT8                           aucReserve[3];                          /*保留位*/
    VOS_UINT8                           aucData[4];                             /*用户数据地址*/
}SMR_SMT_EST_IND_STRU;

typedef struct
{
    VOS_UINT8                           ucDomain;
    VOS_UINT8                           aucReserve1[3];
    VOS_BOOL                            bAttachFlag;
}SMR_SMT_ATTACH_STRU;

typedef struct
{
    VOS_MSG_HEADER                                                              /*消息头*/
    VOS_UINT32                          ulMsgName;
    VOS_UINT32                          ulDataLen;                              /*用户数据的长度*/
    VOS_UINT8                           aucData[256];                           /*用户数据地址*/
}SMT_SMR_DATA_TEMP_STRU;
/* 原语SMT_SMR_SMMA_REQ的结构体 */
typedef struct
{
    VOS_MSG_HEADER                                                              /* 消息头              */
    VOS_UINT32                          ulMsgName;
    VOS_UINT8                           ucAbortFlg;                             /* 是否携带abort参数    */
    VOS_UINT8                           ucSendDomain;
    VOS_UINT8                           aucReserve1[2];
}SMT_SMR_SMMA_STRU;

/* Added by f62575 for V9R1 STK升级, 2013-6-26, begin */
/*****************************************************************************
 枚举名    : SMR_SMT_ERROR_ENUM
 结构说明  : TAF与SMS的接口错误码
             0              无错误，仅用于短信命令或短信命令发送成功
             1        - 0x100  内部错误码
             0x20000  - 0x200FF  CP-ERROR消息错误码，由SMR_SMT_ERROR_CP_ERROR_BEGIN和CP-ERROR空口消息的错误码(低8BIT)组成
             0x40000  - 0x400FF  RP-ERROR消息错误码，由SMR_SMT_ERROR_RP_ERROR_BEGIN和RP-ERROR空口消息的错误码(低8BIT)组成
             0x80000  - 0x800FF  CS域通道错误码，由SMR_SMT_ERROR_CS_ERROR_BEGIN和MM上报消息MMSMS_REL_IND的错误码(低8BIT)组成
             0x100000 - 0x1000FF  PS域通道错误码，由SMR_SMT_ERROR_PS_ERROR_BEGIN和GMM上报消息PMMSMS_ERROR_IND的错误码(低8BIT)组成
             0x200000 - 0x2000FF  EPS域通道错误码，由SMR_SMT_ERROR_EPS_ERROR_BEGIN和GMM上报消息ID_LMM_SMS_ERR_IND的错误码(低8BIT)组成
             0x400000 - 0x400FFF  IMS错误码，由SMR_SMT_ERROR_IMS_ERROR_BEGIN和IMS内部错误码(低12BIT)组成

             
1.日    期   : 2013年6月26日
  作    者   : f62575
  修改内容   : V9R1 STK升级，新创建
2.日    期   : 2013年9月16日
  作    者   : y00245242
  修改内容   : 适配IMSA接口，增加IMS MSG内部cause

*****************************************************************************/
enum SMR_SMT_ERROR_ENUM
{
    SMR_SMT_ERROR_NO_ERROR                = 0x000000,

    SMR_SMT_ERROR_STATE_NOT_COMPATIBLE    = 0x000001,

    SMR_SMT_ERROR_NO_SERVICE              = 0x000002,

    SMR_SMT_ERROR_TC1M_TIMEOUT            = 0x000003,

    SMR_SMT_ERROR_TR1M_TIMEOUT            = 0x000004,

    SMR_SMT_ERROR_TR2M_TIMEOUT            = 0x000005,

    SMR_SMT_ERROR_USER_ABORT              = 0x000006,

    SMR_SMT_ERROR_CP_ERROR_BEGIN          = 0x020000,

    SMR_SMT_ERROR_RP_ERROR_BEGIN          = 0x040000,

    SMR_SMT_ERROR_CS_ERROR_BEGIN          = 0x080000,

    SMR_SMT_ERROR_PS_ERROR_BEGIN          = 0x100000,

    SMR_SMT_ERROR_EPS_ERROR_BEGIN         = 0x200000,

    SMR_SMT_ERROR_IMS_ERROR_BEGIN         = 0x400000,

    SMR_SMT_ERROR_IMSA_ERROR_BEGIN        = 0x800000,

    SMR_SMT_ERROR_ERROR_BUTT              = 0xFFFFFFFF
};
typedef VOS_UINT32 SMR_SMT_ERROR_ENUM_UINT32;

/*****************************************************************************
 结构名    : SMR_SMT_MT_ERR_STRU
 结构说明  : SMS给TAF上报的短信或或短信状态报告接收失败消息结构，
  1.日    期   : 2013年6月26日
    作    者   : f62575
    修改内容   : V9R1 STK升级，新创建
*****************************************************************************/
typedef struct
{

    VOS_MSG_HEADER                                                              /*消息头*/
    VOS_UINT32                          ulMsgName;
    SMR_SMT_ERROR_ENUM_UINT32           enErrorCode;
}SMR_SMT_MT_ERR_STRU;

/* TPDU的最大长度，参考协议24011 8.2.5.3 */
#define SMR_SMT_RP_USER_DATA_LENGTH     (232)

/*****************************************************************************
 结构名    : SMR_SMT_RPDU_STRU
 结构说明  : SMS给TAF上报的短信发送结果消息中的RPDU结构
  1.日    期   : 2013年6月26日
    作    者   : f62575
    修改内容   : V9R1 STK升级，新创建
*****************************************************************************/
typedef struct
{
    VOS_UINT32                          ulDataLen;                              /*用户数据的长度*/
    VOS_UINT8                           aucData[SMR_SMT_RP_USER_DATA_LENGTH];   /*用户数据地址*/
}SMR_SMT_RPDU_STRU;

/*****************************************************************************
 结构名    : SMR_SMT_MO_REPORT_STRU
 结构说明  : SMS给TAF上报的短信发送结果消息结构，
             ucRpMr      RP-MR
             enErrorCode 短信或短信命令发送失败原因值，发送成功为SMR_SMT_ERROR_NO_ERROR
             stRpduData  SMS给TAF上报的短信发送结果消息中的RPDU结构
                         enErrorCode为SMR_SMT_ERROR_RP_ERROR_BEGIN或SMR_SMT_ERROR_NO_ERROR时有效
  1.日    期   : 2013年6月26日
    作    者   : f62575
    修改内容   : V9R1 STK升级，新创建
*****************************************************************************/
typedef struct
{
    VOS_MSG_HEADER                                                              /*消息头*/
    VOS_UINT32                          ulMsgName;
    SMR_SMT_ERROR_ENUM_UINT32           enErrorCode;
    SMR_SMT_RPDU_STRU                   stRpduData;                             /* 短信或短信命令发送成功或接收到RP-ERROR时有效 */
}SMR_SMT_MO_REPORT_STRU;
/* Added by f62575 for V9R1 STK升级, 2013-6-26, end */

/*****************************************************************************
  4 宏定义
*****************************************************************************/


/*****************************************************************************
  5 全局变量声明
*****************************************************************************/


/*****************************************************************************
  6 接口函数声明
*****************************************************************************/


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

#endif /* __NASSMS_H__ */

