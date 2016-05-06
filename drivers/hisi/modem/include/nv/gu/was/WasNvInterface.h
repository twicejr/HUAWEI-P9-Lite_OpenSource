/******************************************************************************

  Copyright(C)2008,Hisilicon Co. LTD.

 ******************************************************************************
  File Name       : WasNvInterface.h
  Description     : WasNvInterface.h header file
  History         :

******************************************************************************/

#ifndef __WASNVINTERFACE_H__
#define __WASNVINTERFACE_H__

#ifdef __cplusplus
#if __cplusplus
extern "C" {
#endif
#endif


/*****************************************************************************
  1 Include Headfile
*****************************************************************************/
#if (VOS_OS_VER != VOS_WIN32)
#pragma pack(4)
#else
#pragma pack(push, 4)
#endif

#include "PsTypeDef.h"

/*****************************************************************************
  2 Macro
*****************************************************************************/
#define WAS_MAX_NETWORKPARA_SIZE                (144)                           /*  NET WorkPara文件长度宏定义 */
/* Modified by x00220225 for 云端频点收集, 2015-07-14, begin */
#define WAS_HISTORY_SEARCH_PLMN_MAX_NUM         (16)
#define WAS_HISTORY_PLMN_MAX_NUM                (32)                            /* 存储到NV中的最多PLMN信息 */
/* Modified by x00220225 for 云端频点收集, 2015-07-14, end */
#define WAS_OPERATOR_FREQS_MAX_NUM              (16)
#define WAS_OPERATOR_PLMN_MAX_NUM               (20)


#define NV_ITEM_MEAS_THRESHOLD_SIZE             (40)
#define WAS_MAPWEIGHT_MAX_NUM                   (16)
#define WAS_HISTORY_PLMN_ID_BYTES               (3)
/* Modified by x00220225 for 云端频点收集, 2015-07-14, begin */
#define WAS_HISTORY_SEARCH_FREQS_MAX_NUM        (6)
#define WAS_HISTORY_FREQS_MAX_NUM               (16)                             /* 存储到NV中的PLMN对应的频点最大个数 */
/* Modified by x00220225 for 云端频点收集, 2015-07-14, end */
#define WAS_UE_ACCESS_CAPA_NUM                  (20)
#define NVIM_MAX_MCC_SIZE                       (3)
#define NVIM_MAX_MNC_SIZE                       (3)
#define NVIM_MAX_RPLMN_FDD_FREQ_NUM             (8)
#define NV_ITEM_RPLMN_INFO_SIZE                 (56)
#define NV_ITEM_NETWORKPARA_SIZE                (144)
#define NV_Item_WAS_RadioAccess_Capa_SIZE       (20)
#define NV_Item_WAS_RadioAccess_Capa_New_SIZE   (48)                            /* WAS新增NV项NV_Item_WAS_RadioAccess_Capa_New */
#define NV_Item_WCDMA_PLMN_FREQ_PAIR_List_SIZE  (260)
/* Added by x00220225 for 云端频点收集, 2015-07-17, begin */
#define NV_Item_WCDMA_HISTORY_PLMN_FREQ_LIST_SIZE  (1156)
/* Added by x00220225 for 云端频点收集, 2015-07-17, end */
#define NV_Item_WCDMA_OPERATOR_FREQ_List_SIZE   (56)
#define NV_ITEM_BG_THRESHOLD_SIZE               (8)
#define NV_ITEM_PDCP_LOSSLESS_SIZE              (2)
#define NV_ITEM_DYN_FREQUENCY_SIZE              (2)
#define NV_ITEM_INIT_FREQUENCY_SIZE             (2)
#define NV_ITEM_PLMN_SEARCH_THRESHOLD_SIZE      (4)
#define NV_ITEM_PLMN_SEARCH_FLOW_SIZE           (8)
#define NV_ITEM_ALL_BAND_SEARCH_PARA_SIZE       (8)
#define NV_ITEM_BROKEN_CELL_PARA_SIZE           (4)
#define NV_ITEM_WAS_ERRORLOG_ITEM_NUM           (4)
#define NV_ITEM_WCDMA_IND_FRED_SIZE             (2)
#define NV_ITEM_FREQBANDS_LIST_SIZE             (52)
#define WAS_NV_MEAS_THRESHOLD_HALF_THRHLD_SIZE  (NV_ITEM_MEAS_THRESHOLD_SIZE/2)
#define WAS_NV_MEAS_THRESHOLD_RESERVE_SIZE      (WAS_NV_MEAS_THRESHOLD_HALF_THRHLD_SIZE-4)
#define NV_ITEM_WAS_ERRORLOG_CSHO_LEN_SIZE      (2)
#define WAS_NV_PTL_VER_R3                       (0)                             /* WAS_PTL_VER_R3 */
#define WAS_NV_PTL_VER_R4                       (1)                             /* WAS_PTL_VER_R4 */
#define WAS_NV_PTL_VER_R5                       (2)                             /* WAS_PTL_VER_R5 */
#define WAS_NV_PTL_VER_R6                       (3)                             /* WAS_PTL_VER_R6 */
#define WAS_NV_PTL_VER_R7                       (4)                             /* WAS_PTL_VER_R7 */
#define WAS_NV_PTL_VER_R8                       (5)                             /* WAS_PTL_VER_R8 */
#define WAS_NV_PTL_VER_R9                       (6)                             /* WAS_PTL_VER_R9 */

#define WAS_INVALID_MNC                         (0xffffffff)
#define WAS_MAX_CSFB_MCC_BAND_NUM               (80)
#define WAS_CSFB_MAX_DETECT_CELL_NUM            (3)                              /* 小区搜索时最多上报的检测小区个数 */
#define WAS_CSFB_MAX_REPORT_CELL_NUM            (3)                              /* CSFB流程指定频点搜索时最多上报的小区个数 */

#define WAS_OPERATOR_CLOUD_PLMN_MAX_NUM         (50)
#define WAS_OPERATOR_CLOUD_FREQS_MAX_NUM        (16)
#define WAS_NV_BROKEN_CELL_RSCP_HIGH_THRESH     (-85)                           /* 加入borokencell列表中得小区是高质量小区的门限 */
#define WAS_NV_BROKEN_CELL_RSCP_OFFSET          (20)                            /* 加入Brokencell中得小区能量变好放出bar列表的门限 */

#define WAS_NV_DEFAULT_CQQUALMIN                (-18)
#define WAS_NV_DEFAULT_CQRXLEVMIN               (-110)


#define WAS_HISTORY_FREQ_SRCH_DEFAULT_ENABLE_BITMAP             ( (VOS_UINT32)WAS_NETWORK_SEARCH_PROGRESS_SPEC_SRCH \
                                                                | (VOS_UINT32)WAS_NETWORK_SEARCH_PROGRESS_FAST_SRCH \
                                                                | (VOS_UINT32)WAS_NETWORK_SEARCH_PROGRESS_HISTORY_SRCH \
                                                                | (VOS_UINT32)WAS_NETWORK_SEARCH_PROGRESS_IDLE_OOS_SRCH \
                                                                | (VOS_UINT32)WAS_NETWORK_SEARCH_PROGRESS_FACH_OOS_SRCH\
                                                                | (VOS_UINT32)WAS_NETWORK_SEARCH_PROGRESS_PCH_OOS_SRCH \
                                                                | (VOS_UINT32)WAS_NETWORK_SEARCH_PROGRESS_DCH_OOS_SRCH \
                                                                | (VOS_UINT32)WAS_NETWORK_SEARCH_PROGRESS_L2W_REDIR_SRCH \
                                                                | (VOS_UINT32)WAS_NETWORK_SEARCH_PROGRESS_NAS_CSFB_SRCH\
                                                                | (VOS_UINT32)WAS_NETWORK_SEARCH_PROGRESS_NAS_PRE_BAND_SRCH\
                                                                | (VOS_UINT32)WAS_NETWORK_SEARCH_PROGRESS_LTE_OOS_SEARCH\
                                                                | (VOS_UINT32)WAS_NETWORK_SEARCH_PROGRESS_NAS_GEO_SRCH\
                                                                | (VOS_UINT32)WAS_NETWORK_SEARCH_PROGRESS_COMMON\)

#define WAS_FULL_BAND_FREQ_SRCH_DEFAULT_ENABLE_BITMAP           ( (VOS_UINT32)WAS_NETWORK_SEARCH_PROGRESS_SPEC_SRCH \
                                                                | (VOS_UINT32)WAS_NETWORK_SEARCH_PROGRESS_FAST_SRCH \
                                                                | (VOS_UINT32)WAS_NETWORK_SEARCH_PROGRESS_HISTORY_SRCH \
                                                                | (VOS_UINT32)WAS_NETWORK_SEARCH_PROGRESS_IDLE_OOS_SRCH \
                                                                | (VOS_UINT32)WAS_NETWORK_SEARCH_PROGRESS_FACH_OOS_SRCH\
                                                                | (VOS_UINT32)WAS_NETWORK_SEARCH_PROGRESS_PCH_OOS_SRCH \
                                                                | (VOS_UINT32)WAS_NETWORK_SEARCH_PROGRESS_DCH_OOS_SRCH \
                                                                | (VOS_UINT32)WAS_NETWORK_SEARCH_PROGRESS_L2W_REDIR_SRCH \
                                                                | (VOS_UINT32)WAS_NETWORK_SEARCH_PROGRESS_NAS_CSFB_SRCH\
                                                                | (VOS_UINT32)WAS_NETWORK_SEARCH_PROGRESS_NAS_PRE_BAND_SRCH\
                                                                | (VOS_UINT32)WAS_NETWORK_SEARCH_PROGRESS_LTE_OOS_SEARCH\
                                                                | (VOS_UINT32)WAS_NETWORK_SEARCH_PROGRESS_NAS_GEO_SRCH\
                                                                | (VOS_UINT32)WAS_NETWORK_SEARCH_PROGRESS_COMMON\)

