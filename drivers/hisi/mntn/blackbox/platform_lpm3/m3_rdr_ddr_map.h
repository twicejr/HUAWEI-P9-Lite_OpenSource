#ifndef __M3_RDR_DDR_MAP_H__
#define __M3_RDR_DDR_MAP_H__

/************************M3 RDR DDR SYSTEM CONTEXT*************************
 *注意: 1、如下文件必须完全保持一致
 *      vendor\hisi\confidential\lpmcu\include\m3_rdr_ddr_map.h
 *      kernel\drivers\hisi\mntn\blackbox\platform_lpm3\m3_rdr_ddr_map.h
 *      bootable\bootloader\legacy\drivers\mntn\m3_rdr_ddr_map.h
 *
 *      2、使用时，请先判断 M3_RDR_SYS_CONTEXT_BASE_ADDR 是否为NULL或0
 *
 *      3、kernel侧，地址为ioremap的虚拟地址
 *         legacy侧，为实际的ddr物理地址
 *         lpmcu侧，为实际的ddr物理地址
---------------------------------------------------------------------------
 0x00000 ~ 0x00100   sys context head                       (0x100)
 0x00100 ~ 0x00300   m3 core regs                           (0x200)
 0x00300 ~ 0x03F00   m3 nvic regs                           (0xF00*4=0x3C00)
 0x03F00 ~ 0x04400   m3 text logs                           (0x500)
 0x04400 ~ 0x04500   m3 private logs                        (0x100)
 0x04500 ~ 0x04900   peri ip regs (ddr, sysnoc, etc..)      (0x400)
 0x04900 ~ 0x04A00   run time var                           (0x100)
 0x04A00 ~ 0x05A00   lpmcu stat                             (0x1000)
 0x05A00 ~ 0x05C00   kernel stat                            (0x200)
 0x05C00 ~ 0x20000   reserved                               (0x1A400)
 0x20000 ~ 0x40000   m3 sys image                           (0x20000=128k)
--------------------------------------------------------------------------*/

/*注意: 使用时，请先判断 M3_RDR_SYS_CONTEXT_BASE_ADDR 是否为NULL或0*/
#if defined(__KERNEL__)
#if defined(CONFIG_HISI_LPMCU_BB)
extern char *g_lpmcu_rdr_ddr_addr;
#define M3_RDR_SYS_CONTEXT_BASE_ADDR						g_lpmcu_rdr_ddr_addr
#else
#define M3_RDR_SYS_CONTEXT_BASE_ADDR						(0)
#endif
#elif defined(__CMSIS_RTOS)
extern unsigned int g_lpmcu_rdr_ddr_addr;
#define M3_RDR_SYS_CONTEXT_BASE_ADDR						g_lpmcu_rdr_ddr_addr
#elif defined(FASTBOOT_MNTN)
extern unsigned long long g_lpmcu_rdr_ddr_addr;
#define M3_RDR_SYS_CONTEXT_BASE_ADDR						g_lpmcu_rdr_ddr_addr
#else
#define M3_RDR_SYS_CONTEXT_BASE_ADDR						(0)
#endif

#define M3_RDR_SYS_CONTEXT_SIZE								(0x40000)

#define M3_RDR_SYS_CONTEXT_RDR_MEM_MAP_INDEX_ADDR			(M3_RDR_SYS_CONTEXT_BASE_ADDR) /*0x0*/
#define M3_RDR_SYS_CONTEXT_RDR_MEM_MAP_INDEX_SIZE			(0x80)

#define M3_RDR_SYS_CONTEXT_EXC_SPECIAL_ADDR					(M3_RDR_SYS_CONTEXT_RDR_MEM_MAP_INDEX_ADDR + M3_RDR_SYS_CONTEXT_RDR_MEM_MAP_INDEX_SIZE)  /*0x80*/
#define M3_RDR_SYS_CONTEXT_EXC_SPECIAL_SIZE					(0x80)

