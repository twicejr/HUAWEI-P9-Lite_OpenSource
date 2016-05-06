/******************************************************************************

  Copyright(C)2008,Hisilicon Co. LTD.

 ******************************************************************************
  File Name       : LRrcGuRrcCommInterface.h
  Description     : LTE&GU RRC模块公共信息头文件
  History         :
      1.liutao 38432       2010-12-30   Draft Enact
	  2.wangyue 151278     2011-12-22 DTS2011121902767:L2G重选接口修改，增加能量值
******************************************************************************/

#ifndef __LRRC_GURRCCOMMINTERFACE_H__
#define __LRRC_GURRCCOMMINTERFACE_H__

#ifdef __cplusplus
#if __cplusplus
extern "C" {
#endif
#endif

/*****************************************************************************
  1 Include Headfile
*****************************************************************************/
#include  "vos.h"

/*****************************************************************************
  #pragma pack(*)    设置字节对齐方式
*****************************************************************************/
#if (VOS_OS_VER != VOS_WIN32)
#pragma pack(4)
#else
#pragma pack(push, 4)
#endif


/*****************************************************************************
  2 Macro
*****************************************************************************/
/* 3GPP 协议上规定最大EUTRAN频点数 */
#define LRRC_GURRC_LTE_ARFCN_MAX_NUM                        8

/* UE支持的EUTRAN频点的最大测量数目 */

/* UE支持的EUTRAN频点的最大测量数目 */
#define LRRC_GURRC_LTE_PHY_MAX_SUPPORT_CARRIER_NUM          8

/* begin: end for feature v700r500 */

/* EUTRAN 单个频点支持小区最大数目 */
#define LRRC_GURRC_MAX_LTE_CELL_PER_FREQ_NUM                32

/* EUTRAN 单个频点上支持的黑名单小区数目*/
#define LRRC_GURRC_BLACK_LIST_CELL_MAX_NUM                  16

/* 3GPP 协议上规定最大UTRAN频点数 */
#define LRRC_GURRC_UTRAN_ARFCN_MAX_NUM                      16

/* UE支持的UTRAN频点的最大测量数目 */
#define LRRC_GURRC_UTRAN_PHY_MAX_SUPPORT_CARRIER_NUM        3

/* UE支持的UTRAN频点的最大测量数目 */
#define LRRC_TRRC_PHY_MAX_SUPPORT_CARRIER_NUM               9

/* UTRAN 单个频点支持小区最大数目 */
#define LRRC_GURRC_MAX_UTRAN_CELL_PER_FREQ_NUM              32

/* 3GPP 协议上规定最大GERAN频点数 */
#define LRRC_GURRC_GERAN_ARFCN_MAX_NUM                      32

/* LUE 支持最大的BSIC VERFIED 小区个数*/
#define LRRC_GURRC_GERAN_CELL_FOR_BSIC_MAX_NUM              8

/* EUTRAN 支持的 GERAN 系统消息个数*/
#define LRRC_GURRC_GERAN_SYS_MAX_NUM                        10

/* EUTRAN 支持的 GERAN 系统消息最大长度 */
#define LRRC_GURRC_GERAN_SYS_MAX_LEN                        24

/* PLMN 搜索时，高质量PLMN 最大个数 */
#define LRRC_GURRC_MAX_HIGH_PLMN_NUM                        16

/* PLMN 搜索时，低质量PLMN 最大个数 */
#define LRRC_GURRC_MAX_LOW_PLMN_NUM                         16

/* EUTRAN中单个小区包含的最大PLMN 个数*/
#define LRRC_GURRC_PLMN_ID_MAX_NUM                          6

/* UTRAN UE 能力编码后最大长度*/
#define LRRC_WRRC_UE_CAP_UTRAN_MAX_LEN                      256

/* EUTRAN UE 能力编码后最大长度*/
#define LRRC_WRRC_UE_CAP_EUTRAN_MAX_LEN                     1024

/* GERAN CS UE 能力编码后最大长度*/
#define LRRC_GRR_UE_CAP_GEREN_CS_MAX_LEN                    128

/* GERAN PS UE 能力编码后最大长度*/
#define LRRC_GRR_UE_CAP_GEREN_PS_MAX_LEN                    128

/* L重定向时，包括的UTRAN CELL 最大个数 */
#define LRRC_WRRC_REDIR_CELL_MAX_MUN                        16
/* v7r2 code begin */
/* L重定向时，包括的UTRAN FREQ 最大个数 */
#define LRRC_TRRC_REDIR_FREQ_MAX_MUN                        6
/* v7r2 code end */

/* L重定向时，包括的UTRAN CELL 的系统消息最大长度 */
/*DTS2015052702134,add by l00195322,联通网络配置不合理，contanier太长，大于256了，修改为512+128*/
#define LRRC_WRRC_UTRAN_BCCH_CONTAINER_MAX_BYTE_LEN         640
/*DTS2015052702134,add by l00195322,联通网络配置不合理，contanier太长，大于256了，修改为512+128*/


/* L CellResel或者CCO到G时，如果目标G小区没有测量值，接口中设置的无效值 */
#define LRRC_GRR_INVALID_CELL_RXLEV_VALUE                   0x00FF

#define LRRC_WRRC_MAX_NUM_OF_PLMN_ID_LIST_2                 5

#define LRRC_GURRC_MAX_FORBLA_NUM                           (16)

/* bgs begin */
/* FORBID TA 最大个数 */
#define LRRC_GURRC_MAX_FORBTA_NUM                           (64)
/* bgs end */

/* EUTRAN 专有优先级最大个数 */
#define LRRC_GURRC_EUTRAN_DEDICATED_PRI_MAX_NUM             (64)

/* UTRAN 专有优先级最大个数 */
#define LRRC_GURRC_UTRAN_DEDICATED_PRI_MAX_NUM              (64)

/*****************************************************************************
  3 Massage Declare
*****************************************************************************/


/*****************************************************************************
  4 Enum
*****************************************************************************/

/*****************************************************************************
 枚举名    : LRRC_GURRC_MEAS_BAND_WIDTH_ENUM
 协议表格  :
 ASN.1描述 :
 枚举说明  : 带宽枚举(测量带宽)
*****************************************************************************/
enum LRRC_GURRC_MEAS_BAND_WIDTH_ENUM
{
    LRRC_GURRC_MEAS_BAND_WIDTH_6RB                          = 0,                /* 带宽为6RB   */
    LRRC_GURRC_MEAS_BAND_WIDTH_15RB                            ,                /* 带宽为15RB  */
    LRRC_GURRC_MEAS_BAND_WIDTH_25RB                            ,                /* 带宽为25RB  */
    LRRC_GURRC_MEAS_BAND_WIDTH_50RB                            ,                /* 带宽为50RB  */
    LRRC_GURRC_MEAS_BAND_WIDTH_75RB                            ,                /* 带宽为75RB  */
    LRRC_GURRC_MEAS_BAND_WIDTH_100RB                           ,                /* 带宽为100RB */

    LRRC_GURRC_MEAS_BAND_WIDTH_BUTT
};
typedef VOS_UINT16 LRRC_GURRC_MEAS_BAND_WIDTH_ENUM_UINT16;

/*****************************************************************************
 枚举名     :LRRC_GRR_BANDINDICATOR_ENUM
 协议表格  :
 ASN.1描述   :
 枚举说明 : 2G小区频带指示
*****************************************************************************/
enum LRRC_GRR_BANDINDICATOR_ENUM
{
    LRRC_GRR_BANDINDICATOR_DCS1800                          = 0,
    LRRC_GRR_BANDINDICATOR_PCS1900                             ,

    LRRC_GRR_BANDINDICATOR_BUTT
};
typedef VOS_UINT16    LRRC_GRR_BANDINDICATOR_ENUM_UINT16;

/*****************************************************************************
 枚举名    : LRRC_GURRC_CELL_CAMPEDON_TYPE_ENUM
 协议表格  :
 ASN.1描述   :
 枚举说明  : 小区驻留方式
*****************************************************************************/
enum LRRC_GURRC_CELL_CAMPEDON_TYPE_ENUM
{
    LRRC_GURRC_CELL_CAMPEDON_SUITABLE                       = 0,                /* 小区驻留在方式为suitable   */
    LRRC_GURRC_CELL_CAMPEDON_ANY_CELL                          ,                /* 小区驻留在方式为acceptable */

    LRRC_GURRC_CELL_CAMPEDON_TYPE_BUTT
};

typedef VOS_UINT8 LRRC_GURRC_CELL_CAMPEDON_TYPE_ENUM_UINT8;

/*****************************************************************************
 枚举名    : LRRC_GRR_RELALL_REASON_ENUM_UINT8
 协议表格  :
 ASN.1描述   :
 枚举说明  : LRRC释放原因
*****************************************************************************/
enum LRRC_GRR_RELALL_REASON_ENUM
{
    LRRC_GRR_REL_REASON_OTHER                             = 0,
    LRRC_GRR_REL_REASON_TO_GSM                               ,                  /* LTE释放的原因为LTE切换或者CCO到GSM */

    LRRC_GRR_REL_REASON_BUTT
};
typedef VOS_UINT8 LRRC_GRR_RELALL_REASON_ENUM_UINT8;


/*****************************************************************************
 枚举名     :LRRC_GURRC_VALID_FLAG_ENUM
 协议表格  :
 ASN.1描述   :
 枚举说明 : 通用是否存在标志
*****************************************************************************/
enum LRRC_GURRC_VALID_FLAG_ENUM
{
    LRRC_GURRC_FLAG_INVALID                                 = 0,
    LRRC_GURRC_FLAG_VALID                                      ,

    LRRC_GURRC_FLAG_BUTT
};
typedef VOS_UINT8    LRRC_GURRC_VALID_FLAG_ENUM_UINT8;

/*****************************************************************************
 枚举名    : LRRC_GURRC_CELL_RESEL_RESULT_ENUM
 协议表格  :
	 44060-8.4.2
	 Access is denied in the new cell (i.e., the mobile station receives an
	 IMMEDIATE ASSIGNMENT REJECT, a PACKET ASSIGNMENT REJECT or, in a UTRAN
	 cell, an RRC CONNECTION REJECT message or fails to establish an RRC
	 connection in an E-UTRAN cell as specified in 3GPP TS 36.331).
	 Cause: "Immediate Assign Reject or Packet Access Reject on target cell";
 ASN.1描述 :
 枚举说明  : GU与LTE之间CELL RESEL结果
*****************************************************************************/
enum LRRC_GURRC_CELL_RESEL_RESULT_ENUM
{
    LRRC_GURRC_CELL_RESEL_SUCC                              = 0,
    LRRC_GURRC_CELL_RESEL_SIB_RCV_FAIL                         ,                /* 系统消息接收失败 */
    LRRC_GURRC_CELL_RESEL_CELL_BARRED                          ,                /* CELL BARRED */
    LRRC_GURRC_CELL_RESEL_CELL_FORBID                          ,                /* CELL 被 FORBID*/
    LRRC_GURRC_CELL_RESEL_NOT_EPLMNS                           ,                /* CELL携带的PLMN信息没有属于RPLMN和EPLMNS */
    LRRC_GURRC_CELL_RESEL_ACCESS                               ,                /* CELL ACCESS 受限 */
    LRRC_GURRC_CELL_RESEL_UNSPECIFIC                           ,                /* 其他未定义的错误 */
    LRRC_GURRC_CELL_RESEL_CONNECTION_REJECT                    ,                /* 立即指派被拒或连接被拒，该原因值只用于CCO流程 */

    LRRC_GURRC_CELL_RESEL_S_OR_C1_CHECK_FAIL                   ,
    LRRC_GURRC_CELL_RESEL_ARFCN_NOT_SUPPORT                    ,

    LRRC_GURRC_CELL_RESEL_RESULT_BUTT
};

typedef VOS_UINT32 LRRC_GURRC_CELL_RESEL_RESULT_ENUM_UINT32;

/* CCO失败原因同 CEL RESEL 流程 */
typedef VOS_UINT32 LRRC_GURRC_CCO_RESULT_ENUM_UINT32;

/*****************************************************************************
 枚举名    : LRRC_GURRC_HANDOVER_RESULT_ENUM
 协议表格  :
 ASN.1描述 :
 枚举说明  : GU与LTE之间HANDOVER 结果
*****************************************************************************/
enum LRRC_GURRC_HANDOVER_RESULT_ENUM
{
    LRRC_GURRC_HANDOVER_RESULT_SUCC                         = 0,
    LRRC_GURRC_HANDOVER_RESULT_CONF_UNACCEPTABLE               ,                /* 切换配置不支持 */
    LRRC_GURRC_HANDOVER_RESULT_PHY_CHANNEL_FAIL                ,                /* physical channel failure  */
    LRRC_GURRC_HANDOVER_RESULT_IRAT_PROTOCOL_ERR               ,                /* inter-RAT protocol error */
    LRRC_GURRC_HANDOVER_RESULT_UNSPECIFIC,

    LRRC_GURRC_HANDOVER_RESULT_ARFCN_NOT_SUPPORT               ,

    LRRC_GURRC_HANDOVER_RESULT_BUTT
};

typedef VOS_UINT32 LRRC_GURRC_HANDOVER_RESULT_ENUM_UINT32;

/*****************************************************************************
 枚举名    : LRRC_GURRC_CELL_RESEL_RESULT_ENUM
 协议表格  :
 ASN.1描述 :
 枚举说明  : GU与LTE之间REDIRECTED结果
*****************************************************************************/
enum LRRC_GURRC_REDIRECTED_RESULT_ENUM
{
    LRRC_GURRC_REDIRECTED_SUCC                              = 0,
    LRRC_GURRC_REDIRECTED_FAIL                                 ,

    LRRC_GURRC_REDIRECTED_ARFCN_NOT_SUPPORT                    ,

    LRRC_GURRC_REDIRECTED_RESULT_BUTT
};

typedef VOS_UINT32 LRRC_GURRC_REDIRECTED_RESULT_ENUM_UINT32;

/*****************************************************************************
 枚举名    : LRRC_GRR_SYS_TYPE_ENUM
 协议表格  :
 ASN.1描述 :
 枚举说明  : CCO等流程中，指示是否存在GERAN系统消息
*****************************************************************************/
enum LRRC_GRR_SYS_TYPE_ENUM
{
    LRRC_GRR_SYS_TYPE_NOT_EXIST                             = 0,
    LRRC_GRR_SYS_TYPE_SI                                       ,
    LRRC_GRR_SYS_TYPE_PSI                                      ,

    LRRC_GRR_SYS_TYPE_BUTT
};

typedef VOS_UINT8   LRRC_GRR_SYS_TYPE_ENUM_UINT8;

/*****************************************************************************
 枚举名    : LRRC_GURRC_SET_DSP_POWER_CMD_ENUM
 协议表格  :
 ASN.1描述 :
 枚举说明  : GU与LTE之间设置DSP省电模式命令
*****************************************************************************/
enum LRRC_GURRC_SET_DSP_POWER_CMD_ENUM
{
    LRRC_GURRC_SET_DSP_POWER_OPEN                           = 0,
    LRRC_GURRC_SET_DSP_POWER_CLOSE                             ,

    LRRC_GURRC_SET_DSP_POWER_TYPE_BUTT
};

typedef VOS_UINT32 LRRC_GURRC_SET_DSP_POWER_CMD_ENUM_UINT32;

/*****************************************************************************
 枚举名    : LRRC_GURRC_SET_DSP_POWER_RESULT_ENUM
 协议表格  :
 ASN.1描述 :
 枚举说明  : GU与LTE之间设置DSP省电模式结果
*****************************************************************************/
enum LRRC_GURRC_SET_DSP_POWER_RESULT_ENUM
{
    LRRC_GURRC_SET_DSP_POWER_SUCC                           = 0,
    LRRC_GURRC_SET_DSP_POWER_FAIL                              ,

    LRRC_GURRC_SET_DSP_POWER_RESULT_BUTT
};

typedef VOS_UINT32 LRRC_GURRC_SET_DSP_POWER_RESULT_ENUM_UINT32;

/*****************************************************************************
 枚举名    : LRRC_WRRC_PLMN_SEARCH_RESULT_ENUM
 协议表格  :
 ASN.1描述 :
 枚举说明  : LTE PLMN搜索结果
*****************************************************************************/
enum LRRC_WRRC_PLMN_SEARCH_RESULT_ENUM
{
    LRRC_WRRC_PLMN_SEARCH_SUCC                              = 0,
    LRRC_WRRC_PLMN_SEARCH_FAIL                                 ,

    LRRC_WRRC_PLMN_SEARCH_RESULT_BUTT
};

typedef VOS_UINT16 LRRC_WRRC_PLMN_SEARCH_RESULT_ENUM_UINT16;

/*****************************************************************************
 枚举名    : LRRC_GURRC_MEAS_CMD_ENUM
 协议表格  :
 ASN.1描述 :
 枚举说明  : GU与LTE之间MEAS 命令
*****************************************************************************/
enum LRRC_GURRC_MEAS_CMD_ENUM
{
    LRRC_GURRC_MEAS_CMD_RELEASE                             = 0,
    LRRC_GURRC_MEAS_CMD_SETUP                                  ,

    LRRC_GURRC_MEAS_CMD_BUTT
};

typedef VOS_UINT16 LRRC_GURRC_MEAS_CMD_ENUM_UINT16;

/*****************************************************************************
 枚举名    : LRRC_GURRC_MEAS_RESULT_ENUM
 协议表格  :
 ASN.1描述 :
 枚举说明  : GU与LTE之间MEAS CMD 结果
*****************************************************************************/
enum LRRC_GURRC_MEAS_RESULT_ENUM
{
    LRRC_GURRC_MEAS_RESULT_SUCC                             = 0,
    LRRC_GURRC_MEAS_RESULT_FAIL                                ,

    LRRC_GURRC_MEAS_RESULT_ARFCN_NOT_SUPPORT                   ,

    LRRC_GURRC_MEAS_RESULT_BUTT
};

typedef VOS_UINT32  LRRC_GURRC_MEAS_RESULT_ENUM_UINT32;

/*****************************************************************************
 枚举名    : LRRC_GURRC_GET_UECAP_RESULT_ENUM
 协议表格  :
 ASN.1描述 :
 枚举说明  : GU与LTE之间UE CAP获取结果
*****************************************************************************/
enum LRRC_GURRC_GET_UECAP_RESULT_ENUM
{
    LRRC_GURRC_GET_UECAP_SUCC                               = 0,
    LRRC_GURRC_GET_UECAP_FAIL                                  ,

    LRRC_GURRC_GET_UECAP_RESULT_BUTT
};

typedef VOS_UINT16 LRRC_GURRC_GET_UECAP_RESULT_ENUM_UINT16;

/*****************************************************************************
 枚举名    : LRRC_GURRC_MEAS_IRAT_TYPE_ENUM
 协议表格  :
 ASN.1描述 :
 枚举说明  : GU与LTE之间IRAT类型
*****************************************************************************/
enum LRRC_GURRC_MEAS_IRAT_TYPE_ENUM
{
    LRRC_GURRC_MEAS_IRAT_TYPE_GERAN                         = 0,
    LRRC_GURRC_MEAS_IRAT_TYPE_UTRAN                            ,

    LRRC_GURRC_MEAS_IRAT_TYPE_BUTT
};

typedef VOS_UINT16 LRRC_GURRC_MEAS_IRAT_TYPE_ENUM_UINT16;

/*****************************************************************************
 枚举名    : LRRC_WRRC_STATE_TYPE_ENUM
 协议表格  :
 ASN.1描述 :
 枚举说明  : WRRC当前的状态类型，用于区分连接态测量请求类型
                            CELL_PCH/URA_PCH: WRRC指示ERRC 启动IDLE态测量
                            CELL_FACH/CELL_DCH: WRRC指示ERRC 启动连接态测量
*****************************************************************************/
enum LRRC_WRRC_STATE_TYPE_ENUM
{
    LRRC_WRRC_STATE_TYPE_CELL_PCH                           = 0,
    LRRC_WRRC_STATE_TYPE_URA_PCH                               ,
    LRRC_WRRC_STATE_TYPE_CELL_FACH                             ,
    LRRC_WRRC_STATE_TYPE_CELL_DCH                              ,

    LRRC_WRRC_STATE_TYPE_BUTT
};

typedef VOS_UINT16 LRRC_WRRC_STATE_TYPE_ENUM_UINT16;

/*****************************************************************************
 枚举名    : LRRC_GURRC_VERIFY_TIME_INDEX_ENUM
 协议表格  :
 ASN.1描述 :
 枚举说明  : LRRC通知GURRC，GSM BSIC初始确认和重确认的时间索引

 连接态索引取值如下:

    index  Number of carriers  Tidentify,gsm  Treconfirm,gsm  Gap configuration
            other than GSM         (ms)            (ms)
   -----------------------------------------------------------------------------
     0            0               2160           1920
     1            1               5280           5040
     2            2               5280           5040            40ms (ID 0)
     3            3               19440          13320
     4            4               31680          29280
     5            5               31680          29280
   -----------------------------------------------------------------------------
     6            0               5280           5040
     7            1               21760          17280           80ms (ID 1)
     8            2               31680          29280

空闲态索引取值如下:

    index  DRX cycle length  Tidentify,gsm
                 (s)              (ms)
   ------------------------------------------
     0           0.32             360
     1           0.64             360
     2           1.28             180
     3           2.56             180

*****************************************************************************/

enum LRRC_GRR_VERIFY_TIME_INDEX_ENUM
{
    LRRC_GRR_VERIFY_TIME_INDEX_0                          = 0,
    LRRC_GRR_VERIFY_TIME_INDEX_1                             ,
    LRRC_GRR_VERIFY_TIME_INDEX_2                             ,
    LRRC_GRR_VERIFY_TIME_INDEX_3                             ,
    LRRC_GRR_VERIFY_TIME_INDEX_4                             ,
    LRRC_GRR_VERIFY_TIME_INDEX_5                             ,
    LRRC_GRR_VERIFY_TIME_INDEX_6                             ,
    LRRC_GRR_VERIFY_TIME_INDEX_7                             ,
    LRRC_GRR_VERIFY_TIME_INDEX_8                             ,

    LRRC_GRR_VERIFY_TIME_INDEX_BUTT
};

typedef VOS_UINT16 LRRC_GRR_VERIFY_TIME_INDEX_ENUM_UINT16;

/*****************************************************************************
 枚举名    : LRRC_GURRC_LOAD_DSP_RESULT_ENUM
 协议表格  :
 ASN.1描述 :
 枚举说明  : LTE加载WDSP结果
*****************************************************************************/
enum LRRC_GURRC_LOAD_DSP_RESULT_ENUM
{
    LRRC_GURRC_LOAD_DSP_RESULT_SUCC                         = 0,
    LRRC_GURRC_LOAD_DSP_RESULT_FAIL                            ,

    LRRC_GURRC_LOAD_DSP_RESULT_BUTT
};

typedef VOS_UINT32 LRRC_GURRC_LOAD_DSP_RESULT_ENUM_UINT32;

/*****************************************************************************
 枚举名    : LRRC_GURRC_GET_CGI_RESULT_ENUM
 协议表格  :
 ASN.1描述 :
 枚举说明  : GU与LTE之间CGI获取结果
*****************************************************************************/
enum LRRC_GURRC_GET_CGI_RESULT_ENUM
{
    LRRC_GURRC_GET_CGI_RESULT_SUCC                          = 0,
    LRRC_GURRC_GET_CGI_RESULT_FAIL                             ,

    LRRC_GURRC_GET_CGI_RESULT_BUTT
};

typedef VOS_UINT32 LRRC_GURRC_GET_CGI_RESULT_ENUM_UINT32;

/*****************************************************************************
 枚举名    : LRRC_GURRC_BG_SEARCH_RESULT_ENUM
 协议表格  :
 ASN.1描述 :
 枚举说明  : GU与LTE之间BG搜索结果
*****************************************************************************/
enum LRRC_GURRC_BG_SEARCH_RESULT_ENUM
{
    LRRC_GURRC_BG_SEARCH_RESULT_SUCC                        = 0,
    LRRC_GURRC_BG_SEARCH_RESULT_FAIL                           ,
    LRRC_GURRC_BG_SEARCH_RESULT_ABNORMAL                       ,

    LRRC_GURRC_BG_SEARCH_RESULT_BUTT
};

typedef VOS_UINT16 LRRC_GURRC_BG_SEARCH_RESULT_ENUM_UINT16;

/*****************************************************************************
 结构名    : LRRC_GURRC_SEARCH_TYPE_ENUM
 协议表格  :
 ASN.1描述 :
 结构说明  : 指示搜索类型，是BG还是PLMN LIST
*****************************************************************************/
enum LRRC_GURRC_SEARCH_TYPE_ENUM
{
    LRRC_GURRC_SEARCH_TYPE_BG                 = 0,                                    /* 通知做背景搜 */
    LRRC_GURRC_SEARCH_TYPE_PLMN_LIST             ,                                    /* 通知做PLMN LIST搜  */
    LRRC_GURRC_SEARCH_TYPE_BG_HIGH_RAT           ,
    LRRC_GURRC_SEARCH_TYPE_BUTT
};
typedef VOS_UINT8 LRRC_GURRC_SEARCH_TYPE_ENUM_UINT8;

/* CMCC-BEGIN */
/*****************************************************************************
 枚举名    : LRRC_GURRC_REDIR_TYPE_ENUM
 协议表格  :
 ASN.1描述 :
 枚举说明  : 重定向类型，包括网络控制的、UE自主执行的
*****************************************************************************/
enum LRRC_GURRC_REDIR_TYPE_ENUM
{
    LRRC_GURRC_REDIR_TYPE_UE_AUTO                         = 0,
    LRRC_GURRC_REDIR_TYPE_NET_CTL                            ,
    LRRC_GURRC_REDIR_TYPE_BUTT
};

typedef VOS_UINT8 LRRC_GURRC_REDIR_TYPE_ENUM_UINT8;
/* CMCC-END */


/*****************************************************************************
  5 STRUCT
*****************************************************************************/
/*****************************************************************************
 结构名    :LRRC_GRR_BSIC_INFO_STRU
 协议表格  :
 ASN.1描述 :
 结构说明  :CELL BAIC Info，协议36331 6.3.4
            usNcc(GSM Network Colour Code)  正常范围:(0..7), 8 表示无效值
            usBcc(GSM Base Station Colour Code)  正常范围:(0..7) , 8 表示无效值
*****************************************************************************/
typedef struct
{
    VOS_UINT16                                              usNcc;
    VOS_UINT16                                              usBcc;
}LRRC_GRR_BSIC_INFO_STRU;

/*****************************************************************************
 结构名     :LRRC_GURRC_LTE_PRI_INFO_STRU
 协议表格  :
 ASN.1描述   :
 结构说明  :LTE优先级信息数据结构
*****************************************************************************/
typedef struct
{
    VOS_UINT16                                              usArfcn;

    /* 取值范围0~9,0表示优先级最低，9表示优先级最高，其中1~8对应协议上的0~7 */
    VOS_UINT8                                               ucCellReselectionPriority;
    VOS_UINT8                                               aucReserved[1];
}LRRC_GURRC_LTE_PRI_INFO_STRU;

/*****************************************************************************
 结构名     :LRRC_GURRC_LTE_DEDICATED_PRI_INFO_STRU
 协议表格  :
 ASN.1描述   :
 结构说明  :LTE专有优先级信息数据结构
*****************************************************************************/
typedef struct
{
    VOS_UINT32                                              ulArfcnNum;
    LRRC_GURRC_LTE_PRI_INFO_STRU                            astLteDPriInfo[LRRC_GURRC_EUTRAN_DEDICATED_PRI_MAX_NUM];
}LRRC_GURRC_LTE_DEDICATED_PRI_INFO_STRU;

/*****************************************************************************
 结构名     :LRRC_GURRC_UTRAN_PRI_INFO_STRU
 协议表格  :
 ASN.1描述   :
 结构说明  :UTRAN优先级信息数据结构
*****************************************************************************/
typedef struct
{
    VOS_UINT16                                              usArfcn;

    /* 取值范围0~9,0表示优先级最低，9表示优先级最高，其中1~8对应协议上的0~7 */
    VOS_UINT8                                               ucCellReselectionPriority;
    VOS_UINT8                                               aucReserved[1];
}LRRC_GURRC_UTRAN_PRI_INFO_STRU;

/*****************************************************************************
 结构名     :LRRC_GURRC_UTRAN_DEDICATED_PRI_INFO_STRU
 协议表格  :
 ASN.1描述   :
 结构说明  :UTRAN专有优先级信息数据结构
*****************************************************************************/
typedef struct
{
    VOS_UINT32                                              ulArfcnNum;
    LRRC_GURRC_UTRAN_PRI_INFO_STRU                          astUtranDPriInfo[LRRC_GURRC_UTRAN_DEDICATED_PRI_MAX_NUM];
}LRRC_GURRC_UTRAN_DEDICATED_PRI_INFO_STRU;

/*****************************************************************************
 结构名     :LRRC_GURRC_GERAN_PRI_INFO_STRU
 协议表格  :
 ASN.1描述   :
 结构说明  :2G优先级信息数据结构
*****************************************************************************/
typedef struct
{
    VOS_UINT16                                              usArfcn;
    LRRC_GRR_BANDINDICATOR_ENUM_UINT16                      enBandInd;

    /* 取值范围0~9,0表示优先级最低，9表示优先级最高，其中1~8对应协议上的0~7 */
    VOS_UINT8                                               ucCellReselectionPriority;
    VOS_UINT8                                               aucReserved[3];
}LRRC_GURRC_GERAN_PRI_INFO_STRU;

/*****************************************************************************
 结构名     :LRRC_GURRC_GERAN_DEDICATED_PRI_INFO_STRU
 协议表格  :
 ASN.1描述   :
 结构说明  :2G专有优先级信息数据结构
*****************************************************************************/
typedef struct
{
    VOS_UINT32                                              ulArfcnNum;
    LRRC_GURRC_GERAN_PRI_INFO_STRU                          astGeranDPriInfo[LRRC_GURRC_GERAN_ARFCN_MAX_NUM];
}LRRC_GURRC_GERAN_DEDICATED_PRI_INFO_STRU;

/*****************************************************************************
 结构名     :LRRC_GURRC_DEDICATED_PRI_INFO_STRU
 协议表格  :
 ASN.1描述   :
 结构说明  :专有优先级信息数据结构
*****************************************************************************/
typedef struct
{
    /**************************************************************************
     bitLteDPriInfoPresent: 表示stLteDPriInfo是否有效，1表示有效，0表示无效
     bitUtranDPriInfoPresent: 表示stUtranDPriInfo是否有效，1表示有效，0表示无效
     bitGeranDPriInfoPresent: 表示stGeranDPriInfo是否有效，1表示有效，0表示无效
     bitDPriTimerPresent: 表示ulTimerValue是否有效，1表示有效，0表示无效
    **************************************************************************/

    VOS_UINT32                                              bitLteDPriInfoPresent  : 1;
    VOS_UINT32                                              bitUtranDPriInfoPresent: 1;
    VOS_UINT32                                              bitGeranDPriInfoPresent: 1;
    VOS_UINT32                                              bitDPriTimerPresent    : 1;  /* bit为0时表示无限时长 */
    VOS_UINT32                                              bitSpare               : 28;

    /* EUTRAN 频点优先级信息 */
    LRRC_GURRC_LTE_DEDICATED_PRI_INFO_STRU                  stLteDPriInfo;

    /* URTAN 频点优先级信息 */
    LRRC_GURRC_UTRAN_DEDICATED_PRI_INFO_STRU                stUtranDPriInfo;

    /* GSM 频点优先级信息 */
    LRRC_GURRC_GERAN_DEDICATED_PRI_INFO_STRU                stGeranDPriInfo;

    /* T3230,T322 ,T320定时器实际剩余时长，单位：毫秒,
            如果T3230,T322 ,T320定时器不存在，表示该数据无限大 */
    VOS_UINT32                                              ulTimerValue;
}LRRC_GURRC_DEDICATED_PRI_INFO_STRU;

/*****************************************************************************
 结构名     :LRRC_GURRC_PLMN_ID_INFO_STRU
 协议表格  :
 ASN.1描述   :
 结构说明  :PLMN信息
    MCC, Mobile country code (aucPlmnId[0], aucPlmnId[1] bits 1 to 4)
    MNC, Mobile network code (aucPlmnId[2], aucPlmnId[1] bits 5 to 8).

    The coding of this field is the responsibility of each administration but BCD
    coding shall be used. The MNC shall consist of 2 or 3 digits. For PCS 1900 for NA,
    Federal regulation mandates that a 3-digit MNC shall be used. However a network
    operator may decide to use only two digits in the MNC over the radio interface.
    In this case, bits 5 to 8 of octet 4 shall be coded as "1111". Mobile equipment
    shall accept MNC coded in such a way.

    ---------------------------------------------------------------------------
                 ||(BIT8)|(BIT7)|(BIT6)|(BIT5)|(BIT4)|(BIT3)|(BIT2)|(BIT1)
    ---------------------------------------------------------------------------
    aucPlmnId[0] ||    MCC digit 2            |           MCC digit 1
    ---------------------------------------------------------------------------
    aucPlmnId[1] ||    MNC digit 3            |           MCC digit 3
    ---------------------------------------------------------------------------
    aucPlmnId[2] ||    MNC digit 2            |           MNC digit 1
    ---------------------------------------------------------------------------

*****************************************************************************/
typedef struct
{
    VOS_UINT8                                               aucPlmnId[3];
    VOS_UINT8                                               aucReserved[1];
}LRRC_GURRC_PLMN_ID_INFO_STRU;

/*****************************************************************************
 结构名     :LRRC_GURRC_PLMN_ID_INFO_LIST_STRU
 协议表格  :
 ASN.1描述   :
 结构说明  :系统消息中携带的PLMN信息
*****************************************************************************/
typedef struct
{
    VOS_UINT32                                              ulPlmnIdNum;
    LRRC_GURRC_PLMN_ID_INFO_STRU                            astPlmnIdInfo[LRRC_GURRC_PLMN_ID_MAX_NUM];
}LRRC_GURRC_PLMN_ID_INFO_LIST_STRU;

/*****************************************************************************
 结构名     :LRRC_GRR_GERAN_CELL_INFO_STRU
 协议表格  :
 ASN.1描述   :
 结构说明  :2G小区信息
*****************************************************************************/
typedef struct
{
    VOS_UINT16                                              usArfcn;
    LRRC_GRR_BANDINDICATOR_ENUM_UINT16                      enBandInd;
    LRRC_GRR_BSIC_INFO_STRU                                 stBsic;
}LRRC_GRR_GERAN_CELL_INFO_STRU;

/*****************************************************************************
 结构名    : LRRC_GRR_SAVE_GERAN_CELL_INFO_STRU
 协议表格  :
 ASN.1描述 :
 结构说明  : LRRC发给GRR连接态下测量的GERAN CELL 相关信息
*****************************************************************************/
typedef struct
{
    LRRC_GRR_GERAN_CELL_INFO_STRU                           stGeranCellInfo;

    /* G目标小区测量电平值,负数形式。如果无法获取，填为约定的无效值。HO时不使用。*/
    VOS_INT16                                               sGeranCellRxlev;

    VOS_UINT8                                               aucReserved[1];

    LRRC_GURRC_VALID_FLAG_ENUM_UINT8                        enFNOffsetTAPresent; /* G小区定时信息, 0: 表示不存在，1 表示存在*/
    VOS_INT32                                               lFNOffset;
    VOS_UINT32                                              ulTimeAlignmt;
}LRRC_GRR_SAVE_GERAN_CELL_INFO_STRU;

/*****************************************************************************
 结构名    : LRRC_GRR_SAVE_GERAN_CELL_INFO_LIST_STRU
 协议表格  :
 ASN.1描述 :
 结构说明  : LRRC发给GRR连接态下测量的GERAN CELL 相关信息列表，只携带已经验证
             成功的G小区相关信息
*****************************************************************************/
typedef struct
{
    /* GSM小区个数 */
    VOS_UINT32                                              ulGsmCellNum;
    LRRC_GRR_SAVE_GERAN_CELL_INFO_STRU                      astRrcSaveCellInfoForGas[LRRC_GURRC_GERAN_CELL_FOR_BSIC_MAX_NUM];
}LRRC_GRR_SAVE_GERAN_CELL_INFO_LIST_STRU;

/*****************************************************************************
 结构名     :GURRC_LRRC_EUTRAN_INFO_STRU
 协议表格  :
 ASN.1描述   :
 结构说明  :EUTRAN 频点信息
*****************************************************************************/
typedef struct
{
   VOS_UINT16                                               usArfcn;
   LRRC_GURRC_MEAS_BAND_WIDTH_ENUM_UINT16                   enMeasband;         /*  空口不携带,填写默认值 0 */

   VOS_UINT8                                                aucReserved[3];

   /* 空口消息中携带的每个频点对应的黑名单信息*/
   VOS_UINT8                                                ucBlackListCnt;
   VOS_UINT16                                               ausBlackCellidList[LRRC_GURRC_BLACK_LIST_CELL_MAX_NUM];
}GURRC_LRRC_EUTRAN_INFO_STRU;

/*****************************************************************************
 结构名     :GURRC_LRRC_EUTRAN_INFO_LIST_STRU
 协议表格  :
 ASN.1描述   :
 结构说明  :EUTRAN 频点信息列表
*****************************************************************************/
typedef struct
{
   /* 需要测量的频点个数 */
   VOS_UINT16                                               usArfcnNum;

   /****************************************************************************
   频点信息中高优先级频点个数。如果usArfcnNum =  usHighPriNum，
   表示仅仅只有高优先级频点，或当前状态不区分优先级
   astEutranInfo存放顺序为:高优先级信息 -> 中优先级信息 -> 低优先级信息
   ****************************************************************************/
   VOS_UINT16                                               usHighPriNum;
   GURRC_LRRC_EUTRAN_INFO_STRU                              astEutranInfo[LRRC_GURRC_LTE_PHY_MAX_SUPPORT_CARRIER_NUM];
}GURRC_LRRC_EUTRAN_INFO_LIST_STRU;

/*****************************************************************************
 结构名    : LRRC_GURRC_EUTRAN_CELL_MEAS_RESULT_STRU
 协议表格  :
 ASN.1描述 :
 结构说明  : 小区测量结果
*****************************************************************************/
typedef struct
{
    VOS_UINT16                                              usCellId;
    VOS_INT16                                               sRsrp;              /* RSRP测量值,取值范围[-141*8,-44*8]， 单位:dBm，精度 1/8  */
    VOS_INT16                                               sRsrq;              /* RSRQ测量值 ,取值范围[-40*4，-6*4]， 单位:dB， 精度 1/8  */
    VOS_INT16                                               sRssi;              /* RSSI测量值 ,取值范围[-110*8,-20*8], 单位:dBm，精度 1/8  */
}LRRC_GURRC_EUTRAN_CELL_MEAS_RESULT_STRU;

/*****************************************************************************
 结构名    : LRRC_GURRC_SINGLE_EUTRAN_FREQ_MEAS_RESULT_STRU
 协议表格  :
 ASN.1描述 :
 结构说明  : 单个LTE 频点小区测量结果
*****************************************************************************/
typedef struct
{
    VOS_UINT16                                              usArfcn;
    VOS_UINT16                                              usArfcnCellNum;
    LRRC_GURRC_EUTRAN_CELL_MEAS_RESULT_STRU                 astInterFreqMeasResult[LRRC_GURRC_MAX_LTE_CELL_PER_FREQ_NUM];
}LRRC_GURRC_SINGLE_EUTRAN_FREQ_MEAS_RESULT_STRU;

/*****************************************************************************
 结构名     :LRRC_GURRC_MEAS_EUTRAN_RESULT_STRU
 协议表格  :
 ASN.1描述   :
 结构说明  :EUTRAN 测量信息
*****************************************************************************/
typedef struct
{
   /* 已经测量到数据的频点数据 */
   VOS_UINT16                                               usArfcnNum;
   VOS_UINT8                                                aucReserved[2];

   LRRC_GURRC_SINGLE_EUTRAN_FREQ_MEAS_RESULT_STRU           astEutranMeasResultInfo[LRRC_GURRC_LTE_PHY_MAX_SUPPORT_CARRIER_NUM];
}LRRC_GURRC_MEAS_EUTRAN_RESULT_STRU;

/*****************************************************************************
 结构名    :    LRRC_GURRC_CELL_GLOBAL_ID_STRU
 协议表格  :
 ASN.1描述   :
 结构说明  :  UTRAN/EUTRAN CELL GLOBAL ID信息
*****************************************************************************/
typedef struct
{
    LRRC_GURRC_PLMN_ID_INFO_STRU                            stPlmnId;
    VOS_UINT32                                              ulCellId;
}LRRC_GURRC_CELL_GLOBAL_ID_STRU;

/*****************************************************************************
 结构名     :LRRC_GURRC_FORB_LA_STRU
 协议表格  :
 ASN.1描述   :
 结构说明  :

*****************************************************************************/
typedef struct
{
    LRRC_GURRC_PLMN_ID_INFO_STRU                 PlmnId;                        /* PlMN标识       */
    VOS_UINT32                                   ulForbLac;                     /* 禁止注册区信息 */
}LRRC_GURRC_FORB_LA_STRU;

/*****************************************************************************
 结构名     :LRRC_GURRC_UTRAN_CELL_STRU
 协议表格  :
 ASN.1描述   :
 结构说明  :GERAN异系统信息
*****************************************************************************/
typedef struct
{
   VOS_UINT16                                               usArfcn;
   LRRC_GRR_BANDINDICATOR_ENUM_UINT16                       enBandInd;
}LRRC_GURRC_GERAN_CELL_STRU;

/*****************************************************************************
 结构名    :    LRRC_GURRC_LOW_PLMN_ID_INFO_STRU
 协议表格  :
 ASN.1描述 :
 结构说明  :  低优先级plmn数据结构，包括plmn信息和RSRP测量值
*****************************************************************************/
typedef struct
{
    LRRC_GURRC_PLMN_ID_INFO_STRU                            stLowPlmnId;
    VOS_INT32                                               lRsrp;
}LRRC_GURRC_LOW_PLMN_ID_INFO_STRU;

/*****************************************************************************
 结构名    :    LRRC_GURRC_PLMN_ID_LIST_STRU
 协议表格  :
 ASN.1描述 :
 结构说明  :  suitable Plmn 搜索失败，LRRC发给WRRC PLMN SEARCH 结果
*****************************************************************************/
typedef struct
{
    /* 高质量PLMN的个数 */
    VOS_UINT32                                              ulHighPlmnNum;
    LRRC_GURRC_PLMN_ID_INFO_STRU                            astHighPlmnList[LRRC_GURRC_MAX_HIGH_PLMN_NUM];

    /* 低质量PLMN的个数 */
    VOS_UINT32                                              ulLowPlmnNum;
    LRRC_GURRC_LOW_PLMN_ID_INFO_STRU                        astLowPlmnList[LRRC_GURRC_MAX_LOW_PLMN_NUM];
}LRRC_GURRC_PLMN_ID_LIST_STRU;

/* CMCC-BEGIN */
/*****************************************************************************
 结构名    : LRRC_GURRC_REDIR_SAVED_EUTRA_INFO_STRU
 协议表格  :
 ASN.1描述 :
 结构说明  : LTE本地保存的历史频点列表信息
*****************************************************************************/
typedef struct
{
    VOS_UINT32                                              ulArfcnNum;
    VOS_UINT16                                              ausArfcn[LRRC_GURRC_LTE_PHY_MAX_SUPPORT_CARRIER_NUM];
}LRRC_GURRC_REDIR_SAVED_EUTRA_INFO_STRU;
/* CMCC-END */

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

#endif /* end of LRRC_GURRCCommInterface.h */
