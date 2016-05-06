
/******************************************************************************

  版权所有 (C), 2001-2011, 华为技术有限公司

******************************************************************************
    文 件 名   : vdmv300plus_hal.h
    版 本 号   : 初稿
    作    者   :
    生成日期   :
    最近修改   :
    功能描述   : VDMV300plus硬件抽象


  修改历史   :
    1.日    期 : 2009-03-04
    作    者   :
    修改内容   :

******************************************************************************/

#ifndef __VDM_HAL_V400R004__HEVC_H__
#define __VDM_HAL_V400R004__HEVC_H__

#include "basedef.h"
#include "mem_manage.h"

#ifdef __cplusplus
extern "C" {
#endif

SINT32 HEVCHAL_V400R004_InitHal(VDMHAL_HWMEM_S *pHwMem);
SINT32 HEVCHAL_V400R004_StartDec(HEVC_DEC_PIC_PARAM_S *pParam, SINT32 VdhId);

#ifdef __cplusplus
}
#endif


#endif //__VDM_HAL_HEVC_H__
