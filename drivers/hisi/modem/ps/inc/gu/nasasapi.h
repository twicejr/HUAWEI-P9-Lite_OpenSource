/*******************************************************************************
  Copyright   : 2005-2007, Huawei Tech. Co., Ltd.
  File name   : NasAsApi.h
  Description : Nas层对As提供的Api接口头文件
  History     :
      1.  张志勇     2003-8-21 : The first version
      2.  L47619  2005.12.13   问题单:    A32D01107
*******************************************************************************/
#ifndef _NAS_AS_API_H_
#define _NAS_AS_API_H_


#ifdef __cplusplus
#if __cplusplus
extern "C" {
#endif  /* __cpluscplus */
#endif  /* __cpluscplus */
#include "asnasapi.h"




/*========  PS业务使用 */
#define RABM_PS_DATA_IND        0
typedef struct
{
    MSG_HEADER_STRU     MsgHdr;                                                 /* 消息头                                    */
    VOS_UINT8                ucErr;                                                  /* 指示数据是否发生错误,                                                                                 * WUEPS_TRUE:错误;WUEPS_FALSE:没有发生错误 */
    VOS_UINT32               ulRbId;                                                 /* radio bear                               */
    VOS_UINT32               ulDataLen;                                              /* 数据的长度                                */
    VOS_UINT8               *pucData;                                               /* 数据首地址                                */
} RABM_PS_DATA_IND_STRU;


/*============  CS环回使用 */
#define RABMRLC_CS_DATA_IND     1
typedef struct
{
    MSG_HEADER_STRU     MsgHdr;                                                 /* 消息头                                    */


    VOS_UINT8               ucErr;                                                  /* 指示数据是否发生错误                        */
    VOS_UINT32               ulRbId;                                                 /* radio bear                               */
    VOS_UINT32               ulDataLen;                                              /* 数据的长度                                */
    VOS_UINT8               *pucData;                                               /* 数据首地址                                */
    VOS_UINT8               ucCrcLen;
}RABMRLC_CS_DATA_IND_STRU;


/* NAS提供给AS使用的API */
NAS_CALLBACK_TYPE    Nas_RrDataInd(VOS_UINT8 ucCnDomain, VOS_UINT32 ulSize, VOS_UINT8 *pucNasMsg, VOS_UINT8 ucICResult);
NAS_CALLBACK_TYPE    Nas_RrPagingInd(PAGING_INFO_STRU *pPagingInfo);
NAS_CALLBACK_TYPE    Nas_RrSysInfoInd(SYSINFO_STRU *pSysInfo);
NAS_CALLBACK_TYPE    Nas_RrEstCnf(VOS_UINT32 ulOpId, VOS_UINT32 ulResult,VOS_UINT32 ulCnDomainId);
NAS_CALLBACK_TYPE    Nas_RrRelInd(VOS_UINT8 ucCnDomain, VOS_UINT32 ulRelCause, VOS_UINT32 ulRrcConnStatus);
NAS_CALLBACK_TYPE    Nas_RrSecurityInd(SECURITY_INFO_STRU *pSecuriryInfo);
NAS_CALLBACK_TYPE    Nas_PlmnSearchCnf(PLMN_SEARCH_RESULT_STRU *pSearchResult);
NAS_CALLBACK_TYPE    Nas_PlmnListInd(PLMN_LIST_STRU *pPlmnList);
NAS_CALLBACK_TYPE    Nas_AreaLostInd(VOS_UINT32 ulRptMode);
NAS_CALLBACK_TYPE    Nas_RabStatusInd(RAB_STATUS_INFO_STRU *pRabInfo);
NAS_CALLBACK_TYPE    Nas_RrSyncInd(SYNC_INFO_STRU *pSyncInfo);
NAS_CALLBACK_TYPE    Nas_RabScInd(RAB_SC_INFO_STRU *pScInfo);
NAS_CALLBACK_TYPE    Nas_PowerOffCnf(VOS_VOID);
NAS_CALLBACK_TYPE    Nas_RrStartCnf(VOS_VOID);
NAS_CALLBACK_TYPE Nas_RrAcInfoChangeInd( VOS_UINT32  ulAcChangeInd );


/* RABM使用的API，由AS提供 */
typedef VOS_INT32 (*RRRABM_RAB_INFO_RSP_FUNC)(VOS_UINT32 ulResult, RAB_RSP_INFO_STRU *pRabInfo);
typedef VOS_INT32 (*RRRABM_RAB_QOS_UPDATE_FUNC)(QOS_INFO_STRU *pQos);

typedef struct rabm_rrc_imported_func_list_stru
{
    RRRABM_RAB_INFO_RSP_FUNC       RrRabmRabInfoRsp;
    RRRABM_RAB_QOS_UPDATE_FUNC     RrRabmRabQosUpdate;
}RABM_RRC_IMPORTED_FUNC_LIST_STRU;

/*A32D00461,zzy,pclint*/
#define  NSAPI_MEM_FAIL()     PS_NAS_LOG(MSP_PID_DIAG_APP_AGENT, 0, OM_PRINT_LEVEL_ERROR, "NAS Mem Operation Failed!");

#define  NSAPI_MSG_FAIL()     PS_NAS_LOG(MSP_PID_DIAG_APP_AGENT, 0, OM_PRINT_LEVEL_ERROR, "NAS Msg Opration Failed!");

#define  NSAPI_TIMER_FAIL()   PS_NAS_LOG(MSP_PID_DIAG_APP_AGENT, 0, OM_PRINT_LEVEL_ERROR, "NAS Timer Opration Failed!");



#ifdef __cplusplus
#if __cplusplus
}
#endif
#endif  /* __cpluscplus */

#endif


