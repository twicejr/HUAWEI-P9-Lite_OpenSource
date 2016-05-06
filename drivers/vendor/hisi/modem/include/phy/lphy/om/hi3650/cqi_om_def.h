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

typedef enum
{
	CQI_A12 = 0,
	CQI_A20,
	CQI_A22,
	CQI_A30,
	CQI_A31,
	CQI_P10,
	CQI_P11,
	CQI_P20,
	CQI_P21,
	CQI_BUTT
}CQI_TYPE_ENUM;
typedef UINT8 CQI_TYPE_ENUM_UINT8;

/************************************************************
                           1. REQ命令和对应的数据结构定义
************************************************************/
typedef enum __LPHY_REQ_MSGID_CQI__
{
    LPHY_REQ_CQI_RESERVED            = OM_CMD_ID(LPHY_CQI_MID, OM_TYPE_REQ, 0x0),
    LPHY_REQ_CQI_TRMS_FILTER,                    //TrmsFlag的滤波因子和TrmsInd的门限判断
    LPHY_REQ_CQI_FLAGS,                          //TrmsFlag、SNRFlag、VelocityFlag、CorrFlag
    LPHY_REQ_CQI_NOISE_FACTOR_ETA2,              //计算模式的噪声修正因子，分SFBC,SM1,SM2
    LPHY_REQ_CQI_NPA,                            //计算信噪比时的修正参数NPA
    LPHY_REQ_CQI_RBIR_ALPHA,                     //CQI的RBIR滤波因子
    LPHY_REQ_CQI_RI_EFF_ALPHA,                   //RI计算效率滤波时的滤波因子
    LPHY_REQ_CQI_RI_THRESH_BETA1,                //RI计算时，前一个计算结果为1时的效率门限值
    LPHY_REQ_CQI_RI_THRESH_BETA2,                //RI计算时，前一个计算结果为2时的效率门限值
    LPHY_REQ_CQI_RI1_SEL_THRESH_SNR_ALPHA,       //RI计算时，秩为1的有效SNR滤波因子
    LPHY_REQ_CQI_RI1_SEL_THRESH_SNR_THRESH,      //RI门限选择时的有效SNR门限
    LPHY_REQ_CQI_RI_STUB,                        //计算的RI
    LPHY_REQ_CQI_R2_WB_CQI_STUB,                 //计算的宽带R2 CQI
    LPHY_REQ_CQI_R1_WB_CQI_STUB,                 //计算的宽带R1 CQI
    LPHY_REQ_CQI_R2_SB_CQI_STUB,                 //计算的子带R2 CQI
    LPHY_REQ_CQI_R1_SB_CQI_STUB,                 //计算的子带R1 CQI 
    LPHY_REQ_CQI_R2_WB_PMI_STUB,                 //计算的宽带R2 PMI
    LPHY_REQ_CQI_R1_WB_PMI_STUB,                 //计算的宽带R1 PMI
    LPHY_REQ_CQI_R2_SB_PMI_STUB,                 //计算的子带R2 PMI
    LPHY_REQ_CQI_R1_SB_PMI_STUB,                 //计算的子带R1 PMI
    LPHY_REQ_CQI_UNEVEN_THRESHOLD,               //CQI的干扰不平衡门限
    LPHY_REQ_CQI_PMI_TRANS_FACTOR,               //PMI跳变因子
    LPHY_REQ_CQI_PTI_FIRSTPMI_ALPHA,             //估计PTI时的FirstPMI的滤波因子
    LPHY_REQ_CQI_OLLA_SWITCH,                    //CQI是否根据OLLA进行调整的标示
    LPHY_REQ_CQI_OLLA_ADJSTEP,                   //CQI OLLA调整时向下和向上调整的步长
    LPHY_REQ_CQI_OLLA_ALPHA,                     //CQI OLLA时的CQI滤波因子
    LPHY_REQ_CQI_HETNET_RSRP_GAP,                //Hetnet场景下RSRP的差距
    LPHY_REQ_CQI_ABSSFM_ESNR_COMPENSATE,         //Hetnet场景下ABS子帧时的ESNR的修正值
    LPHY_REQ_CQI_CSISET1_ABSFLAG,                //CSI集合1是否为ABS的Flag
    LPHY_REQ_CQI_FIRSTPMI_ALPHA,                 //FirstPMI滤波因子
    LPHY_REQ_CQI_TSNR,                           //CQI的目标信干噪比
    LPHY_REQ_CQI_PTI_STUB,                       //PTI上报结果
    LPHY_REQ_CQI_RPT_SG,                         //SG上报使能
	LPHY_REQ_CQI_RPT_PERI,						 //SG上报频率
	LPHY_DT_CQI_INFO_REQ            = OM_CMD_ID(LPHY_CQI_MID, OM_TYPE_REQ, 0x100)
    //LPHY_REQ_CQI_ESNR_COMPENSATE,                //信噪比功率补偿值
    //LPHY_REQ_CQI_RI_EFF_SCALE,                   //RI选择时的效率比例因子
    //LPHY_REQ_CQI_RI_ESNRA_ESNRB,                 //判断是否根据RBIR来选择RI的因子A和B
    //LPHY_REQ_CQI_WHITE_SEL,                      //白化开关配置
    //LPHY_REQ_CQI_DELTA_OFFSET,                   //DeltaOffset
    //LPHY_REQ_CQI_CSIRSH_CRSP_FLAG,               //白化矩阵选择
    //LPHY_REQ_CQI_PTI_THD,                        //PTI的偏差和方差的门限
    //LPHY_REQ_CQI_RIN_RITHRESH,                   //统计RI的次数和次数判断门限
    //LPHY_REQ_CQI_RI_FLAG,                        //RI选择的Flag
    //LPHY_REQ_CQI_WBNORM_AND_SBNORM,              //CQI计算时白化时的宽带和自带归一因子
    //LPHY_REQ_CQI_NOISE_FACTOR,                   //噪声场景修正因子
    //LPHY_REQ_CQI_RI_FACTOR,                      //根据Trms,相关性,白化,传输模式和双工模式进行调整RI门限调整的因子
}LPHY_REQ_MSGID_CQI_ENUM;

typedef struct __LPHY_REQ_CQI_TRMS_FILTER_STRU__
{
    OM_REQ_ENABLE_ENUM_UINT16   enEn;
    UINT8                       ucAlpha;
	UINT16                      usThreshold;
    UINT8                       ucRsv[3];               /*4字节对齐*/
}LPHY_REQ_CQI_TRMS_FILTER_STRU;

typedef struct __LPHY_REQ_CQI_FLAGS_STRU__
{
    OM_REQ_ENABLE_ENUM_UINT16       enEn;
    LTE_CHAN_SPACE_CORR_ENUM_UINT8  enCorrFlag;
    UINT8                           ucTrmsFlag;
    UINT8                           ucSNRFlag;
    UINT8                           ucVelocityFlag;
    UINT8                           ucRsv[2];           /*4字节对齐*/    
}LPHY_REQ_CQI_FLAGS_STRU;

typedef struct __LPHY_REQ_CQI_NOISE_FACTOR_ETA2_STRU__
{
    OM_REQ_ENABLE_ENUM_UINT16   enEn;
    UINT16                      usSFBC;                 /*sfbc eta2*/
    UINT16                      usSM1;                  /*sm1 eta2*/
    UINT16                      usSM2;                  /*sm2 eta2*/
}LPHY_REQ_CQI_NOISE_FACTOR_ETA2_STRU;

typedef struct __LPHY_REQ_CQI_NPA_STRU__
{
    OM_REQ_ENABLE_ENUM_UINT16   enEn;
    UINT16                      usNpa[2][8];            /*2 or 4 trans ant num*/
    UINT8                       ucRsv[2];               /*4字节对齐*/
}LPHY_REQ_CQI_NPA_STRU;

typedef struct __LPHY_REQ_CQI_ESNR_COMPENSATE_STRU__
{
    OM_REQ_ENABLE_ENUM_UINT16   enEn;
    UINT16                      usEsnrComp[2][8];       /*2 or 4 trans ant num*/
    UINT8                       ucRsv[2];               /*4字节对齐*/
}LPHY_REQ_CQI_ESNR_COMPENSATE_STRU;

typedef struct __LPHY_REQ_CQI_RBIR_ALPHA_STRU__
{
    OM_REQ_ENABLE_ENUM_UINT16   enEn;
    UINT16                      usWbAlpha;
    UINT16                      usSbAlpha;
    UINT8                       ucRsv[2];               /*4字节对齐*/
}LPHY_REQ_CQI_RBIR_ALPHA_STRU;

typedef struct __LPHY_REQ_CQI_RI_EFF_ALPHA_STRU__
{
    OM_REQ_ENABLE_ENUM_UINT16   enEn;
    UINT16                      usEffAlpha;             /* (0，1，2，3，4，5，6，7）对应（1，1/2，1/4，1/8，1/16，1/32，1/64，1/128*/
}LPHY_REQ_CQI_RI_EFF_ALPHA_STRU;

