/************************************************************************
  Copyright   : 2005-2007, Huawei Tech. Co., Ltd.
  File name   : Om.h
  Author      : Zongyan Lee
  Version     : V100R001
  Date        : 2005-04-15
  Description : MAPS TAF OM对外的接口头文件。
  History     :
  1. Date:2005-04-15
     Author: Zongyan Lee
     Modification:Create
  2. Date:2005-09-08
     Author: Xiaopeng Du
     Modification:add for A32D00484
************************************************************************/

#ifndef _TRACE_LEVEL_H_
#define _TRACE_LEVEL_H_

#ifdef __cplusplus
#if __cplusplus
extern "C" {
#endif /* __cpluscplus */
#endif /* __cpluscplus */

#include"wuepscfg.h"

/*extern VOS_VOID WUEPS_MSG_TRACE( VOS_UINT32 ,VOS_UCHAR *,VOS_UINT32 ,VOS_CHAR * );*/

#if (VOS_WIN32 == VOS_OS_VER)
extern VOS_CHAR *gcFName;
extern VOS_UINT32 ulLine;
#endif
/*
LEVEL1: 输出各TASK状态迁移信息；
LEVEL2: 输出各TASK与网侧交互的空口消息名称及对应的16进制数据；
LEVEL3: 输出协议栈各TASK与外部模块（HPA/APP/USIM/AGENT/NVM）之间的层间原语rcv/snd信息，及原语的一些
        关键参数；
       （频繁收发的层间原语除外，比如CPHY_SYNC_IND, PHY_DATA_REQ/IND等等）；
LEVEL4: 输出协议栈内部各TASK的层间原语rcv/snd信息，及原语的一些关键参数；
       （频繁收发的层间原语除外，比如MAC_DATA_IND）；
LEVEL5: 输出各种出错信息(包括各种消息解析错误，层间原语检查错误，代码运行异常信息等等）；
LEVEL6: 输出各TASK内部运行的一些信息；
LEVEL7: RESERVED
LEVEL8: 输出频繁的层间原语；
*/

#if 0
extern VOS_VOID SYSTEM_TRACE_FUNC(VOS_UINT32 ulTraceLevel,const VOS_CHAR *pcTraceString,...);
#if (VOS_WIN32 == VOS_OS_VER)
#define WUEPS_TRACE     \
    gcFName = __FILE__;\
    ulLine = __LINE__;\
    SYSTEM_TRACE_FUNC
#else
#define WUEPS_TRACE     SYSTEM_TRACE_FUNC
#endif
#endif

/* Definitions of trace levels for all TASKs and API interfaces */
/* ADMIN TASK */
#define ADMIN_LOG_LEVEL             0x00000100                                  /* ADMIN Task level  */
#define ADMIN_LOG_LEVEL_1           (ADMIN_LOG_LEVEL | 0x00000001)              /* ADMIN level 1: */
#define ADMIN_LOG_LEVEL_2           (ADMIN_LOG_LEVEL | 0x00000002)              /* ADMIN level 2: */
#define ADMIN_LOG_LEVEL_3           (ADMIN_LOG_LEVEL | 0x00000004)              /* ADMIN level 3: */
#define ADMIN_LOG_LEVEL_4           (ADMIN_LOG_LEVEL | 0x00000008)              /* ADMIN level 4: */
#define ADMIN_LOG_LEVEL_5           (ADMIN_LOG_LEVEL | 0x00000010)              /* ADMIN level 5: */
#define ADMIN_LOG_LEVEL_6           (ADMIN_LOG_LEVEL | 0x00000020)              /* ADMIN level 6: */
#define ADMIN_LOG_LEVEL_7           (ADMIN_LOG_LEVEL | 0x00000040)              /* ADMIN level 7: */
#define ADMIN_LOG_LEVEL_8           (ADMIN_LOG_LEVEL | 0x00000080)              /* ADMIN level 8: */

/* WRR TASK */
#define WRR_LOG_LEVEL              0x00000200
#define WRR_LOG_LEVEL_1            (WRR_LOG_LEVEL | 0x00000001)
#define WRR_LOG_LEVEL_2            (WRR_LOG_LEVEL | 0x00000002)
#define WRR_LOG_LEVEL_3            (WRR_LOG_LEVEL | 0x00000004)
#define WRR_LOG_LEVEL_4            (WRR_LOG_LEVEL | 0x00000008)
#define WRR_LOG_LEVEL_5            (WRR_LOG_LEVEL | 0x00000010)
#define WRR_LOG_LEVEL_6            (WRR_LOG_LEVEL | 0x00000020)
#define WRR_LOG_LEVEL_7            (WRR_LOG_LEVEL | 0x00000040)
#define WRR_LOG_LEVEL_8            (WRR_LOG_LEVEL | 0x00000080)

#define WCOM_LOG_LEVEL              0x00000400
#define WCOM_LOG_LEVEL_1            (WCOM_LOG_LEVEL | 0x00000001)
#define WCOM_LOG_LEVEL_2            (WCOM_LOG_LEVEL | 0x00000002)
#define WCOM_LOG_LEVEL_3            (WCOM_LOG_LEVEL | 0x00000004)
#define WCOM_LOG_LEVEL_4            (WCOM_LOG_LEVEL | 0x00000008)
#define WCOM_LOG_LEVEL_5            (WCOM_LOG_LEVEL | 0x00000010)
#define WCOM_LOG_LEVEL_6            (WCOM_LOG_LEVEL | 0x00000020)
#define WCOM_LOG_LEVEL_7            (WCOM_LOG_LEVEL | 0x00000040)
#define WCOM_LOG_LEVEL_8            (WCOM_LOG_LEVEL | 0x00000080)

#if 0
/* RRCF TASK */
#define RRCF_LOG_LEVEL              0x00000200                                  /* RRCF Task level  */
#define RRCF_LOG_LEVEL_1            (RRCF_LOG_LEVEL | 0x00000001)               /* RRCF level 1: */
#define RRCF_LOG_LEVEL_2            (RRCF_LOG_LEVEL | 0x00000002)               /* RRCF level 2: */
#define RRCF_LOG_LEVEL_3            (RRCF_LOG_LEVEL | 0x00000004)               /* RRCF level 3: */
#define RRCF_LOG_LEVEL_4            (RRCF_LOG_LEVEL | 0x00000008)               /* RRCF level 4: */
#define RRCF_LOG_LEVEL_5            (RRCF_LOG_LEVEL | 0x00000010)               /* RRCF level 5: */
#define RRCF_LOG_LEVEL_6            (RRCF_LOG_LEVEL | 0x00000020)               /* RRCF level 6: */
#define RRCF_LOG_LEVEL_7            (RRCF_LOG_LEVEL | 0x00000040)               /* RRCF level 7: */
#define RRCF_LOG_LEVEL_8            (RRCF_LOG_LEVEL | 0x00000080)               /* RRCF level 8: */

/* RMF TASK */
#define RMF_LOG_LEVEL               0x00000400                                  /* RMF Task level  */
#define RMF_LOG_LEVEL_1             (RMF_LOG_LEVEL | 0x00000001)                /* RMF level 1: */
#define RMF_LOG_LEVEL_2             (RMF_LOG_LEVEL | 0x00000002)                /* RMF level 2: */
#define RMF_LOG_LEVEL_3             (RMF_LOG_LEVEL | 0x00000004)                /* RMF level 3: */
#define RMF_LOG_LEVEL_4             (RMF_LOG_LEVEL | 0x00000008)                /* RMF level 4: */
#define RMF_LOG_LEVEL_5             (RMF_LOG_LEVEL | 0x00000010)                /* RMF level 5: */
#define RMF_LOG_LEVEL_6             (RMF_LOG_LEVEL | 0x00000020)                /* RMF level 6: */
#define RMF_LOG_LEVEL_7             (RMF_LOG_LEVEL | 0x00000040)                /* RMF level 7: */
#define RMF_LOG_LEVEL_8             (RMF_LOG_LEVEL | 0x00000080)                /* RMF level 8: */

/* RSRF TASK */
#define RSRF_LOG_LEVEL              0x00000800                                  /* RSRF Task level  */
#define RSRF_LOG_LEVEL_1            (RSRF_LOG_LEVEL | 0x00000001)               /* RSRF level 1: */
#define RSRF_LOG_LEVEL_2            (RSRF_LOG_LEVEL | 0x00000002)               /* RSRF level 2: */
#define RSRF_LOG_LEVEL_3            (RSRF_LOG_LEVEL | 0x00000004)               /* RSRF level 3: */
#define RSRF_LOG_LEVEL_4            (RSRF_LOG_LEVEL | 0x00000008)               /* RSRF level 4: */
#define RSRF_LOG_LEVEL_5            (RSRF_LOG_LEVEL | 0x00000010)               /* RSRF level 5: */
#define RSRF_LOG_LEVEL_6            (RSRF_LOG_LEVEL | 0x00000020)               /* RSRF level 6: */
#define RSRF_LOG_LEVEL_7            (RSRF_LOG_LEVEL | 0x00000040)               /* RSRF level 7: */
#define RSRF_LOG_LEVEL_8            (RSRF_LOG_LEVEL | 0x00000080)               /* RSRF level 8: */

/* RCSF TASK */
#define RCSF_LOG_LEVEL              0x00001000                                  /* RCSF Task level  */
#define RCSF_LOG_LEVEL_1            (RCSF_LOG_LEVEL | 0x00000001)               /* RCSF level 1: */
#define RCSF_LOG_LEVEL_2            (RCSF_LOG_LEVEL | 0x00000002)               /* RCSF level 2: */
#define RCSF_LOG_LEVEL_3            (RCSF_LOG_LEVEL | 0x00000004)               /* RCSF level 3: */
#define RCSF_LOG_LEVEL_4            (RCSF_LOG_LEVEL | 0x00000008)               /* RCSF level 4: */
#define RCSF_LOG_LEVEL_5            (RCSF_LOG_LEVEL | 0x00000010)               /* RCSF level 5: */
#define RCSF_LOG_LEVEL_6            (RCSF_LOG_LEVEL | 0x00000020)               /* RCSF level 6: */
#define RCSF_LOG_LEVEL_7            (RCSF_LOG_LEVEL | 0x00000040)               /* RCSF level 7: */
#define RCSF_LOG_LEVEL_8            (RCSF_LOG_LEVEL | 0x00000080)               /* RCSF level 8: */
#endif

/* PDCP TASK */
#define PDCP_LOG_LEVEL              0x00002000                                  /* PDCP Task level  */
#define PDCP_LOG_LEVEL_1            (PDCP_LOG_LEVEL | 0x00000001)               /* PDCP level 1: */
#define PDCP_LOG_LEVEL_2            (PDCP_LOG_LEVEL | 0x00000002)               /* PDCP level 2: */
#define PDCP_LOG_LEVEL_3            (PDCP_LOG_LEVEL | 0x00000004)               /* PDCP level 3: */
#define PDCP_LOG_LEVEL_4            (PDCP_LOG_LEVEL | 0x00000008)               /* PDCP level 4: */
#define PDCP_LOG_LEVEL_5            (PDCP_LOG_LEVEL | 0x00000010)               /* PDCP level 5: */
#define PDCP_LOG_LEVEL_6            (PDCP_LOG_LEVEL | 0x00000020)               /* PDCP level 6: */
#define PDCP_LOG_LEVEL_7            (PDCP_LOG_LEVEL | 0x00000040)               /* PDCP level 7: */
#define PDCP_LOG_LEVEL_8            (PDCP_LOG_LEVEL | 0x00000080)               /* PDCP level 8: */

/* RLC TASK */
#define RLC_LOG_LEVEL               0x00004000                                  /* RLC Task level  */
#define RLC_LOG_LEVEL_1             (RLC_LOG_LEVEL | 0x00000001)                /* RLC level 1: */
#define RLC_LOG_LEVEL_2             (RLC_LOG_LEVEL | 0x00000002)                /* RLC level 2: */
#define RLC_LOG_LEVEL_3             (RLC_LOG_LEVEL | 0x00000004)                /* RLC level 3: */
#define RLC_LOG_LEVEL_4             (RLC_LOG_LEVEL | 0x00000008)                /* RLC level 4: */
#define RLC_LOG_LEVEL_5             (RLC_LOG_LEVEL | 0x00000010)                /* RLC level 5: */
#define RLC_LOG_LEVEL_6             (RLC_LOG_LEVEL | 0x00000020)                /* RLC level 6: */
#define RLC_LOG_LEVEL_7             (RLC_LOG_LEVEL | 0x00000040)                /* RLC level 7: */
#define RLC_LOG_LEVEL_8             (RLC_LOG_LEVEL | 0x00000080)                /* RLC level 8: */

/* MAC TASK */
#define MAC_LOG_LEVEL               0x00008000                                  /* MAC Task level  */
#define MAC_LOG_LEVEL_1             (MAC_LOG_LEVEL | 0x00000001)                /* MAC level 1: */
#define MAC_LOG_LEVEL_2             (MAC_LOG_LEVEL | 0x00000002)                /* MAC level 2: */
#define MAC_LOG_LEVEL_3             (MAC_LOG_LEVEL | 0x00000004)                /* MAC level 3: */
#define MAC_LOG_LEVEL_4             (MAC_LOG_LEVEL | 0x00000008)                /* MAC level 4: */
#define MAC_LOG_LEVEL_5             (MAC_LOG_LEVEL | 0x00000010)                /* MAC level 5: */
#define MAC_LOG_LEVEL_6             (MAC_LOG_LEVEL | 0x00000020)                /* MAC level 6: */
#define MAC_LOG_LEVEL_7             (MAC_LOG_LEVEL | 0x00000040)                /* MAC level 7: */
#define MAC_LOG_LEVEL_8             (MAC_LOG_LEVEL | 0x00000080)                /* MAC level 8: */

/* RABM TASK */
#define RABM_LOG_LEVEL              0x00010000                                  /* RABM Task level  */
#define RABM_LOG_LEVEL_1            (RABM_LOG_LEVEL | 0x00000001)               /* RABM level 1: */
#define RABM_LOG_LEVEL_2            (RABM_LOG_LEVEL | 0x00000002)               /* RABM level 2: */
#define RABM_LOG_LEVEL_3            (RABM_LOG_LEVEL | 0x00000004)               /* RABM level 3: */
#define RABM_LOG_LEVEL_4            (RABM_LOG_LEVEL | 0x00000008)               /* RABM level 4: */
#define RABM_LOG_LEVEL_5            (RABM_LOG_LEVEL | 0x00000010)               /* RABM level 5: */
#define RABM_LOG_LEVEL_6            (RABM_LOG_LEVEL | 0x00000020)               /* RABM level 6: */
#define RABM_LOG_LEVEL_7            (RABM_LOG_LEVEL | 0x00000040)               /* RABM level 7: */
#define RABM_LOG_LEVEL_8            (RABM_LOG_LEVEL | 0x00000080)               /* RABM level 8: */

/* MM TASK */
#define MM_LOG_LEVEL                0x00020000                                  /* MM Task level  */
#define MM_LOG_LEVEL_1              (MM_LOG_LEVEL | 0x00000001)                 /* MM level 1: */
#define MM_LOG_LEVEL_2              (MM_LOG_LEVEL | 0x00000002)                 /* MM level 2: */
#define MM_LOG_LEVEL_3              (MM_LOG_LEVEL | 0x00000004)                 /* MM level 3: */
#define MM_LOG_LEVEL_4              (MM_LOG_LEVEL | 0x00000008)                 /* MM level 4: */
#define MM_LOG_LEVEL_5              (MM_LOG_LEVEL | 0x00000010)                 /* MM level 5: */
#define MM_LOG_LEVEL_6              (MM_LOG_LEVEL | 0x00000020)                 /* MM level 6: */
#define MM_LOG_LEVEL_7              (MM_LOG_LEVEL | 0x00000040)                 /* MM level 7: */
#define MM_LOG_LEVEL_8              (MM_LOG_LEVEL | 0x00000080)                 /* MM level 8: */

/* MMC TASK */
#define MMC_LOG_LEVEL               0x00040000                                  /* MMC Task level  */
#define MMC_LOG_LEVEL_1             (MMC_LOG_LEVEL | 0x00000001)                /* MMC level 1: */
#define MMC_LOG_LEVEL_2             (MMC_LOG_LEVEL | 0x00000002)                /* MMC level 2: */
#define MMC_LOG_LEVEL_3             (MMC_LOG_LEVEL | 0x00000004)                /* MMC level 3: */
#define MMC_LOG_LEVEL_4             (MMC_LOG_LEVEL | 0x00000008)                /* MMC level 4: */
#define MMC_LOG_LEVEL_5             (MMC_LOG_LEVEL | 0x00000010)                /* MMC level 5: */
#define MMC_LOG_LEVEL_6             (MMC_LOG_LEVEL | 0x00000020)                /* MMC level 6: */
#define MMC_LOG_LEVEL_7             (MMC_LOG_LEVEL | 0x00000040)                /* MMC level 7: */
#define MMC_LOG_LEVEL_8             (MMC_LOG_LEVEL | 0x00000080)                /* MMC level 8: */

/* GMM TASK */
#define GMM_LOG_LEVEL               0x00080000                                  /* GMM Task level  */
#define GMM_LOG_LEVEL_1             (GMM_LOG_LEVEL | 0x00000001)                /* GMM level 1: */
#define GMM_LOG_LEVEL_2             (GMM_LOG_LEVEL | 0x00000002)                /* GMM level 2: */
#define GMM_LOG_LEVEL_3             (GMM_LOG_LEVEL | 0x00000004)                /* GMM level 3: */
#define GMM_LOG_LEVEL_4             (GMM_LOG_LEVEL | 0x00000008)                /* GMM level 4: */
#define GMM_LOG_LEVEL_5             (GMM_LOG_LEVEL | 0x00000010)                /* GMM level 5: */
#define GMM_LOG_LEVEL_6             (GMM_LOG_LEVEL | 0x00000020)                /* GMM level 6: */
#define GMM_LOG_LEVEL_7             (GMM_LOG_LEVEL | 0x00000040)                /* GMM level 7: */
#define GMM_LOG_LEVEL_8             (GMM_LOG_LEVEL | 0x00000080)                /* GMM level 8: */

/* CC TASK */
#define CC_LOG_LEVEL                0x00100000                                  /* CC Task level  */
#define CC_LOG_LEVEL_1              (CC_LOG_LEVEL | 0x00000001)                 /* CC level 1: */
#define CC_LOG_LEVEL_2              (CC_LOG_LEVEL | 0x00000002)                 /* CC level 2: */
#define CC_LOG_LEVEL_3              (CC_LOG_LEVEL | 0x00000004)                 /* CC level 3: */
#define CC_LOG_LEVEL_4              (CC_LOG_LEVEL | 0x00000008)                 /* CC level 4: */
#define CC_LOG_LEVEL_5              (CC_LOG_LEVEL | 0x00000010)                 /* CC level 5: */
#define CC_LOG_LEVEL_6              (CC_LOG_LEVEL | 0x00000020)                 /* CC level 6: */
#define CC_LOG_LEVEL_7              (CC_LOG_LEVEL | 0x00000040)                 /* CC level 7: */
#define CC_LOG_LEVEL_8              (CC_LOG_LEVEL | 0x00000080)                 /* CC level 8: */

/* SM TASK */
#define SM_LOG_LEVEL                0x00200000                                  /* SM Task level  */
#define SM_LOG_LEVEL_1              (SM_LOG_LEVEL | 0x00000001)                 /* SM level 1: */
#define SM_LOG_LEVEL_2              (SM_LOG_LEVEL | 0x00000002)                 /* SM level 2: */
#define SM_LOG_LEVEL_3              (SM_LOG_LEVEL | 0x00000004)                 /* SM level 3: */
#define SM_LOG_LEVEL_4              (SM_LOG_LEVEL | 0x00000008)                 /* SM level 4: */
#define SM_LOG_LEVEL_5              (SM_LOG_LEVEL | 0x00000010)                 /* SM level 5: */
#define SM_LOG_LEVEL_6              (SM_LOG_LEVEL | 0x00000020)                 /* SM level 6: */
#define SM_LOG_LEVEL_7              (SM_LOG_LEVEL | 0x00000040)                 /* SM level 7: */
#define SM_LOG_LEVEL_8              (SM_LOG_LEVEL | 0x00000080)                 /* SM level 8: */

/* SMS TASK */
#define SMS_LOG_LEVEL               0x00800000                                  /* SMS Task level  */
#define SMS_LOG_LEVEL_1             (SMS_LOG_LEVEL | 0x00000001)                /* SMS level 1: */
#define SMS_LOG_LEVEL_2             (SMS_LOG_LEVEL | 0x00000002)                /* SMS level 2: */
#define SMS_LOG_LEVEL_3             (SMS_LOG_LEVEL | 0x00000004)                /* SMS level 3: */
#define SMS_LOG_LEVEL_4             (SMS_LOG_LEVEL | 0x00000008)                /* SMS level 4: */
#define SMS_LOG_LEVEL_5             (SMS_LOG_LEVEL | 0x00000010)                /* SMS level 5: */
#define SMS_LOG_LEVEL_6             (SMS_LOG_LEVEL | 0x00000020)                /* SMS level 6: */
#define SMS_LOG_LEVEL_7             (SMS_LOG_LEVEL | 0x00000040)                /* SMS level 7: */
#define SMS_LOG_LEVEL_8             (SMS_LOG_LEVEL | 0x00000080)                /* SMS level 8: */

/* SS TASK */
#define SS_LOG_LEVEL                0x01000000                                  /* SS Task level  */
#define SS_LOG_LEVEL_1              (SS_LOG_LEVEL | 0x00000001)                 /* SS level 1: */
#define SS_LOG_LEVEL_2              (SS_LOG_LEVEL | 0x00000002)                 /* SS level 2: */
#define SS_LOG_LEVEL_3              (SS_LOG_LEVEL | 0x00000004)                 /* SS level 3: */
#define SS_LOG_LEVEL_4              (SS_LOG_LEVEL | 0x00000008)                 /* SS level 4: */
#define SS_LOG_LEVEL_5              (SS_LOG_LEVEL | 0x00000010)                 /* SS level 5: */
#define SS_LOG_LEVEL_6              (SS_LOG_LEVEL | 0x00000020)                 /* SS level 6: */
#define SS_LOG_LEVEL_7              (SS_LOG_LEVEL | 0x00000040)                 /* SS level 7: */
#define SS_LOG_LEVEL_8              (SS_LOG_LEVEL | 0x00000080)                 /* SS level 8: */

/* TC TASK */
#define TC_LOG_LEVEL                0x02000000                                  /* TC Task level  */
#define TC_LOG_LEVEL_1              (TC_LOG_LEVEL | 0x00000001)                 /* TC level 1: */
#define TC_LOG_LEVEL_2              (TC_LOG_LEVEL | 0x00000002)                 /* TC level 2: */
#define TC_LOG_LEVEL_3              (TC_LOG_LEVEL | 0x00000004)                 /* TC level 3: */
#define TC_LOG_LEVEL_4              (TC_LOG_LEVEL | 0x00000008)                 /* TC level 4: */
#define TC_LOG_LEVEL_5              (TC_LOG_LEVEL | 0x00000010)                 /* TC level 5: */
#define TC_LOG_LEVEL_6              (TC_LOG_LEVEL | 0x00000020)                 /* TC level 6: */
#define TC_LOG_LEVEL_7              (TC_LOG_LEVEL | 0x00000040)                 /* TC level 7: */
#define TC_LOG_LEVEL_8              (TC_LOG_LEVEL | 0x00000080)                 /* TC level 8: */

/* SMT API */
#define SMT_LOG_LEVEL               0x04000000                                  /* SMT Task level  */
#define SMT_LOG_LEVEL_1             (SMT_LOG_LEVEL | 0x00000001)                /* SMT level 1: */
#define SMT_LOG_LEVEL_2             (SMT_LOG_LEVEL | 0x00000002)                /* SMT level 2: */
#define SMT_LOG_LEVEL_3             (SMT_LOG_LEVEL | 0x00000004)                /* SMT level 3: */
#define SMT_LOG_LEVEL_4             (SMT_LOG_LEVEL | 0x00000008)                /* SMT level 4: */
#define SMT_LOG_LEVEL_5             (SMT_LOG_LEVEL | 0x00000010)                /* SMT level 5: */
#define SMT_LOG_LEVEL_6             (SMT_LOG_LEVEL | 0x00000020)                /* SMT level 6: */
#define SMT_LOG_LEVEL_7             (SMT_LOG_LEVEL | 0x00000040)                /* SMT level 7: */
#define SMT_LOG_LEVEL_8             (SMT_LOG_LEVEL | 0x00000080)                /* SMT level 8: */

/* WUEPS COMM */
#define COMM_LOG_LEVEL              0x08000000
#define COMM_LOG_LEVEL_1            (COMM_LOG_LEVEL | 0x00000001)                /* COMM level 1: */
#define COMM_LOG_LEVEL_2            (COMM_LOG_LEVEL | 0x00000002)                /* COMM level 2: */
#define COMM_LOG_LEVEL_3            (COMM_LOG_LEVEL | 0x00000004)                /* COMM level 3: */
#define COMM_LOG_LEVEL_4            (COMM_LOG_LEVEL | 0x00000008)                /* COMM level 4: */
#define COMM_LOG_LEVEL_5            (COMM_LOG_LEVEL | 0x00000010)                /* COMM level 5: */
#define COMM_LOG_LEVEL_6            (COMM_LOG_LEVEL | 0x00000020)                /* COMM level 6: */
#define COMM_LOG_LEVEL_7            (COMM_LOG_LEVEL | 0x00000040)                /* COMM level 7: */
#define COMM_LOG_LEVEL_8            (COMM_LOG_LEVEL | 0x00000080)                /* COMM level 8: */






#ifdef __cplusplus
#if __cplusplus
}
#endif
#endif/* __cpluscplus */

#endif