#define WAS_CLOUD_FREQ_FROM_CSS_DEFAULT_ENABLE_BITMAP           ( (VOS_UINT32)WAS_NETWORK_SEARCH_PROGRESS_SPEC_SRCH \
                                                                | (VOS_UINT32)WAS_NETWORK_SEARCH_PROGRESS_FAST_SRCH \
                                                                | (VOS_UINT32)WAS_NETWORK_SEARCH_PROGRESS_HISTORY_SRCH \
                                                                | (VOS_UINT32)WAS_NETWORK_SEARCH_PROGRESS_IDLE_OOS_SRCH \
                                                                | (VOS_UINT32)WAS_NETWORK_SEARCH_PROGRESS_FACH_OOS_SRCH\
                                                                | (VOS_UINT32)WAS_NETWORK_SEARCH_PROGRESS_PCH_OOS_SRCH \
                                                                | (VOS_UINT32)WAS_NETWORK_SEARCH_PROGRESS_DCH_OOS_SRCH \
                                                                | (VOS_UINT32)WAS_NETWORK_SEARCH_PROGRESS_L2W_REDIR_SRCH \
                                                                | (VOS_UINT32)WAS_NETWORK_SEARCH_PROGRESS_NAS_CSFB_SRCH\
                                                                | (VOS_UINT32)WAS_NETWORK_SEARCH_PROGRESS_NAS_PRE_BAND_SRCH\
                                                                | (VOS_UINT32)WAS_NETWORK_SEARCH_PROGRESS_LTE_OOS_SEARCH\
                                                                | (VOS_UINT32)WAS_NETWORK_SEARCH_PROGRESS_NAS_GEO_SRCH\
                                                                | (VOS_UINT32)WAS_NETWORK_SEARCH_PROGRESS_COMMON\)

#define WAS_PREFER_BAND_FROM_CSS_DEFAULT_ENABLE_BITMAP          ( (VOS_UINT32)WAS_NETWORK_SEARCH_PROGRESS_SPEC_SRCH \
                                                                | (VOS_UINT32)WAS_NETWORK_SEARCH_PROGRESS_FAST_SRCH \
                                                                | (VOS_UINT32)WAS_NETWORK_SEARCH_PROGRESS_HISTORY_SRCH \
                                                                | (VOS_UINT32)WAS_NETWORK_SEARCH_PROGRESS_IDLE_OOS_SRCH \
                                                                | (VOS_UINT32)WAS_NETWORK_SEARCH_PROGRESS_FACH_OOS_SRCH\
                                                                | (VOS_UINT32)WAS_NETWORK_SEARCH_PROGRESS_PCH_OOS_SRCH \
                                                                | (VOS_UINT32)WAS_NETWORK_SEARCH_PROGRESS_DCH_OOS_SRCH \
                                                                | (VOS_UINT32)WAS_NETWORK_SEARCH_PROGRESS_L2W_REDIR_SRCH \
                                                                | (VOS_UINT32)WAS_NETWORK_SEARCH_PROGRESS_NAS_CSFB_SRCH\
                                                                | (VOS_UINT32)WAS_NETWORK_SEARCH_PROGRESS_NAS_PRE_BAND_SRCH\
                                                                | (VOS_UINT32)WAS_NETWORK_SEARCH_PROGRESS_LTE_OOS_SEARCH\
                                                                | (VOS_UINT32)WAS_NETWORK_SEARCH_PROGRESS_NAS_GEO_SRCH\
                                                                | (VOS_UINT32)WAS_NETWORK_SEARCH_PROGRESS_COMMON\)
#define WAS_OPERATOR_FREQ_FROM_CSS_DEFAULT_ENABLE_BITMAP        ( (VOS_UINT32)WAS_NETWORK_SEARCH_PROGRESS_SPEC_SRCH \
                                                                | (VOS_UINT32)WAS_NETWORK_SEARCH_PROGRESS_FAST_SRCH \
                                                                | (VOS_UINT32)WAS_NETWORK_SEARCH_PROGRESS_HISTORY_SRCH \
                                                                | (VOS_UINT32)WAS_NETWORK_SEARCH_PROGRESS_IDLE_OOS_SRCH \
                                                                | (VOS_UINT32)WAS_NETWORK_SEARCH_PROGRESS_FACH_OOS_SRCH\
                                                                | (VOS_UINT32)WAS_NETWORK_SEARCH_PROGRESS_PCH_OOS_SRCH \
                                                                | (VOS_UINT32)WAS_NETWORK_SEARCH_PROGRESS_DCH_OOS_SRCH \
                                                                | (VOS_UINT32)WAS_NETWORK_SEARCH_PROGRESS_L2W_REDIR_SRCH \
                                                                | (VOS_UINT32)WAS_NETWORK_SEARCH_PROGRESS_NAS_CSFB_SRCH\
                                                                | (VOS_UINT32)WAS_NETWORK_SEARCH_PROGRESS_NAS_PRE_BAND_SRCH\
                                                                | (VOS_UINT32)WAS_NETWORK_SEARCH_PROGRESS_LTE_OOS_SEARCH\
                                                                | (VOS_UINT32)WAS_NETWORK_SEARCH_PROGRESS_NAS_GEO_SRCH\
                                                                | (VOS_UINT32)WAS_NETWORK_SEARCH_PROGRESS_COMMON\)
/*****************************************************************************
  3 Massage Declare
*****************************************************************************/


/*****************************************************************************
  4 Enum
*****************************************************************************/


/*****************************************************************************
  5 STRUCT
*****************************************************************************/
/*****************************************************************************
*                                                                            *
*                           参数设置消息结构                                 *
*                                                                            *
******************************************************************************/
/*****************************************************************************
 枚 举 名  : WAS_NETWORK_SEARCH_PROGRESS_ENUM
 枚举说明  : WAS搜网流程枚举
 修改历史  :
  1.日  期   : 2015年10月19日
    作  者   : w00134354
    修改内容 : 新生成结构

*****************************************************************************/
enum WAS_NETWORK_SEARCH_PROGRESS_ENUM
{
    WAS_NETWORK_SEARCH_PROGRESS_NONE                      = 0x00000000,     
    WAS_NETWORK_SEARCH_PROGRESS_SPEC_SRCH                 = 0x00000001,   /* bit0: NAS SPEC SRCH */
    WAS_NETWORK_SEARCH_PROGRESS_FAST_SRCH                 = 0x00000002,   /* bit1: NAS SPEC FAST SRCH */
    WAS_NETWORK_SEARCH_PROGRESS_HISTORY_SRCH              = 0x00000004,   /* bit2: NAS HISTORY SRCH */
    WAS_NETWORK_SEARCH_PROGRESS_IDLE_OOS_SRCH             = 0x00000008,   /* bit3: IDLE OOS SRCH */
    WAS_NETWORK_SEARCH_PROGRESS_FACH_OOS_SRCH             = 0x00000010,   /* bit4: FACH OOS SRCH */
    WAS_NETWORK_SEARCH_PROGRESS_PCH_OOS_SRCH              = 0x00000020,   /* bit5: PCH OOS SRCH */
    WAS_NETWORK_SEARCH_PROGRESS_DCH_OOS_SRCH              = 0x00000040,   /* bit6: DCH OOS SRCH */
    WAS_NETWORK_SEARCH_PROGRESS_L2W_REDIR_SRCH            = 0x00000080,   /* bit7: L2G REDIR(include L2W CSFB) SRCH */
    WAS_NETWORK_SEARCH_PROGRESS_NAS_CSFB_SRCH             = 0x00000100,   /* bit8: NAS CSFB SRCH */
    WAS_NETWORK_SEARCH_PROGRESS_NAS_PRE_BAND_SRCH         = 0x00000200,   /* bit9: NAS prefer band SRCH  */
    WAS_NETWORK_SEARCH_PROGRESS_LTE_OOS_SEARCH            = 0x00000400,   /* bit10:lte OOS SRCH */
    WAS_NETWORK_SEARCH_PROGRESS_NAS_GEO_SRCH              = 0x00000800,   /* bit11:NAS GEO SRCH */
    WAS_NETWORK_SEARCH_PROGRESS_COMMON                    = 0x00001000,   /* bit12:通用流程 */
  
    WAS_NETWORK_SEARCH_PROGRESS_BUTT
};
typedef VOS_UINT32 WAS_NETWORK_SEARCH_PROGRESS_ENUM_UINT32;

/*****************************************************************************
 结构名    : WAS_NVIM_NETPARA_STRU
 结构说明  : NET PARA信息结构                       ID:8246 en_NV_Item_NetWorkPara
*****************************************************************************/
typedef struct
{
    VOS_UINT8                               aucFileContent[WAS_MAX_NETWORKPARA_SIZE];   /* File内容 */
}WAS_NVIM_NETPARA_STRU;

/*****************************************************************************
 结构名    : WAS_NVIM_MEAS_THRESHOLD_STRU
 结构说明  : 从NVIM中读出的MeasThreshold参数        ID:8263 en_NV_Item_Meas_Threshold
*****************************************************************************/
typedef struct
{
    VOS_INT16                               sMeasRptRscpThreshold;              /* 1a/1c事件评估最低RSCP门限    */
    VOS_INT16                               sMeasRptEcn0Threshold;              /* 1a/1c事件评估最低ECN0门限    */
    VOS_INT16                               sCellSrchRscpThreshold;             /* 小区搜索最低RSCP门限         */
    VOS_INT16                               sCellSrchEcn0Threshold;             /* 小区搜索最低ECN0门限         */
    VOS_INT16                               asReserve[WAS_NV_MEAS_THRESHOLD_RESERVE_SIZE];     /* 保留字段 */
}WAS_NVIM_MEAS_THRESHOLD_STRU;

/* Modified by x00220225 for 云端频点收集, 2015-07-17, begin */
/*****************************************************************************
 结构名    : WAS_NVIM_PLMN_FREQ_PAIR_STRU
 结构说明  : 结构体WAS_NVIM_PLMN_FREQ_PAIR_LIST_STRU的数据成员结构体
 注释      : 该结构体已经废弃不用，使用新的结构体 WAS_NVIM_HISTORY_FREQ_LIST_STRU
*****************************************************************************/

typedef struct
{
    VOS_UINT8                               aucPlmnId[WAS_HISTORY_PLMN_ID_BYTES];
    VOS_UINT8                               ucFreqCnt;
    VOS_UINT16                              ausFreq[WAS_HISTORY_SEARCH_FREQS_MAX_NUM];
}WAS_NVIM_PLMN_FREQ_PAIR_STRU;

/*****************************************************************************
 结构名    : WAS_NVIM_HISTORY_FREQ_LIST_STRU
 结构说明  : 结构体WAS_NVIM_HISTORY_SEARCH_PLMN_FREQ_LIST_STRU的数据成员结构体
*****************************************************************************/

typedef struct
{
    VOS_UINT8                               aucPlmnId[WAS_HISTORY_PLMN_ID_BYTES];
    VOS_UINT8                               ucFreqCnt;
    VOS_UINT16                              ausFreq[WAS_HISTORY_FREQS_MAX_NUM];
}WAS_NVIM_HISTORY_FREQ_LIST_STRU;

