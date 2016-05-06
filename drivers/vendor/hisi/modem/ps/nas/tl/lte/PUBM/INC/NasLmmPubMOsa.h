/******************************************************************************

        @(#)Copyright(C)2008,Hisilicon Co. LTD.

 ******************************************************************************
    File Name       : NasLmmPubMOsa.h
    Description     : NasLmmPubMOsa.c header file
    History         :
      1.  hanlufeng 41410  2009-03-11  BA8D01164 NAS_LMM_LOG 视为对PRINTF的
          适配，放在OSA文件中定义，避免对NasLmmPubMOm.h的包含；
          并增加MM ASSERT的定义
      2.  z00148421    2011-05-28   文件名由 NasMmPubMOsa.h修改为
                                    NasLmmPubMOsa.h
******************************************************************************/

#ifndef __NASLMMPUBMOSA_H__
#define __NASLMMPUBMOSA_H__

/*****************************************************************************
  1 其他头文件包含
*****************************************************************************/
#include    "vos.h"
#include    "PsLogdef.h"

#include    "PsCommonDef.h"

#include    "OmCommon.h"
#include    "NasLmmPubMPrint.h"
#include   "UsimPsInterface.h"
#include   "NasFileId.h"

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

/*#define NAS_LMM_ASSERT_ABORT     1    警告 : 此宏开关仅限于发生死机情况时进行PC调试 */




/*========================= OSA类封装 =========================BEGIN */
#define NAS_EMM_TIMER_PARA_NULL             0

#define NAS_EMM_LENGTH_OF_PRINT_LINE_BUF    256

#define NAS_LMM_NULL_PTR                     VOS_NULL_PTR


#define NAS_LOG_LEVEL_OFF               LOG_LEVEL_OFF        /* 关闭打印     */
#define NAS_LOG_LEVEL_ERROR             LOG_LEVEL_ERROR      /* Error级别    */
#define NAS_LOG_LEVEL_WARNING           LOG_LEVEL_WARNING    /* Warning级别  */
#define NAS_LOG_LEVEL_NORMAL            LOG_LEVEL_NORMAL     /* Normal级别   */
#define NAS_LOG_LEVEL_INFO              LOG_LEVEL_INFO       /* Info级别     */

#ifdef  PS_ITT_PC_TEST

#define NAS_LMM_LOG_INFO(SubModId,String)            vos_printf(" %s\r\n",String)
#define NAS_LMM_LOG_NORM(SubModId,String)            vos_printf(" %s\r\n",String)
#define NAS_LMM_LOG_WARN(SubModId,String)            vos_printf(" %s\r\n",String)
#define NAS_LMM_LOG_ERR(SubModId,String)             vos_printf(" %s\r\n",String)

#define NAS_LMM_LOG1_INFO(SubModId,String, Para1)    vos_printf(" %s %d\r\n",String,Para1)

#define NAS_LMM_LOG1_NORM(SubModId,String, Para1)    vos_printf(" %s %d\r\n",String,Para1)
#define NAS_LMM_LOG1_WARN(SubModId,String, Para1)    vos_printf(" %s %d\r\n",String,Para1)
#define NAS_LMM_LOG1_ERR(SubModId,String,  Para1)    vos_printf(" %s %d\r\n",String,Para1)

#define NAS_LMM_LOG2_INFO(SubModId,String, Para1, Para2)    vos_printf(" %s %d,%d\r\n",String,Para1,Para2)
#define NAS_LMM_LOG2_NORM(SubModId,String, Para1, Para2)    vos_printf(" %s %d,%d\r\n",String,Para1,Para2)
#define NAS_LMM_LOG2_WARN(SubModId,String, Para1, Para2)    vos_printf(" %s %d,%d\r\n",String,Para1,Para2)
#define NAS_LMM_LOG2_ERR(SubModId,String,  Para1, Para2)    vos_printf(" %s %d,%d\r\n",String,Para1,Para2)

