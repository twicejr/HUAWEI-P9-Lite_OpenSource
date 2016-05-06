


#ifndef __NASLPPPUBLIC_H__
#define __NASLPPPUBLIC_H__


/*****************************************************************************
  1 Include Headfile
*****************************************************************************/
#include    "vos.h"
#include    "LPPLRrcInterface.h"
#include    "NasLppAirMsg.h"
#include    "PsCommonDef.h"
#include    "EmmLppInterface.h"
#include    "NasLppEncodeDecodePublic.h"
#include    "NasCommPrint.h"
#include    "PsLogdef.h"



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
#define NAS_LPP_NULL_PTR                VOS_NULL_PTR
/*封装打印LOG的宏*/
#ifdef PS_ITT_PC_TEST
#define NAS_LPP_INFO_LOG(String) \
                 vos_printf(" %s\r\n",String)
#define NAS_LPP_INFO_LOG1(String, Para1) \
                 vos_printf(" %s %d\r\n",String, (long)Para1)
#define NAS_LPP_INFO_LOG2(String, Para1, Para2) \
                 vos_printf(" %s %d %d\r\n",String, (long)Para1, (long)Para2)
#define NAS_LPP_NORM_LOG(String) \
                 vos_printf(" %s\r\n",String)
#define NAS_LPP_WARN_LOG(String) \
                 vos_printf(" %s\r\n",String)
#define NAS_LPP_ERR_LOG(String) \
                 vos_printf(" %s\r\n",String)
#define NAS_LPP_ERR_LOG1(String, Para1) \
                 vos_printf(" %s %d\r\n",String, (long)Para1)
#define NAS_LPP_ERR_LOG2(String, Para1, Para2) \
                 vos_printf(" %s %d %d\r\n",String, (long)Para1, (long)Para2)
#else
#define NAS_LPP_INFO_LOG(String) \
                 LPS_LOG(UE_MODULE_LPP_ID, VOS_NULL, LOG_LEVEL_INFO, String)
#define NAS_LPP_INFO_LOG1(String, Para1) \
                 LPS_LOG1(UE_MODULE_LPP_ID, VOS_NULL, LOG_LEVEL_INFO, String, (long)Para1 )
#define NAS_LPP_INFO_LOG2(String, Para1, Para2) \
                 LPS_LOG2(UE_MODULE_LPP_ID, VOS_NULL, LOG_LEVEL_INFO, String, (long)Para1, (long)Para2)
#define NAS_LPP_NORM_LOG(String) \
                 LPS_LOG(UE_MODULE_LPP_ID, VOS_NULL, LOG_LEVEL_NORMAL, String)
#define NAS_LPP_WARN_LOG(String) \
                 LPS_LOG(UE_MODULE_LPP_ID, VOS_NULL, LOG_LEVEL_WARNING, String)
#define NAS_LPP_ERR_LOG(String) \
                 LPS_LOG(UE_MODULE_LPP_ID, VOS_NULL, LOG_LEVEL_ERROR, String)
#define NAS_LPP_ERR_LOG1(String, Para1) \
                 LPS_LOG1(UE_MODULE_LPP_ID, VOS_NULL, LOG_LEVEL_NORMAL, String, (long)Para1 )
#define NAS_LPP_ERR_LOG2(String, Para1, Para2) \
                 LPS_LOG2(UE_MODULE_LPP_ID, VOS_NULL, LOG_LEVEL_NORMAL, String, (long)Para1, (long)Para2)
#endif

/* LPP层内存拷贝宏定义 */
//#define __LINE__    0
#define NAS_LPP_LOG_ERR(String)   vos_printf(" %s\r\n",String)


#if (VOS_OS_VER == VOS_WIN32)

#define NAS_LPP_MEM_CPY_S(pucDestBuffer, ulMaxDest, pucSrcBuffer, ulBufferLen) \
    NAS_LMM_SecuMemCpy((pucDestBuffer), (ulMaxDest), (pucSrcBuffer), (ulBufferLen), (__LINE__), (THIS_FILE_ID))

#define NAS_LPP_MEM_SET_S(pucBuffer, ulMaxDest, ucData, ulBufferLen) \
    NAS_LMM_SecuMemSet((pucBuffer), (ulMaxDest), (ucData), (ulBufferLen), (__LINE__), (THIS_FILE_ID))

#define NAS_LPP_MEM_MOVE_S(pucDestBuffer, ulMaxDest, pucSrcBuffer, ulBufferLen) \
    NAS_LMM_SecuMemMove( (pucDestBuffer), (ulMaxDest), (pucSrcBuffer), (ulBufferLen), (__LINE__), (THIS_FILE_ID))

#else

#define NAS_LPP_MEM_CPY_S(pDestBuffer, DestCount, pSrcBuffer, SrcCount) \
        (VOS_VOID)NAS_LPP_SecuMemCpy(pDestBuffer, DestCount, pSrcBuffer, SrcCount, (__LINE__), (THIS_FILE_ID))

#define NAS_LPP_MEM_SET_S(pDestBuffer, ulMaxDest, ucData, ulLength) \
        (VOS_VOID)TLPS_MEM_SET_S((pDestBuffer), (ulMaxDest), (ucData), (ulLength), (__LINE__), (THIS_FILE_ID))

#define NAS_LPP_MEM_MOVE_S(pDestBuffer, ulMaxDest, pSrcBuffer, ulLength )  \
        (VOS_VOID)TLPS_MEM_MOVE_S((pDestBuffer), (ulMaxDest), (pSrcBuffer), (ulLength), (__LINE__), (THIS_FILE_ID))

#endif

#define NAS_LPP_MEM_CMP(pucDestBuffer, pucSrcBuffer, ulBufferLen)\
    PS_MEM_CMP ((pucDestBuffer), (pucSrcBuffer), (ulBufferLen))

#define NAS_LPP_MEM_FREE(pAddr) \
            {\
                if(VOS_OK != PS_MEM_FREE_ALL_CHECK((PS_PID_LPP), (pAddr)))\
                {\
                    NAS_LPP_LOG_ERR("NAS_LMM_MEM_FREE  ERR!!");\
                }\
            }
#define NAS_LPP_MEM_ALLOC(ulSize) \
            PS_MEM_ALLOC_All_CHECK((PS_PID_LPP), (ulSize))

#define NAS_LPP_ALLOC_MSG(ulLen)\
            PS_ALLOC_MSG_ALL_CHECK((PS_PID_LPP),(ulLen))


/*Memset MSG*/
#define NAS_LPP_MEM_SET_MSG(pMsgBuffer, ulMaxMsgSize, ucData, MsgSize) \
        (VOS_VOID)TLPS_MEM_SET_S((((NAS_LPP_MSG*)pMsgBuffer)->ucRsv), ulMaxMsgSize - NAS_LPP_MSG_HEADER_LENGTH, ucData, MsgSize - NAS_LPP_MSG_HEADER_LENGTH, __LINE__, THIS_FILE_ID)

/* 发送消息 */
#define NAS_LPP_SND_MSG(pMsg)\
    {\
        NAS_LPP_PrintLppSendMsg((const PS_MSG_HEADER_STRU *)pMsg, NAS_COMM_GET_LPP_PRINT_BUF());\
        NAS_LPP_NORM_LOG("====================IN MSG CONTENT is : ============");\
        NAS_COMM_PrintArray(             NAS_COMM_GET_LPP_PRINT_BUF(),\
                                         (VOS_UINT8 *)pMsg,\
                                         (pMsg->ulLength + NAS_LPP_MSG_HEADER_LENGTH));\
        NAS_LPP_NORM_LOG("====================================================");\
        if(VOS_OK != PS_SND_MSG_ALL_CHECK((PS_PID_LPP) , (pMsg)))\
            {\
                NAS_LPP_ERR_LOG("NAS_LPP_SND_MSG:Msg Snd Err!");\
            }\
    }

#define LPP_NV_Read( ulId, pItemData, usItemDataLen ) \
        LPs_NvimItem_Read( ulId, pItemData, usItemDataLen)


#define NAS_LPP_WRITE_EMM_MSG_HEAD(pstMsg, ulEmmLppMsgID)\
                    (pstMsg)->ulMsgId   = (ulEmmLppMsgID);\
                    (pstMsg)->ulSenderCpuId = VOS_LOCAL_CPUID;\
                    (pstMsg)->ulSenderPid = PS_PID_LPP;\
                    (pstMsg)->ulReceiverCpuId = VOS_LOCAL_CPUID;\
                    (pstMsg)->ulReceiverPid = PS_PID_MM;

#define NAS_LPP_INTER_WRITE_EMM_MSG_HEAD(pstMsg, ulLppInterMsgID)\
                    (pstMsg)->ulMsgId   = (ulLppInterMsgID);\
                    (pstMsg)->ulSenderCpuId = VOS_LOCAL_CPUID;\
                    (pstMsg)->ulSenderPid = PS_PID_LPP;\
                    (pstMsg)->ulReceiverCpuId = VOS_LOCAL_CPUID;\
                    (pstMsg)->ulReceiverPid = PS_PID_LPP;


#define NAS_LPP_WRITE_LRRC_MSG_HEAD(pstMsg, ulLrrcLppMsgID)\
                    (pstMsg)->enMsgId   = (ulLrrcLppMsgID);\
                    (pstMsg)->ulSenderCpuId = VOS_LOCAL_CPUID;\
                    (pstMsg)->ulSenderPid = PS_PID_LPP;\
                    (pstMsg)->ulReceiverCpuId = VOS_LOCAL_CPUID;\
                    (pstMsg)->ulReceiverPid = PS_PID_ERRC;

#define NAS_LPP_WRITE_INTRA_MSG_HEAD(pstMsg, ulIntraLppMsgID)\
                    (pstMsg)->enMsgId   = (ulIntraLppMsgID);\
                    (pstMsg)->ulSenderCpuId = VOS_LOCAL_CPUID;\
                    (pstMsg)->ulSenderPid = PS_PID_LPP;\
                    (pstMsg)->ulReceiverCpuId = VOS_LOCAL_CPUID;\
                    (pstMsg)->ulReceiverPid = PS_PID_LPP;

#define NAS_LPP_WRITE_MTA_MSG_HEAD(pstMsg, ulMtaLppMsgID)\
                    (pstMsg)->ulMsgId   = (ulMtaLppMsgID);\
                    (pstMsg)->ulSenderCpuId = VOS_LOCAL_CPUID;\
                    (pstMsg)->ulSenderPid = PS_PID_LPP;\
                    (pstMsg)->ulReceiverCpuId = VOS_LOCAL_CPUID;\
                    (pstMsg)->ulReceiverPid = UEPS_PID_MTA;

#define NAS_LPP_WRITE_LCS_MSG_HEAD(pstMsg, ulLcsLppMsgID)\
                    (pstMsg)->ulMsgId   = (ulLcsLppMsgID);\
                    (pstMsg)->ulSenderCpuId = VOS_LOCAL_CPUID;\
                    (pstMsg)->ulSenderPid =   PS_PID_LPP;\
                    (pstMsg)->ulReceiverCpuId = VOS_LOCAL_CPUID;\
                    (pstMsg)->ulReceiverPid = WUEPS_PID_LCS;

#define NAS_LPP_COMP_STATE(enLppMainState,enLppSubState)  ((((VOS_UINT32)enLppMainState)<<16)|(((VOS_UINT32)enLppSubState)&0xFFFF))
#define NAS_LPP_STATE_TBL_SIZE(astStateTbl)  ( sizeof(astStateTbl)/sizeof(NAS_LPP_FSM_ACT_STRU) )


typedef VOS_INT32 (*NAS_LPP_FSM_COMP_FUNC)(const VOS_VOID*, const VOS_VOID*);
typedef VOS_UINT32 (*NAS_LPP_ACTION_FUN)
(
    VOS_UINT32, /* 消息ID   */
    VOS_VOID *  /* 消息指针 */
);

typedef VOS_VOID (*NAS_LPP_TIMER_PROC_FUNC)(VOS_UINT8, VOS_UINT8, VOS_UINT8, VOS_VOID*);

#define NAS_LPP_MAX_SESSION_COUNT       (3) /*激活的最大的session的个数*/
#define NAS_LPP_MAX_TRANS_COUNT         (4) /*几个session中同时激活的最大的transaction的个数*/
#define NAS_LPP_MAX_TRANS_POOL_COUNT    (8) /*transaction实体池的个数*/
#define NAS_LPP_MAX_BUFF_MSG_COUNT      (8) /*上行最多可以缓存的LPP消息个数*/
#define NAS_LPP_MAX_BUFF_MSG_LEN        (1024)  /*可以缓存的单个LPP消息的最大长度??*/
#define NAS_LPP_MAX_LCS_ASSIST_DATA_BUFF_MSG_LEN        (235)  /*可以缓存的lcs的最大辅助数据buff的最大长度*/
#define NAS_LPP_MAX_RETRANS_COUNT       (3)
#define NAS_LPP_MAX_UP_MSG_PER_TRANSACTION  3
#define NAS_LPP_MAX_FSM_MSG_BUFF_POOL_COUNT         (4) /*状态机消息缓存池的个数*/
#define NAS_LPP_MAX_FSM_MSG_BUFF_LEN                (500) /*状态机消息缓存的长度*/
#define NAS_LPP_MAX_HIGH_FSM_MSG_BUFF_NUM           2
#define NAS_LPP_MAX_LOW_FSM_MSG_BUFF_NUM            2


#define LPP_MAX_MSG_CONTAINER_CNTNTS_LEN            (2048)
#define NAS_LPP_TRANS_END                           (1)
#define NAS_LPP_TRANS_NOT_END                       (0)
#define NAS_LPP_SEQUENCE_NUM_INVALID                (0xFFFE)
#define NAS_LMM_LPP_OPID_NOT_VAILID                 (0xFFFFFFFF)
#define NAS_LPP_TIMER_INVAILD_PARA                  (0xFF)
#define NAS_LPP_MAX_POS_TECH                        (3)
#define NAS_LPP_MIN_SND_MSG_LEN                     (4)
#define NAS_LPP_MSG_HEADER_LENGTH                   (20)
#define NAS_LPP_WAIT_GNSS_CAP_TIMER_LEN             (5000)
#define NAS_LPP_GNSS_LOC_INFO_INVALID_TIMER_LEN     (600000)

