/******************************************************************************

                  版权所有 (C), 2001-2011, 华为技术有限公司

 ******************************************************************************
  文 件 名   : CommAppInterface.h
  版 本 号   : 初稿
  作    者   :     
  生成日期   : 2010年9月9日
  最近修改   :
  功能描述   : E5 三方共用的头文件
  函数列表   :
  修改历史   :
  1.日    期   : 2010年9月9日
    作    者   : 
    修改内容   : 创建文件

******************************************************************************/

#ifndef __COMM_INTERFACE_H__
#define __COMM_INTERFACE_H__

#ifdef __cplusplus
#if __cplusplus
extern "C" {
#endif
#endif


/*****************************************************************************
  1 其他头文件包含                            
*****************************************************************************/



#pragma pack(4)

/*****************************************************************************
  2 宏定义 
*****************************************************************************/

/*****************************************************************************
  3 STRUCT定义
*****************************************************************************/


/**********************************************************************
*
*device event indication
*
*********************************************************************/
#if 0
typedef enum 
{
    DEVICE_ID_NULL_ID =0, /*空id，用于初始化id*/ 
    DEVICE_ID_USB = 1,     /*USB设备id*/
    DEVICE_ID_KEY = 2,     /*KEY按键设备id*/
    DEVICE_ID_BATTERY = 3,/*电池事件上报使用此ID*/
    DEVICE_ID_CHARGER = 4, /*充电器事件上报使用此ID*/
    DEVICE_ID_SD_CARD = 5,
    DEVICE_ID_GPIO_INTER=6, /*非按键的gpio中断上报，使用此ID*/
    DEVICE_ID_SCREEN=7,
    DEVICE_ID_WLAN=8,
    DEVICE_ID_OM = 9, /* OM上报消息 */
    DEVICE_ID_TEMP=10,/*温度保护ID*/
    DEVICE_ID_MAX_ID   /*用做边界保护*/
}DEVICE_ID;
#endif
typedef struct device_event_st
{
    int device_id;   /*设备ID*/
    int value;         /*消息value*/ 
    char * desc;     /*描述*/
}device_event_t;

/*****************************************************************************
  4 函数声明
*****************************************************************************/
extern unsigned long OM_Printf(char * pcformat, ... );
extern unsigned long OM_PrintfWithModule(unsigned long ulModuleId,
                                   unsigned long ulLevel, char * pcformat, ... );
extern unsigned long OM_PrintfSetModuleIdLev(unsigned long ulModuleId, unsigned long ulLev);
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

#endif /* end of __COMM_INTERFACE_H__.h */
