/******************************************************************************

    Copyright(C)2008,Hisilicon Co. LTD.

 ******************************************************************************
  File Name       : Tds_MeasReturnRslt.h
  Description     : Tds_MeasReturnRslt.h header file
  History         :
     1.xiaojun 58160       2012-12-13     Draft Enact
     2.
******************************************************************************/

#ifndef __TDS_MEASRETURNRSLT_H__
#define __TDS_MEASRETURNRSLT_H__

#ifdef __cplusplus
#if __cplusplus
extern "C" {
#endif
#endif


/*****************************************************************************
  1 Include Headfile
*****************************************************************************/

#include  "type_define.h"



/*#pragma pack(4)*/

/*****************************************************************************
  2 macro
*****************************************************************************/


/*****************************************************************************
  3 Massage Declare
*****************************************************************************/


/*****************************************************************************
  4 Enum
*****************************************************************************/

/*****************************************************************************
 枚举名    : TDS_MEAS_ERR_CODE_ENUM_UINT32
 协议表格  :
 枚举说明  : TDS测量模块统一的错误原因值
*****************************************************************************/

enum TDS_MEAS_ERR_CODE_ENUM
{
    TDS_MEAS_SUCC               = 0,
    TDS_MEAS_FAIL               = 1, /* 通用的错误*/
    TDS_MEAS_NUM_OVER_FLOW      = 2, /*数越界*/
    TDS_MEAS_MAIL_BOX_FAIL      = 3,
    TDS_MEAS_SAVE_IE_FAIL       = 4,
    TDS_MEAS_PTR_NULL           = 5, /*指针为空*/
    TDS_MEAS_TIMER_OVER_LEN     = 6, /*时钟长度超过了最大长度*/
    TDS_MEAS_TIMER_EXHAUST,          /*时钟资源耗尽，个数已经到达最大*/
    TDS_MEAS_TIMER_START_FAIL,       /*时钟启动失败*/
    TDS_MEAS_TIMER_STOP_FAIL,        /*时钟停止失败*/
    TDS_MEAS_TIMER_EXPIRE,           /*10,时钟超时*/
    TDS_MEAS_OCCASION_TOO_MIN,       /*11,occaions太短*/
    TDS_MEAS_GET_AGC_GAIN_FAIL,      /*12,获取AGC失败*/

    TDS_MEAS_DATA_PATH_ABNORM_CB,    /*13,data path模块回调失败函数*/
    TDS_MEAS_FIFO_FULL,              /*14*/

    TDS_MEAS_WRONG_PRIME_MODE,       /*15*/
    TDS_MEAS_WRONG_IRAT_MODE,        /*16*/

    TDS_MEAS_CONN_IRAT_SUBFRM_INFO_ERR,/*17*/

    TDS_MEAS_STATE_MACHINE_ERR,       /*18*/
    TDS_MEAS_SLAVE_SLEEP,              /*19*/
	TDS_MEAS_PHY_STATE_ERR,           /*20,物理层的状态ics,idle,acc,dch等状态错误*/
	TDS_MEAS_PERIOD_SRCH_FAIL,        /*21周期搜返回错误*/
	TDS_MEAS_CFG_RCV_FAIL,            /*22周期搜返回错误*/
	TDS_MEAS_NO_CELL,                 /*23周期搜返回错误*/
	
	TDS_MEAS_TAS_OTHER_CELL,         /*24 tas测量同频非服务小区，上报结果*/
	
    /* 可增加其他的错误原因值*/

    TDS_MEAS_ERR_CODE_BUTT
};
typedef UINT32 TDS_MEAS_ERR_CODE_ENUM_UINT32;


/*****************************************************************************
   5 STRUCT
*****************************************************************************/


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










/*#if (VOS_OS_VER == VOS_WIN32)
#pragma pack()
#else
#pragma pack(0)
#endif*/




#ifdef __cplusplus
    #if __cplusplus
        }
    #endif
#endif

#endif /* end of Tds_MeasReturnRslt.h */
