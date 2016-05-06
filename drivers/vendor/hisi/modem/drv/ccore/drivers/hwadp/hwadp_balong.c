/*
* Copyright (C) Huawei Technologies Co., Ltd. 2012-2015. All rights reserved.
* foss@huawei.com
*
* If distributed as part of the Linux kernel, the following license terms
* apply:
*
* * This program is free software; you can redistribute it and/or modify
* * it under the terms of the GNU General Public License version 2 and 
* * only version 2 as published by the Free Software Foundation.
* *
* * This program is distributed in the hope that it will be useful,
* * but WITHOUT ANY WARRANTY; without even the implied warranty of
* * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE. See the
* * GNU General Public License for more details.
* *
* * You should have received a copy of the GNU General Public License
* * along with this program; if not, write to the Free Software
* * Foundation, Inc., 59 Temple Place, Suite 330, Boston, MA 02111-1307, USA
*
* Otherwise, the following license terms apply:
*
* * Redistribution and use in source and binary forms, with or without
* * modification, are permitted provided that the following conditions
* * are met:
* * 1) Redistributions of source code must retain the above copyright
* *    notice, this list of conditions and the following disclaimer.
* * 2) Redistributions in binary form must reproduce the above copyright
* *    notice, this list of conditions and the following disclaimer in the
* *    documentation and/or other materials provided with the distribution.
* * 3) Neither the name of Huawei nor the names of its contributors may 
* *    be used to endorse or promote products derived from this software 
* *    without specific prior written permission.
* 
* * THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS "AS IS"
* AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE
* IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE
* ARE DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT OWNER OR CONTRIBUTORS BE
* LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR
* CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF
* SUBSTITUTE GOODS OR SERVICES; LOSS OF USE, DATA, OR PROFITS; OR BUSINESS
* INTERRUPTION) HOWEVER CAUSED AND ON ANY THEORY OF LIABILITY, WHETHER IN
* CONTRACT, STRICT LIABILITY, OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE)
* ARISING IN ANY WAY OUT OF THE USE OF THIS SOFTWARE, EVEN IF ADVISED OF THE
* POSSIBILITY OF SUCH DAMAGE.
*
*/
/*lint -e451*/
#include <of.h>
#include <product_config.h>
#include <mdrv_memory.h>
#include <mdrv_errno.h>
#include <drv_mailbox_cfg.h>
#include <bsp_sram.h>
#include <bsp_shared_ddr.h>
#include <bsp_sysctrl.h>
#include <bsp_om.h>
#include <bsp_hwadp.h>
#include <bsp_om_enum.h>
#include <bsp_dump.h>
#include <bsp_dump_drv.h>
/*lint +e451*/
#define hwadp_printf(fmt, ...) bsp_trace(BSP_LOG_LEVEL_ERROR,BSP_MODU_HWADP,fmt,##__VA_ARGS__)

#define MEMORY_AXI_DICC_ADDR   (void *)((((SRAM_SMALL_SECTIONS*)((unsigned long)SRAM_BASE_ADDR + SRAM_OFFSET_SMALL_SECTIONS))->SRAM_DICC))
#define SRAM_TEMP_PROTECT_ADDR (void *)(((SRAM_SMALL_SECTIONS*)((unsigned long)SRAM_BASE_ADDR + SRAM_OFFSET_SMALL_SECTIONS))->SRAM_TEMP_PROTECT)

extern void hwadp_register_nmi_reg_offset(unsigned int * regs_addr);
extern void hwadp_register_gu_base(void * phy_base, void * virt_base, unsigned int size);