typedef struct __LPHY_REQ_CQI_RI_THRESH_BETA1_STRU__
{
    OM_REQ_ENABLE_ENUM_UINT16   enEn;
    UINT16                      usBeta1;                /*7u*/
}LPHY_REQ_CQI_RI_THRESH_BETA1_STRU;

typedef struct __LPHY_REQ_CQI_RI_THRESH_BETA2_STRU__
{
    OM_REQ_ENABLE_ENUM_UINT16   enEn;
    UINT16                      usBeta2;                /*7u*/
}LPHY_REQ_CQI_RI_THRESH_BETA2_STRU;

typedef struct __LPHY_REQ_CQI_RI1_SEL_THRESH_SNR_ALPHA_STRU__
{
    OM_REQ_ENABLE_ENUM_UINT16   enEn;
    UINT16                      usSnrAlpha;             /*3u*/
}LPHY_REQ_CQI_RI1_SEL_THRESH_SNR_ALPHA_STRU;

typedef struct __LPHY_REQ_CQI_RI1_SEL_THRESH_SNR_THRESH_STRU__
{
    OM_REQ_ENABLE_ENUM_UINT16   enEn;
    INT16                       sThresh;                /*10s*/
}LPHY_REQ_CQI_RI1_SEL_THRESH_SNR_THRESH_STRU;

typedef struct __LPHY_REQ_CQI_RI_EFF_SCALE_STRU__
{
    OM_REQ_ENABLE_ENUM_UINT16   enEn;
    UINT16                      usEffScale;             /*7u*/
}LPHY_REQ_CQI_RI_EFF_SCALE_STRU;

typedef struct __LPHY_REQ_CQI_RI_ESNRA_ESNRB_STRU__
{
    OM_REQ_ENABLE_ENUM_UINT16   enEn;
    UINT8                       ucESNRA;                /*6u*/
    UINT8                       ucESNRB;                /*6u*/
}LPHY_REQ_CQI_RI_ESNRA_ESNRB_STRU;

typedef struct __LPHY_REQ_CQI_RI_STUB_STRU__
{
    OM_REQ_ENABLE_ENUM_UINT16   enEn;
    UINT16                      usPeriRI;
    UINT16                      usAperRI;
    UINT8                       ucRsv[2];       /*4字节对齐*/    
}LPHY_REQ_CQI_RI_STUB_STRU;

typedef struct __LPHY_REQ_CQI_R2_WB_CQI_STUB_STRU__
{
    OM_REQ_ENABLE_ENUM_UINT16   enEn;
    UINT16                  usCw0Cqi;
    UINT16                  usCw1Cqi;
    UINT16                     usPmi;
}LPHY_REQ_CQI_R2_WB_CQI_STUB_STRU;

typedef struct __LPHY_REQ_CQI_R1_WB_CQI_STUB_STRU__
{
    OM_REQ_ENABLE_ENUM_UINT16   enEn;
    UINT16                  usCw0Cqi;
    UINT16                     usPmi;
    UINT8                   ucRsv[2];           /*4字节对齐*/
}LPHY_REQ_CQI_R1_WB_CQI_STUB_STRU;

typedef struct __LPHY_REQ_CQI_R2_SB_CQI_STUB_STRU__
{
    OM_REQ_ENABLE_ENUM_UINT16   enEn;
    UINT16               usSbPos[13];
    UINT16              usCw0Cqi[13];
    UINT16              usCw1Cqi[13];
    UINT16                 usPmi[13];
    UINT8                   ucRsv[2];           /*4字节对齐*/
}LPHY_REQ_CQI_R2_SB_CQI_STUB_STRU;

typedef struct __LPHY_REQ_CQI_R1_SB_CQI_STUB_STRU__
{
    OM_REQ_ENABLE_ENUM_UINT16   enEn;
    UINT16               usSbPos[13];
    UINT16              usCw0Cqi[13];
    UINT16                 usPmi[13];
}LPHY_REQ_CQI_R1_SB_CQI_STUB_STRU;

typedef struct __LPHY_REQ_CQI_R2_WB_PMI_STUB_STRU__
{
    OM_REQ_ENABLE_ENUM_UINT16   enEn;
    UINT16                     usPmi;
}LPHY_REQ_CQI_R2_WB_PMI_STUB_STRU;

typedef struct __LPHY_REQ_CQI_R1_WB_PMI_STUB_STRU__
{
    OM_REQ_ENABLE_ENUM_UINT16   enEn;
    UINT16                     usPmi;
}LPHY_REQ_CQI_R1_WB_PMI_STUB_STRU;

typedef struct __LPHY_REQ_CQI_R2_SB_PMI_STUB_STRU__
{
    OM_REQ_ENABLE_ENUM_UINT16   enEn;
    UINT16                 usPmi[13];
}LPHY_REQ_CQI_R2_SB_PMI_STUB_STRU;

typedef struct __LPHY_REQ_CQI_R1_SB_PMI_STUB_STRU__
{
    OM_REQ_ENABLE_ENUM_UINT16   enEn;
    UINT16                 usPmi[13];
}LPHY_REQ_CQI_R1_SB_PMI_STUB_STRU;

typedef struct __LPHY_REQ_CQI_WHITE_SEL_STRU__
{
    OM_REQ_ENABLE_ENUM_UINT16   enEn;
	UINT8                 ucWhiteSel;
	UINT8                      ucRsv;
}LPHY_REQ_CQI_WHITE_SEL_STRU;

typedef struct __LPHY_REQ_CQI_DELTA_OFFSET_STRU__
{
    OM_REQ_ENABLE_ENUM_UINT16   enEn;
	INT16               sDeltaOffset;
}LPHY_REQ_CQI_DELTA_OFFSET_STRU;

typedef struct __LPHY_REQ_CQI_CSIRSH_CRSP_FLAG_STRU__
{
    OM_REQ_ENABLE_ENUM_UINT16   enEn;
	UINT8           ucCsirsHCrsPFlag;
	UINT8                      ucRsv;
}LPHY_REQ_CQI_CSIRSH_CRSP_FLAG_STRU;

typedef struct __LPHY_REQ_CQI_UNEVEN_THRESHOLD_STRU__
{
    OM_REQ_ENABLE_ENUM_UINT16   enEn;
	UINT16         usUnevenThreshold;
}LPHY_REQ_CQI_UNEVEN_THRESHOLD_STRU;

typedef struct __LPHY_REQ_CQI_PMI_TRANS_FACTOR_STRU__
{
    OM_REQ_ENABLE_ENUM_UINT16   enEn;
	UINT16               usFactor[5];
}LPHY_REQ_CQI_PMI_TRANS_FACTOR_STRU;

typedef struct __LPHY_REQ_CQI_PTI_FIRSTPMI_ALPHA_STRU__
{
    OM_REQ_ENABLE_ENUM_UINT16   enEn;
    UINT16                   usAlpha;
}LPHY_REQ_CQI_PTI_FIRSTPMI_ALPHA_STRU;

typedef struct __LPHY_REQ_CQI_PTI_THD_STRU__
{
    OM_REQ_ENABLE_ENUM_UINT16   enEn;
	UINT16              usPTIBiasThd; //10u
	UINT16               usPTIVarThd; //10u
	UINT16                     usRsv;
}LPHY_REQ_CQI_PTI_THD_STRU;

typedef struct __LPHY_REQ_CQI_OLLA_SWITCH_STRU__
{
    OM_REQ_ENABLE_ENUM_UINT16   enEn;
	UINT8             ucCqiAdjSwitch; //1u
	UINT8                      ucRsv;
}LPHY_REQ_CQI_OLLA_SWITCH_STRU;

typedef struct __LPHY_REQ_CQI_OLLA_ADJSTEP_STRU__
{
    OM_REQ_ENABLE_ENUM_UINT16   enEn;
	UINT8           ucCqiAdjStepDown; //5u
	UINT8             ucCqiAdjStepUp; //5u
}LPHY_REQ_CQI_OLLA_ADJSTEP_STRU;

typedef struct __LPHY_REQ_CQI_OLLA_ALPHA_STRU__
{
    OM_REQ_ENABLE_ENUM_UINT16   enEn;
	UINT8                    ucAlpha; //6u
	UINT8                      ucRsv;
}LPHY_REQ_CQI_OLLA_ALPHA_STRU;

typedef struct __LPHY_REQ_CQI_RIN_RITHRESH_STRU__
{
    OM_REQ_ENABLE_ENUM_UINT16   enEn;
	UINT8                      ucRiN; //8u
	INT16               sRiThreshold; //10s tbc
	UINT8                   ucRsv[3];
}LPHY_REQ_CQI_RIN_RITHRESH_STRU;

typedef struct __LPHY_REQ_CQI_RI_FACTOR_STRU__
{
    OM_REQ_ENABLE_ENUM_UINT16   enEn;
	UINT16         usRiFactorTrms[3];
	UINT16         usRiFactorCorr[3];
	UINT16    usRiFactorTransMode[4];
	UINT16       usRiFactorDuplex[2];
	UINT16       usRiFactorWhiten[2];
	UINT16                     usRsv;
}LPHY_REQ_CQI_RI_FACTOR_STRU;

