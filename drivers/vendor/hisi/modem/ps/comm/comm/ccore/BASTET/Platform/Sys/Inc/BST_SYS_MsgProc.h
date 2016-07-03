
#ifndef __BST_MSGPROC_H__
#define __BST_MSGPROC_H__

#ifdef __cplusplus
#if __cplusplus
extern "C" {
#endif
#endif

#if (BST_OS_VER == BST_HISI_VOS)
#pragma pack(4)
#elif(BST_OS_VER == BST_WIN32)
#pragma pack(push, 4)
#endif

/*****************************************************************************
  1 其他头文件包含
*****************************************************************************/
#include  "vos.h"
#include  "PsTypeDef.h"
#include  "BST_PAL_As.h"


/*****************************************************************************
  2 宏定义
*****************************************************************************/
#define BST_SEND_SUCCESS                (0)
#define BST_SEND_FAILED                 (1)

/*****************************************************************************
  3 Massage Declare
*****************************************************************************/

/*****************************************************************************
  4 枚举定义
*****************************************************************************/

/*****************************************************************************
  5 类/结构定义
*****************************************************************************/

typedef struct
{
    BST_DRV_CHNLMODE_ENUM_UINT32     enChnlMode;
    VOS_UINT16                       usLimit;
    VOS_UINT8                        rbId;
    VOS_UINT8                        ucReserve;
} BST_PAL_CHNLMODE_STRU;


/*****************************************************************************
  6 UNION定义
*****************************************************************************/

/*****************************************************************************
  7 全局变量声明
*****************************************************************************/

/*****************************************************************************
  8 函数声明
*****************************************************************************/
BST_VOID BST_Pal_CdsRecv( MsgBlock *pstMsg );
BST_VOID BST_MSG_ProcMmaRecv( MsgBlock *pstMsg, BST_MODEM_ID_ENUM_UINT32 enModemId );
BST_VOID BST_PAL_SndMNReportFlag(
    BST_MODEM_ID_ENUM_UINT32    enPsModemId,
    BST_UINT8                   bReportFlag );
BST_VOID BST_MSG_ProcRrrcRealseSend(BST_VOID);
BST_VOID BST_MSG_ProcLRrcRealseSend(BST_VOID);
BST_VOID BST_MSG_ProcWrrcRecv( MsgBlock *pstMsg );
BST_VOID BST_MSG_ProcTrrcRecv( MsgBlock *pstMsg );
BST_VOID BST_MSG_ProcLrrcRecv( MsgBlock *pstMsg );

BST_VOID BST_MSG_ProcWRlcRecv( MsgBlock *pstMsg );
BST_VOID BST_MSG_ProcGRlcRecv( MsgBlock *pstMsg );

BST_UINT32 BST_MSG_SendWChnlModeInfo(
    BST_PAL_CHNLMODE_STRU      *pStChnlInfo);


/*****************************************************************************
  9 OTHERS定义
*****************************************************************************/


#if (BST_OS_VER == BST_HISI_VOS)
#pragma pack()
#elif(BST_OS_VER == BST_WIN32)
#pragma pack(pop)
#endif


#ifdef __cplusplus
#if __cplusplus
}
#endif
#endif


#endif
