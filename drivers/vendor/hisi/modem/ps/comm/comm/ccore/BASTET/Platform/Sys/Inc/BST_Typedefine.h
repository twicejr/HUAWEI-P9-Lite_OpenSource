/******************************************************************************

                  版权所有 (C), 2014, 华为技术有限公司

 ******************************************************************************
  文 件 名   : BST_Typedefine.h
  版 本 号   : 初稿
  作    者   : d00173029
  生成日期   : 2014年06月04日
  最近修改   :
  功能描述   : 与对LWIP接口的一致化封装
  函数列表   :
  修改历史   :
  1.日    期   : 2014年06月04日
    作    者   : d00173029
    修改内容   : 建立文件

******************************************************************************/

#ifndef __BST_OS_TYPEDEF_H__
#define __BST_OS_TYPEDEF_H__

#include "vos.h"
#include "PsTypeDef.h"
#include "PsLogdef.h"

#ifdef __cplusplus
#if __cplusplus
extern "C" {
#endif
#endif

#if (BST_OS_VER == BST_HISI_VOS)
#pragma pack(4)
#elif(BST_OS_VER == BST_WIN32)
#pragma pack(push, 4)
#endif

/*****************************************************************************
  1 宏定义
*****************************************************************************/
typedef VOS_UINT64                      BST_UINT64;   /**< 64 bit unsigned  */
typedef VOS_UINT32                      BST_UINT32;   /**< 32 bit unsigned  */
typedef VOS_UINT16                      BST_UINT16;   /**< 16 bit unsigned  */
typedef VOS_UINT8                       BST_UINT8;    /**<  8 bit unsigned  */
typedef VOS_INT64                       BST_INT64 ;   /**< 64 bit signed  */
typedef VOS_INT32                       BST_INT32;    /**< 32 bit signed  */
typedef VOS_INT16                       BST_INT16;    /**< 16 bit signed  */
typedef VOS_INT8                        BST_INT8;     /**<  8 bit signed  */
typedef VOS_BOOL                        BST_BOOL;
typedef VOS_CHAR                        BST_CHAR;
typedef VOS_UINT_PTR                    BST_UINT_PTR;
typedef VOS_ULONG                       BST_ULONG;



#define BST_INLINE                      __inline
#define BST_VOID                        VOS_VOID
#define BST_NULL_PTR                    VOS_NULL_PTR

#define BST_TRUE                        ( 0x01U )
#define BST_FALSE                       ( 0x00U )

#define IsValidReportException(ErrVal)  ( (ErrVal) < BST_REPORT_MODE_MAX_NUM )

#define UINT8_TO_UINT16( u8L, u8H )     ( ( (u8L) & 0xff ) + ( ( (u8H)<<8 ) & 0xff00 ) )
#define UINT16_TO_UINT8H( u16_data )    ( BST_UINT8 )( ( (u16_data)>>8 ) & 0xff )
#define UINT16_TO_UINT8L( u16_data )    ( BST_UINT8 )( ( (u16_data) ) & 0xff )
/*****************************************************************************
  2 枚举定义
*****************************************************************************/
#define BST_INVALID_ACT_MSG             ( 0x00U )
#define BST_ACTION_ADD                  ( 0x01U )
#define BST_ACTION_REMOVE               ( 0x02U )
#define BST_ACTION_START                ( 0x03U )
#define BST_ACTION_STOP                 ( 0x04U )
#define BST_ACTION_INQUIRE              ( 0x05U )
#define BST_ACTION_CONFIG               ( 0x06U )
#define BST_ACTION_REPORT               ( 0x07U )

#define BST_NO_ERROR_MSG                ( 0x80U )
#define BST_ERR_UNKNOW_OBJ              ( 0x81U )
#define BST_ERR_UNKNOW_ACT              ( 0x82U )
#define BST_ERR_INVALID_PTR             ( 0x83U )
#define BST_ERR_ITEM_EXISTED            ( 0x84U )
#define BST_ERR_ITEM_NOT_EXISTED        ( 0x85U )
#define BST_ERR_UNREACHABLE             ( 0x86U )
#define BST_ERR_PAR_UNKNOW              ( 0x87U )
#define BST_ERR_PAR_OVERRUN             ( 0x88U )
#define BST_ERR_PAR_LEN                 ( 0x89U )
#define BST_ERR_LAYER_VER               ( 0x8AU )
#define BST_ERR_SYNC_TIMEOUT            ( 0x8BU )
#define BST_ERR_NO_MEMORY               ( 0x8CU )
#define BST_ERR_CLIENT_EXCEPTION        ( 0x8DU )
#define BST_ERR_SOCKET_CLSD             ( 0x8EU )
#define BST_ERR_NOT_SUPPORT             ( 0x8FU )


#define BST_ERR_REPORT_TO_AP            ( 0xE0U )
#define BST_ERR_TASK_REMOVED            ( 0xE1U )
#define BST_NEW_EMAIL                   ( 0xE2U )
#define BST_APP_SERVER_TIMEOUT          ( 0xE3U )
#define BST_EMAIL_OTHER_EXCEPIONT       ( 0xE4U )
#define BST_EMAIL_NOT_SUPPORT           ( 0xE5U ) //添加不支持格式的上报
#define BST_ERR_PARAM_ENCRYPTER         ( 0xE6U )
#define BST_ERR_PARAM_DECRYPTER         ( 0xE7U )
#define BST_NOT_HEARTBEAT_PACK          ( 0xE8U )
#define BST_ERR_ILLEGAL_PARAM           ( 0xE9U )
#define BST_TRAFFIC_FLOW_REPORT         ( 0xEAU )
#define BST_REPORT_MODE_MAX_NUM         ( 0xEBU )

#define BST_INVALID_TIMESTAMP           ( 0x00U )

typedef BST_UINT8                       BST_ACT_ERR_ENUM_UINT8;
typedef BST_UINT8                       BST_ERR_ENUM_UINT8;
typedef BST_UINT8                       BST_ACT_ENUM_UINT8;
typedef BST_UINT16                      BST_PROCID_T;
typedef BST_UINT16                      BST_TASKID_T;
typedef BST_UINT32                      BST_TICK_T;
typedef BST_INT32                       BST_TIMER_ID_T;
typedef BST_UINT16                      BST_OFST_ADDR_T;
typedef BST_UINT16                      BST_OBJT_ADDR_T;
typedef BST_UINT16                      BST_PAKCET_SN_T;
typedef BST_UINT16                      BST_PAKCET_PIECE_T;
typedef BST_UINT8                       BST_PRIMITIVE_T;
typedef BST_UINT16                      BST_CMD_LEN_T;
typedef BST_UINT8                       BST_CMD_CNT_T;
typedef BST_UINT32                      BST_IPLINK_ID1_T;
typedef BST_UINT32                      BST_IPLINK_ID2_T;

/*****************************************************************************
  3 OTHERS定义
*****************************************************************************/


#if (BST_OS_VER == BST_HISI_VOS)
#pragma pack()
#elif (BST_OS_VER == BST_WIN32)
#pragma pack(pop)
#endif

#ifdef __cplusplus
#if __cplusplus
}
#endif
#endif


#endif