/*定时器时长*/
#ifdef PS_ITT_PC_TEST_NAS
#define TI_NAS_LPP_UPLINK_MSG_RETRANS_TIMER_LEN     (1000)      /*上行空口消息重传定时器时长*/
#define TI_NAS_LPP_WAIT_CN_ASSIST_DATA_TIMER_LEN    (5000)
#define TI_NAS_LPP_LOCATION_INVALID_TIMER_LEN       (NAS_LPP_GNSS_LOC_INFO_INVALID_TIMER_LEN)
#define TI_NAS_LPP_WAIT_LRRC_MEAS_CNF_TIMER_LEN     (500)
#define TI_NAS_LPP_WAIT_EST_CNF_TIMER_LEN           (5000)
#define TI_NAS_LPP_WAIT_RE_EST_TIMER_LEN            (2000)
#define TI_NAS_LPP_RESPONSE_TIMER_TIMER_LEN         (0)
#define TI_NAS_LPP_PERIODICAL_REPORT_TIMER_LEN      (0)
#define TI_NAS_LPP_REPORT_DURATION_TIMER_LEN        (0)
#define TI_NAS_LPP_WAIT_GNSS_CAP_TIMER_LEN          (NAS_LPP_WAIT_GNSS_CAP_TIMER_LEN)/* added by wangensheng */
#define TI_NAS_LPP_SEQUENCE_NUMBER_INVALID_LEN      (10*60*1000)
#else
#define TI_NAS_LPP_UPLINK_MSG_RETRANS_TIMER_LEN     (1000)      /*上行空口消息重传定时器时长*/
#define TI_NAS_LPP_WAIT_CN_ASSIST_DATA_TIMER_LEN    (5000)
#define TI_NAS_LPP_LOCATION_INVALID_TIMER_LEN       (NAS_LPP_GNSS_LOC_INFO_INVALID_TIMER_LEN)
#define TI_NAS_LPP_WAIT_LRRC_MEAS_CNF_TIMER_LEN     (500)
#define TI_NAS_LPP_WAIT_EST_CNF_TIMER_LEN           (5000)
#define TI_NAS_LPP_WAIT_RE_EST_TIMER_LEN            (2000)
#define TI_NAS_LPP_RESPONSE_TIMER_TIMER_LEN         (0)
#define TI_NAS_LPP_PERIODICAL_REPORT_TIMER_LEN      (0)
#define TI_NAS_LPP_REPORT_DURATION_TIMER_LEN        (0)
#define TI_NAS_LPP_WAIT_GNSS_CAP_TIMER_LEN          (NAS_LPP_WAIT_GNSS_CAP_TIMER_LEN)/* added by wangensheng */
#define TI_NAS_LPP_SEQUENCE_NUMBER_INVALID_LEN      (10*60*1000)
#endif


#define NAS_LPP_GET_MSG_LENGTH(pMsg)        ((pMsg)->ulLength)
#define NAS_LPP_GET_MSG_ENTITY(pMsg)        ((VOS_VOID*)&((pMsg)->ulMsgId))
#define NAS_LPP_GET_GNSS_CAP_MAX            (3)
#define NAS_LPP_OTDOA_CELL_MIN_NUM          (3)
#define NAS_LPP_IsReportInfinity(ucReportAmount)  ( (0 == ucReportAmount) ? PS_TRUE : PS_FALSE  )

/*****************************************************************************
  3 Massage Declare
*****************************************************************************/



/*****************************************************************************
  4 Enum
*****************************************************************************/

/*******************************************************************************
 枚举名    : NAS_LPP_ERROR_CODE_ENUM
 枚举说明  : LPP的错误原因之
 1.日    期   : 2015年07月06日
   作    者   :
   修改内容   :
*******************************************************************************/
enum NAS_LPP_ERROR_CODE_ENUM
{
    NAS_LPP_SUCCESS                     = 0,         /*LPP 模块函数返回成功*/
    NAS_LPP_FAILURE                        ,         /*LPP 模块函数返回失败*/
    NAS_LPP_MSG_DUPLICATE                  ,         /*消息 重复*/
    NAS_LPP_CONN_MANAGE_FAIL               ,         /*EMM发送上行LPP消息时，如果建立连接总是失败、或发生消息总是失败，lpp的连接管理模块给lpp消息的result取此值*/
    NAS_LPP_FSM_NOT_MATCH                  ,         /*消息和状态机状态不匹配*/
    NAS_LPP_MSG_PROCESS_CMPL               ,         /*lpp消息处理完成，无需继续*/
    NAS_LPP_MSG_VERIFY_SUCC                ,
    NAS_LPP_MSG_VERIFY_FAIL                ,
    NAS_LPP_MSG_VERIFY_HEAD_FAIL           ,
    NAS_LPP_MSG_VERIFY_COMMOM_BODY_REPORT_TYPE_ERROR,
    NAS_LPP_FSM_MSG_BUFF_EMPTY,
    NAS_LPP_ASSIST_DATA_CONFLICT,
};
typedef VOS_UINT32  NAS_LPP_ERROR_CODE_ENUM_UINT32;

/*******************************************************************************
 枚举名    : NAS_LPP_UPLINK_MSG_TYPE_ENUM
 枚举说明  : LPP上行消息类型
 1.日    期   : 2015年07月06日
   作    者   :
   修改内容   :
*******************************************************************************/
enum NAS_LPP_UPLINK_MSG_TYPE_ENUM
{
    NAS_LPP_UPLINK_MSG_TYPE_ACK             = 0,         /*上行消息是ACK消息*/
    NAS_LPP_UPLINK_MSG_TYPE_PROCESS         = 1,         /*LPP流程消息*/

    NAS_LPP_UPLINK_MSG_TYPE_BUTT,
};
typedef VOS_UINT32  NAS_LPP_UPLINK_MSG_TYPE_UINT32;

/*******************************************************************************
 枚举名    : NAS_LPP_MAIN_STATE_ENUM
 枚举说明  : LPP的主状态
 1.日    期   : 2015年07月06日
   作    者   : l00253982
   修改内容   : Added for LPP
*******************************************************************************/
enum    NAS_LPP_MAIN_STATE_ENUM
{
    /*=================== EMM的主状态 ===================*/
    LPP_MS_IDLE                         = 0, /*当前没有任何LPP流程*/
    LPP_MS_CAPABILITY                   = 1, /*能力交换流程*/
    LPP_MS_ASSISTDATA                   = 2, /*辅助传输流程*/
    LPP_MS_LOCATION                     = 3, /*位置信息传输流程*/

    LPP_MS_BUTT
};
typedef VOS_UINT32  NAS_LPP_MAIN_STATE_ENUM_UINT32;

/*******************************************************************************
 枚举名    : NAS_LPP_SUB_STATE_ENUM
 枚举说明  : LPP的子状态

     注意:  g_astLppSubStateTime和g_astNasLppFsm两个表格的单元项与此子状态的定义先后顺序
            强相关，不要随意修改子状态的顺序、或在已有子状态中间插入定义新子状态(在最后面增加新的子状态定义)。
            如果在中间插入新定义了子状态，不要忘记修改以上的两个表。

 1.日    期   : 2015年07月06日
   作    者   : l00253982
   修改内容   : Added for LPP
*******************************************************************************/
enum    NAS_LPP_SUB_STATE_ENUM
{

    /*===================LPP_MS_IDLE子状态===================*/
    LPP_SS_IDLE                             = 0, /*表示当前没有任何LPP流程*/

    /*==================LPP_MS_CAPABILITY子状态==============*/
    LPP_SS_CAP_REQ_WAIT_CNF                 = 1, /*表示能力交互过程中等GNSS回复能力*/
    LPP_SS_CAP_PRIVIDE_WAIT_CN_ACK          = 2, /*表示提供给网络能力等网侧ACK*/
    LPP_SS_CAP_WAIT_ABORT_CN_ACK            = 3, /*表示能力transaction abort之后等网侧回复ack*/

    /*==================LPP_MS_ASSISTDATA子状态==============*/
    LPP_SS_ASSISTDATA_REQ_WAIT_CN_ACK       = 4, /*表示请求网侧辅助数据等网侧ACK*/
    LPP_SS_ASSISTDATA_WAIT_CN_CNF           = 5, /*表示等网侧辅助数据回复*/
    LPP_SS_ASSISTDATA_WAIT_ABORT_CN_ACK     = 6, /*表示辅助数据过程等网络侧abort回复ACK*/

    /*==================LPP_MS_LOCATION子状态================*/
    LPP_SS_WAIT_ASSISTDATA_RCV_CMP          = 7, /*表示等待接收辅助数据完成,表示当前有正在进行中的辅助数据流程*/
    LPP_SS_WAIT_ASSISTDATA_REQ_PROCESS_CMP  = 8, /*表示等待辅助数据请求流程完成,表示当前没有辅助数据，需要等起一个新的transaction申请辅助数据*/
    LPP_SS_WAIT_LRRC_MEAS_CNF               = 9, /*表示等待LRRC测量回复*/
    LPP_SS_WAIT_RELEASE_LRRC_MEAS_CNF       = 10,
    LPP_SS_WAIT_LOCATION_CN_ACK             = 11,/*表示等待位置提供信息的ACK回复*/
    LPP_SS_WAIT_LOCATION_ABORT_CN_ACK       = 12,/*表示等待位置请求流程abort，网络侧的ACK回复*/

    LPP_SS_WAIT_INTRA_DATA_CNF              = 13, /*发送data req后，等待LPP 的连接管理模块回复DATA CNF的消息*/
    LPP_SS_WAIT_INTRA_DATA_CNF_OF_UP_LPP_ACK= 14, /*发送LPP ACK的data req后，等待LPP 的连接管理模块回复DATA CNF的消息*/
    LPP_SS_WAIT_MEAS_IND                    = 15, /*表示当前等待LRRC，GNSS的测量回复*/


    LPP_SS_BUTT
};
typedef VOS_UINT32  NAS_LPP_SUB_STATE_ENUM_UINT32;

/*******************************************************************************
 枚举名    : NAS_LPP_UP_STATE_STATE_ENUM
 枚举说明  : LPP的状态
 1.日    期   : 2015年11月24日
   作    者   : l00253982
   修改内容   : Added for LPP
*******************************************************************************/
enum  NAS_LPP_UP_STATE_STATE_ENUM
{
    LPP_UP_STATE_IDLE                             = 0, /*表示当前没有任何LPP流程*/
    LPP_UP_STATE_ASSISTDATA_WAIT_CN_CNF           = 1, /*表示等MTA OTDOA辅助数据回复*/
    LPP_UP_STATE_WAIT_LRRC_ECID_MEAS_CNF          = 2, /*表示等待LRRC ECID的测量回复*/
    LPP_UP_STATE_WAIT_LRRC_OTDOA_MEAS_CNF         = 3, /*表示等待LRRC OTDOA的测量回复*/
    LPP_UP_STATE_WAIT_LRRC_MEAS_IND               = 4, /*表示当前等待LRRC的测量回复*/

    LPP_UP_STATE_BUTT
};
typedef VOS_UINT32  NAS_LPP_UP_STATE_ENUM_UINT32;

/*******************************************************************************
 枚举名    : NAS_LPP_SUB_STATE_ENUM
 枚举说明  : LPP的子状态
 1.日    期   : 2015年07月06日
   作    者   :
   修改内容   :
*******************************************************************************/
enum    NAS_LPP_AIR_MSG_ENUM
{
    /*上行的*/
    NAS_LPP_AIR_MSG_PROVIDE_CAP  = 0,
    NAS_LPP_AIR_MSG_REQUEST_ASSIST_DATA,
    NAS_LPP_AIR_MSG_PROVIDE_LOCATION_INFO,
    NAS_LPP_AIR_MSG_UP_ERR,
    NAS_LPP_AIR_MSG_UP_ABORT,
    NAS_LPP_AIR_MSG_UP_LPP_ACK,

    /*下行的*/
    NAS_LPP_AIR_MSG_REQUEST_CAP,
    NAS_LPP_AIR_MSG_PROVIDE_ASSIST_DATA,
    NAS_LPP_AIR_MSG_REQUEST_LOCATION_INFO,
    NAS_LPP_AIR_MSG_DOWN_ERR,
    NAS_LPP_AIR_MSG_DOWN_ABORT,

    NAS_LPP_AIR_MSG_BUTT
};
typedef VOS_UINT32  NAS_LPP_AIR_MSG_ENUM_UINT32;

/*******************************************************************************
 枚举名    : NAS_LPP_SUB_STATE_ENUM
 枚举说明  : LPP所有使用的定时器
             上报优先级是周期性上报>只上报一次>条件触发方式，如果下行请求位置
             信息的时候，发现上面三种上报方式任意两种或者3中同时从网络侧带下来，
             那么UE需要忽略优先级低的上报方式

   注意: 这个定义的定义与g_astLppSubStateTime和g_afNasLppStateTimerFun/g_afNasLppNoneStateTimerFun表强相关。新定义最好在最后面增加，
   不要在中间插入增加新的定时器名字。修改后，不要忘了修改上面的两个表格。

 1.日    期   : 2015年07月06日
   作    者   : l00253982
   修改内容   : Added for LPP
*******************************************************************************/
enum NAS_LPP_TIMER_PARA_ENUM
{
/*------------------------------------------状态机对应的定时器--------------------------------------*/
    /*-------状态定时器，存在于transaction中----------------------*/
    TI_NAS_LPP_MSG_TIMER_NULL           = 0,
    TI_NAS_LPP_UPLINK_MSG_RETRANS       = 1,    /*LPP发送的上行空口的重传定时器*/
    TI_NAS_LPP_WAIT_CN_ASSIST_DATA      = 2,    /*等网络侧下发辅助数据定时器*/
    TI_NAS_LPP_WAIT_LRRC_MEAS_CNF       = 3,    /*等待LRRC 测量回复*/

    TI_NAS_LPP_WAIT_GNSS_CAP_CNF        = 4,    /*等待gnss回复能力*/
    TI_NAS_LPP_WAIT_INTRA_DATE_CNF      = 5,    /*等待内部DataCnf消息*/


    /*-------连接管理维护的定时器，存在这个LPP的entity中------------*/
    TI_NAS_LPP_WAIT_EST_CNF             = 6,   /*等待LMM建链路回复*/
    TI_NAS_LPP_WAIT_RE_EST              = 7,   /*重建连定时器*/
    TI_NAS_LPP_SEQUENCE_NUMBER_INVALID  = 8,   /*sequence Number是否有效定时器*/

    /* 其他的状态定时器增加到这里，TI_NAS_LPP_STATE_TIMER_MAX_NUM之前 */
    TI_NAS_LPP_UP_STATE_TIMER_START_NUM,
    TI_NAS_LPP_UP_WAIT_CN_ASSIST_DATA   = TI_NAS_LPP_UP_STATE_TIMER_START_NUM,    /*用户面等网络侧下发辅助数据定时器*/
    TI_NAS_LPP_UP_WAIT_LRRC_ECID_MEAS_CNF  ,    /*等待LRRC ECID测量回复*/
    TI_NAS_LPP_UP_WAIT_LRRC_OTDOA_MEAS_CNF ,    /*等待LRRC OTDOA测量回复*/

