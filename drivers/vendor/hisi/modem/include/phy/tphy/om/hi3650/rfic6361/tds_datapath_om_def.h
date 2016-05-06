/******************************************************************************

                  版权所有 (C), 2001-2011, 华为技术有限公司

 ******************************************************************************
  文 件 名   : tds_datapath_om_def.h
  版 本 号   : 初稿
  作    者   : mah
  生成日期   : 2012年10月8日
  最近修改   :
  功能描述   : TDS  数据通道OM接口定义
  函数列表   :
  修改历史   :
  1.日    期   : 2012年10月8日
    作    者   : mah
    修改内容   : 创建文件

******************************************************************************/
#ifndef __TDS_DATAPATH_OM_DEF_H__
#define __TDS_DATAPATH_OM_DEF_H__

#include "om_base_def.h"
/*----------------------------------------------*
 * 宏定义                                       *
 *----------------------------------------------*/

/*----------------------------------------------*
 * 枚举定义                                       *
 *----------------------------------------------*/
typedef enum TDS_DATA_OM_REQ_MSGID
{
    TPHY_REQ_DATA_LONG_RX      =  OM_TCMD_ID(TPHY_DATA_MID, OM_TYPE_REQ, 0x1),
    TPHY_REQ_DATA_RXTS            =  OM_TCMD_ID(TPHY_DATA_MID, OM_TYPE_REQ, 0x2),
    TPHY_REQ_DATA_TXTS            =  OM_TCMD_ID(TPHY_DATA_MID, OM_TYPE_REQ, 0x3),
	TPHY_REQ_DATA_RPT_REQ             =  OM_TCMD_ID(TPHY_DATA_MID, OM_TYPE_REQ, 0x20),
}TDS_DATA_OM_REQ_MSGID_ENUM;

typedef enum TDS_DATA_OM_RPT_IND
{
    TPHY_DATA_LONGRX_IND     =  OM_TCMD_ID(TPHY_DATA_MID, OM_TYPE_IND, 0x0),   /*TDS?t???D??í3????êy*/
    TPHY_DATA_RXTS_IND         =  OM_TCMD_ID(TPHY_DATA_MID, OM_TYPE_IND, 0x1),   /*TDSèy??ê±???D??í3????êy*/
    TPHY_DATA_LONGTX_IND     =  OM_TCMD_ID(TPHY_DATA_MID, OM_TYPE_IND, 0x2),   /*TDSèy??tfp·￠?í?óê??D??í3????êy*/
    TPHY_DATA_TXTS_IND         =  OM_TCMD_ID(TPHY_DATA_MID, OM_TYPE_IND, 0x3),   /*TDSèy??HSUPA?D??í3????êy*/
    TPHY_DATA_HEADER_IND      =  OM_TCMD_ID(TPHY_DATA_MID, OM_TYPE_IND, 0x20),
	TPHY_DATA_TS		      =  OM_TCMD_ID(TPHY_DATA_MID, OM_TYPE_IND, 0x21),
	TPHY_DATA_DWPTS           =  OM_TCMD_ID(TPHY_DATA_MID, OM_TYPE_IND, 0x22),
	TPHY_DATA_MIDABLE        =  OM_TCMD_ID(TPHY_DATA_MID, OM_TYPE_IND, 0x23),
	TPHY_DATA_LONG_RX_PER_1024CHIP   =  OM_TCMD_ID(TPHY_DATA_MID, OM_TYPE_IND, 0x24)

}TDS_DATA_OM_RPT_ENUM;

typedef enum   TPHY_TDS_DATA_RPT_SWICH
{
	RPT_DIABLE,
	RPT_ENABLE
}TPHY_TDS_DATA_RPT_SWICH_ENUM;

typedef struct TPHY_TDS_DATA_RPT_REQ
{
	TPHY_TDS_DATA_RPT_SWICH_ENUM enReportAll;
	TPHY_TDS_DATA_RPT_SWICH_ENUM enReportTS;
	TPHY_TDS_DATA_RPT_SWICH_ENUM enReportDwpts;
	TPHY_TDS_DATA_RPT_SWICH_ENUM enReportMidable;
	TPHY_TDS_DATA_RPT_SWICH_ENUM enReportLongRxdata;
}TPHY_TDS_DATA_RPT_REQ_STRU;