/*****************************************************************************
 结构名    : WAS_NVIM_PLMN_FREQ_PAIR_LIST_STRU
 结构说明  : 从NV中读取出保存的历史PLMN和对应的频点 ID:8284 en_NV_Item_WCDMA_PLMN_FREQ_PAIR_List
 注释      : 该结构体已经废弃不用，使用新的结构体 WAS_NVIM_HISTORY_SEARCH_PLMN_FREQ_STRU
*****************************************************************************/
typedef struct
{
    VOS_UINT32                              ulPlmnCnt;
    WAS_NVIM_PLMN_FREQ_PAIR_STRU            astNvPlmnFreqPair[WAS_HISTORY_SEARCH_PLMN_MAX_NUM];
}WAS_NVIM_PLMN_FREQ_PAIR_LIST_STRU;

/*****************************************************************************
 结构名    : WAS_NVIM_HISTORY_SEARCH_PLMN_FREQ_LIST_STRU
 结构说明  : 从NV中读取出保存的历史PLMN和对应的频点 ID:3023 en_NV_Item_WCDMA_HISTORY_PLMN_FREQ_LIST
*****************************************************************************/
typedef struct
{
    VOS_UINT32                              ulPlmnCnt;
    WAS_NVIM_HISTORY_FREQ_LIST_STRU         astNvPlmnFreqPair[WAS_HISTORY_PLMN_MAX_NUM];
}WAS_NVIM_HISTORY_SEARCH_PLMN_FREQ_LIST_STRU;
/* Modified by x00220225 for 云端频点收集, 2015-07-17, end */

typedef struct
{
    VOS_UINT8    ucMcc[NVIM_MAX_MCC_SIZE];
    VOS_UINT8    ucMnc[NVIM_MAX_MNC_SIZE];
}NVIM_PLMN_ID_STRU;

/*****************************************************************************
 结构名    : WAS_NVIM_PLMN_FREQ_PAIR_LIST_STRU
 结构说明  : 从NV中读取出保存的历史PLMN和对应的频点 ID:8314 en_NV_Item_Opr_Freq_List
*****************************************************************************/
typedef struct
{
    PS_BOOL_ENUM_UINT8                      enOperatorFreqListValidFlg;              /* 频点列表是否有效标志 */
    NVIM_PLMN_ID_STRU                       stPlmnId;                                /* Plmn ID */
    VOS_UINT8                               ucFreqNum;                               /* 所属这个plmn的频点个数 */
    VOS_UINT16                              ausFreqInfo[24]; /* 所属这个plmn的频点信息 */
}WAS_NVIM_OPERATOR_FREQ_LIST_STRU;

/*****************************************************************************
 结构名    : WAS_PLMN_ID_STRU
 协议表格  :
 ASN.1描述 :
 结构说明  :PLMN数据结构
*****************************************************************************/
typedef struct
{
    VOS_UINT32                          ulMcc;              /* MCC,3 bytes      */
    VOS_UINT32                          ulMnc;              /* MNC,2 or 3 bytes */
}WAS_PLMN_ID_STRU;
/*****************************************************************************
 结构名    : WAS_NVIM_OPERATOR_FREQ_INFO_STRU
 结构说明  : 运营商定制频点信息
*****************************************************************************/
typedef struct
{
    WAS_PLMN_ID_STRU                        stPlmnId;                                /* Plmn ID */
    VOS_UINT8                               ucFreqNum;                               /* 所属这个plmn的频点个数 */
    VOS_UINT8                               ucResvered1;                             /* 保留位 */
    VOS_UINT8                               ucResvered2;                             /* 保留位 */
    VOS_UINT8                               ucResvered3;                             /* 保留位 */
    VOS_UINT16                              ausFreqInfo[WAS_OPERATOR_FREQS_MAX_NUM]; /* 所属这个plmn的频点信息 */
}WAS_NVIM_OPERATOR_FREQ_INFO_STRU;

/*****************************************************************************
 结构名    : WAS_NVIM_OPERATOR_FREQ_PLMN_LIST_STRU
 结构说明  : 从NV中读取出保存的历史PLMN和对应的频点 ID:3029 en_NV_Item_Was_Operator_Freq_List_Info
*****************************************************************************/
typedef struct
{
    VOS_UINT8                               ucPlmnNum;
    VOS_UINT8                               ucReportCellNum;
    VOS_UINT8                               ucSearchOperatorBandFlg;                 /* 是否要搜历史频点和运营商频点所在的band */
    VOS_UINT8                               aucResvered2;
    WAS_NVIM_OPERATOR_FREQ_INFO_STRU        ausPlmnFreqList[WAS_OPERATOR_PLMN_MAX_NUM];
}WAS_NVIM_OPERATOR_FREQ_PLMN_LIST_STRU;

/*****************************************************************************
 结构名    : WAS_NVIM_BG_THRESHOLD_STRU
 协议表格  :
 ASN.1描述 :
 结构说明  : 从NVIM中读出的背景搜Threshold参数      ID:8316 en_NV_Item_BG_Threshold
*****************************************************************************/
typedef struct
{
    VOS_UINT8                               ucStatus;                           /*激活项选择,0:不激活,1激活,默认值:1*/
    VOS_INT8                                cWCDMA_RSSI_Threshold;              /*Range:[-125,0]*/ /*WCDMA RSSI门限,默认值:-95*/
    VOS_INT8                                cWCDMA_Cpich_EcNo_Threshold;        /*Range:[-25,0]*/  /*WCDMA Cpich_EcNo门限,默认值:-11*/
    VOS_INT8                                cWCDMA_Cpich_Rscp_Threshold;        /*Range:[-125,0]*/ /*WCDMA Cpich_Rscp门限,默认值:-100*/
    VOS_INT8                                cGSM_RSSI_Threshold;                /*Range:[-125,0]*/ /*GSM RSSI门限,默认值:-95*/
    VOS_UINT8                               ucBgGsmMeasSqualOffset;             /* 高优先级RAT搜时GSM测量启动门限Squal offset */
    VOS_UINT8                               ucBgGsmMeasSrxlevOffset;            /* 高优先级RAT搜时GSM测量启动门限Srxlev offset */
    PS_BOOL_ENUM_UINT8                      enBgModifyDrxThresholdFlg;          /* 修改BG搜DRX门限标记 */
}WAS_NVIM_BG_THRESHOLD_STRU;

/*****************************************************************************
 结构名    : WAS_BROKEN_CELL_STRU
 结构说明  : 存放Broken Cell的参数设置              ID:8341 en_NV_Item_WAS_BROKEN_CELL_PARA
*****************************************************************************/
typedef struct
{
    VOS_UINT16                              usNfail;                            /* 最多进行Nfail轮RRC_CONN_REQ重发,否则将小区加入Bar列表 */
    VOS_UINT16                              usTBarFailLen;                      /* 小区加入禁止列表的时间，单位:秒 */
} WAS_BROKEN_CELL_STRU;

/*****************************************************************************
 结构名    : WAS_BROKEN_CELL_STRU
 结构说明  : 存放Broken Cell的参数设置              ID:3030 en_NV_Item_Was_Broken_Cell_Info
*****************************************************************************/
typedef struct
{
    VOS_UINT8                               ucRaNfail;                          /* 最多进行Nfail轮RRC_CONN_REQ重发,否则将小区加入Bar列表 */
    VOS_UINT8                               ucRejNfail;                         /* RRC CONNECTION REJ N论后将小区加入bar列表 */
    VOS_UINT8                               ucRscpOffset;                       /* 该小区能量增加这么多db时将小区从bar列表放出，可以驻留尝试接入 */
    VOS_INT8                                usRsv1;                             /* 保留位 */
    VOS_UINT16                              usRaMaxBarLen;                      /* bar小区的最大时长，单位为分钟，超过该时长小区自动解bar */
    VOS_UINT16                              usRaTBarInitialLen;                 /* 小区加入禁止列表的初始时间，单位:秒 */
    VOS_UINT16                              usRejMaxBarLen;                     /* RejBar小区的最大时长,单位分钟 */
    VOS_UINT16                              usRejTBarInialLen;                  /* RRC CONNECTION REJ N论后 Bar掉小区的初始时长，单位s */
    VOS_INT16                               sRscpHighThresh;                    /* 加入bar列表中的小区能量高于此门限，该小区放出bar列表就不受能量控制 */
    VOS_INT16                               sEcn0Thresh;                       /* 保留位 */
    VOS_UINT16                              usRsv3;                             /* 保留位 */
    VOS_UINT16                              usRsv4;                             /* 保留位 */
} WAS_NVIM_BROKEN_CELL_STRU;

/*****************************************************************************
 结构名    : WAS_NVIM_UE_FEATURE_CTRL
 结构说明  : 存储有NVIM读入的V3特性能力信息         ID:8472 en_NV_Item_Was_UeFeature_Ctrl
*****************************************************************************/
typedef struct
{
    VOS_UINT8                               ucIntegAlg;                         /* 默认值为6,支持UIA1&UIA2 */
    VOS_UINT8                               ucCipherAlg;                        /* 默认值为7,支持UEA1&UEA2 */
    VOS_UINT8                               ucWasFeatrue;                       /* 默认值为0,bit位依次控制高速移动检测和双DRX特性是否支持*/
	PS_BOOL_ENUM_UINT8                      enEPchCbsSupport;                   /* 是否支持Epch下接受Cbs */
}WAS_NVIM_UE_FEATURE_CTRL;

/*****************************************************************************
 结构名    : WAS_WEAK_SIGNAL_ENERGY_THRESHOLD_STRU
 结构说明  : Errorlog弱信号的门限                   ID:8499 en_NV_Item_WAS_Errorlog_Energy_Threshold
*****************************************************************************/
typedef struct
{
    VOS_INT16                               sRscpThreshold;
    VOS_INT16                               sECN0Threshold;
}WAS_WEAK_SIGNAL_ENERGY_THRESHOLD_STRU;

/*****************************************************************************
 枚举名    : WAS_TX_RX_FREQ_SEPARAT_ENUM_UINT8
 协议表格  :
 ASN.1描述 :
 枚举说明  :
*****************************************************************************/
enum WAS_TX_RX_FREQ_SEPARAT_ENUM
{
    WAS_TX_RX_FREQ_SEPARAT_DEFAULT_TX_RX_SEPARATION = 0,
    WAS_TX_RX_FREQ_SEPARAT_SPARE2,
    WAS_TX_RX_FREQ_SEPARAT_SPARE1,
    WAS_TX_RX_FREQ_SEPARAT_BUTT
} ;
typedef VOS_UINT8 WAS_TX_RX_FREQ_SEPARAT_ENUM_UINT8;

