/******************************************************************************

                  版权所有 (C), 2001-2011, 华为技术有限公司

 ******************************************************************************
  文 件 名   : MnMsgReqProc.c
  版 本 号   : 初稿
  作    者   : 周君 40661
  生成日期   : 2008年2月14日
  最近修改   :
  功能描述   :
  修改历史   :
  1.日    期   : 2008年2月14日
    作    者   : 周君 40661
    修改内容   : 创建文件

  2.日    期   : 2008年6月11日
    作    者   : fuyingjun 62575
    修改内容   : 问题单号：AT2D03725, 修改几处删除响应事件已上报标志的使用错误
                 所有删除SIM卡中记录的操作在操作开始时均将上述标志置为FALSE
  3.日    期   : 2008年6月16日
    作    者   : 傅映君 62575
    修改内容   : 问题单号：AT2D03830, 修改en_NV_Item_SMS_SERVICE_Para项读写相关代码
  4.日    期   : 2008年6月16日
    作    者   : 傅映君 62575
    修改内容   : 问题单号：,
  5.日    期   : 2008年6月16日
    作    者   : 傅映君 62575
    修改内容   : 存储短消息设备满时，修改接收短消息处理方式为不存储，没有发送SMMA消息
  6.日    期   : 2008年8月14日
    作    者   : 傅映君 62575
    修改内容   : 问题单号 AT2D04609,CMMS命令的增加；
  7.日    期   : 2008年8月14日
    作    者   : fuyingjun
    修改内容  : 问题单号:AT2D04545, SMS相关AT模块和MN模块新增代码复杂度超过要求数值20
  8.日    期   : 2008年8月14日
    作    者   : fuyingjun
    修改内容  : 问题单号:AT2D05123, CMGL 显示指定状态的短信不成功
  9.日    期   : 2008年8月25日
    作    者   : 傅映君 62575
    修改内容   : 问题单号 AT2D04608,
 10.日    期   : 2008年8月30日
    作    者   : 傅映君 62575
    修改内容   : 问题单号 AT2D05372,统一NAS模块的VOS_MemCmp，VOS_StrNiCmp和VOS_StrCmp比较操作；
 11.日    期   : 2008年09月08日
    作    者   : f62575
    修改内容   : 问题单AT2D05583,CBS功能模块代码PC-lint错误
 12.日    期   : 2008年09月11日
    作    者   : f62575
    修改内容   : 问题单号AT2D05684, API支持无DA或SCA的短消息写操作
 13.日    期   : 2008年10月10日
    作    者   : f62575
    修改内容   : 问题单号：AT2D06152（AT2D06151）, USIMM优化合入后，SMSP文件相关读写操作失败
 14.日    期   : 2008年12月16日
    作    者   : f62575
    修改内容   : 问题单号:AT2D06704,删除或读取不存在的指定<index>的短信时，协议栈认为出错，但终端的自动化测试工具认为应返回OK
 15.日    期   : 2008-11-17
    作    者   : f62575
    修改内容   : 问题单号:AT2D06843, 短信状态报告的读，删除和上报接口与终端工具需求不符问题
 16.日    期   : 2009-01-12
    作    者   : f62575
    修改内容   : 问题单号:AT2D07548, 短信中心查询操作失败需要返回准确原因
 20.日    期   : 2009年3月3日
    作    者   : z40661
    修改内容   : 问题单号：AT2D08974, 短信打印级别过高
 21.日    期   : 2009年3月23日
    作    者   : f62575
    修改内容   : AT2D08752, W接入方式下，信号较弱时连续发送多条短信会概率性出现发送操作失败；
 22.日    期   : 2009年3月23日
    作    者   : f62575
    修改内容   : AT2D10320, PDU格式写入短信与读出短信内容不是完全一致的；
 23.日    期   : 2009年3月25日
   作    者   : 周君 40661
   修改内容   : 问题单号 AT2D08875,PS优先域发送短信，失败（
 24.日    期   : 2009年4月1日
    作    者   : 周君 40661
    修改内容   : 问题单号:AT2D09786, 用AT+CMGD=,4删除短信时，长时间不回应，导致自动化脚本检测不到单板
 25.日    期   : 2009年4月7日
    作    者   : f62575
    修改内容   : 问题单号 AT2D06392, 不支持短信和状态报告的NV存储相关代码通过宏开关关闭
 26.日    期   : 2009年4月13日
    作    者   : f62575
    修改内容   : 问题单号 AT2D10887
 27.日    期   : 2009-04-22
    作    者   : f62575
    修改内容   : 问题单号:AT2D11256, 打开后台，再插上单板，无法接收到短信。
 28.日    期   : 2009年05月11日
    作    者   : f62575
    修改内容   : 问题单号：AT2D11136，PICS表设置为仅支持SM存储，执行GCF测试用例34.2.5.3，测试用例失败
 29.日    期   : 2009年05月15日
    作    者   : f62575
    修改内容   : 问题单号：AT2D11703，由于勾包过大,申请内存失败,导致单板复位
 30.日    期   : 2009年7月18日
    作    者   : z40661
    修改内容   : 终端可配置需求合入
 31.日    期   : 2009年8月7日
    作    者   : f62575
    修改内容   : MO短信的TP-MR单元填写错误，参考协议9.2.3.6 TP Message Reference
                 (TP MR)应先更新MR后发短信并写SIM卡
 32.日    期   : 2009年08月20日
    作    者   : f62575
    修改内容   : AT2D13875,掉卡时CMGL操作返回与标杆不一致
 33.日    期   : 2009年10月07日
    作    者   : f62575
    修改内容   : AT2D14987,STK短信发送慢问题
 34.日    期   : 2010年3月1日
    作    者   : f62575
    修改内容   : 问题单号: AT2D16941：增加短信功能任意点回放功能
 35.日    期   : 2010年6月30日
    作    者   : 傅映君
    修改内容   : 问题单号DTS2010071500596，STK短信的定制缓存
******************************************************************************/

/*****************************************************************************
  1 头文件包含
*****************************************************************************/

#include "MnMsgInclude.h"
#include "MnMsgCtx.h"
#include "MnMsgProcNvim.h"
#include  "TafCbaCtx.h"
#include  "TafCbaComFunc.h"

#include "TafSdcCtx.h"

#include "MnMsgSendSpm.h"

#ifdef  __cplusplus
  #if  __cplusplus
  extern "C"{
  #endif
#endif


extern VOS_VOID SMS_SetSmsPsConcatenateFlag(NAS_SMS_PS_CONCATENATE_ENUM_UINT8 enFlag);
/*****************************************************************************
  2类型定义
*****************************************************************************/
/*lint -e767 修改人:罗建 107747;检视人:孙少华65952;原因:Log打印*/
#define    THIS_FILE_ID        PS_FILE_ID_MNMSG_REQPROC_C
/*lint +e767 修改人:罗建 107747;检视人:sunshaohua*/

/*直接发送消息和从内存中发送消息的参数结构*/
typedef union
{
    MN_MSG_SEND_PARM_STRU               stSendDirect;
    MN_MSG_SEND_FROMMEM_PARM_STRU       stSendFromMem;
}MSG_APP_REQ_PARM_UNION;

/*lint -save -e958 */

/*****************************************************************************
  3 函数实现
*****************************************************************************/

/*****************************************************************************
 函 数 名  : MSG_BuildRpData
 功能描述  : 根据短信中心地址和TPDU构造RPDU的内容
 输入参数  : pstScAddr      - 短信中心的地址
             pucTpduContent - TPDU的内容
             ulTpduLen      - TPDU的长度
 输出参数  : pucRpduContent - RPDU的内容
             pucRpduLen     - RPDU的长度
             pucTpMr        - 当前的TP-MR的值
 返 回 值  : 无
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2008年2月14日
    作    者   : 周君 40661
    修改内容   : 新生成函数

*****************************************************************************/
LOCAL  VOS_VOID MSG_BuildRpData(
    const MN_MSG_BCD_ADDR_STRU          *pstScAddr,
    const VOS_UINT8                     *pucTpduContent,
    VOS_UINT32                          ulTpduLen,
    VOS_UINT8                           *pucRpduContent,
    VOS_UINT8                           *pucRpduLen,
    VOS_UINT8                           *pucTpMr
)
{
    VOS_UINT8                           ucTpMr;
    MN_MSG_RP_DATA_STRU                 stRpData;

    /*根据24011填写参数内容,7.3.1.2 RP DATA (Mobile Station to Network)*/
    PS_MEM_SET(&stRpData,0X00,sizeof(stRpData));
    stRpData.ucRpMsgType = MN_MSG_RP_MTI_UP_RP_DATA;
    stRpData.stOrgAddr.ucBcdLen = 0;
    PS_MEM_CPY(&stRpData.stDestAddr,pstScAddr,sizeof(MN_MSG_BCD_ADDR_STRU));
    stRpData.ucRpUserDataLen = (VOS_UINT8)ulTpduLen;
    PS_MEM_CPY(stRpData.aucRpUserData,pucTpduContent,ulTpduLen);

    /*重新填写MR的内容*/
    /*协议23040 9.2.3.6 TP Message Reference (TP MR)，下述部分未实现
    The failed message shall be stored in the mobile in such a way that the
    user can request a retransmission using the same TP MR value, without the
    need to re enter any information. Such storage need only be provided for a
    single failed message, i.e. the one most recently attempted.*/
    MN_MSG_AddTpMR();
    MN_MSG_GetTpMR(&ucTpMr);
    stRpData.aucRpUserData[MN_MSG_TPMR_POS] = ucTpMr;
    *pucTpMr = ucTpMr;
    MN_MSG_EncodeRpData(&stRpData,pucRpduContent,pucRpduLen);
}

/*****************************************************************************
 函 数 名  : MSG_BuildRpReport
 功能描述  : 根据发送Ack或Error构造RPDU的内容
 输入参数  : bRpAck         - 是发送RP-Ack还是RP-Error
             enRpCause      - 发送RP-Error时有效,为具体失败的原因值
             pstTsRawData   - TPDU的长度
 输出参数  : pucRpduContent - RPDU的内容
             pucRpduLen     - RPDU的长度
 返 回 值  : 无
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2008年2月14日
    作    者   : 周君 40661
    修改内容   : 新生成函数

*****************************************************************************/
LOCAL  VOS_VOID MSG_BuildRpReport(
    VOS_BOOL                            bRpAck,
    MN_MSG_RP_CAUSE_ENUM_U8             enRpCause,
    const MN_MSG_RAW_TS_DATA_STRU       *pstTsRawData,
    VOS_UINT8                           *pucRpduContent,
    VOS_UINT8                           *pucRpduLen
)
{
    MN_MSG_RP_ACK_STRU                  stRpAck;
    MN_MSG_RP_ERR_STRU                  stRpErr;

    if (VOS_TRUE == bRpAck)
    {
        if (pstTsRawData->ulLen > MN_MSG_MAX_TPDU_LEN)
        {
            MN_WARN_LOG("MSG_BuildRpReport: invalid RP USER data length in RP ACK.");
            return;
        }
        /*根据24011填写参数内容,7.3.3 RP ACK*/
        PS_MEM_SET(&stRpAck,0X00, sizeof(stRpAck));
        stRpAck.ucRpMsgType = MN_MSG_RP_MTI_UP_RP_ACK;
        /*RP User Data*/
        if (pstTsRawData->ulLen > 0)
        {
            stRpAck.bRpUserDataExist = VOS_TRUE;
            stRpAck.ucRpUserDataIei = MN_MSG_RP_USER_DATA_IEI;
            stRpAck.ucRpUserDataLen = (VOS_UINT8)pstTsRawData->ulLen;
            PS_MEM_CPY(stRpAck.aucRpUserData,pstTsRawData->aucData,pstTsRawData->ulLen);
        }
        else
        {
            stRpAck.bRpUserDataExist = VOS_FALSE;
        }
        MN_MSG_EncodeRpAck(&stRpAck,pucRpduContent,pucRpduLen);
    }
    else
    {
        if (pstTsRawData->ulLen > MN_MSG_MAX_TPDU_LEN)
        {
            MN_WARN_LOG("MSG_BuildRpReport: invalid RP USER data length in RP ERROR.");
            return;
        }
        /*根据24011填写参数内容,7.3.4 RP ERROR*/
        PS_MEM_SET(&stRpErr,0X00, sizeof(stRpErr));
        stRpErr.ucRpMsgType = MN_MSG_RP_MTI_UP_RP_ERR;
        /*RP Cause*/
        stRpErr.stRpCause.bDiagnosticsExist = VOS_FALSE;
        stRpErr.ucRpCauseLen = sizeof(MN_MSG_RP_CAUSE_ENUM_U8);
        stRpErr.stRpCause.enRpCause  = enRpCause;
        /*RP User Data*/
        if (pstTsRawData->ulLen > 0)
        {
            stRpErr.bRpUserDataExist = VOS_TRUE;
            stRpErr.ucRpUserDataIei = MN_MSG_RP_USER_DATA_IEI;
            stRpErr.ucRpUserDataLen = (VOS_UINT8)pstTsRawData->ulLen;
            PS_MEM_CPY(stRpErr.aucRpUserData,pstTsRawData->aucData,pstTsRawData->ulLen);
        }
        else
        {
            stRpErr.bRpUserDataExist = VOS_FALSE;
        }
        MN_MSG_EncodeRpErr(&stRpErr,pucRpduContent,pucRpduLen);
    }
}

/*****************************************************************************
 函 数 名  : MSG_ChangeSmStatus
 功能描述  : 读短信或列表短信时,修改短信状态,从未读修改为已读
 输入参数  : enMemStore     - 短信存储器,NVIM或USIM
             clientId       - 发起该请求的Client的ID
             opId           - Operation ID, 标识本次操作
             enAction       - 操作类型,是list还是read
             ulIndex        - 需要修改的短信索引
             pucSmsContent  - 需要修改的短信内容
             pChangeNum     - 已经修改的个数
 输出参数  : pucSmsContent  - 修改后的短信内容
             pChangeNum     - 最新的修改个数
 返 回 值  : 无
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2008年2月14日
    作    者   : 周君 40661
    修改内容   : 新生成函数

*****************************************************************************/
VOS_UINT32  MSG_ChangeSmStatus(
    MN_MSG_MEM_STORE_ENUM_U8            enMemStore,
    MN_CLIENT_ID_T                      clientId,
    MN_OPERATION_ID_T                   opId,
    MN_MSG_USIM_ACTION_ENUM_U8          enAction,
    VOS_UINT32                          ulIndex,
    VOS_UINT8                           *pucSmsContent,
    VOS_UINT8                           *pucChangeNum
)
{
    VOS_UINT32                          ulRet;
#if ((NAS_FEATURE_SMS_NVIM_SMSEXIST == FEATURE_ON) && (NAS_FEATURE_SMS_FLASH_SMSEXIST == FEATURE_ON))
    MN_MSG_WRITE_USIM_INFO_STRU        stWriteUsimInfo;
#else
    MN_MSG_USIM_INFO_STRU               stSmaUsimInfo;
#endif

    VOS_BOOL                            bTimerStart = VOS_FALSE;

    VOS_UINT32                          ulFileId;


    if (TAF_SDC_SIM_TYPE_USIM == TAF_SDC_GetSimType())
    {
        ulFileId    = USIMM_USIM_EFSMS_ID;
    }
    else
    {
        ulFileId    = USIMM_TELE_EFSMS_ID;
    }

    ulRet = MN_MSG_CheckUsimStatus();
    if ((MN_MSG_MEM_STORE_SIM == enMemStore)
     && (MN_ERR_NO_ERROR != ulRet))
    {
        MN_WARN_LOG("MSG_ChangeSmStatus:Usim is not Ready");
        return ulRet;
    }

    *pucSmsContent = EF_SMS_STATUS_MT_READ;

    /* 大于修改的次数,则更新到内存中，等待下次修改 */
    if ( ((*pucChangeNum) >= MN_MSG_MAX_CHG_SM_STATE_NUM)
      && (MN_MSG_MEM_STORE_SIM == enMemStore))
    {
        /* 判断定时器是否启动,如果未启动,则需要启动 */
        bTimerStart = MN_MSG_IsTimerStarting(MN_MSG_TID_WAIT_USIM);
        /*第一次则需要启动定时器等待USIM处理一段时间 */
        if (VOS_FALSE == bTimerStart)
        {
            MN_MSG_StartTimer(MN_MSG_TID_WAIT_USIM,0);
        }
        /* 此时需要先更新内存中的,SIM卡中的稍后更新 */
        MN_MSG_UpdateEachMemSmInfo(ulIndex,pucSmsContent,MN_MSG_EFSMS_LEN);
        MN_MSG_UpdateNeedSendUsim(ulIndex,VOS_TRUE);
        return MN_ERR_SYS_BUSY;
    }

#if ((NAS_FEATURE_SMS_NVIM_SMSEXIST != FEATURE_ON)\
  || (NAS_FEATURE_SMS_FLASH_SMSEXIST != FEATURE_ON))
    PS_MEM_SET(&stSmaUsimInfo,0X00,sizeof(stSmaUsimInfo));
    stSmaUsimInfo.clientId = clientId;
    stSmaUsimInfo.opId = opId;
    stSmaUsimInfo.usEfId = ulFileId;
    stSmaUsimInfo.enDeleteType = MN_MSG_DELETE_MAX;
    stSmaUsimInfo.ucRecIndex = (VOS_UINT8)ulIndex;
    stSmaUsimInfo.enSmaUsimAction = enAction;
    ulRet = MN_MSG_WriteSmsFile(enMemStore,VOS_FALSE,&stSmaUsimInfo,pucSmsContent);
#else
    if (MN_MSG_MEM_STORE_SIM == enMemStore)
    {
        PS_MEM_SET(&stWriteUsimInfo,0X00,sizeof(stWriteUsimInfo));
        stWriteUsimInfo.stUsimInfo.clientId = clientId;
        stWriteUsimInfo.stUsimInfo.opId = opId;
        stWriteUsimInfo.stUsimInfo.usEfId = (VOS_UINT16)ulFileId;
        stWriteUsimInfo.stUsimInfo.enDeleteType = MN_MSG_DELETE_MAX;
        stWriteUsimInfo.stUsimInfo.ucRecIndex = (VOS_UINT8)ulIndex;
        stWriteUsimInfo.stUsimInfo.enSmaUsimAction = enAction;
        stWriteUsimInfo.bCreateNode = VOS_FALSE;
        ulRet = MN_MSG_WriteSmsFile(enMemStore,VOS_NULL_PTR,&stWriteUsimInfo,pucSmsContent);
    }
    else
    {
        ulRet = MN_MSG_WriteSmsFile(enMemStore,&ulIndex,VOS_NULL_PTR,pucSmsContent);
    }
#endif

    if (MN_ERR_NO_ERROR !=ulRet)
    {
        MN_WARN_LOG("MSG_ChangeSmStatus:Write EfSms File Failed");
        if (MN_MSG_MEM_STORE_SIM == enMemStore)
        {
            /* 判断定时器是否启动,如果未启动,则需要启动 */
            bTimerStart = MN_MSG_IsTimerStarting(MN_MSG_TID_WAIT_USIM);
            /*第一次则需要启动定时器等待USIM处理一段时间 */
            if (VOS_FALSE == bTimerStart)
            {
                MN_MSG_StartTimer(MN_MSG_TID_WAIT_USIM,0);
            }
            MN_MSG_UpdateNeedSendUsim(ulIndex,VOS_TRUE);
        }
    }

    return ulRet;
}

/*****************************************************************************
 函 数 名  : MSG_FindDefScAddr
 功能描述  : 获取系统默认的短信中心地址
 输入参数  : 无
 输出参数  : pstScAddr  - 系统默认的短信中心地址
 返 回 值  : VOS_OK:获取成功
             VOS_ERR:获取失败
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2008年2月14日
    作    者   : 周君 40661
    修改内容   : 新生成函数

*****************************************************************************/
LOCAL VOS_UINT32 MSG_FindDefScAddr(
    MN_MSG_BCD_ADDR_STRU                *pstScAddr
)
{
    MN_MSG_SRV_PARAM_STRU                stSrvParm;
    VOS_UINT32                          ulRet;
    VOS_UINT32                          i;
    VOS_UINT8                           ucSrcParmCount;

    ucSrcParmCount = (VOS_UINT8)MN_MSG_GetSmspCapacity(MN_MSG_MEM_STORE_SIM);
    /*优先寻找USIM中的短信中心地址,最开始寻找位置最靠前的短信中心地址*/
    for (i = 0; i < ucSrcParmCount; i++)
    {
        if (VOS_TRUE == MN_MSG_IsEmptySmsp((VOS_UINT8)i))
        {
            continue;
        }

        PS_MEM_SET(&stSrvParm,0X00,sizeof(stSrvParm));
        ulRet = MN_MSG_ReadSmspInfo(MN_MSG_MEM_STORE_SIM,i,&stSrvParm);
        if (MN_ERR_NO_ERROR != ulRet)
        {
            continue;
        }
        /*3GPP 31102:0 Parameter present. 1 Parameter absent*/
        if (MN_MSG_SRV_PARM_ABSENT == ((stSrvParm.ucParmInd & MN_MSG_SRV_PARM_MASK_SC_ADDR) >> 1))
        {
            continue;
        }

        PS_MEM_CPY(pstScAddr,&stSrvParm.stScAddr,sizeof(MN_MSG_BCD_ADDR_STRU));
        break;
    }
    if (i >= ucSrcParmCount)
    {
        /*未能从USIM中获取短信中心地址,从NVIM中获取短信中心地址*/
        ulRet = MN_MSG_ReadSmspInfo(MN_MSG_MEM_STORE_NV,0,&stSrvParm);
        if (MN_ERR_NO_ERROR != ulRet)
        {
            MN_WARN_LOG("MSG_FindDefScAddr:Read NVIM Failed");
            return VOS_ERR;
        }
        /*3GPP 31102:0 Parameter present. 1 Parameter absent*/
        if (MN_MSG_SRV_PARM_ABSENT == ((stSrvParm.ucParmInd & MN_MSG_SRV_PARM_MASK_SC_ADDR) >> 1))
        {
            MN_WARN_LOG("MSG_FindDefScAddr:SC Address is not valid");
            return VOS_ERR;
        }
        PS_MEM_CPY(pstScAddr,&stSrvParm.stScAddr,sizeof(MN_MSG_BCD_ADDR_STRU));
    }
    return VOS_OK;
}

