/******************************************************************************

                  版权所有 (C), 2001-2011, 华为技术有限公司

 ******************************************************************************
  文 件 名   : pppc_sha1.h
  版 本 号   : 初稿
  作    者   :
  生成日期   : 2015年11月10日
  最近修改   :
  功能描述   : pppc_sha1.c 的头文件
  函数列表   :
  修改历史   :
  1.日    期   : 2015年11月10日
    作    者   :
    修改内容   : 创建文件

******************************************************************************/

#ifndef __PPPC_SHA1_H__
#define __PPPC_SHA1_H__


/*****************************************************************************
  1 其他头文件包含
*****************************************************************************/
#include "PsCommonDef.h"
#include "PsTypeDef.h"
#include "ppp_dbug.h"



#ifdef __cplusplus
#if __cplusplus
extern "C" {
#endif
#endif

#pragma pack(4)

/*****************************************************************************
  2 宏定义
*****************************************************************************/

#define PPPC_SHA1_PARA_MAX_NUM          (12)                                    /* SHA1允许的最大参数 */

/*****************************************************************************
                SHA1算法相关宏定义  FIPS1802
*****************************************************************************/

#define PPPC_SHA1_BLOCK_SIZE            (64)                                    /* SHA1处理块大小 */
#define PPPC_SHA1_MAC_LEN               (20)                                    /* SHA1返回值长度 */

#define VOS_TRAN(var, num) (((var) << (num)) | ((var) >> (32 - (num))))
#define VOS_NUM1 (0xFF00FF00)
#define VOS_NUM2 (0x00FF00FF)
#define VOS_VAR0(index) (pStr->ulNum[index] = (VOS_TRAN(pStr->ulNum[index],24)&VOS_NUM1) \
        |(VOS_TRAN(pStr->ulNum[index],8)&VOS_NUM2))
#define VOS_VAR(index) (pStr->ulNum[index&15] = VOS_TRAN(pStr->ulNum[(index+13)&15]^pStr->ulNum[(index+8)&15] \
        ^pStr->ulNum[(index+2)&15]^pStr->ulNum[index&15],1))
#define VOS_NUM3 (0x5A827999)
#define VOS_NUM4 (0x6ED9EBA1)
#define VOS_NUM5 (0x8F1BBCDC)
#define VOS_NUM6 (0xCA62C1D6)

#define OPERA0(a,b,c,d,e,f) e+=((b&(c^d))^d)+VOS_VAR0(f)+VOS_NUM3+VOS_TRAN(a,5);b=VOS_TRAN(b,30);
#define OPERA1(a,b,c,d,e,f) e+=((b&(c^d))^d)+VOS_VAR(f)+VOS_NUM3+VOS_TRAN(a,5);b=VOS_TRAN(b,30);
#define OPERA2(a,b,c,d,e,f) e+=(b^c^d)+VOS_VAR(f)+VOS_NUM4+VOS_TRAN(a,5);b=VOS_TRAN(b,30);
#define OPERA3(a,b,c,d,e,f) e+=(((b|c)&d)|(b&c))+VOS_VAR(f)+VOS_NUM5+VOS_TRAN(a,5);b=VOS_TRAN(b,30);
#define OPERA4(a,b,c,d,e,f) e+=(b^c^d)+VOS_VAR(f)+VOS_NUM6+VOS_TRAN(a,5);b=VOS_TRAN(b,30);


/*****************************************************************************
  3 枚举定义
*****************************************************************************/


/*****************************************************************************
  4 全局变量声明
*****************************************************************************/


/*****************************************************************************
  5 消息头定义
*****************************************************************************/


/*****************************************************************************
  6 消息定义
*****************************************************************************/


/*****************************************************************************
  7 STRUCT定义
*****************************************************************************/

/*****************************************************************************
    SHA1算法结构体
*****************************************************************************/
typedef struct
{
    VOS_UINT32                          aulState[5];
    VOS_UINT32                          aulCount[2];
    VOS_UINT8                           aucBuffer[PPPC_SHA1_BLOCK_SIZE];
} PPPC_HRPD_SHA1_STRU;

/*****************************************************************************
    SHA1算法参数结构体
*****************************************************************************/
typedef struct
{
    VOS_UINT8                           ucNum;                                  /* 参数个数 */
    VOS_UINT8                           aucRsv[3];
    VOS_UINT8                          *apucAdrr[PPPC_SHA1_PARA_MAX_NUM];       /* 参数地址 */
    VOS_UINT32                          aulLen[PPPC_SHA1_PARA_MAX_NUM];         /* 参数长度 */
}PPPC_SHA1_PARA_STRU;


/*****************************************************************************
  8 UNION定义
*****************************************************************************/
typedef union
{
    VOS_UINT32 ulNum[16];
} VOS_CHAR64_TO_LONG16;


/*****************************************************************************
  9 OTHERS定义
*****************************************************************************/


/*****************************************************************************
  10 函数声明
*****************************************************************************/

VOS_UINT32 PPPC_EAP_PRF
(
   VOS_UINT8                          *pucKey,
   VOS_UINT8                           ucKeyLen,
   VOS_UINT8                          *pucMac,
   VOS_UINT8                           ucMacLen
);
VOS_UINT32 PPPC_SHA1
(
   PPPC_SHA1_PARA_STRU                *pstPara,
   VOS_UINT8                          *pucMac
);
VOS_UINT32 PPPC_HMAC_SHA1
(
    VOS_UINT8                          *pucKey,
    VOS_UINT8                           ucKeyLen,
    PPPC_SHA1_PARA_STRU                *pstPara,
    VOS_UINT8                          *pucMac
);





#if (VOS_OS_VER == VOS_WIN32)
#pragma pack()
#else
#pragma pack(0)
#endif




#ifdef __cplusplus
    #if __cplusplus
        }
    #endif
#endif

#endif /* end of pppc_sha1.h */

