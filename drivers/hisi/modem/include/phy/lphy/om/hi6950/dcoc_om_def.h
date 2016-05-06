/******************************************************************************

                  版权所有 (C), 2001-2011, 华为技术有限公司

******************************************************************************
 文 件 名   : dcoc_om_def.h
 版 本 号   : 初稿
 作    者   : Shen Guang
 生成日期   : 2011年06月23日
 最近修改   :
 功能描述   : DCOC OM的头文件
 函数列表   :
 修改历史   :
 1.日    期   : 2011年06月23日
   作    者   : Shen Guang
   修改内容   : 创建文件
******************************************************************************/


#ifndef __DCOC_OM_DEF_H__
#define __DCOC_OM_DEF_H__


#ifdef __cplusplus
#if __cplusplus
extern "C"{
#endif
#endif /* __cplusplus */
/************************************************************
                     包含其它模块的头文件
************************************************************/

/************************************************************
                               宏定义
************************************************************/

/************************************************************
                             数据结构定义
************************************************************/

/************************************************************
                             接口函数声明
 ************************************************************/

/************************************************************
                           1. REQ命令和对应的数据结构定义
************************************************************/

typedef enum
{
    LPHY_REQ_DCOC_ENA                       = OM_CMD_ID(LPHY_DCOC_MID, OM_TYPE_REQ, 0x0),
    LPHY_REQ_DCOC_UPDATE_CONFIG_ENA,
    LPHY_REQ_DCOC_FIXED_VALUE_ENA,
    LPHY_REQ_DCOC_SHIFT_BIT_CONFIG_ENA,
    LPHY_REQ_DCOC_ACC_RESET_ENA,
    LPHY_REQ_DCOC_SWITCH_MODE_ENA,
	LPHY_REQ_DCOC_DC_RPT_EVERY_FRM_ENA,    
	LPHY_REQ_DCOC_INTER_RPT_ENA,
	LPHY_REQ_DCOC_INTRA_RPT_ENA
}LPHY_REQ_DCOC_ENUM;

typedef enum
{
    DCOC_SWITCH_OFF = 0,
    DCOC_SWITCH_ON,
}DCOC_SWITCH_ENUM;

typedef UINT16 DCOC_SWITCH_ENUM_UINT16;
typedef UINT32 DCOC_SWITCH_ENUM_UINT32;


typedef enum
{
    DCOC_ON_AIR = 0,
    DCOC_FIXED,
    DCOC_RESERVED,
}DCOC_FIX_ENABLE_ENUM;

typedef struct
{
    DCOC_SWITCH_ENUM_UINT32   enEnable;
    DCOC_SWITCH_ENUM_UINT16   enSwitch[4];//[cc0 ~cc3]
}LPHY_REQ_DCOC_ENA_STRU;

typedef enum
{
    DCOC_SAMPLE = 0,
    DCOC_SYMBLE,
    DCOC_SUBFRAME,
}DCOC_UPDATECONFIG_ENUM;

typedef enum
{
    DCOC_NORMAL= 0,
    DCOC_FAST,
}DCOC_MODE_ENUM;

typedef struct
{
    DCOC_SWITCH_ENUM_UINT32   enEnable;
    DCOC_UPDATECONFIG_ENUM    enUpdateConfig[4];
    DCOC_MODE_ENUM            enModeConfig[4];
}LPHY_REQ_DCOC_UPDATE_CONFIG_ENA_STRU;

typedef struct
{
    UINT32                ulRx0DcRegValue;
    UINT32                ulRx1DcRegValue;
    UINT32                ulRx0AccIRegValue;
    UINT32                ulRx1AccIRegValue;
    UINT32                ulRx0AccQRegValue;  
    UINT32                ulRx1AccQRegValue;
}LPHY_AGC_OM_DCOC_CFG_STRU;

typedef struct
{
    DCOC_SWITCH_ENUM_UINT32    enEnable;
    DCOC_FIX_ENABLE_ENUM  enFixedEn[4];
	LPHY_AGC_OM_DCOC_CFG_STRU astDcocValue[4];//om for ca
}LPHY_REQ_DCOC_FIXED_VALUE_ENA_STRU;

typedef struct
{
    DCOC_SWITCH_ENUM_UINT32    enEnable;
    UINT32                ulShiftBitReg[4];
}LPHY_REQ_DCOC_SHIFT_BIT_CONFIG_ENA_STRU;

typedef struct
{
    DCOC_SWITCH_ENUM_UINT16    enEnable[4];
}LPHY_REQ_DCOC_ACC_RESET_ENA_STRU;

typedef enum
{
    DCOC_RECOVERY = 0,
    DCOC_UNCHANGED,
    DCOC_CLEAR,
}DCOC_SWITCH_FREQ_MODE_ENUM;
typedef UINT16 DCOC_SWITCH_FREQ_MODE_ENUM_UINT16;

typedef struct
{
    DCOC_SWITCH_ENUM_UINT16           enEnable;
    DCOC_SWITCH_FREQ_MODE_ENUM_UINT16 enSwitchMode;
}LPHY_REQ_DCOC_SWITCH_MODE_ENA_STRU;

typedef struct
{
    DCOC_SWITCH_ENUM_UINT32    enEnable;
}LPHY_REQ_DCOC_REPORT_ENA_STRU;

typedef struct
{
    DCOC_SWITCH_ENUM_UINT32    enEnable;
}LPHY_REQ_DCOC_BACK_REPORT_ENA_STRU;


typedef struct
{
	UINT32 ulDcocRx0;
	UINT32 ulAccI0;
	UINT32 ulAccQ0;
	UINT32 ulDcocRx1;
	UINT32 ulAccI1;
	UINT32 ulAccQ1; 
}LPHY_AGC_OM_DCOC_RPT_STRU;

typedef struct
{
	LPHY_AGC_OM_DCOC_RPT_STRU astDcocRpt[4];//[cc0~cc3]
}LPHY_SG_DCOC_REPORT_ENA_STRU;

typedef struct
{
	UINT32 ulDcocRx0;
	UINT32 ulAccI0;
	UINT32 ulAccQ0;
	UINT32 ulDcocRx1;
	UINT32 ulAccI1;
	UINT32 ulAccQ1;
}DCOC_ONE_RX_LEVEL_RPT_STRU;


typedef struct
{
    AGC_RF_IDX_ENUM_UINT16 enRFIdx;
    UINT16 usCHIdx;
    DCOC_ONE_RX_LEVEL_RPT_STRU stDcocOneRxLevelRpt;    
}DCOC_INTRA_BACK_RPT_STRU;

typedef struct
{
    AGC_RF_IDX_ENUM_UINT16 enRFIdx[2];
    UINT16 usBufIdx;
    UINT16 usReserved;
    DCOC_ONE_RX_LEVEL_RPT_STRU stDcocOneRxLevelRpt;    
}DCOC_INTER_BACK_RPT_STRU;


/************************************************************
                           3. Sg数据结构定义
************************************************************/
typedef enum
{
	LPHY_TRACE_DCOC_REPORT 	   = OM_CMD_ID(LPHY_DCOC_MID, OM_TYPE_TRACE, 0x1),
    LPHY_TRACE_DCOC_INTRA_BACK_REPORT,
    LPHY_TRACE_DCOC_INTRA_RESTORE_REPORT,
    LPHY_TRACE_DCOC_INTER_BACK_REPORT,
    LPHY_TRACE_DCOC_INTER_RESTORE_REPORT
}LPHY_SG_DCOC_ENUM;

/************************************************************
                           4. TRACE数据结构定义
************************************************************/
/************************************************************
                           5. ERROR数据结构定义
************************************************************/

typedef enum
{
    LPHY_ERROR_DCOC_ARRAY_INDEX         = OM_CMD_ID(LPHY_DCOC_MID, OM_TYPE_ERROR, 0x1),
    LPHY_ERROR_DCOC_CASE,
}LPHY_ERROR_DCOC_ENUM;

typedef struct
{
    UINT32      ulLineNum;//__LINE__
    UINT32      ulIncorrectValue;
}LPHY_ERROR_DCOC_ARRAY_INDEX_STRU;

typedef struct
{
    UINT32      ulLineNum;//__LINE__
    UINT32      ulCase;
}LPHY_ERROR_DCOC_CASE_STRU;

typedef union
{
    LPHY_ERROR_DCOC_ARRAY_INDEX_STRU   stDcocArrayIndexError;
    LPHY_ERROR_DCOC_CASE_STRU          stDcocCaseError;
}DCOC_OM_REPORT_UNION;

#ifdef __cplusplus
#if __cplusplus
}
#endif
#endif /* __cplusplus */


#endif /* __DCOC_OM_DEF_H__ */

