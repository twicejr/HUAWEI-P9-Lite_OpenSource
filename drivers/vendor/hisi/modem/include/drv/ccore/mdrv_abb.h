#ifndef __MDRV_CCORE_ABB_H__
#define __MDRV_CCORE_ABB_H__
#ifdef __cplusplus
extern "C"
{
#endif

/*****************************************************************************
* 函 数 名  : mdrv_abb_set_reg
*
* 功能描述  : 设置abb寄存器
*
* 输入参数  : unsigned int regAddr 寄存器的地址偏移
*             unsigned int setData 寄存器设置的值
* 输出参数  : 无
*
* 返 回 值  : 0 成功；其他，失败；
*
* 其它说明  :
*
*****************************************************************************/
int mdrv_abb_set_reg(unsigned int regAddr, unsigned int setData);
/*****************************************************************************
* 函 数 名  : mdrv_abb_get_reg
*
* 功能描述  : 读取abb寄存器的值
*
* 输入参数  : unsigned int regAddr 寄存器的地址偏移
*             unsigned int *data   存储寄存器地址值的buffer
* 输出参数  : unsigned int *data   存储寄存器地址值
*
* 返 回 值  : 0 成功；其他，失败；
*
* 其它说明  :
*
*****************************************************************************/
int mdrv_abb_get_reg(unsigned int regAddr, unsigned int *data);

#ifdef __cplusplus
}
#endif
#endif
