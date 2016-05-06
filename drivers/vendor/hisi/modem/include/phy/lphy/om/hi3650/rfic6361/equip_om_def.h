/******************************************************************************

                  版权所有 (C), 2001-2011, 华为技术有限公司

 ******************************************************************************
  文 件 名   : equip_om_def.h
  版 本 号   : 初稿
  作    者   : zengshangyou
  生成日期   : 2011年11月18日
  最近修改   :
  功能描述   : 定义装备OM需要上报的结构体
  函数列表   :
  修改历史   :
  1.日    期   : 2011年11月18日
    作    者   : z00189258
    修改内容   : 创建文件

******************************************************************************/

/************************************************************
                     包含其它模块的头文件
************************************************************/
#include "om_base_def.h"
/************************************************************
                               宏定义
************************************************************/

/************************************************************
                             数据结构定义
************************************************************/

/************************************************************
                             接口函数声明
 ************************************************************/

#ifndef __EQUIP_OM_DEF_H__
#define __EQUIP_OM_DEF_H__


#ifdef __cplusplus
#if __cplusplus
extern "C"{
#endif
#endif /* __cplusplus */



/************************************************************
                    1. REQ命令和对应的数据结构定义
************************************************************/
typedef enum
{
    LPHY_REQ_EQUIP_BT_REQUEST           = OM_CMD_ID(LPHY_BT_MID, OM_TYPE_REQ, 0x1),
}LPHY_EQUIP_REQ_ENUM;


typedef struct
{
    OM_REQ_ENABLE_ENUM usTxCmpOmSwitch;
    OM_REQ_ENABLE_ENUM usRxCmpOmSwitch;
}LPHY_OM_REQ_EQUIP_STRU;

/************************************************************
                    2. CNF数据结构定义
************************************************************/


/************************************************************
                    3. Ind数据结构定义
************************************************************/
typedef enum
{
    LPHY_IND_EQUIP_BT_CMP_TX_REPORT = OM_CMD_ID(LPHY_BT_MID, OM_TYPE_IND, 0x1),
    LPHY_IND_EQUIP_BT_CMP_RX_REPORT
}LPHY_EQUIP_BT_CMP_ENUM;



typedef struct
{
    UINT16 usCalMaxPwr;      /*根据校准结果计算的最大功率能力*/
    INT16  sPwrCalc;         /*计算功率*/
    UINT16 usPbVal;          /*AMPR和MPR回退值*/
    INT16  sSarMax;          /*降SAR后限定的最大功率*/
    UINT16 usChType;         /*信道类型*/
    INT16  sPowerIn;
    UINT16 usPdmVal;
    INT16  sAptCmp;
    INT16  sPwrAftPd;
    UINT16 usTxFreqCmpNum;   /*查表获得的补偿频点个数*/
    UINT32 ulCentPoint;      /*当前计算的中心频点*/
    INT16  sFreqCmpVal;
    INT16  sTempIndex;
    INT16  sCurMaxPower;
    UINT16 usTempVal;
    UINT16 usPaLevel;        /*PA档位*/
    UINT16 usDbbAttWord;
    UINT16 usAbbAttWord;
    UINT16 usRfCode;         /*RF控制字*/
    INT16  sFilterCmp;
    INT16  sBandWithCmp;
    UINT16 usPdDela;
    UINT16 usRsv2;
}BT_TX_CMP_OM_INFO_STRU;

typedef struct
{
    UINT16 usAgcLevel;
	UINT16 usTempVol;
    UINT16 usFreq;
	UINT16 usBandWidth;

    INT16  sFreqCmpVal0;
    INT16  sTempCmpVal0;
    INT16  sCmpVal0;
    INT16  sPreRsrp0;
    INT16  sPostRsrp0;

    INT16  sFreqCmpVal1;
    INT16  sTempCmpVal1;
    INT16  sCmpVal1;
    INT16  sPreRsrp1;
    INT16  sPostRsrp1;
}BT_RX_CMP_OM_INFO_STRU;

/************************************************************
                    4. TRACE数据结构定义
************************************************************/

/************************************************************
                    5. ERROR数据结构定义
************************************************************/
#ifdef __cplusplus
#if __cplusplus
}
#endif
#endif /* __cplusplus */


#endif 

