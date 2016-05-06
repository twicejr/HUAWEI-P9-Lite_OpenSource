/******************************************************************************

                  版权所有 (C), 2001-2012, 华为技术有限公司

 ******************************************************************************
  文 件 名   : ScCtx.c
  版 本 号   : 初稿
  作    者   : w00184875
  生成日期   : 2012年04月19日
  最近修改   :
  功能描述   : SC CONTEXT文件
  函数列表   :
  修改历史   :
  1.日    期   : 2012年04月19日
    作    者   : w00184875
    修改内容   : 创建文件

******************************************************************************/

/*****************************************************************************
  1 头文件包含
*****************************************************************************/
#include "ScCommCtx.h"
#include "ScCtx.h"
#include "ScApSec.h"

#ifdef __cplusplus
#if __cplusplus
extern "C" {
#endif
#endif

#define THIS_FILE_ID PS_FILE_ID_SC_CONTEXT_C

/*****************************************************************************
  2 全局变量定义
*****************************************************************************/

/*****************************************************************************
 函 数 名  : SC_CTX_GetFacGlobalVarAddr
 功能描述  : 获取SC产线操作的全局变量地址
 输入参数  : 无
 输出参数  : 无
 返 回 值  : SC产线操作的全局变量上下文指针
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2012年04月19日
    作    者   : w00184875
    修改内容   : 新生成函数
*****************************************************************************/
SC_FAC_GLOBAL_STRU*  SC_CTX_GetFacGlobalVarAddr( VOS_VOID )
{
    return &SC_CTX_GetScCtxAddr()->stScFacGlobalVar;
}

/*****************************************************************************
 函 数 名  : SC_CTX_InitFacGlobalVar
 功能描述  : 初始化SC产线操作的全局变量
 输入参数  : 无
 输出参数  : 无
 返 回 值  : 无
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2012年04月19日
    作    者   : w00184875
    修改内容   : 新生成函数
*****************************************************************************/
VOS_VOID  SC_CTX_InitFacGlobalVar( VOS_VOID )
{
    SC_CTX_GetScCtxAddr()->stScFacGlobalVar.enScFacAuthStatus = SC_AUTH_STATUS_UNDO;

    /*lint -e534*/
    VOS_MemSet(SC_CTX_GetScCtxAddr()->stScFacGlobalVar.aucScFacRandData, 0, SC_RAND_DATA_LEN);
    /*lint +e534*/

    return;
}

/*****************************************************************************
 函 数 名  : SC_CTX_GetFacAuthStatus
 功能描述  : 获取SC产线鉴权状态
 输入参数  : 无
 输出参数  : 无
 返 回 值  : SC_AUTH_STATUS_ENUM_UINT8
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2012年04月19日
    作    者   : w00184875
    修改内容   : 新生成函数
*****************************************************************************/
SC_AUTH_STATUS_ENUM_UINT8  SC_CTX_GetFacAuthStatus( VOS_VOID )
{
    return SC_CTX_GetScCtxAddr()->stScFacGlobalVar.enScFacAuthStatus;
}

/*****************************************************************************
 函 数 名  : SC_CTX_GetFacAuthStatus
 功能描述  : 设置SC产线鉴权状态
 输入参数  : 无
 输出参数  : 无
 返 回 值  : 无
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2012年04月19日
    作    者   : w00184875
    修改内容   : 新生成函数
*****************************************************************************/
VOS_VOID  SC_CTX_SetFacAuthStatus( SC_AUTH_STATUS_ENUM_UINT8 enScAuthStatus )
{
    SC_CTX_GetScCtxAddr()->stScFacGlobalVar.enScFacAuthStatus = enScAuthStatus;

    return;
}

/*****************************************************************************
 函 数 名  : SC_CTX_GetIdentifyStartFlg
 功能描述  : 获取发起产线鉴权流程标志
 输入参数  : 无
 输出参数  : 无
 返 回 值  : VOS_UINT8
                VOS_TRUE:   已发起产线鉴权
                VOS_FALSE:  未发起产线鉴权
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2012年04月19日
    作    者   : w00184875
    修改内容   : 新生成函数
*****************************************************************************/
VOS_UINT8  SC_CTX_GetIdentifyStartFlg( VOS_VOID )
{
    return SC_CTX_GetScCtxAddr()->stScFacGlobalVar.ucIdentifyStartFlg;
}

/*****************************************************************************
 函 数 名  : SC_CTX_SetIdentifyStartFlg
 功能描述  : 设置发起产线鉴权流程标志
 输入参数  : VOS_UINT8 ucIdentifyStartFlg
 输出参数  : 无
 返 回 值  : 无
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2012年04月19日
    作    者   : w00184875
    修改内容   : 新生成函数
*****************************************************************************/
VOS_VOID  SC_CTX_SetIdentifyStartFlg( VOS_UINT8 ucIdentifyStartFlg )
{
    SC_CTX_GetScCtxAddr()->stScFacGlobalVar.ucIdentifyStartFlg   = ucIdentifyStartFlg;

    return;
}

/*****************************************************************************
 函 数 名  : SC_CTX_GetFacRandDataAddr
 功能描述  : 获取SC产线鉴权时随机数的地址
 输入参数  : 无
 输出参数  : 无
 返 回 值  : SC产线产线鉴权时随机数的地址
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2012年04月19日
    作    者   : w00184875
    修改内容   : 新生成函数
*****************************************************************************/
VOS_UINT8*  SC_CTX_GetFacRandDataAddr( VOS_VOID )
{
    return SC_CTX_GetScCtxAddr()->stScFacGlobalVar.aucScFacRandData;
}

/*****************************************************************************
 函 数 名  : SC_CTX_GetApSecInitStateAddr
 功能描述  : 获取AP Security双备份文件初始化状态地址
 输入参数  : 无
 输出参数  : 无
 返 回 值  : 返回双备份文件初始化状态地址
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2012年08月30日
    作    者   : h59254
    修改内容   : 新生成函数
*****************************************************************************/
VOS_UINT32*  SC_CTX_GetApSecInitStateAddr(VOS_VOID)
{
    return &SC_CTX_GetScCtxAddr()->stScApSecGlobalVar.ulInitState;
}

/*****************************************************************************
 函 数 名  : SC_CTX_GetApSecItemBaseAddr
 功能描述  : 获取AP Security双备份文件内容在内存中的起始地址
 输入参数  : 无
 输出参数  : 无
 返 回 值  : 返回AP Security双备份文件内容在内存中的起始地址
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2012年08月30日
    作    者   : h59254
    修改内容   : 新生成函数
*****************************************************************************/
SC_APSEC_ITEM_STRU*  SC_CTX_GetApSecItemBaseAddr(VOS_VOID)
{
    return SC_CTX_GetScCtxAddr()->stScApSecGlobalVar.astApSecItem;
}

/*****************************************************************************
 函 数 名  : SC_CTX_GetSecATkeyFlg
 功能描述  : 返回安全AT key的标志位
 输入参数  : VOS_VOID
 输出参数  : 无
 返 回 值  : VOS_UINT8
                VOS_TRUE    : 当前已经设置安全AT key
                VOS_FALSE   : 当前未设置安全AT key
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2012年9月2日
    作    者   : 李紫剑/00198894
    修改内容   : 新生成函数

*****************************************************************************/
VOS_UINT8 SC_CTX_GetSecATkeyFlg(VOS_VOID)
{
    return SC_CTX_GetScCtxAddr()->stScApSecGlobalVar.ucSecATkeyFlg;
}

/*****************************************************************************
 函 数 名  : SC_CTX_SetSecATkeyFlg
 功能描述  : 设置安全AT key的标志位
 输入参数  : VOS_UINT8 ucSecATkeyFlg   - 安全AT key的标志位
                VOS_TRUE    : 已经设置安全AT key
                VOS_FALSE   : 未设置安全AT key
 输出参数  : 无
 返 回 值  : VOS_VOID
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2012年9月2日
    作    者   : 李紫剑/00198894
    修改内容   : 新生成函数

*****************************************************************************/
VOS_VOID SC_CTX_SetSecATkeyFlg(VOS_UINT8 ucSecATkeyFlg)
{
    SC_CTX_GetScCtxAddr()->stScApSecGlobalVar.ucSecATkeyFlg  = ucSecATkeyFlg;
    return;
}

/*****************************************************************************
 函 数 名  : SC_CTX_GetSecATkeyAddr
 功能描述  : 返回安全AT key的首地址
 输入参数  : VOS_VOID
 输出参数  : 无
 返 回 值  : VOS_UINT8* -- 安全AT key的首地址
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2012年9月2日
    作    者   : 李紫剑/00198894
    修改内容   : 新生成函数

*****************************************************************************/
VOS_UINT8* SC_CTX_GetSecATkeyAddr(VOS_VOID)
{
    return SC_CTX_GetScCtxAddr()->stScApSecGlobalVar.aucSecATkey;
}

/*****************************************************************************
 函 数 名  : SC_CTX_GetApSecSeqID
 功能描述  : 返回SeqID
 输入参数  : VOS_VOID
 输出参数  : 无
 返 回 值  : VOS_UINT8  -- SeqID
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2012年9月2日
    作    者   : 李紫剑/00198894
    修改内容   : 新生成函数

*****************************************************************************/
VOS_UINT8 SC_CTX_GetApSecSeqID(VOS_VOID)
{
    return SC_CTX_GetScCtxAddr()->stScApSecGlobalVar.ucSeqID;
}

/*****************************************************************************
 函 数 名  : SC_CTX_SetApSecSeqID
 功能描述  : 设置SeqID
 输入参数  : VOS_UINT8 ucSeqID   - SeqID
 输出参数  : 无
 返 回 值  : VOS_VOID
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2012年9月2日
    作    者   : 李紫剑/00198894
    修改内容   : 新生成函数

*****************************************************************************/
VOS_VOID SC_CTX_SetApSecSeqID(VOS_UINT8 ucSeqID)
{
    SC_CTX_GetScCtxAddr()->stScApSecGlobalVar.ucSeqID  = ucSeqID;
    return;
}


#ifdef __cplusplus
    #if __cplusplus
        }
    #endif
#endif

