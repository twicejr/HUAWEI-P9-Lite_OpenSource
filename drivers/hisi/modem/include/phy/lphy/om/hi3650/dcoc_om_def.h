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
    LPHY_REQ_DCOC1_ENA          = OM_CMD_ID(LPHY_DCOC_MID, OM_TYPE_REQ, 0x0),
    LPHY_REQ_DCOC1_UPDATE_CONFIG_ENA,
    LPHY_REQ_DCOC1_FIXED_VALUE_ENA,
    LPHY_REQ_DCOC1_SHIFT_BIT_CONFIG_ENA,
    LPHY_REQ_DCOC1_ACC_RESET_ENA,

    //LPHY_REQ_DCOC2_ENA,
    //LPHY_REQ_DCOC2_UPDATE_CONFIG_ENA,
    //LPHY_REQ_DCOC2_FIXED_VALUE_ENA,
    //LPHY_REQ_DCOC2_SHIFT_BIT_CONFIG_ENA,
    //LPHY_REQ_DCOC2_ACC_RESET_ENA,

    LPHY_REQ_DCOC_SWITCH_MODE_ENA,
	LPHY_REQ_DCOC_REPORT_ENA,
    
}LPHY_REQ_DCOC_ENUM;

typedef enum
{
    DCOC_SWITCH_OFF = 0,
    DCOC_SWITCH_ON,
}DCOC_SWITCH_ENUM;

typedef enum
{
    DCOC_ON_AIR = 0,
    DCOC_FIXED,
    DCOC_RESERVED,
}DCOC_FIX_ENABLE_ENUM;

typedef struct
{
    OM_REQ_ENABLE_ENUM    enEnable;
    DCOC_SWITCH_ENUM      enSwitch;
}LPHY_REQ_DCOC_ENA_STRU;

typedef enum
{
    DCOC_SAMPLE = 0,
    DCOC_SYMBLE,
    DCOC_SUBFRAME,
}DCOC_UPDATECONFIG_ENUM;

typedef struct
{
    OM_REQ_ENABLE_ENUM        enEnable;
    DCOC_UPDATECONFIG_ENUM    enUpdateConfig;
}LPHY_REQ_DCOC_UPDATE_CONFIG_ENA_STRU;

typedef struct
{
    UINT32                ulRx0DcocRegValue;
    UINT32                ulRx1DcocRegValue;
}LPHY_AGC_OM_DCOC_CFG_STRU;

typedef struct
{
    OM_REQ_ENABLE_ENUM    enEnable;
    DCOC_FIX_ENABLE_ENUM  enFixedEn;
	LPHY_AGC_OM_DCOC_CFG_STRU astDcocValue[2];//om for ca
}LPHY_REQ_DCOC_FIXED_VALUE_ENA_STRU;

typedef struct
{
    OM_REQ_ENABLE_ENUM    enEnable;
    UINT32                ulShiftBitReg;
}LPHY_REQ_DCOC_SHIFT_BIT_CONFIG_ENA_STRU;

typedef struct
{
    OM_REQ_ENABLE_ENUM    enEnable;
}LPHY_REQ_DCOC_ACC_RESET_ENA_STRU;

typedef enum
{
    DCOC_RECOVERY = 0,
    DCOC_UNCHANGED,
    DCOC_CLEAR,
}DCOC_SWITCH_FREQ_MODE_ENUM;

typedef struct
{
    OM_REQ_ENABLE_ENUM    enEnable;
    DCOC_SWITCH_FREQ_MODE_ENUM      enSwitchMode;
}LPHY_REQ_DCOC_SWITCH_MODE_ENA_STRU;

typedef struct
{
    OM_REQ_ENABLE_ENUM    enEnable;
}LPHY_REQ_DCOC_REPORT_ENA_STRU;

typedef struct
{
	INT16 sI[2];
	INT16 sQ[2];
	//alex tbd dc vs vga	
}LPHY_AGC_OM_DCOC_RPT_STRU;

typedef struct
{
	LPHY_AGC_OM_DCOC_RPT_STRU astDcocRpt[2];//om for ca
}LPHY_SG_DCOC_REPORT_ENA_STRU;


/************************************************************
                           3. Sg数据结构定义
************************************************************/
typedef enum
{
	LPHY_SG_DCOC_REPORT_ENA 		= OM_CMD_ID(LPHY_DCOC_MID, OM_TYPE_SG, 0x0),
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

