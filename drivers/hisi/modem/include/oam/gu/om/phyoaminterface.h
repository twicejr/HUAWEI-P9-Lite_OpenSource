

/******************************************************************************

                  版权所有 (C), 2001-2011, 华为技术有限公司

 ******************************************************************************
  文 件 名   : phyoaminterface.h
  版 本 号   : 初稿
  作    者   : luoqingquan
  生成日期   : 2012年11月14日
  最近修改   :
  功能描述   : phyoaminterface.h 的头文件
  函数列表   :
  修改历史   :
  1.日    期   : 2012年10月14日
    作    者   : luoqingquan
    修改内容   : 创建文件

******************************************************************************/

/*****************************************************************************
  1 其他头文件包含
*****************************************************************************/
#include "vos.h"


#ifndef __PHYOAMINTERFACE_H__
#define __PHYOAMINTERFACE_H__

#ifdef __cplusplus
#if __cplusplus
extern "C" {
#endif
#endif

#pragma pack(4)


/*****************************************************************************
  2 宏定义
*****************************************************************************/

/* 降SAR的ulMask类型 */
#define UPHY_OAM_SAR_MASK_ANTSTATE          ( 0x1 )
#define UPHY_OAM_SAR_MASK_REDUCTION         ( 0x2 )

/* 动态加载段数,目前V9R1上没有实质的加载动作,定义段数为1 */
#define UPHY_DYN_CODE_MODULE_BUTT           ( 0x01 )

/* 必须保持和phytoolinterface.h中UPHY_TOOL_SLEEP_INFO_NUM的大小保持一致 */
#define UPHY_OAM_SLEEP_INFO_NUM             ( 16 )

/*****************************************************************************
  3 枚举定义
*****************************************************************************/



/*****************************************************************************
 枚举名    :UPHY_OAM_MSG_ID_ENUM_UINT16
 协议表格  :
 ASN.1描述 :
 枚举说明  :PHY与OAM原语列表
*****************************************************************************/
enum UPHY_OAM_MSG_ID_ENUM
{
    /* OAM与UPHY_APM的原语 */
    ID_OAM_UPHY_ACTIVE_UPHY_REQ             = 0xD200,                   /* _H2ASN_MsgChoice  UPHY_OAM_ACTIVE_UPHY_REQ_STRU */
    ID_UPHY_OAM_ACTIVE_UPHY_CNF             = 0x2D00,                   /* _H2ASN_MsgChoice  UPHY_OAM_ACTIVE_UPHY_CNF_STRU */

    ID_UPHY_OAM_LOAD_NV_REQ                 = 0x2D01,                   /* _H2ASN_MsgChoice  UPHY_OAM_LOAD_NV_REQ_STRU */
    ID_OAM_UPHY_LOAD_NV_CNF                 = 0xD201,                   /* _H2ASN_MsgChoice  UPHY_OAM_LOAD_NV_CNF_STRU */

    ID_OAM_UPHY_GET_NV_ADDR_REQ             = 0xD202,                   /* _H2ASN_MsgChoice  UPHY_OAM_GET_NV_ADDR_REQ_STRU */
    ID_UPHY_OAM_GET_NV_ADDR_IND             = 0x2D02,                   /* _H2ASN_MsgChoice  UPHY_OAM_GET_NV_ADDR_IND_STRU */

    ID_UPHY_OAM_BOOT_INFO_REQ               = 0x2D03,                   /* _H2ASN_MsgChoice  UPHY_OAM_BOOT_INFO_REQ_STRU */
    ID_OAM_UPHY_BOOT_INFO_IND               = 0xD203,                   /* _H2ASN_MsgChoice  UPHY_OAM_BOOT_INFO_IND_STRU */

    /* OAM与UPHY_DRX的原语 */
    ID_OAM_UPHY_MASTER_WAKE_CMD             = 0xD220,                   /* _H2ASN_MsgChoice  UPHY_OAM_WAKE_CMD_STRU */
    ID_UPHY_OAM_MASTER_SLEEP_IND            = 0x2D20,                   /* _H2ASN_MsgChoice  UPHY_OAM_SLEEP_IND_STRU */

    ID_OAM_UPHY_SLAVE_WAKE_CMD              = 0xD221,                   /* _H2ASN_MsgChoice  UPHY_OAM_WAKE_CMD_STRU */
    ID_UPHY_OAM_SLAVE_SLEEP_IND             = 0x2D21,                   /* _H2ASN_MsgChoice  UPHY_OAM_SLEEP_IND_STRU */


    /* OAM与W/GPHY的原语,根据接收PID区分 */
    ID_OAM_PHY_LOAD_PHY_REQ                 = 0xD240,                   /* _H2ASN_MsgChoice  PHY_OAM_LOAD_PHY_REQ_STRU */
    ID_PHY_OAM_LOAD_PHY_CNF                 = 0x2D40,                   /* _H2ASN_MsgChoice  PHY_OAM_LOAD_PHY_CNF_STRU */

    ID_OAM_PHY_SAR_CTRL_REQ                 = 0xD241,                   /* _H2ASN_MsgChoice  PHY_OAM_SAR_CTRL_REQ_STRU */
    ID_PHY_OAM_SAR_CTRL_CNF                 = 0x2D41,                   /* _H2ASN_MsgChoice  PHY_OAM_SAR_CTRL_CNF_STRU */

    ID_OAM_PHY_SET_WORK_MODE_REQ            = 0xD242,                   /* _H2ASN_MsgChoice  PHY_OAM_SET_WORK_MODE_REQ_STRU */
    ID_PHY_OAM_SET_WORK_MODE_CNF            = 0x2D42,                   /* _H2ASN_MsgChoice  PHY_OAM_SET_WORK_MODE_CNF_STRU */

    /* OAM与GPHY的原语 */
    ID_OAM_GPHY_RF_AGING_TEST_REQ           = 0xD280,                   /* _H2ASN_MsgChoice  GPHY_OAM_RF_AGING_TEST_REQ_STRU */
    ID_GPHY_OAM_RF_AGING_TEST_CNF           = 0x2D80,                   /* _H2ASN_MsgChoice  GPHY_OAM_RF_AGING_TEST_CNF_STRU */


    /* OAM与WPHY的原语 */
    ID_OAM_WPHY_RF_AGING_TEST_REQ           = 0xD2C0,                   /* _H2ASN_MsgChoice  WPHY_OAM_RF_AGING_TEST_REQ_STRU */
    ID_WPHY_OAM_RF_AGING_TEST_CNF           = 0x2DC0,                   /* _H2ASN_MsgChoice  WPHY_OAM_RF_AGING_TEST_CNF_STRU */

    ID_OAM_WPHY_UPDATE_REG_STATE_REQ        = 0xD2C1,                   /* _H2ASN_MsgChoice  WPHY_OAM_UPDATE_REG_STATE_REQ_STRU */
    ID_WPHY_OAM_UPDATE_REG_STATE_CNF        = 0x2DC1,                   /* _H2ASN_MsgChoice  WPHY_OAM_UPDATE_REG_STATE_CNF_STRU */

    ID_OAM_WPHY_QUERY_SAMPLE_REQ            = 0xD2D1,                   /* _H2ASN_MsgChoice  OAM_WPHY_QUERY_SAMPLE_REQ */
    ID_WPHY_OAM_QUERY_SAMPLE_CNF            = 0x2DD1,                   /* _H2ASN_MsgChoice  WPHY_OAM_QUERY_SAMPLE_CNF */

    ID_PHY_OAM_MSG_ID_BUTT
};
typedef VOS_UINT16 UPHY_OAM_MSG_ID_ENUM_UINT16;



typedef VOS_UINT32 SLEEP_MODE_ENUM_UINT32;


/*****************************************************************************
 枚举名    :UPHY_OAM_BUSINESS_TYPE_ENUM_UINT16
 协议表格  :
 ASN.1描述 :
 枚举说明  :物理层代码加载业务类型
*****************************************************************************/
enum UPHY_OAM_BUSINESS_TYPE_ENUM
{
    UPHY_OAM_BUSINESS_TYPE_NORMAL           = 0,                                /* 正常业务类型 */
    UPHY_OAM_BUSINESS_TYPE_CT                  ,                                /* 校准CT类型 */
    UPHY_OAM_BUSINESS_TYPE_NO_SIG_BT           ,                                /* 高层非信令BT类型 */
    UPHY_OAM_BUSINESS_TYPE_SIG_BT              ,                                /* 信令BT类型 */

    UPHY_OAM_BUSINESS_TYPE_BUTT
};
typedef VOS_UINT16 UPHY_OAM_BUSINESS_TYPE_ENUM_UINT16;



/*****************************************************************************
 枚举名    :UPHY_OAM_WAKE_TYPE_ENUM_UINT32
 协议表格  :
 ASN.1描述 :
 枚举说明  :唤醒类型定义
*****************************************************************************/
enum UPHY_OAM_WAKE_TYPE_ENUM
{
    UPHY_OAM_NORMAL_WAKE                    = 0,
    UPHY_OAM_FORCE_WAKE                     = 1,
    UPHY_OAM_WAKE_TYPE_BUTT
};
typedef VOS_UINT32 UPHY_OAM_WAKE_TYPE_ENUM_UINT32;



/*****************************************************************************
 枚举名    :UPHY_OAM_RSLT_ENUM_UINT16
 协议表格  :
 ASN.1描述 :
 枚举说明  :UPHY回复OAM的CNF中,携带的处理结果枚举
*****************************************************************************/
enum UPHY_OAM_RSLT_ENUM
{
    UPHY_OAM_RSLT_SUCC                      = 0,
    UPHY_OAM_RSLT_FAIL                      = 1,

    UPHY_OAM_RSLT_BUTT
};
typedef VOS_UINT16 UPHY_OAM_RSLT_ENUM_UINT16;

/*****************************************************************************
 枚举名    :UPHY_OAM_BOOL_ENUM_UINT16
 协议表格  :
 ASN.1描述 :
 枚举说明  :UPHY回复OAM的CNF中,携带的处理结果枚举
*****************************************************************************/
enum UPHY_OAM_BOOL_ENUM
{
    UPHY_OAM_INVALID                        = 0,
    UPHY_OAM_VALID                          = 1,

    UPHY_OAM_BUTT
};
typedef VOS_UINT16 UPHY_OAM_BOOL_ENUM_UINT16;


/*****************************************************************************
 枚举名    :UPHY_OAM_AGING_TEST_CTRL_ENUM_UINT16
 协议表格  :
 ASN.1描述 :
 枚举说明  :老化测试枚举定义
*****************************************************************************/
enum UPHY_OAM_AGING_TEST_CTRL_ENUM
{
    UPHY_OAM_AGING_TEST_ON                  = 0x5555,
    UPHY_OAM_AGING_TEST_OFF                 = 0xaaaa,
    UPHY_OAM_AGING_TEST_BUTT
};
typedef VOS_UINT16 UPHY_OAM_AGING_TEST_CTRL_ENUM_UINT16;


enum PS_REG_UPDATE_STATE_ENUM
{
    PS_REG_STATE_STOP = 0,
    PS_REG_STATE_ACTIVE,
    PS_REG_STATE_BUTT
};
typedef VOS_UINT16  PS_REG_UPDATE_STATE_ENUM_UINT16;


/*****************************************************************************
 枚举名    :UPHY_OAM_NV_INDEX_UINT16
 协议表格  :
 ASN.1描述 :
 枚举说明  : NV项索引 取值为0-15
             其中全网通的功能使用index=10
             index8~15给海思商用特性商用
             index0~7保留开放给终端调试使用
*****************************************************************************/
enum UPHY_OAM_NV_INDEX_ENUM
{
    UPHY_OAM_NV_INDEX_FULL_NET  = 10,
    UPHY_OAM_NV_INDEX_BUTT      = 16
};

typedef VOS_UINT16  UPHY_OAM_NV_INDEX_ENUM_UINT16;

/*****************************************************************************
 枚举名    :PHY_OM_TRANS_MSG_ID_ENUM_UINT16
 协议表格  :
 ASN.1描述 :
 枚举说明  :物理理层和OM之间消息透传的ID
*****************************************************************************/
enum PHY_OM_TRANS_MSG_ID_ENUM
{
    ID_PHY_OM_TRANS_MSG_ID              = 0x5001,
    ID_PHY_AT_TRANS_MSG_ID              = 0x4201,

    ID_PHY_OM_TRANS_MSG_BUTT

};
typedef VOS_UINT16 PHY_OM_TRANS_MSG_ID_ENUM_UINT16;

/*****************************************************************************
 枚举名    :UPHY_OAM_RTT_STATE_ENUM_UINT16
 协议表格  :
 ASN.1描述 :
 枚举说明  : 当前RTT运行的状态
*****************************************************************************/
enum UPHY_OAM_RTT_STATE_ENUM
{
    UPHY_OAM_RTT_STATE_IDLE             = 0,
    UPHY_OAM_RTT_STATE_CS                  ,
    UPHY_OAM_RTT_STATE_PS                  ,
    UPHY_OAM_RTT_STATE_BUTT
};
typedef VOS_UINT16 UPHY_OAM_RTT_STATE_ENUM_UINT16;

/*****************************************************************************
  4 消息头定义
*****************************************************************************/

/*****************************************************************************
 结构名    : PHY_TOOL_MSG_HEAD_STRU
 协议表格  :
 结构说明  : 工具和物理层之间消息透传时消息透结构
*****************************************************************************/

typedef struct
{
    PHY_OM_TRANS_MSG_ID_ENUM_UINT16     usTransPrimId;                          /* 透传消息ID = 0x5001 */
    VOS_UINT16                          usRsv;                                  /* 保留 */
}PHY_TOOL_MSG_HEAD_STRU;




/*****************************************************************************
  5 消息定义
*****************************************************************************/
typedef struct
{
    VOS_MSG_HEADER
    VOS_UINT16                              usMsgId;                            /* 原语ID */
    VOS_UINT8                               aucData[2];                         /* Msg Data*/
}PHY_OAM_MSG_STRU;


/*****************************************************************************
  6 STRUCT定义
*****************************************************************************/




/*****************************************************************************
 结构名    : UPHY_OAM_ACTIVE_UPHY_REQ_STRU
 结构说明  : 上电初始化命令请求
*****************************************************************************/
typedef struct
{
    VOS_MSG_HEADER
    UPHY_OAM_MSG_ID_ENUM_UINT16             enMsgId;                            /* 原语ID */
    MODEM_ID_ENUM_UINT16                    enModem;                            /* MODEM信息 */
    VOS_RATMODE_ENUM_UINT32                 enRatTpye;                          /* 模式 */
}UPHY_OAM_ACTIVE_UPHY_REQ_STRU;




/*****************************************************************************
 结构名    : UPHY_OAM_ACTIVE_UPHY_CNF_STRU
 结构说明  : 上电初始化命令回复
*****************************************************************************/
typedef struct
{
    VOS_MSG_HEADER
    UPHY_OAM_MSG_ID_ENUM_UINT16             enMsgId;                            /* 原语ID */
    MODEM_ID_ENUM_UINT16                    enModem;                            /* MODEM信息 */
    VOS_RATMODE_ENUM_UINT32                 enRatTpye;                          /* 模式 */
    UPHY_OAM_RSLT_ENUM_UINT16               enRslt;                             /* 处理结果 */
    VOS_UINT16                              usRsv;                              /* 保留 */
}UPHY_OAM_ACTIVE_UPHY_CNF_STRU;



/*****************************************************************************
 结构名    : UPHY_OAM_LOAD_NV_REQ_STRU
 结构说明  : UPHY向OAM主动上报NV首地址,OAM收到地址后,将NV项写入
*****************************************************************************/
typedef struct
{
    VOS_MSG_HEADER
    UPHY_OAM_MSG_ID_ENUM_UINT16             enMsgId;                            /* 原语ID */
    MODEM_ID_ENUM_UINT16                    enModem;                            /* MODEM信息 */
    VOS_RATMODE_ENUM_UINT32                 enRatMode;                          /* 上报模式 */
    VOS_UINT32                              uwNvAddr;
}UPHY_OAM_LOAD_NV_REQ_STRU;




/*****************************************************************************
 结构名    : UPHY_OAM_LOAD_NV_CNF_STRU
 结构说明  : OAM获取首地址后,将NV项写入,然后回复CNF
*****************************************************************************/
typedef struct
{
    VOS_MSG_HEADER
    UPHY_OAM_MSG_ID_ENUM_UINT16             enMsgId;                            /* 原语ID */
    MODEM_ID_ENUM_UINT16                    enModem;                            /* MODEM信息 */
    VOS_RATMODE_ENUM_UINT32                 enRatMode;                          /* 上报模式 */
    UPHY_OAM_RSLT_ENUM_UINT16               enRslt;                             /* 处理结果 */
    VOS_UINT16                              usRsv;                              /* 保留 */
}UPHY_OAM_LOAD_NV_CNF_STRU;




/*****************************************************************************
 结构名    : UPHY_OAM_GET_NV_ADDR_REQ_STRU
 结构说明  : OAM下发获取NV项的首地址请求
*****************************************************************************/
typedef struct
{
    VOS_MSG_HEADER
    UPHY_OAM_MSG_ID_ENUM_UINT16             enMsgId;                            /* 原语ID */
    MODEM_ID_ENUM_UINT16                    enModem;                            /* MODEM信息 */
    VOS_RATMODE_ENUM_UINT32                 enRatMode;                          /* 上报模式 */
}UPHY_OAM_GET_NV_ADDR_REQ_STRU;



/*****************************************************************************
 结构名    : UPHY_OAM_GET_NV_ADDR_IND_STRU
 结构说明  : UPHY向OAM回复NV首地址
*****************************************************************************/
typedef struct
{
    VOS_MSG_HEADER
    UPHY_OAM_MSG_ID_ENUM_UINT16             enMsgId;                            /* 原语ID */
    MODEM_ID_ENUM_UINT16                    enModem;                            /* MODEM信息 */
    VOS_RATMODE_ENUM_UINT32                 enRatMode;                          /* 上报模式 */
    VOS_UINT32                              uwNvAddr;
}UPHY_OAM_GET_NV_ADDR_IND_STRU;





/*****************************************************************************
 结构名    : UPHY_OAM_BOOT_INFO_REQ_STRU
 结构说明  : UPHY向OAM请求信息,包括:
             ulUmtsBandBitMap:W支持的频段
             ulCQIAddr:CQI表首地址
             ulAPTAddr:APT表首地址
             ulETAddr:ET表首地址
             UPHY_MODULE_ADDR_INFO_STRU:加载的段信息
*****************************************************************************/
typedef struct
{
    VOS_MSG_HEADER
    UPHY_OAM_MSG_ID_ENUM_UINT16             enMsgId;                            /* 原语ID */
    MODEM_ID_ENUM_UINT16                    enModem;                            /* MODEM信息 */
    VOS_RATMODE_ENUM_UINT32                 enRatMode;                          /* 上报模式 */
}UPHY_OAM_BOOT_INFO_REQ_STRU;




/*****************************************************************************
 结构名    : UPHY_OAM_BOOT_INFO_IND_STRU
 结构说明  : OAM下发BOOT INFO相关信息给GPHY
             ulUmtsBandBitMap:W支持的频段
             ulCQIAddr:CQI表首地址
             ulAPTAddr:APT表首地址
             ulETAddr:ET表首地址
             PHY_MODULE_ADDR_INFO_STRU:加载的段信息
             上移情况下,没有加载,不需要加载段地址信息,因此本接口保留,不写数据.
             本信息一张卡获取一次,如果已经获取,则可以不再获取
*****************************************************************************/

typedef struct
{
    VOS_UINT32                              ulSegSDRamAddr;                         /* 数据段或者代码段在SDRAM中的地址 */
    VOS_UINT32                              ulSegSDRamLength;                       /* 数据段或者代码段长度 */
    VOS_UINT32                              ulSegTcmAddr;                           /* 数据段或者代码段在DSP内部的AHB地址 */
}UPHY_MODULE_ADDR_INFO_STRU;

typedef struct
{
    VOS_MSG_HEADER
    UPHY_OAM_MSG_ID_ENUM_UINT16             enMsgId;                            /* 原语ID */
    MODEM_ID_ENUM_UINT16                    enModem;                            /* MODEM信息 */
    VOS_RATMODE_ENUM_UINT32                 enRatMode;                          /* 上报模式 */
    VOS_UINT32                              ulUmtsBandBitMap;                   /* 频段有效位图 */
    VOS_UINT32                              ulCQIAddr;                          /* CQI表在SDRAM中的首地址 */
    VOS_UINT32                              ulAPTAddr;                          /* APT表地址:注意V3R3这个地址段没有 */
    VOS_UINT32                              ulETAddr;                           /* ET表地址:注意V3R3这个地址段没有 */
    UPHY_MODULE_ADDR_INFO_STRU              astPhyModuleAddrInfo[UPHY_DYN_CODE_MODULE_BUTT];
}UPHY_OAM_BOOT_INFO_IND_STRU;






/*****************************************************************************
 结构名    : UPHY_OAM_WAKE_CMD_STRU
 结构说明  : OAM给UPHY_DRX下发唤醒:包含信息为:MODEM/MODE/主模/从模/强制/正常唤醒
*****************************************************************************/
typedef struct
{
    VOS_MSG_HEADER
    UPHY_OAM_MSG_ID_ENUM_UINT16             enMsgId;                            /* 消息ID */
    MODEM_ID_ENUM_UINT16                    enModem;                            /* MODEM信息 */
    VOS_RATMODE_ENUM_UINT32                 enRatMode;                          /* 上报模式 */
    UPHY_OAM_WAKE_TYPE_ENUM_UINT32          enWakeType;                         /* 唤醒类型 */
    VOS_UINT8                               pRecordInfo[4];                     /* 唤醒时间可维可测信息 */
}UPHY_OAM_WAKE_CMD_STRU;



/*****************************************************************************
 结构名    : UPHY_OAM_SLEEP_IND_STRU
 结构说明  : UPHY_DRX 给OAM发送睡眠包含信息为:MODEM/MODE/主模/从模/睡眠
*****************************************************************************/
typedef struct
{
    VOS_MSG_HEADER
    UPHY_OAM_MSG_ID_ENUM_UINT16             enMsgId;                            /* 原语ID */
    MODEM_ID_ENUM_UINT16                    enModem;                            /* MODEM信息 */
    VOS_RATMODE_ENUM_UINT32                 enRatMode;                          /* 上报模式 */
    VOS_UINT32                              uwCurSlice;                         /* 当前Slice */
    VOS_UINT32                              uwCalSleepLen;                      /* 计算的睡眠长度 */
    VOS_UINT32                              uwCalCLkSwitchLen;                  /* 计算的时钟切换长度 */
    VOS_UINT32                              uwExptWakeSlice;                    /* 期望的唤醒时间 */
    VOS_UINT32                              uwCfgGaugePara;                     /* 配置的校准参数 */
    VOS_UINT32                              uwCfgSleepLen;                      /* 配置的睡眠长度 */
    VOS_UINT32                              uwCfgClkSwitchLen;                  /* 配置的时钟切换长度 */
}UPHY_OAM_SLEEP_IND_STRU;





/*****************************************************************************
 结构名    : PHY_OAM_LOAD_PHY_REQ_STRU
 结构说明  : OAM下发加载W/GPHY,接入模式,信令/非信令
*****************************************************************************/
typedef struct
{
    VOS_MSG_HEADER
    UPHY_OAM_MSG_ID_ENUM_UINT16             enMsgId;                            /* 原语ID */
    MODEM_ID_ENUM_UINT16                    enModem;                            /* MODEM信息 */
    VOS_RATMODE_ENUM_UINT32                 enRatMode;                          /* 上报模式 */
    UPHY_OAM_BUSINESS_TYPE_ENUM_UINT16      enBusinessType;                     /* 加载业务类型 */
    VOS_UINT16                              usRsv;                              /* 保留 */
}PHY_OAM_LOAD_PHY_REQ_STRU;





/*****************************************************************************
 结构名    : PHY_OAM_LOAD_PHY_CNF_STRU
 结构说明  : W/GPHY接收到LOAD命令加载完成后回复CNF
*****************************************************************************/
typedef struct
{
    VOS_MSG_HEADER
    UPHY_OAM_MSG_ID_ENUM_UINT16             enMsgId;                            /* 原语ID */
    MODEM_ID_ENUM_UINT16                    enModem;                            /* MODEM信息 */
    VOS_RATMODE_ENUM_UINT32                 enRatMode;                          /* 上报模式 */
    UPHY_OAM_RSLT_ENUM_UINT16               enRslt;                             /* 处理结果 */
    VOS_UINT16                              usRsv;                              /* 保留 */
}PHY_OAM_LOAD_PHY_CNF_STRU;



/*****************************************************************************
 结构名    : PHY_OAM_SET_WORK_MODE_REQ_STRU
 结构说明  : OAM下发SET_WORK_MODE给W/GPHY,接入模式,信令/非信令
*****************************************************************************/
typedef struct
{
    VOS_MSG_HEADER
    UPHY_OAM_MSG_ID_ENUM_UINT16             enMsgId;                            /* 原语ID */
    MODEM_ID_ENUM_UINT16                    enModem;                            /* MODEM信息 */
    VOS_RATMODE_ENUM_UINT32                 enMasterMode;                       /* 主模模式 */
    VOS_RATMODE_ENUM_UINT32                 enSlaveMode;                        /* 从模模式 */
    UPHY_OAM_BUSINESS_TYPE_ENUM_UINT16      enBusinessType;                     /* 加载业务类型 */
    UPHY_OAM_BOOL_ENUM_UINT16               enPhyInitFlag;                      /* 是否需要初始化PHY */
    UPHY_OAM_BOOL_ENUM_UINT16               enNvUpdateFlag;                     /* 是否需要更新NV项 */
    VOS_UINT16                              sRsv;
}PHY_OAM_SET_WORK_MODE_REQ_STRU;



/*****************************************************************************
 结构名    : PHY_OAM_SET_WORK_MODE_CNF_STRU
 结构说明  : W/GPHY接收到SET_WORK_MODE命令加载完成后回复CNF
*****************************************************************************/
typedef struct
{
    VOS_MSG_HEADER
    UPHY_OAM_MSG_ID_ENUM_UINT16             enMsgId;                            /* 原语ID */
    MODEM_ID_ENUM_UINT16                    enModem;                            /* MODEM信息 */
    VOS_RATMODE_ENUM_UINT32                 enRatMode;                          /* 上报模式 */
    UPHY_OAM_RSLT_ENUM_UINT16               enRslt;                             /* 处理结果 */
    VOS_UINT16                              usRsv;                              /* 保留 */
}PHY_OAM_SET_WORK_MODE_CNF_STRU;



/*****************************************************************************
 结构名    : PHY_OAM_SAR_CTRL_REQ_STRU
 结构说明  : OAM给W/GPHY下发SAR控制命令
*****************************************************************************/
typedef struct
{
    VOS_MSG_HEADER
    UPHY_OAM_MSG_ID_ENUM_UINT16             enMsgId;                            /* 消息ID */
    VOS_UINT16                              usRsv;                              /* 保留 */
    VOS_UINT32                              ulMask;                             /* 变更类型 */
    VOS_INT32                               lAntenStatus;                       /* 当前天线的状态，仅在mask为PHY_OM_SAR_MASK_ANTSTATE时，该域才有效,如果值为-1代表底软函数执行错误*/
    VOS_UINT32                              ulSarReduction;                     /* 功率回退等级,仅在mask为PHY_OM_SAR_MASK_REDUCTION时,该域才有效*/
}PHY_OAM_SAR_CTRL_REQ_STRU;




/*****************************************************************************
 结构名    : PHY_OAM_SAR_CTRL_CNF_STRU
 结构说明  : W/GPHY给OAM回复SAR控制命令
*****************************************************************************/
typedef struct
{
    VOS_MSG_HEADER
    UPHY_OAM_MSG_ID_ENUM_UINT16             enMsgId;                            /* 消息ID */
    UPHY_OAM_RSLT_ENUM_UINT16               enRslt;                             /* 处理结果 */
}PHY_OAM_SAR_CTRL_CNF_STRU;



/*****************************************************************************
 结构名    : GPHY_OAM_RF_AGING_TEST_REQ_STRU
 结构说明  : OAM给GPHY下发老化测试命令
*****************************************************************************/
typedef struct
{
    VOS_MSG_HEADER
    UPHY_OAM_MSG_ID_ENUM_UINT16             enMsgId;                            /* 消息ID */
    VOS_UINT16                              usRsv;                              /* 保留 */
    VOS_UINT16                              usFreqNum;                          /* (Band << 12) | Arfcn */
    UPHY_OAM_AGING_TEST_CTRL_ENUM_UINT16    enTxEnable;                         /* 发送使能控制:0x5555-使能发送;0xAAAA-停止发送;TSC 0; TxData: 随机数 */
    VOS_UINT16                              usModType;                          /* 发射调制方式:0为GMSK调制;1为8PSK调制方式 */
    VOS_UINT16                              usTxPower;                          /* 目标发射功率,单位为0.1dBm,GSM和EDGE共用 */
    VOS_UINT16                              usSlotCnt;                          /* 配置时隙个数，范围1~4，不需指定具体使用哪些时隙，DSP自动配置1~4时隙发射 */
    VOS_UINT16                              usRsv2;
}GPHY_OAM_RF_AGING_TEST_REQ_STRU;



/*****************************************************************************
 结构名    : GPHY_OAM_RF_AGING_TEST_CNF_STRU
 结构说明  : OAM给GPHY下发老化测试命令处理后回复CNF
*****************************************************************************/
typedef struct
{
    VOS_MSG_HEADER
    UPHY_OAM_MSG_ID_ENUM_UINT16             enMsgId;                            /* 原语ID */
    UPHY_OAM_RSLT_ENUM_UINT16               enRslt;                             /* 处理结果 */
}GPHY_OAM_RF_AGING_TEST_CNF_STRU;



/*****************************************************************************
 结构名    : WPHY_OAM_RF_AGING_TEST_REQ_STRU
 结构说明  : OAM给WPHY下发老化测试命令
*****************************************************************************/
typedef struct
{
    VOS_MSG_HEADER
    UPHY_OAM_MSG_ID_ENUM_UINT16             enMsgID;                                /* 消息ID */
    VOS_UINT16                              usRsv;                                  /* 保留位 */
    UPHY_OAM_AGING_TEST_CTRL_ENUM_UINT16    enTxOnOff;                              /* 发送使能控制:0x5555-使能发送;0xAAAA-停止发送 */
    VOS_UINT16                              usTxBand;                               /* band */
    VOS_UINT16                              usTxChannel;                            /* 邋邋 */
    VOS_UINT16                              usTxPower;                              /* 目标发射功率,单位为0.1dBm */
}WPHY_OAM_RF_AGING_TEST_REQ_STRU;


/*****************************************************************************
 结构名    : WPHY_OAM_RF_AGING_TEST_CNF_STRU
 结构说明  : OAM给WPHY下发老化测试命令处理后回复CNF
*****************************************************************************/
typedef struct
{
    VOS_MSG_HEADER
    UPHY_OAM_MSG_ID_ENUM_UINT16             enMsgId;                            /* 原语ID */
    UPHY_OAM_RSLT_ENUM_UINT16               enRslt;                             /* 处理结果 */
}WPHY_OAM_RF_AGING_TEST_CNF_STRU;



/*****************************************************************************
 结构名    : WPHY_OAM_UPDATE_REG_STATE_REQ_STRU
 协议表格  :
 结构说明  : 寄存器勾包配置消息原语控制请求
*****************************************************************************/
typedef struct
{
    VOS_MSG_HEADER
    UPHY_OAM_MSG_ID_ENUM_UINT16             enMsgId;
    PS_REG_UPDATE_STATE_ENUM_UINT16         enRegState;                         /* 0：表示不进行寄存器勾包, 1：进行寄存器勾包 */
}WPHY_OAM_UPDATE_REG_STATE_REQ_STRU;


/*****************************************************************************
 结构名    : WPHY_OAM_UPDATE_REG_STATE_CNF_STRU
 协议表格  :
 结构说明  : 寄存器勾包配置消息原语回复
*****************************************************************************/
typedef struct
{
    VOS_MSG_HEADER
    UPHY_OAM_MSG_ID_ENUM_UINT16             enMsgId;                            /* 原语ID */
    UPHY_OAM_RSLT_ENUM_UINT16               enRslt;                             /* 处理结果 */
}WPHY_OAM_UPDATE_REG_STATE_CNF_STRU;

/*****************************************************************************
 结构名    : WPHY_OAM_QUERY_SAMPLE_REQ_STRU
 结构说明  : 获取ACPU PHY ADDR接口消息结构体
*****************************************************************************/
typedef struct
{
    VOS_MSG_HEADER
    UPHY_OAM_MSG_ID_ENUM_UINT16             enMsgId;                            /* 原语ID */
    VOS_UINT16                              usRsv;                              /* 保留位 */
}WPHY_OAM_QUERY_SAMPLE_REQ_STRU;

/*****************************************************************************
 结构名    : WPHY_OAM_QUERY_SAMPLE_CNF_STRU
 结构说明  : 获取ACPU PHY ADDR接口消息结构体
*****************************************************************************/
typedef struct
{
    VOS_MSG_HEADER
    UPHY_OAM_MSG_ID_ENUM_UINT16             enMsgId;                            /* 原语ID */
    VOS_UINT16                              esRslt;                             /* 处理结果:VOS_TURE:表示查询结果可用。VOS_FALSE:表示查询地址为空 */
    VOS_UINT32                              ulPhyAddr;                          /* PHY地址 */
    VOS_UINT32                              ulPhySize;                          /* PHY内存大小 */
}WPHY_OAM_QUERY_SAMPLE_CNF_STRU;

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


/*****************************************************************************
 函 数 名  : SLEEP_MasterWakeSlave
 功能描述  : GUPHY作为主模唤醒从模函数.
 输入参数  : MODEM_ID_ENUM_UINT16      enModem   需要唤醒的MODEM
             VOS_RATMODE_ENUM_UINT32   enRatMode 需要唤醒的MODE

 输出参数  : 无

 返 回 值  : VOS_UINT32
*****************************************************************************/
VOS_UINT32 SLEEP_MasterWakeSlave(
                    SLEEP_MODE_ENUM_UINT32   enRatMode );


/*****************************************************************************
 函 数 名  : SLEEP_AwakeInfoGet
 功能描述  : 获取器件上电流程
 输入参数  : SLEEP_MODE_ENUM_UINT32 enMode  当前模式
             VOS_UINT32 uLen                传入的数组长度,32bit为单位
 输出参数  : VOS_UINT32 *pstDrxInfo         上电流程时间信息
 返 回 值  : VOS_UINT32
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2014年3月11日
    作    者   : s00207770
    修改内容   : 新生成函数

*****************************************************************************/
VOS_UINT32 SLEEP_AwakeInfoGet( SLEEP_MODE_ENUM_UINT32 enMode, VOS_UINT32 *pstAwakeHWInfo, VOS_UINT32 uLen );
VOS_VOID HPA_2GFrameIsr_CB(MODEM_ID_ENUM_UINT16 enModemID);
VOS_VOID HPA_3GFrameIsr_CB(VOS_VOID);
extern UPHY_OAM_RTT_STATE_ENUM_UINT16 UPHY_COMM_GetRttStateInfo( MODEM_ID_ENUM_UINT16 enModemId, VOS_RATMODE_ENUM_UINT32 enRttMode );

VOS_UINT16 UPHY_DSDA_GetGsmSlaveDrxFlag( MODEM_ID_ENUM_UINT16 enModemId );

/*****************************************************************************
 函 数 名  : SLEEP_BBE16CprocResumeProc
 功能描述  : OAM提供注册函数给CPROC注册resume proc
 输入参数  : SLEEP_BBE16_CPROC_RESUME_FUNC pFun
 输出参数  : 无
 返 回 值  : VOS_VOID
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2015年9月15日
    作    者   : x00306642
    修改内容   : 新生成函数

*****************************************************************************/
typedef VOS_VOID (*SLEEP_BBE16_CPROC_WAKEUP_FUNC)(VOS_VOID* pulPara);

typedef VOS_VOID (*SLEEP_BBE16_CPROC_SLEEP_FUNC)(VOS_VOID* pulPara);

/*****************************************************************************
 函 数 名  : SLEEP_BBE16CprocWakeupProc
 功能描述  : OAM提供注册函数给CPROC注册Wakeup handler
 输入参数  : SLEEP_BBE16_CPROC_WAKEUP_FUNC pFun,
             VOS_RATMODE_ENUM_UINT32 enMode,
             VOS_VOID* pulPara
 输出参数  : 无
 返 回 值  : VOS_VOID
 调用函数  :
 被调函数  :

*****************************************************************************/
VOS_VOID SLEEP_BBE16CprocWakeupProc(SLEEP_BBE16_CPROC_WAKEUP_FUNC pFun, VOS_RATMODE_ENUM_UINT32 enMode, VOS_VOID *pulPara);

/*****************************************************************************
 函 数 名  : SLEEP_BBE16CprocSleepProc
 功能描述  : OAM提供注册函数给CPROC注册Sleep handler
 输入参数  : SLEEP_BBE16_CPROC_SLEEP_FUNC pFun,
             VOS_RATMODE_ENUM_UINT32 enMode,
             VOS_VOID* pulPara
 输出参数  : 无
 返 回 值  : VOS_VOID
 调用函数  :
 被调函数  :

*****************************************************************************/
VOS_VOID SLEEP_BBE16CprocSleepProc(SLEEP_BBE16_CPROC_SLEEP_FUNC pFun, VOS_RATMODE_ENUM_UINT32 enMode, VOS_VOID *pulPara);

/*****************************************************************************
 函 数 名  : SLEEP_IsSlaveSleep
 功能描述  : 获取当前模式是否处于从模低功耗状态
 输入参数  : SLEEP_MODE_ENUM_UINT32 enMode  当前模式
 输出参数  : 无
 返 回 值  : VOS_BOOL   VOS_TRUE    当前模式处于从模低功耗态
                        VOS_FALSE   当前模式没有处于从模低功耗状态
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2015年11月30日
    作    者   : s00207770
    修改内容   : 新生成函数

*****************************************************************************/
VOS_BOOL SLEEP_IsSlaveSleep(SLEEP_MODE_ENUM_UINT32 enMode);

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

#endif /* end of gphytoolinterface.h */

