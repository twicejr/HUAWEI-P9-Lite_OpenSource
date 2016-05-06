/******************************************************************************

    Copyright(C)2008,Hisilicon Co. LTD.

 ******************************************************************************
  File Name       : EmmLppInterface.h
  Description     : EmmLppInterface.h header file
  History           :

******************************************************************************/

#ifndef __EMMLPPINTERFACE_H__
#define __EMMLPPINTERFACE_H__

#ifdef __cplusplus
#if __cplusplus
extern "C" {
#endif
#endif


/*****************************************************************************
  1 Include Headfile
*****************************************************************************/
#include "vos.h"
#include "LPSCommon.h"

#if (VOS_OS_VER != VOS_WIN32)
#pragma pack(4)
#else
#pragma pack(push, 4)
#endif
/*****************************************************************************
  2 macro
*****************************************************************************/
#define LPP_LMM_MSG_HDR  0
#define LMM_LPP_MSG_HDR  100

/*****************************************************************************
  3 Massage Declare
*****************************************************************************/



/*****************************************************************************
  4 Enum
*****************************************************************************/
/*****************************************************************************
 枚举名    : LMM_LPP_MSG_TYPE_ENUM
 枚举说明  : EMM与LPP消息类型
*****************************************************************************/
enum LMM_LPP_MSG_TYPE_ENUM
{
    /*消息原语*/
    /*LPP发送给LMM的消息原语*/
    ID_LPP_LMM_DATA_REQ                     = (LPP_LMM_MSG_HDR + 0x1),  /* _H2ASN_MsgChoice LPP_LMM_DATA_REQ_STRU*/
    ID_LPP_LMM_EST_REQ                      = (LPP_LMM_MSG_HDR + 0x2),  /* _H2ASN_MsgChoice LPP_LMM_EST_REQ_STRU*/

    /*LMM 发送给LPP的消息原语*/
    ID_LMM_LPP_DATA_CNF                     = (LMM_LPP_MSG_HDR + 0x1),  /* _H2ASN_MsgChoice LMM_LPP_DATA_CNF_STRU*/
    ID_LMM_LPP_EST_CNF                      = (LMM_LPP_MSG_HDR + 0x2),  /* _H2ASN_MsgChoice LMM_LPP_EST_CNF_STRU*/
    ID_LMM_LPP_START_IND                    = (LMM_LPP_MSG_HDR + 0x3),  /* _H2ASN_MsgChoice LMM_LPP_START_IND_STRU*/
    ID_LMM_LPP_STOP_IND                     = (LMM_LPP_MSG_HDR + 0x4),  /* _H2ASN_MsgChoice LMM_LPP_STOP_IND_STRU*/
    ID_LMM_LPP_CELL_CHANGE_IND              = (LMM_LPP_MSG_HDR + 0x5),  /* _H2ASN_MsgChoice LMM_LPP_CELL_CHANGE_IND*/
    ID_LMM_LPP_DATA_IND                     = (LMM_LPP_MSG_HDR + 0x6),  /* _H2ASN_MsgChoice LMM_LPP_DATA_IND_STRU*/
    ID_LMM_LPP_REL_IND                      = (LMM_LPP_MSG_HDR + 0x7),  /* _H2ASN_MsgChoice LMM_LPP_REL_IND_STRU*/

    ID_LMM_LPP_BUTT
};
typedef VOS_UINT32 LMM_LPP_MSG_TYPE_ENUM_UINT32;

/*****************************************************************************
 枚举名    : LMM_LPP_SEND_RSLT_ENUM
 枚举说明  : 直传结果
 作者      : lifuxin 00253982 2015-07-02 新开发
*****************************************************************************/
enum LMM_LPP_SEND_RSLT_ENUM
{
    LMM_LPP_SEND_RSLT_SUCCESS                       = 0, /*发送成功*/
    LMM_LPP_SEND_RSLT_FAIL_PS_NOT_ATTACHED          = 1, /*PS域未注册*/
    LMM_LPP_SEND_RSLT_FAIL_PS_ATTACH_NOT_ALLOWED    = 2, /*PS不允许注册*/
    LMM_LPP_SEND_RSLT_FAIL_USIM_PS_INVALID          = 3, /*USIM卡无效*/
    LMM_LPP_SEND_RSLT_FAIL_ACCESS_BARRED            = 4, /*被BAR*/
    LMM_LPP_SEND_RSLT_FAIL_RRC_CONN_NOT_EXIST       = 5, /*连接状态不存在，SS接着用EST REQ请求建链*/
    LMM_LPP_SEND_RSLT_LOW_LAYER_FAIL                = 6, /*底层发送失败，建议1s后再尝试*/
    LMM_LPP_SEND_RSLT_FAIL_3411_RUNNING             = 7, /*3411在运行，可以过10s再尝试*/
    LMM_LPP_SEND_RSLT_FAIL_3402_RUNNING             = 8, /*3402在运行*/
    LMM_LPP_SEND_RSLT_OHTERS                        = 9, /*其他失败原因值*/

    LMM_LPP_SEND_RSLT_BUTT
};
typedef VOS_UINT32 LMM_LPP_SEND_RSLT_ENUM_UINT32;

/*****************************************************************************
 枚举名    : LMM_LPP_EST_RESULT_ENUM
 枚举说明  : 建链的结果
 作者      : lifuxin 00253982 2015-07-02 新开发
*****************************************************************************/
enum LMM_LPP_EST_RESULT_ENUM
{
    LMM_LPP_EST_RESULT_SUCC                         = 0, /*建链成功*/
    LMM_LPP_EST_RESULT_FAIL_PS_NOT_ATTACHED         = 1, /*PS域未注册*/
    LMM_LPP_EST_RESULT_FAIL_PS_ATTACH_NOT_ALLOWED   = 2, /*PS不允许注册*/
    LMM_LPP_EST_RESULT_FAIL_USIM_PS_INVALID         = 3, /*USIM卡无效*/
    LMM_LPP_EST_RESULT_FAIL_ACCESS_BARRED           = 4, /*被BAR*/
    LMM_LPP_EST_RESULT_FAIL_STATE_CANNOT_SERVICE    = 5, /*当前状态无法发起SERVICE*/
    LMM_LPP_EST_RESULT_FAIL_3411_RUNNING            = 6, /*3411在运行，可以过10s再尝试*/
    LMM_LPP_EST_RESULT_FAIL_3402_RUNNING            = 8, /*3402在运行*/
    LMM_LPP_EST_RESULT_FAIL_SERVICE_FAIL            = 9, /*SERVICE失败，建议2s后再尝试*/
    LMM_LPP_EST_RESULT_FAIL_OTHERS                  = 10, /*其他失败原因值*/

    LMM_LPP_EST_RESULT_BUTT
};
typedef VOS_UINT32 LMM_LPP_EST_RESULT_ENUM_UINT32;

/*****************************************************************************
 枚举名    : LMM_LPP_REL_CAUSE_ENUM
 枚举说明  : 链路释放原因
 作者      : lifuxin 00253982 2015-07-02 新开发
*****************************************************************************/
enum LMM_LPP_REL_CAUSE_ENUM
{
    LMM_LPP_REL_CAUSE_CONN_FAIL                  = 0,  /* RR Connection Failure*/
    LMM_LPP_REL_CAUSE_LOAD_BALANCE_REQ           = 1,  /* Rrc Con Release 带有的原因为loadBalancingTAUrequired */
    LMM_LPP_REL_CAUSE_OTHER_REASON               = 2,  /* Rrc Con Release 带有的原因不是loadBalancingTAUrequired，或无线链路失败释放原因*/
    LMM_LPP_REL_CAUSE_NAS_DATA_ABSENT            = 3,  /* NAS Data Request: Connection Absent*/
    LMM_LPP_REL_CAUSE_RRC_ABNORMAL               = 4,  /* RRC或底层系统异常释放原因*/
    LMM_LPP_REL_CAUSE_GU2L_HO_ERR                = 5,  /* GU向L切换失败 */
    LMM_LPP_REL_CAUSE_L2GU_REDIRECT              = 6,  /* 异系统重定向 */
    LMM_LPP_REL_CAUSE_CSFB_HIGH_PRIOR            = 7,  /* Rrc Con Release 带有的原因 cs-FallbackHighPriority */
    LMM_LPP_REL_CAUSE_NO_RF                      = 8,  /* DSDS特性打开可能会导致NORF */

    LMM_LPP_REL_CAUSE_BUTT
};
typedef VOS_UINT32 LMM_LPP_REL_CAUSE_ENUM_UINT32;

/*****************************************************************************
 5. STRUCT
*****************************************************************************/
/*****************************************************************************
 结构名    : LMM_LPP_START_IND_STRU
 结构说明  : LMM_LPP_START_IND_STRU数据结构
 作者      : lifuxin 00253982 2015-07-02 新开发
*****************************************************************************/
typedef struct
{
    VOS_MSG_HEADER                                          /*_H2ASN_Skip*/
    VOS_UINT32                          ulMsgId;            /*_H2ASN_Skip*/  /* 消息头 */

    VOS_UINT32                          ulRsv;              /*对于LPP的开机初始化，无需带更多信息，LPP收到该消息的时候初始化相关全局数据即可*/
}LMM_LPP_START_IND_STRU;

/*****************************************************************************
 结构名    : LMM_LPP_STOP_IND_STRU
 结构说明  : LMM_LPP_STOP_IND_STRU数据结构
 作者      : lifuxin 00253982 2015-07-02 新开发
*****************************************************************************/
typedef struct
{
    VOS_MSG_HEADER                                          /*_H2ASN_Skip*/
    VOS_UINT32                          ulMsgId;            /*_H2ASN_Skip*/  /* 消息头 */

    VOS_UINT32                          ulRsv;              /*关机需要带更多信息，只要清空相关全局数据结构即可*/
}LMM_LPP_STOP_IND_STRU;

/*****************************************************************************
 结构名    : LMM_LPP_DATA_CNF_STRU
 结构说明  : LMM_LPP_DATA_CNF_STRU数据结构
 作者      : lifuxin 00253982 2015-07-02 新开发
*****************************************************************************/
typedef struct
{
    VOS_MSG_HEADER                                                  /*_H2ASN_Skip*/
    VOS_UINT32                                  ulMsgId;            /*_H2ASN_Skip*/

    VOS_UINT32                                  ulOpId;             /*维护LMM, LPP消息交互的计数*/
    LMM_LPP_SEND_RSLT_ENUM_UINT32               enDataCnfRst;       /*Lpp Data cnf结果*/
}LMM_LPP_DATA_CNF_STRU;

/*****************************************************************************
 结构名    : LMM_LPP_EST_CNF_STRU
 结构说明  : LMM_LPP_EST_CNF_STRU数据结构
 作者      : lifuxin 00253982 2015-07-02 新开发
*****************************************************************************/
typedef struct
{
    VOS_MSG_HEADER                                          /*_H2ASN_Skip*/
    VOS_UINT32                          ulMsgId;            /*_H2ASN_Skip*/

    VOS_UINT32                          ulOpId;             /*维护LMM, LPP消息交互的计数*/
    LMM_LPP_EST_RESULT_ENUM_UINT32      ulEstRst;           /*建链结果*/
} LMM_LPP_EST_CNF_STRU;

/*****************************************************************************
 结构名    : LMM_LPP_CELL_CHANGE_IND
 结构说明  : LMM_LPP_CELL_CHANGE_IND数据结构
 作者      : lifuxin 00253982 2015-07-02 新开发
*****************************************************************************/
typedef struct
{
    VOS_MSG_HEADER                                          /*_H2ASN_Skip*/
    VOS_UINT32                          ulMsgId;            /*_H2ASN_Skip*/  /* 消息头 */

    VOS_UINT32                          ulCellId;           /* 物理小区ID发生变化的时候则通知LPP*/
    VOS_UINT32                          ulEarfcn;
    VOS_UINT16                          usPhyCellId;
    VOS_UINT8                           aucPlmnId[3];
    VOS_UINT8                           aucRsv[3];
}LMM_LPP_CELL_CHANGE_IND;

/*****************************************************************************
 结构名    : LPP_LMM_MSG_STRU
 结构说明  : LPP_LMM_MSG_STRU空口消息数据结构
 作者      : lifuxin 00253982 2015-07-02 新开发
*****************************************************************************/
typedef struct
{
    VOS_UINT32                         ulLppMsgSize;
    VOS_UINT8                          aucLppMsg[4];       /* 消息的前四个字节内容             */
    /*************************************************************************
        _H2ASN_Array2String
    *************************************************************************/
}LPP_LMM_MSG_STRU;

/*****************************************************************************
 结构名    : LMM_LPP_DATA_IND_STRU
 结构说明  : LMM_LPP_DATA_IND_STRU数据结构
 作者      : lifuxin 00253982 2015-07-02 新开发
*****************************************************************************/
typedef struct
{
    VOS_MSG_HEADER                                          /*_H2ASN_Skip*/
    VOS_UINT32                          ulMsgId;            /*_H2ASN_Skip*/ /* 消息头 */

    VOS_UINT32                          ulSessionId;        /*LPP消息的会话ID*/
    LPP_LMM_MSG_STRU                    stLppMsg;           /*LPP消息实体码流*/
}LMM_LPP_DATA_IND_STRU;

/*****************************************************************************
 结构名    : LMM_LPP_REL_IND_STRU
 结构说明  : LMM_LPP_REL_IND_STRU数据结构
 作者      : lifuxin 00253982 2015-07-02 新开发
*****************************************************************************/
typedef struct
{
    VOS_MSG_HEADER                                              /*_H2ASN_Skip*/
    VOS_UINT32                              ulMsgId;            /*_H2ASN_Skip*/    /*msg ID*/

    LMM_LPP_REL_CAUSE_ENUM_UINT32           enRelCause;         /* 信令释放原因 */
}LMM_LPP_REL_IND_STRU;

/*****************************************************************************
 结构名    : LPP_LMM_DATA_REQ_STRU
 结构说明  : LPP_LMM_DATA_REQ_STRU数据结构
 作者      : lifuxin 00253982 2015-07-02 新开发
*****************************************************************************/
typedef struct
{
    VOS_MSG_HEADER                                          /*_H2ASN_Skip*/
    VOS_UINT32                          ulMsgId;            /*_H2ASN_Skip*/ /* 消息头 */

    VOS_UINT32                          ulOpId;             /*维护LMM, LPP消息交互的计数*/
    VOS_UINT32                          ulSessionId;        /*会话ID，组包上行generic消息需要使用*/
    LPP_LMM_MSG_STRU                    stLppMsg;           /*LPP消息实体码流*/
}LPP_LMM_DATA_REQ_STRU;

/*****************************************************************************
 结构名    : LPP_LMM_EST_REQ_STRU
 结构说明  : LPP_LMM_EST_REQ_STRU数据结构
 作者      : lifuxin 00253982 2015-07-02 新开发
*****************************************************************************/
typedef struct
{
    VOS_MSG_HEADER                                              /*_H2ASN_Skip*/
    VOS_UINT32                              ulMsgId;            /*_H2ASN_Skip*/    /*msg ID*/

    VOS_UINT32                              ulOpId;             /*OpId计数*/
}LPP_LMM_EST_REQ_STRU;

typedef struct
{
    LMM_LPP_MSG_TYPE_ENUM_UINT32        enMsgID;            /*_H2ASN_MsgChoice_Export LMM_LPP_MSG_TYPE_ENUM_UINT32*/
    VOS_UINT8                           aucMsg[4];
    /***************************************************************************
        _H2ASN_MsgChoice_When_Comment          LMM_LPP_MSG_TYPE_ENUM_UINT32
    ****************************************************************************/
}EMM_LPP_MSG_DATA;
/*_H2ASN_Length UINT32*/

typedef struct
{
    VOS_MSG_HEADER
    EMM_LPP_MSG_DATA                     stMsgData;
}EmmLppInterface_MSG;


/*****************************************************************************
  6 UNION
*****************************************************************************/


/*****************************************************************************
  7 Extern Global Variable
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

#endif /* end of EmmLppInterface.h */





