/******************************************************************************

                  版权所有 (C), 2001-2011, 华为技术有限公司

 ******************************************************************************
  文 件 名   : oam_cphy_interface.h
  版 本 号   : 初稿
  作    者   : 杜建忠
  生成日期   : 2015年9月29日
  最近修改   :
  功能描述   : 定义OAM与CSDR之间的交互信息，目前主要是低功耗相关。

  函数列表   :
  修改历史   :
  1.日    期   : 2015年09月29日
    作    者   : 杜建忠
    修改内容   : 创建文件

******************************************************************************/
/*****************************************************************************
  1 其他头文件包含
*****************************************************************************/
#include "vos.h"
#ifndef __OAM_CPHY_INTERFACE_H__
#define __OAM_CPHY_INTERFACE_H__

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
 枚举名    :CPHY_OAM_WAKE_TYPE_ENUM_UINT32
 协议表格  :
 ASN.1描述 :
 枚举说明  :唤醒类型定义
*****************************************************************************/
enum CPHY_OAM_WAKE_TYPE_ENUM
{
    CPHY_OAM_NORMAL_WAKE                    = 0,
    CPHY_OAM_FORCE_WAKE                     = 1,
    CPHY_OAM_WAKE_TYPE_BUTT
};
typedef VOS_UINT32 CPHY_OAM_WAKE_TYPE_ENUM_UINT32;

/*****************************************************************************
 枚举名    :CPHY_WRITE_MBX_STATE_ENUM_UINT32
 协议表格  :
 ASN.1描述 :
 枚举说明  :CPROC写邮箱是否完成
*****************************************************************************/
enum CPHY_MBX_WRITE_STATE_ENUM
{
    CPHY_WRITE_MBX_COMPLETED           = 0,
    CPHY_WRITE_MBX_UNCOMPLETED         = 1,
    CPHY_WRITE_MBX_BUTT
};
typedef VOS_UINT32 CPHY_MBX_WRITE_STATE_ENUM_UINT32;

/*****************************************************************************
 枚举名    :CPHY_READ_MBX_STATE_ENUM_UINT32
 协议表格  :
 ASN.1描述 :
 枚举说明  :CPROC读邮箱是否完成
*****************************************************************************/
enum CPHY_MBX_READ_STATE_ENUM
{
    CPHY_READ_MBX_COMPLETED           = 0,
    CPHY_READ_MBX_UNCOMPLETED         = 1,
    CPHY_READ_MBX_BUTT
};
typedef VOS_UINT32 CPHY_MBX_READ_STATE_ENUM_UINT32;
/*****************************************************************************
 枚举名        : CPHY_SLEEP_TYPE_ENUM
 枚举说明      : CPHY睡眠类型枚举
*****************************************************************************/
enum CPHY_SLEEP_TYPE_ENUM
{
    CPHY_SLEEP_TYPE_NONE           = 0,
    CPHY_SLEEP_TYPE_SHORT             ,
    CPHY_SLEEP_TYPE_DEEP              ,
    CPHY_SLEEP_TYPE_BUTT
};
typedef VOS_UINT32 CPHY_SLEEP_TYPE_ENUM_UINT32;


/*****************************************************************************
 枚举名        : CPHY_WAKEUP_MODE_ENUM
 枚举说明      : CPHY唤醒类型枚举
*****************************************************************************/
enum CPHY_WAKEUP_TYPE_ENUM
{
    CPHY_WAKEUP_MODE_1X                  = 0,
    CPHY_WAKEUP_MODE_HRPD                   ,
    CPHY_WAKEUP_MODE_BUTT
};
typedef VOS_UINT32 CPHY_WAKEUP_MODE_ENUM_UINT32;

/*****************************************************************************
 枚举名        : CPHY_SLEEP_MODE_ENUM
 枚举说明      : CPHY睡眠主从模信息枚举
*****************************************************************************/
enum CPHY_SLEEP_MODE_ENUM
{
    CPHY_SLEEP_MODE_MASTER                ,
    CPHY_SLEEP_MODE_SLAVE                 ,
    CPHY_SLEEP_MODE_BUTT
};
typedef VOS_UINT32 CPHY_SLEEP_MODE_ENUM_UINT32;

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
 结构名    : CPHY_OAM_SHARE_INFO_STRU
 协议表格  :
 结构说明  : SRAM中CSDR与OAM之间进行低功耗信息交互的结构体
*****************************************************************************/
typedef struct
{
    volatile CPHY_SLEEP_TYPE_ENUM_UINT32        enSleepType;
    volatile CPHY_SLEEP_MODE_ENUM_UINT32        en1xMode;
    volatile CPHY_SLEEP_MODE_ENUM_UINT32        enHrpdMode;
    volatile CPHY_WAKEUP_MODE_ENUM_UINT32       enWakeUpMode;
    volatile CPHY_OAM_WAKE_TYPE_ENUM_UINT32     en1xWakeUpType;
    volatile CPHY_OAM_WAKE_TYPE_ENUM_UINT32     enHrpdWakeUpType;
    volatile CPHY_MBX_WRITE_STATE_ENUM_UINT32   enCprocWriteMbxState;
    volatile CPHY_MBX_READ_STATE_ENUM_UINT32    enCprocReadMbxState;
    volatile VOS_UINT32                         uwReserved[8];
}CPHY_OAM_SHARE_INFO_STRU;


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


#endif /* __OAM_CPHY_INTERFACE_H__ */
