/******************************************************************************

                  版权所有 (C), 2001-2011, 华为技术有限公司

 ******************************************************************************
  文 件 名   : cqi_om_def.h
  版 本 号   : 初稿
  作    者   : tuzhiguo(52067)
  生成日期   : 2010年12月29日
  最近修改   :
  功能描述   : 定义定时模块OM需要上报的结构体,该文件最终会交付给HiStudio使用
  函数列表   :
  修改历史   :
  1.日    期   : 2010年12月29日
    作    者   : tuzhiguo(52067)
    修改内容   : 创建文件

  2.日    期   : 2011年05月26日
    作    者   : tuzhiguo(52067)
    修改内容   : CQI新特性修改合入

  3.日    期   : 2011年05月26日
    作    者   : tuzhiguo(52067)
    修改内容   : 增加测试部需要的OM需求项（上报周期和非周期反馈模式）
	            增加CQITrace，打印收到的原语信息，方便定位
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

#ifndef __CQI_OM_DEF_H__
#define __CQI_OM_DEF_H__


#ifdef __cplusplus
#if __cplusplus
extern "C"{
#endif
#endif /* __cplusplus */

/************************************************************/
#define	CQI_MAX_CA_NUM				2
#define	CQI_MAX_TM10_PROCESS_NUM	LPHY_FEATURE_MAX_CARRIER_NUM
/************************************************************/
typedef enum
{
	CQI_TYPE_A12 = 0,
	CQI_TYPE_A20,
	CQI_TYPE_A22,
	CQI_TYPE_A30,
	CQI_TYPE_A31,
	CQI_TYPE_A_BUTT
}CQI_RPT_TYPE_APERI_ENUM;
typedef UINT8 CQI_RPT_TYPE_APERI_ENUM_UINT8;

typedef enum
{
	CQI_TYPE_P1 = 0,
	CQI_TYPE_P1A,
	CQI_TYPE_P2,
	CQI_TYPE_P2A,
	CQI_TYPE_P2B,
	CQI_TYPE_P2C,
	CQI_TYPE_P3,
	CQI_TYPE_P4,
	CQI_TYPE_P5,
	CQI_TYPE_P6,
	CQI_TYPE_P_BUTT
}CQI_RPT_TYPE_PERI_ENUM;
typedef UINT8 CQI_RPT_TYPE_PERI_ENUM_UINT8;
/************************************************************
                           1. REQ命令和对应的数据结构定义
************************************************************/
typedef enum
{
	LPHY_REQ_CQI_RESERVED			 = OM_CMD_ID(LPHY_CQI_MID, OM_TYPE_REQ, 0x0),//0x30500000
	LPHY_REQ_CQI_CFG_OLLA				,
	LPHY_REQ_CQI_CFG_WHITEN 			,
	LPHY_REQ_CQI_CFG_CQI				,
	LPHY_REQ_CQI_CFG_PMI_SEL			,
	LPHY_REQ_CQI_CFG_RI 				,
	LPHY_REQ_CQI_DISP_RI_CQI_PMI_APERI	,	//与协议规定的周期一致
	LPHY_REQ_CQI_DISP_RI_CQI_PMI_PERI	,	//与协议规定的周期一致
	LPHY_REQ_CQI_DISP_ESINR_PCC_H0		,	//每启动计算就上报
	LPHY_REQ_CQI_DISP_ESINR_PCC_H1		,	//每启动计算就上报
	LPHY_REQ_CQI_DISP_ESINR_SCC1		,	//每启动计算就上报
	LPHY_REQ_CQI_DISP_ESINR_SCC2		,	//每启动计算就上报
	LPHY_REQ_CQI_DISP_ESINR_SCC3		,	//每启动计算就上报
	LPHY_REQ_CQI_DISP_WB_TSINR			,	//宽带cqi的目标信干噪比,每启动计算就上报
	LPHY_REQ_CQI_DISP_WB_RBIR_PCC_H0	,	//宽带cqi的RBIR,每启动计算就上报
	LPHY_REQ_CQI_DISP_WB_RBIR_PCC_H1	,	//宽带cqi的RBIR,每启动计算就上报
	LPHY_REQ_CQI_DISP_WB_RBIR_SCC1		,	//宽带cqi的RBIR,每启动计算就上报
	LPHY_REQ_CQI_DISP_WB_RBIR_SCC2		,	//宽带cqi的RBIR,每启动计算就上报
	LPHY_REQ_CQI_DISP_WB_RBIR_SCC3		,	//宽带cqi的RBIR,每启动计算就上报
	LPHY_REQ_CQI_DISP_PERIOD_LEN        ,   //宽带cqi和子带cqi上报周期,每启动计算就上报
	LPHY_REQ_CQI_DISP_RB_WHITEN_FLAG	,	//RB的白化flag,每启动计算就上报
	LPHY_REQ_CQI_DISP_RI_PERCENT		,	//RI=1,2,3,4的统计百分比,10s上报1次
	LPHY_REQ_CQI_DISP_SB_PMI_PERCENT	,	//子带PMI=0~15的统计百分比,10s上报1次
	LPHY_REQ_CQI_DISP_WB_PMI_PERCENT	,	//宽带PMI=0~15的统计百分比,10s上报1次
	LPHY_REQ_CQI_DISP_SB_CQI_PERCENT	,	//子带CQI0/1=0~15的统计百分比,10s上报1次
	LPHY_REQ_CQI_DISP_WB_CQI_PERCENT	,	//宽带CQI0/1=0~15的统计百分比,10s上报1次
	LPHY_REQ_CQI_DISP_WB_CQI_MEDIAN 	,	//宽带CQI0/1=0~15的中位数，10s上报1次
	LPHY_REQ_CQI_DISP_PA_PC_DELTAOFSET  ,		//1s上报1次
	LPHY_REQ_CQI_DISP_DEBUG  ,		//有配置或者读取就上报
	LPHY_DT_CQI_INFO_REQ            = OM_CMD_ID(LPHY_CQI_MID, OM_TYPE_REQ, 0x100)
}LPHY_REQ_MSGID_CQI_ENUM;

