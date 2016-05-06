/******************************************************************************

                  版权所有 (C), 2001-2011, 华为技术有限公司

 ******************************************************************************
  文 件 名   : WasOmInterface.h
  版 本 号   : 初稿
  作    者   : WAS_SMC_GetLastestDomain
  生成日期   : 2010年5月5日
  最近修改   :
  功能描述   : WasMntnMsg.h 的头文件
  函数列表   :
  修改历史   :
  1.日    期   : 2010年5月5日
    作    者   : WAS_SMC_GetLastestDomain
    修改内容   : 创建文件

******************************************************************************/

#ifndef __WASOMINTERFACE_H__
#define __WASOMINTERFACE_H__

#ifdef __cplusplus
#if __cplusplus
extern "C" {
#endif
#endif


/*****************************************************************************
  1 其他头文件包含
*****************************************************************************/
#include "vos.h"
#include "PsTypeDef.h"
#pragma pack(4)

/*****************************************************************************
  2 宏定义
*****************************************************************************/
/* 打印记录的条数 */
#define WAS_PRINT_MSG_MAX_NUM           10
#define WAS_ACT_SET_CELL_MAX_NUM        6
#define WAS_W_NCELL_MAX_NUM             128
#define WAS_G_NCELL_MAX_NUM             64
#define WAS_L_NCELL_MAX_NUM             256
#define WAS_SECOND_ACT_SET_CELL_MAX_NUM 4
#define WAS_SECOND_W_NCELL_MAX_NUM      32

/*****************************************************************************
  3 枚举定义
*****************************************************************************/
/*****************************************************************************
 枚举名    : WAS_MNTN_RPT_TYPE_ENUM_UINT8
 协议表格  :
 ASN.1描述 :
 枚举说明  :报告小区信息的类型
*****************************************************************************/
enum WAS_MNTN_OM_OUT_OF_SERVICE_ENUM
{
    WAS_MNTN_OM_IN_SERVICE              = 0,
    WAS_MNTN_OM_OUT_SERVICE                ,
    WAS_MNTN_OM_SERVICE_BUTT
};
typedef VOS_UINT8 WAS_MNTN_OM_OUT_OF_SERVICE_ENUM_UINT8;

/*****************************************************************************
 枚举名    : WAS_MNTN_RPT_TYPE_ENUM_UINT8
 协议表格  :
 ASN.1描述 :
 枚举说明  :报告小区信息的类型
*****************************************************************************/
enum WAS_MNTN_RPT_TYPE_ENUM
{
    WAS_MNTN_RPT_ONLYONE              = 0,
    WAS_MNTN_RPT_FOR_CHANGE              ,
    WAS_MNTN_RPT_PERIOD                  ,
    WAS_MNTN_RPT_TYPE_BUTT
};
typedef VOS_UINT8 WAS_MNTN_RPT_TYPE_ENUM_UINT8;


/*****************************************************************************
 枚举名    : WAS_MNTN_RPT_CMD_ENUM_UINT8
 协议表格  :
 ASN.1描述 :
 枚举说明  :开始查询或者停止查询命令
*****************************************************************************/
enum WAS_MNTN_RPT_CMD_ENUM
{
    WAS_MNTN_RPT_STOP                 = 0,
    WAS_MNTN_RPT_START
};
typedef VOS_UINT8 WAS_MNTN_RPT_CMD_ENUM_UINT8;

/*****************************************************************************
 枚举名    : WAS_PRINT_LEVEL_ENUM_UINT16
 协议表格  :
 ASN.1描述 :
 枚举说明  : 打印级别
*****************************************************************************/
enum WAS_PRINT_LEVEL_ENUM
{
    WAS_PRINT_LEVEL_NO_PRINT        = 0 ,
    WAS_PRINT_LEVEL_ERROR               ,
    WAS_PRINT_LEVEL_WARNING             ,
    WAS_PRINT_LEVEL_NORMAL              ,
    WAS_PRINT_LEVEL_INFO                ,
    WAS_PRINT_LEVEL_BUTT

};
typedef VOS_UINT16 WAS_PRINT_LEVEL_ENUM_UINT16;

/*****************************************************************************
 枚举名    : WAS_OM_MSG_TYPE_ENUM_UINT16
 协议表格  :
 ASN.1描述 :WAS_MNTN_INTRA_TRANS_SUBMSG_ENUM_UINT16
 枚举说明  : OM->WAS之间的透明消息,透明消息WAS模块ID高8位表示WAS组件B0固定，
            低8表表示消息ID
*****************************************************************************/
enum WAS_OM_MSG_TYPE_ENUM
{

    /*打印控制级别*/
    ID_OM_WAS_PRINT_LEVEL_CTRL_REQ                  = 0xB000,
    ID_WAS_OM_PRINT_LEVEL_CTRL_CNF                  = 0xB001,

    /* 锁频透明命令  */
    ID_OM_WAS_FREQ_LOCK_REQ                         = 0xB002,                   /*OM_WAS_FREQ_LOCK_REQ_STRU*/
    ID_WAS_OM_FREQ_LOCK_CNF                         = 0xB003,

    /* 加密透明命令  */
    ID_OM_WAS_ENCRYPT_REQ                           = 0xB004 ,
    ID_WAS_OM_ENCRYPT_CNF                           = 0xB005 ,

    /* 头压缩透明命令  */
    ID_OM_WAS_COMPRESS_REQ                          = 0xB006 ,
    ID_WAS_OM_COMPRESS_CNF                          = 0xB007  ,

    /* 功率控制透明命令  */
    ID_OM_WAS_POWERCTRL_REQ                         = 0xB008 ,
    ID_WAS_OM_POWERCTRL_CNF                         = 0xB009 ,


    /* 主小区和激活集测量监控透明命令  */
    ID_OM_WAS_ACT_OR_SERV_CELL_INFO_REQ             = 0xB010 ,          /*_H2ASN_MsgChoice OM_WAS_ACT_OR_SERV_CELL_INFO_REQ_STRU*/
    ID_WAS_OM_ACT_OR_SERV_CELL_INFO_CNF             = 0xB011 ,          /*_H2ASN_MsgChoice WAS_OM_ACT_OR_SERV_CELL_INFO_CNF_STRU*/
    ID_WAS_OM_ACT_OR_SERV_CELL_INFO_IND             = 0xB012 ,          /*_H2ASN_MsgChoice WAS_OM_ACT_OR_SERV_CELL_INFO_IND_STRU*/

    /* W邻区测量监控透明命令*/
    ID_OM_WAS_W_NCELL_INFO_REQ                      = 0xB013 ,          /*_H2ASN_MsgChoice OM_WAS_W_NCELL_INFO_REQ_STRU*/
    ID_WAS_OM_W_NCELL_INFO_CNF                      = 0xB014,           /*_H2ASN_MsgChoice WAS_OM_W_NCELL_INFO_CNF_STRU*/
    ID_WAS_OM_W_NCELL_INFO_IND                      = 0xB015 ,          /*_H2ASN_MsgChoice WAS_OM_W_NCELL_INFO_IND_STRU*/

    /* G 邻区测量监控透明命令*/
    ID_OM_WAS_G_NCELL_INFO_REQ                      = 0xB016 ,          /*_H2ASN_MsgChoice OM_WAS_G_NCELL_INFO_REQ_STRU*/
    ID_WAS_OM_G_NCELL_INFO_CNF                      = 0xB017 ,          /*_H2ASN_MsgChoice WAS_OM_G_NCELL_INFO_CNF_STRU*/
    ID_WAS_OM_G_NCELL_INFO_IND                      = 0xB018 ,          /*_H2ASN_MsgChoice WAS_OM_G_NCELL_INFO_IND_STRU*/

    /*查询WCDMA小区变化命令*/
    ID_OM_WAS_W_CELL_CHG_INFO_REQ                   = 0xB019 ,          /*_H2ASN_MsgChoice OM_WAS_W_CELL_CHG_INFO_REQ_STRU*/
    ID_WAS_OM_W_CELL_CHG_INFO_CNF                   = 0xB01A ,          /*_H2ASN_MsgChoice WAS_OM_W_CELL_CHG_INFO_CNF_STRU*/
    ID_WAS_OM_W_CELL_CHG_INFO_IND                   = 0xB01B ,          /*_H2ASN_MsgChoice WAS_OM_W_CELL_CHG_INFO_IND_STRU*/


    /*查询UE状态*/
    ID_OM_WAS_UE_STATE_REQ                          = 0xB01C ,          /*_H2ASN_MsgChoice OM_WAS_UE_STATE_REQ_STRU*/
    ID_OM_WAS_UE_STATE_CNF                          = 0xB01D ,          /*_H2ASN_MsgChoice WAS_OM_UE_STATE_CNF_STRU*/
    ID_WAS_OM_UE_STATE_IND                          = 0xB01E ,          /*_H2ASN_MsgChoice WAS_OM_UE_STATE_IND_STRU*/


    /*空口消息跟踪*/
    ID_OM_WAS_OTA_REQ                               = 0XB020,                   /*OM_WAS_OTA_REQ_STRU*/
    ID_WAS_OM_OTA_CNF                               = 0XB021,                   /*WAS_OM_OTA_CNF_STRU*/
    ID_WAS_OM_OTA_IND                               = 0XB022,


    ID_WAS_OM_WCDMA_WORK_MODE_REQ                   = 0XB027,                   /*OM_WAS_UE_WORK_MODE_REQ_STRU*/
    ID_OM_WAS_WCDMA_WORK_MODE_CNF                   = 0XB028,                   /*OM_WAS_UE_WORK_MODE_CNF_STRU*/

    ID_WAS_FREQ_LOCK_IND                            = 0xB035,
    ID_WAS_FIXED_DATA_RECUR                         = 0xeeee,
    ID_WAS_ALL_DATA_IND                             = 0xB037,
    ID_OM_WAS_CONNECTED_IND                         = 0xaaaa,
    ID_WAS_OM_CONNECTED_CNF                         = 0xaaab,

    /* 打印调试信息 */
    ID_WAS_PRINT_MSG                                = 0xB040,                   /*_H2ASN_MsgChoice WAS_PRINT_MSG_STRU */
    ID_WAS_LAST_SMC_INTEGRITY_F9_IND                = 0xB049,                   /*_H2ASN_MsgChoice WAS_OM_SMC_INTEGRITY_F9_ALGOR_STRU */
    ID_WAS_AFC_INFO_IND                             = 0xB050,
    ID_WAS_JAM_DETECT_INFO_IND                      = 0xB051,                   /*_H2ASN_MsgChoice WAS_JAM_DETECT_INFO_STRU */
    /* LTE不支持的频点列表 */
    ID_WAS_LTE_UNSUPPORT_FREQ                       = 0xB052,                   /*_H2ASN_MsgChoice WAS_UNSUPPORT_EUTRA_ARFCN_LIST_STRU */

    ID_WAS_CSS_BAND_INFO_IND                        = 0xB053,
    ID_WAS_FFT_PLMN_BAND_INFO_IND                   = 0xB054,

    ID_WAS_OM_CELL_INDI_OFFSET_MODIFY_INFO_IND      = 0xB055,
    ID_WAS_CSS_PRE_FREQ_INFO_IND                    = 0xB056,
    ID_WAS_CSS_PRE_BAND_INFO_IND                    = 0xB057,

    ID_WAS_AM_SRB_SEND_STATE_INFO_IND               = 0xB058,

    /* LTE邻区测量监控透明命令*/
    ID_OM_WAS_L_NCELL_INFO_REQ                      = 0xB060 ,          /*_H2ASN_MsgChoice OM_WAS_L_NCELL_INFO_REQ_STRU*/
    ID_WAS_OM_L_NCELL_INFO_CNF                      = 0xB061 ,          /*_H2ASN_MsgChoice WAS_OM_L_NCELL_INFO_CNF_STRU*/
    ID_WAS_OM_L_NCELL_INFO_IND                      = 0xB062 ,          /*_H2ASN_MsgChoice WAS_OM_L_NCELL_INFO_IND_STRU*/

    /* SECOND CELL邻区测量监控透明命令*/
    ID_OM_WAS_SECOND_CELL_INFO_REQ                  = 0xB063 ,          /*_H2ASN_MsgChoice OM_WAS_SECOND_CELL_INFO_REQ_STRU*/
    ID_WAS_OM_SECOND_CELL_INFO_CNF                  = 0xB064 ,          /*_H2ASN_MsgChoice WAS_OM_SECOND_CELL_INFO_CNF_STRU*/
    ID_WAS_OM_SECOND_CELL_INFO_IND                  = 0xB065 ,          /*_H2ASN_MsgChoice WAS_OM_SECOND_CELL_INFO_IND_STRU*/

    /* 定时器事件上报请求 */
    ID_OM_WAS_TIMER_EVENT_REQ                       = 0xB066 ,          /*_H2ASN_MsgChoice OM_WAS_TIMER_EVENT_REQ_STRU*/
    ID_WAS_OM_TIMER_EVENT_CNF                       = 0xB067 ,          /*_H2ASN_MsgChoice WAS_OM_TIMER_EVENT_CNF_STRU*/

    WAS_OM_MSG_TYPE_ENUM_BUTT
};
typedef VOS_UINT16 WAS_OM_MSG_TYPE_ENUM_UINT16;

/*****************************************************************************
 枚举名    : WAS_OM_STATE_IND_ENUM_UINT8
 协议表格  :
 ASN.1描述 : WAS_OM_STATE_IND_ENUM_UINT8
 枚举说明  : WAS->OM之间RRC状态指示(R8协议升级)
*****************************************************************************/
enum WAS_OM_STATE_IND_ENUM
{
    WAS_OM_STATE_CELL_DCH                   = 0,
    WAS_OM_STATE_CELL_FACH                  = 1,
    WAS_OM_STATE_CELL_PCH                   = 2,
    WAS_OM_STATE_URA_PCH                    = 3,
    WAS_OM_STATE_IDLE                       = 4,
    WAS_OM_STATE_E_CELL_FACH                = 5,
    WAS_OM_STATE_E_CELL_PCH_WITHOUT_HRNTI   = 6,
    WAS_OM_STATE_E_URA_PCH                  = 7,
    WAS_OM_STATE_E_CELL_PCH_WITH_HRNTI      = 8,
    WAS_OM_STATE_BUTT

};
typedef VOS_UINT8 WAS_OM_STATE_IND_ENUM_UINT8;


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
/*======================= 以下为具体的透明命令的结构 ======================*/

/*****************************************************************************
 结构名    : DIAG_WAS_MSG_COMM_HEAD_STRU
 协议表格  :
 ASN.1描述 :
 结构说明  : 透明消息公共参数
*****************************************************************************/
typedef struct
{
    VOS_MSG_HEADER

    VOS_UINT32                      ulMsgId;

    VOS_UINT16                      usOriginalId;
    VOS_UINT16                      usTerminalId;
    VOS_UINT32                      ulTimeStamp;
    VOS_UINT32                      ulSN;
} DIAG_WAS_MSG_COMM_HEAD_STRU;

/*****************************************************************************
 结构名    : OM_WAS_OTA_REQ_STRU
 协议表格  :
 ASN.1描述 :
 结构说明  : 空口消息跟踪请求
*****************************************************************************/
typedef struct
{
    DIAG_WAS_MSG_COMM_HEAD_STRU         stMsgCommHead;

    VOS_UINT32                          ulOnOff;                                /* 0 - 停止上报所有WAS空口消息; 1 - 启动上报所有WAS空口消息 */
}OM_WAS_OTA_REQ_STRU;


/*****************************************************************************
 结构名    : WAS_OM_OTA_CNF_STRU
 协议表格  :
 ASN.1描述 :
 结构说明  : 空口消息跟踪回复
*****************************************************************************/
typedef struct
{
    DIAG_WAS_MSG_COMM_HEAD_STRU         stMsgCommHead;

    VOS_UINT32                          ulErrCode;                              /* 传输消息的内容:0－空口消息跟踪配置成功; 1－空口消息跟踪配置失败 */
}WAS_OM_OTA_CNF_STRU;

/*****************************************************************************
 结构名    : WAS_MNTN_SUB_MODE_PRINT_LEVEL_CTRL_STRU
 协议表格  :
 ASN.1描述 :
 结构说明  : 子模块打印级别控制
*****************************************************************************/
typedef struct
{
    DIAG_WAS_MSG_COMM_HEAD_STRU         stMsgCommHead;

    VOS_UINT32                          enMidId;                                    /* 模块ID:WAS_MID_ENUM_UINT32,因不能包含WasGlobal.h,故此处不使用该枚举进行定义   */
    WAS_PRINT_LEVEL_ENUM_UINT16         enPrintLevel;                               /* 打印级别 */
    VOS_UINT8                           aucReserved[2];

}OM_WAS_PRINT_LEVEL_CTRL_REQ_STRU;

typedef WAS_OM_OTA_CNF_STRU WAS_OM_PRINT_LEVEL_CTRL_CNF_STRU;

/*****************************************************************************
 结构名    : WAS_OM_OTA_IND_STRU
 协议表格  :
 ASN.1描述 :
 结构说明  : 跟踪的空口消息上报
*****************************************************************************/
typedef struct
{
    VOS_UINT16                          usOtaMsgID;         /*空口消息的ID号*/
    VOS_UINT8                           ucUpDown;           /*空口消息的方向*/
    VOS_UINT8                           ucReserved;         /*逻辑信道类型*/
    VOS_UINT32                          ulLengthASN;        /*空口消息内容的长度*/
    VOS_UINT8                           aucData[4];         /*跟踪的空口消息内容*/

}WAS_OM_OTA_IND_STRU;

/*****************************************************************************
 结构名    : OM_WAS_FREQ_LOCK_REQ_STRU
 协议表格  :
 ASN.1描述 :
 结构说明  : 透明消息-锁频
*****************************************************************************/
typedef struct
{
    DIAG_WAS_MSG_COMM_HEAD_STRU         stMsgCommHead;

    VOS_UINT16                          usLockedFreq;                           /* 要锁定的频率，0xffff表示不锁定,其它值表示要锁定的频率 */
    VOS_UINT8                           aucReserved1[2];

} OM_WAS_FREQ_LOCK_REQ_STRU;

typedef WAS_OM_OTA_CNF_STRU WAS_OM_FREQ_LOCK_CNF_STRU;

/*****************************************************************************
 结构名    : OM_WAS_POWER_CTRL_REQ_STRU
 协议表格  :
 ASN.1描述 :
 结构说明  : 透明消息-功率控制
*****************************************************************************/
typedef struct
{
    DIAG_WAS_MSG_COMM_HEAD_STRU         stMsgCommHead;

    PS_BOOL_ENUM_UINT8                  enPowerCtrlFlag;                        /* 是否启动功控标识，PS_FALSE(0)：不启动功控， PS_TRUE(1)：启动功控 */
    VOS_UINT8                           aucReserved1[3];

} OM_WAS_POWER_CTRL_REQ_STRU;

typedef WAS_OM_OTA_CNF_STRU WAS_OM_POWER_CTRL_CNF_STRU;

/*****************************************************************************
 结构名    : OM_WAS_ENCRYPT_REQ_STRU
 协议表格  :
 ASN.1描述 :
 结构说明  : 透明消息-加密
*****************************************************************************/
typedef struct
{
    DIAG_WAS_MSG_COMM_HEAD_STRU         stMsgCommHead;

    PS_BOOL_ENUM_UINT8                  enEncryptFlag;                          /* 是否启动加密标识，PS_FALSE(0)：不启动加密， PS_TRUE(1)：启动加密 */
    VOS_UINT8                           aucReserved1[3];

} OM_WAS_ENCRYPT_REQ_STRU;

typedef WAS_OM_OTA_CNF_STRU WAS_OM_ENCRYPT_CNF_STRU;

/*****************************************************************************
 结构名    : OM_WAS_COMPRESS_REQ_STRU
 协议表格  :
 ASN.1描述 :
 结构说明  : 透明消息-头压缩RFC2507
*****************************************************************************/
typedef struct
{
    DIAG_WAS_MSG_COMM_HEAD_STRU         stMsgCommHead;

    PS_BOOL_ENUM_UINT8                  enCompressFlag;                         /* 是否启动头压缩标识，PS_FALSE(0)：不启动头压缩， PS_TRUE(1)：启动头压缩 */
    VOS_UINT8                           aucReserved1[3];

} OM_WAS_COMPRESS_REQ_STRU;

typedef WAS_OM_OTA_CNF_STRU WAS_OM_COMPRESS_CNF_STRU;

/*********************************以下同WCDMA测量上报有关***************************/

/*****************************************************************************
 结构名    : OM_WAS_ACT_OR_SERV_CELL_INFO_REQ_STRU
 协议表格  :
 ASN.1描述 :
 结构说明  : 透明消息-主小区或活动集测量Req消息
*****************************************************************************/

typedef struct
{
    DIAG_WAS_MSG_COMM_HEAD_STRU         stMsgCommHead;

    WAS_MNTN_RPT_CMD_ENUM_UINT8         enCommand;                              /*开始或停止上报*/
    WAS_MNTN_RPT_TYPE_ENUM_UINT8        enReportType;                           /*一次上报，周期上报或者变化上报*/
    VOS_UINT16                          usReportPerio;                          /*如果周期上报设置周期长度*/
} OM_WAS_ACT_OR_SERV_CELL_INFO_REQ_STRU;


/*****************************************************************************
 结构名    : WAS_OM_ACT_OR_SERV_CELL_INFO_CNF_STRU
 协议表格  :
 ASN.1描述 :
 结构说明  : 透明消息-主小区或活动集测量Cnf消息
*****************************************************************************/
typedef struct
{
    DIAG_WAS_MSG_COMM_HEAD_STRU         stMsgCommHead;

    PS_RSLT_CODE_ENUM_UINT32            enRslt;                                 /* 返回查询结构成功或失败 */
    VOS_UINT8                           aucReserved[3];
    WAS_MNTN_RPT_TYPE_ENUM_UINT8        enReportType;                           /*一次上报，周期上报或者变化上报*/
}WAS_OM_ACT_OR_SERV_CELL_INFO_CNF_STRU;

/*****************************************************************************
 结构名    : WAS_MNTN_REPORT_WCDMA_CELL_RSLT_STRU
 协议表格  :
 ASN.1描述 :
 结构说明  : 透明消息-WCDMA 小区报告结果
*****************************************************************************/
typedef struct
{
    VOS_UINT16                         usCellFreq;

    VOS_UINT16                         usCellPSC;

    VOS_INT16                          sCpichRscp;

    VOS_INT16                          sCpichEcN0;

    VOS_UINT16                         usCellIndex;

    VOS_INT16                          sCellRssi;                               /* 新增，上报当前主小区的RSSI值 */

    PS_BOOL_ENUM_UINT8                 enHsdpaFlg;                              /* 是否已建DPA信道 */

    PS_BOOL_ENUM_UINT8                 enHsupaFlg;                              /* 是否已建UPA信道 */

    VOS_INT16                          sRValue;                                 /* 邻区的R值*/

    VOS_INT16                          sHValue;                                 /* 邻区的H值*/

    PS_BOOL_ENUM_UINT8                 enTreselFlg;                             /* 是否已启动Treselection定时器 */

    PS_BOOL_ENUM_UINT8                 enTevaluateFlg;                          /* 是否已启动Tevaluate定时器 */

    PS_BOOL_ENUM_UINT8                 enTnFlg;                                 /* 是否已启动Tn定时器 */

    PS_BOOL_ENUM_UINT8                 enDetectCellFlg;                         /* 是否是DETECT小区的标记 */

    PS_BOOL_ENUM_UINT8                 enBlackCellFlg;                          /* 当前临区是否被加入黑名单，不会重选到该临区 */
    VOS_UINT8                          ucSscDisableMeas;                        /* SSC Disable异频\GSM测量 */
}WAS_MNTN_REPORT_WCDMA_CELL_RSLT_STRU;


/*****************************************************************************
 结构名    : WAS_OM_ACT_OR_SERV_CELL_INFO_IND_STRU
 协议表格  :
 ASN.1描述 :
 结构说明  : 透明消息-主小区或活动集测量Ind消息

            WAS_MNTN_REPORT_WCDMA_CELL_RSLT_STRU
*****************************************************************************/
typedef struct
{
    VOS_UINT16                              usPrimId;
    VOS_UINT16                              usReserved;

    VOS_UINT8                               aucReserved[3];
    WAS_MNTN_RPT_TYPE_ENUM_UINT8            enReportType;
    VOS_UINT16                              usMeasQuantity;

    VOS_UINT16                              usCellNum;
    WAS_MNTN_REPORT_WCDMA_CELL_RSLT_STRU    astActOrServeCellInfo[WAS_ACT_SET_CELL_MAX_NUM];
}WAS_OM_ACT_OR_SERV_CELL_INFO_IND_STRU;


/*****************************************************************************
 结构名    : OM_WAS_W_NCELL_INFO_REQ_STRU
 协议表格  :
 ASN.1描述 :
 结构说明  : 透明消息-W邻区上报Req消息
*****************************************************************************/
typedef OM_WAS_ACT_OR_SERV_CELL_INFO_REQ_STRU OM_WAS_W_NCELL_INFO_REQ_STRU;


/*****************************************************************************
 结构名    : WAS_OM_W_NCELL_INFO_CNF_STRU
 协议表格  :
 ASN.1描述 :
 结构说明  : 透明消息-W邻区测量Cnf消息
*****************************************************************************/
typedef WAS_OM_ACT_OR_SERV_CELL_INFO_CNF_STRU WAS_OM_W_NCELL_INFO_CNF_STRU;


/*****************************************************************************
 结构名    : WAS_OM_W_NCELL_INFO_IND_STRU
 协议表格  :
 ASN.1描述 :
 结构说明  : 透明消息-W邻区测量Ind消息
*****************************************************************************/
typedef struct
{
    VOS_UINT16                              usPrimId;
    VOS_UINT16                              usReserved;

    VOS_UINT8                               aucReserved[3];
    WAS_MNTN_RPT_TYPE_ENUM_UINT8            enReportType;
    VOS_UINT16                              usMeasQuantity;

    VOS_UINT16                              usCellNum;                          
    WAS_MNTN_REPORT_WCDMA_CELL_RSLT_STRU    astWcdmaNeighberCellInfo[WAS_W_NCELL_MAX_NUM];
} WAS_OM_W_NCELL_INFO_IND_STRU;


/*****************************************************************************
 结构名    : OM_WAS_G_NCELL_INFO_REQ_STRU
 协议表格  :
 ASN.1描述 :
 结构说明  : 透明消息-G邻区上报Req消息
*****************************************************************************/
typedef OM_WAS_ACT_OR_SERV_CELL_INFO_REQ_STRU OM_WAS_G_NCELL_INFO_REQ_STRU;

/*****************************************************************************
 结构名    : OM_WAS_L_NCELL_INFO_REQ_STRU
 协议表格  :
 ASN.1描述 :
 结构说明  : 透明消息LTE邻区上报Req消息
*****************************************************************************/
typedef OM_WAS_ACT_OR_SERV_CELL_INFO_REQ_STRU OM_WAS_L_NCELL_INFO_REQ_STRU;

/*****************************************************************************
 结构名    : OM_WAS_SECOND_CELL_INFO_REQ_STRU
 协议表格  :
 ASN.1描述 :
 结构说明  : 透明消息Second cell info邻区上报Req消息
*****************************************************************************/
typedef OM_WAS_ACT_OR_SERV_CELL_INFO_REQ_STRU OM_WAS_SECOND_CELL_INFO_REQ_STRU;

/*****************************************************************************
 结构名    : WAS_OM_W_NCELL_INFO_CNF_STRU
 协议表格  :
 ASN.1描述 :
 结构说明  : 透明消息-W邻区测量Cnf消息
*****************************************************************************/
typedef WAS_OM_ACT_OR_SERV_CELL_INFO_CNF_STRU WAS_OM_G_NCELL_INFO_CNF_STRU;


/*****************************************************************************
 结构名    : WAS_OM_L_NCELL_INFO_CNF_STRU
 协议表格  :
 ASN.1描述 :
 结构说明  : 透明消息-W邻区测量Cnf消息
*****************************************************************************/
typedef WAS_OM_ACT_OR_SERV_CELL_INFO_CNF_STRU WAS_OM_L_NCELL_INFO_CNF_STRU;

/*****************************************************************************
 结构名    : WAS_OM_SECOND_CELL_INFO_CNF_STRU
 协议表格  :
 ASN.1描述 :
 结构说明  : 透明消息-Second Cell邻区测量Cnf消息
*****************************************************************************/
typedef WAS_OM_ACT_OR_SERV_CELL_INFO_CNF_STRU WAS_OM_SECOND_CELL_INFO_CNF_STRU;

/*****************************************************************************
 结构名    : WAS_MNTN_REPORT_GSM_CELL_RSLT_STRU
 协议表格  :
 ASN.1描述 :
 结构说明  : 透明消息-G邻区结果
*****************************************************************************/
typedef struct
{
    VOS_INT16                            sCarrierRSSI;

    VOS_UINT16                           usBcchArfch;

    VOS_UINT16                           usFreqBandInd;

    VOS_UINT16                           usNCC;

    VOS_UINT16                           usBCC;

    VOS_INT16                            sRValue;                                 /* 邻区的R值*/

    VOS_INT16                            sHValue;                                 /* 邻区的H值*/

    PS_BOOL_ENUM_UINT8                   enTreselFlg;                             /* 是否已启动Treselection定时器 */

    PS_BOOL_ENUM_UINT8                   enTevaluateFlg;                          /* 是否已启动Tevaluate定时器 */

    PS_BOOL_ENUM_UINT8                   enTnFlg;                                 /* 是否已启动Tn定时器 */

    VOS_UINT8                            aucReserved[3];
}WAS_MNTN_REPORT_GSM_CELL_RSLT_STRU;


/*****************************************************************************
 结构名    : WAS_MNTN_REPORT_LTE_CELL_RSLT_STRU
 协议表格  :
 ASN.1描述 :
 结构说明  : 透明消息L邻频点上小区结果
*****************************************************************************/
typedef struct
{
    VOS_UINT16                                              usArfcn;
    VOS_UINT16                                              usCellId;
    VOS_INT16                                               sRsrp;              /* RSRP测量值,取值范围[-141*8,-44*8]，单位:0.125dBm */
    VOS_INT16                                               sRsrq;              /* RSRQ测量值 ,取值范围[-20*8，-3*8]，单位:0.125dB */
    VOS_INT16                                               sRssi;              /* RSSI测量值 ,取值范围[-110*8,-20*8],  单位:0.125dBm*/
    PS_BOOL_ENUM_UINT8                                      enTreselFlg;        /* 是否已启动Treselection定时器 */
    VOS_INT8                                                cArfcnPri;         /* 频点优先级信息,无效值为-1, */
}WAS_MNTN_REPORT_LTE_CELL_RSLT_STRU;

/*****************************************************************************
 结构名    : WAS_OM_L_NCELL_INFO_IND_STRU
 协议表格  :
 ASN.1描述 :
 结构说明  : 透明消息LTE邻区测量Ind,最多支持8个LTE频点上报
*****************************************************************************/
typedef struct
{
    VOS_UINT16                              usPrimId;
    VOS_UINT16                              usReserved;

    VOS_UINT8                               aucReserved[1];
    WAS_MNTN_RPT_TYPE_ENUM_UINT8            enReportType;

    VOS_UINT16                              usCellNum;
    WAS_MNTN_REPORT_LTE_CELL_RSLT_STRU      astLTENeighberCellInfo[WAS_L_NCELL_MAX_NUM];
} WAS_OM_L_NCELL_INFO_IND_STRU;

/*****************************************************************************
 结构名    : WAS_OM_SECOND_CELL_INFO_IND_STRU
 协议表格  :
 ASN.1描述 :
 结构说明  : 透明消息Second Cell邻区测量Ind,最多支持6+32个Second Cell上报
*****************************************************************************/
typedef struct
{
    VOS_UINT16                              usPrimId;
    VOS_UINT16                              usReserved;

    VOS_UINT8                               aucReserved[3];
    WAS_MNTN_RPT_TYPE_ENUM_UINT8            enReportType;
    VOS_UINT16                              usMeasQuantity;
    
    VOS_UINT8                               ucServCellNum;                      /* 主小区个数 */
    VOS_UINT8                               ucNeighCellNum;                     /* 邻区个数 */
    WAS_MNTN_REPORT_WCDMA_CELL_RSLT_STRU    astSecondServCellInfo[WAS_SECOND_ACT_SET_CELL_MAX_NUM];    
    WAS_MNTN_REPORT_WCDMA_CELL_RSLT_STRU    astSecondNeighCellInfo[WAS_SECOND_W_NCELL_MAX_NUM];
}WAS_OM_SECOND_CELL_INFO_IND_STRU;


/*****************************************************************************
 结构名    : WAS_OM_G_NCELL_INFO_IND_STRU
 协议表格  :
 ASN.1描述 :
 结构说明  : 透明消息-G邻区测量Ind,最多支持G 6个邻区上报
*****************************************************************************/
typedef struct
{
    VOS_UINT16                              usPrimId;
    VOS_UINT16                              usReserved;

    VOS_UINT8                               aucReserved[1];
    WAS_MNTN_RPT_TYPE_ENUM_UINT8            enReportType;

    VOS_UINT16                              usCellNum;
    WAS_MNTN_REPORT_GSM_CELL_RSLT_STRU      astGsmNeighberCellInfo[WAS_G_NCELL_MAX_NUM];
} WAS_OM_G_NCELL_INFO_IND_STRU;

/*****************************************************************************
 结构名    : OM_WAS_W_CELL_CHG_INFO_REQ_STRU
 协议表格  :
 ASN.1描述 :
 结构说明  :小区变化信息查询
*****************************************************************************/

typedef struct
{
    DIAG_WAS_MSG_COMM_HEAD_STRU         stMsgCommHead;

    WAS_MNTN_RPT_CMD_ENUM_UINT8         enCommand;                              /*停止或开始上报*/
    WAS_MNTN_RPT_TYPE_ENUM_UINT8        enReportType;                           /*上报类型，这里只能是一次上报或者变化上报*/
    VOS_UINT8                           aucReserve1[2];

}OM_WAS_W_CELL_CHG_INFO_REQ_STRU;

typedef WAS_OM_ACT_OR_SERV_CELL_INFO_CNF_STRU WAS_OM_W_CELL_CHG_INFO_CNF_STRU;

/*****************************************************************************
 枚举名    : WAS_CALL_ACCS_IND_ENUM_UINT8
 协议表格  :
 ASN.1描述 :
 枚举说明  :
*****************************************************************************/
enum WAS_CALL_ACCS_IND_ENUM
{
    WAS_CALL_ACCS_UNLIMITED             = 0,
    WAS_CALL_ACCS_EMERGENCY             = 1,
    WAS_CALL_ACCS_BUTT
};
typedef VOS_UINT8 WAS_CALL_ACCS_IND_ENUM_UINT8;

/*****************************************************************************
 结构名    : WAS_OM_W_CELL_CHG_INFO_IND_STRU
 协议表格  :
 ASN.1描述 :
 结构说明  :RNC ID/CELL ID/URA ID RNC编号/小区编号/注册区编号
Cell Beared 小区禁止接入指示
Cell Reserved 小区保留使用指示
UE Camped to a cell UE驻留到小区指示
*****************************************************************************/
typedef struct
{
    VOS_UINT16                              usPrimId;
    VOS_UINT16                              usReserved;

    WAS_MNTN_RPT_TYPE_ENUM_UINT8            enReportType;
    VOS_UINT8                               aucReserve1[1];

    VOS_UINT16                              usDlFreq;                           /* 小区下行频点 ,单位200KHZ*/
    VOS_UINT16                              usUlFreq;                           /* 小区上行频点 ,单位200KHZ*/

    PS_BOOL_ENUM_UINT8                      enCellBarredFlg;                    /* PS_TRUE,表示小区被阻塞，PS_FALSE表示小区未被阻塞 */
    PS_BOOL_ENUM_UINT8                      enCellReservFlag;                   /* PS_TRUE表示小区被reserved*/
    PS_BOOL_ENUM_UINT8                      enCellCampedFlag;                   /* PS_TRUE表示驻留到该小区*/
    VOS_UINT8                               aucReserve2[1];

    VOS_UINT16                              usRncId;                            /* usRncId */ /*10进制显示*/
    VOS_UINT16                              usUeUraId;                          /*10进制显示*/
    VOS_UINT16                              usCellId;                           /*10进制显示*/

    WAS_CALL_ACCS_IND_ENUM_UINT8            enCallAccs;                         /* 0:表示可以进行任意呼叫;1:表示仅能进行紧急呼叫 */
    VOS_UINT8                               aucReserve3[1];

    VOS_UINT16                              usPrimaryScramCode;                 /*usCellId对应的小区扰码*/

    VOS_UINT16                              usScndDlFreq;                       /* 辅载波下行频点 ,单位200KHZ*/
    VOS_UINT8                               aucReserve4[2];
}WAS_OM_W_CELL_CHG_INFO_IND_STRU;

/*****************************************************************************
 枚举名    : WAS_OM_UE_WORK_MODE_TYPE_ENUM
 协议表格  :
 ASN.1描述 :
 枚举说明  : W工作模式
*****************************************************************************/
enum WAS_OM_UE_WORK_MODE_TYPE_ENUM
{
    WAS_OM_UE_WORK_MODE_TYPE_WCDMA,
    WAS_OM_UE_WORK_MODE_TYPE_HSDPA,
    WAS_OM_UE_WORK_MODE_TYPE_HSUPA,
    WAS_OM_UE_WORK_MODE_TYPE_DEACTIVE,
    WAS_OM_UE_WORK_MODE_TYPE_BUTT
};

typedef VOS_UINT8   WAS_OM_UE_WORK_MODE_TYPE_ENUM_UINT8;

/*****************************************************************************
 结构名    : OM_WAS_UE_WORK_MODE_REQ_STRU
 协议表格  :
 ASN.1描述 : W下UE工作模式查询，R99/R5/R6
*****************************************************************************/
typedef struct
{
    DIAG_WAS_MSG_COMM_HEAD_STRU         stMsgCommHead;
}OM_WAS_UE_WORK_MODE_REQ_STRU;

/*****************************************************************************
 结构名    : OM_WAS_UE_WORK_MODE_REQ_STRU
 协议表格  :
 ASN.1描述 : W下UE工作模式查询，R99/R5/R6
*****************************************************************************/
typedef struct
{
    DIAG_WAS_MSG_COMM_HEAD_STRU             stMsgCommHead;

    WAS_OM_UE_WORK_MODE_TYPE_ENUM_UINT8     enWasWorkMode;
    VOS_UINT8                               aucReserve1[3];
}WAS_OM_UE_WORK_MODE_CNF_STRU;


/*****************************************************************************
 结构名    : OM_WAS_UE_STATE_REQ_STRU
 协议表格  :
 ASN.1描述 :W下UE状态查询
*****************************************************************************/
typedef struct
{
    DIAG_WAS_MSG_COMM_HEAD_STRU         stMsgCommHead;

    WAS_MNTN_RPT_CMD_ENUM_UINT8         enCommand;                              /*停止或开始上报*/
    WAS_MNTN_RPT_TYPE_ENUM_UINT8        enReportType;                           /*上报的类型,这里只能是1次上报或者变化上报*/
    VOS_UINT8                           aucReserve1[2];
}OM_WAS_UE_STATE_REQ_STRU;

/*****************************************************************************
 结构名    : WAS_OM_UE_STATE_CNF_STRU
 协议表格  :
 ASN.1描述 :
*****************************************************************************/
typedef WAS_OM_ACT_OR_SERV_CELL_INFO_CNF_STRU WAS_OM_UE_STATE_CNF_STRU;

/*****************************************************************************
 结构名    : WAS_OM_UE_STATE_IND_STRU
 协议表格  :
 ASN.1描述 :动态上报RRC状态
*****************************************************************************/
typedef struct
{
    VOS_UINT16                          usPrimId;
    VOS_UINT16                          usReserved;

    WAS_OM_STATE_IND_ENUM_UINT8         enRrcStateInd;
    PS_BOOL_ENUM_UINT8                  enReadyForCommEdch;
    VOS_UINT8                           aucReserve1[2];
}WAS_OM_UE_STATE_IND_STRU;

/*****************************************************************************
 结构名    : OM_WAS_TIMER_EVENT_REQ_STRU
 协议表格  :
 ASN.1描述 : 定时器事件上报请求
*****************************************************************************/
typedef struct
{
    DIAG_WAS_MSG_COMM_HEAD_STRU         stMsgCommHead;

    VOS_UINT32                          ulTimerEventBitmap;     /* 每一个bit位对应一个定时器事件
                                                                   0 - 该定时器事件不需要上报
                                                                   1 - 该定时器事件需要上报 */

}OM_WAS_TIMER_EVENT_REQ_STRU;

typedef WAS_OM_OTA_CNF_STRU WAS_OM_TIMER_EVENT_CNF_STRU;

/*****************************************************************************
 结构名    : WAS_PRINT_MSG_STRU
 协议表格  :
 ASN.1描述 : WAS打印信息上报
*****************************************************************************/
typedef struct
{
    VOS_UINT32                          ulTick;
    VOS_UINT32                          enLevel;
    PS_FILE_ID_DEFINE_ENUM_UINT32       enFile;
    VOS_UINT32                          ulLine;
    VOS_INT32                           alPara[4];
}WAS_PRINT_RECORD_STRU;

/*****************************************************************************
 结构名    : WAS_PRINT_MSG_STRU
 协议表格  :
 ASN.1描述 : WAS打印信息上报
*****************************************************************************/
typedef struct
{
    VOS_UINT16                          usPrimId;
    VOS_UINT16                          usReserved;

    VOS_UINT32                          ulCnt;
    WAS_PRINT_RECORD_STRU               astData[WAS_PRINT_MSG_MAX_NUM];
}WAS_PRINT_MSG_STRU;

/*****************************************************************************
 结构名    : OM_WAS_CONNECTED_IND_STRU
 协议表格  :
 ASN.1描述 : 工具连接IND
*****************************************************************************/
typedef struct
{
    DIAG_WAS_MSG_COMM_HEAD_STRU         stMsgCommHead;
}OM_WAS_CONNECTED_IND_STRU;

typedef WAS_OM_OTA_CNF_STRU WAS_OM_CONNECTED_CNF_STRU;

/*****************************************************************************
 结构名    : WAS_OM_CELL_INDI_OFFSET_MODIFY_INFO_IND_STRU
 协议表格  :
 ASN.1描述 :
 结构说明  : 小区偏置定制修改信息
*****************************************************************************/
typedef struct
{
    VOS_INT8                            cCellIndiOffsetBeforeModify;            /* 修改前的小区偏置，按照0.5db精度给OM上报 */
    VOS_INT8                            cCellIndiOffsetAfterModify;             /* 修改后的小区偏置，按照0.5db精度给OM上报 */
    VOS_UINT8                           aucReserved[2];
} WAS_OM_CELL_INDI_OFFSET_MODIFY_INFO_IND_STRU;

/*****************************************************************************
 结构名    : WAS_OM_AM_SRB_SEND_STATE_INFO_STRU
 协议表格  :
 ASN.1描述 :
 结构说明  : 层2当前某个信令RB上的发送状态信息
*****************************************************************************/
typedef struct
{
    VOS_UINT8                           ucRbId;
    VOS_UINT8                           aucReserved[3];
    VOS_UINT32                          ulSduThreshold;
    VOS_UINT32                          ulSduTotalLen;
} WAS_OM_AM_SRB_SEND_STATE_INFO_STRU;

/*完整性保护密钥*/
typedef struct
{
    VOS_UINT8                           aucIk[16];    /* IK的结构 */
}WAS_OM_SMC_IK_STRU;

/* SMC调用完整性保护检查函数时使用的结构体 */
typedef struct
{
    VOS_UINT8                           ucDirect;
    VOS_UINT8                           aucReserve1[3];
    WAS_OM_SMC_IK_STRU                  stIk;
    VOS_UINT32                          ulCountI;
    VOS_UINT32                          ulFresh;
    VOS_UINT32                          ulMac;
    VOS_UINT32                          ulLength;
}WAS_OM_SMC_INTEGRITY_F9_ALGOR_STRU;

/*****************************************************************************
 结构名    : WAS_OM_TRANS_IND_STRU
 协议表格  :
 ASN.1描述 : 透传消息上报公共结构
*****************************************************************************/
typedef struct
{
    VOS_UINT16  usPrimId;
    VOS_UINT16  usReserved;
    VOS_UINT8   aucData[4];
}WAS_OM_TRANS_IND_STRU;

/*****************************************************************************
  8 UNION定义
*****************************************************************************/


/*****************************************************************************
  9 OTHERS定义
*****************************************************************************/


/*****************************************************************************
  10 函数声明
*****************************************************************************/

extern WAS_MNTN_OM_OUT_OF_SERVICE_ENUM_UINT8  WAS_MNTN_GetOmOutOfService(VOS_VOID);

extern VOS_UINT8   WAS_MNTN_FilterMsg(MsgBlock *msg);

extern VOS_VOID WAS_MAIN_ReportAbnormalMsgQueue2OM( VOS_UINT32 *pulAbnormalMsgAddr,
                    VOS_UINT32 *pulMsgQueueLength );



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

#endif /* end of WasOmInterface.h */