typedef struct __LPHY_REQ_CQI_RI_FLAG_STRU__
{
    OM_REQ_ENABLE_ENUM_UINT16   enEn;
	UINT8                   ucRiFlag; //1u
	UINT8                      ucRsv;
}LPHY_REQ_CQI_RI_FLAG_STRU;

typedef struct __LPHY_REQ_CQI_WBNORM_AND_SBNORM_STRU__
{
    OM_REQ_ENABLE_ENUM_UINT16   enEn;
	UINT8                ucNormWb[6]; //8u
	UINT8                ucNormSb[8]; //8u
}LPHY_REQ_CQI_WBNORM_AND_SBNORM_STRU;

typedef struct __LPHY_REQ_CQI_HETNET_RSRP_GAP_STRU__
{
    OM_REQ_ENABLE_ENUM_UINT16   enEn;
	UINT16                 usFactor1; //10u
	UINT16                 usFactor2; //11u
	UINT16                 usFactor3; //10u
	UINT16                 usFactor4; //11u
	UINT16                     usRsv;
}LPHY_REQ_CQI_HETNET_RSRP_GAP_STRU;

typedef struct __LPHY_REQ_CQI_ABSSFM_ESNR_COMPENSATE_STRU__
{
    OM_REQ_ENABLE_ENUM_UINT16   enEn;
	INT8              cSNRFactor5[3]; //8s
	INT8              cSNRFactor6[3]; //8s
}LPHY_REQ_CQI_ABSSFM_ESNR_COMPENSATE_STRU;

typedef struct __LPHY_REQ_CQI_CSISET1_ABSFLAG_STRU__
{
    OM_REQ_ENABLE_ENUM_UINT16   enEn;
	UINT8                  ucAbsFlag; //1u
	UINT8                      ucRsv;
}LPHY_REQ_CQI_CSISET1_ABSFLAG_STRU;

typedef struct __LPHY_REQ_CQI_FIRSTPMI_ALPHA_STRU__
{
    OM_REQ_ENABLE_ENUM_UINT16   enEn;
	UINT16                   usAlpha;
}LPHY_REQ_CQI_FIRSTPMI_ALPHA_STRU;

typedef struct __LPHY_REQ_CQI_TSNR_STRU__
{
    OM_REQ_ENABLE_ENUM_UINT16   enEn;
	INT16                  sTsnr[15]; //10s
}LPHY_REQ_CQI_TSNR_STRU;

typedef struct _LPHY_REQ_CQI_NOISE_FACTOR_STRU__
{
    OM_REQ_ENABLE_ENUM_UINT16   enEn;
	UINT16             usNoiseFactor; //9u
}LPHY_REQ_CQI_NOISE_FACTOR_STRU;

typedef struct __LPHY_REQ_CQI_PTI_STUB_STRU__
{
    OM_REQ_ENABLE_ENUM_UINT16   enEn;
	UINT8                      usPti; //1u
    UINT8                   ucRsv[2];       /*4字节对齐*/
}LPHY_REQ_CQI_PTI_STUB_STRU;

typedef struct __LPHY_REQ_CQI_RPT_SG_STRU__
{
    OM_REQ_ENABLE_ENUM_UINT16   enEn;
    UINT8                   ucRsv[2];       /*4字节对齐*/
}LPHY_REQ_CQI_RPT_SG_STRU;

typedef struct __LPHY_REQ_CQI_RPT_PERI_STRU__
{
    OM_REQ_ENABLE_ENUM_UINT16   enRptEn;
    UINT8						ucOmRptPeri;       /*4字节对齐*/
    UINT8                   	ucRsv;       	   /*4字节对齐*/
}LPHY_REQ_CQI_RPT_PERI_STRU;

/************************************************************
                           2. CNF数据结构定义
************************************************************/
typedef enum __LPHY_CNF_MSGID_CQI__
{
    LPHY_CNF_CQI_RESERVED            = OM_CMD_ID(LPHY_CQI_MID, OM_TYPE_CNF, 0x0),
    LPHY_CNF_CQI_STUB,
}LPHY_CNF_MSGID_CQI_ENUM;


/************************************************************
                           3. Ind数据结构定义
************************************************************/
typedef enum __LPHY_IND_MSGID_CQI__
{
    LPHY_IND_CQI_RESERVED            = OM_CMD_ID(LPHY_CQI_MID, OM_TYPE_IND, 0x0),
}LPHY_IND_MSGID_CQI_ENUM;

/************************************************************
                           4. TRACE数据结构定义
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
                           5. SG 数据结构定义, 算法需要绘图的
************************************************************/
    //OM_Report(OM_REPORT_LEVEL_INFO, OM_DEFAULT_SESSION_ID, LPHY_SG_CQI_PCELL_RI,(UINT8*)&stRi, sizeof(LPHY_SG_CQI_PCELL_RI_STRU));

