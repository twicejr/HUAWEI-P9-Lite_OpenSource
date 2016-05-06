/************************************************************************
  Copyright   : 2005-2007, Huawei Tech. Co., Ltd.
  File name   : GmmCasGsm.h
  Author      : Roger Leo
  Version     : V200R001
  Date        : 2005-11-17
  Description : GmmCasGsm模块的内部头文件
  History     :
  1. Date:2005-11-17
     Author: Roger Leo
     Modification:update
  2.日    期   : 2006年08月09日
    作    者   : 蒋丽萍j60010247
    修改内容   : 问题单A32D03479，在PC机上实现时将#pragma pack(0)和#pragma pack()加编译开关
************************************************************************/

#ifndef _GMM_CAS_GSM_H_
#define _GMM_CAS_GSM_H_

#ifdef __cplusplus
#if __cplusplus
extern "C" {
#endif
#endif

/*****************************************************************************
  1 其他头文件包含
*****************************************************************************/

#pragma pack(4)         /* 1字节对齐，数据结构定义保证4字节对齐 */
                        /* 放在include后，不影响其他头文件的pack参数 */
/*****************************************************************************
  2 宏定义
*****************************************************************************/

/*******************************************************************************
  3 枚举定义
*******************************************************************************/

/*****************************************************************************
  4 全局变量声明
*****************************************************************************/

/*****************************************************************************
  5 消息头定义
*****************************************************************************/

/*****************************************************************************
  6 消息定义
*****************************************************************************/

/*****************************************************************************
  7 STRUCT定义
*****************************************************************************/

/*****************************************************************************
  8 UNION定义
*****************************************************************************/

/*****************************************************************************
  9 OTHERS定义
*****************************************************************************/
VOS_UINT32 GMM_Nop(VOS_VOID *pRcvMsg);
VOS_UINT32 GMM_NopTrue (VOS_VOID *pRcvMsg);
VOS_UINT32 GMM_NopFalse (VOS_VOID *pRcvMsg);
VOS_UINT32 GMM_CasCellS0E16(VOS_VOID *pRcvMsg);
VOS_UINT32 GMM_CasCellS22E16(VOS_VOID *pRcvMsg);
VOS_UINT32 GMM_CasCellS0E17(VOS_VOID *pRcvMsg);
VOS_UINT32 GMM_CasCellS22E17(VOS_VOID *pRcvMsg);
VOS_UINT32 GMM_CasCellS1E18(VOS_VOID *pRcvMsg);
VOS_UINT32 GMM_CasCellS8E18(VOS_VOID *pRcvMsg);
VOS_UINT32 GMM_CasCellS16E18(VOS_VOID *pRcvMsg);
VOS_UINT32 GMM_CasCellS18E18(VOS_VOID *pRcvMsg);
VOS_UINT32 GMM_CasCellS19E18(VOS_VOID *pRcvMsg);
VOS_UINT32 GMM_CasCellS22E18(VOS_VOID *pRcvMsg);
VOS_UINT32 GMM_CasCellS23E18( VOS_VOID *pRcvMsg );
VOS_UINT32 GMM_CasCellS0E19(VOS_VOID *pRcvMsg);
VOS_UINT32 GMM_CasCellS22E19(VOS_VOID *pRcvMsg);
VOS_UINT32 GMM_CasCellS23E19( VOS_VOID *pRcvMsg );
VOS_UINT32 GMM_CasCellS1E20(VOS_VOID *pRcvMsg);
VOS_UINT32 GMM_CasCellS8E20(VOS_VOID *pRcvMsg);
VOS_UINT32 GMM_CasCellS16E20(VOS_VOID *pRcvMsg);
VOS_UINT32 GMM_CasCellS18E20(VOS_VOID *pRcvMsg);
VOS_UINT32 GMM_CasCellS19E20(VOS_VOID *pRcvMsg);
VOS_UINT32 GMM_CasCellS20E20(VOS_VOID *pRcvMsg);
VOS_UINT32 GMM_CasCellS21E20(VOS_VOID *pRcvMsg);
VOS_UINT32 GMM_CasCellS22E20(VOS_VOID *pRcvMsg);
VOS_UINT32 GMM_CasCellS23E20( VOS_VOID *pRcvMsg );
VOS_UINT32 GMM_CasCellS22E21(VOS_VOID *pRcvMsg);
VOS_UINT32 GMM_CasCellS23E21( VOS_VOID *pRcvMsg );
VOS_UINT32 GMM_CasCellS0E22(VOS_VOID *pRcvMsg);
VOS_UINT32 GMM_CasCellS22E22(VOS_VOID *pRcvMsg);
VOS_UINT32 GMM_CasCellS23E22( VOS_VOID *pRcvMsg );
VOS_UINT32 GMM_CasCellS9E23(VOS_VOID *pRcvMsg);
VOS_UINT32 GMM_CasCellS14E23(VOS_VOID *pRcvMsg);
VOS_UINT32 GMM_CasCellS18E23(VOS_VOID *pRcvMsg);
VOS_UINT32 GMM_CasCellS19E23(VOS_VOID *pRcvMsg);
VOS_UINT32 GMM_CasCellS22E23(VOS_VOID *pRcvMsg);
VOS_UINT32 GMM_CasCellS23E23( VOS_VOID *pRcvMsg );
VOS_UINT32 GMM_CasCellS22E24(VOS_VOID *pRcvMsg);
VOS_UINT32 GMM_CasCellS23E24(VOS_VOID *pRcvMsg);
VOS_UINT32 GMM_CasCellS1E25(VOS_VOID *pRcvMsg);
VOS_UINT32 GMM_CasCellS22E25(VOS_VOID *pRcvMsg);
VOS_UINT32 GMM_CasCellS1E26(VOS_VOID *pRcvMsg);
VOS_UINT32 GMM_CasCellS8E26(VOS_VOID *pRcvMsg);
VOS_UINT32 GMM_CasCellS22E26(VOS_VOID *pRcvMsg);
VOS_UINT32 GMM_CasCellS1E28(VOS_VOID *pRcvMsg);
VOS_UINT32 GMM_CasCellS9E28(VOS_VOID *pRcvMsg);
VOS_UINT32 GMM_CasCellS19E28(VOS_VOID *pRcvMsg);
VOS_UINT32 GMM_CasCellS22E28(VOS_VOID *pRcvMsg);
VOS_UINT32 GMM_CasCellS23E28 ( VOS_VOID *pRcvMsg );
VOS_UINT32 GMM_CasCellS19E29(VOS_VOID *pRcvMsg);
VOS_UINT32 GMM_CasCellS22E29(VOS_VOID *pRcvMsg);
VOS_UINT32 GMM_CasCellS23E29 ( VOS_VOID *pRcvMsg );
VOS_UINT32 GMM_CasCellS23E29 ( VOS_VOID *pRcvMsg );
VOS_UINT32 GMM_CasCellS1E30(VOS_VOID *pRcvMsg);
VOS_UINT32 GMM_CasCellS8E30(VOS_VOID *pRcvMsg);
VOS_UINT32 GMM_CasCellS22E30(VOS_VOID *pRcvMsg);
VOS_UINT32 GMM_CasCellS23E30(VOS_VOID *pRcvMsg);
VOS_UINT32 GMM_CasCellS0E31(VOS_VOID *pRcvMsg);
VOS_UINT32 GMM_CasCellS1E32(VOS_VOID *pRcvMsg);
VOS_UINT32 GMM_CasCellS9E32(VOS_VOID *pRcvMsg);
VOS_UINT32 GMM_CasCellS22E32(VOS_VOID *pRcvMsg);
VOS_UINT32 GMM_CasCellS23E32 ( VOS_VOID *pRcvMsg );
VOS_UINT32 GMM_CasCellS1E33(VOS_VOID *pRcvMsg);
VOS_UINT32 GMM_CasCellS5E33(VOS_VOID *pRcvMsg);
VOS_UINT32 GMM_CasCellS8E33(VOS_VOID *pRcvMsg);
VOS_UINT32 GMM_CasCellS9E33(VOS_VOID *pRcvMsg);
VOS_UINT32 GMM_CasCellS15E33(VOS_VOID *pRcvMsg);
VOS_UINT32 GMM_CasCellS20E33(VOS_VOID *pRcvMsg);
VOS_UINT32 GMM_CasCellS22E33(VOS_VOID *pRcvMsg);
VOS_UINT32 GMM_CasCellS23E33 ( VOS_VOID *pRcvMsg );
VOS_UINT32 GMM_CasCellS0E34(VOS_VOID *pRcvMsg);
VOS_UINT32 GMM_CasCellS8E34(VOS_VOID *pRcvMsg);
VOS_UINT32 GMM_CasCellS22E34(VOS_VOID *pRcvMsg);
VOS_UINT32 GMM_CasCellS23E34 ( VOS_VOID *pRcvMsg );
VOS_UINT32 GMM_CasCellS4E35(VOS_VOID *pRcvMsg);
VOS_UINT32 GMM_CasCellS9E35(VOS_VOID *pRcvMsg);
VOS_UINT32 GMM_CasCellS17E35(VOS_VOID *pRcvMsg);
VOS_UINT32 GMM_CasCellS20E35(VOS_VOID *pRcvMsg);
VOS_UINT32 GMM_CasCellS22E35(VOS_VOID *pRcvMsg);
VOS_UINT32 GMM_CasCellS23E35 ( VOS_VOID *pRcvMsg );
VOS_UINT32 GMM_CasCellS1E36(VOS_VOID *pRcvMsg);
VOS_UINT32 GMM_CasCellS1E37(VOS_VOID *pRcvMsg);
VOS_UINT32 GMM_CasCellS2E37(VOS_VOID *pRcvMsg);
VOS_UINT32 GMM_CasCellS4E37(VOS_VOID *pRcvMsg);
VOS_UINT32 GMM_CasCellS8E37(VOS_VOID *pRcvMsg);
VOS_UINT32 GMM_CasCellS9E37(VOS_VOID *pRcvMsg);
VOS_UINT32 GMM_CasCellS11E37(VOS_VOID *pRcvMsg);
VOS_UINT32 GMM_CasCellS13E37(VOS_VOID *pRcvMsg);
VOS_UINT32 GMM_CasCellS14E37(VOS_VOID *pRcvMsg);
VOS_UINT32 GMM_CasCellS19E37(VOS_VOID *pRcvMsg);
VOS_UINT32 GMM_CasCellS20E37(VOS_VOID *pRcvMsg);
VOS_UINT32 GMM_CasCellS22E37(VOS_VOID *pRcvMsg);
VOS_UINT32 GMM_CasCellS23E37 ( VOS_VOID *pRcvMsg );
VOS_UINT32 GMM_CasCellS0E38(VOS_VOID *pRcvMsg);
VOS_UINT32 GMM_CasCellS1E38(VOS_VOID *pRcvMsg);
VOS_UINT32 GMM_CasCellS4E38(VOS_VOID *pRcvMsg);
VOS_UINT32 GMM_CasCellS8E38(VOS_VOID *pRcvMsg);
VOS_UINT32 GMM_CasCellS22E38(VOS_VOID *pRcvMsg);
VOS_UINT32 GMM_CasCellS23E38 ( VOS_VOID *pRcvMsg );
VOS_UINT32 GMM_CasCellS9E39(VOS_VOID *pRcvMsg);
VOS_UINT32 GMM_CasCellS12E39(VOS_VOID *pRcvMsg);
VOS_UINT32 GMM_CasCellS18E39(VOS_VOID *pRcvMsg);
VOS_UINT32 GMM_CasCellS22E39(VOS_VOID *pRcvMsg);
VOS_UINT32 GMM_CasCellS23E39 ( VOS_VOID *pRcvMsg );
VOS_UINT32 GMM_CasCellS1E40(VOS_VOID *pRcvMsg);
VOS_UINT32 GMM_CasCellS22E40(VOS_VOID *pRcvMsg);
VOS_UINT32 GMM_CasCellS23E40 ( VOS_VOID *pRcvMsg );
VOS_UINT32 GMM_CasCellS9E41(VOS_VOID *pRcvMsg);
VOS_UINT32 GMM_CasCellS10E41(VOS_VOID *pRcvMsg);
VOS_UINT32 GMM_CasCellS18E41(VOS_VOID *pRcvMsg);
VOS_UINT32 GMM_CasCellS22E41(VOS_VOID *pRcvMsg);
VOS_UINT32 GMM_CasCellS23E41 ( VOS_VOID *pRcvMsg );
VOS_UINT32 GMM_CasCellS1E42(VOS_VOID *pRcvMsg);
VOS_UINT32 GMM_CasCellS22E42(VOS_VOID *pRcvMsg);
VOS_UINT32 GMM_CasCellS23E42 ( VOS_VOID *pRcvMsg );
VOS_UINT32 GMM_CasCellS1E43(VOS_VOID *pRcvMsg);
VOS_UINT32 GMM_CasCellS22E43(VOS_VOID *pRcvMsg);
VOS_UINT32 GMM_CasCellS23E43 ( VOS_VOID *pRcvMsg );
VOS_UINT32 GMM_CasCellS1E44(VOS_VOID *pRcvMsg);
VOS_UINT32 GMM_CasCellS22E44(VOS_VOID *pRcvMsg);
VOS_UINT32 GMM_CasCellS23E44 ( VOS_VOID *pRcvMsg );
VOS_VOID   GMM_CasCellS0E45(VOS_VOID *pRcvMsg);
VOS_UINT32 GMM_CasCellS22E45(VOS_VOID *pRcvMsg);
VOS_UINT32 GMM_CasCellS23E45 ( VOS_VOID *pRcvMsg );
VOS_UINT32 GMM_CasCellS0E46(VOS_VOID *pRcvMsg);
VOS_UINT32 GMM_CasCellS22E46(VOS_VOID *pRcvMsg);
VOS_UINT32 GMM_CasCellS23E46 ( VOS_VOID *pRcvMsg );
VOS_VOID   NAS_GMM_RcvGmmRabmRoutingAreaUpdateRsp(VOS_VOID *pRcvMsg);
VOS_UINT32 GMM_CasCellS22E47(VOS_VOID *pRcvMsg);
VOS_UINT32 GMM_CasCellS23E47 ( VOS_VOID *pRcvMsg );
VOS_UINT32 GMM_CasCellS9E48(VOS_VOID *pRcvMsg);
VOS_UINT32 GMM_CasCellS18E48(VOS_VOID *pRcvMsg);
VOS_UINT32 GMM_CasCellS19E48(VOS_VOID *pRcvMsg);
VOS_UINT32 GMM_CasCellS22E48(VOS_VOID *pRcvMsg);
VOS_UINT32 GMM_CasCellS23E48 ( VOS_VOID *pRcvMsg );
VOS_VOID   GMM_CasCellS1E49(VOS_VOID *pRcvMsg);
VOS_VOID   GMM_CasCellS4E49(VOS_VOID *pRcvMsg);
VOS_VOID   GMM_CasCellS8E49(VOS_VOID *pRcvMsg);
VOS_VOID   GMM_CasCellS9E49(VOS_VOID *pRcvMsg);
VOS_VOID   GMM_CasCellS10E49(VOS_VOID *pRcvMsg);
VOS_VOID   GMM_CasCellS11E49(VOS_VOID *pRcvMsg);
VOS_VOID   NAS_GMM_EnterCovery(VOS_VOID *pRcvMsg);
VOS_VOID   GMM_CasCellS18E49(VOS_VOID *pRcvMsg);
VOS_VOID   GMM_CasCellS19E49(VOS_VOID *pRcvMsg);
VOS_VOID   GMM_CasCellS22E49(VOS_VOID *pRcvMsg);
VOS_VOID   GMM_CasCellS23E49 ( VOS_VOID *pRcvMsg );
VOS_UINT32 GMM_CasCellS0E50(VOS_VOID *pRcvMsg);
VOS_UINT32 GMM_CasCellS22E50(VOS_VOID *pRcvMsg);
VOS_UINT32 GMM_CasCellS0E51(VOS_VOID *pRcvMsg);
VOS_UINT32 GMM_CasCellS22E51(VOS_VOID *pRcvMsg);
VOS_UINT32 GMM_CasCellS0E52(VOS_VOID *pRcvMsg);
VOS_UINT32 GMM_CasCellS1E53(VOS_VOID *pRcvMsg);
VOS_UINT32 GMM_CasCellS8E53(VOS_VOID *pRcvMsg);
VOS_UINT32 GMM_CasCellS22E53(VOS_VOID *pRcvMsg);
VOS_UINT32 GMM_CasCellS23E53(VOS_VOID *pRcvMsg);
VOS_UINT32 GMM_CasCellS1E54 ( VOS_VOID *pRcvMsg );
VOS_UINT32 GMM_CasCellS8E54 ( VOS_VOID *pRcvMsg );
VOS_UINT32 GMM_CasCellS22E54 ( VOS_VOID *pRcvMsg );
VOS_UINT32 GMM_CasCellS23E54 ( VOS_VOID *pRcvMsg );
VOS_UINT32 GMM_CasCellS0E55(VOS_VOID *pRcvMsg);
VOS_UINT32 GMM_CasCellS8E55(VOS_VOID *pRcvMsg);
VOS_UINT32 GMM_CasCellS9E55 (VOS_VOID *pRcvMsg);
VOS_UINT32 GMM_CasCellS14E55 (VOS_VOID *pRcvMsg);
VOS_UINT32 GMM_CasCellS16E55 (VOS_VOID *pRcvMsg);
VOS_UINT32 GMM_CasCellS18E55 (VOS_VOID *pRcvMsg);
VOS_UINT32 GMM_CasCellS19E55 (VOS_VOID *pRcvMsg);
VOS_UINT32 GMM_CasCellS20E55 (VOS_VOID *pRcvMsg);
VOS_UINT32 GMM_CasCellS22E55(VOS_VOID *pRcvMsg);
VOS_UINT32 GMM_CasCellS23E55(VOS_VOID *pRcvMsg);
VOS_UINT32 GMM_CasCellS0E56 ( VOS_VOID *pRcvMsg );
VOS_UINT32 GMM_CasCellS16E56 ( VOS_VOID *pRcvMsg );
VOS_UINT32 GMM_CasCellS18E56 ( VOS_VOID *pRcvMsg );
VOS_UINT32 GMM_CasCellS22E56 ( VOS_VOID *pRcvMsg );
VOS_UINT32 GMM_CasCellS23E56 ( VOS_VOID *pRcvMsg );
VOS_UINT32 GMM_CasCellS0E57 ( VOS_VOID *pRcvMsg );
VOS_UINT32 GMM_CasCellS19E57 ( VOS_VOID *pRcvMsg );
VOS_UINT32 GMM_CasCellS22E57 ( VOS_VOID *pRcvMsg );
VOS_UINT32 GMM_CasCellS23E57 ( VOS_VOID *pRcvMsg );
VOS_UINT32 GMM_CasCellS0E58 ( VOS_VOID *pRcvMsg );
VOS_UINT32 GMM_CasCellS19E58 ( VOS_VOID *pRcvMsg );
VOS_UINT32 GMM_CasCellS22E58 ( VOS_VOID *pRcvMsg );
VOS_UINT32 GMM_CasCellS23E58 ( VOS_VOID *pRcvMsg );
VOS_UINT32 GMM_CasCellS0E59 ( VOS_VOID *pRcvMsg );
VOS_UINT32 GMM_CasCellS20E59 ( VOS_VOID *pRcvMsg );
VOS_UINT32 GMM_CasCellS22E59 ( VOS_VOID *pRcvMsg );
VOS_UINT32 GMM_CasCellS23E59 ( VOS_VOID *pRcvMsg );
VOS_UINT32 GMM_CasCellS0E60 ( VOS_VOID *pRcvMsg );
VOS_UINT32 GMM_CasCellS20E60 ( VOS_VOID *pRcvMsg );
VOS_UINT32 GMM_CasCellS22E60 ( VOS_VOID *pRcvMsg );
VOS_UINT32 GMM_CasCellS23E60 ( VOS_VOID *pRcvMsg );
VOS_UINT32 GMM_CasCellS0E61 ( VOS_VOID *pRcvMsg );
VOS_UINT32 GMM_CasCellS8E61 ( VOS_VOID *pRcvMsg );
VOS_UINT32 GMM_CasCellS22E61 ( VOS_VOID *pRcvMsg );
VOS_UINT32 GMM_CasCellS23E61 ( VOS_VOID *pRcvMsg );
VOS_UINT32 GMM_CasCellS0E62 ( VOS_VOID *pRcvMsg );
VOS_UINT32 GMM_CasCellS8E62 ( VOS_VOID *pRcvMsg );
VOS_UINT32 GMM_CasCellS22E62 ( VOS_VOID *pRcvMsg );
VOS_UINT32 GMM_CasCellS23E62 ( VOS_VOID *pRcvMsg );
VOS_UINT32 GMM_CasCellS8E63 ( VOS_VOID *pRcvMsg );
VOS_UINT32 GMM_CasCellS22E63 ( VOS_VOID *pRcvMsg );
VOS_UINT32 GMM_CasCellS23E63 ( VOS_VOID *pRcvMsg );
VOS_UINT32 GMM_CasCellS0E64 ( VOS_VOID *pRcvMsg );
VOS_UINT32 GMM_CasCellS8E64 ( VOS_VOID *pRcvMsg );
VOS_UINT32 GMM_CasCellS22E64 ( VOS_VOID *pRcvMsg );
VOS_UINT32 GMM_CasCellS23E64 ( VOS_VOID *pRcvMsg );
VOS_UINT32 GMM_CasCellS1E65 ( VOS_VOID *pRcvMsg );
VOS_UINT32 GMM_CasCellS22E65 ( VOS_VOID *pRcvMsg );
VOS_UINT32 GMM_CasCellS23E65 ( VOS_VOID *pRcvMsg );
VOS_UINT32 GMM_CasCellS1E66 ( VOS_VOID *pRcvMsg );
VOS_UINT32 GMM_CasCellS22E66 ( VOS_VOID *pRcvMsg );
VOS_UINT32 GMM_CasCellS23E66 ( VOS_VOID *pRcvMsg );
VOS_UINT32 GMM_CasCellS0E67 ( VOS_VOID *pRcvMsg );
VOS_UINT32 GMM_CasCellS0E68 (VOS_VOID *pRcvMsg);
VOS_UINT32 GMM_CasCellS0E69 (VOS_VOID *pRcvMsg);
VOS_UINT32 GMM_CasCellS0E70 (VOS_VOID *pRcvMsg);
VOS_UINT32 GMM_CasCellS0E71 ( VOS_VOID *pRcvMsg );
VOS_VOID   GMM_CasCellS1E72(VOS_VOID *pRcvMsg);
VOS_UINT32 GMM_CasCellS9E72(VOS_VOID *pRcvMsg);
VOS_UINT32 GMM_CasCellS22E72 ( VOS_VOID *pRcvMsg );
VOS_UINT32 GMM_CasCellS0E73(VOS_VOID *pRcvMsg);
VOS_UINT32 GMM_CasCellS22E73 ( VOS_VOID *pRcvMsg );
VOS_VOID   GMM_CasCellS23E73 ( VOS_VOID *pRcvMsg );
VOS_UINT32 GMM_CasCellS24E73 ( VOS_VOID *pRcvMsg );

VOS_UINT32 NAS_GMM_GsmAccessBarredProcess(VOS_VOID);
VOS_UINT32 NAS_GMM_GasSysInfoPreCheck(VOS_VOID *pMsg);
VOS_VOID NAS_GMM_GasSysInfoDistribute(VOS_VOID *pMsg);


VOS_VOID GMM_RcvGasSysInfoInd (VOS_VOID *pMsg);
VOS_VOID GMM_RcvLlcDataInd(VOS_VOID *pRcvMsg);
VOS_VOID NAS_GMM_RcvLlcDataCnf(
    VOS_VOID                           *pRcvMsg
);
VOS_VOID NAS_GMM_RcvLlcDataCnf_PowerOff(VOS_VOID);
VOS_VOID GMM_RcvGasPagingInd(VOS_VOID *pMsg);
VOS_VOID GMM_RcvGasTbfRleInd( VOS_VOID *pRcvMsg );
VOS_VOID GMM_RcvGasRadioAccessCapa( VOS_VOID *pRcvMsg );
VOS_VOID GMM_RcvGasTdsRadioAccessCapa(
    VOS_VOID                           *pstRcvMsg
);
/* Added by w00176964 for VoLTE_PhaseII 项目, 2013-10-22, begin */
VOS_VOID GMM_RcvGasClassMarkChangeInd( VOS_VOID *pRcvMsg );
/* Added by w00176964 for VoLTE_PhaseII 项目, 2013-10-22, end */

VOS_VOID GMM_SaveReadyTimerValue(
                        VOS_UINT8 ucMsgByte                 /* 消息中时长位置的字节 */
                        );
VOS_VOID GMM_InitCellUpdate(VOS_UINT8 ucReadychangFLG);

VOS_VOID NAS_GMM_InitCellUpdate_RcvSysInfo(VOS_UINT8 ucReadychangFLG);
VOS_UINT8 GMM_CasGetMsGprsMode(VOS_VOID);
VOS_UINT8 GMM_CasGetGmmState(VOS_VOID);

VOS_VOID GMM_CasFsmStateChangeTo(VOS_UINT8 ucFsmSta);

VOS_VOID GMM_RcvGasSysInfoInd_SuspWaitSys(VOS_VOID *pRcvMsg);
VOS_VOID GMM_RcvGasSuspensionInd(VOS_VOID *pRcvMsg);
VOS_VOID GMM_RcvGasGprsResumeInd(VOS_VOID *pRcvMsg);
VOS_VOID NAS_GMM_HandleGrpsResumeFail(VOS_VOID);

extern VOS_VOID NAS_GMM_EnterCoveryRaiNoChg_BeforeT3312Exp(VOS_VOID);
extern VOS_VOID NAS_GMM_EnterCoveryRaiNoChg_AfterT3312Exp(VOS_VOID);
extern VOS_VOID NAS_GMM_ProcessSmMsgInBuff();

VOS_VOID NAS_GMM_RcvGprsAccessResultInd(
    VOS_VOID                           *pstMsg
);

VOS_VOID NAS_GMM_SaveGsmSysInfo(
    MMCGMM_GSM_SYS_INFO_IND_ST         *pstGsmSysInfo
);

VOS_VOID NAS_GMM_ProcSavedGsmSysInfo(VOS_VOID);

VOS_VOID NAS_GMM_FreeGsmSysInfo(VOS_VOID);

VOS_VOID NAS_GMM_ProcSavedMmT3211ExpiredNotify(VOS_VOID);
VOS_UINT8 NAS_GMM_GetMmT3211ExpiredDelayRauFlag(VOS_VOID);
VOS_VOID NAS_GMM_SetMmT3211ExpiredDelayRauFlag(
    VOS_UINT8                           ucMmT3211ExpiredDelayRauFlag
);


VOS_VOID NAS_GMM_NotifyRrmmChgNonDrxMode(
    VOS_UINT8 ucCurState,
    VOS_UINT8 ucTargetState
);

VOS_VOID NAS_GMM_UpdateClassmark1(
    NAS_MML_MS_CAPACILITY_INFO_STRU    *pstMsCapability,
    RRMM_CLASSMARK_CHANGE_IND_STRU     *pstClassMarkMsg
);
VOS_VOID NAS_GMM_UpdateClassmark2(
    NAS_MML_MS_CAPACILITY_INFO_STRU    *pstMsCapability,
    RRMM_CLASSMARK_CHANGE_IND_STRU     *pstClassMarkMsg
);
VOS_VOID NAS_GMM_UpdateClassmark3(
    NAS_MML_MS_CAPACILITY_INFO_STRU    *pstMsCapability,
    RRMM_CLASSMARK_CHANGE_IND_STRU     *pstClassMarkMsg
);

#if ((VOS_OS_VER == VOS_WIN32) || (VOS_OS_VER == VOS_NUCLEUS))
#pragma pack()
#else
#pragma pack(0)
#endif

#ifdef __cplusplus
    #if __cplusplus
        }
    #endif
#endif

#endif /* end of GmmCasGsm.h*/
