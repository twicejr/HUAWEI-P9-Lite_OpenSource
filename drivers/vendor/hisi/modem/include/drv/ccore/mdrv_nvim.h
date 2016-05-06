#ifndef __MDRV_CCORE_NVIM_H__
#define __MDRV_CCORE_NVIM_H__

#ifdef __cplusplus
extern "C"
{
#endif

#include "mdrv_nvim_comm.h"

/*****************************************************************************
* 函 数 名  : mdrv_nv_flush
*
* 功能描述  : 将内存中的nv数据刷到flash 文件系统中
*
* 输入参数  :
* 输出参数  : 无
*
* 返 回 值  : OK
*
* 修改记录  : Yangzhi create
*
*****************************************************************************/
unsigned int mdrv_nv_flush(void);

/*****************************************************************************
* 函 数 名  : mdrv_nv_restore_result
*
* 功能描述  :  恢复结果检查
*
* 输入参数  :
* 输出参数  : 无
*
* 返 回 值  : OK
*
* 修改记录  : Yangzhi create
*
*****************************************************************************/
unsigned int mdrv_nv_restore_result(void);


#define NV_Backup()	                                (0)
#define NV_SpecialNvIdBackup(a,b,c)                 (0)
#define NV_RestoreManufactureExt()                  (1)
#define NV_BackupCheck()                            (0)
#define NVM_BackUpFNV()                             (0)
#define NVM_RevertFNV()                             (0)
#define NV_RestoreAll()                             (0)
#define NV_RestoreManufactureDefault()              (0)

#define NVM_Flush()                                 mdrv_nv_flush()
#define NV_Flush()	                                mdrv_nv_flush()
#define NV_QueryRestoreResult()                     mdrv_nv_restore_result()

#ifdef __cplusplus
}
#endif
#endif
