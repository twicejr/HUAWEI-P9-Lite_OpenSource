/******************************************************************************

                  版权所有 (C), 2001-2011, 华为技术有限公司

 ******************************************************************************
  文 件 名   : NASUTRANCTRLCtx.c
  版 本 号   : 初稿
  作    者   : w00167002
  生成日期   : 2012年7月12日
  最近修改   :
  功能描述   : NASUTRANCTRLCtx.C文件
  函数列表   :
  修改历史   :
  1.日    期   : 2012年7月12日
    作    者   : w00167002
    修改内容   : 创建文件

******************************************************************************/

/*****************************************************************************
  1 头文件包含
*****************************************************************************/

#include "PsTypeDef.h"
#include "NasMmcFsmPoweroffTbl.h"
#include "NasMmcTimerMgmt.h"
#include "NasMmcMain.h"
#if (FEATURE_ON == FEATURE_LTE)
#include "MmcLmmInterface.h"
#endif
#include "NasComm.h"
#include "NasUtranCtrlCtx.h"
#include "NasUtranCtrlFsmMainTbl.h"
#include "NasUtranCtrlFsmSwitchOnTbl.h"
#include "NasUtranCtrlFsmPoweroffTbl.h"
#include "NasUtranCtrlFsmSyscfgTbl.h"
#include "NasUtranCtrlFsmPlmnSelectionTbl.h"
#include "NasUtranCtrlFsmModeChangeTbl.h"
#include "NasUtranCtrlMain.h"
#include "NasUtranCtrlMntn.h"
#include "NasMmlLib.h"

