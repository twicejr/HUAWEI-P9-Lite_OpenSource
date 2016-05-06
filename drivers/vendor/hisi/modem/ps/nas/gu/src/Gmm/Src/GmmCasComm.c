/************************************************************************
  Copyright    : 2005-2007, Huawei Tech. Co., Ltd.
  File name    : GmmCasComm.c
  Author       : Roger Leo
  Version      : V200R001
  Date         : 2005-08-25
  Description  : 该C文件给出了Gmm Cas模块中通用处理过程的实现
  Function List:
        ---
        ---
        ---
  History      :
  1. Date:2005-08-25
     Author: Roger Leo
     Modification:update
  2. s46746 2006-03-08 根据问题单A32D02368修改
  3. s46746 2006-03-18 根据问题单A32D02141修改
  4. l40632 2006-04-11 根据问题单A32D03039修改
  5. l40632 2006-04-17 根据问题单A32D03141修改
  6. l40632 2006-04-25 根据问题单A32D03000修改
  7. x51137 2006/4/28 A32D02889
  8. l40632 2006.05.20 根据问题单A32D03865修改
  9. l40632 2006.05.30 根据问题单A32D03830
  10.l40632 2006.06.29 根据问题单A32D04514
  11.日    期   : 2006年10月9日
     作    者   : s46746
     修改内容   : 根据问题单号：A32D05744
  12.日    期   : 2007年01月13日
     作    者   : s46746
     修改内容   : 根据问题单号：A32D08326
  13.日    期   : 2007年03月21日
     作    者   : luojian 60022475
     修改内容   : Maps3000接口修改
  14.日    期   : 2007年07月12日
     作    者   : hanlufeng 41410
     修改内容   : A32D12338
  15.日    期   : 2007年08月19日
     作    者   : l60022475
     修改内容   : 根据问题单号：A32D12706
  16.日    期   : 2007年09月10日
     作    者   : s46746
     修改内容   : 根据问题单号：A32D12829
  17.日    期   : 2007-10-26
     作    者   : hanlufeng
     修改内容   : A32D13172
  18.日    期   : 2007年11月22日
     作    者   : s46746
     修改内容   : 根据问题单号：A32D13475,修改异系统改变后指派的old TLLI和开机加密密钥为全0问题
  19.日    期   : 2007-10-26
     作    者   : l00107747
     修改内容   : A32D13862
  20.日    期   : 2007年12月14日
     作    者   : s46746
     修改内容   : 问题单A32D13638，保证进行RAU之前不向网侧发送其它数据，并且RAU不成功，不恢复层2
  21.日    期   : 2007年12月21日
     作    者   : l00107747
     修改内容   : 问题单A32D13950,W支持CS&PS,G下不支持PS，切换到W模式后GMM没有发起联合RAU
  22.日    期   : 2007年12月28日
     作    者   : s46746
     修改内容   : 根据问题单号：A32D13954,修改GMM在2G3过程中缓存消息机制
  23.日    期   : 2008年5月2日
     作    者   : s46746
     修改内容   : 根据问题单号：AT2D03268,没有判断小区是否改变标志，直接进行了RAU或Attach
  24.日    期   : 2008年8月22日
     作    者   : s46746
     修改内容   : 根据问题单号：AT2D05192,cell update判断时，判断依据RAI是否改变没有赋值正确
  25.日    期   : 2008年9月23日
     作    者   : o00132663
     修改内容   : 根据问题单号：AT2D05839,清除无用全局变量 ucRlsMsgFlg和状态GMM_REGISTERED_WAIT_FOR_RAU
  26.日    期   : 2008年12月18日
     作    者   : x00115505
     修改内容   : 根据问题单号：AT2D07624,修改可维可测消息中TimerStamp
                  字段的读取方式。
  27.日    期   : 2009年04月01日
     作    者   : x00115505
     修改内容   : 问题单号:AT2D10473,Rau过程中出服务区，回到服务区之后没有发起Rau。
  28.日    期   : 2009年05月14日
     作    者   : h44270
     修改内容   : 问题单号:AT2D11898/AT2D11828,在IDLE态下发送PS域短信，没有按照ATTACH ACCEPT消息中Radio Priority for SMS来请求资源
  29.日    期   : 2009年6月30日
     作    者   : s46746
     修改内容   : AT2D12561,3G2情形GPRS下未启动加密，NAS指派层2加密算法后，层2对上行数据进行了加密
  30.日    期   : 2009年7月23日
     作    者   : s46746
     修改内容   : 根据问题单号：AT2D12878，GSM下HPLMN搜索时接收到GPRS寻呼或PDP激活(W下PDP激活相同处理)请求需要能及时响应
  31.日    期   : 2011-11-11
     作    者   : h44270
     修改内容   : 根问题单号：DTS2010110500099/DTS2010111103124,修正GMM在W模下向GAS发送去指派消息
  32.日    期   : 2011年12月29日
     作    者   : l00130025
     修改内容   : DTS2011082201679/DTS2011121504358,删除LTE的模式判断函数
************************************************************************/

/*****************************************************************************
   1 头文件包含
*****************************************************************************/

#include "GmmInc.h"
#include "GmmCasGlobal.h"
#include "GmmCasSuspend.h"
#include "GmmCasSend.h"
#include "GmmCasComm.h"
#include "GmmCasMain.h"
#include "GmmCasGsm.h"
#include "GmmMmInterface.h"
#if (FEATURE_ON == FEATURE_LTE)
#include "NasCommDef.h"
#include "NasGmmProcLResult.h"
#endif
#include "NasUsimmApi.h"


