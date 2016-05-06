#include <product_config.h>
#include <mdrv_public.h>
#include <mdrv_memory.h>
#include <mdrv_misc_comm.h>
#include <mdrv_int_comm.h>
#include <mdrv_errno.h>
#include <bsp_om.h>
#include <bsp_dump.h>
#include <bsp_dump_drv.h>
#include <bsp_om_enum.h>
#include <bsp_shared_ddr.h>
#include <bsp_sram.h>
#include <bsp_om.h>

#define hwadp_printf(fmt,...)   (bsp_trace(BSP_LOG_LEVEL_ERROR,BSP_MODU_HWADP,fmt,##__VA_ARGS__))

#define SRAM_USB_ASHELL_ADDR             (void *)(&(((SRAM_SMALL_SECTIONS*)((unsigned long)SRAM_BASE_ADDR + SRAM_OFFSET_SMALL_SECTIONS))->SRAM_USB_ASHELL))
#define SRAM_UART_INFO_ADDR              (void *)(((SRAM_SMALL_SECTIONS*)((unsigned long)SRAM_BASE_ADDR + SRAM_OFFSET_SMALL_SECTIONS))->UART_INFORMATION)
#define MEMORY_AXI_DICC_ADDR             (void *)((((SRAM_SMALL_SECTIONS*)((unsigned long)SRAM_BASE_ADDR + SRAM_OFFSET_SMALL_SECTIONS))->SRAM_DICC))
#define SRAM_DSP_DRV_ADDR                (void *)(&(((SRAM_SMALL_SECTIONS*)((unsigned long)SRAM_BASE_ADDR + SRAM_OFFSET_SMALL_SECTIONS))->SRAM_DSP_DRV))
#define SRAM_PCIE_INFO_ADDR              (void *)(((SRAM_SMALL_SECTIONS*)((unsigned long)SRAM_BASE_ADDR + SRAM_OFFSET_SMALL_SECTIONS))->SRAM_PCIE_INFO)
#define SRAM_SEC_ROOTCA_ADDR             (void *)(((SRAM_SMALL_SECTIONS*)((unsigned long)SRAM_BASE_ADDR + SRAM_OFFSET_SMALL_SECTIONS))->SRAM_SEC_ROOTCA)
#define SRAM_WDT_AM_FLAG_ADDR            (void *)(&(((SRAM_SMALL_SECTIONS*)((unsigned long)SRAM_BASE_ADDR + SRAM_OFFSET_SMALL_SECTIONS))->SRAM_WDT_AM_FLAG))
#define SRAM_WDT_CM_FLAG_ADDR            (void *)(&(((SRAM_SMALL_SECTIONS*)((unsigned long)SRAM_BASE_ADDR + SRAM_OFFSET_SMALL_SECTIONS))->SRAM_WDT_CM_FLAG))
#define SRAM_BUCK3_ACORE_ONOFF_FLAG_ADDR (void *)(&(((SRAM_SMALL_SECTIONS*)((unsigned long)SRAM_BASE_ADDR + SRAM_OFFSET_SMALL_SECTIONS))->SRAM_BUCK3_ACORE_ONOFF_FLAG))
#define SRAM_BUCK3_CCORE_ONOFF_FLAG_ADDR (void *)(&(((SRAM_SMALL_SECTIONS*)((unsigned long)SRAM_BASE_ADDR + SRAM_OFFSET_SMALL_SECTIONS))->SRAM_BUCK3_CCORE_ONOFF_FLAG))
#define SRAM_CUR_CPUFREQ_PROFILE_ADDR    (void *)(&(((SRAM_SMALL_SECTIONS*)((unsigned long)SRAM_BASE_ADDR + SRAM_OFFSET_SMALL_SECTIONS))->SRAM_CUR_CPUFREQ_PROFILE))
#define SRAM_MAX_CPUFREQ_PROFILE_ADDR    (void *)(&(((SRAM_SMALL_SECTIONS*)((unsigned long)SRAM_BASE_ADDR + SRAM_OFFSET_SMALL_SECTIONS))->SRAM_MAX_CPUFREQ_PROFILE))
#define SRAM_MIN_CPUFREQ_PROFILE_ADDR    (void *)(&(((SRAM_SMALL_SECTIONS*)((unsigned long)SRAM_BASE_ADDR + SRAM_OFFSET_SMALL_SECTIONS))->SRAM_MIN_CPUFREQ_PROFILE))
#define SRAM_REBOOT_ADDR                 (void *)(((SRAM_SMALL_SECTIONS*)((unsigned long)SRAM_BASE_ADDR + SRAM_OFFSET_SMALL_SECTIONS))->SRAM_REBOOT_INFO)
#define SRAM_TEMP_PROTECT_ADDR           (void *)(((SRAM_SMALL_SECTIONS*)((unsigned long)SRAM_BASE_ADDR + SRAM_OFFSET_SMALL_SECTIONS))->SRAM_TEMP_PROTECT)
#define SRAM_DLOAD_ADDR                  (void *)(((SRAM_SMALL_SECTIONS*)((unsigned long)SRAM_BASE_ADDR + SRAM_OFFSET_SMALL_SECTIONS))->SRAM_DLOAD)
#define SRAM_SEC_SHARE                   (void *)(&(((SRAM_SMALL_SECTIONS*)((unsigned long)SRAM_BASE_ADDR + SRAM_OFFSET_SMALL_SECTIONS))->SRAM_SEC_SHARE))
#define SRAM_DSP_MNTN_INFO_ADDR          (void *)((((SRAM_SMALL_SECTIONS*)((unsigned long)SRAM_BASE_ADDR + SRAM_OFFSET_SMALL_SECTIONS))->SRAM_DSP_MNTN_INFO))
#define SRAM_DFS_DDRC_CFG_ADDR           (void *)(((SRAM_SMALL_SECTIONS*)((unsigned long)SRAM_BASE_ADDR + SRAM_OFFSET_SMALL_SECTIONS))->SRAM_DFS_DDRC_CFG)
#define SRAM_DUMP_POWER_OFF_FLAG_ADDR    (void *)(&((SRAM_SMALL_SECTIONS*)((unsigned long)SRAM_BASE_ADDR + SRAM_OFFSET_SMALL_SECTIONS))->SRAM_DUMP_POWER_OFF_FLAG)
#define SRAM_PM_CHECK_ADDR               (void *)(&((SRAM_SMALL_SECTIONS*)((unsigned long)SRAM_BASE_ADDR + SRAM_OFFSET_SMALL_SECTIONS))->SRAM_PM_CHECK_ADDR)
#define SRAM_CDSP_MNTN_INFO_ADDR          (void *)((((SRAM_SMALL_SECTIONS*)((unsigned long)SRAM_BASE_ADDR + SRAM_OFFSET_SMALL_SECTIONS))->SRAM_CDSP_MNTN_INFO))
#define SRAM_CDSP_DRV_ADDR                (void *)(&(((SRAM_SMALL_SECTIONS*)((unsigned long)SRAM_BASE_ADDR + SRAM_OFFSET_SMALL_SECTIONS))->SRAM_CDSP_DRV))


