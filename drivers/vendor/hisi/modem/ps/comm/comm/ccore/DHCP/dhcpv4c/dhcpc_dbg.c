/******************************************************************************

                  版权所有 (C), 2001-2011, 华为技术有限公司

 ******************************************************************************
  文 件 名   : dhcpc_dbg.c
  版 本 号   : 初稿
  作    者   : yuqingping(25027)
  生成日期   : 2002年11月21日
  最近修改   :
  功能描述   : dhcpc模块的调试函数
  函数列表   :
  修改历史   :
  1.日    期   : 2002年11月21日
    作    者   : yuqingping(25027)
    修改内容   : 创建文件

******************************************************************************/
#include "dhcp_inc.h"
#include "dhcpc_def.h"
#include "dhcpc.h"
#include "dhcpc_cdb.h"
#include "dhcpc_func.h"
#include "dhcpc_table.h"
#include "dhcpv6c_pkt.h"
#include "dhcpv6c_fsm.h"
#include "dhcpc_var.h"
#include "dhcpc_comp.h"
#include "dhcpc_dbg.h"
#if 0
#include "dhcpm_interface.h"
#endif

/*****************************************************************************
    协议栈打印打点方式下的.C文件宏定义
*****************************************************************************/
/*lint -e767*/
#define    THIS_FILE_ID          PS_FILE_ID_DHCPC_DBG_C
/*lint +e767*/

/*delete by m00221573 for 全文件pclint 2012-10-15*/

ULONG g_ulDhcpcPrintLevel = 0;  /*串口输出的级别*/

/*调试计数*/
ULONG g_ulDHCPV6CDbgCnt[E_DHCPV6C_END] = {0};

UCHAR g_ucDHCPV6CDbgCntName[E_DHCPV6C_END][60] =
{
    "E_DHCPV6C_MSGLEN_ERR               ",

    "E_DHCPV6C_NO_CI                    ",
    "E_DHCPV6C_CIDUID_TYPE_ERR          ",
    "E_DHCPV6C_CIDUID_ENTERNUM_ERR      ",
    "E_DHCPV6C_CIDUID_LEN_ERR           ",
    "E_DHCPV6C_CIDUID_DATA_ERR          ",

    "E_DHCPV6C_NO_SI                    ",
    "E_DHCPV6C_SIDUID_LEN_ERR           ",
    "E_DHCPV6C_SIDUID_LEN2_ERR          ",
    "E_DHCPV6C_SIDUID_TYPE_ERR          ",
    "E_DHCPV6C_SIDUID_DATA_ERR          ",

    "E_DHCPV6C_NO_IANA                  ",
    "E_DHCPV6C_IANA_LEN_ERR             ",
    "E_DHCPV6C_IANA_TEIDC_ERR           ",
    "E_DHCPV6C_IANA_T1T2_ERR            ",
    "E_DHCPV6C_IANA_T1T2_ERR_2          ",

    "E_DHCPV6C_NO_IAADDR                ",
    "E_DHCPV6C_IAADDR_LEN_ERR           ",
    "E_DHCPV6C_IAADDR_TIME_ERR          ",
    "E_DHCPV6C_IAADDR_DATA_ERR          ",

    "E_DHCPV6C_NO_DNS                   ",
    "E_DHCPV6C_DNS_LEN_ERR              ",
    "E_DHCPV6C_DNS_MAIN_ERR             ",
    "E_DHCPV6C_DNS_SECD_ERR             ",
    "E_DHCPV6C_DNS_SAME                 ",

    "E_DHCPV6C_STATUSCODE_LEN_ERR       ",
    "E_DHCPV6C_STATUSCODE_NOADDR        ",
    "E_DHCPV6C_STATUSCODE_UNSPECFAIL    ",
    "E_DHCPV6C_STATUSCODE_UNSPECFAIL_2  ",
    "E_DHCPV6C_STATUSCODE_USEMULTICAST  ",
    "E_DHCPV6C_STATUSCODE_NOBIND        ",

    "E_DHCPV6C_TID_EXHAUST              ",
    "E_DHCPV6C_SEQNUM_REMAIN            ",
    "E_DHCPV6C_SERVER_NO_RSP            ",

    "E_DHCPV6C_ALLOC_MBUF_ERR           ",
    "E_DHCPV6C_COPY_MBUF_ERR            ",
    "E_DHCPV6C_UDPOUT_ERR               ",

    "E_DHCPV6C_REV_SERVER_MSG           ",
    "E_DHCPV6C_REV_ADVERTISE_MSG        ",
    "E_DHCPV6C_REV_REPLY_MSG            ",
    "E_DHCPV6C_REV_SERVER_OTHER_MSG     ",

    "E_DHCPV6C_FSM_PRE_PROC_ENTER       ",
    "E_DHCPV6C_FSM_PRE_PROC_OK          ",

    "E_DHCPV6C_REQUEST_RCV_UNEXCEPT_MSG ",
    "E_DHCPV6C_REQUEST_ADDR_NOT_EQUAL   ",
    "E_DHCPV6C_REQUEST_T1T2_NOT_EQUAL   ",
    "E_DHCPV6C_REQUEST_LEASE_NOT_EQUAL  ",
    "E_DHCPV6C_REL_DEC_RCV_UNEXCEPT_MSG ",
    "E_DHCPV6C_RENEW_RCV_UNEXCEPT_MSG   ",
    "E_DHCPV6C_RENEW_ADDR_NOT_EQUAL     ",
    "E_DHCPV6C_RENEW_VALID_TIME_IS_0    ",
    "E_DHCPV6C_FSM_RCV_UNEXCEPT_MSG     ",

    "E_DHCPV6C_SEND_PACKET_ENTER        ",
    "E_DHCPV6C_SEND_PKT_SELECT_SVR_FAIL ",

    "E_DHCPV6C_SEND_SOLICIT_OK          ",
    "E_DHCPV6C_SEND_REQUEST_OK          ",
    "E_DHCPV6C_SEND_RENEW_OK            ",
    "E_DHCPV6C_SEND_RELEASE_OK          ",
    "E_DHCPV6C_SEND_DECLINE_OK          ",
    "E_DHCPV6C_SEND_SERVER_OTHER_OK     ",
    "E_DHCPV6C_SEND_PACKET_OK           ",

    "E_DHCPV6C_SEND_SOLICIT_ERR         ",
    "E_DHCPV6C_SEND_REQUEST_ERR         ",
    "E_DHCPV6C_SEND_RENEW_ERR           ",
    "E_DHCPV6C_SEND_RELEASE_ERR         ",
    "E_DHCPV6C_SEND_DECLINE_ERR         ",
    "E_DHCPV6C_SEND_SERVER_OTHER_ERR    ",

    "E_DHCPV6C_REV_LAP_REQ_MSG          ",
    "E_DHCPV6C_REV_LAP_RELEASE_MSG      ",
    "E_DHCPV6C_REV_LAP_CONFLICT_MSG     ",
    "E_DHCPV6C_REV_LAP_CONFLICT_FAIL    ",

    "E_DHCPV6C_SEND_LAP_SUCCESS_OK      ",
    "E_DHCPV6C_SEND_LAP_FAIL_OK         ",
    "E_DHCPV6C_SEND_LAP_REL_OK          ",
    "E_DHCPV6C_SEND_LAP_SVR_NO_RSP_OK   ",
    "E_DHCPV6C_SEND_LAP_OTHER_OK        ",

    "E_DHCPV6C_SEND_LAP_SUCCESS_ERR     ",
    "E_DHCPV6C_SEND_LAP_SUCCESS_ERR     ",
    "E_DHCPV6C_SEND_LAP_REL_ERR         ",
    "E_DHCPV6C_SEND_LAP_SVR_NO_RSP_ERR  ",
    "E_DHCPV6C_SEND_LAP_OTHER_ERR       ",

    "E_DHCPV6C_CREAT_CONTEXT_FAIL       ",
    "E_DHCPV6C_INIT_CONTEXT_FAIL        ",
    "E_DHCPV6C_CONTEXT_EXIST_FAIL       ",
    "E_DHCPV6C_FIND_SDB_FAIL            ",
    "E_DHCPV6C_UNPACKET_FAIL            ",
    "E_DHCPV6C_SERVER_QRY_TEIDC_FAIL    ",
    "E_DHCPV6C_SERVER_QRY_CONTEXT_FAIL  ",
    "E_DHCPV6C_LAPREL_QRY_CONTEXT_FAIL  ",

    "E_DHCPV6C_FSM_START_T1_FAIL        ",
    "E_DHCPV6C_FSM_START_T2_FAIL        ",
    "E_DHCPV6C_FSM_START_LEASE_TM_FAIL  ",
    "E_DHCPV6C_FSM_BOUNDIP_START_TM_FAIL",
    "E_DHCPV6C_FSM_START_RESEND_TM_FAIL ",
    "E_DHCPV6C_FSM_1ST_BOUNDIP_FAIL     ",
    "E_DHCPV6C_FSM_SND_LAP_SUCC_FAIL    ",
    "E_DHCPV6C_FSM_RNEW_QUERY_PDP_FAIL  ",

    "E_DHCPV6C_FSM_REQ_IP_SUCC          ",
    "E_DHCPV6C_FSM_RENEW_IP_SUCC        ",
    "E_DHCPV6C_FSM_BOUNDIP_SUCC         ",

    "E_DHCPV6C_BLK_MALLOC_NUM           ",
    "E_DHCPV6C_BLK_CRT_NUM              ",
    "E_DHCPV6C_BLK_CRT_INPUT_NULL       ",
    "E_DHCPV6C_BLK_CRTNEW_NOTMALLOC     ",
    "E_DHCPV6C_BLK_CRTNEW_MALLOC        ",
    "E_DHCPV6C_BLK_CRTNEW_MALLOC_FAIL   ",
    "E_DHCPV6C_BLK_MANAGE_INPUT_NULL    ",
    "E_DHCPV6C_BLK_INSERTIDLE_NUM       ",
    "E_DHCPV6C_BLK_INSERTIDLE_INPUT_NULL",
    "E_DHCPV6C_BLK_INSERTWAIT_NUM       ",
    "E_DHCPV6C_BLK_INSERTWAIT_INPUT_NULL",
    "E_DHCPV6C_BLK_CRT_CRTNEW_FAIL      ",
    "E_DHCPV6C_BLK_CRT_GETBLK_FAIL      ",
    "E_DHCPV6C_BLK_QRY_INPUT_NULL       ",
    "E_DHCPV6C_BLK_QRY_OK               ",
    "E_DHCPV6C_BLK_QRY_FAIL             ",
    "E_DHCPV6C_BLK_ADD_NUM              ",
    "E_DHCPV6C_BLK_ADD_INPUT_NULL       ",
    "E_DHCPV6C_BLK_ADD_CONFLICT         ",
    "E_DHCPV6C_BLK_DEL_NUM              ",
    "E_DHCPV6C_BLK_DEL_FAIL             ",
    "E_DHCPV6C_BLK_DEL_OK               ",
    "E_DHCPV6C_BLK_DEL_NOTFOUND         ",
    "E_DHCPV6C_BLK_DELWHOLE_NUM         ",
    "E_DHCPV6C_BLK_DELWHOLE_INPUT_FAIL  ",
    "E_DHCPV6C_BLK_DELWHOLE_DELSING_FAIL",
    "E_DHCPV6C_BLK_DELSINGLE_NUM        ",
    "E_DHCPV6C_BLK_DELSINGLE_INPUT_FAIL ",
    "E_DHCPV6C_BLK_FREEMEM_NUM          ",
    "E_DHCPV6C_BLK_FREEMEM_ALL          ",
    "E_DHCPV6C_BLK_FREEMEM_DELBLK_FAIL  ",
    "E_DHCPV6C_BLK_FREEMEM_DELNOD_FAIL  ",
    "E_DHCPV6C_BLK_FREEMEM_OK           ",
    "E_DHCPV6C_BLK_DELWAITNOD_NUM       ",
    "E_DHCPV6C_BLK_DELWAITNOD_NODEQU    ",
    "E_DHCPV6C_BLK_MEMCANBEFREE_NUM     ",

    /* zhangjinquan 00175135 DHCPv6特性 2012-07-23 start */
    "E_DHCPV6C_NO_NODE_IN_HASH_LIST     ",
    "E_DHCPV6C_NODE_NOT_IN_HASH_LIST    ",
    "E_DHCPV6C_MALLOC_ERR_FOR_TIMER_NODE",
    "E_DHCPV6C_SECONDNODE_CANNOT_BE_HEAD",
    "E_DHCPV6C_SECONDLIST_LINK_ERROR    ",
    "E_DHCPV6C_HOURNODE_CANNOT_BE_HEAD  ",
    "E_DHCPV6C_HOURLIST_LINK_ERROR      ",
    "E_DHCPV6C_SECOND_FIELD_VALUE_ERROR ",
    "E_DHCPV6C_FIND_NODE_CANNOT_BE_HEAD ",
    "E_DHCPV6C_FIND_SAME_CONFLICT_NODE  ",
    "E_DHCPV6C_TIMER_UP_FIND_HASH_ERROR ",
    /* zhangjinquan 00175135 DHCPv6特性 2012-07-23 end   */

    "E_DHCPV6C_CHECK_BLKDEL             ",
    "E_DHCPV6C_BAK_IPTYPEERR            ",
    "E_DHCPV6C_BAK_IPV6                 ",
    "E_DHCPV6C_BAKRESTORE_IPTYPEERR     ",
    "E_DHCPV6C_BAKRESTORE               ",
    "E_DHCPV6C_BAKRESTORE_STAT_ERR      ",
    "E_DHCPV6C_BAKRESTORE_DELEERR       ",
    "E_DHCPV6C_BAKRESTORE_CRTERR        ",
    "E_DHCPV6C_BAKRESTORE_TIMERR        ",
    "E_DHCPV6C_BAKRESTORE_STOPTIMERR    ",
    "E_DHCPV6C_BAKRDEL_STOPTIMERR       ",
    "E_DHCPV6C_BAKRESTORE_RENEW         ",
    "E_DHCPV6C_BAKDEL_NOTFOUND          ",
    "E_DHCPV6C_BAKDEL_FREEFAIL          ",

    "E_DHCPV6C_TIMRES_EXTIM             ",
    "E_DHCPV6C_TIMRES_T1TIM             ",
    "E_DHCPV6C_TIMRES_T2TIM             ",
    "E_DHCPV6C_TIMRES_T2EXTIM           ",
    "E_DHCPV6C_TIMRES_EXTIM_ERR         ",
    "E_DHCPV6C_STANDBYTIM_T1            ",
    "E_DHCPV6C_STANDBYTIM_T2            ",
    "E_DHCPV6C_STANDBYTIM_LEASE         ",
    "E_DHCPV6C_STANDBYTIM_ERR           ",
    "E_DHCPV6C_RENEW_RCVREPLYBK         ",
    "E_DHCPV6C_SENDTIM_SPUDRESTORE      ",
    "E_DHCPV6C_TIME_SPUDRESTORE_ENTER   ",
    "E_DHCPV6C_TIME_HASEXIST            ",
    "E_DHCPV6C_TIME_SPUDRESTORE         ",
    "E_DHCPV6C_TIME_SPUDRESTORE_FAIL    ",
    "E_DHCPV6C_TIMRES_NOTRESTORE        ",

    "E_DHCPV6C_BLK_DELSINGLE_TAIL_FAIL  ",
    "E_DHCPV6C_BLK_DELSINGLE_FAIL       ",
    "E_DHCPV6C_BLK_DELWAITNOD_ERR       ",
    "E_DHCPV6C_BLK_DELWAITNOD_COUNT_ERR ",

    "E_DHCPV6C_CNT_TRC_1                ",
    "E_DHCPV6C_CNT_TRC_2                ",
    "E_DHCPV6C_CNT_TRC_3                ",
    "E_DHCPV6C_CNT_TRC_4                ",
    "E_DHCPV6C_CNT_TRC_5                ",

    "E_DHCPV6C_CNT_ERR_1                ",
    "E_DHCPV6C_CNT_ERR_2                ",
    "E_DHCPV6C_CNT_ERR_3                ",
    "E_DHCPV6C_CNT_ERR_4                ",
    "E_DHCPV6C_CNT_ERR_5                ",

    /* CAUTION!!!!此计数用于检查枚举值与字符串的对应关系,如果被打印出来,说明对应关系不一致 */
    "E_DHCPV6C_ALARM_CNT_ERRRRRRRRRRRR  "
};

