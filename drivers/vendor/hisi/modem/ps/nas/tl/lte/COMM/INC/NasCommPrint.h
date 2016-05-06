

#ifndef __NASCOMMPRINT_H__
#define __NASCOMMPRINT_H__


/*****************************************************************************
  1 Include Headfile
*****************************************************************************/
#include  "PsTypeDef.h"
#include  "EmmEsmInterface.h"
#include  "EmmRabmInterface.h"
#include  "TcRabmInterface.h"
#include  "EmmTcInterface.h"
#include  "EsmRabmInterface.h"
#include  "LPsOm.h"


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

extern VOS_CHAR                    g_acPrintBuf[];
extern VOS_CHAR                    g_acEsmPrintBuf[];

/*****************************************************************************
  2 macro
*****************************************************************************/
/* delay begin */
extern VOS_UINT32 g_ulTimeDelaySwitch;
/* delay end */

#if (FEATURE_LPP == FEATURE_ON)
extern VOS_CHAR                                 g_acLppPrintBuf[];
#endif

#define NAS_COMM_PRINT_MAX_ITEM_LEN             (80)                /* 数组中字符串最大长度 */
#define NAS_COMM_PRINT_SEP_LEN                  (5)                 /* 每次打印间隔长度 */
#define NAS_COMM_PRINT_BUFF_LEN                 (3096)              /* 1024每次打印预设缓存 */
#define NAS_COMM_PRINT_MAX_BYTES_PER_LINE       (16)                /* 每行打印字节数   */

#define NAS_COMM_GET_MM_PRINT_BUF()             (g_acPrintBuf)
#define NAS_COMM_GET_ESM_PRINT_BUF()            (g_acEsmPrintBuf)
#if (FEATURE_LPP == FEATURE_ON)
#define NAS_COMM_GET_LPP_PRINT_BUF()            (g_acLppPrintBuf)
#endif


/*****************************************************************************
  3 Massage Declare
*****************************************************************************/


/*****************************************************************************
  4 Enum
*****************************************************************************/


/*****************************************************************************
   5 STRUCT
*****************************************************************************/
/* 打印动作函数类型的定义 */
typedef VOS_INT32 (* NAS_COMM_PRINT_ACTION_FUN)
(
    VOS_CHAR                                *pcBuff,
    VOS_UINT16                               usOffset,
    const PS_MSG_HEADER_STRU                *pstMsg
);


typedef struct
{
    VOS_UINT32                  ulId;
    VOS_UINT8                   aucPrintString[NAS_COMM_PRINT_MAX_ITEM_LEN];
    NAS_COMM_PRINT_ACTION_FUN   pfActionFun;
}NAS_COMM_PRINT_LIST_STRU;

typedef struct
{
    VOS_UINT32      ulId;
    VOS_UINT8       aucPrintString[NAS_COMM_PRINT_MAX_ITEM_LEN];
}NAS_COMM_PRINT_MSG_LIST_STRU;


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


extern VOS_VOID    NAS_COMM_nsprintf(
                           VOS_CHAR                                *pcBuff,
                           VOS_UINT16                              usOffset,
                           const VOS_CHAR                          *String,
                           VOS_INT32                               *pilOutLen );
extern VOS_VOID    NAS_COMM_nsprintf_1
       (
           VOS_CHAR                                *pcBuff,
           VOS_UINT16                              usOffset,
           const VOS_CHAR                          *String,
           VOS_UINT32                               para1,
           VOS_INT32                               *pilOutLen
       );
extern VOS_VOID    NAS_COMM_nsprintf_2(
                           VOS_CHAR                                *pcBuff,
                           VOS_UINT16                              usOffset,
                           const VOS_CHAR                          *String,
                           VOS_UINT32                               para1,
                           VOS_UINT32                               para2,
                           VOS_INT32                               *pilOutLen );
extern VOS_VOID    NAS_COMM_nsprintf_3(
                           VOS_CHAR                                *pcBuff,
                           VOS_UINT16                              usOffset,
                           const VOS_CHAR                          *String,
                           VOS_UINT32                               para1,
                           VOS_UINT32                               para2,
                           VOS_UINT32                               para3,
                           VOS_INT32                               *pilOutLen );
extern VOS_VOID    NAS_COMM_Print
       (
           VOS_CHAR                                *pcBuff,
           VOS_UINT16                              usLen
       );
extern VOS_VOID   NAS_COMM_PrintArray
(
    VOS_CHAR                                    *pcBuff,
    const VOS_UINT8                             *pucArray,
    const VOS_UINT32                             ulLen
);

extern VOS_INT32   NAS_COMM_PrintMmRabmMsg
(
    VOS_CHAR                                *pcBuff,
    VOS_UINT16                               usOffset,
    EMM_ERABM_MSG_TYPE_ENUM_UINT32            enMsgId
);

extern VOS_INT32   NAS_COMM_PrintMmEsmMsg
(
    VOS_CHAR                                *pcBuff,
    VOS_UINT16                               usOffset,
    const PS_MSG_HEADER_STRU                *pstMsg
);

extern VOS_INT32   NAS_COMM_PrintSmEsmMsg
(
    VOS_CHAR                                *pcBuff,
    VOS_UINT16                               usOffset,
    const PS_MSG_HEADER_STRU                *pstMsg
);

extern VOS_INT32  NAS_COMM_PrintMmEsmBearerStatusReqOrInd
(
    VOS_CHAR                                *pcBuff,
    VOS_UINT16                               usOffset,
    const PS_MSG_HEADER_STRU                *pstMsg
);

extern VOS_INT32  NAS_COMM_PrintEsmRabmMsg
(
    VOS_CHAR                            *pcBuff,
    VOS_UINT16                           usOffset,
    const PS_MSG_HEADER_STRU            *pstMsg
);

extern VOS_INT32  NAS_COMM_PrintRabmTcMsg
(
    VOS_CHAR                            *pcBuff,
    VOS_UINT16                           usOffset,
    ETC_ERABM_MSG_TYPE_ENUM_UINT32         enMsgId
);

extern VOS_INT32  NAS_COMM_PrintMmTcMsg
(
    VOS_CHAR                            *pcBuff,
    VOS_UINT16                           usOffset,
    EMM_ETC_MSG_TYPE_ENUM_UINT32          enMsgId
);

extern VOS_INT32  NAS_COMM_PrintEsmRabmBearerStatusReqMsg
(
    VOS_CHAR                                *pcBuff,
    VOS_UINT16                               usOffset,
    const PS_MSG_HEADER_STRU                *pstMsg
);

extern VOS_INT32  NAS_COMM_PrintEsmRabmActIndOrModIndMsg
(
    VOS_CHAR                                *pcBuff,
    VOS_UINT16                               usOffset,
    const PS_MSG_HEADER_STRU                *pstMsg
);

extern VOS_INT32  NAS_COMM_PrintEsmRabmDeactIndMsg
(
    VOS_CHAR                                *pcBuff,
    VOS_UINT16                               usOffset,
    const PS_MSG_HEADER_STRU                *pstMsg
);

#if (FEATURE_ON == FEATURE_UE_MODE_CDMA)
extern VOS_INT32   NAS_COMM_PrintEhsmEsmMsg
(
    VOS_CHAR                                *pcBuff,
    VOS_UINT16                               usOffset,
    const PS_MSG_HEADER_STRU                *pstMsg
);
#endif

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
