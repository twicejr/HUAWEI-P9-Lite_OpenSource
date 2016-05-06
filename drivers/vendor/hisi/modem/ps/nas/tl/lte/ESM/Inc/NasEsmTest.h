

#ifndef __NASESMTEST_H__
#define __NASESMTEST_H__

/*****************************************************************************
  1 Include Headfile
*****************************************************************************/
#include  "NasEsmInclude.h"

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
#define NAS_ESM_MAX_ITEM_LEN            (80)    /* 数组中字符串最大长度 */

/*****************************************************************************
 枚举名    :NAS_ESM_TIMER_PRINT_LIST_STRU
 枚举说明  :NAS 软调模块定义
*****************************************************************************/
enum NAS_OM_CMD_TYPE_ENUM
{
    NAS_OM_ALL = 0,
    NAS_OM_MM,
    NAS_OM_ESM,
    NAS_OM_RABM
};
typedef VOS_UINT8 NAS_OM_CMD_TYPE_ENUM_UINT8;

/*****************************************************************************
   5 STRUCT
*****************************************************************************/
/*****************************************************************************
 结构名    :NAS_ESM_TIMER_PRINT_LIST_STRU
 结构说明  :ESM模块定时器打印结构
*****************************************************************************/
typedef struct
{
    VOS_UINT32      ulTimerId;
    VOS_UINT8       aucPrintString[NAS_ESM_MAX_ITEM_LEN];
}NAS_ESM_TIMER_PRINT_LIST_STRU;

/*****************************************************************************
  6 UNION
*****************************************************************************/


/*****************************************************************************
  7 Extern Global Variable
*****************************************************************************/

/*****************************************************************************
  8 Fuction Extern
*****************************************************************************/
extern VOS_VOID  NAS_ESM_CmdHelp(  );
extern VOS_VOID  NAS_ESM_ShowAllActiveEpsbInfo( VOS_VOID );
extern VOS_VOID Nas_ESM_ShowAllSdfStaticInfo(  );
extern VOS_VOID NAS_ESM_ShowAllEpsbInfo( VOS_VOID );
extern VOS_VOID Nas_ESM_ShowAllSdfDynamicInfo(  );
extern VOS_VOID NAS_ESM_ShowSdfStaticInfo( VOS_UINT32 ulCid );
extern VOS_VOID  NAS_ESM_ShowCommonInfo( );
extern VOS_VOID NAS_ESM_ShowEpsbInfo(VOS_UINT32 ulEpsbId);
extern VOS_VOID  NAS_ESM_ShowSdfDynamicInfo( VOS_UINT32 ulCid );
extern VOS_VOID NAS_ESM_ShowStateTblInfo(  );
extern VOS_VOID nasver (VOS_VOID);
extern VOS_VOID NAS_ESM_DebugInit(VOS_VOID);

/*****************************************************************************
  9 OTHERS
*****************************************************************************/



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

#endif /* end of NasPubmHelp.h */
