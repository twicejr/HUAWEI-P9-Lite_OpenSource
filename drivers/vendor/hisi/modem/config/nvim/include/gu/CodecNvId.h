

#ifndef __CODECNVID_H__
#define __CODECNVID_H__

#ifdef __cplusplus
#if __cplusplus
extern "C" {
#endif
#endif

/****************************************************************************
  1 其他头文件包含
*****************************************************************************/
#include "NvIddef.h"

/*typedef VOS_UINT16  SYS_NV_ID_ENUM_U16;
 */

enum CODEC_NV_ID_ENUM
{
      en_NV_Item_MaxVolLevel = 0x7530,                                          /* 30000 */
      en_NV_HeadSetPara_Audio,                                                  /* 30001 */
      en_NV_HandSetPara_Audio,                                                  /* 30002 */
      en_NV_HandFreePara_Audio,                                                 /* 30003 */
      en_NV_PCVoice_Audio,                                                      /* 30004 */

      en_NV_Item_ErrLog_Enable,                                                 /* 30005 */
      en_NV_Item_ErrLog_DataStru,                                               /* 30006 */
      en_NV_Item_Hook_Enable_Target,                                            /* 30007 */

      en_NV_WB_MaxVolLevel,                                                     /* 30008 */

      en_NV_CLVL_VOLUM,                                                         /* 30009 */
      en_NV_VoiceTraceCfg,                                                      /* 30010 */
      en_NV_HifiTraceCfg,                                                       /* 30011 */

      en_NV_Item_SIO_Voice_Master,                                              /* 30012 */
      en_NV_AudioTraceCfg,                                                      /* 30013 */
      en_NV_Item_SIO_Audio_Master,                                              /* 30014 */

      en_NV_HifiPowerOffCfg,                                                    /* 30015 */
      en_NV_HifiWatchDogCfg,                                                    /* 30016 */

      en_NV_NB_HandSet1,                                                        /* 30017 */
      en_NV_NB_HandSet2,                                                        /* 30018 */
      en_NV_NB_HandSet3,                                                        /* 30019 */
      en_NV_NB_HandFree1,                                                       /* 30020 */
      en_NV_NB_HandFree2,                                                       /* 30021 */
      en_NV_NB_HandFree3,                                                       /* 30022 */
      en_NV_NB_CarFree1,                                                        /* 30023 */
      en_NV_NB_CarFree2,                                                        /* 30024 */
      en_NV_NB_CarFree3,                                                        /* 30025 */
      en_NV_NB_HeadSet1,                                                        /* 30026 */
      en_NV_NB_HeadSet2,                                                        /* 30027 */
      en_NV_NB_HeadSet3,                                                        /* 30028 */
      en_NV_NB_BlueTooth1,                                                      /* 30029 */
      en_NV_NB_BlueTooth2,                                                      /* 30030 */
      en_NV_NB_BlueTooth3,                                                      /* 30031 */
      en_NV_NB_PCVoice1,                                                        /* 30032 */
      en_NV_NB_PCVoice2,                                                        /* 30033 */
      en_NV_NB_PCVoice3,                                                        /* 30034 */
      en_NV_NB_HeadPhone1,                                                      /* 30035 */
      en_NV_NB_HeadPhone2,                                                      /* 30036 */
      en_NV_NB_HeadPhone3,                                                      /* 30037 */
      en_NV_WB_HandSet1,                                                        /* 30038 */                                                       /* 12335 */
      en_NV_WB_HandSet2,                                                        /* 30039 */
      en_NV_WB_HandSet3,                                                        /* 30040 */
      en_NV_WB_HandFree1,                                                       /* 30041 */
      en_NV_WB_HandFree2,                                                       /* 30042 */
      en_NV_WB_HandFree3,                                                       /* 30043 */
      en_NV_WB_CarFree1,                                                        /* 30044 */
      en_NV_WB_CarFree2,                                                        /* 30045 */
      en_NV_WB_CarFree3,                                                        /* 30046 */
      en_NV_WB_HeadSet1,                                                        /* 30047 */
      en_NV_WB_HeadSet2,                                                        /* 30048 */
      en_NV_WB_HeadSet3,                                                        /* 30049 */
      en_NV_WB_BlueTooth1,                                                      /* 30050 */
      en_NV_WB_BlueTooth2,                                                      /* 30051 */
      en_NV_WB_BlueTooth3,                                                      /* 30052 */
      en_NV_WB_PCVoice1,                                                        /* 30053 */
      en_NV_WB_PCVoice2,                                                        /* 30054 */
      en_NV_WB_PCVoice3,                                                        /* 30055 */
      en_NV_WB_HeadPhone1,                                                      /* 30056 */
      en_NV_WB_HeadPhone2,                                                      /* 30057 */
      en_NV_WB_HeadPhone3,                                                      /* 30058 */
      en_NV_PHY_MIC_NUM,                                                        /* 30059 */

      en_NV_SmartPACfg,                                                         /* 30060 */
      en_NV_AudioTxCompCfg,                                                     /* 30061 */
      en_NV_AudioRxCompCfg,                                                     /* 30062 */

      en_NV_Audio_HandFree1,                                                    /* 30063 */
      en_NV_Audio_HandFree2,                                                    /* 30064 */
      en_NV_Audio_HandFree3,                                                    /* 30065 */
      en_NV_Audio_HeadPhone1,                                                   /* 30066 */
      en_NV_Audio_HeadPhone2,                                                   /* 30067 */
      en_NV_Audio_HeadPhone3,                                                   /* 30068 */
      
      en_VoIP_NB_HandSetPara1,                                                  /* 30069 */
      en_VoIP_NB_HandSetPara2,                                                  /* 30070 */
      en_VoIP_NB_HandSetPara3,                                                  /* 30071 */
      en_VoIP_NB_HandFreePara1,                                                 /* 30072 */
      en_VoIP_NB_HandFreePara2,                                                 /* 30073 */
      en_VoIP_NB_HandFreePara3,                                                 /* 30074 */
      en_VoIP_NB_CarPara1,                                                      /* 30075 */
      en_VoIP_NB_CarPara2,                                                      /* 30076 */
      en_VoIP_NB_CarPara3,                                                      /* 30077 */
      en_VoIP_NB_HeadSetPara1,                                                  /* 30078 */
      en_VoIP_NB_HeadSetPara2,                                                  /* 30079 */
      en_VoIP_NB_HeadSetPara3,                                                  /* 30080 */
      en_VoIP_NB_BlueToothPara1,                                                /* 30081 */
      en_VoIP_NB_BlueToothPara2,                                                /* 30082 */
      en_VoIP_NB_BlueToothPara3,                                                /* 30083 */
      en_VoIP_NB_PCVoicePara1,                                                  /* 30084 */
      en_VoIP_NB_PCVoicePara2,                                                  /* 30085 */
      en_VoIP_NB_PCVoicePara3,                                                  /* 30086 */
      en_VoIP_NB_HeadPhonePara1,                                                /* 30087 */
      en_VoIP_NB_HeadPhonePara2,                                                /* 30088 */
      en_VoIP_NB_HeadPhonePara3,                                                /* 30089 */
      
      en_VoIP_WB_HandSetPara1,                                                  /* 30090 */
      en_VoIP_WB_HandSetPara2,                                                  /* 30091 */
      en_VoIP_WB_HandSetPara3,                                                  /* 30092 */
      en_VoIP_WB_HandFreePara1,                                                 /* 30093 */
      en_VoIP_WB_HandFreePara2,                                                 /* 30094 */
      en_VoIP_WB_HandFreePara3,                                                 /* 30095 */
      en_VoIP_WB_CarPara1,                                                      /* 30096 */
      en_VoIP_WB_CarPara2,                                                      /* 30097 */
      en_VoIP_WB_CarPara3,                                                      /* 30098 */
      en_VoIP_WB_HeadSetPara1,                                                  /* 30099 */
      en_VoIP_WB_HeadSetPara2,                                                  /* 30100 */
      en_VoIP_WB_HeadSetPara3,                                                  /* 30101 */
      en_VoIP_WB_BlueToothPara1,                                                /* 30102 */
      en_VoIP_WB_BlueToothPara2,                                                /* 30103 */
      en_VoIP_WB_BlueToothPara3,                                                /* 30104 */
      en_VoIP_WB_PCVoicePara1,                                                  /* 30105 */
      en_VoIP_WB_PCVoicePara2,                                                  /* 30106 */
      en_VoIP_WB_PCVoicePara3,                                                  /* 30107 */
      en_VoIP_WB_HeadPhonePara1,                                                /* 30108 */
      en_VoIP_WB_HeadPhonePara2,                                                /* 30109 */
      en_VoIP_WB_HeadPhonePara3,                                                /* 30110 */
      
      en_MultiMic_NB_001,                                                       /* 30111 */
      en_MultiMic_NB_002,                                                       /* 30112 */
      en_MultiMic_NB_003,                                                       /* 30113 */
      en_MultiMic_NB_004,                                                       /* 30114 */
      en_MultiMic_NB_005,                                                       /* 30115 */
      en_MultiMic_NB_006,                                                       /* 30116 */
      en_MultiMic_NB_007,                                                       /* 30117 */
      en_MultiMic_NB_008,                                                       /* 30118 */
      en_MultiMic_NB_009,                                                       /* 30119 */
      en_MultiMic_NB_010,                                                       /* 30120 */
      en_MultiMic_NB_011,                                                       /* 30121 */
      en_MultiMic_NB_012,                                                       /* 30122 */
      en_MultiMic_NB_013,                                                       /* 30123 */
      en_MultiMic_NB_014,                                                       /* 30124 */
      en_MultiMic_NB_015,                                                       /* 30125 */
      en_MultiMic_WB_001,                                                       /* 30126 */
      en_MultiMic_WB_002,                                                       /* 30127 */
      en_MultiMic_WB_003,                                                       /* 30128 */
      en_MultiMic_WB_004,                                                       /* 30129 */
      en_MultiMic_WB_005,                                                       /* 30130 */
      en_MultiMic_WB_006,                                                       /* 30131 */
      en_MultiMic_WB_007,                                                       /* 30132 */
      en_MultiMic_WB_008,                                                       /* 30133 */
      en_MultiMic_WB_009,                                                       /* 30134 */
      en_MultiMic_WB_010,                                                       /* 30135 */
      en_MultiMic_WB_011,                                                       /* 30136 */
      en_MultiMic_WB_012,                                                       /* 30137 */
      en_MultiMic_WB_013,                                                       /* 30138 */
      en_MultiMic_WB_014,                                                       /* 30139 */
      en_MultiMic_WB_015,                                                       /* 30140 */      

      en_NV_OpenDSP_Config  = 30141,
      en_NV_Audio_Play_MBDRC_Config_Part1,                                      /* 30142 */
      en_NV_Audio_Play_MBDRC_Config_Part2,                                      /* 30143 */

      en_NV_Audio_HandSet1,                                                     /* 30144 */
      en_NV_Audio_HandSet2,                                                     /* 30145 */
      en_NV_Audio_HandSet3,                                                     /* 30146 */

      en_NV_VoiceDiagnoseCfg,                                                   /* 30147 */

      en_NV_VoiceJbCfg,                                                         /* 30148 */
      en_NV_VoiceDtmfCfg,                                                       /* 30149 */

      en_NV_Item_Codec_BUTT
};


#ifdef __cplusplus
    #if __cplusplus
        }
    #endif
#endif

#endif /* __CODECNVID_H__ */


