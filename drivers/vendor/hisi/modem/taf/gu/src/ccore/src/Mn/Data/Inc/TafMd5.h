

#ifndef _TAF_MD5_H_
#define _TAF_MD5_H_


/******************************************************************************
   1 头文件包含
 *****************************************************************************/
#include "vos.h"

#include "PsCommonDef.h"


#include "TafTypeDef.h"


#ifdef __cplusplus
#if __cplusplus
extern "C" {
#endif
#endif


/*****************************************************************************
   2 宏定义
 *****************************************************************************/



/*lint -e778 */
/*lint -e572 */
#ifndef VOS_NTOHL                   /* 大小字节序转换*/
#if VOS_BYTE_ORDER==VOS_BIG_ENDIAN
#define VOS_NTOHL(x)    (x)
#define VOS_HTONL(x)    (x)
#define VOS_NTOHS(x)    (x)
#define VOS_HTONS(x)    (x)
#else
#define VOS_NTOHL(x)    ((((x) & 0x000000ff) << 24) | \
             (((x) & 0x0000ff00) <<  8) | \
             (((x) & 0x00ff0000) >>  8) | \
             (((x) & 0xff000000) >> 24))

#define VOS_HTONL(x)    ((((x) & 0x000000ff) << 24) | \
             (((x) & 0x0000ff00) <<  8) | \
             (((x) & 0x00ff0000) >>  8) | \
             (((x) & 0xff000000) >> 24))

#define VOS_NTOHS(x)    ((((x) & 0x00ff) << 8) | \
             (((x) & 0xff00) >> 8))

#define VOS_HTONS(x)    ((((x) & 0x00ff) << 8) | \
             (((x) & 0xff00) >> 8))
#endif  /* _BYTE_ORDER==_LITTLE_ENDIAN */
#endif
/*lint -e572 */
/*lint -e778 */

/*******************************************************************************
  3 枚举定义
*******************************************************************************/


/*****************************************************************************
  4 全局变量声明
*****************************************************************************/


/*****************************************************************************
  6 STRUCT定义
*****************************************************************************/
#pragma pack(4)


typedef struct
{
    VOS_UINT32                            aulIndex[2];
    VOS_UINT32                            aulScrBuf[4];
    VOS_UINT8                             aucInBuf[64];
    VOS_UINT8                             aucDigest[16];
} TAF_MSG_DIGEST_FIVE_CTX;


#if ((VOS_OS_VER == VOS_WIN32) || (VOS_OS_VER == VOS_NUCLEUS))
#pragma pack()
#else
#pragma pack(0)
#endif

/*****************************************************************************
  7 UNION定义
*****************************************************************************/


/*****************************************************************************
  8 OTHERS定义
*****************************************************************************/


/*****************************************************************************
  9 函数声明
*****************************************************************************/
TAF_VOID TAF_InitMsgDigestFiveCtxt(TAF_MSG_DIGEST_FIVE_CTX *pstMdCtxt);
VOS_VOID TAF_UpdateMsgDigestFiveCtxt(
    TAF_MSG_DIGEST_FIVE_CTX            *pstMdCtxt,
    VOS_UINT8                          *pucInBuf,
    VOS_UINT32                          ulInLen
);
VOS_VOID TAF_EndMsgDigestFive(
    VOS_UINT8                           hash[],
    TAF_MSG_DIGEST_FIVE_CTX            *pstMdCtxt
);


#ifdef __cplusplus
#if __cplusplus
}
#endif
#endif

#endif /*_TAF_MD5_H_*/

