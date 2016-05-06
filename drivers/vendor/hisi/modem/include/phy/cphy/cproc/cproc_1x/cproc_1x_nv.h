/**

                   Huawei Technologies Sweden AB (C), 2001-2011,

 ******************************************************************************
 * @file
 *
 * @author  F73150
 * @version
 * @date    2015/03/03 15:20(+0100)
 * @copyright Huawei Technologies Sweden AB
******************************************************************************/

/*****************************************************************************
  1 Other files included
*****************************************************************************/
#ifndef INCLUSION_GUARD_CPROC_1X_NV_H
#define INCLUSION_GUARD_CPROC_1X_NV_H

#ifdef __cplusplus
extern "C"{
#endif /* __cplusplus */
#include "PhyNvDefine.h"
#include "CasNvInterface.h"
#include "uphy_type_define.h"

/*****************************************************************************
  2 Macro definitions
*****************************************************************************/
/* NV context, include all struct */
#define CPROC_1X_GetNvContextAddress()       ( pstCproc1xNvContext )

/* Optimize switch data address, include n2m and n3m */
#define CPROC_1X_GetOptimizeSwitchAddress()       ( &(CPROC_1X_GetNvContextAddress())->stCproc1xOptimizeSwitch )

/* Filter coef data address */
#define CPROC_1X_GetFilterCoefAddress()      ( &(CPROC_1X_GetNvContextAddress())->stCproc1xFilterCoef )

/* n2m config value, read from nv table */
#define CPROC_1X_GetN2mHuaweiConfigValue()   ( (CPROC_1X_GetOptimizeSwitchAddress())->ucN2mHuaweiConfigValue )

/* n3m config value, read from nv table */
#define CPROC_1X_GetN3mHuaweiConfigValue()   ( (CPROC_1X_GetOptimizeSwitchAddress())->ucN3mHuaweiConfigValue )

/* Get MPS threshold NV data address */
#define CPROC_1X_GetMPSThresholdAddress()       ( &(CPROC_1X_GetNvContextAddress())->stCproc1xSmMpsThreshold )

/* Get ref PN threshold data address */
#define CPROC_1X_GetRefPNThresholdAddress()     ( &(CPROC_1X_GetMPSThresholdAddress())->stCproc1xMpsRefPNThreshold )

/* Threshold for changing to a new reference */
#define CPROC_1X_GetRemoveOldRefPNThreshold()   ( (CPROC_1X_GetRefPNThresholdAddress())->sRemoveOldRefPNThreshold )

/* Threshold above reference EcNo before changing reference */
#define CPROC_1X_GetNewRefPNThreshold()         ( (CPROC_1X_GetRefPNThresholdAddress())->usNewRefPNThreshold )

/* Number of times above threshold berfore changing reference */
#define CPROC_1X_GetNewRefPNCount()             ( (CPROC_1X_GetRefPNThresholdAddress())->usNewRefPNCount )

/*****************************************************************************
  3 Enumeration declaration
*****************************************************************************/

/*****************************************************************************
  4 Message Header declaration
*****************************************************************************/

/*****************************************************************************
  5 Message declarations
*****************************************************************************/

/*****************************************************************************
  6 STRUCT declarations
*****************************************************************************/

typedef struct CPROC_1X_NV_TABLE_STRU
{
    UCOM_NV_CDMA_1X_CPROC_GENERAL_STRU stGeneral;
    UCOM_NV_SINGLE_XO_DEFINE_STRU      stXoDefine;
}CPROC_1X_NV_TABLE_STRU;

typedef struct CPROC_1X_NV_CONTEXT_STRU
{
    CPROC_1X_NVIM_FILTER_COEF_STRU          stCproc1xFilterCoef;
    CPROC_1X_NVIM_OPTIMIZE_SWITCH_STRU      stCproc1xOptimizeSwitch;
    CPROC_1X_NVIM_SM_MPS_THRESHOLD_STRU     stCproc1xSmMpsThreshold; /* threshold for MPS */
    CPROC_1X_NVIM_TAS_CTRL_STRU             stCproc1xTas;
}CPROC_1X_NV_CONTEXT_STRU;
/*****************************************************************************
  7 UNION declarations
*****************************************************************************/

/*****************************************************************************
  8 OTHER declarations
*****************************************************************************/

/*****************************************************************************
  9 Global variables
*****************************************************************************/

/*****************************************************************************
  10 Function declarations
*****************************************************************************/
/*nv context pointer*/
extern CPROC_1X_NV_CONTEXT_STRU *pstCproc1xNvContext;

CPROC_1X_NV_TABLE_STRU* pstGetCproc1xNvAddress(PHY_VOID);
PHY_VOID CPROC_1X_GetFilterCoefFromNvTable( PHY_VOID );


PHY_VOID CPROC_1X_ReadNvTable( PHY_VOID );

#ifdef __cplusplus
}
#endif /* __cplusplus */

#endif /* INCLUSION_GUARD_CPROC_1X_NV_H */
