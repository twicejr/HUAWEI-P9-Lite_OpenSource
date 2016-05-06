/**
    @copyright: Huawei Technologies Co., Ltd. 2012-2012. All rights reserved.
    
    @file: srecorder_dump_backtrace.h
    
    @brief: 进行内核堆栈回溯。
    
    @version: 1.0 
    
    @author: QiDechun ID: 216641
    
    @date: 2012-07-04
    
    @history:
*/

#ifndef SRECORDER_DUMP_BACKTRACE_H
#define SRECORDER_DUMP_BACKTRACE_H


/*----includes-----------------------------------------------------------------------*/

#include <asm/stacktrace.h>
#include "srecorder_common.h"


/*----c++ support--------------------------------------------------------------------*/

#ifdef __cplusplus
extern "C" {
#endif


/*----export macroes-----------------------------------------------------------------*/


/*----export prototypes---------------------------------------------------------------*/


/*----global variables-----------------------------------------------------------------*/


/*----export function prototypes--------------------------------------------------------*/

/**
    @function: void srecorder_dump_backtrace(srecorder_reserved_mem_info_for_log_t *pmem_info, 
        struct pt_regs *regs, struct task_struct *tsk)
    @brief: dump死机时内核的调用栈信息
    
    @param: pmem_info SRecorder的保留内存信息
    @param: regs cpu的寄存器状态
    @param: tsk 需要被dump调用栈的进程
    
    @return: none

    @note: 
*/
void srecorder_dump_backtrace(srecorder_reserved_mem_info_t *pmem_info, 
    struct pt_regs *regs, struct task_struct *tsk);


/**
    @function: int srecorder_unwind_frame(struct stackframe *frame)
    @brief: 进行栈帧检查和追溯
    
    @param: frame 待检查和追溯的栈帧
    
    @return: 0 - successfully, others - failed

    @note: 
*/
int srecorder_unwind_frame(struct stackframe *frame);


/**
    @function: int srecorder_unwind_frame(struct stackframe *frame)
    @brief: do backtrace
    
    @param: none
    
    @return: none

    @note: 
*/
asmlinkage void srecorder___backtrace(void);


/**
    @function: int srecorder_unwind_frame(struct stackframe *frame)
    @brief: do backtrace for ARM disconfig CONFIG_ARM_UNWIND 
    
    @param: fp frame pointer
    @param: pmode the mode of the processor
    
    @return: none

    @note: 
*/
asmlinkage void srecorder_c_backtrace(unsigned long fp, int pmode);


#ifdef __cplusplus
}
#endif
#endif /* SRECORDER_DUMP_BACKTRACE_H */

