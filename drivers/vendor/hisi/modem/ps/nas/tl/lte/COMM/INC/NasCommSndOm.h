

#ifndef __NASCOMMSNDOM_H__
#define __NASCOMMSNDOM_H__


/*****************************************************************************
  1 Include Headfile
*****************************************************************************/
#include  "vos.h"
#include  "LPSCommon.h"
#include  "NasLmmPubMTimer.h"
#include  "NasEsmPublic.h"
#include  "NasERabmPublic.h"
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

/*****************************************************************************
  3 Massage Declare
*****************************************************************************/


/*****************************************************************************
  4 Enum
*****************************************************************************/
/*****************************************************************************
 枚举名    : NAS_LMM_OM_TI_ENUM
 枚举说明  : MM层所有并行状态机的状态保护定时器定义
             BOUNDARY_START，标识该模块定时器在定时器表中的起始下标;
             BOUNDARY_END，标识该模块定时器在定时器表中的结束下标;
             各个模块的定时器定义需要定义在各自响应的区间中.
*****************************************************************************/
enum LNAS_OM_TI_MSG_ENUM
{
    /*****************************************************************
      EMM模块定时器在此定义
    *****************************************************************/

    /*========== 保留定时器 ===================*/
    TI_LNAS_EMM_STATE_NO_TIMER           = PS_MSG_ID_EMM_TO_EMM_OM_BASE,    /* 稳定状态下无定时器 */
    TI_LNAS_EMM_STATE_T3440                      ,                               /*_H2ASN_MsgChoice  NAS_EMM_TIMER_INFO_STRU*/
    TI_LNAS_EMM_STATE_DEL_FORB_TA_PROID          ,            /* 删除禁止的TA */ /*_H2ASN_MsgChoice  NAS_EMM_TIMER_INFO_STRU*/
    /*========== PUB模块定时器 ===================*/
    TI_LNAS_LMM_TIMER_WAIT_USIM_CNF               ,                              /*_H2ASN_MsgChoice  NAS_EMM_TIMER_INFO_STRU*/
    TI_LNAS_LMM_TIMER_WAIT_USIM_READY_START       ,                              /*_H2ASN_MsgChoice  NAS_EMM_TIMER_INFO_STRU*/

    /*========== MRRC 模块定时器 ==============*/
    TI_LNAS_EMM_STATE_MRRC_BOUNDARY_START        ,           /* MRRC 定时器开始边界 */
    TI_LNAS_EMM_MRRC_WAIT_RRC_CONN_CNF           ,                               /*_H2ASN_MsgChoice  NAS_EMM_TIMER_INFO_STRU*/
    TI_LNAS_EMM_MRRC_WAIT_RRC_REL_CNF            ,                               /*_H2ASN_MsgChoice  NAS_EMM_TIMER_INFO_STRU*/

    /*========== ATTACH 模块定时器 ============*/
    TI_LNAS_EMM_STATE_REG_BOUNDARY_START         ,           /* REG 定时器开始边界 */
    TI_LNAS_EMM_T3410                            ,                               /*_H2ASN_MsgChoice  NAS_EMM_TIMER_INFO_STRU*/
    TI_LNAS_EMM_T3411                            ,                               /*_H2ASN_MsgChoice  NAS_EMM_TIMER_INFO_STRU*/
     /*TI_LNAS_EMM_T3402                          ,*/
    TI_LNAS_EMM_WAIT_ESM_PDN_RSP                 ,           /*等待ESM的PDN响应*//*_H2ASN_MsgChoice  NAS_EMM_TIMER_INFO_STRU*/
    TI_LNAS_EMM_WAIT_ESM_BEARER_CNF              ,           /*等待ESM的承载响应*//*_H2ASN_MsgChoice  NAS_EMM_TIMER_INFO_STRU*/
    TI_LNAS_EMM_WAIT_RRC_DATA_CNF                ,           /*等待RRC直传消息传输确认*//*_H2ASN_MsgChoice  NAS_EMM_TIMER_INFO_STRU*/

    /*========== DETACH 模块定时器 ============*/
    TI_LNAS_EMM_STATE_DEREG_BOUNDARY_START       ,           /* DEREG 定时器开始边界 *//*_H2ASN_MsgChoice  NAS_EMM_TIMER_INFO_STRU*/
    TI_LNAS_EMM_T3421                            ,                               /*_H2ASN_MsgChoice  NAS_EMM_TIMER_INFO_STRU*/