/*****************************************************************************
 函 数 名  : MSG_ParseSendMem
 功能描述  : 根据发送内存短信的输入参数,校验合法性并解析出发送短信的具体参数
 输入参数  : enMsgType       - 发送短信的类型,是直接发送一条短信还是从内存中发送一条短信
             pstSendFromMem  - 发送短信相关参数
 输出参数  : pstMoEntity     - 发送短信的的相关参数
             pucEfSmContent  - 存入USIM中的短信内容
 返 回 值  : MN_ERR_NO_ERROR:解析发送参数成功
             其他:解析发送参数失败
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2008年2月14日
    作    者   : 周君 40661
    修改内容   : 新生成函数
  2.日    期   : 2014年07月07日
    作    者   : z00234330
    修改内容   : coverity清理

*****************************************************************************/
LOCAL VOS_UINT32 MSG_ParseSendMem(
    MN_MSG_MSGTYPE_ENUM_U16             enMsgType,
    const MN_MSG_SEND_FROMMEM_PARM_STRU *pstSendFromMem,
    MN_MSG_MO_ENTITY_STRU               *pstMoEntity,
    VOS_UINT8                           *pucEfSmContent
)
{
    VOS_UINT32                          ulRet;
    MN_MSG_BCD_ADDR_STRU                stScAddr;
    VOS_UINT8                           aucRawData[MN_MSG_MAX_LEN];
    VOS_UINT8                           aucSmContent[MN_MSG_EFSMS_LEN];
    MN_MSG_RAW_TS_DATA_STRU             stRawData;
    VOS_UINT8                           ucStatus;
    MN_MSG_TS_DATA_INFO_STRU            *pstTsData;
    VOS_UINT8                           ucUDLastByte;

    PS_MEM_SET(&stRawData, 0x00, sizeof(stRawData));

    /*检查当前是否有可用域*/
    MN_MSG_GetCurSendDomain(pstSendFromMem->enDomain,
                            &pstMoEntity->enSendDomain);
    if (MN_MSG_SEND_DOMAIN_NO == pstMoEntity->enSendDomain)
    {
        return MN_ERR_CLASS_SMS_NOAVAILDOMAIN;
    }

    /* 记录期望发送域 */
    pstMoEntity->enHopeSendDomain = MN_MSG_GetRealPrefSendDomain(pstMoEntity->enSendDomain,pstSendFromMem->enDomain);
    pstMoEntity->enSaveArea = pstSendFromMem->enMemStore;
    ulRet = MN_MSG_GetStatus(pstMoEntity->enSaveArea,
                             pstSendFromMem->ulIndex,
                             &ucStatus);
    if (MN_ERR_NO_ERROR != ulRet)
    {
        return ulRet;
    }

    if ((EF_SMS_STATUS_MO_TO_BE_SEND != (ucStatus & (0x07)))
     && (EF_SMS_STATUS_MO_SEND_TO_NT != (ucStatus & (0x07))))
    {
        return MN_ERR_CLASS_SMS_INVALID_TPDUTYPE;
    }

    pstMoEntity->ulSaveIndex = pstSendFromMem->ulIndex;
    PS_MEM_SET(aucSmContent,(VOS_CHAR)0xFF,MN_MSG_EFSMS_LEN);
    ulRet = MN_MSG_ReadSmsInfo(pstMoEntity->enSaveArea,
                               pstSendFromMem->ulIndex,
                               aucSmContent);
    if (MN_ERR_NO_ERROR != ulRet)
    {
        return ulRet;
    }

    PS_MEM_SET(&stScAddr,0X00,sizeof(stScAddr));
    ulRet = MN_MSG_ParseEFSmContent(aucSmContent,&stScAddr,&stRawData,&ucStatus);
    if (MN_ERR_NO_ERROR != ulRet)
    {
        return ulRet;
    }
    else
    {
        /*确认将要发送到网络侧的消息能获取到短信中心地址*/
        if (0 == stScAddr.ucBcdLen)
        {
            ulRet = MSG_FindDefScAddr(&stScAddr);
            if (VOS_ERR == ulRet)
            {
                MN_WARN_LOG("MSG_ParseSendMem:No SC address.");
                return MN_ERR_CLASS_SMS_INVALID_SCADDR;
            }
        }
    }

    /*发送短信必须是SUBMIT或COMMAND的类型*/
    if ((MN_MSG_TPDU_SUBMIT != stRawData.enTpduType)
     && (MN_MSG_TPDU_COMMAND != stRawData.enTpduType))
    {
        MN_WARN_LOG("MSG_ParseSendMem:Conflict TPDU type");
        return MN_ERR_CLASS_SMS_INVALID_TPDUTYPE;
    }
    /*解码必须成功*/
    pstTsData = (MN_MSG_TS_DATA_INFO_STRU *)PS_MEM_ALLOC(WUEPS_PID_TAF, sizeof(MN_MSG_TS_DATA_INFO_STRU));
    if (VOS_NULL_PTR == pstTsData)
    {
        return MN_ERR_NOMEM;
    }
    ulRet = MN_MSG_Decode(&stRawData, pstTsData);
    if(MN_ERR_NO_ERROR != ulRet)
    {
        PS_MEM_FREE(WUEPS_PID_TAF,pstTsData);
        return ulRet;
    }
    /*输入了新的目标地址,需要重新构造TPDU*/
    if (MN_MSG_TPDU_SUBMIT == stRawData.enTpduType)
    {
        if (MN_MSG_TPDU_SUBMIT != pstTsData->enTpduType)
        {
            MN_WARN_LOG("MSG_ParseSendMem:Conflict TPDU type");
            PS_MEM_FREE(WUEPS_PID_TAF,pstTsData);
            return MN_ERR_CLASS_SMS_INVALID_TPDUTYPE;
        }

        /*确认将要发送到网络侧的消息体中存在目的地址*/
        if (pstSendFromMem->stDestAddr.ucBcdLen > 0)
        {
            ulRet = MN_MSG_BcdAddrToAscii((MN_MSG_BCD_ADDR_STRU*)&pstSendFromMem->stDestAddr,
                                          &pstTsData->u.stSubmit.stDestAddr);
            if(MN_ERR_NO_ERROR != ulRet)
            {
                MN_WARN_LOG("MSG_ParseSendMem:invalid DA");
                PS_MEM_FREE(WUEPS_PID_TAF,pstTsData);
                return ulRet;
            }

            ucUDLastByte = stRawData.aucData[stRawData.ulLen - 1];
            ulRet = MN_MSG_Encode(pstTsData, &stRawData);
            if(MN_ERR_NO_ERROR != ulRet)
            {
                PS_MEM_FREE(WUEPS_PID_TAF,pstTsData);
                return ulRet;
            }
            stRawData.aucData[stRawData.ulLen - 1] = ucUDLastByte;
        }
        else
        {
            if (0 == pstTsData->u.stSubmit.stDestAddr.ulLen)
            {
                MN_WARN_LOG("MSG_ParseSendMem:No DA");
                PS_MEM_FREE(WUEPS_PID_TAF,pstTsData);
                return MN_ERR_CLASS_SMS_INVALID_DESTADDR;
            }

        }
    }
    else
    {
        if (MN_MSG_TPDU_COMMAND != pstTsData->enTpduType)
        {
            MN_WARN_LOG("MSG_ParseSendMem:Conflict TPDU type");
            PS_MEM_FREE(WUEPS_PID_TAF,pstTsData);
            return MN_ERR_CLASS_SMS_INVALID_TPDUTYPE;
        }
    }

    PS_MEM_FREE(WUEPS_PID_TAF,pstTsData);

    PS_MEM_SET(aucRawData,0X00,MN_MSG_MAX_LEN);
    PS_MEM_CPY(aucRawData,stRawData.aucData,stRawData.ulLen);
    /*构造一条RPDU消息*/
    MSG_BuildRpData(&stScAddr,
                    aucRawData,
                    stRawData.ulLen,
                    pstMoEntity->aucRpDataInfo,
                    &pstMoEntity->ucRpDataLen,
                    &pstMoEntity->ucMr);
    pstMoEntity->enTpduType = stRawData.enTpduType;

    /*构造存在EFSMS的内容*/
    MN_MSG_CreateEFSmContent(&stScAddr,
                             &stRawData,
                             EF_SMS_STATUS_MO_TO_BE_SEND,
                             pucEfSmContent);

    return MN_ERR_NO_ERROR;
}


/*****************************************************************************
 函 数 名  : MSG_ParseSendParm
 功能描述  : 根据发送短信的输入参数,校验合法性并解析出发送短信的具体参数
 输入参数  : enMsgType       - 发送短信的类型,是直接发送一条短信还是从内存中发送一条短信
             pstSendDirect   - 发送短信相关参数
 输出参数  : pstMoEntity     - 发送短信的的相关参数
             pucEfSmContent  - 存入USIM中的短信内容
 返 回 值  : MN_ERR_NO_ERROR:解析发送参数成功
             其他:解析发送参数失败
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2008年2月14日
    作    者   : 周君 40661
    修改内容   : 新生成函数

*****************************************************************************/
LOCAL VOS_UINT32 MSG_ParseSendParm(
    MN_MSG_MSGTYPE_ENUM_U16             enMsgType,
    const MN_MSG_SEND_PARM_STRU         *pstSendDirect,
    MN_MSG_MO_ENTITY_STRU               *pstMoEntity,
    VOS_UINT8                           *pucEfSmContent
)
{
    VOS_UINT32                          ulRet;
    MN_MSG_BCD_ADDR_STRU                stScAddr;
    VOS_UINT8                           aucRawData[MN_MSG_MAX_LEN];

    /*检查当前是否有可用域*/
    MN_MSG_GetCurSendDomain(pstSendDirect->enDomain,
                            &pstMoEntity->enSendDomain);
    if (MN_MSG_SEND_DOMAIN_NO == pstMoEntity->enSendDomain)
    {
        return MN_ERR_CLASS_SMS_NOAVAILDOMAIN;
    }
    /* 记录期望发送域 */
    pstMoEntity->enHopeSendDomain = MN_MSG_GetRealPrefSendDomain(pstMoEntity->enSendDomain,pstSendDirect->enDomain);

    /*检查USIM或NVIM中是否有空闲位置,如果没有空闲位置,则置该短信不保存*/
    pstMoEntity->enSaveArea = pstSendDirect->enMemStore;
#if (NAS_FEATURE_SMS_NVIM_SMSEXIST == FEATURE_ON)
    if ((MN_MSG_MEM_STORE_SIM == pstSendDirect->enMemStore)
     || (MN_MSG_MEM_STORE_NV == pstSendDirect->enMemStore))
#else
    if (MN_MSG_MEM_STORE_SIM == pstSendDirect->enMemStore)
#endif
    {
        pstMoEntity->ulSaveIndex = MN_MSG_GetAvailSmRecIndex(pstMoEntity->enSaveArea);
        if (MN_MSG_NO_AVAILABLE_SMS_REC == pstMoEntity->ulSaveIndex)
        {
            pstMoEntity->enSaveArea = MN_MSG_MEM_STORE_NONE;
        }
    }

    /*填写短信中心地址*/
    PS_MEM_SET(&stScAddr,0X00,sizeof(stScAddr));
    if (pstSendDirect->stMsgInfo.stScAddr.ucBcdLen > 0)
    {
        PS_MEM_CPY(&stScAddr,&pstSendDirect->stMsgInfo.stScAddr,sizeof(MN_MSG_BCD_ADDR_STRU));
    }
    else
    {
        ulRet = MSG_FindDefScAddr(&stScAddr);
        if (VOS_ERR == ulRet)
        {
            return MN_ERR_CLASS_SMS_INVALID_SCADDR;
        }
    }

    PS_MEM_SET(aucRawData,0X00,MN_MSG_MAX_LEN);
    PS_MEM_CPY(aucRawData,
               pstSendDirect->stMsgInfo.stTsRawData.aucData,
               pstSendDirect->stMsgInfo.stTsRawData.ulLen);
    /*重新填写MR的内容, 构造一条RPDU消息*/
    MSG_BuildRpData(&stScAddr,
                    aucRawData,
                    pstSendDirect->stMsgInfo.stTsRawData.ulLen,
                    pstMoEntity->aucRpDataInfo,
                    &pstMoEntity->ucRpDataLen,
                    &pstMoEntity->ucMr);
    pstMoEntity->enTpduType = pstSendDirect->stMsgInfo.stTsRawData.enTpduType;

    /*构造存在EFSMS的内容*/
#if (NAS_FEATURE_SMS_NVIM_SMSEXIST == FEATURE_ON)
    if ((MN_MSG_MEM_STORE_SIM == pstSendDirect->enMemStore)
     || (MN_MSG_MEM_STORE_NV == pstSendDirect->enMemStore))
#else
    if (MN_MSG_MEM_STORE_SIM == pstSendDirect->enMemStore)
#endif
    {
        MN_MSG_CreateEFSmContent(&stScAddr,
                                 &pstSendDirect->stMsgInfo.stTsRawData,
                                 EF_SMS_STATUS_MO_TO_BE_SEND,
                                 pucEfSmContent);

    }

    return MN_ERR_NO_ERROR;
}


/*****************************************************************************
 函 数 名  : MSG_UpdateMemFlag
 功能描述  : 更新APP的内存状态
 输入参数  : MN_MSG_MEM_FLAG_ENUM_U8 enMemFlag  短信内存状态
 输出参数  : 无
 返 回 值  : 无
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2007年10月24日
    作    者   : z40661
    修改内容   : 新生成函数
  2.日    期   : 2012年09月18日
    作    者   : f62575
    修改内容   : STK补充特性及DCM需求开发项目修改入参
*****************************************************************************/
LOCAL VOS_VOID MSG_UpdateMemFlag(MN_MSG_MEM_FLAG_ENUM_U8 enMemFlag)
{
    MN_MSG_SMSS_INFO_STRU               stSmssInfo;
    VOS_UINT32                          ulRet;

    (VOS_VOID)MN_MSG_UpdateAppMemStatus(enMemFlag);
    PS_MEM_SET(&stSmssInfo,0X00,sizeof(stSmssInfo));

    ulRet= MN_MSG_ReadSmssInfo(&stSmssInfo);
    if (VOS_OK == ulRet)
    {
        stSmssInfo.enMemCapExcNotFlag =  enMemFlag;
        MN_MSG_WriteSmssFile(&stSmssInfo);
    }
}

/* Deleted by f62575 for V9R1 STK升级, 2013-6-26, begin */
/* Deleted MN_MSG_ReleaseBufferMsg */
/* Deleted by f62575 for V9R1 STK升级, 2013-6-26, end */

/*****************************************************************************
 函 数 名  : MN_MSG_CheckMoSmsCtrl
 功能描述  : 发送短信流程中的MO SMS CONTROL检查
 输入参数  : MN_MSG_MO_ENTITY_STRU              *pstMoEntity    短信发送信息结构
 输出参数  : VOS_BOOL                           *pCheckMoCtrl   是否检查MO SMS CONTROL
 返 回 值  : VOS_UINT32
                MN_ERR_NO_ERROR                 MO SMS CONTROL检查执行正确
                其他，                          MO SMS CONTROL检查执行失败，需要拒绝用户的短信发送请求
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2012年2月23日
    作    者   : 傅映君/f62575
    修改内容   : 新生成函数
  2.日    期   : 2012年9月20日
    作    者   : f62575
    修改内容   : 2012082906141 解决数据卡STK短信群发失败问题，修改函数命名及返回
*****************************************************************************/
VOS_UINT32 MN_MSG_CheckMoSmsCtrl(
    MN_MSG_MO_ENTITY_STRU              *pstMoEntity,
    VOS_BOOL                           *pbCheckMoCtrl
)
{
    MN_MSG_USIM_EFUST_INFO_STRU         stUstInfo;
    VOS_UINT8                           ucMoSmsCtrlFlag;
    VOS_BOOL                            bBufferEntity;
    VOS_UINT32                          ulIndex;
    MN_MSG_MO_ENTITY_STRU               stMoEntity;
    VOS_UINT32                          ulRet;

    *pbCheckMoCtrl = VOS_FALSE;

    /*开启了SMS Mo Control功能,则需要向USIM发送Envelope命令,并等待USIM的回复*/
    MN_MSG_GetMoSmsCtrlFlag(&ucMoSmsCtrlFlag);
    PS_MEM_SET(&stUstInfo,0X00,sizeof(stUstInfo));
    MN_MSG_ReadUstInfo(&stUstInfo);

    if ((MN_MSG_NVIM_ITEM_ACTIVE != ucMoSmsCtrlFlag)
     || (VOS_TRUE != stUstInfo.bMoSmsCtrlFlag))
    {
        return MN_ERR_NO_ERROR;
    }

    /* 如果当前已经有短信在MN_MSG_MO_STATE_WAIT_SMS_CTRL_RSP 状态则拒绝新短信 */
    ulRet = MN_MSG_GetSpecificStatusMoEntity(MN_MSG_MO_STATE_WAIT_SMS_CTRL_RSP,
                                             &bBufferEntity,
                                             &ulIndex,
                                             &stMoEntity);
    if (MN_ERR_NO_ERROR == ulRet)
    {
        return MN_ERR_CLASS_SMS_MOSTATE;
    }

    *pbCheckMoCtrl = VOS_TRUE;

    return MN_ERR_NO_ERROR;
}

/*****************************************************************************
 函 数 名  : MN_MSG_SendMsgToSms
 功能描述  : 发送短信到SMS模块
             重发流程不做FDN和MO SMS CONTROL检查；
 输入参数  : MN_MSG_MO_ENTITY_STRU              *pstMoEntity    短信发送信息结构
 输出参数  : 无
 返 回 值  : VOS_VOID
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2011年2月17日
    作    者   : 傅映君/f62575
    修改内容   : 新生成函数
  2.日    期   : 2011年6月24日
    作    者   : 傅映君/f62575
    修改内容   : DTS2011062201273 MO SMS CONTROL
  3.日    期   : 2012年2月23日
    作    者   : 傅映君/f62575
    修改内容   : C50_IPC Project 新增FDN检查
  4.日    期   : 2012年12月18日
    作    者   : 傅映君/f62575
    修改内容   : DTS2012121810558, 缓存SMMA消息发送失败
  5.日    期   : 2013年8月3日
    作    者   : z60575
    修改内容   : TQE修改
  6.日    期   : 2013年7月10日
    作    者   : y00245242
    修改内容   : 增加SMS发送路由判断，决定SMS发送给IMS栈还是PS栈
  7.日    期   : 2013年09月24日
    作    者   : s00217060
    修改内容   : VoLTE_PhaseII项目
  8.日    期   : 2015年4月13日
    作    者   : s00217060
    修改内容   : DTS2015041007878:ID_TAF_SPM_MSG_REPORT_IND中的client id不对
                 ，重拨缓存未清除
*****************************************************************************/
VOS_VOID MN_MSG_SendMsgToSms(
    MN_MSG_MO_ENTITY_STRU              *pstMoEntity
)
{
    VOS_UINT32                          ulRet;
    MN_MSG_RETRY_INFO_STRU              stRetryInfo;
    MN_MSG_SENDMSG_EVT_INFO_STRU        stSendMsgEvt;

    ulRet   = VOS_OK;

    MN_NORM_LOG("MN_MSG_SendMsgToSms : send current message.");

    PS_MEM_SET(&stRetryInfo, 0, sizeof(stRetryInfo));

    /* 结束了FDN业务检查和MO SMS CONTROL检查后，MSG发送用户消息到SMS模块 */
    MN_MSG_UpdateSmaMoState(MN_MSG_MO_STATE_WAIT_REPORT_IND);

    /*将一条完整的RP-Data发送给NAS层的SMS模块*/
    if (MN_MSG_MO_TYPE_SMMA == pstMoEntity->enSmsMoType)
    {
        /* Here send SMMA request to SPM module */
        /* Modified by s00217060 for VoLTE_PhaseII  项目, 2013-09-24, begin */
#if (FEATURE_IMS == FEATURE_ON)
        /* 如果IMS宏打开需要到SPM模块做域选择，否则直接走NAS信令 */
        TAF_MSG_SendSpmSmmaInd();
#else
        /* Modified by y00245242 for VoLTE_PhaseI  项目, 2013-7-29, begin */
        ulRet = MN_MSG_SendSmma(pstMoEntity->clientId, pstMoEntity->opId, VOS_FALSE, TAF_MSG_SIGNALLING_TYPE_NAS_SIGNALLING);
        /* Modified by y00245242 for VoLTE_PhaseI  项目, 2013-7-29, end */
#endif
        /* Modified by s00217060 for VoLTE_PhaseII  项目, 2013-09-24, end */
    }
    else
    {
        /* Modified by y00245242 for VoLTE_PhaseI  项目, 2013-7-10, begin */
        ulRet = MN_MSG_SendSmsRpDataReq(pstMoEntity->enSendDomain,
                                        pstMoEntity->aucRpDataInfo,
                                        pstMoEntity->ucRpDataLen,
                                        pstMoEntity->enMsgSignallingType);
        /* Modified by y00245242 for VoLTE_PhaseI  项目, 2013-7-10, end */                                        
    }

    if (VOS_ERR == ulRet)
    {
        MN_WARN_LOG("MN_MSG_SendMsgToSms: send submit or command returns Error");
        MN_MSG_DestroyMoInfo();
        MN_SendClientResponse(pstMoEntity->clientId, pstMoEntity->opId, MN_ERR_CLASS_SMS_INTERNAL);
        return;
    }

    if (MN_MSG_MO_TYPE_SMMA != pstMoEntity->enSmsMoType)
    {
        MN_SendClientResponse(pstMoEntity->clientId, pstMoEntity->opId, MN_ERR_NO_ERROR);
        MN_MSG_GetRetryInfo(&stRetryInfo);

        /* 短信重发周期>0 才需要启动短信重发周期*/
        /* 如果短信在IMS上发送，不需要启动MSG模块的重拨定时器 */
        if ((0 < stRetryInfo.ulRetryPeriod)
        &&  (TAF_MSG_SIGNALLING_TYPE_NAS_SIGNALLING == pstMoEntity->enMsgSignallingType))
        {
            MN_MSG_StartTimer(MN_MSG_ID_WAIT_RETRY_PERIOD,0);
        }

        /*广播上报短信已被发送*/
        PS_MEM_SET(&stSendMsgEvt,0X00,sizeof(stSendMsgEvt));
        stSendMsgEvt.enTpduType = pstMoEntity->enTpduType;
        MN_MSG_ReportSentEvent(pstMoEntity->clientId, pstMoEntity->opId,&stSendMsgEvt,MN_MSG_EVT_MSG_SENT);
    }

    return;
}

/*****************************************************************************
 函 数 名  : MSG_StoreMsgWhenSend
 功能描述  : 发送短信过程中保存短信
 输入参数  : MN_MSG_MSGTYPE_ENUM_U16             enMsgType
             MN_MSG_MO_ENTITY_STRU              *pstMoEntity
             VOS_UINT8                           aucEfSmContent[]
 输出参数  : 无
 返 回 值  : VOS_VOID
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2011年2月17日
    作    者   : 傅映君/f62575
    修改内容   : 新生成函数
  2.日    期   : 2012年8月10日
    作    者   : y00213812
    修改内容   : DTS2012082204471, TQE清理，入参由数据结构改为数据结构指针
*****************************************************************************/
LOCAL VOS_VOID MSG_StoreMsgWhenSend(
    MN_MSG_MSGTYPE_ENUM_U16             enMsgType,
    MN_MSG_MO_ENTITY_STRU              *pstMoEntity,
    VOS_UINT8                           aucEfSmContent[]
)
{
    VOS_UINT32                          ulRet = MN_ERR_NO_ERROR;
    MN_OPERATION_ID_T                   bcOpId;
#if ((NAS_FEATURE_SMS_NVIM_SMSEXIST == FEATURE_ON) && (NAS_FEATURE_SMS_FLASH_SMSEXIST == FEATURE_ON))
    MN_MSG_WRITE_USIM_INFO_STRU         stWriteUsimInfo;
#else
    MN_MSG_USIM_INFO_STRU               stSmaUsimInfo;
#endif
    VOS_UINT32                          ulFileId;

    if (TAF_SDC_SIM_TYPE_USIM == TAF_SDC_GetSimType())
    {
        ulFileId    = USIMM_USIM_EFSMS_ID;
    }
    else
    {
        ulFileId    = USIMM_TELE_EFSMS_ID;
    }

#if (NAS_FEATURE_SMS_NVIM_SMSEXIST == FEATURE_ON)
    if ((MN_MSG_MSGTYPE_SEND_RPDATA_DIRECT == enMsgType)
     && ((MN_MSG_MEM_STORE_SIM == pstMoEntity->enSaveArea)
      || (MN_MSG_MEM_STORE_NV == pstMoEntity->enSaveArea)))
#else
    if ((MN_MSG_MSGTYPE_SEND_RPDATA_DIRECT == enMsgType)
     && (MN_MSG_MEM_STORE_SIM == pstMoEntity->enSaveArea))
#endif
    {
        /*如果发送短信要由NVIM或USIM保存,将未发送的短信存入USIM或NVIM中,状态为To Be Sent*/
#if ((NAS_FEATURE_SMS_NVIM_SMSEXIST != FEATURE_ON)\
          || (NAS_FEATURE_SMS_FLASH_SMSEXIST != FEATURE_ON))
        PS_MEM_SET(&stSmaUsimInfo,0X00,sizeof(stSmaUsimInfo));
        stSmaUsimInfo.clientId = pstMoEntity->clientId;
        stSmaUsimInfo.opId = pstMoEntity->opId;
        stSmaUsimInfo.usEfId = ulFileId;
        stSmaUsimInfo.enDeleteType = MN_MSG_DELETE_MAX;
        stSmaUsimInfo.ucRecIndex = (VOS_UINT8)pstMoEntity.ulSaveIndex;
        stSmaUsimInfo.enSmaUsimAction = MN_MSG_USIM_SEND;
        ulRet = MN_MSG_WriteSmsFile(pstMoEntity->enSaveArea,VOS_FALSE,&stSmaUsimInfo,aucEfSmContent);
#else
        if (MN_MSG_MEM_STORE_SIM == pstMoEntity->enSaveArea)
        {
            PS_MEM_SET(&stWriteUsimInfo,0X00,sizeof(stWriteUsimInfo));
            stWriteUsimInfo.stUsimInfo.clientId = pstMoEntity->clientId;
            stWriteUsimInfo.stUsimInfo.opId = pstMoEntity->opId;
            stWriteUsimInfo.stUsimInfo.usEfId = (VOS_UINT16)ulFileId;
            stWriteUsimInfo.stUsimInfo.enDeleteType = MN_MSG_DELETE_MAX;
            stWriteUsimInfo.stUsimInfo.ucRecIndex = (VOS_UINT8)pstMoEntity->ulSaveIndex;
            stWriteUsimInfo.stUsimInfo.enSmaUsimAction = MN_MSG_USIM_SEND;
            stWriteUsimInfo.bCreateNode = VOS_FALSE;
            ulRet = MN_MSG_WriteSmsFile(pstMoEntity->enSaveArea,VOS_NULL_PTR,&stWriteUsimInfo,aucEfSmContent);

        }
        else
        {
            ulRet = MN_MSG_WriteSmsFile(pstMoEntity->enSaveArea,&(pstMoEntity->ulSaveIndex),VOS_NULL_PTR,aucEfSmContent);
        }
#endif
        if (MN_ERR_NO_ERROR != ulRet)
        {
            /*更新f_stMsgMoEntity中短信存储区域为不存储*/
            MN_MSG_UpdateMoSaveInfo(MN_MSG_MEM_STORE_NONE,0);
            MN_WARN_LOG("MSG_StoreMsgWhenSend: Write Usim Or Nv Failure");
        }
        else if (MN_MSG_MEM_STORE_NV == pstMoEntity->enSaveArea)
        {
            bcOpId = MN_MSG_GetBCopId();
            MN_MSG_ReportSmChanged(pstMoEntity->clientId,bcOpId,VOS_TRUE,MN_MSG_MEM_STORE_NV);
        }
        else
        {
        }
    }

    return;
}