/*****************************************************************************
 结构名    : WAS_RF_CAPA_STRU
 协议表格  : 10.3.3.33 RF capability FDD
 ASN.1描述 :
 结构说明  : RF能力信息
*****************************************************************************/
typedef struct
{
    VOS_UINT8                               ucPowerClass;                       /* UE功率级别                               */
    WAS_TX_RX_FREQ_SEPARAT_ENUM_UINT8       enTxRxFreqSeparate;                 /* Tx/Rx 频率区间                           */
    VOS_UINT8                               aucReserve1[2];                     /* 4字节对齐，保留 */
}WAS_RF_CAPA_STRU;


/*****************************************************************************
 枚举名    : WAS_DL_SIMUL_HS_DSCH_CFG_ENUM_UINT8
 协议表格  :
 ASN.1描述 :
 枚举说明  :
*****************************************************************************/
enum  WAS_DL_SIMUL_HS_DSCH_CFG_ENUM
{
    WAS_DL_SIMUL_HS_DSCH_CFG_KBPS32 = 0,
    WAS_DL_SIMUL_HS_DSCH_CFG_KBPS64,
    WAS_DL_SIMUL_HS_DSCH_CFG_KBPS128,
    WAS_DL_SIMUL_HS_DSCH_CFG_KBPS384,
    WAS_DL_SIMUL_HS_DSCH_CFG_BUTT
};
typedef VOS_UINT8 WAS_DL_SIMUL_HS_DSCH_CFG_ENUM_UINT8;

/*****************************************************************************
 枚举名    : WAS_PTL_VER_TYPE_ENUM_UINT8
 协议表格  : 10.2.39    RRC CONNECTION REQUEST
 ASN.1描述 : AccessStratumReleaseIndicator
 枚举说明  : 协议版本
             Absence of the IE implies R3.
             The IE also indicates the release of the RRC transfer syntax
             supported by the UE 13 spare values are needed
*****************************************************************************/
enum WAS_PTL_VER_TYPE_ENUM
{
    WAS_PTL_VER_ENUM_R3                 = WAS_NV_PTL_VER_R3,                    /* _H2ASN_Replace  WAS_NV_PTL_VER_R3 = 0 */
    WAS_PTL_VER_ENUM_R4                 = WAS_NV_PTL_VER_R4,                    /* _H2ASN_Replace  WAS_NV_PTL_VER_R4 = 1 */
    WAS_PTL_VER_ENUM_R5                 = WAS_NV_PTL_VER_R5,                    /* _H2ASN_Replace  WAS_NV_PTL_VER_R5 = 2 */
    WAS_PTL_VER_ENUM_R6                 = WAS_NV_PTL_VER_R6,                    /* _H2ASN_Replace  WAS_NV_PTL_VER_R6 = 3 */
    WAS_PTL_VER_ENUM_R7                 = WAS_NV_PTL_VER_R7,                    /* _H2ASN_Replace  WAS_NV_PTL_VER_R7 = 4 */
    WAS_PTL_VER_ENUM_R8                 = WAS_NV_PTL_VER_R8,                    /* _H2ASN_Replace  WAS_NV_PTL_VER_R8 = 5 */
    WAS_PTL_VER_ENUM_R9                 = WAS_NV_PTL_VER_R9,                    /* _H2ASN_Replace  WAS_NV_PTL_VER_R9 = 6 */
    WAS_PTL_VER_ENUM_BUTT
};
typedef VOS_UINT8 WAS_PTL_VER_TYPE_ENUM_UINT8;

/*****************************************************************************
 结构名    : WAS_NVIM_UE_CAPA_STRU
 结构说明  : 存储在NVIM中的UE能力信息               ID:9008 en_NV_Item_WAS_RadioAccess_Capa_New
*****************************************************************************/
typedef struct
{
    VOS_UINT32                              ulHspaStatus;                       /* 0表示未激活,那么DPA和UPA都支持;1表示激活 */

    WAS_RF_CAPA_STRU                        stRfCapa;                           /* RF 能力信息                                  */

    PS_BOOL_ENUM_UINT8                      enSupportPwrBoosting;               /* 16QAM特性相关，是否支持E-DPCCH Power Boosting*/
    PS_BOOL_ENUM_UINT8                      enSf4Support;                       /* 是否支持ul dpcch 使用 slotFormat4 */

    WAS_DL_SIMUL_HS_DSCH_CFG_ENUM_UINT8     enDlSimulHsDschCfg;                 /* ENUMERATED  OPTIONAL                         */
    WAS_PTL_VER_TYPE_ENUM_UINT8             enAsRelIndicator;                   /* Access Stratum Release Indicator             */

    PS_BOOL_ENUM_UINT8                      enHSDSCHSupport;                    /* 是否支持enHSDSCHSupport的标志                */
    VOS_UINT8                               ucHSDSCHPhyCategory;                /* 支持HS-DSCH物理层的类型标志                  */

    PS_BOOL_ENUM_UINT8                      enMacEhsSupport;
    VOS_UINT8                               ucHSDSCHPhyCategoryExt;
    PS_BOOL_ENUM_UINT8                      enMultiCellSupport;                 /* 是否支持 Multi cell support,如果支持MultiCell,Ex2存在 */
    VOS_UINT8                               ucHSDSCHPhyCategoryExt2;            /* HS-DSCH physical layer category extension 2 */

    PS_BOOL_ENUM_UINT8                      enCellSpecTxDiversityForDc;         /*  This IE is optionally present if Dual-Cell HSDPA is supported. Otherwise it is not needed.
                                                                                    The IE is not needed in the INTER RAT HANDOVER INFO message. Otherwise, it is optional*/
    PS_BOOL_ENUM_UINT8                      enEFDPCHSupport;                    /* 是否支持E-FDPCH的标志,FDPCH支持时此NV才生效 */
    PS_BOOL_ENUM_UINT8                      enEDCHSupport;                      /* 是否支持EDCH的标志                           */
    VOS_UINT8                               ucEDCHPhyCategory;                  /* 支持UPA的等级                                */
    PS_BOOL_ENUM_UINT8                      enSuppUl16QAM;                      /* 是否支持上行16QAM，当支持时ucEDCHPhyCategoryExt才有效 */
    VOS_UINT8                               ucEDCHPhyCategoryExt;               /* 上行单载波支持16QAM时，填写7 */
    PS_BOOL_ENUM_UINT8                      enSuppEDpdchInterpolationFormula;   /* 16QAM特性相关，是否支持E-DPDCH power interpolation formula */
    PS_BOOL_ENUM_UINT8                      enSuppHsdpaInFach;                  /* 支持CELL_FACH下HS-DSCH的接收 */
    PS_BOOL_ENUM_UINT8                      enSuppHsdpaInPch;                   /* 支持CELL_PCH或URA_PCH下HS-DSCH的接收 */

    PS_BOOL_ENUM_UINT8                      enMacIsSupport;                     /* 是否支持MAC_I/MAC_Is */

    PS_BOOL_ENUM_UINT8                      enFDPCHSupport;                     /* 是否支持FDPCH的标志                          */

    PS_BOOL_ENUM_UINT8                      enHsscchLessSupport;                /* 是否支持 hsscchlessHsdschOperation           */
    PS_BOOL_ENUM_UINT8                      enUlDpcchDtxSupport;                /* 是否支持 discontinuousDpcchTransmission      */

    PS_BOOL_ENUM_UINT8                      enAdjFreqMeasWithoutCmprMode;       /* 是否支持 Adjacent Frequency measurements without compressed mode */

    PS_BOOL_ENUM_UINT8                      enMimoSingleStreamStrict;           /* 是否限制只能使用单流MIMO */
    PS_BOOL_ENUM_UINT8                      enMimoWithDlTxDiversity;            /* R9特性，在MIMO激活时，下行控制信道是否允许使用分集 */

    /* V7r1 双模增加NV项 LTE能力 */
    PS_BOOL_ENUM_UINT8                      enSptAbsPriBasedReselInUtra;        /* 支持UTRA中的优先级重选，默认为0，1为支持，0为不支持 */

    VOS_UINT8                               ucHSDSCHPhyCategoryExt3;            /* HS-DSCH physical layer category extension 3 */
    PS_BOOL_ENUM_UINT8                      enDcMimoSupport;                    /* 是否支持DC+MIMO */
    PS_BOOL_ENUM_UINT8                      enSuppCommEDCH;                     /* E-RACH新增特性 */

    PS_BOOL_ENUM_UINT8                      enDcUpaSupport;                     /* 是否支持DC UPA的标志 */
    VOS_UINT8                               ucEDCHPhyCategoryExt2;              /* EDCH  category extension 2*/
    PS_BOOL_ENUM_UINT8                      enEdpdchGainFactorFlg;              /* E-DPDCH功率回退因子使能标志位 */
    PS_BOOL_ENUM_UINT8                      enHo2EutranUnSupportFlg;            /* 是否不支持到L的HO */
    PS_BOOL_ENUM_UINT8                      enEutranMeasUnSupportFlg;           /* 是否不支持到连接态L的测量 */
    VOS_UINT8                               aucReserve2[5];
}WAS_NVIM_UE_CAPA_STRU;

/*****************************************************************************
 结构名    : WAS_PRACH_PARA_STRU
 结构说明  : W下发起随机接入时可能需要的参数        ID:9023 en_NV_Item_Wcdma_Prach_Para
*****************************************************************************/
typedef struct
{
    VOS_INT8                                cInitTxPowerExt;                    /*Range:[0,20]*/ /* 初始发射功率调节参数 */
    VOS_UINT8                               ucPrbRetransMaxExt;                 /* 随机接入发起次数调节参数 */
    VOS_UINT8                               aucReserve[2];
    VOS_UINT32                              ulASC0Para;                         /* 紧急呼随机接入概率算法参数 */
}WAS_PRACH_PARA_STRU;

/*****************************************************************************
 结构名    : NVIM_FASTDORM_PARA_STRU
 结构说明  : FASTDORM操作相关参数                   ID:9027 en_NV_Item_Fastdorm_Para
*****************************************************************************/
typedef struct
{
    VOS_UINT8                               ucWasMaxSCRINumInPCH;               /* WAS定义的P下DRX周期<CN域DRX周期长度最小值时SCRI最大发送次数  */
    VOS_UINT8                               ucNasRetryInterval;                 /* NAS定义的Retry时间间隔，以秒为单位*/
    VOS_UINT8                               ucT323Default;                      /* 网络配置的T323为0时使用NV中配置的默认值 */
    VOS_UINT8                               aucReserved[1];                     /* 预留 */
}NVIM_FASTDORM_PARA_STRU;

