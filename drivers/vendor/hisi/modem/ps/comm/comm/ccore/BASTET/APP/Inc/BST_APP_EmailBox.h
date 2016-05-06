/******************************************************************************

                  版权所有 (C), 2001-2011, 华为技术有限公司

 ******************************************************************************
  文 件 名   : BST_APP_EmailBox.h
  版 本 号   : 初稿
  作    者   : d00173029
  生成日期   : 2013年10月9日
  最近修改   :
  功能描述   : CEmailBox类的声明
  函数列表   :
  修改历史   :
  1.日    期   : 2013年10月9日
    作    者   : d00173029
    修改内容   : 创建文件

******************************************************************************/
#ifndef __BST_APP_EMALIBOX_H__
#define __BST_APP_EMALIBOX_H__
/*****************************************************************************
  1 其他头文件包含
*****************************************************************************/
#include "BST_APP_EmailBaseProc.h"
#include "BST_OS_Memory.h"

#if (BST_OS_VER == BST_HISI_VOS)
#pragma pack(4)
#elif(BST_OS_VER == BST_WIN32)
#pragma pack(push, 4)
#endif

/*****************************************************************************
  2 宏定义
*****************************************************************************/
#define BST_EMAIL_CFGFLG_NONE           (0x00)
#define BST_EMAIL_CFGFLG_TYPE           (0x01)
#define BST_EMAIL_CFGFLG_USER           (0x02)
#define BST_EMAIL_CFGFLG_PASSWORD       (0x04)


#define BST_EMAIL_IsInfoConfiged( enFlag )    ( (enFlag) == ( m_EmailCfgFlag & (enFlag) ) )
#define BST_EMAIL_SetEmailConfigFlag(enFlag)        ( m_EmailCfgFlag |= (enFlag) )
/*****************************************************************************
  3 类/结构定义
*****************************************************************************/
class BST_APP_CEmailBox :  BST_PUBLIC BST_CORE_CNPTask
{
BST_PUBLIC:
    BST_APP_CEmailBox(
        BST_PROCID_T usProcID,
        BST_TASKID_T usTaskID );
    virtual ~BST_APP_CEmailBox( BST_VOID );
BST_PRIVATE:
    BST_VOID Entry( BST_VOID );
    BST_ERR_ENUM_UINT8 PidConfiged( 
        BST_CORE_PID_ENUM_UINT16  enParamId,
        BST_UINT16                usLen,
        const BST_VOID           *const pData,
        BST_UINT32                ulBaseCfged,
        BST_UINT8               **pucNewAddr );
    BST_UINT8 *SetStrategyInfo(
        BST_CORE_PID_ENUM_UINT16 enParamId,
        BST_UINT16               usLen,
        const BST_VOID          *const pData );
    BST_UINT8 *ConfigType( 
        const BST_VOID *const pData,
        BST_UINT16      usLen );
    BST_UINT8 *SetProtclType(
        const BST_VOID *const pData,
        BST_UINT16 usLen );

    BST_UINT8 *SetUsername(
        BST_UINT8 *pucUserName,
        BST_UINT16 usLen ) const;
    BST_UINT8 *SetPasswd(
        BST_UINT8 *pucPasswd,
        BST_UINT16 usLen ) const;
    BST_UINT8 *SetCipherkey(
        BST_UINT8 *pucCipherKey,
        BST_UINT16 usLen ) const;
    BST_UINT8 *SetEncryptType(
        const BST_VOID *const pData,
        BST_UINT16 usLen );
    BST_UINT8 *SetSyncType(
        const BST_VOID *const pData,
        BST_UINT16 usLen );
    BST_APP_CEmailBox( const BST_APP_CEmailBox& EmailBox );
    BST_APP_CEmailBox& operator = ( const BST_APP_CEmailBox& EmailBox );
    EMAIL_ACCOUNT_STRU                 *m_pstAccountInfo;
    BST_APP_CEmailPacketProc           *m_PacktStrategy;
    BST_UINT32                          m_EmailCfgFlag;
};
/*****************************************************************************
  4 OTHERS定义
*****************************************************************************/

#if (BST_OS_VER == BST_HISI_VOS)
#pragma pack()
#elif(BST_OS_VER == BST_WIN32)
#pragma pack(pop)
#endif

#endif
