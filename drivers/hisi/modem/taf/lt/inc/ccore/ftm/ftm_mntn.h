#ifndef _FTM_MNTN_H
#define _FTM_MNTN_H

#ifdef __cplusplus
extern "C"{
#endif

#include "v_lib.h"
#include "v_msg.h"

VOS_INT32 ftm_mntn_printf(const VOS_CHAR *fmt, ... );
VOS_VOID  ftm_mntn_datahook(VOS_UINT32 pid1, VOS_UINT32 pid2, VOS_UINT32 length, VOS_UINT8 *data);



#ifdef __cplusplus
}
#endif

#endif

