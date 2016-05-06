/******************************************************************************

                  版权所有 (C), 2001-2011, 华为技术有限公司

 ******************************************************************************
  文 件 名   : CdsUlProc.h
  版 本 号   : 初稿
  作    者   : y00151394
  生成日期   : 2011年12月15日
  最近修改   :
  功能描述   : CDS上行数据处理头文件
  函数列表   :
  修改历史   :
  1.日    期   : 2011年12月12日
    作    者   : y00151394
    修改内容   : 创建文件

******************************************************************************/

#ifndef __CDS_ULPROC_H__
#define __CDS_ULPROC_H__

#ifdef __cplusplus
#if __cplusplus
extern "C" {
#endif
#endif


/*****************************************************************************
  1 其他头文件包含
*****************************************************************************/

#if (VOS_OS_VER != VOS_WIN32)
#pragma pack(4)
#else
#pragma pack(push, 4)
#endif

/*****************************************************************************
  2 宏定义
*****************************************************************************/

/*将RD中的FilterResult/ModemId/RabId保存到TTF的ulForCds[0]中*/
/*lint -emacro({717}, CDS_UL_SAVE_RD_INFO_TO_TTF)*/
/*lint -emacro({701}, CDS_UL_SAVE_RD_INFO_TO_TTF)*/
#define CDS_UL_SAVE_RD_INFO_TO_TTF(pstIpPkt,pstRd)      \
                            do\
                            {\
                                (pstIpPkt)->ulForCds[0] = 0;\
                                (pstIpPkt)->ulForCds[0] = (((pstRd)->u16Result)<<16) | ((pstRd)->u16UsrField1);\
                            }while(0)


/*上行将IPF RESULT/ModemId/RabId保持到TTF的保留域中*/
/*lint -emacro({717}, CDS_UL_SAVE_IPFRSLT_MODEMID_RABID_TO_TTF)*/
/*lint -emacro({701}, CDS_UL_SAVE_IPFRSLT_MODEMID_RABID_TO_TTF)*/
#define CDS_UL_SAVE_IPFRSLT_MODEMID_RABID_TO_TTF(pstIpPkt,usIpfRslt,usModemId,ucRabId) \
                            do\
                            {\
                                (pstIpPkt)->ulForCds[0] = 0;\
                                (pstIpPkt)->ulForCds[0] = ((usModemId) << 8) | ucRabId;\
                                (pstIpPkt)->ulForCds[0] = ((usIpfRslt) << 16) | ((pstIpPkt)->ulForCds[0]);\
                            }while(0)


/*上行将IPF RESULT保存到TTF的保留域中,用于二次过滤*/
/*lint -emacro({717}, CDS_UL_SAVE_IPFRSLT_TO_TTF)*/
/*lint -emacro({701}, CDS_UL_SAVE_IPFRSLT_TO_TTF)*/
#define CDS_UL_SAVE_IPFRSLT_TO_TTF(pstIpPkt,usIpfRslt) \
                            do\
                            {\
                                (pstIpPkt)->ulForCds[0] = ((pstIpPkt)->ulForCds[0]) & 0x0000FFFF;\
                                (pstIpPkt)->ulForCds[0] = ((usIpfRslt) << 16) | ((pstIpPkt)->ulForCds[0]);\
                            }while(0)

/*从TTF中获取过滤结果*/
#define CDS_UL_GET_IPF_RESULT_FORM_TTF(pstIpPkt)        ((VOS_UINT16)((((pstIpPkt)->ulForCds[0]) & 0xFFFF0000) >> 16))

/*从TTF中获取ModemId*/
#define CDS_UL_GET_MODEMID_FROM_TTF(pstIpPkt)           ((VOS_UINT16)((((pstIpPkt)->ulForCds[0]) & 0x0000FF00) >> 8))

/*从TTF中获取RabId*/
#define CDS_UL_GET_RABID_FROM_TTF(pstIpPkt)             ((VOS_UINT8)(((pstIpPkt)->ulForCds[0]) & 0x0000000F))

/*从TTF中获取PktType*/
#define CDS_UL_GET_PKT_TYPE_FROM_TTF(pstIpPkt)          ((VOS_UINT8)((((pstIpPkt)->ulForCds[0]) & 0x000000F0) >> 4))

/*IPF结果中标识错误的位域*/
#define CDS_UL_IPF_RESULT_PKT_ERROR_MASK                (0x7C00)

/*****************************************************************************
  3 Massage Declare
*****************************************************************************/

/*****************************************************************************
  4 枚举定义
*****************************************************************************/


/*****************************************************************************
   5 STRUCT定义
*****************************************************************************/



/*****************************************************************************
  6 UNION定义
*****************************************************************************/


/*****************************************************************************
  7 全局变量声明
*****************************************************************************/

extern VOS_VOID CDS_UlProcIpfResult(VOS_VOID);
extern VOS_VOID CDS_SendUlBuffData(CDS_ENTITY_STRU *pstCdsEntity);
extern VOS_VOID CDS_ClearUlBuffData(CDS_ENTITY_STRU *pstCdsEntity);
extern VOS_VOID CDS_UlDispatchDataByRanMode(CDS_ENTITY_STRU *pstCdsEntity, TTF_MEM_ST *pstIpPkt);

extern VOS_VOID CDS_TriggerUlProcOnFinalRD(VOS_VOID);
/*end*/

extern VOS_VOID CDS_UlGUClearBuffData(CDS_ENTITY_STRU *pstCdsEntity,VOS_UINT8 ucRabId);
extern VOS_VOID CDS_SendUlBuffDataToRabm(CDS_ENTITY_STRU *pstCdsEntity,VOS_UINT8 ucSendRabId);
extern VOS_VOID CDS_CDMASendUlBuffData(CDS_ENTITY_STRU *pstCdsEntity, VOS_UINT8 ucSendRabId);

/*****************************************************************************
  8 函数声明
*****************************************************************************/
RABM_RAB_STATUS_ENUM_UINT32 I1_NAS_RABM_GetRabIdStatus(VOS_UINT8 ucRabId);
VOS_VOID I1_NAS_RABM_UL_DataReq(CDS_RABM_TRANS_DATA_STRU *pstUlData);
RABM_RAB_STATUS_ENUM_UINT32 I2_NAS_RABM_GetRabIdStatus(VOS_UINT8 ucRabId);
VOS_VOID I2_NAS_RABM_UL_DataReq(CDS_RABM_TRANS_DATA_STRU *pstUlData);
VOS_UINT8 I1_TAF_APS_MapRabIdToPdnId(VOS_UINT8 ucRabId);
VOS_UINT8 I2_TAF_APS_MapRabIdToPdnId(VOS_UINT8 ucRabId);
VOS_UINT8 I1_TAF_APS_GetCdataBearStatus(VOS_UINT8 ucRabId);
VOS_UINT8 I2_TAF_APS_GetCdataBearStatus(VOS_UINT8 ucRabId);

/*****************************************************************************
  9 OTHERS定义
*****************************************************************************/


#if (VOS_OS_VER != VOS_WIN32)
#pragma pack()
#else
#pragma pack(pop)
#endif




#ifdef __cplusplus
    #if __cplusplus
        }
    #endif
#endif

#endif

