/*--------------------------------------------------------------------------------------------------------------------------*/
/*!!Warning: This is a key information asset of Huawei Tech Co.,Ltd                                                         */
/*CODEMARK:kOyQZYzjDpyGdBAEC2GaWinjiDDUykL9e8pckESWBbMVmSWkBuyJO01cTiy3TdzKxGk0oBQa
mSMf7J4FkTpfv/JzwTgKEHe/9N4yU5rqhEDaRH/mYdIijFrTqr/UaRBfB2ylm29ZtemC0p1r
w4HAPbbH4t6iDi2/mFtyUSlIVT+nKV/RdAMR1aHSV7g+kgmjqIqkz+fbghQ5WOLIdzoegXpN
g5jtTnC3wfIfHL1l2i3VPP7vDnS8SFyE8F5FzKsM8MBweNgjFJraJBZQN3rGeg==*/
/*--------------------------------------------------------------------------------------------------------------------------*/
/***********************************************************************
*
* Copyright (c) 2006 HUAWEI - All Rights Reserved
*
* File: $vfmw.h$
* Date: $2006/11/30$
* Revision: $v1.0$
* Purpose: interface header file of VFMW
*
*
* Change History:
*
* Date             Author            Change
* ====             ======            ======
* 2006/11/30       z56361            Original
*
*
* Dependencies:
*
************************************************************************/

#ifndef __VDEC_FIRMWARE_H__
#define __VDEC_FIRMWARE_H__

#if defined(VFMW_EXTRA_TYPE_DEFINE)
#include "hi_type.h"
#endif

