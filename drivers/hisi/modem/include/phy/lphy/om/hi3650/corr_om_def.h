/******************************************************************************

                  版权所有 (C), 2001-2011, 华为技术有限公司

 ******************************************************************************
  文 件 名   : corr_om_def.h
  版 本 号   : 初稿
  作    者   : tuzhiguo(52067)
  生成日期   : 2010年12月29日
  最近修改   :
  功能描述   : 定义相关模块OM需要上报的结构体,该文件最终会交付给HiStudio使用
  函数列表   :
  修改历史   :
  1.日    期   : 2010年12月29日
    作    者   : tuzhiguo(52067)
    修改内容   : 创建文件

  2.日    期   : 2011年05月26日
    作    者   : tuzhiguo(52067)
    修改内容   : CQI新特性修改合入

******************************************************************************/

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

#ifndef __CORR_OM_DEF_H__
#define __CORR_OM_DEF_H__


#ifdef __cplusplus
#if __cplusplus
extern "C"{
#endif
#endif /* __cplusplus */

/************************************************************
                           1. REQ命令和对应的数据结构定义
************************************************************/
typedef enum __LPHY_REQ_MSGID_CORR__
{
    LPHY_REQ_CORR_RESERVED            = OM_CMD_ID(LPHY_CORR_MID, OM_TYPE_REQ, 0x0),
    LPHY_REQ_CORR_WB_ALPHA,                              //非白化宽带滤波因子
    LPHY_REQ_CORR_SB_ALPHA,                              //非白化自带滤波因子
    LPHY_REQ_CORR_WHITE_ALPHA,                           //白化的滤波因子
	//LPHY_REQ_CORR_1T_OR_1R_NOISE_FACTOR,				   //相关性计算时，1发射天线或1接收天线时，计算相关性的噪声因子
	//LPHY_REQ_CORR_2T2R_OR_4T2R_NOISE_FACTOR_2T,		   //2发2收时，计算相关性的噪声因子，或4发2收时计算相关性Corr21,Corr22,Corr23时的噪声因子 
	//LPHY_REQ_CORR_4T2R_OR_8T2R_NOISE_FACTOR_4T,		   //4/8发2收时，计算相关性Corr1时的噪声因子
	//LPHY_REQ_CORR_WHITE_1T_OR_1R_NOISE_FACTOR,		   //1发射天线或1接收天线时，计算噪声白化后的相关性噪声因子
	//LPHY_REQ_CORR_WHITE_2T2R_OR_4T2R_NOISE_FACTOR_2T,    //2发2收时，计算噪声白化后的相关性噪声因子或4发2收时计算相关性Corr21,Corr22,Corr23的噪声因子
	//LPHY_REQ_CORR_WHITE_4T2R_NOISE_FACTOR_4T, 		   //4发2收时，计算噪声白化后的相关性Corr1时的噪声因子
	//LPHY_REQ_CORR_1T_OR_1R_THRESH,					   //1发射天线或1接收天线时，判断相关性的门限值
	//LPHY_REQ_CORR_2T2R_OR_4T2R_THRESH,				   //2发2收获4发2收时，判断相关性的门限值
	//LPHY_REQ_CORR_FDD_CORRFLAG,						   //FDD模式下，相关性启动子帧计算的时序Flag
	//LPHY_REQ_CORR_TDD_CORRFLAG,						   //TDD模式下，相关性启动子帧计算的时序Flag
    //LPHY_REQ_CORR_HETNET_SNR_THRESH,                     //hetnet场景下判断是否进行Corr计算的SNR门限
}LPHY_REQ_MSGID_CORR_ENUM;

typedef struct __LPHY_REQ_CORR_1T_OR_1R_NOISE_FACTOR_STRU__
{
    OM_REQ_ENABLE_ENUM_UINT16   enEn;
    UINT16                      usNoiseFactor;
}LPHY_REQ_CORR_1T_OR_1R_NOISE_FACTOR_STRU;

typedef struct __LPHY_REQ_CORR_2T2R_OR_4T2R_NOISE_FACTOR_2T_STRU__
{
    OM_REQ_ENABLE_ENUM_UINT16   enEn;
    UINT16                      usNoiseFactor;
}LPHY_REQ_CORR_2T2R_OR_4T2R_NOISE_FACTOR_2T_STRU;

typedef struct __LPHY_REQ_CORR_4T2R_OR_8T2R_NOISE_FACTOR_4T_STRU__
{
    OM_REQ_ENABLE_ENUM_UINT16   enEn;
    UINT16                      usNoiseFactor;
}LPHY_REQ_CORR_4T2R_OR_8T2R_NOISE_FACTOR_4T_STRU;

typedef struct __LPHY_REQ_CORR_WHITE_1T_OR_1R_NOISE_FACTOR_STRU__
{
    OM_REQ_ENABLE_ENUM_UINT16   enEn;
    UINT16                      usNoiseFactor;
}LPHY_REQ_CORR_WHITE_1T_OR_1R_NOISE_FACTOR_STRU;

typedef struct __LPHY_REQ_CORR_WHITE_2T2R_OR_4T2R_NOISE_FACTOR_2T_STRU__
{
    OM_REQ_ENABLE_ENUM_UINT16   enEn;
    UINT16                      usNoiseFactor;
}LPHY_REQ_CORR_WHITE_2T2R_OR_4T2R_NOISE_FACTOR_2T_STRU;

typedef struct __LPHY_REQ_CORR_WHITE_4T2R_NOISE_FACTOR_4T_STRU__
{
    OM_REQ_ENABLE_ENUM_UINT16   enEn;
    UINT16                      usNoiseFactor;
}LPHY_REQ_CORR_WHITE_4T2R_NOISE_FACTOR_4T_STRU;

typedef struct __LPHY_REQ_CORR_1T_OR_1R_THRESH_STRU__
{
    OM_REQ_ENABLE_ENUM_UINT16   enEn;
    UINT16                      usThresh;
}LPHY_REQ_CORR_1T_OR_1R_THRESH_STRU;

typedef struct __LPHY_REQ_CORR_2T2R_OR_4T2R_THRESH__
{
    OM_REQ_ENABLE_ENUM_UINT16   enEn;
    UINT16                      usThresh;
}LPHY_REQ_CORR_2T2R_OR_4T2R_THRESH_STRU;

typedef struct __LPHY_REQ_CORR_FDD_CORRFLAG_STRU__
{
    OM_REQ_ENABLE_ENUM_UINT16   enEn;
    UINT8                       ucCorrFlag[6];
}LPHY_REQ_CORR_FDD_CORRFLAG_STRU;

typedef struct __LPHY_REQ_CORR_TDD_CORRFLAG_STRU__
{
    OM_REQ_ENABLE_ENUM_UINT16   enEn;
    UINT8                       ucCorrFlag[6];
}LPHY_REQ_CORR_TDD_CORRFLAG_STRU;

typedef struct __LPHY_REQ_CORR_WB_ALPHA_STRU__
{
    OM_REQ_ENABLE_ENUM_UINT16   enEn;
    UINT8                       ucAlpha[6][3];
}LPHY_REQ_CORR_WB_ALPHA_STRU;

typedef struct __LPHY_REQ_CORR_SB_ALPHA_STRU__
{
    OM_REQ_ENABLE_ENUM_UINT16   enEn;
    UINT8                       ucAlpha[6][3];
}LPHY_REQ_CORR_SB_ALPHA_STRU;

typedef struct __LPHY_REQ_CORR_WHITE_ALPHA_STRU__
{
    OM_REQ_ENABLE_ENUM_UINT16   enEn;
    UINT16                      usAlpha;
    UINT16                      usLT5MAlpha;
	UINT16                      usRsv;
}LPHY_REQ_CORR_WHITE_ALPHA_STRU;

typedef struct __LPHY_REQ_CORR_HETNET_SNR_THRESH_STRU__
{
    OM_REQ_ENABLE_ENUM_UINT16   enEn;
    INT16                 sSnrThresh;
}LPHY_REQ_CORR_HETNET_SNR_THRESH_STRU;

/************************************************************
                           2. CNF数据结构定义
************************************************************/
typedef enum __LPHY_CNF_MSGID_CORR__
{
    LPHY_CNF_CORR_RESERVED            = OM_CMD_ID(LPHY_CORR_MID, OM_TYPE_CNF, 0x0),
}LPHY_CNF_MSGID_CORR_ENUM;


/************************************************************
                           3. Ind数据结构定义
************************************************************/
typedef enum __LPHY_IND_MSGID_CORR__
{
    LPHY_IND_CORR_RESERVED            = OM_CMD_ID(LPHY_CORR_MID, OM_TYPE_IND, 0x0),
}LPHY_IND_MSGID_CORR_ENUM;


/************************************************************
                           4. TRACE数据结构定义
************************************************************/
typedef enum __LPHY_TRACE_CORR_
{
    LPHY_TRACE_CORR_RESERVED         = OM_CMD_ID(LPHY_CORR_MID, OM_TYPE_TRACE, 0x0),
}LPHY_TRACE_CORR_ENUM;


/************************************************************
                           5. SG数据结构定义
************************************************************/
typedef enum __LPHY_SG_CORR_
{
    LPHY_SG_CORR_RESERVED         = OM_CMD_ID(LPHY_CORR_MID, OM_TYPE_SG, 0x0),
	LPHY_SG_PCELL_CS0_NONWHTN_CORR_RESULT,
    LPHY_SG_PCELL_CS0_WHTN_CORR_RESULT,
    LPHY_SG_PCELL_CS0_CORR_STAT,
	LPHY_SG_PCELL_CS1_NONWHTN_CORR_RESULT,
	LPHY_SG_PCELL_CS1_WHTN_CORR_RESULT,
	LPHY_SG_PCELL_CS1_CORR_STAT,
	LPHY_SG_SCELL_NONWHTN_CORR_RESULT,
	LPHY_SG_SCELL_WHTN_CORR_RESULT,
	LPHY_SG_SCELL_CORR_STAT,
}LPHY_SG_CORR_ENUM;

typedef struct __LPHY_SG_WHTN_CORR_RESULT_STRU__
{
    LTE_CHAN_SPACE_CORR_ENUM_UINT8  ucWhtnRecCorr;      /*0,表示低相关，1，表示中相关，2表示高相关*/
    LTE_CHAN_SPACE_CORR_ENUM_UINT8  ucWhtnCorr;         /*0,表示低相关，1，表示中相关，2表示高相关*/
	UINT32                          ulTransRecCorrDev[16];  /*发射和接收之间的相关性的比值*/
	UINT16                          usRsv;
}LPHY_SG_WHTN_CORR_RESULT_STRU;

typedef struct __LPHY_SG_NONWHTN_CORR_RESULT_STRU__
{
    LTE_CHAN_SPACE_CORR_ENUM_UINT8  ucNonWhtnRecCorr;   /*0,表示低相关，1，表示中相关，2表示高相关*/
    LTE_CHAN_SPACE_CORR_ENUM_UINT8  ucNonWhtnCorr;      /*0,表示低相关，1，表示中相关，2表示高相关*/
	UINT32                          ulTransRecCorrDev[16];  /*发射和接收之间的相关性的比值*/
	UINT16                          usRsv;
}LPHY_SG_NONWHTN_CORR_RESULT_STRU;

typedef struct __LPHY_SG_CORR_OM_STAT_STRU__
{
    UINT32      ulSubFrmCnt;                     /*子帧计数*/
    UINT16      ulWhtnRecCorr[3];                /*高中低相关所占百分比*/
    UINT16      ulWhtnCorr[3];                   /*高中低相关所占百分比*/
    UINT16      ulNonWhtnRecCorr[3];             /*高中低相关所占百分比*/
    UINT16      ulNonWhtnCorr[3];                /*高中低相关所占百分比*/
	UINT32      ulTransRecCorrDev[16];           /*发射和接收之间的相关性比值*/
	UINT8       ucWhtnIdx;                       /*发射和接收之间的相关性比值的index*/
	UINT8       ucNonWhtnIdx;                    /*发射和接收之间的相关性比值的index*/
	UINT16      usRsv;
}LPHY_SG_CORR_OM_STAT_STRU;

/************************************************************
                           6. DT数据结构定义
************************************************************/


typedef struct __LPHY_DT_NONWHTN_CORR_RESULT_STRU__
{
    UINT16      usSysFrmNum;            /*上报时刻系统帧号*/
	UINT16      usSubFrmNum;            /*上报时刻子帧号*/
	LTE_CHAN_SPACE_CORR_ENUM_UINT8  ucNonWhtnRecCorr;   /*0,表示低相关，1，表示中相关，2表示高相关*/
	UINT8                          usRsv[3];
}LPHY_DT_NONWHTN_CORR_RESULT_STRU;


typedef struct __LPHY_DT_WHTN_CORR_RESULT_STRU__
{
    UINT16      usSysFrmNum;            /*上报时刻系统帧号*/
	UINT16      usSubFrmNum;            /*上报时刻子帧号*/
	LTE_CHAN_SPACE_CORR_ENUM_UINT8  ucWhtnRecCorr;   /*0,表示低相关，1，表示中相关，2表示高相关*/
	UINT8                          usRsv[3];
}LPHY_DT_WHTN_CORR_RESULT_STRU;





typedef enum __LPHY_DT_CORR_
{
    LPHY_DT_CORR_RESERVED         = OM_CMD_ID(LPHY_CORR_MID, OM_TYPE_DT, 0x0),
	LPHY_DT_PCELL_CS0_NONWHTN_CORR_RESULT,
    LPHY_DT_PCELL_CS0_WHTN_CORR_RESULT,
    LPHY_DT_PCELL_CS0_CORR_STAT,
	LPHY_DT_PCELL_CS1_NONWHTN_CORR_RESULT,
	LPHY_DT_PCELL_CS1_WHTN_CORR_RESULT,
	LPHY_DT_PCELL_CS1_CORR_STAT,
	LPHY_DT_SCELL_NONWHTN_CORR_RESULT,
	LPHY_DT_SCELL_WHTN_CORR_RESULT,
	LPHY_DT_SCELL_CORR_STAT,
}LPHY_DT_CORR_ENUM;

#ifdef __cplusplus
#if __cplusplus
}
#endif
#endif /* __cplusplus */


#endif /* __CORR_OM_DEF_H__ */
