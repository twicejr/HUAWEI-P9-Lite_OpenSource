/**
 * @file SRE_buildef.h
 *
 * Copyright(C), 2008-2050, Huawei Tech. Co., Ltd. ALL RIGHTS RESERVED. \n
 *
 * 描述：定义硬件平台的编译宏。 \n
 */

#ifndef _SRE_BUILDEF_H
#define _SRE_BUILDEF_H


#ifdef __cplusplus
#if __cplusplus
extern "C" {
#endif /* __cpluscplus */
#endif /* __cpluscplus */

/**
* 小字节序。
*/
#define OS_LITTLE_ENDIAN                                    0x1234

/**
* 大字节序。
*/
#define OS_BIG_ENDIAN                                       0x4321

/* To define OS_HARDWARE_PLATFORM */
#define OS_C64X                                             0x0
#define OS_C64XPLUS                                         0x1
#define OS_SC3400                                           0x2
#define OS_XTENSA2                                          0x3
#define OS_SC3850                                           0x4
#define OS_RISC170                                          0x5
#define OS_DSP170                                           0x6
#define OS_RISC220                                          0x7
#define OS_DSP220                                           0x8
#define OS_HACCC                                            0x9
#define OS_CORTEX_AX                                        0xa
#define OS_CORTEX_MX                                        0xb
#define OS_HI1210                                           0xc
#define OS_HIDSP                                            0xd

/* To define OS_CPU_TYPE */
#define OS_TI6482                                           0x0
#define OS_LSI2603                                          0x1
#define OS_MSC8144                                          0x2
#define OS_SD6153                                           0x3
#define OS_TI6487                                           0x4
#define OS_GBDSP                                            0x5
#define OS_MSC8156                                          0x6
#define OS_SD6108                                           0x7
#define OS_SD6181                                           0x8
#define OS_SD6182                                           0x9
#define OS_CORTEX_A9                                        0xa
#define OS_STM32F407                                        0xb
#define OS_CORTEX_A7                                        0xc
#define OS_SD6183                                           0xd
#define OS_SD6157                                           0xe

#ifndef OS_HARDWARE_PLATFORM
#define OS_HARDWARE_PLATFORM                                OS_CORTEX_AX
#endif

#if (defined (CHIP_BB_HI6758) || defined (CHIP_BB_HI6210))
#ifndef OS_CPU_TYPE
#define OS_CPU_TYPE                                         OS_CORTEX_A7
#endif
#else
#ifndef OS_CPU_TYPE
#define OS_CPU_TYPE                                         OS_CORTEX_A9
#endif
#endif
#ifndef OS_BYTE_ORDER
#define OS_BYTE_ORDER                                       OS_LITTLE_ENDIAN
#endif


#define LOW                                                 (1)
#define HIGH                                                (2)

/*
配置芯片最大的核数。用于初始化时指定waitforallcores的数组长度。
此后内存模块初始化完成，之后均使用用户配置的启动核数来配置核相关数组长度。
*/
#define OS_MAX_CORE_NUM                                     1

/*OS是否支持多核功能*/
#define OS_MULTI_CORE                                       NO

/*OS是否支持协处理器*/
#define OS_OPTION_COPROCESSOR                               NO

/*OS是否支持DCACHE*/
#define OS_OPTION_DCACHE                                    YES

/*tick中断是否由用户创建和接管*/
#define OS_OPTION_TICK_USR_MNG                              NO

/*是否由OS提供cycle计数*/
#define OS_OPTION_SYS_CYCLE                                 NO

/*OS是否支持从可cache分区中申请不可cache内存*/
#define OS_OPTION_MEM_UNCACHE_ALLOC                         YES

/*任务栈监控是否支持软件方式*/
#define OS_OPTION_STACK_MON_SOFT                            YES

/*OS是否支持重设同步MSGM的参数*/
#define OS_OPTION_MSGM_SYN_PARA_RESET                       NO

/*OS是否支持查询同步MSGM的使能状态*/
#define OS_OPTION_MSGM_SYN_STATE_GET                        NO

/*OS是否支持信号量递归PV操作*/
#define OS_OPTION_SEM_RECUR_PV                              YES

/*OS是否支持LP同步信息获取操作*/
#define OS_OPTION_LP_SYN_INFO_GET                           NO

/*OS是否支持LP单核复位功能*/
#define OS_OPTION_LP_CORE_RESET                             NO

/*OS是否支持系统级CPUP*/
#define OS_OPTION_CPUP_SYS                                  YES

/*OS是否支持线程级CPUP*/
#define OS_OPTION_CPUP_THREAD                               YES

/*OS是否支持CPUP告警*/
#define OS_OPTION_CPUP_WARN                                 YES

/*实例间初始化阶段*/
#define OS_OPTION_INIT_PHASE_QUERY                          NO

/*OS是否支持clib库*/
#define OS_OPTION_LIBC                                      YES

/*OS是否支持IO接口*/
#define OS_OPTION_IO_INTF                                   YES

/*OS是否支持INIT TRACE打印功能*/
#define OS_OPTION_PRINT_INIT_TRACE_INFO                     YES

/*OS是否支持ssc内存算法*/
#define OS_OPTION_SSC_MEM                                   NO

/*HUNT是否使用实例间共享内存*/
#define OS_OPTION_HUNT_INST_SHARE_MEM                       NO

/*OS是否支持消息内存回收*/
#define OS_OPTION_MSG_MEM_RECLAIM                           NO

/*OS是否支持直接模式硬件信号量*/
#define OS_OPTION_HWSEM_DIRECT                              NO

/*OS是否支持硬件信号量的单核复位--HWSEM DELETE*/
#define OS_OPTION_HWSEM_CORE_RESET                          NO

/*OS是否支持核间信号量回收*/
#define OS_OPTION_MCSEM_RECLAIM                             NO

/*OS是否支持HUNT 内存回收*/
#define OS_OPTION_HUNT_MEM_RECLAIM                          NO

/*OS是否支持共享静态fsc内存释放*/
#define OS_OPTION_MCSTA_FSCMEM_FREE                         NO

/*OS是否支持msgm资源由用户管理*/
#define OS_OPTION_MSGM_USR_MNG                              NO

/*OS是否支持任务监控功能*/
#define OS_OPTION_TASK_MON                                  YES

/*OS是否支持系统跟踪功能*/
#define OS_OPTION_TRACE                                     YES

/*OS是否支持有名空间功能*/
#define OS_OPTION_NSM                                       NO

/*OS是否支持事件功能*/
#define OS_OPTION_EVENT                                     YES

/*OS是否支持队列功能*/
#define OS_OPTION_QUEUE                                     YES

/*OS使用的安全C库函数等级,
  NO   --未使用,
  LOW  --仅使用实心函数,
  HIGH --使用实心和空心函数*/
#define OS_OPTION_SEC_C_LEVEL                               HIGH

/*OS是否支持消息白名单*/
#define OS_OPTION_MSG_WHITE_LIST                            NO

/*OS是否支持内核态进程*/
#define OS_OPTION_KERNEL_PROCESS                            NO

/*OS是否支持用户态进程*/
#define OS_OPTION_USR_PROCESS                               NO

/*OS是否支持软中断*/
#define OS_OPTION_SWI                                       YES

/*OS是否支持快速信号量*/
#define OS_OPTION_FSEM                                      YES

/*OS是否支持异常接管*/
#define OS_OPTION_EXC                                       YES

/*OS是否支持任务栈监控*/
#define OS_OPTION_STACK_MON                                 YES

/*OS是否支持核休眠*/
#define OS_OPTION_CORESLEEP                                 YES

/*OS是否支持符号表按生效核查找*/
#define OS_OPTION_SYMBOL_COREBITMAP                         NO

/*OS是否支持BM_SRE*/
#define OS_OPTION_BM_SRE                                    NO
/*OS是否支持log上报*/
#define OS_OPTION_LOG_REPORT                               NO
/* 各个核定制的Write error interrupt中断号OS_EXC_WRITE_ERROR_INTERRUPT,
   等后续其他核都支持该中断之后，再可以在这里填入，
   并将sre_exc_init.c中引用该宏处的#if删除 */
#define OS_EXC_WRITE_ERROR_INTERRUPT                        9

/****************************** 任务模块 ****************************/
/**
 * CORTEX_A9(Balong C核) 平台任务共支持64个优先级，分别为0-63。0表示最高优先级，63表示最低优先级。
 * IDLE任务使用此优先级(63)，用户应不创建此优先级的任务。
 */
#define OS_TSK_PRIORITY_HIGHEST                             0
#define OS_TSK_PRIORITY_LOWEST                              63
/**
*  CORTEX_A9 平台任务支持的优先级数64。
*/
#define OS_TSK_NUM_OF_PRIORITIES                            64

#ifdef DEBUG
#define OS_DEBUG
#endif

#ifndef _WIN32
/* 定义操作系统的代码数据分段 */
/*指示函数为inlne类型*/
#ifndef OS_SEC_ALW_INLINE
#define OS_SEC_ALW_INLINE           __attribute__((always_inline))
#endif

#ifndef OS_SEC_TEXT
#define OS_SEC_TEXT                 __attribute__((section(".os.text")))
#endif

#ifndef OS_KERNEL_TEXT
#define OS_KERNEL_TEXT              __attribute__((section(".os.kernel.text")))
#endif

#ifndef OS_SEC_TEXT_MINOR
#define OS_SEC_TEXT_MINOR           __attribute__((section(".os.minor.text")))
#endif

#ifndef OS_SEC_TEXT_MONITOR
#define OS_SEC_TEXT_MONITOR         __attribute__((section(".os.monitor.text")))
#endif

#ifndef OS_SEC_TEXT_INIT
#define OS_SEC_TEXT_INIT            __attribute__((section(".os.init.text")))
#endif

#ifndef OS_SEC_TEXT_NONCACHE
#define OS_SEC_TEXT_NONCACHE
#endif

#ifndef OS_SEC_DATA
#define OS_SEC_DATA                 __attribute__((section(".os.data")))
#endif

#ifndef OS_SEC_DATA_SHARED
#define OS_SEC_DATA_SHARED          __attribute__((section(".os.data")))
#endif

#ifndef OS_SEC_DATA_INIT
#define OS_SEC_DATA_INIT            __attribute__((section(".os.data")))
#endif

#ifndef OS_SEC_PRI_DATA_HSHELL
#define OS_SEC_PRI_DATA_HSHELL      __attribute__((section(".os.hshell.pri.data")))
#endif

#ifndef OS_SEC_BSS
#define OS_SEC_BSS                  __attribute__((section(".os.bss, \"aw\", %nobits@")))
#endif

#ifndef OS_SEC_BSS_SHARED
#define OS_SEC_BSS_SHARED           __attribute__((section(".os.bss, \"aw\", %nobits@")))
#endif

#ifndef OS_SEC_BSS_INIT
#define OS_SEC_BSS_INIT             __attribute__((section(".os.bss, \"aw\", %nobits@")))
#endif

#ifndef OS_SEC_BSS_BACK
#define OS_SEC_BSS_BACK             __attribute__((section(".os.bss, \"aw\", %nobits@")))
#endif

#ifndef OS_SEC_TEXT_HSHELL
#define OS_SEC_TEXT_HSHELL          __attribute__((section(".os.hshell.text")))
#endif

#ifndef OS_SEC_DATA_HSHELL
#define OS_SEC_DATA_HSHELL          __attribute__((section(".os.hshell.data")))
#endif

#ifndef OS_SEC_BSS_HSHELL
#define OS_SEC_BSS_HSHELL           __attribute__((section(".os.hshell.bss, \"aw\", %nobits@")))
#endif

#ifndef OS_SEC_BSS_HSHELL_SVR
#define OS_SEC_BSS_HSHELL_SVR       __attribute__((section(".os.hshell.svr.bss, \"aw\", %nobits@")))
#endif

#ifndef OS_SEC_DATA_SYMBOL
#define OS_SEC_DATA_SYMBOL          __attribute__((section(".os.symbol.data")))
#endif

/* Hi1380 nocache data */
#ifndef OS_SEC_NC_DATA_SHARED
#define OS_SEC_NC_DATA_SHARED
#endif

/* Hi1380 nocache bss */
#ifndef OS_SEC_NC_BSS_SHARED
#define OS_SEC_NC_BSS_SHARED
#endif

/* Hi1380 test data */
#ifndef OS_SEC_TEST_DATA_SHARED
#define OS_SEC_TEST_DATA_SHARED
#endif

#ifndef PAT_SEC_DATA_SHARED
#define PAT_SEC_DATA_SHARED     __attribute__((section(".os.mcpatch.data")))
#endif

#ifndef PAT_SEC_BSS_SHARED
#define PAT_SEC_BSS_SHARED      __attribute__((section(".os.mcpatch.bss, \"aw\", %nobits@")))
#endif
#ifndef OS_SEC_BSS_INSTANCE_SHARED
#define OS_SEC_BSS_INSTANCE_SHARED   __attribute__((section(".os.over.inst.shared.bss, \"aw\", %nobits@")))
#endif
#define EXTERN_FAR extern

#define PACK1
#else
/*指示函数为inlne类型*/
#ifndef OS_SEC_ALW_INLINE
#define OS_SEC_ALW_INLINE
#endif

#ifndef OS_SEC_TEXT
#define OS_SEC_TEXT
#endif

#ifndef OS_KERNEL_TEXT
#define OS_KERNEL_TEXT
#endif

#ifndef OS_SEC_TEXT_MINOR
#define OS_SEC_TEXT_MINOR
#endif

#ifndef OS_SEC_TEXT_MONITOR
#define OS_SEC_TEXT_MONITOR
#endif

#ifndef OS_SEC_TEXT_INIT
#define OS_SEC_TEXT_INIT
#endif

#ifndef OS_SEC_TEXT_NONCACHE
#define OS_SEC_TEXT_NONCACHE
#endif

#ifndef OS_SEC_DATA
#define OS_SEC_DATA
#endif

#ifndef OS_SEC_DATA_SHARED
#define OS_SEC_DATA_SHARED
#endif

#ifndef OS_SEC_DATA_INIT
#define OS_SEC_DATA_INIT
#endif

#ifndef OS_SEC_PRI_DATA_HSHELL
#define OS_SEC_PRI_DATA_HSHELL
#endif

#ifndef OS_SEC_BSS
#define OS_SEC_BSS
#endif

#ifndef OS_SEC_BSS_SHARED
#define OS_SEC_BSS_SHARED
#endif

#ifndef OS_SEC_BSS_INIT
#define OS_SEC_BSS_INIT
#endif

#ifndef OS_SEC_BSS_BACK
#define OS_SEC_BSS_BACK
#endif

#ifndef OS_SEC_TEXT_HSHELL
#define OS_SEC_TEXT_HSHELL
#endif

#ifndef OS_SEC_DATA_HSHELL
#define OS_SEC_DATA_HSHELL
#endif

#ifndef OS_SEC_BSS_HSHELL
#define OS_SEC_BSS_HSHELL
#endif

#ifndef OS_SEC_BSS_HSHELL_SVR
#define OS_SEC_BSS_HSHELL_SVR
#endif

#ifndef OS_SEC_DATA_SYMBOL
#define OS_SEC_DATA_SYMBOL
#endif

/* Hi1380 nocache data */
#ifndef OS_SEC_NC_DATA_SHARED
#define OS_SEC_NC_DATA_SHARED
#endif

/* Hi1380 nocache bss */
#ifndef OS_SEC_NC_BSS_SHARED
#define OS_SEC_NC_BSS_SHARED
#endif

/* Hi1380 test data */
#ifndef OS_SEC_TEST_DATA_SHARED
#define OS_SEC_TEST_DATA_SHARED
#endif

#ifndef PAT_SEC_DATA_SHARED
#define PAT_SEC_DATA_SHARED
#endif

#ifndef PAT_SEC_BSS_SHARED
#define PAT_SEC_BSS_SHARED
#endif

#ifndef OS_SEC_BSS_INSTANCE_SHARED
#define OS_SEC_BSS_INSTANCE_SHARED
#endif
#define EXTERN_FAR extern

#define PACK1
#endif

#ifdef __cplusplus
#if __cplusplus
}
#endif /* __cpluscplus */
#endif /* __cpluscplus */


#endif /* _SRE_BUILDEF_H */



