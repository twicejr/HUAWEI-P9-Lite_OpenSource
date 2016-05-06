/******************************************************************************

                  版权所有 (C), 2001-2011, 华为技术有限公司

 ******************************************************************************
  文 件 名   : tds_int_om_def.h
  版 本 号   : 初稿
  作    者   : mah
  生成日期   : 2012年9月18日
  最近修改   :
  功能描述   : TDS 中断OM接口定义
  函数列表   :
  修改历史   :
  1.日    期   : 2012年9月18日
    作    者   : mah
    修改内容   : 创建文件

******************************************************************************/
#ifndef __TDS_INT_OM_DEF_H__
#define __TDS_INT_OM_DEF_H__


/*----------------------------------------------*
 * 枚举定义                                *
 *----------------------------------------------*/
typedef enum TDS_INT_OM_REQ_MSGID
{
    TPHY_REQ_INT_STAT_INFO_ID                    =  OM_TCMD_ID(TPHY_INT_MID, OM_TYPE_REQ, 0x0),
    TPHY_REQ_INT_SLOT_STAT_INFO_ID           =  OM_TCMD_ID(TPHY_INT_MID, OM_TYPE_REQ, 0x2),
}TDS_INT_OM_REQ_MSGID_ENUM;

typedef enum TDS_INT_STAT_RPT_IND
{
    TDS_INT_VEC_STAT_INFO_IND     =  OM_TCMD_ID(TPHY_INT_MID, OM_TYPE_IND, 0x0),     /*TDS二级中断统计计数*/
    TDS_INT_SLOT_STAT_INFO_IND    =  OM_TCMD_ID(TPHY_INT_MID, OM_TYPE_IND, 0x1),   /*TDS三级时隙中断统计计数*/
           
}TDS_INT_STAT_RPT_IND_ENUM;

/*----------------------------------------------*
 * 结构体定义                                   *
 *----------------------------------------------*/
typedef struct TPHY_REQ_INT_INFO
{
    OM_REQ_ENABLE_ENUM_UINT16  enIntStatInfoEna; /*获取TDS 中断统计信息，下发一次上报一次，不是一直生效*/
    UINT16 usRsvd  ;  
}TDS_REQ_INT_INFO_STRU;

typedef struct TDS_INT_STAT_INFO
{
    UINT32 ulSbfnIntCnt;     /*子帧中断计数*/
    UINT32 ulSlotIntCnt;     /*时隙中断计数*/
    UINT32 ulHsupaIntCnt;    /*HSUPA中断计数*/
    UINT32 ulViterbiIntCnt;  
    UINT32 ulTurboIntCnt;    
    UINT32 ulHarqIntCnt;    
    UINT32 ulTfpIntCnt; 
}TDS_INT_STAT_INFO_STRU;


typedef struct TDS_INT_STAT_SLOT_INFO
{
    UINT32 ulSlotIntCnt[TDS_SLOT_SCHDL_NUM_MAX]; /*TDS 时隙中断统计计数 */
          
}TDS_INT_STAT_SLOT_INFO_STRU;

/*各上报信息开关量顺序必须要相应的上报中断信息枚举顺序(TDS_INT_STAT_RPT_ENUM)一致*/
typedef struct TDS_INT_STAT_RPT_CTRL
{
    OM_REQ_ENABLE_ENUM_UINT16  enTdsIntRptSwitch;
    OM_REQ_ENABLE_ENUM_UINT16  enTdsSlotIntRptSwitch;          
}TDS_INT_STAT_RPT_CTRL_STRU;
/*----------------------------------------------*
 * 内部函数原型说明                             *
 *----------------------------------------------*/


/*----------------------------------------------*
 * 全局变量                                     *
 *----------------------------------------------*/
extern TDS_INT_STAT_INFO_STRU gstTdsIntStatInfo;           /*TDS 二级中断统计计数 */
extern TDS_INT_STAT_SLOT_INFO_STRU gstSlotIntCntInfo;      /*TDS 时隙中断统计计数 */
//extern TDS_INT_STAT_RPT_CTRL_STRU gstTdsIntStatRptCtrl;
/*----------------------------------------------*
 * 模块级变量                                   *
 *----------------------------------------------*/

/*----------------------------------------------*
 * 常量定义                                     *
 *----------------------------------------------*/

/*----------------------------------------------*
 * 宏定义                                       *
 *----------------------------------------------*/
#endif

