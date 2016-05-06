/******************************************************************************

  Copyright(C)2008,Hisilicon Co. LTD.

 ******************************************************************************
  File Name       : NasETcPublic.h
  Description     : NasETcPublic.c header file
  History         :
      1.李洪 00150010       2009-10-13  Draft Enact

******************************************************************************/

#ifndef __NASTCPUBLIC_H__
#define __NASTCPUBLIC_H__

/*****************************************************************************
  1 Include Headfile
*****************************************************************************/
#include "LTcPdcpInterface.h"
#include  "PsTypeDef.h"
#include  "PsCommonDef.h"
#include  "PsLogdef.h"
#include  "NasCommPrint.h"
#include  "msp.h"
#include  "CdsEtcInterface.h"
#include  "NasFileId.h"

#if (VOS_OS_VER != VOS_WIN32)
#include  "LPsOm.h"
#endif



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
#define NAS_ETC_NULL                     (0)
#define NAS_ETC_MSG_LOW_BIT              (0x0F)
#define NAS_ETC_MSG_HIGH_BIT             (0xF0)
#define NAS_ETC_MSG_LOW_5_BIT            (0x1F)

#define NAS_ETC_OP_TRUE                  (1)
#define NAS_ETC_OP_FALSE                 (0)

#define NAS_ETC_MOVEMENT_4_BITS          (4)
#define NAS_ETC_MOVEMENT_8_BITS          (8)

#define NAS_ETC_SKIP_INDICATOR           (0)

/*上行空口消息的缓存长度*/
#define NAS_ETC_UL_AIR_MSG_BUFFER_LEN    (4)

#define NAS_ETC_MSG_PD                   (0x0F)              /*TC 消息的PD(低4位)为1111*/

#ifdef PS_ITT_PC_TEST
#define NAS_ETC_INFO_LOG(String) \
                 vos_printf(" %s\r\n",String)
#define NAS_ETC_NORM_LOG(String) \
                 vos_printf(" %s\r\n",String)
#define NAS_ETC_WARN_LOG(String) \
                 vos_printf(" %s\r\n",String)
#define NAS_ETC_ERR_LOG(String) \
                 vos_printf(" %s\r\n",String)
#define NAS_ETC_LOG1(String, Para1) \
                 vos_printf(" %s %d\r\n",String, (long)Para1)
#define NAS_ETC_LOG2(String, Para1, Para2) \
                 vos_printf(" %s %d %d\r\n",String, (long)Para1, (long)Para2)
#else
#define NAS_ETC_INFO_LOG(String) \
                 LPS_LOG(UE_MODULE_TC_ID, VOS_NULL, LOG_LEVEL_INFO, String)
#define NAS_ETC_NORM_LOG(String) \
                 LPS_LOG(UE_MODULE_TC_ID, VOS_NULL, LOG_LEVEL_NORMAL, String)
#define NAS_ETC_WARN_LOG(String) \
                 LPS_LOG(UE_MODULE_TC_ID, VOS_NULL, LOG_LEVEL_WARNING, String)
#define NAS_ETC_ERR_LOG(String) \
                 LPS_LOG(UE_MODULE_TC_ID, VOS_NULL, LOG_LEVEL_ERROR, String)
#define NAS_ETC_LOG1(String, Para1) \
                 LPS_LOG1(UE_MODULE_TC_ID, VOS_NULL, LOG_LEVEL_NORMAL, String, (long)Para1 )
#define NAS_ETC_LOG2(String, Para1, Para2) \
                 LPS_LOG2(UE_MODULE_TC_ID, VOS_NULL, LOG_LEVEL_NORMAL, String, (long)Para1, (long)Para2)

#endif

#define NAS_ETC_GET_MSG_LENGTH(pMsg)        ((pMsg)->ulLength)
#define NAS_ETC_GET_MSG_ENTITY(pMsg)        ((VOS_VOID*)&((pMsg)->ulMsgId))
#define NAS_ETC_GET_TC_PDCP_MSG_ENTITY(pMsg)((VOS_VOID*)&((pMsg)->enMsgName))
#define NAS_ETC_GET_TC_MTC_MSG_ENTITY(pMsg)((VOS_VOID*)&((pMsg)->ulMsgName))



