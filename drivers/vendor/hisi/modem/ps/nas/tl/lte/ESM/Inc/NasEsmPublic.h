/******************************************************************************

  Copyright(C)2008,Hisilicon Co. LTD.

 ******************************************************************************
  File Name       : NasEsmPublic.h
  Description     : NasEsmPublic.h header file
  History           :
      1.丁丽 00128736    2008-08-20  Draft   Enact
      2.杨茜惠 00135146  2008-12-19  Modify  BA8D00752
      3.孙兵 49683       2009-01-06  Modify  BA8D00870
      4.杨茜惠 00135146  2009-03-06  Modify  BA8D01127
      5.李洪00150010       2009-08-03  Modify  BJ9D01608
      6.李洪00150010       2009-08-05  Modify  BJ9D01627


******************************************************************************/

#ifndef __NASESMPUBLIC_H__
#define __NASESMPUBLIC_H__



/*****************************************************************************
  1 Include Headfile
*****************************************************************************/
#include "PsTypeDef.h"
#include "PsCommonDef.h"
#include "EmmEsmInterface.h"
#include "EsmRabmInterface.h"
#include "AppEsmInterface.h"
#include "PsLogdef.h"
#include "OmCommon.h"
#include "Msp_diag_cmd_id.h"
#include  "NasCommPrint.h"
#include "LPsNvInterface.h"
#include "NasCommBuffer.h"
#include "PsLib.h"
#include "SmEsmInterface.h"
#include "UsimPsInterface.h"


#include "product_config.h"

#include "NasFileId.h"


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
  2 Macro
*****************************************************************************/
#define NAS_ESM_NULL                    (0)

#define NAS_ESM_OP_TRUE                 (1)
#define NAS_ESM_OP_FALSE                (0)

#define NAS_ESM_BIT_0                   (1)

#define NAS_ESM_USIM_BACKOFF_PARA_LEN         32
#define NAS_ESM_USIM_BACKOFF_PARA_ADDR_LEN    3

#define NAS_ESM_BACKOFF_IGNORE_FX_DEFAULT_VALUE   60
#define NAS_ESM_BACKOFF_PERM_FX_DEFAULT_VALUE     30
#define NAS_ESM_BACKOFF_TEMP_FX_DEFAULT_VALUE     60

#define NAS_ESM_MAX_PTI_BUFF_ITEM_NUM   (10)                /* 最大PTI缓存记录个数 */
#define NAS_ESM_MAX_ATTACHING_BUFF_ITEM_NUM   (10)          /* 最大ATTACHING过程中缓存记录个数 */

#define NAS_ESM_MAX_EPSB_NUM            (11)                /*最大承载数*/
#define NAS_ESM_MAX_STATETBL_NUM        (11)                /*最大动态表数*/
/*lint -e961*/
#define NAS_ESM_ILL_STATETAL_INDEX      (0xffffffff)        /*非法动态表索引号*/
/*lint +e961*/
#define NAS_ESM_MAX_EPSB_ID             (15)                /*最大的承载号*/
#define NAS_ESM_MIN_EPSB_ID             (5)                 /*最小的承载号*/
#define NAS_ESM_UNASSIGNED_EPSB_ID      (0)                 /*未分配的承载号*/

#define NAS_ESM_MAX_SDF_PF_NUM          (16)                /*SDF所支持的最大PF数*/
#define NAS_ESM_MAX_FLOW_LABEL_TYPE     (0xFFFFF)           /* ipv6中流标记的最大值 */
#define NAS_ESM_SDF_PF_NUM_ONE      (1)                     /*SDF中PF数为1*/

#define NAS_ESM_MAX_UE_CONTRUL_CID_NUM      (NAS_ESM_MAX_UE_CONTRUL_CID + 1)
#define NAS_ESM_MAX_CID_NUM                 (NAS_ESM_MAX_CID + 1)              /*最大承载上下文数参数个数*/

#define NAS_ESM_CID_NV_NUM              (12)                /* NV参数的数目 */

#define NAS_ESM_MAX_UE_CONTRUL_CID      (20)                /*UE控制的最大CID*/
#define NAS_ESM_MIN_NW_CONTROL_CID      (21)                /*NW控制的最小CID*/

#define NAS_ESM_MAX_CID                 (31)                /*最大的CID*/
#define NAS_ESM_MIN_CID                 (0)                 /*最小的CID*/
#define NAS_ESM_ILL_CID                 (32)                /*无效的CID*/
#define NAS_ESM_ATTACH_CID              (0)                 /*注册CID*/

#define NAS_ESM_MAX_PDN_NUM             (4)                 /*最大PDN数*/
#define NAS_ESM_MAX_APN_NUM             (100)               /*最大APN数*/

#define NAS_ESM_PTI_UNASSIGNED_VALUE    0x00                /*未分配的PTI*/
#define NAS_ESM_PTI_MAX_VALUE           0xFE                /*PTI的最大值*/
#define NAS_ESM_PTI_MIN_VALUE           0x01                 /*PTI的最小值*/

#define NAS_ESM_PTI_RESERVED_VALUE      0xFF                /*保留的PTI值*/
#define NAS_ESM_GWAUTHID_MAX_VALUE      0xFE                /*GW AUTH ID的最大值*/
#define NAS_ESM_GWAUTHID_MIN_VALUE      0x0                 /*GW AUTH ID的最小值*/
#define NAS_ESM_AUTH_CHALLENGE_VALUE_LEN    16
#define NAS_ESM_AUTH_RESPONSE_VALUE_LEN     16
#define NAS_ESM_MAX_MD5_INPUT_PARA_LEN      (1+APP_ESM_MAX_PASSWORD_LEN+NAS_ESM_AUTH_RESPONSE_VALUE_LEN)

#define NAS_ESM_RELEASE_CTRL_R8             0
#define NAS_ESM_RELEASE_CTRL_R9             1

#define NAS_ESM_RELEASE_CTRL                NAS_ESM_RELEASE_CTRL_R8
/*lint -e961*/
#define NAS_ESM_MAX_UINT32              (0xffffffff)        /*最大UINT32数*/
#define NAS_ESM_MAX_OPID_VALUE          (0xfffffffe)        /*OPID的最大值*/
#define NAS_ESM_MIN_OPID_VALUE          (0)                 /*OPID的最小值*/
#define NAS_ESM_ILLEGAL_OPID            (0xffffffff)        /*无效OPID*/
/*lint +e961*/

#define NAS_ESM_MIN_PDN_NUM             (1)                 /*最少的PDN数*/

#define NAS_ESM_MSG_LOW_BIT             0x0F
#define NAS_ESM_MSG_HIGH_BIT            0xF0
#define NAS_ESM_MSG_HIGH_3_BIT          0xE0

#define NAS_ESM_MSG_TWO_LEN             2
#define NAS_ESM_MOVEMENT_2_BITS         2
#define NAS_ESM_MOVEMENT_3_BITS         3
#define NAS_ESM_MOVEMENT_4_BITS         4
#define NAS_ESM_MOVEMENT_5_BITS         5
#define NAS_ESM_MOVEMENT_6_BITS         6
#define NAS_ESM_MOVEMENT_7_BITS         7
#define NAS_ESM_MOVEMENT_8_BITS         8
#define NAS_ESM_MOVEMENT_16_BITS        16
#define NAS_ESM_MOVEMENT_24_BITS        24

#define NAS_ESM_SEA_TABLE_ERR_LOC       0xFF
#define NAS_ESM_EVENTTYPE_FAIL          0xFFFF

#define NAS_ESM_LOW_2_BIT_MASK          0x03

#define NAS_ESM_HIGH_5_BIT_MASK         0xF8

/*状态表中上行空口消息的缓存长度*/
#define NAS_ESM_AIR_MSG_BUFFER_LEN      1024

/* 承载对应的激活的Cid个数为1 */
#define NAS_ESM_BEARER_ACT_CID_NUM_ONE  1

#define NAS_ESM_MSGID_OFFSET            (2)

#define NAS_ESM_MAX_PCSCF_NUM           (3)
#define NAS_ESM_MAX_DNS_SERVER_NUM      (2)
#define NAS_ESM_MAX_NBNS_NUM            (2)

/* 删除PCO flag相关无效代码 y00307272 20151205 DTS2015101700432 */

#define NAS_ESM_DEL_SDF_WITH_QOS_OFF    (0)
#define NAS_ESM_DEL_SDF_WITH_QOS_ON     (1)

#define NAS_ERABM_IPV6_PREFIX_LEN       (8)

/*定时器时长*/
#ifdef PS_ITT_PC_TEST_NAS
#define TI_NAS_ESM_T3482_TIMER_LEN      8000                /*T3482的时间长度，in milliseconds*/
#define TI_NAS_ESM_T3492_TIMER_LEN      3000                /*T3492的时间长度，in milliseconds*/
#define TI_NAS_ESM_T3480_TIMER_LEN      7000                /*T3480的时间长度，in milliseconds*/
#define TI_NAS_ESM_T3481_TIMER_LEN      4000                /*T3481的时间长度，in milliseconds*/

#define TI_NAS_ESM_WAIT_APP_CNF_TIMER_LEN 5000              /*WAIT_APP_CNF_TIMER的时间长度，in milliseconds*/

#define TI_NAS_ESM_WAIT_PTI_INVALID_TIMER_LEN 10000         /*WAIT_PTI_INVALID_TIMER的时间长度，in milliseconds*/
#else
#define TI_NAS_ESM_T3482_TIMER_LEN      8000                /*T3482的时间长度，in milliseconds*/
#define TI_NAS_ESM_T3492_TIMER_LEN      6000                /*T3492的时间长度，in milliseconds*/
#define TI_NAS_ESM_T3480_TIMER_LEN      8000                /*T3480的时间长度，in milliseconds*/
#define TI_NAS_ESM_T3481_TIMER_LEN      8000

#define TI_NAS_ESM_WAIT_APP_CNF_TIMER_LEN 10000             /*WAIT_APP_CNF_TIMER的时间长度，in milliseconds*/

#define TI_NAS_ESM_WAIT_PTI_INVALID_TIMER_LEN 50000         /*WAIT_PTI_INVALID_TIMER的时间长度，in milliseconds*/

#endif

#define TI_NAS_ESM_ATTACH_BEARER_REEST_TIMER_LEN    1800    /*Default value of attach bearer re-establishement timer, in second*/
#define TI_NAS_ESM_REL_NON_EMC_BEARER_TIMER_LEN     3000    /*延迟释放非紧急承载定时器时长, in milliseconds*/

#define TI_NAS_ESM_BACKOFF_WAIT_USIM_CNF_TIMER_LEN  3000    /* BACKOFF算法相关参数读USIM文件等待定时器时长 */

/* 网侧重发缺省承载激活请求定时器 */
#define TI_NAS_ESM_T3485_TIMER_LEN                  8000


/*封装打印LOG的宏*/
#ifdef PS_ITT_PC_TEST
#define NAS_ESM_INFO_LOG(String) \
                 vos_printf(" %s\r\n",String)/*LPS_LOG(UE_MODULE_ESM_ID, VOS_NULL, PS_PRINT_INFO, String)
 */
#define NAS_ESM_INFO_LOG1(String, Para1) \
                 vos_printf(" %s %d\r\n",String, (long)Para1)/*LPS_LOG1(UE_MODULE_ESM_ID, VOS_NULL, PS_PRINT_INFO, String, (long)Para1 )
 */
#define NAS_ESM_INFO_LOG2(String, Para1, Para2) \
                 vos_printf(" %s %d %d\r\n",String, (long)Para1, (long)Para2)/*LPS_LOG2(UE_MODULE_ESM_ID, VOS_NULL, PS_PRINT_INFO, String, (long)Para1, (long)Para2)
 */
#define NAS_ESM_NORM_LOG(String) \
                 vos_printf(" %s\r\n",String)/*LPS_LOG(UE_MODULE_ESM_ID, VOS_NULL, PS_PRINT_NORMAL, String)
 */
#define NAS_ESM_WARN_LOG(String) \
                 vos_printf(" %s\r\n",String)/*LPS_LOG(UE_MODULE_ESM_ID, VOS_NULL, PS_PRINT_WARNING, String)
 */
#define NAS_ESM_ERR_LOG(String) \
                 vos_printf(" %s\r\n",String)/*LPS_LOG(UE_MODULE_ESM_ID, VOS_NULL, PS_PRINT_ERROR, String)
 */
#define NAS_ESM_LOG1(String, Para1) \
                 vos_printf(" %s %d\r\n",String, (long)Para1)/*LPS_LOG1(UE_MODULE_ESM_ID, VOS_NULL, PS_PRINT_NORMAL, String, (long)Para1 )
 */
#define NAS_ESM_LOG2(String, Para1, Para2) \
                 vos_printf(" %s %d %d\r\n",String, (long)Para1, (long)Para2)/*LPS_LOG2(UE_MODULE_ESM_ID, VOS_NULL, PS_PRINT_NORMAL, String, (long)Para1, (long)Para2)
 */
#else
#define NAS_ESM_INFO_LOG(String) \
                 LPS_LOG(UE_MODULE_ESM_ID, VOS_NULL, LOG_LEVEL_INFO, String)
#define NAS_ESM_INFO_LOG1(String, Para1) \
                 LPS_LOG1(UE_MODULE_ESM_ID, VOS_NULL, LOG_LEVEL_INFO, String, (long)Para1 )
#define NAS_ESM_INFO_LOG2(String, Para1, Para2) \
                 LPS_LOG2(UE_MODULE_ESM_ID, VOS_NULL, LOG_LEVEL_INFO, String, (long)Para1, (long)Para2)
#define NAS_ESM_NORM_LOG(String) \
                 LPS_LOG(UE_MODULE_ESM_ID, VOS_NULL, LOG_LEVEL_NORMAL, String)
#define NAS_ESM_WARN_LOG(String) \
                 LPS_LOG(UE_MODULE_ESM_ID, VOS_NULL, LOG_LEVEL_WARNING, String)
#define NAS_ESM_ERR_LOG(String) \
                 LPS_LOG(UE_MODULE_ESM_ID, VOS_NULL, LOG_LEVEL_ERROR, String)
#define NAS_ESM_LOG1(String, Para1) \
                 LPS_LOG1(UE_MODULE_ESM_ID, VOS_NULL, LOG_LEVEL_NORMAL, String, (long)Para1 )
#define NAS_ESM_LOG2(String, Para1, Para2) \
                 LPS_LOG2(UE_MODULE_ESM_ID, VOS_NULL, LOG_LEVEL_NORMAL, String, (long)Para1, (long)Para2)

#endif

#define NAS_ESM_GET_MSG_LENGTH(pMsg)        ((pMsg)->ulLength)
#define NAS_ESM_GET_MSG_ENTITY(pMsg)        ((VOS_VOID*)&((pMsg)->ulMsgId))
#define NAS_ESM_MIN(n1,n2)                  (((n1)>(n2))?(n2):(n1))

#if (FEATURE_ON == FEATURE_UE_MODE_CDMA)
#define NAS_ESM_GET_EHSM_MSG_LENGTH(pMsg)        ((pMsg)->ulLength)
#define NAS_ESM_GET_EHSM_MSG_ENTITY(pMsg)        ((VOS_VOID*)&((pMsg)->enMsgId))
#endif