    TI_NAS_LPP_STATE_TIMER_MAX_NUM         ,
/*------------------------------------------非状态机对应的定时器--------------------------------------*/
    /*-------上报位置信息的协议定时器，存在于session中------------*/
    TI_NAS_LPP_RESPONSE_TIMER = TI_NAS_LPP_STATE_TIMER_MAX_NUM ,    /*如果只报一次的响应时间*/
    TI_NAS_LPP_PERIODICAL_REPORT           ,    /*周期性上报的时间间隔*/
    TI_NAS_LPP_REPORT_DURATION             ,    /*条件上报上报持续的最大时间*/

    /*-------GPS位置信息是否有效的定时器---------------------------*/
    TI_NAS_LPP_LOCATION_INVALID            ,    /*位置信息无效定时器*/

    TI_NAS_LPP_PTC_TIMER_MAX_NUM         ,      /*协议定时器最大的边界值*/
    /*-------用户面定位技术使用到了定时器--------------------------*/
    TI_NAS_LPP_UP_RESPONSE_TIMER = TI_NAS_LPP_PTC_TIMER_MAX_NUM,  /*用户面如果只报一次的响应时间*/
    TI_NAS_LPP_UP_PERIODICAL_REPORT           ,    /*用户面周期性上报的时间间隔*/
    TI_NAS_LPP_UP_REPORT_DURATION             ,    /*用户面条件上报上报持续的最大时间*/

    TI_NAS_LPP_TIMER_PARA_BUTT
};
typedef VOS_UINT8   NAS_LPP_TIMER_PARA_ENUM_UINT8;

/*******************************************************************************
 枚举名    : NAS_LPP_CONN_STATUS_ENUM
 枚举说明  : LPP的连接状态
 1.日    期   : 2015年07月06日
   作    者   : l00253982
   修改内容   : Added for LPP
*******************************************************************************/
enum NAS_LPP_CONN_STATUS_ENUM
{
    NAS_LPP_CONN_STATUS_IDLE            = 0,    /*LPP当前处于空闲态*/
    NAS_LPP_CONN_STATUS_CONNECT         = 1,    /*LPP当前处于连接态*/
    NAS_LPP_CONN_STATUS_ESTING          = 2,    /*LPP当前处于建链过程中*/

    NAS_LPP_CONN_STATUS_BUTT
};
typedef VOS_UINT32   NAS_LPP_CONN_STATUS_ENUM_UINT32;

/*******************************************************************************
 枚举名    : NAS_LPP_REPORT_LOCATION_TYPE_ENUM
 枚举说明  : LPP上报位置信息的方式
 1.日    期   : 2015年07月06日
   作    者   : lifuxin 00253982
   修改内容   : Added for LPP
*******************************************************************************/

enum NAS_LPP_REPORT_LOCATION_TYPE_ENUM
{
    NAS_LPP_REPORT_LOCATION_TYPE_TRIGGER            = 0,/*条件触发上报*/
    NAS_LPP_REPORT_LOCATION_TYPE_PERIOD             = 1,/*周期性上报*/
    NAS_LPP_REPORT_LOCATION_TYPE_ONCE               = 2,/*上报一次*/

    NAS_LPP_REPORT_LOCATION_TYPE_BUTT
};
typedef VOS_UINT8 NAS_LPP_REPORT_LOCATION_TYPE_ENUM_UINT8;

/*******************************************************************************
 枚举名    : NAS_LPP_POSITION_TECH_ENUM
 枚举说明  : LPP定位记数枚举
 1.日    期   : 2015年07月06日
   作    者   : lifuxin 00253982
   修改内容   : Added for LPP
*******************************************************************************/

enum NAS_LPP_POSITION_TECH_ENUM
{
    NAS_LPP_POSITION_TECH_NULL                      = 0,/*当前结构没有被占用*/
    NAS_LPP_POSITION_TECH_ECID                      = 1,/*ECID的上报技术*/
    NAS_LPP_POSITION_TECH_OTDOA                     = 2,/*OTDOA的定位技术*/
    NAS_LPP_POSITION_TECH_GNSS                      = 3,/*GNSS的定位技术*/

    NAS_LPP_POSITION_TECH_BUTT
};
typedef VOS_UINT8 NAS_LPP_POSITION_TECH_ENUM_UINT8;

/*******************************************************************************
 枚举名    : NAS_LPP_POSITION_TECH_ENUM
 枚举说明  : LPP定位记数枚举
 1.日    期   : 2015年07月06日
   作    者   : lifuxin 00253982
   修改内容   : Added for LPP
*******************************************************************************/

enum NAS_LPP_BUFF_FSM_MSG_PRIORITY_ENUM
{
    NAS_LPP_BUFF_FSM_MSG_PRIORITY_HIGH,
    NAS_LPP_BUFF_FSM_MSG_PRIORITY_LOW,
    NAS_LPP_BUFF_FSM_MSG_PRIORITY_BUTT
};
typedef VOS_UINT8 NAS_LPP_BUFF_FSM_MSG_PRIORITY_ENUM_UINT8;

/*******************************************************************************
 枚举名    : NAS_LPP_POSITION_PROCESS_TYPE_ENUM
 枚举说明  : 记录当前定位流程是用户面还是控制面
 1.日    期   : 2015年11月20日
   作    者   : lifuxin 00253982
   修改内容   : Added for LPP
*******************************************************************************/
enum NAS_LPP_POSITION_PROCESS_TYPE_ENUM
{
    NAS_LPP_POSITION_PROCESS_TYPE_NULL,
    NAS_LPP_POSITION_PROCESS_TYPE_CONTROL_PLANE,
    NAS_LPP_POSITION_PROCESS_TYPE_USER_PLANE,
    NAS_LPP_POSITION_PROCESS_TYPE_BUTT
};
typedef VOS_UINT8 NAS_LPP_POSITION_PROCESS_TYPE_ENUM_UINT8;

/*******************************************************************************
 枚举名    : NAS_LPP_UP_POS_REQ_TECH_TYPE_ENUM
 枚举说明  : 记录用户面当前请求的是哪一种定位技术
 1.日    期   : 2015年11月20日
   作    者   : lifuxin 00253982
   修改内容   : Added for LPP
*******************************************************************************/
enum NAS_LPP_UP_POS_REQ_TECH_TYPE_ENUM
{
    NAS_LPP_UP_POS_REQ_TECH_TYPE_NULL,
    NAS_LPP_UP_POS_REQ_TECH_TYPE_ECID,
    NAS_LPP_UP_POS_REQ_TECH_TYPE_OTDOA,
    NAS_LPP_UP_POS_REQ_TECH_TYPE_ECID_AND_OTDOA,
    NAS_LPP_UP_POS_REQ_TECH_TYPE_BUTT
};
typedef VOS_UINT8 NAS_LPP_UP_POS_REQ_TECH_TYPE_ENUM_UINT8;


/*****************************************************************************
  5 STRUCT
*****************************************************************************/
/*******************************************************************************
 结构名    : NAS_LPP_FSM_ACT_STRU
 结构说明  : NAS_LPP_FSM_ACT_STRU
 1.日    期   : 2015年07月06日
   作    者   :Xiaojun
*******************************************************************************/

typedef struct
{
    VOS_UINT32                          ulSendPid;
    VOS_UINT32                          ulMsgId;
#if 0
    NAS_LPP_ACTION_FUN                  pfActionFun;   /* 动作函数 */
#endif
}NAS_LPP_FSM_ACT_STRU;

/*******************************************************************************
 结构名    :
 结构说明  : NAS_LPP_FSM_STRU
 1.日    期   : 2015年07月06日
   作    者   :Xiaojun
*******************************************************************************/

typedef struct
{
    VOS_UINT32                          ulState;
    VOS_UINT32                          ulSize;     /*NAS_LPP_FSM_ACT_STRU的个数*/
    NAS_LPP_FSM_ACT_STRU               *pfFsmActTbl;
}NAS_LPP_FSM_STRU;

/*******************************************************************************
 结构名    :
 结构说明  : LPP-TransactionID
 1.日    期   : 2015年07月06日
   作    者   :Xiaojun
*******************************************************************************/
typedef struct
{
    NAS_LPP_SUB_STATE_ENUM_UINT32       enLppSubState;
    NAS_LPP_TIMER_PARA_ENUM_UINT8       enTimeName;
    VOS_UINT8                           aucRsv[3];
}NAS_LPP_SUB_STATE_TIME_STRU;


/*******************************************************************************
 结构名    :
 结构说明  : LPP-TransactionID
 1.日    期   : 2015年07月06日
   作    者   :
*******************************************************************************/
typedef struct
{
    LPP_INITIATOR_TYPE_ENUM_UINT8       enInitiator;
    VOS_UINT8                           ucTransactionNumber;
    VOS_UINT8                           aucRes[2];
}NAS_LPP_TRANS_ID_STRU;

/*******************************************************************************
 结构名    : NAS_LPP_MSG_IDENTITY_STRU
 结构说明  : 唯一识别一条LPP消息的结构
 1.日    期   : 2015年07月06日
   作    者   : l00253982
   修改内容   : Added for LPP
*******************************************************************************/
typedef struct
{
    VOS_UINT32                          ulSessionId;        /*会话ID，组包上行generic消息需要使用*/
    VOS_UINT16                          usSequnceNum;       /*当前会话发送使用上行的消息的消息计数*/
    VOS_UINT8                           aucRsv[2];
    NAS_LPP_TRANS_ID_STRU               stTransId;          /*Transaction的标识*/
    NAS_LPP_UPLINK_MSG_TYPE_UINT32      enUplinkMsgType;    /*上行消息类型*/
    VOS_BOOL                            bIsProvideLocFalg;   /*表示该条存储消息是否是provideLocation消息*/
}NAS_LPP_MSG_IDENTITY_STRU;

/*******************************************************************************
 结构名    : NAS_LPP_TIMER_STRU
 结构说明  : LPP单个transaction运行的定时器
 1.日    期   : 2015年07月06日
   作    者   : l00253982
   修改内容   : Added for LPP
*******************************************************************************/
typedef struct
{
    HTIMER                                  hTimer;             /* vos分配的Timer Id */
    NAS_LPP_TIMER_PARA_ENUM_UINT8           enTimerId;          /* Timer类型*/
    VOS_UINT8                               aucReserve1[3];     /* 四字节对齐，保留 */
    VOS_UINT32                              ulPara;             /* 定时器需要传入的参数*/
}NAS_LPP_TIMER_STRU;
/*******************************************************************************
 结构名    : NAS_LPP_CAP_REQ_STRU
 结构说明  : LPP下行能力请求缓存
 1.日    期   : 2015年08月04日
   作    者   : l00253982
   修改内容   : Added for LPP
*******************************************************************************/
typedef struct
{
    VOS_UINT32                              bitOpAgnssCapReq    :1;
    VOS_UINT32                              bitOpOtdoaCapReq    :1;
    VOS_UINT32                              bitOpEcidCapReq     :1;
    VOS_UINT32                              bitOpSpare          :29;

    LPP_AGNSS_REQ_CAP_STRU                  stGnssReqCap;
}NAS_LPP_CAP_REQ_STRU;
/*******************************************************************************
 结构名    : NAS_LPP_FSM_MSG_BUFF_POOL_STRU
 结构说明  :
 1.日    期   : 2015年07月06日
   作    者   : xiaojun
   修改内容   : Added for LPP
*******************************************************************************/
typedef struct
{
    VOS_UINT32                              ulSenderPid;
    VOS_UINT32                              ulMsgId;
    VOS_VOID                               *pMsg;
}NAS_LPP_FSM_MSG_BUFF_STRU;

/*******************************************************************************
 结构名    : NAS_LPP_FSM_MSG_BUFF_STRU
 结构说明  :
 1.日    期   : 2015年08月04日
   作    者   :
   修改内容   : Added for LPP
*******************************************************************************/
typedef struct
{
    VOS_UINT8                               ucHighNum;
    VOS_UINT8                               aucRsv[3];
    NAS_LPP_FSM_MSG_BUFF_STRU               astHighMsg[NAS_LPP_MAX_HIGH_FSM_MSG_BUFF_NUM];

    VOS_UINT8                               ucLowNum;
    VOS_UINT8                               aucRsv1[3];
    NAS_LPP_FSM_MSG_BUFF_STRU               astLowMsg[NAS_LPP_MAX_LOW_FSM_MSG_BUFF_NUM];
}NAS_LPP_FSM_BUFF_STRU;

/*******************************************************************************
 结构名    : NAS_LPP_TRANSACTION_ELEMENT_ENTIYT_STRU
 结构说明  : LPP单个transaction的实体结构
 1.日    期   : 2015年07月06日
   作    者   : l00253982
   修改内容   : Added for LPP
*******************************************************************************/
typedef struct
{
    VOS_UINT32                              bitOpWaitEcidMeasCnf    :1;
    VOS_UINT32                              bitOpWaitOtdoaMeasCnf   :1;
    VOS_UINT32                              bitOpOtdoaAssistReq     :1;
    VOS_UINT32                              bitOpSpare:29;

    NAS_LPP_TRANS_ID_STRU                   stTransId;              /*transaction ID*/
    NAS_LPP_MAIN_STATE_ENUM_UINT32          enLppMainState;         /*表示当前transaction的主状态*/
    NAS_LPP_SUB_STATE_ENUM_UINT32           enLppSubState;          /*表示当前transaction的子状态*/
    NAS_LPP_TIMER_STRU                      stLppTimer;             /*单个transaction running的定时器*/
    NAS_LPP_AIR_MSG_ENUM_UINT32             enLastUpMsgId;          /*发送的最新的上行LPP消息*/
    VOS_UINT8                               ucRetranNum;            /*重传次数*/
    VOS_UINT8                               ucTransEndFlag;         /*表示该transaction是否结束*/
    VOS_UINT8                               ucCommCfgIndex;         /*表示存储的本transactio位置请求相关的配置信息的索引*/
    VOS_UINT8                               aucRsv[1];

    /*缓存的空口request capability info里 的参数,返回provide capabilities information使用*/
    NAS_LPP_CAP_REQ_STRU                    stCapReq;

    NAS_LPP_FSM_BUFF_STRU                   stFsmBuff;
}NAS_LPP_TRANSACTION_ELEMENT_ENTITY_STRU;

/*******************************************************************************
 结构名    : NAS_LPP_MSG_HEAD_STRU
 结构说明  : LPP消息头结构
 1.日    期   : 2015年08月04日
   作    者   : l00253982
   修改内容   : Added for LPP
*******************************************************************************/
typedef struct
{
    VOS_UINT32                              bitOpLppTransactionId:1;
    VOS_UINT32                              bitOpSequenceNumber:1;
    VOS_UINT32                              bitOpAcknowledgement:1;
    VOS_UINT32                              bitOpLppMessageBody:1;
    VOS_UINT32                              bitOpSpare:28;

    LPP_TRANSACTION_ID_STRU                 stTransactionId;
    VOS_BOOL                                bEndTransaction;
    LPP_SEQUENCE_NUMBER_STRU                stSequenceNumber;
    LPP_ACKNOWLEDGEMENT_STRU                stAcknowledgement;
}NAS_LPP_MSG_HEAD_STRU;

