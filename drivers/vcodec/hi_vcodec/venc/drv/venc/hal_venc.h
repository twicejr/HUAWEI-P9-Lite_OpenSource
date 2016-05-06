#ifndef __HAL_VENC_H__
#define __HAL_VENC_H__

#include "hi_type.h"
#include "drv_venc.h"
#include "drv_venc_efl.h"
#include "Vedu_RegAll.h"
#ifdef __cplusplus
 #if __cplusplus
extern "C" {
 #endif
#endif

typedef unsigned long VEDU_LOCK_FLAG;

HI_VOID VENC_HAL_ClrAllInt(S_HEVC_AVC_REGS_TYPE *pVeduReg);
HI_VOID VENC_HAL_DisableAllInt(S_HEVC_AVC_REGS_TYPE *pVeduReg);
HI_VOID VENC_HAL_ReadReg(HI_HANDLE EncHandle);
HI_VOID VeduHal_ReadReg_Venc(VeduEfl_EncPara_S *pEncPara);
HI_VOID VENC_HAL_CfgReg (HI_HANDLE EncHandle);
HI_VOID VENC_HAL_ResetReg(HI_VOID);
HI_VOID VeduHal_CfgReg(HI_HANDLE EncHandle);
HI_VOID VeduHal_CfgRegSimple(HI_HANDLE EncHandle);
HI_VOID VENC_HAL_ConfigMMU(S_HEVC_AVC_REGS_TYPE *pVeduReg);
HI_VOID VENC_HAL_CfgAXIReg(HI_HANDLE EncHandle, HI_BOOL bAXI_en);
HI_VOID VENC_HAL_ReadRegSimple(HI_HANDLE EncHandle);

#ifdef __cplusplus
 #if __cplusplus
}
 #endif
#endif

#endif //__HAL_VENC_H__