extern BSP_DDR_SECT_INFO_S g_ddr_info[BSP_DDR_SECT_TYPE_BUTTOM];

/*****************************************************************************
 函 数 名  : bsp_show_ip_addr
 功能描述  : 打印IP基地址信息
 输入参数  : 无
 输出参数  : 无
 返回值    ：无
*****************************************************************************/
int bsp_show_ip_addr(void)
{
    unsigned int i;

    for(i = 0; i < BSP_IP_TYPE_BUTTOM; i++)
    {
        hwadp_printf("ip_addr[%d] = 0x%p\n", i, mdrv_misc_get_ip_baseaddr((BSP_IP_TYPE_E)i));
    }
    return 0;
}

/*****************************************************************************
 函 数 名  : bsp_show_irq_num
 功能描述  : 打印中断信息
 输入参数  : 无
 输出参数  : 无
 返回值    ：无
*****************************************************************************/
int bsp_show_irq_num(void)
{
    unsigned int i;

    for(i = 0; i < BSP_INT_TYPE_BUTTOM; i++)
    {
        hwadp_printf("irq_num[%d] = 0x%X\n", i, mdrv_int_get_num(i));
    }
    return 0;
}

/*****************************************************************************
 函 数 名  : BSP_DDR_ShowSectInfo
 功能描述  : 打印DDR内存段信息
 输入参数  : 无
 输出参数  : 无
 返回值    ：无
*****************************************************************************/
int BSP_DDR_ShowSectInfo(void)
{
    BSP_DDR_SECT_TYPE_E     enSectTypeIndex = (BSP_DDR_SECT_TYPE_E)0;

    hwadp_printf("\ntype       paddr      vaddr      size       attr\n");
    for(; enSectTypeIndex < BSP_DDR_SECT_TYPE_BUTTOM; enSectTypeIndex++)
    {
          hwadp_printf("0x%-8.8x 0x%8p 0x%8p 0x%-8.8x 0x%-8.8x\n", \
          g_ddr_info[enSectTypeIndex].enSectType, \
          g_ddr_info[enSectTypeIndex].pSectPhysAddr, \
          g_ddr_info[enSectTypeIndex].pSectVirtAddr, \
          g_ddr_info[enSectTypeIndex].ulSectSize, \
          g_ddr_info[enSectTypeIndex].enSectAttr);
    }
    return 0;
}

int show_meminfo(void)
{
	int i = 0;

	for(; i < (int)BSP_DDR_TYPE_BUTTOM; i++)
	{
		unsigned int addr = 0, size = 0;
		(void)mdrv_getmeminfo((BSP_DDR_TYPE_E)i,&addr, &size);
		hwadp_printf("BSP_DDR_TYPE_E:%X  addr:%X   size:%X\n", i, addr, size);
	}
	return 0;
}

int show_axi_addr(void)
{
	int i = 0;

	for(; i < (int)BSP_AXI_SECT_TYPE_BUTTOM; i++)
	{
		BSP_AXI_SECT_INFO_S pstSectInfo = {NULL, NULL, BSP_AXI_SECT_TYPE_BUTTOM, 0};
		(void)mdrv_get_fix_axi_addr((BSP_AXI_SECT_TYPE_E)i, &pstSectInfo);
		hwadp_printf("axi-type:%X  vadd:%X  paddr:%X  size:%X\n",
			pstSectInfo.enSectType,
			pstSectInfo.pSectVirtAddr,
			pstSectInfo.pSectPhysAddr,
			pstSectInfo.ulSectSize);
	}
	return 0;
}

