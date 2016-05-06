/******************************************************************************

                  版权所有 (C), 2001-2015, 华为技术有限公司

 ******************************************************************************
  文 件 名   : NasSndUsimm.h
  版 本 号   : 初稿
  作    者   : h00313353
  生成日期   : 2015年01月26日
  最近修改   :
  功能描述   : 供NAS USIM API调用的向USIMM发送消息的接口文件
  函数列表   :
  修改历史   :
  1.日    期   : 2015年01月26日
    作    者   : h00313353
    修改内容   : 创建文件

******************************************************************************/
#ifndef _NAS_SNDUSIMM_H_
#define _NAS_SNDUSIMM_H_

/*****************************************************************************
  1 其他头文件包含
*****************************************************************************/
#include "siapppb.h"
#include "siappstk.h"
#include "UsimPsInterface.h"
#include "NVIM_Interface.h"

#ifdef __cplusplus
#if __cplusplus
extern "C" {
#endif
#endif

/*****************************************************************************
  2 宏定义
*****************************************************************************/
#define NAS_SI_STK_ENVELOPEDOWN_ENCODE (1)
#define MAX_FILE_LENGTH (65535)
#define MIN_FILE_LENGTH (1)
#define BITS_OF_ONE_BYTE (8)
#define RECEIVERID_NOT_FOUND (0xFFFFF)
#define NAS_USIMM_UPDATEFILE_STRU_ARRAY_LENGTH (3)
#define NAS_SI_PB_ECALLQRY_REQ_STRU_ARRAY_LENGTH (3)
#define MAX_VALUE_OF_ONE_BYTE (255)


/*****************************************************************************
  3 枚举定义
*****************************************************************************/
/*****************************************************************************
 枚举名    : NAS_USIMM_SVLTE_TYPE_ENUM_UINT8
 结构说明  : svlte是否支持标识
  1.日    期   : 2015年01月27日
    作    者   : h00313353
    修改内容   : Create
*****************************************************************************/
enum NAS_USIMM_SVLTE_TYPE_ENUM
{
    NAS_USIMM_SVLTE_TYPE_NOT_SUPPORT    = 0x00,
    NAS_USIMM_SVLTE_TYPE_SUPPORT        = 0x01,

    NAS_USIMM_SVLTE_TYPE_BUTT
};

typedef VOS_UINT8 NAS_USIMM_SVLTE_TYPE_ENUM_UINT8;

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
  7 结构体定义
*****************************************************************************/
/*****************************************************************************
 结构名    : NAS_USIMM_UPDATEFILE_INFO_STRU
 结构说明  : 更新文件

 1.日    期   : 2015年02月03日
   作    者   : h00313353
   修改内容   : Create
*****************************************************************************/
typedef struct
{
    USIMM_CARDAPP_ENUM_UINT32   enAppType;      /* 应用类型 */
    VOS_UINT16                  usEfId;         /* 文件ID */
    VOS_UINT8                   ucRecordNum;    /* 文件记录号，二进制文件填0 */
    VOS_UINT8                   ucRsv;          /* 保留 */
    VOS_UINT32                  ulEfLen;        /* 更新数据长度 */
    VOS_UINT8                  *pucEfContent;   /* 更新数据内容 */
}NAS_USIMM_UPDATEFILE_DATA_STRU;

/*****************************************************************************
 结构名    : NAS_USIMM_GETFILE_INFO_STRU
 结构说明  : 获取文件

 1.日    期   : 2015年02月03日
   作    者   : h00313353
   修改内容   : Create
*****************************************************************************/
typedef struct
{
    USIMM_CARDAPP_ENUM_UINT32   enAppType;      /* 应用类型 */
    VOS_UINT16                  usEfId;         /* 文件ID */
    VOS_UINT8                   ucRecordNum;    /* 文件记录号，二进制文件填0 */
    VOS_UINT8                   ucRsv;          /* 保留 */
}NAS_USIMM_GETFILE_DATA_STRU;

/*****************************************************************************
 结构名    : NAS_USIMM_AUTH_DATA_STRU
 结构说明  : 鉴权数据

 1.日    期   : 2015年02月03日
   作    者   : h00313353
   修改内容   : Create
*****************************************************************************/
typedef struct
{
    USIMM_AUTH_TYPE_ENUM_UINT32         enAuthType;
    USIMM_AUTH_DATA_UNION               unAuthPara;
}NAS_USIMM_AUTH_DATA_STRU;

/*****************************************************************************
  8 UNION定义
*****************************************************************************/

/*****************************************************************************
  9 OTHERS定义
*****************************************************************************/

/*****************************************************************************
  10 函数声明
*****************************************************************************/
VOS_UINT32 NAS_SNDUSIMM_IsSvlteSupported(
    VOS_VOID
);

VOS_VOID NAS_SNDUSIMM_ReadSvlteSupportFlagNvim(
    VOS_VOID
);

NAS_USIMM_SVLTE_TYPE_ENUM_UINT8 NAS_SNDUSIMM_GetSvlteSupportFlag(
    VOS_VOID
);

VOS_VOID NAS_SNDUSIMM_SetSvlteSupportFlag(
    NAS_USIMM_SVLTE_TYPE_ENUM_UINT8     enSvlteSupportFlag
);

VOS_UINT32 NAS_SndUsimmUpdateFileReq(
    VOS_UINT32                          ulSenderPid,
    VOS_UINT32                          ulSendPara,
    NAS_USIMM_UPDATEFILE_DATA_STRU     *pstSetFileInfo
);

VOS_UINT32 NAS_SndUsimmReadFileReq(
    VOS_UINT32                          ulSenderPid,
    VOS_UINT32                          ulSendPara,
    NAS_USIMM_GETFILE_DATA_STRU        *pstGetFileInfo
);

VOS_UINT32 NAS_SndUsimmAuthReq(
    VOS_UINT32                          ulSenderPid,
    USIMM_CARDAPP_ENUM_UINT32           enAppType,
    NAS_USIMM_AUTH_DATA_STRU           *pstAuth,
    VOS_UINT8                           ucOpId
);

VOS_UINT32 NAS_SndUsimmPinReq(
    VOS_UINT32                          ulSenderPid,
    VOS_UINT8                           ucCmdType,
    VOS_UINT8                           ucPINType,
    VOS_UINT8                          *pucOldPIN,
    VOS_UINT8                          *pucNewPIN
);

VOS_UINT32 NAS_SndUsimmFdnNumCheckReq(
    VOS_UINT32                          ulPid,
    VOS_UINT32                          ulContextIndex,
    VOS_UINT32                          ulSendPara,
    SI_PB_FDN_NUM_STRU                 *pstFdnInfo
);

VOS_UINT32 NAS_SndUsimmQueryFileReq(
    VOS_UINT32                          ulSenderPid,
    USIMM_CARDAPP_ENUM_UINT32           enAppType,
    VOS_UINT16                          usEFid
);

VOS_UINT32 NAS_SndUsimmDeactiveCardReq(
    VOS_UINT32                          ulSenderPid
);

VOS_UINT32 NAS_SndUsimmEcallNumberQry(
    VOS_UINT32                          ulPid,
    SI_PB_STORAGE_ENUM_UINT32           enStorage,
    VOS_UINT8                           ucListLen,
    VOS_UINT8                          *pucList
);

VOS_UINT32 NAS_SndUsimmEnvelopeDownloadReq(
    VOS_UINT32                          ulSenderPid,
    VOS_UINT32                          ulSendPara,
    SI_STK_ENVELOPE_STRU               *pstENStru
);

VOS_UINT32 NAS_SndUsimmRestrictedAccessReq(
    VOS_UINT32                          ulSenderPid,
    VOS_UINT32                          ulSendPara,
    USIMM_RACCESS_REQ_STRU             *pstData
);

VOS_UINT32 NAS_SndUsimmRefreshReq(
    VOS_UINT32                          ulSenderPid,
    USIMM_STK_COMMAND_DETAILS_STRU     *pstCMDDetail,
    USIMM_RESET_INFO_STRU              *pstRstInfo
);

#ifdef __cplusplus
    #if __cplusplus
        }
    #endif
#endif

#endif /* END OF _NAS_SNDUSIMM_H_ */