#ifdef  __cplusplus
  #if  __cplusplus
  extern "C"{
  #endif
#endif


/*****************************************************************************
    协议栈打印打点方式下的.C文件宏定义
*****************************************************************************/
/*lint -e767 修改人:luojian 107747;检视人:sunshaohua65952;原因:LOG方案设计需要*/
#define    THIS_FILE_ID        PS_FILE_ID_GMM_CASCOMM_C
/*lint +e767 修改人:luojian 107747;检视人:sunshaohua*/


/*****************************************************************************
   2 全局变量定义
*****************************************************************************/


/*lint -save -e958 */

/*****************************************************************************
   3 函数实现
*****************************************************************************/

/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~ */
/*---------------3.1 GMM CAS 通用过程处理   -------------*/
/*=======================================================*/

/*****************************************************************************
 Prototype      : GMM_IsCasGsmMode
 Description    : 判断当前接入模式是否GSM网络
                  HSS 4100 V200R001 新增
 Input          :
 Output         :
 Return Value   : GMM_TRUE       GSM网络接入
                  GMM_FALSE      非GSM网络接入
 Calls          :
 Called By      :

 History        :
  1.Date        : 2005-08-25
    Author      : Roger Leo
    Modification: Created function
*****************************************************************************/
VOS_UINT8 GMM_IsCasGsmMode (VOS_VOID)
{
    if (NAS_MML_NET_RAT_TYPE_GSM == NAS_MML_GetCurrNetRatType())
    {
        return GMM_TRUE;
    }
    else
    {
        return GMM_FALSE;
    }
}

/*****************************************************************************
 Prototype      : GMM_IsLastRand
 Description    : 判断新存的RAND和上次记录值是否相等
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
VOS_UINT8 GMM_IsLastRand(VOS_VOID)
{
    VOS_UINT8   i;
    VOS_UINT8   ucRel = GMM_TRUE;

    for (i=0; i<GMM_MAX_SIZE_RAND; i++)
    {
        if (g_GmmAuthenCtrl.aucRandSav[i]
           != g_GmmAuthenCtrl.aucRand[i])
        {
            ucRel = GMM_FALSE;
            break;
        }
    }

    return ucRel;
}

/*****************************************************************************
 Prototype      :
 Description    : 公共接入层模块使用全局结构变量初始化函数
                  HSS 4100 V200R001 新增
 Input          :
 Output         :
 Return Value   :
 Calls          :
 Called By      :

 History        :
  1.Date        : 2005-11-08
    Author      : Roger Leo
    Modification: Created function

  2. x51137 2006/4/28 A32D02889
  3.日    期   : 2009年05月14日
    作    者   : h44270
    修改内容   : 问题单号:AT2D11898/AT2D11828,在IDLE态下发送PS域短信，没有按照ATTACH ACCEPT消息中Radio Priority for SMS来请求资源
  4.日    期   : 2009年09月03日
    作    者   : l65478
    修改内容   : 问题单号：AT2D14239,detach完成后,再次发起ATTATCH REQ时,GAS使用旧的TLLI建立的TBF发送数据,没有及时使用新的TLLI,导致MS和仪器侧维护的TLLI不一致,从而导致GAS因为TLLI不匹配丢弃了建立下行TBF的指派命令,最终导致用例失败
  5.日    期   : 2010年12月18日
    作    者   : o00132663
    修改内容   : 问题单号:DTS2010121800152,GMM关机关不掉，状态挂死
*****************************************************************************/
VOS_VOID GMM_InitCasGlobalVariable (VOS_VOID)
{
    /* GMM CAS全局结构变量清零 */
    Gmm_MemSet(&gstGmmCasGlobalCtrl, 0, sizeof(GMM_CAS_CTRL_STRU));
    Gmm_MemSet(&gstGmmCasMsgBuf,     0, sizeof(GMM_CAS_MSG_BUFFER_STRU));
    Gmm_MemSet(&gstGmmSuspendCtrl,   0, sizeof(GMM_SUSPEND_CTRL_STRU));


    /* 设定初始值 */
    gstGmmCasGlobalCtrl.ucGmmCasState       = GMM_CAS_WCDMA_AS;
    gstGmmCasGlobalCtrl.ucGmmCasPreState    = GMM_CAS_WCDMA_AS;
    gstGmmCasGlobalCtrl.GmmSrvState         = GMM_IU_PMM_DETACHED;
    gstGmmCasGlobalCtrl.ucBufMsgResFlg      = GMM_FALSE;             /* 标记没有需要恢复的挂起消息 */
    gstGmmCasGlobalCtrl.ucReadyTimerNgtFlg  = GMM_FALSE;             /*标记可协商ready timer*/
    gstGmmCasGlobalCtrl.ucRauCmpFlg         = GMM_FALSE;             /*标记不能发送RAU CMP消息*/
    gstGmmCasGlobalCtrl.ucWaitRabmRauRspFlg = GMM_FALSE;
    gstGmmCasGlobalCtrl.ucRabmRauRspRcvdFlg = GMM_FALSE;
    gstGmmCasGlobalCtrl.ucWaitRabmRauRspFlg = GMM_FALSE;
    gstGmmCasGlobalCtrl.ucRabmRauRspRcvdFlg = GMM_FALSE;

    gstGmmCasGlobalCtrl.ucRabmResumeFlg     = GMM_TRUE;              /*标记RABM RAU更新已完成*/
    gstGmmCasGlobalCtrl.ulReadyTimerValue   = 44000;                 /* 44 s*/
    gstGmmCasGlobalCtrl.ucReadyTimerChgFlg  = VOS_FALSE;
    /* 初始化系统TLLI值 */
    gstGmmCasGlobalCtrl.ulTLLI              = 0xffffffff;            /* 无效TLLI值 */
    gstGmmCasGlobalCtrl.ulOldTLLI           = 0xffffffff;            /* 无效TLLI值 */
    gstGmmCasGlobalCtrl.ucflgTLLI           = GMM_INVALID_TLLI;      /* 置TLLI无效标志 */
    gstGmmCasGlobalCtrl.ucTlliAssignFlg     = GMM_FALSE;             /* 未完成TLLI指配 */
    gstGmmCasGlobalCtrl.enRaPrioLevFosSms   = GMM_RA_PRIO_LEV_1;

    g_GmmGlobalCtrl.ulGmmAttachFlg          = GMM_FALSE;

    gstGmmSuspendCtrl.ucSuspendCause        = MMC_SUSPEND_CAUSE_BUTT;

    NAS_GMM_SetLmmSecInfoFlg(VOS_FALSE);

    return;
}

/*****************************************************************************
 Prototype      : GMM_CasRcvUsimCnfUmtsSucc
 Description    : 收到USIM卡UMTS鉴权成功结果
                  HSS 4100 V200R001 新增
 Input          : USIMM_TELECOM_AUTH_CNF_STRU *pAuthCnf 参数结构指针
 Output         :
 Return Value   :
 Calls          :
 Called By      :

 History        :
  1.Date        : 2005-08-25
    Author      : Roger Leo
    Modification: Created function
  2.日    期    : 2009年03月18日
    作    者    : l65478
    修改内容    : 根据问题单号：AT2D08671,数传状态下，W出服务区后，切到G，数传恢复失败，因为GMM没有配置LL加密算法
  3.日    期   : 2009年03月31日
    作    者   : L65478
    修改内容   : 根据问题单号：AT2D10529两次鉴权失败后没有释放RRC连接
  4.日    期   : 2011年7月27日
    作    者   : h44270
    修改内容   : V7R1 PHASEII 重构: 数据结构，全局变量初始化，魔鬼数字的调整
  5.日    期   : 2013年07月23日
    作    者   : y00245242
    修改内容   : VOLTE开发，适配新的USIM接口
*****************************************************************************/
VOS_VOID GMM_CasRcvUsimCnfUmtsSucc(USIMM_TELECOM_AUTH_CNF_STRU *pAuthCnf)
{
    NAS_MSG_STRU *pNasMsg;                                  /* 定义指向NAS消息的指针*/

    NAS_MML_SetSimPsSecurityCksn(g_GmmAuthenCtrl.ucCksnSav);            /* 暂存消息中的CKSN赋给全局变量中的CKSN                         */

    /* Modified by y00245242 for VoLTE_PhaseI  项目, 2013-7-23, begin */
    /* 记录CK值到全局变量中, 跳过首个长度字节 */
    Gmm_MemCpy(NAS_MML_GetSimPsSecurityUmtsCk(),
            &(pAuthCnf->aucCK[1]), 16 );                          /* 更新全局变量中的Ck*/

    /* 记录IK值到全局变量中，跳过首个长度字节 */
    Gmm_MemCpy(NAS_MML_GetSimPsSecurityUmtsIk(),
            &(pAuthCnf->aucIK[1]), 16 );                          /* 更新全局变量中的Ik*/

    /* 计算保存GSM Kc */
    if (0 == pAuthCnf->aucGsmKc[0]) /* check Kc length */
    {
        NAS_MML_SecContext3GTO2G(NAS_MML_GetSimPsSecurityUmtsIk(),
                                 NAS_MML_GetSimPsSecurityUmtsCk(),
                                 NAS_MML_GetSimPsSecurityGsmKc());
    }
    else
    {
        /* skip the first length byte */
        Gmm_MemCpy(NAS_MML_GetSimPsSecurityGsmKc(),
                &(pAuthCnf->aucGsmKc[1]), 8 );                        /* 更新全局变量中的GSM Kc*/
    }
    /* Modified by y00245242 for VoLTE_PhaseI  项目, 2013-7-23, end */


    /* 保存CK,IK,Kc值到SIM中 */
    if (MMC_SIM_TYPE_USIM == NAS_MML_GetSimType())
    {/* 3G USIM */
        Gmm_SndAgentUsimUpdateFileReq(USIMM_USIM_EFKEYSPS_ID);    /* 更新SIM中的CKSN,Ck,IK*/
        Gmm_SndAgentUsimUpdateFileReq(USIMM_USIM_EFKCGPRS_ID);   /* 更新SIM中的GSM CKSN,Kc*/
    }
    else
    {/* 2G SIM */
        Gmm_SndAgentUsimUpdateFileReq(USIMM_GSM_EFKCGPRS_ID);   /* 更新SIM中的GSM CKSN,Kc*/
    }

    /* 记录RES */
    GMM_SaveAuthenResult(pAuthCnf);

    /* 通知MMC实体鉴权结果信息 */
    Gmm_SndRrmmNasInfoChangeReq(RRC_NAS_MASK_SECURITY_KEY); /* 发送RRMM_NAS_INFO_CHANGE_REQ*/

    /* 修改鉴权过程的标志量 */
    Gmm_Start_StopedRetransmissionTimer();                  /* 存在被停止的retransmission timer将其启动 */
    g_GmmAuthenCtrl.ucAuthenAttmptCnt = 0;                  /* GMM Authentication attempt counter清0    */
    g_GmmAuthenCtrl.ucLastFailCause = GMM_AUTHEN_REJ_CAUSE_INVALID;

    /* 填写鉴权回应消息 */
    pNasMsg = Gmm_AuthenAndCipherResponseMsgMake(
            GMM_AUTH_AND_CIPH_RES_NEEDED);                  /* 发送A&C RESPONSE*/

    /* 发送GMM消息 */
    Gmm_SndRrmmDataReq(RRC_NAS_MSG_PRIORTY_HIGH, pNasMsg);

    if (GMM_TRUE == GMM_IsCasGsmMode())
    {
        Gmm_ComGprsCipherHandle();
    }

    /* RAND值比较更新 */
    GMM_UpdateAuthenCtrlFlg();

    return;
}

/*****************************************************************************
 Prototype      : GMM_CasRcvUsimCnfGsmSucc
 Description    : 收到USIM卡GSM鉴权成功结果
                  HSS 4100 V200R001 新增
 Input          :
 Output         :
 Return Value   :
 Calls          :
 Called By      :

 History        :
 1.Date        : 2005-11-08
   Author      : Roger Leo
   Modification: Created function
 2.日    期   : 2011年7月25日
   作    者   : h44270
   修改内容   : V7R1 PHASEII 重构: 数据结构，全局变量初始化，魔鬼数字的调整
 3.日    期   : 2013年07月23日
   作    者   : y00245242
   修改内容   : 为开发VOLTE，适配新的USIM接口
*****************************************************************************/
VOS_VOID GMM_CasRcvUsimCnfGsmSucc(USIMM_TELECOM_AUTH_CNF_STRU *pAuthCnf)
{
    NAS_MSG_STRU *pNasMsg;                                  /* 定义指向NAS消息的指针*/

    NAS_MML_SetSimPsSecurityCksn(g_GmmAuthenCtrl.ucCksnSav);            /* 暂存消息中的CKSN赋给全局变量中的CKSN                                 */


    /* Modified by y00245242 for VoLTE_PhaseI  项目, 2013-7-23, begin */
    /* 记录Kc值到全局变量中, 跳过首个长度字节COPY */
    Gmm_MemCpy(NAS_MML_GetSimPsSecurityGsmKc(),
            &(pAuthCnf->aucGsmKc[1]), 8 );                        /* 更新全局变量中的GSM Kc*/
    /* Modified by y00245242 for VoLTE_PhaseI  项目, 2013-7-23, end */


    /* 计算IK,CK */
    NAS_MML_SecContext2GTO3G(NAS_MML_GetSimPsSecurityUmtsIk(),
                             NAS_MML_GetSimPsSecurityUmtsCk(),
                             NAS_MML_GetSimPsSecurityGsmKc());

    /*Gmm_MemCpy(g_GmmGlobalCtrl.PsSecutityInfo.aucCk,
            pAuthCnf->aucCK, 16 );*/                          /* 更新全局变量中的Ck*/

    /*Gmm_MemCpy(g_GmmGlobalCtrl.PsSecutityInfo.aucIk,
            pAuthCnf->aucIK, 16 );*/                          /* 更新全局变量中的Ik*/

    /* 保存Kc,IK,CK值到SIM中 */
    if (NAS_MML_SIM_TYPE_USIM == NAS_MML_GetSimType())
    {/* 3G USIM */
        Gmm_SndAgentUsimUpdateFileReq(USIMM_USIM_EFKEYSPS_ID);    /* 更新SIM中的CKSN,Ck,IK*/
        Gmm_SndAgentUsimUpdateFileReq(USIMM_USIM_EFKCGPRS_ID);   /* 更新SIM中的GSM CKSN,Kc*/
    }
    else
    {/* 2G SIM */
        Gmm_SndAgentUsimUpdateFileReq(USIMM_GSM_EFKCGPRS_ID);   /* 更新SIM中的GSM CKSN,Kc*/
    }

    /* 记录SRES */
    GMM_SaveAuthenResult(pAuthCnf);

    if (GMM_TRUE == GMM_IsCasGsmMode())
    {
        Gmm_ComGprsCipherHandle();
    }

    Gmm_SndRrmmNasInfoChangeReq(RRC_NAS_MASK_SECURITY_KEY); /* 发送RRMM_NAS_INFO_CHANGE_REQ*/

    /* 填写鉴权回应消息 */
    pNasMsg = Gmm_AuthenAndCipherResponseMsgMake(
            GMM_AUTH_AND_CIPH_RES_NEEDED);                  /* 发送A&C RESPONSE*/

    /* 发送GMM消息 */
    Gmm_SndRrmmDataReq(RRC_NAS_MSG_PRIORTY_HIGH, pNasMsg);

    /* RAND值比较更新 */
    GMM_UpdateAuthenCtrlFlg();

    return;
}

/*****************************************************************************
 Prototype      : GMM_CasRcvUsimCnfFailUmts
 Description    : UMTS鉴权:SYNC失败或者MAC失败
                  HSS 4100 V200R001 新增
 Input          :
 Output         :
 Return Value   :
 Calls          :
 Called By      :

 History        :
  1.Date        : 2005-11-08
    Author      : Roger Leo
    Modification: Created function
  2.  日    期   : 2006年12月5日
      作    者   : luojian 60022475
      修改内容   : Maps3000接口修改
  3.  日    期   : 2009年03月31日
      作    者   : L65478
      修改内容   : 根据问题单号：AT2D10529两次鉴权失败后没有释放RRC连接
  4.  日    期   : 2012年4月20日
      作    者   : l00130025
      修改内容   : DTS2012032004389，Netork连续3次被Ms Auth Rej或T3318/T3320超时时，没有通知GAS Bar掉当前小区
  5.  日    期   : 2012年8月25日
      作    者   : m00217266
      修改内容   : 删除GMM_SaveErrCode，添加Gmm_Save_Detach_Cause，
                  保存导致Attach失败的原因值
  6.  日    期   : 2013年07月23日
      作    者   : y00245242
      修改内容   : 为开发VOLTE，适配新的USIM接口
  7.  日    期  :2014年01月09日
      作    者  :l65478
      修改内容  :DTS2014010704608:第一次鉴权响应和网络发起的第二次鉴权请求冲突
*****************************************************************************/
VOS_VOID GMM_CasRcvUsimCnfFailUmts(
    USIMM_TELECOM_AUTH_CNF_STRU        *pAuthCnf,
    USIMM_AUTH_RESULT_ENUM_UINT32       enResult
)
{
    NAS_MSG_STRU    *pNasMsg;

    g_GmmAuthenCtrl.ucAuthenAttmptCnt++;                    /* GMM Authentication attempt counter＋1    */

    /* 判断鉴权尝试次数 */
    if (GMM_AUTHEN_ATTEMPT_MAX_CNT == g_GmmAuthenCtrl.ucAuthenAttmptCnt)
    {/* 超过最大次数 */

        if (USIMM_AUTH_MAC_FAILURE == enResult)
        {
            /*保存鉴权失败的错误码*/
            NAS_GMM_SetAttach2DetachErrCode(GMM_SM_CAUSE_MAC_FAILURE);
        }
        else
        {
            /*保存鉴权失败的错误码*/
            NAS_GMM_SetAttach2DetachErrCode(GMM_SM_CAUSE_SYNCH_FAILURE);
        }

        /* 鉴权失败处理，结束返回 */
        Gmm_AuCntFail();
        return;
    }

    /* Failure 处理过程 */
    if (USIMM_AUTH_MAC_FAILURE == enResult)
    {/* MAC failure */
        Gmm_Au_MacAutnWrong(NAS_MML_REG_FAIL_CAUSE_MAC_FAILURE);
    }
    else
    {/* SQN failure */
        /* AUTHENTICATION AND CIPHERING FAILURE作成 */
        /* Modified by y00245242 for VoLTE_PhaseI  项目, 2013-7-23, begin */
        pNasMsg = Gmm_AuthenAndCipherFailureMsgMake(
                            NAS_MML_REG_FAIL_CAUSE_SYNCH_FAILURE,
                            pAuthCnf->aucAuts[0],
                            &(pAuthCnf->aucAuts[1]));
        /* Modified by y00245242 for VoLTE_PhaseI  项目, 2013-7-23, end */

        /* 调用发送函数 */
        Gmm_SndRrmmDataReq(RRC_NAS_MSG_PRIORTY_HIGH, pNasMsg);

        Gmm_TimerStop(GMM_TIMER_T3316);                                         /* 停止T3316                                */

        g_GmmAuthenCtrl.ucResStoredFlg  = GMM_FALSE;                            /* 将"RES存在标志 "置为0                    */
        g_GmmAuthenCtrl.ucRandStoredFlg = GMM_FALSE;                            /* 将"RAND存在标志 "置为0                   */

        if (GMM_AUTHEN_REJ_CAUSE_SYNC_FAIL == g_GmmAuthenCtrl.ucLastFailCause)
        {/* 上次鉴权失败原因值是同步失败 */
            g_GmmAuthenCtrl.ucAuthenAttmptCnt = 0;          /* GMM Authentication attempt counter清0 */
            g_GmmAuthenCtrl.ucLastFailCause = GMM_AUTHEN_REJ_CAUSE_INVALID;

            Gmm_TimerStop(GMM_TIMER_T3320);                 /* 停T3320 */

            NAS_GMM_SndGasGprsAuthFailNotifyReq();

            Gmm_SndRrmmRelReq(RRC_CELL_BARRED);             /* 发送RRMM_ABORT_REQ(RRC connection) */

            Gmm_Start_StopedRetransmissionTimer();          /* 存在被停止的retransmission timer将其启动 */
        }
        else
        {/* 上次鉴权失败原因值不是同步失败 */
            g_GmmAuthenCtrl.ucLastFailCause = GMM_AUTHEN_REJ_CAUSE_SYNC_FAIL;
            Gmm_TimerStop(GMM_TIMER_T3318);                 /* 停T3318(如果在运行) */
            Gmm_TimerStart(GMM_TIMER_T3320);                /* 启T3320 */
            Gmm_Stop_RetransmissionTimer();                 /* 停止正在运行的retransmission timer */
        }
    }
    return;
}

/*****************************************************************************
 Prototype      : GMM_CasRcvUsimCnfFailGsm
 Description    : GSM鉴权失败,或者其它原因
                  HSS 4100 V200R001 新增
 Input          :
 Output         :
 Return Value   :
 Calls          :
 Called By      :

 History        :
  1.Date        : 2006-01-13
    Author      : Roger Leo
    Modification: Created function
  2.日    期   : 2013年07月23日
    作    者   : y00245242
    修改内容   : 为开发VOLTE，适配新的USIM接口,修改函数入参结构定义
*****************************************************************************/
VOS_VOID GMM_CasRcvUsimCnfFailGsm(USIMM_TELECOM_AUTH_CNF_STRU *pAuthCnf)
{
    /*NAS_MSG_STRU    *pNasMsg;*/

    GMM_LOG_WARN("GSM authentication failure for unacceptable reason by MS!");
    /* 直接发送鉴权回应消息到网络 */
    /*pNasMsg = GMM_MakeAuthenAndCipherResponseMsgGsm
                (GMM_AUTH_AND_CIPH_RES_UNNEEDED);*/
    /*pNasMsg = Gmm_AuthenAndCipherFailureMsgMake(*/
    /*                                    NAS_MML_REG_FAIL_CAUSE_PROTOCOL_ERROR,*/
    /*                                    0,*/
    /*                                    VOS_NULL_PTR);*/
    /* 发送GMM消息 */
    /*Gmm_SndRrmmDataReq(RRC_NAS_MSG_PRIORTY_HIGH,pNasMsg);*/

    return;
}

/*****************************************************************************
 Prototype      : GMM_ExecLlgmmStatusIndCause
 Description    : 分析处理LL_GMM_STATUS_IND_MSG消息中的原因值
                  HSS 4100 V200R001 新增
 Input          :
 Output         :
 Return Value   :
 Calls          :
 Called By      :

 History        :
  1.Date        : 2005-11-08
    Author      : Roger Leo
    Modification: Created function
*****************************************************************************/
VOS_VOID GMM_ExecLlgmmStatusIndCause(VOS_UINT16 usCause)
{
    switch (usCause)
    {
        case LL_GMM_STA_CAUSE_UNSOLICITED_UA_RSP:           /* unsolicited UA response */
            GMM_LOG_WARN("GMM_ExecLlgmmStatusIndCause():Warning: LLC link status mistake!");
            break;

        case LL_GMM_STA_CAUSE_UNSOLICITED_DM_RSP:           /* unsolicited DM response */
            GMM_LOG_WARN("GMM_ExecLlgmmStatusIndCause():Warning: LLC link status mistake!");
            break;

        case LL_GMM_STA_CAUSE_RETRANS_SABM_N200:            /* SABM命令重发N200次 */
            GMM_LOG_WARN("GMM_ExecLlgmmStatusIndCause():Warning: LLC link status mistake!");
            break;

        case LL_GMM_STA_CAUSE_RETRANS_DISC_N200:            /* DISC命令重发N200次 */
            GMM_LOG_WARN("GMM_ExecLlgmmStatusIndCause():Warning: LLC link status mistake!");
            break;

        case LL_GMM_STA_CAUSE_RETRANS_XID_CMD_N200:         /* XID命令重复N200次 */
            GMM_LOG_WARN("GMM_ExecLlgmmStatusIndCause():Warning: LLC link status mistake!");
            break;

        case LL_GMM_STA_CAUSE_INQUIRY_PEER_BUSY_N200:       /* 查询对方是否处于忙状态超过N200次 */
            GMM_LOG_WARN("GMM_ExecLlgmmStatusIndCause():Warning: LLC link status mistake!");
            break;

        case LL_GMM_STA_CAUSE_LLC_INIT_RE_EST:              /* LLC发起ABM重建 */
            GMM_LOG_WARN("GMM_ExecLlgmmStatusIndCause():Warning: LLC link status mistake!");
            break;

        case LL_GMM_STA_CAUSE_PEER_INIT_RE_EST:             /* 对端发起ABM重建 */
            GMM_LOG_WARN("GMM_ExecLlgmmStatusIndCause():Warning: LLC link status mistake!");
            break;

        case LL_GMM_STA_CAUSE_FRAME_REJ_CONDITION:          /* 检测到帧拒绝条件 */
            GMM_LOG_WARN("GMM_ExecLlgmmStatusIndCause():Warning: LLC link status mistake!");
            break;

        case LL_GMM_STA_CAUSE_RECV_FRMR_RSP:                /* 接收到FRMR响应 */
            GMM_LOG_WARN("GMM_ExecLlgmmStatusIndCause():Warning: LLC link status mistake!");
            break;

        case LL_GMM_STA_CAUSE_GMM_ASSIGN_FAIL:              /* TLLI指配失败 */
            GMM_LOG_WARN("GMM_ExecLlgmmStatusIndCause():Warning: LLC ASSIGN command failed!");
            break;

        case LL_GMM_STA_CAUSE_GMM_TRIGGER_FAIL:             /* LLC帧发送触发请求失败 */
            GMM_LOG_WARN("GMM_ExecLlgmmStatusIndCause():Warning: LLC TRIGGER command failed!");
            break;

        case LL_GMM_STA_CAUSE_GMM_SUSPEND_FAIL:             /* LLC挂起失败 */
            GMM_LOG_WARN("GMM_ExecLlgmmStatusIndCause():Warning: LLC SUSPEND command failed!");
            break;

        case LL_GMM_STA_CAUSE_GMM_RESUME_FAIL:              /* LLC恢复失败 */
            GMM_LOG_WARN("GMM_ExecLlgmmStatusIndCause():Warning: LLC RESUME command failed!");
            break;

        default :
            GMM_LOG_WARN("GMM_ExecLlgmmStatusIndCause():Warning: LLC link status alert undefined!");
            break;
    }

    return;
}

/*****************************************************************************
 Prototype      :
 Description    :
                  HSS 4100 V200R001 新增
 Input          :
 Output         :
 Return Value   :
 Calls          :
 Called By      :

 History        :
  1.Date        : 2005-11-08
    Author      : Roger Leo
    Modification: Created function
  2.日    期   : 2006年10月9日
    作    者   : s46746
    修改内容   : 根据问题单号：A32D05744
  3.日    期   : 2007年08月19日
    作    者   : l60022475
    修改内容   : 根据问题单号：A32D12706
  4.日    期   : 2007-10-26
    作    者   : hanlufeng
    修改内容   : A32D13172
  5.日    期   : 2007-10-26
    作    者   : l00107747
    修改内容   : A32D13862
  6.日    期   : 2009-6-3
    作    者   : l00130025
    修改内容   : 问题单号:AT2D12225,从GPRS小区重选到GSM小区,t3312超时后,重回原GPRS小区,发起了normal RAU而非周期性RAU
  7.日    期   : 2010年8月14日
    作    者   : s46746
    修改内容   : DTS2010073001405,G2W异系统重选后，不向层2发送去指派而是挂起层2
  8.日    期   : 2010年9月09日
    作    者   : l65478
    修改内容   : DTS2010090302562,PDP激活过程中发生重选，PDP激活事件比标杆慢
  9.日    期   : 2010年12月01日
    作    者   : z00161729
    修改内容  : DTS2010111903590:LAI、RAI、CELL均未变只是网络模式发生改变，UE发起RAU或LAU，标杆不会
 10.日    期   : 2011年03月1日
    作    者   : w00176964
    修改内容   : 问题单号：DTS2011022503955, [正向质量活动-背景搜优化双模]背景搜快速指定搜过程中，发起
                 用户列表搜索，关机等操作，停止搜网后回RPLMN成功，但当前小区禁止或不支持CS/PS，缓存的用
                 户操作未立即处理，需要等待定时器超时进行异常处理
 11.日    期   : 2012年03月17日
    作    者   : s46746
    修改内容   : DTS2012030705720:RAI和网络模式发生改变,需要进行LAU流程
 12.日    期   : 2012年2月15日
    作    者   : w00166186
    修改内容   : CSFB&PPAC&ETWS&ISR 开发
 13. 日    期   : 2012年7月17日
     作    者   : z00161729
     修改内容   : DTS2012071606177:W(LAI1)-L(TAI2/LAI2 ISR激活CS LAI改变)-W(LAI1网络模式I)需要
                  发起联合rau
 14.日    期   : 2012年8月14日
    作    者   : t00212959
    修改内容   : DCM定制需求和遗留问题
 15.日    期   : 2012年12月11日
    作    者   : w00176964
    修改内容   : NAS_MML_GetPsRestrictNormalServiceFlg修改函数名
 16.日    期   : 2015年1月15日
    作    者   : z00161729
    修改内容   : AT&T 支持DAM特性修改
*****************************************************************************/
VOS_UINT32 GMM_SaveGsmSysInfoIndMsgPara(MMCGMM_GSM_SYS_INFO_IND_ST *pSysInfo)
{
    GMM_RAI_STRU                *pRaiTemp  = VOS_NULL_PTR;
    VOS_UINT8                    ucNetMod  = g_GmmGlobalCtrl.ucNetMod;
    MMCGMM_GSM_SYS_INFO_IND_ST  *ptr;
    VOS_UINT8                   *pucRaiChgFlg;
    VOS_UINT16                   usCellIdNew;
    VOS_UINT8                    ucCsAttachAllow;

    GMM_RAI_STRU                 stAttempUpdateRaiInfo;
    GMM_RAI_STRU                 stOldRai;
    NAS_MML_RAI_STRU            *pstAttemptUpdateRaiInfo = VOS_NULL_PTR;

    gstGmmCasGlobalCtrl.TempMsgPara.ucRaiChgFlg         = GMM_FALSE;
    gstGmmCasGlobalCtrl.TempMsgPara.ucLaiChgFlg         = GMM_FALSE;
    gstGmmCasGlobalCtrl.TempMsgPara.ucDrxLengthChgFlg   = GMM_FALSE;

    pucRaiChgFlg = &gstGmmCasGlobalCtrl.TempMsgPara.ucRaiChgFlg;

    pRaiTemp = (GMM_RAI_STRU *)Gmm_MemMalloc(sizeof(GMM_RAI_STRU));

    if (VOS_NULL_PTR == pRaiTemp)
    {
        PS_NAS_LOG(WUEPS_PID_GMM, VOS_NULL, PS_LOG_LEVEL_ERROR, "GMM_SaveGsmSysInfoIndMsgPara:ERROR: MALLOC FAIL!");
        return GMM_FAILURE;                                                     /* 返回                                     */
    }
    Gmm_MemCpy(pRaiTemp, &g_GmmGlobalCtrl.SysInfo.Rai, sizeof(GMM_RAI_STRU));

    /* 填写RAC */
    pRaiTemp->ucRac = pSysInfo->ucRac;
    /* 填写LAC */
    pRaiTemp->Lai.aucLac[1] = (VOS_UINT8)pSysInfo->usLac;                       /* LAC */
    pRaiTemp->Lai.aucLac[0] = (VOS_UINT8)(pSysInfo->usLac >> 8);
    /* 填写PLMN */
    pRaiTemp->Lai.PlmnId.aucMccDigit[0] =
        (VOS_UINT8)(pSysInfo->stPlmnId.ulMcc & 0x0F);                           /* MCC Digit 1                              */
    pRaiTemp->Lai.PlmnId.aucMccDigit[1] =
        (VOS_UINT8)((pSysInfo->stPlmnId.ulMcc >> 8) & 0x0F);                    /* MCC Digit 2                              */
    pRaiTemp->Lai.PlmnId.aucMccDigit[2] =
        (VOS_UINT8)((pSysInfo->stPlmnId.ulMcc >> 16) & 0x0F);                   /* MCC Digit 3                              */
    pRaiTemp->Lai.PlmnId.aucMncDigit[0] =
        (VOS_UINT8)(pSysInfo->stPlmnId.ulMnc & 0x0F);                           /* MNC Digit 1                              */
    pRaiTemp->Lai.PlmnId.aucMncDigit[1] =
        (VOS_UINT8)((pSysInfo->stPlmnId.ulMnc >> 8) & 0x0F);                    /* MNC Digit 2                              */
    pRaiTemp->Lai.PlmnId.aucMncDigit[2] =
        (VOS_UINT8)((pSysInfo->stPlmnId.ulMnc >> 16) & 0x0F);                   /* MNC Digit 3                              */
    pRaiTemp->Lai.PlmnId.ucMncCnt = 3;                                          /* MNC Degit count                          */

    if (GMM_PLMNID_MNC3_INVALID == pRaiTemp->Lai.PlmnId.aucMncDigit[2])
    {
        pRaiTemp->Lai.PlmnId.ucMncCnt = 2;                                      /* MNC Degit count                          */
    }

    PS_MEM_SET(&stAttempUpdateRaiInfo, 0, sizeof(stAttempUpdateRaiInfo));
    pstAttemptUpdateRaiInfo = NAS_GMM_GetAttemptUpdateRaiInfo();

    NAS_GMM_ConvertPlmnIdToGmmFormat(&pstAttemptUpdateRaiInfo->stLai.stPlmnId, &stAttempUpdateRaiInfo.Lai.PlmnId);
    stAttempUpdateRaiInfo.Lai.aucLac[0] = pstAttemptUpdateRaiInfo->stLai.aucLac[0];
    stAttempUpdateRaiInfo.Lai.aucLac[1] = pstAttemptUpdateRaiInfo->stLai.aucLac[1];
    stAttempUpdateRaiInfo.ucRac         = pstAttemptUpdateRaiInfo->ucRac;

    stOldRai = g_GmmGlobalCtrl.SysInfo.Rai;
    if (VOS_TRUE == NAS_GMM_IsNeedUseAttemptUpdateRaiInfo(pRaiTemp, &stAttempUpdateRaiInfo))
    {
        stOldRai = stAttempUpdateRaiInfo;
    }

    if (GMM_FALSE == Gmm_Com_CmpRai(pRaiTemp, &stOldRai, pSysInfo->ucNetworkOperationMode))
    {                                                                           /* 设置RAI是否变化标志                      */
        gstGmmCasGlobalCtrl.TempMsgPara.ucRaiChgFlg = GMM_TRUE;
        gstGmmCasGlobalCtrl.ucSysRauFlg             = GMM_TRUE;
    }
    if (GMM_FALSE == Gmm_Compare_Lai(&pRaiTemp->Lai, &stOldRai.Lai))
    {                                                                           /* 设置LAI是否变化标志                      */
        gstGmmCasGlobalCtrl.TempMsgPara.ucLaiChgFlg = GMM_TRUE;
    }

    /* GPRS支持指示 */
    g_GmmGlobalCtrl.SysInfo.ucNotSupportGprs = GMM_SUPPORT_GPRS;

    if (0 == pSysInfo->ucGprsSupportInd)
    {
        g_GmmGlobalCtrl.SysInfo.ucNotSupportGprs = GMM_NOT_SUPPORT_GPRS;
    }

    usCellIdNew = pSysInfo->usCellId;

    if (usCellIdNew != g_GmmGlobalCtrl.SysInfo.usGsmCellId)
    {
        g_GmmGlobalCtrl.SysInfo.usGsmCellId = usCellIdNew;
        gstGmmCasGlobalCtrl.TempMsgPara.ucGsmCellChgFlg = GMM_TRUE;             /* 新小区标志 */
    }
    else
    {
        gstGmmCasGlobalCtrl.TempMsgPara.ucGsmCellChgFlg = GMM_FALSE;
    }

    if (0 != pSysInfo->ucNetworkOperationMode)
    {/* 网络模式有效 */
        ucNetMod = pSysInfo->ucNetworkOperationMode;
    }

    if ((g_GmmGlobalCtrl.SysInfo.ucNtType
        != NAS_MML_GetCurrNetRatType())
      &&(GMM_SUSPENDED_WAIT_FOR_SYSINFO != g_GmmGlobalCtrl.ucState))
    {/* 异系统的小区的系统消息的无效条件 */
        PS_NAS_LOG(WUEPS_PID_GMM, VOS_NULL, PS_LOG_LEVEL_WARNING,
            "GMM_SaveGsmSysInfoIndMsgPara:WARNING: Inter-System information cannot be handled in the GMM STATE!");
    }
    /* ==>A32D12706 */
    if ((g_GmmGlobalCtrl.SysInfo.ucNetMod != ucNetMod)
        && (0 != g_GmmGlobalCtrl.SysInfo.ucNetMod)
        && (GMM_STATUS_ATTACHED == g_MmSubLyrShare.GmmShare.ucAttachSta))
    /* <==A32D12706 */
    {/* 网络模式变更 */

        if ((GMM_TRUE == gstGmmCasGlobalCtrl.TempMsgPara.ucLaiChgFlg)
         || (GMM_TRUE == gstGmmCasGlobalCtrl.TempMsgPara.ucRaiChgFlg))
        {
            g_GmmRauCtrl.ucT3330outCnt = 0;

            if ((NAS_MML_MS_MODE_PS_CS == NAS_MML_GetMsMode()))
            {                                                                       /* 用户模式为A,并且已经注册                 */
                if (GMM_SUSPENDED_WAIT_FOR_SYSINFO != g_GmmGlobalCtrl.ucState)
                {
                    /* 非异系统挂起过程等待小区系统消息状态 */
                    /* 同系统的小区系统消息处理 */
                    Gmm_ComNetModeChangeGsm(pSysInfo);                              /* 调用网络模式变换的公共处理               */
                    Gmm_MemFree(pRaiTemp);

                    /*如果小区网络模式改变，GMM_RcvGasSysInfoInd函数不会走到处理恢复层二用户面的处理。
                      所以在此处增加处理。
                    */
                    if (GMM_NOT_SUSPEND_LLC != gstGmmCasGlobalCtrl.ucSuspendLlcCause)
                    {
                        if (GMM_SUSPEND_LLC_FOR_RAU != (GMM_SUSPEND_LLC_FOR_RAU & gstGmmCasGlobalCtrl.ucSuspendLlcCause))
                        {
                            GMM_SndLlcResumeReq(LL_GMM_RESUME_TYPE_ALL);
                            gstGmmCasGlobalCtrl.ucSuspendLlcCause = GMM_NOT_SUSPEND_LLC;
                        }
                        else
                        {
                            gstGmmCasGlobalCtrl.ucSuspendLlcCause = GMM_SUSPEND_LLC_FOR_RAU;
                        }
                    }

                    if (0 == pSysInfo->ucGprsSupportInd)
                    {
                         NAS_GMM_SndMmcActionResultIndWhenBarorNotSupportGprs(NAS_MML_REG_FAIL_CAUSE_SERVING_CELL_DOMAIN_NOT_SUPPORT);
                    }

                    /* 收到G模系统消息, 指示RABM当前系统模式, 根据是否支持GPRS, 挂起或恢复RABM */
                    /* Modified by w00176964 for V7R1C50_DCM接入禁止小区信息上报, 2012-12-11, begin */
                    if ((VOS_TRUE == NAS_MML_GetPsRestrictNormalServiceFlg())
                    /* Modified by w00176964 for V7R1C50_DCM接入禁止小区信息上报, 2012-12-11, end */
                     || (0 == pSysInfo->ucGprsSupportInd)
                     || (GMM_FALSE == gstGmmCasGlobalCtrl.ucTlliAssignFlg))
                    {
                        /* 不支持GPRS、PS bar或者没有指派层2, 挂起RABM, bRatChangeFlg为FALSE
                           没有指派层2时如果不挂起RABM，RABM会向SN发送数据，SN会发送到LLC，
                           而LLC在未指派情况下接收到数据会释放内存导致解除流控,后续数传小包会将消息队列灌满 */
                        NAS_GMM_SndRabmSysSrvChgInd(NAS_MML_NET_RAT_TYPE_GSM,
                                                    VOS_FALSE,
                                                    VOS_TRUE,
                                                    VOS_TRUE);
                    }
                    else
                    {
                        /* 支持GPRS, 恢复RABM, bRatChangeFlg为FALSE */
                        NAS_GMM_SndRabmSysSrvChgInd(NAS_MML_NET_RAT_TYPE_GSM,
                                                    VOS_FALSE,
                                                    VOS_FALSE,
                                                    VOS_TRUE);
                    }

                    return GMM_FAILURE;
                }
            }
        }

        gstGmmSuspendCtrl.ucNetModeChange = GMM_CasGetNetChgType(ucNetMod);
    }
    else
    {
        /* 网络模式没有变更，或者原来网络模式无效 */
        gstGmmSuspendCtrl.ucNetModeChange = GMM_NETMODE_CHG_NULL;
                    /*= GMM_CasGetNetChgTypeByGsm(ucNetMod);*/
    }

    /* Modified by t00212959 for DCM定制需求和遗留问题, 2012-8-16, begin */
    /* 删除对2G系统消息ucDrxTimerMax赋值到DrxLen*/
    /* Modified by t00212959 for DCM定制需求和遗留问题, 2012-8-16, end */

    if (GMM_TRUE == gstGmmCasGlobalCtrl.TempMsgPara.ucGsmCellChgFlg)
    {
        if (GMM_TRUE == *pucRaiChgFlg)
        {
            gstGmmCasGlobalCtrl.ucCellUpdateFlg = GMM_FALSE;
        }
        else
        {
            gstGmmCasGlobalCtrl.ucCellUpdateFlg = GMM_TRUE;
        }
    }
    else
    {
        gstGmmCasGlobalCtrl.ucCellUpdateFlg = GMM_FALSE;
    }

    if (GMM_TRUE == *pucRaiChgFlg)
    {/* RA改变 */
        if ((GMM_FALSE == g_GmmGlobalCtrl.ucSigConFlg)
            && (GMM_RRC_RRMM_EST_CNF_FLG
            == (g_GmmReqCnfMng.ucCnfMask & GMM_RRC_RRMM_EST_CNF_FLG)))
        {/* 无信令且正在建立信令连接 */
            if (GMM_REGISTERED_INITIATED == g_GmmGlobalCtrl.ucState)
            {/* GMM_REGISTERED_INITIATED状态 */
                ptr = (MMCGMM_GSM_SYS_INFO_IND_ST *)Gmm_MemMalloc(sizeof(MMCGMM_GSM_SYS_INFO_IND_ST));
                if (VOS_NULL_PTR == ptr)
                {
                    Gmm_MemFree(pRaiTemp);
                    return GMM_FAILURE;
                }
                Gmm_MemCpy(ptr, pSysInfo,
                           sizeof(MMCGMM_GSM_SYS_INFO_IND_ST));
                g_GmmGlobalCtrl.MsgHold.ulMsgAddrForAttach = (VOS_UINT32)ptr;   /* 存储消息首地址到 ulMsgAddrForAttach      */
                g_GmmGlobalCtrl.MsgHold.ulMsgHoldMsk |= GMM_MSG_HOLD_FOR_ATTACH;/* 置消息保留标志                           */
                Gmm_MemFree(pRaiTemp);
                return GMM_FAILURE;
            }
            else if ((GMM_DEREGISTERED_INITIATED == g_GmmGlobalCtrl.ucState)
                     || (GMM_ROUTING_AREA_UPDATING_INITIATED
                     == g_GmmGlobalCtrl.ucState)
                     || (GMM_SERVICE_REQUEST_INITIATED
                     == g_GmmGlobalCtrl.ucState)
                     || (GMM_REGISTERED_IMSI_DETACH_INITIATED
                     == g_GmmGlobalCtrl.ucState))
            {
                ptr = (MMCGMM_GSM_SYS_INFO_IND_ST *)Gmm_MemMalloc(sizeof(MMCGMM_GSM_SYS_INFO_IND_ST));
                if (VOS_NULL_PTR == ptr)
                {
                    Gmm_MemFree(pRaiTemp);
                    return GMM_FAILURE;
                }
                Gmm_MemCpy(ptr, pSysInfo,
                           sizeof(MMCGMM_GSM_SYS_INFO_IND_ST));
                g_GmmGlobalCtrl.MsgHold.ulMsgAddrForRau = (VOS_UINT32)ptr;      /* 存储消息首地址到 ulMsgAddrForRau         */
                g_GmmGlobalCtrl.MsgHold.ulMsgHoldMsk |= GMM_MSG_HOLD_FOR_RAU;   /* 置消息保留标志                           */
                Gmm_MemFree(pRaiTemp);

                if (0 == pSysInfo->ucGprsSupportInd)
                {
                     NAS_GMM_SndMmcActionResultIndWhenBarorNotSupportGprs(NAS_MML_REG_FAIL_CAUSE_SERVING_CELL_DOMAIN_NOT_SUPPORT);
                }

                return GMM_FAILURE;
            }
            else
            {
            }
        }
    }

    if ((MMCGMM_GSM_NO_FORBIDDEN == pSysInfo->ulForbiddenFlg)
        && (0 != pSysInfo->ucGprsSupportInd))
    {
        Gmm_MemCpy(&g_GmmGlobalCtrl.SysInfo.Rai, pRaiTemp, sizeof(GMM_RAI_STRU));   /* 存储系统信息中的RAI                      */
        if (GMM_RAU_NORMAL_CS_UPDATED == g_GmmGlobalCtrl.ucSpecProcInCsTrans)
        {
            g_GmmGlobalCtrl.ucSpecProcInCsTrans = GMM_NULL_PROCEDURE;
            gstGmmCasGlobalCtrl.TempMsgPara.ucRaiChgFlg = GMM_TRUE;
        }
    }
    else
    {
        /* 获取CS ATTACH Allow标志 */
        ucCsAttachAllow                             = NAS_MML_GetCsAttachAllowFlg();
        gstGmmCasGlobalCtrl.TempMsgPara.ucRaiChgFlg = GMM_FALSE;
        gstGmmCasGlobalCtrl.ucSysRauFlg             = GMM_FALSE;
        if ((MMCGMM_GSM_NO_FORBIDDEN == pSysInfo->ulForbiddenFlg)
            || (MMCGMM_GSM_FORBIDDEN_PLMN_FOR_GPRS == pSysInfo->ulForbiddenFlg))
        {
            if ((GMM_STATUS_ATTACHED == g_MmSubLyrShare.GmmShare.ucAttachSta)
             && (VOS_TRUE == ucCsAttachAllow))
            {
                g_GmmGlobalCtrl.ucSpecProcInCsTrans = GMM_RAU_NORMAL_CS_UPDATED;
            }
        }
    }

    g_GmmGlobalCtrl.SysInfo.ucNetMod = ucNetMod;                                /* 网络模式                                 */
    if (g_GmmGlobalCtrl.ucNetMod != ucNetMod)
    {
        g_GmmGlobalCtrl.ucNetMod = ucNetMod;                                    /* 网络模式                                 */
    }

    g_GmmGlobalCtrl.SysInfo.ucForbMask = (VOS_UINT8)pSysInfo->ulForbiddenFlg;   /* PLMN是否禁止                             */
    g_GmmGlobalCtrl.SysInfo.ucSysValidFlg = GMM_TRUE;                           /* 置系统信息有效标志                       */

    Gmm_MemFree(pRaiTemp);
    return GMM_SUCCESS;
}

/*****************************************************************************
 Prototype      : GMM_CharToUlong
 Description    : 字节数据转换成ULONG型
                  HSS 4100 V200R001 新增
 Input          :
 Output         :
 Return Value   :
 Calls          :
 Called By      :

 History        :
  1.Date        : 2005-11-08
    Author      : Roger Leo
    Modification: Created function
*****************************************************************************/
VOS_VOID GMM_CharToUlong(VOS_UINT32 *ulDst, VOS_UINT8 *pucSrc)
{
    VOS_UINT32  ulResult;

    ulResult  = 0;
    /*lint -e701 -e961*/
    ulResult += (*(pucSrc++) << 24);
    ulResult += (*(pucSrc++) << 16);
    ulResult += (*(pucSrc++) << 8);
    ulResult += (*(pucSrc) );
    /*lint +e701 +e961*/
    *ulDst = ulResult;
    return;
}

/*****************************************************************************
 Prototype      : GMM_CreateNewTlli
 Description    : 创建新的TLLI值
                  HSS 4100 V200R001 新增
 Input          :
 Output         :
 Return Value   :
 Calls          :
 Called By      :

 History        :
  1.Date        : 2005-11-08
    Author      : Roger Leo
    Modification: Created function

  2.Date        : 2015-07-23
    Author      : wx270776
    Modification: OM Migration
*****************************************************************************/
VOS_VOID GMM_CreateNewTlli(VOS_UINT32 *pulTmsi, VOS_UINT8 ucType)
{
    VOS_UINT32  ulTLLI;
    VOS_UINT32  ulHead5;

    ulTLLI   = *pulTmsi;                /* 得到PTMSI值 */
    ulHead5  = ulTLLI >> 27;            /* 取得TLLI的标志头 */
    ulHead5 &= 0x07;                    /* 清除无效的数位 */

    /*填写TLLI值的高5位值*/
    switch (ucType)
    {
        case GMM_RANDOM_TLLI:
            ulHead5  = 0x0f;            /* 5位值是 01111 */
            /* Modified by wx270776 for OM融合, 2015-7-23, begin */
            ulTLLI   = VOS_GetSlice();   /* 取系统时钟数作为伪随机数 */
            /* Modified by wx270776 for OM融合, 2015-7-23, end */
            break;

        case GMM_LOCAL_TLLI:
            ulHead5 |= 0x18;            /* 5位值是 11XXX */
            break;

        case GMM_FOREIGN_TLLI:
            ulHead5 |= 0x10;            /* 5位值是 10XXX */
            break;

        case GMM_AUXILIARY_TLLI:
            ulHead5 = 0x0e;            /* 5位值是 01110 */
            break;

        default :                       /* 保留,参看3GPP TS23.003描述 */
            ulHead5  = 0x00;            /* 5位值是 00000 */
            break;
    }

    /*填写TLLI值的低27位值*/
    ulHead5 = ulHead5 << 27;
    ulTLLI &= 0x07ffffff;               /* 清除高5位 */
    ulTLLI += ulHead5;                  /* 新TTLLI值 */

    *pulTmsi = ulTLLI;                  /* 返回结果 */
    return;
}

#if (FEATURE_ON == FEATURE_LTE)
/*****************************************************************************
 函 数 名  : NAS_GMM_UseGutiDerivedPtmsi
 功能描述  : 当前Tin值和GU P-tmsi是否指示需要使用 GUTI导出的P-Tmsi
 输入参数  : VOS_VOID
 输出参数  : 无
 返 回 值  : VOS_UINT32
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2011年8月20日
    作    者   : l00130025
    修改内容   : PhaseI 问题单修改:DTS2011080305247,G模要使用映射的P-TMSI导出TLLI

*****************************************************************************/
VOS_UINT32 NAS_GMM_UseGutiDerivedPtmsi ( VOS_VOID )
{
    VOS_UINT8                           ucUeIdMask;
    VOS_UINT32                          ulGetGutiRst;
    NAS_MML_TIN_TYPE_ENUM_UINT8         enTinType;
    VOS_UINT32                          ulRslt;

    /* 如下，协议描述，b)和d) 返回VOS_TRUE,其它返回 VOS_FALSE
    4.7.1.4.1   Radio resource sublayer address handling (A/Gb mode only)

    For an MS supporting S1 mode, the following five cases can be distinguished:
    a)  the TIN indicates "P-TMSI" or "RAT related TMSI" and the MS holds a valid P-TMSI and a RAI;
    b)  the TIN indicates "GUTI" and the MS holds a valid GUTI;
    c)  the TIN is deleted and the MS holds a valid P-TMSI and RAI;
    d)  the TIN is deleted and the MS holds a valid GUTI, but no valid P-TMSI and RAI; or
    e)  none of the previous cases is fulfilled.

    In case b), the MS shall derive a P-TMSI from the GUTI and
                then a foreign TLLI from this P-TMSI and proceed as specified for case i) above.
    In case d) the MS shall derive a P-TMSI from the GUTI and then a foreign TLLI from this P-TMSI and proceed as specified for case i) above.

    In case a) the MS shall derive a foreign TLLI from the P-TMSI and proceed as specified for case i) above.
    In case c) the MS shall derive a foreign TLLI from the P-TMSI and proceed as specified for case i) above.
    In case e) the MS shall proceed as as specified for case ii) above.
    */

    /* 获取当前GU的p-Tmsi的取值 */
    ucUeIdMask          = NAS_GMM_GetUeIdMask();

    /* 获取当前的Tin值和Mapped P-Tmsi是否正确 */
    ulGetGutiRst        = NAS_GMM_MapPtmsiFromGUTI();
    enTinType           = NAS_MML_GetTinType();

    if (VOS_OK == ulGetGutiRst)
    {
        /* b)  the TIN indicates "GUTI" and the MS holds a valid GUTI; */
        if (NAS_MML_TIN_TYPE_GUTI == enTinType)
        {
            ulRslt = VOS_TRUE;
        }
        /* d)  the TIN is deleted and the MS holds a valid GUTI, but no valid P-TMSI and RAI; */
        else if ( (NAS_MML_TIN_TYPE_INVALID == enTinType)
               && (GMM_UEID_P_TMSI != (ucUeIdMask & GMM_UEID_P_TMSI) ))
        {
            ulRslt = VOS_TRUE;
        }
        else
        {
            ulRslt = VOS_FALSE;
        }
    }
    else
    {
        ulRslt = VOS_FALSE;
    }

    return ulRslt;

}

#endif

/*****************************************************************************
 函 数 名  : NAS_GMM_GetPTmsiForTLLI
 功能描述  : 获取当前要使用的P-TMSI值
 输入参数  : VOS_UINT8 *
 输出参数  : 无
 返 回 值  : VOS_UINT32
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2011年8月19日
    作    者   : l00130025
    修改内容   : PhaseI 问题单修改:DTS2011080305247,G模要使用映射的P-TMSI导出TLLI
  2.日    期   : 2013年05月21日
    作    者   : l65478
    修改内容   : DTS2013053002449希腊问题:当不支持LTE时,使用GU下的ID
 3.日    期   :2013年8月29日
    作    者   :z00161729
    修改内容  :DTS2013082702039:syscfg不支持l或l disable时，gmm rau和attach不需携带ue network capability

*****************************************************************************/
VOS_UINT32 NAS_GMM_GetPTmsiForTLLI(
    VOS_UINT8                           aucPtmsi[NAS_MML_MAX_PTMSI_LEN]
)
{
    VOS_UINT8                          *pucPtmsiAddr        = VOS_NULL_PTR;
    VOS_UINT8                           ucUeIdMask;
    VOS_UINT32                          ulLocalPtmsiFlg;

#if (FEATURE_ON == FEATURE_LTE)
    VOS_UINT32                          ulGetGutiRst;
    VOS_UINT8                          *pucMappedPtmsiAddr  = VOS_NULL_PTR;
    NAS_MML_TIN_TYPE_ENUM_UINT8         enTinType;
    VOS_UINT32                          ulRslt;

    VOS_UINT32                          ulIsSupportLteCap;
#endif

    /*
    4.7.1.4.1   Radio resource sublayer address handling (A/Gb mode only)
    This subclause describes how the RR addressing is managed by GMM.
    For the detailed coding of the different TLLI types and how a TLLI can be derived from a P-TMSI, see 3GPP TS 23.003 [10].
    For an MS not supporting S1 mode, two cases can be distinguished:
    -   a valid P-TMSI is available in the MS; or
    -   no valid P-TMSI is available in the MS.
    i)   valid P-TMSI available
        If the MS has stored a valid P-TMSI, the MS shall derive a foreign TLLI from that P-TMSI and shall use it for transmission of the:
    -   ATTACH REQUEST message of any GPRS combined/non-combined attach procedure; other GMM messages sent during this procedure shall be transmitted using the same foreign TLLI until the ATTACH ACCEPT message or the ATTACH REJECT message is received; and
    -   ROUTING AREA UPDATE REQUEST message of a combined/non-combined RAU procedure if the MS has entered a new routing area, or if the GPRS update status is not equal to GU1 UPDATED. Other GMM messages sent during this procedure shall be transmitted using the same foreign TLLI, until the ROUTING AREA UPDATE ACCEPT message or the ROUTING AREA UPDATE REJECT message is received.
        After a successful GPRS attach or routing area update procedure, independent whether a new P-TMSI is assigned, if the MS has stored a valid P-TMSI then the MS shall derive a local TLLI from the stored P-TMSI and shall use it for addressing at lower layers.
    NOTE 1: Although the MS derives a local TLLI for addressing at lower layers, the network should not assume that it will receive only LLC frames using a local TLLI. Immediately after the successful GPRS attach or routing area update procedure, the network must be prepared to continue accepting LLC frames from the MS still using the foreign TLLI.
    ii) no valid P-TMSI available
        When the MS has not stored a valid P-TMSI, i.e. the MS is not attached to GPRS, the MS shall use a randomly selected random TLLI for transmission of the:
    -   ATTACH REQUEST message of any combined/non-combined GPRS attach procedure.
        The same randomly selected random TLLI value shall be used for all message retransmission attempts and for the cell updates within one attach attempt.
        Upon receipt of an ATTACH REQUEST message, the network shall assign a P-TMSI to the MS. The network derives a local TLLI from the assigned P-TMSI, and transmits the assigned P-TMSI to the MS.
        Upon receipt of the assigned P-TMSI, the MS shall derive the local TLLI from this P-TMSI and shall use it for addressing at lower layers.
    NOTE 2: Although the MS derives a local TLLI for addressing at lower layers, the network should not assume that it will receive only LLC frames using a local TLLI. Immediately after the successful GPRS attach, the network must be prepared to continue accepting LLC frames from the MS still using the random TLLI.
    In both cases the MS shall acknowledge the reception of the assigned P-TMSI to the network. After receipt of the acknowledgement, the network shall use the local TLLI for addressing at lower layers.


    For an MS supporting S1 mode, the following five cases can be distinguished:
    a)  the TIN indicates "P-TMSI" or "RAT related TMSI" and the MS holds a valid P-TMSI and a RAI;
    b)  the TIN indicates "GUTI" and the MS holds a valid GUTI;
    c)  the TIN is deleted and the MS holds a valid P-TMSI and RAI;
    d)  the TIN is deleted and the MS holds a valid GUTI, but no valid P-TMSI and RAI; or
    e)  none of the previous cases is fulfilled.

    In case a) the MS shall derive a foreign TLLI from the P-TMSI and proceed as specified for case i) above.
    In case b), the MS shall derive a P-TMSI from the GUTI and
                then a foreign TLLI from this P-TMSI and proceed as specified for case i) above.
    In case c) the MS shall derive a foreign TLLI from the P-TMSI and proceed as specified for case i) above.
    In case d) the MS shall derive a P-TMSI from the GUTI and then a foreign TLLI from this P-TMSI and proceed as specified for case i) above.
    In case e) the MS shall proceed as as specified for case ii) above.
    */

    /* 取得存储PTMSI数据的地址 */
    pucPtmsiAddr        = NAS_MML_GetUeIdPtmsi();

    ucUeIdMask          = NAS_GMM_GetUeIdMask();

    /* 判断GUPTMSI是否有效，VOS_TRUE:有效;VOS_FALSE:无效; */
    if ( GMM_UEID_P_TMSI == (ucUeIdMask & GMM_UEID_P_TMSI) )
    {
        PS_MEM_CPY(aucPtmsi, pucPtmsiAddr, NAS_MML_MAX_PTMSI_LEN);

        ulLocalPtmsiFlg = VOS_TRUE;
    }
    else
    {
        ulLocalPtmsiFlg = VOS_FALSE;
    }

#if (FEATURE_ON == FEATURE_LTE)

    /* 初始化当前的P-Tmsi的存在标志 */
    ulRslt              = VOS_TRUE;

    /* 获取当前的Tin值和Mapped P-Tmsi */
    ulGetGutiRst        = NAS_GMM_MapPtmsiFromGUTI();
    enTinType           = NAS_MML_GetTinType();

    /* 取得存储PTMSI数据的地址 */
    pucMappedPtmsiAddr  = NAS_GMM_GetMappedPtmsiAddr();

    /* reference to 24.008 4.7.1.4.1 */
    ulIsSupportLteCap = NAS_MML_IsSupportLteCapability();

    /* syscfg设置不支持L或者L 已经disable则无需从guti中获取ptimsi */
    if (VOS_FALSE == ulIsSupportLteCap)
    {
        if (VOS_TRUE == ulLocalPtmsiFlg)
        {
            PS_MEM_CPY(aucPtmsi, pucPtmsiAddr, NAS_MML_MAX_PTMSI_LEN);
        }
        else
        {
            ulRslt = VOS_FALSE;
        }

        return ulRslt;
    }

    /* a)  the TIN indicates "P-TMSI" or "RAT related TMSI" and the MS holds a valid P-TMSI and a RAI; */
    if ( ( (NAS_MML_TIN_TYPE_RAT_RELATED_TMSI == enTinType)
        || (NAS_MML_TIN_TYPE_PTMSI  == enTinType))
      && (VOS_TRUE == ulLocalPtmsiFlg))
    {
        PS_MEM_CPY(aucPtmsi, pucPtmsiAddr, NAS_MML_MAX_PTMSI_LEN);
    }
    /* b)  the TIN indicates "GUTI" and the MS holds a valid GUTI; */
    else if ((NAS_MML_TIN_TYPE_GUTI == enTinType)
          && (VOS_OK == ulGetGutiRst) )
    {
        PS_MEM_CPY(aucPtmsi, pucMappedPtmsiAddr, NAS_MML_MAX_PTMSI_LEN);
    }
    /* c)  the TIN is deleted and the MS holds a valid P-TMSI and RAI; */
    else if ((NAS_MML_TIN_TYPE_INVALID == enTinType)
          && (VOS_TRUE == ulLocalPtmsiFlg))
    {
        PS_MEM_CPY(aucPtmsi, pucPtmsiAddr, NAS_MML_MAX_PTMSI_LEN);
    }
    /* d)  the TIN is deleted and the MS holds a valid GUTI, but no valid P-TMSI and RAI; */
    else if ((NAS_MML_TIN_TYPE_INVALID == enTinType)
          && (VOS_FALSE == ulLocalPtmsiFlg)
          && (VOS_OK == ulGetGutiRst))
    {
        PS_MEM_CPY(aucPtmsi, pucMappedPtmsiAddr, NAS_MML_MAX_PTMSI_LEN);
    }
    /*e)  none of the previous cases is fulfilled.*/
    else
    {
        ulRslt = VOS_FALSE;
    }

    return ulRslt;

#else

    /* LTE不打开时，只需要判断 GU P-Tmsi是否有效 */
    return ulLocalPtmsiFlg;
#endif

}

/*****************************************************************************
 函 数 名  : GMM_UpdateSysTlli
 功能描述  : 检查TLLI类型有效性,并更新默认TLLI类型和数值
 输入参数  : TlliType
 输出参数  : 无
 返 回 值  : 无
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2011年7月27日
    作    者   : h44270
    修改内容   : V7R1 PHASEII 重构: 数据结构，全局变量初始化，魔鬼数字的调整
  2.日    期   : 2011年8月19日
    作    者   : l00130025
    修改内容   : 问题单号:DTS2011080305247,G模要使用映射的P-TMSI导出TLLI
  3.日    期   : 2013年5月20日
    作    者   : s00217060
    修改内容   : coverity和foritfy修改

*****************************************************************************/
VOS_VOID GMM_UpdateSysTlli(GMM_TLLI_TYPE TlliType)
{
    VOS_UINT8                           aucPtmsi[NAS_MML_MAX_PTMSI_LEN];

    /* 入口参数检查 */
    if ( (GMM_RANDOM_TLLI != TlliType)
      && (GMM_FOREIGN_TLLI != TlliType)
      && (GMM_LOCAL_TLLI != TlliType) )
    {
        GMM_LOG_ERR("GMM_UpdateSysTlli():Error: TlliType is not correct.");
        return;
    }

    /* Added by s00217060 for coverity和foritfy修改 , 2013-05-20, begin */
    /* 初始化 */
    PS_MEM_SET(aucPtmsi, 0, sizeof(aucPtmsi));
    /* Added by s00217060 for coverity和foritfy修改 , 2013-05-20, end */

    /* 没有存贮有效的PTMSI, 计算RANDOM TLLI */
    if (VOS_FALSE == NAS_GMM_GetPTmsiForTLLI(aucPtmsi))
    {
        GMM_CreateNewTlli(&gstGmmCasGlobalCtrl.ulTLLI, GMM_RANDOM_TLLI);

        gstGmmCasGlobalCtrl.ucflgTLLI = GMM_RANDOM_TLLI;

        return;
    }

    /* 待更新的TLLI值 */
    GMM_CharToUlong(&gstGmmCasGlobalCtrl.ulTLLI, aucPtmsi);


    GMM_CreateNewTlli(&gstGmmCasGlobalCtrl.ulTLLI, TlliType);

    gstGmmCasGlobalCtrl.ucflgTLLI = TlliType;

    return;
}

/*****************************************************************************
 Prototype      : GMM_GetPtmsiFromMsgIe
 Description    : 从指定消息IE中得到PTMSI
                  HSS 4100 V200R001 新增
 Input          :
 Output         :
 Return Value   :
 Calls          :
 Called By      :

 History        :
  1.Date        : 2005-11-08
    Author      : Roger Leo
    Modification: Created function
  2.日    期   : 2012年8月10日
    作    者   : y00213812
    修改内容   : DTS2012082204471, TQE清理
  3.日    期   : 2013年08月23日
    作    者   : f00179208
    修改内容   : ErrLog&FTM项目,PTMSI发生改变时上报给OM
*****************************************************************************/
VOS_UINT32 GMM_GetPtmsiFromMsgIe(VOS_UINT8 *pData)
{
    VOS_UINT32  ulNewTlli = 0;
    VOS_UINT32  ulRslt;

    /* 判断IE数据类型是否有效 */
    if ( (5 != *(pData))                                    /*长度值非法*/
      || (0x04 != (*(pData+1) & 0x07) )                     /*类型不匹配*/
        )
    {/* 类型无效 */
        GMM_LOG_WARN("GMM_GetPtmsiFromMsgIe:WARNING: Wrong length or type in IE data");
        return GMM_FALSE;
    }

    /* 更新GMM系统量存贮的PTMSI值 */
    NAS_MML_SetUeIdPtmsi((pData + 2));
    g_GmmGlobalCtrl.UeInfo.UeId.ucUeIdMask |= GMM_UEID_P_TMSI;

    GMM_CharToUlong(&ulNewTlli,
                    NAS_MML_GetUeIdPtmsi());  /*待更新的TLLI值*/

    /* 计算local TLLI值 */
    GMM_CreateNewTlli(&ulNewTlli, GMM_LOCAL_TLLI);          /*计算TLLI*/

    /* 指配new TLLI */
    /*modified by Y00213812 for DTS2012082204471 TQE清理, 2012-08-10, begin*/
    ulRslt = GMM_AssignNewTlli(ulNewTlli, GMM_LOCAL_TLLI);
    if (GMM_FALSE == ulRslt)
    {
        GMM_LOG_WARN("GMM_GetPtmsiFromMsgIe():Error: new TLLI assigned failed!");
    }
    /*modified by Y00213812 for DTS2012082204471 TQE清理, 2012-08-10, end*/

#if (FEATURE_ON == FEATURE_PTM)
    /* 工程菜单打开后，PTMSI发生改变需要上报给OM */
    NAS_GMM_SndAcpuOmChangePtmsi();
#endif

    return GMM_TRUE;
}

/*****************************************************************************
 Prototype      : GMM_FreeOldTlli
 Description    : 释放old TLLI
                  HSS 4100 V200R001 新增
 Input          :
 Output         :
 Return Value   :
 Calls          :
 Called By      :

 History        :
  1.Date        : 2005-11-08
    Author      : Roger Leo
    Modification: Created function
  2.Date        : 2011-11-11
    Author      : h44270
    Modification: 问题单号：DTS2010110500099/DTS2010111103124,修正GMM在W模下向GAS发送去指派消息
*****************************************************************************/
VOS_VOID GMM_FreeOldTlli(VOS_VOID)
{
    LL_GMM_ASSIGN_REQ_MSG   *pAssignReqMsg;
    GRRGMM_ASSIGN_REQ_ST    *pGasAssignMsg;
    VOS_UINT32               ulRet;

    /* 通知LLC释放old TLLI */
    pAssignReqMsg = GMM_MakeLlgmmAssignReqMsg(GMM_OP_TLLI_UNASSIGN);
    if (VOS_NULL_PTR == pAssignReqMsg)
    {
        GMM_LOG_ERR("GMM_FreeOldTlli():Error: making LLC message wrongly!");
        return;
    }
    /* 发送原语到LLC */
    ulRet = PS_SEND_MSG(WUEPS_PID_GMM, pAssignReqMsg);

    /* 通知GRR释放old TLLI */
    if (NAS_MML_NET_RAT_TYPE_GSM == NAS_MML_GetCurrNetRatType())
    {
        pGasAssignMsg = GMM_MakeGrrmmAssignReqMsg(GMM_GRR_OLD_TLLI);
        if (VOS_NULL_PTR == pGasAssignMsg)
        {
            GMM_LOG_ERR("GMM_FreeOldTlli():Error: making GAS message wrongly!");
            return;
        }
        /* 发送原语到GRR */
        ulRet = PS_SEND_MSG(WUEPS_PID_GMM, pGasAssignMsg);
        if (VOS_OK != ulRet)
        {
            GMM_LOG_ERR("GMM_FreeOldTlli():Error: Send msg fail!");
        }
    }
    return;
}

/*****************************************************************************
 Prototype      : GMM_FreeSysTlli
 Description    : 释放系统默认TLLI
                  HSS 4100 V200R001 新增
 Input          :
 Output         :
 Return Value   :
 Calls          :
 Called By      :

 History        :
  1.Date        : 2005-11-08
    Author      : Roger Leo
    Modification: Created function
  2. 日    期   : 2010年10月29日
     作    者   : l00167671/罗开辉
     修改内容   : 问题单号：DTS2010100802035,添加恢复LLC
*****************************************************************************/
VOS_VOID GMM_FreeSysTlli(VOS_VOID)
{
    LL_GMM_ASSIGN_REQ_MSG   *pAssignReqMsg;
    VOS_UINT32               ulRet;

    /* 通知LLC释放old TLLI */
    pAssignReqMsg = GMM_MakeLlgmmAssignReqMsg(GMM_OP_TLLI_UNASSIGN_SYS);
    if (VOS_NULL_PTR == pAssignReqMsg)
    {
        GMM_LOG_ERR("GMM_FreesSysTlli():Error: making LLC message wrongly!");
        return;
    }
    /* 发送原语到LLC */
    ulRet = PS_SEND_MSG(WUEPS_PID_GMM, pAssignReqMsg);

    /* 置TLLI未指配标志 */
    gstGmmCasGlobalCtrl.ucTlliAssignFlg = GMM_FALSE;

    if (GMM_NOT_SUSPEND_LLC != gstGmmCasGlobalCtrl.ucSuspendLlcCause)
    {

        GMM_SndLlcResumeReq(LL_GMM_RESUME_TYPE_ALL);                               /* 恢复LLC数据传输 */
        gstGmmCasGlobalCtrl.ucSuspendLlcCause = GMM_NOT_SUSPEND_LLC;
    }

    if (VOS_OK != ulRet)
    {
        GMM_LOG_ERR("GMM_FreesSysTlli():Error: Send msg fail!");
    }

    return;
}

/*****************************************************************************
 Prototype      : GMM_AssignNewTlli
 Description    : 指配new TLLI
                  HSS 4100 V200R001 新增
 Input          :
 Output         :
 Return Value   :
 Calls          :
 Called By      :

 History        :
  1.Date        : 2005-11-08
    Author      : Roger Leo
    Modification: Created function
*****************************************************************************/
VOS_UINT32 GMM_AssignNewTlli(VOS_UINT32 ulNewTlli, VOS_UINT8 ucType)
{
    LL_GMM_ASSIGN_REQ_MSG   *pAssignReqMsg;
    GRRGMM_ASSIGN_REQ_ST    *pGasAssignMsg;
    VOS_UINT32               ulRet;

    /* 替换系统默认TLLI */
    gstGmmCasGlobalCtrl.ulOldTLLI = gstGmmCasGlobalCtrl.ulTLLI;
    gstGmmCasGlobalCtrl.ulTLLI    = ulNewTlli;

    gstGmmCasGlobalCtrl.ucflgTLLI = ucType;             /* 修改TLLI类型标志 */

    /* 通知LLC指配new TLLI */
    pAssignReqMsg = GMM_MakeLlgmmAssignReqMsg(GMM_OP_TLLI_MODIFY);
    if (VOS_NULL == pAssignReqMsg)
    {
        GMM_LOG_ERR("GMM_AssignNewTlli():Error: making LLC message wrongly!");
        return GMM_FALSE;
    }
    /* 发送原语到LLC */
    ulRet = PS_SEND_MSG(WUEPS_PID_GMM, pAssignReqMsg);

    /* 通知GRR指配new TLLI */
    pGasAssignMsg = GMM_MakeGrrmmAssignReqMsg(GMM_GRR_NEW_TLLI);
    if (VOS_NULL == pGasAssignMsg)
    {
        GMM_LOG_ERR("GMM_AssignNewTlli():Error: making GAS message wrongly!");
        return GMM_FALSE;
    }
    /* 发送原语到GRR */
    ulRet = PS_SEND_MSG(WUEPS_PID_GMM, pGasAssignMsg);
    if (VOS_OK != ulRet)
    {
        GMM_LOG_ERR("GMM_AssignNewTlli():Error: Send msg fail!");
    }

    return GMM_TRUE;
}

/*****************************************************************************
 Prototype      : GMM_AssignModifyTlli
 Description    : 修改TLLI
                  HSS 4100 V200R001 新增
 Input          :
 Output         :
 Return Value   :
 Calls          :
 Called By      :

 History        :
  1.Date        : 2006-05-20
    Author      : Roger Leo
    Modification: Created function
*****************************************************************************/
VOS_UINT32 GMM_AssignModifyTlli(VOS_UINT32 ulNewTlli, VOS_UINT8 ucType)
{
    LL_GMM_ASSIGN_REQ_MSG   *pAssignReqMsg;
    GRRGMM_ASSIGN_REQ_ST    *pGasAssignMsg;
    VOS_UINT32               ulRet;

    /* 替换系统默认TLLI */
    gstGmmCasGlobalCtrl.ulTLLI    = ulNewTlli;

    gstGmmCasGlobalCtrl.ucflgTLLI = ucType;             /* 修改TLLI类型标志 */

    /* 通知LLC指配new TLLI */
    pAssignReqMsg = GMM_MakeLlgmmAssignReqMsg(GMM_OP_TLLI_MODIFY);
    if (VOS_NULL == pAssignReqMsg)
    {
        GMM_LOG_ERR("GMM_AssignModifyTlli():Error: making LLC message wrongly!");
        return GMM_FALSE;
    }
    /* 发送原语到LLC */
    ulRet = PS_SEND_MSG(WUEPS_PID_GMM, pAssignReqMsg);

    /* 通知GRR指配new TLLI */
    pGasAssignMsg = GMM_MakeGrrmmAssignReqMsg(GMM_GRR_NEW_TLLI);
    if (VOS_NULL == pGasAssignMsg)
    {
        GMM_LOG_ERR("GMM_AssignModifyTlli():Error: making GAS message wrongly!");
        return GMM_FALSE;
    }
    /* 发送原语到GRR */
    ulRet = PS_SEND_MSG(WUEPS_PID_GMM, pGasAssignMsg);
    if (VOS_OK != ulRet)
    {
        GMM_LOG_ERR("GMM_AssignModifyTlli():Error: Send msg fail!");
    }

    return GMM_TRUE;
}

/*****************************************************************************
 Prototype      : GMM_AssignSysTlli
 Description    : 指配同步当前系统的TLLI
                  HSS 4100 V200R001 新增
 Input          :
 Output         :
 Return Value   :
 Calls          :
 Called By      :

 History        :
  1.Date        : 2005-11-15
    Author      : Roger Leo
    Modification: Created function
  2.日    期   : 2011年12月8日
    作    者   : s46746
    修改内容   : 问题单号：DTS2011111603445,接收到系统消息而且层2已经指派后才能恢复RABM
*****************************************************************************/
VOS_VOID GMM_AssignSysTlli(VOS_VOID)
{
    LL_GMM_ASSIGN_REQ_MSG   *pAssignReqMsg;
    GRRGMM_ASSIGN_REQ_ST    *pGasAssignMsg;
    GMM_OP_TLLI              TlliOpMode;
    VOS_UINT32               ulRet;

    /* 判断TLLI操作类型 */
    if (GMM_FALSE == gstGmmCasGlobalCtrl.ucTlliAssignFlg)
    {
        TlliOpMode = GMM_OP_TLLI_ASSIGN;                    /* 重新指配TLLI */
    }
    else
    {
        TlliOpMode = GMM_OP_TLLI_SYNC;                      /* 同步当前TLLI */
    }

    /* 通知LLC同步系统TLLI */
    pAssignReqMsg = GMM_MakeLlgmmAssignReqMsg(TlliOpMode);
    if (VOS_NULL == pAssignReqMsg)
    {
        GMM_LOG_ERR("GMM_AssignSysTlli():Error: making LLC message wrongly!");
        return;
    }
    /* 发送原语到LLC */
    ulRet = PS_SEND_MSG(WUEPS_PID_GMM, pAssignReqMsg);
    if (GMM_OP_TLLI_ASSIGN == TlliOpMode)
    {
        gstGmmCasGlobalCtrl.ucTlliAssignFlg = GMM_TRUE;     /* TLLI指配完成标志 */

        /* 恢复RABM, bRatChangeFlg为FALSE */
        NAS_GMM_SndRabmSysSrvChgInd(NAS_MML_NET_RAT_TYPE_GSM,
                                    VOS_FALSE,
                                    VOS_FALSE,
                                    VOS_TRUE);
    }

    /* 通知GRR指配new TLLI */
    pGasAssignMsg = GMM_MakeGrrmmAssignReqMsg(GMM_GRR_NEW_TLLI);
    if (VOS_NULL == pGasAssignMsg)
    {
        GMM_LOG_ERR("GMM_AssignSysTlli():Error: making GAS message wrongly!");
        return;
    }
    /* 发送原语到GRR */
    ulRet = PS_SEND_MSG(WUEPS_PID_GMM, pGasAssignMsg);
    if (VOS_OK != ulRet)
    {
        GMM_LOG_ERR("GMM_AssignSysTlli():Error: Send msg fail!");
    }

    return;
}

/*****************************************************************************
 Prototype      : GMM_AssignGsmKc
 Description    : 指配GSM Kc
                  HSS 4100 V200R001 新增
 Input          :
 Output         :
 Return Value   :
 Calls          :
 Called By      :

 History        :
  1.Date        : 2005-12-27
    Author      : Roger Leo
    Modification: Created function
  2.日    期    : 2009年03月18日
    作    者    : l65478
    修改内容    : 根据问题单号：AT2D08671,数传状态下，W出服务区后，切到G，数传恢复失败，因为GMM没有配置LL加密算法
*****************************************************************************/
VOS_VOID GMM_AssignGsmKc(VOS_VOID)
{
    LL_GMM_ASSIGN_REQ_MSG   *pAssignReqMsg;
    VOS_UINT32               ulRet;

    /* 通知LLC指配Kc和加密算法 */
    pAssignReqMsg = GMM_MakeLlgmmAssignReqMsg(GMM_OP_TLLI_KC);
    if (VOS_NULL == pAssignReqMsg)
    {
        GMM_LOG_ERR("GMM_AssignGsmKc():Error: making LLC message wrongly!");
        return;
    }
    /* 设置加密算法已经指配 */
    gstGmmCasGlobalCtrl.ucGprsCipherAssign = VOS_TRUE;

    /* 发送原语到LLC */
    ulRet = PS_SEND_MSG(WUEPS_PID_GMM, pAssignReqMsg);
    if (VOS_OK != ulRet)
    {
        GMM_LOG_ERR("GMM_AssignGsmKc():Error: Send msg fail!");
    }
    return;
}

/*****************************************************************************
 Prototype      : GMM_SaveAuthenResult
 Description    : 保存USIM卡鉴权结果
                  HSS 4100 V200R001 新增
 Input          :
 Output         :
 Return Value   :
 Calls          :
 Called By      :

 History        :
  1.Date        : 2005-11-08
    Author      : Roger Leo
    Modification: Created function
  2.日    期   : 2013年07月23日
    作    者   : y00245242
    修改内容   : 为开发VOLTE，适配新的USIM接口
*****************************************************************************/
VOS_VOID GMM_SaveAuthenResult(USIMM_TELECOM_AUTH_CNF_STRU *pAuthCnf)
{
    VOS_UINT8   i;
    VOS_UINT8  *pucAuthRes;

    /* Modified by y00245242 for VoLTE_PhaseI  项目, 2013-7-23, begin */
    pucAuthRes = &(pAuthCnf->aucAuthRes[0]);
    /* Modified by y00245242 for VoLTE_PhaseI  项目, 2013-7-23, end */

    /* 保存GSM鉴权结果 */
    if (GMM_UMTS_AUTHEN_UNSUPPORTED == g_GmmAuthenCtrl.ucUmtsAuthFlg)
    {
        g_GmmAuthenCtrl.ucResExtLen = 0;                    /* 没有扩展部分 */
        for (i=1; i<5; i++)
        {
            if (i > *(pucAuthRes))
            {
                g_GmmAuthenCtrl.aucRes[i-1] = 0xFF;         /* 填充无效值 */
            }
            else
            {
                /* Modified by y00245242 for VoLTE_PhaseI  项目, 2013-8-9, begin */
                g_GmmAuthenCtrl.aucRes[i-1] = *((pucAuthRes + i));
                /* Modified by y00245242 for VoLTE_PhaseI  项目, 2013-8-9, end */
            }
        }
        return;
    }

    /* 保存RES的基本内容 */
    if (4 > *(pucAuthRes))
    {
        Gmm_MemCpy(g_GmmAuthenCtrl.aucRes,
                   (pucAuthRes + 1),
                  *(pucAuthRes) );                          /* 保存RES */

        for ( i=*(pucAuthRes); i<4; i++ )
        {
            g_GmmAuthenCtrl.aucRes[i] = 0xFF;
        }

        g_GmmAuthenCtrl.ucResExtLen = 0;                    /* 存RES(EXTERN)的长度，0:aucResExt无意义   */
    }
    else
    {
        Gmm_MemCpy(g_GmmAuthenCtrl.aucRes,
                (pucAuthRes + 1), 4 );                      /* 保存RES */
        g_GmmAuthenCtrl.ucResExtLen =
               *(pucAuthRes) - 4;                           /* 存RES(EXTERN)的长度，0:aucResExt无意义   */
    }

    /* 保存RES扩展内容 */
    if (0 < g_GmmAuthenCtrl.ucResExtLen)
    {
        if (12 < g_GmmAuthenCtrl.ucResExtLen)
        {
            g_GmmAuthenCtrl.ucResExtLen = 12;               /* 修正无效的RES Extension长度 */
        }
        Gmm_MemCpy(g_GmmAuthenCtrl.aucResExt,
               (pucAuthRes + 5),
               g_GmmAuthenCtrl.ucResExtLen );               /* 保存RES Extension */
    }

    return;
}

/*****************************************************************************
 Prototype      : GMM_UpdateAuthenCtrlFlg
 Description    : 更新鉴权控制结构中的标志
                  HSS 4100 V200R001 新增
 Input          :
 Output         :
 Return Value   :
 Calls          :
 Called By      :

 History        :
  1.Date        : 2005-11-08
    Author      : Roger Leo
    Modification: Created function
  2.日    期    : 2007年01月13日
    作    者    : s46746
    修改内容    : 根据问题单号：A32D08326
*****************************************************************************/
VOS_VOID GMM_UpdateAuthenCtrlFlg(VOS_VOID)
{
    VOS_UINT8   i;

    if (GMM_FALSE == g_GmmAuthenCtrl.ucResStoredFlg)
    {                                                       /* 易失性内存为空*/
        g_GmmAuthenCtrl.ucRandStoredFlg = GMM_TRUE;
        g_GmmAuthenCtrl.ucResStoredFlg  = GMM_TRUE;         /* 设定易失性内存不为空*/

        for (i=0; i<GMM_MAX_SIZE_RAND; i++)
        {                                                   /* 更新上一次的RAND值*/
            g_GmmAuthenCtrl.aucRand[i] = g_GmmAuthenCtrl.aucRandSav[i];
        }
        Gmm_TimerStart(GMM_TIMER_T3316);                    /* 启动T3316*/
    }
    else
    {                                                       /* 易失性内存不为空*/
        for (i=0; i<GMM_MAX_SIZE_RAND; i++)
        {                                                   /* 更新上一次的RAND值*/
            g_GmmAuthenCtrl.aucRand[i] = g_GmmAuthenCtrl.aucRandSav[i];
        }

        Gmm_TimerStart(GMM_TIMER_T3316);                    /* 启动T3316*/
    }

    return;
}


/*****************************************************************************
 Prototype      : GMM_RcvGsmPagingAtRegNmlServ
 Description    : 在GMM_REGISTERED_NORMAL_SERVICE状态，
                   接收GRRMM_PAGING_IND消息
                  HSS 4100 V200R001 新增
 Input          :
 Output         :
 Return Value   :

 Calls          :
 Called By      :

 History        :
  1.Date        : 2005-11-03
    Author      : Roger Leo
    Modification: Created function

  2. x51137 2006/4/28 A32D02889
  3.日    期   : 2012年3月1日
    作    者   : z00161729
    修改内容   : V7R1 C50 支持ISR修改
  4.日    期   : 2014年9月5日
    作    者   : w00167002
    修改内容   : GCF.2.3.1.6 失败修改，在收到 GAS的PAGING IND时候不启动T3314，待
                 收到LL下发的数据才启动。
*****************************************************************************/
VOS_VOID GMM_RcvGsmPagingAtRegNmlServ(GRRMM_PAGING_IND_ST *pMsg)
{
    NAS_MML_NET_RAT_TYPE_ENUM_UINT8    enRatType;


    if (GAS_IMSI == pMsg->ucMSIDType)
    {/* 寻呼的类型为IMSI */
        if (GMM_FALSE == g_GmmGlobalCtrl.ucSigConFlg)
        {                                                                       /* 无信令连接                               */
            g_GmmAttachCtrl.ucPagingWithImsiFlg = GMM_TRUE;                     /* 标记由网侧的IMSI寻呼触发的ATTACH         */
        }
        Gmm_PagingInd_common();
    }
    else
    {
        /* 在收到PAGING IND时不进入READY状态，在收到LLC INFOM时进入 */

        if ( 0 == gstGmmCasGlobalCtrl.ulReadyTimerValue )
        {
            gstGmmCasGlobalCtrl.GmmSrvState = GMM_AGB_GPRS_STANDBY;
#if (FEATURE_LTE == FEATURE_ON)
            if (GMM_TIMER_T3312_FLG != (GMM_TIMER_T3312_FLG & g_GmmTimerMng.ulTimerRunMask))
            {
                NAS_GMM_SndLmmTimerInfoNotify(GMM_TIMER_T3312, GMM_LMM_TIMER_START);
            }
#endif
            Gmm_TimerStart(GMM_TIMER_T3312);
        }


        enRatType   = NAS_MML_GetCurrNetRatType();
        if ((GMM_RAU_FOR_WAITSERVICE == gstGmmSuspendCtrl.ucRauCause)
         && (gstGmmCasGlobalCtrl.ucLastDataSender != enRatType)
#if (FEATURE_ON == FEATURE_LTE)
         && (gstGmmCasGlobalCtrl.ucLastDataSender != NAS_MML_NET_RAT_TYPE_LTE)
#endif
         )
        {
            GMM_LOG_INFO("GMM_RcvGsmPagingAtRegNmlServ:Inter System change, Exec select RAU.");
            Gmm_RoutingAreaUpdateInitiate(GMM_UPDATING_TYPE_INVALID);
            gstGmmSuspendCtrl.ucRauCause = GMM_RAU_FOR_NORMAL;
            return;
        }

        GMM_SndLlcTriggerReq(LL_GMM_TRIG_CAUSE_PAG_RSP);
    /*}*/
    }

    return;
}

/*****************************************************************************
 Prototype      : GMM_RcvGsmPagingAtDeregInit
 Description    : 在GMM_DEREGISTERED_INITIATED状态，
                   接收GRRMM_PAGING_IND消息
                  HSS 4100 V200R001 新增
 Input          :
 Output         :
 Return Value   :

 Calls          :
 Called By      :

 History        :
  1.Date        : 2005-11-03
    Author      : Roger Leo
    Modification: Created function
*****************************************************************************/
VOS_VOID GMM_RcvGsmPagingAtDeregInit(GRRMM_PAGING_IND_ST *pMsg)
{
    GRRMM_PAGING_IND_ST    *pMsgHold;

    if (GAS_IMSI == pMsg->ucMSIDType)
    {/* 寻呼的类型为IMSI */
        if ((GMM_FALSE == g_GmmGlobalCtrl.ucSigConFlg)
            && (GMM_RRC_RRMM_EST_CNF_FLG
            == (g_GmmReqCnfMng.ucCnfMask & GMM_RRC_RRMM_EST_CNF_FLG)))
        {                                                                       /* 无信令且正在建立信令连接                 */
            g_GmmGlobalCtrl.MsgHold.ulMsgHoldMsk |= GMM_MSG_HOLD_FOR_PAGING;    /* 置消息被缓存的标志                       */
            pMsgHold = (GRRMM_PAGING_IND_ST *)Gmm_MemMalloc(sizeof(GRRMM_PAGING_IND_ST));
            if (VOS_NULL_PTR == pMsgHold)
            {
                return;
            }
            Gmm_MemCpy(pMsgHold, pMsg, sizeof(GRRMM_PAGING_IND_ST));
            g_GmmGlobalCtrl.MsgHold.ulMsgAddrForPaging = (VOS_UINT32)pMsgHold;  /* 保留RRMM_PAGING _IND首地址               */
        }
        else
        {                                                                       /* 有信令或没有信令且还没建信令             */
            if (GMM_AGENT_USIM_AUTHENTICATION_CNF_FLG
                == (g_GmmReqCnfMng.ucCnfMask
                & GMM_AGENT_USIM_AUTHENTICATION_CNF_FLG))
            {                                                                   /* 等待鉴权响应                             */
                Gmm_TimerStop(GMM_TIMER_PROTECT);                               /* 停保护定时器                             */
                g_GmmReqCnfMng.ucCnfMask
                    &= ~GMM_AGENT_USIM_AUTHENTICATION_CNF_FLG;                  /* 清除原语等待标志                         */
            }
            NAS_MML_SetPsUpdateStatus(NAS_MML_ROUTING_UPDATE_STATUS_NOT_UPDATED); /* 更新状态变为GU2                          */
            Gmm_DelPsLocInfoUpdateUsim();
            Gmm_SndMmcLocalDetachInd(NAS_MML_REG_FAIL_CAUSE_NTDTH_IMSI);

            if (GMM_DEREGISTERED_INITIATED == g_GmmGlobalCtrl.ucState)
            {
                Gmm_RcvDetachAcceptMsg_DeregInit();
            }
            else
            {
                Gmm_RcvDetachAcceptMsg_RegImsiDtchInit();
                Gmm_ComStaChg(GMM_DEREGISTERED_NORMAL_SERVICE);
                Gmm_Attach_Prepare();                                           /* 全局变量的清理工作，为attach作好准备     */
                Gmm_AttachInitiate(GMM_NULL_PROCEDURE);
            }
        }
    }

    return;
}

/*****************************************************************************
 Prototype      : GMM_RcvGsmPagingAtRauInit
 Description    : 在GMM_ROUTING_AREA_UPDATING_INITIATED状态，
                   接收GRRMM_PAGING_IND消息
                  HSS 4100 V200R001 新增
 Input          :
 Output         :
 Return Value   :

 Calls          :
 Called By      :

 History        :
  1.Date        : 2005-11-03
    Author      : Roger Leo
    Modification: Created function
*****************************************************************************/
VOS_VOID GMM_RcvGsmPagingAtRauInit(GRRMM_PAGING_IND_ST *pMsg)
{
    GRRMM_PAGING_IND_ST    *pMsgHold;

    if (GAS_IMSI == pMsg->ucMSIDType)
    {/* 寻呼的类型为IMSI */
        if ((GMM_FALSE == g_GmmGlobalCtrl.ucSigConFlg)
            && (GMM_RRC_RRMM_EST_CNF_FLG
            == (g_GmmReqCnfMng.ucCnfMask & GMM_RRC_RRMM_EST_CNF_FLG)))
        {                                                                       /* 无信令且正在建立信令连接                 */
            g_GmmGlobalCtrl.MsgHold.ulMsgHoldMsk |= GMM_MSG_HOLD_FOR_PAGING;    /* 置消息被缓存的标志                       */
            pMsgHold = (GRRMM_PAGING_IND_ST *)Gmm_MemMalloc(sizeof(GRRMM_PAGING_IND_ST));
            if (VOS_NULL_PTR == pMsgHold)
            {
                  return;
            }
            Gmm_MemCpy(pMsgHold, pMsg, sizeof(GRRMM_PAGING_IND_ST));
            g_GmmGlobalCtrl.MsgHold.ulMsgAddrForPaging = (VOS_UINT32)pMsgHold;       /* 保留RRMM_PAGING _IND首地址              */
        }
        else
        {                                                                       /* 有信令或没有信令且还没建信令             */
            Gmm_TimerStop(GMM_TIMER_T3330);                                     /* 停T3330                                  */
            Gmm_TimerStop(GMM_TIMER_T3318);                                     /* 停止T3318                                */
            Gmm_TimerStop(GMM_TIMER_T3320);                                     /* 停止T3320                                */

            Gmm_PagingInd_common();
        }
    }

    return;
}

/*****************************************************************************
 Prototype      : GMM_RcvGsmPaging_RegPlmnSrch
 Description    : 在GMM_REGISTER_PLMN_SEARCH状态，
                   接收GRRMM_PAGING_IND消息
 Input          :
 Output         :
 Return Value   :

 Calls          :
 Called By      :

 History        :
  1.Date        : 2009-07-20
    Author      : s46746
    Modification: Created function
  2.日    期   : 2012年8月15日
    作    者   : z00161729
    修改内容   : DCM定制需求和遗留问题修改
*****************************************************************************/
VOS_VOID GMM_RcvGsmPaging_RegPlmnSrch(GRRMM_PAGING_IND_ST *pMsg)
{
    if (GAS_IMSI != pMsg->ucMSIDType)
    {
        /* Modified by z00161729 for DCM定制需求和遗留问题, 2012-8-15, begin */
        Gmm_SndMmcGprsServiceInd(NAS_MMC_GMM_GPRS_SERVICE_PAGING);
        /* Modified by z00161729 for DCM定制需求和遗留问题, 2012-8-15, end */

        g_GmmGlobalCtrl.enServReq = GMM_SERVICE_REQ_PAGING;
    }

    return;
}

/*****************************************************************************
 Prototype      : GMM_AuthType
 Description    : 分析当前鉴权过程类型
                  HSS 4100 V200R001 新增
 Input          :
 Output         :
 Return Value   :
 Calls          :
 Called By      :

 History        :
 1.Date        : 2005-11-08
   Author      : Roger Leo
   Modification: Created function
 2.日    期   : 2011年01月18日
   作    者   : lijun 00171473
   修改内容   : W网络下SIM卡收到网络的3G鉴权应该按2G鉴权处理
 3.日    期   : 2011年7月25日
   作    者   : h44270
   修改内容   : V7R1 PHASEII 重构: 数据结构，全局变量初始化，魔鬼数字的调整
*****************************************************************************/
VOS_UINT8 GMM_AuthType(VOS_UINT8 ucAutnFlag)
{
    VOS_UINT8                               usAuthTypeRet;
    NAS_MML_NET_RAT_TYPE_ENUM_UINT8         enCurRat;

    usAuthTypeRet = GMM_AUTH_FAILURE;
    enCurRat = NAS_MML_GetCurrNetRatType();
    switch (enCurRat)
    {
        case NAS_MML_NET_RAT_TYPE_WCDMA:/*在UMTS网络中*/
            if (NAS_MML_SIM_TYPE_USIM == NAS_MML_GetSimType())
            {   /*卡类型是USIM卡*/
                if (GMM_TRUE == ucAutnFlag)
                {
                    usAuthTypeRet = GMM_AUTH_UMTS;                      /*UMTS鉴权*/
                }
                else
                {
                    usAuthTypeRet = GMM_AUTH_GSM_AUTH_UNACCEPTABLE;     /*GSM authentication unacceptable*/
                }
            }
            else
            {
                if (NAS_MML_SIM_TYPE_SIM == NAS_MML_GetSimType())
                {   /*卡类型是SIM卡*/
                    if (GMM_TRUE == ucAutnFlag)
                    {
                        usAuthTypeRet = GMM_AUTH_GSM;       /*GSM鉴权*/
                    }
                    else
                    {
                        usAuthTypeRet = GMM_AUTH_GSM;       /*GSM鉴权*/
                    }
                }
            }
            break;

        case NAS_MML_NET_RAT_TYPE_GSM:
            if (NAS_MML_SIM_TYPE_USIM == NAS_MML_GetSimType())
            {   /*卡类型是USIM卡*/
                if (GMM_TRUE == ucAutnFlag)
                {
                    usAuthTypeRet = GMM_AUTH_UMTS;          /*UMTS鉴权*/
                }
                else
                {
                    usAuthTypeRet = GMM_AUTH_GSM;           /*GSM鉴权*/
                }
            }
            else
            {
                if (NAS_MML_SIM_TYPE_SIM == NAS_MML_GetSimType())
                {   /*卡类型是SIM卡*/
                    if (GMM_TRUE == ucAutnFlag)
                    {
                        usAuthTypeRet = GMM_AUTH_GSM;       /*GSM鉴权*/
                    }
                    else
                    {
                        usAuthTypeRet = GMM_AUTH_GSM;       /*GSM鉴权*/
                    }
                }
            }
            break;

        default:
            break;
    }

    /* 系统不允许进行UMTS鉴权 */
    if ((GMM_FALSE == g_GmmAuthenCtrl.ucUmtsAuthFlg) && (GMM_AUTH_UMTS == usAuthTypeRet))
    {
        usAuthTypeRet = GMM_AUTH_FAILURE;
        PS_NAS_LOG(WUEPS_PID_GMM, VOS_NULL, PS_LOG_LEVEL_WARNING, "Gmm_RcvAuthenAndCipherRequestMsg:WARNING: perform the GSM authentication challenge");
    }

    return usAuthTypeRet;
}


/*****************************************************************************
 函 数 名  : NAS_GMM_RauCompleteHandling
 功能描述  : RAU过程中，收到RAU ACCEPT后，需要等待WRR或RABM的回复消息，
             再收到所有回复消息后，回复网络RAU COMPLETE消息，及通知MMC等模块。
 输入参数  : VOS_VOID
 输出参数  : 无
 返 回 值  : VOS_VOID
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2010年3月18日
    作    者   : o00132663
    修改内容   : 新生成函数
  2.日    期   : 2010年4月12日
    作    者   : l65478
    修改内容   : AT2D18389,在初始小区更新时，GMM应该通知LLC发送NULL帧
  3.日    期   : 2010年9月09日
    作    者   : l65478
    修改内容   : DTS2010090302562,PDP激活过程中发生重选，PDP激活事件比标杆慢
  4.日    期   : 2012年3月16日
    作    者   : s46746
    修改内容   : DTS2012030603347:GSM下,GMM进行联合注册,仅PS成功,5次触发CS注册,CS单独注册失败,
                 接入层恢复GPRS失败导致又进行联合RAU,形成注册循环
  5.日    期   : 2012年4月03日
    作    者   : l65478
    修改内容   : DTS2012032603732:在RAU失败时，却打印了RAU成功
  6.日    期   : 2012年4月26日
    作    者   : l65478
    修改内容   : DTS2012041707074:在联合RAU PS成功,CS失败时,最后一次RAU ACCEPT没有通知MM/MMC注册结果
  7.日    期   : 2012年12月22日
    作    者   : l00171473
    修改内容   : DTS2012122200186:调用2G的处理函数时没有判断2G
  8.日    期   : 2014年6月13日
    作    者   : w00242748
    修改内容   : DSDS 新特性
  9.日    期   : 2014年7月18日
    作    者   : b00269685
    修改内容   : DSDS IV修改
*****************************************************************************/
VOS_VOID NAS_GMM_RauCompleteHandling( VOS_VOID )
{
    NAS_MSG_STRU                            *pSendNasMsg;
    GMM_MSG_RESOLVE_STRU                    stAttachAcceptIe;
    NAS_MSG_FOR_PCLINT_STRU                 stNasMsg;

    Gmm_MemSet(&stAttachAcceptIe, 0, sizeof(GMM_MSG_RESOLVE_STRU));
    Gmm_MemSet(&stNasMsg, 0, sizeof(NAS_MSG_STRU));

    /* 发送RAU complete消息 */
    if (VOS_TRUE == gstGmmCasGlobalCtrl.ucRauCmpFlg)
    {
        gstGmmCasGlobalCtrl.ucRauCmpFlg = VOS_FALSE;
        pSendNasMsg = Gmm_RoutingAreaUpdateCompleteMsgMake();

        Gmm_SndRrmmDataReq(RRC_NAS_MSG_PRIORTY_HIGH, pSendNasMsg);



        if (GMM_TRUE == GMM_IsCasGsmMode())
        {
            /* 只有前面进行过RAU suspend，此处resume才有意义 */
            if (GMM_SUSPEND_LLC_FOR_RAU == (gstGmmCasGlobalCtrl.ucSuspendLlcCause & GMM_SUSPEND_LLC_FOR_RAU))
            {
                gstGmmCasGlobalCtrl.ucSuspendLlcCause &= ~GMM_SUSPEND_LLC_FOR_RAU;

                if (GMM_NOT_SUSPEND_LLC == gstGmmCasGlobalCtrl.ucSuspendLlcCause)
                {
                    GMM_SndLlcResumeReq(LL_GMM_RESUME_TYPE_ALL);                             /* 恢复LLC数据传输 */
                }
            }

            gstGmmCasGlobalCtrl.ucCellUpdateFlg = GMM_FALSE;
            GMM_InitCellUpdate(GMM_FALSE);                                                   /* 小区更新，生效新的READY TIMER */
        }


        g_GmmGlobalCtrl.ucSpecProc = GMM_NULL_PROCEDURE;
        g_GmmRauCtrl.ucPeriodicRauFlg = GMM_FALSE;
        NAS_INFO_LOG(WUEPS_PID_GMM, "NAS_GMM_RauCompleteHandling:INFO: specific procedure ended");
    }

    /* RABM发送RSP消息有如下几种情况:
       1、NORMAL RAU成功
       2、系统间重选/切换成功
       3、系统间重选/切换失败

       GMM在ATTEMP COUNTER大于5的情况有如下几种情况:
       1、RAU失败
       2、联合RAU失败
       3、联合RAU只有PS成功
       所以GMM在通知MM/MMC注册结果时,应该只有在第三种情况通知成功,
       其它两种情况应该通知失败,但是因为在收到注册结果时已经通知,所以此处代码冗余*/
    if (5 <= g_GmmRauCtrl.ucRauAttmptCnt)
    {
        if ((GMM_REGISTERED_ATTEMPTING_TO_UPDATE_MM == g_GmmGlobalCtrl.ucState)
         || ( (GMM_SUSPENDED_NORMAL_SERVICE == g_GmmGlobalCtrl.ucState)
           && (GMM_REGISTERED_ATTEMPTING_TO_UPDATE_MM == gstGmmSuspendCtrl.ucPreState)))
        {
            NAS_GMM_SndMmCombinedRauAccept(GMMMM_RAU_RESULT_PS_ONLY,
                                           NAS_MML_REG_FAIL_CAUSE_MSC_UNREACHABLE,
                                           &stNasMsg,
                                           &stAttachAcceptIe);

            /* 向MMC发送PS注册结果 */
            NAS_GMM_SndMmcPsRegResultInd(GMM_MMC_ACTION_RAU,
                                         GMM_MMC_ACTION_RESULT_SUCCESS,
                                         NAS_MML_REG_FAIL_CAUSE_MSC_UNREACHABLE);

            /*  事件上报 */
            NAS_EventReport(WUEPS_PID_GMM,
                            NAS_OM_EVENT_RAU_SUCC,
                            VOS_NULL_PTR,
                            NAS_OM_EVENT_NO_PARA);
        }
    }

    if (GMM_RAU_FOR_NORMAL != gstGmmSuspendCtrl.ucRauCause)
    {
        GMM_LOG_INFO("GMM_RauSuccessInterSys:Gmm rau success for intersystem change.");

        gstGmmSuspendCtrl.ucRauCause = GMM_RAU_FOR_NORMAL;

        GMM_ResumeSuccess();
    }

    /*处理follow on 或其他缓存的事件 */
    NAS_GMM_HandleDelayedEvent();
}


/*****************************************************************************
  函 数 名  : NAS_GMM_GetGmmCasGlobalCtrl
  功能描述  : 获取全局变量gstGmmCasGlobalCtrl的地址
  输入参数  : 无
  输出参数  : 无
  返 回 值  : GMM_CAS_CTRL_STRU*
  调用函数  :
  被调函数  :

  修改历史  :
1.日    期  : 2015年4月7日
  作    者  : wx270776
  修改内容  : 新生成函数
*****************************************************************************/
GMM_CAS_CTRL_STRU* NAS_GMM_GetGmmCasGlobalCtrl(VOS_VOID)
{
    return &(gstGmmCasGlobalCtrl);
}

/*****************************************************************************
  函 数 名  : NAS_GMM_GetMui
  功能描述  : 获取全局变量usMui的值
  输入参数  : 无
  输出参数  : 无
  返 回 值  : VOS_UINT16
  调用函数  :
  被调函数  :

  修改历史  :
1.日    期  : 2015年4月7日
  作    者  : wx270776
  修改内容  : 新生成函数
*****************************************************************************/
VOS_UINT16 NAS_GMM_GetMui(VOS_VOID)
{
    return (NAS_GMM_GetGmmCasGlobalCtrl()->usMui);
}

/*****************************************************************************
  函 数 名  : NAS_GMM_IncreaseMui
  功能描述  : usMui自增
  输入参数  : 无
  输出参数  : 无
  返 回 值  : VOS_UINT16
  调用函数  :
  被调函数  :

  修改历史  :
1.日    期  : 2015年4月7日
  作    者  : wx270776
  修改内容  : 新生成函数
*****************************************************************************/
VOS_UINT16 NAS_GMM_IncreaseMui(VOS_VOID)
{
    return ((NAS_GMM_GetGmmCasGlobalCtrl()->usMui)++);
}

/*****************************************************************************
  函 数 名  : NAS_GMM_GetPowerOffDetachPsMui
  功能描述  : 获取全局变量usPowerOffDetachPsMui的值
  输入参数  : 无
  输出参数  : 无
  返 回 值  : VOS_UINT16
  调用函数  :
  被调函数  :

  修改历史  :
1.日    期  : 2015年4月7日
  作    者  : wx270776
  修改内容  : 新生成函数
*****************************************************************************/
VOS_UINT16 NAS_GMM_GetPowerOffDetachPsMui(VOS_VOID)
{
    return (NAS_GMM_GetGmmCasGlobalCtrl()->usPowerOffDetachPsMui);
}

/*****************************************************************************
  函 数 名  : NAS_GMM_SetPowerOffDetachPsMui
  功能描述  : 设置usPowerOffDetachPsMui的值
  输入参数  : VOS_UINT16                usMui
  输出参数  : 无
  返 回 值  : 无
  调用函数  :
  被调函数  :

  修改历史  :
1.日    期  : 2015年4月7日
  作    者  : wx270776
  修改内容  : 新生成函数
*****************************************************************************/
VOS_VOID NAS_GMM_SetPowerOffDetachPsMui(
    VOS_UINT16                          usMui
)
{
    NAS_GMM_GetGmmCasGlobalCtrl()->usPowerOffDetachPsMui = usMui;

    return;
}

/*****************************************************************************
  函 数 名  : NAS_GMM_IsPowerOffPsDetachMsg
  功能描述  : 判断是否是PS关机DETACH消息
  输入参数  : 无
  输出参数  : 无
  返 回 值  : VOS_TRUE: 是关机PS DETACH消息
              VOS_FALSE:
  调用函数  :
  被调函数  :

  修改历史  :
1.日    期  : 2015年4月7日
  作    者  : wx270776
  修改内容  : 新生成函数
*****************************************************************************/
VOS_UINT32 NAS_GMM_IsPowerOffPsDetachMsg(
    NAS_MSG_STRU                       *pstNasL3Msg
)
{
    VOS_UINT32                          ulUsimMMApiIsTestCard;
    ulUsimMMApiIsTestCard             = NAS_USIMMAPI_IsTestCard();

    /* 如果当前是关机流程，则携带NeedCnf标志 */
    if ( (GMM_MSG_LEN_DETACH_REQUEST    <= pstNasL3Msg->ulNasMsgSize)
      && (GMM_PD_GMM                    == pstNasL3Msg->aucNasMsg[0])
      && (GMM_MSG_DETACH_REQUEST        == pstNasL3Msg->aucNasMsg[1])
      && ((GMM_GPRS_DETACH_POWEROFF     == pstNasL3Msg->aucNasMsg[2])
       || (GMM_COMBINED_DETACH_POWEROFF == pstNasL3Msg->aucNasMsg[2]))
      && (VOS_FALSE                     == ulUsimMMApiIsTestCard    ) )
    {
        return VOS_TRUE;
    }

    return VOS_FALSE;
}

/*****************************************************************************
  函 数 名  : NAS_GMM_GetCiphInd
  功能描述  : 获取CiphInd
  输入参数  : 无
  输出参数  : 无
  返 回 值  : VOS_UINT8
  调用函数  :
  被调函数  :

  修改历史  :
1.日    期  : 2015年4月7日
  作    者  : wx270776
  修改内容  : 新生成函数:原有逻辑进行函数封装
*****************************************************************************/
VOS_UINT8 NAS_GMM_GetCiphInd(
    NAS_MSG_STRU                       *pstNasL3Msg
)
{
    VOS_UINT8                           ucCiphInd;

    if (VOS_FALSE == gstGmmCasGlobalCtrl.ucGprsCipher)
    {
        ucCiphInd = 0;
    }
    else
    {
        if (GMM_PD_GMM == pstNasL3Msg->aucNasMsg[0])
        {
            switch(pstNasL3Msg->aucNasMsg[1])
            {
                case 0x01:
                case 0x04:
                case 0x12:
                case 0x13:
                case 0x14:
                case 0x1c:
                case 0x15:
                case 0x16:
                case 0x08:
                case 0x0B:
                    ucCiphInd = 0;
                    break;

                default:
                    ucCiphInd = 1;
                    break;
            }
        }
        else
        {
             ucCiphInd = 1;
        }
    }

    return ucCiphInd;
}

/*lint -restore */
#ifdef  __cplusplus
  #if  __cplusplus
  }
  #endif
#endif
