/******************************************************************************

                  版权所有 (C), 2001-2011, 华为技术有限公司

 ******************************************************************************
  文 件 名   : CdsMsgProc.h
  版 本 号   : 初稿
  作    者   : y00151394
  生成日期   : 2011年12月15日
  最近修改   :
  功能描述   : CDS接收、发送消息处理
  函数列表   :
  修改历史   :
  1.日    期   : 2011年12月12日
    作    者   : y00151394
    修改内容   : 创建文件

******************************************************************************/

#ifndef __CDS_MSGPROC_H__
#define __CDS_MSGPROC_H__

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

#if (VOS_OS_VER != VOS_WIN32)
#pragma pack(4)
#else
#pragma pack(push, 4)
#endif

/*****************************************************************************
  2 宏定义
*****************************************************************************/
/*封装OSA消息头*/
#define CDS_CFG_MSG_HDR(pstMsg,ulRecvPid)\
                    (pstMsg)->ulSenderCpuId   = VOS_LOCAL_CPUID;\
                    (pstMsg)->ulSenderPid     = UEPS_PID_CDS;\
                    (pstMsg)->ulReceiverCpuId = VOS_LOCAL_CPUID;\
                    (pstMsg)->ulReceiverPid   = (ulRecvPid)

/*封装CDS发送OSA消息接口*/
#define CDS_SEND_MSG(pMsg) \
                if (VOS_OK != PS_SND_MSG_ALL_CHECK(UEPS_PID_CDS,(pMsg)))\
                {\
                    CDS_ERROR_LOG(UEPS_PID_CDS,"CDS_SEND_MSG : Send Msg Fail");\
                    return;\
                }

/*封装OSA消息申请接口*/
#define CDS_ALLOC_MSG_WITH_HDR(MsgLen)    (VOS_VOID *)PS_ALLOC_MSG_ALL_CHECK(UEPS_PID_CDS,(MsgLen))

/*定义CDS状态转换的函数指针*/
typedef  VOS_VOID (*CDS_STATE_UPDATE_FUN)(VOS_VOID);

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

extern VOS_VOID CDS_UlDataIndToAds(TTF_MEM_ST *pstIpPkt);
extern VOS_VOID CDS_RabmSerivceRequestNotify(VOS_UINT8 ucRabId, CDS_ENTITY_STRU *pstCdsEntity);
extern VOS_VOID CDS_RecvMsgProc(MsgBlock  *pstMsg);


/*LTE Only*/
#if (CDS_FEATURE_ON == CDS_FEATURE_LTE)
extern VOS_VOID CDS_ERabmSerivceRequestNotify(VOS_UINT8 ucEpsbId);
#endif

/*CDMA Only*/
#if (CDS_FEATURE_ON == CDS_FEATURE_CDMA)
extern VOS_VOID CDS_APSServiceRequestNotify(CDS_ENTITY_STRU *pstCdsEntity, VOS_UINT8 ucRabId);
#endif

extern VOS_VOID CDS_ProcRabmVoicePreferActIndMsg(const MsgBlock  *pstMsg);
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

