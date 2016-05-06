/******************************************************************************


        @(#)Copyright(C)2008,Hisilicon Co. LTD.

 ******************************************************************************
    File name   : PsTypeDef.h
    Description : PS使用的公共类型定义
    History     :
      1.  Xiaojun  2009-02-10  Initial

******************************************************************************/

#ifndef __PSTYPEDEF_H__
#define __PSTYPEDEF_H__


/*****************************************************************************
  1 Include Headfile
*****************************************************************************/

#include "vos.h"
/*****************************************************************************
  1.1 Cplusplus Announce
*****************************************************************************/
#ifdef __cplusplus
#if __cplusplus
extern "C" {
#endif
#endif

#if (VOS_OS_VER != VOS_WIN32)
#pragma pack(4)
#else
#pragma pack(push, 4)
#endif

/*****************************************************************************
  2 macro
*****************************************************************************/
#define PS_NULL_UINT8                   (0xFF)
#define PS_NULL_UINT16                  (0xFFFF)
#define PS_NULL_UINT32                  (0xFFFFFFFFUL)
#define PS_NULL_INT8                    (0x7F)
#define PS_NULL_INT16                   (0x7FFF)
#define PS_NULL_INT32                   (0x7FFFFFFF)
#define PS_NEG_ONE                      (-1)

/* 协议栈统一BIT位赋值宏定义 */
#define PS_IE_NOT_PRESENT               PS_FALSE   /*GU模使用，保留*/
#define PS_IE_ABSENT                    PS_FALSE
#define PS_IE_PRESENT                   PS_TRUE
#define PS_IE_MODIFIED                  2

#define PS_DISABLE                      1
#define PS_ENABLE                       2

#define THREAD_PRI_ERRC VOS_PRIORITY_BASE

/* UE能力宏定义 */
#define PS_CAP_UNSUPPORT                0
#define PS_CAP_SUPPORT                  1



/*****************************************************************************
  3 Massage Declare
*****************************************************************************/



/*****************************************************************************
  4 Enum
*****************************************************************************/

/*****************************************************************************
 枚举名    : PS_BOOL_ENUM
 协议表格  :
 ASN.1描述 :
 枚举说明  : PS统一布尔类型枚举定义
*****************************************************************************/
enum PS_BOOL_ENUM
{
    PS_FALSE                            = 0,
    PS_TRUE                             = 1,
    PS_BOOL_BUTT
};
typedef VOS_UINT8   PS_BOOL_ENUM_UINT8;

/*****************************************************************************
 枚举名    : PS_RSLT_CODE_ENUM
 协议表格  :
 ASN.1描述 :
 枚举说明  : 协议栈统一返回值枚举定义
*****************************************************************************/
enum PS_RSLT_CODE_ENUM
{
    PS_SUCC                             = 0,
    PS_FAIL                             = 1,

    PS_PTR_NULL                         = 2,    /*空指针*/
    PS_PARA_ERR                         = 3,    /*参数错误*/
    PS_STATE_ERR                        = 4,    /*状态错误*/
    PS_MODE_ERR                         = 5,    /*模式错误*/
    PS_SCOPE_ERR                        = 6,    /*范围错误*/
    PS_MEM_ALLOC_FAIL                   = 7,    /*内存分配失败*/
    PS_MSG_ALLOC_FAIL                   = 8,    /*消息分配失败*/
    PS_MSG_SEND_FAIL                    = 9,    /*消息发送失败*/
    PS_TIMER_ERR                        = 10,   /*定时器错误*/
    PS_TIMER_OUT                        = 11,   /*定时器超时*/
    PS_QUE_FULL                         = 12,   /*队列满*/
    PS_QUE_EMPTY                        = 13,   /*队列空*/

    PS_RSLT_CODE_BUTT
};
typedef VOS_UINT32   PS_RSLT_CODE_ENUM_UINT32;

/*开关枚举*/
enum PS_SWITCH_ENUM
{
    PS_SWITCH_OFF = 0,
    PS_SWITCH_ON  = 1
};


/*****************************************************************************
  5 STRUCT
*****************************************************************************/

/*****************************************************************************
 结构名    : PS_MSG_HEADER_STRU
 协议表格  :
 ASN.1描述 :
 结构说明  : 消息头定义
*****************************************************************************/
typedef VOS_UINT32 PS_NULL_STRU;
/* GU使用，保留。消息头定义，为了兼容4121定义 */
typedef struct
{
    VOS_MSG_HEADER
    VOS_UINT32                          ulMsgName;
}MSG_HEADER_STRU;

/*L模使用*/
typedef struct
{
    VOS_MSG_HEADER
    VOS_UINT32                          ulMsgName;
}PS_MSG_HEADER_STRU;

/*L模使用*/
typedef struct
{
    VOS_MSG_HEADER
    VOS_UINT32                          ulMsgName;
    VOS_UINT16                          usOpId;
	VOS_UINT8                           aucRsv[2];
}LHPA_MSG_HEADER_STRU;

typedef struct
{
    VOS_MSG_HEADER
    VOS_UINT16                          usMsgName;
    VOS_UINT8                           aucRsv[2];
}CAS_MSG_HEADER_STRU;
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

#endif /* end of PsTypeDef.h */

