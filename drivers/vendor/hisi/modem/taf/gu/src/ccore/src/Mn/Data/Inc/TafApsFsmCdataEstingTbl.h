/******************************************************************************

                  版权所有 (C), 2001-2011, 华为技术有限公司

 ******************************************************************************
  文 件 名   : TafApsFsmCdataEstingTbl.h
  版 本 号   : 初稿
  作    者   : y00218312
  生成日期   : 2014年10月16日
  最近修改   :
  功能描述   : TafApsFsmCdataEstingTbl.c 的头文件
  函数列表   :
  修改历史   :
  1.日    期   : 2014年10月16日
    作    者   : y00218312
    修改内容   : 创建文件

******************************************************************************/

#ifndef __TAFAPSFSMCDATAESTINGTBL_H__
#define __TAFAPSFSMCDATAESTINGTBL_H__

/*****************************************************************************
  1 其他头文件包含
*****************************************************************************/
#include  "vos.h"
#include  "TafFsm.h"


#ifdef __cplusplus
#if __cplusplus
extern "C" {
#endif
#endif


#pragma pack(4)

/*****************************************************************************
  2 宏定义
*****************************************************************************/
#if (FEATURE_ON == FEATURE_UE_MODE_CDMA)
extern TAF_STA_STRU                             g_astTafApsCdataEstingStaTbl[];
#define TAF_APS_GetCdataEstingStaTbl()          (g_astTafApsCdataEstingStaTbl)

#endif


/*****************************************************************************
  3 枚举定义
*****************************************************************************/
/*****************************************************************************
 枚举名    : TAF_APS_CDATA_ESTING_SUBSTA_ENUM
 枚举说明  : CDATA ESTING主状态下子状态枚举定义
 1.日    期   : 2014年10月15日
   作    者   : y00213812
   修改内容   : 新建

*****************************************************************************/
enum TAF_APS_CDATA_ESTING_SUBSTA_ENUM
{
    TAF_APS_CDATA_ESTING_SUBSTA_INIT                          = 0x00,    /* CDATA ESTING状态机的初始状态 */
    TAF_APS_CDATA_ESTING_SUBSTA_WAIT_XCC_ORIG_CALL_CNF        = 0x01,    /* CDMA模式下主叫时建立数据服务链接——等待XCC回复拨号请求子状态 */
    TAF_APS_CDATA_ESTING_SUBSTA_WAIT_XCC_SO_CONNECTED         = 0x02,    /* CDMA模式下主叫时建立数据服务链接——等待XCC上报SO子状态 */
    TAF_APS_CDATA_ESTING_SUBSTA_WAIT_XCC_ANS_CALL_CNF         = 0x03,    /* CDMA模式下被叫时建立数据服务链接——等待XCC回复应答子状态 */
    TAF_APS_CDATA_ESTING_SUBSTA_WAIT_XCC_CALL_CONNECTED_IND   = 0x04,    /* CDMA模式下被叫时建立数据服务链接——等待XCC上报CONNECTED子状态 */
    TAF_APS_CDATA_ESTING_SUBSTA_WAIT_INTERVAL_REDIAL          = 0x05,    /* CDMA模式下数据时服务链接建立——等待重拨子状态 */
    TAF_APS_CDATA_ESTING_SUBSTA_WAIT_HSM_ORIG_CALL_CNF        = 0x06,    /* CDMA模式下主叫时建立数据服务链接——等待HSM回复拨号请求子状态 */
    TAF_APS_CDATA_ESTING_SUBSTA_WAIT_EHSM_PDN_ACTIVATE_CNF    = 0x07,    /* CDMA模式下主叫时建立数据服务链接——等待EHSM回复拨号请求子状态 */
    TAF_APS_CDATA_ESTING_SUBSTA_SUSPEND                       = 0x08,    /* CDMA ESTING状态机的挂起状态 */

    TAF_APS_CDATA_ESTING_SUBSTA_WAIT_PPP_ACT_CNF              = 0x09,    /* CDMA模式下数据服务链接建立——等待PPP协商子状态 */

    TAF_APS_CDATA_ESTING_SUBSTA_WAIT_EHSM_PDN_ATTACH_CNF      = 0x0A,    /* CDMA模式下主叫时建立数据服务链接——等待EHSM回复Attach请求子状态 */

    TAF_APS_CDATA_ESTING_SUBSTA_BUTT                          = 0xFF
} ;
typedef VOS_UINT32 TAF_APS_CDATA_ESTING_SUBSTA_ENUM_UINT32;



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

#if (FEATURE_ON == FEATURE_UE_MODE_CDMA)

VOS_UINT32 TAF_APS_GetCdataEstingStaTblSize( VOS_VOID );
TAF_FSM_DESC_STRU * TAF_APS_GetCdataEstingFsmDescAddr( VOS_VOID );

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

#endif /* end of TafApsFsmCdataEstingTbl.h */
