/******************************************************************************


        @(#)Copyright(C)2008,Hisilicon Co. LTD.

 ******************************************************************************
    File name   : NasEsmInclude.h
    Description : SM的C文件要包含的头文件
    History     :
      1.丁丽 00128736    2008-08-20  Draft Enact
      2.杨茜惠 00135146  2008-12-19  BA8D00752
      3.孙兵 49683       2009-01-06  BA8D00870
      4.杨茜惠 00135146  2009-03-06  Modify  BA8D01127

******************************************************************************/

#ifndef __NASESMINCLUDE_H__
#define __NASESMINCLUDE_H__

/*****************************************************************************
  1 Include Headfile
*****************************************************************************/

#include    "vos.h"
#include    "EmmEsmInterface.h"
#include    "EsmRabmInterface.h"
#include    "AppEsmInterface.h"
#include    "PsLogdef.h"
#include    "PsTypeDef.h"
#include    "PsCommonDef.h"
#include    "OmCommon.h"
#include    "msp.h"

#include    "NasEsmPublic.h"
#include    "NasEsmEmmMsgProc.h"
#include    "NasEsmAppMsgParaProc.h"
#include    "NasEsmNwMsgBearerResAllocProc.h"
#include    "NasEsmNwMsgBearerResModProc.h"
#include    "NasEsmNwMsgPdnConProc.h"
#include    "NasEsmNwMsgPdnDisconProc.h"
#include    "NasEsmTimerMsgProc.h"
#include    "NasEsmRabmMsgProc.h"
#include    "NasEsmNwMsgDecode.h"
#include    "NasEsmNwMsgEncode.h"
#include    "NasEsmMain.h"
#include    "NasEsmOmMsgProc.h"
#include    "NasCommPrint.h"
#include    "NasEsmSmMsgProc.h"
#include    "OmEsmInterface.h"
#include    "NasEmmPubUGlobal.h"
#include    "NasLmmPubMNvim.h"
#include    "NasEsmBackOffAlgMain.h"

#include    "NasEsmEhsmMsgProc.h"

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

#endif /* end of NasEsmInclude.h */