    /*========== TAU 模块定时器 ===============*/
    TI_LNAS_EMM_STATE_TAU_BOUNDARY_START         ,           /* TAU 定时器开始边界 */
    TI_LNAS_EMM_STATE_TAU_T3430                  ,                               /*_H2ASN_MsgChoice  NAS_EMM_TIMER_INFO_STRU*/
    TI_LNAS_EMM_STATE_TAU_T3411                  ,                               /*_H2ASN_MsgChoice  NAS_EMM_TIMER_INFO_STRU*/

    /*========== SERVICE 模块定时器 ===========*/
    TI_LNAS_EMM_STATE_SERVICE_BOUNDARY_START     ,           /* SERVICE 定时器开始边界 */
    TI_LNAS_EMM_STATE_SERVICE_T3417              ,                               /*_H2ASN_MsgChoice  NAS_EMM_TIMER_INFO_STRU*/
    TI_LNAS_EMM_STATE_SERVICE_T3417_EXT          ,                               /*_H2ASN_MsgChoice  NAS_EMM_TIMER_INFO_STRU*/
    TI_LNAS_EMM_STATE_SERVICE_T3442              ,                               /*_H2ASN_MsgChoice  NAS_EMM_TIMER_INFO_STRU*/

    /*========== PLMN 模块定时器 ==============*/
    TI_LNAS_EMM_STATE_PLMN_BOUNDARY_START        ,           /* PLMN 定时器开始边界 */
    TI_LNAS_EMM_WAIT_MMC_START_CNF_TIMER         ,
    TI_LNAS_EMM_WAIT_RRC_START_CNF_TIMER         ,
    TI_LNAS_EMM_WAIT_MMC_STOP_CNF_TIMER          ,
    TI_LNAS_EMM_WAIT_RRC_STOP_CNF_TIMER          ,

    /*========== AUTH 模块定时器 ==============*/
    TI_LNAS_EMM_STATE_AUTH_BOUNDARY_START        ,           /* AUTH 定时器开始边界 */
    TI_LNAS_EMM_T3418                            ,                               /*_H2ASN_MsgChoice  NAS_EMM_TIMER_INFO_STRU*/
    TI_LNAS_EMM_T3420                            ,                               /*_H2ASN_MsgChoice  NAS_EMM_TIMER_INFO_STRU*/

    /*========== SUSPEND定时器 ================*/
    TI_LNAS_EMM_RRCORI_WAIT_OTHER_SUSPEND_RSP_TIMER   ,                          /*_H2ASN_MsgChoice  NAS_EMM_TIMER_INFO_STRU*/
    TI_LNAS_EMM_WAIT_SUSPEND_END_TIMER           ,                               /*_H2ASN_MsgChoice  NAS_EMM_TIMER_INFO_STRU*/
    TI_LNAS_EMM_MMCORI_WAIT_OTHER_SUSPEND_RSP_TIMER   ,                          /*_H2ASN_MsgChoice  NAS_EMM_TIMER_INFO_STRU*/
    TI_LNAS_EMM_SYSCFGORI_WAIT_OTHER_SUSPEND_RSP_TIMER   ,                       /*_H2ASN_MsgChoice  NAS_EMM_TIMER_INFO_STRU*/


    /*========== RESEUME定时器 ================*/
    TI_LNAS_EMM_RRCRSM_WAIT_OTHER_RESUME_RSP_TIMER     ,                         /*_H2ASN_MsgChoice  NAS_EMM_TIMER_INFO_STRU*/
    TI_LNAS_EMM_WAIT_SYS_INFO_IND_TIMER         ,                                /*_H2ASN_MsgChoice  NAS_EMM_TIMER_INFO_STRU*/
    TI_LNAS_EMM_SYSCFGRSM_WAIT_OTHER_RESUME_RSP_TIMER,                           /*_H2ASN_MsgChoice  NAS_EMM_TIMER_INFO_STRU*/

    /*========== SYSCFG的定时器 ============================*/
    TI_LNAS_EMM_STATE_WAIT_SYSCFG_CNF_TIMER,                                     /*_H2ASN_MsgChoice  NAS_EMM_TIMER_INFO_STRU*/