/*****************************************************************************
 函 数 名  : DHCPC_Debug_ShowDhcpServerGroup
 功能描述  : 显示dhcp-server group信息
 输入参数  : ULONG argc
             CHAR*argv[]
 输出参数  : 无
 返 回 值  : VOID
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2012年8月6日
    作    者   : jixiaoming 00180244
    修改内容   : 新生成函数

*****************************************************************************/
VOID DHCPC_Debug_ShowDhcpServerGroup(ULONG argc, CHAR*argv[])
{
    ULONG ulReturn = 0;
    ULONG ulNameLen = 0;
    UCHAR *pServerName = 0;
    S_CFG_CDB_CONDITION stCdbCon = {0};        /* CDB查询条件 */
    LAP_DHCP_CFG_S stDhcpServerInfo = {0};
    DHCP_SERVER_STATUS_S stDhcpServerStatus = {0};

    if (1 != argc)
    {
        DHCPC_OutString( "\r\n Please input dhcp-server group name");
        return;
    }

    pServerName = argv[0];

    stCdbCon.ucOper = M_CFG_CDB_EQUAL;
    stCdbCon.udwFieldId = M_LAP_DHCP_TBL_SERVER_GROUP_NAME_FLD_ID;

    ulNameLen = VOS_StrLen(pServerName);
    VOS_MemCpy( ( ( UCHAR* )( stCdbCon.aValue ) ), pServerName, ulNameLen );

    ulReturn = DBApiQuerySingle( M_LAP_DHCP_TBL_ID, 1, &stCdbCon, ( CHAR * )( &stDhcpServerInfo ) );
    if (VOS_OK != ulReturn)
    {
        DHCPC_OutString( "\r\n dhcp-server group ( %s ) not exist!", pServerName);
        return;
    }

    ulReturn = DHCPM_GetDhcpSrvStatusByIndex(stDhcpServerInfo.usDhcpServerGrpIndex, &stDhcpServerStatus);
    if (VOS_OK != ulReturn)
    {
        DHCPC_OutString( "\r\n get dhcp-server group status fail!");
        return;
    }

    DHCPC_OutString("\r\n -----------dhcp server group cfg------------");
    DHCPC_OutString("\r\n           primary ip = 0x%x %x %x %x", stDhcpServerInfo.aulPrimaryServerIp[0],
        stDhcpServerInfo.aulPrimaryServerIp[1], stDhcpServerInfo.aulPrimaryServerIp[2], stDhcpServerInfo.aulPrimaryServerIp[3]);
    DHCPC_OutString("\r\n         secondary ip = 0x%x %x %x %x", stDhcpServerInfo.aulSecondaryServerIp[0],
        stDhcpServerInfo.aulSecondaryServerIp[1], stDhcpServerInfo.aulSecondaryServerIp[2], stDhcpServerInfo.aulSecondaryServerIp[3]);
    DHCPC_OutString("\r\n            vpn index = %u", stDhcpServerInfo.ulVpnIndex);
    DHCPC_OutString("\r\n  DhcpServer Grp name = %s", stDhcpServerInfo.aucDhcpServerGrpName);
    DHCPC_OutString("\r\n DhcpServer Grp Index = %u", stDhcpServerInfo.usDhcpServerGrpIndex);
    DHCPC_OutString("\r\n             vpn name = %s", stDhcpServerInfo.aucVpnName);
    DHCPC_OutString("\r\n             IsDHCPv6 = %u", stDhcpServerInfo.ucIsDHCPv6);
    DHCPC_OutString("\r\n        RetransmitNum = %u", stDhcpServerInfo.ucRetransmitNum);
    DHCPC_OutString("\r\n    RetransmitTimeOut = %u", stDhcpServerInfo.ucRetransmitTimeOut);

    DHCPC_OutString("\r\n -----------dhcp server group stutas------------");
    DHCPC_OutString("\r\n       primary status = %u (%u: normal %u: abnormal %u:try)",
        stDhcpServerStatus.ucPrimarySrvStatus, DHCP_SEVER_NORMAL, DHCP_SEVER_ABNORMAL, DHCP_SEVER_TRY);
    DHCPC_OutString("\r\n       PrimarySrvTest = %u", stDhcpServerStatus.ucPrimarySrvTest);
    DHCPC_OutString("\r\n     secondary status = %u (%u: normal %u: abnormal %u:try)",
        stDhcpServerStatus.ucSecondarySrvStatus, DHCP_SEVER_NORMAL, DHCP_SEVER_ABNORMAL, DHCP_SEVER_TRY);
    DHCPC_OutString("\r\n     SecondarySrvTest = %u", stDhcpServerStatus.ucSecondarySrvTest);
    DHCPC_OutString("\r\n   PrimSrvTimerStatus = %u", stDhcpServerStatus.ucPrimSrvTimerStatus);
    DHCPC_OutString("\r\n     ucPrimTimeoutNum = %u", stDhcpServerStatus.ucPrimTimeoutNum);
    DHCPC_OutString("\r\n      ucSecTimeoutNum = %u", stDhcpServerStatus.ucSecTimeoutNum);
    DHCPC_OutString("\r\n  PrimTryTimeInterval = %u", stDhcpServerStatus.usPrimTryTimeInterval);
    DHCPC_OutString("\r\n   SecTryTimeInterval = %u", stDhcpServerStatus.usSecTryTimeInterval);
    DHCPC_OutString("\r\n     PrimaryAlarmFlag = %u", stDhcpServerStatus.ucPrimaryAlarmFlag);
    DHCPC_OutString("\r\n   SecondaryAlarmFlag = %u", stDhcpServerStatus.ucSecondaryAlarmFlag);
    DHCPC_OutString("\r\n    PrimequestTimeout = %u", stDhcpServerStatus.ucPrimRequestTimeout);
    DHCPC_OutString("\r\n SecondrequestTimeout = %u", stDhcpServerStatus.ucSecRequestTimeout);

    return;
}

/* DHCPC 模块seqnum维护命令 */
struct Command_S g_stDhcpcSeqNumCommand[] =
{
    { "show", "show the usage info of seqnum", NULL, DHCPC_Debug_ShowSeqNum},
#ifdef __SPU_DEBUG_VER__
    { "reset", "reset the usage info of seqnum", NULL, DHCPC_Debug_ResetSeqNum},
#endif
};

/* DHCPC 模块显示命令的二级命令组 */
struct Command_Group_S DhcpcSeqNumCmdGroup =
{
    sizeof(g_stDhcpcSeqNumCommand) / sizeof(struct Command_S), 20, g_stDhcpcSeqNumCommand
};

/*命令注册集合*/
struct Command_S DHCPDebugCommand[ ] =
{
    { "cnt", "show DHCP debug count ",
      NULL,     DHCPC_Debug_ShowDbgCnt},
    { "clearcnt", "clear DHCP debug count ",
      NULL,     DHCPC_Debug_ClearDbgCnt},
    { "blockinfo", "show DHCP control block infomation ",
      NULL,     DHCPC_Debug_ShowBlockInfo},
    { "blocknum", "show DHCP control block num",
      NULL,     DHCPC_Debug_ShowBlockNum},
    { "seqnum", "manage the resource of sequence-number ",
      &DhcpcSeqNumCmdGroup, NULL},
    { "cfg", "show dhcp-server group cfg",
      NULL,     DHCPC_Debug_ShowDhcpServerGroup},
    { "timerinfo", "show DHCP timer node hashinfo",
      NULL,     DHCPC_Debug_ShowTimerInfo},
    #ifdef __SPU_DEBUG_VER__
    { "mem_print","print dhcpc memory info",
      NULL, DHCPC_DebugShowMemInfo },
    {"print",    "set print level",
      NULL, DHCPC_DebugPrintLevelSet},
    #endif

};

