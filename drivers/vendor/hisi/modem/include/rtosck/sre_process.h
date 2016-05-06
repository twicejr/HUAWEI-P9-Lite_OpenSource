/*--------------------------------------------------------------------------------------------------------------------------*/
/*!!Warning: This is a key information asset of Huawei Tech Co.,Ltd                                                         */
/*CODEMARK:kOyQZYzjDpyGdBAEC2GaWrXNs8MZYk9cpFfgXfKX0g1VVtQNxHnHCKsK8caFMiW8LvCCkwIW
Tc6iJlHGFi3nUeJwZnaqeEUBwq/bzU5cp8JMIZQR60CPwhsVGkig7D46L1mTcjaBXLwtoHt/
6v3Dah1fIWJ0QzaviBugQMTxyfdBxnyOas2YfpGASpq0YvtHfmHX7l8QwPfHpzP7j4EeXHMT
USc3qHiOuJ4gPVgZD1CGUi+Lkp5wZHTl1P4cpX3nmPzE0A11ZIZrF2sLrogADQ==*/
/*--------------------------------------------------------------------------------------------------------------------------*/
/**
 * @file sre_process.h
 *
 * Copyright(C), 2008-2050, Huawei Tech. Co., Ltd. ALL RIGHTS RESERVED. \n
 *
 * 描述：进程模块的对外头文件。 \n
 */

 /**@defgroup SRE_process 进程基本功能
  *@ingroup SRE_kernel
 */

#ifndef _SRE_PROCESS_H
#define _SRE_PROCESS_H

#include "sre_base.h"

