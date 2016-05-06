/************************************************************************
  Copyright    : 2005-2007, Huawei Tech. Co., Ltd.
  File name    : GmmCasSuspend.c
  Author       : Roger Leo
  Version      : V200R001
  Date         : 2005-08-25
  Description  : 该C文件给出了GmmCasSuspend模块的实现
  Function List:
        ---
        ---
        ---
  History      :
  1. Date:2005-08-25
     Author: Roger Leo
     Modification:update
  2. s46746 2006-03-07 根据问题单A32D02356修改
  2. s46746 2006-03-08 根据问题单A32D02368修改
  3.x51137 2006/11/3 A32D06511
  4. 日    期   : 2007年07月14日
     作    者   : luojian id:60022475
     修改内容   : 根据问题单号：A32D12436
  5. 日    期   : 2007年09月05日
     作    者   : s46746
     修改内容   : 根据问题单号：AT2D01456
  6. 日    期   : 2007年09月21日
     作    者   : luojian id:107747
     修改内容   : 根据问题单号：AT2D01670
  7. 日    期   : 2007年10月13日
     作    者   : s46746
     修改内容   : 根据问题单号：A32D13060
  8. 日    期   : 2007年11月22日
     作    者   : s46746
     修改内容   : 根据问题单号：A32D13475,修改异系统改变后指派的old TLLI和开机加密密钥为全0问题
  9. 日    期   : 2007年12月28日
     作    者   : s46746
     修改内容   : 根据问题单号：A32D13954,修改GMM在2G3过程中缓存消息机制
  10.日    期   : 2008年3月17日
     作    者   : s46746
     修改内容   : 问题单号:AT2D02570,NAS B005版本新增需求合入
  11.日    期   : 2008年9月26日
     作    者   : x00115505
     修改内容   : 问题单号:AT2D05431
  12.日    期   : 2009年4月9日
     作    者   : s46746
     修改内容   : 问题单号:AT2D10867,异系统改变后，未完成的Detach流程没有继续
  13.日    期   : 2009年08月24日
     作    者   : x00115505
     修改内容   : AT2D14023,测试GCF用例44.2.2.1.9失败
  14.日    期   : 2009年09月25日
     作    者   : s46746
     修改内容   : AT2D14760,异系统重选完成后立即上报出服务区，NAS上报服务状态不正确
************************************************************************/

/*****************************************************************************
   1 头文件包含
*****************************************************************************/

#include "GmmInc.h"
#include "GmmCasGlobal.h"
#include "GmmCasSuspend.h"
#include "GmmCasGsm.h"
#include "GmmCasSend.h"
#include "NasGmmSndOm.h"
#include "NasUtranCtrlInterface.h"
/* Added by w00176964 for VoLTE_PhaseII 项目, 2013-9-25, begin */
#include "NasMmlCtx.h"
/* Added by w00176964 for VoLTE_PhaseII 项目, 2013-9-25, end */

