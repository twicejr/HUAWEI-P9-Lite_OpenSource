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

#include <string.h>
#include <securec.h>
#include <osl_types.h>
#include <osl_module.h>
#include <osl_irq.h>
#include <osl_malloc.h>
#include <osl_list.h>
#include <soc_interrupts_comm.h>
#include <mdrv_public.h>
#include <mdrv_misc_comm.h>
#include <mdrv_int_comm.h>
#include <mdrv_int.h>
#include <mdrv_memory.h>
#include <bsp_shared_ddr.h>
#include <bsp_vic.h>

#define HWADP_MAX_IP_BASE_NUM 256U
#define HWADP_MAX_IRQ_NUM 256U
#define HWADP_MAX_NAME_LEN 127U
#define HWADP_ERR_IRQ_NUM -1

#ifndef INT_LVL_MAX
#define INT_LVL_MAX 224
#endif

struct ul_base_addr_info
{
	struct list_head node;
	BSP_IP_TYPE_E enIPType;
	char ip_name[HWADP_MAX_NAME_LEN + 1];
	void * ul_base_addr;
};

struct ul_int_info
{
	struct list_head node;
	BSP_INT_TYPE_E enIPType;
	char int_name[HWADP_MAX_NAME_LEN + 1];
	unsigned int irq_num;
};

struct ul_mem_info
{
	BSP_DDR_TYPE_E enMEMType;
	void * mem_base_addr;
	unsigned int size;
};

struct gu_ctrl
{
	void *addr_virt;
	void *addr_phy;
	unsigned int mem_size;
};

struct ul_base_addr_info * g_ip_addrs[HWADP_MAX_IP_BASE_NUM] =
{
	[0 ... HWADP_MAX_IP_BASE_NUM - 1] = NULL,
};
struct ul_int_info * g_irqs[HWADP_MAX_IRQ_NUM] =
{
	[0 ... HWADP_MAX_IRQ_NUM - 1] = NULL,
};
BSP_DDR_SECT_INFO_S g_ddr_info[BSP_DDR_SECT_TYPE_BUTTOM] =
{
	[0 ... BSP_DDR_SECT_TYPE_BUTTOM - 1] = {BSP_DDR_SECT_TYPE_BUTTOM, BSP_DDR_SECT_ATTR_BUTTOM, NULL, NULL, 0},
};
struct gu_ctrl g_gu_ctrl = {NULL, NULL, 0};
struct ul_mem_info g_mem_info[BSP_DDR_TYPE_BUTTOM] =
{
	[0 ... BSP_DDR_TYPE_BUTTOM - 1] = {BSP_DDR_TYPE_BUTTOM, NULL, 0},
};
BSP_AXI_SECT_INFO_S g_sram_info[BSP_AXI_SECT_TYPE_BUTTOM] =
{
	[0 ... BSP_AXI_SECT_TYPE_BUTTOM - 1] = {NULL, NULL, BSP_AXI_SECT_TYPE_BUTTOM, 0},
};
static void * sysctrl_nmi_reg[NMI_INT_CORE_NUM] = {NULL,};

LIST_HEAD(hwadp_ip_addrs);
LIST_HEAD(hwadp_irq_nums);

void * mdrv_misc_get_ip_baseaddr(BSP_IP_TYPE_E enIPType)
{
	/*lint -e650 */
	return enIPType < HWADP_MAX_IP_BASE_NUM && g_ip_addrs[(int)enIPType] ? g_ip_addrs[(int)enIPType]->ul_base_addr : NULL;
	/*lint +e650 */
}

void * mdrv_misc_get_ip_baseaddr_byname(const char * ip_name)
{
	void * ip_base = NULL;
	struct ul_base_addr_info * pos = (struct ul_base_addr_info *)hwadp_ip_addrs.next;

	if(!ip_name)
		return ip_base;

	list_for_each_entry(pos, &hwadp_ip_addrs, node)
	{
		if(!strcmp(ip_name, pos->ip_name))
		{
			ip_base = pos->ul_base_addr;
			break;
		}
	}
	return ip_base;
}

int mdrv_int_get_num(BSP_INT_TYPE_E enIntType)
{
	/*lint -e650 */
	return enIntType < HWADP_MAX_IRQ_NUM && g_irqs[(int)enIntType] ? (int)g_irqs[(int)enIntType]->irq_num : HWADP_ERR_IRQ_NUM;
	/*lint +e650 */
}