typedef struct
{
	OM_REQ_ENABLE_ENUM_UINT16	enEn;
	UINT8						ucCQIAdjSwitch;		//CQI是否调整标示	0：不调整	1：调整
	UINT8						ucCQIAdjStepDown;	//CQI向下调整步长
	UINT8						ucCQIAdjStepUp;		//CQI向上调整步长
	UINT8						ucCQIAlpha;			//CQI滤波因子
	UINT8						ucCQISortFlag;		//CQI滤波时是否按大小排序的Flag	0：不按大小排序	1：按大小排序
	UINT8						ucRsv;
}LPHY_REQ_CQI_CFG_OLLA_STRU;

typedef struct
{
	OM_REQ_ENABLE_ENUM_UINT16	enEn;
	UINT16						usRuuMode_CQI;		//默认值1。配置时1表示使用CRS的Ruu；0表示采用CMU;
	UINT16						usSNRThreshold;		//100,使用噪声生成白化阵的信噪比门限
	UINT8   					ucCRSIC;			//0,v750版本不启动CRSIC功能
	UINT8   					ucTargetWidth_Ruu;	//16,
}LPHY_REQ_CQI_CFG_WHITEN_STRU;

typedef struct
{
	OM_REQ_ENABLE_ENUM_UINT16	enEn;
	OM_REQ_ENABLE_ENUM_UINT16   usRbirAlpha_En;
	UINT16						usRbirAlpha;		//CQI的RBIR滤波因子支持打桩
	OM_REQ_ENABLE_ENUM_UINT16   sEsinrFactor5_En;
	INT16						sEsinrFactor5;		//有效信噪比补偿，3层时码字1的修正值支持配置
	OM_REQ_ENABLE_ENUM_UINT16   usUnevenThreshold_En;
	UINT16						usUnevenThreshold;	//512,符号间干扰不平衡判断门限
	OM_REQ_ENABLE_ENUM_UINT16   sWbTsinr_En;
	INT16						sWbTsinr[15];		//宽带CQI的目标信干噪比支持配置
	OM_REQ_ENABLE_ENUM_UINT16   ucHextractInd_En;
	UINT8						ucHextractInd;		//0--抽取偶数序号的H矩阵；1--抽取奇数序号的H矩阵
	UINT8						aucRsv;
	OM_REQ_ENABLE_ENUM_UINT16   ucFreqNoiseFactor_En;
	UINT8						ucFreqNoiseFactor;	//5
	UINT8						aucRsv1;
	OM_REQ_ENABLE_ENUM_UINT16   ucNoiseBitThres_En;
	UINT8						ucNoiseBitThres;	//14,NumLayers>=3的时候噪声最小值,适用于3、4层
	UINT8						aucRsv2;
	OM_REQ_ENABLE_ENUM_UINT16   ucMinNoiseBit_En;
	UINT8						ucMinNoiseBit;		//5,最小噪声比特,适用于3、4层
	UINT8						aucRsv3;
	OM_REQ_ENABLE_ENUM_UINT16   ucWbCqi_En;
	UINT8						ucWbCqi;			//计算所得到的宽带CQI和宽带PMI需要可以打桩
	UINT8						aucRsv4;
	OM_REQ_ENABLE_ENUM_UINT16   ucWbPmi_En;
	UINT8						ucWbPmi;			//计算所得到的宽带CQI和宽带PMI需要可以打桩
	UINT8						aucRsv5;
	OM_REQ_ENABLE_ENUM_UINT16   ucSbCqi_En;
	UINT8						ucSbCqi;			//计算所得到的子带CQI和子带PMI需要可以打桩
	UINT8						aucRsv6;
	OM_REQ_ENABLE_ENUM_UINT16   ucSbPmi_En;
	UINT8						ucSbPmi;			//计算所得到的子带CQI和子带PMI需要可以打桩
	UINT8						aucRsv7[3];
}LPHY_REQ_CQI_CFG_CQI_STRU;


