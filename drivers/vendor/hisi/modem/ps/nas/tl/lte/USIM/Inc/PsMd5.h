

#ifndef __PSMD5_H__
#define __PSMD5_H__


/*****************************************************************************
  1 Include Headfile
*****************************************************************************/
#include "vos.h"
#include "LPsOm.h"

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

#if (VOS_OS_VER == VOS_WIN32)

#define NAS_USIM_MEM_CPY_S(pucDestBuffer, ulMaxDest, pucSrcBuffer, ulBufferLen) \
    NAS_LMM_SecuMemCpy((pucDestBuffer), (ulMaxDest), (pucSrcBuffer), (ulBufferLen), (__LINE__), (THIS_FILE_ID))

#define NAS_USIM_MEM_SET_S(pucBuffer, ulMaxDest, ucData, ulBufferLen) \
    NAS_LMM_SecuMemSet((pucBuffer), (ulMaxDest), (ucData), (ulBufferLen), (__LINE__), (THIS_FILE_ID))

#define NAS_USIM_MEM_MOVE_S(pucDestBuffer, ulMaxDest, pucSrcBuffer, ulBufferLen) \
    NAS_LMM_SecuMemMove( (pucDestBuffer), (ulMaxDest), (pucSrcBuffer), (ulBufferLen), (__LINE__), (THIS_FILE_ID))

#else

#define NAS_USIM_MEM_CPY_S(pDestBuffer, ulMaxDest, pSrcBuffer, ulLength ) \
        (VOS_VOID)TLPS_MEM_CPY_S(pDestBuffer, ulMaxDest, pSrcBuffer, ulLength, (__LINE__), (THIS_FILE_ID))

#define NAS_USIM_MEM_SET_S(pDestBuffer, ulMaxDest, ucData, ulLength) \
        (VOS_VOID)TLPS_MEM_SET_S((pDestBuffer), (ulMaxDest), (ucData), (ulLength), (__LINE__), (THIS_FILE_ID))

#define NAS_USIM_MEM_MOVE_S(pDestBuffer, ulMaxDest, pSrcBuffer, ulLength ) \
        (VOS_VOID)TLPS_MEM_MOVE_S((pDestBuffer), (ulMaxDest), (pSrcBuffer), (ulLength), (__LINE__), (THIS_FILE_ID))

#endif

/*****************************************************************************
  3 Massage Declare
*****************************************************************************/

/*****************************************************************************
  4 Enum
*****************************************************************************/

/*****************************************************************************
   5 STRUCT
*****************************************************************************/
#ifdef __alpha
typedef unsigned int uint32;
#else
typedef unsigned long uint32;
#endif

struct MD5Context {
        uint32 buf[4];
        uint32 bits[2];
        unsigned char in[64];
};
/*
 * This is needed to make RSAREF happy on some MS-DOS compilers.
 */
typedef struct MD5Context MD5_CTX;

/*****************************************************************************
  6 UNION
*****************************************************************************/


/*****************************************************************************
  7 Extern Global Variable
*****************************************************************************/


/*****************************************************************************
  8 Fuction Extern
*****************************************************************************/
extern void PS_MD5Init();
extern void PS_MD5Update();
extern void PS_MD5Final();
extern void PS_MD5Transform();
extern void PS_MD5String (const char *string, unsigned char result[16],unsigned char len);


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


#endif /* !PSMD5_H */
