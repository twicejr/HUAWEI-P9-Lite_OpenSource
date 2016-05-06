
/******************************************************************************

                  版权所有 (C), 2001-2011, 华为技术有限公司

 ******************************************************************************
  文 件 名   : NasMmcCtx.c
  版 本 号   : 初稿
  作    者   : zhoujun /40661
  生成日期   : 2011年04月22日
  最近修改   :
  功能描述   : NAS MMC CTX文件
  函数列表   :

  修改历史   :
  1.日    期   : 2010年11月13日
    作    者   : zhoujun /40661
    修改内容   : 创建文件

******************************************************************************/

/*****************************************************************************
  1 头文件包含
*****************************************************************************/
#include "PsLib.h"

#include "PsCommonDef.h"
#include "NasCommDef.h"
#include "NasMmcSndOm.h"
#include "NasMmcFsmMainTbl.h"
#include "NasMmcCtx.h"
#include "NasMmcMain.h"
#include "NasMmcFsmPlmnSelectionTbl.h"
#include "NasMmcFsmInterSysCellReselTbl.h"
#include "NasMmcFsmInterSysHoTbl.h"
#include "NasMmcFsmInterSysCcoTbl.h"
#include "NasMmcFsmInterSysOosTbl.h"
#include "NasMmcFsmSwitchOnTbl.h"
#include "NasMmcFsmPoweroffTbl.h"
#include "NasMmcFsmPLmnListTbl.h"
#include "NasMmcFsmBgPlmnSearchTbl.h"
#include "NasMmcFsmGetGeoTbl.h"
#include "NasMmcTimerMgmt.h"
#include "NasMmcFsmSyscfgTbl.h"
#include "NasMmcFsmAnyCellSearchTbl.h"
#include "NasMmcSndMscc.h"
#include "NasMmcSndLmm.h"
#include "NasMmcProcNvim.h"
#include "NasMmcComFunc.h"
#include "NasMmcFsmPowerOff.h"

/* Added by l00167671 for 主动上报AT命令控制下移至C核, 2013-3-30, begin */
#include "MsccMmcInterface.h"
/* Added by l00167671 for 主动上报AT命令控制下移至C核, 2013-3-30, end */

#include "NasMmcFsmPlmnSelection.h"

#include "NasUsimmApi.h"

#ifdef __cplusplus
#if __cplusplus
extern "C" {
#endif
#endif


/*****************************************************************************
    协议栈打印打点方式下的.C文件宏定义
*****************************************************************************/
/*lint -e(767)*/
#define    THIS_FILE_ID        PS_FILE_ID_NAS_MMC_CTX_C


/*****************************************************************************
  2 全局变量定义
*****************************************************************************/

/* MMC CTX,用于保存MMC状态机,描述表 */
NAS_MMC_CONTEXT_STRU                    g_stNasMmcCtx;

/*lint -save -e958 */

/*****************************************************************************
 全局变量名    : g_aulFsmEntryEventType
 全局变量说明  : 状态机的入口消息
 1.日    期   : 2011年9月28日
   作    者   : zhoujun 40661
   修改内容   : 新建
 2.日    期   : 2014年2月24日
   作    者   : w00176964
   修改内容   : High_Rat_Hplmn_Search特性调整
 3.日    期   : 2015年9月6日
   作    者   : z00161729
   修改内容   : 支持LTE CSG功能新增
*****************************************************************************/

VOS_UINT32 g_aulFsmEntryEventType[] =
{
    NAS_BuildEventType(WUEPS_PID_WRR, RRMM_SUSPEND_IND),

    NAS_BuildEventType(UEPS_PID_GAS, RRMM_SUSPEND_IND),

    /* Modified by l00167671 for 主动上报AT命令控制下移至C核, 2013-3-30, begin */
    NAS_BuildEventType(UEPS_PID_MSCC, ID_MSCC_MMC_POWER_OFF_REQ),

    NAS_BuildEventType(UEPS_PID_MSCC, ID_MSCC_MMC_SYS_CFG_SET_REQ),

    NAS_BuildEventType(UEPS_PID_MSCC, ID_MSCC_MMC_PLMN_LIST_REQ),
    /* Modified by l00167671 for 主动上报AT命令控制下移至C核, 2013-3-30, end */

#if (FEATURE_ON == FEATURE_CSG)
    NAS_BuildEventType(UEPS_PID_MSCC, ID_MSCC_MMC_CSG_LIST_SEARCH_REQ),
    NAS_BuildEventType(UEPS_PID_MSCC, TI_NAS_MMC_PERIOD_TRYING_USER_CSG_LIST_SEARCH),
#endif
    NAS_BuildEventType(WUEPS_PID_MMC, MMCMMC_INTER_PLMN_LIST_REQ),

    NAS_BuildEventType(VOS_PID_TIMER, TI_NAS_MMC_PERIOD_TRYING_INTER_PLMN_LIST),

    NAS_BuildEventType(VOS_PID_TIMER, TI_NAS_MMC_PERIOD_TRYING_USER_PLMN_LIST),

    /* Modified by l00167671 for 主动上报AT命令控制下移至C核, 2013-3-30, begin */
    NAS_BuildEventType(UEPS_PID_MSCC, ID_MSCC_MMC_PLMN_SPECIAL_REQ),

    NAS_BuildEventType(UEPS_PID_MSCC, ID_MSCC_MMC_PLMN_SEARCH_REQ),
    /* Modified by l00167671 for 主动上报AT命令控制下移至C核, 2013-3-30, end */

    NAS_BuildEventType(WUEPS_PID_MMC, MMCMMC_INTER_ANYCELL_SEARCH_REQ),

    NAS_BuildEventType(WUEPS_PID_MMC, MMCMMC_INTER_PLMN_SEARCH_REQ),

    NAS_BuildEventType(VOS_PID_TIMER, TI_NAS_MMC_HPLMN_TIMER),

    NAS_BuildEventType(VOS_PID_TIMER, TI_NAS_MMC_PERIOD_TRYING_HIGH_PRIO_PLMN_SEARCH),

    NAS_BuildEventType(VOS_PID_TIMER, TI_NAS_MMC_HIGH_PRIO_RAT_HPLMN_TIMER),

    NAS_BuildEventType(UEPS_PID_MSCC, ID_MSCC_MMC_GET_GEO_REQ),

#if   (FEATURE_ON == FEATURE_LTE)
    NAS_BuildEventType(PS_PID_MM, ID_LMM_MMC_SUSPEND_IND)
#endif
};


/*****************************************************************************
 函 数 名  : NAS_MMC_GetMmcCtxAddr
 功能描述  : 获取当前MMC的CTX
 输入参数  : 无
 输出参数  : 无
 返 回 值  : 返回当前MMC的CTX地址
 调用函数  :
 被调函数  :

 修改历史      :
 1.日    期   : 2011年7月29日
   作    者   : w00167002
   修改内容   : 新生成函数

*****************************************************************************/
NAS_MMC_CONTEXT_STRU* NAS_MMC_GetMmcCtxAddr(VOS_VOID)
{
    return &(g_stNasMmcCtx);
}

/*****************************************************************************
 函 数 名  : NAS_MMC_GetRegCtrlAddr
 功能描述  : 获取当前状态机地址
 输入参数  : 无
 输出参数  : 无
 返 回 值  : 当前状态机地址
 调用函数  :
 被调函数  :

 修改历史      :
 1.日    期   : 2011年7月29日
   作    者   : w00167002
   修改内容   : 新生成函数

*****************************************************************************/
NAS_MMC_FSM_CTX_STRU* NAS_MMC_GetCurFsmAddr(VOS_VOID)
{
    return &(g_stNasMmcCtx.stCurFsm);
}

/*****************************************************************************
 函 数 名  : NAS_MMC_GetFsmStackAddr
 功能描述  : 获取当前状态机栈地址
 输入参数  : 无
 输出参数  : 无
 返 回 值  : 当前状态机栈地址
 调用函数  :
 被调函数  :

 修改历史      :
 1.日    期   : 2011年7月29日
   作    者   : w00167002
   修改内容   : 新生成函数

*****************************************************************************/
NAS_MMC_FSM_STACK_STRU* NAS_MMC_GetFsmStackAddr(VOS_VOID)
{
    return &(g_stNasMmcCtx.stFsmStack);
}

/*****************************************************************************
 函 数 名  : NAS_MMC_GetCurFsmDesc
 功能描述  : 获取当前状态机表的地址
 输入参数  : 无
 输出参数  : 无
 返 回 值  : 当前状态机表的地址
 调用函数  :
 被调函数  :

 修改历史      :
 1.日    期   : 2011年7月29日
   作    者   : w00167002
   修改内容   : 新生成函数

*****************************************************************************/
NAS_FSM_DESC_STRU* NAS_MMC_GetCurFsmDesc(VOS_VOID)
{
    return (g_stNasMmcCtx.stCurFsm.pstFsmDesc);
}

/*****************************************************************************
 函 数 名  : NAS_MMC_GetCurrFsmMsgAddr
 功能描述  : 获取当前状态机入口消息的地址
 输入参数  : 无
 输出参数  : 无
 返 回 值  : 当前状态机入口消息的地址
 调用函数  :
 被调函数  :

 修改历史      :
 1.日    期   : 2011年7月29日
   作    者   : w00167002
   修改内容   : 新生成函数

*****************************************************************************/
NAS_MMC_ENTRY_MSG_STRU* NAS_MMC_GetCurrFsmMsgAddr(VOS_VOID)
{
    return &(g_stNasMmcCtx.stCurFsm.stEntryMsg);
}

/*****************************************************************************
 函 数 名  : NAS_MMC_GetCurrFsmMsgAddr
 功能描述  : 获取当前状态机的ID
 输入参数  : 无
 输出参数  : 无
 返 回 值  : 当前状态机的ID
 调用函数  :
 被调函数  :

 修改历史      :
 1.日    期   : 2011年7月29日
   作    者   : w00167002
   修改内容   : 新生成函数

*****************************************************************************/
NAS_MMC_FSM_ID_ENUM_UINT32 NAS_MMC_GetCurrFsmId(VOS_VOID)
{
    return (g_stNasMmcCtx.stCurFsm.enFsmId);
}

/*****************************************************************************
 函 数 名  : NAS_MMC_GetCurrFsmEventType
 功能描述  : 获取当前状态机的消息类型
 输入参数  : 无
 输出参数  : 无
 返 回 值  : 当前状态机的消息类型
 调用函数  :
 被调函数  :

 修改历史      :
 1.日    期   : 2011年9月29日
   作    者   : h44270
   修改内容   : 新生成函数

*****************************************************************************/
VOS_UINT32 NAS_MMC_GetCurrFsmEventType(VOS_VOID)
{
    return (g_stNasMmcCtx.stCurFsm.stEntryMsg.ulEventType);
}

/*****************************************************************************
 函 数 名  : NAS_MMC_GetParentFsmId
 功能描述  : 获取上层状态机的ID
 输入参数  : 无
 输出参数  : 无
 返 回 值  : 上层状态机的ID
 调用函数  :
 被调函数  :

 修改历史      :
 1.日    期   : 2011年9月29日
   作    者   : h44270
   修改内容   : 新生成函数

*****************************************************************************/
NAS_MMC_FSM_ID_ENUM_UINT32 NAS_MMC_GetParentFsmId(VOS_VOID)
{
    return (g_stNasMmcCtx.stCurFsm.enParentFsmId);
}

/*****************************************************************************
 函 数 名  : NAS_MMC_GetParentFsmEventType
 功能描述  : 获取上层状态机的消息类型
 输入参数  : 无
 输出参数  : 无
 返 回 值  : 上层状态机的消息类型
 调用函数  :
 被调函数  :

 修改历史      :
 1.日    期   : 2011年9月29日
   作    者   : h44270
   修改内容   : 新生成函数

*****************************************************************************/
VOS_UINT32 NAS_MMC_GetParentFsmEventType(VOS_VOID)
{
    return (g_stNasMmcCtx.stCurFsm.ulParentEventType);
}

/*****************************************************************************
 函 数 名  : NAS_MMC_GetParentFsmCtx
 功能描述  : 获取上层状态机的上下文内容
 输入参数  : 无
 输出参数  : 无
 返 回 值  : 上层状态机的消息类型
 调用函数  :
 被调函数  :

 修改历史      :
 1.日    期   : 2013年9月16日
   作    者   : w00167002
   修改内容   : 新生成函数

*****************************************************************************/
NAS_MMC_FSM_EXTRA_CTX_UNION* NAS_MMC_GetParentFsmCtx(VOS_VOID)
{
    return (g_stNasMmcCtx.stCurFsm.punParentFsmCtx);
}


/*****************************************************************************
 函 数 名  : NAS_MMC_GetCachMsgBufferAddr
 功能描述  : 获取当前的缓存消息地址
 输入参数  : 无
 输出参数  : 无
 返 回 值  : NAS MMC缓存消息队列
 调用函数  :
 被调函数  :

 修改历史      :
 1.日    期   : 2011年7月29日
   作    者   : w00167002
   修改内容   : 新生成函数

*****************************************************************************/
NAS_MMC_MSG_QUEUE_STRU* NAS_MMC_GetCachMsgBufferAddr(VOS_VOID)
{
    return &(g_stNasMmcCtx.stBufferEntryMsgQueue);
}

/*****************************************************************************
 函 数 名  : NAS_MMC_FSM_PushFsm
 功能描述  : 对状态机进行压栈
 输入参数  : *pstFsmStack:状态机栈
             *pstNewFsm:需要压入的状态机
 输出参数  : 无
 返 回 值  : VOS_VOID
 调用函数  :
 被调函数  :

 修改历史      :
 1.日    期   : 2011年4月1日
   作    者   : zhoujun /40661
   修改内容   : 新生成函数

 2.日    期   : 2011年10月10日
   作    者   : zhoujun /40661
   修改内容   :  修改栈深度的类型

*****************************************************************************/
VOS_VOID NAS_MMC_FSM_PushFsm(
    NAS_MMC_FSM_STACK_STRU              *pstFsmStack,
    NAS_MMC_FSM_CTX_STRU                *pstNewFsm
)
{
    NAS_MMC_FSM_CTX_STRU                *pstCurFsm;

    if ( (VOS_NULL_PTR == pstFsmStack)
      || (VOS_NULL_PTR == pstNewFsm) )
    {
        NAS_ERROR_LOG(WUEPS_PID_MMC,
                       "NAS_MMC_FSM_PushFsm,Para null ptr,pstFsmStack,pstNewFsm");

        return;
    }

    if ( pstFsmStack->usStackDepth >= NAS_MMC_MAX_STACK_DEPTH )
    {
        NAS_ERROR_LOG1(WUEPS_PID_MMC,
                       "NAS_MMC_FSM_PushFsm,Fsm Stack Depth Error!",
                       pstFsmStack->usStackDepth);

        return;
    }

    pstCurFsm               = &((pstFsmStack->astFsmStack)[pstFsmStack->usStackDepth]);

    /* 将当前状态机所有CTX都需要保存起来 */
    PS_MEM_CPY(pstCurFsm, pstNewFsm, sizeof(NAS_MMC_FSM_CTX_STRU));

    pstFsmStack->usStackDepth++;


    return;
}

/*****************************************************************************
 函 数 名  : NAS_MMC_FSM_PopFsm
 功能描述  : 对状态机进行出栈
 输入参数  : 无
             无
 输出参数  : 无
 返 回 值  : VOS_VOID
 调用函数  :
 被调函数  :

 修改历史      :
 1.日    期   : 2011年4月1日
   作    者   : zhoujun /40661
   修改内容   : 新生成函数

 2.日    期   : 2011年10月10日
   作    者   : zhoujun /40661
   修改内容   :  修改栈深度的类型

*****************************************************************************/
VOS_VOID NAS_MMC_FSM_PopFsm( VOS_VOID )
{
    VOS_UINT16                          usPopFsmPos;
    NAS_MMC_FSM_STACK_STRU             *pstFsmStack = VOS_NULL_PTR;
    NAS_MMC_FSM_CTX_STRU               *pstCurFsm   = VOS_NULL_PTR;

    /* 根据并行状态机栈弹出的状态机获取当前状态机描述地址  */
    pstFsmStack                     = NAS_MMC_GetFsmStackAddr();
    pstCurFsm                       = NAS_MMC_GetCurFsmAddr();

    /* 栈已空 */
    if ( 0 == (pstFsmStack->usStackDepth) )
    {
        NAS_ERROR_LOG(WUEPS_PID_MMC, "NAS_MMC_FSM_PopFsm,FSM Stack empty");

        return;
    }

    pstFsmStack->usStackDepth--;
    usPopFsmPos   = pstFsmStack->usStackDepth;

    /* 设置当前状态机 */
    PS_MEM_CPY(pstCurFsm,
              &((pstFsmStack->astFsmStack)[usPopFsmPos]),
              sizeof(NAS_MMC_FSM_CTX_STRU));

    return;
}

/*****************************************************************************
 函 数 名  : NAS_MMC_GetL1MainFsm
 功能描述  : 在状态机栈中获取底层状态机的地址
 输入参数  : VOS_VOID
 输出参数  : 无
 返 回 值  : VOS_VOID
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2015年12月1日
    作    者   : n00355355
    修改内容   : 新生成函数

*****************************************************************************/
NAS_MMC_FSM_CTX_STRU* NAS_MMC_GetBottomFsmInFsmStack(VOS_VOID)
{
    NAS_MMC_FSM_STACK_STRU             *pstFsmStack     = VOS_NULL_PTR;

    /* 获取状态机栈的地址 */
    pstFsmStack                     = NAS_MMC_GetFsmStackAddr();

    /* 空栈直接退出 */
    if (0 == pstFsmStack->usStackDepth)
    {
        NAS_ERROR_LOG(WUEPS_PID_MMC, "NAS_MMC_GetBottomFsmInFsmStack:FsmStack is empty.");
        return VOS_NULL_PTR;
    }

    return &(pstFsmStack->astFsmStack[0]);
}

/*****************************************************************************
 函 数 名  : NAS_MMC_SaveCurEntryMsg
 功能描述  : 保存当前状态机的入口消息
 输入参数  : ulEventType            :入口消息类型
              pstMsg             :入口消息内容
 输出参数  : 无
 返 回 值  : VOS_VOID
 调用函数  :
 被调函数  :
 修改历史      :
  1.日    期   : 2011-04-19
    作    者   : z40661
    修改内容   : 新生成函数
*****************************************************************************/
VOS_VOID NAS_MMC_SaveCurEntryMsg(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg
)
{
    NAS_MMC_ENTRY_MSG_STRU             *pstEntryMsg  = VOS_NULL_PTR;
    MSG_HEADER_STRU                    *pstMsgHeader = VOS_NULL_PTR;
    VOS_UINT32                          ulLen;

    /* 获得当前处理NAS_MMC入口消息的缓冲区地址 */
    pstEntryMsg                 =   NAS_MMC_GetCurrFsmMsgAddr();
    pstMsgHeader                = (MSG_HEADER_STRU*)pstMsg;

    /* 如果是空消息 */
    if ( VOS_NULL_PTR == pstMsg )
    {
        pstEntryMsg->ulEventType    =   ulEventType;
        NAS_WARNING_LOG( WUEPS_PID_MMC, "NAS_MMC_SaveCurEntryMsg Entry Message Pointer is NULL!" );
        return;
    }

    ulLen                       = pstMsgHeader->ulLength + VOS_MSG_HEAD_LENGTH;

    /* 将当前处理的入口消息拷贝到Context对应的缓冲区 */
    PS_MEM_CPY( pstEntryMsg->aucEntryMsgBuffer, pstMsg, ulLen );

    /* 填写Context中的参数 */
    pstEntryMsg->ulEventType    =   ulEventType;

    return;

}

/*****************************************************************************
 函 数 名  : NAS_MMC_LoadSubFsmInfo
 功能描述  : 加载L2状态机的信息
 输入参数  : enFsmId:L2状态机ID
 输出参数  : 无
 返 回 值  :
 调用函数  :
 被调函数  :

 修改历史      :
 1.日    期   : 2011年5月9日
   作    者   : zhoujun 40661
   修改内容   : 新生成函数

 2.日    期   : 2011年7月14日
   作    者   : w00167002
   修改内容   : V7R1 PHASEII 重构: 增加SYSCFG子状态机的处理

 3.日    期   : 2011年7月20日
   作    者   : w00176964
   修改内容   : V7R1 PHASEII 重构: 增加cellresel,ho,cco子状态机的处理

 4.日    期   : 2011年7月20日
   作    者   : s46746
   修改内容   : V7R1 PHASEII 重构: 增加plmn selection子状态机的处理

 5.日    期   : 2011年9月24日
   作    者   : w00167002
   修改内容   : V7R1 PHASEII 重构: 增加HIGH_PRIO_PLMN_SEARCH子状态机的处理

 6.日    期   : 2012年4月27日
   作    者   : w00176964
   修改内容   : GUL BG搜网调整

 7.日    期   : 2015年05月08日
   作    者   : s00193151
   修改内容   : 漫游搜网优化: 增加COMM SEARCH子状态机的处理
*****************************************************************************/
VOS_VOID  NAS_MMC_LoadSubFsm(
    NAS_MMC_FSM_ID_ENUM_UINT32          enFsmId,
    NAS_MMC_FSM_CTX_STRU               *pstCurFsm
)
{
    switch ( enFsmId )
    {
        case NAS_MMC_FSM_SWITCH_ON :
            pstCurFsm->ulState                  = NAS_MMC_SWITCH_ON_STA_SWITCH_ON_INIT;
            pstCurFsm->pstFsmDesc               = NAS_MMC_GetSwitchOnFsmDescAddr();
            break;

        case NAS_MMC_FSM_POWER_OFF :
            pstCurFsm->ulState                  = NAS_MMC_POWER_OFF_STA_POWEROFF_INIT;
            pstCurFsm->pstFsmDesc               = NAS_MMC_GetPowerOffFsmDescAddr();
            break;

        case NAS_MMC_FSM_PLMN_SELECTION :
            pstCurFsm->ulState                  = NAS_MMC_PLMN_SELECTION_STA_INIT;
            pstCurFsm->pstFsmDesc               = NAS_MMC_GetPlmnSelectionFsmDescAddr();
            break;

        case NAS_MMC_FSM_ANYCELL_SEARCH :
            pstCurFsm->ulState                  = NAS_MMC_ANYCELL_SEARCH_STA_INIT;
            pstCurFsm->pstFsmDesc               = NAS_MMC_GetAnyCellSearchFsmDescAddr();
            break;

        case NAS_MMC_FSM_SYSCFG :
            pstCurFsm->ulState                  = NAS_MMC_SYSCFG_STA_INIT;
            pstCurFsm->pstFsmDesc               = NAS_MMC_GetSysCfgFsmDescAddr();
            break;

        case NAS_MMC_FSM_INTER_SYS_CELLRESEL :
            pstCurFsm->ulState                  = NAS_MMC_INTER_SYS_CELLRESEL_STA_INIT;
            pstCurFsm->pstFsmDesc               = NAS_MMC_GetInterSysCellReselFsmDescAddr();
            break;

        case NAS_MMC_FSM_INTER_SYS_HO :
            pstCurFsm->ulState                  = NAS_MMC_INTER_SYS_HO_STA_INIT;
            pstCurFsm->pstFsmDesc               = NAS_MMC_GetInterSysHoFsmDescAddr();
            break;

        case NAS_MMC_FSM_INTER_SYS_CCO :
            pstCurFsm->ulState                  = NAS_MMC_INTER_SYS_CCO_STA_INIT;
            pstCurFsm->pstFsmDesc               = NAS_MMC_GetInterSysCcoFsmDescAddr();
            break;

        case NAS_MMC_FSM_INTER_SYS_OOS:
            pstCurFsm->ulState                  = NAS_MMC_INTER_SYS_OOS_STA_INIT;
            pstCurFsm->pstFsmDesc               = NAS_MMC_GetInterSysOosFsmDescAddr();
            break;



        case NAS_MMC_FSM_PLMN_LIST:
            pstCurFsm->ulState                  = NAS_MMC_PLMN_LIST_STA_INIT;
            pstCurFsm->pstFsmDesc               = NAS_MMC_GetPlmnListFsmDescAddr();
            break;



        case NAS_MMC_FSM_BG_PLMN_SEARCH:
            pstCurFsm->ulState                  = NAS_MMC_BG_PLMN_SEARCH_STA_INIT;
            pstCurFsm->pstFsmDesc               = NAS_MMC_GetBgPlmnSearchFsmDescAddr();
            break;

        case NAS_MMC_FSM_GET_GEO:
            pstCurFsm->ulState                  = NAS_MMC_GET_GEO_STA_INIT;
            pstCurFsm->pstFsmDesc               = NAS_MMC_GetGeoFsmDescAddr();
            break;

        default:
            NAS_ERROR_LOG(WUEPS_PID_MMC, "NAS_MMC_LoadSubFsm:Invalid Fsm Id");
            break;
    }


    /*执行初始化L2状态机的函数*/
    pstCurFsm->pstFsmDesc->pfInitHandle();
}

/*****************************************************************************
 函 数 名  : NAS_MMC_FSM_InitFsmL2
 功能描述  : MMC启动一个L2或L3的状态机。启动流程的同时启动状态以及保护定时器?
              该函数会进行压栈操作,如果不需要进行协议栈压栈,必须保证退出前流程
 输入参数  : enFsmId:L2状态机ID
 输出参数  : 无
 返 回 值  : VOS_VOID
 调用函数  :
 被调函数  :

 修改历史      :
 1.日    期   : 2011年4月1日
   作    者   : zhoujun /40661
   修改内容   : 新生成函数

 2.日    期   : 2011年10月9日
   作    者   : huwen /44270
   修改内容   : 增加当前状态机的上一层状态机的相关信息
*****************************************************************************/
VOS_VOID NAS_MMC_FSM_InitFsmL2(
    NAS_MMC_FSM_ID_ENUM_UINT32          enFsmId
)
{
    NAS_MMC_FSM_STACK_STRU             *pstFsmStack = VOS_NULL_PTR;
    NAS_MMC_FSM_CTX_STRU               *pstCurFsm   = VOS_NULL_PTR;
    NAS_MMC_FSM_ID_ENUM_UINT32          enParentFsmId;
    VOS_UINT32                          ulParentEventType;

    VOS_UINT16                          usStackDepth;                           /* 当前压栈的状态机数 */

    enParentFsmId                       = NAS_FSM_BUTT;

    pstCurFsm                           = NAS_MMC_GetCurFsmAddr();
    pstFsmStack                         = NAS_MMC_GetFsmStackAddr();

    /*  打印压栈前的L1和L2状态 */
    NAS_MMC_LogMmcFsmInfo();


    /* 记录压栈前的状态机名和入口消息类型 */
    enParentFsmId                       = pstCurFsm->enFsmId;
    ulParentEventType                   = pstCurFsm->stEntryMsg.ulEventType;

    /* 将当前状态机压栈操作 */
    NAS_MMC_FSM_PushFsm(pstFsmStack, pstCurFsm);

    /* 设置当前状态机 */
    pstCurFsm->enFsmId                  = enFsmId;

    /* 加载L2状态机 */
    NAS_MMC_LoadSubFsm(enFsmId, pstCurFsm);

    /* 记录上层状态机名和入口消息类型 */
    pstCurFsm->enParentFsmId            = enParentFsmId;
    pstCurFsm->ulParentEventType        = ulParentEventType;

    usStackDepth = pstFsmStack->usStackDepth;

    pstCurFsm->punParentFsmCtx = VOS_NULL_PTR;

    /* 增加状态机栈深的异常保护 */
    if ( (0            < usStackDepth)
      && (usStackDepth <= NAS_MMC_MAX_STACK_DEPTH) )
    {
        /* 记录上层状态机的数据内容地址 */
        pstCurFsm->punParentFsmCtx          = &(pstFsmStack->astFsmStack[(usStackDepth - 1)].unFsmCtx);
    }


    /*  打印当前的L1和L2状态 */
    NAS_MMC_LogMmcFsmInfo();
}


/*****************************************************************************
 函 数 名  : NAS_MMC_FSM_QuitFsmL2
 功能描述  : 结束L2状态机。如果结束流程，状态机弹出状态栈
 输入参数  : 无
 输出参数  : 无
 返 回 值  : VOS_VOID
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2011年4月1日
    作    者   : zhoujun /40661
    修改内容   : 新生成函数
*****************************************************************************/
VOS_VOID NAS_MMC_FSM_QuitFsmL2( VOS_VOID )
{
    NAS_MMC_FSM_CTX_STRU               *pstCurFsm   = VOS_NULL_PTR;

    pstCurFsm                           = NAS_MMC_GetCurFsmAddr();

    /* QUIT时清空当前L2状态机的CTX */
    pstCurFsm->pstFsmDesc->pfInitHandle();

    /*  打印压栈前的L1和L2状态 */
    NAS_MMC_LogMmcFsmInfo();

    /* 状态机出栈操作 */
    NAS_MMC_FSM_PopFsm();

    /*  打印当前的L1和L2状态 */
    NAS_MMC_LogMmcFsmInfo();

    return;
}
/*****************************************************************************
 函 数 名  : NAS_MMC_FSM_SetCurrState
 功能描述  : 设置当前需要迁移的状态
 输入参数  : ulCurrState:当前迁移的状态
 输出参数  : 无
 返 回 值  :
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2011年4月1日
    作    者   : zhoujun /40661
    修改内容   : 新生成函数
*****************************************************************************/
VOS_VOID  NAS_MMC_FSM_SetCurrState(
    VOS_UINT32                          ulCurrState
)
{
    NAS_MMC_FSM_CTX_STRU               *pstCurFsm   = VOS_NULL_PTR;

    /* 获取当前的状态信息 */
    pstCurFsm                   = NAS_MMC_GetCurFsmAddr();

    /* 设置当前状态 */
    pstCurFsm->ulState          = ulCurrState;

    /*  打印当前的L1和L2状态 */
    NAS_MMC_LogMmcFsmInfo();

    return;
}


/*****************************************************************************
 函 数 名  : NAS_FSM_GetFsmTopState
 功能描述  : 获取状态机顶层的状态
 输入参数  : 无
 输出参数  : 无
 返 回 值  : 当前状态机的顶层状态
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2011年4月19日
    作    者   : zhoujun /40661
    修改内容   : 新生成函数

*****************************************************************************/
VOS_UINT32 NAS_MMC_GetFsmTopState( VOS_VOID )
{
    NAS_MMC_FSM_CTX_STRU               *pstCurFsm   = VOS_NULL_PTR;
    VOS_UINT32                          ulState;

    /* 获取当前状态机 */
    pstCurFsm               = NAS_MMC_GetCurFsmAddr();
    ulState                 = pstCurFsm->ulState;

    return ulState;
}

/*****************************************************************************
 函 数 名  : NAS_MMC_GetFsmStackDepth
 功能描述  : 获取当前协议栈的栈深度
 输入参数  : 无
 输出参数  : 无
 返 回 值  : 当前状态机的深度
 调用函数  :
 被调函数  :

 修改历史      :
 1.日    期   : 2011年4月22日
   作    者   : zhoujun /40661
   修改内容   : 新生成函数

 2.日    期   : 2011年10月10日
   作    者   : zhoujun /40661
   修改内容   :  修改栈深度的类型
*****************************************************************************/
VOS_UINT16  NAS_MMC_GetFsmStackDepth( VOS_VOID )
{
    NAS_MMC_FSM_STACK_STRU             *pstFsmStack = VOS_NULL_PTR;

    pstFsmStack = NAS_MMC_GetFsmStackAddr();

    return pstFsmStack->usStackDepth;
}

/*****************************************************************************
 函 数 名  : NAS_MMC_GetTimerAddr
 功能描述  : 获取MMC CTX模块中定时器的上下文
 输入参数  : 无
 输出参数  : 无
 返 回 值  :
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2011年7月25日
    作    者   : zhoujun 40661
    修改内容   : 新生成函数

*****************************************************************************/
NAS_MMC_TIMER_CTX_STRU*  NAS_MMC_GetTimerAddr( VOS_VOID )
{
    return g_stNasMmcCtx.astMmcTimerCtx;
}

/*****************************************************************************
 函 数 名  : NAS_MMC_SaveCacheMsgInMsgQueue
 功能描述  : 将缓存消息保存的缓存内存池中
 输入参数  : ulEventType:消息ID+PID
             pMsg      :消息内容
 输出参数  : 无
 返 回 值  :
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2011年8月6日
    作    者   : zhoujun 40661
    修改内容   : 新生成函数

*****************************************************************************/
VOS_VOID  NAS_MMC_SaveCacheMsgInMsgQueue(
    VOS_UINT32                          ulEventType,
    VOS_VOID                           *pstMsg
)
{
    NAS_MMC_MSG_QUEUE_STRU              *pstMsgQueue   = VOS_NULL_PTR;
    MSG_HEADER_STRU                     *pstMsgHeader  = VOS_NULL_PTR;

    pstMsgHeader = (MSG_HEADER_STRU*)pstMsg;

    pstMsgQueue = NAS_MMC_GetCachMsgBufferAddr();

    if ( pstMsgQueue->ucCacheMsgNum >= NAS_MMC_MAX_MSG_QUEUE_NUM )
    {
        NAS_ERROR_LOG(WUEPS_PID_MMC, "NAS_MMC_SaveCacheMsgInMsgQueue:No Empty buffer");

        NAS_MMC_LogBufferQueueMsg(VOS_TRUE);

        return ;
    }

    pstMsgQueue->astMsgQueue[pstMsgQueue->ucCacheMsgNum].stMsgEntry.ulEventType   = ulEventType;
    PS_MEM_CPY((pstMsgQueue->astMsgQueue[pstMsgQueue->ucCacheMsgNum].stMsgEntry.aucEntryMsgBuffer),
               pstMsg,
               pstMsgHeader->ulLength + VOS_MSG_HEAD_LENGTH);
    pstMsgQueue->ucCacheMsgNum++;

    NAS_INFO_LOG1(WUEPS_PID_MMC, "NAS_MMC_SaveCacheMsgInMsgQueue:Cache Num", pstMsgQueue->ucCacheMsgNum);

    NAS_MMC_LogBufferQueueMsg(VOS_FALSE);
}

/*****************************************************************************
 函 数 名  : NAS_MMC_SaveCacheMsg
 功能描述  : 保存当前需要处理的缓存
 输入参数  : ulEventType:消息ID+PID
             pMsg      :消息内容
 输出参数  : 无
 返 回 值  : VOS_TRUE:保存成功
             VOS_FALSE:保存失败
 调用函数  :
 被调函数  :

 修改历史      :
 1.日    期   : 2011年4月20日
   作    者   : zhoujun /40661
   修改内容   : 新生成函数
 2.日    期   : 2015年11月9日
   作    者   : s00217060
   修改内容   : ROAM_PLMN_SELECTION_OPTIMIZE_3.0修改:新增对DPLMN SET REQ的
                 处理

*****************************************************************************/
VOS_VOID NAS_MMC_SaveCacheMsg(
    VOS_UINT32                          ulEventType,
    VOS_VOID                           *pstMsg
)
{
    MSG_HEADER_STRU                     *pstMsgHeader  = VOS_NULL_PTR;

    pstMsgHeader = (MSG_HEADER_STRU*)pstMsg;

    if ( pstMsgHeader->ulLength >= ( NAS_MMC_MAX_MSG_BUFFER_LEN - VOS_MSG_HEAD_LENGTH) )
    {
        NAS_ERROR_LOG(WUEPS_PID_MMC, "NAS_MMC_SaveCacheMsg:Len too Long");
        return;
    }

    /* 比较消息优先级,判断是否需要保存在缓存池中 */
    if ( VOS_FALSE == NAS_MMC_IsNeedCacheMsg(ulEventType, pstMsg))
    {
        NAS_INFO_LOG(WUEPS_PID_MMC, "NAS_MMC_SaveCacheMsg:already exist msg");
        return;
    }

    /* 将消息缓存在缓存内存池中 */
    NAS_MMC_SaveCacheMsgInMsgQueue(ulEventType, pstMsg);

    return;
}


/*****************************************************************************
 函 数 名  : NAS_MMC_GetNextInterSysCachedMsg
 功能描述  : 获取当前存在的异系统重选消息
 输入参数  : 无
 输出参数  : 无
 返 回 值  :
 调用函数  :
 被调函数  :

 修改历史      :
 1.日    期   : 2011年11月7日
   作    者   : zhoujun 40661
   修改内容   : 新生成函数

*****************************************************************************/
VOS_UINT32  NAS_MMC_GetNextInterSysCachedMsg(
    NAS_MMC_ENTRY_MSG_STRU             *pstEntryMsg
)
{
    VOS_UINT32                          ulCacheFlg;

    ulCacheFlg  = VOS_FALSE;

    switch ( pstEntryMsg->ulEventType)
    {
        case NAS_BuildEventType(WUEPS_PID_WRR, RRMM_SUSPEND_IND):
        case NAS_BuildEventType(UEPS_PID_GAS, RRMM_SUSPEND_IND):
            ulCacheFlg = VOS_TRUE;

            break;

        default:
            NAS_INFO_LOG(WUEPS_PID_MMC, "NAS_MMC_GetNextInterSysCachedMsg:No Empty suspend buffer");
            break;
    }

    return ulCacheFlg;
}



/*****************************************************************************
 函 数 名  : NAS_MMC_GetNextUserCachedMsg
 功能描述  : 获取缓存的User缓存消息
 输入参数  : 无
 输出参数  : pstEntryMsg:缓存的用户消息
 返 回 值  : VOS_TRUE:高优先级的缓存存在
             VOS_FALSE:高优先级的缓存不存在
 调用函数  :
 被调函数  :

 修改历史      :
 1.日    期   : 2011年10月9日
   作    者   : zhoujun /40661
   修改内容   : 新生成函数
 2.日    期   : 2013年3月30日
   作    者   : l00167671
   修改内容   : 主动上报AT命令控制下移至C核
 3.日    期   : 2015年9月6日
   作    者   : z00161729
   修改内容   : 支持LTE CSG功能新增
*****************************************************************************/
VOS_UINT32  NAS_MMC_GetNextUserCachedMsg(
    NAS_MMC_ENTRY_MSG_STRU             *pstEntryMsg
)
{
    VOS_UINT32                          ulCacheFlg;

    ulCacheFlg  = VOS_FALSE;

    /* Modified by l00167671 for 主动上报AT命令控制下移至C核, 2013-3-30, begin */
    switch ( pstEntryMsg->ulEventType)
    {
        case NAS_BuildEventType(UEPS_PID_MSCC, ID_MSCC_MMC_PLMN_SPECIAL_REQ):
        case NAS_BuildEventType(UEPS_PID_MSCC, ID_MSCC_MMC_SYS_CFG_SET_REQ):
        case NAS_BuildEventType(UEPS_PID_MSCC, ID_MSCC_MMC_PLMN_LIST_REQ)  :
#if (FEATURE_ON == FEATURE_CSG)
        case NAS_BuildEventType(UEPS_PID_MSCC, ID_MSCC_MMC_CSG_LIST_SEARCH_REQ):
#endif
            ulCacheFlg = VOS_TRUE;

            break;

        default:
            NAS_INFO_LOG(WUEPS_PID_MMC, "NAS_MMC_GetNextUserCachedMsg:No Empty buffer");
            break;
    }
    /* Modified by l00167671 for 主动上报AT命令控制下移至C核, 2013-3-30, begin */

    return ulCacheFlg;

}

/*****************************************************************************
 函 数 名  : NAS_MMC_GetNextHighPrioCachedMsg
 功能描述  : 扫描高优先级的缓存是否存在
 输入参数  : 无
 输出参数  : pstEntryMsg:高优先级的缓存
 返 回 值  : VOS_TRUE:高优先级的缓存存在
             VOS_FALSE:高优先级的缓存不存在
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2011年8月6日
    作    者   : zhoujun 40661
    修改内容   : 新生成函数

  2.日    期   : 2011年9月29日
    作    者   : zhoujun 40661
    修改内容   : 重新根据优先级获取缓存消息

  3.日    期   : 2011年11月7日
    作    者   : zhoujun 40661
    修改内容   : RRMM_SUSPEND_IND消息的优先级比较高,需要优先获取该消息。

*****************************************************************************/
VOS_UINT32 NAS_MMC_GetNextHighPrioCachedMsg(
    NAS_MMC_ENTRY_MSG_STRU             *pstEntryMsg
)
{
    VOS_UINT32                          i;
    NAS_MMC_MSG_QUEUE_STRU             *pstMsgQueue = VOS_NULL_PTR;
    VOS_UINT32                          ulCacheFlg  ;

    pstMsgQueue                         = NAS_MMC_GetCachMsgBufferAddr();
    ulCacheFlg                          = VOS_FALSE;


    /* 必须先获取所有的状态机的非入口消息 */
    for ( i = 0 ; i < pstMsgQueue->ucCacheMsgNum; i++ )
    {
        /* 优先获取状态机非入口消息 */
        if ( VOS_FALSE == NAS_MMC_IsFsmEntryEventType(pstMsgQueue->astMsgQueue[i].stMsgEntry.ulEventType) )
        {
            PS_MEM_CPY(pstEntryMsg,
                       &(pstMsgQueue->astMsgQueue[i].stMsgEntry),
                       sizeof(NAS_MMC_ENTRY_MSG_STRU));

            ulCacheFlg = VOS_TRUE;

        }

        /* 找到高优先级的消息后，完成高优先级消息的拷贝和清除 */
        if ( VOS_TRUE == ulCacheFlg )
        {
            NAS_MMC_ClearCacheMsg(pstEntryMsg->ulEventType);
            return VOS_TRUE;
        }
    }

    /* 认为intersys消息的优先级比用户请求消息的优先级高,目前仅在BG搜索过程
       中,收到rrmm_suspend_ind消息后会打断当前状态机缓存intersys消息*/
    /* 必须先获取所有的intersys消息 */
    for ( i = 0 ; i < pstMsgQueue->ucCacheMsgNum; i++ )
    {
        if ( VOS_TRUE == NAS_MMC_GetNextInterSysCachedMsg(&(pstMsgQueue->astMsgQueue[i].stMsgEntry)) )
        {
            PS_MEM_CPY(pstEntryMsg,
                   &(pstMsgQueue->astMsgQueue[i].stMsgEntry),
                   sizeof(NAS_MMC_ENTRY_MSG_STRU));

            ulCacheFlg = VOS_TRUE;
        }

        /* 找到高优先级的消息后，完成高优先级消息的拷贝和清除 */
        if ( VOS_TRUE == ulCacheFlg )
        {
            NAS_MMC_ClearCacheMsg(pstEntryMsg->ulEventType);
            return VOS_TRUE;
        }
    }

    /* 必须先获取所有的高优先级消息 */
    for ( i = 0 ; i < pstMsgQueue->ucCacheMsgNum; i++ )
    {
        /* 用户的缓存消息优先级次高 */
        ulCacheFlg = NAS_MMC_GetNextUserCachedMsg(&(pstMsgQueue->astMsgQueue[i].stMsgEntry));
        if ( VOS_TRUE == ulCacheFlg )
        {
            PS_MEM_CPY(pstEntryMsg,
                   &(pstMsgQueue->astMsgQueue[i].stMsgEntry),
                   sizeof(NAS_MMC_ENTRY_MSG_STRU));
        }


        /* 找到高优先级的消息后，完成高优先级消息的拷贝和清除 */
        if ( VOS_TRUE == ulCacheFlg )
        {
            NAS_MMC_ClearCacheMsg(pstEntryMsg->ulEventType);
            return VOS_TRUE;
        }
    }



    return VOS_FALSE;
}

/*****************************************************************************
 函 数 名  : NAS_MMC_GetNextNormalPrioCachedMsg
 功能描述  : 获取普通的缓存消息
 输入参数  : 无
 输出参数  : 无
 返 回 值  :
 调用函数  :
 被调函数  :

 修改历史      :
 1.日    期   : 2011年10月9日
   作    者   : zhoujun /40661
   修改内容   : 新生成函数

*****************************************************************************/
VOS_UINT32  NAS_MMC_GetNextNormalPrioCachedMsg(
    NAS_MMC_ENTRY_MSG_STRU             *pstEntryMsg
)
{
    NAS_MMC_MSG_QUEUE_STRU             *pstMsgQueue = VOS_NULL_PTR;

    pstMsgQueue                         = NAS_MMC_GetCachMsgBufferAddr();

    if ( 0 == pstMsgQueue->ucCacheMsgNum )
    {
        NAS_INFO_LOG(WUEPS_PID_MMC, "NAS_MMC_GetNextCachedMsg:Empty buffer");

        return VOS_FALSE;
    }

    /* 按照先入先出原则,默认取第1个缓存内容 */
    PS_MEM_CPY(pstEntryMsg,
               &(pstMsgQueue->astMsgQueue[0].stMsgEntry),
               sizeof(NAS_MMC_ENTRY_MSG_STRU));

    /* 消息已经取出则清除当前缓存 */
    NAS_MMC_ClearCacheMsg(pstEntryMsg->ulEventType);

    return VOS_TRUE;
}

/*****************************************************************************
 函 数 名  : NAS_MMC_GetNextCachedMsg
 功能描述  : 获取当前需要处理的缓存
 输入参数  : 无
 输出参数  : pstEntryMSg:当前优先级最高的缓存消息
 返 回 值  : VOS_OK:获取成功
             VOS_ERR:获取失败
 调用函数  :
 被调函数  :

 修改历史      :
 1.日    期   : 2011年4月20日
   作    者   : zhoujun /40661
   修改内容   : 新生成函数

 2.日    期   : 2011年10月9日
   作    者   : zhoujun /40661
   修改内容   : 优先获取高优先级的缓存消息
*****************************************************************************/
VOS_UINT32  NAS_MMC_GetNextCachedMsg(
    NAS_MMC_ENTRY_MSG_STRU             *pstEntryMsg
)
{
    NAS_MMC_MSG_QUEUE_STRU             *pstMsgQueue = VOS_NULL_PTR;

    pstMsgQueue                         = NAS_MMC_GetCachMsgBufferAddr();

    if ( 0 == pstMsgQueue->ucCacheMsgNum )
    {
        NAS_INFO_LOG(WUEPS_PID_MMC, "NAS_MMC_GetNextCachedMsg:Empty buffer");

        return VOS_FALSE;
    }


    /* 如果存在高优先级的消息,先返回高优先级的消息, 优先级高的消息优先得到处理 */
    if ( VOS_TRUE == NAS_MMC_GetNextHighPrioCachedMsg(pstEntryMsg) )
    {
        return VOS_TRUE;
    }

    /* 获取普通的缓存消息成功,返回普通的缓存消息 */
    if ( VOS_TRUE == NAS_MMC_GetNextNormalPrioCachedMsg(pstEntryMsg) )
    {
        return VOS_TRUE;
    }

    return VOS_FALSE;

}

/*****************************************************************************
 函 数 名  : NAS_MMC_IsExistCacheMsg
 功能描述  : 判断当前消息是否已经缓存
 输入参数  : ulEventType:消息ID
 输出参数  : pulIndex   :缓存的消息索引
 返 回 值  : VOS_TRUE:存在缓存的消息
             VOS_FALSE:不存在缓存的消息
 调用函数  :pulIndex
 被调函数  :

 修改历史      :
 1.日    期   : 2011年7月25日
   作    者   : zhoujun /40661
   修改内容   : 新生成函数

*****************************************************************************/
VOS_UINT32  NAS_MMC_IsExistCacheMsg(
    VOS_UINT32                          ulEventType,
    VOS_UINT32                         *pulIndex
)
{
    NAS_MMC_MSG_QUEUE_STRU             *pstMsgQueue = VOS_NULL_PTR;
    VOS_UINT32                          i;

    pstMsgQueue                         = NAS_MMC_GetCachMsgBufferAddr();
   *pulIndex                           = 0;

    for ( i = 0 ; i < pstMsgQueue->ucCacheMsgNum ; i++ )
    {
        if ( ulEventType == pstMsgQueue->astMsgQueue[i].stMsgEntry.ulEventType)
        {
            *pulIndex   = i;
            return VOS_TRUE;
        }

    }


    NAS_INFO_LOG(WUEPS_PID_MMC, "NAS_MMC_IsExistCacheMsg:not match MSG");

    return VOS_FALSE;
}


/*****************************************************************************
 函 数 名  : NAS_MMC_ClearCacheMsg
 功能描述  : 清除指定的缓存消息
 输入参数  : ulEventType:清除需求缓存的消息类型
 输出参数  : 无
 返 回 值  : VOS_VOID
 调用函数  :
 被调函数  :

 修改历史      :
 1.日    期   : 2011年8月06日
   作    者   : zhoujun /40661
   修改内容   : 新生成函数

*****************************************************************************/
VOS_VOID NAS_MMC_ClearCacheMsg(
    VOS_UINT32                          ulEventType
)
{
    NAS_MMC_MSG_QUEUE_STRU             *pstMsgQueue = VOS_NULL_PTR;
    VOS_INT8                            i;
    VOS_INT8                            cCachePos;

    pstMsgQueue                         = NAS_MMC_GetCachMsgBufferAddr();
    cCachePos                           = -1;

    /* 先找到需要被清除的缓存 */
    for ( i = 0 ; i < pstMsgQueue->ucCacheMsgNum ; i++ )
    {
        if ( ulEventType == pstMsgQueue->astMsgQueue[i].stMsgEntry.ulEventType )
        {
            PS_MEM_SET(&(pstMsgQueue->astMsgQueue[i].stMsgEntry),
                       0x00,
                       sizeof(NAS_MMC_ENTRY_MSG_STRU));
            cCachePos = (VOS_INT8)i;
        }
    }

    /* 未找到该消息类型直接返回 */
    if ( -1 == cCachePos )
    {
        NAS_INFO_LOG1(WUEPS_PID_MMC, "NAS_MMC_ClearCacheMsg:invalid msg type", ulEventType);
        return;
    }

    /* 为保证先入先出,需要将后面的消息移到前面 */
    for ( i = cCachePos ; i < (pstMsgQueue->ucCacheMsgNum - 1) ; i++ )
    {
        /* COPY消息内容 */
        PS_MEM_CPY(&(pstMsgQueue->astMsgQueue[i].stMsgEntry),
                   &(pstMsgQueue->astMsgQueue[i + 1].stMsgEntry),
                   sizeof(NAS_MMC_ENTRY_MSG_STRU));

    }

    /* 将缓存个数减一 */
    pstMsgQueue->ucCacheMsgNum--;

    /* 将当前缓存给打印出来 */
    NAS_MMC_LogBufferQueueMsg(VOS_FALSE);

    return;
}


/*****************************************************************************
 函 数 名  : NAS_MMC_ClearAllCacheMsg
 功能描述  : 清除所有的缓存消息
 输入参数  : 无
 输出参数  : 无
 返 回 值  : VOS_VOID
 调用函数  :
 被调函数  :

 修改历史      :
 1.日    期   : 2011年7月25日
   作    者   : zhoujun /40661
   修改内容   : 新生成函数

*****************************************************************************/
VOS_VOID NAS_MMC_ClearAllCacheMsg( VOS_VOID )
{
    NAS_MMC_MSG_QUEUE_STRU             *pstMsgQueue = VOS_NULL_PTR;
    VOS_UINT32                          i;

    pstMsgQueue                         = NAS_MMC_GetCachMsgBufferAddr();

    pstMsgQueue->ucCacheMsgNum          = 0;

    for ( i = 0 ; i < NAS_MMC_MAX_MSG_QUEUE_NUM ; i++ )
    {
        PS_MEM_SET(&(pstMsgQueue->astMsgQueue[i].stMsgEntry),
                   0x00,
                   sizeof(NAS_MMC_ENTRY_MSG_STRU));
    }

    NAS_MMC_LogBufferQueueMsg(VOS_FALSE);
    return;
}

/*****************************************************************************
 函 数 名  : NAS_MMC_InitFsmCtx_L1Main
 功能描述  : 初始化L1状态机上下文
 输入参数  : 无
 输出参数  : 无
 返 回 值  :
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2011年5月7日
    作    者   : w00176964
    修改内容   : 新生成函数
  2.日    期   : 2014年1月2日
    作    者   : z00161729
    修改内容   : SVLTE支持NCELL搜网
  3.日    期   : 2014年2月24日
    作    者   : w00176964
    修改内容   : High_Rat_Hplmn_Search特性调整
  4.日    期   : 2015年6月4日
    作    者   : s00217060
    修改内容   : ROAM_PLMN_SELECTION_OPTIMIZE_2.0修改
*****************************************************************************/

VOS_VOID  NAS_MMC_InitFsmCtx_L1Main(VOS_VOID)
{
    NAS_MMC_ClearAllRegAdditionalAction_L1Main();

    NAS_MMC_ResetOosPlmnSearchTimerCount_OnPlmn();

    NAS_MMC_ResetCurHighPrioRatHplmnTimerFirstSearchCount_L1Main();

    NAS_MMC_ClearAllRegAttemptCount_L1Main();

    /* 默认AVAILABLE COUNTER为NORMAL类型 */
    NAS_MMC_SetAvailableTimerType_OnPlmn(NAS_MMC_AVAILABLE_TIMER_TYPE_NORMAL);
}


/*****************************************************************************
 函 数 名  : NAS_MMC_InitFsmCtx_SwitchOn
 功能描述  : NAS_MMC_InitFsmCtx_SwitchOn
 输入参数  : VOS_VOID
 输出参数  : 无
 返 回 值  : VOS_VOID
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2011年5月7日
    作    者   : l00130025
    修改内容   : 新生成函数

  2.日    期   : 2012年8月13日
    作    者   : w00167002
    修改内容   : V7R1C50_GUTL_PhaseII:,更改当前的开机顺序为G->L->W，初始化
                  开机状态机上下文时

  3.日    期   : 2013年2月25日
    作    者   : w00167002
    修改内容   : DTS2013022500811:LAST RPLMN rat特性开启，插拔换卡后，没有
                  使用SYSCFG设置的顺序搜RPLMN.
*****************************************************************************/
VOS_VOID  NAS_MMC_InitFsmCtx_SwitchOn(VOS_VOID)
{
    NAS_MMC_SENDING_AS_SWITCH_ON_SEQUENCE_CTRL_STRU        *pstSwitchOnRecord;
    NAS_MML_NET_RAT_TYPE_ENUM_UINT8                        *pucSwitchOnRatPrio;

    VOS_UINT8                                              *pucLastImsi = VOS_NULL_PTR;

    VOS_UINT32                                              i;

    /* 获取状态机中的要设置SYSCFG接入模所对应的索引和列表地址 */
    pstSwitchOnRecord                   = NAS_MMC_GetSwitchOnSequenceRecord_SwitchOn();
    pucSwitchOnRatPrio                  = pstSwitchOnRecord->aucSwitchOnRatPrio;

    pucLastImsi = NAS_MMC_GetLastImsi_SwitchOn();

    NAS_MMC_ClearAllWaitMmStartCnfFlg_SwitchOn();
    NAS_MMC_ClearAllWaitSimFilesCnfFlg_SwitchOn();

    /* Switch On状态机上下文中设置接入层开机优先级顺序信息的初始化:
       搜网索引初始化为0,每向接入层发送卡机后，该索引自增1，表示要发开机的模的接入模式 */
    pstSwitchOnRecord->ucSwitchOnIndex = 0;

    /* 设置需要下发开机接入技术的总个数 */
    pstSwitchOnRecord->ucTotalSwitchOnRatNum = 0;

    /* SYSCFG状态机上下文中设置接入层优先级顺序信息的初始化:
       接入模式全部初始化为NAS_MML_NET_RAT_TYPE_BUTT */
    for ( i = 0 ; i < NAS_MML_MAX_RAT_NUM; i++ )
    {
        pucSwitchOnRatPrio[i]           = NAS_MML_NET_RAT_TYPE_BUTT;
    }


    /* 初始化状态机上下文中的开机钱的IMSI信息 */
    for ( i = 0 ; i < NAS_MML_MAX_IMSI_LEN ; i++ )
    {
        pucLastImsi[i] = NAS_MML_IMSI_INVALID;
    }
}

/*****************************************************************************
 函 数 名  : NAS_MMC_GetSwitchOnSequenceRecord_SwitchOn
 功能描述  : 获取状态机中的NAS_MMC_SENDING_AS_SWITCH_ON_SEQUENCE_CTRL_STRU结构值
 输入参数  : 无
 输出参数  : 无
 返 回 值  : SwitchOn状态机上下文中的记录向接入层发送开机的先后顺序信息

 调用函数  :
 被调函数  :

 修改历史      :
 1.日    期   : 2012-08-03
   作    者   : w00167002
   修改内容   : 新生成函数

****************************************************************************/
NAS_MMC_SENDING_AS_SWITCH_ON_SEQUENCE_CTRL_STRU* NAS_MMC_GetSwitchOnSequenceRecord_SwitchOn(VOS_VOID)
{
    NAS_MMC_CONTEXT_STRU               *pstNasMmcCtx        = VOS_NULL_PTR;
    pstNasMmcCtx = NAS_MMC_GetMmcCtxAddr();

    /* 如果当前状态机不是NAS_MMC_FSM_SWITCH_ON */
    if (NAS_MMC_FSM_SWITCH_ON != NAS_MMC_GetCurrFsmId())
    {
        NAS_ERROR_LOG(WUEPS_PID_MMC, "NAS_MMC_GetSwitchOnSettingRecord_SwitchOn,ERROR:FsmId Error");
    }

    return &(pstNasMmcCtx->stCurFsm.unFsmCtx.stSwitchOnCtx.stSwitchOnRecord);
}



/*****************************************************************************
 函 数 名  : NAS_MMC_AddSwitchOnIndex_SwitchOn
 功能描述  : 设置下一个需要设置SwitchOn模的接入技术
 输入参数  : 无
 输出参数  : 无
 返 回 值  : 无

 调用函数  :
 被调函数  :

 修改历史      :
 1.日    期   : 2011年7月2日
   作    者   : w00167002
   修改内容   : 新生成函数

*****************************************************************************/
VOS_VOID NAS_MMC_AddSwitchOnIndex_SwitchOn(VOS_VOID)
{
    NAS_MMC_SENDING_AS_SWITCH_ON_SEQUENCE_CTRL_STRU        *pstSwitchOnRecord;

    /* 如果当前状态机不是NAS_MMC_FSM_SwitchOn */
    if (NAS_MMC_FSM_SWITCH_ON != NAS_MMC_GetCurrFsmId())
    {
        NAS_ERROR_LOG(WUEPS_PID_MMC, "NAS_MMC_AddSwitchOnIndex_SwitchOn,ERROR:FsmId Error");
    }

    /* 获取状态机中的要设置SwitchOn接入模所对应的索引和列表地址 */
    pstSwitchOnRecord   = NAS_MMC_GetSwitchOnSequenceRecord_SwitchOn();

    /* 更新INDEX索引,指向下一个要进行SwitchOn设置的接入技术 */
    pstSwitchOnRecord->ucSwitchOnIndex ++;

    /* 返回 */
    return ;
}



/*****************************************************************************
 函 数 名  : NAS_MMC_GetNextSettingRat_SwitchOn
 功能描述  : 获取下一个需要设置SwitchOn模的接入技术
 输入参数  : 无
 输出参数  : 无
 返 回 值  : NAS_MML_NET_RAT_TYPE_ENUM_UINT8类型:接入技术,列举如下
             NAS_MML_NET_RAT_TYPE_GSM,
             NAS_MML_NET_RAT_TYPE_WCDMA,
             NAS_MML_NET_RAT_TYPE_LTE,
             NAS_MML_NET_RAT_TYPE_BUTT

 调用函数  :
 被调函数  :

 修改历史      :
 1.日    期   : 2011年7月2日
   作    者   : w00167002
   修改内容   : 新生成函数

*****************************************************************************/
NAS_MML_NET_RAT_TYPE_ENUM_UINT8 NAS_MMC_GetNextSendingRat_SwitchOn(VOS_VOID)
{
    NAS_MML_NET_RAT_TYPE_ENUM_UINT8                        *pucSwitchOnRatPrio;
    NAS_MMC_SENDING_AS_SWITCH_ON_SEQUENCE_CTRL_STRU        *pstSwitchOnRecord;
    NAS_MML_NET_RAT_TYPE_ENUM_UINT8                         ucNextSwitchOnRat;

    /* 如果当前状态机不是NAS_MMC_FSM_SwitchOn */
    if (NAS_MMC_FSM_SWITCH_ON != NAS_MMC_GetCurrFsmId())
    {
        NAS_WARNING_LOG(WUEPS_PID_MMC, "NAS_MMC_GetNextSendingRat_SwitchOn,ERROR:FsmId Error");
    }

    pstSwitchOnRecord      = NAS_MMC_GetSwitchOnSequenceRecord_SwitchOn();

    /* 获取状态机中的要设置SwitchOn接入模所对应的索引和列表地址 */
    pucSwitchOnRatPrio     = pstSwitchOnRecord->aucSwitchOnRatPrio;

    /* 如果索引以到达设置的总个数，返回接入技术为无效值，表示SwitchOn设置结束 */
    if ( pstSwitchOnRecord->ucSwitchOnIndex >= pstSwitchOnRecord->ucTotalSwitchOnRatNum )
    {
        return NAS_MML_NET_RAT_TYPE_BUTT;
    }

    /* 取得数组中索引所对应的接入技术 */
    ucNextSwitchOnRat                     = pucSwitchOnRatPrio[pstSwitchOnRecord->ucSwitchOnIndex];

    /* 返回需要SwitchOn设置的接入技术 */
    return ucNextSwitchOnRat;
}

/*****************************************************************************
 函 数 名  : NAS_MMC_SetSwitchOnSendingAsOrder_SwitchOn
 功能描述  : 设置向接入层下发SwitchOn的先后顺序
 输入参数  : 无
 输出参数  : 无
 返 回 值  : 无
 调用函数  :
 被调函数  :

 修改历史      :
 1.日    期   : 2012年8月3日
   作    者   : w00167002
   修改内容   : 新生成函数
 2.日    期   : 2012年12月26日
   作    者   : s00217060
   修改内容   : for DSDA GUNAS C CORE:调整为只给平台支持的接入层发送开机请求
*****************************************************************************/
VOS_VOID NAS_MMC_SetSwitchOnSendingAsOrder_SwitchOn(VOS_VOID)
{
    NAS_MMC_SENDING_AS_SWITCH_ON_SEQUENCE_CTRL_STRU        *pstSwitchOnSettingRecord = VOS_NULL_PTR;
    NAS_MML_NET_RAT_TYPE_ENUM_UINT8                        *pucSwitchOnRatPrio       = VOS_NULL_PTR;
    VOS_UINT8                                               ucRatIndex;

    /* 如果当前状态机不是NAS_MMC_FSM_SwitchOn */
    if (NAS_MMC_FSM_SWITCH_ON != NAS_MMC_GetCurrFsmId())
    {
        NAS_ERROR_LOG(WUEPS_PID_MMC, "NAS_MMC_SetSwitchOnSendingOrder_SwitchOn,ERROR:FsmId Error");
    }

    ucRatIndex                          = 0;

    /* 取得当前 SwitchOn状态机上下文中的记录设置接入层优先级顺序信息 */
    pstSwitchOnSettingRecord            = NAS_MMC_GetSwitchOnSequenceRecord_SwitchOn();
    pucSwitchOnRatPrio                  = pstSwitchOnSettingRecord->aucSwitchOnRatPrio;

    /* 设置下发SwitchOn请求的顺序为GLW,若LTE不支持，则为GW */
    if (VOS_TRUE == NAS_MML_IsPlatformSupportGsm())
    {
        pucSwitchOnRatPrio[ucRatIndex]      = NAS_MML_NET_RAT_TYPE_GSM;
        ucRatIndex++;
    }

#if (FEATURE_ON == FEATURE_LTE)
    if (VOS_TRUE == NAS_MML_IsPlatformSupportLte())
    {
        pucSwitchOnRatPrio[ucRatIndex]      = NAS_MML_NET_RAT_TYPE_LTE;
        ucRatIndex++;
    }
#endif

    /* 如果平台支持W或TD，需要给U模发开机请求 */
    if (VOS_TRUE == NAS_MML_IsPlatformSupportUtran())
    {
        pucSwitchOnRatPrio[ucRatIndex]      = NAS_MML_NET_RAT_TYPE_WCDMA;
        ucRatIndex++;
    }

    /* 设置需要下发开机接入层的总个数 */
    pstSwitchOnSettingRecord->ucTotalSwitchOnRatNum = ucRatIndex;

    return;
}

/*****************************************************************************
 函 数 名  : NAS_MMC_GetLastImsi_SwitchOn
 功能描述  : 获取下一个需要设置SwitchOn模的接入技术
 输入参数  : 无
 输出参数  : 无
 返 回 值  : 返回存储开机前NV中保存的IMSI的内容的首地址

 调用函数  :
 被调函数  :

 修改历史      :
 1.日    期   : 2013年2月25日
   作    者   : w00167002
   修改内容   : 新生成函数

*****************************************************************************/
VOS_UINT8* NAS_MMC_GetLastImsi_SwitchOn(VOS_VOID)
{
    NAS_MMC_CONTEXT_STRU               *pstNasMmcCtx        = VOS_NULL_PTR;

    pstNasMmcCtx = NAS_MMC_GetMmcCtxAddr();

    /* 如果当前状态机不是NAS_MMC_FSM_SWITCH_ON */
    if (NAS_MMC_FSM_SWITCH_ON != NAS_MMC_GetCurrFsmId())
    {
        NAS_ERROR_LOG(WUEPS_PID_MMC, "NAS_MMC_GetLastImsi_SwitchOn,ERROR:FsmId Error");
    }

    /* 返回存储开机前NV中保存的IMSI的内容的首地址 */
    return pstNasMmcCtx->stCurFsm.unFsmCtx.stSwitchOnCtx.aucLastImsi;
}


/*****************************************************************************
 函 数 名  : NAS_MMC_InitFsmCtx_PowerOff
 功能描述  : 初始化关机状态机上下文
 输入参数  : 无
 输出参数  : 无
 返 回 值  :
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2011年5月7日
    作    者   : w00176964
    修改内容   : 新生成函数

  2.日    期   : 2012年8月17日
    作    者   : w00167002
    修改内容   : V7R1C50_GUTL_PhaseII: 初始化关机时当前的主模上下文
  3.日    期   : 2013年1月15日
    作    者   : s00217060
    修改内容   : for DSDA GUNAS C CORE: 初始化关机时的从模列表

*****************************************************************************/

VOS_VOID  NAS_MMC_InitFsmCtx_PowerOff(VOS_VOID)
{
    NAS_MML_PLMN_RAT_PRIO_STRU         *pstSlaveModeRatList = VOS_NULL_PTR;
    VOS_UINT32                          i;

    NAS_MMC_ClearAllMmPowerOffCnfFlag_PowerOff();
    NAS_MMC_ClearAllAsPowerOffCnfFlag_PowerOff();

    NAS_MMC_SetMasterModeRat_PowerOff( NAS_MML_NET_RAT_TYPE_BUTT );

    /* 初始化关机时的从模列表 */
    pstSlaveModeRatList           = NAS_MMC_GetSlaveModeRatList_PowerOff();
    pstSlaveModeRatList->ucRatNum = 0;
    for (i = 0; i < NAS_MML_MAX_RAT_NUM; i++)
    {
        pstSlaveModeRatList->aucRatPrio[i] = NAS_MML_NET_RAT_TYPE_BUTT;
    }
}

/*****************************************************************************
 函 数 名  : NAS_MMC_InitFsmCtx_PlmnSelection
 功能描述  : 初始化Plmn Selection状态机上下文
 输入参数  : 无
 输出参数  : 无
 返 回 值  :
 调用函数  :
 被调函数  :

 修改历史      :
 1.日    期   : 2011年5月7日
   作    者   : s46746
   修改内容   : 新生成函数

 2.日    期   : 2011年11月12日
   作    者   : w00167002
   修改内容   : DTS2011110907180:初始化选网状态机的禁止漫游LA

 3.日    期   : 2012年5月10日
   作    者   : l65478
   修改内容   : DTS2012050500988:NMO I时,PS注册失败#11,收到系统信息后又发起了注册
 4.日    期   : 2012年06月11日
   作    者   : s00217060
   修改内容   : For CS/PS mode 1，初始化需要重新驻留的LTE网络
 5.日    期   : 2012年8月10日
   作    者   : L00171473
   修改内容   : DTS2012082204471, TQE清理
 6.日    期   : 2013年8月5日
   作    者   : w00167002
   修改内容   : DTS2013073106748:开机手动模式G下搜24003 CS域注册成功，PS域
                注册失败17，在选网状态机，用户发起电话，切换到W下的46002网络上。
                电话挂断后，W上报丢网,选网状态机作ANYCELL搜网，没有搜原有的24003网络。
                修改为选网状态机等注册结果时候，如果收到HO切换成功后，则退出
                选网状态机,待电话结束后，再由L1 MAIN进入选网状态机。
                默认接入技术初始化为BUTT.
 7.日    期   :2013年8月21日
   作    者   :z00161729
   修改内容   :DTS2013081607507:开机搜网过程中后台多次下发at+cops=0，mmc判断非正常服务不停打断当前搜网重新搜网导致开机速度慢
 8.日    期   : 2014年11月8日
   作    者   : z00161729
   修改内容   : 开机搜网优化项目修改
 9.日    期   : 2015年5月23日
   作    者   : s00217060
   修改内容   : ROAM_PLMN_SELECTION_OPTIMIZE_2.0修改
*****************************************************************************/
VOS_VOID  NAS_MMC_InitFsmCtx_PlmnSelection(VOS_VOID)
{
    NAS_MMC_PLMN_SELECTION_LIST_INFO_STRU                  *pstPlmnSelectionListInfo = VOS_NULL_PTR;

    NAS_MML_FORBIDPLMN_ROAMING_LAS_INFO_STRU               *pstForbRoamLaInfo = VOS_NULL_PTR;

    NAS_MML_PLMN_WITH_RAT_STRU                              stInvalidPlmnId;

#if (FEATURE_ON == FEATURE_LTE)
    NAS_MML_PLMN_ID_STRU                                    stPlmnId;
#endif

    /* 设置Abort标志为VOS_FALSE */
    NAS_MMC_SetAbortFlag_PlmnSelection(VOS_FALSE);

    /* 设置Rel Request标志为VOS_FALSE */
    NAS_MMC_SetRelRequestFlag_PlmnSelection(VOS_FALSE);

    NAS_MMC_SetInterSysSuspendRat_PlmnSelection(NAS_MML_NET_RAT_TYPE_BUTT);

    /* 设置等待注册标志为NULL */
    NAS_MMC_ClearAllWaitRegRsltFlag_PlmnSelection();

    /* 设置CS注册结果触发的后续动作为BUTT */
    NAS_MMC_SetCsRegAdditionalAction_PlmnSelection(NAS_MMC_ADDITIONAL_ACTION_BUTT);

    /* 设置PS注册结果触发的后续动作为BUTT */
    NAS_MMC_SetPsRegAdditionalAction_PlmnSelection(NAS_MMC_ADDITIONAL_ACTION_BUTT);

    /* 初始化CS、PS cause值为BUTT */
    NAS_MMC_SetCsRegCause_PlmnSelection(NAS_MML_REG_FAIL_CAUSE_BUTT);
    NAS_MMC_SetPsRegCause_PlmnSelection(NAS_MML_REG_FAIL_CAUSE_BUTT);

    /* 初始化搜网列表 */
    pstPlmnSelectionListInfo = NAS_MMC_GetPlmnSelectionListInfo_PlmnSelection();


    PS_MEM_SET(pstPlmnSelectionListInfo, 0x0, sizeof(NAS_MMC_PLMN_SELECTION_LIST_INFO_STRU));

    /* 初始化搜网状态机上下文中不同接入技术的覆盖及搜索信息 */
    NAS_MMC_InitSearchRatInfo_PlmnSelection();

    pstForbRoamLaInfo = NAS_MMC_GetForbRoamLaInfo_PlmnSelection();
    PS_MEM_SET(pstForbRoamLaInfo, 0X0, sizeof(NAS_MML_FORBIDPLMN_ROAMING_LAS_INFO_STRU));

    PS_MEM_SET(NAS_MMC_GetForbPlmnForGrpsInfo_PlmnSelection(),
               0X0, sizeof(NAS_MML_PLMN_ID_STRU));

#if (FEATURE_ON == FEATURE_LTE)
    stPlmnId.ulMcc = NAS_MML_INVALID_MCC;
    stPlmnId.ulMnc = NAS_MML_INVALID_MNC;
    NAS_MMC_SetCsPsMode1ReCampLtePlmn_PlmnSelection(&stPlmnId);
#endif

    PS_MEM_SET(&stInvalidPlmnId, 0x0, sizeof(stInvalidPlmnId));
    stInvalidPlmnId.stPlmnId.ulMcc = NAS_MML_INVALID_MCC;
    stInvalidPlmnId.stPlmnId.ulMnc = NAS_MML_INVALID_MNC;
    stInvalidPlmnId.enRat          = NAS_MML_NET_RAT_TYPE_BUTT;

    NAS_MMC_SetCurrSearchingPlmn_PlmnSelection(&stInvalidPlmnId);

    NAS_MMC_SetCurrSearchingType_PlmnSelection(NAS_MMC_PLMN_SEARCH_TYPE_BUTT);

    NAS_MMC_SetExistRplmnOrHplmnFlag_PlmnSelection(VOS_FALSE);

    NAS_MMC_SetLmmAttachClRegStatus_PlmnSelection(MMC_LMM_CL_REG_STATUS_BUTT);

    return;
}

/*****************************************************************************
 函 数 名  : NAS_MMC_InitFsmCtx_AnyCellSearch
 功能描述  : 初始化ANYCELL搜网状态机上下文
 输入参数  : 无
 输出参数  : 无
 返 回 值  :
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2011年5月7日
    作    者   : w00176964
    修改内容   : 新生成函数
  2.日    期   : 2011年7月27日
    作    者   : L00171473
    修改内容   : V7R1 phase II 修改
*****************************************************************************/
VOS_VOID  NAS_MMC_InitFsmCtx_AnyCellSearch(VOS_VOID)
{
    NAS_MMC_FSM_ANYCELL_SEARCH_CTX_STRU                    *pstAnyCellSearchCtx = VOS_NULL_PTR;
    NAS_MML_PLMN_RAT_PRIO_STRU                             *pstRatPrioList      = VOS_NULL_PTR;
    VOS_UINT32                                              i;
    VOS_UINT8                                               ucRatNum;

    pstAnyCellSearchCtx = NAS_MMC_GetFsmCtxAddr_AnyCellSearch();

    /* 获取MS当前支持的接入技术 */
    pstRatPrioList     = NAS_MML_GetMsPrioRatList();

    /* 初始化ANYCELL状态机的接入技术为当前MS支持的接入技术 */
    g_stNasMmcCtx.stCurFsm.unFsmCtx.stAnyCellSearchCtx.stMmcPlmnRatPrio = (*pstRatPrioList);

    ucRatNum = NAS_MMC_GetRatNum_AnyCellSearch();

    /* 初始化接入技术为未搜索过 */
    for (i = 0; i < ucRatNum; i++)
    {
        pstAnyCellSearchCtx->aucSearchedFlag[i] = VOS_FALSE;
    }

    /* 设置Abort标志为VOS_FALSE */
    NAS_MMC_SetAbortFlag_AnyCellSearch(VOS_FALSE);

}

/*****************************************************************************
 函 数 名  : NAS_MMC_InitFsmCtx_BgPlmnSearch
 功能描述  : 初始化Bg Plmn Search状态机上下文
 输入参数  : 无
 输出参数  : 无
 返 回 值  :
 调用函数  :
 被调函数  :

 修改历史      :
 1.日    期   : 2011年9月21日
   作    者   : w00167002
   修改内容   : 新生成函数

 2.日    期   : 2011年11月29日
   作    者   : w00167002
   修改内容   : DTS2011112301233:初始化状态机上下文中的打断事件类型
 3.日    期   : 2012年6月25日
   作    者   : L60609
   修改内容   : AT&T&DCM:初始化是否需要发送系统消息的标志
 4.日    期   : 2014年5月28日
   作    者   : z00234330
   修改内容   : covertity修改
*****************************************************************************/
VOS_VOID  NAS_MMC_InitFsmCtx_BgPlmnSearch()
{
    NAS_MML_PLMN_ID_STRU                stInvalidPlmnId;
    NAS_MML_EQUPLMN_INFO_STRU           stEquPlmnInfo;

    stInvalidPlmnId.ulMcc = NAS_MML_INVALID_MCC;
    stInvalidPlmnId.ulMnc = NAS_MML_INVALID_MNC;

    /* modified by z00234330 for coverity修改 2014-05-28 begin */
    PS_MEM_SET(&stEquPlmnInfo, 0x00, sizeof(stEquPlmnInfo));
    /* modified by z00234330 for coverity修改 2014-05-28 begin */


    /* 记录状态机上下文中Abort事件类型0xFFFFFFFF */
    NAS_MMC_SetAbortEventType_BgPlmnSearch(NAS_MML_INVALID_EVENT_TYPE);

    /* 初始化ABORT标志为无打断 */
    NAS_MMC_SetAbortType_BgPlmnSearch(NAS_MMC_ABORT_BUTT);

    NAS_MMC_SetNeedSndSysInfo_BgPlmnSearch(VOS_FALSE);

#if (FEATURE_OFF == FEATURE_LTE)
    /* 初始化保留字段 */
    PS_MEM_SET(g_stNasMmcCtx.stCurFsm.unFsmCtx.stBgPlmnSearchCtx.aucReserve,
               0X00,
               sizeof(g_stNasMmcCtx.stCurFsm.unFsmCtx.stBgPlmnSearchCtx.aucReserve));
#endif

    /* 初始化RegInfo信息 */
    NAS_MMC_SetRelRequestFlag_BgPlmnSearch(VOS_FALSE);
    NAS_MMC_ClearAllWaitRegRsltFlag_BgPlmnSearch();
    NAS_MMC_SetCsRegAdditionalAction_BgPlmnSearch(NAS_MMC_ADDITIONAL_ACTION_BUTT);
    NAS_MMC_SetPsRegAdditionalAction_BgPlmnSearch(NAS_MMC_ADDITIONAL_ACTION_BUTT);

    /* 初始化当前正在尝试的高优先级网络及其接入技术信息 */
    NAS_MMC_SetCurHighPrioPlmn_BgPlmnSearch(&stInvalidPlmnId, NAS_MML_NET_RAT_TYPE_BUTT);

    /* 初始化VPlmn信息 */
    NAS_MMC_SetPreCampPlmn_BgPlmnSearch(&stInvalidPlmnId, NAS_MML_NET_RAT_TYPE_BUTT);

    /* 初始化EPlmn信息 */
    NAS_MML_InitEquPlmnInfo(&stEquPlmnInfo);
    NAS_MMC_SetPreEquPlmnInfo_BgPlmnSearch(&stInvalidPlmnId, &stEquPlmnInfo);

    /* Added by w00176964 for coverity清理, 2014-3-10, begin */
#if (FEATURE_ON == FEATURE_LTE)
    NAS_MMC_SetPreLteDisableFlg_BgPlmnSearch(VOS_FALSE);
    NAS_MMC_SetNeedEnableLteFlg_BgPlmnSearch(VOS_FALSE);
#endif
    /* Added by w00176964 for coverity清理, 2014-3-10, end */
}

/*****************************************************************************
 函 数 名  : NAS_MMC_InitFsmCtx_InterSysCellResel
 功能描述  : 初始化异系统重选状态机上下文
 输入参数  : 无
 输出参数  : 无
 返 回 值  :
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2011年5月7日
    作    者   : w00176964
    修改内容   : 新生成函数
  2.日    期   : 2012年11月16日
    作    者   : s00217060
    修改内容   : DTS2012082007133：Abort标志初始化

  3.日    期   : 2014年2月26日
    作    者   : w00167002
    修改内容   : L-C互操作项目:UT检测没有初始化
*****************************************************************************/

VOS_VOID  NAS_MMC_InitFsmCtx_InterSysCellResel(VOS_VOID)
{
    NAS_MMC_ClearAllSuspendRspFlag_InterSysCellResel();
    NAS_MMC_ClearAllResumeRspFlag_InterSysCellResel();
    NAS_MMC_SetAbortFlag_InterSysCellResel(VOS_FALSE);
    NAS_MMC_SetSndSuspendRelReqFlg_InterSysCellResel(VOS_FALSE);

    /* Added by w00167002 for L-C互操作项目, 2014-2-26, begin */
    NAS_MMC_SetResumeOrign_InterSysCellResel(MMC_RESUME_ORIGEN_BUTT);
    /* Added by w00167002 for L-C互操作项目, 2014-2-26, end */
}


/*****************************************************************************
 函 数 名  : NAS_MMC_InitFsmCtx_InterSysHo
 功能描述  : 初始化异系统切换状态机上下文
 输入参数  : 无
 输出参数  : 无
 返 回 值  :
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2011年7月11日
    作    者   : w00176964
    修改内容   : 新生成函数

*****************************************************************************/

VOS_VOID  NAS_MMC_InitFsmCtx_InterSysHo(VOS_VOID)
{
    NAS_MMC_ClearAllSuspendRspFlag_InterSysHo();
    NAS_MMC_ClearAllResumeRspFlag_InterSysHo();

    NAS_MMC_SetCsSigExistFlag_InterSysHo(VOS_FALSE);
    NAS_MMC_SetPsSigExistFlag_InterSysHo(VOS_FALSE);
}


/*****************************************************************************
 函 数 名  : NAS_MMC_InitFsmCtx_InterSysCco
 功能描述  : 初始化异系统COO状态机上下文
 输入参数  : 无
 输出参数  : 无
 返 回 值  :
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2011年7月11日
    作    者   : w00176964
    修改内容   : 新生成函数

*****************************************************************************/

VOS_VOID  NAS_MMC_InitFsmCtx_InterSysCco(VOS_VOID)
{
    NAS_MMC_ClearAllSuspendRspFlag_InterSysCco();
    NAS_MMC_ClearAllResumeRspFlag_InterSysCco();
}


/*****************************************************************************
 函 数 名  : NAS_MMC_InitFsmCtx_InterSysOos
 功能描述  : 初始化异系统OOS状态机上下文
 输入参数  : 无
 输出参数  : 无
 返 回 值  :
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2011年7月11日
    作    者   : w00176964
    修改内容   : 新生成函数

*****************************************************************************/

VOS_VOID  NAS_MMC_InitFsmCtx_InterSysOos(VOS_VOID)
{
    NAS_MMC_ClearAllSuspendRspFlag_InterSysOos();
    NAS_MMC_ClearAllResumeRspFlag_InterSysOos();
}

/*****************************************************************************
 函 数 名  : NAS_MMC_InitFsmCtx_PlmnList
 功能描述  : 初始化PLMN LIST状态机上下文
 输入参数  : 无
 输出参数  : 无
 返 回 值  :
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2011年9月19日
    作    者   : w00176964
    修改内容   : 新生成函数
  2.日    期   : 2012年5月8日
    作    者   : t00212959
    修改内容   : GUL BG项目调整
  3.日    期   : 2015年9月30日
    作    者   : z00161729
    修改内容   : 支持LTE CSG功能新增
*****************************************************************************/

VOS_VOID  NAS_MMC_InitFsmCtx_PlmnList(VOS_VOID)
{
    /* 初始化搜索的接入技术信息*/
    NAS_MMC_InitSearchRatInfo_PlmnList();

    /* 设置状态机退出标记 */
    NAS_MMC_SetAbortFlag_PlmnList(VOS_FALSE);

    /* 设置通知MSCC标记为假 */
    NAS_MMC_SetNotifyMsccFlag_PlmnList(VOS_FALSE);

    /* 初始化所搜到的各个网络信息 */
    NAS_MMC_InitSearchedPlmnListInfo_PlmnList();

    /* 清除等待所有域的标记信息 */
    NAS_MMC_ClearAllWaitRegRsltFlag_PlmnList();

    /* 清除CS/PS的addition值 */
    NAS_MMC_SetCsRegAdditionalAction_PlmnList(NAS_MMC_ADDITIONAL_ACTION_BUTT);

    NAS_MMC_SetPsRegAdditionalAction_PlmnList(NAS_MMC_ADDITIONAL_ACTION_BUTT);

#if (FEATURE_ON == FEATURE_LTE)
    /* 保存当前L disable状态到状态机上下文 */
    NAS_MMC_SetPreLteDisableFlg_PlmnList(VOS_FALSE);
#endif

    /* 设置anycell搜网标记 */
    NAS_MMC_SetAnyCellSrchFlg_PlmnList(VOS_FALSE);

#if (FEATURE_ON == FEATURE_CSG)
    /* 初始化CSG搜索到的CSG ID结果列表信息 */
    NAS_MMC_InitCsgSearchedPlmnListInfo_PlmnList();
#endif

}


/*****************************************************************************
 函 数 名  : NAS_MMC_InitFsmCtx_GetGeo
 功能描述  : 初始化GetGeo状态机上下文
 输入参数  : 无
 输出参数  : 无
 返 回 值  :
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2015年05月08日
    作    者   : sunjitan 00193151
    修改内容   : 新生成函数

*****************************************************************************/
VOS_VOID  NAS_MMC_InitFsmCtx_GetGeo(VOS_VOID)
{
    VOS_UINT32                          i;
    NAS_MMC_FSM_GET_GEO_CTX_STRU       *pstGetGeoCtx = VOS_NULL_PTR;

    pstGetGeoCtx    = NAS_MMC_GetFsmCtxAddr_GetGeo();

    /* 状态机变量在这里初始化 */
    PS_MEM_SET(pstGetGeoCtx, 0, sizeof(NAS_MMC_FSM_GET_GEO_CTX_STRU));

    /* 设置状态机ABORT标识为无效 */
    NAS_MMC_SetAbortFlag_GetGeo(VOS_FALSE);

    /* 设置通知MSCC回复标记为无效 */
    NAS_MMC_SetNotifyMsccFlag_GetGeo(VOS_FALSE);

    /* 设置状态机任务阶段为BUTT */
    NAS_MMC_SetFsmTaskPhase_GetGeo(NAS_MMC_GET_GEO_FSM_TASK_PHASE_BUTT);

    /* 初始化GET GEO接入技术优先级列表 */
    pstGetGeoCtx->stGetGeoRatInfoList.ucRatNum = 0;
    for (i = 0; i < NAS_MML_MAX_RAT_NUM; i++)
    {
        pstGetGeoCtx->stGetGeoRatInfoList.astGetGeoRatInfo[i].enRatType      = NAS_MML_NET_RAT_TYPE_BUTT;
        pstGetGeoCtx->stGetGeoRatInfoList.astGetGeoRatInfo[i].enCoverageType = NAS_MMC_COVERAGE_TYPE_BUTT;
        pstGetGeoCtx->stGetGeoRatInfoList.astGetGeoRatInfo[i].ucIsSrchedFlag = VOS_FALSE;
    }

    return;
}




/*****************************************************************************
 函 数 名  : NAS_MMC_InitPlmnSearchCtrlCtx
 功能描述  : 初始化PLMN搜索控制块上下文
 输入参数  : enInitType:初始化类型,初始化或软关机
 输出参数  : pstPlmnSearchCtrl:搜网控制上下文
 返 回 值  :
 调用函数  :
 被调函数  :

 修改历史      :
 1.日    期   : 2011年6月30日
   作    者   : zhoujun 40661
   修改内容   : 新生成函数
 2.日    期   : 2011年10月17日
   作    者   : s46746
   修改内容   : 高优先级状态机代码检视意见修改,修改接入层驻留变量名,增加NAS是否搜网状态

 3.日    期   : 2011年11月17日
   作    者   : w00167002
   修改内容   : DTS2011111603447:进行缓存的搜网的初始化处理
 4.日    期   : 2011年12月24日
   作    者   : w00166186
   修改内容   : DTS2011122204051:手动模式开机驻留在ACC BAR的小区，重选到等效PLMN不发起注册
 5.日    期   : 2012年2月9日
   作    者   : l00130025
   修改内容   : DTS2012020604181:重新上下电，手动模式开机驻留在ACC BAR的小区，
                重选到等效PLMN不发起注册,因为开机时Rplmn和Eplmn已做过比较处理，修改默认值为VOS_TRUE
 6.日    期   : 2013年11月23日
   作    者   : z00161729
   修改内容    : SVLTE优化G-TL ps切换性能修改
 7.日    期   : 2013年12月24日
   作    者   : z00161729
   修改内容   : SVLTE支持NCELL搜网
 8.日    期   : 2014年1月26日
   作    者   : z00161729
   修改内容   : DTS2014012305088：支持增强NCELL搜网，如果Modem1传递过来的邻区信息不存在的情况下，通过历史频点支持NCELL搜索。
 9.日    期   : 2013年4月4日
   作    者   : y00176023
   修改内容   : DSDS GUNAS II项目:更改NO RF 相关变量名称
 10.日    期   : 2014年2月22日
   作    者   : w00167002
   修改内容   : 开机初始化为MMC控制
 11.日    期   : 2014年6月13日
    作    者   : w00167002
    修改内容   : 初始化通知MSCC当前NO RF的状态
 12.日    期   : 2014年6月24日
    作    者   : z00161729
    修改内容   : DSDS III新增
 13.日    期   : 2014年12月29日
    作    者   : z00161729
    修改内容   : DSDS业务重拨时no rf未触发搜网导致业务失败，mm在no cell available状态no rf时给mmc发送cm service ind触发搜网
 14.日    期   : 2014年11月4日
    作    者   : z00161729
    修改内容   : 开机漫游搜网项目修改
 15.日    期   : 2015年1月6日
    作    者   : z00161729
    修改内容   : AT&T 支持DAM特性修改
 16.日    期   : 2015年9月17日
    作    者   : y00346957
    修改内容   : DTS2015070910885 修改
 17.日    期   : 2015年11月2日
    作    者   : l00289540
    修改内容   : ROAM_PLMN_SELECTION_OPTIMIZE_3.0 修改
*****************************************************************************/
VOS_VOID  NAS_MMC_InitPlmnSearchCtrlCtx(
    NAS_MMC_INIT_CTX_TYPE_ENUM_UINT8     enInitType,
    NAS_MMC_PLMN_SEARCH_CTRL_CTX_STRU   *pstPlmnSearchCtrl
)
{
    pstPlmnSearchCtrl->ucWrrLimitServiceInd             = VOS_FALSE;
    pstPlmnSearchCtrl->stUserSpecPlmnId.enRat           = NAS_MML_NET_RAT_TYPE_BUTT;

    if ( NAS_MMC_INIT_CTX_STARTUP  == enInitType )
    {
        pstPlmnSearchCtrl->enSelectionMode                  = NAS_MMC_PLMN_SELECTION_MODE_AUTO;
        pstPlmnSearchCtrl->stUserSpecPlmnId.stPlmnId.ulMcc  = NAS_MML_INVALID_MCC;
        pstPlmnSearchCtrl->stUserSpecPlmnId.stPlmnId.ulMnc  = NAS_MML_INVALID_MNC;

        pstPlmnSearchCtrl->ucUserSpecPlmnRegStatus          = VOS_TRUE;
    }

    pstPlmnSearchCtrl->stUserReselPlmnId.enRat          = NAS_MML_NET_RAT_TYPE_BUTT;
    pstPlmnSearchCtrl->stUserReselPlmnId.stPlmnId.ulMcc = NAS_MML_INVALID_MCC;
    pstPlmnSearchCtrl->stUserReselPlmnId.stPlmnId.ulMnc = NAS_MML_INVALID_MNC;

    pstPlmnSearchCtrl->stBufferedPlmnSearchInfo.ulPlmnSearchFlg   = VOS_FALSE;
    pstPlmnSearchCtrl->stBufferedPlmnSearchInfo.enPlmnSearchScene = NAS_MMC_PLMN_SEARCH_SCENE_BUTT;

    pstPlmnSearchCtrl->enAsCellCampOn                   = NAS_MMC_AS_CELL_NOT_CAMP_ON;
    pstPlmnSearchCtrl->enSpecPlmnSearchState            = NAS_MMC_SPEC_PLMN_SEARCH_STOP;

    NAS_MMC_SetUtranSkipWPlmnSearchFlag(VOS_FALSE);
    pstPlmnSearchCtrl->stOtherModemPlmnId.ulMcc = NAS_MML_INVALID_MCC;
    pstPlmnSearchCtrl->stOtherModemPlmnId.ulMnc = NAS_MML_INVALID_MNC;

    /* 默认不支持ncell搜网 */
    NAS_MMC_SetNcellSearchFirstTimerLen(0);
    NAS_MMC_SetNcellSearchSecondTimerLen(0);


    NAS_MMC_SetNcellSearchFlag(VOS_FALSE);
    NAS_MML_InitEquPlmnInfo(&pstPlmnSearchCtrl->stNcellSearchInfo.stOtherModemEplmnInfo);
    PS_MEM_SET(&pstPlmnSearchCtrl->stNcellSearchInfo.stTdsNcellInfo, 0,
               sizeof(pstPlmnSearchCtrl->stNcellSearchInfo.stTdsNcellInfo));
    PS_MEM_SET(&pstPlmnSearchCtrl->stNcellSearchInfo.stLteNcellInfo, 0,
               sizeof(pstPlmnSearchCtrl->stNcellSearchInfo.stLteNcellInfo));


    /* Added by w00167002 for L-C互操作项目, 2014-2-22, begin */
    NAS_MMC_SetRegCtrl(NAS_MMC_REG_CONTROL_BY_3GPP_MMC);

    NAS_MMC_SetAsAnyCampOn(VOS_FALSE);
    /* Added by w00167002 for L-C互操作项目, 2014-2-22, end */

    NAS_MMC_InitUserDPlmnNPlmnInfo(&pstPlmnSearchCtrl->stDplmnNplmnCtx);

    NAS_MMC_SetEnableLteTimerExpireFlag(VOS_FALSE);
    NAS_MMC_ClearDisabledLtePlmnId();

    NAS_MMC_SetRoamPlmnSelectionSortActiveFlg(VOS_FALSE);

    NAS_MMC_SetSrchUOplmnPriorToDplmnFlg(VOS_FALSE);
    NAS_MMC_InitNonOosPlmnSearchFeatureSupportCfg(&pstPlmnSearchCtrl->stNonOosPlmnSearchFeatureSupportCfg);
    NAS_MMC_InitOosSearchStrategyInfo(&pstPlmnSearchCtrl->stOosPlmnSearchStrategyInfo);

    NAS_MMC_InitGetGeoInfo(&pstPlmnSearchCtrl->stGetGeoInfo);

#if (FEATURE_ON == FEATURE_UE_MODE_CDMA)
    pstPlmnSearchCtrl->stCLAssociatedInfoNtf.ucAllowSrchLteFlg         = VOS_TRUE;
    pstPlmnSearchCtrl->stCLAssociatedInfoNtf.enLteSysPriClass          = NAS_MSCC_PIF_PLMN_PRIORITY_ANY;
#endif
}

/*****************************************************************************
 函 数 名  : NAS_MMC_InitServiceInfo
 功能描述  : 初始化MMC的服务状态信息
 输入参数  : 无
 输出参数  : pstServiceInfo:服务参数
 返 回 值  :
 调用函数  :
 被调函数  :

 修改历史      :
 1.日    期   : 2011年10月13日
   作    者   : zhoujun 40661
   修改内容   : 新生成函数

*****************************************************************************/
VOS_VOID  NAS_MMC_InitServiceInfo(
    NAS_MMC_SERVICE_INFO_CTX_STRU       *pstServiceInfo
)
{
    pstServiceInfo->enCsCurrService = NAS_MMC_NO_SERVICE;
    pstServiceInfo->enPsCurrService = NAS_MMC_NO_SERVICE;
}

/*****************************************************************************
 函 数 名  : NAS_MMC_InitMaintainCtx
 功能描述  : 初始化MMC可维可测上下文
 输入参数  : pstMaintainInfo:可维可测信息
 输出参数  : 无
 返 回 值  :
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2011年6月30日
    作    者   : zhoujun 40661
    修改内容   : 新生成函数
  2.日    期   : 2011年7月26日
    作    者   : w00176964
    修改内容   : 新生成函数
  3.日    期   : 2012年4月24日
    作    者   : l00171473
    修改内容   : DTS2012041805606
  4.日    期   : 2012年11月21日
    作    者   : z00161729
    修改内容   : 支持cerssi和nmr
*****************************************************************************/
VOS_VOID  NAS_MMC_InitMaintainCtx(
    NAS_MMC_MAINTAIN_CTX_STRU           *pstMaintainInfo
)
{
    pstMaintainInfo->ucGcfCh9_4_3_AND_Ch26_7_4_3    = VOS_FALSE;

    pstMaintainInfo->ucActionType                   = NAS_MMC_AT_ACTION_TYPE_START_FOREVER;
    pstMaintainInfo->ucMsgType                      = NAS_MMC_AT_MSG_TYPE_CELL_SIGN;
    pstMaintainInfo->ucMsgType                     |= NAS_MMC_AT_MSG_TYPE_CELL_ID;
    pstMaintainInfo->ucMsgType                     |= NAS_MMC_AT_MSG_TYPE_CELL_BLER;


    pstMaintainInfo->ucSignThreshold       = 0;   /* 默认接入层取缺省值*/

    pstMaintainInfo->ucMinRptTimerInterval = 0; /*默认间隔时间*/
}


/*****************************************************************************
 函 数 名  : NAS_MMC_InitPlmnRegRejCtx
 功能描述  : 初始化PLMN注册被拒信息上下文
 输入参数  : 无
 输出参数  : pstPlmnRegRejInfo:注册被拒信息上下文
 返 回 值  :
 调用函数  :
 被调函数  :

 修改历史      :
 1.日    期   : 2011年6月30日
   作    者   : zhoujun 40661
   修改内容   : 新生成函数
 2.日    期   : 2011年12月5日
   作    者   : z00161729
   修改内容   : V7R1 phaseIV修改合并原NAS_MMC_HPLMN_REG_REJ_STRU和NAS_MMC_PLMN_REG_INFO_STRU

*****************************************************************************/
VOS_VOID  NAS_MMC_InitPlmnRegRejCtx(
    NAS_MMC_PLMN_REG_REJ_CTX_STRU          *pstPlmnRegRejInfo
)
{
    VOS_UINT32                          i;

    pstPlmnRegRejInfo->ucPlmnRegInfoNum     = 0;

    for ( i = 0 ; i < NAS_MMC_MAX_REG_PLMN_INFO_NUM ; i++ )
    {
        pstPlmnRegRejInfo->astPlmnRegInfoList[i].stPlmnId.ulMcc = NAS_MML_INVALID_MCC;
        pstPlmnRegRejInfo->astPlmnRegInfoList[i].stPlmnId.ulMnc = NAS_MML_INVALID_MNC;
        pstPlmnRegRejInfo->astPlmnRegInfoList[i].enGCsRegStatus = NAS_MML_REG_FAIL_CAUSE_NULL;
        pstPlmnRegRejInfo->astPlmnRegInfoList[i].enGPsRegStatus = NAS_MML_REG_FAIL_CAUSE_NULL;
        pstPlmnRegRejInfo->astPlmnRegInfoList[i].enWPsRegStatus = NAS_MML_REG_FAIL_CAUSE_NULL;
        pstPlmnRegRejInfo->astPlmnRegInfoList[i].enWCsRegStatus = NAS_MML_REG_FAIL_CAUSE_NULL;
#if (FEATURE_ON == FEATURE_LTE)
        pstPlmnRegRejInfo->astPlmnRegInfoList[i].enLCsRegStatus = NAS_MML_REG_FAIL_CAUSE_NULL;
        pstPlmnRegRejInfo->astPlmnRegInfoList[i].enLPsRegStatus = NAS_MML_REG_FAIL_CAUSE_NULL;
#endif

    }
}


/*****************************************************************************
 函 数 名  : NAS_MMC_InitCurrFsmCtx
 功能描述  : 初始化当前状态机上下文
 输入参数  : 无
 输出参数  : pstCurrFsmCtx:当前状态机上下文信息
 返 回 值  :
 调用函数  :
 被调函数  :

 修改历史      :
 1.日    期   : 2011年6月30日
   作    者   : zhoujun 40661
   修改内容   : 新生成函数
 2.日    期   : 2014年1月2日
   作    者   : z00161729
   修改内容   : SVLTE支持NCELL搜网
 3.日    期   : 2014年2月24日
   作    者   : w00176964
   修改内容   : High_Rat_Hplmn_Search特性调整
 4.日    期   : 2014年4月22日
   作    者   : w00167002
   修改内容   : 初始化AVAILABLE的类型，否则初始化为NAS_MMC_AVAILABLE_TIMER_TYPE_NCELL
 5.日    期   : 2015年6月6日
   作    者   : s00217060
   修改内容   : ROAM_PLMN_SELECTION_OPTIMIZE_2.0修改
*****************************************************************************/
VOS_VOID  NAS_MMC_InitCurrFsmCtx(
    NAS_MMC_FSM_CTX_STRU                *pstCurrFsmCtx
)
{
    pstCurrFsmCtx->enFsmId                  =   NAS_MMC_FSM_L1_MAIN;
    pstCurrFsmCtx->pstFsmDesc               =   NAS_MMC_GetMainFsmDescAddr();
    pstCurrFsmCtx->ulState                  =   NAS_MMC_L1_STA_NULL;
    pstCurrFsmCtx->stEntryMsg.ulEventType   =   0;
    pstCurrFsmCtx->enParentFsmId            =   NAS_FSM_BUTT;
    pstCurrFsmCtx->ulParentEventType        =   0;


    /* 默认AVAILABLE COUNTER为NORMAL类型 */
    NAS_MMC_SetAvailableTimerType_OnPlmn(NAS_MMC_AVAILABLE_TIMER_TYPE_NORMAL);

    NAS_MMC_SetCsRegAdditionalAction_L1Main(NAS_MMC_ADDITIONAL_ACTION_BUTT);
    NAS_MMC_SetPsRegAdditionalAction_L1Main(NAS_MMC_ADDITIONAL_ACTION_BUTT);

    NAS_MMC_SetCLRegAdditionalAction_L1Main(NAS_MMC_CL_ADDITIONAL_ACTION_BUTT);

    NAS_MMC_ResetOosPlmnSearchTimerCount_OnPlmn();

    NAS_MMC_ResetCurHighPrioRatHplmnTimerFirstSearchCount_L1Main();

    PS_MEM_SET(pstCurrFsmCtx->stEntryMsg.aucEntryMsgBuffer,
               0x00,
               NAS_MMC_MAX_MSG_BUFFER_LEN);
}

/*****************************************************************************
 函 数 名  : NAS_MMC_InitFsmStackCtx
 功能描述  : 初始化状态机栈上下文
 输入参数  : 无
 输出参数  : pstFsmStack:状态机栈信息
 返 回 值  :
 调用函数  :
 被调函数  :

 修改历史      :
 1.日    期   : 2011年6月30日
   作    者   : zhoujun 40661
   修改内容   : 新生成函数

 2.日    期   : 2011年10月9日
   作    者   : zhoujun /40661
   修改内容   : 增加栈pop标志初始化
*****************************************************************************/
VOS_VOID  NAS_MMC_InitFsmStackCtx(
    NAS_MMC_FSM_STACK_STRU              *pstFsmStack
)
{
    VOS_UINT32                          i;

    pstFsmStack->usStackDepth   = 0;
    pstFsmStack->usStackPopFlg  = VOS_FALSE;

    for ( i = 0 ; i < NAS_MMC_MAX_STACK_DEPTH ; i++ )
    {
        pstFsmStack->astFsmStack[i].pstFsmDesc  = VOS_NULL_PTR;
        pstFsmStack->astFsmStack[i].enFsmId     = NAS_FSM_BUTT;
        pstFsmStack->astFsmStack[i].ulState     = NAS_MMC_L1_STA_BUTT;
    }
}

/*****************************************************************************
 函 数 名  : NAS_MMC_InitInternalBuffer
 功能描述  : 清除内部缓存消息
 输入参数  : 无
 输出参数  : 无
 返 回 值  :
 调用函数  :
 被调函数  :

 修改历史      :
 1.日    期   : 2011年9月15日
   作    者   : zhoujun 40661
   修改内容   : 新生成函数

*****************************************************************************/
VOS_VOID  NAS_MMC_InitInternalBuffer(
    NAS_MMC_MSG_QUEUE_STRU             *pstBufferEntryMsgQueue
)
{
    pstBufferEntryMsgQueue->ucCacheMsgNum   = 0;
    pstBufferEntryMsgQueue->ucCurrIndex     = 0;
    PS_MEM_SET(pstBufferEntryMsgQueue->astMsgQueue,
               0x00,
               sizeof(pstBufferEntryMsgQueue->astMsgQueue));
}

/*****************************************************************************
 函 数 名  : NAS_MMC_InitHighPrioPlmnSearchCtx
 功能描述  : 初始化NETSCAN请求上下文
 输入参数  : NETSCAN请求上下文指针
 输出参数  : 无
 返 回 值  : 无
 调用函数  :
 被调函数  :

 修改历史      :
 1.日    期   : 2013年10月29日
   作    者   : w00167002
   修改内容   : 新生成函数

*****************************************************************************/
VOS_VOID NAS_MMC_InitNetScanReqCtx(
    NAS_MMC_NET_SCAN_REQ_CTX_STRU      *pstNetScanReqCtx
)
{
    PS_MEM_SET( &(pstNetScanReqCtx->stNetScanReq), 0X00, sizeof(MSCC_MMC_NET_SCAN_REQ_STRU) );

    pstNetScanReqCtx->stNetScanReq.ucRat = NAS_MML_NET_RAT_TYPE_BUTT;

    return;
}


/*****************************************************************************
 函 数 名  : NAS_MMC_GetCurrEntryMsg
 功能描述  : 获取当前状态机的入口消息
 输入参数  : 无
 输出参数  : 无
 返 回 值  : 当前状态机的入口消息
 调用函数  :
 被调函数  :
 修改历史      :
 1.日    期   : 2011-07-11
   作    者   : z40661
   修改内容   : 新生成函数
*****************************************************************************/
NAS_MMC_ENTRY_MSG_STRU* NAS_MMC_GetCurrEntryMsg(VOS_VOID)
{
    return &(NAS_MMC_GetMmcCtxAddr()->stCurFsm.stEntryMsg);
}


/*****************************************************************************
 函 数 名  : NAS_MMC_GetPlmnSearchCtrl
 功能描述  : 获取当前PLMN搜网控制上下文
 输入参数  : 无
 输出参数  : 无
 返 回 值  : PLMN搜网控制上下文
 调用函数  :
 被调函数  :
 修改历史      :
 1.日    期   : 2011-07-11
   作    者   : z40661
   修改内容   : 新生成函数
*****************************************************************************/
NAS_MMC_PLMN_SEARCH_CTRL_CTX_STRU *NAS_MMC_GetPlmnSearchCtrl(VOS_VOID)
{
    return &(NAS_MMC_GetMmcCtxAddr()->stPlmnSearchCtrl);
}

/*****************************************************************************
 函 数 名  : NAS_MMC_GetPlmnSelectionMode
 功能描述  : 获取当前PLMN搜网模式
 输入参数  : 无
 输出参数  : 无
 返 回 值  : PLMN搜网模式
 调用函数  :
 被调函数  :
 修改历史      :
 1.日    期   : 2011-07-11
   作    者   : z40661
   修改内容   : 新生成函数
*****************************************************************************/
NAS_MMC_PLMN_SELECTION_MODE_ENUM_UINT8 NAS_MMC_GetPlmnSelectionMode(VOS_VOID)
{
    /* CL模式下无条件返回自动搜网 */
#if (FEATURE_ON == FEATURE_UE_MODE_CDMA)
    if (VOS_FALSE == NAS_MML_IsGULModeConfigured())
    {
        return NAS_MMC_PLMN_SELECTION_MODE_AUTO;
    }
#endif

    return (NAS_MMC_GetMmcCtxAddr()->stPlmnSearchCtrl.enSelectionMode);
}

/*****************************************************************************
 函 数 名  : NAS_MMC_GetUtranSkipWPlmnSearchFlag
 功能描述  : 获取UTRAN搜网状态机在搜T/W状态有副卡gsm中国区信息的前提下，是否需要跳过w搜索的标识
 输入参数  : 无
 输出参数  : 无
 返 回 值  : VOS_TRUE:不搜w;VOS_FALSE:搜w
 调用函数  :
 被调函数  :
 修改历史      :
 1.日    期   : 2013年11月23日
   作    者   : z00161729
   修改内容   : SVLTE优化G-TL ps切换性能修改
*****************************************************************************/
VOS_UINT8 NAS_MMC_GetUtranSkipWPlmnSearchFlag(VOS_VOID)
{
    return (NAS_MMC_GetMmcCtxAddr()->stPlmnSearchCtrl.stDsdaPlmnSearchEnhancedCfg.ucUtranSkipWPlmnSearchFlag);
}

/*****************************************************************************
 函 数 名  : NAS_MMC_GetOtherModemPlmnId
 功能描述  : 获取副卡驻留plmn id
 输入参数  : 无
 输出参数  : 无
 返 回 值  : 副卡驻留plmn id
 调用函数  :
 被调函数  :
 修改历史      :
 1.日    期   : 2013年11月25日
   作    者   : z00161729
   修改内容   : SVLTE优化G-TL ps切换性能修改
*****************************************************************************/
NAS_MML_PLMN_ID_STRU* NAS_MMC_GetOtherModemPlmnId(VOS_VOID)
{
    return &(NAS_MMC_GetMmcCtxAddr()->stPlmnSearchCtrl.stOtherModemPlmnId);
}

/*****************************************************************************
 函 数 名  : NAS_MMC_SetOtherModemPlmnId
 功能描述  : 设置副卡驻留plmn id
 输入参数  : pstPlmnId - plmn id
 输出参数  : 无
 返 回 值  : 无
 调用函数  :
 被调函数  :
 修改历史      :
 1.日    期   : 2013年11月25日
   作    者   : z00161729
   修改内容   : SVLTE优化G-TL ps切换性能修改
*****************************************************************************/
VOS_VOID NAS_MMC_SetOtherModemPlmnId(NAS_MML_PLMN_ID_STRU *pstPlmnId)
{
    NAS_MMC_GetMmcCtxAddr()->stPlmnSearchCtrl.stOtherModemPlmnId = *pstPlmnId;

}


/*****************************************************************************
 函 数 名  : NAS_MMC_SetUtranSkipWPlmnSearchFlag
 功能描述  : 设置UTRAN搜网状态机在搜T/W状态有副卡gsm中国区信息的前提下，是否需要跳过w搜索的标识
 输入参数  : ucUtranSkipWPlmnSearchFlag - UTRAN搜网状态机在搜T/W状态有副卡gsm中国区信息的前提下是否需要跳过w搜索的标识
 输出参数  : 无
 返 回 值  : 无
 调用函数  :
 被调函数  :
 修改历史      :
 1.日    期   : 2013年11月23日
   作    者   : z00161729
   修改内容    :SVLTE优化G-TL ps切换性能修改
*****************************************************************************/
VOS_VOID NAS_MMC_SetUtranSkipWPlmnSearchFlag(VOS_UINT8 ucUtranSkipWPlmnSearchFlag)
{
    NAS_MMC_GetMmcCtxAddr()->stPlmnSearchCtrl.stDsdaPlmnSearchEnhancedCfg.ucUtranSkipWPlmnSearchFlag = ucUtranSkipWPlmnSearchFlag;
}


/*****************************************************************************
 函 数 名  : NAS_MMC_GetNcellSearchInfo
 功能描述  : 获取ncell搜网相关信息
 输入参数  : 无
 输出参数  : 无
 返 回 值  : ncell搜网相关信息
 调用函数  :
 被调函数  :
 修改历史      :
 1.日    期   : 2013年12月24日
   作    者   : z00161729
   修改内容   : SVLTE支持NCELL搜网

*****************************************************************************/
NAS_MMC_NCELL_SEARCH_INFO_STRU* NAS_MMC_GetNcellSearchInfo(VOS_VOID)
{
    return &(NAS_MMC_GetMmcCtxAddr()->stPlmnSearchCtrl.stNcellSearchInfo);
}


/*****************************************************************************
 函 数 名  : NAS_MMC_GetNcellSearchFlag
 功能描述  : 获取是否支持ncell搜网标识
 输入参数  : 无
 输出参数  : 无
 返 回 值  : VOS_TRUE:支持;VOS_FALSE:不支持
 调用函数  :
 被调函数  :
 修改历史      :
 1.日    期   : 2013年12月24日
   作    者   : z00161729
   修改内容   : SVLTE支持NCELL搜网
*****************************************************************************/
VOS_UINT8 NAS_MMC_GetNcellSearchFlag(VOS_VOID)
{
    return (NAS_MMC_GetMmcCtxAddr()->stPlmnSearchCtrl.stDsdaPlmnSearchEnhancedCfg.ucNcellSearchFlag);
}

/*****************************************************************************
 函 数 名  : NAS_MMC_SetNcellSearchFlag
 功能描述  : 设置是否支持ncell搜网标识
 输入参数  : ucNcellSearchFlag - 是否支持ncell搜网标识
 输出参数  : 无
 返 回 值  : 无
 调用函数  :
 被调函数  :
 修改历史      :
 1.日    期   : 2013年12月24日
   作    者   : z00161729
   修改内容   : SVLTE支持NCELL搜网
*****************************************************************************/
VOS_VOID NAS_MMC_SetNcellSearchFlag(VOS_UINT8 ucNcellSearchFlag)
{
    NAS_MMC_GetMmcCtxAddr()->stPlmnSearchCtrl.stDsdaPlmnSearchEnhancedCfg.ucNcellSearchFlag = ucNcellSearchFlag;
}

/*****************************************************************************
 函 数 名  : NAS_MMC_GetNcellSearchFirstTimerLen
 功能描述  : 获取第一阶段邻区频点快速搜索策略的时间间隔
 输入参数  : 无
 输出参数  : 无
 返 回 值  : 时间间隔
 调用函数  :
 被调函数  :
 修改历史      :
 1.日    期   : 2013年12月24日
   作    者   : z00161729
   修改内容   : SVLTE支持NCELL搜网
 2.日    期   : 2014年1月26日
   作    者   : z00161729
   修改内容   : DTS2014012305088:支持增强NCELL搜网，如果Modem1传递过来的邻区信息不存在的情况下，通过历史频点支持NCELL搜索。
*****************************************************************************/
VOS_UINT8 NAS_MMC_GetNcellSearchFirstTimerLen(VOS_VOID)
{
    return (NAS_MMC_GetMmcCtxAddr()->stPlmnSearchCtrl.stDsdaPlmnSearchEnhancedCfg.ucNcellSearchFirstTimerLen);
}

/*****************************************************************************
 函 数 名  : NAS_MMC_SetNcellSearchFirstTimerLen
 功能描述  : 设置第一阶段邻区频点快速搜索策略的时间间隔
 输入参数  : ucNcellSearchTimerLen - ncell搜网时间间隔
 输出参数  : 无
 返 回 值  : 无
 调用函数  :
 被调函数  :
 修改历史      :
 1.日    期   : 2013年12月24日
   作    者   : z00161729
   修改内容   : SVLTE支持NCELL搜网
 2.日    期   : 2014年1月26日
   作    者   : z00161729
   修改内容   : DTS2014012305088:支持增强NCELL搜网，如果Modem1传递过来的邻区信息不存在的情况下，通过历史频点支持NCELL搜索。
*****************************************************************************/
VOS_VOID NAS_MMC_SetNcellSearchFirstTimerLen(VOS_UINT8 ucNcellSearchTimerLen)
{
    NAS_MMC_GetMmcCtxAddr()->stPlmnSearchCtrl.stDsdaPlmnSearchEnhancedCfg.ucNcellSearchFirstTimerLen = ucNcellSearchTimerLen;
}


/*****************************************************************************
 函 数 名  : NAS_MMC_GetNcellSearchSecondTimerLen
 功能描述  : 获取第二阶段邻区频点快速搜索策略的时间间隔
 输入参数  : 无
 输出参数  : 无
 返 回 值  : 时间间隔
 调用函数  :
 被调函数  :
 修改历史      :
 1.日    期   : 2014年1月26日
   作    者   : z00161729
   修改内容   : DTS2014012305088:支持增强NCELL搜网，如果Modem1传递过来的邻区信息不存在的情况下，通过历史频点支持NCELL搜索。
*****************************************************************************/
VOS_UINT8 NAS_MMC_GetNcellSearchSecondTimerLen(VOS_VOID)
{
    return (NAS_MMC_GetMmcCtxAddr()->stPlmnSearchCtrl.stDsdaPlmnSearchEnhancedCfg.ucNcellSearchSecondTimerLen);
}

/*****************************************************************************
 函 数 名  : NAS_MMC_SetNcellSearchSecondTimerLen
 功能描述  : 设置第二阶段邻区频点快速搜索策略的时间间隔
 输入参数  : ucNcellSearchTimerLen - ncell搜网时间间隔
 输出参数  : 无
 返 回 值  : 无
 调用函数  :
 被调函数  :
 修改历史      :
 1.日    期   : 2014年1月26日
   作    者   : z00161729
   修改内容   : DTS2014012305088:支持增强NCELL搜网，如果Modem1传递过来的邻区信息不存在的情况下，通过历史频点支持NCELL搜索。
*****************************************************************************/
VOS_VOID NAS_MMC_SetNcellSearchSecondTimerLen(VOS_UINT8 ucNcellSearchTimerLen)
{
    NAS_MMC_GetMmcCtxAddr()->stPlmnSearchCtrl.stDsdaPlmnSearchEnhancedCfg.ucNcellSearchSecondTimerLen = ucNcellSearchTimerLen;
}



/*******************************************************************************
  函 数 名  : NAS_MMC_GetPlmnSelectionMode
  功能描述  : 获取当前PLMN搜网模式,供SI_STK_ProvideLocalInfo_SearchMode函数调用
              接口适配
  输入参数  : 无
  输出参数  : 无
  返 回 值  : PLMN搜网模式
  调用函数  :
  被调函数  :
  修改历史      :
  1.日    期   : 2011-08-24
    作    者   : l00130025
    修改内容   : 新生成函数
*******************************************************************************/
VOS_VOID Mmc_ComGetPlmnSearchMode(VOS_UINT8 *pucReselMode)
{
    *pucReselMode = NAS_MMC_GetPlmnSelectionMode();
    return;
}

/*****************************************************************************
 函 数 名  : NAS_MMC_SetPlmnSelMode
 功能描述  : 获取当前PLMN搜网模式
 输入参数  : 无
 输出参数  : 无
 返 回 值  : PLMN搜网模式
 调用函数  :
 被调函数  :
 修改历史      :
 1.日    期   : 2011-07-11
   作    者   : z40661
   修改内容   : 新生成函数
*****************************************************************************/
VOS_VOID NAS_MMC_SetPlmnSelectionMode(
    NAS_MMC_PLMN_SELECTION_MODE_ENUM_UINT8      enSelectionMode
)
{
    NAS_MMC_GetMmcCtxAddr()->stPlmnSearchCtrl.enSelectionMode = enSelectionMode;
}

/*****************************************************************************
 函 数 名  : NAS_MMC_GetAsCellCampOn
 功能描述  : 获取接入层上报的驻留状态
 输入参数  : 无
 输出参数  : 无
 返 回 值  : 接入层上报的驻留状态
 调用函数  :
 被调函数  :
 修改历史      :
 1.日    期   : 2011-10-17
   作    者   : s46746
   修改内容   : 新生成函数
*****************************************************************************/
NAS_MMC_AS_CELL_CAMP_ON_ENUM_UINT8 NAS_MMC_GetAsCellCampOn(VOS_VOID)
{
    return (NAS_MMC_GetMmcCtxAddr()->stPlmnSearchCtrl.enAsCellCampOn);
}

/*****************************************************************************
 函 数 名  : NAS_MMC_SetAsCellCampOn
 功能描述  : 设置接入层上报的驻留状态
 输入参数  : enAsCellCampOn
 输出参数  : 无
 返 回 值  : 接入层上报的驻留状态
 调用函数  :
 被调函数  :
 修改历史      :
 1.日    期   : 2011-07-29
   作    者   : w00176964
   修改内容   : 新生成函数
*****************************************************************************/
VOS_VOID NAS_MMC_SetAsCellCampOn(NAS_MMC_AS_CELL_CAMP_ON_ENUM_UINT8   enAsCellCampOn)
{
    NAS_MMC_GetMmcCtxAddr()->stPlmnSearchCtrl.enAsCellCampOn = enAsCellCampOn;
}

/*****************************************************************************
 函 数 名  : NAS_MMC_GetSpecPlmnSearchState
 功能描述  : 获取MMC是否指定搜网状态
 输入参数  : 无
 输出参数  : 无
 返 回 值  : MMC是否指定搜网状态
 调用函数  :
 被调函数  :
 修改历史      :
 1.日    期   : 2011-10-17
   作    者   : s46746
   修改内容   : 新生成函数
*****************************************************************************/
NAS_MMC_SPEC_PLMN_SEARCH_STATE_ENUM_UINT8 NAS_MMC_GetSpecPlmnSearchState(VOS_VOID)
{
    return (NAS_MMC_GetMmcCtxAddr()->stPlmnSearchCtrl.enSpecPlmnSearchState);
}

/*****************************************************************************
 函 数 名  : NAS_MMC_SetSpecPlmnSearchState
 功能描述  : 设置指定搜网状态
 输入参数  : enSpecPlmnSearchState
 输出参数  : 无
 返 回 值  : 无
 调用函数  :
 被调函数  :
 修改历史      :
 1.日    期   : 2011-07-29
   作    者   : w00176964
   修改内容   : 新生成函数
*****************************************************************************/
VOS_VOID NAS_MMC_SetSpecPlmnSearchState(NAS_MMC_SPEC_PLMN_SEARCH_STATE_ENUM_UINT8 enSpecPlmnSearchState)
{
    NAS_MMC_GetMmcCtxAddr()->stPlmnSearchCtrl.enSpecPlmnSearchState = enSpecPlmnSearchState;
}

/*****************************************************************************
 函 数 名  : NAS_MMC_GetUserSpecPlmnId
 功能描述  : 获取用户指定搜网的PLMNID
 输入参数  : 无
 输出参数  : 无
 返 回 值  : 用户指定搜网的PLMNID
 调用函数  :
 被调函数  :
 修改历史      :
 1.日    期   : 2011-07-11
   作    者   : z40661
   修改内容   : 新生成函数
*****************************************************************************/

NAS_MML_PLMN_WITH_RAT_STRU *NAS_MMC_GetUserSpecPlmnId(VOS_VOID)
{
    return &(NAS_MMC_GetMmcCtxAddr()->stPlmnSearchCtrl.stUserSpecPlmnId);
}

/*****************************************************************************
 函 数 名  : NAS_MMC_GetUserSpecPlmnRegisterStatus
 功能描述  : 获取用户指定搜网的注册状态
 输入参数  : 无
 输出参数  : 无
 返 回 值  : 用户指定搜网的注册状态
 调用函数  :
 被调函数  :
 修改历史      :
 1.日    期   : 2011-08-2
   作    者   : s46746
   修改内容   : 新生成函数
*****************************************************************************/

VOS_UINT32 NAS_MMC_GetUserSpecPlmnRegisterStatus()
{
    return NAS_MMC_GetMmcCtxAddr()->stPlmnSearchCtrl.ucUserSpecPlmnRegStatus;
}

/*****************************************************************************
 函 数 名  : NAS_MMC_GetUserReselPlmnId
 功能描述  : 获取指定搜网前驻留的PLMNID和接入技术,但同时指定搜网注册成功后也会更新该值
 输入参数  : 无
 输出参数  : 无
 返 回 值  : 用户指定搜网前驻留的PLMNID和接入技术,但同时指定搜网注册成功后也会更新该值
 调用函数  :
 被调函数  :
 修改历史      :
 1.日    期   : 2011-07-11
   作    者   : z40661
   修改内容   : 新生成函数
*****************************************************************************/

NAS_MML_PLMN_WITH_RAT_STRU *NAS_MMC_GetUserReselPlmnId(VOS_VOID)
{
    return &(NAS_MMC_GetMmcCtxAddr()->stPlmnSearchCtrl.stUserReselPlmnId);
}

/*****************************************************************************
 函 数 名  : NAS_MMC_SetUserSpecPlmnId
 功能描述  : 设置用户指定搜网的PLMNID
 输入参数  : pstPlmnInfo:用户指定搜网的PLMNID
 输出参数  : 无
 返 回 值  :
 调用函数  :
 被调函数  :
 修改历史      :
 1.日    期   : 2011-07-11
   作    者   : z40661
   修改内容   : 新生成函数
*****************************************************************************/

VOS_VOID NAS_MMC_SetUserSpecPlmnId(
    NAS_MML_PLMN_WITH_RAT_STRU         *pstPlmnInfo
)
{
    PS_MEM_CPY(&(NAS_MMC_GetMmcCtxAddr()->stPlmnSearchCtrl.stUserSpecPlmnId),
               pstPlmnInfo,
               sizeof(NAS_MML_PLMN_WITH_RAT_STRU));
}

/*****************************************************************************
 函 数 名  : NAS_MMC_SetUserSpecPlmnRegisterStatus
 功能描述  : 设置用户指定搜网的注册状态
 输入参数  : ucRegisterStatus:注册状态
 输出参数  : 无
 返 回 值  : 无
 调用函数  :
 被调函数  :
 修改历史      :
 1.日    期   : 2011-08-2
   作    者   : s46746
   修改内容   : 新生成函数
 2.日    期   : 2012年08月20日
   作    者   : l65478
   修改内容   : DTS2012081703289，手动搜网失败后关机，重新开机注册成功
               后出服务区后不驻留EPLMN上

  3.日    期   : 2012年9月20日
    作    者   : z40661
    修改内容   : 自动模式下收到指定搜网请求，会将这个变量设置为VOS_FALSE，此
                 处不能进行自动模式的判断。
*****************************************************************************/

VOS_VOID NAS_MMC_SetUserSpecPlmnRegisterStatus(
    VOS_UINT8                           ucRegisterStatus
)
{
    NAS_MMC_GetMmcCtxAddr()->stPlmnSearchCtrl.ucUserSpecPlmnRegStatus = ucRegisterStatus;
}

/*****************************************************************************
 函 数 名  : NAS_MMC_SetUserReselPlmnId
 功能描述  : 设置指定搜网前驻留的PLMNID和接入技术
 输入参数  : pstPlmnInfo:用户指定搜网的PLMNID
 输出参数  : 无
 返 回 值  :
 调用函数  :
 被调函数  :
 修改历史      :
 1.日    期   : 2011-07-11
   作    者   : z40661
   修改内容   : 新生成函数
 2.日    期   : 2011年8月6日
   作    者   : L00171473
   修改内容   : 输入参数修改
*****************************************************************************/

VOS_VOID NAS_MMC_SetUserReselPlmnId(
    NAS_MML_PLMN_ID_STRU               *pstPlmnId,
    NAS_MML_NET_RAT_TYPE_ENUM_UINT8     enRat
)
{
    NAS_MML_PLMN_WITH_RAT_STRU         *pstUserReselPlmn = VOS_NULL_PTR;

    pstUserReselPlmn = NAS_MMC_GetUserReselPlmnId();

    pstUserReselPlmn->stPlmnId.ulMcc = pstPlmnId->ulMcc;
    pstUserReselPlmn->stPlmnId.ulMnc = pstPlmnId->ulMnc;
    pstUserReselPlmn->enRat          = enRat;
}


/*****************************************************************************
 函 数 名  : NAS_MMC_GetPlmnRegRejInfo
 功能描述  : 获取当前PLMN注册被拒上下文
 输入参数  : 无
 输出参数  : 无
 返 回 值  : PLMN注册被拒上下文
 调用函数  :
 被调函数  :
 修改历史      :
 1.日    期   : 2011-07-11
   作    者   : z40661
   修改内容   : 新生成函数
*****************************************************************************/
NAS_MMC_PLMN_REG_REJ_CTX_STRU *NAS_MMC_GetPlmnRegRejInfo(VOS_VOID)
{
    return &(NAS_MMC_GetMmcCtxAddr()->stPlmnRegInfo);
}

/*****************************************************************************
 函 数 名  : NAS_MMC_GetServiceInfo
 功能描述  : 获取当前MMC服务状态
 输入参数  : 无
 输出参数  : 无
 返 回 值  : 当前MMC服务状态
 调用函数  :
 被调函数  :
 修改历史      :
 1.日    期   : 2011-07-11
   作    者   : z40661
   修改内容   : 新生成函数
*****************************************************************************/
NAS_MMC_SERVICE_INFO_CTX_STRU *NAS_MMC_GetServiceInfo(VOS_VOID)
{
    return &(NAS_MMC_GetMmcCtxAddr()->stServiceInfo);
}


/*****************************************************************************
 函 数 名  : NAS_MMC_GetCurrCsService
 功能描述  : 获取当前MMC CS服务状态
 输入参数  : 无
 输出参数  : 无
 返 回 值  : 当前MMC服务状态
 调用函数  :
 被调函数  :
 修改历史      :
 1.日    期   : 2014-10-22
   作    者   : w00167002
   修改内容   : 新生成函数
*****************************************************************************/
NAS_MMC_SERVICE_ENUM_UINT8 NAS_MMC_GetCurrCsService(VOS_VOID)
{
    return (NAS_MMC_GetMmcCtxAddr()->stServiceInfo.enCsCurrService);
}

/*****************************************************************************
 函 数 名  : NAS_MMC_GetCurrPsService
 功能描述  : 获取当前MMC CS服务状态
 输入参数  : 无
 输出参数  : 无
 返 回 值  : 当前MMC服务状态
 调用函数  :
 被调函数  :
 修改历史      :
 1.日    期   : 2014-10-22
   作    者   : w00167002
   修改内容   : 新生成函数
*****************************************************************************/
NAS_MMC_SERVICE_ENUM_UINT8 NAS_MMC_GetCurrPsService(VOS_VOID)
{
    return (NAS_MMC_GetMmcCtxAddr()->stServiceInfo.enPsCurrService);
}



/*****************************************************************************
 函 数 名  : NAS_MMC_IsCsNormalService
 功能描述  : 判断当前CS域是否正常服务
 输入参数  : VOS_VOID
 输出参数  : 无
 返 回 值  : VOS_UINT32
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2011年8月27日
    作    者   : l00130025
    修改内容   : 新生成函数

*****************************************************************************/
VOS_UINT32 NAS_MMC_IsCsNormalService( VOS_VOID )
{
    if ( NAS_MMC_NORMAL_SERVICE == NAS_MMC_GetMmcCtxAddr()->stServiceInfo.enCsCurrService )
    {
        return VOS_TRUE;
    }

    return VOS_FALSE;
}

/*****************************************************************************
 函 数 名  : NAS_MMC_IsPsNormalService
 功能描述  : 判断当前PS域是否正常服务
 输入参数  : VOS_VOID
 输出参数  : 无
 返 回 值  : VOS_UINT32
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2011年8月27日
    作    者   : l00130025
    修改内容   : 新生成函数

*****************************************************************************/
VOS_UINT32 NAS_MMC_IsPsNormalService( VOS_VOID )
{
    if ( NAS_MMC_NORMAL_SERVICE == NAS_MMC_GetMmcCtxAddr()->stServiceInfo.enPsCurrService )
    {
        return VOS_TRUE;
    }

    return VOS_FALSE;
}

/*****************************************************************************
 函 数 名  : NAS_MMC_IsNormalServiceStatus
 功能描述  : 判断MMC是否是正常服务
 输入参数  : 无
 输出参数  : 无
 返 回 值  : VOS_TRUE:正常服务
             VOS_FALSE:不是正常服务
 调用函数  :
 被调函数  :
 修改历史      :
 1.日    期   : 2011-07-11
   作    者   : z40661
   修改内容   : 新生成函数
*****************************************************************************/
VOS_UINT32 NAS_MMC_IsNormalServiceStatus(VOS_VOID)
{
    if ( NAS_MMC_NORMAL_SERVICE == NAS_MMC_GetMmcCtxAddr()->stServiceInfo.enCsCurrService )
    {
        return VOS_TRUE;
    }

    if ( NAS_MMC_NORMAL_SERVICE == NAS_MMC_GetMmcCtxAddr()->stServiceInfo.enPsCurrService )
    {
        return VOS_TRUE;
    }

    return VOS_FALSE;
}


/*****************************************************************************
 函 数 名  : NAS_MMC_GetMaintainInfo
 功能描述  : 获取当前MMC可维可测信息
 输入参数  : 无
 输出参数  : 无
 返 回 值  : 当前MMC可维可测信息
 调用函数  :
 被调函数  :
 修改历史      :
 1.日    期   : 2011-07-11
   作    者   : z40661
   修改内容   : 新生成函数
*****************************************************************************/
NAS_MMC_MAINTAIN_CTX_STRU *NAS_MMC_GetMaintainInfo(VOS_VOID)
{
    return &(NAS_MMC_GetMmcCtxAddr()->stMaintainInfo);
}

/*****************************************************************************
 函 数 名  : NAS_MMC_ConverMmStatusToMmc
 功能描述  : MM或GMM的服务状态转换为MMC的服务状态
 输入参数  : enServiceStatus:MM或GMM的服务状态
 输出参数  : 无
 返 回 值  :
 调用函数  :
 被调函数  :

 修改历史      :
 1.日    期   : 2011年7月20日
   作    者   : zhoujun 40661
   修改内容   : 新生成函数

*****************************************************************************/
NAS_MMC_SERVICE_ENUM_UINT8  NAS_MMC_ConverMmStatusToMmc(
    NAS_MMC_REG_DOMAIN_ENUM_UINT8           enRegDomain,
    NAS_MM_COM_SERVICE_STATUS_ENUM_UINT8    enServiceStatus
)
{
    switch ( enServiceStatus )
    {
        case MM_COM_SRVST_NORMAL_SERVICE :
            return NAS_MMC_NORMAL_SERVICE;

        case MM_COM_SRVST_LIMITED_SERVICE :
            return NAS_MMC_LIMITED_SERVICE;

        case MM_COM_SRVST_LIMITED_SERVICE_REGION :
            return NAS_MMC_LIMITED_SERVICE_REGION;

        case MM_COM_SRVST_NO_IMSI :
            return NAS_MMC_LIMITED_SERVICE;

        case MM_COM_SRVST_NO_SERVICE :
            return NAS_MMC_NO_SERVICE;

        default:
            NAS_INFO_LOG1(WUEPS_PID_MMC, "NAS_MMC_ConverMmStatusToMmc,", enServiceStatus);
            break;
    }

    if ( NAS_MMC_REG_DOMAIN_CS == enRegDomain )
    {
        return NAS_MMC_GetCsServiceStatus();
    }
    else
    {
        return NAS_MMC_GetPsServiceStatus();
    }
}



/*****************************************************************************
 函 数 名  : NAS_MMC_UpdateDomainServiceStatus
 功能描述  : 更新服务域的状态
 输入参数  : enCurrDomain  :当前的服务域
              enCurrService :须更新当前服务域的状态
 输出参数  : 无
 返 回 值  : 无
 调用函数  :
 被调函数  :
 修改历史      :
 1.日    期   : 2011-11-3
   作    者   : w00167002
   修改内容   : 新生成函数
*****************************************************************************/

VOS_VOID NAS_MMC_UpdateDomainServiceStatus(
    VOS_UINT8                           enCurrDomain,
    NAS_MMC_SERVICE_ENUM_UINT8          enCurrService
)
{
    /* 如果存在CS域，则更新CS域的结果 */
    if ( NAS_MMC_WAIT_REG_RESULT_IND_CS == (NAS_MMC_WAIT_REG_RESULT_IND_CS & enCurrDomain) )
    {
        NAS_MMC_SetCsServiceStatus(enCurrService);
    }

    /* 如果存在PS域，则更新PS域的结果 */
    if ( NAS_MMC_WAIT_REG_RESULT_IND_PS == (NAS_MMC_WAIT_REG_RESULT_IND_PS & enCurrDomain) )
    {
        NAS_MMC_SetPsServiceStatus(enCurrService);
    }
}



/*****************************************************************************
 函 数 名  : NAS_MMC_SetCsServiceStatus
 功能描述  : 更新当前CS服务状态
 输入参数  : CS服务状态
 输出参数  : 无
 返 回 值  : 无
 调用函数  :
 被调函数  :
 修改历史      :
 1.日    期   : 2011-07-13
   作    者   : W00176964
   修改内容   : 新生成函数
*****************************************************************************/

VOS_VOID    NAS_MMC_SetCsServiceStatus(
    NAS_MMC_SERVICE_ENUM_UINT8          enCsCurrService
)
{
    NAS_MMC_SERVICE_INFO_CTX_STRU      *pstServiceInfo = VOS_NULL_PTR;

    pstServiceInfo =  NAS_MMC_GetServiceInfo();

    pstServiceInfo->enCsCurrService = enCsCurrService;
}
/* Added by s00261364 for V3R360_eCall项目, 2014-4-30, begin */

/*****************************************************************************
 函 数 名  : NAS_MMC_IsInValidCampPlmn
 功能描述  : 更新当前驻留网络是否无效
 输入参数  : VOS_VOID
 输出参数  : 无
 返 回 值  : VOS_UINT32
 调用函数  :
 被调函数  :
 修改历史      :
 1.日    期   : 2014-04-30
   作    者   : s00261364
   修改内容   : 新生成函数
*****************************************************************************/

VOS_UINT32  NAS_MMC_IsInValidCampPlmn( VOS_VOID )
{
    NAS_MML_CAMP_PLMN_INFO_STRU         *pstCampPlmnInfo = VOS_NULL_PTR;

    pstCampPlmnInfo = NAS_MML_GetCurrCampPlmnInfo();

    /* 判定当前驻留PLMN为无效值 */
    if ( (NAS_MML_INVALID_MCC == pstCampPlmnInfo->stLai.stPlmnId.ulMcc )
      && (NAS_MML_INVALID_MNC == pstCampPlmnInfo->stLai.stPlmnId.ulMnc ) )
    {
        return VOS_TRUE;
    }

    return VOS_FALSE;
}

/* Added by s00261364 for V3R360_eCall项目, 2014-4-30, end */
/*****************************************************************************
 函 数 名  : NAS_MMC_SetPsServiceStatus
 功能描述  : 更新当前PS服务状态
 输入参数  : PS服务状态
 输出参数  : 无
 返 回 值  : 无
 调用函数  :
 被调函数  :
 修改历史      :
 1.日    期   : 2011-07-13
   作    者   : W00176964
   修改内容   : 新生成函数
*****************************************************************************/
VOS_VOID    NAS_MMC_SetPsServiceStatus(NAS_MMC_SERVICE_ENUM_UINT8   enPsCurrService)
{
    NAS_MMC_SERVICE_INFO_CTX_STRU      *pstServiceInfo = VOS_NULL_PTR;

    pstServiceInfo =  NAS_MMC_GetServiceInfo();

    pstServiceInfo->enPsCurrService = enPsCurrService;
}

/*****************************************************************************
 函 数 名  : NAS_MMC_GetCsServiceStatus
 功能描述  : 获取当前CS服务状态
 输入参数  : CS服务状态
 输出参数  : 无
 返 回 值  : 当前CS服务状态
 调用函数  :
 被调函数  :
 修改历史      :
 1.日    期   : 2011-07-19
   作    者   : W00176964
   修改内容   : 新生成函数
*****************************************************************************/

NAS_MMC_SERVICE_ENUM_UINT8 NAS_MMC_GetCsServiceStatus( VOS_VOID )
{
    NAS_MMC_SERVICE_INFO_CTX_STRU*          pstServiceInfo = VOS_NULL_PTR;

    pstServiceInfo =  NAS_MMC_GetServiceInfo();

    return pstServiceInfo->enCsCurrService;
}

/*****************************************************************************
 函 数 名  : NAS_MMC_GetPsServiceStatus
 功能描述  : 获取当前PS服务状态
 输入参数  : PS服务状态
 输出参数  : 无
 返 回 值  : 当前PS服务状态
 调用函数  :
 被调函数  :
 修改历史      :
 1.日    期   : 2011-07-19
   作    者   : W00176964
   修改内容   : 新生成函数
*****************************************************************************/

NAS_MMC_SERVICE_ENUM_UINT8 NAS_MMC_GetPsServiceStatus( VOS_VOID )
{
    NAS_MMC_SERVICE_INFO_CTX_STRU*          pstServiceInfo = VOS_NULL_PTR;

    pstServiceInfo =  NAS_MMC_GetServiceInfo();

    return pstServiceInfo->enPsCurrService;
}


/*****************************************************************************
 函 数 名  : NAS_MMC_GetNextAvailableTimerValue
 功能描述  : 获取当前AvailableTimer的时长
 输入参数  : 无
 输出参数  : 无
 返 回 值  : 当前AvailableTimer的时长
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2011年7月29日
    作    者   : w00176964
    修改内容   : 新生成函数

  2.日    期   : 2012年9月29日
    作    者   : z40661
    修改内容   : DTS2012080908811,available timer定时器启动多了1次
  3.日    期   : 2013年12月24日
    作    者   : z00161729
    修改内容   : SVLTE支持NCELL搜网
  4.日    期   : 2014年1月26日
    作    者   : z00161729
    修改内容   : DTS2014012305088：支持增强NCELL搜网，如果Modem1传递过来的邻区信息不存在的情况下，通过历史频点支持NCELL搜索。
  5.日    期   : 2015年10月26日
    作    者   : h00281185
    修改内容   : 新增PrefBand搜
*****************************************************************************/
VOS_UINT32  NAS_MMC_GetNextAvailableTimerValue(VOS_VOID)
{

    VOS_UINT32                          ulTimerLen;

    //Fen = Ncell Priority?
    if (VOS_TRUE == NAS_MMC_IsNeedStartNcellAvailableTimer())
    {
        /* NCELL全局变量中存的只是数字，将其转换成以毫秒为单位 */
        if (NAS_MMC_OOS_PHASE_ONE == NAS_MMC_GetOosPhaseNum())
        {
            ulTimerLen = NAS_MML_ONE_THOUSAND_MILLISECOND * NAS_MMC_GetNcellSearchFirstTimerLen();
        }
        else
        {
            ulTimerLen = NAS_MML_ONE_THOUSAND_MILLISECOND * NAS_MMC_GetNcellSearchSecondTimerLen();
        }
    }
    else
    {
        ulTimerLen  = NAS_MMC_GetNextSearchSleepTimerLen();
    }

    return ulTimerLen;
}






/*****************************************************************************
 函 数 名  : NAS_MMC_GetNextSearchSleepTimerLen
 功能描述  : 获取PrefBand搜时定时器的时长
 输入参数  : VOS_VOID
 输出参数  : 无
 返 回 值  : VOS_UINT32
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2015年10月12日
    作    者   : h00281185
    修改内容   : 新生成函数

*****************************************************************************/
VOS_UINT32 NAS_MMC_GetNextSearchSleepTimerLen(VOS_VOID)
{
    NAS_MMC_OOS_PLMN_SEARCH_PATTERN_INFO_STRU                          *pstPhaseOneOosPlmnSearchPatternInfo  = VOS_NULL_PTR;
    NAS_MMC_OOS_PLMN_SEARCH_PATTERN_INFO_STRU                          *pstPhaseTwoOosPlmnSearchPatternInfo  = VOS_NULL_PTR;

    VOS_UINT32                                              ulTimerLen;


    pstPhaseOneOosPlmnSearchPatternInfo    = NAS_MMC_GetPhaseOneOosPlmnSearchPatternInfo();
    pstPhaseTwoOosPlmnSearchPatternInfo    = NAS_MMC_GetPhaseTwoOosPlmnSearchPatternInfo();


    if (NAS_MMC_OOS_PHASE_ONE == NAS_MMC_GetOosPhaseNum())
    {
        ulTimerLen = NAS_MML_ONE_THOUSAND_MILLISECOND * (pstPhaseOneOosPlmnSearchPatternInfo->usSleepTimerLen);
    }
    else
    {
        ulTimerLen = NAS_MML_ONE_THOUSAND_MILLISECOND * (pstPhaseTwoOosPlmnSearchPatternInfo->usSleepTimerLen);
    }

    return ulTimerLen;
}

/*************************************** L1 MAIN状态机上下文操作函数 *************************************************/
/*****************************************************************************
 函 数 名  : NAS_MMC_GetCurNormalAvailableTimerCount_L1Main
 功能描述  : 获取availble timer当前启动的次数
 输入参数  : 无
 输出参数  : 无
 返 回 值  : VOS_UINT32
 调用函数  :
 被调函数  :

 修改历史     :
 1.日    期   : 2011年7月29日
   作    者   : w00176964
   修改内容   : 新生成函数
 2.日    期   : 2014年1月2日
   作    者   : z00161729
   修改内容   : SVLTE支持NCELL搜网
*****************************************************************************/
VOS_UINT32  NAS_MMC_GetCurNormalAvailableTimerCount_L1Main(VOS_VOID)
{

    /* 如果当前状态机不是L1 MAIN */
    if (NAS_MMC_FSM_L1_MAIN != NAS_MMC_GetCurrFsmId())
    {
        NAS_ERROR_LOG(WUEPS_PID_MMC, "NAS_MMC_GetCurNormalAvailableTimerCount_L1Main,ERROR:FsmId Error");
    }

    return g_stNasMmcCtx.stCurFsm.unFsmCtx.stL1MainCtx.ulCurTimerCount;
}

/*****************************************************************************
 函 数 名  : NAS_MMC_ResetCurNormalAvailableTimerCount_L1Main
 功能描述  : Reset normal available timer当前启动的次数
 输入参数  : 无
 输出参数  : 无
 返 回 值  : VOS_UINT32
 调用函数  :
 被调函数  :

 修改历史     :
 1.日    期   : 2011年7月29日
   作    者   : w00176964
   修改内容   : 新生成函数
 2.日    期   : 2014年1月2日
   作    者   : z00161729
   修改内容   : SVLTE支持NCELL搜网
*****************************************************************************/
VOS_VOID    NAS_MMC_ResetCurNormalAvailableTimerCount_L1Main(VOS_VOID)
{
    /* 如果当前状态机不是L1 MAIN */
    if (NAS_MMC_FSM_L1_MAIN != NAS_MMC_GetCurrFsmId())
    {
        NAS_ERROR_LOG(WUEPS_PID_MMC, "NAS_MMC_ResetCurNormalAvailableTimerCount_L1Main,ERROR:FsmId Error");

        return;
    }

    g_stNasMmcCtx.stCurFsm.unFsmCtx.stL1MainCtx.ulCurTimerCount = 0;
}

/*****************************************************************************
 函 数 名  : NAS_MMC_AddCurNormalAvailableTimerCount_L1Main
 功能描述  : 递增普通availble timer当前启动的次数
 输入参数  : 无
 输出参数  : 无
 返 回 值  : VOS_UINT32
 调用函数  :
 被调函数  :

 修改历史     :
 1.日    期   : 2011年7月29日
   作    者   : w00176964
   修改内容   : 新生成函数
 2.日    期   : 2014年1月2日
   作    者   : z00161729
   修改内容   : SVLTE支持NCELL搜网
*****************************************************************************/
VOS_VOID    NAS_MMC_AddCurNormalAvailableTimerCount_L1Main(VOS_VOID)
{
    /* 如果当前状态机不是L1 MAIN */
    if (NAS_MMC_FSM_L1_MAIN != NAS_MMC_GetCurrFsmId())
    {
        NAS_ERROR_LOG(WUEPS_PID_MMC, "NAS_MMC_AddCurNormalAvailableTimerCount_L1Main,ERROR:FsmId Error");

        return;
    }

    g_stNasMmcCtx.stCurFsm.unFsmCtx.stL1MainCtx.ulCurTimerCount++;
}

/* Added by s00246516 for L-C互操作项目, 2014-03-28, Begin */
/*****************************************************************************
 函 数 名  : NAS_MMC_SetCurNormalAvailableTimerCount
 功能描述  : 设置availble timer当前启动的次数
 输入参数  : 无
 输出参数  : 无
 返 回 值  : VOS_VOID
 调用函数  :
 被调函数  :

 修改历史     :
 1.日    期   : 2014年3月28日
   作    者   : s00246516
   修改内容   : 新生成函数
*****************************************************************************/
VOS_VOID   NAS_MMC_SetCurNormalAvailableTimerCount(
    VOS_UINT32                          ulCurTimerCount
)
{
    g_stNasMmcCtx.stCurFsm.unFsmCtx.stL1MainCtx.ulCurTimerCount = ulCurTimerCount;
}
/* Added by s00246516 for L-C互操作项目, 2014-03-28, End */

/*****************************************************************************
 函 数 名  : NAS_MMC_IsNeedStartNcellAvailableTimer
 功能描述  : 判断是否需要启动ncell available
 输入参数  : 无
 输出参数  : 无
 返 回 值  : VOS_TRUE:需要启动ncell available；VOS_FALSE:不需要启动ncell available
 调用函数  :
 被调函数  :

 修改历史     :
 1.日    期   : 2013年12月24日
   作    者   : z00161729
   修改内容   : SVLTE支持NCELL搜网
 2.日    期   : 2014年1月26日
   作    者   : z00161729
   修改内容   : DTS2014012305088：支持增强NCELL搜网，如果Modem1传递过来的邻区信息不存在的情况下，通过历史频点支持NCELL搜索。
 3.日    期   : 2014年6月17日
   作    者   : z00234330
   修改内容   : PCINT清理
*****************************************************************************/
VOS_UINT8  NAS_MMC_IsNeedStartNcellAvailableTimer(VOS_VOID)
{
    VOS_UINT8                           ucNcellSearchFlag;
    VOS_UINT8                           ucNcellSearchTimerLen;
    VOS_UINT32                          ulAvailableSearchTimeLen;

    VOS_UINT8                           ucPsAttachAllowFlag;
    VOS_UINT8                           ucCsAttachAllowFlag;



    ucNcellSearchFlag          = NAS_MMC_GetNcellSearchFlag();
    ucPsAttachAllowFlag        = NAS_MML_GetPsAttachAllowFlg();
    ucCsAttachAllowFlag        = NAS_MML_GetCsAttachAllowFlg();

    if (NAS_MMC_OOS_PHASE_ONE == NAS_MMC_GetOosPhaseNum())
    {
        /* 获取第一阶段available时间间隔和ncell时间间隔 */
        ulAvailableSearchTimeLen    = NAS_MMC_GetPhaseOnePeriodicSleepTimerLen();
        ucNcellSearchTimerLen       = NAS_MMC_GetNcellSearchFirstTimerLen();
    }
    else
    {
        /* 获取第二阶段available时间间隔和ncell时间间隔 */
        ulAvailableSearchTimeLen    = NAS_MMC_GetPhaseTwoPeriodicSleepTimerLen();
        ucNcellSearchTimerLen       = NAS_MMC_GetNcellSearchSecondTimerLen();
    }

    /*
       1、支持ncell快速搜网nv开启:
        -- modem1 gas上报存在t或l的邻区频点信息或邻区个数为0时也需启动ncell搜定时器
        -- 当前为PS attach not allow/cs attach not allow,防止国外情况开启该功能
        -- 如果普通available定时器为5s，NCELL available时长为10s，
          此时不需要启动NCELL available定时器。还是启动5s 普通available定时器，超时做
          普通 available搜索。
          如果要启动NCELL available定时器的话，必须满足普通available定时器时长内
          至少可启动两次NCELL available定时器，第一次NCELL available定时器超时做NCELL快速搜，
          第二次超时做普通Available搜
        -- 如果ncell时长为0，则启动普通available定时器
   */
   /* Modified by z00234330 for PCLINT清理, 2014-06-16, begin */
    if ((VOS_TRUE == ucNcellSearchFlag)
     && (0 != ucNcellSearchTimerLen)
     && (ulAvailableSearchTimeLen >= (2*ucNcellSearchTimerLen))
     && (VOS_FALSE == ucPsAttachAllowFlag)
     && (VOS_FALSE == ucCsAttachAllowFlag))
    {
        return VOS_TRUE;
    }
    /* Modified by z00234330 for PCLINT清理, 2014-06-16, end */

    return VOS_FALSE;
}


/*****************************************************************************
 函 数 名  : NAS_MMC_IsNeedStartHistoryTimer
 功能描述  : 是否需要启history搜定时器
 输入参数  : VOS_VOID
 输出参数  : 无
 返 回 值  : VOS_UINT8
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2015年5月25日
    作    者   : s00217060
    修改内容   : 新生成函数
  2.日    期   : 2015年9月11日
    作    者   : c00318887
    修改内容   : 预置频点搜网优化,
  3.日    期   : 2015年10月17日
    作    者   : h00281185
    修改内容   : 预制频段搜网优化, 采用倍数关系逻辑

*****************************************************************************/
VOS_UINT8 NAS_MMC_IsNeedStartHistoryTimer(VOS_VOID)
{
    NAS_MMC_OOS_PLMN_SEARCH_PATTERN_INFO_STRU      *pstPhaseOneOosPlmnSearchPatternInfo  = VOS_NULL_PTR;
    NAS_MMC_OOS_PLMN_SEARCH_PATTERN_INFO_STRU      *pstPhaseTwoOosPlmnSearchPatternInfo  = VOS_NULL_PTR;

    VOS_UINT8                           ucHistoryNum;


    pstPhaseOneOosPlmnSearchPatternInfo    = NAS_MMC_GetPhaseOneOosPlmnSearchPatternInfo();
    pstPhaseTwoOosPlmnSearchPatternInfo    = NAS_MMC_GetPhaseTwoOosPlmnSearchPatternInfo();



    if (NAS_MMC_OOS_PHASE_ONE == NAS_MMC_GetOosPhaseNum())
    {
        /* 获取第一阶段历史搜次数 */
        ucHistoryNum = pstPhaseOneOosPlmnSearchPatternInfo->ucHistoryNum;
    }
    else
    {
        /* 获取第二阶段历史搜次数 */
        ucHistoryNum = pstPhaseTwoOosPlmnSearchPatternInfo->ucHistoryNum;
    }

    /* 次数为0，表示history特性关闭，不需要启动history搜定时器 */

    if (0 < ucHistoryNum)
    {
        return VOS_TRUE;
    }

    return VOS_FALSE;

}

/*****************************************************************************
 函 数 名  : NAS_MMC_IsNeedStartPrefBandTimer
 功能描述  : 是否需要启PrefBand搜定时器
 输入参数  : VOS_VOID
 输出参数  : 无
 返 回 值  : VOS_UINT8
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2015年10月09日
    作    者   : h00281185
    修改内容   : 新生成函数
*****************************************************************************/
VOS_UINT8 NAS_MMC_IsNeedStartPrefBandTimer(VOS_VOID)
{
    NAS_MMC_OOS_PLMN_SEARCH_PATTERN_INFO_STRU      *pstPhaseOneOosPlmnSearchPatternInfo  = VOS_NULL_PTR;
    NAS_MMC_OOS_PLMN_SEARCH_PATTERN_INFO_STRU      *pstPhaseTwoOosPlmnSearchPatternInfo  = VOS_NULL_PTR;
    VOS_UINT8                           ucPrefBandNum;


    pstPhaseOneOosPlmnSearchPatternInfo    = NAS_MMC_GetPhaseOneOosPlmnSearchPatternInfo();
    pstPhaseTwoOosPlmnSearchPatternInfo    = NAS_MMC_GetPhaseTwoOosPlmnSearchPatternInfo();


    if (NAS_MMC_OOS_PHASE_ONE == NAS_MMC_GetOosPhaseNum())
    {
        /* 获取第一阶段PrefBand搜次数 */
        ucPrefBandNum = pstPhaseOneOosPlmnSearchPatternInfo->ucPrefBandNum;
    }
    else
    {
        /* 获取第二阶段PrefBand搜次数 */
        ucPrefBandNum = pstPhaseTwoOosPlmnSearchPatternInfo->ucPrefBandNum;
    }

    /* 次数为0不需要启动PrefBand搜定时器 */
    if (0 < ucPrefBandNum)
    {
        return VOS_TRUE;
    }

    return VOS_FALSE;

}

/*****************************************************************************
 函 数 名  : NAS_MMC_GetAvailableTimerType_OnPlmn
 功能描述  : 获取available定时器类型
 输入参数  : 无
 输出参数  : 无
 返 回 值  : VOS_UINT8
 调用函数  :
 被调函数  :

 修改历史     :
 1.日    期   : 2014年2月7日
   作    者   : z00161729
   修改内容   : DTS2014012305088：支持增强NCELL搜网，如果Modem1传递过来的邻区信息不存在的情况下，通过历史频点支持NCELL搜索

*****************************************************************************/
NAS_MMC_AVAILABLE_TIMER_TYPE_ENUM_UINT8  NAS_MMC_GetAvailableTimerType_OnPlmn(VOS_VOID)
{

    /* 如果当前状态机不是L1 MAIN */
    if (NAS_MMC_FSM_L1_MAIN != NAS_MMC_GetCurrFsmId())
    {
        NAS_ERROR_LOG(WUEPS_PID_MMC, "NAS_MMC_GetAvailableTimerType_OnPlmn,ERROR:FsmId Error");
    }

    return g_stNasMmcCtx.stCurFsm.unFsmCtx.stL1MainCtx.enAvailableTimerType;
}

/*****************************************************************************
 函 数 名  : NAS_MMC_SetAvailableTimerType_OnPlmn
 功能描述  : 设置available定时器类型
 输入参数  : enAvailableTimerType - available定时器类型
 输出参数  : 无
 返 回 值  : 无
 调用函数  :
 被调函数  :

 修改历史     :
 1.日    期   : 2014年2月7日
   作    者   : z00161729
   修改内容   : DTS2014012305088：支持增强NCELL搜网，如果Modem1传递过来的邻区信息不存在的情况下，通过历史频点支持NCELL搜索

*****************************************************************************/
VOS_VOID  NAS_MMC_SetAvailableTimerType_OnPlmn(
    NAS_MMC_AVAILABLE_TIMER_TYPE_ENUM_UINT8                 enAvailableTimerType
)
{
    /* 如果当前状态机不是L1 MAIN */
    if (NAS_MMC_FSM_L1_MAIN != NAS_MMC_GetCurrFsmId())
    {
        NAS_ERROR_LOG(WUEPS_PID_MMC, "NAS_MMC_SetAvailableTimerType_OnPlmn,ERROR:FsmId Error");

        return;
    }

    g_stNasMmcCtx.stCurFsm.unFsmCtx.stL1MainCtx.enAvailableTimerType = enAvailableTimerType;

}



/*****************************************************************************
 函 数 名  : NAS_MMC_GetCurNcellSearchTimerCount_OnPlmn
 功能描述  : 获取ncell搜索当前启动的次数
 输入参数  : 无
 输出参数  : 无
 返 回 值  : VOS_UINT32
 调用函数  :
 被调函数  :

 修改历史     :
 1.日    期   : 2013年12月24日
   作    者   : z00161729
   修改内容   : SVLTE支持NCELL搜网

*****************************************************************************/
VOS_UINT32  NAS_MMC_GetCurNcellSearchTimerCount_OnPlmn(VOS_VOID)
{

    /* 如果当前状态机不是L1 MAIN */
    if (NAS_MMC_FSM_L1_MAIN != NAS_MMC_GetCurrFsmId())
    {
        NAS_ERROR_LOG(WUEPS_PID_MMC, "NAS_MMC_GetCurNcellSearchTimerCount_L1Main,ERROR:FsmId Error");
    }

    return g_stNasMmcCtx.stCurFsm.unFsmCtx.stL1MainCtx.ulCurNcellSearchTimerCount;
}

/*****************************************************************************
 函 数 名  : NAS_MMC_ResetCurNcellSearchTimerCount_OnPlmn
 功能描述  : Reset ncell搜网当前启动的次数
 输入参数  : 无
 输出参数  : 无
 返 回 值  : VOS_UINT32
 调用函数  :
 被调函数  :

 修改历史     :
 1.日    期   : 2013年12月24日
   作    者   : z00161729
   修改内容   : SVLTE支持NCELL搜网

*****************************************************************************/
VOS_VOID  NAS_MMC_ResetCurNcellSearchTimerCount_OnPlmn(VOS_VOID)
{
    /* 如果当前状态机不是L1 MAIN */
    if (NAS_MMC_FSM_L1_MAIN != NAS_MMC_GetCurrFsmId())
    {
        NAS_ERROR_LOG(WUEPS_PID_MMC, "NAS_MMC_ResetCurNcellSearchTimerCount_L1Main,ERROR:FsmId Error");

        return;
    }

    g_stNasMmcCtx.stCurFsm.unFsmCtx.stL1MainCtx.ulCurNcellSearchTimerCount = 0;
}

/*****************************************************************************
 函 数 名  : NAS_MMC_AddCurNcellSearchTimerCount_OnPlmn
 功能描述  : 递增 ncell 搜网当前启动的次数
 输入参数  : 无
 输出参数  : 无
 返 回 值  : VOS_UINT32
 调用函数  :
 被调函数  :

 修改历史     :
 1.日    期   : 2013年12月24日
   作    者   : z00161729
   修改内容   : SVLTE支持NCELL搜网

*****************************************************************************/
VOS_VOID  NAS_MMC_AddCurNcellSearchTimerCount_OnPlmn(VOS_VOID)
{
    /* 如果当前状态机不是L1 MAIN */
    if (NAS_MMC_FSM_L1_MAIN != NAS_MMC_GetCurrFsmId())
    {
        NAS_ERROR_LOG(WUEPS_PID_MMC, "NAS_MMC_AddCurNcellSearchTimerCount_L1Main,ERROR:FsmId Error");

        return;
    }

    g_stNasMmcCtx.stCurFsm.unFsmCtx.stL1MainCtx.ulCurNcellSearchTimerCount++;
}


/*****************************************************************************
 函 数 名  : NAS_MMC_GetCurHistorySearchTimerCount_OnPlmn
 功能描述  : 获取history搜索当前启动的次数
 输入参数  : 无
 输出参数  : 无
 返 回 值  : VOS_UINT32
 调用函数  :
 被调函数  :

 修改历史     :
  1.日    期   : 2015年6月4日
    作    者   : s00217060
    修改内容   : 新生成函数

*****************************************************************************/
VOS_UINT32  NAS_MMC_GetCurHistorySearchTimerCount_OnPlmn(VOS_VOID)
{
    /* 如果当前状态机不是L1 MAIN */
    if (NAS_MMC_FSM_L1_MAIN != NAS_MMC_GetCurrFsmId())
    {
        NAS_ERROR_LOG(WUEPS_PID_MMC, "NAS_MMC_GetCurHistorySearchTimerCount_OnPlmn,ERROR:FsmId Error");
    }

    return g_stNasMmcCtx.stCurFsm.unFsmCtx.stL1MainCtx.ulCurHistorySearchTimerCount;
}

/*****************************************************************************
 函 数 名  : NAS_MMC_SetCurHistorySearchTimerCount_OnPlmn
 功能描述  : 设置history搜索当前启动的次数
 输入参数  : 无
 输出参数  : 无
 返 回 值  : VOS_UINT32
 调用函数  :
 被调函数  :

 修改历史     :
  1.日    期   : 2015年6月4日
    作    者   : s00217060
    修改内容   : 新生成函数

*****************************************************************************/
VOS_VOID  NAS_MMC_SetCurHistorySearchTimerCount(
    VOS_UINT32                          ulCurHistorySearchTimerCount
)
{
    g_stNasMmcCtx.stCurFsm.unFsmCtx.stL1MainCtx.ulCurHistorySearchTimerCount = ulCurHistorySearchTimerCount;
}


/*****************************************************************************
 函 数 名  : NAS_MMC_ResetCurHistorySearchTimerCount_OnPlmn
 功能描述  : 重置history搜定时器次数
 输入参数  : VOS_VOID
 输出参数  : 无
 返 回 值  : VOS_VOID
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2015年5月25日
    作    者   : s00217060
    修改内容   : 新生成函数

*****************************************************************************/
VOS_VOID NAS_MMC_ResetCurHistorySearchTimerCount_OnPlmn(VOS_VOID)
{
    /* 如果当前状态机不是L1 MAIN */
    if (NAS_MMC_FSM_L1_MAIN != NAS_MMC_GetCurrFsmId())
    {
        NAS_ERROR_LOG(WUEPS_PID_MMC, "NAS_MMC_ResetCurHistorySearchTimerCount_OnPlmn,ERROR:FsmId Error");

        return;
    }

    g_stNasMmcCtx.stCurFsm.unFsmCtx.stL1MainCtx.ulCurHistorySearchTimerCount = 0;

    return;
}

/*****************************************************************************
 函 数 名  : NAS_MMC_AddCurHistorySearchTimerCount_OnPlmn
 功能描述  : 递增 history 搜网当前启动的次数
 输入参数  : 无
 输出参数  : 无
 返 回 值  : VOS_UINT32
 调用函数  :
 被调函数  :

 修改历史     :
  1.日    期   : 2015年5月25日
    作    者   : s00217060
    修改内容   : 新生成函数

*****************************************************************************/
VOS_VOID  NAS_MMC_AddCurHistorySearchTimerCount_OnPlmn(VOS_VOID)
{
    /* 如果当前状态机不是L1 MAIN */
    if (NAS_MMC_FSM_L1_MAIN != NAS_MMC_GetCurrFsmId())
    {
        NAS_ERROR_LOG(WUEPS_PID_MMC, "NAS_MMC_AddCurHistorySearchTimerCount_OnPlmn,ERROR:FsmId Error");

        return;
    }

    g_stNasMmcCtx.stCurFsm.unFsmCtx.stL1MainCtx.ulCurHistorySearchTimerCount++;

    return;
}


/*****************************************************************************
 函 数 名  : NAS_MMC_ResetOosPlmnSearchTimerCount_OnPlmn
 功能描述  : 清除所有PLMN Search相关定时器的计数值
 输入参数  : 无
 输出参数  : 无
 返 回 值  : VOS_VOID
 调用函数  :
 被调函数  :

 修改历史     :
  1.日    期   : 2015年11月05日
    作    者   : d00305650
    修改内容   : 新生成函数
*****************************************************************************/
VOS_VOID NAS_MMC_ResetOosPlmnSearchTimerCount_OnPlmn(VOS_VOID)
{

    /* 如果当前状态机不是L1 MAIN */
    if (NAS_MMC_FSM_L1_MAIN != NAS_MMC_GetCurrFsmId())
    {
        NAS_ERROR_LOG(WUEPS_PID_MMC, "NAS_MMC_ResetOosPlmnSearchTimerCount_OnPlmn,ERROR:FsmId Error");

        return;
    }

    /* Reset Normal Available Timer Count */
    g_stNasMmcCtx.stCurFsm.unFsmCtx.stL1MainCtx.ulCurTimerCount                 = 0;
    /* Reset NCell Timer Count */
    g_stNasMmcCtx.stCurFsm.unFsmCtx.stL1MainCtx.ulCurNcellSearchTimerCount      = 0;
    /* Reset History Timer Count */
    g_stNasMmcCtx.stCurFsm.unFsmCtx.stL1MainCtx.ulCurHistorySearchTimerCount    = 0;
    /* Reset PrefBand Timer Count */
    g_stNasMmcCtx.stCurFsm.unFsmCtx.stL1MainCtx.ulCurPrefBandSearchTimerCount   = 0;
    /* Reset OOS Phase Num */
    NAS_MMC_GetMmcCtxAddr()->stPlmnSearchCtrl.stOosPlmnSearchStrategyInfo.enNextOosSearchPhaseNum = NAS_MMC_OOS_PHASE_ONE;
    NAS_MMC_GetMmcCtxAddr()->stPlmnSearchCtrl.stOosPlmnSearchStrategyInfo.enCurrOosSearchPhaseNum = NAS_MMC_OOS_PHASE_ONE;

    return;
}
/*****************************************************************************
 函 数 名  : NAS_MMC_GetCurPrefBandSearchTimerCount_OnPlmn
 功能描述  : 获取PrefBand搜索当前启动的次数
 输入参数  : 无
 输出参数  : 无
 返 回 值  : VOS_UINT32
 调用函数  :
 被调函数  :

 修改历史     :
  1.日    期   : 2015年10月12日
    作    者   : h00281185
    修改内容   : 新生成函数

*****************************************************************************/
VOS_UINT32  NAS_MMC_GetCurPrefBandSearchTimerCount_OnPlmn(VOS_VOID)
{
    /* 如果当前状态机不是L1 MAIN */
    if (NAS_MMC_FSM_L1_MAIN != NAS_MMC_GetCurrFsmId())
    {
        NAS_ERROR_LOG(WUEPS_PID_MMC, "NAS_MMC_GetCurPrefBandSearchTimerCount_OnPlmn,ERROR:FsmId Error");
    }

    return g_stNasMmcCtx.stCurFsm.unFsmCtx.stL1MainCtx.ulCurPrefBandSearchTimerCount;
}

/*****************************************************************************
 函 数 名  : NAS_MMC_SetCurPrefBandSearchTimerCount_OnPlmn
 功能描述  : 设置PrefBand搜索当前启动的次数
 输入参数  : 无
 输出参数  : 无
 返 回 值  : VOS_UINT32
 调用函数  :
 被调函数  :

 修改历史     :
  1.日    期   : 2015年10月12日
    作    者   : h00281185
    修改内容   : 新生成函数

*****************************************************************************/
VOS_VOID  NAS_MMC_SetCurPrefBandSearchTimerCount(
    VOS_UINT32                          ulCurPrefBandSearchTimerCount
)
{
    g_stNasMmcCtx.stCurFsm.unFsmCtx.stL1MainCtx.ulCurPrefBandSearchTimerCount = ulCurPrefBandSearchTimerCount;
}


/*****************************************************************************
 函 数 名  : NAS_MMC_ResetCurPrefBandSearchTimerCount_OnPlmn
 功能描述  : 重置PrefBand搜定时器次数
 输入参数  : VOS_VOID
 输出参数  : 无
 返 回 值  : VOS_VOID
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2015年10月12日
    作    者   : h00281185
    修改内容   : 新生成函数

*****************************************************************************/
VOS_VOID NAS_MMC_ResetCurPrefBandSearchTimerCount_OnPlmn(VOS_VOID)
{
    /* 如果当前状态机不是L1 MAIN */
    if (NAS_MMC_FSM_L1_MAIN != NAS_MMC_GetCurrFsmId())
    {
        NAS_ERROR_LOG(WUEPS_PID_MMC, "NAS_MMC_ResetCurPrefBandSearchTimerCount_OnPlmn,ERROR:FsmId Error");

        return;
    }

    g_stNasMmcCtx.stCurFsm.unFsmCtx.stL1MainCtx.ulCurPrefBandSearchTimerCount = 0;

    return;
}

/*****************************************************************************
 函 数 名  : NAS_MMC_AddCurPrefBandSearchTimerCount_OnPlmn
 功能描述  : 递增 PrefBand 搜网当前启动的次数
 输入参数  : 无
 输出参数  : 无
 返 回 值  : VOS_UINT32
 调用函数  :
 被调函数  :

 修改历史     :
  1.日    期   : 2015年10月12日
    作    者   : h00281185
    修改内容   : 新生成函数

*****************************************************************************/
VOS_VOID  NAS_MMC_AddCurPrefBandSearchTimerCount_OnPlmn(VOS_VOID)
{
    /* 如果当前状态机不是L1 MAIN */
    if (NAS_MMC_FSM_L1_MAIN != NAS_MMC_GetCurrFsmId())
    {
        NAS_ERROR_LOG(WUEPS_PID_MMC, "NAS_MMC_AddCurPrefBandSearchTimerCount_OnPlmn,ERROR:FsmId Error");

        return;
    }

    g_stNasMmcCtx.stCurFsm.unFsmCtx.stL1MainCtx.ulCurPrefBandSearchTimerCount++;

    return;
}

/*****************************************************************************
 函 数 名  : NAS_MMC_GetOosCurInfo
 功能描述  : 获得当前OOS状态history timer/prefband timer/fullband timer启动的次数
 输入参数  : NSA_MML_OOS_INFO_STRU              *pstOosInfo;

 输出参数  : 无
 返 回 值  : VOS_VOID
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2015年12月1日
    作    者   : n00355355
    修改内容   : 新生成函数

*****************************************************************************/
VOS_VOID NAS_MMC_GetOosCurInfo(
    NAS_MML_OOS_INFO_STRU              *pstOosInfo
)
{
    NAS_MMC_FSM_CTX_STRU               *pstL1MainFsm = VOS_NULL_PTR;

    /* 当前在NAS_MMC_FSM_L1_MAIN状态机 */
    if (NAS_MMC_FSM_L1_MAIN == NAS_MMC_GetCurrFsmId())
    {
        pstOosInfo->ucCurOosPhaseNum          = NAS_MMC_GetCurrOosSearchPhaseNum();
        pstOosInfo->ulCurHistoryTimerCount    = NAS_MMC_GetCurHistorySearchTimerCount_OnPlmn();
        pstOosInfo->ulCurPrefBandTimerCount   = NAS_MMC_GetCurPrefBandSearchTimerCount_OnPlmn();
        pstOosInfo->ulCurFullBandTimerCount   = NAS_MMC_GetCurNormalAvailableTimerCount_L1Main();
        return;
    }

    /* 当前不在NAS_MMC_FSM_L1_MAIN状态机，去栈中获取NAS_MMC_FSM_L1_MAIN的内容 */
    pstL1MainFsm = NAS_MMC_GetBottomFsmInFsmStack();

    if (VOS_NULL_PTR == pstL1MainFsm)
    {
        pstOosInfo->ucCurOosPhaseNum = NAS_MMC_OOS_PHASE_BUTT;
        return;
    }

    pstOosInfo->ucCurOosPhaseNum        = NAS_MMC_GetCurrOosSearchPhaseNum();
    pstOosInfo->ulCurHistoryTimerCount  = pstL1MainFsm->unFsmCtx.stL1MainCtx.ulCurHistorySearchTimerCount;
    pstOosInfo->ulCurPrefBandTimerCount = pstL1MainFsm->unFsmCtx.stL1MainCtx.ulCurPrefBandSearchTimerCount;
    pstOosInfo->ulCurFullBandTimerCount = pstL1MainFsm->unFsmCtx.stL1MainCtx.ulCurTimerCount;

    return;
}


/*****************************************************************************
 函 数 名  : NAS_MMC_GetCsRegAdditionalAction_L1Main
 功能描述  : 获取状态机上下文中的CS注册结果触发的后续动作
 输入参数  : 无
 输出参数  : 无
 返 回 值  : NAS_MMC_ADDITIONAL_ACTION_ENUM_UINT8
 调用函数  :
 被调函数  :

 修改历史     :
 1.日    期   : 2011年7月28日
   作    者   : w00176964
   修改内容   : 新生成函数

 2.日    期   : 2011年10月13日
   作    者   : w00176964
   修改内容   : 内部列表搜网调整L1 MAIN上下文结构
*****************************************************************************/
NAS_MMC_ADDITIONAL_ACTION_ENUM_UINT8 NAS_MMC_GetCsRegAdditionalAction_L1Main(VOS_VOID)
{

    /* 如果当前状态机不是L1 MAIN */
    if (NAS_MMC_FSM_L1_MAIN != NAS_MMC_GetCurrFsmId())
    {
        NAS_ERROR_LOG(WUEPS_PID_MMC, "NAS_MMC_GetCsRegAdditionalAction_L1Main,ERROR:FsmId Error");
    }

    return g_stNasMmcCtx.stCurFsm.unFsmCtx.stL1MainCtx.stRegRsltInfo.enCsRegAdditionalAction;
}

/*****************************************************************************
 函 数 名  : NAS_MMC_SetCsRegAdditionalAction_L1Main
 功能描述  : 设置状态机上下文中的CS注册结果触发的后续动作
 输入参数  : NAS_MMC_ADDITIONAL_ACTION_ENUM_UINT8
 输出参数  : 无
 返 回 值  : VOS_VOID
 调用函数  :
 被调函数  :

 修改历史     :
 1.日    期   : 2011年7月28日
   作    者   : w00176964
   修改内容   : 新生成函数

 2.日    期   : 2011年10月13日
   作    者   : w00176964
   修改内容   : 内部列表搜网调整L1 MAIN上下文结构

*****************************************************************************/
VOS_VOID NAS_MMC_SetCsRegAdditionalAction_L1Main(
    NAS_MMC_ADDITIONAL_ACTION_ENUM_UINT8 enCsAddtionalAction
)
{
    /* 如果当前状态机不是L1 MAIN */
    if (NAS_MMC_FSM_L1_MAIN != NAS_MMC_GetCurrFsmId())
    {
        NAS_ERROR_LOG(WUEPS_PID_MMC, "NAS_MMC_SetCsRegAdditionalAction_L1Main,ERROR:FsmId Error");

        return;
    }

    g_stNasMmcCtx.stCurFsm.unFsmCtx.stL1MainCtx.stRegRsltInfo.enCsRegAdditionalAction = enCsAddtionalAction;
}

/*****************************************************************************
 函 数 名  : NAS_MMC_GetPsRegAdditionalAction_L1Main
 功能描述  : 获取状态机上下文中的PS注册结果触发的后续动作
 输入参数  : 无
 输出参数  : 无
 返 回 值  : NAS_MMC_ADDITIONAL_ACTION_ENUM_UINT8
 调用函数  :
 被调函数  :

 修改历史     :
 1.日    期   : 2011年7月28日
   作    者   : w00176964
   修改内容   : 新生成函数

 2.日    期   : 2011年10月13日
   作    者   : w00176964
   修改内容   : 内部列表搜网调整L1 MAIN上下文结构

*****************************************************************************/
NAS_MMC_ADDITIONAL_ACTION_ENUM_UINT8 NAS_MMC_GetPsRegAdditionalAction_L1Main(VOS_VOID)
{
    /* 如果当前状态机不是L1 MAIN */
    if (NAS_MMC_FSM_L1_MAIN != NAS_MMC_GetCurrFsmId())
    {
        NAS_ERROR_LOG(WUEPS_PID_MMC, "NAS_MMC_GetPsRegAdditionalAction_L1Main,ERROR:FsmId Error");
    }

    return g_stNasMmcCtx.stCurFsm.unFsmCtx.stL1MainCtx.stRegRsltInfo.enPsRegAdditionalAction;
}

/*****************************************************************************
 函 数 名  : NAS_MMC_SetPsRegAdditionalAction_L1Main
 功能描述  : 设置状态机上下文中的PS注册结果触发的后续动作
 输入参数  : NAS_MMC_ADDITIONAL_ACTION_ENUM_UINT8
 输出参数  : 无
 返 回 值  : VOS_VOID
 调用函数  :
 被调函数  :

 修改历史     :
 1.日    期   : 2011年7月28日
   作    者   : w00176964
   修改内容   : 新生成函数

 2.日    期   : 2011年10月13日
   作    者   : w00176964
   修改内容   : 内部列表搜网调整L1 MAIN上下文结构

*****************************************************************************/
VOS_VOID NAS_MMC_SetPsRegAdditionalAction_L1Main(
    NAS_MMC_ADDITIONAL_ACTION_ENUM_UINT8  enPsAddtionalAction
)
{
    /* 如果当前状态机不是L1 MAIN */
    if (NAS_MMC_FSM_L1_MAIN != NAS_MMC_GetCurrFsmId())
    {
        NAS_ERROR_LOG(WUEPS_PID_MMC, "NAS_MMC_SetPsRegAdditionalAction_L1Main,ERROR:FsmId Error");

        return;
    }

    g_stNasMmcCtx.stCurFsm.unFsmCtx.stL1MainCtx.stRegRsltInfo.enPsRegAdditionalAction = enPsAddtionalAction;
}

/*****************************************************************************
 函 数 名  : NAS_MMC_GetCLRegAdditionalAction_L1Main
 功能描述  : 获取状态机上下文中的CL模式下注册结果触发的后续动作
 输入参数  : 无
 输出参数  : 无
 返 回 值  : NAS_MMC_CL_ADDITIONAL_ACTION_ENUM_UINT8
 调用函数  :
 被调函数  :

 修改历史     :
 1.日    期   : 2016年1月18日
   作    者   : w00176964
   修改内容   : 新生成函数
*****************************************************************************/
NAS_MMC_CL_ADDITIONAL_ACTION_ENUM_UINT8 NAS_MMC_GetCLRegAdditionalAction_L1Main(VOS_VOID)
{

    /* 如果当前状态机不是L1 MAIN */
    if (NAS_MMC_FSM_L1_MAIN != NAS_MMC_GetCurrFsmId())
    {
        NAS_ERROR_LOG(WUEPS_PID_MMC, "NAS_MMC_GetCLRegAdditionalAction_L1Main,ERROR:FsmId Error");
    }

    return g_stNasMmcCtx.stCurFsm.unFsmCtx.stL1MainCtx.stRegRsltInfo.enCLRegAdditionalAction;
}

/*****************************************************************************
 函 数 名  : NAS_MMC_SetCLRegAdditionalAction_L1Main
 功能描述  : 设置状态机上下文中的CL模式下注册结果触发的后续动作
 输入参数  : NAS_MMC_CL_ADDITIONAL_ACTION_ENUM_UINT8
 输出参数  : 无
 返 回 值  : VOS_VOID
 调用函数  :
 被调函数  :

 修改历史     :
 1.日    期   : 2016年1月16日
   作    者   : w00176964
   修改内容   : 新生成函数
*****************************************************************************/
VOS_VOID NAS_MMC_SetCLRegAdditionalAction_L1Main(
    NAS_MMC_CL_ADDITIONAL_ACTION_ENUM_UINT8                 enCLRegAdditionalAction
)
{
    /* 如果当前状态机不是L1 MAIN */
    if (NAS_MMC_FSM_L1_MAIN != NAS_MMC_GetCurrFsmId())
    {
        NAS_ERROR_LOG(WUEPS_PID_MMC, "NAS_MMC_SetCLRegAdditionalAction_L1Main,ERROR:FsmId Error");

        return;
    }

    g_stNasMmcCtx.stCurFsm.unFsmCtx.stL1MainCtx.stRegRsltInfo.enCLRegAdditionalAction = enCLRegAdditionalAction;
}


/*****************************************************************************
 函 数 名  : NAS_MMC_ClearAllRegAdditionalAction_L1Main
 功能描述  : 清除状态机上下文中的CS/PS注册结果触发的后续动作
 输入参数  : 无
 输出参数  : 无
 返 回 值  : VOS_VOID
 调用函数  :
 被调函数  :

 修改历史     :
 1.日    期   : 2011年8月05日
   作    者   : w00176964
   修改内容   : 新生成函数

 2.日    期   : 2011年10月13日
   作    者   : w00176964
   修改内容   : 内部列表搜网调整L1 MAIN上下文结构

 3.日    期   : 2016年1月18日
   作    者   : w00176964
   修改内容   : DTS2016011802320调整:增加CL模式下的后续动作
*****************************************************************************/
VOS_VOID NAS_MMC_ClearAllRegAdditionalAction_L1Main(VOS_VOID)
{
    /* 如果当前状态机不是L1 MAIN */
    if (NAS_MMC_FSM_L1_MAIN != NAS_MMC_GetCurrFsmId())
    {
        NAS_ERROR_LOG(WUEPS_PID_MMC, "NAS_MMC_ClearAllRegAdditionalAction_L1Main,ERROR:FsmId Error");

        return;
    }

    g_stNasMmcCtx.stCurFsm.unFsmCtx.stL1MainCtx.stRegRsltInfo.enCsRegAdditionalAction = NAS_MMC_ADDITIONAL_ACTION_BUTT;
    g_stNasMmcCtx.stCurFsm.unFsmCtx.stL1MainCtx.stRegRsltInfo.enPsRegAdditionalAction = NAS_MMC_ADDITIONAL_ACTION_BUTT;
    g_stNasMmcCtx.stCurFsm.unFsmCtx.stL1MainCtx.stRegRsltInfo.enCLRegAdditionalAction = NAS_MMC_CL_ADDITIONAL_ACTION_BUTT;

}

/*****************************************************************************
 函 数 名  : NAS_MMC_SetCsRegAttemptCount_L1Main
 功能描述  : 设置状态机上下文中的CS注册尝试次数
 输入参数  : ulCsCount CS注册尝试次数
 输出参数  : 无
 返 回 值  : VOS_VOID
 调用函数  :
 被调函数  :

 修改历史     :
 1.日    期   : 2011年10月13日
   作    者   : w00176964
   修改内容   : 新生成函数

*****************************************************************************/
VOS_VOID NAS_MMC_SetCsRegAttemptCount_L1Main(
    VOS_UINT32      ulCsCount
)
{
    /* 如果当前状态机不是L1 MAIN */
    if (NAS_MMC_FSM_L1_MAIN != NAS_MMC_GetCurrFsmId())
    {
        NAS_ERROR_LOG(WUEPS_PID_MMC, "NAS_MMC_SetCsRegAttemptCount_L1Main,ERROR:FsmId Error");

        return;
    }

    g_stNasMmcCtx.stCurFsm.unFsmCtx.stL1MainCtx.stRegRsltInfo.ulCsAttemptCount = ulCsCount;
}

/*****************************************************************************
 函 数 名  : NAS_MMC_SetPsRegAttemptCount_L1Main
 功能描述  : 设置状态机上下文中的PS注册尝试次数
 输入参数  : ulPsCount PS注册尝试次数
 输出参数  : 无
 返 回 值  : VOS_VOID
 调用函数  :
 被调函数  :

 修改历史     :
 1.日    期   : 2011年10月13日
   作    者   : w00176964
   修改内容   : 新生成函数

*****************************************************************************/
VOS_VOID NAS_MMC_SetPsRegAttemptCount_L1Main(
    VOS_UINT32      ulPsCount
)
{
    /* 如果当前状态机不是L1 MAIN */
    if (NAS_MMC_FSM_L1_MAIN != NAS_MMC_GetCurrFsmId())
    {
        NAS_ERROR_LOG(WUEPS_PID_MMC, "NAS_MMC_SetPsRegAttemptCount_L1Main,ERROR:FsmId Error");

        return;
    }

    g_stNasMmcCtx.stCurFsm.unFsmCtx.stL1MainCtx.stRegRsltInfo.ulPsAttemptCount = ulPsCount;
}

/*****************************************************************************
 函 数 名  : NAS_MMC_GetCsRegAttemptCount_L1Main
 功能描述  : 获取状态机上下文中的CS注册尝试次数
 输入参数  : 无
 输出参数  : 无
 返 回 值  : CS注册尝试次数
 调用函数  :
 被调函数  :

 修改历史     :
 1.日    期   : 2011年10月13日
   作    者   : w00176964
   修改内容   : 新生成函数

*****************************************************************************/
VOS_UINT32 NAS_MMC_GetCsRegAttemptCount_L1Main(VOS_VOID)
{
    /* 如果当前状态机不是L1 MAIN */
    if (NAS_MMC_FSM_L1_MAIN != NAS_MMC_GetCurrFsmId())
    {
        NAS_ERROR_LOG(WUEPS_PID_MMC, "NAS_MMC_GetCsRegAttemptCount_L1Main,ERROR:FsmId Error");
    }

    return g_stNasMmcCtx.stCurFsm.unFsmCtx.stL1MainCtx.stRegRsltInfo.ulCsAttemptCount;
}


/*****************************************************************************
 函 数 名  : NAS_MMC_GetPsRegAttemptCount_L1Main
 功能描述  : 获取状态机上下文中的PS注册尝试次数
 输入参数  : 无
 输出参数  : 无
 返 回 值  : PS注册尝试次数
 调用函数  :
 被调函数  :

 修改历史     :
 1.日    期   : 2011年10月13日
   作    者   : w00176964
   修改内容   : 新生成函数

*****************************************************************************/
VOS_UINT32 NAS_MMC_GetPsRegAttemptCount_L1Main(VOS_VOID)
{
    /* 如果当前状态机不是L1 MAIN */
    if (NAS_MMC_FSM_L1_MAIN != NAS_MMC_GetCurrFsmId())
    {
        NAS_ERROR_LOG(WUEPS_PID_MMC, "NAS_MMC_GetPsRegAttemptCount_L1Main,ERROR:FsmId Error");
    }

    return g_stNasMmcCtx.stCurFsm.unFsmCtx.stL1MainCtx.stRegRsltInfo.ulPsAttemptCount;
}


/*****************************************************************************
 函 数 名  : NAS_MMC_ClearAllRegAttemptCount_L1Main
 功能描述  : 清除状态机上下文中的CS/PS注册尝试次数
 输入参数  : 无
 输出参数  : 无
 返 回 值  : VOS_VOID
 调用函数  :
 被调函数  :

 修改历史     :
 1.日    期   : 2011年10月13日
   作    者   : w00176964
   修改内容   : 新生成函数

*****************************************************************************/
VOS_VOID NAS_MMC_ClearAllRegAttemptCount_L1Main(VOS_VOID)
{
    /* 如果当前状态机不是L1 MAIN */
    if (NAS_MMC_FSM_L1_MAIN != NAS_MMC_GetCurrFsmId())
    {
        NAS_ERROR_LOG(WUEPS_PID_MMC, "NAS_MMC_ClearAllRegAttemptCount_L1Main,ERROR:FsmId Error");

        return;
    }

    g_stNasMmcCtx.stCurFsm.unFsmCtx.stL1MainCtx.stRegRsltInfo.ulCsAttemptCount = 0;
    g_stNasMmcCtx.stCurFsm.unFsmCtx.stL1MainCtx.stRegRsltInfo.ulPsAttemptCount = 0;
}

/*************************************** 开机相关状态机上下文操作函数 *************************************************/

/*****************************************************************************
 函 数 名  : NAS_MMC_GetWaitMmStartCnfFlg_SwitchOn
 功能描述  : 开机过程中获取MM模块开机回复标记
 输入参数  : 无
 输出参数  : 无
 返 回 值  : MM模块开机回复标记
 调用函数  :
 被调函数  :
 修改历史      :
  1.日    期   : 2011-07-11
    作    者   : w00176964
    修改内容   : 新生成函数
*****************************************************************************/

NAS_MMC_WAIT_MM_START_CNF_ENUM_UINT8    NAS_MMC_GetWaitMmStartCnfFlg_SwitchOn(VOS_VOID)
{
    /* 如果当前状态机不是switch on */
    if (NAS_MMC_FSM_SWITCH_ON != NAS_MMC_GetCurrFsmId())
    {
        /* 异常事件 */
        NAS_WARNING_LOG(WUEPS_PID_MMC, "NAS_MMC_GetWaitMmStartCnfFlg_SwitchOn:ENTERED");
    }

    return g_stNasMmcCtx.stCurFsm.unFsmCtx.stSwitchOnCtx.ucMmcMmStartCnfFlg;
}


/*****************************************************************************
 函 数 名  : NAS_MMC_GetWaitSimFilesCnfFlg_SwitchOn
 功能描述  : 开机过程中获取读取SIM卡文件回复标记
 输入参数  : 无
 输出参数  : 无
 返 回 值  : 读取SIM卡文件回复标记
 调用函数  :
 被调函数  :
 修改历史      :
  1.日    期   : 2011-07-11
    作    者   : w00176964
    修改内容   : 新生成函数
*****************************************************************************/
NAS_MML_READ_SIM_FILES_CNF_ENUM_UINT32   NAS_MMC_GetWaitSimFilesCnfFlg_SwitchOn(VOS_VOID)
{
    /* 如果当前状态机不是switch on */
    if (NAS_MMC_FSM_SWITCH_ON != NAS_MMC_GetCurrFsmId())
    {
        /* 异常事件 */
        NAS_WARNING_LOG(WUEPS_PID_MMC, "NAS_MMC_GetWaitSimFilesFlg_SwitchOn:ENTERED");
    }

    return g_stNasMmcCtx.stCurFsm.unFsmCtx.stSwitchOnCtx.ulMmcReadSimFileFlg;
}

/*****************************************************************************
 函 数 名  : NAS_MMC_ClearMmStartCnfFlg_SwitchOn
 功能描述  : 开机过程中清除MM/GMM的开机回复标记
 输入参数  : MM/GMM开机回复标记
 输出参数  : 无
 返 回 值  : 无
 调用函数  :
 被调函数  :
 修改历史      :
  1.日    期   : 2011-07-11
    作    者   : w00176964
    修改内容   : 新生成函数
*****************************************************************************/
VOS_VOID    NAS_MMC_ClearMmStartCnfFlg_SwitchOn(
    NAS_MMC_WAIT_MM_START_CNF_ENUM_UINT8                    enMmStartCnfFlg
)
{
    /* 如果当前状态机不是switch on */
    if (NAS_MMC_FSM_SWITCH_ON != NAS_MMC_GetCurrFsmId())
    {
        /* 异常事件 */
        NAS_WARNING_LOG(WUEPS_PID_MMC, "NAS_MMC_ClearMmStartCnfFlg_SwitchOn:ENTERED");

        return;
    }

    g_stNasMmcCtx.stCurFsm.unFsmCtx.stSwitchOnCtx.ucMmcMmStartCnfFlg &= ~enMmStartCnfFlg;
}

/*****************************************************************************
 函 数 名  : NAS_MMC_ClearAllWaitMmStartCnfFlg_SwitchOn
 功能描述  : 开机过程中清除MM和GMM的开机回复标记
 输入参数  : 无
 输出参数  : 无
 返 回 值  : 无
 调用函数  :
 被调函数  :
 修改历史      :
  1.日    期   : 2011-07-11
    作    者   : w00176964
    修改内容   : 新生成函数
*****************************************************************************/
VOS_VOID    NAS_MMC_ClearAllWaitMmStartCnfFlg_SwitchOn(VOS_VOID)
{
    /* 如果当前状态机不是switch on */
    if (NAS_MMC_FSM_SWITCH_ON != NAS_MMC_GetCurrFsmId())
    {
        /* 异常事件 */
        NAS_WARNING_LOG(WUEPS_PID_MMC, "NAS_MMC_ClearAllWaitMmStartCnfFlg_SwitchOn:ENTERED");

        return;
    }

    g_stNasMmcCtx.stCurFsm.unFsmCtx.stSwitchOnCtx.ucMmcMmStartCnfFlg = NAS_MMC_WAIT_MMGMM_START_CNF_NULL;
}



/*****************************************************************************
 函 数 名  : NAS_MMC_ClearAllAsStartCnfFlg_SwitchOn
 功能描述  : 开机过程中清除读取SIM卡文件回复标记
 输入参数  : SIM卡文件回复标记
 输出参数  : 无
 返 回 值  : 无
 调用函数  :
 被调函数  :
 修改历史      :
  1.日    期   : 2011-07-11
    作    者   : w00176964
    修改内容   : 新生成函数
*****************************************************************************/
VOS_VOID    NAS_MMC_ClearWaitSimFilesCnfFlg_SwitchOn(
    NAS_MML_READ_SIM_FILES_CNF_ENUM_UINT32                   enSimFileCnfFlg
)
{
    /* 如果当前状态机不是switch on */
    if (NAS_MMC_FSM_SWITCH_ON != NAS_MMC_GetCurrFsmId())
    {
        /* 异常事件 */
        NAS_WARNING_LOG(WUEPS_PID_MMC, "NAS_MMC_ClearWaitSimFilesCnfFlg_SwitchOn:ENTERED");

        return;
    }

    g_stNasMmcCtx.stCurFsm.unFsmCtx.stSwitchOnCtx.ulMmcReadSimFileFlg &= ~enSimFileCnfFlg;
}

/*****************************************************************************
 函 数 名  : NAS_MMC_ClearAllWaitSimFilesFlg_SwitchOn
 功能描述  : 开机过程中清除所有读取SIM卡文件回复标记
 输入参数  : 无
 输出参数  : 无
 返 回 值  : 无
 调用函数  :
 被调函数  :
 修改历史      :
  1.日    期   : 2011-07-11
    作    者   : w00176964
    修改内容   : 新生成函数
*****************************************************************************/
VOS_VOID    NAS_MMC_ClearAllWaitSimFilesCnfFlg_SwitchOn(VOS_VOID)
{
    /* 如果当前状态机不是switch on */
    if (NAS_MMC_FSM_SWITCH_ON != NAS_MMC_GetCurrFsmId())
    {
        /* 异常事件 */
        NAS_WARNING_LOG(WUEPS_PID_MMC, "NAS_MMC_ClearAllWaitSimFilesFlg_SwitchOn:ENTERED");

        return;
    }

    g_stNasMmcCtx.stCurFsm.unFsmCtx.stSwitchOnCtx.ulMmcReadSimFileFlg = NAS_MML_READ_USIM_FILE_FLG_NULL;
}

/*****************************************************************************
 函 数 名  : NAS_MMC_SetWaitMmStartCnfFlg_SwitchOn
 功能描述  : 开机过程中设置MM/GMM模块开机回复标记
 输入参数  : MM/GMM模块开机回复标记
 输出参数  : 无
 返 回 值  : 无
 调用函数  :
 被调函数  :
 修改历史      :
  1.日    期   : 2011-07-11
    作    者   : w00176964
    修改内容   : 新生成函数
*****************************************************************************/
VOS_VOID    NAS_MMC_SetWaitMmStartCnfFlg_SwitchOn(
    NAS_MMC_WAIT_MM_START_CNF_ENUM_UINT8                    enMmStartCnfFlg
)
{
    /* 如果当前状态机不是switch on */
    if (NAS_MMC_FSM_SWITCH_ON != NAS_MMC_GetCurrFsmId())
    {
        /* 异常事件 */
        NAS_WARNING_LOG(WUEPS_PID_MMC, "NAS_MMC_SetWaitMmStartCnfFlg_SwitchOn:ENTERED");

        return;
    }

    g_stNasMmcCtx.stCurFsm.unFsmCtx.stSwitchOnCtx.ucMmcMmStartCnfFlg |= enMmStartCnfFlg;
}

/*****************************************************************************
 函 数 名  : NAS_MMC_SetWaitSimFilesCnfFlg_SwitchOn
 功能描述  : 开机过程中设置SIM卡文件回复标记
 输入参数  : SIM卡文件回复标记
 输出参数  : 无
 返 回 值  : 无
 调用函数  :
 被调函数  :
 修改历史      :
  1.日    期   : 2011-07-11
    作    者   : w00176964
    修改内容   : 新生成函数
*****************************************************************************/
VOS_VOID    NAS_MMC_SetWaitSimFilesCnfFlg_SwitchOn(
    NAS_MML_READ_SIM_FILES_CNF_ENUM_UINT32                   enSimFileCnfFlg
)
{
    /* 如果当前状态机不是switch on */
    if (NAS_MMC_FSM_SWITCH_ON != NAS_MMC_GetCurrFsmId())
    {
        /* 异常事件 */
        NAS_WARNING_LOG(WUEPS_PID_MMC, "NAS_MMC_SetWaitSimFilesCnfFlg_SwitchOn:ENTERED");

        return;
    }

    g_stNasMmcCtx.stCurFsm.unFsmCtx.stSwitchOnCtx.ulMmcReadSimFileFlg |= enSimFileCnfFlg;
}

/*************************************** 关机相关状态机上下文操作函数 *************************************************/
/*****************************************************************************
 函 数 名  : NAS_MMC_GetMmPowerOffCnfFlg_PowerOff
 功能描述  : 无
 输入参数  : 无
 输出参数  : 无
 返 回 值  : MM/GMM模块关机回复标记
 调用函数  :
 被调函数  :
 修改历史      :
  1.日    期   : 2011-07-11
    作    者   : w00176964
    修改内容   : 新生成函数
*****************************************************************************/
NAS_MMC_MM_POWEROFF_FLAG_ENUM_UINT8     NAS_MMC_GetMmPowerOffCnfFlg_PowerOff(VOS_VOID)
{
    /* 如果当前状态机不是power off */
    if (NAS_MMC_FSM_POWER_OFF != NAS_MMC_GetCurrFsmId())
    {
        /* 异常事件 */
        NAS_WARNING_LOG(WUEPS_PID_MMC, "NAS_MMC_GetMmPowerOffCnfFlg_PowerOff:ENTERED");
    }

    return  g_stNasMmcCtx.stCurFsm.unFsmCtx.stPowerOffCtx.ucMmcMmPowerOffCnfFlg;
}

/*****************************************************************************
 函 数 名  : NAS_MMC_GetAsPowerOffCnfFlg_PowerOff
 功能描述  : 无
 输入参数  : 无
 输出参数  : 无
 返 回 值  : 接入层关机回复标记
 调用函数  :
 被调函数  :
 修改历史      :
  1.日    期   : 2011-07-11
    作    者   : w00176964
    修改内容   : 新生成函数
*****************************************************************************/
NAS_MMC_AS_POWEROFF_FLAG_ENUM_UINT8     NAS_MMC_GetAsPowerOffCnfFlg_PowerOff(VOS_VOID)
{
    /* 如果当前状态机不是power off */
    if (NAS_MMC_FSM_POWER_OFF != NAS_MMC_GetCurrFsmId())
    {
        /* 异常事件 */
        NAS_WARNING_LOG(WUEPS_PID_MMC, "NAS_MMC_GetAsPowerOffCnfFlg_PowerOff:ENTERED");
    }

    return  g_stNasMmcCtx.stCurFsm.unFsmCtx.stPowerOffCtx.ucMmcAsPowerOffCnfFlg;
}

/*****************************************************************************
 函 数 名  : NAS_MMC_SetMmPowerOffCnfFlag_PowerOff
 功能描述  : 设置MM/GMM模块关机回复标记
 输入参数  : MM/GMM模块关机回复标记
 输出参数  : 无
 返 回 值  : 无
 调用函数  :
 被调函数  :
 修改历史      :
  1.日    期   : 2011-07-11
    作    者   : w00176964
    修改内容   : 新生成函数
*****************************************************************************/
VOS_VOID    NAS_MMC_SetMmPowerOffCnfFlag_PowerOff(
    NAS_MMC_MM_POWEROFF_FLAG_ENUM_UINT8                     enMmPowerOffFlg
)
{
    /* 如果当前状态机不是power off */
    if (NAS_MMC_FSM_POWER_OFF != NAS_MMC_GetCurrFsmId())
    {
        /* 异常事件 */
        NAS_WARNING_LOG(WUEPS_PID_MMC, "NAS_MMC_SetMmPowerOffCnfFlag_PowerOff:ENTERED");

        return;
    }

    g_stNasMmcCtx.stCurFsm.unFsmCtx.stPowerOffCtx.ucMmcMmPowerOffCnfFlg |= enMmPowerOffFlg;
}

/*****************************************************************************
 函 数 名  : NAS_MMC_SetAsPowerOffCnfFlag_PowerOff
 功能描述  : 设置AS模块关机回复标记
 输入参数  : AS模块关机回复标记
 输出参数  : 无
 返 回 值  : 无
 调用函数  :
 被调函数  :
 修改历史      :
  1.日    期   : 2011-07-11
    作    者   : w00176964
    修改内容   : 新生成函数
*****************************************************************************/
VOS_VOID    NAS_MMC_SetAsPowerOffCnfFlag_PowerOff(
    NAS_MMC_AS_POWEROFF_FLAG_ENUM_UINT8                     enAsPowerOffFlg
)
{
    /* 如果当前状态机不是power off */
    if (NAS_MMC_FSM_POWER_OFF != NAS_MMC_GetCurrFsmId())
    {
        /* 异常事件 */
        NAS_WARNING_LOG(WUEPS_PID_MMC, "NAS_MMC_SetAsPowerOffCnfFlag_PowerOff:ENTERED");

        return;
    }

    g_stNasMmcCtx.stCurFsm.unFsmCtx.stPowerOffCtx.ucMmcAsPowerOffCnfFlg |= enAsPowerOffFlg;
}

/*****************************************************************************
 函 数 名  : NAS_MMC_ClearMmPowerOffCnfFlag_PowerOff
 功能描述  : 清除MM/GMM模块关机回复标记
 输入参数  : MM/GMM模块关机回复标记
 输出参数  : 无
 返 回 值  : 无
 调用函数  :
 被调函数  :
 修改历史      :
  1.日    期   : 2011-07-11
    作    者   : w00176964
    修改内容   : 新生成函数
*****************************************************************************/
VOS_VOID    NAS_MMC_ClearMmPowerOffCnfFlag_PowerOff(
    NAS_MMC_MM_POWEROFF_FLAG_ENUM_UINT8                     enMmPowerOffFlg
)
{
    /* 如果当前状态机不是power off */
    if (NAS_MMC_FSM_POWER_OFF != NAS_MMC_GetCurrFsmId())
    {
        /* 异常事件 */
        NAS_WARNING_LOG(WUEPS_PID_MMC, "NAS_MMC_ClearMmPowerOffCnfFlag_PowerOff:ENTERED");

        return;
    }

    g_stNasMmcCtx.stCurFsm.unFsmCtx.stPowerOffCtx.ucMmcMmPowerOffCnfFlg &= ~enMmPowerOffFlg;
}

/*****************************************************************************
 函 数 名  : NAS_MMC_GetMasterModeRat_PowerOff
 功能描述  : 无
 输入参数  : 无
 输出参数  : 无
 返 回 值  : 接入层关机主模标记
 调用函数  :
 被调函数  :
 修改历史      :
  1.日    期   : 2011-08-17
    作    者   : w00167002
    修改内容   : 新生成函数
*****************************************************************************/
NAS_MML_NET_RAT_TYPE_ENUM_UINT8 NAS_MMC_GetMasterModeRat_PowerOff(VOS_VOID)
{
    /* 如果当前状态机不是power off */
    if (NAS_MMC_FSM_POWER_OFF != NAS_MMC_GetCurrFsmId())
    {
        /* 异常事件 */
        NAS_WARNING_LOG(WUEPS_PID_MMC, "NAS_MMC_GetMasterModeRat_PowerOff:ENTERED");
    }

    return  g_stNasMmcCtx.stCurFsm.unFsmCtx.stPowerOffCtx.enMasterModeRat;
}

/*****************************************************************************
 函 数 名  : NAS_MMC_SetMasterModeRat_PowerOff
 功能描述  : 设置关机时主模的接入技术标志
 输入参数  : MM/GMM模块关机回复标记
 输出参数  : 无
 返 回 值  : 无
 调用函数  :
 被调函数  :
 修改历史      :
  1.日    期   : 2012-08-17
    作    者   : w00167002
    修改内容   : 新生成函数
*****************************************************************************/
VOS_VOID NAS_MMC_SetMasterModeRat_PowerOff(
    NAS_MML_NET_RAT_TYPE_ENUM_UINT8     enMasterModeRat
)
{
    /* 如果当前状态机不是power off */
    if (NAS_MMC_FSM_POWER_OFF != NAS_MMC_GetCurrFsmId())
    {
        /* 异常事件 */
        NAS_WARNING_LOG(WUEPS_PID_MMC, "NAS_MMC_SetMasterModeRat_PowerOff:ENTERED");
    }

    g_stNasMmcCtx.stCurFsm.unFsmCtx.stPowerOffCtx.enMasterModeRat = enMasterModeRat;
}

/*****************************************************************************
 函 数 名  : NAS_MMC_GetSlaveModeRatList_PowerOff
 功能描述  : 获取关机状态机上下文中的从模关机个数和顺序
 输入参数  : 无
 输出参数  : 无
 返 回 值  : 接入层从模关机个数和顺序
 调用函数  :
 被调函数  :
 修改历史      :
  1.日    期   : 2012-12-26
    作    者   : s00217060
    修改内容   : 新生成函数
*****************************************************************************/
NAS_MML_PLMN_RAT_PRIO_STRU *NAS_MMC_GetSlaveModeRatList_PowerOff(VOS_VOID)
{
    /* 如果当前状态机不是power off */
    if (NAS_MMC_FSM_POWER_OFF != NAS_MMC_GetCurrFsmId())
    {
        /* 异常事件 */
        NAS_WARNING_LOG(WUEPS_PID_MMC, "NAS_MMC_GetSlaveModeRatList_PowerOff:ENTERED");
    }

    return &(NAS_MMC_GetMmcCtxAddr()->stCurFsm.unFsmCtx.stPowerOffCtx.stSlaveModeList);
}

/*****************************************************************************
 函 数 名  : NAS_MMC_BuildSlaveModeRatList_PowerOff
 功能描述  : 关机时，根据主模创建从模列表
 输入参数  : enMasterModeRat:当前主模
 输出参数  : 无
 返 回 值  : 无
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2012年12月26日
    作    者   : s00217060
    修改内容   : 新生成函数
*****************************************************************************/
VOS_VOID NAS_MMC_BuildSlaveModeRatList_PowerOff(
    NAS_MML_NET_RAT_TYPE_ENUM_UINT8     enMasterModeRat
)
{
    NAS_MML_PLMN_RAT_PRIO_STRU                 *pstSlaveModeList = VOS_NULL_PTR; /* 发送关机请求的从模列表 */
    VOS_UINT8                                   ucRatIndex;
    VOS_UINT8                                   i;

    pstSlaveModeList = NAS_MMC_GetSlaveModeRatList_PowerOff();

    ucRatIndex = 0;

    /* 先按平台接入技术能力把LWG都加到从模列表中 */
#if (FEATURE_ON == FEATURE_LTE)
    if (VOS_TRUE == NAS_MML_IsPlatformSupportLte())
    {
        pstSlaveModeList->aucRatPrio[ucRatIndex]      = NAS_MML_NET_RAT_TYPE_LTE;
        ucRatIndex++;
    }
#endif


    if (VOS_TRUE == NAS_MML_IsPlatformSupportUtran())
    {
        pstSlaveModeList->aucRatPrio[ucRatIndex]      = NAS_MML_NET_RAT_TYPE_WCDMA;
        ucRatIndex++;
    }

    if (VOS_TRUE == NAS_MML_IsPlatformSupportGsm())
    {
        pstSlaveModeList->aucRatPrio[ucRatIndex]      = NAS_MML_NET_RAT_TYPE_GSM;
        ucRatIndex++;
    }

    pstSlaveModeList->ucRatNum = ucRatIndex;

    /* 把主模从列表中删除 */
    for (i = 0; i < ucRatIndex; i++)
    {
        if (pstSlaveModeList->aucRatPrio[i] == enMasterModeRat)
        {
            /*lint -e961*/
            (VOS_VOID)PS_MEM_MOVE(&(pstSlaveModeList->aucRatPrio[i]),
                        &(pstSlaveModeList->aucRatPrio[i+1]),
                        (NAS_MML_MAX_RAT_NUM-i-1) * sizeof(pstSlaveModeList->aucRatPrio[i]));
            /*lint +e961*/
            pstSlaveModeList->ucRatNum--;
            break;
        }
    }

    return;

}
/*****************************************************************************
 函 数 名  : NAS_MMC_ClearAsPowerOffCnfFlag_PowerOff
 功能描述  : 清除AS模块关机回复标记
 输入参数  : AS模块关机回复标记
 输出参数  : 无
 返 回 值  : 无
 调用函数  :
 被调函数  :
 修改历史      :
  1.日    期   : 2011-07-11
    作    者   : w00176964
    修改内容   : 新生成函数
*****************************************************************************/
VOS_VOID    NAS_MMC_ClearAsPowerOffCnfFlag_PowerOff(
    NAS_MMC_AS_POWEROFF_FLAG_ENUM_UINT8                     enAsPowerOffFlg
)
{
    /* 如果当前状态机不是power off */
    if (NAS_MMC_FSM_POWER_OFF != NAS_MMC_GetCurrFsmId())
    {
        /* 异常事件 */
        NAS_WARNING_LOG(WUEPS_PID_MMC, "NAS_MMC_ClearAsPowerOffCnfFlag_PowerOff:ENTERED");

        return;
    }

    g_stNasMmcCtx.stCurFsm.unFsmCtx.stPowerOffCtx.ucMmcAsPowerOffCnfFlg &= ~enAsPowerOffFlg;
}

/*****************************************************************************
 函 数 名  : NAS_MMC_ClearMmPowerOffCnfFlag_PowerOff
 功能描述  : 清除所有MM/GMM模块关机回复标记
 输入参数  : 无
 输出参数  : 无
 返 回 值  : 无
 调用函数  :
 被调函数  :
 修改历史      :
  1.日    期   : 2011-07-11
    作    者   : w00176964
    修改内容   : 新生成函数
*****************************************************************************/

VOS_VOID    NAS_MMC_ClearAllMmPowerOffCnfFlag_PowerOff(VOS_VOID)
{
    /* 如果当前状态机不是power off */
    if (NAS_MMC_FSM_POWER_OFF != NAS_MMC_GetCurrFsmId())
    {
        /* 异常事件 */
        NAS_WARNING_LOG(WUEPS_PID_MMC, "NAS_MMC_ClearAllMmPowerOffCnfFlag_PowerOff:ENTERED");

        return;
    }

    g_stNasMmcCtx.stCurFsm.unFsmCtx.stPowerOffCtx.ucMmcMmPowerOffCnfFlg = NAS_MMC_MMGMM_POWER_OFF_NULL_FLG;
}

/*****************************************************************************
 函 数 名  : NAS_MMC_ClearAsPowerOffCnfFlag_PowerOff
 功能描述  : 清除所有AS模块关机回复标记
 输入参数  : 无
 输出参数  : 无
 返 回 值  : 无
 调用函数  :
 被调函数  :
 修改历史      :
  1.日    期   : 2011-07-11
    作    者   : w00176964
    修改内容   : 新生成函数
*****************************************************************************/
VOS_VOID    NAS_MMC_ClearAllAsPowerOffCnfFlag_PowerOff(VOS_VOID)
{
    /* 如果当前状态机不是power off */
    if (NAS_MMC_FSM_POWER_OFF != NAS_MMC_GetCurrFsmId())
    {
        /* 异常事件 */
        NAS_WARNING_LOG(WUEPS_PID_MMC, "NAS_MMC_ClearAllAsPowerOffCnfFlag_PowerOff:ENTERED");

    }

    g_stNasMmcCtx.stCurFsm.unFsmCtx.stPowerOffCtx.ucMmcAsPowerOffCnfFlg = NAS_MMC_AS_POWER_OFF_NULL_FLG;

    return;
}

/*************************************** 异系统重选相关状态机上下文操作函数 *************************************************/
/*****************************************************************************
 函 数 名  : NAS_MMC_GetSuspendRspFlg_InterSysCellResel
 功能描述  : 获取挂起回复标记
 输入参数  : 无
 输出参数  : 无
 返 回 值  : 挂起回复标记
 调用函数  :
 被调函数  :
 修改历史      :
  1.日    期   : 2011-07-11
    作    者   : w00176964
    修改内容   : 新生成函数
*****************************************************************************/
NAS_MMC_SUSPEND_RSP_FLAG_ENUM_UINT8  NAS_MMC_GetSuspendRspFlg_InterSysCellResel(VOS_VOID)
{
    /* 如果当前状态机不是INTERSYSCELLREL */
    if (NAS_MMC_FSM_INTER_SYS_CELLRESEL != NAS_MMC_GetCurrFsmId())
    {
        /* 异常事件 */
        NAS_WARNING_LOG(WUEPS_PID_MMC, "NAS_MMC_GetSuspendRspFlg_InterSysCellResel:ENTERED");
    }

    return g_stNasMmcCtx.stCurFsm.unFsmCtx.stInterSysCellReselCtx.ucMmcSuspendRspFlg;
}

/*****************************************************************************
 函 数 名  : NAS_MMC_GetResumeRspFlg_InterSysCellResel
 功能描述  : 获取恢复回复标记
 输入参数  : 无
 输出参数  : 无
 返 回 值  : 挂起恢复标记
 调用函数  :
 被调函数  :
 修改历史      :
  1.日    期   : 2011-07-11
    作    者   : w00176964
    修改内容   : 新生成函数
*****************************************************************************/
NAS_MMC_RESUME_RSP_FLAG_ENUM_UINT8   NAS_MMC_GetResumeRspFlg_InterSysCellResel(VOS_VOID)
{
    /* 如果当前状态机不是INTERSYSCELLREL */
    if (NAS_MMC_FSM_INTER_SYS_CELLRESEL != NAS_MMC_GetCurrFsmId())
    {
        /* 异常事件 */
        NAS_WARNING_LOG(WUEPS_PID_MMC, "NAS_MMC_GetResumeRspFlg_InterSysCellResel:ENTERED");
    }

    return g_stNasMmcCtx.stCurFsm.unFsmCtx.stInterSysCellReselCtx.ucMmcResumeRspFlg;
}

/* Added by s00246516 for L-C互操作项目, 2014-01-27, Begin */
/*****************************************************************************
 函 数 名  : NAS_MMC_GetResumeOrign_InterSysCellResel
 功能描述  : 获取恢复发起方枚举
 输入参数  : 无
 输出参数  : 无
 返 回 值  : 恢复发起枚举
 调用函数  :
 被调函数  :
 修改历史      :
  1.日    期   : 2014-01-27
    作    者   : s00246516
    修改内容   : 新生成函数
*****************************************************************************/
MMC_RESUME_ORIGEN_ENUM_UINT8 NAS_MMC_GetResumeOrign_InterSysCellResel(VOS_VOID)
{
    /* 如果当前状态机不是INTERSYSCELLREL */
    if (NAS_MMC_FSM_INTER_SYS_CELLRESEL != NAS_MMC_GetCurrFsmId())
    {
        /* 异常事件 */
        NAS_WARNING_LOG(WUEPS_PID_MMC, "NAS_MMC_GetResumeRspFlg_InterSysCellResel:ENTERED");
    }

    return g_stNasMmcCtx.stCurFsm.unFsmCtx.stInterSysCellReselCtx.enResumeOrign;
}

/*****************************************************************************
 函 数 名  : NAS_MMC_SetResumeOrign_InterSysCellResel
 功能描述  : 设置恢复发起方枚举
 输入参数  : 恢复发起枚举
 输出参数  : 无
 返 回 值  : 无
 调用函数  :
 被调函数  :
 修改历史      :
  1.日    期   : 2014-01-27
    作    者   : s00246516
    修改内容   : 新生成函数
*****************************************************************************/
VOS_VOID NAS_MMC_SetResumeOrign_InterSysCellResel(
    MMC_RESUME_ORIGEN_ENUM_UINT8        enResumeOrign
)
{
    /* 如果当前状态机不是INTERSYSCELLREL */
    if (NAS_MMC_FSM_INTER_SYS_CELLRESEL != NAS_MMC_GetCurrFsmId())
    {
        /* 异常事件 */
        NAS_WARNING_LOG(WUEPS_PID_MMC, "NAS_MMC_SetResumeOrign_InterSysCellResel:ENTERED");

        return;
    }

    g_stNasMmcCtx.stCurFsm.unFsmCtx.stInterSysCellReselCtx.enResumeOrign = enResumeOrign;
}
/* Added by s00246516 for L-C互操作项目, 2014-01-27, End */

/*****************************************************************************
 函 数 名  : NAS_MMC_ClearSuspendRspFlag_InterSysCellResel
 功能描述  : 清除挂起回复标记
 输入参数  : 需要清除的挂起回复标记
 输出参数  : 无
 返 回 值  : 无
 调用函数  :
 被调函数  :
 修改历史      :
  1.日    期   : 2011-07-11
    作    者   : w00176964
    修改内容   : 新生成函数
*****************************************************************************/
VOS_VOID NAS_MMC_ClearSuspendRspFlag_InterSysCellResel(NAS_MMC_SUSPEND_RSP_FLAG_ENUM_UINT8 enMmSuspendRsp)
{
    /* 如果当前状态机不是INTERSYSCELLREL */
    if (NAS_MMC_FSM_INTER_SYS_CELLRESEL != NAS_MMC_GetCurrFsmId())
    {
        /* 异常事件 */
        NAS_WARNING_LOG(WUEPS_PID_MMC, "NAS_MMC_ClearSuspendRspFlag_InterSysCellResel:ENTERED");

        return;
    }

    g_stNasMmcCtx.stCurFsm.unFsmCtx.stInterSysCellReselCtx.ucMmcSuspendRspFlg &= ~(enMmSuspendRsp);
}

/*****************************************************************************
 函 数 名  : NAS_MMC_ClearResumeRspFlag_InterSysCellResel
 功能描述  : 清除恢复回复标记
 输入参数  : 需要清除的恢复回复标记
 输出参数  : 无
 返 回 值  : 无
 调用函数  :
 被调函数  :
 修改历史      :
  1.日    期   : 2011-07-11
    作    者   : w00176964
    修改内容   : 新生成函数
*****************************************************************************/
VOS_VOID NAS_MMC_ClearResumeRspFlag_InterSysCellResel(NAS_MMC_RESUME_RSP_FLAG_ENUM_UINT8 enMmResumeRsp)
{
    /* 如果当前状态机不是INTERSYSCELLREL */
    if (NAS_MMC_FSM_INTER_SYS_CELLRESEL != NAS_MMC_GetCurrFsmId())
    {
        /* 异常事件 */
        NAS_WARNING_LOG(WUEPS_PID_MMC, "NAS_MMC_ClearResumeRspFlag_InterSysCellResel:ENTERED");

        return;
    }

    g_stNasMmcCtx.stCurFsm.unFsmCtx.stInterSysCellReselCtx.ucMmcResumeRspFlg&= ~(enMmResumeRsp);
}


/*****************************************************************************
 函 数 名  : NAS_MMC_SetSuspendRspFlag_InterSysCellResel
 功能描述  : 清除恢复回复标记
 输入参数  : 挂起回复标记
 输出参数  : 无
 返 回 值  : 无
 调用函数  :
 被调函数  :
 修改历史      :
  1.日    期   : 2011-07-11
    作    者   : w00176964
    修改内容   : 新生成函数
*****************************************************************************/
VOS_VOID NAS_MMC_SetSuspendRspFlag_InterSysCellResel(NAS_MMC_SUSPEND_RSP_FLAG_ENUM_UINT8 enMmSuspendRsp)
{
    /* 如果当前状态机不是INTERSYSCELLREL */
    if (NAS_MMC_FSM_INTER_SYS_CELLRESEL != NAS_MMC_GetCurrFsmId())
    {
        /* 异常事件 */
        NAS_WARNING_LOG(WUEPS_PID_MMC, "NAS_MMC_SetSuspendRspFlag_InterSysCellResel:ENTERED");

        return;
    }

    g_stNasMmcCtx.stCurFsm.unFsmCtx.stInterSysCellReselCtx.ucMmcSuspendRspFlg |= enMmSuspendRsp;
}

/*****************************************************************************
 函 数 名  : NAS_MMC_SetResumeRspFlag_InterSysCellResel
 功能描述  : 清除恢复回复标记
 输入参数  : 恢复回复标记
 输出参数  : 无
 返 回 值  : 无
 调用函数  :
 被调函数  :
 修改历史      :
  1.日    期   : 2011-07-11
    作    者   : w00176964
    修改内容   : 新生成函数
*****************************************************************************/

VOS_VOID NAS_MMC_SetResumeRspFlag_InterSysCellResel(NAS_MMC_RESUME_RSP_FLAG_ENUM_UINT8 enMmResumeRsp)
{
    /* 如果当前状态机不是INTERSYSCELLREL */
    if (NAS_MMC_FSM_INTER_SYS_CELLRESEL != NAS_MMC_GetCurrFsmId())
    {
        /* 异常事件 */
        NAS_WARNING_LOG(WUEPS_PID_MMC, "NAS_MMC_SetResumeRspFlag_InterSysCellResel:ENTERED");

        return;
    }

    g_stNasMmcCtx.stCurFsm.unFsmCtx.stInterSysCellReselCtx.ucMmcResumeRspFlg|= enMmResumeRsp;
}


/*****************************************************************************
 函 数 名  : NAS_MMC_ClearAllSuspendRspFlag_InterSysCellResel
 功能描述  : 清除所有挂起回复标记
 输入参数  : 无
 输出参数  : 无
 返 回 值  : 无
 调用函数  :
 被调函数  :
 修改历史      :
  1.日    期   : 2011-07-11
    作    者   : w00176964
    修改内容   : 新生成函数
*****************************************************************************/

VOS_VOID NAS_MMC_ClearAllSuspendRspFlag_InterSysCellResel(VOS_VOID)
{
    /* 如果当前状态机不是INTERSYSCELLREL */
    if (NAS_MMC_FSM_INTER_SYS_CELLRESEL != NAS_MMC_GetCurrFsmId())
    {
        /* 异常事件 */
        NAS_WARNING_LOG(WUEPS_PID_MMC, "NAS_MMC_ClearAllSuspendRspFlag_InterSysCellResel:ENTERED");

        return;
    }

    g_stNasMmcCtx.stCurFsm.unFsmCtx.stInterSysCellReselCtx.ucMmcSuspendRspFlg = NAS_MMC_SUSPEND_RSP_NULL_FLG;
}


/*****************************************************************************
 函 数 名  : NAS_MMC_ClearAllResumeRspFlag_InterSysCellResel
 功能描述  : 清除所有恢复回复标记
 输入参数  : 无
 输出参数  : 无
 返 回 值  : 无
 调用函数  :
 被调函数  :
 修改历史      :
  1.日    期   : 2011-07-11
    作    者   : w00176964
    修改内容   : 新生成函数
*****************************************************************************/

VOS_VOID NAS_MMC_ClearAllResumeRspFlag_InterSysCellResel(VOS_VOID)
{
    /* 如果当前状态机不是INTERSYSCELLREL */
    if (NAS_MMC_FSM_INTER_SYS_CELLRESEL != NAS_MMC_GetCurrFsmId())
    {
        /* 异常事件 */
        NAS_WARNING_LOG(WUEPS_PID_MMC, "NAS_MMC_ClearAllResumeRspFlag_InterSysCellResel:ENTERED");

        return;
    }

    g_stNasMmcCtx.stCurFsm.unFsmCtx.stInterSysCellReselCtx.ucMmcResumeRspFlg= NAS_MMC_RESUME_RSP_NULL_FLG;
}

/*****************************************************************************
 函 数 名  : NAS_MMC_SetAbortFlag_InterSysCellResel
 功能描述  : 设置小区重选状态机上下文中的Abort标志
 输入参数  : ulAbortFlg
 输出参数  : 无
 返 回 值  : 无
 调用函数  :
 被调函数  :

 修改历史     :
 1.日    期   : 2012年11月15日
    作    者  : s00217060
    修改内容  : 新生成函数

*****************************************************************************/
VOS_VOID NAS_MMC_SetAbortFlag_InterSysCellResel(
    VOS_UINT8                           ucAbortFlg
)
{
    /* 如果当前状态机不是PLMN SELECTION异常打印 */
    if (NAS_MMC_FSM_INTER_SYS_CELLRESEL != NAS_MMC_GetCurrFsmId())
    {
        NAS_ERROR_LOG(WUEPS_PID_MMC, "NAS_MMC_SetAbortFlag_InterSysCellResel,ERROR:FsmId Error");
        return;
    }

    g_stNasMmcCtx.stCurFsm.unFsmCtx.stInterSysCellReselCtx.ucAbortFlg = ucAbortFlg;
}

/*****************************************************************************
 函 数 名  : NAS_MMC_GetAbortFlag_InterSysCellResel
 功能描述  : 获取小区重选状态机上下文中的Abort标志
 输入参数  : 无
 输出参数  : 无
 返 回 值  : ulAbortFlg：Abort标志
 调用函数  :
 被调函数  :

 修改历史     :
 1.日    期   : 2012年11月15日
    作    者  : s00217060
    修改内容  : 新生成函数

*****************************************************************************/
VOS_UINT8 NAS_MMC_GetAbortFlag_InterSysCellResel(VOS_VOID)
{
    /* 如果当前状态机不是PLMN SELECTION异常打印 */
    if (NAS_MMC_FSM_INTER_SYS_CELLRESEL != NAS_MMC_GetCurrFsmId())
    {
        NAS_ERROR_LOG(WUEPS_PID_MMC, "NAS_MMC_SetAbortFlag_InterSysCellResel,ERROR:FsmId Error");
    }

    return g_stNasMmcCtx.stCurFsm.unFsmCtx.stInterSysCellReselCtx.ucAbortFlg;
}

/*****************************************************************************
 函 数 名  : NAS_MMC_SetSndSuspendRelReqFlg_InterSysCellResel
 功能描述  : 设置小区重选状态机上下文中的是否已经给接入层或LMM发送过SuspendRelReq标志
 输入参数  : ucSndSuspendRelReqFlg
 输出参数  : 无
 返 回 值  : 无
 调用函数  :
 被调函数  :

 修改历史     :
 1.日    期   : 2012年11月21日
    作    者  : s00217060
    修改内容  : 新生成函数

*****************************************************************************/
VOS_VOID NAS_MMC_SetSndSuspendRelReqFlg_InterSysCellResel(
    VOS_UINT8                           ucSndSuspendRelReqFlg
)
{
    /* 如果当前状态机不是PLMN SELECTION异常打印 */
    if (NAS_MMC_FSM_INTER_SYS_CELLRESEL != NAS_MMC_GetCurrFsmId())
    {
        NAS_ERROR_LOG(WUEPS_PID_MMC, "NAS_MMC_SetAbortFlag_InterSysCellResel,ERROR:FsmId Error");
        return;
    }

    g_stNasMmcCtx.stCurFsm.unFsmCtx.stInterSysCellReselCtx.ucSndSuspendRelReqFlg = ucSndSuspendRelReqFlg;
}

/*****************************************************************************
 函 数 名  : NAS_MMC_GetSndSuspendRelReqFlg_InterSysCellResel
 功能描述  : 获取小区重选状态机上下文中的是否已经给接入层或LMM发送过SuspendRelReq标志标志
 输入参数  : 无
 输出参数  : 无
 返 回 值  : ucSndSuspendRelReqFlg：是否已经给接入层或LMM发送过SuspendRelReq标志
 调用函数  :
 被调函数  :

 修改历史     :
 1.日    期   : 2012年11月21日
    作    者  : s00217060
    修改内容  : 新生成函数

*****************************************************************************/
VOS_UINT8 NAS_MMC_GetSndSuspendRelReqFlg_InterSysCellResel(VOS_VOID)
{
    /* 如果当前状态机不是PLMN SELECTION异常打印 */
    if (NAS_MMC_FSM_INTER_SYS_CELLRESEL != NAS_MMC_GetCurrFsmId())
    {
        NAS_ERROR_LOG(WUEPS_PID_MMC, "NAS_MMC_GetSndSuspendRelReqFlg_InterSysCellResel,ERROR:FsmId Error");
    }

    return g_stNasMmcCtx.stCurFsm.unFsmCtx.stInterSysCellReselCtx.ucSndSuspendRelReqFlg;
}


/*************************************** 异系统OOS相关状态机上下文操作函数 *************************************************/
/*****************************************************************************
 函 数 名  : NAS_MMC_GetSuspendRspFlg_InterSysOos
 功能描述  : 获取挂起回复标记
 输入参数  : 无
 输出参数  : 无
 返 回 值  : 挂起回复标记
 调用函数  :
 被调函数  :
 修改历史      :
  1.日    期   : 2011-07-11
    作    者   : w00176964
    修改内容   : 新生成函数
*****************************************************************************/
NAS_MMC_SUSPEND_RSP_FLAG_ENUM_UINT8  NAS_MMC_GetSuspendRspFlg_InterSysOos(VOS_VOID)
{
    /* 如果当前状态机不是INTERSYSOOS */
    if (NAS_MMC_FSM_INTER_SYS_OOS != NAS_MMC_GetCurrFsmId())
    {
        /* 异常事件 */
        NAS_WARNING_LOG(WUEPS_PID_MMC, "NAS_MMC_GetSuspendRspFlg_InterSysOos:ENTERED");
    }

    return g_stNasMmcCtx.stCurFsm.unFsmCtx.stInterSysOosCtx.ucMmcSuspendRspFlg;
}

/*****************************************************************************
 函 数 名  : NAS_MMC_GetResumeRspFlg_InterSysOos
 功能描述  : 获取恢复回复标记
 输入参数  : 无
 输出参数  : 无
 返 回 值  : 挂起恢复标记
 调用函数  :
 被调函数  :
 修改历史      :
  1.日    期   : 2011-07-11
    作    者   : w00176964
    修改内容   : 新生成函数
*****************************************************************************/
NAS_MMC_RESUME_RSP_FLAG_ENUM_UINT8   NAS_MMC_GetResumeRspFlg_InterSysOos(VOS_VOID)
{
    /* 如果当前状态机不是INTERSYSOOS */
    if (NAS_MMC_FSM_INTER_SYS_OOS != NAS_MMC_GetCurrFsmId())
    {
        /* 异常事件 */
        NAS_WARNING_LOG(WUEPS_PID_MMC, "NAS_MMC_GetResumeRspFlg_InterSysOos:ENTERED");
    }

    return g_stNasMmcCtx.stCurFsm.unFsmCtx.stInterSysOosCtx.ucMmcResumeRspFlg;
}

/*****************************************************************************
 函 数 名  : NAS_MMC_ClearSuspendRspFlag_InterSysOos
 功能描述  : 清除挂起回复标记
 输入参数  : 需要清除的挂起回复标记
 输出参数  : 无
 返 回 值  : 无
 调用函数  :
 被调函数  :
 修改历史      :
  1.日    期   : 2011-07-11
    作    者   : w00176964
    修改内容   : 新生成函数
*****************************************************************************/
VOS_VOID NAS_MMC_ClearSuspendRspFlag_InterSysOos(NAS_MMC_SUSPEND_RSP_FLAG_ENUM_UINT8 enMmSuspendRsp)
{
    /* 如果当前状态机不是INTERSYSOOS */
    if (NAS_MMC_FSM_INTER_SYS_OOS != NAS_MMC_GetCurrFsmId())
    {
        /* 异常事件 */
        NAS_WARNING_LOG(WUEPS_PID_MMC, "NAS_MMC_ClearSuspendRspFlag_InterSysOos:ENTERED");

        return;
    }

    g_stNasMmcCtx.stCurFsm.unFsmCtx.stInterSysOosCtx.ucMmcSuspendRspFlg &= ~(enMmSuspendRsp);
}

/*****************************************************************************
 函 数 名  : NAS_MMC_ClearResumeRspFlag_InterSysOos
 功能描述  : 清除恢复回复标记
 输入参数  : 需要清除的恢复回复标记
 输出参数  : 无
 返 回 值  : 无
 调用函数  :
 被调函数  :
 修改历史      :
  1.日    期   : 2011-07-11
    作    者   : w00176964
    修改内容   : 新生成函数
*****************************************************************************/
VOS_VOID NAS_MMC_ClearResumeRspFlag_InterSysOos(NAS_MMC_RESUME_RSP_FLAG_ENUM_UINT8 enMmResumeRsp)
{
    /* 如果当前状态机不是INTERSYSOOS */
    if (NAS_MMC_FSM_INTER_SYS_OOS != NAS_MMC_GetCurrFsmId())
    {
        /* 异常事件 */
        NAS_WARNING_LOG(WUEPS_PID_MMC, "NAS_MMC_ClearResumeRspFlag_InterSysOos:ENTERED");

        return;
    }

    g_stNasMmcCtx.stCurFsm.unFsmCtx.stInterSysOosCtx.ucMmcResumeRspFlg&= ~(enMmResumeRsp);
}


/*****************************************************************************
 函 数 名  : NAS_MMC_SetSuspendRspFlag_InterSysOos
 功能描述  : 清除恢复回复标记
 输入参数  : 挂起回复标记
 输出参数  : 无
 返 回 值  : 无
 调用函数  :
 被调函数  :
 修改历史      :
  1.日    期   : 2011-07-11
    作    者   : w00176964
    修改内容   : 新生成函数
*****************************************************************************/
VOS_VOID NAS_MMC_SetSuspendRspFlag_InterSysOos(NAS_MMC_SUSPEND_RSP_FLAG_ENUM_UINT8 enMmSuspendRsp)
{
    /* 如果当前状态机不是INTERSYSOOS */
    if (NAS_MMC_FSM_INTER_SYS_OOS != NAS_MMC_GetCurrFsmId())
    {
        /* 异常事件 */
        NAS_WARNING_LOG(WUEPS_PID_MMC, "NAS_MMC_SetSuspendRspFlag_InterSysOos:ENTERED");

        return;
    }

    g_stNasMmcCtx.stCurFsm.unFsmCtx.stInterSysOosCtx.ucMmcSuspendRspFlg |= enMmSuspendRsp;
}

/*****************************************************************************
 函 数 名  : NAS_MMC_SetResumeRspFlag_InterSysOos
 功能描述  : 清除恢复回复标记
 输入参数  : 恢复回复标记
 输出参数  : 无
 返 回 值  : 无
 调用函数  :
 被调函数  :
 修改历史      :
  1.日    期   : 2011-07-11
    作    者   : w00176964
    修改内容   : 新生成函数
*****************************************************************************/

VOS_VOID NAS_MMC_SetResumeRspFlag_InterSysOos(NAS_MMC_RESUME_RSP_FLAG_ENUM_UINT8 enMmResumeRsp)
{
    /* 如果当前状态机不是INTERSYSOOS */
    if (NAS_MMC_FSM_INTER_SYS_OOS != NAS_MMC_GetCurrFsmId())
    {
        /* 异常事件 */
        NAS_WARNING_LOG(WUEPS_PID_MMC, "NAS_MMC_SetResumeRspFlag_InterSysOos:ENTERED");

        return;
    }

    g_stNasMmcCtx.stCurFsm.unFsmCtx.stInterSysOosCtx.ucMmcResumeRspFlg|= enMmResumeRsp;
}


/*****************************************************************************
 函 数 名  : NAS_MMC_ClearAllSuspendRspFlag_InterSysOos
 功能描述  : 清除所有挂起回复标记
 输入参数  : 无
 输出参数  : 无
 返 回 值  : 无
 调用函数  :
 被调函数  :
 修改历史      :
  1.日    期   : 2011-07-11
    作    者   : w00176964
    修改内容   : 新生成函数
*****************************************************************************/

VOS_VOID NAS_MMC_ClearAllSuspendRspFlag_InterSysOos(VOS_VOID)
{
    /* 如果当前状态机不是INTERSYSOOS */
    if (NAS_MMC_FSM_INTER_SYS_OOS != NAS_MMC_GetCurrFsmId())
    {
        /* 异常事件 */
        NAS_WARNING_LOG(WUEPS_PID_MMC, "NAS_MMC_ClearAllSuspendRspFlag_InterSysOos:ENTERED");

        return;
    }

    g_stNasMmcCtx.stCurFsm.unFsmCtx.stInterSysOosCtx.ucMmcSuspendRspFlg = NAS_MMC_SUSPEND_RSP_NULL_FLG;
}


/*****************************************************************************
 函 数 名  : NAS_MMC_ClearAllResumeRspFlag_InterSysOos
 功能描述  : 清除所有恢复回复标记
 输入参数  : 无
 输出参数  : 无
 返 回 值  : 无
 调用函数  :
 被调函数  :
 修改历史      :
  1.日    期   : 2011-07-11
    作    者   : w00176964
    修改内容   : 新生成函数
*****************************************************************************/

VOS_VOID NAS_MMC_ClearAllResumeRspFlag_InterSysOos(VOS_VOID)
{
    /* 如果当前状态机不是INTERSYSOOS */
    if (NAS_MMC_FSM_INTER_SYS_OOS != NAS_MMC_GetCurrFsmId())
    {
        /* 异常事件 */
        NAS_WARNING_LOG(WUEPS_PID_MMC, "NAS_MMC_ClearAllResumeRspFlag_InterSysOos:ENTERED");

        return;
    }

    g_stNasMmcCtx.stCurFsm.unFsmCtx.stInterSysOosCtx.ucMmcResumeRspFlg= NAS_MMC_RESUME_RSP_NULL_FLG;
}

/*************************************** 异系统HO相关状态机上下文操作函数 *************************************************/
/*****************************************************************************
 函 数 名  : NAS_MMC_GetSuspendRspFlg_InterSysHo
 功能描述  : 获取挂起回复标记
 输入参数  : 无
 输出参数  : 无
 返 回 值  : 挂起回复标记
 调用函数  :
 被调函数  :
 修改历史      :
  1.日    期   : 2011-07-11
    作    者   : w00176964
    修改内容   : 新生成函数
*****************************************************************************/
NAS_MMC_SUSPEND_RSP_FLAG_ENUM_UINT8  NAS_MMC_GetSuspendRspFlg_InterSysHo(VOS_VOID)
{
    /* 如果当前状态机不是INTERSYSHO */
    if (NAS_MMC_FSM_INTER_SYS_HO != NAS_MMC_GetCurrFsmId())
    {
        /* 异常事件 */
        NAS_WARNING_LOG(WUEPS_PID_MMC, "NAS_MMC_GetSuspendRspFlg_InterSysHo:ENTERED");
    }

    return g_stNasMmcCtx.stCurFsm.unFsmCtx.stInterSysHoCtx.ucMmcSuspendRspFlg;
}

/*****************************************************************************
 函 数 名  : NAS_MMC_GetResumeRspFlg_InterSysHo
 功能描述  : 获取恢复回复标记
 输入参数  : 无
 输出参数  : 无
 返 回 值  : 挂起恢复标记
 调用函数  :
 被调函数  :
 修改历史      :
  1.日    期   : 2011-07-11
    作    者   : w00176964
    修改内容   : 新生成函数
*****************************************************************************/
NAS_MMC_RESUME_RSP_FLAG_ENUM_UINT8   NAS_MMC_GetResumeRspFlg_InterSysHo(VOS_VOID)
{
    /* 如果当前状态机不是INTERSYSHO */
    if (NAS_MMC_FSM_INTER_SYS_HO != NAS_MMC_GetCurrFsmId())
    {
        /* 异常事件 */
        NAS_WARNING_LOG(WUEPS_PID_MMC, "NAS_MMC_GetResumeRspFlg_InterSysHo:ENTERED");
    }

    return g_stNasMmcCtx.stCurFsm.unFsmCtx.stInterSysHoCtx.ucMmcResumeRspFlg;
}

/*****************************************************************************
 函 数 名  : NAS_MMC_ClearSuspendRspFlag_InterSysHo
 功能描述  : 清除挂起回复标记
 输入参数  : 需要清除的挂起回复标记
 输出参数  : 无
 返 回 值  : 无
 调用函数  :
 被调函数  :
 修改历史      :
  1.日    期   : 2011-07-11
    作    者   : w00176964
    修改内容   : 新生成函数
*****************************************************************************/
VOS_VOID NAS_MMC_ClearSuspendRspFlag_InterSysHo(NAS_MMC_SUSPEND_RSP_FLAG_ENUM_UINT8 enMmSuspendRsp)
{
    /* 如果当前状态机不是INTERSYSHO */
    if (NAS_MMC_FSM_INTER_SYS_HO != NAS_MMC_GetCurrFsmId())
    {
        /* 异常事件 */
        NAS_WARNING_LOG(WUEPS_PID_MMC, "NAS_MMC_ClearSuspendRspFlag_InterSysHo:ENTERED");

        return;
    }

    g_stNasMmcCtx.stCurFsm.unFsmCtx.stInterSysHoCtx.ucMmcSuspendRspFlg &= ~(enMmSuspendRsp);
}

/*****************************************************************************
 函 数 名  : NAS_MMC_ClearResumeRspFlag_InterSysHo
 功能描述  : 清除恢复回复标记
 输入参数  : 需要清除的恢复回复标记
 输出参数  : 无
 返 回 值  : 无
 调用函数  :
 被调函数  :
 修改历史      :
  1.日    期   : 2011-07-11
    作    者   : w00176964
    修改内容   : 新生成函数
*****************************************************************************/
VOS_VOID NAS_MMC_ClearResumeRspFlag_InterSysHo(NAS_MMC_RESUME_RSP_FLAG_ENUM_UINT8 enMmResumeRsp)
{
    /* 如果当前状态机不是INTERSYSHO */
    if (NAS_MMC_FSM_INTER_SYS_HO != NAS_MMC_GetCurrFsmId())
    {
        /* 异常事件 */
        NAS_WARNING_LOG(WUEPS_PID_MMC, "NAS_MMC_ClearResumeRspFlag_InterSysHo:ENTERED");

        return;
    }

    g_stNasMmcCtx.stCurFsm.unFsmCtx.stInterSysHoCtx.ucMmcResumeRspFlg&= ~(enMmResumeRsp);
}


/*****************************************************************************
 函 数 名  : NAS_MMC_SetSuspendRspFlag_InterSysHo
 功能描述  : 清除恢复回复标记
 输入参数  : 挂起回复标记
 输出参数  : 无
 返 回 值  : 无
 调用函数  :
 被调函数  :
 修改历史      :
  1.日    期   : 2011-07-11
    作    者   : w00176964
    修改内容   : 新生成函数
*****************************************************************************/
VOS_VOID NAS_MMC_SetSuspendRspFlag_InterSysHo(NAS_MMC_SUSPEND_RSP_FLAG_ENUM_UINT8 enMmSuspendRsp)
{
    /* 如果当前状态机不是INTERSYSHO */
    if (NAS_MMC_FSM_INTER_SYS_HO != NAS_MMC_GetCurrFsmId())
    {
        /* 异常事件 */
        NAS_WARNING_LOG(WUEPS_PID_MMC, "NAS_MMC_SetSuspendRspFlag_InterSysHo:ENTERED");

        return;
    }

    g_stNasMmcCtx.stCurFsm.unFsmCtx.stInterSysHoCtx.ucMmcSuspendRspFlg |= enMmSuspendRsp;
}

/*****************************************************************************
 函 数 名  : NAS_MMC_SetResumeRspFlag_InterSysHo
 功能描述  : 清除恢复回复标记
 输入参数  : 恢复回复标记
 输出参数  : 无
 返 回 值  : 无
 调用函数  :
 被调函数  :
 修改历史      :
  1.日    期   : 2011-07-11
    作    者   : w00176964
    修改内容   : 新生成函数
*****************************************************************************/

VOS_VOID NAS_MMC_SetResumeRspFlag_InterSysHo(NAS_MMC_RESUME_RSP_FLAG_ENUM_UINT8 enMmResumeRsp)
{
    /* 如果当前状态机不是INTERSYSHO */
    if (NAS_MMC_FSM_INTER_SYS_HO != NAS_MMC_GetCurrFsmId())
    {
        /* 异常事件 */
        NAS_WARNING_LOG(WUEPS_PID_MMC, "NAS_MMC_SetResumeRspFlag_InterSysHo:ENTERED");

        return;
    }

    g_stNasMmcCtx.stCurFsm.unFsmCtx.stInterSysHoCtx.ucMmcResumeRspFlg|= enMmResumeRsp;
}


/*****************************************************************************
 函 数 名  : NAS_MMC_ClearAllSuspendRspFlag_InterSysHo
 功能描述  : 清除所有挂起回复标记
 输入参数  : 无
 输出参数  : 无
 返 回 值  : 无
 调用函数  :
 被调函数  :
 修改历史      :
  1.日    期   : 2011-07-11
    作    者   : w00176964
    修改内容   : 新生成函数
*****************************************************************************/

VOS_VOID NAS_MMC_ClearAllSuspendRspFlag_InterSysHo(VOS_VOID)
{
    /* 如果当前状态机不是INTERSYSHO */
    if (NAS_MMC_FSM_INTER_SYS_HO != NAS_MMC_GetCurrFsmId())
    {
        /* 异常事件 */
        NAS_WARNING_LOG(WUEPS_PID_MMC, "NAS_MMC_ClearAllSuspendRspFlag_InterSysHo:ENTERED");

        return;
    }

    g_stNasMmcCtx.stCurFsm.unFsmCtx.stInterSysHoCtx.ucMmcSuspendRspFlg = NAS_MMC_SUSPEND_RSP_NULL_FLG;
}


/*****************************************************************************
 函 数 名  : NAS_MMC_ClearAllResumeRspFlag_InterSysHo
 功能描述  : 清除所有恢复回复标记
 输入参数  : 无
 输出参数  : 无
 返 回 值  : 无
 调用函数  :
 被调函数  :
 修改历史      :
  1.日    期   : 2011-07-11
    作    者   : w00176964
    修改内容   : 新生成函数
*****************************************************************************/

VOS_VOID NAS_MMC_ClearAllResumeRspFlag_InterSysHo(VOS_VOID)
{
    /* 如果当前状态机不是INTERSYSHO */
    if (NAS_MMC_FSM_INTER_SYS_HO != NAS_MMC_GetCurrFsmId())
    {
        /* 异常事件 */
        NAS_WARNING_LOG(WUEPS_PID_MMC, "NAS_MMC_ClearAllResumeRspFlag_InterSysHo:ENTERED");

        return;
    }

    g_stNasMmcCtx.stCurFsm.unFsmCtx.stInterSysHoCtx.ucMmcResumeRspFlg= NAS_MMC_RESUME_RSP_NULL_FLG;
}

/*****************************************************************************
 函 数 名  : NAS_MMC_SetCsSigExistFlag_InterSysHo
 功能描述  : 设置CS信令连接存在标记
 输入参数  : CS信令连接存在标记
 输出参数  : 无
 返 回 值  : 无
 调用函数  :
 被调函数  :
 修改历史      :
  1.日    期   : 2013-11-26
    作    者   : w00176964
    修改内容   : 新生成函数
*****************************************************************************/
VOS_VOID NAS_MMC_SetCsSigExistFlag_InterSysHo(
    VOS_UINT8       ucSigExistFlg
)
{
    /* 如果当前状态机不是INTERSYSHO */
    if (NAS_MMC_FSM_INTER_SYS_HO != NAS_MMC_GetCurrFsmId())
    {
        /* 异常事件 */
        NAS_WARNING_LOG(WUEPS_PID_MMC, "NAS_MMC_SetCsSigExistFlag_InterSysHo:ENTERED");

        return;
    }

    g_stNasMmcCtx.stCurFsm.unFsmCtx.stInterSysHoCtx.ucCsSigExistFlg = ucSigExistFlg;
}

/*****************************************************************************
 函 数 名  : NAS_MMC_SetPsSigExistFlag_InterSysHo
 功能描述  : 设置PS信令连接存在标记
 输入参数  : PS信令连接存在标记
 输出参数  : 无
 返 回 值  : 无
 调用函数  :
 被调函数  :
 修改历史      :
  1.日    期   : 2013-11-26
    作    者   : w00176964
    修改内容   : 新生成函数
*****************************************************************************/
VOS_VOID NAS_MMC_SetPsSigExistFlag_InterSysHo(
    VOS_UINT8       ucSigExistFlg
)
{
    /* 如果当前状态机不是INTERSYSHO */
    if (NAS_MMC_FSM_INTER_SYS_HO != NAS_MMC_GetCurrFsmId())
    {
        /* 异常事件 */
        NAS_WARNING_LOG(WUEPS_PID_MMC, "NAS_MMC_SetPsSigExistFlag_InterSysHo:ENTERED");

        return;
    }

    g_stNasMmcCtx.stCurFsm.unFsmCtx.stInterSysHoCtx.ucPsSigExistFlg = ucSigExistFlg;
}


/*****************************************************************************
 函 数 名  : NAS_MMC_GetCsSigExistFlag_InterSysHo
 功能描述  : 获取CS信令连接存在标记
 输入参数  : 无
 输出参数  : 无
 返 回 值  : CS信令连接存在标记
 调用函数  :
 被调函数  :
 修改历史      :
  1.日    期   : 2011-07-11
    作    者   : w00176964
    修改内容   : 新生成函数
*****************************************************************************/
VOS_UINT8  NAS_MMC_GetCsSigExistFlag_InterSysHo(VOS_VOID)
{
    /* 如果当前状态机不是INTERSYSHO */
    if (NAS_MMC_FSM_INTER_SYS_HO != NAS_MMC_GetCurrFsmId())
    {
        /* 异常事件 */
        NAS_WARNING_LOG(WUEPS_PID_MMC, "NAS_MMC_GetCsSigExistFlag_InterSysHo:ENTERED");
    }

    return g_stNasMmcCtx.stCurFsm.unFsmCtx.stInterSysHoCtx.ucCsSigExistFlg;
}

/*****************************************************************************
 函 数 名  : NAS_MMC_GetPsSigExistFlag_InterSysHo
 功能描述  : 获取PS信令连接存在标记
 输入参数  : 无
 输出参数  : 无
 返 回 值  : PS信令连接存在标记
 调用函数  :
 被调函数  :
 修改历史      :
  1.日    期   : 2011-07-11
    作    者   : w00176964
    修改内容   : 新生成函数
*****************************************************************************/
VOS_UINT8  NAS_MMC_GetPsSigExistFlag_InterSysHo(VOS_VOID)
{
    /* 如果当前状态机不是INTERSYSHO */
    if (NAS_MMC_FSM_INTER_SYS_HO != NAS_MMC_GetCurrFsmId())
    {
        /* 异常事件 */
        NAS_WARNING_LOG(WUEPS_PID_MMC, "NAS_MMC_GetPsSigExistFlag_InterSysHo:ENTERED");
    }

    return g_stNasMmcCtx.stCurFsm.unFsmCtx.stInterSysHoCtx.ucPsSigExistFlg;
}



/*************************************** 异系统CCO相关状态机上下文操作函数 *************************************************/
/*****************************************************************************
 函 数 名  : NAS_MMC_GetSuspendRspFlg_InterSysCco
 功能描述  : 获取挂起回复标记
 输入参数  : 无
 输出参数  : 无
 返 回 值  : 挂起回复标记
 调用函数  :
 被调函数  :
 修改历史      :
  1.日    期   : 2011-07-11
    作    者   : w00176964
    修改内容   : 新生成函数
*****************************************************************************/
NAS_MMC_SUSPEND_RSP_FLAG_ENUM_UINT8  NAS_MMC_GetSuspendRspFlg_InterSysCco(VOS_VOID)
{
    /* 如果当前状态机不是INTERSYSCCO */
    if (NAS_MMC_FSM_INTER_SYS_CCO != NAS_MMC_GetCurrFsmId())
    {
        /* 异常事件 */
        NAS_WARNING_LOG(WUEPS_PID_MMC, "NAS_MMC_GetSuspendRspFlg_InterSysCco:ENTERED");
    }

    return g_stNasMmcCtx.stCurFsm.unFsmCtx.stInterSysCcoCtx.ucMmcSuspendRspFlg;
}

/*****************************************************************************
 函 数 名  : NAS_MMC_GetResumeRspFlg_InterSysCco
 功能描述  : 获取恢复回复标记
 输入参数  : 无
 输出参数  : 无
 返 回 值  : 挂起恢复标记
 调用函数  :
 被调函数  :
 修改历史      :
  1.日    期   : 2011-07-11
    作    者   : w00176964
    修改内容   : 新生成函数
*****************************************************************************/
NAS_MMC_RESUME_RSP_FLAG_ENUM_UINT8   NAS_MMC_GetResumeRspFlg_InterSysCco(VOS_VOID)
{
    /* 如果当前状态机不是INTERSYSCCO */
    if (NAS_MMC_FSM_INTER_SYS_CCO != NAS_MMC_GetCurrFsmId())
    {
        /* 异常事件 */
        NAS_WARNING_LOG(WUEPS_PID_MMC, "NAS_MMC_GetResumeRspFlg_InterSysCco:ENTERED");
    }

    return g_stNasMmcCtx.stCurFsm.unFsmCtx.stInterSysCcoCtx.ucMmcResumeRspFlg;
}

/*****************************************************************************
 函 数 名  : NAS_MMC_ClearSuspendRspFlag_InterSysCco
 功能描述  : 清除挂起回复标记
 输入参数  : 需要清除的挂起回复标记
 输出参数  : 无
 返 回 值  : 无
 调用函数  :
 被调函数  :
 修改历史      :
  1.日    期   : 2011-07-11
    作    者   : w00176964
    修改内容   : 新生成函数
*****************************************************************************/
VOS_VOID NAS_MMC_ClearSuspendRspFlag_InterSysCco(NAS_MMC_SUSPEND_RSP_FLAG_ENUM_UINT8 enMmSuspendRsp)
{
    /* 如果当前状态机不是INTERSYSCCO */
    if (NAS_MMC_FSM_INTER_SYS_CCO != NAS_MMC_GetCurrFsmId())
    {
        /* 异常事件 */
        NAS_WARNING_LOG(WUEPS_PID_MMC, "NAS_MMC_ClearSuspendRspFlag_InterSysCco:ENTERED");

        return;
    }

    g_stNasMmcCtx.stCurFsm.unFsmCtx.stInterSysCcoCtx.ucMmcSuspendRspFlg &= ~(enMmSuspendRsp);
}

/*****************************************************************************
 函 数 名  : NAS_MMC_ClearResumeRspFlag_InterSysCco
 功能描述  : 清除恢复回复标记
 输入参数  : 需要清除的恢复回复标记
 输出参数  : 无
 返 回 值  : 无
 调用函数  :
 被调函数  :
 修改历史      :
  1.日    期   : 2011-07-11
    作    者   : w00176964
    修改内容   : 新生成函数
*****************************************************************************/
VOS_VOID NAS_MMC_ClearResumeRspFlag_InterSysCco(NAS_MMC_RESUME_RSP_FLAG_ENUM_UINT8 enMmResumeRsp)
{
    /* 如果当前状态机不是INTERSYSCCO */
    if (NAS_MMC_FSM_INTER_SYS_CCO != NAS_MMC_GetCurrFsmId())
    {
        /* 异常事件 */
        NAS_WARNING_LOG(WUEPS_PID_MMC, "NAS_MMC_ClearResumeRspFlag_InterSysCco:ENTERED");

        return;
    }

    g_stNasMmcCtx.stCurFsm.unFsmCtx.stInterSysCcoCtx.ucMmcResumeRspFlg&= ~(enMmResumeRsp);
}


/*****************************************************************************
 函 数 名  : NAS_MMC_SetSuspendRspFlag_InterSysCco
 功能描述  : 清除恢复回复标记
 输入参数  : 挂起回复标记
 输出参数  : 无
 返 回 值  : 无
 调用函数  :
 被调函数  :
 修改历史      :
  1.日    期   : 2011-07-11
    作    者   : w00176964
    修改内容   : 新生成函数
*****************************************************************************/
VOS_VOID NAS_MMC_SetSuspendRspFlag_InterSysCco(NAS_MMC_SUSPEND_RSP_FLAG_ENUM_UINT8 enMmSuspendRsp)
{
    /* 如果当前状态机不是INTERSYSCCO */
    if (NAS_MMC_FSM_INTER_SYS_CCO != NAS_MMC_GetCurrFsmId())
    {
        /* 异常事件 */
        NAS_WARNING_LOG(WUEPS_PID_MMC, "NAS_MMC_SetSuspendRspFlag_InterSysCco:ENTERED");

        return;
    }

    g_stNasMmcCtx.stCurFsm.unFsmCtx.stInterSysCcoCtx.ucMmcSuspendRspFlg |= enMmSuspendRsp;
}

/*****************************************************************************
 函 数 名  : NAS_MMC_SetResumeRspFlag_InterSysCco
 功能描述  : 清除恢复回复标记
 输入参数  : 恢复回复标记
 输出参数  : 无
 返 回 值  : 无
 调用函数  :
 被调函数  :
 修改历史      :
  1.日    期   : 2011-07-11
    作    者   : w00176964
    修改内容   : 新生成函数
*****************************************************************************/

VOS_VOID NAS_MMC_SetResumeRspFlag_InterSysCco(NAS_MMC_RESUME_RSP_FLAG_ENUM_UINT8 enMmResumeRsp)
{
    /* 如果当前状态机不是INTERSYSCCO */
    if (NAS_MMC_FSM_INTER_SYS_CCO != NAS_MMC_GetCurrFsmId())
    {
        /* 异常事件 */
        NAS_WARNING_LOG(WUEPS_PID_MMC, "NAS_MMC_SetResumeRspFlag_InterSysCco:ENTERED");

        return;
    }

    g_stNasMmcCtx.stCurFsm.unFsmCtx.stInterSysCcoCtx.ucMmcResumeRspFlg|= enMmResumeRsp;
}


/*****************************************************************************
 函 数 名  : NAS_MMC_ClearAllSuspendRspFlag_InterSysCco
 功能描述  : 清除所有挂起回复标记
 输入参数  : 无
 输出参数  : 无
 返 回 值  : 无
 调用函数  :
 被调函数  :
 修改历史      :
  1.日    期   : 2011-07-11
    作    者   : w00176964
    修改内容   : 新生成函数
*****************************************************************************/

VOS_VOID NAS_MMC_ClearAllSuspendRspFlag_InterSysCco(VOS_VOID)
{
    /* 如果当前状态机不是INTERSYSCCO */
    if (NAS_MMC_FSM_INTER_SYS_CCO != NAS_MMC_GetCurrFsmId())
    {
        /* 异常事件 */
        NAS_WARNING_LOG(WUEPS_PID_MMC, "NAS_MMC_ClearAllSuspendRspFlag_InterSysCco:ENTERED");

        return;
    }

    g_stNasMmcCtx.stCurFsm.unFsmCtx.stInterSysCcoCtx.ucMmcSuspendRspFlg = NAS_MMC_SUSPEND_RSP_NULL_FLG;
}


/*****************************************************************************
 函 数 名  : NAS_MMC_ClearAllResumeRspFlag_InterSysCco
 功能描述  : 清除所有恢复回复标记
 输入参数  : 无
 输出参数  : 无
 返 回 值  : 无
 调用函数  :
 被调函数  :
 修改历史      :
  1.日    期   : 2011-07-11
    作    者   : w00176964
    修改内容   : 新生成函数
*****************************************************************************/

VOS_VOID NAS_MMC_ClearAllResumeRspFlag_InterSysCco(VOS_VOID)
{
    /* 如果当前状态机不是INTERSYSCCO */
    if (NAS_MMC_FSM_INTER_SYS_CCO != NAS_MMC_GetCurrFsmId())
    {
        /* 异常事件 */
        NAS_WARNING_LOG(WUEPS_PID_MMC, "NAS_MMC_ClearAllResumeRspFlag_InterSysCco:ENTERED");

        return;
    }

    g_stNasMmcCtx.stCurFsm.unFsmCtx.stInterSysCcoCtx.ucMmcResumeRspFlg= NAS_MMC_RESUME_RSP_NULL_FLG;
}



/*****************************************************************************
 函 数 名  : NAS_MMC_GetL1MainCtx_L1Main
 功能描述  : 获取L1MAIN状态机上下文的地址
 输入参数  : 无
 输出参数  : 无
 返 回 值  : L1MAIN状态机上下文的地址
 调用函数  :
 被调函数  :

 修改历史     :
 1.日    期   : 2015年6月5日
    作    者  : w00167002
    修改内容  : 新生成函数

*****************************************************************************/
NAS_MMC_FSM_L1_MAIN_CTX_STRU* NAS_MMC_GetL1MainCtx_L1Main(VOS_VOID)
{
    /* 如果当前状态机不是PLMN SELECTION */
    if (NAS_MMC_FSM_L1_MAIN != NAS_MMC_GetCurrFsmId())
    {
        NAS_ERROR_LOG(WUEPS_PID_MMC, "NAS_MMC_GetL1MainCtx_L1Main,ERROR:FsmId Error");

        return VOS_NULL_PTR;
    }

    return &(g_stNasMmcCtx.stCurFsm.unFsmCtx.stL1MainCtx);
}

/*****************************************************************************
 函 数 名  : NAS_MMC_GetPlmnSelectionCtx_PlmnSelection
 功能描述  : 获取选网状态机上下文的地址
 输入参数  : 无
 输出参数  : 无
 返 回 值  : 选网状态机上下文的地址
 调用函数  :
 被调函数  :

 修改历史     :
 1.日    期   : 2015年6月5日
    作    者  : w00167002
    修改内容  : 新生成函数

*****************************************************************************/
NAS_MMC_FSM_PLMN_SELECTION_CTX_STRU* NAS_MMC_GetPlmnSelectionCtx_PlmnSelection(VOS_VOID)
{
    /* 如果当前状态机不是PLMN SELECTION */
    if (NAS_MMC_FSM_PLMN_SELECTION != NAS_MMC_GetCurrFsmId())
    {
        NAS_ERROR_LOG(WUEPS_PID_MMC, "NAS_MMC_GetPlmnSelectionCtx_PlmnSelection,ERROR:FsmId Error");

        return VOS_NULL_PTR;
    }

    return &(g_stNasMmcCtx.stCurFsm.unFsmCtx.stPlmnSelectionCtx);
}



/*****************************************************************************
 函 数 名  : NAS_MMC_GetAbortFlag_PlmnSelection
 功能描述  : 获取状态机上下文中的Abort标志
 输入参数  : 无
 输出参数  : 无
 返 回 值  : VOS_TRUE
             VOS_FALSE
 调用函数  :
 被调函数  :

 修改历史     :
 1.日    期   : 2011年7月11日
    作    者  : s46746
    修改内容  : 新生成函数

*****************************************************************************/
VOS_UINT32 NAS_MMC_GetAbortFlag_PlmnSelection(VOS_VOID)
{
    /* 如果当前状态机不是PLMN SELECTION */
    if (NAS_MMC_FSM_PLMN_SELECTION != NAS_MMC_GetCurrFsmId())
    {
        NAS_ERROR_LOG(WUEPS_PID_MMC, "NAS_MMC_GetAbortFlag_PlmnSelection,ERROR:FsmId Error");
    }

    return (VOS_UINT32)(g_stNasMmcCtx.stCurFsm.unFsmCtx.stPlmnSelectionCtx.ucAbortFlg);
}

/*****************************************************************************
 函 数 名  : NAS_MMC_SetAbortFlag_PlmnSelection
 功能描述  : 设置状态机上下文中的Abort标志
 输入参数  : ulAbortFlg
 输出参数  : 无
 返 回 值  : 无
 调用函数  :
 被调函数  :

 修改历史     :
 1.日    期   : 2011年7月11日
    作    者  : s46746
    修改内容  : 新生成函数

*****************************************************************************/
VOS_VOID NAS_MMC_SetAbortFlag_PlmnSelection(
    VOS_UINT8                           ucAbortFlg
)
{
    /* 如果当前状态机不是PLMN SELECTION异常打印 */
    if (NAS_MMC_FSM_PLMN_SELECTION != NAS_MMC_GetCurrFsmId())
    {
        NAS_ERROR_LOG(WUEPS_PID_MMC, "NAS_MMC_SetAbortFlag_PlmnSelection,ERROR:FsmId Error");
        return;
    }

    g_stNasMmcCtx.stCurFsm.unFsmCtx.stPlmnSelectionCtx.ucAbortFlg = ucAbortFlg;
}

/*****************************************************************************
 函 数 名  : NAS_MMC_GetRelRequestFlag_PlmnSelection
 功能描述  : 获取状态机上下文中的Rel Request标志
 输入参数  : 无
 输出参数  : 无
 返 回 值  : VOS_TRUE
             VOS_FALSE
 调用函数  :
 被调函数  :

 修改历史     :
 1.日    期   : 2011年7月11日
    作    者  : s46746
    修改内容  : 新生成函数

*****************************************************************************/
VOS_UINT32 NAS_MMC_GetRelRequestFlag_PlmnSelection(VOS_VOID)
{
    /* 如果当前状态机不是PLMN SELECTION */
    if (NAS_MMC_FSM_PLMN_SELECTION != NAS_MMC_GetCurrFsmId())
    {
        NAS_ERROR_LOG(WUEPS_PID_MMC, "NAS_MMC_GetRelRequestFlag_PlmnSelection,ERROR:FsmId Error");
    }

    return (VOS_UINT32)(g_stNasMmcCtx.stCurFsm.unFsmCtx.stPlmnSelectionCtx.ucRelRequestFlg);
}

/*****************************************************************************
 函 数 名  : NAS_MMC_SetRelRequestFlag_PlmnSelection
 功能描述  : 设置状态机上下文中的Rel Request标志
 输入参数  : ucRelRequestFlg
 输出参数  : 无
 返 回 值  : 无
 调用函数  :
 被调函数  :

 修改历史     :
 1.日    期   : 2011年7月11日
    作    者  : s46746
    修改内容  : 新生成函数

*****************************************************************************/
VOS_VOID NAS_MMC_SetRelRequestFlag_PlmnSelection(
    VOS_UINT8                           ucRelRequestFlg
)
{
    /* 如果当前状态机不是PLMN SELECTION异常打印 */
    if (NAS_MMC_FSM_PLMN_SELECTION != NAS_MMC_GetCurrFsmId())
    {
        NAS_ERROR_LOG(WUEPS_PID_MMC, "NAS_MMC_SetPlmnSelectionRelRequestFlag_PlmnSelection,ERROR:FsmId Error");
        return;
    }

    g_stNasMmcCtx.stCurFsm.unFsmCtx.stPlmnSelectionCtx.ucRelRequestFlg = ucRelRequestFlg;
}



/*****************************************************************************
 函 数 名  : NAS_MMC_GetExistRplmnOrHplmnFlag_PlmnSelection
 功能描述  : 获取状态机上下文中的searched plmn info是否上报过存在rplmn或hplmn标志
 输入参数  : 无
 输出参数  : 无
 返 回 值  : VOS_TRUE  - 存在
             VOS_FALSE - 不存在
 调用函数  :
 被调函数  :

 修改历史     :
 1.日    期   : 2014年11月8日
   作    者   : z00161729
   修改内容   : 开机搜网优化项目修改

*****************************************************************************/
VOS_UINT8 NAS_MMC_GetExistRplmnOrHplmnFlag_PlmnSelection(VOS_VOID)
{
    /* 如果当前状态机不是PLMN SELECTION */
    if (NAS_MMC_FSM_PLMN_SELECTION != NAS_MMC_GetCurrFsmId())
    {
        NAS_ERROR_LOG(WUEPS_PID_MMC, "NAS_MMC_GetExistRplmnOrHplmnFlag_PlmnSelection,ERROR:FsmId Error");
    }

    return (g_stNasMmcCtx.stCurFsm.unFsmCtx.stPlmnSelectionCtx.ucExistRplmnOrHplmnFlag);
}

/*****************************************************************************
 函 数 名  : NAS_MMC_SetExistRplmnOrHplmnFlag_PlmnSelection
 功能描述  : 设置状态机上下文中的searched plmn info是否上报过存在rplmn或hplmn标志
 输入参数  : 无
 输出参数  : 无
 返 回 值  : VOS_TRUE  - 存在
             VOS_FALSE - 不存在
 调用函数  :
 被调函数  :

 修改历史     :
 1.日    期   : 2014年11月8日
   作    者   : z00161729
   修改内容   : 开机搜网优化项目修改

*****************************************************************************/
VOS_VOID NAS_MMC_SetExistRplmnOrHplmnFlag_PlmnSelection(
    VOS_UINT8                           ucExistRplmnOrHplmnFlag
)
{
    /* 如果当前状态机不是PLMN SELECTION */
    if (NAS_MMC_FSM_PLMN_SELECTION != NAS_MMC_GetCurrFsmId())
    {
        NAS_ERROR_LOG(WUEPS_PID_MMC, "NAS_MMC_SetExistRplmnOrHplmnFlag_PlmnSelection,ERROR:FsmId Error");
    }

    g_stNasMmcCtx.stCurFsm.unFsmCtx.stPlmnSelectionCtx.ucExistRplmnOrHplmnFlag = ucExistRplmnOrHplmnFlag;
    return;
}


/*****************************************************************************
 函 数 名  : NAS_MMC_SetInterSysSuspendRat_PlmnSelection
 功能描述  : 设置搜网状态机上下文中的收到SUSPEND_IND表示异系统时的接入技术
 输入参数  : enRat
 输出参数  : 无
 返 回 值  : 无
 调用函数  :
 被调函数  :

 修改历史     :
 1.日    期   : 2013年8月5日
   作    者   : w00167002
   修改内容   : 新生成函数
*****************************************************************************/
VOS_VOID NAS_MMC_SetInterSysSuspendRat_PlmnSelection(
    NAS_MML_NET_RAT_TYPE_ENUM_UINT8     enRat
)
{
    /* 如果当前状态机不是PLMN SELECTION */
    if (NAS_MMC_FSM_PLMN_SELECTION != NAS_MMC_GetCurrFsmId())
    {
        NAS_ERROR_LOG(WUEPS_PID_MMC, "NAS_MMC_GetInterSysSuspendRat_PlmnSelection,ERROR:FsmId Error");
    }

    g_stNasMmcCtx.stCurFsm.unFsmCtx.stPlmnSelectionCtx.ucInterSysSuspendRat = enRat;

    return;
}

/*****************************************************************************
 函 数 名  : NAS_MMC_GetInterSysSuspendRat_PlmnSelection
 功能描述  : 获取设置搜网状态机上下文中的收到SUSPEND_IND表示异系统时的接入技术
 输入参数  : 无
 输出参数  : 无
 返 回 值  : NAS_MMC_RAT_SEARCH_INFO_STRU*
 调用函数  :
 被调函数  :

 修改历史     :
 1.日    期   : 2013年8月5日
   作    者   : w00167002
   修改内容   : 新生成函数

*****************************************************************************/
NAS_MML_NET_RAT_TYPE_ENUM_UINT8 NAS_MMC_GetInterSysSuspendRat_PlmnSelection(VOS_VOID)
{
    /* 如果当前状态机不是PLMN SELECTION */
    if (NAS_MMC_FSM_PLMN_SELECTION != NAS_MMC_GetCurrFsmId())
    {
        NAS_ERROR_LOG(WUEPS_PID_MMC, "NAS_MMC_GetInterSysSuspendRat_PlmnSelection,ERROR:FsmId Error");
    }

    return (g_stNasMmcCtx.stCurFsm.unFsmCtx.stPlmnSelectionCtx.ucInterSysSuspendRat);
}


/*****************************************************************************
 函 数 名  : NAS_MMC_GetWaitRegRsltFlag_PlmnSelection
 功能描述  : 获取状态机上下文中的等待CS/PS的注册结果的标志
 输入参数  : 无
 输出参数  : 无
 返 回 值  : VOS_UINT16
 调用函数  :
 被调函数  :

 修改历史     :
 1.日    期   : 2011年7月22日
   作    者   : l00130025
   修改内容   : 新生成函数

*****************************************************************************/
VOS_UINT8 NAS_MMC_GetWaitRegRsltFlag_PlmnSelection(VOS_VOID)
{
    /* 如果当前状态机不是PLMN SELECTION */
    if (NAS_MMC_FSM_PLMN_SELECTION != NAS_MMC_GetCurrFsmId())
    {
        NAS_ERROR_LOG(WUEPS_PID_MMC, "NAS_MMC_GetWaitRegRsltFlag_PlmnSelection,ERROR:FsmId Error");
    }

    return (g_stNasMmcCtx.stCurFsm.unFsmCtx.stPlmnSelectionCtx.stRegRlstInfo.ucWaitRegRsltFlag);
}

/*****************************************************************************
 函 数 名  : NAS_MMC_SetWaitRegRsltFlag_PlmnSelection
 功能描述  : 设置状态机上下文中的等待CS/PS的注册结果的标志
 输入参数  : NAS_MML_REG_FAIL_CAUSE_ENUM_UINT16
 输出参数  : 无
 返 回 值  : VOS_VOID
 调用函数  :
 被调函数  :

 修改历史     :
 1.日    期   : 2011年7月22日
   作    者   : l00130025
   修改内容   : 新生成函数

*****************************************************************************/
VOS_VOID NAS_MMC_SetWaitRegRsltFlag_PlmnSelection(VOS_UINT8 ucWaitFlag)
{
    /* 如果当前状态机不是PLMN SELECTION */
    if (NAS_MMC_FSM_PLMN_SELECTION != NAS_MMC_GetCurrFsmId())
    {
        NAS_ERROR_LOG(WUEPS_PID_MMC, "NAS_MMC_SetWaitRegRsltFlag_PlmnSelection,ERROR:FsmId Error");
        return;
    }

    g_stNasMmcCtx.stCurFsm.unFsmCtx.stPlmnSelectionCtx.stRegRlstInfo.ucWaitRegRsltFlag |= ucWaitFlag;
}

/*****************************************************************************
 函 数 名  : NAS_MMC_ClearSingleDomainWaitRegRsltFlag_PlmnSelection
 功能描述  : 清除状态机上下文中的等待指定域的注册结果的标志
 输入参数  : 无
 输出参数  : 无
 返 回 值  : VOS_VOID
 调用函数  :
 被调函数  :

 修改历史     :
 1.日    期   : 2011年7月22日
   作    者   : l00130025
   修改内容   : 新生成函数

*****************************************************************************/
VOS_VOID NAS_MMC_ClearSingleDomainWaitRegRsltFlag_PlmnSelection(
    VOS_UINT8                           ucRegDomain
)
{
    /* 如果当前状态机不是PLMN SELECTION */
    if (NAS_MMC_FSM_PLMN_SELECTION != NAS_MMC_GetCurrFsmId())
    {
        NAS_ERROR_LOG(WUEPS_PID_MMC, "NAS_MMC_ClearSingleDomainWaitRegRsltFlag_PlmnSelection,ERROR:FsmId Error");
        return;
    }

    g_stNasMmcCtx.stCurFsm.unFsmCtx.stPlmnSelectionCtx.stRegRlstInfo.ucWaitRegRsltFlag &= ~ucRegDomain;
}

/*****************************************************************************
 函 数 名  : NAS_MMC_ClearAllWaitRegRsltFlag_PlmnSelection
 功能描述  : 清除状态机上下文中的等待CS/PS域的注册结果的标志
 输入参数  : 无
 输出参数  : 无
 返 回 值  : VOS_VOID
 调用函数  :
 被调函数  :

 修改历史     :
 1.日    期   : 2011年7月22日
   作    者   : l00130025
   修改内容   : 新生成函数

*****************************************************************************/
VOS_VOID NAS_MMC_ClearAllWaitRegRsltFlag_PlmnSelection()
{
    /* 如果当前状态机不是PLMN SELECTION */
    if (NAS_MMC_FSM_PLMN_SELECTION != NAS_MMC_GetCurrFsmId())
    {
        NAS_ERROR_LOG(WUEPS_PID_MMC, "NAS_MMC_ClearAllWaitRegRsltFlag_PlmnSelection,ERROR:FsmId Error");
        return;
    }

    g_stNasMmcCtx.stCurFsm.unFsmCtx.stPlmnSelectionCtx.stRegRlstInfo.ucWaitRegRsltFlag = NAS_MMC_WAIT_REG_RESULT_IND_NULL;
}

/*****************************************************************************
 函 数 名  : NAS_MMC_GetCsRegAdditionalAction_PlmnSelection
 功能描述  : 获取状态机上下文中的CS注册结果触发的后续动作
 输入参数  : 无
 输出参数  : 无
 返 回 值  : NAS_MMC_ADDITIONAL_ACTION_ENUM_UINT8
 调用函数  :
 被调函数  :

 修改历史     :
 1.日    期   : 2011年7月15日
   作    者   : l00130025
   修改内容   : 新生成函数

*****************************************************************************/
NAS_MMC_ADDITIONAL_ACTION_ENUM_UINT8 NAS_MMC_GetCsRegAdditionalAction_PlmnSelection(VOS_VOID)
{

    /* 如果当前状态机不是PLMN SELECTION */
    if (NAS_MMC_FSM_PLMN_SELECTION != NAS_MMC_GetCurrFsmId())
    {
        NAS_ERROR_LOG(WUEPS_PID_MMC, "NAS_MMC_GetCsRegAdditionalAction_PlmnSelection,ERROR:FsmId Error");
    }

    return g_stNasMmcCtx.stCurFsm.unFsmCtx.stPlmnSelectionCtx.stRegRlstInfo.enCsRegAdditionalAction;
}

/*****************************************************************************
 函 数 名  : NAS_MMC_SetCsRegAdditionalAction_PlmnSelection
 功能描述  : 设置状态机上下文中的CS注册结果触发的后续动作
 输入参数  : NAS_MMC_ADDITIONAL_ACTION_ENUM_UINT8
 输出参数  : 无
 返 回 值  : VOS_VOID
 调用函数  :
 被调函数  :

 修改历史     :
 1.日    期   : 2011年7月15日
   作    者   : l00130025
   修改内容   : 新生成函数

*****************************************************************************/
VOS_VOID NAS_MMC_SetCsRegAdditionalAction_PlmnSelection(
    NAS_MMC_ADDITIONAL_ACTION_ENUM_UINT8 enCsAddtionalAction
)
{
    /* 如果当前状态机不是PLMN SELECTION */
    if (NAS_MMC_FSM_PLMN_SELECTION != NAS_MMC_GetCurrFsmId())
    {
        NAS_ERROR_LOG(WUEPS_PID_MMC, "NAS_MMC_SetCsRegAdditionalAction_PlmnSelection,ERROR:FsmId Error");
        return;
    }

    g_stNasMmcCtx.stCurFsm.unFsmCtx.stPlmnSelectionCtx.stRegRlstInfo.enCsRegAdditionalAction = enCsAddtionalAction;
}

/*****************************************************************************
 函 数 名  : NAS_MMC_GetPsRegAdditionalAction_PlmnSelection
 功能描述  : 获取状态机上下文中的PS注册结果触发的后续动作
 输入参数  : 无
 输出参数  : 无
 返 回 值  : NAS_MMC_ADDITIONAL_ACTION_ENUM_UINT8
 调用函数  :
 被调函数  :

 修改历史     :
 1.日    期   : 2011年7月15日
   作    者   : l00130025
   修改内容   : 新生成函数

*****************************************************************************/
NAS_MMC_ADDITIONAL_ACTION_ENUM_UINT8 NAS_MMC_GetPsRegAdditionalAction_PlmnSelection(VOS_VOID)
{
    /* 如果当前状态机不是PLMN SELECTION */
    if (NAS_MMC_FSM_PLMN_SELECTION != NAS_MMC_GetCurrFsmId())
    {
        NAS_ERROR_LOG(WUEPS_PID_MMC, "NAS_MMC_GetPsRegAdditionalAction_PlmnSelection,ERROR:FsmId Error");
    }

    return g_stNasMmcCtx.stCurFsm.unFsmCtx.stPlmnSelectionCtx.stRegRlstInfo.enPsRegAdditionalAction;
}

/*****************************************************************************
 函 数 名  : NAS_MMC_SetPsRegAdditionalAction_PlmnSelection
 功能描述  : 设置状态机上下文中的PS注册结果触发的后续动作
 输入参数  : NAS_MMC_ADDITIONAL_ACTION_ENUM_UINT8
 输出参数  : 无
 返 回 值  : VOS_VOID
 调用函数  :
 被调函数  :

 修改历史     :
 1.日    期   : 2011年7月15日
   作    者   : l00130025
   修改内容   : 新生成函数

*****************************************************************************/
VOS_VOID NAS_MMC_SetPsRegAdditionalAction_PlmnSelection(
    NAS_MMC_ADDITIONAL_ACTION_ENUM_UINT8  enPsAddtionalAction
)
{
    /* 如果当前状态机不是PLMN SELECTION */
    if (NAS_MMC_FSM_PLMN_SELECTION != NAS_MMC_GetCurrFsmId())
    {
        NAS_ERROR_LOG(WUEPS_PID_MMC, "NAS_MMC_SetPsRegAdditionalAction_PlmnSelection,ERROR:FsmId Error");
        return;
    }

    g_stNasMmcCtx.stCurFsm.unFsmCtx.stPlmnSelectionCtx.stRegRlstInfo.enPsRegAdditionalAction = enPsAddtionalAction;
}

/*****************************************************************************
 函 数 名  : NAS_MMC_GetCsRegCause_PlmnSelection
 功能描述  : 获取状态机上下文中的CS注册结果的 Cause
 输入参数  : 无
 输出参数  : 无
 返 回 值  : NAS_MML_REG_FAIL_CAUSE_ENUM_UINT16
 调用函数  :
 被调函数  :

 修改历史     :
 1.日    期   : 2011年7月15日
   作    者   : l00130025
   修改内容   : 新生成函数

*****************************************************************************/
NAS_MML_REG_FAIL_CAUSE_ENUM_UINT16 NAS_MMC_GetCsRegCause_PlmnSelection(VOS_VOID)
{
    /* 如果当前状态机不是PLMN SELECTION */
    if (NAS_MMC_FSM_PLMN_SELECTION != NAS_MMC_GetCurrFsmId())
    {
        NAS_ERROR_LOG(WUEPS_PID_MMC, "NAS_MMC_GetCsRegCause_PlmnSelection,ERROR:FsmId Error");
    }

    return g_stNasMmcCtx.stCurFsm.unFsmCtx.stPlmnSelectionCtx.stRegRlstInfo.enCsRegCause;
}

/*****************************************************************************
 函 数 名  : NAS_MMC_GetPsRegCause_PlmnSelection
 功能描述  : 获取状态机上下文中的PS注册结果的 Cause
 输入参数  : 无
 输出参数  : 无
 返 回 值  : NAS_MML_REG_FAIL_CAUSE_ENUM_UINT16
 调用函数  :
 被调函数  :

 修改历史     :
 1.日    期   : 2011年7月15日
   作    者   : l00130025
   修改内容   : 新生成函数

*****************************************************************************/
NAS_MML_REG_FAIL_CAUSE_ENUM_UINT16 NAS_MMC_GetPsRegCause_PlmnSelection(VOS_VOID)
{
    /* 如果当前状态机不是PLMN SELECTION */
    if (NAS_MMC_FSM_PLMN_SELECTION != NAS_MMC_GetCurrFsmId())
    {
        NAS_ERROR_LOG(WUEPS_PID_MMC, "NAS_MMC_GetPsRegCause_PlmnSelection,ERROR:FsmId Error");
    }

    return g_stNasMmcCtx.stCurFsm.unFsmCtx.stPlmnSelectionCtx.stRegRlstInfo.enPsRegCause;
}

/*****************************************************************************
 函 数 名  : NAS_MMC_SetCsRegCause_PlmnSelection
 功能描述  : 设置状态机上下文中的CS注册结果的 Cause
 输入参数  : NAS_MML_REG_FAIL_CAUSE_ENUM_UINT16
 输出参数  : 无
 返 回 值  : VOS_VOID
 调用函数  :
 被调函数  :

 修改历史     :
 1.日    期   : 2011年7月15日
   作    者   : l00130025
   修改内容   : 新生成函数

*****************************************************************************/
VOS_VOID NAS_MMC_SetCsRegCause_PlmnSelection(
    NAS_MML_REG_FAIL_CAUSE_ENUM_UINT16  enCsCause
)
{
    /* 如果当前状态机不是PLMN SELECTION */
    if (NAS_MMC_FSM_PLMN_SELECTION != NAS_MMC_GetCurrFsmId())
    {
        NAS_ERROR_LOG(WUEPS_PID_MMC, "NAS_MMC_SetCsRegCause_PlmnSelection,ERROR:FsmId Error");
        return;
    }

    g_stNasMmcCtx.stCurFsm.unFsmCtx.stPlmnSelectionCtx.stRegRlstInfo.enCsRegCause = enCsCause;
}

/*****************************************************************************
 函 数 名  : NAS_MMC_SetPsRegCause_PlmnSelection
 功能描述  : 设置状态机上下文中的PS注册结果的 Cause
 输入参数  : NAS_MML_REG_FAIL_CAUSE_ENUM_UINT16
 输出参数  : 无
 返 回 值  : VOS_VOID
 调用函数  :
 被调函数  :

 修改历史     :
 1.日    期   : 2011年7月15日
   作    者   : l00130025
   修改内容   : 新生成函数

*****************************************************************************/
VOS_VOID NAS_MMC_SetPsRegCause_PlmnSelection(
    NAS_MML_REG_FAIL_CAUSE_ENUM_UINT16  enPsCause
)
{
    /* 如果当前状态机不是PLMN SELECTION */
    if (NAS_MMC_FSM_PLMN_SELECTION != NAS_MMC_GetCurrFsmId())
    {
        NAS_ERROR_LOG(WUEPS_PID_MMC, "NAS_MMC_SetPsRegCause_PlmnSelection,ERROR:FsmId Error");
        return;
    }

    g_stNasMmcCtx.stCurFsm.unFsmCtx.stPlmnSelectionCtx.stRegRlstInfo.enPsRegCause = enPsCause;
}

/*****************************************************************************
 函 数 名  : NAS_MMC_GetPlmnSelectionListInfo_PlmnSelection
 功能描述  : 获取网络选择状态机上下文中的搜网列表信息
 输入参数  : 无
 输出参数  : 无
 返 回 值  : VOS_TRUE
             VOS_FALSE
 调用函数  :
 被调函数  :

 修改历史    :
 1.日    期  : 2011年7月11日
   作    者  : s46746
   修改内容  : 新生成函数

*****************************************************************************/
NAS_MMC_PLMN_SELECTION_LIST_INFO_STRU * NAS_MMC_GetPlmnSelectionListInfo_PlmnSelection()
{
    /* 如果当前状态机不是PLMN SELECTION */
    if (NAS_MMC_FSM_PLMN_SELECTION != NAS_MMC_GetCurrFsmId())
    {
        NAS_ERROR_LOG(WUEPS_PID_MMC, "NAS_MMC_GetPlmnSelectionListInfo_PlmnSelection,ERROR:FsmId Error");
    }

    return &(g_stNasMmcCtx.stCurFsm.unFsmCtx.stPlmnSelectionCtx.stPlmnSelectionListInfo);
}

/*****************************************************************************
 函 数 名  : NAS_MMC_GetSearchedRoamPlmnSortedFlag_PlmnSelection
 功能描述  : 获取搜网状态机上下文中某接入技术收到接入层的searched plmn info ind是否进行过排序标识
 输出参数  : 无
 返 回 值  : VOS_VOID
 调用函数  :
 被调函数  :

 修改历史      :
 1.日    期   : 2014年10月30日
   作    者   : z00161729
   修改内容   : 新生成函数

*****************************************************************************/
VOS_UINT8 NAS_MMC_GetSearchedRoamPlmnSortedFlag_PlmnSelection(
    NAS_MML_NET_RAT_TYPE_ENUM_UINT8     enRat
)
{
    VOS_UINT32                          i;

    /* 如果当前状态机不是PLMN SELECTION */
    if (NAS_MMC_FSM_PLMN_SELECTION != NAS_MMC_GetCurrFsmId())
    {
        NAS_ERROR_LOG(WUEPS_PID_MMC, "NAS_MMC_GetSearchedRoamPlmnSortedFlag_PlmnSelection,ERROR:FsmId Error");
    }

    /* 查找选网状态机上下文中与enRat相同的接入技术数组 */
    for (i = 0 ; i < NAS_MML_MAX_RAT_NUM; i++)
    {
        if (enRat == (g_stNasMmcCtx.stCurFsm.unFsmCtx.stPlmnSelectionCtx.astSearchRatInfo[i].enRatType))
        {
            return g_stNasMmcCtx.stCurFsm.unFsmCtx.stPlmnSelectionCtx.astSearchRatInfo[i].ucSearchedRoamPlmnSortedFlag;
        }
    }

    NAS_ERROR_LOG(WUEPS_PID_MMC, "NAS_MMC_GetSearchedRoamPlmnSortedFlag_PlmnSelection,ERROR:enRatType Error");

    return VOS_FALSE;
}

/*****************************************************************************
 函 数 名  : NAS_MMC_SetSearchedRoamPlmnSortedFlag_PlmnSelection
 功能描述  : 设置搜网状态机上下文中某接入技术收到接入层的searched plmn info ind是否进行过排序标识
 输出参数  : enRat                        - 接入技术
             ucSearchedRoamPlmnSortedFlag - 收到接入层的searched plmn info ind是否进行过排序标识
 返 回 值  : VOS_VOID
 调用函数  :
 被调函数  :

 修改历史      :
 1.日    期   : 2014年10月30日
   作    者   : z00161729
   修改内容   : 新生成函数
*****************************************************************************/
VOS_VOID NAS_MMC_SetSearchedRoamPlmnSortedFlag_PlmnSelection(
    NAS_MML_NET_RAT_TYPE_ENUM_UINT8     enRat,
    VOS_UINT8                           ucSearchedRoamPlmnSortedFlag
)
{
    VOS_UINT32                          i;

    /* 如果当前状态机不是PLMN SELECTION */
    if (NAS_MMC_FSM_PLMN_SELECTION != NAS_MMC_GetCurrFsmId())
    {
        NAS_ERROR_LOG(WUEPS_PID_MMC, "NAS_MMC_SetSearchedRoamPlmnSortedFlag_PlmnSelection,ERROR:FsmId Error");
        return;
    }

    /* 查找选网状态机上下文中与enRat相同的接入技术数组 */
    for (i = 0 ; i < NAS_MML_MAX_RAT_NUM; i++)
    {
        if (enRat == (g_stNasMmcCtx.stCurFsm.unFsmCtx.stPlmnSelectionCtx.astSearchRatInfo[i].enRatType))
        {
            g_stNasMmcCtx.stCurFsm.unFsmCtx.stPlmnSelectionCtx.astSearchRatInfo[i].ucSearchedRoamPlmnSortedFlag = ucSearchedRoamPlmnSortedFlag;
            return;
        }
    }
}

/*****************************************************************************
 函 数 名  : NAS_MMC_GetHistorySearchedFlag_PlmnSelection
 功能描述  : 获取搜网状态机上下文中某接入技术下是否完成了HISTORY搜流程
 输出参数  : 无
 返 回 值  : VOS_UINT8
 调用函数  :
 被调函数  :

 修改历史      :
 1.日    期   : 2015年5月22日
   作    者   : w00167002
   修改内容   : 新生成函数

*****************************************************************************/
VOS_UINT8 NAS_MMC_GetHistorySearchedFlag_PlmnSelection(
    NAS_MML_NET_RAT_TYPE_ENUM_UINT8     enRat
)
{
    VOS_UINT32                          i;

    /* 如果当前状态机不是PLMN SELECTION */
    if (NAS_MMC_FSM_PLMN_SELECTION != NAS_MMC_GetCurrFsmId())
    {
        NAS_ERROR_LOG(WUEPS_PID_MMC, "NAS_MMC_GetHistorySearchedFlag_PlmnSelection,ERROR:FsmId Error");

        return VOS_FALSE;
    }

    /* 查找选网状态机上下文中与enRat相同的接入技术数组 */
    for (i = 0; i < NAS_MML_MAX_RAT_NUM; i++)
    {
        if (enRat == (g_stNasMmcCtx.stCurFsm.unFsmCtx.stPlmnSelectionCtx.astSearchRatInfo[i].enRatType))
        {
            return g_stNasMmcCtx.stCurFsm.unFsmCtx.stPlmnSelectionCtx.astSearchRatInfo[i].ucHistorySearchedFlag;
        }
    }

    NAS_ERROR_LOG(WUEPS_PID_MMC, "NAS_MMC_GetHistorySearchedFlag_PlmnSelection,ERROR:enRatType Error");

    return VOS_FALSE;
}


/*****************************************************************************
 函 数 名  : NAS_MMC_SetHistorySearchedFlag_PlmnSelection
 功能描述  : 设置搜网状态机上下文中某接入技术是否完成跟接入层的HISTORY搜流程
 输入参数  : NAS_MML_NET_RAT_TYPE_ENUM_UINT8     enRat
             VOS_UINT8                           ucHistorySearchedFlag
 输出参数  : 无
 返 回 值  : VOS_VOID
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2015年5月21日
    作    者   : w00167002
    修改内容   : 新生成函数

*****************************************************************************/
VOS_VOID NAS_MMC_SetHistorySearchedFlag_PlmnSelection(
    NAS_MML_NET_RAT_TYPE_ENUM_UINT8     enRat,
    VOS_UINT8                           ucHistorySearchedFlag
)
{
    VOS_UINT32                          i;

    /* 如果当前状态机不是PLMN SELECTION */
    if (NAS_MMC_FSM_PLMN_SELECTION != NAS_MMC_GetCurrFsmId())
    {
        NAS_ERROR_LOG(WUEPS_PID_MMC, "NAS_MMC_SetHistorySearchedFlag_PlmnSelection,ERROR:FsmId Error");
        return;
    }

    /* 查找选网状态机上下文中与enRat相同的接入技术数组 */
    for (i = 0 ; i < NAS_MML_MAX_RAT_NUM; i++)
    {
        if (enRat == (g_stNasMmcCtx.stCurFsm.unFsmCtx.stPlmnSelectionCtx.astSearchRatInfo[i].enRatType))
        {
            g_stNasMmcCtx.stCurFsm.unFsmCtx.stPlmnSelectionCtx.astSearchRatInfo[i].ucHistorySearchedFlag = ucHistorySearchedFlag;

            return;
        }
    }

    return;
}

/*****************************************************************************
 函 数 名  : NAS_MMC_IsSpecRatListAllHistorySearched_PlmnSelection
 功能描述  : 指定的接入技术列表是否都已完成了HISTORY搜索
 输出参数  : 无
 返 回 值  : VOS_TRUE:指定的接入技术列表都已完成了HISTORY搜索
             VOS_FALSE:指定的接入技术列表存在未HISTORY搜索的RAT
 调用函数  :
 被调函数  :

 修改历史      :
 1.日    期   : 2015年6月1日
   作    者   : w00167002
   修改内容   : 新生成函数

*****************************************************************************/
VOS_UINT8 NAS_MMC_IsSpecRatListAllHistorySearched_PlmnSelection(
    NAS_MML_PLMN_RAT_PRIO_STRU         *pstPrioRatList
)
{
    VOS_UINT32                          i;

    /* 如果当前状态机不是PLMN SELECTION */
    if (NAS_MMC_FSM_PLMN_SELECTION != NAS_MMC_GetCurrFsmId())
    {
        NAS_ERROR_LOG(WUEPS_PID_MMC, "NAS_MMC_IsSpecRatListAllHistorySearched_PlmnSelection,ERROR:FsmId Error");
    }

    for ( i = 0; i < pstPrioRatList->ucRatNum; i++)
    {
        /* 找到未进行HISTORY搜的RAT */
        if (VOS_FALSE == NAS_MMC_GetHistorySearchedFlag_PlmnSelection(pstPrioRatList->aucRatPrio[i]) )
        {
            return VOS_FALSE;
        }
    }

    /* 指定的接入技术列表都已完成了HISTORY搜索 */
    return VOS_TRUE;
}



/*****************************************************************************
 函 数 名  : NAS_MMC_IsSpecRatListRoamSorted_PlmnSelection
 功能描述  : 指定的接入技术列表中是否存在漫游排序过的RAT
 输出参数  : 无
 返 回 值  : VOS_TRUE:指定的接入技术列表存在漫游排序过的RAT
             VOS_FALSE:指定的接入技术列表不存在漫游排序过的RAT
 调用函数  :
 被调函数  :

 修改历史      :
 1.日    期   : 2015年6月1日
   作    者   : w00167002
   修改内容   : 新生成函数

*****************************************************************************/
VOS_UINT8 NAS_MMC_IsSpecRatListRoamSorted_PlmnSelection(
    NAS_MML_PLMN_RAT_PRIO_STRU         *pstPrioRatList
)
{
    VOS_UINT32                          i;

    /* 如果当前状态机不是PLMN SELECTION */
    if (NAS_MMC_FSM_PLMN_SELECTION != NAS_MMC_GetCurrFsmId())
    {
        NAS_ERROR_LOG(WUEPS_PID_MMC, "NAS_MMC_IsSpecRatListAllHistorySearched_PlmnSelection,ERROR:FsmId Error");
    }

    for ( i = 0; i < pstPrioRatList->ucRatNum; i++)
    {
        /* 找到排过序的RAT,则返回TRUE */
        if (VOS_TRUE == NAS_MMC_GetSearchedRoamPlmnSortedFlag_PlmnSelection(pstPrioRatList->aucRatPrio[i]) )
        {
            return VOS_TRUE;
        }
    }

    /* 都没有排过序,则返回FALSE */
    return VOS_FALSE;
}



/*****************************************************************************
 函 数 名  : NAS_MMC_GetAllBandSearch_PlmnSelection
 功能描述  : 获取搜网状态机上下文中某接入技术的是否全频搜索标志
 输出参数  : 无
 返 回 值  : VOS_VOID
 调用函数  :
 被调函数  :

 修改历史      :
 1.日    期   : 2011年7月26日
   作    者   : L00171473
   修改内容   : 新生成函数

*****************************************************************************/
VOS_UINT8 NAS_MMC_GetAllBandSearch_PlmnSelection(
    NAS_MML_NET_RAT_TYPE_ENUM_UINT8     enRat
)
{
    VOS_UINT32                          i;

    /* 如果当前状态机不是PLMN SELECTION */
    if (NAS_MMC_FSM_PLMN_SELECTION != NAS_MMC_GetCurrFsmId())
    {
        NAS_ERROR_LOG(WUEPS_PID_MMC, "NAS_MMC_GetAllBandSearch_PlmnSelection,ERROR:FsmId Error");
    }

    /* 查找选网状态机上下文中与enRat相同的接入技术数组 */
    for (i = 0 ; i < NAS_MML_MAX_RAT_NUM; i++)
    {
        if (enRat == (g_stNasMmcCtx.stCurFsm.unFsmCtx.stPlmnSelectionCtx.astSearchRatInfo[i].enRatType))
        {
            return g_stNasMmcCtx.stCurFsm.unFsmCtx.stPlmnSelectionCtx.astSearchRatInfo[i].ucSearchAllBand;
        }
    }

    NAS_ERROR_LOG(WUEPS_PID_MMC, "NAS_MMC_GetAllBandSearch_PlmnSelection,ERROR:enRatType Error");

    return VOS_FALSE;
}

/*****************************************************************************
 函 数 名  : NAS_MMC_SetAllBandSearch_PlmnSelection
 功能描述  : 设置搜网状态机上下文中的是否全频搜索标志
 输入参数  : enRat
             ucAllBandSearch
 输出参数  : 无
 返 回 值  : 无
 调用函数  :
 被调函数  :

 修改历史     :
 1.日    期   : 2011年7月11日
   作    者   : s46746
   修改内容   : 新生成函数

*****************************************************************************/
VOS_VOID NAS_MMC_SetAllBandSearch_PlmnSelection(
    NAS_MML_NET_RAT_TYPE_ENUM_UINT8     enRat,
    VOS_UINT8                           ucAllBandSearch
)
{
    VOS_UINT32                          i;

    /* 如果当前状态机不是PLMN SELECTION */
    if (NAS_MMC_FSM_PLMN_SELECTION != NAS_MMC_GetCurrFsmId())
    {
        NAS_ERROR_LOG(WUEPS_PID_MMC, "NAS_MMC_SetAllBandSearch_PlmnSelection,ERROR:FsmId Error");
        return;
    }

    /* 查找选网状态机上下文中与enRat相同的接入技术数组 */
    for (i = 0 ; i < NAS_MML_MAX_RAT_NUM; i++)
    {
        if (enRat == (g_stNasMmcCtx.stCurFsm.unFsmCtx.stPlmnSelectionCtx.astSearchRatInfo[i].enRatType))
        {
            g_stNasMmcCtx.stCurFsm.unFsmCtx.stPlmnSelectionCtx.astSearchRatInfo[i].ucSearchAllBand = ucAllBandSearch;
            return;
        }
    }
}

/*****************************************************************************
 函 数 名  : NAS_MMC_SetRatCoverage_PlmnSelection
 功能描述  : 设置搜网状态机上下文中的是否存在覆盖标志
 输入参数  : enRat
             enCoverType
 输出参数  : 无
 返 回 值  : 无
 调用函数  :
 被调函数  :

 修改历史     :
 1.日    期   : 2011年7月11日
   作    者   : s46746
   修改内容   : 新生成函数
 2.日    期   : 2012年11月05日
   作    者   : w00176964
   修改内容   : DTS2011082405001:扩展覆盖标记入参,区分高低质量的网络覆盖
*****************************************************************************/
VOS_VOID NAS_MMC_SetRatCoverage_PlmnSelection(
    NAS_MML_NET_RAT_TYPE_ENUM_UINT8     enRat,
    NAS_MMC_COVERAGE_TYPE_ENUM_UINT8    enCoverType
)
{
    VOS_UINT32                          i;

    /* 如果当前状态机不是PLMN SELECTION */
    if (NAS_MMC_FSM_PLMN_SELECTION != NAS_MMC_GetCurrFsmId())
    {
        NAS_ERROR_LOG(WUEPS_PID_MMC, "NAS_MMC_SetRatCoverage_PlmnSelection,ERROR:FsmId Error");
        return;
    }

    /* 查找选网状态机上下文中与enRat相同的接入技术数组 */
    for ( i = 0 ; i < NAS_MML_MAX_RAT_NUM; i++ )
    {
        if ( enRat == (g_stNasMmcCtx.stCurFsm.unFsmCtx.stPlmnSelectionCtx.astSearchRatInfo[i].enRatType) )
        {
            g_stNasMmcCtx.stCurFsm.unFsmCtx.stPlmnSelectionCtx.astSearchRatInfo[i].enCoverageType = enCoverType;
            return ;
        }
    }

    /* 若未找到更新的接入技术，则进行LOG打印 */
    NAS_ERROR_LOG(WUEPS_PID_MMC, "NAS_MMC_SetRatCoverage_PlmnSelection,ERROR:NOT FOUND THE enRAT");
}

/*****************************************************************************
 函 数 名  : NAS_MMC_GetRatCoverage_PlmnSelection
 功能描述  : 获取搜网状态机上下文中的是否存在覆盖标志
 输入参数  : enRat

 输出参数  : enCoverType
 返 回 值  : 无
 调用函数  :
 被调函数  :

 修改历史     :
 1.日    期   : 2015年8月13日
   作    者   : l00289540
   修改内容   : 新生成函数

*****************************************************************************/
NAS_MMC_COVERAGE_TYPE_ENUM_UINT8 NAS_MMC_GetRatCoverage_PlmnSelection(
    NAS_MML_NET_RAT_TYPE_ENUM_UINT8     enRat
)
{
    VOS_UINT32                          i;

    /* 如果当前状态机不是PLMN SELECTION */
    if (NAS_MMC_FSM_PLMN_SELECTION != NAS_MMC_GetCurrFsmId())
    {
        NAS_ERROR_LOG(WUEPS_PID_MMC, "NAS_MMC_GetRatCoverage_PlmnSelection,ERROR:FsmId Error");
        return NAS_MMC_COVERAGE_TYPE_BUTT;
    }

    /* 查找选网状态机上下文中与enRat相同的接入技术数组 */
    for ( i = 0 ; i < NAS_MML_MAX_RAT_NUM; i++ )
    {
        if ( enRat == (g_stNasMmcCtx.stCurFsm.unFsmCtx.stPlmnSelectionCtx.astSearchRatInfo[i].enRatType) )
        {
            return g_stNasMmcCtx.stCurFsm.unFsmCtx.stPlmnSelectionCtx.astSearchRatInfo[i].enCoverageType;

        }
    }

    return NAS_MMC_COVERAGE_TYPE_BUTT;
}



/*****************************************************************************
 函 数 名  : NAS_MMC_GetSearchRplmnAndHplmnFlg
 功能描述  : 获取搜网状态机上下文中某接入技术是否进行过RPLMN+HPLMN搜
 输出参数  : 无
 返 回 值  : VOS_VOID
 调用函数  :
 被调函数  :

 修改历史      :
 1.日    期   : 2014年3月22日
   作    者   : w00242748
   修改内容   : 新生成函数

*****************************************************************************/
VOS_UINT8 NAS_MMC_GetSearchRplmnAndHplmnFlg_PlmnSelection(
    NAS_MML_NET_RAT_TYPE_ENUM_UINT8     enRat
)
{
    VOS_UINT32                          i;

    /* 如果当前状态机不是PLMN SELECTION */
    if (NAS_MMC_FSM_PLMN_SELECTION != NAS_MMC_GetCurrFsmId())
    {
        NAS_ERROR_LOG(WUEPS_PID_MMC, "NAS_MMC_GetSearchRplmnAndHplmnFlg,ERROR:FsmId Error");
    }

    /* 查找选网状态机上下文中与enRat相同的接入技术数组 */
    for (i = 0 ; i < NAS_MML_MAX_RAT_NUM; i++)
    {
        if (enRat == (g_stNasMmcCtx.stCurFsm.unFsmCtx.stPlmnSelectionCtx.astSearchRatInfo[i].enRatType))
        {
            return g_stNasMmcCtx.stCurFsm.unFsmCtx.stPlmnSelectionCtx.astSearchRatInfo[i].ucSearchRplmnAndHplmnFlg;
        }
    }

    NAS_ERROR_LOG(WUEPS_PID_MMC, "NAS_MMC_GetSearchRplmnAndHplmnFlg,ERROR:enRatType Error");

    return VOS_FALSE;
}

/*****************************************************************************
 函 数 名  : NAS_MMC_GetSearchRplmnAndHplmnFlg
 功能描述  : 设置搜网状态机上下文中某接入技术是否进行过RPLMN+HPLMN搜
 输出参数  : 无
 返 回 值  : VOS_VOID
 调用函数  :
 被调函数  :

 修改历史      :
 1.日    期   : 2014年3月22日
   作    者   : w00242748
   修改内容   : 新生成函数

*****************************************************************************/
VOS_VOID NAS_MMC_SetSearchRplmnAndHplmnFlg_PlmnSelection(
    NAS_MML_NET_RAT_TYPE_ENUM_UINT8     enRat,
    VOS_UINT8                           ucSearchRplmnAndHplmnFlg
)
{
    VOS_UINT32                          i;

    /* 如果当前状态机不是PLMN SELECTION */
    if (NAS_MMC_FSM_PLMN_SELECTION != NAS_MMC_GetCurrFsmId())
    {
        NAS_ERROR_LOG(WUEPS_PID_MMC, "NAS_MMC_SetSearchRplmnAndHplmnFlg,ERROR:FsmId Error");
        return;
    }

    /* 查找选网状态机上下文中与enRat相同的接入技术数组 */
    for (i = 0 ; i < NAS_MML_MAX_RAT_NUM; i++)
    {
        if (enRat == (g_stNasMmcCtx.stCurFsm.unFsmCtx.stPlmnSelectionCtx.astSearchRatInfo[i].enRatType))
        {
            g_stNasMmcCtx.stCurFsm.unFsmCtx.stPlmnSelectionCtx.astSearchRatInfo[i].ucSearchRplmnAndHplmnFlg = ucSearchRplmnAndHplmnFlg;
            return;
        }
    }
}


/*****************************************************************************
 函 数 名  : NAS_MMC_GetSearchRplmnAndEplmnFlg_PlmnSelection
 功能描述  : 获取搜网状态机上下文中某接入技术是否进行过RPLMN+EPLMN搜
 输入参数  : enRat - 接入技术
 输出参数  : 无
 返 回 值  : VOS_UINT8
 调用函数  :
 被调函数  :

 修改历史      :
 1.日    期   : 2014年9月9日
   作    者   : z00161729
   修改内容   : 新生成函数

*****************************************************************************/
VOS_UINT8 NAS_MMC_GetSearchRplmnAndEplmnFlg_PlmnSelection(
    NAS_MML_NET_RAT_TYPE_ENUM_UINT8     enRat
)
{
    VOS_UINT32                          i;

    /* 如果当前状态机不是PLMN SELECTION */
    if (NAS_MMC_FSM_PLMN_SELECTION != NAS_MMC_GetCurrFsmId())
    {
        NAS_ERROR_LOG(WUEPS_PID_MMC, "NAS_MMC_GetSearchRplmnAndEplmnFlg_PlmnSelection,ERROR:FsmId Error");
    }

    /* 查找选网状态机上下文中与enRat相同的接入技术数组 */
    for (i = 0 ; i < NAS_MML_MAX_RAT_NUM; i++)
    {
        if (enRat == (g_stNasMmcCtx.stCurFsm.unFsmCtx.stPlmnSelectionCtx.astSearchRatInfo[i].enRatType))
        {
            return g_stNasMmcCtx.stCurFsm.unFsmCtx.stPlmnSelectionCtx.astSearchRatInfo[i].ucSearchRplmnAndEplmnFlg;
        }
    }

    NAS_ERROR_LOG(WUEPS_PID_MMC, "NAS_MMC_GetSearchRplmnAndEplmnFlg_PlmnSelection,ERROR:enRatType Error");

    return VOS_FALSE;
}

/*****************************************************************************
 函 数 名  : NAS_MMC_SetSearchRplmnAndEplmnFlg_PlmnSelection
 功能描述  : 设置搜网状态机上下文中某接入技术是否进行过RPLMN+EPLMN搜网标识
 输入参数  : enRat - 接入技术
             ucSearchRplmnAndEplmnFlg - 是否进行过rplmn+eplmn搜网标识
 输出参数  : 无
 返 回 值  : 无
 调用函数  :
 被调函数  :

 修改历史      :
 1.日    期   : 2014年9月9日
   作    者   : z00161729
   修改内容   : 新生成函数

*****************************************************************************/
VOS_VOID NAS_MMC_SetSearchRplmnAndEplmnFlg_PlmnSelection(
    NAS_MML_NET_RAT_TYPE_ENUM_UINT8     enRat,
    VOS_UINT8                           ucSearchRplmnAndEplmnFlg
)
{
    VOS_UINT32                          i;

    /* 如果当前状态机不是PLMN SELECTION */
    if (NAS_MMC_FSM_PLMN_SELECTION != NAS_MMC_GetCurrFsmId())
    {
        NAS_ERROR_LOG(WUEPS_PID_MMC, "NAS_MMC_SetSearchRplmnAndEplmnFlg_PlmnSelection,ERROR:FsmId Error");
        return;
    }

    /* 查找选网状态机上下文中与enRat相同的接入技术数组 */
    for (i = 0 ; i < NAS_MML_MAX_RAT_NUM; i++)
    {
        if (enRat == (g_stNasMmcCtx.stCurFsm.unFsmCtx.stPlmnSelectionCtx.astSearchRatInfo[i].enRatType))
        {
            g_stNasMmcCtx.stCurFsm.unFsmCtx.stPlmnSelectionCtx.astSearchRatInfo[i].ucSearchRplmnAndEplmnFlg = ucSearchRplmnAndEplmnFlg;
            return;
        }
    }
}


/* Modified by c00318887 for DPlmn扩容和优先接入HPLMN, 2015-5-18, begin */
/*****************************************************************************
 函 数 名  : NAS_MMC_GetSearchDplmnAndHplmnFlg_PlmnSelection
 功能描述  : 漫游优化方案中开机搜网HPLMN优先，获取是否已经搜过HPLMN的标示
 输出参数  : 无
 返 回 值  : VOS_VOID
 调用函数  :
 被调函数  :

 修改历史      :
 1.日    期   : 2015年05月18日
   作    者   : c00318887
   修改内容   : 新生成函数

*****************************************************************************/
VOS_UINT8 NAS_MMC_GetSearchDplmnAndHplmnFlg_PlmnSelection(
    NAS_MML_NET_RAT_TYPE_ENUM_UINT8     enRat
)
{
    VOS_UINT32                          i;

    /* 如果当前状态机不是PLMN SELECTION */
    if (NAS_MMC_FSM_PLMN_SELECTION != NAS_MMC_GetCurrFsmId())
    {
        NAS_ERROR_LOG(WUEPS_PID_MMC, "NAS_MMC_GetSearchDplmnAndHplmnFlg_PlmnSelection,ERROR:FsmId Error");
    }

    /* 查找选网状态机上下文中与enRat相同的接入技术数组 */
    for (i = 0 ; i < NAS_MML_MAX_RAT_NUM; i++)
    {
        if (enRat == (g_stNasMmcCtx.stCurFsm.unFsmCtx.stPlmnSelectionCtx.astSearchRatInfo[i].enRatType))
        {
            return g_stNasMmcCtx.stCurFsm.unFsmCtx.stPlmnSelectionCtx.astSearchRatInfo[i].ucSearchDplmnAndHplmnFlg;
        }
    }

    NAS_ERROR_LOG(WUEPS_PID_MMC, "NAS_MMC_GetSearchDplmnAndHplmnFlg_PlmnSelection,ERROR:enRatType Error");

    return VOS_FALSE;
}

/*****************************************************************************
 函 数 名  : NAS_MMC_SetSearchDplmnAndHplmnFlg_PlmnSelection
 功能描述  : 漫游优化方案中开机搜网HPLMN优先，设置是否已经搜过HPLMN的标示
 输出参数  : enRat                        - 接入技术
             ucSwithOnAddHplmnFlg         - 是否已经搜过HPLMN的标示
 返 回 值  : VOS_VOID
 调用函数  :
 被调函数  :

 修改历史      :
 1.日    期   : 2015年05月18日
   作    者   : c00318887
   修改内容   : 新生成函数
*****************************************************************************/
VOS_VOID NAS_MMC_SetSearchDplmnAndHplmnFlg_PlmnSelection(
    NAS_MML_NET_RAT_TYPE_ENUM_UINT8     enRat,
    VOS_UINT8                           ucSearchDplmnAndHplmnFlg
)
{
    VOS_UINT32                          i;

    /* 如果当前状态机不是PLMN SELECTION */
    if (NAS_MMC_FSM_PLMN_SELECTION != NAS_MMC_GetCurrFsmId())
    {
        NAS_ERROR_LOG(WUEPS_PID_MMC, "NAS_MMC_SetSearchDplmnAndHplmnFlg_PlmnSelection,ERROR:FsmId Error");
        return;
    }

    /* 查找选网状态机上下文中与enRat相同的接入技术数组 */
    for (i = 0 ; i < NAS_MML_MAX_RAT_NUM; i++)
    {
        if (enRat == (g_stNasMmcCtx.stCurFsm.unFsmCtx.stPlmnSelectionCtx.astSearchRatInfo[i].enRatType))
        {
            g_stNasMmcCtx.stCurFsm.unFsmCtx.stPlmnSelectionCtx.astSearchRatInfo[i].ucSearchDplmnAndHplmnFlg = ucSearchDplmnAndHplmnFlg;
            return;
        }
    }
}
/* Modified by c00318887 for DPlmn扩容和优先接入HPLMN, 2015-5-18, end */

/*lint -e438 -e830*/
/*****************************************************************************
 函 数 名  : NAS_MMC_InitSearchRatInfo_PlmnSelection
 功能描述  : 初始化搜网状态机上下文中不同接入技术的覆盖及搜索信息
 输入参数  : VOS_VOID
 输出参数  : 无
 返 回 值  : VOS_VOID
 调用函数  :
 被调函数  :

 修改历史      :
 1.日    期   : 2011年7月26日
   作    者   : L00171473
   修改内容   : 新生成函数
 2.日    期   : 2012年11月05日
   作    者   : w00176964
   修改内容   : DTS2011082405001:更新网络覆盖类型
 3.日    期   : 2013年02月01日
   作    者   : s00217060
   修改内容   : for DSDA GUNAS C CORE:增加平台接入技术能力的判断
 4.日    期   : 2014年3月19日
   作    者   : w00242748
   修改内容   : DTS2014031200137:当NV特性打开时，自动开机或者搜网时，如果首次搜索RPLMN的话，
                需要将HPLMN/EHPLMN带给接入层。
 5.日    期   : 2014年9月9日
   作    者   : z00161729
   修改内容   : DTS2014082807343:csfb搜网到gu后mmc搜网请求需带rplmn+eplmn，否则存在搜网慢T303超时呼叫失败场景
 6.日    期   : 2014年11月3日
   作    者   : z00161729
   修改内容   : 开机漫游搜网项目修改

 7.日    期   : 2015年5月21日
   作    者   : w00167002
   修改内容   : ROAM_PLMN_SELECTION_OPTIMIZE_2.0项目修改
 8.日    期   : 2015-5-18
   作    者   : c00318887
   修改内容   : DPlmn扩容和优先接入HPLMN
*****************************************************************************/
VOS_VOID NAS_MMC_InitSearchRatInfo_PlmnSelection(VOS_VOID)
{
    VOS_UINT32                          i;
    NAS_MMC_RAT_SEARCH_INFO_STRU       *pstSearchRatInfo = VOS_NULL_PTR;

    pstSearchRatInfo = &(g_stNasMmcCtx.stCurFsm.unFsmCtx.stPlmnSelectionCtx.astSearchRatInfo[0]);

     /* 先进行初始化，将剩余的初始化为无效值 */
    for (i = 0; i < NAS_MML_MAX_RAT_NUM; i++ )
    {
        pstSearchRatInfo[i].enRatType       = NAS_MML_NET_RAT_TYPE_BUTT;
        pstSearchRatInfo[i].ucSearchAllBand = VOS_FALSE;
        pstSearchRatInfo[i].enCoverageType  = NAS_MMC_COVERAGE_TYPE_BUTT;
        pstSearchRatInfo[i].ucSearchRplmnAndHplmnFlg   = VOS_FALSE;

        pstSearchRatInfo[i].ucSearchRplmnAndEplmnFlg = VOS_FALSE;

        pstSearchRatInfo[i].ucHistorySearchedFlag    = VOS_FALSE;
        /* Modified by c00318887 for DPlmn扩容和优先接入HPLMN, 2015-5-18, begin */
        pstSearchRatInfo[i].ucSearchDplmnAndHplmnFlg = VOS_FALSE;
        /* Modified by c00318887 for DPlmn扩容和优先接入HPLMN, 2015-5-18, end */

    }

    i = 0;

#if (FEATURE_ON == FEATURE_LTE)
    if (VOS_TRUE == NAS_MML_IsPlatformSupportLte())
    {
        /* 设置LTE接入技术未全频搜网,不存在覆盖 */
        pstSearchRatInfo[i].enRatType       = NAS_MML_NET_RAT_TYPE_LTE;
        pstSearchRatInfo[i].ucSearchAllBand = VOS_FALSE;
        pstSearchRatInfo[i].enCoverageType  = NAS_MMC_COVERAGE_TYPE_BUTT;
        pstSearchRatInfo[i].ucSearchRplmnAndHplmnFlg = VOS_FALSE;

        pstSearchRatInfo[i].ucSearchedRoamPlmnSortedFlag = VOS_FALSE;

        pstSearchRatInfo[i].ucSearchRplmnAndEplmnFlg = VOS_FALSE;
        /* Modified by c00318887 for DPlmn扩容和优先接入HPLMN, 2015-5-18, begin */
        pstSearchRatInfo[i].ucSearchDplmnAndHplmnFlg = VOS_FALSE;
        /* Modified by c00318887 for DPlmn扩容和优先接入HPLMN, 2015-5-18, end */

        i++;
    }
#endif

    if (VOS_TRUE == NAS_MML_IsPlatformSupportUtran())
    {
        /* 设置WCDMA接入技术未全频搜网,不存在覆盖 */
        pstSearchRatInfo[i].enRatType       = NAS_MML_NET_RAT_TYPE_WCDMA;
        pstSearchRatInfo[i].ucSearchAllBand = VOS_FALSE;
        pstSearchRatInfo[i].enCoverageType  = NAS_MMC_COVERAGE_TYPE_BUTT;
        pstSearchRatInfo[i].ucSearchRplmnAndHplmnFlg = VOS_FALSE;

        pstSearchRatInfo[i].ucSearchRplmnAndEplmnFlg = VOS_FALSE;
        /* Modified by c00318887 for DPlmn扩容和优先接入HPLMN, 2015-5-18, begin */
        pstSearchRatInfo[i].ucSearchDplmnAndHplmnFlg = VOS_FALSE;
        /* Modified by c00318887 for DPlmn扩容和优先接入HPLMN, 2015-5-18, end */

        i++;
    }

    if (VOS_TRUE == NAS_MML_IsPlatformSupportGsm())
    {
        /* 设置GSM接入技术未全频搜网,不存在覆盖 */
        pstSearchRatInfo[i].enRatType       = NAS_MML_NET_RAT_TYPE_GSM;
        pstSearchRatInfo[i].ucSearchAllBand = VOS_FALSE;
        pstSearchRatInfo[i].enCoverageType  = NAS_MMC_COVERAGE_TYPE_BUTT;
        pstSearchRatInfo[i].ucSearchRplmnAndHplmnFlg = VOS_FALSE;

        pstSearchRatInfo[i].ucSearchRplmnAndEplmnFlg = VOS_FALSE;
        /* Modified by c00318887 for DPlmn扩容和优先接入HPLMN, 2015-5-18, begin */
        pstSearchRatInfo[i].ucSearchDplmnAndHplmnFlg = VOS_FALSE;
        /* Modified by c00318887 for DPlmn扩容和优先接入HPLMN, 2015-5-18, end */

        i++;
    }

    return;
}

/*lint +e438 +e830*/


/*****************************************************************************
 函 数 名  : NAS_MMC_GetForbRoamLaInfo_PlmnSelection
 功能描述  : 获取网络选择状态机上下文中的禁止漫游位置区信息
 输入参数  : 无
 输出参数  : 无
 返 回 值  : 禁止漫游位置区信息地址
 调用函数  :
 被调函数  :

 修改历史    :
 1.日    期  : 2011年11月11日
   作    者  : w00167002
   修改内容  : 新生成函数

*****************************************************************************/
NAS_MML_FORBIDPLMN_ROAMING_LAS_INFO_STRU* NAS_MMC_GetForbRoamLaInfo_PlmnSelection(VOS_VOID)
{
    /* 如果当前状态机不是PLMN SELECTION */
    if (NAS_MMC_FSM_PLMN_SELECTION != NAS_MMC_GetCurrFsmId())
    {
        NAS_ERROR_LOG(WUEPS_PID_MMC, "NAS_MMC_GetForbRoamLaInfo_PlmnSelection,ERROR:FsmId Error");
    }

    return &(g_stNasMmcCtx.stCurFsm.unFsmCtx.stPlmnSelectionCtx.stForbRoamLaInfo);
}


/*****************************************************************************
 函 数 名  : NAS_MMC_GetForbPlmnForGrpsInfo_PlmnSelection
 功能描述  : 获取网络选择状态机上下文中的禁止PLMN FOR GPRS信息
 输入参数  : 无
 输出参数  : 无
 返 回 值  : 禁止PLMN信息地址
 调用函数  :
 被调函数  :

 修改历史    :
 1.日    期  : 2012年05月10日
   作    者  : l65478
   修改内容  : 新生成函数

*****************************************************************************/
NAS_MML_PLMN_ID_STRU* NAS_MMC_GetForbPlmnForGrpsInfo_PlmnSelection(VOS_VOID)
{
    /* 如果当前状态机不是PLMN SELECTION */
    if (NAS_MMC_FSM_PLMN_SELECTION != NAS_MMC_GetCurrFsmId())
    {
        NAS_ERROR_LOG(WUEPS_PID_MMC, "NAS_MMC_GetForbPlmnForGrpsInfo_PlmnSelection,ERROR:FsmId Error");
    }

    return &(g_stNasMmcCtx.stCurFsm.unFsmCtx.stPlmnSelectionCtx.stForbGprsPlmn);
}

/*****************************************************************************
 函 数 名  : NAS_MMC_SetCurrSearchingPlmn_PlmnSelection
 功能描述  : 设置PLMN SELECTION状态机上下文中正在搜索的plmn信息
 输入参数  : pstPlmnId -- PLMN SELECTION当前正在搜索的plmn信息
 输出参数  : 无
 返 回 值  : VOS_VOID
 调用函数  :
 被调函数  :

 修改历史      :
 1.日    期   : 2013年08月21日
   作    者   : z00161729
   修改内容   : 新生成函数

*****************************************************************************/
VOS_VOID NAS_MMC_SetCurrSearchingPlmn_PlmnSelection(
    NAS_MML_PLMN_WITH_RAT_STRU         *pstPlmnId
)
{
    /* 如果当前状态机不是PLMN SELECTION, 异常打印 */
    if ( NAS_MMC_FSM_PLMN_SELECTION != NAS_MMC_GetCurrFsmId() )
    {
        NAS_ERROR_LOG(WUEPS_PID_MMC, "NAS_MMC_SetCurrSearchingPlmn_PlmnSelection,ERROR:FsmId Error");
        return;
    }

    g_stNasMmcCtx.stCurFsm.unFsmCtx.stPlmnSelectionCtx.stCurrSearchingPlmn = *pstPlmnId;
}

/*****************************************************************************
 函 数 名  : NAS_MMC_GetCurrSearchingPlmn_PlmnSelection
 功能描述  : 设置PLMN SELECTION状态机上下文中的当前正在搜索的PLMN信息
 输入参数  : 无
 输出参数  : 无
 返 回 值  : PLMN SELECTION状态机正在搜索的plmn信息
 调用函数  :
 被调函数  :

 修改历史      :
 1.日    期   : 2013年08月21日
   作    者   : z00161729
   修改内容   : 新生成函数

*****************************************************************************/
NAS_MML_PLMN_WITH_RAT_STRU* NAS_MMC_GetCurrSearchingPlmn_PlmnSelection(VOS_VOID)
{
    /* 如果当前状态机不是PLMN SELECTION, 异常打印 */
    if ( NAS_MMC_FSM_PLMN_SELECTION != NAS_MMC_GetCurrFsmId() )
    {
        NAS_ERROR_LOG(WUEPS_PID_MMC, "NAS_MMC_GetCurrSearchingPlmn_PlmnSelection,ERROR:FsmId Error");
    }

    return &(g_stNasMmcCtx.stCurFsm.unFsmCtx.stPlmnSelectionCtx.stCurrSearchingPlmn);
}


/*****************************************************************************
 函 数 名  : NAS_MMC_SetCurrSearchingType_PlmnSelection
 功能描述  : 设置PLMN SELECTION状态机上下文中搜索的plmn类型
 输入参数  : enCurrSearchingPlmnType -- PLMN搜索的类型
 输出参数  : 无
 返 回 值  : VOS_VOID
 调用函数  :
 被调函数  :

 修改历史      :
 1.日    期   : 2015年05月22日
   作    者   : w00167002
   修改内容   : 新生成函数

*****************************************************************************/
VOS_VOID NAS_MMC_SetCurrSearchingType_PlmnSelection(
    NAS_MMC_PLMN_SEARCH_TYPE_ENUM_UINT32                    enCurrSearchingType
)
{
    /* 如果当前状态机不是PLMN SELECTION, 异常打印 */
    if ( NAS_MMC_FSM_PLMN_SELECTION != NAS_MMC_GetCurrFsmId() )
    {
        NAS_ERROR_LOG(WUEPS_PID_MMC, "NAS_MMC_SetCurrSearchingType_PlmnSelection,ERROR:FsmId Error");
        return;
    }

    g_stNasMmcCtx.stCurFsm.unFsmCtx.stPlmnSelectionCtx.enCurrSearchingType = enCurrSearchingType;
}

/*****************************************************************************
 函 数 名  : NAS_MMC_GetCurrSearchingType_PlmnSelection
 功能描述  : 获取PLMN SELECTION状态机上下文中搜索的plmn类型
 输入参数  : 无
 输出参数  : 无
 返 回 值  : PLMN SELECTION状态机搜索的plmn类型
 调用函数  :
 被调函数  :

 修改历史      :
1.日    期   : 2015年05月22日
   作    者   : w00167002
   修改内容   : 新生成函数

*****************************************************************************/
NAS_MMC_PLMN_SEARCH_TYPE_ENUM_UINT32 NAS_MMC_GetCurrSearchingType_PlmnSelection(VOS_VOID)
{
    /* 如果当前状态机不是PLMN SELECTION, 异常打印 */
    if ( NAS_MMC_FSM_PLMN_SELECTION != NAS_MMC_GetCurrFsmId() )
    {
        NAS_ERROR_LOG(WUEPS_PID_MMC, "NAS_MMC_GetCurrSearchingType_PlmnSelection,ERROR:FsmId Error");
    }

    return (g_stNasMmcCtx.stCurFsm.unFsmCtx.stPlmnSelectionCtx.enCurrSearchingType);
}



#if (FEATURE_ON == FEATURE_LTE)
/*****************************************************************************
 函 数 名  : NAS_MMC_SetCsPsMode1ReCampLtePlmn_PlmnSelection
 功能描述  : 设置PLMN SELECTION状态机上下文中需要重新驻留LTE的PLMN信息
 输入参数  : pstPlmnId -- PLMN SELECTION时驻留的PLMN ID
 输出参数  : 无
 返 回 值  : VOS_VOID
 调用函数  :
 被调函数  :

 修改历史      :
 1.日    期   : 2012年06月11日
   作    者   : s00217060
   修改内容   : 新生成函数

*****************************************************************************/
VOS_VOID NAS_MMC_SetCsPsMode1ReCampLtePlmn_PlmnSelection(
    NAS_MML_PLMN_ID_STRU               *pstPlmnId
)
{
    /* 如果当前状态机不是PLMN SELECTION, 异常打印 */
    if ( NAS_MMC_FSM_PLMN_SELECTION != NAS_MMC_GetCurrFsmId() )
    {
        NAS_ERROR_LOG(WUEPS_PID_MMC, "NAS_MMC_SetCsPsMode1ReCampLtePlmn_PlmnSelection,ERROR:FsmId Error");
        return;
    }

    g_stNasMmcCtx.stCurFsm.unFsmCtx.stPlmnSelectionCtx.stCsPsMode1ReCampLtePlmn = *pstPlmnId;
}

/*****************************************************************************
 函 数 名  : NAS_MMC_GetCsPsMode1ReCampLtePlmn_PlmnSelection
 功能描述  : 设置PLMN SELECTION状态机上下文中的当前驻留的PLMN信息
 输入参数  : 无
 输出参数  : 无
 返 回 值  : NAS_MML_PLMN_ID_STRU* -- PLMN SELECTION时驻留的PLMN ID
 调用函数  :
 被调函数  :

 修改历史      :
 1.日    期   : 2012年06月11日
   作    者   : s00217060
   修改内容   : 新生成函数

*****************************************************************************/
NAS_MML_PLMN_ID_STRU* NAS_MMC_GetCsPsMode1ReCampLtePlmn_PlmnSelection()
{
    /* 如果当前状态机不是PLMN SELECTION, 异常打印 */
    if ( NAS_MMC_FSM_PLMN_SELECTION != NAS_MMC_GetCurrFsmId() )
    {
        NAS_ERROR_LOG(WUEPS_PID_MMC, "NAS_MMC_GetCsPsMode1ReCampLtePlmn_PlmnSelection,ERROR:FsmId Error");
    }

    return &(g_stNasMmcCtx.stCurFsm.unFsmCtx.stPlmnSelectionCtx.stCsPsMode1ReCampLtePlmn);
}
#endif

/*****************************************************************************
 函 数 名  : NAS_MMC_GetAbortFlag_AnyCellSearch
 功能描述  : 获取AnycellPlmnSrch状态机上下文中的Abort标志
 输入参数  : VOS_VOID
 输出参数  : 无
 返 回 值  : VOS_UINT32
 调用函数  :
 被调函数  :

 修改历史      :
 1.日    期   : 2011年7月26日
   作    者   : L00171473
   修改内容   : 新生成函数

*****************************************************************************/
VOS_UINT32 NAS_MMC_GetAbortFlag_AnyCellSearch(VOS_VOID)
{
    /* 如果当前状态机不是ANYCELL PLMN SRCH */
    if (NAS_MMC_FSM_ANYCELL_SEARCH != NAS_MMC_GetCurrFsmId())
    {
        NAS_ERROR_LOG(WUEPS_PID_MMC, "NAS_MMC_GetAbortFlag_AnyCellSearch,ERROR:FsmId Error");
    }

    return (VOS_UINT32)(g_stNasMmcCtx.stCurFsm.unFsmCtx.stAnyCellSearchCtx.ucAbortFlag);
}

/*****************************************************************************
 函 数 名  : NAS_MMC_SetAbortFlag_AnyCellSearch
 功能描述  : 设置AnycellPlmnSrch状态机上下文中的Abort标志
 输入参数  : VOS_VOID
 输出参数  : 无
 返 回 值  : VOS_VOID
 调用函数  :
 被调函数  :

 修改历史      :
 1.日    期   : 2011年7月26日
   作    者   : L00171473
   修改内容   : 新生成函数

*****************************************************************************/
VOS_VOID NAS_MMC_SetAbortFlag_AnyCellSearch(
    VOS_UINT8                           ucAbortFlg
)
{
    /* 如果当前状态机不是ANYCELL PLMN SRCH */
    if (NAS_MMC_FSM_ANYCELL_SEARCH != NAS_MMC_GetCurrFsmId())
    {
        NAS_ERROR_LOG(WUEPS_PID_MMC, "NAS_MMC_SetAbortFlag_AnyCellSearch,ERROR:FsmId Error");
        return;
    }

    g_stNasMmcCtx.stCurFsm.unFsmCtx.stAnyCellSearchCtx.ucAbortFlag = ucAbortFlg;
}

/*****************************************************************************
 函 数 名  : NAS_MMC_GetFsmCtxAddr_AnyCellSearch
 功能描述  : 获取AnyCellSearch状态机的上下文的指针
 输入参数  : VOS_VOID
 输出参数  : 无
 返 回 值  : NAS_MMC_FSM_ANYCELL_SEARCH_CTX_STRU*
 调用函数  :
 被调函数  :

 修改历史      :
 1.日    期   : 2011年7月27日
   作    者   : L00171473
   修改内容   : 新生成函数

*****************************************************************************/
NAS_MMC_FSM_ANYCELL_SEARCH_CTX_STRU* NAS_MMC_GetFsmCtxAddr_AnyCellSearch(VOS_VOID)
{
    /* 如果当前状态机不是ANYCELL PLMN SRCH */
    if (NAS_MMC_FSM_ANYCELL_SEARCH != NAS_MMC_GetCurrFsmId())
    {
        NAS_ERROR_LOG(WUEPS_PID_MMC, "NAS_MMC_GetFsmCtxAddr_AnyCellSearch,ERROR:FsmId Error");
    }

    return &(g_stNasMmcCtx.stCurFsm.unFsmCtx.stAnyCellSearchCtx);
}

/*****************************************************************************
 函 数 名  : NAS_MMC_GetRatNum_AnyCellSearch
 功能描述  : 获取AnyCell状态机支持的接入技术的个数
 输入参数  : VOS_VOID
 输出参数  : 无
 返 回 值  : VOS_UINT8
 调用函数  :
 被调函数  :

 修改历史      :
 1.日    期   : 2011年7月27日
   作    者   : L00171473
   修改内容   : 新生成函数

*****************************************************************************/
VOS_UINT8 NAS_MMC_GetRatNum_AnyCellSearch(VOS_VOID)
{
    /* 如果当前状态机不是ANYCELL PLMN SRCH */
    if (NAS_MMC_FSM_ANYCELL_SEARCH != NAS_MMC_GetCurrFsmId())
    {
        NAS_ERROR_LOG(WUEPS_PID_MMC, "NAS_MMC_GetRatNum_AnyCellSearch,ERROR:FsmId Error");
    }

    return g_stNasMmcCtx.stCurFsm.unFsmCtx.stAnyCellSearchCtx.stMmcPlmnRatPrio.ucRatNum;
}

/*****************************************************************************
 函 数 名  : NAS_MMC_DelMsUnsupportRat
 功能描述  : 删除MS不支持的接入技术
 输入参数  : pstRatPrioList:接入技术优先级列表
 输出参数  : pstRatPrioList:删除了MS不支持的接入技术优先级列表
 返 回 值  : 无
 调用函数  :
 被调函数  :

 修改历史      :
 1.日    期   : 2012年10月8日
   作    者   : t00212959
   修改内容   : 新生成函数
*****************************************************************************/
VOS_VOID NAS_MMC_DelMsUnsupportRat(
    NAS_MML_PLMN_RAT_PRIO_STRU         *pstRatPrioList
)
{
    NAS_MML_PLMN_RAT_PRIO_STRU          stNewPrioList;
    NAS_MML_PLMN_RAT_PRIO_STRU         *pstMsPrioRatList  = VOS_NULL_PTR;
    VOS_UINT32                          ulRatIndex;
    VOS_UINT32                          ulMsRatIndex;

    VOS_UINT8                          ucNewRatNum;
    ucNewRatNum      = NAS_MMC_NUM_ZERO;
    pstMsPrioRatList = NAS_MML_GetMsPrioRatList();

    /*初始化中间结构变量*/
    stNewPrioList.ucRatNum = ucNewRatNum;
    for ( ulRatIndex = 0 ; ulRatIndex < NAS_MML_MAX_RAT_NUM; ulRatIndex++ )
    {
        stNewPrioList.aucRatPrio[ulRatIndex] = NAS_MML_NET_RAT_TYPE_BUTT;
    }

    for ( ulRatIndex = 0 ; ulRatIndex < pstRatPrioList->ucRatNum; ulRatIndex++ )
    {
        for ( ulMsRatIndex = 0 ; ulMsRatIndex < pstMsPrioRatList->ucRatNum; ulMsRatIndex++ )
        {
            if (pstRatPrioList->aucRatPrio[ulRatIndex] == pstMsPrioRatList->aucRatPrio[ulMsRatIndex])
            {
                stNewPrioList.aucRatPrio[ucNewRatNum]= pstRatPrioList->aucRatPrio[ulRatIndex];
                ucNewRatNum++;
                stNewPrioList.ucRatNum = ucNewRatNum;
            }
        }
    }

    pstRatPrioList->ucRatNum = stNewPrioList.ucRatNum;
    for ( ulRatIndex = 0 ; ulRatIndex < NAS_MML_MAX_RAT_NUM; ulRatIndex++ )
    {
        pstRatPrioList->aucRatPrio[ulRatIndex] = stNewPrioList.aucRatPrio[ulRatIndex];
    }

    return;
}

/*****************************************************************************
 函 数 名  : NAS_MMC_SetRatPrioList_AnyCellSearch
 功能描述  : 设置AnyCell状态机支持的接入技术列表
 输入参数  : VOS_VOID
 输出参数  : 无
 返 回 值  : VOS_UINT8
 调用函数  :
 被调函数  :

 修改历史      :
 1.日    期   : 2011年8月12日
   作    者   : l00130025
   修改内容   : 新生成函数
 2.日    期   : 2012年10月8日
   作    者   : z00161729
   修改内容   : DTS2012083007796:无卡支持语音业务时开机应优先选择gu下anycell驻留
 3.日    期   : 2015年9月17日
   作    者   : w00167002
   修改内容   : DTS2015091602371:澳电需求，优先2G/3G anycell搜索
*****************************************************************************/
VOS_VOID NAS_MMC_SetRatPrioList_AnyCellSearch(
    NAS_MML_PLMN_RAT_PRIO_STRU         *pstRatPrioList
)
{
    NAS_MML_PLMN_RAT_PRIO_STRU         *pstAnycellPrioList = VOS_NULL_PTR;
    VOS_UINT32                          i;

#if (FEATURE_ON == FEATURE_LTE)
    NAS_MML_PLMN_RAT_PRIO_STRU          stAnycellSrchRatList;
    VOS_UINT8                           ucIndex;
    VOS_UINT32                          ulIsLteOnly;
    VOS_UINT8                           ucSupportCsServiceFlg;
    VOS_UINT8                           ucSimCsPsRegStatus;
    NAS_MML_SIM_STATUS_STRU            *pstSimStatus = VOS_NULL_PTR;
    VOS_UINT32                          ulIsSupportLte;
    NAS_MML_MS_MODE_ENUM_UINT8          enMsMode;

    /* Added by w00167002 for DTS2015091602371 澳电低优先级ANYCELL搜LTE定制, 2015-9-17, begin */

    VOS_UINT8                           ucLowPrioAnycellSearchLteFlg;
    ucLowPrioAnycellSearchLteFlg        = NAS_MML_GetLowPrioAnycellSearchLteFlg();
    /* Added by w00167002 for DTS2015091602371 澳电低优先级ANYCELL搜LTE定制, 2015-9-17, end */

    pstSimStatus          = NAS_MML_GetSimStatus();
    ucSimCsPsRegStatus    = VOS_TRUE;
    ulIsLteOnly           = NAS_MML_IsLteOnlyMode(pstRatPrioList);
    ucSupportCsServiceFlg = NAS_MML_GetSupportCsServiceFLg();
    ulIsSupportLte        = NAS_MML_IsSpecRatInRatList(NAS_MML_NET_RAT_TYPE_LTE,
                                                       pstRatPrioList);
    ucIndex               = 0;
    enMsMode              = NAS_MML_GetMsMode();
    PS_MEM_SET(&stAnycellSrchRatList, (VOS_CHAR)0x0, sizeof(NAS_MML_PLMN_RAT_PRIO_STRU));

    if (( VOS_FALSE == pstSimStatus->ucSimPsRegStatus)
     && ( VOS_FALSE == pstSimStatus->ucSimCsRegStatus))
    {
        ucSimCsPsRegStatus = VOS_FALSE;
    }
#endif

    /* 如果当前状态机不是ANYCELL PLMN SRCH */
    if (NAS_MMC_FSM_ANYCELL_SEARCH != NAS_MMC_GetCurrFsmId())
    {
        NAS_ERROR_LOG(WUEPS_PID_MMC, "NAS_MMC_SetRatPrioList_AnyCellSearch,ERROR:FsmId Error");
    }

    pstAnycellPrioList = &(g_stNasMmcCtx.stCurFsm.unFsmCtx.stAnyCellSearchCtx.stMmcPlmnRatPrio);

    pstAnycellPrioList->ucRatNum = pstRatPrioList->ucRatNum;

    for ( i = 0 ; i < pstRatPrioList->ucRatNum; i++ )
    {
        pstAnycellPrioList->aucRatPrio[i] = pstRatPrioList->aucRatPrio[i];
    }

    /* 45008协议描述: If the mobile station supports CS voice services,the MS shall avoid
       reselecting acceptable(but not suitable) E-UTRA cells regardless of the priorities
       in system information,支持cs语音业务，无卡或csps卡均无效导致的anycell搜，非L单模，不是ps only
       (软银有用例ps only被3、6、8拒绝需要待在L),将L的接入技术排在最后 */
#if (FEATURE_ON == FEATURE_LTE)

    /* Modified by w00167002 for DTS2015091602371 澳电低优先级ANYCELL搜LTE定制, 2015-9-17, begin */
    if ( (((VOS_FALSE == NAS_MML_GetSimPresentStatus())
         || (VOS_FALSE == ucSimCsPsRegStatus)
         || (VOS_TRUE == ucLowPrioAnycellSearchLteFlg))
        && (VOS_TRUE == ucSupportCsServiceFlg)
        && (VOS_FALSE == ulIsLteOnly)
        && (VOS_TRUE == ulIsSupportLte)
        && (NAS_MML_MS_MODE_PS_ONLY != enMsMode)))
    /* Modified by w00167002 for DTS2015091602371 澳电低优先级ANYCELL搜LTE定制, 2015-9-17, begin */
    {
        for (i = 0; i < pstRatPrioList->ucRatNum; i++)
        {
            if (pstRatPrioList->aucRatPrio[i] != NAS_MML_NET_RAT_TYPE_LTE)
            {
                stAnycellSrchRatList.aucRatPrio[ucIndex] = pstRatPrioList->aucRatPrio[i];
                ucIndex++;
            }
        }

        stAnycellSrchRatList.aucRatPrio[ucIndex] = NAS_MML_NET_RAT_TYPE_LTE;
        ucIndex++;
        stAnycellSrchRatList.ucRatNum = ucIndex;
        PS_MEM_CPY(pstAnycellPrioList, &stAnycellSrchRatList, sizeof(stAnycellSrchRatList));
    }
#endif

    return;
}

/*****************************************************************************
 函 数 名  : NAS_MMC_GetNextSearchRat_AnyCellSearch
 功能描述  : ANY CELL搜索时获取下个要搜索的网络接入技术
 输入参数  : 无
 输出参数  : 无
 返 回 值  : NAS_MML_NET_RAT_TYPE_ENUM_UINT8: 接入技术

 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2011年4月26日
    作    者   : w00176964
    修改内容   : 新生成函数
  2.日    期   : 2011年7月27日
    作    者   : L00171473
    修改内容   : V7R1 phase II 修改
  3.日    期   : 2011年11月30日
    作    者   : w00176964
    修改内容   : V7R1 Phase IV调整:disable/enable 调整以及detach调整

  4.日    期   : 2012年9月15日
    作    者   : z40661
    修改内容   : DTS2012082006273,未通知L
****************************************************************************/

NAS_MML_NET_RAT_TYPE_ENUM_UINT8 NAS_MMC_GetNextSearchRat_AnyCellSearch(VOS_VOID)
{
    NAS_MMC_FSM_ANYCELL_SEARCH_CTX_STRU                    *pstAnyCellSearchCtx = VOS_NULL_PTR;
    VOS_UINT32                                              i;
    VOS_UINT8                                               ucRatNum;

#if (FEATURE_ON == FEATURE_LTE)
    NAS_MML_LTE_CAPABILITY_STATUS_ENUM_UINT32               enLteCapabilityStatus;
#endif

    /* 如果当前状态机不是ANYCELL PLMN SRCH */
    if (NAS_MMC_FSM_ANYCELL_SEARCH != NAS_MMC_GetCurrFsmId())
    {
        NAS_ERROR_LOG(WUEPS_PID_MMC, "NAS_MMC_GetNextSearchRat_AnyCellSearch,ERROR:FsmId Error");
    }

    pstAnyCellSearchCtx   = NAS_MMC_GetFsmCtxAddr_AnyCellSearch();
    ucRatNum = NAS_MMC_GetRatNum_AnyCellSearch();

    for ( i = 0; i < ucRatNum; i++)
    {
#if (FEATURE_ON == FEATURE_LTE)

        /* 获取LTE的能力状态 */
        enLteCapabilityStatus   = NAS_MML_GetLteCapabilityStatus();

        /* 接入技术为LTE且当前LTE状态为disable时，不选择LTE的接入技术 */
        if (((NAS_MML_LTE_CAPABILITY_STATUS_DISABLE_UNNOTIFY_AS  == enLteCapabilityStatus)
          || (NAS_MML_LTE_CAPABILITY_STATUS_DISABLE_NOTIFIED_AS  == enLteCapabilityStatus))
         && (NAS_MML_NET_RAT_TYPE_LTE   == pstAnyCellSearchCtx->stMmcPlmnRatPrio.aucRatPrio[i]))
        {
            continue;
        }
#endif

        if ( VOS_FALSE == pstAnyCellSearchCtx->aucSearchedFlag[i])
        {
            /* 获取下个未搜索过的接入技术 */
            return pstAnyCellSearchCtx->stMmcPlmnRatPrio.aucRatPrio[i];
        }
    }

    /* 获取下个未搜索过的接入技术失败 */
    return NAS_MML_NET_RAT_TYPE_BUTT;
}

/*****************************************************************************
 函 数 名  : NAS_MMC_SetSearchedFlag_AnyCellSearch
 功能描述  : 根据传入的接入技术，设置该接入技术的搜索状态为已搜过
 输入参数  : enSpecRat:需更新的接入技术
 输出参数  : 无
 返 回 值  : 无
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2011年4月26日
    作    者   : w00176964
    修改内容   : 新生成函数
  2.日    期   : 2011年7月27日
    作    者   : L00171473
    修改内容   : V7R1 phase II 修改
****************************************************************************/

VOS_VOID NAS_MMC_SetSearchedFlag_AnyCellSearch(
    NAS_MML_NET_RAT_TYPE_ENUM_UINT8     enSpecRat
)
{
    NAS_MMC_FSM_ANYCELL_SEARCH_CTX_STRU                    *pstAnyCellSearchCtx = VOS_NULL_PTR;
    VOS_UINT32                                              i;

    /* 如果当前状态机不是ANYCELL PLMN SRCH */
    if (NAS_MMC_FSM_ANYCELL_SEARCH != NAS_MMC_GetCurrFsmId())
    {
        NAS_ERROR_LOG(WUEPS_PID_MMC, "NAS_MMC_SetSearchedFlag_AnyCellSearch,ERROR:FsmId Error");
        return;
    }

    /* 获取AnyCell搜网状态机的上下文地址 */
    pstAnyCellSearchCtx   = NAS_MMC_GetFsmCtxAddr_AnyCellSearch();

    for (i = 0; i < NAS_MMC_GetRatNum_AnyCellSearch(); i++)
    {
        if ( enSpecRat == pstAnyCellSearchCtx->stMmcPlmnRatPrio.aucRatPrio[i])
        {
            /* 设置该接入技术为已搜过 */
            pstAnyCellSearchCtx->aucSearchedFlag[i] = VOS_TRUE;
        }
    }

    return;

}


/*****************************************************************************
 函 数 名  : NAS_MMC_InitFsmCtx_SysCfg
 功能描述  : SYSCFG状态机上下文的初始化
 输入参数  : 无
 输出参数  : 无
 返 回 值  : 无

 调用函数  :
 被调函数  :

 修改历史      :
 1.日    期   : 2011-07-10
   作    者   : w00167002
   修改内容   : 新生成函数
 2.日    期   : 2011年12月1日
   作    者   : w00176964
   修改内容   : GUNAS V7R1 PhaseIV 阶段调整
 3.日    期   : 2012年8月15日
   作    者   : z00161729
   修改内容   : DCM定制需求和遗留问题修改
 4.日    期   : 2015年9月16日
   作    者   : wx270776
   修改内容   : SYSCFG上报顺序修改
****************************************************************************/
VOS_VOID NAS_MMC_InitFsmCtx_SysCfg(VOS_VOID)
{
    NAS_MMC_SYSCFG_SETTING_CTRL_STRU   *pstSyscfgSettingRecord  = VOS_NULL_PTR;

    /* Modified by z00161729 for DCM定制需求和遗留问题, 2012-8-15, begin */
    NAS_MML_PLMN_RAT_PRIO_STRU          stPrePrioRatList;
    /* Modified by z00161729 for DCM定制需求和遗留问题, 2012-8-15, end */

    /* 获取状态机中的要设置SYSCFG接入模所对应的索引和列表地址 */
    pstSyscfgSettingRecord              = NAS_MMC_GetSysCfgSettingRecord_SysCfg();

    NAS_MMC_SetRelRequestFlag_SysCfg(VOS_FALSE);

    /* SYSCFG状态机上下文中搜网的初始化:默认不需要搜网 */
    NAS_MMC_SetPlmnSearchFlag_SysCfg(VOS_FALSE);

    /* SYSCFG状态机上下文中设置接入层优先级顺序信息的初始化:
       搜网索引初始化为0,每设置SYSCFG后，该索引自增1，表示要设置SYSCFG的接入模式 */
    pstSyscfgSettingRecord->ucSetCurrSyscfgIndex = 0;

    /* 设置需要下发SYSCFG的总个数 */
    pstSyscfgSettingRecord->ucTotalSyscfgNum = 0;

    /* 初始设置下发SYSCFG请求的顺序为LUG，如果平台不支持某个接入技术，不给该接入技术发送请求 */
#if (FEATURE_ON == FEATURE_LTE)
    if (VOS_TRUE == NAS_MML_IsPlatformSupportLte())
    {
        pstSyscfgSettingRecord->aucSyscfgRatPrio[pstSyscfgSettingRecord->ucTotalSyscfgNum] = NAS_MML_NET_RAT_TYPE_LTE;
        pstSyscfgSettingRecord->ucTotalSyscfgNum++;
    }
#endif

    if (VOS_TRUE == NAS_MML_IsPlatformSupportUtran())
    {
        pstSyscfgSettingRecord->aucSyscfgRatPrio[pstSyscfgSettingRecord->ucTotalSyscfgNum] = NAS_MML_NET_RAT_TYPE_WCDMA;
        pstSyscfgSettingRecord->ucTotalSyscfgNum++;
    }

    if (VOS_TRUE == NAS_MML_IsPlatformSupportGsm())
    {
        pstSyscfgSettingRecord->aucSyscfgRatPrio[pstSyscfgSettingRecord->ucTotalSyscfgNum] = NAS_MML_NET_RAT_TYPE_GSM;
        pstSyscfgSettingRecord->ucTotalSyscfgNum++;
    }

    /* Modified by z00161729 for DCM定制需求和遗留问题, 2012-8-15, begin */
#if (FEATURE_ON == FEATURE_LTE)
    stPrePrioRatList.ucRatNum     = 0;
    stPrePrioRatList.aucRatPrio[0]= NAS_MML_NET_RAT_TYPE_BUTT;
    stPrePrioRatList.aucRatPrio[1]= NAS_MML_NET_RAT_TYPE_BUTT;
    stPrePrioRatList.aucRatPrio[2]= NAS_MML_NET_RAT_TYPE_BUTT;
#else
    stPrePrioRatList.ucRatNum     = 0;
    stPrePrioRatList.aucRatPrio[0]= NAS_MML_NET_RAT_TYPE_BUTT;
    stPrePrioRatList.aucRatPrio[1]= NAS_MML_NET_RAT_TYPE_BUTT;
#endif

    NAS_MMC_SetPrePrioRatList_SysCfg(&stPrePrioRatList);
    /* Modified by z00161729 for DCM定制需求和遗留问题, 2012-8-15, end */
    return ;
}


/*****************************************************************************
 函 数 名  : NAS_MMC_SysCfg_GetSyscfgSettingRecord
 功能描述  : 获取状态机中的NAS_MMC_SYSCFG_SETTING_CTRL_STRU结构值
 输入参数  : 无
 输出参数  : 无
 返 回 值  : SYSCFG状态机上下文中的记录设置接入层优先级顺序信息

 调用函数  :
 被调函数  :

 修改历史      :
 1.日    期   : 2011-07-10
   作    者   : w00167002
   修改内容   : 新生成函数

****************************************************************************/
NAS_MMC_SYSCFG_SETTING_CTRL_STRU* NAS_MMC_GetSysCfgSettingRecord_SysCfg(VOS_VOID)
{
    NAS_MMC_CONTEXT_STRU               *pstNasMmcCtx        = VOS_NULL_PTR;
    pstNasMmcCtx = NAS_MMC_GetMmcCtxAddr();

    /* 如果当前状态机不是NAS_MMC_FSM_SYSCFG */
    if (NAS_MMC_FSM_SYSCFG != NAS_MMC_GetCurrFsmId())
    {
        NAS_ERROR_LOG(WUEPS_PID_MMC, "NAS_MMC_GetSysCfgSettingRecord_SysCfg,ERROR:FsmId Error");
    }

    return &(pstNasMmcCtx->stCurFsm.unFsmCtx.stSyscfgCtx.stSyscfgSettingRecord);
}

/* Modified by z00161729 for DCM定制需求和遗留问题, 2012-8-15, begin */
/*****************************************************************************
 函 数 名  : NAS_MMC_SetPrePrioRatList_SysCfg
 功能描述  : 设置状态机上下文中syscfg设置前的接入技术和优先级
 输入参数  : pstPrePrioRatList - 接入技术和优先级
 输出参数  : 无
 返 回 值  : 无
 调用函数  :
 被调函数  :

 修改历史      :
 1.日    期   : 2012-08-15
   作    者   : z00161729
   修改内容   : 新生成函数

****************************************************************************/
VOS_VOID NAS_MMC_SetPrePrioRatList_SysCfg(
    NAS_MML_PLMN_RAT_PRIO_STRU          *pstPrePrioRatList
)
{
    /* 如果当前状态机不是NAS_MMC_FSM_SYSCFG */
    if (NAS_MMC_FSM_SYSCFG != NAS_MMC_GetCurrFsmId())
    {
        NAS_ERROR_LOG(WUEPS_PID_MMC, "NAS_MMC_SetPrePrioRatList_SysCfg,ERROR:FsmId Error");
    }

    NAS_MMC_GetMmcCtxAddr()->stCurFsm.unFsmCtx.stSyscfgCtx.stPrePrioRatList
                   = *pstPrePrioRatList;
    return;
}

/*****************************************************************************
 函 数 名  : NAS_MMC_GetPrePrioRatList_SysCfg
 功能描述  : 获取状态机上下文中syscfg设置前的接入技术和优先级
 输入参数  : 无
 输出参数  : 无
 返 回 值  : 接入技术和优先级
 调用函数  :
 被调函数  :

 修改历史      :
 1.日    期   : 2012-08-15
   作    者   : z00161729
   修改内容   : 新生成函数

****************************************************************************/
NAS_MML_PLMN_RAT_PRIO_STRU* NAS_MMC_GetPrePrioRatList_SysCfg(VOS_VOID)
{
    /* 如果当前状态机不是NAS_MMC_FSM_SYSCFG */
    if (NAS_MMC_FSM_SYSCFG != NAS_MMC_GetCurrFsmId())
    {
        NAS_ERROR_LOG(WUEPS_PID_MMC, "NAS_MMC_GetPrePrioRatList_SysCfg,ERROR:FsmId Error");
    }

    return &(NAS_MMC_GetMmcCtxAddr()->stCurFsm.unFsmCtx.stSyscfgCtx.stPrePrioRatList);
}

/* Modified by z00161729 for DCM定制需求和遗留问题, 2012-8-15, end */

/*****************************************************************************
 函 数 名  : NAS_MMC_AddSysCfgIndex_SysCfg
 功能描述  : 设置下一个需要设置SYSCFG模的接入技术
 输入参数  : 无
 输出参数  : 无
 返 回 值  : 无

 调用函数  :
 被调函数  :

 修改历史      :
 1.日    期   : 2011年7月2日
   作    者   : w00167002
   修改内容   : 新生成函数

*****************************************************************************/
VOS_VOID NAS_MMC_AddSysCfgIndex_SysCfg(VOS_VOID)
{
    NAS_MMC_SYSCFG_SETTING_CTRL_STRU   *pstSysCfgRecord     = VOS_NULL_PTR;

    /* 如果当前状态机不是NAS_MMC_FSM_SYSCFG */
    if (NAS_MMC_FSM_SYSCFG != NAS_MMC_GetCurrFsmId())
    {
        NAS_ERROR_LOG(WUEPS_PID_MMC, "NAS_MMC_AddSysCfgIndex_SysCfg,ERROR:FsmId Error");
    }

    /* 获取状态机中的要设置SYSCFG接入模所对应的索引和列表地址 */
    pstSysCfgRecord   = NAS_MMC_GetSysCfgSettingRecord_SysCfg();

    /* 更新INDEX索引,指向下一个要进行SYSCFG设置的接入技术 */
    pstSysCfgRecord->ucSetCurrSyscfgIndex ++;

    /* 返回 */
    return ;
}



/*****************************************************************************
 函 数 名  : NAS_MMC_GetNextSettingRat_SysCfg
 功能描述  : 获取下一个需要设置SYSCFG模的接入技术
 输入参数  : 无
 输出参数  : 无
 返 回 值  : NAS_MML_NET_RAT_TYPE_ENUM_UINT8类型:接入技术,列举如下
             NAS_MML_NET_RAT_TYPE_GSM,
             NAS_MML_NET_RAT_TYPE_WCDMA,
             NAS_MML_NET_RAT_TYPE_LTE,
             NAS_MML_NET_RAT_TYPE_BUTT

 调用函数  :
 被调函数  :

 修改历史      :
 1.日    期   : 2011年7月2日
   作    者   : w00167002
   修改内容   : 新生成函数

*****************************************************************************/
NAS_MML_NET_RAT_TYPE_ENUM_UINT8 NAS_MMC_GetNextSettingRat_SysCfg(VOS_VOID)
{
    NAS_MML_NET_RAT_TYPE_ENUM_UINT8    *pucSyscfgRatPrio    = VOS_NULL_PTR;
    NAS_MMC_SYSCFG_SETTING_CTRL_STRU   *pstSysCfgRecord     = VOS_NULL_PTR;
    NAS_MML_NET_RAT_TYPE_ENUM_UINT8     ucNextSyscfgRat;

    /* 如果当前状态机不是NAS_MMC_FSM_SYSCFG */
    if (NAS_MMC_FSM_SYSCFG != NAS_MMC_GetCurrFsmId())
    {
        NAS_ERROR_LOG(WUEPS_PID_MMC, "NAS_MMC_GetNextSettingRat_SysCfg,ERROR:FsmId Error");
    }

    pstSysCfgRecord      = NAS_MMC_GetSysCfgSettingRecord_SysCfg();

    /* 获取状态机中的要设置SYSCFG接入模所对应的索引和列表地址 */
    pucSyscfgRatPrio     = pstSysCfgRecord->aucSyscfgRatPrio;

    /* 如果索引以到达设置的总个数，返回接入技术为无效值，表示SYSCFG设置结束 */
    if ( pstSysCfgRecord->ucSetCurrSyscfgIndex >= pstSysCfgRecord->ucTotalSyscfgNum )
    {
        return NAS_MML_NET_RAT_TYPE_BUTT;
    }

    /* 取得数组中索引所对应的接入技术 */
    ucNextSyscfgRat                     = pucSyscfgRatPrio[pstSysCfgRecord->ucSetCurrSyscfgIndex];

    /* 返回需要SYSCFG设置的接入技术 */
    return ucNextSyscfgRat;
}

/*****************************************************************************
 函 数 名  : NAS_MMC_GetPlmnSearchFlag_SysCfg
 功能描述  : 获取SYSCFG状态机中是否需要搜网的信息
 输入参数  : 无
 输出参数  : 无
 返 回 值  : 返回SYSCFG状态机中是否需要搜网的信息地址；
 调用函数  :
 被调函数  :

 修改历史      :
 1.日    期   : 2011-07-18
   作    者   : w00167002
   修改内容   : 新生成函数

****************************************************************************/
VOS_UINT32  NAS_MMC_GetPlmnSearchFlag_SysCfg(VOS_VOID)
{
    NAS_MMC_CONTEXT_STRU               *pstNasMmcCtx        = VOS_NULL_PTR;

    /* 如果当前状态机不是NAS_MMC_FSM_SYSCFG */
    if (NAS_MMC_FSM_SYSCFG != NAS_MMC_GetCurrFsmId())
    {
        NAS_ERROR_LOG(WUEPS_PID_MMC, "NAS_MMC_GetNextSettingRat_SysCfg,ERROR:FsmId Error");
    }

    pstNasMmcCtx = NAS_MMC_GetMmcCtxAddr();

    return (pstNasMmcCtx->stCurFsm.unFsmCtx.stSyscfgCtx.ulNeedSearchPlmnFlag);
}

/*****************************************************************************
 函 数 名  : NAS_MMC_SetPlmnSearchFlag_SysCfg
 功能描述  : 更新SYSCFG状态机中是否需要搜网的信息
 输入参数  : 是否需要搜网的信息
 输出参数  : 无
 返 回 值  : 无
 调用函数  :
 被调函数  :

 修改历史      :
 1.日    期   : 2011-07-20
   作    者   : z00161729
   修改内容   : 新生成函数

****************************************************************************/
VOS_VOID NAS_MMC_SetPlmnSearchFlag_SysCfg(VOS_UINT32 ulNeedSearchPlmnFlag)
{
    /* 如果当前状态机不是NAS_MMC_FSM_SYSCFG */
    if (NAS_MMC_FSM_SYSCFG != NAS_MMC_GetCurrFsmId())
    {
        NAS_ERROR_LOG(WUEPS_PID_MMC, "NAS_MMC_GetNextSettingRat_SysCfg,ERROR:FsmId Error");
    }

    g_stNasMmcCtx.stCurFsm.unFsmCtx.stSyscfgCtx.ulNeedSearchPlmnFlag = ulNeedSearchPlmnFlag;
    return;
}


/*****************************************************************************
 函 数 名  : NAS_MMC_SysCfg_SetSendingSysCfgOrder
 功能描述  : 设置向接入层下发SYSCFG的先后顺序
 输入参数  : enDestRat: 目标模的接入技术
 输出参数  : 无
 返 回 值  : 无
 调用函数  :
 被调函数  :

 修改历史      :
 1.日    期   : 2011年7月11日
   作    者   : w00167002
   修改内容   : 新生成函数

 2.日    期   : 2011年11月30日
   作    者   : w00167002
   修改内容   : DTS2011113001438:设置MMC通知GUL接入层顺序更改为目标模最后通知.

                修改原因:syscfgex设置模式或频段改变时MMC需要通知GUL 3个接入模，
                目前通知3个接入层的顺序为先发主模，再发送从模，从模的顺序默认
                为L优先于W优先于G。如at^syscfgex=? ^syscfgex:"0201",3FFFFFFF,1,2,7FFFFFFFFFFFFFFF,0,0.
                当前驻留W模,后面at^syscfgex="03",3FFFFFFF,1,2,7FFFFFFFFFFFFFFF,0,0
                设置只支持L,MMC先给主模W发送RRMM_SYS_CFG_REQ,收到W的RRMM_SYS_CFG_CNF回复,
                再给L发送ID_MMC_LMM_SYS_CFG_REQ,收到L的ID_LMM_MMC_SYS_CFG_CNF,
                最后给G发送RRMM_SYS_CFG_REQ。主模W收到RRMM_SYS_CFG_REQ请求会
                deactive自己并通知L启动测量，但此时L还没收到ID_MMC_LMM_SYS_CFG_REQ
                通知L支持，会无法处理，导致syscfg设置后没有主模可用。现MMC
                需要修改通知GUL 3个接入层的顺序为目标模最后通知。

 3.日    期   : 2012年12月26日
   作    者   : s00217060
   修改内容   : for DSDA GUNAS C CORE:调整为只给平台支持的接入层发送SYSCFG请求

 4.日    期   : 2015年9月7日
   作    者   : wx270776
   修改内容   : 1.触发点：
                  Austin三卡三待上MODEM0和MODEM2的GPHY公用一个GBBP，所以需求一个GPHY使用GBBP之后，
                  需要等到GBBP完全睡眠后，另一个GPHY才能使用GBBP。
                2.现有方案不可行（SYSCFG顺序调整后可行）：
                  方案描述：由GAS在SYSCFG流程等到GBBP睡眠后，给NAS回复SYSCFG_CNF。
                  问题描述：W主模，G从模，W测量G，SYSCFG去激活G模。GAS先收到SYSCFG_REQ，
                            GAS无法先停止WPHY测量再停止GPHY的测量，也就是无法彻底停掉W测量G，
                            因也就无法等到GPHY睡眠再回复SYSCFG_CNF。
                3.SYSCFG顺序规则描述：
                  新增进来的模式优先下发，多个新增之间不指定顺序。 剩下的模式先主模再从模，
                  多个主模之间不指定顺序，多个从模之间不指定顺序。

*****************************************************************************/
VOS_VOID NAS_MMC_SetSysCfgSendingOrder_SysCfg(
    MSCC_MMC_SYS_CFG_SET_REQ_STRU      *pstSysCfgMsg
)
{
    VOS_UINT32                          i;
    /* 保存新增的接入技术列表 */
    NAS_MML_PLMN_RAT_PRIO_STRU          stTempRatList;
    /* 保存SYSCFG上报的顺序 */
    NAS_MML_PLMN_RAT_PRIO_STRU          stSyscfgSendingOrder;
    NAS_MMC_SYSCFG_SETTING_CTRL_STRU   *pstSyscfgSettingRecord = VOS_NULL_PTR;

    /* 如果当前状态机不是NAS_MMC_FSM_SYSCFG */
    if (NAS_MMC_FSM_SYSCFG != NAS_MMC_GetCurrFsmId())
    {
        NAS_ERROR_LOG(WUEPS_PID_MMC, "NAS_MMC_SetSysCfgSendingOrder_SysCfg,ERROR:FsmId Error");
    }

    /* 取得当前 SYSCFG状态机上下文中的记录设置接入层优先级顺序信息 */
    pstSyscfgSettingRecord  = NAS_MMC_GetSysCfgSettingRecord_SysCfg();

    /* 初始化 */
    PS_MEM_SET(&stSyscfgSendingOrder, 0x00, sizeof(stSyscfgSendingOrder));
    stSyscfgSendingOrder.ucRatNum = pstSyscfgSettingRecord->ucTotalSyscfgNum;
    PS_MEM_CPY( stSyscfgSendingOrder.aucRatPrio,
                pstSyscfgSettingRecord->aucSyscfgRatPrio,
                sizeof(pstSyscfgSettingRecord->aucSyscfgRatPrio) );

    /* 1. 找出新增的接入技术，放入临时的列表中 */
    NAS_MML_GetNewRatFromRatList( NAS_MML_GetMsPrioRatList(),
                                  &(pstSysCfgMsg->stRatPrioList),
                                  &stTempRatList );

    /* 2. 将当前主模优先级设置到最高 */
    NAS_MML_SortSpecRatPrioHighest( NAS_MML_GetCurrNetRatType(),
                                    &stSyscfgSendingOrder );

    /* 3. 将新增的接入技术排序到接入技术列表表首 */
    for ( i = stTempRatList.ucRatNum; i > 0 ; i-- )
    {
        NAS_MML_SortSpecRatPrioHighest( stTempRatList.aucRatPrio[i-1],
                                        &stSyscfgSendingOrder );
    }

    /* 将SYSCFG上报顺序存入全局变量中 */
    pstSyscfgSettingRecord->ucTotalSyscfgNum = stSyscfgSendingOrder.ucRatNum;
    PS_MEM_CPY( pstSyscfgSettingRecord->aucSyscfgRatPrio,
                stSyscfgSendingOrder.aucRatPrio,
                sizeof(pstSyscfgSettingRecord->aucSyscfgRatPrio) );

    return;
}

/*****************************************************************************
 函 数 名  : NAS_MMC_GetRelRequestFlag_SysCfg
 功能描述  : 获取SysCfg状态机上下文中的是否主动请求连接标志
 输入参数  : 无
 输出参数  : 无
 返 回 值  : VOS_TRUE :是主动请求
             VOS_FALSE:被动等待释放
 调用函数  :
 被调函数  :

 修改历史      :
 1.日    期   : 2011年12月01日
   作    者   : w00176964
   修改内容   : 新生成函数

*****************************************************************************/
VOS_UINT8 NAS_MMC_GetRelRequestFlag_SysCfg(VOS_VOID)
{
    /* 如果当前状态机不是 SysCfg, 异常打印 */
    if (NAS_MMC_FSM_SYSCFG != NAS_MMC_GetCurrFsmId())
    {
        NAS_ERROR_LOG(WUEPS_PID_MMC, "NAS_MMC_GetRelRequestFlag_SysCfg,ERROR:FsmId Error");
    }

    return (g_stNasMmcCtx.stCurFsm.unFsmCtx.stSyscfgCtx.ucRelRequestFlg);
}

/*****************************************************************************
 函 数 名  : NAS_MMC_SetRelRequestFlag_SysCfg
 功能描述  : 设置SysCfg状态机上下文中的是否主动请求连接标志
 输入参数  : ucRelRequestFlg: 是否主动请求连接标志
 输出参数  : 无
 返 回 值  : 无
 调用函数  :
 被调函数  :

 修改历史      :
 1.日    期   : 2011年12月01日
   作    者   : w00176964
   修改内容   : 新生成函数

*****************************************************************************/
VOS_VOID NAS_MMC_SetRelRequestFlag_SysCfg(
    VOS_UINT8                           ucRelRequestFlg
)
{
    /* 如果当前状态机不是 SysCfg, 异常打印  */
    if (NAS_MMC_FSM_SYSCFG !=NAS_MMC_GetCurrFsmId())
    {
        NAS_ERROR_LOG(WUEPS_PID_MMC, "NAS_MMC_SetRelRequestFlag_SysCfg,ERROR:FsmId Error");
        return ;
    }

    g_stNasMmcCtx.stCurFsm.unFsmCtx.stSyscfgCtx.ucRelRequestFlg = ucRelRequestFlg;
}

/*****************************************************************************
 函 数 名  : NAS_MMC_IsCurrentPlmnIdRoamingAllowed_SysCfg
 功能描述  : 判断SYSCFG设置导致当前驻留的网络是否允许漫游
 输入参数  : pstSysCfgSetParm:用户SYSCFG设置的消息
 输出参数  : 无
 返 回 值  : VOS_TRUE  : SYSCFG设置导致当前驻留的网络允许漫游
             VOS_FALSE : SYSCFG设置导致当前驻留的网络不允许漫游
 被调函数  :
 修改历史      :
 1.日    期   : 2011年08月04日
   作    者   : w00167002
   修改内容   : 新生成函数
 2.日    期   : 2011年11月24日
   作    者   : w00167002
   修改内容   : DTS2011112405567:原有的函数名NAS_MML_IsPlmnIdInDestPlmnList
               更改为NAS_MML_IsBcchPlmnIdInDestSimPlmnList,用于明确判断
               网络的类型，否则网络比较可能会出错
  3.日    期   : 2013年3月30日
    作    者   : l00167671
    修改内容   : 主动上报AT命令控制下移至C核
*****************************************************************************/
VOS_UINT32 NAS_MMC_IsCurrentPlmnIdRoamingAllowed_SysCfg(
    MSCC_MMC_SYS_CFG_SET_REQ_STRU        *pstSysCfgSetParm
)
{
    NAS_MML_ROAM_CFG_INFO_STRU         *pstRoamCfg          = VOS_NULL_PTR;
    NAS_MML_PLMN_ID_STRU               *pstPlmnId           = VOS_NULL_PTR;
    VOS_UINT32                          ulFlg;

    /* 如果当前状态机不是NAS_MMC_FSM_SYSCFG */
    if (NAS_MMC_FSM_SYSCFG != NAS_MMC_GetCurrFsmId())
    {
        NAS_ERROR_LOG(WUEPS_PID_MMC, "NAS_MMC_IsCurrentPlmnIdRoamingAllowed_SysCfg,ERROR:FsmId Error");
    }

    pstRoamCfg      = NAS_MML_GetRoamCfg();

    /* 取得当前驻留的PLMN ID */
    pstPlmnId       = NAS_MML_GetCurrCampPlmnId();

    /* 与HPLMN相同，直接返回允许 */
    if (VOS_TRUE == NAS_MML_ComparePlmnIdWithHplmn(pstPlmnId))
    {
        return VOS_TRUE;
    }

    /* 漫游特性开关关闭，直接返回允许 */
    if (VOS_FALSE == pstRoamCfg->ucRoamFeatureFlg)
    {
        return VOS_TRUE;
    }

    /* Modified by l00167671 for 主动上报AT命令控制下移至C核, 2013-3-30, begin */
    /* 允许漫游时直接返回允许 */
    if (NAS_MSCC_PIF_ROAM_NATION_ON_INTERNATION_ON == pstSysCfgSetParm->enRoamCapability)
    {
        return VOS_TRUE;
    }


    /* 判断当前网络是否在允许国内漫游列表中 */
    ulFlg = NAS_MML_IsBcchPlmnIdInDestSimPlmnList( pstPlmnId,
                                            pstRoamCfg->ucNationalRoamNum,
                                            pstRoamCfg->astRoamPlmnIdList );

    /* 若SYSCFG设置准许进行国内漫游，且当前网络在允许国内漫游列表中，返回准许漫游 */
    if ( (NAS_MSCC_PIF_ROAM_NATION_ON_INTERNATION_OFF == pstSysCfgSetParm->enRoamCapability)
      && (VOS_TRUE == ulFlg) )
    {
        return VOS_TRUE;
    }

    /* 若SYSCFG设置不准许进行国内漫游，且当前网络在漫游不支持时可以注册网络中，返回准许漫游 */
    ulFlg = NAS_MML_IsBcchPlmnIdInDestSimPlmnList( pstPlmnId,
                                            pstRoamCfg->ucNotRoamNum,
                                            pstRoamCfg->astRoamPlmnIdList );
    if ( ( (NAS_MSCC_PIF_ROAM_NATION_OFF_INTERNATION_ON == pstSysCfgSetParm->enRoamCapability)
        || (NAS_MSCC_PIF_ROAM_NATION_OFF_INTERNATION_OFF == pstSysCfgSetParm->enRoamCapability) )
      && (VOS_TRUE == ulFlg) )
    {
        return VOS_TRUE;
    }
	/* Modified by l00167671 for 主动上报AT命令控制下移至C核, 2013-3-30, end */

    /* 否则返回不允许漫游 */
    return VOS_FALSE;
}

/* LIST搜网状态机上下文操作函数 */
/*****************************************************************************
 函 数 名  : NAS_MMC_InitSearchRatInfo_PlmnList
 功能描述  : PLMN LIST搜网状态机运行过程中初始化需要搜索的接入技术信息
 输入参数  : 无
 输出参数  : 无
 返 回 值  : 无
 调用函数  :
 被调函数  :

 修改历史      :
 1.日    期   : 2011年9月15日
   作    者   : w00176964
   修改内容   : 新生成函数

*****************************************************************************/

VOS_VOID NAS_MMC_InitSearchRatInfo_PlmnList(VOS_VOID)
{
    VOS_UINT32                          i;
    NAS_MMC_PLMN_LIST_SEARCH_CTRL_STRU *pstSearchRatInfo = VOS_NULL_PTR;
    NAS_MML_PLMN_RAT_PRIO_STRU         *pstRatPrioList   = VOS_NULL_PTR;
    NAS_MML_PLMN_RAT_PRIO_STRU          stTmpPrioRatList;

    PS_MEM_SET(&stTmpPrioRatList, 0, sizeof(NAS_MML_PLMN_RAT_PRIO_STRU));

    /* 当前不是PLMN LIST状态机 异常打印 */
    if ( NAS_MMC_FSM_PLMN_LIST != NAS_MMC_GetCurrFsmId())
    {
        NAS_ERROR_LOG(WUEPS_PID_MMC, "NAS_MMC_InitSearchRatInfo_PlmnList,ERROR:FsmId Error");

        return;
    }

    pstSearchRatInfo    = NAS_MMC_GetSearchCtrlInfo_PlmnList();

    pstRatPrioList      = NAS_MML_GetMsPrioRatList();

    /* 构造一份临时接入技术列表, 便于调整 */
    PS_MEM_CPY(&stTmpPrioRatList, pstRatPrioList, sizeof(NAS_MML_PLMN_RAT_PRIO_STRU));

    /* 当前接入技术存在,当前接入技术排在最前面 */
    if ( NAS_MML_NET_RAT_TYPE_BUTT != NAS_MML_GetCurrNetRatType())
    {
        NAS_MML_SortSpecRatPrioHighest(NAS_MML_GetCurrNetRatType(), &stTmpPrioRatList);
    }

    /* 初始化接入技术优先级列表以及搜索标记 */
    for (i = 0; i < stTmpPrioRatList.ucRatNum; i++ )
    {
        pstSearchRatInfo[i].enRat           = stTmpPrioRatList.aucRatPrio[i];
        pstSearchRatInfo[i].ucSearchedFlag  = VOS_FALSE;
    }
}


/*****************************************************************************
 函 数 名  : NAS_MMC_GetSearchRatInfo_PlmnList
 功能描述  : PLMN LIST搜网状态机运行过程中获取搜索的接入技术优先级列表信息以及搜索记录
 输入参数  : 无
 输出参数  : 无
 返 回 值  : PLMN LIST搜索的接入技术优先级列表信息以及搜索记录
 调用函数  :
 被调函数  :

 修改历史      :
 1.日    期   : 2011年9月22日
   作    者   : w00176964
   修改内容   : 新生成函数

*****************************************************************************/
NAS_MMC_PLMN_LIST_SEARCH_CTRL_STRU *NAS_MMC_GetSearchCtrlInfo_PlmnList(VOS_VOID)
{
    /* 当前不是PLMN LIST状态机 异常打印 */
    if ( NAS_MMC_FSM_PLMN_LIST != NAS_MMC_GetCurrFsmId())
    {
       NAS_ERROR_LOG(WUEPS_PID_MMC, "NAS_MMC_GetSearchRatInfo_PlmnList,ERROR:FsmId Error");
    }

    return &(g_stNasMmcCtx.stCurFsm.unFsmCtx.stPlmnListCtx.astPlmnListCtrlInfo[0]);
}

/*****************************************************************************
 函 数 名  : NAS_MMC_GetNextSearchingRat_PlmnList
 功能描述  : PLMN LIST搜网状态机运行过程中获取下个需要搜索的接入技术
 输入参数  : 无
 输出参数  : penRat 下个需要搜索的接入技术
 返 回 值  : 获取到返回VOS_TRUE
             获取不到返回VOS_FALSE
 调用函数  :
 被调函数  :

 修改历史      :
 1.日    期   : 2011年9月15日
   作    者   : w00176964
   修改内容   : 新生成函数

*****************************************************************************/

VOS_UINT32  NAS_MMC_GetNextSearchingRat_PlmnList(
    NAS_MML_NET_RAT_TYPE_ENUM_UINT8    *penRat
)
{
    NAS_MMC_PLMN_LIST_SEARCH_CTRL_STRU *pstSearchRatInfo = VOS_NULL_PTR;
    VOS_UINT32                          i;
    VOS_UINT8                           ucRatNum;

    /* 当前不是PLMN LIST状态机 异常打印 */
    if ( NAS_MMC_FSM_PLMN_LIST != NAS_MMC_GetCurrFsmId())
    {
        NAS_ERROR_LOG(WUEPS_PID_MMC, "NAS_MMC_GetNextSearchRat_PlmnList,ERROR:FsmId Error");
    }

    pstSearchRatInfo    = NAS_MMC_GetSearchCtrlInfo_PlmnList();
    ucRatNum            = NAS_MML_GetMsPrioRatList()->ucRatNum;

    for ( i = 0; i < ucRatNum; i++)
    {
        if ( VOS_FALSE == pstSearchRatInfo[i].ucSearchedFlag)
        {
            /* 获取下个未搜索过的接入技术 */
            *penRat  = pstSearchRatInfo[i].enRat;
            return VOS_TRUE;
        }
    }

    /* 获取下个未搜索过的接入技术失败 */
    return VOS_FALSE;
}

/*****************************************************************************
 函 数 名  : NAS_MMC_GetOrigenSearchRat_PlmnList
 功能描述  : PLMN LIST搜网状态机运行过程中获取初始搜索的接入技术
 输入参数  : 无
 输出参数  : penRat 初始搜索的接入技术
 返 回 值  : 无
 调用函数  :
 被调函数  :

 修改历史      :
 1.日    期   : 2011年9月20日
   作    者   : w00176964
   修改内容   : 新生成函数

*****************************************************************************/

VOS_VOID NAS_MMC_GetOrigenSearchRat_PlmnList(
    NAS_MML_NET_RAT_TYPE_ENUM_UINT8    *penRat
)
{
    NAS_MMC_PLMN_LIST_SEARCH_CTRL_STRU *pstSearchRatInfo = VOS_NULL_PTR;

    /* 当前不是PLMN LIST状态机 异常打印 */
    if ( NAS_MMC_FSM_PLMN_LIST != NAS_MMC_GetCurrFsmId())
    {
        NAS_ERROR_LOG(WUEPS_PID_MMC, "NAS_MMC_GetOrigenSearchRat_PlmnList,ERROR:FsmId Error");
    }

    pstSearchRatInfo    = NAS_MMC_GetSearchCtrlInfo_PlmnList();

    *penRat = pstSearchRatInfo[0].enRat;
}

/*****************************************************************************
 函 数 名  : NAS_MMC_SetSearchedFlag_PlmnList
 功能描述  : PLMN LIST搜网状态机运行过程中设置指定的接入技术搜索过
 输入参数  : enSpecRat 已经搜索过的接入技术
 输出参数  : 无
 返 回 值  : 无
 调用函数  :
 被调函数  :

 修改历史      :
 1.日    期   : 2011年9月15日
   作    者   : w00176964
   修改内容   : 新生成函数

*****************************************************************************/

VOS_VOID NAS_MMC_SetSearchedFlag_PlmnList(
    NAS_MML_NET_RAT_TYPE_ENUM_UINT8     enSpecRat
)
{
    VOS_UINT32                              i;
    VOS_UINT8                               ucRatNum;
    NAS_MMC_PLMN_LIST_SEARCH_CTRL_STRU     *pstSearchRatInfo = VOS_NULL_PTR;
    NAS_MMC_SEARCHED_PLMN_LIST_INFO_STRU   *pstListInfo      = VOS_NULL_PTR;

    /* 当前不是PLMN LIST状态机 异常打印 */
    if ( NAS_MMC_FSM_PLMN_LIST != NAS_MMC_GetCurrFsmId())
    {
       NAS_ERROR_LOG(WUEPS_PID_MMC, "NAS_MMC_SetSearchedFlag_PlmnList,ERROR:FsmId Error");
       return ;
    }

    pstSearchRatInfo    = NAS_MMC_GetSearchCtrlInfo_PlmnList();
    ucRatNum            = NAS_MML_GetMsPrioRatList()->ucRatNum;
    pstListInfo         = NAS_MMC_GetSearchedPlmnListInfo_PlmnList();

    for ( i = 0; i < ucRatNum; i++)
    {
       if ( enSpecRat == pstSearchRatInfo[i].enRat )
       {
           pstSearchRatInfo[i].ucSearchedFlag = VOS_TRUE;

           /* 更新搜索到的网络列表中所带的接入技术，便于后续根据接入技术对列表进行更新 */
           pstListInfo[i].enRatType           = enSpecRat;
           break;
       }
    }

    return;
}

/*****************************************************************************
 函 数 名  : NAS_MMC_GetAbortFlag_PlmnList
 功能描述  : PLMN LIST搜网状态机运行过程中获取状态机打断标记
 输入参数  : 无
 输出参数  : 无
 返 回 值  : 状态机打断标记
 调用函数  :
 被调函数  :

 修改历史      :
 1.日    期   : 2011年9月15日
   作    者   : w00176964
   修改内容   : 新生成函数

*****************************************************************************/

VOS_UINT8 NAS_MMC_GetAbortFlag_PlmnList(VOS_VOID)
{
    /* 当前不是PLMN LIST状态机 异常打印 */
    if ( NAS_MMC_FSM_PLMN_LIST != NAS_MMC_GetCurrFsmId())
    {
       NAS_ERROR_LOG(WUEPS_PID_MMC, "NAS_MMC_GetAbortFlag_PlmnList,ERROR:FsmId Error");
    }

    return g_stNasMmcCtx.stCurFsm.unFsmCtx.stPlmnListCtx.ucAbortFlg;
}

/*****************************************************************************
 函 数 名  : NAS_MMC_SetAbortFlag_PlmnList
 功能描述  : PLMN LIST搜网状态机运行过程中设置状态机打断标记
 输入参数  : 状态机打断标记
 输出参数  : 无
 返 回 值  : 无
 调用函数  :
 被调函数  :

 修改历史      :
 1.日    期   : 2011年9月15日
   作    者   : w00176964
   修改内容   : 新生成函数

*****************************************************************************/

VOS_VOID NAS_MMC_SetAbortFlag_PlmnList(
    VOS_UINT8                           ucAbortFlg
)
{
    /* 当前不是PLMN LIST状态机 异常打印 */
    if ( NAS_MMC_FSM_PLMN_LIST != NAS_MMC_GetCurrFsmId())
    {
       NAS_ERROR_LOG(WUEPS_PID_MMC, "NAS_MMC_SetAbortFlag_PlmnList,ERROR:FsmId Error");

       return;
    }

    g_stNasMmcCtx.stCurFsm.unFsmCtx.stPlmnListCtx.ucAbortFlg = ucAbortFlg;
}

/*****************************************************************************
 函 数 名  : NAS_MMC_GetNotifyMsccFlag_PlmnList
 功能描述  : PLMN LIST搜网状态机运行过程中获取通知MSCC结果的标记
 输入参数  : 无
 输出参数  : 无
 返 回 值  : 是否通知MSCC结果的标记
 调用函数  :
 被调函数  :

 修改历史      :
 1.日    期   : 2011年9月20日
   作    者   : w00176964
   修改内容   : 新生成函数

*****************************************************************************/

VOS_UINT8 NAS_MMC_GetNotifyMsccFlag_PlmnList(VOS_VOID)
{
    /* 当前不是PLMN LIST状态机 异常打印 */
    if ( NAS_MMC_FSM_PLMN_LIST != NAS_MMC_GetCurrFsmId())
    {
       NAS_ERROR_LOG(WUEPS_PID_MMC, "NAS_MMC_GetNotifyMsccFlag_PlmnList,ERROR:FsmId Error");
    }

    return g_stNasMmcCtx.stCurFsm.unFsmCtx.stPlmnListCtx.ucNotifyMsccFlg;
}

/*****************************************************************************
 函 数 名  : NAS_MMC_SetNotifyMsccFlag_PlmnList
 功能描述  : PLMN LIST搜网状态机运行过程中设置通知MSCC结果的标记
 输入参数  : 通知MSCC结果的标记
 输出参数  : 无
 返 回 值  : 无
 调用函数  :
 被调函数  :

 修改历史      :
 1.日    期   : 2011年9月20日
   作    者   : w00176964
   修改内容   : 新生成函数

*****************************************************************************/

VOS_VOID NAS_MMC_SetNotifyMsccFlag_PlmnList(
    VOS_UINT8                           ucNotifyFlg
)
{
    /* 当前不是PLMN LIST状态机 异常打印 */
    if ( NAS_MMC_FSM_PLMN_LIST != NAS_MMC_GetCurrFsmId())
    {
       NAS_ERROR_LOG(WUEPS_PID_MMC, "NAS_MMC_SetNotifyMsccFlag_PlmnList,ERROR:FsmId Error");

       return;
    }

    g_stNasMmcCtx.stCurFsm.unFsmCtx.stPlmnListCtx.ucNotifyMsccFlg= ucNotifyFlg;
}

/*****************************************************************************
 函 数 名  : NAS_MMC_GetWaitRegRsltFlag_PlmnList
 功能描述  : 获取状态机上下文中的等待CS/PS的注册结果的标志
 输入参数  : 无
 输出参数  : 无
 返 回 值  : VOS_UINT8
 调用函数  :
 被调函数  :

 修改历史     :
 1.日    期   : 2011年9月19日
   作    者   : w00176964
   修改内容   : 新生成函数

*****************************************************************************/
VOS_UINT8 NAS_MMC_GetWaitRegRsltFlag_PlmnList(VOS_VOID)
{
    /* 当前不是PLMN LIST状态机 异常打印 */
    if ( NAS_MMC_FSM_PLMN_LIST != NAS_MMC_GetCurrFsmId())
    {
       NAS_ERROR_LOG(WUEPS_PID_MMC, "NAS_MMC_GetWaitRegRsltFlag_PlmnList,ERROR:FsmId Error");
    }

    return g_stNasMmcCtx.stCurFsm.unFsmCtx.stPlmnListCtx.stRegRsltInfo.ucWaitRegRsltFlag;
}

/*****************************************************************************
 函 数 名  : NAS_MMC_SetWaitRegRsltFlag_PlmnList
 功能描述  : 设置状态机上下文中的等待CS/PS的注册结果的标志
 输入参数  : NAS_MMC_WAIT_REG_RSLT_IND_ENUM_UINT8
 输出参数  : 无
 返 回 值  : VOS_VOID
 调用函数  :
 被调函数  :

 修改历史     :
 1.日    期   : 2011年9月19日
   作    者   : w00176964
   修改内容   : 新生成函数

*****************************************************************************/
VOS_VOID NAS_MMC_SetWaitRegRsltFlag_PlmnList(
    VOS_UINT8       ucWaitFlag
)
{
    /* 当前不是PLMN LIST状态机 异常打印 */
    if ( NAS_MMC_FSM_PLMN_LIST != NAS_MMC_GetCurrFsmId())
    {
       NAS_ERROR_LOG(WUEPS_PID_MMC, "NAS_MMC_SetWaitRegRsltFlag_PlmnList,ERROR:FsmId Error");

       return;
    }

    g_stNasMmcCtx.stCurFsm.unFsmCtx.stPlmnListCtx.stRegRsltInfo.ucWaitRegRsltFlag |= ucWaitFlag;
}

/*****************************************************************************
 函 数 名  : NAS_MMC_ClearSingleDomainWaitRegRsltFlag_PlmnList
 功能描述  : 清除状态机上下文中的等待指定域的注册结果的标志
 输入参数  : ucRegRslt    CS+PS注册结果
 输出参数  : 无
 返 回 值  : VOS_VOID
 调用函数  :
 被调函数  :

 修改历史     :
 1.日    期   : 2011年9月19日
   作    者   : w00176964
   修改内容   : 新生成函数

*****************************************************************************/
VOS_VOID NAS_MMC_ClearSingleDomainWaitRegRsltFlag_PlmnList(
    VOS_UINT8                           ucRegRslt
)
{
    /* 当前不是PLMN LIST状态机 异常打印 */
    if ( NAS_MMC_FSM_PLMN_LIST != NAS_MMC_GetCurrFsmId())
    {
       NAS_ERROR_LOG(WUEPS_PID_MMC, "NAS_MMC_ClearSingleDomainWaitRegRsltFlag_PlmnList,ERROR:FsmId Error");

       return;
    }

    g_stNasMmcCtx.stCurFsm.unFsmCtx.stPlmnListCtx.stRegRsltInfo.ucWaitRegRsltFlag &= ~ucRegRslt;
}

/*****************************************************************************
 函 数 名  : NAS_MMC_ClearAllWaitRegRsltFlag_PlmnList
 功能描述  : 清除状态机上下文中的等待CS/PS域的注册结果的标志
 输入参数  : 无
 输出参数  : 无
 返 回 值  : VOS_VOID
 调用函数  :
 被调函数  :

 修改历史     :
 1.日    期   : 2011年9月19日
   作    者   : w00176964
   修改内容   : 新生成函数

*****************************************************************************/
VOS_VOID NAS_MMC_ClearAllWaitRegRsltFlag_PlmnList(VOS_VOID)
{
    /* 当前不是PLMN LIST状态机 异常打印 */
    if ( NAS_MMC_FSM_PLMN_LIST != NAS_MMC_GetCurrFsmId())
    {
       NAS_ERROR_LOG(WUEPS_PID_MMC, "NAS_MMC_ClearAllWaitRegRsltFlag_PlmnList,ERROR:FsmId Error");
       return;
    }

    g_stNasMmcCtx.stCurFsm.unFsmCtx.stPlmnListCtx.stRegRsltInfo.ucWaitRegRsltFlag = NAS_MMC_WAIT_REG_RESULT_IND_NULL;
}


/*****************************************************************************
 函 数 名  : NAS_MMC_GetCsRegAdditionalAction_PlmnList
 功能描述  : 获取状态机上下文中的CS注册结果触发的后续动作
 输入参数  : 无
 输出参数  : 无
 返 回 值  : NAS_MMC_ADDITIONAL_ACTION_ENUM_UINT8
 调用函数  :
 被调函数  :

 修改历史     :
 1.日    期   : 2011年9月30日
   作    者   : w00176964
   修改内容   : 新生成函数

*****************************************************************************/
NAS_MMC_ADDITIONAL_ACTION_ENUM_UINT8 NAS_MMC_GetCsRegAdditionalAction_PlmnList(VOS_VOID)
{

    /* 如果当前状态机不是PLMN LIST */
    if (NAS_MMC_FSM_PLMN_LIST != NAS_MMC_GetCurrFsmId())
    {
        NAS_ERROR_LOG(WUEPS_PID_MMC, "NAS_MMC_GetCsRegAdditionalAction_PlmnList,ERROR:FsmId Error");
    }

    return g_stNasMmcCtx.stCurFsm.unFsmCtx.stPlmnListCtx.stRegRsltInfo.enCsRegAdditionalAction;
}

/*****************************************************************************
 函 数 名  : NAS_MMC_SetCsRegAdditionalAction_PlmnList
 功能描述  : 设置状态机上下文中的CS注册结果触发的后续动作
 输入参数  : NAS_MMC_ADDITIONAL_ACTION_ENUM_UINT8
 输出参数  : 无
 返 回 值  : VOS_VOID
 调用函数  :
 被调函数  :

 修改历史     :
 1.日    期   : 2011年9月30日
   作    者   : w00176964
   修改内容   : 新生成函数

*****************************************************************************/
VOS_VOID NAS_MMC_SetCsRegAdditionalAction_PlmnList(
    NAS_MMC_ADDITIONAL_ACTION_ENUM_UINT8 enCsAddtionalAction
)
{
    /* 如果当前状态机不是PLMN LIST */
    if (NAS_MMC_FSM_PLMN_LIST != NAS_MMC_GetCurrFsmId())
    {
        NAS_ERROR_LOG(WUEPS_PID_MMC, "NAS_MMC_SetCsRegAdditionalAction_PlmnList,ERROR:FsmId Error");
        return;
    }

    g_stNasMmcCtx.stCurFsm.unFsmCtx.stPlmnListCtx.stRegRsltInfo.enCsRegAdditionalAction = enCsAddtionalAction;
}

/*****************************************************************************
 函 数 名  : NAS_MMC_GetPsRegAdditionalAction_PlmnList
 功能描述  : 获取状态机上下文中的PS注册结果触发的后续动作
 输入参数  : 无
 输出参数  : 无
 返 回 值  : NAS_MMC_ADDITIONAL_ACTION_ENUM_UINT8
 调用函数  :
 被调函数  :

 修改历史     :
 1.日    期   : 2011年9月30日
   作    者   : w00176964
   修改内容   : 新生成函数

*****************************************************************************/
NAS_MMC_ADDITIONAL_ACTION_ENUM_UINT8 NAS_MMC_GetPsRegAdditionalAction_PlmnList(VOS_VOID)
{
    /* 如果当前状态机不是PLMN LIST */
    if (NAS_MMC_FSM_PLMN_LIST != NAS_MMC_GetCurrFsmId())
    {
        NAS_ERROR_LOG(WUEPS_PID_MMC, "NAS_MMC_GetPsRegAdditionalAction_PlmnList,ERROR:FsmId Error");
    }

    return g_stNasMmcCtx.stCurFsm.unFsmCtx.stPlmnListCtx.stRegRsltInfo.enPsRegAdditionalAction;
}

/*****************************************************************************
 函 数 名  : NAS_MMC_SetPsRegAdditionalAction_PlmnList
 功能描述  : 设置状态机上下文中的PS注册结果触发的后续动作
 输入参数  : NAS_MMC_ADDITIONAL_ACTION_ENUM_UINT8
 输出参数  : 无
 返 回 值  : VOS_VOID
 调用函数  :
 被调函数  :

 修改历史     :
 1.日    期   : 2011年9月30日
   作    者   : w00176964
   修改内容   : 新生成函数

*****************************************************************************/
VOS_VOID NAS_MMC_SetPsRegAdditionalAction_PlmnList(
    NAS_MMC_ADDITIONAL_ACTION_ENUM_UINT8  enPsAddtionalAction
)
{
    /* 如果当前状态机不是PLMN LIST */
    if (NAS_MMC_FSM_PLMN_LIST != NAS_MMC_GetCurrFsmId())
    {
        NAS_ERROR_LOG(WUEPS_PID_MMC, "NAS_MMC_SetPsRegAdditionalAction_PlmnList,ERROR:FsmId Error");
        return;
    }

    g_stNasMmcCtx.stCurFsm.unFsmCtx.stPlmnListCtx.stRegRsltInfo.enPsRegAdditionalAction = enPsAddtionalAction;
}


/*****************************************************************************
 函 数 名  : NAS_MMC_GetRegRsltInfo_PlmnList
 功能描述  : 获取状态机上下文中的注册结果信息
 输入参数  : 无
 输出参数  : 无
 返 回 值  : NAS_MMC_PLMN_LIST_REG_RSLT_INFO_STRU*
 调用函数  :
 被调函数  :

 修改历史     :
 1.日    期   : 2011年9月30日
   作    者   : w00176964
   修改内容   : 新生成函数

*****************************************************************************/
NAS_MMC_PLMN_LIST_REG_RSLT_INFO_STRU *NAS_MMC_GetRegRsltInfo_PlmnList(VOS_VOID)
{
    /* 如果当前状态机不是PLMN LIST */
    if (NAS_MMC_FSM_PLMN_LIST != NAS_MMC_GetCurrFsmId())
    {
        NAS_ERROR_LOG(WUEPS_PID_MMC, "NAS_MMC_GetRegRsltInfo_PlmnList,ERROR:FsmId Error");
    }

    return &(g_stNasMmcCtx.stCurFsm.unFsmCtx.stPlmnListCtx.stRegRsltInfo);
}

/*****************************************************************************
 函 数 名  : NAS_MMC_InitSearchedPlmnListInfo_PlmnList
 功能描述  : PLMN LIST搜网状态机运行过程中初始化搜索到的网络列表信息
 输入参数  : 无
 输出参数  : 无
 返 回 值  : 无
 调用函数  :
 被调函数  :

 修改历史      :
 1.日    期   : 2011年9月15日
   作    者   : w00176964
   修改内容   : 新生成函数
 2.日    期   : 2012年11月05日
   作    者   : w00176964
   修改内容   : DTS2011082405001:初始化网络覆盖类型
*****************************************************************************/

VOS_VOID NAS_MMC_InitSearchedPlmnListInfo_PlmnList(VOS_VOID)
{
    VOS_UINT32                                              i;
    VOS_UINT32                                              j;
    VOS_UINT32                                              k;
    NAS_MMC_SEARCHED_PLMN_LIST_INFO_STRU                   *pstListInfo     = VOS_NULL_PTR;

    /* 当前不是PLMN LIST状态机 异常打印*/
    if ( NAS_MMC_FSM_PLMN_LIST != NAS_MMC_GetCurrFsmId() )
    {
       NAS_ERROR_LOG(WUEPS_PID_MMC, "NAS_MMC_InitSearchedPlmnListInfo_PlmnList,ERROR:FsmId Error");
       return;
    }

    pstListInfo         = NAS_MMC_GetSearchedPlmnListInfo_PlmnList();

    for ( i= 0; i < NAS_MML_MAX_RAT_NUM; i++ )
    {
        pstListInfo[i].enRatType        = NAS_MML_NET_RAT_TYPE_BUTT;
        pstListInfo[i].ulHighPlmnNum    = 0;
        pstListInfo[i].ulLowPlmnNum     = 0;
        pstListInfo[i].enCoverType      = NAS_MMC_COVERAGE_TYPE_BUTT;

        /* 高优先级列表 */
        for ( j = 0; j < NAS_MMC_INTRA_MAX_HIGH_QUALITY_PLMN_NUM; j++ )
        {
            pstListInfo[i].astHighPlmnList[j].ulMcc = NAS_MML_INVALID_MCC;
            pstListInfo[i].astHighPlmnList[j].ulMnc = NAS_MML_INVALID_MNC;
        }

        /* 低优先级列表 */
        for ( k = 0; k < NAS_MMC_INTRA_MAX_LOW_QUALITY_PLMN_NUM; k++)
        {
            pstListInfo[i].astLowPlmnList[k].stPlmnId.ulMcc = NAS_MML_INVALID_MCC;
            pstListInfo[i].astLowPlmnList[k].stPlmnId.ulMnc = NAS_MML_INVALID_MNC;
            pstListInfo[i].astLowPlmnList[k].lRscp          = NAS_MML_UTRA_RSCP_UNVALID;
        }
    }
}


/*****************************************************************************
 函 数 名  : NAS_MMC_InitSearchedPlmnListInfo_PlmnList
 功能描述  : PLMN LIST搜网状态机运行过程中获取搜索到的网络列表信息
 输入参数  : 无
 输出参数  : 无
 返 回 值  : 需要搜索的网络列表信息
 调用函数  :
 被调函数  :

 修改历史      :
 1.日    期   : 2011年9月15日
   作    者   : w00176964
   修改内容   : 新生成函数

*****************************************************************************/

NAS_MMC_SEARCHED_PLMN_LIST_INFO_STRU *NAS_MMC_GetSearchedPlmnListInfo_PlmnList(VOS_VOID)
{
    /* 当前不是PLMN LIST状态机 异常打印*/
    if ( NAS_MMC_FSM_PLMN_LIST != NAS_MMC_GetCurrFsmId())
    {
       NAS_ERROR_LOG(WUEPS_PID_MMC, "NAS_MMC_GetSearchedPlmnListInfo_PlmnList,ERROR:FsmId Error");
    }

    return &(g_stNasMmcCtx.stCurFsm.unFsmCtx.stPlmnListCtx.astPlmnSearchInfo[0]);
}

#if (FEATURE_ON == FEATURE_CSG)

/*****************************************************************************
 函 数 名  : NAS_MMC_InitCsgSearchedPlmnListInfo_PlmnList
 功能描述  : PLMN LIST搜网状态机运行过程中初始化CSG搜索到的网络列表信息
 输入参数  : 无
 输出参数  : 无
 返 回 值  : 无
 调用函数  :
 被调函数  :

 修改历史      :
 1.日    期   : 2015年10月15日
   作    者   : s00193151
   修改内容   : 新生成函数
*****************************************************************************/
VOS_VOID NAS_MMC_InitCsgSearchedPlmnListInfo_PlmnList(VOS_VOID)
{
    VOS_UINT32                                              i;
    NAS_MMC_CSG_SEARCHED_PLMN_LIST_INFO_STRU               *pstCsgPlmnIdList  = VOS_NULL_PTR;

    /* 当前不是PLMN LIST状态机 异常打印*/
    if (NAS_MMC_FSM_PLMN_LIST != NAS_MMC_GetCurrFsmId())
    {
       NAS_ERROR_LOG(WUEPS_PID_MMC, "NAS_MMC_InitCsgSearchedPlmnListInfo_PlmnList,ERROR:FsmId Error");
       return;
    }

    /* 初始化CSG搜网结果列表 */
    pstCsgPlmnIdList = NAS_MMC_GetCsgSearchedPlmnListInfo_PlmnList();

    PS_MEM_SET(pstCsgPlmnIdList, 0, sizeof(NAS_MMC_CSG_SEARCHED_PLMN_LIST_INFO_STRU));

    for ( i= 0; i < RRC_NAS_MAX_PLMN_CSG_ID_NUM; i++ )
    {
        pstCsgPlmnIdList->astCsgListSearchedPlmnInfoList[i].stPlmnCsgIdWithRat.ulCsgId                      = NAS_MML_INVALID_CSG_ID_VALUE;
        pstCsgPlmnIdList->astCsgListSearchedPlmnInfoList[i].stPlmnCsgIdWithRat.stPlmnWithRat.ulRat          = RRC_NAS_RAT_TYPE_BUTT;
        pstCsgPlmnIdList->astCsgListSearchedPlmnInfoList[i].stPlmnCsgIdWithRat.stPlmnWithRat.stPlmnId.ulMcc = NAS_MML_INVALID_MCC;
        pstCsgPlmnIdList->astCsgListSearchedPlmnInfoList[i].stPlmnCsgIdWithRat.stPlmnWithRat.stPlmnId.ulMnc = NAS_MML_INVALID_MNC;
    }

    return;
}


/*****************************************************************************
 函 数 名  : NAS_MMC_GetCsgSearchedPlmnListInfo_PlmnList
 功能描述  : PLMN LIST搜网状态机运行过程中获取搜索到的CSG网络列表信息
 输入参数  : 无
 输出参数  : 无
 返 回 值  : 状态机中保存的CSG网络列表地址
 调用函数  :
 被调函数  :

 修改历史      :
 1.日    期   : 2015年10月16日
   作    者   : s00193151
   修改内容   : 新生成函数

*****************************************************************************/
NAS_MMC_CSG_SEARCHED_PLMN_LIST_INFO_STRU *NAS_MMC_GetCsgSearchedPlmnListInfo_PlmnList(VOS_VOID)
{
    /* 当前不是PLMN LIST状态机 异常打印*/
    if ( NAS_MMC_FSM_PLMN_LIST != NAS_MMC_GetCurrFsmId())
    {
       NAS_ERROR_LOG(WUEPS_PID_MMC, "NAS_MMC_GetCsgSearchedPlmnListInfo_PlmnList,ERROR:FsmId Error");
    }

    return &(g_stNasMmcCtx.stCurFsm.unFsmCtx.stPlmnListCtx.stCsgListSearchedPlmnInfoList);
}

/*****************************************************************************
 函 数 名  : NAS_MMC_IsBcchPlmnIdInSearchedPlmnList_PlmnList
 功能描述  : 检查当前PLMN是否已经在PLMN LIST搜网状态机的某接入技术的搜索结果中
 输入参数  : NAS_MML_PLMN_ID_STRU*                    待判断的PLMN
             NAS_MMC_SEARCHED_PLMN_LIST_INFO_STR*     已经创建好的某接入技术下的搜网结果列表
 输出参数  : 无
 返 回 值  : VOS_TRUE: 已经在此列表中; VOS_FALSE: 不在此列表中
 调用函数  : 调用此函数的函数必须保证入参不为空指针
 被调函数  :

 修改历史      :
 1.日    期   : 2015年10月16日
   作    者   : s00193151
   修改内容   : 新生成函数
*****************************************************************************/
VOS_UINT32 NAS_MMC_IsBcchPlmnIdInSearchedPlmnList_PlmnList(
    NAS_MML_PLMN_ID_STRU                          *pstPlmnId,
    NAS_MMC_SEARCHED_PLMN_LIST_INFO_STRU          *pstSearchedPlmnList
)
{
    /* 检查重复，只要高低质量列表中有一个已经存在此PLMN，则返回已经在表中 */
    if (VOS_TRUE == NAS_MML_IsBcchPlmnIdInDestSimPlmnList(pstPlmnId,
                    (VOS_UINT8)NAS_MML_MIN(pstSearchedPlmnList->ulHighPlmnNum, NAS_MMC_INTRA_MAX_HIGH_QUALITY_PLMN_NUM),
                    pstSearchedPlmnList->astHighPlmnList))
    {
        return VOS_TRUE;
    }

    if (VOS_TRUE == NAS_MMC_IsBcchPlmnInInDestLowPlmnInfoList(pstPlmnId,
                    (VOS_UINT8)NAS_MML_MIN(pstSearchedPlmnList->ulLowPlmnNum, NAS_MMC_INTRA_MAX_HIGH_QUALITY_PLMN_NUM),
                    pstSearchedPlmnList->astLowPlmnList))
    {
        return VOS_TRUE;
    }

    return VOS_FALSE;

}

/*****************************************************************************
 函 数 名  : NAS_MMC_UpdateSearchedPlmnListInfoFromCsgSearchResult_PlmnList
 功能描述  : PLMN LIST搜网状态机运行过程中将CSG列表搜结果更新到搜索到的网络列表信息
 输入参数  : pstRrcList  搜索到的网络列表信息
 输出参数  : 无
 返 回 值  : 无
 调用函数  : 调用此函数的函数必须保证入参不为空指针
 被调函数  :

 修改历史      :
 1.日    期   : 2015年10月16日
   作    者   : s00193151
   修改内容   : 新生成函数
*****************************************************************************/
VOS_VOID NAS_MMC_UpdateSearchedPlmnListInfoFromCsgSearchResult_PlmnList(
    NAS_MMC_CSG_SEARCHED_PLMN_LIST_INFO_STRU               *pstCsgPlmnList
)
{
    VOS_UINT32                                              i;
    VOS_UINT32                                              j;
    VOS_UINT32                                              ulIndex;
    VOS_UINT32                                              ucRatNum;
    NAS_MML_NET_RAT_TYPE_ENUM_UINT8                         enRat;
    NAS_MML_PLMN_ID_STRU                                    stPlmnId;
    NAS_MMC_SEARCHED_PLMN_LIST_INFO_STRU                   *pstListInfo = VOS_NULL_PTR;
    NAS_MML_PLMN_RAT_PRIO_STRU                             *pstRatPrio = VOS_NULL_PTR;

    /* 当前不是PLMN LIST状态机 异常打印 */
    if (NAS_MMC_FSM_PLMN_LIST != NAS_MMC_GetCurrFsmId())
    {
       NAS_ERROR_LOG(WUEPS_PID_MMC, "NAS_MMC_UpdateSearchedPlmnListInfoFromCsgSearchResult_PlmnList,ERROR:FsmId Error");
       return;
    }

    /* 实现思路很简单，在状态机上下文中保存的CSG ID搜索结果列表中，取出每个PLMN ID，保存到状态机上下文原
    来的那个高优先级搜网结果列表中，高质量的更新到高质量列表中，低质量的更新到低质量列表中，更新时需检查
    重复情况，如果表中已经有了此PLMN，则不再向里加入 */

    /* 局部变量初始化 */
    ulIndex         = 0;
    pstRatPrio      = NAS_MML_GetMsPrioRatList();
    ucRatNum        = pstRatPrio->ucRatNum;
    stPlmnId.ulMcc  = NAS_MML_INVALID_MCC;
    stPlmnId.ulMnc  = NAS_MML_INVALID_MNC;
    pstListInfo     = NAS_MMC_GetSearchedPlmnListInfo_PlmnList();
    pstRatPrio      = NAS_MML_GetMsPrioRatList();

    /* 保存高质量列表到上下文相应接入技术的列表 */
    for (i = 0; i < ucRatNum; i++)
    {
        for (j = 0; j < NAS_MML_MIN(pstCsgPlmnList->ulHighPlmnNum, RRC_NAS_MAX_PLMN_CSG_ID_NUM); j++)
        {
            /* 转换RRC格式的接入技术 */
            NAS_MMC_ConvertRrcRatToNasFormat(pstCsgPlmnList->astCsgListSearchedPlmnInfoList[j].stPlmnCsgIdWithRat.stPlmnWithRat.ulRat, &enRat);

            /* 如果判断的PLMN与当前循环的第i个接入技术相同，则进一步考虑是否加入当前接入技术的高优先级列表 */
            if (enRat == pstListInfo[i].enRatType)
            {
                stPlmnId.ulMcc  = pstCsgPlmnList->astCsgListSearchedPlmnInfoList[j].stPlmnCsgIdWithRat.stPlmnWithRat.stPlmnId.ulMcc;
                stPlmnId.ulMnc  = pstCsgPlmnList->astCsgListSearchedPlmnInfoList[j].stPlmnCsgIdWithRat.stPlmnWithRat.stPlmnId.ulMnc;

                /* 检查重复，如果表中没有此PLMN，则添加，否则不添加 */
                if (VOS_TRUE != NAS_MMC_IsBcchPlmnIdInSearchedPlmnList_PlmnList(&stPlmnId, &pstListInfo[i]))
                {
                    ulIndex = pstListInfo[i].ulHighPlmnNum;
                    pstListInfo[i].astHighPlmnList[ulIndex].ulMcc = stPlmnId.ulMcc;
                    pstListInfo[i].astHighPlmnList[ulIndex].ulMnc = stPlmnId.ulMnc;
                    pstListInfo[i].ulHighPlmnNum ++;

                    /* 保证数组不越界 */
                    if (pstListInfo[i].ulHighPlmnNum >= NAS_MMC_INTRA_MAX_HIGH_QUALITY_PLMN_NUM)
                    {
                        /* 数组越界，跳出外层循环 */
                        i = ucRatNum;
                        break;
                    }
                }
            }
        }
    }

    /* 保存低质量列表到上下文相应接入技术的列表 */
    for (i = 0; i < ucRatNum; i++)
    {
        /* 除去高质量的PLMN，剩下的都是低质量的PLMN，所以起始位置是从最后1个高质量PLMN的下1个开始 */
        for (j = pstCsgPlmnList->ulHighPlmnNum; j < NAS_MML_MIN(pstCsgPlmnList->ulTotalPlmnNum, RRC_NAS_MAX_PLMN_CSG_ID_NUM); j++)
        {
            /* 转换RRC格式的接入技术 */
            NAS_MMC_ConvertRrcRatToNasFormat(pstCsgPlmnList->astCsgListSearchedPlmnInfoList[j].stPlmnCsgIdWithRat.stPlmnWithRat.ulRat, &enRat);

            /* 如果判断的PLMN与当前循环的第i个接入技术相同，则进一步考虑是否加入当前接入技术的低优先级列表 */
            if (enRat == pstListInfo[i].enRatType)
            {
                stPlmnId.ulMcc  = pstCsgPlmnList->astCsgListSearchedPlmnInfoList[j].stPlmnCsgIdWithRat.stPlmnWithRat.stPlmnId.ulMcc;
                stPlmnId.ulMnc  = pstCsgPlmnList->astCsgListSearchedPlmnInfoList[j].stPlmnCsgIdWithRat.stPlmnWithRat.stPlmnId.ulMnc;

                /* 检查重复，如果表中没有此PLMN，则添加，否则不添加 */
                if (VOS_TRUE != NAS_MMC_IsBcchPlmnIdInSearchedPlmnList_PlmnList(&stPlmnId, &pstListInfo[i]))
                {
                    ulIndex = pstListInfo[i].ulLowPlmnNum;
                    pstListInfo[i].astLowPlmnList[ulIndex].stPlmnId.ulMcc = stPlmnId.ulMcc;
                    pstListInfo[i].astLowPlmnList[ulIndex].stPlmnId.ulMnc = stPlmnId.ulMnc;
                    pstListInfo[i].astLowPlmnList[ulIndex].lRscp = pstCsgPlmnList->astCsgListSearchedPlmnInfoList[j].lRscp;
                    pstListInfo[i].ulLowPlmnNum ++;

                    /* 保证数组不越界 */
                    if (pstListInfo[i].ulLowPlmnNum >= NAS_MMC_INTRA_MAX_LOW_QUALITY_PLMN_NUM)
                    {
                        /* 数组越界，跳出外层循环 */
                        i = ucRatNum;
                        break;
                    }
                }
            }
        }
    }

    /* 根据高低质量个数更新覆盖类型 */
    for (i = 0; i < ucRatNum; i++)
    {
        pstListInfo[i].enCoverType = NAS_MMC_COVERAGE_TYPE_NONE;

        if (pstListInfo[i].ulHighPlmnNum > 0)
        {
            pstListInfo[i].enCoverType = NAS_MMC_COVERAGE_TYPE_HIGH;
            break;
        }

        if (pstListInfo[i].ulLowPlmnNum > 0)
        {
            pstListInfo[i].enCoverType = NAS_MMC_COVERAGE_TYPE_LOW;
            break;
        }
    }

    return;

}


#endif

/*****************************************************************************
 函 数 名  : NAS_MMC_UpdateSearchedPlmnListInfo_PlmnList
 功能描述  : PLMN LIST搜网状态机运行过程中更新搜索到的网络列表信息
 输入参数  : pstRrcList  搜索到的网络列表信息
 输出参数  : 无
 返 回 值  : 无
 调用函数  :
 被调函数  :

 修改历史      :
 1.日    期   : 2011年9月15日
   作    者   : w00176964
   修改内容   : 新生成函数
 2.日    期   : 2012年11月05日
   作    者   : w00176964
   修改内容   : DTS2011082405001:更新网络覆盖类型
*****************************************************************************/

VOS_VOID NAS_MMC_UpdateSearchedPlmnListInfo_PlmnList(
    RRC_PLMN_ID_LIST_STRU              *pstRrcList
)
{
    VOS_UINT32                                              i;
    VOS_UINT32                                              j;
    VOS_UINT32                                              ulIndex;
    VOS_UINT32                                              ucRatNum;
    NAS_MMC_SEARCHED_PLMN_LIST_INFO_STRU                   *pstListInfo     = VOS_NULL_PTR;
    NAS_MML_NET_RAT_TYPE_ENUM_UINT8                         enRat;

    /* 当前不是PLMN LIST状态机 异常打印 */
    if ( NAS_MMC_FSM_PLMN_LIST != NAS_MMC_GetCurrFsmId())
    {
       NAS_ERROR_LOG(WUEPS_PID_MMC, "NAS_MMC_UpdateSearchedPlmnListInfo_PlmnList,ERROR:FsmId Error");
       return;
    }

    pstListInfo     = NAS_MMC_GetSearchedPlmnListInfo_PlmnList();
    ucRatNum        = NAS_MML_GetMsPrioRatList()->ucRatNum;

    /* 保存高质量列表到上下文相应接入技术的列表 */
    for ( i = 0; i < ucRatNum; i++ )
    {
        for ( j = 0; j < pstRrcList->ulHighPlmnNum; j++ )
        {
            /* 转换RRC格式的接入技术 */
            NAS_MMC_ConvertRrcRatToNasFormat(pstRrcList->aHighPlmnList[j].ulRat, &enRat);

            if ( enRat == pstListInfo[i].enRatType )
            {
                ulIndex = pstListInfo[i].ulHighPlmnNum;
                pstListInfo[i].astHighPlmnList[ulIndex].ulMcc
                       = pstRrcList->aHighPlmnList[j].stPlmnId.ulMcc;

                pstListInfo[i].astHighPlmnList[ulIndex].ulMnc
                       = pstRrcList->aHighPlmnList[j].stPlmnId.ulMnc;

                pstListInfo[i].ulHighPlmnNum ++;

                /* 保证数组不越界 */
                if (pstListInfo[i].ulHighPlmnNum >= NAS_MMC_INTRA_MAX_HIGH_QUALITY_PLMN_NUM)
                {
                    /* 数组越界，跳出外层循环 */
                    i = ucRatNum;
                    break;
                }
            }

        }
    }

    /* 保存低质量列表到上下文相应接入技术的列表 */
    for ( i = 0; i < ucRatNum; i++ )
    {
        for ( j = 0; j < pstRrcList->ulLowPlmnNum; j++ )
        {
            /* 转换RRC格式的接入技术 */
            NAS_MMC_ConvertRrcRatToNasFormat(pstRrcList->aLowPlmnList[j].PlmnId.ulRat, &enRat);

            if ( enRat == pstListInfo[i].enRatType )
            {
                ulIndex = pstListInfo[i].ulLowPlmnNum;
                pstListInfo[i].astLowPlmnList[ulIndex].stPlmnId.ulMcc
                       = pstRrcList->aLowPlmnList[j].PlmnId.stPlmnId.ulMcc;

                pstListInfo[i].astLowPlmnList[ulIndex].stPlmnId.ulMnc
                       = pstRrcList->aLowPlmnList[j].PlmnId.stPlmnId.ulMnc;

                pstListInfo[i].astLowPlmnList[ulIndex].lRscp
                       = pstRrcList->aLowPlmnList[j].lRscp;

                pstListInfo[i].ulLowPlmnNum ++;

                /* 保证数组不越界 */
                if (pstListInfo[i].ulLowPlmnNum >= NAS_MMC_INTRA_MAX_LOW_QUALITY_PLMN_NUM)
                {
                    /* 数组越界，跳出外层循环 */
                    i = ucRatNum;
                    break;
                }
            }
        }
    }

    /* 根据高低质量个数更新覆盖类型 */
    for ( i = 0; i < ucRatNum; i++ )
    {
        if (pstListInfo[i].ulHighPlmnNum > 0)
        {
            pstListInfo[i].enCoverType = NAS_MMC_COVERAGE_TYPE_HIGH;
        }
        else if (pstListInfo[i].ulLowPlmnNum > 0)
        {
            pstListInfo[i].enCoverType = NAS_MMC_COVERAGE_TYPE_LOW;
        }
        else
        {
            pstListInfo[i].enCoverType = NAS_MMC_COVERAGE_TYPE_NONE;
        }
    }
}

#if (FEATURE_ON == FEATURE_LTE)
/*****************************************************************************
 函 数 名  : NAS_MMC_GetPreLteDisableFlg_PlmnList
 功能描述  : PLMN LIST搜网状态机运行过程中获取L disable的状态
 输入参数  : 无
 输出参数  : 无
 返 回 值  : Lte capability状态
 调用函数  :
 被调函数  :

 修改历史      :
 1.日    期   : 2012年5月8日
   作    者   : t00212959
   修改内容   : 新生成函数

*****************************************************************************/

VOS_UINT8 NAS_MMC_GetPreLteDisableFlg_PlmnList(VOS_VOID)
{
    /* 当前不是PLMN LIST状态机 异常打印 */
    if ( NAS_MMC_FSM_PLMN_LIST != NAS_MMC_GetCurrFsmId())
    {
       NAS_ERROR_LOG(WUEPS_PID_MMC, "NAS_MMC_GetPreLteDisableFlg_PlmnList,ERROR:FsmId Error");
    }

    return g_stNasMmcCtx.stCurFsm.unFsmCtx.stPlmnListCtx.ucPreLteDisableFlg;
}

/*****************************************************************************
 函 数 名  : NAS_MMC_SetPreLteDisableFlg_PlmnList
 功能描述  : PLMN LIST搜网状态机运行过程中设置L disable的状态
 输入参数  : enLteCapStatus - Lte capability状态
 输出参数  : 无
 返 回 值  : 无
 调用函数  :
 被调函数  :

 修改历史      :
 1.日    期   : 2012年5月8日
   作    者   : t00212959
   修改内容   : 新生成函数

*****************************************************************************/

VOS_VOID NAS_MMC_SetPreLteDisableFlg_PlmnList(
    VOS_UINT8                           ucPreLteDisableFlg
)
{
    /* 当前不是PLMN LIST状态机 异常打印 */
    if ( NAS_MMC_FSM_PLMN_LIST != NAS_MMC_GetCurrFsmId())
    {
       NAS_ERROR_LOG(WUEPS_PID_MMC, "NAS_MMC_SetPreLteDisableFlg_PlmnList,ERROR:FsmId Error");

       return;
    }

    g_stNasMmcCtx.stCurFsm.unFsmCtx.stPlmnListCtx.ucPreLteDisableFlg = ucPreLteDisableFlg;
    return;

}
#endif

/*****************************************************************************
 函 数 名  : NAS_MMC_GetAnyCellSrchFlg_PlmnList
 功能描述  : PLMN LIST搜网状态机运行过程中获取需要进行anycell搜网标记
 输入参数  : 无
 输出参数  : 无
 返 回 值  : anycell搜网标记
 调用函数  :
 被调函数  :

 修改历史      :
 1.日    期   : 2012年5月31日
   作    者   : w00176964
   修改内容   : 新生成函数
*****************************************************************************/

VOS_UINT8 NAS_MMC_GetAnyCellSrchFlg_PlmnList(VOS_VOID)
{
    /* 当前不是PLMN LIST状态机 异常打印 */
    if ( NAS_MMC_FSM_PLMN_LIST != NAS_MMC_GetCurrFsmId())
    {
       NAS_ERROR_LOG(WUEPS_PID_MMC, "NAS_MMC_GetAnyCellSrchFlg_PlmnList,ERROR:FsmId Error");
    }

    return g_stNasMmcCtx.stCurFsm.unFsmCtx.stPlmnListCtx.ucAnyCellSrchFlg;
}

/*****************************************************************************
 函 数 名  : NAS_MMC_SetAnyCellSrchFlg_PlmnList
 功能描述  : PLMN LIST搜网状态机运行过程中设置anycell搜网标记
 输入参数  : anycell搜网标记
 输出参数  : 无
 返 回 值  : 无
 调用函数  :
 被调函数  :

 修改历史      :
 1.日    期   : 2012年5月31日
   作    者   : w00176964
   修改内容   : 新生成函数

*****************************************************************************/

VOS_VOID NAS_MMC_SetAnyCellSrchFlg_PlmnList(
    VOS_UINT8                           ucAnyCellSrchFlg
)
{
    /* 当前不是PLMN LIST状态机 异常打印 */
    if ( NAS_MMC_FSM_PLMN_LIST != NAS_MMC_GetCurrFsmId())
    {
       NAS_ERROR_LOG(WUEPS_PID_MMC, "NAS_MMC_SetAnyCellSrchFlg_PlmnList,ERROR:FsmId Error");

       return;
    }

    g_stNasMmcCtx.stCurFsm.unFsmCtx.stPlmnListCtx.ucAnyCellSrchFlg = ucAnyCellSrchFlg;
    return;
}

/*****************************************************************************
 函 数 名  : NAS_MMC_InitHighPrioPlmnSearchCtx
 功能描述  : 初始化高优先级搜网控制上下文
 输入参数  : 高优先级搜网控制上下文指针
 输出参数  : 无
 返 回 值  : 无
 调用函数  :
 被调函数  :

 修改历史      :
 1.日    期   : 2011年10月2日
   作    者   : z00161729
   修改内容   : 新生成函数
 2.日    期   : 2011年10月2日
   作    者   : w00167002
   修改内容   : 增加对RESERVE字段的初始化
 3.日    期   : 2014年1月22日
   作    者   : w00167002
   修改内容   : SVLTE共天线项目:对新增变量进行初始化；
 4.日    期   : 2014年10月27日
   作    者   : b00269685
   修改内容   : 增加TD下超时次数
*****************************************************************************/
VOS_VOID NAS_MMC_InitHighPrioPlmnSearchCtx(NAS_MMC_HIGH_PRIO_PLMN_SEARCH_CTRL_CTX_STRU *pstHighPrioPlmnSearchCtrl)
{
    VOS_UINT32                          i;
    VOS_UINT32                          j;

    pstHighPrioPlmnSearchCtrl->ucFirstStartHPlmnTimerFlg                       = VOS_TRUE;
    pstHighPrioPlmnSearchCtrl->enPlmnSelectionListType                         = NAS_MMC_STORE_HIGH_PRIO_PLMN_SELECTION_LIST;
    pstHighPrioPlmnSearchCtrl->ucTdHighRatSearchCount                          = 0;
    pstHighPrioPlmnSearchCtrl->aucReserve[0]                                   = 0;

    pstHighPrioPlmnSearchCtrl->stHighPrioPlmnSearchListInfo.usSearchPlmnNum = 0;
    pstHighPrioPlmnSearchCtrl->stHighPrioPlmnSearchListInfo.aucReserve[0]   = 0;
    pstHighPrioPlmnSearchCtrl->stHighPrioPlmnSearchListInfo.aucReserve[1]   = 0;

    for (i = 0; i < NAS_MMC_MAX_PLMN_NUM_IN_SELECTION_LIST; i++)
    {
        pstHighPrioPlmnSearchCtrl->stHighPrioPlmnSearchListInfo.astPlmnSelectionList[i].stPlmnId.ulMcc = NAS_MML_INVALID_MCC;
        pstHighPrioPlmnSearchCtrl->stHighPrioPlmnSearchListInfo.astPlmnSelectionList[i].stPlmnId.ulMnc = NAS_MML_INVALID_MNC;
        pstHighPrioPlmnSearchCtrl->stHighPrioPlmnSearchListInfo.astPlmnSelectionList[i].enPlmnType     = NAS_MMC_PLMN_TYPE_BUTT;
        pstHighPrioPlmnSearchCtrl->stHighPrioPlmnSearchListInfo.astPlmnSelectionList[i].ucRatNum       = 0;
        pstHighPrioPlmnSearchCtrl->stHighPrioPlmnSearchListInfo.astPlmnSelectionList[i].aucReserve[0]  = 0;
        pstHighPrioPlmnSearchCtrl->stHighPrioPlmnSearchListInfo.astPlmnSelectionList[i].aucReserve[1]  = 0;

        for (j = 0; j < NAS_MML_MAX_RAT_NUM; j++)
        {
            pstHighPrioPlmnSearchCtrl->stHighPrioPlmnSearchListInfo.astPlmnSelectionList[i].astPlmnRatInfo[j].enRatType   = NAS_MML_NET_RAT_TYPE_BUTT;
            pstHighPrioPlmnSearchCtrl->stHighPrioPlmnSearchListInfo.astPlmnSelectionList[i].astPlmnRatInfo[j].enNetStatus = NAS_MMC_NET_STATUS_BUTT;
            pstHighPrioPlmnSearchCtrl->stHighPrioPlmnSearchListInfo.astPlmnSelectionList[i].astPlmnRatInfo[j].enQuality   = NAS_MMC_NET_QUALITY_BUTT;

            pstHighPrioPlmnSearchCtrl->stHighPrioPlmnSearchListInfo.astPlmnSelectionList[i].astPlmnRatInfo[j].ucReserve   = 0;

            pstHighPrioPlmnSearchCtrl->stHighPrioPlmnSearchListInfo.astPlmnSelectionList[i].astPlmnRatInfo[j].lRscp       = NAS_MML_UTRA_RSCP_UNVALID;
        }
    }
}

/*****************************************************************************
 函 数 名  : NAS_MMC_GetHighPrioPlmnList
 功能描述  : 获取高优先级网络列表指针
 输入参数  : 无
 输出参数  : 无
 返 回 值  : 高优先级网络列表指针
 调用函数  :
 被调函数  :

 修改历史      :
 1.日    期   : 2011年9月20日
   作    者   : w00166186
   修改内容   : 新生成函数

*****************************************************************************/
NAS_MMC_PLMN_SELECTION_LIST_INFO_STRU *NAS_MMC_GetHighPrioPlmnList(VOS_VOID)
{

    return &(g_stNasMmcCtx.stHighPrioPlmnSearchCtrl.stHighPrioPlmnSearchListInfo);
}

/*****************************************************************************
 函 数 名  : NAS_MMC_GetPlmnSelectionListType
 功能描述  : 获取当前MMC保存的全局变量中的选网列表类型
 输入参数  : 无
 输出参数  : 无
 返 回 值  : NAS_MMC_PLMN_SELECTION_LIST_TYPE_ENUM
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2014年1月21日
    作    者   : w00167002
    修改内容   : 新生成函数
*****************************************************************************/
NAS_MMC_PLMN_SELECTION_LIST_TYPE_ENUM_UINT8 NAS_MMC_GetPlmnSelectionListType(VOS_VOID)
{
    return g_stNasMmcCtx.stHighPrioPlmnSearchCtrl.enPlmnSelectionListType;
}

/*****************************************************************************
 函 数 名  : NAS_MMC_SetPlmnSelectionListType
 功能描述  : 设置当前在MMC的全局变量中保存的选网列表类型
 输入参数  : enPlmnSelectionListType:设置当前在MMC的全局变量中保存的选网列表类型
 输出参数  : 无
 返 回 值  : 无
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2014年1月21日
    作    者   : w00167002
    修改内容   : 新生成函数
*****************************************************************************/
VOS_VOID NAS_MMC_SetPlmnSelectionListType(
    NAS_MMC_PLMN_SELECTION_LIST_TYPE_ENUM_UINT8             enListType
)
{
    g_stNasMmcCtx.stHighPrioPlmnSearchCtrl.enPlmnSelectionListType = enListType;

    return;
}

/*****************************************************************************
 函 数 名  : NAS_MMC_GetTdHighRatSearchCount
 功能描述  : 获取当前MMC保存的全局变量中的高优先级搜网定时器启动次数
 输入参数  : 无
 输出参数  : 无
 返 回 值  : ucTdHighRatSearchCount
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2014年10月25日
    作    者   : b00269685
    修改内容   : 新生成函数
*****************************************************************************/
VOS_UINT8 NAS_MMC_GetTdHighRatSearchCount(VOS_VOID)
{
    return g_stNasMmcCtx.stHighPrioPlmnSearchCtrl.ucTdHighRatSearchCount;
}

/*****************************************************************************
 函 数 名  : NAS_MMC_AddTdHighRatSearchCount
 功能描述  : 增加当前MMC保存的全局变量中的高优先级搜网定时器启动次数
 输入参数  : 无
 输出参数  : 无
 返 回 值  : ucTdHighRatSearchCount
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2014年10月25日
    作    者   : b00269685
    修改内容   : 新生成函数
*****************************************************************************/
VOS_VOID NAS_MMC_AddTdHighRatSearchCount(VOS_VOID)
{
    g_stNasMmcCtx.stHighPrioPlmnSearchCtrl.ucTdHighRatSearchCount++;

    return;
}

/*****************************************************************************
 函 数 名  : NAS_MMC_InitTdHighRatSearchCount
 功能描述  : 初始化当前MMC保存的全局变量中的高优先级搜网定时器启动次数
 输入参数  : enPlmnSelectionListType:设置当前在MMC的全局变量中保存的选网列表类型
 输出参数  : 无
 返 回 值  : 无
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2014年10月25日
    作    者   : b00269685
    修改内容   : 新生成函数
*****************************************************************************/
VOS_VOID NAS_MMC_InitTdHighRatSearchCount(VOS_VOID)
{
    g_stNasMmcCtx.stHighPrioPlmnSearchCtrl.ucTdHighRatSearchCount = 0;

    return;
}

/*****************************************************************************
 函 数 名  : NAS_MMC_GetNetScanReq
 功能描述  : 获取保存的NetScan REQ
 输入参数  : 无
 输出参数  : 无
 返 回 值  : NetScan请求
 调用函数  :
 被调函数  :

 修改历史      :
 1.日    期   : 2013年10月16日
   作    者   : w00242748
   修改内容   : 新生成函数

*****************************************************************************/
MSCC_MMC_NET_SCAN_REQ_STRU *NAS_MMC_GetNetScanReq(VOS_VOID)
{
    return &(g_stNasMmcCtx.stNetScanReqCtx.stNetScanReq);
}

/*****************************************************************************
 函 数 名  : NAS_MMC_SetNetScanReq
 功能描述  : 获取保存的NetScan REQ
 输入参数  : 无
 输出参数  : 无
 返 回 值  : NetScan请求
 调用函数  :
 被调函数  :

 修改历史      :
 1.日    期   : 2013年10月16日
   作    者   : w00242748
   修改内容   : 新生成函数

*****************************************************************************/
VOS_VOID NAS_MMC_SetNetScanReq(
    MSCC_MMC_NET_SCAN_REQ_STRU          *pstNetScanReq
)
{
    PS_MEM_CPY(&(g_stNasMmcCtx.stNetScanReqCtx.stNetScanReq),
                pstNetScanReq,
                sizeof(MSCC_MMC_NET_SCAN_REQ_STRU));

    return;
}




/*****************************************************************************
 函 数 名  : NAS_MMC_GetSpecRatPrio
 功能描述  : 获取特定接入技术在接入技术列表中的优先级
 输入参数  : NAS_MMC_NET_RAT_TYPE_ENUM_U8        enRat
 输出参数  : 无
 返 回 值  : RRC_NAS_RAT_PRIO_ENUM_UINT32
 调用函数  :
 被调函数  :

 修改历史      :
 1.日    期   : 2011年5月10日
   作    者   : l00130025
   修改内容   : 新生成函数
 2.日    期   : 2011年7月11日
   作    者   : w00167002
   修改内容   : V7_phaseII调整

*****************************************************************************/
RRMM_RAT_PRIO_ENUM_UINT8 NAS_MMC_GetSpecRatPrio(
    NAS_MML_NET_RAT_TYPE_ENUM_UINT8     enRat,
    NAS_MML_PLMN_RAT_PRIO_STRU         *pstRatList
)
{
    VOS_UINT32                          i;

    /* 查找对应接入技术是否在支持列表中 */
    for ( i = 0; i < pstRatList->ucRatNum; i++ )
    {
        if ( (pstRatList->aucRatPrio[i] == enRat)
          && (enRat < NAS_MML_NET_RAT_TYPE_BUTT) )
        {
            break;
        }
    }

    /* 查找成功,返回对应的接入技术优先级 */
    if ( i < pstRatList->ucRatNum )
    {
        /*接入技术的优先级，从高到低排列 */
        return (VOS_UINT8)(RRMM_RAT_PRIO_HIGH - i);
    }

    /* 不在支持列表中时，返回优先级为NULL*/
    else
    {
        return RRMM_RAT_PRIO_NULL;
    }

}




/*****************************************************************************
 函 数 名  : NAS_MMC_GetEHPlmn
 功能描述  : 提供给接入层获取EHPLMN的API接口函数
 输入参数  : 无
 输出参数  : NAS_MML_PLMN_ID_STRU *pstEHPlmn:EHPLMN列表，需要能存储32个PLMNID
             VOS_UINT32 *pulEHPlmnNum:EHPLMN个数
 返 回 值  : VOS_OK :获取成功，返回EHPLMN或者home plmn(不支持EHPLMN或者EHPLMN列表为空)
             VOS_ERR:获取失败，参数检查失败或者无卡或者卡被锁定
 调用函数  :
 被调函数  :

 修改历史      :
 1.日    期   : 2011年5月11日
   作    者   : s46746
   修改内容   : 新生成函数

 2.日    期   : 2011年7月13日
   作    者   : W00167002
   修改内容   : 同步到V7R1_PHASEII

*****************************************************************************/
VOS_UINT32 NAS_MMC_GetEHPlmn(
    RRC_PLMN_ID_STRU                   *pstEHPlmn,
    VOS_UINT8                          *pucEHPlmnNum
)
{
    NAS_MML_SIM_EHPLMN_INFO_STRU       *pstSimEHplmn = VOS_NULL_PTR;
    NAS_MML_SIM_STATUS_STRU            *pstSimStatus = VOS_NULL_PTR;
    VOS_UINT32                          i;
    VOS_UINT8                           ucSimFlg;

    /* 获取当前的SIM卡状态信息 */
    pstSimStatus = NAS_MML_GetSimStatus();
    ucSimFlg    = pstSimStatus->ucSimPresentStatus;

    if ((VOS_NULL_PTR == pstEHPlmn) || (VOS_NULL_PTR == pucEHPlmnNum))
    {
        NAS_WARNING_LOG(WUEPS_PID_MMC, "NAS_MMC_GetEHPlmn, input para is null.");
        return VOS_ERR;
    }

    if (VOS_FALSE == ucSimFlg)
    {

        NAS_WARNING_LOG(WUEPS_PID_MMC, "NAS_MMC_GetEHPlmn, sim is absent or locked");
        return VOS_ERR;
    }

    pstSimEHplmn = NAS_MML_GetSimEhplmnList();

    /* 获得EHPLMN的个数 */
    *pucEHPlmnNum  = pstSimEHplmn->ucEhPlmnNum;

    /* 获取EHPLMN */
    for (i = 0; i < (*pucEHPlmnNum); i++)
    {
        pstEHPlmn[i].ulMcc = pstSimEHplmn->astEhPlmnInfo[i].stPlmnId.ulMcc;
        pstEHPlmn[i].ulMnc = pstSimEHplmn->astEhPlmnInfo[i].stPlmnId.ulMnc;
    }

    return VOS_OK;
}

/*****************************************************************************
 函 数 名  : NAS_MMC_UpdateGURegRlstRPlmnIdInNV
 功能描述  : 注册成功后更新当前的RPLMN和RAT到RPLMN的全局变量和NV项中
 输入参数  : VOS_VOID
 输出参数  : 无
 返 回 值  : VOS_VOID
 调用函数  :
 被调函数  :

 修改历史      :
 1.日    期   : 2011年7月28日
   作    者   : L00171473
   修改内容   : 新生成函数
 2.日    期   : 2011年8月6日
   作    者   : l00130025
   修改内容   : 新生成函数

*****************************************************************************/
VOS_VOID NAS_MMC_UpdateGURegRlstRPlmnIdInNV(VOS_VOID)
{
    NAS_MML_RPLMN_CFG_INFO_STRU        *pstRplmnCfgInfo = VOS_NULL_PTR;
    NAS_MML_PLMN_ID_STRU                stPlmnId;                               /* PlMN标识 */
    NAS_MML_NET_RAT_TYPE_ENUM_UINT8     enCurrRat;
    VOS_UINT32                          ulGRplmnChangeFlag;
    VOS_UINT32                          ulWRplmnChangeFlag;
    VOS_UINT32                          ulRatChangeFlag;

    ulGRplmnChangeFlag = VOS_FALSE;
    ulWRplmnChangeFlag = VOS_FALSE;
    ulRatChangeFlag    = VOS_FALSE;

    /* 用于获取RPLMN的定制需求信息 */
    pstRplmnCfgInfo = NAS_MML_GetRplmnCfg();

    /* 获取当前的接入技术 */
    enCurrRat = NAS_MML_GetCurrNetRatType();

    /* 用于最后一次注册成功的PLMN,没有Rplmn时，返回失败 */
    if (VOS_FALSE == NAS_MML_GetRPlmn(enCurrRat, &stPlmnId))
    {
        return;
    }

    /* 更新全局变量中的LastRPLMN的接入技术 */
    if (enCurrRat != NAS_MML_GetLastRplmnRat())
    {
        ulRatChangeFlag = VOS_TRUE;
        NAS_MML_SetLastRplmnRat(enCurrRat);
    }


    /* 更新全局变量中的RPLMN */
    if (VOS_FALSE == pstRplmnCfgInfo->ucMultiRATRplmnFlg)
    {
        ulGRplmnChangeFlag = NAS_MML_CompareBcchPlmnwithSimPlmn(&stPlmnId,
                                                            &pstRplmnCfgInfo->stGRplmnInNV);
        ulWRplmnChangeFlag = NAS_MML_CompareBcchPlmnwithSimPlmn(&stPlmnId,
                                                            &pstRplmnCfgInfo->stWRplmnInNV);
        /* 不支持双RPLMN，则W和G的RPLMN都更新 */
        pstRplmnCfgInfo->stGRplmnInNV = stPlmnId;
        pstRplmnCfgInfo->stWRplmnInNV = stPlmnId;

    }
    else
    {
        /* 支持双RPLMN, 则只更新对应接入技术的RPLMN */
        if (NAS_MML_NET_RAT_TYPE_GSM == enCurrRat)
        {
            ulGRplmnChangeFlag = NAS_MML_CompareBcchPlmnwithSimPlmn(&stPlmnId,
                                                            &pstRplmnCfgInfo->stGRplmnInNV);
            pstRplmnCfgInfo->stGRplmnInNV = stPlmnId;

        }
        else if (NAS_MML_NET_RAT_TYPE_WCDMA == enCurrRat)
        {
            ulWRplmnChangeFlag = NAS_MML_CompareBcchPlmnwithSimPlmn(&stPlmnId,
                                                                 &pstRplmnCfgInfo->stWRplmnInNV);
            pstRplmnCfgInfo->stWRplmnInNV = stPlmnId;
        }
        else
        {
            ;
        }
    }

    if ((VOS_TRUE ==ulRatChangeFlag)
     || (VOS_TRUE == ulWRplmnChangeFlag)
     || (VOS_TRUE == ulGRplmnChangeFlag))
    {
        NAS_MMC_WriteRplmnWithRatNvim();
    }

    return;

}
/*****************************************************************************
 函 数 名  : NAS_MMC_SaveUserReselPlmnInfo
 功能描述  : 在用户指定搜网前，保存当前的网络信息。
             在正常服务状态下，保存当前的网络ID和对应的RAT;
             在限制服务下，保存HOME PLMN，根据用户设置的优先级保存RAT。
             在用户指定搜网失败，提示回到原来的网络时使用此信息进行搜网
 输入参数  : VOS_VOID
 输出参数  : 无
 返 回 值  : VOS_VOID
 调用函数  :
 被调函数  :

 修改历史      :
 1.日    期   : 2011年2月21日
   作    者   : l65478
   修改内容   : 新生成函数
 2.日    期   : 2011年7月20日
   作    者   : L00171473
   修改内容   : V7R1 phase II 修改

*****************************************************************************/
VOS_VOID NAS_MMC_SaveUserReselPlmnInfo(VOS_VOID)
{
    NAS_MML_PLMN_RAT_PRIO_STRU         *pstPlmnRatList    = VOS_NULL_PTR;
    NAS_MML_NET_RAT_TYPE_ENUM_UINT8     enRatType;

    if (VOS_TRUE == NAS_MMC_IsNormalServiceStatus())
    {
        /* 在正常服务状态下，保存当前驻留的网络ID和对应的RAT */
        NAS_MMC_SetUserReselPlmnId( NAS_MML_GetCurrCampPlmnId(),
                                    NAS_MML_GetCurrNetRatType() );
    }
    else
    {
        /* 原来是自动模式才需要保存。
           原来是手动搜网模式，在限制服务状态，说明旧的PLMN信息已经保存,此时不需
           要再保存，避免把原来的PLMN ID信息清除 */
        if (NAS_MMC_PLMN_SELECTION_MODE_AUTO == NAS_MMC_GetPlmnSelectionMode())
        {
            enRatType    = NAS_MML_GetCurrNetRatType();

            /* 获取MML中保存的当前MS支持的接入模式和接入优先级 */
            pstPlmnRatList = NAS_MML_GetMsPrioRatList();

            /* 获取用户设置的优先级RAT */
            if (pstPlmnRatList->ucRatNum != 0)
            {
                enRatType = pstPlmnRatList->aucRatPrio[0];
            }

            /* 在限制服务下，保存HOME PLMN，和用户设置的优先级RAT */
            NAS_MMC_SetUserReselPlmnId(&(NAS_MML_GetSimEhplmnList()->astEhPlmnInfo[0].stPlmnId),
                                       enRatType);
        }
    }
}

/*****************************************************************************
 函 数 名  : NAS_MMC_SetPlmnRegRejInfo
 功能描述  : 按PlmnID,域,Cause值填充RegInfo
 输入参数  : 无
 输出参数  : 无
 返 回 值  :
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2011年2月27日
    作    者   : l00130025
    修改内容   : 新生成函数
  2.日    期   : 2011年7月28日
    作    者   : L00171473
    修改内容   : V7R1 PhaseII 修改

  3.日    期   : 2011年8月6日
    作    者   : zhoujun 40661
    修改内容   : REG INFO结构发生变化，调整该函数
  4.日    期   : 2011年11月2日
    作    者   : z00161729
    修改内容   : 联合注册修改L支持cs需要更新reg info
  5.日    期   : 2011年12月5日
    作    者   : z00161729
    修改内容   : V7R1 phaseIV修改合并原NAS_MMC_HPLMN_REG_REJ_STRU和NAS_MMC_PLMN_REG_INFO_STRU
*****************************************************************************/
VOS_VOID  NAS_MMC_SetPlmnRegRejInfo(
    NAS_MML_PLMN_ID_STRU               *pstPlmnId,
    NAS_MMC_REG_DOMAIN_ENUM_UINT8       enDomain,
    NAS_MML_REG_FAIL_CAUSE_ENUM_UINT16  enCause,
    NAS_MMC_PLMN_REG_INFO_STRU         *pstPlmnRegInfo
)
{
    NAS_MML_NET_RAT_TYPE_ENUM_UINT8     enCurrRat;
    NAS_MML_LAI_STRU                   *pstCurrLai;
    VOS_UINT32                          i;
    VOS_UINT8                           ucCurrCampRac;

    if (VOS_NULL_PTR == pstPlmnRegInfo)
    {
        NAS_WARNING_LOG(WUEPS_PID_MMC, "NAS_MMC_SetPlmnRegRejInfo:WARNING:pstPlmnRegInfo IS NULL POINTER");
        return;
    }

    /* 获取当前的接入技术 */
    enCurrRat     = NAS_MML_GetCurrNetRatType();
    pstCurrLai    = NAS_MML_GetCurrCampLai();
    ucCurrCampRac = NAS_MML_GetCurrCampRac();

    pstPlmnRegInfo->stPlmnId = *pstPlmnId;

    for (i = 0 ; i < NAS_MML_MAX_LAC_LEN ; i++ )
    {
        pstPlmnRegInfo->aucLac[i] = pstCurrLai->aucLac[i];
    }
    pstPlmnRegInfo->ucRac = ucCurrCampRac;

    NAS_NORMAL_LOG4(WUEPS_PID_MMC,
                    "NAS_MMC_SetPlmnRegRejInfo: PLMN MCC, MNC, Domain and Reg Fail Cause",
                    pstPlmnRegInfo->stPlmnId.ulMcc,
                    pstPlmnRegInfo->stPlmnId.ulMnc,
                    enDomain,
                    enCause);

    NAS_NORMAL_LOG4(WUEPS_PID_MMC,
                    "NAS_MMC_SetPlmnRegRejInfo: RAT, LAI and RAC ",
                    enCurrRat,
                    pstPlmnRegInfo->aucLac[0],
                    pstPlmnRegInfo->aucLac[1],
                    pstPlmnRegInfo->ucRac);

    if (NAS_MML_NET_RAT_TYPE_GSM == enCurrRat)
    {
        if (NAS_MMC_REG_DOMAIN_CS == enDomain)
        {
            pstPlmnRegInfo->enGCsRegStatus  = enCause;
            return;
        }

        if (NAS_MMC_REG_DOMAIN_PS == enDomain)
        {
            pstPlmnRegInfo->enGPsRegStatus  = enCause;
            return;
        }

        if (NAS_MMC_REG_DOMAIN_PS_CS == enDomain)
        {
            pstPlmnRegInfo->enGCsRegStatus  = enCause;
            pstPlmnRegInfo->enGPsRegStatus  = enCause;
            return;
        }

    }
    else if (NAS_MML_NET_RAT_TYPE_WCDMA == enCurrRat)
    {
        if (NAS_MMC_REG_DOMAIN_CS == enDomain)
        {
            pstPlmnRegInfo->enWCsRegStatus  = enCause;
            return;
        }

        if (NAS_MMC_REG_DOMAIN_PS == enDomain)
        {
            pstPlmnRegInfo->enWPsRegStatus  = enCause;
            return;
        }

        if (NAS_MMC_REG_DOMAIN_PS_CS == enDomain)
        {
            pstPlmnRegInfo->enGCsRegStatus  = enCause;
            pstPlmnRegInfo->enGPsRegStatus  = enCause;
            return;
        }

    }
#if   (FEATURE_ON == FEATURE_LTE)
    else if (NAS_MML_NET_RAT_TYPE_LTE == enCurrRat)
    {
        if (NAS_MMC_REG_DOMAIN_EPS == enDomain)
        {
            pstPlmnRegInfo->enLPsRegStatus  = enCause;
            return;
        }
        if (NAS_MMC_REG_DOMAIN_CS == enDomain)
        {
            pstPlmnRegInfo->enLCsRegStatus = enCause;
            return;
        }
    }
#endif
    else
    {
        NAS_NORMAL_LOG(WUEPS_PID_MMC, "NAS_MMC_FillPlmnRegInfo: NORMAL: enCurrRat is wrong!");
    }


}


/*****************************************************************************
 函 数 名  : NAS_MMC_UpdatePlmnRegInfoList
 功能描述  : 更新g_MmcPlmnSrchCtrl.astPlmnRegInfoList中对应PlmnId的注册结果
             当前PlmnID在列表中时，更新，
             不在列表中时，添加，
             列表已满时，覆盖最早的信息,其它信息迁移
 输入参数  : pstPlmn,需要更新的网络
             enDomain,需要更新的服务域
             enCause,更新的原因值
 输出参数  : 无
 返 回 值  :
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2011年2月27日
    作    者   : l00130025
    修改内容   : 新生成函数
  2.日    期   : 2011年7月28日
    作    者   : L00171473
    修改内容   : V7R1 PhaseII 修改
  3.日    期   : 2011年12月12日
    作    者   : z00161729
    修改内容   : V7R1 phaseIV修改合并原NAS_MMC_HPLMN_REG_REJ_STRU和NAS_MMC_PLMN_REG_INFO_STRU
  4.日    期   : 2012年1月9日
    作    者   : w00167002
    修改内容   : DTS2011122006209:当保存网络注册原因值时，若该PLMN不在注册表
                 里面且Cause值为NAS_MML_REG_FAIL_CAUSE_NULL,则不保存。周君客来
                 讨论若一直往表里增加网络的注册原因值时，那么最多能保存64个，
                 在一直不关机的情况下，在环游世界的时候，存在问题，应增加此处修改。
  5.日    期   : 2014年5月28日
    作    者   : z00234330
    修改内容   : covertity修改
  6.日    期   : 2014年6月17日
    作    者   : z00234330
    修改内容   : PCINT清理
*****************************************************************************/
VOS_VOID NAS_MMC_UpdatePlmnRegInfoList(
    NAS_MML_PLMN_ID_STRU               *pstPlmn,
    NAS_MMC_REG_DOMAIN_ENUM_UINT8       enDomain,
    NAS_MML_REG_FAIL_CAUSE_ENUM_UINT16  enCause
)
{
    NAS_MMC_PLMN_REG_REJ_CTX_STRU      *pstPlmnRegRejInfo = VOS_NULL_PTR;
    NAS_MMC_PLMN_REG_INFO_STRU         *pstPlmnRegList    = VOS_NULL_PTR;
    VOS_UINT32                          ulIndex;

    pstPlmnRegRejInfo = NAS_MMC_GetPlmnRegRejInfo();

    /* 获取注册原因列表的指针 */
    pstPlmnRegList = pstPlmnRegRejInfo->astPlmnRegInfoList;

    /* 判断当前网络是否已在注册列表中   */
    ulIndex = NAS_MMC_GetPlmnIndexInRegInfoList(pstPlmn,
                            pstPlmnRegRejInfo->ucPlmnRegInfoNum, pstPlmnRegList);


    /* 当前网络在注册被拒列表中 */
    /* modified by z00234330 for coverity修改 2014-05-28 begin */
    if ( ulIndex < NAS_MML_MIN(pstPlmnRegRejInfo->ucPlmnRegInfoNum ,(NAS_MMC_MAX_REG_PLMN_INFO_NUM - 1)))
    /* modified by z00234330 for coverity修改 2014-05-28 end */
    {
        /* 该网络已在列表中存在,更新注册原因值 */
        NAS_MMC_SetPlmnRegRejInfo(pstPlmn, enDomain, enCause, (pstPlmnRegList + ulIndex));
        /*lint -e961*/
        /* 判断网络是否存在注册失败的域信息，若未曾有注册失败的域信息，则将此网络从被拒信息表里删除 */
        if ( VOS_TRUE == NAS_MMC_IsPlmnRegInfoAllSucc( pstPlmnRegList + ulIndex ) )
        {
            (VOS_VOID)PS_MEM_MOVE(pstPlmnRegList + ulIndex, (pstPlmnRegList + ulIndex + 1),
                (pstPlmnRegRejInfo->ucPlmnRegInfoNum - ulIndex - 1) * sizeof(NAS_MMC_PLMN_REG_INFO_STRU));

            /* 更新列表中的个数 */
            pstPlmnRegRejInfo->ucPlmnRegInfoNum--;
        }
        /*lint +e961*/
        return;
    }

    /* 该网络不在注册表里且注册原因值为NULL,则不保存 */
    if ( NAS_MML_REG_FAIL_CAUSE_NULL == enCause )
    {
        return;
    }

    /* 当前网络不在保存的列表中或列表为空 */
    if (pstPlmnRegRejInfo->ucPlmnRegInfoNum < NAS_MMC_MAX_REG_PLMN_INFO_NUM)
    {
        /* 列表未满，追加注册原因到列表中 */
        NAS_MMC_SetPlmnRegRejInfo(pstPlmn, enDomain, enCause,
                     (pstPlmnRegList + pstPlmnRegRejInfo->ucPlmnRegInfoNum));

        /* 更新列表中的个数 */
        pstPlmnRegRejInfo->ucPlmnRegInfoNum++;
    }
    else
    {
        /* 列表已满, 最早的记录移动出数组 */
        (VOS_VOID)PS_MEM_MOVE(pstPlmnRegList, (pstPlmnRegList + 1),
                   (NAS_MMC_MAX_REG_PLMN_INFO_NUM - 1) * sizeof(NAS_MMC_PLMN_REG_INFO_STRU));

        /* 保存注册原因到列表中 */
        NAS_MMC_SetPlmnRegRejInfo(pstPlmn, enDomain, enCause,
              (pstPlmnRegList + (NAS_MMC_MAX_REG_PLMN_INFO_NUM - 1)));
    }

    return;

}

/*****************************************************************************
 函 数 名  : NAS_MMC_ConvertHplmnRegStatusToDomainInfo
 功能描述  : 根据注册结果转换为服务域信息
 输入参数  : pstPlmnRegInfo - hplmn注册结果信息
 输出参数  : pucDomainInfo  - 服务域信息
 返 回 值  : VOS_VOID
 调用函数  :
 被调函数  :

 修改历史      :
 1.日    期   : 2011年12月5日
   作    者   : z00161729
   修改内容   : 新生成函数

*****************************************************************************/
VOS_VOID NAS_MMC_ConvertHplmnRegStatusToDomainInfo(
    VOS_UINT8                          *pucDomainInfo,
    NAS_MMC_PLMN_REG_INFO_STRU         *pstPlmnRegInfo
)
{
    NAS_MML_NET_RAT_TYPE_ENUM_UINT8     enNetRatType;

    enNetRatType   = NAS_MML_GetCurrNetRatType();
    *pucDomainInfo = NAS_MMC_REG_DOMAIN_NONE;

    switch (enNetRatType)
    {
        case NAS_MML_NET_RAT_TYPE_GSM:
            if ((NAS_MML_REG_FAIL_CAUSE_PLMN_NOT_ALLOW == pstPlmnRegInfo->enGCsRegStatus)
             && (NAS_MML_REG_FAIL_CAUSE_PLMN_NOT_ALLOW == pstPlmnRegInfo->enGPsRegStatus))
            {
                *pucDomainInfo = NAS_MMC_REG_DOMAIN_PS_CS;
                return;
            }

            if (NAS_MML_REG_FAIL_CAUSE_PLMN_NOT_ALLOW == pstPlmnRegInfo->enGCsRegStatus)
            {
                *pucDomainInfo = NAS_MMC_REG_DOMAIN_CS;
                return;
            }

            if (NAS_MML_REG_FAIL_CAUSE_PLMN_NOT_ALLOW == pstPlmnRegInfo->enGPsRegStatus)
            {
                *pucDomainInfo = NAS_MMC_REG_DOMAIN_PS;
                return;
            }
            return;

        case NAS_MML_NET_RAT_TYPE_WCDMA:
            if ((NAS_MML_REG_FAIL_CAUSE_PLMN_NOT_ALLOW == pstPlmnRegInfo->enWCsRegStatus)
             && (NAS_MML_REG_FAIL_CAUSE_PLMN_NOT_ALLOW == pstPlmnRegInfo->enWPsRegStatus))
            {
                *pucDomainInfo = NAS_MMC_REG_DOMAIN_PS_CS;
                return;
            }

            if (NAS_MML_REG_FAIL_CAUSE_PLMN_NOT_ALLOW == pstPlmnRegInfo->enWCsRegStatus)
            {
                *pucDomainInfo = NAS_MMC_REG_DOMAIN_CS;
                return;
            }

            if (NAS_MML_REG_FAIL_CAUSE_PLMN_NOT_ALLOW == pstPlmnRegInfo->enWPsRegStatus)
            {
                *pucDomainInfo = NAS_MMC_REG_DOMAIN_PS;
                return;
            }
            return;

#if (FEATURE_ON == FEATURE_LTE)
        case NAS_MML_NET_RAT_TYPE_LTE:
            if ((NAS_MML_REG_FAIL_CAUSE_PLMN_NOT_ALLOW == pstPlmnRegInfo->enLCsRegStatus)
             && (NAS_MML_REG_FAIL_CAUSE_PLMN_NOT_ALLOW == pstPlmnRegInfo->enLPsRegStatus))
            {
                *pucDomainInfo = NAS_MMC_REG_DOMAIN_PS_CS;
                return;
            }

            if (NAS_MML_REG_FAIL_CAUSE_PLMN_NOT_ALLOW == pstPlmnRegInfo->enLCsRegStatus)
            {
                *pucDomainInfo = NAS_MMC_REG_DOMAIN_CS;
                return;
            }

            if (NAS_MML_REG_FAIL_CAUSE_PLMN_NOT_ALLOW == pstPlmnRegInfo->enLPsRegStatus)
            {
                *pucDomainInfo = NAS_MMC_REG_DOMAIN_EPS;
                return;
            }
            return;
#endif
        default:
            NAS_WARNING_LOG(WUEPS_PID_MMC, "NAS_MMC_ConvertHplmnRegStatusToDomainInfo:invalid rat type");
            return;
    }
}


/*****************************************************************************
 函 数 名  : NAS_MMC_GetHplmnRejDomainInfo
 功能描述  : 获取Ehplmn或Hplmn被拒绝的域
 输入参数  : 无
 输出参数  : pucRejDomainRlst,当前Plmn的注册被拒域结果
 返 回 值  : VOS_VOID
 调用函数  :
 被调函数  :

 修改历史      :
 1.日    期   : 2011年5月5日
   作    者   : luokaihui / l00167671
   修改内容   : 新生成函数

 2.日    期   : 2011年8月15日
   作    者   : W00167002
   修改内容   : 若当前网络不为HPLMN，直接返回前需要将拒绝域填写为0，否则为随机值，可能出错
 3.日    期   : 2011年12月5日
   作    者   : z00161729
   修改内容   : V7R1 phaseIV修改合并原NAS_MMC_HPLMN_REG_REJ_STRU和NAS_MMC_PLMN_REG_INFO_STRU

 4.日    期   : 2014年5月28日
   作    者   : z00234330
   修改内容   : covertity修改
*****************************************************************************/
VOS_VOID NAS_MMC_GetHplmnRejDomainInfo(
    VOS_UINT8                          *pucRejDomainRlst
)
{
    NAS_MMC_PLMN_REG_REJ_CTX_STRU      *pstRegRejCtx       = VOS_NULL_PTR;
    NAS_MML_PLMN_ID_STRU               *pstCurrPlmn        = VOS_NULL_PTR;
    VOS_UINT32                          ulIndex;

    /* 获取当前驻留的PLMN */
    pstCurrPlmn = NAS_MML_GetCurrCampPlmnId();

    /* 用于获取HPLMN注册被拒的列表 */
    pstRegRejCtx       = NAS_MMC_GetPlmnRegRejInfo();

    /* 当前驻留PLMN不在HPLMN列表中，则直接返回 */
    if (VOS_FALSE ==  NAS_MML_ComparePlmnIdWithHplmn(pstCurrPlmn))
    {
        *pucRejDomainRlst = NAS_MMC_REG_DOMAIN_NONE;

        return;
    }

    /* 判断当前网络是否在HPLMN注册被拒列表中 */
    ulIndex = NAS_MMC_GetPlmnIndexInRegInfoList(pstCurrPlmn,
                             pstRegRejCtx->ucPlmnRegInfoNum, pstRegRejCtx->astPlmnRegInfoList);


    /* modified by z00234330 for coverity修改 2014-05-28 begin */
    if (ulIndex < NAS_MML_MIN(pstRegRejCtx->ucPlmnRegInfoNum, (NAS_MMC_MAX_REG_PLMN_INFO_NUM - 1)))
    {
        /* 该网络已在HPLMN注册被拒列表中，更新其被拒域 */
        NAS_MMC_ConvertHplmnRegStatusToDomainInfo(pucRejDomainRlst,
                                             &pstRegRejCtx->astPlmnRegInfoList[ulIndex]);

    }
    /* modified by z00234330 for coverity修改 2014-05-28 end */
    else
    {
        *pucRejDomainRlst = NAS_MMC_REG_DOMAIN_NONE;
    }

    return;
}

/*****************************************************************************
 函 数 名  : NAS_MMC_ClearHplmnRejDomainInfo
 功能描述  : 在某个Ehplmn或Hplmn上注册成功时，清除对应域的被拒信息
 输出参数  : pstPlmn,需要清除被拒域信息的网络
             ucAcceptCnDomain,需要清除的服务域
 返 回 值  : VOS_VOID
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2010年3月24日
    作    者   : likelai
    修改内容   : 新生成函数
  2.日    期   : 2011年7月28日
    作    者   : L00171473
    修改内容   : V7R1 PhaseII 修改
*****************************************************************************/
VOS_VOID NAS_MMC_ClearHplmnRejDomainInfo(
    NAS_MML_PLMN_ID_STRU               *pstPlmn,
    VOS_UINT8                           ucAcceptCnDomain
)
{
    NAS_MMC_PLMN_REG_REJ_CTX_STRU      *pstRegRejCtx       = VOS_NULL_PTR;
    VOS_UINT8                           ucIdx;

    /* 获取HPLMN注册被拒的列表 */
    pstRegRejCtx       = NAS_MMC_GetPlmnRegRejInfo();

    /* 在HPLMN注册被拒列表中未查找到当前驻留PLMN，则直接返回 */
    ucIdx = (VOS_UINT8)NAS_MMC_GetPlmnIndexInRegInfoList(pstPlmn,
                            pstRegRejCtx->ucPlmnRegInfoNum, pstRegRejCtx->astPlmnRegInfoList);

    if (ucIdx >= pstRegRejCtx->ucPlmnRegInfoNum)
    {
        return;
    }

    /* 清除对应域的被拒信息 */
    NAS_MMC_UpdatePlmnRegInfoList(NAS_MML_GetCurrCampPlmnId(),
                      ucAcceptCnDomain, NAS_MML_REG_FAIL_CAUSE_NULL);

}

/*****************************************************************************
 函 数 名  : NAS_MMC_GetAbortEventType_BgPlmnSearch
 功能描述  : 获取BG_PLMN_SEARCH状态机上下文中的ABORT事件类型
 输入参数  : 无
 输出参数  : 无
 返 回 值  : ABORT事件类型
 调用函数  :
 被调函数  :

 修改历史      :
 1.日    期   : 2011年11月29日
   作    者   : w00167002
   修改内容   : 新生成函数

*****************************************************************************/
VOS_UINT32 NAS_MMC_GetAbortEventType_BgPlmnSearch(VOS_VOID)
{
    /* 如果当前状态机不是 BG_PLMN_SEARCH, 异常打印 */
    if (NAS_MMC_FSM_BG_PLMN_SEARCH != NAS_MMC_GetCurrFsmId())
    {
        NAS_ERROR_LOG(WUEPS_PID_MMC, "NAS_MMC_GetAbortEventType_BgPlmnSearch,ERROR:FsmId Error");
    }

    return (g_stNasMmcCtx.stCurFsm.unFsmCtx.stBgPlmnSearchCtx.ulAbortEventType);
}

/*****************************************************************************
 函 数 名  : NAS_MMC_SetAbortEventType_BgPlmnSearch
 功能描述  : 设置BG_PLMN_SEARCH状态机上下文中的ABORT事件类型
 输入参数  : ulAbortEventType: ABORT标志
 输出参数  : 无
 返 回 值  : 无
 调用函数  :
 被调函数  :

 修改历史      :
 1.日    期   : 2011年11月29日
   作    者   : w00167002
   修改内容   : 新生成函数

*****************************************************************************/
VOS_VOID NAS_MMC_SetAbortEventType_BgPlmnSearch(
    VOS_UINT32                          ulAbortEventType
)
{
    /* 如果当前状态机不是 BG_PLMN_SEARCH, 异常打印  */
    if (NAS_MMC_FSM_BG_PLMN_SEARCH != NAS_MMC_GetCurrFsmId())
    {
        NAS_ERROR_LOG(WUEPS_PID_MMC, "NAS_MMC_SetAbortEventType_BgPlmnSearch,ERROR:FsmId Error");
        return;
    }

    g_stNasMmcCtx.stCurFsm.unFsmCtx.stBgPlmnSearchCtx.ulAbortEventType = ulAbortEventType;
}



/*****************************************************************************
 函 数 名  : NAS_MMC_GetAbortType_BgPlmnSearch
 功能描述  : 获取BG PLMN SEARCH状态机上下文中的ABORT标志
 输入参数  : 无
 输出参数  : 无
 返 回 值  : NAS_MMC_ABORT_FSM_IMMEDIATELY: 立即打断
             NAS_MMC_ABORT_FSM_DELAY      : 延迟打断
 调用函数  :
 被调函数  :

 修改历史      :
 1.日    期   : 2011年9月21日
   作    者   : L00171473
   修改内容   : 新生成函数

*****************************************************************************/
NAS_MMC_ABORT_FSM_TYPE_UINT8 NAS_MMC_GetAbortType_BgPlmnSearch(VOS_VOID)
{
    /* 如果当前状态机不是 BG PLMN SEARCH, 异常打印 */
    if (NAS_MMC_FSM_BG_PLMN_SEARCH != NAS_MMC_GetCurrFsmId())
    {
        NAS_ERROR_LOG(WUEPS_PID_MMC, "NAS_MMC_GetAbortType_BgPlmnSearch,ERROR:FsmId Error");
    }

    return (g_stNasMmcCtx.stCurFsm.unFsmCtx.stBgPlmnSearchCtx.enAbortType);
}

/*****************************************************************************
 函 数 名  : NAS_MMC_SetAbortType_BgPlmnSearch
 功能描述  : 设置BG PLMN SEARCH状态机上下文中的ABORT标志
 输入参数  : enAbortType: ABORT标志
 输出参数  : 无
 返 回 值  : 无
 调用函数  :
 被调函数  :

 修改历史      :
 1.日    期   : 2011年9月21日
   作    者   : L00171473
   修改内容   : 新生成函数

*****************************************************************************/
VOS_VOID NAS_MMC_SetAbortType_BgPlmnSearch(
    NAS_MMC_ABORT_FSM_TYPE_UINT8        enAbortType
)
{
    /* 如果当前状态机不是 BG PLMN SEARCH, 异常打印  */
    if (NAS_MMC_FSM_BG_PLMN_SEARCH != NAS_MMC_GetCurrFsmId())
    {
        NAS_ERROR_LOG(WUEPS_PID_MMC, "NAS_MMC_SetAbortType_BgPlmnSearch,ERROR:FsmId Error");
        return;
    }

    g_stNasMmcCtx.stCurFsm.unFsmCtx.stBgPlmnSearchCtx.enAbortType = enAbortType;
}

/*****************************************************************************
 函 数 名  : NAS_MMC_GetNeedSndSysInfo_BgPlmnSearch
 功能描述  : 更新BG PLMN SEARCH状态机上下文中的ucNeedSndSysInfo标志
 输入参数  : VOS_VOID
 输出参数  : 无
 返 回 值  : VOS_UINT8
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2012年6月25日
    作    者   : l60609
    修改内容   : 新生成函数

*****************************************************************************/
VOS_UINT8 NAS_MMC_GetNeedSndSysInfo_BgPlmnSearch(VOS_VOID)
{
    /* 如果当前状态机不是 BG PLMN SEARCH, 异常打印  */
    if (NAS_MMC_FSM_BG_PLMN_SEARCH != NAS_MMC_GetCurrFsmId())
    {
        NAS_ERROR_LOG(WUEPS_PID_MMC, "NAS_MMC_GetNeedSndSysInfo_BgPlmnSearch,ERROR:FsmId Error");
    }

    return g_stNasMmcCtx.stCurFsm.unFsmCtx.stBgPlmnSearchCtx.ucNeedSndSysInfo;
}

/*****************************************************************************
 函 数 名  : NAS_MMC_SetNeedSndSysInfo_BgPlmnSearch
 功能描述  : 设置BG PLMN SEARCH状态机上下文中的ucNeedSndSysInfo标志
 输入参数  : VOS_UINT8 ucNeedSndSysInfo
 输出参数  : 无
 返 回 值  : VOS_VOID
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2012年6月25日
    作    者   : l60609
    修改内容   : 新生成函数

*****************************************************************************/
VOS_VOID NAS_MMC_SetNeedSndSysInfo_BgPlmnSearch(
    VOS_UINT8                           ucNeedSndSysInfo
)
{
    /* 如果当前状态机不是 BG PLMN SEARCH, 异常打印  */
    if (NAS_MMC_FSM_BG_PLMN_SEARCH != NAS_MMC_GetCurrFsmId())
    {
        NAS_ERROR_LOG(WUEPS_PID_MMC, "NAS_MMC_SetNeedSndSysInfo_BgPlmnSearch,ERROR:FsmId Error");
        return;
    }

    g_stNasMmcCtx.stCurFsm.unFsmCtx.stBgPlmnSearchCtx.ucNeedSndSysInfo = ucNeedSndSysInfo;
}


/*****************************************************************************
 函 数 名  : NAS_MMC_GetRelRequestFlag_BgPlmnSearch
 功能描述  : 获取BG PLMN SEARCH状态机上下文中的是否主动请求连接标志
 输入参数  : 无
 输出参数  : 无
 返 回 值  : VOS_TRUE :是主动请求
             VOS_FALSE:被动等待释放
 调用函数  :
 被调函数  :

 修改历史      :
 1.日    期   : 2011年9月22日
   作    者   : L00171473
   修改内容   : 新生成函数

*****************************************************************************/
VOS_UINT8 NAS_MMC_GetRelRequestFlag_BgPlmnSearch(VOS_VOID)
{
    /* 如果当前状态机不是 BG PLMN SEARCH, 异常打印 */
    if (NAS_MMC_FSM_BG_PLMN_SEARCH != NAS_MMC_GetCurrFsmId())
    {
        NAS_ERROR_LOG(WUEPS_PID_MMC, "NAS_MMC_GetRelRequestFlag_BgPlmnSearch,ERROR:FsmId Error");
    }

    return (g_stNasMmcCtx.stCurFsm.unFsmCtx.stBgPlmnSearchCtx.stCurHighPrioPlmnRegInfo.ucRelRequestFlg);
}

/*****************************************************************************
 函 数 名  : NAS_MMC_SetRelRequestFlag_BgPlmnSearch
 功能描述  : 设置BG PLMN SEARCH状态机上下文中的是否主动请求连接标志
 输入参数  : ucRelRequestFlg: 是否主动请求连接标志
 输出参数  : 无
 返 回 值  : 无
 调用函数  :
 被调函数  :

 修改历史      :
 1.日    期   : 2011年9月22日
   作    者   : L00171473
   修改内容   : 新生成函数

*****************************************************************************/
VOS_VOID NAS_MMC_SetRelRequestFlag_BgPlmnSearch(
    VOS_UINT8                           ucRelRequestFlg
)
{
    /* 如果当前状态机不是 BG PLMN SEARCH, 异常打印  */
    if (NAS_MMC_FSM_BG_PLMN_SEARCH !=NAS_MMC_GetCurrFsmId())
    {
        NAS_ERROR_LOG(WUEPS_PID_MMC, "NAS_MMC_SetRelRequestFlag_BgPlmnSearch,ERROR:FsmId Error");
        return ;
    }

    g_stNasMmcCtx.stCurFsm.unFsmCtx.stBgPlmnSearchCtx.stCurHighPrioPlmnRegInfo.ucRelRequestFlg = ucRelRequestFlg;
}

/*****************************************************************************
 函 数 名  : NAS_MMC_GetWaitRegRsltFlag_BgPlmnSearch
 功能描述  : 获取BG PLMN SEARCH状态机上下文中的等待CS/PS的注册结果的标志
 输入参数  : VOS_VOID
 输出参数  : 无
 返 回 值  : VOS_UINT8
 调用函数  :
 被调函数  :

 修改历史      :
 1.日    期   : 2011年9月22日
   作    者   : L00171473
   修改内容   : 新生成函数

*****************************************************************************/
VOS_UINT8 NAS_MMC_GetWaitRegRsltFlag_BgPlmnSearch(VOS_VOID)
{
    /* 如果当前状态机不是 BG PLMN SEARCH, 异常打印 */
    if (NAS_MMC_FSM_BG_PLMN_SEARCH != NAS_MMC_GetCurrFsmId())
    {
        NAS_ERROR_LOG(WUEPS_PID_MMC, "NAS_MMC_GetWaitRegRsltFlag_BgPlmnSearch,ERROR:FsmId Error");
    }

    return (g_stNasMmcCtx.stCurFsm.unFsmCtx.stBgPlmnSearchCtx.stCurHighPrioPlmnRegInfo.ucWaitRegRsltFlag);
}

/*****************************************************************************
 函 数 名  : NAS_MMC_SetWaitRegRsltFlag_BgPlmnSearch
 功能描述  : 设置BG PLMN SEARCH状态机上下文中的等待CS/PS的注册结果的标志
 输入参数  : VOS_UINT8                           ucWaitFlag
 输出参数  : 无
 返 回 值  : VOS_VOID
 调用函数  :
 被调函数  :

 修改历史      :
 1.日    期   : 2011年9月22日
   作    者   : L00171473
   修改内容   : 新生成函数

*****************************************************************************/
VOS_VOID NAS_MMC_SetWaitRegRsltFlag_BgPlmnSearch(
    VOS_UINT8                           ucWaitFlag
)
{
    /* 如果当前状态机不是 BG PLMN SEARCH, 异常打印 */
    if (NAS_MMC_FSM_BG_PLMN_SEARCH != NAS_MMC_GetCurrFsmId())
    {
        NAS_ERROR_LOG(WUEPS_PID_MMC, "NAS_MMC_SetWaitRegRsltFlag_BgPlmnSearch,ERROR:FsmId Error");
        return;
    }

    g_stNasMmcCtx.stCurFsm.unFsmCtx.stBgPlmnSearchCtx.stCurHighPrioPlmnRegInfo.ucWaitRegRsltFlag |= ucWaitFlag;
}

/*****************************************************************************
 函 数 名  : NAS_MMC_ClearSingleDomainWaitRegRsltFlag_BgPlmnSearch
 功能描述  : 清除BG PLMN SEARCH状态机上下文中的等待指定域的注册结果的标志
 输入参数  : VOS_UINT8                           ucRegDomain
 输出参数  : 无
 返 回 值  : VOS_VOID
 调用函数  :
 被调函数  :

 修改历史      :
 1.日    期   : 2011年9月22日
   作    者   : L00171473
   修改内容   : 新生成函数

*****************************************************************************/
VOS_VOID NAS_MMC_ClearSingleDomainWaitRegRsltFlag_BgPlmnSearch(
    VOS_UINT8                           ucRegDomain
)
{
    /* 如果当前状态机不是 BG PLMN SEARCH, 异常打印 */
    if (NAS_MMC_FSM_BG_PLMN_SEARCH != NAS_MMC_GetCurrFsmId())
    {
        NAS_ERROR_LOG(WUEPS_PID_MMC, "NAS_MMC_ClearSingleDomainWaitRegRsltFlag_BgPlmnSearch,ERROR:FsmId Error");
        return;
    }

    g_stNasMmcCtx.stCurFsm.unFsmCtx.stBgPlmnSearchCtx.stCurHighPrioPlmnRegInfo.ucWaitRegRsltFlag &= ~ucRegDomain;
}

/*****************************************************************************
 函 数 名  : NAS_MMC_ClearAllWaitRegRsltFlag_BgPlmnSearch
 功能描述  : 清除状态机上下文中的等待CS/PS域的注册结果的标志
 输入参数  : VOS_VOID
 输出参数  : 无
 返 回 值  : VOS_VOID
 调用函数  :
 被调函数  :

 修改历史      :
 1.日    期   : 2011年9月22日
   作    者   : L00171473
   修改内容   : 新生成函数

*****************************************************************************/
VOS_VOID NAS_MMC_ClearAllWaitRegRsltFlag_BgPlmnSearch(VOS_VOID)
{
    /* 如果当前状态机不是 BG PLMN SEARCH, 异常打印 */
    if (NAS_MMC_FSM_BG_PLMN_SEARCH != NAS_MMC_GetCurrFsmId())
    {
        NAS_ERROR_LOG(WUEPS_PID_MMC, "NAS_MMC_ClearAllWaitRegRsltFlag_BgPlmnSearch,ERROR:FsmId Error");
        return;
    }

    g_stNasMmcCtx.stCurFsm.unFsmCtx.stBgPlmnSearchCtx.stCurHighPrioPlmnRegInfo.ucWaitRegRsltFlag = NAS_MMC_WAIT_REG_RESULT_IND_NULL;
}

/*****************************************************************************
 函 数 名  : NAS_MMC_GetCsRegAdditionalAction_BgPlmnSearch
 功能描述  : 获取BG PLMN SEARCH状态机上下文中的CS注册结果触发的后续动作
 输入参数  : VOS_VOID
 输出参数  : 无
 返 回 值  : NAS_MMC_ADDITIONAL_ACTION_ENUM_UINT8
 调用函数  :
 被调函数  :

 修改历史      :
 1.日    期   : 2011年9月22日
   作    者   : L00171473
   修改内容   : 新生成函数

*****************************************************************************/
NAS_MMC_ADDITIONAL_ACTION_ENUM_UINT8 NAS_MMC_GetCsRegAdditionalAction_BgPlmnSearch(VOS_VOID)
{
    /* 如果当前状态机不是 BG PLMN SEARCH, 异常打印 */
    if (NAS_MMC_FSM_BG_PLMN_SEARCH != NAS_MMC_GetCurrFsmId())
    {
        NAS_ERROR_LOG(WUEPS_PID_MMC, "NAS_MMC_GetCsRegAdditionalAction_BgPlmnSearch,ERROR:FsmId Error");
    }

    return (g_stNasMmcCtx.stCurFsm.unFsmCtx.stBgPlmnSearchCtx.stCurHighPrioPlmnRegInfo.enCsRegAdditionalAction);
}

/*****************************************************************************
 函 数 名  : NAS_MMC_SetCsRegAdditionalAction_BgPlmnSearch
 功能描述  : 设置BG PLMN SEARCH状态机上下文中的CS注册结果触发的后续动作
 输入参数  : NAS_MMC_ADDITIONAL_ACTION_ENUM_UINT8 enCsAddtionalAction
 输出参数  : 无
 返 回 值  : VOS_VOID
 调用函数  :
 被调函数  :

 修改历史      :
 1.日    期   : 2011年9月22日
   作    者   : L00171473
   修改内容   : 新生成函数

*****************************************************************************/
VOS_VOID NAS_MMC_SetCsRegAdditionalAction_BgPlmnSearch(
    NAS_MMC_ADDITIONAL_ACTION_ENUM_UINT8 enCsAddtionalAction
)
{
    /* 如果当前状态机不是 BG PLMN SEARCH, 异常打印 */
    if (NAS_MMC_FSM_BG_PLMN_SEARCH != NAS_MMC_GetCurrFsmId())
    {
        NAS_ERROR_LOG(WUEPS_PID_MMC, "NAS_MMC_SetCsRegAdditionalAction_BgPlmnSearch,ERROR:FsmId Error");
        return;
    }

    g_stNasMmcCtx.stCurFsm.unFsmCtx.stBgPlmnSearchCtx.stCurHighPrioPlmnRegInfo.enCsRegAdditionalAction = enCsAddtionalAction;
}

/*****************************************************************************
 函 数 名  : NAS_MMC_GetPsRegAdditionalAction_BgPlmnSearch
 功能描述  : 获取BG PLMN SEARCH状态机上下文中的PS注册结果触发的后续动作
 输入参数  : VOS_VOID
 输出参数  : 无
 返 回 值  : NAS_MMC_ADDITIONAL_ACTION_ENUM_UINT8
 调用函数  :
 被调函数  :

 修改历史      :
 1.日    期   : 2011年9月22日
   作    者   : L00171473
   修改内容   : 新生成函数

*****************************************************************************/
NAS_MMC_ADDITIONAL_ACTION_ENUM_UINT8 NAS_MMC_GetPsRegAdditionalAction_BgPlmnSearch(VOS_VOID)
{
    /* 如果当前状态机不是 BG PLMN SEARCH, 异常打印 */
    if (NAS_MMC_FSM_BG_PLMN_SEARCH != NAS_MMC_GetCurrFsmId())
    {
        NAS_ERROR_LOG(WUEPS_PID_MMC, "NAS_MMC_GetPsRegAdditionalAction_BgPlmnSearch,ERROR:FsmId Error");
    }

    return (g_stNasMmcCtx.stCurFsm.unFsmCtx.stBgPlmnSearchCtx.stCurHighPrioPlmnRegInfo.enPsRegAdditionalAction);
}

/*****************************************************************************
 函 数 名  : NAS_MMC_SetPsRegAdditionalAction_BgPlmnSearch
 功能描述  : 设置BG PLMN SEARCH状态机上下文中的PS注册结果触发的后续动作
 输入参数  : NAS_MMC_ADDITIONAL_ACTION_ENUM_UINT8 enPsAddtionalAction
 输出参数  : 无
 返 回 值  : VOS_VOID
 调用函数  :
 被调函数  :

 修改历史      :
 1.日    期   : 2011年9月22日
   作    者   : L00171473
   修改内容   : 新生成函数

*****************************************************************************/
VOS_VOID NAS_MMC_SetPsRegAdditionalAction_BgPlmnSearch(
    NAS_MMC_ADDITIONAL_ACTION_ENUM_UINT8 enPsAddtionalAction
)
{
    /* 如果当前状态机不是 BG PLMN SEARCH, 异常打印 */
    if (NAS_MMC_FSM_BG_PLMN_SEARCH != NAS_MMC_GetCurrFsmId())
    {
        NAS_ERROR_LOG(WUEPS_PID_MMC, "NAS_MMC_SetPsRegAdditionalAction_BgPlmnSearch,ERROR:FsmId Error");
        return;
    }

    g_stNasMmcCtx.stCurFsm.unFsmCtx.stBgPlmnSearchCtx.stCurHighPrioPlmnRegInfo.enPsRegAdditionalAction = enPsAddtionalAction;
}

/*****************************************************************************
 函 数 名  : NAS_MMC_GetCurHighPrioPlmn_BgPlmnSearch
 功能描述  : 获取BG PLMN SEARCH状态机上下文中的当前正在尝试的高优先级网络的信息
 输入参数  : VOS_VOID
 输出参数  : 无
 返 回 值  : NAS_MML_PLMN_WITH_RAT_STRU*
 调用函数  :
 被调函数  :

 修改历史      :
 1.日    期   : 2011年9月22日
   作    者   : L00171473
   修改内容   : 新生成函数

*****************************************************************************/
NAS_MML_PLMN_WITH_RAT_STRU* NAS_MMC_GetCurHighPrioPlmn_BgPlmnSearch(VOS_VOID)
{
    /* 如果当前状态机不是 BG PLMN SEARCH, 异常打印 */
    if (NAS_MMC_FSM_BG_PLMN_SEARCH != NAS_MMC_GetCurrFsmId())
    {
        NAS_ERROR_LOG(WUEPS_PID_MMC, "NAS_MMC_GetCurHighPrioPlmn_BgPlmnSearch,ERROR:FsmId Error");
    }

    return &(g_stNasMmcCtx.stCurFsm.unFsmCtx.stBgPlmnSearchCtx.stCurHighPrioPlmn);
}

/*****************************************************************************
 函 数 名  : NAS_MMC_SetCurHighPrioPlmn_BgPlmnSearch
 功能描述  : 设置BG PLMN SEARCH状态机上下文中的当前正在尝试的高优先级网络的信息
 输入参数  : NAS_MML_PLMN_ID_STRU                stPlmnId
             NAS_MML_NET_RAT_TYPE_ENUM_UINT8     enRat
 输出参数  : 无
 返 回 值  : VOS_VOID
 调用函数  :
 被调函数  :

 修改历史      :
 1.日    期   : 2011年9月22日
   作    者   : L00171473
   修改内容   : 新生成函数

*****************************************************************************/
VOS_VOID NAS_MMC_SetCurHighPrioPlmn_BgPlmnSearch(
    NAS_MML_PLMN_ID_STRU               *pstPlmnId,
    NAS_MML_NET_RAT_TYPE_ENUM_UINT8     enRat
)
{
    /* 如果当前状态机不是 BG PLMN SEARCH, 异常打印 */
    if (NAS_MMC_FSM_BG_PLMN_SEARCH != NAS_MMC_GetCurrFsmId())
    {
        NAS_ERROR_LOG(WUEPS_PID_MMC, "NAS_MMC_SetCurHighPrioPlmn_BgPlmnSearch,ERROR:FsmId Error");
        return;
    }

    g_stNasMmcCtx.stCurFsm.unFsmCtx.stBgPlmnSearchCtx.stCurHighPrioPlmn.stPlmnId = *pstPlmnId;
    g_stNasMmcCtx.stCurFsm.unFsmCtx.stBgPlmnSearchCtx.stCurHighPrioPlmn.enRat    = enRat;
}

/*****************************************************************************
 函 数 名  : NAS_MMC_GetPreCampPlmn_BgPlmnSearch
 功能描述  : 获取BG PLMN SEARCH状态机上下文中的发起BG搜索时驻留的PLMN信息
 输入参数  : VOS_VOID
 输出参数  : 无
 返 回 值  : BG搜之前驻留的VPLMN的信息
 调用函数  :
 被调函数  :

 修改历史      :
 1.日    期   : 2011年9月22日
   作    者   : L00171473
   修改内容   : 新生成函数

*****************************************************************************/
NAS_MML_PLMN_WITH_RAT_STRU* NAS_MMC_GetPreCampPlmn_BgPlmnSearch(VOS_VOID)
{
    /* 如果当前状态机不是 BG PLMN SEARCH, 异常打印 */
    if (NAS_MMC_FSM_BG_PLMN_SEARCH != NAS_MMC_GetCurrFsmId())
    {
        NAS_ERROR_LOG(WUEPS_PID_MMC, "NAS_MMC_GetPreCampPlmn_BgPlmnSearch,ERROR:FsmId Error");
    }

    return &(g_stNasMmcCtx.stCurFsm.unFsmCtx.stBgPlmnSearchCtx.stPreCampPlmn);
}

/*****************************************************************************
 函 数 名  : NAS_MMC_SetPreCampPlmn_BgPlmnSearch
 功能描述  : 设置BG PLMN SEARCH状态机上下文中的发起BG搜索时驻留的PLMN信息
 输入参数  : stPlmnId -- 发起BG搜索时驻留的PLMN ID
             enRat    -- 发起BG搜索时驻留的PLMN的接入技术
 输出参数  : 无
 返 回 值  : VOS_VOID
 调用函数  :
 被调函数  :

 修改历史      :
 1.日    期   : 2011年9月22日
   作    者   : L00171473
   修改内容   : 新生成函数

*****************************************************************************/
VOS_VOID NAS_MMC_SetPreCampPlmn_BgPlmnSearch(
    NAS_MML_PLMN_ID_STRU               *pstPlmnId,
    NAS_MML_NET_RAT_TYPE_ENUM_UINT8     enRat
)
{
    /* 如果当前状态机不是 BG PLMN SEARCH, 异常打印 */
    if (NAS_MMC_FSM_BG_PLMN_SEARCH != NAS_MMC_GetCurrFsmId())
    {
        NAS_ERROR_LOG(WUEPS_PID_MMC, "NAS_MMC_SetPreCampPlmn_BgPlmnSearch,ERROR:FsmId Error");
        return;
    }

    g_stNasMmcCtx.stCurFsm.unFsmCtx.stBgPlmnSearchCtx.stPreCampPlmn.stPlmnId = *pstPlmnId;
    g_stNasMmcCtx.stCurFsm.unFsmCtx.stBgPlmnSearchCtx.stPreCampPlmn.enRat    = enRat;
}




/*****************************************************************************
 函 数 名  : NAS_MMC_SetPreCampPlmnRat_BgPlmnSearch
 功能描述  : 设置BG PLMN SEARCH状态机上下文中的发起BG搜索时驻留的PLMN接入技术信息
 输入参数  : enRat    -- 发起BG搜索时驻留的PLMN的接入技术
 输出参数  : 无
 返 回 值  : VOS_VOID
 调用函数  :
 被调函数  :

 修改历史      :
 1.日    期   : 2011年10月4日
   作    者   : w00167002
   修改内容   : 新生成函数

*****************************************************************************/
VOS_VOID NAS_MMC_SetPreCampPlmnRat_BgPlmnSearch(
    NAS_MML_NET_RAT_TYPE_ENUM_UINT8     enRat
)
{
    /* 如果当前状态机不是 BG PLMN SEARCH, 异常打印 */
    if (NAS_MMC_FSM_BG_PLMN_SEARCH != NAS_MMC_GetCurrFsmId())
    {
        NAS_ERROR_LOG(WUEPS_PID_MMC, "NAS_MMC_SetPreCampPlmn_BgPlmnSearch,ERROR:FsmId Error");
        return;
    }

    g_stNasMmcCtx.stCurFsm.unFsmCtx.stBgPlmnSearchCtx.stPreCampPlmn.enRat    = enRat;
}


/*****************************************************************************
 函 数 名  : NAS_MMC_GetPreEquPlmnInfo_BgPlmnSearch
 功能描述  : 获取BG PLMN SEARCH状态机上下文中的EquPlmn的信息
 输入参数  : VOS_VOID
 输出参数  : 无
 返 回 值  : 返回状态机上下文中VPLMN的EPLMN信息
 调用函数  :
 被调函数  :

 修改历史      :
 1.日    期   : 2011年9月22日
   作    者   : w00167002
   修改内容   : 新生成函数

*****************************************************************************/
NAS_MML_EQUPLMN_INFO_STRU* NAS_MMC_GetPreEquPlmnInfo_BgPlmnSearch(VOS_VOID)
{
    /* 如果当前状态机不是 BG_PLMN_SEARCH, 异常打印 */
    if (NAS_MMC_FSM_BG_PLMN_SEARCH != NAS_MMC_GetCurrFsmId())
    {
        NAS_ERROR_LOG(WUEPS_PID_MMC, "NAS_MMC_GetPreEquPlmnInfo_BgPlmnSearch,ERROR:FsmId Error");
    }

    return &(g_stNasMmcCtx.stCurFsm.unFsmCtx.stBgPlmnSearchCtx.stPreEquPlmnInfo);
}

/*****************************************************************************
 函 数 名  : NAS_MMC_SetPreEquPlmnInfo_BgPlmnSearch
 功能描述  : 设置BG PLMN SEARCH状态机上下文中的EQUPLMN信息
 输入参数  : NAS_MML_PLMN_ID_STRU                pstCurrCampPlmnId
             NAS_MML_EQUPLMN_INFO_STRU          *pstEquPlmnInfo
 输出参数  : 无
 返 回 值  : VOS_VOID
 调用函数  :
 被调函数  :

 修改历史      :
 1.日    期   : 2011年9月22日
   作    者   : w00167002
   修改内容   : 新生成函数

*****************************************************************************/
VOS_VOID NAS_MMC_SetPreEquPlmnInfo_BgPlmnSearch(
    NAS_MML_PLMN_ID_STRU               *pstCurrCampPlmnId,
    NAS_MML_EQUPLMN_INFO_STRU          *pstEquPlmnInfo
)
{
    /* 如果当前状态机不是 BG_PLMN_SEARCH, 异常打印 */
    if (NAS_MMC_FSM_BG_PLMN_SEARCH != NAS_MMC_GetCurrFsmId())
    {
        NAS_ERROR_LOG(WUEPS_PID_MMC, "NAS_MMC_SetPreEquPlmnInfo_BgPlmnSearch,ERROR:FsmId Error");

        return;
    }

    /* 第一个EQUPLMN(即RPLMN)与当前驻留网络相同, 则保存当前驻留网络的EQUPLMN到状态机上下文 */
    if (VOS_TRUE == NAS_MML_CompareBcchPlmnwithSimPlmn(pstCurrCampPlmnId,
                                                       &(pstEquPlmnInfo->astEquPlmnAddr[0])))
    {
        g_stNasMmcCtx.stCurFsm.unFsmCtx.stBgPlmnSearchCtx.stPreEquPlmnInfo = *pstEquPlmnInfo;
    }
    else
    {
        g_stNasMmcCtx.stCurFsm.unFsmCtx.stBgPlmnSearchCtx.stPreEquPlmnInfo.ucEquPlmnNum = 0x1;
        g_stNasMmcCtx.stCurFsm.unFsmCtx.stBgPlmnSearchCtx.stPreEquPlmnInfo.astEquPlmnAddr[0] = *pstCurrCampPlmnId;
    }

    return;
}

#if (FEATURE_ON == FEATURE_LTE)
/*****************************************************************************
 函 数 名  : NAS_MMC_SetPreLteDisableFlg_BgPlmnSearch
 功能描述  : 设置BG PLMN SEARCH状态机上下文中的L disable的状态
 输入参数  : enLteCapStatus - Lte capability状态
 输出参数  : 无
 返 回 值  : 无
 调用函数  :
 被调函数  :

 修改历史      :
 1.日    期   : 2012年5月8日
   作    者   : z00161729
   修改内容   : 新生成函数

*****************************************************************************/
VOS_VOID NAS_MMC_SetPreLteDisableFlg_BgPlmnSearch(
    NAS_MML_LTE_CAPABILITY_STATUS_ENUM_UINT32               enLteCapStatus
)
{
    /* 如果当前状态机不是 BG_PLMN_SEARCH, 异常打印 */
    if (NAS_MMC_FSM_BG_PLMN_SEARCH != NAS_MMC_GetCurrFsmId())
    {
        NAS_ERROR_LOG(WUEPS_PID_MMC, "NAS_MMC_SetPreLteDisableFlg_BgPlmnSearch,ERROR:FsmId Error");
        return;
    }

    if ((NAS_MML_LTE_CAPABILITY_STATUS_DISABLE_UNNOTIFY_AS == enLteCapStatus)
     || (NAS_MML_LTE_CAPABILITY_STATUS_DISABLE_NOTIFIED_AS == enLteCapStatus))
    {
        g_stNasMmcCtx.stCurFsm.unFsmCtx.stBgPlmnSearchCtx.ucPreLteDisableFlg = VOS_TRUE;
        return;
    }

    g_stNasMmcCtx.stCurFsm.unFsmCtx.stBgPlmnSearchCtx.ucPreLteDisableFlg = VOS_FALSE;
    return;
}

/*****************************************************************************
 函 数 名  : NAS_MMC_GetPreLteDisableFlg_BgPlmnSearch
 功能描述  : 获取BG PLMN SEARCH状态机上下文中的L disable的状态
 输入参数  : 无
 输出参数  : 无
 返 回 值  : Lte capability状态
 调用函数  :
 被调函数  :

 修改历史      :
 1.日    期   : 2012年5月8日
   作    者   : z00161729
   修改内容   : 新生成函数

*****************************************************************************/
VOS_UINT32 NAS_MMC_GetPreLteDisableFlg_BgPlmnSearch(VOS_VOID)
{
    /* 如果当前状态机不是 BG_PLMN_SEARCH, 异常打印 */
    if (NAS_MMC_FSM_BG_PLMN_SEARCH != NAS_MMC_GetCurrFsmId())
    {
        NAS_ERROR_LOG(WUEPS_PID_MMC, "NAS_MMC_SetPreLteDisableFlg_BgPlmnSearch,ERROR:FsmId Error");
    }

    return g_stNasMmcCtx.stCurFsm.unFsmCtx.stBgPlmnSearchCtx.ucPreLteDisableFlg;
}
/*****************************************************************************
 函 数 名  : NAS_MMC_SetPreLteDisableFlg_BgPlmnSearch
 功能描述  : 设置BG PLMN SEARCH状态机上下文中的是否需要enbale LTE的状态
 输入参数  : ucNeedEnableLteFlg   是否需要enable LTE标志
 输出参数  : 无
 返 回 值  : 无
 调用函数  :
 被调函数  :

 修改历史      :
 1.日    期   : 2014年5月15日
   作    者   : b00269685
   修改内容   : 新生成函数

*****************************************************************************/
VOS_VOID NAS_MMC_SetNeedEnableLteFlg_BgPlmnSearch(VOS_UINT8 ucNeedEnableLteFlg)
{
    /* 如果当前状态机不是 BG_PLMN_SEARCH, 异常打印 */
    if (NAS_MMC_FSM_BG_PLMN_SEARCH != NAS_MMC_GetCurrFsmId())
    {
        NAS_ERROR_LOG(WUEPS_PID_MMC, "NAS_MMC_SetNeedEnableLteFlg_BgPlmnSearch,ERROR:FsmId Error");
        return;
    }

    g_stNasMmcCtx.stCurFsm.unFsmCtx.stBgPlmnSearchCtx.ucNeedEnableLteFlg = ucNeedEnableLteFlg;
    return;
}

/*****************************************************************************
 函 数 名  : NAS_MMC_GetPreLteDisableFlg_BgPlmnSearch
 功能描述  : 得到BG PLMN SEARCH状态机上下文中的是否需要enbale LTE的状态
 输入参数  : 无
 输出参数  : 无
 返 回 值  : BG PLMN SEARCH状态机上下文中的是否需要enbale LTE的状态
 调用函数  :
 被调函数  :

 修改历史      :
 1.日    期   : 2014年5月15日
   作    者   : b00269685
   修改内容   : 新生成函数

*****************************************************************************/
VOS_UINT32 NAS_MMC_GetNeedEnableLteFlg_BgPlmnSearch(VOS_VOID)
{
    /* 如果当前状态机不是 BG_PLMN_SEARCH, 异常打印 */
    if (NAS_MMC_FSM_BG_PLMN_SEARCH != NAS_MMC_GetCurrFsmId())
    {
        NAS_ERROR_LOG(WUEPS_PID_MMC, "NAS_MMC_GetNeedEnableLteFlg_BgPlmnSearch,ERROR:FsmId Error");
    }

    return g_stNasMmcCtx.stCurFsm.unFsmCtx.stBgPlmnSearchCtx.ucNeedEnableLteFlg;
}
#endif

/*****************************************************************************
 函 数 名  : NAS_MMC_SetFirstStartHPlmnTimerFlg
 功能描述  : 设置是否为首次启动HPLMN定时器
 输入参数  : ulFirstStartHPlmnTimer - 首次或非首次启动HPLMN定时器
 输出参数  : 无
 返 回 值  : 无
 调用函数  :
 被调函数  :

 修改历史      :
 1.日    期   : 2011年9月25日
   作    者   : z00161729
   修改内容   : 新生成函数

*****************************************************************************/
VOS_VOID NAS_MMC_SetFirstStartHPlmnTimerFlg(
    VOS_UINT8                           ucFirstStartHPlmnTimer
)
{
    g_stNasMmcCtx.stHighPrioPlmnSearchCtrl.ucFirstStartHPlmnTimerFlg = ucFirstStartHPlmnTimer;
}

/*****************************************************************************
 函 数 名  : NAS_MMC_GetFirstStartHPlmnTimerFlg
 功能描述  : 获取首次或非首次启动HPLMN定时器标志
 输入参数  : 无
 输出参数  : 无
 返 回 值  : VOS_TRUE:首次启动HPLMN定时器
             VOS_FALSE:非首次启动HPLMN定时器
 调用函数  :
 被调函数  :

 修改历史      :
 1.日    期   : 2011年9月25日
   作    者   : z00161729
   修改内容   : 新生成函数

*****************************************************************************/
VOS_UINT8 NAS_MMC_GetFirstStartHPlmnTimerFlg(VOS_VOID)
{
    return g_stNasMmcCtx.stHighPrioPlmnSearchCtrl.ucFirstStartHPlmnTimerFlg;
}

/*****************************************************************************
 函 数 名  : NAS_MMC_GetHplmnTimerLen
 功能描述  : 获取当前HPLMN定时器的时长
 输入参数  : 无
 输出参数  : 无
 返 回 值  : 当前定时器的时长，单位毫秒
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2011年9月23日
    作    者   : z00161729
    修改内容   : 新生成函数

*****************************************************************************/
VOS_UINT32  NAS_MMC_GetHplmnTimerLen( VOS_VOID )
{
    NAS_MML_BG_SEARCH_CFG_INFO_STRU    *pstBgSearchCfg = VOS_NULL_PTR;
    VOS_UINT32                          ulHplmnTimerLen;

    pstBgSearchCfg = NAS_MML_GetBgSearchCfg();

    if (VOS_TRUE == NAS_MMC_GetFirstStartHPlmnTimerFlg())
    {
        /* 首次启动，从NV：en_NV_Item_HPlmnFirstTimer中读取，默认为2分钟 */
        ulHplmnTimerLen = pstBgSearchCfg->ulFirstStartHplmnTimerLen;
    }
    else
    {
        ulHplmnTimerLen = NAS_MML_GetSimHplmnTimerLen();
        
        NAS_NORMAL_LOG1(WUEPS_PID_MMC, "GetHplmnTimerLen:NAS_MML_GetSimHplmnTimerLen is",ulHplmnTimerLen);
    }

    /* H3G需求: VPLMN下非首次搜HPLMN周期可在NV中配置 */
    if (VOS_TRUE == pstBgSearchCfg->stNonFirstHplmnTimerPeriod.ucNvimActiveFlg)
    {
        if (VOS_TRUE != NAS_MMC_GetFirstStartHPlmnTimerFlg())
        {
            /* 非首次启动，从NV: en_NV_Item_SearchHplmnTtimerValue中获取，无论USIM文件中
               的取值或NV: en_NV_Item_Default_Max_Hplmn_Srch_Peri中取的值是否生效 */
            ulHplmnTimerLen = pstBgSearchCfg->stNonFirstHplmnTimerPeriod.ulNonFirstHplmnTimerLen;

            NAS_NORMAL_LOG1(WUEPS_PID_MMC, "NAS_MMC_GetHplmnTimerLen:nvim ulNonFirstHplmnTimerLen is",ulHplmnTimerLen);
        }
    }

    return ulHplmnTimerLen;
}





/*****************************************************************************
 函 数 名  : NAS_MMC_GetCacheNum
 功能描述  : 获取当前存在的缓存个数
 输入参数  : 无
 输出参数  : 当前存在的缓存个数
 返 回 值  :
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2011年9月29日
    作    者   : zhoujun 40661
    修改内容   : 新生成函数

*****************************************************************************/
VOS_UINT32  NAS_MMC_GetCacheNum( VOS_VOID )
{
    NAS_MMC_MSG_QUEUE_STRU             *pstMsgQueue = VOS_NULL_PTR;

    pstMsgQueue                         = NAS_MMC_GetCachMsgBufferAddr();

    return pstMsgQueue->ucCacheMsgNum;
}


/*****************************************************************************
 函 数 名  : NAS_MMC_SetFsmStackPopFlg
 功能描述  : 设置状态机栈pop标志
 输入参数  : ucStachPopFlg:栈pop标志
 输出参数  : 无
 返 回 值  :
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2011年10月6日
    作    者   : zhoujun 40661
    修改内容   : 新生成函数

*****************************************************************************/
VOS_VOID  NAS_MMC_SetFsmStackPopFlg(
    VOS_UINT16                          ucStachPopFlg
)
{
    NAS_MMC_FSM_STACK_STRU             *pstFsmStack = VOS_NULL_PTR;

    pstFsmStack = NAS_MMC_GetFsmStackAddr();

    pstFsmStack->usStackPopFlg  = ucStachPopFlg;
}

/*****************************************************************************
 函 数 名  : NAS_MMC_GetFsmStackPopFlg
 功能描述  : 获取状态机栈pop标志
 输入参数  : 无
 输出参数  : 无
 返 回 值  :
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2011年10月6日
    作    者   : zhoujun 40661
    修改内容   : 新生成函数

*****************************************************************************/
VOS_UINT16  NAS_MMC_GetFsmStackPopFlg( VOS_VOID )
{
    NAS_MMC_FSM_STACK_STRU             *pstFsmStack = VOS_NULL_PTR;

    pstFsmStack = NAS_MMC_GetFsmStackAddr();

    return pstFsmStack->usStackPopFlg;
}


/*****************************************************************************
 函 数 名  : NAS_MMC_IsFsmEntryEventType
 功能描述  : 判断消息是否是状态机入口消息
 输入参数  :
 输出参数  : 无
 返 回 值  :
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2011年9月27日
    作    者   : zhoujun 40661
    修改内容   : 新生成函数

*****************************************************************************/
VOS_UINT32 NAS_MMC_IsFsmEntryEventType(
    VOS_UINT32                          ulEventType
)
{
    VOS_UINT32                          i;

    for ( i = 0 ; i < (sizeof(g_aulFsmEntryEventType) / sizeof(VOS_UINT32)) ; i++ )
    {
        if ( ulEventType == g_aulFsmEntryEventType[i] )
        {
            return VOS_TRUE;
        }
    }

    return VOS_FALSE;
}


/*****************************************************************************
 函 数 名  : NAS_MMC_GetBufferedPlmnSearchFlg
 功能描述  : 取得当前是否有缓存的标志
 输入参数  : 无
 输出参数  : 无
 返 回 值  : 取得当前是否有缓存的标志，如available timer定时器超时导致的搜网
 调用函数  :
 被调函数  :

 修改历史      :
 1.日    期   : 2011年10月12日
   作    者   : zhoujun 40661
   修改内容   : 新生成函数

 2.日    期   : 2011年11月17日
   作    者   : w00167002
   修改内容   : 更改函数名

*****************************************************************************/
VOS_UINT32  NAS_MMC_GetBufferedPlmnSearchFlg( VOS_VOID )
{

    return g_stNasMmcCtx.stPlmnSearchCtrl.stBufferedPlmnSearchInfo.ulPlmnSearchFlg;
}

/*****************************************************************************
 函 数 名  : NAS_MMC_GetBufferedPlmnSearchFlg
 功能描述  : 取得当前缓存的搜网场景
 输入参数  : 无
 输出参数  : 无
 返 回 值  : 取得当前缓存的搜网场景
 调用函数  :
 被调函数  :

 修改历史      :
 1.日    期   : 2011年11月17日
   作    者   : w00167002
   修改内容   : 新增函数

*****************************************************************************/
NAS_MMC_PLMN_SEARCH_SCENE_ENUM_UINT32  NAS_MMC_GetBufferedPlmnSearchScene( VOS_VOID )
{

    return g_stNasMmcCtx.stPlmnSearchCtrl.stBufferedPlmnSearchInfo.enPlmnSearchScene;
}


/*****************************************************************************
 函 数 名  : NAS_MMC_SetBufferedPlmnSearchInfo
 功能描述  : 设置缓存的搜网信息
 输入参数  : ulPlmnSearchFlg:   搜网标志
              enPlmnSearchScene: 搜网场景
 输出参数  : 无
 返 回 值  : VOS_VOID
 调用函数  :
 被调函数  :

 修改历史     :
 1.日    期   : 2011年10月12日
   作    者   : z40661
   修改内容   : 新生成函数

 2.日    期   : 2011年11月17日
   作    者   : w00167002
   修改内容   : 更改函数名

*****************************************************************************/
VOS_VOID NAS_MMC_SetBufferedPlmnSearchInfo(
    VOS_UINT32                                              ulPlmnSearchFlg,
    NAS_MMC_PLMN_SEARCH_SCENE_ENUM_UINT32                   enPlmnSearchScene
)
{
    g_stNasMmcCtx.stPlmnSearchCtrl.stBufferedPlmnSearchInfo.ulPlmnSearchFlg   = ulPlmnSearchFlg;
    g_stNasMmcCtx.stPlmnSearchCtrl.stBufferedPlmnSearchInfo.enPlmnSearchScene = enPlmnSearchScene;
}


/*****************************************************************************
 函 数 名  : NAS_MMC_GetSrvStaChngInfo
 功能描述  : 设置缓存的搜网信息
 输入参数  : ulPlmnSearchFlg:   搜网标志
              enPlmnSearchScene: 搜网场景
 输出参数  : 无
 返 回 值  : VOS_VOID
 调用函数  :
 被调函数  :

 修改历史     :
 1.日    期   : 2011年10月12日
   作    者   : z40661
   修改内容   : 新生成函数

 2.日    期   : 2011年11月17日
   作    者   : w00167002
   修改内容   : 更改函数名

*****************************************************************************/
NAS_MMC_SRV_STA_CHNG_INFO_STRU* NAS_MMC_GetSrvStaChngInfo( VOS_VOID )
{
    return &g_stNasMmcCtx.stPlmnSearchCtrl.stLastSrvStaInfo;
}

/*****************************************************************************
 函 数 名  : NAS_MMC_GetLastPlmnid
 功能描述  : 设置丢网时的PLMN ID信息
 输入参数  :
 输出参数  : 无
 返 回 值  : VOS_VOID
 调用函数  :
 被调函数  :

 修改历史     :
 1.日    期   : 2014年02月18日
   作    者   : t00173447
   修改内容   : 新生成函数
 2.日    期   : 2015年09月09日
   作    者   : c00318887
   修改内容   : 增加接入技术

*****************************************************************************/
NAS_MML_PLMN_ID_STRU* NAS_MMC_GetLastCampedPlmnid( VOS_VOID )
{
    return &g_stNasMmcCtx.stPlmnSearchCtrl.stLastCampedPlmnId.stPlmnId;
}


/* Added by c00318887 for 预置频点搜网优化, 2015-9-10, begin */
/*****************************************************************************
 函 数 名  : NAS_MMC_GetLastCampedPlmnRat
 功能描述  : 获取最后驻留的PLMN 接入技术
 输入参数  :
 输出参数  : 无
 返 回 值  : NAS_MML_NET_RAT_TYPE_ENUM_UINT8
 调用函数  :
 被调函数  :

 修改历史     :
 1.日    期   : 2015年09月09日
   作    者   : c00318887
   修改内容   : 预置频点搜网优化

*****************************************************************************/
NAS_MML_NET_RAT_TYPE_ENUM_UINT8 NAS_MMC_GetLastCampedPlmnRat( VOS_VOID )
{
    return g_stNasMmcCtx.stPlmnSearchCtrl.stLastCampedPlmnId.enRat;
}

/*****************************************************************************
 函 数 名  : NAS_MMC_SetLastCampedPlmnRat
 功能描述  : 设置最后驻留的PLMN 接入技术
 输入参数  :
 输出参数  : 无
 返 回 值  : NAS_MML_NET_RAT_TYPE_ENUM_UINT8
 调用函数  :
 被调函数  :

 修改历史     :
 1.日    期   : 2015年09月09日
   作    者   : c00318887
   修改内容   : 预置频点搜网优化

*****************************************************************************/
VOS_VOID NAS_MMC_SetLastCampedPlmnRat(NAS_MML_NET_RAT_TYPE_ENUM_UINT8 enRat)
{
    g_stNasMmcCtx.stPlmnSearchCtrl.stLastCampedPlmnId.enRat = enRat;
}

/* Added by c00318887 for 预置频点搜网优化, 2015-9-10, end */
/*****************************************************************************
 函 数 名  : NAS_MMC_SaveLastCampedPlmnWithRat
 功能描述  : 存储上次驻留网络的PLMNID
 输入参数  : 无
 输出参数  : 无
 返 回 值  : 无
 调用函数  :
 被调函数  :
 修改历史      :
 1.日    期   : 2014年02月25日
   作    者   : t00173447
   修改内容   : 新生成函数
 2.日    期   : 2015年09月09日
   作    者   : c00318887
   修改内容   : 增加接入技术
*****************************************************************************/
/* Modified by c00318887 for 预置频点搜网优化, 2015-9-9, begin */
VOS_VOID NAS_MMC_SaveLastCampedPlmnWithRat(
    VOS_UINT32                          ulMcc,
    VOS_UINT32                          ulMnc,
    NAS_MML_NET_RAT_TYPE_ENUM_UINT8     enRat
)
{
    NAS_MML_PLMN_ID_STRU             *pstLastPlmnid;

    pstLastPlmnid = NAS_MMC_GetLastCampedPlmnid();

    pstLastPlmnid->ulMcc = ulMcc;
    pstLastPlmnid->ulMnc = ulMnc;

    /* Added by c00318887 for 预置频点搜网优化, 2015-9-10, begin */
    NAS_MMC_SetLastCampedPlmnRat(enRat);
    /* Added by c00318887 for 预置频点搜网优化, 2015-9-10, end */

    return;
}
/* Modified by c00318887 for 预置频点搜网优化, 2015-9-9, end */




/*****************************************************************************
 函 数 名  : NAS_MMC_IsFsmIdInFsmStack
 功能描述  : 判断FSM ID是否在状态机栈数组中
 输入参数  : 无
 输出参数  : 无
 返 回 值  : VOS_TRUE - FSM ID在状态机栈数组中
             VOS_FALSE- FSM ID不在状态机栈数组中
 调用函数  :
 被调函数  :

 修改历史      :
 1.日    期   : 2011年12月7日
   作    者   : z00161729
   修改内容   : 新生成函数

*****************************************************************************/
VOS_UINT32  NAS_MMC_IsFsmIdInFsmStack(
    NAS_MMC_FSM_ID_ENUM_UINT32          enFsmId
)
{
    VOS_UINT32                          i;
    NAS_MMC_FSM_STACK_STRU             *pstFsmStack;

    pstFsmStack = NAS_MMC_GetFsmStackAddr();

    for (i = 0; i < pstFsmStack->usStackDepth; i++)
    {
        if (enFsmId == pstFsmStack->astFsmStack[i].enFsmId)
        {
            return VOS_TRUE;
        }
    }

    return VOS_FALSE;
}


/*****************************************************************************
 函 数 名  : NAS_MMC_NeedTrigPlmnSrch_UserSpecCurrentPlmn
 功能描述  : 用户指定搜索当前网络时，是否需要触发Plmn搜网
 输入参数  : 无
 输出参数  : 无
 返 回 值  : VOS_TRUE:正常服务
              VOS_FALSE:不是正常服务
 调用函数  :
 被调函数  :
 修改历史      :
 1.日    期   : 2012年6月6日
   作    者   : l00130025
   修改内容   : DTS2012060604313:单个域注册成功，用户发起对该网络的指定搜网时需要发起搜网注册
*****************************************************************************/
VOS_UINT32 NAS_MMC_NeedTrigPlmnSrch_UserSpecCurrentPlmn(VOS_VOID)
{
    NAS_MML_SIM_STATUS_STRU            *pstSimStatus    = VOS_NULL_PTR;
    NAS_MMC_SERVICE_ENUM_UINT8          enCsCurrService;
    NAS_MMC_SERVICE_ENUM_UINT8          enPsCurrService;


    pstSimStatus     = NAS_MML_GetSimStatus();
    enCsCurrService  = NAS_MMC_GetCsServiceStatus();
    enPsCurrService  = NAS_MMC_GetPsServiceStatus();

    /* 用户指定当前驻留Plmn,CS/PS同时都为正常服务时，不需要触发搜网 */
    if (( NAS_MMC_NORMAL_SERVICE == enCsCurrService)
     && ( NAS_MMC_NORMAL_SERVICE == enPsCurrService))
    {
        return VOS_FALSE;
    }

    /* 用户指定当前驻留Plmn,CS正常服务,PS不允许注册或PS卡无效时，不需要触发搜网 */
    if ((( VOS_FALSE == NAS_MML_GetPsAttachAllowFlg())
        ||( VOS_FALSE == pstSimStatus->ucSimPsRegStatus))
      &&(NAS_MMC_NORMAL_SERVICE == enCsCurrService))
    {
        return VOS_FALSE;
    }

    /* 用户指定当前驻留Plmn,PS正常服务,CS不允许注册或CS卡无效时，不需要触发搜网 */
    if (( (VOS_FALSE == NAS_MML_GetCsAttachAllowFlg())
        ||( VOS_FALSE == pstSimStatus->ucSimCsRegStatus))
      &&(NAS_MMC_NORMAL_SERVICE == enPsCurrService))
    {
        return VOS_FALSE;
    }

    /* 其他情况下，需要发起搜网 */
    return VOS_TRUE;

}






/*****************************************************************************
 函 数 名  : NAS_MMC_GetWaitWasPlmnSrchCnfTimerLen
 功能描述  : 获取等待WAS的搜网回复的定时器时长
 输入参数  : 无
 输出参数  : 无
 返 回 值  : 等待WAS的搜网回复的定时器时长
 调用函数  :
 被调函数  :
 修改历史      :
 1.日    期   : 2012年12月27日
   作    者   : s00217060
   修改内容   : for DSDA GUNAS C CORE:根据平台接入技术能力返回等待WAS的搜网回复的定时器时长
*****************************************************************************/
VOS_UINT32 NAS_MMC_GetWaitWasPlmnSrchCnfTimerLen(VOS_VOID)
{
#if (FEATURE_ON == FEATURE_UE_MODE_TDS)
    VOS_UINT32                          ulSupportFddFlg;
    VOS_UINT32                          ulSupportTddFlg;

    ulSupportTddFlg = NAS_MML_IsPlatformSupportUtranTdd();
    ulSupportFddFlg = NAS_MML_IsPlatformSupportUtranFdd();

    /* 如果同时支持FDD和TDD，定时器时长为301s */
    if ( (VOS_TRUE == ulSupportFddFlg)
      && (VOS_TRUE == ulSupportTddFlg) )
    {
        return TI_NAS_MMC_WAIT_UTRAN_PLMN_SEARCH_CNF_LEN;
    }

    /* 如果只支持FDD和TDD中的一个，定时器时长为150s */
    if (ulSupportFddFlg != ulSupportTddFlg)
    {
        return TI_NAS_MMC_WAIT_WAS_PLMN_SEARCH_CNF_LEN;
    }
#endif

    return TI_NAS_MMC_WAIT_WAS_PLMN_SEARCH_CNF_LEN;

}







/* Deleted by w00167002 for L-C互操作项目, 2014-4-16, begin */
/* Deleted by w00167002 for L-C互操作项目, 2014-4-16, end */




/*****************************************************************************
 函 数 名  : NAS_MMC_SetSrvTrigPlmnSearchFlag_PlmnSelection
 功能描述  : 设置是否存在业务触发搜网标识
 输入参数  : ucSrvTriggerPlmnSearchFlag - 业务触发搜网标识
 输出参数  : 无
 返 回 值  : 无
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2014年6月30日
    作    者   : z00161729
    修改内容   : 新生成函数
*****************************************************************************/
VOS_VOID  NAS_MMC_SetSrvTrigPlmnSearchFlag_PlmnSelection(
    VOS_UINT8                           ucSrvTriggerPlmnSearchFlag
)
{
    /* 如果当前状态机不是PLMN SELECTION */
    if (NAS_MMC_FSM_PLMN_SELECTION != NAS_MMC_GetCurrFsmId())
    {
        NAS_ERROR_LOG(WUEPS_PID_MMC, "NAS_MMC_SetSrvTrigPlmnSearchFlag_PlmnSelection,ERROR:FsmId Error");
    }

    g_stNasMmcCtx.stCurFsm.unFsmCtx.stPlmnSelectionCtx.ucSrvTrigPlmnSearchFlag = ucSrvTriggerPlmnSearchFlag;
    return;
}

/*****************************************************************************
 函 数 名  : NAS_MMC_GetSrvTrigPlmnSearchFlag_PlmnSelection
 功能描述  : 获取是否存在业务触发搜网标识
 输入参数  : 无
 输出参数  : 无
 返 回 值  : 业务触发搜网标识
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2014年6月30日
    作    者   : z00161729
    修改内容   : 新生成函数
*****************************************************************************/
VOS_UINT8 NAS_MMC_GetSrvTrigPlmnSearchFlag_PlmnSelection(VOS_VOID)
{
    /* 如果当前状态机不是PLMN SELECTION */
    if (NAS_MMC_FSM_PLMN_SELECTION != NAS_MMC_GetCurrFsmId())
    {
        NAS_ERROR_LOG(WUEPS_PID_MMC, "NAS_MMC_GetSrvTrigPlmnSearchFlag_PlmnSelection,ERROR:FsmId Error");
    }

    return g_stNasMmcCtx.stCurFsm.unFsmCtx.stPlmnSelectionCtx.ucSrvTrigPlmnSearchFlag;
}

/*****************************************************************************
 函 数 名  : NAS_MMC_GetHighPrioRatHplmnTimerLen
 功能描述  : 获取高优先级接入技术的HPLMN定时器的时长
 输入参数  : 无
 输出参数  : 无
 返 回 值  : 当前定时器的时长，单位毫秒
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2014年2月19日
    作    者   : w00176964
    修改内容   : 新生成函数

*****************************************************************************/
VOS_UINT32  NAS_MMC_GetHighPrioRatHplmnTimerLen( VOS_VOID )
{
    NAS_MML_HIGH_PRIO_RAT_HPLMN_TIMER_CFG_STRU             *pstHighRatHplmnTimerCfg = VOS_NULL_PTR;
    VOS_UINT32                                              ulHplmnTimerLen;
    VOS_UINT32                                              ulCount;

    pstHighRatHplmnTimerCfg = NAS_MML_GetHighPrioRatHplmnTimerCfg();
    ulCount                 = NAS_MMC_GetCurHighPrioRatHplmnTimerFirstSearchCount_L1Main();

    if (ulCount < pstHighRatHplmnTimerCfg->ulFirstSearchTimeCount)
    {
        ulHplmnTimerLen = pstHighRatHplmnTimerCfg->ulFirstSearchTimeLen * NAS_MML_ONE_THOUSAND_MILLISECOND;/* 需要转换为毫秒 */
    }
    else
    {
        ulHplmnTimerLen = pstHighRatHplmnTimerCfg->ulNonFirstSearchTimeLen * NAS_MML_ONE_THOUSAND_MILLISECOND;/* 需要转换为毫秒 */
    }

    return ulHplmnTimerLen;
}

/*****************************************************************************
 函 数 名  : NAS_MMC_GetHighPrioRatHplmnTimerRetryLen
 功能描述  : 获取高优先级接入技术的HPLMN定时器的重试时长
 输入参数  : 无
 输出参数  : 无
 返 回 值  : 当前定时器的重试时长，单位毫秒
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2014年2月19日
    作    者   : w00176964
    修改内容   : 新生成函数

*****************************************************************************/
VOS_UINT32  NAS_MMC_GetHighPrioRatHplmnTimerRetryLen( VOS_VOID )
{
    NAS_MML_HIGH_PRIO_RAT_HPLMN_TIMER_CFG_STRU             *pstHighRatHplmnTimerCfg = VOS_NULL_PTR;

    pstHighRatHplmnTimerCfg = NAS_MML_GetHighPrioRatHplmnTimerCfg();

    return pstHighRatHplmnTimerCfg->ulRetrySearchTimeLen * NAS_MML_ONE_THOUSAND_MILLISECOND;/* 需要转换为毫秒 */
}


/*****************************************************************************
 函 数 名  : NAS_MMC_GetCurHighPrioRatHplmnTimerFirstSearchCount_L1Main
 功能描述  : 获取当前高优先级接入技术的HPLMN定时器首次搜索次数
 输入参数  : 无
 输出参数  : 无
 返 回 值  : 当前高优先级接入技术的HPLMN定时器首次搜索次数
 调用函数  :
 被调函数  :

 修改历史     :
 1.日    期   : 2014年2月22日
   作    者   : w00176964
   修改内容   : 新生成函数
*****************************************************************************/
VOS_UINT32  NAS_MMC_GetCurHighPrioRatHplmnTimerFirstSearchCount_L1Main(VOS_VOID)
{
    /* 如果当前状态机不是L1 MAIN */
    if (NAS_MMC_FSM_L1_MAIN != NAS_MMC_GetCurrFsmId())
    {
        NAS_ERROR_LOG(WUEPS_PID_MMC, "NAS_MMC_GetCurHighPrioRatHplmnTimerFirstSearchCount_L1Main,ERROR:FsmId Error");
    }

    return g_stNasMmcCtx.stCurFsm.unFsmCtx.stL1MainCtx.ulCurHighRatHplmnTimerCount;
}

/*****************************************************************************
 函 数 名  : NAS_MMC_ResetCurHighPrioRatHplmnTimerFirstSearchCount_L1Main
 功能描述  : Reset高优先级接入技术的HPLMN定时器首次搜索次数
 输入参数  : 无
 输出参数  : 无
 返 回 值  : VOS_VOID
 调用函数  :
 被调函数  :

 修改历史     :
 1.日    期   : 2014年2月22日
   作    者   : w00176964
   修改内容   : 新生成函数
*****************************************************************************/
VOS_VOID    NAS_MMC_ResetCurHighPrioRatHplmnTimerFirstSearchCount_L1Main(VOS_VOID)
{
    /* 如果当前状态机不是L1 MAIN */
    if (NAS_MMC_FSM_L1_MAIN != NAS_MMC_GetCurrFsmId())
    {
        NAS_ERROR_LOG(WUEPS_PID_MMC, "NAS_MMC_ResetCurHighPrioRatHplmnTimerFirstSearchCount_L1Main,ERROR:FsmId Error");

        return;
    }

    g_stNasMmcCtx.stCurFsm.unFsmCtx.stL1MainCtx.ulCurHighRatHplmnTimerCount= 0;
}

/*****************************************************************************
 函 数 名  : NAS_MMC_AddCurHighPrioRatHplmnTimerFirstSearchCount_L1Main
 功能描述  : 递增高优先级接入技术的HPLMN定时器首次搜索次数
 输入参数  : 无
 输出参数  : 无
 返 回 值  : VOS_UINT32
 调用函数  :
 被调函数  :

 修改历史     :
 1.日    期   : 2014年2月22日
   作    者   : w00176964
   修改内容   : 新生成函数
*****************************************************************************/
VOS_VOID    NAS_MMC_AddCurHighPrioRatHplmnTimerFirstSearchCount_L1Main(VOS_VOID)
{
    /* 如果当前状态机不是L1 MAIN */
    if (NAS_MMC_FSM_L1_MAIN != NAS_MMC_GetCurrFsmId())
    {
        NAS_ERROR_LOG(WUEPS_PID_MMC, "NAS_MMC_AddCurHighPrioRatHplmnTimerFirstSearchCount_L1Main,ERROR:FsmId Error");

        return;
    }

    g_stNasMmcCtx.stCurFsm.unFsmCtx.stL1MainCtx.ulCurHighRatHplmnTimerCount++;
}



/*****************************************************************************
 函 数 名  : NAS_MMC_UpdateEhplmnToDplmnNplmnCfgInfo
 功能描述  : AP没有预置DPLMN信息时，将UE全局变量中的Ehplmn更新到DplmnNplmnCfg
             全局变量以及NV中
 输出参数  : 无
 返 回 值  : VOS_VOID
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2015年10月22日
    作    者   : l00289540
    修改内容   : 新生成函数

*****************************************************************************/
VOS_VOID NAS_MMC_UpdateEhplmnToDplmnNplmnCfgInfo(VOS_VOID)
{
    NAS_MMC_DPLMN_NPLMN_CFG_INFO_STRU                      *pstDPlmnNPlmnCfgInfo = VOS_NULL_PTR;
    NAS_MML_SIM_EHPLMN_INFO_STRU                           *pstSimEhplmnInfo     = VOS_NULL_PTR;
    VOS_UINT8                                              *pucImsi              = VOS_NULL_PTR;
    NAS_MML_PLMN_ID_STRU                                    stHPlmn;
    VOS_UINT8                                               i,j;

    pucImsi = NAS_MML_GetSimImsi();

    /* 从当前的IMSI中取出home plmn */
    stHPlmn                   = NAS_MML_GetImsiHomePlmn(pucImsi);
    pstDPlmnNPlmnCfgInfo      = NAS_MMC_GetDPlmnNPlmnCfgInfo();
    pstSimEhplmnInfo          = NAS_MML_GetSimEhplmnList();

    j = 0;
    pstDPlmnNPlmnCfgInfo->astEHplmnList[j++] = stHPlmn;
    pstDPlmnNPlmnCfgInfo->ucEHplmnNum = j;

    for (i = 0; i < pstSimEhplmnInfo->ucEhPlmnNum; i++)
    {
        if (VOS_TRUE == NAS_MML_IsBcchPlmnIdInDestSimPlmnList(&(pstSimEhplmnInfo->astEhPlmnInfo[i].stPlmnId),
                                                              pstDPlmnNPlmnCfgInfo->ucEHplmnNum,
                                                              pstDPlmnNPlmnCfgInfo->astEHplmnList))
        {
            continue;
        }

        pstDPlmnNPlmnCfgInfo->astEHplmnList[j++] = pstSimEhplmnInfo->astEhPlmnInfo[i].stPlmnId;

        if (j >= NAS_MMC_MAX_CFG_HPLMN_NUM)
        {
            break;
        }
    }

    pstDPlmnNPlmnCfgInfo->ucEHplmnNum = j;

}

/*****************************************************************************
 函 数 名  : NAS_MMC_GetDPlmnNPlmnCfgInfo
 功能描述  : 获取NV项中DPLMN NPLMN 列表
 输入参数  : 无
 输出参数  : 无
 返 回 值  : NV项中DPLMN NPLMN 列表
 调用函数  :
 被调函数  :

 修改历史      :
 1.日    期   : 2014年7月14日
   作    者   : c00188733
   修改内容   : 新生成函数

  2.日    期   : 2015年11月2日
    作    者   : l00289540
    修改内容   : ROAM_PLMN_SELECTION_OPTIMIZE_3.0 修改
*****************************************************************************/
NAS_MMC_DPLMN_NPLMN_CFG_INFO_STRU* NAS_MMC_GetDPlmnNPlmnCfgInfo( VOS_VOID )
{
    return &(NAS_MMC_GetMmcCtxAddr()->stPlmnSearchCtrl.stDplmnNplmnCtx.stDplmnNplmnInfo);
}

/*****************************************************************************
 函 数 名  : NAS_MMC_GetDPlmnNPlmnCfgInfo
 功能描述  : 获取存储DPLMN/NPLMN相关信息的上下文
 输入参数  : 无
 输出参数  : 无
 返 回 值  : 指向存储DPLMN/NPLMN相关信息的上下文的指针
 调用函数  :
 被调函数  :

 修改历史      :
 1.日    期   : 2015年11月02日
   作    者   : l00289540
   修改内容   : 新生成函数
*****************************************************************************/
NAS_MMC_DPLMN_NPLMN_CFG_CTX_STRU* NAS_MMC_GetDPlmnNPlmnCfgCtx( VOS_VOID )
{
    return &(NAS_MMC_GetMmcCtxAddr()->stPlmnSearchCtrl.stDplmnNplmnCtx);
}

/*****************************************************************************
 函 数 名  : NAS_MMC_InitUserDPlmnNPlmnInfo
 功能描述  : 初始化MMC_CTX中dplmn和nplmn信息
 输入参数  : pstUserDPlmnNPlmnInfo - dplmn和nplmn信息
 输出参数  : 无
 返 回 值  : 无
 调用函数  :
 被调函数  :

 修改历史      :
 1.日    期   : 2014年7月14日
   作    者   : c00188733
   修改内容   : 新生成函数

 2.日    期   : 2015年10月21日
   作    者   : l00289540
   修改内容   : ROAM_PLMN_SELECTION_OPTIMIZE_3.0 修改
*****************************************************************************/
VOS_VOID  NAS_MMC_InitUserDPlmnNPlmnInfo(
    NAS_MMC_DPLMN_NPLMN_CFG_CTX_STRU                      *pstDPlmnNPlmnCfgCtx
)
{
    NAS_MMC_DPLMN_NPLMN_CFG_INFO_STRU                      *pstDPlmnNPlmnCfgInfo;

    VOS_UINT32                                              i;

    if (VOS_TRUE != pstDPlmnNPlmnCfgCtx->ucDplmnSetFlg)
    {
        pstDPlmnNPlmnCfgCtx->ucDplmnSetFlg = VOS_FALSE;
    }

    pstDPlmnNPlmnCfgInfo                                    = &(pstDPlmnNPlmnCfgCtx->stDplmnNplmnInfo);
    pstDPlmnNPlmnCfgInfo->ucEHplmnNum                       = 0;
    pstDPlmnNPlmnCfgInfo->usDplmnListNum                    = 0;
    pstDPlmnNPlmnCfgInfo->usNplmnListNum                    = 0;
    pstDPlmnNPlmnCfgInfo->usPresetDplmnNum                  = 0;

    PS_MEM_SET(pstDPlmnNPlmnCfgInfo->aucVersionId, 0x00, NAS_MCC_INFO_VERSION_LEN*sizeof(VOS_UINT8));

    for ( i = 0 ; i < NAS_MMC_MAX_CFG_HPLMN_NUM; i++ )
    {
        pstDPlmnNPlmnCfgInfo->astEHplmnList[i].ulMcc   = NAS_MML_INVALID_MCC;
        pstDPlmnNPlmnCfgInfo->astEHplmnList[i].ulMnc   = NAS_MML_INVALID_MNC;
    }

    for ( i = 0 ; i < NAS_MMC_MAX_CFG_DPLMN_NUM ; i++ )
    {
        pstDPlmnNPlmnCfgInfo->astDPlmnList[i].stSimPlmnWithRat.stPlmnId.ulMcc   = NAS_MML_INVALID_MCC;
        pstDPlmnNPlmnCfgInfo->astDPlmnList[i].stSimPlmnWithRat.stPlmnId.ulMnc   = NAS_MML_INVALID_MNC;
        pstDPlmnNPlmnCfgInfo->astDPlmnList[i].stSimPlmnWithRat.usSimRat         = NAS_MML_INVALID_SIM_RAT;
        pstDPlmnNPlmnCfgInfo->astDPlmnList[i].enRegDomain                       = NAS_MMC_REG_DOMAIN_NONE;
    }

    for ( i = 0 ; i < NAS_MMC_MAX_CFG_NPLMN_NUM ; i++ )
    {
        pstDPlmnNPlmnCfgInfo->astNPlmnList[i].stSimPlmnWithRat.stPlmnId.ulMcc   = NAS_MML_INVALID_MCC;
        pstDPlmnNPlmnCfgInfo->astNPlmnList[i].stSimPlmnWithRat.stPlmnId.ulMnc   = NAS_MML_INVALID_MNC;
        pstDPlmnNPlmnCfgInfo->astNPlmnList[i].stSimPlmnWithRat.usSimRat         = NAS_MML_INVALID_SIM_RAT;
        pstDPlmnNPlmnCfgInfo->astNPlmnList[i].enRegDomain                       = NAS_MMC_REG_DOMAIN_NONE;
    }

    return;
}


/*****************************************************************************
 函 数 名  : NAS_MMC_GetRoamPlmnSelectionSortActiveFlg
 功能描述  : 获取NV中漫游选网排序是否开启标志
 输入参数  : 无
 输出参数  : 无
 返 回 值  : VOS_TRUE: NV激活漫游选网排序
             VOS_FALSE:nv不激活漫游选网排序
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2015年6月2日
    作    者   : w00167002
    修改内容   : 新生成函数

*****************************************************************************/
VOS_UINT8 NAS_MMC_GetRoamPlmnSelectionSortActiveFlg( VOS_VOID )
{
    return (NAS_MMC_GetMmcCtxAddr()->stPlmnSearchCtrl.stRoamPlmnSeletionSortCfgInfo.ucRoamPlmnSelectionSortFlg);
}

/*****************************************************************************
 函 数 名  : NAS_MMC_SetRoamPlmnSelectionSortActiveFlg
 功能描述  : 设置NV中漫游选网排序是否开启标志
 输入参数  : ucRoamPlmnSelectionSortFlg
 输出参数  : 无
 返 回 值  : 无
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2015年6月2日
    作    者   : w00167002
    修改内容   : 新生成函数

*****************************************************************************/
VOS_VOID NAS_MMC_SetRoamPlmnSelectionSortActiveFlg(
    VOS_UINT8                           ucRoamPlmnSelectionSortFlg
)
{
    NAS_MMC_GetMmcCtxAddr()->stPlmnSearchCtrl.stRoamPlmnSeletionSortCfgInfo.ucRoamPlmnSelectionSortFlg = ucRoamPlmnSelectionSortFlg;
}


/*****************************************************************************
 函 数 名  : NAS_MMC_SetSrchUOplmnPriorToDplmnFlg
 功能描述  : 设置漫游搜网时是否在搜DPLMN之前先搜UOPLMN的标志
 输入参数  : ucSrchUOplmnPriorToDplmnFlg
 输出参数  : 无
 返 回 值  :
 调用函数  :
 被调函数  :

 修改历史     :
 1.日    期   : 2015年10月09日
   作    者   : l00289540
   修改内容   : 新生成函数
*****************************************************************************/
VOS_VOID NAS_MMC_SetSrchUOplmnPriorToDplmnFlg(
    VOS_UINT8 ucSrchUOplmnPriorToDplmnFlg
)
{
    NAS_MMC_GetMmcCtxAddr()->stPlmnSearchCtrl.stRoamPlmnSeletionSortCfgInfo.ucSrchUOplmnPriorToDplmnFlg = ucSrchUOplmnPriorToDplmnFlg;
    return;
}

/*****************************************************************************
 函 数 名  : NAS_MMC_GetSrchUOplmnPriorToDplmnFlg
 功能描述  : 获取漫游搜网时是否在搜DPLMN之前先搜UOPLMN的标志
 输入参数  : 无
 输出参数  : 无
 返 回 值  : VOS_TRUE:先搜UOPLMN,VOS_FALSE:先搜DPLMN
 调用函数  :
 被调函数  :

 修改历史     :
 1.日    期   : 2015年10月09日
   作    者   : l00289540
   修改内容   : 新生成函数
*****************************************************************************/
VOS_UINT8 NAS_MMC_GetSrchUOplmnPriorToDplmnFlg(VOS_VOID)
{
    if (VOS_TRUE == NAS_USIMMAPI_IsTestCard())
    {
        return VOS_FALSE;
    }

    return NAS_MMC_GetMmcCtxAddr()->stPlmnSearchCtrl.stRoamPlmnSeletionSortCfgInfo.ucSrchUOplmnPriorToDplmnFlg;
}


/*****************************************************************************
 函 数 名  : NAS_MMC_GetGeoPlmn
 功能描述  : 获取状态机上下文中的GeoPlmn
 输入参数  : 无
 输出参数  : 无
 返 回 值  : NAS_MML_PLMN_WITH_RAT_STRU:PLMN+RAT
 调用函数  :
 被调函数  :

 修改历史     :
 1.日    期   : 2015年05月22日
   作    者   : s00217060
   修改内容   : ROAM_PLMN_SELECTION_OPTIMIZE_2.0

*****************************************************************************/
NAS_MML_PLMN_WITH_RAT_STRU* NAS_MMC_GetGeoPlmn(VOS_VOID)
{
    return &(NAS_MMC_GetMmcCtxAddr()->stPlmnSearchCtrl.stGetGeoInfo.stGeoPlmn);
}

/*****************************************************************************
 函 数 名  : NAS_MMC_SetGeoPlmn
 功能描述  : 设置状态机上下文中的GeoPlmn
 输入参数  : NAS_MML_PLMN_WITH_RAT_STRU:PLMN+RAT
 输出参数  : 无
 返 回 值  : 无
 调用函数  :
 被调函数  :

 修改历史     :
  1.日    期   : 2015年5月22日
    作    者   : s00217060
    修改内容   : ROAM_PLMN_SELECTION_OPTIMIZE_2.0

*****************************************************************************/
VOS_VOID NAS_MMC_SetGeoPlmn(
    NAS_MML_PLMN_WITH_RAT_STRU         *pstGeoPlmn
)
{
    NAS_MMC_GetMmcCtxAddr()->stPlmnSearchCtrl.stGetGeoInfo.stGeoPlmn = *pstGeoPlmn;
    return;
}

/*****************************************************************************
 函 数 名  : NAS_MMC_GetNonOosPlmnSearchFeatureSupportCfg
 功能描述  : 获取NV项中history搜相关信息
 输入参数  : 无
 输出参数  : 无
 返 回 值  : NAS_MMC_NON_OOS_PLMN_SEARCH_FEATURE_SUPPORT_CFG_STRU:history搜相关信息
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2015年5月23日
    作    者   : s00217060
    修改内容   : 新生成函数

*****************************************************************************/
NAS_MMC_NON_OOS_PLMN_SEARCH_FEATURE_SUPPORT_CFG_STRU* NAS_MMC_GetNonOosPlmnSearchFeatureSupportCfg( VOS_VOID )
{
    return &(NAS_MMC_GetMmcCtxAddr()->stPlmnSearchCtrl.stNonOosPlmnSearchFeatureSupportCfg);
}


/*****************************************************************************
 函 数 名  : NAS_MMC_GetNonOosSceneHistorySearchActiveFlg
 功能描述  : 获取NV中history搜是否开启标志
 输入参数  : 无
 输出参数  : 无
 返 回 值  : VOS_TRUE: NV激活history搜索
             VOS_FALSE:nv不激活histrory搜索
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2015年5月29日
    作    者   : w00167002
    修改内容   : 新生成函数
  2.日    期   : 2015年10月26日
    作    者   : h00281185
    修改内容   : 修改成回傳 ucHistoryActiveFlg. 变更原有NV结构
*****************************************************************************/
VOS_UINT8 NAS_MMC_GetNonOosSceneHistorySearchActiveFlg( VOS_VOID )
{
    return (NAS_MMC_GetMmcCtxAddr()->stPlmnSearchCtrl.stNonOosPlmnSearchFeatureSupportCfg.ucHistoryActiveFlg);
}


/*****************************************************************************
 函 数 名  : NAS_MMC_GetPrefBandSearchInfo
 功能描述  : 获取NV项中搜网相关信息
 输入参数  : 无
 输出参数  : 无
 返 回 值  : NAS_MMC_OOS_PLMN_SEARCH_STRATEGY_INFO_STRU:搜网相关信息
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2015年10月10日
    作    者   : h00281185
    修改内容   : 新生成函数
*****************************************************************************/
NAS_MMC_OOS_PLMN_SEARCH_STRATEGY_INFO_STRU* NAS_MMC_GetOosPlmnSearchStrategyInfo( VOS_VOID )
{
    return &(NAS_MMC_GetMmcCtxAddr()->stPlmnSearchCtrl.stOosPlmnSearchStrategyInfo);
}

/*****************************************************************************
 函 数 名  : NAS_MMC_GetPhaseOneOosPlmnSearchPatternInfo
 功能描述  : 获取第一阶段搜网定时器时资讯
 输入参数  : 无
 输出参数  : 无
 返 回 值  : NAS_MMC_OOS_PLMN_SEARCH_PATTERN_INFO_STRU:第一阶段搜网相关信息
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2015年10月10日
    作    者   : h00281185
    修改内容   : 新生成函数
*****************************************************************************/
NAS_MMC_OOS_PLMN_SEARCH_PATTERN_INFO_STRU* NAS_MMC_GetPhaseOneOosPlmnSearchPatternInfo( VOS_VOID )
{
    return &(NAS_MMC_GetMmcCtxAddr()->stPlmnSearchCtrl.stOosPlmnSearchStrategyInfo.stPhaseOnePatternCfg);
}

/*****************************************************************************
 函 数 名  : NAS_MMC_GetPhaseTwoOosPlmnSearchPatternInfo
 功能描述  : 获取第二阶段搜网定时器时资讯
 输入参数  : 无
 输出参数  : 无
 返 回 值  : NAS_MMC_OOS_PLMN_SEARCH_PATTERN_INFO_STRU:第二阶段搜网相关信息
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2015年10月10日
    作    者   : h00281185
    修改内容   : 新生成函数
*****************************************************************************/
NAS_MMC_OOS_PLMN_SEARCH_PATTERN_INFO_STRU* NAS_MMC_GetPhaseTwoOosPlmnSearchPatternInfo( VOS_VOID )
{
    return &(NAS_MMC_GetMmcCtxAddr()->stPlmnSearchCtrl.stOosPlmnSearchStrategyInfo.stPhaseTwoPatternCfg);
}

/*****************************************************************************
 函 数 名  : NAS_MMC_IsNeedGoToNextPhaseByHistory
 功能描述  : 藉由History Count决定OOS Phase是否进入下一阶段
 输入参数  : 无
 输出参数  : 无
 返 回 值  : VOS_UINT8

 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2015年10月30日
    作    者   : h00281185
    修改内容   : 新生成函数

*****************************************************************************/

VOS_UINT8 NAS_MMC_IsNeedGoToNextPhaseByHistory( VOS_VOID )
{
    NAS_MMC_OOS_PLMN_SEARCH_PATTERN_INFO_STRU              *pstPhaseOneOosPlmnSearchPatternInfo  = VOS_NULL_PTR;
    NAS_MMC_OOS_PLMN_SEARCH_PATTERN_INFO_STRU              *pstPhaseTwoOosPlmnSearchPatternInfo  = VOS_NULL_PTR;
    VOS_UINT32                                              ulCurHistoryCount       = 0;
    VOS_UINT8                                               ucTotalHistoryCount     = 0;
    VOS_UINT8                                               ucTotalPrefBandCount    = 0;
    VOS_UINT8                                               ucTotalFullBandCount    = 0;

    pstPhaseOneOosPlmnSearchPatternInfo         = NAS_MMC_GetPhaseOneOosPlmnSearchPatternInfo();
    pstPhaseTwoOosPlmnSearchPatternInfo         = NAS_MMC_GetPhaseTwoOosPlmnSearchPatternInfo();
    ulCurHistoryCount                           = NAS_MMC_GetCurHistorySearchTimerCount_OnPlmn();

    if (NAS_MMC_OOS_PHASE_ONE == NAS_MMC_GetOosPhaseNum())
    {
        /* 第一阶段 */
        ucTotalHistoryCount     = pstPhaseOneOosPlmnSearchPatternInfo->ucHistoryNum;
        ucTotalPrefBandCount    = pstPhaseOneOosPlmnSearchPatternInfo->ucPrefBandNum;
        ucTotalFullBandCount    = pstPhaseOneOosPlmnSearchPatternInfo->ucFullBandNum;
    }
    else
    {
         /* 第二阶段 */
        ucTotalHistoryCount     = pstPhaseTwoOosPlmnSearchPatternInfo->ucHistoryNum;
        ucTotalPrefBandCount    = pstPhaseTwoOosPlmnSearchPatternInfo->ucPrefBandNum;
        ucTotalFullBandCount    = pstPhaseTwoOosPlmnSearchPatternInfo->ucFullBandNum;
    }

    /* 若不是最後一阶段且history为最大定时器则进入下一阶段 */
    if((NAS_MMC_OOS_PHASE_MAX != NAS_MMC_GetOosPhaseNum())
     &&(0 == ucTotalPrefBandCount)
     &&(0 == ucTotalFullBandCount)
     &&((ulCurHistoryCount == ucTotalHistoryCount)))
    {
        return VOS_TRUE;

    }

    return VOS_FALSE;
}

/*****************************************************************************
 函 数 名  : NAS_MMC_IsNeedGoToNextPhaseByPrefBand
 功能描述  : 藉由PrefBand Count决定OOS Phase是否进入下一阶段
 输入参数  : 无
 输出参数  : 无
 返 回 值  : VOS_UINT8

 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2015年10月30日
    作    者   : h00281185
    修改内容   : 新生成函数

*****************************************************************************/

VOS_UINT8 NAS_MMC_IsNeedGoToNextPhaseByPrefBand( VOS_VOID )
{
    NAS_MMC_OOS_PLMN_SEARCH_PATTERN_INFO_STRU              *pstPhaseOneOosPlmnSearchPatternInfo  = VOS_NULL_PTR;
    NAS_MMC_OOS_PLMN_SEARCH_PATTERN_INFO_STRU              *pstPhaseTwoOosPlmnSearchPatternInfo  = VOS_NULL_PTR;
    VOS_UINT32                                              ulCurPrefBandCount;
    VOS_UINT8                                               ucTotalPrefBandCount = 0;
    VOS_UINT8                                               ucTotalFullBandCount = 0;


    pstPhaseOneOosPlmnSearchPatternInfo         = NAS_MMC_GetPhaseOneOosPlmnSearchPatternInfo();
    pstPhaseTwoOosPlmnSearchPatternInfo         = NAS_MMC_GetPhaseTwoOosPlmnSearchPatternInfo();
    ulCurPrefBandCount                          = NAS_MMC_GetCurPrefBandSearchTimerCount_OnPlmn();


    if (NAS_MMC_OOS_PHASE_ONE == NAS_MMC_GetOosPhaseNum())
    {
        /* 第一阶段 */
        ucTotalPrefBandCount = pstPhaseOneOosPlmnSearchPatternInfo->ucPrefBandNum;
        ucTotalFullBandCount = pstPhaseOneOosPlmnSearchPatternInfo->ucFullBandNum;
    }
    else
    {
        /* 第二阶段 */
        ucTotalPrefBandCount = pstPhaseTwoOosPlmnSearchPatternInfo->ucPrefBandNum;
        ucTotalFullBandCount = pstPhaseTwoOosPlmnSearchPatternInfo->ucFullBandNum;
    }

    /* 若不是最後一阶段且Prefband为最大定时器则进入下一阶段 */
    if((NAS_MMC_OOS_PHASE_MAX != NAS_MMC_GetOosPhaseNum())
     &&(0 == ucTotalFullBandCount)
     && (ulCurPrefBandCount == ucTotalPrefBandCount))
    {
        return VOS_TRUE;
    }

    return VOS_FALSE;

}

/*****************************************************************************
 函 数 名  : NAS_MMC_IsNeedGoToNextPhaseByFullBand
 功能描述  : 藉由PrefBand Count决定OOS Phase是否进入下一阶段
 输入参数  : 无
 输出参数  : 无
 返 回 值  : VOS_UINT8

 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2015年10月30日
    作    者   : h00281185
    修改内容   : 新生成函数

*****************************************************************************/
VOS_UINT8 NAS_MMC_IsNeedGoToNextPhaseByFullBand( VOS_VOID )
{
    NAS_MMC_OOS_PLMN_SEARCH_PATTERN_INFO_STRU              *pstPhaseOneOosPlmnSearchPatternInfo  = VOS_NULL_PTR;
    NAS_MMC_OOS_PLMN_SEARCH_PATTERN_INFO_STRU              *pstPhaseTwoOosPlmnSearchPatternInfo  = VOS_NULL_PTR;
    VOS_UINT32                                              ulCurFullBandCount;
    VOS_UINT8                                               ucTotalFullBandCount;


    pstPhaseOneOosPlmnSearchPatternInfo                    = NAS_MMC_GetPhaseOneOosPlmnSearchPatternInfo();
    pstPhaseTwoOosPlmnSearchPatternInfo                    = NAS_MMC_GetPhaseTwoOosPlmnSearchPatternInfo();


    if (NAS_MMC_OOS_PHASE_ONE == NAS_MMC_GetOosPhaseNum())
    {
        /* 第一阶段 */
        ucTotalFullBandCount = pstPhaseOneOosPlmnSearchPatternInfo->ucFullBandNum;
    }
    else
    {
         /* 第二阶段 */
        ucTotalFullBandCount = pstPhaseTwoOosPlmnSearchPatternInfo->ucFullBandNum;
    }

    ulCurFullBandCount          = NAS_MMC_GetCurNormalAvailableTimerCount_L1Main();

    /* 若Fullband到达设定执行次数且目前不是最後一阶段则进入下一阶段 */
    if ((NAS_MMC_OOS_PHASE_MAX != NAS_MMC_GetOosPhaseNum())
      &&(ulCurFullBandCount == ucTotalFullBandCount))
    {
        return VOS_TRUE;

    }

    return VOS_FALSE;

}

/*****************************************************************************
 函 数 名  : NAS_MMC_GetOosPhaseNum
 功能描述  : 获取目前是OOS中的第几阶段
 输入参数  : 无
 输出参数  : 无
 返 回 值  : VOS_UINT8:目前是OOS中的第几阶段

 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2015年11月05日
    作    者   : d00305650
    修改内容   : 新生成函数

*****************************************************************************/
NAS_MMC_OOS_PHASE_ENUM_UINT8 NAS_MMC_GetOosPhaseNum( VOS_VOID )
{

    return (NAS_MMC_GetMmcCtxAddr()->stPlmnSearchCtrl.stOosPlmnSearchStrategyInfo.enNextOosSearchPhaseNum);

}

/*****************************************************************************
 函 数 名  : NAS_MMC_ResetOosPhaseNum
 功能描述  : 重置OOS阶段
 输入参数  : VOS_VOID
 输出参数  : 无
 返 回 值  : VOS_VOID
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2015年11月05日
    作    者   : d00305650
    修改内容   : 新生成函数

*****************************************************************************/
VOS_VOID NAS_MMC_ResetOosPhaseNum(VOS_VOID)
{

    NAS_MMC_GetMmcCtxAddr()->stPlmnSearchCtrl.stOosPlmnSearchStrategyInfo.enNextOosSearchPhaseNum = NAS_MMC_OOS_PHASE_ONE;

    return;
}

/*****************************************************************************
 函 数 名  : NAS_MMC_AddOosPhaseNum
 功能描述  : 递增 OOS阶段
 输入参数  : 无
 输出参数  : 无
 返 回 值  : VOS_UINT32
 调用函数  :
 被调函数  :

 修改历史     :
  1.日    期   : 2015年11月05日
    作    者   : d00305650
    修改内容   : 新生成函数

*****************************************************************************/
VOS_VOID  NAS_MMC_AddOosPhaseNum(VOS_VOID)
{

    NAS_MMC_GetMmcCtxAddr()->stPlmnSearchCtrl.stOosPlmnSearchStrategyInfo.enNextOosSearchPhaseNum++;
    return;
}

/*****************************************************************************
 函 数 名  : NAS_MMC_SetCurrSearchPhaseNum
 功能描述  : 设置当前OOS搜网到了第几阶段
 输入参数  : NAS_MMC_OOS_PHASE_ENUM_UINT8    enCurrPhaseNum
 输出参数  : 无
 返 回 值  : VOS_VOID
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2015年11月6日
    作    者   : s00217060
    修改内容   : 新生成函数

*****************************************************************************/
VOS_VOID NAS_MMC_SetCurrOosSearchPhaseNum(
    NAS_MMC_OOS_PHASE_ENUM_UINT8        enCurrPhaseNum
)
{
    NAS_MMC_GetMmcCtxAddr()->stPlmnSearchCtrl.stOosPlmnSearchStrategyInfo.enCurrOosSearchPhaseNum = enCurrPhaseNum;
    return;
}

/*****************************************************************************
 函 数 名  : NAS_MMC_GetCurrOosSearchPhaseNum
 功能描述  : 获取目前搜网是OOS中的第几阶段
 输入参数  : 无
 输出参数  : 无
 返 回 值  : NAS_MMC_OOS_PHASE_ENUM_UINT8:目前是OOS中的第几阶段

 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2015年11月6日
    作    者   : s00217060
    修改内容   : 新生成函数

*****************************************************************************/
NAS_MMC_OOS_PHASE_ENUM_UINT8 NAS_MMC_GetCurrOosSearchPhaseNum( VOS_VOID )
{
    return (NAS_MMC_GetMmcCtxAddr()->stPlmnSearchCtrl.stOosPlmnSearchStrategyInfo.enCurrOosSearchPhaseNum);
}

/*****************************************************************************
 函 数 名  : NAS_MMC_InitOosSearchStrategyInfo
 功能描述  : 初始化history/PrefBand/FullBand搜相关信息
 输入参数  : NAS_MMC_OOS_PLMN_SEARCH_STRATEGY_INFO_STRU   *pstSearchTypeStrategyInfo
 输出参数  : 无
 返 回 值  : VOS_VOID
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2015年5月26日
    作    者   : s00217060
    修改内容   : 新生成函数

*****************************************************************************/
VOS_VOID NAS_MMC_InitOosSearchStrategyInfo(
    NAS_MMC_OOS_PLMN_SEARCH_STRATEGY_INFO_STRU                 *pstSearchTypeStrategyInfo
)
{
    pstSearchTypeStrategyInfo->stPhaseOnePatternCfg.usSleepTimerLen    = 0;
    pstSearchTypeStrategyInfo->stPhaseOnePatternCfg.ucHistoryNum       = 0;
    pstSearchTypeStrategyInfo->stPhaseOnePatternCfg.ucPrefBandNum      = 0;
    pstSearchTypeStrategyInfo->stPhaseOnePatternCfg.ucFullBandNum      = 0;
    pstSearchTypeStrategyInfo->stPhaseOnePatternCfg.usTotalTimerLen    = 0;

    pstSearchTypeStrategyInfo->stPhaseTwoPatternCfg.usSleepTimerLen    = 0;
    pstSearchTypeStrategyInfo->stPhaseTwoPatternCfg.ucHistoryNum       = 0;
    pstSearchTypeStrategyInfo->stPhaseTwoPatternCfg.ucPrefBandNum      = 0;
    pstSearchTypeStrategyInfo->stPhaseTwoPatternCfg.ucFullBandNum      = 0;
    pstSearchTypeStrategyInfo->stPhaseTwoPatternCfg.usTotalTimerLen    = 0;

    return;
}

/*****************************************************************************
 函 数 名  : NAS_MMC_GetPhaseOnePeriodicSleepTimerLen
 功能描述  : 获取第一阶段搜网定时器时资讯
 输入参数  : 无
 输出参数  : 无
 返 回 值  : ulPhaseOnePeriodicSleepTimerLen: "全频搜"间隔睡眠时长,
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2015年10月10日
    作    者   : h00281185
    修改内容   : 新生成函数
*****************************************************************************/
VOS_UINT32 NAS_MMC_GetPhaseOnePeriodicSleepTimerLen( VOS_VOID )
{
    NAS_MMC_OOS_PLMN_SEARCH_PATTERN_INFO_STRU              *pstPhaseOneOosPlmnSearchPatternInfo  = VOS_NULL_PTR;
    VOS_UINT32                                              ulPhaseOnePeriodicSleepTimerLen;

    pstPhaseOneOosPlmnSearchPatternInfo                     = NAS_MMC_GetPhaseOneOosPlmnSearchPatternInfo();
    ulPhaseOnePeriodicSleepTimerLen                         = 0;

    if (0 != pstPhaseOneOosPlmnSearchPatternInfo->ucFullBandNum)
    {
        /*
        sleep = FullBandlength = Len(H+1)(P+1)
        ex: F=1, P=0, H=2
        OOS:_H_H_F, Len => (2+1)(0+1) = 3
        ex: F=1, P=2, H=0
        OOS:_P_P_F, Len => (0+1)(2+1) = 3
        ex: F=1, P=2, H=1
        OOS:_H_P_H_P_H_F, Len => (1+1)(2+1) = 6
        */
        ulPhaseOnePeriodicSleepTimerLen =
          pstPhaseOneOosPlmnSearchPatternInfo->usSleepTimerLen * (pstPhaseOneOosPlmnSearchPatternInfo->ucHistoryNum + 1) * (pstPhaseOneOosPlmnSearchPatternInfo->ucPrefBandNum + 1);
    }
    else if (0 != pstPhaseOneOosPlmnSearchPatternInfo->ucPrefBandNum)
    {
        /*
        ex: F=0, P=2, H=0
        OOS:_P          , Len => (0+1) = 1
        ex: F=0, P=2, H=1
        OOS:_H_P        , Len => (1+1) = 2
        */
        ulPhaseOnePeriodicSleepTimerLen =
          pstPhaseOneOosPlmnSearchPatternInfo->usSleepTimerLen * (pstPhaseOneOosPlmnSearchPatternInfo->ucHistoryNum + 1);
    }
    else
    {
        /*
        ex: F=0, P=0, H=2
        OOS:_H, Len => Len
        */
        ulPhaseOnePeriodicSleepTimerLen =
          pstPhaseOneOosPlmnSearchPatternInfo->usSleepTimerLen;
    }
        /*
        ex: F=0, P=0, H=0 --> read NV 会回避, 变成 F=1, P=0, H=0
        */
    return ulPhaseOnePeriodicSleepTimerLen;
}

/*****************************************************************************
 函 数 名  : NAS_MMC_GetPhaseTwoPeriodicSleepTimerLen
 功能描述  : 获取第二阶段搜网定时器时资讯
 输入参数  : 无
 输出参数  : 无
 返 回 值  : ulFullBandSleepTimerLen: 全频搜间隔睡眠时长
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2015年10月10日
    作    者   : h00281185
    修改内容   : 新生成函数
*****************************************************************************/
VOS_UINT32 NAS_MMC_GetPhaseTwoPeriodicSleepTimerLen( VOS_VOID )
{
    NAS_MMC_OOS_PLMN_SEARCH_PATTERN_INFO_STRU              *pstPhaseTwoOosPlmnSearchPatternInfo  = VOS_NULL_PTR;
    VOS_UINT32                                              ulPhaseTwoPeriodicSleepTimerLen;

    pstPhaseTwoOosPlmnSearchPatternInfo                     = NAS_MMC_GetPhaseTwoOosPlmnSearchPatternInfo();
    ulPhaseTwoPeriodicSleepTimerLen                         = 0;

    if (0 != pstPhaseTwoOosPlmnSearchPatternInfo->ucFullBandNum)
    {
        /*
        sleep = FullBandlength = Len(H+1)(P+1)
        ex: F=1, P=0, H=2
        OOS:_H_H_F, Len => (2+1)(0+1) = 3
        ex: F=1, P=2, H=0
        OOS:_P_P_F, Len => (0+1)(2+1) = 3
        ex: F=1, P=2, H=1
        OOS:_H_P_H_P_H_F, Len => (1+1)(2+1) = 6
        */
        ulPhaseTwoPeriodicSleepTimerLen =
          pstPhaseTwoOosPlmnSearchPatternInfo->usSleepTimerLen * (pstPhaseTwoOosPlmnSearchPatternInfo->ucHistoryNum + 1) * (pstPhaseTwoOosPlmnSearchPatternInfo->ucPrefBandNum + 1);
    }
    else if (0 != pstPhaseTwoOosPlmnSearchPatternInfo->ucPrefBandNum)
    {
        /*
        ex: F=0, P=2, H=0
        OOS:_P          , Len => (0+1) = 1
        ex: F=0, P=2, H=1
        OOS:_H_P        , Len => (1+1) = 2
        */
        ulPhaseTwoPeriodicSleepTimerLen =
          pstPhaseTwoOosPlmnSearchPatternInfo->usSleepTimerLen * (pstPhaseTwoOosPlmnSearchPatternInfo->ucHistoryNum + 1);
    }
    else
    {
        /*
        ex: F=0, P=0, H=2
        OOS:_H, Len => Len
        */
        ulPhaseTwoPeriodicSleepTimerLen =
          pstPhaseTwoOosPlmnSearchPatternInfo->usSleepTimerLen;
    }
        /*
        ex: F=0, P=0, H=0 --> read NV 会回避, 变成 F=1, P=0, H=0
        */
    return ulPhaseTwoPeriodicSleepTimerLen;
}



/*****************************************************************************
 函 数 名  : NAS_MMC_InitNonOosPlmnSearchFeatureSupportCfg
 功能描述  : 初始化history搜相关信息
 输入参数  : NAS_MMC_NON_OOS_PLMN_SEARCH_FEATURE_SUPPORT_CFG_STRU   *pstHistoryInfo
 输出参数  : 无
 返 回 值  : VOS_VOID
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2015年5月26日
    作    者   : s00217060
    修改内容   : 新生成函数
  2.日    期   : 2015年10月26日
    作    者   : h00281185
    修改内容   : ROAM_PLMN_SELECTION_OPTIMIZE_3.0

*****************************************************************************/
VOS_VOID NAS_MMC_InitNonOosPlmnSearchFeatureSupportCfg(
    NAS_MMC_NON_OOS_PLMN_SEARCH_FEATURE_SUPPORT_CFG_STRU   *pstNonOosPlmnSearchFeatureSupportCfg
)
{
    PS_MEM_SET(pstNonOosPlmnSearchFeatureSupportCfg, 0,
               sizeof(NAS_MMC_NON_OOS_PLMN_SEARCH_FEATURE_SUPPORT_CFG_STRU));

    /* 默认不激活history搜特性 */
    pstNonOosPlmnSearchFeatureSupportCfg->ucHistoryActiveFlg                        = VOS_FALSE;

    /* 默认不激活PrefBand搜特性 */
    pstNonOosPlmnSearchFeatureSupportCfg->ucPrefBandActiveFlg                       = VOS_FALSE;

    /* 默认area lost场景history之后进行spec搜 */
    pstNonOosPlmnSearchFeatureSupportCfg->enSearchTypeAfterHistoryInAreaLostScene   = NAS_MMC_PLMN_SEARCH_TYPE_AFTER_HISTORY_SPEC;
    return;
}

#if (FEATURE_ON == FEATURE_CSG)
/*****************************************************************************
 函 数 名  : NAS_MMC_InitCsgListSearchRatInfo_PlmnList
 功能描述  : CSG LIST搜网状态机运行过程中初始化需要搜索的接入技术信息,目前只支持lte csg
 输入参数  : 无
 输出参数  : 无
 返 回 值  : 无
 调用函数  :
 被调函数  :

 修改历史      :
 1.日    期   : 2015年10月12日
   作    者   : z00161729
   修改内容   : 支持LTE CSG功能新增

*****************************************************************************/
VOS_VOID NAS_MMC_InitCsgListSearchRatInfo_PlmnList(VOS_VOID)
{
    VOS_UINT32                          i;
    NAS_MMC_PLMN_LIST_SEARCH_CTRL_STRU *pstSearchRatInfo = VOS_NULL_PTR;
    NAS_MML_PLMN_RAT_PRIO_STRU         *pstRatPrioList   = VOS_NULL_PTR;
    NAS_MML_PLMN_RAT_PRIO_STRU          stTmpPrioRatList;

    PS_MEM_SET(&stTmpPrioRatList, 0, sizeof(NAS_MML_PLMN_RAT_PRIO_STRU));

    /* 当前不是PLMN LIST状态机 异常打印 */
    if ( NAS_MMC_FSM_PLMN_LIST != NAS_MMC_GetCurrFsmId())
    {
        NAS_ERROR_LOG(WUEPS_PID_MMC, "NAS_MMC_InitCsgListSearchRatInfo_PlmnList,ERROR:FsmId Error");

        return;
    }

    pstSearchRatInfo    = NAS_MMC_GetSearchCtrlInfo_PlmnList();

    pstRatPrioList      = NAS_MML_GetMsPrioRatList();

    /* 构造一份临时接入技术列表, 便于调整 */
    PS_MEM_CPY(&stTmpPrioRatList, pstRatPrioList, sizeof(NAS_MML_PLMN_RAT_PRIO_STRU));

    /* 当前接入技术存在,当前接入技术排在最前面 */
    if ( NAS_MML_NET_RAT_TYPE_BUTT != NAS_MML_GetCurrNetRatType())
    {
        NAS_MML_SortSpecRatPrioHighest(NAS_MML_GetCurrNetRatType(), &stTmpPrioRatList);
    }

    /* 初始化接入技术优先级列表以及搜索标记,目前只支持LTE CSG,gu的设置为true */
    for (i = 0; i < stTmpPrioRatList.ucRatNum; i++ )
    {
        pstSearchRatInfo[i].enRat           = stTmpPrioRatList.aucRatPrio[i];
        pstSearchRatInfo[i].ucSearchedFlag  = VOS_FALSE;

        if (NAS_MML_NET_RAT_TYPE_LTE != stTmpPrioRatList.aucRatPrio[i])
        {
            pstSearchRatInfo[i].ucSearchedFlag  = VOS_TRUE;
        }
    }
}
#endif


/*****************************************************************************
 函 数 名  : NAS_MMC_InitGetGeoInfo
 功能描述  : 初始化get_geo相关信息
 输入参数  : NAS_MMC_GET_GEO_INFO_STRU          *pstGetGeoInfo
 输出参数  : 无
 返 回 值  : VOS_VOID
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2015年5月28日
    作    者   : s00217060
    修改内容   : 新生成函数

*****************************************************************************/
VOS_VOID NAS_MMC_InitGetGeoInfo(
    NAS_MMC_GET_GEO_INFO_STRU          *pstGetGeoInfo
)
{
    /* 初始化GEO PLMN */
    NAS_MMC_InitGeoPlmn();

    return;
}

/*****************************************************************************
 函 数 名  : NAS_MMC_InitGeoPlmn
 功能描述  : 初始化GEO PLMN
 输入参数  : VOS_VOID
 输出参数  : 无
 返 回 值  :
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2015年6月9日
    作    者   : s00217060
    修改内容   : 新生成函数

*****************************************************************************/
VOS_VOID NAS_MMC_InitGeoPlmn(VOS_VOID)
{

    NAS_MML_PLMN_WITH_RAT_STRU                              stGeoPlmn;

    PS_MEM_SET(&stGeoPlmn, 0, sizeof(NAS_MML_PLMN_WITH_RAT_STRU));
    stGeoPlmn.enRat             = NAS_MML_NET_RAT_TYPE_BUTT;
    stGeoPlmn.stPlmnId.ulMcc    = NAS_MML_INVALID_MCC;
    stGeoPlmn.stPlmnId.ulMnc    = NAS_MML_INVALID_MNC;

    NAS_MMC_SetGeoPlmn(&stGeoPlmn);

    return;
}

/*****************************************************************************
 函 数 名  : NAS_MMC_GetDisabledLtePlmnId
 功能描述  : 获取disable lte时驻留的网络信息
 输入参数  : 无
 输出参数  : 无
 返 回 值  : disable lte时驻留的网络信息
 调用函数  :
 被调函数  :

 修改历史      :
 1.日    期   : 2015年1月5日
   作    者   : z00161729
   修改内容   : AT&T 支持DAM特性修改
*****************************************************************************/
NAS_MML_PLMN_ID_STRU *NAS_MMC_GetDisabledLtePlmnId(VOS_VOID)
{
    return &(NAS_MMC_GetMmcCtxAddr()->stPlmnSearchCtrl.stDisabledLtePlmnId);
}

/*****************************************************************************
 函 数 名  : NAS_MMC_SetDisabledLtePlmnId
 功能描述  : 设置disable lte时驻留的网络信息
 输入参数  : pstPlmnId - plmn信息
 输出参数  : 无
 返 回 值  : 无
 调用函数  :
 被调函数  :

 修改历史      :
 1.日    期   : 2015年1月5日
   作    者   : z00161729
   修改内容   : AT&T 支持DAM特性修改
*****************************************************************************/
VOS_VOID NAS_MMC_SetDisabledLtePlmnId(
    NAS_MML_PLMN_ID_STRU              *pstPlmnId
)
{
    NAS_MMC_GetMmcCtxAddr()->stPlmnSearchCtrl.stDisabledLtePlmnId.ulMcc = pstPlmnId->ulMcc;
    NAS_MMC_GetMmcCtxAddr()->stPlmnSearchCtrl.stDisabledLtePlmnId.ulMnc = pstPlmnId->ulMnc;
    return;
}

/*****************************************************************************
 函 数 名  : NAS_MMC_ClearDisabledLtePlmnId
 功能描述  : 清除disable lte时驻留的网络信息
 输入参数  : 无
 输出参数  : 无
 返 回 值  : 无
 调用函数  :
 被调函数  :

 修改历史      :
 1.日    期   : 2015年1月5日
   作    者   : z00161729
   修改内容   : AT&T 支持DAM特性修改
*****************************************************************************/
VOS_VOID NAS_MMC_ClearDisabledLtePlmnId(VOS_VOID)
{
    NAS_MMC_GetMmcCtxAddr()->stPlmnSearchCtrl.stDisabledLtePlmnId.ulMcc = NAS_MML_INVALID_MCC;
    NAS_MMC_GetMmcCtxAddr()->stPlmnSearchCtrl.stDisabledLtePlmnId.ulMnc = NAS_MML_INVALID_MNC;
    return;
}

/*****************************************************************************
 函 数 名  : NAS_MMC_GetEnableLteTimerExpireFlag
 功能描述  : 获取enable lte定时器是否超时标识
 输入参数  : 无
 输出参数  : 无
 返 回 值  : enable lte定时器是否超时标识
 调用函数  :
 被调函数  :

 修改历史     :
 1.日    期   : 2015年1月5日
   作    者   : z00161729
   修改内容   : AT&T 支持DAM特性修改

*****************************************************************************/
VOS_UINT8 NAS_MMC_GetEnableLteTimerExpireFlag( VOS_VOID )
{
    return (NAS_MMC_GetMmcCtxAddr()->stPlmnSearchCtrl.ucEnableLteTimerExpireFlag);
}

/*****************************************************************************
 函 数 名  : NAS_MMC_SetEnableLteTimerExpireFlag
 功能描述  : 设置enable lte定时器是否超时标识
 输入参数  : ucEnableLteTimerExpireFlag - enable lte定时器是否超时标识
 输出参数  : 无
 返 回 值  : 无
 调用函数  :
 被调函数  :

 修改历史     :
 1.日    期   : 2015年1月5日
   作    者   : z00161729
   修改内容   : AT&T 支持DAM特性修改

*****************************************************************************/
VOS_VOID NAS_MMC_SetEnableLteTimerExpireFlag(
    VOS_UINT8                           ucEnableLteTimerExpireFlag
)
{
    NAS_MMC_GetMmcCtxAddr()->stPlmnSearchCtrl.ucEnableLteTimerExpireFlag = ucEnableLteTimerExpireFlag;
    return;
}



/* Added by s00246516 for L-C互操作项目, 2014-02-13, Begin */
/*****************************************************************************
 函 数 名  : NAS_MMC_GetRegCtrl
 功能描述  : 获取注册控制信息
 输入参数  : 无
 输出参数  : 无
 返 回 值  : NAS_MMC_REG_CONTROL_ENUM_UINT8
 调用函数  :
 被调函数  :

 修改历史     :
 1.日    期   : 2014年2月14日
   作    者   : s00246516
   修改内容   : 新生成函数

*****************************************************************************/
NAS_MMC_REG_CONTROL_ENUM_UINT8 NAS_MMC_GetRegCtrl( VOS_VOID )
{
    return (NAS_MMC_GetMmcCtxAddr()->stPlmnSearchCtrl.enRegCtrl);
}

/*****************************************************************************
 函 数 名  : NAS_MMC_SetRegCtrl
 功能描述  : 设置注册控制信息
 输入参数  : NAS_MMC_REG_CONTROL_ENUM_UINT8
 输出参数  : 无
 返 回 值  : 无
 调用函数  :
 被调函数  :

 修改历史     :
 1.日    期   : 2014年2月14日
   作    者   : s00246516
   修改内容   : 新生成函数

*****************************************************************************/
VOS_VOID NAS_MMC_SetRegCtrl(
    NAS_MMC_REG_CONTROL_ENUM_UINT8      enRegCtrl
)
{
    (NAS_MMC_GetMmcCtxAddr()->stPlmnSearchCtrl.enRegCtrl) = enRegCtrl;
}

/*****************************************************************************
 函 数 名  : NAS_MMC_GetAsAnyCampOn
 功能描述  : 获取接入层是否Any cell驻留
 输入参数  : 无
 输出参数  : 无
 返 回 值  : VOS_UINT8
 调用函数  :
 被调函数  :

 修改历史     :
 1.日    期   : 2014年2月14日
   作    者   : s00246516
   修改内容   : 新生成函数

*****************************************************************************/
VOS_UINT8 NAS_MMC_GetAsAnyCampOn( VOS_VOID )
{
    return (NAS_MMC_GetMmcCtxAddr()->stPlmnSearchCtrl.ucAsAnyCampOn);
}

/*****************************************************************************
 函 数 名  : NAS_MMC_SetAsAnyCampOn
 功能描述  : 设置接入层是否Any cell驻留
 输入参数  : VOS_UINT8
 输出参数  : 无
 返 回 值  : 无
 调用函数  :
 被调函数  :

 修改历史     :
 1.日    期   : 2014年2月14日
   作    者   : s00246516
   修改内容   : 新生成函数

*****************************************************************************/
VOS_VOID NAS_MMC_SetAsAnyCampOn(
    VOS_UINT8                          ucAsAnyCampOn
)
{
    (NAS_MMC_GetMmcCtxAddr()->stPlmnSearchCtrl.ucAsAnyCampOn) = ucAsAnyCampOn;
}


/*****************************************************************************
 函 数 名  : NAS_MMC_SaveRegReqNCellInfo
 功能描述  : 保存MSCC REG REQ请求消息中的CellInfo信息到NCELL全局变量中
 输入参数  : pstCellInfo:需要保存的CellInfo信息
 输出参数  : 无
 返 回 值  : 无
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2014年1月27日
    作    者   : s00246516
    修改内容   : 新生成函数

*****************************************************************************/
VOS_VOID NAS_MMC_SaveRegReqNCellInfo(
    MSCC_MMC_REG_CELL_INFO_STRU         *pstCellInfo
)
{
    NAS_MMC_NCELL_SEARCH_INFO_STRU     *pstMmcNcellSearchInfo = VOS_NULL_PTR;

    /* 目前仅支持注册请求中携带LTE的NCell信息 */
    if (NAS_MML_NET_RAT_TYPE_LTE != pstCellInfo->ucRat)
    {
        return;
    }

    /* 保存NCELL信息 */
    pstMmcNcellSearchInfo = NAS_MMC_GetNcellSearchInfo();
    pstMmcNcellSearchInfo->stLteNcellInfo.ucLteArfcnNum       = 1;
    pstMmcNcellSearchInfo->stLteNcellInfo.aulLteArfcnList[0]  = pstCellInfo->ulArfcn;

    pstMmcNcellSearchInfo->stLteNcellInfo.ucLteCellNum        = NAS_MML_MIN(pstCellInfo->ucCellNum, NAS_MMC_LTE_CELL_MAX_NUM);
    PS_MEM_CPY(pstMmcNcellSearchInfo->stLteNcellInfo.ausLteCellList, pstCellInfo->ausCellId,
               ((pstMmcNcellSearchInfo->stLteNcellInfo.ucLteCellNum) * sizeof(VOS_UINT16)));

    pstMmcNcellSearchInfo->stOtherModemEplmnInfo.ucEquPlmnNum = NAS_MML_MIN(pstCellInfo->ucPlmnNum, NAS_MML_MAX_EQUPLMN_NUM);
    PS_MEM_CPY(pstMmcNcellSearchInfo->stOtherModemEplmnInfo.astEquPlmnAddr, pstCellInfo->astPlmnId,
               ((pstMmcNcellSearchInfo->stOtherModemEplmnInfo.ucEquPlmnNum) * sizeof(NAS_MML_PLMN_ID_STRU)));

    return;
}
/* Added by s00246516 for L-C互操作项目, 2014-02-13, End */

/*****************************************************************************
 函 数 名  : NAS_MMC_GetPrefPlmnPara
 功能描述  : 用于从MMC中获取MMC的全局变量信息
 输入参数  : MMC_MMA_SHARE_PARA_ST *pMmcPara
 输出参数  : 无
 返 回 值  : VOS_UINT32  VOS_FALSE:表示失败，VOS_TRUE:表示成功
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2015年02月07日
    作    者   : y00307564
    修改内容   : 新生成函数
*****************************************************************************/
VOS_UINT32 NAS_MMC_GetPrefPlmnPara(
    MMC_MMA_SHARE_PARA_ST              *pstMmcPara
)
{
    /* 参数有效性判断 */
    if (VOS_NULL_PTR == pstMmcPara)
    {
        /* 指针为空指针，返回错误 */
        NAS_WARNING_LOG(WUEPS_PID_MMC,"NAS_MMC_GetPrefPlmnPara:WARNING:NULL PTR ");
        return VOS_FALSE;
    }

    if (pstMmcPara->enMmaParaType >= EN_MMC_BEGIN_SET_MMC_PARA)
    {
        /* 类型参数错误,返回错误值 */
        NAS_WARNING_LOG(WUEPS_PID_MMC,"NAS_MMC_GetPrefPlmnPara:WARNING:PARA TYPE WRONG");
        return VOS_FALSE;
    }

    switch (pstMmcPara->enMmaParaType)
    {
        case EN_MMC_OPLMN_INFO:
            NAS_MMC_GetOperPlmnInfoForMscc(&(pstMmcPara->u.stOPlmnInfo));
            break;

        case EN_MMC_UPLMN_INFO:
            NAS_MMC_GetUserPlmnInfoForMscc(&(pstMmcPara->u.stUPlmnInfo));
            break;

        case EN_MMC_HPLMN_INFO:
            NAS_MMC_GetHPlmnInfoForMscc(&(pstMmcPara->u.stHPlmnInfo));
            break;


        /* PLMNSEL 和 UPLMN 只可能出现一个，故都存在 stUPlmnInfo 中 */
        case EN_MMC_PLMNSEL_INFO:
            NAS_MMC_GetSelPlmnInfoForMscc(&(pstMmcPara->u.stUPlmnInfo));
            break;

        default:
            /* 打印出错信息,返回出错标志 */
            NAS_WARNING_LOG(WUEPS_PID_MMC,"NAS_MMC_GetPrefPlmnPara:WARNING:PARA TYPE WRONG IN DEFAULT");
            return VOS_FALSE;
    }

    return VOS_TRUE;
}


/*****************************************************************************
 函 数 名  : NAS_MMC_SetPrefPlmnPara
 功能描述  : 用于设置MMC的全局变量信息
 输入参数  : MMC_MMA_SHARE_PARA_ST *pMmcPara
 输出参数  : 无
 返 回 值  : VOS_UINT32  VOS_FALSE:表示失败，VOS_TRUE:表示成功
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2015年02月07日
    作    者   : y00307564
    修改内容   : 新生成函数
*****************************************************************************/
VOS_UINT32 NAS_MMC_SetPrefPlmnPara(
    MMC_MMA_SHARE_PARA_ST              *pstMmcPara
)
{
    VOS_UINT32                          ulI = 0;
    NAS_MML_SIM_SELPLMN_INFO_STRU      *pstSelPlmn  = VOS_NULL_PTR;
    NAS_MML_SIM_USERPLMN_INFO_STRU     *pstUserPlmn = VOS_NULL_PTR;

    if (VOS_NULL_PTR == pstMmcPara)
    {
        /* 指针为空指针，返回错误 */
        NAS_WARNING_LOG(WUEPS_PID_MMC, "NAS_MMC_SetPrefPlmnPara:WARNING:Set Para Point is NULL");
        return VOS_FALSE;
    }

    pstUserPlmn = NAS_MML_GetSimUserPlmnList();
    pstSelPlmn  = NAS_MML_GetSimSelPlmnList();

    if ((pstMmcPara->enMmaParaType < EN_MMC_BEGIN_SET_MMC_PARA)
      || (pstMmcPara->enMmaParaType > EN_MMC_END_SET_MMC_PARA))
    {
        NAS_WARNING_LOG(WUEPS_PID_MMC, "NAS_MMC_SetPrefPlmnPara:WARNING:PARA TYPE WRONG");
        return VOS_FALSE;
    }

    switch (pstMmcPara->enMmaParaType)
    {
        case EN_MMC_SET_UPLMN_INFO:
             pstUserPlmn->ucUserPlmnNum      = (VOS_UINT8)pstMmcPara->u.stUPlmnInfo.usCurPlmnNum;
             for (ulI = 0; ulI < pstMmcPara->u.stUPlmnInfo.usCurPlmnNum ; ulI++)
             {
                 pstUserPlmn->astUserPlmnInfo[ulI].stPlmnId.ulMcc = pstMmcPara->u.stUPlmnInfo.astPlmnInfo[ulI].stPlmn.ulMcc;
                 pstUserPlmn->astUserPlmnInfo[ulI].stPlmnId.ulMnc = pstMmcPara->u.stUPlmnInfo.astPlmnInfo[ulI].stPlmn.ulMnc;
                 pstUserPlmn->astUserPlmnInfo[ulI].usSimRat       = pstMmcPara->u.stUPlmnInfo.astPlmnInfo[ulI].usRaMode;
             }

             break;

        case  EN_MMC_SET_PLMNSEL_INFO:
            pstSelPlmn->ucSelPlmnNum    = (VOS_UINT8)pstMmcPara->u.stUPlmnInfo.usCurPlmnNum;
            for (ulI = 0; ulI < pstMmcPara->u.stUPlmnInfo.usCurPlmnNum ; ulI++)
            {
                pstSelPlmn->astPlmnId[ulI].ulMcc = pstMmcPara->u.stUPlmnInfo.astPlmnInfo[ulI].stPlmn.ulMcc;
                pstSelPlmn->astPlmnId[ulI].ulMnc = pstMmcPara->u.stUPlmnInfo.astPlmnInfo[ulI].stPlmn.ulMnc;
            }

            break;

        default:
            NAS_WARNING_LOG(WUEPS_PID_MMC, "NAS_MMC_SetPrefPlmnPara:WARNING:PARA TYPE WRONG IN DEFAULT");
            return VOS_FALSE;

    }
    return VOS_TRUE;
}

/*****************************************************************************
 函 数 名  : NAS_MMC_GetPlmnInfo
 功能描述  : 从MMC中获取MMC的全局变量信息
 输入参数  : NAS_MSCC_PIF_PARA_TYPE_ENUM_UINT8                       enPrefPlmnParaType,
            NAS_MSCC_PIF_USER_PLMN_LIST_STRU                       *pstPlmnInfo
 输出参数  : 无
 返 回 值  : VOS_UINT32
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2015年02月07日
    作    者   : y00307564
    修改内容   : 新生成函数
*****************************************************************************/
VOS_UINT32 NAS_MMC_GetPlmnInfo(
    NAS_MSCC_PIF_PARA_TYPE_ENUM_UINT8                       enPrefPlmnParaType,
    NAS_MSCC_PIF_USER_PLMN_LIST_STRU                       *pstPlmnInfo
)
{
    VOS_UINT32                          ulLoop;
    MMC_TAF_PLMN_LIST_INFO_ST          *pstRptMsccSelPlmnList = VOS_NULL_PTR;

    pstRptMsccSelPlmnList = (MMC_TAF_PLMN_LIST_INFO_ST *)PS_MEM_ALLOC(WUEPS_PID_MMC, sizeof(MMC_TAF_PLMN_LIST_INFO_ST));
    if (VOS_NULL_PTR == pstRptMsccSelPlmnList)
    {
        return VOS_FALSE;
    }

    switch (enPrefPlmnParaType)
    {
        case NAS_MSCC_OPLMN_INFO:
            NAS_MMC_GetOperPlmnInfoForMscc(pstRptMsccSelPlmnList);
            break;

        case NAS_MSCC_UPLMN_INFO:
            NAS_MMC_GetUserPlmnInfoForMscc(pstRptMsccSelPlmnList);
            break;

        case NAS_MSCC_HPLMN_INFO:
            NAS_MMC_GetHPlmnInfoForMscc(pstRptMsccSelPlmnList);
            break;

        /* PLMNSEL 和 UPLMN 只可能出现一个，故都存在 stUPlmnInfo 中 */
        case NAS_MSCC_PLMNSEL_INFO:
            NAS_MMC_GetSelPlmnInfoForMscc(pstRptMsccSelPlmnList);
            break;

        default:
            /* 打印出错信息,返回出错标志 */
            PS_MEM_FREE(WUEPS_PID_MMC, pstRptMsccSelPlmnList);
            NAS_WARNING_LOG(WUEPS_PID_MMC, "NAS_MMC_GetPlmnInfo:WARNING:PARA TYPE WRONG IN DEFAULT ");
            return VOS_FALSE;
    }

    pstPlmnInfo->usPlmnNum = pstRptMsccSelPlmnList->usCurPlmnNum;
    for ( ulLoop = 0; ulLoop < pstRptMsccSelPlmnList->usCurPlmnNum ; ulLoop++ )
    {
        pstPlmnInfo->Plmn[ulLoop].ulMcc = pstRptMsccSelPlmnList->astPlmnInfo[ulLoop].stPlmn.ulMcc;
        pstPlmnInfo->Plmn[ulLoop].ulMnc = pstRptMsccSelPlmnList->astPlmnInfo[ulLoop].stPlmn.ulMnc;
        NAS_MMC_PlmnId2Bcd(&(pstPlmnInfo->Plmn[ulLoop]));
        pstPlmnInfo->ausPlmnRat[ulLoop] = pstRptMsccSelPlmnList->astPlmnInfo[ulLoop].usRaMode;
    }

    PS_MEM_FREE(WUEPS_PID_MMC, pstRptMsccSelPlmnList);

    return VOS_TRUE;
}

/*****************************************************************************
 函 数 名  : NAS_MMC_GetSpecificPlmnTblSize
 功能描述  : 获取plmn tbl size
 输入参数  : NAS_MSCC_PIF_PARA_TYPE_ENUM_UINT8            enPrefPLMNType
 输出参数  : 无
 返 回 值  : VOS_UINT16
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2015年02月07日
    作    者   : y00307564
    修改内容   : 新生成函数
*****************************************************************************/
VOS_UINT16 NAS_MMC_GetSpecificPlmnTblSize(
    NAS_MSCC_PIF_PARA_TYPE_ENUM_UINT8                       enPrefPLMNType
)
{
    VOS_UINT16                                              usCurPlmnNum;
    NAS_MML_SIM_OPERPLMN_INFO_STRU                         *pstOperPlmnList = VOS_NULL_PTR;
    NAS_MML_SIM_USERPLMN_INFO_STRU                         *pstUserPlmnList = VOS_NULL_PTR;
    NAS_MML_SIM_HPLMN_WITH_RAT_INFO_STRU                   *pstHplmnWithRat = VOS_NULL_PTR;
    NAS_MML_SIM_SELPLMN_INFO_STRU                          *pstSelPlmnInfo  = VOS_NULL_PTR;

    usCurPlmnNum = 0;
    switch(enPrefPLMNType)
    {
        case NAS_MSCC_UPLMN_INFO:
            pstUserPlmnList = NAS_MML_GetSimUserPlmnList();
            usCurPlmnNum    = pstUserPlmnList->ucUserPlmnNum;
            break;
        case NAS_MSCC_PLMNSEL_INFO:
            pstSelPlmnInfo  = NAS_MML_GetSimSelPlmnList();
            usCurPlmnNum    = pstSelPlmnInfo->ucSelPlmnNum;
            break;
        case NAS_MSCC_OPLMN_INFO:
            pstOperPlmnList = NAS_MML_GetSimOperPlmnList();
            usCurPlmnNum    = pstOperPlmnList->usOperPlmnNum;
            break;
        case NAS_MSCC_HPLMN_INFO:
            pstHplmnWithRat = NAS_MML_GetSimHplmnWithRatList();
            usCurPlmnNum    = pstHplmnWithRat->ucHPlmnWithRatNum;
            break;
        default:
            break;
    }

    return usCurPlmnNum;
}

/*****************************************************************************
 函 数 名  : NAS_MMC_UpdatePlmnInfo
 功能描述  : 更新pref plmn
 输入参数  : VOS_UINT16                          usEfId
 输出参数  : 无
 返 回 值  : VOS_VOID
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2015年02月07日
    作    者   : y00307564
    修改内容   : 新生成函数
*****************************************************************************/
VOS_VOID NAS_MMC_UpdatePlmnInfo(
    VOS_UINT16                          usEfId
)
{
    MMC_MMA_SHARE_PARA_ST              *pstMsccPara;
    VOS_UINT16                          usIndex;
    MMC_MODIFY_PLMN_INFO_STRU          *pstPrefPlmnCtx;

    pstMsccPara = (MMC_MMA_SHARE_PARA_ST *)PS_MEM_ALLOC(WUEPS_PID_MMC,
                                            sizeof(MMC_MMA_SHARE_PARA_ST));

    if (VOS_NULL_PTR == pstMsccPara)
    {
        PS_NAS_LOG(WUEPS_PID_MMC, VOS_NULL, PS_LOG_LEVEL_WARNING, "NAS_MMC_UpdatePlmnInfo: Alloc memory fail.");
        return ;
    }

    if (USIMM_GSM_EFPLMNSEL_ID == usEfId ) /* EFPLMNsel */
    {
        pstMsccPara->enMmaParaType = EN_MMC_PLMNSEL_INFO;
    }
    else if ((USIMM_USIM_EFPLMNWACT_ID == usEfId) /* EFPLMNwAcT */
         || ((USIMM_GSM_EFPLMNWACT_ID  == usEfId)))
    {
        pstMsccPara->enMmaParaType = EN_MMC_UPLMN_INFO;
    }
    else if ((USIMM_USIM_EFOPLMNWACT_ID == usEfId)
          || (USIMM_GSM_EFOPLMNWACT_ID  == usEfId)) /* EFOPLMNwAcT */
    {
        pstMsccPara->enMmaParaType = EN_MMC_OPLMN_INFO;
    }
    else
    {
        pstMsccPara->enMmaParaType = EN_MMC_HPLMN_INFO;
    }

    pstPrefPlmnCtx = NAS_MMC_GetPrefPlmnCtxAddr();

    usIndex = pstPrefPlmnCtx->usIndex;

    if (usIndex >= NAS_MML_MAX_USERPLMN_NUM)
    {
        PS_MEM_FREE(WUEPS_PID_MMC, pstMsccPara);
        return ;
    }

    (VOS_VOID)NAS_MMC_GetPrefPlmnPara(pstMsccPara);

    if ( (USIMM_GSM_EFPLMNSEL_ID   == usEfId ) /* EFPLMNsel */
      || (USIMM_USIM_EFPLMNWACT_ID == usEfId)
      || (USIMM_GSM_EFPLMNWACT_ID  == usEfId)) /* EFPLMNwAcT */
    {
        pstMsccPara->u.stUPlmnInfo.astPlmnInfo[usIndex].stPlmn.ulMcc = pstPrefPlmnCtx->stPlmnId.ulMcc;
        pstMsccPara->u.stUPlmnInfo.astPlmnInfo[usIndex].stPlmn.ulMnc = pstPrefPlmnCtx->stPlmnId.ulMnc;
        NAS_MMC_PlmnId2NasStyle(&(pstMsccPara->u.stUPlmnInfo.astPlmnInfo[usIndex].stPlmn));
        pstMsccPara->u.stUPlmnInfo.astPlmnInfo[usIndex].usRaMode     = pstPrefPlmnCtx->PlmnRat;

        /* UPLMN需要进行更新 */
        NAS_MMC_SndMmcUpdateUplmnNotify();
    }
    else if ((USIMM_USIM_EFOPLMNWACT_ID == usEfId)
          || (USIMM_GSM_EFOPLMNWACT_ID  == usEfId)) /* EFOPLMNwAcT */
    {
        pstMsccPara->u.stOPlmnInfo.astPlmnInfo[usIndex].stPlmn.ulMcc = pstPrefPlmnCtx->stPlmnId.ulMcc;
        pstMsccPara->u.stOPlmnInfo.astPlmnInfo[usIndex].stPlmn.ulMnc = pstPrefPlmnCtx->stPlmnId.ulMnc;
        NAS_MMC_PlmnId2NasStyle(&(pstMsccPara->u.stOPlmnInfo.astPlmnInfo[usIndex].stPlmn));
        pstMsccPara->u.stOPlmnInfo.astPlmnInfo[usIndex].usRaMode     = pstPrefPlmnCtx->PlmnRat;

    }
    else
    {
        pstMsccPara->u.stHPlmnInfo.astPlmnInfo[usIndex].stPlmn.ulMcc = pstPrefPlmnCtx->stPlmnId.ulMcc;
        pstMsccPara->u.stHPlmnInfo.astPlmnInfo[usIndex].stPlmn.ulMnc = pstPrefPlmnCtx->stPlmnId.ulMnc;
        NAS_MMC_PlmnId2NasStyle(&(pstMsccPara->u.stHPlmnInfo.astPlmnInfo[usIndex].stPlmn));
        pstMsccPara->u.stHPlmnInfo.astPlmnInfo[usIndex].usRaMode     = pstPrefPlmnCtx->PlmnRat;
    }


    if (EN_MMC_UPLMN_INFO == pstMsccPara->enMmaParaType)
    {
        pstMsccPara->enMmaParaType = EN_MMC_SET_UPLMN_INFO;
    }
    else if (EN_MMC_PLMNSEL_INFO == pstMsccPara->enMmaParaType)
    {
        pstMsccPara->enMmaParaType = EN_MMC_SET_PLMNSEL_INFO;
    }
    else if (EN_MMC_OPLMN_INFO == pstMsccPara->enMmaParaType)
    {
        pstMsccPara->enMmaParaType = EN_MMC_SET_OPLMN_INFO;
    }
    else
    {
        pstMsccPara->enMmaParaType = MMC_MMA_PARA_TYPE_BUTT;
    }

    (VOS_VOID)NAS_MMC_SetPrefPlmnPara(pstMsccPara);

    PS_MEM_FREE(WUEPS_PID_MMC, pstMsccPara);

    return;

}

/*****************************************************************************
 函 数 名  : NAS_MMC_QryPrefPlmnId
 功能描述  : 查询pref plmn
 输入参数  : NAS_MSCC_PIF_PARA_TYPE_ENUM_UINT8   enPrefPLMNType,
             VOS_UINT32                          ulFromIndex,
             VOS_UINT32                          ulPlmnNum,
             NAS_MSCC_CPOL_PLMN_NAME_LIST_STRU  *pstPlmnInfo
 输出参数  : 无
 返 回 值  : VOS_UINT32
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2015年02月07日
    作    者   : y00307564
    修改内容   : 新生成函数
*****************************************************************************/
VOS_UINT32 NAS_MMC_QryPrefPlmnId(
    NAS_MSCC_PIF_PARA_TYPE_ENUM_UINT8       enPrefPLMNType,
    VOS_UINT32                              ulFromIndex,
    VOS_UINT32                              ulPlmnNum,
    NAS_MSCC_CPOL_PLMN_NAME_LIST_STRU      *pstPlmnInfo
)
{
    VOS_UINT32                                              i;
    NAS_MSCC_PIF_USER_PLMN_LIST_STRU                       *pstOrgPlmnInfo;

    pstOrgPlmnInfo = (NAS_MSCC_PIF_USER_PLMN_LIST_STRU*)PS_MEM_ALLOC(WUEPS_PID_MMC, sizeof(NAS_MSCC_PIF_USER_PLMN_LIST_STRU));

    if (VOS_NULL_PTR == pstOrgPlmnInfo)
    {
        return VOS_FALSE;
    }

    PS_MEM_SET(pstOrgPlmnInfo, 0x00, sizeof(NAS_MSCC_PIF_USER_PLMN_LIST_STRU));

    /* 获取优先网络列表 */
    if (VOS_TRUE != NAS_MMC_GetPlmnInfo(enPrefPLMNType, pstOrgPlmnInfo))
    {
        PS_MEM_FREE(WUEPS_PID_MMC, pstOrgPlmnInfo);

        return VOS_FALSE;
    }

    pstPlmnInfo->ulPlmnNum = pstOrgPlmnInfo->usPlmnNum;

    for (i = 0; i < ulPlmnNum; i++ )
    {
        pstPlmnInfo->ausPlmnRat[i]                         = pstOrgPlmnInfo->ausPlmnRat[(i + ulFromIndex)];
        pstPlmnInfo->astPlmnName[i].stOperatorPlmnId.ulMcc = pstOrgPlmnInfo->Plmn[(i + ulFromIndex)].ulMcc;
        pstPlmnInfo->astPlmnName[i].stOperatorPlmnId.ulMnc = pstOrgPlmnInfo->Plmn[(i + ulFromIndex)].ulMnc;
    }

    PS_MEM_FREE(WUEPS_PID_MMC, pstOrgPlmnInfo);

    return VOS_TRUE;

}


/*****************************************************************************
 函 数 名  : NAS_MMC_InitPrefPlmnCtx
 功能描述  : 初始化设置pref plmn设置请求上下文
 输入参数  : MMC_MODIFY_PLMN_INFO_STRU          *pstPreflmnInfo
 输出参数  : 无
 返 回 值  : 无
 调用函数  :
 被调函数  :

 修改历史      :
 1.日    期   : 2015年02月15日
   作    者   : y00307564
   修改内容   : 新生成函数

*****************************************************************************/
VOS_VOID NAS_MMC_InitPrefPlmnCtx(
    MMC_MODIFY_PLMN_INFO_STRU          *pstPreflmnInfo
)
{
    pstPreflmnInfo->stPlmnId.ulMcc  = NAS_MML_INVALID_MCC;
    pstPreflmnInfo->stPlmnId.ulMnc  = NAS_MML_INVALID_MNC;
    pstPreflmnInfo->usIndex         = 0;
    pstPreflmnInfo->PlmnRat         = NAS_MMC_RAT_BUTT;

    return;
}

/*****************************************************************************
 函 数 名  : NAS_MMC_InitPrefPlmnCtx
 功能描述  : 初始化设置pref plmn设置请求上下文
 输入参数  : 无
 输出参数  : prefPlmn nas_mmc_ctx上下文地址
 返 回 值  : 无
 调用函数  :
 被调函数  :

 修改历史      :
 1.日    期   : 2015年02月15日
   作    者   : y00307564
   修改内容   : 新生成函数

*****************************************************************************/
MMC_MODIFY_PLMN_INFO_STRU* NAS_MMC_GetPrefPlmnCtxAddr(VOS_VOID)
{
    return &(NAS_MMC_GetMmcCtxAddr()->stPreflmnInfo);
}

/*****************************************************************************
 函 数 名  : NAS_MMC_InitDetachReqCtx
 功能描述  : 初始化设置detach request请求上下文
 输入参数  : NAS_MMC_DETACH_REQ_CTX_STRU          *pstDetachReqCtx
 输出参数  : 无
 返 回 值  : 无
 调用函数  :
 被调函数  :

 修改历史      :
 1.日    期   : 2015年04月17日
   作    者   : y00245242
   修改内容   : 新生成函数

*****************************************************************************/
VOS_VOID NAS_MMC_InitDetachReqCtx(
    NAS_MMC_DETACH_REQ_CTX_STRU        *pstDetachReqCtx
)
{
    pstDetachReqCtx->enDetachReason = NAS_MSCC_PIF_DETACH_REASON_BUTT;

    pstDetachReqCtx->enDetachType   = NAS_MSCC_PIF_DETACH_TYPE_BUTT;

    return;
}

/*****************************************************************************
 函 数 名  : NAS_MMC_GetDetachReqCtxAddr
 功能描述  : 获取detach请求上下文地址
 输入参数  : 无
 输出参数  : 无
 返 回 值  : NAS_MMC_DETACH_REQ_CTX_STRU
 调用函数  :
 被调函数  :

 修改历史     :
 1.日    期   : 2015年4月17日
   作    者   : y00245242
   修改内容   : 新生成函数

*****************************************************************************/
NAS_MMC_DETACH_REQ_CTX_STRU *NAS_MMC_GetDetachReqCtxAddr(VOS_VOID)
{
    return &(NAS_MMC_GetMmcCtxAddr()->stDetachReqCtx);
}

/*****************************************************************************
 函 数 名  : NAS_MMC_InitAttachReqCtx
 功能描述  : 初始化设置attach request请求上下文
 输入参数  : NAS_MMC_DETACH_REQ_CTX_STRU          *pstDetachReqCtx
 输出参数  : 无
 返 回 值  : 无
 调用函数  :
 被调函数  :

 修改历史      :
 1.日    期   : 2015年04月17日
   作    者   : y00245242
   修改内容   : 新生成函数

*****************************************************************************/
VOS_VOID NAS_MMC_InitAttachReqCtx(
    NAS_MMC_ATTACH_REQ_CTX_STRU        *pstAttachReqCtx
)
{
    pstAttachReqCtx->ulOpID = 0;

    return;
}

/*****************************************************************************
 函 数 名  : NAS_MMC_GetAttachReqOpId
 功能描述  : 获取attach请求上下文地址
 输入参数  : 无
 输出参数  : 无
 返 回 值  : VOS_UINT32
 调用函数  :
 被调函数  :

 修改历史     :
 1.日    期   : 2015年4月17日
   作    者   : y00245242
   修改内容   : 新生成函数

*****************************************************************************/
VOS_UINT32 NAS_MMC_GetAttachReqOpId(VOS_VOID)
{
    return (NAS_MMC_GetMmcCtxAddr()->stAttachReqCtx.ulOpID);
}

/*****************************************************************************
 函 数 名  : NAS_MMC_SetAttachReqOpId
 功能描述  : 设置attach请求OpId
 输入参数  : ulOpId -- 操作ID
 输出参数  : 无
 返 回 值  : 无
 调用函数  :
 被调函数  :

 修改历史     :
 1.日    期   : 2015年4月17日
   作    者   : y00245242
   修改内容   : 新生成函数

*****************************************************************************/
VOS_VOID NAS_MMC_SetAttachReqOpId(VOS_UINT32 ulOpId)
{
    NAS_MMC_GetMmcCtxAddr()->stAttachReqCtx.ulOpID = ulOpId;
}

/*lint -restore */

/*****************************************************************************
 函 数 名  : NAS_MMC_GetFsmCtxAddr_GetGeo
 功能描述  : 获取GetGeo状态机的上下文的指针
 输入参数  : VOS_VOID
 输出参数  : 无
 返 回 值  : NAS_MMC_FSM_GET_GEO_CTX_STRU*
 调用函数  :
 被调函数  :

 修改历史     :
 1.日    期   : 2015年05月08日
   作    者   : sunjitan 00193151
   修改内容   : 新生成函数
*****************************************************************************/
NAS_MMC_FSM_GET_GEO_CTX_STRU* NAS_MMC_GetFsmCtxAddr_GetGeo(VOS_VOID)
{
    /* 如果当前状态机不是GET GEO */
    if (NAS_MMC_FSM_GET_GEO != NAS_MMC_GetCurrFsmId())
    {
        NAS_ERROR_LOG(WUEPS_PID_MMC, "NAS_MMC_GetFsmCtxAddr_GetGeo,ERROR:FsmId Error");
    }

    return &(g_stNasMmcCtx.stCurFsm.unFsmCtx.stGetGeoCtx);
}

/*****************************************************************************
 函 数 名  : NAS_MMC_GetGeoRatInfoList_GetGeo
 功能描述  : 获取GetGeo状态机的接入技术优先级列表上下文的指针
 输入参数  : VOS_VOID
 输出参数  : 无
 返 回 值  : NAS_MMC_GET_GEO_RAT_INFO_LIST_STRU*
 调用函数  :
 被调函数  :

 修改历史     :
 1.日    期   : 2015年06月12日
   作    者   : f00179208
   修改内容   : 新生成函数
*****************************************************************************/
NAS_MMC_GET_GEO_RAT_INFO_LIST_STRU* NAS_MMC_GetGeoRatInfoList_GetGeo(VOS_VOID)
{
    /* 如果当前状态机不是GET GEO */
    if (NAS_MMC_FSM_GET_GEO != NAS_MMC_GetCurrFsmId())
    {
        NAS_ERROR_LOG(WUEPS_PID_MMC, "NAS_MMC_GetGeoRatListInfo_GetGeo,ERROR:FsmId Error");
    }

    return &(g_stNasMmcCtx.stCurFsm.unFsmCtx.stGetGeoCtx.stGetGeoRatInfoList);
}

/*****************************************************************************
 函 数 名  : NAS_MMC_GetAbortFlag_GetGeo
 功能描述  : 获取GetGeo状态机上下文中的ABORT标识
 输入参数  : VOS_VOID
 输出参数  : 无
 返 回 值  : VOS_UINT8
 调用函数  :
 被调函数  :

 修改历史      :
 1.日    期   : 2015年05月08日
   作    者   : sunjitan 00193151
   修改内容   : 新生成函数

*****************************************************************************/
VOS_UINT8 NAS_MMC_GetAbortFlag_GetGeo(VOS_VOID)
{
    /* 如果当前状态机不是GET_GEO, 异常打印  */
    if (NAS_MMC_FSM_GET_GEO != NAS_MMC_GetCurrFsmId())
    {
        NAS_ERROR_LOG(WUEPS_PID_MMC, "NAS_MMC_GetAbortFlag_GetGeo,ERROR:FsmId Error");
    }

    return g_stNasMmcCtx.stCurFsm.unFsmCtx.stGetGeoCtx.ucAbortFlag;
}

/*****************************************************************************
 函 数 名  : NAS_MMC_SetAbortFlag_GetGeo
 功能描述  : 设置GET GEO状态机上下文中的ABORT标识
 输入参数  : VOS_UINT8    ulAbortFlag     ABORT标志
 输出参数  : 无
 返 回 值  : 无
 调用函数  :
 被调函数  :

 修改历史      :
 1.日    期   : 2015年05月08日
   作    者   : sunjitan 00193151
   修改内容   : 新生成函数

*****************************************************************************/
VOS_VOID NAS_MMC_SetAbortFlag_GetGeo(
    VOS_UINT8                           ucAbortFlag
)
{
    /* 如果当前状态机不是GET_GEO, 异常打印  */
    if (NAS_MMC_FSM_GET_GEO != NAS_MMC_GetCurrFsmId())
    {
        NAS_ERROR_LOG(WUEPS_PID_MMC, "NAS_MMC_SetAbortFlag_GetGeo,ERROR:FsmId Error");
        return;
    }

    g_stNasMmcCtx.stCurFsm.unFsmCtx.stGetGeoCtx.ucAbortFlag = ucAbortFlag;
    return;
}

/*****************************************************************************
 函 数 名  : NAS_MMC_GetNotifyMsccFlag_GetGeo
 功能描述  : 获取GetGeo状态机上下文中的通知MSCC结果的标记
 输入参数  : VOS_VOID
 输出参数  : 无
 返 回 值  : VOS_UINT8
 调用函数  :
 被调函数  :

 修改历史      :
 1.日    期   : 2015年05月08日
   作    者   : f00179208
   修改内容   : 新生成函数

*****************************************************************************/
VOS_UINT8 NAS_MMC_GetNotifyMsccFlag_GetGeo(VOS_VOID)
{
    /* 如果当前状态机不是GET_GEO, 异常打印  */
    if (NAS_MMC_FSM_GET_GEO != NAS_MMC_GetCurrFsmId())
    {
        NAS_ERROR_LOG(WUEPS_PID_MMC, "NAS_MMC_GetNotifyMsccFlag_GetGeo,ERROR:FsmId Error");
    }

    return g_stNasMmcCtx.stCurFsm.unFsmCtx.stGetGeoCtx.ucNotifyMsccFlg;
}

/*****************************************************************************
 函 数 名  : NAS_MMC_SetNotifyMsccFlag_GetGeo
 功能描述  : 设置GET GEO状态机上下文中的通知MSCC结果的标记
 输入参数  : VOS_UINT8    ucNotifyMsccFlg
 输出参数  : 无
 返 回 值  : 无
 调用函数  :
 被调函数  :

 修改历史      :
 1.日    期   : 2015年05月08日
   作    者   : f00179208
   修改内容   : 新生成函数

*****************************************************************************/
VOS_VOID NAS_MMC_SetNotifyMsccFlag_GetGeo(
    VOS_UINT8                           ucNotifyMsccFlg
)
{
    /* 如果当前状态机不是GET_GEO, 异常打印  */
    if (NAS_MMC_FSM_GET_GEO != NAS_MMC_GetCurrFsmId())
    {
        NAS_ERROR_LOG(WUEPS_PID_MMC, "NAS_MMC_SetNotifyMsccFlag_GetGeo,ERROR:FsmId Error");
        return;
    }

    g_stNasMmcCtx.stCurFsm.unFsmCtx.stGetGeoCtx.ucNotifyMsccFlg = ucNotifyMsccFlg;

    return;
}

/*****************************************************************************
 函 数 名  : NAS_MMC_GetTaskPhase_GetGeo
 功能描述  : 获取GetGeo状态机的任务阶段
 输入参数  : VOS_VOID
 输出参数  : 无
 返 回 值  : NAS_MMC_GET_GEO_FSM_TASK_PHASE_ENUM_UINT8
 调用函数  :
 被调函数  :

 修改历史     :
 1.日    期   : 2015年06月03日
   作    者   : sunjitan 00193151
   修改内容   : 新生成函数
*****************************************************************************/
NAS_MMC_GET_GEO_FSM_TASK_PHASE_ENUM_UINT8 NAS_MMC_GetFsmTaskPhase_GetGeo(VOS_VOID)
{
    /* 如果当前状态机不是GET GEO */
    if (NAS_MMC_FSM_GET_GEO != NAS_MMC_GetCurrFsmId())
    {
        NAS_ERROR_LOG(WUEPS_PID_MMC, "NAS_MMC_GetTaskPhase_GetGeo,ERROR:FsmId Error");
    }

    return g_stNasMmcCtx.stCurFsm.unFsmCtx.stGetGeoCtx.enGetGeoTaskPhase;
}

/*****************************************************************************
 函 数 名  : NAS_MMC_SetTaskPhase_GetGeo
 功能描述  : 设置GetGeo状态机的任务阶段
 输入参数  : NAS_MMC_GET_GEO_FSM_TASK_PHASE_ENUM_UINT8
 输出参数  : 无
 返 回 值  : 无
 调用函数  :
 被调函数  :

 修改历史     :
 1.日    期   : 2015年06月03日
   作    者   : sunjitan 00193151
   修改内容   : 新生成函数
*****************************************************************************/
VOS_VOID NAS_MMC_SetFsmTaskPhase_GetGeo(
    NAS_MMC_GET_GEO_FSM_TASK_PHASE_ENUM_UINT8     enGetGeoTaskPhase
)
{
    /* 如果当前状态机不是GET GEO */
    if (NAS_MMC_FSM_GET_GEO != NAS_MMC_GetCurrFsmId())
    {
        NAS_ERROR_LOG(WUEPS_PID_MMC, "NAS_MMC_GetTaskPhase_GetGeo,ERROR:FsmId Error");
    }

    g_stNasMmcCtx.stCurFsm.unFsmCtx.stGetGeoCtx.enGetGeoTaskPhase = enGetGeoTaskPhase;

    return;
}

/*****************************************************************************
 函 数 名  : NAS_MMC_GetBackUpNoRfPlmnSearchScene_PlmnSelection
 功能描述  : 获取当前MMC保存的全局变量中的的NO RF下的搜网场景
 输入参数  : 无
 输出参数  : 无
 返 回 值  : NAS_MMC_PLMN_SEARCH_SCENE_ENUM_UINT32
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2015年5月26日
    作    者   : l00305157
    修改内容   : 新生成函数 ROAM_PLMN_SELECTION_OPTIMIZE_2.0
*****************************************************************************/
NAS_MMC_PLMN_SEARCH_SCENE_ENUM_UINT32 NAS_MMC_GetBackUpNoRfPlmnSearchScene_PlmnSelection(VOS_VOID)
{
    return g_stNasMmcCtx.stBackUpSearchInfo.stNoRFBackUpSearchInfo.enPlmnSearchScene;
}

/*****************************************************************************
 函 数 名  : NAS_MMC_GetNoRfPlmnSearchScene_PlmnSelection
 功能描述  : 设置当前在MMC的全局变量中保存的NO RF下的搜网场景
 输入参数  : NAS_MMC_PLMN_SEARCH_SCENE_ENUM_UINT32:设置当前在MMC的全局变量中保存的NO RF下的搜网场景
 输出参数  : 无
 返 回 值  : 无
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2015年5月26日
    作    者   : l00305157
    修改内容   : 新生成函数 ROAM_PLMN_SELECTION_OPTIMIZE_2.0
*****************************************************************************/
VOS_VOID NAS_MMC_SetBackUpNoRfPlmnSearchScene_PlmnSelection(
    NAS_MMC_PLMN_SEARCH_SCENE_ENUM_UINT32             enPlmnSearchScene
)
{
    g_stNasMmcCtx.stBackUpSearchInfo.stNoRFBackUpSearchInfo.enPlmnSearchScene = enPlmnSearchScene;

    return;
}

/*****************************************************************************
 函 数 名  : NAS_MMC_GetBackUpNoRfHistorySearchRatInfo_PlmnSelection
 功能描述  : 获取当前MMC保存的全局变量中的的NO RF下的搜网场景
 输入参数  : 无
 输出参数  : 无
 返 回 值  : NAS_MMC_PLMN_SEARCH_SCENE_ENUM_UINT32
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2015年5月26日
    作    者   : l00305157
    修改内容   : 新生成函数 ROAM_PLMN_SELECTION_OPTIMIZE_2.0
*****************************************************************************/
NAS_MMC_RAT_HISTORY_SEARCH_INFO_STRU* NAS_MMC_GetBackUpNoRfHistorySearchRatInfo_PlmnSelection(VOS_VOID)
{
    return &(g_stNasMmcCtx.stBackUpSearchInfo.stNoRFBackUpSearchInfo.astHistorySearchRatInfo[0]);
}

/*****************************************************************************
 函 数 名  : NAS_MMC_BackupNoRfSearchInfo_PlmnSelection
 功能描述  : 获取搜网列表
 输入参数  : VOS_VOID
 输出参数  : 无
 返 回 值  : NAS_MMC_RAT_SEARCH_INFO_STRU
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2015年5月21日
    作    者   : l00305157
    修改内容   : 新生成函数  ROAM_PLMN_SELECTION_OPTIMIZE_2.0

*****************************************************************************/
NAS_MMC_RAT_SEARCH_INFO_STRU* NAS_MMC_GetSearchRatInfo_PlmnSelection(VOS_VOID)
{
    return &(g_stNasMmcCtx.stCurFsm.unFsmCtx.stPlmnSelectionCtx.astSearchRatInfo[0]);
}

/*****************************************************************************
 函 数 名  : NAS_MMC_BackupNoRfSearchInfo_PlmnSelection
 功能描述  : NO RF情况下,备份HISTORY搜网场景以及搜网列表
 输入参数  : VOS_VOID
 输出参数  : 无
 返 回 值  : VOS_VOID
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2015年5月21日
    作    者   : l00305157
    修改内容   : 新生成函数  ROAM_PLMN_SELECTION_OPTIMIZE_2.0

*****************************************************************************/
VOS_VOID NAS_MMC_BackupNoRfHistorySearchedInfo_PlmnSelection(VOS_VOID)
{
    VOS_UINT32                                              i;
    NAS_MMC_RAT_SEARCH_INFO_STRU                           *pstSearchRatInfo = VOS_NULL_PTR;
    NAS_MMC_RAT_HISTORY_SEARCH_INFO_STRU                   *pstHsirotySearchRatInfo = VOS_NULL_PTR;
    NAS_MMC_PLMN_SEARCH_SCENE_ENUM_UINT32                   enPlmnSearchScene;


    /* 如果当前状态机不是PLMN SELECTION */
    if (NAS_MMC_FSM_PLMN_SELECTION != NAS_MMC_GetCurrFsmId())
    {
        NAS_ERROR_LOG(WUEPS_PID_MMC, "NAS_MMC_BackupNoRfHistorySearchedInfo_PlmnSelection,ERROR:FsmId Error");
        return;
    }

    /* 备份HISTORY搜网数据 */
    pstSearchRatInfo                    = NAS_MMC_GetSearchRatInfo_PlmnSelection();
    pstHsirotySearchRatInfo             = NAS_MMC_GetBackUpNoRfHistorySearchRatInfo_PlmnSelection();

    PS_MEM_SET(pstHsirotySearchRatInfo, 0, sizeof(NAS_MMC_RAT_HISTORY_SEARCH_INFO_STRU) * NAS_MML_MAX_RAT_NUM);

    for (i = 0; i < NAS_MML_MAX_RAT_NUM; i++ )
    {
        pstHsirotySearchRatInfo[i].enRatType                = pstSearchRatInfo[i].enRatType;
        pstHsirotySearchRatInfo[i].ucHistorySearchedFlag    = pstSearchRatInfo[i].ucHistorySearchedFlag;
    }

    /* 备份搜网场景 */
    enPlmnSearchScene = NAS_MMC_GetPlmnSearchScene_PlmnSelection();
    NAS_MMC_SetBackUpNoRfPlmnSearchScene_PlmnSelection(enPlmnSearchScene);

    return;
}

/*****************************************************************************
 函 数 名  : NAS_MMC_RestoreNoRfHistorySearchedRatInfo_PlmnSelection
 功能描述  : NO RF情况下,获取备份HISTORY搜网列表
 输入参数  : VOS_VOID
 输出参数  : 无
 返 回 值  : NAS_MMC_RAT_SEARCH_INFO_STRU*  astSearchRatInfo
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2015年5月21日
    作    者   : l00305157
    修改内容   : 新生成函数  ROAM_PLMN_SELECTION_OPTIMIZE_2.0

*****************************************************************************/
VOS_VOID NAS_MMC_RestoreNoRfHistorySearchedRatInfo_PlmnSelection(
    NAS_MMC_RAT_SEARCH_INFO_STRU       *pstSearchRatInfo

)
{
    VOS_UINT32                                              i;
    NAS_MMC_RAT_HISTORY_SEARCH_INFO_STRU                   *pstHsirotySearchRatInfo = VOS_NULL_PTR;

    pstHsirotySearchRatInfo             = NAS_MMC_GetBackUpNoRfHistorySearchRatInfo_PlmnSelection();

    /* 恢复HISTORY搜网数据 */
    for (i = 0; i < NAS_MML_MAX_RAT_NUM; i++ )
    {
        pstSearchRatInfo[i].enRatType             = pstHsirotySearchRatInfo[i].enRatType;
        pstSearchRatInfo[i].ucHistorySearchedFlag = pstHsirotySearchRatInfo[i].ucHistorySearchedFlag;
    }
    return;
}

/*****************************************************************************
 函 数 名  : NAS_MMC_InitNoRFBackUpSearchedInfoCtx
 功能描述  : NO RF情况下,初始化备份的HISTORY搜网列表/搜网场景
 输入参数  : NAS_MMC_NO_RF_BACK_UP_SEARCH_INFO_STRU*         pstNoRFBackSearchInfo
 输出参数  : 无
 返 回 值  : 无
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2015年5月21日
    作    者   : l00305157
    修改内容   : 新生成函数  ROAM_PLMN_SELECTION_OPTIMIZE_2.0

*****************************************************************************/
VOS_VOID NAS_MMC_InitNoRFBackUpSearchedInfoCtx(
    NAS_MMC_BACK_UP_SEARCH_INFO_STRU*         pstBackSearchInfo
)
{
    VOS_UINT32                                              i;

    pstBackSearchInfo->stNoRFBackUpSearchInfo.enPlmnSearchScene = NAS_MMC_PLMN_SEARCH_SCENE_BUTT;

    for (i = 0; i < NAS_MML_MAX_RAT_NUM; i++ )
    {
        pstBackSearchInfo->stNoRFBackUpSearchInfo.astHistorySearchRatInfo[i].enRatType                        = NAS_MML_NET_RAT_TYPE_BUTT;
        pstBackSearchInfo->stNoRFBackUpSearchInfo.astHistorySearchRatInfo[i].ucHistorySearchedFlag            = VOS_FALSE;
        pstBackSearchInfo->stNoRFBackUpSearchInfo.astHistorySearchRatInfo[i].aucReserved[0]                   = 0;
        pstBackSearchInfo->stNoRFBackUpSearchInfo.astHistorySearchRatInfo[i].aucReserved[1]                   = 0;
    }
    return;
}

/*****************************************************************************
 函 数 名  : NAS_MMC_GetLmmAttachReqSendRslt_PlmnSelection
 功能描述  : 获取LMM发来的Attach注册状态
 输入参数  : 无
 输出参数  : 无
 返 回 值  : 全局变量g_stNasMmcCtx中的Attach注册状态
 调用函数  :
 被调函数  :

 修改历史     :
 1.日    期   : 2015年4月22日
   作    者   : wx270776
   修改内容   : 新生成函数

*****************************************************************************/
MMC_LMM_ATTACH_CL_REG_STATUS_ENUM8 NAS_MMC_GetLmmAttachClRegStatus_PlmnSelection( VOS_VOID )
{
    return (g_stNasMmcCtx.stCurFsm.unFsmCtx.stPlmnSelectionCtx.stRegRlstInfo.enLmmAttachClRegStatus);
}

/*****************************************************************************
 函 数 名  : NAS_MMC_SetLmmAttachReqSendRslt_PlmnSelection
 功能描述  : 设置LMM发来的Attach注册状态
 输入参数  : 无
 输出参数  : 无
 返 回 值  : 无
 调用函数  :
 被调函数  :

 修改历史     :
 1.日    期   : 2015年4月22日
   作    者   : wx270776
   修改内容   : 新生成函数

*****************************************************************************/
VOS_VOID NAS_MMC_SetLmmAttachClRegStatus_PlmnSelection(
    MMC_LMM_ATTACH_CL_REG_STATUS_ENUM8                     enLmmAttachClRegStatus
)
{
    /* 如果当前状态机不是PLMN SELECTION异常打印 */
    if (NAS_MMC_FSM_PLMN_SELECTION != NAS_MMC_GetCurrFsmId())
    {
        NAS_ERROR_LOG(WUEPS_PID_MMC, "NAS_MMC_SetLmmAttachClRegStatus_PlmnSelection,ERROR:FsmId Error");
    }

    g_stNasMmcCtx.stCurFsm.unFsmCtx.stPlmnSelectionCtx.stRegRlstInfo.enLmmAttachClRegStatus = enLmmAttachClRegStatus;

    return;
}

#if (FEATURE_ON == FEATURE_UE_MODE_CDMA)
/*****************************************************************************
 函 数 名  : NAS_MMC_GetCLAssociatedInfoAddr
 功能描述  : 取得mmc上下文中的CLAssociatedInfoNtf
 输入参数  : 无
 输出参数  : 无
 返 回 值  : stCLAssociatedInfoNtf的地址

 修改历史      :
  1.日    期   : 2015年9月11日
    作    者   : y00346957
    修改内容   : add for DTS2015070910885

*****************************************************************************/
NAS_MMC_CL_ASSOCIATED_INFO_NTF_STRU* NAS_MMC_GetCLAssociatedInfoAddr(VOS_VOID)
{
    return &(g_stNasMmcCtx.stPlmnSearchCtrl.stCLAssociatedInfoNtf);
}
#endif

/*lint -restore */

#ifdef __cplusplus
    #if __cplusplus
        }
    #endif
#endif


