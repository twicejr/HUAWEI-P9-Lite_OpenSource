


#ifdef __cplusplus
#if __cplusplus
extern "C" {
#endif
#endif


/*****************************************************************************
  1 Include HeadFile
*****************************************************************************/
#include "dhcp_inc.h"
#include "dhcpc_def.h"
#include "dhcpv4s_def.h"
#include "dhcpv4s_type.h"
#include "dhcpv4s_fun.h"



/*****************************************************************************
    协议栈打印打点方式下的.C文件宏定义
*****************************************************************************/
/*lint -e767*/
#define    THIS_FILE_ID          PS_FILE_ID_DHCPV4S_PUB_C
/*lint +e767*/

/*****************************************************************************
 函 数 名      : DHCPS_FSM_REQUESTIP_AddressAllocateFailed
 功能描述   : 不回应响应消息给UE（协议中描述：
                            If no address is available, the server may choose to report the problem to
                            the system administrator. ）
                            此处协议DHCP协议
                            （RFC2131中规定还要发送ICMP ECHO消息，
                            我们的设备自己保证地址分配的正常，
                            不需要发送此消息）。
                            状态由RequestIP -> IDEL。
 输入参数   : 无
 输出参数   : 无
 返 回 值      : VOS_OK    成功; VOS_ERR    失败
 调用函数   :
 被调函数   :

 修改历史        :
  1.日    期     : 2013年04月25日
    作    者     : guolixian 00171003
    修改内容     : 新生成函数

*****************************************************************************/
ULONG DHCPS_FSM_REQUESTIP_AddressAllocateFailed(
          DHCPS_PRE_RESULT_S *pstPreResult, DHCPS_STATE_RET *pstStateChangeRet)
{
    return VOS_OK;
}

/*****************************************************************************
 函 数 名      : DHCPS_FSM_REQUESTIP_Deactive
 功能描述   : USM发送的去活消息，
                           DHCPS模块删除地址租约消息，
                           每次去活用户都发给DHCP。
                           不用通知USM。
 输入参数   : 无
 输出参数   : 无
 返 回 值      : VOS_OK    成功; VOS_ERR    失败
 调用函数   :
 被调函数   :

 修改历史        :
  1.日    期     : 2013年04月25日
    作    者     : guolixian 00171003
    修改内容     : 新生成函数

*****************************************************************************/
ULONG DHCPS_FSM_REQUESTIP_Deactive(  DHCPS_PRE_RESULT_S *pstPreResult,
                                                  DHCPS_STATE_RET *pstStateChangeRet)
{
    return VOS_OK;
}

/*****************************************************************************
 函 数 名      : DHCPS_FSM_REQUESTIP_USMTimerOut
 功能描述   : 不回应响应消息给UE（协议中描述：
                            If no address is available, the server may choose to report the problem
                            to the system administrator. ）
                            此处协议DHCP协议
                            （RFC2131中规定还要发送ICMP ECHO消息，
                            我们的设备自己保证地址分配的正常，
                            不需要发送此消息）
                            状态切换到idel。
 输入参数   : 无
 输出参数   : 无
 返 回 值      : VOS_OK    成功; VOS_ERR    失败
 调用函数   :
 被调函数   :

 修改历史        :
  1.日    期     : 2013年04月25日
    作    者     : guolixian 00171003
    修改内容     : 新生成函数

*****************************************************************************/
ULONG DHCPS_FSM_REQUESTIP_USMTimerOut(
          DHCPS_PRE_RESULT_S *pstPreResult,DHCPS_STATE_RET *pstStateChangeRet)
{
    return VOS_OK;
}

ULONG DHCPS_FSM_OFFERED_ReceiveDiscover(DHCPS_PRE_RESULT_S *pstPreResult,
                                        DHCPS_STATE_RET *pstStateChangeRet)
{
    return VOS_OK;
}

ULONG DHCPS_FSM_OFFERED_ReceiveRequest(DHCPS_PRE_RESULT_S *pstPreResult,
                                  DHCPS_STATE_RET *pstStateChangeRet)
{
    return VOS_OK;
}
ULONG DHCPS_FSM_OFFERED_ReceiveDecline(
                                                                          DHCPS_PRE_RESULT_S *pstPreResult,
                                                                          DHCPS_STATE_RET *pstStateChangeRet)
{
    return VOS_OK;
}
ULONG DHCPS_FSM_OFFERED_ReceiveRelease(
                                                                          DHCPS_PRE_RESULT_S *pstPreResult,
                                                                          DHCPS_STATE_RET *pstStateChangeRet)
{
    return VOS_OK;
}
ULONG DHCPS_FSM_OFFERED_Deactive(
                                                                          DHCPS_PRE_RESULT_S *pstPreResult,
                                                                          DHCPS_STATE_RET *pstStateChangeRet)
{
    return VOS_OK;
}
ULONG DHCPS_FSM_OFFERED_ClientTimerOut(
                                                                          DHCPS_PRE_RESULT_S *pstPreResult,
                                                                          DHCPS_STATE_RET *pstStateChangeRet)
{
    return VOS_OK;
}

ULONG DHCPS_FSM_COMMITED_ReceiveDiscover(
                                                                          DHCPS_PRE_RESULT_S *pstPreResult,
                                                                          DHCPS_STATE_RET *pstStateChangeRet)
{
    return VOS_OK;
}

ULONG DHCPS_FSM_COMMITED_ReceiveRequest(
                                                                          DHCPS_PRE_RESULT_S *pstPreResult,
                                                                          DHCPS_STATE_RET *pstStateChangeRet)
{
    return VOS_OK;
}
ULONG DHCPS_FSM_COMMITED_ReceiveDecline(
                                                                          DHCPS_PRE_RESULT_S *pstPreResult,
                                                                          DHCPS_STATE_RET *pstStateChangeRet)
{
    return VOS_OK;
}
ULONG DHCPS_FSM_COMMITED_ReceiveRelease(
                                                                          DHCPS_PRE_RESULT_S *pstPreResult,
                                                                          DHCPS_STATE_RET *pstStateChangeRet)
{
    return VOS_OK;
}
ULONG DHCPS_FSM_COMMITED_ReceiveInform(DHCPS_PRE_RESULT_S *pstPreResult,
                                       DHCPS_STATE_RET *pstStateChangeRet)
{
    return VOS_OK;
}
ULONG DHCPS_FSM_COMMITED_ReceiveDeactive(
                                                                          DHCPS_PRE_RESULT_S *pstPreResult,
                                                                          DHCPS_STATE_RET *pstStateChangeRet)
{
    return VOS_OK;
}

ULONG DHCPS_FSM_COMMITED_LeaseTimerOut(
                                                                          DHCPS_PRE_RESULT_S *pstPreResult,
                                                                          DHCPS_STATE_RET *pstStateChangeRet)
{
    return VOS_OK;
}

/*****************************************************************************
 函 数 名      : DHCPS_FSM_RELAY_ReceiveRelease
 功能描述   :    收到从UE过来的DHCP Release消息，
                 转发给PGW，
                 同时通知USM释放，
                 然后删除控制块
 输入参数   : 无
 输出参数   : 无
 返 回 值      : VOS_OK    成功; VOS_ERR    失败
 调用函数   :
 被调函数   :

 修改历史        :
  1.日    期     : 2013年04月25日
    作    者     : guolixian 00171003
    修改内容     : 新生成函数

*****************************************************************************/
ULONG DHCPS_FSM_RELAY_ReceiveRelease(
              DHCPS_PRE_RESULT_S *pstPreResult, DHCPS_STATE_RET *pstStateChangeRet)
{
    return VOS_OK;
}

/*****************************************************************************
 函 数 名      : DHCPS_FSM_RELAY_ReceiveDecline
 功能描述   :    收到从UE过来的DHCP Decline消息，
                 转发给PGW，
                 同时通知USM释放，
                 然后删除控制块
 输入参数   : 无
 输出参数   : 无
 返 回 值      : VOS_OK    成功; VOS_ERR    失败
 调用函数   :
 被调函数   :

 修改历史   :
  1.日    期      : 2008年12月29日
    作    者       : zhangyang 00142225
    修改内容: 新生成函数

*****************************************************************************/
ULONG DHCPS_FSM_RELAY_ReceiveDecline(
                                                                          DHCPS_PRE_RESULT_S *pstPreResult,
                                                                          DHCPS_STATE_RET *pstStateChangeRet)
{
    return VOS_OK;
}

/*****************************************************************************
 函 数 名      : DHCPS_FSM_RELAY_ReceiveRelease
 功能描述   :    收到USM的去活消息，删除控制块
 输入参数   : 无
 输出参数   : 无
 返 回 值      : VOS_OK    成功; VOS_ERR    失败
 调用函数   :
 被调函数   :

 修改历史        :
  1.日    期     : 2013年04月25日
    作    者     : guolixian 00171003
    修改内容     : 新生成函数

*****************************************************************************/
ULONG DHCPS_FSM_RELAY_ReceiveDeactive(
            DHCPS_PRE_RESULT_S *pstPreResult, DHCPS_STATE_RET *pstStateChangeRet)
{
    return VOS_OK;
}

/*****************************************************************************
 函 数 名      : DHCPS_FSM_IDEL_ReceiveDiscover
 功能描述   : 通知USM申请IP地址，起USM定时器1进行等待，
                            同时置租约控制块的标志位，成功后状态由
                            IDLE－－>REQUESTIP。
 输入参数   : 无
 输出参数   : 无
 返 回 值      : VOS_OK    成功; VOS_ERR    失败
 调用函数   :
 被调函数   :

 修改历史        :
  1.日    期     : 2013年04月25日
    作    者     : guolixian 00171003
    修改内容     : 新生成函数

*****************************************************************************/
ULONG DHCPS_FSM_IDLE_ReceiveDiscover(DHCPS_PRE_RESULT_S *pstPreResult,
                                     DHCPS_STATE_RET *pstStateChangeRet)
{
    return VOS_OK;
}

/*****************************************************************************
 函 数 名        : DHCPS_FSM_IDEL_ReceiveRequest
 功能描述        : 通知USM申请IP地址，起USM定时器1进行等待，
                            同时置租约控制块的标志位，成功后状态由
                            IDLE－－>REQUESTIP。
 输入参数        : 无
 输出参数        : 无
 返 回 值        : VOS_OK    成功; VOS_ERR    失败
 调用函数        :
 被调函数        :

 修改历史        :
  1.日    期     : 2013年04月25日
    作    者     : guolixian 00171003
    修改内容     : 新生成函数

*****************************************************************************/
ULONG DHCPS_FSM_IDEL_ReceiveRequest(DHCPS_PRE_RESULT_S *pstPreResult,
                                    DHCPS_STATE_RET *pstStateChangeRet)
{
    return VOS_OK;
}
/*****************************************************************************
 函 数 名      : DHCPS_FSM_IDEL_ReceiveDiscover
 功能描述   : 清除租约信息，释放资源
 输入参数   : 无
 输出参数   : 无
 返 回 值      : VOS_OK    成功; VOS_ERR    失败
 调用函数   :
 被调函数   :

 修改历史   :
  1.日    期      : 2008年11月27日
    作    者       : dongmingzhou 42828
    修改内容: 新生成函数

*****************************************************************************/
ULONG DHCPS_FSM_IDLE_ReceiveRelease(
                                                                             DHCPS_PRE_RESULT_S *pstPreResult,
                                                                             DHCPS_STATE_RET *pstStateChangeRet)
{
    return VOS_OK;
}

/*****************************************************************************
 函 数 名      : DHCPS_FSM_REQUESTIP_ReceiveRelease
 功能描述   : 收到Release消息(按说不应该收到的)，
                            不回应响应消息给UE  ，
                            状态切换到IDEL，
                            REQUESTIP-->IDLE。
 输入参数   : 无
 输出参数   : 无
 返 回 值      : VOS_OK    成功; VOS_ERR    失败
 调用函数   :
 被调函数   :

 修改历史   :
  1.日    期      : 2008年11月27日
    作    者       : dongmingzhou 42828
    修改内容: 新生成函数

*****************************************************************************/
ULONG DHCPS_FSM_REQUESTIP_ReceiveRelease(
                                                                          DHCPS_PRE_RESULT_S *pstPreResult,
                                                                          DHCPS_STATE_RET *pstStateChangeRet)
{
    return VOS_OK;
}

/*****************************************************************************
 函 数 名      : DHCPS_FSM_REQUESTIP_AddressAllocateSuccess
 功能描述   : 发送OFFER消息给SGW，
                           启动等待Request消息的定时器2，
                           状态由REQUESTIP－－>OFFERED。
                           本地保存地址记录信息，
 输入参数   : 无
 输出参数   : 无
 返 回 值      : VOS_OK    成功; VOS_ERR    失败
 调用函数   :
 被调函数   :

 修改历史   :
  1.日    期      : 2008年11月27日
    作    者       : dongmingzhou 42828
    修改内容: 新生成函数

*****************************************************************************/
ULONG DHCPS_FSM_REQUESTIP_AddressAllocateSuccess(
                                                                          DHCPS_PRE_RESULT_S *pstPreResult,
                                                                          DHCPS_STATE_RET *pstStateChangeRet)
{
    return VOS_OK;
}

/*=======================================================================
 *  函数名称:  ICMPv6_CheckSum
 *  初稿完成:  2004/07/30
 *  作    者:    屈琴
 *  函数功能:  计算ICMPv6报文的校验和
 *                           ptr参数指向的报文会被覆盖，请注意需要事先保存
 *  输入参数:
 *  输出参数:  无
 *  返回类型:
 *  全局变量:
 *  其他说明:  无
 *  调用函数:
 *  主调函数:   IPV6_TimerOutProc
 *=======================================================================*/
USHORT ICMPv6_CheckSum(UCHAR *ptr, const in6_addr src, const in6_addr des, const UCHAR *msg,
                                                    USHORT usLen, USHORT *pusCheckSum, UCHAR ucPro)
{
    return VOS_OK;
}

ULONG UGW_GtpEncap( PMBUF_S *pMbuf, ULONG ulPdpIndex )
{
    return 0;
}

/*****************************************************************************
 函 数 名        : UGW_GRE_Encap
 功能描述        :

 输入参数        : 无
 输出参数        : 无
 返 回 值        : VOS_OK    成功; VOS_ERR    失败
 调用函数        :
 被调函数        :

 修改历史        :
  1.日    期     : 2009年08月12日
    作    者     : zhangyang 00142225
    修改内容     : 新生成函数

*****************************************************************************/
ULONG UGW_GRE_Encap(PMBUF_S *pMbuf, ULONG ulPdpIndex )
{
    return VOS_OK;
}

/*****************************************************************************
 函 数 名  : AM_CtxApiGetApnInfo
 功能描述  : 获取apn信息
 输入参数  : ULONG ulPdpIdx
 输出参数  : AM_CTX_APN_INFO_S *pstApnInfo
 返 回 值  : VOS_OK/VOS_ERR
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2013年5月14日
    作    者   : h50774
    修改内容   : 新生成函数

*****************************************************************************/
ULONG AM_CtxApiGetApnInfo( ULONG ulPdnIndex, AM_CTX_APN_INFO_S *pstApnInfo)
{
    return VOS_OK;
}

VOID UGW_OmAccessMsgTrc(UCHAR *pMsg,
                      E_TRACE_TYPE enTraceType,
                      ULONG  ulMsgClass,
                      ULONG  ulGtpMsgType,
                      ULONG  ulPeerIpAddr,
                      USHORT usMsgLen)
{
    return;
}

VOID GTPC_OmExternInterfaceTrcProcess(UCHAR *pMsg, E_TRACE_TYPE enTraceType, UGW_EXTERN_INTF_TRACE_S stTraceInfo)
{
    return;
}

/*****************************************************************************
 函 数 名  : AM_CtxApiGetReqApnIndexByPdpContext
 功能描述  : AM提供给其他模块使用，按照上下文获取到对应的请求的apnindex
 输入参数  : ULONG ulPdpindex
             USHORT *pusRequestIndex
             UCHAR *pucAliaApnFlag
 输出参数  : 无
 返 回 值  : VOID
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2014年4月29日
    作    者   : p00114481
    修改内容   : 新生成函数

*****************************************************************************/
VOID AM_CtxApiGetReqApnIndexByPdpContext(SDB_GSPU_CONTEXT_S *pstContext,USHORT *pusRequestIndex,UCHAR *pucAliaApnFlag)
{
    return;
}

/*****************************************************************************
 函 数 名   : IPV6_SrcAddrValidationCheck
 功能描述   : ipv6的ns或rs或dhcp包原地址合法性检查
 输入参数   : USHORT usApnIndex
 输出参数   :
 返 回 值   :

 调用函数   :
 被调函数   :

 修改历史   :
 1.日    期 : 2012年02月01日
   作    者 : zhangjinquan
   修改内容 : 新增函数  DTS2012011006447 ipv6模块进行源地址类型检查
*****************************************************************************/
ULONG IPV6_SrcAddrValidationCheck(IPV6HDR_S *pstIpv6Hdr)
{
    return VOS_OK;
}

PF_ULONG fwd_get_ctrlhdr_pdpindex(FWD_TO_CTRL_HDR* pstCtrlHdr)
{
    return pstCtrlHdr->ulPdpIndex;
}

/*****************************************************************************
 函 数 名  : LAP_SetPrefixLengthIp
 功能描述  : 根据前缀长度设置前缀长度外的部分为0，本函数不做入参校验，由调用函数保证
 输入参数  : ULONG aulOldIp[], UCHAR ucPrefixLength
 输出参数  : ULONG aulNewIp[], UCHAR *pucPos, UCHAR *pucMoveBitNum
 返 回 值  : 无
 调用函数  :
 被调函数  : LAP1_GetIpv6Prefix

 修改历史      :
  1.日    期   : 2012-08-01
    作    者   : zhangjinquan 00175135
    修改内容   : 新生成函数 zhangjinquan 00175135 IPv6 Prefix Delegation特性 2012-08-01

*****************************************************************************/
VOID LAP_SetPrefixLengthIp(ULONG aulOldIp[], UCHAR ucPrefixLength, ULONG aulNewIp[],
                            UCHAR *pucPos, UCHAR *pucMoveBitNum)
{
    return;
}

/*****************************************************************************
 函 数 名  : PTM_DebugBatchSProcDebugCmdRspMsg
 功能描述  : ptm批量执行命令服务器侧处理客户端响应消息
 输入参数  : UCHAR *pucMsg
 输出参数  : 无
 返 回 值  : ULONG
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2013年1月11日
    作    者   : y00138047
    修改内容   : 新生成函数

*****************************************************************************/
ULONG PTM_DebugBatchSProcDebugCmdRspMsg(UCHAR *pucMsg)
{
    return VOS_OK;
}

/*****************************************************************************
 函 数 名  : CLAP_TaskInit
 功能描述  : CLAP初始化函数， 挂在CLAP任务，用于PDP上下文的地址核查
 输入参数  : VOS_UINT64 ullCsi
             ULONG ulHandle
 输出参数  : 无
 返 回 值  : extern VOS_UINT32
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2013年12月3日
    作    者   : mengyuanhui 00221593
    修改内容   : 新生成函数

*****************************************************************************/
VOS_UINT32 CLAP_TaskInit(VOS_UINT64 ullCsi, ULONG ulHandle)
{
    return VOS_OK;
}

/*****************************************************************************
 函 数 名      : DHCPS_FSM_PreMsgFromUSM
 功能描述   : 预处理从USM收到的消息，包括:申请地址成功，
                            申请地址失败，取活用户。
 输入参数   : 无
 输出参数   : 无
 返 回 值      : VOS_OK    成功; VOS_ERR    失败
 调用函数   :
 被调函数   :

 修改历史   :
  1.日    期      : 2008年12月5日
    作    者       : dongmingzhou 42828
    修改内容: 新生成函数

*****************************************************************************/
VOID DHCPS_FSM_PreMsgFromUSM(UCHAR *pucRspMsg)
{
    return;
}

/*****************************************************************************
 函 数 名  : CLAP_TaskConfirm
 功能描述  : 挂在CLAP任务,必要资源申请，回调注册、定时器等，用于PDP上下文的地址核查
 输入参数  : ULONG ulTaskID
 输出参数  : 无
 返 回 值  : extern ULONG
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2013年12月3日
    作    者   : mengyuanhui 00221593
    修改内容   : 新生成函数

*****************************************************************************/
ULONG CLAP_TaskConfirm(ULONG ulTaskID)
{
    return VOS_OK;
}

/*****************************************************************************
 函 数 名  : CLAP_TaskProcess
 功能描述  : CLAP的消息处理函数，用于PDP上下文的地址核查
 输入参数  : VOID
 输出参数  : 无
 返 回 值  : extern VOID
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2013年12月3日
    作    者   : mengyuanhui 00221593
    修改内容   : 新生成函数

*****************************************************************************/
VOID CLAP_TaskProcess()
{
    return;
}

/*****************************************************************************
 函 数 名  : Path_GetVpn
 功能描述  : 根据地址获取逻辑接口绑定的vpn索引
 输入参数  : SDB_GSPU_CONTEXT_S *pstContext, ULONG *pulVpnId
 输出参数  : 无
 返 回 值  : VOID
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2012年5月31日
    作    者   : jixiaoming 00180244
    修改内容   : 新生成函数

*****************************************************************************/
VOID Path_GetVpn(SDB_GSPU_CONTEXT_S *pstContext, ULONG *pulVpnId)
{
    return;
}




#ifdef __cplusplus
    #if __cplusplus
        }
    #endif
#endif