typedef struct TDSP_TRACE_INFO
{
   UINT32 ulData[2];
}TPHY_TDS_TRACE_INFO_STRU;

typedef enum TDS_DATA_RPT_TYPE
{
    NOMAL_TDS_TS_DATA,
	DWPTS_DATA,
	MIDABL_DATA,
	LONG_RX_1024CHIP_DATA
}TDS_DATA_RPT_TYPE_ENUM;

typedef struct TPHY_TDS_DATA_RPT_HEADER
{
    UINT16 usSFN;
	UINT16 usTsNum;
	UINT32 usTimeStick;    /*¨o?à??¨￠*/
	TDS_DATA_RPT_TYPE_ENUM enDataType;
}TPHY_TDS_DATA_RPT_HEADER_STRU;
typedef struct TPHY_TDS_DATA_TS
{
	//TPHY_TDS_DATA_RPT_HEADER_STRU stHeader;
	UINT32 usData[TDS_TS_DATA_CHIPLEN];
}TPHY_TDS_DARA_TS_STRU;

typedef struct TPHY_TDS_DATA_DWPTS
{
	//TPHY_TDS_DATA_RPT_HEADER_STRU stHeader;
	UINT32 usData[TDS_DWPTS_CHIPLEN+32];
}TPHY_TDS_DARA_DWPTS_STRU;

typedef struct TPHY_TDS_DATA_MIDABL
{
	//TPHY_TDS_DATA_RPT_HEADER_STRU stHeader;
	UINT32 usData[TDS_MIDABL_CHIPLEN];
}TPHY_TDS_DARA_MIDABL_STRU;

typedef struct TPHY_TDS_DATA_1024CHIP
{
	//TPHY_TDS_DATA_RPT_HEADER_STRU stHeader;
	UINT32 usData[1024];
}TPHY_TDS_DARA_1024CHIP_STRU;
/*----------------------------------------------*
 * 结构体定义                                     *
 *----------------------------------------------*/
typedef struct TPHY_REQ_DATA_RX_LONG
{
    OM_REQ_ENABLE_ENUM_UINT16  enDatReqEna;   /*获取TDS  长收数据使能开关，前端接收数据打开时有效*/
    UINT16 usTotalGain;
    UINT16 usFreq;
    UINT16 usFourthFastFlg;
}TPHY_REQ_DATA_RX_LONG_STRU;

typedef struct TPHY_REQ_DATA_RXTS
{
    OM_REQ_ENABLE_ENUM_UINT16  enIntStatInfoEna; /*获取TDS 特定时隙接收数据使能开关，前端接收数据打开时单次生效，数据采集完后关闭*/
    UINT16 usTs;    /*时隙号*/
    UINT16 usTotalGain;
    UINT16 usFreq;
    UINT16 usFourthFastFlg;
    UINT16 usRes;
}TPHY_REQ_DATA_RXTS_STRU;

typedef struct TPHY_REQ_DATA_TXTS
{
    OM_REQ_ENABLE_ENUM_UINT16  enIntStatInfoEna; /*获取TDS 特定时隙发送数据使能开关，前端接收数据打开时单次生效，数据采集完后关闭*/
    UINT16 usTs;    /*时隙号*/
    UINT16 usTxPow;
    UINT16 usFreq;
}TPHY_REQ_DATA_TXTS_STRU;

typedef struct TPHY_DATA_OM_CTRL
{
    UINT16 usLongRxTaskFlg; /*配置长收标记*/
    UINT16 usTdsOmEn;
}TPHY_DATA_OM_CTRL_STRU;


/*----------------------------------------------*
 * 外部变量说明                                 *
 *----------------------------------------------*/

/*----------------------------------------------*
 * 外部函数原型说明                             *
 *----------------------------------------------*/

/*----------------------------------------------*
 * 内部函数原型说明                             *
 *----------------------------------------------*/



/*----------------------------------------------*
 * 全局变量                                     *
 *----------------------------------------------*/

/*----------------------------------------------*
 * 模块级变量                                   *
 *----------------------------------------------*/

#endif