int mdrv_int_get_num_byname(const char * int_name)
{
	int irq_num = HWADP_ERR_IRQ_NUM;
	struct ul_int_info * pos = (struct ul_int_info *)hwadp_irq_nums.next;

	if(!int_name)
		return irq_num;

	list_for_each_entry(pos, &hwadp_irq_nums, node)
	{
		if(!strcmp(int_name, pos->int_name))
		{
			irq_num = (int)pos->irq_num;
			break;
		}
	}
	return irq_num;
}

int mdrv_int_enable(int ulLev)
{
	int retval = MDRV_OK;

	if(ulLev >= 0 && ulLev < INT_LVL_MAX)
		(void)enable_irq((unsigned int)ulLev);
	else if(ulLev < INT_LVL_MAX + 32 * 4)
		retval = bsp_vic_enable(ulLev - INT_LVL_MAX);
	else
		retval = MDRV_ERROR;

	return retval;
}

int mdrv_int_disable(int ulLev)
{
	int retval = MDRV_OK;

	if(ulLev >= 0 && ulLev < INT_LVL_MAX)
		(void)disable_irq((unsigned int)ulLev);
	else if(ulLev < INT_LVL_MAX + 32 * 4)
		retval = bsp_vic_disable(ulLev - INT_LVL_MAX);
	else
		retval = MDRV_ERROR;

	return retval;
}

int mdrv_int_connect(int level, VOIDFUNCPTR routine, unsigned int parameter)
{
	int retval = MDRV_OK;

	if(level < INT_LVL_MAX && level >= 0)
		return request_irq((unsigned int)level,(irq_handler_t) routine, 0, "other", (void*)(unsigned long)parameter);
	else if(level < INT_LVL_MAX + 32 * 4)
		retval = bsp_vic_connect(level - INT_LVL_MAX, (vicfuncptr)routine, (int)parameter);
	else
		retval = MDRV_ERROR;

	return retval;
}

int mdrv_int_disconnect(int level, unsigned int parameter)
{
	int retval = MDRV_OK;

	if(level < INT_LVL_MAX && level >= 0)
		free_irq((unsigned int)level, (void*)(unsigned long)parameter);
	else if(level < INT_LVL_MAX + 32 * 4)
		retval = bsp_vic_disconnect(level - INT_LVL_MAX);
	else
		retval = MDRV_ERROR;

	return retval;
}

int mdrv_get_fix_ddr_addr(BSP_DDR_SECT_QUERY_S *pstSectQuery, BSP_DDR_SECT_INFO_S *pstSectInfo)
{
    if((NULL == pstSectQuery) || (NULL == pstSectInfo) || (NULL == g_ddr_info[pstSectQuery->enSectType].pSectPhysAddr))
    {
        return MDRV_ERROR;
    }

    (void)memcpy((void *)pstSectInfo, (const void *)(&g_ddr_info[pstSectQuery->enSectType]), sizeof(BSP_DDR_SECT_INFO_S));

    return MDRV_OK;
}


int mdrv_getmeminfo(BSP_DDR_TYPE_E enDdrType, unsigned int *addr, unsigned int *size)
{
    int i = 0;

    if(!addr || !size || (enDdrType >= BSP_DDR_TYPE_BUTTOM))
        return MDRV_ERROR;

    for(i = 0; i < BSP_DDR_TYPE_BUTTOM; i++) {
        if(enDdrType == g_mem_info[i].enMEMType) {
            *addr = (unsigned int)g_mem_info[i].mem_base_addr;
            *size = g_mem_info[i].size;
            return MDRV_OK;
        }
    }

    return MDRV_ERROR;
}

int mdrv_get_fix_axi_addr(BSP_AXI_SECT_TYPE_E enSectType, BSP_AXI_SECT_INFO_S *pstSectInfo)
{
    if(NULL == pstSectInfo)
    {
        return MDRV_ERROR;
    }

    (void)memcpy_s((void *)pstSectInfo,sizeof(BSP_AXI_SECT_INFO_S),(const void *)(&g_sram_info[enSectType]), sizeof(BSP_AXI_SECT_INFO_S));

    return MDRV_OK;
}

unsigned int mdrv_int_is_inside_context(void)
{
	return (unsigned int)osl_int_context();
}

void bsp_int_send_nmi(enum nmi_int_dst_core core_type, unsigned int status)
{
	unsigned long regval = 0;

	if(NULL == sysctrl_nmi_reg[core_type])
		return;

	regval = readl((unsigned long)sysctrl_nmi_reg[core_type]);
	writel(regval | (0x1U << status), (unsigned long)sysctrl_nmi_reg[core_type]);
}

void mdrv_int_send_nmi(enum nmi_int_dst_core core_type, unsigned int status)
{
	bsp_int_send_nmi(core_type, status);
}

void mdrv_int_register_exithook(FUNCPTR_1 p_Func)
{
}