/*封装写APP消息头的宏*/
#define NAS_ESM_WRITE_APP_MSG_HEAD(pstMsg, ulApptMsgID, usOrigId, usTermId, ulSn)\
                    (pstMsg)->ulMsgId = (ulApptMsgID);\
                    (pstMsg)->ulSenderCpuId = VOS_LOCAL_CPUID;\
                    (pstMsg)->ulSenderPid = PS_PID_ESM;\
                    (pstMsg)->ulReceiverCpuId = VOS_LOCAL_CPUID;\
                    (pstMsg)->ulReceiverPid = PS_PID_APP;\
                    (pstMsg)->usOriginalId = (usOrigId);\
                    (pstMsg)->usTerminalId = (usTermId);\
                    (pstMsg)->ulSN         = (ulSn);

/* 封装写TAF消息头的宏, L4A优化重构, 跟PDP激活相关的消息ESM与TAF交互, 不通过L4A, 消息接口不变*/
#define NAS_ESM_WRITE_TAF_MSG_HEAD(pstMsg, ulApptMsgID, usOrigId, usTermId, ulSn)\
                    (pstMsg)->ulMsgId = (ulApptMsgID);\
                    (pstMsg)->ulSenderCpuId = VOS_LOCAL_CPUID;\
                    (pstMsg)->ulSenderPid = PS_PID_ESM;\
                    (pstMsg)->ulReceiverCpuId = VOS_LOCAL_CPUID;\
                    (pstMsg)->ulReceiverPid = WUEPS_PID_TAF;\
                    (pstMsg)->usOriginalId = (usOrigId);\
                    (pstMsg)->usTerminalId = (usTermId);\
                    (pstMsg)->ulSN         = (ulSn);

#define NAS_ESM_WRITE_APP_DT_CNF_MSG_HEAD(pstMsg, ulApptMsgID, usOrigId, usTermId, ulSn)\
                    (pstMsg)->ulMsgId = (ulApptMsgID);\
                    (pstMsg)->ulSenderCpuId = VOS_LOCAL_CPUID;\
                    (pstMsg)->ulSenderPid = PS_PID_ESM;\
                    (pstMsg)->ulReceiverCpuId = VOS_LOCAL_CPUID;\
                    (pstMsg)->ulReceiverPid = L3_MSP_PID_DT;\
                    (pstMsg)->usOriginalId = (usOrigId);\
                    (pstMsg)->usTerminalId = (usTermId);\
                    (pstMsg)->ulSN         = (ulSn);

#define NAS_ESM_WRITE_APP_DT_IND_MSG_HEAD(pstMsg, ulApptMsgID, usOrigId, usTermId, ulSn)\
                    (pstMsg)->ulMsgId = (ulApptMsgID);\
                    (pstMsg)->ulSenderCpuId = VOS_LOCAL_CPUID;\
                    (pstMsg)->ulSenderPid = PS_PID_ESM;\
                    (pstMsg)->ulReceiverCpuId = VOS_LOCAL_CPUID;\
                    (pstMsg)->ulReceiverPid = L3_MSP_PID_DT_IND;\
                    (pstMsg)->usOriginalId = (usOrigId);\
                    (pstMsg)->usTerminalId = (usTermId);\
                    (pstMsg)->ulSN         = (ulSn);


/*封装写EMM消息头的宏*/
#define NAS_ESM_WRITE_EMM_MSG_HEAD(pstMsg, ulEmmMsgID)\
                    (pstMsg)->ulMsgId   = (ulEmmMsgID);\
                    (pstMsg)->ulSenderCpuId = VOS_LOCAL_CPUID;\
                    (pstMsg)->ulSenderPid = PS_PID_ESM;\
                    (pstMsg)->ulReceiverCpuId = VOS_LOCAL_CPUID;\
                    (pstMsg)->ulReceiverPid = PS_PID_MM;

/*封装写RABM消息头的宏*/
#define NAS_ESM_WRITE_RABM_MSG_HEAD(pstMsg, ulRabmMsgID)\
                    (pstMsg)->ulMsgId   = (ulRabmMsgID);\
                    (pstMsg)->ulSenderCpuId = VOS_LOCAL_CPUID;\
                    (pstMsg)->ulSenderPid = PS_PID_ESM;\
                    (pstMsg)->ulReceiverCpuId = VOS_LOCAL_CPUID;\
                    (pstMsg)->ulReceiverPid = PS_PID_RABM;

/*封装写SM消息头的宏*/
#define NAS_ESM_WRITE_SM_MSG_HEAD(pstMsg, ulSmMsgID)\
                    (pstMsg)->ulMsgId   = (ulSmMsgID);\
                    (pstMsg)->ulSenderCpuId = VOS_LOCAL_CPUID;\
                    (pstMsg)->ulSenderPid = PS_PID_ESM;\
                    (pstMsg)->ulReceiverCpuId = VOS_LOCAL_CPUID;\
                    (pstMsg)->ulReceiverPid = WUEPS_PID_TAF;

#if (FEATURE_ON == FEATURE_UE_MODE_CDMA)
/*封装写EHSM消息头的宏*/
#define NAS_ESM_WRITE_EHSM_MSG_HEAD(pstMsg, ulEhsmMsgID)\
                    (pstMsg)->enMsgId         = (ulEhsmMsgID);\
                    (pstMsg)->ulSenderCpuId   = VOS_LOCAL_CPUID;\
                    (pstMsg)->ulSenderPid     = PS_PID_ESM;\
                    (pstMsg)->ulReceiverCpuId = VOS_LOCAL_CPUID;\
                    (pstMsg)->ulReceiverPid   = UEPS_PID_EHSM;
#endif

/*封装写IP消息头的宏*/
#define NAS_ESM_WRITE_IP_MSG_HEAD(pstMsg, ulIpMsgID)\
                    (pstMsg)->ulMsgId   = (ulIpMsgID);\
                    (pstMsg)->ulSenderCpuId = VOS_LOCAL_CPUID;\
                    (pstMsg)->ulSenderPid = PS_PID_ESM;\
                    (pstMsg)->ulReceiverCpuId = VOS_LOCAL_CPUID;\
                    (pstMsg)->ulReceiverPid = PS_PID_IP;

/*封装写USIM消息头的宏*/
/*USIM的消息头都被统一封装在了MsgHeader中*/
#define NAS_ESM_WRITE_USIM_MSG_HEAD(pstMsg, ulMsgID, enApptype, ulSendpara)\
                    (pstMsg)->stMsgHeader.enMsgName   = (ulMsgID);\
                    (pstMsg)->stMsgHeader.ulSenderCpuId = VOS_LOCAL_CPUID;\
                    (pstMsg)->stMsgHeader.ulSenderPid = PS_PID_ESM;\
                    (pstMsg)->stMsgHeader.ulReceiverCpuId = VOS_LOCAL_CPUID;\
                    (pstMsg)->stMsgHeader.enAppType = (enApptype);\
                    (pstMsg)->stMsgHeader.ulSendPara = (ulSendpara);\
                    (pstMsg)->stMsgHeader.ulReceiverPid = WUEPS_PID_USIM;


/* 内存拷贝宏定义 */

#if (VOS_OS_VER == VOS_WIN32)

#define NAS_ESM_MEM_CPY_S(pucDestBuffer, ulMaxDest, pucSrcBuffer, ulBufferLen) \
	NAS_LMM_SecuMemCpy((pucDestBuffer), (ulMaxDest), (pucSrcBuffer), (ulBufferLen), (__LINE__), (THIS_FILE_ID))

#define NAS_ESM_MEM_SET_S(pucBuffer, ulMaxDest, ucData, ulBufferLen) \
	NAS_LMM_SecuMemSet((pucBuffer), (ulMaxDest), (ucData), (ulBufferLen), (__LINE__), (THIS_FILE_ID))

#define NAS_ESM_MEM_MOVE_S(pucDestBuffer, ulMaxDest, pucSrcBuffer, ulBufferLen) \
	NAS_LMM_SecuMemMove( (pucDestBuffer), (ulMaxDest), (pucSrcBuffer), (ulBufferLen), (__LINE__), (THIS_FILE_ID))

#else
#define NAS_ESM_MEM_CPY_S(pucDestBuffer, ulMaxDest, pucSrcBuffer, ulBufferLen) \
        (VOS_VOID)NAS_ESM_SecuMemCpy((pucDestBuffer), (ulMaxDest), (pucSrcBuffer), (ulBufferLen), (__LINE__), (THIS_FILE_ID))

#define NAS_ESM_MEM_SET_S(pucBuffer, ulMaxDest, ucData, ulBufferLen) \
        (VOS_VOID)TLPS_MEM_SET_S((pucBuffer), (ulMaxDest), (ucData), (ulBufferLen), (__LINE__), (THIS_FILE_ID))

#define NAS_ESM_MEM_MOVE_S(pucDestBuffer, ulMaxDest, pucSrcBuffer, ulBufferLen) \
        (VOS_VOID)TLPS_MEM_MOVE_S( (pucDestBuffer), (ulMaxDest), (pucSrcBuffer), (ulBufferLen), (__LINE__), (THIS_FILE_ID))

#endif



#define NAS_ESM_MEM_CMP(pucDestBuffer, pucSrcBuffer, ulBufferLen)\
            PS_MEM_CMP ((pucDestBuffer), (pucSrcBuffer), (ulBufferLen))

#define NAS_ESM_ALLOC_MSG(ulLen) \
            PS_ALLOC_MSG_ALL_CHECK((PS_PID_ESM) , (ulLen))

#if (VOS_OS_VER != VOS_WIN32)
/* 发送消息 */
#define NAS_ESM_SND_MSG(pMsg)\
    {\
        NAS_ESM_PrintEsmSendMsg((const PS_MSG_HEADER_STRU *)pMsg,NAS_COMM_GET_ESM_PRINT_BUF());\
        if(VOS_OK != PS_SND_MSG_ALL_CHECK((PS_PID_ESM) , (pMsg)))\
            {\
                NAS_ESM_ERR_LOG("NAS_ESM_SND_MSG:Msg Snd Err!");\
            }\
    }
#else
#define NAS_ESM_SND_MSG(pMsg)\
    {\
        NAS_ESM_PrintEsmSendMsg((const PS_MSG_HEADER_STRU *)pMsg,NAS_COMM_GET_ESM_PRINT_BUF());\
        PS_SND_MSG_ALL_CHECK((PS_PID_ESM) , (pMsg));\
    }
#endif

#if (VOS_OS_VER != VOS_WIN32)
/*内存释放*/
#define NAS_ESM_MEM_FREE(pAddr)\
    {\
        if(VOS_OK != PS_MEM_FREE_ALL_CHECK((PS_PID_ESM), (pAddr)))\
        {\
            NAS_ESM_ERR_LOG("NAS_ESM_MEM_FREE  ERR!!");\
        }\
    }
#else
#define NAS_ESM_MEM_FREE(pAddr)     PS_MEM_FREE_ALL_CHECK((PS_PID_ESM), (pAddr));
#endif

/*内存动态分配*/
#define NAS_ESM_MEM_ALLOC(ulSize)\
            PS_MEM_ALLOC_All_CHECK((PS_PID_ESM) , (ulSize))

#if (VOS_OS_VER != VOS_WIN32)
#define NAS_ESM_PRINT_BEARCNTXTSTA(BearerCntxtState)\
            switch (BearerCntxtState)\
            {\
                case    NAS_ESM_BEARER_STATE_INACTIVE   :\
                    NAS_ESM_NORM_LOG("State :  BEARER_CONTEXT_INACTIVE");\
                    break;\
                case    NAS_ESM_BEARER_STATE_ACTIVE:\
                    NAS_ESM_NORM_LOG("State :  BEARER_CONTEXT_ACTIVE ");\
                    break;\
                case    NAS_ESM_BEARER_STATE_BUTT:\
                default   :\
                    NAS_ESM_NORM_LOG("State :  SM UKNOWN BEARER_CONTEXT_STATE");\
                    break;\
            }
#else
#define NAS_ESM_PRINT_BEARCNTXTSTA(BearerCntxtState)  NAS_ESM_LOG1("State: BEARER_CONTEXT_STATE is", BearerCntxtState)
#endif


#define NAS_ESM_PRINT_PROCTRANSSTA(ProcTransState)\
            switch (ProcTransState)\
            {\
                case    NAS_ESM_BEARER_PROC_TRANS_STATE_INACTIVE   :\
                    NAS_ESM_NORM_LOG("State :  PROCEDURE_TRANSACTION_INACTIVE");\
                    break;\
                case    NAS_ESM_BEARER_PROC_TRANS_STATE_PENDING:\
                    NAS_ESM_NORM_LOG("State :  PROCEDURE_TRANSACTION_PENDING ");\
                    break;\
                case    NAS_ESM_BEARER_PROC_TRANS_STATE_BUTT:\
                default   :\
                    NAS_ESM_NORM_LOG("State :  SM UKNOWN PROCEDURE_TRANSACTION_STATE");\
                    break;\
            }

#define NAS_ESM_PRINT_EMMSTA(EmmStatus)\
            switch (EmmStatus)\
            {\
                case    NAS_ESM_PS_REGISTER_STATUS_DETACHED   :\
                    NAS_ESM_NORM_LOG("EMM_DETACHED");\
                    break;\
                case    NAS_ESM_PS_REGISTER_STATUS_ATTACHING:\
                    NAS_ESM_NORM_LOG("EMM_ATTACHING");\
                    break;\
                case    NAS_ESM_PS_REGISTER_STATUS_ATTACHED:\
                    NAS_ESM_NORM_LOG("EMM_ATTACHED");\
                    break;\
                case    NAS_ESM_PS_REGISTER_STATUS_BUTT:\
                default   :\
                    NAS_ESM_NORM_LOG("UKNOWN EMM REGISTER STATUS");\
                    break;\
            }

#define NAS_ESM_PRINT_LMODESTA(LModeStatus)\
            switch (LModeStatus)\
            {\
                case    NAS_ESM_L_MODE_STATUS_NORMAL   :\
                    NAS_ESM_NORM_LOG("ESM L_MODE_NORMAL");\
                    break;\
                case    NAS_ESM_L_MODE_STATUS_SUSPENDED:\
                    NAS_ESM_NORM_LOG("ESM L_MODE_SUSPENDED");\
                    break;\
                case    NAS_ESM_L_MODE_STATUS_BUTT:\
                default   :\
                    NAS_ESM_NORM_LOG("ESM UKNOWN L MODE STATUS");\
                    break;\
            }

#define NAS_ESM_IS_IPV4_ADDR_INVALID(IPADDR)\
     ((IPADDR[0] == 0)&&(IPADDR[1] == 0)&&(IPADDR[2] == 0)&&(IPADDR[3] == 0))

#define  NAS_ESM_NO                     0
#define  NAS_ESM_YES                    1
#define  NAS_ESM_EMM_OPID_NOT_VAILID    0xFFFFFFFFL



/*****************************************************************************
  3 Massage Declare
*****************************************************************************/