#define M3_RDR_SYS_CONTEXT_HEAD_ADDR						(M3_RDR_SYS_CONTEXT_EXC_SPECIAL_ADDR + M3_RDR_SYS_CONTEXT_EXC_SPECIAL_SIZE)  /*0x100*/
#define M3_RDR_SYS_CONTEXT_HEAD_SIZE						(0x100)

#define M3_RDR_SYS_CONTEXT_M3_COREREG_ADDR					(M3_RDR_SYS_CONTEXT_HEAD_ADDR + M3_RDR_SYS_CONTEXT_HEAD_SIZE)  /*0x200*/
#define M3_RDR_SYS_CONTEXT_M3_COREREG_SIZE					(0x200)

#define M3_RDR_SYS_CONTEXT_M3_NVICREG_ADDR					(M3_RDR_SYS_CONTEXT_M3_COREREG_ADDR + M3_RDR_SYS_CONTEXT_M3_COREREG_SIZE) /*0x400*/
#define M3_RDR_SYS_CONTEXT_M3_NVICREG_SIZE					(0xF00*4)

#define M3_RDR_SYS_CONTEXT_M3_LOG_ADDR						(M3_RDR_SYS_CONTEXT_M3_NVICREG_ADDR+M3_RDR_SYS_CONTEXT_M3_NVICREG_SIZE)/*0x4000*/
#define M3_RDR_SYS_CONTEXT_M3_LOG_SIZE						(0x1000)

#define M3_RDR_SYS_CONTEXT_M3_PRIVATE_DATA_ADDR				(M3_RDR_SYS_CONTEXT_M3_LOG_ADDR+M3_RDR_SYS_CONTEXT_M3_LOG_SIZE)/*0x5000*/
#define M3_RDR_SYS_CONTEXT_M3_PRIVATE_DATA_SIZE				(0x400)

#define M3_RDR_SYS_CONTEXT_PERI_IPREG_ADDR					(M3_RDR_SYS_CONTEXT_M3_PRIVATE_DATA_ADDR + M3_RDR_SYS_CONTEXT_M3_PRIVATE_DATA_SIZE)/*0x5400*/
#define M3_RDR_SYS_CONTEXT_PERI_IPREG_SIZE					(0x400)

#define M3_RDR_SYS_CONTEXT_RUNTIME_VAR_ADDR					(M3_RDR_SYS_CONTEXT_PERI_IPREG_ADDR + M3_RDR_SYS_CONTEXT_PERI_IPREG_SIZE)/*0x5800*/
#define M3_RDR_SYS_CONTEXT_RUNTIME_VAR_SIZE					(0x100)

#define M3_RDR_SYS_CONTEXT_LPMCU_STAT_ADDR					(M3_RDR_SYS_CONTEXT_RUNTIME_VAR_ADDR+M3_RDR_SYS_CONTEXT_RUNTIME_VAR_SIZE)/*0x5900*/
#define M3_RDR_SYS_CONTEXT_LPMCU_STAT_SIZE					(0x1000)

#define M3_RDR_SYS_CONTEXT_KERNEL_STAT_ADDR					(M3_RDR_SYS_CONTEXT_LPMCU_STAT_ADDR+M3_RDR_SYS_CONTEXT_LPMCU_STAT_SIZE)/*0x6900*/
#define M3_RDR_SYS_CONTEXT_KERNEL_STAT_SIZE					(0x200)

#define M3_RDR_SYS_CONTEXT_EXPOSE_STORAGE_ADDR				(M3_RDR_SYS_CONTEXT_KERNEL_STAT_ADDR+M3_RDR_SYS_CONTEXT_KERNEL_STAT_SIZE)/*0x6B00*/
#define M3_RDR_SYS_CONTEXT_EXPOSE_STORAGE_SIZE				(0xC00)