/*******************************************************************************
 结构名    : NAS_LPP_SESSION_ENTITY_ELEMENT_STRU
 结构说明  : LPP会话中transaction的实体结构
 1.日    期   : 2015年07月06日
   作    者   : l00253982
   修改内容   : Added for LPP
*******************************************************************************/
typedef struct
{
    VOS_UINT8                                   ucTransIdCount;         /*表示当前会话中running的transaction的总数*/
    VOS_UINT8                                   aucRsv[3];

    /*表示transaction实体在transaction element entity pool里的索引*/
    VOS_UINT8                                   aucTransElementIdx[NAS_LPP_MAX_TRANS_COUNT];
}NAS_LPP_TRANSACTION_STRU;

/*******************************************************************************
 结构名    : NAS_LPP_SESSION_ENTITY_ELEMENT_STRU
 结构说明  : LPP会话中transaction的实体结构
 1.日    期   : 2015年07月06日
   作    者   : l00253982
   修改内容   : Added for LPP
*******************************************************************************/
typedef struct
{
    /*对应bit 1:对应的transaction实体被使用； 对应bit 0:对应的transaction实体未使用*/
    VOS_UINT32                                  ulTransBitmap;

    /*表示单一transaction实体*/
    NAS_LPP_TRANSACTION_ELEMENT_ENTITY_STRU     astTransElementEntity[NAS_LPP_MAX_TRANS_POOL_COUNT];
}NAS_LPP_TRANSACTION_ENTITY_POOL_STRU;

/*******************************************************************************
 结构名    : NAS_LPP_REPORT_LOCATION_TYPE_TRIGGER_STRU
 结构说明  : 条件触发上报方式维护的全局信息
 1.日    期   : 2015年07月06日
   作    者   : l00253982
   修改内容   : Added for LPP
*******************************************************************************/
typedef struct
{

    VOS_UINT32                                  ulReportDuration;   /*上报持续的时间*/
    NAS_LPP_TIMER_STRU                          stLppTimer;         /*上报持续时间定时器*/
}NAS_LPP_REPORT_LOCATION_TYPE_TRIGGER_STRU;

/*******************************************************************************
 结构名    : NAS_LPP_REPORT_LOCATION_TYPE_PERIOD_STRU
 结构说明  : 周期性上报方式维护的全局信息
 1.日    期   : 2015年07月06日
   作    者   : l00253982
   修改内容   : Added for LPP
*******************************************************************************/
typedef struct
{
    VOS_UINT8                                   ucReportAmount;     /*要求上报的总的计数*/
    VOS_UINT8                                   ucReportingAmount;  /*已经上报的的计数*/
    LPP_LRRC_OTDOA_RPRT_INTERVAL_ENUM_UINT16    enOtdoaRprtInterval;/*上报的时间间隔，只在配置LRRC时使用*/
    VOS_UINT32                                  ulReportIntraval;   /*上报的时间间隔*/
    NAS_LPP_TIMER_STRU                          stLppTimer;         /*周期性上报定时器*/
}NAS_LPP_REPORT_LOCATION_TYPE_PERIOD_STRU;

/*******************************************************************************
 结构名    : NAS_LPP_REPORT_LOCATION_TYPE_ONCE_STRU
 结构说明  : 上报一次维护的全局信息
 1.日    期   : 2015年07月06日
   作    者   : l00253982
   修改内容   : Added for LPP
*******************************************************************************/
typedef struct
{
    VOS_UINT32                                  ulResponseTime;     /*response time时长*/
    NAS_LPP_TIMER_STRU                          stLppTimer;         /*上报一次定时器*/
}NAS_LPP_REPORT_LOCATION_TYPE_ONCE_STRU;

/*******************************************************************************
 结构名    : NAS_LPP_REPORT_CRITERIA_STRU
 结构说明  : lpp上报位置信息的方式
 1.日    期   : 2015年07月06日
   作    者   : l00253982
   修改内容   : Added for LPP
*******************************************************************************/
typedef struct
{
    NAS_LPP_REPORT_LOCATION_TYPE_ENUM_UINT8     enType;
    VOS_UINT8                                   ucSessionIndex;
    VOS_UINT8                                   ucSessionTransIndex;
    VOS_UINT8                                   ucRsv;

    union
    {
        NAS_LPP_REPORT_LOCATION_TYPE_TRIGGER_STRU   stReportTrigger;
        NAS_LPP_REPORT_LOCATION_TYPE_PERIOD_STRU    stReportPeriod;
        NAS_LPP_REPORT_LOCATION_TYPE_ONCE_STRU      stReportOnce;
    }u;
}NAS_LPP_REPORT_CRITERIA_STRU;

/*******************************************************************************
 结构名    : NAS_LPP_SESSION_ENTITY_ELEMENT_STRU
 结构说明  : LPP单个会话的实体结构
 1.日    期   : 2015年07月06日
   作    者   : l00253982
   修改内容   : Added for LPP
*******************************************************************************/
typedef struct
{
    VOS_UINT32                                      ulSessionId;            /*当前会话的ID*/
    PS_BOOL_ENUM_UINT8                              enRcvedDownMsg;
    VOS_UINT8                                       ucLastDownSequenceNum;  /*当前会话收到的最新的下行LPP消息的sequence number*/
    VOS_UINT8                                       aucRsv[2];
    NAS_LPP_TIMER_STRU                              stSequenceNumInvalid;   /*表示在session可见的定时器，目前用于sequenceNumber是否有效维护使用*/

    NAS_LPP_TRANSACTION_STRU                        stLppTrans;             /*一个会话中的所有transaction实体*/
}NAS_LPP_SESSION_ENTITY_ELEMENT_STRU;

/*******************************************************************************
 结构名    : NAS_LPP_SESSION_ENTITY_STRU
 结构说明  : LPP会话实体的结构
 1.日    期   : 2015年07月06日
   作    者   : l00253982
   修改内容   : Added for LPP
*******************************************************************************/
typedef struct
{
    VOS_UINT32                                      ulSessionActiveBitmap;  /*当前SESSION的状态:对应bit为1，对应的session实体被使用；对应bit为0，对应的实体未被使用*/
    NAS_LPP_SESSION_ENTITY_ELEMENT_STRU             astLppSessionEntity[NAS_LPP_MAX_SESSION_COUNT]; /*单一会话实体*/
    /*维护一个标识去标识当前有没有各种定位技术的辅助信息*/

}NAS_LPP_SESSION_ENTITY_POOL_STRU;

/*****************************************************************************
 结构名    : LPP_UPLINK_MSG_BUF_STRU
 结构说明  : LPP_UPLINK_MSG_BUF_STRU数据结构
 作者      : lifuxin 00253982 2015-07-02 新开发
 功能点描述: 上行缓存buffer存储的数据结构，每一个buffer包含LPP消息的IDENTIY，
             以及具体的直传消息实体，这样定义的好处是操作每一个buffer的时候
             都知道是哪一个session中哪一个transaction的哪一条空口消息，这样
             就可以动态的维护指定的buffer。
*****************************************************************************/
typedef struct
{
    NAS_LPP_MSG_IDENTITY_STRU           stLppMsgIdentity;    /*一条LPP消息的唯一的身份识别*/
    VOS_BOOL                            bSendBufFlag;        /*表示该buffer的缓存消息是否已经发送成功到了网侧，非ACK*/

    union
    {
        LPP_LMM_DATA_REQ_STRU           stLppDataReq;       /*LPP发往LMM的直传消息*/
        VOS_UINT8                       aucLppMsg[NAS_LPP_MAX_BUFF_MSG_LEN];
    } u;
}LPP_UPLINK_MSG_BUF_STRU;

/*******************************************************************************
 结构名    : NAS_LPP_CONN_MANAGE_STRU
 结构说明  : LPP连接管理数据结构
 功能点描述: 有上行空口要发，如果当前为IDLE， 则跟LMM发起建链，建链同时，将对应
             发给LMM的直传消息放到缓存列表中去，有两种结果，一是建链成功，则依次
             取出缓存中的直传消息发送DATA REQ给LMM，二是建链失败，则启动重建链定
             时器，定时器超时后，则重新发起建链，现阶段暂时重建链一次即可，如果
             还是失败，则依次根据缓存中sessionID和transactionID找到对应transaction，
             将对应的资源清空，终止定位流程。

             直传有两个地方会用到:
             1. 建链成功之后，立即去待发送缓存列表中依次去取对应的消息发送给LMM
             2. 当前链路存在，直接组包直传消息，发送给LMM，同时将该上行消息也放到缓存
             队列中去
             上面两种情况，只要发送成功之后，则将对应buffer的指针设置成NULL， 并且发
             送一条内部消息到transaction中通知需要启动重传定时器，如果发送失败，则
             启动重建链定时器，定时器超时之后再次发起建链，回到上面建链的逻辑中去。

 1.日    期   : 2015年07月06日
   作    者   : l00253982
   修改内容   : Added for LPP

*******************************************************************************/
typedef struct
{
    NAS_LPP_CONN_STATUS_ENUM_UINT32         enConectStatus;                                 /*表示当前的连接状态*/
    VOS_UINT32                              ulEstOrDataCnt;                                 /*建链或者直传尝试次数，初步实现如果建链失败，则重传一次*/
    NAS_LPP_TIMER_STRU                      stLppTimer;                                     /*连接管理中正在running的定时器*/
}NAS_LPP_CONN_MANAGE_STRU;

/*******************************************************************************
 结构名    : NAS_LPP_UP_MSG_BUFF_SEARCH_RSLT_STRU
 结构说明  : 上行buffer的内存池搜的结果
 1.日    期   : 2015年07月06日
   作    者   : l00253982
   修改内容   : Added for LPP
*******************************************************************************/
typedef struct
{
    VOS_UINT8                               ucNum;
    VOS_UINT8                               aucIndex[NAS_LPP_MAX_UP_MSG_PER_TRANSACTION];
}NAS_LPP_UP_MSG_BUFF_SEARCH_RSLT_STRU;

/*******************************************************************************
 结构名    : NAS_LPP_UP_MSG_SEQUENCE_STRU
 结构说明  : 上行buffer的按先后顺序存储索引结构
 1.日    期   : 2015年07月06日
   作    者   : l00253982
   修改内容   : Added for LPP
*******************************************************************************/
typedef struct
{
    VOS_UINT8               ucUsedFlag;         /*是否被占用flag*/
    VOS_UINT8               ucUpLinkBuffIndex;  /*上行缓存buffer的索引*/
}NAS_LPP_UP_MSG_SEQUENCE_STRU;

/*******************************************************************************
 结构名    : NAS_LPP_UP_MSG_BUFF_POOL_STRU
 结构说明  : 上行buffer的内存池
 1.日    期   : 2015年07月06日
   作    者   : l00253982
   修改内容   : Added for LPP
*******************************************************************************/
typedef struct
{
    NAS_LPP_UP_MSG_SEQUENCE_STRU            astUpmsgSeq[NAS_LPP_MAX_BUFF_MSG_COUNT];
    VOS_UINT32                              ulBitMap;
    LPP_UPLINK_MSG_BUF_STRU                 astLppUpMsg[NAS_LPP_MAX_BUFF_MSG_COUNT];
}NAS_LPP_UP_MSG_BUFF_POOL_STRU;

/*******************************************************************************
 结构名    : NAS_LPP_LOC_TECH_MAP_STRU
 结构说明  : 定位技术和session间的映射关系
 1.日    期   : 2015年07月06日
   作    者   : l00253982
   修改内容   : Added for LPP
*******************************************************************************/
typedef struct
{
    NAS_LPP_POSITION_TECH_ENUM_UINT8        enPositionTech;     /*定位技术*/
    VOS_UINT8                               ucSessionIndx;      /*正在running的定位技术对应的sessionIndx*/
    VOS_UINT8                               ucSessionTranIndx;  /*正在running的定位技术对应的数组下标*/
    VOS_UINT8                               ucTransIndx;        /*正在running的定位技术对应的transaction内存池中的索引*/
}NAS_LPP_LOC_TECH_MAP_STRU;
/*******************************************************************************
 结构名    : NAS_LPP_LOC_TECH_RUNING_STRU
 结构说明  : 记录当前发起位置请求流程的session transactionID等，方便
             LRRC回复测量IND之后，能知道是哪一个实体发起的流程
 1.日    期   : 2015年07月06日
   作    者   : l00253982
   修改内容   : Added for LPP
*******************************************************************************/
typedef struct
{
    VOS_UINT8                               ucNum;
    VOS_UINT8                               aucRsv[3];
    NAS_LPP_LOC_TECH_MAP_STRU               astLocTechMap[NAS_LPP_MAX_POS_TECH];
}NAS_LPP_LOC_TECH_RUNING_STRU;

/*******************************************************************************
 结构名    : NAS_LPP_ECID_MEAS_RESULT_STRU
 结构说明  : 用于保存ECID的测量信息
 1.日    期   : 2015年07月28日
   作    者   : l00253982
   修改内容   : Added for LPP
*******************************************************************************/
typedef struct
{
    VOS_BOOL                                    bHaveEcidMeasFlag;
    LRRC_LPP_ECID_MEAS_RESULT_LIST_STRU         stLrrcLppEcidMeasResultList;   /*本次上报的测量信息保存*/
    LRRC_LPP_CELL_GLOBAL_ID_INFO_STRU           stLastGlobalIdInfo;     /*上次测量ind对应的GLOID信息*/
    VOS_UINT16                                  usLastPhyCellId;        /*上次测量ind对应的物理小区ID*/
}NAS_LPP_ECID_MEAS_RESULT_STRU;

/*******************************************************************************
 结构名    : NAS_LPP_OTDOA_MEAS_RESLT_STRU
 结构说明  : 用于保存otdoa的测量信息
 1.日    期   : 2015年07月28日
   作    者   : l00253982
   修改内容   : Added for LPP
*******************************************************************************/
typedef struct
{
    VOS_BOOL                                        bMeasRsltFlag;

    /* 0:代表CellGlobalId数据无效，1:代表CellGlobalId数据有效 */
    LPP_LRRC_INFO_FLAG_ENUM_UINT8                   ucCellGlobalIdFlag;

    /* 0:代表OTDOA-MeasQuality数据无效，1:代表OTDOA-MeasQuality数据有效 */
    LPP_LRRC_INFO_FLAG_ENUM_UINT8                   ucOtdoaMeasqualityFlag;

    VOS_UINT16                                      usSfn;

    /* 取值[0,503] */
    VOS_UINT16                                      usPhyCellIdRef;
    VOS_UINT8                                       aucRsv[2];

    VOS_UINT32                                      ulEarfcn;

    VOS_UINT32                                      ulNghbrRptNum;  /*已经在provide location infor里上报的小区个数*/

    LRRC_LPP_CELL_GLOBAL_ID_INFO_STRU               stCellGlobalIdInfo;

    LRRC_LPP_OTDOA_MEAS_QUALITY_STRU                stReferenceMeasQuality;

    LRRC_LPP_OTDOA_NEIGHBOUR_MEAS_LIST_STRU         stNeighbourMeasurementList;
}NAS_LPP_OTDOA_MEAS_RESLT_STRU;


