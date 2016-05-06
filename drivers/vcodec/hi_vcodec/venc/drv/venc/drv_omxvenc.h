#ifndef __DRV_OMXVENC_H__
#define __DRV_OMXVENC_H__

#include "drv_venc.h"

#ifdef __cplusplus
 #if __cplusplus
extern "C" {
 #endif
#endif

HI_S32 VENC_DRV_QueueFrame_OMX(HI_HANDLE hVencChn, venc_user_buf *pstFrameInfo );

HI_S32 VENC_DRV_QueueStream_OMX(HI_HANDLE hVencChn, venc_user_buf *pstFrameInfo );

HI_S32 VENC_DRV_GetMessage_OMX(HI_HANDLE hVencChn, venc_msginfo *pmsg_info );

HI_S32 VENC_DRV_MMZ_Map_OMX(HI_HANDLE hVencChn, HI_MMZ_BUF_S *pMMZbuf );
HI_S32 VENC_DRV_MMZ_UMMap_OMX(HI_HANDLE hVencChn, HI_MMZ_BUF_S *pMMZbuf );

HI_S32 VENC_DRV_FlushPort_OMX(HI_HANDLE hVencChn, HI_U32 u32PortIndex);

HI_S32 VENC_DRV_MMZ_Alloc_OMX(HI_HANDLE hVencChn, HI_MMZ_BUF_S *pMMZbuf );


#ifdef __cplusplus
 #if __cplusplus
}
 #endif
#endif /* __cplusplus */

#endif //__DRV_OMXVENC_H__