/*****************************************************************************
 函 数 名  : MSG_ConvMsgSendDomain
 功能描述  : 根据需要转换发送域
 输入参数  :
 输出参数  : 无
 返 回 值  : 转换后的发送域
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2009年7月3日
    作    者   : z40661
    修改内容   : 新生成函数
  2.日    期   : 2011年03月01日
    作    者   : A00165503
    修改内容   : 问题单号: DTS2011021202242/DTS2011021400322，添加宏开关判断
                 服务域为PS_ONLY时，CS域短信和呼叫业务是否能够发起
  3.日    期   : 2011年11月3日
    作    者   : f62575
    修改内容   : AT PROJECT 发送域CS ONLY -> CS PREFER,PS ONLY -> PS PREFER的转换在C核实现
                 函数At_ConvMsgSendDomain 移动到C核实现，更名为MSG_ConvMsgSendDomain
  4.日    期   : 2012年03月03日
    作    者   : s62952
    修改内容   : BalongV300R002 Build优化项目
  5.日    期   : 2012年12月10日
    作    者   : f62575
    修改内容   : DTS2012123101285, DCM短信发送网络无响应，要求CM层重传结束后TL层重传至少一次
  6.日    期   : 2015年4月10日
    作    者   : h00313353
    修改内容   : SysCfg重构
*****************************************************************************/
MN_MSG_SEND_DOMAIN_ENUM_U8 MSG_ConvMsgSendDomain(
    MN_MSG_SEND_DOMAIN_ENUM_U8        enCurrDomain
)
{
    VOS_UINT32                          ulRet;
    VOS_UINT8                           ucServiceDomain;
    /* Modified by s62952 for BalongV300R002 Build优化项目 2012-02-28, begin */
    MN_MSG_CUSTOM_CFG_INFO_STRU        *pstCustomCfgAddr;
    VOS_BOOL                            bProtocolSendDomain;

    /* 获取特性控制NV地址 */
    pstCustomCfgAddr                    = MN_MSG_GetCustomCfgInfo();
    /* Modified by s62952 for BalongV300R002 Build优化项目 2012-02-28, end */

    bProtocolSendDomain = MN_MSG_IsProtocolSendDomain();
    ulRet = MN_MSG_MoRetryFlag();
    if ((TAF_TRUE == ulRet)
     && (VOS_FALSE == bProtocolSendDomain))
    {
        if (MN_MSG_NV_ITEM_DEACTIVE == pstCustomCfgAddr->ucPsOnlyCsServiceSupportFlg)
        {
            ucServiceDomain = MN_MMA_GetServiceDomain();
            if (TAF_MMA_SERVICE_DOMAIN_PS == ucServiceDomain)
            {
                if (MN_MSG_SEND_DOMAIN_CS == enCurrDomain)
                {
                    return MN_MSG_SEND_DOMAIN_NO;
                }

                return MN_MSG_SEND_DOMAIN_PS;
            }
        }
        /* Modified by s62952 for BalongV300R002 Build优化项目 2012-02-28, end */

        if ( (MN_MSG_SEND_DOMAIN_PS_PREFERRED == enCurrDomain)
          || (MN_MSG_SEND_DOMAIN_PS == enCurrDomain))
        {
            return MN_MSG_SEND_DOMAIN_PS_PREFERRED;
        }
        return MN_MSG_SEND_DOMAIN_CS_PREFERRED;
    }
    else
    {
        return enCurrDomain;
    }

}

/*****************************************************************************
 函 数 名  : MN_MSG_ProcAppSend
 功能描述  : 处理发送短信请求,包括应用直接发送和从内存中发送
 输入参数  : pstMsgSend     发送短信请求消息
 输出参数  : 无
 返 回 值  : 无
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2007年10月24日
    作    者   : z40661
    修改内容   : 新生成函数
  2.日    期   : 2010年6月30日
    作    者   : 傅映君
    修改内容   : 问题单号DTS2010071500596，STK短信的定制缓存
  3.日    期   : 2011年11月10日
    作    者   : f62575
    修改内容   : DTS2011111004869 支持双核架构下STK模块短信发送请求
  4.日    期   : 2012年8月10日
    作    者   : y00213812
    修改内容   : DTS2012082204471, TQE清理
  5.日    期   : 2012年12月10日
    作    者   : f62575
    修改内容   : DTS2012123101285, DCM短信发送网络无响应，要求CM层重传结束后TL层重传至少一次
  6.日    期   : 2013年6月26日
    作    者   : f62575
    修改内容   : V9R1 STK升级，修改函数入口参数
  7.日    期   : 2013年7月29日
    作    者   : y00245242
    修改内容   : VOLTE开发，增加SMS的信令路由
  8.日    期   : 2013年12月30日                                                    
    作    者   : s00217060                                                         
    修改内容   : VoLTE_PhaseIII项目
*****************************************************************************/
VOS_VOID MN_MSG_ProcAppSend(struct MsgCB * pstMsgSend)
{
    VOS_UINT32                          ulRet = MN_ERR_NO_ERROR;
    VOS_UINT8                           aucEfSmContent[MN_MSG_EFSMS_LEN];
    MN_MSG_MO_ENTITY_STRU               stMoEntity;
    /* Deleted by s00217060 for VoLTE_PhaseIII  项目, 2013-12-30, begin */
    /* Deleted by s00217060 for VoLTE_PhaseIII  项目, 2013-12-30, end */  
    MSG_APP_REQ_PARM_UNION             *punParm;
    VOS_BOOL                            bRequireCheck;
    VOS_BOOL                            bBufferEntity;
    /* Modified by f62575 for V9R1 STK升级, 2013-6-26, begin */
    MN_CLIENT_ID_T                      clientId;
    MN_OPERATION_ID_T                   opId;
    MN_MSG_MSGTYPE_ENUM_U16             enMsgType;
    VOS_VOID                           *pParm = VOS_NULL_PTR;

    MN_INFO_LOG("MN_MSG_ProcAppSend : Step into function.");

    clientId    = ((MN_APP_MSG_SEND_REQ_STRU *)pstMsgSend)->usClientId;
    opId        = ((MN_APP_MSG_SEND_REQ_STRU *)pstMsgSend)->opID;
    enMsgType   = (VOS_UINT16)((MSG_HEADER_STRU *)pstMsgSend)->ulMsgName;
    pParm       = &((MN_APP_MSG_SEND_REQ_STRU *)pstMsgSend)->stMsgSendReq;
    /* Modified by f62575 for V9R1 STK升级, 2013-6-26, end */

    PS_MEM_SET(aucEfSmContent,(VOS_CHAR)0xFF,MN_MSG_EFSMS_LEN);
    PS_MEM_SET(&stMoEntity,0X00,sizeof(stMoEntity));

    punParm = (MSG_APP_REQ_PARM_UNION *)pParm;

    /* Deleted by s00217060 for VoLTE_PhaseIII  项目, 2013-12-30, begin */
    /* 检查当前USIM状态是否可以发送短信上移到SPM */
    /* Deleted by s00217060 for VoLTE_PhaseIII  项目, 2013-12-30, end */

    /*检查当前是否允许MO 功能*/
    ulRet = MN_MSG_MoFeatureAvailable();
    if (MN_ERR_NO_ERROR != ulRet)
    {
        MN_SendClientResponse(clientId,opId, ulRet);
        return;
    }

    /*检查并解析发送参数*/
    if (MN_MSG_MSGTYPE_SEND_RPDATA_DIRECT == enMsgType)
    {
        punParm->stSendDirect.enDomain = MSG_ConvMsgSendDomain(punParm->stSendDirect.enDomain);
        ulRet = MSG_ParseSendParm(enMsgType,&punParm->stSendDirect,&stMoEntity,aucEfSmContent);
        /* Added by y00245242 for VoLTE_PhaseI  项目, 2013-7-10, begin */
        stMoEntity.enMsgSignallingType = punParm->stSendDirect.enMsgSignallingType;
        /* Added by y00245242 for VoLTE_PhaseI  项目, 2013-7-10, end */
    }
    else
    {
        punParm->stSendFromMem.enDomain = MSG_ConvMsgSendDomain(punParm->stSendFromMem.enDomain);
        ulRet = MSG_ParseSendMem(enMsgType,&punParm->stSendFromMem,&stMoEntity,aucEfSmContent);
        /* Added by y00245242 for VoLTE_PhaseI  项目, 2013-7-10, begin */
        stMoEntity.enMsgSignallingType = punParm->stSendFromMem.enMsgSignallingType;
        /* Added by y00245242 for VoLTE_PhaseI  项目, 2013-7-10, end */
    }

    if (MN_ERR_NO_ERROR != ulRet)
    {
        MN_WARN_LOG1("MN_MSG_ProcAppSend : ErrCode ", (VOS_INT32)ulRet);
        MN_SendClientResponse(clientId,opId,ulRet);
        return;
    }
    stMoEntity.clientId = clientId;
    stMoEntity.opId = opId;
    stMoEntity.enSmsMoType = MN_MSG_MO_TYPE_MO;
    stMoEntity.bReportFlag = VOS_TRUE;

    /* 发送短信的本地检查，检查通过则根据注册和短信发送状态确认缓存或发送 */
    ulRet = MN_MSG_CheckMoMsg(aucEfSmContent, &stMoEntity, &bRequireCheck, &bBufferEntity);
    if (MN_ERR_NO_ERROR != ulRet)
    {
        MN_WARN_LOG1("MN_MSG_ProcAppSend : ErrCode ", (VOS_INT32)ulRet);
        MN_SendClientResponse(clientId,opId,ulRet);
        return;
    }

    if ((VOS_TRUE != bRequireCheck)
     && (VOS_TRUE != bBufferEntity))
    {
        MN_MSG_SendMsgToSms(&stMoEntity);
    }

    /*modified by Y00213812 for DTS2012082204471 TQE清理, 2012-08-10, begin*/
    MSG_StoreMsgWhenSend(enMsgType, &stMoEntity, aucEfSmContent);
    /*modified by Y00213812 for DTS2012082204471 TQE清理, 2012-08-10, end*/
    return;
}

/*****************************************************************************
 函 数 名  : MSG_SendAck
 功能描述  : 处理来自应用发送短信报告请求
 输入参数  : clientId       - 发起该请求的Client的ID
             opId           - Operation ID, 标识本次操作
             pstAckParm     - 发送短信报告相关参数
 输出参数  : 无
 返 回 值  : 无
             无
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2007年9月27日
    作    者   : z40661
    修改内容   : 新生成函数
  2.日    期   : 2013年7月29日
    作    者   : y00245242
    修改内容   : VOLTE开发，增加SMS发送底层信令选择项
  3.日    期   :2014年9月28日
    作    者   :s00217060
    修改内容   :for cs_err_log
*****************************************************************************/
LOCAL VOS_VOID MSG_SendAck(
    MN_CLIENT_ID_T                      clientId,
    MN_OPERATION_ID_T                   opId,
    const MN_MSG_SEND_ACK_PARM_STRU     *pstAckParm
)
{
    MN_MSG_MT_STATE_ENUM_U8             enMtState;
    VOS_UINT8                           aucRpContent[MN_MSG_MAX_RPDATA_LEN];
    VOS_UINT8                           ucRpLen = 0;
    VOS_UINT32                          ulRet;
    MN_MSG_SENDMSG_EVT_INFO_STRU        stSendMsgEvt;
    MN_MSG_MEMSTATUS_EVT_INFO_STRU      stMemStatusEvt;
    MN_OPERATION_ID_T                   bcOpId;
/* Added by y00245242 for VoLTE_PhaseI  项目, 2013-7-11, begin */
    TAF_MSG_SIGNALLING_TYPE_ENUM_UINT32 enMsgSignallingType;
/* Added by y00245242 for VoLTE_PhaseI  项目, 2013-7-11, end */
    MN_MSG_RP_CAUSE_ENUM_U8             enCause;

    PS_MEM_SET(&stSendMsgEvt,0X00,sizeof(stSendMsgEvt));
    PS_MEM_SET(&stMemStatusEvt,0X00,sizeof(stMemStatusEvt));

    enMtState = MN_MSG_GetMtState();
    if (MN_MSG_MT_STATE_WAIT_REPORT_REQ != enMtState)
    {
        MN_WARN_LOG("MSG_SendAck : Invalid Mt State");
        MN_SendClientResponse(clientId,opId,MN_ERR_CLASS_SMS_INVALID_MTSTATE);
        return;
    }

    PS_MEM_SET(aucRpContent,0X00,MN_MSG_MAX_RPDATA_LEN);
    /*构造短信Rp-Ack或Rp-Error消息*/
    MSG_BuildRpReport(pstAckParm->bRpAck,
                      pstAckParm->enRpCause,
                      &pstAckParm->stTsRawData,
                      aucRpContent,
                      &ucRpLen);

/* Added by y00245242 for VoLTE_PhaseI  项目, 2013-7-11, begin */ 
    enMsgSignallingType = MN_MSG_GetMtRouteStackType();
/* Added by y00245242 for VoLTE_PhaseI  项目, 2013-7-11, end */

    /*将短信Rp-Ack或Rp-Error发送给NAS层的SMS模块*/
/* Modified by y00245242 for VoLTE_PhaseI  项目, 2013-7-10, begin */
    ulRet = MN_MSG_SendSmsRpReportReq(aucRpContent,ucRpLen, enMsgSignallingType);
/* Modified by y00245242 for VoLTE_PhaseI  项目, 2013-7-10, end */
    if (VOS_OK != ulRet)
    {
        MN_WARN_LOG("MSG_SendAck : Send Msg Failed ");
        MN_SendClientResponse(clientId,opId,MN_ERR_SEND_MSG_ERROR);
        return;
    }

    MN_SendClientResponse(clientId,opId,MN_ERR_NO_ERROR);

    /*删除MT短信相关信息*/
    MN_MSG_DestroyMtInfo();
    if (VOS_TRUE == pstAckParm->bRpAck)
    {
        stSendMsgEvt.enTpduType = MN_MSG_TPDU_DELIVER_RPT_ACK;
    }
    else
    {
        stSendMsgEvt.enTpduType = MN_MSG_TPDU_DELIVER_RPT_ERR;

        enCause = pstAckParm->enRpCause;

        NAS_EventReport(WUEPS_PID_TAF, 
                        NAS_OM_EVENT_SMS_MT_FAIL, 
                        &enCause, 
                        sizeof(MN_MSG_RP_CAUSE_ENUM_U8));
    }
    MN_MSG_ReportSentEvent(clientId,opId,&stSendMsgEvt,MN_MSG_EVT_MSG_SENT);

    /*由于内存中的memflag已经改变,上报memflag已改变*/
    if ((VOS_FALSE == pstAckParm->bRpAck)
     && (MN_MSG_RP_CAUSE_MEMORY_EXCEEDED == pstAckParm->enRpCause))
    {
        MSG_UpdateMemFlag(MN_MSG_MEM_FULL_SET);
        /*上报memflag已改变*/
        stMemStatusEvt.bSuccess = VOS_TRUE;
        stMemStatusEvt.ulFailCause = MN_ERR_NO_ERROR;
        stMemStatusEvt.enMemFlag = MN_MSG_MEM_FULL_SET;
        bcOpId = MN_MSG_GetBCopId();
        MN_MSG_ReportMemStatustEvent(clientId,bcOpId,VOS_TRUE,&stMemStatusEvt,MN_MSG_EVT_MEMSTATUS_CHANGED);
    }
}

/*****************************************************************************
 函 数 名  : MSG_ChkWriteMsg
 功能描述  : 判断短信的状态和短信的TPDU类型是否一致
 输入参数  : clientId       - 发起该请求的Client的ID
             opId           - Operation ID, 标识本次操作
             pstWriteParm   - 写短信相关参数
 输出参数  : 无
 返 回 值  : 无

 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2007年9月27日
    作    者   : z40661
    修改内容   : 新生成函数
*****************************************************************************/
LOCAL VOS_UINT32 MSG_ChkWriteMsg(
    const MN_MSG_WRITE_PARM_STRU        *pstWriteParm
)
{

    if ((MN_MSG_TPDU_SUBMIT == pstWriteParm->stMsgInfo.stTsRawData.enTpduType)
     || (MN_MSG_TPDU_COMMAND == pstWriteParm->stMsgInfo.stTsRawData.enTpduType))
    {
        if ((MN_MSG_STATUS_MO_NOT_SENT != pstWriteParm->enStatus)
         && (MN_MSG_STATUS_MO_SENT != pstWriteParm->enStatus)
         && (MN_MSG_STATUS_NONE != pstWriteParm->enStatus))
        {
            MN_WARN_LOG("MSG_ChkWriteMsg : Not Matched Sm");
            return MN_ERR_CLASS_SMS_INVALID_SMSTATUS;
        }
    }
    else if ((MN_MSG_TPDU_DELIVER == pstWriteParm->stMsgInfo.stTsRawData.enTpduType)
          || (MN_MSG_TPDU_STARPT == pstWriteParm->stMsgInfo.stTsRawData.enTpduType))
    {
        if ((MN_MSG_STATUS_MT_NOT_READ != pstWriteParm->enStatus)
         && (MN_MSG_STATUS_MT_READ != pstWriteParm->enStatus)
         && (MN_MSG_STATUS_NONE != pstWriteParm->enStatus))
        {
            MN_WARN_LOG("MSG_ChkWriteMsg : Not Matched Sm");
            return MN_ERR_CLASS_SMS_INVALID_SMSTATUS;
        }
    }
    else
    {
        MN_WARN_LOG("MSG_ChkWriteMsg : Invalid Tpdu Type");
        return MN_ERR_CLASS_SMS_INVALID_SMSTATUS;

    }

    return MN_ERR_NO_ERROR;
}

/*****************************************************************************
 函 数 名  : MSG_GetMsgRecordStatusForWrite
 功能描述  : 获取短信消息记录的状态
 输入参数  : MN_MSG_STATUS_TYPE_ENUM_U8          enStatus
             MN_MSG_TPDU_TYPE_ENUM_U8            enTpduType
             VOS_UINT8                          *pucStatus
 输出参数  : 无
 返 回 值  : VOS_UINT32
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2011年2月17日
    作    者   : 傅映君/f62575
    修改内容   : 新生成函数

*****************************************************************************/
LOCAL VOS_VOID MSG_GetMsgRecordStatusForWrite(
    MN_MSG_STATUS_TYPE_ENUM_U8          enStatus,
    MN_MSG_TPDU_TYPE_ENUM_U8            enTpduType,
    VOS_UINT8                          *pucStatus
)
{
    if (enStatus == MN_MSG_STATUS_NONE)
    {
        if ((MN_MSG_TPDU_SUBMIT == enTpduType)
         || (MN_MSG_TPDU_COMMAND == enTpduType))
        {
            enStatus = MN_MSG_STATUS_MO_NOT_SENT;
        }
        else
        {
            enStatus = MN_MSG_STATUS_MT_NOT_READ;
        }
    }
    MN_MSG_GetPsStatus(enStatus,pucStatus);

    return;
}

/*****************************************************************************
 函 数 名  : MSG_Write
 功能描述  : 向USIM或NVIM中写一条短信
 输入参数  : clientId       - 发起该请求的Client的ID
             opId           - Operation ID, 标识本次操作
             pstWriteParm   - 写短信相关参数
 输出参数  : 无
 返 回 值  : 无

 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2007年9月27日
    作    者   : z40661
    修改内容   : 新生成函数
  2.日    期   : 2012年12月22日
    作    者   : f62575
    修改内容   : DTS2012122203135, 短信写操作涉及的存储介质满情况，
                 补充^SMMEFULL主动上报，通知应用存储介质溢出
*****************************************************************************/
LOCAL VOS_VOID MSG_Write(
    MN_CLIENT_ID_T                      clientId,
    MN_OPERATION_ID_T                   opId,
    const MN_MSG_WRITE_PARM_STRU        *pstWriteParm
)
{
    MN_OPERATION_ID_T                   bcOpId;
    MN_MSG_BCD_ADDR_STRU                stScAddr;
    VOS_UINT32                          ulRet;
    VOS_UINT32                          ulSaveIndex;
    VOS_UINT8                           ucStatus;
    VOS_UINT8                           aucSmContent[MN_MSG_EFSMS_LEN];
    MN_MSG_WRITE_EVT_INFO_STRU          stWriteEvt;
#if ((NAS_FEATURE_SMS_NVIM_SMSEXIST == FEATURE_ON) && (NAS_FEATURE_SMS_FLASH_SMSEXIST == FEATURE_ON))
    MN_MSG_WRITE_USIM_INFO_STRU         stWriteUsimInfo;
#else
    MN_MSG_USIM_INFO_STRU               stSmaUsimInfo;
#endif
    VOS_UINT32                          ulFileId;

    if (TAF_SDC_SIM_TYPE_USIM == TAF_SDC_GetSimType())
    {
        ulFileId    = USIMM_USIM_EFSMS_ID;
    }
    else
    {
        ulFileId    = USIMM_TELE_EFSMS_ID;
    }

    ulRet = MSG_ChkWriteMsg(pstWriteParm);
    if (MN_ERR_NO_ERROR != ulRet)
    {
        MN_WARN_LOG("MSG_Write : Invalid Tpdu Type");
        MN_SendClientResponse(clientId,opId,ulRet);
        return;
    }

    if (MN_MSG_WRITE_MODE_REPLACE == pstWriteParm->enWriteMode)
    {
        if (VOS_FALSE == MN_MSG_IsValidSmIndex(pstWriteParm->enMemStore, (VOS_UINT8)pstWriteParm->ulIndex))
        {
            MN_WARN_LOG("MSG_Write : Invalid Record");
            MN_SendClientResponse(clientId,opId,MN_ERR_CLASS_SMS_INVALID_REC);
            return;
        }
        ulSaveIndex = (VOS_UINT8)pstWriteParm->ulIndex;
    }
    else
    {
        ulSaveIndex = MN_MSG_GetAvailSmRecIndex(pstWriteParm->enMemStore);
        if (MN_MSG_NO_AVAILABLE_SMS_REC == ulSaveIndex)
        {
            MN_WARN_LOG("MSG_Write : No Empty Sm");
            MN_SendClientResponse(clientId,opId,MN_ERR_CLASS_SMS_STORAGE_FULL);

            bcOpId = MN_MSG_GetBCopId();
            MN_MSG_ReportMemExceed(bcOpId, pstWriteParm->enMemStore);
            return;
        }
    }

    /*获取适当的短信中心*/
    PS_MEM_SET(&stScAddr,0X00,sizeof(stScAddr));
    if (pstWriteParm->stMsgInfo.stScAddr.ucBcdLen > 0)
    {
        PS_MEM_CPY(&stScAddr,&pstWriteParm->stMsgInfo.stScAddr,sizeof(stScAddr));
    }
    else
    {
        ulRet = MSG_FindDefScAddr(&stScAddr);
        if (VOS_ERR == ulRet)
        {
            MN_WARN_LOG("MSG_Write : No SCA.");
        }
    }

    if (MN_MSG_MEM_STORE_SIM == pstWriteParm->enMemStore)
    {
        ulRet = MN_MSG_CheckUsimStatus();
        if (MN_ERR_NO_ERROR != ulRet)
        {
            MN_WARN_LOG1("MSG_Write : ErrCode", (VOS_INT32)ulRet);
            MN_SendClientResponse(clientId,opId,ulRet);
            return;
        }
    }

    MN_SendClientResponse(clientId,opId,MN_ERR_NO_ERROR);

    PS_MEM_SET(aucSmContent,(VOS_CHAR)0xFF,MN_MSG_EFSMS_LEN);

    /*构造一条EFSMS格式的短信并将短信存入存储器*/
    MSG_GetMsgRecordStatusForWrite(pstWriteParm->enStatus,
                     pstWriteParm->stMsgInfo.stTsRawData.enTpduType,
                     &ucStatus);

    MN_MSG_CreateEFSmContent(&stScAddr,
                             &pstWriteParm->stMsgInfo.stTsRawData,
                             ucStatus,
                             aucSmContent);
#if ((NAS_FEATURE_SMS_NVIM_SMSEXIST != FEATURE_ON)\
      || (NAS_FEATURE_SMS_FLASH_SMSEXIST != FEATURE_ON))
    PS_MEM_SET(&stSmaUsimInfo,0X00,sizeof(stSmaUsimInfo));
    stSmaUsimInfo.clientId = clientId;
    stSmaUsimInfo.opId = opId;
    stSmaUsimInfo.usEfId = ulFileId;
    stSmaUsimInfo.enDeleteType = MN_MSG_DELETE_MAX;
    stSmaUsimInfo.ucRecIndex = (VOS_UINT8)ulSaveIndex;
    stSmaUsimInfo.enSmaUsimAction = MN_MSG_USIM_WRITE;
    ulRet = MN_MSG_WriteSmsFile(pstWriteParm->enMemStore,VOS_TRUE,&stSmaUsimInfo,aucSmContent);