/*****************************************************************************
  4 Enum
*****************************************************************************/
enum NAS_ESM_ERROR_CODE_ENUM
{
    NAS_ESM_SUCCESS                                         = 0,         /*ESM 模块函数返回成功*/
    NAS_ESM_FAILURE                                            ,         /*ESM 模块函数返回失败*/
    NAS_ESM_MSG_DISCARD                                        ,         /*丢弃消息*/
    NAS_ESM_MSG_HANDLED                                                 /*消息已处理 */
};

enum NAS_ESM_MATCH_RESULT_ENUM
{
    NAS_ESM_MATCH_FAIL                      = 0,
    NAS_ESM_MATCH_SUCCESS                   = 1,
    NAS_ESM_MATCH_PTR_NULL                  = 2,
    NAS_ESM_MATCH_RESULT_BUTT
};
typedef VOS_UINT32  NAS_ESM_MATCH_RESULT_ENUM_UINT32;


/*空口消息类型*/
enum NAS_ESMCN_MSG_TYPE_ENUM
{
    /* 消息名称 */                                         /*消息ID*/   /* 备注 */
    NAS_ESMCN_MSG_TYPE_ACT_DEFLT_EPS_BEARER_CNTXT_REQ       = 0xC1,      /*缺省承载激活请求 1100  0001   Activate default EPS bearer context request  */
    NAS_ESMCN_MSG_TYPE_ACT_DEFLT_EPS_BEARER_CNTXT_ACC       = 0xC2,      /*缺省承载激活接受 1100  0010   Activate default EPS bearer context accept  */
    NAS_ESMCN_MSG_TYPE_ACT_DEFLT_EPS_BEARER_CNTXT_REJ       = 0xC3,      /*缺省承载激活拒绝 1100  0011   Activate default EPS bearer context reject  */

    NAS_ESMCN_MSG_TYPE_ACT_DEDICTD_EPS_BEARER_CNTXT_REQ     = 0xC5,      /*专有承载激活请求 1100  0101   Activate dedicated EPS bearer context request  */
    NAS_ESMCN_MSG_TYPE_ACT_DEDICTD_EPS_BEARER_CNTXT_ACC     = 0xC6,      /*专有承载激活接受 1100  0110   Activate dedicated EPS bearer context accept  */
    NAS_ESMCN_MSG_TYPE_ACT_DEDICTD_EPS_BEARER_CNTXT_REJ     = 0xC7,      /*专有承载激活拒绝 1100  0111   Activate dedicated EPS bearer context reject  */

    NAS_ESMCN_MSG_TYPE_MOD_EPS_BEARER_CNTXT_REQ             = 0xC9,      /*承载修改请求 1100  1001   Modify EPS bearer context request  */
    NAS_ESMCN_MSG_TYPE_MOD_EPS_BEARER_CNTXT_ACC             = 0xCA,      /*承载修改接受 1100  1010   Modify EPS bearer context accept  */
    NAS_ESMCN_MSG_TYPE_MOD_EPS_BEARER_CNTXT_REJ             = 0xCB,      /*承载修改拒绝 1100  1011   Modify EPS bearer context reject  */

    NAS_ESMCN_MSG_TYPE_DEACT_EPS_BEARER_CNTXT_REQ           = 0xCD,      /*承载去激活请求 1100  1101   Deactivate EPS bearer context request  */
    NAS_ESMCN_MSG_TYPE_DEACT_EPS_BEARER_CNTXT_ACC           = 0xCE,      /*承载去激活接受 1100  1110   Deactivate EPS bearer context accept  */

    NAS_ESMCN_MSG_TYPE_PDN_CONNECT_REQ                      = 0xD0,      /*PDN连接请求 1101  0000   PDN connectivity request  */
    NAS_ESMCN_MSG_TYPE_PDN_CONNECT_REJ                      = 0xD1,      /*PDN连接拒绝 1101  0001   PDN connectivity reject  */

    NAS_ESMCN_MSG_TYPE_PDN_DISCONNECT_REQ                   = 0xD2,      /*PDN去连接请求 1101  0010   PDN disconnect request  */
    NAS_ESMCN_MSG_TYPE_PDN_DISCONNECT_REJ                   = 0xD3,      /*PDN去连接拒绝 1101  0011   PDN disconnect reject  */

    NAS_ESMCN_MSG_TYPE_BEARER_RES_ALLOC_REQ                 = 0xD4,      /*资源分配请求 1101  0100   Bearer resource allocation request  */
    NAS_ESMCN_MSG_TYPE_BEARER_RES_ALLOC_REJ                 = 0xD5,      /*资源分配拒绝 1101  0101   Bearer resource allocation reject  */
    NAS_ESMCN_MSG_TYPE_BEARER_RES_MOD_REQ                   = 0xD6,      /*资源修改请求 1101  0110   Bearer resource modification request  */
    NAS_ESMCN_MSG_TYPE_BEARER_RES_MOD_REJ                   = 0xD7,      /*资源修改拒绝 1101  0111   Bearer resource modification reject  */

    NAS_ESMCN_MSG_TYPE_ESM_INFORMATION_REQ                  = 0xD9,
    NAS_ESMCN_MSG_TYPE_ESM_INFORMATION_RSP                  = 0xDA,

    NAS_ESMCN_MSG_TYPE_ESM_STATUS                           = 0xE8,
    NAS_ESMCN_MSG_TYPE_ESM_NOTIFICATION                     = 0xDB,

    NAS_ESMCN_MSG_TYPE_BUTT
};
typedef VOS_UINT8    NAS_ESMCN_MSG_TYPE_ENUM_UINT8;

enum NAS_ESM_CAUSE_ENUM
{
    NAS_ESM_CAUSE_SUCCESS                                   = 0,/*UE自定义*/
    NAS_ESM_CAUSE_ERROR                                     = 1,/*UE自定义*/

    NAS_ESM_CAUSE_OPERATOR_DETERMINE_BARRING                = 8,
    NAS_ESM_CAUSE_INSUFFICIENT_RESOURCES                    = 26,/*UE可能发出的*/
    NAS_ESM_CAUSE_UNKNOWN_OR_MISSING_APN                    = 27,
    NAS_ESM_CAUSE_UNKNOWN_PDN_TYPE                          = 28,
    NAS_ESM_CAUSE_USER_AUTH_FAIL                            = 29,
    NAS_ESM_CAUSE_REQ_REJ_BY_SGW_OR_PGW                     = 30,
    NAS_ESM_CAUSE_REQ_REJ_UNSPECITY                         = 31,/*UE可能发出的*/
    NAS_ESM_CAUSE_SERVICE_OPTION_NOT_SUPPORT                = 32,
    NAS_ESM_CAUSE_REQ_SERVICE_NOT_SUBSCRIBED                = 33,
    NAS_ESM_CAUSE_SERVICE_OPTION_TEMP_OUT_ORDER             = 34,
    NAS_ESM_CAUSE_PTI_ALREADY_IN_USED                       = 35,
    NAS_ESM_CAUSE_REGULAR_DEACTIVATION                      = 36,
    NAS_ESM_CAUSE_EPS_QOS_NOT_ACCEPT                        = 37,
    NAS_ESM_CAUSE_NETWORK_FAILURE                           = 38,
    NAS_ESM_CAUSE_FEATURE_NOT_SUPPORTED                     = 40,
    NAS_ESM_CAUSE_SEMANTIC_ERR_IN_TFT                       = 41,/*UE可能发出的*/
    NAS_ESM_CAUSE_SYNTACTIC_ERR_IN_TFT                      = 42,/*UE可能发出的*/
    NAS_ESM_CAUSE_INVALID_EPS_BEARER_IDENTITY               = 43,
    NAS_ESM_CAUSE_SEMANTIC_ERR_IN_PACKET_FILTER             = 44,/*UE可能发出的*/
    NAS_ESM_CAUSE_SYNCTACTIC_ERR_IN_PACKET_FILTER           = 45,/*UE可能发出的*/
    NAS_ESM_CAUSE_BEARER_WITHOUT_TFT_ACT                    = 46,/*UE可能发出的*/
    NAS_ESM_CAUSE_PTI_MISMATCH                              = 47,
    NAS_ESM_CAUSE_LAST_PDN_DISCONN_NOT_ALLOWED              = 49,
    NAS_ESM_CAUSE_PDNTYPE_IPV4_ONLY_ALLOWED                 = 50,
    NAS_ESM_CAUSE_PDNTYPE_IPV6_ONLY_ALLOWED                 = 51,
    NAS_ESM_CAUSE_SINGLE_ADDR_BEARER_ONLY_ALLOWED           = 52,
    NAS_ESM_CAUSE_ESM_INFORMATION_NOT_RECEIVED              = 53,
    NAS_ESM_CAUSE_PDN_CONNECTION_DOES_NOT_EXIST             = 54,
    NAS_ESM_CAUSE_SAME_APN_MULTI_PDN_CONNECTION_NOT_ALLOWED = 55,
    NAS_ESM_CAUSE_COLLISION_WITH_NETWORK_INITIATED_REQUEST  = 56,
    NAS_ESM_CAUSE_UNSUPPORTED_QCI_VALUE                     = 59,
    NAS_ESM_CAUSE_APN_NOT_SUPPORT_IN_CURRENT_RAT_AND_PLMN   = 66,
    NAS_ESM_CAUSE_INVALID_PTI_VALUE                         = 81,
    NAS_ESM_CAUSE_SEMANTICALLY_INCORRECT_MESSAGE            = 95,
    NAS_ESM_CAUSE_INVALID_MANDATORY_INFORMATION             = 96,
    NAS_ESM_CAUSE_MESSAGE_TYPE_NON_EXIST_OR_NOT_IMPLEMENTED = 97,
    NAS_ESM_CAUSE_MESSAGE_TYPE_NOT_COMPATIBLE_WITH_PROT_STA = 98,
    NAS_ESM_CAUSE_INFO_ELEMENT_NON_EXIST_OR_NOT_IMPLEMENTED = 99,
    NAS_ESM_CAUSE_CONDITIONAL_IE_ERROR                      = 100,
    NAS_ESM_CAUSE_MESSAGE_NOT_COMPATIBLE_WITH_PROT_STA      = 101,
    NAS_ESM_CAUSE_PROTOCOL_ERROR                            = 111,

    NAS_ESM_CAUSE_APN_RESTRICTION_VAL_INCOMPATIBLE_WITH_ACT_BEARER = 112,

    NAS_ESM_CAUSE_MSG_TOO_SHORT                             = 200
};
typedef VOS_UINT8   NAS_ESM_CAUSE_ENUM_UINT8;

enum    NAS_ESM_PDN_REQ_TYPE_ENUM
{
    NAS_ESM_PDN_REQ_TYPE_INITIAL     = 0x00,
    NAS_ESM_PDN_REQ_TYPE_HANDOVER    = 0x01,
    NAS_ESM_PDN_REQ_TYPE_BUTT
};
typedef VOS_UINT8   NAS_ESM_PDN_REQ_TYPE_ENUM_UINT8;

enum NAS_ESM_BEARER_TYPE_ENUM
{
    NAS_ESM_BEARER_TYPE_DEFAULT = 0,                /*缺省承载*/
    NAS_ESM_BEARER_TYPE_DEDICATED,                  /*专有承载*/
    NAS_ESM_BEARER_TYPE_EMERGENCY,                  /*紧急承载*/

    NAS_ESM_BEARER_TYPE_BUTT
};/*承载的属性*/
typedef VOS_UINT8  NAS_ESM_BEARER_TYPE_ENUM_UINT8;


enum NAS_ESM_BEARER_STATE_ENUM
{
    NAS_ESM_BEARER_STATE_INACTIVE  = 0,             /*上下文去激活态*/
    NAS_ESM_BEARER_STATE_ACTIVE,                    /*上下文激活状态*/

    NAS_ESM_BEARER_STATE_BUTT
};/*ESM 承载的状态*/
typedef VOS_UINT8  NAS_ESM_BEARER_STATE_ENUM_UINT8;

enum NAS_ESM_BEARER_PROC_TRANS_STATE_ENUM
{
    NAS_ESM_BEARER_PROC_TRANS_STATE_INACTIVE = 0,           /*PROCEDURE_TRANSACTION_INACTIVE*/
    NAS_ESM_BEARER_PROC_TRANS_STATE_PENDING,                /*PROCEDURE_TRANSACTION_PENDING，等待网络回复*/

    NAS_ESM_BEARER_PROC_TRANS_STATE_BUTT
};/*ESM  PROCEDURE_TRANSACTION状态*/
typedef VOS_UINT8  NAS_ESM_PROC_TRANS_STATE_ENUM_UINT8;

enum NAS_ESM_TIMER_PARA_ENUM
{
    TI_NAS_ESM_T3482 = 0,
    TI_NAS_ESM_T3492,
    TI_NAS_ESM_T3480,
    TI_NAS_ESM_T3481,

    TI_NAS_ESM_WAIT_APP_CNF,                                /*等待APP回复定时器*/

    TI_NAS_ESM_WAIT_PTI_INVALID,                            /*等待PTI失效*/
    TI_NAS_ESM_ATTACH_BEARER_REEST,                         /* Timer for Attach Bearer Reest*/
    TI_NAS_ESM_REL_NON_EMC_BEARER,                          /* Timer for defer release non-emergency PDN*/

    TI_NAS_ESM_BACKOFF_WAIT_USIM_CNF,
    TI_NAS_ESM_BACKOFF_IGNORE_FORBID,
    TI_NAS_ESM_BACKOFF_PERM_REJ_FORBID,
    TI_NAS_ESM_BACKOFF_TEMP_REJ_FORBID,

    TI_NAS_ESM_WAIT_EHRPD_PDN_RECONN_SUCC,

    TI_NAS_ESM_TIMER_PARA_BUTT
};/*ESM 定时器名，用于设置定时器时的para字段*/
typedef VOS_UINT8 NAS_ESM_TIMER_PARA_ENUM_UINT8;
enum NAS_ESM_OM_LOG_MSG_ENUM
{
    NAS_ESM_OM_LOG_TIMER_MIN               = PS_MSG_ID_ESM_TO_ESM_OM_BASE,

    NAS_ESM_OM_LOG_TIMER_MAX               = PS_MSG_ID_ESM_TO_ESM_OM_BASE + 0x10,  /* 一共32条，留给定时器16条 */

    NAS_ESM_OM_LOG_BACKOFF_INIT            = NAS_ESM_OM_LOG_TIMER_MAX + 0x01,
    NAS_ESM_OM_LOG_BACKOFF_JUDGMENT        = NAS_ESM_OM_LOG_TIMER_MAX + 0x02,
    NAS_ESM_OM_LOG_BACKOFF_MAINTAIN        = NAS_ESM_OM_LOG_TIMER_MAX + 0x03,
    NAS_ESM_OM_LOG_BACKOFF_RESET           = NAS_ESM_OM_LOG_TIMER_MAX + 0x04,

    NAS_ESM_OM_LOG_BACKOFF_NV_PARA         = NAS_ESM_OM_LOG_TIMER_MAX + 0x05,
    NAS_ESM_OM_LOG_BACKOFF_COMM_INFO       = NAS_ESM_OM_LOG_TIMER_MAX + 0x06,
    NAS_ESM_OM_LOG_BACKOFF_APN_ENTITY_LIST = NAS_ESM_OM_LOG_TIMER_MAX + 0x07,