typedef enum __LPHY_SG_MSGID_CQI__
{
    LPHY_SG_CQI_RESERVED            = OM_CMD_ID(LPHY_CQI_MID, OM_TYPE_SG, 0x0),

	LPHY_SG_CQI_RPT_PCELL_PERIODIC_CS0_R1_ESNR,      /*主载波ESNR的结果*/
	LPHY_SG_CQI_RPT_PCELL_PERIODIC_CS0_R2_ESNR,      /*主载波ESNR的结果*/
	LPHY_SG_CQI_RPT_PCELL_PERIODIC_CS0_R1_EFFI,		/*主载波EFFI的结果*/
	LPHY_SG_CQI_RPT_PCELL_PERIODIC_CS0_R2_EFFI,		/*主载波EFFI的结果*/
	LPHY_SG_CQI_RPT_PCELL_PERIODIC_CS0_RI_RESULT,		 /*上报主载波RI的结果*/
	LPHY_SG_CQI_RPT_PCELL_PERIODIC_CS0_R1_WCQI_RESULT,	 /*上报主载波宽带CQI的结果*/
	LPHY_SG_CQI_RPT_PCELL_PERIODIC_CS0_R2_WCQI_RESULT,	 /*上报主载波宽带CQI的结果*/
	LPHY_SG_CQI_RPT_PCELL_PERIODIC_CS0_R1_SCQI_RESULT,	 /*上报主载波子带CQI的结果*/
	LPHY_SG_CQI_RPT_PCELL_PERIODIC_CS0_R2_SCQI_RESULT,	 /*上报主载波子带CQI的结果*/
	LPHY_SG_CQI_RPT_PCELL_PERIODIC_CS0_R1_WPMI_RESULT,	 /*上报主载波宽带PMI的结果*/
	LPHY_SG_CQI_RPT_PCELL_PERIODIC_CS0_R2_WPMI_RESULT,	 /*上报主载波宽带PMI的结果*/
	LPHY_SG_CQI_RPT_PCELL_PERIODIC_CS0_R1_SPMI_RESULT,	 /*上报主载波子带PMI的结果*/
	LPHY_SG_CQI_RPT_PCELL_PERIODIC_CS0_R2_SPMI_RESULT,	 /*上报主载波子带PMI的结果*/
	LPHY_SG_CQI_RPT_PCELL_PERIODIC_CS0_R1_BESTM_PMI_RESULT, 
	LPHY_SG_CQI_RPT_PCELL_PERIODIC_CS0_R2_BESTM_PMI_RESULT,
	LPHY_SG_CQI_RPT_PCELL_PERIODIC_CS0_R1_BESTM_CQI_RESULT,
	LPHY_SG_CQI_RPT_PCELL_PERIODIC_CS0_R2_BESTM_CQI_RESULT,
	LPHY_SG_CQI_RPT_PCELL_PERIODIC_CS0_R1_BP_BEST_SB_CQI_RESULT,
	LPHY_SG_CQI_RPT_PCELL_PERIODIC_CS0_R2_BP_BEST_SB_CQI_RESULT,
	LPHY_SG_CQI_RPT_PCELL_PERIODIC_CS0_CSI_PARA, 	/*和CSI相关的deltaOffset,PA和PC*/
	LPHY_SG_CQI_RPT_PCELL_PERIODIC_CS0_CQI_RPT_INFO,
	LPHY_SG_CQI_RPT_PCELL_PERIODIC_CS0_STAT,				 /*上报CQI/PMI/RI计数*/

	LPHY_SG_CQI_RPT_PCELL_PERIODIC_CS1_R1_ESNR,      /*主载波ESNR的结果*/
	LPHY_SG_CQI_RPT_PCELL_PERIODIC_CS1_R2_ESNR,      /*主载波ESNR的结果*/
	LPHY_SG_CQI_RPT_PCELL_PERIODIC_CS1_R1_EFFI,		/*主载波EFFI的结果*/
	LPHY_SG_CQI_RPT_PCELL_PERIODIC_CS1_R2_EFFI,		/*主载波EFFI的结果*/
	LPHY_SG_CQI_RPT_PCELL_PERIODIC_CS1_RI_RESULT,		 /*上报主载波RI的结果*/
	LPHY_SG_CQI_RPT_PCELL_PERIODIC_CS1_R1_WCQI_RESULT,	 /*上报主载波宽带CQI的结果*/
	LPHY_SG_CQI_RPT_PCELL_PERIODIC_CS1_R2_WCQI_RESULT,	 /*上报主载波宽带CQI的结果*/
	LPHY_SG_CQI_RPT_PCELL_PERIODIC_CS1_R1_SCQI_RESULT,	 /*上报主载波子带CQI的结果*/
	LPHY_SG_CQI_RPT_PCELL_PERIODIC_CS1_R2_SCQI_RESULT,	 /*上报主载波子带CQI的结果*/
	LPHY_SG_CQI_RPT_PCELL_PERIODIC_CS1_R1_WPMI_RESULT,	 /*上报主载波宽带PMI的结果*/
	LPHY_SG_CQI_RPT_PCELL_PERIODIC_CS1_R2_WPMI_RESULT,	 /*上报主载波宽带PMI的结果*/
	LPHY_SG_CQI_RPT_PCELL_PERIODIC_CS1_R1_SPMI_RESULT,	 /*上报主载波子带PMI的结果*/
	LPHY_SG_CQI_RPT_PCELL_PERIODIC_CS1_R2_SPMI_RESULT,	 /*上报主载波子带PMI的结果*/
	LPHY_SG_CQI_RPT_PCELL_PERIODIC_CS1_R1_BESTM_PMI_RESULT, 
	LPHY_SG_CQI_RPT_PCELL_PERIODIC_CS1_R2_BESTM_PMI_RESULT,
	LPHY_SG_CQI_RPT_PCELL_PERIODIC_CS1_R1_BESTM_CQI_RESULT,
	LPHY_SG_CQI_RPT_PCELL_PERIODIC_CS1_R2_BESTM_CQI_RESULT,
	LPHY_SG_CQI_RPT_PCELL_PERIODIC_CS1_R1_BP_BEST_SB_CQI_RESULT,
	LPHY_SG_CQI_RPT_PCELL_PERIODIC_CS1_R2_BP_BEST_SB_CQI_RESULT,
	LPHY_SG_CQI_RPT_PCELL_PERIODIC_CS1_CSI_PARA, 	/*和CSI相关的deltaOffset,PA和PC*/
	LPHY_SG_CQI_RPT_PCELL_PERIODIC_CS1_CQI_RPT_INFO,
	LPHY_SG_CQI_RPT_PCELL_PERIODIC_CS1_STAT,				 /*上报CQI/PMI/RI计数*/
	
	LPHY_SG_CQI_RPT_SCELL_R1_ESNR,		/*副载波ESNR的结果*/
	LPHY_SG_CQI_RPT_SCELL_R2_ESNR,		/*副载波ESNR的结果*/
	LPHY_SG_CQI_RPT_SCELL_R1_EFFI,		/*副载波EFFI的结果*/
	LPHY_SG_CQI_RPT_SCELL_R2_EFFI,		/*副载波EFFI的结果*/
	LPHY_SG_CQI_RPT_SCELL_RI_RESULT,		 /*上报副载波RI的结果*/
	LPHY_SG_CQI_RPT_SCELL_R1_WCQI_RESULT,	 /*上报副载波宽带CQI的结果*/
	LPHY_SG_CQI_RPT_SCELL_R2_WCQI_RESULT,    /*上报副载波宽带CQI的结果*/
	LPHY_SG_CQI_RPT_SCELL_R1_SCQI_RESULT,	 /*上报副载波子带CQI的结果*/
	LPHY_SG_CQI_RPT_SCELL_R2_SCQI_RESULT,    /*上报副载波子带CQI的结果*/
	LPHY_SG_CQI_RPT_SCELL_R1_WPMI_RESULT,    /*上报副载波宽带PMI的结果*/
	LPHY_SG_CQI_RPT_SCELL_R2_WPMI_RESULT,    /*上报副载波宽带PMI的结果*/
	LPHY_SG_CQI_RPT_SCELL_R1_SPMI_RESULT,    /*上报副载波子带PMI的结果*/
	LPHY_SG_CQI_RPT_SCELL_R2_SPMI_RESULT,    /*上报副载波子带PMI的结果*/
	LPHY_SG_CQI_RPT_SCELL_R1_BESTM_PMI_RESULT,
	LPHY_SG_CQI_RPT_SCELL_R2_BESTM_PMI_RESULT,
	LPHY_SG_CQI_RPT_SCELL_R1_BESTM_CQI_RESULT,
	LPHY_SG_CQI_RPT_SCELL_R2_BESTM_CQI_RESULT,
	LPHY_SG_CQI_RPT_SCELL_R1_BP_BEST_SB_CQI_RESULT,
	LPHY_SG_CQI_RPT_SCELL_R2_BP_BEST_SB_CQI_RESULT,
	LPHY_SG_CQI_RPT_SCELL_CSI_PARA, 	/*和CSI相关的deltaOffset,PA和PC*/
	LPHY_SG_CQI_RPT_SCELL_CQI_RPT_INFO,
	LPHY_SG_CQI_RPT_SCELL_STAT,				 /*上报CQI/PMI/RI计数*/

	LPHY_SG_CQI_RPT_PCELL_APERIODIC_R1_ESNR,      /*主载波ESNR的结果*/
	LPHY_SG_CQI_RPT_PCELL_APERIODIC_R2_ESNR,      /*主载波ESNR的结果*/
	LPHY_SG_CQI_RPT_PCELL_APERIODIC_R1_EFFI,		/*主载波EFFI的结果*/
	LPHY_SG_CQI_RPT_PCELL_APERIODIC_R2_EFFI,		/*主载波EFFI的结果*/
	LPHY_SG_CQI_RPT_PCELL_APERIODIC_RI_RESULT,		 /*上报主载波RI的结果*/
	LPHY_SG_CQI_RPT_PCELL_APERIODIC_R1_WCQI_RESULT,	 /*上报主载波宽带CQI的结果*/
	LPHY_SG_CQI_RPT_PCELL_APERIODIC_R2_WCQI_RESULT,	 /*上报主载波宽带CQI的结果*/
	LPHY_SG_CQI_RPT_PCELL_APERIODIC_R1_SCQI_RESULT,	 /*上报主载波子带CQI的结果*/
	LPHY_SG_CQI_RPT_PCELL_APERIODIC_R2_SCQI_RESULT,	 /*上报主载波子带CQI的结果*/
	LPHY_SG_CQI_RPT_PCELL_APERIODIC_R1_WPMI_RESULT,	 /*上报主载波宽带PMI的结果*/
	LPHY_SG_CQI_RPT_PCELL_APERIODIC_R2_WPMI_RESULT,	 /*上报主载波宽带PMI的结果*/
	LPHY_SG_CQI_RPT_PCELL_APERIODIC_R1_SPMI_RESULT,	 /*上报主载波子带PMI的结果*/
	LPHY_SG_CQI_RPT_PCELL_APERIODIC_R2_SPMI_RESULT,	 /*上报主载波子带PMI的结果*/
	LPHY_SG_CQI_RPT_PCELL_APERIODIC_R1_BESTM_PMI_RESULT,
	LPHY_SG_CQI_RPT_PCELL_APERIODIC_R2_BESTM_PMI_RESULT,
	LPHY_SG_CQI_RPT_PCELL_APERIODIC_R1_BESTM_CQI_RESULT,
	LPHY_SG_CQI_RPT_PCELL_APERIODIC_R2_BESTM_CQI_RESULT,
	LPHY_SG_CQI_RPT_PCELL_APERIODIC_R1_BP_BEST_SB_CQI_RESULT,
	LPHY_SG_CQI_RPT_PCELL_APERIODIC_R2_BP_BEST_SB_CQI_RESULT,
	LPHY_SG_CQI_RPT_PCELL_APERIODIC_CSI_PARA, 	/*和CSI相关的deltaOffset,PA和PC*/
	LPHY_SG_CQI_RPT_PCELL_APERIODIC_CQI_RPT_INFO,
	LPHY_SG_CQI_RPT_PCELL_APERIODIC_STAT,				 /*上报CQI/PMI/RI计数*/

	LPHY_SG_CQI_RPT_SCELL_APERIODIC_R1_ESNR,      /*主载波ESNR的结果*/
	LPHY_SG_CQI_RPT_SCELL_APERIODIC_R2_ESNR,      /*主载波ESNR的结果*/
	LPHY_SG_CQI_RPT_SCELL_APERIODIC_R1_EFFI,		/*主载波EFFI的结果*/
	LPHY_SG_CQI_RPT_SCELL_APERIODIC_R2_EFFI,		/*主载波EFFI的结果*/
	LPHY_SG_CQI_RPT_SCELL_APERIODIC_RI_RESULT,		 /*上报主载波RI的结果*/
	LPHY_SG_CQI_RPT_SCELL_APERIODIC_R1_WCQI_RESULT,	 /*上报主载波宽带CQI的结果*/
	LPHY_SG_CQI_RPT_SCELL_APERIODIC_R2_WCQI_RESULT,	 /*上报主载波宽带CQI的结果*/
	LPHY_SG_CQI_RPT_SCELL_APERIODIC_R1_SCQI_RESULT,	 /*上报主载波子带CQI的结果*/
	LPHY_SG_CQI_RPT_SCELL_APERIODIC_R2_SCQI_RESULT,	 /*上报主载波子带CQI的结果*/
	LPHY_SG_CQI_RPT_SCELL_APERIODIC_R1_WPMI_RESULT,	 /*上报主载波宽带PMI的结果*/
	LPHY_SG_CQI_RPT_SCELL_APERIODIC_R2_WPMI_RESULT,	 /*上报主载波宽带PMI的结果*/
	LPHY_SG_CQI_RPT_SCELL_APERIODIC_R1_SPMI_RESULT,	 /*上报主载波子带PMI的结果*/
	LPHY_SG_CQI_RPT_SCELL_APERIODIC_R2_SPMI_RESULT,	 /*上报主载波子带PMI的结果*/
	LPHY_SG_CQI_RPT_SCELL_APERIODIC_R1_BESTM_PMI_RESULT,
	LPHY_SG_CQI_RPT_SCELL_APERIODIC_R2_BESTM_PMI_RESULT,
	LPHY_SG_CQI_RPT_SCELL_APERIODIC_R1_BESTM_CQI_RESULT,
	LPHY_SG_CQI_RPT_SCELL_APERIODIC_R2_BESTM_CQI_RESULT,
	LPHY_SG_CQI_RPT_SCELL_APERIODIC_R1_BP_BEST_SB_CQI_RESULT,
	LPHY_SG_CQI_RPT_SCELL_APERIODIC_R2_BP_BEST_SB_CQI_RESULT,
	LPHY_SG_CQI_RPT_SCELL_APERIODIC_CSI_PARA, 	/*和CSI相关的deltaOffset,PA和PC*/
	LPHY_SG_CQI_RPT_SCELL_APERIODIC_CQI_RPT_INFO,
	LPHY_SG_CQI_RPT_SCELL_APERIODIC_STAT,				 /*上报CQI/PMI/RI计数*/

}LPHY_SG_MSGID_CQI_ENUM;

