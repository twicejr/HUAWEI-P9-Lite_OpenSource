/******************************************************************************

                  版权所有 (C), 2001-2011, 华为技术有限公司

 ******************************************************************************
  文 件 名   : tds_cqi_om_def.h
  版 本 号   : 初稿
  作    者   : mah
  生成日期   : 2012年11月12日
  最近修改   :
  功能描述   : TDS CQI模块OM定义头文件
  函数列表   :
  修改历史   :
  1.日    期   : 2012年11月12日
    作    者   : mah
    修改内容   : 创建文件

******************************************************************************/
#ifndef __TDS_CQI_OM_DEF_H__
#define __TDS_CQI_OM_DEF_H__

#ifdef __cplusplus
#if __cplusplus
extern "C"{
#endif
#endif /* __cplusplus */

#include "om_base_def.h"

/*----------------------------------------------*
 * 宏定义                                       *
 *----------------------------------------------*/
#define TDS_MODE_BUTT  2
#define TPHY_REQ_SIR_OM_REP_SWITCH    OM_TCMD_ID(TPHY_CMU_MID, OM_TYPE_REQ, 0x0)
#define TPHY_REQ_SIR_ALGTH_PARA       OM_TCMD_ID(TPHY_CMU_MID, OM_TYPE_REQ, 0x1)
#define TPHY_REQ_SIR_STUB             OM_TCMD_ID(TPHY_CMU_MID, OM_TYPE_REQ, 0x2)

#define TPHY_REQ_CQI_OM_REP_SWITCH    OM_TCMD_ID(TPHY_CQI_MID, OM_TYPE_REQ, 0x0)
#define TPHY_REQ_CQI_ALGTH_PARA       OM_TCMD_ID(TPHY_CQI_MID, OM_TYPE_REQ, 0x1)
#define TPHY_REQ_CQI_STUB             OM_TCMD_ID(TPHY_CQI_MID, OM_TYPE_REQ, 0x2)

#define TPHY_REQ_VEL_ALGTH_PARA       OM_TCMD_ID(TPHY_CQI_MID, OM_TYPE_REQ, 0x4)
#define TPHY_REQ_VEL_STUB             OM_TCMD_ID(TPHY_CQI_MID, OM_TYPE_REQ, 0x5)

/*----------------------------------------------*
 * 枚举定义                                *
 *----------------------------------------------*/
typedef enum TDS_SIR_OM_RPT_IND
{
    TPHY_IND_SIR_DPCH    =  OM_TCMD_ID(TPHY_CMU_MID, OM_TYPE_IND, 0x0),
    TPHY_IND_SIR_HSSCCH  =  OM_TCMD_ID(TPHY_CMU_MID, OM_TYPE_IND, 0x1),
    TPHY_IND_SIR_EAGCH   =  OM_TCMD_ID(TPHY_CMU_MID, OM_TYPE_IND, 0x2),
    TPHY_IND_SIR_HSDSCH  =  OM_TCMD_ID(TPHY_CMU_MID, OM_TYPE_IND, 0x3),
    TPHY_IND_SIR_PCCPCH  =  OM_TCMD_ID(TPHY_CMU_MID, OM_TYPE_IND, 0x4),
    TPHY_IND_SIR_SCCPCH  =  OM_TCMD_ID(TPHY_CMU_MID, OM_TYPE_IND, 0x5),
    TPHY_IND_SIR_EHICH   =  OM_TCMD_ID(TPHY_CMU_MID, OM_TYPE_IND, 0x6),
}TDS_SIR_OM_RPT_IND_ENUM;

typedef enum TDS_CQI_OM_RPT_IND
{
    TPHY_IND_VEL_OUT         =  OM_TCMD_ID(TPHY_CQI_MID, OM_TYPE_IND, 0x0),
    TPHY_IND_CQI_OUT         =  OM_TCMD_ID(TPHY_CQI_MID, OM_TYPE_IND, 0x1),
    TPHY_IND_VEL_PROC_VAR    =  OM_TCMD_ID(TPHY_CQI_MID, OM_TYPE_IND, 0x2),
    TPHY_IND_CQI_PROC_VAR    =  OM_TCMD_ID(TPHY_CQI_MID, OM_TYPE_IND, 0x3),
}TDS_CQI_OM_RPT_IND_ENUM;
    
/*----------------------------------------------*
 * 结构定义                                                    *
 *----------------------------------------------*/
typedef enum TDS_SWITCH_FALG
{
    TDS_DISABLE = 0,
    TDS_ENABLE ,        
}TDS_SWITCH_FALG_ENUM;
#define TDS_SWITCH_FALG_ENUM_UINT16 UINT16

 /*TDS SIR计算算法可配参数结构定义*/
typedef struct TDS_SIR_ALG_PARA
{
    UINT16 usMaxSirSoftSyblNum[TDS_MODE_BUTT];    /*QPSK/16QAM调制时，SIR平滑使用的最大符号软值数据长度*/
    UINT16 usMaxSirCodeNum[TDS_MODE_BUTT];         /*QPSK/16QAM调制方式时，SIR平滑使用的最大符号软值数据长度*/
    UINT16 usMaxSirSlotSmoothNum;      /*SIR平滑时，最大的平滑时隙数目,取值1-31*/
    UINT16 usMaxSirSfSmoothNum;        /*SIR平滑时，最大的平滑子帧数目,取值1-31*/      
}TDS_SIR_ALG_PARA_STRU;

/*TDS SIR 结果打桩结构体定义*/
typedef struct TDS_SIR_STUB
{
    TDS_SWITCH_FALG_ENUM_UINT16 ulSirStubSwitch;     /*SIR打桩控制开关*/
	UINT16 usRsvd;
    INT32 lSir;            
}TDS_SIR_STUB_STRU;

 /*TDS 速度估计算法可配参数结构定义*/
typedef struct TDS_VEL_ALG_PARA
{
    UINT16 usVp;        /*信号功率统计周期，以子帧为单位*/
    UINT8 ucVelFadThrd; /*信号功率相邻子帧信号功率深衰门限*/
    UINT8 ucVelAwgnThrd;/*信号功率相邻子帧信号功率深衰门限*/
    UINT8 ucVelPowThrd; /*极慢衰落信道衰落门限*/
    UINT8 ucLrThrd;     /*极慢衰落信道过零点次数门限*/
    INT8  cVelSirThrd;  /*速度估计低SIR保护门限*/   /*5*/   
    UINT8 ucMainPthPos; /*定时同步位置*/                    /*MainPthPos 算法保证取值2-5范围内*/
    UINT16 usVarTh;     /*AWGN信道Var门限*/
    UINT16 usLrTh0;     /*慢衰落信道过零点次数门限*/
    UINT16 usLrTh1;     /*中衰落信道过零点次数门限*/
    UINT16 usLrTh2;     /*高慢衰落信道过零点次数门限*/  /*10*/

}TDS_VEL_ALG_PARA_STRU;

/*TDS  速度估计 结果打桩结构体定义*/
typedef struct TDS_VEL_STUB
{
    TDS_SWITCH_FALG_ENUM_UINT16 usVelStubSwitch;     /*速度估计 打桩控制开关*/
    UINT16 usVar;
    UINT16 usVelStat;
    UINT16 usRsvd;        
}TDS_VEL_STUB_STRU;

/* TDS CQI 计算算法可配参数结构定义*/
typedef struct TDS_CQI_NV_PARA
{
    UINT16 usUeCategory;/*UE的能力等级*/
    UINT16 usPunRateLimit;/*极限打孔率*/
}TDS_CQI_NV_PARA_STRU;

typedef struct TDS_CQI_ALG_PARA
{
    TDS_SWITCH_FALG_ENUM_UINT16 usOLASwitch;            /*欧拉修正算法的开关                    */          /*0*/     
    UINT16 usOLAAdjStep;                                /*欧拉算法TBI修正步长                   */            
    TDS_SWITCH_FALG_ENUM_UINT16 usVelSwitch;            /*自适应信道类型判断开关                */            
    UINT16 usSirAvrPrd;                                 /*SIR平滑周期，VelocitySwitch关闭时生效 */            
    TDS_SWITCH_FALG_ENUM_UINT16 usDynOLASwitch;         /*动态欧拉开关，VelocitySwitch关闭时生效*/            
    UINT16 usTargetBlerOne;            /*欧拉修正单目标值          */    
    UINT16 usTargetBlerA;              /*欧拉修正AWGN目标值        */    
    UINT16 usTargetBlerS;              /*欧拉修正极慢衰落信道目标值*/    
    UINT16 usTargetBlerH1;             /*慢衰欧拉修正SIR区间1目标值*/    
    UINT16 usTargetBlerH2;             /*慢衰欧拉修正SIR区间2目标值*/              
    UINT16 usTargetBlerH3;             /*慢衰欧拉修正SIR区间3目标值*/       /*10*/
    UINT16 usTargetBlerHH1;            /*快衰欧拉修正SIR区间1目标值*/
    UINT16 usTargetBlerHH2;            /*快衰欧拉修正SIR区间2目标值*/
    UINT16 usTargetBlerHH3;            /*快衰欧拉修正SIR区间3目标值*/
    UINT16 usVarTh;                    /*速度估计Var门限           */     
    UINT16 usLrTh0;                    /*慢衰落信道过零点次数门限  */     
    UINT16 usLrTh1;                    /*中衰落信道过零点次数门限  */     
    UINT16 usLrTh2;                    /*快衰落信道过零点次数门限  */     
    INT32 lVelSirTh;                   /*信道类型判决生效SIR门限*/
    INT32 lCqiAvraFadTH;               /*深衰落SIR保护门限*/                           
    INT32 lSirRang1;                   /*SIR区间门限1*/                    /*20*/
    INT32 lSirRang2;                   /*SIR区间门限2*/
}TDS_CQI_ALG_PARA_STRU;

typedef struct TDS_SIR_OM_RPT_CTRL
{
    TDS_SWITCH_FALG_ENUM_UINT16 usTdsSirDpchRptEbl;
    TDS_SWITCH_FALG_ENUM_UINT16 usTdsSirHsscchhRptEbl;
    TDS_SWITCH_FALG_ENUM_UINT16 usTdsSirEagchRptEbl;
    TDS_SWITCH_FALG_ENUM_UINT16 usTdsSirHsdschRptEbl;
    TDS_SWITCH_FALG_ENUM_UINT16 usTdsSirPccpchRptEbl;
    TDS_SWITCH_FALG_ENUM_UINT16 usTdsSirSccpcbRptEbl;
    TDS_SWITCH_FALG_ENUM_UINT16 usTdsSirEhichRptEbl;
    UINT16 usRsvd;        
}TDS_SIR_OM_REQ_CTRL_STRU;

typedef struct TDS_CQI_OM_RPT_CTRL
{
    TDS_SWITCH_FALG_ENUM_UINT16 usTdsVelRptEbl;
    TDS_SWITCH_FALG_ENUM_UINT16 usTdsCqiRptEbl;
    TDS_SWITCH_FALG_ENUM_UINT16 usVelVarRptEbl;
    TDS_SWITCH_FALG_ENUM_UINT16 usCqiVarRptEbl;
}TDS_CQI_OM_REQ_CTRL_STRU;

typedef struct TDS_SIR_OUT
{
    UINT16 usSbfn;      /*当前子帧号*/
    UINT16 usRsvd;        
    INT32  lSir;        /*当前子帧SIR结果*/
}TDS_SIR_OUT_STRU;

/*TDS  CQI 结果打桩结构体定义*/
typedef struct TDS_CQI_STUB
{
    TDS_SWITCH_FALG_ENUM_UINT16 usCqiStubSwitch;     /*CQI 结果 打桩控制开关*/
    UINT16 usModuFormat;
    UINT16 usTbiOut;
    UINT16 usRsvd;        
}TDS_CQI_STUB_STRU;

/*速度估计结构变量*/
typedef struct TDS_VEL_2HALF_MAX
{
    INT16 sMax0;
    INT16 sMin0;
    INT16 sMax1;
    INT16 sMin1;
}TDS_VEL_2HALF_MAX_STRU;

typedef struct TDS_VEL_PROC_VAR
{
    UINT16 usVelTaskFalg; /*Vel任务标志，在时隙中断中触发，保证一个子帧执行一次*/
    UINT16 usSfn;         /*当前速度估计处理数据对应子帧号*/
    UINT16 usAgc;         /*当前AGC增益*/
    UINT16 usCurVelFrmCnt;/*当前速度估计处理周期内子帧计数，取值0-127*/
    TDS_VEL_2HALF_MAX_STRU stVelCurPeak;
    INT32 lAccu;           /*功率累加值Accu*/    
    INT32 lSirSum;         /*SIR累加值SIRSum*/              
}TDS_VEL_PROC_VAR_STRU;

typedef struct TDS_VEL_OUT
{
    UINT16 usVar;
    UINT16 usLr0;
    UINT16 usLr1;
    UINT16 usLr;
    UINT16 usVelStat;
    UINT16 usTmpVelStat;
}TDS_VEL_OUT_STRU;

/*CQI处理过程变量输出结构*/
typedef struct TDS_CQI_PROC_VAR
{
    UINT16 usVelStat;      
    UINT16 usSirIdx;
    UINT16 usCycleFlag;
    UINT16 usSnrAvrPrdRl;
    UINT16 usStaChaged;
    INT16 sCQI_DInitialTx;//16s
    UINT16 usCqiStubFlag;
    UINT16 usNewDataInd;
    UINT16 usCrcResult;
    INT16 sDCqi_InitialTx;
    INT32 lSirHold;
    INT32 lSirSum;
    INT32 lSirMear;
    INT32 lSirAverage;
}TDS_CQI_PROC_VAR_STRU;

typedef struct TDS_CQI_OUT
{
    UINT16 usPuncRate;
    UINT16 usModuFormat;
    UINT16 usTbiOut;
    UINT16 usTbiOrg;
    UINT16 usMaxTbi;
    UINT16 usMinTbi;
    INT16 sOutOlaOffset;
    UINT16 usRsvd;    
}TDS_CQI_OUT_STRU;

#ifdef __cplusplus
#if __cplusplus
}
#endif
#endif /* __cplusplus */

#endif

