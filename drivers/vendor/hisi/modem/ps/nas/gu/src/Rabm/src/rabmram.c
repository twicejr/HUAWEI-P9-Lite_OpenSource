/*******************************************************************************
  Copyright    : 2005-2007, Huawei Tech. Co., Ltd.
  File name    : rabmram.c
  Description  : rabm的全局变量定义
  Function List:

  History:
      1.   张志勇      2004.04.01   新规作成
*******************************************************************************/
#include "rabminclude.h"


#ifdef  __cplusplus
  #if  __cplusplus
  extern "C"{
  #endif
#endif



RABM_ENTITY_PS_STRU    g_aRabmPsEnt[RABM_PS_MAX_ENT_NUM];                       /* PS域RABM实体的全局量                     */

RABM_ENTITY_CS_STRU    g_aRabmCsEnt[RABM_CS_MAX_ENT_NUM];                       /* CS域RABM实体的全局量                     */


VOS_UINT8        g_aucSiMapEnt[256];                                                /* SI和RABM实体的映射关系                   */

VOS_UINT8        g_ucReestTimerFlg;                                                 /* RABM_TRUE:重建TIMER有效；RABM_FALSE:无效 */

HTIMER     g_ulRabReestTimerId;                                               /* rab重建timer                             */

RABM_RRC_IMPORTED_FUNC_LIST_STRU  g_RabmRrcImportFunc;                          /* API定义                                  */

RABM_TC_INF_STRU       g_RabmTcInf;

PDCP_RABM_TC_DATA_Q_STRU g_stPdcpRabmTcDataQ;

VOS_UINT32                              g_ulNasRabmRabPendingTmrLen = 7000;     /* 默认7秒 */


#ifdef  __cplusplus
  #if  __cplusplus
  }
  #endif
#endif