typedef struct __LPHY_SG_CQI_RPT_R1_ESNR_STRU__
{
	INT16      Reserved;
    INT16      sR1Esnr;                   /*本次计算获取的Esnr结果*/
}LPHY_SG_CQI_RPT_R1_ESNR_STRU;

typedef struct __LPHY_SG_CQI_RPT_R2_ESNR_STRU__
{
	INT16      sR2Esnr[2];                /*本次计算获取的Esnr结果*/
}LPHY_SG_CQI_RPT_R2_ESNR_STRU;

typedef struct __LPHY_SG_CQI_RPT_R1_WCQI_RESULT_STRU__
{
	UINT8      Reserved[3];
	UINT8      ucR1WbCqi;              /*码字0和码字1的宽带CQI*/
	UINT32     auCqiRpt[8];            /*上报给上行的比特流*/
	UINT16     usSysFrmNum;            /*上报时刻系统帧号*/
	UINT16     usSubFrmNum;            /*上报时刻子帧号*/
}LPHY_SG_CQI_RPT_R1_WCQI_RESULT_STRU;

typedef struct __LPHY_SG_CQI_RPT_R2_WCQI_RESULT_STRU__
{
	UINT16     Reserved;
	UINT8      ucR2WbCqi[2];           /*码字0和码字1的宽带CQI*/
	UINT32     auCqiRpt[8];            /*上报给上行的比特流*/
	UINT16     usSysFrmNum;            /*上报时刻系统帧号*/
	UINT16     usSubFrmNum;            /*上报时刻子帧号*/
}LPHY_SG_CQI_RPT_R2_WCQI_RESULT_STRU;

typedef struct __LPHY_SG_CQI_RPT_R1_SCQI_RESULT_STRU__
{
	UINT8       Reserved[3];
	UINT8       ucR1SbCqi[13];          /*码字0和码字1的子带CQI, bestM在对应位置*/
	UINT32      auCqiRpt[8];            /*上报给上行的比特流*/
	UINT16      usSysFrmNum;            /*上报时刻系统帧号*/
	UINT16      usSubFrmNum;            /*上报时刻子帧号*/
}LPHY_SG_CQI_RPT_R1_SCQI_RESULT_STRU;

typedef struct __LPHY_SG_CQI_RPT_R2_SCQI_RESULT_STRU__
{
	UINT8       Reserved[2];
	UINT8       ucR2SbCqi[2][13];       /*码字0和码字1的子带CQI, bestM在对应位置*/
	UINT32      auCqiRpt[8];            /*上报给上行的比特流*/
	UINT16      usSysFrmNum;            /*上报时刻系统帧号*/
	UINT16      usSubFrmNum;            /*上报时刻子帧号*/
}LPHY_SG_CQI_RPT_R2_SCQI_RESULT_STRU;

typedef struct __LPHY_SG_CQI_RPT_R1_WPMI_RESULT_STRU__
{
	UINT8       Reserved[3];
	UINT8       ucR1WbPmi;              /*码字0和码字1的宽带PMI*/
	UINT16      usSysFrmNum;            /*上报时刻系统帧号*/
	UINT16      usSubFrmNum;            /*上报时刻子帧号*/
}LPHY_SG_CQI_RPT_R1_WPMI_RESULT_STRU;

typedef struct __LPHY_SG_CQI_RPT_R2_WPMI_RESULT_STRU__
{
	UINT8       Reserved[3];
	UINT8       ucR2WbPmi;              /*码字0和码字1的宽带PMI*/
	UINT16      usSysFrmNum;            /*上报时刻系统帧号*/
	UINT16      usSubFrmNum;            /*上报时刻子帧号*/
}LPHY_SG_CQI_RPT_R2_WPMI_RESULT_STRU;

typedef struct __LPHY_SG_CQI_RPT_R1_SPMI_RESULT_STRU__
{
	UINT8       Reserved[3];
	UINT8       ucR1SbPmi[13];          /*码字0和码字1的子带PMI*/
	UINT16      usSysFrmNum;            /*上报时刻系统帧号*/
	UINT16      usSubFrmNum;            /*上报时刻子帧号*/
}LPHY_SG_CQI_RPT_R1_SPMI_RESULT_STRU;

typedef struct __LPHY_SG_CQI_RPT_R2_SPMI_RESULT_STRU__
{
	UINT8       Reserved[3];
	UINT8       ucR2SbPmi[13];          /*码字0和码字1的子带PMI*/
	UINT16      usSysFrmNum;            /*上报时刻系统帧号*/
	UINT16      usSubFrmNum;            /*上报时刻子帧号*/
}LPHY_SG_CQI_RPT_R2_SPMI_RESULT_STRU;

typedef struct __LPHY_SG_CQI_RPT_R1_BESTM_PMI_RESULT_STRU__
{
	UINT8       Reserved[3];
	UINT8       ucR1BestMPmi;              /*码字0和码字1的宽带PMI*/
}LPHY_SG_CQI_RPT_R1_BESTM_PMI_RESULT_STRU;

typedef struct __LPHY_SG_CQI_RPT_R2_BESTM_PMI_RESULT_STRU__
{
	UINT8       Reserved[3];
	UINT8       ucR2BestMPmi;              /*码字0和码字1的宽带PMI*/
}LPHY_SG_CQI_RPT_R2_BESTM_PMI_RESULT_STRU;

typedef struct __LPHY_SG_CQI_RPT_R1_BESTM_CQI_RESULT_STRU__
{
	UINT8       Reserved[3];
	UINT8       ucR1BestMCqi;              /*码字0和码字1的宽带PMI*/
}LPHY_SG_CQI_RPT_R1_BESTM_CQI_RESULT_STRU;

typedef struct __LPHY_SG_CQI_RPT_R2_BESTM_CQI_RESULT_STRU__
{
	UINT8       Reserved[2];
	UINT8       ucR2BestMCqi[2];              /*码字0和码字1的宽带PMI*/
}LPHY_SG_CQI_RPT_R2_BESTM_CQI_RESULT_STRU;

typedef struct __LPHY_SG_CQI_RPT_R1_BP_BEST_SB_CQI_RESULT_STRU__
{
	UINT8         Reserved[2];
	UINT8         ucBpBestSbId;
    UINT8         ucBpBestSbCqiR1;
}LPHY_SG_CQI_RPT_R1_BP_BEST_SB_CQI_RESULT_STRU;

typedef struct __LPHY_SG_CQI_RPT_R2_BP_BEST_SB_CQI_RESULT_STRU__
{
	UINT8         Reserved;
	UINT8         ucBpBestSbId;
    UINT8         ucBpBestSbCqiR2[2];
}LPHY_SG_CQI_RPT_R2_BP_BEST_SB_CQI_RESULT_STRU;

typedef struct __LPHY_SG_CQI_RPT_RI_RESULT_STRU__
{
	UINT16      Reserved;
	UINT16      usRI;                   /*本次计算获取的RI结果*/
	UINT16      usSysFrmNum;            /*上报时刻系统帧号*/
	UINT16      usSubFrmNum;            /*上报时刻子帧号*/
}LPHY_SG_CQI_RPT_RI_RESULT_STRU;