static void hwadp_dts_register_base_addr(void)
{
	struct device_node *node = NULL, *np = NULL;
	int retval = 0;
	const char * nmi_node = "hisilicon,mdrv_nmi_interrupt_regs";
	unsigned int nmi_regs_val[NMI_INT_CORE_NUM] = {0,};

	node = of_find_compatible_node(NULL, NULL, "hisilicon,hardware_adapt");
	if (!node) {
		hwadp_printf("dts node not found!\n");
		return;
	}

	for_each_available_child_of_node(node, np)
	{
		unsigned int ip_type = ~0U, int_type = ~0U, irq_num = ~0U;
		int na = 0, ns = 0, len = 0;
		unsigned long base_addr = 0;
		const __be32 *prop = NULL;

		if(!np->name || !strlen(np->name))
			continue;

		/* try to obtain ip base address */
		na = of_n_addr_cells(np);
		ns = of_n_size_cells(np);
		prop = of_get_property(np, "reg", &len);
		retval = of_property_read_u32(np, "ip_type", &ip_type);
		if(prop && (len == (na + ns) * (int)sizeof(*prop)))
		{
			base_addr = (unsigned long)of_read_number(prop, na);
			if(base_addr && !(base_addr & ((0x1U << 12) - 1)))
				(void)of_iomap(np, 0);
			else
				hwadp_printf("hwad:reg addr = 0x%X Address of zero or that ones not aligned for page are not map!\n",base_addr);
			if(retval)
				ip_type = ~0U;
			retval = bsp_hwadp_register_base_addr(ip_type, (const char *)np->name, (void *)base_addr);
			if(retval)
				hwadp_printf("hwadp:failed to register base addr!ip_type=%d base_addr=%p name=%s\n",(int)ip_type, (void*)base_addr,np->name);
			continue;
		}

		/* try to obtain irq number */
		retval = of_property_read_u32_index(np, "interrupts", 1, &irq_num);
		if(retval)
			continue;

		retval = of_property_read_u32(np, "int_type", &int_type);
		if(retval)
			int_type = ~0U;

		if(bsp_hwadp_register_irq_num(int_type, (const char *)np->name, irq_num))
			hwadp_printf("hwadp:failed to register irq number!int_type=%d irq_num=%d name=%s\n", (int)int_type, irq_num, np->name);
	}

	/* nmi */
	np = of_find_compatible_node(NULL, NULL, nmi_node);
	if(!np)
		return;
	retval = of_property_read_u32_array(np, "regs", nmi_regs_val, NMI_INT_CORE_NUM);
	if(retval)
		return;
	hwadp_register_nmi_reg_offset(nmi_regs_val);
}

