


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



/*****************************************************************************
    协议栈打印打点方式下的.C文件宏定义
*****************************************************************************/
/*lint -e767*/
#define    THIS_FILE_ID          PS_FILE_ID_DHCP_PUB_C
/*lint +e767*/


ULONG g_aulGtpcSndLapDbgCnt[GTPC_SND2_LAP_CNT_COUNT] = {0UL};

UCHAR g_ucSoftParaDHCPKPN = 0;

in6_addr in6addr_ggsn;

ULONG FCM_CreateFwdChannel(ULONG ulCompType, ULONG ulMsgType, ULONG ulCpuCompInstId)
{
    return 0;
}

VOS_UINT32 PTM_CreateMcQueue(PTM_QUEUE_INFO_S *pstQueInfo, VOS_UINT32* pulQueID)
{
    VOS_UINT32 ulRet = VOS_OK;

    return ulRet;
}

VOS_UINT32 VOS_MCQueueShow(MC_QUE_ID MCQueId, VOS_VOID* pMCQueInfo,
                                  VOS_UINT32 ulExpectCount, VOS_UINT32* pulReadCount)
{
    return VOS_OK;
}


VOS_UINT32 LAP2_McQue_IsEmpty( VOS_VOID *pvMCQueId )
{
    VOS_UINT32 ulRet = 0;
    VOS_UINT32 ulLen = 0;
    MC_QUE_Info stQueInfo = {0};

#ifdef __WIN32_PLATFORM__
    if (1)
    {
        return VOS_OK;
    }
#endif

    if( NULL == pvMCQueId )
    {
        return VOS_ERR;
    }

    stQueInfo.ulCurrentLen = 0;
    ulRet = VOS_MCQueueShow(pvMCQueId, (VOS_VOID *)&stQueInfo, 1, &ulLen);
    if( VOS_OK != ulRet )
    {
        return VOS_ERR;
    }

    if( 0 == stQueInfo.ulCurrentLen )
    {
        return VOS_ERR;
    }
    else
    {
        return VOS_OK;
    }
}

VOID PGP_Ready()
{
    return ;
}

ULONG FCM_ReadMCQue(ULONG ulCompType,
                    ULONG ulMsgType,
                    ULONG ulCpuCompInstId,
                    PMBUF_S **ppMBuf)
{
    return VOS_OK;
}

ULONG PGP_SetTaskRunConfirm()
{
    return VOS_OK;
}


VOS_UINT32 PGP_RTDistributeCallback(ULONG ulFlag, ULONG64 ul64DstCsi, VOID *pData, ULONG ulLen)
{
    return 0;
}

/* 强制打印输出缓冲区的内容 */
VOID PTM_Print_Exception_End(ULONG ulResultCode)
{
}

/* 打印异常字符窜 */
VOID PTM_Print_Exception_Info(UCHAR *pucStr)
{
    return;
}

VOID PTM_Print_Exception_Loop(UCHAR *pucStr, ULONG ulLoop, ULONG ulValue)
{
    return;
}


VOS_VOID  CDBRegCallBackCmd(CDB_TBLID         nTbl,       /* 表号 */
                                      CDB_CALLBACK_FUN pFun,        /* 函数指针 */
                                      ULONG64          ullCSI,      /* 那个任务注册的函数 */
                                      VOS_UINT8        ucFunType,   /* 回调函数的类型 */
                                      VOS_UINT8        ucBoardType, /* 注册在哪一种单板上 */
                                      VOS_INT8        *pcName)      /* 函数的名称 */
{
}

ULONG VOS_MCRWReadLock(MC_RWLOCK_ID RWLockID, VOS_CHAR *pFile, ULONG ulLine)
{
    return VOS_OK;
}

ULONG VOS_MCRWReadUnlock (MC_RWLOCK_ID RWLockID, VOS_CHAR *pFile, ULONG ulLine)
{
    return VOS_OK;
}

VOS_UINT32 VOS_MCRWWriteLock(MC_RWLOCK_ID RWLockID,VOS_CHAR *pFile,VOS_UINT32 ulLine)
{
    return VOS_OK;
}

VOS_UINT32 VOS_MCRWWriteUnlock (MC_RWLOCK_ID RWLockID, VOS_CHAR *pFile, VOS_UINT32 ulLine)
{
    return VOS_OK;
}