typedef struct __LPHY_SG_CQI_RPT_CSI_PARA_STRU__
{
	UINT8		ucPdschPAdB;         /*PA*/
	UINT8		ucPc;                /*PC*/
	INT16		sPdschRsEpreOffset;  /*DeltaOffset*/
}LPHY_SG_CQI_RPT_CSI_PARA_STRU;

typedef struct __LPHY_SG_CQI_RPT_RI_CNT_STRU__
{
	UINT16      usRsv;
    UINT16      usRI[3];            /*RI分别位0，1，2的计数*/
}LPHY_SG_CQI_RPT_RI_CNT_STRU;

typedef struct __LPHY_SG_CQI_RPT_WCQI_CNT_STRU__
{
	UINT16      usRsv;
    UINT16      usR2WbCqiCw0[16];       /*码字0的16个宽带的统计量计数*/
    UINT16      usR2WbCqiCw1[16];       /*码字0的16个宽带的统计量计数*/
    UINT16      usR2WbPmi[16];          /*码字0的16个宽带的统计量计数*/
    UINT16      usR2WbCqiMid[2];        /*码字0的宽带CQI中位数*/
    UINT16      usR1WbCqi[16];          /*码字0的16个宽带的统计量计数*/
    UINT16      usR1WbPmi[16];          /*码字0的16个宽带的统计量计数*/
    UINT16      usR1WbCqiMid;           /*码字1的宽带CQI中位数*/
	UINT32      ulR1WbCqiOutSide;       /*OutSide中值实测*/
	UINT32      ulR2WbCqiOutSide[2];    /*OutSide中值实测*/
}LPHY_SG_CQI_RPT_WCQI_CNT_STRU;

typedef struct __LPHY_SG_CQI_RPT_SCQI_CNT_STRU__
{
    UINT16      usR2Cw0SbCqi[13][16];   /*码字0的13个子带每个CQI的统计量计数*/
    UINT16      usR2Cw1SbCqi[13][16];   /*码字1的13个子带每个CQI的统计量计数*/
    UINT16      usR2SbPmi[13][16];      /*码字0的13个子带每个CQI的统计量计数*/
    UINT16      usR1SbCqi[13][16];      /*码字0的13个子带每个CQI的统计量计数*/
    UINT16      usR1SbPmi[13][16];      /*码字0的13个子带每个PMI的统计量计数*/
}LPHY_SG_CQI_RPT_SCQI_CNT_STRU;

/*可维可测统计量结构体*/
typedef struct __LPHY_SG_CQI_OM_STAT_STRU__
{
    UINT32                            ulSubFrmCnt;          /*子帧计数*/
    LPHY_SG_CQI_RPT_RI_CNT_STRU       stRiCnt;         /*10秒内RI上报计数统计量*/
    LPHY_SG_CQI_RPT_WCQI_CNT_STRU     stWCqiCnt;       /*10秒内宽带CQI计数*/ 
    LPHY_SG_CQI_RPT_SCQI_CNT_STRU     stSCqiCnt;       /*10秒内子带CQI计数*/
}LPHY_SG_CQI_OM_STAT_STRU;

typedef struct __LPHY_SG_CQI_RPT_R1_EFFI_STRU__
{
	UINT16      Reserved;
    UINT16      usR1Effi;                   /*本次计算获取的Effi结果*/
}LPHY_SG_CQI_RPT_R1_EFFI_STRU;

typedef struct __LPHY_SG_CQI_RPT_R2_EFFI_STRU__
{
	UINT16      Reserved;
	UINT16      usR2Effi[3];                /*本次计算获取的Effi结果*/
}LPHY_SG_CQI_RPT_R2_EFFI_STRU;

typedef struct __OM_STAT_SUB_FRM_CNT_STRU__
{
    UINT32      ulSubFrmCnt;     /*子帧计数*/
}OM_STAT_SUB_FRM_CNT_STRU;

typedef struct __LPHY_SG_CQI_RPT_CQI_RPT_INFO_STRU__
{
	UINT8         				Reserved;
    CQI_TYPE_ENUM_UINT8         ucCqiRptMode;  //0~8:A12/A20/A22/A30/A31/P10/P11/P20/P21
    UINT16        				usCqiPeri_Ri;   //周期cqi的ri上报周期
    UINT16        				usCqiPeri_Wb;   //周期cqi的宽带上报周期
    UINT16        				usCqiPeri_Sb;   //周期cqi的子带上报周期
}LPHY_SG_CQI_RPT_CQI_RPT_INFO_STRU;

/************************************************************
                           6. Error数据结构定义
************************************************************/
typedef enum __LPHY_ERROR_CQI__
{
    LPHY_ERROR_CQI_RESERVED         =  OM_CMD_ID(LPHY_CQI_MID, OM_TYPE_ERROR, 0x0),
    LPHY_ERROR_CQI_STAT    
}LPHY_ERROR_CQI_ENUM;

typedef enum __LPHY_ERROR_CQI_STAT_ENUM__
{
    LPHY_ERROR_CQI_STAT_NOT_FINISHED = 0x1,
    LPHY_ERROR_CQI_RESET_HWFSM = 0x2,
}LPHY_ERROR_CQI_STAT_ENUM_UINT16;

typedef struct __LPHY_ERROR_CQI_STAT_STRU__
{
    LPHY_ERROR_CQI_STAT_ENUM_UINT16   enErrNo;
}LPHY_ERROR_CQI_STAT_STRU;