#else
    if (MN_MSG_MEM_STORE_SIM == pstWriteParm->enMemStore)
    {
        PS_MEM_SET(&stWriteUsimInfo,0X00,sizeof(stWriteUsimInfo));
        stWriteUsimInfo.stUsimInfo.clientId = clientId;
        stWriteUsimInfo.stUsimInfo.opId = opId;
        stWriteUsimInfo.stUsimInfo.usEfId = (VOS_UINT16)ulFileId;
        stWriteUsimInfo.stUsimInfo.enDeleteType = MN_MSG_DELETE_MAX;
        stWriteUsimInfo.stUsimInfo.ucRecIndex = (VOS_UINT8)ulSaveIndex;
        stWriteUsimInfo.stUsimInfo.enSmaUsimAction = MN_MSG_USIM_WRITE;
        stWriteUsimInfo.bCreateNode = VOS_TRUE;
        ulRet = MN_MSG_WriteSmsFile(pstWriteParm->enMemStore,VOS_NULL_PTR,&stWriteUsimInfo,aucSmContent);

    }
    else
    {
        ulRet = MN_MSG_WriteSmsFile(pstWriteParm->enMemStore,&ulSaveIndex,VOS_NULL_PTR,aucSmContent);
    }
#endif
    PS_MEM_SET(&stWriteEvt,0X00,sizeof(stWriteEvt));
    stWriteEvt.enMemStroe = pstWriteParm->enMemStore;
    stWriteEvt.enStatus =  pstWriteParm->enStatus;
    stWriteEvt.ulIndex = ulSaveIndex;
    if (MN_ERR_NO_ERROR != ulRet)
    {
        /*上报写文件失败*/
        stWriteEvt.bSuccess = VOS_FALSE;
        stWriteEvt.ulFailCause = ulRet;
        MN_MSG_ReportWriteEvent(clientId,opId,&stWriteEvt,MN_MSG_EVT_WRITE);
        return;
    }
#if (NAS_FEATURE_SMS_NVIM_SMSEXIST == FEATURE_ON)
    if (MN_MSG_MEM_STORE_NV == pstWriteParm->enMemStore)
    {
        /*上报写文件成功*/
        stWriteEvt.bSuccess = VOS_TRUE;
        stWriteEvt.ulFailCause = MN_ERR_NO_ERROR;
        MN_MSG_ReportWriteEvent(clientId,opId,&stWriteEvt,MN_MSG_EVT_WRITE);
        /*广播上报NVIM中的短信发生了变化*/
        bcOpId = MN_MSG_GetBCopId();
        MN_MSG_ReportSmChanged(clientId,bcOpId,VOS_TRUE,MN_MSG_MEM_STORE_NV);
    }
#endif
}


/*****************************************************************************
 函 数 名  : MSG_Read
 功能描述  : 从USIM或NVIM中读一条短信
 输入参数  : clientId       - 发起该请求的Client的ID
             opId           - Operation ID, 标识本次操作
             pstRead        - 读取短信相关参数
 输出参数  : 无
 返 回 值  : 无

 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2007年9月27日
    作    者   : z40661
    修改内容   : 新生成函数
  2.日    期   : 2012年12月11日
    作    者   : L00171473
    修改内容   : DTS201212110930, TQE清理
*****************************************************************************/
LOCAL VOS_VOID MSG_Read(
    MN_CLIENT_ID_T                      clientId,
    MN_OPERATION_ID_T                   opId,
    const MN_MSG_READ_PARM_STRU         *pstRead
)
{
    VOS_UINT32                          ulRet;
    VOS_UINT8                           aucSmContent[MN_MSG_EFSMS_LEN];
    MN_MSG_BCD_ADDR_STRU                stScAddr;
    MN_MSG_RAW_TS_DATA_STRU             stRawData;
    VOS_UINT8                           ucStatus;
    MN_MSG_READ_EVT_INFO_STRU           stReadEvt;
    VOS_UINT8                           ucChangeNum = 0;
#if (NAS_FEATURE_SMS_NVIM_SMSEXIST == FEATURE_ON)
    MN_OPERATION_ID_T                   bcOpId;
#endif

    if (MN_MSG_MEM_STORE_SIM == pstRead->enMemStore)
    {
        ulRet = MN_MSG_CheckUsimStatus();
        if (MN_ERR_NO_ERROR != ulRet)
        {
            MN_WARN_LOG1("MSG_Read:ErrCode ", (VOS_INT32)ulRet);
            MN_SendClientResponse(clientId,opId,ulRet);
            return;
        }
    }
#if (NAS_FEATURE_SMS_NVIM_SMSEXIST != FEATURE_ON)
    else
    {
        MN_WARN_LOG1("MSG_Read:pstRead->enMemStore ", (VOS_INT32)pstRead->enMemStore);
        MN_SendClientResponse(clientId,opId,MN_ERR_INVALIDPARM);
        return;
    }
#endif

    PS_MEM_SET(aucSmContent,(VOS_CHAR)0xFF,MN_MSG_EFSMS_LEN);
    PS_MEM_SET(&stReadEvt,0X00,sizeof(stReadEvt));
    PS_MEM_SET(&stScAddr,0X00,sizeof(stScAddr));
    ulRet = MN_MSG_ReadSmsInfo(pstRead->enMemStore,pstRead->ulIndex,aucSmContent);
    if (MN_ERR_NO_ERROR != ulRet)
    {
        MN_WARN_LOG1("MSG_Read : ErrCode ", (VOS_INT32)ulRet);
        MN_SendClientResponse(clientId,opId,ulRet);
        return;
    }


    PS_MEM_SET(&stRawData, 0x00, sizeof(stRawData));

    ulRet = MN_MSG_ParseEFSmContent(aucSmContent,&stScAddr,&stRawData,&ucStatus);
    if (MN_ERR_NO_ERROR != ulRet)
    {
        MN_WARN_LOG1("MSG_Read : ErrCode ", (VOS_INT32)ulRet);
        MN_SendClientResponse(clientId,opId,ulRet);
        return;
    }
    MN_SendClientResponse(clientId,opId,MN_ERR_NO_ERROR);

    MN_MSG_GetAppStatus(ucStatus,&stReadEvt.enStatus);
    PS_MEM_CPY(&stReadEvt.stMsgInfo.stScAddr,&stScAddr,sizeof(MN_MSG_BCD_ADDR_STRU));
    PS_MEM_CPY(&stReadEvt.stMsgInfo.stTsRawData,&stRawData,sizeof(MN_MSG_RAW_TS_DATA_STRU));
    stReadEvt.bSuccess = VOS_TRUE;
    stReadEvt.ulFailCause = MN_ERR_NO_ERROR;
    stReadEvt.enMemStore = pstRead->enMemStore;
    stReadEvt.ulIndex = pstRead->ulIndex;
    MN_MSG_ReportReadEvent(clientId,opId,&stReadEvt,MN_MSG_EVT_READ);

    /*需要改变NVIM或USIM中短信的状态*/
    if ((VOS_TRUE == pstRead->bChangeFlag)
     && (MN_MSG_STATUS_MT_NOT_READ == stReadEvt.enStatus))
    {
        (VOS_VOID)MSG_ChangeSmStatus(pstRead->enMemStore,
                           clientId,
                           opId,
                           MN_MSG_USIM_READ,
                           pstRead->ulIndex,
                           aucSmContent,
                           &ucChangeNum);

#if (NAS_FEATURE_SMS_NVIM_SMSEXIST == FEATURE_ON)
        if (MN_MSG_MEM_STORE_NV == pstRead->enMemStore)
        {
            /*广播上报NVIM中短信已发生了改变*/
            bcOpId = MN_MSG_GetBCopId();
            MN_MSG_ReportSmChanged(clientId,bcOpId,VOS_TRUE,MN_MSG_MEM_STORE_NV);
        }
#endif
    }
}

/*****************************************************************************
 函 数 名  : MSG_CounterListMsg
 功能描述  : 计算从USIM或NVIM中列表某种状态短信的总数
 输入参数  : pstList        - 列表短信相关参数
 输出参数  : 无
 返 回 值  : None

 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2007年9月27日
    作    者   : z40661
    修改内容   : 新生成函数
*****************************************************************************/
LOCAL VOS_UINT32 MSG_CounterListMsg(
    const MN_MSG_LIST_PARM_STRU         *pstList,
    VOS_UINT32                          ulSmCapacity,
    VOS_UINT8                           ucListStatus
)
{
    VOS_UINT32                          i;
    VOS_UINT32                          ulSmReportNum = 0;
    VOS_UINT32                          ulRet;
    VOS_UINT8                           ucStatus;

    for (i = 0; i < ulSmCapacity; i++)
    {
        ulRet = MN_MSG_GetStatus(pstList->enMemStore,i,&ucStatus);
        if (MN_ERR_NO_ERROR != ulRet)
        {
            continue;
        }

        if ((MN_MSG_STATUS_NONE == pstList->enStatus)
         || (ucListStatus == ucStatus))
        {
            ulSmReportNum++;
        }
    }

    return ulSmReportNum;
}

/*****************************************************************************
 函 数 名  : MSG_List
 功能描述  : 从USIM或NVIM中列表某种状态短信
 输入参数  : clientId       - 发起该请求的Client的ID
             opId           - Operation ID, 标识本次操作
             pstList        - 列表短信相关参数
 输出参数  : 无
 返 回 值  : None

 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2007年9月27日
    作    者   : z40661
    修改内容   : 新生成函数

  2.日    期   : 2010年3月15日
    作    者   : zhoujun /z40661
    修改内容   : VOS_TaskDelay清理
  3.日    期   : 2011年1月10日
    作    者   : 傅映君/f62575
    修改内容   : DTS2010010400031 组合AT命令AT+CPMS="SM";+CMGL=4无响应
  4.日    期   : 2013年9月27日
    作    者   : w00167002
    修改内容   : DTS2013092100149:删除C核TASKDELAY处理，在V9低功耗时，会导致
                   TASKDELAY后未被唤醒，导致AT消息没有回复。     
*****************************************************************************/
LOCAL VOS_VOID MSG_List(
    MN_CLIENT_ID_T                      clientId,
    MN_OPERATION_ID_T                   opId,
    const MN_MSG_LIST_PARM_STRU         *pstList
)
{
    VOS_UINT32                          ulSmCapacity;
    VOS_UINT32                          ulSmReportNum = 0;
    VOS_UINT32                          ulRet;
    VOS_UINT8                           ucListStatus = EF_SMS_STATUS_FREE_SPACE;
    MN_MSG_LIST_EVT_INFO_STRU           *pstListEvt;


    /* AT:CMGL请求上报剩余的SMS消息 */
    if ( VOS_FALSE == pstList->ucIsFirstTimeReq)
    {
        TAF_MSG_ListLeftMsg();
        return;
    }

    if (MN_MSG_STATUS_NONE != pstList->enStatus)
    {
        MN_MSG_GetPsStatus(pstList->enStatus, &ucListStatus);
    }

    if (MN_MSG_MEM_STORE_SIM == pstList->enMemStore)
    {
        ulRet = MN_MSG_CheckUsimStatus();
        if (MN_ERR_NO_ERROR != ulRet)
        {
            MN_WARN_LOG1("MSG_List:ErrCode ", (VOS_INT32)ulRet);
            MN_SendClientResponse(clientId,opId,ulRet);
            return;
        }
    }

#if (NAS_FEATURE_SMS_NVIM_SMSEXIST != FEATURE_ON)
    else
    {
        MN_WARN_LOG1("MSG_List:pstList->enMemStore ", (VOS_INT32)pstList->enMemStore);
        MN_SendClientResponse(clientId,opId,MN_ERR_INVALIDPARM);
        return;
    }
#endif

    pstListEvt = (MN_MSG_LIST_EVT_INFO_STRU *)PS_MEM_ALLOC(WUEPS_PID_TAF, sizeof(MN_MSG_LIST_EVT_INFO_STRU));
    if (VOS_NULL_PTR == pstListEvt)
    {
        MN_WARN_LOG("MSG_List :No Mem");
        MN_SendClientResponse(clientId,opId,MN_ERR_NOMEM);
        return;
    }
    else
    {
        pstListEvt->bSuccess = VOS_TRUE;
        pstListEvt->bLastListEvt = VOS_TRUE;

        PS_MEM_CPY( &(pstListEvt->stReceivedListPara), pstList, sizeof(MN_MSG_LIST_PARM_STRU) );
    }

    MN_SendClientResponse(clientId,opId,MN_ERR_NO_ERROR);

    ulSmCapacity = MN_MSG_GetSmCapacity(pstList->enMemStore);

    ulSmReportNum = MSG_CounterListMsg(pstList, ulSmCapacity, ucListStatus);
    if (0 == ulSmReportNum)
    {
        MN_WARN_LOG("MSG_List :No Sm");
        pstListEvt->ulReportNum = ulSmReportNum;
        MN_MSG_ReportListEvent(clientId,opId,pstListEvt,MN_MSG_EVT_LIST);
        PS_MEM_FREE(WUEPS_PID_TAF, pstListEvt);
        return;
    }

    /* 调用函数分段上报需列表个数 */

    pstListEvt->bFirstListEvt = VOS_TRUE;

    MN_MSG_RptMsg(clientId,opId,ulSmReportNum,pstList,pstListEvt);

    PS_MEM_FREE(WUEPS_PID_TAF, pstListEvt);


    return;
}

/*****************************************************************************
 函 数 名  : MSG_DeleteSingleSm
 功能描述  : 删除一条短信记录
 输入参数  : MN_CLIENT_ID_T                      clientId
             MN_OPERATION_ID_T                   opId
             const MN_MSG_DELETE_PARAM_STRU      *pstDeleteParm
 输出参数  : 无
 返 回 值  : VOS_VOID
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2011年2月17日
    作    者   : 傅映君/f62575
    修改内容   : 新生成函数
  2.日    期   : 2013年01月24日
    作    者   : 傅映君/f62575
    修改内容   : DTS2013012403505，短信删除没有清除用户数据

*****************************************************************************/
LOCAL VOS_VOID MSG_DeleteSingleSm(
    MN_CLIENT_ID_T                      clientId,
    MN_OPERATION_ID_T                   opId,
    const MN_MSG_DELETE_PARAM_STRU     *pstDeleteParm
)
{
    VOS_UINT32                          ulRet;
    VOS_UINT8                           aucSmContent[MN_MSG_EFSMS_LEN];
    MN_MSG_DELETE_EVT_INFO_STRU         stDeleteInfo;
#if ((NAS_FEATURE_SMS_NVIM_SMSEXIST == FEATURE_ON) && (NAS_FEATURE_SMS_FLASH_SMSEXIST == FEATURE_ON))
    MN_MSG_WRITE_USIM_INFO_STRU         stWriteUsimInfo;
#else
    MN_MSG_USIM_INFO_STRU               stSmaUsimInfo;
#endif
#if (NAS_FEATURE_SMS_NVIM_SMSEXIST == FEATURE_ON)
    MN_OPERATION_ID_T                   bcOpId;
#endif
    VOS_UINT32                          ulFileId;

    if (TAF_SDC_SIM_TYPE_USIM == TAF_SDC_GetSimType())
    {
        ulFileId    = USIMM_USIM_EFSMS_ID;
    }
    else
    {
        ulFileId    = USIMM_TELE_EFSMS_ID;
    }

    PS_MEM_SET(aucSmContent,0X00,MN_MSG_EFSMS_LEN);
    if (VOS_FALSE == MN_MSG_IsValidSmIndex(pstDeleteParm->enMemStore, (VOS_UINT8)pstDeleteParm->ulIndex))
    {
        MN_WARN_LOG("MSG_DeleteSingleMsg: ErrCode MN_ERR_CLASS_SMS_INVALID_REC");
        MN_SendClientResponse(clientId,opId, MN_ERR_CLASS_SMS_INVALID_REC);
        return;
    }
    ulRet = MN_MSG_ReadSmsInfo(pstDeleteParm->enMemStore,
                               pstDeleteParm->ulIndex,
                               aucSmContent);
    if (MN_ERR_NO_ERROR != ulRet)
    {
        MN_WARN_LOG1("MSG_DeleteSingleMsg: ErrCode ", (VOS_INT32)ulRet);
        MN_SendClientResponse(clientId,opId,ulRet);
        return;
    }
    /*上报应用请求确认*/
    MN_SendClientResponse(clientId,opId,MN_ERR_NO_ERROR);
    PS_MEM_SET(aucSmContent,(VOS_CHAR)0xFF,MN_MSG_EFSMS_LEN);
    aucSmContent[0] = EF_SMS_STATUS_FREE_SPACE;

#if ((NAS_FEATURE_SMS_NVIM_SMSEXIST != FEATURE_ON)\
|| (NAS_FEATURE_SMS_FLASH_SMSEXIST != FEATURE_ON))
    PS_MEM_SET(&stSmaUsimInfo,0X00,sizeof(stSmaUsimInfo));
    stSmaUsimInfo.clientId = clientId;
    stSmaUsimInfo.opId = opId;
    stSmaUsimInfo.usEfId = ulFileId;
    stSmaUsimInfo.enDeleteType = pstDeleteParm->enDeleteType;
    stSmaUsimInfo.ucRecIndex = (VOS_UINT8)pstDeleteParm->ulIndex;
    stSmaUsimInfo.enSmaUsimAction = MN_MSG_USIM_DELETE;
    ulRet = MN_MSG_WriteSmsFile(pstDeleteParm->enMemStore,VOS_TRUE,&stSmaUsimInfo,aucSmContent);
#else
    if (MN_MSG_MEM_STORE_SIM == pstDeleteParm->enMemStore)
    {
        PS_MEM_SET(&stWriteUsimInfo,0X00,sizeof(stWriteUsimInfo));
        stWriteUsimInfo.stUsimInfo.clientId = clientId;
        stWriteUsimInfo.stUsimInfo.opId = opId;
        stWriteUsimInfo.stUsimInfo.usEfId = (VOS_UINT16)ulFileId;
        stWriteUsimInfo.stUsimInfo.enDeleteType = pstDeleteParm->enDeleteType;
        stWriteUsimInfo.stUsimInfo.ucRecIndex = (VOS_UINT8)pstDeleteParm->ulIndex;
        stWriteUsimInfo.stUsimInfo.enSmaUsimAction = MN_MSG_USIM_DELETE;
        stWriteUsimInfo.bCreateNode = VOS_TRUE;
        ulRet = MN_MSG_WriteSmsFile(pstDeleteParm->enMemStore,VOS_NULL_PTR,&stWriteUsimInfo,aucSmContent);

    }
    else
    {
        ulRet = MN_MSG_WriteSmsFile(pstDeleteParm->enMemStore,&(pstDeleteParm->ulIndex),VOS_NULL_PTR,aucSmContent);
    }
#endif

    stDeleteInfo.enDeleteType = pstDeleteParm->enDeleteType;
    stDeleteInfo.enMemStore = pstDeleteParm->enMemStore;
    stDeleteInfo.ulIndex = pstDeleteParm->ulIndex;
#if (NAS_FEATURE_SMS_NVIM_SMSEXIST == FEATURE_ON)
    if (MN_ERR_NO_ERROR != ulRet)
    {
        stDeleteInfo.bSuccess = VOS_FALSE;
        stDeleteInfo.ulFailCause = ulRet;
        MN_MSG_ReportDeleteEvent(clientId,opId,&stDeleteInfo,MN_MSG_EVT_DELETE);
        MN_WARN_LOG1("MSG_Delete: ErrCode ", (VOS_INT32)ulRet);
    }
    else if (MN_MSG_MEM_STORE_NV == pstDeleteParm->enMemStore)
    {
        stDeleteInfo.bSuccess = VOS_TRUE;
        stDeleteInfo.ulFailCause = MN_ERR_NO_ERROR;
        MN_MSG_ReportDeleteEvent(clientId,opId,&stDeleteInfo,MN_MSG_EVT_DELETE);
        /*广播上报NVIM中短信发生了改变*/
        bcOpId = MN_MSG_GetBCopId();
        MN_MSG_ReportSmChanged(clientId,bcOpId,VOS_TRUE,MN_MSG_MEM_STORE_NV);
        /*查看是否需要通知网侧可用内存*/
        MN_MSG_StartMemNotification();
    }
    else
    {
    }
#else
    if (MN_ERR_NO_ERROR != ulRet)
    {
        stDeleteInfo.bSuccess = VOS_FALSE;
        stDeleteInfo.ulFailCause = ulRet;
        MN_MSG_ReportDeleteEvent(clientId,opId,&stDeleteInfo,MN_MSG_EVT_DELETE);
        MN_WARN_LOG1("MSG_Delete: ErrCode ", (VOS_INT32)ulRet);
    }
#endif
}

