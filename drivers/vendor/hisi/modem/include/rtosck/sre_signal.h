/*--------------------------------------------------------------------------------------------------------------------------*/
/*!!Warning: This is a key information asset of Huawei Tech Co.,Ltd                                                         */
/*CODEMARK:kOyQZYzjDpyGdBAEC2GaWrXNs8MZYk9cpFfgXfKX0g1VVtQNxHnHCKsK8caFMiW8LvCCkwIW
Tc6iJlHGFi3nUeJwZnaqeEUBwq/bzU5cp8JMIZQR60CPwhsVGkig7D46L1mTcjaBXLwtoHt/
6v3Dah1fIWJ0QzaviBugQMTxyfdBxnyOas2YfpGASpq0YvtHfmHX7l8QwPfHpzP7j4EeXHMT
USc3qHiOuJ4gPVgZD1CGUi+Lkp5wZHTl1P4cpX3nmPzE0A11ZIZrF2sLrogADQ==*/
/*--------------------------------------------------------------------------------------------------------------------------*/
/**
 * @file sre_signal.h
 *
 * Copyright(C), 2008-2050, Huawei Tech. Co., Ltd. ALL RIGHTS RESERVED. \n
 *
 * 描述：任务模块的对外头文件。 \n
 */

 /**@defgroup SRE_siganl 任务基本功能
  *@ingroup SRE_kernel
 */

#ifndef _SRE_SIGNAL_H
#define _SRE_SIGNAL_H

#include "sre_base.h"

#ifdef __cplusplus
#if __cplusplus
extern "C" {
#endif /* __cpluscplus */
#endif /* __cpluscplus */




/**
 * @ingroup SRE_task
 * 任务名的最大长度。
 *
 * 任务名的最大长度，包括结尾符'\0'。
 */
//#define OS_TSK_NAME_LEN                                     16



/**
 * @ingroup SRE_signal
 * 任务错误码：信号未创建。
 *
 * 值: 0x02001a00
 *
 * 解决方案: 检查信号是否创建。
 */
#define OS_ERRNO_SIG_NOT_CREATED                            SRE_ERRNO_OS_ERROR(OS_MID_SIG, 0x00)


#if (OS_OPTION_USR_PROCESS == YES) 
/**
 * @ingroup  SRE_signal
 * @brief 创建信号。
 *
 * @par 描述:
 * 
 *
 * @attention
 * <ul>
 * <li></li>
 * </ul>
 *
 * @param  puwTaskPID [OUT] 类型#UINT32 *，保存任务PID。
 * @param  pstInitParam [IN] 类型#TSK_INIT_PARAM_S *，任务创建参数，其结构体中的成员参数uwStackAddr传入时必须进行初始化，若不采用用户配置的独立任务栈进行栈空间分配，该成员必须初始化为0。
 *

 * @retval #SRE_OK                              0x00000000，任务创建成功。
 * @par 依赖:
 * <ul><li>sre_signal.h：该接口声明所在的头文件。</li></ul>
 * @since RTOSck V100R001C01
 * @see SRE_TaskDelete | SRE_TaskCreateHookAdd | SRE_TaskCreateOnly
 */
//extern UINT32 UINT32 SRE_SigCreate(UINT32 uwPid, UINT32 uwSigNo, OS_SIG_ENTRY_HOOK pfnhandler);
#define SRE_SigCreate(uwPid, uwSigNo, pfnhandler) \
        (UINT32)SRE_SYSCALL(SRE_SigCreate, 3, (UINT32)uwPid, (UINT32)uwSigNo, (UINT32)pfnhandler)

//extern UINT32 SREK_SigDelete(UINT32 uwPid, UINT32 uwSigNo)  
#define SRE_SigDelete(uwPid, uwSigNo) \
        (UINT32)SRE_SYSCALL(SRE_SigDelete, 2, (UINT32)uwPid, (UINT32)uwSigNo)

//extern UINT32 SREK_SigUsrReg(UINT32 uwPid, UINT32* pUsrData, UINT32 uwSigSp) 
#define SRE_SigUsrReg(uwPid, pUsrData, uwSigSp) \
        (UINT32)SRE_SYSCALL(SRE_SigUsrReg, 3, (UINT32)uwPid, (UINT32)pUsrData, (UINT32)uwSigSp) 

//extern UINT32 SREK_SigSend(UINT32 uwPid, UINT32 uwSigNo)
#define SRE_SigSend(uwPid, uwSigNo) \
        (UINT32)SRE_SYSCALL(SRE_SigSend, 2, (UINT32)uwPid, (UINT32)uwSigNo) 


#endif



#ifdef __cplusplus
#if __cplusplus
}
#endif /* __cpluscplus */
#endif /* __cpluscplus */


#endif /* _SRE_SIGNAL_H */

/**
 * History:
 * 2008-02-20 l66919: Create this file.
 *
 * vi: set expandtab ts=4 sw=4 tw=80:
 */

