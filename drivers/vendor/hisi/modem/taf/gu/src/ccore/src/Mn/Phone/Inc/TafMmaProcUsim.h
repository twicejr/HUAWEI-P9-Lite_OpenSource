/******************************************************************************

                  版权所有 (C), 2001-2014, 华为技术有限公司

 ******************************************************************************
  文 件 名   : TafMmaProcUsim.h
  版 本 号   : 初稿
  作    者   : s00261364
  生成日期   : 2014年4月17日
  最近修改   :
  功能描述   : TafMmaProcUsim.c 的头文件
  函数列表   :
  修改历史   :
  1.日    期   : 2014年4月17日
    作    者   : s00261364
    修改内容   : 创建文件
******************************************************************************/
#ifndef _TAF_MMA_PROC_USIM_H
#define _TAF_MMA_PROC_USIM_H

/*****************************************************************************
  1 其他头文件包含
*****************************************************************************/
#include "TafSdcCtx.h"
#include "MmaAppLocal.h"

#include "TafMmaCtx.h"

#ifdef __cplusplus
#if __cplusplus
extern "C" {
#endif
#endif


#pragma pack(4)

/*****************************************************************************
  2 宏定义
*****************************************************************************/

#define TAF_MMA_EFRUIMID_OCTET_LEN_EIGHT                   (8)
#define TAF_MMA_EFRUIMID_OCTET_LEN_FIVE                    (5)

/*****************************************************************************
  3 枚举定义
*****************************************************************************/
/* 移到TafMmaCtx.h中 */

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


/*****************************************************************************
  10 函数声明
*****************************************************************************/
#if (FEATURE_ON == FEATURE_ECALL)

VOS_VOID TAF_MMA_UpdateCallMode( VOS_VOID );

#endif

VOS_VOID    TAF_MMA_SetWaitSimFilesCnfFlg(
    TAF_MMA_READ_SIM_FILES_CNF_ENUM_UINT32                  enSimFileCnfFlg
);

TAF_MMA_READ_SIM_FILES_CNF_ENUM_UINT32  TAF_MMA_GetWaitSimFilesCnfFlg(VOS_VOID);
VOS_VOID  TAF_MMA_ClearAllWaitSimFilesCnfFlg(VOS_VOID);
VOS_VOID  TAF_MMA_ReadSimCphsOperNameFile(VOS_VOID);

VOS_VOID TAF_MMA_ReadSpnFile(VOS_VOID);

VOS_UINT32 TAF_MMA_UsimGetFileRspPreProc(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg
);

VOS_VOID TAF_MMA_ReadOplFile(VOS_VOID);
VOS_VOID TAF_MMA_ReadPnnFile(VOS_VOID);
VOS_VOID TAF_MMA_ReadSpdiFile(VOS_VOID);
VOS_UINT32 TAF_MMA_SendUsimFileReq(
    USIMM_CARDAPP_ENUM_UINT32           enAppType,
    VOS_UINT16                          usEfId
);
VOS_VOID  TAF_MMA_ClearWaitSimFilesCnfFlg(
    USIMM_DEF_FILEID_ENUM_UINT32        usEfId
);
VOS_VOID TAF_MMA_ReadCustomerServiceProfileFile_SwitchOn(VOS_VOID);

VOS_VOID   TAF_MMA_ReadCphsFileCnf(
    USIMM_READFILE_CNF_STRU            *pUsimTafMsg
);
VOS_VOID TAF_MMA_UsimRefreshIndFileListChangedMsgProc(USIMM_STKREFRESH_IND_STRU *pUsimTafMsg);
VOS_VOID TAF_MMA_ReadIccIdFileCnf(VOS_VOID);
VOS_VOID TAF_MMA_ReadSpdiFileCnf(
    USIMM_READFILE_CNF_STRU            *pUsimTafMsg,
    USIMM_DEF_FILEID_ENUM_UINT32        enFileID
);
VOS_VOID TAF_MMA_ReadPnnFileCnf(
    USIMM_READFILE_CNF_STRU            *pUsimTafMsg,
    USIMM_DEF_FILEID_ENUM_UINT32        enFileID
);
VOS_VOID TAF_MMA_ReadOplFileCnf(
    USIMM_READFILE_CNF_STRU            *pUsimTafMsg,
    USIMM_DEF_FILEID_ENUM_UINT32        enFileID
);

VOS_VOID MMA_ReadSpnFileCnf(
    TAF_PH_USIM_SPN_CNF_STRU           *pMsg,
    USIMM_DEF_FILEID_ENUM_UINT32        enFileID
);

VOS_VOID TAF_MMA_RcvCustomerServiceProfileFile(
    VOS_UINT32                          ulRslt,
    VOS_UINT16                          usEfLen,
    VOS_UINT8                          *pucEf
);

VOS_VOID TAF_MMA_USIMRefreshFileProc(
    VOS_UINT16                          usEfId,
    VOS_UINT16                          usEfLen,
    VOS_UINT8                          *pucEf
);


#if (FEATURE_ON == FEATURE_UE_MODE_CDMA)
VOS_VOID TAF_MMA_ReadImsimFile( VOS_VOID );

VOS_VOID TAF_MMA_ReadRuimidFile( VOS_VOID );
VOS_VOID TAF_MMA_RcvUsimmReadRuimidFile(
    USIMM_READFILE_CNF_STRU            *pstUsimmReadCnfMsg
);
#endif

#if (VOS_OS_VER == VOS_WIN32)
#pragma pack()
#else
#pragma pack(0)
#endif




#ifdef __cplusplus
    #if __cplusplus
        }
    #endif
#endif

#endif


