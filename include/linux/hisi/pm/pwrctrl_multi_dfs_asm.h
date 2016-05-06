/******************************************************************************
修改以下文件需要保证下面文件的一致性：
hardware\libhardware\include\hardware\hisi\pwrctrl_multi_memcfg.h       ->vendor\hisi\modem\drv\hi6210\src\comm\inc\pwrctrl_multi_memcfg.h
hardware\libhardware\include\hardware\hisi\pwrctrl_multi_dfs_asm.h      ->vendor\hisi\modem\drv\hi6210\src\comm\inc\pwrctrl_multi_dfs_asm.h
hardware\libhardware\include\hardware\hisi\soc_baseaddr_interface.h     ->vendor\hisi\platform\hi6210sft\soc_baseaddr_interface.h
hardware\libhardware\include\hardware\hisi\global_ddr_map.h             ->vendor\hisi\config\product\include\hi6210sft\global_ddr_map.h
******************************************************************************/
#ifndef __PWRCTRL_MULTI_DFS_ASM_H__
#define __PWRCTRL_MULTI_DFS_ASM_H__

#define SLAVE_CORE_FIQ_NUM 0xF
#define ACPU_IDLE_READY_FLAG 0x5a
#define ACPU_DVFS_COMPLETE_FLAG 0x1
#define IPC2_NOSEC_INT_ACPU 0x5
#define IPC2_NOSEC_DVFS_INT_NUM 0x0
#define IPC2_NOSEC_DVFS_INT_CLEAR (0x1 << IPC2_NOSEC_DVFS_INT_NUM)

#define IPC2_NOSEC_ACPUWDT_INT_NUM 0x1
#define IPC2_NOSEC_ACPUWDT_INT_CLEAR (0x1 << IPC2_NOSEC_ACPUWDT_INT_NUM)

#define POLICY_VALID_MAGIC 0x12849176
#define SURPPORT_POLICY_NUM 15
#define INVALID_POLICY_NUM 0xFFFFFFFF

#define POLICY_HEAD_LEN (4)
#define POLICY_LEN (24)
#define MAX_PROFILE_NUM_CPU (7)
#define MAX_PROFILE_NUM_DDR (6)
#endif
