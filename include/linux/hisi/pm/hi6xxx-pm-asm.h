/******************************************************************************

                  版权所有 (C), 2001-2011, 华为技术有限公司

 ******************************************************************************
  文 件 名   : pm_asm.h
  版 本 号   : 初稿
  作    者   : 王振伟 00176398
  生成日期   : 2014年3月26日
  最近修改   :
  功能描述   : 电源管理汇编代码头文件
  函数列表   :
  修改历史   :
  1.日    期   : 2014年3月26日
    作    者   : 王振伟 00176398
    修改内容   : 创建文件

******************************************************************************/
#define __SOC_H_FOR_ASM__
#include <linux/hisi/pm/pwrctrl_multi_memcfg.h>

#ifndef PM_ASM_H
#define PM_ASM_H


#define _ARM_FUNCTION_CALLED_FROM_C(a) \
    .globl a ;\
    .code  32 ;\
    .balign 4 ;\
a:

#define PM_ACPU_ASM_MEM_VADDR   (PWRCTRL_ACPU_ASM_CODE_BASE)
#define PM_ASM_CODE_COPY_OFFSET 0x40
#define PM_ASM_CORE_INFO_AREA_OFFSET        (0x64)

#define ACPU_GIC_DIST_BASE          (SOC_ACPU_GIC_BASE_ADDR + 0x1000)
#define ACPU_GIC_ICDISPR            (ACPU_GIC_DIST_BASE + 0x200)

#define ACPU_SLICE_ADDR (SOC_AO_SCTRL_BASE_ADDR + 0x890)
#endif
