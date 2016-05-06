/*******************************************************************************
  Copyright    : 2005-2007, Huawei Tech. Co., Ltd.
  File name    : SsRam.c
  Description  : SS全局变量实体
  Function List:
      1.  NULL
  History:
      1.  张志勇      2004.02.27   新版作成
      2.  丁  庆      2006.11.07   问题单A32D07063
*******************************************************************************/

#include "SsInclude.h"


#ifdef  __cplusplus
  #if  __cplusplus
  extern "C"{
  #endif
#endif


/* 实体定义    */
SS_ENTITY_STRU                  g_SsEntity[SS_MAX_ENTITY_NUM];                  /* SS实体定义                               */
SS_SAVE_MSG_STRU                g_SsSaveMsg[SS_MO_ENTITY_NUM];                  /* 缓存REGISTER消息                         */
/*=>A32D07063*/
#if 0
SS_TIMER_MNG_STRU               g_SsTimerMng[SS_MAX_ENTITY_NUM];                /* SS TIMER管理                             */
#endif
/*<=A32D07063*/


#ifdef  __cplusplus
  #if  __cplusplus
  }
  #endif
#endif