    NAS_ESM_OM_LOG_EHRPD_PDN_ENTITY_NUM    = NAS_ESM_OM_LOG_TIMER_MAX + 0x08,
    NAS_ESM_OM_LOG_EHRPD_PDN_ENTITY_INFO   = NAS_ESM_OM_LOG_TIMER_MAX + 0x09,
    NAS_ESM_OM_LOG_REG_CID_INFO            = NAS_ESM_OM_LOG_TIMER_MAX + 0x0a

};

enum NAS_ESM_PS_REGISTER_STATUS_ENUM
{
    NAS_ESM_PS_REGISTER_STATUS_DETACHED = 0,                /*非注册*/
    NAS_ESM_PS_REGISTER_STATUS_ATTACHING,                   /*注册中*/
    NAS_ESM_PS_REGISTER_STATUS_ATTACHED,                    /*已注册*/

    NAS_ESM_PS_REGISTER_STATUS_BUTT
};/*EMM的注册状态*/
typedef VOS_UINT8 NAS_ESM_PS_REGISTER_STATUS_ENUM_UINT8;

enum NAS_ESM_L_MODE_STATUS_ENUM
{
    NAS_ESM_L_MODE_STATUS_NORMAL        = 0,                /*正常态*/
    NAS_ESM_L_MODE_STATUS_SUSPENDED     = 1,                /*挂起态*/

    NAS_ESM_L_MODE_STATUS_BUTT
};/* L模状态 */

typedef VOS_UINT8 NAS_ESM_L_MODE_STATUS_ENUM_UINT8;

enum NAS_ESM_BEARER_MANAGE_TYPE_ENUM
{
    NAS_ESM_BEARER_MANAGE_TYPE_ACCEPT = 0,                  /*接受*/
    NAS_ESM_BEARER_MANAGE_TYPE_REJ,                         /*拒绝*/

    NAS_ESM_BEARER_MANANGE_TYPE_BUTT
}; /*标识承载管理类型*/
typedef VOS_UINT8  NAS_ESM_BEARER_MANAGE_TYPE_ENUM_UINT8;

enum NAS_ESM_BEARER_MANAGE_MODE_ENUM
{
    NAS_ESM_BEARER_MANAGE_MODE_AUTO = 0,                    /*自动*/
    NAS_ESM_BEARER_MANAGE_MODE_MANUAL,                      /*手动*/

    NAS_ESM_BEARER_MANAGE_MODE_BUTT
}; /*标识承载管理模式*/
typedef VOS_UINT8  NAS_ESM_BEARER_MANAGE_MODE_ENUM_UINT8;

enum NAS_ESM_BEARER_PROC_STATE_ENUM
{
    NAS_ESM_BEARER_PROC_STATE_ALLOW = 0,                    /*允许*/
    NAS_ESM_BEARER_PROC_STATE_FORBID,                       /*禁止*/

    NAS_ESM_BEARER_PROC_STATE_BUTT
}; /*标识承载当前是否可处理*/
typedef VOS_UINT8  NAS_ESM_BEARER_PROC_STATE_ENUM_UINT8;


/* tad操作枚举 */
enum NAS_ESM_TFT_OP_TYPE_ENUM
{
    NAS_ESM_TFT_OP_TYPE_CREATE_TFT      = 0x01 ,
    NAS_ESM_TFT_OP_TYPE_DELETE_TFT      = 0x02,
    NAS_ESM_TFT_OP_TYPE_ADD_FILTER      = 0x03,
    NAS_ESM_TFT_OP_TYPE_REPLACE_FILTER  = 0x04,
    NAS_ESM_TFT_OP_TYPE_DELETE_FILTER   = 0x05,
    NAS_ESM_TFT_OP_TYPE_NO_OP           = 0x06,
    NAS_ESM_TFT_OP_TYPE_BUTT
};
typedef VOS_UINT8  NAS_ESM_TFT_OP_TYPE_ENUM_UINT8;

/* QOS偏移枚举 */
enum NAS_ESM_QOS_OFFSET_ENUM
{
    NAS_ESM_QOS_OFFSET_QCI              = 0x0 ,
    NAS_ESM_QOS_OFFSET_ULMAXRATE        = 0x01,
    NAS_ESM_QOS_OFFSET_DLMAXRATE        = 0x02,
    NAS_ESM_QOS_OFFSET_ULGMAXRATE       = 0x03,
    NAS_ESM_QOS_OFFSET_DLGMAXRATE       = 0x04,
    NAS_ESM_QOS_OFFSET_ULMAXRATE_EXT    = 0x05,
    NAS_ESM_QOS_OFFSET_DLMAXRATE_EXT    = 0x06,
    NAS_ESM_QOS_OFFSET_ULGMAXRATE_EXT   = 0x07,
    NAS_ESM_QOS_OFFSET_DLGMAXRATE_EXT   = 0x08,
    NAS_ESM_QOS_OFFSET_ULMAXRATE_EXT_2  = 0x09,
    NAS_ESM_QOS_OFFSET_DLMAXRATE_EXT_2  = 0x0A,
    NAS_ESM_QOS_OFFSET_ULGMAXRATE_EXT_2 = 0x0B,
    NAS_ESM_QOS_OFFSET_DLGMAXRATE_EXT_2 = 0x0C,

    NAS_ESM_QOS_OFFSET_BUTT
};
typedef VOS_UINT8  NAS_ESM_QOS_OFFSET_ENUM_UINT8;


/* QOS速率枚举 */
enum NAS_ESM_QOS_RATE_ENUM
{
    NAS_ESM_QOS_RATE_64KB               = 64,
    NAS_ESM_QOS_RATE_568KB              = 568 ,
    NAS_ESM_QOS_RATE_576KB              = 576 ,
    NAS_ESM_QOS_RATE_8600KB             = 8600,
    NAS_ESM_QOS_RATE_8640KB             = 8640,
    NAS_ESM_QOS_RATE_8700KB             = 8700,
    NAS_ESM_QOS_RATE_16000KB            = 16000,
    NAS_ESM_QOS_RATE_16MB               = 16*1000,
    NAS_ESM_QOS_RATE_17MB               = 17*1000,
    NAS_ESM_QOS_RATE_128MB              = 128*1000,
    NAS_ESM_QOS_RATE_130MB              = 130*1000,
    NAS_ESM_QOS_RATE_256MB              = 256*1000,
    NAS_ESM_QOS_RATE_260MB              = 260*1000,
    NAS_ESM_QOS_RATE_500MB              = 500*1000,
    NAS_ESM_QOS_RATE_510MB              = 510*1000,
    NAS_ESM_QOS_RATE_1500MB             = 1500*1000,
    NAS_ESM_QOS_RATE_1600MB             = 1600*1000,
    NAS_ESM_QOS_RATE_10GB               = 10000*1000,

    NNAS_ESM_QOS_RATE_BUTT
};
typedef VOS_UINT8  NAS_ESM_QOS_RATE_ENUM_UINT8;

/* QOS速率间隔枚举 */
enum NAS_ESM_QOS_RATE_GRANULARITY_ENUM
{
    NAS_ESM_QOS_RATE_GRANULARITY_8KB    = 8,
    NAS_ESM_QOS_RATE_GRANULARITY_64KB   = 64 ,
    NAS_ESM_QOS_RATE_GRANULARITY_100KB  = 100,
    NAS_ESM_QOS_RATE_GRANULARITY_1MB    = 1000,
    NAS_ESM_QOS_RATE_GRANULARITY_2MB    = 2*1000,
    NAS_ESM_QOS_RATE_GRANULARITY_4MB    = 4*1000,
    NAS_ESM_QOS_RATE_GRANULARITY_10MB   = 10*1000,
    NAS_ESM_QOS_RATE_GRANULARITY_100MB  = 100*1000,

    NAS_ESM_QOS_RATE_GRANULARITY_BUTT
};
typedef VOS_UINT8  NAS_ESM_QOS_RATE_GRANULARITY_ENUM_UINT8;

/* QOS速率区间枚举 */
enum NAS_ESM_QOS_RATE_RANGE_ENUM
{
    NAS_ESM_QOS_RATE_RANGE_568KB_GRANULARITY_8KB            = 0x7F,
    NAS_ESM_QOS_RATE_RANGE_8640KB_GRANULARITY_64KB          = 0xFE ,
    NAS_ESM_QOS_RATE_RANGE_16000KB_GRANULARITY_64KB         = 0x4A,
    NAS_ESM_QOS_RATE_RANGE_128MB_GRANULARITY_1MB            = 0xBA,
    NAS_ESM_QOS_RATE_RANGE_256MB_GRANULARITY_2MB            = 0xFA,
    NAS_ESM_QOS_RATE_RANGE_500MB_GRANULARITY_4MB            = 0x3D,
    NAS_ESM_QOS_RATE_RANGE_1500MB_GRANULARITY_10MB          = 0xA1,
    NAS_ESM_QOS_RATE_RANGE_10GB_GRANULARITY_100MB           = 0XF6,

    NAS_ESM_QOS_RATE_RANGE_BUTT
};
typedef VOS_UINT8  NAS_ESM_QOS_RATE_RANGE_UINT8;

/* 查找CID结果枚举 */
enum NAS_ESM_QUERY_CID_RSLT_ENUM
{
    NAS_ESM_QUERY_CID_RSLT_ALL_FOUND_EQUAL_CID         = 0x01,
    NAS_ESM_QUERY_CID_RSLT_ALL_FOUND_UNEQUAL_CID       = 0x02 ,
    NAS_ESM_QUERY_CID_RSLT_PART_FOUND_EQUAL_CID        = 0x03,
    NAS_ESM_QUERY_CID_RSLT_PART_FOUND_UNEQUAL_CID      = 0x04,
    NAS_ESM_QUERY_CID_RSLT_ALL_UNFOUND                 = 0x05,

    NAS_ESM_QUERY_CID_RSLT_BUTT
};
typedef VOS_UINT8  NAS_ESM_QUERY_CID_RSLT_ENUM_UINT8;

/* APN AMBR偏移枚举 */
enum NAS_ESM_APN_AMBR_OFFSET_ENUM
{
    NAS_ESM_APN_AMBR_OFFSET_DLRATE        = 0x00,
    NAS_ESM_APN_AMBR_OFFSET_ULRATE        = 0x01,
    NAS_ESM_APN_AMBR_OFFSET_DLEXT1        = 0x02,
    NAS_ESM_APN_AMBR_OFFSET_ULEXT1        = 0x03,
    NAS_ESM_APN_AMBR_OFFSET_DLEXT2        = 0x04,
    NAS_ESM_APN_AMBR_OFFSET_ULEXT2        = 0x05,

    NAS_ESM_APN_AMBR_OFFSET_BUTT
};
typedef VOS_UINT8  NAS_ESM_APN_AMBR_OFFSET_ENUM_UINT8;

/* ESM OPID类型 */
enum NAS_ESM_OPID_TYPE_ENUM
{
    NAS_ESM_OPID_TYPE_SETUP_IND         = DIAG_CMD_ESM_PDP_SETUP_IND,
    NAS_ESM_OPID_TYPE_MODIFY_IND        = DIAG_CMD_ESM_PDP_MODIFY_IND,
    NAS_ESM_OPID_TYPE_RELEASE_IND       = DIAG_CMD_ESM_PDP_RELEASE_IND,
    NAS_ESM_OPID_TYPE_MANAGER_IND       = DIAG_CMD_ESM_PDP_MANAGER_IND,
    NAS_ESM_OPID_TYPE_BUTT
};
typedef VOS_UINT8  NAS_ESM_OPID_TYPE_ENUM_UINT8;

/* QCI类型 */
enum NAS_ESM_QCI_TYPE_ENUM
{
    NAS_ESM_QCI_TYPE_QCI1_GBR           = 1,
    NAS_ESM_QCI_TYPE_QCI2_GBR           = 2,
    NAS_ESM_QCI_TYPE_QCI3_GBR           = 3,
    NAS_ESM_QCI_TYPE_QCI4_GBR           = 4,
    NAS_ESM_QCI_TYPE_QCI5_NONGBR        = 5,
    NAS_ESM_QCI_TYPE_QCI6_NONGBR        = 6,
    NAS_ESM_QCI_TYPE_QCI7_NONGBR        = 7,
    NAS_ESM_QCI_TYPE_QCI8_NONGBR        = 8,
    NAS_ESM_QCI_TYPE_QCI9_NONGBR        = 9,

    NAS_ESM_QCI_TYPE_BUTT
};
typedef VOS_UINT8  NAS_ESM_QCI_TYPE_ENUM_UINT8;

enum NAS_ESM_BUFF_ITEM_TYPE_ENUM
{
    NAS_ESM_BUFF_ITEM_TYPE_PTI                                 = 0,             /*PTI缓存记录类型*/
    NAS_ESM_BUFF_ITEM_TYPE_ATTACHING                           = 1,             /*ATTACH过程中缓存记录类型*/

    NAS_ESM_BUFF_ITEM_TYPE_BUTT
};
typedef VOS_UINT8  NAS_ESM_BUFF_ITEM_TYPE_ENUM_UINT8;

enum NAS_ESM_FUN_MD5_CTRL_ENUM
{
    NAS_ESM_FUN_MD5_CTRL_OFF        = 0x00 ,
    NAS_ESM_FUN_MD5_CTRL_ON         = 0x01,

    NAS_ESM_FUN_MD5_BUTT
};
typedef VOS_UINT32  NAS_ESM_FUN_MD5_CTRL_ENUM_UINT32;

enum NAS_ESM_EPS_QOS_CHANGE_TYPE_ENUM
{
    NAS_ESM_EPS_QOS_CHANGE_TYPE_CHANGED                     = 0x00 ,
    NAS_ESM_EPS_QOS_CHANGE_TYPE_NO_CHANGE                   = 0x01,

    NAS_ESM_EPS_QOS_CHANGE_TYPE_BUTT
};
typedef VOS_UINT32  NAS_ESM_EPS_QOS_CHANGE_TYPE_ENUM_UINT32;

enum NAS_ESM_APP_IND_TYPE_ENUM
{
    NAS_ESM_APP_IND_TYPE_SETUP                              = 0x01,
    NAS_ESM_APP_IND_TYPE_RELEASE                            = 0x02,
    NAS_ESM_APP_IND_TYPE_MODIFY                             = 0x03,

    NAS_ESM_APP_IND_TYPE_BUTT
};
typedef VOS_UINT32  NAS_ESM_APP_IND_TYPE_ENUM_UINT32;

typedef SM_ESM_BCM_ENUM_UINT8 NAS_ESM_BCM_ENUM_UINT8;

/*****************************************************************************
    枚举名    : NAS_ESM_NW_LOCAL_IP_CAP_ENUM
    枚举说明  : 网侧是否支持LOCAL IP
*****************************************************************************/
enum    NAS_ESM_NW_LOCAL_IP_CAP_ENUM
{
    NAS_ESM_NW_LOCAL_IP_CAP_UNSUPPORT                = 0x00,
    NAS_ESM_NW_LOCAL_IP_CAP_SUPPORT,

