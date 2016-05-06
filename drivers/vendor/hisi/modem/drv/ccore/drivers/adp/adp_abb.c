#include <bsp_abb.h>

/*****************************************************************************
 函 数 名  : mdrv_abb_set_reg
 功能描述  : set ABB register data
 输入参数  : regAddr --- 待设置寄存器地址,ABB地址位宽为9bit,32bit留作扩展
             setData --- 设置的值,ABB数据位宽为8bit,32bit留作扩展
 输出参数  : 无
 返 回 值  : 0    - successful
             -1   - unsuccessful
*****************************************************************************/
int mdrv_abb_set_reg(unsigned int regAddr, unsigned int setData)
{   
    int ret;
	ret = bsp_abb_write(regAddr, setData);
    return ret;    
}

/*****************************************************************************
 函 数 名  : mdrv_abb_set_reg
 功能描述  : get ABB register data
 输入参数  : regAddr --- 待读寄存器地址,ABB地址位宽为9bit,32bit留作扩展
 输出参数  : *getData --- 存放寄存器值,ABB数据位宽为8bit,32bit留作扩展
 返 回 值  : 0    - successful
             -1 - unsuccessful
*****************************************************************************/
int mdrv_abb_get_reg(unsigned int regAddr, unsigned int *data)
{
    int ret;
	ret = bsp_abb_read(regAddr, data);    
    return ret;    
}