/*****************************************************************************
 函 数 名  : MSG_Delete
 功能描述  : 从USIM或NVIM中列表删除短信
 输入参数  : clientId       - 发起该请求的Client的ID
             opId           - Operation ID, 标识本次操作
             pstDeleteParm  - 删除短信相关参数
 输出参数  : 无
 返 回 值  : 无

 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2007年9月27日
    作    者   : z40661
    修改内容   : 新生成函数
  2.日    期   : 2008年6月11日
    作    者   : fuyingjun 62575
    修改内容   : 问题单号：AT2D03725, 修改几处删除响应事件已上报标志的使用错误
  2.日    期   : 2013年11月22日
    作    者   : y00245242
    修改内容   : 修改SMS删除时异常响应事件，避免AT命令端口被挂起
*****************************************************************************/
LOCAL VOS_VOID MSG_Delete(
    MN_CLIENT_ID_T                      clientId,
    MN_OPERATION_ID_T                   opId,
    const MN_MSG_DELETE_PARAM_STRU      *pstDeleteParm
)
{
    VOS_UINT32                          ulRet;
    VOS_BOOL                            bDeleteAll = VOS_FALSE;
    VOS_UINT32                          ulDeleteCount = 0;
    MN_MSG_DELETE_EVT_INFO_STRU         stDeleteInfo;
    VOS_UINT32                          ulFileId;
#if (NAS_FEATURE_SMS_NVIM_SMSEXIST == FEATURE_ON)
    MN_OPERATION_ID_T                   bcOpId;
#endif

    ulFileId    = USIMM_DEF_FILEID_BUTT;

    PS_MEM_SET(&stDeleteInfo,0X00,sizeof(stDeleteInfo));
    if (MN_MSG_MEM_STORE_SIM == pstDeleteParm->enMemStore)
    {
        ulRet = MN_MSG_CheckUsimStatus();
        if (MN_ERR_NO_ERROR != ulRet)
        {
            MN_WARN_LOG1("MSG_Delete:ErrCode ", (VOS_INT32)ulRet);

            /* Added by y00245242 for VoLTE_PhaseII 项目, 2013-11-22, begin */
            stDeleteInfo.bSuccess     = VOS_FALSE;
            stDeleteInfo.ulFailCause  = ulRet;
            stDeleteInfo.enDeleteType = pstDeleteParm->enDeleteType;

            MN_MSG_ReportDeleteEvent(clientId, opId, &stDeleteInfo, MN_MSG_EVT_DELETE);
            /* Added by y00245242 for VoLTE_PhaseII 项目, 2013-11-22, end */
            return;
        }

        if (TAF_SDC_SIM_TYPE_USIM == TAF_SDC_GetSimType())
        {
            ulFileId    = USIMM_USIM_EFSMS_ID;
        }
        else
        {
            ulFileId    = USIMM_TELE_EFSMS_ID;
        }

        if (VOS_FALSE == MN_MSG_IsUsimFileExist((VOS_UINT16)ulFileId))
        {
           stDeleteInfo.bSuccess     = VOS_TRUE;
           stDeleteInfo.ulFailCause  = MN_ERR_NO_ERROR;
           /* Added by y00245242 for VoLTE_PhaseII 项目, 2013-11-22, begin */        
           stDeleteInfo.enDeleteType = pstDeleteParm->enDeleteType;
           /* Added by y00245242 for VoLTE_PhaseII 项目, 2013-11-22, end */ 

           MN_MSG_ReportDeleteEvent(clientId,opId,&stDeleteInfo,MN_MSG_EVT_DELETE);
           return;
        }

        MN_MSG_SetDeleteReportFlag(MN_MSG_SET_USIM_DELETE, VOS_FALSE);
    }
#if (NAS_FEATURE_SMS_NVIM_SMSEXIST != FEATURE_ON)
    else
    {
        MN_WARN_LOG1("MSG_Delete: pstDeleteParm->enMemStore ", (VOS_INT32)pstDeleteParm->enMemStore);
        MN_SendClientResponse(clientId,opId,MN_ERR_INVALIDPARM);

        /* Added by y00245242 for VoLTE_PhaseII 项目, 2013-11-22, begin */
        stDeleteInfo.bSuccess     = VOS_FALSE;
        stDeleteInfo.ulFailCause  = MN_ERR_INVALIDPARM;
        stDeleteInfo.enDeleteType = pstDeleteParm->enDeleteType;
                   
        MN_MSG_ReportDeleteEvent(clientId,opId,&stDeleteInfo,MN_MSG_EVT_DELETE);
        /* Added by y00245242 for VoLTE_PhaseII 项目, 2013-11-22, end */        
        
        return;
    }
#endif

    /*删除单条短信*/
    if (MN_MSG_DELETE_SINGLE == pstDeleteParm->enDeleteType)
    {
        MSG_DeleteSingleSm(clientId,opId,pstDeleteParm);
    }
    else
    {
        /*上报应用请求确认*/
        MN_SendClientResponse(clientId,opId,MN_ERR_NO_ERROR);
        MN_MSG_SetUsimRec(MN_MSG_SET_USIM_DELETE_BEGIN,0);
        ulRet = MN_MSG_DeleteMultiSm(clientId,
                                     opId,
                                     pstDeleteParm->enMemStore,
                                     pstDeleteParm->enDeleteType,
                                     &bDeleteAll,
                                     &ulDeleteCount);
        stDeleteInfo.enDeleteType = pstDeleteParm->enDeleteType;
        stDeleteInfo.enMemStore = pstDeleteParm->enMemStore;
        stDeleteInfo.ulIndex = pstDeleteParm->ulIndex;
        if (MN_ERR_NO_ERROR != ulRet)
        {
            /*上报删除短信失败*/
            stDeleteInfo.bSuccess = VOS_FALSE;
            stDeleteInfo.ulFailCause = ulRet;
            MN_MSG_ReportDeleteEvent(clientId,opId,&stDeleteInfo,MN_MSG_EVT_DELETE);
            MN_WARN_LOG1("MSG_Delete: ErrCode ", (VOS_INT32)ulRet);
        }
        else if (VOS_TRUE == bDeleteAll)
        {
            /*所有的都删除完成*/
#if (NAS_FEATURE_SMS_NVIM_SMSEXIST == FEATURE_ON)
            if ((MN_MSG_MEM_STORE_NV == pstDeleteParm->enMemStore)
             || ((MN_MSG_MEM_STORE_SIM == pstDeleteParm->enMemStore)
              && (0 == ulDeleteCount)))
#else
            if ((MN_MSG_MEM_STORE_SIM == pstDeleteParm->enMemStore)
             && (0 == ulDeleteCount))
#endif
            {
                /*上报删除成功*/
                stDeleteInfo.bSuccess = VOS_TRUE;
                stDeleteInfo.ulFailCause = MN_ERR_NO_ERROR;
                MN_MSG_ReportDeleteEvent(clientId,opId,&stDeleteInfo,MN_MSG_EVT_DELETE);
            }
        }
        else
        {        
        }

#if (NAS_FEATURE_SMS_NVIM_SMSEXIST == FEATURE_ON)
        if ((ulDeleteCount > 0)
         && (MN_MSG_MEM_STORE_NV == pstDeleteParm->enMemStore))
        {
            /*广播上报NVIM中短信发生了改变*/
            bcOpId = MN_MSG_GetBCopId();
            MN_MSG_ReportSmChanged(clientId,bcOpId,VOS_TRUE,MN_MSG_MEM_STORE_NV);
            /*查看是否需要通知网侧可用内存*/
            MN_MSG_StartMemNotification();
        }
#endif
    }
}

/*****************************************************************************
 函 数 名  : MSG_Delete_Test
 功能描述  : 从USIM或NVIM中列表删除短信操作的测试命令
 输入参数  : clientId       - 发起该请求的Client的ID
             opId           - Operation ID, 标识本次操作
             enMemStore     - 删除短信测试命令操作的存储介质类型
 输出参数  : 无
 返 回 值  : 无

 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2007年9月27日
    作    者   : z40661
    修改内容   : 新生成函数
  2.日    期   : 2008年6月11日
    作    者   : fuyingjun 62575
    修改内容   : 问题单号：AT2D03725, 修改几处删除响应事件已上报标志的使用错误
  3.日    期   : 2013年07月222日
    作    者   : j00177245
    修改内容   : 清理Coverity
*****************************************************************************/
LOCAL VOS_VOID MSG_Delete_Test(
    MN_CLIENT_ID_T                      clientId,
    MN_OPERATION_ID_T                   opId,
    const MN_MSG_LIST_PARM_STRU         *pstList
)
{
    VOS_UINT32                          i;                                      /* 定义循环变量 */
    VOS_UINT32                          ulRet;
    MN_MSG_DELETE_TEST_EVT_INFO_STRU    stDeleteTestInfo;
    VOS_UINT8                           ucStatus;
    VOS_UINT8                           ucListStatus = EF_SMS_STATUS_FREE_SPACE;
    VOS_UINT32                          ulFileId;

    if (TAF_SDC_SIM_TYPE_USIM == TAF_SDC_GetSimType())
    {
        ulFileId    = USIMM_USIM_EFSMS_ID;
    }
    else
    {
        ulFileId    = USIMM_TELE_EFSMS_ID;
    }

    MN_MSG_GetPsStatus(pstList->enStatus, &ucListStatus);

    PS_MEM_SET(&stDeleteTestInfo, 0x00, sizeof(stDeleteTestInfo));

#if (NAS_FEATURE_SMS_NVIM_SMSEXIST == FEATURE_ON)
    if ( MN_MSG_MEM_STORE_SIM == pstList->enMemStore )
    {
        ulRet = MN_MSG_CheckUsimStatus();
        if (MN_ERR_NO_ERROR != ulRet)
        {
            MN_WARN_LOG1("MSG_Delete_Test:ErrCode ", (VOS_INT32)ulRet);
            MN_SendClientResponse(clientId,opId,ulRet);
            return;
        }

        if (VOS_FALSE == MN_MSG_IsUsimFileExist((VOS_UINT16)ulFileId))
        {
            MN_MSG_ReportDeleteTestEvent(clientId,opId,&stDeleteTestInfo,MN_MSG_EVT_DELETE_TEST);
            return;
        }
    }
#else
    /*如果指定的存储器为USIM*/
    if ( MN_MSG_MEM_STORE_SIM == pstList->enMemStore )
    {
        ulRet = MN_MSG_CheckUsimStatus();
        if (MN_ERR_NO_ERROR != ulRet)
        {
            MN_WARN_LOG1("MSG_Delete_Test:ErrCode ", (VOS_INT32)ulRet);
            MN_SendClientResponse(clientId,opId,ulRet);
            return;
        }

        if (VOS_FALSE == MN_MSG_IsUsimFileExist((VOS_UINT16)ulFileId))
        {
            MN_MSG_ReportDeleteTestEvent(clientId,opId,&stDeleteTestInfo,MN_MSG_EVT_DELETE_TEST);
            return;
        }
    }
    /*如果指定的存储器为NVIM*/
    else
    {
        MN_WARN_LOG("MSG_Delete_Test: invalid storage media");
        MN_SendClientResponse(clientId,opId,MN_ERR_INVALIDPARM);
        return;
    }
#endif

    /*获得满足条件短消息数目的总数*/
    stDeleteTestInfo.ulSmCapacity = MN_MSG_GetSmCapacity(pstList->enMemStore);
    if (stDeleteTestInfo.ulSmCapacity > (MN_MSG_CMGD_PARA_MAX_LEN * 32))
    {
        stDeleteTestInfo.ulSmCapacity = (MN_MSG_CMGD_PARA_MAX_LEN * 32);
    }

    for (i = 0; i < stDeleteTestInfo.ulSmCapacity; i++)
    {
        ulRet = MN_MSG_GetStatus(pstList->enMemStore,i,&ucStatus);
        if (MN_ERR_NO_ERROR != ulRet)
        {
            continue;
        }

        if ((MN_MSG_STATUS_NONE == pstList->enStatus)
         || (ucListStatus == ucStatus))
        {
            MN_SetBitMap(stDeleteTestInfo.aulValidLocMap, i, VOS_FALSE);
        }

    }

    MN_MSG_ReportDeleteTestEvent(clientId,opId,&stDeleteTestInfo,MN_MSG_EVT_DELETE_TEST);
    return;
}

/*****************************************************************************
 函 数 名  : MSG_ReadStaRpt
 功能描述  : 从USIM或NVIM中读一条短信状态报告
 输入参数  : clientId            - 发起该请求的Client的ID
             opId                - Operation ID, 标识本次操作
             pstReadStaRpt       - 短信状态报告相关参数
 输出参数  : 无
 返 回 值  : 无

 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2007年9月27日
    作    者   : z40661
    修改内容   : 新生成函数
*****************************************************************************/
LOCAL VOS_VOID MSG_ReadStaRpt(
    MN_CLIENT_ID_T                      clientId,
    MN_OPERATION_ID_T                   opId,
    const MN_MSG_READ_COMM_PARAM_STRU   *pstReadStaRpt
)
{
    VOS_UINT8                           aucSmsrContent[MN_MSG_EFSMSR_LEN];
    VOS_UINT32                          ulRet = MN_ERR_NO_ERROR;
    MN_MSG_READ_EVT_INFO_STRU           stReadEvt;

    PS_MEM_SET(aucSmsrContent,(VOS_CHAR)0xFF,MN_MSG_EFSMSR_LEN);
    PS_MEM_SET(&stReadEvt,0X00,sizeof(stReadEvt));

    ulRet = MN_MSG_ReadSmsrInfo(pstReadStaRpt->enMemStore,
                                pstReadStaRpt->ulIndex,
                                aucSmsrContent);

    if (MN_ERR_NO_ERROR != ulRet)
    {
        MN_WARN_LOG1("MSG_ReadStaRpt:ErrCode ", (VOS_INT32)ulRet);
        MN_SendClientResponse(clientId,opId, ulRet);
        return;
    }
    MN_SendClientResponse(clientId,opId,ulRet);
    stReadEvt.stMsgInfo.stTsRawData.enTpduType = MN_MSG_TPDU_STARPT;
    stReadEvt.stMsgInfo.stTsRawData.ulLen = MN_MSG_EFSMSR_LEN - 1;
    PS_MEM_CPY(stReadEvt.stMsgInfo.stTsRawData.aucData,aucSmsrContent + 1,MN_MSG_EFSMSR_LEN - 1);
    stReadEvt.bSuccess = VOS_TRUE;
    stReadEvt.ulFailCause = MN_ERR_NO_ERROR;
    stReadEvt.enMemStore = pstReadStaRpt->enMemStore;
    stReadEvt.ulIndex = pstReadStaRpt->ulIndex;
    stReadEvt.enStatus = MN_MSG_STATUS_STARPT;
    MN_MSG_ReportReadEvent(clientId,opId,&stReadEvt,MN_MSG_EVT_READ_STARPT);
    return;
}

/*****************************************************************************
 函 数 名  : MSG_DeleteStaRpt
 功能描述  : 从USIM或NVIM中列表删除短信状态报告
 输入参数  : clientId       - 发起该请求的Client的ID
             opId           - Operation ID, 标识本次操作
             pstDelete      - 删除短信状态报告相关参数
 输出参数  : 无
 返 回 值  : 无

 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2007年9月27日
    作    者   : z40661
    修改内容   : 新生成函数
  2.日    期   : 2008年6月11日
    作    者   : fuyingjun 62575
    修改内容   : 问题单号：AT2D03725, 删除短消息事件响应已上报标志
*****************************************************************************/
LOCAL VOS_VOID MSG_DeleteStaRpt(
    MN_CLIENT_ID_T                      clientId,
    MN_OPERATION_ID_T                   opId,
    const MN_MSG_DELETE_PARAM_STRU      *pstDelete
)
{
    VOS_UINT32                          ulRet;
    VOS_UINT8                           aucSmsrContent[MN_MSG_EFSMSR_LEN];
    VOS_BOOL                            bDeleteAll = VOS_FALSE;
    VOS_UINT8                           ucDeleteCount = 0;
    MN_MSG_DELETE_EVT_INFO_STRU         stDeleteInfo;
    MN_MSG_USIM_INFO_STRU               stSmaUsimInfo;
    /* Modified by s62952 for BalongV300R002 Build优化项目 2012-02-28, begin */
    MN_MSG_CUSTOM_CFG_INFO_STRU        *pstCustomCfgAddr;
    VOS_UINT32                          ulFileId;

    if (TAF_SDC_SIM_TYPE_USIM == TAF_SDC_GetSimType())
    {
        ulFileId    = USIMM_USIM_EFSMSR_ID;
    }
    else
    {
        ulFileId    = USIMM_TELE_EFSMSR_ID;
    }

    /* 获取特性控制NV地址 */
    pstCustomCfgAddr                    = MN_MSG_GetCustomCfgInfo();
    /* Modified by s62952 for BalongV300R002 Build优化项目 2012-02-28, end */


    PS_MEM_SET(aucSmsrContent,(VOS_CHAR)0xFF,MN_MSG_EFSMSR_LEN);
    PS_MEM_SET(&stDeleteInfo,0X00,sizeof(stDeleteInfo));

    /* Modified by s62952 for BalongV300R002 Build优化项目 2012-02-28, begin */
    if (MN_MSG_NV_ITEM_DEACTIVE == pstCustomCfgAddr->ucSmsNvSmsRexitSupportFlg)
    {
        if (MN_MSG_MEM_STORE_SIM == pstDelete->enMemStore)
        {
            ulRet = MN_MSG_CheckUsimStatus();
            if (MN_ERR_NO_ERROR != ulRet)
            {
                MN_WARN_LOG1("MSG_DeleteStaRpt : ErrCode ", (VOS_INT32)ulRet);
                MN_SendClientResponse(clientId,opId,ulRet);
                return;
            }
            if (VOS_FALSE == MN_MSG_IsUsimFileExist((VOS_UINT16)ulFileId))
            {
                MN_WARN_LOG("MSG_DeleteStaRpt : USIMM_USIM_EFSMSR_ID Not Exist");
                MN_SendClientResponse(clientId,opId,MN_ERR_CLASS_SMS_FILE_NOEXIST);
                return;
            }

            MN_MSG_SetDeleteReportFlag(MN_MSG_SET_USIM_DELETE_STARPT, VOS_FALSE);
        }
        else
        {
            MN_WARN_LOG("MSG_DeleteStaRpt : invalid storage type.");
            MN_SendClientResponse(clientId,opId,MN_ERR_INVALIDPARM);
            return;
        }

    }
    /* Modified by s62952 for BalongV300R002 Build优化项目 2012-02-28, end */

    if (MN_MSG_DELETE_SINGLE == pstDelete->enDeleteType)
    {
        ulRet = MN_MSG_ReadSmsrInfo(pstDelete->enMemStore,
                                    pstDelete->ulIndex,
                                    aucSmsrContent);

        if (MN_ERR_NO_ERROR != ulRet)
        {
            MN_WARN_LOG1("MSG_DeleteStaRpt : ErrCode ", (VOS_INT32)ulRet);
            MN_SendClientResponse(clientId,opId,ulRet);
            return;
        }

        MN_SendClientResponse(clientId,opId,MN_ERR_NO_ERROR);
        aucSmsrContent[0] = EF_SMS_STATUS_REPORT_EMPTY;
        PS_MEM_SET(&stSmaUsimInfo,0X00,sizeof(stSmaUsimInfo));
        stSmaUsimInfo.clientId = clientId;
        stSmaUsimInfo.opId = opId;
        stSmaUsimInfo.usEfId = (VOS_UINT16)ulFileId;
        stSmaUsimInfo.enDeleteType = pstDelete->enDeleteType;
        stSmaUsimInfo.ucRecIndex = (VOS_UINT8)pstDelete->ulIndex;
        stSmaUsimInfo.enSmaUsimAction = MN_MSG_USIM_DELETE_STARPT;
        ulRet = MN_MSG_WriteSmsrFile(pstDelete->enMemStore,&stSmaUsimInfo,aucSmsrContent);

        stDeleteInfo.enDeleteType = pstDelete->enDeleteType;
        stDeleteInfo.enMemStore = pstDelete->enMemStore;
        stDeleteInfo.ulIndex = pstDelete->ulIndex;

        /* Modified by s62952 for BalongV300R002 Build优化项目 2012-02-28, begin */
        if (MN_MSG_NV_ITEM_ACTIVE == pstCustomCfgAddr->ucSmsNvSmsRexitSupportFlg)
        {
            if (MN_ERR_NO_ERROR != ulRet)
            {
                stDeleteInfo.bSuccess = VOS_FALSE;
                stDeleteInfo.ulFailCause = ulRet;
                MN_MSG_ReportDeleteEvent(clientId,opId,&stDeleteInfo,MN_MSG_EVT_DELETE_STARPT);
                MN_WARN_LOG("MSG_DeleteStaRpt: Delete Status Report Error");
            }
            else if (MN_MSG_MEM_STORE_NV == pstDelete->enMemStore)
            {
                stDeleteInfo.bSuccess = VOS_TRUE;
                stDeleteInfo.ulFailCause = MN_ERR_NO_ERROR;
                MN_MSG_ReportDeleteEvent(clientId,opId,&stDeleteInfo,MN_MSG_EVT_DELETE_STARPT);
            }
            else
            {
            }
        }
        else
        {
            if (MN_ERR_NO_ERROR != ulRet)
            {
                stDeleteInfo.bSuccess = VOS_FALSE;
                stDeleteInfo.ulFailCause = ulRet;
                MN_MSG_ReportDeleteEvent(clientId,opId,&stDeleteInfo,MN_MSG_EVT_DELETE_STARPT);
                MN_WARN_LOG("MSG_DeleteStaRpt: Delete Status Report Error");
            }
        }
        /* Modified by s62952 for BalongV300R002 Build优化项目 2012-02-28, end */

    }
    else  /*删除所有短信状态报告*/
    {
        MN_SendClientResponse(clientId,opId,MN_ERR_NO_ERROR);
        MN_MSG_SetUsimRec(MN_MSG_SET_USIM_DELETE_STARPT_BEGIN,0);
        ulRet = MN_MSG_DeleteMultiStaRpt(clientId,
                                         opId,
                                         pstDelete->enMemStore,
                                         &bDeleteAll,
                                         &ucDeleteCount);
        stDeleteInfo.enDeleteType = pstDelete->enDeleteType;
        stDeleteInfo.enMemStore = pstDelete->enMemStore;
        stDeleteInfo.ulIndex = pstDelete->ulIndex;
        if (MN_ERR_NO_ERROR != ulRet)
        {
            /*上报删除失败*/
            stDeleteInfo.bSuccess = VOS_FALSE;
            stDeleteInfo.ulFailCause = ulRet;
            MN_MSG_ReportDeleteEvent(clientId,opId,&stDeleteInfo,MN_MSG_EVT_DELETE_STARPT);
        }
        else if (VOS_TRUE == bDeleteAll)
        {
            /*所有的都删除完成*/
#if (NAS_FEATURE_SMS_NVIM_SMSEXIST == FEATURE_ON)
            if ((MN_MSG_MEM_STORE_NV == pstDelete->enMemStore)
             || ((MN_MSG_MEM_STORE_SIM == pstDelete->enMemStore)
              && (0 == ucDeleteCount)))
#else
            if ((MN_MSG_MEM_STORE_SIM == pstDelete->enMemStore)
              && (0 == ucDeleteCount))
#endif
            {
                /*上报删除成功*/
                stDeleteInfo.bSuccess = VOS_TRUE;
                stDeleteInfo.ulFailCause = MN_ERR_NO_ERROR;
                MN_MSG_ReportDeleteEvent(clientId,opId,&stDeleteInfo,MN_MSG_EVT_DELETE_STARPT);
            }
        }
        else
        {
        }
    }
    return;
}

/*****************************************************************************
 函 数 名  : MSG_WriteSrvParm
 功能描述  : 设置短信相关参数,如短信中心，有效期等等
 输入参数  : clientId       - 发起该请求的Client的ID
             opId           - Operation ID, 标识本次操作
             pstSrvParam     - 写入短信相关参数
 输出参数  : 无
 返 回 值  : 无

 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2007年9月27日
    作    者   : z40661
    修改内容   : 新生成函数
*****************************************************************************/
LOCAL VOS_VOID MSG_WriteSrvParm(
    MN_CLIENT_ID_T                      clientId,
    MN_OPERATION_ID_T                   opId,
    const MN_MSG_WRITE_SRV_PARAM_STRU   *pstSrvParam
)
{
    VOS_UINT32                          ulRet;
    MN_MSG_SRV_PARM_EVT_INFO_STRU       stSrvParmEvt;
    VOS_UINT8                           ucSaveIndex = 0;
    MN_MSG_USIM_INFO_STRU               stSmaUsimInfo;
    MN_OPERATION_ID_T                   bcopId;
    MN_MSG_USIM_POWER_STATE_ENUM_U8     enPowerState;
    VOS_UINT32                          ulFileId;

    if (TAF_SDC_SIM_TYPE_USIM == TAF_SDC_GetSimType())
    {
        ulFileId    = USIMM_USIM_EFSMSP_ID;
    }
    else
    {
        ulFileId    = USIMM_TELE_EFSMSP_ID;
    }

    PS_MEM_SET(&stSrvParmEvt,0X00,sizeof(stSrvParmEvt));

    if (MN_MSG_MEM_STORE_SIM == pstSrvParam->enMemStore)
    {
        ulRet = MN_MSG_CheckUsimStatus();
        if (MN_ERR_NO_ERROR != ulRet)
        {
            MN_MSG_GetUsimPowerState(&enPowerState);
            if ((MN_ERR_CLASS_SMS_UPDATE_USIM != ulRet)
             || (enPowerState <= MN_MSG_USIM_POWER_WAIT_EFSMSP))
            {
                MN_WARN_LOG1("MSG_WriteSrvParm : ErrCode ", (VOS_INT32)ulRet);
                MN_SendClientResponse(clientId,opId,ulRet);
                return;
            }

        }

        if (MN_MSG_WRITE_MODE_INSERT == pstSrvParam->enWriteMode)
        {
            ucSaveIndex = MN_MSG_GetAvailSmspRecIndex();
            if (MN_MSG_NO_AVAILABLE_REC == ucSaveIndex)
            {
                MN_WARN_LOG("MSG_WriteSrvParm : No Empty Rec");
                MN_SendClientResponse(clientId,opId,MN_ERR_CLASS_SMS_STORAGE_FULL);
                return;
            }
        }
        else
        {
            if (VOS_FALSE == MN_MSG_IsValidSmspIndex((VOS_UINT8)pstSrvParam->ulIndex))
            {
                MN_WARN_LOG("MSG_WriteSrvParm : Invalid Rec");
                MN_SendClientResponse(clientId,opId,MN_ERR_CLASS_SMS_INVALID_REC);
                return;
            }
            ucSaveIndex = (VOS_UINT8)pstSrvParam->ulIndex;
        }
    }

    MN_SendClientResponse(clientId,opId,MN_ERR_NO_ERROR);

    /*写文件EFSMSP*/
    PS_MEM_SET(&stSmaUsimInfo,0X00,sizeof(stSmaUsimInfo));
    stSmaUsimInfo.clientId = clientId;
    stSmaUsimInfo.opId = opId;
    stSmaUsimInfo.usEfId = (VOS_UINT16)ulFileId;
    stSmaUsimInfo.enDeleteType = MN_MSG_DELETE_MAX;
    stSmaUsimInfo.ucRecIndex = ucSaveIndex;
    stSmaUsimInfo.enSmaUsimAction = MN_MSG_USIM_WRITE_EFSMSP;
    ulRet = MN_MSG_WriteSmspFile(pstSrvParam->enMemStore,
                                 &stSmaUsimInfo,
                                 &(pstSrvParam->stSrvParm));
    stSrvParmEvt.operType = MN_MSG_OPER_SET;
    stSrvParmEvt.ulIndex = ucSaveIndex;
    PS_MEM_CPY(&stSrvParmEvt.stSrvParm,&pstSrvParam->stSrvParm,sizeof(stSrvParmEvt.stSrvParm));
    if (MN_ERR_NO_ERROR != ulRet )
    {
        /*上报设置错误*/
        stSrvParmEvt.bSuccess = VOS_FALSE;
        stSrvParmEvt.ulFailCause = ulRet;
        MN_MSG_ReportSrvParmEvent(clientId,opId,&stSrvParmEvt,MN_MSG_EVT_WRITE_SRV_PARM);
    }
    else if (MN_MSG_MEM_STORE_NV == pstSrvParam->enMemStore)
    {
        /*上报设置成功*/
        stSrvParmEvt.bSuccess = VOS_TRUE;
        stSrvParmEvt.ulFailCause = MN_ERR_NO_ERROR;
        MN_MSG_ReportSrvParmEvent(clientId,opId,&stSrvParmEvt,MN_MSG_EVT_WRITE_SRV_PARM);
        /*广播上报NVIM中的短信参数已发生了改变*/
        bcopId = MN_MSG_GetBCopId();
        MN_MSG_ReportSrvParmChanged(clientId,bcopId,MN_MSG_MEM_STORE_NV);
    }
    else
    {
    }
}

