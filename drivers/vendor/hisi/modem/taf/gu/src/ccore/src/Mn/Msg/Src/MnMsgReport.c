/******************************************************************************

                  版权所有 (C), 2001-2011, 华为技术有限公司

 ******************************************************************************
  文 件 名   : MnMsgReport.c
  版 本 号   : 初稿
  作    者   : 周君 40661
  生成日期   : 2008年2月19日
  最近修改   :
  功能描述   :
  函数列表   :
  修改历史   :
  1.日    期   : 2008年2月19日
    作    者   : 周君 40661
    修改内容   : 创建文件
  2.日    期   : 2008年8月14日
    作    者   : 傅映君 62575
    修改内容   : 问题单号 AT2D03741,编程规范问题：   1。枚举类型定义   2。全局变量的外部声名   3。文件或函数的注释问题；   打印信息不完整   1。增加调试打印代码
  3.日    期   : 2008年8月14日
    作    者   : 傅映君 62575
    修改内容   : 问题单号 AT2D04609,CMMS命令的增加；
  4.日    期   : 2008年8月29日
    作    者   : fuyingjun
    修改内容   : 问题单号:AT2D05344, 短消息模块初始化过程结束后进行SDT工具与单板反复进行连接和断开操作,协议栈会重复上报初始化完成事件;
  5.日    期   : 2008年09月08日
    作    者   : f62575
    修改内容   : 问题单AT2D05583,CBS功能模块代码PC-lint错误
  6.日    期   : 2008年10月10日
    作    者   : f62575
    修改内容   : 问题单号：AT2D06152（AT2D06151）, USIMM优化合入后，SMSP文件相关读写操作失败
  7.日    期   : 2009年3月3日
    作    者   : z40661
    修改内容   : 问题单号：AT2D07942（AT2D09557）, 短信中心号码上报时间较长
  8.日    期   : 2009年7月18日
    作    者   : z40661
    修改内容   : 终端可配置需求合入
  9.日    期   : 2009年7月31日
    作    者   : f62575
    修改内容   : 问题单号：AT2D13420,短信TAF模块初始化处理错误
 10.日    期   : 2010年6月30日
    作    者   : 傅映君
    修改内容   : 问题单号DTS2010071500596，STK短信的定制缓存
******************************************************************************/

/*****************************************************************************
  1 头文件包含
*****************************************************************************/
#include  "MnMsgInclude.h"
#include  "TafCbaCtx.h"


