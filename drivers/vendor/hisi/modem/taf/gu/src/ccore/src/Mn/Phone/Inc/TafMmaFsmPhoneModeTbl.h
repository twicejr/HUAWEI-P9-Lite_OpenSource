
#ifndef _TAF_MMA_FSM_PHONE_MODE_TBL_H_
#define _TAF_MMA_FSM_PHONE_MODE_TBL_H_

/*****************************************************************************
  1 其他头文件包含
*****************************************************************************/

#include  "vos.h"
#include  "PsTypeDef.h"
#include "TafFsm.h"



#ifdef __cplusplus
#if __cplusplus
extern "C" {
#endif
#endif


#pragma pack(4)

/*****************************************************************************
  1 全局变量定义
*****************************************************************************/

extern TAF_STA_STRU                            g_astTafMmaPhoneModeStaTbl[];


/*****************************************************************************
  2 宏定义
*****************************************************************************/
#define TAF_MMA_GetPhoneModeProcessStaTbl()                   (g_astTafMmaPhoneModeStaTbl)


/*****************************************************************************
  3 枚举定义
*****************************************************************************/


enum TAF_MMA_PHONE_MODE_STA_ENUM
{
    TAF_MMA_PHONE_MODE_STA_INIT,                                                /* 业务控制的初始化状态 */

    TAF_MMA_PHONE_MODE_STA_WAIT_EXTERNAL_MODULE_INIT,                           /* 等待USIM模块和物理层的初始化指示的状态 */

    TAF_MMA_PHONE_MODE_STA_WAIT_MSCC_START_CNF,                                 /*  等待MSCC模块的开机回复状态 */


    TAF_MMA_PHONE_MODE_STA_WAIT_MSCC_POWER_OFF_CNF,                              /* 等待MSCC模块的关机回复状态 */

    TAF_MMA_PHONE_MODE_STA_GET_GEO_WAIT_MSCC_START_CNF,                         /* 等待MSCC模块获取国家的开机回复状态 */

    TAF_MMA_PHONE_MODE_STA_WAIT_MSCC_GET_GEO_CNF,                               /* 等待MSCC获取地理信息回复状态 */

    TAF_MMA_PHONE_MODE_STA_GET_GEO_CMP_WAIT_USIM_STATUS_IND,                    /* GET GEO完成之后，等待卡状态上报状态 */

    TAF_MMA_PHONE_MODE_STA_WAIT_MSCC_STOP_GET_GEO_CNF,                          /* 等待MSCC停止获取地理信息回复状态 */

    TAF_MMA_PHONE_MODE_STA_GET_GEO_WAIT_MSCC_POWER_OFF_CNF,                     /* 等待MSCC模块获取国家的关机回复状态 */

    TAF_MMA_PHONE_MODE_STA_STA_BUTT
};
typedef VOS_UINT32  TAF_MMA_PHONE_MODE_STA_ENUM_UINT32;

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
  8 UNION定义
*****************************************************************************/


/*****************************************************************************
  9 OTHERS定义
*****************************************************************************/



/*****************************************************************************
  10 函数声明
*****************************************************************************/
VOS_UINT32 TAF_MMA_GetPhoneModeStaTblSize(VOS_VOID);

TAF_FSM_DESC_STRU * TAF_MMA_GetPhoneModeFsmDescAddr(VOS_VOID);

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

#endif /* end of TafMmaFsmPhoneModeTbl.h */


