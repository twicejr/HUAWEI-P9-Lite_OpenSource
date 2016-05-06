/******************************************************************************

                  版权所有 (C), 2001-2011, 华为技术有限公司

 ******************************************************************************
  文 件 名   : CdsDepend.h
  版 本 号   : 初稿
  作    者   : y00151394
  生成日期   : 2011年12月12日
  最近修改   :
  功能描述   : 定义CDS依赖的外部条件
  函数列表   :
  修改历史   :
  1.日    期   : 2012年1月8日
    作    者   : y00151394
    修改内容   : 创建文件

******************************************************************************/

#ifndef __CDS_DEPEND_H__
#define __CDS_DEPEND_H__

#ifdef __cplusplus
#if __cplusplus
extern "C" {
#endif
#endif

#include "vos.h"
#include "PsCommonDef.h"
#include "PsLogdef.h"
#include "PsTypeDef.h"
#include "TTFMem.h"
#include "TTFMemInterface.h"
#include "TTFComm.h"
#include "LUPQueue.h"
#include "ApsCdsInterface.h"
#include "ApsCdsInterface.h"
#include "CdsAdsInterface.h"
#include "CdsMmcInterface.h"
#include "CdsNdInterface.h"
#include "CdsRabmInterface.h"
#include "CdsRabmInterface.h"
#include "QosFcCommon.h"
#include "QosFcOm.h"
#include "CdsInterface.h"
#include "TlPsDrv.h"
#include "product_config.h"
#include "ImsaCdsInterface.h"
#include "CdsDhcpInterface.h"

#if (FEATURE_ON == FEATURE_BASTET)
#include "BastetCdsInterface.h"
#endif

#if (FEATURE_ON ==FEATURE_LTE)
#include "LPsOm.h"
#include "OmCommon.h"
#include "CdsLPdcpInterface.h"
#include "CdsErabmInterface.h"
#include "CdsEtcInterface.h"
#endif

#if (FEATURE_ON == FEATURE_UE_MODE_CDMA)
#include "cds_trans_data_pif.h"
#include "CdsPppInterface.h"
#endif

#if (VOS_OS_VER != VOS_WIN32)
#pragma pack(4)
#else
#pragma pack(push, 4)
#endif


extern VOS_VOID TL_OM_CdsUlRecIpPktInfo(TTF_MEM_ST *pstIpPkt);
extern VOS_VOID TL_OM_CdsDlRecIpPktInfo(TTF_MEM_ST *pstIpPkt);
extern VOS_VOID TL_OM_CdsUlIpPktHook(TTF_MEM_ST *pstIpPkt);
extern VOS_VOID TL_OM_CdsDlIpPktHook(TTF_MEM_ST *pstIpPkt);
extern VOS_VOID TL_OM_CdsDlLteDbgPktHook(TTF_MEM_ST *pstIpPkt);
extern VOS_VOID TL_OM_CdsImsUlPktHook(TTF_MEM_ST *pstIpPkt);
extern VOS_VOID TL_OM_CdsImsDlPktHook(TTF_MEM_ST *pstIpPkt);
extern VOS_VOID TL_OM_CdsBastetUlPktHook(TTF_MEM_ST *pstIpPkt);
extern VOS_VOID TL_OM_CdsBastetDlPktHook(TTF_MEM_ST *pstIpPkt);
extern VOS_VOID TL_OM_UlIpPktHook(TTF_MEM_ST *pstIpPkt);

/*****************************************************************************
  1 其他头文件包含
*****************************************************************************/
#define CDS_FEATURE_ON                  (1)
#define CDS_FEATURE_OFF                 (0)

#if (FEATURE_ON == FEATURE_LTE)
#define CDS_FEATURE_LTE                 CDS_FEATURE_ON
#else
#define CDS_FEATURE_LTE                 CDS_FEATURE_OFF
#endif

#if (FEATURE_ON == FEATURE_UE_MODE_CDMA)
#define CDS_FEATURE_CDMA                 CDS_FEATURE_ON
#else
#define CDS_FEATURE_CDMA                 CDS_FEATURE_OFF
#endif

#if (FEATURE_OFF  == FEATURE_MULTI_MODEM)
#define CDS_FEATURE_MULTI_MODEM         CDS_FEATURE_OFF
#define CDS_MAX_MODEM_NUM               (1)
#define CDS_FEATURE_MODEM_2             CDS_FEATURE_OFF
#else
#define CDS_FEATURE_MULTI_MODEM         CDS_FEATURE_ON
#if (3 == MULTI_MODEM_NUMBER)
#define CDS_MAX_MODEM_NUM               (3)
#define CDS_FEATURE_MODEM_2             CDS_FEATURE_ON
#else
#define CDS_MAX_MODEM_NUM               (2)
#define CDS_FEATURE_MODEM_2             CDS_FEATURE_OFF
#endif
#endif

#if (FEATURE_OFF == FEATURE_IMS)
#define CDS_FEATURE_IMS                 CDS_FEATURE_OFF
#else
#define CDS_FEATURE_IMS                 CDS_FEATURE_ON
#endif

#if (FEATURE_OFF == FEATURE_BASTET )
#define CDS_FEATURE_BASTET              CDS_FEATURE_OFF
#else
#define CDS_FEATURE_BASTET              CDS_FEATURE_ON
#endif
/*****************************************************************************
  2 宏定义
*****************************************************************************/


#ifdef _lint
#define WUEPS_PID_MMC       210
#define ACPU_PID_ADS_UL     211
#define ACPU_PID_ADS_DL     212
#define WUEPS_PID_RABM      213
#define PS_PID_RABM         214
#define UEPS_PID_NDCLIENT   216
#define PS_PID_TC           217
#define PS_PID_IMSA         222
#define WUEPS_PID_PDCP      250

#define I0_WUEPS_PID_MMC    310
#define I0_WUEPS_PID_RABM   314
#define I1_WUEPS_PID_MMC    318
#define I1_WUEPS_PID_RABM   319

#define I0_WUEPS_PID_TAF    220
#define I1_WUEPS_PID_TAF    221

#endif



#if (CDS_FEATURE_ON == CDS_FEATURE_LTE)

/*定义消息上报接口*/
extern  VOS_UINT32 LTE_MsgHook( VOS_VOID *pMsg );
#define CDS_MSG_HOOK(pstMsgBlk)    (VOS_VOID)LTE_MsgHook(pstMsgBlk)

#if (VOS_WIN32 == VOS_OS_VER)

/*LOG PRINT定义*/
#define CDS_INFO_LOG(ModuleId, String)                                 LPS_LOG(  ModuleId, 0,LOG_LEVEL_INFO, String )
#define CDS_INFO_LOG1(ModuleId, String,Para1)                          LPS_LOG1( ModuleId, 0,LOG_LEVEL_INFO, String, (VOS_INT32)Para1)
#define CDS_INFO_LOG2(ModuleId, String,Para1,Para2)                    LPS_LOG2( ModuleId, 0,LOG_LEVEL_INFO, String, (VOS_INT32)Para1, (VOS_INT32)Para2 )
#define CDS_INFO_LOG3(ModuleId, String,Para1,Para2,Para3)              LPS_LOG3( ModuleId, 0,LOG_LEVEL_INFO, String, (VOS_INT32)Para1, (VOS_INT32)Para2, (VOS_INT32)Para3 )
#define CDS_INFO_LOG4(ModuleId, String,Para1,Para2,Para3,Para4)        LPS_LOG4( ModuleId, 0,LOG_LEVEL_INFO, String, (VOS_INT32)Para1, (VOS_INT32)Para2, (VOS_INT32)Para3,(VOS_INT32)Para4 )

#define CDS_WARNING_LOG(ModuleId, String)                              LPS_LOG(  ModuleId, 0,LOG_LEVEL_WARNING, String )
#define CDS_WARNING_LOG1(ModuleId, String,Para1)                       LPS_LOG1( ModuleId, 0,LOG_LEVEL_WARNING, String, Para1)
#define CDS_WARNING_LOG2(ModuleId, String,Para1,Para2)                 LPS_LOG2( ModuleId, 0,LOG_LEVEL_WARNING, String, Para1, Para2 )
#define CDS_WARNING_LOG3(ModuleId, String,Para1,Para2,Para3)           LPS_LOG3( ModuleId, 0,LOG_LEVEL_WARNING, String, Para1, Para2, Para3 )
#define CDS_WARNING_LOG4(ModuleId, String,Para1,Para2,Para3,Para4)     LPS_LOG4( ModuleId, 0,LOG_LEVEL_WARNING, String, Para1, Para2, Para3, Para4 )

#define CDS_ERROR_LOG(ModuleId, String)                                LPS_LOG(  ModuleId, 0,LOG_LEVEL_ERROR, String )
#define CDS_ERROR_LOG1(ModuleId, String,Para1)                         LPS_LOG1( ModuleId, 0,LOG_LEVEL_ERROR, String, Para1)
#define CDS_ERROR_LOG2(ModuleId, String,Para1,Para2)                   LPS_LOG2( ModuleId, 0,LOG_LEVEL_ERROR, String, Para1, Para2 )
#define CDS_ERROR_LOG3(ModuleId, String,Para1,Para2,Para3)             LPS_LOG3( ModuleId, 0,LOG_LEVEL_ERROR, String, Para1, Para2, Para3 )
#define CDS_ERROR_LOG4(ModuleId, String,Para1,Para2,Para3,Para4)       LPS_LOG4( ModuleId, 0,LOG_LEVEL_ERROR, String, Para1, Para2, Para3, Para4 )

/*新打印接口*/
#define CDS_PRINT_INFO(enFunction, enProcFlag)
#define CDS_PRINT_INFO1(enFunction, enProcFlag, ulPara1)
#define CDS_PRINT_INFO2(enFunction, enProcFlag, ulPara1, ulPara2)

#define CDS_PRINT_WARNING(enFunction, enProcFlag)
#define CDS_PRINT_WARNING1(enFunction, enProcFlag, ulPara1)
#define CDS_PRINT_WARNING2(enFunction, enProcFlag, ulPara1, ulPara2)

#define CDS_PRINT_ERROR(enFunction, enProcFlag)
#define CDS_PRINT_ERROR1(enFunction, enProcFlag, ulPara1)
#define CDS_PRINT_ERROR2(enFunction, enProcFlag, ulPara1, ulPara2)

#else

#ifdef _lint
#define CDS_INFO_LOG(ModuleId, String)                                 LPS_LOG(  ModuleId, 0,LOG_LEVEL_INFO, String )
#define CDS_INFO_LOG1(ModuleId, String,Para1)                          LPS_LOG1( ModuleId, 0,LOG_LEVEL_INFO, String, (VOS_INT32)Para1)
#define CDS_INFO_LOG2(ModuleId, String,Para1,Para2)                    LPS_LOG2( ModuleId, 0,LOG_LEVEL_INFO, String, (VOS_INT32)Para1, (VOS_INT32)Para2 )
#define CDS_INFO_LOG3(ModuleId, String,Para1,Para2,Para3)              LPS_LOG3( ModuleId, 0,LOG_LEVEL_INFO, String, (VOS_INT32)Para1, (VOS_INT32)Para2, (VOS_INT32)Para3 )
#define CDS_INFO_LOG4(ModuleId, String,Para1,Para2,Para3,Para4)        LPS_LOG4( ModuleId, 0,LOG_LEVEL_INFO, String, (VOS_INT32)Para1, (VOS_INT32)Para2, (VOS_INT32)Para3,(VOS_INT32)Para4 )

#define CDS_WARNING_LOG(ModuleId, String)                              LPS_LOG(  ModuleId, 0,LOG_LEVEL_WARNING, String )
#define CDS_WARNING_LOG1(ModuleId, String,Para1)                       LPS_LOG1( ModuleId, 0,LOG_LEVEL_WARNING, String, Para1)
#define CDS_WARNING_LOG2(ModuleId, String,Para1,Para2)                 LPS_LOG2( ModuleId, 0,LOG_LEVEL_WARNING, String, Para1, Para2 )
#define CDS_WARNING_LOG3(ModuleId, String,Para1,Para2,Para3)           LPS_LOG3( ModuleId, 0,LOG_LEVEL_WARNING, String, Para1, Para2, Para3 )
#define CDS_WARNING_LOG4(ModuleId, String,Para1,Para2,Para3,Para4)     LPS_LOG4( ModuleId, 0,LOG_LEVEL_WARNING, String, Para1, Para2, Para3, Para4 )

#define CDS_ERROR_LOG(ModuleId, String)                                LPS_LOG(  ModuleId, 0,LOG_LEVEL_ERROR, String )
#define CDS_ERROR_LOG1(ModuleId, String,Para1)                         LPS_LOG1( ModuleId, 0,LOG_LEVEL_ERROR, String, Para1)
#define CDS_ERROR_LOG2(ModuleId, String,Para1,Para2)                   LPS_LOG2( ModuleId, 0,LOG_LEVEL_ERROR, String, Para1, Para2 )
#define CDS_ERROR_LOG3(ModuleId, String,Para1,Para2,Para3)             LPS_LOG3( ModuleId, 0,LOG_LEVEL_ERROR, String, Para1, Para2, Para3 )
#define CDS_ERROR_LOG4(ModuleId, String,Para1,Para2,Para3,Para4)       LPS_LOG4( ModuleId, 0,LOG_LEVEL_ERROR, String, Para1, Para2, Para3, Para4 )

/*新打印接口*/
#define CDS_PRINT_INFO(enFunction, enProcFlag)
#define CDS_PRINT_INFO1(enFunction, enProcFlag, ulPara1)
#define CDS_PRINT_INFO2(enFunction, enProcFlag, ulPara1, ulPara2)

#define CDS_PRINT_WARNING(enFunction, enProcFlag)
#define CDS_PRINT_WARNING1(enFunction, enProcFlag, ulPara1)
#define CDS_PRINT_WARNING2(enFunction, enProcFlag, ulPara1, ulPara2)

#define CDS_PRINT_ERROR(enFunction, enProcFlag)
#define CDS_PRINT_ERROR1(enFunction, enProcFlag, ulPara1)
#define CDS_PRINT_ERROR2(enFunction, enProcFlag, ulPara1, ulPara2)

#else

#define CDS_INFO_LOG(ModuleId, String)
#define CDS_INFO_LOG1(ModuleId, String,Para1)
#define CDS_INFO_LOG2(ModuleId, String,Para1,Para2)
#define CDS_INFO_LOG3(ModuleId, String,Para1,Para2,Para3)
#define CDS_INFO_LOG4(ModuleId, String,Para1,Para2,Para3,Para4)

#define CDS_WARNING_LOG(ModuleId, String)
#define CDS_WARNING_LOG1(ModuleId, String,Para1)
#define CDS_WARNING_LOG2(ModuleId, String,Para1,Para2)
#define CDS_WARNING_LOG3(ModuleId, String,Para1,Para2,Para3)
#define CDS_WARNING_LOG4(ModuleId, String,Para1,Para2,Para3,Para4)

#define CDS_ERROR_LOG(ModuleId, String)
#define CDS_ERROR_LOG1(ModuleId, String,Para1)
#define CDS_ERROR_LOG2(ModuleId, String,Para1,Para2)
#define CDS_ERROR_LOG3(ModuleId, String,Para1,Para2,Para3)
#define CDS_ERROR_LOG4(ModuleId, String,Para1,Para2,Para3,Para4)

/*新打印接口*/
#define CDS_PRINT_INFO(enFunction, enProcFlag)                          TLPS_PRINT2LAYER_INFO(enFunction, enProcFlag)
#define CDS_PRINT_INFO1(enFunction, enProcFlag, ulPara1)                TLPS_PRINT2LAYER_INFO1(enFunction, enProcFlag, ulPara1)
#define CDS_PRINT_INFO2(enFunction, enProcFlag, ulPara1, ulPara2)       TLPS_PRINT2LAYER_INFO2(enFunction, enProcFlag, ulPara1, ulPara2)


#define CDS_PRINT_WARNING(enFunction, enProcFlag)                       TLPS_PRINT2LAYER_WARNING(enFunction, enProcFlag)
#define CDS_PRINT_WARNING1(enFunction, enProcFlag, ulPara1)             TLPS_PRINT2LAYER_WARNING1(enFunction, enProcFlag, ulPara1)
#define CDS_PRINT_WARNING2(enFunction, enProcFlag, ulPara1, ulPara2)    TLPS_PRINT2LAYER_WARNING2(enFunction, enProcFlag, ulPara1, ulPara2)

#define CDS_PRINT_ERROR(enFunction, enProcFlag)                         TLPS_PRINT2LAYER_ERROR(enFunction, enProcFlag)
#define CDS_PRINT_ERROR1(enFunction, enProcFlag, ulPara1)               TLPS_PRINT2LAYER_ERROR1(enFunction, enProcFlag, ulPara1)
#define CDS_PRINT_ERROR2(enFunction, enProcFlag, ulPara1, ulPara2)      TLPS_PRINT2LAYER_ERROR2(enFunction, enProcFlag, ulPara1, ulPara2)

#endif
#endif
/*用户面事件上报*/
#define CDS_UP_EVENT_UL_IPF_ERR                                         (TL_UP_EVENT_CDS_UL_IPF_ERR)
#define CDS_UP_EVENT_UL_SOFT_IPF_ERR                                    (TL_UP_EVENT_CDS_UL_SOFT_IPF_ERR)
#define CDS_UP_EVENT_UL_FLOW_CTRL_DISCARD                               (TL_UP_EVENT_CDS_UL_FLOW_CTRL)
#define CDS_UP_EVENT_DL_FLOW_CTRL_DISCARD                               (TL_UP_EVENT_CDS_DL_FLOW_CTRL)
#define CDS_UP_EVENT_DL_SDU_QUE_FULL                                    (TL_UP_EVENT_CDS_DL_SDU_QUE_FULL)

/*z00282933，多模OM融合添加 - BEGIN*/
#define CDS_UP_EVENT_RPT(Event)                                         TL_OM_ReportSingleUpEvent(Event, UEPS_PID_CDS, 0xFFFFUL, 0xFFFFUL, 0xFFFFUL, DIAG_MODE_COMM)
/*z00282933, 多模OM融合添加 - END*/

/*Added for LTE PDU Report*/
#define  CDS_DBG_UL_REC_IP_PKT_INFO(pstIpPkt)                           TL_OM_CdsUlRecIpPktInfo(pstIpPkt)
#define  CDS_DBG_DL_REC_IP_PKT_INFO(pstIpPkt)                           TL_OM_CdsDlRecIpPktInfo(pstIpPkt)
#define  CDS_DBG_UL_LTE_IP_PKT_HOOK(pstIpPkt)                           TL_OM_CdsUlIpPktHook(pstIpPkt)
#define  CDS_DBG_DL_LTE_IP_PKT_HOOK(pstIpPkt)                           TL_OM_CdsDlIpPktHook(pstIpPkt)
#define  CDS_DBG_DL_LTE_DBG_PKT_HOOK(pstIpPkt)                          TL_OM_CdsDlLteDbgPktHook(pstIpPkt)

#define  CDS_DBG_IMS_UL_IP_PKT_HOOK(pstIpPkt)                           TL_OM_CdsImsUlPktHook(pstIpPkt)
#define  CDS_DBG_IMS_DL_IP_PKT_HOOK(pstIpPkt)                           TL_OM_CdsImsDlPktHook(pstIpPkt)
#define  CDS_DBG_BASTET_UL_IP_PKT_HOOK(pstIpPkt)                        TL_OM_CdsBastetUlPktHook(pstIpPkt)
#define  CDS_DBG_BASTET_DL_IP_PKT_HOOK(pstIpPkt)                        TL_OM_CdsBastetDlPktHook(pstIpPkt)
#define  CDS_DBB_NDCLIENT_DATA_REQ_HOOK(pstIpPkt)                       TL_OM_UlIpPktHook(pstIpPkt)
#define  CDS_DBG_DHCP_DATA_REQ_HOOK(pstIpPkt)                           TL_OM_UlIpPktHook(pstIpPkt)

#else

/*定义消息上报接口*/
extern VOS_UINT32   OM_TraceMsgHook(VOS_VOID *pMsg);
#define CDS_MSG_HOOK(pstMsgBlk)         (VOS_VOID)OM_TraceMsgHook(pstMsgBlk)


/*LOG PRINT定义*/
#define CDS_INFO_LOG(ModuleId, String)
#define CDS_INFO_LOG1(ModuleId, String,Para1)
#define CDS_INFO_LOG2(ModuleId, String,Para1,Para2)
#define CDS_INFO_LOG3(ModuleId, String,Para1,Para2,Para3)
#define CDS_INFO_LOG4(ModuleId, String,Para1,Para2,Para3,Para4)

#define CDS_WARNING_LOG(ModuleId, String)
#define CDS_WARNING_LOG1(ModuleId, String,Para1)
#define CDS_WARNING_LOG2(ModuleId, String,Para1,Para2)
#define CDS_WARNING_LOG3(ModuleId, String,Para1,Para2,Para3)
#define CDS_WARNING_LOG4(ModuleId, String,Para1,Para2,Para3,Para4)

#define CDS_ERROR_LOG(ModuleId, String)                              PS_PRINTF(" %s, %d, %s\r\n ", __FILE__, __LINE__,String)
#define CDS_ERROR_LOG1(ModuleId, String,Para1)                       PS_PRINTF (" %s, %d, %s, %d, \r\n ",  __FILE__, __LINE__, String, Para1)
#define CDS_ERROR_LOG2(ModuleId, String,Para1,Para2)                 PS_PRINTF (" %s, %d, %s, %d, %d \r\n ",  __FILE__, __LINE__, String, Para1, Para2)
#define CDS_ERROR_LOG3(ModuleId, String,Para1,Para2,Para3)           PS_PRINTF (" %s, %d, %s, %d, %d, %d\r\n ",  __FILE__, __LINE__, String, Para1, Para2, Para3)
#define CDS_ERROR_LOG4(ModuleId, String,Para1,Para2,Para3,Para4)     PS_PRINTF (" %s, %d, %s, %d, %d, %d, %d\r\n ",  __FILE__, __LINE__, String, Para1, Para2, Para3, Para4)

/*用户面事件上报*/
#define CDS_UP_EVENT_UL_IPF_ERR
#define CDS_UP_EVENT_UL_SOFT_IPF_ERR
#define CDS_UP_EVENT_UL_FLOW_CTRL_DISCARD
#define CDS_UP_EVENT_DL_FLOW_CTRL_DISCARD
#define CDS_UP_EVENT_DL_SDU_QUE_FULL

#define CDS_UP_EVENT_RPT(Event)

#define  CDS_DBG_UL_REC_IP_PKT_INFO(pstIpPkt)
#define  CDS_DBG_DL_REC_IP_PKT_INFO(pstIpPkt)
#define  CDS_DBG_UL_LTE_IP_PKT_HOOK(pstIpPkt)
#define  CDS_DBG_DL_LTE_IP_PKT_HOOK(pstIpPkt)
#define  CDS_DBG_DL_LTE_DBG_PKT_HOOK(pstIpPkt)

#define  CDS_DBG_IMS_UL_IP_PKT_HOOK(pstIpPkt)
#define  CDS_DBG_IMS_DL_IP_PKT_HOOK(pstIpPkt)
#define  CDS_DBG_BASTET_UL_IP_PKT_HOOK(pstIpPkt)
#define  CDS_DBG_BASTET_DL_IP_PKT_HOOK(pstIpPkt)
#define  CDS_DBB_NDCLIENT_DATA_REQ_HOOK(pstIpPkt)
#define  CDS_DBG_DHCP_DATA_REQ_HOOK(pstIpPkt)

#endif



/*CDS DEBUG*/
#ifdef CDS_DEBUG
#define CDS_ASSERT(exp) \
              if (!(exp))\
              {\
                  PS_PRINTF("%s,%d " #exp "\r\n", __FILE__,__LINE__);\
                  return;\
              }

#define CDS_ASSERT_RTN(exp,ret)\
              if (!(exp))\
              {\
                  PS_PRINTF("%s,%d " #exp "\r\n",,__FILE__,__LINE__);\
                  return ret;\
              }

#else
#define CDS_ASSERT(exp)
#define CDS_ASSERT_RTN(exp,ret)
#endif


/*****************************************************************************
  3 Massage Declare
*****************************************************************************/

/*****************************************************************************
  4 枚举定义
*****************************************************************************/

/*****************************************************************************
   5 STRUCT定义
*****************************************************************************/


/*****************************************************************************
  6 UNION定义
*****************************************************************************/


/*****************************************************************************
  7 全局变量声明
*****************************************************************************/


/*****************************************************************************
  8 函数声明
*****************************************************************************/


/*****************************************************************************
  9 OTHERS定义
*****************************************************************************/


#if (VOS_OS_VER != VOS_WIN32)
#pragma pack()
#else
#pragma pack(pop)
#endif




#ifdef __cplusplus
    #if __cplusplus
        }
    #endif
#endif

#endif