#ifndef __WIN32_PLATFORM_PTM__
void spin_lock(spinlock_t *lock)
{
        lock->lock = 1;
}

void spin_unlock(spinlock_t *lock)
{
        lock->lock = 0;
}
#endif

ULONG CRM_GetSelfLogicSlotID()
{
    return 1;
}

ULONG CRM_GetSlotPrimaryInfoOfSelfGroup(UCHAR ucSlotID)
{
    return 0;
}
VOID PTM_DebugBatchSRunCmdProc()
{
}

ULONG SPM_GetDwordValue(ULONG ulSoftparaNum, ULONG* ulDwordValue)
{
    return VOS_OK;
}

VOS_UINT32 VOS_MCRWLockCreate (VOS_CHAR* pName, MC_RWLOCK_ID *pIndex, VOS_UINT32 ulFlag )
{
    return VOS_OK;
}



VOS_UINT32 DBApiQueryFirst(CDB_TBLID nTableId,
                           VOS_INT32 dwCondNum,
                           S_CFG_CDB_CONDITION *pCond,
                           VOS_INT8 *pTuple,
                           VOS_UINT32 *pudwQueryId)
{
    return M_CFG_DB_API_SUCCESS;
}

/************************************************************
函数名:      DBApiQueryNext()
描述:        查询指定CDB表中满足条件的下一条记录
调用:        CDB相应核心函数
被调用:
输入:        pudwQueryId -- 本次查询操作标识
输出:        pTuple      -- 查询结果记录值
返回:        M_CFG_DB_API_SUCCESS    -- 成功
             M_CFG_DB_API_CURSOREND  -- 查询结束
             M_CFG_DB_API_DBERROR    -- 数据库错误
其他:        无
**************************************************************/
VOS_UINT32 DBApiQueryNext(VOS_UINT32 *pudwQueryId, VOS_INT8 *pTuple)
{
    return M_CFG_DB_API_SUCCESS;
}

VOS_BOOL PSM_Inf_IsOnlySGRestarted()
{
    return VOS_FALSE;
}

VOS_UINT32 PGP_Timer_Create( VOS_UINT64 CSI, VOS_UINT32 ulTimerMsgType, VOS_UINT32 ulInterval, VOID (*cbFunc)(VOID *), VOS_VOID *pArg, RELTMR_T *pTimerID, VOS_UINT32 ulTimerMode)
{
    return 0;
}

VOS_UINT32 PGP_RTCreate(VOS_UINT64 ulSelfCSI, VOS_UINT32 uiFlag, VOS_UINT32 uiQueueID, IPC_RTNOTIFY_FUNC pfNotify)
{
    return 0;
}

VOS_INT32  VOS_atoul( const VOS_CHAR * pcStr, VOS_UINT32 * pulVal )
{

    *pulVal = strtoul(pcStr, 0, 10);
    return VOS_OK;
}

VOS_INT32 VOS_StrToUint32(const VOS_CHAR *szStr, VOS_UINT32 *pulVal)
{
    VOS_atoul(szStr, pulVal);
    return 0;
}

VOID PTM_SetPrintLevel(PTM_DBG_PRINT_MODULE_E emModuleType, ULONG ulPrintLevel)
{
    return;
}

ULONG PTM_DbgLogRecordReg(PTM_DBG_PRINT_MODULE_E emModuleType, CHAR szSystemName[],
                          CHAR szModuleName[], CHAR szSubmoduleName[])
{
    return VOS_OK;
}

VOS_UINT32 CommandsRegister (struct Command_Group_S *  pCommand_Group, VOS_CHAR *cpCommand, VOS_CHAR *cpHelp)
{
    return 0;
}

ULONG DebugPrintf(ULONG ulModId,  ULONG ulCtrlLevel, CHAR * pcFileName, USHORT ulLineNo, CHAR * cDbgInfo, ...)
{
    return 0;
}

VOID PTM_Print_String_With_Arguments(UCHAR *pszFormat, ...)
{
    return;
}

#ifndef DMT
VOS_INT VOS_StrNCmp( VOS_CHAR * pscStr1, VOS_CHAR * pscStr2, SIZE_T ulCount )
{
    return strncmp(pscStr1, pscStr2, ulCount);
}