#define M3_RDR_SYS_CONTEXT_NOC_REG_ADDR						(M3_RDR_SYS_CONTEXT_EXPOSE_STORAGE_ADDR+M3_RDR_SYS_CONTEXT_EXPOSE_STORAGE_SIZE)/*0x7700*/
#define M3_RDR_SYS_CONTEXT_NOC_REG_SIZE						(0x200)

#define M3_RDR_SYS_CONTEXT_RUNTIME_EXPOSE_STORAGE_ADDR		(M3_RDR_SYS_CONTEXT_NOC_REG_ADDR+M3_RDR_SYS_CONTEXT_NOC_REG_SIZE)/*0x7900*/
#define M3_RDR_SYS_CONTEXT_RUNTIME_EXPOSE_STORAGE_SIZE		(0x400)

#define M3_RDR_SYS_CONTEXT_MODEM_DATA_ADDR					(M3_RDR_SYS_CONTEXT_RUNTIME_EXPOSE_STORAGE_ADDR+M3_RDR_SYS_CONTEXT_RUNTIME_EXPOSE_STORAGE_SIZE)/*0x7D00*/
#define M3_RDR_SYS_CONTEXT_MODEM_DATA_SIZE					(0x400)

#define M3_RDR_CRG_PERI_ADDR								(M3_RDR_SYS_CONTEXT_MODEM_DATA_ADDR + M3_RDR_SYS_CONTEXT_MODEM_DATA_SIZE)/*0x8100*/
#define M3_RDR_CRG_PERI_SIZE								(0xE20)

#define M3_RDR_SCTRL_ADDR									(M3_RDR_CRG_PERI_ADDR + M3_RDR_CRG_PERI_SIZE)/*0x8F20*/
#define M3_RDR_SCTRL_SIZE									(0xE00)

#define M3_RDR_PMCTRL_ADDR									(M3_RDR_SCTRL_ADDR + M3_RDR_SCTRL_SIZE)/*0x9D20*/
#define M3_RDR_PMCTRL_SIZE									(0x480)

#define M3_RDR_PCTRL_ADDR									(M3_RDR_PMCTRL_ADDR + M3_RDR_PMCTRL_SIZE)/*0xA1A0*/
#define M3_RDR_PCTRL_SIZE									(0xC20)

#define M3_RDR_SYS_CONTEXT_IOMCU_REG_ADDR					(M3_RDR_PCTRL_ADDR+M3_RDR_PCTRL_SIZE)/*0xADC0*/
#define M3_RDR_SYS_CONTEXT_IOMCU_REG_SIZE					(0x100)

#define M3_RDR_DDR_REG_ADDR								(M3_RDR_SYS_CONTEXT_IOMCU_REG_ADDR + M3_RDR_SYS_CONTEXT_IOMCU_REG_SIZE)/*0xAEC0*/
#define M3_RDR_DDR_REG_SIZE									(0xC00)

#define M3_RDR_PMU_REG_ADDR									(M3_RDR_DDR_REG_ADDR + M3_RDR_DDR_REG_SIZE)/*0xBAC0*/
#define M3_RDR_PMU_REG_SIZE									(0x20)

#define M3_RDR_SYS_CONTEXT_RESERVED_ADDR				(M3_RDR_PMU_REG_ADDR + M3_RDR_PMU_REG_SIZE)

#if	((M3_RDR_SYS_CONTEXT_RESERVED_ADDR) > (M3_RDR_SYS_CONTEXT_BASE_ADDR+0x20000))
#error	"rdr space overflow! please reorganize the rdr space"
#endif

/* m3 sysimage at the last 128K */
#define M3_RDR_SYS_CONTEXT_M3_IMAGE_ADDR					(M3_RDR_SYS_CONTEXT_BASE_ADDR+0x20000)         /* sys img offset 0x20000 */
#define M3_RDR_SYS_CONTEXT_M3_IMAGE_SIZE					(0x20000)



#endif /* __M3_RDR_DDR_MAP_H__ */
