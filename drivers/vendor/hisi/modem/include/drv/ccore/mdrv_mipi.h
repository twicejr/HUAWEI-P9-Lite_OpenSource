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

int mdrv_mipi_write_byte(unsigned int mipi_id, unsigned int slave_id, unsigned int reg_addr, unsigned char  value);


int mdrv_mipi_ex_write(unsigned int mipi_id, unsigned int slave_id, unsigned int reg_addr, unsigned int value, unsigned int byte_cnt);


int mdrv_mipi_read_byte(unsigned int mipi_id, unsigned int slave_id, unsigned int reg_addr, unsigned char* value);



int mdrv_mipi_ex_read(unsigned int mipi_id, unsigned int slave_id, unsigned int reg_addr, unsigned int* value, unsigned int byte_cnt);

#ifdef __cplusplus
}
#endif

#endif

