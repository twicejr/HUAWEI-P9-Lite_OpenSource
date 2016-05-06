

#ifndef __HI_DRV_VENC_H__
#define __HI_DRV_VENC_H__

#include "hi_unf_venc.h"

#ifdef __cplusplus
 #if __cplusplus
extern "C" {
 #endif
#endif /* End of #ifdef __cplusplus */

#define VENC_MAX_CHN_NUM 8

/*********************************************************************/
/* for omxvenc struction                                             */
/*********************************************************************/
/* VENC msg response types */
#define VENC_MSG_RESP_BASE 		        0xA0000
#define VENC_MSG_RESP_START_DONE        (VENC_MSG_RESP_BASE + 0x1)
#define VENC_MSG_RESP_STOP_DONE        	(VENC_MSG_RESP_BASE + 0x2)
#define VENC_MSG_RESP_PAUSE_DONE        (VENC_MSG_RESP_BASE + 0x3)
#define VENC_MSG_RESP_RESUME_DONE	    (VENC_MSG_RESP_BASE + 0x4)
#define VENC_MSG_RESP_FLUSH_INPUT_DONE  (VENC_MSG_RESP_BASE + 0x5)
#define VENC_MSG_RESP_FLUSH_OUTPUT_DONE (VENC_MSG_RESP_BASE + 0x6)
#define VENC_MSG_RESP_INPUT_DONE        (VENC_MSG_RESP_BASE + 0x7)          //改帧可以还
#define VENC_MSG_RESP_OUTPUT_DONE       (VENC_MSG_RESP_BASE + 0x8)          //已经填满?
#define VENC_MSG_RESP_MSG_STOP_DONE	    (VENC_MSG_RESP_BASE + 0x9)

typedef struct venc_chan_cfg_s {
    HI_U32 protocol;      /* VEDU_H264, VEDU_H265 */
    HI_U32 frame_width;    /* width	in pixel, 96 ~ 2048 */
    HI_U32 frame_height;   /* height in pixel, 96 ~ 2048 */
	HI_UNF_H264_PROFILE_E   VencProfile;

    HI_U32 rotation_angle; /* venc don't care */

    HI_U32 priority;
    HI_U32 streamBufSize;

    HI_BOOL bSlcSplitEn;    /* 0 or 1, slice split enable */
    HI_U32 Gop;
    HI_U16 QuickEncode;

    HI_U32 TargetBitRate;
    HI_U32 TargetFrmRate;
    HI_U32 InputFrmRate;

    HI_U32 MinQP;
    HI_U32 MaxQP;
	////////////////////////////////////////// just for omx priv
	HI_U32 h264Level;
	HI_U32 ControlRateType;    //match the enum OMX_VIDEO_CONTROLRATETYPE

	HI_UNF_HEVC_PROFILE_E	VencHevcProfile;
	HI_U32 h265Level;

	HI_UNF_VCODEC_CROP_INFO_S  CropInfo;
	HI_UNF_VCODEC_SCALE_INFO_S ScaleInfo;
	HI_UNF_VCODEC_ROI_INFO_S ROIInfo;

	HI_BOOL bEnableCrop;
	HI_BOOL bEnableScale;

	HI_BOOL bSkipFrame;
	HI_U32 	ui32nSlices;
	HI_BOOL	bLowPowerMode;
	HI_BOOL	bInputLowDelayMode;
	HI_BOOL	bOutputLowDelayMode;
	HI_BOOL	bEnableROI;

	HI_U32  uiYUVStoreMode;

	HI_U32	bMMUByPass;
	HI_U32  WideToNarrowEn;
}venc_chan_cfg;

enum venc_port_dir {
	PORT_DIR_INPUT,
	PORT_DIR_OUTPUT,
	PORT_DIR_BOTH = 0xFFFFFFFF
};

typedef struct venc_metadata_buf_s {
	void  *bufferaddr;     //虚拟地址
    HI_U32 bufferaddr_Phy;
	HI_U32 vir2phy_offset;   //kernel VirAddr - PhyAddr
	HI_U32 buffer_size;    //buffer alloc size
	HI_U32 offset_YC;    //YC分量的偏移
    HI_U32 offset_YCr;   //YCr offset
	HI_U32 offset;
	HI_U32 data_len;      //filled len
	void *ion_handle; /*used for ion*/
}venc_metadata_buf;

typedef struct venc_user_buf_s {

	HI_U64 bufferaddr;
	HI_U64 bufferaddr_Phy;
	HI_U64 kernelbufferaddr;	 //kernel VirAddr - PhyAddr

	HI_U32 buffer_size;    //buffer alloc size
	HI_U32 offset_YC;    //YC分量的偏移
	HI_U32 offset_YCr;   //YCr offset
	HI_U32 offset;
	HI_U32 data_len;      //filled len

	HI_U32 strideY;
	HI_U32 strideC;

	HI_U32 store_type;
	HI_U32 sample_type;
	HI_U32 package_sel;
	HI_U64 timestamp;
	HI_U32 flags;
	HI_U32 bEOS;//add by ljh

	HI_U32 picWidth;
	HI_U32 picHeight;
	enum venc_port_dir dir;

	HI_U32 MetaDateFlag;
	HI_U64 ion_handle; /*used for ion*/
	HI_S32 pmem_fd;

	unsigned long long mmaped_size;

	HI_U64 client_data;

	HI_U64 MMU_Mem_addr;
	HI_U32 mmu_bypass_flag;
   	HI_S32 share_fd;
}venc_user_buf;

typedef struct venc_msginfo_s {
	HI_U32 status_code;          //记录操作的返回值(success/failure)
	HI_U32 msgcode;              //自定义的上行消息返回值，定义在此处
	venc_user_buf buf;     //
	HI_U32 msgdatasize;
}venc_msginfo;

#define OMXVENC_BUFFERFLAG_EOS 0x00000001
#define OMXVENC_BUFFERFLAG_STARTTIME 0x00000002
#define OMXVENC_BUFFERFLAG_DECODEONLY 0x00000004
#define OMXVENC_BUFFERFLAG_DATACORRUPT 0x00000008
#define OMXVENC_BUFFERFLAG_ENDOFFRAME 0x00000010
#define OMXVENC_BUFFERFLAG_SYNCFRAME 0x00000020
#define OMXVENC_BUFFERFLAG_EXTRADATA 0x00000040
#define OMXVENC_BUFFERFLAG_CODECCONFIG 0x00000080

#ifdef __cplusplus
 #if __cplusplus
}
 #endif
#endif

#endif //__HI_DRV_VENC_H__