struct Command_Group_S DHCPDebugCommandGroup =
{
       sizeof(DHCPDebugCommand)/sizeof(DHCPDebugCommand[0]),
       13,
       DHCPDebugCommand
};

//[EBCC]2847
VOID DHCPC_OutString(CHAR *fmt,...)
{
    /*lint +e530*/
    va_list arg;
    /*lint -e530*/
    CHAR DbgInfo[256] = {0};

    /*lint -e746*/
    va_start(arg,fmt);
    (VOS_VOID)VOS_nvsprintf(DbgInfo,256, fmt, arg);
    va_end(arg);
    /*lint +e746*/
#ifdef __WIN32_PLATFORM__
    printf("%s", DbgInfo);
#else
    (VOID)vos_printf("%s", DbgInfo);
#endif

    return;
}

VOID DHCPC_DebugPrintLevelSet( ULONG ulArgc, CHAR *szArgv[] )
{
    ULONG ulPrintLevel = 0;

    if (1 != ulArgc)
    {
        (VOID)vos_printf( "\r\n Please input print level!" );
        return;
    }

    if (0 != VOS_StrToUint32(szArgv[0], &ulPrintLevel))
    {
        (VOID)vos_printf("\r\n Please input parameter(0~4) !");
        return;
    }

    g_ulDhcpcPrintLevel = ulPrintLevel;

    return;
}

/*****************************************************************************
 函 数 名  : DHCPC_Dbg_PacketPrint
 功能描述  : DHCPC的报文输出函数
 输入参数  : UCHAR ucType
             void *pPacket
             ULONG ulPktLen
 输出参数  : 无
 返 回 值  : VOID
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2002年11月24日
    作    者   : yuqingping(25027)
    修改内容   : 新生成函数

*****************************************************************************/

