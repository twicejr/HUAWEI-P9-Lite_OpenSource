


#ifndef __NAS_MSCC_PROC_USIM_H__
#define __NAS_MSCC_PROC_USIM_H__

/*****************************************************************************
  1 其他头文件包含
*****************************************************************************/
#include "vos.h"
#include "UsimPsInterface.h"
#include "NasMsccMntn.h"


#ifdef __cplusplus
#if __cplusplus
extern "C" {
#endif
#endif


#pragma pack(4)

/*****************************************************************************
  2 宏定义
*****************************************************************************/


/*****************************************************************************
  3 枚举定义
*****************************************************************************/


/*****************************************************************************
  4 全局变量声明
*****************************************************************************/
#ifdef DMT
extern NAS_MSCC_CARD_READ_STUB_TYPE_ENUM_UINT8 genCardReadStubTypeForDmt;
#endif

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
  8 UNION定义
*****************************************************************************/


/*****************************************************************************
  9 OTHERS定义
*****************************************************************************/


/*****************************************************************************
  10 函数声明
*****************************************************************************/

VOS_VOID NAS_MSCC_ReadUsimmFile(
    USIMM_CARDAPP_ENUM_UINT32                               enCardApp,
    USIMM_DEF_FILEID_ENUM_UINT32                            usFileId

);

#if (FEATURE_ON == FEATURE_UE_MODE_CDMA)

VOS_VOID NAS_MSCC_ReadAndParseMlplMsplNvim(VOS_VOID);

VOS_VOID  NAS_MSCC_RcvUsimmReadMlplFileCnf(
    USIMM_READFILE_CNF_STRU                                *pstUsimmReadCnfMsg
);

VOS_VOID  NAS_MSCC_RcvUsimmReadMsplFileCnf(
    USIMM_READFILE_CNF_STRU                                *pstUsimmReadCnfMsg
);

VOS_VOID  NAS_MSCC_RcvUsimmReadFileCnf(
    USIMM_READFILE_CNF_STRU                                *pstUsimmReadCnfMsg,
    USIMM_DEF_FILEID_ENUM_UINT32                            enEfId
);

VOS_VOID NAS_MSCC_ParseDefaultMlplMspl(VOS_VOID);

#ifdef DMT
VOS_VOID NAS_MSCC_SendCardReadTimerExpireMsgForDmt(VOS_VOID);
#endif

#endif

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

#endif /* end of NasMsccProcUsim.h */


