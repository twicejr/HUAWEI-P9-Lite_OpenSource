


#ifndef __NASLPPDECODE_H__
#define __NASLPPDECODE_H__


/*****************************************************************************
  1 Include Headfile
*****************************************************************************/
#include  "vos.h"
#include  "NasLppEncodeDecodePublic.h"
#include  "NasLppOm.h"
#include  "NasLppDecode.h"

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
  2 Macro
*****************************************************************************/





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
extern VOS_UINT32  NAS_LPP_DecodeMessage(
                                VOS_UINT8 *pucDecodeInMsg,
                                VOS_UINT32 ulByteLen,
                                LPP_MESSAGE_STRU *pstLppMsg);
extern VOS_UINT32  NAS_LPP_Decode_ExtChoice(
                                                        VOS_UINT8                       *pDecodeBitStream,
                                                        VOS_UINT32                      *pCurrentBitPos,
                                                        VOS_UINT8                       ucLen,
                                                        VOS_UINT32                      *pExtChoiceValue);


extern VOS_UINT32  NAS_LPP_DecodeArfcnEutranV9a0(
                        VOS_UINT8                               *pDecodeBitStream,
                        VOS_UINT32                              *pCurrentBitPos,
                        LPP_ARFCN_VALUE_EUTRA_V9A0_STRU         *pstArfcnValueV9a0);

extern VOS_UINT32  NAS_LPP_DecodePlmnIdentity(
                        VOS_UINT8                               *pDecodeBitStream,
                        VOS_UINT32                              *pCurrentBitPos,
                        LPP_PLMN_IDENTITY_STRU                  *pstPlmnInetity);


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

#endif












































