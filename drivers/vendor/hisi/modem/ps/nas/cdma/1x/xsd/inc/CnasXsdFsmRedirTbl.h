



#ifndef __CNAS_XSD_FSM_REDIR_TBL_H__
#define __CNAS_XSD_FSM_REDIR_TBL_H__

/*****************************************************************************
  1 其他头文件包含
*****************************************************************************/
#include  "vos.h"
#include  "NasFsm.h"


#ifdef __cplusplus
#if __cplusplus
extern "C" {
#endif
#endif


#pragma pack(4)


/*****************************************************************************
  2 全局变量声明
*****************************************************************************/
extern NAS_STA_STRU                                         g_astCnasXsdRedirStaTbl[];

/*****************************************************************************
  3 宏定义
*****************************************************************************/
#define CNAS_XSD_GetRedirStaTbl()                          (g_astCnasXsdRedirStaTbl)


/*****************************************************************************
  4 枚举定义
*****************************************************************************/


enum CNAS_XSD_REDIR_STA_ENUM
{
    /* System redirection indication init*/
    CNAS_XSD_REDIR_STA_INIT                   = 0x00,

    /* Waiting for CAS system sync confirmation*/
    CNAS_XSD_REDIR_STA_WAIT_CAS_SYNC_CNF                   = 0x01,

    /* Waiting for CAS system sync stop confirmation */
    CNAS_XSD_REDIR_STA_WAIT_CAS_STOP_SYNC_CNF                   = 0x02,

     /* Waiting for CAS system sync confirmation with original system */
    CNAS_XSD_REDIR_STA_WAIT_CAS_SYNC_CNF_RET_ORIG_SYS                   = 0x03,

    /* Waiting for CAS system sync stop confirmation with original system */
    CNAS_XSD_REDIR_STA_WAIT_CAS_STOP_SYNC_CNF_RET_ORIG_SYS                   = 0x04,

    /* Waiting for CAS OHM indication */
    CNAS_XSD_REDIR_STA_WAIT_CAS_OHM_IND                   = 0x05,

    /* Waiting for CAS OHM indication after camp on with original system */
    CNAS_XSD_REDIR_STA_WAIT_CAS_OHM_RET_ORIG_SYS_IND                   =  0x06
};
typedef VOS_UINT32 CNAS_XSD_REDIR_STA_ENUM_UINT32;


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

extern NAS_FSM_DESC_STRU * CNAS_XSD_GetRedirFsmDescAddr(VOS_VOID);
extern VOS_UINT32 CNAS_XSD_GetRedirStaTblSize(VOS_VOID);


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

#endif /* end of CnasXsdFsmRedirTbl.h */
