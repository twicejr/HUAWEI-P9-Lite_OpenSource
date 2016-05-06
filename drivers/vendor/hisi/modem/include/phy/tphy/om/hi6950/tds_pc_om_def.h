/******************************************************************************

                  版权所有 (C), 2001-2011, 华为技术有限公司

******************************************************************************
  文 件 名   : tds_pc_om.h
  版 本 号   : 初稿
  作    者   : wangchao
  生成日期   : 2012年11月12日
  最近修改   :
  功能描述   : 功率控制OM上报
  函数列表   :
  修改历史   :
  1.日    期   : 2012年11月12日
     作    者   : wangchao
    修改内容   : 创建文件

******************************************************************************/

#ifndef TDS_PC_OM_DEF_H_
#define TDS_PC_OM_DEF_H_



#ifdef __cplusplus
#if __cplusplus
    extern "C"{
#endif
#endif /* __cplusplus */
/************************************************************
                     包含其它模块的头文件
************************************************************/
//#include "balong_lte_dsp.h"
//#include "type_define.h"
#include "om_base_def.h"



/************************************************************
                               宏定义
************************************************************/



/************************************************************
                             数据结构定义
************************************************************/

typedef struct
{
	UINT16      usSysSfn;        /*系统子帧号*/
    UINT16      usSysTs;         /*系统时隙号*/
    UINT16      usChipTime;      /*当前chip位置*/
    UINT16*		pAddr;
}TPHY_OM_TRACE_POWERCTRL_STRU;


typedef struct
{
    UINT8  ucDpchOmCtrl;
    UINT8  ucUppchOmCtrl;
    UINT8  ucPrachOmCtrl;
    UINT8  ucHssichOmCtrl;
    UINT8  ucEagchOmCtrl;
    UINT8  ucHsscchOmCtrl;
    UINT8  ucEpuchOmCtrl;
} TDS_POWERCTRL_OMCTRL_STRU;


typedef enum
{
    TPHY_REQ_PC       = OM_TCMD_ID(TPHY_PC_MID, OM_TYPE_REQ, 0x0),

}TPHY_PC_REQ_ENUM;


typedef enum
{
    TPHY_TRACE_ULPC_UPPCH       = OM_TCMD_ID(TPHY_PC_MID, OM_TYPE_TRACE, 0x1),
    TPHY_TRACE_ULPC_RACH        = OM_TCMD_ID(TPHY_PC_MID, OM_TYPE_TRACE, 0x2),
    TPHY_TRACE_ULPC_DPCH        = OM_TCMD_ID(TPHY_PC_MID, OM_TYPE_TRACE, 0x3),
    TPHY_TRACE_ULPC_EPUCH       = OM_TCMD_ID(TPHY_PC_MID, OM_TYPE_TRACE, 0x4),
    TPHY_TRACE_ULPC_HSSICH      = OM_TCMD_ID(TPHY_PC_MID, OM_TYPE_TRACE, 0x5),
    TPHY_TRACE_DWPC_DPCH        = OM_TCMD_ID(TPHY_PC_MID, OM_TYPE_TRACE, 0x6),
    TPHY_TRACE_DWPC_EAGCH       = OM_TCMD_ID(TPHY_PC_MID, OM_TYPE_TRACE, 0x7),
    TPHY_TRACE_DWPC_HSSCCH      = OM_TCMD_ID(TPHY_PC_MID, OM_TYPE_TRACE, 0x8),
    
}TPHY_PC_TRACE_ENUM;

typedef UINT16 TPHY_PC_TRACE_ENUM_UINT16;

typedef enum
{
	/*原语参数错误*/
    TPHY_ERROR_PC_DPCHPARA_ERROR            = OM_TCMD_ID(TPHY_PC_MID, OM_TYPE_ERROR, 0x1),
    TPHY_ERROR_PC_EPUCH_PARA_ERROR          = OM_TCMD_ID(TPHY_PC_MID, OM_TYPE_ERROR, 0x2),
    TPHY_ERROR_PC_RACH_PARA_ERROR           = OM_TCMD_ID(TPHY_PC_MID, OM_TYPE_ERROR, 0x3),
    TPHY_ERROR_PC_HSSICH_PARA_ERROR         = OM_TCMD_ID(TPHY_PC_MID, OM_TYPE_ERROR, 0x4),
    TPHY_ERROR_PC_UPPCH_PARA_ERROR          = OM_TCMD_ID(TPHY_PC_MID, OM_TYPE_ERROR, 0x5),
    TPHY_ERROR_PC_EAGCH_PARA_ERROR          = OM_TCMD_ID(TPHY_PC_MID, OM_TYPE_ERROR, 0x6),
    TPHY_ERROR_PC_HSSCCH_PARA_ERROR         = OM_TCMD_ID(TPHY_PC_MID, OM_TYPE_ERROR, 0x7),
    
    TPHY_ERROR_PC_DIV_ZREO                  = OM_TCMD_ID(TPHY_PC_MID, OM_TYPE_ERROR, 0x8),
    TPHY_ERROR_PC_MOD_ZREO                  = OM_TCMD_ID(TPHY_PC_MID, OM_TYPE_ERROR, 0x9),
}TPHY_PC_ERROR_ENUM;
typedef UINT16 TPHY_PC_ERROR_ENUM_UINT16;
typedef struct
{
	UINT16      usTPC;        /*系统子帧号*/
    UINT16      usContinuousSameTPCCnt;         /*系统时隙号*/
    INT32       lMeasSir;      /*当前chip位置*/
    INT32       lTxtargetSir;
    UINT16      usTotalErrTbNum;
    UINT16      usRxErrFlag;
    UINT16      usDpchSirSbErrCnt;
    UINT16		usrev;
}TPHY_OM_TRACE_POWERCTRL_DWDPCH_STRU;

typedef struct
{
	INT16       sDpchTxPower;
    INT16       sTpcValue;
    UINT16      usDtxFlag;
}TPHY_OM_TRACE_POWERCTRL_ULDPCH_STRU;

typedef struct
{
	INT16       sUpPCHTxPower;
    UINT16      usAccMaxAllowedUlTxPower;
}TPHY_OM_TRACE_POWERCTRL_UPPCH_STRU;

typedef struct
{
	INT16      sRachTxPower;
}TPHY_OM_TRACE_POWERCTRL_PRACH_STRU;

typedef struct
{
	INT16       sEpuchTxPower;        /*系统子帧号*/
    UINT16      usEpuchReferenceBetaE;         /*系统时隙号*/
    UINT16      usEpuchPathLoss;      /*当前chip位置*/
    INT16       sPebaseAddTpc;
    UINT16      usScheduleInd;
    UINT16      usAgchTpc;
    UINT16      usHichTpc;
}TPHY_OM_TRACE_POWERCTRL_EPUCH_STRU;

typedef struct
{
	INT16       sHsSichTxPower;        /*系统子帧号*/
    UINT16      usHsSichTpc;         /*系统时隙号*/
    UINT16      usScchSir;      /*当前chip位置*/
    UINT16      usSichIntervalsCnt;
    UINT16      usDpchPathLoss;
}TPHY_OM_TRACE_POWERCTRL_HSSICH_STRU;

typedef struct
{
	UINT16      usTPC;        /*系统子帧号*/
    UINT16      usLostCnt;         /*系统时隙号*/
    UINT16      usHcsn;      /*当前chip位置*/
    UINT16      usExeFrame;
    INT32       lMeasSir;
    INT32       lTxtargetSir;
}TPHY_OM_TRACE_POWERCTRL_EAGCHHSSCCH_STRU;



/************************************************************
                             函数声明
************************************************************/


#ifdef __cplusplus
#if __cplusplus
}
#endif
#endif /* __cplusplus */

#endif               /* define TDS_PC_OM_H_   */

