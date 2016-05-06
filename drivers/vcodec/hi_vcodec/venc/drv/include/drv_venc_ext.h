#ifndef __DRV_VENC_EXT_H__
#define __DRV_VENC_EXT_H__

#include "hi_drv_video.h"

#ifdef __cplusplus
 #if __cplusplus
extern "C" {
 #endif
#endif

/* source information.
   venc will get / release frame or send private info to sourec by function pointer */
typedef HI_S32  (*FN_VENC_GET_FRAME)(HI_HANDLE handle, HI_DRV_VIDEO_FRAME_S *pstImage);
typedef HI_S32  (*FN_VENC_PUT_FRAME)(HI_HANDLE handle, HI_DRV_VIDEO_FRAME_S *pstImage);
typedef HI_S32  (*FN_VENC_CHANGE_INFO)(HI_HANDLE handle, HI_U32 u32Width,HI_U32 u32Height);

typedef struct hiDRV_VENC_SRC_INFO_S
{
    HI_HANDLE hSrc;
    FN_VENC_GET_FRAME   pfAcqFrame;
    FN_VENC_PUT_FRAME   pfRlsFrame;
    FN_VENC_CHANGE_INFO pfChangeInfo;

    HI_U32    u32Resrve0;
    HI_U32    u32Resrve1;
}HI_DRV_VENC_SRC_INFO_S;

typedef HI_S32  (*FN_VENC_QueueFrame)(HI_HANDLE handle, HI_DRV_VIDEO_FRAME_S *pstFrame);
typedef HI_VOID (*FN_VENC_WakeUpThread)(HI_VOID);

typedef HI_S32  (*FN_VENC_Resume)(HI_VOID);
typedef HI_S32 (*FN_VENC_Suspend)(HI_VOID);

typedef struct
{
	FN_VENC_WakeUpThread pfnVencWakeUpThread;
	FN_VENC_Resume       pfnVencResume;
    FN_VENC_Suspend      pfnVencSuspend;

} VENC_EXPORT_FUNC_S;

HI_S32 VENC_DRV_ModInit(HI_VOID);
HI_VOID VENC_DRV_ModExit(HI_VOID);

#ifdef __cplusplus
 #if __cplusplus
}
 #endif
#endif

#endif //__DRV_VENC_EXT_H__