int hwadp_init(void)
{
	int ret = MDRV_OK;
	void * gu_base = NULL;
	void * addr_ao = NULL, *addr_pd = NULL, *addr_mdm = NULL, *addr_ap_peri = NULL;

	hwadp_dts_register_base_addr();
	/* IP base */
	addr_ao = bsp_sysctrl_addr_phy_byindex(sysctrl_ao);
	addr_pd = bsp_sysctrl_addr_phy_byindex(sysctrl_pd);
	addr_mdm = bsp_sysctrl_addr_phy_byindex(sysctrl_mdm);
	addr_ap_peri = bsp_sysctrl_addr_phy_byindex(sysctrl_ap_peri);

	ret += bsp_hwadp_register_base_addr(BSP_IP_TYPE_AHB, "AHB", (void*)DDR_ZSP_UP_ADDR);
	ret += bsp_hwadp_register_base_addr(BSP_IP_TYPE_SYSCTRL, "SYSCTRL", addr_ao);
	if(addr_ao != addr_pd)
		ret += bsp_hwadp_register_base_addr(BSP_IP_TYPE_SYSCTRL_PD, "SYSCTRL_PD", addr_pd);
	if(addr_ao != addr_mdm)
		ret += bsp_hwadp_register_base_addr(BSP_IP_TYPE_SYSCTRL_MDM, "SYSCTRL_MDM", addr_mdm);
	if(addr_ao != addr_ap_peri)
		ret += bsp_hwadp_register_base_addr(BSP_IP_TYPE_PERI_SYSCTRL, "PERI_SYSCTRL", addr_ap_peri);

	/* mem info */
	ret += bsp_hwadp_register_mem_info(BSP_DDR_TYPE_DDR_GU, (void *)DDR_UPA_ADDR,
			DDR_UPA_SIZE + DDR_CQI_SIZE + DDR_APT_SIZE + DDR_ET_SIZE + DDR_NV_SIZE + DDR_ZSP_UP_SIZE);
    ret += bsp_hwadp_register_mem_info(BSP_DDR_TYPE_SRAM_TLPHY,
                                      (void *)((unsigned long)SHM_BASE_ADDR + SHM_OFFSET_TLPHY),
                                      SHM_SIZE_TLPHY);
    ret += bsp_hwadp_register_mem_info(BSP_DDR_TYPE_SHM_TEMPERATURE,
                                      (void *)((unsigned long)SHM_BASE_ADDR + SHM_OFFSET_TEMPERATURE),
                                      SHM_SIZE_TEMPERATURE);
    ret += bsp_hwadp_register_mem_info(BSP_DDR_TYPE_SRAM_TLDSP_SHARED,
                                      (void *)((unsigned long)SRAM_BASE_ADDR + SRAM_OFFSET_TLDSP_SHARED),
                                       SRAM_SIZE_TLDSP_SHARED);
    ret += bsp_hwadp_register_mem_info(BSP_DDR_TYPE_SHM_TIMESTAMP,
                                      (void *)((unsigned long)SHM_BASE_ADDR + SHM_OFFSET_TIMESTAMP),
                                      SHM_SIZE_TIMESTAMP);
    ret += bsp_hwadp_register_mem_info(BSP_DDR_TYPE_SRAM_MAILBOX_PROTECT_FLG,
                                      (void *)(&((SRAM_SMALL_SECTIONS*)((unsigned long)SRAM_BASE_ADDR + SRAM_OFFSET_SMALL_SECTIONS))->SRAM_DSP_DRV),
                                      sizeof(unsigned int));
    ret += bsp_hwadp_register_mem_info(BSP_DDR_TYPE_SRAM_DSP_MNTN_INFO,
                                      (void *)(((SRAM_SMALL_SECTIONS*)((unsigned long)SRAM_BASE_ADDR + SRAM_OFFSET_SMALL_SECTIONS))->SRAM_DSP_MNTN_INFO),
                                      SRAM_DSP_MNTN_SIZE);
    ret += bsp_hwadp_register_mem_info(BSP_DDR_TYPE_DDR_TLPHY_BANDNV,
                                      (void *)((unsigned long)SHM_BASE_ADDR + SHM_OFFSET_TENCILICA_MULT_BAND),
                                      SHM_SIZE_TENCILICA_MULT_BAND);
    ret += bsp_hwadp_register_mem_info(BSP_DDR_TYPE_DDR_TLPHY_IMAGE,(void*)DDR_TLPHY_IMAGE_ADDR,DDR_TLPHY_IMAGE_SIZE);
    ret += bsp_hwadp_register_mem_info(BSP_DDR_TYPE_DDR_LPHY_SDR,(void*)DDR_LPHY_SDR_ADDR,DDR_LPHY_SDR_SIZE);
    ret += bsp_hwadp_register_mem_info(BSP_DDR_TYPE_DDR_TLPHY_LCS,(void*)DDR_LCS_ADDR,DDR_LCS_SIZE);
    ret += bsp_hwadp_register_mem_info(BSP_DDR_TYPE_DDR_HIFI,(void*)DDR_HIFI_ADDR,DDR_HIFI_SIZE);
    ret += bsp_hwadp_register_mem_info(BSP_DDR_TYPE_SHM_BBE16_HIFI_HEAD,(void*)MAILBOX_HEAD_ADDR(BBE16, HIFI, MSG),MAILBOX_HEAD_LEN);
    ret += bsp_hwadp_register_mem_info(BSP_DDR_TYPE_SHM_HIFI_BBE16_HEAD,(void*)MAILBOX_HEAD_ADDR(HIFI, BBE16, MSG),MAILBOX_HEAD_LEN);
    ret += bsp_hwadp_register_mem_info(BSP_DDR_TYPE_SHM_BBE16_HIFI_QUEUE,(void*)MAILBOX_QUEUE_ADDR(BBE16, HIFI, MSG),MAILBOX_QUEUE_SIZE(BBE16, HIFI, MSG));
    ret += bsp_hwadp_register_mem_info(BSP_DDR_TYPE_SHM_HIFI_BBE16_QUEUE,(void*)MAILBOX_QUEUE_ADDR(HIFI, BBE16, MSG),MAILBOX_QUEUE_SIZE(HIFI, BBE16, MSG));

    /* sram */
    ret += bsp_hwadp_register_sram(BSP_AXI_SECT_TYPE_TEMPERATURE, (void *)SRAM_TEMP_PROTECT_ADDR,
                                   (void *)SRAM_V2P(SRAM_TEMP_PROTECT_ADDR), SRAM_TEMP_PROTECT_SIZE);
    ret += bsp_hwadp_register_sram(BSP_AXI_SECT_TYPE_DICC, MEMORY_AXI_DICC_ADDR,
                                   (void *)SRAM_V2P((unsigned long)MEMORY_AXI_DICC_ADDR), 8);
    ret += bsp_hwadp_register_sram(BSP_AXI_SECT_TYPE_HIFI, (void *)((unsigned long)SHM_BASE_ADDR + SHM_OFFSET_HIFI),
                                   (void *)SHD_DDR_V2P((unsigned long)SHM_BASE_ADDR + SHM_OFFSET_HIFI), SHM_SIZE_HIFI);
    ret += bsp_hwadp_register_sram(BSP_AXI_SECT_TYPE_TTF_BBP, (void *)((unsigned long)SRAM_BASE_ADDR + SRAM_OFFSET_GU_MAC_HEADER),
                                   (void *)SRAM_V2P((void *)((unsigned long)SRAM_BASE_ADDR + SRAM_OFFSET_GU_MAC_HEADER)), SRAM_SIZE_GU_MAC_HEADER);
#ifdef CPHY_SRAM_ADDR
    ret += bsp_hwadp_register_sram(BSP_AXI_SECT_TYPE_CPHY_SRAM, (void *)((unsigned long)CPHY_SRAM_ADDR),
                                   (void *)SRAM_V2P((void *)((unsigned long)CPHY_SRAM_ADDR)), CPHY_SRAM_SIZE);
#endif
    ret += bsp_hwadp_register_ddr(BSP_DDR_SECT_TYPE_WAN, BSP_DDR_SECT_ATTR_NONCACHEABLE, (void *)((unsigned long)SHM_BASE_ADDR + SHM_OFFSET_WAN),
                                  (void *)SHD_DDR_V2P((unsigned long)SHM_BASE_ADDR + SHM_OFFSET_WAN), SHM_SIZE_WAN);
	ret += bsp_hwadp_register_ddr(BSP_DDR_SECT_TYPE_MODEM_SR_STAMP, BSP_DDR_SECT_ATTR_NONCACHEABLE, (void *)((unsigned long)SHM_BASE_ADDR + SHM_OFFSET_MODEM_SR_STAMP),
                                  (void *)SHD_DDR_V2P((unsigned long)SHM_BASE_ADDR + SHM_OFFSET_MODEM_SR_STAMP), SHM_SIZE_MODEM_SR_STAMP);
    ret += bsp_hwadp_register_ddr(BSP_DDR_SECT_TYPE_HIFI, BSP_DDR_SECT_ATTR_NONCACHEABLE, (void *)DDR_HIFI_ADDR,
                                  (void *)DDR_HIFI_ADDR, DDR_HIFI_SIZE);
    ret += bsp_hwadp_register_ddr(BSP_DDR_SECT_TYPE_SOCP, BSP_DDR_SECT_ATTR_NONCACHEABLE, ioremap_wc((MMU_VA_T)DDR_SOCP_ADDR, DDR_SOCP_SIZE),
                                   (void *)DDR_SOCP_ADDR, DDR_SOCP_SIZE);
    /**************************************GU   memmap   begin**************************/
	gu_base = ioremap_wc((MMU_VA_T)DDR_GU_ADDR, DDR_GU_SIZE);
	hwadp_register_gu_base((void*)DDR_GU_ADDR, gu_base, DDR_GU_SIZE);
    ret += bsp_hwadp_register_ddr(BSP_DDR_SECT_TYPE_UPA, BSP_DDR_SECT_ATTR_NONCACHEABLE, (void*)((unsigned long)gu_base + DDR_UPA_ADDR - DDR_GU_ADDR),
                                  (void *)DDR_UPA_ADDR, DDR_UPA_SIZE);
    ret += bsp_hwadp_register_ddr(BSP_DDR_SECT_TYPE_CQI, BSP_DDR_SECT_ATTR_NONCACHEABLE, (void*)((unsigned long)gu_base + DDR_CQI_ADDR - DDR_GU_ADDR),
                                  (void *)DDR_CQI_ADDR, DDR_CQI_SIZE);
    ret += bsp_hwadp_register_ddr(BSP_DDR_SECT_TYPE_APT, BSP_DDR_SECT_ATTR_NONCACHEABLE, (void*)((unsigned long)gu_base + DDR_APT_ADDR - DDR_GU_ADDR),
                                  (void *)DDR_APT_ADDR, DDR_APT_SIZE);
    ret += bsp_hwadp_register_ddr(BSP_DDR_SECT_TYPE_ET, BSP_DDR_SECT_ATTR_NONCACHEABLE, (void*)((unsigned long)gu_base + DDR_ET_ADDR - DDR_GU_ADDR),
                                  (void *)DDR_ET_ADDR, DDR_ET_SIZE);
    ret += bsp_hwadp_register_ddr(BSP_DDR_SECT_TYPE_NV, BSP_DDR_SECT_ATTR_NONCACHEABLE, (void*)((unsigned long)gu_base + DDR_NV_ADDR - DDR_GU_ADDR),
                                  (void *)DDR_NV_ADDR, DDR_NV_SIZE);
    ret += bsp_hwadp_register_ddr(BSP_DDR_SECT_TYPE_ZSP_UP, BSP_DDR_SECT_ATTR_NONCACHEABLE, (void*)((unsigned long)gu_base + DDR_ZSP_UP_ADDR - DDR_GU_ADDR),
                                   (void *)DDR_ZSP_UP_ADDR, DDR_ZSP_UP_SIZE);
    ret += bsp_hwadp_register_ddr(BSP_DDR_SECT_TYPE_ECS_TEE, BSP_DDR_SECT_ATTR_NONCACHEABLE, (void*)((unsigned long)gu_base + DDR_ECS_TEE_ADDR - DDR_GU_ADDR),
                                   (void *)DDR_ECS_TEE_ADDR, DDR_ECS_TEE_SIZE);
    /**************************************GU   memmap   end**************************/


    if(!ret)
        hwadp_printf("hwadp init ok.\n");
    else
        hwadp_printf("hwadp init fail.\n");
    
    return ret;
}