/*****************************************************************************
 函 数 名  : MSG_ReadSrvParm
 功能描述  : 获取短信相关参数,如短信中心，有效期等等
 输入参数  : clientId       - 发起该请求的Client的ID
             opId           - Operation ID, 标识本次操作
             pstReadParm    - 短信服务参数
 输出参数  : 无
 返 回 值  : 无

 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2007年9月27日
    作    者   : z40661
    修改内容   : 新生成函数
*****************************************************************************/
LOCAL VOS_VOID MSG_ReadSrvParm(
    MN_CLIENT_ID_T                      clientId,
    MN_OPERATION_ID_T                   opId,
    const MN_MSG_READ_COMM_PARAM_STRU   *pstReadParm
)
{
    VOS_UINT32                          ulRet;
    MN_MSG_SRV_PARAM_STRU               stSrvParm;
    MN_MSG_SRV_PARM_EVT_INFO_STRU       stSrvParmEvt;

    PS_MEM_SET(&stSrvParm,0X00,sizeof(stSrvParm));
    PS_MEM_SET(&stSrvParmEvt,0X00,sizeof(stSrvParmEvt));
    ulRet = MN_MSG_ReadSmspInfo(pstReadParm->enMemStore,pstReadParm->ulIndex,&stSrvParm);
    if (MN_ERR_NO_ERROR != ulRet)
    {
        MN_WARN_LOG1("MSG_ReadSrvParm : ErrCode ", (VOS_INT32)ulRet);
        MN_SendClientResponse(clientId,opId,ulRet);
        return;
    }

    MN_SendClientResponse(clientId,opId,MN_ERR_NO_ERROR);
    stSrvParmEvt.operType = MN_MSG_OPER_GET;
    stSrvParmEvt.bSuccess = VOS_TRUE;
    stSrvParmEvt.ulFailCause = MN_ERR_NO_ERROR;
    stSrvParmEvt.ulIndex = pstReadParm->ulIndex;
    PS_MEM_CPY(&stSrvParmEvt.stSrvParm,&stSrvParm,sizeof(stSrvParmEvt.stSrvParm));
    MN_MSG_ReportSrvParmEvent(clientId,opId,&stSrvParmEvt,MN_MSG_EVT_READ_SRV_PARM);
    return;
}

/*****************************************************************************
 函 数 名  : MSG_DeleteSrvParm
 功能描述  : 删除短信相关参数,如短信中心，有效期等等
 输入参数  : clientId        - 发起该请求的Client的ID
             opId            - Operation ID, 标识本次操作
             pstDeleteParm   - 删除短信服务参数相关参数
 输出参数  : 无
 返 回 值  : 无

 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2007年9月27日
    作    者   : z40661
    修改内容   : 新生成函数
*****************************************************************************/
LOCAL VOS_VOID MSG_DeleteSrvParm(
    MN_CLIENT_ID_T                      clientId,
    MN_OPERATION_ID_T                   opId,
    const MN_MSG_DELETE_PARAM_STRU       *pstDeleteParm
)
{
    VOS_UINT32                          ulRet;
    MN_MSG_SRV_PARAM_STRU                stSrvParm;
    MN_MSG_DELETE_EVT_INFO_STRU         stDeleteEvt;
    VOS_UINT32                          i;
    VOS_UINT8                           ucSetUsimRec = 0;
    VOS_UINT32                          ulSmspCount = 0;
    MN_MSG_DELETE_EVT_INFO_STRU         stDeleteInfo;
    MN_MSG_USIM_INFO_STRU               stSmaUsimInfo;
    MN_OPERATION_ID_T                   bcopId;
    MN_MSG_USIM_POWER_STATE_ENUM_U8     enPowerState;
    VOS_UINT32                          ulFileId;

    if (TAF_SDC_SIM_TYPE_USIM == TAF_SDC_GetSimType())
    {
        ulFileId    = USIMM_USIM_EFSMSP_ID;
    }
    else
    {
        ulFileId    = USIMM_TELE_EFSMSP_ID;
    }

    PS_MEM_SET(&stSrvParm,0X00,sizeof(stSrvParm));
    PS_MEM_SET(&stDeleteEvt,0X00,sizeof(stDeleteEvt));
    PS_MEM_SET(&stDeleteInfo,0X00,sizeof(stDeleteInfo));

    stDeleteInfo.enDeleteType = pstDeleteParm->enDeleteType;
    stDeleteInfo.enMemStore = pstDeleteParm->enMemStore;
    stDeleteInfo.ulIndex = pstDeleteParm->ulIndex;
    if (MN_MSG_MEM_STORE_SIM == pstDeleteParm->enMemStore)
    {
        ulRet = MN_MSG_CheckUsimStatus();
        if (MN_ERR_NO_ERROR != ulRet)
        {
            MN_MSG_GetUsimPowerState(&enPowerState);
            if ((MN_ERR_CLASS_SMS_UPDATE_USIM != ulRet)
             || (enPowerState <= MN_MSG_USIM_POWER_WAIT_EFSMSP))
            {
                MN_WARN_LOG1("MSG_DeleteSrvParm : ErrCode ", (VOS_INT32)ulRet);
                MN_SendClientResponse(clientId,opId,ulRet);
                return;
            }
        }

        if (VOS_FALSE == MN_MSG_IsUsimFileExist((VOS_UINT16)ulFileId))
        {
            MN_WARN_LOG("MSG_DeleteSrvParm : USIMM_USIM_EFSMSP_ID Not Exist");
            MN_SendClientResponse(clientId,opId,MN_ERR_CLASS_SMS_FILE_NOEXIST);
            return;
        }

        MN_MSG_SetDeleteReportFlag(MN_MSG_SET_USIM_DELETE_EFSMSP, VOS_FALSE);

        if (MN_MSG_DELETE_SINGLE == pstDeleteParm->enDeleteType)
        {
            if (VOS_FALSE == MN_MSG_IsValidSmspIndex((VOS_UINT8)pstDeleteParm->ulIndex))
            {
                MN_WARN_LOG("MSG_DeleteSrvParm : Invalid Rec");
                MN_SendClientResponse(clientId,opId,MN_ERR_CLASS_SMS_INVALID_REC);
                return;
            }
            if (VOS_TRUE == MN_MSG_IsEmptySmsp((VOS_UINT8)pstDeleteParm->ulIndex))
            {
                MN_WARN_LOG("MSG_DeleteSrvParm : EMPTY Rec");
                MN_SendClientResponse(clientId,opId,MN_ERR_CLASS_SMS_INVALID_REC);
                return;
            }
            MN_SendClientResponse(clientId,opId,MN_ERR_NO_ERROR);
            /*设置所有的参数指示都无效*/
            stSrvParm.ucParmInd = MN_MSG_SRV_PARM_TOTALABSENT;
            PS_MEM_SET(&stSmaUsimInfo,0X00,sizeof(stSmaUsimInfo));
            stSmaUsimInfo.clientId = clientId;
            stSmaUsimInfo.opId = opId;
            stSmaUsimInfo.usEfId = (VOS_UINT16)ulFileId;
            stSmaUsimInfo.enDeleteType = pstDeleteParm->enDeleteType;
            stSmaUsimInfo.ucRecIndex = (VOS_UINT8)pstDeleteParm->ulIndex;
            stSmaUsimInfo.enSmaUsimAction = MN_MSG_USIM_DELETE_EFSMSP;
            ulRet = MN_MSG_WriteSmspFile(MN_MSG_MEM_STORE_SIM,&stSmaUsimInfo,&stSrvParm);
            if (MN_ERR_NO_ERROR != ulRet)
            {
                /*上报删除失败*/
                stDeleteInfo.bSuccess = VOS_FALSE;
                stDeleteInfo.ulFailCause = ulRet;
                MN_MSG_ReportDeleteEvent(clientId,opId,&stDeleteInfo,MN_MSG_EVT_DELETE_SRV_PARM);
            }
        }
        else
        {
            MN_SendClientResponse(clientId,opId,MN_ERR_NO_ERROR);
            ulSmspCount = MN_MSG_GetSmspCapacity(MN_MSG_MEM_STORE_SIM);
            if (MN_MSG_FILE_NONE_REC == ulSmspCount)
            {
                /*上报删除失败*/
                stDeleteInfo.bSuccess = VOS_FALSE;
                stDeleteInfo.ulFailCause = MN_ERR_INVALIDPARM;
                MN_MSG_ReportDeleteEvent(clientId,opId,&stDeleteInfo,MN_MSG_EVT_DELETE_SRV_PARM);
                return;
            }
            for (i = 0; i < ulSmspCount; i++)
            {
                if (VOS_TRUE == MN_MSG_IsEmptySmsp((VOS_UINT8)i))
                {
                    continue;
                }
                stSrvParm.ucParmInd = MN_MSG_SRV_PARM_TOTALABSENT;
                PS_MEM_SET(&stSmaUsimInfo,0X00,sizeof(stSmaUsimInfo));
                stSmaUsimInfo.clientId = clientId;
                stSmaUsimInfo.opId = opId;
                stSmaUsimInfo.usEfId = (VOS_UINT16)ulFileId;
                stSmaUsimInfo.enDeleteType = pstDeleteParm->enDeleteType;
                stSmaUsimInfo.ucRecIndex = (VOS_UINT8)i;
                stSmaUsimInfo.enSmaUsimAction = MN_MSG_USIM_DELETE_EFSMSP;
                ulRet = MN_MSG_WriteSmspFile(MN_MSG_MEM_STORE_SIM,&stSmaUsimInfo,&stSrvParm);
                if (MN_ERR_NO_ERROR != ulRet)
                {
                    /*上报删除失败*/
                    stDeleteInfo.bSuccess = VOS_FALSE;
                    stDeleteInfo.ulFailCause = ulRet;
                    MN_MSG_ReportDeleteEvent(clientId,opId,&stDeleteInfo,MN_MSG_EVT_DELETE_SRV_PARM);
                    break;
                }
                ucSetUsimRec++;
            }
        }
        if (ucSetUsimRec > 0)
        {
            MN_MSG_SetUsimRec(MN_MSG_SET_USIM_DELETE_EFSMSP,ucSetUsimRec);
        }
    }
    else
    {
        MN_SendClientResponse(clientId,opId,MN_ERR_NO_ERROR);
        /*设置所有的参数指示都无效*/
        stSrvParm.ucParmInd = MN_MSG_SRV_PARM_TOTALABSENT;
        PS_MEM_SET(&stSmaUsimInfo,0X00,sizeof(stSmaUsimInfo));
        ulRet = MN_MSG_WriteSmspFile(MN_MSG_MEM_STORE_NV,&stSmaUsimInfo,&stSrvParm);
        if (MN_ERR_NO_ERROR == ulRet)
        {
            /*上报删除成功*/
            stDeleteInfo.bSuccess = VOS_TRUE;
            stDeleteInfo.ulFailCause = MN_ERR_NO_ERROR;
            MN_MSG_ReportDeleteEvent(clientId,opId,&stDeleteInfo,MN_MSG_EVT_DELETE_SRV_PARM);
            /*上报NVIM的短信参数发生了变化*/
            bcopId = MN_MSG_GetBCopId();
            MN_MSG_ReportSrvParmChanged(clientId,bcopId,MN_MSG_MEM_STORE_NV);
        }
        else
        {
            /*上报删除失败*/
            stDeleteInfo.bSuccess = VOS_FALSE;
            stDeleteInfo.ulFailCause = ulRet;
            MN_MSG_ReportDeleteEvent(clientId,opId,&stDeleteInfo,MN_MSG_EVT_DELETE_SRV_PARM);
        }
    }
}

/*****************************************************************************
 函 数 名  : MSG_CheckTpduStatusAndStatus
 功能描述  : 检查TPDU记录类型和状态的一致性，仅要更新的状态与TPDU类型一致才能作修改操作
 输入参数  : MN_MSG_STATUS_TYPE_ENUM_U8          enStatus
             MN_MSG_TPDU_TYPE_ENUM_U8            enTpduType
 输出参数  : 无
 返 回 值  : LOCAL
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2011年2月17日
    作    者   : 傅映君/f62575
    修改内容   : 新生成函数

*****************************************************************************/
LOCAL VOS_UINT32 MSG_CheckTpduTypeAndStatus(
    MN_MSG_STATUS_TYPE_ENUM_U8          enStatus,
    MN_MSG_TPDU_TYPE_ENUM_U8            enTpduType
)
{
    /*短信状态和TPDU类型必须一致才能允许修改*/
    if ((MN_MSG_STATUS_MT_NOT_READ == enStatus)
     || (MN_MSG_STATUS_MT_READ == enStatus))
    {
        if (MN_MSG_TPDU_DELIVER != enTpduType)
        {
            MN_WARN_LOG("MSG_CheckTpduTypeAndStatus: Invalid Tpdu Type");
            return MN_ERR_CLASS_SMS_INVALID_TPDUTYPE;
        }
    }
    else if ((MN_MSG_STATUS_MO_NOT_SENT == enStatus)
          || (MN_MSG_STATUS_MO_SENT == enStatus))
    {
        if ((MN_MSG_TPDU_SUBMIT != enTpduType)
         && (MN_MSG_TPDU_COMMAND != enTpduType))
        {
            MN_WARN_LOG("MSG_CheckTpduTypeAndStatus: Invalid Tpdu Type");
            return MN_ERR_CLASS_SMS_INVALID_TPDUTYPE;
        }
    }
    else
    {
        MN_WARN_LOG("MSG_CheckTpduTypeAndStatus: Invalid SM State");
        return MN_ERR_INVALIDPARM;
    }

    return MN_ERR_NO_ERROR;
}

/*****************************************************************************
 函 数 名  : MSG_ModifyStatus
 功能描述  : 修改短信状态
 输入参数  : clientId            - 发起该请求的Client的ID
             opId                - Operation ID, 标识本次操作
             pstModifyParm       - 修改短信状态相关参数
 输出参数  : 无
 返 回 值  : 无

 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2007年9月27日
    作    者   : z40661
    修改内容   : 新生成函数
*****************************************************************************/
LOCAL VOS_VOID MSG_ModifyStatus(
    MN_CLIENT_ID_T                       clientId,
    MN_OPERATION_ID_T                    opId,
    const MN_MSG_MODIFY_STATUS_PARM_STRU *pstModifyParm
)
{
    VOS_UINT32                          ulRet;
    VOS_UINT8                           aucSmContent[MN_MSG_EFSMS_LEN];
    MN_MSG_BCD_ADDR_STRU                stScAddr;
    MN_MSG_RAW_TS_DATA_STRU             stRawData;
    VOS_UINT8                           ucStatus;
    VOS_UINT8                           ucHopeStatus;
    MN_MSG_MODIFY_STATUS_EVT_INFO_STRU  stModifyStatusEvt;
#if ((NAS_FEATURE_SMS_NVIM_SMSEXIST == FEATURE_ON) && (NAS_FEATURE_SMS_FLASH_SMSEXIST == FEATURE_ON))
    MN_MSG_WRITE_USIM_INFO_STRU         stWriteUsimInfo;
#else
    MN_MSG_USIM_INFO_STRU               stSmaUsimInfo;
#endif
#if (NAS_FEATURE_SMS_NVIM_SMSEXIST == FEATURE_ON)
    MN_OPERATION_ID_T                   bcOpId;
#endif
    VOS_UINT32                          ulFileId;

    if (TAF_SDC_SIM_TYPE_USIM == TAF_SDC_GetSimType())
    {
        ulFileId    = USIMM_USIM_EFSMS_ID;
    }
    else
    {
        ulFileId    = USIMM_TELE_EFSMS_ID;
    }

    PS_MEM_SET(aucSmContent,(VOS_CHAR)0xFF,MN_MSG_EFSMS_LEN);
    PS_MEM_SET(&stScAddr,0x00,sizeof(stScAddr));
    PS_MEM_SET(&stRawData,0x00,sizeof(stRawData));
    PS_MEM_SET(&stModifyStatusEvt,0x00,sizeof(stModifyStatusEvt));

    if (MN_MSG_MEM_STORE_SIM == pstModifyParm->enMemStore)
    {
        ulRet = MN_MSG_CheckUsimStatus();
        if (MN_ERR_NO_ERROR != ulRet)
        {
            MN_WARN_LOG1("MSG_ModifyStatus:ErrCode ", (VOS_INT32)ulRet);
            MN_SendClientResponse(clientId,opId,ulRet);
            return;
        }
    }
#if (NAS_FEATURE_SMS_NVIM_SMSEXIST != FEATURE_ON)
    else
    {
        MN_WARN_LOG1("MSG_ModifyStatus: enMemStore is ", pstModifyParm->enMemStore);
        MN_SendClientResponse(clientId, opId, MN_ERR_INVALIDPARM);
        return;
    }
#endif

    ulRet = MN_MSG_ReadSmsInfo(pstModifyParm->enMemStore,pstModifyParm->ulIndex,aucSmContent);
    if (MN_ERR_NO_ERROR != ulRet)
    {
        MN_WARN_LOG1("MSG_ModifyStatus:ErrCode ", (VOS_INT32)ulRet);
        MN_SendClientResponse(clientId,opId,ulRet);
        return;
    }

    ulRet = MN_MSG_ParseEFSmContent(aucSmContent,&stScAddr,&stRawData,&ucStatus);
    if (MN_ERR_NO_ERROR != ulRet)
    {
        MN_WARN_LOG1("MSG_ModifyStatus:ErrCode ", (VOS_INT32)ulRet);
        MN_SendClientResponse(clientId,opId,ulRet);
        return;
    }

    ulRet = MSG_CheckTpduTypeAndStatus(pstModifyParm->enStatus,
                                       stRawData.enTpduType);
    if (MN_ERR_NO_ERROR != ulRet)
    {
        MN_WARN_LOG("MSG_ModifyStatus: Invalid Parameter");
        MN_SendClientResponse(clientId,opId,ulRet);
        return;
    }

    MN_SendClientResponse(clientId,opId,MN_ERR_NO_ERROR);
    stModifyStatusEvt.enMemStore = pstModifyParm->enMemStore;
    stModifyStatusEvt.enStatus = pstModifyParm->enStatus;
    stModifyStatusEvt.ulIndex = pstModifyParm->ulIndex;
    MN_MSG_GetPsStatus(pstModifyParm->enStatus,&ucHopeStatus);
    if (ucHopeStatus == ucStatus)
    {
        stModifyStatusEvt.bSuccess = VOS_TRUE;
        stModifyStatusEvt.ulFailCause = MN_ERR_NO_ERROR;
        MN_MSG_ReportModifyEvent(clientId,opId,&stModifyStatusEvt,MN_MSG_EVT_MODIFY_STATUS);
        return;
    }

    aucSmContent[0] =  ucHopeStatus;

#if ((NAS_FEATURE_SMS_FLASH_SMSEXIST == FEATURE_ON)\
  && (NAS_FEATURE_SMS_NVIM_SMSEXIST == FEATURE_ON))
    if (MN_MSG_MEM_STORE_SIM == pstModifyParm->enMemStore)
    {
        PS_MEM_SET(&stWriteUsimInfo,0X00,sizeof(stWriteUsimInfo));
        stWriteUsimInfo.stUsimInfo.clientId = clientId;
        stWriteUsimInfo.stUsimInfo.opId = opId;
        stWriteUsimInfo.stUsimInfo.usEfId = (VOS_UINT16)ulFileId;
        stWriteUsimInfo.stUsimInfo.enDeleteType = MN_MSG_DELETE_MAX;
        stWriteUsimInfo.stUsimInfo.ucRecIndex = (VOS_UINT8)pstModifyParm->ulIndex;
        stWriteUsimInfo.stUsimInfo.enSmaUsimAction = MN_MSG_USIM_MODIFYSTATUS;
        stWriteUsimInfo.bCreateNode = VOS_TRUE;
        ulRet = MN_MSG_WriteSmsFile(pstModifyParm->enMemStore,VOS_NULL_PTR,&stWriteUsimInfo,aucSmContent);

    }
    else
    {
        ulRet = MN_MSG_WriteSmsFile(pstModifyParm->enMemStore,&(pstModifyParm->ulIndex),VOS_NULL_PTR,aucSmContent);
    }
#else
    PS_MEM_SET(&stSmaUsimInfo,0X00,sizeof(stSmaUsimInfo));
    stSmaUsimInfo.clientId = clientId;
    stSmaUsimInfo.opId = opId;
    stSmaUsimInfo.usEfId = ulFileId;
    stSmaUsimInfo.enDeleteType = MN_MSG_DELETE_MAX;
    stSmaUsimInfo.ucRecIndex = (VOS_UINT8)pstModifyParm->ulIndex;
    stSmaUsimInfo.enSmaUsimAction = MN_MSG_USIM_MODIFYSTATUS;
    ulRet = MN_MSG_WriteSmsFile(pstModifyParm->enMemStore,VOS_TRUE,&stSmaUsimInfo,aucSmContent);

#endif

#if (NAS_FEATURE_SMS_NVIM_SMSEXIST == FEATURE_ON)
    if (MN_ERR_NO_ERROR != ulRet)
    {
        /*上报修改失败*/
        stModifyStatusEvt.bSuccess = VOS_FALSE;
        stModifyStatusEvt.ulFailCause = ulRet;
        MN_MSG_ReportModifyEvent(clientId,opId,&stModifyStatusEvt,MN_MSG_EVT_MODIFY_STATUS);
        MN_WARN_LOG("MSG_ModifyStatus: Write SM Error");
    }
    else if (MN_MSG_MEM_STORE_NV == pstModifyParm->enMemStore)
    {
        /*上报修改成功*/
        stModifyStatusEvt.bSuccess = VOS_TRUE;
        stModifyStatusEvt.ulFailCause = MN_ERR_NO_ERROR;
        MN_MSG_ReportModifyEvent(clientId,opId,&stModifyStatusEvt,MN_MSG_EVT_MODIFY_STATUS);
        /*广播上报NVIM中短信已发生了改变*/
        bcOpId = MN_MSG_GetBCopId();
        MN_MSG_ReportSmChanged(clientId,bcOpId,VOS_TRUE,MN_MSG_MEM_STORE_NV);
    }
    else
    {
    }
#else
    if (MN_ERR_NO_ERROR != ulRet)
    {
        /*上报修改失败*/
        stModifyStatusEvt.bSuccess = VOS_FALSE;
        stModifyStatusEvt.ulFailCause = ulRet;
        MN_MSG_ReportModifyEvent(clientId,opId,&stModifyStatusEvt,MN_MSG_EVT_MODIFY_STATUS);
        MN_WARN_LOG("MSG_ModifyStatus: Write SM Error");
    }
#endif
}

