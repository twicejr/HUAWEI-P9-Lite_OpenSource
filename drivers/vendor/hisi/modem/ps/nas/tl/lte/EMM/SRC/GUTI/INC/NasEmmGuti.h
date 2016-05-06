/******************************************************************************

        @(#)Copyright(C)2008,Hisilicon Co. LTD.

 ******************************************************************************
    File name   : NasEmmGuti.h
    Description : 这是EMM GUTI模块的头文件
    History     :
  1. Date       : 2008-08-28
     Author     : z57968
     Modification:Create
  2. Data       :
     Author     :
     Modification:
******************************************************************************/

#ifndef _NASEMMGUTI_H
#define _NASEMMGUTI_H


/*****************************************************************************
  1 其他头文件包含
****************************************************************************/
#include    "NasEmmGIMComm.h"
#include    "NasEmmPubUCnMsgDecode.h"

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
****************************************************************************/
/*应该包含长度字段*/
#define EMM_COUNT_CN_GUTI_CMP_LEN \
        (\
            NAS_MSG_STRU_MSG_SIZE_LEN   +   \
            NAS_GUTI_COMP_NAS_MSG_LEN       \
        )

#define VOS_UINT32_FFS VOS_UINT32


/*封装GUTI模块的LOG打印宏*/
#define LOG_SUBMOD_ID_NAS_LMM_GUTI               1
#define NAS_EMM_GUTI_ERROR_LOG(String)          NAS_LMM_LOG_ERR(LOG_SUBMOD_ID_NAS_LMM_EMM_GUTI, String)
#define NAS_EMM_GUTI_WARNING_LOG(String)        NAS_LMM_LOG_WARN(LOG_SUBMOD_ID_NAS_LMM_EMM_GUTI, String)
#define NAS_EMM_GUTI_NORMAL_LOG(String)         NAS_LMM_LOG_NORM(LOG_SUBMOD_ID_NAS_LMM_EMM_GUTI, String)
#define NAS_EMM_GUTI_INFO_LOG(String)           NAS_LMM_LOG_INFO(LOG_SUBMOD_ID_NAS_LMM_EMM_GUTI, String)
#define NAS_EMM_GUTI_NORAML_LOG1(String, Para1) NAS_LMM_LOG1_NORM(LOG_SUBMOD_ID_NAS_LMM_EMM_GUTI, String, Para1)

#define NAS_EMM_GUTI_NORAML_LOG2(String, Para1, Para2) NAS_LMM_LOG2_NORM(LOG_SUBMOD_ID_NAS_LMM_EMM_GUTI, String, Para1, Para2)

/*****************************************************************************
  3 Massage Declare
*****************************************************************************/

/*****************************************************************************
  4 Enum
*****************************************************************************/


/*****************************************************************************
  5 STRUCT
*****************************************************************************/
/*网侧发的空口消息GUTI_REALLOCATION_COMMAND的结构*/


/*****************************************************************************
  6 UNION
*****************************************************************************/

/*****************************************************************************
  7 Extern Global Variable
*****************************************************************************/

/*调用NVIM接口函数*/
extern VOS_VOID       NAS_EMM_GutiWrite(VOS_UINT32 g_ulGuti);
extern VOS_VOID       NAS_EMM_TaiListWrite(VOS_VOID);
extern VOS_VOID    NAS_EMM_CompCnGutiCmp(LRRC_LNAS_MSG_STRU  *pNasMsg);
/*****************************************************************************
  8 Fuction Extern
*****************************************************************************/
extern VOS_UINT32    NAS_EMM_GutiMrrcDataReq(VOS_VOID);

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