    NAS_ESM_NW_LOCAL_IP_CAP_BUTT
};
typedef VOS_UINT32   NAS_ESM_NW_LOCAL_IP_CAP_ENUM_UINT32;

enum NAS_ESM_FUN_CTRL_ENUM
{
    NAS_ESM_FUN_CTRL_OFF              = 0x00 ,
    NAS_ESM_FUN_CTRL_ON               = 0x01,

    NAS_ESM_FUN_CTRL_BUTT
};
typedef VOS_UINT32  NAS_ESM_FUN_CTRL_ENUM_UINT32;



/*****************************************************************************
    枚举名    : NAS_TIMER_RUN_STA_ENUM
    枚举说明  : 定时器的状态:正在运行,停止
*****************************************************************************/
enum    NAS_ESM_TIMER_RUN_STA_ENUM
{
    NAS_ESM_TIMER_RUNNING                = 0x00,
    NAS_ESM_TIMER_STOPED,
    NAS_ESM_TIMER_INVALID,

    NAS_ESM_TIMER_BUTT
};
typedef VOS_UINT32   NAS_ESM_TIMER_RUN_STA_ENUM_UINT32;

enum NAS_ESM_BEARER_DATA_CNF_ENUM
{
     NAS_ESM_BEARER_STATUS_NULL = 0, /*初始状态*/
     NAS_ESM_BEARER_DATA_CNF_SENDING,     /*DATA REQ发送中， 等待LRRC回复*/
     NAS_ESM_BEARER_DATA_CNF_FAIL,
     NAS_ESM_BEARER_DATA_CNF_SUCC,
     NAS_ESM_BEARER_DATA_CNF_BUTT
};
typedef VOS_UINT8   NAS_ESM_BEARER_DATA_CNF_ENUM_UINT8;


/*****************************************************************************
  5 STRUCT
*****************************************************************************/
/* 用于SMPDN地址的结构体*/
typedef APP_ESM_IP_ADDR_STRU NAS_ESM_CONTEXT_IP_ADDR_STRU;

/* SM上下文的TFT结构体 */
typedef APP_ESM_TFT_INFO_STRU NAS_ESM_CONTEXT_TFT_STRU;

/* SM上下文的SDF QOS结构体 */

/*****************************************************************************
 结构名    : NAS_ESM_CONTEXT_LTE_QOS_STRU
 结构说明  : EPS_QOS  参数
*****************************************************************************/
typedef struct
{
    APP_ESM_EPS_QOS_INFO_STRU           stQosInfo;
    VOS_UINT8                           ucNwQCI;
    VOS_UINT8                           aucReserve1[3];     /* 四字节对齐，保留 */
}NAS_ESM_CONTEXT_LTE_QOS_STRU;


/* SM上下文的QOS的结构体 */
typedef APP_ESM_QOS_INFO_STRU NAS_ESM_CONTEXT_QOS_STRU;

/*****************************************************************************
 结构名    : NAS_ESM_CONTEXT_APN_STRU
 结构说明  : APN编码以后结构
*****************************************************************************/
typedef struct
{
    VOS_UINT8                           ucApnLen;
    VOS_UINT8                           ucReserved[3];
    VOS_UINT8                           aucApnName[NAS_ESM_MAX_APN_NUM];
}NAS_ESM_CONTEXT_APN_STRU;


/* SM上下文的APN AMBR的结构体 */
typedef APP_ESM_APN_AMBR_INFO_STRU NAS_ESM_CONTEXT_APN_AMBR_STRU;

/* SM上下文的Transaciotn Id的结构体 */
typedef SM_ESM_TRANSACTION_ID_STRU NAS_ESM_CONTEXT_TRANS_ID_STRU;

typedef struct
{
    VOS_UINT8                           aucIpV4Addr[APP_MAX_IPV4_ADDR_LEN];
}NAS_ESM_IPV4_ADDR_STRU;

typedef struct
{
    VOS_UINT8                           aucIpV6Addr[APP_MAX_IPV6_ADDR_LEN];
}NAS_ESM_IPV6_ADDR_STRU;

/* SM上下文的PCO的结构体 */
/*typedef APP_ESM_PCO_INFO_STRU NAS_ESM_CONTEXT_PCO_STRU;*/
/*****************************************************************************
 结构名    : NAS_ESM_CONTEXT_PCO_STRU
 结构说明  : 译码后的PCO参数
*****************************************************************************/
typedef struct
{
    VOS_UINT32                          bitOpBcm        : 1;
    VOS_UINT32                          bitOpImsCnSignalFlag :1;
    VOS_UINT32                          bitOpNwLocalIpCap :1;
    VOS_UINT32                          bitOpSpare      : 29;

    NAS_ESM_BCM_ENUM_UINT8              enBcm;
    VOS_UINT8                           ucIpv4DnsSerNum;
    VOS_UINT8                           ucIpv4PcscfNum;
    VOS_UINT8                           ucIpv6DnsSerNum;
    VOS_UINT8                           ucIpv6PcscfNum;
    VOS_UINT8                           ucIpv4NbnsNum;
    NAS_ESM_IPV4_ADDR_STRU              astIpv4DnsServer[NAS_ESM_MAX_DNS_SERVER_NUM];
    NAS_ESM_IPV4_ADDR_STRU              astIpv4Pcscf[NAS_ESM_MAX_PCSCF_NUM];
    NAS_ESM_IPV4_ADDR_STRU              astIpv4Nbns[NAS_ESM_MAX_NBNS_NUM];
    NAS_ESM_IPV6_ADDR_STRU              astIpv6DnsServer[NAS_ESM_MAX_DNS_SERVER_NUM];
    NAS_ESM_IPV6_ADDR_STRU              astIpv6Pcscf[NAS_ESM_MAX_PCSCF_NUM];

    APP_ESM_IMS_CN_SIG_FLAG_ENUM_UINT32 enImsCnSignalFlag;

    NAS_ESM_NW_LOCAL_IP_CAP_ENUM_UINT32 enNwLocalIPCap;
}NAS_ESM_CONTEXT_PCO_STRU;

/*****************************************************************************
 结构名    : NAS_ESM_CONTEXT_PCO_STRU
 结构说明  : 转换后的PCO参数
*****************************************************************************/
typedef struct
{
    VOS_UINT32                          bitOpBcm        : 1;
    VOS_UINT32                          bitOpSpare      : 31;

    NAS_ESM_BCM_ENUM_UINT8              enBcm;
    VOS_UINT8                           ucDnsSerNum;
    VOS_UINT8                           ucPcscfNum;
    VOS_UINT8                           ucNbnsNum;
    NAS_ESM_CONTEXT_IP_ADDR_STRU        astDnsServer[NAS_ESM_MAX_DNS_SERVER_NUM];
    NAS_ESM_CONTEXT_IP_ADDR_STRU        astPcscf[NAS_ESM_MAX_PCSCF_NUM];
    NAS_ESM_CONTEXT_IP_ADDR_STRU        astNbns[NAS_ESM_MAX_NBNS_NUM];
}NAS_ESM_PCO_TRANSFORM_STRU;



/*记录APP消息的结构体*/
typedef struct
{
    VOS_UINT32                          ulAppMsgOpId;       /* App发给SM的消息操作标识 */
    VOS_UINT32                          ulEsmMsgOpId;       /* Sm发给App的消息操作标识 */
    VOS_UINT16                          usOriginalId;       /* 源MID */
    VOS_UINT16                          usTerminalId;       /* 目的ID */
    APP_ESM_MSG_TYPE_ENUM_UINT32        enAppMsgType;       /* 消息类型 */
}NAS_ESM_APP_MSG_RECORD_STRU;


/*记录空口消息的结构体*/
typedef struct
{
    VOS_UINT32                          ulOpId;
    VOS_UINT8                           ucIsEmcPdnReq;      /* 标识是否是紧急PDN连接请求 */
    VOS_UINT8                           ucPti;              /* Procedure transaction identifier */
    NAS_ESMCN_MSG_TYPE_ENUM_UINT8       enEsmCnMsgType;     /* SM发给CN的空口消息类型 */
    NAS_ESMCN_MSG_TYPE_ENUM_UINT8       enCnEsmMsgType;     /* CN发给SM的空口消息类型 */
    VOS_UINT32                          ulMsgLength;
    VOS_UINT8                           aucMsgBuff[NAS_ESM_AIR_MSG_BUFFER_LEN];
}NAS_ESM_NW_MSG_RECORD_STRU;

/*定时器使用的数据结构*/
typedef struct
{
    HTIMER                              hTimer;             /* vos分配的Timer Id   */
    NAS_ESM_TIMER_PARA_ENUM_UINT8       enPara;             /* Timer类型   */
    VOS_UINT8                           ucExpireTimes;      /* Timer超时次数  */
    VOS_UINT8                           aucReserve1[2];     /* 四字节对齐，保留 */
}NAS_ESM_TIMER_STRU;

typedef struct tag_NAS_ESM_PDN_REJ_INFO_STRU
{
    struct tag_NAS_ESM_PDN_REJ_INFO_STRU *pstNext;

    VOS_UINT32                          bitOpApnInfo :1; /* 1: VALID; 0: INVALID*/
    VOS_UINT32                          bitOpRsv     :31;

    APP_ESM_PDN_TYPE_ENUM_UINT32        enPdnType;
    APP_ESM_APN_INFO_STRU               stApnInfo;
    NAS_ESM_PLMN_LIST_STRU              stEPlmnList;
}NAS_ESM_PDN_REJ_INFO_STRU;


/*承载管理信息的数据结构*/

typedef APP_ESM_PDP_MANAGE_INFO_STRU NAS_ESM_PDP_MANAGE_INFO_STRU;


typedef struct
{
    VOS_UINT32                          bitOpPdpManInfo :1; /* 1: VALID; 0: INVALID*/
    VOS_UINT32                          bitOpRsv        :31;

    NAS_ESM_PDP_MANAGE_INFO_STRU        stPdpManInfo;
}NAS_ESM_NV_PDP_MANAGE_INFO_STRU;

typedef APP_ESM_SDF_PARA_STRU          NAS_ESM_SDF_PARA_STRU;

/*EPS承载上下文信息的数据结构*/
typedef struct
{
    VOS_UINT32                          bitOpPdnAddr                      : 1;
    VOS_UINT32                          bitOpApn                          : 1;
    VOS_UINT32                          bitOpApnAmbr                      : 1;
    VOS_UINT32                          bitOpEpsQos                       : 1;
    VOS_UINT32                          bitOpPco                          : 1;
    VOS_UINT32                          bitOpEsmCause                     : 1;
    VOS_UINT32                          bitOpCId                          : 1;
    VOS_UINT32                          bitOpGateWayAddrInfo              : 1;
    VOS_UINT32                          bitOpTransId                      : 1;
    VOS_UINT32                          bitOpNegQos                       : 1;
    VOS_UINT32                          bitOpLlcSapi                      : 1;
    VOS_UINT32                          bitOpRadioPriority                : 1;
    VOS_UINT32                          bitOpPacketFlowId                 : 1;
    VOS_UINT32                          bitOpSpare                        : 19;

    NAS_ESM_BEARER_STATE_ENUM_UINT8     enBearerCntxtState; /* SM上下文的状态 */
    NAS_ESM_BEARER_TYPE_ENUM_UINT8      enBearerCntxtType;  /* 上下文对应承载的类型 */
    NAS_ESM_CAUSE_ENUM_UINT8            enEsmCau;
    VOS_UINT8                           ucReserve1[1];         /* 四字节对齐，保留 */

    VOS_UINT32                          ulEpsbId;           /*对应EPS承载ID*/
    VOS_UINT32                          ulBitCId;           /*此承载对应的CID，一个BIT对应一个CID*/
    VOS_UINT32                          ulLinkedEpsbId;     /*与此承载关联的EPS承载ID*/
    NAS_ESM_CONTEXT_IP_ADDR_STRU        stPdnAddrInfo;
    NAS_ESM_CONTEXT_IP_ADDR_STRU        stSubnetMask;
    NAS_ESM_CONTEXT_IP_ADDR_STRU        stGateWayAddrInfo;
    APP_ESM_APN_INFO_STRU               stApnInfo;
    NAS_ESM_CONTEXT_APN_AMBR_STRU       stApnAmbrInfo;
    NAS_ESM_CONTEXT_LTE_QOS_STRU        stEpsQoSInfo;
    NAS_ESM_CONTEXT_QOS_STRU            stCntxtQosInfo;
    NAS_ESM_CONTEXT_PCO_STRU            stPcoInfo;
    NAS_ESM_CONTEXT_TRANS_ID_STRU       stTransId;
    VOS_UINT8                           ucLlcSapi;
    VOS_UINT8                           ucRadioPriority;
    VOS_UINT8                           ucPacketFlowId;
    VOS_UINT8                           aucReserved2[1];
}NAS_ESM_EPSB_CNTXT_INFO_STRU;

typedef struct
{
    VOS_UINT32                          ulEpsbId;
    VOS_UINT32                          ulSdfPfNum;           /*SDF当前有效的PF数*/
    NAS_ESM_CONTEXT_TFT_STRU            astSdfPfInfo[NAS_ESM_MAX_SDF_PF_NUM];
    NAS_ESM_CONTEXT_LTE_QOS_STRU        stSdfQosInfo;
}NAS_ESM_SDF_CNTXT_INFO_STRU;

/*ESM 记录待发送的空口消息的数据结构*/
typedef struct
{
    VOS_UINT32                          ulNwMsgSize;         /* 消息的总长度 */
    VOS_UINT8                          *pucNwMsg;            /* 消息的首地址 */
}NAS_ESM_SND_NW_MSG_STRU;

/*ESM 与网络协商后的TFT信息*/
typedef struct
{
    VOS_UINT32                          ulEpsbId;
    VOS_UINT32                          ulCid;
    NAS_ESM_CONTEXT_TFT_STRU            stCntxtUlTftInfo;
}NAS_ESM_EPSB_TFT_INFO_STRU;

/*ESM 记录空口消息IE的数据结构*/
typedef struct
{
    VOS_UINT8                           ucLen;              /* IE的长度       */
    VOS_UINT8                           aucReserve1[3];     /* 四字节对齐，保留 */
    VOS_UINT8                          *pucValue;           /* IE的首地址     */
}NAS_ESM_MSG_IE_COMMON_STRU;

/*ESM 记录空口消息中TAD信息*/
typedef struct
{
    NAS_ESM_TFT_OP_TYPE_ENUM_UINT8      enTftOpType;
    VOS_UINT8                           ucSdfPfNum;         /*SDF当前有效的PF数*/
    VOS_UINT8                           aucReserved[2];
    NAS_ESM_CONTEXT_TFT_STRU            astSdfPfInfo[NAS_ESM_MAX_SDF_PF_NUM];
}NAS_ESM_TAD_INFO_STRU;

/*ESM 记录空口消息中Notification Indicator信息*/
typedef struct
{
    VOS_UINT8                           ucValue;
    VOS_UINT8                           aucRsv[3];
}NAS_ESM_NOTIFICATION_IND_STRU;