/*****************************************************************************
 结构名    : WAS_CSFB_PPAC_STRU
 结构说明  : 接入控制能力信息                       ID:9050 en_NV_Item_CSFB_PPAC_Para
*****************************************************************************/
typedef struct
{
    PS_BOOL_ENUM_UINT8                      enSuppPPACFlg;                      /* PPAC标志 */
    PS_BOOL_ENUM_UINT8                      enCsfbRcvAllSibFlg;                 /* CSFB是否全解系统消息标志 ,默认值为0，标志不全解 */
    PS_BOOL_ENUM_UINT8                      enCsfbSearchFailFastReturnFlg;      /* W下指定频点或小区搜网失败后，不再发起全频带搜网立即返回LTE */
    VOS_UINT8                               ucFrWaitGmmProcAndTimerLen;         /* CSFB流程结束后FR时是否等待GMM流程结束标记和等待FR的时长 */
}WAS_CSFB_PPAC_STRU;

/*****************************************************************************
 结构名    : WAS_3G_TO_2G_STRU
 结构说明  : 3G到2G重选优化NV
*****************************************************************************/
typedef struct
{
    PS_BOOL_ENUM_UINT8                      enSuppDetectCellSearchFlg;          /* 支持三步法标志 */
    VOS_UINT8                               ucDetectCellSearchThreshold;        /* 启动三步法的默认门限值 */
    VOS_UINT8                               ucStartDetectCellSearchCnt;         /* 启动三步法，需要服务小区连续满足停止门限的次数 */
    VOS_UINT8                               ucStopDetectCellSearchCnt;          /* 停止三步法，需要服务小区连续满足停止门限的次数 */
}WAS_3G_TO_2G_STRU;

/*****************************************************************************
 结构名    : WAS_NVIM_REPORT_CELL_SIGN_STRU
 结构说明  : 小区信号强度上报定时器长度和RSCP变化的门限值   ID:9067 en_NV_Item_Report_Cell_Sign
*****************************************************************************/
typedef struct
{
    VOS_UINT8                               ucPeriodTimerLen;
    VOS_UINT8                               ucRscpThreshold;
    VOS_UINT8                               ucEcn0Threshold;
    VOS_UINT8                               aucReserve1[1];
}WAS_NVIM_REPORT_CELL_SIGN_STRU;

/*****************************************************************************
 结构名    : WAS_CUSTOMIZED_PARA_STRU
 结构说明  : W下其他备选能力                        ID: 9069 en_NV_Item_Was_Customized_Para
*****************************************************************************/
typedef struct
{
    /* Was_Customized_Para */
    VOS_UINT8                               ucSbmMaskSupportType;
    VOS_UINT8                               ucDchOosSearchInterRatFlg;          /* DCH下触发CU时T314运行时是否搜索异系统标记*/
    VOS_UINT8                               ucOosAllBandHistoryFreqValidFlg;    /* 出服务区指定PLMN搜，历史频点搜索后，全频带搜索时搜索已搜索的历史频点 */
    VOS_UINT8                               ucOosAllBandAddHistoryFreqCnt;      /* 出服务区全频带搜索指定频点列表搜时增加历史频点的个数 */
    VOS_UINT32                              ulDocomMcc;
    VOS_UINT32                              ulDocomMnc;
}WAS_CUSTOMIZED_PARA_STRU;

/*****************************************************************************
 结构名    : WAS_W2L_CEll_RESEL_OFFSET_STRU
 结构说明  : W2L重选低功耗相关NV结构                ID:9124 en_NV_Item_LOW_POWER_Cell_Resel_OffSet
*****************************************************************************/
typedef struct
{
    PS_BOOL_ENUM_UINT8                      enOffsetEnableFlg;                  /* offset NV使能标记    */
    PS_BOOL_ENUM_UINT8                      enR8BasedCellReselFlg;              /* offset NV使能标记,enW2LR8BasedCellReselFlg不受控制    */
    VOS_UINT8                               aucReserve1[2];                     /* 保留位 */
    VOS_UINT16                              usWRscpThresh;                      /*Range:[0,928]*/  /* W服务小区RSCP门限，大于门限才能使用重选OFFSET，取绝对值 */
    VOS_UINT16                              usWEcnoThresh;                      /*Range:[0,160]*/  /* W服务小区ECNO门限，大于门限才能使用重选OFFSET，取绝对值 */
    VOS_UINT16                              usEutranCellRsrpOffset;             /*Range:[0,1040]*/ /* EUTRAN小区RSRP OFFSET */
    VOS_UINT16                              usEutranCellRsrqOffset;             /*Range:[0,160]*/  /* EUTRAN小区RSRQ OFFSET */
    VOS_UINT16                              usLteServRsrpOffSet;                /*Range:[0,784]*/
    VOS_UINT16                              usLteServRsrqOffSet;                /*Range:[0,256]*/
    VOS_UINT16                              usUtranRscpOffSet;                  /*Range:[0,376]*/
    VOS_UINT16                              usUtranEcn0OffSet;                  /*Range:[0,248]*/
}WAS_W2L_CEll_RESEL_OFFSET_STRU;

/*****************************************************************************
 结构名    : NVIM_UE_POSITION_CAPABILITIES_STRU
 结构说明  : UE的定位能力结构                       ID:9093 en_NV_Item_UE_POSITION_CAPABILITIES
*****************************************************************************/
typedef struct
{
   VOS_UINT8                                ucGpsUeAssisted;                    /* UE辅助的 GPS 定位能力: 0: 不支持, 1: 支持 */
   VOS_UINT8                                ucGpsUeBased;                       /* 基于UE的 GPS 定位能力: 0: 不支持, 1: 支持 */
   VOS_UINT8                                ucGpsUeStandalone;                  /* UE独立的 GPS 定位能力: 0: 不支持, 1: 支持 */
   VOS_UINT8                                ucGpsValidInPch;                    /* PCH态下的 GPS 定位能力(仅W 模使用): 0: 不支持, 1: 支持 */
   VOS_UINT8                                ucLcsVaCapability;                  /* LCS VALUE ADD定位能力(仅G 模使用): 0: 不支持, 1: 支持 */
   VOS_UINT8                                ucAddPosCapability;                 /* 附加的定位能力(仅G 模使用): 0: 不支持, 1: 支持 */

   VOS_UINT8                                aucRsv[2];                          /* 保留位 */
}NVIM_UE_POSITION_CAPABILITIES_STRU;


/*****************************************************************************
 结构名    : WAS_NVIM_PLMN_SEARCH_THRESHOLD_STRU
 结构说明  : 从NV中读取出保存的全频段搜网的门限      ID:8483 en_NV_Item_Plmn_Search_Threshold
*****************************************************************************/
typedef struct
{
    VOS_INT8                                cBgSearchHighQulityThreshold;       /* 背景搜RSSI高质量门限 */
    VOS_INT8                                cOtherSearchHighQulityThreshold;    /* 其他搜RSSI高质量门限 */
    VOS_INT8                                cLowQulityThreshold;                /* RSSI低质量门限 */
    VOS_UINT8                               ucInterRatMeasOffset;               /* 在启停异系统测量门限上减去的迟滞 */
}WAS_NVIM_PLMN_SEARCH_THRESHOLD_STRU;

/*****************************************************************************
 结构名    : WAS_NVIM_PLMN_LIST_SEARCH_THRESHOLD_STRU
 结构说明  : 从NV中读取出保存的PLMN LIST全频段搜网的门限
*****************************************************************************/
typedef struct
{
    VOS_INT8                                cPlmnListSrchHighQulityThreshold;   /* PLMN搜索RSSI高质量门限 */
    VOS_INT8                                cPlmnListSrchLowQulityThreshold;    /* PLMN搜索RSSI高质量门限 */
    VOS_INT8                                cReserve1;                           /* 保留 */
    VOS_INT8                                cReserve2;                           /* 保留 */
    VOS_INT8                                cReserve3;                           /* 保留 */
    VOS_INT8                                cReserve4;                           /* 保留 */
    VOS_INT8                                cReserve5;                           /* 保留 */
    VOS_INT8                                cReserve6;                           /* 保留 */
}WAS_NVIM_PLMN_LIST_SEARCH_THRESHOLD_STRU;

/*****************************************************************************
 结构名    : WAS_NVIM_PLMN_SEARCH_FLOW_STRU
 结构说明  : 从NV中读取出保存的全频段搜网的流程     ID:8484  en_NV_Item_Plmn_Search_Flow
*****************************************************************************/
typedef struct
{
    VOS_UINT8                               ucBgLowQulityFreqScrhFlag;          /* 背景搜低质量频点是否需要搜标志*/
    VOS_UINT8                               ucBgMultipleFreqScrhFlag;           /* 背景搜倍频点是否需要搜标志*/
    VOS_UINT8                               ucPlmnListLowQulityFreqScrhFlag;    /* PLMNLIST低质量频点是否需要搜标志*/
    VOS_UINT8                               ucPlmnListMultipleFreqScrhFlag;     /* PLMNLIST倍频点是否需要搜标志*/
    VOS_UINT8                               ucOtherLowQulityFreqScrhFlag;       /* 其他搜网流程低质量频点是否需要搜标志*/
    VOS_UINT8                               ucOtherMultipleFreqScrhFlag;        /* 其他搜网流程倍频点是否需要搜标志*/
    VOS_UINT8                               aucReserve1[2];
}WAS_NVIM_PLMN_SEARCH_FLOW_STRU;

/*****************************************************************************
 结构名    : WAS_NVIM_ALL_BAND_SEARCH_PARA_STRU
 结构说明  : 从NV中读取出保存的全频段搜网的配置参数 ID:8485 en_NV_Item_All_Band_Search_Para
*****************************************************************************/
typedef struct
{
    VOS_UINT32                              ulRawScanFftFlag;                   /* 各个band的粗扫算法 */
    VOS_UINT8                               aucReserv[2];                       /* 4字节对齐，保留字节 */
    VOS_UINT8                               ucFftFineScanFreqOffsetNum;         /* FFT算法细扫时取中心频点的偏移频点个数*/
    VOS_UINT8                               ucCellSearchFreqNum;                /* 细扫后一组频点需要做小区搜索的频点个数*/
    VOS_UINT8                               ucMultipleSrchFreqOffsetNum;        /* 倍频点搜索时，取中心频点的偏移频点个数*/
    VOS_UINT8                               ucPlmnListHistoryFreqThreshold;     /* PLMNLIST搜网时历史频点的个数门限*/
    VOS_UINT8                               ucWcdmaRawScanFftStep;              /* FFT算法时，采样步长*/
    VOS_UINT8                               ucWcdmaRawScanRssiStep;             /* RSSI算法时，采样步长*/
}WAS_NVIM_ALL_BAND_SEARCH_PARA_STRU;

/*****************************************************************************
 结构名    : WAS_NVIM_WCDMA_IND_FREQ_STRU
 结构说明  : WCDMA IND FREQ信息结构                 ID:8248 en_NV_Item_Wcdma_Ind_Freq UINT结构包成结构
*****************************************************************************/
typedef struct
{
    VOS_UINT16                              usUserIndFreq;
    VOS_UINT8                               aucReserve[2];
}WAS_NVIM_WCDMA_IND_FREQ_STRU;