#ifdef __cplusplus
extern "C" {
#endif

/***********************************************************************
      VFMWµÄ°æ±¾ºÅ
 ***********************************************************************/
#define  VFMW_VERSION_NUM       (2016010400)


/***********************************************************************
      Type Define 
 ***********************************************************************/
#if defined(VFMW_EXTRA_TYPE_DEFINE)
#define UINT64 HI_U64
#define SINT64 HI_S64
#define UINT32 HI_U32
#define SINT32 HI_S32
#define UINT16 HI_U16
#define SINT16 HI_S16
#define UINT8  HI_U8
#define SINT8  HI_S8
#define ULONG  HI_SIZE_T
#define UADDR  HI_U32

#ifndef VOID
#define VOID   HI_VOID
#endif

typedef const void CONSTVOID;
typedef unsigned   USIGN;
#else
typedef  unsigned long long UINT64;
typedef  long long          SINT64;
typedef  unsigned int       UINT32;
typedef  signed int         SINT32;
typedef  unsigned short     UINT16;
typedef  signed short       SINT16;
typedef  signed char        SINT8;
typedef  unsigned char      UINT8;
typedef  void               VOID;
typedef  unsigned int       UADDR;
typedef  const void         CONSTVOID;
typedef  unsigned           USIGN;
typedef  unsigned long      ULONG;
#endif

#ifndef NULL
  #define NULL               0L
#endif

#if  defined(PRODUCT_STB) || defined(PRODUCT_DPT)
  #define COMMAND_LINE_EXTRA
#endif

/***********************************************************************
      Constants 
 ***********************************************************************/
#ifdef HI_TVP_SUPPORT
// keep these channels for secure
#define  TVP_CHAN_NUM            (4)
#else
#define  TVP_CHAN_NUM            (0)
#endif

#ifdef ENV_SOS_KERNEL
/* Max support channel num */
#define  MAX_CHAN_NUM            (TVP_CHAN_NUM)
// channel for secure
#define  FIRST_CHAN_NUM          (0)
#define  LAST_CHAN_NUM           (MAX_CHAN_NUM)
#else
/* Max support channel num */
#define  MAX_CHAN_NUM            (32)
// channel for normal
#define  FIRST_CHAN_NUM          (TVP_CHAN_NUM)
#define  LAST_CHAN_NUM           (MAX_CHAN_NUM)
#endif

/* Output order */
#define  OUTPUT_IN_DEC           (1)
#define  OUTPUT_IN_DSP           (0)
                                
/* VFMW API return value */           
#define  VDEC_OK                (0)
#define  VDEC_ERR               (-1)
#define  VDEC_ERR_WRONG_PARAM   (-2)
#define  VDEC_ERR_NO_MEM        (-3)
#define  VDEC_ERR_VDEC_BUSY     (-4)
#define  VDEC_ERR_CHAN_FULL     (-5)
#define  VDEC_ERR_CHAN_RUN      (-6)
#define  VDEC_ERR_CHAN_STOP     (-7)
#define  VDEC_ERR_UNSUPPORT     (-8)
#define  VDEC_ERR_DEFAUT        (-10)

/* formal definition, to be removed later */
#define  VF_OK                  (1)
#define  VF_NO_MEM              (-1)
#define  VF_ERR_PARAM           (-2)
#define  VF_TIME_OUT            (-3)
#define  VF_VDM_ERR             (-4)
#define  VF_FORCE_STOP          (-5)
#define  VF_ERR_SYS             (-20)
#define  VF_ERR_SPS             (-21)
#define  VF_ERR_PPS             (-22)
#define  VF_ERR_SLICE           (-23)

/* extream value */
#define MAX_USRDAT_SIZE         (1024)

/* DAR(Display Aspect Ratio) */
typedef enum
{
    DAR_UNKNOWN = 0,
    DAR_4_3,
    DAR_16_9,
    DAR_221_100,
    DAR_235_100,
    DAR_IMG_SIZE,
    DAR_END_RESERVED
} VDEC_DAR_E;

/* PLUS_FS_NUM = DecFsNum - MaxRefFsNum */
#define PLUS_FS_NUM             (1)
#define MAX_FRAME_NUM           (32)
#define MIN_USERDEC_FRAME_NUM   (3)

/*PTS*/
#define PTS_NO_USE              (UINT64)(-1)

/***********************************************************************
      enums 
 ***********************************************************************/
// standard type
typedef enum
{
    VFMW_START_RESERVED = 0,
    VFMW_H264 = 0,
    VFMW_VC1,
    VFMW_MPEG4,
    VFMW_MPEG2,
    VFMW_H263,
    VFMW_DIVX3,
    VFMW_AVS,
    VFMW_JPEG,
    VFMW_REAL8 = 8,
    VFMW_REAL9 = 9,
    VFMW_VP6   = 10,
    VFMW_VP6F,
    VFMW_VP6A,
    VFMW_VP8,
    VFMW_SORENSON,
    VFMW_MVC,
    VFMW_HEVC,
    VFMW_RAW,
    VFMW_USER,           /*## vfmw simply provide frame path. for external decoder, eg. mjpeg ##*/
    VFMW_END_RESERVED
} VID_STD_E;

#define STD_START_RESERVED VFMW_START_RESERVED
#define STD_H264           VFMW_H264
#define STD_VC1            VFMW_VC1
#define STD_MPEG4          VFMW_MPEG4
#define STD_MPEG2          VFMW_MPEG2
#define STD_H263           VFMW_H263
#define STD_DIVX3          VFMW_DIVX3
#define STD_AVS            VFMW_AVS
#define STD_JPEG           VFMW_JPEG
#define STD_REAL8          VFMW_REAL8
#define STD_REAL9          VFMW_REAL9
#define STD_VP6            VFMW_VP6
#define STD_VP6F           VFMW_VP6F
#define STD_VP6A           VFMW_VP6A
#define STD_VP8            VFMW_VP8
#define STD_SORENSON       VFMW_SORENSON
#define STD_MVC            VFMW_MVC
#define STD_HEVC           VFMW_HEVC
#define STD_RAW            VFMW_RAW
#define STD_USER           VFMW_USER
#define STD_END_RESERVED   VFMW_END_RESERVED


/* buffer flags bits masks omx buffer flag. */
#define VDEC_BUFFERFLAG_EOS		        (0x00000001)
#define VDEC_BUFFERFLAG_STARTTIME       (0x00000002)
#define VDEC_BUFFERFLAG_DECODEONLY	    (0x00000004)
#define VDEC_BUFFERFLAG_DATACORRUPT	    (0x00000008)
#define VDEC_BUFFERFLAG_ENDOFFRAME	    (0x00000010)
#define VDEC_BUFFERFLAG_SYNCFRAME	    (0x00000020)
#define VDEC_BUFFERFLAG_EXTRADATA	    (0x00000040)
#define VDEC_BUFFERFLAG_CODECCONFIG	    (0x00000080)

/* channel capacity level */
typedef enum hiCAP_LEVEL_E
{
    CAP_LEVEL_MPEG_QCIF = 0,
    CAP_LEVEL_MPEG_CIF,
    CAP_LEVEL_MPEG_D1,
    CAP_LEVEL_MPEG_720,
    CAP_LEVEL_MPEG_FHD,
    CAP_LEVEL_H264_QCIF,
    CAP_LEVEL_H264_CIF,
    CAP_LEVEL_H264_D1,
    CAP_LEVEL_H264_720,
    CAP_LEVEL_H264_FHD,
    CAP_LEVEL_H264_BYDHD,

    CAP_LEVEL_1280x800,       
    CAP_LEVEL_800x1280,
    CAP_LEVEL_1488x1280,
    CAP_LEVEL_1280x1488,
    CAP_LEVEL_2160x1280,
    CAP_LEVEL_1280x2160,
    CAP_LEVEL_2160x2160, 
    CAP_LEVEL_4096x2160, 
    CAP_LEVEL_2160x4096, 
    CAP_LEVEL_4096x4096,
    CAP_LEVEL_8192x4096, 
    CAP_LEVEL_4096x8192, 
    CAP_LEVEL_8192x8192,

    CAP_LEVEL_SINGLE_IFRAME_FHD,
    CAP_LEVEL_USER_DEFINE_WITH_OPTION, 
	
    CAP_LEVEL_MVC_FHD,
    CAP_LEVEL_HEVC_QCIF,
    CAP_LEVEL_HEVC_CIF,
    CAP_LEVEL_HEVC_D1,
    CAP_LEVEL_HEVC_720,
    CAP_LEVEL_HEVC_FHD,
    CAP_LEVEL_HEVC_UHD,
    
    CAP_LEVEL_BUTT
} VDEC_CHAN_CAP_LEVEL_E;

/* VDEC control command id, different function have different CID. */
typedef enum hiVDEC_CID_E
{
    VDEC_CID_GET_GLOBAL_STATE=0,       /* 0. get global state */
    VDEC_CID_GET_CAPABILITY,           /* 1. get the capacity of the decoder */
    VDEC_CID_GET_GLOBAL_CFG,           /* 2. get the configured info of the decoder */
    VDEC_CID_CFG_DECODER,              /* 3. congfig the decoder */
    VDEC_CID_CREATE_CHAN,              /* 4. create channel */
    VDEC_CID_CREATE_CHAN_WITH_OPTION,  /* 5. create channel with options */
    VDEC_CID_DESTROY_CHAN,             /* 6. destroy channel */
    VDEC_CID_DESTROY_CHAN_WITH_OPTION, /* 7. destroy a channel created with options */
    VDEC_CID_GET_CHAN_CFG,             /* 8. get the configuration of the decode channel */
    VDEC_CID_CFG_CHAN,                 /* 9. config the decode channel */
    
    VDEC_CID_GET_CHAN_STATE=10,        /* 10. get the state of the decode channel */
    VDEC_CID_START_CHAN,               /* 11. start channel */
    VDEC_CID_STOP_CHAN,                /* 12. stop channel */
    VDEC_CID_RESET_CHAN,               /* 13. reset channel */
    VDEC_CID_SET_STREAM_INTF,          /* 14. set the stream access interface for the decode channel */
    VDEC_CID_GET_IMAGE_INTF,           /* 15. get the stream access interface for the decode channel */
    VDEC_CID_GET_STREAM_SIZE,          /* 16. get the stream size(in byte) held by vfmw */
    VDEC_CID_GET_HAL_MEMSIZE,          /* 17. get the memory budget for hal usage */
    VDEC_CID_GET_CHAN_MEMSIZE,         /* 18. get the memory budget for the specified channel capacity level */
    VDEC_CID_GET_CHAN_DETAIL_MEMSIZE_WITH_OPTION,  /*19. get the detailed memory budget according to the options */
    
    VDEC_CID_GET_CHAN_MEMADDR=20,      /* 20. get chan mem addr */
    VDEC_CID_GET_CHAN_ID_BY_MEM,       /* 21. querry the channel number according the memroy physical address */
    VDEC_CID_RELEASE_STREAM,           /* 22. reset scd to release stream buffers */
    VDEC_CID_RESET_CHAN_WITH_OPTION,   /* 23. reset channel with options to keep some characters of the channel */
    VDEC_CID_CFG_EXTRA,                /* 24. set decoder's extra_ref & extra_disp */
    
    VDEC_CID_GET_USRDEC_FRAME=30,      /* 30 for VFMW_USER channel, get a frame block from vfmw */
    VDEC_CID_PUT_USRDEC_FRAME,         /* 31 for VFMW_USER channel, push a frame(info) into vfmw */
    VDEC_CID_SET_DISCARDPICS_PARAM,    /* 32 get discard pictures parameters */
    VDEC_CID_SYNC_EXT_BUFFER,          /* 33 synchronize ext buffer state */

    VDEC_CID_SET_DBG_OPTION=40,        /* 40 set debug options */
    VDEC_CID_GET_DGB_OPTION,           /* 41 get debug options */
    VDEC_CID_SET_PTS_TO_SEEK,          /* 42 set pts to be seeked by vfmw */
    VDEC_CID_SET_TRICK_MODE,           /* 44 set fast forward or backword speed */
    VDEC_CID_SET_CTRL_INFO ,           /* 45 set pvr fast forward or backword stream info and control info */
    VDEC_CID_SET_FRAME_RATE,           /* 46 set frame rate to vfmw */
    VDEC_CID_START_LOWDLAY_CALC,       /* 47 start lowdelay performance calculation */
    VDEC_CID_STOP_LOWDLAY_CALC,        /* 48 stop  lowdelay performance calculation */

    VDEC_CID_ALLOC_MEM_TO_CHANNEL=50,  /* 50 alloc entir mem for vfmw */
    VDEC_CID_BIND_MEM_TO_CHANNEL,      /* 51 alloc seperate mem and bind to vfmw */
    VDEC_CID_ACTIVATE_CHANNEL,         /* 52 notify vfmw that mem already in position */

} VDEC_CID_E;

/* decode mode */
typedef enum
{
    IPB_MODE = 0,
    IP_MODE,
    I_MODE,
    DISCARD_MODE,
    DISCARD_B_BF_P_MODE    /* discard B before get first P */
} DEC_MODE_E;

/* user data source */
typedef enum
{
    USD_INVALID = 0,
    USD_MP2SEQ,
    USD_MP2GOP,
    USD_MP2PIC,
    USD_MP4VSOS,
    USD_MP4VSO,
    USD_MP4VOL,
    USD_MP4GOP,
    USD_H264,
    USD_AVSSEQ,
    USD_AVSPIC
} VDEC_USD_TYPE_E;

/* event type */
typedef enum
{
    EVNT_DISP_EREA = 1,
    EVNT_IMG_SIZE_CHANGE,
    EVNT_FRMRATE_CHANGE,
    EVNT_SCAN_CHANGE,
    EVNT_NEW_IMAGE,
    EVNT_USRDAT,
    EVNT_ASPR_CHANGE,
    EVNT_OUTPUT_IMG_SIZE_CHANGE,  /* means a frame with different size is to be output */
    EVNT_FIND_IFRAME = 20,
    EVNT_STREAM_ERR = 100,
    EVNT_VDM_ERR,
    EVNT_UNSUPPORT,
    EVNT_SE_ERR,
    EVNT_OVER_REFTHR,
    EVNT_OVER_OUTTHR,
    EVNT_REF_NUM_OVER,
    EVNT_SIZE_OVER,
    EVNT_SLICE_NUM_OVER,
    EVNT_SPS_NUM_OVER,
    EVNT_PPS_NUM_OVER,
    EVNT_IFRAME_ERR,
    EVNT_MEET_NEWFRM,
    EVNT_DECSYNTAX_ERR,
    EVNT_RATIO_NOTZERO,
    EVNT_LAST_FRAME,
    EVNT_RESOLUTION_CHANGE,
	EVNT_STREAM_END_SYNTAX,
    EVNT_NEED_ARRANGE,
    EVNT_UNSUPPORT_SPEC,
    EVNT_FAKE_FRAME,
    EVNT_NEED_ARRANGE_L,
} VDEC_EVNT_TYPE_E;

/* buffer callbak type */
typedef enum
{
    BC_CHK_BUF = 0,
    BC_REPORT_BUF,
} VDEC_BC_TYPE_E;

typedef enum
{
    COLOR_FMT_400,       /*YUV 400*/
    COLOR_FMT_420,       /*YUV 420*/
    COLOR_FMT_422_2x1,   /*YUV 422 2x1*/
    COLOR_FMT_422_1x2,   /*YUV 422 1x2*/
    COLOR_FMT_444,       /*YUV 444*/
    COLOR_FMT_410,       /*YUV 410*/
    COLOR_FMT_411,       /*YUV 411*/
    COLOR_FMT_BUTT       /*other unsupported format*/
} COLOR_FMT_E;

/* unsupport specification */
typedef enum
{
    SPEC_BIT_DEPTH,    // unsupport bit depth
    SPEC_BUTT
} UNSUPPORT_SPEC_E;

/*adapter type*/
typedef enum
{
    ADAPTER_TYPE_VDEC = 0,
    ADAPTER_TYPE_OMXVDEC,
    ADAPTER_TYPE_BUTT,
} VDEC_ADAPTER_TYPE_E;

/*channel purpose*/
typedef enum
{
    PURPOSE_DECODE = 1,
    PURPOSE_FRAME_PATH_ONLY,
    PURPOSE_BUTT
} VDEC_CHAN_PURPOSE_E;

/*channel memory allocation type*/
typedef enum
{
    MODE_ALL_BY_SDK = 1,
    MODE_ALL_BY_MYSELF,
    MODE_PART_BY_SDK,
    MODE_BUTT,
} VDEC_CHAN_MEM_ALLOC_MODE_E;

/*memory type*/
typedef enum
{
    MEM_ION = 0,      // ion default
    MEM_CMA,          // kmalloc
    MEM_CMA_ZERO,     // kzalloc
} MEM_TYPE_E;

/*ext buf state*/
typedef enum
{
    EXTBUF_NULL = 0,       // ext buf not exist / or deleted
    EXTBUF_INSERT,         // ext buf first inserted
    EXTBUF_NOT_READY,      // ext buf not ready for use
    EXTBUF_READY,          // ext buf ready for use
    EXTBUF_TAKEN,          // ext buf already taken
} EXTBUF_STATE_E;

typedef enum
{
    FRAME_PACKING_TYPE_NONE,             /* normal frame, not a 3D frame */
    FRAME_PACKING_TYPE_SIDE_BY_SIDE,     /* side by side */
    FRAME_PACKING_TYPE_TOP_BOTTOM,       /* top bottom */
    FRAME_PACKING_TYPE_TIME_INTERLACED,  /* time interlaced: one frame for left eye, the next frame for right eye */
    FRAME_PACKING_TYPE_BUTT
} FRAME_PACKING_TYPE_E;

typedef enum YUV_FORMAT_E
{
    //Semi-Planner
    SPYCbCr400 = 0,
    SPYCbCr411,
    SPYCbCr420,
    SPYCbCr422_1X2,
    SPYCbCr422_2X1,
    SPYCbCr444,

    //Planner
    PLNYCbCr400,
    PLNYCbCr411,
    PLNYCbCr420,
    PLNYCbCr422_1X2,
    PLNYCbCr422_2X1,
    PLNYCbCr444,
    PLNYCbCr410,
    YCbCrBUTT
} YUV_FORMAT_E;

/***********************************************************************
      structures
 ***********************************************************************/
/* VDEC capacity */
typedef struct
{
    SINT32    s32MaxChanNum;
    SINT32    s32MaxBitRate;
    SINT32    s32MaxFrameWidth;
    SINT32    s32MaxFrameHeight;
    SINT32    s32MaxPixelPerSec;
    VID_STD_E SupportedStd[32];
} VDEC_CAP_S;

typedef union
{
    struct
    {
        SINT32 IsAdvProfile;
        SINT32 CodecVersion;
    } Vc1Ext;

    struct
    {
        SINT32 bReversed;   /**<if the image need to be reversed, set to 1, otherwise set to 0 */
    } Vp6Ext;
} STD_EXTENSION_U;

 /* channel config info */
typedef struct
{
    SINT8            s8SupportAllP;         /* support stream of all p frames */
    SINT8            s8ModuleLowlyEnable;   /* module lowdelay enable */
    SINT8            s8IsOmxPath;           /* specify for omx path */
    SINT8            s8SpecMode;            /* special mode, 0: normal, 1: CRC check */
    UINT8            u8UVOrder;             /* 0: uv, 1: vu */
    SINT8            s8DecOrderOutput ;     /* 0: output by display order£¬1:output by decode order */
    SINT8            s8LowdlyEnable ;       /* lowdly enable */
    SINT8            s8VcmpEn ;             /* frame compress enable */   
    SINT8            s8WmEn ;               /* water marker enable */
    DEC_MODE_E       s32DecMode;            /* decode mode£¬0£ºIPB£¬ 1£ºIP£¬ 2£ºI */
    SINT32           eVidStd;               /* video compressing standard */
    SINT32           s32ChanPriority;       /* channel priority */
    SINT32           s32ChanErrThr;         /* channel error torlerance threshold. 0: zero torlerance; 100: display no matter how many error occured */
    SINT32           s32ChanStrmOFThr;      /* stream overflow control threshold, must >= 0, 0 means do not enable overflow control */
    SINT32           s32VcmpWmStartLine;    /* water marker start line number */
    SINT32           s32VcmpWmEndLine;      /* water marker end line number */
    SINT32           s32MaxRawPacketNum;    /* omx path ext packet num */
    SINT32           s32MaxRawPacketSize;   /* omx path ext packet size */
    STD_EXTENSION_U  StdExt;                /* extended info, for VC1 indicate AP or not, and other version info */
} VDEC_CHAN_CFG_S;

typedef struct
{
   SINT32   s32Mode;   /*discard picture mode, 0: discard zero pictures, 1: discard pictures until s32Mode = 0, 2: discard s32DisNums pictures*/
   SINT32   s32DisNums;
}VDEC_DISPIC_PARAM_S;

/* userdata desc. */
typedef struct
{
    UINT8   data[MAX_USRDAT_SIZE]; /* USRDAT data entity */
    UINT8   pic_coding_type;
    UINT8   top_field_first;

    /* for CC, valid when IsRegistered=1 */
    SINT8   IsRegistered;
    UINT8   itu_t_t35_country_code;
    UINT8   itu_t_t35_country_code_extension_byte;
    UINT16  itu_t_t35_provider_code;
    UINT32  pic_num_count;
    UINT32  dnr_used_flag;         /* internal used only, ignore */
    VDEC_USD_TYPE_E  from;         /* USRDAT source */
    UINT32  seq_cnt;               /** to be removed later */
    UINT32  seq_img_cnt;
    SINT32  data_size;             /* USRDAT size, in byte */
    UINT64  PTS;                   /* pts of the frame containning the userdata */
} VDEC_USRDAT_S, USRDAT;

/* decoded image description */
typedef struct
{
    UINT32  u32AspectWidth;
    UINT32  u32AspectHeight;

    UINT32  DispEnableFlag;
    UINT32  DispFrameDistance;
    UINT32  DistanceBeforeFirstFrame;
    UINT32  GopNum;
    UINT32  u32RepeatCnt;

    UINT32  is_fld_save;  //0:frm, 1:fld
    UINT32  top_fld_type;
    UINT32  bottom_fld_type;

    /* [1:0] frame_type: 00(I), 01(P), 10(B), 11(Reserved)*/
    /* [4:2] CSP: 000(YUV:4:2:0), 001(YUV:4:0:0), 010~111(Reserved)*/
    /* [7:5] Norm: 000(component), 001(PLA), 010(NTSC), 011(SECAM), 100(MAC), 101(Unspecified Video Format), 110~111(Reserved)*/
    /* [9:8] source_format: 00(progressive), 01(interlaced), 10(infered_progressive), 11(infered_interlaced)*/
    /* [11:10] field_valid_flag: 00(top_field invalid, bottom_field invalid), 01(top_field valid, bottom_field invalid), 
               10(top_field invalid, bottom_field valid), 11(top_field valid, bottom_field valid)*/
    /* [13:12]top_field_first: 00(bottom field first), 01(top field first), 10(un-know), 11(Reserved)*/
    /* [16:14] aspect_ratio: 000(unspecified), 001(4:3), 010(16:9), 011(2.21:1),100(2.35:1),101(origin width and height), 111(Reserved)*/
    /* [31:17](Reserved)*/
    UINT32  format;
    UINT32  image_width;
    UINT32  image_height;
    UINT32  disp_width;
    UINT32  disp_height;
    UINT32  disp_center_x;
    UINT32  disp_center_y;

    UINT32  frame_rate;     /* frame rate, in Q10 */
    UINT32  image_stride;
    UINT32  image_id;
    UINT32  error_level;
    UINT32  seq_cnt;
    UINT32  seq_img_cnt;

    UINT32  bit_depth_luma;
    UINT32  bit_depth_chroma;
    UINT32  frame_num;
    SINT32  last_frame;
    SINT32  view_id;      //h264 mvc
    SINT32  image_id_1;
    UINT32  is_3D;
    UINT32  is_compress;
    UINT32  is_secure;  
    FRAME_PACKING_TYPE_E  eFramePackingType;
    
    UADDR   top_luma_phy_addr;
    UADDR   top_chrom_phy_addr;
    UADDR   btm_luma_phy_addr;
    UADDR   btm_chrom_phy_addr;
    UADDR   top_luma_phy_addr_1;
    UADDR   top_chrom_phy_addr_1;
    UADDR   btm_luma_phy_addr_1;
    UADDR   btm_chrom_phy_addr_1;
    
    UADDR   luma_phy_addr;
    UADDR   chrom_phy_addr;
    UADDR   luma_2d_phy_addr;
    UADDR   chrom_2d_phy_addr;
    UADDR   line_num_phy_addr;

    UINT32  left_offset;
    UINT32  right_offset;
    UINT32  top_offset;
    UINT32  bottom_offset;

    UINT32  ActualCRC[2];

    UINT64  SrcPts;
    UINT64  PTS;
    UINT64  Usertag;
    UINT64  DispTime;
    VDEC_USRDAT_S*  p_usrdat[4];
#ifdef ENV_SOS_KERNEL 
    /* For upper pointer, make struct with same size between 62bit normal and 32bit secure world */
    UINT32  Reserve[4];  //with same index with  p_usrdat 
#endif
} IMAGE;

/* frame desc for VFMW_USER */
typedef struct
{
    COLOR_FMT_E enFmt;           /* color format */
    SINT32  s32IsFrameValid; /* 1: frame valid, to be output to vo;  0: frame invalid, just free the frame-store */
    SINT32  s32IsSemiPlanar;
    SINT32  s32YWidth;
    SINT32  s32YHeight;
    UADDR   s32LumaPhyAddr;
    SINT32  s32LumaStride;
    UADDR   s32CbPhyAddr;    /* if semi-planar stand for the interlaced chrom addr; if planar stand for the Cb addr */
    UADDR   s32CrPhyAddr;    /* if semi-planar do not care£¬if planar stand for the Cr addr */
    SINT32  s32ChromStride;
    SINT32  s32ChromCrStride;
    UINT64  Pts;
} USRDEC_FRAME_DESC_S;

/* global state */
typedef struct
{
    UINT32  VFMW_version_number;
    SINT32  total_chan_num;
    SINT32  active_chan_num;
    SINT32  print_device;
    SINT32  print_enable;
} VDEC_GLOBAL_STATE_S;

/* REAL usr decode pic header */
typedef struct
{
    UINT32  PicFlag;
    UINT32  PicCodType;
    UINT32  PicWidthInPixel;
    UINT32  PicHeightInPixel;
    UINT32  Trb;
    UINT32  Trd;
    UINT32  Rounding;
    UINT32  TotalSliceNum;
} CB_PicHdrEnc_S;

/* REAL usr decode slice header */
typedef struct
{
    UINT32  SlcFlag;
    UINT32  SliceQP;
    UINT32  Osvquant;
    UINT32  DblkFilterPassThrough;
    UINT32  FirstMbInSlice;
    UINT32  BitOffset;
    UINT32  BitLen;
    UINT32  Reserve;
} CB_SlcHdrEnc_S;

/* channel state */
typedef struct
{
    UINT32  image_width;
    UINT32  image_height;
    UINT32  aspect_ratio;
    UINT32  scan_type;
    UINT32  video_format;
    UINT32  frame_rate;
    UINT32  bit_rate;
    UINT32  sub_video_standard;
    UINT32  profile;
    UINT32  level;
    SINT32  total_frame_num;
    SINT32  error_frame_num;
    SINT32  dec_error_frame_num;    /*the number of Frame which pErrRatio is not 0*/
    SINT32  decoded_1d_frame_num;   /* decoded, but not ready to display. generally refer to the decoded 1D frames */
    SINT32  buffered_stream_size;   /* the un-decoded stream seg produced by SCD */
    SINT32  buffered_stream_num;    /* the un-decoded stream seg num produced by SCD */

    UADDR   chan_mem_address;
    SINT32  chan_mem_size;
    SINT32  total_fstore_num;
    SINT32  total_pmv_num;
    SINT32  voque_detail;

    UINT32  stream_not_enough;
    UINT32  wait_disp_frame_num;
    UINT32  mpeg4_shorthead;        /* mpeg4 short head info, 1: sh 2:not sh  0:not mpeg4 stream */
    UINT32  total_disp_frame_num;   /* total display num ( plus extra_disp ) */
    UINT32  is_field_flg;           /* 0:frame 1:field */
} VDEC_CHAN_STATE_S;

/*Export image interface */
typedef SINT32 (*EXT_FN_READ_IMAGE)(SINT32, IMAGE*);
typedef SINT32 (*EXT_FN_RELEASE_IMAGE)(SINT32, IMAGE*);

/* image accessing interface */
/* NOTICE: NOT allow used in secure world for different size */
typedef struct
{
    SINT32                image_provider_inst_id;
    EXT_FN_READ_IMAGE     read_image;
    EXT_FN_RELEASE_IMAGE  release_image;
}IMAGE_INTF_S;

typedef struct
{
    UINT8   IsSeekPending;
    UINT32  Flags;
    UINT32  BufLen;
    UINT32  CfgWidth;
    UINT32  CfgHeight;
} RAW_EXTENSION_S;

/* stream packet struct */
typedef struct
{
    UINT8   is_not_last_packet_flag;
    UINT8   is_stream_end_flag; 
    SINT32  Length;
    UINT32  Index;
    UINT32  discontinue_count;
    UINT32  DispEnableFlag;
    UINT32  DispFrameDistance;
    UINT32  DistanceBeforeFirstFrame;
    UINT32  GopNum;
    UADDR   PhyAddr;
    UINT8  *VirAddr;
#ifdef ENV_SOS_KERNEL 
    /* For upper pointer, make struct with same size between 62bit normal and 32bit secure world */
    UINT32  Reserve;    
#endif
    UINT64  UserTag;
    UINT64  DispTime;
    UINT64  Pts;
    RAW_EXTENSION_S RawExt;          /* Omx raw buffer extension */
} STREAM_DATA_S;

typedef struct
{
    UINT32 u32IDRFlag;               /* IDR frame Flag, 1 means IDR frame */
    UINT32 u32BFrmRefFlag;           /* whether B frame is refer frame, 1 means B frame is refer frame */
    UINT32 u32ContinuousFlag;        /* whether send frame is continusous. 1 means continusous */
    UINT32 u32BackwardOptimizeFlag;  /* Backward optimize flag, 1 means optimize the backward fast play performance */
    UINT32 u32DispOptimizeFlag;      /* Display optimize flag, 1 means optimize the VO display performance */
} VFMW_CONTROLINFO_S;

/*Ext stream interface */
typedef SINT32 (*EXT_FN_READ_STREAM)(SINT32, STREAM_DATA_S*);
typedef SINT32 (*EXT_FN_RELEASE_STREAM)(SINT32, STREAM_DATA_S*);

/* stream accessing interface */
/* NOTICE: NOT allow used in secure world for different size */
typedef struct
{
    SINT32                 stream_provider_inst_id;
    EXT_FN_READ_STREAM     read_stream;
    EXT_FN_RELEASE_STREAM  release_stream;
} STREAM_INTF_S;

/* memory budget for a decode channel */
typedef struct
{
    SINT32  MinMemSize;
    SINT32  NormalMemSize;
    SINT32  FluentMemSize;
} CHAN_MEM_BUDGET_S;

/* memroy description */
typedef struct
{
    UINT8       IsSecure;
    MEM_TYPE_E  MemType;
    UADDR       PhyAddr;
    SINT32      Length;
    VOID*       VirAddr;
#ifdef ENV_SOS_KERNEL 
    /* For upper pointer, make struct with same size between 62bit normal and 32bit secure world */
    UINT32      Reserve;
#endif
} MEM_DESC_S;

/* detailed channel memory desc. */
typedef struct
{
    MEM_DESC_S  ChanMemVdh;
    MEM_DESC_S  ChanMemScd;
    MEM_DESC_S  ChanMemCtx;
} VDEC_CHAN_MEM_DETAIL_S;

/*For dynamic frame store param */
typedef struct
{
    UADDR  PhyAddr;
    UINT32 Length;
    UINT32 FrameNum;
    UINT32 NeedMMZ;
    VOID*  VirAddr;
#ifdef ENV_SOS_KERNEL 
    /* For upper pointer, make struct with same size between 62bit normal and 32bit secure world */
    UINT32 Reserve;
#endif
} VDEC_CHAN_FRAME_PARAM_S;

/*For dynamic seperated frame store param */
typedef struct
{
	UINT32      TotalFrameNum;
	MEM_DESC_S  stFrameBuf[MAX_FRAME_NUM];
	MEM_DESC_S  stPmvBuf[MAX_FRAME_NUM];
}VDEC_CHAN_FRAME_STORES;

/* user defined channel option */
typedef struct
{
    VDEC_ADAPTER_TYPE_E eAdapterType;          /* channel type vdec/omxvdec */
    VDEC_CHAN_PURPOSE_E Purpose;               /* channel purpose, indicate if this channel is used for decoding or frame path only*/
    VDEC_CHAN_MEM_ALLOC_MODE_E MemAllocMode;   /* who alloc memory for the channel */
    SINT32 s32MaxWidth;                        /* max width  supported by the channel*/
    SINT32 s32MaxHeight;                       /* max height supported by the channel*/
    SINT32 s32MaxSliceNum;                     /* for H264,H265 max slice number */
    SINT32 s32MaxVpsNum;                       /* for H264,H265 max vps number */
    SINT32 s32MaxSpsNum;                       /* for H264,H265 max sps number */
    SINT32 s32MaxPpsNum;                       /* for H264,H265 max pps number */
    SINT32 s32MaxRefFrameNum;                  /* max reference frame num*/
    SINT32 s32SupportBFrame;                   /* if support B frame. 1: yes, 0: no */
    UINT32 u32SupportStd;                      /* if this channel support H.264/MVC/H.265 decoding. bit 0:h264, 1:mvc, 2:h265 */
    SINT32 s32ScdLowdlyEnable;                 /* if this channel support scd lowdly. 1: yes, 0: no */
    SINT32 s32ReRangeEn;                       /* when resolution change, if the framestore be re-partitioned according to the new resolution. */
                                               /* 1:yes. can decode smaller(but more ref) stream, but one or more frame may be discarded */
                                               /* 0:no.  no frame discarded, but the stream with more ref can not dec, even if the total memory is enough */
    SINT32 s32SCDBufSize;                      /* SCD buf size */
    SINT32 s32DisplayFrameNum;                 /* user defined display frame num */
    SINT32 s32SlotWidth;                       /* if Purpose==PURPOSE_FRAME_PATH_ONLY, frame store width*/
    SINT32 s32SlotHeight;                      /* if Purpose==PURPOSE_FRAME_PATH_ONLY, frame store height*/
    UINT32 u32DynamicFrameStoreAllocEn;        /* for dynamic fs control, 1 enable, 0 disable */
    SINT32 s32DelayTime;                       /* for dynamic fs self alloc time out */
    UINT32 u32OmxBypassMode;                   /* for omx specific bypass mode */
    UINT32 u32IsSecMode;                       /* secure channel flag */
    VDEC_CHAN_MEM_DETAIL_S MemDetail;
} VDEC_CHAN_OPTION_S;

/* user defined channel reset option*/
typedef struct
{
    SINT32 s32KeepBS;                          /* keep bs in the scd buffer */
    SINT32 s32KeepSPSPPS;                      /* keep global info in ctx for seek reset, default 0 */
    SINT32 s32KeepFSP;                         /* keep info in fsp for seek reset, default 0 */
} VDEC_CHAN_RESET_OPTION_S;

typedef struct
{
    SINT32 VdhDetailMem;
    SINT32 ScdDetailMem;
    SINT32 CtxDetailMem;
} DETAIL_MEM_SIZE;

typedef struct
{
    UINT32 IsFPGA;
    UINT32 MfdeIrqNum;
    UINT32 ScdIrqNum;
    UINT32 BpdIrqNum;
    UINT32 SmmuIrqNum;
    UINT32 VdhRegBaseAddr;
    UINT32 VdhRegRange;
    UINT64 SmmuPageBaseAddr;
}VFMW_DTS_CONFIG_S;

typedef struct
{
    EXTBUF_STATE_E  State;
    UADDR           PhyAddr;
} EXTBUF_PARAM_S;

/*Ext interface */
typedef SINT32 (*EXT_FN_EVENT_CALLBACK)(SINT32, SINT32, VOID*, UINT32);
typedef SINT32 (*EXT_FN_BUFFER_CALLBACK)(SINT32, SINT32, VOID*);
typedef SINT32 (*EXT_FN_MEM_MALLOC)(SINT8*, UINT32, UINT32, VOID*);
typedef VOID   (*EXT_FN_MEM_FREE)(VOID*);
typedef SINT32 (*EXT_FN_POWER_ON)(VOID);
typedef SINT32 (*EXT_FN_POWER_OFF)(VOID);

/* callback interface */
/* NOTICE: NOT allow used in secure world for different size */
typedef struct
{
    EXT_FN_EVENT_CALLBACK  event_handler;
    EXT_FN_BUFFER_CALLBACK buffer_handler;
    EXT_FN_MEM_MALLOC      mem_malloc;
    EXT_FN_MEM_FREE        mem_free;
    EXT_FN_POWER_ON        power_on;
    EXT_FN_POWER_OFF       power_off;
} INIT_INTF_S;

/* external specified operations(method) */
typedef struct
{
    UINT8                  is_secure;
    VDEC_ADAPTER_TYPE_E    adapter_type;
    MEM_DESC_S             ext_halmem;
    INIT_INTF_S            ext_intf;
} VDEC_OPERATION_S;


/***********************************************************************
      functions
 ***********************************************************************/
VOID   VDEC_OpenModule(VOID);
VOID   VDEC_ExitModule(VOID);
SINT32 VDEC_Init(VDEC_OPERATION_S *pArgs);
SINT32 VDEC_Exit(UINT8 IsSecure);
SINT32 VDEC_Control(SINT32 ChanID, VDEC_CID_E eCmdID, VOID *pArgs, UINT32 ArgLen);
SINT32 VDEC_Suspend(VOID);
SINT32 VDEC_Resume(VOID);


#ifdef __cplusplus
}
#endif

#endif  // __VDEC_FIRMWARE_H__