#define NAS_LMM_LOG3_INFO(SubModId,String, Para1, Para2, Para3)    vos_printf(" %s %d,%d,%d\r\n",String,Para1,Para2,Para3)
#define NAS_LMM_LOG3_NORM(SubModId,String, Para1, Para2, Para3)    vos_printf(" %s %d,%d,%d\r\n",String,Para1,Para2,Para3)
#define NAS_LMM_LOG3_WARN(SubModId,String, Para1, Para2, Para3)    vos_printf(" %s %d,%d,%d\r\n",String,Para1,Para2,Para3)
#define NAS_LMM_LOG3_ERR(SubModId,String,  Para1, Para2, Para3)    vos_printf(" %s %d,%d,%d\r\n",String,Para1,Para2,Para3)

#else  /*For PS_ITT_PC_TEST*/

#define NAS_LMM_LOG_INFO(SubModId, String)            LPS_LOG(UE_MODULE_MM_ID, SubModId, NAS_LOG_LEVEL_INFO, String)
#define NAS_LMM_LOG_NORM(SubModId, String)            LPS_LOG(UE_MODULE_MM_ID, SubModId, NAS_LOG_LEVEL_NORMAL, String)
/* leixiantiao 00258641 EMM 添加可维可测 begin */
#define NAS_LMM_LOG_WARN(SubModId, String) \
    {\
        LPS_LOG(UE_MODULE_MM_ID, SubModId, NAS_LOG_LEVEL_WARNING, String);\
        NAS_LMM_SndDebugInfoInd(THIS_NAS_FILE_ID, __LINE__, VOS_NULL_PTR, VOS_NULL_PTR, VOS_NULL_PTR, VOS_NULL_PTR); \
    }
#define NAS_LMM_LOG_ERR(SubModId, String) \
    {\
        LPS_LOG(UE_MODULE_MM_ID, SubModId, NAS_LOG_LEVEL_ERROR, String); \
        NAS_LMM_SndDebugInfoInd(THIS_NAS_FILE_ID, __LINE__, VOS_NULL_PTR, VOS_NULL_PTR, VOS_NULL_PTR, VOS_NULL_PTR); \
    }

#define NAS_LMM_LOG1_INFO(SubModId, String, Para1)    LPS_LOG1(UE_MODULE_MM_ID, SubModId, NAS_LOG_LEVEL_INFO, String, (long)Para1)
#define NAS_LMM_LOG1_NORM(SubModId, String, Para1)    LPS_LOG1(UE_MODULE_MM_ID, SubModId, NAS_LOG_LEVEL_NORMAL, String, (long)Para1)
#define NAS_LMM_LOG1_WARN(SubModId, String, Para1) \
    {\
        LPS_LOG1(UE_MODULE_MM_ID, SubModId, NAS_LOG_LEVEL_WARNING, String, (long)Para1);\
        NAS_LMM_SndDebugInfoInd(THIS_NAS_FILE_ID, __LINE__, (VOS_UINT16)Para1, VOS_NULL_PTR, VOS_NULL_PTR, VOS_NULL_PTR); \
    }
#define NAS_LMM_LOG1_ERR(SubModId, String,  Para1) \
    {\
        LPS_LOG1(UE_MODULE_MM_ID, SubModId, NAS_LOG_LEVEL_ERROR, String, (long)Para1);\
        NAS_LMM_SndDebugInfoInd(THIS_NAS_FILE_ID, __LINE__, (VOS_UINT16)Para1, VOS_NULL_PTR, VOS_NULL_PTR, VOS_NULL_PTR); \
    }

#define NAS_LMM_LOG2_INFO(SubModId, String, Para1, Para2)    LPS_LOG2(UE_MODULE_MM_ID, SubModId, NAS_LOG_LEVEL_INFO, String, (long)Para1, (long)Para2)
#define NAS_LMM_LOG2_NORM(SubModId, String, Para1, Para2)    LPS_LOG2(UE_MODULE_MM_ID, SubModId, NAS_LOG_LEVEL_NORMAL, String, (long)Para1, (long)Para2)
#define NAS_LMM_LOG2_WARN(SubModId, String, Para1, Para2) \
    {\
        LPS_LOG2(UE_MODULE_MM_ID, SubModId, NAS_LOG_LEVEL_WARNING, String, (long)Para1, (long)Para2); \
        NAS_LMM_SndDebugInfoInd(THIS_NAS_FILE_ID, __LINE__, (VOS_UINT16)Para1, (VOS_UINT16)Para2, VOS_NULL_PTR, VOS_NULL_PTR); \
    }