/*****************************************************************************
 结构名    : WAS_NVIM_PDCP_LOSSLESS_SWITCH_STRU
 结构说明  : PDCP LOSSLESS SWITCH信息结构           ID:8324 en_NV_Item_PDCP_LossLess_Switch UINT结构包成结构
*****************************************************************************/
typedef struct
{
    VOS_UINT16                              usNvPdcpLossLessSwitch;    /*Range:[0,1]*/    /* PDCP 无损迁移开关 */
    VOS_UINT8                               aucReserve[2];
}WAS_NVIM_PDCP_LOSSLESS_SWITCH_STRU;

/*****************************************************************************
 结构名    : WAS_NVIM_OLPC_MAPWEIGHT_PARA_STRU
 结构说明  : WCDMA OLPC MAPWEIGHT PARA信息结构      ID:8525 en_NV_Item_Wcdma_OLPC_MapWeight_Para UINT结构包成结构
*****************************************************************************/
typedef struct
{
    VOS_UINT16                              ausMapWeight[WAS_MAPWEIGHT_MAX_NUM];    /*TOT OLPC算法参数*/
}WAS_NVIM_OLPC_MAPWEIGHT_PARA_STRU;

/*****************************************************************************
 结构名    : WAS_NVIM_W_CELLSRCH_MEAS_PARA
 结构说明  : W_CELLSRCH_MEAS_PARA信息结构           ID:8256 废弃NV项
*****************************************************************************/
typedef struct
{
    VOS_UINT16                              usSysInfoRcvOptimSwitch;
    VOS_UINT16                              usPIOptimSwitch;
    VOS_UINT16                              usCellSrchMeasOptimSwitch;
    VOS_UINT16                              usCellSrchPeriod;
    VOS_INT16                               sCsStartRSCPThreshold;
    VOS_INT16                               sCsStopRSCPThreshold;
    VOS_INT16                               sCsStartECN0Threshold;
    VOS_INT16                               sCsStopECN0Threshold;
    VOS_UINT16                              usMeasIntraNCellNum;
    VOS_UINT16                              usMeasFilterFactor;
}WAS_NVIM_W_CELLSRCH_MEAS_PARA;

/*****************************************************************************
 结构名    : WAS_NVIM_UE_ACCESS_CAPA
 结构说明  : UE_ACCESS_CAPA信息结构                 ID:8264 废弃NV项
*****************************************************************************/
typedef struct
{
    VOS_UINT8                               aucWasUeAccessCapa[WAS_UE_ACCESS_CAPA_NUM];
}WAS_NVIM_UE_ACCESS_CAPA;

/*****************************************************************************
 结构名    : NV_ITEM_BG_IRAT_LIST_STRU
 结构说明  : BG_IRAT_LIST信息结构                   ID:8487 废弃NV项
*****************************************************************************/
typedef struct
{
    VOS_UINT8                               ucValid;
    VOS_UINT8                               ucReserve;
    VOS_UINT16                              usBgIratListTime;                   /*Range:[6,65536]*/
}NV_ITEM_BG_IRAT_LIST_STRU;


/*****************************************************************************
 结构名    : WAS_NVIM_T_CR_MAX_STRU
 协议表格  : 10.3.2.3 Cell selection and re-selection info for SIB3/4
 ASN.1描述 : T_CRMax
 结构说明  : 高速移动检测参数
*****************************************************************************/
typedef struct
{
    VOS_UINT8                           ucTCrMax;       /* 单位:10s，0表示不使用，(0, 3, 6, 12, 18, 24) */
    VOS_UINT8                           ucNCr;          /* ucTCRMax不为0时有效，default 8，Integer(1..16) */
    VOS_UINT8                           ucTCrMaxHyst;   /* ucTCRMax不为0时有效，单位:1s，0表示不使用，(0, 10, 20, 30, 40, 50, 60, 70) */
    VOS_UINT8                           ucReserve;
}WAS_NVIM_T_CR_MAX_STRU;

/*****************************************************************************
 结构名    : WAS_NV_OOS_RL_FAIL_PARA_STRU
 结构说明  :
*****************************************************************************/
typedef struct
{
    VOS_UINT8                               ucOosTimerLen;
    PS_BOOL_ENUM_UINT8                      enT313UseDefaultValueFlg;
    VOS_UINT8                               ucReserve[2];
}WAS_NV_OOS_RL_FAIL_PARA_STRU;
/*****************************************************************************
 结构名    : NVIM_SBM_CUSTOM_DUAL_IMSI_STRU
 结构说明  : 日本的EMOIBLE网络中的plmn信息，该plmn LTE需要用到
*****************************************************************************/
typedef struct
{
    VOS_UINT8                           aucJapanEmMcc[3];  /* 日本EMBILE网络的MCC信息 */
    VOS_UINT8                           ucJapanEmMncCount; /* 日本EMBILE网络的MNC长度，2或者3 */
    VOS_UINT8                           aucJapanEmMnc[3];  /* 日本EMBILE网络的MNC信息,假如为两位，高位填f */
    VOS_UINT8                           ucReserve;
} NVIM_JAPAN_EM_PLMN_INFO_STRU;
/*****************************************************************************
 结构名    : NVIM_SBM_CUSTOM_DUAL_IMSI_STRU
 结构说明  : 软银双imsi开关和MCC信息
*****************************************************************************/

typedef struct
{
    VOS_UINT8                           ucSbmCustomDualImsiFlg;
    VOS_UINT8                           aucJapanMcc[3];      /* 日本地区的一个MCC */
    VOS_UINT8                           aucJapanMcc1[3];     /* 日本地区的另一个MCC */
    VOS_UINT8                           ucJapanSbmMncCount;  /* 日本软银网络的MNC个数 */
    VOS_UINT32                          aulJapanSbmMnc[5];   /* 日本软银网络的最多5个MNC,可扩展 */
    NVIM_JAPAN_EM_PLMN_INFO_STRU        stJapanEmPlmnInfo;   /* 日本的EMOBILE网络的plmn信息 */
    VOS_UINT8                           ucSbmOosTimerLen;    /* 驻留在日本软银网络出服务区起的定时器，超时前只搜band1和band11 */
    VOS_UINT8                           aucReserve[3];
} NVIM_SBM_CUSTOM_DUAL_IMSI_STRU;

/*****************************************************************************
 结构名    : NVIM_SBM_CUSTOM_DUAL_IMSI_STRU_NEW
 结构说明  : 软银双imsi开关和MCC信息
*****************************************************************************/

typedef struct
{
    VOS_UINT8                           ucSbmCustomDualImsiFlg;/* 双Imsi总开关 */
    VOS_UINT8                           ucDualImsiCellSearchChkFlg; /* 是否在搜网的时候band检查  */
    VOS_UINT8                           aucReserve[2];       /* 保留位 */
    VOS_UINT8                           ucSbmOosTimerLen;    /* 驻留在日本软银网络出服务区起的定时器 */
    VOS_UINT8                           aucJapanMcc[3];      /* 日本地区的一个MCC */
    VOS_UINT8                           aucJapanMcc1[3];     /* 日本地区的另一个MCC */
    VOS_UINT8                           ucJapanSbmMncCount;  /* 日本软银网络的MNC个数 */
    VOS_UINT32                          aulJapanSbmMnc[5];   /* 日本软银网络的最多5个MNC,可扩展 */
    NVIM_JAPAN_EM_PLMN_INFO_STRU        stJapanEmPlmnInfo;   /* 日本的EMOBILE网络的plmn信息 */
    VOS_UINT32                          ulSbmSupBandInJapan;         /* 软银在日本国内支持的band，如果是全1则认为支持的band不做限制，支持UE支持的所有band */
    VOS_UINT32                          ulEmSupBandInJapan;          /* EM在日本国内支持的band，如果是全1则认为支持的band不做限制，支持UE支持的所有band */
    VOS_UINT32                          ulOtherOperateSupBandInJapan;/* 其他运营商在日本国内支持的band，如果是全1则认为支持的band不做限制，支持UE支持的所有band */
    VOS_UINT32                          ulSupBandOutJapan;           /* 日本国外支持的band,如果全1则认为支持的band不做限制，支持UE支持的所有band */
    VOS_UINT32                          ulLteDelWcdmaBandInJapan;    /* 日本国内驻留Lte时需要屏蔽的W的band,如果全1则认为需要屏蔽所有的W的band */
} NVIM_SBM_CUSTOM_DUAL_IMSI_STRU_NEW;

/*****************************************************************************
 结构名    : NVIM_SBM_CUSTOM_DUAL_IMSI_STRU
 结构说明  : WAS的双imsi信息
*****************************************************************************/
typedef struct
{
    PS_BOOL_ENUM_UINT8                      enNvSbmDualImsiFlg;     /* 软银双imsi开关是否打开，默认关闭， */
    PS_BOOL_ENUM_UINT8                      enDualImsiCellSearchChkFlg; /* 是否在搜网的时候band检查  */
    VOS_UINT8                               ucSbmOosTimerLen;       /* 驻留在日本软银网络出服务区起的定时器，超时前只搜band1和band11 */
    VOS_UINT8                               ucJapanSbmMncCount;     /* 日本软银网络的MNC个数 */
    VOS_UINT32                              aulJapanSbmMnc[5];      /* 日本软银网络的最多5个MNC,可扩展支持测试 */
    VOS_UINT32                              ulJapanMcc;             /* 日本地区的一个MCC */
    VOS_UINT32                              ulJapanMcc1;            /* 日本地区的另一个MCC */
    VOS_UINT32                              ulEmMcc;                /* 日本地区embile网络的MCC */
    VOS_UINT32                              ulEmMnc;                /* 日本地区embile网络的MNC */
    VOS_UINT32                              ulSbmSupBandInJapan;    /* 软银在日本国内支持的band，如果是全1则认为支持的band不做限制，支持UE支持的所有band */
    VOS_UINT32                              ulEmSupBandInJapan;      /* EM在日本国内支持的band，如果是全1则认为支持的band不做限制，支持UE支持的所有band */
    VOS_UINT32                              ulOtherOperateSupBandInJapan;/* 其他运营商在日本国内支持的band，如果是全1则认为支持的band不做限制，支持UE支持的所有band */
    VOS_UINT32                              ulSupBandOutJapan;        /* 日本国外支持的band,如果全1则认为支持的band不做限制，支持UE支持的所有band */
} WAS_NV_SBM_CUSTOM_DUAL_IMSI_STRU;
/*****************************************************************************
 结构名    : WAS_NV_YOIGO_CUSTOM_PARA_INFO_STRU
 结构说明  : YOIGO定制开关和PLMN信息
*****************************************************************************/
typedef struct
{
    PS_BOOL_ENUM_UINT8            enYoigoCustomSwitchFlag;          /* YOIGO定制开关是否打开标志，默认关闭 */
    VOS_UINT8                     aucReserve[3];                    /* 保留位 */
    VOS_UINT32                    ulYoigoMcc;                       /* YOIGO网络的MCC */
    VOS_UINT32                    ulYoigoMnc;                       /* YOIGO网络的MNC */
}WAS_NV_YOIGO_CUSTOM_PARA_INFO_STRU;