typedef struct
{
	OM_REQ_ENABLE_ENUM_UINT16	enEn;
	OM_REQ_ENABLE_ENUM_UINT16   ulFactorJump_En;
	UINT16						ulFactorJump;		//CQI的RBIR滤波因子支持打桩
	OM_REQ_ENABLE_ENUM_UINT16   ulFactorRi3_En;
	UINT16						ulFactorRi3;		//CQI的RBIR滤波因子支持打桩
	OM_REQ_ENABLE_ENUM_UINT16   ulFactorRi4_En;
	UINT16						ulFactorRi4;		//CQI的RBIR滤波因子支持打桩
	OM_REQ_ENABLE_ENUM_UINT16   usPtiBiasThd_En;
	UINT16						usPtiBiasThd;		//PTI的偏差的门限
	OM_REQ_ENABLE_ENUM_UINT16   usPtiVarThd_En;
	UINT16						usPtiVarThd;		//PTI的方差的门限
	OM_REQ_ENABLE_ENUM_UINT16   usPmi1Alpha_En;
	UINT16						usPmi1Alpha;		//估计PTI时的FirstPMI的滤波因子可以配置
	OM_REQ_ENABLE_ENUM_UINT16   ucPmi1Pmi2AlgSel_En;
	UINT8						ucPmi1Pmi2AlgSel;	//TM9，8CSIRSPort，4层，W1和W2联合选择还是分开选支持配置,0--分开选择；1--联合选择
	UINT8						aucRsv;
	OM_REQ_ENABLE_ENUM_UINT16   ucPmi1_En;
	UINT8						ucPmi1;				//First PMI的滤波因子可以打桩
	UINT8						aucRsv1[3];
}LPHY_REQ_CQI_CFG_PMI_SEL_STRU;

typedef struct
{
	OM_REQ_ENABLE_ENUM_UINT16	enEn;
	OM_REQ_ENABLE_ENUM_UINT16	ulLimitRbir_En;
	UINT32						ulLimitRbir[4];							//根据互信息计算RI时每个RI的互信息限幅值
	UINT8						aucRsv0[2];
	OM_REQ_ENABLE_ENUM_UINT16	aul_Cqi_BbpReg_CHx_RI_R234_FACTOR_En;
	UINT32						aul_Cqi_BbpReg_CHx_RI_R234_FACTOR[3];	//配置下来的RIFactor，除白化因子外的相乘计算结果,Cqi_BbpReg_CHx_RI_Rx_FACTOR
	UINT32						aul_Cqi_BbpReg_CHx_RI_R234_WHITEN_FACTOR[3];
	OM_REQ_ENABLE_ENUM_UINT16	sRiThreshold_En;
	INT16						sRiThreshold;							//RI门限选择时的有效SNR门限,gstCqi_AlgPara.sRiThreshold
	OM_REQ_ENABLE_ENUM_UINT16	ucRi_En;
	UINT8						ucRi;									//计算得到的RI可以打桩
	UINT8						ucPti;
	//统计RI的次数和次数判断门限
		/*算法需求描述不清楚*/
	//根据Trms、相关性、白化、传输模式和双工模式进行调整RI门限调整的因子可以配置,Cqi_BbpReg_CHx_RI_Rx_FACTOR
		/*nv中实现*/
}LPHY_REQ_CQI_CFG_RI_STRU;

typedef struct
{
	OM_REQ_ENABLE_ENUM_UINT16	enEn;
	UINT8						aucRsv[2];
}LPHY_REQ_CQI_DISP_EN_STRU;