void mdrv_int_unregister_exithook(void)
{
}

void mdrv_int_register_enterhook(FUNCPTR_1 p_Func)
{
}

void mdrv_int_unregister_enterhook(void)
{
}


void hwadp_register_nmi_reg_offset(unsigned int * regs_addr)
{
	int i = 0;

	for(i = 0; i < NMI_INT_CORE_NUM; i++)
		sysctrl_nmi_reg[i] = (void *)regs_addr[i];
}

void hwadp_register_gu_base(void * phy_base, void * virt_base, unsigned int size)
{
	g_gu_ctrl.addr_virt = virt_base;
	g_gu_ctrl.addr_phy = phy_base;
	g_gu_ctrl.mem_size = size;
}

int bsp_hwadp_register_base_addr(BSP_IP_TYPE_E type, const char * ip_name, void *base_addr)
{
	struct ul_base_addr_info * ip_base = NULL;
	void * base = NULL;

	base = mdrv_misc_get_ip_baseaddr_byname(ip_name);
	if(base)
		return -2;

	if(strlen(ip_name) > HWADP_MAX_NAME_LEN)
		return -1;

	ip_base = (struct ul_base_addr_info *)osl_malloc(sizeof(struct ul_base_addr_info));
	if(!ip_base)
		return -3;

	ip_base->enIPType = type;
	ip_base->ul_base_addr = base_addr;
	(void)strncpy((void *)ip_base->ip_name, ip_name, HWADP_MAX_NAME_LEN);
	ip_base->ip_name[HWADP_MAX_NAME_LEN] = 0;

	list_add(&ip_base->node, &hwadp_ip_addrs);

	/*lint -e650 */
	if(type < HWADP_MAX_IP_BASE_NUM && !g_ip_addrs[(int)type])
		g_ip_addrs[(int)type] = ip_base;
	/*lint +e650 */

	return 0;
}

int bsp_hwadp_register_irq_num(BSP_INT_TYPE_E type, const char * irq_name, unsigned int irq_num)
{
	struct ul_int_info * irq_info = NULL;
	int int_num = HWADP_ERR_IRQ_NUM;

	int_num = mdrv_int_get_num_byname(irq_name);
	if(HWADP_ERR_IRQ_NUM != int_num)
		return -2;

	if(strlen(irq_name) > HWADP_MAX_NAME_LEN)
		return -1;

	irq_info = (struct ul_int_info *)osl_malloc(sizeof(struct ul_int_info));
	if(!irq_info)
		return -3;

	irq_info->enIPType = type;
	irq_info->irq_num = irq_num;
	(void)strncpy((void *)irq_info->int_name, irq_name, HWADP_MAX_NAME_LEN);
	irq_info->int_name[HWADP_MAX_NAME_LEN] = 0;

	list_add(&irq_info->node, &hwadp_irq_nums);

	/*lint -e650 */
	if(type < HWADP_MAX_IRQ_NUM && !g_irqs[(int)type])
		g_irqs[(int)type] = irq_info;
	/*lint +e650 */

	return 0;
}

int bsp_hwadp_register_ddr(BSP_DDR_SECT_TYPE_E type, BSP_DDR_SECT_ATTR_E attr, void *ddr_virt, void *ddr_phy, unsigned int size)
{
    if(type >= BSP_DDR_SECT_TYPE_BUTTOM)
        return MDRV_ERROR;

    g_ddr_info[type].enSectType= type;
    g_ddr_info[type].enSectAttr = attr;
    g_ddr_info[type].pSectVirtAddr = ddr_virt;
    g_ddr_info[type].pSectPhysAddr = ddr_phy;
    g_ddr_info[type].ulSectSize = size;

    return MDRV_OK;
}

int bsp_hwadp_register_mem_info(BSP_DDR_TYPE_E type, void *addr, unsigned int size)
{
    if(type >= BSP_DDR_TYPE_BUTTOM)
        return MDRV_ERROR;

    g_mem_info[type].enMEMType= type;
    g_mem_info[type].mem_base_addr = addr;
    g_mem_info[type].size = size;

    return MDRV_OK;
}

int bsp_hwadp_register_sram(BSP_AXI_SECT_TYPE_E type, void *sram_virt, void *sram_phy, unsigned int size)
{
    if(type >= BSP_AXI_SECT_TYPE_BUTTOM)
        return MDRV_ERROR;

    g_sram_info[type].enSectType= type;
    g_sram_info[type].pSectVirtAddr = sram_virt;
    g_sram_info[type].pSectPhysAddr = sram_phy;
    g_sram_info[type].ulSectSize = size;

    return MDRV_OK;
}
