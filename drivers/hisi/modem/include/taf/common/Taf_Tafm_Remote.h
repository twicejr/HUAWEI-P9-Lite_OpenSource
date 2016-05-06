
#ifndef __TAF_TAFM_REMOTE_H__
#define __TAF_TAFM_REMOTE_H__

#ifdef __cplusplus
extern "C" {
#endif
#pragma pack(4)
/*========================================================*/

#include "TafClientApi.h"

/*宏定义开始*/

/*定义Client的广播值*/
#define TAF_CLIENTID_BROADCAST          (0xFFFF)
#define MN_CLIENTID_INVALID             (0xFFFE)


/*CS或者PS最大支持的RAB数目*/
#define  TAF_MAX_RABID                15


#define TAF_MSG_HEADER_LEN  6

#ifndef TAF_SUCCESS
#define TAF_SUCCESS    TAF_ERR_NO_ERROR     /*函数执行成功*/
#endif
#ifndef TAF_FAILURE
#define TAF_FAILURE    TAF_ERR_ERROR        /*函数执行失败*/
#endif

#define PS_INIT_NOT_START  0
#define PS_INIT_START      1
#define PS_INIT_FINISH     2

/*宏定义结束*/

/*远端API与TAFM进行通信时使用的消息类型*/
/*********************************************************
1.日    期   : 2012年12月10日
  作    者   : w00176964
  修改内容   : 增加ACINFO新增命令的查询消息
2.日    期   : 2013年05月06日
  作    者   : f62575
  修改内容   : SS FDN&Call Control项目，删除TAF_MSG_GETPWD_MSG，新增TAF_MSG_MMA_COPN_INFO_QUERY_REQ
**********************************************************/

typedef enum
{

    TAF_MSG_MMA_USIM_RESTRICTED_ACCESS, /*+CRSM*/


    TAF_MSG_PARA_READ,            /* 通信参数查询*/

    /*电话管理*/
    TAF_MSG_MMA_PLMN_LIST,        /* 可用PLMN搜索，扩展命令*/


    TAF_MSG_MMA_OP_PIN_REQ,       /* PIN操作请求*/
    TAF_MSG_MMA_ATTACH,           /* 启动附着过程*/
    TAF_MSG_MMA_DETACH,           /* 启动去附着过程*/


    TAF_MSG_MMA_ME_PERSONAL_REQ,   /* 锁机操作请求 */

    /* Added by C00173809 for AT Project，2011-10-08,  Begin*/
    TAF_MSG_MMA_GET_CURRENT_ATTACH_STATUS,      /*请求获取CS和PS的注册状态*/

    /* Deleted SSA消息 */

    TAF_MSG_MMA_USIM_INFO,
    TAF_MSG_MMA_CPNN_INFO,

    /* Added by C00173809 for AT Project，2011-11-03,  Begin*/
    TAF_MSG_MMA_SET_PIN,
    /* Added by C00173809 for AT Project，2011-11-03,  End*/


    TAF_MSG_MMA_COPS_FORMAT_TYPE_SET_REQ,
    TAF_MSG_MMA_USIM_STUB_SET_REQ,
    TAF_MSG_MMA_REFRESH_STUB_SET_REQ,
    TAF_MSG_MMA_AUTO_RESEL_STUB_SET_REQ,

    TAF_MSG_BUTT
}TAF_MSG_TYPE;
typedef VOS_UINT16   TAF_MSG_TYPE_ENUM_U16;


/*TAF参数管理类子消息类型定义*/
typedef enum
{
    TAF_SUB_MSG_PARA_SET,     /*通信参数设置*/
    TAF_SUB_MSG_PARA_READ,    /*通信参数查询*/
    TAF_SUB_MSG_BUTT
}TAF_PRIM_MSG_TYPE;


/*全局变量定义开始*/
/*远端API所需全局变量定义*/
/*APP/AT回调函数记录表*/


/*全局变量定义结束*/

/*API辅助宏定义*/
#define TAF_ENCODE_MSG_HEADER(ptr, MsgType, ClientId, Id, IeMask)  \
                         *ptr++ = MsgType;                         \
                         *ptr++ = (VOS_UINT8)((ClientId >> 8) & 0xFF); \
                         *ptr++ = (VOS_UINT8)(ClientId & 0xFF);        \
                         *ptr++ = Id;                              \
                         *ptr++ = (VOS_UINT8)((IeMask >> 8) & 0xFF);   \
                         *ptr++ = (VOS_UINT8)(IeMask & 0xFF)


/*TAF是否已经在远端注册过MUX回调函数*/
#define TAF_REG_MUX_CALLBACK_NO    0   /*未注册过MUX回调函数*/
#define TAF_REG_MUX_CALLBACK_YES   1   /*已注册过MUX回调函数*/

VOS_VOID   Taf_EventReportProc(VOS_UINT16 usMuxId, VOS_UINT8 *pData, VOS_UINT16 usLen, VOS_UINT8 ucRegTabIndex);


#if ((VOS_OS_VER == VOS_WIN32) || (VOS_OS_VER == VOS_NUCLEUS))
#pragma pack()
#else
#pragma pack(0)
#endif

/*========================================================*/
#ifdef __cplusplus
}
#endif
/******************************************************************************/

/*============================================================================*/
#endif          /* __TAF_REMOTE_H__ */