typedef LPHY_REQ_CQI_DISP_EN_STRU	LPHY_REQ_CQI_DISP_RI_CQI_PMI_APERI_STRU;
typedef LPHY_REQ_CQI_DISP_EN_STRU	LPHY_REQ_CQI_DISP_RI_CQI_PMI_PERI_STRU;
typedef LPHY_REQ_CQI_DISP_EN_STRU	LPHY_REQ_CQI_DISP_ESINR_PCC_H0_STRU;
typedef LPHY_REQ_CQI_DISP_EN_STRU	LPHY_REQ_CQI_DISP_ESINR_PCC_H1_STRU;
typedef LPHY_REQ_CQI_DISP_EN_STRU	LPHY_REQ_CQI_DISP_ESINR_SCC1_STRU;
typedef LPHY_REQ_CQI_DISP_EN_STRU	LPHY_REQ_CQI_DISP_ESINR_SCC2_STRU;
typedef LPHY_REQ_CQI_DISP_EN_STRU	LPHY_REQ_CQI_DISP_ESINR_SCC3_STRU;
typedef LPHY_REQ_CQI_DISP_EN_STRU	LPHY_REQ_CQI_DISP_WB_TSINR_STRU;
typedef LPHY_REQ_CQI_DISP_EN_STRU	LPHY_REQ_CQI_DISP_WB_RBIR_PCC_H0_STRU;
typedef LPHY_REQ_CQI_DISP_EN_STRU	LPHY_REQ_CQI_DISP_WB_RBIR_PCC_H1_STRU;
typedef LPHY_REQ_CQI_DISP_EN_STRU	LPHY_REQ_CQI_DISP_WB_RBIR_SCC1_STRU;
typedef LPHY_REQ_CQI_DISP_EN_STRU	LPHY_REQ_CQI_DISP_WB_RBIR_SCC2_STRU;
typedef LPHY_REQ_CQI_DISP_EN_STRU	LPHY_REQ_CQI_DISP_WB_RBIR_SCC3_STRU;
typedef LPHY_REQ_CQI_DISP_EN_STRU	LPHY_REQ_CQI_DISP_PERIOD_LEN_STRU;
typedef LPHY_REQ_CQI_DISP_EN_STRU	LPHY_REQ_CQI_DISP_RB_WHITEN_FLAG_STRU;
typedef LPHY_REQ_CQI_DISP_EN_STRU	LPHY_REQ_CQI_DISP_RI_PERCENT_STRU;
typedef LPHY_REQ_CQI_DISP_EN_STRU	LPHY_REQ_CQI_DISP_SB_PMI_PERCENT_STRU;
typedef LPHY_REQ_CQI_DISP_EN_STRU	LPHY_REQ_CQI_DISP_WB_PMI_PERCENT_STRU;
typedef LPHY_REQ_CQI_DISP_EN_STRU	LPHY_REQ_CQI_DISP_SB_CQI_PERCENT_STRU;
typedef LPHY_REQ_CQI_DISP_EN_STRU	LPHY_REQ_CQI_DISP_WB_CQI_PERCENT_STRU;
typedef LPHY_REQ_CQI_DISP_EN_STRU	LPHY_REQ_CQI_DISP_WB_CQI_MEDIAN_STRU;
typedef LPHY_REQ_CQI_DISP_EN_STRU	LPHY_REQ_CQI_DISP_PA_PC_DELTAOFSET_STRU;
typedef LPHY_REQ_CQI_DISP_EN_STRU	LPHY_REQ_CQI_DISP_DEBUG_STRU;
/************************************************************
                           2. SG 数据结构定义, 算法需要绘图的
************************************************************/
//OM_Report(OM_REPORT_LEVEL_INFO, OM_DEFAULT_SESSION_ID, LPHY_SG_CQI_DISP_RI_CQI_PMI,(UINT8*)&stRiCqiPmi, sizeof(LPHY_SG_CQI_DISP_RI_CQI_PMI_STRU));
typedef enum
{
    LPHY_SG_CQI_RESERVED            = OM_CMD_ID(LPHY_CQI_MID, OM_TYPE_SG, 0x0),//0x30530000
	LPHY_SG_CQI_DISP_RI_CQI_PMI_APERI	,	//与协议规定的周期一致
	LPHY_SG_CQI_DISP_RI_CQI_PMI_PERI	,	//与协议规定的周期一致
	LPHY_SG_CQI_DISP_ESINR_PCC_H0		,	//每启动计算就上报
	LPHY_SG_CQI_DISP_ESINR_PCC_H1		,	//每启动计算就上报
	LPHY_SG_CQI_DISP_ESINR_SCC1			,	//每启动计算就上报
	LPHY_SG_CQI_DISP_ESINR_SCC2			,	//每启动计算就上报
	LPHY_SG_CQI_DISP_ESINR_SCC3			,	//每启动计算就上报
	LPHY_SG_CQI_DISP_WB_TSINR			,	//宽带cqi的目标信干噪比,每启动计算就上报
	LPHY_SG_CQI_DISP_WB_RBIR_PCC_H0		,	//宽带cqi的RBIR,每启动计算就上报
	LPHY_SG_CQI_DISP_WB_RBIR_PCC_H1 	,	//宽带cqi的RBIR,每启动计算就上报
	LPHY_SG_CQI_DISP_WB_RBIR_SCC1	 	,	//宽带cqi的RBIR,每启动计算就上报
	LPHY_SG_CQI_DISP_WB_RBIR_SCC2		,	//宽带cqi的RBIR,每启动计算就上报
	LPHY_SG_CQI_DISP_WB_RBIR_SCC3		,	//宽带cqi的RBIR,每启动计算就上报
	LPHY_SG_CQI_DISP_PERIOD_LEN         ,   //宽带cqi和子带cqi上报周期,每启动计算就上报
	LPHY_SG_CQI_DISP_RB_WHITEN_FLAG		,	//RB的白化flag,每启动计算就上报
	LPHY_SG_CQI_DISP_RI_PERCENT			,	//RI=1,2,3,4的统计百分比,10s上报1次
	LPHY_SG_CQI_DISP_SB_PMI_PERCENT		,	//子带PMI=0~15的统计百分比,10s上报1次
	LPHY_SG_CQI_DISP_WB_PMI_PERCENT		,	//宽带PMI=0~15的统计百分比,10s上报1次
	LPHY_SG_CQI_DISP_SB_CQI_PERCENT		,	//子带CQI0/1=0~15的统计百分比,10s上报1次
	LPHY_SG_CQI_DISP_WB_CQI_PERCENT		,	//宽带CQI0/1=0~15的统计百分比,10s上报1次
	LPHY_SG_CQI_DISP_WB_CQI_MEDIAN 		,	//宽带CQI0/1=0~15的中位数，10s上报1次
	LPHY_SG_CQI_DISP_PA_PC_DELTAOFSET	,	//1s上报1次
	LPHY_SG_CQI_DISP_DEBUG_INFO		//有配置或者读取就上报
}LPHY_SG_MSGID_CQI_ENUM;
/************************************/
typedef struct
{
	LRRC_LPHY_CQI_MODEA_PERIODIC_ENUM_UINT16	enRptType;
	LPHY_CA_CC_ENUM_UINT16 						enCc;
	UINT8										ucRptReq;	//上报请求，给arbiter
	UINT8										ucCellIdx;
	//UINT8                                       ucProcId;	//tm10的process id；tm1-tm9，应固定为0；
	UINT8										ucHetnet;
	UINT8										ucCellIdx_Trigger;	//通过dci0触发非周期上报的cc对应的cellindex
	/*********************************************/
	UINT8       ucRi;			//1,2,3,4
	/*********************************************/
	UINT8		ucWcqi0;
	UINT8		ucWcqi1;
	UINT8		ucWpmi;
	UINT8		ucWpmi1;
	UINT8		ucWpmi2;
	UINT8		aucRsv[2];
	/*********************************************/
	UINT8		ucSpmi[13];
	UINT8		ucSpmi2[13];
	UINT8		ucScqi0[13];
	UINT8		ucScqi1[13];
	/*********************************************/
	UINT32		ucMposSbidx[6];	//M子带位置
	UINT8		ucMcqi0;		//M子带cqi0
	UINT8		ucMcqi1;		//M子带cqi1
	UINT8		ucMpmi;			//M子带pmi
	UINT8		ucMpmi2;		//M子带pmi2
}CQI_OM_ACQI_RPT_STRU;