VOS_INTPTR VOS_StrICmp(VOS_CHAR *pscStr1, VOS_CHAR *pscStr2)
{
    return stricmp(pscStr1, pscStr2);
}

VOS_UINT32 VOS_TmGet( DATE_T * pDate, TIME_T * pTime, VOS_UINT32 * pulMillSecs )
{
    return VOS_ERR;
}
#endif

/*****************************************************************************
 Prototype    : PTM_WriteDiagLog
 Description  : 协议组日志统一入口函数
 Input        : ULONG ulDBGLogRegID
                DBG_LOG_LEVEL_E enLogType
                CHAR *szFileName
                ULONG ulLineNumber
                CHAR *pcFormat
                ...
 Output       : None
 Return Value :
 Calls        :
 Called By    :

*****************************************************************************/
ULONG PTM_WriteDiagLog(ULONG ulDBGLogRegID, DBG_LOG_LEVEL_E enLogType,
    CHAR *szFileName, ULONG ulLineNumber, CHAR *pcFormat, ...)
{
    return VOS_OK;
}

/*****************************************************************************
 Prototype    : LAP_IPv4AddrToStr
 Description  : IPv4地址转换为字符串
 Input        : ULONG ulIpAddr
                CHAR *szStr
 Output       : None
 Return Value :
 Calls        :
 Called By    :

*****************************************************************************/
ULONG LAP_IPv4AddrToStr( ULONG ulIpAddr, CHAR *szStr )
{
    UCHAR szIpAddr[4] = {0};

    szIpAddr[0] = (UCHAR)(ulIpAddr >> 24);
    szIpAddr[1] = (UCHAR)(ulIpAddr >> 16);
    szIpAddr[2] = (UCHAR)(ulIpAddr >> 8);
    szIpAddr[3] = (UCHAR)ulIpAddr;
    VOS_sprintf(szStr, "%d.%d.%d.%d", szIpAddr[0], szIpAddr[1], szIpAddr[2], szIpAddr[3]);

    return VOS_OK;
}

/*****************************************************************************
 Prototype    : LAP_Ipv6AddrToStr
 Description  : 将IPv6地址（主机字节顺序）转化为字符串；szStr应预留足够的空间
 Input        : ULONG* pulAddr
                CHAR *szStr 存储转化后的字符串；
 Output       : None
 Return Value : CHAR* 转化后的字符串；
 Calls        :
 Called By    :

*****************************************************************************/
CHAR *LAP_Ipv6AddrToStr( ULONG* pulAddr, CHAR *szStr )
{
    in6_addr stip;

    if((NULL == pulAddr) || (NULL == szStr))
    {
        return NULL;
    }

    VOS_MemSet( &stip, 0, sizeof( stip ) );
    VOS_MemCpy( ( VOID * ) &stip , ( VOID * ) pulAddr, sizeof( stip ) );

    VOS_sprintf(szStr, "%x:%x:%x:%x:%x:%x:%x:%x",
        stip.s6_addr16[0], stip.s6_addr16[1], stip.s6_addr16[2], stip.s6_addr16[3],
        stip.s6_addr16[4], stip.s6_addr16[5], stip.s6_addr16[6], stip.s6_addr16[7]);

    return szStr;
}


VOID PTM_StrNCpy(CHAR *pucDestStr, CHAR *pucSrcStr, ULONG ulMaxLength)
{
    ULONG ulCopyLength = VOS_StrLen(pucSrcStr);

    if ( ulCopyLength > ulMaxLength )
    {
        VOS_Assert(0);
        ulCopyLength = ulMaxLength;
    }

    VOS_MemCpy(pucDestStr, pucSrcStr, ulCopyLength);
    pucDestStr[ulCopyLength] = 0;

    return;
}



ULONG PTM_LogCnt_RecordReg(PTM_LogCnt_RecRegInfo_S *pstRegInfo)
{
    return VOS_OK;
}

