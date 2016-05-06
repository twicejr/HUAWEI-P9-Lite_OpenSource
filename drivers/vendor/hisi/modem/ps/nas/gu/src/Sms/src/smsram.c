/*******************************************************************************
  Copyright    : 2005-2007, Huawei Tech. Co., Ltd.
  File name:          SmrRam.c
  Description:        sms的全局变量定义
  Function List: 
               1.  
  History: 
      1.   张志勇      2004.03.09   新规作成
      2.Data :2007-08-20
        Author:z40661
        Modify:A32D12705
*******************************************************************************/
#include "smsinclude.h"


#ifdef  __cplusplus
  #if  __cplusplus
  extern "C"{
  #endif
#endif


SMC_ENTITY_STRU     g_SmcPsEnt;                                                 /* sms ps域的实体定义                       */
SMC_ENTITY_STRU     g_SmcCsEnt;                                                 /* sms cs域的实体定义                       */
VOS_UINT8               g_ucPsServiceStatus = SMS_FALSE;                        /* GMM的PS域是否注册标志                    */
VOS_UINT8               g_ucCsRegFlg = SMS_FALSE;                                                 /* MM的CS域是否注册标志                    */

SMR_ENTITY_STRU     g_SmrEnt;                                                   /* smr的实体定义                            */

/*
SMR_SMC_IMPORTED_FUNC_LIST_STRU   g_SmrSmcApiFunc;                              / * api函数实体定义                          * /
*/
VOS_UINT8               g_ucSmsMR;                                                     /* SMR层维护的短消息标识0～255              */
/* 增加全局量表示上层指定的传输域 */
VOS_UINT8                g_SndDomain;                                               /* 发送域 */


#ifdef  __cplusplus
  #if  __cplusplus
  }
  #endif
#endif