VOID DHCPC_Dbg_PacketPrint( DHCP_S  *pstDHCPPkt, ULONG ulOptionLen,USHORT s1 )
{
    UCHAR  *pucOptions   = VOS_NULL_PTR;
    ULONG  ulMagicCookie = VOS_NULL_LONG;
    UCHAR  a_ucCount[19] = {0};
    CHAR   cTmp[200] = {0};
    UCHAR  *puctmp = NULL;
    CHAR   *szTotalStr   = VOS_NULL_PTR;
    UCHAR  i;
    CHAR  cMoreThen1[130] = {0};

    if (NULL == pstDHCPPkt)
    {
        DHCPC_Dbg_Printf( 0,"\r\n DHCPC: pstDHCPPkt is NULL in DHCPC_Dbg_PacketPrint()" );
        return;
    }

    szTotalStr = ( CHAR * )DHCP_Malloc( DHCPC_HANDLE, DHCPC_DEBUGBUF_LEN );
    if (  szTotalStr == VOS_NULL_PTR )
    {
        DHCPC_Dbg_Printf( 0,"\r\n DHCPC: DHCP_Malloc ERR in DHCPC_Dbg_PacketPrint()" );
        return;
    }
    /* zhangjinquan DTS2011122601821 review问题-增加初始化处理 2012-01-02 */
    PGP_MemZero(szTotalStr, DHCPC_DEBUGBUF_LEN);
// *szTotalStr=0;

    if ( 1==s1 )
    {
        VOS_sprintf( cTmp,"\r\n DHCPC: send packet :" );
        DHCPC_DBG_strcat( szTotalStr,cTmp );
    }
    else
    {
        VOS_sprintf( cTmp,"\r\n DHCPC: receive packet:" );
        DHCPC_DBG_strcat( szTotalStr,cTmp );
    }

    if ( pstDHCPPkt->ucOp == DHCP_OP_REPLY )
    {
        VOS_sprintf( cTmp,"\r\n    [Op    ] REPLY" );
        DHCPC_DBG_strcat( szTotalStr,cTmp );
    }
    else if ( pstDHCPPkt->ucOp == DHCP_OP_REQUEST )
    {
        VOS_sprintf( cTmp,"\r\n    [Op    ] REQUEST" );
        DHCPC_DBG_strcat( szTotalStr,cTmp );
    }
    else
    {
        VOS_sprintf( cTmp,"\r\n    [Op    ] %u ERROR",pstDHCPPkt->ucOp );
        DHCPC_DBG_strcat( szTotalStr,cTmp );

        DHCPC_Dbg_Printf( 1,szTotalStr );  /*-------------------------显示*/
        DHCP_Free( DHCPC_HANDLE, szTotalStr );
        return;


    }

    if ( pstDHCPPkt->ucHtype != DHCP_ETHERNETHARDWARETYPE )
    {
        VOS_sprintf( cTmp,"\r\n    [Htype] %u ERROR,not ETHERNETHARDWARETYPE:1",pstDHCPPkt->ucHtype );
        DHCPC_DBG_strcat( szTotalStr,cTmp );

        DHCPC_Dbg_Printf( 1,szTotalStr );  /*-------------------------显示*/
        DHCP_Free( DHCPC_HANDLE, szTotalStr );
        return;

    }
    else
    {
        /*VOS_sprintf(ucTmp,"\r\n    [ucHtype ] %u OK)",pstDHCPPkt->ucHtype);
        DHCPC_DBG_strcat(szTotalStr,ucTmp);    */

    }

    if ( pstDHCPPkt->ucHlen != DHCP_ETHERNETHARDWARELEN )
    {
        VOS_sprintf( cTmp,"\r\n    [Hlen] %u ERROR,not ETHERNETHARDWARELEN:6",pstDHCPPkt->ucHlen );
        DHCPC_DBG_strcat( szTotalStr,cTmp );

        DHCPC_Dbg_Printf( 1,szTotalStr );  /*-------------------------显示*/
        DHCP_Free( DHCPC_HANDLE, szTotalStr );
        return;

    }
    else
    {
        VOS_sprintf( cTmp,"\r\n    [Hlen  ] %u OK",pstDHCPPkt->ucHlen );
        DHCPC_DBG_strcat( szTotalStr,cTmp );
    }

    VOS_sprintf( cTmp,"\r\n    [Hops  ] %u",pstDHCPPkt->ucHops );
    DHCPC_DBG_strcat( szTotalStr,cTmp );
    VOS_sprintf( cTmp,"\r\n    [Xid   ] %u",pstDHCPPkt->ulXid );
    DHCPC_DBG_strcat( szTotalStr,cTmp );
    VOS_sprintf( cTmp,"\r\n    [Secs  ] %u",pstDHCPPkt->usSecs );
    DHCPC_DBG_strcat( szTotalStr,cTmp );
    VOS_sprintf( cTmp,"\r\n    [Flag  ] %u",pstDHCPPkt->usFlag );
    DHCPC_DBG_strcat( szTotalStr,cTmp );

    puctmp=( UCHAR * )( &pstDHCPPkt->ulCiaddr );
    VOS_sprintf( cTmp,"\r\n    [Ciaddr] %u.%u.%u.%u",*( puctmp+0 ),*( puctmp+1 ),*( puctmp+2 ),*( puctmp+3 ) );
    DHCPC_DBG_strcat( szTotalStr,cTmp );

    puctmp=( UCHAR * )( &pstDHCPPkt->ulYiaddr );
    VOS_sprintf( cTmp,"\r\n    [Yiaddr] %u.%u.%u.%u",*( puctmp+0 ),*( puctmp+1 ),*( puctmp+2 ),*( puctmp+3 ) );
    DHCPC_DBG_strcat( szTotalStr,cTmp );

    puctmp=( UCHAR * )( &pstDHCPPkt->ulSiaddr );
    VOS_sprintf( cTmp,"\r\n    [Siaddr] %u.%u.%u.%u",*( puctmp+0 ),*( puctmp+1 ),*( puctmp+2 ),*( puctmp+3 ) );
    DHCPC_DBG_strcat( szTotalStr,cTmp );

    puctmp=( UCHAR * )( &pstDHCPPkt->ulGiaddr );
    VOS_sprintf( cTmp,"\r\n    [Giaddr] %u.%u.%u.%u",*( puctmp+0 ),*( puctmp+1 ),*( puctmp+2 ),*( puctmp+3 ) );
    DHCPC_DBG_strcat( szTotalStr,cTmp );

    VOS_sprintf( cTmp,"\r\n    [Chaddr] %x-%x-%x-%x-%x-%x",pstDHCPPkt->szChaddr[0],pstDHCPPkt->szChaddr[1],pstDHCPPkt->szChaddr[2],pstDHCPPkt->szChaddr[3],pstDHCPPkt->szChaddr[4],pstDHCPPkt->szChaddr[5] );
    DHCPC_DBG_strcat( szTotalStr,cTmp );


    pstDHCPPkt->szSname[DHCPS_SNAME_LEN-1]=0;
    VOS_sprintf( cTmp,"\r\n    [Sname ] %s",pstDHCPPkt->szSname );
    DHCPC_DBG_strcat( szTotalStr,cTmp );
    pstDHCPPkt->szFile[DHCPS_FILE_LEN-1]=0;
    VOS_sprintf( cTmp,"\r\n    [File  ] %s",pstDHCPPkt->szFile );
    DHCPC_DBG_strcat( szTotalStr,cTmp );


    VOS_sprintf( cTmp,"\r\n    DHCP option -----------------" );
    DHCPC_DBG_strcat( szTotalStr,cTmp );

    pucOptions = ( UCHAR * )( pstDHCPPkt+1 );



    /*判断MAGICCODE是否为所需要的*/
    ulMagicCookie = *( ULONG * )pucOptions;
    if ( ulMagicCookie != ( ULONG )VOS_HTONL( DCHP_MAGICCOOKIE ) )
    {
        VOS_sprintf( cTmp,"\r\n    ERROR- [MCookie ] is %u not %u",ulMagicCookie,( ULONG )VOS_HTONL( DCHP_MAGICCOOKIE ) );
        DHCPC_DBG_strcat( szTotalStr,cTmp );

        DHCPC_Dbg_Printf( 1,szTotalStr );  /*-------------------------显示*/
        DHCP_Free( DHCPC_HANDLE, szTotalStr );
        return;

    }
    else
    {
        /*VOS_sprintf(ucTmp,"\r\n    [MCookie ] %u OK",ulMagicCookie );
        DHCPC_DBG_strcat(szTotalStr,ucTmp);*/
    }


    /*为每个属性初始化计数*/
    for ( i = 0; i < 19; a_ucCount[i] = 0, i++ ) ;

    /*pucOption指针加4，长度减4*/
    pucOptions       += 4;
    ulOptionLen     -= 4;




    while ( *pucOptions!= DHCP_ENDOFOPTIONS/* *pucOption != 0xFF*/ )
    {
        /*定义变量记录option类型和option长度*/
        UCHAR ucOptionCode = VOS_NULL;
        UCHAR ucOptionLen = VOS_NULL;

        /*判断ulOptionLen大于2，2为最小的option长度*/

        /*取得option类型*/
        ucOptionCode    = *pucOptions++;

        if ( ucOptionCode == 0 )
        {
            ucOptionLen     = 0;
            ulOptionLen  --;
        }
        else
        {
            ucOptionLen     = *pucOptions++;
            ulOptionLen -= 2;
        }

        /*取得option长度*/

        /*判断后面的变长字段的长度是否还足够,绝对保证不能
          读到当前DHCP报文的变长字段的长度域之外去*/
        if ( ulOptionLen <= ( unsigned long )ucOptionLen ) /*Modify by xiaoweifang34710 for compile warnings!*/
        {
            VOS_sprintf( cTmp,"\r\n            ERROR-option code 's length exceed" );
            DHCPC_DBG_strcat( szTotalStr,cTmp );

            DHCPC_Dbg_Printf( 1,szTotalStr );  /*-------------------------显示*/
            DHCP_Free( DHCPC_HANDLE, szTotalStr );
            return;

        }

        switch ( ucOptionCode/*option类型*/ )
        {
                /*1.是"Subnet mask"选项，code = 0x01*/
            case DHCP_SUBNETMASK_CODE :
                if ( ucOptionLen != 4 )
                {
                    VOS_sprintf( cTmp,"\r\n    SUBNETMASK:%u len err", ucOptionLen );
                    DHCPC_DBG_strcat( szTotalStr,cTmp );

                    DHCPC_Dbg_Printf( 1,szTotalStr );  /*-------------------------显示*/
                    DHCP_Free( DHCPC_HANDLE, szTotalStr );
                    return;

                }

                a_ucCount[0]++;

                puctmp=( UCHAR * )( pucOptions );
                VOS_sprintf( cTmp,"\r\n    SUBNETMASK:%u.%u.%u.%u",*( puctmp+0 ),*( puctmp+1 ),*( puctmp+2 ),*( puctmp+3 ) );
                DHCPC_DBG_strcat( szTotalStr,cTmp );

                break;

                /*2.是"Router"选项，code = 0x03*/
            case DHCP_ROUTERIP_CODE :
                /*判断长度是否是4的倍数*/
                if ( ( ucOptionLen & 0x03 )!= NULL )
                {
                    VOS_sprintf( cTmp,"\r\n    ROUTERIP:%u len err", ucOptionLen );
                    DHCPC_DBG_strcat( szTotalStr,cTmp );

                    DHCPC_Dbg_Printf( 1,szTotalStr );  /*-------------------------显示*/
                    DHCP_Free( DHCPC_HANDLE, szTotalStr );
                    return;

                }

                a_ucCount[1]++;


                for ( i=0;i<( ucOptionLen>>2 );i++ )
                {
                    puctmp=( UCHAR * )( pucOptions+i*4 );
                    VOS_sprintf( cTmp,"\r\n    ROUTERIP%d:%u.%u.%u.%u  ",i,*( puctmp+0 ),*( puctmp+1 ),*( puctmp+2 ),*( puctmp+3 ) );
                    DHCPC_DBG_strcat( szTotalStr,cTmp );
                }
                break;

                /*3.是"DNS 服务器"选项，code = 0x06*/
            case DHCP_DNSIP_CODE :
                /*判断长度是否是4的倍数*/
                if ( ( ucOptionLen & 0x03 )!= NULL )
                {
                    VOS_sprintf( cTmp,"\r\n    DNSIP:%u len err", ucOptionLen );
                    DHCPC_DBG_strcat( szTotalStr,cTmp );

                    DHCPC_Dbg_Printf( 1,szTotalStr );  /*-------------------------显示*/
                    DHCP_Free( DHCPC_HANDLE, szTotalStr );
                    return;

                }

                a_ucCount[2]++;


                for ( i=0;i<( ucOptionLen>>2 );i++ )
                {
                    puctmp=( UCHAR * )( pucOptions+i*4 );
                    VOS_sprintf( cTmp,"\r\n    DNSIP%d:%u.%u.%u.%u  ",i,*( puctmp+0 ),*( puctmp+1 ),*( puctmp+2 ),*( puctmp+3 ) );
                    DHCPC_DBG_strcat( szTotalStr,cTmp );
                }

                break;

                /*4.是"Host name"选项，code = 0x0b*/
            case DHCP_HOSTNAME_CODE :
                if ( ucOptionLen < 1 )
                {
                    VOS_sprintf( cTmp,"\r\n    HOSTNAME:%u len err", ucOptionLen );
                    DHCPC_DBG_strcat( szTotalStr,cTmp );

                    DHCPC_Dbg_Printf( 1,szTotalStr );  /*-------------------------显示*/
                    DHCP_Free( DHCPC_HANDLE, szTotalStr );
                    return;

                }

                a_ucCount[3]++;
                puctmp=pucOptions;
                DHCPC_DBG_strcat( szTotalStr,"\r\n    HOSTNAME:" );
                *( puctmp+ucOptionLen-1 )=0;
                DHCPC_DBG_strcat( szTotalStr,( CHAR * )puctmp );
                /*
                  for(i=0;i<(ucOptionLen);i++)
                      {
                      VOS_sprintf(ucTmp,"%u ",* puctmp);
                      DHCPC_DBG_strcat(szTotalStr,ucTmp);
                      puctmp++;
                      }
                */

                break;

                /*5.是"Domain name"选项，code = 0x0f*/
            case DHCP_DOMAINNAME_CODE :
                if ( ucOptionLen < 1 )
                {
                    VOS_sprintf( cTmp,"\r\n    DOMAINNAME:%u len err",ucOptionLen );
                    DHCPC_DBG_strcat( szTotalStr,( CHAR * )cTmp );

                    DHCPC_Dbg_Printf( 1,szTotalStr );  /*-------------------------显示*/
                    DHCP_Free( DHCPC_HANDLE, szTotalStr );
                    return;

                }

                a_ucCount[4]++;
                puctmp=pucOptions;
                DHCPC_DBG_strcat( szTotalStr,"\r\n    DOMAINNAME:" );
                *( puctmp+ucOptionLen-1 )=0;
                DHCPC_DBG_strcat( szTotalStr,( CHAR * )puctmp );
                /*
                for(i=0;i<(ucOptionLen);i++)
                    {
                    VOS_sprintf(ucTmp,"%u ",* puctmp);
                    DHCPC_DBG_strcat(szTotalStr,ucTmp);
                    puctmp++;
                    }
                */

                break;

                /*6.是"Netbios name server"选项，code = 0x2c*/
            case DHCP_NBNS_CODE :
                /*判断长度是否是4的倍数*/
                if ( ( ucOptionLen & 0x03 )!= NULL )
                {
                    VOS_sprintf( cTmp,"\r\n    NBNS:%u len err", ucOptionLen );
                    DHCPC_DBG_strcat( szTotalStr,cTmp );

                    DHCPC_Dbg_Printf( 1,szTotalStr );  /*-------------------------显示*/
                    DHCP_Free( DHCPC_HANDLE, szTotalStr );
                    return;

                }

                a_ucCount[5]++;


                for ( i=0;i<( ucOptionLen>>2 );i++ )
                {
                    puctmp=( UCHAR * )( pucOptions+i*4 );
                    VOS_sprintf( cTmp,"\r\n    NBNS%d:%u.%u.%u.%u  ",i,*( puctmp+0 ),*( puctmp+1 ),*( puctmp+2 ),*( puctmp+3 ) );
                    DHCPC_DBG_strcat( szTotalStr,cTmp );
                }

                break;


                /*7.是"Netbios data distribute server"选项，code = 0x2d*/
            case DHCP_NBDS_CODE :
                /*判断长度是否是4的倍数*/
                if ( ( ucOptionLen & 0x03 )!= NULL )
                {
                    VOS_sprintf( cTmp,"\r\n    NBDS:%u len err", ucOptionLen );
                    DHCPC_DBG_strcat( szTotalStr,cTmp );

                    DHCPC_Dbg_Printf( 1,szTotalStr );  /*-------------------------显示*/
                    DHCP_Free( DHCPC_HANDLE, szTotalStr );
                    return;

                }

                a_ucCount[6]++;


                for ( i=0;i<( ucOptionLen>>2 );i++ )
                {
                    puctmp=( UCHAR * )( pucOptions+i*4 );
                    VOS_sprintf( cTmp,"\r\n    NBDS%d:%u.%u.%u.%u  ",i,*( puctmp+0 ),*( puctmp+1 ),*( puctmp+2 ),*( puctmp+3 ) );
                    DHCPC_DBG_strcat( szTotalStr,cTmp );
                }
                break;

                /*8.是"Netbios node type"选项，code = 0x2e*/
            case DHCP_NBNT_CODE :
                if ( ucOptionLen != 1 )
                {
                    VOS_sprintf( cTmp,"\r\n    NBNT:%u len err", ucOptionLen );
                    DHCPC_DBG_strcat( szTotalStr,cTmp );

                    DHCPC_Dbg_Printf( 1,szTotalStr );  /*-------------------------显示*/
                    DHCP_Free( DHCPC_HANDLE, szTotalStr );
                    return;

                }

                a_ucCount[7]++;
                VOS_sprintf( cTmp,"\r\n    NBNT:%u ",* pucOptions );
                DHCPC_DBG_strcat( szTotalStr,cTmp );
                break;

                /*9.是"Netbios scope"选项，code = 0x2f*/
            case DHCP_NBSCOPE_CODE :
                if ( ucOptionLen < 1 )
                {
                    VOS_sprintf( cTmp,"\r\n    NBSCOPE:%u len err",ucOptionLen );
                    DHCPC_DBG_strcat( szTotalStr,cTmp );

                    DHCPC_Dbg_Printf( 1,szTotalStr );  /*-------------------------显示*/
                    DHCP_Free( DHCPC_HANDLE, szTotalStr );
                    return;


                }

                a_ucCount[8]++;
                puctmp=pucOptions;
                DHCPC_DBG_strcat( szTotalStr,"\r\n    NBSCOPE:" );
                for ( i=0;i<( ucOptionLen );i++ )
                {
                    VOS_sprintf( cTmp,"%u ",* puctmp );
                    DHCPC_DBG_strcat( szTotalStr,cTmp );
                    puctmp++;
                }

                break;

                /*10.是"Requested Ip"选项，code = 0x32*/
            case DHCP_REQUESTEDIP_CODE :
                if ( ucOptionLen != 4 )
                {
                    VOS_sprintf( cTmp,"\r\n    REQIP:%u len err ", ucOptionLen );
                    DHCPC_DBG_strcat( szTotalStr,cTmp );

                    DHCPC_Dbg_Printf( 1,szTotalStr );  /*-------------------------显示*/
                    DHCP_Free( DHCPC_HANDLE, szTotalStr );
                    return;

                }
                a_ucCount[9]++;

                puctmp=( UCHAR * )( pucOptions );
                VOS_sprintf( cTmp,"\r\n    REQIP:%u.%u.%u.%u",*( puctmp+0 ),*( puctmp+1 ),*( puctmp+2 ),*( puctmp+3 ) );
                DHCPC_DBG_strcat( szTotalStr,cTmp );

                break;

                /*11.是"Ip address lease time"选项，code=0x33*/
            case DHCP_IPLEASETIME_CODE:
                if ( ucOptionLen != 4 )
                {
                    VOS_sprintf( cTmp,"\r\n    IPLEASETIME:%u len err", ucOptionLen );
                    DHCPC_DBG_strcat( szTotalStr,cTmp );

                    DHCPC_Dbg_Printf( 1,szTotalStr );  /*-------------------------显示*/
                    DHCP_Free( DHCPC_HANDLE, szTotalStr );
                    return;

                }
                a_ucCount[10]++;
                VOS_sprintf( cTmp,"\r\n    IPLEASETIME:%u ",VOS_HTONL( * ( ULONG * )pucOptions ) );
                DHCPC_DBG_strcat( szTotalStr,cTmp );
                break;

                /*12.是"DHCP message type"选项，code=0x35*/
                /*当没有这个选项时,会在调用此函数的函数中进行出错处理*/
            case DHCP_MESSAGETYPE_CODE:
                /*"DHCP Message Type"选项的长度是否为1*/
                if ( ucOptionLen != 1 )
                {
                    VOS_sprintf( cTmp,"\r\n    MsgType:%u len err", ucOptionLen );
                    DHCPC_DBG_strcat( szTotalStr,cTmp );

                    DHCPC_Dbg_Printf( 1,szTotalStr );  /*-------------------------显示*/
                    DHCP_Free( DHCPC_HANDLE, szTotalStr );
                    return;

                }

                a_ucCount[11]++;

                switch ( * pucOptions )
                {
                    case DHCP_DISCOVER:
                        VOS_sprintf( cTmp,"\r\n    MsgType:DISCOVER(%u)  ",* pucOptions );
                        break;
                    case DHCP_OFFER:
                        VOS_sprintf( cTmp,"\r\n    MsgType:OFFER(%u)  ",* pucOptions );
                        break;
                    case DHCP_REQUEST:
                        VOS_sprintf( cTmp,"\r\n    MsgType:REQUEST(%u)  ",* pucOptions );
                        break;
                    case DHCP_DECLINE:
                        VOS_sprintf( cTmp,"\r\n    MsgType:DECLINE(%u)  ",* pucOptions );
                        break;
                    case DHCP_ACK:
                        VOS_sprintf( cTmp,"\r\n    MsgType:ACK(%u)  ",* pucOptions );
                        break;
                    case DHCP_NAK:
                        VOS_sprintf( cTmp,"\r\n    MsgType:NAK(%u)  ",* pucOptions );
                        break;
                    case DHCP_RELEASE:
                        VOS_sprintf( cTmp,"\r\n    MsgType:RELEASE(%u)  ",* pucOptions );
                        break;
                    case DHCP_INFORM:
                        VOS_sprintf( cTmp,"\r\n    MsgType:INFORM(%u)  ",* pucOptions );
                        break;
                    default :
                        VOS_sprintf( cTmp,"\r\n    MsgType:%u ERROR ",* pucOptions );
                        break;
                }

                DHCPC_DBG_strcat( szTotalStr,cTmp );
                break;

                /*13.是"Server Identifier"选项，code=0x36*/
            case DHCP_SERVERIP_CODE:
                if ( ucOptionLen != 4 )
                {
                    VOS_sprintf( cTmp,"\r\n    SERVERIP:%u len err ", ucOptionLen );
                    DHCPC_DBG_strcat( szTotalStr,cTmp );

                    DHCPC_Dbg_Printf( 1,szTotalStr );  /*-------------------------显示*/
                    DHCP_Free( DHCPC_HANDLE, szTotalStr );
                    return;

                }
                a_ucCount[12]++;

                puctmp=( UCHAR * )( pucOptions );
                VOS_sprintf( cTmp,"\r\n    SERVERIP:%u.%u.%u.%u",*( puctmp+0 ),*( puctmp+1 ),*( puctmp+2 ),*( puctmp+3 ) );
                DHCPC_DBG_strcat( szTotalStr,cTmp );

                break;

                /*14.是"Requested parameter list"选项，code = 0x37*/
            case DHCP_REQPARAM_CODE :
                if ( ucOptionLen < 1 )
                {
                    VOS_sprintf( cTmp,"\r\n    REQPARAM:%u len err",ucOptionLen );
                    DHCPC_DBG_strcat( szTotalStr,cTmp );

                    DHCPC_Dbg_Printf( 1,szTotalStr );  /*-------------------------显示*/
                    DHCP_Free( DHCPC_HANDLE, szTotalStr );
                    return;
                }

                a_ucCount[13]++;
                puctmp=pucOptions;
                DHCPC_DBG_strcat( szTotalStr,"\r\n    REQPARAM:" );
                for ( i=0;i<( ucOptionLen );i++ )
                {
                    VOS_sprintf( cTmp,"%u+ ",* puctmp );
                    DHCPC_DBG_strcat( szTotalStr,cTmp );
                    puctmp++;
                }
                break;

                /*15.是"Renew time"选项，code = 0x3a*/
            case DHCP_RENEWTIME_CODE :
                if ( ucOptionLen != 4 )
                {
                    VOS_sprintf( cTmp,"\r\n    RENEWTIME:%u len err", ucOptionLen );
                    DHCPC_DBG_strcat( szTotalStr,cTmp );

                    DHCPC_Dbg_Printf( 1,szTotalStr );  /*-------------------------显示*/
                    DHCP_Free( DHCPC_HANDLE, szTotalStr );
                    return;

                }
                a_ucCount[14]++;
                VOS_sprintf( cTmp,"\r\n    RENEWTIME:%u", * ( ULONG * )pucOptions );
                DHCPC_DBG_strcat( szTotalStr,cTmp );
                break;

                /*16.是"Rebind time"选项，code = 0x3b*/
            case DHCP_REBINDTIME_CODE :
                if ( ucOptionLen != 4 )
                {
                    VOS_sprintf( cTmp,"\r\n    REBINDTIME:%u len err", ucOptionLen );
                    DHCPC_DBG_strcat( szTotalStr,cTmp );

                    DHCPC_Dbg_Printf( 1,szTotalStr );  /*-------------------------显示*/
                    DHCP_Free( DHCPC_HANDLE, szTotalStr );
                    return;

                }
                a_ucCount[15]++;
                VOS_sprintf( cTmp,"\r\n    REBINDTIME:%u ", * ( ULONG * )pucOptions );
                DHCPC_DBG_strcat( szTotalStr,cTmp );
                break;

                /*17.是"Client Id"选项，code = 0x3d*/
            case DHCP_CLIENTID_CODE :
                if ( ucOptionLen < 2 )
                {
                    VOS_sprintf( cTmp,"\r\n    CLIENTID:%u len err",ucOptionLen );
                    DHCPC_DBG_strcat( szTotalStr,cTmp );

                    DHCPC_Dbg_Printf( 1,szTotalStr );  /*-------------------------显示*/
                    DHCP_Free( DHCPC_HANDLE, szTotalStr );
                    return;


                }

                a_ucCount[16]++;
                puctmp=pucOptions + 1;
                DHCPC_DBG_strcat( szTotalStr,"\r\n    CLIENTID:" );
                for ( i=0;i<( ucOptionLen - 1 );i++ )
                {
                    VOS_sprintf( cTmp,"%x ",* puctmp );
                    DHCPC_DBG_strcat( szTotalStr,cTmp );
                    puctmp++;
                }
                break;

                /*18.是"Vendor information"选项，code = 0x29*/
            case DHCP_VENDORINFO_CODE :
                if ( ucOptionLen < 1 )
                {
                    VOS_sprintf( cTmp,"\r\n    VENDORINFO:%u len err",ucOptionLen );
                    DHCPC_DBG_strcat( szTotalStr,cTmp );

                    DHCPC_Dbg_Printf( 1,szTotalStr );  /*-------------------------显示*/
                    DHCP_Free( DHCPC_HANDLE, szTotalStr );
                    return;

                }

                a_ucCount[17]++;
                puctmp=pucOptions;
                DHCPC_DBG_strcat( szTotalStr,"\r\n    VENDORINFO:" );
                for ( i=0;i<( ucOptionLen );i++ )
                {
                    VOS_sprintf( cTmp,"%u ",* puctmp );
                    DHCPC_DBG_strcat( szTotalStr,cTmp );
                    puctmp++;
                }
                break;

                /*对其他的选项不做任何操作*/
            default:
                a_ucCount[18]++;
                break;
        }

        /*跳过ucOptionLen长度的字节，得到下一个code字节*/
        pucOptions       += ucOptionLen;
        ulOptionLen -= ( long )ucOptionLen;

    }
    DHCPC_DBG_strcat( szTotalStr,"<-end" );
    for ( i = 0; i < 18;  i++ )
    {
        if ( a_ucCount[i] >1 )
        {
            switch ( i )
            {
                case 0:
                    VOS_sprintf( cMoreThen1,"\r\n    SUBNETMASK " );
                    break;
                case 1:
                    VOS_sprintf( cMoreThen1,"\r\n    ROUTERIP " );
                    break;
                case 2:
                    VOS_sprintf( cMoreThen1,"\r\n    DNSIP " );
                    break;
                case 3:
                    VOS_sprintf( cMoreThen1,"\r\n    HOSTNAME " );
                    break;
                case 4:
                    VOS_sprintf( cMoreThen1,"\r\n    HOSTNAME " );
                    break;
                case 5:
                    VOS_sprintf( cMoreThen1,"\r\n    NBNS " );
                    break;
                case 6:
                    VOS_sprintf( cMoreThen1,"\r\n    NBDS " );
                    break;
                case 7:
                    VOS_sprintf( cMoreThen1,"\r\n    NBNT " );
                    break;
                case 8:
                    VOS_sprintf( cMoreThen1,"\r\n    NBSCOPE " );
                    break;
                case 9:
                    VOS_sprintf( cMoreThen1,"\r\n    REQUESTEDIP " );
                    break;
                case 10:
                    VOS_sprintf( cMoreThen1,"\r\n    IPLEASETIME " );
                    break;
                case 11:
                    VOS_sprintf( cMoreThen1,"\r\n    MESSAGETYPE " );
                    break;
                case 12:
                    VOS_sprintf( cMoreThen1,"\r\n    SERVERIP " );
                    break;
                case 13:
                    VOS_sprintf( cMoreThen1,"\r\n    REQPARAM " );
                    break;
                case 14:
                    VOS_sprintf( cMoreThen1,"\r\n    RENEWTIME " );
                    break;
                case 15:
                    VOS_sprintf( cMoreThen1,"\r\n    REBINDTIME " );
                    break;
                case 16:
                    VOS_sprintf( cMoreThen1,"\r\n    CLIENTID " );
                    break;
                case 17:
                    VOS_sprintf( cMoreThen1,"\r\n    VENDORINFO " );
                    break;
                default:
                    break;
            }
            DHCPC_DBG_strcat( cMoreThen1,"occur more than 1" );
            DHCPC_DBG_strcat( szTotalStr,cMoreThen1 );
        }
    }
    if ( a_ucCount[18] >0 )     DHCPC_DBG_strcat( szTotalStr,"\r\n    WORN:some unsuport optioncode occur" );

    DHCPC_Dbg_Printf( 1,szTotalStr );  /*-------------------------显示*/
    DHCP_Free( DHCPC_HANDLE, szTotalStr );
}

