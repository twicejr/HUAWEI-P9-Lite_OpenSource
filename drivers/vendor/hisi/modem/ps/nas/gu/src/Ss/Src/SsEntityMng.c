/*******************************************************************************
  Copyright    : 2005-2007, Huawei Tech. Co., Ltd.
  File name    : SsEntityMng.c
  Description  : SS实体管理
  Function List:
      1.  Ss_EntityBuildTi      选择TI
      2.  Ss_EntityBuildCr      选择CR
      3.  Ss_EntityCreat        创建实体
      4.  Ss_EntityClear        释放实体
      5.  Ss_EntitySelectTi     根据CR和TAF ID选择其对应的TI
      6.  Ss_AribMalloc         为生成ARIB结构提供内存空间
      7.  Ss_AribFree           释放掉生成ARIB结构过程中申请的内存
  History:
      1.  张志勇 2004.03.08   新版作成
      2.  丁  庆 2006.11.07   问题单A32D07063
*******************************************************************************/

#include "SsInclude.h"


#ifdef  __cplusplus
  #if  __cplusplus
  extern "C"{
  #endif
#endif


/*****************************************************************************
    协议栈打印打点方式下的.C文件宏定义
*****************************************************************************/
/*lint -e767 修改人:罗建 107747;检视人:孙少华65952;原因:Log打印*/
#define    THIS_FILE_ID        PS_FILE_ID_SS_ENTITYMNG_C
/*lint +e767 修改人:罗建 107747;检视人:sunshaohua*/

/*lint -save -e958 */
/*****************************************************************************
 函 数 名  : NAS_SS_LogSsStateInfo
 功能描述  : 勾SS的状态
 输入参数  : ucSsState: SS的当前状态
 输出参数  : VOS_VOID
 返 回 值  : VOS_VOID
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2014年06月30日
    作    者   : w00242748
    修改内容   : 新生成函数

*****************************************************************************/
VOS_VOID  NAS_SS_LogSsStateInfo(
    VOS_UINT8                           ucState
)
{
    NAS_SS_LOG_STATE_INFO_STRU         *pstMsg = VOS_NULL_PTR;

    pstMsg = (NAS_SS_LOG_STATE_INFO_STRU*)PS_MEM_ALLOC(WUEPS_PID_SS,
                                         sizeof(NAS_SS_LOG_STATE_INFO_STRU));

    if (VOS_NULL_PTR == pstMsg)
    {
        NAS_ERROR_LOG(WUEPS_PID_SS, "NAS_SS_LogCcStateInfo:ERROR:Alloc Mem Fail.");
        return;
    }

    PS_MEM_SET(pstMsg, 0x00, sizeof(NAS_SS_LOG_STATE_INFO_STRU));

    pstMsg->stMsgHeader.ulSenderCpuId   = VOS_LOCAL_CPUID;
    pstMsg->stMsgHeader.ulReceiverCpuId = VOS_LOCAL_CPUID;
    pstMsg->stMsgHeader.ulSenderPid     = WUEPS_PID_SS;
    pstMsg->stMsgHeader.ulReceiverPid   = WUEPS_PID_SS;
    pstMsg->stMsgHeader.ulLength        = sizeof(NAS_SS_LOG_STATE_INFO_STRU) - VOS_MSG_HEAD_LENGTH;
    pstMsg->stMsgHeader.ulMsgName       = SSOM_LOG_STATE_INFO_IND;
    pstMsg->ucSsState                   = ucState;

    DIAG_TraceReport(pstMsg);

    PS_MEM_FREE(WUEPS_PID_SS, pstMsg);

    return;
}


/***********************************************************************
*  MODULE   : Ss_EntityBuildTi
*  FUNCTION : 为MO过程中的SS实体选择一个新的TI
*  INPUT    : VOS_UINT8             ucCr        消息中的CR
*             VOS_UINT8             ucTafId     消息中的TAF ID
*  OUTPUT   : VOS_VOID
*  RETURN   : VOS_UINT8             ucTi    所选择的TI
*  NOTE     : 无
*  HISTORY  :
*     1.  张志勇 04-03-08  新版作成
************************************************************************/

VOS_UINT8 Ss_EntityBuildTi(
                            VOS_UINT8 ucCr
                       )
{
    VOS_UINT8   i;

    for( i = 8 ; i < SS_MAX_ENTITY_NUM ; i++ )
    {                                                                           /* 循环考察所有TI                           */
        if(( ucCr == g_SsEntity[i].ucCr )
            && ( SS_S_NULL != g_SsEntity[i].ucState ))
        {                                                                       /* 判断指定TI是否已存在                     */
            return SS_NONE_TI;                                                  /* 返回没找到TI                             */
        }
    }

    for( i = 8 ; i < SS_MAX_ENTITY_NUM ; i++ )
    {                                                                           /* 循环考察所有TI                           */
        if( SS_S_NULL == g_SsEntity[i].ucState )
        {                                                                       /* 判断是否存在空闲的TI                     */
            return i;                                                           /* 返回此TI                                 */
        }
    }
    return SS_NONE_TI;                                                          /* 返回没找到TI                             */
}

/***********************************************************************
*  MODULE   : Ss_EntityBuildCr
*  FUNCTION : 为MT过程中的SS实体选择一个新的CR
*  INPUT    : VOS_UINT8     ucTi        指定实体的TI
*  OUTPUT   : VOS_VOID
*  RETURN   : VOS_UINT8     ucCr        所选择的CR
*  NOTE     : 无
*  HISTORY  :
*     1.  张志勇 04-03-08  新版作成
************************************************************************/

VOS_UINT8 Ss_EntityBuildCr( VOS_UINT8 ucTi )
{
    if( SS_S_NULL == g_SsEntity[ucTi].ucState )
    {                                                                           /* 判断指定TI是否已存在                     */
        return ((VOS_UINT8)( ucTi + 128 ));                                         /* 返回没找到TI                             */
    }
    return SS_NONE_CR;                                                          /* 返回没找到CR                             */
}

/*****************************************************************************
 函 数 名  : NAS_SS_IsOnlyMtSs
 功能描述  : 判断是否是唯一存在的mt ss业务
 输入参数  : ucTi       - 指定实体的TI
 输出参数  : 无
 返 回 值  : VOS_TRUE  - 是唯一存在的mt ss业务
             VOS_FALSE - 不是唯一存在的 mt ss业务
 调用函数  :
 被调函数  :

 修改历史      :
 1.日    期   : 2014年6月16日
   作    者   : z00161729
   修改内容   : DSDS III新增

*****************************************************************************/
VOS_UINT8 NAS_SS_IsOnlyMtSs(
    VOS_UINT8                           ucTi
)
{
    VOS_UINT8                           ucIndex;
    VOS_UINT8                           ucNum;

    ucNum = 0;

    /* TI非法，返回VOS_FALSE */
    if (ucTi >= SS_MT_ENTITY_NUM)
    {
        return VOS_FALSE;
    }

    for (ucIndex = 0; ucIndex < SS_MT_ENTITY_NUM; ucIndex++)
    {
        if (SS_S_NULL != g_SsEntity[ucIndex].ucState)
        {
            ucNum++;
        }
    }

    if (1 == ucNum)
    {
        return VOS_TRUE;
    }

    return VOS_FALSE;
}



/*****************************************************************************
 函 数 名  : NAS_SS_IsOnlyMoSs
 功能描述  : 判断是否是唯一存在的mo ss业务
 输入参数  : ucTi       - 指定实体的TI
 输出参数  : 无
 返 回 值  : VOS_TRUE  - 是唯一存在的mo ss业务
             VOS_FALSE - 不是唯一存在的mo ss业务
 调用函数  :
 被调函数  :

 修改历史      :
 1.日    期   : 2014年6月16日
   作    者   : z00161729
   修改内容   : DSDS III新增

*****************************************************************************/
VOS_UINT8 NAS_SS_IsOnlyMoSs(
    VOS_UINT8                           ucTi
)
{
    VOS_UINT8                           ucIndex;
    VOS_UINT8                           ucNum;

    ucNum = 0;

    /* TI非法返回VOS_FALSE */
    if ((ucTi < 8)
     || (ucTi >= SS_MAX_ENTITY_NUM))
    {
        return VOS_FALSE;
    }

    for (ucIndex = 8; ucIndex < SS_MAX_ENTITY_NUM; ucIndex++)
    {
        if (SS_S_NULL != g_SsEntity[ucIndex].ucState)
        {
            ucNum++;
        }
    }

    if (1 == ucNum)
    {
        return VOS_TRUE;
    }

    return VOS_FALSE;
}

#if (FEATURE_ON == FEATURE_DSDS)
/*****************************************************************************
 函 数 名  : NAS_SS_NotifySessionAccordingSsStateChg
 功能描述  : 根据ss实体状态进行资源申请和释放
 输入参数  : ucTi       - 指定实体的TI
             ucNewState - ss状态
 输出参数  : 无
 返 回 值  : 无
 调用函数  :
 被调函数  :

 修改历史      :
 1.日    期   : 2014年6月16日
   作    者   : z00161729
   修改内容   : DSDS III新增

*****************************************************************************/
VOS_VOID NAS_SS_NotifySessionAccordingSsStateChg(
    VOS_UINT8                           ucTi,
    VOS_UINT8                           ucNewState
)
{
    if ((SS_S_NULL == g_SsEntity[ucTi].ucState)
     && (SS_S_NULL != ucNewState))
    {
        g_SsEntity[ucTi].ucState = ucNewState;

        /* 第一个被叫ss业务，通知mm资源申请 */
        if (0 == (ucTi & NAS_SS_MSG_SND_TO_SIDE_THAT_ORIGINATES_THE_TI))
        {
            if (VOS_TRUE == NAS_SS_IsOnlyMtSs(ucTi))
            {
                NAS_SS_SndMmBeginSessionNotify(MMSS_SESSION_TYPE_MT_SS);
                return;
            }
        }

        /* 第一主叫ss业务，给mm申请资源 */
        if (VOS_TRUE == NAS_SS_IsOnlyMoSs(ucTi))
        {
            NAS_SS_SndMmBeginSessionNotify(MMSS_SESSION_TYPE_MO_SS);
        }

        return;
    }

    if ((SS_S_NULL == ucNewState)
     && (SS_S_NULL != g_SsEntity[ucTi].ucState))
    {
        /* 如果是最后一路被叫ss结束，通知mm 资源释放 */
        if (0 == (ucTi & NAS_SS_MSG_SND_TO_SIDE_THAT_ORIGINATES_THE_TI))
        {
            if (VOS_TRUE == NAS_SS_IsOnlyMtSs(ucTi))
            {
                NAS_SS_SndMmEndSessionNotify(MMSS_SESSION_TYPE_MT_SS);
            }

            g_SsEntity[ucTi].ucState = ucNewState;
            return;
        }

        /* 如果是最后一路主叫ss结束，通知mm释放资源 */
        if (VOS_TRUE == NAS_SS_IsOnlyMoSs(ucTi))
        {
            NAS_SS_SndMmEndSessionNotify(MMSS_SESSION_TYPE_MO_SS);
        }

        g_SsEntity[ucTi].ucState = ucNewState;
        return;
    }

    return;
}
#endif

/*****************************************************************************
 函 数 名  : NAS_SS_ChangeSsState
 功能描述  : 设置ss实体状态
 输入参数  : ucTi       - 指定实体的TI
             ucNewState - ss状态
 输出参数  : 无
 返 回 值  : 无
 调用函数  :
 被调函数  :

 修改历史      :
 1.日    期   : 2014年6月16日
   作    者   : z00161729
   修改内容   : DSDS III新增

*****************************************************************************/
VOS_VOID NAS_SS_ChangeSsState(
    VOS_UINT8                           ucTi,
    VOS_UINT8                           ucNewState
)
{
    NAS_SS_LogSsStateInfo(g_SsEntity[ucTi].ucState);

#if (FEATURE_ON == FEATURE_DSDS)
    NAS_SS_NotifySessionAccordingSsStateChg(ucTi, ucNewState);
 #endif

    g_SsEntity[ucTi].ucState = ucNewState;

    NAS_SS_LogSsStateInfo(g_SsEntity[ucTi].ucState);
    return;
}


/***********************************************************************
*  MODULE   : Ss_EntityCreat
*  FUNCTION : 创建实体
*  INPUT    : VOS_UINT8     ucTi        指定实体的TI
*             VOS_UINT8     ucCr        指定实体对应的CR
*             VOS_UINT8     ucTafId     指定实体对应的TAF ID
*  OUTPUT   : VOS_VOID
*  RETURN   : VOS_VOID
*  NOTE     : 无
*  HISTORY  :
*     1.  张志勇 04-03-08  新版作成
************************************************************************/

VOS_VOID Ss_EntityCreat(
                    VOS_UINT8 ucTi,
                    VOS_UINT8 ucCr
                    )
{
    SS_NORM_LOG( "\n Create SS entity()\r");
    g_SsEntity[ucTi].ucCr = ucCr;                                               /* 设置CR                                   */
}

/***********************************************************************
*  MODULE   : Ss_EntityClear
*  FUNCTION : 释放实体
*  INPUT    : VOS_UINT8     ucTi        指定实体的TI
*  OUTPUT   : VOS_VOID
*  RETURN   : VOS_VOID
*  NOTE     : 无
*  HISTORY  :
*     1.  张志勇 04-03-08  新版作成
*     2.  张志勇 04-03-23  增加停止T551的处理
    3.日    期   : 2014年6月24日
      作    者   : w00167002
      修改内容   : DSDS III项目
************************************************************************/


VOS_VOID Ss_EntityClear(
                    VOS_UINT8 ucTi
                    )
{
    NAS_SS_ChangeSsState(ucTi, SS_S_NULL);

    SS_NORM_LOG( "\n SS state = SS_S_NULL() \r" );
    SS_NORM_LOG( "\n Destroy SS entity()\r" );
    g_SsEntity[ucTi].ucCr = SS_NONE_CR;                                         /* 清除CR                                   */
}


/***********************************************************************
*  MODULE   : Ss_EntitySelectTi
*  FUNCTION : 根据CR和TAF ID选择其对应的TI
*  INPUT    : VOS_UINT8     ucCr        指定实体对应的CR
*             VOS_UINT8     ucTafId     指定实体对应的TAF ID
*  OUTPUT   : VOS_VOID
*  RETURN   : VOS_UINT8     ucTi;
*  NOTE     : 无
*  HISTORY  :
*     1.  张志勇 04-03-08  新版作成
*     2.
************************************************************************/

VOS_UINT8 Ss_EntitySelectTi(
                            VOS_UINT8 ucCr
                        )
{
    VOS_UINT8   i;                                                                  /* 用于循环                                 */
    VOS_UINT8   ucTi;                                                               /* 定义用于返回的TI                         */

    ucTi = SS_NONE_TI;                                                          /* 初始化TI                                 */

    if( ucCr <= SS_MO_CR_NUM )
    {                                                                           /* MO过程                                   */
        for( i = 8 ; i < SS_MAX_ENTITY_NUM ; i++ )
        {                                                                       /* 遍历MO过程的所有SS实体                   */
            if( ucCr == g_SsEntity[i].ucCr )
            {                                                                   /* 找到了指定的CR和TAF ID                   */
                if( SS_S_CONNECTED == g_SsEntity[i].ucState )
                {                                                               /* 对应的SS实体的状态为SS_S_CONNECTED       */
                    ucTi = i;                                                   /* 返回该TI                                 */
                }
                else
                {                                                               /* 实体状态不对                             */
                    SS_WARN_LOG("\n [Error]SsEntity State Error! \r" );
                }
                break;                                                          /* 跳出循环                                 */
            }
        }
    }
    else
    {                                                                           /* MT过程                                   */
        for( i = 0 ; i < SS_MT_ENTITY_NUM ; i++ )
        {                                                                       /* 遍历MT过程的所有SS实体                   */
            if( ucCr == g_SsEntity[i].ucCr )
            {                                                                   /* 找到了指定的CR                           */
                if( SS_S_CONNECTED == g_SsEntity[i].ucState )
                {                                                               /* 对应的SS实体的状态为SS_S_CONNECTED       */
                        ucTi = i;                                               /* 返回该TI                                 */
                    }
                else
                {                                                               /* 实体状态不对                             */
                    SS_WARN_LOG("\n [Error]SsEntity State Error! \r" );
                }
                break;                                                          /* 跳出循环                                 */
            }
        }
    }
    return ucTi;                                                                /* 返回找到的TI                             */
}
/***********************************************************************
*  MODULE   : Ss_GetSsTi
*  FUNCTION :
*  INPUT    : VOS_UINT8     ucCr        指定实体对应的CR
*
*  OUTPUT   : VOS_UINT8
*  RETURN   : VOS_UINT8     ucTi;
*  NOTE     : 无
*  HISTORY  :
      1.  日    期   : 2008年05月24日
          作    者   : huwen id:44270
          修改内容   : 问题单号:AT2D03224
      2.日    期   : 2013年8月6日
        作    者   : z00161729
        修改内容  : V9R1 STK升级修改

************************************************************************/
VOS_UINT8 Ss_GetSsTi(VOS_UINT8  ucCr)
{
    VOS_UINT8  i;
    VOS_UINT8  ucTi = SS_NONE_TI;

    /* Modified by z00161729 for V9R1 STK升级, 2013-8-6, begin */
    /* 网络发起USSD业务要求用户确认，用户不确认至超时处理时Cr范围是8-14,转换成128-134 */
    if ((ucCr > (TAF_MIDDLE_SSA_TI))
     && (ucCr <= TAF_MAX_SSA_TI))
    {
        ucCr += 120;
    }
    /* Modified by z00161729 for V9R1 STK升级, 2013-8-6, end */

    for( i = 0 ; i < SS_MAX_ENTITY_NUM ; i++ )
    {
        if( ucCr == g_SsEntity[i].ucCr )
        {
            ucTi = i;
            break;
        }
    }

    return ucTi;
}

/*lint -restore */

#ifdef  __cplusplus
  #if  __cplusplus
  }
  #endif
#endif