/*******************************************************************************
 结构名    : NAS_LPP_GNSS_MEAS_RESLT_STRU
 结构说明  : 用于保存GNSS的测量信息
 1.日    期   : 2015年07月28日
   作    者   : l00253982
   修改内容   : Added for LPP
*******************************************************************************/
typedef struct
{
    VOS_UINT32                                      bitCommonInfo:1;
    VOS_UINT32                                      bitAgnssInfo:1;
    VOS_UINT32                                      bitSpare:30;

    VOS_BOOL                                        bHaveGnssMeasFlag;      /*是否有GNSS的测量信息*/
    MTA_LPP_AGNSS_PROVIDE_LOCATION_INFO_STRU        stGnssReqLocationInfo;  /*GNSS的测量信息*/
    MTA_LPP_COMMON_IES_PROVIDE_LOCATION_INFO_STRU   stCommonProvideLocInfo; /*经纬度公共信息*/
}NAS_LPP_GNSS_MEAS_RESLT_STRU;

/*******************************************************************************
 结构名    : NAS_LPP_MEAS_RESULT_STRU
 结构说明  : 用于保存ECID，OTDOA，GNSS的测量信息
 1.日    期   : 2015年07月28日
   作    者   : l00253982
   修改内容   : Added for LPP
*******************************************************************************/
typedef struct
{
    NAS_LPP_ECID_MEAS_RESULT_STRU           stEcidMeasRslt;     /*ECID的测量结果*/
    NAS_LPP_OTDOA_MEAS_RESLT_STRU           stOtdoaMeasRslt;    /*OTDOA的测量结果*/
    NAS_LPP_GNSS_MEAS_RESLT_STRU            stGnssMeasRslt;     /*GNSS的测量结果*/
}NAS_LPP_MEAS_RESULT_STRU;

/*******************************************************************************
 结构名    : NAS_LPP_MEAS_RESULT_STRU
 结构说明  : 用于保存ECID，OTDOA，GNSS的测量信息
 1.日    期   : 2015年08月03日
   作    者   : w00324863
   修改内容   : Added for LPP
*******************************************************************************/

typedef struct
{

    /* 0:代表不支持，1:代表支持*/
    LPP_LRRC_INFO_FLAG_ENUM_UINT8                   ucUeRxTxTimeDiffMeasFlag;

    LPP_LRRC_INFO_FLAG_ENUM_UINT8                   ucOtdoaUeAssistFlag;

    /* 0:代表不支持，1:代表支持 */
    LPP_LRRC_INFO_FLAG_ENUM_UINT8                   ucInterFreqRSTDMeasFlag;

    /* 0:代表不支持，1:代表支持 */
    LPP_LRRC_INFO_FLAG_ENUM_UINT8                   ucAddOtdoaNeighbourCellInfoListFlag;

    /*
    usBandNum 取值范围[1,256]
    ulBandInd,每个BIT，1:代表支持，0代表不支持，ulBandInd[0]中第一个BIT代表BAND1,依次类推;
    */

    VOS_UINT32                                      ulBandNum;
    VOS_UINT32                                      aulBandInd[LRRC_LPP_MAX_BAND_IND_ARRAY_NUM];

}LRRC_CAPABILITY_STRU;
/*******************************************************************************
 结构名    :NAS_LPP_TRANS_INDEX_STRU
 结构说明  :  一个transaction实体对应的指针以及对应内存池中的索引，以及
              对应的存储索引值的transaction的数组下标
 1.日    期   : 2015年07月06日
   作    者   :
*******************************************************************************/
typedef struct
{
    NAS_LPP_TRANSACTION_ELEMENT_ENTITY_STRU *pstTransEntity;
    VOS_UINT8                                ucTransIndx;
    VOS_UINT8                                ucSessionTransIndx;
    VOS_UINT8                                aucRsv[2];
}NAS_LPP_TRANS_INDEX_STRU;

/*******************************************************************************
 结构名    : NAS_LPP_MEAS_RESULT_STRU
 结构说明  : 用于保存ECID，OTDOA，GNSS的测量信息
 1.日    期   : 2015年08月03日
   作    者   : w00324863
   修改内容   : Added for LPP
*******************************************************************************/

typedef struct
{

    /*代表数据有效，收到RRC消息时置为TRUE*/
    VOS_BOOL                        bRrcCapbilityFlag;
    LRRC_CAPABILITY_STRU            stRrcCapbility;
}LRRC_SUPPORT_CAPABILITY_STRU;

/*******************************************************************************
 结构名    : NAS_LPP_ENTITY_STRU
 结构说明  : LPP实体的数据结构
 1.日    期   : 2015年07月06日
   作    者   : l00253982
   修改内容   : Added for LPP

*******************************************************************************/
typedef struct
{
    VOS_UINT16                          usReTransTimerLen;/*resend msg timer len*/
    VOS_UINT16                          usAttempeTransCnt;/*连接管理尝试计数*/
    VOS_UINT8                           ucLppLayerSwitch;/*LPP可维可测总开关*/
    VOS_UINT8                           ucLppLayerNorm;/*LPP可维可测normal消息开关*/
    VOS_UINT8                           ucLppLayerInfo;/*LPP可维可测info消息开关*/
    VOS_UINT8                           ucLppLayerWarn;/*LPP可维可测warn消息开关*/
    VOS_UINT8                           ucLppLayerErr;/*LPP可维可测error消息开关*/
    VOS_UINT8                           aucRsv[3];
}NAS_LPP_NV_CONFIG_STRU;

/*******************************************************************************
 结构名    : NAS_LPP_OTDOA_ASSIST_CFG_STRU
 结构说明  : LPP下行辅助数据提供缓存
 1.日    期   : 2015年08月04日
   作    者   : l00253982
   修改内容   : Added for LPP
*******************************************************************************/
typedef struct
{
    VOS_BOOL                                        bOtdoaAssistDataFlag;

    /* 0:otdoa ReferenceCellInfo 无效，1: otdoa ReferenceCellInfo 有效 */
    LPP_LRRC_INFO_FLAG_ENUM_UINT8                   ucOtdoaReferenceCellInfoFlag;

    /* 0:otdoa NeighbourCellInfo 无效，1: otdoa NeighbourCellInfo 有效 */
    LPP_LRRC_INFO_FLAG_ENUM_UINT8                   ucOtdoaNeighbourCellInfoFlag;

    VOS_UINT8                                       aucReserved[2];

    LPP_LRRC_OTDOA_REFERENCE_CELL_INFO_STRU         stOtdoaReferenceCellInfo;

    LPP_LRRC_OTDOA_NEIGHBOUR_CELL_INFO_LIST_STRU    stOtdoaNeighbourCellInfo;
}NAS_LPP_OTDOA_ASSIST_CFG_STRU;


/*******************************************************************************
 结构名    : NAS_LPP_LOCATION_REQ_STRU
 结构说明  : LPP下行位置信息请求
 1.日    期   : 2015年08月04日
   作    者   : l00253982
   修改内容   : Added for LPP
*******************************************************************************/
typedef struct
{
    VOS_UINT32                                      bitOpAgnssLocReq    :1;
    VOS_UINT32                                      bitOpOtdoaLocReq    :1;
    VOS_UINT32                                      bitOpEcidLocReq     :1;
    VOS_UINT32                                      bitOpSpare          :29;

    LPP_AGNSS_REQ_LOCATION_INFO_STRU                stAGNSSReqLocationInfo;
    LPP_OTDOA_REQ_LOCATION_INFO_STRU                stOtdoaReqLocationInfo;
    LPP_ECID_REQ_LOCATION_INFO_STRU                 stEcidReqLocationInfo;
}NAS_LPP_LOCATION_REQ_STRU;

/*******************************************************************************
 结构名    : NAS_LPP_COMM_CONFIG_INFO_STRU
 结构说明  :request location information的公共配置参数
 1.日    期   : 2015年08月04日
   作    者   : l00253982
   修改内容   : Added for LPP
*******************************************************************************/
typedef struct
{
   VOS_UINT32                                   bitOpQos                        :1;
   VOS_UINT32                                   bitOpLocationCoordinateType     :1;
   VOS_UINT32                                   bitOPVelocityTypes              :1;
   VOS_UINT32                                   bitOpSpare                      :29;

    /*对应的session和transaction的对应关系*/
    VOS_UINT8                                   ucSessionIndex;
    VOS_UINT8                                   ucSessionTransIndex;

    /*上报location information的*/
    LPP_LOCATION_INFO_TYPE_ENUM_UINT8           enLocationInformationType;

    /*是否上报addtional*/
    LPP_ADDITON_REPORT_ENUM_UNIT8               enAdditonInfo;

    /* 环境参数 */
    LPP_ENVIRONMENT_ENUM_UINT8                  enEnvironment;

    VOS_UINT8                                   ascRsv[3];

    /*上报准则*/
    NAS_LPP_REPORT_CRITERIA_STRU                stReportCriteria;

    /* Qos: 里面的stResponseTime参数已经在report criteria中整理存储，这里只是存一下，不使用。*/
    LPP_MTA_COMMON_QOS_STRU                     stQos;

    /* 只是GNSS用 */
    LPP_MTA_COMMON_LOCATION_COORDINATE_TYPE_STRU stLocationCoordinateType;

    /* 只是GNSS用 */
    LPP_MTA_COMMON_VELOCITY_TYPE_STRU           stVeloctytype;
}NAS_LPP_COMM_CONFIG_INFO_STRU;


/*******************************************************************************
 结构名    : NAS_LPP_ENTITY_STRU
 结构说明  : LPP实体的数据结构
 1.日    期   : 2015年07月06日
   作    者   : l00253982
   修改内容   : Added for LPP
*******************************************************************************/
typedef struct
{
    VOS_UINT32                          ulBitmap;
    NAS_LPP_COMM_CONFIG_INFO_STRU       astLppCommCfgInfo[NAS_LPP_MAX_POS_TECH];
}NAS_LPP_COMM_CONFIG_INFO_POOL_STRU;
/*******************************************************************************
 结构名    : NAS_LPP_SERVING_CELL_STRU
 结构说明  : LPP实体的数据结构
 1.日    期   : 2015年07月06日
   作    者   : l00253982
   修改内容   : Added for LPP
*******************************************************************************/
typedef struct
{
    VOS_UINT32                          bitCELLIDChng:1;/* 记录CELL ID CHANGE */
    VOS_UINT32                          bitOpspare:31;
    VOS_UINT32                          ulEarfcn;
    VOS_UINT16                          usPhyCellId;
    VOS_UINT8                           aucRsv[2];

    VOS_UINT32                          ulCellIdentity;

     /* PLMN ID与空口保持一致 */
    VOS_UINT8                           aucPlmnId[3];
    VOS_UINT8                           ucReserved;

}NAS_LPP_SERVING_CELL_STRU;

/*******************************************************************************
 结构名    : NAS_LPP_CONFIG_PARA_STRU
 结构说明  : LPP配置参数数据结构
 1.日    期   : 2015年07月06日
   作    者   : xiaojun
   修改内容   : Added for LPP
*******************************************************************************/
typedef struct
{
    VOS_UINT32                          bitOtdoaAssisChng   :1;
    VOS_UINT32                          bitGnssAssisChng    :1;
    VOS_UINT32                          bitEcidReq          :1; /*记录当前的Location request里是否携带了ecid 的请求*/
    VOS_UINT32                          bitOtdoaReq         :1; /*记录当前的Location request里是否携带了otdoa 的请求*/
    VOS_UINT32                          bitGnssReq          :1; /*记录当前的Location request里是否携带了gnss 的请求*/
    VOS_UINT32                          bitSpare            :27;

    /*REQUEST LOCATION INFOR里携带的common配置参数，最大可能对应3个request location information下发的*/
    NAS_LPP_COMM_CONFIG_INFO_POOL_STRU  stCommCfgInfoPool;

    /*OTDOA的辅助数据参数*/
    NAS_LPP_OTDOA_ASSIST_CFG_STRU       stOtdoaAssisCfg;

    /*GNSS的辅助数据参数*/
    /*NAS_LPP_GNSS_ASSIS_DATA_STRU        stGnssAssisData;*/

    /*REQUEST LOCATION INFOR 里的数据参数*/
    NAS_LPP_LOCATION_REQ_STRU           stLocationReq;

    NAS_LPP_SERVING_CELL_STRU           stServingCell;
}NAS_LPP_CONFIG_PARA_STRU;

/*******************************************************************************
 结构名    : NAS_LPP_GNSS_TIMER_STRU
 结构说明  : LPP gnss timer struct
 1.日    期   : 2015年10月22日
   作    者   : w00324863
   修改内容   : Added for LPP
*******************************************************************************/
typedef struct
{
    /* 获取GNSS CAP计数 */
    VOS_UINT8                               ucSendMtaGnssCapCnt;
    VOS_UINT8                               aucRsv[3];
    /* GNSS CAP 获取成功标志位 */
    VOS_BOOL                                bGnssCapbilityFlag;
    /* GNSS能力信息 */
    MTA_LPP_AGNSS_PROVIDE_CAP_STRU          stMtaLppGnssCap;
    /* 等待GNSS CAP CNF 定时器 */
    NAS_LPP_TIMER_STRU                      stLppWaitForGnssCapCnfTimer;    /* 等待MTA回复GNSS CAP的定时器 */
    NAS_LPP_TIMER_STRU                      stLppGnssLocInfoInvalidTimer;    /* 位置信息有效定时器 */
}NAS_LPP_GNSS_DATA_STRU;

/*******************************************************************************
 结构名    : NAS_LPP_UP_REPORT_CRITERIA_STRU
 结构说明  : lpp上报位置信息的方式
 1.日    期   : 2015年07月06日
   作    者   : W00324863
   修改内容   : Added for LPP
*******************************************************************************/
typedef struct
{
    NAS_LPP_REPORT_LOCATION_TYPE_ENUM_UINT8     enType;
    VOS_UINT8                                   ucRsv[3];

    union
    {
        NAS_LPP_REPORT_LOCATION_TYPE_TRIGGER_STRU   stReportTrigger;
        NAS_LPP_REPORT_LOCATION_TYPE_PERIOD_STRU    stReportPeriod;
        NAS_LPP_REPORT_LOCATION_TYPE_ONCE_STRU      stReportOnce;
    }u;
}NAS_LPP_UP_REPORT_CRITERIA_STRU;

