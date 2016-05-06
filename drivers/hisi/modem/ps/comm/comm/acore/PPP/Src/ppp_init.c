/*
 *
 * All rights reserved.
 *
 * This software is available to you under a choice of one of two
 * licenses. You may choose this file to be licensed under the terms
 * of the GNU General Public License (GPL) Version 2 or the 2-clause
 * BSD license listed below:
 *
 * Redistribution and use in source and binary forms, with or without
 * modification, are permitted provided that the following conditions
 * are met:
 * 1. Redistributions of source code must retain the above copyright
 *    notice, this list of conditions and the following disclaimer.
 * 2. Redistributions in binary form must reproduce the above copyright
 *    notice, this list of conditions and the following disclaimer in the
 *    documentation and/or other materials provided with the distribution.
 *
 * THIS SOFTWARE IS PROVIDED BY THE AUTHOR AND CONTRIBUTORS "AS IS" AND
 * ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE
 * IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE
 * ARE DISCLAIMED.  IN NO EVENT SHALL THE AUTHOR OR CONTRIBUTORS BE LIABLE
 * FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL
 * DAMAGES (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS
 * OR SERVICES; LOSS OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION)
 * HOWEVER CAUSED AND ON ANY THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT
 * LIABILITY, OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY
 * OUT OF THE USE OF THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF
 * SUCH DAMAGE.
 *
 */