/*ESM 记录空口消息的数据结构*/
typedef struct
{
    VOS_UINT32                          bitOpPdnAddr                      : 1;
    VOS_UINT32                          bitOpApn                          : 1;
    VOS_UINT32                          bitOpEpsQos                       : 1;
    VOS_UINT32                          bitOpPco                          : 1;
    VOS_UINT32                          bitOpEsmCause                     : 1;
    VOS_UINT32                          bitOpLinkedEpsbId                 : 1;
    VOS_UINT32                          bitOpApnAmbr                      : 1;
    VOS_UINT32                          bitOpTadInfo                      : 1;
    VOS_UINT32                          bitOpTransId                      : 1;
    VOS_UINT32                          bitOpNegQos                       : 1;
    VOS_UINT32                          bitOpLlcSapi                      : 1;
    VOS_UINT32                          bitOpRadioPriority                : 1;
    VOS_UINT32                          bitOpPacketFlowId                 : 1;
    VOS_UINT32                          bitOpNotificationInd              : 1;
    VOS_UINT32                          bitOpSpare                        : 18;

    VOS_UINT8                           ucEpsbId;
    VOS_UINT8                           ucLinkedEpsbId;
    NAS_ESMCN_MSG_TYPE_ENUM_UINT8       enEsmCnMsgType;     /* 空口消息类型 */
    NAS_ESM_CAUSE_ENUM_UINT8            enEsmCau;           /* ESM Cause*/
    VOS_UINT8                           ucPti;
    VOS_UINT8                           aucReserved[3];

    NAS_ESM_TAD_INFO_STRU               stTadInfo;
    NAS_ESM_CONTEXT_LTE_QOS_STRU        stSdfQosInfo;
    NAS_ESM_CONTEXT_IP_ADDR_STRU        stPdnAddrInfo;
    APP_ESM_APN_INFO_STRU               stApnInfo;
    NAS_ESM_CONTEXT_APN_AMBR_STRU       stApnAmbrInfo;
    NAS_ESM_CONTEXT_PCO_STRU            stPcoInfo;
    NAS_ESM_CONTEXT_QOS_STRU            stCntxtQosInfo;
    NAS_ESM_CONTEXT_TRANS_ID_STRU       stTransId;
    VOS_UINT8                           ucLlcSapi;
    VOS_UINT8                           ucRadioPriority;
    VOS_UINT8                           ucPacketFlowId;
    VOS_UINT8                           aucReserved2[1];
    NAS_ESM_NOTIFICATION_IND_STRU       stNotificationInd;
}NAS_ESM_NW_MSG_STRU;

/*****************************************************************************
 结构名    : NAS_ESM_STATE_INFO_STRU
 结构说明  : 动态表结构体
 ***************************************************************************/
typedef struct
{
    VOS_UINT32                          bitOpAppMsgRecord                 : 1;
    VOS_UINT32                          bitOpNwMsgRecord                  : 1;
    VOS_UINT32                          bitOpSpare                        : 30;

    VOS_UINT32                          ulCid;              /*无效值为0x20，有效值为0~31*/
    VOS_UINT32                          ulEpsbId;           /*对应EPS承载ID*/
    VOS_UINT32                          ulLinkedEpsbId;     /*与此承载关联的EPS承载ID*/

    NAS_ESM_PROC_TRANS_STATE_ENUM_UINT8 enProcTransTState;  /* SM的PROCEDURE_TRANSACTION状态 */
    NAS_ESM_BEARER_STATE_ENUM_UINT8     enBearerCntxtState; /* SM上下文的状态 */
    NAS_ESM_BEARER_TYPE_ENUM_UINT8      enBearerCntxtType;  /* 上下文对应承载的类型 */
    VOS_UINT8                           ucIsWaitForUserAnswer;/* 是否处于等待用户回复 */
    NAS_ESM_APP_IND_TYPE_ENUM_UINT32    enAppIndType;       /* ESM上报APP类型 */

    NAS_ESM_PDN_REQ_TYPE_ENUM_UINT8     enPdnReqType;       /* PDN连接请求类型，目前仅在CL多模场景使用 */

    NAS_ESM_BEARER_DATA_CNF_ENUM_UINT8  enEsmBearerDataCnf;
    VOS_UINT8                           aucRsv[2];

    NAS_ESM_APP_MSG_RECORD_STRU         stAppMsgRecord;     /*App消息记录*/
    NAS_ESM_NW_MSG_RECORD_STRU          stNwMsgRecord;      /*空口消息记录*/
    NAS_ESM_TIMER_STRU                  stTimerInfo;        /*定时器使用信息*/

    NAS_ESM_NW_MSG_STRU                *pstDecodedNwMsg;    /* 缓存译码后的网络消息 */
} NAS_ESM_STATE_INFO_STRU;

/*****************************************************************************
 结构名    : EMM_ESM_INTRA_DATA_IND_STRU
 结构说明  : 内部构造的ID_EMM_ESM_DATA_IND消息
 ***************************************************************************/
typedef struct
{
    VOS_MSG_HEADER
    VOS_UINT32                           ulMsgId;           /* 消息头 */
    NAS_ESM_NW_MSG_STRU                  stEsmNwMsgIE;      /* 解析后的网侧消息 */
}EMM_ESM_INTRA_DATA_IND_STRU;

/*****************************************************************************
 结构名    : NAS_ESM_ATTACHING_BUFF_ITEM_STRU
 结构说明  : 存储译码以后的网络消息以及译码结果的结构体
 ***************************************************************************/
typedef struct
{
    NAS_ESM_CAUSE_ENUM_UINT8            enDecodeRslt;
    VOS_UINT8                           aucReserved[3];
    EMM_ESM_INTRA_DATA_IND_STRU         stDecodedNwMsg;
}NAS_ESM_ATTACHING_BUFF_ITEM_STRU;

/* PTI缓存记录结构体 */
typedef struct
{
    VOS_UINT8                           ucPti;
    VOS_UINT8                           ucEpsbId;
    VOS_UINT8                           aucReserved[2];

    VOS_UINT32                          ulOpId;             /* 用于标识发送的消息 */
    NAS_ESM_TIMER_STRU                  stTimerInfo;        /* 定时器变量 */
    EMM_ESM_MSG_STRU                    stEsmMsg;           /* 回复消息，即 ACCEPT消息或REJ消息 */
} NAS_ESM_PTI_BUFF_ITEM_STRU;

/* ESM缓存结构体 */
typedef struct
{
    VOS_UINT8                           ucPtiBuffItemNum;
    VOS_UINT8                           ucAttBuffItemNum;
    VOS_UINT8                           aucReserved[2];

    VOS_VOID                           *paPtiBuffer[NAS_ESM_MAX_PTI_BUFF_ITEM_NUM];
    VOS_VOID                           *paAttBuffer[NAS_ESM_MAX_ATTACHING_BUFF_ITEM_NUM];
}NAS_ESM_BUFF_MANAGE_INFO_STRU;

/* Info for Attach Bearer Re-establishment feature */
typedef struct
{
    LNAS_ESM_NV_ATTACH_BEARER_REEST_STRU stNvData;    /* NV data */
    VOS_UINT32                           ulEpsbId;    /* EBI of attach bearer */
    NAS_ESM_TIMER_STRU                   stTimerInfo; /* timer info */
} NAS_ESM_ATTACH_BEARER_REEST_INFO_STRU;

/*ESM 实体的数据结构*/
typedef struct
{
    NAS_ESM_PS_REGISTER_STATUS_ENUM_UINT8 enRegisterStatus;  /* EMM的PS域注册状态  */
    NAS_ESM_L_MODE_STATUS_ENUM_UINT8    enLModeStatus;      /* L模状态 */
    VOS_UINT8                           ucCurMaxPTI;        /* 当前已使用的PTI的最大值 */
    VOS_UINT8                           ucCurMaxGwAuthId;   /*当前已使用的GwAuthId的最大值*/

    VOS_UINT32                          ulCurMaxOpId;       /* 当前已使用的OpId的最大值 */
    VOS_UINT32                          ulCurPdnConNum;     /*当前PDN连接数量*/

    VOS_UINT8                           ucEsmErabmSessionId;     /* ESM通知REABM ACT_IND消息时使用 */
    VOS_UINT8                           aucRsv[3];

    /* 本地存储的所有SDF参数  */
    NAS_ESM_SDF_PARA_STRU               astSdfPara[NAS_ESM_MAX_CID_NUM];

    /*已激活承载的SDF参数*/
    NAS_ESM_SDF_CNTXT_INFO_STRU         astSdfCntxtInfo[NAS_ESM_MAX_CID_NUM];

    /* EPS承载信息  */
    NAS_ESM_EPSB_CNTXT_INFO_STRU        astEpsbCntxtInfo[NAS_ESM_MAX_EPSB_NUM];

    /*存储UE发起的流程信息*/
    NAS_ESM_STATE_INFO_STRU             astStateTable[NAS_ESM_MAX_STATETBL_NUM];

    NAS_ESM_PDP_MANAGE_INFO_STRU        stEsmBearerManageInfo;/* 承载管理信息  */

    NAS_ESM_SND_NW_MSG_STRU             stEsmSndNwMsg;

    NAS_ESM_BUFF_MANAGE_INFO_STRU       stEsmBuffManageInfo;

    NAS_ESM_ATTACH_BEARER_REEST_INFO_STRU stAttachBearerReestInfo;

    NAS_ESM_TIMER_STRU                  stDeferRelNonEmcTimerInfo;

    VOS_UINT32                          ulBearerSessionStartFlag;
    NAS_ESM_PDN_REJ_INFO_STRU           *pstPdnRej50Info;
    NAS_ESM_PDN_REJ_INFO_STRU           *pstPdnRej51Info;
    NAS_ESM_PDN_REJ_INFO_STRU           *pstPdnRej66Info;
    NAS_ESM_TIMER_STRU                  stBackOffWaitUsimTimerInfo;
} NAS_ESM_ENTITY_STRU;

/*ESM 接收的消息头的数据结构*/
typedef struct
{
    VOS_MSG_HEADER
    VOS_UINT32                          ulMsgId;
}NAS_ESM_GENERAL_MSG_HEADER_STRU;


/* 动作处理函数的类型定义 */
typedef VOS_VOID (                  * NAS_ESM_ACTION_FUN )
(
    VOS_VOID *                                              /* 消息指针 */
);


/* 动作表结构 */
typedef struct ACT
{
    VOS_UINT32                          ulEventType;        /* 事件类型 */
    NAS_ESM_ACTION_FUN                       pfActionFun;        /* 动作函数 */
}  NAS_ESM_ACT_STRU;


/* 状态转移表结构 */
typedef struct STA
{
    VOS_UINT32                          ulState;            /* 状态,低两字节有效: 0x0000_0x主_0x子 */
    VOS_UINT32                          ulSize;             /* 动作表的大小字节数除以ACT结构的大小 */
    NAS_ESM_ACT_STRU                    *pActTable;         /* 动作表的基地址                      */
}  NAS_ESM_STA_STRU;

/*****************************************************************************
 结构名    : NAS_ESM_APP_ERROR_MAPPING_STRU
 结构说明  : APP错误码与网侧错误码映射结构
 ***************************************************************************/
typedef struct
{
    VOS_UINT32                          ulAppErrorCode;
    VOS_UINT32                          enEsmCause;
}NAS_ESM_APP_ERROR_MAPPING_STRU;

/*****************************************************************************
结构名称    :NAS_ESM_MSG_VALIDATE_FUN
使用说明    :消息验证函数指针结构
*****************************************************************************/
typedef VOS_UINT32 ( * NAS_ESM_MSG_VALIDATE_FUN)
(
    const NAS_ESM_NW_MSG_STRU *               /* 译码后的空口消息指针 */
);

/*****************************************************************************
结构名称    :NAS_ESM_MSG_VAL_ACT_STRU
使用说明    :消息验证操作结构
*****************************************************************************/
typedef struct
{
    VOS_UINT8                       aucRsv[3];
    NAS_ESMCN_MSG_TYPE_ENUM_UINT8   enMsgTp;            /* 消息id */
    NAS_ESM_MSG_VALIDATE_FUN        pstMsgVldtFun;      /* 消息检测函数指针*/
}NAS_ESM_MSG_VAL_ACT_STRU;


/*****************************************************************************
 结构名    : NAS_EMM_TIMER_INFO_STRU
 结构说明  : log出ESM定时器运行情况
 1.日    期   : 2012年12月03日
   作    者   : n00181501
   修改内容   : 新建

*****************************************************************************/
typedef struct
{
    MSG_HEADER_STRU                          stMsgHeader;     /*_H2ASN_Skip*/
    NAS_ESM_TIMER_RUN_STA_ENUM_UINT32        enTimerStatus;   /* 定时器状态*/

    NAS_ESM_TIMER_PARA_ENUM_UINT8             enTimerId;       /* 定时器ID*/
    VOS_UINT8                                usRsv[3];
    VOS_UINT32                               ulTimerRemainLen;/* 定时器的时长 */
}NAS_ESM_TIMER_INFO_STRU;

/*****************************************************************************
  6 UNION
*****************************************************************************/


/*****************************************************************************
  7 Extern Global Variable
*****************************************************************************/
/* 删除PCO flag相关无效代码 y00307272 20151205 DTS2015101700432 */
extern VOS_UINT32                                           g_ulDelSdfWithQosFlag;
#define NAS_ESM_GetDelSdfWithQosFlag()\
    (((g_ulDelSdfWithQosFlag)== (LPS_NV_GET_DEL_SDF_WITH_QOS_BIT))?(NAS_ESM_DEL_SDF_WITH_QOS_ON):(NAS_ESM_DEL_SDF_WITH_QOS_OFF))

/*P-CSCF功能开关*/
extern VOS_UINT32                                            g_ulPcscfFlag;
#define NAS_ESM_GetPcscfFlag()                              (g_ulPcscfFlag)

/*BCM功能开关*/
extern VOS_UINT32                                            g_ulBcmFlag;
#define NAS_ESM_GetBcmFlag()                                (g_ulBcmFlag)
/*MD5功能开关*/
extern VOS_UINT32                                            g_ulMd5Flag;
#define NAS_ESM_GetMd5Flag()                                (g_ulMd5Flag)

extern VOS_UINT8                                            g_aucChallengeValue[NAS_ESM_AUTH_CHALLENGE_VALUE_LEN];
#define NAS_ESM_GetChallegeValue()                          (g_aucChallengeValue)

extern VOS_UINT8                                            g_aucChallegeRspValue[NAS_ESM_AUTH_RESPONSE_VALUE_LEN];
#define NAS_ESM_GetChallegeRspValue()                       (g_aucChallegeRspValue)
/*ESM  实体信息*/
extern NAS_ESM_ENTITY_STRU                                  g_stNasEsmEntity;
extern NAS_ESM_ENTITY_STRU                                 *pg_stNasEsmEntity;

#define NAS_ESM_Entity()                                   (pg_stNasEsmEntity)

/*通过PCO申请IPV6 DNS功能开关*/
/*extern NAS_ESM_GET_IPV6_DNS_CTRL_ENUM_UINT32     g_enIpv6DnsFlag;
 */
#define NAS_ESM_GetIpv6DnsFlag()                            (g_enIpv6DnsFlag)

extern  VOS_UINT32                                          g_ulLocalIpSupportFlag;
#define NAS_ESM_GetLocalIpSupFlag()                            (g_ulLocalIpSupportFlag)