/*******************************************************************************
 结构名    : NAS_LPP_UP_ECID_INFO_STRU
 结构说明  : LPP 用户面ECID的实体结构
 1.日    期   : 2015年11月18日
   作    者   : l00253982
   修改内容   : Added for LPP
*******************************************************************************/
typedef struct
{
    NAS_LPP_UP_POS_REQ_TECH_TYPE_ENUM_UINT8     enReqPosTechType;   /*表示MTA请求具体定位技术类型*/
    VOS_UINT8                                   aucRsv[3];
    NAS_LPP_ECID_MEAS_RESULT_STRU               stEcidMeasRslt;      /*ECID的测量结果*/
    NAS_LPP_UP_REPORT_CRITERIA_STRU             stReportCriteria;    /*上报准则*/
    NAS_LPP_TIMER_STRU                          stLppUpStateTimer;   /*ECID流程中使用到得状态定时器*/
    NAS_LPP_UP_STATE_ENUM_UINT32                enLppUpState;        /*表示ECID的当前状态*/
    MTA_LPP_REQ_MEASUREMENT_STRU                stRequestedMeasurements; /*表示请求ECID的测量的类型*/
}NAS_LPP_UP_ECID_INFO_STRU;

/*******************************************************************************
 结构名    : NAS_LPP_UP_OTDOA_INFO_STRU
 结构说明  : LPP 用户面OTDOA的数据结构
 1.日    期   : 2015年11月18日
   作    者   : l00253982
   修改内容   : Added for LPP
*******************************************************************************/
typedef struct
{
    NAS_LPP_UP_POS_REQ_TECH_TYPE_ENUM_UINT8     enReqPosTechType;   /*表示MTA请求具体定位技术类型*/
    VOS_UINT8                                   aucRsv[3];
    NAS_LPP_OTDOA_MEAS_RESLT_STRU               stOtdoaMeasRslt;     /*OTDOA的测量结果*/
    NAS_LPP_OTDOA_ASSIST_CFG_STRU               stOtdoaAssisCfg;     /*OTDOA的辅助数据参数*/
    NAS_LPP_UP_REPORT_CRITERIA_STRU             stReportCriteria;    /*上报准则*/
    NAS_LPP_TIMER_STRU                          stLppUpStateTimer;   /*OTDOA流程中使用到的状态定时器*/
    NAS_LPP_UP_STATE_ENUM_UINT32                enLppUpState;        /*表示OTDOA的当前状态*/
}NAS_LPP_UP_OTDOA_INFO_STRU;

/*******************************************************************************
 结构名    : NAS_LPP_USER_PLANE_ENTITY_STRU
 结构说明  : LPP 用户面的实体信息
 1.日    期   : 2015年11月18日
   作    者   : l00253982
   修改内容   : Added for LPP
*******************************************************************************/
typedef struct
{
    VOS_BOOL                                bReqEcidAndOtdoaFlag; /*标识同时请求了ECID&OTDOA的测量请求*/
    NAS_LPP_UP_REPORT_CRITERIA_STRU         stReportCriteria;     /*同时请求ECID&OTDOA维护的上报准则*/
}NAS_LPP_UP_MULTI_POS_TECH_INFO_STRU;

/*******************************************************************************
 结构名    : NAS_LPP_USER_PLANE_ENTITY_STRU
 结构说明  : LPP 用户面的实体信息
 1.日    期   : 2015年11月18日
   作    者   : l00253982
   修改内容   : Added for LPP
*******************************************************************************/
typedef struct
{
    NAS_LPP_UP_MULTI_POS_TECH_INFO_STRU     stMultiPosTechEntity; /*同时请求ECID&OTDOA的私有信息*/
    NAS_LPP_UP_ECID_INFO_STRU               stEcidUpEntity;     /*用户面ECID的实体信息*/
    NAS_LPP_UP_OTDOA_INFO_STRU              stOtdoaUpEntity;    /*用户面OTDOA的实体信息*/
}NAS_LPP_USER_PLANE_ENTITY_STRU;

/*******************************************************************************
 结构名    : NAS_LPP_ENTITY_STRU
 结构说明  : LPP实体的数据结构
 1.日    期   : 2015年07月06日
   作    者   : l00253982
   修改内容   : Added for LPP
*******************************************************************************/
typedef struct
{
    VOS_UINT8                                ucTransNum;             /*当前使用的由UE创建的transaction的transaction Number的最大值，网络侧发起的transaction由SMLC维护*/
    VOS_UINT8                                ucUpSequenceNumMax;     /*当前使用上行LPP消息sequenceNum的最大值， 下行LPP消息sequenceNum由SMLC维护*/
    VOS_UINT8                                aucRsv[2];

    VOS_UINT32                               ulInvalidLen;
    NAS_LPP_SESSION_ENTITY_POOL_STRU         stSessionEntityPool;    /*LPP的会话实体*/
    NAS_LPP_NV_CONFIG_STRU                   stLppNvConfig;          /*LPP涉及到得NV项*/
    NAS_LPP_TRANSACTION_ENTITY_POOL_STRU     stTransEntityPool;      /*TRANSACTION实体的资源池，所有的session实体从这里申请transaction单元*/
    LRRC_SUPPORT_CAPABILITY_STRU             stLrrcSupCapability;    /*开机LRRC上报的LCS定位的相关能力*/
    NAS_LPP_LOC_TECH_RUNING_STRU             stRuningLocTech;        /*用于记录当前正在running的定位技术在哪一个实体中运行，便于LRRC回复测量cnf，测量IND之后的实体索引*/
    NAS_LPP_MEAS_RESULT_STRU                 stMeasResult;           /*保存测量ind消息*/
    NAS_LPP_CONN_MANAGE_STRU                 stLppConnManage;        /*LPP连接管理模块所需要的所有消息*/
    NAS_LPP_UP_MSG_BUFF_POOL_STRU            stUpMsgBuffPool;        /*上行消息的公共内存池*/
    NAS_LPP_CONFIG_PARA_STRU                 stLppConfig;            /*存储配置参数:request location information和assistant data来的*/
    NAS_LPP_GNSS_DATA_STRU                   stStructDataForGnss;    /*gnss data */
    NAS_LPP_USER_PLANE_ENTITY_STRU           stUserPlaneEntity;      /*用户面实体*/
} NAS_LPP_ENTITY_STRU;
/*******************************************************************************
 结构名    : NAS_LPP_MSG
 结构说明  : LPP消息
 1.日    期   : 2015年07月06日
   作    者   : l00253982
   修改内容   : Added for LPP
*******************************************************************************/
typedef struct
{
    VOS_MSG_HEADER                                          /*_H2ASN_Skip*/

    VOS_UINT8                           ucRsv[4];
}NAS_LPP_MSG;

/*****************************************************************************
  6 UNION
*****************************************************************************/


/*****************************************************************************
  7 Extern Global Variable
*****************************************************************************/
extern NAS_LPP_ENTITY_STRU     g_stNasLppEntity;
extern NAS_LPP_SUB_STATE_TIME_STRU g_astLppSubStateTime[LPP_SS_BUTT];
extern NAS_LPP_FSM_STRU  g_astNasLppFsm[];
extern LPP_MESSAGE_STRU        stLppMsgBuff;

/*****************************************************************************
  8 Fuction Extern
*****************************************************************************/

extern VOS_INT32   NAS_COMM_PrinLrrcLppMsg
       (
           VOS_CHAR                                *pcBuff,
           VOS_UINT16                               usOffset,
           const PS_MSG_HEADER_STRU                *pstMsg
       );
extern VOS_INT32   NAS_COMM_PrintMmLppMsg
       (
           VOS_CHAR                                *pcBuff,
           VOS_UINT16                               usOffset,
           const PS_MSG_HEADER_STRU                *pstMsg
       );
extern VOS_VOID  NAS_LPP_AddRunningPositionTech
       (
           NAS_LPP_POSITION_TECH_ENUM_UINT8        enPositionTech,
           VOS_UINT8                               ucSessionIndx,
           VOS_UINT8                               ucSessionTransIndx,
           VOS_UINT8                               ucTransIndx
       );
extern VOS_UINT32 NAS_LPP_AddTransEntityToSession( NAS_LPP_SESSION_ENTITY_ELEMENT_STRU *pstSessionEntity ,VOS_UINT8 ucIndex,VOS_UINT8 *pucSessionTransIndex);
extern VOS_UINT8 NAS_LPP_ApplyTransNum( VOS_VOID );
extern VOS_VOID  NAS_LPP_BuffFsmMsg
       (
           PS_MSG_HEADER_STRU                         *pstMsg,
           VOS_UINT32                                  ulSize,
           VOS_UINT8                                   ucTransIndex,
           NAS_LPP_BUFF_FSM_MSG_PRIORITY_ENUM_UINT8    enMsgPriority
       );
extern VOS_VOID NAS_LPP_ChangeTransFsmState
       (
           VOS_UINT8                           ucSessionIndx,
           VOS_UINT8                           ucSessionTransIndx,
           NAS_LPP_MAIN_STATE_ENUM_UINT32      enLppMainState,
           NAS_LPP_SUB_STATE_ENUM_UINT32       enLppSubState
       );
extern VOS_UINT8  NAS_LPP_GetLppLayerSwitchFlag(VOS_VOID);
extern VOS_VOID  NAS_LPP_ClearLppMsgBuff( VOS_VOID );
extern VOS_VOID  NAS_LPP_ClearLppTransCnt(VOS_VOID);
extern VOS_VOID  NAS_LPP_DeleteRunningPositionTech(  NAS_LPP_POSITION_TECH_ENUM_UINT8 enPositionTech );
extern VOS_VOID  NAS_LPP_DelTransEntityFromSession( NAS_LPP_SESSION_ENTITY_ELEMENT_STRU *pstSessionEntity, VOS_UINT8 ucSessionTransIndx );
extern LPP_UPLINK_MSG_BUF_STRU* NAS_LPP_FindUpLinkBuffer
       (
           VOS_UINT8                           ucSequenceNum,
           VOS_UINT32                          ulSessionId
       );
extern NAS_LPP_FSM_STRU * NAS_LPP_FsmFind(NAS_LPP_MAIN_STATE_ENUM_UINT32 enLppMainState, NAS_LPP_SUB_STATE_ENUM_UINT32 enLppSubState);
extern VOS_VOID NAS_LPP_FsmInit( VOS_VOID );
extern VOS_INT32 NAS_LPP_FsmStaCompare( const VOS_VOID *arg1, const VOS_VOID *arg2 );
extern NAS_LPP_CONFIG_PARA_STRU *NAS_LPP_GetCfgPara( VOS_VOID );
extern NAS_LPP_COMM_CONFIG_INFO_STRU *NAS_LPP_GetCommCfgInfoElementByIndex( VOS_UINT8 ucIndex);
extern NAS_LPP_COMM_CONFIG_INFO_POOL_STRU *NAS_LPP_GetCommCfgInfoPool( VOS_VOID );
extern NAS_LPP_TIMER_STRU*  NAS_LPP_GetConnManageTimer( VOS_VOID );
extern LPP_REQUEST_CAPABILITIES_R9_IES_STRU*  NAS_LPP_GetDownLinkCapReqIEAddr
       (
           LPP_MESSAGE_STRU                   *pstLppMsg
       );
extern LPP_REQ_LOCATION_INFO_R9_IES_STRU*  NAS_LPP_GetDownLinkLocationReqIEAddr
       (
           LPP_MESSAGE_STRU                   *pstLppMsg
       );
extern VOS_UINT16 NAS_LPP_GetDownLinkMsgSequenceNum
       (
           VOS_UINT8               ucSessionIndx
       );
extern VOS_UINT32 NAS_LPP_GetDownlinkMsgType
       (
           LPP_MESSAGE_STRU                   *pstLppMsg
       );
extern NAS_LPP_TIMER_STRU*  NAS_LPP_GetDurationTimer
       (
           VOS_UINT8                          ucSessionIndex,
           VOS_UINT8                          ucSessionTransIndx
       );
extern NAS_LPP_ECID_MEAS_RESULT_STRU*  NAS_LPP_GetEcidMeasRsltAddr( VOS_VOID );
extern NAS_LPP_MEAS_RESULT_STRU*  NAS_LPP_GetMeasRsltAddr( VOS_VOID );
extern VOS_UINT8  NAS_LPP_GetEndTransFlg( VOS_UINT8 ucSessionIndx,VOS_UINT8 ucSessionTransIndx );
extern LRRC_LPP_CELL_GLOBAL_ID_INFO_STRU*  NAS_LPP_GetLastTriggerCellGloId( VOS_VOID );
extern NAS_LPP_LOCATION_REQ_STRU  *NAS_LPP_GetLocationReqBuff( VOS_VOID );
extern NAS_LPP_CONN_STATUS_ENUM_UINT32  NAS_LPP_GetLppConnStatus( VOS_VOID );
extern NAS_LPP_ENTITY_STRU*  NAS_LPP_GetLppEntityCtx( VOS_VOID );
extern VOS_UINT32  NAS_LPP_GetLppIntraDataCnfTimerLen(VOS_VOID);
extern VOS_UINT32  NAS_LPP_GetLppMainState
       (
           VOS_UINT8                           ucSessionIndx,
           VOS_UINT8                           ucSessionTransIndx
       );
extern LPP_MESSAGE_STRU*  NAS_LPP_GetLppMsgBuff( VOS_VOID );
extern NAS_LPP_NV_CONFIG_STRU*  NAS_LPP_GetLppNvParaConfig(VOS_VOID);
extern NAS_LPP_SESSION_ENTITY_POOL_STRU* NAS_LPP_GetLppSessionEntityPool( VOS_VOID );
extern VOS_UINT32  NAS_LPP_GetLppSubState
       (
           VOS_UINT8                           ucSessionIndx,
           VOS_UINT8                           ucSessionTransIndex
       );
extern VOS_UINT32  NAS_LPP_GetLppTransAttepCnt(VOS_VOID);
extern NAS_LPP_TRANSACTION_ENTITY_POOL_STRU * NAS_LPP_GetLppTransEntityPool( VOS_VOID );
extern NAS_LPP_UP_MSG_BUFF_POOL_STRU * NAS_LPP_GetLppUpMsgBuffPool( VOS_VOID );
extern LRRC_SUPPORT_CAPABILITY_STRU *NAS_LPP_GetLrrcCap( VOS_VOID );
extern VOS_UINT8  NAS_LPP_GetLrrcRxTxTimeDiffMeasFlag(VOS_VOID);
extern NAS_LPP_OTDOA_ASSIST_CFG_STRU *NAS_LPP_GetOtdoaAssisCfg( VOS_VOID );
extern NAS_LPP_TIMER_STRU*  NAS_LPP_GetPeriodTimer
       (
           VOS_UINT8                          ucSessionIndex,
           VOS_UINT8                          ucSessionTransIndx
       );
