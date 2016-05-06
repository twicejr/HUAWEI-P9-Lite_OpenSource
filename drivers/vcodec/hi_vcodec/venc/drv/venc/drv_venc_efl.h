#ifndef __DRV_VENC_EFL_H__
#define __DRV_VENC_EFL_H__

#include "hi_type.h"
#include "drv_venc_buf_mng.h"
//#include "hi_unf_common.h"
#include "hi_drv_video.h"
#include "drv_venc_queue_mng.h"
#include <linux/delay.h>

#include "hi_drv_mem.h"

#ifdef __cplusplus
 #if __cplusplus
extern "C" {
 #endif
#endif


#define VEDU_TR_STEP (1)
/*************************************************************************************/
#define MAX_VEDU_CHN (8)
#define MAX_VEDU_QUEUE_NUM (32)  //l00214825 0326 多slice，修改大
#define MSG_QUEUE_NUM     (100)
#define INVAILD_CHN_FLAG   (-1)
#define VEDU_MAX_ENC_WIDTH   (4096)
#define VEDU_MIN_ENC_WIDTH   (144)
#define VEDU_MAX_ENC_HEIGHT  (2160)
#define VEDU_MIN_ENC_HEIGHT  (144)
#if 0
#define VEDU_REG_BASE_ADDR  (0xe8900000) //k3 寄存器地址 l00214825
#else
#define VEDU_REG_BASE_ADDR  (0xe8800000) //k3 寄存器地址 l00214825
#endif
#define VEDU_REG_LENGTH    (0x10000) //寄存器长度


//rc start
#define MAX_FRAME_RATE (240) //支持最大帧率
#define RC_MAX_INTRA_LOADSIZE (2)
#define RC_MAX_INTER_LOADSIZE (5)
#define I_RATIO_NUM (5) //I比重数
#define SMALL_MOVE_DET_THRESH     (60)
#define LARGE_MOVE_DET_THRESH     (120)
#define STATIC_FRAME_NUM          (3)
#define RC_QP_MAX          (43)
#define RC_QP_MIN          (15)
//end

#define  SAO_FRAME_REFRESH     (4)
#define  SAO_RATIO_OFF_LUMA    (60)
#define  SAO_RATIO_OFF_CHROMA  (75)

#define VPS_MAX_LEN        (200)
#define SPS_MAX_LEN        (200)
#define PPS_MAX_LEN        (200)


/*******************************************************************/

#define __VEDU_NEW_RC_ALG__

//调试函数
#define pos()  printk("***### %s: L%d\n", __FUNCTION__, __LINE__ )

#define SWAP(a,b) {HI_U32 c;c=a;a=b;b=c;}
#define ALIGN_UP(val, align) ( (val+((align)-1))&~((align)-1) )

#define D_VENC_ALIGN_UP(val, align) ( (val+((align)-1))&~((align)-1) )
typedef HI_S32 (*VE_IMAGE_FUNC)(HI_S32 handle, HI_DRV_VIDEO_FRAME_S *pstImage);
typedef HI_S32 (*VE_IMAGE_OMX_FUNC)(HI_S32 handle, venc_user_buf *pstImage);
typedef HI_S32 (*VE_CHANGE_INFO_FUNC)(HI_HANDLE handle, HI_U32 u32Width,HI_U32 u32Height);
typedef HI_S32 (*VE_DETACH_FUNC)(HI_HANDLE handle, HI_HANDLE hSrc);

enum {
    VEDU_H265	= 0,
    VEDU_H264   = 1
};

enum {
	VEDU_H264_BASELINE_PROFILE = 0,
	VEDU_H264_MAIN_PROFILE	   = 1,
	VEDU_H264_EXTENDED_PROFILE = 2,
	VEDU_H264_HIGH_PROFILE     = 3,
	VEDU_H264_PROFILE_BUTT     = 4
};

enum {
	VEDU_YUV420	= 0,
	VEDU_YUV422	= 1,
	VEDU_YUV444 = 2
};

enum {
	VEDU_SEMIPLANNAR = 0,
	VEDU_PLANNAR	 = 1,
	VEDU_PACKAGE     = 2
};



typedef struct
{
    HI_U32 uiMaxSubLayersMinus1;
    HI_U32 uiMaxDecPicBufferMinus1[2];
    HI_U32 uiMaxNumReorderPics[2];
    HI_U32 uiMaxLatencyIncreasePlus1[2];
} VeduEfl_H265e_VPS_S;

typedef struct
{
    HI_U32  ProfileIDC;
    HI_U32  uiPicWidthInLumaSamples;
    HI_U32  uiPicHeightInLumaSamples;
    HI_U32  bPicCroppingFlag;
    HI_U32  uiPicCropLeftOffset;
    HI_U32  uiPicCropRightOffset;
    HI_U32  uiPicCropTopOffset;
    HI_U32  uiPicCropBottomOffset;
    HI_U32  uiSPSMaxSubLayersMinus1;
    HI_U32  bPcmEnable;
    HI_U32  iPcmLog2MaxSize;
    HI_U32  bSAOEnabledFlag;
    HI_U32  iPcmLog2MinSize;
    HI_U32  bPcmFilterDisable;
    HI_U32  sps_temporal_mvp_enable_flag;
    HI_U32  uiNumNegativePics;
    HI_U32  bStrongIntraSmoothingFlag;
} VeduEfl_H265e_SPS_S;


typedef struct
{
    HI_U32 bCUQpDeltaEnable;
    HI_U32 constrained_intra_pred_flag;
    HI_S32 iCbQpOffset;
    HI_S32 iCrQpOffset;
    HI_U32 bTilesEnabledFlag;
    HI_U32 bEntropyCodingSyncEnabled;
    HI_U32 InLoopFilterCrossTiles;
    HI_U32 bSliceLFAcrossSlicepps;

    HI_U32 InLoopFilterCrossSlices;
    HI_U32 bDBFilterCtlPresent;
    HI_U32 bPicDisableDBFilter;
    HI_S32 iBetaOffsetDiv2;
    HI_S32 iTcOffsetDiv2;
    HI_U32 bPicScalingListPresent;
}VeduEfl_H265e_PPS_S;

typedef struct
{
    HI_U32 bFirstSliceInPic;
    HI_U32 eSliceType;
    HI_U32 iSliceAddr;
    HI_U32 uiPocLsb;
    HI_U32 bSpsTemporalMvpEnableFlag;
    HI_U32 bSAOEnabledFlag;
    HI_U32 bSliceSaoLuma;
    HI_U32 bSliceSaoChroma;
    HI_U32 cabac_init_flag;
    HI_U32 five_minus_max_num_merge_cand;
    HI_S32 iSliceQPDelta;
    HI_U32 bDBFilterCtlPresent;
    HI_U32 bDBFilterOverrideEnabled;
    HI_U32 bDFOverrideFlag;
    HI_U32 bSliceHeaderDisableDF;
    HI_S32 iBetaOffsetDiv2;
    HI_S32 iTcOffsetDiv2;
    HI_U32 bSliceLFAcrossSlice;
    HI_U32 frame_num;
    HI_U32 slice_type;
    HI_U32 NumRefIndex;
}VeduEfl_H265e_SlcHdr_S;


typedef struct
{
    HI_U32 ProfileIDC;
    HI_U32 FrameWidthInMb;
    HI_U32 FrameHeightInMb;
    HI_U8  FrameCropLeft;
    HI_U8  FrameCropRight;
    HI_U8  FrameCropTop;
    HI_U8  FrameCropBottom;
} VeduEfl_H264e_SPS_S;

typedef struct
{
    HI_U32  ConstIntra;
    //HI_S32  ChrQpOffset;
    HI_S32  CbQpOffset;
    HI_S32  CrQpOffset;
	HI_U32  H264HpEn;
    HI_U32  H264CabacEn;
    HI_S32 *pScale8x8;
} VeduEfl_H264e_PPS_S;

typedef struct
{
    HI_U32 slice_type; /* 0-P, 2-I */
    HI_U32 frame_num;
    HI_U32 NumRefIndex; /* 0 or 1 */
    HI_U32 idr_pic_id;
} VeduEfl_H264e_SlcHdr_S;

typedef struct
{
    HI_U32 Pframe;   /* 1-P, 0-I */
    HI_U32 TR;       /* temporal ref */
    HI_U32 Wframe;
    HI_U32 Hframe;
    HI_U32 SrcFmt;
    HI_U32 PicQP;
} VeduEfl_H263e_PicHdr_S;

typedef struct
{
    HI_U32 Wframe;
    HI_U32 Hframe;
} VeduEfl_MP4e_VOL_S;

typedef struct
{
    HI_U32 Pframe;        /* 1-P, 0-I */
    HI_U32 PicQP;
    HI_U32 Fcode;
} VeduEfl_MP4e_VopHdr_S;

typedef struct
{
    HI_U32 PacketLen;     /* 64 aligned */
    HI_U32 InvldByte;     /* InvalidByteNum */
    HI_U8  Type;
    HI_U8  bBotField;
    HI_U8  bField;
    HI_U8  bLastSlice;
    HI_U32 ChnID;
    HI_U32 PTS0;
    HI_U32 PTS1;
    HI_U32 Reserved[10];
} VeduEfl_NaluHdr_S;

typedef struct
{
    HI_HANDLE           handle;
    VE_IMAGE_FUNC       pfGetImage;
    VE_IMAGE_OMX_FUNC   pfGetImage_OMX;
    VE_IMAGE_FUNC       pfPutImage;
    VE_CHANGE_INFO_FUNC pfChangeInfo;
    VE_DETACH_FUNC      pfDetachFunc;
} VeduEfl_SrcInfo_S;

typedef struct
{
    // 记录venc获取帧存/码流次数(dequeue)，
    // 以及释放帧存/码流次数(fill buffer done empty buffer done)
    HI_U32 GetFrameNumTry;
    HI_U32 PutFrameNumTry;
    HI_U32 GetStreamNumTry;
    HI_U32 PutStreamNumTry;

    HI_U32 GetFrameNumOK;
    HI_U32 PutFrameNumOK;
    HI_U32 GetStreamNumOK;
    HI_U32 PutStreamNumOK;

    HI_U32 GetStreamNumInTaskTry;
    HI_U32 GetStreamNumInTaskOK;
    HI_U32 GetStreamNumInIsrTry;
    HI_U32 GetStreamNumInIsrOK;

    // 记录omx送入帧存/码流次数(queue)，(fill this buffer ,empty this buffer)
    HI_U32 QueueFrameNumTry;
    HI_U32 QueueFrameNumOK;
    HI_U32 QueueStreamNumTry;
    HI_U32 QueueStreamNumOK;

    HI_U32 FlushUndoFrameNum;
    HI_U32 FlushUndoStreamNum;

    HI_U32 RecvTotalFrameNum; //get + flush
    HI_U32 RecvTotalStreamNum; //get + flush

	HI_U32 StartVencNumInTask;
	HI_U32 StartVencNumInISR;

 /************************For Test **********************************/

 	HI_U32 LastTime;
 	HI_U32 ThisTime;
	HI_U32 OneCycletime;
	HI_U32 TotalOneCycletime;
	HI_U32 TotalFrame;
	HI_U32 ISRtaketime;
	HI_U32 ISRAvgtaketime;
	HI_U32 ISRtakeNum;

	HI_U32 Sleep2ISRtime;
	HI_U32 Enc2ISRtime;
	HI_U32 Sleeptime;
	HI_U32 starttime;
	HI_U32 OneCycletesttime;

	HI_U32 InputNum;
	HI_U32 OutputNum;
	HI_U32 EtbTime[5];//queueframe的时间 ms
	HI_U32 FbdTime[5];//QueueStreamNumOK 的时间 ms
	HI_U32 TotalEncTime;// 编码总时间 ( (FbdTime - EtbTime)* QueueStreamNumOK ) ms
	HI_U32 AvgEncTime;
	HI_U32 StartVencTime;//启动硬件编码时间 ms
	HI_U32 EndVencTime;//硬件编码结束时间 ms
	HI_U32 TotalIPVencTime;// 硬件编码总时间  ms
	HI_U32 AvgIPVencTime; //ms

	HI_U32 StartCfgRegTime;
	HI_U32 EndCfgRegTime;
	HI_U32 TotalCfgRegTime;// 硬件编码总时间  ms
	HI_U32 AvgCfgRegTime; //ms

	HI_U32 StartEncSHTime;
	HI_U32 EndEncSHTime;
	HI_U32 TotalEncSHTime;// 硬件编码总时间  ms
	HI_U32 AvgEncSHTime; //ms


	HI_U32 StartEncRCTime;
	HI_U32 EndEncRCTime;
	HI_U32 TotalEncRCTime;// 硬件编码总时间  ms
	HI_U32 AvgEncRCTime; //ms

	HI_U32 StartEncSHRCTime;
	HI_U32 EndEncSHRCTime;
	HI_U32 TotalEncSHRCTime;// 硬件编码总时间  ms
	HI_U32 AvgEncSHRCTime; //ms

	HI_U32 StartCfgRegTime1;
	HI_U32 EndCfgRegTime1;
	HI_U32 TotalCfgRegTime1;// 硬件编码总时间  ms
	HI_U32 AvgCfgRegTime1; //ms

	HI_U32 StartCfgRegTime2;
	HI_U32 EndCfgRegTime2;
	HI_U32 TotalCfgRegTime2;// 硬件编码总时间  ms
	HI_U32 AvgCfgRegTime2; //ms

	HI_U32 StartISRTime;
	HI_U32 EndISRTime;
	HI_U32 TotalISRTime;// 硬件编码总时间  ms
	HI_U32 AvgISRTime; //ms

    HI_U64 Total_VEDU_TIMER;
    HI_U64 Avg_VEDU_TIMER;

    HI_U64 Total_VEDU_IDLE_TIMER;
    HI_U64 Avg_VEDU_IDLE_TIMER;

	HI_U32 TotalISRTime1;// 硬件编码总时间  ms
	HI_U32 TotalISRTime2;// 硬件编码总时间  ms
	HI_U32 TotalISRTime3;// 硬件编码总时间  ms
	HI_U32 TotalISRTime4;// 硬件编码总时间  ms
	HI_U32 TotalISRTime5;// 硬件编码总时间  ms
	HI_U32 TotalISRTime6;// 硬件编码总时间  ms

/*************************************************************************/
    HI_U32 BufFullNum;
    //HI_U32 SkipFrmNum;
	HI_U32 FrmRcCtrlSkip;
	HI_U32 SamePTSSkip;
	HI_U32 QuickEncodeSkip;
	HI_U32 TooFewBufferSkip;
	HI_U32 ErrCfgSkip;

	HI_U32 QueueNum;
	HI_U32 DequeueNum;                  /*OMX Channel not use this data*/
	HI_U32 StreamQueueNum;              /*just OMX Channel use this data*/
    HI_U32 MsgQueueNum;

	HI_U32 UsedStreamBuf;
    HI_U32 StreamTotalByte;

    HI_U32 u32RealSendInputRrmRate;       /*use to record curent Input FrameRate in use*/
	HI_U32 u32RealSendOutputFrmRate;      /*use to record curent Output FrameRate in use*/
	HI_U32 u32FrameType;

	HI_U32 u32TotalPicBits;
	HI_U32 u32TotalEncodeNum;
	HI_U32 u32FrameIrqNum;
	HI_U32 u32SliceIrqNum;
	HI_U32 u32IrqNum;
	//HI_U32 u32AvgFrmRate;

} VeduEfl_StatInfo_S;

typedef struct
{
    HI_U32 Protocol;      /* VEDU_H264, VEDU_H263 or VEDU_MPEG4 */
	HI_U32 Profile;       /* H264 Profile*/
    HI_U32 FrameWidth;    /* width	in pixel, 96 ~ 2048 */
    HI_U32 FrameHeight;   /* height in pixel, 96 ~ 2048 */

    HI_U32 RotationAngle; /* venc don't care */

    HI_U32 PackageSel;
    HI_U32 Priority;
    HI_U32 streamBufSize; //size of just one frame  ljh

    HI_BOOL QuickEncode;
    HI_BOOL bSlcSplitEn;    /* 0 or 1, slice split enable */
	HI_BOOL bSlcSplitMod;   /* 0 or 1, 0:byte; 1:mb line */
    HI_U32 SplitSize;     /* <512 mb line @ H264, H263 don't care*/
    HI_U32 Gop;
    HI_U32 QLevel;        /* venc don't care */
} VeduEfl_EncCfg_S;

typedef struct
{
    HI_U32 BitRate;       /* 32k ~ 20M, bits per second */
    HI_U32 OutFrmRate;    /* 1 ~ InFrmRate */
    HI_U32 InFrmRate;     /* 1 ~ 30  */
    HI_U32   MaxQp;         /* H264: 0 ~ 51, Mpeg4: 1 ~ 31 */
    HI_U32   MinQp;         /* MinQp <= MaxQp */
	HI_U32   Gop;         /* for new RC ALG*/
	HI_U32	 ImgWidth;	   /* 64 ~ 4320, picture width*/
	HI_U32	 ImgHeight;    /* 64 ~ 2160, picture heitht*/
    HI_U32   SkipFrameEn;   /* 0 or 1 */

} VeduEfl_RcAttr_S;

typedef struct
{
    HI_VOID*   pVirtAddr[2];
    HI_U32     PhyAddr[2];
    HI_U32     SlcLen[2];  /* byte */
    HI_U32     PTS0;
    HI_U32     PTS1;
    HI_U32     bFrameEnd;
    HI_U32     NaluType;   /* 1(P),5(I),6(SEI),7(SPS) or 8(PPS), only used by H264	*/
	HI_U32     InvldByte;
} VeduEfl_NALU_S;

typedef struct
{
    HI_U32   Enable [8];    /* only used at H264  */
    HI_U32   AbsQpEn[8];
    HI_S32   Qp     [8];    /* -26 ~ 25 or 0 ~ 51 */
    HI_U32   Width  [8];    /* size in MB */
    HI_U32   Height [8];    /* size in MB */
    HI_U32   StartX [8];    /* size in MB */
    HI_U32   StartY [8];    /* size in MB */
	HI_U32   Keep   [8];

} VeduEfl_RoiAttr_S;

typedef struct
{
    HI_U32 osd_rgbfm;            /* 0 ~ 1 */
    HI_S32 osd_global_en   [8];
    HI_S32 osd_en          [8];
    HI_U32 osd_alpha0      [8];
    HI_U32 osd_alpha1      [8];
    HI_U32 osd_global_alpha[8];
    HI_U32 osd_x           [8]; /* pixel, 2 aligned */
    HI_U32 osd_y           [8]; /* pixel, 2 aligned */
    HI_U32 osd_w           [8]; /* pixel, 2 aligned */
    HI_U32 osd_h           [8]; /* pixel, 2 aligned */
    HI_U32 osd_addr        [8]; /* 16-byte aligned  */
    HI_U32 osd_stride      [8]; /* 64-byte aligned  */
    HI_U32 osd_layer_id    [8]; /* 0 ~ 7 */

    HI_S32 osd_absqp_en    [8]; /* only used at H264  */
    HI_S32 osd_qp          [8]; /* -26 ~ 25 or 0 ~ 51 */

    HI_U32 osd_invs_en     [8];
    HI_U32 osd_invs_w;          /* 1 ~ 4 */
    HI_U32 osd_invs_h;          /* 1 ~ 4 */
    HI_U32 osd_invs_thr;        /* 0 ~ 255 */
    HI_U32 osd_invs_mode;       /* 0 ~ 1 */
    HI_U32 curld_col2gray_en;
    HI_U32 curld_clip_en;
    HI_U32 curld_csc_mode;
    HI_U32 curld_rotate_mode;
    HI_U32 curld_read_interval;
    HI_U32 curld_lowdly_en;

}VeduEfl_OsdAttr_S;


typedef struct
{
	HI_U32 skipFrame;
    HI_U32 preskipFrame;

    HI_S32 MbNum;//number of mb
    HI_S32 FrmNumInGop; //frame number in gop minus 1
    HI_S32 FrmNumSeq;//frame number in sequence

 /*******bits***********/
    HI_S32 GopBits;//bits in gop
    HI_S32 AveFrameBits;//average bits of one frame

  //  HI_S32 GopFrameNum;//frame num in gop
    HI_S32 GopBitsLeft;//left bits in gop
    HI_S32 PreGopBitsLeft;//left bits in previous gop
    HI_S32 TotalBitsLeft;//left bits in sequence
    HI_S32 TotalTargetBitsUsedInGop;//total target bits used in gop
    HI_S32 TotalBitsUsedInGop;//actual total used bits used in gop

    HI_U32 AvePBits;//bits of P frame
    HI_U32 ConsAvePBits;//constant bits of P frame

    HI_S32 ITotalBits[6];//bits of previous six I frames
    HI_S32 PTotalBits[6];//bits of previous six P frames
    HI_S32 PreType;//I or P frame of previous frame, 1--I frame, 0--P frame'
    HI_S32 PPreQp[6];//Qp of previous six P frames
    HI_S32 IPreQp[6];//Qp of previous six I frames
    HI_S32 PreTargetBits;

    HI_S32 SaveBitsMode;//mode of saving bits

/*********IMB***********/
    HI_S32 NumIMBCurFrm;//number of I MB in current  frame
    HI_S32 NumIMB[6];//number of I MB of previous six frames
    HI_S32 AveOfIMB;//average number of I MB of previous six frames
    HI_S32 ImbRatioSeq;//sum of Imb Ratio in the sequence

/**********scence change detect *************/
    HI_S32 CurZone[16];//histogram of scene change detect of current frame
    HI_S32 PreZone[16];//histogram of scene change detect of previous frame
    HI_S32 SceneChangeFlag;
    HI_S32 PreSceneChangeFlag;
    HI_S32 AveDiffZone;//average of previous six differences
    HI_S32 DiffZone[6];//previous six differences

    HI_S32 SenChaNum[6];//sence change num of previous gop
    HI_S32 CurSenChaNum;//sence change num of current gop

    HI_S32 PreAveY;//average of Y of previous frame
    HI_S32 AverageY[6];//Y of previous six frame

/************RC Out**************/
    HI_S32 CurQp;
    HI_S32 TargetBits;

    HI_S32 InitialQp;
    HI_S32 PreQp;
    HI_S32 PreMeanQp;
    HI_S32 MeanQp[6];
    HI_S32 AveMeanQp;

    HI_S32 StillToMove;
    HI_S32 StillMoveNum;
    HI_S32 StillFrameNum;
    HI_S32 StillFrameNum2;

   /**********parameter set************/
    HI_S32 MinTimeOfP;
    HI_S32 MaxTimeOfP;
    HI_S32 DeltaTimeOfP;
    HI_S32 AveFrameMinusAveP;
    HI_S32 StillToMoveDelay;
    HI_S32 IQpDelta;
    HI_S32 PQpDelta;


    HI_S32 StreamBuffer[30];
	HI_S32 BufferBits;

}VeduEfl_Rc_S;

typedef struct {
  char  *TokenName;
  void  *Place;
  int    Type;
  int Value;
  int min_limit;
  int max_limit;
  int    Step;
} Mapping;

typedef struct
{
	HI_U8** items;
	HI_U32 curItem;
	HI_U32 Cfg_bufsize;
	HI_S32 curFrameNumInCfgIdx;
	HI_S32 curCfgIdx;
	HI_U8* pCfgBuffer;

	HI_U32  CFG_NUM;
	HI_U32  CFG_IDX;
	HI_U32  CFG_TIMES;
	HI_U32  beLastCfg;
	HI_U32  LastCfgIdx;
	HI_U32  beCfgEnd;

    //vcpi 0x20620000
	HI_U32 enable_cfg_err;
	HI_U32 enable_vedu_timeout;
	HI_U32 enable_vedu_step;
	HI_U32 enable_vedu_brkpt;
	HI_U32 enable_vedu_slice_end;
	HI_U32 enable_ve_pbitsover;
	HI_U32 enable_ve_buffull;
	HI_U32 enable_ve_eop;
	HI_U32 clr_cfg_err;
	HI_U32 clr_vedu_timeout;
	HI_U32 clr_vedu_step;
	HI_U32 clr_vedu_brkpt;
	HI_U32 clr_vedu_slice_end;
	HI_U32 clr_ve_pbitsover;
	HI_U32 clr_ve_buffull;
	HI_U32 clr_ve_eop;
	HI_U32 vcpi_vstep;
	HI_U32 vcpi_vstart;
	HI_U32 vcpi_dbgmod;
	HI_U32 vcpi_bkp_en;
	HI_U32 vcpi_time_en;
	HI_U32 vcpi_lcu_size;
	HI_U32 vcpi_tiles_en;
	HI_U32 vcpi_ref_cmp_en;
	HI_U32 vcpi_trans_mode;
	HI_U32 vcpi_pskp_en;
	HI_U32 vcpi_idr_pic;
	HI_U32 vcpi_entropy_mode;
	HI_U32 vcpi_frame_type;
	HI_U32 vcpi_img_improve_en;
	HI_U32 vcpi_rec_cmp_en;
	HI_U32 vcpi_sao_chroma;
	HI_U32 vcpi_sao_luma;
	HI_U32 vcpi_slice_int_en;
	HI_U32 vcpi_protocol;
	HI_U32 vcpi_cfg_mode;
	HI_U32 vcpi_lcu_time_sel;
	HI_U32 vcpi_vedsel;
	HI_U32 vcpi_tile_height;
	HI_U32 vcpi_tile_width;
	HI_U32 vcpi_multislc_en;
	HI_U32 vcpi_slcspilt_mod;
	HI_U32 vcpi_slice_size;
	HI_U32 vcpi_frm_qp;
	HI_U32 vcpi_cb_qp_offset;
	HI_U32 vcpi_cr_qp_offset;
	HI_U32 vcpi_cnt_clr;
	HI_U32 vcpi_frame_no;
	HI_U32 vcpi_dblk_filter_flag;
	HI_U32 vcpi_dblk_alpha;
	HI_U32 vcpi_dblk_beta;
	HI_U32 vcpi_protocol_clkgate_en;
	HI_U32 vcpi_mem_clkgate_en;
	HI_U32 vcpi_clkgate_en;
	HI_U32 fme_gtck_en;
	HI_U32 mrg_gtck_en;
	HI_U32 tqitq_gtck_en;
	HI_U32 vcpi_ime_lowpow;
	HI_U32 vcpi_fme_lowpow;
	HI_U32 vcpi_intra_lowpow;
	HI_U32 vcpi_imgheight_pix;
	HI_U32 vcpi_imgwidth_pix;
	HI_U32 vcpi_bp_lcu_y;
	HI_U32 vcpi_bp_lcu_x;
	HI_U32 vedu_timeout;
	HI_U32 vcpi_w_outstanding;
	HI_U32 vcpi_r_outstanding;
	HI_U32 vcpi_sw_height;
	HI_U32 vcpi_sw_width;
	HI_U32 vcpi_tmv_wr_rd_avail;
	HI_U32 vcpi_cross_tile;
	HI_U32 vcpi_cross_slice;
	HI_U32 vcpi_roi_en;
	HI_U32 osd7_absqp;
	HI_U32 osd6_absqp;
	HI_U32 osd5_absqp;
	HI_U32 osd4_absqp;
	HI_U32 osd3_absqp;
	HI_U32 osd2_absqp;
	HI_U32 osd1_absqp;
	HI_U32 osd0_absqp;
	HI_U32 osd7_en;
	HI_U32 osd6_en;
	HI_U32 osd5_en;
	HI_U32 osd4_en;
	HI_U32 osd3_en;
	HI_U32 osd2_en;
	HI_U32 osd1_en;
	HI_U32 osd0_en;
	HI_U32 osd_en;
	HI_U32 osd0_y;
	HI_U32 osd0_x;
	HI_U32 osd1_y;
	HI_U32 osd1_x;
	HI_U32 osd2_y;
	HI_U32 osd2_x;
	HI_U32 osd3_y;
	HI_U32 osd3_x;
	HI_U32 osd4_y;
	HI_U32 osd4_x;
	HI_U32 osd5_y;
	HI_U32 osd5_x;
	HI_U32 osd6_y;
	HI_U32 osd6_x;
	HI_U32 osd7_y;
	HI_U32 osd7_x;
	HI_U32 osd0_h;
	HI_U32 osd0_w;
	HI_U32 osd1_h;
	HI_U32 osd1_w;
	HI_U32 osd2_h;
	HI_U32 osd2_w;
	HI_U32 osd3_h;
	HI_U32 osd3_w;
	HI_U32 osd4_h;
	HI_U32 osd4_w;
	HI_U32 osd5_h;
	HI_U32 osd5_w;
	HI_U32 osd6_h;
	HI_U32 osd6_w;
	HI_U32 osd7_h;
	HI_U32 osd7_w;
	HI_U32 osd7_layer_id;
	HI_U32 osd6_layer_id;
	HI_U32 osd5_layer_id;
	HI_U32 osd4_layer_id;
	HI_U32 osd3_layer_id;
	HI_U32 osd2_layer_id;
	HI_U32 osd1_layer_id;
	HI_U32 osd0_layer_id;
	HI_U32 osd3_qp;
	HI_U32 osd2_qp;
	HI_U32 osd1_qp;
	HI_U32 osd0_qp;
	HI_U32 osd7_qp;
	HI_U32 osd6_qp;
	HI_U32 osd5_qp;
	HI_U32 osd4_qp;
	HI_U32 curld_tunlcell_addr;
	HI_U32 curld_y_addr;
	HI_U32 curld_c_addr;
	HI_U32 curld_v_addr;
	HI_U32 curld_yh_addr;
	HI_U32 curld_ch_addr;
	HI_U32 curld_y_stride;
	HI_U32 curld_c_stride;
	HI_U32 curld_yh_stride;
	HI_U32 curld_ch_stride;
	HI_U32 recst_yaddr;
	HI_U32 recst_caddr;
	HI_U32 recst_cstride;
	HI_U32 recst_ystride;
	HI_U32 recst_yh_addr;
	HI_U32 recst_ch_addr;
	HI_U32 recst_head_stride;
	HI_U32 refld_luma_addr;
	HI_U32 refld_chroma_addr;
	HI_U32 refld_luma_vstride;
	HI_U32 refld_chroma_vstride;
	HI_U32 refld_yh_addr;
	HI_U32 refld_ch_addr;
	HI_U32 refld_yh_stride;
	HI_U32 refld_ch_stride;
	HI_U32 vcpi_pmeld_addr;
	HI_U32 vcpi_pmest_addr;
	HI_U32 upst_address;
	HI_U32 mvst_address;
	HI_U32 mvld_address;
	HI_U32 csst_strmaddr;
	HI_U32 csst_swptraddr;
	HI_U32 csst_srptraddr;
	HI_U32 curld_lowdly_en;
	HI_U32 curld_read_interval;
	HI_U32 vcpi_package_sel;
	HI_U32 vcpi_str_fmt;
	HI_U32 vcpi_blk_type;
	HI_U32 vcpi_store_mode;
	HI_U32 vcpi_scale_en;
	HI_U32 vcpi_crop_en;
	HI_U32 vcpi_crop_ystart;
	HI_U32 vcpi_crop_xstart;
	HI_U32 vcpi_crop_yend;
	HI_U32 vcpi_crop_xend;
	HI_U32 vcpi_yscale;
	HI_U32 vcpi_xscale;
	HI_U32 vcpi_oriheight_pix;
	HI_U32 vcpi_oriwidth_pix;
	HI_U32 vcpi_mrg_cu_en;
	HI_U32 vcpi_fme_cu_en;
	HI_U32 vcpi_ipcm_en;
	HI_U32 vcpi_intra_cu_en;
	HI_U32 vcpi_byte_stuffing;
	HI_U32 vcpi_num_refidx;
	HI_U32 vcpi_cabac_init_idc;
	HI_U32 vcpi_ref_idc;
	HI_U32 vcpi_ext_edge_en;
	HI_U32 vcpi_force_inter;
	HI_U32 vcpi_pblk_pre_en;
	HI_U32 vcpi_iblk_pre_en;
	HI_U32 vcpi_pblk_pre_cost_thr;
	HI_U32 vcpi_iblk_pre_cost_thr;
	HI_U32 vcpi_iblk_pre_mvy_thr;
	HI_U32 vcpi_iblk_pre_mvx_thr;
	HI_U32 vcpi_iblk_pre_mv_dif_thr1;
	HI_U32 vcpi_iblk_pre_mv_dif_thr0;
	HI_U32 vcpi_win0_height;
	HI_U32 vcpi_win0_width;
	HI_U32 vcpi_win1_height;
	HI_U32 vcpi_win1_width;
	HI_U32 vcpi_win2_height;
	HI_U32 vcpi_win2_width;
	HI_U32 vcpi_win3_height;
	HI_U32 vcpi_win3_width;
	HI_U32 vcpi_static_en;
	HI_U32 vcpi_highedge_en;
	HI_U32 vcpi_skin_en;
    HI_U32 vcpi_pblk_pre_mvy_thr;
    HI_U32 vcpi_pblk_pre_mvx_thr;
//vctrl 0x20620200
    HI_U32 region7keep;
    HI_U32 region6keep;
    HI_U32 region5keep;
    HI_U32 region4keep;
    HI_U32 region3keep;
    HI_U32 region2keep;
    HI_U32 region1keep;
    HI_U32 region0keep;
    HI_U32 absqp7;
    HI_U32 absqp6;
    HI_U32 absqp5;
    HI_U32 absqp4;
    HI_U32 absqp3;
    HI_U32 absqp2;
    HI_U32 absqp1;
    HI_U32 absqp0;
    HI_U32 region7en;
    HI_U32 region6en;
    HI_U32 region5en;
    HI_U32 region4en;
    HI_U32 region3en;
    HI_U32 region2en;
    HI_U32 region1en;
    HI_U32 region0en;
    HI_U32 roiqp3;
    HI_U32 roiqp2;
    HI_U32 roiqp1;
    HI_U32 roiqp0;
    HI_U32 roiqp7;
    HI_U32 roiqp6;
    HI_U32 roiqp5;
    HI_U32 roiqp4;
    HI_U32 size0_roiheight;
    HI_U32 size0_roiwidth;
    HI_U32 start0_roistarty;
    HI_U32 start0_roistartx;
    HI_U32 size1_roiheight;
    HI_U32 size1_roiwidth;
    HI_U32 start1_roistarty;
    HI_U32 start1_roistartx;
    HI_U32 size2_roiheight;
    HI_U32 size2_roiwidth;
    HI_U32 start2_roistarty;
    HI_U32 start2_roistartx;
    HI_U32 size3_roiheight;
    HI_U32 size3_roiwidth;
    HI_U32 start3_roistarty;
    HI_U32 start3_roistartx;
    HI_U32 size4_roiheight;
    HI_U32 size4_roiwidth;
    HI_U32 start4_roistarty;
    HI_U32 start4_roistartx;
    HI_U32 size5_roiheight;
    HI_U32 size5_roiwidth;
    HI_U32 start5_roistarty;
    HI_U32 start5_roistartx;
    HI_U32 size6_roiheight;
    HI_U32 size6_roiwidth;
    HI_U32 start6_roistarty;
    HI_U32 start6_roistartx;
    HI_U32 size7_roiheight;
    HI_U32 size7_roiwidth;
    HI_U32 start7_roistarty;
    HI_U32 start7_roistartx;
    HI_U32 lcu_target_bit;
    HI_U32 narrow_tile_width;
    HI_U32 lcu_performance_baseline;
    HI_U32 norm32_tr1_denois_max_num;
    HI_U32 norm32_coeff_protect_num;
    HI_U32 norm16_tr1_denois_max_num;
    HI_U32 norm16_coeff_protect_num;
    HI_U32 skin32_tr1_denois_max_num;
    HI_U32 skin32_coeff_protect_num;
    HI_U32 skin16_tr1_denois_max_num;
    HI_U32 skin16_coeff_protect_num;
    HI_U32 static32_tr1_denois_max_num;
    HI_U32 static32_coeff_protect_num;
    HI_U32 static16_tr1_denois_max_num;
    HI_U32 static16_coeff_protect_num;
    HI_U32 hedge32_tr1_denois_max_num;
    HI_U32 hedge32_coeff_protect_num;
    HI_U32 hedge16_tr1_denois_max_num;
    HI_U32 hedge16_coeff_protect_num;
    HI_U32 norm_intra_cu32_rdcost_offset;
    HI_U32 norm_intra_cu16_rdcost_offset;
    HI_U32 norm_intra_cu8_rdcost_offset;
    HI_U32 norm_intra_cu4_rdcost_offset;
    HI_U32 norm_mrg_cu64_rdcost_offset;
    HI_U32 norm_mrg_cu32_rdcost_offset;
    HI_U32 norm_mrg_cu16_rdcost_offset;
    HI_U32 norm_mrg_cu8_rdcost_offset;
    HI_U32 norm_fme_cu64_rdcost_offset;
    HI_U32 norm_fme_cu32_rdcost_offset;
    HI_U32 norm_fme_cu16_rdcost_offset;
    HI_U32 norm_fme_cu8_rdcost_offset;
    HI_U32 skin_intra_cu32_rdcost_offset;
    HI_U32 skin_intra_cu16_rdcost_offset;
    HI_U32 skin_intra_cu8_rdcost_offset ;
    HI_U32 skin_intra_cu4_rdcost_offset ;
    HI_U32 skin_mrg_cu64_rdcost_offset;
    HI_U32 skin_mrg_cu32_rdcost_offset;
    HI_U32 skin_mrg_cu16_rdcost_offset;
    HI_U32 skin_mrg_cu8_rdcost_offset  ;
    HI_U32 skin_fme_cu64_rdcost_offset;
    HI_U32 skin_fme_cu32_rdcost_offset;
    HI_U32 skin_fme_cu16_rdcost_offset;
    HI_U32 skin_fme_cu8_rdcost_offset  ;
    HI_U32 hedge_intra_cu32_rdcost_offset;
    HI_U32 hedge_intra_cu16_rdcost_offset;
    HI_U32 hedge_intra_cu8_rdcost_offset;
    HI_U32 hedge_intra_cu4_rdcost_offset;
    HI_U32 hedge_mrg_cu64_rdcost_offset;
    HI_U32 hedge_mrg_cu32_rdcost_offset;
    HI_U32 hedge_mrg_cu16_rdcost_offset;
    HI_U32 hedge_mrg_cu8_rdcost_offset;
    HI_U32 hedge_fme_cu64_rdcost_offset;
    HI_U32 hedge_fme_cu32_rdcost_offset;
    HI_U32 hedge_fme_cu16_rdcost_offset;
    HI_U32 hedge_fme_cu8_rdcost_offset;

  // Pme  0x20620600
    HI_U32 vcpi_new_cost_en;
    HI_U32 vcpi_psw_adapt_en;
    HI_U32 vcpi_psw_thr0;
    HI_U32 vcpi_psw_thr1;
    HI_U32 vcpi_psw_thr2;
    HI_U32 tr_weightx_2;
    HI_U32 tr_weightx_1;
    HI_U32 tr_weightx_0;
    HI_U32 tr_weighty_2;
    HI_U32 tr_weighty_1;
    HI_U32 tr_weighty_0;
    HI_U32 sr_weight_2;
    HI_U32 sr_weight_1;
    HI_U32 sr_weight_0;
    HI_U32 skin_v_min_thr;
    HI_U32 skin_v_max_thr;
    HI_U32 skin_u_min_thr;
    HI_U32 skin_u_max_thr;
    HI_U32 still_scene_thr;
    HI_U32 high_edge_cnt;
    HI_U32 high_edge_thr;
    HI_U32 skin_num;

    // Refld 0x20620800
    HI_U32 refld_vcpi2cont_title_en;
    HI_U32 refld_ddr_cross_idx;

    // Ime  0x20620a00
    HI_U32 vcpi_high3pre_en;
    HI_U32 vcpi_rect3_mod;
    HI_U32 vcpi_rect2_mod;
    HI_U32 vcpi_rect1_mod;
    HI_U32 vcpi_inter8x8_en;
    HI_U32 vcpi_rect0_vstep;
    HI_U32 vcpi_rect0_hstep;
    HI_U32 vcpi_rect1_vstep;
    HI_U32 vcpi_rect1_hstep;
    HI_U32 vcpi_rect2_vstep;
    HI_U32 vcpi_rect2_hstep;
    HI_U32 vcpi_rect3_vstep;
    HI_U32 vcpi_rect3_hstep;
    HI_U32 vcpi_start_thr;
    HI_U32 vcpi_intra_thr;
    HI_U32 vcpi_lambdaoff16;
    HI_U32 vcpi_lambdaoff8;
    HI_U32 vcpi_lowpow_fme_thr1;
    HI_U32 vcpi_lowpow_fme_thr0;

    //Qpg  0x20620c00
    HI_U32 max_qp;
    HI_U32 min_qp;
    HI_U32 ave_lcu_bits;
    HI_U32 qp_delta;
    HI_U32 cu_qp_delta_thresh3;
    HI_U32 cu_qp_delta_thresh2;
    HI_U32 cu_qp_delta_thresh1;
    HI_U32 cu_qp_delta_thresh0;
    HI_U32 cu_qp_delta_thresh7;
    HI_U32 cu_qp_delta_thresh6;
    HI_U32 cu_qp_delta_thresh5;
    HI_U32 cu_qp_delta_thresh4;
    HI_U32 cu_qp_delta_thresh11;
    HI_U32 cu_qp_delta_thresh10;
    HI_U32 cu_qp_delta_thresh9;
    HI_U32 cu_qp_delta_thresh8;
    HI_U32 strong_edge_qp_delta;
    HI_U32 skin_qp_delta;
    HI_U32 lambda00;
    HI_U32 lambda01;
    HI_U32 lambda02;
    HI_U32 lambda03;
    HI_U32 lambda04;
    HI_U32 lambda05;
    HI_U32 lambda06;
    HI_U32 lambda07;
    HI_U32 lambda08;
    HI_U32 lambda09;
    HI_U32 lambda10;
    HI_U32 lambda11;
    HI_U32 lambda12;
    HI_U32 lambda13;
    HI_U32 lambda14;
    HI_U32 lambda15;
    HI_U32 lambda16;
    HI_U32 lambda17;
    HI_U32 lambda18;
    HI_U32 lambda19;
    HI_U32 lambda20;
    HI_U32 lambda21;
    HI_U32 lambda22;
    HI_U32 lambda23;
    HI_U32 lambda24;
    HI_U32 lambda25;
    HI_U32 lambda26;
    HI_U32 lambda27;
    HI_U32 lambda28;
    HI_U32 lambda29;
    HI_U32 lambda30;
    HI_U32 lambda31;
    HI_U32 lambda32;
    HI_U32 lambda33;
    HI_U32 lambda34;
    HI_U32 lambda35;
    HI_U32 lambda36;
    HI_U32 lambda37;
    HI_U32 lambda38;
    HI_U32 lambda39;
    HI_U32 lambda40;
    HI_U32 lambda41;
    HI_U32 lambda42;
    HI_U32 lambda43;
    HI_U32 lambda44;
    HI_U32 lambda45;
    HI_U32 lambda46;
    HI_U32 lambda47;
    HI_U32 lambda48;
    HI_U32 lambda49;
    HI_U32 lambda50;
    HI_U32 lambda51;
    HI_U32 lambda52;
    HI_U32 lambda53;
    HI_U32 lambda54;
    HI_U32 lambda55;
    HI_U32 lambda56;
    HI_U32 lambda57;
    HI_U32 lambda58;
    HI_U32 lambda59;
    HI_U32 lambda60;
    HI_U32 lambda61;
    HI_U32 lambda62;
    HI_U32 lambda63;
    HI_U32 lambda64;
    HI_U32 lambda65;
    HI_U32 lambda66;
    HI_U32 lambda67;
    HI_U32 lambda68;
    HI_U32 lambda69;
    HI_U32 lambda70;
    HI_U32 lambda71;
    HI_U32 lambda72;
    HI_U32 lambda73;
    HI_U32 lambda74;
    HI_U32 lambda75;
    HI_U32 lambda76;
    HI_U32 lambda77;
    HI_U32 lambda78;
    HI_U32 lambda79;

    //Intra   0x20621200
    HI_U32 inter_avail;
    HI_U32 intra_smooth;
    HI_U32 intra_bit_weight;
    HI_U32 intra_cu4_mode31_en;
    HI_U32 intra_cu4_mode30_en;
    HI_U32 intra_cu4_mode29_en;
    HI_U32 intra_cu4_mode28_en;
    HI_U32 intra_cu4_mode27_en;
    HI_U32 intra_cu4_mode26_en;
    HI_U32 intra_cu4_mode25_en;
    HI_U32 intra_cu4_mode24_en;
    HI_U32 intra_cu4_mode23_en;
    HI_U32 intra_cu4_mode22_en;
    HI_U32 intra_cu4_mode21_en;
    HI_U32 intra_cu4_mode20_en;
    HI_U32 intra_cu4_mode19_en;
    HI_U32 intra_cu4_mode18_en;
    HI_U32 intra_cu4_mode17_en;
    HI_U32 intra_cu4_mode16_en;
    HI_U32 intra_cu4_mode15_en;
    HI_U32 intra_cu4_mode14_en;
    HI_U32 intra_cu4_mode13_en;
    HI_U32 intra_cu4_mode12_en;
    HI_U32 intra_cu4_mode11_en;
    HI_U32 intra_cu4_mode10_en;
    HI_U32 intra_cu4_mode9_en;
    HI_U32 intra_cu4_mode8_en;
    HI_U32 intra_cu4_mode7_en;
    HI_U32 intra_cu4_mode6_en;
    HI_U32 intra_cu4_mode5_en;
    HI_U32 intra_cu4_mode4_en;
    HI_U32 intra_cu4_mode3_en;
    HI_U32 intra_cu4_mode2_en;
    HI_U32 intra_cu4_mode1_en;
    HI_U32 intra_cu4_mode0_en;
    HI_U32 intra_cu4_mode34_en;
    HI_U32 intra_cu4_mode33_en;
    HI_U32 intra_cu4_mode32_en;
    HI_U32 intra_cu4_mode1;
    HI_U32 intra_cu4_mode0;
    HI_U32 intra_cu8_mode31_en;
    HI_U32 intra_cu8_mode30_en;
    HI_U32 intra_cu8_mode29_en;
    HI_U32 intra_cu8_mode28_en;
    HI_U32 intra_cu8_mode27_en;
    HI_U32 intra_cu8_mode26_en;
    HI_U32 intra_cu8_mode25_en;
    HI_U32 intra_cu8_mode24_en;
    HI_U32 intra_cu8_mode23_en;
    HI_U32 intra_cu8_mode22_en;
    HI_U32 intra_cu8_mode21_en;
    HI_U32 intra_cu8_mode20_en;
    HI_U32 intra_cu8_mode19_en;
    HI_U32 intra_cu8_mode18_en;
    HI_U32 intra_cu8_mode17_en;
    HI_U32 intra_cu8_mode16_en;
    HI_U32 intra_cu8_mode15_en;
    HI_U32 intra_cu8_mode14_en;
    HI_U32 intra_cu8_mode13_en;
    HI_U32 intra_cu8_mode12_en;
    HI_U32 intra_cu8_mode11_en;
    HI_U32 intra_cu8_mode10_en;
    HI_U32 intra_cu8_mode9_en;
    HI_U32 intra_cu8_mode8_en;
    HI_U32 intra_cu8_mode7_en;
    HI_U32 intra_cu8_mode6_en;
    HI_U32 intra_cu8_mode5_en;
    HI_U32 intra_cu8_mode4_en;
    HI_U32 intra_cu8_mode3_en;
    HI_U32 intra_cu8_mode2_en;
    HI_U32 intra_cu8_mode1_en;
    HI_U32 intra_cu8_mode0_en;
    HI_U32 intra_cu8_mode34_en;
    HI_U32 intra_cu8_mode33_en;
    HI_U32 intra_cu8_mode32_en;
    HI_U32 intra_cu8_mode1;
    HI_U32 intra_cu8_mode0;
    HI_U32 intra_cu16_mode31_en;
    HI_U32 intra_cu16_mode30_en;
    HI_U32 intra_cu16_mode29_en;
    HI_U32 intra_cu16_mode28_en;
    HI_U32 intra_cu16_mode27_en;
    HI_U32 intra_cu16_mode26_en;
    HI_U32 intra_cu16_mode25_en;
    HI_U32 intra_cu16_mode24_en;
    HI_U32 intra_cu16_mode23_en;
    HI_U32 intra_cu16_mode22_en;
    HI_U32 intra_cu16_mode21_en;
    HI_U32 intra_cu16_mode20_en;
    HI_U32 intra_cu16_mode19_en;
    HI_U32 intra_cu16_mode18_en;
    HI_U32 intra_cu16_mode17_en;
    HI_U32 intra_cu16_mode16_en;
    HI_U32 intra_cu16_mode15_en;
    HI_U32 intra_cu16_mode14_en;
    HI_U32 intra_cu16_mode13_en;
    HI_U32 intra_cu16_mode12_en;
    HI_U32 intra_cu16_mode11_en;
    HI_U32 intra_cu16_mode10_en;
    HI_U32 intra_cu16_mode9_en;
    HI_U32 intra_cu16_mode8_en;
    HI_U32 intra_cu16_mode7_en;
    HI_U32 intra_cu16_mode6_en;
    HI_U32 intra_cu16_mode5_en;
    HI_U32 intra_cu16_mode4_en;
    HI_U32 intra_cu16_mode3_en;
    HI_U32 intra_cu16_mode2_en;
    HI_U32 intra_cu16_mode1_en;
    HI_U32 intra_cu16_mode0_en;
    HI_U32 intra_cu16_mode34_en;
    HI_U32 intra_cu16_mode33_en;
    HI_U32 intra_cu16_mode32_en;
    HI_U32 intra_cu16_mode1;
    HI_U32 intra_cu16_mode0;
    HI_U32 intra_cu32_mode31_en;
    HI_U32 intra_cu32_mode30_en;
    HI_U32 intra_cu32_mode29_en;
    HI_U32 intra_cu32_mode28_en;
    HI_U32 intra_cu32_mode27_en;
    HI_U32 intra_cu32_mode26_en;
    HI_U32 intra_cu32_mode25_en;
    HI_U32 intra_cu32_mode24_en;
    HI_U32 intra_cu32_mode23_en;
    HI_U32 intra_cu32_mode22_en;
    HI_U32 intra_cu32_mode21_en;
    HI_U32 intra_cu32_mode20_en;
    HI_U32 intra_cu32_mode19_en;
    HI_U32 intra_cu32_mode18_en;
    HI_U32 intra_cu32_mode17_en;
    HI_U32 intra_cu32_mode16_en;
    HI_U32 intra_cu32_mode15_en;
    HI_U32 intra_cu32_mode14_en;
    HI_U32 intra_cu32_mode13_en;
    HI_U32 intra_cu32_mode12_en;
    HI_U32 intra_cu32_mode11_en;
    HI_U32 intra_cu32_mode10_en;
    HI_U32 intra_cu32_mode9_en;
    HI_U32 intra_cu32_mode8_en;
    HI_U32 intra_cu32_mode7_en;
    HI_U32 intra_cu32_mode6_en;
    HI_U32 intra_cu32_mode5_en;
    HI_U32 intra_cu32_mode4_en;
    HI_U32 intra_cu32_mode3_en;
    HI_U32 intra_cu32_mode2_en;
    HI_U32 intra_cu32_mode1_en;
    HI_U32 intra_cu32_mode0_en;
    HI_U32 intra_cu32_mode34_en;
    HI_U32 intra_cu32_mode33_en;
    HI_U32 intra_cu32_mode32_en;
    HI_U32 intra_cu32_mode1;
    HI_U32 intra_cu32_mode0;

    //Pmv  0x20621400
    HI_U32 tmv_en;

    //Tqitq  0x20621600
    HI_U32 q_scaling_waddr;
    HI_U32 q_scaling_wdata;

    // Pack  0x20621e00
    HI_U32 pack_sybtax_config;
    HI_U32 vcpi2cu_qp_min_cu_size;
    HI_U32 vcpi2cu_tq_bypass_enabled_flag;
    HI_U32 vcpi2pu_log2_max_ipcm_cbsizey;
    HI_U32 vcpi2pu_log2_min_ipcm_cbsizey;
    HI_U32 vcpi2res_tf_skip_enabled_flag;
    //Cabac  0x20622000
    HI_U32 nal_unit_head;
    HI_U32 max_num_mergecand;
    HI_U32 slchdr_size_part2;
    HI_U32 slchdr_size_part1;
    HI_U32 slchdr_part1;
    HI_U32 slchdr_part2_seg1;
    HI_U32 slchdr_part2_seg2;
    HI_U32 slchdr_part2_seg3;
    HI_U32 slchdr_part2_seg4;
    HI_U32 slchdr_part2_seg5;
    HI_U32 slchdr_part2_seg6;
    HI_U32 slchdr_part2_seg7;
    HI_U32 slchdr_part2_seg8;
    //recst 0x20622a00
    HI_U32 recst_ddr_cross_idx;
    //vlcst  0x20622c00
    HI_U32 strmbuflen;
    HI_U32 ptbits_en;
    HI_U32 ptbits;
    HI_U32 chnid;
    HI_U32 idrind;
    HI_U32 slc_cfg0;
    HI_U32 slc_cfg1;
    HI_U32 slc_cfg2;
    HI_U32 slc_cfg3;
    // vlc     0x20622e00
    HI_U32 vcpi_slchdrstrm0;
    HI_U32 vcpi_slchdrstrm1;
    HI_U32 vcpi_slchdrstrm2;
    HI_U32 vcpi_slchdrstrm3;
    HI_U32 vcpi_reorderstrm0;
    HI_U32 vcpi_reorderstrm1;
    HI_U32 vcpi_markingstrm0;
    HI_U32 vcpi_markingstrm1;
    HI_U32 vcpi_parabit;
    HI_U32 vcpi_reorderbit;
    HI_U32 vcpi_markingbit;
    HI_U32 vcpi_svc_strm;
    HI_U32 vcpi_svc_en;
    //Curpre    0x20623000
    HI_U32 curld_filter_hshift;
    HI_U32 curld_filter_hrnd;
    HI_U32 curld_filter_h3;
    HI_U32 curld_filter_h2;
    HI_U32 curld_filter_h1;
    HI_U32 curld_filter_h0;
    HI_U32 curld_filter_vshift;
    HI_U32 curld_filter_vrnd;
    HI_U32 curld_filter_v3;
    HI_U32 curld_filter_v2;
    HI_U32 curld_filter_v1;
    HI_U32 curld_filter_v0;
    HI_U32 curld_y_filt_01coef;
    HI_U32 curld_y_filt_00coef;
    HI_U32 curld_y_filt_03coef;
    HI_U32 curld_y_filt_02coef;
    HI_U32 curld_y_filt_11coef;
    HI_U32 curld_y_filt_10coef;
    HI_U32 curld_y_filt_13coef;
    HI_U32 curld_y_filt_12coef;
    HI_U32 curld_y_filt_21coef;
    HI_U32 curld_y_filt_20coef;
    HI_U32 curld_y_filt_23coef;
    HI_U32 curld_y_filt_22coef;
    HI_U32 curld_y_filt_31coef;
    HI_U32 curld_y_filt_30coef;
    HI_U32 curld_y_filt_33coef;
    HI_U32 curld_y_filt_32coef;
    HI_U32 curld_c_filt_01coef;
    HI_U32 curld_c_filt_00coef;
    HI_U32 curld_c_filt_03coef;
    HI_U32 curld_c_filt_02coef;
    HI_U32 curld_c_filt_11coef;
    HI_U32 curld_c_filt_10coef;
    HI_U32 curld_c_filt_13coef;
    HI_U32 curld_c_filt_12coef;
    HI_U32 curld_c_filt_21coef;
    HI_U32 curld_c_filt_20coef;
    HI_U32 curld_c_filt_23coef;
    HI_U32 curld_c_filt_22coef;
    HI_U32 curld_c_filt_31coef;
    HI_U32 curld_c_filt_30coef;
    HI_U32 curld_c_filt_33coef;
    HI_U32 curld_c_filt_32coef;
    //two group of scale coeff
    HI_U32 curld_y_filt_col_01coef;
    HI_U32 curld_y_filt_col_00coef;
    HI_U32 curld_y_filt_col_03coef;
    HI_U32 curld_y_filt_col_02coef;
    HI_U32 curld_y_filt_col_11coef;
    HI_U32 curld_y_filt_col_10coef;
    HI_U32 curld_y_filt_col_13coef;
    HI_U32 curld_y_filt_col_12coef;
    HI_U32 curld_y_filt_col_21coef;
    HI_U32 curld_y_filt_col_20coef;
    HI_U32 curld_y_filt_col_23coef;
    HI_U32 curld_y_filt_col_22coef;
    HI_U32 curld_y_filt_col_31coef;
    HI_U32 curld_y_filt_col_30coef;
    HI_U32 curld_y_filt_col_33coef;
    HI_U32 curld_y_filt_col_32coef;
    HI_U32 curld_c_filt_col_01coef;
    HI_U32 curld_c_filt_col_00coef;
    HI_U32 curld_c_filt_col_03coef;
    HI_U32 curld_c_filt_col_02coef;
    HI_U32 curld_c_filt_col_11coef;
    HI_U32 curld_c_filt_col_10coef;
    HI_U32 curld_c_filt_col_13coef;
    HI_U32 curld_c_filt_col_12coef;
    HI_U32 curld_c_filt_col_21coef;
    HI_U32 curld_c_filt_col_20coef;
    HI_U32 curld_c_filt_col_23coef;
    HI_U32 curld_c_filt_col_22coef;
    HI_U32 curld_c_filt_col_31coef;
    HI_U32 curld_c_filt_col_30coef;
    HI_U32 curld_c_filt_col_33coef;
    HI_U32 curld_c_filt_col_32coef;
    HI_U32 curld_clip_en;
    HI_U32 clip_chrm_max;
    HI_U32 clip_chrm_min;
    HI_U32 clip_luma_max;
    HI_U32 clip_luma_min;

    HI_S32 vcpi_coeff_ry   ;
    HI_S32 vcpi_coeff_gy   ;
    HI_S32 vcpi_coeff_by   ;
    HI_S32 vcpi_coeff_rcb  ;
    HI_S32 vcpi_coeff_gcb  ;
    HI_S32 vcpi_coeff_bcb  ;
    HI_S32 vcpi_coeff_rcr  ;
    HI_S32 vcpi_coeff_gcr  ;
    HI_S32 vcpi_coeff_bcr  ;
    HI_U32 vcpi_rgb_shift  ;
    HI_U32 vcpi_rgb_rndy   ;
    HI_U32 vcpi_rgb_rndcb  ;
    HI_U32 vcpi_rgb_rndcr  ;
    HI_U32 vcpi_rgb_clip_en;
    HI_U32 vcpi_rgb_clpmax ;
    HI_U32 vcpi_rgb_clpmin ;
    HI_U32 vcpi_wide_narrow_en ;

    //emar
    HI_U32 vcpi_wtmax;
    HI_U32 vcpi_rtmax;
    HI_U32 vcpi_ch00_rrmax;
    HI_U32 vcpi_ch01_rrmax;
    HI_U32 vcpi_ch02_rrmax;
    HI_U32 vcpi_ch03_rrmax;
    HI_U32 vcpi_ch04_rrmax;
    HI_U32 vcpi_ch05_rrmax;
    HI_U32 vcpi_ch06_rrmax;
    HI_U32 vcpi_ch07_rrmax;
    HI_U32 vcpi_ch08_rrmax;
    HI_U32 vcpi_ch09_rrmax;
    HI_U32 vcpi_ch10_rrmax;
    HI_U32 vcpi_ch11_rrmax;
    HI_U32 vcpi_ch12_rrmax;
    HI_U32 vcpi_ch00_wrmax;
    HI_U32 vcpi_ch01_wrmax;
    HI_U32 vcpi_ch02_wrmax;
    HI_U32 vcpi_ch03_wrmax;
    HI_U32 vcpi_ch04_wrmax;
    HI_U32 vcpi_ch05_wrmax;
    HI_U32 vcpi_ch06_wrmax;
    HI_U32 vcpi_ch07_wrmax;
    HI_U32 vcpi_ch08_wrmax;
    HI_U32 vcpi_ch09_wrmax;
    HI_U32 vcpi_ch10_wrmax;
    HI_U32 vcpi_ch11_wrmax;
    HI_U32 vcpi_ch12_wrmax;
    HI_U32 vcpi_ch13_wrmax;
    HI_U32 vcpi_ch14_wrmax;
    
    //comn0  0x20623600
    HI_U32 comn0_ptw_mid                ;        
    HI_U32 comn0_ptw_pf                  ;    
    HI_U32 comn0_smr_rd_shadow     ;  
    HI_U32 comn0_wqos                     ;
    HI_U32 comn0_rqos                      ;
    HI_U32 comn0_cache_l2_en           ;    
    HI_U32 comn0_cache_l1_en           ;    
    HI_U32 comn0_int_en                    ;  
    HI_U32 comn0_wqos_en                ;
    HI_U32 comn0_rqos_en                 ;
    HI_U32 comn0_glb_bypass             ;    
    HI_U32 comn0_mem_ctrl_rd            ;    
    HI_U32 comn0_mem_ctrl_wr            ;    
    HI_U32 comn0_auto_clk_gt_en         ;    
    HI_U32 comn0_remap_sel15            ;    
    HI_U32 comn0_remap_sel14            ;    
    HI_U32 comn0_remap_sel13            ;    
    HI_U32 comn0_remap_sel12            ;    
    HI_U32 comn0_remap_sel11            ;    
    HI_U32 comn0_remap_sel10            ;    
    HI_U32 comn0_remap_sel9             ;    
    HI_U32 comn0_remap_sel8             ;    
    HI_U32 comn0_remap_sel7             ;    
    HI_U32 comn0_remap_sel6             ;    
    HI_U32 comn0_remap_sel5             ;    
    HI_U32 comn0_remap_sel4             ;    
    HI_U32 comn0_remap_sel3             ;    
    HI_U32 comn0_remap_sel2             ;    
    HI_U32 comn0_remap_sel1             ;    
    HI_U32 comn0_remap_sel0             ;    
    HI_U32 comn0_intns_ptw_ns_msk       ;    
    HI_U32 comn0_intns_ptw_invalid_msk  ;    
    HI_U32 comn0_intns_ptw_trans_msk    ;    
    HI_U32 comn0_intns_tlbmiss_msk      ;    
    HI_U32 comn0_intns_ext_msk          ;    
    HI_U32 comn0_intns_permis_msk       ;    
    HI_U32 comn0_intns_ptw_ns_clr       ;    
    HI_U32 comn0_intns_ptw_invalid_clr  ;    
    HI_U32 comn0_intns_ptw_trans_clr    ;    
    HI_U32 comn0_intns_tlbmiss_clr      ;    
    HI_U32 comn0_intns_ext_clr          ;    
    HI_U32 comn0_intns_permis_clr       ;    
    HI_U32 comn0_smr0_offset_addr       ;    
    HI_U32 comn0_smr0_ptw_qos           ;    
    HI_U32 comn0_smr0_invld_en          ;    
    HI_U32 comn0_smr0_bypass            ;    
    HI_U32 comn0_smr1_offset_addr       ;    
    HI_U32 comn0_smr1_ptw_qos           ;    
    HI_U32 comn0_smr1_invld_en          ;    
    HI_U32 comn0_smr1_bypass            ;    
    HI_U32 comn0_smr2_offset_addr       ;    
    HI_U32 comn0_smr2_ptw_qos           ;    
    HI_U32 comn0_smr2_invld_en          ;    
    HI_U32 comn0_smr2_bypass            ;    
    HI_U32 comn0_smr3_offset_addr       ;    
    HI_U32 comn0_smr3_ptw_qos           ;    
    HI_U32 comn0_smr3_invld_en          ;    
    HI_U32 comn0_smr3_bypass            ;    
    HI_U32 comn0_smr4_offset_addr       ;    
    HI_U32 comn0_smr4_ptw_qos           ;    
    HI_U32 comn0_smr4_invld_en          ;    
    HI_U32 comn0_smr4_bypass            ;    
    HI_U32 comn0_smr5_offset_addr       ;    
    HI_U32 comn0_smr5_ptw_qos           ;    
    HI_U32 comn0_smr5_invld_en          ;    
    HI_U32 comn0_smr5_bypass            ;    
    HI_U32 comn0_smr6_offset_addr       ;    
    HI_U32 comn0_smr6_ptw_qos           ;    
    HI_U32 comn0_smr6_invld_en          ;    
    HI_U32 comn0_smr6_bypass            ;    
    HI_U32 comn0_smr7_offset_addr       ;    
    HI_U32 comn0_smr7_ptw_qos           ;    
    HI_U32 comn0_smr7_invld_en          ;    
    HI_U32 comn0_smr7_bypass            ;    
    HI_U32 comn0_smr8_offset_addr       ;    
    HI_U32 comn0_smr8_ptw_qos           ;    
    HI_U32 comn0_smr8_invld_en          ;    
    HI_U32 comn0_smr8_bypass            ; 
    HI_U32 comn0_smr9_offset_addr       ;    
    HI_U32 comn0_smr9_ptw_qos           ;    
    HI_U32 comn0_smr9_invld_en          ;    
    HI_U32 comn0_smr9_bypass            ;    
    HI_U32 comn0_smr10_offset_addr      ;    
    HI_U32 comn0_smr10_ptw_qos          ;    
    HI_U32 comn0_smr10_invld_en         ;    
    HI_U32 comn0_smr10_bypass           ;    
    HI_U32 comn0_smr11_offset_addr      ;    
    HI_U32 comn0_smr11_ptw_qos          ;    
    HI_U32 comn0_smr11_invld_en         ;    
    HI_U32 comn0_smr11_bypass           ;    
    HI_U32 comn0_smr12_offset_addr      ;    
    HI_U32 comn0_smr12_ptw_qos          ;    
    HI_U32 comn0_smr12_invld_en         ;    
    HI_U32 comn0_smr12_bypass           ;    
    HI_U32 comn0_smr13_offset_addr      ;    
    HI_U32 comn0_smr13_ptw_qos          ;    
    HI_U32 comn0_smr13_invld_en         ;    
    HI_U32 comn0_smr13_bypass           ;    
    HI_U32 comn0_smr14_offset_addr      ;    
    HI_U32 comn0_smr14_ptw_qos          ;    
    HI_U32 comn0_smr14_invld_en         ;    
    HI_U32 comn0_smr14_bypass           ;    
    HI_U32 comn0_smr15_offset_addr      ;    
    HI_U32 comn0_smr15_ptw_qos          ;    
    HI_U32 comn0_smr15_invld_en         ;    
    HI_U32 comn0_smr15_bypass           ;    
    HI_U32 comn0_smr16_offset_addr      ;    
    HI_U32 comn0_smr16_ptw_qos          ;    
    HI_U32 comn0_smr16_invld_en         ;    
    HI_U32 comn0_smr16_bypass           ;    
    HI_U32 comn0_smr17_offset_addr      ;    
    HI_U32 comn0_smr17_ptw_qos          ;    
    HI_U32 comn0_smr17_invld_en         ;    
    HI_U32 comn0_smr17_bypass           ; 
    HI_U32 comn0_smr18_offset_addr      ;    
    HI_U32 comn0_smr18_ptw_qos          ;    
    HI_U32 comn0_smr18_invld_en         ;    
    HI_U32 comn0_smr18_bypass           ;    
    HI_U32 comn0_smr19_offset_addr      ;    
    HI_U32 comn0_smr19_ptw_qos          ;    
    HI_U32 comn0_smr19_invld_en         ;    
    HI_U32 comn0_smr19_bypass           ;    
    HI_U32 comn0_smr20_offset_addr      ;    
    HI_U32 comn0_smr20_ptw_qos          ;    
    HI_U32 comn0_smr20_invld_en         ;    
    HI_U32 comn0_smr20_bypass           ;    
    HI_U32 comn0_smr21_offset_addr      ;    
    HI_U32 comn0_smr21_ptw_qos          ;    
    HI_U32 comn0_smr21_invld_en         ;    
    HI_U32 comn0_smr21_bypass           ;    
    HI_U32 comn0_smr22_offset_addr      ;    
    HI_U32 comn0_smr22_ptw_qos          ;    
    HI_U32 comn0_smr22_invld_en         ;    
    HI_U32 comn0_smr22_bypass           ;    
    HI_U32 comn0_smr23_offset_addr      ;    
    HI_U32 comn0_smr23_ptw_qos          ;    
    HI_U32 comn0_smr23_invld_en         ;    
    HI_U32 comn0_smr23_bypass           ;    
    HI_U32 comn0_smr24_offset_addr      ;    
    HI_U32 comn0_smr24_ptw_qos          ;    
    HI_U32 comn0_smr24_invld_en         ;    
    HI_U32 comn0_smr24_bypass           ;    
    HI_U32 comn0_smr25_offset_addr      ;    
    HI_U32 comn0_smr25_ptw_qos          ;    
    HI_U32 comn0_smr25_invld_en         ;    
    HI_U32 comn0_smr25_bypass           ;    
    HI_U32 comn0_smr26_offset_addr      ;    
    HI_U32 comn0_smr26_ptw_qos          ;    
    HI_U32 comn0_smr26_invld_en         ;    
    HI_U32 comn0_smr26_bypass           ;    
    HI_U32 comn0_smr27_offset_addr      ;    
    HI_U32 comn0_smr27_ptw_qos          ;    
    HI_U32 comn0_smr27_invld_en         ;    
    HI_U32 comn0_smr27_bypass           ;    
    HI_U32 comn0_smr28_offset_addr      ;    
    HI_U32 comn0_smr28_ptw_qos          ;    
    HI_U32 comn0_smr28_invld_en         ;    
    HI_U32 comn0_smr28_bypass           ;    
    HI_U32 comn0_smr29_offset_addr      ;    
    HI_U32 comn0_smr29_ptw_qos          ;    
    HI_U32 comn0_smr29_invld_en         ;    
    HI_U32 comn0_smr29_bypass           ;    
    HI_U32 comn0_smr30_offset_addr      ;    
    HI_U32 comn0_smr30_ptw_qos          ;    
    HI_U32 comn0_smr30_invld_en         ;    
    HI_U32 comn0_smr30_bypass           ;    
    HI_U32 comn0_smr31_offset_addr      ;    
    HI_U32 comn0_smr31_ptw_qos          ;    
    HI_U32 comn0_smr31_invld_en         ;    
    HI_U32 comn0_smr31_bypass           ;    
    HI_U32 comn0_smr32_offset_addr      ;    
    HI_U32 comn0_smr32_ptw_qos          ;    
    HI_U32 comn0_smr32_invld_en         ;    
    HI_U32 comn0_smr32_bypass           ;    
    HI_U32 comn0_smr33_offset_addr      ;    
    HI_U32 comn0_smr33_ptw_qos          ; 
    HI_U32 comn0_smr33_invld_en         ;    
    HI_U32 comn0_smr33_bypass           ;    
    HI_U32 comn0_smr34_offset_addr      ;    
    HI_U32 comn0_smr34_ptw_qos          ;    
    HI_U32 comn0_smr34_invld_en         ;    
    HI_U32 comn0_smr34_bypass           ;    
    HI_U32 comn0_smr35_offset_addr      ;    
    HI_U32 comn0_smr35_ptw_qos          ;    
    HI_U32 comn0_smr35_invld_en         ;    
    HI_U32 comn0_smr35_bypass           ;    
    HI_U32 comn0_smr36_offset_addr      ;    
    HI_U32 comn0_smr36_ptw_qos          ;    
    HI_U32 comn0_smr36_invld_en         ;    
    HI_U32 comn0_smr36_bypass           ;    
    HI_U32 comn0_smr37_offset_addr      ;    
    HI_U32 comn0_smr37_ptw_qos          ;    
    HI_U32 comn0_smr37_invld_en         ;    
    HI_U32 comn0_smr37_bypass           ;    
    HI_U32 comn0_smr38_offset_addr      ;    
    HI_U32 comn0_smr38_ptw_qos          ;    
    HI_U32 comn0_smr38_invld_en         ;    
    HI_U32 comn0_smr38_bypass           ;    
    HI_U32 comn0_smr39_offset_addr      ;    
    HI_U32 comn0_smr39_ptw_qos          ;    
    HI_U32 comn0_smr39_invld_en         ;    
    HI_U32 comn0_smr39_bypass           ;    
    HI_U32 comn0_smr40_offset_addr      ;    
    HI_U32 comn0_smr40_ptw_qos          ;    
    HI_U32 comn0_smr40_invld_en         ;    
    HI_U32 comn0_smr40_bypass           ;    
    HI_U32 comn0_smr41_offset_addr      ;    
    HI_U32 comn0_smr41_ptw_qos          ;    
    HI_U32 comn0_smr41_invld_en         ;    
    HI_U32 comn0_smr41_bypass           ;    
    HI_U32 comn0_smr42_offset_addr      ;    
    HI_U32 comn0_smr42_ptw_qos          ;    
    HI_U32 comn0_smr42_invld_en         ;    
    HI_U32 comn0_smr42_bypass           ;    
    HI_U32 comn0_smr43_offset_addr      ;    
    HI_U32 comn0_smr43_ptw_qos          ;    
    HI_U32 comn0_smr43_invld_en         ;    
    HI_U32 comn0_smr43_bypass           ;    
    HI_U32 comn0_smr44_offset_addr      ;    
    HI_U32 comn0_smr44_ptw_qos          ;    
    HI_U32 comn0_smr44_invld_en         ;    
    HI_U32 comn0_smr44_bypass           ;    
    HI_U32 comn0_smr45_offset_addr      ;    
    HI_U32 comn0_smr45_ptw_qos          ;    
    HI_U32 comn0_smr45_invld_en         ;    
    HI_U32 comn0_smr45_bypass           ;    
    HI_U32 comn0_smr46_offset_addr      ;     
    HI_U32 comn0_smr46_ptw_qos          ;    
    HI_U32 comn0_smr46_invld_en         ;    
    HI_U32 comn0_smr46_bypass           ;    
    HI_U32 comn0_smr47_offset_addr      ;    
    HI_U32 comn0_smr47_ptw_qos          ;    
    HI_U32 comn0_smr47_invld_en         ;    
    HI_U32 comn0_smr47_bypass           ;    
    HI_U32 comn0_smr48_offset_addr      ;    
    HI_U32 comn0_smr48_ptw_qos          ;    
    HI_U32 comn0_smr48_invld_en         ;    
    HI_U32 comn0_smr48_bypass           ;    
    HI_U32 comn0_smr49_offset_addr      ;    
    HI_U32 comn0_smr49_ptw_qos          ;    
    HI_U32 comn0_smr49_invld_en         ;    
    HI_U32 comn0_smr49_bypass           ;    
    HI_U32 comn0_smr50_offset_addr      ;    
    HI_U32 comn0_smr50_ptw_qos          ;    
    HI_U32 comn0_smr50_invld_en         ;    
    HI_U32 comn0_smr50_bypass           ;    
    HI_U32 comn0_smr51_offset_addr      ;    
    HI_U32 comn0_smr51_ptw_qos          ;    
    HI_U32 comn0_smr51_invld_en         ;    
    HI_U32 comn0_smr51_bypass           ;    
    HI_U32 comn0_smr52_offset_addr      ;    
    HI_U32 comn0_smr52_ptw_qos          ;    
    HI_U32 comn0_smr52_invld_en         ;    
    HI_U32 comn0_smr52_bypass           ;    
    HI_U32 comn0_smr53_offset_addr      ;    
    HI_U32 comn0_smr53_ptw_qos          ;    
    HI_U32 comn0_smr53_invld_en         ;    
    HI_U32 comn0_smr53_bypass           ;    
    HI_U32 comn0_smr54_offset_addr      ;    
    HI_U32 comn0_smr54_ptw_qos          ;    
    HI_U32 comn0_smr54_invld_en         ;    
    HI_U32 comn0_smr54_bypass           ;    
    HI_U32 comn0_smr55_offset_addr      ;    
    HI_U32 comn0_smr55_ptw_qos          ;    
    HI_U32 comn0_smr55_invld_en         ;    
    HI_U32 comn0_smr55_bypass           ;    
    HI_U32 comn0_smr56_offset_addr      ;    
    HI_U32 comn0_smr56_ptw_qos          ;    
    HI_U32 comn0_smr56_invld_en         ;    
    HI_U32 comn0_smr56_bypass           ;    
    HI_U32 comn0_smr57_offset_addr      ;    
    HI_U32 comn0_smr57_ptw_qos          ;    
    HI_U32 comn0_smr57_invld_en         ;    
    HI_U32 comn0_smr57_bypass           ;    
    HI_U32 comn0_smr58_offset_addr      ;    
    HI_U32 comn0_smr58_ptw_qos          ;    
    HI_U32 comn0_smr58_invld_en         ;    
    HI_U32 comn0_smr58_bypass           ;    
    HI_U32 comn0_smr59_offset_addr      ;    
    HI_U32 comn0_smr59_ptw_qos          ;    
    HI_U32 comn0_smr59_invld_en         ;    
    HI_U32 comn0_smr59_bypass           ;    
    HI_U32 comn0_smr60_offset_addr      ;    
    HI_U32 comn0_smr60_ptw_qos          ;    
    HI_U32 comn0_smr60_invld_en         ;    
    HI_U32 comn0_smr60_bypass           ;    
    HI_U32 comn0_smr61_offset_addr      ;    
    HI_U32 comn0_smr61_ptw_qos          ;    
    HI_U32 comn0_smr61_invld_en         ;    
    HI_U32 comn0_smr61_bypass           ;    
    HI_U32 comn0_smr62_offset_addr      ;    
    HI_U32 comn0_smr62_ptw_qos          ;    
    HI_U32 comn0_smr62_invld_en         ;    
    HI_U32 comn0_smr62_bypass           ;    
    HI_U32 comn0_smr63_offset_addr      ;    
    HI_U32 comn0_smr63_ptw_qos          ;    
    HI_U32 comn0_smr63_invld_en         ;    
    HI_U32 comn0_smr63_bypass           ;    
    HI_U32 comn0_smr64_offset_addr      ;    
    HI_U32 comn0_smr64_ptw_qos          ;    
    HI_U32 comn0_smr64_invld_en         ;    
    HI_U32 comn0_smr64_bypass           ;    
    HI_U32 comn0_smr65_offset_addr      ;    
    HI_U32 comn0_smr65_ptw_qos          ;    
    HI_U32 comn0_smr65_invld_en         ;    
    HI_U32 comn0_smr65_bypass           ;    
    HI_U32 comn0_smr66_offset_addr      ;    
    HI_U32 comn0_smr66_ptw_qos          ;    
    HI_U32 comn0_smr66_invld_en         ;    
    HI_U32 comn0_smr66_bypass           ;    
    HI_U32 comn0_smr67_offset_addr      ;    
    HI_U32 comn0_smr67_ptw_qos          ;    
    HI_U32 comn0_smr67_invld_en         ;    
    HI_U32 comn0_smr67_bypass           ;    
    HI_U32 comn0_smr68_offset_addr      ;    
    HI_U32 comn0_smr68_ptw_qos          ;    
    HI_U32 comn0_smr68_invld_en         ;    
    HI_U32 comn0_smr68_bypass           ;    
    HI_U32 comn0_smr69_offset_addr      ;    
    HI_U32 comn0_smr69_ptw_qos          ;    
    HI_U32 comn0_smr69_invld_en         ;    
    HI_U32 comn0_smr69_bypass           ;    
    HI_U32 comn0_smr70_offset_addr      ;    
    HI_U32 comn0_smr70_ptw_qos          ;    
    HI_U32 comn0_smr70_invld_en         ;    
    HI_U32 comn0_smr70_bypass           ;    
    HI_U32 comn0_smr71_offset_addr      ;    
    HI_U32 comn0_smr71_ptw_qos          ;    
    HI_U32 comn0_smr71_invld_en         ;    
    HI_U32 comn0_smr71_bypass           ;    
    HI_U32 comn0_smr72_offset_addr      ;    
    HI_U32 comn0_smr72_ptw_qos          ;    
    HI_U32 comn0_smr72_invld_en         ;    
    HI_U32 comn0_smr72_bypass           ;    
    HI_U32 comn0_smr73_offset_addr      ;    
    HI_U32 comn0_smr73_ptw_qos          ;    
    HI_U32 comn0_smr73_invld_en         ;    
    HI_U32 comn0_smr73_bypass           ;    
    HI_U32 comn0_smr74_offset_addr      ;    
    HI_U32 comn0_smr74_ptw_qos          ;    
    HI_U32 comn0_smr74_invld_en         ;    
    HI_U32 comn0_smr74_bypass           ;    
    HI_U32 comn0_smr75_offset_addr      ;    
    HI_U32 comn0_smr75_ptw_qos          ;    
    HI_U32 comn0_smr75_invld_en         ;    
    HI_U32 comn0_smr75_bypass           ;    
    HI_U32 comn0_smr76_offset_addr      ;    
    HI_U32 comn0_smr76_ptw_qos          ;    
    HI_U32 comn0_smr76_invld_en         ;    
    HI_U32 comn0_smr76_bypass           ;    
    HI_U32 comn0_smr77_offset_addr      ;    
    HI_U32 comn0_smr77_ptw_qos          ;    
    HI_U32 comn0_smr77_invld_en         ;    
    HI_U32 comn0_smr77_bypass           ;    
    HI_U32 comn0_smr78_offset_addr      ;    
    HI_U32 comn0_smr78_ptw_qos          ;    
    HI_U32 comn0_smr78_invld_en         ;    
    HI_U32 comn0_smr78_bypass           ;    
    HI_U32 comn0_smr79_offset_addr      ;    
    HI_U32 comn0_smr79_ptw_qos          ;    
    HI_U32 comn0_smr79_invld_en         ;    
    HI_U32 comn0_smr79_bypass           ;    
    HI_U32 comn0_smr_rld_en0            ;    
    HI_U32 comn0_smr_rld_en1            ;    
    HI_U32 comn0_smr_rld_en2            ;  
    
    //comn1  0x20623800
    HI_U32 comn1_cb_bypass             ;
    HI_U32 comn1_cb_ttbr0              ;
    HI_U32 comn1_cb_ttbr1              ;
    HI_U32 comn1_cb_ttbcr_t1sz         ;
    HI_U32 comn1_cb_ttbcr_n            ;
    HI_U32 comn1_cb_ttbcr_t0sz         ;
    HI_U32 comn1_cb_ttbcr_des          ;
    HI_U32 comn1_offset_addr_ns        ;
    HI_U32 comn1_cache_all_level       ;
    HI_U32 comn1_cache_all_invalid     ;
    HI_U32 comn1_cache_l1_security     ;
    HI_U32 comn1_cache_l1_invalid      ;
    HI_U32 comn1_cache_l2l3_strmid     ;
    HI_U32 comn1_cache_l2l3_invalid    ;
    HI_U32 comn1_fama_bps_msb_ns   ;
    HI_U32 comn1_fama_chn_sel_ns     ;
    HI_U32 comn1_fama_sdes_msb_ns  ;
    HI_U32 comn1_fama_ptw_msb_ns   ;
    HI_U32 comn1_msb_ova               ;
    HI_U32 comn1_msb_errwr             ;
    HI_U32 comn1_msb_errrd             ;
    HI_U32 comn1_err_rd_addr           ;
    HI_U32 comn1_err_wr_addr           ;
    HI_U32 comn1_dbg_tlb_type          ;
    HI_U32 comn1_dbg_tlbentry_pointer  ;
    HI_U32 comn1_dbg_tlbword_pointer   ;
    HI_U32 comn1_dbg_cache_l2_strmid   ;
    HI_U32 comn1_dbg_cache_l1_ns       ;
    HI_U32 comn1_dbg_cache_l1_pointer  ;
    HI_U32 comn1_dbg_cache_level       ;
    HI_U32 comn1_dbg_axilock_en        ;
    HI_U32 comn1_override_va           ;
    HI_U32 comn1_override_tbu_num      ;
    HI_U32 comn1_override_va_strmid    ;
    HI_U32 comn1_override_va_indexid   ;
    HI_U32 comn1_override_va_type      ;
    HI_U32 comn1_override_va_cfg       ;
    HI_U32 comn1_override_pref_addr    ;
    HI_U32 comn1_override_pref_strmid  ;
    HI_U32 comn1_override_pref_indexid ;
    HI_U32 comn1_override_pref_initial ;
    HI_U32 comn1_override_pref_type    ;
    HI_U32 comn1_override_pref_cfg     ;
    
    //comn2  0x20623a00
    HI_U32 comn2_smr0_offset_addr_s    ;
    HI_U32 comn2_smr0_nscfg_en         ;
    HI_U32 comn2_smr0_nscfg            ;
    HI_U32 comn2_smr1_offset_addr_s    ;
    HI_U32 comn2_smr1_nscfg_en         ;
    HI_U32 comn2_smr1_nscfg            ;
    HI_U32 comn2_smr2_offset_addr_s    ;
    HI_U32 comn2_smr2_nscfg_en         ;
    HI_U32 comn2_smr2_nscfg            ;
    HI_U32 comn2_smr3_offset_addr_s    ;
    HI_U32 comn2_smr3_nscfg_en         ;
    HI_U32 comn2_smr3_nscfg            ;
    HI_U32 comn2_smr4_offset_addr_s    ;
    HI_U32 comn2_smr4_nscfg_en         ;
    HI_U32 comn2_smr4_nscfg            ;
    HI_U32 comn2_smr5_offset_addr_s    ;
    HI_U32 comn2_smr5_nscfg_en         ;
    HI_U32 comn2_smr5_nscfg            ;
    HI_U32 comn2_smr6_offset_addr_s    ;
    HI_U32 comn2_smr6_nscfg_en         ;
    HI_U32 comn2_smr6_nscfg            ;
    HI_U32 comn2_smr7_offset_addr_s    ;
    HI_U32 comn2_smr7_nscfg_en         ;
    HI_U32 comn2_smr7_nscfg            ;
    HI_U32 comn2_smr8_offset_addr_s    ;
    HI_U32 comn2_smr8_nscfg_en         ;
    HI_U32 comn2_smr8_nscfg            ;
    HI_U32 comn2_smr9_offset_addr_s    ;
    HI_U32 comn2_smr9_nscfg_en         ;
    HI_U32 comn2_smr9_nscfg            ;
    HI_U32 comn2_smr10_offset_addr_s   ;
    HI_U32 comn2_smr10_nscfg_en        ;
    HI_U32 comn2_smr10_nscfg           ;
    HI_U32 comn2_smr11_offset_addr_s   ;
    HI_U32 comn2_smr11_nscfg_en        ;
    HI_U32 comn2_smr11_nscfg           ;
    HI_U32 comn2_smr12_offset_addr_s   ;
    HI_U32 comn2_smr12_nscfg_en        ;
    HI_U32 comn2_smr12_nscfg           ;
    HI_U32 comn2_smr13_offset_addr_s   ;
    HI_U32 comn2_smr13_nscfg_en        ;
    HI_U32 comn2_smr13_nscfg           ;
    HI_U32 comn2_smr14_offset_addr_s   ;
    HI_U32 comn2_smr14_nscfg_en        ;
    HI_U32 comn2_smr14_nscfg           ;
    HI_U32 comn2_smr15_offset_addr_s   ;
    HI_U32 comn2_smr15_nscfg_en        ;
    HI_U32 comn2_smr15_nscfg           ;
    HI_U32 comn2_smr16_offset_addr_s   ;
    HI_U32 comn2_smr16_nscfg_en        ;
    HI_U32 comn2_smr16_nscfg           ;
    HI_U32 comn2_smr17_offset_addr_s   ;
    HI_U32 comn2_smr17_nscfg_en        ;
    HI_U32 comn2_smr17_nscfg           ;
    HI_U32 comn2_smr18_offset_addr_s   ;
    HI_U32 comn2_smr18_nscfg_en        ;
    HI_U32 comn2_smr18_nscfg           ;
    HI_U32 comn2_smr19_offset_addr_s   ;
    HI_U32 comn2_smr19_nscfg_en        ;
    HI_U32 comn2_smr19_nscfg           ;
    HI_U32 comn2_smr20_offset_addr_s   ;
    HI_U32 comn2_smr20_nscfg_en        ;
    HI_U32 comn2_smr20_nscfg           ;
    HI_U32 comn2_smr21_offset_addr_s   ;
    HI_U32 comn2_smr21_nscfg_en        ;
    HI_U32 comn2_smr21_nscfg           ;
    HI_U32 comn2_smr22_offset_addr_s   ;
    HI_U32 comn2_smr22_nscfg_en        ;
    HI_U32 comn2_smr22_nscfg           ;
    HI_U32 comn2_smr23_offset_addr_s   ;
    HI_U32 comn2_smr23_nscfg_en        ;
    HI_U32 comn2_smr23_nscfg           ;
    HI_U32 comn2_smr24_offset_addr_s   ;
    HI_U32 comn2_smr24_nscfg_en        ;
    HI_U32 comn2_smr24_nscfg           ;
    HI_U32 comn2_smr25_offset_addr_s   ;
    HI_U32 comn2_smr25_nscfg_en        ;
    HI_U32 comn2_smr25_nscfg           ;
    HI_U32 comn2_smr26_offset_addr_s   ;
    HI_U32 comn2_smr26_nscfg_en        ;
    HI_U32 comn2_smr26_nscfg           ;
    HI_U32 comn2_smr27_offset_addr_s   ;
    HI_U32 comn2_smr27_nscfg_en        ;
    HI_U32 comn2_smr27_nscfg           ;
    HI_U32 comn2_smr28_offset_addr_s   ;
    HI_U32 comn2_smr28_nscfg_en        ;
    HI_U32 comn2_smr28_nscfg           ;
    HI_U32 comn2_smr29_offset_addr_s   ;
    HI_U32 comn2_smr29_nscfg_en        ;
    HI_U32 comn2_smr29_nscfg           ;
    HI_U32 comn2_smr30_offset_addr_s   ;
    HI_U32 comn2_smr30_nscfg_en        ;
    HI_U32 comn2_smr30_nscfg           ;
    HI_U32 comn2_smr31_offset_addr_s   ;
    HI_U32 comn2_smr31_nscfg_en        ;
    HI_U32 comn2_smr31_nscfg           ;
    HI_U32 comn2_smr32_offset_addr_s   ;
    HI_U32 comn2_smr32_nscfg_en        ;
    HI_U32 comn2_smr32_nscfg           ;
    HI_U32 comn2_smr33_offset_addr_s   ;
    HI_U32 comn2_smr33_nscfg_en        ;
    HI_U32 comn2_smr33_nscfg           ;
    HI_U32 comn2_smr34_offset_addr_s   ;
    HI_U32 comn2_smr34_nscfg_en        ;
    HI_U32 comn2_smr34_nscfg           ;
    HI_U32 comn2_smr35_offset_addr_s   ;
    HI_U32 comn2_smr35_nscfg_en        ;
    HI_U32 comn2_smr35_nscfg           ;
    HI_U32 comn2_smr36_offset_addr_s   ;
    HI_U32 comn2_smr36_nscfg_en        ;
    HI_U32 comn2_smr36_nscfg           ;
    HI_U32 comn2_smr37_offset_addr_s   ;
    HI_U32 comn2_smr37_nscfg_en        ;
    HI_U32 comn2_smr37_nscfg           ;
    HI_U32 comn2_smr38_offset_addr_s   ;
    HI_U32 comn2_smr38_nscfg_en        ;
    HI_U32 comn2_smr38_nscfg           ;
    HI_U32 comn2_smr39_offset_addr_s   ;
    HI_U32 comn2_smr39_nscfg_en        ;
    HI_U32 comn2_smr39_nscfg           ;
    HI_U32 comn2_smr40_offset_addr_s   ;
    HI_U32 comn2_smr40_nscfg_en        ;
    HI_U32 comn2_smr40_nscfg           ;
    HI_U32 comn2_smr41_offset_addr_s   ;
    HI_U32 comn2_smr41_nscfg_en        ;
    HI_U32 comn2_smr41_nscfg           ;
    HI_U32 comn2_smr42_offset_addr_s   ;
    HI_U32 comn2_smr42_nscfg_en        ;
    HI_U32 comn2_smr42_nscfg           ;
    HI_U32 comn2_smr43_offset_addr_s   ;
    HI_U32 comn2_smr43_nscfg_en        ;
    HI_U32 comn2_smr43_nscfg           ;
    HI_U32 comn2_smr44_offset_addr_s   ;
    HI_U32 comn2_smr44_nscfg_en        ;
    HI_U32 comn2_smr44_nscfg           ;
    HI_U32 comn2_smr45_offset_addr_s   ;
    HI_U32 comn2_smr45_nscfg_en        ;
    HI_U32 comn2_smr45_nscfg           ;
    HI_U32 comn2_smr46_offset_addr_s   ;
    HI_U32 comn2_smr46_nscfg_en        ;
    HI_U32 comn2_smr46_nscfg           ;
    HI_U32 comn2_smr47_offset_addr_s   ;
    HI_U32 comn2_smr47_nscfg_en        ;
    HI_U32 comn2_smr47_nscfg           ;
    HI_U32 comn2_smr48_offset_addr_s   ;
    HI_U32 comn2_smr48_nscfg_en        ;
    HI_U32 comn2_smr48_nscfg           ;
    HI_U32 comn2_smr49_offset_addr_s   ;
    HI_U32 comn2_smr49_nscfg_en        ;
    HI_U32 comn2_smr49_nscfg           ;
    HI_U32 comn2_smr50_offset_addr_s   ;
    HI_U32 comn2_smr50_nscfg_en        ;
    HI_U32 comn2_smr50_nscfg           ;
    HI_U32 comn2_smr51_offset_addr_s   ;
    HI_U32 comn2_smr51_nscfg_en        ;
    HI_U32 comn2_smr51_nscfg           ;
    HI_U32 comn2_smr52_offset_addr_s   ;
    HI_U32 comn2_smr52_nscfg_en        ;
    HI_U32 comn2_smr52_nscfg           ;
    HI_U32 comn2_smr53_offset_addr_s   ;
    HI_U32 comn2_smr53_nscfg_en        ;
    HI_U32 comn2_smr53_nscfg           ;
    HI_U32 comn2_smr54_offset_addr_s   ;
    HI_U32 comn2_smr54_nscfg_en        ;
    HI_U32 comn2_smr54_nscfg           ;
    HI_U32 comn2_smr55_offset_addr_s   ;
    HI_U32 comn2_smr55_nscfg_en        ;
    HI_U32 comn2_smr55_nscfg           ;
    HI_U32 comn2_smr56_offset_addr_s   ;
    HI_U32 comn2_smr56_nscfg_en        ;
    HI_U32 comn2_smr56_nscfg           ;
    HI_U32 comn2_smr57_offset_addr_s   ;
    HI_U32 comn2_smr57_nscfg_en        ;
    HI_U32 comn2_smr57_nscfg           ;
    HI_U32 comn2_smr58_offset_addr_s   ;
    HI_U32 comn2_smr58_nscfg_en        ;
    HI_U32 comn2_smr58_nscfg           ;
    HI_U32 comn2_smr59_offset_addr_s   ;
    HI_U32 comn2_smr59_nscfg_en        ;
    HI_U32 comn2_smr59_nscfg           ;
    HI_U32 comn2_smr60_offset_addr_s   ;
    HI_U32 comn2_smr60_nscfg_en        ;
    HI_U32 comn2_smr60_nscfg           ;
    HI_U32 comn2_smr61_offset_addr_s   ;
    HI_U32 comn2_smr61_nscfg_en        ;
    HI_U32 comn2_smr61_nscfg           ;
    HI_U32 comn2_smr62_offset_addr_s   ;
    HI_U32 comn2_smr62_nscfg_en        ;
    HI_U32 comn2_smr62_nscfg           ;
    HI_U32 comn2_smr63_offset_addr_s   ;
    HI_U32 comn2_smr63_nscfg_en        ;
    HI_U32 comn2_smr63_nscfg           ;
    
    //comn3  0x20623c00
    HI_U32 comn3_smr64_offset_addr_s      ;             
    HI_U32 comn3_smr64_nscfg_en           ;       
    HI_U32 comn3_smr64_nscfg              ;       
    HI_U32 comn3_smr65_offset_addr_s      ;       
    HI_U32 comn3_smr65_nscfg_en           ;       
    HI_U32 comn3_smr65_nscfg              ;       
    HI_U32 comn3_smr66_offset_addr_s      ;       
    HI_U32 comn3_smr66_nscfg_en           ;       
    HI_U32 comn3_smr66_nscfg              ;       
    HI_U32 comn3_smr67_offset_addr_s      ;       
    HI_U32 comn3_smr67_nscfg_en           ;       
    HI_U32 comn3_smr67_nscfg              ;       
    HI_U32 comn3_smr68_offset_addr_s      ;       
    HI_U32 comn3_smr68_nscfg_en           ;       
    HI_U32 comn3_smr68_nscfg              ;       
    HI_U32 comn3_smr69_offset_addr_s      ;       
    HI_U32 comn3_smr69_nscfg_en           ;       
    HI_U32 comn3_smr69_nscfg              ;       
    HI_U32 comn3_smr70_offset_addr_s      ;       
    HI_U32 comn3_smr70_nscfg_en           ;       
    HI_U32 comn3_smr70_nscfg              ;       
    HI_U32 comn3_smr71_offset_addr_s      ;       
    HI_U32 comn3_smr71_nscfg_en           ;       
    HI_U32 comn3_smr71_nscfg              ;       
    HI_U32 comn3_smr72_offset_addr_s      ;       
    HI_U32 comn3_smr72_nscfg_en           ;       
    HI_U32 comn3_smr72_nscfg              ;       
    HI_U32 comn3_smr73_offset_addr_s      ;       
    HI_U32 comn3_smr73_nscfg_en           ;       
    HI_U32 comn3_smr73_nscfg              ;       
    HI_U32 comn3_smr74_offset_addr_s      ;       
    HI_U32 comn3_smr74_nscfg_en           ;       
    HI_U32 comn3_smr74_nscfg              ;       
    HI_U32 comn3_smr75_offset_addr_s      ;       
    HI_U32 comn3_smr75_nscfg_en           ;       
    HI_U32 comn3_smr75_nscfg              ;       
    HI_U32 comn3_smr76_offset_addr_s      ;       
    HI_U32 comn3_smr76_nscfg_en           ;       
    HI_U32 comn3_smr76_nscfg              ;       
    HI_U32 comn3_smr77_offset_addr_s      ;       
    HI_U32 comn3_smr77_nscfg_en           ;       
    HI_U32 comn3_smr77_nscfg              ;       
    HI_U32 comn3_smr78_offset_addr_s      ;       
    HI_U32 comn3_smr78_nscfg_en           ;       
    HI_U32 comn3_smr78_nscfg              ;       
    HI_U32 comn3_smr79_offset_addr_s      ;       
    HI_U32 comn3_smr79_nscfg_en           ;       
    HI_U32 comn3_smr79_nscfg              ;       
    HI_U32 comn3_smr_rld_en0_s            ;       
    HI_U32 comn3_smr_rld_en1_s            ;       
    HI_U32 comn3_smr_rld_en2_s            ;       
    HI_U32 comn3_ints_ptw_ns_msk          ;       
    HI_U32 comn3_ints_ptw_invalid_msk     ;       
    HI_U32 comn3_ints_ptw_trans_msk       ;       
    HI_U32 comn3_ints_tlbmiss_msk         ;       
    HI_U32 comn3_ints_ext_msk             ;       
    HI_U32 comn3_ints_permis_msk          ;       
    HI_U32 comn3_ints_ptw_ns_clr          ;       
    HI_U32 comn3_ints_ptw_invalid_clr     ;       
    HI_U32 comn3_ints_ptw_trans_clr       ;       
    HI_U32 comn3_ints_tlbmiss_clr         ;       
    HI_U32 comn3_ints_ext_clr             ;       
    HI_U32 comn3_ints_permis_clr          ;       
    HI_U32 comn3_glb_nscfg                ;       
    HI_U32 comn3_scb_bypass               ;       
    HI_U32 comn3_scb_ttbr                 ;       
    HI_U32 comn3_scb_ttbcr_des            ;       
    HI_U32 comn3_offset_addr_s            ;       
    HI_U32 comn3_fama_bps_msb_s           ;       
    HI_U32 comn3_fama_chn_sel_s           ;       
    HI_U32 comn3_fama_sdes_msb_s          ;       
    HI_U32 comn3_fama_ptw_msb_s           ;       
    HI_U32 comn3_dbg_tlb_en               ;       
    HI_U32 comn3_dbg_cache_en             ;       
    HI_U32 comn3_override_va_security     ;       
    
    // mmu0   0x20623e00
    HI_U32 glb_scr; 
    HI_U32 glb_bypass;  
    HI_U32 sid31_bypass;  
    HI_U32 sid30_bypass;  
    HI_U32 sid29_bypass;  
    HI_U32 sid28_bypass;  
    HI_U32 sid27_bypass;  
    HI_U32 sid26_bypass; 
    HI_U32 sid25_bypass;  
    HI_U32 sid24_bypass;  
    HI_U32 sid23_bypass;  
    HI_U32 sid22_bypass;  
    HI_U32 sid21_bypass;  
    HI_U32 sid20_bypass;
    HI_U32 sid19_bypass; 
    HI_U32 sid18_bypass;  
    HI_U32 sid17_bypass;  
    HI_U32 sid16_bypass;  
    HI_U32 sid15_bypass;  
    HI_U32 sid14_bypass;  
    HI_U32 sid13_bypass;
    HI_U32 sid12_bypass;  
    HI_U32 sid11_bypass;  
    HI_U32 sid10_bypass;
    HI_U32 sid9_bypass; 
    HI_U32 sid8_bypass;  
    HI_U32 sid7_bypass;  
    HI_U32 sid6_bypass;  
    HI_U32 sid5_bypass;  
    HI_U32 sid4_bypass;  
    HI_U32 sid3_bypass;
    HI_U32 sid2_bypass;  
    HI_U32 sid1_bypass;  
    HI_U32 sid0_bypass;
    HI_U32 sid63_bypass;  
    HI_U32 sid62_bypass;  
    HI_U32 sid61_bypass;  
    HI_U32 sid60_bypass; 
    HI_U32 sid59_bypass;  
    HI_U32 sid58_bypass;  
    HI_U32 sid57_bypass;  
    HI_U32 sid56_bypass; 
    HI_U32 sid55_bypass;  
    HI_U32 sid54_bypass;  
    HI_U32 sid53_bypass;  
    HI_U32 sid52_bypass;  
    HI_U32 sid51_bypass;  
    HI_U32 sid50_bypass;
    HI_U32 sid49_bypass; 
    HI_U32 sid48_bypass;  
    HI_U32 sid47_bypass;  
    HI_U32 sid46_bypass;  
    HI_U32 sid45_bypass;  
    HI_U32 sid44_bypass;  
    HI_U32 sid43_bypass;
    HI_U32 sid42_bypass;  
    HI_U32 sid41_bypass;  
    HI_U32 sid40_bypass;
    HI_U32 sid39_bypass; 
    HI_U32 sid38_bypass;  
    HI_U32 sid37_bypass;  
    HI_U32 sid36_bypass;  
    HI_U32 sid35_bypass;  
    HI_U32 sid34_bypass;  
    HI_U32 sid33_bypass;
    HI_U32 sid32_bypass;  
    
    HI_U32 mst_pref_0chn  ;   
    HI_U32 mst_pref_1chn  ; 
    HI_U32 mst_pref_2chn  ; 
    HI_U32 mst_pref_3chn  ; 
    HI_U32 mst_pref_4chn  ; 
    HI_U32 mst_pref_5chn  ;
    HI_U32 mst_pref_6chn  ; 
    HI_U32 mst_pref_7chn  ; 
    HI_U32 mst_pref_8chn  ;
    HI_U32 mst_pref_9chn  ; 
    HI_U32 mst_pref_10chn; 
    HI_U32 mst_pref_11chn; 
    HI_U32 mst_pref_12chn; 
    HI_U32 mst_pref_13chn; 
    HI_U32 mst_pref_14chn; 
    HI_U32 mst_pref_15chn;
    HI_U32 mst_pref_16chn; 
    HI_U32 mst_pref_17chn; 
    
    HI_U32 rd0_tlb_depth  ;   
    HI_U32 rd0_tlb_base  ; 
    HI_U32 rd0_tlb_last  ; 
    HI_U32 rd0_tlb_nxt  ; 
    HI_U32 rd0_tlb_uw  ; 
    HI_U32 rd0_tlb_upd_dis  ;
    HI_U32 rd0_tlb_upd_len  ; 
    HI_U32 rd1_tlb_depth  ;   
    HI_U32 rd1_tlb_base  ; 
    HI_U32 rd1_tlb_last  ; 
    HI_U32 rd1_tlb_nxt  ; 
    HI_U32 rd1_tlb_uw  ; 
    HI_U32 rd1_tlb_upd_dis  ;
    HI_U32 rd1_tlb_upd_len  ;
    HI_U32 rd2_tlb_depth  ;   
    HI_U32 rd2_tlb_base  ; 
    HI_U32 rd2_tlb_last  ; 
    HI_U32 rd2_tlb_nxt  ; 
    HI_U32 rd2_tlb_uw  ; 
    HI_U32 rd2_tlb_upd_dis  ;
    HI_U32 rd2_tlb_upd_len  ;
    HI_U32 rd3_tlb_depth  ;   
    HI_U32 rd3_tlb_base  ; 
    HI_U32 rd3_tlb_last  ; 
    HI_U32 rd3_tlb_nxt  ; 
    HI_U32 rd3_tlb_uw  ; 
    HI_U32 rd3_tlb_upd_dis  ;
    HI_U32 rd3_tlb_upd_len  ;
    HI_U32 rd4_tlb_depth  ;   
    HI_U32 rd4_tlb_base  ; 
    HI_U32 rd4_tlb_last  ; 
    HI_U32 rd4_tlb_nxt  ; 
    HI_U32 rd4_tlb_uw  ; 
    HI_U32 rd4_tlb_upd_dis  ;
    HI_U32 rd4_tlb_upd_len  ;
    HI_U32 rd5_tlb_depth  ;   
    HI_U32 rd5_tlb_base  ; 
    HI_U32 rd5_tlb_last  ; 
    HI_U32 rd5_tlb_nxt  ; 
    HI_U32 rd5_tlb_uw  ; 
    HI_U32 rd5_tlb_upd_dis  ;
    HI_U32 rd5_tlb_upd_len  ;
    HI_U32 rd6_tlb_depth  ;   
    HI_U32 rd6_tlb_base  ; 
    HI_U32 rd6_tlb_last  ; 
    HI_U32 rd6_tlb_nxt  ; 
    HI_U32 rd6_tlb_uw  ; 
    HI_U32 rd6_tlb_upd_dis  ;
    HI_U32 rd6_tlb_upd_len  ;
    HI_U32 rd7_tlb_depth  ;   
    HI_U32 rd7_tlb_base  ; 
    HI_U32 rd7_tlb_last  ; 
    HI_U32 rd7_tlb_nxt  ; 
    HI_U32 rd7_tlb_uw  ; 
    HI_U32 rd7_tlb_upd_dis  ;
    HI_U32 rd7_tlb_upd_len  ;
    HI_U32 rd8_tlb_depth  ;   
    HI_U32 rd8_tlb_base  ; 
    HI_U32 rd8_tlb_last  ; 
    HI_U32 rd8_tlb_nxt  ; 
    HI_U32 rd8_tlb_uw  ; 
    HI_U32 rd8_tlb_upd_dis  ;
    HI_U32 rd8_tlb_upd_len  ;
    HI_U32 rd9_tlb_depth  ;   
    HI_U32 rd9_tlb_base  ; 
    HI_U32 rd9_tlb_last  ; 
    HI_U32 rd9_tlb_nxt  ; 
    HI_U32 rd9_tlb_uw  ; 
    HI_U32 rd9_tlb_upd_dis  ;
    HI_U32 rd9_tlb_upd_len  ;
    
    HI_U32 wr0_tlb_depth  ;   
    HI_U32 wr0_tlb_base  ; 
    HI_U32 wr0_tlb_last  ; 
    HI_U32 wr0_tlb_nxt  ; 
    HI_U32 wr0_tlb_uw  ; 
    HI_U32 wr0_tlb_upd_dis  ;
    HI_U32 wr0_tlb_upd_len  ; 
    HI_U32 wr1_tlb_depth  ;   
    HI_U32 wr1_tlb_base  ; 
    HI_U32 wr1_tlb_last  ; 
    HI_U32 wr1_tlb_nxt  ; 
    HI_U32 wr1_tlb_uw  ; 
    HI_U32 wr1_tlb_upd_dis  ;
    HI_U32 wr1_tlb_upd_len  ;
    HI_U32 wr2_tlb_depth  ;   
    HI_U32 wr2_tlb_base  ; 
    HI_U32 wr2_tlb_last  ; 
    HI_U32 wr2_tlb_nxt  ; 
    HI_U32 wr2_tlb_uw  ; 
    HI_U32 wr2_tlb_upd_dis  ;
    HI_U32 wr2_tlb_upd_len  ;
    HI_U32 wr3_tlb_depth  ;   
    HI_U32 wr3_tlb_base  ; 
    HI_U32 wr3_tlb_last  ; 
    HI_U32 wr3_tlb_nxt  ; 
    HI_U32 wr3_tlb_uw  ; 
    HI_U32 wr3_tlb_upd_dis  ;
    HI_U32 wr3_tlb_upd_len  ;
    HI_U32 wr4_tlb_depth  ;   
    HI_U32 wr4_tlb_base  ; 
    HI_U32 wr4_tlb_last  ; 
    HI_U32 wr4_tlb_nxt  ; 
    HI_U32 wr4_tlb_uw  ; 
    HI_U32 wr4_tlb_upd_dis  ;
    HI_U32 wr4_tlb_upd_len  ;
    HI_U32 wr5_tlb_depth  ;   
    HI_U32 wr5_tlb_base  ; 
    HI_U32 wr5_tlb_last  ; 
    HI_U32 wr5_tlb_nxt  ; 
    HI_U32 wr5_tlb_uw  ; 
    HI_U32 wr5_tlb_upd_dis  ;
    HI_U32 wr5_tlb_upd_len  ;
    HI_U32 wr6_tlb_depth  ;   
    HI_U32 wr6_tlb_base  ; 
    HI_U32 wr6_tlb_last  ; 
    HI_U32 wr6_tlb_nxt  ; 
    HI_U32 wr6_tlb_uw  ; 
    HI_U32 wr6_tlb_upd_dis  ;
    HI_U32 wr6_tlb_upd_len  ;
    HI_U32 wr7_tlb_depth  ;   
    HI_U32 wr7_tlb_base  ; 
    HI_U32 wr7_tlb_last  ; 
    HI_U32 wr7_tlb_nxt  ; 
    HI_U32 wr7_tlb_uw  ; 
    HI_U32 wr7_tlb_upd_dis  ;
    HI_U32 wr7_tlb_upd_len  ;
}VeduEfl_EncPara_S_Cfg;

typedef struct
{
	VeduEfl_EncPara_S_Cfg * pstCfg_EncPara;

	HI_U32 bCfgVencPerFrame;

    HI_U32  RcnYHeadAddr[2];
    HI_U32  RcnCHeadAddr[2];

    HI_U32  VEDU_NBI_MVST_ADDR;
    HI_U32  VEDU_NBI_MVLD_ADDR;
    HI_U32  VEDU_PMELD_ADDR;
    HI_U32  VEDU_PMEST_ADDR;
    HI_U32  TUNLCELL_ADDR;
    HI_U32  RcnYHeadLength;
    HI_U32  RcnCHeadLength;

    HI_U32	VEDU_NBI_MVST_Length;
    HI_U32	VEDU_NBI_MVLD_Length;
    HI_U32	VEDU_PMELD_Length;
    HI_U32	VEDU_PMEST_Length;
    HI_U32  RcnYLength;
    HI_U32  RcnCLength;

    HI_U32  VEDU_MMU_ERR_RD_Length;
    HI_U32  VEDU_MMU_ERR_WR_Length;

    HI_U32 VEDU_SRC_YLength;
    HI_U32 VEDU_SRC_CLength;
    HI_U32 VEDU_SRC_VLength;

    /* stream buffer parameter */
    HI_U64	VEDU_STRM_ADDR[16];// 16片码流地址
    HI_U64	VEDU_STRM_BUFLEN[16]; // 16片码流最大长度
    HI_U64	VEDU_SLICE_LENGTH[16];	// 16片码流真正长度
    HI_U64	VEDU_SLICE_IS_END[16]; //16片码流是否end标志

    HI_U32  VEDU_HEADER[48];
    HI_U32  vlcst_para_set_en;
    HI_U32  vlcst_para_set_len;
    HI_U32  uHeaderRealLength;//sps pps真实长度

    /* 地址分配结构体 */
    MEM_BUFFER_S MEM_VEDU_START_ADDR;

    HI_U32  vcpi_protocol;
    HI_U32  vcpi_imgwidth_pix;//PicWidth
    HI_U32  vcpi_imgheight_pix;//PicHeight

    HI_U32  vcpi_multislc_en;//SliceSplitEn

    HI_S32  PicBits;
    HI_U32  I8x8Num;
    HI_U32  MeanQP;
    HI_U32  VencBufFull;
    HI_U32  VencEndOfPic;
    HI_U32  RcnIdx;
    VeduEfl_StatInfo_S  stStat;
    HI_U32  RcStart;

    HI_U32  ViFrmRate;
    HI_U32  VoFrmRate;

    HI_U32  IntraPic;
    HI_BOOL bAddHeader;//表示下一帧要不要带序列头信息
    HI_BOOL bRequestIFrame;
    HI_U32  InterFrmCnt;
    HI_U32  RcnYAddr[2];
    HI_U32  RcnCAddr[2];

    HI_U32  MMURdAddr;
    HI_U32  MMUWrAddr;

    HI_U8*  VirRcnYAddr[2];
    HI_U8*  VirRcnCAddr[2];

    HI_U8*  VirRcnYHAddr[2];
    HI_U8*  VirRcnCHAddr[2];

    HI_S32  NumRefIndex;

    HI_U8   Priority;
    HI_BOOL bStartEnc;
    HI_BOOL bFirstNal2Send;
    HI_BOOL bFirstSlc;
    volatile HI_U32  WaitingIsr;
    volatile HI_U32  CalcMd5Flag;

    queue_info_s *MsgQueue_OMX;
    queue_info_s *StreamQueue_OMX;
    queue_info_s *FrameQueue_OMX;

    HI_BOOL bOutPutbufflush;//表示buffer已经flush，不要再发送done消息
    HI_BOOL bInPutbufflush;

    venc_user_buf  stImage_OMX;

    HI_U32  YuvStoreType;
    HI_U32  YuvSampleType;

    HI_U32  YuvSelType;

    HI_U32  StoreFmt;
    VeduEfl_SrcInfo_S  stSrcInfo;
    HI_U32 *pRegBase;
    HI_S32  LowDlyMod;
    HI_U32  slchdr_part1;
    HI_U32  CABAC_SLCHDR_PART2_SEG[8];
    HI_U32  slchdr_size_part1;
    HI_U32  slchdr_size_part2;

    HI_U32  vcpi_frame_type;

    HI_U32  VEDU_CNTCLR;
    HI_U32  VEDU_FRAMENO;
    HI_U32  VEDU_TIMEOUT;

    HI_U32  curld_c_stride;
    HI_U32  curld_y_stride;

    HI_U32  vcpi_str_fmt;
    HI_U32  vcpi_store_mode;
    HI_U32  vcpi_package_sel;

    HI_U32  H265FrmNum;

    HI_U32  SlcHdrBits;
    HI_U32  SlcHdrStream [4];
    HI_U32  ReorderStream[2];
    HI_U32  MarkingStream[2];
    HI_U32  VEDU_SRC_YADDR;//SRC_YADDR
    HI_U32  VEDU_SRC_CADDR;//SRC_CADDR
    HI_U32  VEDU_SRC_VADDR;//VADDR

    HI_U32  VEDU_YH_ADDR;//YH_ADDR
    HI_U32  VEDU_CH_ADDR;//CH_ADDR
    HI_U32  VEDU_TUNLCELL_ADDR;

    HI_U32  VEDU_REF_YADDR;
    HI_U32  VEDU_REF_CADDR;
    HI_U32  VEDU_REC_YADDR;
    HI_U32  VEDU_REC_CADDR;

    HI_U32  VEDU_REF_YH_ADDR;
    HI_U32  VEDU_REF_CH_ADDR;

    HI_U32  VEDU_REC_YH_ADDR;
    HI_U32  VEDU_REC_CH_ADDR;

    HI_U32  bSAOEnabledFlag;

    HI_U32  VpsBits;
    HI_U32  SpsBits;
    HI_U32  PpsBits;
    HI_U8   VpsStream[VPS_MAX_LEN];
    HI_U8   SpsStream[SPS_MAX_LEN];
    HI_U8   PpsStream[PPS_MAX_LEN];

    HI_U32  H264FrmNum;
    HI_U32  H264Profile;

    HI_U32  Gop;
    HI_U32  bSliceLFAcrossSlicepps;

    /* rate control mid */

    VeduEfl_Rc_S stRc;

    HI_U32 PTS0;
    HI_U32 PTS1;

    HI_U32 idr_pic_id;
    HI_U32 EncFrameTotalNum;

    /* sequence rate control in */
    HI_S32 iImgWidth;
    HI_S32 iImgHeight;
    HI_S32 iFrameRate;
    HI_S32 iBitRate;
    //HI_S32 iMaxQP;//统一使用寄存器来配置 ljh
    //HI_S32 iMinQP;
    HI_S32 bFrameSkip;
    /* frame rate control out */
    HI_S32 iFrameQp;
    HI_S32 iAveLcuBits;
    /* rate control mid */
    HI_S32 iPicMbs;
    HI_S32 iVbvBufferSize;
    HI_S32 iVbvBuffFillFinal;
    HI_S32 iVbvBuffFillInit;
    HI_S32 iBitsPerFrame;
    HI_S32 iIBitsPerFrame;
    HI_S32 iPBitsPerFrame;
    HI_S32 iQpDelta;
    HI_S32 iCounter;
    HI_S32 iFrameBitsQueue[MAX_FRAME_RATE];
    HI_S32 iIntraPointer;
    HI_S32 aiIntraFrmBits[RC_MAX_INTRA_LOADSIZE];
    HI_S32 iInterPointer;
    HI_S32 aiInterFrmBits[RC_MAX_INTER_LOADSIZE];
	HI_S32 iTotalBits;
	HI_S32 iTargetBits;
	HI_S32 iInstBits;
	HI_S32 iStartQP;
	HI_S32 iMaxIBits;
	HI_S32 iMaxPBits;
	HI_S32 iIpQpDelta;
	HI_S32 iLastIFrameQp;
	HI_S32 iLastIFrameBits;
    HI_S32 aiIRatio[I_RATIO_NUM]; //I块比重
    HI_S32 iIRatioCounter;
    HI_S32 iIRatioDelta; //I块比重差
    HI_S32 iFrameCuNum; //一帧8x8块数
    HI_S32 iStaticFrame; //静止帧数
    HI_S32 iI8x8Num; //一帧8x8 I块数

	HI_S32 bLastIFrameFlag;
	HI_S32 bInitFlag;
	HI_S32 bReEncode;

	HI_U32 iSliceSplitNum; //每帧划分多少个slice ，后面根据上层进行配置 l00214825
	HI_U32 iCurrentStreamCnt; //当前一帧编码前获取到第几个码流buffer   l00214825

#ifdef OUTPUT_LOWDELAY_EN
	HI_U32 iLastEncodedStreamCnt;
#endif

    venc_user_buf  stStream_OMX[16];
    venc_user_buf  stStreamHeader_OMX;// 用来存储码流头  l00214825

#ifdef SAO_LOWPOWER_EN
    HI_U32  aiRatioSaoLumaOff;
    HI_U32  aiRatioSaoChromaOff;
    HI_U32  numof_Frame_Refresh;
    HI_U32  Sao_Frame_Count;
    HI_U32  abSaoLumaFlag;
    HI_U32  abSaoChromaFlag;
    HI_U32  sao2vcpi_lcu_cnt;
    HI_U32  sao2vcpi_saooff_num_luma;
    HI_U32  sao2vcpi_saooff_num_chroma;
#endif

    HI_U32  bMMUByPass;
    HI_U32  bAXIPressEn;
    HI_U32  QuickEncode;

    HI_U32  bSecureFlag;//是否安全通道标志	
/*************************************************************************************/
} VeduEfl_EncPara_S;

typedef struct
{
    HI_U32 BusViY;      /* 16-byte aligned  */
    HI_U32 BusViC;      /* 16-byte aligned  */
    HI_U32 BusViV;
    HI_U32 ViYStride;   /* 16-byte aligned  即SStrideY*/
    HI_U32 ViCStride;   /* 16-byte aligned  即SStrideC*/

    HI_U32 PTS0;
    HI_U32 PTS1;
  //ADD
    HI_U32   RStrideY;      /* 16-byte aligned  */
    HI_U32   RStrideC;      /* 16-byte aligned  */
    HI_U32   TunlCellAddr;
} VeduEfl_EncIn_S;

typedef struct
{
    HI_HANDLE EncHandle;
} VeduEfl_ChnCtx_S;

typedef struct
{
    HI_U32   IpFree;       /* for channel control */
    HI_HANDLE   CurrHandle;   /* used in ISR */
    HI_U32  *pRegBase;
    HI_VOID *pChnLock;     /* lock ChnCtx[MAX_CHN] */
    HI_VOID *pTask_Frame;        //for both venc & omxvenc
    HI_VOID *pTask_Stream;       //juse for omxvenc
    HI_U32   StopTask;
    HI_U32   TaskRunning;  /* to block Close IP */
} VeduEfl_IpCtx_S;

#ifdef MD5_WC_EN

typedef struct tagMD5Context
{
	HI_U32 buf[4];
	HI_U32 bits[2];
	union
	{
		HI_U8 b8[64];
		HI_U32 b32[16];
	} in;
} MD5Context;

#endif

typedef struct
{
    HI_U32 IsFPGA;
    HI_U32 VeduIrqNum;
    HI_U32 MmuIrqNum;
    HI_U32 VedusecIrqNum;
    HI_U32 MmusecIrqNum;
    HI_U32 VencRegBaseAddr;
    HI_U32 VencRegRange;
    HI_U64 SmmuPageBaseAddr;
}VeduEfl_DTS_CONFIG_S;

HI_S32	VENC_DRV_EflOpenVedu( HI_VOID );
HI_S32	VENC_DRV_EflCloseVedu( HI_VOID );
HI_S32 VENC_DRV_EflCreateVenc( HI_HANDLE *pEncHandle, VeduEfl_EncCfg_S *pEncCfg, HI_U32 Index, HI_UNF_VENC_CHN_ATTR_S *pstAttr);
HI_S32	VENC_DRV_EflDestroyVenc( HI_HANDLE EncHandle );
HI_S32	VENC_DRV_EflAttachInput( HI_HANDLE EncHandle, VeduEfl_SrcInfo_S *pSrcInfo );
HI_S32	VENC_DRV_EflDetachInput( HI_HANDLE EncHandle, VeduEfl_SrcInfo_S *pSrcInfo );
HI_S32	VENC_DRV_EflStartVenc( HI_HANDLE EncHandle );
HI_S32	VENC_DRV_EflStopVenc( HI_HANDLE EncHandle );
HI_S32	VENC_DRV_EflRcGetAttr( HI_HANDLE EncHandle, VeduEfl_RcAttr_S *pRcAttr );
HI_S32	VENC_DRV_EflRcAttrInit( HI_HANDLE EncHandle, VeduEfl_RcAttr_S *pRcAttr );
HI_S32  VENC_DRV_EflRcSetAttr( HI_HANDLE EncHandle, VeduEfl_RcAttr_S *pRcAttr );
HI_S32	VENC_DRV_EflRcFrmRateCtrl( HI_HANDLE EncHandle, HI_U32 TR );
HI_S32	VENC_DRV_EflRcOpenOneFrm( HI_HANDLE EncHandle );
HI_S32	VENC_DRV_EflRcCloseOneFrm( HI_HANDLE EncHandle );
HI_S32	VENC_DRV_EflStartOneFrameVenc( HI_HANDLE EncHandle, VeduEfl_EncIn_S *pEncIn );
HI_S32	VENC_DRV_EflEndOneFrameVenc( HI_HANDLE EncHandle );
HI_S32	VENC_DRV_EflRequestIframe( HI_HANDLE EncHandle );
HI_S32	VENC_DRV_EflSetResolution( HI_HANDLE EncHandle, HI_U32 FrameWidth, HI_U32 FrameHeight );
HI_S32	VENC_DRV_EflResumeVedu(HI_VOID);
HI_S32	VENC_DRV_EflGetBitStream( HI_HANDLE EncHandle, VeduEfl_NALU_S *pNalu );
HI_S32	VENC_DRV_EflSkpBitStream( HI_HANDLE EncHandle, VeduEfl_NALU_S *pNalu );
HI_S32	VENC_DRV_EflQueryStatInfo( HI_HANDLE EncHandle, VeduEfl_StatInfo_S *pStatInfo );
HI_U32	VENC_DRV_EflGetStreamLen( HI_HANDLE EncHandle );
HI_S32  VENC_DRV_EflQueueFrame( HI_HANDLE EncHandle, HI_DRV_VIDEO_FRAME_S  *pstFrame);
HI_S32  VENC_DRV_EflDequeueFrame( HI_HANDLE EncHandle, HI_DRV_VIDEO_FRAME_S  *pstFrame);
HI_S32  VENC_DRV_EflGetImage(HI_HANDLE EncHandle, HI_DRV_VIDEO_FRAME_S  *pstFrame);
HI_S32  VENC_DRV_EflGetImage_OMX(HI_HANDLE EncHandle, venc_user_buf *pstFrame);
HI_S32  VENC_DRV_EflGetStream_OMX(HI_HANDLE EncHandle, venc_user_buf *pstStream);

HI_S32  VENC_DRV_EflPutImage(HI_HANDLE EncHandle, HI_DRV_VIDEO_FRAME_S  *pstFrame);

HI_S32  VENC_DRV_EflCfgRegVenc( HI_HANDLE EncHandle );
HI_S32  VENC_DRV_EflStartVencByReg( HI_HANDLE EncHandle );
HI_VOID VENC_DRV_EflSortPriority(HI_VOID);

HI_VOID VENC_DRV_EflWakeUpThread(HI_VOID);

HI_VOID VENC_DRV_EflSceChaDetect(VeduEfl_Rc_S *pRc, HI_S32 w, HI_S32 h, HI_S32 IntraPic);
HI_S32  VEDU_DRV_EflRcInitQp(HI_S32 bits,HI_S32 w,HI_S32 h);
HI_S32  VENC_DRV_EflRcAverage(HI_S32 *pData,HI_S32 n);
HI_VOID VENC_DRV_EflRcCalIFrmQp(VeduEfl_Rc_S *pRc, HI_S32 w, HI_S32 h, HI_S32 times, HI_S32 GopLength,int FrameIMBRatio);
HI_VOID VENC_DRV_EflRcCalPFrmQp(VeduEfl_Rc_S *pRc, HI_S32 PrePicBits, HI_S32 FrameIMBRatio, HI_S32 Gop,HI_U32 u32BitRate);
HI_S32 VENC_DRV_DbgWriteYUV420(HI_U8* pSY,HI_U8* pSU,HI_U8* pSV,HI_S32 width,HI_S32 height);
HI_S32 VENC_DRV_DbgWriteYUV(HI_DRV_VIDEO_FRAME_S *pstFrame,HI_CHAR* pFileName,HI_U64 uVirOffset);
HI_S32 VENC_DRV_EflSuspendVedu( HI_VOID );
HI_S32 VENC_DRV_EflFlushStrmHeader( VeduEfl_EncPara_S  *pEncPara );
HI_VOID VENC_DRV_DpressRcn( HI_HANDLE EncHandle );
HI_VOID check_enc_para(VeduEfl_EncPara_S_Cfg* pEncPara, int bIntraFrame);
HI_VOID VENC_DRV_MD5_CALC(VeduEfl_EncPara_S * pEncPara,HI_U32 chanlnum);


#ifdef MD5_WC_EN
void MD5CalcTransform(HI_U32 buf[4], HI_U32 const in[16]);
void MD5CalcInit(MD5Context *ctx);
void MD5CalcUpdate(MD5Context *ctx, HI_U8 *buf, unsigned len);
void MD5CalcFinal(HI_U8 digest[16], MD5Context *ctx);
HI_S32 VENC_DRV_RYUV_MD5(HI_DRV_VIDEO_FRAME_S *pstFrame);
#endif
HI_S32  VENC_SetDtsConfig(VeduEfl_DTS_CONFIG_S* info);
/*************************************************************************************/
#ifdef __cplusplus
 #if __cplusplus
}
 #endif
#endif

#endif //__DRV_VENC_EFL_H__
