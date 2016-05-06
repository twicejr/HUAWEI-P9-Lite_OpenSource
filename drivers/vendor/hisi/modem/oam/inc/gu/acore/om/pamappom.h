

/******************************************************************************

                  版权所有 (C), 2001-2015, 华为技术有限公司

 ******************************************************************************
  文 件 名      : pamappom.h
  版 本 号      : 初稿
  作    者      : H00300778
  生成日期      : 2015年6月24日
  最近修改      :
  功能描述      : 该h文件给出了pamappom.c的头文件
  函数列表      :
  修改历史      :
  1.日    期    : 2015年6月24日
    作    者    : H00300778
    修改内容    : 创建文件

******************************************************************************/


#ifndef __PAMAPPOM_H__
#define __PAMAPPOM_H__


#ifdef __cplusplus
#if __cplusplus
extern "C"{
#endif
#endif /* __cplusplus */

/****************************************************************************
  1 其他头文件包含
*****************************************************************************/
#include "vos.h"
#include "msp_diag_comm.h"
#include "mdrv.h"


/*****************************************************************************
  2 宏定义
******************************************************************************/
#define  OM_ICC_LOG_PATH                "/data/modemlog/Log/Icc-log"
#define  OM_ICC_UNITARY_LOG_PATH        "/modem_log/Log/Icc-log"

#define OM_ICC_BUFFER_SIZE              (16*1024)

#define OM_DRV_MAX_IO_COUNT             (8)        /*一次提交给底软接口的最大数目*/

#define OM_ICC_CHANNEL_PRIORITY         (0)

#define OM_ICC_HANDSHAKE_TIME_MAX       (200000)

#define OM_LOG_FILE_MAX_SIZE            (0x40000)

/* AT<->AT的屏蔽处理，移到GuNasLogFilter.c */

#if  ( FEATURE_MULTI_MODEM == FEATURE_ON )
#define OSA_ICC_BUFFER_SIZE                                     (128*1024)
#else
#define OSA_ICC_BUFFER_SIZE                                     (64*1024)
#endif  /* ( FEATURE_MULTI_MODEM == FEATURE_ON ) */

/*******************************************************************************
  3 枚举定义
*****************************************************************************/


enum OM_DATA_DESTINATION_ENUM
{
    OMRL_UART = 0,              /*物理串口*/
    OMRL_USB,                   /*USB通道*/
    OMRL_FS,                    /*写文件系统*/
    OMRL_WIFI,                  /*SOCKET WIFI通道*/
    OMRL_SD,                    /*写SD卡*/
    OMRL_PORT_BUTT
};
typedef VOS_UINT16 OM_DATA_DESTINATION_ENUM_UIN16;
typedef VOS_UINT32 OM_DATA_DESTINATION_ENUM_UIN32;

enum OM_USB_PORT_ENUM
{
    OMRL_USB_OM = 1,            /*OM虚拟端口*/
    OMRL_USB_AT,                /*AT虚拟端口*/
    OMRL_USB_SHELL,             /*shell虚拟端口*/
    OMRL_USB_CONTROL = 5,
    OMRL_USB_BUTT
};
typedef VOS_UINT16 OM_USB_PORT_ENUM_UINT16;
typedef VOS_UINT32 OM_USB_PORT_ENUM_UINT32;

enum OM_ICC_CHANNEL_ENUM
{
    OM_OM_ICC_CHANNEL           = 0,    /*当前通道用于传输OM数据*/
    OM_OSA_MSG_ICC_CHANNEL,             /*当前通道用于传输OSA的消息数据*/
    OM_ICC_CHANNEL_BUTT
};
typedef VOS_UINT32 OM_ICC_CHANNEL_ENUM_UINT32;

/*用于ICC通道UDI控制数据片结构*/
typedef struct
{
    VOS_UINT32                      enICCId;        /*底软定义的当前通道号*/
    ICC_CHAN_ATTR_S                *pstICCAttr;     /*当前通道属性*/
}OM_ICC_UDI_CTRL_STRU;

typedef struct
{
   VOS_UINT16                       usSendPid;
   VOS_UINT16                       usRcvPid;
   VOS_UINT32                       ulMsgName;
   VOS_UINT32                       ulSliceStart;
   VOS_UINT32                       ulSliceEnd;
}OM_RECORD_INFO_STRU;

typedef struct
{
   VOS_UINT8                       *pucBuf;
   VOS_UINT32                       ulLen;
   VOS_UINT8                        aucRsv[4];
}OM_RECORD_BUF_STRU;

typedef struct
{
    VOS_MSG_HEADER
}OM_FILTER_MSG_HEAD_STRU;

/*****************************************************************************
  4 STRUCT定义
*****************************************************************************/


/*****************************************************************************
  5 接口定义
*****************************************************************************/
extern VOS_UINT V_ICC_OSAMsg_CB(VOS_UINT ulChannelID,VOS_INT lLen);

extern VOS_UINT32 VOS_GetMsgName(VOS_UINT32 ulAddrress);

extern VOS_VOID Om_AcpuQueryDumpMsgProc(MsgBlock* pMsg);

extern VOS_VOID  Om_AcpuPhyMsgProc( MsgBlock* pMsg );

/* AT<->AT的屏蔽处理，移到GuNasLogFilter.c */

#if (VOS_WIN32 == VOS_OS_VER)
#define PS_LOG(ModulePID, SubMod, Level, String)\
        vos_printf("\r\n%s",   String)

#define PS_LOG1(ModulePID, SubMod, Level, String, Para1)\
        vos_printf("\r\n%s,para1=%d", String, Para1)

#define PS_LOG2(ModulePID, SubMod, Level, String, Para1, Para2)\
        vos_printf("\r\n%s,para1=%d,para2=%d", String, Para1, Para2)

#define PS_LOG3(ModulePID, SubMod, Level, String, Para1, Para2, Para3)\
        vos_printf("\r\n%s,para1=%d,para2=%d,para3=%d", String, Para1, Para3)

#define PS_LOG4(ModulePID, SubMod, Level, String, Para1, Para2, Para3, Para4)\
        vos_printf("\r\n%s,para1=%d,para2=%d,para3=%d,para4=%d", String, Para1, Para3, Para4)

#else
#define PS_LOG(ModulePID, SubMod, Level, String)

#define PS_LOG1(ModulePID, SubMod, Level, String, Para1)

#define PS_LOG2(ModulePID, SubMod, Level, String, Para1, Para2)

#define PS_LOG3(ModulePID, SubMod, Level, String, Para1, Para2, Para3)

#define PS_LOG4(ModulePID, SubMod, Level, String, Para1, Para2, Para3, Para4)

#endif

#ifdef __cplusplus
#if __cplusplus
}
#endif
#endif /* __cplusplus */


#endif /* __PAMAPPOM_H__ */
