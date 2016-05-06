

#ifndef __TAFMMIENCODE_H__
#define __TAFMMIENCODE_H__

/*****************************************************************************
  1 其他头文件包含
*****************************************************************************/
#include "vos.h"
#include "v_typdef.h"
#include "Taf_MmiStrParse.h"

#ifdef __cplusplus
#if __cplusplus
extern "C" {
#endif
#endif


#pragma pack(4)

/*****************************************************************************
  2 宏定义
*****************************************************************************/

#define TAF_MMI_INSERT_SEPERATION_CHAR(pcOutMmiStr, ulPos)  \
{ \
    *(pcOutMmiStr + ulPos) = '*';   \
    ulPos                 += VOS_StrLen("*");   \
}

#define TAF_MMI_REGISTER_PASSWORD       "**03"

#define TAF_MMI_BuildEventType(ulSndPid,usMsgName) \
    (((VOS_UINT32)(/*lint -e778*/((ulSndPid) & 0xF0000)/*lint +e778*/ \
    | (((ulSndPid) & 0xFFF) << 4)) << 12) | (usMsgName))      /* 根据 Pid以及usMsgName 构建EventType  */

#define TAF_MMI_BITS_PER_OCTET                              (8)
#define TAF_MMI_BITS_PER_SEPTET                             (7)
#define TAF_MMI_USSD_7BIT_PAD                               (0x1a)

/*****************************************************************************
  3 枚举定义
*****************************************************************************/


/*****************************************************************************
  4 全局变量声明
*****************************************************************************/


/*****************************************************************************
  5 消息头定义
*****************************************************************************/


/*****************************************************************************
  6 消息定义
*****************************************************************************/


/*****************************************************************************
  7 STRUCT定义
*****************************************************************************/
typedef VOS_UINT32 (*TAF_MMI_ENCODE_PROC_FUNC)(
    VOS_UINT32                          ulEventType,
    VOS_VOID                           *pMsg,
    VOS_CHAR                           *pOutMmiStr
);

/*****************************************************************************
 结构名    : TAF_MMI_OPERATION_TABLE_STRU
 结构说明  : 消息与对应操作类型的结构
             ulEventType                     - 待编码的事件类型；
             enSsOpType                      - 事件类型对应的操作码

  1.日    期   : 2013年05月06日
    作    者   : 傅映君/62575
    修改内容   : SS FDN&Call Control
*****************************************************************************/
typedef struct
{
    VOS_UINT32                          ulEventType;
    MN_MMI_OPERATION_TYPE_ENUM_U8       enSsOpType;
    VOS_UINT8                           aucReserved1[3];
}TAF_MMI_OPERATION_TABLE_STRU;

/*****************************************************************************
 结构名    : TAF_SSA_ENCODE_MMISTR_PROC_STRU
 结构说明  : 消息与对应处理函数的结构
             ulEventType                     - 待编码的事件类型；
             TAF_MmiEncodeRegisterMmiString  - 编码处理函数

  1.日    期   : 2013年05月06日
    作    者   : 傅映君/62575
    修改内容   : SS FDN&Call Control
*****************************************************************************/
/*lint -e958 -e959 修改人:l60609;原因:64bit*/
typedef struct
{
    VOS_UINT32                          ulEventType;
    TAF_MMI_ENCODE_PROC_FUNC            pMsgProcFunc;
}TAF_MMI_ENCODE_PROC_FUNC_STRU;
/*lint +e958 +e959 修改人:l60609;原因:64bit*/

/*****************************************************************************
  8 UNION定义
*****************************************************************************/


/*****************************************************************************
  9 OTHERS定义
*****************************************************************************/


/*****************************************************************************
  10 函数声明
*****************************************************************************/

extern VOS_UINT32 TAF_MmiEncodeActiveMmiString(
    VOS_UINT32                          ulEventType,
    VOS_VOID                           *pMsg,
    VOS_CHAR                           *pOutMmiStr
);

extern VOS_UINT32 TAF_MmiEncodeBS(
    TAF_SS_BASIC_SERVICE_STRU          *pstBsService,
    VOS_CHAR                           *pOutMmiStr,
    VOS_UINT32                         *pulBSLength
);

extern VOS_VOID TAF_MmiEncodeDN(
    TAF_SS_REGISTERSS_REQ_STRU         *pstRegisterInfo,
    VOS_CHAR                           *pOutMmiStr,
    VOS_UINT32                         *pulDNLength
);

extern VOS_UINT32 TAF_MmiEncodeEraseCcEntryMmiString(
    VOS_UINT32                          ulEventType,
    VOS_VOID                           *pPara,
    VOS_CHAR                           *pOutMmiStr
);

extern VOS_UINT32 TAF_MmiEncodeMmiString(
    VOS_VOID                           *pPara,
    VOS_CHAR                           *pOutMmiStr
);

extern VOS_VOID TAF_MmiEncodePW(
    VOS_UINT8                          *pucPassword,
    VOS_UINT32                          ulPasswordLength,
    VOS_CHAR                           *pcOutMmiStr,
    VOS_UINT32                         *pulPWLength
);
extern VOS_UINT32 TAF_MmiEncodeRegisterMmiString(
    VOS_UINT32                          ulEventType,
    VOS_VOID                           *pPara,
    VOS_CHAR                           *pOutMmiStr
);

extern VOS_UINT32 TAF_MmiEncodeRegisterPwdMmiString(
    VOS_UINT32                          ulEventType,
   VOS_VOID                           *pMsg,
   VOS_CHAR                           *pOutMmiStr
);

extern VOS_UINT32 TAF_MmiEncodeSC(
    TAF_SS_CODE                         SsCode,
    VOS_CHAR                           *pOutMmiStr,
    VOS_UINT32                         *pulScLength
);

extern TAF_MMI_OPERATION_TABLE_STRU *TAF_MmiGetEventOperationTypeTblAddr(VOS_VOID);

extern VOS_UINT32 TAF_MmiGetEventOperationTypeTblSize(VOS_VOID);

extern VOS_UINT32 TAF_MmiEncodeUssdMessage (
    TAF_SS_USSD_STRING_STRU            *pstPara
);

VOS_UINT32 TAF_MmiGetOperationType(
    VOS_UINT32                          ulEventType,
    MN_MMI_OPERATION_TYPE_ENUM_U8      *penSsOpType
);
#if (VOS_OS_VER == VOS_WIN32)
#pragma pack()
#else
#pragma pack(0)
#endif




#ifdef __cplusplus
    #if __cplusplus
        }
    #endif
#endif

#endif /* end of TafMmiEncode.h */