#define NAS_LMM_LOG2_ERR(SubModId, String,  Para1, Para2) \
    { \
        LPS_LOG2(UE_MODULE_MM_ID, SubModId, NAS_LOG_LEVEL_ERROR,   String, (long)Para1, (long)Para2); \
        NAS_LMM_SndDebugInfoInd(THIS_NAS_FILE_ID, __LINE__, (VOS_UINT16)Para1, (VOS_UINT16)Para2, VOS_NULL_PTR, VOS_NULL_PTR); \
    }

#define NAS_LMM_LOG3_INFO(SubModId, String, Para1, Para2, Para3)    LPS_LOG3(UE_MODULE_MM_ID, SubModId, NAS_LOG_LEVEL_INFO, String, (long)Para1, (long)Para2, (long)Para3)
#define NAS_LMM_LOG3_NORM(SubModId, String, Para1, Para2, Para3)    LPS_LOG3(UE_MODULE_MM_ID, SubModId, NAS_LOG_LEVEL_NORMAL, String, (long)Para1, (long)Para2, (long)Para3)
#define NAS_LMM_LOG3_WARN(SubModId, String, Para1, Para2, Para3) \
    {\
        LPS_LOG3(UE_MODULE_MM_ID, SubModId, NAS_LOG_LEVEL_WARNING, String, (long)Para1, (long)Para2, (long)Para3);\
        NAS_LMM_SndDebugInfoInd(THIS_NAS_FILE_ID, __LINE__, (VOS_UINT16)Para1, (VOS_UINT16)Para2, (VOS_UINT16)Para3, VOS_NULL_PTR);\
    }
#define NAS_LMM_LOG3_ERR(SubModId, String,  Para1, Para2, Para3) \
    { \
        LPS_LOG3(UE_MODULE_MM_ID, SubModId, NAS_LOG_LEVEL_ERROR,   String, (long)Para1, (long)Para2, (long)Para3); \
        NAS_LMM_SndDebugInfoInd(THIS_NAS_FILE_ID, __LINE__, (VOS_UINT16)Para1, (VOS_UINT16)Para2, (VOS_UINT16)Para3, VOS_NULL_PTR); \
    }
/* leixiantiao 00258641 EMM 添加可维可测 end */

#endif


/*=============================== 以下为PUBM 专用 ============================*/

#define NAS_LMM_PUBM_LOG_INFO(String)                     NAS_LMM_LOG_INFO(LOG_SUBMOD_ID_NAS_LMM_PUBM, String)
#define NAS_LMM_PUBM_LOG_NORM(String)                     NAS_LMM_LOG_NORM(LOG_SUBMOD_ID_NAS_LMM_PUBM, String)
#define NAS_LMM_PUBM_LOG_WARN(String)                     NAS_LMM_LOG_WARN(LOG_SUBMOD_ID_NAS_LMM_PUBM, String)
#define NAS_LMM_PUBM_LOG_ERR(String)                      NAS_LMM_LOG_ERR(LOG_SUBMOD_ID_NAS_LMM_PUBM, String)

#define NAS_LMM_PUBM_LOG1_INFO(String, Para1)             NAS_LMM_LOG1_INFO(LOG_SUBMOD_ID_NAS_LMM_PUBM, String, Para1)
#define NAS_LMM_PUBM_LOG1_NORM(String, Para1)             NAS_LMM_LOG1_NORM(LOG_SUBMOD_ID_NAS_LMM_PUBM, String, Para1)
#define NAS_LMM_PUBM_LOG1_WARN(String, Para1)             NAS_LMM_LOG1_WARN(LOG_SUBMOD_ID_NAS_LMM_PUBM, String, Para1)
#define NAS_LMM_PUBM_LOG1_ERR(String,  Para1)             NAS_LMM_LOG1_ERR(LOG_SUBMOD_ID_NAS_LMM_PUBM, String,  Para1)