//subsys_initcall(hwadp_init);


unsigned int   * MemAddr32 = 0x00000000;
/*******************************************************************************
* writeM - write a unsigned int value to perihical address
* adpt for gu
* RETURNS: N/A
*/
void writeM(unsigned int pAddr, unsigned int value)
{
    *(volatile unsigned int *)(pAddr)=value;
}

/***********************************************************
 Function: memRead32--read memory and display the value
            adpt for gu
 Input:    the start address
 return:   void
************************************************************/
void memRead32 (unsigned int uiMemAddr32)
{
    if (0 != uiMemAddr32)
    {
         MemAddr32 = (unsigned int *)(uiMemAddr32 & 0xFFFFFFFC);
    }

    hwadp_printf("0x%.8X: 0x%.8X   0x%.8X   0x%.8X   0x%.8X\n",
            (unsigned int)(MemAddr32+0x0), 
            readl((unsigned int)(MemAddr32+0x0)),
            readl((unsigned int)(MemAddr32+0x1)),
            readl((unsigned int)(MemAddr32+0x2)),
            readl((unsigned int)(MemAddr32+0x3)));
    hwadp_printf("0x%.8X: 0x%.8X   0x%.8X   0x%.8X   0x%.8X\n",
            (unsigned int)(MemAddr32+0x4),
            readl((unsigned int)(MemAddr32+0x4)),
            readl((unsigned int)(MemAddr32+0x5)),
            readl((unsigned int)(MemAddr32+0x6)),
            readl((unsigned int)(MemAddr32+0x7)));
    hwadp_printf("0x%.8X: 0x%.8X   0x%.8X   0x%.8X   0x%.8X\n",
            (unsigned int)(MemAddr32+0x8),
            readl((unsigned int)(MemAddr32+0x8)),
            readl((unsigned int)(MemAddr32+0x9)),
            readl((unsigned int)(MemAddr32+0xa)),
            readl((unsigned int)(MemAddr32+0xb)));
    hwadp_printf("0x%.8X: 0x%.8X   0x%.8X   0x%.8X   0x%.8X\n",
            (unsigned int)(MemAddr32+0xc),
            readl((unsigned int)(MemAddr32+0xc)),
            readl((unsigned int)(MemAddr32+0xd)),
            readl((unsigned int)(MemAddr32+0xe)),
            readl((unsigned int)(MemAddr32+0xf)));        
    MemAddr32 += 0x10;
}

/***********************************************************
 Function: r--simple read memory command
           adpt for gu
 Input:    the start address
 return:  void
************************************************************/
void r(unsigned int newMemAddr32)
{
    memRead32(newMemAddr32);
}

void show_hpm_temp(void)
{
#ifndef BSP_CONFIG_PHONE_TYPE
    struct hpm_tem_print *hpm_ptr = ((struct hpm_tem_print * )bsp_dump_get_field_addr(DUMP_M3_BOOST));
    if(hpm_ptr == NULL)
    {
        hwadp_printf("error, can't find DUMP_SAVE_BOOT_MCORE field in dump.\n");
        return;
    }
    hwadp_printf("****************hpm_temperature****************\n");
    hwadp_printf("hpm_uhvt_opc: 0x%x\n", hpm_ptr->hpm_uhvt_opc);
    hwadp_printf("hpm_hvt_opc : 0x%x\n", hpm_ptr->hpm_hvt_opc);
    hwadp_printf("hpm_svt_opc : 0x%x\n", hpm_ptr->hpm_svt_opc);
    hwadp_printf("temperature : %d\n", hpm_ptr->temperature);
    hwadp_printf("up_volt     : %d\n", hpm_ptr->up_volt);
#endif
}

