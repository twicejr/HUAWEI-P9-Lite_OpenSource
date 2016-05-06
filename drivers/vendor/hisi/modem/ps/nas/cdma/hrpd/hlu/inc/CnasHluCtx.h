/******************************************************************************

                  版权所有 (C), 2001-2011, 华为技术有限公司

 ******************************************************************************
  文 件 名   : CnasHluCtx.h
  版 本 号   : 初稿
  作    者   : y00213812
  生成日期   : 2014年12月17日
  最近修改   :
  功能描述   : CnasHluCtx.c 的头文件
  函数列表   :
  修改历史   :
  1.日    期   : 2014年12月17日
    作    者   : y00213812
    修改内容   : 创建文件

******************************************************************************/

#ifndef __CNAS_HLU_CTX_H__
#define __CNAS_HLU_CTX_H__

/*****************************************************************************
  1 Include files
*****************************************************************************/
#include "hsd_hlu_pif.h"
#include "cnas_cttf_hrpd_pa_pif.h"


#ifdef __cplusplus
#if __cplusplus
extern "C" {
#endif
#endif


#pragma pack(4)

/*****************************************************************************
  2 Macro definitions
*****************************************************************************/
/* BYTES, Max len of param StorageBLOB = 8*StorageBLOBLength bits */
#define CNAS_HLU_STORAGE_BLOB_MAX_LEN   ( 255 )


/*****************************************************************************
  3 ENUM define
*****************************************************************************/


/*****************************************************************************
  4 Global Variable declaration
*****************************************************************************/


/*****************************************************************************
  5 Message Header define
*****************************************************************************/


/*****************************************************************************
  6 Message define
*****************************************************************************/


/*****************************************************************************
  7 STRUCT
*****************************************************************************/

typedef struct
{
    VOS_UINT16                          usSID;
    VOS_UINT16                          usNID;
    VOS_UINT8                           ucPacketZoneID;
    VOS_UINT8                           aucReserved[3];
}CNAS_HLU_LOC_VALUE_STRU;


typedef struct
{
    VOS_UINT8                           ucTransID;
    VOS_UINT8                           ucLocType;
    VOS_UINT8                           ucLocLen;
    VOS_UINT8                           ucReserve1;
    CNAS_HLU_LOC_VALUE_STRU             stLocVal;
}CNAS_HLU_LOC_STRU;


typedef struct
{
    VOS_UINT8                           ucTransID;
    VOS_UINT8                           ucReserve1;
    VOS_UINT16                          usStrgBLOBtype;
    VOS_UINT8                           ucStrgBLOBLen;
    VOS_UINT8                           aucStorageBLOB[CNAS_HLU_STORAGE_BLOB_MAX_LEN];
}CNAS_HLU_BLOB_STRU;


typedef struct
{
    CNAS_HLU_LOC_STRU                   stLocCtx;
    CNAS_HLU_BLOB_STRU                  stBLOBCtx;
    /* RANHAndoff value set by layer 2 */
    CTTF_HRPD_PROTOCOL_TYPE_ENUM_UINT16 enProtocolType;
    VOS_UINT8                           ucRANHandoff;
    /* 1X_TO_HRPD_HANDOFF msg ID */
    VOS_UINT8                           ucOpId;
    VOS_UINT8                           ucHandOffFlg;       /* 当前是否正在进行HandOff相关处理的标记 */

    VOS_UINT8                           aucReserve[3];

}CNAS_HLU_CTX_STRU;


typedef struct
{
    VOS_UINT16                          usStrgBLOBtype;
    VOS_UINT8                           ucStrgBLOBLen;
    VOS_UINT8                           aucStorageBLOB[CNAS_HLU_STORAGE_BLOB_MAX_LEN];
}CNAS_HLU_STRG_BLOB_STRU;

/*****************************************************************************
  8 UNION
*****************************************************************************/


/*****************************************************************************
  9 OTHERS
*****************************************************************************/


/*****************************************************************************
  10 Function declaration
*****************************************************************************/

CNAS_HLU_CTX_STRU *CNAS_HLU_GetLocCtxAddr(VOS_VOID);

VOS_UINT16 CNAS_HLU_GetCurrSid(VOS_VOID);

VOS_UINT16 CNAS_HLU_GetCurrNid(VOS_VOID);

VOS_UINT8 CNAS_HLU_GetCurrPcktZoneId(VOS_VOID);

VOS_UINT8 CNAS_HLU_GetLocMsgTransId(VOS_VOID);

VOS_UINT8 CNAS_HLU_GetBLobTransId(VOS_VOID);

VOS_VOID CNAS_HLU_GetCurrLocValHToN(
    VOS_UINT8                          *pucLocValue,
    VOS_BOOL                            bIsHandOff,
    const CNAS_HLU_LOC_VALUE_STRU      *pstHandOffLocVal
);

VOS_VOID CNAS_HLU_GetCurrStrgBlobHToN(
    VOS_UINT8                          *pucLocValue
);

VOS_BOOL CNAS_HLU_IsCurrLocTypeValid(VOS_VOID);

VOS_BOOL CNAS_HLU_IsCurrBlobTypeValid(VOS_VOID);

VOS_UINT8 CNAS_HLU_GetCurrBlobLen(VOS_VOID);

VOS_UINT16 CNAS_HLU_GetCurrBlobType(VOS_VOID);

VOS_UINT8 CNAS_HLU_GetRANHandoff(VOS_VOID);

VOS_VOID CNAS_HLU_SetRANHandoff(
    VOS_UINT8                           ucRANHandOff
);


VOS_VOID CNAS_HLU_SetHandOffOpId(VOS_VOID);

VOS_UINT8 CNAS_HLU_GetHandOffOpId(VOS_VOID);

CTTF_HRPD_PROTOCOL_TYPE_ENUM_UINT16 CNAS_HLU_GetProtocolType(VOS_VOID);

VOS_VOID CNAS_HLU_SetProtocolType(CTTF_HRPD_PROTOCOL_TYPE_ENUM_UINT16 enCurrProtocolType);

VOS_UINT8 CNAS_HLU_GetHandOffFlg(VOS_VOID);

VOS_VOID CNAS_HLU_SetHandOffFlg(
    VOS_UINT8                           ucHandOffFlg
);

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

#endif /* end of CnasHluCtx.h */
