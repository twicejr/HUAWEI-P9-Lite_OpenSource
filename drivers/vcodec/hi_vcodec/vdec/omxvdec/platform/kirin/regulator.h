

#ifndef __VDEC_REGULATOR_H__
#define __VDEC_REGULATOR_H__

#include "hi_type.h"

typedef enum {
	CLK_RATE_LOW = 0,
	CLK_RATE_HIGH,
	CLK_RATE_BUTT,
}eCLK_RATE;

static const struct of_device_id Hisi_Vdec_Match_Table[] = {
	{ .compatible = "hisi,kirin960-vdec", },
	{ }
};

HI_S32  VDEC_Regulator_Initialize(HI_VOID *pParam);
HI_VOID VDEC_Regulator_DeInitialize(HI_VOID *pParam);
HI_S32  VDEC_Regulator_Enable(HI_VOID);
HI_S32  VDEC_Regulator_Disable(HI_VOID);
HI_S32  VDEC_Regulator_SetClkRate(struct device *pdev, eCLK_RATE eClkRate);
HI_VOID VDEC_Regulator_Read_Proc(HI_VOID *p, HI_VOID *v);

#endif