/*****************************************************************************
 函 数 名  : DHCPC_Dbg_PacketPrintReceive
 功能描述  : DHCPC的报文输出函数
 输入参数  : UCHAR ucType
             void *pPacket
             ULONG ulPktLen
 输出参数  : 无
 返 回 值  : VOID
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2002年11月24日
    作    者   : yuqingping(25027)
    修改内容   : 新生成函数

*****************************************************************************/
VOID DHCPC_Dbg_PacketPrintReceive( DHCP_S  *pstDHCPPkt, ULONG ulOptionLen )
{
    if ( g_ulDHCPCDbgPkt!=1 ) return;
    DHCPC_Dbg_PacketPrint( pstDHCPPkt,  ulOptionLen,0 );  /*LFBDBG*/
}

/*****************************************************************************
 函 数 名  : DHCPC_Dbg_PacketPrintSend
 功能描述  : DHCPC的报文输出函数
 输入参数  : UCHAR ucType
             void *pPacket
             ULONG ulPktLen
 输出参数  : 无
 返 回 值  : VOID
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2002年11月24日
    作    者   : yuqingping(25027)
    修改内容   : 新生成函数

*****************************************************************************/
VOID DHCPC_Dbg_PacketPrintSend( PMBUF_S  *pMBuf )
{
    if ( g_ulDHCPCDbgPkt != 1 ) return;
    DHCPC_Dbg_PacketPrint( ( DHCP_S* )PMBUF_MTOD ( pMBuf, CHAR * ),
        ( ULONG )(pMBuf->ulTotalDataLength  - DHCPC_PKT_FIXEDFIELD_LEN),1 );
}

/*****************************************************************************
 函 数 名  : DHCPC_DBG_strcat
 功能描述  : 将两个字符串的内容连接起来
 输入参数  : CHAR *dest, CHAR *src
 输出参数  : 无
 返 回 值  : VOID
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2002年11月24日
    作    者   : yuqingping(25027)
    修改内容   : 新生成函数

*****************************************************************************/
VOID DHCPC_DBG_strcat( CHAR *dest, CHAR *src )
{

    if ( VOS_StrLen( dest )+VOS_StrLen( src )>( DHCPC_DEBUGBUF_LEN-2 ) )
    {
        DHCPC_Dbg_Printf( 0,dest );
        *dest=0;
    }
    VOS_StrCat( dest,src );
}


/*****************************************************************************
 函 数 名  : DHCPC_Dbg_Printf
 功能描述  :信息打印函数
 输入参数  : USHORT usIC_flag 为1，则同时向信息中心打印。const CHAR *pucStr
 输出参数  : 无
 返 回 值  : VOID
 调用函数  :
 被调函数  :
 修改历史       :
  1.日      期   : 2003年03月07日
    作      者   : lifubing(28197)
    修改内容   : 新生成函数
*****************************************************************************/
VOID DHCPC_Dbg_Printf( USHORT usIC_flag,CHAR *pucStr )
{
    DebugPrintf( ( ULONG )FSU_TID_DHCP, DHCPC_DBG_L2, 0,0,pucStr );
}