/*****************************************************************************
 函 数 名  : show_global_ddr_status
 功能描述  : DDR内存段信息打印
 输入参数  : 无
 输出参数  : 无
 返回值    ：无
*****************************************************************************/
int show_global_ddr_status(void)
{
    hwadp_printf("%-30s%10s%10s\t\n", "name", "phy addr", "size");
    hwadp_printf("%-30s%10x%10x\n", "DDR_APP_ACP_ADDR", DDR_APP_ACP_ADDR, DDR_APP_ACP_SIZE);
    hwadp_printf("%-30s%10x%10x\n", "DDR_ACORE_ADDR", DDR_ACORE_ADDR, DDR_ACORE_SIZE);
#ifdef DDR_ACORE_DTS_ADDR
    hwadp_printf("%-30s%10x%10x\n", "DDR_ACORE_DTS_ADDR", DDR_ACORE_DTS_ADDR, DDR_ACORE_DTS_SIZE);
#endif
    hwadp_printf("%-30s%10x%10x\n", "DDR_MCORE_ADDR", DDR_MCORE_ADDR, DDR_MCORE_SIZE);
#ifdef DDR_MCORE_DTS_ADDR
    hwadp_printf("%-30s%10x%10x\n", "DDR_MCORE_DTS_ADDR", DDR_MCORE_DTS_ADDR, DDR_MCORE_DTS_SIZE);
#endif
    hwadp_printf("%-30s%10p%10x\n", "DDR_SHARED_MEM_ADDR", g_mem_ctrl.sddr_phy_addr, g_mem_ctrl.sddr_mem_size);
    hwadp_printf("%-30s%10x%10x\n", "DDR_MNTN_ADDR", DDR_MNTN_ADDR, DDR_MNTN_SIZE);
    //hwadp_printf("%-30s%10p%10x\n", "DDR_GU_ADDR", g_gu_ctrl.addr_phy, g_gu_ctrl.mem_size);
    hwadp_printf("%-30s%10x%10x\n", "DDR_TLPHY_IMAGE_ADDR", DDR_TLPHY_IMAGE_ADDR, DDR_TLPHY_IMAGE_SIZE);
    hwadp_printf("%-30s%10x%10x\n", "DDR_LPHY_SDR_ADDR", DDR_LPHY_SDR_ADDR, DDR_LPHY_SDR_SIZE);
    hwadp_printf("%-30s%10x%10x\n", "DDR_SOCP_ADDR", DDR_SOCP_ADDR, DDR_SOCP_SIZE);
    hwadp_printf("%-30s%10x%10x\n", "DDR_LCS_ADDR", DDR_LCS_ADDR, DDR_LCS_SIZE);
    hwadp_printf("%-30s%10x%10x\n", "DDR_HIFI_ADDR", DDR_HIFI_ADDR, DDR_HIFI_SIZE);
    hwadp_printf("%-30s%10x%10x\n", "DDR_MDM_ACP_ADDR", DDR_MDM_ACP_ADDR, DDR_MDM_ACP_SIZE);
#ifdef DDR_SECURE_OS_ADDR
    hwadp_printf("%-30s%10x%10x\n", "DDR_SECURE_OS_ADDR", DDR_SECURE_OS_ADDR, DDR_SECURE_OS_SIZE);
#endif

	return 0;
}