#ifdef  __cplusplus
  #if  __cplusplus
  extern "C"{
  #endif
#endif


/*****************************************************************************
    协议栈打印打点方式下的.C文件宏定义
*****************************************************************************/
/*lint -e767 修改人:luojian 107747;检视人:sunshaohua65952;原因:LOG方案设计需要*/
#define    THIS_FILE_ID        PS_FILE_ID_GMM_CASSUSPEND_C
/*lint +e767 修改人:luojian 107747;检视人:sunshaohua*/



/*****************************************************************************
   2 全局变量定义
*****************************************************************************/
GMM_CAS_MSG_BUFFER_STRU     gstGmmCasMsgBuf;                /* 挂起消息缓存链表 */
extern VOS_UINT32 g_ulGmmDelaySuspendRsp;

/*lint -save -e958 */

/*****************************************************************************
   3 函数实现
*****************************************************************************/

/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~ */
/*---------------3.1 GMM挂起消息的缓存处理  -------------*/
/*=======================================================*/

/*****************************************************************************
 Prototype      : GMM_BufferMsgQueueIn
 Description    : 得到消息缓存队列的空闲位置
                  HSS 4100 V200R001 新增
 Input          : struct MsgCB*     pMsgIn            待保存的消息指针
 Output         :
 Return Value   :
 Calls          :
 Called By      :

 History        :
  1.Date        : 2005-08-25
    Author      : Roger Leo
    Modification: Created function
*****************************************************************************/
VOS_UINT32 GMM_BufferMsgQueueIn(VOS_VOID)
{
    VOS_UINT32      ulIndex = 0;
    VOS_UINT32      ulRet = GMM_CAS_MSG_NUMBER_MAX;         /* 无效值 */

    /* 顺序检查未释放的缓存消息 */
    for (ulIndex=0; ulIndex<GMM_CAS_MSG_NUMBER_MAX; ulIndex++)
    {
        /* 缓存消息空闲位置 */
        if (GMM_MSG_BUFFER_FLAG_IDLE
         == gstGmmCasMsgBuf.aucBufMsgFlg[ulIndex])
        {
            ulRet = ulIndex;
            break;
        }
    }

    return ulRet;   /* 返回消息队列的头条空闲位置的索引 */

}

/*****************************************************************************
 Prototype      : GMM_BufferMsgQueueOut
 Description    : 从消息缓存队列取出GMM挂起消息的位置
                  HSS 4100 V200R001 新增
 Input          : struct MsgCB*     pMsgOut            待取出的消息指针
 Output         :
 Return Value   : >=0
 Calls          :
 Called By      :

 History        :
  1.Date        : 2005-08-25
    Author      : Roger Leo
    Modification: Created function
*****************************************************************************/
VOS_UINT32 GMM_BufferMsgQueueOut(VOS_VOID)
{
    VOS_UINT32      ulIndex = 0;
    VOS_UINT32      ulRet = GMM_CAS_MSG_NUMBER_MAX;         /* 无效值 */

    /* 顺序检查未释放的缓存消息 */
    for (ulIndex=0; ulIndex<GMM_CAS_MSG_NUMBER_MAX; ulIndex++)
    {
        /* 有效的缓存消息 */
        if (GMM_MSG_BUFFER_FLAG_USED
        == gstGmmCasMsgBuf.aucBufMsgFlg[ulIndex])
        {
            ulRet = ulIndex;
            break;
        }
    }

    return ulRet;   /* 返回消息队列的头条缓存消息的索引值 */
}

/*****************************************************************************
 Prototype      : GMM_BufferMsgSend
 Description    : 重新发送从消息缓存队列取出GMM挂起消息
                  HSS 4100 V200R001 新增
 Input          :
 Output         :
 Return Value   :
 Calls          :
 Called By      :

 History        :
  1.Date        : 2005-08-25
    Author      : Roger Leo
    Modification: Created function
 2. 日    期   : 2011年12月01日
    作    者   : w00166186
    修改内容   : DTS2011112400118,CS语音过程发起PS ATTACH，后处理缓存时返回ERROR
*****************************************************************************/
VOS_UINT32 GMM_BufferMsgSend(VOS_VOID)
{
    VOS_VOID       *pBufMsg;
    VOS_UINT32      ulIndex;
    MSG_HEADER_STRU     *pNasMsgHeader;                                         /* 定义MSG_HEADER_STRU类型指针              */

    /* 取得当前队列头端的索引 */
    ulIndex = GMM_BufferMsgQueueOut();
    if (GMM_CAS_MSG_NUMBER_MAX == ulIndex)
    {
        GMM_LOG_WARN("GMM_BufferMsgSend():Warning: Buffer is empty");
        return GMM_FALSE;               /* 错误返回 */
    }

    /* 取得消息内容指针 */
    pBufMsg = gstGmmCasMsgBuf.apBufMsg[ulIndex];

    pNasMsgHeader = (MSG_HEADER_STRU *)pBufMsg;                                 /* 得到消息头                               */

    if ((WUEPS_PID_MMC == pNasMsgHeader->ulSenderPid)
     && (MMCGMM_ATTACH_REQ == pNasMsgHeader->ulMsgName))
    {
        if (VOS_TRUE == NAS_GMM_RcvMmcAttachReq_PreProc((MMCGMM_ATTACH_REQ_STRU*) pBufMsg))
        {
            return GMM_TRUE;
        }
    }

    /* 直接调用GMM的消息处理函数 */
    Gmm_MsgDistribute(pBufMsg);

    return GMM_TRUE;
}

/*****************************************************************************
 函 数 名  : NAS_GMM_ClearSameMsgFromBuff
 功能描述  : 从缓存消息中删除和要缓存的消息相同的内容
 输入参数  : struct MsgCB                   *pstMsgIn
             VOS_UINT32                     *pulIndex
 输出参数  : 无
 返 回 值  : VOS_VOID
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2010年12月17日
    作    者   : l65478
    修改内容   : 新生成函数

*****************************************************************************/
VOS_VOID NAS_GMM_ClearSameMsgFromBuff(
        struct MsgCB                   *pstMsgIn,
        VOS_UINT32                     *pulIndex
)
{
    MSG_HEADER_STRU                    *pstBuffMsg;
    MSG_HEADER_STRU                    *pstInputMsg;
    VOS_UINT32                          i;

    pstInputMsg = (MSG_HEADER_STRU *)pstMsgIn;

    /* 查找缓存中已经存在的相同的消息类型，如果找到，
       把原来的缓存消息清除，并把新的消息存储到此位置 */
    for (i = 0; i < gstGmmCasMsgBuf.ucBufMsgTotal; i++)
    {
        pstBuffMsg = (MSG_HEADER_STRU *)gstGmmCasMsgBuf.apBufMsg[i];
        if (pstBuffMsg->ulMsgName == pstInputMsg->ulMsgName)
        {
            Gmm_MemFree(gstGmmCasMsgBuf.apBufMsg[i]);
            gstGmmCasMsgBuf.apBufMsg[i]     = VOS_NULL_PTR;
            gstGmmCasMsgBuf.aucBufMsgFlg[i] = GMM_MSG_BUFFER_FLAG_IDLE;

            gstGmmCasMsgBuf.ucBufMsgTotal--;

            *pulIndex = i;
            break;
        }
    }
    return;
}

/*****************************************************************************
 Prototype      : GMM_BufferMsgReceive
 Description    : GMM挂起消息加入消息缓存队列
                  HSS 4100 V200R001 新增
 Input          : struct MsgCB*     pMsgIn            待保存的消息指针
 Output         :
 Return Value   :
 Calls          :
 Called By      :

 History        :
  1.Date        : 2005-08-25
    Author      : Roger Leo
    Modification: Created function
*****************************************************************************/
VOS_VOID GMM_BufferMsgReceive(struct MsgCB* pMsgIn)
{
    VOS_UINT32      ulInsert;
    VOS_UINT32      ulMsgSize;
    MSG_CB         *pMsgNew;

    /* 得到消息缓冲链表的插入位置 */
    ulInsert  = GMM_BufferMsgQueueIn();
    if (GMM_CAS_MSG_NUMBER_MAX == ulInsert)
    {
        GMM_LOG_WARN("GMM_BufferMsgReceive():Warning: Buffer is full");
        return;
    }

    /* 复制待缓存消息内容 */
    ulMsgSize = pMsgIn->ulLength;
    /*pMsgNew   = (MSG_CB*)VOS_AllocMsg(WUEPS_PID_GMM,
                    ulMsgSize - VOS_MSG_HEAD_LENGTH );*/
    pMsgNew   = (MSG_CB*)PS_MEM_ALLOC(WUEPS_PID_GMM, (ulMsgSize + VOS_MSG_HEAD_LENGTH));
    if (VOS_NULL_PTR == pMsgNew)
    {
        GMM_LOG_ERR("GMM_BufferMsgReceive():Error: Invalid results of VOS_AllocMsg()");
        return;
    }

    /* 缓存中同一个消息只存储一个，只保存最新的消息，
       把缓存中旧的相同的消息删除 */
    NAS_GMM_ClearSameMsgFromBuff(pMsgIn, &ulInsert);

    Gmm_MemCpy(pMsgNew, pMsgIn, (ulMsgSize + VOS_MSG_HEAD_LENGTH));                 /* 消息内容复制 */

    /* 加入到缓存队列 */
    gstGmmCasMsgBuf.apBufMsg[ulInsert]     = (VOS_VOID*)pMsgNew;
    gstGmmCasMsgBuf.aucBufMsgFlg[ulInsert] = GMM_MSG_BUFFER_FLAG_USED;

    if (gstGmmCasMsgBuf.ucBufMsgTotal < GMM_CAS_MSG_NUMBER_MAX)
    {
        gstGmmCasMsgBuf.ucBufMsgTotal ++;
    }

    return;                    /* 结束返回 */
}

/*****************************************************************************
 函 数 名  : NAS_GMM_ClearMsgFromBuff
 功能描述  : 根据消息名字清除缓存中的消息
 输入参数  :
             VOS_UINT32         ulMsgName
 输出参数  : 无
 返 回 值  : VOS_VOID
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2013年2月17日
    作    者   : l00167671
    修改内容   : 新生成函数FOR DTS2013021804440

  2.日    期   : 2014年6月17日
    作    者   : z00234330
    修改内容   : PCINT清理
*****************************************************************************/
VOS_VOID NAS_GMM_ClearMsgFromBuff(
        VOS_UINT32                     ulMsgName,
        VOS_UINT32                     ulSenderPid,
        VOS_UINT32                     ulReceiverPid
)
{
    MSG_HEADER_STRU                    *pstBuffMsg;
    VOS_UINT32                          i;

    /* 查找缓存中已经存在的相同的消息类型，如果找到，
       把原来的缓存消息清除，并把新的消息存储到此位置 */
    for (i = 0; i < gstGmmCasMsgBuf.ucBufMsgTotal; i++)
    {
        pstBuffMsg = (MSG_HEADER_STRU *)gstGmmCasMsgBuf.apBufMsg[i];
        /* Modified by z00234330 for PCLINT清理, 2014-06-24, begin */
        if ( (pstBuffMsg->ulMsgName == ulMsgName)
          && (pstBuffMsg->ulSenderPid == ulSenderPid)
          && (pstBuffMsg->ulReceiverPid == ulReceiverPid) )
        /* Modified by z00234330 for PCLINT清理, 2014-06-24, end */
        {
            Gmm_MemFree(gstGmmCasMsgBuf.apBufMsg[i]);
            gstGmmCasMsgBuf.apBufMsg[i]     = VOS_NULL_PTR;
            gstGmmCasMsgBuf.aucBufMsgFlg[i] = GMM_MSG_BUFFER_FLAG_IDLE;

            gstGmmCasMsgBuf.ucBufMsgTotal--;
            break;
        }
    }
    return;
}

/*****************************************************************************
 Prototype      : GMM_BufferMsgResume
 Description    : GMM挂起消息的恢复处理过程
                  HSS 4100 V200R001 新增
 Input          :
 Output         :
 Return Value   :
 Calls          :
 Called By      :

 History        :
  1.Date        : 2005-08-25
    Author      : Roger Leo
    Modification: Created function
*****************************************************************************/
VOS_VOID GMM_BufferMsgResume(VOS_VOID)
{
    VOS_UINT32  ulIndex = 0;

/*
    if (GMM_FALSE == gstGmmCasGlobalCtrl.ucBufMsgResFlg)
    {
        return GMM_FALSE;
    }

    gstGmmCasGlobalCtrl.ucBufMsgResFlg = GMM_FALSE;
*/

    /* 判断是否存在缓存消息 */
    if ( 0 == gstGmmCasMsgBuf.ucBufMsgTotal )
    {
        /* 不存在缓存消息 */
        GMM_LOG_WARN("GMM_BufferMsgResume():Warning: Buffer is empty");
        return;               /* 结束返回 */
    }

    /* 顺序检查缓存队列中的缓存消息 */
    for (ulIndex=0; ulIndex<GMM_CAS_MSG_NUMBER_MAX; ulIndex++)
    {
        /* 发送缓存消息队列头端的消息 */
        if (GMM_FALSE == GMM_BufferMsgSend())
        {
            continue;
        }

        /* 释放缓存消息内容 */
        Gmm_MemFree(gstGmmCasMsgBuf.apBufMsg[ulIndex]);
        /* VOS_MemFree(WUEPS_PID_GMM, gstGmmCasMsgBuf.apBufMsg[ulIndex]); */

        gstGmmCasMsgBuf.apBufMsg[ulIndex] = VOS_NULL_PTR;   /* 置空指针 */

        /* 置指针释放标志 */
        gstGmmCasMsgBuf.aucBufMsgFlg[ulIndex]  = GMM_MSG_BUFFER_FLAG_IDLE;

        gstGmmCasMsgBuf.ucBufMsgTotal--;

        /* 缓存消息总数更新 */
        if (0 == gstGmmCasMsgBuf.ucBufMsgTotal)
        {
            break;
        }

    }

    return;                    /* 结束返回 */
}

/*****************************************************************************
 Prototype      : GMM_BufferMsgDump
 Description    : 缓存消息队列中的消息清空
                  HSS 4100 V200R001 新增
 Input          :
 Output         :
 Return Value   :
 Calls          :
 Called By      :

 History        :
  1.Date        : 2005-08-25
    Author      : Roger Leo
    Modification: Created function

  2.日    期   : 2014年9月26日
    作    者   : w00167002
    修改内容   : DTS2014091904027:GSM下，在gmm上报DETACH时候，用户发起电话，GMM被
                挂起，发起PDP业务，GMM缓存GMMSM_ESTABLISH_REQ消息，在电话挂断后，
                GAS上报GPRS resume fail,GMM会清空缓存，但没给SM上报EST CNF消息。
                后续GMM注册成功，SM依然等待EST CNF消息直到定时器超时。
*****************************************************************************/
VOS_VOID GMM_BufferMsgDump(VOS_VOID)
{
    VOS_UINT32  ulIndex;

    MSG_HEADER_STRU                     *pNasMsgHeader = VOS_NULL_PTR;

    /* 判断是否存在缓存消息 */
    if ( 0 == gstGmmCasMsgBuf.ucBufMsgTotal )
    {
        /* 不存在缓存消息 */
        GMM_LOG_WARN("GMM_BufferMsgDump():Warning: Buffer is already empty");
        return;               /* 结束返回 */
    }

    /* 顺序释放缓存队列中的缓存消息指针 */
    for (ulIndex=0; ulIndex<GMM_CAS_MSG_NUMBER_MAX; ulIndex++)
    {
        /* 缓存消息已释放 */
        if (GMM_MSG_BUFFER_FLAG_IDLE
         == gstGmmCasMsgBuf.aucBufMsgFlg[ulIndex])
        {
            continue;
        }


        /* 在释放缓存时候，给SM回复结果，否则SM模块一直等待此结果至定时器超时 */
        pNasMsgHeader = (MSG_HEADER_STRU *)gstGmmCasMsgBuf.apBufMsg[ulIndex];
        if ((WUEPS_PID_SM           == pNasMsgHeader->ulSenderPid)
         && (GMMSM_ESTABLISH_REQ    == pNasMsgHeader->ulMsgName))
        {
            Gmm_SndSmEstablishCnf(GMM_SM_EST_FAILURE, GMM_SM_CAUSE_UNKNOWN);
        }

        /* 释放消息指针内容 */
        Gmm_MemFree(gstGmmCasMsgBuf.apBufMsg[ulIndex]);
        /* VOS_MemFree(WUEPS_PID_GMM, gstGmmCasMsgBuf.apBufMsg[ulIndex]); */
        gstGmmCasMsgBuf.apBufMsg[ulIndex] = VOS_NULL_PTR;   /* 置空指针 */

        /* 置指针释放标志 */
        gstGmmCasMsgBuf.aucBufMsgFlg[ulIndex]  = GMM_MSG_BUFFER_FLAG_IDLE;

        /* 缓存消息总数更新 */
        if (gstGmmCasMsgBuf.ucBufMsgTotal > 0)
        {
            gstGmmCasMsgBuf.ucBufMsgTotal--;
        }
        else
        {
            gstGmmCasMsgBuf.ucBufMsgTotal = 0;
        }
    }

    return;                    /* 结束返回 */
}

/*****************************************************************************
 函 数 名  : NAS_GMM_BackupCcoFallbackCtx
 功能描述  : 对CCO 回退流程需要的GMM上下文进行备份，当CCO回退时，GMM直接
              可以恢复到正常服务
 输入参数  : 无
 输出参数  : 无
 返 回 值  : 无
 调用函数  :
 被调函数  :

 修改历史      :
 1.日    期   : 2011年7月12日
   作    者   : h44270
   修改内容   : 新生成函数
 2.日    期   : 2012年03月08日
   作    者   : l00130025
   修改内容   : DTS2012030107623: G->W Est_Rej_Cogest,CCO回退过程，Eplmn被删除，导致受限驻留
 3.日    期   : 2012年3月15日
   作    者   : z00161729
   修改内容   : V7R1 C50 ISR特性修改
 4.日    期   : 2013年2月4日
   作    者   : w00176964
   修改内容   : DTS2011082402748:EST CNF fail导致CCO回退时,3311不需要恢复启动
*****************************************************************************/
VOS_VOID NAS_GMM_BackupCcoFallbackCtx(VOS_VOID)
{
    /* 对g_GmmGlobalCtrl.stBackShare进行赋值，将g_GmmGlobalCtrl.stBackShare
       的成员取值均来自g_GmmGlobalCtrl的其他成员变量 */
    g_GmmGlobalCtrl.stBackupShare.ucState                   = g_GmmGlobalCtrl.ucState;

    g_GmmGlobalCtrl.stBackupShare.ucNtMod                   = g_GmmGlobalCtrl.ucNetMod;

    g_GmmGlobalCtrl.stBackupShare.ucPsSigConnFlg            = g_GmmGlobalCtrl.ucSigConFlg;

    g_GmmGlobalCtrl.stBackupShare.enPsIntegrityProtect      = g_MmSubLyrShare.GmmShare.ucPsIntegrityProtect;

    g_GmmGlobalCtrl.stBackupShare.ucRauAttmptCnt            = g_GmmRauCtrl.ucRauAttmptCnt;

    g_GmmGlobalCtrl.stBackupShare.ucSrvState                = gstGmmCasGlobalCtrl.GmmSrvState;

    /* PS域的security information */
    g_GmmGlobalCtrl.stBackupShare.stPsSecutityInfo = g_GmmGlobalCtrl.PsSecutityInfo;

    /* 上次驻留的系统信息  */
    g_GmmGlobalCtrl.stBackupShare.stSysInfo = g_GmmGlobalCtrl.SysInfo;


    /* UE 信息 */
    g_GmmGlobalCtrl.stBackupShare.stUeInfo =  g_GmmGlobalCtrl.UeInfo;
    g_GmmGlobalCtrl.stBackupShare.stUeInfo.ucUpdateSta = NAS_MML_GetPsUpdateStatus();


    PS_MEM_CPY(&(g_GmmGlobalCtrl.stBackupShare.stBackupEquPlmnInfo),
               NAS_MML_GetEquPlmnList(), sizeof(NAS_MML_EQUPLMN_INFO_STRU));


#if (FEATURE_ON == FEATURE_LTE)
    g_GmmGlobalCtrl.stBackupShare.enTinType = NAS_MML_GetTinType();
#endif

    g_GmmGlobalCtrl.stBackupShare.ucT3311Status = (g_GmmTimerMng.ulTimerRunMask & (0x00000001 << GMM_TIMER_T3311));
}


/*****************************************************************************
 函 数 名  : NAS_GMM_ResumeCcoFallbackCtx
 功能描述  : 对CCO 回退流程，恢复为CCO流程发起时的GMM参数
 输入参数  : 无
 输出参数  : 无
 返 回 值  : 无
 调用函数  :
 被调函数  :

 修改历史      :
 1.日    期   : 2011年7月12日
   作    者   : h44270
   修改内容   : 新生成函数
 2.日    期   : 2012年03月08日
   作    者   : l00130025
   修改内容   : DTS2012030107830:CCO回退过程，停掉挂起的定时器
 3.日    期   : 2012年03月08日
   作    者   : l00130025
   修改内容   : DTS2012030107623: G->W Est_Rej_Cogest,CCO回退过程，Eplmn被删除，导致受限驻留
 4.日    期   : 2012年3月15日
   作    者   : z00161729
   修改内容   : V7R1 C50 ISR特性修改
 5.日    期   : 2012年9月07日
   作    者   : l00171473
   修改内容   : DTS2012081701006, 添加GMM状态的可维可测消息
 6.日    期   : 2013年2月4日
   作    者   : w00176964
   修改内容   : DTS2011082402748:EST CNF fail导致CCO回退时,3311不需要恢复启动
 7.日    期   : 2013年3月20日
   作    者   : w00176964
   修改内容   : DTS2012112909686:W CCO到G，G下RAU无响应，超时回退到W未停止T3312
*****************************************************************************/
VOS_VOID NAS_GMM_ResumeCcoFallbackCtx(VOS_VOID)
{

    /* 对g_GmmGlobalCtrl的成员变量赋值，赋值的来源
       来自于g_GmmGlobalCtrl.stBackupShare */

    NAS_MML_EQUPLMN_INFO_STRU          *pstBackupEplmnList;
    NAS_MML_EQUPLMN_INFO_STRU          *pstCurrentEplmnList;

#if (FEATURE_ON == FEATURE_LTE)
    NAS_MML_RPLMN_CFG_INFO_STRU        *pstRplmnCfgInfo = VOS_NULL_PTR;

    pstRplmnCfgInfo = NAS_MML_GetRplmnCfg();
#endif


    g_GmmGlobalCtrl.ucState                                 = g_GmmGlobalCtrl.stBackupShare.ucState;

    g_GmmGlobalCtrl.ucNetMod                                = g_GmmGlobalCtrl.stBackupShare.ucNtMod;

    g_GmmGlobalCtrl.ucSigConFlg                             = g_GmmGlobalCtrl.stBackupShare.ucPsSigConnFlg;

    g_MmSubLyrShare.GmmShare.ucPsIntegrityProtect           = g_GmmGlobalCtrl.stBackupShare.enPsIntegrityProtect;

    g_GmmRauCtrl.ucRauAttmptCnt                             = g_GmmGlobalCtrl.stBackupShare.ucRauAttmptCnt;

    gstGmmCasGlobalCtrl.GmmSrvState                         = g_GmmGlobalCtrl.stBackupShare.ucSrvState;

    /* PS域的security information */
    g_GmmGlobalCtrl.PsSecutityInfo = g_GmmGlobalCtrl.stBackupShare.stPsSecutityInfo;

    /* 上次驻留的系统信息  */
    g_GmmGlobalCtrl.SysInfo = g_GmmGlobalCtrl.stBackupShare.stSysInfo;

    /* UE 信息 */
    g_GmmGlobalCtrl.UeInfo = g_GmmGlobalCtrl.stBackupShare.stUeInfo;

    NAS_MML_SetPsUpdateStatus(g_GmmGlobalCtrl.stBackupShare.stUeInfo.ucUpdateSta);


    NAS_GMM_LogGmmStateInfo(g_GmmGlobalCtrl.ucState);

    GMM_ResumeTimer(GMM_TIMER_NOT_RESUME);

    pstBackupEplmnList  = &(g_GmmGlobalCtrl.stBackupShare.stBackupEquPlmnInfo);

    pstCurrentEplmnList = NAS_MML_GetEquPlmnList();

    if (VOS_TRUE == NAS_MML_IsEquPlmnInfoChanged(pstBackupEplmnList))
    {
        /* 将EPLMN保存到MML全局变量 */
        PS_MEM_CPY(pstCurrentEplmnList, pstBackupEplmnList, sizeof(NAS_MML_EQUPLMN_INFO_STRU));

        /* 将EPLMN更新到NV中 */
        NAS_GMM_WriteEplmnNvim(pstCurrentEplmnList);
    }


 #if (FEATURE_ON == FEATURE_LTE)
    NAS_GMM_WriteTinInfoNvim(g_GmmGlobalCtrl.stBackupShare.enTinType, pstRplmnCfgInfo->aucLastImsi);
    if (NAS_MML_TIN_TYPE_RAT_RELATED_TMSI != g_GmmGlobalCtrl.stBackupShare.enTinType)
    {
        Gmm_TimerStop(GMM_TIMER_T3323);

        /* ISR去激活，需要更新pdp激活是在ISR激活前激活的 */
        NAS_MML_UpdateAllPsBearIsrFlg(NAS_MML_PS_BEARER_EXIST_BEFORE_ISR_ACT);
    }

 #endif

    /* 根据备份前的3311定时器状态恢复启动 */
    if (0 != (g_GmmGlobalCtrl.stBackupShare.ucT3311Status & (0x00000001 << GMM_TIMER_T3311)))
    {
        Gmm_TimerStart(GMM_TIMER_T3311);
    }


#if (defined(__PS_WIN32_RECUR__)) || ( VOS_WIN32 == VOS_OS_VER )
#else
{
    /* W下PMM-CONNECTED态需要停止3312 */
    if ((NAS_MML_NET_RAT_TYPE_WCDMA == NAS_MML_GetCurrNetRatType())
     && (GMM_TRUE == g_GmmGlobalCtrl.ucSigConFlg))
    {
#if (FEATURE_LTE == FEATURE_ON)
        NAS_GMM_SndLmmTimerInfoNotify(GMM_TIMER_T3312, GMM_LMM_TIMER_STOP);
#endif
        Gmm_TimerStop(GMM_TIMER_T3312);
    }

    /* G下ready timer在运行则停止3312 */
    if ((NAS_MML_NET_RAT_TYPE_WCDMA == NAS_MML_GetCurrNetRatType())
     && (GMM_TIMER_T3314_FLG == (g_GmmTimerMng.ulTimerRunMask & GMM_TIMER_T3314_FLG)))
    {
#if (FEATURE_LTE == FEATURE_ON)
        NAS_GMM_SndLmmTimerInfoNotify(GMM_TIMER_T3312, GMM_LMM_TIMER_STOP);
#endif
        Gmm_TimerStop(GMM_TIMER_T3312);
    }
}

#endif
}



/*****************************************************************************
 Prototype      : GMM_RcvMmcSuspendInd
 Description    : 收到MMC挂起指示的处理
                  HSS 4100 V200R001 新增
 Input          :
 Output         :
 Return Value   :
 Calls          :
 Called By      :

 History        :
  1.Date        : 2005-08-25
    Author      : Roger Leo
    Modification: Created function
  2.日    期   : 2010年09月27日
    作    者   : z00161729
    修改内容   : 问题单号：AT2D19560
  3.日    期   : 2010年12月23日
    作    者   : s46746
    修改内容   : DTS2010122305821:GPRS数传过程中高优先级定时器超时会发起指定搜网
  4.日    期   : 2011年7月12日
    作    者   : h44270
    修改内容   : V7R1 PhaseII阶段调整，用于缓存CCO流程中的GMM全局变量
  5.日    期   : 2011年7月13日
    作    者   : w00176964
    修改内容   : V7R1 PhaseII阶段调整，向RABM指示RAB是否需要重建
  6.日    期   : 2011年7月28日
    作    者   : sunxibo 46746
    修改内容   : V7R1 phase II,autoplmnsrch状态机调整为PlmnSelection状态机
  7.日    期   : 2011年10月8日
    作    者   : l00171473
    修改内容   : V7R1 phase II,TC环回调整，MMC不维护TC状态
  8.日    期   : 2011年10月27日
    作    者   : s46746
    修改内容   : V7R1 PhaseIII,支持L模联合注册
  9.日    期   : 2011年12月2日
    作    者   : s46746
    修改内容   : 从L异系统改变到GU后，没有指派加密密钥到GU接入层
  7.日    期   : 2012年2月27日
    作    者   : z00161729
    修改内容   : V7R1 C50 支持ISR修改
  8.日    期   : 2012年04月11日
    作    者   : z00161729
    修改内容  : csfb mt L重定向到W失败回退到L，再csfb mt失败
  9.日    期   : 2012年04月24日
    作    者   : w00166186
    修改内容   : DTS2012042303735，从L CCO到G后再重选会L，第一次TAU失败
 10.日    期   : 2012年09月24日
    作    者   : z00161729
    修改内容   : DTS2012072701845:日本外场测试ISR激活L HO到GU未向L获取安全上下文概率出现ho失败
  11.日    期   : 2012年10月10日
     作    者   : z00161729
     修改内容   : DTS201210100991:csfb mt到g，lai未改变呼叫结束后rel ind指示重定向到l，未做tau
  12.日    期   : 2012年11月15日
     作    者   : w00176964
     修改内容   : TD->L进行异系统操作时,不需要在TC状态起2S定时器延迟给RRC回复

  13.日    期   : 2012年12月10日
    作    者   : z40661
    修改内容   : DTS2012120705386,异系统过程中,目标系统为G模时,需要通知GAS RAI,PTMSI

  14.日    期   : 2012年12月10日
     作    者   : z40661
     修改内容   : DTS2012122105035,异系统过程中,目标系统为G模时,需要通知PS域Attach状态
  15.日    期   : 2011年12月28日
     作    者  : l00167671
     修改内容  : 修改问题单DTS2012122001075,问题单场景如下:
                 PS建链过程中发生RA改变，该场景中如果CS域有业务则PS域做RAU
                 会被不确定的推迟到CS连接释放时才做，修改此场景中的操作如下:
                 若CS域有业务则给WAS发送RRMM_REL_REQ请求，请WAS释放连接，
                 并保存系统消息。在收到WAS的RRMM_REL_IND时用保存的系统消息做RAU
  16.日    期   : 2013年08月07日
     作    者  : l65478
     修改内容  : 修改问题单DTS2013080502397,在备份原来的状态时,如果原来已经是挂起状态,需要备份,否则恢复状态时可能导致GMM的状态恢复到挂起状态
  17.日    期   : 2013年11月1日
     作    者   : z00161729
     修改内容   : DTS2013110103529:L重建到gu，ISR激活位置区未改变，gmm未发起rau
  18.日    期   : 2013年9月24日
     作    者   : w00176964
     修改内容   : Volte_phaseII 项目:PS的安全上下文增加备份恢复机制
  19.日    期   : 2015年1月12日
     作    者   : s00217060
     修改内容   : Service_State_Optimize_PhaseI修改
*****************************************************************************/
VOS_VOID GMM_RcvMmcSuspendInd(VOS_VOID* pRcvMsg)
{
    MMCGMM_SUSPEND_IND_ST              *pSuspendIndMsg;
    NAS_UTRANCTRL_UTRAN_MODE_ENUM_UINT8 enCurUtranMode;

#if (FEATURE_ON == FEATURE_LTE)
    VOS_UINT32                          ulGprsSuspendFlg;


    ulGprsSuspendFlg    = VOS_FALSE;
#endif

    /* GSM模式处理过程 */
    pSuspendIndMsg      = (MMCGMM_SUSPEND_IND_ST *)pRcvMsg;

    GMM_LOG_INFO("GMM_RcvMmcSuspendInd:Receive MMC_SUSPEND_IND");

    /* 停HO等待系统消息定时器 */
    Gmm_TimerStop(GMM_TIMER_HO_WAIT_SYSINFO);

    NAS_MML_SetPsTbfStatusFlg(VOS_FALSE);

    NAS_GMM_FreeGsmSysInfo();

    NAS_GMM_FreeWasSysInfo();

    /* 指示RABM当前系统模式, 并挂起RABM, bRatChangeFlg为TRUE */
    NAS_GMM_SndRabmSysSrvChgInd(pSuspendIndMsg->ucSuspendOrigen,
                                VOS_TRUE,
                                VOS_TRUE,
                                VOS_TRUE);



    if ( NAS_MML_NET_RAT_TYPE_GSM == pSuspendIndMsg->ucSuspendDestination)
    {
        NAS_GMM_SndGasInfoChangeReq(RRC_NAS_MASK_PTMSI_RAI | RRC_NAS_MASK_ATTACH);
    }

    switch (g_GmmGlobalCtrl.ucState)
    {
        case GMM_GPRS_SUSPENSION:
            gstGmmCasGlobalCtrl.GmmSrvState       = gstGmmSuspendCtrl.ucPreSrvState;

#if (FEATURE_ON == FEATURE_LTE)
            ulGprsSuspendFlg    = VOS_TRUE;
#endif

            break;

        case GMM_SUSPENDED_GPRS_SUSPENSION:
        case GMM_SUSPENDED_WAIT_FOR_SYSINFO:
            Gmm_TimerStop(GMM_TIMER_SUSPENDED);
            GMM_ResumeFailure();
            break;

        case GMM_SUSPENDED_NORMAL_SERVICE:
            GMM_LOG_WARN("GMM_RcvGasSuspensionInd:Receive RRMM_GPRS_SUSPENSION_IND in abnormal state.");
            return;
        case GMM_ROUTING_AREA_UPDATING_INITIATED:
            if (GMM_RAU_FOR_NORMAL != gstGmmSuspendCtrl.ucRauCause)
            {
                GMM_BufferMsgDump();
            }
            break;
        case GMM_DEREGISTERED_INITIATED:
            if (GMM_AGENT_USIM_AUTHENTICATION_CNF_FLG
                == (g_GmmReqCnfMng.ucCnfMask
                & GMM_AGENT_USIM_AUTHENTICATION_CNF_FLG))
            {
                Gmm_TimerStop(GMM_TIMER_PROTECT);
                g_GmmReqCnfMng.ucCnfMask
                    &= ~GMM_AGENT_USIM_AUTHENTICATION_CNF_FLG;
            }
            /*异系统改变时,如果RA发生改变，则RAU完成后继续Detach流程，
            如果RA没有改变，则通过Detach定时器超时保证Detach流程继续。异系统不改变时
            直接重新开始Detach流程*/
            g_GmmGlobalCtrl.ucFollowOnFlg = GMM_TRUE;
            NAS_MML_SetPsServiceBufferStatusFlg(VOS_TRUE);

            g_GmmGlobalCtrl.ucSpecProcHold = g_GmmGlobalCtrl.ucSpecProc;
            break;
        default:
            break;
    }

    /*保存切换之前的状态和网络模式*/
    if ((GMM_GPRS_SUSPENSION != g_GmmGlobalCtrl.ucState)
     && (GMM_SUSPENDED_NORMAL_SERVICE != g_GmmGlobalCtrl.ucState)
     && (GMM_SUSPENDED_GPRS_SUSPENSION != g_GmmGlobalCtrl.ucState)
     && (GMM_SUSPENDED_WAIT_FOR_SYSINFO != g_GmmGlobalCtrl.ucState))
    {
        gstGmmSuspendCtrl.ucPreState                  = g_GmmGlobalCtrl.ucState;
    }

    gstGmmSuspendCtrl.ucPreRat                    = NAS_MML_GetCurrNetRatType();
    gstGmmSuspendCtrl.ucSuspendCause              = pSuspendIndMsg->ucSuspendCause;

    /* 获取切换之前的服务状态 */
    if (NAS_MML_NET_RAT_TYPE_WCDMA == NAS_MML_GetCurrNetRatType())
    {
        if (VOS_TRUE == NAS_GMM_IsDeregisterState(g_GmmGlobalCtrl.ucState))
        {
            gstGmmSuspendCtrl.ucPreSrvState       = GMM_IU_PMM_DETACHED;
        }
        else if (GMM_TRUE == g_GmmGlobalCtrl.ucSigConFlg)
        {
            gstGmmSuspendCtrl.ucPreSrvState       = GMM_IU_PMM_CONNECTED;
        }
        else
        {
            gstGmmSuspendCtrl.ucPreSrvState       = GMM_IU_PMM_IDLE;
        }
    }
    else if (NAS_MML_NET_RAT_TYPE_GSM == NAS_MML_GetCurrNetRatType())
    {
        gstGmmSuspendCtrl.ucPreSrvState           = gstGmmCasGlobalCtrl.GmmSrvState;
    }
    else
    {
        ;
    }

    if (MMC_SUSPEND_CAUSE_CELLCHANGE == pSuspendIndMsg->ucSuspendCause)
    {
        /* 备份GMM的全局变量，用于CCO回退时使用 */
        NAS_GMM_BackupCcoFallbackCtx();
    }


    GMM_SuspendTimer();

    Gmm_ComStaChg(GMM_SUSPENDED_NORMAL_SERVICE);

    /* HO过程中，L进行挂起请求时，需要向L获取安全上下文 */
#if   (FEATURE_ON == FEATURE_LTE)
    /* 3GPP 24008 4.7.5.1.1章节描述:
       If the routing area updating procedure is not initiated by the MS due to
       an S1 mode to Iu mode or S1 mode to A/Gb mode intersystem change,
       or if it is initiated due to such an intersystem change and the TIN
       indicates "RAT related TMSI", the MS shall use the existing UMTS
       security context for the PS domain. The ROUTING AREA UPDATE REQUEST
       message shall contain the P-TMSI signature when received in a previous
       ATTACH ACCEPT or ROUTING AREA UPDATE ACCEPT message.
       If the MS has a valid UMTS security context, the MS shall indicate
       it in the GPRS ciphering key sequence number IE.*/

    if ((MMC_SUSPEND_CAUSE_HANDOVER == pSuspendIndMsg->ucSuspendCause)
     && (NAS_MML_NET_RAT_TYPE_LTE == pSuspendIndMsg->ucSuspendOrigen))
    {
        /* Added by w00176964 for VoLTE_PhaseII 项目, 2013-9-24, begin */
        /* 备份PS的安全上下文,由于HO失败的回退 */
        PS_MEM_CPY(&(g_GmmGlobalCtrl.stBackupShare.stSimPsSecurity),
                   NAS_MML_GetSimPsSecurity(), sizeof(NAS_MML_SIM_PS_SECURITY_INFO_STRU));

        /* Added by w00176964 for VoLTE_PhaseII 项目, 2013-9-24, end */

        /* 给L模发送GMM_LMM_HO_SECU_INFO_REQ */
        NAS_GMM_SndLmmHoSecuInfoReq();

        gstGmmSuspendCtrl.ucGetLteSecContext = VOS_TRUE;

        /* 启动定时器 */
        Gmm_TimerStart(GMM_TIMER_WAIT_GET_HO_SECU_INFO_CNF);

        return;
    }
    /* 如果挂起目的方为LTE，通知LMM模块Gmm的连接状态 */
    if ((NAS_MML_NET_RAT_TYPE_LTE == pSuspendIndMsg->ucSuspendDestination)
     && (NAS_MML_NET_RAT_TYPE_LTE != pSuspendIndMsg->ucSuspendOrigen))
    {
        /* 只带G模的连接状态,不带PS域状态是挂起还是正常，在收到gas的gprs suspend ind消息时通知 */
        NAS_GMM_SndLmmInfoChangeNotifyReq(NAS_MML_GetCurrNetRatType(),
                                          VOS_TRUE,
                                          VOS_FALSE,
                                          gstGmmSuspendCtrl.ucPreSrvState,
                                          ulGprsSuspendFlg);
    }

#endif

#if (defined(__PS_WIN32_RECUR__)) || ( VOS_WIN32 == VOS_OS_VER )
    if (1 == g_ulGmmDelaySuspendRsp)
    {
        Gmm_TimerStart(GMM_TIMER_TC_DELAY_SUSPEND_RSP);
        return;
    }
#endif


    /* 由于GCF测试原因，TC状态下，在W2G的异系统切换情况下，需要延迟一定时间再回复
       挂起结果。于是启动定时器，待定时器超时后再回复挂起结果。
       由于此处状态已迁移，故使用切换之前GMM状态进行判断。
       W2L挂起时，此处不知道挂起的目的方，故也会做此处理，但只会延迟上报挂起结果，没有其它影响 */
    /* 挂起目的方为GSM,启动定时器,为LTE时不启动定时器 */
    enCurUtranMode = NAS_UTRANCTRL_GetCurrUtranMode();

    if ((NAS_MML_NET_RAT_TYPE_WCDMA == NAS_MML_GetCurrNetRatType())
     && (GMM_TC_ACTIVE == gstGmmSuspendCtrl.ucPreState)
     && (NAS_UTRANCTRL_UTRAN_MODE_FDD == enCurUtranMode)
     && (NAS_MML_NET_RAT_TYPE_GSM == pSuspendIndMsg->ucSuspendDestination))
    {
        Gmm_TimerStart(GMM_TIMER_TC_DELAY_SUSPEND_RSP);
        return;
    }


    Gmm_TimerStart(GMM_TIMER_SUSPENDED);

    GMM_SndMmcSuspendRsp();
}

/*****************************************************************************
 Prototype      : GMM_RcvMmcResumeInd
 Description    : 收到MMC恢复指示的处理
                  HSS 4100 V200R001 新增
 Input          :
 Output         :
 Return Value   :
 Calls          :
 Called By      :

 History        :
  1.Date        : 2005-08-25
    Author      : Roger Leo
    Modification: Created function
  2.日    期   : 2007年07月14日
    作    者   : luojian id:60022475
    修改内容   : 根据问题单号：A32D12436
  3.日    期   : 2007年09月21日
    作    者   : luojian id:107747
    修改内容   : 根据问题单号：AT2D01670
  4.日    期   : 2007年09月21日
    作    者   : l00130025
    修改内容   : 根据问题单号：AT2D11326,G下数传时发起了HPLMN搜索
  5.日    期   : 2010年8月14日
    作    者   : s46746
    修改内容   : DTS2010073001405,G2W异系统重选后，不向层2发送去指派而是挂起层2
  6.日    期   : 2010年9月9日
    作    者   : z00161729
    修改内容   : DTS2010090800871,W下进行PS业务，G下设置为接入禁止，
                 W2G2W直接进入紧急驻留状态，无法正常提供正常业务
  7.日    期   : 2010年09月27日
    作    者   : z00161729
    修改内容   : 问题单号：AT2D19560
  8.日    期   : 2010年09月27日
    作    者   : z00161729
    修改内容   : 问题单号：DTS2010122404478,W挂起NAS后，用户发起PDP激活，重选失败后
                 重回到W下，未发起PDP激活。
  9.日    期   : 2011年3月3日
    作    者   : z00161729
    修改内容   : DTS2011021201997:PS、CS完整性保护是否开启由GMM和MM分开维护,MMC不再维护
 10.日    期   : 2011年7月12日
    作    者   : h44270
    修改内容   : V7R1 PhaseII阶段调整，用于恢复CCO流程开始前的GMM全局变量
 11.日    期   : 2011年7月13日
    作    者   : w00176964
    修改内容   : V7R1 PhaseII阶段调整，向RABM指示RAB是否需要重建
 12.日    期   : 2011年07月29日
	作    者   : L65478
	修改内容   : 根据问题单号：DTS2011072503161,CS ONLY在重选过程中,发起PDP激活
 13.日    期   : 2011年05月03日
    作    者   : l65478
    修改内容   : 问题单DTS2011043000267,ready状态，G->W->G CCO,在W下接入禁止,在W下没有启动T3312
 14.日    期   : 2011年4月13日
    作    者   : l65478
    修改内容   : DTS2011041100237:在W下进行服务请求的过程中，发生W->G的cell change，到G后，没有发起RAU，导致后续PS业务无法发起
 15.日    期   : 2011年11月11日
    作    者   : l00130025
    修改内容   : DTS2011091607198: 无卡，W下重选到L模后，Resume处理Gmm的状态错误,
                 迁移到GMM_REGISTERED_NO_CELL_AVAILABLE，导致L丢网到W下发起了RAU
 16.日    期   : 2011年12月8日
    作    者   : s46746
    修改内容   : 问题单号：DTS2011111603445,接收到系统消息而且层2已经指派后才能恢复RABM
 17.日    期   : 2011年12月24日
    作    者   : w00166186
    修改内容   : L -CCO/HO-W后，链路存在，发起RAU又发起了建链请求
 18.日    期   : 2011年12月1日
    作    者   : w00176964
    修改内容   : V7R1 PhaseIV 调整:RRC链接维护调整
 19.日    期   : 2012年03月08日
    作    者   : l00130025
    修改内容   : DTS2012030107830: G->W Est_Rej_Cogest,CCO回退过程，T3211没有停止，导致错误发起LAU,LAU Type错误
 20.日    期   : 2012年04月16日
    作    者   : w00166186
    修改内容   : DTS2012041601505，service req状态重定向，挂起过程收到SM_data_req,重复发送业务请求
 21.日    期   : 2012年3月3日
    作    者   : z00161729
    修改内容   : V7R1 C50 支持ISR修改
 22.日    期   : 2012年5月16日
    作    者   : l00171473
    修改内容   : DTS2012051501127, 进入TC状态后, W2G时未通知GPHY.
 23.日    期   : 2012年06月03日
    作    者   : l65478
    修改内容   : DTS2012060201181, 从G回退到W后，不处理网络的消息.

 23.日    期   : 2012年6月9日
    作    者   : z40661
    修改内容   : PDP激活过程中异系统从GU到L，PDP激活失败，实际后续APS会给ESM
                 发送，此处不需要给SM回复service rej。
 24.日    期   : 2012年6月21日
    作    者   : l00171473
    修改内容   : DTS2012061908142, L到W的HO失败回退到W, 不需通知 RABM 等待等待W接入层RAB的恢复
 25.日    期   : 2012年7月04日
    作    者   : l00171473
    修改内容   : DTS2012070202083, W到L的异系统流程, 此时W接入层已清除了PDCP, 此时需通知RABM
                 以便RABM清除W的RAB信息
 26.日    期   : 2013年2月06日
    作    者   : w00176964
    修改内容   : DTS2013020601874:gmm内存泄露清理
 27.日    期   : 2013年2月4日
    作    者   : w00176964
    修改内容   : DTS2011082402748:EST CNF fail导致CCO回退时,3311不需要恢复启动
 28.日    期   : 2013年7月22日
    作    者   : z00161729
    修改内容   : DTS2013071908566:rau init状态从w cco到g再回退到w，gmm不重新发起rau
 29.日    期   : 2013年08月16日
    作    者   : l65478
    修改内容   : DTS2013081400197,T3314超时后,不能终止当前的注册过程
 30.日    期   : 2013年08月16日
    作    者   : l65478
    修改内容   : DTS2013092202614,G CCO到W失败回退到G,在G下通知了GAS进入了REDAY态
 31.日    期   : 2013年08月16日
    作    者   : l65478
    修改内容   : DTS2013091003969,L handover to W后收到鉴权消息没有处理
 32.日    期   : 2013年9月22日
    作    者   : w00176964
    修改内容   : Volte_phaseII 项目:增加PS安全上下文失败回退处理
 33.日    期   : 2014年2月8日
    作    者   : s00246516
    修改内容   : L-C互操作项目:增加异系统到HRPD的处理
 34.日    期   : 2014年6月17日
   作    者   : z00234330
   修改内容   : PCINT清理
 35.日    期   : 2014年8月19日
    作    者    : b00269685
    修改内容    : L->GU,CS handover重新获取重定向的安全上下文
 36.日    期   : 2014年12月25日
    作    者   : w00167002
    修改内容   : DTS2014122201960:在L下SRVCC HO到G再HO到W,RABM触发重建，导致立即
                 触发RAU，后续收到系统消息又再次发起RAU,导致网络REL了链路，导致
                 掉话。修改为在HO后，启动保护定时器等系统消息。
 37.日    期   : 2014年12月13日
    作    者   : s00217060
    修改内容   : Service_State_Optimize_PhaseI 切换流程修改
*****************************************************************************/
VOS_VOID GMM_RcvMmcResumeInd(VOS_VOID* pRcvMsg)
{
    MMCGMM_RESUME_IND_ST                *pResumeIndMsg;
    NAS_MML_NET_RAT_TYPE_ENUM_UINT8      enCurrNetType;


    enCurrNetType = NAS_MML_GetCurrNetRatType();
    /* GSM模式处理过程 */
    pResumeIndMsg = (MMCGMM_RESUME_IND_ST *)pRcvMsg;

    /* 收到resume ind消息后恢复RABM的处理 */
    NAS_GMM_ProcRabmSysSrvChgInd_ResumeInd();

    /* 收到resume ind消息后PS信令链接的处理 */
    NAS_GMM_ProcPsSigConn_ResumeInd(pResumeIndMsg);


    /* GMM向mmc发送resume rsp */
    NAS_GMM_SndMmcResumeRsp();


    if (GMM_SUSPENDED_NORMAL_SERVICE != g_GmmGlobalCtrl.ucState)
    {
        GMM_LOG_WARN("GMM_RcvMmcResumeInd:Receive MMCGMM_RESUME_IND in abnormal State.");
        return;
    }


    NAS_GMM_RcvMmcResumeInd_CcoFallbak();

    NAS_GMM_RcvMmcResumeInd_Handover(pResumeIndMsg);

    /*如果发生过系统间改变，需要通知接入层PTMSI信息*/
    if ( ( gstGmmSuspendCtrl.ucPreRat != enCurrNetType )
      && ( ( NAS_MML_NET_RAT_TYPE_WCDMA == enCurrNetType )
        || ( NAS_MML_NET_RAT_TYPE_GSM == enCurrNetType ) ) )
    {
        /* 异系统到GU的处理 */
        NAS_GMM_ProcResumeToGU(pResumeIndMsg);
    }

    if (NAS_MML_NET_RAT_TYPE_GSM == enCurrNetType)
    {
        g_GmmGlobalCtrl.ucSigConFlg = GMM_TRUE;

        /* GMM_TIMER_PROTECT_FOR_SIGNALING 不需要恢复 */
        gstGmmSuspendCtrl.ulTimerRunMask &= ~(VOS_UINT32)(0x00000001 << GMM_TIMER_PROTECT_FOR_SIGNALING);

        g_GmmReqCnfMng.ucCnfMask &= ~GMM_RRC_RRMM_EST_CNF_FLG;

        /* T3340不需要恢复 */
        gstGmmSuspendCtrl.ulTimerRunMask &= ~(VOS_UINT32)(GMM_TIMER_T3340_FLG);

        /*如果PS域有短消息待发送，则通知SMS模块发送失败*/
        if (GMM_TRUE == g_GmmServiceCtrl.ucSmsFlg)
        {                                                                         /* SMS在等待响应                            */
            Gmm_SndSmsErrorInd(GMM_SMS_SIGN_NO_EXIST);                              /* 发送PMMSMS_ERROR_IND                     */
            g_GmmServiceCtrl.ucSmsFlg = GMM_FALSE;
        }
    }
    /* ==>A32D12436 */
    else if (NAS_MML_NET_RAT_TYPE_GSM == gstGmmSuspendCtrl.ucPreRat)
    {
        if (MMC_SUSPEND_CAUSE_CELLCHANGE_FALLBACK != gstGmmSuspendCtrl.ucSuspendCause)
        {
            g_GmmGlobalCtrl.ucSigConFlg = GMM_FALSE;
        }

        Gmm_TimerStop(GMM_TIMER_T3314);
        gstGmmSuspendCtrl.ulTimerRunMask &= ~(VOS_UINT32)(0x00000001 << GMM_TIMER_PROTECT_OLD_TLLI);

    }
    else
    {
    }
    /* <==A32D12436 */
    Gmm_TimerStop(GMM_TIMER_SUSPENDED);

#if   (FEATURE_ON == FEATURE_LTE)

    if ( NAS_MML_NET_RAT_TYPE_LTE == enCurrNetType )
    {
        /* Modified by s00246516 for L-C互操作项目, 2014-01-27, Begin */
        NAS_GMM_ProcResumeToLTE();
        /* Modified by s00246516 for L-C互操作项目, 2014-01-27, End */

        return ;
    }
#endif

    /* Added by s00246516 for L-C互操作项目, 2014-01-27, Begin */
#if (FEATURE_ON == FEATURE_CL_INTERWORK)
    /* 异系统变换到EHRPD下的处理 */
    if ( MMC_RESUME_ORIGEN_HRPD == pResumeIndMsg->ucResumeOrigen )
    {
        NAS_GMM_ProcResumeToHRPD(pResumeIndMsg);

        return;
    }
#endif
    /* Added by s00246516 for L-C互操作项目, 2014-01-27, End */

    switch (pResumeIndMsg->ucPsResumeResult)
    {
        case MMC_RESUME_RESULT_SUCCESS:
            if (gstGmmSuspendCtrl.ucPreRat == enCurrNetType)
            {
                GMM_LOG_INFO("GMM_RcvMmcResumeInd:Switch back,PS resume successfully.");
                /*回退成功处理函数*/
                GMM_ResumeTimer(GMM_TIMER_RESUME);
                Gmm_ComStaChg(gstGmmSuspendCtrl.ucPreState);
                GMM_ResumeSuccess();

                if ((GMM_TRUE == g_GmmGlobalCtrl.ucFollowOnFlg)
                 && (GMM_SERVICE_REQUEST_INITIATED != gstGmmSuspendCtrl.ucPreState))
                {
                    g_GmmGlobalCtrl.ucFollowOnFlg = GMM_FALSE;
                    NAS_MML_SetPsServiceBufferStatusFlg(VOS_FALSE);

                    Gmm_RoutingAreaUpdateHandleFollowOn();
                }
            }
            else if ((0x10 == (gstGmmSuspendCtrl.ucPreState & 0xF0))
                  || (GMM_REGISTERED_INITIATED == gstGmmSuspendCtrl.ucPreState))
            {
                GMM_LOG_INFO("GMM_RcvMmcResumeInd:PS not register.");
                /*回退成功处理函数*/
                GMM_ResumeTimer(GMM_TIMER_RESUME);
                Gmm_TimerStop( GMM_TIMER_T3310 );
                Gmm_ComStaChg(gstGmmSuspendCtrl.ucPreState);
                /*  在注册过程中,说明原来在去注册正常服务状态 */
                if (GMM_REGISTERED_INITIATED == gstGmmSuspendCtrl.ucPreState)
                {
                    Gmm_ComStaChg(GMM_DEREGISTERED_NORMAL_SERVICE);
                }

                GMM_ResumeFailure();

                /* resume成功时清除缓存 */
                NAS_GMM_ProcBufferSmMsg_ResumeSuccess();
            }
            /*  rau init状态cco回退没有恢复t3330，需要重新启动，状态不变还是GMM_ROUTING_AREA_UPDATING_INITIATED，
                t3330超时重新发起rau或网络释放连接，停t3330，启动t3311，t3311超时再进行rau */
            else if ((GMM_ROUTING_AREA_UPDATING_INITIATED == g_GmmGlobalCtrl.ucState)
                  && (MMC_SUSPEND_CAUSE_CELLCHANGE_FALLBACK == gstGmmSuspendCtrl.ucSuspendCause))
            {
                Gmm_TimerStart(GMM_TIMER_T3330);
            }
            else if ((MMC_SUSPEND_CAUSE_HANDOVER == gstGmmSuspendCtrl.ucSuspendCause)
                  && (NAS_MML_NET_RAT_TYPE_LTE == gstGmmSuspendCtrl.ucPreRat)
                  && (NAS_MML_NET_RAT_TYPE_WCDMA == enCurrNetType))
            {
                Gmm_ComStaChg(GMM_REGISTERED_NORMAL_SERVICE);

                Gmm_TimerStop(GMM_TIMER_T3312);

                NAS_MML_SetEpsSigConnStatusFlg(VOS_FALSE);

                NAS_MML_SetEpsServiceConnStatusFlg(VOS_FALSE);

                /* PS信令连接的更新依赖于MMC转发的resume ind指示 */
            }
            else
            {
                GMM_LOG_INFO("GMM_RcvMmcResumeInd:Intersystem change,PS resume successfully.");
                if ( MMC_SUSPEND_CAUSE_HANDOVER != gstGmmSuspendCtrl.ucSuspendCause )
                {
                    Gmm_TimerStart(GMM_TIMER_SUSPENDED);
                }
                Gmm_ComStaChg(GMM_SUSPENDED_WAIT_FOR_SYSINFO);
            }

            if ( gstGmmSuspendCtrl.ucPreRat != enCurrNetType )
            {
                if ( NAS_MML_NET_RAT_TYPE_WCDMA == enCurrNetType)
                {
                    /* 异重选,cco,cco回退恢复时需要用此全局变量记录，便于后续建链的原因值填写 */
                    if ((MMC_SUSPEND_CAUSE_CELLRESELECT == gstGmmSuspendCtrl.ucSuspendCause)
                        ||(MMC_SUSPEND_CAUSE_REDIRECTION == gstGmmSuspendCtrl.ucSuspendCause)
                        ||(MMC_SUSPEND_CAUSE_CELLCHANGE == gstGmmSuspendCtrl.ucSuspendCause))
                    {
                        g_GmmInterRatCellReselect = 1;
                    }
                }
            }

            break;
        case MMC_RESUME_RESULT_FAILURE:
            GMM_LOG_INFO("GMM_RcvMmcResumeInd:PS resume failure.");
            GMM_ResumeTimer(GMM_TIMER_RESUME);
            Gmm_ComStaChg(gstGmmSuspendCtrl.ucPreState);
            GMM_ResumeFailure();
            break;
        case MMC_RESUME_GPRS_SUSPENSION:
            if (NAS_MML_NET_RAT_TYPE_GSM != enCurrNetType)
            {
                GMM_LOG_WARN("GMM_RcvMmcResumeInd:PS resume result of MMCGMM_RESUME_IND is abnormal.");
                GMM_ResumeTimer(GMM_TIMER_RESUME);
                Gmm_ComStaChg(gstGmmSuspendCtrl.ucPreState);
                GMM_ResumeFailure();
                return;
            }
            GMM_LOG_INFO("GMM_RcvMmcResumeInd:PS resume result is GPRS_SUSPENSION.");
            if (gstGmmSuspendCtrl.ucPreRat == enCurrNetType)
            {
                GMM_BufferMsgDump();
                Gmm_HoldBufferFree();                                           /* 清除保留消息                             */
                Gmm_ComCnfHandle();
                Gmm_ComStaChg(GMM_GPRS_SUSPENSION);
                if (GMM_REGISTERED_NORMAL_SERVICE == gstGmmSuspendCtrl.ucPreState)
                {
                    g_GmmGlobalCtrl.ucSuspendProc                = GMM_TRUE;
                }
            }
            else
            {
                Gmm_ComStaChg(GMM_SUSPENDED_GPRS_SUSPENSION);
            }
            break;
        default:
            GMM_LOG_WARN("GMM_RcvMmcResumeInd:Receive MMCGMM_RESUME_IND in abnormal State.");
            break;
    }
}

/*****************************************************************************
 Prototype      : GMM_ResumeSuccess
 Description    : 收到MMC恢复指示的处理
                  HSS 4100 V200R001 新增
 Input          :
 Output         :
 Return Value   :
 Calls          :
 Called By      :

 History        :
  1.Date        : 2005-08-25
    Author      : Roger Leo
    Modification: Created function
*****************************************************************************/
VOS_VOID GMM_ResumeSuccess()
{
    GMM_BufferMsgResume();

    if (GMM_T3312_TIMEOUT == gstGmmSuspendCtrl.ucT3312State)
    {
        Gmm_RoutingAreaUpdateInitiate(GMM_PERIODC_UPDATING);
        gstGmmSuspendCtrl.ucT3312State = GMM_T3312_NOT_TIMEOUT;
    }

}

/*****************************************************************************
 Prototype      : GMM_ResumeFailure
 Description    : 收到MMC恢复指示的处理
                  HSS 4100 V200R001 新增
 Input          :
 Output         :
 Return Value   :
 Calls          :
 Called By      :

 History        :
  1.Date        : 2005-08-25
    Author      : Roger Leo
    Modification: Created function
  2.日    期   : 2007年09月21日
    作    者   : luojian id:107747
    修改内容   : 根据问题单号：AT2D01670
  2.日    期   : 2011年1月3日
    作    者   : z00161729
    修改内容  : DTS2011011100386：CS ONLY模式W重选到G过程pdp激活失败，
                因为GMM收到RESUME_IND后状态迁到DEREGISTERED_LIMIT_SERVICE,
                该状态收到SM建链请求直接回复失败.
*****************************************************************************/
VOS_VOID GMM_ResumeFailure()
{
    RRMM_REL_IND_STRU      stRrRelIndMsg;

    if (MMC_SUSPEND_CAUSE_CELLRESELECT == gstGmmSuspendCtrl.ucSuspendCause)
    {
        if (GMM_REGISTERED_INITIATED == g_GmmGlobalCtrl.ucState)
        {
            Gmm_ComStaChg(GMM_DEREGISTERED_ATTEMPTING_TO_ATTACH);
        }
    }
    else if (GMM_TRUE == g_GmmGlobalCtrl.ucSigConFlg)
    {
        stRrRelIndMsg.ulCnDomainId    = RRC_NAS_PS_DOMAIN;
        stRrRelIndMsg.ulRelCause      = RRC_REL_CAUSE_RR_NORM_EVENT;
        stRrRelIndMsg.ulRrcConnStatus = RRC_RRC_CONN_STATUS_ABSENT;
        Gmm_RcvRrmmRelInd(&stRrRelIndMsg);
    }
    else
    {
    }

    if (GMM_T3312_TIMEOUT == gstGmmSuspendCtrl.ucT3312State)
    {
        gstGmmSuspendCtrl.ucT3312State = GMM_T3312_NOT_TIMEOUT;
    }

    GMM_BufferMsgDump();
    Gmm_HoldBufferFree();                                                       /* 清除保留消息                             */
    Gmm_ComCnfHandle();
}

/*****************************************************************************
 函 数 名  : NAS_GMM_ProcBufferSmMsg_ResumeSuccess
 功能描述  : resume成功时处理缓存的SM的消息
 输入参数  : 无
 输出参数  : 无
 返 回 值  : VOS_VOID
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2013年2月6日
    作    者   : w00176964
    修改内容   : 新生成函数
*****************************************************************************/
VOS_VOID NAS_GMM_ProcBufferSmMsg_ResumeSuccess()
{
    VOS_VOID                           *pstBuffMsg      = VOS_NULL_PTR;
    MSG_CB                             *pstTmpBuffMsg   = VOS_NULL_PTR;
    VOS_UINT32                          ulIndex;

    /* 取得当前队列头端的索引 */
    ulIndex = GMM_BufferMsgQueueOut();

    if (GMM_CAS_MSG_NUMBER_MAX == ulIndex)
    {
        return;
    }

    /* 取得消息内容指针 */
    pstTmpBuffMsg = (MSG_CB *)gstGmmCasMsgBuf.apBufMsg[ulIndex];

    /* 因为在挂起过程中,可能收到PDP激活请求,或者在业务触发的ATTACH流程中,
       发起了系统间重选,如果此时清除缓存的SM消息,会导致PDP激活失败,
       所以此时不能清除SM消息 */
    if ((WUEPS_PID_SM == pstTmpBuffMsg->ulSenderPid)
     && (GMM_CAS_MSG_NUMBER_MAX != ulIndex))
    {
        pstBuffMsg = (MSG_CB *)PS_MEM_ALLOC(WUEPS_PID_GMM, (pstTmpBuffMsg->ulLength + VOS_MSG_HEAD_LENGTH));

        if (VOS_NULL_PTR == pstBuffMsg)
        {
            GMM_LOG_ERR("NAS_GMM_ProcBufferSmMsg_ResumeSuccess():Error: Invalid results of VOS_AllocMsg()");
            return;
        }

        Gmm_MemCpy(pstBuffMsg, pstTmpBuffMsg, (pstTmpBuffMsg->ulLength + VOS_MSG_HEAD_LENGTH));                 /* 消息内容复制 */
    }

    if (VOS_NULL_PTR != pstBuffMsg)
    {
        GMM_BufferMsgReceive((struct MsgCB *)(pstBuffMsg));

        Gmm_MemFree(pstBuffMsg);
    }
}

/* Added by s00246516 for L-C互操作项目, 2014-01-27, Begin */
#if (FEATURE_ON == FEATURE_LTE)
/*****************************************************************************
 函 数 名  : NAS_GMM_ProcResumeToLTE
 功能描述  : 处理异系统到LTE后收到resume ind消息的处理
 输入参数  : 无
 输出参数  : 无
 返 回 值  : 无
 调用函数  :
 被调函数  :
 修改历史      :
 1.日    期   : 2014年1月27日
   作    者   : s00246516
   修改内容   : 新生成函数
 2.日    期   : 2015年1月5日
   作    者   : z00161729
   修改内容   : AT&T 支持DAM特性修改

*****************************************************************************/
VOS_VOID NAS_GMM_ProcResumeToLTE(VOS_VOID)
{
    RRMM_REL_IND_STRU                    stRrMmRelIndMsg;

    VOS_UINT8                           aucTimerId[3];

    /* Added by w00176964 for VoLTE_PhaseII 项目, 2013-9-24, begin */
    /* ps的安全上下文失败回退 */
    if (MMC_SUSPEND_CAUSE_HANDOVER == gstGmmSuspendCtrl.ucSuspendCause)
    {
        NAS_MML_SetSimPsSecurity(&(g_GmmGlobalCtrl.stBackupShare.stSimPsSecurity));
    }
    /* Added by w00176964 for VoLTE_PhaseII 项目, 2013-9-24, end */

    if (GMM_TRUE == gstGmmCasGlobalCtrl.ucTlliAssignFlg)
    {
        NAS_GMM_SuspendLlcForInterSys();

        gstGmmCasGlobalCtrl.GmmSrvState = GMM_AGB_GPRS_STANDBY;

        Gmm_TimerStop(GMM_TIMER_T3314);
    }

    if (VOS_FALSE == NAS_MML_IsPlmnSupportDam(NAS_MML_GetCurrCampPlmnId()))
    {
        GMM_ResumeTimer(GMM_TIMER_NOT_RESUME);
    }
    else
    {
        GMM_ResumeTimer(GMM_TIMER_RESUME);
    }


    if ((0x10 == (gstGmmSuspendCtrl.ucPreState & 0xF0))
     || (GMM_REGISTERED_INITIATED == gstGmmSuspendCtrl.ucPreState))
    {
        Gmm_ComStaChg(GMM_DEREGISTERED_NO_CELL_AVAILABLE);
    }
    else
    {
        Gmm_ComStaChg(GMM_REGISTERED_NO_CELL_AVAILABLE);
    }

    gstGmmSuspendCtrl.ucPreState = GMM_SUSPENDED_NORMAL_SERVICE;

    if (GMM_TRUE == g_GmmGlobalCtrl.ucSigConFlg)
    {
        stRrMmRelIndMsg.ulCnDomainId    = RRC_NAS_PS_DOMAIN;
        stRrMmRelIndMsg.ulRelCause      = RRC_REL_CAUSE_RR_NORM_EVENT;
        stRrMmRelIndMsg.ulRrcConnStatus = RRC_RRC_CONN_STATUS_ABSENT;
        Gmm_RcvRrmmRelInd(&stRrMmRelIndMsg);
    }

    GMM_BufferMsgDump();

    Gmm_HoldBufferFree();                                                       /* 清除保留消息                             */

    Gmm_ComCnfHandle();

    if (VOS_FALSE == NAS_MML_IsPlmnSupportDam(NAS_MML_GetCurrCampPlmnId()))
    {
        Gmm_TimerStop(GMM_TIMER_ALL_EXCEPT_T3312_T3323);
        return;
    }

    aucTimerId[0] = GMM_TIMER_T3312;
    aucTimerId[1] = GMM_TIMER_T3323;
    aucTimerId[2] = GMM_TIMER_T3302;
    NAS_GMM_TimerStopExceptSpecialTimers(3, aucTimerId);


    return;
}
#endif


#if (FEATURE_ON == FEATURE_CL_INTERWORK)
/*****************************************************************************
 函 数 名  : NAS_GMM_ProcResumeToHRPD
 功能描述  : 处理异系统到HRPD后收到resume ind消息的处理
 输入参数  : pstResumeMsg----MMC的resume ind消息
 输出参数  : 无
 返 回 值  : 无
 调用函数  :
 被调函数  :
 修改历史      :
 1.日    期   : 2014年1月27日
   作    者   : s00246516
   修改内容   : 新生成函数
*****************************************************************************/
VOS_VOID NAS_GMM_ProcResumeToHRPD(
    MMCGMM_RESUME_IND_ST               *pstResumeMsg
)
{
    /* 不恢复定时器 */
    GMM_ResumeTimer(GMM_TIMER_NOT_RESUME);

    /* 状态迁移到无服务状态 */
    if ((0x10 == (gstGmmSuspendCtrl.ucPreState & 0xF0))
     || (GMM_REGISTERED_INITIATED == gstGmmSuspendCtrl.ucPreState))
    {
        Gmm_ComStaChg(GMM_DEREGISTERED_NO_CELL_AVAILABLE);
    }
    else
    {
        Gmm_ComStaChg(GMM_REGISTERED_NO_CELL_AVAILABLE);
    }

    /* 清除所有缓存的操作 */
    GMM_BufferMsgDump();

    Gmm_HoldBufferFree();                                                       /* 清除保留消息                             */

    Gmm_ComCnfHandle();

    /* 停止所有定时器 */
    Gmm_TimerStop(GMM_TIMER_ALL);

    return;
}
#endif
/* Added by s00246516 for L-C互操作项目, 2014-01-27, End */

/*lint -restore */

/*****************************************************************************
 函 数 名  : NAS_GMM_ProcRabmSysSrvChgInd_ResumeInd
 功能描述  : 收到resume ind消息后恢复RABM的处理
 输入参数  : 无
 输出参数  : 无
 返 回 值  : 无
 调用函数  :
 被调函数  :
 修改历史      :
 1.日    期   : 2014年12月13日
   作    者   : s00217060
   修改内容   : 新生成函数
*****************************************************************************/
VOS_VOID NAS_GMM_ProcRabmSysSrvChgInd_ResumeInd(VOS_VOID)
{
    NAS_MML_NET_RAT_TYPE_ENUM_UINT8      enCurrNetType;

    enCurrNetType   = NAS_MML_GetCurrNetRatType();

    /* 如果在W下指示RABM当前系统模式, 根据PsResumeResult挂起或恢复RABM, bRatChangeFlg为TRUE,
       如果在G下等到收到系统消息后恢复RABM */
    if (NAS_MML_NET_RAT_TYPE_WCDMA == enCurrNetType)
    {
        /* L到W的HO成功, 需通知 RABM 等待等待W接入层RAB的恢复; */
        /* CCO回退过程中, 接入层会上报RAB SETUP和SUCCESS, 也需通知 RABM 等待等待W接入层RAB的恢复; */
        if ( MMC_SUSPEND_CAUSE_CELLCHANGE_FALLBACK == gstGmmSuspendCtrl.ucSuspendCause
#if   (FEATURE_ON == FEATURE_LTE)
          || ( (MMC_SUSPEND_CAUSE_HANDOVER == gstGmmSuspendCtrl.ucSuspendCause)
             &&(NAS_MML_NET_RAT_TYPE_LTE   == gstGmmSuspendCtrl.ucPreRat) )
#endif
        )
        {
            NAS_GMM_SndRabmSysSrvChgInd(NAS_MML_NET_RAT_TYPE_WCDMA,
                                        VOS_TRUE,
                                        VOS_FALSE,
                                        VOS_FALSE);
        }
        else
        {
            NAS_GMM_SndRabmSysSrvChgInd(NAS_MML_NET_RAT_TYPE_WCDMA,
                                        VOS_TRUE,
                                        VOS_FALSE,
                                        VOS_TRUE);
        }
    }
    else
    {
        NAS_GMM_SndRabmSysSrvChgInd(enCurrNetType,
                                    VOS_TRUE,
                                    VOS_TRUE,
                                    VOS_TRUE);
    }

    return;
}

/*****************************************************************************
 函 数 名  : NAS_GMM_ProcPsSigConn_ResumeInd
 功能描述  : 收到resume ind消息后PS信令链接的处理
 输入参数  : pstResumeMsg----MMC的resume ind消息
 输出参数  : 无
 返 回 值  : 无
 调用函数  :
 被调函数  :
 修改历史      :
 1.日    期   : 2014年12月13日
   作    者   : s00217060
   修改内容   : 新生成函数
*****************************************************************************/
VOS_VOID NAS_GMM_ProcPsSigConn_ResumeInd(
    MMCGMM_RESUME_IND_ST               *pstResumeMsg
)
{
    /* 非HO,接入技术发生改变 删除PS信令链接 */
    if ((gstGmmSuspendCtrl.ucPreRat != NAS_MML_GetCurrNetRatType())
     && (MMC_SUSPEND_CAUSE_HANDOVER != gstGmmSuspendCtrl.ucSuspendCause))
    {
        if (VOS_TRUE == NAS_MML_GetConnStatus()->ucPsSigConnStatusFlg)
        {
            Gmm_SndMmcSignalingStatusInd(MMC_GMM_SIGNALING_STATUS_ABSENT);
        }

        NAS_MML_SetPsSigConnStatusFlg(VOS_FALSE);

        g_GmmGlobalCtrl.ucSigConFlg = VOS_FALSE;
    }

    if ((VOS_TRUE                   == pstResumeMsg->ucPsSigExistFlg)
     && (MMC_SUSPEND_CAUSE_HANDOVER == gstGmmSuspendCtrl.ucSuspendCause))
    {
        /* HO过来时，PS连接已经建好，此处信令连接存在 */
        Gmm_SndMmcSignalingStatusInd(MMC_GMM_SIGNALING_STATUS_PRESENT);

        NAS_MML_SetPsSigConnStatusFlg(VOS_TRUE);

        g_GmmGlobalCtrl.ucSigConFlg = GMM_TRUE;
    }

    return;
}

/*****************************************************************************
 函 数 名  : NAS_GMM_ProcResumeToGU
 功能描述  : 收到resume ind消息到GU的处理
 输入参数  : pstResumeMsg----MMC的resume ind消息
 输出参数  : 无
 返 回 值  : 无
 调用函数  :
 被调函数  :
 修改历史      :
 1.日    期   : 2014年12月13日
   作    者   : s00217060
   修改内容   : 新生成函数
*****************************************************************************/
VOS_VOID NAS_GMM_ProcResumeToGU(
    MMCGMM_RESUME_IND_ST               *pstResumeMsg
)
{
    NAS_MML_NET_RAT_TYPE_ENUM_UINT8     enCurrNetType;
    RRMM_REL_IND_STRU                   stRrMmRelIndMsg;

#if (FEATURE_ON == FEATURE_LTE)
    VOS_UINT32                          ulIsNeedDeactiveIsrFlg;
    NAS_MML_RPLMN_CFG_INFO_STRU        *pstRplmnCfgInfo;

    pstRplmnCfgInfo = NAS_MML_GetRplmnCfg();
#endif

    enCurrNetType = NAS_MML_GetCurrNetRatType();

    /* 因为在进行TC测试发生系统间切换时，媒体无法进行声码器切换，
       在发生系统间切换时，并且切换成功时，需要通知TC切换事件，以便TC可以通知媒体.
       L to G时 不需要发此消息 */
    if ( (GMM_TC_ACTIVE == gstGmmSuspendCtrl.ucPreState)
      && (gstGmmSuspendCtrl.ucPreRat != NAS_MML_NET_RAT_TYPE_LTE) )
    {
        NAS_GMM_SndTcHandoverInd();
    }

#if (FEATURE_ON == FEATURE_LTE)
    ulIsNeedDeactiveIsrFlg = NAS_GMM_IsNeedDeactiveIsr_InterSys(gstGmmSuspendCtrl.ucPreRat, enCurrNetType, gstGmmSuspendCtrl.ucSuspendCause);

    if (VOS_TRUE == ulIsNeedDeactiveIsrFlg)
    {
        NAS_GMM_WriteTinInfoNvim(NAS_MML_TIN_TYPE_GUTI, pstRplmnCfgInfo->aucLastImsi);
        Gmm_TimerStop(GMM_TIMER_T3323);

        /* ISR去激活，需要更新pdp激活是在ISR激活前激活的 */
        NAS_MML_UpdateAllPsBearIsrFlg(NAS_MML_PS_BEARER_EXIST_BEFORE_ISR_ACT);
    }
#endif

    /* 发生W到G异系统切换 */
    if (NAS_MML_NET_RAT_TYPE_GSM == enCurrNetType)
    {
        g_MmSubLyrShare.GmmShare.ucPsIntegrityProtect = NAS_MML_RRC_INTEGRITY_PROTECT_DEACTIVE;
        if ((0x10 != (gstGmmSuspendCtrl.ucPreState & 0xF0))
         && (GMM_REGISTERED_INITIATED != gstGmmSuspendCtrl.ucPreState))
        {
#if (FEATURE_LTE == FEATURE_ON)
            if (GMM_TIMER_T3312_FLG != (GMM_TIMER_T3312_FLG & g_GmmTimerMng.ulTimerRunMask))
            {
                NAS_GMM_SndLmmTimerInfoNotify(GMM_TIMER_T3312, GMM_LMM_TIMER_START);
            }
#endif

            Gmm_TimerStart(GMM_TIMER_T3312);
        }
    }

    Gmm_SndRrmmNasInfoChangeReq(RRC_NAS_MASK_PTMSI_RAI);

    if ((NAS_MML_NET_RAT_TYPE_WCDMA == enCurrNetType)
     && (GMM_TRUE == gstGmmCasGlobalCtrl.ucTlliAssignFlg))
    {
        NAS_GMM_SuspendLlcForInterSys();

        if (MMC_SUSPEND_CAUSE_CELLCHANGE != gstGmmSuspendCtrl.ucSuspendCause)
        {
            gstGmmCasGlobalCtrl.GmmSrvState = GMM_AGB_GPRS_STANDBY;

            Gmm_TimerStop(GMM_TIMER_T3314);
        }

        if ((0x10 != (gstGmmSuspendCtrl.ucPreState & 0xF0))
         && (GMM_REGISTERED_INITIATED != gstGmmSuspendCtrl.ucPreState))
        {
#if (FEATURE_LTE == FEATURE_ON)
            if (GMM_TIMER_T3312_FLG != (GMM_TIMER_T3312_FLG & g_GmmTimerMng.ulTimerRunMask))
            {
                NAS_GMM_SndLmmTimerInfoNotify(GMM_TIMER_T3312, GMM_LMM_TIMER_START);
            }
#endif
            Gmm_TimerStart(GMM_TIMER_T3312);
        }
    }

    /* 发生异系统切换从W到G，如果存在建链请求则清除 */
    if ((NAS_MML_NET_RAT_TYPE_WCDMA == gstGmmSuspendCtrl.ucPreRat)
     && ((GMM_RRC_RRMM_EST_CNF_FLG == (g_GmmReqCnfMng.ucCnfMask & GMM_RRC_RRMM_EST_CNF_FLG))
       || (GMM_SERVICE_REQUEST_INITIATED == gstGmmSuspendCtrl.ucPreState)))
    {
        Gmm_TimerStop(GMM_TIMER_PROTECT_FOR_SIGNALING);

        g_GmmReqCnfMng.ucCnfMask &= ~GMM_RRC_RRMM_EST_CNF_FLG;

        Gmm_ComStaChg(gstGmmSuspendCtrl.ucPreState);
        stRrMmRelIndMsg.ulCnDomainId              = RRC_NAS_PS_DOMAIN;
        stRrMmRelIndMsg.ulRelCause                = RRC_REL_CAUSE_RR_NORM_EVENT;
        stRrMmRelIndMsg.ulRrcConnStatus           = RRC_RRC_CONN_STATUS_ABSENT;
        Gmm_RcvRrmmRelInd(&stRrMmRelIndMsg);

        gstGmmSuspendCtrl.ucPreState = g_GmmGlobalCtrl.ucState;
    }

    return;
}

/*****************************************************************************
 函 数 名  : NAS_GMM_RcvMmcResumeInd_CcoFallbak
 功能描述  : CCO回退流程的处理
 输入参数  : 无
 输出参数  : 无
 返 回 值  : 无
 调用函数  :
 被调函数  :
 修改历史      :
 1.日    期   : 2014年12月13日
   作    者   : s00217060
   修改内容   : 新生成函数
*****************************************************************************/
VOS_VOID NAS_GMM_RcvMmcResumeInd_CcoFallbak(VOS_VOID)
{

    /* 不是CCO回退流程不在该函数中处理 */
    if (MMC_SUSPEND_CAUSE_CELLCHANGE_FALLBACK != gstGmmSuspendCtrl.ucSuspendCause )
    {
        return;
    }

    NAS_GMM_ResumeCcoFallbackCtx();

    /* 在CCO过程中T3314可能超时,所以需要根据T3314的运行状态调整服务状态 */
    if ((VOS_FALSE == NAS_GMM_QryTimerStatus(GMM_TIMER_T3314))
     && (0xffffffff != gstGmmCasGlobalCtrl.ulReadyTimerValue)
     && (GMM_AGB_GPRS_READY == gstGmmCasGlobalCtrl.GmmSrvState))
    {
        gstGmmCasGlobalCtrl.GmmSrvState = GMM_AGB_GPRS_STANDBY;
    }

    if (GMM_REGISTERED_NORMAL_SERVICE == g_GmmGlobalCtrl.stBackupShare.ucState)
    {
        gstGmmSuspendCtrl.ucPreState = GMM_REGISTERED_NORMAL_SERVICE;
    }

    return;
}

/*****************************************************************************
 函 数 名  : NAS_GMM_RcvMmcResumeInd_Handover
 功能描述  : 切换流程的处理
 输入参数  : 无
 输出参数  : 无
 返 回 值  : 无
 调用函数  :
 被调函数  :
 修改历史      :
 1.日    期   : 2014年12月13日
   作    者   : s00217060
   修改内容   : 新生成函数
*****************************************************************************/
VOS_VOID NAS_GMM_RcvMmcResumeInd_Handover(
    MMCGMM_RESUME_IND_ST               *pstResumeIndMsg
)
{
    NAS_MML_NET_RAT_TYPE_ENUM_UINT8     enCurrNetType;

    enCurrNetType   = NAS_MML_GetCurrNetRatType();

    /* 不是HO流程不在该函数中处理 */
    if (MMC_SUSPEND_CAUSE_HANDOVER != gstGmmSuspendCtrl.ucSuspendCause )
    {
        return;
    }

    /* L到GU的HO或GU之间的HO流程，启定时器，时长可NV配置 */
    /* GU到L的HO,和李洪确认，如果有系统消息会先做TAU；如果没有系统消息会等链路释放重新驻留再做TAU，TAU之后上报TAU结果和服务状态 */
    if ( (enCurrNetType != gstGmmSuspendCtrl.ucPreRat)
#if (FEATURE_ON == FEATURE_LTE)
      && (enCurrNetType != NAS_MML_NET_RAT_TYPE_LTE)
#endif
      )
    {
        /* 先停再启 */
        Gmm_TimerStop(GMM_TIMER_HO_WAIT_SYSINFO);

        Gmm_TimerStart(GMM_TIMER_HO_WAIT_SYSINFO);
    }

    /* L->GU,CS handover重新获取重定向的安全上下文 */
    if ((VOS_FALSE                   == pstResumeIndMsg->ucPsSigExistFlg)
     && (NAS_MML_NET_RAT_TYPE_LTE    != enCurrNetType)
     && (NAS_MML_NET_RAT_TYPE_LTE    == gstGmmSuspendCtrl.ucPreRat))
    {
        gstGmmSuspendCtrl.ucGetLteSecContext = VOS_FALSE;
    }

    return;
}

#ifdef  __cplusplus
  #if  __cplusplus
  }
  #endif
#endif