/*****************************************************************************
 函 数 名  : DHCPC_Debug_ShowDbgCnt
 功能描述  :信息打印函数
 输入参数  :
 输出参数  : 无
 返 回 值  : VOID
 调用函数  :
 被调函数  :
 修改历史       :
  1.日      期   : 2009年06月04日
    作      者   : jiahuidong00142544
    修改内容   : 新生成函数
*****************************************************************************/

VOID DHCPC_Debug_ShowDbgCnt(ULONG argc, CHAR*argv[])
{
    ULONG i = 0;
    ULONG j = 0;
    ULONG k = 0;

    PTM_PRINT_EXCEPTION_INFO( "\r\n DHCPC process debug cnt");
    for(i = 0; i < DHCP_MAX_FAILURE_COUNTER; i++)
    {
        PTM_PRINT_EXCEPTION_LOOP("\r\n aulDHCPDbgCnt[%u]=%u", i, g_aulDHCPDbgCnt[i]);
    }

    for(i = 0; i < E_DHCPV6C_END; i++)
    {
        if(0 != g_ulDHCPV6CDbgCnt[i])
        {
            PTM_PRINT_STRING_WITH_ARGUMENTS("\r\n%5lu : %-25s = %4u", i,g_ucDHCPV6CDbgCntName[i],g_ulDHCPV6CDbgCnt[i]);
        }
    }

    PTM_PRINT_EXCEPTION_INFO( "\r\n\r\n DHCPV6C fsm cnt");
    for(i = 0; i < DHCPV6C_STATE_BUTT; i++)
    {
        PTM_PRINT_STRING_WITH_ARGUMENTS("\r\n %s", g_ucDhcpv6FsmStateStr[i]);
        for(j = 0; j < DHCPV6C_EV_BUTT; j++)
        {

            for (k = 0; k < DHCPV6C_STATE_BUTT; k++)
            {
                if (0 != g_stDhcpv6cStateMachine[i].aulTrack[j][k])
                {
                    PTM_PRINT_STRING_WITH_ARGUMENTS("\r\n    <-- %s", g_ucDhcpv6FsmEventStr[j]);
                    PTM_PRINT_STRING_WITH_ARGUMENTS("\r\n    -->%-20s = %u\r\n", g_ucDhcpv6FsmStateStr[k], g_stDhcpv6cStateMachine[i].aulTrack[j][k]);
                }
            }
        }
        PTM_PRINT_EXCEPTION_INFO( "\r\n------------------------------");
    }

    /* 强制打印输出缓冲区的内容 */
    PTM_PRINT_EXCEPTION_END(PTM_BATCH_CMD_RSP_END);

    return;
}


/*****************************************************************************
 函 数 名  : DHCPC_Debug_ClearDbgCnt
 功能描述  :信息打印函数
 输入参数  :
 输出参数  : 无
 返 回 值  : VOID
 调用函数  :
 被调函数  :
 修改历史       :
  1.日      期   : 2009年06月04日
    作      者   : jiahuidong00142544
    修改内容   : 新生成函数
*****************************************************************************/
VOID DHCPC_Debug_ClearDbgCnt(ULONG argc, CHAR*argv[])
{
    ULONG i = 0;
    PGP_MemZero((VOID *)g_aulDHCPDbgCnt, (sizeof(ULONG)*DHCP_MAX_FAILURE_COUNTER));

    /* 清空新dhcpv6数据 */
    PGP_MemZero(g_ulDHCPV6CDbgCnt, (sizeof(ULONG) * E_DHCPV6C_END));

    /* 清空状态数据 */
    for(i = 0; i < DHCPV6C_STATE_BUTT; i++)
    {
        PGP_MemZero(g_stDhcpv6cStateMachine[i].aulEventCounter, (sizeof(ULONG) * DHCPV6C_EV_BUTT));
    }
    return;
}



/*****************************************************************************
 函 数 名  : DHCPC_Debug_ShowBlockInfo
 功能描述  :信息打印函数
 输入参数  :
 输出参数  : 无
 返 回 值  : VOID
 调用函数  :
 被调函数  :
 修改历史       :
  1.日      期   : 2009年07月04日
    作      者   : jiahuidong00142544
    修改内容   : 新生成函数
  2.日      期   : 2010年08月07日
    作      者   : w00140934
    修改内容   : 通过控制块索引查询;
*****************************************************************************/

VOID DHCPC_Debug_ShowBlockInfo(ULONG argc, CHAR*argv[])
{
    ULONG ulRet = 0;
    ULONG ulIter = 0;
    ULONG ulTeidc = 0;
    ULONG ulIptype = 0;
    DHCPC_CTRLBLK *pstDhcpCtrlBlk = NULL;

    if(2 != argc)
    {
        DHCPC_OutString( "\r\n paramate 1 : teidc");
        DHCPC_OutString( "\r\n paramate 2 : 0 (ipv4) 1(ipv6)");
        return;
    }

    ulRet = (ULONG)VOS_StrToUint32(argv[0], &ulTeidc);
    if (ulRet != VOS_OK )
    {
        DHCPC_OutString( "\r\n paramate 1 error");
    }

    ulRet = (ULONG)VOS_StrToUint32(argv[1], &ulIptype);
    if (ulRet != VOS_OK )
    {
        DHCPC_OutString( "\r\n paramate 2 error");
    }

    ulRet = DHCPC_QueryDhcpcContext((UCHAR)ulIptype, ulTeidc, &pstDhcpCtrlBlk);
    if (VOS_OK != ulRet)
    {
        DHCPC_OutString( "\r\n not find!");
        return;
    }

    DHCPC_OutString( "\r\n ------------dhcpc block info-----------------");
    DHCPC_OutString( "\r\n     ulDHCPCtxIdx = %u", pstDhcpCtrlBlk->ulDHCPCtxIdx);
    DHCPC_OutString( "\r\n        aulMSISDN = 0x%x %x", pstDhcpCtrlBlk->aulMSISDN[0], pstDhcpCtrlBlk->aulMSISDN[1]);
    DHCPC_OutString( "\r\n          aulIMSI = 0x%x %x", pstDhcpCtrlBlk->aulIMSI[0], pstDhcpCtrlBlk->aulIMSI[1]);
    DHCPC_OutString( "\r\n          aulIMEI = 0x%x %x", pstDhcpCtrlBlk->aulIMEI[0], pstDhcpCtrlBlk->aulIMEI[1]);
    DHCPC_OutString( "\r\n               T1 = %u", pstDhcpCtrlBlk->ulT1);
    DHCPC_OutString( "\r\n               T2 = %u", pstDhcpCtrlBlk->ulT2);
    DHCPC_OutString( "\r\n          usLease = %u", pstDhcpCtrlBlk->ulLease);
    DHCPC_OutString( "\r\n      ulTimeStamp = %u", pstDhcpCtrlBlk->ulTimeStamp);
    DHCPC_OutString( "\r\n         aulSrvIp = 0x%x %x %x %x", pstDhcpCtrlBlk->aulSrvIp[0],
                    pstDhcpCtrlBlk->aulSrvIp[1], pstDhcpCtrlBlk->aulSrvIp[2], pstDhcpCtrlBlk->aulSrvIp[3]);
    DHCPC_OutString( "\r\n    aulUserIpAddr = 0x%x %x %x %x", pstDhcpCtrlBlk->aulUserIpAddr[0],
                    pstDhcpCtrlBlk->aulUserIpAddr[1], pstDhcpCtrlBlk->aulUserIpAddr[2], pstDhcpCtrlBlk->aulUserIpAddr[3]);
    DHCPC_OutString( "\r\n   aulAgentIpAddr = 0x%x %x %x %x", pstDhcpCtrlBlk->aulAgentIpAddr[0],
                    pstDhcpCtrlBlk->aulAgentIpAddr[1], pstDhcpCtrlBlk->aulAgentIpAddr[2], pstDhcpCtrlBlk->aulAgentIpAddr[3]);
    DHCPC_OutString( "\r\n       usVPNIndex = %u", pstDhcpCtrlBlk->usVPNIndex);
    DHCPC_OutString( "\r\n      usPoolIndex = %u", pstDhcpCtrlBlk->usPoolIndex);
    DHCPC_OutString( "\r\n usServerGrpIndex = %u", pstDhcpCtrlBlk->usServerGrpIndex);
    DHCPC_OutString( "\r\n       usApnIndex = %u", pstDhcpCtrlBlk->usApnIndex);
    DHCPC_OutString( "\r\n       ucUserType = %u", pstDhcpCtrlBlk->ucUserType);
    DHCPC_OutString( "\r\n     usDhcpStatus = %u", pstDhcpCtrlBlk->usDhcpStatus);
    DHCPC_OutString( "\r\n      ucAgingFlag = %u", pstDhcpCtrlBlk->ucAgingFlag);
    DHCPC_OutString( "\r\n          ulTEIDC = %u", pstDhcpCtrlBlk->ulTEIDC);
    DHCPC_OutString( "\r\n       ulPDPIndex = %u", pstDhcpCtrlBlk->ulPDPIndex);
    DHCPC_OutString( "\r\n         usSeqNum = %u", pstDhcpCtrlBlk->usSeqNum);
    DHCPC_OutString( "\r\n  ucRspTimeOutNum = %u", pstDhcpCtrlBlk->ucWaitRspTimeOutNum);
    DHCPC_OutString( "\r\n  ucResendTimeout = %u", pstDhcpCtrlBlk->ucResendTimeout);
    DHCPC_OutString( "\r\n          ucLAPNo = %u", pstDhcpCtrlBlk->ucLAPNo);
    DHCPC_OutString( "\r\n         ucIpType = %u", pstDhcpCtrlBlk->ucIpType);
    DHCPC_OutString( "\r\n       ucResource = 0x%x", pstDhcpCtrlBlk->ucResource);
    DHCPC_OutString( "\r\n   aulMainDnsAddr = 0x%x %x %x %x", pstDhcpCtrlBlk->aulMainDnsAddr[0],
                    pstDhcpCtrlBlk->aulMainDnsAddr[1], pstDhcpCtrlBlk->aulMainDnsAddr[2], pstDhcpCtrlBlk->aulMainDnsAddr[3]);
    DHCPC_OutString( "\r\n   aulSecdDnsAddr = 0x%x %x %x %x", pstDhcpCtrlBlk->aulSecdDnsAddr[0],
                    pstDhcpCtrlBlk->aulSecdDnsAddr[1], pstDhcpCtrlBlk->aulSecdDnsAddr[2], pstDhcpCtrlBlk->aulSecdDnsAddr[3]);
    DHCPC_OutString( "\r\n       aucSiDuid  = 0x");
    for (ulIter = 0; ulIter < DHCPV6C_MAX_DUID_LEN; ulIter++)
    {
        DHCPC_OutString( "%x ", pstDhcpCtrlBlk->aucSiDuid[ulIter]);
    }

    return ;
}

/*****************************************************************************
 函 数 名  : DHCPC_Debug_ShowBlockNum
 功能描述  :信息打印函数
 输入参数  :
 输出参数  : 无
 返 回 值  : VOID
 调用函数  :
 被调函数  :
 修改历史       :
  1.日      期   : 2009年07月04日
    作      者   : jiahuidong00142544
    修改内容   : 新生成函数
  2.日      期   : 2010年08月07日
    作      者   : w00140934
    修改内容   : 通过控制块索引查询;
*****************************************************************************/
VOID DHCPC_Debug_ShowBlockNum(ULONG argc, CHAR*argv[])
{
    DHCPC_CTRLBLK *pstDhcpCtrlBlk = NULL;
    ULONG i = 0;
    ULONG ulNum = 0;

    DHCPC_OutString( "\r\n ****************DHCPC_Debug_ShowBlockNum******************\r\n");

    for(i = 0; i < DHCPC_CTRLBLK_HASH_TABLE_SIZE; i++)
    {
        pstDhcpCtrlBlk = ( DHCPC_CTRLBLK * )g_pstDhcpcCtrlBlkRec[i];

        while(NULL != pstDhcpCtrlBlk)
        {
            ulNum ++;
            pstDhcpCtrlBlk = pstDhcpCtrlBlk->pstNextNode;
        }
    }

    DHCPC_OutString( "\r\n DHCPV4 Control Block NUM = %u",ulNum);

    DHCPC_OutString( "\r\n DHCPV6 Control Block NUM = %u",DHCPC_GetCtlBlkUsedNum());
    DHCPC_OutString( "\r\n DHCPV6 IDLE Block NUM = %u",DHCPC_GetIdelBlkNum());
    DHCPC_OutString( "\r\n DHCPV6 Manage Mem NUM = %u",DHCPC_GetManageMemNum());

    return ;
}