#define NAS_LMM_PUBM_LOG2_INFO(String, Para1, Para2)      NAS_LMM_LOG2_INFO(LOG_SUBMOD_ID_NAS_LMM_PUBM, String, Para1, Para2)
#define NAS_LMM_PUBM_LOG2_NORM(String, Para1, Para2)      NAS_LMM_LOG2_NORM(LOG_SUBMOD_ID_NAS_LMM_PUBM, String, Para1, Para2)
#define NAS_LMM_PUBM_LOG2_WARN(String, Para1, Para2)      NAS_LMM_LOG2_WARN(LOG_SUBMOD_ID_NAS_LMM_PUBM, String, Para1, Para2)
#define NAS_LMM_PUBM_LOG2_ERR(String,  Para1, Para2)      NAS_LMM_LOG2_ERR(LOG_SUBMOD_ID_NAS_LMM_PUBM, String,  Para1, Para2)

#define NAS_LMM_PUBM_LOG3_INFO(String, Para1, Para2, Para3)    NAS_LMM_LOG3_INFO(LOG_SUBMOD_ID_NAS_LMM_PUBM, String, Para1, Para2, Para3)
#define NAS_LMM_PUBM_LOG3_NORM(String, Para1, Para2, Para3)    NAS_LMM_LOG3_NORM(LOG_SUBMOD_ID_NAS_LMM_PUBM, String, Para1, Para2, Para3)
#define NAS_LMM_PUBM_LOG3_WARN(String, Para1, Para2, Para3)    NAS_LMM_LOG3_WARN(LOG_SUBMOD_ID_NAS_LMM_PUBM, String, Para1, Para2, Para3)
#define NAS_LMM_PUBM_LOG3_ERR(String,  Para1, Para2, Para3)    NAS_LMM_LOG3_ERR(LOG_SUBMOD_ID_NAS_LMM_PUBM, String,  Para1, Para2, Para3)





#if (VOS_OS_VER == VOS_WIN32)

#define NAS_LMM_MEM_CPY_S(pucDestBuffer, ulMaxDest, pucSrcBuffer, ulBufferLen) \
    NAS_LMM_SecuMemCpy((pucDestBuffer), (ulMaxDest), (pucSrcBuffer), (ulBufferLen), (__LINE__), (THIS_FILE_ID))

#define NAS_LMM_MEM_SET_S(pucBuffer, ulMaxDest, ucData, ulBufferLen) \
    NAS_LMM_SecuMemSet((pucBuffer), (ulMaxDest), (ucData), (ulBufferLen), (__LINE__), (THIS_FILE_ID))

#define NAS_LMM_MEM_MOVE_S(pucDestBuffer, ulMaxDest, pucSrcBuffer, ulBufferLen) \
    NAS_LMM_SecuMemMove( (pucDestBuffer), (ulMaxDest), (pucSrcBuffer), (ulBufferLen), (__LINE__), (THIS_FILE_ID))

#else
#define NAS_LMM_MEM_CPY_S(pucDestBuffer, ulMaxDest, pucSrcBuffer, ulBufferLen) \
        (VOS_VOID)NAS_LMM_PUBM_SecuMemCpy((pucDestBuffer), (ulMaxDest), (pucSrcBuffer), (ulBufferLen), (__LINE__), (THIS_FILE_ID))

#define NAS_LMM_MEM_SET_S(pucBuffer, ulMaxDest, ucData, ulBufferLen) \
        (VOS_VOID)TLPS_MEM_SET_S((pucBuffer), (ulMaxDest), (ucData), (ulBufferLen), (__LINE__), (THIS_FILE_ID))

#define NAS_LMM_MEM_MOVE_S(pucDestBuffer, ulMaxDest, pucSrcBuffer, ulBufferLen) \
        (VOS_VOID)TLPS_MEM_MOVE_S((pucDestBuffer), (ulMaxDest), (pucSrcBuffer), (ulBufferLen), (__LINE__), (THIS_FILE_ID))

#endif



/* MM层DOPRA消息申请宏定义 */
#define NAS_LMM_ALLOC_MSG(ulLen)\
            PS_ALLOC_MSG_ALL_CHECK((PS_PID_MM),(ulLen))

/* MM层内存释放宏定义 */
#define NAS_LMM_FREE_MSG(pData)\
            PS_FREE_MSG_ALL_CHECK((PS_PID_MM),(pData))

/* MM层内存分配宏定义 */
#define NAS_LMM_MEM_ALLOC(ulSize) \
            PS_MEM_ALLOC_All_CHECK((PS_PID_MM), (ulSize))

