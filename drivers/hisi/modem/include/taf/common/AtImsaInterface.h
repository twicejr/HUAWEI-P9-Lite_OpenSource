

#ifndef  AT_IMSA_INTERFACE_H
#define  AT_IMSA_INTERFACE_H

/*****************************************************************************
  1 头文件包含
*****************************************************************************/
#include "vos.h"
#include "TafTypeDef.h"

#include "TafApsApi.h"

#ifdef __cplusplus
#if __cplusplus
extern "C" {
#endif
#endif


#pragma pack(4)

#define AT_IMSA_IMPU_MAX_LENGTH     (128)

/* equals IMSA_MAX_CALL_NUMBER_LENGTH */
#define AT_IMSA_CALL_ASCII_NUM_MAX_LENGTH     (40)
/*****************************************************************************
  2 枚举定义
*****************************************************************************/
/*****************************************************************************
枚举名    : AT_IMSA_MSG_TYPE_ENUM
结构说明  : AT 和IMSA的之间的消息

  1.日    期   : 2013年9月13日
    作    者   : Y00213812
    修改内容   : 定义AT和IMSA之间的接口消息
*****************************************************************************/
enum AT_IMSA_MSG_TYPE_ENUM
{
    /* AT->IMSA */
    ID_AT_IMSA_CIREG_SET_REQ                = 0x0001,                           /* _H2ASN_MsgChoice AT_IMSA_CIREG_SET_REQ_STRU */
    ID_AT_IMSA_CIREG_QRY_REQ,                                                   /* _H2ASN_MsgChoice AT_IMSA_CIREG_QRY_REQ_STRU */
    ID_AT_IMSA_CIREP_SET_REQ,                                                   /* _H2ASN_MsgChoice AT_IMSA_CIREP_SET_REQ_STRU */
    ID_AT_IMSA_CIREP_QRY_REQ,                                                   /* _H2ASN_MsgChoice AT_IMSA_CIREP_QRY_REQ_STRU */
    ID_AT_IMSA_VOLTEIMPU_QRY_REQ,                                               /* _H2ASN_MsgChoice AT_IMSA_VOLTEIMPU_QRY_REQ_STRU */

    ID_AT_IMSA_CCWAI_SET_REQ,                                                   /* _H2ASN_MsgChoice AT_IMSA_CCWAI_SET_REQ_STRU */


    /* IMSA->AT */
    ID_IMSA_AT_CIREG_SET_CNF                = 0x1001,                           /* _H2ASN_MsgChoice IMSA_AT_CIREG_SET_CNF_STRU */
    ID_IMSA_AT_CIREG_QRY_CNF,                                                   /* _H2ASN_MsgChoice IMSA_AT_CIREG_QRY_CNF_STRU */
    ID_IMSA_AT_CIREP_SET_CNF,                                                   /* _H2ASN_MsgChoice IMSA_AT_CIREP_SET_CNF_STRU */
    ID_IMSA_AT_CIREP_QRY_CNF,                                                   /* _H2ASN_MsgChoice IMSA_AT_CIREP_QRY_CNF_STRU */

    ID_IMSA_AT_VOLTEIMPU_QRY_CNF,                                               /* _H2ASN_MsgChoice IMSA_AT_VOLTEIMPU_QRY_CNF_STRU */


    ID_IMSA_AT_CCWAI_SET_CNF,                                                   /* _H2ASN_MsgChoice IMSA_AT_CCWAI_SET_CNF_STRU */

    ID_IMSA_AT_CIREGU_IND,                                                      /* _H2ASN_MsgChoice IMSA_AT_CIREGU_IND_STRU */
    ID_IMSA_AT_CIREPH_IND,                                                      /* _H2ASN_MsgChoice IMSA_AT_CIREPH_IND_STRU */
    ID_IMSA_AT_CIREPI_IND,                                                      /* _H2ASN_MsgChoice IMSA_AT_CIREPI_IND_STRU */

    ID_IMSA_AT_VT_PDP_ACTIVATE_IND,                                             /* _H2ASN_MsgChoice IMSA_AT_VT_PDP_ACTIVATE_IND_STRU */
    ID_IMSA_AT_VT_PDP_DEACTIVATE_IND,                                           /* _H2ASN_MsgChoice IMSA_AT_VT_PDP_DEACTIVATE_IND_STRU */

    ID_IMSA_AT_MT_STATES_IND,                                                   /* _H2ASN_MsgChoice IMSA_AT_MT_STATES_IND_STRU */

    ID_AT_IMSA_MSG_BUTT
};
typedef  VOS_UINT32  AT_IMSA_MSG_TYPE_ENUM_UINT32;


/*****************************************************************************
枚举名    : AT_IMSA_IMS_REG_STATE_REPORT_ENUM
结构说明  : IMS注册状态上报控制

  1.日    期   : 2013年9月13日
    作    者   : Y00213812
    修改内容   : 新增枚举
*****************************************************************************/
enum AT_IMSA_IMS_REG_STATE_REPORT_ENUM
{
    AT_IMSA_IMS_REG_STATE_DISABLE_REPORT        = 0,
    AT_IMSA_IMS_REG_STATE_ENABLE_REPORT,
    AT_IMSA_IMS_REG_STATE_ENABLE_EXTENDED_REPROT,

    AT_IMSA_IMS_REG_STATE_REPROT_BUTT
};
typedef  VOS_UINT32  AT_IMSA_IMS_REG_STATE_REPORT_ENUM_UINT32;

/*****************************************************************************
枚举名    : AT_IMSA_CCWAI_MODE_ENUM
结构说明  : 网络是否支持IMSVOPS

  1.日    期   : 2013年9月13日
    作    者   : Y00213812
    修改内容   : 新增枚举
*****************************************************************************/
enum AT_IMSA_CCWAI_MODE_ENUM
{
    AT_IMSA_CCWAI_MODE_DISABLE               = 0,
    AT_IMSA_CCWAI_MODE_ENABLE,

    AT_IMSA_CCWAI_MODE_BUTT
};
typedef  VOS_UINT8 AT_IMSA_CCWAI_MODE_ENUM_UINT8;


/*****************************************************************************
枚举名    : AT_IMSA_IMSVOPS_CAPABILITY_ENUM
结构说明  : 网络是否支持IMSVOPS

  1.日    期   : 2013年9月13日
    作    者   : Y00213812
    修改内容   : 新增枚举
*****************************************************************************/
enum AT_IMSA_IMSVOPS_CAPABILITY_ENUM
{
    AT_IMSA_NW_NOT_SUPORT_IMSVOPS               = 0,
    AT_IMSA_NW_SUPORT_IMSVOPS,

    AT_IMSA_IMSVOPS_CAPABILITY_BUTT
};
typedef  VOS_UINT32  AT_IMSA_IMSVOPS_CAPABILITY_ENUM_UINT32;


/*****************************************************************************
枚举名    : AT_IMSA_CIREP_REPORT_ENUM
结构说明  : 是否允许CIREPH和CIREPI主动上报

  1.日    期   : 2013年9月13日
    作    者   : Y00213812
    修改内容   : 新增枚举
*****************************************************************************/
enum AT_IMSA_CIREP_REPORT_ENUM
{
    AT_IMSA_CIREP_REPORT_DISENABLE      = 0,
    AT_IMSA_CIREP_REPORT_ENABLE,

    AT_IMSA_CIREP_REPORT_BUTT
};
typedef  VOS_UINT32  AT_IMSA_CIREP_REPORT_ENUM_UINT32;


/*****************************************************************************
枚举名    : AT_IMSA_SRVCC_HANDVOER_ENUM
结构说明  : SRVCC过程状态

  1.日    期   : 2013年9月13日
    作    者   : Y00213812
    修改内容   : 新增枚举
*****************************************************************************/
enum AT_IMSA_SRVCC_HANDVOER_ENUM
{
    AT_IMSA_SRVCC_HANDOVER_STARTED                = 0,
    AT_IMSA_SRVCC_HANDOVER_SUCCESS,
    AT_IMSA_SRVCC_HANDOVER_CANCEL,
    AT_IMSA_SRVCC_HANDOVER_FAILURE,

    AT_IMSA_SRVCC_HANDOVER_BUTT
};
typedef  VOS_UINT32  AT_IMSA_SRVCC_HANDVOER_ENUM_UINT32;


/*****************************************************************************
  3 类型定义
*****************************************************************************/
/*****************************************************************************
结构名    : AT_IMSA_MSG_STRU
结构说明  : AT模块与IMSA模块间的消息结构

1.日    期  : 2013年09月12日
  作    者  : Y00213812
  修改内容  : 新增结构
*****************************************************************************/
typedef struct
{
    VOS_MSG_HEADER                                                              /* _H2ASN_Skip */
    VOS_UINT32                          ulMsgId;                                /* _H2ASN_Skip */
    VOS_UINT16                          usClientId;
    VOS_UINT8                           ucOpId;
    VOS_UINT8                           aucReserved[1];
    VOS_UINT8                           aucContent[4];
} AT_IMSA_MSG_STRU;

/*****************************************************************************
结构名    : AT_IMSA_CIREG_QRY_REQ_STRU
结构说明  : ID_AT_IMSA_CIREG_QRY_REQ的消息结构

1.日    期  : 2013年09月12日
  作    者  : Y00213812
  修改内容  : 新增结构
*****************************************************************************/
typedef AT_IMSA_MSG_STRU AT_IMSA_CIREG_QRY_REQ_STRU;


/*****************************************************************************
结构名    : AT_IMSA_CIREP_QRY_REQ_STRU
结构说明  : ID_AT_IMSA_CIREP_QRY_REQ的消息结构

1.日    期  : 2013年09月12日
  作    者  : Y00213812
  修改内容  : 新增结构
*****************************************************************************/
typedef AT_IMSA_MSG_STRU AT_IMSA_CIREP_QRY_REQ_STRU;

/*****************************************************************************
结构名    : AT_IMSA_VOLTEIMPU_QRY_REQ_STRU
结构说明  : ID_AT_IMSA_VOLTEIMPU_QRY_REQ的消息结构

1.日    期  : 2013年12月05日
  作    者  : Y00213812
  修改内容  : 新增结构
*****************************************************************************/
typedef AT_IMSA_MSG_STRU AT_IMSA_VOLTEIMPU_QRY_REQ_STRU;


/*****************************************************************************
 结构名  : AT_IMSA_CCWAI_SET_REQ_STRU
 结构说明: ^CCWAI IMS  呼叫等待
 修改历史      :
  1.日    期   : 2014年3月11日
    作    者   : w00209181
    修改内容   : 新增结构
*****************************************************************************/
typedef struct
{
    VOS_MSG_HEADER                                                              /* _H2ASN_Skip */
    VOS_UINT32                          ulMsgId;                                /* _H2ASN_Skip */
    VOS_UINT16                          usClientId;
    VOS_UINT8                           ucOpId;
    AT_IMSA_CCWAI_MODE_ENUM_UINT8       enMode;
    VOS_UINT32                          ulSrvClass;
} AT_IMSA_CCWAI_SET_REQ_STRU;

/*****************************************************************************
 结构名  : IMSA_AT_CCWAI_SET_CNF_STRU
 结构说明: ^CCWAI IMS  呼叫等待
 修改历史      :
  1.日    期   : 2014年3月11日
    作    者   : w00209181
    修改内容   : 新增结构
*****************************************************************************/
typedef struct
{
    VOS_MSG_HEADER                                                              /* _H2ASN_Skip */
    VOS_UINT32                          ulMsgId;                                /* _H2ASN_Skip */
    VOS_UINT16                          usClientId;
    VOS_UINT8                           ucOpId;
    VOS_UINT8                           ucReserved;
    VOS_UINT32                          ulResult;
} IMSA_AT_CCWAI_SET_CNF_STRU;


/*****************************************************************************
 结构名  : AT_IMSA_CIREG_SET_REQ_STRU
 结构说明: +CIREG IMS注册状态主动上报控制设置

 修改历史      :
  1.日    期   : 2013年9月13日
    作    者   : Y00213812
    修改内容   : 新增结构
*****************************************************************************/
typedef struct
{
    VOS_MSG_HEADER                                                              /* _H2ASN_Skip */
    VOS_UINT32                          ulMsgId;                                /* _H2ASN_Skip */
    VOS_UINT16                          usClientId;
    VOS_UINT8                           ucOpId;
    VOS_UINT8                           aucReserved[1];
    AT_IMSA_IMS_REG_STATE_REPORT_ENUM_UINT32    enCireg;
} AT_IMSA_CIREG_SET_REQ_STRU;


/*****************************************************************************
 结构名  : IMSA_AT_CIREG_SET_CNF_STRU
 结构说明: +CIREG IMS注册状态主动上报控制

 修改历史      :
  1.日    期   : 2013年9月13日
    作    者   : Y00213812
    修改内容   : 新增结构
*****************************************************************************/
typedef struct
{
    VOS_MSG_HEADER                                                              /* _H2ASN_Skip */
    VOS_UINT32                          ulMsgId;                                /* _H2ASN_Skip */
    VOS_UINT16                          usClientId;
    VOS_UINT8                           ucOpId;
    VOS_UINT8                           aucReserved[1];
    VOS_UINT32                          ulResult;                               /* 成功返回VOS_OK，失败返回VOS_ERR */
} IMSA_AT_CIREG_SET_CNF_STRU;


/*****************************************************************************
 结构名  : IMSA_AT_CIREG_QRY_CNF_STRU
 结构说明: +CIREG IMS注册状态查询结果

 修改历史      :
  1.日    期   : 2013年9月13日
    作    者   : Y00213812
    修改内容   : 新增结构
*****************************************************************************/
typedef struct
{
    VOS_MSG_HEADER                                                              /* _H2ASN_Skip */
    VOS_UINT32                          ulMsgId;                                /* _H2ASN_Skip */
    VOS_UINT16                          usClientId;
    VOS_UINT8                           ucOpId;
    VOS_UINT8                           aucReserved[1];

    VOS_UINT32                          bitOpExtInfo    : 1 ;                   /* +CIREG=2时,标志位置1 */
    VOS_UINT32                          bitOpSpare      : 31;

    AT_IMSA_IMS_REG_STATE_REPORT_ENUM_UINT32    enCireg;
    VOS_UINT32                          ulRegInfo;
    VOS_UINT32                          ulExtInfo;                              /* +CIREG=2时 ，扩展信息暂时回复0 */
    VOS_UINT32                          ulResult;                               /* 成功返回VOS_OK，失败返回VOS_ERR */
} IMSA_AT_CIREG_QRY_CNF_STRU;

/*****************************************************************************
 结构名  : IMSA_AT_CIREGU_IND_STRU
 结构说明: ID_IMSA_AT_CIREGU_IND IMS注册状态主动上报

 修改历史      :
  1.日    期   : 2013年9月13日
    作    者   : Y00213812
    修改内容   : 新增结构
*****************************************************************************/
typedef struct
{
    VOS_MSG_HEADER                                                              /* _H2ASN_Skip */
    VOS_UINT32                          ulMsgId;                                /* _H2ASN_Skip */
    VOS_UINT16                          usClientId;                             /* 主动上报时填0X3FFF */
    VOS_UINT8                           ucOpId;                                 /* 填0 */
    VOS_UINT8                           aucReserved[1];

    VOS_UINT32                          bitOpExtInfo    : 1 ;
    VOS_UINT32                          bitOpSpare      : 31;

    VOS_UINT32                          ulRegInfo;
    VOS_UINT32                          ulExtInfo;
} IMSA_AT_CIREGU_IND_STRU;


/*****************************************************************************
 结构名  : AT_IMSA_CIREP_SET_REQ_STRU
 结构说明: +CIREP SRVCC切换状态主动上报控制

 修改历史      :
  1.日    期   : 2013年9月13日
    作    者   : Y00213812
    修改内容   : 新增结构
*****************************************************************************/
typedef struct
{
    VOS_MSG_HEADER                                                              /* _H2ASN_Skip */
    VOS_UINT32                          ulMsgId;                                /* _H2ASN_Skip */
    VOS_UINT16                          usClientId;
    VOS_UINT8                           ucOpId;
    VOS_UINT8                           aucReserved[1];
    AT_IMSA_CIREP_REPORT_ENUM_UINT32    enReport;
} AT_IMSA_CIREP_SET_REQ_STRU;


/*****************************************************************************
 结构名  : IMSA_AT_CIREP_SET_CNF_STRU
 结构说明: +CIREP SRVCC切换状态主动上报控制

 修改历史      :
  1.日    期   : 2013年9月13日
    作    者   : Y00213812
    修改内容   : 新增结构
*****************************************************************************/
typedef struct
{
    VOS_MSG_HEADER                                                              /* _H2ASN_Skip */
    VOS_UINT32                          ulMsgId;                                /* _H2ASN_Skip */
    VOS_UINT16                          usClientId;
    VOS_UINT8                           ucOpId;
    VOS_UINT8                           aucReserved[1];
    VOS_UINT32                          ulResult;                               /* 成功返回VOS_OK，失败返回VOS_ERR */
} IMSA_AT_CIREP_SET_CNF_STRU;


/*****************************************************************************
 结构名  : IMSA_AT_CIREP_QRY_CNF_STRU
 结构说明: +CIREP IMSVOPS能力查询

 修改历史      :
  1.日    期   : 2013年9月13日
    作    者   : Y00213812
    修改内容   : 新增结构
*****************************************************************************/
typedef struct
{
    VOS_MSG_HEADER                                                              /* _H2ASN_Skip */
    VOS_UINT32                          ulMsgId;                                /* _H2ASN_Skip */
    VOS_UINT16                          usClientId;
    VOS_UINT8                           ucOpId;
    VOS_UINT8                           aucReserved[1];
    AT_IMSA_CIREP_REPORT_ENUM_UINT32            enReport;
    AT_IMSA_IMSVOPS_CAPABILITY_ENUM_UINT32      enImsvops;
    VOS_UINT32                          ulResult;                               /* 成功返回VOS_OK，失败返回VOS_ERR */
} IMSA_AT_CIREP_QRY_CNF_STRU;

/*****************************************************************************
 结构名  : IMSA_AT_VOLTEIMPU_QRY_CNF_STRU
 结构说明: ^VOLTEIMPU IMPU信息查询结果

 修改历史      :
  1.日    期   : 2013年12月05日
    作    者   : Y00213812
    修改内容   : 新增结构
*****************************************************************************/
typedef struct
{
    VOS_MSG_HEADER                                             /* _H2ASN_Skip */
    VOS_UINT32                          ulMsgId;               /* _H2ASN_Skip */
    VOS_UINT16                          usClientId;
    VOS_UINT8                           ucOpId;
    VOS_UINT8                           aucReserved[1];
    VOS_UINT32                          ulResult;              /* 成功返回VOS_OK，失败返回VOS_ERR */
    VOS_UINT32                          ulImpuLen;
    VOS_CHAR                            aucImpu[AT_IMSA_IMPU_MAX_LENGTH];
} IMSA_AT_VOLTEIMPU_QRY_CNF_STRU;


/*****************************************************************************
 结构名  : IMSA_AT_CIREPH_IND_STRU
 结构说明: +CIREPH SRVCC切换状态主动上报

 修改历史      :
  1.日    期   : 2013年9月13日
    作    者   : Y00213812
    修改内容   : 新增结构
*****************************************************************************/
typedef struct
{
    VOS_MSG_HEADER                                                              /* _H2ASN_Skip */
    VOS_UINT32                          ulMsgId;                                /* _H2ASN_Skip */
    VOS_UINT16                          usClientId;                             /* 主动上报时填0X3FFF */
    VOS_UINT8                           ucOpId;                                 /* 填0 */
    VOS_UINT8                           aucReserved[1];
    AT_IMSA_SRVCC_HANDVOER_ENUM_UINT32  enHandover;
} IMSA_AT_CIREPH_IND_STRU;

/*****************************************************************************
 结构名  : IMSA_AT_CIREPI_IND_STRU
 结构说明: +CIREPI IMSVOPS主动上报

 修改历史      :
  1.日    期   : 2013年9月23日
    作    者   : Y00213812
    修改内容   : 新增结构
*****************************************************************************/
typedef struct
{
    VOS_MSG_HEADER                                                              /* _H2ASN_Skip */
    VOS_UINT32                          ulMsgId;                                /* _H2ASN_Skip */
    VOS_UINT16                          usClientId;                             /* 主动上报时填0X3FFF */
    VOS_UINT8                           ucOpId;                                 /* 填0 */
    VOS_UINT8                           aucReserved[1];
    AT_IMSA_IMSVOPS_CAPABILITY_ENUM_UINT32      enImsvops;
} IMSA_AT_CIREPI_IND_STRU;


/*****************************************************************************
 结构名称: IMSA_AT_VT_PDP_ACTIVATE_IND_STRU
 结构说明: IMSA上报VT承载激活成功结果的结构

 修改历史      :
  1.日    期   : 2014年07月31日
    作    者   : f00179208
    修改内容   : 新增结构
*****************************************************************************/
typedef struct
{
    VOS_MSG_HEADER                                             /* _H2ASN_Skip */
    VOS_UINT32                          ulMsgId;               /* _H2ASN_Skip */
    VOS_UINT16                          usClientId;
    VOS_UINT8                           ucOpId;
    VOS_UINT8                           aucReserved[1];
    TAF_PDP_ADDR_STRU                   stPdpAddr;
    TAF_PDP_DNS_STRU                    stIpv4Dns;
    TAF_PDP_IPV6_DNS_STRU               stIpv6Dns;
} IMSA_AT_VT_PDP_ACTIVATE_IND_STRU;


/*****************************************************************************
 结构名称: IMSA_AT_VT_PDP_DEACTIVATE_IND_STRU
 结构说明: IMSA上报VT承载去激活成功结果的结构

 修改历史      :
  1.日    期   : 2014年07月31日
    作    者   : f00179208
    修改内容   : 新增结构
*****************************************************************************/
typedef struct
{
    VOS_MSG_HEADER                                             /* _H2ASN_Skip */
    VOS_UINT32                          ulMsgId;               /* _H2ASN_Skip */
    VOS_UINT16                          usClientId;
    VOS_UINT8                           ucOpId;
    TAF_PDP_TYPE_ENUM_UINT8             enPdpType;
} IMSA_AT_VT_PDP_DEACTIVATE_IND_STRU;

/*****************************************************************************
 结构名称： IMSA_AT_MT_STATES_IND_STRU
 结构说明:  IMSA上报AT收到被叫事件的结构

 修改历史:
 1.日期: 2015年03月18日
   作者: m00277840
   修改内容:新增结构
*****************************************************************************/
typedef struct
{
    VOS_MSG_HEADER                                          /* _H2ASN_Skip */
    VOS_UINT32                          ulMsgId;            /* _H2ASN_Skip */
    VOS_UINT16                          usClientId;
    VOS_UINT8                           ucOpId;
    VOS_UINT8                           aucReserved[1];
    VOS_UINT32                          ulCauseCode;
    VOS_UINT8                           ucMtStatus;
    VOS_UINT8                           aucRsv[3];
    VOS_UINT8                           aucAsciiCallNum[AT_IMSA_CALL_ASCII_NUM_MAX_LENGTH];
} IMSA_AT_MT_STATES_IND_STRU;
/*****************************************************************************
  4 宏定义
*****************************************************************************/


/*****************************************************************************
  5 全局变量声明
*****************************************************************************/


/*****************************************************************************
  6 接口函数声明
*****************************************************************************/

/*****************************************************************************
  7 OTHERS定义
*****************************************************************************/

/* ASN解析结构 */
typedef struct
{
    VOS_UINT32                          ulMsgId;                                /*_H2ASN_MsgChoice_Export AT_IMSA_MSG_TYPE_ENUM_UINT32 */
    VOS_UINT8                           aucMsg[4];
    /***************************************************************************
        _H2ASN_MsgChoice_When_Comment          AT_IMSA_MSG_TYPE_ENUM_UINT32
    ****************************************************************************/
}AT_IMSA_INTERFACE_MSG_DATA;
/*_H2ASN_Length UINT32*/

typedef struct
{
    VOS_MSG_HEADER
    AT_IMSA_INTERFACE_MSG_DATA           stMsgData;
} AtImsaInterface_MSG;


#if ((VOS_OS_VER == VOS_WIN32) || (VOS_OS_VER == VOS_NUCLEUS))
#pragma pack()
#else
#pragma pack(0)
#endif


#ifdef __cplusplus
#if __cplusplus
}
#endif
#endif

#endif


