/**
 * @file vos_redef.h
 *
 * Copyright(C), 2008-2050, Huawei Tech. Co., Ltd. ALL RIGHTS RESERVED. \n
 *
 * 描述：OSAL符号重定义头文件。 \n
 */

/**@defgroup vos_redef OSAL符号重定义
 *@ingroup OSAL
*/

#ifndef __VOS_REDEF_H__
#define __VOS_REDEF_H__

#ifdef __cplusplus
#if __cplusplus
extern "C" {
#endif /* __cpluscplus */
#endif /* __cpluscplus */

#define VOS_sscanf                          RTOSCK_sscanf
#define VOS_Mem_Cmp                         RTOSCK_Mem_Cmp
#define VOS_Mem_Set                         RTOSCK_Mem_Set
#define VOS_MemSet                          RTOSCK_MemSet
#define VOS_StrNCmp                         RTOSCK_StrNCmp
#define VOS_StrICmp                         RTOSCK_StrICmp
#define VOS_atoul                           RTOSCK_atoul
#define VOS_Mem_Zero                        RTOSCK_Mem_Zero
#define VOS_Mem_Copy                        RTOSCK_Mem_Copy
#define VOS_StrRChr                         RTOSCK_StrRChr
#define VOS_MemChr                          RTOSCK_MemChr
#define VOS_StrToUint32                     RTOSCK_StrToUint32
#define VOS_strchr                          RTOSCK_strchr
#define VOS_strcpy                          RTOSCK_strcpy
#define VOS_StrCpy                          RTOSCK_StrCpy
#define VOS_strncpy                         RTOSCK_strncpy
#define VOS_strcat                          RTOSCK_strcat
#define VOS_StrNCat                         RTOSCK_StrNCat
#define VOS_strlen                          RTOSCK_strlen
#define VOS_StrStr                          RTOSCK_StrStr
#define VOS_strcmp                          RTOSCK_strcmp
#define VOS_strncmp                         RTOSCK_strncmp
#define VOS_toupper                         RTOSCK_toupper
#define VOS_tolower                         RTOSCK_tolower
#define VOS_stricmp                         RTOSCK_stricmp
#define VOS_strnicmp                        RTOSCK_strnicmp
#define VOS_vsprintf                        RTOSCK_vsprintf
#define VOS_nvsprintf                       RTOSCK_nvsprintf
#define VOS_sprintf                         RTOSCK_sprintf
#define VOS_nsprintf                        RTOSCK_nsprintf
#define vos_printf                          RTOSCK_printf
#define VOS_atol                            RTOSCK_atol
#define VOS_MemCpy                          RTOSCK_MemCpy
#define VOS_uppercase                       RTOSCK_uppercase
#define VOS_lowercase                       RTOSCK_lowercase
#define VOS_StrLen                          RTOSCK_StrLen
#define VOS_StrCmp                          RTOSCK_StrCmp
#define VOS_strsep                          RTOSCK_strsep
#define VOS_StrToIpAddr                     RTOSCK_StrToIpAddr
#define VOS_IpAddrToStr                     RTOSCK_IpAddrToStr
#define VOS_Malloc                          RTOSCK_Malloc
#define VOS_Free                            RTOSCK_Free
#define VOS_Mem_GetRef                      RTOSCK_Mem_GetRef
#define VOS_Mem_IncRef                      RTOSCK_Mem_IncRef
#define VOS_Mem_Calloc                      RTOSCK_Mem_Calloc
#define VOS_MemReAlloc                      RTOSCK_MemReAlloc
#define VOS_Que_Create                      RTOSCK_Que_Create
#define VOS_Que_Delete                      RTOSCK_Que_Delete
#define VOS_Que_Write                       RTOSCK_Que_Write
#define VOS_Que_Read                        RTOSCK_Que_Read
#define VOS_Que_GetMsgNum                   RTOSCK_Que_GetMsgNum
#define VOS_Que_GetMaxNum                   RTOSCK_Que_GetMaxNum
#define VOS_Que_GetName                     RTOSCK_Que_GetName
#define VOS_QueueDelete                     RTOSCK_QueueDelete
#define VOS_SmMCreate                       RTOSCK_SmMCreate
#define VOS_SmB_Create                      RTOSCK_SmB_Create
#define VOS_SmCCreate                       RTOSCK_SmCCreate
#define VOS_SmDelete                        RTOSCK_SmDelete
#define VOS_SmP                             RTOSCK_SmP
#define VOS_SmV                             RTOSCK_SmV
#define VOS_Sm_AsyP                         RTOSCK_Sm_AsyP
#define VOS_Ev_Read                         RTOSCK_Ev_Read
#define VOS_Ev_Write                        RTOSCK_Ev_Write
#define VOS_SplImp                          RTOSCK_SplImp
#define VOS_SplX                            RTOSCK_SplX
#define VOS_Tm_BootInSec                    RTOSCK_Tm_BootInSec
#define VOS_Tm_Now                          RTOSCK_Tm_Now
#define VOS_GetCpuTick                      RTOSCK_GetCpuTick
#define VOS_TickGet                         RTOSCK_TickGet
#define VOS_GetCpuTickBase                  RTOSCK_GetCpuTickBase
#define VOS_TmSecToTick                     RTOSCK_TmSecToTick
#define VOS_Tm_Get                          RTOSCK_Tm_Get
#define VOS_Tm_Since1970                    RTOSCK_Tm_Since1970
#define VOS_Tm_NowInSec                     RTOSCK_Tm_NowInSec
#define VOS_SYS_GetCurrentTime              RTOSCK_SYS_GetCurrentTime
#define VOS_TmNow                           RTOSCK_TmNow
#define VOS_DateTime_Cmp                    RTOSCK_DateTime_Cmp
#define VOS_DateTime_DeltaSec               RTOSCK_DateTime_DeltaSec
#define VOS_T_Create                        RTOSCK_T_Create
#define VOS_T_Delete                        RTOSCK_T_Delete
#define VOS_TaskLock                        RTOSCK_TaskLock
#define VOS_TaskUnlock                      RTOSCK_TaskUnlock
#define VOS_T_FreeCPU                       RTOSCK_T_FreeCPU
#define VOS_T_Delay                         RTOSCK_T_Delay
#define VOS_T_RunDelay                      RTOSCK_T_RunDelay
#define VOS_T_Suspend                       RTOSCK_T_Suspend
#define VOS_GetTaskName                     RTOSCK_GetTaskName
#define VOS_T_GetName                       RTOSCK_T_GetName
#define VOS_T_GetSelfID                     RTOSCK_T_GetSelfID
#define VOS_TaskIdValidate                  RTOSCK_TaskIdValidate
#define VOS_CreateTask                      RTOSCK_CreateTask
#define VOS_DeleteTask                      RTOSCK_DeleteTask
#define VOS_Timer_Create                    RTOSCK_Timer_Create
#define VOS_Timer_Delete                    RTOSCK_Timer_Delete
#define VOS_Timer_Resize                    RTOSCK_Timer_Resize
#define VOS_Timer_GetInfo                   RTOSCK_Timer_GetInfo
#define VOS_Timer_IsStoped                  RTOSCK_Timer_IsStoped
#define VOS_Timer_IsValid                   RTOSCK_Timer_IsValid
#define VOS_Timer_Pause                     RTOSCK_Timer_Pause
#define VOS_Timer_Resume                    RTOSCK_Timer_Resume
#define perror                              RTOSCK_perror
#define VOS_AdapterInit                     RTOSCK_AdapterInit

#ifdef __cplusplus
#if __cplusplus
}
#endif /* __cpluscplus */
#endif /* __cpluscplus */

#endif //__VOS_REDEF_H__