/*****************************************************************************
 函 数 名  : show_sram_status
 功能描述  : SRAM内存段信息打印
 输入参数  : 无
 输出参数  : 无
 返回值    ：无
*****************************************************************************/
int show_sram_status(void)
{
    /*请依照先后顺序增加打印输出项*/
    int total_size = SRAM_SIZE_SMALL_SECTIONS + SRAM_SIZE_MCU_RESERVE + SRAM_SIZE_ICC + SRAM_SIZE_TLDSP_SHARED +
                     SRAM_SIZE_GU_MAC_HEADER;/*lint !e569 */
    hwadp_printf("%-30s%10s%10s%10s\n", "name", "phy addr", "virt addr", "size");
    hwadp_printf("%-30s%10p%10lx%10x\n", "SRAM_SMALL_SECTIONS_ADDR", SRAM_V2P((unsigned long)SRAM_BASE_ADDR + SRAM_OFFSET_SMALL_SECTIONS),(unsigned long)SRAM_BASE_ADDR + SRAM_OFFSET_SMALL_SECTIONS, SRAM_SIZE_SMALL_SECTIONS);/*lint !e778 */
    hwadp_printf("%-30s%10p%10lx%10x\n", "SRAM_MCU_RESERVE_ADDR", SRAM_V2P((unsigned long)SRAM_BASE_ADDR + SRAM_OFFSET_MCU_RESERVE),(unsigned long)SRAM_BASE_ADDR + SRAM_OFFSET_MCU_RESERVE, SRAM_SIZE_MCU_RESERVE);
    hwadp_printf("%-30s%10p%10lx%10x\n", "SRAM_ADDR_ICC", SRAM_V2P((unsigned long)SRAM_BASE_ADDR + SRAM_OFFSET_ICC),(unsigned long)SRAM_BASE_ADDR + SRAM_OFFSET_ICC, SRAM_SIZE_ICC);
    hwadp_printf("%-30s%10p%10lx%10x\n", "SRAM_TLDSP_SHARED_ADDR", SRAM_V2P((unsigned long)SRAM_BASE_ADDR + SRAM_OFFSET_TLDSP_SHARED),(unsigned long)SRAM_BASE_ADDR + SRAM_OFFSET_TLDSP_SHARED, SRAM_SIZE_TLDSP_SHARED);
    hwadp_printf("%-30s%10p%10lx%10x\n", "SRAM_GU_MAC_HEADER_ADDR", SRAM_V2P((unsigned long)SRAM_BASE_ADDR + SRAM_OFFSET_GU_MAC_HEADER), (unsigned long)SRAM_BASE_ADDR + SRAM_OFFSET_GU_MAC_HEADER, SRAM_SIZE_GU_MAC_HEADER);
    hwadp_printf("%-30s%10p%10lx%10lx\n", "SRAM_DYNAMIC_SEC_ADDR", SRAM_V2P((unsigned long)SRAM_BASE_ADDR + SRAM_OFFSET_DYNAMIC_SEC), (unsigned long)SRAM_BASE_ADDR + SRAM_OFFSET_DYNAMIC_SEC, SRAM_SIZE_DYNAMIC_SEC);
    hwadp_printf("total size: 0x%x\n", total_size);
    hwadp_printf("detailed info of SRAM_SMALL_SECTIONS_ADDR: \n");
    hwadp_printf("%-30s%10p%10p\n", "SRAM_USB_ASHELL_ADDR", SRAM_V2P(SRAM_USB_ASHELL_ADDR), SRAM_USB_ASHELL_ADDR);
    hwadp_printf("%-30s%10p%10p\n", "SRAM_UART_INFO_ADDR", SRAM_V2P(SRAM_UART_INFO_ADDR), SRAM_UART_INFO_ADDR);
    hwadp_printf("%-30s%10p%10p\n", "MEMORY_AXI_DICC_ADDR", SRAM_V2P(MEMORY_AXI_DICC_ADDR), MEMORY_AXI_DICC_ADDR);
    hwadp_printf("%-30s%10p%10p\n", "SRAM_DSP_DRV_ADDR", SRAM_V2P(SRAM_DSP_DRV_ADDR), SRAM_DSP_DRV_ADDR);
    hwadp_printf("%-30s%10p%10p\n", "SRAM_PCIE_INFO_ADDR", SRAM_V2P(SRAM_PCIE_INFO_ADDR), SRAM_PCIE_INFO_ADDR);
    hwadp_printf("%-30s%10p%10p\n", "SRAM_SEC_ROOTCA_ADDR", SRAM_V2P(SRAM_SEC_ROOTCA_ADDR), SRAM_SEC_ROOTCA_ADDR);
    hwadp_printf("%-30s%10p%10p\n", "SRAM_WDT_AM_FLAG_ADDR", SRAM_V2P(SRAM_WDT_AM_FLAG_ADDR), SRAM_WDT_AM_FLAG_ADDR);
    hwadp_printf("%-30s%10p%10p\n", "SRAM_WDT_CM_FLAG_ADDR", SRAM_V2P(SRAM_WDT_CM_FLAG_ADDR), SRAM_WDT_CM_FLAG_ADDR);
    hwadp_printf("%-30s%10p%10p\n", "SRAM_BUCK3_ACORE_ONOFF_FLAG_ADDR", SRAM_V2P(SRAM_BUCK3_ACORE_ONOFF_FLAG_ADDR), SRAM_BUCK3_ACORE_ONOFF_FLAG_ADDR);
    hwadp_printf("%-30s%10p%10p\n", "SRAM_BUCK3_CCORE_ONOFF_FLAG_ADDR", SRAM_V2P(SRAM_BUCK3_CCORE_ONOFF_FLAG_ADDR), SRAM_BUCK3_CCORE_ONOFF_FLAG_ADDR);
    hwadp_printf("%-30s%10p%10p\n", "SRAM_CUR_CPUFREQ_PROFILE_ADDR", SRAM_V2P(SRAM_CUR_CPUFREQ_PROFILE_ADDR), SRAM_CUR_CPUFREQ_PROFILE_ADDR);
    hwadp_printf("%-30s%10p%10p\n", "SRAM_MAX_CPUFREQ_PROFILE_ADDR", SRAM_V2P(SRAM_MAX_CPUFREQ_PROFILE_ADDR), SRAM_MAX_CPUFREQ_PROFILE_ADDR);
    hwadp_printf("%-30s%10p%10p\n", "SRAM_MIN_CPUFREQ_PROFILE_ADDR", SRAM_V2P(SRAM_MIN_CPUFREQ_PROFILE_ADDR), SRAM_MIN_CPUFREQ_PROFILE_ADDR);
    hwadp_printf("%-30s%10p%10p\n", "SRAM_REBOOT_ADDR", SRAM_V2P(SRAM_REBOOT_ADDR), SRAM_REBOOT_ADDR);
    hwadp_printf("%-30s%10p%10p\n", "SRAM_TEMP_PROTECT_ADDR", SRAM_V2P(SRAM_TEMP_PROTECT_ADDR), SRAM_TEMP_PROTECT_ADDR);
    hwadp_printf("%-30s%10p%10p\n", "SRAM_DLOAD_ADDR", SRAM_V2P(SRAM_DLOAD_ADDR), SRAM_DLOAD_ADDR);
    hwadp_printf("%-30s%10p%10p\n", "SRAM_SEC_SHARE", SRAM_V2P(SRAM_SEC_SHARE), SRAM_SEC_SHARE);
    hwadp_printf("%-30s%10p%10p\n", "SRAM_DSP_MNTN_INFO", SRAM_V2P(SRAM_DSP_MNTN_INFO_ADDR), SRAM_DSP_MNTN_INFO_ADDR);
    hwadp_printf("%-30s%10p%10p\n", "SRAM_DFS_DDRC_CFG_ADDR", SRAM_V2P(SRAM_DFS_DDRC_CFG_ADDR), SRAM_DFS_DDRC_CFG_ADDR);
    hwadp_printf("%-30s%10p%10p\n", "SRAM_DUMP_POWER_OFF_FLAG_ADDR", SRAM_V2P(SRAM_DUMP_POWER_OFF_FLAG_ADDR), SRAM_DUMP_POWER_OFF_FLAG_ADDR);
    hwadp_printf("%-30s%10p%10p\n", "SRAM_PM_CHECK_ADDR", SRAM_V2P(SRAM_PM_CHECK_ADDR), SRAM_PM_CHECK_ADDR);
    hwadp_printf("%-30s%10p%10p\n", "SRAM_CDSP_DRV_ADDR", SRAM_V2P(SRAM_CDSP_DRV_ADDR), SRAM_CDSP_DRV_ADDR);
    hwadp_printf("%-30s%10p%10p\n", "SRAM_CDSP_MNTN_INFO_ADDR", SRAM_V2P(SRAM_CDSP_MNTN_INFO_ADDR), SRAM_CDSP_MNTN_INFO_ADDR);
	return 0;
}