/*封装写EMM消息头的宏*/
#define NAS_ETC_WRITE_EMM_MSG_HEAD(pstMsg, ulEmmMsgID)\
                    (pstMsg)->ulMsgId           = (ulEmmMsgID);\
                    (pstMsg)->ulSenderCpuId     = VOS_LOCAL_CPUID;\
                    (pstMsg)->ulSenderPid       = PS_PID_TC;\
                    (pstMsg)->ulReceiverCpuId   = VOS_LOCAL_CPUID;\
                    (pstMsg)->ulReceiverPid     = PS_PID_MM;

/*封装写RABM消息头的宏*/
#define NAS_ETC_WRITE_RABM_MSG_HEAD(pstMsg, ulRabmMsgID)\
                    (pstMsg)->ulMsgId           = (ulRabmMsgID);\
                    (pstMsg)->ulSenderCpuId     = VOS_LOCAL_CPUID;\
                    (pstMsg)->ulSenderPid       = PS_PID_TC;\
                    (pstMsg)->ulReceiverCpuId   = VOS_LOCAL_CPUID;\
                    (pstMsg)->ulReceiverPid     = PS_PID_RABM;

/*封装写PDCP UL消息头的宏*/
#define NAS_ETC_WRITE_PDCP_MSG_HEAD(pstMsg, ulPdcpMsgID)\
                    (pstMsg)->enMsgName         = (ulPdcpMsgID);\
                    (pstMsg)->ulSenderCpuId     = VOS_LOCAL_CPUID;\
                    (pstMsg)->ulSenderPid       = PS_PID_TC;\
                    (pstMsg)->ulReceiverCpuId   = VOS_LOCAL_CPUID;\
                    (pstMsg)->ulReceiverPid     = PS_PID_PDCP_UL;

#define NAS_ETC_WRITE_CDS_MSG_HEAD(pstMsg, ulCdsMsgID)\
                    (pstMsg)->enMsgId         = (ulCdsMsgID);\
                    (pstMsg)->ulSenderCpuId     = VOS_LOCAL_CPUID;\
                    (pstMsg)->ulSenderPid       = PS_PID_TC;\
                    (pstMsg)->ulReceiverCpuId   = VOS_LOCAL_CPUID;\
                    (pstMsg)->ulReceiverPid     = UEPS_PID_CDS;

/*封装写MTC消息头的宏*/
#define NAS_ETC_WRITE_MTC_MSG_HEAD(pstMsg, ulMtcMsgName)\
                    (pstMsg)->ulMsgName         = (ulMtcMsgName);\
                    (pstMsg)->ulSenderCpuId     = VOS_LOCAL_CPUID;\
                    (pstMsg)->ulSenderPid       = PS_PID_TC;\
                    (pstMsg)->ulReceiverCpuId   = VOS_LOCAL_CPUID;\
                    (pstMsg)->ulReceiverPid     = UEPS_PID_MTC;



/* 内存拷贝宏定义 */

#if (VOS_OS_VER == VOS_WIN32)

#define NAS_ETC_MEM_CPY_S(pucDestBuffer, ulMaxDest, pucSrcBuffer, ulBufferLen) \
    NAS_LMM_SecuMemCpy((pucDestBuffer), (ulMaxDest), (pucSrcBuffer), (ulBufferLen), (__LINE__), (THIS_FILE_ID))

#define NAS_ETC_MEM_SET_S(pucBuffer, ulMaxDest, ucData, ulBufferLen) \
    NAS_LMM_SecuMemSet((pucBuffer), (ulMaxDest), (ucData), (ulBufferLen), (__LINE__), (THIS_FILE_ID))

#define NAS_ETC_MEM_MOVE_S(pucDestBuffer, ulMaxDest, pucSrcBuffer, ulBufferLen) \
    NAS_LMM_SecuMemMove( (pucDestBuffer), (ulMaxDest), (pucSrcBuffer), (ulBufferLen), (__LINE__), (THIS_FILE_ID))

#else
#define NAS_ETC_MEM_CPY_S(pDestBuffer, ulMaxDest, pSrcBuffer, ulLength ) \
        (VOS_VOID)NAS_ETC_SecuMemCpy((pDestBuffer), (ulMaxDest), (pSrcBuffer), (ulLength), (__LINE__), (THIS_FILE_ID))

#define NAS_ETC_MEM_SET_S(pucBuffer, ulMaxDest, ucData, ulBufferLen )   \
        (VOS_VOID)TLPS_MEM_SET_S((pucBuffer), (ulMaxDest), (ucData), (ulBufferLen), (__LINE__), (THIS_FILE_ID))