extern VOS_UINT32  NAS_LPP_GetPositionTechEcid(VOS_UINT8 ucSessionIndx);
extern VOS_UINT32  NAS_LPP_GetPositionTechGnss(VOS_UINT8 ucSessionIndx);
extern VOS_UINT32  NAS_LPP_GetPositionTechOtdoa(VOS_UINT8 ucSessionIndx);
extern VOS_UINT32  NAS_LPP_GetPrtclTimeLen
       (
           NAS_LPP_TIMER_PARA_ENUM_UINT8       enTimeName,
           VOS_UINT8                           ucSessionIndex,
           VOS_UINT8                           ucSessionTransIndx
       );
extern NAS_LPP_TIMER_STRU*  NAS_LPP_GetResPonseTimer
       (
           VOS_UINT8                          ucSessionIndex,
           VOS_UINT8                          ucSessionTransIndx
       );
extern NAS_LPP_LOC_TECH_RUNING_STRU  *NAS_LPP_GetRuningLocTech( VOS_VOID );
extern NAS_LPP_SERVING_CELL_STRU *NAS_LPP_GetServingCell( VOS_VOID );
extern NAS_LPP_SESSION_ENTITY_ELEMENT_STRU * NAS_LPP_GetSessionElementByIndex(VOS_UINT8 ucIndex);
extern NAS_LPP_SESSION_ENTITY_ELEMENT_STRU*  NAS_LPP_GetSessionEntity
       (
           VOS_UINT32                          ulSessionIndex
       );
extern VOS_UINT8  NAS_LPP_GetSessionEntityReportType
       (
           VOS_UINT8                           ucSessionIndex,
           VOS_UINT8                           ucSessionTransIndex
       );
extern VOS_UINT32  NAS_LPP_GetSessionIdBySessionIndx
       (
           VOS_UINT8                           ucSessionIndx
       );
extern NAS_LPP_TIMER_PARA_ENUM_UINT8  NAS_LPP_GetTimeNameBySubState
       (
           NAS_LPP_SUB_STATE_ENUM_UINT32       enLppSubState
       );
extern NAS_LPP_TIMER_STRU*  NAS_LPP_GetTimer
       (
           VOS_UINT32                          ulSessionIndex,
           VOS_UINT32                          ulSessionTransIndx,
           NAS_LPP_UP_POS_REQ_TECH_TYPE_ENUM_UINT8 enUpPosTechType,
           NAS_LPP_TIMER_PARA_ENUM_UINT8       enTimerType
       );
extern VOS_UINT32  NAS_LPP_GetTimerLen
       (
           NAS_LPP_TIMER_PARA_ENUM_UINT8       enTimeName,
           VOS_UINT8                           ucSessionIndex,
           VOS_UINT8                           ucSessionTransIndx,
           NAS_LPP_UP_POS_REQ_TECH_TYPE_ENUM_UINT8 enPosTechType
       );
extern NAS_LPP_TIMER_PROC_FUNC  NAS_LPP_GetTimerProcFun( NAS_LPP_TIMER_PARA_ENUM_UINT8 enTimeName );
extern NAS_LPP_TIMER_STRU*  NAS_LPP_GetTransactionTimer
       (
           VOS_UINT32                          ulSessionIndex,
           VOS_UINT32                          ulSessionTransIndx
       );
extern NAS_LPP_TRANSACTION_ELEMENT_ENTITY_STRU* NAS_LPP_GetTransElementByIndex(VOS_UINT8 ucIndex);
extern NAS_LPP_TRANSACTION_ELEMENT_ENTITY_STRU  *NAS_LPP_GetTransEntity
       (
           VOS_UINT32                          ulSessionIndex,
           VOS_UINT32                          ulSessionTransIndex
       );
extern VOS_UINT8  NAS_LPP_GetTransIdIndex
       (
           VOS_UINT8                          ucSessionIndex,
           VOS_UINT8                          ucSessionTransIndex
       );
extern VOS_UINT32  NAS_LPP_GetTransLppMsgCnt( VOS_VOID );
extern NAS_LPP_MSG_IDENTITY_STRU* NAS_LPP_GetUpLinkMsgIndetity
       (
           VOS_UINT32          ulUpBufferIndex
       );
extern LPP_PROVIDE_CAPABILITIES_R9_IES_STRU*  NAS_LPP_GetUpLinkProvideCapIEAddr
       (
           LPP_MESSAGE_STRU                   *pstLppMsg
       );
extern LPP_PROVIDE_LOCATION_INFO_R9_IES_STRU*  NAS_LPP_GetUpLinkProvideLocIEAddr
       (
           LPP_MESSAGE_STRU                   *pstLppMsg
       );
extern VOS_UINT32 NAS_LPP_GetUpLinkSequenceNumber
       (
           VOS_UINT32          ulUpBufferIndex
       );
extern VOS_UINT32 NAS_LPP_GetUpLinkSessionId
       (
           VOS_UINT32          ulUpBufferIndex
       );
extern VOS_UINT32 NAS_LPP_GetUpLinkTransactionNumber
       (
           VOS_UINT32          ulUpBufferIndex
       );
extern VOS_UINT8 NAS_LPP_GetUpMsgSequenceNum( VOS_VOID );
extern NAS_LPP_SUB_STATE_ENUM_UINT32  NAS_LPP_GetWaitAckSubState
       (
           NAS_LPP_AIR_MSG_ENUM_UINT32         ulUpLppMsgId,
           NAS_LPP_MAIN_STATE_ENUM_UINT32      enMainState
       );
extern VOS_VOID NAS_LPP_InitRunningLocTech( VOS_VOID );
extern VOS_UINT32  NAS_LPP_IsTimerNameValid
       (
           VOS_UINT32                          ulSessionIndex,
           VOS_UINT32                          ucSessionTransIndx,
           NAS_LPP_TIMER_PARA_ENUM_UINT8       enTimerType
       );
extern VOS_VOID NAS_LPP_LppCtxInit( VOS_VOID );
extern VOS_VOID  NAS_LPP_LppPlmn2NasPlmn
       (
           LPP_MTA_COMMON_PLMN_IDENTITY_STRU   *pstLppPlmnId,
           VOS_UINT8                           *pucNasPlmnId
       );
extern VOS_UINT8  NAS_LPP_MallocCommCfgInfoElementIndex( VOS_UINT8 ucTransIndex );
extern NAS_LPP_SESSION_ENTITY_ELEMENT_STRU* NAS_LPP_MallocSessionEntity( VOS_UINT32  ulSessionId );
extern NAS_LPP_TRANSACTION_ELEMENT_ENTITY_STRU* NAS_LPP_MallocTransEntity
       (
           LPP_TRANSACTION_ID_STRU                 *pstUuTransactionId
       );
extern VOS_UINT8 NAS_LPP_MallocTransEntityIndx
       (
           LPP_TRANSACTION_ID_STRU                 *pstUuTransactionId
       );
LPP_UPLINK_MSG_BUF_STRU  *NAS_LPP_MallocUpMsgBuffer(VOS_UINT8 *pucUplinkBuffIndx);
extern VOS_VOID  NAS_LPP_ModifyPrtclTimerLen
       (
           NAS_LPP_TIMER_PARA_ENUM_UINT8       enTimeName,
           VOS_UINT8                           ucSessionIndex,
           VOS_UINT8                           ucSessionTransIndx,
           VOS_UINT32                          ulTimerLen
       );
extern VOS_VOID  NAS_LPP_ModifyTimerLen
       (
           NAS_LPP_TIMER_PARA_ENUM_UINT8       enTimeName,
           VOS_UINT8                           ucSessionIndex,
           VOS_UINT8                           ucSessionTransIndx,
           VOS_UINT32                          ulTimerLen
       );
extern VOS_UINT32 NAS_LPP_MsgDuplicateDetect( VOS_UINT32 ulSessionId, VOS_UINT8 ucNewMsgSequenecNum );
extern VOS_VOID  NAS_LPP_NasPlmn2LppPlmn
       (
           VOS_UINT8                           *pucNasPlmnId,
           LPP_MTA_COMMON_PLMN_IDENTITY_STRU   *pstLppPlmnId
       );
extern VOS_UINT32  NAS_LPP_PopFsmMsg
       (
           VOS_UINT8                                   ucTransIndex,
           NAS_LPP_BUFF_FSM_MSG_PRIORITY_ENUM_UINT8    enMsgPriority );
extern VOS_VOID NAS_LPP_PrintLppRevMsg
       (
           const PS_MSG_HEADER_STRU           *pstMsg,
           VOS_CHAR                           *pcBuff
       );
extern VOS_VOID NAS_LPP_PrintLppSendMsg
       (
           const PS_MSG_HEADER_STRU           *pstMsg,
           VOS_CHAR                           *pcBuff
       );
extern VOS_VOID  NAS_LPP_ReadLppNvConfig( VOS_VOID);
extern VOS_VOID NAS_LPP_ReInitTransEntity
       (
           VOS_UINT8       ucTransIndex,
           VOS_UINT8       ucSessionIndx,
           VOS_UINT8       ucSessionTransIndx
       );
extern VOS_VOID  NAS_LPP_RelAllTransEntity( VOS_VOID );
extern VOS_VOID  NAS_LPP_ReleaseAllSession( VOS_VOID );
extern VOS_VOID  NAS_LPP_ReleaseCommCfgInfoElementByIndex( VOS_UINT8 ucTransIndex, VOS_UINT8 ucIndex);
extern VOS_VOID  NAS_LPP_ReleasePosTechMeas
(
    VOS_UINT8                               ucSessionIndx,
    VOS_UINT8                               ucSessionTransIndx,
    NAS_LPP_POSITION_TECH_ENUM_UINT8        enPosTech
);
extern VOS_VOID NAS_LPP_ReleaseSessionEntity(VOS_UINT32 ulSessionId);
extern VOS_VOID  NAS_LPP_ReleaseSessionEntityByIndex( VOS_UINT8 ucSessionIndx );
extern VOS_VOID  NAS_LPP_ReleaseTransEntity( VOS_UINT8 ucSessionIndx, VOS_UINT8 ucSessionTransIndx );
extern VOS_VOID  NAS_LPP_ReleaseTransEntityAction
       (
           VOS_UINT8                               ucSessionIndx,
           VOS_UINT8                               ucSessionTransIndx
       );
extern VOS_VOID  NAS_LPP_ReleaseTransEntityByIndx(VOS_UINT8 ucSessionIndx ,VOS_UINT8 ucSessionTransIndx );
extern VOS_VOID NAS_LPP_ReleaseTransEntityElementOnly( VOS_UINT8 ucSessionIndx, VOS_UINT8 ucSessionTransIndx );
extern VOS_VOID NAS_LPP_RelUpMsgBuffer( LPP_UPLINK_MSG_BUF_STRU **ppstLppUpMsgBuf );
extern VOS_VOID NAS_LPP_RelUpMsgBufferByIndex( VOS_UINT8 ucIndex );
extern VOS_VOID  NAS_LPP_ReturnTransEntityToPool( VOS_UINT8 ucTransIndex );
extern NAS_LPP_LOC_TECH_MAP_STRU*  NAS_LPP_SearchRunningPositionTech
       (
           NAS_LPP_POSITION_TECH_ENUM_UINT8        enPositionTech
       );
extern VOS_VOID NAS_LPP_SearchRunningPosTechByIndx2
       (
           VOS_UINT8 ucSessionIndx,
           VOS_UINT8 ucSessionTranIndx,
           NAS_LPP_LOC_TECH_RUNING_STRU *pstPosSearchRslt
       );
extern VOS_VOID NAS_LPP_SearchRunningPosTechBySessionIndx
       (
           VOS_UINT8 ucSessionIndx,
           NAS_LPP_LOC_TECH_RUNING_STRU *pstPosSearchRslt
       );
extern VOS_VOID NAS_LPP_SearchRunningPosTechByTransIndx
       (
           VOS_UINT8 ucTransIndx,
           NAS_LPP_LOC_TECH_RUNING_STRU *pstPosSearchRslt
       );
extern NAS_LPP_SESSION_ENTITY_ELEMENT_STRU*  NAS_LPP_SearchSessionElement( VOS_UINT32 ulSessionId );
extern VOS_UINT8 NAS_LPP_SearchSessionIndx( VOS_UINT32 ulSessionId );
extern NAS_LPP_TRANSACTION_ELEMENT_ENTITY_STRU * NAS_LPP_SearchTransEntity
       (
           VOS_UINT32                          ulSessionId,
           NAS_LPP_TRANS_ID_STRU               *pstTransId,
           VOS_UINT8                           *pucSessionTransIndx
       );
extern VOS_VOID NAS_LPP_SearchTransEntityIndx(
           VOS_UINT8                       ucSessionIndx,
           NAS_LPP_TRANS_ID_STRU          *pstTransId,
           VOS_UINT8                      *pucTransIndx,
           VOS_UINT8                      *pucSessionTransIndx );
extern LPP_UPLINK_MSG_BUF_STRU*   NAS_LPP_SearchUpMsgBuff
       (
           VOS_UINT32             ulSessionId,
           NAS_LPP_TRANS_ID_STRU *pstTransId
       );
extern VOS_VOID NAS_LPP_SearchUpMsgBuffByTrnasId
       (
           NAS_LPP_TRANS_ID_STRU                *pstTransId,
           NAS_LPP_UP_MSG_BUFF_SEARCH_RSLT_STRU *pstSearchRslt
       );
extern VOS_VOID  NAS_LPP_SessionEntityReInit( VOS_UINT8 ucSessionIndx );
extern VOS_VOID NAS_LPP_SetDownLinkMsgSequenceNum
       (
           VOS_UINT8               ucSessionIndx,
           VOS_UINT8               ucSequenceNumber
       );
extern VOS_VOID  NAS_LPP_SetEndTransFlg( VOS_UINT8 ucSessionIndx,VOS_UINT8 ucSessionTransIndx ,PS_BOOL_ENUM_UINT8 enTransEndFlg);
extern VOS_VOID  NAS_LPP_SetLppConnStatus(NAS_LPP_CONN_STATUS_ENUM_UINT32 enConnStatus);
extern VOS_VOID  NAS_LPP_TimerReg
       (
           NAS_LPP_TIMER_PARA_ENUM_UINT8       enTimeName,
           NAS_LPP_TIMER_PROC_FUNC             fFun,
           VOS_UINT32                          ulTimerLen

       );
extern VOS_VOID NAS_LPP_TimerStart
       (
           VOS_UINT32                          ulSessionIndex,
           VOS_UINT32                          ucSessionTransIndx,
           NAS_LPP_TIMER_PARA_ENUM_UINT8       enTimerType
       );