typedef struct
{
	CQI_OM_ACQI_RPT_STRU	astCqiOmAcqiRpt[CQI_MAX_CA_NUM+1];//CQI_MAX_CA_NUM = 4
}LPHY_SG_CQI_DISP_RI_CQI_PMI_APERI_STRU;
/************************************/
typedef enum{
	PCQI_RPT_MODE_P10	= 0,
	PCQI_RPT_MODE_P11,
	PCQI_RPT_MODE_P20,
	PCQI_RPT_MODE_P21,
	PCQI_RPT_MODE_BUTT
}CQI_PCQI_RPT_MODE_ENUM;
typedef UINT8  CQI_PCQI_RPT_MODE_ENUM_UINT8;

/************************************/
typedef enum {
	CQI_PUCCH_RPT_TYPE_1 = 0,
	CQI_PUCCH_RPT_TYPE_1A,
	CQI_PUCCH_RPT_TYPE_2,
	CQI_PUCCH_RPT_TYPE_2A,
	CQI_PUCCH_RPT_TYPE_2B,
	CQI_PUCCH_RPT_TYPE_2C,
	CQI_PUCCH_RPT_TYPE_3,
	CQI_PUCCH_RPT_TYPE_4,
	CQI_PUCCH_RPT_TYPE_5,
	CQI_PUCCH_RPT_TYPE_6,
	CQI_PUCCH_RPT_TYPE_BUTT
}CQI_PUCCH_RPT_TYPE_ENUM;
typedef UINT8 CQI_PUCCH_RPT_TYPE_ENUM_UINT8;
/************************************/
typedef struct
{
	UINT8       								ucRptReq;	//上报请求，给arbiter
	CQI_PCQI_RPT_MODE_ENUM_UINT8				enPcqiType;
	CQI_PUCCH_RPT_TYPE_ENUM_UINT8 				enRptType;
	UINT8										ucCellIdx;
	LPHY_CA_CC_ENUM_UINT16 						enCc;
	UINT8										ucHetnet;
	/*********************************************/
	UINT8       ucRi;			//当前计算出的ri--1,2,3,4
	UINT8       ucPti;
	UINT8       ucWcqi0;
	UINT8       ucWcqi1;
	UINT8       ucWpmi;
	UINT8       ucWpmi1;
	UINT8       ucWpmi2;
	UINT8       ucBestSbid;		//BP内最好的子带
	UINT8       ucScqi0;		//子带Cqi
	UINT8       ucScqi1;		//子带Cqi
	UINT8       ucSpmi2;
	UINT8		aucRsv[2];
	/*********************************************/
	UINT8       aucWpmi1[4];	//各层Pmi1
}CQI_OM_PCQI_RPT_STRU;
typedef struct
{
	CQI_OM_PCQI_RPT_STRU	astCqiOmPcqiRpt[CQI_MAX_CA_NUM+1];//CQI_MAX_CA_NUM = 4
}LPHY_SG_CQI_DISP_RI_CQI_PMI_PERI_STRU;
/************************************/
typedef struct
{
	LPHY_CA_CC_ENUM_UINT16 	enCc;
	UINT8					ucHetnet;
	UINT8					aucRsv[1];

	INT16					sAmodRank1WbEsinr;
	INT16					sAmodRank2WbEsinr[2];
	INT16					sAmodRank3WbEsinr[2];
	INT16					sAmodRank4WbEsinr[2];

	INT16					sAmodRank1SbEsinr[13];
	INT16					sAmodRank2SbEsinr[26];
	INT16					sAmodRank3SbEsinr[26];
	INT16					sAmodRank4SbEsinr[26];

	INT16					sPmodRank1WbEsinr;
	INT16					sPmodRank2WbEsinr[2];
	INT16					sPmodRank3WbEsinr[2];
	INT16					sPmodRank4WbEsinr[2];

	INT16					sPmodBp0Esinr[2];
	INT16					sPmodBp1Esinr[2];
	INT16					sPmodBp2Esinr[2];
	INT16					sPmodBp3Esinr[2];
	INT16					asRsv[1];

}LPHY_SG_CQI_DISP_ESINR_STRU;//CQI_OM_CQI_ESINR_STRU;
/************************************/
typedef struct
{
	LPHY_CA_CC_ENUM_UINT16 	enCc;
	UINT8					ucHetnet;
	UINT8					aucRsv[1];
	INT16					sWbTsinrR1[15];
	INT16					sWbTsinrR2[15];
	INT16					sWbTsinrR3[15];
	INT16					sWbTsinrR4[15];
}CQI_OM_WB_TSINR_STRU;

