
#include <linux/module.h>
#include <linux/printk.h>
#include <linux/kern_levels.h>
#include "vfmw_ext.h"
#ifdef HI_TVP_SUPPORT
#include "tvp_adapter.h"
#endif

#ifdef HI_ADVCA_FUNCTION_RELEASE
#define ModPrint(format,arg...)    ({do{}while(0);0;})
#else
#define ModPrint(format,arg...) \
	do { \
		    printk(KERN_ALERT format, ## arg); \
	} while (0)
#endif

#ifdef HI_TVP_SUPPORT
static VFMW_EXPORT_FUNC_S s_VfmwExportFuncs =
{
    .pfnVfmwOpenModule       = TVP_VDEC_OpenModule,
    .pfnVfmwExitModule       = TVP_VDEC_ExitModule,
    .pfnVfmwInit             = TVP_VDEC_Init,
    .pfnVfmwExit             = TVP_VDEC_Exit,
    .pfnVfmwControl          = TVP_VDEC_Control,
    .pfnVfmwSuspend          = TVP_VDEC_Suspend,
    .pfnVfmwResume           = TVP_VDEC_Resume,
};
#else
VFMW_EXPORT_FUNC_S s_VfmwExportFuncs =
{
    .pfnVfmwOpenModule       = VDEC_OpenModule,
    .pfnVfmwExitModule       = VDEC_ExitModule,
    .pfnVfmwInit             = VDEC_Init,     
    .pfnVfmwExit             = VDEC_Exit,
    .pfnVfmwControl          = VDEC_Control,
    .pfnVfmwSuspend          = VDEC_Suspend,
    .pfnVfmwResume           = VDEC_Resume,
};
#endif

HI_S32 VFMW_GetFunction(VFMW_EXPORT_FUNC_S **ppVfmwExportFuncs)
{
    *ppVfmwExportFuncs = &s_VfmwExportFuncs;
	
    return HI_SUCCESS;
}

EXPORT_SYMBOL(VFMW_GetFunction);


HI_S32 VFMW_DRV_Init(HI_VOID)
{
    VDEC_OpenModule();   // open proc
    
#ifdef HI_TVP_SUPPORT
    TVP_VDEC_OpenModule();
#endif

    return HI_SUCCESS;
}

HI_VOID VFMW_DRV_Exit(HI_VOID)
{
    VDEC_ExitModule();   // close proc
    
#ifdef HI_TVP_SUPPORT
    TVP_VDEC_ExitModule();
#endif
    
    return;
}

HI_S32 VFMW_DRV_ModInit(HI_VOID)
{
    HI_S32 ret;
    
    ret = VFMW_DRV_Init();
    if (HI_SUCCESS != ret)
    {
        ModPrint("VFMW_DRV_Init failed.\n");
        return -1;
    }
    
#ifdef MODULE
    ModPrint("Load hi_vfmw.ko (%d) success.\n", VFMW_VERSION_NUM);
#endif

    return 0;
}

HI_VOID VFMW_DRV_ModExit(HI_VOID)
{
    VFMW_DRV_Exit();
    
#ifdef MODULE
    ModPrint("Unload hi_vfmw.ko (%d) success.\n", VFMW_VERSION_NUM);
#endif

    return ;
}

module_init(VFMW_DRV_ModInit);
module_exit(VFMW_DRV_ModExit);

MODULE_AUTHOR("HISILICON");
MODULE_LICENSE("GPL");