/*****************************************************************************
 函 数 名  : MSG_SetRcvMsgPath
 功能描述  : 设置接收短信路径,包括存储位置和短信报告应答
 输入参数  : clientId            - 发起该请求的Client的ID
             opId                - Operation ID, 标识本次操作
             pstRcvPathParm      - 短信路径相关参数
 输出参数  : 无
 返 回 值  : 无
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2007年9月27日
    作    者   : z40661
    修改内容   : 新生成函数
  2.日    期   : 2012年12月11日
    作    者   : l00167671
    修改内容   : DTS201212345678, TQE清理
  3.日    期   : 2013年8月3日
    作    者   : z60575
    修改内容   : TQE修改
  4.日    期   : 2014年03月04日
    作    者   : f62575
    修改内容   : DTS2014030801193, +CNMI参数<MT>3配置不生效
*****************************************************************************/
LOCAL VOS_VOID MSG_SetRcvMsgPath(
    MN_CLIENT_ID_T                         clientId,
    MN_OPERATION_ID_T                      opId,
    const MN_MSG_SET_RCVMSG_PATH_PARM_STRU *pstRcvPathParm
)
{
    MN_MSG_SET_RCVMSG_PATH_PARM_STRU    stRcvPath;
    MN_MSG_RCVMSG_PATH_EVT_INFO_STRU    stRcvPathEvt;
    VOS_UINT32                          ulRet;
    MN_OPERATION_ID_T                   bcOpId;
    VOS_INT                             lRet;

    PS_MEM_SET(&stRcvPath, 0, sizeof(stRcvPath));

    MN_INFO_LOG("MSG_SetRcvMsgPath: step into function.");
    MN_SendClientResponse(clientId,opId,MN_ERR_NO_ERROR);
    MN_MSG_GetCurRcvMsgPath(&stRcvPath);

    PS_MEM_SET(&stRcvPathEvt,0X00,sizeof(stRcvPathEvt));
    stRcvPathEvt.operType = MN_MSG_OPER_SET;
    stRcvPathEvt.enRcvSmAct = pstRcvPathParm->enRcvSmAct;
    stRcvPathEvt.enSmMemStore = pstRcvPathParm->enSmMemStore;
    stRcvPathEvt.enRcvStaRptAct = pstRcvPathParm->enRcvStaRptAct;
    stRcvPathEvt.enStaRptMemStore = pstRcvPathParm->enStaRptMemStore;
    stRcvPathEvt.enSmsServVersion = pstRcvPathParm->enSmsServVersion;
    lRet = VOS_MemCmp(pstRcvPathParm, &stRcvPath, sizeof(stRcvPath));
    if (0 == lRet)
    {
        stRcvPathEvt.bSuccess = VOS_TRUE;
        stRcvPathEvt.ulFailCause = MN_ERR_NO_ERROR;
        MN_MSG_ReportRcvPathEvent(clientId,opId,VOS_FALSE,&stRcvPathEvt,MN_MSG_EVT_SET_RCVMSG_PATH);
        return;
    }

    /*更新配置数据到内存和NV */
    ulRet = MN_MSG_UpdateRcvMsgPath(pstRcvPathParm);
    MN_NORM_LOG1("MSG_SetRcvMsgPath: result of MN_MSG_UpdateRcvMsgPath ", (VOS_INT32)ulRet);
    if (MN_ERR_NO_ERROR != ulRet)
    {
        stRcvPathEvt.bSuccess = VOS_FALSE;
        stRcvPathEvt.ulFailCause = ulRet;
        MN_MSG_ReportRcvPathEvent(clientId,opId,VOS_FALSE,&stRcvPathEvt,MN_MSG_EVT_SET_RCVMSG_PATH);
        return;
    }

    stRcvPathEvt.bSuccess = VOS_TRUE;
    stRcvPathEvt.ulFailCause = MN_ERR_NO_ERROR;
    MN_MSG_ReportRcvPathEvent(clientId,opId,VOS_FALSE,&stRcvPathEvt,MN_MSG_EVT_SET_RCVMSG_PATH);

    bcOpId = MN_MSG_GetBCopId();
    MN_MSG_ReportRcvPathEvent(clientId,bcOpId,VOS_TRUE,&stRcvPathEvt,MN_MSG_EVT_RCVMSG_PATH_CHANGED);
    MN_MSG_StartMemNotification();
}


/*****************************************************************************
 函 数 名  : MSG_GetRcvMsgPath
 功能描述  : 获取接收短信路径,包括存储位置和短信报告应答
 输入参数  : clientId            - 发起该请求的Client的ID
             opId                - Operation ID, 标识本次操作
             pstRcvPah           - 获取短信路径相关参数
 输出参数  : 无
 返 回 值  : 无

 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2007年9月27日
    作    者   : z40661
    修改内容   : 新生成函数
*****************************************************************************/
LOCAL VOS_VOID MSG_GetRcvMsgPath(
    MN_CLIENT_ID_T                      clientId,
    MN_OPERATION_ID_T                   opId,
    MN_MSG_GET_RCVMSG_PATH_PARM_STRU    *pstRcvPah
)
{
    MN_MSG_SET_RCVMSG_PATH_PARM_STRU    stRcvPath;
    MN_MSG_RCVMSG_PATH_EVT_INFO_STRU    stRcvPathEvt;

    MN_SendClientResponse(clientId,opId,MN_ERR_NO_ERROR);
    MN_MSG_GetCurRcvMsgPath(&stRcvPath);
    PS_MEM_SET(&stRcvPathEvt,0X00,sizeof(stRcvPathEvt));
    stRcvPathEvt.operType = MN_MSG_OPER_GET;
    stRcvPathEvt.bSuccess = VOS_TRUE;
    stRcvPathEvt.ulFailCause = MN_ERR_NO_ERROR;
    stRcvPathEvt.enRcvSmAct = stRcvPath.enRcvSmAct;
    stRcvPathEvt.enSmMemStore = stRcvPath.enSmMemStore;
    stRcvPathEvt.enRcvStaRptAct = stRcvPath.enRcvStaRptAct;
    stRcvPathEvt.enStaRptMemStore = stRcvPath.enStaRptMemStore;
    MN_MSG_ReportRcvPathEvent(clientId,opId,VOS_FALSE,&stRcvPathEvt,MN_MSG_EVT_GET_RCVMSG_PATH);
}


/*****************************************************************************
 函 数 名  : MSG_GetStorageStatus
 功能描述  : 获取短信具体存储状况
 输入参数  : clientId            - 发起该请求的Client的ID
             opId                - Operation ID, 标识本次操作
             pstMemParm          - 短信存储位置
 输出参数  : 无
 返 回 值  : 无

 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2007年9月27日
    作    者   : z40661
    修改内容   : 新生成函数
  2.日    期   : 2011年1月12日
    作    者   : 傅映君/f62575
    修改内容   : DTAS2011011200351 法国ORANGE后台打开PIN码短信接收失败
*****************************************************************************/
LOCAL VOS_VOID MSG_GetStorageStatus(
    MN_CLIENT_ID_T                            clientId,
    MN_OPERATION_ID_T                         opId,
    const MN_MSG_GET_STORAGE_STATUS_PARM_STRU *pstMemParm
)
{
    VOS_UINT32                          ulRet;

    if ((MN_MSG_MEM_STORE_SIM == pstMemParm->enMem1Store)
     || (MN_MSG_MEM_STORE_SIM == pstMemParm->enMem2Store))
    {
        ulRet = MN_MSG_CheckUsimStatus();
        if (MN_ERR_NO_ERROR != ulRet)
        {
            MN_WARN_LOG1("MSG_GetStorageStatus:ErrCode ", (VOS_INT32)ulRet);
            MN_SendClientResponse(clientId,opId,ulRet);
            return;
        }
    }

    MN_SendClientResponse(clientId,opId,MN_ERR_NO_ERROR);
#if (NAS_FEATURE_SMS_NVIM_SMSEXIST == FEATURE_ON)
    if ((MN_MSG_MEM_STORE_SIM == pstMemParm->enMem1Store)
     || (MN_MSG_MEM_STORE_NV == pstMemParm->enMem1Store))
    {
        MN_MSG_ReportSmChanged(clientId,opId,VOS_FALSE,pstMemParm->enMem1Store);
    }
    if ((MN_MSG_MEM_STORE_SIM == pstMemParm->enMem2Store)
     || (MN_MSG_MEM_STORE_NV == pstMemParm->enMem2Store))
    {
        MN_MSG_ReportSmChanged(clientId,opId,VOS_FALSE,pstMemParm->enMem2Store);
    }
#else
    MN_MSG_ReportSmChanged(clientId,opId, VOS_FALSE, MN_MSG_MEM_STORE_SIM);
#endif
}

/*****************************************************************************
 函 数 名  : MSG_GetStaRptFromMoMsg
 功能描述  : 根据MO短信索引得到其状态报告索引
 输入参数  : clientId       - 发起该请求的Client的ID
             opId           - Operation ID, 标识本次操作
             pstMoMsgParm   - MO短信相关参数
 输出参数  : 无
 返 回 值  : 无

 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2007年9月27日
    作    者   : z40661
    修改内容   : 新生成函数
  2.日    期   : 2014年7月24日
    作    者   : b00269685
    修改内容   : coverify清理
*****************************************************************************/
LOCAL VOS_VOID MSG_GetStaRptFromMoMsg(
    MN_CLIENT_ID_T                      clientId,
    MN_OPERATION_ID_T                   opId,
    const MN_MSG_STARPT_MOMSG_PARM_STRU *pstMoMsgParm
)
{
    VOS_UINT32                          ulRet;
    VOS_UINT8                           ucStatus;
    VOS_UINT8                           aucSmCotent[MN_MSG_EFSMS_LEN];
    VOS_UINT8                           aucSmsrCotent[MN_MSG_EFSMSR_LEN];
    MN_MSG_BCD_ADDR_STRU                stscAddr;
    MN_MSG_RAW_TS_DATA_STRU             stRawData;
    VOS_UINT32                          ulSmsrCapacity = 0;
    VOS_UINT32                          i;
    VOS_UINT8                           ucMoTpMr;
    MN_MSG_READ_EVT_INFO_STRU           stReadEvt;

    /* Added by b00269685 for Coverify清理, 2014-7-24, begin */
    PS_MEM_SET(&stRawData, 0, sizeof(MN_MSG_RAW_TS_DATA_STRU));
    /* Added by b00269685 for Coverify清理, 2014-7-24, end */
    
    ulRet = MN_MSG_GetStatus(pstMoMsgParm->enMemStore,pstMoMsgParm->ulIndex,&ucStatus);
    if ((MN_ERR_NO_ERROR != ulRet)
     || (EF_SMS_STATUS_SRR_RCV_STOR != ucStatus))
    {
        MN_WARN_LOG("MSG_GetStaRptFromMoMsg:Invalid Tpdu Type");
        MN_SendClientResponse(clientId,opId,MN_ERR_CLASS_SMS_INVALID_TPDUTYPE);
        return;
    }

    PS_MEM_SET(aucSmCotent,(VOS_CHAR)0XFF,MN_MSG_EFSMS_LEN);
    ulRet = MN_MSG_ReadSmsInfo(pstMoMsgParm->enMemStore,pstMoMsgParm->ulIndex, aucSmCotent);
    if (MN_ERR_NO_ERROR != ulRet)
    {
        MN_WARN_LOG1("MSG_GetStaRptFromMoMsg:ErrCode ", (VOS_INT32)ulRet);
        MN_SendClientResponse(clientId,opId,ulRet);
        return;
    }

    ulRet = MN_MSG_ParseEFSmContent(aucSmCotent,&stscAddr,&stRawData,&ucStatus);
    if (MN_ERR_NO_ERROR != ulRet)
    {
        MN_WARN_LOG1("MSG_GetStaRptFromMoMsg:ErrCode ", (VOS_INT32)ulRet);
        MN_SendClientResponse(clientId,opId,ulRet);
        return;
    }

    if ((MN_MSG_TPDU_COMMAND != stRawData.enTpduType)
     && (MN_MSG_TPDU_SUBMIT != stRawData.enTpduType))
    {
        MN_WARN_LOG("MSG_GetStaRptFromMoMsg:Invalid Tpdu Type");
        MN_SendClientResponse(clientId,opId,MN_ERR_CLASS_SMS_INVALID_TPDUTYPE);
        return;
    }

    ucMoTpMr = stRawData.aucData[1];
    ulSmsrCapacity = MN_MSG_GetSmsrCapacity(pstMoMsgParm->enMemStore);
    PS_MEM_SET(aucSmsrCotent,(VOS_CHAR)0XFF,MN_MSG_EFSMSR_LEN);

    /*寻找TP-MR相同的短信状态报告*/
    for(i = 0; i < ulSmsrCapacity; i++)
    {
        PS_MEM_SET(aucSmsrCotent,(VOS_CHAR)0XFF,MN_MSG_EFSMSR_LEN);
        ulRet = MN_MSG_ReadSmsrInfo(pstMoMsgParm->enMemStore,i,aucSmsrCotent);
        if (MN_ERR_NO_ERROR != ulRet)
        {
            continue;
        }

        /*比较TP-MR的值*/
        if (ucMoTpMr == aucSmsrCotent[2])
        {
            break;
        }
    }

    /*未能找到相同的TP-MR的短信状态报告*/
    if (i >= ulSmsrCapacity)
    {
        MN_WARN_LOG("MSG_GetStaRptFromMoMsg:No Sm");
        MN_SendClientResponse(clientId,opId,MN_ERR_CLASS_SMS_NO_SM);
        return;
    }

    MN_SendClientResponse(clientId,opId,MN_ERR_NO_ERROR);
    PS_MEM_SET(&stReadEvt,0X00,sizeof(stReadEvt));
    stReadEvt.stMsgInfo.stTsRawData.enTpduType = MN_MSG_TPDU_STARPT;
    stReadEvt.stMsgInfo.stTsRawData.ulLen = MN_MSG_EFSMSR_LEN - 1;
    PS_MEM_CPY(stReadEvt.stMsgInfo.stTsRawData.aucData,aucSmsrCotent + 1,MN_MSG_EFSMSR_LEN - 1);
    stReadEvt.bSuccess = VOS_TRUE;
    stReadEvt.ulFailCause = MN_ERR_NO_ERROR;
    stReadEvt.enMemStore = pstMoMsgParm->enMemStore;
    stReadEvt.ulIndex = i;
    stReadEvt.enStatus = MN_MSG_STATUS_STARPT;
    MN_MSG_ReportReadEvent(clientId,opId,&stReadEvt,MN_MSG_EVT_MATCH_MO_STARPT_INFO);
    return;
}

/*****************************************************************************
 函 数 名  : MSG_GetMoMsgFromStaRpt
 功能描述  : 根据短信状态报告索引得到MO短信索引
 输入参数  : clientId       - 发起该请求的Client的ID
             opId           - Operation ID, 标识本次操作
             pstStaRptParm  - 短信状态报告相关参数
 输出参数  : 无
 返 回 值  : 无

 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2007年9月27日
    作    者   : z40661
    修改内容   : 新生成函数
  2.日    期   : 2014年7月7号
    作    者   : z00234330
    修改内容   : coverity清理      
*****************************************************************************/
LOCAL VOS_VOID MSG_GetMoMsgFromStaRpt(
    MN_CLIENT_ID_T                      clientId,
    MN_OPERATION_ID_T                   opId,
    const MN_MSG_STARPT_MOMSG_PARM_STRU *pstStaRptParm
)
{
    VOS_UINT32                          ulRet;
    VOS_UINT8                           ucStatus;
    VOS_UINT8                           aucSmCotent[MN_MSG_EFSMS_LEN];
    VOS_UINT8                           aucSmsrCotent[MN_MSG_EFSMSR_LEN];
    MN_MSG_BCD_ADDR_STRU                stscAddr;
    MN_MSG_RAW_TS_DATA_STRU             stRawData;
    VOS_UINT8                           ucStaRptTpMr;
    MN_MSG_READ_EVT_INFO_STRU           stReadEvt;

    PS_MEM_SET(&stRawData, 0x00, sizeof(stRawData));
    PS_MEM_SET(aucSmsrCotent,(VOS_CHAR)0XFF,MN_MSG_EFSMSR_LEN);
    ulRet = MN_MSG_ReadSmsrInfo(pstStaRptParm->enMemStore,pstStaRptParm->ulIndex,aucSmsrCotent);
    if ((MN_ERR_NO_ERROR != ulRet)
     || (0 == aucSmsrCotent[0]))
    {
        MN_WARN_LOG1("MSG_GetMoMsgFromStaRpt:ErrCode ", (VOS_INT32)ulRet);
        MN_SendClientResponse(clientId,opId,ulRet);
        return;
    }
    ucStaRptTpMr = aucSmsrCotent[2];
    PS_MEM_SET(&stRawData,0X00,sizeof(stRawData));
    PS_MEM_SET(&stscAddr,0X00,sizeof(stscAddr));
    /*寻找TP-MR相同的短信*/
    PS_MEM_SET(aucSmCotent,(VOS_CHAR)0XFF,MN_MSG_EFSMS_LEN);
    if (VOS_FALSE == MN_MSG_IsValidSmIndex(pstStaRptParm->enMemStore, (aucSmsrCotent[0] - 1)))
    {
        MN_SendClientResponse(clientId,opId,MN_ERR_CLASS_SMS_INVALID_REC);
        return;
    }
    ulRet = MN_MSG_ReadSmsInfo(pstStaRptParm->enMemStore,(aucSmsrCotent[0] - 1),aucSmCotent);
    if (MN_ERR_NO_ERROR != ulRet)
    {
        MN_SendClientResponse(clientId,opId,MN_ERR_CLASS_SMS_INVALID_REC);
        return;
    }
    ulRet = MN_MSG_ParseEFSmContent(aucSmCotent,&stscAddr,&stRawData,&ucStatus);
    if (MN_ERR_NO_ERROR != ulRet)
    {
        MN_SendClientResponse(clientId,opId,MN_ERR_CLASS_SMS_INVALID_REC);
        return;
    }
    if ((MN_MSG_TPDU_COMMAND != stRawData.enTpduType)
     && (MN_MSG_TPDU_SUBMIT != stRawData.enTpduType))
    {
        MN_SendClientResponse(clientId,opId,MN_ERR_CLASS_SMS_INVALID_REC);
        return;
    }
    if (EF_SMS_STATUS_SRR_RCV_STOR != ucStatus)
    {
        MN_SendClientResponse(clientId,opId,MN_ERR_CLASS_SMS_INVALID_REC);
        return;
    }
    if (ucStaRptTpMr == stRawData.aucData[1])
    {
        MN_SendClientResponse(clientId,opId,MN_ERR_CLASS_SMS_INVALID_REC);
        return;
    }

    MN_SendClientResponse(clientId,opId,MN_ERR_NO_ERROR);
    PS_MEM_SET(&stReadEvt,0X00,sizeof(stReadEvt));
    PS_MEM_CPY(&stReadEvt.stMsgInfo.stTsRawData,&stRawData,sizeof(MN_MSG_RAW_TS_DATA_STRU));
    PS_MEM_CPY(&stReadEvt.stMsgInfo.stScAddr,&stscAddr,sizeof(MN_MSG_BCD_ADDR_STRU));
    stReadEvt.bSuccess = VOS_TRUE;
    stReadEvt.ulFailCause = MN_ERR_NO_ERROR;
    stReadEvt.enMemStore = pstStaRptParm->enMemStore;
    stReadEvt.ulIndex = (aucSmsrCotent[0] - 1);
    stReadEvt.enStatus = MN_MSG_STATUS_MO_SENT;
    MN_MSG_ReportReadEvent(clientId,opId,&stReadEvt,MN_MSG_EVT_MATCH_MO_STARPT_INFO);
    return;
}

/*****************************************************************************
 函 数 名  : MSG_SetMemStatus
 功能描述  : APP设置当前的应用存储设备状态
 输入参数  : clientId            - 发起该请求的Client的ID
             opId                - Operation ID, 标识本次操作
             pMemStatusParm      - APP当前接收容量
 输出参数  : 无
 返 回 值  : 无
             无
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2007年9月27日
    作    者   : z40661
    修改内容   : 新生成函数
  2.日    期   : 2011年11月08日
    作    者   : 傅映君/f62575
    修改内容   : DTS2012111201995，DCM短信接收定制需求
*****************************************************************************/
LOCAL VOS_VOID MSG_SetMemStatus(
    MN_CLIENT_ID_T                       clientId,
    MN_OPERATION_ID_T                    opId,
    const MN_MSG_SET_MEMSTATUS_PARM_STRU *pstMemStatusParm
)
{
    VOS_UINT32                          ulRet;
    MN_MSG_MEM_FLAG_ENUM_U8             enAppStatus;
    MN_MSG_MEMSTATUS_EVT_INFO_STRU      stMemStatusEvt;
    MN_OPERATION_ID_T                   bcOpId;

    PS_MEM_SET(&stMemStatusEvt,0X00,sizeof(stMemStatusEvt));

    MN_MSG_GetCurAppMemStatus(&enAppStatus);
    MN_SendClientResponse(clientId,opId,MN_ERR_NO_ERROR);
    if (enAppStatus != pstMemStatusParm->enMemFlag)
    {
        ulRet =  MN_MSG_UpdateAppMemStatus(pstMemStatusParm->enMemFlag);
        if (MN_ERR_NO_ERROR != ulRet)
        {
            stMemStatusEvt.bSuccess = VOS_FALSE;
            stMemStatusEvt.ulFailCause = MN_ERR_CLASS_SMS_NVIM;
            MN_MSG_ReportMemStatustEvent(clientId,opId,VOS_FALSE,&stMemStatusEvt,MN_MSG_EVT_SET_MEMSTATUS);
        }
        else
        {
            stMemStatusEvt.bSuccess = VOS_TRUE;
            stMemStatusEvt.ulFailCause = MN_ERR_NO_ERROR;

            stMemStatusEvt.enMemFlag = pstMemStatusParm->enMemFlag;
            MN_MSG_ReportMemStatustEvent(clientId, opId,VOS_FALSE, &stMemStatusEvt, MN_MSG_EVT_SET_MEMSTATUS);

            /*广播上报给所有应用当前接收容量发生了改变*/
            bcOpId = MN_MSG_GetBCopId();
            MN_MSG_ReportMemStatustEvent(clientId,bcOpId,VOS_TRUE, &stMemStatusEvt, MN_MSG_EVT_MEMSTATUS_CHANGED);

            /* 如果当前APP的状态是SET,应用需要修改为UNSET,则需要发送SMMA消息到网侧 */
            MN_MSG_StartMemNotification();
        }

    }
    else
    {
        stMemStatusEvt.bSuccess = VOS_TRUE;
        stMemStatusEvt.ulFailCause = MN_ERR_NO_ERROR;
        stMemStatusEvt.enMemFlag = pstMemStatusParm->enMemFlag;
        MN_MSG_ReportMemStatustEvent(clientId,opId,VOS_FALSE,&stMemStatusEvt,MN_MSG_EVT_SET_MEMSTATUS);
    }

}

/*****************************************************************************
 函 数 名  : MSG_SetLinkCtrl
 功能描述  : 设置中继链路控制数据
 输入参数  : clientId            - 发起该请求的Client的ID
             opId                - Operation ID, 标识本次操作
             pstSetParam         - 中继链路控制数据结构指针
 输出参数  : 无
 返 回 值  : 无
             无
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2008年7月22日
    作    者   : f62575
    修改内容   : 新生成函数
*****************************************************************************/
LOCAL VOS_VOID MSG_SetLinkCtrl(
    MN_CLIENT_ID_T                       clientId,
    MN_OPERATION_ID_T                    opId,
    const MN_MSG_SET_LINK_CTRL_STRU      *pstSetParam
)
{
    VOS_UINT32                          ulRet;

    MN_SendClientResponse(clientId,opId,MN_ERR_NO_ERROR);
    ulRet = MN_MSG_UpdateLinkCtrlParam(pstSetParam->enRelayLinkCtrl);
    MN_MSG_ReportLinkCtrl(clientId,
                               opId,
                               MN_MSG_EVT_SET_LINK_CTRL_PARAM,
                               ulRet,
                               MN_MSG_GetLinkCtrlParam());
    return;
}

/*****************************************************************************
 函 数 名  : MSG_GetLinkCtrl
 功能描述  : APP获取中继链路控制数据
 输入参数  : clientId            - 发起该请求的Client的ID
             opId                - Operation ID, 标识本次操作
 输出参数  : 无
 返 回 值  : 无
             无
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2008年7月22日
    作    者   : f62575
    修改内容   : 新生成函数
*****************************************************************************/
LOCAL VOS_VOID MSG_GetLinkCtrl(
    MN_CLIENT_ID_T                       clientId,
    MN_OPERATION_ID_T                    opId
)
{
    VOS_UINT32                          ulRet = MN_ERR_NO_ERROR;

    MN_SendClientResponse(clientId,opId,MN_ERR_NO_ERROR);
    MN_MSG_ReportLinkCtrl(clientId,
                               opId,
                               MN_MSG_EVT_GET_LINK_CTRL_PARAM,
                               ulRet,
                               MN_MSG_GetLinkCtrlParam());
    return;
}

