#ifndef __DRV_VENC_H__
#define __DRV_VENC_H__

#include <linux/kthread.h>

#include "drv_venc_efl.h"
#include "drv_venc_ioctl.h"
#include "hi_unf_venc.h"
#include <linux/hisi/hisi-iommu.h>
#include <linux/iommu.h>

#ifdef __cplusplus
 #if __cplusplus
extern "C" {
 #endif
#endif

#define GET_VENC_CHHANDLE(u32ChanId) (u32ChanId | (HI_ID_VENC << 16))

#define D_VENC_CHECK_PTR(ptr) \
    do {\
        if (HI_NULL == ptr)\
        { \
            printk("PTR '%s' is NULL.\n", # ptr); \
            return HI_ERR_VENC_NULL_PTR;           \
        }  \
    } while (0)

#define D_VENC_CHECK_CHN(u32VeChn) \
    do {if (u32VeChn >= VENC_MAX_CHN_NUM){    \
            return HI_ERR_VENC_CHN_NOT_EXIST;           \
        }                                          \
    } while (0)


typedef struct hiVENC_PROC_WRITE_S
{
    struct file *  fpSaveFile;    /* file pointer */
	HI_CHAR YUVFileName[64];
	HI_CHAR StreamFileName[64];
    HI_U32  u32FrameModeCount;    /* number of saved frame, used in frame mode */
    HI_BOOL bTimeModeRun;         /* run tag in time mode */
    HI_BOOL bFrameModeRun;        /* run tag in frame mode */
	HI_BOOL bSaveYUVFileRun;
} VENC_PROC_WRITE_S;

typedef struct tagOPTM_VENC_CHN_S
{
    HI_U32                 u32UID;
    HI_BOOL                bEnable;
	HI_BOOL                bFrameBufMng;
    HI_HANDLE              hSource;
    HI_HANDLE              hVEncHandle;
    HI_HANDLE              hUsrHandle;     //user handle will not change after pmoc
    HI_U32                 u32SrcUser;
    HI_U32                 StrmBufAddr;
    HI_U32                 StrmBufSize;
    HI_UNF_VENC_CHN_ATTR_S stChnUserCfg;
	HI_U32                 u32SliceSize;   /* use to record the slice size in unit of MB line*/
    VeduEfl_NALU_S         stChnPacket;    /* use to release the stream */
    struct timeval stTimeStart;
    HI_U32 u32FrameNumLastInput;           /* use as a static value, save last encoded frame number */
    HI_U32 u32FrameNumLastEncoded;         /* use as a static value, save last input frame number */
    HI_U32 u32TotalByteLastEncoded;        /* use as a static value, save last encoded total byte */
    HI_U32 u32LastSecInputFps;             /* input frame rate of last second, source may be VI or VO */
    HI_U32 u32LastSecEncodedFps;           /* encoded frame rate of last second by frame control */
    HI_U32 u32LastSecKbps;                 /* bit rate of last second, count as Kbps */
    HI_U32 u32LastSecTryNum;
    HI_U32 u32LastTryNumTotal;
	HI_U32 u32LastSecOKNum;
    HI_U32 u32LastOKNumTotal;
    HI_U32 u32LastSecPutNum;
    HI_U32 u32LastPutNumTotal;
    struct file *pWhichFile;

	VeduEfl_SrcInfo_S     stSrcInfo;
	VENC_PROC_WRITE_S     stProcWrite;

	HI_U8 bhavecalc;//Md5º∆À„≈–∂œ”√µΩ

} OPTM_VENC_CHN_S;

typedef struct tagVENC_SOURCE_HANDLE_S
{
    HI_U32        u32UserId;
    VE_IMAGE_FUNC pfGetImage;
    VE_IMAGE_FUNC pfPutImage;
} VENC_SOURCE_HANDLE_S;


extern HI_U32* pResetReg;
extern struct iommu_domain* g_hisi_mmu_domain; //conflict name :g_hisi_domain;
extern HI_U32  pre_enc_protocol;
extern HI_HANDLE h_pre_enc_handle;
extern HI_U32 cur_handle_num;
extern HI_U32 b_Regular_down_flag;

HI_VOID VENC_DRV_BoardInit(HI_VOID);
HI_VOID VENC_DRV_BoardDeinit(HI_VOID);


HI_S32 VENC_DRV_CreateChn(HI_HANDLE *phVencChn, HI_UNF_VENC_CHN_ATTR_S *pstAttr,
                      VENC_CHN_INFO_S *pstVeInfo, struct file  *pfile);


HI_S32	VENC_DRV_DestroyChn( HI_HANDLE hVencChn);
HI_S32	VENC_DRV_StartReceivePic(HI_HANDLE EncHandle);
HI_S32	VENC_DRV_StopReceivePic(HI_HANDLE EncHandle);
HI_S32 VENC_DRV_SetAttr(HI_HANDLE EncHandle, HI_UNF_VENC_CHN_ATTR_S *pstAttr,VENC_CHN_INFO_S *pstVeInfo);
HI_S32	VENC_DRV_GetAttr(HI_HANDLE EncHandle, HI_UNF_VENC_CHN_ATTR_S *pstAttr);
HI_S32	VENC_DRV_RequestIFrame(HI_HANDLE EncHandle);
HI_S32 VENC_DRV_ProcAdd(HI_HANDLE hVenc,HI_U32 u32ChnID);   /**/
HI_VOID VENC_DRV_ProcDel(HI_HANDLE hVenc,HI_U32 u32ChnID);
HI_S32 VENC_DRV_MemProcAdd(HI_VOID);
HI_VOID VENC_DRV_MemProcDel(HI_VOID);
#ifdef __cplusplus
 #if __cplusplus
}
 #endif
#endif /* __cplusplus */

#endif //__DRV_VENC_H__