extern  VOS_UINT32                                          g_ulNwLocalIpSupportFlag;
#define NAS_ESM_GetNwLocalIpSupFlag()                       (g_ulNwLocalIpSupportFlag)



#define NAS_ESM_GetEmmStatus()\
                  ((NAS_ESM_Entity())->enRegisterStatus)

#define NAS_ESM_GetLModeStatus()\
                  ((NAS_ESM_Entity())->enLModeStatus)

#define NAS_ESM_GetSdfCntxtInfo(ulCid)\
                  (&((NAS_ESM_Entity())->astSdfCntxtInfo[(ulCid)]))

#if (VOS_OS_VER != VOS_WIN32)
#define NAS_ESM_SetEmmStatus(ucEmmStatus)\
        {\
             NAS_ESM_NORM_LOG("~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~");\
             NAS_ESM_NORM_LOG("EMM Register Status change----");\
             NAS_ESM_PRINT_EMMSTA(NAS_ESM_GetEmmStatus());\
             NAS_ESM_NORM_LOG("==>>");\
             (NAS_ESM_Entity())->enRegisterStatus = (ucEmmStatus);\
             NAS_ESM_PRINT_EMMSTA(ucEmmStatus);\
             NAS_ESM_NORM_LOG("~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~");\
        }
#else
#define NAS_ESM_SetEmmStatus(ucEmmStatus)\
        {\
             (NAS_ESM_Entity())->enRegisterStatus = (ucEmmStatus);\
        }
#endif

#if (VOS_OS_VER != VOS_WIN32)
#define NAS_ESM_SetLModeStatus(ucLModeStatus)\
        {\
             NAS_ESM_NORM_LOG("~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~");\
             NAS_ESM_NORM_LOG("ESM L Mode Status change----");\
             NAS_ESM_PRINT_LMODESTA(NAS_ESM_GetLModeStatus());\
             NAS_ESM_NORM_LOG("==>>");\
             (NAS_ESM_Entity())->enLModeStatus = (ucLModeStatus);\
             NAS_ESM_PRINT_LMODESTA(ucLModeStatus);\
             NAS_ESM_NORM_LOG("~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~");\
        }
#else
#define NAS_ESM_SetLModeStatus(ucLModeStatus)\
        {\
             (NAS_ESM_Entity())->enLModeStatus = (ucLModeStatus);\
        }
#endif

#define NAS_ESM_GetStateTblAddr(ulStateTblIndex)\
                  (&((NAS_ESM_Entity())->astStateTable[(ulStateTblIndex)]))
#define NAS_ESM_GetStateTblBearerState(ulStateTblIndex)\
                  (((NAS_ESM_Entity())->astStateTable[(ulStateTblIndex)]).enBearerCntxtState)
#define NAS_ESM_GetStateTblAppMsgType(ulStateTblIndex) \
                  (((NAS_ESM_Entity())->astStateTable[(ulStateTblIndex)]).stAppMsgRecord.enAppMsgType)

#define NAS_ESM_GetSdfParaAddr(ulCID)\
                  (&((NAS_ESM_Entity())->astSdfPara[(ulCID)]))

#define NAS_ESM_GetBearerManageInfoAddr()\
                  (&((NAS_ESM_Entity())->stEsmBearerManageInfo))
#define NAS_ESM_GetEsmSndNwMsgAddr()\
                  (&((NAS_ESM_Entity())->stEsmSndNwMsg))
#define NAS_ESM_GetCurEsmSndNwMsgAddr()\
                  ((NAS_ESM_GetEsmSndNwMsgAddr())->pucNwMsg)
#define NAS_ESM_UpdateEsmSndNwMsgLen(ulNwMsgAddLen)\
                  ((NAS_ESM_GetEsmSndNwMsgAddr())->ulNwMsgSize = ulNwMsgAddLen)
#define NAS_ESM_GetEsmSndNwMsgLen()\
                  (NAS_ESM_GetEsmSndNwMsgAddr()->ulNwMsgSize)
#define NAS_ESM_ClearEsmSndNwMsgAddr() \
        {                                                            \
            if (VOS_NULL_PTR != NAS_ESM_GetCurEsmSndNwMsgAddr())     \
            {                                                        \
                NAS_ESM_MEM_FREE(NAS_ESM_GetCurEsmSndNwMsgAddr());   \
            }                                                        \
                                                                     \
            NAS_ESM_MEM_SET_S(NAS_ESM_GetEsmSndNwMsgAddr(),          \
                             sizeof(NAS_ESM_SND_NW_MSG_STRU),        \
                             NAS_ESM_NULL,                           \
                             sizeof(NAS_ESM_SND_NW_MSG_STRU));       \
         }

#define NAS_ESM_GetStateTblTimer(ulStateTblIndex)\
                  (&((NAS_ESM_Entity())->astStateTable[(ulStateTblIndex)].\
                                                                   stTimerInfo))

#define NAS_ESM_GetProcTransState(ulStateTblIndex)\
                  (((NAS_ESM_Entity())->astStateTable[(ulStateTblIndex)]).enProcTransTState)

#if (VOS_OS_VER != VOS_WIN32)
#define NAS_ESM_SetProcTransState(ulStateTblIndex,enDestState)\
        {\
             NAS_ESM_NORM_LOG("~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~");\
             NAS_ESM_LOG1("SM Procedure Transaction state change----StateTblIndex : ", ulStateTblIndex);\
             NAS_ESM_PRINT_PROCTRANSSTA(NAS_ESM_GetProcTransState(ulStateTblIndex));\
             NAS_ESM_NORM_LOG("==>>");\
             ((NAS_ESM_Entity())->astStateTable[(ulStateTblIndex)]).enProcTransTState = (enDestState);\
             NAS_ESM_PRINT_PROCTRANSSTA(enDestState);\
             NAS_ESM_NORM_LOG("~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~");\
        }
#else
#define NAS_ESM_SetProcTransState(ulStateTblIndex,enDestState)\
        {\
             ((NAS_ESM_Entity())->astStateTable[(ulStateTblIndex)]).enProcTransTState = (enDestState);\
        }
#endif

#define NAS_ESM_GetCurMaxOpIdValue()   ((NAS_ESM_Entity())->ulCurMaxOpId)
#define NAS_ESM_SetCurMaxOpIdValue(ulOpId)\
                  ((NAS_ESM_Entity())->ulCurMaxOpId = (ulOpId))

#define NAS_ESM_GetErabmSessionIdValue()      ((NAS_ESM_Entity())->ucEsmErabmSessionId)
#define NAS_ESM_SetErabmSessionIdValue(ucId)\
                   ((NAS_ESM_Entity())->ucEsmErabmSessionId = (ucId))

#define NAS_ESM_GetCurMaxPTIValue()     ((NAS_ESM_Entity())->ucCurMaxPTI)
#define NAS_ESM_SetCurMaxPTIValue(ucPti) ((NAS_ESM_Entity())->ucCurMaxPTI = (ucPti))
#define NAS_ESM_GetCurMaxGwAuthIdVaule() ((NAS_ESM_Entity())->ucCurMaxGwAuthId)
#define NAS_ESM_SetCurMaxGwAuthIdVaule(ucGwAuthId) ((NAS_ESM_Entity())->ucCurMaxGwAuthId = (ucGwAuthId))

#define NAS_ESM_GetCurPdnNum()     ((NAS_ESM_Entity())->ulCurPdnConNum)
#define NAS_ESM_SetCurPdnNum(ucPdnNum) ((NAS_ESM_Entity())->ulCurPdnConNum = (ucPdnNum))

#define NAS_ESM_GetEsmBufferManageInfoAddr()     (&(NAS_ESM_Entity())->stEsmBuffManageInfo)

#define NAS_ESM_GetEsmAppErrorMapArrayLen()      (sizeof(g_astEsmAppErrorMappingTbl)/sizeof(NAS_ESM_APP_ERROR_MAPPING_STRU))
#define NAS_ESM_GetEsmAppErrorMapTbl()           (g_astEsmAppErrorMappingTbl)
#define NAS_ESM_GetCid(ulEpsbId)\
                ((ulEpsbId - NAS_ESM_MIN_EPSB_ID) + NAS_ESM_MAX_UE_CONTRUL_CID + 1)

#define NAS_ESM_AttachBearerReestEnable()        (NAS_ESM_Entity()->stAttachBearerReestInfo.stNvData.bitOpAttachBearerReest)
#define NAS_ESM_SetAttachBearerId(Id)            (NAS_ESM_Entity()->stAttachBearerReestInfo.ulEpsbId = Id)
#define NAS_ESM_GetAttachBearerId()              (NAS_ESM_Entity()->stAttachBearerReestInfo.ulEpsbId)
#define NAS_ESM_GetAttachBearerReestTimerLen()   (NAS_ESM_Entity()->stAttachBearerReestInfo.stNvData.ulReestTimeLen)
#define  NAS_ESM_GetBearerSessionStartFlag()                                (NAS_ESM_Entity()->ulBearerSessionStartFlag)
#define  NAS_ESM_SetBearerSessionStartFlag(ulBearerSessionStartFlag)        (NAS_ESM_GetBearerSessionStartFlag()  = (ulBearerSessionStartFlag))
#define NAS_ESM_GetEsmPdnRejCause50InfoAddr()     (NAS_ESM_Entity()->pstPdnRej50Info)
#define NAS_ESM_GetEsmPdnRejCause51InfoAddr()     (NAS_ESM_Entity()->pstPdnRej51Info)

/*****************************************************************************
  8 Fuction Extern
*****************************************************************************/
extern VOS_VOID  NAS_ESM_SetBearCntxtType
(
    VOS_UINT32                          ulEpsbId,
    NAS_ESM_BEARER_TYPE_ENUM_UINT8      enDestType
);
extern NAS_ESM_BEARER_TYPE_ENUM_UINT8  NAS_ESM_GetBearCntxtType( VOS_UINT32 ulEpsbId );
extern NAS_ESM_BEARER_STATE_ENUM_UINT8 NAS_ESM_GetBearCntxtState(VOS_UINT32 ulEpsbId);
extern VOS_VOID NAS_ESM_SetBearCntxtState
(
    VOS_UINT32                          ulEpsbId,
    NAS_ESM_BEARER_STATE_ENUM_UINT8     enDestState
);
extern VOS_VOID  NAS_ESM_SetBearCntxtLinkCid
(
    VOS_UINT32                          ulEpsbId,
    VOS_UINT32                          ulCid
);
extern VOS_VOID  NAS_ESM_ClearBearCntxtLinkCid
(
    VOS_UINT32                          ulEpsbId,
    VOS_UINT32                          ulCid
);
extern VOS_VOID  NAS_ESM_UpdateBearCntextLinkCid
(
    const NAS_ESM_NW_MSG_STRU          *pstDecodedNwMsg,
    VOS_UINT32                          ulEpsbId,
    VOS_UINT32                          ulCid
);
extern NAS_ESM_EPSB_CNTXT_INFO_STRU * NAS_ESM_GetEpsbCntxtInfoAddr( VOS_UINT32 ulEpsbId );
extern VOS_VOID NAS_ESM_AssignOpId(VOS_UINT32         *pulOpId);
extern VOS_VOID NAS_ESM_AssignPTI(VOS_UINT32         *pulPti);
extern VOS_VOID NAS_ESM_AssignGwIpId( VOS_UINT8   *pucGwAuthId);
extern VOS_VOID NAS_ESM_GetGwAuthChallengeValue( VOS_UINT8 *pucValue );
extern VOS_VOID  NAS_ESM_GetGwAuthRpsValue
(
    const VOS_UINT8                    *pucPwd,
    VOS_UINT8                           ucPwdLen,
    VOS_UINT8                           ucId,
    const VOS_UINT8                    *pucChlgVal,
    VOS_UINT8                          *pucRspVal
);
extern VOS_UINT32  NAS_ESM_QueryPfInTft
(
    VOS_UINT8                           ucPacketFilterID,
    const APP_ESM_TFT_INFO_STRU        *pstCntxtTftInfo,
    VOS_UINT32                          ulPfNum,
    VOS_UINT32                         *pulIndex
);
extern VOS_VOID NAS_ESM_ClearEsmBearerResource( VOS_UINT32  ulEpsbId );
extern VOS_VOID NAS_ESM_ClearEsmResource( VOS_VOID );
extern VOS_UINT32  NAS_ESM_GetLinkCidByActiveCid
(
    VOS_UINT32                          ulCid
);
extern VOS_UINT32 NAS_ESM_GetStateTblIndexByCid(VOS_UINT32 ulCidRecv,VOS_UINT32 *ulStateId);
extern VOS_UINT32 NAS_ESM_QueryEpsbCntxtTblByCid(VOS_UINT32  ulCId,
                                              VOS_UINT32  *pulEpsbId);
extern VOS_UINT32 NAS_ESM_QueryEpsbCntxtTblByEpsbId(VOS_UINT32  ulEpsbId,
                                              VOS_UINT32  *pulCId);
extern VOS_UINT32 NAS_ESM_QueryFirstSdfIdByEpsbId
       (
           VOS_UINT32                          ulEpsbId,
           VOS_UINT32                         *pulCid
       );
extern VOS_UINT32 NAS_ESM_QuerySdfIdByEpsbIdAndPfId
(
    VOS_UINT8                           ucEpsbId,
    VOS_UINT8                           ucPacketFilterId,
    VOS_UINT32                         *pulCid
);

extern VOS_UINT32 NAS_ESM_QueryStateTblIndexByCid(VOS_UINT32 ulCidRecv,VOS_UINT32 *ulStateId);
extern VOS_UINT32 NAS_ESM_QueryStateTblIndexByEpsbId(VOS_UINT32 ulEpsbId,VOS_UINT32 *ulStateId);
extern VOS_UINT32 NAS_ESM_QueryStateTblIndexByPti(VOS_UINT8 ucPti,VOS_UINT32 *ulStateId);


extern VOS_VOID NAS_ESM_RelStateTblResource(VOS_UINT32  ulStateTblIndex );


extern NAS_ESM_QUERY_CID_RSLT_ENUM_UINT8  NAS_ESM_QuerySdfId
(
    const NAS_ESM_NW_MSG_STRU          *pstEsmNwMsgIE,
    VOS_UINT32                         *pulCid
);

extern VOS_UINT32  NAS_ESM_GetBearerLinkedCidNum
(
    VOS_UINT32                          ulEpsbId
);

extern VOS_UINT32 NAS_ESM_GetAppErrorByEsmCause
(
    NAS_ESM_CAUSE_ENUM_UINT8            enEsmCause
);

extern VOS_UINT32 NAS_ESM_QueryNWPacketFilterID
(
    VOS_UINT8                           ucPacketFilterID,
    VOS_UINT32                          ulCID,
    VOS_UINT8                          *ucNWPacketFilterID
);


extern VOS_UINT32  NAS_ESM_IsTftInfoValid
(
    const APP_ESM_TFT_INFO_STRU               *pstAppTftInfo
);

extern VOS_UINT32  NAS_ESM_IsSdfQosValid
(
    const APP_ESM_EPS_QOS_INFO_STRU          *pstSdfQosInfo
);

