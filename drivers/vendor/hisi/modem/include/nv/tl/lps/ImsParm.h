#ifndef __IMS_PARM_PARM_H__
#define __IMS_PARM_PARM_H__

#ifndef HW_VOLTE
#include "vos.h"
#endif

#ifdef __cplusplus
extern "C" {
#endif

#ifdef HW_VOLTE
#ifndef VOS_INT8
#define VOS_INT8       char
#endif

#ifndef VOS_UINT8
#define VOS_UINT8      unsigned char
#endif

#ifndef VOS_INT16
#define VOS_INT16      short
#endif

#ifndef VOS_UINT16
#define VOS_UINT16     unsigned short
#endif

#ifndef VOS_INT32
#define VOS_INT32      long
#endif

#ifndef VOS_UINT32
#define VOS_UINT32     unsigned long
#endif
#endif
/*****************************************************************************
 * 0. Common
*****************************************************************************/
/** IMS String Parameter Size */
#define IMS_PARM_STRING_SIZE             (129)

/*****************************************************************************
 * 1. SIP
*****************************************************************************/
/** Indicates SIP transport type */
enum IMS_PARM_TRANSPORT_TYPE_ENUM{
    IMS_PARM_TRANSPORT_TYPE_UDP,
    IMS_PARM_TRANSPORT_TYPE_TCP,
    IMS_PARM_TRANSPORT_TYPE_BUTT
};
typedef VOS_UINT8 IMS_PARM_TRANSPORT_TYPE_ENUM_UINT8;

enum    IMS_PARM_URI_FORMAT_TYPE_ENUM
{
    IMS_PARM_URI_FORMAT_TYPE_DEFAULT      = 0x00,   /* default */
    IMS_PARM_URI_FORMAT_TYPE_SIP ,                  /* sip */
    IMS_PARM_URI_FORMAT_TYPE_TEL                    /* tel */
};
typedef VOS_UINT8 IMS_PARM_URI_FORMAT_TYPE_ENUM_UINT8;

/** SIP parameter definiton */
typedef struct{
    IMS_PARM_TRANSPORT_TYPE_ENUM_UINT8     ucTransportType;
    IMS_PARM_URI_FORMAT_TYPE_ENUM_UINT8    ucUriFormat;
    VOS_UINT8     ucHeaderCompactEnabled;
    VOS_UINT8     ucForkingFlag;
    VOS_UINT32    ulServerPort;
    VOS_UINT32    ulTimerSipRegValue;
    VOS_UINT32    ulTimerT1Value;
    VOS_UINT32    ulTimerT2Value;
    VOS_UINT32    ulTimerT4Value;
    VOS_UINT32    ulTimerTFValue;
    VOS_UINT32    ulTimerTJValue;
    VOS_UINT32    ulSipSocketKeepAliveValue;
    VOS_INT8      aucUserAgent[IMS_PARM_STRING_SIZE];
    VOS_INT8      ucTimerReg;
    VOS_INT8      aucSmsFormat_TimerDeReg[2];  /* aucSmsFormat_TimerDeReg[0]: instance msg uri format */
                                                                                 /* aucSmsFormat_TimerDeReg[1]: time length of deregister */
    VOS_UINT32    ulTcpThreshold;
}IMS_PARM_SIP_STRU;

/*****************************************************************************
 * 2. VOIP
*****************************************************************************/
/** Indicates Session Refresh type */
enum    IMS_PARM_SESSION_REFRESH_TYPE_ENUM
{
    IMS_PARM_SESSION_REFRESH_TYPE_UAC      = 0x00,   /* Client Refresh */
    IMS_PARM_SESSION_REFRESH_TYPE_UAS            ,   /* Server Refresh */
    IMS_PARM_SESSION_REFRESH_TYPE_BUTT
};
typedef VOS_UINT8   IMS_PARM_SESSION_REFRESH_TYPE_ENUM_UINT8;

/** Indicates Session Refresh method */
enum    IMS_PARM_SESSION_REFRESH_METHOD_ENUM
{
    IMS_PARM_SESSION_REFRESH_METHOD_UPDATE       = 0x00,   /* Update */
    IMS_PARM_SESSION_REFRESH_METHOD_REINVITE           ,   /* Reinvite */
    IMS_PARM_SESSION_REFRESH_METHOD_BUTT
};
typedef VOS_UINT8   IMS_PARM_SESSION_REFRESH_METHOD_ENUM_UINT8;

/** VOIP parameter definiton */
typedef struct{
    VOS_UINT8     ucSessionTimerEnabled;                                  /* Enabled Session Expire in Invite */
    VOS_UINT8     ucPreConditionEnabled;
    IMS_PARM_SESSION_REFRESH_TYPE_ENUM_UINT8     ucSessionRefreshType;
    IMS_PARM_SESSION_REFRESH_METHOD_ENUM_UINT8   ucSessionRefreshMethod;
    VOS_UINT16    usSessionExpires;
    VOS_UINT8     ucRTPInactiveTimer_IR92V90[2];           /* ucRTPInactiveTimer_IR92V90[0]:value:[0, 0XFF), value=0, turn off; value=0xFF, invalid; seconds
                                                                                                   ucRTPInactiveTimer_IR92V90[1]:value:  YYYY YXXX ------ X = 0, enable; X = 1, disable; Y = 0, reserved
                                                                                                                                                                           |||______  enable precondition with a = sendrecv
                                                                                                                                                                           ||_______  enable ue to send 183 with SDP in no precondition scenes
                                                                                                                                                                           |________  enable presentation of diverting parties and of diverted-to parties */
}IMS_PARM_VOIP_STRU;

/*****************************************************************************
 * 3. CODE
*****************************************************************************/
/** Indicates Audio Capability */
enum    IMS_PARM_AUDIO_CAP_ENUM
{
    IMS_PARM_AUDIO_CAP_AMR_NB_AND_WB           = 0x00,   /* AMR-NB and AMR-WB (AMR-NB preferred) */
    IMS_PARM_AUDIO_CAP_AMR_WB_AND_NB                 ,   /* AMR-WB and AMR-NB (AMR-WB preferred) */
    IMS_PARM_AUDIO_CAP_AMR_NB                        ,   /* AMR-NB */
    IMS_PARM_AUDIO_CAP_AMR_WB                        ,   /* AMR-WB */
    IMS_PARM_AUDIO_CAP_EVS_AND_AMR_NB_AND_WB,  /* AMR-NB and AMR-WB and EVS (EVS preferred) */
    IMS_PARM_AUDIO_CAP_EVS = 5,
    IMS_PARM_AUDIO_CAP_TYPE_BUTT
};
typedef VOS_UINT8   IMS_PARM_AUDIO_CAP_ENUM_UINT8;

/** Indicates Audio Code Mode */
enum    IMS_PARM_AUDIO_CODE_TYPE_ENUM
{
    IMS_PARM_AUDIO_CODE_MODE_OCTECT_ALIGN      = 0x00,  /* Octet-aligned Mode */
    IMS_PARM_AUDIO_CODE_MODE_BAND_EFFICIENT          ,  /* Bandwidth-Efficient Mode */
    IMS_PARM_AUDIO_CODE_MODE_EF_AND_OC               ,  /* bandwidth-efficient and octet-aligned Mode */
    IMS_PARM_AUDIO_CODE_MODE_OC_AND_EF               ,  /* octet-aligned and bandwidth-efficient Mode */
    IMS_PARM_AUDIO_CODE_TYPE_BUTT
};
typedef VOS_UINT8 IMS_PARM_AUDIO_CODE_MODE_ENUM_UINT8;

/** Indicates video resolution */
enum    IMS_PARM_VIDEO_RESOLUTION_ENUM
{
    IMS_PARM_VIDEO_RESOLUTION_CIF,
    IMS_PARM_VIDEO_RESOLUTION_VGA,
    IMS_PARM_VIDEO_RESOLUTION_720P,
    IMS_PARM_VIDEO_RESOLUTION_QVGA,
    IMS_PARM_VIDEO_RESOLUTION_BUTT
};
typedef VOS_UINT8 IMS_PARM_VIDEO_RESOLUTION_ENUM_UINT8;

/** Indicates h264 level*/
enum    IMS_PARM_VIDEO_H264_LEVEL_ENUM
{
    IMS_PARM_VIDEO_H264_LEVEL_12,
    IMS_PARM_VIDEO_H264_LEVEL_13,
    IMS_PARM_VIDEO_H264_LEVEL_22,
    IMS_PARM_VIDEO_H264_LEVEL_30,
    IMS_PARM_VIDEO_H264_LEVEL_31,
    IMS_PARM_VIDEO_H264_LEVEL_BUTT
};
typedef VOS_UINT8 IMS_PARM_VIDEO_H264_LEVEL_ENUM_UINT8;

/** Code parameter definiton */
typedef struct{
    IMS_PARM_AUDIO_CAP_ENUM_UINT8       ucAudioCap;           /* Audio Capabilities */
    VOS_UINT8                           ucSetNbAmrModeFlag;   /* Enabled setting Mode set of AMR-NB */
    VOS_UINT8                           ucSetWbAmrModeFlag;   /* Enabled setting Mode set of AMR-WB */
    VOS_UINT8                           ucReserved;
    VOS_UINT32                          ulNbAmrModeSet;       /* Mode set of AMR-NB */
    VOS_UINT32                          ulWbAmrModeSet;       /* Mode set of AMR-WB */
    IMS_PARM_AUDIO_CODE_MODE_ENUM_UINT8 ucNbAmrAudioCodeMode; /* Code Mode of AMR-NB */
    IMS_PARM_AUDIO_CODE_MODE_ENUM_UINT8 ucWbAmrAudioCodeMode; /* Code Mode of AMR-WB */
    VOS_UINT16                          usPtimerValue;        /* PTime */
    IMS_PARM_VIDEO_RESOLUTION_ENUM_UINT8 ucVideoResolution;   /* Video resolution*/
    IMS_PARM_VIDEO_H264_LEVEL_ENUM_UINT8 ucH264Level;         /* H264 level*/
    VOS_UINT8                           ucVideoFps;           /* Video Fps*/
    VOS_UINT8                           ucCVOFlag;            /* CVO Enabled */
    VOS_UINT32                          ulVideoBitrate;       /* Video Bitrate*/
}IMS_PARM_VOIP_CODE_STRU;

/*****************************************************************************
 * 4. Supplementary Service
*****************************************************************************/
/** Supplementary Service parameter definiton */
typedef struct{
    VOS_INT8      ucConfFactoryURI[IMS_PARM_STRING_SIZE];     /* Conference factory URI */
    VOS_INT8      aucRejectWith486[3];    /* aucRejectWith486[0]: value:[0, 1] set REJECT_WITH_486:486_WARNING_SWITCH
                                                                    * value=0, turn off,reject with 603; value=1, turn on, reject whit 486
                                                                    * aucRejectWith486[1]: reserved
                                                                    * aucRejectWith486[2]: reserved */
}IMS_PARM_SS_CONF_STRU;

/*****************************************************************************
 * 5. Security
*****************************************************************************/
/** Security parameter definiton */
typedef struct{
    VOS_UINT8     ucSrtpFlag;      /* SRTP enabled */
    VOS_UINT8     aucSockSupportlinger[3]; /*aucSockSupportlinger[0]: value:{0,1,2} set socket support linger function]
                                                                      value=0, default; value=1, if port is 5060,set true; value=2, set true
                                                                      aucSockSupportlinger[1]: reserved
                                                                      aucSockSupportlinger[2]: reserved*/
    struct{
        VOS_UINT8     ucNull;            /* 0 not support, 1 support. */
        VOS_UINT8     ucAes;             /* 0 not support, 1 support. */
        VOS_UINT8     uc3des;            /* 0 not support, 1 support. */
        VOS_UINT8     aucRsv[1];
    } stEAlgoCapability; /* ipsec encrypt algorithms capability */
    struct{
        VOS_UINT8     ucMd5;             /* 0 not support, 1 support. */
        VOS_UINT8     ucSha1;            /* 0 not support, 1 support. */
        VOS_UINT8     aucRsv[2];
    } stIAlgoCapability; /* ipsec integrity algorithms capability */
}IMS_PARM_SECURITY_STRU;

/*****************************************************************************
 * 6. Media
*****************************************************************************/
/** Media parameter definiton */
typedef struct{
    VOS_UINT8                          ucDtxEnable;          /* Enabled DTX flag */
    VOS_UINT8                          aucReserved[63];
}IMS_PARM_MEDIA_STRU;

/*****************************************************************************
 * 7. UE Capability
*****************************************************************************/
/* unsigned char type unit */
typedef struct{
    VOS_UINT8      ucReserved0;
    VOS_UINT8      ucReserved1;
    VOS_UINT8      ucReserved2;
    VOS_UINT8      ucReserved3;
    VOS_UINT8      ucReserved4;
    VOS_UINT8      ucReserved5;
    VOS_UINT8      ucReserved6;
    VOS_UINT8      ucReserved7;
    VOS_UINT8      ucReserved8;
    VOS_UINT8      ucReserved9;
    VOS_UINT8      ucReserved10;
    VOS_UINT8      ucReserved11;
    VOS_UINT8      ucReserved12;
    VOS_UINT8      ucReserved13;
    VOS_UINT8      ucReserved14;
    VOS_UINT8      ucReserved15;
}UINT8_NV_STRU;

/* unsigned short type unit */
typedef struct{
    VOS_UINT16     usReserved0;
    VOS_UINT16     usReserved1;
    VOS_UINT16     usReserved2;
    VOS_UINT16     usReserved3;
    VOS_UINT16     usReserved4;
    VOS_UINT16     usReserved5;
    VOS_UINT16     usReserved6;
    VOS_UINT16     usReserved7;
}UINT16_NV_STRU;

/* unsigned long type unit */
typedef struct{
    VOS_UINT32     ulReserved0;
    VOS_UINT32     ulReserved1;
    VOS_UINT32     ulReserved2;
    VOS_UINT32     ulReserved3;
    VOS_UINT32     ulReserved4;
    VOS_UINT32     ulReserved5;
    VOS_UINT32     ulReserved6;
    VOS_UINT32     ulReserved7;
}UINT32_NV_STRU;

/** UE Capability parameter definiton */
typedef struct{
    VOS_UINT8        ucRspSipTimeout;          /* initial register when receive 504 Msg 0-NotSupport 1-Support */
    VOS_UINT8        ucImageAttrFlag;          /* Suppot ImageAttr param in video call, 0 not support, 1 support. */
    VOS_UINT8        ucATTFeatureFlag;         /* Suppot AT&T feature flags.*/
    VOS_UINT8        ucReserved3;
    VOS_UINT8        ucReserved4;
    VOS_UINT8        ucReserved5;
    VOS_UINT8        ucReserved6;
    VOS_UINT8        ucReserved7;
    UINT8_NV_STRU    stUint8NVpara[16];
    UINT16_NV_STRU   stUint16NVpara[16];
    UINT32_NV_STRU   stUint32NVpara[8];

}IMS_PARM_UE_CAPABILITY_STRU;

#ifdef __cplusplus
}
#endif

#endif //__IMS_PARM_PARM_H__
