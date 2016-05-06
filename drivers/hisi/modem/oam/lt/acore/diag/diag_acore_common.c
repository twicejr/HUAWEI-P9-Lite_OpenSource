



/*****************************************************************************
  1 Include HeadFile
*****************************************************************************/
#include "vos.h"
#include "vos_Id.h"
#include <linux/debugfs.h>
#include "mdrv.h"
#include "msp_errno.h"
#include "msp_service.h"
#include "diag_common.h"
#include "SCMProc.h"
#include "SCMSoftDecode.h"
#include "diag_msgbsp.h"
#include "diag_msgbbp.h"
#include "diag_msgphy.h"
#include "diag_msgps.h"
#include "diag_msghifi.h"
#include "diag_acore_common.h"
#include "omerrorlog.h"
#include "diag_api.h"
#include "diag_cfg.h"
#include "diag_debug.h"
#include "cpm.h"
#include "OmSocketPpm.h"
#include "omnvinterface.h"
#include "SysNvId.h"


#ifdef __cplusplus
#if __cplusplus
extern "C" {
#endif
#endif

/*****************************************************************************
  2 Declare the Global Variable
*****************************************************************************/

/*lint -save -e767 原因:Log打印*/
#define    THIS_FILE_ID        MSP_FILE_ID_DIAG_ACORE_COMMON_C
/*lint -restore +e767*/

DRV_RESET_CB_MOMENT_E g_DiagResetingCcore = MDRV_RESET_CB_INVALID;

#if(FEATURE_SOCP_ON_DEMAND == FEATURE_ON)
SOCP_VOTE_TYPE_ENUM_U32 g_diagSocpState = SOCP_VOTE_FOR_WAKE;
#endif

VOS_UINT32 g_ulDebugCfg = 0;

DIAG_DUMP_INFO_STRU g_stDumpInfo = {0};


extern DIAG_TRANS_HEADER_STRU g_stBbpTransHead;
extern DIAG_TRANS_HEADER_STRU g_stPSTransHead;

struct wake_lock diag_wakelock;

/*****************************************************************************
  3 Function
*****************************************************************************/

extern VOS_VOID SCM_StopAllSrcChan(VOS_VOID);


/***********************************************************************
 Function Name   : diag_SocpVoteMsgProc
 Description     : DIAG APP AGENT SOCP投票处理
 Input           : MsgBlock* pMsgBlock
 Output          : None
 Return          : VOS_VOID

 History         :
    1.z00212940      2014-2-21  Draft Enact

*****************************************************************************/
VOS_VOID diag_SocpVoteMsgProc(MsgBlock* pMsgBlock)
{
#if(FEATURE_SOCP_ON_DEMAND == FEATURE_ON)
    DIAG_MSG_SOCP_VOTE_WAKE_CNF_STRU * voteCnf;
    DIAG_MSG_SOCP_VOTE_REQ_STRU * voteReq;
    VOS_INT32 ret;
    /*lint -save -e740*/
    voteReq = (DIAG_MSG_SOCP_VOTE_REQ_STRU *)pMsgBlock;
    /*lint -restore*/
    DIAG_DEBUG_SDM_FUN(EN_DIAG_APP_SOCP_VOTE, voteReq->ulVoteId, voteReq->ulVoteType, 0);
    if(voteReq->ulVoteId >= SOCP_VOTE_ID_BUTT)
    {
        DIAG_DEBUG_SDM_FUN(EN_DIAG_APP_SOCP_VOTE_ERR, voteReq->ulVoteId, voteReq->ulVoteType, 1);
        diag_printf("%s: invalid vote id 0x%x\n", __FUNCTION__, voteReq->ulVoteId);
        return;
    }

    ret = DRV_SOCP_VOTE(voteReq->ulVoteId, voteReq->ulVoteType);
    if(ERR_MSP_SUCCESS != ret)
    {
        DIAG_DEBUG_SDM_FUN(EN_DIAG_APP_SOCP_VOTE_ERR, voteReq->ulVoteId, voteReq->ulVoteType, 2);
        diag_printf("%s: 0x%x DRV_SOCP_VOTE ERR\n", __FUNCTION__, voteReq->ulVoteId);
    }

    /* 反对票才回复 */
    if(voteReq->ulVoteType == SOCP_VOTE_FOR_SLEEP)
    {
        return;
    }
    /*lint -save -e740*/
    voteCnf = (DIAG_MSG_SOCP_VOTE_WAKE_CNF_STRU *)VOS_AllocMsg(MSP_PID_DIAG_APP_AGENT, sizeof(DIAG_MSG_SOCP_VOTE_WAKE_CNF_STRU) - 20);
    /*lint -restore*/
    if(voteCnf == NULL)
    {
        DIAG_DEBUG_SDM_FUN(EN_DIAG_APP_SOCP_VOTE_ERR, voteReq->ulVoteId, voteReq->ulVoteType, 3);
        diag_printf("%s: 0x%x ALLOC MSG ERR\n", __FUNCTION__, voteReq->ulVoteId);
        return;
    }

    voteCnf->ulReceiverPid = voteReq->ulSenderPid;
    voteCnf->ulSenderPid   = MSP_PID_DIAG_APP_AGENT;
    voteCnf->ulLength      = sizeof(DIAG_MSG_SOCP_VOTE_WAKE_CNF_STRU) - 20;
    voteCnf->ulMsgId       = voteReq->ulMsgId;
    voteCnf->ulVoteId      = voteReq->ulVoteId;
    voteCnf->ulVoteType    = voteReq->ulVoteType;
    voteCnf->ulVoteRst     = (VOS_UINT32)ret;

    if(ERR_MSP_SUCCESS != VOS_SendMsg(MSP_PID_DIAG_APP_AGENT, voteCnf))
    {
        DIAG_DEBUG_SDM_FUN(EN_DIAG_APP_SOCP_VOTE_ERR, voteReq->ulVoteId, voteReq->ulVoteType, 4);
        diag_printf("%s: 0x%x SEND MSG ERR\n", __FUNCTION__, voteReq->ulVoteId);
    }
#endif
}

/*****************************************************************************
 Function Name   : diag_AgentVoteToSocp
 Description     : DIAG AGENT向SOCP投票
 Input           : SOCP_VOTE_TYPE_ENUM_U32 voteType
 Output          : None
 Return          : VOS_VOID

 History         :
    1.w00182550      2012-12-20  Draft Enact

*****************************************************************************/
VOS_VOID diag_AgentVoteToSocp(SOCP_VOTE_TYPE_ENUM_U32 voteType)
{
#if(FEATURE_SOCP_ON_DEMAND == FEATURE_ON)
    VOS_UINT32 ulRet;

    /*投票睡眠首先改变状态*/
    if(SOCP_VOTE_FOR_SLEEP == voteType)
    {
        g_diagSocpState = SOCP_VOTE_FOR_SLEEP;
    }

    ulRet = DRV_SOCP_VOTE(SOCP_VOTE_DIAG_APP, voteType);
    if(ERR_MSP_SUCCESS != ulRet)
    {
        diag_printf("[%s]:Vote To Socp Err!\n",__FUNCTION__);
        return;
    }
    g_diagSocpState = voteType;
#endif
}

/*****************************************************************************
 Function Name   : diag_ResetCcoreCB
 Description     : 诊断modem单独复位回调函数
 Input           : enParam
 Output          : None
 Return          : VOS_VOID
*****************************************************************************/
VOS_INT diag_ResetCcoreCB(DRV_RESET_CB_MOMENT_E enParam, int userdata)
{
    VOS_INT ret = ERR_MSP_SUCCESS;
    VOS_UINT32 ulRet;
    OM_CHANNLE_PORT_CFG_STRU stPortCfg;
    DIAG_CMD_TRANS_IND_STRU stTransInfo = {0};
    DIAG_MSG_REPORT_HEAD_STRU stDiagHead;

    if(enParam == MDRV_RESET_CB_BEFORE)
    {
#if(FEATURE_SOCP_ON_DEMAND == FEATURE_ON)
        (VOS_VOID)DRV_SOCP_VOTE(SOCP_VOTE_DIAG_COMM, SOCP_VOTE_FOR_WAKE);
        (VOS_VOID)DRV_SOCP_VOTE(SOCP_VOTE_GU_DSP, SOCP_VOTE_FOR_WAKE);
        (VOS_VOID)DRV_SOCP_VOTE(SOCP_VOTE_TL_DSP, SOCP_VOTE_FOR_WAKE);
#endif
        g_DiagResetingCcore = MDRV_RESET_CB_BEFORE;

        if(!DIAG_IS_CONN_ON)
        {
            return ERR_MSP_SUCCESS;
        }

        stTransInfo.ulModule = MSP_PID_DIAG_APP_AGENT;
        stTransInfo.ulMsgId  = DIAG_CMD_MODEM_WILL_RESET;
        stTransInfo.ulNo     = (g_DiagLogPktNum.ulTransNum)++;

        (VOS_VOID)VOS_MemSet(&stDiagHead, 0, sizeof(DIAG_MSG_REPORT_HEAD_STRU));

        stDiagHead.u.ulID           = DIAG_CMD_MODEM_WILL_RESET;
        stDiagHead.ulSsid           = DIAG_SSID_CPU;
        stDiagHead.ulModemId        = 0;
        stDiagHead.ulDirection      = DIAG_MT_IND;
        stDiagHead.ulMsgTransId     = g_ulTransId++;
        stDiagHead.ulChanId         = SCM_CODER_SRC_LOM_IND;

        stDiagHead.ulHeaderSize     = sizeof(stTransInfo);
        stDiagHead.pHeaderData      = &stTransInfo;

        stDiagHead.ulDataSize       = sizeof(VOS_UINT32);
        stDiagHead.pData            = &enParam;

        ret = diag_ServicePackData(&stDiagHead);
        if(ret)
        {
            vos_printf("report ccore reset fail\n");
        }

        vos_printf("diag report ccore reset to HIDP,and reset SOCP timer.\n");

        /* modem单独复位时，把中断超时时间恢复为默认值，让HIDP尽快收到复位消息 */
        mdrv_socp_set_log_int_default_timeout();
    }
    else if(enParam == MDRV_RESET_CB_AFTER)
    {
        g_DiagResetingCcore = MDRV_RESET_CB_AFTER;
        
        ulRet = NV_Read(en_NV_Item_Om_Port_Type, &stPortCfg, sizeof(OM_CHANNLE_PORT_CFG_STRU));
        
        /* 如果是连接HIDP则恢复超时时长 */
        if((VOS_OK == ulRet) && (CPM_OM_PORT_TYPE_VCOM == stPortCfg.enPortNum))
        {
            /* 调用底软接口把超时时长恢复，如果延时上报开关未打开，底软不配置 */
            mdrv_socp_set_log_int_timeout();
        }
    }
    else
    {
        vos_printf("diag_ResetCcoreCB enParam error\n");
    }
    return ERR_MSP_SUCCESS;
}

/***********************************************************************
 Function Name   : diag_AppAgentMsgProcInit
 Description     : DIAG APP AGENT初始化
 Input           :enum VOS_INIT_PHASE_DEFINE ip
 Output          : None
 Return          : VOS_UINT32

 History         :
    1.w00182550      2012-12-7  Draft Enact

*****************************************************************************/
VOS_UINT32 diag_AppAgentMsgProcInit(enum VOS_INIT_PHASE_DEFINE ip)
{
    VOS_UINT32 ret = ERR_MSP_SUCCESS;
    VOS_CHAR * resetName = "DIAG";  /*C核单独复位的名字*/
    VOS_INT    resetLevel = 49;

    if(ip == VOS_IP_LOAD_CONFIG)
    {
    	 wake_lock_init(&diag_wakelock,WAKE_LOCK_SUSPEND,"diag_wakelock");
        ret = (VOS_UINT32)mdrv_sysboot_register_reset_notify(resetName, (pdrv_reset_cbfun)diag_ResetCcoreCB, 0, resetLevel);
        if(ret)
        {
            vos_printf("diag register ccore reset fail\n");
        }

        diag_CfgResetAllSwt();
        diag_MspMsgInit();
        diag_BspMsgInit();
        diag_DspMsgInit();
        diag_BbpMsgInit();
        diag_PsMsgInit();
        diag_HifiMsgInit();
        diag_MessageInit();
        diag_ServiceInit();
        msp_ServiceInit();

        VOS_SpinLockInit(&g_DiagLogPktNum.ulPrintLock);
        VOS_SpinLockInit(&g_DiagLogPktNum.ulAirLock);
        VOS_SpinLockInit(&g_DiagLogPktNum.ulVoLTELock);
        VOS_SpinLockInit(&g_DiagLogPktNum.ulLayerLock);
        VOS_SpinLockInit(&g_DiagLogPktNum.ulUserLock);
        VOS_SpinLockInit(&g_DiagLogPktNum.ulEventLock);
        VOS_SpinLockInit(&g_DiagLogPktNum.ulTransLock);

        diag_AgentVoteToSocp(SOCP_VOTE_FOR_SLEEP);
    }
    else if(ip == VOS_IP_RESTART)
    {
        diag_InitAuthVariable();

        if (VOS_OK != CPM_PortAssociateInit())
        {
            return VOS_ERR;
        }
    }

    return ret;
}


/*****************************************************************************
 Function Name   : diag_DumpMsgInfo
 Description     : 保存A核最后收到的64条消息
 Input           : 

 注意事项:
    不支持重入，由调用者保证不会重复进入

 History         :
    1.c00326366      2015-12-23  Draft Enact

*****************************************************************************/
VOS_VOID diag_DumpMsgInfo(VOS_UINT32 ulSenderPid, VOS_UINT32 ulMsgId, VOS_UINT32 ulSize)
{
    VOS_UINT32 ulPtr = g_stDumpInfo.ulMsgCur;

    if(g_stDumpInfo.pcMsgAddr)
    {
        *((VOS_UINT32*)(&g_stDumpInfo.pcMsgAddr[ulPtr]))    = ulSenderPid;
        *((VOS_UINT32*)(&g_stDumpInfo.pcMsgAddr[ulPtr+4]))  = ulMsgId;
        *((VOS_UINT32*)(&g_stDumpInfo.pcMsgAddr[ulPtr+8]))  = ulSize;
        *((VOS_UINT32*)(&g_stDumpInfo.pcMsgAddr[ulPtr+12])) = mdrv_timer_get_normal_timestamp();
 
        g_stDumpInfo.ulMsgCur = (g_stDumpInfo.ulMsgCur + 16);
        if(g_stDumpInfo.ulMsgCur >= g_stDumpInfo.ulMsgLen)
        {
            g_stDumpInfo.ulMsgCur = 0;
        }
    }
}

/* DUMP存储的消息的最大长度，其中64表示包含0xaa5555aa、帧头、消息内容的总的最大长度 */
#define DIAG_DUMP_MAX_FRAME_LEN          (80)

/*****************************************************************************
 Function Name   : diag_DumpDFInfo
 Description     : 保存A核最后收到的码流信息，每条码流的保存长度不超过100字节
 Input           : 

 注意事项:
    不支持重入，由调用者保证不会重复进入

 History         :
    1.c00326366      2015-12-23  Draft Enact

*****************************************************************************/
VOS_VOID diag_DumpDFInfo(DIAG_FRAME_INFO_STRU * pFrame)
{
    VOS_UINT32 ulPtr;
    VOS_UINT32 ulLen;

    if(g_stDumpInfo.pcDFAddr)
    {
        ulPtr = g_stDumpInfo.ulDFCur;
        
        *((VOS_INT32*)(&g_stDumpInfo.pcDFAddr[ulPtr])) = 0xaa5555aa;
        *((VOS_INT32*)(&g_stDumpInfo.pcDFAddr[ulPtr+4])) = mdrv_timer_get_normal_timestamp();

        /* 每组数据都是16字节对齐，不会回卷 */
        g_stDumpInfo.ulDFCur = g_stDumpInfo.ulDFCur + 8;
        
        ulPtr = g_stDumpInfo.ulDFCur;

        ulLen = 8 + sizeof(DIAG_FRAME_INFO_STRU) + pFrame->ulMsgLen;
        if(ulLen > DIAG_DUMP_MAX_FRAME_LEN)
        {
            ulLen = DIAG_DUMP_MAX_FRAME_LEN;
        }
        
        ulLen = ((ulLen + 0xf) & (~0xf)) - 8;

        if((ulPtr + ulLen) <= g_stDumpInfo.ulDFLen)
        {
            (VOS_VOID)VOS_MemCpy(&g_stDumpInfo.pcDFAddr[ulPtr], (VOS_VOID*)pFrame, ulLen);

            /* 可能为0，需要取余 */
            g_stDumpInfo.ulDFCur = (g_stDumpInfo.ulDFCur + ulLen) % g_stDumpInfo.ulDFLen;
        }
        else
        {
            (VOS_VOID)VOS_MemCpy(&g_stDumpInfo.pcDFAddr[ulPtr], (VOS_VOID*)pFrame, (g_stDumpInfo.ulDFLen - ulPtr));
            
            ulLen = ulLen - (g_stDumpInfo.ulDFLen - ulPtr);     /* 未拷贝的码流长度 */
            ulPtr = g_stDumpInfo.ulDFLen - ulPtr;               /* 已拷贝的长度 */
            
            (VOS_VOID)VOS_MemCpy(&g_stDumpInfo.pcDFAddr[0], (((VOS_UINT8*)pFrame) + ulPtr), ulLen);

            /* ulLen前面已经做了限制，不会回卷 */
            g_stDumpInfo.ulDFCur = ulLen;
        }
    }
}


/*****************************************************************************
 Function Name   : diag_AppAgentMsgProc
 Description     : DIAG APP AGENT接收到的消息处理入口
 Input           : MsgBlock* pMsgBlock

 注意事项:
    由于errorlog的消息不能识别发送PID，所以需要进入errorlog的处理函数中检查
    当已知消息被成功处理时，则不需要再进行errorlog的消息检查
    通过ulErrorLog的值判断是否进行errorlog的消息检查
    后续函数扩展时需要注意

 History         :
    1.w00182550      2012-11-19  Draft Enact
    1.c00326366      2015-08-04  增加errorlog的消息处理

*****************************************************************************/
VOS_VOID diag_AppAgentMsgProc(MsgBlock* pMsgBlock)
{
    VOS_UINT32  ulErrorLog = ERR_MSP_CONTINUE; /* 见函数头中的注意事项的描述 */
    REL_TIMER_MSG *pTimer =NULL;
    DIAG_DATA_MSG_STRU* pMsgTmp =NULL;

    /*入参判断*/
    if (NULL == pMsgBlock)
    {
        return;
    }

    /*任务开始处理，不允许睡眠*/
    wake_lock(&diag_wakelock);

    diag_DumpMsgInfo(pMsgBlock->ulSenderPid, (*(VOS_UINT32*)pMsgBlock->aucValue), pMsgBlock->ulLength);

    /*根据发送PID，执行不同处理*/
    switch(pMsgBlock->ulSenderPid)
    {
        /*超时消息，按照超时包格式，打包回复*/
        case DOPRA_PID_TIMER:

            pTimer   = (REL_TIMER_MSG*)pMsgBlock;

            if((DIAG_ERRORLOG_TIMER_NAME == pTimer->ulName) && (DIAG_ERRORLOG_TIMER_PARA == pTimer->ulPara))
            {
#if(FEATURE_ON == FEATURE_PTM)
                OM_AcpuRcvMsgFinish();
#endif
            }
            else if((DIAG_CLTINFO_TIMER_NAME == pTimer->ulName) && (DIAG_CLTINFO_TIMER_PARA == pTimer->ulPara))
            {
#if(FEATURE_ON == FEATURE_PTM)
                OM_AcpuCltInfoCnfNotNeedProcessSetFlag();
                OM_AcpuRcvCltInfoFinish();
#endif
            }
            else if((DIAG_DEBUG_TIMER_NAME == pTimer->ulName) && (DIAG_DEBUG_TIMER_PARA == pTimer->ulPara))
            {
                diag_ReportMntn();
            }
            else
            {
                diag_TransTimeoutProc(pTimer);
            }
            ulErrorLog = VOS_OK;
            break;

        case WUEPS_PID_REG:
        case CCPU_PID_PAM_OM:

            ulErrorLog = diag_TransCnfProc((VOS_UINT8*)pMsgBlock, (pMsgBlock->ulLength + VOS_MSG_HEAD_LENGTH),
                                            DIAG_MSG_TYPE_BBP, &g_stBbpTransHead);
            break;

        case MSP_PID_DIAG_APP_AGENT:

            pMsgTmp = (DIAG_DATA_MSG_STRU*)pMsgBlock;
            if(ID_MSG_DIAG_HSO_DISCONN_IND == pMsgTmp->ulMsgId)
            {
                (VOS_VOID)diag_SetChanDisconn(pMsgBlock);
            }
            else
            {
            }

            ulErrorLog = VOS_OK;
            break;

        /*投票消息*/
        case MSP_PID_DIAG_AGENT:

            pMsgTmp = (DIAG_DATA_MSG_STRU*)pMsgBlock;
            if(DIAG_MSG_BSP_NV_AUTH_REQ == pMsgTmp->ulMsgId)
            {
                diag_AuthNvCfg(pMsgBlock);
                ulErrorLog = VOS_OK;
            }
#if(FEATURE_SOCP_ON_DEMAND == FEATURE_ON)
            else if((DIAG_MSG_DIAG_SOCP_VOTE_REQ == pMsgTmp->ulMsgId)
                || (DIAG_MSG_PHY_SOCP_VOTE_REQ == pMsgTmp->ulMsgId))
            {
                diag_SocpVoteMsgProc(pMsgBlock);
                ulErrorLog = VOS_OK;
            }
#endif
            else
            {
                ulErrorLog = ERR_MSP_CONTINUE;
            }
            break;

        case DSP_PID_APM:

            pMsgTmp = (DIAG_DATA_MSG_STRU*)pMsgBlock;
#if(FEATURE_SOCP_ON_DEMAND == FEATURE_ON)
            if(DIAG_MSG_UPHY_SOCP_VOTE_REQ == (pMsgTmp->ulMsgId & 0x0000ffff))
            {
                diag_SocpVoteMsgProc(pMsgBlock);
                ulErrorLog = VOS_OK;
            }
            else
#endif
            {
                ulErrorLog = ERR_MSP_CONTINUE;
            }
            break;

        default:
            /* 不通过PID判断是否透传的回复，通过匹配请求时保存的节点指针来确定是否透传的回复 */
            ulErrorLog = diag_TransCnfProc((VOS_UINT8*)pMsgBlock, (pMsgBlock->ulLength + VOS_MSG_HEAD_LENGTH),
                                            DIAG_MSG_TYPE_PS, &g_stPSTransHead);
            break;

    }

    /* 当返回值为ERR_MSP_CONTINUE时，表示需要继续检查是否是errorlog的消息 */
    if(ERR_MSP_CONTINUE == ulErrorLog)
    {
        OM_AcpuErrLogMsgProc(pMsgBlock);
        OM_AcpuCltInfoCnfMsgProc(pMsgBlock);
    }

   /*任务开始结束，允许睡眠*/
  wake_unlock(&diag_wakelock);

   return ;
}

/*****************************************************************************
 Function Name   : diag_AddTransInfoToList
 Description     : 添加解码后的透传命令数据到链表中
*****************************************************************************/
DIAG_TRANS_NODE_STRU* diag_AddTransInfoToList(VOS_UINT8 * pstReq, VOS_UINT32 ulRcvlen, DIAG_TRANS_HEADER_STRU *pstHead)
{
    DIAG_TRANS_NODE_STRU* pNewNode = NULL;
    VOS_UINT32 ret, ulHigh32, ulLow32;
#ifdef CONFIG_ARM64
    VOS_UINT_PTR ullAddr;
#endif

    /*申请一个节点大小*/
    pNewNode = VOS_MemAlloc(MSP_PID_DIAG_APP_AGENT, DYNAMIC_MEM_PT, sizeof(DIAG_TRANS_NODE_STRU) + ulRcvlen);
    if (NULL == pNewNode)
    {
        return NULL;
    }

    (VOS_VOID)VOS_MemSet(pNewNode, 0, ulRcvlen + sizeof(DIAG_TRANS_NODE_STRU));

    /*将新来的命令缓存到节点中*/
    (VOS_VOID)VOS_MemCpy(pNewNode->ucRcvData, pstReq, ulRcvlen);

    ulLow32 = (uintptr_t)pNewNode;
#ifdef CONFIG_ARM64
    {
        ullAddr = (VOS_UINT_PTR)pNewNode;
        ulHigh32 = (VOS_UINT32)(ullAddr>>32);
    }
#else
    {
        ulHigh32 = 0;
    }
#endif

    /* 启动定时器，以便没有回复时能够超时删除节点 */
    ret = VOS_StartRelTimer(&pNewNode->Timer, MSP_PID_DIAG_APP_AGENT, DIAG_TRANS_TIMEOUT_LEN, ulHigh32, \
                            ulLow32, VOS_RELTIMER_NOLOOP, VOS_TIMER_NO_PRECISION);
    if(ret != ERR_MSP_SUCCESS)
    {
        diag_printf("VOS_StartRelTimer fail [%s]\n", __FUNCTION__);
    }

    /* 添加信号量保护 */
    (VOS_VOID)VOS_SmP(pstHead->TransSem, 0);

    /* 插入节点到链表尾部 */
    blist_add_tail(&pNewNode->DiagList, &pstHead->TransHead);

    pNewNode->pSem       = &pstHead->TransSem;  /* 用于超时时的互斥保护 */
    pNewNode->ulMagicNum = DIAG_TRANS_MAGIC_NUM;

    (VOS_VOID)VOS_SmV(pstHead->TransSem);

    return pNewNode;
}


/*****************************************************************************
 Function Name   : diag_TransReqProcEntry
 Description     : 该函数用于透传命令的REQ处理
 Input           : VOS_UINT8* pstReq
 Output          : None
 Return          : VOS_UINT32

 History         :
    1.c00326366      2015-06-14  Draft Enact

*****************************************************************************/
VOS_UINT32 diag_TransReqProcEntry(DIAG_FRAME_INFO_STRU *pstReq, DIAG_TRANS_HEADER_STRU *pstHead)
{
    VOS_UINT32              ret = ERR_MSP_FAILURE;
    VOS_UINT32              ulSize;
    VOS_UINT32              ulCmdParasize;
    DIAG_TRANS_MSG_STRU     *pstSendReq = NULL;
    DIAG_TRANS_NODE_STRU    *pNode;
#ifdef CONFIG_ARM64
    VOS_UINT_PTR            ullAddr;
#endif
    DIAG_OSA_MSG_STRU       *pstMsg = NULL;

    diag_PTR(EN_DIAG_PTR_MSGMSP_TRANS);

    ulCmdParasize = pstReq->ulMsgLen - sizeof(MSP_DIAG_DATA_REQ_STRU);

     /* 打包透传数据*/
    pstSendReq = (DIAG_TRANS_MSG_STRU*)(pstReq->aucData + sizeof(MSP_DIAG_DATA_REQ_STRU));

    diag_LNR(EN_DIAG_LNR_PS_TRANS, pstReq->ulCmdId, VOS_GetSlice());

    ulSize = sizeof(DIAG_FRAME_INFO_STRU) + pstReq->ulMsgLen;

    pNode = diag_AddTransInfoToList((VOS_UINT8*)pstReq, ulSize, pstHead);
    if(VOS_NULL == pNode)
    {
        diag_printf("%s diag_AddTransCmdToList failed.\n", __FUNCTION__);
        return ERR_MSP_FAILURE;
    }

    /* 写低32位 */
    pstSendReq->ulSN = (uintptr_t)pNode;

    /* 如果是64位CPU，需要把高32位也传过去 */
#ifdef CONFIG_ARM64
    {
        ullAddr = (VOS_UINT_PTR)pNode;
        pstSendReq->usOriginalId    = (VOS_UINT16)((ullAddr>>32)&0x0000FFFF);
        pstSendReq->usTerminalId    = (VOS_UINT16)((ullAddr>>48)&0x0000FFFF);
    }
#endif

    if(DIAG_DEBUG_TRANS & g_ulDebugCfg)
    {
        vos_printf("[debug] trans req : cmdid 0x%x, pid %d, msgid 0x%x.\n",
           pstReq->ulCmdId, pstSendReq->ulReceiverPid, pstSendReq->ulMsgId);
    }

    pstMsg = (DIAG_OSA_MSG_STRU *)VOS_AllocMsg(MSP_PID_DIAG_APP_AGENT, (ulCmdParasize - VOS_MSG_HEAD_LENGTH));

    if (pstMsg != NULL)
    {
        pstMsg->ulReceiverPid   = pstSendReq->ulReceiverPid;

        (VOS_VOID)VOS_MemCpy(&pstMsg->ulMsgId, &pstSendReq->ulMsgId, (ulCmdParasize - VOS_MSG_HEAD_LENGTH));

        ret = VOS_SendMsg(MSP_PID_DIAG_APP_AGENT, pstMsg);
        if (ret != VOS_OK)
        {
			diag_printf("diag_TransReqProcEntry VOS_SendMsg failed!\n");
        }
        else
        {
            ret = ERR_MSP_SUCCESS;
        }
    }

    return ret;
}


/*****************************************************************************
 Function Name   : diag_DelTransCmdNode
 Description     : 删除已经处理完的节点
*****************************************************************************/
VOS_VOID diag_DelTransCmdNode(DIAG_TRANS_NODE_STRU* pTempNode)
{
    if(DIAG_TRANS_MAGIC_NUM != pTempNode->ulMagicNum)
    {
        return;
    }

    /*添加信号量保护*/
    (VOS_VOID)VOS_SmP((*pTempNode->pSem),0);

    /*删除节点*/
    if((VOS_NULL != pTempNode->DiagList.next) && (VOS_NULL != pTempNode->DiagList.prev))
    {
        blist_del(&pTempNode->DiagList);
    }

    (VOS_VOID)VOS_SmV((*pTempNode->pSem));

    (VOS_VOID)VOS_MemSet(pTempNode, 0, sizeof(DIAG_TRANS_NODE_STRU));

    /*释放内存*/
    VOS_MemFree(MSP_PID_DIAG_APP_AGENT, pTempNode);

    return ;
}


/*****************************************************************************
 Function Name   : diag_TransTimeoutProc
 Description     : 透传命令的超时处理
*****************************************************************************/
VOS_VOID diag_TransTimeoutProc(REL_TIMER_MSG *pTimer)
{
    DIAG_TRANS_NODE_STRU *pNode;
    DIAG_FRAME_INFO_STRU *pFrame;
#ifdef CONFIG_ARM64
    VOS_UINT_PTR ullAddr;
#endif

    /* 兼容64位 */
#ifndef CONFIG_ARM64
    {
        pNode = (DIAG_TRANS_NODE_STRU *)pTimer->ulPara;
    }
#else
    {
        ullAddr = (VOS_UINT_PTR)pTimer->ulName;
        ullAddr = (ullAddr<<32) | pTimer->ulPara;

        pNode = (DIAG_TRANS_NODE_STRU *)ullAddr;
    }
#endif

    pFrame = (DIAG_FRAME_INFO_STRU *)pNode->ucRcvData;

    if(DIAG_DEBUG_TRANS & g_ulDebugCfg)
    {
        vos_printf("[debug] trans timeout : cmdid 0x%x.\n", pFrame->ulCmdId);
    }

    /* 删除节点 */
    diag_DelTransCmdNode(pNode);
}


DIAG_TRANS_NODE_STRU * diag_IsTransCnf(DIAG_TRANS_MSG_STRU* pstPsCnf, DIAG_TRANS_HEADER_STRU *pstHead)
{
    DIAG_TRANS_NODE_STRU    *pNode;
    DIAG_TRANS_NODE_STRU    *pTempNode;
    LIST_S                  *me = NULL;
#ifdef CONFIG_ARM64
    VOS_UINT_PTR ullAddr;
#endif

    /* 兼容64位 */
#ifndef CONFIG_ARM64
    pNode = (DIAG_TRANS_NODE_STRU *)pstPsCnf->ulSN;
#else
    ullAddr = (VOS_UINT_PTR)pstPsCnf->usTerminalId;
    ullAddr = (ullAddr<<16) | pstPsCnf->usOriginalId;
    ullAddr = (ullAddr<<32) | pstPsCnf->ulSN;

    pNode = (DIAG_TRANS_NODE_STRU *)ullAddr;
#endif

    /*添加信号量保护*/
    (VOS_VOID)VOS_SmP(pstHead->TransSem,0);

    /* 在链表中查找每个子命令结点*/
    blist_for_each(me, &pstHead->TransHead)
    {
        pTempNode = blist_entry(me, DIAG_TRANS_NODE_STRU, DiagList);

        if(pTempNode == pNode)
        {
            (VOS_VOID)VOS_SmV(pstHead->TransSem);

            /* ulMagicNum非法表示节点已超时删除 */
            if(DIAG_TRANS_MAGIC_NUM != pNode->ulMagicNum)
            {
                return VOS_NULL;
            }

            return pNode;
        }
    }

    (VOS_VOID)VOS_SmV(pstHead->TransSem);

    return VOS_NULL;
}

/*****************************************************************************
 Function Name   : diag_GetTransInfo
 Description     : 获取透传命令的信息，并删除节点
*****************************************************************************/
VOS_VOID diag_GetTransInfo(MSP_DIAG_CNF_INFO_STRU *pstInfo,
                             DIAG_TRANS_CNF_STRU    *pstDiagCnf,
                             DIAG_TRANS_MSG_STRU    *pstPsCnf,
                             DIAG_TRANS_NODE_STRU   *pNode)
{
    DIAG_FRAME_INFO_STRU    *pFrame;
    MSP_DIAG_DATA_REQ_STRU  *pDiagData;
    APP_OM_MSG_STRU         *pstOmMsg;

    /*添加信号量保护*/
    (VOS_VOID)VOS_SmP((*pNode->pSem),0);

    /* 删除定时器 */
    (VOS_VOID)VOS_StopRelTimer(&pNode->Timer);

    pFrame = (DIAG_FRAME_INFO_STRU *)pNode->ucRcvData;
    pstInfo->ulTransId    = pFrame->stService.ulMsgTransId;
    pstInfo->ulMsgId      = pFrame->ulCmdId;
    pstInfo->ulMode       = pFrame->stID.mode4b;
    pstInfo->ulSubType    = pFrame->stID.sec5b;

    pDiagData           = (MSP_DIAG_DATA_REQ_STRU *)pFrame->aucData;
    pstDiagCnf->ulAuid  = pDiagData->ulAuid;
    pstDiagCnf->ulSn    = pDiagData->ulSn;

    pstOmMsg = (APP_OM_MSG_STRU *)pDiagData->ucData;

    pstPsCnf->usOriginalId  = pstOmMsg->usOriginalId;
    pstPsCnf->usTerminalId  = pstOmMsg->usTerminalId;
    pstPsCnf->ulSN          = pstOmMsg->ulSN;

    (VOS_VOID)VOS_SmV((*pNode->pSem));

    diag_DelTransCmdNode(pNode);

    return ;
}

/*****************************************************************************
 Function Name   : diag_TransCnfProc
 Description     : 透传命令的应答处理
 Input           :  VOS_UINT8* pstCnf
                    VOS_UINT32 ulLen
 Output          : None
 Return          : VOS_UINT32

 History         :
    1.c00326366      2015-06-14  Draft Enact

*****************************************************************************/
VOS_UINT32 diag_TransCnfProc(VOS_UINT8* pstCnf ,VOS_UINT32 ulLen, DIAG_MESSAGE_TYPE_U32 ulGroupId, DIAG_TRANS_HEADER_STRU *pstHead)
{
    VOS_UINT32              ret = 0;
    DIAG_TRANS_CNF_STRU     *pstDiagCnf;
    DIAG_TRANS_MSG_STRU     *pstPsCnf;
    MSP_DIAG_CNF_INFO_STRU  stDiagInfo = {0};
    DIAG_TRANS_NODE_STRU    *pNode;

    if(VOS_NULL_PTR == pstCnf)
    {
        return ERR_MSP_FAILURE;
    }
    pstPsCnf = (DIAG_TRANS_MSG_STRU *)pstCnf;

    if(pstPsCnf->ulLength < (sizeof(DIAG_TRANS_MSG_STRU) - VOS_MSG_HEAD_LENGTH - sizeof(pstPsCnf->aucPara)))
    {
        /* 如果长度小于透传命令的回复长度肯定不是透传命令 */
        return ERR_MSP_CONTINUE;
    }

    pNode = diag_IsTransCnf(pstPsCnf, pstHead);
    if(VOS_NULL == pNode)
    {
        return ERR_MSP_CONTINUE;
    }

    diag_LNR(EN_DIAG_LNR_PS_TRANS, ((pstPsCnf->usOriginalId<<16) | pstPsCnf->usTerminalId), pstPsCnf->ulSN);

    if(DIAG_DEBUG_TRANS & g_ulDebugCfg)
    {
        vos_printf("[debug] trans cnf : cmdid 0x%x, pid %d, msgid 0x%x.\n",
            stDiagInfo.ulMsgId, pstPsCnf->ulSenderPid, pstPsCnf->ulMsgId);
    }

    pstDiagCnf = VOS_MemAlloc(MSP_PID_DIAG_APP_AGENT, DYNAMIC_MEM_PT, (ulLen + sizeof(DIAG_TRANS_CNF_STRU)));
    if(VOS_NULL_PTR == pstDiagCnf)
    {
        return ERR_MSP_FAILURE;
    }

    stDiagInfo.ulSSId       = DIAG_SSID_APP_CPU;
    stDiagInfo.ulMsgType    = ulGroupId;
    stDiagInfo.ulDirection  = DIAG_MT_CNF;
    stDiagInfo.ulModemid    = 0;

    diag_GetTransInfo(&stDiagInfo, pstDiagCnf, pstPsCnf, pNode);

    diag_LNR(EN_DIAG_LNR_PS_TRANS, (stDiagInfo.ulMsgId), VOS_GetSlice());

    (VOS_VOID)VOS_MemCpy(pstDiagCnf->aucPara, pstPsCnf, ulLen);

    ret = DIAG_MsgReport(&stDiagInfo, pstDiagCnf, (ulLen + sizeof(DIAG_TRANS_CNF_STRU)));

    VOS_MemFree(MSP_PID_DIAG_APP_AGENT, pstDiagCnf);

    return ret;
}


/*****************************************************************************
 Function Name   : DIAG_LogShowToFile
 Description     : 给AT命令提供的调用接口，保存DIAG的log到文件中(AT^PULLOMLOG)
 Input           : bIsSendMsg 是否给A核发送消息保存A核log
 Return          : VOS_VOID

 History         :
    1.c00326366      2015-6-20  Draft Enact

*****************************************************************************/
VOS_VOID DIAG_LogShowToFile(VOS_BOOL bIsSendMsg)
{
}


int diag_debug_open(struct inode *inode, struct file *filp)
{
	return 0;
}

static ssize_t diag_debug_read(struct file *file, char __user *ubuf, size_t cnt, loff_t *ppos)
{
    printk("usage:\n");
    printk("\t echo cmd [param1] [param2] ... [paramN] > /sys/kernel/debug/modem_diag/diag\n");
    printk("cmd list:\n");
    printk("\t DIAG_ALL --- save all diag debug infomation.\n");
    return 0;
}

static ssize_t diag_debug_write(struct file *filp, const char __user *ubuf, size_t cnt, loff_t *ppos)
{
    char buf[128] = {0};
    ssize_t ret = cnt;
    DIAG_A_DEBUG_C_REQ_STRU *pstFlag = NULL;
    VOS_UINT32              ulret = ERR_MSP_FAILURE;

    cnt = (cnt > 127) ? 127 : cnt;
    if(copy_from_user(buf, ubuf, cnt))
    {
        diag_printf("copy from user fail\n");
        ret = -EFAULT;
        goto out;
    }
    buf[cnt] = 0;

    /* 配置异常目录份数 */
    if(0 == strncmp(buf, "DIAG_ALL", strlen("DIAG_ALL")))
    {
        DIAG_DebugCommon();
        DIAG_DebugNoIndLog();
        DIAG_DebugDFR();

        pstFlag = (DIAG_A_DEBUG_C_REQ_STRU *)VOS_AllocMsg(MSP_PID_DIAG_APP_AGENT, (sizeof(DIAG_A_DEBUG_C_REQ_STRU) - VOS_MSG_HEAD_LENGTH));

        if (pstFlag != NULL)
        {
            pstFlag->ulReceiverPid  = MSP_PID_DIAG_AGENT;

            pstFlag->ulMsgId        = DIAG_MSG_MSP_A_DEBUG_C_REQ;
            pstFlag->ulFlag         = DIAG_DEBUG_DFR_BIT | DIAG_DEBUG_NIL_BIT;

            ulret = VOS_SendMsg(MSP_PID_DIAG_APP_AGENT, pstFlag);
            if (ulret != VOS_OK)
            {
                diag_printf("diag_debug_write VOS_SendMsg failed!\n");
            }
        }
    }

out:
    return ret;
}

long diag_debug_ioctl(struct file *file, unsigned int cmd, unsigned long arg)
{
    return 0;
}

static const struct file_operations diag_debug_fops = {
    .open       = diag_debug_open,
    .read       = diag_debug_read,
    .write	    = diag_debug_write,
    .unlocked_ioctl = diag_debug_ioctl,
};


/*****************************************************************************
 Function Name   : MSP_AppDiagFidInit
 Description     : A核DIAG 任务注册
 Input           :enum VOS_INIT_PHASE_DEFINE ip
 Output          : None
 Return          : VOS_UINT32

 History         :
    1.w00182550      2012-11-19  Draft Enact

*****************************************************************************/
VOS_UINT32 MSP_AppDiagFidInit(enum VOS_INIT_PHASE_DEFINE ip)
{
    VOS_UINT32 ulRelVal = 0;
    struct dentry * d_file;

    switch (ip)
    {
        case VOS_IP_LOAD_CONFIG:

            ulRelVal = VOS_RegisterPIDInfo(MSP_PID_DIAG_APP_AGENT, (Init_Fun_Type) diag_AppAgentMsgProcInit, (Msg_Fun_Type) diag_AppAgentMsgProc);

            if (ulRelVal != VOS_OK)
            {
                return VOS_ERR;
            }

            ulRelVal = VOS_RegisterMsgTaskPrio(MSP_FID_DIAG_ACPU, VOS_PRIORITY_M2);
            if (ulRelVal != VOS_OK)
            {
                return VOS_ERR;
            }

            d_file = debugfs_create_dir("modem_diag", NULL);
            if(!d_file)
            {
                diag_printf("create debugfs dir modem_diag fail\n");
                return VOS_ERR;
            }

            if(!debugfs_create_file("diag", 0640, d_file, NULL, &diag_debug_fops))
            {
                diag_printf("create debugfs file modem_diag/diag file\n");
                return VOS_ERR;
            }

            /* 申请8K的dump空间 */
            g_stDumpInfo.pcDumpAddr = (VOS_VOID * )mdrv_om_register_field(OM_AP_DIAG, "ap_diag", (void*)0, (void*)0, DIAG_DUMP_LEN, 0);

            if(VOS_NULL != g_stDumpInfo.pcDumpAddr)
            {
                g_stDumpInfo.pcMsgAddr = g_stDumpInfo.pcDumpAddr;
                g_stDumpInfo.ulMsgCur  = 0;
                g_stDumpInfo.ulMsgLen  = DIAG_DUMP_MSG_LEN;
                
                g_stDumpInfo.pcDFAddr  = g_stDumpInfo.pcDumpAddr + DIAG_DUMP_MSG_LEN;
                g_stDumpInfo.ulDFCur   = 0;
                g_stDumpInfo.ulDFLen   = DIAG_DUMP_DF_LEN;
            }

            SCM_SoftDecodeCfgRcvTaskInit();

            VOS_RegisterMsgGetHook((VOS_MSG_HOOK_FUNC)DIAG_TraceReport);

#if (FEATURE_HISOCKET == FEATURE_ON)

            if((BSP_MODULE_SUPPORT == mdrv_misc_support_check(BSP_MODULE_TYPE_WIFI))
                && (VOS_TRUE == PPM_SockIsEnable()))
            {
                /* 接收SOCKET数据的自处理任务 */
                ulRelVal = VOS_RegisterSelfTaskPrio(MSP_FID_DIAG_ACPU,
                                 (VOS_TASK_ENTRY_TYPE)PPM_SockOmServerTask,
                                 COMM_SOCK_SELFTASK_PRIO, RL_SOCK_TASK_STACK_SIZE);
                if ( VOS_NULL_BYTE == ulRelVal )
                {
                    return VOS_ERR;
                }

                /* 接收SOCKET数据的自处理任务 */
                ulRelVal = VOS_RegisterSelfTaskPrio(MSP_FID_DIAG_ACPU,
                                 (VOS_TASK_ENTRY_TYPE)PPM_SockAtServerTask,
                                 COMM_SOCK_SELFTASK_PRIO, RL_SOCK_TASK_STACK_SIZE);
                if ( VOS_NULL_BYTE == ulRelVal )
                {
                    return VOS_ERR;
                }

                PPM_SockUdpInit();

            }
#endif

            break;

        case VOS_IP_RESTART:
            return COMM_Init();

        default:
            break;
    }

    return VOS_OK;
}


VOS_VOID DIAG_DebugTransOn(VOS_UINT32 ulOn)
{
    if(0 == ulOn)
    {
        g_ulDebugCfg &= (~DIAG_DEBUG_TRANS);
    }
    else
    {
        g_ulDebugCfg |= DIAG_DEBUG_TRANS;
    }
}

#ifdef __cplusplus
    #if __cplusplus
        }
    #endif
#endif