#ifdef __cplusplus
#if __cplusplus
extern "C" {
#endif /* __cpluscplus */
#endif /* __cpluscplus */

#if (OS_OPTION_KERNEL_PROCESS == YES) 

/**
 * @ingroup SRE_procss
 * 进程PID。
 *
 * 进程PID非法 
 */
#define OS_PROCESS_NULL_ID                                      0xFFFFFFFF


/**
 * @ingroup SRE_process
 * 进程最低优先级
 *
 * 
 */
#define OS_PROCESS_PRIORITY_LOWEST                              0x0000


/*
 * 进程模块的错误码定义。
 */
/**
 * @ingroup SRE_process
 * 进程错误码：申请内存失败。
 *
 * 值: 0x02003000
 *
 * 解决方案: 分配更大的私有FSC内存分区
 *
 */
#define OS_ERRNO_PROCESS_NO_MEMORY                          SRE_ERRNO_OS_ERROR(OS_MID_PROCESS, 0x00)

/**
 * @ingroup SRE_process
 * 进程错误码：进程创建或删除时入参指针参数为空或地址值为空。
 *
 * 值: 0x02003001
 *
 * 解决方案: 检查参数指针或地址是否为NULL。
 */
#define OS_ERRNO_PROCESS_PTR_NULL                           SRE_ERRNO_OS_ERROR(OS_MID_PROCESS, 0x01)

/**
 * @ingroup SRE_process
 * 进程错误码：用户进程栈大小未按16字节大小对齐。
 *
 * 值: 0x02003002
 *
 * 解决方案: 检查入参用户进程栈大小是否按16字节对齐。
 */
#define OS_ERRNO_PROCESS_STKSZ_NOT_ALIGN                    SRE_ERRNO_OS_ERROR(OS_MID_PROCESS, 0x02)

/**
 * @ingroup SRE_process
 * 进程错误码：用户配置的进程用户栈首地址未16字节对齐。
 *
 * 值: 0x02003003
 *
 * 解决方案: 配置进来进程用户栈首地址需16字节对齐。
 */
#define OS_ERRNO_PROCESS_STACKADDR_NOT_ALIGN                SRE_ERRNO_OS_ERROR(OS_MID_PROCESS, 0x03)


/**
 * @ingroup SRE_process
 * 进程错误码：进程名的指针为空或进程名为空字符串。
 *
 * 值: 0x02003004
 *
 * 解决方案: 检查进程名指针和进程名。
 */
#define OS_ERRNO_PROCESS_NAME_EMPTY                         SRE_ERRNO_OS_ERROR(OS_MID_PROCESS, 0x04)


/**
 * @ingroup SRE_process
 * 进程错误码：配置的进程数量太多，最多15个，不包括内核进程且不能为0。
 *
 * 值: 0x02003005
 *
 * 解决方案: 进程配置项中将最大用户进程数改为小于等于15个且大于0。
 */
#define OS_ERRNO_PROCESS_MAX_NUM_NOT_SUITED                 SRE_ERRNO_OS_ERROR(OS_MID_PROCESS, 0x05)

/**
 * @ingroup SRE_process
 * 进程错误码：进程配置项中配置的页表地址或长度非法
 *
 * 值: 0x02003006
 *
 * 解决方案: 请确保配置项中页表地址不能为0，而且页表长度不能为0。
 */
#define OS_ERRNO_PROCESS_PAGE_TBL_CFG_INVALID               SRE_ERRNO_OS_ERROR(OS_MID_PROCESS, 0x06)

/**
 * @ingroup SRE_process
 * 进程错误码：配置进程页表基地址未按0x4000字节(16K)大小对齐。
 *
 * 值: 0x02003007
 *
 * 解决方案: 检查配置项中页表基地址是否按0x4000字节大小对齐。
 */
#define OS_ERRNO_PROCESS_PAGE_TBL_ADDR_NOT_ALIGN            SRE_ERRNO_OS_ERROR(OS_MID_PROCESS, 0x07)

/**
 * @ingroup SRE_process
 * 进程错误码：配置项中的进程页表大小未按0x400字节(1K)大小对齐。
 *
 * 值: 0x02003008
 *
 * 解决方案: 进程配置项中页表大小至少按0x400字节(1K)大小对齐。
 */
#define OS_ERRNO_PROCESS_PAGE_TBL_ADDR_SIZE_NOT_ALIGN       SRE_ERRNO_OS_ERROR(OS_MID_PROCESS, 0x08)

/**
 * @ingroup SRE_process
 * 进程错误码：配置项中的进程页表大小配置过小。
 *
 * 值: 0x02003009
 *
 * 解决方案: 进程配置项中页表大小OS_PROCESS_PAGE_TABLE_SIZE不小于(1K + OS_PROCESS_MAX_SUPPORT_NUM * 16K)。
 */
#define OS_ERRNO_PROCESS_PAGE_TBL_SIZE_TOO_SMALL            SRE_ERRNO_OS_ERROR(OS_MID_PROCESS, 0x09)

/**
 * @ingroup SRE_process
 * 进程错误码: 用户进程创建时用户进程ELF文件头错误。
 *
 * 值: 0x0200300a
 *
 *解决方案:检查用户进程的ELF文件是否有问题。
 */
#define OS_ERRNO_PROCESS_ELF_HEAD_ERROR                     SRE_ERRNO_OS_ERROR(OS_MID_PROCESS, 0x0a)

/**
 * @ingroup SRE_process
 * 进程错误码: 用户进程LP文件类型错误。
 *
 * 值: 0x0200300b
 *
 *解决方案:检查SD6183平台是否使用了HIDSP编译器编译的用户进程可执行文件。
 */
#define OS_ERRNO_PROCESS_ELF_FILETYPE_ERROR                 SRE_ERRNO_OS_ERROR(OS_MID_PROCESS, 0x0b)

/**
 * @ingroup SRE_process
 * 进程错误码: 用户进程加载时ELF段表头错误。
 *
 * 值: 0x0200300c
 *
 *解决方案:检查加载的用户进程ELF文件是否有问题。
 */
#define OS_ERRNO_PROCESS_ELF_SEC_HEAD_ERROR                 SRE_ERRNO_OS_ERROR(OS_MID_PROCESS, 0x0c)

/**
 * @ingroup SRE_process
 * 进程错误码: 用户进程加载时ELF文件段信息校验错误。
 *
 * 值: 0x0200300d
 *
 *解决方案:检查加载的用户进程ELF文件是否有问题。
 */
#define OS_ERRNO_PROCESS_ELF_SEC_NUM_ERROR                  SRE_ERRNO_OS_ERROR(OS_MID_PROCESS, 0x0d)

/**
 * @ingroup SRE_process
 * 进程错误码: 用户进程加载时ELF文件节区个数错误。。
 *
 * 值: 0x0200300e
 *
 *解决方案:ELF的段个数不能为0，请确认用户进程的可执行文件是否正确性。
 */
#define OS_ERRNO_PROCESS_SEC_NUM_ADDR_ERROR                 SRE_ERRNO_OS_ERROR(OS_MID_PROCESS, 0x0e)

/**
 * @ingroup SRE_process
 * 进程错误码: 用户进程文件的ELF段对齐错误。
 *
 * 值: 0x0200300f
 *
 *解决方案:查看用户进程ELF文件是否有问题。
 */
#define OS_ERRNO_PROCESS_SEC_ALIGN_ERROR                    SRE_ERRNO_OS_ERROR(OS_MID_PROCESS, 0x0f)

/**
 * @ingroup SRE_process
 * 进程错误码: 用户进程可执行文件段属性错误。
 *
 * 值: 0x02003010
 *
 *解决方案:检查用户进程ELF文件是否有问题。
 */
#define OS_ERRNO_PROCESS_SECTION_FLAG_ERROR                 SRE_ERRNO_OS_ERROR(OS_MID_PROCESS, 0x10)

/**
 * @ingroup SRE_process
 * 进程错误码: 用户进程创建时配置的段区名字为空。
 *
 * 值: 0x02003011
 *
 *解决方案:用户进程创建时配置的段区名字不能为空。
 */
#define OS_ERRNO_PROCESS_CFG_SEC_NAME_INVALID               SRE_ERRNO_OS_ERROR(OS_MID_PROCESS, 0x11)

/**
 * @ingroup SRE_process
 * 进程错误码: 用户进程加载时二级页表内存不够。
 *
 * 值: 0x02003012
 *
 * 解决方案: 请在进程配置项中扩大页表空间大小。
 */
#define OS_ERRNO_PROCESS_MMU_SIZE_ERROR                     SRE_ERRNO_OS_ERROR(OS_MID_PROCESS, 0x12)

/**
 * @ingroup SRE_process
 * 进程错误码: 用户进程创建时配置的进程段个数为0或者进程段区地址为空。
 *
 * 值: 0x02003013
 *
 *解决方案:用户进程创建时配置的段区数不能为0及进程段区地址不能为空。
 */
#define OS_ERRNO_PROCESS_SECAREAINFO_IS_NULL                SRE_ERRNO_OS_ERROR(OS_MID_PROCESS, 0x13)

/**
 * @ingroup SRE_process
 * 进程错误码: 用户进程创建时配置的进程段名存在相同。
 *
 * 值: 0x02003014
 *
 *解决方案:修改相同的段名为不同段名。
 */
#define OS_ERRNO_PROCESS_SEC_NAME_SAME                      SRE_ERRNO_OS_ERROR(OS_MID_PROCESS, 0x14)

/**
 * @ingroup SRE_process
 *  进程错误码：用户进程创建时配置的进程段中存在虚拟地址重叠。
 *
 * 值: 0x02003015
 *
 * 解决方案: 确保各段配置中虚拟地址不重叠。
 */
#define OS_ERRNO_PROCESS_SEC_AREA_OVERLAY_IN_VIR_ADDR       SRE_ERRNO_OS_ERROR(OS_MID_PROCESS, 0x15)

/**
 * @ingroup SRE_process
 * 进程错误码: 用户进程创建加载时传入的缓冲区地址(uwExeAddr)非4字节对齐。
 *
 * 值: 0x02003016
 *
 *解决方案:保证入参缓冲区地址(uwExeAddr)4字节对齐。
 */
#define OS_ERRNO_PROCESS_BUF_ADDR_NOT_ALIGN                 SRE_ERRNO_OS_ERROR(OS_MID_PROCESS, 0x16) 

/**
 * @ingroup SRE_process
 * 进程错误码: 用户进程创建时缓冲区长度不够，或者缓冲区长度为0，请检查入参是否正确。
 *
 * 值: 0x02003017
 *
 *解决方案:查看输入的缓冲区长度。
 */
#define OS_ERRNO_PROCESS_BUF_NOT_ENOUGH                     SRE_ERRNO_OS_ERROR(OS_MID_PROCESS, 0x17) 

/**
 * @ingroup SRE_process
 * 进程错误码: 用户进程创建时配置的进程用户栈大小为0。
 *
 * 值: 0x02003018
 *
 *解决方案:查看进程用户栈配置大小是否为0。
 */
#define OS_ERRNO_PROCESS_STKSZ_IS_ZERO                      SRE_ERRNO_OS_ERROR(OS_MID_PROCESS, 0x18) 

/**
 * @ingroup SRE_process
 * 进程错误码: 用户进程创建时配置的进程用户栈地址为空。
 *
 * 值: 0x02003019
 *
 *解决方案:查看进程用户栈配置地址是否为NULL。
 */
#define OS_ERRNO_PROCESS_STACKADDR_IS_NULL                  SRE_ERRNO_OS_ERROR(OS_MID_PROCESS, 0x19) 

/**
 * @ingroup SRE_process
 * 进程错误码: 用户进程创建时找不能空闲的进程注册信息块。
 *
 * 值: 0x0200301a
 *
 *解决方案:检查当前创建的用户进程数是否已经超过用户配置的最大进程数(OS_PROCESS_MAX_SUPPORT_NUM)。
 */
#define OS_ERRNO_PROCESS_REG_NOT_FIND_IDLE_BLOCK            SRE_ERRNO_OS_ERROR(OS_MID_PROCESS, 0x1a) 

/**
 * @ingroup SRE_process
 * 任务错误码：进程ID非法。
 *
 * 值: 0x0200301b
 *
 * 解决方案: 检查当前运行进程的PID是否超过配置的进程最大数或检查用户入参进程PID是否合法。
 */
#define OS_ERRNO_PROCESS_ID_INVALID                         SRE_ERRNO_OS_ERROR(OS_MID_PROCESS, 0x1b)

/**
 * @ingroup SRE_process
 * 任务错误码：进程没有创建。
 *
 * 值: 0x0200301c
 *
 * 解决方案: 检查当前PID指定的进程是否已经被创建过。
 */
#define OS_ERRNO_PROCESS_NOT_CREATED                        SRE_ERRNO_OS_ERROR(OS_MID_PROCESS, 0x1c)


/**
 * @ingroup SRE_process
 * 进程ID的类型定义。
 */
typedef UINT32                                              PROCESS_HANDLE_T;

/**
 * @ingroup SRE_process
 * 进程优先级的类型定义。
 */
typedef UINT16                                              PROCESS_PRIOR_T;


/**
 * @ingroup SRE_process
 * 进程模块配置信息的结构体定义。
 *
 * 保存进程模块的配置项信息。
 */
typedef struct tagProcessModInfo
{
    UINT32 uwMaxNum;                       /**< 最大支持的进程数           */
    UINT32 uwPTblAddr;                     /**< 用户进程页表配置基地址(16k对齐)*/    
    UINT32 uwPTblsize;                     /**< 用户进程页表配置大小(16k对齐)*/  
} PROCESS_MOD_INFO_S;

/**
 * @ingroup SRE_process
 * 进程模块配置信息中配置段的结构体定义。
 *
 * 进程创建时。
 */
typedef struct tagProcessSection
{
    CHAR * pcSecName;                      /**< 用户进程的段名         */
    UINT32 uwSecVA;                        /**< 用户进程的段虚拟地址   */
    UINT32 uwSecPA;                        /**< 用户进程的段物理地址   */
    UINT32 uwSecSize;                      /**< 用户进程的段大小       */
    UINT32 uwSecAttr;                      /**< 用户进程的段属性       */
}PROCESS_SECTION_S; 

/**
 * @ingroup SRE_process
 * 进程创建参数的结构体定义。
 *
 * 传递进程创建时指定的参数信息。
 */
typedef struct tagProcessParam
{
    CHAR * pcProcessName;                   /**< 进程名                     */
    PROCESS_PRIOR_T usProcessPrio;          /**< 进程优先级                 */
    UINT16 usPreserved;                     /**< 预留                       */
    UINT32 uwInitCnt;                       /**< 进程时间片初始计数值(Tick值的整数倍)*/
    UINT32 uwUsrStackAddr;                  /**< 进程用户栈地址             */
    UINT32 uwUsrStackSize;                  /**< 进程用户栈大小             */
    UINT32 uwVMID;                          /**< 用户进程的VMID             */
    UINT32 uwSecNum;                        /**< 用户进程段区个数           */
    PROCESS_SECTION_S *pstProcessSection;   /**< 用户进程段区地址空间       */
} PROCESS_PARA_S;

/**
 * @ingroup  SRE_process
 * @brief 创建进程。
 *
 * @par 描述:
 * 创建一个进程。
 * 系统初始化后创建的进程，如果优先级高于当前进程且未锁进程，则立即发生进程调度并被运行，否则加入就绪队列。
 *
 * @attention
 * <ul>
 * <li>创建进程时消息队列数默认为1个，不需要配置。</li>
 * <li>进程名的最大长度为16字节，含结束符。</li>
 * <li>同一核内进程名不允许重复，且不允许和软中断重名。</li>
 * <li>进程栈的大小必须按16字节大小对齐。确定进程栈大小的原则是，够用就行：多了浪费，少了进程栈溢出。具体多少取决于需要消耗多少的栈内存，视情况而定：函数调用层次越深，栈内存开销越大，局部数组越大，局部变量越多，栈内存开销也越大。</li>
 * <li>用户配置的进程栈空间需由用户保证其合法性，即对可cache空间的地址用户需要保证其进程栈首地址及栈大小cache line对齐，系统不做对齐处理，并在使用后需由用户进行释放。</li>
 * </ul>
 *
 * @param  puwProcessPID [OUT] 类型#UINT32 *，保存进程PID。
 * @param  pstInitParam [IN] 类型#PROCESS_PARA_S *，进程创建参数，其结构体中的成员参数uwStackAddr传入时必须进行初始化，若不采用用户配置的独立进程栈进行栈空间分配，该成员必须初始化为0。
 *
 * @retval #OS_ERRNO_PROCESS_NO_MEMORY              0x02002f00，申请内存失败。
 * @retval #OS_ERRNO_PROCESS_PTR_NULL               0x02002f01，指针参数为空。
 * @retval #OS_ERRNO_PROCESS_STKSZ_NOT_ALIGN        0x02002f02，进程栈大小未按16字节大小对齐。
 * @retval #OS_ERRNO_PROCESS_NAME_EMPTY             0x02002f04，进程名的指针为空或进程名为空字符串。
 * @retval #OS_ERRNO_PROCESS_ID_INVALID             0x02002f1b，进程PID非法。
 * @retval #OS_ERRNO_PROCESS_STACKADDR_NOT_ALIGN    0x02002f03，创建进程时，用户配置进程栈地址未16字节对齐。
 * @retval #SRE_OK                                  0x00000000，进程创建成功。
 * @par 依赖:
 * <ul><li>sre_process.h：该接口声明所在的头文件。</li></ul>
 * @since RTOSck V100R003C00
 * @see SRE_ProcessDelete | SRE_ProcessCreateOnly
 */
extern UINT32 SRE_ProcessCreate(PROCESS_HANDLE_T *puwProcessPID, UINT32 uwExeAddr, UINT32 uwSize, PROCESS_PARA_S *pstProcessPara);


/**
 * @ingroup  SRE_process
 * @brief 创建进程，但不激活进程。
 *
 * @par 描述:
 * 创建一个进程。该进程不加入就绪队列，只处于挂起状态，用户需要激活该进程需要通过调用SRE_ProcessResume函数将其激活。
 *
 * @attention
 * <ul>
 * <li>进程名的最大长度为16字节，含结束符。</li>
 * <li>创建进程时消息队列数默认为1个，不需要配置。</li>
 * <li>同一核内进程名不允许重复。</li>
 * <li>进程栈的大小必须按16字节大小对齐。确定进程栈大小的原则是，够用就行：多了浪费，少了进程栈溢出。具体多少取决于需要消耗多少的栈内存，视情况而定：函数调用层次越深，栈内存开销越大，局部数组越大，局部变量越多，栈内存开销也越大。</li>
 * <li>用户配置的进程栈首地址需16字节对齐，且配置的进程栈空间中，os会使用消息队列数*消息队列控制块的内存大小。</li>
 * <li>用户配置的进程栈空间需由用户保证其合法性，即对可cache空间的地址用户需要保证其进程栈首地址及栈大小cache line对齐，系统不做对齐处理，并在使用后需由用户进行释放。</li>
 * </ul>
 *
 * @param  puwProcessPID [OUT] 类型#UINT32 *，保存进程PID。
 * @param  pstInitParam [IN] 类型#PROCESS_PARA_S *，进程创建参数，其结构体中的成员参数uwStackAddr传入时必须进行初始化，若不采用用户配置的独立进程栈进行栈空间分配，该成员必须初始化为0。
 *
 * @retval #OS_ERRNO_PROCESS_NO_MEMORY              0x02002f00，申请内存失败。
 * @retval #OS_ERRNO_PROCESS_PTR_NULL               0x02002f01，指针参数为空。
 * @retval #OS_ERRNO_PROCESS_STKSZ_NOT_ALIGN        0x02002f02，进程栈大小未按16字节大小对齐。
 * @retval #OS_ERRNO_PROCESS_NAME_EMPTY             0x02002f04，进程名的指针为空或进程名为空字符串。
 * @retval #OS_ERRNO_PROCESS_ID_INVALID             0x02002f1b，进程PID非法。
 * @retval #OS_ERRNO_PROCESS_STACKADDR_NOT_ALIGN    0x02002f03，创建进程时，用户配置进程栈地址未16字节对齐.
 * @retval #SRE_OK                                  0x00000000，进程创建成功。
 * @par 依赖:
 * <ul><li>sre_process.h：该接口声明所在的头文件。</li></ul>
 * @since RTOSck V100R003C00
 * @see SRE_ProcessDelete | SRE_ProcessCreate
 */
extern UINT32 SRE_ProcessCreateOnly(PROCESS_HANDLE_T *puwProcessPID, UINT32 uwExeAddr, UINT32 uwSize, PROCESS_PARA_S *pstProcessPara);


/**
 * @ingroup  SRE_process
 * @brief 恢复进程。
 *
 * @par 描述:
 * 恢复挂起的进程。
 *
 * @attention
 * <ul>
 * <li>在osStart之前不能调用该接口。</li>
 * <li>若进程仍处于延时、阻塞态，则只是取消挂起态，并不加入就绪队列。</li>
 * </ul>
 *
 * @param  uwProcessPID [IN] 类型#UINT32，进程PID。
 *
 * @retval #OS_ERRNO_PROCESS_ID_INVALID         0x02002f1b，进程PID非法。
 * @retval #OS_ERRNO_PROCESS_NOT_CREATED        0x02002f1c，进程没有被创建。
 * @retval #SRE_OK                              0x00000000，恢复进程成功。
 * @par 依赖:
 * <ul><li>sre_process.h：该接口声明所在的头文件。</li></ul>
 * @since RTOSck V100R003C00
 * @see SRE_ProcessSuspend
 */
extern UINT32 SRE_ProcessResume(PROCESS_HANDLE_T uwProcessPID);


/**
 * @ingroup  SRE_process
 * @brief 挂起进程。
 *
 * @par 描述:
 * 挂起指定的进程，进程将从就绪队列中被删除。
 *
 * @attention
 * <ul>
 * <li>若为当前进程且已锁进程，则不能被挂起。</li>
 * </ul>
 *
 * @param  uwProcessPID [IN] 类型#UINT32，进程PID。
 *
 * @retval #OS_ERRNO_PROCESS_ID_INVALID             0x02002f1b，进程PID非法。
 * @retval #OS_ERRNO_PROCESS_NOT_CREATED            0x02002f1c，进程没有被创建。
 * @retval #SRE_OK                                  0x00000000，挂起进程成功。
 * @par 依赖:
 * <ul><li>sre_process.h：该接口声明所在的头文件。</li></ul>
 * @since  RTOSck V100R003C00
 * @see SRE_ProcessResume | SRE_ProcessLock
 */
extern UINT32 SRE_ProcessSuspend(PROCESS_HANDLE_T uwProcessPID);


/**
 * @ingroup  SRE_task
 * @brief 删除进程。
 *
 * @par 描述:
 * 删除指定的进程，释放进程栈和进程控制块资源。
 *
 * @attention
 * <ul>
 * <li> </li>
 * </ul>
 *
 * @param  uwProcessPID [IN] 类型#UINT32，进程PID。
 *
 * @retval #OS_ERRNO_PROCESS_ID_INVALID             0x02002f1b，进程PID非法。
 * @retval #OS_ERRNO_PROCESS_NOT_CREATED            0x02002f1c，进程没有被创建。
 * @retval #SRE_OK                                  0x00000000，删除进程成功。
 * @par 依赖:
 * <ul><li>sre_process.h：该接口声明所在的头文件。</li></ul>
 * @since RTOSck V100R003C00
 * @see SRE_ProcessCreate
 */
//extern UINT32 SRE_ProcessDelete(PROCESS_HANDLE_T uwProcessPID, PROCESS_PARA_S *pstProcessPara);
extern UINT32 SRE_ProcessDelete(PROCESS_HANDLE_T uwProcessPID);

/**
 * @ingroup  SRE_process
 * @brief 锁进程调度。
 *
 * @par 描述:
 * 锁进程调度。若进程调度被锁，则不发生进程切换。
 *
 * @attention
 * <ul>
 * <li>只是锁进程调度，并不关中断，因此进程仍可被中断打断。</li>
 * <li>执行此函数则锁计数值加1，解锁则锁计数值减1。因此，必须与#SRE_processUnlock配对使用。</li>
 * </ul>
 *
 * @param  无
 *
 * @retval 无
 * @par 依赖:
 * <ul><li>sre_process.h：该接口声明所在的头文件。</li></ul>
 * @since RTOSck V100R003C00
 * @see SRE_ProcessUnlock
 */
extern VOID SRE_ProcessLock(VOID);


/**
 * @ingroup  SRE_process
 * @brief 解锁进程调度。
 *
 * @par 描述:
 * 进程锁计数值减1。若嵌套加锁，则只有锁计数值减为0才真正的解锁了进程调度。
 *
 * @attention
 * <ul>
 * <li>在osStart之前不能调用该接口。</li>
 * <li>执行此函数则锁计数值加1，解锁则锁计数值减1。因此，必须与#SRE_processLock配对使用。</li>
 * </ul>
 *
 * @param  无
 *
 * @retval 无
 * @par 依赖:
 * <ul><li>sre_process.h：该接口声明所在的头文件。</li></ul>
 * @since RTOSck V100R003C00
 * @see SRE_processLock
 */
extern VOID SRE_ProcessUnlock(VOID);

#endif


#ifdef __cplusplus
#if __cplusplus
}
#endif /* __cpluscplus */
#endif /* __cpluscplus */


#endif /* _SRE_PROCESS_H */

/**
 * History:
 * 2008-02-20 l66919: Create this file.
 *
 * vi: set expandtab ts=4 sw=4 tw=80:
 */