typedef struct
{
	CQI_OM_WB_TSINR_STRU	astCqiOmTsinr[CQI_MAX_CA_NUM+1];
	UINT8						aucRsv[2];
}LPHY_SG_CQI_DISP_WB_TSINR_STRU;
/************************************/
typedef struct
{
	UINT32	ulR1RbirSum;
	UINT32	ulR2RbirSum;
	UINT32	ulR3RbirSum;
	UINT32	ulR4RbirSum;
}LPHY_SG_CQI_DISP_WB_RBIR_STRU;
/************************************/
typedef struct
{
	UINT16					usNpd[CQI_MAX_CA_NUM+1];			//分hetnet0/hetnet1
	UINT16					usMri[CQI_MAX_CA_NUM+1];			//分hetnet0/hetnet1
	UINT16	                usH[CQI_MAX_CA_NUM+1];			//分hetnet0/hetnet1;
	UINT16	                usH1[CQI_MAX_CA_NUM+1];			//分hetnet0/hetnet1;
	UINT16                  usWblen[CQI_MAX_CA_NUM+1];			//分hetnet0/hetnet1;
	UINT16                  usSblen[CQI_MAX_CA_NUM+1];			//分hetnet0/hetnet1;
	UINT16                  usRilen[CQI_MAX_CA_NUM+1];			//分hetnet0/hetnet1;
} LPHY_SG_CQI_DISP_PERIOD_LEN_STRU;

/************************************/