/*****************************************************************************
 Prototype    : PTM_Dbg_RegMemoryPrint
 Description  : 协议组内存打印
 Input        : ULONG ulDBGLogRegID
                DBG_LOG_LEVEL_E enLogType
                CHAR *szFileName
                ULONG ulLineNumber
                CHAR *pcFormat
                ...
 Output       : None
 Return Value :
 Calls        :
 Called By    :

*****************************************************************************/
VOS_VOID PTM_Dbg_RegMemoryPrint(VOS_UINT64 ullCsi )
{
}

VOS_UINT32 VOS_Tm_NowInSec( VOS_UINT32 *pulRetTimeInSec )
{
    *pulRetTimeInSec = VOS_GetTick()/1000;
    return 0;
}

VOID OutString ( char * szString )
{
}


VOS_UINT32 DBApiQueryDirect(CDB_TBLID nTableId,
                            VOS_INT32 dwTupleNo,
                            VOS_INT8 *pTuple)
{
    return M_CFG_DB_API_DBERROR;
}

VOS_UINT32 CdbGetApnIndexByApnName(VOS_UINT8 *pucAPNName,  VOS_UINT16 *pusAPNIndex )
{
    return VOS_OK;
}

VOS_UINT32 PGP_Timer_Delete(RELTMR_T TimerID)
{
    return 0;
}

ULONG UDPS_PickUpExt( UDPS_PACKET_INFO_S * pstUdp, PMBUF_S *pstMbuf )
{
    return VOS_OK;
}

ULONG SPM_GetBitValue(ULONG ulSoftparaNum, UCHAR* ucByteValue)
{
    return VOS_OK;
}


ULONG AM_IsNeedChecksum(ULONG ulMsgCode)
{
    return VOS_NO;
}

ULONG UDPS_ConvertToSockAddr(SOCKADDRIN_S * pAddress, ULONG ulAddressLen)
{
    return VOS_OK;
}

LONG UDPS_DataHandle(UDPS_PACKET_INFO_S *pstPktInfo, PMBUF_S *pstMBuf)
{
    return VOS_OK;
}

ULONG CRM_GetSpuWorkModeOfSelfGroup(VOID)
{
    return 0;
}



ULONG  AM_USM_NotifyBackupByIndex (ULONG ulIndex, UCHAR ucType)
{
    return SDB_SUCCESS;
}


ULONG SDB_GTPC_GetRelatedContextsByTeidc(ULONG ulTeidc,  ULONG *pulNum, UCHAR *pucContextDim[])
{
    return SDB_SUCCESS;
}


ULONG SDB_GetContextByIndex(ULONG ulSdbIndex, UCHAR **ppucContext)
{
    return VOS_OK;
}


VOS_UINT32 DHCPC_SendAddrMsgToLAP(VOS_VOID *pMsg, VOS_UINT32 ulMsgLegth, ULONG ulUserIpAddr, VOS_UINT8 ucLapNo)
{
    return VOS_OK;
}

VOS_BOOL PSM_Inf_GetStatByCSI(VOS_UINT64 CSI)
{
    return 1;
}

VOS_UINT32 PGP_URTDistributeSend(VOS_UINT64 ul64SrcCSI,
                                           VOS_UINT64 ul64DstCSI,
                                           PMBUF_S* pstMsgBuff,
                                           VOS_UINT32 ulMode,
                                           VOS_UINT32 ulMsgType,
                                           VOS_UINT32 ulGene)
{
    return 0;
}


ULONG GTPC_RadiusHlrIPValidCheck(ULONG ulAddr)
{
    return VOS_OK;
}



VOS_BOOL TrcGetTraceFlag(ULONG ulTrcType)
{
    return VOS_FALSE;
}

/* 封装用户消息跟踪处理函数*/
VOID UGW_OmUsrMsgTrace(UCHAR *pMsg,
                          ULONG    ulMsgClass,
                          ULONG    ulGtpMsgType,
                          USHORT   usMsgLen,
                          UCHAR*   pucImsi,
                          UCHAR*   pucImei,
                          MSISDN   aucMsisdn,
                          UCHAR   ucRandomNo)
{
    return;
}

/* test if the address is an unspecific address */
ULONG ipv6_addr_any(in6_addr *a)
{
    return ((a->s6_addr32[0] | a->s6_addr32[1] |
         a->s6_addr32[2] | a->s6_addr32[3] ) == 0);
}