#define NAS_ETC_MEM_MOVE_S(pucDestBuffer, ulMaxDest, pucSrcBuffer, ulBufferLen) \
        (VOS_VOID)TLPS_MEM_MOVE_S( (pucDestBuffer), (ulMaxDest), (pucSrcBuffer), (ulBufferLen), (__LINE__), (THIS_FILE_ID))

#endif


#define NAS_ETC_ALLOC_MSG(ulLen) \
        PS_ALLOC_MSG_ALL_CHECK((PS_PID_TC),(ulLen))
    /* 发送消息 */
#define NAS_ETC_SND_MSG(pMsg)\
    {\
        NAS_ETC_PrintTcSendMsg((const PS_MSG_HEADER_STRU *)pMsg,NAS_COMM_GET_ESM_PRINT_BUF());\
        if(VOS_OK != PS_SND_MSG_ALL_CHECK((PS_PID_TC) , (pMsg)))\
        {\
            NAS_ETC_ERR_LOG("PS_SND_MSG:Msg Snd Err!");\
        }\
    }

/*内存释放*/
#define NAS_ETC_MEM_FREE(pAddr)\
    {\
        if(VOS_OK != PS_MEM_FREE_ALL_CHECK((PS_PID_TC), (pAddr)))\
        {\
            NAS_ETC_ERR_LOG("NAS_ETC_MEM_FREE  ERR!!");\
        }\
    }

/*内存动态分配*/
#define NAS_ETC_MEM_ALLOC(ulSize)\
            PS_MEM_ALLOC_All_CHECK((PS_PID_TC) , (ulSize))

#define NAS_ETC_PRINT_LMODESTA(LModeStatus)\
            switch (LModeStatus)\
            {\
                case    NAS_ETC_L_MODE_STATUS_NORMAL   :\
                    NAS_ETC_NORM_LOG("TC L_MODE_NORMAL");\
                    break;\
                case    NAS_ETC_L_MODE_STATUS_SUSPENDED:\
                    NAS_ETC_NORM_LOG("TC L_MODE_SUSPENDED");\
                    break;\
                case    NAS_ETC_L_MODE_STATUS_BUTT:\
                default   :\
                    NAS_ETC_NORM_LOG("TC UKNOWN L MODE STATUS");\
                    break;\
            }
/*****************************************************************************
  3 Massage Declare
*****************************************************************************/


/*****************************************************************************
  4 Enum
*****************************************************************************/
/*****************************************************************************
 枚举名    : NAS_ETC_CAUSE_ENUM
 枚举说明  : 译码空口消息错误类型枚举
 ***************************************************************************/
enum NAS_ETC_CAUSE_ENUM
{
    NAS_ETC_CAUSE_SUCCESS                                   = 0,
    NAS_ETC_CAUSE_ERROR                                     = 1,

    NAS_ETC_CAUSE_BUTT
};
typedef VOS_UINT8   NAS_ETC_CAUSE_ENUM_UINT8;

enum NAS_ETC_L_MODE_STATUS_ENUM
{
    NAS_ETC_L_MODE_STATUS_NORMAL        = 0,                /*正常态*/
    NAS_ETC_L_MODE_STATUS_SUSPENDED     = 1,                /*挂起态*/

    NAS_ETC_L_MODE_STATUS_BUTT
};
typedef VOS_UINT8 NAS_ETC_L_MODE_STATUS_ENUM_UINT8;

/* ETC工作模式 */
enum NAS_ETC_MODE_TYPE_ENUM
{
    NAS_ETC_MODE_TYPE_NORMAL           =      0,        /*正常模式*/
    NAS_ETC_MODE_TYPE_LB               =      1,        /*环回模式*/

    NAS_ETC_MODE_TYPE_BUTT
};
typedef VOS_UINT32 NAS_ETC_MODE_TYPE_ENUM_UINT32;

/*****************************************************************************
 枚举名    : NAS_ETC_CNMSG_TYPE_ENUM
 枚举说明  : 空口消息类型枚举
 ***************************************************************************/
enum NAS_ETC_CNMSG_TYPE_ENUM
{
    /* 消息名称 */                                         /*消息ID*/    /* 备注 */
    NAS_ETC_CNMSG_TYPE_ACT_TEST_MODE                         = 0x84,      /*激活环回测试模式     1000  0100   ACTIVATE TEST MODE */
    NAS_ETC_CNMSG_TYPE_ACT_TEST_MODE_COMPLETE                = 0x85,      /*激活环回测试模式回复 1000  0101   ACTIVATE TEST MODE COMPLETE  */

