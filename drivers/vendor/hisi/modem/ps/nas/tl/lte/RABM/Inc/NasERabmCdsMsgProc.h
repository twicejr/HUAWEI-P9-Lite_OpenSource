

#ifndef __NASERABMCDSMSGPROC_H__
#define __NASERABMCDSMSGPROC_H__


/*****************************************************************************
  1 Include Headfile
*****************************************************************************/
#include  "CdsErabmInterface.h"
#include  "NasERabmPublic.h"

/*****************************************************************************
  1.1 Cplusplus Announce
*****************************************************************************/
#ifdef __cplusplus
#if __cplusplus
extern "C" {
#endif
#endif


/*****************************************************************************
  #pragma pack(*)    设置字节对齐方式
*****************************************************************************/
#if (VOS_OS_VER != VOS_WIN32)
#pragma pack(4)
#else
#pragma pack(push, 4)
#endif

/*****************************************************************************
  2 macro
*****************************************************************************/
/*定义IP的版本*/
#define NAS_ERABM_IP_VERSION_4                      (4)
#define NAS_ERABM_IP_VERSION_6                      (6)


/* 获取IP版本号 */
#define NAS_ERABM_GetIpVersion(pucIpMsg)\
                ((pucIpMsg)[0] >> NAS_ERABM_MOVEMENT_4_BITS )



/*****************************************************************************
  3 Massage Declare
*****************************************************************************/


/*****************************************************************************
  4 Enum
*****************************************************************************/



/*****************************************************************************
   5 STRUCT
*****************************************************************************/


/*****************************************************************************
  6 UNION
*****************************************************************************/


/*****************************************************************************
  7 Extern Global Variable
*****************************************************************************/


/*****************************************************************************
  8 Fuction Extern
*****************************************************************************/
extern VOS_VOID NAS_ERABM_SndErabmCdsFreeBuffDataInd( VOS_VOID );
extern VOS_VOID NAS_ERABM_SndErabmCdsSndBuffDataInd
(
    CDS_ERABM_SEND_BUFF_DATA_ALLOWED_TYPE_ENUM_UINT32   enSndBuffDataAllowedType
);

extern VOS_VOID NAS_ERABM_SndErabmCdsRabCreatInd( VOS_UINT32 ulEpsbId );

extern VOS_VOID NAS_ERABM_SndErabmCdsRabReleaseInd( VOS_UINT32 ulEpsbId );

extern VOS_VOID  NAS_ERABM_RcvCdsErabmServiceNotify
(
    const CDS_ERABM_SERVICE_NOTIFY_STRU    *pRcvMsg
);
extern VOS_VOID NAS_ERABM_CdsMsgDistr( VOS_VOID *pRcvMsg );
extern VOS_UINT32 NAS_ERABM_GetEpsbIdByDrbId
(
    VOS_UINT32                           ulRbId,
    VOS_UINT32                          *pulEpsbId
);

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

#endif /* end of NasERabmCdsMsgProc.h */