#ifdef __cplusplus
#if __cplusplus
extern "C" {
#endif
#endif

/*****************************************************************************
  2 常量定义
*****************************************************************************/

#define    THIS_FILE_ID        PS_FILE_ID_NAS_UTRANCTRL_CTX_C

/*****************************************************************************
  3 类型定义
*****************************************************************************/

/*****************************************************************************
  4 函数声明
*****************************************************************************/

/*****************************************************************************
  5 变量定义
*****************************************************************************/
#if (FEATURE_ON == FEATURE_UE_MODE_TDS)

/* 保存三个模块共用的CTX */
NAS_UTRANCTRL_CTX_STRU                    g_stNasUtranCtrlCtx;
#endif

/*lint -save -e958 */

/*****************************************************************************
  6 函数定义
*****************************************************************************/

#if (FEATURE_ON == FEATURE_UE_MODE_TDS)
/*****************************************************************************
 函 数 名  : NAS_UTRANCTRL_GetUtranCtrlCtx
 功能描述  : 获取当前MMAGENT的CTX
 输入参数  : 无
 输出参数  : 无
 返 回 值  : 当前MMAGENT的CTX
 调用函数  :
 被调函数  :

 修改历史      :
 1.日    期   : 2012年7月12日
   作    者   : w00167002
   修改内容   : 新生成函数
*****************************************************************************/
NAS_UTRANCTRL_CTX_STRU* NAS_UTRANCTRL_GetUtranCtrlCtx( VOS_VOID )
{
    return &(g_stNasUtranCtrlCtx);
}

/*****************************************************************************
函 数 名  : NAS_UTRANCTRL_InitCustomCfgInfo
功能描述  : 初始化客户定制特性
输入参数  : 无
输出参数  : pstCustomCfg:初始化客户定制特性
返 回 值  :
调用函数  :
被调函数  :

修改历史      :
1.日    期   : 2012年7月12日
   作    者   : w00167002
   修改内容   : 新生成函数

3.日    期   : 2013年11月18日
  作    者   : w00167002
  修改内容   : DTS2013112006986:控制在3G TDD模式下是否需要开启SMC验证标记:中国移动拉萨网络设备在
                TD下不发起SMC流程。
               默认需要进行SMC流程。 
*****************************************************************************/
VOS_VOID  NAS_UTRANCTRL_InitCustomCfgInfo(
    NAS_UTRANCTRL_CUSTOM_CFG_INFO_STRU   *pstCustomCfg
)
{
    NAS_UTRANCTRL_UTRAN_MODE_AUTO_SWITCH_STRU              *pstUtranModeAutoSwitch;

    pstUtranModeAutoSwitch                      = &(pstCustomCfg->stUtranModeAutoSwitch);

    /* 默认初始化为TDD模式 */
    pstCustomCfg->enCurrUtranMode               = NAS_UTRANCTRL_UTRAN_MODE_TDD;
    pstCustomCfg->enPreUtranMode                = NAS_UTRANCTRL_UTRAN_MODE_BUTT;

    pstCustomCfg->ucIsUtranTddCsSmcNeeded       = VOS_TRUE;
    pstCustomCfg->ucIsUtranTddPsSmcNeeded       = VOS_TRUE;

    pstCustomCfg->enCurUtranSwitchMode          = NAS_UTRANCTRL_UTRAN_SWITCH_MODE_FDD_ONLY;
    pstUtranModeAutoSwitch->ucUtranSwitchMode   = NAS_UTRANCTRL_UTRAN_SWITCH_MODE_FDD_ONLY;

    /* 默认中国网络列表个数为0个 */
    pstUtranModeAutoSwitch->ucTdMccListNum      = 0;

    /* 默认IMSI中的网络列表个数为0个 */
    pstUtranModeAutoSwitch->ucImsiPlmnListNum   = 0;

    /* 初始化保留字段 */
    PS_MEM_SET( pstUtranModeAutoSwitch->aucReserve,
                0,
                sizeof(pstUtranModeAutoSwitch->aucReserve) );

    /* 初始化TD网络国家列表 */
    PS_MEM_SET( pstUtranModeAutoSwitch->aulTdMccList,
                0,
                sizeof(pstUtranModeAutoSwitch->aulTdMccList) );

    /* 初始化IMSI PLMN LIST国家列表 */
    PS_MEM_SET( pstUtranModeAutoSwitch->astImsiPlmnList,
                0,
                sizeof(pstUtranModeAutoSwitch->astImsiPlmnList) );
}


/*****************************************************************************
 函 数 名  : NAS_UTRANCTRL_InitMsCfgCtx
 功能描述  : 初始化MML_CTX中手机配置相关信息
 输入参数  : pstMsCfgInfo:手机配置信息
 输出参数  : 无
 返 回 值  : 无
 调用函数  :
 被调函数  :

 修改历史      :
 1.日    期   : 2012年7月12日
   作    者   : w00167002
   修改内容   : 新生成函数
*****************************************************************************/
VOS_VOID  NAS_UTRANCTRL_InitMsCfgCtx(
    NAS_UTRANCTRL_MS_CFG_INFO_STRU       *pstMsCfgInfo
)
{

    NAS_UTRANCTRL_InitCustomCfgInfo(&(pstMsCfgInfo->stCustomCfg));
}

/*****************************************************************************
 函 数 名  : NAS_UTRANCTRL_InitCurrFsmCtx
 功能描述  : 初始化当前状态机上下文
 输入参数  : 无
 输出参数  : pstCurrFsmCtx:当前状态机上下文信息
 返 回 值  :
 调用函数  :
 被调函数  :

 修改历史      :
 1.日    期   : 2011年7月19日
   作    者   : w00167002
   修改内容   : 新生成函数

*****************************************************************************/
VOS_VOID  NAS_UTRANCTRL_InitCurrFsmCtx(
    NAS_UTRANCTRL_FSM_CTX_STRU         *pstCurrFsmCtx
)
{
    pstCurrFsmCtx->enFsmId                = NAS_UTRANCTRL_FSM_MAIN;
    pstCurrFsmCtx->pstFsmDesc             = NAS_UTRANCTRL_GetMainFsmDescAddr();
    pstCurrFsmCtx->ulState                = NAS_UTRANCTRL_MAIN_STA_INIT;
    pstCurrFsmCtx->stEntryMsg.ulEventType = 0;

    PS_MEM_SET(pstCurrFsmCtx->stEntryMsg.aucEntryMsgBuffer,
               0x00,
               NAS_UTRANCTRL_MAX_MSG_BUFFER_LEN);
}

/*****************************************************************************
 函 数 名  : NAS_UTRANCTRL_InitMainCtrlInfo
 功能描述  : 初始化当前UTRANCTRL模块的主控信息
 输入参数  : 无
 输出参数  : pstMainCtrl:当前UTRANCTRL模块的主控信息
 返 回 值  :
 调用函数  :
 被调函数  :

 修改历史      :
 1.日    期   : 2012年8月14日
   作    者   : w00167002
   修改内容   : 新生成函数
 2.日    期   : 2012年8月14日
   作    者   : w00176964
   修改内容   : 修改函数名
 3.日    期   : 2014年11月25日
   作    者   : z00161729
   修改内容   : 开机搜网优化项目修改

*****************************************************************************/
VOS_VOID  NAS_UTRANCTRL_InitMainCtrlInfo(
    NAS_UTRANCTRL_MAIN_CTRL_INFO_STRU  *pstMainCtrl
)
{
    /* 初始化当前主控信息 */
    pstMainCtrl->ucReplaceMmcMsgFlg     = VOS_FALSE;

    PS_MEM_SET( pstMainCtrl->aucReserve,
                (VOS_UINT8)0x00,
                sizeof(pstMainCtrl->aucReserve) );


    PS_MEM_SET( &(pstMainCtrl->stBufferUtranSndMmcMsg),
                (VOS_UINT8)0x00,
                sizeof(NAS_UTRANCTRL_ENTRY_MSG_STRU) );

    PS_MEM_SET( &(pstMainCtrl->stBufferMmcSndUtranMsg),
                (VOS_UINT8)0x00,
                sizeof(NAS_UTRANCTRL_ENTRY_MSG_STRU) );

    NAS_UTRANCTRL_SetSwithOnPlmnSearchFlag(VOS_FALSE);

    return;
}

/*****************************************************************************
 函 数 名  : NAS_UTRANCTRL_InitFsmBufferEntryMsgQueueCtx
 功能描述  : 初始化缓存消息队列上下文
 输入参数  : 无
 输出参数  : pstCurrFsmCtx:当前缓存消息队列上下文
 返 回 值  :
 调用函数  :
 被调函数  :

 修改历史      :
 1.日    期   : 2011年7月19日
   作    者   : w00167002
   修改内容   : 新生成函数

*****************************************************************************/
VOS_VOID  NAS_UTRANCTRL_InitFsmBufferEntryMsgQueueCtx(
    NAS_UTRANCTRL_MSG_QUEUE_STRU       *pstBufferEntryMsgQueue
)
{
    /* 初始化缓存消息队列上下文 */
    pstBufferEntryMsgQueue->ucCurrIndex   = 0;
    pstBufferEntryMsgQueue->ucCacheMsgNum = 0;

    PS_MEM_SET( pstBufferEntryMsgQueue->aucReserve,
                (VOS_UINT8)0x00,
                sizeof(pstBufferEntryMsgQueue->aucReserve) );


    PS_MEM_SET( pstBufferEntryMsgQueue->astMsgQueue,
                (VOS_UINT8)0x00,
                sizeof(pstBufferEntryMsgQueue->astMsgQueue) );

    return;
}

/*****************************************************************************
 函 数 名  : NAS_UTRANCTRL_InitFsmPlmnSearchCtrlCtx
 功能描述  : 初始化搜网控制上下文
 输入参数  : 无
 输出参数  : pstPlmnSearchCtrl:搜网控制结构上下文
 返 回 值  :
 调用函数  :
 被调函数  :

 修改历史      :
 1.日    期   : 2011年7月19日
   作    者   : w00167002
   修改内容   : 新生成函数

*****************************************************************************/
VOS_VOID  NAS_UTRANCTRL_InitFsmPlmnSearchCtrlCtx(
    NAS_UTRANCTRL_PLMN_SEARCH_CTRL_CTX_STRU       *pstPlmnSearchCtrl
)
{
    /* 初始化搜网控制结构上下文 */
    pstPlmnSearchCtrl->ucSearchedSpecTdMccFlg = VOS_FALSE;

    PS_MEM_SET( pstPlmnSearchCtrl->aucReserve,
                (VOS_UINT8)0x00,
                sizeof(pstPlmnSearchCtrl->aucReserve) );

    return;
}


/*****************************************************************************
 函 数 名  : NAS_UTRANCTRL_InitMaintainInfo
 功能描述  : 初始化UTRANCTRL_CTX中可维可测部分
 输入参数  : pstMaintainInfo:可维可测全局变量
 输出参数  : 无
 返 回 值  : 无
 调用函数  :
 被调函数  :

 修改历史      :
 1.日    期   : 2012年8月16日
   作    者   : w00167002
   修改内容   : 新生成函数

*****************************************************************************/
VOS_VOID  NAS_UTRANCTRL_InitMaintainInfo(
    NAS_UTRANCTRL_INIT_CTX_TYPE_ENUM_UINT8                  enInitType,
    NAS_UTRANCTRL_MAINTAIN_CTX_STRU                        *pstMaintainInfo
)
{
    /* 上电开机时才需要初始化如下变量 */
    if (NAS_UTRANCTRL_INIT_CTX_STARTUP != enInitType)
    {
        return;
    }

    /* 初始默认不发送PC回放消息 */
    pstMaintainInfo->stUeMaintainInfo.ucUeSndPcRecurFlg    = VOS_FALSE;

    /* 初始化保留字段为0 */
    PS_MEM_SET( pstMaintainInfo->stUeMaintainInfo.aucRsv3,
                (VOS_UINT8)0X00,
                sizeof(pstMaintainInfo->stUeMaintainInfo.aucRsv3) );

    return;
}


/*****************************************************************************
 函 数 名  : NAS_UTRANCTRL_SwitchCurrFsmCtx
 功能描述  : 切换当前的状态机的上下文
 输入参数  : 无
 输出参数  : enNewFsmId:新的状态机名称
 返 回 值  :
 调用函数  :
 被调函数  :

 修改历史      :
 1.日    期   : 2012年8月6日
   作    者   : w00176964
   修改内容   : 新生成函数
  2.日    期   : 2012年12月11日
    作    者   : l00167671
    修改内容   : DTS2012121802573, TQE清理
*****************************************************************************/
VOS_VOID  NAS_UTRANCTRL_SwitchCurrFsmCtx(
    NAS_UTRANCTRL_FSM_ID_ENUM_UINT32    enNewFsmId
)
{
    NAS_UTRANCTRL_FSM_CTX_STRU         *pstCurFsmCtx;
    NAS_UTRANCTRL_CTX_STRU             *pstCtx;

    pstCtx          = NAS_UTRANCTRL_GetUtranCtrlCtx();
    pstCurFsmCtx    = &(pstCtx->stCurFsm);

    if (VOS_NULL_PTR == pstCurFsmCtx->pstFsmDesc)
    {
        NAS_ERROR_LOG(WUEPS_PID_MMC, "NAS_UTRANCTRL_SwitchCurrFsmCtx:Invalid pstFsmDesc");
    }

    switch (enNewFsmId)
    {
        case NAS_UTRANCTRL_FSM_MAIN:
            pstCurFsmCtx->enFsmId                = enNewFsmId;
            pstCurFsmCtx->pstFsmDesc             = NAS_UTRANCTRL_GetMainFsmDescAddr();
            pstCurFsmCtx->ulState                = NAS_UTRANCTRL_MAIN_STA_INIT;
            break;

        case NAS_UTRANCTRL_FSM_SWITCH_ON:
            pstCurFsmCtx->enFsmId                = enNewFsmId;
            pstCurFsmCtx->pstFsmDesc             = NAS_UTRANCTRL_GetSwitchOnFsmDescAddr();
            pstCurFsmCtx->ulState                = NAS_UTRANCTRL_SWITCH_ON_STA_INIT;
            break;

        case NAS_UTRANCTRL_FSM_POWER_OFF:
            pstCurFsmCtx->enFsmId                = enNewFsmId;
            pstCurFsmCtx->pstFsmDesc             = NAS_UTRANCTRL_GetPowerOffFsmDescAddr();
            pstCurFsmCtx->ulState                = NAS_UTRANCTRL_POWER_OFF_STA_INIT;
            break;

        case NAS_UTRANCTRL_FSM_PLMN_SELECTION:
            pstCurFsmCtx->enFsmId                = enNewFsmId;
            pstCurFsmCtx->pstFsmDesc             = NAS_UTRANCTRL_GetPlmnSelectionFsmDescAddr();
            pstCurFsmCtx->ulState                = NAS_UTRANCTRL_PLMN_SELECTION_STA_INIT;
            break;

        case NAS_UTRANCTRL_FSM_SYSCFG:
            pstCurFsmCtx->enFsmId                = enNewFsmId;
            pstCurFsmCtx->pstFsmDesc             = NAS_UTRANCTRL_GetSysCfgFsmDescAddr();
            pstCurFsmCtx->ulState                = NAS_UTRANCTRL_SYSCFG_STA_INIT;
            break;

        case NAS_UTRANCTRL_FSM_MODE_CHANGE:
            pstCurFsmCtx->enFsmId                = enNewFsmId;
            pstCurFsmCtx->pstFsmDesc             = NAS_UTRANCTRL_GetModeChangeFsmDescAddr();
            pstCurFsmCtx->ulState                = NAS_UTRANCTRL_MODE_CHANGE_STA_INIT;
            break;

        default:
            NAS_ERROR_LOG(WUEPS_PID_MMC, "NAS_UTRANCTRL_SwitchCurrFsmCtx:Invalid Fsm Id");

            return;
    }

    /* 初始化UTRANCTRL状态机上下文 */
    pstCurFsmCtx->pstFsmDesc->pfInitHandle();

    /* 可维可测状态机信息打印 */
    NAS_UTRANCTRL_SndOmUtranCtrlFsmInfo();

    return;
}



/*****************************************************************************
 函 数 名  : NAS_UTRANCTRL_SaveCurEntryMsg
 功能描述  : 保存当前状态机的入口消息
 输入参数  : ulEventType            :入口消息类型
              pstMsg             :入口消息内容
 输出参数  : 无
 返 回 值  : VOS_VOID
 调用函数  :
 被调函数  :
 修改历史      :
  1.日    期   : 2012-08-6
    作    者   : W00176964
    修改内容   : 新生成函数

  2.日    期   : 2012年8月30日
    作    者   : w00167002
    修改内容   : 使用NAS_UTRANCTRL_ENTRY_MSG_STRU类型
*****************************************************************************/
VOS_VOID NAS_UTRANCTRL_SaveCurEntryMsg(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg
)
{
    NAS_UTRANCTRL_ENTRY_MSG_STRU       *pstEntryMsg  = VOS_NULL_PTR;

    MSG_HEADER_STRU                    *pstMsgHeader = VOS_NULL_PTR;
    VOS_UINT32                          ulLen;

    /* 获得当前UTRANCTRL模块状态机入口消息的缓冲区地址 */
    pstEntryMsg                 = NAS_UTRANCTRL_GetCurrEntryMsgAddr();
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
 函 数 名  : NAS_UTRANCTRL_FSM_SetCurrState
 功能描述  : 设置当前需要迁移的状态
 输入参数  : ulCurrState:当前迁移的状态
 输出参数  : 无
 返 回 值  :
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2012年8月7日
    作    者   : w00176964
    修改内容   : 新生成函数
*****************************************************************************/
VOS_VOID  NAS_UTRANCTRL_FSM_SetCurrState(
    VOS_UINT32                          ulCurrState
)
{
    NAS_UTRANCTRL_FSM_CTX_STRU         *pstCurFsm   = VOS_NULL_PTR;

    /* 获取当前的状态信息 */
    pstCurFsm                   = NAS_UTRANCTRL_GetCurFsmAddr();

    /* 设置当前状态 */
    pstCurFsm->ulState          = ulCurrState;

    /* 可维可测状态机信息打印 */
    NAS_UTRANCTRL_SndOmUtranCtrlFsmInfo();

    return;
}

/*****************************************************************************
 函 数 名  : NAS_UTRANCTRL_FSM_GetCurrState
 功能描述  : 获取当前的状态
 输入参数  : 无
 输出参数  : 无
 返 回 值  : ulCurrState:当前迁移的状态
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2012年8月15日
    作    者   : w00167002
    修改内容   : 新生成函数
*****************************************************************************/
VOS_UINT32 NAS_UTRANCTRL_FSM_GetCurrState(VOS_VOID)
{
    NAS_UTRANCTRL_FSM_CTX_STRU         *pstCurFsm   = VOS_NULL_PTR;

    /* 获取当前的状态机信息 */
    pstCurFsm                   = NAS_UTRANCTRL_GetCurFsmAddr();

    /* 获取当前状态 */
    return (pstCurFsm->ulState);
}

#endif

/*****************************************************************************
 函 数 名  : NAS_UTRANCTRL_InitCtx
 功能描述  : 开机初始化NAS_UTRANCTRL的时CTX
 输入参数  : 无
 输出参数  : 无
 返 回 值  : 无
 调用函数  :
 被调函数  :

 修改历史     :
 1.日    期   : 2012年7月12日
   作    者   : w00167002
   修改内容   : 新生成函数
 2.日    期   : 2012年8月7日
   作    者   : w00176964
   修改内容   : 修改注册状态机函数名
*****************************************************************************/
VOS_VOID  NAS_UTRANCTRL_InitCtx(
    VOS_UINT8                           ucInitType
)
{
#if (FEATURE_ON == FEATURE_UE_MODE_TDS)
    NAS_UTRANCTRL_CTX_STRU             *pstCtx;

    pstCtx = NAS_UTRANCTRL_GetUtranCtrlCtx();

    /* 初始化MS配置信息 */
    NAS_UTRANCTRL_InitMsCfgCtx(&(pstCtx->stMsCfgInfo));

    /* 初始化UTRANCTRL当前状态机上下文 */
    NAS_UTRANCTRL_InitCurrFsmCtx(&(pstCtx->stCurFsm));


    /* 初始化UTRANCTRL模块主控信息 */
    NAS_UTRANCTRL_InitMainCtrlInfo(&(pstCtx->stMainCtrlInfo));

    /* 初始化UTRANCTRL状态机缓存消息队列上下文 */
    NAS_UTRANCTRL_InitFsmBufferEntryMsgQueueCtx(&(pstCtx->stBufferEntryMsgQueue));

    /* 初始化UTRANCTRL状态机搜网控制上下文 */
    NAS_UTRANCTRL_InitFsmPlmnSearchCtrlCtx(&(pstCtx->stPlmnSearchCtrl));

    /* 初始化可维可测信息 */
    NAS_UTRANCTRL_InitMaintainInfo( ucInitType,
                                    &(pstCtx->stMaintainInfo));

    /* 状态机表的初始化 */
    NAS_UTRANCTRL_RegFsm();

#endif
}

/*****************************************************************************
 函 数 名  : NAS_UTRANCTRL_GetCurrUtranMode
 功能描述  : 获取当前的UTRAN模式,如果外部模块调用需要确保为驻留状态,否则可能会不准确
 输入参数  : 无
 输出参数  : 无
 返 回 值  : NAS_UTRANCTRL_UTRAN_MODE_ENUM_UINT8:当前的UTRAN模式
 调用函数  :
 被调函数  :

 修改历史      :
 1.日    期   : 2012年7月12日
   作    者   : w00167002
   修改内容   : 新建函数
 2.日    期   : 2012年8月14日
   作    者   : w00176964
   修改内容   : 根据UTRAN的切换模式获取工作模式
 3.日    期   : 2012年12月25日
   作    者   : s00217060
   修改内容   : for DSDA GUNAS C CORE:平台接入技术能力只支持W/TD中的一个时，
                UtranMode为TDD或FDD不变，两者都不支持时为BUTT
*****************************************************************************/
NAS_UTRANCTRL_UTRAN_MODE_ENUM_UINT8 NAS_UTRANCTRL_GetCurrUtranMode(VOS_VOID)
{
    /* !!获取当前的UTRAN模式,如果外部模块调用需要确保为驻留状态,否则可能会不准确 */
    
#if (FEATURE_ON == FEATURE_UE_MODE_TDS)
    VOS_UINT32                          ulSupportFddFlg;
    VOS_UINT32                          ulSupportTddFlg;

    ulSupportTddFlg = NAS_MML_IsPlatformSupportUtranTdd();
    ulSupportFddFlg = NAS_MML_IsPlatformSupportUtranFdd();
#endif

    /* 平台对W和TD都不支持时，UtranMode为BUTT */
    if (VOS_FALSE == NAS_MML_IsPlatformSupportUtran())
    {
        return NAS_UTRANCTRL_UTRAN_MODE_BUTT;
    }

#if (FEATURE_ON == FEATURE_UE_MODE_TDS)
    /* 平台接入技术能力只支持W时，UtranMode为FDD */
    if (VOS_FALSE == ulSupportTddFlg)
    {
        return NAS_UTRANCTRL_UTRAN_MODE_FDD;
    }

    /* 平台接入技术能力只支持TD时，UtranMode为TDD */
    if (VOS_FALSE == ulSupportFddFlg)
    {
        return NAS_UTRANCTRL_UTRAN_MODE_TDD;
    }

    if (NAS_UTRANCTRL_UTRAN_SWITCH_MODE_FDD_ONLY == NAS_UTRANCTRL_GetCurUtranSwitchMode())
    {
        return NAS_UTRANCTRL_UTRAN_MODE_FDD;
    }

    if (NAS_UTRANCTRL_UTRAN_SWITCH_MODE_TDD_ONLY == NAS_UTRANCTRL_GetCurUtranSwitchMode())
    {
        return NAS_UTRANCTRL_UTRAN_MODE_TDD;
    }

    return NAS_UTRANCTRL_GetUtranCtrlCtx()->stMsCfgInfo.stCustomCfg.enCurrUtranMode;
#else
    return NAS_UTRANCTRL_UTRAN_MODE_FDD;
#endif
}

/*****************************************************************************
 函 数 名  : NAS_UTRANCTRL_GetRatModeBasedOnUtranMode
 功能描述  : 将当前的utran mode值转换成相应的接入技术
 输入参数  : NAS_UTRANCTRL_UTRAN_MODE_ENUM_UINT8 enUtranMode
 输出参数  : 无
 返 回 值  : VOS_RATMODE_ENUM_UINT32
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2015年9月2日
    作    者   : w00242748
    修改内容   : 新生成函数

*****************************************************************************/
VOS_RATMODE_ENUM_UINT32 NAS_UTRANCTRL_GetRatModeBasedOnUtranMode(
    NAS_UTRANCTRL_UTRAN_MODE_ENUM_UINT8 enUtranMode
)
{
    VOS_RATMODE_ENUM_UINT32             enRatMode;

    enRatMode = VOS_RATMODE_BUTT;

    switch (enUtranMode)
    {
        case NAS_UTRANCTRL_UTRAN_MODE_FDD :
            enRatMode = VOS_RATMODE_WCDMA;
            break;

#if (FEATURE_ON == FEATURE_UE_MODE_TDS)
        case NAS_UTRANCTRL_UTRAN_MODE_TDD :
            enRatMode = VOS_RATMODE_TDS;
            break;
#endif

        default:
            enRatMode = VOS_RATMODE_BUTT;
            break;
    }

    return enRatMode;
}


/*****************************************************************************
 函 数 名  : NAS_UTRANCTRL_GetUtranTddCsSmcNeededFlg
 功能描述  : 获取UTRANCTRL中保存的UTRAN TDD模式下是否需要检测CS SMC流程
 输入参数  : 无
 输出参数  : 无
 返 回 值  : VOS_TRUE: UTRAN TDD模式下需要检测CS SMC流程
             VOS_FALSE:UTRAN TDD模式下不需要检测CS SMC流程
 调用函数  :
 被调函数  :

 修改历史      :
 1.日    期   : 2013年11月18日
   作    者   : w00167002
   修改内容   : 新建函数

*****************************************************************************/
VOS_UINT8 NAS_UTRANCTRL_GetUtranTddCsSmcNeededFlg(VOS_VOID)
{
#if (FEATURE_ON == FEATURE_UE_MODE_TDS)
   
    return (NAS_UTRANCTRL_GetUtranCtrlCtx()->stMsCfgInfo.stCustomCfg.ucIsUtranTddCsSmcNeeded);

#else

    /* 平台不开启TDD特性宏时候，则需要进行SMC */
    return VOS_TRUE;

#endif    
}


/*****************************************************************************
 函 数 名  : NAS_UTRANCTRL_GetUtranTddPsSmcNeededFlg
 功能描述  : 获取UTRANCTRL中保存的UTRAN TDD模式下是否需要检测PS SMC流程
 输入参数  : 无
 输出参数  : 无
 返 回 值  : VOS_TRUE: UTRAN TDD模式下需要检测PS SMC流程
             VOS_FALSE:UTRAN TDD模式下不需要检测PS SMC流程
 调用函数  :
 被调函数  :

 修改历史      :
 1.日    期   : 2013年11月18日
   作    者   : w00167002
   修改内容   : 新建函数

*****************************************************************************/
VOS_UINT8 NAS_UTRANCTRL_GetUtranTddPsSmcNeededFlg(VOS_VOID)
{
#if (FEATURE_ON == FEATURE_UE_MODE_TDS)
   
    return (NAS_UTRANCTRL_GetUtranCtrlCtx()->stMsCfgInfo.stCustomCfg.ucIsUtranTddPsSmcNeeded);

#else

    /* 平台不开启TDD特性宏时候，则需要进行SMC */
    return VOS_TRUE;

#endif    
}

/*****************************************************************************
 函 数 名  : NAS_UTRANCTRL_IsUtranCsSmcNeeded
 功能描述  : 获取UTRANCTRL中保存的UTRAN TDD模式下是否需要检测CS SMC流程
 输入参数  : 无
 输出参数  : 无
 返 回 值  : VOS_TRUE: UTRAN 模式下需要检测CS SMC流程
             VOS_FALSE:UTRAN 模式下不需要检测CS SMC流程
 调用函数  :
 被调函数  :

 修改历史      :
 1.日    期   : 2013年11月18日
   作    者   : w00167002
   修改内容   : 新建函数

*****************************************************************************/
VOS_UINT8 NAS_UTRANCTRL_IsUtranCsSmcNeeded(VOS_VOID)
{
    VOS_UINT8                           ucIsUtranTddCsSmcNeeded;

    ucIsUtranTddCsSmcNeeded             = NAS_UTRANCTRL_GetUtranTddCsSmcNeededFlg();
    
    /* 当前不在UTRAN模式下，则不需要UTRAN SMC检测 */
    if ( NAS_MML_NET_RAT_TYPE_WCDMA != NAS_MML_GetCurrNetRatType() )
    {
        return VOS_FALSE;
    }

    /* 当前在TDD模式下，且用户配置不需要CS SMC，则返回不需要SMC检测 */
    if ( (NAS_UTRANCTRL_UTRAN_MODE_TDD == NAS_UTRANCTRL_GetCurrUtranMode())
      && (VOS_FALSE                    == ucIsUtranTddCsSmcNeeded) )
    {
        return VOS_FALSE;
    }
    
    /* 当前在FDD模式下或者TDD时需要检测SMC时候，则需要进行SMC */
    return VOS_TRUE;

}


/*****************************************************************************
 函 数 名  : NAS_UTRANCTRL_IsUtranPsSmcNeeded
 功能描述  : 获取UTRANCTRL中保存的UTRAN TDD模式下是否需要检测PS SMC流程
 输入参数  : 无
 输出参数  : 无
 返 回 值  : VOS_TRUE: UTRAN 模式下需要检测PS SMC流程
             VOS_FALSE:UTRAN 模式下不需要检测PS SMC流程
 调用函数  :
 被调函数  :

 修改历史      :
 1.日    期   : 2013年11月18日
   作    者   : w00167002
   修改内容   : 新建函数

*****************************************************************************/
VOS_UINT8 NAS_UTRANCTRL_IsUtranPsSmcNeeded(VOS_VOID)
{
    VOS_UINT8                           ucIsUtranTddPsSmcNeeded;

    ucIsUtranTddPsSmcNeeded             = NAS_UTRANCTRL_GetUtranTddPsSmcNeededFlg();
    
    /* 当前不在UTRAN模式下，则不需要UTRAN SMC检测 */
    if ( NAS_MML_NET_RAT_TYPE_WCDMA != NAS_MML_GetCurrNetRatType() )
    {
        return VOS_FALSE;
    }

    /* 当前在TDD模式下，且用户配置不需要CS SMC，则返回不需要SMC检测 */
    if ( (NAS_UTRANCTRL_UTRAN_MODE_TDD == NAS_UTRANCTRL_GetCurrUtranMode())
      && (VOS_FALSE                    == ucIsUtranTddPsSmcNeeded) )
    {
        return VOS_FALSE;
    }
    
    /* 当前在FDD模式下或者TDD时需要检测SMC时候，则需要进行SMC */
    return VOS_TRUE;

}


#if (FEATURE_ON == FEATURE_UE_MODE_TDS)
/*****************************************************************************
 函 数 名  : NAS_UTRANCTRL_SetCurrUtranMode
 功能描述  : 设置UTRANCTRL中保存的UTRAN模式
 输入参数  : UTRAN模式
 输出参数  : 无
 返 回 值  : 无
 调用函数  :
 被调函数  :

 修改历史      :
 1.日    期   : 2012年7月12日
   作    者   : w00167002
   修改内容   : 新建函数

*****************************************************************************/
VOS_VOID NAS_UTRANCTRL_SetCurrUtranMode(
    NAS_UTRANCTRL_UTRAN_MODE_ENUM_UINT8 enUtranMode
)
{
    NAS_UTRANCTRL_GetUtranCtrlCtx()->stMsCfgInfo.stCustomCfg.enCurrUtranMode = enUtranMode;

    return;
}


/*****************************************************************************
 函 数 名  : NAS_UTRANCTRL_SetUtranTddCsSmcNeededFlg
 功能描述  : 设置UTRANCTRL中保存的UTRAN TDD模式下是否需要检测CS SMC流程
 输入参数  : ucIsUtranTddSmcNeeded
 输出参数  : 无
 返 回 值  : 无
 调用函数  :
 被调函数  :

 修改历史      :
 1.日    期   : 2013年11月18日
   作    者   : w00167002
   修改内容   : 新建函数

*****************************************************************************/
VOS_VOID NAS_UTRANCTRL_SetUtranTddCsSmcNeededFlg(
    VOS_UINT8                           ucIsUtranTddCsSmcNeeded
)
{
    NAS_UTRANCTRL_GetUtranCtrlCtx()->stMsCfgInfo.stCustomCfg.ucIsUtranTddCsSmcNeeded = ucIsUtranTddCsSmcNeeded;

    return;
}

/*****************************************************************************
 函 数 名  : NAS_UTRANCTRL_SetUtranTddPsSmcNeededFlg
 功能描述  : 设置UTRANCTRL中保存的UTRAN TDD模式下是否需要检测PS SMC流程
 输入参数  : ucIsUtranTddSmcNeeded
 输出参数  : 无
 返 回 值  : 无
 调用函数  :
 被调函数  :

 修改历史      :
 1.日    期   : 2013年11月18日
   作    者   : w00167002
   修改内容   : 新建函数

*****************************************************************************/
VOS_VOID NAS_UTRANCTRL_SetUtranTddPsSmcNeededFlg(
    VOS_UINT8                           ucIsUtranTddPsSmcNeeded
)
{
    NAS_UTRANCTRL_GetUtranCtrlCtx()->stMsCfgInfo.stCustomCfg.ucIsUtranTddPsSmcNeeded = ucIsUtranTddPsSmcNeeded;

    return;
}


/*****************************************************************************
 函 数 名  : NAS_UTRANCTRL_SetSwithOnPlmnSearchFlag
 功能描述  : 设置UTRANCTRL模块中是否为开机搜网场景
 输入参数  : ucSwitchOnPlmnSearchFlag - 是否是开机搜网
 输出参数  : 无
 返 回 值  : 无
 调用函数  :
 被调函数  :

 修改历史      :
 1.日    期   : 2014年11月25日
   作    者   : z00161729
   修改内容   : 开机搜网优化项目修改

*****************************************************************************/
VOS_VOID NAS_UTRANCTRL_SetSwithOnPlmnSearchFlag(
    VOS_UINT8                           ucSwitchOnPlmnSearchFlag
)
{
    NAS_UTRANCTRL_GetUtranCtrlCtx()->stMainCtrlInfo.ucSwitchOnPlmnSearchFlag = ucSwitchOnPlmnSearchFlag;
}


/*****************************************************************************
 函 数 名  : NAS_UTRANCTRL_GetSwithOnPlmnSearchFlag
 功能描述  : 获取UTRANCTRL模块中是否为开机搜网场景标识
 输入参数  : 无
 输出参数  : 无
 返 回 值  : 开机搜网标识
 调用函数  :
 被调函数  :

 修改历史      :
 1.日    期   : 2014年11月25日
   作    者   : z00161729
   修改内容   : 开机搜网优化项目修改

*****************************************************************************/
VOS_UINT8 NAS_UTRANCTRL_GetSwithOnPlmnSearchFlag(VOS_VOID)
{
    return NAS_UTRANCTRL_GetUtranCtrlCtx()->stMainCtrlInfo.ucSwitchOnPlmnSearchFlag;
}




/*****************************************************************************
 函 数 名  : NAS_UTRANCTRL_SetReplaceMmcMsgFlg
 功能描述  : 设置UTRANCTRL模块中替换MMC消息的标记
 输入参数  : ucReplaceFlg
 输出参数  : 无
 返 回 值  : 无
 调用函数  :
 被调函数  :

 修改历史      :
 1.日    期   : 2012年8月8日
   作    者   : w00176964
   修改内容   : 新建函数

*****************************************************************************/
VOS_VOID NAS_UTRANCTRL_SetReplaceMmcMsgFlg(
    VOS_UINT8                           ucReplaceFlg
)
{
    NAS_UTRANCTRL_GetUtranCtrlCtx()->stMainCtrlInfo.ucReplaceMmcMsgFlg = ucReplaceFlg;
}

/*****************************************************************************
 函 数 名  : NAS_UTRANCTRL_GetReplaceMmcMsgFlg
 功能描述  : 获取UTRANCTRL模块中替换MMC消息的标记
 输入参数  : 无
 输出参数  : 无
 返 回 值  : UTRANCTRL模块中替换MMC消息的标记
 调用函数  :
 被调函数  :

 修改历史      :
 1.日    期   : 2012年8月8日
   作    者   : w00176964
   修改内容   : 新建函数

*****************************************************************************/
VOS_UINT8 NAS_UTRANCTRL_GetReplaceMmcMsgFlg(VOS_VOID)
{
    return (NAS_UTRANCTRL_GetUtranCtrlCtx()->stMainCtrlInfo.ucReplaceMmcMsgFlg);
}

/*****************************************************************************
 函 数 名  : NAS_UTRANCTRL_GetPreUtranMode
 功能描述  : 获取UTRANCTRL中保存的上次发给RRC的UTRAN模式
 输入参数  : 无
 输出参数  : 无
 返 回 值  : UTRANCTRL中保存的UTRAN模式
 调用函数  :
 被调函数  :

 修改历史      :
 1.日    期   : 2012年7月12日
   作    者   : w00167002
   修改内容   : 新建函数

*****************************************************************************/
NAS_UTRANCTRL_UTRAN_MODE_ENUM_UINT8 NAS_UTRANCTRL_GetPreUtranMode(VOS_VOID)
{
    return NAS_UTRANCTRL_GetUtranCtrlCtx()->stMsCfgInfo.stCustomCfg.enPreUtranMode;
}

/*****************************************************************************
 函 数 名  : NAS_UTRANCTRL_SetPreUtranMode
 功能描述  : 设置UTRANCTRL中保存的上次发给RRC的UTRAN模式
 输入参数  : UTRAN模式
 输出参数  : 无
 返 回 值  : 无
 调用函数  :
 被调函数  :

 修改历史      :
 1.日    期   : 2012年7月12日
   作    者   : w00167002
   修改内容   : 新建函数

*****************************************************************************/
VOS_VOID NAS_UTRANCTRL_SetPreUtranMode(
    NAS_UTRANCTRL_UTRAN_MODE_ENUM_UINT8 enUtranMode
)
{
    NAS_UTRANCTRL_GetUtranCtrlCtx()->stMsCfgInfo.stCustomCfg.enPreUtranMode = enUtranMode;

    return;
}

/*****************************************************************************
 函 数 名  : NAS_UTRANCTRL_GetCurFsmAddr
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
NAS_UTRANCTRL_FSM_CTX_STRU* NAS_UTRANCTRL_GetCurFsmAddr(VOS_VOID)
{
    return &(NAS_UTRANCTRL_GetUtranCtrlCtx()->stCurFsm);
}

/*****************************************************************************
 函 数 名  : NAS_UTRANCTRL_GetCurFsmDesc
 功能描述  : 获取当前状态机表的地址
 输入参数  : 无
 输出参数  : 无
 返 回 值  : 当前状态机表的地址
 调用函数  :
 被调函数  :

 修改历史      :
 1.日    期   : 2012年7月19日
   作    者   : w00167002
   修改内容   : 新生成函数

*****************************************************************************/
NAS_FSM_DESC_STRU* NAS_UTRANCTRL_GetCurFsmDesc(VOS_VOID)
{
    return (NAS_UTRANCTRL_GetUtranCtrlCtx()->stCurFsm.pstFsmDesc);
}

/*****************************************************************************
 函 数 名  : NAS_UTRANCTRL_GetCurrEntryMsgAddr
 功能描述  : 获取当前状态机入口消息的地址
 输入参数  : 无
 输出参数  : 无
 返 回 值  : 当前状态机入口消息的地址
 调用函数  :
 被调函数  :

 修改历史      :
 1.日    期   : 2012年7月19日
   作    者   : w00167002
   修改内容   : 新生成函数
*****************************************************************************/
NAS_UTRANCTRL_ENTRY_MSG_STRU* NAS_UTRANCTRL_GetCurrEntryMsgAddr(VOS_VOID)
{
    return &(NAS_UTRANCTRL_GetUtranCtrlCtx()->stCurFsm.stEntryMsg);
}

/*****************************************************************************
 函 数 名  : NAS_UTRANCTRL_GetCurrFsmId
 功能描述  : 获取当前状态机的ID
 输入参数  : 无
 输出参数  : 无
 返 回 值  : 当前状态机的ID
 调用函数  :
 被调函数  :

 修改历史      :
 1.日    期   : 2012年7月19日
   作    者   : w00167002
   修改内容   : 新生成函数

*****************************************************************************/
NAS_UTRANCTRL_FSM_ID_ENUM_UINT32 NAS_UTRANCTRL_GetCurrFsmId(VOS_VOID)
{
    return (NAS_UTRANCTRL_GetUtranCtrlCtx()->stCurFsm.enFsmId);
}



/*****************************************************************************
 函 数 名  : NAS_UTRANCTRL_GetCachMsgBufferAddr
 功能描述  : 获取当前的缓存消息地址
 输入参数  : 无
 输出参数  : 无
 返 回 值  : NAS UTRANCTRL缓存消息队列
 调用函数  :
 被调函数  :

 修改历史      :
 1.日    期   : 2012年8月7日
   作    者   : W00176964
   修改内容   : 新生成函数

*****************************************************************************/
NAS_UTRANCTRL_MSG_QUEUE_STRU* NAS_UTRANCTRL_GetCachMsgBufferAddr(VOS_VOID)
{
    return &(NAS_UTRANCTRL_GetUtranCtrlCtx()->stBufferEntryMsgQueue);
}

/*****************************************************************************
 函 数 名  : NAS_UTRANCTRL_ClearCacheMsg
 功能描述  : 清除指定的缓存消息
 输入参数  : ulEventType:清除需求缓存的消息类型
 输出参数  : 无
 返 回 值  : VOS_VOID
 调用函数  :
 被调函数  :

 修改历史      :
 1.日    期   : 2015年11月05日
   作    者   : z00161729
   修改内容   : 新生成函数

*****************************************************************************/
VOS_VOID NAS_UTRANCTRL_ClearCacheMsg(
    VOS_UINT32                          ulEventType
)
{
    VOS_INT8                            i;
    VOS_INT8                            cCachePos;
    NAS_UTRANCTRL_MSG_QUEUE_STRU       *pstBufferMsgQueue   = VOS_NULL_PTR;

    pstBufferMsgQueue = NAS_UTRANCTRL_GetCachMsgBufferAddr();
    cCachePos         = -1;

    /* 先找到需要被清除的缓存 */
    for ( i = 0 ; i < pstBufferMsgQueue->ucCacheMsgNum ; i++ )
    {
        if ( ulEventType == pstBufferMsgQueue->astMsgQueue[i].stMsgEntry.ulEventType )
        {
            PS_MEM_SET(&(pstBufferMsgQueue->astMsgQueue[i].stMsgEntry),
                       0x00,
                       sizeof(NAS_UTRANCTRL_ENTRY_MSG_STRU));
            cCachePos = (VOS_INT8)i;
        }
    }

    /* 未找到该消息类型直接返回 */
    if ( -1 == cCachePos )
    {
        return;
    }

    /* 为保证先入先出,需要将后面的消息移到前面 */
    for ( i = cCachePos ; i < (pstBufferMsgQueue->ucCacheMsgNum - 1) ; i++ )
    {
        /* COPY消息内容 */
        PS_MEM_CPY(&(pstBufferMsgQueue->astMsgQueue[i].stMsgEntry),
                   &(pstBufferMsgQueue->astMsgQueue[i + 1].stMsgEntry),
                   sizeof(NAS_UTRANCTRL_ENTRY_MSG_STRU));

    }

    /* 将缓存个数减一 */
    pstBufferMsgQueue->ucCacheMsgNum--;

    /* 可维可测缓存队列信息打印 */
    NAS_UTRANCTRL_SndOmBufferQueueMsg();

    return;
}



/*****************************************************************************
 函 数 名  : NAS_UTRANCTRL_InitCachBufferMsgQueue
 功能描述  : 初始化外部队列消息
 输入参数  : 无
 输出参数  : 无
 返 回 值  : 无
 调用函数  :
 被调函数  :

 修改历史      :
 1.日    期   : 2012年8月8日
   作    者   : w00167002
   修改内容   : 新生成函数

*****************************************************************************/
VOS_VOID NAS_UTRANCTRL_InitCachBufferMsgQueue( VOS_VOID )
{
    NAS_UTRANCTRL_MSG_QUEUE_STRU       *pstBufferMsgQueue;

    pstBufferMsgQueue                   = NAS_UTRANCTRL_GetCachMsgBufferAddr();

    /* 将索引以及缓存的个数清零 */
    pstBufferMsgQueue->ucCurrIndex      = 0;
    pstBufferMsgQueue->ucCacheMsgNum    = 0;

    /* 将消息内容清空 */
    PS_MEM_SET(pstBufferMsgQueue->aucReserve, 0X0, sizeof(pstBufferMsgQueue->aucReserve));
    PS_MEM_SET(pstBufferMsgQueue->astMsgQueue, 0X0, sizeof(NAS_UTRANCTRL_CACH_MSG_INFO_STRU));

    return;
}

/*****************************************************************************
 函 数 名  : NAS_UTRANCTRL_GetNextCachBufferMsg
 功能描述  : 获取下一条可用的外部消息
 输入参数  : 无
 输出参数  : 无
 返 回 值  : 内部消息队列的指针
 调用函数  :
 被调函数  :

 修改历史      :
 1.日    期   : 2012年8月8日
   作    者   : w00167002
   修改内容   : 新生成函数

*****************************************************************************/
VOS_VOID* NAS_UTRANCTRL_GetNextCachBufferMsg( VOS_VOID )
{
    NAS_UTRANCTRL_MSG_QUEUE_STRU       *pstBufferMsgQueue;
    NAS_UTRANCTRL_ENTRY_MSG_STRU       *pstMsgEntry;

    pstBufferMsgQueue = NAS_UTRANCTRL_GetCachMsgBufferAddr();

    /* 如果消息已取完，返回VOS_NULL_PTR */
    if ( pstBufferMsgQueue->ucCacheMsgNum <= pstBufferMsgQueue->ucCurrIndex)
    {
        NAS_UTRANCTRL_InitCachBufferMsgQueue();

        return VOS_NULL_PTR;
    }

    pstMsgEntry = &(pstBufferMsgQueue->astMsgQueue[pstBufferMsgQueue->ucCurrIndex].stMsgEntry);

    /* 指向下一条缓存的外部消息 */
    pstBufferMsgQueue->ucCurrIndex++;

    /* 可维可测缓存队列信息打印 */
    NAS_UTRANCTRL_SndOmBufferQueueMsg();

    /* 返回取得缓存的外部消息 */
    return (VOS_VOID*)(pstMsgEntry->aucEntryMsgBuffer);

}

/*****************************************************************************
 函 数 名  : NAS_UTRANCTRL_SaveCacheMsgInMsgQueue
 功能描述  : 将缓存消息保存的缓存内存池中
 输入参数  : ulEventType:消息ID+PID
             pMsg      :消息内容
 输出参数  : 无
 返 回 值  :
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2012年8月6日
    作    者   : w00176964
    修改内容   : 新生成函数
  2.日    期   : 2012年9月15日
    作    者   : w00167002
    修改内容   : 如果消息长度超过了缓存的长度，则不保存, 防止数组越界

*****************************************************************************/
VOS_VOID  NAS_UTRANCTRL_SaveCacheMsgInMsgQueue(
    VOS_UINT32                          ulEventType,
    VOS_VOID                           *pstMsg
)
{
    NAS_UTRANCTRL_MSG_QUEUE_STRU       *pstMsgQueue   = VOS_NULL_PTR;
    MSG_HEADER_STRU                    *pstMsgHeader  = VOS_NULL_PTR;

    pstMsgHeader = (MSG_HEADER_STRU*)pstMsg;

    pstMsgQueue = NAS_UTRANCTRL_GetCachMsgBufferAddr();

    if ( pstMsgQueue->ucCacheMsgNum >= NAS_UTRANCTRL_MAX_MSG_QUEUE_NUM )
    {
        /* 可维可测缓存队列信息打印 */
        NAS_UTRANCTRL_SndOmBufferQueueMsg();

        NAS_ERROR_LOG(WUEPS_PID_MMC, "NAS_UTRANCTRL_SaveCacheMsgInMsgQueue:No Empty buffer");

        return ;
    }

    /* 消息长度超过了缓存的长度，则不保存, 防止数组越界 */
    if ( (pstMsgHeader->ulLength + VOS_MSG_HEAD_LENGTH) > NAS_UTRANCTRL_MAX_MSG_BUFFER_LEN )
    {
        NAS_WARNING_LOG(WUEPS_PID_MMC, "NAS_UTRANCTRL_SaveCacheMsgInMsgQueue:Msg too big to save ");
        return ;
    }

    pstMsgQueue->astMsgQueue[pstMsgQueue->ucCacheMsgNum].stMsgEntry.ulEventType   = ulEventType;
    PS_MEM_CPY((pstMsgQueue->astMsgQueue[pstMsgQueue->ucCacheMsgNum].stMsgEntry.aucEntryMsgBuffer),
               pstMsg,
               pstMsgHeader->ulLength + VOS_MSG_HEAD_LENGTH);
    pstMsgQueue->ucCacheMsgNum++;

    /* 可维护可测缓存队列信息打印 */
    NAS_UTRANCTRL_SndOmBufferQueueMsg();

    return;
}

/*****************************************************************************
 函 数 名  : NAS_UTRANCTRL_GetCurrFsmEventType
 功能描述  : 获取当前状态机的消息类型
 输入参数  : 无
 输出参数  : 无
 返 回 值  : 当前状态机的消息类型
 调用函数  :
 被调函数  :

 修改历史      :
 1.日    期   : 2012年7月19日
   作    者   : w00167002
   修改内容   : 新生成函数

*****************************************************************************/
VOS_UINT32 NAS_UTRANCTRL_GetCurrFsmEventType(VOS_VOID)
{
    return (NAS_UTRANCTRL_GetUtranCtrlCtx()->stCurFsm.stEntryMsg.ulEventType);
}


/*****************************************************************************
 函 数 名  : NAS_UTRANCTRL_SaveBufferedSndUtranReqMsg
 功能描述  : 保存缓存的发送给W/TD的请求消息
 输入参数  : 无
 输出参数  : 无
 返 回 值  : 无
 调用函数  :
 被调函数  :
 修改历史      :
  1.日    期   : 2012-08-6
    作    者   : W00176964
    修改内容   : 新生成函数
  2.日    期   : 2012年9月15日
    作    者   : w00167002
    修改内容   : 如果消息长度超过了缓存的长度，则不保存, 防止数组越界
*****************************************************************************/
VOS_VOID NAS_UTRANCTRL_SaveBufferedSndUtranReqMsg(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg
)
{
    NAS_UTRANCTRL_ENTRY_MSG_STRU       *pstEntryMsg  = VOS_NULL_PTR;
    MSG_HEADER_STRU                    *pstMsgHeader = VOS_NULL_PTR;
    VOS_UINT32                          ulLen;

    /* 获得当前缓存的发送给UTRAN的请求消息的缓冲区地址 */
    pstEntryMsg                 =   NAS_UTRANCTRL_GetBufferedSndUtranReqMsgAddr();
    pstMsgHeader                =   (MSG_HEADER_STRU*)pstMsg;

    /* 如果是空消息 */
    if ( VOS_NULL_PTR == pstMsg )
    {
        pstEntryMsg->ulEventType    =   ulEventType;
        NAS_WARNING_LOG( WUEPS_PID_MMC, "NAS_UTRANCTRL_SaveBufferedSndUtranReqMsg Entry Message Pointer is NULL!" );
        return;
    }

    ulLen                       = pstMsgHeader->ulLength + VOS_MSG_HEAD_LENGTH;

    /* 消息长度超过了缓存的长度，则不保存, 防止数组越界 */
    if ( ulLen > NAS_UTRANCTRL_MAX_MSG_BUFFER_LEN )
    {
        NAS_ERROR_LOG(WUEPS_PID_MMC, "NAS_UTRANCTRL_SaveBufferedSndUtranReqMsg:Msg too big to save ");
        return ;
    }

    /* 将当前处理的入口消息拷贝到Context对应的缓冲区 */
    PS_MEM_CPY( pstEntryMsg->aucEntryMsgBuffer, pstMsg, ulLen );

    /* 填写Context中的参数 */
    pstEntryMsg->ulEventType    =   ulEventType;

    return;
}

/*****************************************************************************
 函 数 名  : NAS_UTRANCTRL_ClearBufferedSndUtranReqMsg
 功能描述  : 清空缓存的发送给UTRAN的请求消息
 输入参数  : 无
 输出参数  : 无
 返 回 值  : 无
 调用函数  :
 被调函数  :
 修改历史      :
  1.日    期   : 2012-08-6
    作    者   : W00176964
    修改内容   : 新生成函数
*****************************************************************************/
VOS_VOID NAS_UTRANCTRL_ClearBufferedSndUtranReqMsg(VOS_VOID)
{
    NAS_UTRANCTRL_ENTRY_MSG_STRU       *pstEntryMsg  = VOS_NULL_PTR;

    /* 获得当前缓存的发送给UTRAN的请求消息的缓冲区地址 */
    pstEntryMsg                 =   NAS_UTRANCTRL_GetBufferedSndUtranReqMsgAddr();

     /* 清空对应的缓冲区 */
    PS_MEM_SET(pstEntryMsg, (VOS_UINT8)0x00, sizeof(NAS_UTRANCTRL_ENTRY_MSG_STRU));
}

/*****************************************************************************
 函 数 名  : NAS_UTRANCTRL_GetBufferedSndUtranReqMsgAddr
 功能描述  : 获取状态机缓存的发送给UTRAN的请求消息地址
 输入参数  : 无
 输出参数  : 无
 返 回 值  : 缓存的发送给UTRAN的请求消息地址
 调用函数  :
 被调函数  :
 修改历史      :
  1.日    期   : 2012-08-6
    作    者   : W00176964
    修改内容   : 新生成函数
*****************************************************************************/
NAS_UTRANCTRL_ENTRY_MSG_STRU* NAS_UTRANCTRL_GetBufferedSndUtranReqMsgAddr(VOS_VOID)
{
    return &(NAS_UTRANCTRL_GetUtranCtrlCtx()->stMainCtrlInfo.stBufferMmcSndUtranMsg);
}

/*****************************************************************************
 函 数 名  : NAS_UTRANCTRL_GetBufferedPlmnSearchReqType
 功能描述  : 获取状态机缓存的搜网请求类型
 输入参数  : 无
 输出参数  : 无
 返 回 值  : 缓存的搜网请求类型
 调用函数  :
 被调函数  :
 修改历史      :
  1.日    期   : 2012-08-15
    作    者   : W00176964
    修改内容   : 新生成函数
  2.日    期   : 2012-08-24
    作    者   : W00167002
    修改内容   : 取缓存的消息发送PID是WUEPS_PID_MMC，而不是WRR
*****************************************************************************/
VOS_UINT32 NAS_UTRANCTRL_GetBufferedPlmnSearchReqType(VOS_VOID)
{
    RRMM_PLMN_SEARCH_REQ_STRU           stPlmnSearchReqMsg;
    VOS_UINT32                          ulEventType;

    ulEventType = NAS_UTRANCTRL_GetBufferedSndUtranReqMsgAddr()->ulEventType;


    /* 当期缓存的UTRAN的请求消息如果不是指定搜网请求消息则说明有异常 */
    if (ulEventType != NAS_BuildEventType(WUEPS_PID_MMC, RRMM_PLMN_SEARCH_REQ))
    {
        NAS_WARNING_LOG( WUEPS_PID_MMC, "NAS_UTRANCTRL_GetBufferedPlmnSearchReqType Invalid Event type!" );

        return RRC_PLMN_SEARCH_TYPE_BUTT;
    }

    stPlmnSearchReqMsg = *(RRMM_PLMN_SEARCH_REQ_STRU*)(NAS_UTRANCTRL_GetBufferedSndUtranReqMsgAddr()->aucEntryMsgBuffer);

    return stPlmnSearchReqMsg.ulSearchType;
}

/*****************************************************************************
 函 数 名  : NAS_UTRANCTRL_GetSearchedSpecTdMccFlg
 功能描述  : 获取搜到指定td的MCC的标记
 输入参数  : 无
 输出参数  : 无
 返 回 值  : VOS_UINT8:搜到指定TD的MCC的标记
 调用函数  :
 被调函数  :
 修改历史      :
  1.日    期   : 2012-08-6
    作    者   : W00176964
    修改内容   : 新生成函数
*****************************************************************************/
VOS_UINT8 NAS_UTRANCTRL_GetSearchedSpecTdMccFlg(VOS_VOID)
{
    return (NAS_UTRANCTRL_GetUtranCtrlCtx()->stPlmnSearchCtrl.ucSearchedSpecTdMccFlg);
}



/*****************************************************************************
 函 数 名  : NAS_UTRANCTRL_GetSpecTdMccListNum
 功能描述  : 获取定制的TD国家码列表个数
 输入参数  : 无
 输出参数  : 定制的国家码列表个数
 返 回 值  : 无
 调用函数  :
 被调函数  :

 修改历史      :
 1.日    期   : 2012年8月10日
   作    者   : w00176964
   修改内容   : 新生成函数

*****************************************************************************/
VOS_UINT8   NAS_UTRANCTRL_GetSpecTdMccListNum(VOS_VOID)
{
    return (NAS_UTRANCTRL_GetUtranCtrlCtx()->stMsCfgInfo.stCustomCfg.stUtranModeAutoSwitch.ucTdMccListNum);
}

/*****************************************************************************
 函 数 名  : NAS_UTRANCTRL_GetSpecTdMccList
 功能描述  : 获取定制的TD国家码列表
 输入参数  : 无
 输出参数  : pulMcc 定制的TD国家码列表
 返 回 值  : 无
 调用函数  :
 被调函数  :

 修改历史      :
 1.日    期   : 2012年8月10日
   作    者   : w00176964
   修改内容   : 新生成函数

*****************************************************************************/
VOS_UINT32* NAS_UTRANCTRL_GetSpecTdMccList(VOS_VOID)
{
    return NAS_UTRANCTRL_GetUtranCtrlCtx()->stMsCfgInfo.stCustomCfg.stUtranModeAutoSwitch.aulTdMccList;
}

/*****************************************************************************
 函 数 名  : NAS_UTRANCTRL_SetCurUtranSwitchMode
 功能描述  : 设置当前UTRAN的切换模式
 输入参数  : ucSwitchMode:UTRAND的切换模式
 输出参数  : 无
 返 回 值  : 无
 调用函数  :
 被调函数  :
 修改历史      :
  1.日    期   : 2012-08-6
    作    者   : W00176964
    修改内容   : 新生成函数
  2.日    期   : 2012-08-10
    作    者   : W00176964
    修改内容   : 修改函数名
*****************************************************************************/
VOS_VOID  NAS_UTRANCTRL_SetCurUtranSwitchMode(
    VOS_UINT8                               ucSwitchMode
)
{
    (NAS_UTRANCTRL_GetUtranCtrlCtx()->stMsCfgInfo.stCustomCfg.enCurUtranSwitchMode) = ucSwitchMode;
}

/*****************************************************************************
 函 数 名  : NAS_UTRANCTRL_GetUePcRecurFlg
 功能描述  : 获取当前的UE侧的PC回放标志
 输入参数  : 无
 输出参数  : 无
 返 回 值  : 当前的UE侧的PC回放标志
 调用函数  :
 被调函数  :

 修改历史      :
 1.日    期   : 2012年08月16日
   作    者   : w00167002
   修改内容   : 新生成函数

*****************************************************************************/
VOS_UINT8 NAS_UTRANCTRL_GetUePcRecurFlg(VOS_VOID)
{
    return (NAS_UTRANCTRL_GetUtranCtrlCtx()->stMaintainInfo.stUeMaintainInfo.ucUeSndPcRecurFlg);
}

/*****************************************************************************
 函 数 名  : NAS_UTRANCTRL_SetUePcRecurFlg
 功能描述  : 更新UE的PC回放使能标志
 输入参数  : ucUePcRecurFlg: UE侧的PC回放标志
 输出参数  : 无
 返 回 值  :
 调用函数  :
 被调函数  :

 修改历史      :
 1.日    期   : 2012年08月16日
   作    者   : w00167002
   修改内容   : 新生成函数

*****************************************************************************/
VOS_VOID NAS_UTRANCTRL_SetUePcRecurFlg(
    VOS_UINT8                           ucUePcRecurFlg
)
{
    NAS_UTRANCTRL_GetUtranCtrlCtx()->stMaintainInfo.stUeMaintainInfo.ucUeSndPcRecurFlg = ucUePcRecurFlg;
}


/*****************************************************************************
 函 数 名  : NAS_UTRANCTRL_GetCurUtranSwitchMode
 功能描述  : 获取UTRAN的切换模式
 输入参数  : 无
 输出参数  : 无
 返 回 值  : VOS_UINT8:UTRAN的切换模式
 调用函数  :
 被调函数  :
 修改历史      :
  1.日    期   : 2012-08-6
    作    者   : W00176964
    修改内容   : 新生成函数
  2.日    期   : 2012-08-14
    作    者   : W00176964
    修改内容   : 修改函数名
*****************************************************************************/
VOS_UINT8 NAS_UTRANCTRL_GetCurUtranSwitchMode(VOS_VOID)
{
    return (NAS_UTRANCTRL_GetUtranCtrlCtx()->stMsCfgInfo.stCustomCfg.enCurUtranSwitchMode);
}

/*****************************************************************************
 函 数 名  : NAS_UTRANCTRL_InitFsmCtx_Main
 功能描述  : 初始化主状态机上下文
 输入参数  : 无
 输出参数  : 无
 返 回 值  :
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2012年8月7日
    作    者   : w00176964
    修改内容   : 新生成函数

*****************************************************************************/

VOS_VOID  NAS_UTRANCTRL_InitFsmCtx_Main(VOS_VOID)
{
    return;
}

/*****************************************************************************
 函 数 名  : NAS_UTRANCTRL_InitFsmCtx_SwitchOn
 功能描述  : 初始化开机状态机上下文
 输入参数  : 无
 输出参数  : 无
 返 回 值  :
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2012年8月7日
    作    者   : w00176964
    修改内容   : 新生成函数

*****************************************************************************/

VOS_VOID  NAS_UTRANCTRL_InitFsmCtx_SwitchOn(VOS_VOID)
{
    return;
}

/*****************************************************************************
 函 数 名  : NAS_UTRANCTRL_InitFsmCtx_PowerOff
 功能描述  : 初始化关机状态机上下文
 输入参数  : 无
 输出参数  : 无
 返 回 值  :
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2012年8月7日
    作    者   : w00176964
    修改内容   : 新生成函数

*****************************************************************************/

VOS_VOID  NAS_UTRANCTRL_InitFsmCtx_PowerOff(VOS_VOID)
{
    return;
}

/*****************************************************************************
 函 数 名  : NAS_UTRANCTRL_InitFsmCtx_PlmnSelection
 功能描述  : 初始化搜网状态机上下文
 输入参数  : 无
 输出参数  : 无
 返 回 值  :
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2012年8月7日
    作    者   : w00176964
    修改内容   : 新生成函数

*****************************************************************************/

VOS_VOID  NAS_UTRANCTRL_InitFsmCtx_PlmnSelection(VOS_VOID)
{
    NAS_UTRANCTRL_SetAbortFlg_PlmnSelection(VOS_FALSE);

    NAS_UTRANCTRL_SetRcvMmcAbortFsmReqMsgFlg_PlmnSelection(VOS_FALSE);
}

/*****************************************************************************
 函 数 名  : NAS_UTRANCTRL_InitFsmCtx_Syscfg
 功能描述  : 初始化syscfg状态机上下文
 输入参数  : 无
 输出参数  : 无
 返 回 值  :
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2012年8月7日
    作    者   : w00176964
    修改内容   : 新生成函数

*****************************************************************************/

VOS_VOID  NAS_UTRANCTRL_InitFsmCtx_Syscfg(VOS_VOID)
{
    return;
}

/*****************************************************************************
 函 数 名  : NAS_UTRANCTRL_InitFsmCtx_ModeChange
 功能描述  : 初始化模式改变状态机上下文
 输入参数  : 无
 输出参数  : 无
 返 回 值  :
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2012年8月7日
    作    者   : w00176964
    修改内容   : 新生成函数

*****************************************************************************/

VOS_VOID  NAS_UTRANCTRL_InitFsmCtx_ModeChange(VOS_VOID)
{
    NAS_UTRANCTRL_ClearAllWaitAsUtranModeCnfFlg_ModeChange();
    return;
}

/* 搜网状态机上下文操作函数 */
/*****************************************************************************
 函 数 名  : NAS_UTRANCTRL_SetAbortFlg_PlmnSelection
 功能描述  : 设置状态机打断标记
 输入参数  : 无
 输出参数  : 无
 返 回 值  : VOS_UINT8:状态机打断标记
 调用函数  :
 被调函数  :
 修改历史      :
  1.日    期   : 2012-08-6
    作    者   : W00176964
    修改内容   : 新生成函数
*****************************************************************************/
VOS_VOID NAS_UTRANCTRL_SetAbortFlg_PlmnSelection(
    VOS_UINT8       ucAbortFlg
)
{
    (NAS_UTRANCTRL_GetUtranCtrlCtx()->stCurFsm.unFsmCtx.stPlmnSelectionCtx.ucAbortFlg) = ucAbortFlg;

    return;
}

/*****************************************************************************
 函 数 名  : NAS_UTRANCTRL_GetAbortFlg_PlmnSelection
 功能描述  : 获取状态机打断标记
 输入参数  : 无
 输出参数  : 无
 返 回 值  : VOS_UINT8:状态机打断标记
 调用函数  :
 被调函数  :
 修改历史      :
  1.日    期   : 2012-08-6
    作    者   : W00176964
    修改内容   : 新生成函数
*****************************************************************************/
VOS_UINT8 NAS_UTRANCTRL_GetAbortFlg_PlmnSelection(VOS_VOID)
{
    return  (NAS_UTRANCTRL_GetUtranCtrlCtx()->stCurFsm.unFsmCtx.stPlmnSelectionCtx.ucAbortFlg);
}

/*****************************************************************************
 函 数 名  : NAS_UTRANCTRL_SetRcvMmcAbortFsmReqMsgFlg_PlmnSelection
 功能描述  : 设置状态机打断标记
 输入参数  : 无
 输出参数  : 无
 返 回 值  : VOS_UINT8:状态机打断标记
 调用函数  :
 被调函数  :
 修改历史      :
  1.日    期   : 2015-12-17
    作    者   : w00167002
    修改内容   : 新生成函数
*****************************************************************************/
VOS_VOID NAS_UTRANCTRL_SetRcvMmcAbortFsmReqMsgFlg_PlmnSelection(
    VOS_UINT8                           ucRcvMmcAbortFsmReqMsgFlg
)
{
    (NAS_UTRANCTRL_GetUtranCtrlCtx()->stCurFsm.unFsmCtx.stPlmnSelectionCtx.ucRcvMmcAbortFsmReqMsgFlg) = ucRcvMmcAbortFsmReqMsgFlg;

    return;
}

/*****************************************************************************
 函 数 名  : NAS_UTRANCTRL_GetRcvMmcAbortFsmReqMsgFlg_PlmnSelection
 功能描述  : 获取状态机打断标记
 输入参数  : 无
 输出参数  : 无
 返 回 值  : VOS_UINT8:状态机打断标记
 调用函数  :
 被调函数  :
 修改历史      :
  1.日    期   : 2015-12-17
    作    者   : w00167002
    修改内容   : 新生成函数
*****************************************************************************/
VOS_UINT8 NAS_UTRANCTRL_GetRcvMmcAbortFsmReqMsgFlg_PlmnSelection(VOS_VOID)
{
    return  (NAS_UTRANCTRL_GetUtranCtrlCtx()->stCurFsm.unFsmCtx.stPlmnSelectionCtx.ucRcvMmcAbortFsmReqMsgFlg);
}


/*****************************************************************************
 函 数 名  : NAS_UTRANCTRL_SaveBufferUtranSndMmcMsg
 功能描述  : 保存UTRAN模块缓存的W/TD发给MMC的消息
 输入参数  : VOS_UINT32                          ulEventType
             struct MsgCB                        *pMsg
 输出参数  : 无
 返 回 值  : 无
 调用函数  :
 被调函数  :
 修改历史      :
  1.日    期   : 2012-08-6
    作    者   : W00176964
    修改内容   : 新生成函数
  2.日    期   : 2012年9月15日
    作    者   : w00167002
    修改内容   : 如果消息长度超过了缓存的长度，则不保存, 防止数组越界
*****************************************************************************/
VOS_VOID NAS_UTRANCTRL_SaveBufferUtranSndMmcMsg(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg
)
{
    NAS_UTRANCTRL_ENTRY_MSG_STRU       *pstEntryMsg  = VOS_NULL_PTR;
    MSG_HEADER_STRU                    *pstMsgHeader = VOS_NULL_PTR;
    VOS_UINT32                          ulLen;

    /* 获得当前缓存的缓冲区地址 */
    pstEntryMsg                         = NAS_UTRANCTRL_GetBufferUtranSndMmcMsgAddr();
    pstMsgHeader                        = (MSG_HEADER_STRU *)pstMsg;

    /* 如果是空消息 */
    if ( VOS_NULL_PTR == pstMsg )
    {
        NAS_WARNING_LOG( WUEPS_PID_MMC, "NAS_UTRANCTRL_SaveBufferUtranSndMmcMsg Entry Message Pointer is NULL!" );

        return;
    }


    /* 保存缓存前清空下缓存 */
    PS_MEM_SET(pstEntryMsg->aucEntryMsgBuffer, (VOS_UINT8)0x00, sizeof(pstEntryMsg->aucEntryMsgBuffer) );

    ulLen                               = pstMsgHeader->ulLength + VOS_MSG_HEAD_LENGTH;

    /* 消息长度超过了缓存的长度，则不保存, 防止数组越界 */
    if ( ulLen > NAS_UTRANCTRL_MAX_MSG_BUFFER_LEN )
    {
        NAS_ERROR_LOG(WUEPS_PID_MMC, "NAS_UTRANCTRL_SaveBufferUtranSndMmcMsg:Msg too big to save! ");
        return ;
    }

    /* 将当前处理的入口消息拷贝到Context对应的缓冲区 */
    PS_MEM_CPY( pstEntryMsg->aucEntryMsgBuffer, pstMsg, ulLen );

    /* 填写Context中的参数 */
    pstEntryMsg->ulEventType            = ulEventType;

    return;
}


/*****************************************************************************
 函 数 名  : NAS_UTRANCTRL_GetBufferUtranSndMmcMsgAddr
 功能描述  : 获取UTRAN模块缓存的W/TD发给MMC的消息地址
 输入参数  : 无
 输出参数  : 无
 返 回 值  : UTRAN模块缓存的W/TD发给MMC的消息地址
 调用函数  :
 被调函数  :
 修改历史      :
  1.日    期   : 2012-08-6
    作    者   : W00176964
    修改内容   : 新生成函数
*****************************************************************************/
NAS_UTRANCTRL_ENTRY_MSG_STRU* NAS_UTRANCTRL_GetBufferUtranSndMmcMsgAddr(VOS_VOID)
{
    return &(NAS_UTRANCTRL_GetUtranCtrlCtx()->stMainCtrlInfo.stBufferUtranSndMmcMsg);
}


/*****************************************************************************
 函 数 名  : NAS_UTRANCTRL_GetUtranModeAutoSwtich
 功能描述  : 获取存储当前UTRAN MODE自动切换的NVIM内容
 输入参数  : 无
 输出参数  : 无
 返 回 值  : 当前状态机表的地址
 调用函数  :
 被调函数  :

 修改历史      :
 1.日    期   : 2012年8月9日
   作    者   : w00167002
   修改内容   : 新生成函数

*****************************************************************************/
NAS_UTRANCTRL_UTRAN_MODE_AUTO_SWITCH_STRU* NAS_UTRANCTRL_GetUtranModeAutoSwtich(VOS_VOID)
{
    return &(NAS_UTRANCTRL_GetUtranCtrlCtx()->stMsCfgInfo.stCustomCfg.stUtranModeAutoSwitch);
}

/*****************************************************************************
 函 数 名  : NAS_UTRANCTRL_GetWaitSlaveModeUtranModeCnfFlg_ModeChange
 功能描述  : 获取是否已经收到Gass的模式变更回复标记
 输入参数  : 无
 输出参数  : 无
 返 回 值  : VOS_TRUE：需要等待从模的模式变更回复
              VOS_FALSE：不需要等待从模的模式变更回复
 调用函数  :
 被调函数  :
 修改历史      :
  1.日    期   : 2012-8-8
    作    者   : s00217060
    修改内容   : 新生成函数
*****************************************************************************/
VOS_UINT8  NAS_UTRANCTRL_GetWaitSlaveModeUtranModeCnfFlg_ModeChange(VOS_VOID)
{
    return (NAS_UTRANCTRL_GetUtranCtrlCtx()->stCurFsm.unFsmCtx.stModeChangeCtx.ucWaitSlaveModeUtranModeCnfFlg);
}

/*****************************************************************************
 函 数 名  : NAS_UTRANCTRL_SetWaitSlaveModeUtranModeCnfFlg_ModeChange
 功能描述  : 设置是否需要等待从模的模式变更回复标记
 输入参数  : ucWaitSlaveModeUtranModeCnfFlg:是否需要等待从模的模式变更回复标记
 输出参数  : 无
 返 回 值  : 无
 调用函数  :
 被调函数  :
 修改历史      :
  1.日    期   : 2012-8-8
    作    者   : s00217060
    修改内容   : 新生成函数
*****************************************************************************/
VOS_VOID  NAS_UTRANCTRL_SetWaitSlaveModeUtranModeCnfFlg_ModeChange(
    VOS_UINT8                           ucWaitSlaveModeUtranModeCnfFlg
)
{
    (NAS_UTRANCTRL_GetUtranCtrlCtx()->stCurFsm.unFsmCtx.stModeChangeCtx.ucWaitSlaveModeUtranModeCnfFlg) |= ucWaitSlaveModeUtranModeCnfFlg;
}

/*****************************************************************************
 函 数 名  : NAS_UTRANCTRL_ClearWaitSlaveUtranModeCnfFlg_ModeChange
 功能描述  : 清除等待模式变更回复标志
 输入参数  : ucWaitUtranModeCnfFlg:是否需要等待模式变更回复标记
 输出参数  : 无
 返 回 值  : 无
 调用函数  :
 被调函数  :
 修改历史      :
  1.日    期   : 2012-8-8
    作    者   : s00217060
    修改内容   : 新生成函数
*****************************************************************************/
VOS_VOID  NAS_UTRANCTRL_ClearWaitSlaveUtranModeCnfFlg_ModeChange(
    VOS_UINT8                           ucWaitUtranModeCnfFlg
)
{
    /* 如果当前状态机不是MODE CHANGE状态机 */
    if (NAS_UTRANCTRL_FSM_MODE_CHANGE != NAS_MMC_GetCurrFsmId())
    {
        /* 异常事件 */
        NAS_WARNING_LOG(WUEPS_PID_MMC, "NAS_UTRANCTRL_ClearWaitSlaveUtranModeCnfFlg_ModeChange:ENTERED");
    }

    (NAS_UTRANCTRL_GetUtranCtrlCtx()->stCurFsm.unFsmCtx.stModeChangeCtx.ucWaitSlaveModeUtranModeCnfFlg) &= ~ucWaitUtranModeCnfFlg;

    return;
}


/*****************************************************************************
 函 数 名  : NAS_UTRANCTRL_ClearAllWaitUtranModeCnfFlg_ModeChange
 功能描述  : 清除等待模式变更回复标志
 输入参数  : ucWaitUtranModeCnfFlg:是否需要等待模式变更回复标记
 输出参数  : 无
 返 回 值  : 无
 调用函数  :
 被调函数  :
 修改历史      :
  1.日    期   : 2012-8-8
    作    者   : s00217060
    修改内容   : 新生成函数
*****************************************************************************/
VOS_VOID  NAS_UTRANCTRL_ClearAllWaitAsUtranModeCnfFlg_ModeChange(VOS_VOID)
{
    /* 如果当前状态机不是MODE CHANGE状态机 */
    if (NAS_UTRANCTRL_FSM_MODE_CHANGE != NAS_MMC_GetCurrFsmId())
    {
        /* 异常事件 */
        NAS_WARNING_LOG(WUEPS_PID_MMC, "NAS_UTRANCTRL_ClearAllWaitUtranModeCnfFlg_ModeChange:ENTERED");
    }

    (NAS_UTRANCTRL_GetUtranCtrlCtx()->stCurFsm.unFsmCtx.stModeChangeCtx.ucWaitSlaveModeUtranModeCnfFlg) = NAS_UTRANCTRL_WAIT_UTRAN_MODE_CNF_NULL;

    return;
}
#endif

/*****************************************************************************
 函 数 名  : NAS_UTRANCTRL_SetSearchedSpecTdMccFlg
 功能描述  : 设置当前搜到的指定TD的MCC的标记
 输入参数  : ucFlg:当前搜到的指定TD的MCC的标记
 输出参数  : 无
 返 回 值  : 无
 调用函数  :
 被调函数  :
 修改历史      :
  1.日    期   : 2012-08-6
    作    者   : W00176964
    修改内容   : 新生成函数
*****************************************************************************/
VOS_VOID  NAS_UTRANCTRL_SetSearchedSpecTdMccFlg(
    VOS_UINT8       ucFlg
)
{
#if (FEATURE_ON == FEATURE_UE_MODE_TDS)
    (NAS_UTRANCTRL_GetUtranCtrlCtx()->stPlmnSearchCtrl.ucSearchedSpecTdMccFlg) = ucFlg;
#endif
    return;
}



/*lint -restore */


#ifdef __cplusplus
    #if __cplusplus
        }
    #endif
#endif