typedef struct
{
	LPHY_CA_CC_ENUM_UINT16 	enCc;
	UINT8					ucHetnet;
	UINT8					aucRsv[1];
	UINT32					ulRbWhitenFlag[5];	//CC0_SHIFT_WHTN_FLG0开始的寄存器
}CQI_OM_RB_WHITEN_STRU;
typedef struct
{
	CQI_OM_RB_WHITEN_STRU	astCqiOmRbWhitenFlag[CQI_MAX_CA_NUM+1];
}LPHY_SG_CQI_DISP_RB_WHITEN_FLAG_STRU;
/************************************/
typedef struct
{
	UINT32	aulPercent[CQI_MAX_CA_NUM+1];
}LPHY_SG_CQI_DISP_RI_PERCENT_STRU;
/************************************/
typedef struct
{
    LPHY_CA_CC_ENUM_UINT16 	enCc;
	UINT8					ucHetnet;
	UINT8					aucRsv[1];
}LPHY_SG_CQI_DISP_SB_PMI_PERCENT_STRU;
/************************************/
typedef struct
{
    LPHY_CA_CC_ENUM_UINT16 	enCc;
	UINT8					ucHetnet;
	UINT8					aucRsv[1];
}LPHY_SG_CQI_DISP_WB_PMI_PERCENT_STRU;
/************************************/
typedef struct
{
    LPHY_CA_CC_ENUM_UINT16 	enCc;
	UINT8					ucHetnet;
	UINT8					aucRsv[1];
}LPHY_SG_CQI_DISP_SB_CQI_PERCENT_STRU;
/************************************/
typedef struct
{
    LPHY_CA_CC_ENUM_UINT16 	enCc;
	UINT8					ucHetnet;
	UINT8					aucRsv[1];
}LPHY_SG_CQI_DISP_WB_CQI_PERCENT_STRU;
/************************************/
typedef struct
{
    LPHY_CA_CC_ENUM_UINT16 	enCc;
	UINT8					ucHetnet;
	UINT8					aucRsv[1];
}LPHY_SG_CQI_DISP_WB_CQI_MEDIAN_STRU;
/************************************/
typedef struct
{
    LPHY_CA_CC_ENUM_UINT16 	enCc;
	UINT8					ucHetnet;
	UINT8					aucRsv[1];
}LPHY_SG_CQI_DISP_PA_PC_DELTAOFSET_STRU;
/************************************/


/************************************************************
                           3. CNF数据结构定义
************************************************************/
typedef enum __LPHY_CNF_MSGID_CQI__
{
    LPHY_CNF_CQI_RESERVED            = OM_CMD_ID(LPHY_CQI_MID, OM_TYPE_CNF, 0x0),
}LPHY_CNF_MSGID_CQI_ENUM;


/************************************************************
                           4. Ind数据结构定义
************************************************************/
typedef enum __LPHY_IND_MSGID_CQI__
{
    LPHY_IND_CQI_RESERVED            = OM_CMD_ID(LPHY_CQI_MID, OM_TYPE_IND, 0x0),
}LPHY_IND_MSGID_CQI_ENUM;

/************************************************************
                           5. TRACE数据结构定义
************************************************************/
typedef enum __LPHY_TRACE_CQI__
{
    LPHY_TRACE_CQI_RESERVED         =  OM_CMD_ID(LPHY_CQI_MID, OM_TYPE_TRACE, 0x0),
    LPHY_TRACE_CQI_TRACE_BINARY,
    LPHY_TRACE_CQI_CONFIG,
    LPHY_TRACE_CQI_INVALID_PARA
}LPHY_TRACE_CQI_ENUM;

typedef struct __LPHY_TRACE_CQI_INVALID_PARA_STRU__
{
    INT32       lErrNo;             /*表示参数无效码*/
}LPHY_TRACE_CQI_INVALID_PARA_STRU;

/************************************************************
                           6. Error数据结构定义
************************************************************/
typedef enum __LPHY_ERROR_CQI__
{
    LPHY_ERROR_CQI_RESERVED         =  OM_CMD_ID(LPHY_CQI_MID, OM_TYPE_ERROR, 0x0),
    LPHY_ERROR_CQI_STAT
}LPHY_ERROR_CQI_ENUM;

/************************************************************
                           7. DT路测数据结构定义
************************************************************/
	typedef enum __LPHY_DT_MSGID_CQI__
	{
		LPHY_DT_CQI_RESERVED			= OM_CMD_ID(LPHY_CQI_MID, OM_TYPE_DT, 0x0),

	}LPHY_DT_MSGID_CQI_ENUM;


