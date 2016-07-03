
#ifndef  MN_CALL_BC_PROC_H
#define  MN_CALL_BC_PROC_H

/*****************************************************************************
  1 头文件包含
*****************************************************************************/
#include "MnCallApi.h"
#include "NasCcIe.h"
#include "MnCallFacilityDecode.h"
#include "product_config.h"


#ifdef __cplusplus
#if __cplusplus
extern "C" {
#endif
#endif

#pragma pack(4)

/*****************************************************************************
  2 常量定义
*****************************************************************************/


/*****************************************************************************
  3类型定义
*****************************************************************************/
typedef struct
{
    VOS_BOOL                            bUsed;
    VOS_UINT8                           ucCallId;
    VOS_UINT8                           ucInvokeId;
    VOS_UINT8                           ucOperateCode;
    VOS_UINT8                           aucReserved[1];
}MN_CALL_SS_ID_TABLE_STRU;



/*****************************************************************************
  4 宏定义
*****************************************************************************/
#define MN_CALL_INVALID_TI              0xff


/*****************************************************************************
  5 全局变量声明
*****************************************************************************/
extern MN_CALL_SS_ID_TABLE_STRU g_stCallInvokeIdTable[MN_CALL_MAX_INVOKE_NUM];


/*****************************************************************************
  6 接口函数声明
*****************************************************************************/

VOS_UINT32 MN_CALL_FacilityEncode(
    VOS_UINT8                           *pucDest,
    const MN_CALL_SS_COMPONENT_UNION    *punComponent
);


VOS_VOID MN_CALL_SimpleFacilityEncode(
    VOS_UINT8                           *pucDest,
    const MN_CALL_SS_COMPONENT_UNION    *punComponent
);

/*****************************************************************************
 Prototype      : MN_CALL_InvokeId_Free()
 Description    : 分配InvokeId
 Input          : ucInvokeId: 要释放的ucInvokeId
 Output         :
 Return Value   : SPEECH_SUCCESS  释放成功
                : SPEECH_ERROR    释放失败
 Calls          :
 Called By      :

 History        :
  1.Date        : 2005-08-19
    Author      : cjh
    Modification: Created function
*****************************************************************************/
VOS_VOID MN_CALL_InvokeId_Free(
    VOS_UINT8                           ucInvokeId
);


#if ((VOS_OS_VER == VOS_WIN32) || (VOS_OS_VER == VOS_NUCLEUS))
#pragma pack()
#else
#pragma pack(0)
#endif

#ifdef __cplusplus
#if __cplusplus
}
#endif
#endif

#endif /* MN_CALL_BC_PROC_H */

