

#ifndef _ATTAFAGENTINTERFACE_H_
#define _ATTAFAGENTINTERFACE_H_

/*****************************************************************************
  1 头文件包含
*****************************************************************************/
#include  "vos.h"
#include  "TafAgentInterface.h"

#pragma pack(4)

#ifdef __cplusplus
#if __cplusplus
extern "C" {
#endif
#endif

/*****************************************************************************
  2 全局变量定义
*****************************************************************************/



/*****************************************************************************
  3 函数实现
*****************************************************************************/

/*****************************************************************************
 函 数 名  : TAF_AGENT_FindCidForDial
 功能描述  : 通过同步机制获取用于拨号的CID
 输入参数  : pCid    - CID
 输出参数  : 无
 返 回 值  : VOS_OK  - 成功
             VOS_ERR - 失败
 调用函数  :
 被调函数  :
*****************************************************************************/
VOS_UINT32 TAF_AGENT_FindCidForDial(
    MN_CLIENT_ID_T                      usClientId,
    VOS_UINT8                          *pCid
);


/*****************************************************************************
 函 数 名  : TAF_AGENT_SetPdpCidPara
 功能描述  : 设置指定CID的参数
 输入参数  : usClientId    - 客户端ID
             pstPdpPriPara - PDP上下文参数
 输出参数  : 无
 返 回 值  : VOS_OK        - 成功
             VOS_ERR       - 失败
 调用函数  :
 被调函数  :
*****************************************************************************/
VOS_UINT32 TAF_AGENT_SetPdpCidPara(
    MN_CLIENT_ID_T                      usClientId,
    TAF_PDP_PRIM_CONTEXT_EXT_STRU      *pstPdpPrimContextExt
);


/*****************************************************************************
 函 数 名  : TAF_AGENT_GetPdpCidPara
 功能描述  : 查询指定CID的参数
 输入参数  : pstPdpPriPara - PDP上下文参数
             ucCid         - CID
 返 回 值  : VOS_OK        - 成功
             VOS_ERR       - 失败
 调用函数  :
 被调函数  :
*****************************************************************************/
VOS_UINT32 TAF_AGENT_GetPdpCidPara(
    TAF_PDP_PRIM_CONTEXT_STRU          *pstPdpPriPara,
    MN_CLIENT_ID_T                      usClientId,
    VOS_UINT8                           ucCid
);


/*****************************************************************************
 函 数 名  : TAF_AGENT_GetCallInfo
 功能描述  : 获取通话信息同步API
 输入参数  : usClientId
             pucNumOfCalls
             pstCallInfos
 输出参数  : 无
 返 回 值  : VOS_OK  - 成功
             VOS_ERR - 失败
 调用函数  :
 被调函数  :
*****************************************************************************/
VOS_UINT32 TAF_AGENT_GetCallInfoReq(
    MN_CLIENT_ID_T                      usClientId,
    VOS_UINT8                          *pucCallNum,
    TAFAGERNT_MN_CALL_INFO_STRU        *pstCallInfos
);


/* Added by s00217060 for 主动上报AT命令控制下移至C核, 2013-4-2, begin */
VOS_UINT32 TAF_AGENT_GetSysMode(
    VOS_UINT16                                 usClientId,
    TAF_AGENT_SYS_MODE_STRU                   *pstSysMode
);
/* Added by s00217060 for 主动上报AT命令控制下移至C核, 2013-4-2, end */

extern VOS_VOID TAF_AGENT_ClearAllSem(VOS_VOID);

VOS_UINT32 TAF_AGENT_SetPdpCidQosPara(
    MN_CLIENT_ID_T                      usClientId,
    TAF_PS_PDP_QOS_SET_PARA_STRU       *pstQosPara
);

VOS_UINT32 TAF_AGENT_GetPdpCidQosPara(
    MN_CLIENT_ID_T                      usClientId,
    VOS_UINT8                           ucCid,
    TAF_PS_PDP_QOS_QUERY_PARA_STRU     *pstQosPara
);

VOS_UINT32 TAF_AGENT_GetAntState(
    VOS_UINT16                                 usClientId,
    VOS_UINT16                                *pusAntState
);


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

#endif