/************************************************************
                           7. DT路测数据结构定义
************************************************************/
	typedef enum __LPHY_DT_MSGID_CQI__
	{
		LPHY_DT_CQI_RESERVED			= OM_CMD_ID(LPHY_CQI_MID, OM_TYPE_DT, 0x0),
	
		LPHY_DT_CQI_RPT_PCELL_PERIODIC_CS0_R1_ESNR, 	                   /*主载波ESNR的结果*/
		LPHY_DT_CQI_RPT_PCELL_PERIODIC_CS0_R2_ESNR, 	                   /*主载波ESNR的结果*/
		LPHY_DT_CQI_RPT_PCELL_PERIODIC_CS0_R1_EFFI, 	                   /*主载波EFFI的结果*/
		LPHY_DT_CQI_RPT_PCELL_PERIODIC_CS0_R2_EFFI, 	                   /*主载波EFFI的结果*/
		LPHY_DT_CQI_RPT_PCELL_PERIODIC_CS0_RI_RESULT,		               /*上报主载波RI的结果*/
		LPHY_DT_CQI_RPT_PCELL_PERIODIC_CS0_R1_WCQI_RESULT,	               /*上报主载波宽带CQI的结果*/
		LPHY_DT_CQI_RPT_PCELL_PERIODIC_CS0_R2_WCQI_RESULT,	               /*上报主载波宽带CQI的结果*/
		LPHY_DT_CQI_RPT_PCELL_PERIODIC_CS0_R1_SCQI_RESULT,	               /*上报主载波子带CQI的结果*/
		LPHY_DT_CQI_RPT_PCELL_PERIODIC_CS0_R2_SCQI_RESULT,	               /*上报主载波子带CQI的结果*/
		LPHY_DT_CQI_RPT_PCELL_PERIODIC_CS0_R1_WPMI_RESULT,	               /*上报主载波宽带PMI的结果*/
		LPHY_DT_CQI_RPT_PCELL_PERIODIC_CS0_R2_WPMI_RESULT,	               /*上报主载波宽带PMI的结果*/
		LPHY_DT_CQI_RPT_PCELL_PERIODIC_CS0_R1_SPMI_RESULT,	               /*上报主载波子带PMI的结果*/
		LPHY_DT_CQI_RPT_PCELL_PERIODIC_CS0_R2_SPMI_RESULT,	               /*上报主载波子带PMI的结果*/
		LPHY_DT_CQI_RPT_PCELL_PERIODIC_CS0_R1_BESTM_PMI_RESULT, 
		LPHY_DT_CQI_RPT_PCELL_PERIODIC_CS0_R2_BESTM_PMI_RESULT,
		LPHY_DT_CQI_RPT_PCELL_PERIODIC_CS0_R1_BESTM_CQI_RESULT,
		LPHY_DT_CQI_RPT_PCELL_PERIODIC_CS0_R2_BESTM_CQI_RESULT,
		LPHY_DT_CQI_RPT_PCELL_PERIODIC_CS0_R1_BP_BEST_SB_CQI_RESULT,
		LPHY_DT_CQI_RPT_PCELL_PERIODIC_CS0_R2_BP_BEST_SB_CQI_RESULT,
		LPHY_DT_CQI_RPT_PCELL_PERIODIC_CS0_CSI_PARA,	                   /*和CSI相关的deltaOffset,PA和PC*/
		LPHY_DT_CQI_RPT_PCELL_PERIODIC_CS0_CQI_RPT_INFO,
		LPHY_DT_CQI_RPT_PCELL_PERIODIC_CS0_STAT,				           /*上报CQI/PMI/RI计数*/
	
		LPHY_DT_CQI_RPT_PCELL_PERIODIC_CS1_R1_ESNR, 	 /*主载波ESNR的结果*/
		LPHY_DT_CQI_RPT_PCELL_PERIODIC_CS1_R2_ESNR, 	 /*主载波ESNR的结果*/
		LPHY_DT_CQI_RPT_PCELL_PERIODIC_CS1_R1_EFFI, 	/*主载波EFFI的结果*/
		LPHY_DT_CQI_RPT_PCELL_PERIODIC_CS1_R2_EFFI, 	/*主载波EFFI的结果*/
		LPHY_DT_CQI_RPT_PCELL_PERIODIC_CS1_RI_RESULT,		 /*上报主载波RI的结果*/
		LPHY_DT_CQI_RPT_PCELL_PERIODIC_CS1_R1_WCQI_RESULT,	 /*上报主载波宽带CQI的结果*/
		LPHY_DT_CQI_RPT_PCELL_PERIODIC_CS1_R2_WCQI_RESULT,	 /*上报主载波宽带CQI的结果*/
		LPHY_DT_CQI_RPT_PCELL_PERIODIC_CS1_R1_SCQI_RESULT,	 /*上报主载波子带CQI的结果*/
		LPHY_DT_CQI_RPT_PCELL_PERIODIC_CS1_R2_SCQI_RESULT,	 /*上报主载波子带CQI的结果*/
		LPHY_DT_CQI_RPT_PCELL_PERIODIC_CS1_R1_WPMI_RESULT,	 /*上报主载波宽带PMI的结果*/
		LPHY_DT_CQI_RPT_PCELL_PERIODIC_CS1_R2_WPMI_RESULT,	 /*上报主载波宽带PMI的结果*/
		LPHY_DT_CQI_RPT_PCELL_PERIODIC_CS1_R1_SPMI_RESULT,	 /*上报主载波子带PMI的结果*/
		LPHY_DT_CQI_RPT_PCELL_PERIODIC_CS1_R2_SPMI_RESULT,	 /*上报主载波子带PMI的结果*/
		LPHY_DT_CQI_RPT_PCELL_PERIODIC_CS1_R1_BESTM_PMI_RESULT, 
		LPHY_DT_CQI_RPT_PCELL_PERIODIC_CS1_R2_BESTM_PMI_RESULT,
		LPHY_DT_CQI_RPT_PCELL_PERIODIC_CS1_R1_BESTM_CQI_RESULT,
		LPHY_DT_CQI_RPT_PCELL_PERIODIC_CS1_R2_BESTM_CQI_RESULT,
		LPHY_DT_CQI_RPT_PCELL_PERIODIC_CS1_R1_BP_BEST_SB_CQI_RESULT,
		LPHY_DT_CQI_RPT_PCELL_PERIODIC_CS1_R2_BP_BEST_SB_CQI_RESULT,
		LPHY_DT_CQI_RPT_PCELL_PERIODIC_CS1_CSI_PARA,	/*和CSI相关的deltaOffset,PA和PC*/
		LPHY_DT_CQI_RPT_PCELL_PERIODIC_CS1_CQI_RPT_INFO,
		LPHY_DT_CQI_RPT_PCELL_PERIODIC_CS1_STAT,				 /*上报CQI/PMI/RI计数*/
		
		LPHY_DT_CQI_RPT_SCELL_R1_ESNR,		/*副载波ESNR的结果*/
		LPHY_DT_CQI_RPT_SCELL_R2_ESNR,		/*副载波ESNR的结果*/
		LPHY_DT_CQI_RPT_SCELL_R1_EFFI,		/*副载波EFFI的结果*/
		LPHY_DT_CQI_RPT_SCELL_R2_EFFI,		/*副载波EFFI的结果*/
		LPHY_DT_CQI_RPT_SCELL_RI_RESULT,		 /*上报副载波RI的结果*/
		LPHY_DT_CQI_RPT_SCELL_R1_WCQI_RESULT,	 /*上报副载波宽带CQI的结果*/
		LPHY_DT_CQI_RPT_SCELL_R2_WCQI_RESULT,	 /*上报副载波宽带CQI的结果*/
		LPHY_DT_CQI_RPT_SCELL_R1_SCQI_RESULT,	 /*上报副载波子带CQI的结果*/
		LPHY_DT_CQI_RPT_SCELL_R2_SCQI_RESULT,	 /*上报副载波子带CQI的结果*/
		LPHY_DT_CQI_RPT_SCELL_R1_WPMI_RESULT,	 /*上报副载波宽带PMI的结果*/
		LPHY_DT_CQI_RPT_SCELL_R2_WPMI_RESULT,	 /*上报副载波宽带PMI的结果*/
		LPHY_DT_CQI_RPT_SCELL_R1_SPMI_RESULT,	 /*上报副载波子带PMI的结果*/
		LPHY_DT_CQI_RPT_SCELL_R2_SPMI_RESULT,	 /*上报副载波子带PMI的结果*/
		LPHY_DT_CQI_RPT_SCELL_R1_BESTM_PMI_RESULT,
		LPHY_DT_CQI_RPT_SCELL_R2_BESTM_PMI_RESULT,
		LPHY_DT_CQI_RPT_SCELL_R1_BESTM_CQI_RESULT,
		LPHY_DT_CQI_RPT_SCELL_R2_BESTM_CQI_RESULT,
		LPHY_DT_CQI_RPT_SCELL_R1_BP_BEST_SB_CQI_RESULT,
		LPHY_DT_CQI_RPT_SCELL_R2_BP_BEST_SB_CQI_RESULT,
		LPHY_DT_CQI_RPT_SCELL_CSI_PARA, 	/*和CSI相关的deltaOffset,PA和PC*/
		LPHY_DT_CQI_RPT_SCELL_CQI_RPT_INFO,
		LPHY_DT_CQI_RPT_SCELL_STAT, 			 /*上报CQI/PMI/RI计数*/
	
		LPHY_DT_CQI_RPT_PCELL_APERIODIC_R1_ESNR,	  /*主载波ESNR的结果*/
		LPHY_DT_CQI_RPT_PCELL_APERIODIC_R2_ESNR,	  /*主载波ESNR的结果*/
		LPHY_DT_CQI_RPT_PCELL_APERIODIC_R1_EFFI,		/*主载波EFFI的结果*/
		LPHY_DT_CQI_RPT_PCELL_APERIODIC_R2_EFFI,		/*主载波EFFI的结果*/
		LPHY_DT_CQI_RPT_PCELL_APERIODIC_RI_RESULT,		 /*上报主载波RI的结果*/
		LPHY_DT_CQI_RPT_PCELL_APERIODIC_R1_WCQI_RESULT,  /*上报主载波宽带CQI的结果*/
		LPHY_DT_CQI_RPT_PCELL_APERIODIC_R2_WCQI_RESULT,  /*上报主载波宽带CQI的结果*/
		LPHY_DT_CQI_RPT_PCELL_APERIODIC_R1_SCQI_RESULT,  /*上报主载波子带CQI的结果*/
		LPHY_DT_CQI_RPT_PCELL_APERIODIC_R2_SCQI_RESULT,  /*上报主载波子带CQI的结果*/
		LPHY_DT_CQI_RPT_PCELL_APERIODIC_R1_WPMI_RESULT,  /*上报主载波宽带PMI的结果*/
		LPHY_DT_CQI_RPT_PCELL_APERIODIC_R2_WPMI_RESULT,  /*上报主载波宽带PMI的结果*/
		LPHY_DT_CQI_RPT_PCELL_APERIODIC_R1_SPMI_RESULT,  /*上报主载波子带PMI的结果*/
		LPHY_DT_CQI_RPT_PCELL_APERIODIC_R2_SPMI_RESULT,  /*上报主载波子带PMI的结果*/
		LPHY_DT_CQI_RPT_PCELL_APERIODIC_R1_BESTM_PMI_RESULT,
		LPHY_DT_CQI_RPT_PCELL_APERIODIC_R2_BESTM_PMI_RESULT,
		LPHY_DT_CQI_RPT_PCELL_APERIODIC_R1_BESTM_CQI_RESULT,
		LPHY_DT_CQI_RPT_PCELL_APERIODIC_R2_BESTM_CQI_RESULT,
		LPHY_DT_CQI_RPT_PCELL_APERIODIC_R1_BP_BEST_SB_CQI_RESULT,
		LPHY_DT_CQI_RPT_PCELL_APERIODIC_R2_BP_BEST_SB_CQI_RESULT,
		LPHY_DT_CQI_RPT_PCELL_APERIODIC_CSI_PARA,	/*和CSI相关的deltaOffset,PA和PC*/
		LPHY_DT_CQI_RPT_PCELL_APERIODIC_CQI_RPT_INFO,
		LPHY_DT_CQI_RPT_PCELL_APERIODIC_STAT,				 /*上报CQI/PMI/RI计数*/
	
		LPHY_DT_CQI_RPT_SCELL_APERIODIC_R1_ESNR,	  /*主载波ESNR的结果*/
		LPHY_DT_CQI_RPT_SCELL_APERIODIC_R2_ESNR,	  /*主载波ESNR的结果*/
		LPHY_DT_CQI_RPT_SCELL_APERIODIC_R1_EFFI,		/*主载波EFFI的结果*/
		LPHY_DT_CQI_RPT_SCELL_APERIODIC_R2_EFFI,		/*主载波EFFI的结果*/
		LPHY_DT_CQI_RPT_SCELL_APERIODIC_RI_RESULT,		 /*上报主载波RI的结果*/
		LPHY_DT_CQI_RPT_SCELL_APERIODIC_R1_WCQI_RESULT,  /*上报主载波宽带CQI的结果*/
		LPHY_DT_CQI_RPT_SCELL_APERIODIC_R2_WCQI_RESULT,  /*上报主载波宽带CQI的结果*/
		LPHY_DT_CQI_RPT_SCELL_APERIODIC_R1_SCQI_RESULT,  /*上报主载波子带CQI的结果*/
		LPHY_DT_CQI_RPT_SCELL_APERIODIC_R2_SCQI_RESULT,  /*上报主载波子带CQI的结果*/
		LPHY_DT_CQI_RPT_SCELL_APERIODIC_R1_WPMI_RESULT,  /*上报主载波宽带PMI的结果*/
		LPHY_DT_CQI_RPT_SCELL_APERIODIC_R2_WPMI_RESULT,  /*上报主载波宽带PMI的结果*/
		LPHY_DT_CQI_RPT_SCELL_APERIODIC_R1_SPMI_RESULT,  /*上报主载波子带PMI的结果*/
		LPHY_DT_CQI_RPT_SCELL_APERIODIC_R2_SPMI_RESULT,  /*上报主载波子带PMI的结果*/
		LPHY_DT_CQI_RPT_SCELL_APERIODIC_R1_BESTM_PMI_RESULT,
		LPHY_DT_CQI_RPT_SCELL_APERIODIC_R2_BESTM_PMI_RESULT,
		LPHY_DT_CQI_RPT_SCELL_APERIODIC_R1_BESTM_CQI_RESULT,
		LPHY_DT_CQI_RPT_SCELL_APERIODIC_R2_BESTM_CQI_RESULT,
		LPHY_DT_CQI_RPT_SCELL_APERIODIC_R1_BP_BEST_SB_CQI_RESULT,
		LPHY_DT_CQI_RPT_SCELL_APERIODIC_R2_BP_BEST_SB_CQI_RESULT,
		LPHY_DT_CQI_RPT_SCELL_APERIODIC_CSI_PARA,	/*和CSI相关的deltaOffset,PA和PC*/
		LPHY_DT_CQI_RPT_SCELL_APERIODIC_CQI_RPT_INFO,
		LPHY_DT_CQI_RPT_SCELL_APERIODIC_STAT,				 /*上报CQI/PMI/RI计数*/
	
	}LPHY_DT_MSGID_CQI_ENUM;


