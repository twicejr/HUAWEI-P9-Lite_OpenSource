#ifndef __VFMW_REGULATOR_H__
#define __VFMW_REGULATOR_H__

#include "hi_type.h"

HI_S32  Venc_Regulator_Init(struct platform_device *pdev);
HI_VOID Venc_Regulator_Deinit(struct platform_device *pdev);
HI_S32  Venc_Regulator_Enable(HI_VOID);
HI_S32  Venc_Regulator_Disable(HI_VOID);

#endif