extern VOS_UINT32  NAS_ESM_IsGwAuthInfoValid
(
    const APP_ESM_GW_AUTH_INFO_STRU           *pstGwAuthInfo
);

extern VOS_UINT32  NAS_ESM_IsSdfParaOtherInfoValid
(
    const NAS_ESM_SDF_PARA_STRU           *pstSdfPara
);

extern VOS_UINT32  NAS_ESM_IsSdfParaValid
(
    const NAS_ESM_SDF_PARA_STRU           *pstSdfPara
);
extern VOS_UINT32  NAS_ESM_IsGbrBearer( VOS_UINT8 ucQci );
extern VOS_VOID NAS_ESM_ClearEsmBuffItem
(
    NAS_ESM_BUFF_ITEM_TYPE_ENUM_UINT8   enEsmBuffType,
    VOS_UINT32                          ulIndex
);
extern VOS_VOID  NAS_ESM_ClearEsmBuff( VOS_VOID );
extern NAS_ESM_TIMER_STRU* NAS_ESM_GetPtiBuffItemTimer
       (
           VOS_UINT32                          ulIndex
       );
extern NAS_ESM_TIMER_STRU*  NAS_ESM_GetTimer
       (
            VOS_UINT32                          ulIndex,
            NAS_ESM_TIMER_PARA_ENUM_UINT8       enTimerType
       );
extern VOS_UINT32  NAS_ESM_GetTimerLen
       (
            NAS_ESM_TIMER_PARA_ENUM_UINT8       enTimerType
       );
extern VOS_VOID  NAS_ESM_PrintTimeStartInfo
       (
            VOS_UINT32                          ulIndex,
            NAS_ESM_TIMER_PARA_ENUM_UINT8       enTimerType
       );
extern VOS_VOID  NAS_ESM_PrintTimeStopInfo
       (
            VOS_UINT32                          ulIndex,
            NAS_ESM_TIMER_PARA_ENUM_UINT8       enTimerType
       );
extern VOS_UINT32  NAS_ESM_QueryOverduePtiBuffItem
       (
           VOS_UINT8                           ucPti,
           VOS_UINT8                           ucEpsbId,
           VOS_UINT32                         *pulIndex
       );
extern VOS_UINT32  NAS_ESM_QueryPtiBuffItemByEpsbId
       (
           VOS_UINT8                           ucEpsbId,
           VOS_UINT32                         *pulIndex
       );
extern VOS_UINT32  NAS_ESM_QueryPtiBuffItemByPti
       (
           VOS_UINT8                           ucPti,
           VOS_UINT32                         *pulIndex
       );

extern VOS_UINT32 NAS_ESM_QuerySdfIdByEpsbIdAndPfId
       (
           VOS_UINT8                           ucEpsbId,
           VOS_UINT8                           ucPacketFilterId,
           VOS_UINT32                         *pulCid
       );
extern VOS_UINT32  NAS_ESM_SavePtiBuffItem
       (
           VOS_UINT8                           ucPti,
           VOS_UINT8                           ucEpsbId,
           VOS_UINT32                          ulLength,
           const VOS_UINT8                    *pucSendMsg
       );
extern VOS_VOID NAS_ESM_TimerStart
       (
           VOS_UINT32                          ulIndex,
           NAS_ESM_TIMER_PARA_ENUM_UINT8       enTimerType
       );
extern VOS_VOID NAS_ESM_TimerStop
       (
           VOS_UINT32                          ulIndex,
           NAS_ESM_TIMER_PARA_ENUM_UINT8       enTimerType
       );
extern VOS_UINT32  NAS_ESM_GetTimerMaxExpNum
       (
           NAS_ESM_TIMER_PARA_ENUM_UINT8 enTimerType
       );
extern VOS_UINT32  NAS_ESM_IsTimerNameValid
      (
           VOS_UINT32                          ulIndex,
           NAS_ESM_TIMER_PARA_ENUM_UINT8       enTimerType
      );
extern VOS_VOID* NAS_ESM_GetBuffItemAddr
      (
           NAS_ESM_BUFF_ITEM_TYPE_ENUM_UINT8   enEsmBuffType,
           VOS_UINT32                          ulIndex
      );
extern VOS_INT32  NAS_ESM_PrintAppEsmSetManageTypeReqMsg
(
    VOS_CHAR                                *pcBuff,
    VOS_UINT16                               usOffset,
    const PS_MSG_HEADER_STRU                *pstMsg
);


extern VOS_INT32  NAS_ESM_PrintAppEsmSetBearerTypeReqMsg
(
    VOS_CHAR                                *pcBuff,
    VOS_UINT16                               usOffset,
    const PS_MSG_HEADER_STRU                *pstMsg
);

extern VOS_INT32  NAS_ESM_PrintAppEsmSetPdnTypeReqMsg
(
    VOS_CHAR                                *pcBuff,
    VOS_UINT16                               usOffset,
    const PS_MSG_HEADER_STRU                *pstMsg
);

extern VOS_INT32  NAS_ESM_PrintAppEsmSetEpsQosReqMsg
(
    VOS_CHAR                                *pcBuff,
    VOS_UINT16                               usOffset,
    const PS_MSG_HEADER_STRU                *pstMsg
);

extern VOS_INT32  NAS_ESM_PrintAppEsmSetGwAuthReqMsg
(
    VOS_CHAR                                *pcBuff,
    VOS_UINT16                               usOffset,
    const PS_MSG_HEADER_STRU                *pstMsg
);

extern VOS_INT32  NAS_ESM_PrintEsmAppSetResult
(
    VOS_CHAR                                *pcBuff,
    VOS_UINT16                               usOffset,
    const PS_MSG_HEADER_STRU                *pstMsg
);

extern VOS_INT32  NAS_ESM_PrintEsmAppSetManageTypeResult
(
    VOS_CHAR                                *pcBuff,
    VOS_UINT16                               usOffset,
    const PS_MSG_HEADER_STRU                *pstMsg
);
extern VOS_VOID  NAS_ESM_PrintEsmSendMsg
(
    const PS_MSG_HEADER_STRU               *pstMsg,
    VOS_CHAR                               *pcBuff
);

extern VOS_VOID NAS_ESM_PrintEsmRevMsg
(
    const PS_MSG_HEADER_STRU           *pstMsg,
    VOS_CHAR                           *pcBuff
);

extern VOS_INT32  NAS_ESM_PrintEsmAppMsg
(
    VOS_CHAR                            *pcBuff,
    VOS_UINT16                           usOffset,
    const PS_MSG_HEADER_STRU            *pstMsg
);

extern VOS_INT32  NAS_ESM_PrintEsmTimer
(
    VOS_CHAR                            *pcBuff,
    VOS_UINT16                           usOffset,
    VOS_UINT32                           ulTimerType
);

extern VOS_VOID NAS_ESM_PrintEpsbInfo(VOS_UINT32 ulEpsbId);

extern VOS_UINT32 NAS_ESM_GetAllEpsBearerInPdn
(
    VOS_UINT8                           ucEpsbId,
    VOS_UINT8                          *pucEpsBearNum,
    VOS_UINT8                          *pucEspbId
);
extern VOS_UINT32  NAS_ESM_Random();
VOS_UINT32 NAS_ESM_IsExistSamePrecedenceInTft
(
    VOS_UINT32                          ulPfNum,
    const NAS_ESM_CONTEXT_TFT_STRU     *pstTFT
);
extern VOS_VOID NAS_ESM_DHCPGetIPv4Mask
(
    const VOS_UINT8                    *pucIpv4Addr,
    VOS_UINT8                          *pucIpv4Mask
);
extern VOS_VOID NAS_ESM_DHCPGetIPv4GateWay
(
    const VOS_UINT8                    *pucIpv4Addr,
    const VOS_UINT8                    *pucIpv4Mask,
    VOS_UINT8                          *pucIpv4GateWay
);

extern VOS_VOID NAS_ESM_ClearSdfPara(VOS_UINT32  ulCid);
extern VOS_VOID NAS_ESM_ClearNwCtrlSdfPara(VOS_VOID);

extern VOS_VOID NAS_ESM_TransformPcoStru
(
    VOS_UINT8                           ucIpType,
    const NAS_ESM_CONTEXT_PCO_STRU           *pstContPco,
    NAS_ESM_PCO_TRANSFORM_STRU         *pstTransPco
);

extern VOS_VOID NAS_ESM_Ipv4TransformPcoStru
(
    const NAS_ESM_CONTEXT_PCO_STRU     *pstContPco,
    NAS_ESM_PCO_TRANSFORM_STRU         *pstTransPco
);
extern VOS_VOID NAS_ESM_Ipv6TransformPcoStru
(
    const NAS_ESM_CONTEXT_PCO_STRU     *pstContPco,
    NAS_ESM_PCO_TRANSFORM_STRU         *pstTransPco
);

extern VOS_VOID NAS_ESM_Ipv4v6TransformPcoStru
(
    const NAS_ESM_CONTEXT_PCO_STRU     *pstContPco,
    NAS_ESM_PCO_TRANSFORM_STRU         *pstTransPco
);
extern VOS_INT32  NAS_ESM_PrintEsmAppProcedureAbortNotify
(
    VOS_CHAR                                *pcBuff,
    VOS_UINT16                               usOffset,
    const PS_MSG_HEADER_STRU                *pstMsg
);
extern VOS_INT32  NAS_ESM_PrintEsmAppIpv6InfoNotify
(
    VOS_CHAR                                *pcBuff,
    VOS_UINT16                               usOffset,
    const PS_MSG_HEADER_STRU                *pstMsg
);
extern VOS_VOID NAS_ESM_ClearCid0StaticInfo(VOS_VOID);

extern VOS_UINT32 NAS_ESM_HasExistedEmergencyPdn(VOS_VOID);
extern VOS_UINT32 NAS_ESM_HasEstingEmergencyPdn(VOS_VOID);
extern VOS_UINT32 NAS_ESM_HasEmergencyPdn(VOS_VOID);
extern VOS_UINT32 NAS_ESM_IsEmmEmcAttachedOrAttaching(VOS_VOID);
extern VOS_VOID   NAS_ESM_ClearEsmResoureWhenEstingEmcPdn(VOS_VOID);
extern VOS_VOID   NAS_ESM_DeactAllNonEmcPdn(VOS_VOID);
extern VOS_UINT32 NAS_ESM_IsDefaultEpsBearerType(VOS_UINT32 Type);
extern VOS_UINT32 NAS_ESM_QueryStateTblIndexForEmc(VOS_UINT32 *pulStateIndex);

extern VOS_VOID  NAS_ESM_SndOmEsmTimerStatus(
    NAS_ESM_TIMER_RUN_STA_ENUM_UINT32        enTimerStatus,
    NAS_ESM_TIMER_PARA_ENUM_UINT8           enTimerId,
    VOS_UINT32                              ulTimerRemainLen
);

extern VOS_INT32  NAS_ESM_PrintAppEsmSetCgdontReqMsg
(
    VOS_CHAR                                *pcBuff,
    VOS_UINT16                               usOffset,
    const PS_MSG_HEADER_STRU                *pstMsg
);
extern VOS_INT32  NAS_ESM_PrintEsmAppCgdontResult
(
    VOS_CHAR                                *pcBuff,
    VOS_UINT16                               usOffset,
    const PS_MSG_HEADER_STRU                *pstMsg
);
extern VOS_UINT32  NAS_ESM_GetSdfPara
(
    VOS_UINT32                         *pulSdfNum,
    APP_ESM_SDF_PARA_STRU              *pstSdfPara
);
extern VOS_UINT32  NAS_ESM_GetPdpManageInfo
(
    APP_ESM_PDP_MANAGE_INFO_STRU  *pstPdpManageInfo
);


extern VOS_VOID NAS_LMM_LogIsUpSigPend
(
    EMM_ESM_UP_SINGNAL_PENDING_ENUM_UINT32  enUpSigPend
);
extern VOS_VOID NAS_LMM_LogSdfPara
(
    const VOS_UINT32                         *pulSdfNum,
    const APP_ESM_SDF_PARA_STRU        *pstSdfPara,
    VOS_UINT32                          ulRslt
);
extern VOS_VOID NAS_LMM_LogPdpManageInfo
(
    const APP_ESM_PDP_MANAGE_INFO_STRU   *pstPdpManageInfo,
    VOS_UINT32  ulRslt
);

extern VOS_UINT32 NAS_ESM_IsExistAllFailStateTable(VOS_VOID);
extern VOS_VOID NAS_ESM_SendBeginSessionNotify(VOS_VOID);
extern VOS_VOID NAS_ESM_SendEndSessionNotify(VOS_VOID);
extern VOS_UINT32  NAS_ESM_AllocEmmEsmOpId( VOS_VOID );
extern VOS_UINT32  NAS_ESM_IsCurrentApnHas50Rej
(
    APP_ESM_PDN_TYPE_ENUM_UINT32        enPdnType,
    VOS_UINT32                           ulBitOpApnInfo,
    const APP_ESM_APN_INFO_STRU               *pstApnInfo
);
extern VOS_UINT32  NAS_ESM_IsCurrentApnHas51Rej
(
    APP_ESM_PDN_TYPE_ENUM_UINT32        enPdnType,
    VOS_UINT32                           ulBitOpApnInfo,
    const APP_ESM_APN_INFO_STRU               *pstApnInfo
);
extern VOS_UINT32  NAS_ESM_IsCurrentApnHas66Rej
(
    VOS_UINT32                           ulBitOpApnInfo,
    const APP_ESM_APN_INFO_STRU               *pstApnInfo
);
extern VOS_UINT32  NAS_ESM_IsCurrentApnAvailable
(
    APP_ESM_PDN_TYPE_ENUM_UINT32        enPdnType,
    VOS_UINT32                          ulBitOPApnInfo,
    const APP_ESM_APN_INFO_STRU               *pstApnInfo
);
extern VOS_VOID NAS_ESM_AssignErabmSessionId(VOS_UINT8         *pucOpId);

extern VOS_UINT32 NAS_ESM_ReadUsimBackOffRpmPdpPara(VOS_VOID);
extern VOS_VOID NAS_ESM_UsimMsgDistr(VOS_VOID *pRcvMsg);
extern VOS_UINT8 NAS_ESM_IsWaitBackOffUsimCnfTimerRunning(VOS_VOID);
extern VOS_VOID NAS_ESM_ProcReadIsimFileResult(VOS_VOID *pRcvMsg);
extern VOS_UINT32 NAS_ESM_SndUsimReadFileReq
(
    USIMM_CARDAPP_ENUM_UINT32       ulAppType,
    VOS_UINT8                       ucRecordNum,
    VOS_UINT8                       ulOpId,
    USIMM_FILEPATH_INFO_STRU       *pstGetFilePath
);

extern VOS_UINT32 NAS_ESM_QueryPdnDisconnNumInStateTbl(VOS_VOID);

extern VOS_INT32 NAS_ESM_SecuMemCpy
(
    VOS_VOID        * pDst,
    VOS_UINT32      ulMaxBuffer,
    const VOS_VOID  * pSrc,
    VOS_UINT32      ulLength,
    VOS_UINT32      ulLineNO,
    VOS_UINT32      ulFileID
);

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

#endif /* end of NasEsmPublic.h */