ULONG ipv6_addr_all_one(in6_addr *a)
{
    return ((a->s6_addr32[0] & a->s6_addr32[1] &
         a->s6_addr32[2] & a->s6_addr32[3] ) == 0xFFFFFFFF);
}

void ipv6_addr_copy(in6_addr *a1, in6_addr *a2)
{
    if((NULL == a1) || (NULL == a2))
    {
        return;
    }
    VOS_MemCpy((VOID *) a1, (VOID *) a2, sizeof( in6_addr));
}

PF_VOID fwd_set_ctrlhdr_vcpuid(FWD_TO_CTRL_HDR* pstCtrlHdr,PF_ULONG ulVcpuId)
{
    pstCtrlHdr->ulVcpuId = ulVcpuId;
    return;
}

PF_VOID fwd_set_ctrlhdr_vrfindex(FWD_TO_CTRL_HDR* pstCtrlHdr,PF_ULONG ulVrfIndex)
{
    pstCtrlHdr->ulVrfIndex = ulVrfIndex;
    return;
}

PF_VOID fwd_set_ctrlhdr_msgcode(FWD_TO_CTRL_HDR* pstCtrlHdr,PF_ULONG ulMsgCode)
{
    pstCtrlHdr->ulMsgCode = ulMsgCode;
    return;
}

PF_VOID fwd_set_ctrlhdr_moduleid(FWD_TO_CTRL_HDR* pstCtrlHdr,PF_ULONG ulModuleId)
{
    pstCtrlHdr->ulModuleId = ulModuleId;
    return;
}

void ipv6_addr_set(in6_addr *addr, ULONG w1, ULONG w2,ULONG w3, ULONG w4)
{
    addr->s6_addr32[0] = w1;
    addr->s6_addr32[1] = w2;
    addr->s6_addr32[2] = w3;
    addr->s6_addr32[3] = w4;
}

/*
 *    compute link-local solicited-node multicast address
 */

/* make an IPV6 address of all node multicast FF02::1 */
void ipv6_addr_all_nodes(in6_addr *addr)
{
    ipv6_addr_set(addr,
              VOS_HTONL(0xFF020000), 0, 0,
              VOS_HTONL(0x1));
}

VOID UGW_OmEmsTrcMsgTrc(S_OM_EMS_TRC_PARA *pstTrcPara, RM_SOCKET_PATH_S* pstPath)
{
    return;
}

ULONG DVM_GetSelfLpid()
{
    return 0;
}

ULONG64 PGP_getTimeByTicksInMisc(void)
{
    return VOS_GetTick();
}

VOS_VOID FamTrcSendTrcMsgWithTime(UCHAR  ucTrcType,         /* 接口类型 */
                                            UCHAR* pFilter,           /* 过滤参数 */
                                            ULONG  ulReportMsgType,   /* 消息类型 */
                                            USHORT usLen,             /* 消息长度 */
                                            UCHAR* pMsg,              /*消息内容*/
                                            S_FAM_BAM_TRC_TIME_DATA stTime) /*时间信息*/
{
    return;
}

VOID EMS_DebugTrace(ULONG ulPdpIndex,USHORT usModule, USHORT usCode, UCHAR* szReason, UCHAR* szSuggestion )
{
    return;
}

