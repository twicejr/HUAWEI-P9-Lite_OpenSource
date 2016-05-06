

/*****************************************************************************
  1 头文件包含
*****************************************************************************/
#ifndef _ATAPPVCOMINTERFACE_H_
#define _ATAPPVCOMINTERFACE_H_


/*****************************************************************************
  1 其他头文件包含
*****************************************************************************/
#include "vos.h"
#include "product_config.h"


#ifdef __cplusplus
#if __cplusplus
extern "C" {
#endif
#endif

#pragma pack(4)

/*****************************************************************************
  2 宏定义
*****************************************************************************/
/*提供给OM 的设备索引*/
#if (FEATURE_ON == FEATURE_VCOM_EXT)
#define APP_VCOM_DEV_INDEX_CBT            (APP_VCOM_DEV_INDEX_27)
#define APP_VCOM_DEV_INDEX_TLLOG          (APP_VCOM_DEV_INDEX_28)
#define APP_VCOM_DEV_INDEX_ERRLOG         (APP_VCOM_DEV_INDEX_29)
#define APP_VCOM_DEV_INDEX_LOG            (APP_VCOM_DEV_INDEX_30)
#define APP_VCOM_DEV_INDEX_LOG1           (APP_VCOM_DEV_INDEX_31)
#else
#define APP_VCOM_DEV_INDEX_CBT            (APP_VCOM_DEV_INDEX_BUTT)
#define APP_VCOM_DEV_INDEX_TLLOG          (APP_VCOM_DEV_INDEX_BUTT)
#define APP_VCOM_DEV_INDEX_ERRLOG         (APP_VCOM_DEV_INDEX_BUTT)
#define APP_VCOM_DEV_INDEX_LOG            (APP_VCOM_DEV_INDEX_BUTT)
#define APP_VCOM_DEV_INDEX_LOG1           (APP_VCOM_DEV_INDEX_BUTT)
#endif
/*****************************************************************************
  3 枚举定义
*****************************************************************************/

/*****************************************************************************
 结构名    : APP_VCOM_DEV_INDEX
 结构说明  : APP VCOM 虚拟设备索引号

 1.日    期   : 2012年11月23日
   作    者   : z00220246
   修改内容   : DSDA Phase I:
*****************************************************************************/
enum APP_VCOM_DEV_INDEX
{
    APP_VCOM_DEV_INDEX_0                 = 0,
    APP_VCOM_DEV_INDEX_1                 = 1,
#if (FEATURE_ON == FEATURE_VCOM_EXT)
    APP_VCOM_DEV_INDEX_2                 = 2,
    APP_VCOM_DEV_INDEX_3                 = 3,
    APP_VCOM_DEV_INDEX_4                 = 4,
    APP_VCOM_DEV_INDEX_5                 = 5,
    APP_VCOM_DEV_INDEX_6                 = 6,
    APP_VCOM_DEV_INDEX_7                 = 7,
    APP_VCOM_DEV_INDEX_8                 = 8,
    APP_VCOM_DEV_INDEX_9                 = 9,
    APP_VCOM_DEV_INDEX_10                = 10,
    APP_VCOM_DEV_INDEX_11                = 11,
    APP_VCOM_DEV_INDEX_12                = 12,
    APP_VCOM_DEV_INDEX_13                = 13,
    APP_VCOM_DEV_INDEX_14                = 14,
    APP_VCOM_DEV_INDEX_15                = 15,
    APP_VCOM_DEV_INDEX_16                = 16,
    APP_VCOM_DEV_INDEX_17                = 17,
    APP_VCOM_DEV_INDEX_18                = 18,
    APP_VCOM_DEV_INDEX_19                = 19,
    APP_VCOM_DEV_INDEX_20                = 20,
    APP_VCOM_DEV_INDEX_21                = 21,
    APP_VCOM_DEV_INDEX_22                = 22,
    APP_VCOM_DEV_INDEX_23                = 23,
    APP_VCOM_DEV_INDEX_24                = 24,
    APP_VCOM_DEV_INDEX_25                = 25,
    APP_VCOM_DEV_INDEX_26                = 26,
    APP_VCOM_DEV_INDEX_27                = 27,
    APP_VCOM_DEV_INDEX_28                = 28,
    APP_VCOM_DEV_INDEX_29                = 29,
    APP_VCOM_DEV_INDEX_30                = 30,
    APP_VCOM_DEV_INDEX_31                = 31,
#endif
    APP_VCOM_DEV_INDEX_BUTT
};
typedef VOS_UINT8 APP_VCOM_DEV_INDEX_UINT8;

enum APP_VCOM_EVT
{
    APP_VCOM_EVT_RELEASE   = 0,     /* 端口关闭事件 */
    APP_VCOM_EVT_OPEN      = 1,     /* 端口打开事件 */
    APP_VCOM_EVT_BUTT
};
typedef VOS_UINT32 APP_VCOM_EVT_UINT32;
/*****************************************************************************
  2 全局变量定义
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
  8 UNION定义
*****************************************************************************/

/*****************************************************************************
  9 OTHERS定义
*****************************************************************************/

/*****************************************************************************
  10 函数声明
*****************************************************************************/


typedef int (*SEND_UL_AT_FUNC)(VOS_UINT8 ucDevIndex, VOS_UINT8 *pData, VOS_UINT32 uslength);
typedef int (*EVENT_FUNC)(APP_VCOM_EVT_UINT32 event);

/*****************************************************************************
 函 数 名  : APP_VCOM_RegDataCallback
 功能描述  : 提供上层应用程序注册数据接收回调函数指针的API接口函数。
 输入参数  : uPortNo：串口实例号。
             pCallback：回调函数指针。
 输出参数  : 无。
 返 回 值  : 0:  操作成功；
             -1：操作失败。
*****************************************************************************/
extern VOS_UINT32 APP_VCOM_RegDataCallback(VOS_UINT8 ucDevIndex, SEND_UL_AT_FUNC pFunc);
/*****************************************************************************
 函 数 名  : APP_VCOM_RegEvtCallback
 功能描述  : VCOM为外部模块提供的注册端口事件处理函数接口。
 输入参数  : uPortNo：串口实例号。
             pCallback：回调函数指针。
 输出参数  : 无。
 返 回 值  : 0:  操作成功；
             -1：操作失败。
*****************************************************************************/
extern VOS_UINT32 APP_VCOM_RegEvtCallback(VOS_UINT8 ucDevIndex, EVENT_FUNC pFunc);
/*****************************************************************************
 函 数 名  : APP_VCOM_Send
 功能描述  : 实现虚拟串口通道的数据发送功能，将上层软件传递的待发送数据
              直接传递至APP。
 输入参数  : uPortNo：虚拟串口实例号。
             pData：缓冲区指针。
             uslength：发送字节数。
 输出参数  : 无。
 返 回 值  : 0：操作成功；
             其它值：操作失败

*****************************************************************************/
extern VOS_UINT32 APP_VCOM_Send (VOS_UINT8 ucDevIndex, VOS_UINT8 *pData, VOS_UINT32 uslength);
#define APP_VCOM_SEND(ucDevIndex,pData,uslength) APP_VCOM_Send(ucDevIndex,pData,uslength)


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

