/******************************************************************************

                  版权所有 (C), 2001-2011, 华为技术有限公司

******************************************************************************
 文 件 名   : rxiq_om_def.h
 版 本 号   : 初稿
 作    者   : Shen Guang
 生成日期   : 2011年06月23日
 最近修改   :
 功能描述   : RXIQ OM的头文件
 函数列表   :
 修改历史   :
 1.日    期   : 2011年06月23日
   作    者   : Shen Guang
   修改内容   : 创建文件
******************************************************************************/


#ifndef __RXIQ_OM_DEF_H__
#define __RXIQ_OM_DEF_H__


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
	LPHY_TRACE_RXIQ_REPORT_ENA 		= OM_CMD_ID(LPHY_RXIQ_MID, OM_TYPE_TRACE, 0x0),
    LPHY_TRACE_RXIQ_BACK_REPORT_ENA    
}LPHY_SG_RXIQ_ENUM;

typedef enum
{
    LPHY_REQ_RXIQ_COMP_ENA          = OM_CMD_ID(LPHY_RXIQ_MID, OM_TYPE_REQ, 0x0),
    LPHY_REQ_RXIQ_CALC_ENA,
    LPHY_REQ_RXIQ_FIXED_VALUE_ENA,
    LPHY_REQ_RXIQ_REPORT_ENA,
	LPHY_REQ_RXIQ_LIMIT_ENA,
	LPHY_REQ_RXIQ_FILT_COEF_ENA
}LPHY_REQ_RXIQ_ENUM;

typedef enum
{
    RXIQ_SWITCH_OFF = 0,
    RXIQ_SWITCH_ON,
    RXIQ_SWITCH_RESERVED,
}RXIQ_SWITCH_ENUM;
typedef UINT16 RXIQ_SWITCH_ENUM_UINT32;

typedef struct
{
    RXIQ_SWITCH_ENUM_UINT32    enEnable;
}LPHY_REQ_RXIQ_ENA_STRU;

typedef enum
{
    RXIQ_ON_AIR = 0,
    RXIQ_FIXED,
}RXIQ_FIX_ENABLE_ENUM;
typedef UINT32 RXIQ_FIX_ENABLE_ENUM_UINT32;


typedef struct
{
    RXIQ_SWITCH_ENUM_UINT32      enEnable;
    RXIQ_FIX_ENABLE_ENUM_UINT32  enFixedEn;
    UINT32                aulRxiqReg[4][2];//[cc idx][rx num]
}LPHY_REQ_RXIQ_FIXED_VALUE_ENA_STRU;

typedef struct
{
    RXIQ_SWITCH_ENUM_UINT32    enEnable;
}LPHY_REQ_RXIQ_REPORT_ENA_STRU;

typedef struct
{
    RXIQ_SWITCH_ENUM_UINT32    enEnable;
    UINT32                ulAPLimitReg[4];
}LPHY_REQ_RXIQ_LIMIT_ENA_STRU;

typedef struct
{
    RXIQ_SWITCH_ENUM_UINT32    enEnable;
    
	struct {
		UINT8 ucWeight1;
		UINT8 ucWeight2;
		UINT8 ucThre;
		UINT8 uvRsv;
	} astCoef[4];
}LPHY_REQ_RXIQ_FILT_COEF_ENA_STRU;

typedef struct
{
	INT16 sA[2];
	INT16 sP[2];
    UINT32 ulRxiqCnt;
	//alex tbd dc vs vga
}LPHY_AGC_OM_RXIQ_RPT_ONE_CC_STRU;

typedef struct
{
	LPHY_AGC_OM_RXIQ_RPT_ONE_CC_STRU astRxiq[4];//om for ca
}LPHY_SG_RXIQ_REPORT_ENA_STRU;

typedef struct
{
    UINT16    usFreqInfo;
    UINT16    usReserved;
    UINT32    ulRxiqCnt[2];
    UINT32    aulRxiqCfg[LPHY_MAX_RX_ANTENNA_NUM];
}LPHY_SG_RXIQ_BACK_REPORT_ENA_STRU;



/************************************************************
                           3. Sg数据结构定义
************************************************************/


/************************************************************
                           4. TRACE数据结构定义
************************************************************/
/************************************************************
                           5. ERROR数据结构定义
************************************************************/

typedef enum
{
    LPHY_ERROR_RXIQ_ARRAY_INDEX         = OM_CMD_ID(LPHY_DCOC_MID, OM_TYPE_ERROR, 0x1),
    LPHY_ERROR_RXIQ_CASE,
}LPHY_ERROR_RXIQ_ENUM;

typedef struct
{
    UINT32      ulLineNum;//__LINE__
    UINT32      ulIncorrectValue;
}LPHY_ERROR_RXIQ_ARRAY_INDEX_STRU;

typedef struct
{
    UINT32      ulLineNum;//__LINE__
    UINT32      ulCase;
}LPHY_ERROR_RXIQ_CASE_STRU;

typedef union
{
    LPHY_ERROR_RXIQ_ARRAY_INDEX_STRU   stRxiqArrayIndexError;
    LPHY_ERROR_RXIQ_CASE_STRU          stRxiqCaseError;
}RXIQ_OM_REPORT_UNION;

#ifdef __cplusplus
#if __cplusplus
}
#endif
#endif /* __cplusplus */


#endif /* __RXIQ_OM_DEF_H__ */

