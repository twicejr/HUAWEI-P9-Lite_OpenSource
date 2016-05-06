/*******************************************************************************
*
*
*                Copyright 2006, Huawei Technologies Co. Ltd.
*                            ALL RIGHTS RESERVED
*
*-------------------------------------------------------------------------------
*
*                              tcpip_debug.h
*
*  Project Code: VISPV1R5
*   Module Name: PUBLIC  
*  Date Created: 2006-5-22
*        Author: X36317
*   Description: 定义了DEBUG相关的宏
*
*-------------------------------------------------------------------------------
*  Modification History
*  DATE        NAME             DESCRIPTION    
*  -----------------------------------------------------------------------------
*  2005-3-26  X36317         Creat the first version.
*  2006-5-22  X36317         为消除PC-LINT告警所做的修改.
*  2006-6-16  X36317         第二阶段质量改进.
*
*******************************************************************************/

#ifdef  __cplusplus
extern  "C"{
#endif

#ifndef _TCPIP_DEBUG_H_
#define _TCPIP_DEBUG_H_

extern VOID TCPIP_DebugOutput(CHAR *pDebugInfo);
        
#endif  /* _TCPIP_DEBUG_H_ */

#ifdef  __cplusplus
}
#endif