#ifdef  __cplusplus
  #if  __cplusplus
  extern "C"{
  #endif
#endif

/******************************************************************************
   2 外部函数变量声明
******************************************************************************/
#include "product_config.h"
#if(FEATURE_ON == FEATURE_PPP)
/******************************************************************************
   1 头文件包含
******************************************************************************/
#include "PPP/Inc/ppp_public.h"
#include "PPP/Inc/pppid.h"
#include "PPP/Inc/layer.h"
#include "PPP/Inc/ppp_mbuf.h"
#include "PPP/Inc/hdlc.h"
#include "PPP/Inc/throughput.h"
#include "PPP/Inc/proto.h"
#include "PPP/Inc/ppp_fsm.h"
#include "PPP/Inc/lcp.h"
#include "PPP/Inc/async.h"
#include "PPP/Inc/auth.h"
#include "PPP/Inc/ipcp.h"
#include "PPP/Inc/link.h"
#include "PPP/Inc/pap.h"
#include "PPP/Inc/ppp_input.h"
#include "PPP/Inc/ppp_atcmd.h"
#include "NVIM_Interface.h"
#if (FEATURE_ON == FEATURE_HARDWARE_HDLC_FUNC)
#include "PPP/Inc/hdlc_hardware.h"
#endif
#include "TtfNvInterface.h"
#include "NasNvInterface.h"
#include "TafNvInterface.h"

/*****************************************************************************
    协议栈打印打点方式下的.C文件宏定义
*****************************************************************************/
/*lint -e767  修改人: z57034; 检视人: g45205 原因简述: 打点日志文件宏ID定义 */
#define    THIS_FILE_ID        PS_FILE_ID_PPP_INIT_C
/*lint +e767  修改人: z57034; 检视人: g45205 */

/******************************************************************************
   PPP任务优先级高于modem_send高，比modem_recv任务低
******************************************************************************/
#define PPP_TASK_PRI                                  143

extern VOS_VOID PPP_ProcDataNotify(VOS_VOID);
extern VOS_UINT32  PPP_Snd1stDataNotify(VOS_VOID);
extern VOS_VOID PPP_ProcAsFrmDataInd(struct MsgCB * pMsg);

/*Add by y45445 for PS FUSION PC ST*/
#ifdef WTTF_PS_FUSION_PC_ST
extern PPP_ID   PPP_STUB_SetUp();
extern VOS_VOID PPP_STUB_Config(PPP_ID usPppId, PPP_HDLC_CTRL_STRU *pstParam);
#endif

#if (VOS_OS_VER == VOS_WIN32)
extern VOS_UINT32  VHW_HDLC_Init( VOS_VOID );
#endif
/*Add by y45445 for PS FUSION PC ST*/

/******************************************************************************
   3 私有定义
******************************************************************************/


/******************************************************************************
   4 全局变量定义
******************************************************************************/
/* 保存从NV项中读取的WINS特性开关值*/
VOS_UINT8  g_ucPppConfigWins = WINS_CONFIG_ENABLE;

/* 队列自旋锁 */
extern      VOS_SPINLOCK           g_stPppASpinLock;

/******************************************************************************
   5 函数实现
******************************************************************************/
/*****************************************************************************
 Prototype      : PPP_UpdateWinsConfig()
 Description    : 更新PPP模块的WINS设置
 Input          :
 Output         :
 Return Value   : VOID
 Calls          :
 Called By      :
 History        :
  1.Date        : 2009-07-13
    Author      : L47619
    Modification: Created function
*****************************************************************************/
VOS_VOID PPP_UpdateWinsConfig(VOS_UINT8 ucWins)
{
    if ((WINS_CONFIG_DISABLE != ucWins) && (WINS_CONFIG_ENABLE != ucWins))
    {
        /* ucWins值无效 */
        return;
    }

    /* 更新g_ucPppConfigWins */
    g_ucPppConfigWins = ucWins;

    return;
}

/*****************************************************************************
 Prototype      : PPP_DataQInit()
 Description    : PPP数据队列的初始化
 Input          : VOS_VOID
 Output         :
 Return Value   : VOID
 Calls          :
 Called By      :
 History        :
  1.Date        : 2008-07-16
    Author      : L47619
    Modification: Created function
*****************************************************************************/
VOS_VOID PPP_DataQInit(VOS_VOID)
{
    PPP_ZC_QUEUE_STRU                    *pstDataQ;


    pstDataQ    = &(g_PppDataQCtrl.stDataQ);

    VOS_MemSet(&g_PppDataQCtrl, 0, sizeof(g_PppDataQCtrl));

    PPP_ZC_QUEUE_INIT(pstDataQ);

    return;
}


/*****************************************************************************
 Prototype      : PPP_DataQClear()
 Description    : 清除PPP数据队列内容
 Input          : VOS_VOID
 Output         :
 Return Value   : VOID
 Calls          :
 Called By      :
 History        :
  1.Date        : 2008-07-16
    Author      : L47619
    Modification: Created function
*****************************************************************************/
VOS_VOID PPP_ClearDataQ(VOS_VOID)
{
    PPP_ZC_STRU    *pstMem;


    for(;;)
    {
        if ( 0 == PPP_ZC_GET_QUEUE_LEN(&g_PppDataQCtrl.stDataQ) )
        {
            break;
        }

        pstMem  = (PPP_ZC_STRU *)PPP_ZC_DEQUEUE_HEAD(&g_PppDataQCtrl.stDataQ);

        PPP_MemFree(pstMem);
    }

    PPP_MNTN_LOG(PS_PID_APP_PPP, 0, PS_PRINT_NORMAL,
                                  "PPP, PPP_ClearDataQ, NORMAL, Clear Stat Info\n");

    return;
} /* PPP_ClearDataQ */


/*****************************************************************************
 Prototype      : PPP_GetMruConfig()
 Description    : 定制需求,通过NV项获取PPP用户配置MRU
 Input          : VOS_VOID
 Output         :
 Return Value   : VOS_UINT16 用户配置的MRU
 Calls          :
 Called By      :
 History        :
  1.Date        : 2009-07-13
    Author      : x00138766
    Modification: Created function
*****************************************************************************/
VOS_UINT16 PPP_GetMruConfig(VOS_VOID)
{
    VOS_UINT16                      usPppConfigMru  = DEF_MRU;
    VOS_UINT32                      ulRslt;
    PPP_CONFIG_MRU_TYPE_NV_STRU     stPppConfigMruType;


    PS_MEM_SET(&stPppConfigMruType, 0x00, sizeof(PPP_CONFIG_MRU_TYPE_NV_STRU));

    /* 为客户定制PPP Default MRU而使用NV_Item，由于此NV结构为16bit，考虑到字节对齐因素，
       长度固定写sizeof(VOS_UINT16) */
    ulRslt = NV_ReadEx(MODEM_ID_0, en_NV_Item_PPP_CONFIG_MRU_Type, &stPppConfigMruType, sizeof(VOS_UINT16));
    usPppConfigMru  = stPppConfigMruType.usPppConfigType;

    if (NV_OK != ulRslt)
    {
        usPppConfigMru = DEF_MRU;
        PPP_MNTN_LOG(PS_PID_APP_PPP, 0, PS_PRINT_WARNING,
                     "Warning: Read en_NV_Item_PPP_DEFAULT_MRU_Type Error!");
    }

    if (usPppConfigMru > MAX_MRU)
    {
        usPppConfigMru = MAX_MRU;
    }

    if (usPppConfigMru < MIN_MRU)
    {
        usPppConfigMru = MIN_MRU;
    }

    PPP_MNTN_LOG1(PS_PID_APP_PPP, 0, PS_PRINT_INFO,
        "[INFO] PPP -- NV config MRU : <1>", (VOS_INT32)usPppConfigMru);

    return usPppConfigMru;
}


/*****************************************************************************
 Prototype      : PPP_GetConfigWINS()
 Description    : 定制需求,通过NV项获取PPP用户配置WINS协商使能开关
 Input          : VOS_VOID
 Output         :
 Return Value   : VOS_UINT8 WINS开关
 Calls          :
 Called By      :
 History        :
  1.Date        : 2009-07-13
    Author      : x00138766
    Modification: Created function
*****************************************************************************/
VOS_UINT8 PPP_GetWinsConfig(VOS_VOID)
{
    WINS_CONFIG_STRU    stWins;

    /* 定制需求,读取WINS特性控制开关NV项 */

    /* 若读取en_NV_Item_WINS失败,则默认WINS设置为使能 */
    if(NV_OK != NV_ReadEx(MODEM_ID_0, en_NV_Item_WINS_Config, &stWins, sizeof(WINS_CONFIG_STRU)))
    {
        PPP_MNTN_LOG(PS_PID_APP_PPP, 0, PS_PRINT_WARNING, "Warning: Read en_NV_Item_WINS_Config Error!");
        return WINS_CONFIG_ENABLE;
    }

    /* 若en_NV_Item_WINS未设置，则默认WINS设置为使能 */
    if (0 == stWins.ucStatus)
    {
        return WINS_CONFIG_ENABLE;
    }

    /* 若en_NV_Item_WINS设置值无效，则默认WINS设置为使能 */
    if ((WINS_CONFIG_ENABLE != stWins.ucWins) && (WINS_CONFIG_DISABLE != stWins.ucWins))
    {
        return WINS_CONFIG_ENABLE;
    }

    PPP_MNTN_LOG1(PS_PID_APP_PPP, 0, PS_PRINT_INFO,
                  "PPP_GetWinsConfig,[INFO] PPP -- NV config WINS : %d", (VOS_INT32)stWins.ucWins);

    return stWins.ucWins;
}


/*****************************************************************************
 Prototype      : PppInit
 Description    : TAF PPP模块中的初始化函数,该函数将向系统申请建立PPP模块运行
                  所需要的各种资源。如果成功将返回VOS_OK，否则为VOS_ERR。
 Input          : ---
 Output         : ---
 Return Value   : ---VOS_UINT32
 Calls          : ---
 Called By      : ---

 History        : ---
  1.Date        : 2005-11-18
    Author      : ---
    Modification: Created function
  2. 2006-03-13 MODIFY BY F49086 FOR A32D02474
  3.Date        : 2006-05-22
    Author      : L47619
    Modification: Modify for PN:A32D04462
  4.Date        : 2006-10-08
    Author      : L47619
    Modification: Modify for PN:A32D06578
  5.Data        : 2009-7-14
    Author      : x00138766
    Modification: 增加WINS协商使能开关特性
*****************************************************************************/
VOS_UINT32    PppInit(enum VOS_INIT_PHASE_DEFINE InitPhase )
{
    VOS_INT32               i;

    /*Add by y45445 for PS FUSION PC ST*/
    #ifdef WTTF_PS_FUSION_PC_ST
    VOS_UINT16              usPppId;
    PPP_HDLC_CTRL_STRU      stParam;
    #endif
    /*Add by y45445 for PS FUSION PC ST*/

    switch( InitPhase )
    {
    case   VOS_IP_LOAD_CONFIG:


           /*定制需求,通过NV项,获取用户配置MRU以及WINS协商开关*/
           /*读取NV项,获取用户配置MRU*/
           g_usPppConfigMru = PPP_GetMruConfig();

           /*读取NV项,获取用户配置WINS使能开关*/
           g_ucPppConfigWins = PPP_GetWinsConfig();


            /*向系统申请分配一块全局所用的link数组的空间*/
            /*lint -e433*/
            pgPppLink = (struct link *)VOS_MemAlloc(PS_PID_APP_PPP, STATIC_MEM_PT, sizeof(struct link)*PPP_MAX_ID_NUM);
            /*lint +e433*/
            if (VOS_NULL_PTR == pgPppLink)
            {
                /*输出错误信息*/
                PPP_MNTN_LOG(PS_PID_APP_PPP, 0, PS_PRINT_ERROR,"PppInit, malloc of  memory fail\r\n");
                return VOS_ERR;
            }

            /*向系统申请分配一块全局所用的TAF_PPP_PUBLIC_STRU的空间*/
            pgPppId = (PPP_ID *)VOS_MemAlloc(PS_PID_APP_PPP, STATIC_MEM_PT, sizeof(PPP_ID)*PPP_MAX_ID_NUM_ALLOC);
            if (VOS_NULL_PTR == pgPppId)
            {
                /*释放申请的全局所用的TAF_PPP_PUBLIC_STRU的空间*/
                VOS_MemFree(PS_PID_APP_PPP, pgPppLink);
                pgPppLink = VOS_NULL_PTR;


                /*输出错误信息*/
                PPP_MNTN_LOG(PS_PID_APP_PPP, 0, PS_PRINT_ERROR,"PppInit, malloc of  memory fail\r\n");
                return VOS_ERR;
            }

            /*对于系统所用到的所有数据结构都初始化*/
            for(i = 0;i < PPP_MAX_ID_NUM; i++)
            {
                link_Init((pgPppLink + i));
            }

            PppIdInit();

            /*初始化PPP的数据队列*/
            PPP_DataQInit();

            #if (FEATURE_ON == FEATURE_HARDWARE_HDLC_FUNC)
            /* 初始化HDLC */
            if (VOS_OK != PPP_HDLC_HARD_Init())
            {
                return VOS_ERR;
            }
            #endif

            #if (VOS_OS_VER == VOS_WIN32)
            VHW_HDLC_Init();
            #endif

            /*Add by y45445 for PS FUSION PC ST*/
            #ifdef WTTF_PS_FUSION_PC_ST
            usPppId = PPP_STUB_SetUp();
            stParam.ulAccm                =   0xFFFFFFFF;
            stParam.ulAcfComp          =   0;
            stParam.ulProtoComp      =   0;

            PPP_STUB_Config( usPppId, &stParam);
            #endif
            /*Add by y45445 for PS FUSION PC ST*/
            break;

    case   VOS_IP_FARMALLOC:
    case   VOS_IP_INITIAL:
    case   VOS_IP_ENROLLMENT:
    case   VOS_IP_LOAD_DATA:
    case   VOS_IP_FETCH_DATA:
    case   VOS_IP_STARTUP:
    case   VOS_IP_RIVAL:
    case   VOS_IP_KICKOFF:
    case   VOS_IP_STANDBY:
    case   VOS_IP_BROADCAST_STATE:
    case   VOS_IP_RESTART:
    case   VOS_IP_BUTT:
           break;
    }

    return VOS_OK;
}


/*****************************************************************************
 Prototype      : PppMsgTimerProc
 Description    : PPP模块中的定时器消息处理函数
 Input          : ---
 Output         : ---
 Return Value   : ---VOS_VOID
 Calls          : ---
 Called By      : ---

 History        : ---
  1.Date        : 2005-11-18
    Author      : fanzhibin
    Modification: Created function
  2.Date        : 2006-05-22
    Author      : L47619
    Modification: Modify for PN:A32D04462
  3.Date        : 2007-01-05
    Author      : L47619
    Modification: Modify for PN:A32D08013
  4.Date        : 2008-10-28
    Author      : liukai
    Modification: support CHAP authentication timer
*****************************************************************************/
VOS_VOID PppMsgTimerProc( struct MsgCB * pMsg )
{
    REL_TIMER_MSG  *pPsMsg = (REL_TIMER_MSG  *)pMsg;
    VOS_UINT16      usPppId = (VOS_UINT16)(pPsMsg->ulName);
#if (FEATURE_ON == FEATURE_HARDWARE_HDLC_FUNC)
    VOS_UINT32      ulFlags = 0UL;
#endif


    /*判断是那个阶段启动的定时器*/
    switch(pPsMsg->ulPara)
    {
        /*如果是LCP阶段启动的定时器*/
        case PHASE_ESTABLISH:
            if (PPP_LINK(usPppId)->phase == PHASE_ESTABLISH)
            {
                FsmTimeout(&(PPP_LINK(usPppId)->lcp.fsm),
                    pPsMsg->ulPara);
            }

            break;

        /*如果是终止阶段启动的定时器*/
        case PHASE_TERMINATE:
            if (PPP_LINK(usPppId)->phase == PHASE_TERMINATE)
            {
                FsmTimeout(&(PPP_LINK(usPppId)->lcp.fsm),
                    pPsMsg->ulPara);
            }

            break;

        /*如果是认证阶段启动的定时器*/
        case PHASE_AUTHENTICATE:
            {
                if (PPP_LINK(usPppId)->phase == PHASE_AUTHENTICATE)
                {
                    AuthTimeout(PPP_LINK(usPppId));
                }

                break;
            }

        /*如果是IPCP阶段启动的定时器*/
        case PHASE_NETWORK:
            if (PPP_LINK(pPsMsg->ulName)->phase == PHASE_NETWORK)
            {
                FsmTimeout(&(PPP_LINK(usPppId)->ipcp.fsm),
                    pPsMsg->ulPara);
            }

            break;

        /*如果是IPCP阶段待PDP激活的定时器,则处理待处理的IPCP帧*/
        case PHASE_PDP_ACT_PENDING:
            if (VOS_NULL_PTR != PPP_LINK(usPppId)->ipcp.pstIpcpPendFrame)
            {
                fsm_Input(&(PPP_LINK(usPppId)->ipcp.fsm), PPP_LINK(usPppId)->ipcp.pstIpcpPendFrame);
                PPP_LINK(usPppId)->ipcp.pstIpcpPendFrame = VOS_NULL_PTR;
            }
            PPP_LINK(usPppId)->ipcp.hIpcpPendTimer = VOS_NULL_PTR;
            break;

        case PHASE_TERMINATE_PENDING:
            PPP_LINK(usPppId)->lcp.hLcpCloseTimer = VOS_NULL_PTR;
            PPP_ProcPppDisconnEvent(usPppId);
            break;

#if (FEATURE_ON == FEATURE_HARDWARE_HDLC_FUNC)
        case HDLC_FRM_OUTPUT_SPACE_ALLOC_FAIL:
            g_stHdlcConfigInfo.stHdlcFrmTimerHandle = VOS_NULL_PTR;

            /*lint -e571*/
            VOS_SpinLockIntLock(&g_stPppASpinLock, ulFlags);
            /*lint +e571*/

            g_PppDataQCtrl.ulNotifyMsgCnt++;
            g_PppDataQCtrl.stStat.ulSndMsgCnt++;
            VOS_SpinUnlockIntUnlock(&g_stPppASpinLock , ulFlags);

            PPP_Snd1stDataNotify();
            break;
#endif

        default:
            {
                PPP_MNTN_LOG(PS_PID_APP_PPP, 0, PS_PRINT_WARNING,"unknow timer!\r\n");
            }
    }


    return;
}


/*****************************************************************************
 Prototype      : PppMsgProc
 Description    : TAF PPP模块中的消息处理函数，他处理定时器消息以及从AT模块接
                  收到数据帧的消息。如果成功将返回VOS_OK，否则为VOS_ERR。
 Input          : ---
 Output         : ---
 Return Value   : ---VOS_VOID
 Calls          : ---
 Called By      : ---

 History        : ---
  1.Date        : 2005-11-18
    Author      : ---
    Modification: Created function
  2.Date        : 2006-05-17
    Author      : L47619
    Modification: Modified for PN:A32D04462
*****************************************************************************/
VOS_VOID PppMsgProc( struct MsgCB * pMsg )
{
    PPP_MSG    *pPsMsg  = (PPP_MSG *)pMsg;


    /*PPP_MNTN_LOG(PS_PID_APP_PPP, 0, PS_PRINT_INFO, "\r\nPppMsgProc, INFO, Enter!\r\n");
 */

    if(pMsg == VOS_NULL_PTR)
    {
        return;
    }

    #if (FEATURE_ON == FEATURE_HARDWARE_HDLC_FUNC)
    PPP_HDLC_HARD_PeriphClkOpen();
    #endif

    /*如果是定时器发来的消息*/
    if (VOS_PID_TIMER == pMsg->ulSenderPid)
    {
        PppMsgTimerProc(pMsg);

        #if (FEATURE_ON == FEATURE_HARDWARE_HDLC_FUNC)
        PPP_HDLC_HARD_PeriphClkClose();
        #endif

        return ;
    }

    /*如果是接收到从TE发送来的数据帧*/
    switch(pPsMsg->ulMsgType)
    {
        #if (PPP_FEATURE == PPP_FEATURE_PPP)
        case PPP_DATA_PROC_NOTIFY:
            PPP_ProcDataNotify();
            break;

        case PPP_AT_CTRL_OPERATION:
            PPP_ProcAtCtrlOper(pMsg);
            break;

        case PPP_HDLC_PROC_AS_FRM_PACKET_IND:
            PPP_ProcAsFrmDataInd(pMsg);
            break;

        #endif
/*Add by y45445 for PS FUSION PC ST*/
#ifdef WTTF_PS_FUSION_PC_ST
        case AT_PPP_UL_DATA_REQ:
           PPP_STUB_RcvUlData(pMsg);
           break;
        case PPP_AT_DL_DATA_IND:
              break;
#endif
/*Add by y45445 for PS FUSION PC ST*/
        default:
            break;
    }

    #if (FEATURE_ON == FEATURE_HARDWARE_HDLC_FUNC)
    PPP_HDLC_HARD_PeriphClkClose();
    #endif

    return;
}

/*****************************************************************************
 Prototype      : PPP_PowerOff()
 Description    : 软关机过程中，用以回收PPP模块资源
 Input          : VOS_VOID
 Output         :
 Return Value   : VOID
 Calls          :
 Called By      :
 History        :
  1.Date        : 2007-08-28
    Author      : l47619
    Modification: 根据问题单新增:A32D12744
*****************************************************************************/
VOS_VOID    PPP_PowerOff(VOS_VOID)
{
    VOS_UINT8   ucPppId;

    /*软关机时若定时器还在运行，则停止该定时器:*/
    for(ucPppId = 1; ucPppId <= PPP_MAX_ID_NUM; ucPppId++)
    {
        /*LCP状态机定时器:*/
        if( VOS_NULL_PTR !=((PPP_LINK(ucPppId))->lcp.fsm.timer) )
        {
            VOS_StopRelTimer(&((PPP_LINK(ucPppId))->lcp.fsm.timer));
        }

        /*IPCP状态机定时器:*/
        if( VOS_NULL_PTR !=((PPP_LINK(ucPppId))->ipcp.fsm.timer) )
        {
            VOS_StopRelTimer(&((PPP_LINK(ucPppId))->ipcp.fsm.timer));
        }
    }

    /*释放PPP数据队列*/
    PPP_ClearDataQ();
    return;
}


/*****************************************************************************
 Prototype      : PppStop
 Description    : TAF PPP模块中的结束函数,该函数负责在系统重新启动时释放PPP模
                  块向系统申请的资源
 Input          : ---
 Output         : ---
 Return Value   : ---VOS_UINT32
 Calls          : ---
 Called By      : ---

 History        : ---
  1.Date        : 2005-11-18
    Author      : ---
    Modification: Created function
*****************************************************************************/
#define PPP_FREE(point)\
    if(point!=VOS_NULL_PTR)         \
    {                                   \
        /*释放申请的全局所用的空间*/    \
        VOS_MemFree(PS_PID_APP_PPP, point);   \
        point = VOS_NULL_PTR;  \
    }\

VOS_VOID    PppStop(VOS_VOID)
{
    /*VOS_UINT32    dis_interrupt;*/
    VOS_INT32 i;



    /*对于系统所用到的throughout结构都释放掉它申请的内存*/
    for(i = 0;i < PPP_MAX_ID_NUM; i++)
    {
        throughput_destroy(&((pgPppLink + i)->stats.total));
    }

    PPP_FREE(pgPppLink)
    PPP_FREE(pgPppId)

    return;
}

#else

/*****************************************************************************
  1 头文件包含
*****************************************************************************/
#include "AtPppInterface.h"
#include "ppp_init.h"

/*****************************************************************************
  3 函数实现
*****************************************************************************/

/*****************************************************************************
 Prototype      : PPP_UpdateWinsConfig()
 Description    : 更新PPP模块的WINS设置
 Input          :
 Output         :
 Return Value   : VOID
 Calls          :
 Called By      :
 History        :
  1.Date        : 2009-07-13
    Author      : L47619
    Modification: Created function
*****************************************************************************/
VOS_VOID PPP_UpdateWinsConfig(VOS_UINT8 ucWins)
{
    return;
}

VOS_UINT32    PppInit(enum VOS_INIT_PHASE_DEFINE InitPhase )
{
    switch (InitPhase)
    {
        case VOS_IP_INITIAL:
            break;

        default:
            break;
    }

    return VOS_OK;
}

VOS_VOID PppMsgProc( struct MsgCB * pMsg )
{
    /*消息为空，直接返回*/
    if (VOS_NULL_PTR == pMsg)
    {
        return;
    }

    return;
}

#endif /*#if(FEATURE_ON == FEATURE_PPP)*/



#ifdef  __cplusplus
  #if  __cplusplus
  }
  #endif
#endif

