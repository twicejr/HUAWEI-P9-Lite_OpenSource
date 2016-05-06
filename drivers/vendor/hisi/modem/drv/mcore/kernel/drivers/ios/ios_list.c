/******************************************************************
* Copyright (C), 2005-2007, HISILICON Tech. Co., Ltd.             *
*                                                                 *
* File name: ios_list.c                                           *
*                                                                 *
* Description:                                                    *
*      driver debug module source file                            *
*                                                                 *
* Author:                                                         *
*                                                                 *
* Version: v0.1                                                   *
*                                                                 *
* Function List:                                                  *
*                                                                 *
* Date:                                                           *
*                                                                 *
* History:                                                        *
*                                                                 *
*******************************************************************/
/*lint -save -e537*/
#include <osl_types.h>
#include <osl_bio.h>

#include "bsp_memmap.h"
#include "ios_list.h"

static IOS_POOL_CTRL* p_ios_ctrl = NULL;

static void phy_virt_ctrl_convert(IOS_POOL_CTRL* pool_ctrl, IOS_POOL_CTRL* p_ctrl)
{
    pool_ctrl->start  = p_ctrl->start;
    pool_ctrl->cur    = p_ctrl->cur;
    pool_ctrl->end    = p_ctrl->end;    
}
static void phy_virt_addr_convert(unsigned int *virt_addr, unsigned int addr)
{
    *virt_addr = addr;
}

/*´Ó¹²ÏíÄÚ´æÖÐ»Ö¸´IOSÅäÖÃ¼Ä´æÆ÷*/
int ios_config_resume(void)
{
    unsigned int virt_addr = 0;
    
    IOS_REG_DATA *p_data = NULL;
    IOS_POOL_CTRL pool_ctrl = {0,0,0};
    IOS_POOL_CTRL *p_ctrl = p_ios_ctrl;

    phy_virt_ctrl_convert(&pool_ctrl, p_ctrl);    
    
    p_data = pool_ctrl.start;

    while(p_data != pool_ctrl.cur)
    {
        phy_virt_addr_convert(&virt_addr, p_data->addr);
        writel(p_data->value, virt_addr);
        ++p_data;
    }
    
    return IOS_OK;
}

static int ios_echo(IOS_POOL_CTRL* p_ctrl)
{   
    int i = 0;
    
    IOS_REG_DATA *p_data = NULL;
    IOS_POOL_CTRL pool_ctrl = {0,0,0};

    phy_virt_ctrl_convert(&pool_ctrl, p_ctrl);    
    
    p_data = pool_ctrl.start;

    while(p_data != pool_ctrl.cur)
    {
        ios_print_info("%d\ta=0x%x\tv=0x%x\n",++i, p_data->addr, p_data->value);
        ++p_data;
    }

    ios_print_info("%d left.\n", pool_ctrl.end - pool_ctrl.cur);

    return IOS_OK;
}

void ios_list_echo(void)
{
    IOS_POOL_CTRL* p_ctrl = p_ios_ctrl;
    
	ios_print_info("start...\n");
    
    ios_echo(p_ctrl);
	
	ios_print_info("end...\n");
    
}
void ios_list_init(void)
{
	p_ios_ctrl = (IOS_POOL_CTRL *)SHARED_IOS_ADDR;

}