#ifdef  __cplusplus
  #if  __cplusplus
  extern "C"{
  #endif
#endif


/*****************************************************************************
  2 变量定义
*****************************************************************************/
/*lint -e767 修改人:罗建 107747;检视人:孙少华65952;原因:Log打印*/
#define    THIS_FILE_ID        PS_FILE_ID_MNMSG_REPORT_C
/*lint +e767 修改人:罗建 107747;检视人:sunshaohua*/

MN_MSG_EVENT_INFO_STRU           f_stMsgEventInfo;


extern VOS_UINT8                        g_ucMnOmConnectFlg;
extern VOS_UINT8                        g_ucMnOmPcRecurEnableFlg;

/*lint -save -e958 */

/*****************************************************************************
  3 函数实现
*****************************************************************************/
/***********************************************************************
函 数 名  : MN_MSG_ReportRcvMsgEvent
功能描述  : 收到一条短信(包括Delliver,Status Report短信),广播上报给所有应用
输入参数  : opId:标识本次操作
            pstDeliverEvt:Deliver短信上报相关内容
输出参数  : 无
返 回 值  : 无
调用函数  :
被调函数  :

修改历史      :
 1.日    期   : 2007年10月26日
   作    者   : z40661
   修改内容   : 新生成函数
************************************************************************/
VOS_VOID MN_MSG_ReportRcvMsgEvent(
    MN_OPERATION_ID_T                   opId,
    const MN_MSG_DELIVER_EVT_INFO_STRU  *pstDeliverEvt
)
{
    PS_MEM_SET(&f_stMsgEventInfo,0X00,sizeof(f_stMsgEventInfo));

    /*广播上报来一条短信*/
    PS_MEM_CPY(&f_stMsgEventInfo.u.stDeliverInfo,pstDeliverEvt,sizeof(f_stMsgEventInfo.u.stDeliverInfo));
    f_stMsgEventInfo.opId = opId;
    f_stMsgEventInfo.clientId = MN_CLIENT_ALL;
    MN_SendClientEvent(MN_CLIENT_ALL,MN_CALLBACK_MSG,MN_MSG_EVT_DELIVER,(VOS_VOID *)&f_stMsgEventInfo);
}


/***********************************************************************
函 数 名  : MN_MSG_ReportSmChanged
功能描述  : 当USIM或NVIM中的短信状态发生了改变时,上报给所有应用
输入参数  : clientId  : 发起该请求的Client的ID
            opId      : Operation ID, 标识本次操作
            bBroadCast:是否是广播上报
            enMemStore:当前的存储器,USIM或NVIM
输出参数  : 无
返 回 值  : 无
调用函数  :
被调函数  :

修改历史      :
 1.日    期   : 2007年10月26日
   作    者   : z40661
   修改内容   : 新生成函数
 2.日    期   : 2011年04月23日
   作    者   : L00171473
   修改内容   : for V7R1 porting, 清除编译WARNING
************************************************************************/
VOS_VOID MN_MSG_ReportSmChanged(
    MN_CLIENT_ID_T                      clientId,
    MN_OPERATION_ID_T                   opId,
    VOS_BOOL                            bBroadCast,
    MN_MSG_MEM_STORE_ENUM_U8            enMemStore
)
{
    MN_OPERATION_ID_T                   bcOpId;
    NAS_OM_SMS_STATICS_STRU             stSmsOmEventPara;
    VOS_UINT32                          ulTempRec;

    PS_MEM_SET(&f_stMsgEventInfo,0X00,sizeof(f_stMsgEventInfo));
    MN_MSG_GetSmStorageList(enMemStore,
                            &f_stMsgEventInfo.u.stStorageListInfo.ulTotalRec,
                            &f_stMsgEventInfo.u.stStorageListInfo.ulUsedRec,
                            f_stMsgEventInfo.u.stStorageListInfo.aulEachStatusRec);
    f_stMsgEventInfo.clientId = clientId;
    f_stMsgEventInfo.opId = opId;
    f_stMsgEventInfo.u.stStorageListInfo.enMemStroe = enMemStore;
    if (VOS_TRUE == bBroadCast)
    {
        MN_SendClientEvent(MN_CLIENT_ALL,
                           MN_CALLBACK_MSG,
                           MN_MSG_EVT_SM_STORAGE_LIST,
                           (VOS_VOID *)&f_stMsgEventInfo);
    }
    else
    {
        MN_SendClientEvent(clientId,
                           MN_CALLBACK_MSG,
                           MN_MSG_EVT_SM_STORAGE_LIST,
                          (VOS_VOID *)&f_stMsgEventInfo);
    }
    stSmsOmEventPara.ucMemType = NAS_SMS_SAVE_AREA_SM;
    stSmsOmEventPara.ucMemCap  = (VOS_UINT8)f_stMsgEventInfo.u.stStorageListInfo.ulTotalRec;
    stSmsOmEventPara.ucMemUsed = (VOS_UINT8)f_stMsgEventInfo.u.stStorageListInfo.ulUsedRec;
    NAS_EventReport(WUEPS_PID_SMS, NAS_OM_EVENT_SMS_STATICS,
                    &stSmsOmEventPara, sizeof(stSmsOmEventPara));

    if (f_stMsgEventInfo.u.stStorageListInfo.ulTotalRec == f_stMsgEventInfo.u.stStorageListInfo.ulUsedRec)
    {
        bcOpId = MN_MSG_GetBCopId();
        f_stMsgEventInfo.opId = bcOpId;
        f_stMsgEventInfo.u.stStorageStateInfo.enMemStroe = enMemStore;

        /* Modified by L00171473 for V7R1 porting, 2011-04-23, begin, 清除编译WARNING */
        ulTempRec = f_stMsgEventInfo.u.stStorageListInfo.ulTotalRec;
        f_stMsgEventInfo.u.stStorageStateInfo.ulTotalRec = ulTempRec;
        ulTempRec = f_stMsgEventInfo.u.stStorageListInfo.ulUsedRec;
        f_stMsgEventInfo.u.stStorageStateInfo.ulUsedRec = ulTempRec;

        if (VOS_TRUE == bBroadCast)
        {
            MN_SendClientEvent(MN_CLIENT_ALL,
                               MN_CALLBACK_MSG,
                               MN_MSG_EVT_STORAGE_FULL,
                               (VOS_VOID *)&f_stMsgEventInfo);
        }
        else
        {
            MN_SendClientEvent(clientId,
                               MN_CALLBACK_MSG,
                               MN_MSG_EVT_STORAGE_FULL,
                               (VOS_VOID *)&f_stMsgEventInfo);
        }
    }


}

/***********************************************************************
函 数 名  : MN_MSG_ReportMemExceed
功能描述  : 当USIM或NVIM中的短信已满,此时收到了一条短信,上报给应用无足够的容量收短信
输入参数  : enMemStore:当前的存储器,USIM或NVIM
输出参数  : 无
返 回 值  : 无
调用函数  :
被调函数  :

修改历史      :
 1.日    期   : 2007年10月26日
   作    者   : z40661
   修改内容   : 新生成函数
************************************************************************/
VOS_VOID MN_MSG_ReportMemExceed(
    MN_OPERATION_ID_T                   opId,
    MN_MSG_MEM_STORE_ENUM_U8            enMemStore
)
{
    MN_INFO_LOG("MN_MSG_ReportMemExceed: step into function.");
    PS_MEM_SET(&f_stMsgEventInfo,0X00,sizeof(f_stMsgEventInfo));
    f_stMsgEventInfo.clientId = MN_CLIENT_ALL;
    f_stMsgEventInfo.opId = opId;
    f_stMsgEventInfo.u.stStorageStateInfo.enMemStroe = enMemStore;
    f_stMsgEventInfo.u.stStorageStateInfo.ulTotalRec = MN_MSG_GetSmCapacity(enMemStore);
    f_stMsgEventInfo.u.stStorageStateInfo.ulUsedRec = f_stMsgEventInfo.u.stStorageStateInfo.ulTotalRec;

    MN_SendClientEvent(MN_CLIENT_ALL,
                       MN_CALLBACK_MSG,
                       MN_MSG_EVT_STORAGE_EXCEED,
                       (VOS_VOID *)&f_stMsgEventInfo);
}

/***********************************************************************
函 数 名  : MN_MSG_ReportDeleteEvent
功能描述  : 上报删除操作结果
输入参数  : clientId  : 发起该请求的Client的ID
            opId      : Operation ID, 标识本次操作
            pstDeleteEvt:删除操作结果
            ulEventType:删除类型
输出参数  : 无
返 回 值  : 无
调用函数  :
被调函数  :

修改历史      :
 1.日    期   : 2007年10月26日
   作    者   : z40661
   修改内容   : 新生成函数
************************************************************************/
VOS_VOID MN_MSG_ReportDeleteEvent(
    MN_CLIENT_ID_T                      clientId,
    MN_OPERATION_ID_T                   opId,
    const MN_MSG_DELETE_EVT_INFO_STRU   *pstDeleteEvt,
    VOS_UINT32                          ulEventType
)
{
    PS_MEM_SET(&f_stMsgEventInfo,0X00,sizeof(f_stMsgEventInfo));
    f_stMsgEventInfo.clientId = clientId;
    f_stMsgEventInfo.opId = opId;
    PS_MEM_CPY(&f_stMsgEventInfo.u.stDeleteInfo,pstDeleteEvt,sizeof(MN_MSG_DELETE_EVT_INFO_STRU));
    MN_SendClientEvent(clientId,MN_CALLBACK_MSG,ulEventType,(VOS_VOID *)&f_stMsgEventInfo);
}

/***********************************************************************
函 数 名  : MN_MSG_ReportDeleteTestEvent
功能描述  : 上报删除操作结果
输入参数  : clientId  : 发起该请求的Client的ID
            opId      : Operation ID, 标识本次操作
            pstDeleteTestEvt:删除命令测试操作结果
            ulEventType:操作类型
输出参数  : 无
返 回 值  : 无
调用函数  :
被调函数  :

修改历史      :
 1.日    期   : 2007年10月26日
   作    者   : z40661
   修改内容   : 新生成函数
************************************************************************/
VOS_VOID MN_MSG_ReportDeleteTestEvent(
    MN_CLIENT_ID_T                      clientId,
    MN_OPERATION_ID_T                   opId,
    const MN_MSG_DELETE_TEST_EVT_INFO_STRU *pstDeleteTestEvt,
    VOS_UINT32                          ulEventType
)
{
    PS_MEM_SET(&f_stMsgEventInfo,0X00,sizeof(f_stMsgEventInfo));
    f_stMsgEventInfo.clientId = clientId;
    f_stMsgEventInfo.opId = opId;
    PS_MEM_CPY(&f_stMsgEventInfo.u.stDeleteTestInfo,pstDeleteTestEvt,sizeof(MN_MSG_DELETE_TEST_EVT_INFO_STRU));
    MN_SendClientEvent(clientId,MN_CALLBACK_MSG,ulEventType,(VOS_VOID *)&f_stMsgEventInfo);
}

/***********************************************************************
函 数 名  : MN_MSG_ReportWriteEvent
功能描述  : 上报写短信操作结果
输入参数  : clientId  : 发起该请求的Client的ID
            opId      : Operation ID, 标识本次操作
            pstDeleteEvt:写短信操作结果
            ulEventType:操作类型
输出参数  : 无
返 回 值  : 无
调用函数  :
被调函数  :

修改历史      :
 1.日    期   : 2007年10月26日
   作    者   : z40661
   修改内容   : 新生成函数
************************************************************************/
VOS_VOID MN_MSG_ReportWriteEvent(
    MN_CLIENT_ID_T                      clientId,
    MN_OPERATION_ID_T                   opId,
    const MN_MSG_WRITE_EVT_INFO_STRU    *pstWriteEvt,
    VOS_UINT32                          ulEventType
)
{
    PS_MEM_SET(&f_stMsgEventInfo,0X00,sizeof(f_stMsgEventInfo));
    f_stMsgEventInfo.clientId = clientId;
    f_stMsgEventInfo.opId = opId;
    PS_MEM_CPY(&f_stMsgEventInfo.u.stWriteInfo,pstWriteEvt,sizeof(MN_MSG_WRITE_EVT_INFO_STRU));
    MN_SendClientEvent(clientId,MN_CALLBACK_MSG,ulEventType,(VOS_VOID *)&f_stMsgEventInfo);
}

/***********************************************************************
函 数 名  : MN_MSG_ReportReadEvent
功能描述  : 上报读短信操作结果
输入参数  : clientId  : 发起该请求的Client的ID
            opId      : Operation ID, 标识本次操作
            pReadEvt:读短信操作结果
            ulEventType:操作类型
输出参数  : 无
返 回 值  : 无
调用函数  :
被调函数  :

修改历史      :
 1.日    期   : 2007年10月26日
   作    者   : z40661
   修改内容   : 新生成函数
************************************************************************/
VOS_VOID MN_MSG_ReportReadEvent(
    MN_CLIENT_ID_T                      clientId,
    MN_OPERATION_ID_T                   opId,
    const MN_MSG_READ_EVT_INFO_STRU     *pReadEvt,
    VOS_UINT32                          ulEventType
)
{
    PS_MEM_SET(&f_stMsgEventInfo,0X00,sizeof(f_stMsgEventInfo));
    f_stMsgEventInfo.clientId = clientId;
    f_stMsgEventInfo.opId = opId;
    PS_MEM_CPY(&f_stMsgEventInfo.u.stReadInfo,pReadEvt,sizeof(MN_MSG_READ_EVT_INFO_STRU));
    MN_SendClientEvent(clientId,MN_CALLBACK_MSG,ulEventType,(VOS_VOID *)&f_stMsgEventInfo);
}

/***********************************************************************
函 数 名  : MN_MSG_ReportListEvent
功能描述  : 上报列表短信操作结果
输入参数  : clientId  : 发起该请求的Client的ID
            opId      : Operation ID, 标识本次操作
            pListEvt:列表短信操作结果
            ulEventType:操作类型
输出参数  : 无
返 回 值  : 无
调用函数  :
被调函数  :

修改历史      :
 1.日    期   : 2007年10月26日
   作    者   : z40661
   修改内容   : 新生成函数
************************************************************************/
VOS_VOID MN_MSG_ReportListEvent(
    MN_CLIENT_ID_T                      clientId,
    MN_OPERATION_ID_T                   opId,
    const MN_MSG_LIST_EVT_INFO_STRU     *pListEvt,
    VOS_UINT32                          ulEventType
)
{
    PS_MEM_SET(&f_stMsgEventInfo,0X00,sizeof(f_stMsgEventInfo));
    f_stMsgEventInfo.clientId = clientId;
    f_stMsgEventInfo.opId = opId;
    PS_MEM_CPY(&f_stMsgEventInfo.u.stListInfo,pListEvt,sizeof(MN_MSG_LIST_EVT_INFO_STRU));
    MN_SendClientEvent(clientId,MN_CALLBACK_MSG,ulEventType,(VOS_VOID *)&f_stMsgEventInfo);
}

/***********************************************************************
函 数 名  : MN_MSG_ReportModifyEvent
功能描述  : 上报修改短信操作结果
输入参数  : clientId  : 发起该请求的Client的ID
            opId      : Operation ID, 标识本次操作
            pModifyStatusEvt:修改短信状态操作结果
            ulEventType:操作类型
输出参数  : 无
返 回 值  : 无
调用函数  :
被调函数  :

修改历史      :
 1.日    期   : 2007年10月26日
   作    者   : z40661
   修改内容   : 新生成函数
************************************************************************/
VOS_VOID MN_MSG_ReportModifyEvent(
    MN_CLIENT_ID_T                           clientId,
    MN_OPERATION_ID_T                        opId,
    const MN_MSG_MODIFY_STATUS_EVT_INFO_STRU *pModifyStatusEvt,
    VOS_UINT32                                ulEventType
)
{
    PS_MEM_SET(&f_stMsgEventInfo,0X00,sizeof(f_stMsgEventInfo));
    f_stMsgEventInfo.clientId = clientId;
    f_stMsgEventInfo.opId = opId;
    PS_MEM_CPY(&f_stMsgEventInfo.u.stModifyInfo,pModifyStatusEvt,sizeof(MN_MSG_MODIFY_STATUS_EVT_INFO_STRU));
    MN_SendClientEvent(clientId,MN_CALLBACK_MSG,ulEventType,(VOS_VOID *)&f_stMsgEventInfo);
}

/***********************************************************************
函 数 名  : MN_MSG_ReportSrvParmEvent
功能描述  : 上报短信参数设置或获取操作结果
输入参数  : clientId  : 发起该请求的Client的ID
            opId      : Operation ID, 标识本次操作
            pstSrvParmEvt:设置或获取短信参数结果
            ulEventType:操作类型
输出参数  : 无
返 回 值  : 无
调用函数  :
被调函数  :

修改历史      :
 1.日    期   : 2007年10月26日
   作    者   : z40661
   修改内容   : 新生成函数
************************************************************************/
VOS_VOID MN_MSG_ReportSrvParmEvent(
    MN_CLIENT_ID_T                       clientId,
    MN_OPERATION_ID_T                    opId,
    const MN_MSG_SRV_PARM_EVT_INFO_STRU *pstSrvParmEvt,
    VOS_UINT32                           ulEventType
)
{
    PS_MEM_SET(&f_stMsgEventInfo,0X00,sizeof(f_stMsgEventInfo));
    f_stMsgEventInfo.clientId = clientId;
    f_stMsgEventInfo.opId = opId;
    PS_MEM_CPY(&f_stMsgEventInfo.u.stSrvParmInfo,pstSrvParmEvt,sizeof(MN_MSG_SRV_PARM_EVT_INFO_STRU));
    MN_SendClientEvent(clientId,MN_CALLBACK_MSG,ulEventType,(VOS_VOID *)&f_stMsgEventInfo);
}

/*****************************************************************************
 函 数 名  : MN_MSG_ReportSentEvent
 功能描述  : 上报消息发送或缓存的结果
 输入参数  : clientId  : 发起该请求的Client的ID
             opId      : Operation ID, 标识本次操作
             pstSendMsgEvt:消息发送或缓存的结果
             ulEventType:操作类型
 输出参数  : 无
 返 回 值  :
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2008年2月19日
    作    者   : 周君 40661
    修改内容   : 新生成函数

*****************************************************************************/
VOS_VOID MN_MSG_ReportSentEvent(
    MN_CLIENT_ID_T                      clientId,
    MN_OPERATION_ID_T                   opId,
    MN_MSG_SENDMSG_EVT_INFO_STRU        *pstSendMsgEvt,
    VOS_UINT32                          ulEventType
)
{
    PS_MEM_SET(&f_stMsgEventInfo,0X00,sizeof(f_stMsgEventInfo));
    f_stMsgEventInfo.clientId = clientId;
    f_stMsgEventInfo.opId = opId;
    PS_MEM_CPY(&f_stMsgEventInfo.u.stSendMsgInfo,pstSendMsgEvt,sizeof(MN_MSG_SENDMSG_EVT_INFO_STRU));
    MN_SendClientEvent(clientId,MN_CALLBACK_MSG,ulEventType,(VOS_VOID *)&f_stMsgEventInfo);
}

/*****************************************************************************
 函 数 名  : MN_MSG_ReportSubmitRptEvent
 功能描述  : 上报消息发送或缓存的结果
 输入参数  : clientId  : 发起该请求的Client的ID
             opId      : Operation ID, 标识本次操作
             pstSubmitRptEvt:接收发送消息的报告
             ulEventType:操作类型
 输出参数  : 无
 返 回 值  :
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2008年2月19日
    作    者   : 周君 40661
    修改内容   : 新生成函数

*****************************************************************************/
VOS_VOID MN_MSG_ReportSubmitRptEvent(
    MN_CLIENT_ID_T                      clientId,
    MN_OPERATION_ID_T                   opId,
    MN_MSG_SUBMIT_RPT_EVT_INFO_STRU     *pstSubmitRptEvt,
    VOS_UINT32                          ulEventType
)
{
    PS_MEM_SET(&f_stMsgEventInfo,0X00,sizeof(f_stMsgEventInfo));
    f_stMsgEventInfo.clientId = clientId;
    f_stMsgEventInfo.opId = opId;
    PS_MEM_CPY(&f_stMsgEventInfo.u.stSubmitRptInfo,
               pstSubmitRptEvt,
               sizeof(f_stMsgEventInfo.u.stSubmitRptInfo));
    MN_SendClientEvent(f_stMsgEventInfo.clientId,MN_CALLBACK_MSG,ulEventType,(VOS_VOID *)&f_stMsgEventInfo);
}
/*****************************************************************************
 函 数 名  : MN_MSG_ReportRcvPathEvent
 功能描述  : 上报设置或获取当前配置路径的结果
 输入参数  : clientId  : 发起该请求的Client的ID
             opId      : Operation ID, 标识本次操作
             bBroadCast:是否需要广播上报
             pRcvPathEvt:当前配置路径的结果
             ulEventType:操作类型
 输出参数  : 无
 返 回 值  :
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2008年2月19日
    作    者   : 周君 40661
    修改内容   : 新生成函数

*****************************************************************************/
VOS_VOID MN_MSG_ReportRcvPathEvent(
    MN_CLIENT_ID_T                         clientId,
    MN_OPERATION_ID_T                      opId,
    VOS_BOOL                               bBroadCast,
    const MN_MSG_RCVMSG_PATH_EVT_INFO_STRU *pRcvPathEvt,
    VOS_UINT32                             ulEventType
)
{
    PS_MEM_SET(&f_stMsgEventInfo,0X00,sizeof(f_stMsgEventInfo));
    f_stMsgEventInfo.clientId = clientId;
    f_stMsgEventInfo.opId = opId;
    PS_MEM_CPY(&f_stMsgEventInfo.u.stRcvMsgPathInfo,pRcvPathEvt,sizeof(MN_MSG_RCVMSG_PATH_EVT_INFO_STRU));
    if (VOS_TRUE == bBroadCast)
    {
        MN_SendClientEvent(MN_CLIENT_ALL,MN_CALLBACK_MSG,ulEventType,(VOS_VOID *)&f_stMsgEventInfo);
    }
    else
    {
        MN_SendClientEvent(clientId,MN_CALLBACK_MSG,ulEventType,(VOS_VOID *)&f_stMsgEventInfo);
    }
}

/*****************************************************************************
 函 数 名  : MN_MSG_ReportMemStatustEvent
 功能描述  : 上报设置或获取当前APP内存使用的结果
 输入参数  : clientId  : 发起该请求的Client的ID
             opId      : Operation ID, 标识本次操作
             bBroadCast:是否是广播上报
             pstMemStatusEvt:当前APP内存情况
             ulEventType:操作类型
 输出参数  : 无
 返 回 值  :
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2008年2月19日
    作    者   : 周君 40661
    修改内容   : 新生成函数

*****************************************************************************/
VOS_VOID MN_MSG_ReportMemStatustEvent(
    MN_CLIENT_ID_T                       clientId,
    MN_OPERATION_ID_T                    opId,
    VOS_BOOL                             bBroadCast,
    const MN_MSG_MEMSTATUS_EVT_INFO_STRU *pstMemStatusEvt,
    VOS_UINT32                           ulEventType
)
{
    PS_MEM_SET(&f_stMsgEventInfo,0X00,sizeof(f_stMsgEventInfo));
    f_stMsgEventInfo.opId = opId;
    f_stMsgEventInfo.clientId = clientId;
    PS_MEM_CPY(&f_stMsgEventInfo.u.stMemStatusInfo,pstMemStatusEvt,sizeof(MN_MSG_MEMSTATUS_EVT_INFO_STRU));
    if (VOS_TRUE == bBroadCast)
    {
        MN_SendClientEvent(MN_CLIENT_ALL,MN_CALLBACK_MSG,ulEventType,(VOS_VOID *)&f_stMsgEventInfo);
    }
    else
    {
        MN_SendClientEvent(clientId,MN_CALLBACK_MSG,ulEventType,(VOS_VOID *)&f_stMsgEventInfo);
    }
}

/***********************************************************************
函 数 名  : MN_MSG_ReportSrvParmChanged
功能描述  : 当USIM或NVIM中的短信参数发生了改变时,上报给所有应用
输入参数  : clientId  :发起该请求的Client的ID
            opId      :Operation ID, 标识本次操作
            enMemStore:当前的存储器,USIM或NVIM
输出参数  : 无
返 回 值  : 无
调用函数  :
被调函数  :

修改历史      :
 1.日    期   : 2007年10月26日
   作    者   : z40661
   修改内容   : 新生成函数
************************************************************************/
VOS_VOID MN_MSG_ReportSrvParmChanged(
    MN_CLIENT_ID_T                      clientId,
    MN_OPERATION_ID_T                   opId,
    MN_MSG_MEM_STORE_ENUM_U8            enMemStore
)
{
    PS_MEM_SET(&f_stMsgEventInfo,0X00,sizeof(f_stMsgEventInfo));

    MN_MSG_GetSmspStorageList(enMemStore,
                               &f_stMsgEventInfo.u.stSrvParmChangeInfo.ulTotalRec,
                               &f_stMsgEventInfo.u.stSrvParmChangeInfo.ulUsedRec,
                               f_stMsgEventInfo.u.stSrvParmChangeInfo.astSrvParm);
    f_stMsgEventInfo.opId = opId;
    f_stMsgEventInfo.clientId = clientId;
    MN_SendClientEvent(MN_CLIENT_ALL,MN_CALLBACK_MSG,MN_MSG_EVT_SRV_PARM_CHANGED,(VOS_VOID *)&f_stMsgEventInfo);
}

/***********************************************************************
函 数 名  : MN_MSG_ReportDeliverErr
功能描述  : MT失败后,广播向应用上报接收短信失败
输入参数  : ucRpStatus:失败的状态
            ucRpCause:失败原因
输出参数  : 无
返 回 值  : 无
调用函数  :
被调函数  :

修改历史      :
 1.日    期   : 2007年10月26日
   作    者   : z40661
   修改内容   : 新生成函数
 2.日    期   : 2013年07月11日
   作    者   : f62575
   修改内容   : V9R1 STK升级项目
************************************************************************/
VOS_VOID MN_MSG_ReportDeliverErr(TAF_MSG_ERROR_ENUM_UINT32 enErrorCode)
{
    MN_OPERATION_ID_T                   bcOpId;

    PS_MEM_SET(&f_stMsgEventInfo,0X00,sizeof(f_stMsgEventInfo));
    /* Modified by f62575 for V9R1 STK升级, 2013-6-26, begin */
    f_stMsgEventInfo.u.stDeliverErrInfo.enErrorCode = enErrorCode;
    /* Modified by f62575 for V9R1 STK升级, 2013-6-26, end */
    bcOpId = MN_MSG_GetBCopId();
    f_stMsgEventInfo.clientId = MN_CLIENT_ALL;
    f_stMsgEventInfo.opId = bcOpId;
    MN_SendClientEvent(MN_CLIENT_ALL,MN_CALLBACK_MSG,MN_MSG_EVT_DELIVER_ERR,(VOS_VOID *)&f_stMsgEventInfo);
}

/***********************************************************************
函 数 名  : MN_MSG_ReportLinkCtrl
功能描述  : 中继链路控制参数设置结果上报
输入参数  : clientId    : 发起该请求的Client的ID
            opId        : Operation ID, 标识本次操作
            ulEventType : 上报事件类型
            ulErrorCode : 错误原因值,MN_ERR_NO_ERROR说明设置成功
            enLinkCtrl  : 当前启用的中继链路控制数据
输出参数  : 无
返 回 值  : 无
调用函数  :
被调函数  :

修改历史      :
 1.日    期   : 2007年10月26日
   作    者   : z40661
   修改内容   : 新生成函数
************************************************************************/
VOS_VOID MN_MSG_ReportLinkCtrl(
    MN_CLIENT_ID_T                      clientId,
    MN_OPERATION_ID_T                   opId,
    VOS_UINT32                          ulEventType,
    VOS_UINT32                          ulErrorCode,
    MN_MSG_LINK_CTRL_U8                 enLinkCtrl
)
{

    PS_MEM_SET(&f_stMsgEventInfo,0X00,sizeof(f_stMsgEventInfo));
    f_stMsgEventInfo.clientId = clientId;
    f_stMsgEventInfo.opId = opId;
    f_stMsgEventInfo.u.stLinkCtrlInfo.ulErrorCode = ulErrorCode;
    f_stMsgEventInfo.u.stLinkCtrlInfo.enLinkCtrl = enLinkCtrl;
    MN_SendClientEvent(clientId,MN_CALLBACK_MSG,ulEventType,(VOS_VOID *)&f_stMsgEventInfo);
    return;
}

/* Added by f62575 for AT Project，2011-10-03,  Begin*/
/*****************************************************************************
 函 数 名  : MN_MSG_ReportResult
 功能描述  : 短信相关设置结果上报
 输入参数  : MN_CLIENT_ID_T       clientId     发起该请求的Client的ID
             MN_OPERATION_ID_T    opId         Operation ID, 标识本次操作
             VOS_UINT32           ulEventType  上报事件类型
             VOS_UINT32           ulErrorCode  错误原因值,MN_ERR_NO_ERROR说明设置成功
 输出参数  : 无
 返 回 值  : VOS_VOID
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2011年10月3日
    作    者   : f62575
    修改内容   : 新生成函数

*****************************************************************************/
VOS_VOID MN_MSG_ReportResult(
    MN_CLIENT_ID_T                      clientId,
    MN_OPERATION_ID_T                   opId,
    VOS_UINT32                          ulEventType,
    VOS_UINT32                          ulErrorCode
)
{
    PS_MEM_SET(&f_stMsgEventInfo,0X00,sizeof(f_stMsgEventInfo));
    f_stMsgEventInfo.clientId                     = clientId;
    f_stMsgEventInfo.opId                         = opId;
    f_stMsgEventInfo.u.stLinkCtrlInfo.ulErrorCode = ulErrorCode;
    MN_SendClientEvent(clientId, MN_CALLBACK_MSG, ulEventType, (VOS_VOID *)&f_stMsgEventInfo);
    return;
}
/* Added by f62575 for AT Project，2011-10-03,  End*/


/*****************************************************************************
 函 数 名  : MN_MSG_SmspInitFinish
 功能描述  : SIM卡中的EFSMSS和EFSMSP初始化完成后,上报USIM卡中相关参数
 输入参数  : 无
 输出参数  : 无

 返 回 值  : 无
 调用函数  :
 被调函数  :
 修改历史      :
  1.日    期   : 2009年02月26日
    作    者   : z40661
    修改内容   : 新生成函数
*****************************************************************************/
VOS_VOID MN_MSG_SmspInitFinish(
    MN_CLIENT_ID_T                      clientId
)
{
    MN_MSG_USIM_POWER_STATE_ENUM_U8     enPowerState;

    MN_MSG_GetUsimPowerState(&enPowerState);

    if(enPowerState < MN_MSG_USIM_POWER_WAIT_EFSMSP)
    {
        return;
    }
    PS_MEM_SET(&f_stMsgEventInfo,0,sizeof(MN_MSG_EVENT_INFO_STRU));

    MN_MSG_GetSmspStorageList(MN_MSG_MEM_STORE_SIM,
                              &f_stMsgEventInfo.u.stInitSmspResultInfo.ulTotalSrvParm,
                              &f_stMsgEventInfo.u.stInitSmspResultInfo.ulUsedSrvParm,
                              f_stMsgEventInfo.u.stInitSmspResultInfo.astSrvParm);

    MN_MSG_GetCurRcvMsgPath(&f_stMsgEventInfo.u.stInitSmspResultInfo.stRcvMsgPath);

    f_stMsgEventInfo.u.stInitSmspResultInfo.enClass0Tailor = MN_MSG_GetClass0Tailor();;

    MN_SendClientEvent(clientId,
                       MN_CALLBACK_MSG,
                       MN_MSG_EVT_INIT_SMSP_RESULT,
                       (VOS_VOID *)&f_stMsgEventInfo);

}

/*****************************************************************************
 函 数 名  : MN_MSG_SmInitFinish
 功能描述  : SIM卡初始化完成后,上报USIM卡中相关参数
 输入参数  : 无
 输出参数  : 无

 返 回 值  : 无
 调用函数  :
 被调函数  :
 修改历史      :
  1.日    期   : 2008年01月18日
    作    者   : z40661
    修改内容   : 新生成函数
  2.日    期   : 2010年6月30日
    作    者   : 傅映君
    修改内容   : 问题单号DTS2010071500596，STK短信的定制缓存
  3.日    期   : 2013年6月26日
    作    者   : f62575
    修改内容   : V9R1 STK升级
  4.日    期   : 2015年03月14日
    作    者   : y00245242
    修改内容   : USIMM卡接口调整
*****************************************************************************/
VOS_VOID MN_MSG_SmInitFinish(
    MN_CLIENT_ID_T                      clientId
)
{
    MN_MSG_USIM_POWER_STATE_ENUM_U8     enPowerState;

#ifndef __PS_WIN32_RECUR__
    if ( (VOS_TRUE == g_ucMnOmConnectFlg)
      && (VOS_TRUE == g_ucMnOmPcRecurEnableFlg) )
    {
        NAS_MSG_SndOutsideContextData_Part1();
        NAS_MSG_SndOutsideContextData_Part2();
        NAS_MSG_SndOutsideContextData_Part3();
    }
#endif

    MN_MSG_GetUsimPowerState(&enPowerState);

    if(MN_MSG_USIM_POWER_ON != enPowerState)
    {
        return;
    }

    /* 清除短信文件要求更新的标志，保证重复接收到REFRESH消息时不会有文件不更新 */
    /* Added by f62575 for V9R1 STK升级, 2013-6-26, begin */
    MN_MSG_SetSmsFileRefreshFlag(USIMM_USIM_EFSMSS_ID, VOS_TRUE);
    MN_MSG_SetSmsFileRefreshFlag(USIMM_USIM_EFSMS_ID, VOS_TRUE);
    MN_MSG_SetSmsFileRefreshFlag(USIMM_USIM_EFSMSP_ID, VOS_TRUE);
    MN_MSG_SetSmsFileRefreshFlag(USIMM_USIM_EFSMSR_ID, VOS_TRUE);
    /* Added by f62575 for V9R1 STK升级, 2013-6-26, end */

    PS_MEM_SET(&f_stMsgEventInfo,0,sizeof(MN_MSG_EVENT_INFO_STRU));

    MN_MSG_GetSmStorageList(MN_MSG_MEM_STORE_SIM,
                            &f_stMsgEventInfo.u.stInitResultInfo.ulTotalSmRec,
                            &f_stMsgEventInfo.u.stInitResultInfo.ulUsedSmRec,
                            f_stMsgEventInfo.u.stInitResultInfo.aulEachStatusRec);


    MN_MSG_GetSmsrStorageList(MN_MSG_MEM_STORE_SIM,
                              &f_stMsgEventInfo.u.stInitResultInfo.ulTotalSmsrRec,
                              &f_stMsgEventInfo.u.stInitResultInfo.ulUsedSmsrRec);

    MN_SendClientEvent(clientId,
                       MN_CALLBACK_MSG,
                       MN_MSG_EVT_INIT_RESULT,
                       (VOS_VOID *)&f_stMsgEventInfo);

    MN_MSG_StartMemNotification();
}

/*****************************************************************************
 函 数 名  : MN_MSG_SmInitFinish
 功能描述  : 隐式软复位时终止AT的阻塞模式
 输入参数  : 无
 输出参数  : 无
 返 回 值  : 无
 调用函数  :
 被调函数  :
 修改历史      :
  1.日    期   : 2009年07月31日
    作    者   : f62575
    修改内容   : 新生成函数
  2.日    期   : 2012年10月10日
    作    者   : f62575
    修改内容   : STK&DCM Project
  3.日    期   : 2012年12月03日
    作    者   : 傅映君/f62575
    修改内容   : DTS2012120305230,FDN和MO SMS CONTROL流程定时器未停止问题；
  4.日    期   : 2013年8月3日
    作    者   : z60575
    修改内容   : TQE修改
  5.日    期   : 2013年08月06日
    作    者   : j00177245
    修改内容   : 清理Coverity
  6.日    期   : 2013年6月26日
    作    者   : f62575
    修改内容   : V9R1 STK升级
*****************************************************************************/
VOS_VOID MN_MSG_FinishMoProc(
    VOS_VOID
)
{
    VOS_UINT32                          i;
    VOS_UINT32                          ulStoreIndex;
    MN_MSG_STORE_MSG_STRU               stStoreMsg;
    MN_MSG_SUBMIT_RPT_EVT_INFO_STRU     stSubmitRptEvt;
    MN_MSG_MO_ENTITY_STRU               stMoEntity;
    VOS_UINT32                          ulTotal;

    PS_MEM_SET(&stSubmitRptEvt,0X00,sizeof(stSubmitRptEvt));

    PS_MEM_SET(&stMoEntity,0x00,sizeof(stMoEntity));

    ulTotal = MN_MSG_GetMoBufferCap();
    for (i = 0; i < ulTotal; i++)
    {
        ulStoreIndex = MN_MSG_GetStoreMsg(&stStoreMsg);
        if (MN_MSG_NO_AVAILABLE_SMS_REC == ulStoreIndex)
        {
            continue;
        }
        else
        {
            if ((MN_MSG_MO_TYPE_MO == stStoreMsg.stMoInfo.enSmsMoType)
             || (MN_MSG_MO_TYPE_BUFFER_STK == stStoreMsg.stMoInfo.enSmsMoType)
             || ((MN_MSG_MO_TYPE_SMMA == stStoreMsg.stMoInfo.enSmsMoType)
              && (VOS_TRUE == stStoreMsg.stMoInfo.bReportFlag)))
            {
                MN_INFO_LOG("MN_MSG_FinishMoProc: Abnormal abort.");
                /* Modified by f62575 for V9R1 STK升级, 2013-6-26, begin */
                stSubmitRptEvt.ucMr                 = stStoreMsg.stMoInfo.ucMr;/*TP-MR*/
                stSubmitRptEvt.enErrorCode          = TAF_MSG_ERROR_NO_SERVICE;
                stSubmitRptEvt.enSaveArea           = stStoreMsg.stMoInfo.enSaveArea;
                stSubmitRptEvt.ulSaveIndex          = stStoreMsg.stMoInfo.ulSaveIndex;
                /* Modified by f62575 for V9R1 STK升级, 2013-6-26, end */
                MN_MSG_ReportSubmitRptEvent(stStoreMsg.stMoInfo.clientId,
                                            stStoreMsg.stMoInfo.opId,
                                            (MN_MSG_SUBMIT_RPT_EVT_INFO_STRU *)&stSubmitRptEvt,
                                            MN_MSG_EVT_SUBMIT_RPT);
            }
            MN_MSG_FreeStoreMsg(ulStoreIndex);
        }

    }

    PS_MEM_SET(&stMoEntity, 0, sizeof(stMoEntity));

    MN_MSG_GetMoEntity(&stMoEntity);
    if ((stMoEntity.enSmaMoState > MN_MSG_MO_STATE_NULL)
     && (stMoEntity.enSmaMoState < MN_MSG_MO_STATE_MAX))
    {
        if (MN_MSG_MO_STATE_WAIT_FDN_CHECK_RSP == stMoEntity.enSmaMoState)
        {
            MN_MSG_StopTimer(MN_MGS_ID_WAIT_FDN_CHECK);
        }

        if (MN_MSG_MO_STATE_WAIT_SMS_CTRL_RSP == stMoEntity.enSmaMoState)
        {
            MN_MSG_StopTimer(MN_MGS_ID_WAIT_MO_SMS_CTRL_CHECK);
        }

        MN_INFO_LOG("MN_MSG_FinishMoProc: fail to mo.");
        stSubmitRptEvt.ucMr = stMoEntity.ucMr;/*TP-MR*/
        /* Modified by f62575 for V9R1 STK升级, 2013-6-26, begin */
        stSubmitRptEvt.enErrorCode          = TAF_MSG_ERROR_NO_SERVICE;
        stSubmitRptEvt.enSaveArea           = stMoEntity.enSaveArea;
        stSubmitRptEvt.ulSaveIndex          = stMoEntity.ulSaveIndex;
        /* Modified by f62575 for V9R1 STK升级, 2013-6-26, end */
        MN_MSG_ReportSubmitRptEvent(stMoEntity.clientId,
                                    stMoEntity.opId,
                                    (MN_MSG_SUBMIT_RPT_EVT_INFO_STRU *)&stSubmitRptEvt,
                                    MN_MSG_EVT_SUBMIT_RPT);
        MN_MSG_DestroyMoInfo();
    }

    return;

}

/*lint -restore */


#ifdef  __cplusplus
  #if  __cplusplus
  }
  #endif
#endif

