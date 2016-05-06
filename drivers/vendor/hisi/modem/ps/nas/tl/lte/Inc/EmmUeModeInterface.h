/******************************************************************************

  Copyright(C)2008,Hisilicon Co. LTD.

 ******************************************************************************
  File Name       : EmmUeModeInterface.h
  Description     : UEMODE与LNAS的内部接口文件
  History         :
      1.HANLUFENG 41410 2011-09-20   Draft Enact

******************************************************************************/

#ifndef __EMMUEMODEINTERFACE_H__
#define __EMMUEMODEINTERFACE_H__


/*****************************************************************************
  1 Include Headfile
*****************************************************************************/
#include    "AppNasComm.h"

/*****************************************************************************
  1.1 Cplusplus Announce
*****************************************************************************/
#ifdef __cplusplus
#if __cplusplus
    extern "C" {
#endif
#endif


#if (VOS_OS_VER != VOS_WIN32)
 #pragma pack(4)
#else
 #pragma pack(push, 4)
#endif


/*****************************************************************************
  2 Macro
*****************************************************************************/

/*****************************************************************************
  3 Massage Declare
*****************************************************************************/


/*****************************************************************************
  4 Enum
*****************************************************************************/


/****************************************************************************
 枚举名称: NAS_LMM_UEMODE_INFO_TYPE_ENUM
 协议表格:
 ASN.1 描述:
 枚举说明:   LTE UE MODE 提供给LNAS各子模块模的信息枚举
*****************************************************************************/
enum NAS_LMM_UEMODE_TYPE_ENUM
{
    NAS_LMM_UEMODE_INFO_GU_UEMODE                        = 0x00000000,
    NAS_LMM_UEMODE_INFO_LTE_UEMODE,

    NAS_LMM_UEMODE_INFO_CENTER,

    NAS_LMM_UEMODE_INFO_SUP_VOICE_DOMAIN,
    NAS_LMM_UEMODE_INFO_VOICE_DOMAIN_PRE,

    NAS_LMM_UEMODE_INFO_SUP_SMS_DOMAIN,
    NAS_LMM_UEMODE_INFO_SMS_DOMAIN_PRE,

    NAS_LMM_UEMODE_INFO_SUP_IMS,
    NAS_LMM_UEMODE_INFO_NET_FEATURE,

    NAS_LMM_UEMODE_INFO_BUTT
};
typedef VOS_UINT32 NAS_LMM_UEMODE_TYPE_ENUM_UINT32;



/*****************************************************************************
  5 STRUCT
*****************************************************************************/

/****************************************************************************
 结构名称: NAS_LMM_UEMODE_INFO_STRU
 协议表格:
 ASN.1描述 :
 结构说明:
 *****************************************************************************/
typedef struct
{
    union
    {
        NAS_LMM_GU_UE_MODE_ENUM_UINT32          ulGuUeMode;
        NAS_LMM_UE_OPERATION_MODE_ENUM_UINT32   ulLteUeMode;

        NAS_EMM_USAGE_SETTING_UINT32            ulUsageSetting;

        /* UE 支持哪些语音域 */
        NAS_LMM_SUP_ENUM_UINT32                 aulLmmSupVoiceDomain[NAS_LMM_SUP_VOICE_DOMAIN_BUTT];

        /*Voice domain preference for E-UTRAN*/
        NAS_LMM_VOICE_DOMAIN_ENUM_UINT32        ulVoiceDomain;


        /* UE 支持哪些SMS域 */
        NAS_LMM_SUP_ENUM_UINT32                 aulLmmSupSmsDomain[NAS_LMM_SUP_SMS_DOMAIN_BUTT];

        /* UE 选择优先使用哪个域执行SMS业务 */
        NAS_LMM_SUP_SMS_DOMAIN_ENUM_UINT32      ulSmsDomainPrefer;


        NAS_LMM_SUP_ENUM_UINT32                 ulLmmSupIms;    /* UE LMM是否支持IMS */

        /*"CS fallback is not available" includes EMM causes #16, #17, #18 and #22*/
        /*NAS_LMM_SUP_ENUM_UINT32                 ulCSFBAvail;*/

        /*24301 960 9.9.3.12A EPS network feature support
          -----------------------------------------------------
            8  |  7  |  6  |  5  |  4  |   3   |  2   |  1
          -----------------------------------------------------
            0  |  0  |  0  |  CS-LCS   |EPC-LCS| EMCS | IMSVoPS
          ----------------------------------------------------- */
        VOS_UINT8                               ucNetFeature;   /* 当前网络是否支持IMS */
    }u;

} NAS_LMM_UEMODE_INFO_STRU;





/*****************************************************************************
  6 UNION
*****************************************************************************/


/*****************************************************************************
  7 Extern Global Variable
*****************************************************************************/


/*****************************************************************************
  8 Fuction Extern
*****************************************************************************/


/*****************************************************************************
  Function : Nas_GetLteUeModeInfo
  Input    :
  Output   :
  NOTE     :
  Return   :
  History  :
*****************************************************************************/
extern  VOS_UINT32  Nas_LMM_GetLteUeModeInfo
(
    NAS_LMM_UEMODE_TYPE_ENUM_UINT32     ulInfoType,
    NAS_LMM_UEMODE_INFO_STRU           *pstLmmUeModeInfo
);



/*****************************************************************************
   Function : Nas_SetLteUeModeInfo
   Input    :
   Output   :
   NOTE     :
   Return   :
   History  :

*****************************************************************************/
extern  VOS_UINT32  Nas_LMM_SetLteUeModeInfo
(
    NAS_LMM_UEMODE_TYPE_ENUM_UINT32     ulInfoType,
    NAS_LMM_UEMODE_INFO_STRU           *pstLmmUeModeInfo
);

extern VOS_VOID  NAS_EMM_PubmInfoUeModeInit(VOS_VOID);

/*****************************************************************************
  9 OTHERS
*****************************************************************************/



#if (VOS_OS_VER != VOS_WIN32)
 #pragma pack()
#else
 #pragma pack(pop)
#endif





#ifdef __cplusplus
    #if __cplusplus
        }
    #endif
#endif

#endif /* end of NasIpInterface.h */
