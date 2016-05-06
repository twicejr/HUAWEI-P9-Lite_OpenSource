#ifndef _SRE_SYS_CALL_DEF_H
#define _SRE_SYS_CALL_DEF_H


#ifdef __cplusplus
#if __cplusplus
extern "C" {
#endif /* __cpluscplus */
#endif /* __cpluscplus */

#define OS_N_SYS_CALL_BASE                  16
#define OS_N_osTIDGet                       OS_N_SYS_CALL_BASE + 0
#define OS_N_osTIDClear                     OS_N_SYS_CALL_BASE + 1
#define OS_N_SRE_CycleCountGet64            OS_N_SYS_CALL_BASE + 2
#define OS_N_SRE_SigCreate                  OS_N_SYS_CALL_BASE + 3
#define OS_N_SRE_SigDelete                  OS_N_SYS_CALL_BASE + 4    
#define OS_N_SRE_SigUsrReg                  OS_N_SYS_CALL_BASE + 5
#define OS_N_SRE_SigSend                    OS_N_SYS_CALL_BASE + 6
#define OS_N_SRE_ProcessMsgmBufSet          OS_N_SYS_CALL_BASE + 7
#define OS_N_SRE_SelfPidGet                 OS_N_SYS_CALL_BASE + 8

//#define OS_N_SRE_HwSemCreate                OS_N_SYS_CALL_BASE + 9
//#define OS_N_SRE_HwSemDelete                OS_N_SYS_CALL_BASE + 10
//#define OS_N_SRE_HwSemPend                  OS_N_SYS_CALL_BASE + 11
//#define OS_N_SRE_HwSemPost                  OS_N_SYS_CALL_BASE + 12
//#define OS_N_SRE_HwSemReset                 OS_N_SYS_CALL_BASE + 13
//#define OS_N_SRE_HwSemCreateById            OS_N_SYS_CALL_BASE + 14 

#define OS_N_SRE_PrcesSleep                 OS_N_SYS_CALL_BASE + 15 


//#define OS_N_SRE_WaitForAllCores            OS_N_SYS_CALL_BASE + 16

#define OS_N_SRE_HuntByName                 OS_N_SYS_CALL_BASE + 17
#define OS_N_SRE_HuntPidByName              OS_N_SYS_CALL_BASE + 18
#define OS_N_SRE_HuntMature                 OS_N_SYS_CALL_BASE + 19
#define OS_N_SRE_TickCountGet               OS_N_SYS_CALL_BASE + 20
#define OS_N_osThreadNameAdd                OS_N_SYS_CALL_BASE + 21
#define OS_N_osThreadNameDel                OS_N_SYS_CALL_BASE + 22
#define OS_N_osThreadNameGet                OS_N_SYS_CALL_BASE + 23

//#define OS_N_SRE_QportRecv                  OS_N_SYS_CALL_BASE + 24
//#define OS_N_SRE_MsgmNorQueSet              OS_N_SYS_CALL_BASE + 25
#define OS_N_SRE_WaitForAllCores            OS_N_SYS_CALL_BASE + 24
#define OS_N_SRE_SyncBarrierWait            OS_N_SYS_CALL_BASE + 25
#define OS_N_SRE_HwiTrigger                 OS_N_SYS_CALL_BASE + 26


#define OS_N_SRE_SYS_CALL_END               OS_N_SYS_CALL_BASE + 27


#define OS_ERR_FUN_NAME                     0x0
#define OS_ERR_FUN_PARA_NUM                 0x1
#define OS_SYSCALL_ERROR_ID                 0x02002f00

#ifdef __cplusplus
#if __cplusplus
}
#endif /* __cpluscplus */
#endif /* __cpluscplus */


#endif /* _SRE_BUILDEF_H */