typedef struct
{
    VOS_UINT8                   aucUeWcdmaBandPriodiry[NVIM_MAX_FDD_FREQ_BANDS_NUM];
}NVIM_WAS_FREQ_BAND_PRIORITY_STRU;

/*****************************************************************************
 结构名    : WAS_ERR_LOG_CS_HO_LEN_STRU
 结构说明  : Errorlog:CS 语音切换的时长
 修改历史  :
 1.日    期    : 2014年9月2日
   作    者    : 00134354
   修改内容    : 新建结构体
*****************************************************************************/
typedef struct
{
    VOS_UINT16                              usCSHandoverTime;                   /* cs切换需要的默认时间，超过该时间就主动上报 */
    VOS_UINT8                               aucReserve[2];                     /* 保留位 */
}WAS_ERR_LOG_CS_HO_LEN_STRU;

/*****************************************************************************
 结构名    : NVIM_ERR_LOG_STAY_SELF_RAT_TIMER_THRESHOLD_STRU
 结构说明  : 在本模停留的时间长度门限，默认为10分钟
 修改历史  :
 1.日    期    : 2015年2月6日
   作    者    : 00134354
   修改内容    : 新建结构体
*****************************************************************************/
typedef struct
{
    VOS_UINT16                              usTimerLength;                   /* 在本模停留的时间长度, 单位为分钟 */
    VOS_UINT8                               aucReserve[2];                  /* 保留位 */
}NVIM_ERR_LOG_STAY_SELF_RAT_TIMER_THRESHOLD_STRU;


/*****************************************************************************
 结构名    : WAS_ERR_LOG_3G_NOT_TO_LTE_TIMER_STRU
 结构说明  : 在W模驻留的时间长度，默认为10分钟
 修改历史  :
 1.日    期    : 2015年2月6日
   作    者    : 00134354
   修改内容    : 新建结构体
*****************************************************************************/
typedef struct
{
    VOS_UINT16                              usCampOnTime;                   /* 在W模下的时间，超过该时间就主动上报 */
    VOS_UINT8                               aucReserve[2];                  /* 保留位 */
}WAS_ERR_LOG_3G_NOT_TO_LTE_TIMER_STRU;

/*****************************************************************************
 结构名    : WAS_NV_T320_CTRL_STRU
 结构说明  : t320是否支持开关
 修改历史  :
 1.日    期    : 2015年2月6日
   作    者    : 00134354
   修改内容    : 新建结构体
*****************************************************************************/
typedef struct
{
    PS_BOOL_ENUM_UINT8                              enT320SupportFlg;               /* t320是否支持开关 */
    VOS_UINT8                                       aucReserve[3];                  /* 保留位 */
}WAS_NV_T320_CTRL_STRU;
/*****************************************************************************
 结构名    : WAS_CSFB_MCC_BAND_STRU
 协议表格  :
 ASN.1描述 :
 结构说明  :国家定制全频带搜索的band数据结构
*****************************************************************************/
typedef struct
{
    WAS_PLMN_ID_STRU        stPlmn;
    VOS_UINT32              ulSupportWBand;
}WAS_CSFB_MCC_BAND_STRU;

/*****************************************************************************
 结构名    : WAS_CSFB_MCC_BAND_INFO_STRU
 协议表格  :
 ASN.1描述 :
 结构说明  : CSFB时根据国家定制全频带搜索的band
*****************************************************************************/
typedef struct
{
    VOS_UINT32                   ulMccNum;                                      /* 指示多少组MCC有效 */
    WAS_CSFB_MCC_BAND_STRU       astUeCapMccBand[WAS_MAX_CSFB_MCC_BAND_NUM];
}WAS_CSFB_MCC_BAND_INFO_STRU;
/*****************************************************************************
 结构名    : WAS_NV_DMCR_CTRL_INFO_STRU
 结构说明  : DMCR开关
 修改历史  :
 1.日    期    : 2015年2月6日
   作    者    : 00134354
   修改内容    : 新建结构体
*****************************************************************************/
typedef struct
{
    PS_BOOL_ENUM_UINT8                     enCsDmcrFlg;            /* L2W重定向cs业务或CSFB的搜网场景，DMCR开关 */
    PS_BOOL_ENUM_UINT8                     enPsDmcrFlg;            /* L2W重定向，ps业务DMCR开关 */
    PS_BOOL_ENUM_UINT8                     enCuDmcrFlg;            /* CU场景的DMCR开关 */
    VOS_UINT8                              ucReserve1;            /* 保留位 */
    VOS_UINT8                              ucReserve2;            /* 保留位 */
    VOS_UINT8                              ucReserve3;            /* 保留位 */
    VOS_UINT8                              ucReserve4;            /* 保留位 */
    VOS_UINT8                              ucReserve5;            /* 保留位 */
}WAS_NV_DMCR_CTRL_INFO_STRU;

/*****************************************************************************
 结构名    : WAS_CSFB_SEARCH_CTRL_INFO_STRU
 协议表格  :
 ASN.1描述 :
 结构说明  : CSFB时根据定时搜索检测小区
*****************************************************************************/
typedef struct
{
    VOS_UINT8                          ucCsfbSearchCtrlInfo;               /* CSFB时W下搜网的控制NV,第1bit表示是否搜索检测小区
                                                                              第2bit表示是否优先驻留指定小区中最强的小区 */
    VOS_UINT8                          ucCsfbDetectCellNum;                /* 搜索检测小区的个数 */
    VOS_UINT8                          ucCsfbReprotCellNum;                /* 指定频点搜索时上报的小区个数 */
    VOS_UINT8                          ucReserve1;
}WAS_CSFB_SEARCH_CTRL_INFO_STRU;
/*****************************************************************************
 结构名    : WAS_AC_CTRL_INFO_STRU
 协议表格  :
 ASN.1描述 :
 结构说明  : 连接态不检查AC接入信息控制NV
*****************************************************************************/
typedef struct
{
    VOS_UINT8                          ucIgnorAcInfo;                      /* 连接态不检查AC接入信息 */
    VOS_UINT8                          ucReserve1;
    VOS_UINT8                          ucReserve2;
    VOS_UINT8                          ucReserve3;
}WAS_AC_CTRL_INFO_STRU;

/*****************************************************************************
 结构名    : WAS_NV_RPT_CONN_LOC_INFO_STRU
 协议表格  :
 ASN.1描述 :
 结构说明  : 上报连接态位置信息开关
*****************************************************************************/
typedef struct
{
    PS_BOOL_ENUM_UINT8                     enRptConnLocInfoFlg;                 /* 上报连接态位置信息开关 */
    VOS_UINT8                              ucRcvDchSysInfoTimerLen;             /* DCH下解广播保护时间，单位s */
    VOS_UINT8                              aucReserve1;
    VOS_UINT8                              aucReserve2;
}WAS_NV_RPT_CONN_LOC_INFO_STRU;

/*****************************************************************************
 结构名    : WAS_NV_RADOM_ACC_CTRL_STRU
 结构说明  : 随机接入控制NV
 修改历史  :
 1.日    期    : 2015年6月15日
   作    者    : j00169676
   修改内容    : 新建结构体
*****************************************************************************/
typedef struct
{
    PS_BOOL_ENUM_UINT8                              enModifyN300Flg;                /* 是否定制N300 */
    VOS_UINT8                                       ucN300Num;                      /* 定制N300的次数 */
    VOS_UINT8                                       aucReserve1;                    /* 保留位 */
    VOS_UINT8                                       aucReserve2;                    /* 保留位 */
}WAS_NV_RADOM_ACC_CTRL_STRU;

/*****************************************************************************
 结构名    : WAS_EUTRA_CELL_RESEL_CTRL_INFO_STRU
 协议表格  :
 ASN.1描述 :
 结构说明  : W2L重选相关定制参数，用于解决3G、4G制式之间平凡切换的问题
*****************************************************************************/
typedef struct
{
    VOS_UINT8                          ucJudgeL2WReselOrRedirTimeLen;           /* 在该定时器规定时长内判断是否发生L2W重选或重定向 */
    VOS_UINT8                          ucL2WReselOrRedirMaxNum;                 /* 长度为ucJudgeL2WReselOrRedirTimeLen时间内从L模重选或重定向到W模的最大次数 */
    VOS_UINT8                          ucW2LReselPenalTimeLen;                  /* W2L重选惩罚定时器时长 */
    VOS_UINT8                          ucW2LReselOffset;                        /* 当惩罚定时器启动时，W2L重选偏置参数 */
}WAS_EUTRA_CELL_RESEL_CTRL_INFO_STRU;
/*****************************************************************************
 结构名    : WAS_NV_SBM_CUSTOM_DCDPA_CTRL_STRU
 结构说明  : 软银定制动态适配DCDPA,此NV依赖与3001
 修改历史  :
 1.日    期    : 2015年5月4日
   作    者    : x81004927 
   修改内容    : 新建结构体
*****************************************************************************/
typedef struct
{
    PS_BOOL_ENUM_UINT8            enSbmUnSupDcdpa;
    PS_BOOL_ENUM_UINT8            enEmUnSupDcdpa;
    PS_BOOL_ENUM_UINT8            enOtherUnSupDcdpaInJapan;
    PS_BOOL_ENUM_UINT8            enUnSupDcdpaOutJapan;
    VOS_UINT8                     aucReserve1;                  /* 保留位 */
    VOS_UINT8                     aucReserve2;                  /* 保留位 */
    VOS_UINT8                     aucReserve3;                  /* 保留位 */
    VOS_UINT8                     aucReserve4;                  /* 保留位 */
}WAS_NV_SBM_CUSTOM_DCDPA_CTRL_STRU;