/*****************************************************************************
 *  函数名称:       DHCPC_Debug_ShowSeqNum
 *  初稿完成:       2012-07-18
 *  作    者:       y00170683
 *  函数功能:       SeqNum使用情况查询
 *  输入参数:       无
 *  输出参数:       无
 *  返回类型:       VOID
 *  其他说明:       无
 *  调用函数:
 *  主调函数:
*****************************************************************************/
VOID DHCPC_Debug_ShowSeqNum(ULONG argc, CHAR*argv[])
{
    ULONG i = 0;
    ULONG ulen = 0;
    ULONG ulUsedNum = 0;
    CHAR aucTemp[100] = {0} ;

    if (NULL == g_pstDhcpv6cSeqContext)
    {
        return;
    }

    DHCPC_OutString( "\r\n ***********Dhcpv6UsedSeqNumInfo*************");
    DHCPC_OutString( "\r\n The number of total seqnum : %u",g_usDhcpv6cMaxSeqNum);
    DHCPC_OutString( "\r\n The number of used seqnum : %u",g_stDhcpv6cSeqNumLink.usUsedNum);
    if (0 != g_stDhcpv6cSeqNumLink.usUsedNum)
    {
        DHCPC_OutString( "\r\n The used info of seqnum : ");
        for ( i = 0 ; i < DHCPV6C_MAX_SEQUENCE_NUM ; i++ )
        {
            if (VOS_TRUE == g_pstDhcpv6cSeqContext[i].ucbit2UsedFlg)
            {
                ulen += VOS_sprintf(aucTemp+ulen,"%u  ",i);
                ulUsedNum++;
            }

            if (ulen > 76 )
            {
                DHCPC_OutString("\r\n %s", aucTemp);
                ulen = 0;
            }
        }

        if (0 != ulen)
        {
            DHCPC_OutString("\r\n %s", aucTemp);
            ulen = 0;
        }

        DHCPC_OutString( "\r\n The number of actual used Seqnum : %u", ulUsedNum);
    }

    return ;
}

/*****************************************************************************
 *  函数名称:       DHCPC_Debug_ResetSeqNum
 *  初稿完成:       2012-07-26
 *  作    者:       y00170683
 *  函数功能:       重置SeqNum使用
 *  输入参数:       无
 *  输出参数:       无
 *  返回类型:       VOID
 *  其他说明:       无
 *  调用函数:
 *  主调函数:
*****************************************************************************/
VOID DHCPC_Debug_ResetSeqNum(ULONG argc, CHAR*argv[])
{
    ULONG ulen = 0;
    USHORT usIndex = 0;
    USHORT usEndIndex = 0;
    CHAR aucTemp[100] = {0};
    USHORT usStartIndex = 0;
    UCHAR ucFreeAllFlg = VOS_FALSE;
    USHORT usTotalNum = DHCPV6C_MAX_SEQUENCE_NUM;

    if ((NULL == g_stDhcpv6cSeqNumLink.pusNextNode) || (NULL == g_pstDhcpv6cSeqContext))
    {
        return;
    }

    if(1 != argc ||!VOS_StrCmp(argv[0], "?"))
    {
        DHCPC_OutString("\r\n please input [index] or [all]");
        return;
    }

    /* 确认需要释放的index */
    if (VOS_OK == VOS_StrNCmp(argv[0], "all", 3))
    {
        usStartIndex = 0;
        usEndIndex = usTotalNum;
        ucFreeAllFlg = VOS_TRUE;
    }
    else
    {
        usStartIndex = (USHORT)atoi(argv[0]);
        usEndIndex = (USHORT)atoi(argv[0]) + 1;
    }

    /* 参数检查 */
    if (usEndIndex > usTotalNum)
    {
        DHCPC_OutString("\r\n index should be smaller than %u", usTotalNum);
        return;
    }

    /* 释放指定的 */
    if (VOS_FALSE == ucFreeAllFlg)
    {
        if (VOS_FALSE == g_pstDhcpv6cSeqContext[usStartIndex].ucbit2UsedFlg)
        {
            DHCPC_OutString("\r\n sequence-num %u is free already!", usStartIndex);
            return;
        }
    }
    else
    {
        if (0 == g_stDhcpv6cSeqNumLink.usUsedNum)
        {
            DHCPC_OutString("\r\n no sequence-num is used!");
            return;
        }
    }

    DHCPC_OutString("\r\n reset sequence-num :");

    /*回收seqnum至空闲链 */
    for(usIndex = usStartIndex; usIndex < usEndIndex; usIndex++)
    {
        if (VOS_TRUE == g_pstDhcpv6cSeqContext[usIndex].ucbit2UsedFlg)
        {
            DHCPV6C_FreeSeqNum(usIndex);
            ulen += VOS_sprintf(aucTemp+ulen,"%u  ", usIndex);
        }
        if (ulen > 76 )
        {
            DHCPC_OutString("\r\n %s", aucTemp);
            ulen = 0;
        }
    }
    if (0 != ulen)
    {
        DHCPC_OutString("\r\n %s", aucTemp);
        ulen = 0;
    }

    DHCPC_Debug_ShowSeqNum(argc, argv);
    return ;
}

/*****************************************************************************
 函 数 名   : DHCPC_PrintMemInfo
 功能描述   : 获取显示dhcp在sc上的内存信息
 输入参数   : ULONG argc, CHAR* argv[], UCHAR ucParIdx
 输出参数   : ULONG *pulParValue
 返 回 值   :

 调用函数   :
 被调函数   :

 修改历史   :
 1.日    期 : 2012年1月18日
   作    者 : guolixian
   修改内容 : 新增函数
 2.日    期 : 2012年2月18日
   作    者 : z00175135
   修改内容 : 修改函数 DTS2011120504839 全pclint修改 2012-02-18
*****************************************************************************/
VOID DHCPC_PrintMemInfo(UCHAR *pucStructName,ULONG ulUnitSize, ULONG ulUnitNum, ULONG ulMemSize, UCHAR *pucMemType, UCHAR ucStatic)
{
    ULONG ulCpuId = 0;
    ULONG ulVcpuId = 0;

    ulCpuId = DVM_GetSelfCpuId();
    ulVcpuId = DVM_GetSelfVcpuID();
    /*StructName,UnitSize,UnitNum,ulMemSize,MemType,Static,Mid,Sub-System,CPU,vCPU*/
    if((NULL == pucStructName) || (NULL == pucMemType))
    {
        DHCPC_OutString("\r\n print info is wrong\r\n");
        return;
    }
    ulMemSize = ulMemSize >> 20;
    if(ulMemSize > 0)
    {
        DHCPC_OutString("%23s,%10u,%12u,%8u,%12s,%8c,%12x,%8s,%6u,%4u\r\n",pucStructName,ulUnitSize,ulUnitNum,
            ulMemSize,pucMemType,ucStatic,MID_DHCPC,"PTM",ulCpuId,ulVcpuId);
    }
    return;
}


/*****************************************************************************
 函 数 名   : DHCPC_DebugShowMemInfo
 功能描述   : 获取显示dhcpc的内存信息
 输入参数   : ULONG argc, CHAR* argv[], UCHAR ucParIdx
 输出参数   : ULONG *pulParValue
 返 回 值   :

 调用函数   :
 被调函数   :

 修改历史   :
 1.日    期 : 2012年1月18日
   作    者 : guolixian
   修改内容 : 新增函数
*****************************************************************************/
VOID DHCPC_DebugShowMemInfo(ULONG argc, CHAR* argv[])
{
    if( 0 == DHCPC_SELF_CSI )
    {
        return;
    }

    DHCPC_OutString("\r\n ---------------------------- TABLE INFO--------------------------------------------\r\n");

    DHCPC_OutString("\r\n *************************************The DHCPC memory info Begin********************************************************");

    DHCPC_OutString("\r\n    StructName,            UnitSize,   UnitNum,    ulMemSize,  MemType,    Static, Mid,      Sub-System, CPU, vCPU\r\n");
    /* z00175135 DTS2012012003193 全文件pclint 2012-02-09 start */

    DHCPC_PrintMemInfo((UCHAR *)"g_astTimerLink",sizeof( DLL_S ),DHCPC_TMR_CIRCLE_TIME,
        DHCPC_TMR_CIRCLE_TIME * sizeof( DLL_S ), (UCHAR *)"SC",'N');

    DHCPC_PrintMemInfo((UCHAR *)"g_pstDhcpCtrlBlkNodeArr",sizeof(DHCPC_CTRLBLK_NODE),DHCPC_MAX_CTRLBLKNUM,
        sizeof( DHCPC_CTRLBLK_NODE )*DHCPC_MAX_CTRLBLKNUM , (UCHAR *)"SC",'N');

    DHCPC_PrintMemInfo((UCHAR *)"g_pstDhcpcCtrlBlkRec",sizeof(DHCPC_CTRLBLK),DHCPC_CTRLBLK_HASH_TABLE_SIZE,
        sizeof( DHCPC_CTRLBLK* )*DHCPC_CTRLBLK_HASH_TABLE_SIZE , (UCHAR *)"SC",'N');

    DHCPC_PrintMemInfo((UCHAR *)"g_pucDhcpPktBuf",sizeof(UCHAR) * DHCP_PKT_ASSUME_MAX_LEN,
        1,sizeof(UCHAR) * DHCP_PKT_ASSUME_MAX_LEN, (UCHAR *)"SC",'N');

    DHCPC_PrintMemInfo((UCHAR *)"g_aulDHCPDbgCnt",sizeof(ULONG),DHCP_MAX_FAILURE_COUNTER,
        sizeof(ULONG)*DHCP_MAX_FAILURE_COUNTER, (UCHAR *)"SC",'Y');
    /* z00175135 DTS2012012003193 全文件pclint 2012-02-09 end   */
    DHCPC_OutString("\r\n *************************************The DHCPC memory info END**********************************************************\r\n ");

    DHCPC_OutString("\r\n ---------------------------------------------------------------------------------\r\n");
}

VOID DHCPC_DebugOut_Stub(ULONG ulLevel, CHAR *pszFormat, ...)
{
    va_list ArgList;
    CHAR szBuffer[512];
    CHAR *pcTmpBuf = szBuffer;

    va_start(ArgList, pszFormat);
    VOS_vsprintf(pcTmpBuf, pszFormat, ArgList);
    va_end(ArgList);

    if (0 != g_ulDhcpcPrintLevel)
    {
        (VOID)vos_printf("\r\n[DHCPC]: %s\r\n", szBuffer);
    }

    return;
}


VOID DHCPC_NewDebugOut(ULONG ulLevel, CHAR* pszFile, ULONG ulLineNo, CHAR *pszFuncName, CHAR *pszFormat, ...)
{
    va_list ArgList;
    CHAR szBuffer[512];
    CHAR *pcTmpBuf = szBuffer;

    /* 防止输入参数太长 踩内存 */
    if ( VOS_StrLen( pszFormat ) > 400 )
    {
        /*lint +e416*/
        /*lint +e415*/
        pszFormat[400] = '\0';
        /*lint -e415*/
        /*lint -e416*/
    }

    pcTmpBuf += VOS_sprintf(pcTmpBuf, "%s: ", pszFuncName);

    va_start(ArgList, pszFormat);
    VOS_vsprintf(pcTmpBuf, pszFormat, ArgList);
    va_end(ArgList);

    if ( (1 == g_ulDhcpcPrintLevel && ulLevel <= PTM_LOG_ERR )
        || (1 < g_ulDhcpcPrintLevel ) )
    {
        (VOID)vos_printf("[%s %u]%s\r\n", pszFile, ulLineNo, szBuffer);
    }

    if (PTM_LOG_ERR >= ulLevel)
    {
        //DBG_WriteDiagLog2SRU(g_ulDhcpcLogRecordRegId, ulLevel, pszFile, ulLineNo, szBuffer, ArgList);
        PTM_WriteDiagLog(g_ulDhcpcLogRecordRegId, ulLevel, pszFile, ulLineNo, "%s", szBuffer);
    }

    return;
}