/* Added by f62575 for AT Project，2011-10-03,  Begin*/
/*****************************************************************************
 函 数 名  : MSG_ProcStub
 功能描述  : 设置桩数据到MSG模块
 输入参数  : MN_CLIENT_ID_T      clientId   发起该请求的Client的ID
             MN_OPERATION_ID_T   opId,      标识本次操作
             const MN_MSG_STUB_MSG_STRU     *pstStubParam 桩数据结构指针
 输出参数  : 无
 返 回 值  : 无
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2008年7月22日
    作    者   : f62575
    修改内容   : 新生成函数
*****************************************************************************/
LOCAL VOS_VOID MSG_ProcStub(
    MN_CLIENT_ID_T                       clientId,
    MN_OPERATION_ID_T                    opId,
    const MN_MSG_STUB_MSG_STRU          *pstStubParam
)
{
    VOS_UINT32                          ulRet;

    MN_SendClientResponse(clientId, opId, MN_ERR_NO_ERROR);

    ulRet = MN_ERR_NO_ERROR;

    switch (pstStubParam->enStubType)
    {
        case MN_MSG_STUB_TYPE_SET_EFSMS_INAVAILABLE:
            g_ucSetEfSmsFail = (VOS_UINT8)pstStubParam->ulValue;
            break;
#if ( VOS_WIN32 == VOS_OS_VER )
        case MN_MSG_STUB_TYPE_EFSMS_GET_NO_RESPONSE:
            g_ucSetEfSmsNoResponse = (VOS_UINT8)pstStubParam->ulValue;
            break;
        case MN_MSG_STUB_TYPE_SET_EFSMS_CAPACITY:
            g_ucSetEfSmsCapacity = (VOS_UINT8)pstStubParam->ulValue;
            if (0 == g_ucSetEfSmsCapacity)
            {
                MSG_UpdateMemFlag(MN_MSG_MEM_FULL_UNSET);
            }
            else
            {
                MN_MGS_UpdateSmsCapability(MN_MSG_MEM_STORE_SIM, pstStubParam->ulValue);
            }

            break;
        case MN_MSG_STUB_TYPE_EFSMSS_RESET:
            g_ucSetEfSmssClear = (VOS_UINT8)pstStubParam->ulValue;
            break;
        case MN_MSG_STUB_TYPE_EFSMSP_GET_NO_RESPONSE:
            g_ucSetEfSmspNoRsp = (VOS_UINT8)pstStubParam->ulValue;
            break;
        case MN_MSG_STUB_TYPE_STK_8BIT_TO_7BIT:
            USIMM_SendSMSDataInd1();
            break;
        case MN_MSG_STUB_TYPE_STK_SEGMENT:
            USIMM_SendSMSDataInd2();
            break;
        case MN_MSG_STUB_TYPE_DISABLE_MO_RETRY:
            g_ucDisableMoRetry = (VOS_UINT8)pstStubParam->ulValue;
            break;
        case MN_MSG_STUB_TYPE_CLASS0_TAILOR:
            g_enClass0Tailor = (VOS_UINT8)pstStubParam->ulValue;
            break;
        case MN_MSG_STUB_TYPE_PP_DOWNLOAD_RSP_TYPE:
            g_ucPpDownloadStub = (VOS_UINT8)pstStubParam->ulValue;
            break;
#endif
        case MN_MSG_STUB_TYPE_PS_CONCATENATE_FLAG:
            SMS_SetSmsPsConcatenateFlag((NAS_SMS_PS_CONCATENATE_ENUM_UINT8)pstStubParam->ulValue);
            break;
        default:
            ulRet = MN_ERR_UNSPECIFIED;
            break;
    }

    MN_MSG_ReportResult(clientId, opId, MN_MSG_EVT_STUB_RESULT, ulRet);

    return;
}
/* Added by f62575 for AT Project，2011-10-03,  End*/


/*****************************************************************************
 函 数 名  : MN_MSG_RecurDataRestore
 功能描述  : 将TRACE记录的全局变量数据恢复到回放工程的内存
 输入参数  : MN_APP_REQ_MSG_STRU                 *pstAppMsg
 输出参数  : 无
 返 回 值  : VOS_VOID
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2011年12月19日
    作    者   : f62575
    修改内容   : 新生成函数

*****************************************************************************/
VOS_VOID MN_MSG_RecurDataRestore(
    struct MsgCB                        *pstMsg
)
{

#ifdef __PS_WIN32_RECUR__
    MN_APP_REQ_MSG_STRU                 *pstAppMsg;

    pstAppMsg = (MN_APP_REQ_MSG_STRU *)pstMsg;

    if ( MN_MSG_PC_REPLAY_MSG_PART1 == pstAppMsg->usMsgName)
    {
        NAS_MSG_RestoreContextData_Part1(pstAppMsg);
        return;
    }
    if ( MN_MSG_PC_REPLAY_MSG_PART2 == pstAppMsg->usMsgName)
    {
        NAS_MSG_RestoreContextData_Part2(pstAppMsg);
        return;
    }
    if ( MN_MSG_PC_REPLAY_MSG_PART3 == pstAppMsg->usMsgName)
    {
        NAS_MSG_RestoreContextData_Part3(pstAppMsg);
        return;
    }
#endif
    return;
}
/*****************************************************************************
 函 数 名  : MN_MSG_ProcAppReqMsg
 功能描述  : 处理收到了API接口发送过来消息的入口函数
 输入参数  : pstAppMsg            - API接口发送过来的消息包
 输出参数  : 无
 返 回 值  : 无
             无
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2007年9月27日
    作    者   : z40661
    修改内容   : 新生成函数
 2.日    期   : 2009年10月28日
    作    者   : f62575
    修改内容   : AT2D15641, STK短信发送需要支持长短信的分段发送功能
 3.日    期   : 2010年2月23日
    作    者   : f62575
    修改内容   : 问题单号：增加短信功能任意点回放功能
 4.日    期   : 2011年10月3日
   作    者   : f62575
   修改内容   : AT Project 增加短信桩处理分支
 5.日    期   : 2011年11月10日
   作    者   : f62575
   修改内容   : DTS2011111004869 支持双核架构下STK模块短信发送请求
  6.日    期   : 2012年4月5日
    作    者   : l00171473
    修改内容   : for V7R1C50 CSFB&PPAC&ETWS&ISR
  7.日    期   : 2013年6月26日
    作    者   : f62575
    修改内容   : V9R1 STK升级
*****************************************************************************/
VOS_VOID MN_MSG_ProcAppReqMsg(
    MN_APP_REQ_MSG_STRU                 *pstAppMsg
)
{
    /* Modified by s62952 for BalongV300R002 Build优化项目 2012-02-28, begin */
    MN_MSG_CUSTOM_CFG_INFO_STRU        *pstCustomCfgAddr;

    /* 获取特性控制NV地址 */
    pstCustomCfgAddr                    = MN_MSG_GetCustomCfgInfo();
    /* Modified by s62952 for BalongV300R002 Build优化项目 2012-02-28, end */


#ifdef __PS_WIN32_RECUR__
    if ( MN_MSG_PC_REPLAY_MSG_PART1 == pstAppMsg->usMsgName)
    {
        NAS_MSG_RestoreContextData_Part1((struct MsgCB *)pstAppMsg);
        return;
    }
    if ( MN_MSG_PC_REPLAY_MSG_PART2 == pstAppMsg->usMsgName)
    {
        NAS_MSG_RestoreContextData_Part2((struct MsgCB *)pstAppMsg);
        return;
    }
    if ( MN_MSG_PC_REPLAY_MSG_PART3 == pstAppMsg->usMsgName)
    {
        NAS_MSG_RestoreContextData_Part3((struct MsgCB *)pstAppMsg);
        return;
    }
#endif

    switch (pstAppMsg->usMsgName)
    {
        /* Modified by f62575 for V9R1 STK升级, 2013-6-26, begin */
        case MN_MSG_MSGTYPE_SEND_RPDATA_DIRECT:
            MN_MSG_ProcAppSend((struct MsgCB *)pstAppMsg);
            break;
        case MN_MSG_MSGTYPE_SEND_RPDATA_FROMMEM:
            MN_MSG_ProcAppSend((struct MsgCB *)pstAppMsg);
            break;
        /* Modified by f62575 for V9R1 STK升级, 2013-6-26, end */
        case MN_MSG_MSGTYPE_SEND_RPRPT:
            MSG_SendAck(pstAppMsg->clientId,
                        pstAppMsg->opId,
                        (MN_MSG_SEND_ACK_PARM_STRU*)pstAppMsg->aucContent);
            break;
        case MN_MSG_MSGTYPE_WRITE:
            MSG_Write(pstAppMsg->clientId,
                      pstAppMsg->opId,
                      (MN_MSG_WRITE_PARM_STRU*)pstAppMsg->aucContent);
            break;
        case MN_MSG_MSGTYPE_READ:
            MSG_Read(pstAppMsg->clientId,
                     pstAppMsg->opId,
                     (MN_MSG_READ_PARM_STRU*)pstAppMsg->aucContent);
            break;
        case MN_MSG_MSGTYPE_LIST:
            MSG_List(pstAppMsg->clientId,
                     pstAppMsg->opId,
                     (MN_MSG_LIST_PARM_STRU*)pstAppMsg->aucContent);
            break;
        case MN_MSG_MSGTYPE_DELETE:
            MSG_Delete(pstAppMsg->clientId,
                       pstAppMsg->opId,
                       (MN_MSG_DELETE_PARAM_STRU*)pstAppMsg->aucContent);
            break;
        case MN_MSG_MSGTYPE_DELETE_TEST:
            MSG_Delete_Test(pstAppMsg->clientId,
                            pstAppMsg->opId,
                            (MN_MSG_LIST_PARM_STRU *)pstAppMsg->aucContent);
            break;
        case MN_MSG_MSGTYPE_WRITE_SRV_PARA:
            MSG_WriteSrvParm(pstAppMsg->clientId,
                              pstAppMsg->opId,
                              (MN_MSG_WRITE_SRV_PARAM_STRU*)pstAppMsg->aucContent);
            break;
        case MN_MSG_MSGTYPE_READ_SRV_PARA:
            MSG_ReadSrvParm(pstAppMsg->clientId,
                             pstAppMsg->opId,
                             (MN_MSG_READ_COMM_PARAM_STRU*)pstAppMsg->aucContent);
            break;
        case MN_MSG_MSGTYPE_DELETE_SRV_PARA:
            MSG_DeleteSrvParm(pstAppMsg->clientId,
                               pstAppMsg->opId,
                               (MN_MSG_DELETE_PARAM_STRU*)pstAppMsg->aucContent);
            break;
        case MN_MSG_MSGTYPE_MODIFY_STATUS:
            MSG_ModifyStatus(pstAppMsg->clientId,
                             pstAppMsg->opId,
                             (MN_MSG_MODIFY_STATUS_PARM_STRU*)pstAppMsg->aucContent);
            break;
        case MN_MSG_MSGTYPE_SET_RCVPATH:
            MSG_SetRcvMsgPath(pstAppMsg->clientId,
                              pstAppMsg->opId,
                              (MN_MSG_SET_RCVMSG_PATH_PARM_STRU*)pstAppMsg->aucContent);
            break;
        case MN_MSG_MSGTYPE_GET_RCVPATH:
            MSG_GetRcvMsgPath(pstAppMsg->clientId,
                              pstAppMsg->opId,
                              (MN_MSG_GET_RCVMSG_PATH_PARM_STRU*)pstAppMsg->aucContent);
            break;
        case MN_MSG_MSGTYPE_GET_STORAGESTATUS:
            MSG_GetStorageStatus(pstAppMsg->clientId,
                                 pstAppMsg->opId,
                                 (MN_MSG_GET_STORAGE_STATUS_PARM_STRU*)pstAppMsg->aucContent);
            break;
        /* Modified by s62952 for BalongV300R002 Build优化项目 2012-02-28, begin */
        case MN_MSG_MSGTYPE_READ_STARPT:
            if (MN_MSG_NV_ITEM_DEACTIVE == pstCustomCfgAddr->ucSmsStatusInEfsmsSupportFlg)
            {
                MSG_ReadStaRpt(pstAppMsg->clientId,
                               pstAppMsg->opId,
                               (MN_MSG_READ_COMM_PARAM_STRU*)pstAppMsg->aucContent);
            }

            break;
        case MN_MSG_MSGTYPE_DELETE_STARPT:
            if (MN_MSG_NV_ITEM_DEACTIVE == pstCustomCfgAddr->ucSmsStatusInEfsmsSupportFlg)
            {
                MSG_DeleteStaRpt(pstAppMsg->clientId,
                                 pstAppMsg->opId,
                                 (MN_MSG_DELETE_PARAM_STRU*)pstAppMsg->aucContent);
            }
            break;
        case MN_MSG_MSGTYPE_GET_STARPT_FROMMOMSG:
            if (MN_MSG_NV_ITEM_DEACTIVE == pstCustomCfgAddr->ucSmsStatusInEfsmsSupportFlg)
            {
                MSG_GetStaRptFromMoMsg(pstAppMsg->clientId,
                                       pstAppMsg->opId,
                                       (MN_MSG_STARPT_MOMSG_PARM_STRU*)pstAppMsg->aucContent);

            }
            break;
        case MN_MSG_MSGTYPE_GET_MOMSG_FROMSTARPT:
            if (MN_MSG_NV_ITEM_DEACTIVE == pstCustomCfgAddr->ucSmsStatusInEfsmsSupportFlg)
            {
                MSG_GetMoMsgFromStaRpt(pstAppMsg->clientId,
                                       pstAppMsg->opId,
                                       (MN_MSG_STARPT_MOMSG_PARM_STRU*)pstAppMsg->aucContent);

            }
            break;
        /* Modified by s62952 for BalongV300R002 Build优化项目 2012-02-28, end */

        case MN_MSG_MSGTYPE_SET_MEMSTATUS:
            MSG_SetMemStatus(pstAppMsg->clientId,
                             pstAppMsg->opId,
                             (MN_MSG_SET_MEMSTATUS_PARM_STRU*)pstAppMsg->aucContent);
            break;
        case MN_MSG_MSGTYPE_SET_RELAY_LINK_CTRL:
            MSG_SetLinkCtrl(pstAppMsg->clientId,
                            pstAppMsg->opId,
                            (MN_MSG_SET_LINK_CTRL_STRU*)pstAppMsg->aucContent);
            break;
        case MN_MSG_MSGTYPE_GET_RELAY_LINK_CTRL:
            MSG_GetLinkCtrl(pstAppMsg->clientId,
                            pstAppMsg->opId);
            break;
        /* Added by f62575 for AT Project，2011-10-03,  Begin*/
        case MN_MSG_MSGTYPE_STUB:
            MSG_ProcStub(pstAppMsg->clientId,
                         pstAppMsg->opId,
                         (MN_MSG_STUB_MSG_STRU *)pstAppMsg->aucContent);
            break;
        /* Added by f62575 for AT Project，2011-10-03,  End*/
#if ((FEATURE_ON == FEATURE_GCBS) || (FEATURE_ON == FEATURE_WCBS))

        case MN_MSG_MSGTYPE_GET_ALLCBMIDS:
        case MN_MSG_MSGTYPE_ADD_CBMIDS:
        case MN_MSG_MSGTYPE_DELETE_CBMIDS:
        case MN_MSG_MSGTYPE_EMPTY_CBMIDS:
            TAF_CBA_MsgProc((struct MsgCB *)pstAppMsg);
            break;

#endif
        default:
            MN_WARN_LOG("MN_MSG_ProcAppReqMsg:Invalid Msg Name");
            break;
    }
}

/*****************************************************************************
 函 数 名  : MN_MSG_CheckMoMsg
 功能描述  : 发送短信实体的本地检查，包括FDN 和MO SMS CONTROL
 输入参数  : MN_MSG_MO_ENTITY_STRU              *pstMoEntity 待发送的短信实体
             VOS_UINT8                           aucEfSmContent[] 待发送的短信内容
 输出参数  : VOS_BOOL                           *pbRequireCheck 是否要求等待检查结果
             VOS_BOOL                           *pbBufferEntity 待发送短信是否缓存
 返回值    : VOS_UINT32
                MN_ERR_NO_ERROR                 检查执行正确
                其他，                          检查执行失败，需要拒绝用户的短信发送请求
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2012年9月20日
    作    者   : f62575
    修改内容   : 新生成函数
  2.日    期   : 2012年12月03日
    作    者   : 傅映君/f62575
    修改内容   : DTS2012120305230,FDN和MO SMS CONTROL流程定时器未停止问题；
  3.日    期   : 2012年12月28日
    作    者   : 傅映君/f62575
    修改内容   : DTS2012122406218, 短信正向质量发现问题: 短信发送流程部分
  4.日    期   : 2013年8月3日
    作    者   : z60575
    修改内容   : TQE修改
*****************************************************************************/
VOS_UINT32 MN_MSG_CheckMoMsg(
    VOS_UINT8                           aucEfSmContent[],
    MN_MSG_MO_ENTITY_STRU              *pstMoEntity,
    VOS_BOOL                           *pbRequireCheck,
    VOS_BOOL                           *pbBufferEntity
)
{
    MN_MSG_MO_ENTITY_STRU               stMoEntity;
    VOS_UINT32                          ulRet;
    VOS_BOOL                            bCheckFdn;
    VOS_BOOL                            bCheckMoCtrl;
    VOS_BOOL                            bStkBuffer;
    VOS_UINT32                          ulStoreIndex;
    MN_MSG_SEND_DOMAIN_ENUM_U8          enPsSendDomain;
    MN_MSG_SEND_DOMAIN_ENUM_U8          enCsSendDomain;
    MN_MSG_SENDMSG_EVT_INFO_STRU        stSendMsgEvt;

    /*判断当前消息是否需要缓存:
    1.STK短信，若当前UE没有注册，则不进行发送尝试，直接缓存;
    2.TAF MO实体非空闲状态最多可以缓存一条短信；*/
    bStkBuffer      = VOS_FALSE;
    *pbRequireCheck = VOS_FALSE;
    *pbBufferEntity = VOS_FALSE;
    bCheckFdn       = VOS_FALSE;

    if (MN_MSG_TPDU_SUBMIT != pstMoEntity->enTpduType)
    {
        return MN_ERR_NO_ERROR;
    }

    if (OAM_CLIENT_ID_STK == pstMoEntity->clientId)
    {
        MN_MSG_GetCurSendDomain(MN_MSG_SEND_DOMAIN_CS,&enPsSendDomain);
        MN_MSG_GetCurSendDomain(MN_MSG_SEND_DOMAIN_PS,&enCsSendDomain);
        if ((MN_MSG_SEND_DOMAIN_NO == enPsSendDomain)
         && (MN_MSG_SEND_DOMAIN_NO == enCsSendDomain))
        {
            bStkBuffer = VOS_TRUE;
        }
    }

    PS_MEM_SET(&stMoEntity, 0, sizeof(stMoEntity));

    /* 获取短信发送实体的信息 */
    ulStoreIndex = MN_MSG_NO_AVAILABLE_SMS_REC;
    MN_MSG_GetMoEntity(&stMoEntity);
    if ((MN_MSG_MO_STATE_NULL != stMoEntity.enSmaMoState)
     || (VOS_TRUE == bStkBuffer))
    {
        ulStoreIndex = MN_MSG_GetStoreMsgIndex();

        if (MN_MSG_NO_AVAILABLE_SMS_REC == ulStoreIndex)
        {
            MN_WARN_LOG("MN_MSG_CheckMoMsg: No Buffer");
            return MN_ERR_CLASS_SMS_NO_BUFFER;
        }

        /*广播上报短信已被缓存*/
        *pbBufferEntity = VOS_TRUE;
        PS_MEM_SET(&stSendMsgEvt,0X00,sizeof(stSendMsgEvt));
        stSendMsgEvt.enTpduType = pstMoEntity->enTpduType;

        *pbBufferEntity = VOS_TRUE;

        MN_MSG_ReportSentEvent(pstMoEntity->clientId,
                               pstMoEntity->opId,
                               &stSendMsgEvt,
                               MN_MSG_EVT_MSG_STORED);
    }

    MN_MSG_CreateMoEntity(*pbBufferEntity, ulStoreIndex, pstMoEntity, aucEfSmContent);

    /* MO SMS CONTROL流程前插入FDN 处理:    */
    ulRet = MN_MSG_CheckFdn(pstMoEntity, &bCheckFdn);
    if (MN_ERR_NO_ERROR != ulRet)
    {
        MN_WARN_LOG("MN_MSG_CheckMoMsg: send submit or command returns Error");
        MN_MSG_DestroySpecificMoEntity(*pbBufferEntity, ulStoreIndex);
        return ulRet;
    }

    /* 要求检查FDN: 启动定时器等待USIM的检查结果 */
    if (VOS_TRUE == bCheckFdn)
    {
        ulRet = MN_MSG_SendFdnCheckInfo(pstMoEntity);
        if (MN_ERR_NO_ERROR != ulRet)
        {
            MN_WARN_LOG("MN_MSG_CheckMoMsg: send submit or command returns Error");
            MN_MSG_DestroySpecificMoEntity(*pbBufferEntity, ulStoreIndex);
            return ulRet;
        }

        /* 启动定时器等待USIM的检查结果 */
        MN_MSG_StartTimer(MN_MGS_ID_WAIT_FDN_CHECK, 0);
        /* 保存待发送短信到发送实体或缓存，并更新状态到MN_MSG_MO_STATE_WAIT_FDN_CHECK_RSP */

        MN_MSG_UpdateSpecificMoEntityStatus(*pbBufferEntity, ulStoreIndex, MN_MSG_MO_STATE_WAIT_FDN_CHECK_RSP);

        *pbRequireCheck = VOS_TRUE;

        return MN_ERR_NO_ERROR;
    }

    /* MO SMS CONTROL 处理: 这个过程需要封装为函数 */
    ulRet = MN_MSG_CheckMoSmsCtrl(pstMoEntity, &bCheckMoCtrl);
    if (MN_ERR_NO_ERROR != ulRet)
    {
        MN_WARN_LOG("MN_MSG_CheckMoMsg: send submit or command returns Error");
        MN_MSG_DestroySpecificMoEntity(*pbBufferEntity, ulStoreIndex);
        return ulRet;
    }

    /* 要求检查MO SMS CONTROL: 启动定时器等待USIM的检查结果 */
    if (VOS_TRUE == bCheckMoCtrl)
    {
        ulRet = MN_MSG_ProcMoCtrl(pstMoEntity->clientId,
                                  pstMoEntity->opId,
                                  pstMoEntity->aucRpDataInfo);
        if (MN_ERR_NO_ERROR != ulRet)
        {
            MN_WARN_LOG("MN_MSG_CheckMoMsg: send submit or command returns Error");
            MN_MSG_DestroySpecificMoEntity(*pbBufferEntity, ulStoreIndex);
            return MN_ERR_CLASS_SMS_INTERNAL;
        }

        /* 保存待发送短信到发送实体或缓存，并更新状态到MN_MSG_MO_STATE_WAIT_FDN_CHECK_RSP
           启动定时器等待USIM的检查结果 */
        MN_MSG_StartTimer(MN_MGS_ID_WAIT_MO_SMS_CTRL_CHECK, 0);
        MN_MSG_UpdateSpecificMoEntityStatus(*pbBufferEntity, ulStoreIndex, MN_MSG_MO_STATE_WAIT_SMS_CTRL_RSP);

        *pbRequireCheck = VOS_TRUE;

        return MN_ERR_NO_ERROR;
    }

    *pbRequireCheck = VOS_FALSE;

    return MN_ERR_NO_ERROR;

}

/* Added by s00217060 for VoLTE_PhaseII  项目, 2013-09-24, begin */
/*****************************************************************************
 函 数 名  : TAF_MSG_ProcTafMsg
 功能描述  : MSG模块分发来自TAF的消息
 输入参数  : pstMsg - 收到的消息
 返 回 值  : 无
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2013年9月25日
    作    者   : s00217060
    修改内容   : 新生成函数
*****************************************************************************/
VOS_VOID TAF_MSG_ProcTafMsg (
    struct MsgCB                       *pstMsg
)
{
    TAF_INTERNAL_MSG_STRU              *pstTafMsg   = VOS_NULL_PTR;

    pstTafMsg = (TAF_INTERNAL_MSG_STRU *)pstMsg;

    switch (pstTafMsg->ulMsgId)
    {
    
        case ID_TAF_SPM_SMMA_RSP:
            TAF_MSG_RcvSpmSmmaRsp(pstMsg);
            break;

        default:
            MN_ERR_LOG("TAF_MSG_ProcTafMsg: Unknown message type.");
            break;
    }

    return;
}
/* Added by s00217060 for VoLTE_PhaseII  项目, 2013-09-24, end */
/*lint -restore */


#ifdef  __cplusplus
  #if  __cplusplus
  }
  #endif
#endif

