/******************************************************************************

        @(#)Copyright(C)2008,Hisilicon Co. LTD.

 ******************************************************************************
    File name   : NasLmmPubMMsgBuf.h
    Description :
    History     :
    1.zhengjunyan 00148421  2011-05-28 文件名由 NasMmPubMMsgBuf.h修改为NasLmmPubMMsgBuf.h
******************************************************************************/

#ifndef _NASLMMPUBMMSGBUF_H
#define _NASLMMPUBMMSGBUF_H

/*****************************************************************************
  1 其他头文件包含
*****************************************************************************/
#include    "vos.h"

#include    "NasLmmPubMFsm.h"

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
extern  VOS_UINT32  NAS_LMM_StoreMsgToQue(
                NAS_LMM_PARALLEL_FSM_ENUM_UINT16 enParalFsmId,
                VOS_UINT32                      ulBufPriLevel,
                VOS_UINT32                      ulMsgType,
                const VOS_VOID                  *pMsg );

extern VOS_UINT32  NAS_LMM_OutMsgFromQue( NAS_LMM_PARALLEL_FSM_ENUM_UINT16 enParalFsmId,
                                        VOS_UINT32     ulBufPriLevel,
                                        NAS_LMM_BUFF_MSG_STRU  *pstGetMsg );

extern NAS_LMM_BUFF_MSG_STRU * NAS_LMM_GetStoreBufMsgAddr(
                NAS_LMM_FSM_MSG_BUF_STRU*        pstFsmAddr,
                VOS_UINT32                      ulPriLevel);


/*extern  VOS_VOID *  NAS_LMM_OutMsgFromQue(
                NAS_LMM_PARALLEL_FSM_ENUM_UINT16  enParalFsmId,
                VOS_UINT32                       ulProcessFlag);
*/
extern  VOS_VOID    NAS_LMM_ClearBufMsgQue(
                NAS_LMM_PARALLEL_FSM_ENUM_UINT16  enParalFsmId,
                VOS_UINT32                       ulProcessFlag);

extern VOS_VOID  NAS_EMM_InitBufMsgQue( VOS_VOID );


extern VOS_VOID  NAS_EMMC_InitBufMsgQue( VOS_VOID );


extern NAS_LMM_FSM_MSG_BUF_STRU* NAS_LMM_GetFsmBufAddr( NAS_LMM_PARALLEL_FSM_ENUM_UINT16
                                                              enParalFsmId );
extern VOS_BOOL  NAS_LMM_RemoveMsgFromQue(
    NAS_LMM_BUFF_MSG_STRU*               pstMsgQue ,
    VOS_UINT8                           ucCnt,
    VOS_UINT32                          ulMsgType
                                           );


extern VOS_UINT32  NAS_LMM_ExistMsgInFsmQue(NAS_LMM_PARALLEL_FSM_ENUM_UINT16 enParalFsmId,
                                 VOS_UINT32                 ulPriLevel);

extern VOS_VOID  NAS_LMM_BufMsgQueFree( VOS_VOID );

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

#endif /* end of NasLmmPubMMsgBuf.h*/