/************************************************************
                           8. CQI DEBUG 观察信息
************************************************************/
/**************************
1   CQI   BBP 配置
配置当前子帧
15  WORD     from 5 word  2cc 20word
***************************/
typedef struct
{
    UINT8   ucCC;
    UINT8   ucTrms;
    UINT8   ucVelocity;
    UINT8   ucCorr;

    UINT8   ucWhiteSel;//CH0_CQI_WHITE_SEL
    UINT8   ucPcqiEnAndBusy;//CH0_PMOD_CQI_EN and BUSY
    UINT8   ucAcqiEnAndBusy;//CH0_AMOD_CQI_EN and BUSY
    UINT8   ucAntNum;

    UINT16  usPcqiType;
    UINT16  usAcqiType;
    
    UINT32  ulEnFlag;//
    UINT32  ulTransMode;//CH0_NORM_TRANS_MOD
    UINT32  ulCmuPmatrix;//CH0_CQI_WBNOISE_PMATRIX0

    /*只读取 ant0 和ant4*/
    UINT32 ulNoise_CMU_Rx[4];        //CMU输入的噪声,分接收天线送入
    UINT32 ulCSIDAGCGain[4];        //Rx0/1/2/3的CSI-RS的DAGC增益,信道估计提供
    INT16  sSinrDB_Rx[4];//以(1/4)dB为单位的当前子帧集合所对应的SINR值,CMU给出
    INT16  sAGCPowGaindB_CRS[4];    //Rx 0/1/2/3的使用CRS Ruu对应的信号功率的AGC增益,AGC_GetAGCGainAnt0(enCc)
    INT16  sAGCPowGaindB_CSIRS[4];    //CSI-RS子帧的AAGC增益
    
    UINT16  ausRsv[4];    //保证字节对齐
}CQI_BBP_CFG_REGS_OM_STRU;

/**************************
2 读取 BBP  TCM  CQI 上报信息
读取上一子帧
14  WORD   from 35word    channel1 49word
**************************/
typedef struct
{
    UINT8  ucValid;
    UINT8  ucCC;
    UINT16  usCsiFlag;// 0---CRS   1---CSI
    UINT32  ulH[4];//取对应小区  前两个H      H--当前帧     CSI上一子帧
    UINT32  ulP[4];//取对应小区   P  上一子帧  
                  
    UINT16  usEsnr;// 瞬时BBP   PMOD
    UINT16  usRi;// 瞬时BBP   PMOD
    UINT32  ulWbcqi;// 瞬时BBP  PMOD
    
    UINT32  ulRbirCur[4];// 瞬时
    UINT32	ulR1RbirSum;
    UINT32	ulR2RbirSum;
    UINT32	ulR3RbirSum;
    UINT32	ulR4RbirSum;// 滤波r1~r4


    UINT32  aulRsv0[2];    
    UINT16  ausRsv1[2];    
    UINT32  aulRsv2[6];        
}CQI_BBP_RPT_REGS_OM_STRU;

/***************************
3 读取调度  CQI信息
配置当前子帧
7word  form   63word  
***************************/
typedef struct
{
    UINT8   aucCcSelected [CQI_MAX_CA_NUM];        //bbp调度结果，指示该cc是否被选中，0--未选中，1--被选中
    UINT8   aucCcChannelId[CQI_MAX_CA_NUM];        //bbp调度结果，该cc如果被选中，被分配的channel号，0,1
    UINT32  ucHetnet;                            //pcc,当前子帧的hetnet属性,0,1,0xff
    INT16   asPriority[CQI_MAX_CA_NUM +1];    //索引由函数 Cqi_GetRsrcIdx() 确定
    
    UINT16  ausRsv[CQI_MAX_CA_NUM +1];    //保证字节对齐
}CQI_SCHEDULE_OM_STRU;//上报CQI信息

/***************************
上报拼装  CQI信息
****************************/
typedef struct
{
    UINT8   ucCcAct; 
    UINT8   ucPcqiType;
    UINT8   enWbSbInd;
    UINT8   ucRptReq;
    
    UINT32   aulRsv[2];    //保证字节对齐
    UINT16   ausRsv[2];    //保证字节对齐
}CQI_PCQI_RPT_OM_STRU;

typedef struct
{
    UINT16  usSysFrmNum;
    UINT16  usSubFrmNum;
    UINT32  aulCellCfg[CQI_MAX_CA_NUM];//CC_CELL_CFG
    CQI_BBP_CFG_REGS_OM_STRU astCqiCfgRegOm[2];// 2--ch0 ch1
    CQI_BBP_RPT_REGS_OM_STRU astCqiRptRegOm[2];// 2--ch0 ch1
    CQI_SCHEDULE_OM_STRU stCqiSchudInfo;
    CQI_PCQI_RPT_OM_STRU astCqiRptInfo[CQI_MAX_CA_NUM +1];
}LPHY_SG_CQI_DISP_DEBUG_STRU;

#ifdef __cplusplus
#if __cplusplus
}
#endif
#endif /* __cplusplus */


#endif /* __CQI_OM_DEF_H__ */