/*typedef enum __LPHY_DT_CQI_REQ_
{
    LPHY_DT_CQI_INFO_REQ         = OM_CMD_ID(LPHY_CQI_MID, OM_TYPE_DT, 0x1),

}LPHY_DT_CQI_REQ_ENUM;*/

typedef struct __LPHY_DT_CQI_INFO_REQ_STRU__
{
    OM_REQ_ENABLE_ENUM_UINT16   enEn;
    UINT16  usRsv;
} LPHY_DT_CQI_INFO_REQ_STRU;



#if 0
typedef enum __LPHY_DT_CORR_REQ_
{
    LPHY_DT_CORR_INFO_REQ         = OM_CMD_ID(LPHY_CORR_MID, OM_TYPE_DT, 0x1),

}LPHY_DT_CORR_REQ_ENUM;

typedef enum __LPHY_DT_CORR_IND_
{
    LPHY_DT_CORR_INFO_IND         = OM_CMD_ID(LPHY_CORR_MID, OM_TYPE_DT, 0x0011),

}LPHY_DT_CORR_IND_ENUM;

typedef struct
{
    OM_REQ_ENABLE_ENUM_UINT16   enEn;
    UINT16          usPeriod;
} LPHY_DT_CORR_INFO_REQ_STRU;

typedef struct __LPHY_DT_CORR_INFO_IND_STRU__
{
    UINT16 usSFN;
    UINT8  ucSubFn;
    LTE_CHAN_SPACE_CORR_ENUM_UINT8 enRecCorr;
} LPHY_DT_CORR_INFO_IND_STRU;
#endif


typedef struct __LPHY_DT_CQI_RPT_CQI_RPT_INFO_STRU__
{
	UINT8         				Reserved;
    CQI_TYPE_ENUM_UINT8         ucCqiRptMode;  //0~8:A12/A20/A22/A30/A31/P10/P11/P20/P21
    UINT16        				usCqiPeri_Ri;   //周期cqi的ri上报周期
    UINT16        				usCqiPeri_Wb;   //周期cqi的宽带上报周期
    UINT16        				usCqiPeri_Sb;   //周期cqi的子带上报周期
    
    UINT16        				usLabelLen;   
    UINT16        				usBpNum;  
    UINT16        				usK;

	UINT16                      usBestMNum;
	UINT32                      ulCombinationrialIndex;  		
}LPHY_DT_CQI_RPT_CQI_RPT_INFO_STRU;



typedef struct __LPHY_DT_CQI_RPT_BESTM_SB_CQI_ESNR_R1_STRU__
{
	UINT8         Reserved;
	UINT8         ucR1BestMCqi;              /*码字0和码字1的宽带PMI*/
    UINT16        ucBestmCqiR1Snr;
}LPHY_DT_CQI_RPT_BESTM_SB_CQI_ESNR_R1_STRU;

typedef struct __LPHY_DT_CQI_RPT_BESTM_SB_CQI_ESNR_R2_STRU__
{
	UINT8         Reserved[2];
	UINT8         ucR2BestMCqi[2];              /*码字0和码字1的宽带PMI*/
    UINT16        ucBestmCqiR2Snr[2];
}LPHY_DT_CQI_RPT_BESTM_SB_CQI_ESNR_R2_STRU;

typedef struct __LPHY_DT_CQI_RPT_BP_BEST_SB_CQI_ESNR_R1_STRU__
{
	UINT8         ucBpBestSbId;
    UINT8         ucBpBestSbCqiR1;
    UINT16        ucBpBestSbCqiR1Snr;
}LPHY_DT_CQI_RPT_BP_BEST_SB_CQI_ESNR_R1_STRU;

typedef struct __LPHY_DT_CQI_RPT_BP_BEST_SB_CQI_ESNR_R2_STRU__
{
	UINT8         Reserved;
	UINT8         ucBpBestSbId;
    UINT8         ucBpBestSbCqiR2[2];
    UINT16        ucBpBestSbCqiR2Snr[2];
}LPHY_DT_CQI_RPT_BP_BEST_SB_CQI_ESNR_R2_STRU;

typedef struct __LPHY_DT_CQI_RPT_SB_CQI_ESNR_R1_STRU__
{
	UINT8       Reserved;
	UINT8       ucR1SbCqi[13];          /*码字0和码字1的子带CQI, bestM在对应位置*/
	INT16		sR1SbCqiSnr[13];
	UINT16      usSysFrmNum;            /*上报时刻系统帧号*/
	UINT16      usSubFrmNum;            /*上报时刻子帧号*/	
}LPHY_DT_CQI_RPT_SB_CQI_ESNR_R1_STRU;

typedef struct __LPHY_DT_CQI_RPT_SB_CQI_ESNR_R2_STRU__
{
	UINT8         Reserved[2];
	UINT8         ucR2SbCqi[2][13];       /*码字0和码字1的子带CQI, bestM在对应位置*/
	INT16		  sR2SbCqiSnr[2][13];
	UINT16        usSysFrmNum;            /*上报时刻系统帧号*/
	UINT16        usSubFrmNum;            /*上报时刻子帧号*/	
}LPHY_DT_CQI_RPT_SB_CQI_ESNR_R2_STRU;

typedef struct __LPHY_DT_CQI_RPT_R2_WCQI_RESULT_STRU__
{
	UINT16     Reserved;
	UINT8      ucR2WbCqi[2];           /*码字0和码字1的宽带CQI*/
	UINT16     usSysFrmNum;            /*上报时刻系统帧号*/
	UINT16     usSubFrmNum;            /*上报时刻子帧号*/
}LPHY_DT_CQI_RPT_R2_WCQI_RESULT_STRU;

typedef struct __LPHY_DT_CQI_RPT_R1_WCQI_RESULT_STRU__
{
	UINT16     Reserved;
	UINT8      ucR1WbCqi;           /*宽带CQI*/
	UINT16     usSysFrmNum;            /*上报时刻系统帧号*/
	UINT16     usSubFrmNum;            /*上报时刻子帧号*/
}LPHY_DT_CQI_RPT_R1_WCQI_RESULT_STRU;



#ifdef __cplusplus
#if __cplusplus
}
#endif
#endif /* __cplusplus */


#endif /* __CQI_OM_DEF_H__ */
