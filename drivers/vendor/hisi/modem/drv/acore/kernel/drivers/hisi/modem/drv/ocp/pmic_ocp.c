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
#include <linux/module.h>
#include <linux/init.h>
#include <linux/mfd/hisi_pmic.h>
#include <of.h>
#include <osl_list.h>
#include <osl_malloc.h>
#include <bsp_icc.h>
#include <bsp_om.h>

#define  pmic_print_error(fmt, ...)    (bsp_trace(BSP_LOG_LEVEL_ERROR, BSP_MODU_PMU, "[pmu]: <%s> "fmt, __FUNCTION__, ##__VA_ARGS__))
/*#define  pmic_print_info(fmt, ...)     (bsp_trace(BSP_LOG_LEVEL_INFO, BSP_MODU_PMU, "[pmu]: <%s> "fmt, __FUNCTION__, ##__VA_ARGS__))*/

struct pmic_volt_ocp
{
    int   volt_id;
    const char* volt_name;
    struct list_head   list;
};
//struct list_head g_modem_ocp_list;
LIST_HEAD(g_modem_ocp_list);

static int pmic_modem_ocp_handler(char * name)
{
    int len;
    struct pmic_volt_ocp *ocp_node = NULL;
    u32 chan_id = ICC_CHN_IFC << 16 | IFC_RECV_FUNC_PMU_OCP;
    
    if (NULL == name)
    {
        pmic_print_error("argc is null return\n");
        return -1;
    }

    
    /*get name form id*/
    list_for_each_entry(ocp_node, &g_modem_ocp_list, list)
    {
        if (!strcmp(ocp_node->volt_name, name))
        {
                break;
        }
    }

    len = bsp_icc_send(ICC_CPU_MODEM, chan_id, (unsigned char*)&ocp_node->volt_id, sizeof(int));
    if(len == 0)
    {
        pmic_print_error("send len(%x) != expected len(%x).\n", len, sizeof(int));
        return -2;
    }
    
    return 0;
}

static int __init pmic_modem_ocp_init(void)
{
    int    ret = 0;
    struct device_node *root = NULL;
    struct device_node *child_node = NULL;
    struct pmic_volt_ocp *ocp = NULL;
    
    /*get dts info*/  
    root = of_find_compatible_node(NULL, NULL, "hisilicon,pmic_ocp_modem");
    if(!root)
    {
        pmic_print_error("get pmic dts node failed!\n");
        return -1;
    }

    for_each_child_of_node(root, child_node)
    {
        ocp = (struct pmic_volt_ocp *)osl_malloc(sizeof(struct pmic_volt_ocp));
        if (NULL == ocp)
        {
            pmic_print_error("ocp malloc failed ,err %d\n", ocp);
            return -1;
        }
        INIT_LIST_HEAD(&ocp->list);
        ret = of_property_read_u32(child_node, "id",(u32 *)&ocp->volt_id);
        ret |= of_property_read_string(child_node, "name", &ocp->volt_name);   
        list_add(&ocp->list, &g_modem_ocp_list);        
        if(!ret)
        {        
            ret = hisi_pmic_special_ocp_register((char*)(ocp->volt_name), pmic_modem_ocp_handler);
            if(ret)
            {
                pmic_print_error("modem(%s) ocp register fail! ret is %d\n",ocp->volt_name,ret);
            }
        }
    }
    
    pmic_print_error("pmic modem ocp init ok!\n");

    return ret;
}

module_init(pmic_modem_ocp_init);