/*****************************************************************************
 结构名    : WAS_NV_SBM_CUSTOM_LTE_BAND_INFO_STRU
 结构说明  : 软银双imsi开关和MCC信息,LTE预制的band信息
*****************************************************************************/
typedef struct
{
    VOS_UINT8                           ucSbmCustomSrchFlg; /*  SBm 搜网 开关，LTE模使用，用于控制双IMSI方案和搜网方案*/
    VOS_UINT8                           aucReserve[3];          /* 保留位 */
    VOS_UINT32                          aulSbmSupBandInJapan[2];         /* 软银在日本国内支持的band，如果是全1则认为支持的band不做限制，支持UE支持的所有band */
    VOS_UINT32                          aulEmSupBandInJapan[2];          /* EM在日本国内支持的band，如果是全1则认为支持的band不做限制，支持UE支持的所有band */
    VOS_UINT32                          aulOtherOperateSupBandInJapan[2];/* 其他运营商在日本国内支持的band，如果是全1则认为支持的band不做限制，支持UE支持的所有band */
    VOS_UINT32                          aulSupBandOutJapan[2];           /* 日本国外支持的band,如果全1则认为支持的band不做限制，支持UE支持的所有band */
} WAS_NV_SBM_CUSTOM_LTE_BAND_INFO_STRU;
/*****************************************************************************
 结构名    : WAS_NV_CAPBILITY_FDDLIST_CTRL_STRU
 结构说明  : FDD LIST能力上报控制NV
 修改历史  :
 1.日    期    : 2015年7月15日
   作    者    : j00169676
   修改内容    : 新建结构体
*****************************************************************************/
typedef struct
{
    PS_BOOL_ENUM_UINT8                              enFddList3CtrFlg;                /* 是否定制FDD LIST能力上报 */
    PS_BOOL_ENUM_UINT8                              enInterHoShortFddList3Flg;       /* 是否定制GSM查询能力时，裁剪LTE能力 */
    PS_BOOL_ENUM_UINT8                              enShortExternIndFlg;             /* 是否裁剪externInd的上报 */
    VOS_UINT8                                       aucReserve1;                     /* 保留位 */
}WAS_NV_CAPBILITY_FDDLIST_CTRL_STRU;

/*****************************************************************************
 结构名    : WAS_NV_CELL_INDI_OFFSET_CTRL_INFO_STRU
 协议表格  :
 ASN.1描述 :
 结构说明  :D态下测量评估时，小区偏置参数控制NV
*****************************************************************************/
typedef struct
{
    PS_BOOL_ENUM_UINT8                 enModifyCellIndiOffsetFlg;               /* 是否定制小区偏置的标记 */
    VOS_INT8                           cCellIndiOffsetHighThreshold;            /* 用于判断是否需要定制小区偏置的最高门限 */
    VOS_INT8                           cCellIndiOffsetLowThreshold;             /* 用于判断是否需要定制小区偏置的最低门限 */
    VOS_UINT8                          ucModifyOffsetForHighThreshold;          /* 用于修正超过最高门限的小区偏置的值 */
    VOS_UINT8                          ucModifyOffsetForLowThreshold;           /* 用于修正低于最低门限的小区偏置的值 */
    VOS_UINT8                          ucReserve1;                              /* 保留位 */
    VOS_UINT8                          ucReserve2;                              /* 保留位 */
    VOS_UINT8                          ucReserve3;                              /* 保留位 */
}WAS_NV_CELL_INDI_OFFSET_CTRL_INFO_STRU;
/*****************************************************************************
 结构名    : WAS_NV_NOISE_OPTMIZE_CTRL_STRU
 结构说明  : 流水声优化控制NV
 修改历史  :
 1.日    期    : 2015年7月15日
   作    者    : j00169676
   修改内容    : 新建结构体
*****************************************************************************/
typedef struct
{
    PS_BOOL_ENUM_UINT8                              enNoiseOptmizeFlg;              /* 是否定制流水声检测 */
    PS_BOOL_ENUM_UINT8                              enSilenceFlg;                   /* 是否启动静默音标记 */
    VOS_UINT8                                       ucTimerLen;                     /* 单位s */
    VOS_UINT8                                       ucReserve1;                     /* 保留位 */
}WAS_NV_NOISE_OPTIMIZE_CTRL_STRU;
/*****************************************************************************
 结构名    : WAS_NV_CU_CELL_SEARCH_CTRL_INFO_STRU
 协议表格  :
 ASN.1描述 :
 结构说明  :WAS CU搜网优化控制NV
*****************************************************************************/
typedef struct
{
    PS_BOOL_ENUM_UINT8                 enSearchCampCellFlg;         /* rl fail是否先搜之前驻留的频点搜网 */
    VOS_INT8                           cCuRSSIThreshold;            /* rl fail搜网粗扫门限 */
    PS_BOOL_ENUM_UINT8                 enCuPschSrchFlg;             /* rl fail搜网是否需要细扫 */
    VOS_UINT8                          ucCuSpecCellNum;             /* rl fail粗扫细扫后搜网发起指定扰码搜索，物理层上报该频点上最强小区的个数 */
    VOS_UINT8                          ucCuSpecFreqCellNum;         /* rl fail粗扫细扫后搜网发起指定频点，物理层上报该频点上最强小区的个数 */   
    VOS_UINT8                          ucReserve1;                  /* 保留位 */
    VOS_UINT8                          ucReserve2;                  /* 保留位 */
    VOS_UINT8                          ucReserve3;                  /* 保留位 */    
}WAS_NV_CU_CELL_SEARCH_CTRL_INFO_STRU;


/*****************************************************************************
 结构名    : WAS_NV_CLOUD_FREQ_STRATEGY_INFO_STRU
 协议表格  :
 ASN.1描述 :
 结构说明  :WAS 云通信控制NV,非NV结构，从NV中读取后保存nv的结构
*****************************************************************************/
typedef struct
{
    PS_BOOL_ENUM_UINT8                 enCloudEnableFlg;              /* 云通信NV开关是否打开 */
    PS_BOOL_ENUM_UINT8                 enWcdmaPrefFreqFlg;            /* 云通信功能打开时，WCDMA运营商频点是否从云端获取 */
    PS_BOOL_ENUM_UINT8                 enWcdmaPrefBandFlg;            /* 云通信功能打开时，WCDMA是否发起云端预置band的搜索 */
    VOS_UINT8                          ucReserve1;                    /* 保留位 */    
}WAS_NV_CLOUD_STRATEGY_INFO_STRU;

/*****************************************************************************
 结 构 名  : WAS_NV_NETWORK_SEARCH_CUSTOMIZE_CFG_STRU
 结构说明  : 网络搜索定制NV
 修改历史  :
  1.日  期   : 2015年10月19日
    作  者   : w00134354
    修改内容 : 新生成结构

*****************************************************************************/
typedef struct
{
    VOS_UINT32              ulHistoryFreqEnableBitmap;                          /* 历史频点搜索流程使能bit位 */
    VOS_UINT32              ulOperatorSrchEnableBitmap;                         /* 运营商搜网搜索流程使能bit位 */
    VOS_UINT32              ulFullBandableBitmap;                               /* 全频段搜索流程使能bit位 */
    VOS_UINT32              ulCloudFreqFromCssBitmap;                           /* 运营商频点从云端获取使能bit位 */
    VOS_UINT32              ulPreferBandFromCssBitmap;                          /* PreferBand从云端获取使能bit位 */    
    VOS_UINT32              ulReserved1;                                        /* 保留位 */
    VOS_UINT32              ulReserved2;                                        /* 保留位 */
    VOS_UINT32              ulReserved3;                                        /* 保留位 */
    VOS_UINT32              ulReserved4;                                        /* 保留位 */
    VOS_UINT32              ulReserved5;                                        /* 保留位 */
    VOS_UINT32              ulReserved6;                                        /* 保留位 */
    VOS_UINT32              ulReserved7;                                        /* 保留位 */
    VOS_UINT32              ulReserved8;                                        /* 保留位 */
    VOS_UINT32              ulReserved9;                                        /* 保留位 */
    VOS_UINT32              ulReserved10;                                       /* 保留位 */
}WAS_NV_NETWORK_SEARCH_CUSTOMIZE_CFG_STRU;

/*****************************************************************************
 结 构 名  : WAS_NV_T314_CFG_STRU
 结构说明  : 网络没有配置T314时使用NV定制默认参数
 修改历史  :
  1.日  期   : 2015年12月29日
    作  者   : j00169676
    修改内容 : 新生成结构
*****************************************************************************/
typedef struct
{
    PS_BOOL_ENUM_UINT8      enCfgOnOffFlg;                                      /* 定制是否生效开关 */
    VOS_UINT8               ucT314DefaultValue;                                 /* 网络配置T314为0时使用该值 */
    VOS_UINT8               ucReserved1;                                        /* 保留位 */
    VOS_UINT8               ucReserved2;                                        /* 保留位 */
}WAS_NV_T314_CFG_STRU;
/*****************************************************************************
 结构名    : WAS_NVIM_GSM_MEAS_OFFSET_STRU
 结构说明  : GSM测量启动门限相关NV
*****************************************************************************/
typedef struct
{
    PS_BOOL_ENUM_UINT8              enGsmMeasUseDefaultSCriterionFlg;           /* 阻止到GSM重选，GSM测量启动判决时，S准则使用默认网络配置参数-18和-58 */
    PS_BOOL_ENUM_UINT8              enOutOfServiceUseDefaultSCriterionFlg;      /* 出服务区判决时是否使用默认S准则标记 */
    VOS_UINT8                       ucGsmMeasRscpOffset;                        /* 在启停异系统测量门限上减去的迟滞，RSCP迟滞 */
    VOS_UINT8                       ucReserve1;
    VOS_INT8                        cQRxlevmin;
    VOS_INT8                        cQQualmin;
    VOS_UINT8                       ucReserve2;
    VOS_UINT8                       ucReserve3;
}WAS_NVIM_GSM_MEAS_OFFSET_STRU;

/*****************************************************************************
 结构名    : WAS_NVIM_W2L_RESEL_THRES_CFG_NV_STRU
 结构说明  : W2L重选优化门限相关NV
*****************************************************************************/
typedef struct
{
    VOS_UINT8                        ucFeatureSwitch;                        /* 功能开关*/
    VOS_UINT8                        ucReserve1;                             /* 保留位  */
    VOS_INT16                        sRsrqThres;                             /* L的服务小区Rsrq私有门限，单位1dB */
    VOS_INT16                        sDeltaRsrq;                             /* 异系统重选回L的RSRQ约束的迟滞门限，单位1dB */
    VOS_INT16                        sUtraRscp;                              /* 低于此值时，utra重选回L按原流程处理，单位1dB */
    VOS_INT16                        sUtraEcn0;                              /* 低于此值时，utra重选回L按原流程处理，单位1dB */
    VOS_UINT16                       ucReserve2;                             /* 保留位 */
}WAS_NVIM_W2L_RESEL_THRES_CFG_NV_STRU;

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

#endif /* end of WasNvInterface.h */
