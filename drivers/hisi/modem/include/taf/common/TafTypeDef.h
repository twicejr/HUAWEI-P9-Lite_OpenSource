
#ifndef  TAF_TYPE_DEF_H
#define  TAF_TYPE_DEF_H

#include "v_typdef.h"

#ifdef __cplusplus
#if __cplusplus
extern "C" {
#endif
#endif

#pragma pack(4)

/* LOCAL */
/*lint -e961 修改人:l60609;原因:64bit*/
#ifdef  LOCAL
#undef  LOCAL
#endif
/*lint +e961 修改人:l60609;原因:64bit*/

#ifdef _EXPORT_LOCAL
#define LOCAL
#else
#define LOCAL static
#endif


/* ---------------LogSaver可维可测功能相关定义----------------------- */
/* 1.1: OM_GreenChannel的第二个参数usPrimId的定义*/
#define     TAF_OM_GREEN_CHANNEL_PS     (0xC001)                                /* PS相关 */

/* 1.2: OM_GreenChannel的第三个参数可带一些可维可测信息，为了提高定位效率，对一些典型
   错误做了如下枚举定义 */
enum TAF_OM_GREENCHANNEL_ERR_ENUM
{
    TAF_OM_GREENCHANNEL_PS_CID_NOT_DEFINE = 0,
    TAF_OM_GREENCHANNEL_PS_CREATE_PPP_REQ_ERR,
    TAF_OM_GREENCHANNEL_PS_CREATE_RAW_DATA_PPP_REQ_ERR,
    TAF_OM_GREENCHANNEL_PS_IP_TYPE_DIAL_FAIL,
    TAF_OM_GREENCHANNEL_PS_PPP_TYPE_DIAL_FAIL,
    TAF_OM_GREENCHANNEL_PS_DEACTIVE_PDP_ERR_EVT,
    TAF_OM_GREENCHANNEL_PS_ACTIVE_PDP_REJ,
    TAF_OM_GREENCHANNEL_PS_MODIFY_PDP_REJ,
    TAF_OM_GREENCHANNEL_PS_NET_ORIG_DEACTIVE_IND,

    TAF_OM_GREENCHANNEL_ERR_BUTT
};

/*字节序定义*/
#define TAF_LITTLE_ENDIAN              1234
#define TAF_BIG_ENDIAN                 4321

#define TAF_BYTE_ORDER                 TAF_LITTLE_ENDIAN

/*OS定义*/
#define TAF_WIN32                      1
#define TAF_PSOS                       2
#define TAF_VXWORKS                    3
#define TAF_LINUX                      4
#define TAF_UNIX                       5
#define TAF_SOLARIS                    6
#define TAF_TLINUX                     7
#define TAF_HPUNIX                     8
#define TAF_IBMUNIX                    9
#define TAF_RTT                        10
#define TAF_WINCE                      11
#define TAF_NUCLEUS                    12

#ifndef TAF_OS_VER
#define TAF_OS_VER                     TAF_VXWORKS
#endif

#ifndef CONST
#define CONST const
#endif

#ifndef CONST_T
#define CONST_T   const
#endif

#ifndef STATIC
#define STATIC static
#endif

/*lint -e961 修改人:l60609;原因:64bit*/
#undef PUBLIC
#undef PRIVATE
#undef EXTERN
/*lint +e961 修改人:l60609;原因:64bit*/

#define PUBLIC    extern
#define EXTERN extern
#ifdef _EXPORT_PRIVATE
#define PRIVATE
#else
#define PRIVATE   static
#endif

/*lint -e961 修改人:l60609;原因:64bit*/
#undef OUT
#undef IN
/*lint +e961 修改人:l60609;原因:64bit*/

#define OUT
#define IN


/*TAF API数据类型*/
typedef int                 TAF_INT;
typedef signed   char       TAF_INT8;
typedef unsigned char       TAF_UINT8;

typedef signed   short      TAF_INT16;
typedef unsigned short      TAF_UINT16;

typedef signed   int        TAF_INT32;
typedef unsigned int        TAF_UINT32;

typedef char                TAF_CHAR;
typedef unsigned char       TAF_UCHAR;

typedef void                TAF_VOID;

typedef unsigned int        TAF_BOOL;
enum
{
    TAF_FALSE = 0,
    TAF_TRUE  = 1
};

typedef TAF_UINT8 MN_CLIENT_TYPE;
enum MN_CLIENT_TYPE_ENUM
{
    TAF_APP_CLIENT,
    TAF_AT_CLIENT,
    TAF_CLIENT_TYPE_BUTT
};

typedef TAF_UINT16          MN_CLIENT_ID_T;     /* APP/AT Client ID type */
typedef TAF_UINT8           MN_OPERATION_ID_T;  /* Async operation ID type */

/* 表示所有的Client */
#define MN_CLIENT_ALL                                       ((MN_CLIENT_ID_T)(-1))
#define MN_OP_ID_BUTT                                       ((MN_OPERATION_ID_T)(-1))

/* 定义CMMCA的client id */
#define CMMCA_CLIENT_ID                                     (0x88)

#define  TAF_NULL_PTR                   0                    /* null pointer */

#define  TAF_MAX_STATUS_TI              1

#define  TAF_ERR_CODE_BASE              (0)                 /* TAF层通用错误码定义 */
#define  TAF_ERR_PHONE_BASE             (150)               /* 电话管理错误码 */
#define TAF_ERR_PB_BASE                 (350)               /* 电话本错误码 */
#define TAF_ERR_SAT_BASE                (400)               /* SAT错误码 */
#define TAF_ERR_SS_BASE                 (0x400)             /* SS错误码 */
#define TAF_ERR_SS_IMS_BASE             (0x1000)            /* IMS回复的SS错误码 */
#define TAF_ERR_SS_IMSA_BASE            (0x2000)            /* IMSA回复的SS错误码 */

/*****************************************************************************
 枚举名    : TAF_ERROR_CODE_ENUM_UINT32
 结构说明  : TAF层通用错误码

  3.日    期   : 2013年07月09日
    作    者   : s00217060
    修改内容   : VoLTE_PhaseI项目:枚举定义进行调整
                (1)CC层（网络）的原因值从1~255（目前协议规定最大127）
                (2)CALL模块内部的原因值从256~511
                (3)IMS原因值范围512~767
                (4)IMSA模块内部原因值768~1023

*****************************************************************************/
enum TAF_ERROR_CODE_ENUM
{
    TAF_ERR_NO_ERROR                                        = (TAF_ERR_CODE_BASE),          /* 成功 */
    TAF_ERR_ERROR                                           = (TAF_ERR_CODE_BASE + 1),      /* 失败 */
    TAF_ERR_NULL_PTR                                        = (TAF_ERR_CODE_BASE + 2),      /* 空指针 */
    TAF_ERR_PARA_ERROR                                      = (TAF_ERR_CODE_BASE + 3),      /* 参数错误 */
    TAF_ERR_TIME_OUT                                        = (TAF_ERR_CODE_BASE + 4),      /* 定时器超时 */
    TAF_ERR_TAF_ID_INVALID                                  = (TAF_ERR_CODE_BASE + 5),      /* CallId或者OpId或者Smi无效 */
    TAF_ERR_NUM_VALUE_INVALID                               = (TAF_ERR_CODE_BASE + 6),      /* 号码有误(号码value无效) */
    TAF_ERR_NUM_LEN_INVALID                                 = (TAF_ERR_CODE_BASE + 7),      /* 号码长度为0或者超出最大长度 */
    TAF_ERR_CAPABILITY_ERROR                                = (TAF_ERR_CODE_BASE + 8),      /* 终端能力不支持 */
    TAF_ERR_CLIENTID_NO_FREE                                = (TAF_ERR_CODE_BASE + 9),      /* 没有空闲ClientId，请求失败 */
    TAF_ERR_CALLBACK_FUNC_ERROR                             = (TAF_ERR_CODE_BASE + 10),     /* 回调函数错误 */
    TAF_ERR_MSG_DECODING_FAIL                               = (TAF_ERR_CODE_BASE + 11),     /* 消息解码失败 */
    TAF_ERR_TI_ALLOC_FAIL                                   = (TAF_ERR_CODE_BASE + 12),     /* TI分配失败 */
    TAF_ERR_TI_GET_FAIL                                     = (TAF_ERR_CODE_BASE + 13),     /* 获取Ti失败 */
    TAF_ERR_CMD_TYPE_ERROR                                  = (TAF_ERR_CODE_BASE + 14),     /* 命令类型错误 */
    TAF_ERR_MUX_LINK_EST_FAIL                               = (TAF_ERR_CODE_BASE + 15),     /* APP与TAF之间MUX链路建立失败 */
    TAF_ERR_USIM_SIM_CARD_NOTEXIST                          = (TAF_ERR_CODE_BASE + 16),     /* USIM卡不存在 */
    TAF_ERR_CLIENTID_NOT_EXIST                              = (TAF_ERR_CODE_BASE + 17),     /* ClientId不存在 */
    TAF_ERR_NEED_PIN1                                       = (TAF_ERR_CODE_BASE + 18),     /* 需要输入PIN1码 */
    TAF_ERR_NEED_PUK1                                       = (TAF_ERR_CODE_BASE + 19),     /* 需要输入PUK1 */
    TAF_ERR_USIM_SIM_INVALIDATION                           = (TAF_ERR_CODE_BASE + 20),     /* 无效的USIM/SIM卡 */
    TAF_ERR_SIM_BUSY                                        = (TAF_ERR_CODE_BASE + 21),     /* SIM卡忙 */
    TAF_ERR_SIM_LOCK                                        = (TAF_ERR_CODE_BASE + 22),     /* SIM卡锁卡 */
    TAF_ERR_SIM_INCORRECT_PASSWORD                          = (TAF_ERR_CODE_BASE + 23),     /* 不正确的密码 */
    TAF_ERR_SIM_FAIL                                        = (TAF_ERR_CODE_BASE + 24),     /* SIM卡操作失败 */
    TAF_ERR_NOT_READY                                       = (TAF_ERR_CODE_BASE + 25),     /* 开机未本地初始化完成，接收工具的切换FTM模式请求 */
    TAF_ERR_FILE_NOT_EXIST                                  = (TAF_ERR_CODE_BASE + 26),     /* OPL 文件不存在 */
    TAF_ERR_NO_NETWORK_SERVICE                              = (TAF_ERR_CODE_BASE + 27),     /* 无网络 */
    TAF_ERR_GET_CSQLVL_FAIL                                 = (TAF_ERR_CODE_BASE + 28),     /* 获取CSQLVL信息错误 */
    TAF_ERR_AT_ERROR                                        = (TAF_ERR_CODE_BASE + 29),     /* 输出AT_ERROR */
    TAF_ERR_CME_OPT_NOT_SUPPORTED                           = (TAF_ERR_CODE_BASE + 30),     /* 输出AT_CME_OPERATION_NOT_SUPPORTED */
    TAF_ERR_AT_CONNECT                                      = (TAF_ERR_CODE_BASE + 31),     /* 输出AT_CONNECT */
    TAF_ERR_USIM_SVR_OPLMN_LIST_INAVAILABLE                 = (TAF_ERR_CODE_BASE + 32),     /* 获取(U)SIM卡USIM_SVR_OPLMN_LIST服务失败 */
    TAF_ERR_FDN_CHECK_FAILURE                               = (TAF_ERR_CODE_BASE + 33),     /* FDN业务检查失败 */
    TAF_ERR_INTERNAL                                        = (TAF_ERR_CODE_BASE + 34),     /* 内部错误 */
    TAF_ERR_NET_SEL_MENU_DISABLE                            = (TAF_ERR_CODE_BASE + 36),     /* PLMN SEL菜单Disable */
    TAF_ERR_SYSCFG_CS_SERV_EXIST                            = (TAF_ERR_CODE_BASE + 37),     /* 设置syscfg时有CS业务存在 */
    TAF_ERR_NEED_PUK2                                       = (TAF_ERR_CODE_BASE + 38),     /* 需要输入PUK2 */
    TAF_ERR_USSD_NET_TIMEOUT                                = (TAF_ERR_CODE_BASE + 39),     /* USSD定时器超时 TAF_ERR_USSD_TIME_OUT => TAF_ERR_USSD_NET_TIMEOUT */
    TAF_ERR_BUSY_ON_USSD                                    = (TAF_ERR_CODE_BASE + 40),     /* 已经存在USSD业务 */
    TAF_ERR_BUSY_ON_SS                                      = (TAF_ERR_CODE_BASE + 41),     /* 已经存在SS业务 */
    TAF_ERR_USSD_USER_TIMEOUT                               = (TAF_ERR_CODE_BASE + 42),     /* USSD业务等待APP回复超时 */
    TAF_ERR_SS_NET_TIMEOUT                                  = (TAF_ERR_CODE_BASE + 43),     /* SS业务等待网络回复超时 */
    TAF_ERR_USSD_TERMINATED_BY_USER                         = (TAF_ERR_CODE_BASE + 44),     /* USSD业务被用户打断 */
    TAF_ERR_NO_SUCH_ELEMENT                                 = (TAF_ERR_CODE_BASE + 45),     /* 逻辑通道上没有对应的数据单元 */
    TAF_ERR_MISSING_RESOURCE                                = (TAF_ERR_CODE_BASE + 46),     /* 无剩余通道资源 */
    TAF_ERR_SS_DOMAIN_SELECTION_FAILURE                     = (TAF_ERR_CODE_BASE + 47),     /* 业务域选择失败 */
    TAF_ERR_SS_DOMAIN_SELECTION_TIMER_EXPIRED               = (TAF_ERR_CODE_BASE + 48),     /* 业务域选择缓存保护定时器超时 */
    TAF_ERR_SS_POWER_OFF                                    = (TAF_ERR_CODE_BASE + 49),     /* 业务域选择收到关机指示清除缓存 */
    TAF_ERR_PHY_INIT_FAILURE                                = (TAF_ERR_CODE_BASE + 50),     /* 物理层初始化失败 */
    TAF_ERR_UNSPECIFIED_ERROR                               = (TAF_ERR_CODE_BASE + 51),     /* 其他错误类型 */
    TAF_ERR_NO_RF                                           = (TAF_ERR_CODE_BASE + 52),     /* NO RF */

    TAF_ERR_IMS_NOT_SUPPORT                                 = (TAF_ERR_CODE_BASE + 53),     /* IMS不支持 */
    TAF_ERR_IMS_SERVICE_EXIST                               = (TAF_ERR_CODE_BASE + 54),     /* IMS服务存在 */
    TAF_ERR_IMS_VOICE_DOMAIN_PS_ONLY                        = (TAF_ERR_CODE_BASE + 55),     /* IMS语音优选域为PS_ONLY */
    TAF_ERR_IMS_STACK_TIMEOUT                               = (TAF_ERR_CODE_BASE + 56),     /* IMS协议栈超时 */

    TAF_ERR_1X_RAT_NOT_SUPPORTED                            = (TAF_ERR_CODE_BASE + 57),     /* 当前1X RAT不支持 */

    TAF_ERR_PHONE_MSG_UNMATCH                               = (TAF_ERR_PHONE_BASE + 1),     /*消息关系不匹配*/
    TAF_ERR_PHONE_ATTACH_FORBIDDEN                          = (TAF_ERR_PHONE_BASE + 2),     /*禁止ATTACH过程*/
    TAF_ERR_PHONE_DETACH_FORBIDDEN                          = (TAF_ERR_PHONE_BASE + 3),     /*禁止DETACH过程*/


    TAF_ERR_PB_NOT_INIT                                     = (TAF_ERR_PB_BASE + 1),        /* PB模块尚未初始化 */
    TAF_ERR_PB_MALLOC_FAIL                                  = (TAF_ERR_PB_BASE + 2),        /* 分配内存失败 */
    TAF_ERR_PB_WRONG_INDEX                                  = (TAF_ERR_PB_BASE + 3),        /* 错误的index */
    TAF_ERR_PB_WRONG_PARA                                   = (TAF_ERR_PB_BASE + 4),        /* 错误的输入参数 */
    TAF_ERR_PB_STORAGE_FULL                                 = (TAF_ERR_PB_BASE + 5),        /* 介质已满 */
    TAF_ERR_PB_STORAGE_OP_FAIL                              = (TAF_ERR_PB_BASE + 6),        /* 卡操作失败 */
    TAF_ERR_PB_NOT_FOUND                                    = (TAF_ERR_PB_BASE + 7),        /* 无匹配记录 */
    TAF_ERR_PB_DIAL_STRING_TOO_LONG                         = (TAF_ERR_PB_BASE + 8),        /* 输入的号码有错 */


    TAF_ERR_SAT_MALLOC_FAIL                                 = (TAF_ERR_SAT_BASE + 1),       /* 分配内存失败 */
    TAF_ERR_SAT_WRONG_PARA                                  = (TAF_ERR_SAT_BASE + 2),       /* 错误的输入参数 */
    TAF_ERR_SAT_STORAGE_OP_FAIL                             = (TAF_ERR_SAT_BASE + 3),       /* 卡操作失败 */
    TAF_ERR_SAT_STORAGE_OP_93_SW                            = (TAF_ERR_SAT_BASE + 4),       /* 93回复 */
    TAF_ERR_SAT_NO_MAIN_MENU                                = (TAF_ERR_SAT_BASE + 5),       /* 没有主菜单 */

    TAF_ERR_CODE_BUTT                                       = (0xFFFFFFFF)
};
typedef  VOS_UINT32  TAF_ERROR_CODE_ENUM_UINT32;

/* Added by s00217060 for 主动上报AT命令控制下移至C核, 2013-5-6, begin */
#ifndef TAF_SUCCESS
#define TAF_SUCCESS    TAF_ERR_NO_ERROR     /*函数执行成功*/
#endif
#ifndef TAF_FAILURE
#define TAF_FAILURE    TAF_ERR_ERROR        /*函数执行失败*/
#endif

typedef TAF_UINT8 TAF_PARA_TYPE;


#define TAF_PH_MS_CLASS_PARA             91


#define TAF_PH_IMSI_ID_PARA              98    /*+CIMI - 获取IMSI*/


#define TAF_PH_NETWORKNAMEFROMUSIM_PARA  105   /*^SPIN, 从USIM中获取当前运营商名字*/


#define TAF_PH_IDENTIFICATION_INFO_PARA  107
#define TAF_PH_CUR_FREQ                  108
#define TAF_PH_ICC_ID                    110
#define TAF_PH_CELL_RSCP_VALUE_PARA      111
#define TAF_PH_UE_RFPOWER_FREQ_PARA      112
#define TAF_PH_ICC_TYPE_PARA             114
#define TAF_PH_ICC_STATUS_PARA           115
#define TAF_PH_LOAD_DEFAULT              117
#define TAF_PH_PNN_PARA                  120
#define TAF_PH_OPL_PARA                  121


#define TAF_PH_CPNN_PARA                 125
#define TAF_PH_PNN_RANGE_PARA            126
#define TAF_PH_OPL_RANGE_PARA            127


#define TAF_PH_SIMLOCK_VALUE_PARA        (137)                                  /*^SIMLOCK=2获取数据卡的锁卡状态 */


#define TAF_TELE_PARA_BUTT               (142)


/* Modify by w00199382 for V7代码同步, 2012-04-07, End   */

/*内部使用的参数查询宏定义*/
#define TAF_MMA_AT_QUERY_PARA_BEGIN (TAF_TELE_PARA_BUTT + 1)/*137*/


/*获取手机漫游状态*/
#define  TAF_PH_ROAM_STATUS_PARA    (TAF_MMA_AT_QUERY_PARA_BEGIN + 1)/*138*/

/*获取手机所处域信息*/
#define  TAF_PH_DOMAIN_PARA         (TAF_PH_ROAM_STATUS_PARA + 1)/*139*/

/*GMR命令，获取mobile software revision, release date, release time*/
#define  TAF_PH_GMR_PARA            (TAF_PH_DOMAIN_PARA + 1)/*140*/

/*产品名称，GMM，CGMM使用*/
#define  TAF_PH_PRODUCT_NAME_PARA   (TAF_PH_GMR_PARA + 1)/*141*/


/*参数设置结果*/
typedef TAF_UINT8 TAF_PARA_SET_RESULT;
#define TAF_PARA_OK                            0  /*参数设置成功*/
#define TAF_PARA_SET_ERROR                     1  /*设置参数错误*/
#define TAF_PARA_WRITE_NVIM_ERROR              2  /*写NVIM失败*/
#define TAF_PARA_TYPE_NOT_SUPPORT              3  /*不支持的参数类型*/
#define TAF_PARA_CID_NOT_SUPPORT               4  /*CID取值超出支持范围*/
#define TAF_PARA_NOT_INCLUDE_ALL_OP_IE         5  /*参数设置非修改，未包含所有可选参数*/
#define TAF_PARA_IE_DECODE_ERROR               6  /*消息解码失败*/
#define TAF_PARA_IE_ENCODE_ERROR               7  /*消息编码失败*/
#define TAF_PARA_IE_VALUE_ERROR                8  /*参数取值错误*/
#define TAF_PARA_CMD_NOT_MATCH_PARA            9  /*无法对该参数执行操作*/
#define TAF_PARA_SIM_IS_BUSY                   10 /*SIM卡正忙*/
#define TAF_PARA_PDP_CONTEXT_NOT_DEFINED       11 /*PDP上下文未定义*/
#define TAF_PARA_SEC_PDP_CONTEXT_NOT_DEFINED   12 /*从属PDP上下文未定义*/
#define TAF_PARA_TFT_NOT_DEFINED               13 /*TFT未定义*/
#define TAF_PARA_QOS_NOT_DEFINED               14 /*QOS未定义*/
#define TAF_PARA_MIN_QOS_NOT_DEFINED           15 /*MIN QOS未定义*/
#define TAF_PARA_SPN_NO_EXIST                  16 /*spn文件不存在*/
#define TAF_PARA_ALLOC_MEM_FAIL                17 /*查询参数时,申请内存失败*/
#define TAF_PARA_NO_USIM_ERROR                 18 /*查询imsi时，USIM不存*/
#define TAF_PARA_AUTH_NOT_DEFINED              19 /*AUTH未定义*/
#define TAF_PARA_MEMORY_FULL                   20
#define TAF_PARA_INVALID_INDEX                 21
#define TAF_PARA_NDIS_AUTHDATA_NOT_DEFINED     22 /*NDIS AUTHDATA未定义*/
#define TAF_PARA_EPS_QOS_NOT_DEFINED           23 /* EPS QOS未定义 */
#define TAF_PARA_INVALID_PLMNID                24
#define TAF_PARA_DUPLICATE_PLMNINFO            25
#define TAF_PARA_UNSPECIFIED_ERROR             255 /*其他错误*/



/* 年，月，日，时，分，秒，均为BCD编码格式，
   高字节为10位数，低字节为个位数，即: 0x51 转为0x15,表示10进制数15
   时区为有符号整数，以15分钟为单位 */
typedef struct{
    VOS_UINT8                       ucYear;
    VOS_UINT8                       ucMonth;
    VOS_UINT8                       ucDay;
    VOS_UINT8                       ucHour;
    VOS_UINT8                       ucMinute;
    VOS_UINT8                       ucSecond;
    VOS_INT8                        cTimeZone;
    VOS_UINT8                       Reserved;
}TIME_ZONE_TIME_STRU;

/* 消息MMCMM_INFO_IND的结构体 */
typedef struct
{
    VOS_UINT8                       ucIeFlg;
    VOS_INT8                        cLocalTimeZone;
    VOS_UINT8                       ucDST;
    VOS_UINT8                       ucLSAID[3];
    VOS_UINT8                       aucReserve[2];
    TIME_ZONE_TIME_STRU             stUniversalTimeandLocalTimeZone;
}NAS_MM_INFO_IND_STRU;


#if ((VOS_OS_VER == VOS_WIN32) || (TAF_OS_VER == TAF_NUCLEUS))
#pragma pack()
#else
#pragma pack(0)
#endif

#ifdef __cplusplus
    #if __cplusplus
        }
    #endif
#endif

#endif /* TAF_TYPE_DEF_H */