    NAS_ETC_CNMSG_TYPE_DEACT_TEST_MODE                       = 0x86,      /*关闭环回测试模式     1000  0110   DEACTIVATE TEST MODE  */
    NAS_ETC_CNMSG_TYPE_DEACT_TEST_MODE_COMPLETE              = 0x87,      /*关闭环回测试模式回复 1000  0111   DEACTIVATE TEST MODE COMPLETE  */

    NAS_ETC_CNMSG_TYPE_CLOSE_UE_TEST_LOOP                    = 0x80,      /*打开环回测试功能     1000  0000   CLOSE UE TEST LOOP  */
    NAS_ETC_CNMSG_TYPE_CLOSE_UE_TEST_LOOP_COMPLETE           = 0x81,      /*打开环回测试功能回复 1000  0001   CLOSE UE TEST LOOP COMPLETE  */

    NAS_ETC_CNMSG_TYPE_OPEN_UE_TEST_LOOP                     = 0x82,      /*关闭环回测试功能     1000  0010   OPEN UE TEST LOOP  */
    NAS_ETC_CNMSG_TYPE_OPEN_UE_TEST_LOOP_COMPLETE            = 0x83,      /*关闭环回测试功能回复 1000  0011   OPEN UE TEST LOOP COMPLETE  */

    NAS_ETC_CNMSG_TYPE_RESET_UE_POSITION_INFO                = 0x88,      /*复位UE的位置信息     1000  1000*/

    NAS_ETC_CNMSG_TYPE_BUTT
};
typedef VOS_UINT8    NAS_ETC_CNMSG_TYPE_ENUM_UINT8;

/*****************************************************************************
  5 STRUCT
*****************************************************************************/
/*****************************************************************************
 结构名    : NAS_ETC_NW_MSG_STRU
 结构说明  : 记录空口消息的数据结构
 ***************************************************************************/
typedef struct
{
    VOS_UINT32                          bitOpLBMode                 : 1;
    VOS_UINT32                          bitOpLBModeA                : 1;
    VOS_UINT32                          bitOpLBModeB                : 1;
    VOS_UINT32                          bitOpSpare                  : 29;

    NAS_ETC_CNMSG_TYPE_ENUM_UINT8        enTcCnMsgType;             /* 空口消息类型 */
    LTC_LPDCP_LOOPBACK_MODE_ENUM_UINT32   enLoopBackMode;
    LLOOP_BACK_MODE_A_STRU               stLBModeA;
    LLOOP_BACK_MODE_B_STRU               stLBModeB;
    VOS_UINT8                            ucUePositionTech;
    VOS_UINT8                            aucRsv[3];
}NAS_ETC_NW_MSG_STRU;


/*****************************************************************************
  6 UNION
*****************************************************************************/


/*****************************************************************************
  7 Extern Global Variable
*****************************************************************************/
extern NAS_ETC_L_MODE_STATUS_ENUM_UINT8          g_enEtcLModeStatus;

extern NAS_ETC_MODE_TYPE_ENUM_UINT32            g_enEtcModeType;

#define NAS_ETC_GetLModeStatus()                 (g_enEtcLModeStatus)

#define NAS_ETC_SetLModeStatus(ucLModeStatus)\
            {\
                 NAS_ETC_NORM_LOG("~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~");\
                 NAS_ETC_NORM_LOG("TC L Mode Status change----");\
                 NAS_ETC_PRINT_LMODESTA(NAS_ETC_GetLModeStatus());\
                 NAS_ETC_NORM_LOG("==>>");\
                 (g_enEtcLModeStatus = (ucLModeStatus));\
                 NAS_ETC_PRINT_LMODESTA(ucLModeStatus);\
                 NAS_ETC_NORM_LOG("~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~");\
            }

#define NAS_ETC_GetModeType()                 (g_enEtcModeType)

#define NAS_ETC_SetModeType(enModeType)\
            {\
                 NAS_ETC_NORM_LOG("~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~");\
                 NAS_ETC_NORM_LOG("TC Mode Type change----");\
                 NAS_ETC_NORM_LOG("==>>");\
                 (g_enEtcModeType = (enModeType));\
                 NAS_ETC_NORM_LOG("~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~");\
            }

/*****************************************************************************
  8 Fuction Extern
*****************************************************************************/

extern VOS_INT32 NAS_ETC_SecuMemCpy
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

#endif /* end of NasETcPublic.h */
