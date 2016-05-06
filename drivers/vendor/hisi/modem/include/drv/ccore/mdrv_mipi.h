#ifndef __MDRV_CCORE_MIPI_H__
#define __MDRV_CCORE_MIPI_H__
#ifdef __cplusplus
extern "C"
{
#endif

#include "mdrv_public.h"

typedef enum{
    MIPI_ONE_BYTE  = 1,
    MIPI_TWO_BYTE  = 2,
    MIPI_THREE_BYTE= 3,
    MIPI_FOUR_BYTE = 4
}MDRV_MIPI_WR_E;
/*****************************************************************************
    * 函 数    : mdrv_mipi_write_byte
    * 功 能    : mipi 正常写1个byte
    * 输 入    : @mipi_id     使用哪个mipi 总线
                         @slave_id   slave id
                         @reg_addr   要写的寄存器偏移
                         @value       需要写入的值

    * 输 出    : 无
    * 返 回    : 0为成功，-1为失败
    * 作 者    : z00228752
    * 说 明    : 
    *****************************************************************************/
int mdrv_mipi_write_byte(unsigned int mipi_id, unsigned int slave_id, unsigned int reg_addr, unsigned char  value);

/*****************************************************************************
    * 函 数    : mdrv_mipi_write
    * 功 能    : mipi 扩展写
    * 输 入    : @mipi_id     使用哪个mipi 总线
                        @slave_id    slave id
                        @reg_addr    要写的寄存器偏移
                        @value        需要写入的值
                        @byte_cnt    需要写入的字节数，当前支持1、2、4字节的写入

    * 输 出    : 无
    * 返 回    : 0为成功，-1为失败
    * 作 者    : z00228752
    * 说 明    : byte_cnt不要超过4
    *****************************************************************************/
int mdrv_mipi_ex_write(unsigned int mipi_id, unsigned int slave_id, unsigned int reg_addr, unsigned int value, unsigned int byte_cnt);

/*****************************************************************************
    * 函 数    : mdrv_mipi_write_byte
    * 功 能    : mipi 普通读1个byte
    * 输 入    : @mipi_id     使用哪个mipi 总线
                         @slave_id    slave id
                         @reg_addr   要写的寄存器偏移

    * 输 出    : 无
    * 返 回    : -1为失败,other 返回值
    * 作 者    : z00228752
    * 说 明    : 只有低byte为有效寄存器值
    *****************************************************************************/
int mdrv_mipi_read_byte(unsigned int mipi_id, unsigned int slave_id, unsigned int reg_addr, unsigned char* value);


/*****************************************************************************
    * 函 数    : mdrv_mipi_write_byte
    * 功 能    : mipi 扩展读
    * 输 入    : @mipi_id     使用哪个mipi 总线
                        @slave_id    slave id
                        @reg_addr    要写的寄存器偏移
	                 @byte_cnt	 需要写入的字节数，当前支持1、2、4字节的写入

    * 输 出    : 无
    * 返 回    : -1为失败,other 返回值
    * 作 者    : z00228752
    * 说 明    : byte_cnt不要超过4
    *****************************************************************************/
int mdrv_mipi_ex_read(unsigned int mipi_id, unsigned int slave_id, unsigned int reg_addr, unsigned int* value, unsigned int byte_cnt);

#ifdef __cplusplus
}
#endif

#endif

