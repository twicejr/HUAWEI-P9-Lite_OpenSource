#ifndef __MDRV_CCORE_EFUSE_H__
#define __MDRV_CCORE_EFUSE_H__
#ifdef __cplusplus
extern "C"
{
#endif

#include "mdrv_efuse_common.h"


    /************************************************************************
     *  函 数 名  : mdrv_efuse_read_huk
     *  功能描述  :  读取腍UK值。
     *  输入参数  :  pbuf   buffer地址
     *               len    buffer的长度(字节数)
     *
     *  输出参数  : 无
     *  返 回 值  :  0           操作成功。
     *                           其他    操作失败。
     *
     *************************************************************************/
     int mdrv_efuse_read_huk(unsigned char *pbuf, unsigned int len);

#ifdef __cplusplus
}
#endif
#endif

