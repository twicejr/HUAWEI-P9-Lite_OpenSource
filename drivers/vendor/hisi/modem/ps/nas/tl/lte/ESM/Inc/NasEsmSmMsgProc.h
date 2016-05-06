/******************************************************************************

        @(#)Copyright(C)2008,Hisilicon Co. LTD.

 ******************************************************************************
    File name   : NasEsmSmMsgProc.h
    Description :
    History     :
     1.李洪 00150010      2011-04-28  Draft Enact

******************************************************************************/

#ifndef _NASESMSMMSGPROC_H
#define _NASESMSMMSGPROC_H


/*****************************************************************************
  1 其他头文件包含
*****************************************************************************/
#include    "vos.h"
#include    "PsTypeDef.h"
#include    "SmEsmInterface.h"
#include    "NasEsmPublic.h"



/*****************************************************************************
  1.1 Cplusplus Announce
*****************************************************************************/
#ifdef __cplusplus
#if __cplusplus
extern "C" {
#endif
#endif
/*****************************************************************************
  #pragma pack(*)    设置字节对齐方式
*****************************************************************************/
#if (VOS_OS_VER != VOS_WIN32)
#pragma pack(4)
#else
#pragma pack(push, 4)
#endif

/*****************************************************************************
  2 macro
*****************************************************************************/
#define NAS_ESM_SavePdnAddr(pstEpsPdnAddr, pstPdpPdnAddr)\
            {\
                (pstEpsPdnAddr)->ucIpType = (pstPdpPdnAddr)->enPdpType;\
                NAS_ESM_MEM_CPY_S((pstEpsPdnAddr)->aucIpV4Addr, APP_MAX_IPV4_ADDR_LEN, \
                                    (pstPdpPdnAddr)->aucIpV4Addr, APP_MAX_IPV4_ADDR_LEN);\
                NAS_ESM_MEM_CPY_S((pstEpsPdnAddr)->aucIpV6Addr, APP_MAX_IPV6_ADDR_LEN, \
                                    (pstPdpPdnAddr)->aucIpV6Addr, APP_MAX_IPV6_ADDR_LEN);\
            }

#define NAS_ESM_SaveApnAddr(pstEpsApnAddr, pstPdpApnAddr)\
            {\
                (pstEpsApnAddr)->ucApnLen = (pstPdpApnAddr)->ucLength;\
                NAS_ESM_MEM_CPY_S((pstEpsApnAddr)->aucApnName, APP_MAX_APN_LEN, \
                                    (pstPdpApnAddr)->aucValue, APP_MAX_APN_LEN);\
            }

#define NAS_ESM_MapTraffClassConventional2EpsQci(pstEpsQos, pstPdpQos)\
            {\
                if (NAS_ESM_SRC_STATISTICS_DESCRIPTROR_SPEECH == (pstPdpQos)->ucSrcStatisticsDescriptor)\
                {\
                    (pstEpsQos)->ucNwQCI = NAS_ESM_QCI_TYPE_QCI1_GBR;\
                    (pstEpsQos)->stQosInfo.ucQCI = NAS_ESM_QCI_TYPE_QCI1_GBR;\
                }\
                else\
                {\
                    if((pstPdpQos)->ucTransDelay >= 15)\
                    {\
                        (pstEpsQos)->ucNwQCI = NAS_ESM_QCI_TYPE_QCI2_GBR;\
                        (pstEpsQos)->stQosInfo.ucQCI = NAS_ESM_QCI_TYPE_QCI2_GBR;\
                    }\
                    else\
                    {\
                        (pstEpsQos)->ucNwQCI = NAS_ESM_QCI_TYPE_QCI3_GBR;\
                        (pstEpsQos)->stQosInfo.ucQCI = NAS_ESM_QCI_TYPE_QCI3_GBR;\
                    }\
                }\
            }

#define NAS_ESM_MapTraffClassInteractive2EpsQci(pstEpsQos, pstPdpQos)\
            {\
                if (NAS_ESM_TRAFFIC_HANDLING_PRIORITY_LEVEL1 == (pstPdpQos)->ucTraffHandlPrior)\
                {\
                    if (NAS_ESM_SIGALLING_INDICATION_OPTIMISED == (pstPdpQos)->ucSignallingIndication)\
                    {\
                        (pstEpsQos)->ucNwQCI = NAS_ESM_QCI_TYPE_QCI5_NONGBR;\
                        (pstEpsQos)->stQosInfo.ucQCI = NAS_ESM_QCI_TYPE_QCI5_NONGBR;\
                    }\
                    else\
                    {\
                        (pstEpsQos)->ucNwQCI = NAS_ESM_QCI_TYPE_QCI6_NONGBR;\
                        (pstEpsQos)->stQosInfo.ucQCI = NAS_ESM_QCI_TYPE_QCI6_NONGBR;\
                    }\
                }\
                else if(NAS_ESM_TRAFFIC_HANDLING_PRIORITY_LEVEL2 == (pstPdpQos)->ucTraffHandlPrior)\
                {\
                    (pstEpsQos)->ucNwQCI = NAS_ESM_QCI_TYPE_QCI7_NONGBR;\
                    (pstEpsQos)->stQosInfo.ucQCI = NAS_ESM_QCI_TYPE_QCI7_NONGBR;\
                }\
                else\
                {\
                    (pstEpsQos)->ucNwQCI = NAS_ESM_QCI_TYPE_QCI8_NONGBR;\
                    (pstEpsQos)->stQosInfo.ucQCI = NAS_ESM_QCI_TYPE_QCI8_NONGBR;\
                }\
            }


/*****************************************************************************
  3 Massage Declare
*****************************************************************************/



/*****************************************************************************
  4 Enum
*****************************************************************************/
enum NAS_ESM_RADIO_PRIORITY_ENUM
{
    NAS_ESM_RADIO_PRIORITY_LEVEL1                   = 0x1,
    NAS_ESM_RADIO_PRIORITY_LEVEL2                   = 0x2,
    NAS_ESM_RADIO_PRIORITY_LEVEL3                   = 0x3,
    NAS_ESM_RADIO_PRIORITY_LEVEL4                   = 0x4,

    NAS_ESM_RADIO_PRIORITY_BUTT
};
typedef VOS_UINT8  NAS_ESM_RADIO_PRIORITY_ENUM_ENUM8;

enum NAS_ESM_TRAFFIC_CLASS_ENUM
{
    NAS_ESM_TRAFFIC_CLASS_SUBSRIBED                 = 0x0,
    NAS_ESM_TRAFFIC_CLASS_CONVENTIONAL              = 0x1,
    NAS_ESM_TRAFFIC_CLASS_STREAMING                 = 0x2,
    NAS_ESM_TRAFFIC_CLASS_INTERACTIVE               = 0x3,
    NAS_ESM_TRAFFIC_CLASS_BACKGROUD                 = 0x4,

    NAS_ESM_TRAFFIC_CLASS_BUTT
};
typedef VOS_UINT8  NAS_ESM_TRAFFIC_CLASS_ENUM_ENUM8;

enum NAS_ESM_TRAFFIC_HANDLING_PRIORITY_ENUM
{
    NAS_ESM_TRAFFIC_HANDLING_PRIORITY_SUBSRIBED     = 0x0,
    NAS_ESM_TRAFFIC_HANDLING_PRIORITY_LEVEL1        = 0x1,
    NAS_ESM_TRAFFIC_HANDLING_PRIORITY_LEVEL2        = 0x2,
    NAS_ESM_TRAFFIC_HANDLING_PRIORITY_LEVEL3        = 0x3,

    NAS_ESM_TRAFFIC_HANDLING_PRIORITY_BUTT
};
typedef VOS_UINT8  NAS_ESM_TRAFFIC_HANDLING_PRIORITY_ENUM_ENUM8;

enum NAS_ESM_SIGALLING_INDICATION_ENUM
{
    NAS_ESM_SIGALLING_INDICATION_NOT_OPTIMISED      = 0x0,
    NAS_ESM_SIGALLING_INDICATION_OPTIMISED          = 0x1,

    NAS_ESM_SIGALLING_INDICATION_BUTT
};
typedef VOS_UINT8  NAS_ESM_SIGALLING_INDICATION_ENUM_ENUM8;



/*****************************************************************************
  5 STRUCT
*****************************************************************************/

/*****************************************************************************
  6 UNION
*****************************************************************************/


/*****************************************************************************
  7 Extern Global Variable
*****************************************************************************/
extern VOS_VOID NAS_ESM_SmMsgDistr
(
    VOS_VOID                           *pRcvMsg
);
extern VOS_VOID  NAS_ESM_RcvPdpContextInfoInd
(
    const SM_ESM_PDP_CONTEXT_INFO_IND_STRU                 *pstRcvMsg
);
extern VOS_VOID  NAS_ESM_ProcSmPdpActivate
(
    const SM_ESM_PDP_CONTEXT_INFO_IND_STRU                 *pstRcvMsg
);
extern VOS_VOID  NAS_ESM_ProcSmPdpModify
(
    const SM_ESM_PDP_CONTEXT_INFO_IND_STRU                 *pstRcvMsg
);
extern VOS_VOID  NAS_ESM_ProcSmPdpDeactivate
(
    const SM_ESM_PDP_CONTEXT_INFO_IND_STRU                 *pstRcvMsg
);
extern VOS_VOID  NAS_ESM_ModifySdfQos
(
    const SM_ESM_PDP_CONTEXT_INFO_IND_STRU  *pstRcvMsg,
    const NAS_ESM_CONTEXT_LTE_QOS_STRU      *pstEpsQos
);
extern VOS_UINT32  NAS_ESM_ValidateSmPdpModify
(
    const SM_ESM_PDP_CONTEXT_INFO_IND_STRU *pstRcvMsg
);
/*****************************************************************************
  8 Fuction Extern
*****************************************************************************/


/*****************************************************************************
  9 OTHERS
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

#endif /* end of NasEsmSmMsgProc.h*/
