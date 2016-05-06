#ifndef __MSP_DIAG_H__
#define __MSP_DIAG_H__

#ifdef __cplusplus
extern "C"
{
#endif
#include <msp_diag_comm.h>
#include <vos.h>

typedef VOS_UINT32 (*DIAG_GTR_DATA_RCV_PFN)(VOS_UINT32 ulGtrDtaSize, VOS_VOID* pGtrData);

/*****************************************************************************
 Function Name   : DIAG_GtrRcvCallBackReg
 Description     :自动化测试上报接口，供PS调用
 Input           :DIAG_GTR_DATA_RCV_PFN pfnGtrRcv
 Output          : None
 Return          : VOS_UINT32

 History         :
    1.w00182550      2012-12-26  Draft Enact

*****************************************************************************/
VOS_VOID DIAG_GtrRcvCallBackReg(DIAG_GTR_DATA_RCV_PFN pfnGtrRcv);

/*****************************************************************************
 Function Name   : DIAG_SocpPowerOn
 Description     : SOCP上电
 Input           : None
 Output          : None
 Return          : VOS_UINT32 0:成功   0xFFFFFFFF: 失败

 History         :
    1.y00228784     2012-12-26  Draft Enact

*****************************************************************************/
VOS_UINT32 DIAG_SocpPowerOn(VOS_VOID);

/*****************************************************************************
 Function Name   : DIAG_DspInitFinished
 Description     : 通知DIAG LDSP初始化完成
 Input           : None
 Output          : None
 Return          : VOS_VOID

 History         :
    1.y00228784     2012-12-26  Draft Enact

*****************************************************************************/
VOS_VOID DIAG_DspInitFinished(VOS_VOID);

#ifdef __cplusplus
}
#endif
#endif
