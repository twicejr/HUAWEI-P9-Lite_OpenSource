/******************************************************************************

                  版权所有 (C), 2001-2011, 华为技术有限公司

 ******************************************************************************
  文 件 名   : NasUtranCtrlInterface.h
  版 本 号   : 初稿
  作    者   : w00167002
  生成日期   : 2012年7月12日
  最近修改   :
  功能描述   : 供NAS各个子模块:MM子层、TAF层、CM层查询的接口文件
  函数列表   :
  修改历史   :
  1.日    期   : 2012年7月12日
    作    者   : w00167002
    修改内容   : 创建文件

******************************************************************************/
#ifndef _NAS_UTRANCTRL_INTERFACE_H_
#define _NAS_UTRANCTRL_INTERFACE_H_

/*****************************************************************************
  1 其他头文件包含
*****************************************************************************/
#include  "PsTypeDef.h"
#include  "TTFMem.h"

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
 枚举名    : NAS_UTRANCTRL_UTRAN_MODE_ENUM_UINT8
 结构说明  : MS当前具体的UTRAN模式:WCDMA/TD-SCAMA
 1.日    期   : 2012年7月27日
   作    者   : w00167002
   修改内容   : 新建
*****************************************************************************/
enum NAS_UTRANCTRL_UTRAN_MODE_ENUM
{
    NAS_UTRANCTRL_UTRAN_MODE_FDD,                                               /* UTRAN模式为WCDMA */
    NAS_UTRANCTRL_UTRAN_MODE_TDD,                                               /* UTRAN模式为TDSCDMA */
    NAS_UTRANCTRL_UTRAN_MODE_NULL,                                              /* UTRAN模式为NULL */
    NAS_UTRANCTRL_UTRAN_MODE_BUTT
};
typedef VOS_UINT8 NAS_UTRANCTRL_UTRAN_MODE_ENUM_UINT8;

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
  8 UNION定义
*****************************************************************************/


/*****************************************************************************
  9 OTHERS定义
*****************************************************************************/


/*****************************************************************************
  10 函数声明
*****************************************************************************/
NAS_UTRANCTRL_UTRAN_MODE_ENUM_UINT8 NAS_UTRANCTRL_GetCurrUtranMode(VOS_VOID);

VOS_RATMODE_ENUM_UINT32 NAS_UTRANCTRL_GetRatModeBasedOnUtranMode(
    NAS_UTRANCTRL_UTRAN_MODE_ENUM_UINT8 enUtranMode
);


VOS_UINT8 NAS_UTRANCTRL_GetUtranTddCsSmcNeededFlg(VOS_VOID);
VOS_UINT8 NAS_UTRANCTRL_GetUtranTddPsSmcNeededFlg(VOS_VOID);
VOS_UINT8 NAS_UTRANCTRL_IsUtranCsSmcNeeded(VOS_VOID);
VOS_UINT8 NAS_UTRANCTRL_IsUtranPsSmcNeeded(VOS_VOID);

VOS_UINT32 NAS_UTRANCTRL_SndAsMsg(
    VOS_UINT32                          ulSndPid,
    struct MsgCB                       **ppstMsg
);

VOS_VOID NAS_UTRANCTRL_RABM_AdaptPdcpDataReq(
    VOS_UINT8                           ucRbId,
    TTF_MEM_ST                         *pstData,
    VOS_UINT32                          ulDataBitLen
);

VOS_VOID NAS_UTRANCTRL_RABM_GetRbSuitableUlPduSize(
    VOS_UINT8                          ucRbId,
    VOS_UINT32                         ulPduSize,
    VOS_UINT8                          ucCrcSize,
    VOS_UINT32                        *pulUlPduSize
);

VOS_UINT32 NAS_UTRANCTRL_RABM_SendTcDataNotify(VOS_VOID);

VOS_VOID NAS_UTRANCTRL_RABM_SetFinIpInRdFlag(VOS_UINT32 ulFlag);

VOS_VOID NAS_UTRANCTRL_ProcBufferMsg(VOS_VOID);

VOS_UINT32 NAS_UTRANCTRL_MsgProc(
    struct MsgCB                       *pstSrcMsg,
    struct MsgCB                      **ppstDestMsg
);

VOS_VOID  NAS_UTRANCTRL_InitCtx(
    VOS_UINT8                           ucInitType
);

VOS_VOID  NAS_UTRANCTRL_SetSearchedSpecTdMccFlg(
    VOS_UINT8       ucFlg
);

VOS_VOID NAS_UTRANCTRL_SndOutsideContextData( VOS_VOID );

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

#endif /* end of NasNAS_UTRANCTRLCtx.h */