    TI_LNAS_EMM_STATE_TI_BUTT                    ,

    /*========== MMC的定时器 ============================*/
    /*========== PLMN_SRCH的定时器 ============================*/
    TI_LNAS_EMMC_STATE_WAIT_PLMN_SRCH_CNF_TIMER,                                 /*_H2ASN_MsgChoice  NAS_EMM_TIMER_INFO_STRU*/

    TI_LNAS_EMMC_STATE_TI_BUTT                    ,

    /*========== END ====================================*/
    LNAS_LMM_STATE_TI_BUTT,

    /*=================== EMM的定时器 ===================*/

    /*========== ATTACH 模块定时器 ============*/
    /*========== DETACH 模块定时器 ============*/
    /*========== TAU 模块定时器 ===============*/
    TI_LNAS_EMM_PTL_T3412                        ,                               /*_H2ASN_MsgChoice  NAS_EMM_TIMER_INFO_STRU*/
    TI_LNAS_EMM_PTL_T3402                        ,                               /*_H2ASN_MsgChoice  NAS_EMM_TIMER_INFO_STRU*/
    TI_LNAS_EMM_PTL_T3423                        ,                               /*_H2ASN_MsgChoice  NAS_EMM_TIMER_INFO_STRU*/

    /*========== AUTH 模块定时器 ===============*/
    TI_LNAS_EMM_PTL_T3416                        ,                               /*_H2ASN_MsgChoice  NAS_EMM_TIMER_INFO_STRU*/

    /*========== 关机定时器 ===================*/
    TI_LNAS_EMM_PTL_SWITCH_OFF_TIMER             ,                               /*_H2ASN_MsgChoice  NAS_EMM_TIMER_INFO_STRU*/


    TI_LNAS_EMM_PTL_TI_BUTT                      ,

    /*========== MMC的定时器 ==================*/
    LNAS_LMM_PTL_TI_BUTT,

    /*****************************************************************
      ESM模块定时器在此定义
    *****************************************************************/



    /* 移到pubmom.h中 */
};
typedef VOS_UINT32 LNAS_OM_TI_MSG_ENUM_UINT32;

/*****************************************************************************
 枚举名    : LNAS_OM_DEBUG_MSG_ENUM_UINT32
 枚举说明  : LNAS各模块可维可测消息ID, NAS所有可维可测消息ID在此定义
*****************************************************************************/
enum LNAS_OM_DEBUG_MSG_ENUM
{
    ID_NAS_LMM_OM_LOG_SET_REG_DOMAIN = TL_DBG_MSG_ID_LTE_NAS_BASE + 0x00,       /*_H2ASN_MsgChoice  NAS_EMM_TIMER_INFO_STRU*/
    LNAS_OM_LOG_IMSI_REFRESH_STATUS_IND = TL_DBG_MSG_ID_LTE_NAS_BASE + 0x01,    /*_H2ASN_MsgChoice NAS_EMM_IMSI_REFRESH_STATUS_STRU*/
    LNAS_OM_DEBUG_MSG                = TL_DBG_MSG_ID_LTE_NAS_BASE + 0x80
};
typedef VOS_UINT32 LNAS_OM_DEBUG_MSG_ENUM_UINT32;

/*****************************************************************************
   5 STRUCT
*****************************************************************************/


typedef struct
{
    LNAS_OM_TI_MSG_ENUM_UINT32          enMsgId;            /*_H2ASN_MsgChoice_Export LNAS_OM_TI_MSG_ENUM_UINT32*/
    VOS_UINT8                           aucMsg[4];
    /***************************************************************************
        _H2ASN_MsgChoice_When_Comment          LNAS_OM_TI_MSG_ENUM_UINT32
    ****************************************************************************/
}LNAS_OM_INTERFACE_MSG_DATA;
/*_H2ASN_Length UINT32*/


typedef struct
{
    VOS_MSG_HEADER
    LNAS_OM_INTERFACE_MSG_DATA           stMsgData;
} NasCommSndOm_MSG;

/*****************************************************************************
  6 UNION
*****************************************************************************/


/*****************************************************************************
  7 Extern Global Variable
*****************************************************************************/


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

#endif /* end of NasCommPrint.h */