/*****************************************************************************
 函 数 名  : show_shared_ddr_status
 功能描述  : 共享内存内存段信息打印
 输入参数  : 无
 输出参数  : 无
 返回值    ：无
*****************************************************************************/
int show_shared_ddr_status(void)
{
    /*请依照先后顺序增加打印输出项*/
    int total_size = SHM_SIZE_HIFI_MBX + SHM_SIZE_HIFI + SHM_SIZE_TLPHY + SHM_SIZE_TEMPERATURE
                   + SHM_SIZE_DDM_LOAD + SHM_SIZE_MEM_APPA9_PM_BOOT + SHM_SIZE_MEM_MDMA9_PM_BOOT
                   + SHM_SIZE_TENCILICA_MULT_BAND + SHM_SIZE_ICC + SHM_SIZE_IPF + SHM_SIZE_PSAM + SHM_SIZE_WAN
                   + SHM_SIZE_NV + SHM_SIZE_M3_MNTN + SHM_SIZE_TIMESTAMP + SHM_SIZE_IOS
                   + SHM_SIZE_RESTORE_AXI + SHM_SIZE_PMU + SHM_SIZE_PTABLE + SHM_SIZE_CCORE_RESET
                   +SHM_SIZE_PM_OM + SHM_SIZE_M3PM + SHM_SIZE_SLICE_MEM+SHM_SIZE_M3RSRACC_BD;
    hwadp_printf("%-30s%10s%10s%10s\n", "name", "phy addr", "virt addr", "size");
    hwadp_printf("%-30s%10p%10lx%10x\n", "SHM_SIZE_HIFI_MBX", SHD_DDR_V2P((unsigned long)SHM_BASE_ADDR+SHM_OFFSET_HIFI_MBX), (unsigned long)SHM_BASE_ADDR+SHM_OFFSET_HIFI_MBX, SHM_SIZE_HIFI_MBX);
    hwadp_printf("%-30s%10p%10lx%10x\n", "SHM_SIZE_HIFI", SHD_DDR_V2P((unsigned long)SHM_BASE_ADDR+SHM_OFFSET_HIFI), (unsigned long)SHM_BASE_ADDR+SHM_OFFSET_HIFI, SHM_SIZE_HIFI);
    hwadp_printf("%-30s%10p%10lx%10x\n", "SHM_SIZE_TLPHY", SHD_DDR_V2P((unsigned long)SHM_BASE_ADDR+SHM_OFFSET_TLPHY), (unsigned long)SHM_BASE_ADDR+SHM_OFFSET_TLPHY, SHM_SIZE_TLPHY);
    hwadp_printf("%-30s%10p%10lx%10x\n", "SHM_SIZE_TEMPERATURE", SHD_DDR_V2P((unsigned long)SHM_BASE_ADDR+SHM_OFFSET_TEMPERATURE), (unsigned long)SHM_BASE_ADDR+SHM_OFFSET_TEMPERATURE, SHM_SIZE_TEMPERATURE);
    hwadp_printf("%-30s%10p%10lx%10x\n", "SHM_SIZE_DDM_LOAD", SHD_DDR_V2P((unsigned long)SHM_BASE_ADDR+SHM_OFFSET_DDM_LOAD),(unsigned long)SHM_BASE_ADDR+SHM_OFFSET_DDM_LOAD, SHM_SIZE_DDM_LOAD);
    hwadp_printf("%-30s%10p%10lx%10x\n", "SHM_SIZE_MEM_APPA9_PM_BOOT", SHD_DDR_V2P((unsigned long)SHM_BASE_ADDR+SHM_OFFSET_APPA9_PM_BOOT), (unsigned long)SHM_BASE_ADDR + SHM_OFFSET_APPA9_PM_BOOT, SHM_SIZE_MEM_APPA9_PM_BOOT);
    hwadp_printf("%-30s%10p%10lx%10x\n", "SHM_SIZE_MEM_MDMA9_PM_BOOT", SHD_DDR_V2P((unsigned long)SHM_BASE_ADDR+SHM_OFFSET_MDMA9_PM_BOOT), (unsigned long)SHM_BASE_ADDR+SHM_OFFSET_MDMA9_PM_BOOT, SHM_SIZE_MEM_MDMA9_PM_BOOT);
    hwadp_printf("%-30s%10p%10lx%10x\n", "SHM_SIZE_TENCILICA_MULT_BAND", SHD_DDR_V2P((unsigned long)SHM_BASE_ADDR+SHM_OFFSET_TENCILICA_MULT_BAND), (unsigned long)SHM_BASE_ADDR+SHM_OFFSET_TENCILICA_MULT_BAND, SHM_SIZE_TENCILICA_MULT_BAND);
    hwadp_printf("%-30s%10p%10lx%10x\n", "SHM_SIZE_ICC", SHD_DDR_V2P((unsigned long)SHM_BASE_ADDR+SHM_OFFSET_ICC), (unsigned long)SHM_BASE_ADDR+SHM_OFFSET_ICC, SHM_SIZE_ICC);
    hwadp_printf("%-30s%10p%10lx%10x\n", "SHM_SIZE_IPF", SHD_DDR_V2P((unsigned long)SHM_BASE_ADDR+SHM_OFFSET_IPF), (unsigned long)SHM_BASE_ADDR+SHM_OFFSET_IPF, SHM_SIZE_IPF);
    hwadp_printf("%-30s%10p%10lx%10x\n", "SHM_SIZE_PSAM", SHD_DDR_V2P((unsigned long)SHM_BASE_ADDR+SHM_OFFSET_PSAM), (unsigned long)SHM_BASE_ADDR+SHM_OFFSET_PSAM, SHM_SIZE_PSAM);
    hwadp_printf("%-30s%10p%10lx%10x\n", "SHM_SIZE_WAN", SHD_DDR_V2P((unsigned long)SHM_BASE_ADDR+SHM_OFFSET_WAN), (unsigned long)SHM_BASE_ADDR+SHM_OFFSET_WAN, SHM_SIZE_WAN);
    hwadp_printf("%-30s%10p%10lx%10x\n", "SHM_SIZE_NV", SHD_DDR_V2P((unsigned long)SHM_BASE_ADDR+SHM_OFFSET_NV), (unsigned long)SHM_BASE_ADDR+SHM_OFFSET_NV, SHM_SIZE_NV);
    hwadp_printf("%-30s%10p%10lx%10x\n", "SHM_SIZE_M3_MNTN", SHD_DDR_V2P((unsigned long)SHM_BASE_ADDR+SHM_OFFSET_M3_MNTN), (unsigned long)SHM_BASE_ADDR+SHM_OFFSET_M3_MNTN, SHM_SIZE_M3_MNTN);
    hwadp_printf("%-30s%10p%10lx%10x\n", "SHM_SIZE_TIMESTAMP", SHD_DDR_V2P((unsigned long)SHM_BASE_ADDR+SHM_OFFSET_TIMESTAMP), (unsigned long)SHM_BASE_ADDR+SHM_OFFSET_TIMESTAMP, SHM_SIZE_TIMESTAMP);
    hwadp_printf("%-30s%10p%10lx%10x\n", "SHM_SIZE_IOS", SHD_DDR_V2P((unsigned long)SHM_BASE_ADDR+SHM_OFFSET_IOS), (unsigned long)SHM_BASE_ADDR+SHM_OFFSET_IOS, SHM_SIZE_IOS);
    hwadp_printf("%-30s%10p%10lx%10x\n", "SHM_SIZE_RESTORE_AXI", SHD_DDR_V2P((unsigned long)SHM_BASE_ADDR+SHM_OFFSET_RESTORE_AXI), (unsigned long)SHM_BASE_ADDR+SHM_OFFSET_RESTORE_AXI, SHM_SIZE_RESTORE_AXI);
    hwadp_printf("%-30s%10p%10lx%10x\n", "SHM_SIZE_PMU", SHD_DDR_V2P((unsigned long)SHM_BASE_ADDR+SHM_OFFSET_PMU), (unsigned long)SHM_BASE_ADDR+SHM_OFFSET_PMU, SHM_SIZE_PMU);
    hwadp_printf("%-30s%10p%10lx%10x\n", "SHM_SIZE_PTABLE", SHD_DDR_V2P((unsigned long)SHM_BASE_ADDR+SHM_OFFSET_PTABLE), (unsigned long)SHM_BASE_ADDR+SHM_OFFSET_PTABLE, SHM_SIZE_PTABLE);
    hwadp_printf("%-30s%10p%10lx%10x\n", "SHM_SIZE_CCORE_RESET", SHD_DDR_V2P((unsigned long)SHM_BASE_ADDR+SHM_OFFSET_CCORE_RESET), (unsigned long)SHM_BASE_ADDR+SHM_OFFSET_CCORE_RESET, SHM_SIZE_CCORE_RESET);
    hwadp_printf("%-30s%10p%10lx%10x\n", "SHM_SIZE_PM_OM", SHD_DDR_V2P((unsigned long)SHM_BASE_ADDR+SHM_OFFSET_PM_OM), (unsigned long)SHM_BASE_ADDR+SHM_OFFSET_PM_OM, SHM_SIZE_PM_OM);
    hwadp_printf("%-30s%10p%10lx%10x\n", "SHM_SIZE_M3PM", SHD_DDR_V2P((unsigned long)SHM_BASE_ADDR+SHM_OFFSET_M3PM), (unsigned long)SHM_BASE_ADDR+SHM_OFFSET_M3PM, SHM_SIZE_M3PM);
    hwadp_printf("%-30s%10p%10lx%10x\n", "SHM_SIZE_SLICE_MEM", SHD_DDR_V2P((unsigned long)SHM_BASE_ADDR+SHM_OFFSET_SLICE_MEM), (unsigned long)SHM_BASE_ADDR+SHM_OFFSET_SLICE_MEM, SHM_SIZE_SLICE_MEM);
    hwadp_printf("%-30s%10p%10lx%10x\n", "SHM_SIZE_OSA_LOG", SHD_DDR_V2P((unsigned long)SHM_BASE_ADDR+SHM_OFFSET_OSA_LOG), (unsigned long)SHM_BASE_ADDR+SHM_OFFSET_OSA_LOG, SHM_SIZE_OSA_LOG);
    hwadp_printf("%-30s%10p%10lx%10x\n", "SHM_SIZE_WAS_LOG", SHD_DDR_V2P((unsigned long)SHM_BASE_ADDR+SHM_OFFSET_WAS_LOG), (unsigned long)SHM_BASE_ADDR+SHM_OFFSET_WAS_LOG, SHM_SIZE_WAS_LOG);
    hwadp_printf("%-30s%10p%10lx%10x\n", "SHM_SIZE_SRAM_BAK", SHD_DDR_V2P((unsigned long)SHM_BASE_ADDR+SHM_OFFSET_SRAM_BAK), (unsigned long)SHM_BASE_ADDR+SHM_OFFSET_SRAM_BAK, SHM_SIZE_SRAM_BAK);
    hwadp_printf("%-30s%10p%10lx%10x\n", "SHM_SIZE_SRAM_TO_DDR", SHD_DDR_V2P((unsigned long)SHM_BASE_ADDR+SHM_OFFSET_SRAM_TO_DDR), (unsigned long)SHM_BASE_ADDR+SHM_OFFSET_SRAM_TO_DDR, SHM_SIZE_SRAM_TO_DDR);
	hwadp_printf("%-30s%10p%10lx%10x\n", "SHM_SIZE_M3RSRACC_BD", SHD_DDR_V2P((unsigned long)SHM_BASE_ADDR+SHM_OFFSET_M3RSRACC_BD), (unsigned long)SHM_BASE_ADDR+SHM_OFFSET_M3RSRACC_BD, SHM_SIZE_M3RSRACC_BD);
    hwadp_printf("%-30s%10p%10lx%10x\n", "SHM_SIZE_MEMMGR", SHD_DDR_V2P((unsigned long)SHM_BASE_ADDR+SHM_OFFSET_MEMMGR), (unsigned long)SHM_BASE_ADDR+SHM_OFFSET_MEMMGR, SHM_SIZE_MEMMGR);
    /*不满足KB对齐区，从SLICE_MEM中分配*/
    hwadp_printf("%-30s%10p%10lx%10x\n", "SHM_SIZE_MEMMGR_FLAG", SHD_DDR_V2P((unsigned long)SHM_BASE_ADDR+SHM_OFFSET_MEMMGR_FLAG), (unsigned long)SHM_BASE_ADDR+SHM_OFFSET_MEMMGR_FLAG, SHM_SIZE_MEMMGR_FLAG);
    hwadp_printf("%-30s%10p%10lx%10x\n", "SHM_SIZE_SYNC", SHD_DDR_V2P((unsigned long)SHM_BASE_ADDR+SHM_OFFSET_SYNC), (unsigned long)SHM_BASE_ADDR+SHM_OFFSET_SYNC, SHM_SIZE_SYNC);
    hwadp_printf("%-30s%10p%10lx%10x\n", "SHM_SIZE_AT_FLAG", SHD_DDR_V2P((unsigned long)SHM_BASE_ADDR+SHM_OFFSET_AT_FLAG), (unsigned long)SHM_BASE_ADDR+SHM_OFFSET_AT_FLAG, SHM_SIZE_AT_FLAG);
    hwadp_printf("%-30s%10p%10lx%10x\n", "SHM_SIZE_CSHELL_FLAG", SHD_DDR_V2P((unsigned long)SHM_BASE_ADDR+SHM_OFFSET_CHSELL_FLAG), (unsigned long)SHM_BASE_ADDR+SHM_OFFSET_CHSELL_FLAG, SHM_SIZE_CSHELL_FLAG);
    hwadp_printf("%-30s%10p%10lx%10x\n", "SHM_SIZE_DSP_FLAG", SHD_DDR_V2P((unsigned long)SHM_BASE_ADDR+SHM_OFFSET_DSP_FLAG), (unsigned long)SHM_BASE_ADDR+SHM_OFFSET_DSP_FLAG, SHM_SIZE_DSP_FLAG);
    hwadp_printf("%-30s%10p%10lx%10x\n", "SHM_SIZE_CDSP_FLAG", SHD_DDR_V2P((unsigned long)SHM_BASE_ADDR+SHM_OFFSET_CDSP_FLAG), (unsigned long)SHM_BASE_ADDR+SHM_OFFSET_CDSP_FLAG, SHM_SIZE_CDSP_FLAG);
    hwadp_printf("%-30s%10p%10lx%10x\n", "SHM_SIZE_CCORE_L2CACHE", SHD_DDR_V2P((unsigned long)SHM_BASE_ADDR+SHM_OFFSET_CCORE_L2CACHE), (unsigned long)SHM_BASE_ADDR+SHM_OFFSET_CCORE_L2CACHE, SHM_SIZE_CCORE_L2CACHE);
    hwadp_printf("%-30s%10p%10lx%10x\n", "SHM_SIZE_LOADM", SHD_DDR_V2P((unsigned long)SHM_BASE_ADDR+SHM_OFFSET_LOADM), (unsigned long)SHM_BASE_ADDR+SHM_OFFSET_LOADM, SHM_SIZE_LOADM);
    hwadp_printf("%-30s%10p%10lx%10x\n", "SHM_SIZE_MEMREPAIR", SHD_DDR_V2P((unsigned long)SHM_BASE_ADDR+SHM_OFFSET_MEMREPAIR), (unsigned long)SHM_BASE_ADDR+SHM_OFFSET_MEMREPAIR, SHM_SIZE_MEMREPAIR);
    hwadp_printf("%-30s%10p%10lx%10x\n", "SHM_SIZE_NAND_SPEC", SHD_DDR_V2P((unsigned long)SHM_BASE_ADDR+SHM_OFFSET_NAND_SPEC), (unsigned long)SHM_BASE_ADDR+SHM_OFFSET_NAND_SPEC, SHM_SIZE_NAND_SPEC);
    hwadp_printf("%-30s%10p%10lx%10x\n", "SHM_SIZE_VERSION", SHD_DDR_V2P((unsigned long)SHM_BASE_ADDR+SHM_OFFSET_VERSION), (unsigned long)SHM_BASE_ADDR+SHM_OFFSET_VERSION, SHM_SIZE_VERSION);
    hwadp_printf("%-30s%10p%10lx%10x\n", "SHM_SIZE_UART_FLAG", SHD_DDR_V2P((unsigned long)SHM_BASE_ADDR+SHM_OFFSET_UART_FLAG), (unsigned long)SHM_BASE_ADDR+SHM_OFFSET_UART_FLAG, SHM_SIZE_UART_FLAG);
    hwadp_printf("%-30s%10p%10lx%10x\n", "SHM_SIZE_M3PM_LOG", SHD_DDR_V2P((unsigned long)SHM_BASE_ADDR+SHM_OFFSET_M3PM_LOG), (unsigned long)SHM_BASE_ADDR+SHM_OFFSET_M3PM_LOG, SHM_SIZE_M3PM_LOG);
    hwadp_printf("%-30s%10p%10lx%10x\n", "SHM_SIZE_PAN_RPC", SHD_DDR_V2P((unsigned long)SHM_BASE_ADDR+SHM_OFFSET_PAN_RPC), (unsigned long)SHM_BASE_ADDR+SHM_OFFSET_PAN_RPC, SHM_SIZE_PAN_RPC);
    hwadp_printf("%-30s%10p%10lx%10x\n", "SHM_SIZE_MODEM_SR_STAMP", SHD_DDR_V2P((unsigned long)SHM_BASE_ADDR+SHM_OFFSET_MODEM_SR_STAMP), (unsigned long)SHM_BASE_ADDR+SHM_OFFSET_MODEM_SR_STAMP, SHM_SIZE_MODEM_SR_STAMP);
    hwadp_printf("%-30s%10p%10lx%10x\n", "SHM_SIZE_TSENSOR_STAMP", SHD_DDR_V2P((unsigned long)SHM_BASE_ADDR+SHM_OFFSET_TSENSOR_STAMP), (unsigned long)SHM_BASE_ADDR+SHM_OFFSET_TSENSOR_STAMP, SHM_SIZE_TSENSOR_STAMP);
    hwadp_printf("%-30s%10p%10lx%10x\n", "SHM_SIZE_RFFE_VIA_FLAG", SHD_DDR_V2P((unsigned long)SHM_BASE_ADDR+SHM_OFFSET_RFFE_VIA_LP_FLAG), (unsigned long)SHM_BASE_ADDR+SHM_OFFSET_RFFE_VIA_LP_FLAG, SHM_SIZE_RFFE_VIA_LP_FLAG);
    hwadp_printf("total size: 0x%x\n", total_size);
	return 0;
}