/*****************************************************************************
 Prototype    : LAP_IPv6GetAddrType
 Description  : IPv6地址类型检查
 Input        : in6_addr *addr
 Output       : None
 Return Value :
 Calls        :
 Called By    :

*****************************************************************************/
USHORT LAP_IPv6GetAddrType( in6_addr *addr )
{
    USHORT  type;
    ULONG  st;

    st = addr->s6_addr32[0];

    if ( ( st & VOS_HTONL( 0xFF000000 ) ) == VOS_HTONL( 0xFF000000 ) )
    {
        type = IPV6_ADDR_MULTICAST;

        switch ( ( st & VOS_HTONL( 0x00FF0000 ) ) )
        {
            /*lint -e30*/
            case 0x00000100: /*VOS_HTONL( 0x00010000 ) */
                            type |= IPV6_ADDR_LOOPBACK;
                break;

            case 0x00000200: /*VOS_HTONL( 0x00020000 )*/
                            type |= IPV6_ADDR_LINKLOCAL;
                break;

            case 0x00000500: /*VOS_HTONL( 0x00050000 )*/
                            type |= IPV6_ADDR_SITELOCAL;
                break;
            /*lint +e30*/
            default:
                break;
        };
        return type;
    }

    type = IPV6_ADDR_UNICAST;

    /* Consider all addresses with the first three bits different of
       000 and 111 as finished.
     */
    if ( ( st & VOS_HTONL( 0xE0000000 ) ) != VOS_HTONL( 0x00000000 ) &&
         ( st & VOS_HTONL( 0xE0000000 ) ) != VOS_HTONL( 0xE0000000 ) )
{
        if ( ( st & VOS_HTONL( 0x20000000 ) ) == VOS_HTONL( 0x20000000 ) )
        {
            return ( IPV6_ADDR_GLOBAL | type ); /* global 0010 0000 0000 0000
                                                     global 0011 0000 0000 0000 */
        }
        return type;
    }

    if ( ( st & VOS_HTONL( 0xFFC00000 ) ) == VOS_HTONL( 0xFE800000 ) )
        return ( IPV6_ADDR_LINKLOCAL | type );/*link-local 1111 1110 10*/

    if ( ( st & VOS_HTONL( 0xFFC00000 ) ) == VOS_HTONL( 0xFEC00000 ) )
        return ( IPV6_ADDR_SITELOCAL | type );/*site-local 1111 1110 11*/

    if ( ( addr->s6_addr32[0] | addr->s6_addr32[1] ) == 0 )
    {
        if ( addr->s6_addr32[2] == 0 )
        {
            if ( addr->s6_addr32[3] == 0 )
                return IPV6_ADDR_ANY;/*all ::0*/

            if ( addr->s6_addr32[3] == VOS_HTONL( 0x00000001 ) )
                return ( IPV6_ADDR_LOOPBACK | type );/* ::0:1 */

            return ( IPV6_ADDR_COMPATv4 | type );
        }

        if ( addr->s6_addr32[2] == VOS_HTONL( 0x0000ffff ) )
            return IPV6_ADDR_MAPPED;
    }

    st &= VOS_HTONL( 0xFF000000 );
    if ( st == 0 )
        return IPV6_ADDR_RESERVED; /*0000 0000 */
    st &= VOS_HTONL( 0xFE000000 );
    if ( st == VOS_HTONL( 0x02000000 ) )
        return IPV6_ADDR_RESERVED;    /* for NSAP */
    if ( st == VOS_HTONL( 0x04000000 ) )
        return IPV6_ADDR_RESERVED;    /* for IPX */
    return type;
}

VOS_SIZE_T PerfGetFamPerfCounterAddress(    VOS_UINT32 enMeasureUnit,     VOS_UINT32 enMeasureEntity,     VOS_UINT8 *pucObjectData)
{
    return VOS_OK;
}

VOS_VOID * IPC_RPC_AllocMsg(VOS_UINT32 ulSize, VOS_UINT32 ulUserInfo)
{
    return malloc(ulSize);
}

ULONG DHCPS_DPEDhcpMsgProc( UCHAR * pucMsg, ULONG ulMsgLen)
{
    return VOS_ERR;
}

VOS_UINT64 PSM_Inf_GetCSIBySGIDCmpTypeAndCmpInstId(VOS_UINT64 SGID,VOS_UINT32 CmpType,VOS_UINT32 CmpInsId)
{
    return 0;
}

ULONG IPC_RPC_Register(ULONG ulModuleID, IPC_RPC_RECEIVE_NOTIFY pfReceiveNotify)
{
    return 0;
}

VOS_VOID VOS_T_Delay(VOS_UINT32 ulMillisecond)
{
    //Sleep(ulMillisecond);
}

VOS_UINT32 VOS_Ev_Read( VOS_UINT32 ulEvents, VOS_UINT32 *pulEvents, VOS_UINT32 ulFlags, VOS_UINT32 ulTimerOut )
{
    return VOS_ERR;
}

ULONG DVM_GetSelfLogicSlotID()
{
    return 5;
}
ULONG DVM_GetSelfVcpuID(VOID)
{
    return 1;
}





#ifdef __cplusplus
    #if __cplusplus
        }
    #endif
#endif