extern VOS_VOID NAS_LPP_TimerStop
       (
           VOS_UINT32                          ulSessionIndex,
           VOS_UINT32                          ulTransIndex,
           NAS_LPP_TIMER_PARA_ENUM_UINT8       enTimerType
       );
extern VOS_UINT32  NAS_LPP_TransFsmCheck
(
    NAS_LPP_MAIN_STATE_ENUM_UINT32  enLppMainState,
    NAS_LPP_SUB_STATE_ENUM_UINT32   enLppSubState,
    PS_MSG_HEADER_STRU             *pstMsg
);
extern VOS_VOID  NAS_LPP_TransLppMsgAddCnt(VOS_VOID);
extern VOS_VOID  NAS_LPP_CreatNewTrans
(
    VOS_UINT8       ucSessionIndx ,
    VOS_UINT8      *pucSessionTransIndx,
    VOS_UINT8      *pucTransIndex
);
extern NAS_LPP_GNSS_DATA_STRU *NAS_LPP_GetGnssData( VOS_VOID );
extern VOS_UINT32  NAS_LPP_JustMsgBuffInCapState( VOS_UINT32 ulSubState, VOS_VOID *pMsg );
extern VOS_UINT32  NAS_LPP_JustMsgBuffInAssistState( VOS_UINT32 ulSubState, VOS_VOID *pMsg );
extern VOS_UINT32  NAS_LPP_JustMsgBuffInLocState( VOS_UINT32 ulSubState, VOS_VOID *pMsg );
extern VOS_VOID  NAS_LPP_SetWaitMeasCnfFlag
(
    VOS_UINT8                           ucSessionIndx,
    VOS_UINT8                           ucSessionTranIndx,
    NAS_LPP_POSITION_TECH_ENUM_UINT8    enPosTech,
    VOS_UINT32                          ulFlag
);
extern VOS_UINT32  NAS_LPP_GetWaitMeasCnfFlag
(
    VOS_UINT8                           ucSessionIndx,
    VOS_UINT8                           ucSessionTranIndx,
    NAS_LPP_POSITION_TECH_ENUM_UINT8    enPosTech
);
extern VOS_BOOL NAS_LPP_IsThereOtherTransactionRunningInSession
(
    VOS_UINT8                       ucSessionIndx,
    NAS_LPP_TRANS_ID_STRU          *pstTransId
);
extern VOS_UINT16  NAS_LPP_GetLastTriggerLastPhyCellId( VOS_VOID );
extern VOS_VOID  NAS_LPP_SetLastTriggerLastPhyCellId(VOS_UINT16 usPhyCellId);
extern VOS_BOOL  NAS_LPP_IsOtdoaAssistDataChng( VOS_VOID );
extern VOS_BOOL  NAS_LPP_IsGnssAssistDataChng( VOS_VOID );
extern VOS_VOID  NAS_LPP_AbortAndErrorProcess
(
    VOS_UINT8                           ucSessionIndex,
    VOS_UINT8                           ucSessionTransIndx,
    NAS_LPP_TRANS_ID_STRU              *pstTransId
);
extern VOS_VOID  NAS_LPP_StopTechLocForLackOfAssistData( VOS_VOID );
extern NAS_LPP_GNSS_MEAS_RESLT_STRU*  NAS_LPP_GetGnssMeasRsltAddr( VOS_VOID );
extern NAS_LPP_TIMER_STRU*  NAS_LPP_GetUpResponseTimer
(
    NAS_LPP_UP_POS_REQ_TECH_TYPE_ENUM_UINT8 enUpPosTechType
);
extern NAS_LPP_TIMER_STRU*  NAS_LPP_GetUpPeriodicalTimer
(
    NAS_LPP_UP_POS_REQ_TECH_TYPE_ENUM_UINT8 enUpPosTechType
);
extern NAS_LPP_TIMER_STRU*  NAS_LPP_GetUpDurationTimer
(
    NAS_LPP_UP_POS_REQ_TECH_TYPE_ENUM_UINT8 enUpPosTechType
);
extern NAS_LPP_TIMER_STRU*  NAS_LPP_GetUpStateTimer
(
    NAS_LPP_UP_POS_REQ_TECH_TYPE_ENUM_UINT8 enUpPosTechType
);
extern VOS_UINT32  NAS_LPP_GetUpPrtcTimeLen
(
    NAS_LPP_TIMER_PARA_ENUM_UINT8       enTimeName,
    NAS_LPP_UP_POS_REQ_TECH_TYPE_ENUM_UINT8 enPosTechType
);
extern VOS_VOID   NAS_LPP_RcvMtaLppUpCapReq
(
    MTA_LPP_UP_CAPABILITY_REQ_STRU          *pstMtaLppUpCapREq
);
extern VOS_VOID  NAS_LPP_UPClrOtdoaCtx( VOS_VOID );
extern VOS_VOID  NAS_LPP_UPClrEcidCtx(VOS_VOID);
extern VOS_BOOL  NAS_LPP_GetEcidLrrcMeasFlag(VOS_VOID);
extern VOS_BOOL  NAS_LPP_GetOtodaLrrcMeasFlag(VOS_VOID);
extern VOS_VOID  NAS_LPP_UPClrEntity( VOS_VOID );
extern VOS_VOID NAS_LPP_UpTimerStart
(
    NAS_LPP_UP_POS_REQ_TECH_TYPE_ENUM_UINT8 enPosTechType,
    NAS_LPP_TIMER_PARA_ENUM_UINT8           enTimerType
);
extern VOS_UINT32  NAS_LPP_GetEcidPeriodReportCnt( VOS_VOID );
extern VOS_UINT32  NAS_LPP_GetEcidPeriodReportingCnt( VOS_VOID );
extern VOS_VOID  NAS_LPP_EcidPeriodReportingCntAddOne( VOS_VOID );
extern VOS_UINT32  NAS_LPP_GetOtodaPeriodReportCnt( VOS_VOID );
extern VOS_UINT32  NAS_LPP_GetOtodaPeriodReportingCnt( VOS_VOID );
extern VOS_VOID  NAS_LPP_LppUpEntityInit( VOS_VOID );
extern VOS_VOID  NAS_LPP_OmMtaLocInfoReq
(
    LPP_MTA_MSG_TYPE_ENUM_UINT32        enGnssAssistData
);
extern VOS_VOID  NAS_LPP_OmMtaAssistData
(
    LPP_MTA_MSG_TYPE_ENUM_UINT32        enGnssAssistData
);
extern VOS_VOID NAS_LPP_UpTimerStop
(
    NAS_LPP_UP_POS_REQ_TECH_TYPE_ENUM_UINT8 enPosTechType,
    NAS_LPP_TIMER_PARA_ENUM_UINT8           enTimerType
);
extern NAS_LPP_UP_OTDOA_INFO_STRU*  NAS_LPP_GetLppUpOtdoaCtx( VOS_VOID );
extern NAS_LPP_UP_POS_REQ_TECH_TYPE_ENUM_UINT8  NAS_LPP_GetEcidPosReqTechType(VOS_VOID);
extern NAS_LPP_UP_POS_REQ_TECH_TYPE_ENUM_UINT8  NAS_LPP_GetOtdoaPosReqTechType(VOS_VOID);
extern VOS_VOID NAS_LPP_UpChangeTransFsmState
(
    NAS_LPP_UP_STATE_ENUM_UINT32            enLppUpState,
    NAS_LPP_UP_POS_REQ_TECH_TYPE_ENUM_UINT8 enPosTechType
);
extern NAS_LPP_UP_ECID_INFO_STRU*  NAS_LPP_GetLppUpEcidCtx( VOS_VOID );
extern NAS_LPP_UP_REPORT_CRITERIA_STRU*  NAS_LPP_EcidReportTypeAddr(VOS_VOID);
extern NAS_LPP_UP_REPORT_CRITERIA_STRU*  NAS_LPP_OtdoaReportTypeAddr(VOS_VOID);
extern NAS_LPP_UP_REPORT_CRITERIA_STRU*  NAS_LPP_MultiPosTechReportTypeAddr(VOS_VOID);
extern VOS_VOID  NAS_LPP_SetEcidAndOtdoaMeasFlag(VOS_BOOL bReqEcidAndOtdoaFlag);
extern VOS_VOID  NAS_LPP_SetEcidPosType
(
    NAS_LPP_UP_POS_REQ_TECH_TYPE_ENUM_UINT8 enEcidPosType
);
extern VOS_VOID  NAS_LPP_SetOtdoaPosType
(
    NAS_LPP_UP_POS_REQ_TECH_TYPE_ENUM_UINT8 enOtodaPosType
);
extern VOS_VOID  NAS_LPP_SetEcidPosReqTechType
(
    NAS_LPP_UP_POS_REQ_TECH_TYPE_ENUM_UINT8 enUpPosReqTech
);
extern VOS_VOID  NAS_LPP_SetOtdoaPosReqTechType
(
    NAS_LPP_UP_POS_REQ_TECH_TYPE_ENUM_UINT8 enUpPosReqTech
);
extern VOS_BOOL  NAS_LPP_GetEcidAndOtdoaMeasFlag(VOS_VOID);
extern VOS_BOOL  NAS_LPP_GetOtdoaAssistDataFlag( VOS_VOID );
extern VOS_VOID  NAS_LPP_SaveSlotNumOffset
(
    LPP_LRRC_OTDOA_NEIGHBOUR_CELL_INFO_STRU     *pstOtdoaNghbrCellCfg,
    LPP_OTDOA_NEIGHBOUR_CELL_INFO_ELEMENT_STRU  *pstNgnbrCellElement
);
extern VOS_VOID   NAS_LPP_SaveOtdoaNghbrCell
(
    LPP_OTDOA_PROVIDE_ASSIST_DATA_STRU      *pstOtdoaAssist,
    NAS_LPP_OTDOA_ASSIST_CFG_STRU           *pstOtdoaAssisCfg
);
extern NAS_LPP_UP_POS_REQ_TECH_TYPE_ENUM_UINT8  NAS_LPP_GetEcidPosType( VOS_VOID );
extern NAS_LPP_UP_POS_REQ_TECH_TYPE_ENUM_UINT8  NAS_LPP_GetOtdoaPosType( VOS_VOID );
extern VOS_VOID NAS_LPP_PrePareGloIdPara
(
    LPP_MEAS_RESULT_ELEMENT_STRU            *pstMeasRsltEle,
    LRRC_LPP_ECID_MEAS_RESULT_STRU          *pstLrrcLppMeasRslt
);
extern NAS_LPP_ECID_MEAS_RESULT_STRU*  NAS_LPP_GetEcidLrrcMeasAddr(VOS_VOID);
extern VOS_UINT8  NAS_LPP_GetEcidReqMeasType(VOS_VOID);
extern LPP_MEAS_RESULT_ELEMENT_STRU* NAS_LPP_UpGetNeighberMeasRsltElement
(
    LPP_MTA_ECID_SIGNAL_MEAS_INFO_STRU      *pstEcidSignalMeasInfo,
    VOS_UINT32                               ulLoop
);
extern LPP_MEAS_RESULT_ELEMENT_STRU* NAS_LPP_UpGetPrimaryMeasRsltElement
(
    LPP_MTA_ECID_SIGNAL_MEAS_INFO_STRU      *pstEcidSignalMeasInfo
);
extern LRRC_LPP_ECID_MEAS_RESULT_STRU* NAS_LPP_GetLrrcEcidMeasRslt
(
    NAS_LPP_ECID_MEAS_RESULT_STRU         *pstEcidMeasRslt,
    VOS_UINT32                             ulLoop
);
extern LPP_MEAS_RESULT_ELEMENT_STRU* NAS_LPP_UpGetPrimaryMeasRsltElement
(
    LPP_MTA_ECID_SIGNAL_MEAS_INFO_STRU      *pstEcidSignalMeasInfo
);
extern NAS_LPP_OTDOA_MEAS_RESLT_STRU*  NAS_LPP_GetOtodaLrrcMeasAddr(VOS_VOID);
extern VOS_VOID  NAS_LPP_PrePareOtdoaSignalMeasInfo
(
    LPP_OTDOA_SIGNAL_MEAS_INFO_STRU         *pstOtdoaSignalMeasInfo,
    NAS_LPP_OTDOA_MEAS_RESLT_STRU           *pstOtdoaMeasRslt
);
extern VOS_VOID   NAS_LPP_RcvMtaLppUpMeasNotify
(
    MTA_LPP_UP_MEAS_NTY_STRU          *pstUpMeasNty
);
extern VOS_VOID   NAS_LPP_UpRcvMtaOtdoaAssistData
(
    MTA_LPP_UP_OTDOA_ASSIST_DATA_NTY_STRU                  *pstMtaLppUpOtdoaAssistData
);
extern VOS_VOID NAS_LPP_RcvMtaLppUpAbortMeas
(
    MTA_LPP_UP_MEAS_ABORT_NTY_STRU     *pstLppUpMeasAbort
);
extern VOS_VOID   NAS_LPP_SndUpLppMtaEcidMeasmentInd
(
    LPP_ECID_TARGET_DEVICE_ERROR_CAUSE_ENUM_UINT32 enEcidErrCause
);
extern VOS_VOID   NAS_LPP_SndUpLppMtaOtdoaMeasmentInd
(
    LPP_OTDOA_LOCATION_TARGET_DEVICE_ERROR_CAUSE_ENUM_UINT32  enOtdoaErrCause
);
extern VOS_VOID   NAS_LPP_SndUpLppMtaEcidAndOtodaMeasmentInd
(
    LPP_ECID_TARGET_DEVICE_ERROR_CAUSE_ENUM_UINT32            enEcidErrCause,
    LPP_OTDOA_LOCATION_TARGET_DEVICE_ERROR_CAUSE_ENUM_UINT32  enOtdoaErrCause
);
extern VOS_VOID   NAS_LPP_SndUpLppMtaMeasInd
(
    NAS_LPP_UP_POS_REQ_TECH_TYPE_ENUM_UINT8     enReqTechType

);
extern VOS_VOID   NAS_LPP_SndUpLppMtaEcidMeasAndOtodaErrInd
(
    LPP_OTDOA_LOCATION_TARGET_DEVICE_ERROR_CAUSE_ENUM_UINT32  enOtdoaErrCause
);
extern VOS_VOID   NAS_LPP_SndUpLppMtaOtodaMeasAndEcidErrInd
(
    LPP_ECID_TARGET_DEVICE_ERROR_CAUSE_ENUM_UINT32            enEcidErrCause
);
extern VOS_VOID NAS_LPP_LppInitExceptCap( VOS_VOID );
extern NAS_LPP_UP_MULTI_POS_TECH_INFO_STRU*  NAS_LPP_GetLppUpMultiPosTechCtx( VOS_VOID );

extern VOS_INT32 NAS_LPP_SecuMemCpy
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

#endif











































