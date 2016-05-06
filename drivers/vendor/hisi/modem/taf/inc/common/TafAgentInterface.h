

#ifndef _TAFAGENTAPSINTERFACE_H_
#define _TAFAGENTAPSINTERFACE_H_

/*****************************************************************************
  1 头文件包含
*****************************************************************************/
#include "vos.h"
#include "TafTypeDef.h"
#include "AtMnInterface.h"
#include "TafApsApi.h"
#include "MnCallApi.h"
/* Added by s00217060 for 主动上报AT命令控制下移至C核, 2013-4-2, begin */
#include "TafAppMma.h"
/* Added by s00217060 for 主动上报AT命令控制下移至C核, 2013-4-2, end */

#pragma pack(4)


#ifdef __cplusplus
#if __cplusplus
extern "C" {
#endif
#endif

#if (VOS_OS_VER == VOS_WIN32)
#pragma pack()
#else
#pragma pack(0)
#endif


/*****************************************************************************
  2 宏定义
*****************************************************************************/

/*****************************************************************************
  3 全局变量定义
*****************************************************************************/


/*****************************************************************************
  4 枚举定义
*****************************************************************************/
/*****************************************************************************
枚举名    : TAFAGENT_MSG_ID_ENUM
结构说明  : CDS和ADS的之间的消息

  1.日    期   : 2011年12月22日
    作    者   : 陈志敏/c00173809
    修改内容   : 定义TAFAGENT和APS之间的消息
  2.日    期   : 2011年12月26日
    作    者   : w00199382
    修改内容   : 定义TAFAGENT和MN之间的消息
*****************************************************************************/
enum TAFAGENT_MSG_ID_ENUM
{

    /* TAFAGENT->APS 查询CID请求消息 */
    ID_TAFAGENT_APS_FIND_CID_FOR_DIAL_REQ   = 0x1000,                           /* _H2ASN_MsgChoice TAFAGENT_APS_FIND_CID_FOR_DIAL_REQ_STRU */

    /* TAFAGENT->APS 设置CID的参数请求消息 */
    ID_TAFAGENT_APS_SET_CID_PARA_REQ        = 0x1001,                           /* _H2ASN_MsgChoice TAFAGENT_APS_SET_CID_PARA_REQ_STRU */

    /* TAFAGENT->APS 获取CID的参数请求消息 */
    ID_TAFAGENT_APS_GET_CID_PARA_REQ        = 0x1002,                           /* _H2ASN_MsgChoice TAFAGENT_APS_GET_CID_PARA_REQ_STRU */

    /* TAFAGENT->APS 设置CID的QOS参数请求消息 */
    ID_TAFAGENT_APS_SET_CID_QOS_PARA_REQ    = 0x1003,                           /* _H2ASN_MsgChoice TAFAGENT_APS_SET_CID_QOS_PARA_REQ_STRU */

    /* TAFAGENT->APS 获取CID的QOS参数请求消息 */
    ID_TAFAGENT_APS_GET_CID_QOS_PARA_REQ    = 0x1004,                           /* _H2ASN_MsgChoice TAFAGENT_APS_GET_CID_QOS_PARA_REQ_STRU */

    /* Added by s00217060 for 主动上报AT命令控制下移至C核, 2013-3-25, begin */
    ID_TAFAGENT_MTA_GET_SYSMODE_REQ         = 0x1005,                           /* _H2ASN_MsgChoice TAFAGENT_MTA_GET_SYSMODE_REQ_STRU */
    /* Added by s00217060 for 主动上报AT命令控制下移至C核, 2013-3-25, end */

    ID_TAFAGENT_MTA_GET_ANT_STATE_REQ       = 0x1006,                           /* _H2ASN_MsgChoice TAFAGENT_MTA_GET_ANT_STATE_REQ_STRU */


    /* APS->TAFAGENT 查询CID回复消息 */
    ID_TAFAGENT_APS_FIND_CID_FOR_DIAL_CNF   = 0x2000,                           /* _H2ASN_MsgChoice TAFAGENT_APS_FIND_CID_FOR_DIAL_CNF_STRU */

    /* APS->TAFAGENT 设置CID的参数回复消息 */
    ID_TAFAGENT_APS_SET_CID_PARA_CNF        = 0x2001,                           /* _H2ASN_MsgChoice TAFAGENT_APS_SET_CID_PARA_CNF_STRU */

    /* APS->TAFAGENT 获取CID的参数回复消息 */
    ID_TAFAGENT_APS_GET_CID_PARA_CNF        = 0x2002,                           /* _H2ASN_MsgChoice TAFAGENT_APS_GET_CID_PARA_CNF_STRU */

    /* APS->TAFAGENT 设置CID的QOS参数回复消息 */
    ID_TAFAGENT_APS_SET_CID_QOS_PARA_CNF    = 0x2003,                           /* _H2ASN_MsgChoice TAFAGENT_APS_SET_CID_QOS_PARA_CNF_STRU */

    /* APS->TAFAGENT 获取CID的QOS参数回复消息 */
    ID_TAFAGENT_APS_GET_CID_QOS_PARA_CNF    = 0x2004,                           /* _H2ASN_MsgChoice TAFAGENT_APS_GET_CID_QOS_PARA_CNF_STRU */

    /* Added by s00217060 for 主动上报AT命令控制下移至C核, 2013-3-25, begin */
    /* TAFAGENT->MTA  获取系统模式信息回复消息*/
    ID_TAFAGENT_MTA_GET_SYSMODE_CNF         = 0x2005,                           /* _H2ASN_MsgChoice TAFAGENT_MTA_GET_SYSMODE_CNF_STRU */
    /* Added by s00217060 for 主动上报AT命令控制下移至C核, 2013-3-25, end */

    /* TAFAGENT->MN  获取通话信息回复消息*/
    ID_TAFAGENT_MN_GET_CALL_INFO_CNF        = 0x2006,                           /* _H2ASN_MsgChoice TAFAGERNT_MN_GET_CALL_INFO_CNF_STRU */



    /* Added by s00217060 for 主动上报AT命令控制下移至C核, 2013-3-25, begin */
    /* MTA->TAFAGENT  获取天线状态回复消息*/
    ID_TAFAGENT_MTA_GET_ANT_STATE_CNF       = 0x2007,                           /* _H2ASN_MsgChoice TAFAGENT_MTA_GET_ANT_STATE_CNF_STRU */
    /* Added by s00217060 for 主动上报AT命令控制下移至C核, 2013-3-25, end */

    ID_TAFAGENT_MSG_ID_ENUM_BUTT
};
typedef VOS_UINT32  TAFAGENT_MSG_ID_ENUM_UINT32;


/*****************************************************************************
  5 结构定义
*****************************************************************************/

/*****************************************************************************
 结构名    : TAFAGENT_APS_SET_CID_PARA_REQ_STRU
 结构说明  : ID_MSG_TAF_PS_SET_CID_PARA_REQ消息结构, 设置CID 参数
 1.日    期   : 2011年12月19日
   作    者   : C00173809
   修改内容   : 创建文件
*****************************************************************************/
typedef struct
{
    VOS_MSG_HEADER                                                              /* _H2ASN_Skip */
    TAFAGENT_MSG_ID_ENUM_UINT32         enMsgId;                                /* _H2ASN_Skip */

    VOS_UINT32                          ulClientID;                             /* CLIENT ID */
    TAF_PDP_PRIM_CONTEXT_EXT_STRU       stPdpPrimContextExt;                    /* CID参数 */
} TAFAGENT_APS_SET_CID_PARA_REQ_STRU;

/*****************************************************************************
 结构名    : TAFAGENT_APS_QUERY_ERROR_CODE_REQ_STRU
 结构说明  : ID_TAFAGENT_APS_QUERY_ERROR_CODE_REQ消息结构,
 1.日    期   : 2011年12月19日
   作    者   : C00173809
   修改内容   : 创建文件
*****************************************************************************/
typedef struct
{
    VOS_MSG_HEADER                                                              /* _H2ASN_Skip */
    TAFAGENT_MSG_ID_ENUM_UINT32         enMsgId;                                /* _H2ASN_Skip */

} TAFAGENT_APS_QUERY_ERROR_CODE_REQ_STRU;

/*****************************************************************************
 结构名    : TAFAGENT_APS_CLEAR_ERROR_CODE_REQ_STRU
 结构说明  : ID_TAFAGENT_APS_CLEAR_ERROR_CODE_REQ消息结构,
 1.日    期   : 2011年12月19日
   作    者   : C00173809
   修改内容   : 创建文件
*****************************************************************************/
typedef struct
{
    VOS_MSG_HEADER                                                              /* _H2ASN_Skip */
    TAFAGENT_MSG_ID_ENUM_UINT32         enMsgId;                                /* _H2ASN_Skip */

} TAFAGENT_APS_CLEAR_ERROR_CODE_REQ_STRU;

/*****************************************************************************
 结构名    : TAFAGENT_APS_GET_CID_PARA_REQ_STRU
 结构说明  : ID_TAFAGENT_APS_GET_CID_PARA_REQ消息结构,
 1.日    期   : 2011年12月19日
   作    者   : C00173809
   修改内容   : 创建文件
*****************************************************************************/
typedef struct
{
    VOS_MSG_HEADER                                                              /* _H2ASN_Skip */
    TAFAGENT_MSG_ID_ENUM_UINT32         enMsgId;                                /* _H2ASN_Skip */

    VOS_UINT8                           ucCid;                                  /* 要获取参数的CID */

    VOS_UINT8                           aucReserved[3];
} TAFAGENT_APS_GET_CID_PARA_REQ_STRU;

/*****************************************************************************
 结构名    : TAFAGENT_APS_FIND_CID_FOR_DIAL_REQ_STRU
 结构说明  : ID_TAFAGENT_APS_FIND_CID_FOR_DIAL_REQ消息结构,
 1.日    期   : 2011年12月19日
   作    者   : C00173809
   修改内容   : 创建文件
*****************************************************************************/
typedef struct
{
    VOS_MSG_HEADER                                                              /* _H2ASN_Skip */
    TAFAGENT_MSG_ID_ENUM_UINT32         enMsgId;                                /* _H2ASN_Skip */

} TAFAGENT_APS_FIND_CID_FOR_DIAL_REQ_STRU;

/* Added by s00217060 for 主动上报AT命令控制下移至C核, 2013-3-25, begin */
/*****************************************************************************
 结构名    : TAFAGENT_MTA_GET_SYSMODE_REQ_STRU
 结构说明  : ID_TAFAGENT_MTA_GET_SYSMODE_REQ消息结构,
 1.日    期   : 2013年3月25日
   作    者   : s00217060
   修改内容   : 创建文件
*****************************************************************************/
typedef struct
{
    VOS_MSG_HEADER                                                              /* _H2ASN_Skip */
    TAFAGENT_MSG_ID_ENUM_UINT32         enMsgId;                                /* _H2ASN_Skip */
} TAFAGENT_MTA_GET_SYSMODE_REQ_STRU;
/* Added by s00217060 for 主动上报AT命令控制下移至C核, 2013-3-25, end */

/* Deleted by Y00213812 for VoLTE_PhaseI 项目, 2013-07-08, begin */
/* Deleted by Y00213812 for VoLTE_PhaseI 项目, 2013-07-08, end */

/*****************************************************************************
 结构名    : TAFAGENT_APS_CLEAR_ERROR_CODE_CNF_STRU
 结构说明  : ID_EVT_TAF_PS_CLEAR_ERROR_CODE_CNF消息结构,
 1.日    期   : 2011年12月18日
   作    者   : c00173809
   修改内容   : 创建结构
*****************************************************************************/
typedef struct
{
    VOS_MSG_HEADER                                                              /* _H2ASN_Skip */
    TAFAGENT_MSG_ID_ENUM_UINT32         enMsgId;                                /* _H2ASN_Skip */

    VOS_UINT32                          ulRet;                                  /* 返回结果 */
} TAFAGENT_APS_CLEAR_ERROR_CODE_CNF_STRU;

/*****************************************************************************
 结构名    : TAFAGENT_APS_GET_CID_PARA_CNF_STRU
 结构说明  : ID_EVT_TAF_PS_GET_CID_PARA_CNF消息结构, 获取指定CID的参数
 1.日    期   : 2011年12月18日
   作    者   : c00173809
   修改内容   : 创建结构
*****************************************************************************/
typedef struct
{
    VOS_MSG_HEADER                                                              /* _H2ASN_Skip */
    TAFAGENT_MSG_ID_ENUM_UINT32         enMsgId;                                /* _H2ASN_Skip */

    VOS_UINT32                          ulRet;                                  /* 返回结果 */
    TAF_PDP_PRIM_CONTEXT_STRU           stCidInfo;                     /* 查询获取指定CID的参数 */
} TAFAGENT_APS_GET_CID_PARA_CNF_STRU;

/*****************************************************************************
 结构名    : TAFAGENT_APS_SET_CID_PARA_CNF_STRU
 结构说明  : ID_EVT_TAF_PS_SET_CID_PARA_CNF消息结构,
 1.日    期   : 2011年12月18日
   作    者   : c00173809
   修改内容   : 创建结构
*****************************************************************************/
typedef struct
{
    VOS_MSG_HEADER                                                              /* _H2ASN_Skip */
    TAFAGENT_MSG_ID_ENUM_UINT32         enMsgId;                                /* _H2ASN_Skip */

    VOS_UINT32                          ulRet;                                  /* 返回结果 */
} TAFAGENT_APS_SET_CID_PARA_CNF_STRU;

/*****************************************************************************
 结构名    : TAFAGENT_APS_FIND_CID_FOR_DIAL_CNF_STRU
 结构说明  : ID_EVT_TAF_PS_FIND_CID_FOR_DIAL_CNF消息结构, 获取CID回复结构
 1.日    期   : 2011年12月18日
   作    者   : c00173809
   修改内容   : 创建结构
*****************************************************************************/
typedef struct
{
    VOS_MSG_HEADER                                                              /* _H2ASN_Skip */
    TAFAGENT_MSG_ID_ENUM_UINT32         enMsgId;                                /* _H2ASN_Skip */

    VOS_UINT32                          ulRet;                                  /* 返回结果 */
    VOS_UINT8                           ucCid;                                  /* 要查询的CID */
    VOS_UINT8                           aucReserved[3];                         /* 保留位 */
} TAFAGENT_APS_FIND_CID_FOR_DIAL_CNF_STRU;

/*****************************************************************************
 结构名    : TAFAGERNT_TAF_GET_CALL_INFO_STRU
 结构说明  : 获取通话信息的结构
 1.日    期   : 2011年12月18日
   作    者   : w00199382
   修改内容   : 创建结构
*****************************************************************************/

typedef struct
{
    MN_CALL_ID_T                        callId;                                 /* 所有正在通话的个数 */
    MN_CALL_TYPE_ENUM_U8                enCallType;                             /* 通话类型*/
    MN_CALL_STATE_ENUM_U8               enCallState;                            /* 通话状态*/
    VOS_UINT8                           aucReserved[1];                         /* 保留位 */
}TAFAGERNT_MN_CALL_INFO_STRU;

/*****************************************************************************
 结构名    : TAFAGERNT_MN_GET_CALL_INFO_CNF_STRU
 结构说明  : ID_TAFAGENT_MN_GET_CALL_INFO_CNF消息结构, 获取回复结构
 1.日    期   : 2011年12月18日
   作    者   : w00199382
   修改内容   : 创建结构
*****************************************************************************/

typedef struct
{
    VOS_MSG_HEADER                                                              /* _H2ASN_Skip */
    TAFAGENT_MSG_ID_ENUM_UINT32         enMsgId;                                /* _H2ASN_Skip */

    VOS_UINT8                           ucNumOfCalls;                           /* 所有正在通话的个数 */
    VOS_UINT8                           aucReserved[3];                         /* 保留位 */
    TAFAGERNT_MN_CALL_INFO_STRU         stCallInfo[MN_CALL_MAX_NUM];            /*返回呼叫信息*/
}TAFAGERNT_MN_GET_CALL_INFO_CNF_STRU;

/* Added by s00217060 for 主动上报AT命令控制下移至C核, 2013-3-25, begin */
/*****************************************************************************
 结构名    : TAF_SYS_MODE_STRU
 结构说明  : 记录当前系统模式, 包含:
             (1) RAT Type 接入技术
             (2) Sub Mode 系统子模式
*****************************************************************************/
typedef struct
{
    TAF_SYS_MODE_ENUM_UINT8             enRatType;           /* 接入技术   */
    TAF_SYS_SUBMODE_ENUM_UINT8          enSysSubMode;        /* 系统子模式 */
    VOS_UINT8                           aucReserve[2];
} TAF_AGENT_SYS_MODE_STRU;

/*****************************************************************************
 结构名    : TAFAGENT_MTA_GET_SYSMODE_CNF_STRU
 结构说明  : ID_TAFAGENT_MTA_GET_SYSMODE_CNF消息结构, 获取回复结构
 1.日    期   : 2013年03月26日
   作    者   : s00217060
   修改内容   : 创建结构
*****************************************************************************/

typedef struct
{
    VOS_MSG_HEADER                                                              /* _H2ASN_Skip */
    TAFAGENT_MSG_ID_ENUM_UINT32         enMsgId;                                /* _H2ASN_Skip */
    VOS_UINT32                          ulRet;                                  /* 回复结果 */
    TAF_AGENT_SYS_MODE_STRU             stSysMode;                              /* 系统模式，包括接入技术与系统子模式 */
}TAFAGENT_MTA_GET_SYSMODE_CNF_STRU;
/* Added by s00217060 for 主动上报AT命令控制下移至C核, 2013-3-25, end */

/*****************************************************************************
 结构名    : TAFAGENT_APS_SET_CID_QOS_PARA_REQ_STRU
 结构说明  : ID_MSG_TAF_PS_SET_CID_QOS_PARA_REQ消息结构, 设置CID 参数
 1.日    期   : 2013年06月29日
   作    者   : L60609
   修改内容   : 创建文件
*****************************************************************************/
typedef struct
{
    VOS_MSG_HEADER                                                              /* _H2ASN_Skip */
    VOS_UINT32                          ulMsgId;                                /* _H2ASN_Skip */

    VOS_UINT16                          usClientId;                             /* CLIENT ID */

    VOS_UINT8                           ucRsv1[2];

    TAF_PS_PDP_QOS_SET_PARA_STRU        stQosPara;
} TAFAGENT_APS_SET_CID_QOS_PARA_REQ_STRU;

/*****************************************************************************
 结构名    : TAFAGENT_APS_GET_CID_QOS_PARA_REQ_STRU
 结构说明  : ID_TAFAGENT_APS_GET_CID_QOS_PARA_REQ消息结构,
 1.日    期   : 2013年06月29日
   作    者   : L60609
   修改内容   : 创建文件
*****************************************************************************/
typedef struct
{
    VOS_MSG_HEADER                                                              /* _H2ASN_Skip */
    VOS_UINT32                          ulMsgId;                                /* _H2ASN_Skip */

    VOS_UINT8                           ucCid;                                  /* 要获取参数的CID */

    VOS_UINT8                           ucRsv1[3];
} TAFAGENT_APS_GET_CID_QOS_PARA_REQ_STRU;

/*****************************************************************************
 结构名    : TAFAGENT_APS_SET_CID_QOS_PARA_CNF_STRU
 结构说明  : ID_EVT_TAF_PS_SET_CID_QOS_PARA_CNF消息结构,
 1.日    期   : 2013年06月29日
   作    者   : L60609
   修改内容   : 创建文件
*****************************************************************************/
typedef struct
{
    VOS_MSG_HEADER                                                              /* _H2ASN_Skip */
    TAFAGENT_MSG_ID_ENUM_UINT32         enMsgId;                                /* _H2ASN_Skip */

    VOS_UINT32                          ulRet;                                  /* 返回结果 */
} TAFAGENT_APS_SET_CID_QOS_PARA_CNF_STRU;

/*****************************************************************************
 结构名    : TAFAGENT_APS_GET_CID_QOS_PARA_CNF_STRU
 结构说明  : ID_EVT_TAF_PS_GET_CID_QOS_PARA_CNF消息结构, 获取指定CID的参数
 1.日    期   : 2013年06月29日
   作    者   : L60609
   修改内容   : 创建文件
*****************************************************************************/
typedef struct
{
    VOS_MSG_HEADER                                                              /* _H2ASN_Skip */
    TAFAGENT_MSG_ID_ENUM_UINT32         enMsgId;                                /* _H2ASN_Skip */

    VOS_UINT32                          ulRet;                                  /* 返回结果 */

    TAF_PS_PDP_QOS_QUERY_PARA_STRU      stQosPara;

} TAFAGENT_APS_GET_CID_QOS_PARA_CNF_STRU;



/*****************************************************************************
 结构名    : TAFAGENT_MTA_GET_ANT_STATE_REQ_STRU
 结构说明  : ID_TAFAGENT_MTA_GET_ANT_STATE_REQ消息结构,
 1.日    期   : 2013年8月2日
   作    者   : z60575
   修改内容   : 创建结构
*****************************************************************************/
typedef struct
{
    VOS_MSG_HEADER                                                              /* _H2ASN_Skip */
    TAFAGENT_MSG_ID_ENUM_UINT32         enMsgId;                                /* _H2ASN_Skip */
} TAFAGENT_MTA_GET_ANT_STATE_REQ_STRU;

/*****************************************************************************
 结构名    : TAFAGENT_MTA_GET_ANT_STATE_CNF_STRU
 结构说明  : ID_TAFAGENT_MTA_GET_ANT_STATE_CNF消息结构, 获取指定CID的参数
 1.日    期   : 2013年06月29日
   作    者   : L60609
   修改内容   : 创建文件
*****************************************************************************/
typedef struct
{
    VOS_MSG_HEADER                                                              /* _H2ASN_Skip */
    TAFAGENT_MSG_ID_ENUM_UINT32         enMsgId;                                /* _H2ASN_Skip */

    VOS_UINT32                          ulRslt;
    VOS_UINT16                          usAntState;                             /* 天线状态 */
    VOS_UINT8                           aucReserved1[2];

} TAFAGENT_MTA_GET_ANT_STATE_CNF_STRU;
/*****************************************************************************
  H2ASN顶级消息结构定义
*****************************************************************************/
typedef struct
{
    TAFAGENT_MSG_ID_ENUM_UINT32         ulMsgId;                                /*_H2ASN_MsgChoice_Export TAFAGENT_MSG_ID_ENUM_UINT32*/
    VOS_UINT8                           aucMsgBlock[4];
    /***************************************************************************
        _H2ASN_MsgChoice_When_Comment          TAFAGENT_MSG_ID_ENUM_UINT32
    ****************************************************************************/
}TAF_AGENT_MSG_DATA;
/*_H2ASN_Length UINT32*/

typedef struct
{
    VOS_MSG_HEADER
    TAF_AGENT_MSG_DATA                  stMsgData;
}TafAgentInterface_MSG;


/*****************************************************************************
  5 函数实现
*****************************************************************************/




#ifdef __cplusplus
    #if __cplusplus
        }
    #endif
#endif

#endif