/*****************************************************************************
 函 数 名  : DHCPC_Debug_ShowTimerNodeInfo
 功能描述  : 显示特定指定时间节点数据
 输入参数  : ULONG ulHashKey, DHCPC_TIMER_NODE_S *pstTimerNode
 输出参数  : 无
 返 回 值  : 无
 调用函数  :
 被调函数  :
 修改历史      :
  1.日    期   : 2012-07-30
    作    者   : zhangjinquan 00175135
    修改内容   : 新生成函数 zhangjinquan 00175135 DHCPv6特性 2012-07-30
*****************************************************************************/
VOID DHCPC_Debug_ShowTimerNodeInfo(ULONG ulHashKey, DHCPC_TIMER_NODE_S *pstTimerNode)
{
    CHAR szIpAddr[60] = {0};
    DHCPC_CTRLBLK *pstDhcpcBlk = NULL;

    (VOID)vos_printf("\r\n Key=%u, IpType=%s, Teidc=0x%08x, Event=%d, ListType=%s",
                    ulHashKey, ((LAP_IPV4 == pstTimerNode->ucIpType) ? "IPv4" : "IPv6"),
                    pstTimerNode->ulTeidc, pstTimerNode->ucEvent,
                    ((DHCPC_LIST_TYPE_SECOND == pstTimerNode->ucListType) ? "second":"hour"));
    pstDhcpcBlk = NULL;
    (VOID)DHCPC_QueryDhcpcContext(pstTimerNode->ucIpType, pstTimerNode->ulTeidc, &pstDhcpcBlk);
    if (NULL == pstDhcpcBlk)
    {
        (VOID)vos_printf(", findDhcpBlk ERROR!");
    }
    else
    {
        (VOID)vos_printf(", Ip=%s", ((LAP_IPV4 == pstTimerNode->ucIpType) ?
                        LAP_IPv4AddrToStr(pstDhcpcBlk->aulUserIpAddr[0], szIpAddr)
                        : LAP_Ipv6AddrToStr(pstDhcpcBlk->aulUserIpAddr, szIpAddr)));
    }

    if (DHCPC_LIST_TYPE_HOUR == pstTimerNode->ucListType)
    {
        (VOID)vos_printf(", SecondField=%d, Months=%u", pstTimerNode->usSecondField,
                        pstTimerNode->ulCircleNum);
    }

    return;
}

/*****************************************************************************
 函 数 名  : DHCPC_Debug_ShowTimerInfoByTeidc
 功能描述  : 显示特定teidc对应的时间节点数据
 输入参数  : ULONG ulTeidc
 输出参数  : 无
 返 回 值  : 无
 调用函数  :
 被调函数  :
 修改历史      :
  1.日    期   : 2012-07-30
    作    者   : zhangjinquan 00175135
    修改内容   : 新生成函数 zhangjinquan 00175135 DHCPv6特性 2012-07-30
*****************************************************************************/
VOID DHCPC_Debug_ShowTimerInfoByTeidc(ULONG ulTeidc)
{
    ULONG i = 0;
    DHCPC_TIMER_NODE_S *pstTimerNode = NULL;

    for (i = 0; i < DHCPC_CTRLBLK_HASH_TABLE_SIZE; i++)
    {
        pstTimerNode = g_pstDHCPTimerHashList[i].pstNextNode;
        while ((NULL != pstTimerNode) && (ulTeidc == pstTimerNode->ulTeidc))
        {
            DHCPC_Debug_ShowTimerNodeInfo(i, pstTimerNode);

            pstTimerNode = pstTimerNode->pstHashNextNode;
        }
    }

    return;
}

/*****************************************************************************
 函 数 名  : DHCPC_Debug_ShowGlobalTimerInfo
 功能描述  : 显示timer哈希链的总体信息
 输入参数  : 无
 输出参数  : 无
 返 回 值  : 无
 调用函数  :
 被调函数  :
 修改历史      :
  1.日    期   : 2012-07-30
    作    者   : zhangjinquan 00175135
    修改内容   : 新生成函数 zhangjinquan 00175135 DHCPv6特性 2012-07-30
*****************************************************************************/
VOID DHCPC_Debug_ShowGlobalTimerInfo()
{
    (VOID)vos_printf("\r\n The second timer list node num is %u and the current index is %u.",
                    g_ulDHCPCTimerListNodeNum[DHCPC_LIST_TYPE_SECOND],
                    DHCPC_getCurTimerSecondPos());
    (VOID)vos_printf("\r\n The hour   timer list node num is %u and the current index is %u"
                    ", the current hour second is %u.",
                    g_ulDHCPCTimerListNodeNum[DHCPC_LIST_TYPE_HOUR],
                    DHCPC_getCurTimerHourPos(), DHCPC_getCurTimerHourSec());

    return;
}

/*****************************************************************************
 函 数 名  : DHCPC_Debug_ShowTimerInfo
 功能描述  : 显示时间节点哈希链表数据
 输入参数  : ULONG argc 参数个数, CHAR* argv[]参数字符串
 输出参数  : 无
 返 回 值  : 无
 调用函数  :
 被调函数  :
 修改历史      :
  1.日    期   : 2012-07-27
    作    者   : zhangjinquan 00175135
    修改内容   : 新生成函数 zhangjinquan 00175135 DHCPv6特性 2012-07-27
*****************************************************************************/
VOID DHCPC_Debug_ShowTimerInfo(ULONG argc, CHAR *argv[])
{
    ULONG i = 0;
    ULONG ulTeidc = 0;
    ULONG ulMaxCount = 0;
    ULONG ulShowNum = VOS_NULL_WORD;
    ULONG ulStartIndex = 0;
    DHCPC_TIMER_NODE_S *pstTimerNode = NULL;

    if (1 == argc)
    {
        if (!VOS_StrCmp(argv[0], "?"))
        {
            (VOID)vos_printf("\r\n You can input \"all\"/\"a\" or don't input any parameter to show all timer hash node;"
                            "\r\n Or you can input the number of hash list and the start index you want it to show;"
                            "\r\n Or you can input \"teidc\" and the real value of teidc to show the specified timer node!");
            return;
        }
    }

    if ((0 == argc) || (!VOS_StrCmp(argv[0], "all"))
        || (!VOS_StrCmp(argv[0], "ALL")))
    {
        ulShowNum = DHCPC_CTRLBLK_HASH_TABLE_SIZE;
    }
    else
    {
        if (!VOS_StrCmp(argv[0], "teidc"))
        {
            if (1 == argc)
            {
                (VOID)vos_printf("\r\n Please input the value of teidc!");
                return;
            }

            DHCPC_Debug_ShowGlobalTimerInfo();

            if ((VOS_StrLen(argv[1]) >= 2) && ('0' == argv[1][0]) && (('x' == argv[1][1]) || ('X' == argv[1][1])))
            {
                (VOID)VOS_StrToUint32(argv[1], &ulTeidc);
            }
            else
            {
                (VOID)VOS_StrToUint32(argv[1], &ulTeidc);
            }

            DHCPC_Debug_ShowTimerInfoByTeidc(ulTeidc);

            return;
        }

        if (1 == argc)
        {
            (VOID)vos_printf("\r\n Please input the start index of hash list!");
            return;
        }

        (VOID)VOS_StrToUint32(argv[0], &ulShowNum);
        if ((0 == ulShowNum) || (DHCPC_CTRLBLK_HASH_TABLE_SIZE < ulShowNum))
        {
            (VOID)vos_printf("\r\n The number of hash list you want it to show must between 1 and 65535!");
            return;
        }

        (VOID)VOS_StrToUint32(argv[1], &ulStartIndex);
        if (DHCPC_CTRLBLK_HASH_TABLE_SIZE < ulShowNum)
        {
            (VOID)vos_printf("\r\n The start index of hash list you want it to show must between 1 and 65535!");
            return;
        }
    }

    DHCPC_Debug_ShowGlobalTimerInfo();

    for (i = ulStartIndex; i < ulShowNum; i++)
    {
        pstTimerNode = g_pstDHCPTimerHashList[i].pstNextNode;
        while (NULL != pstTimerNode)
        {
            ulMaxCount++;

            DHCPC_Debug_ShowTimerNodeInfo(i, pstTimerNode);

            if (ulMaxCount >= 5000)
            {
                break;
            }

            pstTimerNode = pstTimerNode->pstHashNextNode;
        }

        if (ulMaxCount >= 5000)
        {
            break;
        }
    }

    return;
}

extern ULONG g_aulGtpcSndLapDbgCnt[GTPC_SND2_LAP_CNT_COUNT];

/*****************************************************************************
 函 数 名  : DHCPC_RegLogCnt
 功能描述  : 注册计数打印日志
 输出参数  : 无
 返 回 值  : ULONG
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2013年1月17日
    作    者   : jixiaoming 00180244
    修改内容   : 新生成函数

*****************************************************************************/
ULONG DHCPC_RegLogCnt(VOID)
{
    ULONG ulResult = VOS_OK;
    ULONG *aulCntUnit[2] = {0};

    PTM_LogCnt_RecRegInfo_S stRegInfo = {0};

    stRegInfo.ul64ComCsi = DHCPC_SELF_CSI;
    stRegInfo.ulComHandle = DHCPC_HANDLE;
    stRegInfo.ulTimeMsgType = DHCPC_MSG_TYPE_TIMER;
    stRegInfo.ulIsTimerSupport = VOS_TRUE;
    stRegInfo.ulDBGLogRegId = g_ulDhcpcLogRecordRegId;

    stRegInfo.ulCntUnitNum = 1;
    stRegInfo.ppulCntAddr = aulCntUnit;

    /* 注册打印DHCPV4C计数 */
    PTM_StrNCpy(stRegInfo.aucPrefixName, "DHCPV4CCnt", PTM_LOG_CNT_PREFIX_NAME_MAX_LEN);

    aulCntUnit[0] = g_aulDHCPDbgCnt;
    stRegInfo.ulTotalCntElemNum = DHCP_MAX_FAILURE_COUNTER;

    ulResult = PTM_LogCnt_RecordReg(&stRegInfo);
    if (VOS_OK != ulResult)
    {
        DHCPC_DebugPrint(PTM_LOG_ERR, "call PTM_LogCnt_RecordReg fail! DHCPV4C ulResult=%u", ulResult);
    }

    /* 注册打印DHCPV6C计数 */
    PTM_StrNCpy(stRegInfo.aucPrefixName, "DHCPV6CCnt", PTM_LOG_CNT_PREFIX_NAME_MAX_LEN);

    aulCntUnit[0] = g_ulDHCPV6CDbgCnt;
    stRegInfo.ulTotalCntElemNum = E_DHCPV6C_END;

    ulResult = PTM_LogCnt_RecordReg(&stRegInfo);
    if (VOS_OK != ulResult)
    {
        DHCPC_DebugPrint(PTM_LOG_ERR, "call PTM_LogCnt_RecordReg fail! DHCPV6C ulResult=%u", ulResult);
    }

    /* 注册LAPQ计数打印日志 */
    PTM_StrNCpy(stRegInfo.aucPrefixName, "LAPQCnt", PTM_LOG_CNT_PREFIX_NAME_MAX_LEN);

    aulCntUnit[0] = g_aulGtpcSndLapDbgCnt;
    stRegInfo.ulTotalCntElemNum = GTPC_SND2_LAP_CNT_COUNT;
    ulResult = PTM_LogCnt_RecordReg(&stRegInfo);
    if (VOS_OK != ulResult)
    {
        DHCPC_DebugPrint(PTM_LOG_ERR, "call PTM_LogCnt_RecordReg fail! DHCPV6C ulResult=%u", ulResult);
    }

    return ulResult;
}

