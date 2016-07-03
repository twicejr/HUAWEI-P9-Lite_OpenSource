
#ifndef _UTTEST_NAS_RNIC_ENTITY_H_
#define _UTTEST_NAS_RNIC_ENTITY_H_

/*****************************************************************************
  1 其他头文件包含
*****************************************************************************/
#include "AdsCtx.h"
#include "RnicProcMsg.h"
#include "RnicDebug.h"
#include "RnicEntity.h"
#include "RnicCtx.h"
#include "SdioInterface.h"


#ifdef __cplusplus
#if __cplusplus
extern "C" {
#endif
#endif

#pragma pack(4)

/*****************************************************************************
  2 宏定义
*****************************************************************************/
#define    THIS_FILE_ID                 PS_FILE_ID_RNIC_ENTITY_C

/*****************************************************************************
3 枚举定义
*****************************************************************************/



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
extern void UT_STUB_INIT(void);


extern RNIC_STATS_INFO_STRU                     g_astRnicStats[RNIC_NET_ID_MAX_NUM];
extern const RNIC_NETCARD_ELEMENT_TAB_STRU      g_astRnicManageTbl[RNIC_NET_ID_MAX_NUM];

extern netdev_tx_t RNIC_RcvInsideModemUlData(
struct sk_buff                     *pstSkb,
struct net_device                  *pstNetDev,
    RNIC_NETCARD_DEV_INFO_STRU         *pstPriv,
    VOS_UINT8                           ucNetIndex
    );

#if (FEATURE_ON == FEATURE_CL_INTERWORK)
extern netdev_tx_t RNIC_RcvOutsideModemUlData(
struct sk_buff                     *pstSkb,
struct net_device                  *pstNetDev,
    RNIC_NETCARD_DEV_INFO_STRU         *pstPriv,
    VOS_UINT8                           ucNetIndex
    );
#endif

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


#endif /* end of uttest_nas_RnicEntity.h */


