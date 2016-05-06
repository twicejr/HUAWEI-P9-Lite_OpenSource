#include <mdrv.h>
#include "bsp_misc.h"

#ifdef __cplusplus
extern "C"
{
#endif

#ifdef CONFIG_SC
/*
* Function   : mdrv_misc_scbackup_ext_write
* Discription: c core nv init,this phase build upon the a core kernel init,
*              this phase after icc init,this phase ensure to use all nv api normal
*              start at this phase ,ops global ddr need spinlock
* Parameter  : none
* Output     : result
* History    : 
*/
int mdrv_misc_scbackup_ext_write(unsigned char *pRamAddr, unsigned int len)
{
    return (int)bsp_sc_backup((u8*)pRamAddr, (u32)len);   
}

/*
* Function   : mdrv_misc_scbackup_ext_read
* Discription: c core nv init,this phase build upon the a core kernel init,
*              this phase after icc init,this phase ensure to use all nv api normal
*              start at this phase ,ops global ddr need spinlock
* Parameter  : none
* Output     : result
* History    : 
*/
int mdrv_misc_scbackup_ext_read(unsigned char *pRamAddr, unsigned int len)
{
    return (int)bsp_sc_restore((u8*)pRamAddr, (u32)len);
}
#else
int mdrv_misc_scbackup_ext_write(unsigned char *pRamAddr, unsigned int len)
{
    return MDRV_OK;
}
int mdrv_misc_scbackup_ext_read(unsigned char *pRamAddr, unsigned int len)
{
    return MDRV_OK;
}
#endif

#ifdef __cplusplus
}
#endif