#if (VOS_OS_VER != VOS_WIN32)
/* MM层内存分配宏定义 */
#define NAS_LMM_MEM_FREE(pAddr) \
            {\
                if(NAS_EMM_OK != PS_MEM_FREE_ALL_CHECK((PS_PID_MM), (pAddr)))\
                {\
                    NAS_LMM_PUBM_LOG_ERR("NAS_LMM_MEM_FREE  ERR!!");\
                }\
            }
#else
#define NAS_LMM_MEM_FREE(pAddr)  PS_MEM_FREE_ALL_CHECK((PS_PID_MM), (pAddr));
#endif

#if (VOS_OS_VER != VOS_WIN32)
#define NAS_LMM_SEND_MSG(pMsg) \
        {\
            NAS_LMM_PUBM_PrintSendMsg((const PS_MSG_HEADER_STRU *)pMsg,NAS_COMM_GET_MM_PRINT_BUF());\
            if(NAS_EMM_OK != PS_SND_MSG_ALL_CHECK((PS_PID_MM), (pMsg)))\
            {\
                NAS_LMM_PUBM_LOG_ERR("NAS_LMM_SEND_MSG  ERR!!");\
            }\
        }
#else
#define NAS_LMM_SEND_MSG(pMsg) \
        {\
            NAS_LMM_PUBM_PrintSendMsg((const PS_MSG_HEADER_STRU *)pMsg,NAS_COMM_GET_MM_PRINT_BUF());\
            PS_SND_MSG_ALL_CHECK((PS_PID_MM), (pMsg));\
        }
#endif

#if (VOS_OS_VER != VOS_WIN32)
#define NAS_EMM_SEND_INTRA_MSG(pIntraMsg)\
        {\
            NAS_LMM_PUBM_PrintSendMsg((const PS_MSG_HEADER_STRU *)pIntraMsg,\
                                      NAS_COMM_GET_MM_PRINT_BUF());\
            if(NAS_EMM_OK !=  NAS_LMM_SendIntraMsg((pIntraMsg)))\
            {\
                NAS_LMM_PUBM_LOG_ERR("NAS_EMM_SEND_INTRA_MSG  ERR!!");\
            }\
        }
#else
#define NAS_EMM_SEND_INTRA_MSG(pIntraMsg)\
    {\
        NAS_LMM_PUBM_PrintSendMsg((const PS_MSG_HEADER_STRU *)pIntraMsg,\
                                  NAS_COMM_GET_MM_PRINT_BUF());\
        NAS_LMM_SendIntraMsg((pIntraMsg));\
    }
#endif

#define NAS_LMM_SEND_URGENT_MSG(pMsg) \
        {\
            NAS_LMM_PUBM_PrintSendMsg((const PS_MSG_HEADER_STRU *)pMsg,NAS_COMM_GET_MM_PRINT_BUF());\
            if(NAS_EMM_OK != PS_SND_URGENT_MSG((PS_PID_MM), (pMsg)))\
            {\
                NAS_LMM_PUBM_LOG_ERR("NAS_LMM_SEND_URGENT_MSG  ERR!!");\
            }\
        }

/*****************************************************************************
  3 Massage Declare
*****************************************************************************/



/*****************************************************************************
  4 Enum
*****************************************************************************/


/*****************************************************************************
  5 STRUCT
*****************************************************************************/

/*typedef struct MsgCB                    NAS_EMM_MSG_STRU;
 */

/*****************************************************************************
 结构名    : NasMmIntraMsgCB
 结构说明  : NAS_LMM内部消息结构,同VOS申请时分配的结构 MsgCB
*****************************************************************************/
struct NasMmMsgCB
{
    VOS_MSG_HEADER
    VOS_UINT8 aucValue[4];
};

typedef struct NasMmMsgCB               NasMmMsgBlock;


/*****************************************************************************
  6 UNION
*****************************************************************************/


/*****************************************************************************
  7 Extern Global Variable
*****************************************************************************/


/*****************************************************************************
  8 Fuction Extern
*****************************************************************************/

extern VOS_INT32 NAS_LMM_PUBM_SecuMemCpy
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

#endif /* end of NasLmmPubMOsa.h*/
