#ifndef __MSP_DIAG_H__
#define __MSP_DIAG_H__

#ifdef __cplusplus
extern "C"
{
#endif
#include <msp_diag_comm.h>
#include <vos.h>

typedef VOS_UINT32 (*DIAG_GTR_DATA_RCV_PFN)(VOS_UINT32 ulGtrDtaSize, VOS_VOID* pGtrData);


VOS_VOID DIAG_GtrRcvCallBackReg(DIAG_GTR_DATA_RCV_PFN pfnGtrRcv);


VOS_UINT32 DIAG_SocpPowerOn(VOS_VOID);


VOS_VOID DIAG_DspInitFinished(VOS_VOID);

#ifdef __cplusplus
}
#endif
#endif
