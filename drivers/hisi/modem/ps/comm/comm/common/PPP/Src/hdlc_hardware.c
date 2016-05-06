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

/******************************************************************************
   头文件包含
******************************************************************************/
#include "product_config.h"
#include "TTFComm.h"
#include "soc_sctrl_interface.h"

#if (VOS_RTOSCK == VOS_OS_VER)
#include "TTFMem.h"
#include "cttf_1x_rrlp_data_pif.h"
#include "ppp_trans_data_pif.h"
#include "rlp_ppp_pub_pif.h"
#include "ppp_inc.h"
#include "pppc_ctrl.h"
#include "ppp_dbug.h"
#include "fwd_ppp.h"
#else
#include "PPP/Inc/ppp_public.h"
#endif

#include "mdrv.h"
#include "PPP/Inc/hdlc_hardware.h"

#ifdef __cplusplus
    #if __cplusplus
        extern "C" {
    #endif
#endif
/*lint -e732*/
/*lint -e40*/
/*lint -e718*/
/*lint -e746*/

/*****************************************************************************
   1 协议栈打印打点方式下的.C文件宏定义
*****************************************************************************/
/*lint -e767 */
#define    THIS_FILE_ID        PS_FILE_ID_HDLC_HARDWARE_C
/*lint +e767 */


/******************************************************************************
   2 外部函数变量声明
******************************************************************************/
#if (VOS_OS_VER == VOS_WIN32)
extern VOS_UINT32  VHW_HDLC_Task( VOS_VOID );
extern VOS_UINT8   g_ucScCtrlRegAddr[0xFFC];
#endif


/*****************************************************************************
   3 私有定义
*****************************************************************************/
VOS_UINT32 PPP_HDLC_HARD_DefIsr(unsigned int ulPara);

VOS_UINT32 PPP_HDLC_HARD_FrmIsr(unsigned int ulPara);


#define  PPP_HDLC_MNTN_TRACE_PARA       (1)
#define  PPP_HDLC_MNTN_TRACE_REG        (2)
#define  PPP_HDLC_MNTN_TRACE_DATA       (4)

/*****************************************************************************
   4 全局变量定义
*****************************************************************************/
/* 解封装输出的非完整帧信息 */
HDLC_DEF_UNCOMPLETED_INFO_STRU  g_stUncompletedInfo = {0};

/* 保存解封装使用的内存 */
HDLC_DEF_BUFF_INFO_STRU        *g_pstHdlcDefBufInfo = VOS_NULL_PTR;

/* 保存封装使用的内存 */
HDLC_FRM_BUFF_INFO_STRU        *g_pstHdlcFrmBufInfo = VOS_NULL_PTR;

/* HDLC配置相关信息 */
HDLC_CONFIG_INFO_STRU           g_stHdlcConfigInfo  =
{
    0,
    0,
    0,
    0,
    0,
    HDLC_DEF_INTERRUPT_LIMIT_DEFAULT,
    HDLC_FRM_INTERRUPT_LIMIT_DEFAULT,
    VOS_NULL_PTR,
    0
};

/* 统计信息 */
PPP_HDLC_HARD_DATA_PROC_STAT_ST g_PppHdlcHardStat   = {0};

/* 保留清原始中断时的RAW_INT和STATUS值 */
HDLC_REG_SAVE_INFO_STRU         g_stHdlcRegSaveInfo;

#define    HDLC_IP_BASE_ADDR    (g_stHdlcConfigInfo.ulHDLCIPBaseAddr)

/* 系统控制器基地址 */
VOS_UINT_PTR    g_ulHdlcScCtrlBaseAddr  = 0;

VOS_UINT_PTR    g_ulPppVirtAddr         = 0;
VOS_UINT_PTR    g_ulPppPhyAddr          = 0;
VOS_UINT_PTR    g_ulPppTotalBufLen      = 0;

/******************************************************************************
   5 函数实现
******************************************************************************/

#if (VOS_RTOSCK == VOS_OS_VER)

/* PPPC的数据队列统计信息结构体 */
extern PPP_DATA_Q_STAT_STRU             g_stPppcDataQueueStats;

#ifdef PPPC_HDLC_ST_TEST
VOS_VOID   PPPC_STUB_ProcDlData(PPPC_DATA_LINK_NODE_STRU *pstMem);
VOS_UINT32 PPPC_STUB_ProcUlData(PPPC_DATA_LINK_NODE_STRU *pstData, VOS_UINT16 usDataLen);
#endif

/*****************************************************************************
 函 数 名  : PPP_MemAlloc
 功能描述  : 分配零拷贝内存
 输入参数  : usLen      -- 数据块长度,单位为字节
 输出参数  : 无
 返 回 值  : 零拷贝内存指针
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2015-04-27
    作    者   : c00184031
    修改内容   : Created
*****************************************************************************/
PPPC_DATA_LINK_NODE_STRU * PPP_MemAlloc
(
    VOS_UINT16                          usLen,
    TTF_MEM_POOL_ID_ENUM_UINT32         ulPoolId
)
{
    /* 该接口用在上行时需要保留MAC头长度，
      上行与ADS收发数为IP包，为与NDIS、E5保持数据结构统一，需要保留MAC头，
      零拷贝指针从C核返回的时候统一偏移固定字节，找到零拷贝头部。
    */
    /*
       用在下行时保留长度填0，下行与USB收发数据为字节流形式的PPP帧，无MAC头
    */
    PPPC_DATA_LINK_NODE_STRU           *pstNode = VOS_NULL_PTR;
    TTF_MEM_ST                         *pstMem  = VOS_NULL_PTR;


    /* 申请节点 */
    pstNode = (PPPC_DATA_LINK_NODE_STRU *)TTF_NODE_MEM_ALLOC(PS_PID_PPP_HDLC, sizeof(PPPC_DATA_LINK_NODE_STRU));

    if (VOS_NULL_PTR != pstNode)
    {
        pstMem  = TTF_MemBlkAlloc(PS_PID_PPP_HDLC, ulPoolId, (VOS_UINT32)usLen);
        if (VOS_NULL_PTR != pstMem)
        {
            PPP_MemSet(pstNode, 0, sizeof(PPPC_DATA_LINK_NODE_STRU));
            pstNode->pstPduMem    = pstMem;
            pstNode->ulTimeStamp  = mdrv_timer_get_normal_timestamp();
            pstNode->ucPdnId      = 0;
            TTF_NodeInit(&(pstNode->stNode));

            if (TTF_MEM_POOL_ID_UL_DATA == ulPoolId)
            {
                /* 更新上行申请总次数 */
                g_stPppcDataQueueStats.ulMemAllocUplinkCnt++;
            }
            else
            {
                /* 更新下行申请总次数 */
                g_stPppcDataQueueStats.ulMemAllocDownlinkCnt++;
            }

            return pstNode;
        }
        else
        {
            PPP_HDLC_WARNING_LOG1("alloc ttf memory fail. allocMemlen:%d\n", usLen);
            TTF_NODE_MEM_FREE(PS_PID_PPP_HDLC, pstNode);
        }
    }
    else
    {
        PPP_HDLC_WARNING_LOG1("alloc node memory fail. allocMemlen:%d\n", sizeof(PPPC_DATA_LINK_NODE_STRU));
    }

    if (TTF_MEM_POOL_ID_UL_DATA == ulPoolId)
    {
        /* 更新上行申请失败次数 */
        g_stPppcDataQueueStats.ulMemAllocUplinkFailCnt++;
    }
    else
    {
        /* 更新下行申请失败次数 */
        g_stPppcDataQueueStats.ulMemAllocDownlinkFailCnt++;
    }

    return VOS_NULL_PTR;
}

/*****************************************************************************
 函 数 名  : PPP_MemFree
 功能描述  : 释放零拷贝内存
 输入参数  : pstNode  --- TTF_MEM形式的数据
 输出参数  :
 返 回 值  : 无
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2015-04-027
    作    者   : c00184031
    修改内容   : Created
*****************************************************************************/
VOS_VOID PPP_MemFree(PPPC_DATA_LINK_NODE_STRU *pstNode)
{
    if (VOS_NULL_PTR == pstNode)
    {
        return;
    }

    if (VOS_NULL_PTR != pstNode->pstPduMem)
    {
        TTF_MemFree(PS_PID_PPP_HDLC, pstNode->pstPduMem);
        pstNode->pstPduMem = VOS_NULL_PTR;
    }

    if (VOS_NULL_PTR != pstNode->pstUlDataInfo)
    {
        PS_MEM_FREE(PS_PID_PPP_HDLC, pstNode->pstUlDataInfo);
        pstNode->pstUlDataInfo  = VOS_NULL_PTR;
    }

    /* 释放零拷贝内存 */
    TTF_NODE_MEM_FREE(PS_PID_PPP_HDLC, pstNode);

    g_stPppcDataQueueStats.ulMemFreeCnt++;

    return;
}

/*****************************************************************************
 函 数 名  : PPP_MemSingleCopy
 功能描述  : 获取给定内存单元实际使用的总字节数，包括整个数据链
 输入参数  : pMemSrc  -- 要获取数据的TTF内存块头指针
 输出参数  : 无
 返 回 值  : 数据长度
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2011-03-09
    作    者   : l00164359
    修改内容   : Created
*****************************************************************************/
VOS_VOID PPP_MemSingleCopy(VOS_UINT8 *pucDest, VOS_UINT8 *pucSrc, VOS_UINT32 ulLen)
{
    /* 待修改为EDMA拷贝 */
    PS_MEM_CPY(pucDest, pucSrc, ulLen);

    return;
}
#endif

/*****************************************************************************
 函 数 名  : PPP_HDLC_HARD_PeriphClkOpen
 功能描述  : 打开HDLC时钟
 输入参数  : 无
 输出参数  : 无
 返 回 值  : 无
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2013年6月13日
    作    者   : c00191211
    修改内容   : 新生成函数

*****************************************************************************/
VOS_VOID PPP_HDLC_HARD_PeriphClkOpen(VOS_VOID)
{
    VOS_UINT32      ulValue = 0;

    ulValue |= (1 << HDLC_CRG_CLK_BITPOS);
    PPP_HDLC_WRITE_32REG(HDLC_CRG_CLKEN4_ADDR(g_ulHdlcScCtrlBaseAddr), ulValue);

    return;
}

/*****************************************************************************
 函 数 名  : PPP_HDLC_HARD_PeriphClkClose
 功能描述  : 关闭HDLC时钟
 输入参数  : 无
 输出参数  : 无
 返 回 值  : 无
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2013年6月13日
    作    者   : c00191211
    修改内容   : 新生成函数

*****************************************************************************/
VOS_VOID PPP_HDLC_HARD_PeriphClkClose(VOS_VOID)
{
    VOS_UINT32      ulValue = 0;

    ulValue |= (1 << HDLC_CRG_CLK_BITPOS);
    PPP_HDLC_WRITE_32REG(HDLC_CRG_CLKENDIS4_ADDR(g_ulHdlcScCtrlBaseAddr), ulValue);

    return;
}

/*****************************************************************************
 函 数 名  : PPP_HDLC_HARD_MntnSetConfig
 功能描述  : 设置可维可测等级
 输入参数  : ulConfig - 可维可测等级
 输出参数  : 无
 返 回 值  : 无
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2012年4月10日
    作    者   : l00164359
    修改内容   : 新生成函数

*****************************************************************************/
VOS_UINT32 PPP_HDLC_HARD_MntnSetConfig(VOS_UINT32 ulConfig)
{
    g_stHdlcConfigInfo.ulHdlcMntnTraceCfg = ulConfig;

    return g_stHdlcConfigInfo.ulHdlcMntnTraceCfg;
}

/*****************************************************************************
 函 数 名  : PPP_HDLC_HARD_MntnSetDefIntLimit
 功能描述  : 设置解封装中断水线
 输入参数  : ulIntLimit - 中断水线
 输出参数  : 无
 返 回 值  : 无
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2012年4月10日
    作    者   : l00164359
    修改内容   : 新生成函数

*****************************************************************************/
VOS_UINT32 PPP_HDLC_HARD_MntnSetDefIntLimit(VOS_UINT32 ulIntLimit)
{
    g_stHdlcConfigInfo.ulHdlcDefIntLimit = ulIntLimit;

    return g_stHdlcConfigInfo.ulHdlcDefIntLimit;
}

/*****************************************************************************
 函 数 名  : PPP_HDLC_HARD_MntnSetFrmIntLimit
 功能描述  : 设置封装中断水线
 输入参数  : ulIntLimit - 中断水线
 输出参数  : 无
 返 回 值  : 无
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2012年4月10日
    作    者   : l00164359
    修改内容   : 新生成函数

*****************************************************************************/
VOS_UINT32 PPP_HDLC_HARD_MntnSetFrmIntLimit(VOS_UINT32 ulIntLimit)
{
    g_stHdlcConfigInfo.ulHdlcFrmIntLimit = ulIntLimit;

    return g_stHdlcConfigInfo.ulHdlcFrmIntLimit;
}

/*****************************************************************************
 函 数 名  : PPP_HDLC_HARD_MntnTraceMsg
 功能描述  : 基础勾包函数
 输入参数  : pstHead    - 消息首地址
             ulMsgname  - 消息ID
             ulDataLen  - 消息长度
 输出参数  : 无
 返 回 值  : 无
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2012年4月10日
    作    者   : l00164359
    修改内容   : 新生成函数

*****************************************************************************/
VOS_VOID PPP_HDLC_HARD_MntnTraceMsg
(
    HDLC_MNTN_TRACE_HEAD_STRU          *pstHead,
    HDLC_MNTN_EVENT_TYPE_ENUM_UINT32    ulMsgname,
    VOS_UINT32                          ulDataLen
)
{
    pstHead->ulReceiverCpuId = VOS_LOCAL_CPUID;
    pstHead->ulReceiverPid   = PS_PID_PPP_HDLC;
    pstHead->ulSenderCpuId   = VOS_LOCAL_CPUID;
    pstHead->ulSenderPid     = PS_PID_PPP_HDLC;
    pstHead->ulLength        = ulDataLen - VOS_MSG_HEAD_LENGTH;

    pstHead->ulMsgname       = ulMsgname;

    PPP_MNTN_TRACE_MSG(pstHead);

    return;
}

/*****************************************************************************
 函 数 名  : PPP_HDLC_HARD_MntnDefTraceRegConfig
 功能描述  : 勾取解封装寄存器配置数据
 输入参数  : ulEnable   -   封装解封装使能前还是使能后，VOS_TRUE: 使能后,VOS_FALSE: 使能前
             ulValue    -   使能寄存器配置的值
             ulEnableInterrupt - 中断方式还是轮询方式，仅在使能后勾取寄存器时生效
 输出参数  : 无
 返 回 值  : 无
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2012年4月20日
    作    者   : l00164359
    修改内容   : 新生成函数

*****************************************************************************/
VOS_VOID PPP_HDLC_HARD_MntnDefTraceRegConfig
(
    VOS_UINT32      ulEnable,
    VOS_UINT32      ulValue,
    VOS_UINT32      ulEnableInterrupt
)
{
    HDLC_MNTN_DEF_REG_CONFIG_STRU           stRegConfig;
    HDLC_MNTN_DEF_REG_CONFIG_STRU          *pstRegConfig = &stRegConfig;
    VOS_UINT32                              ulDataLen;

    if ((g_stHdlcConfigInfo.ulHdlcMntnTraceCfg & PPP_HDLC_MNTN_TRACE_REG) != 0)
    {
        ulDataLen    = sizeof(HDLC_MNTN_DEF_REG_CONFIG_STRU);

        /* 拷贝全部寄存器内容 */
        pstRegConfig->ulStateSwRst             = PPP_HDLC_READ_32REG(SOC_ARM_HDLC_STATE_SW_RST_ADDR(HDLC_IP_BASE_ADDR));
        pstRegConfig->ulPriorTimeoutCtrl       = PPP_HDLC_READ_32REG(SOC_ARM_HDLC_PRIROR_TIMEOUT_CTRL_ADDR(HDLC_IP_BASE_ADDR));
        pstRegConfig->ulRdErrCurrAddr          = PPP_HDLC_READ_32REG(SOC_ARM_HDLC_RD_ERR_CURR_ADDR(HDLC_IP_BASE_ADDR));
        pstRegConfig->ulWrErrCurrAddr          = PPP_HDLC_READ_32REG(SOC_ARM_HDLC_WR_ERR_CURR_ADDR(HDLC_IP_BASE_ADDR));
        pstRegConfig->ulHdlcDefEn              = PPP_HDLC_READ_32REG(SOC_ARM_HDLC_DEF_EN_ADDR(HDLC_IP_BASE_ADDR));
        pstRegConfig->ulHdlcDefRawInt          = PPP_HDLC_READ_32REG(SOC_ARM_HDLC_DEF_RAW_INT_ADDR(HDLC_IP_BASE_ADDR));
        pstRegConfig->ulHdlcDefIntStatus       = PPP_HDLC_READ_32REG(SOC_ARM_HDLC_DEF_INT_STATUS_ADDR(HDLC_IP_BASE_ADDR));
        pstRegConfig->ulHdlcDefIntClr          = PPP_HDLC_READ_32REG(SOC_ARM_HDLC_DEF_INT_CLR_ADDR(HDLC_IP_BASE_ADDR));
        pstRegConfig->ulHdlcDefCfg             = PPP_HDLC_READ_32REG(SOC_ARM_HDLC_DEF_CFG_ADDR(HDLC_IP_BASE_ADDR));
        pstRegConfig->ulDefUncompletedLen      = PPP_HDLC_READ_32REG(SOC_ARM_HDLC_DEF_UNCOMPLETED_LEN_ADDR(HDLC_IP_BASE_ADDR));
        pstRegConfig->ulDefUncompletedPro      = PPP_HDLC_READ_32REG(SOC_ARM_HDLC_DEF_UNCOMPLETED_PRO_ADDR(HDLC_IP_BASE_ADDR));
        pstRegConfig->ulDefUncompletedAddr     = PPP_HDLC_READ_32REG(SOC_ARM_HDLC_DEF_UNCOMPLETED_ADDR(HDLC_IP_BASE_ADDR));
        pstRegConfig->ulDefUncompleteStAgo     = PPP_HDLC_READ_32REG(SOC_ARM_HDLC_DEF_UNCOMPLETED_ST_AGO_ADDR(HDLC_IP_BASE_ADDR));
        pstRegConfig->ulHdlcDefGoOn            = PPP_HDLC_READ_32REG(SOC_ARM_HDLC_DEF_GO_ON_ADDR(HDLC_IP_BASE_ADDR));
        pstRegConfig->ulHdlcDefStatus          = PPP_HDLC_READ_32REG(SOC_ARM_HDLC_DEF_STATUS_ADDR(HDLC_IP_BASE_ADDR));
        pstRegConfig->ulDefUncompletStNow      = PPP_HDLC_READ_32REG(SOC_ARM_HDLC_DEF_UNCOMPLETED_ST_NOW_ADDR(HDLC_IP_BASE_ADDR));
        pstRegConfig->ulDefInLliAddr           = PPP_HDLC_READ_32REG(SOC_ARM_HDLC_DEF_IN_LLI_ADDR(HDLC_IP_BASE_ADDR));
        pstRegConfig->ulDefInPktAddr           = PPP_HDLC_READ_32REG(SOC_ARM_HDLC_DEF_IN_PKT_ADDR(HDLC_IP_BASE_ADDR));
        pstRegConfig->ulDefInPktLen            = PPP_HDLC_READ_32REG(SOC_ARM_HDLC_DEF_IN_PKT_LEN_ADDR(HDLC_IP_BASE_ADDR));
        pstRegConfig->ulDefInPktLenMax         = PPP_HDLC_READ_32REG(SOC_ARM_HDLC_DEF_IN_PKT_LEN_MAX_ADDR(HDLC_IP_BASE_ADDR));
        pstRegConfig->ulDefOutSpcAddr          = PPP_HDLC_READ_32REG(SOC_ARM_HDLC_DEF_OUT_SPC_ADDR(HDLC_IP_BASE_ADDR));
        pstRegConfig->ulDefOutSpaceDep         = PPP_HDLC_READ_32REG(SOC_ARM_HDLC_DEF_OUT_SPACE_DEP_ADDR(HDLC_IP_BASE_ADDR));
        pstRegConfig->ulDefRptAddr             = PPP_HDLC_READ_32REG(SOC_ARM_HDLC_DEF_RPT_ADDR(HDLC_IP_BASE_ADDR));
        pstRegConfig->ulDefRptDep              = PPP_HDLC_READ_32REG(SOC_ARM_HDLC_DEF_RPT_DEP_ADDR(HDLC_IP_BASE_ADDR));
        pstRegConfig->ulHdlcDefErrInfor0       = PPP_HDLC_READ_32REG(SOC_ARM_HDLC_DEF_ERR_INFO_0_ADDR(HDLC_IP_BASE_ADDR));
        pstRegConfig->ulHdlcDefErrInfor1       = PPP_HDLC_READ_32REG(SOC_ARM_HDLC_DEF_ERR_INFO_1_ADDR(HDLC_IP_BASE_ADDR));
        pstRegConfig->ulHdlcDefErrInfor2       = PPP_HDLC_READ_32REG(SOC_ARM_HDLC_DEF_ERR_INFO_2_ADDR(HDLC_IP_BASE_ADDR));
        pstRegConfig->ulHdlcDefErrInfor3       = PPP_HDLC_READ_32REG(SOC_ARM_HDLC_DEF_ERR_INFO_3_ADDR(HDLC_IP_BASE_ADDR));
        pstRegConfig->ulDefInfoFr1CntAgo       = PPP_HDLC_READ_32REG(SOC_ARM_HDLC_DEF_INFO_FRL_CNT_AGO_ADDR(HDLC_IP_BASE_ADDR));
        pstRegConfig->ulDefInfoFr1CntNow       = PPP_HDLC_READ_32REG(SOC_ARM_HDLC_DEF_INFO_FRL_CNT_NOW_ADDR(HDLC_IP_BASE_ADDR));

        /* 使能前勾包，使能寄存器还没有配置，因为配置之后HDLC会开始工作，会改变其他寄存器的值 */
        if( VOS_FALSE == ulEnable)
        {
            pstRegConfig->ulHdlcDefEn   = ulValue;
            PPP_HDLC_HARD_MntnTraceMsg((HDLC_MNTN_TRACE_HEAD_STRU *)pstRegConfig,
                                       ID_HDLC_MNTN_DEF_REG_BEFORE_EN, ulDataLen);
        }
        else
        {
            /* 使能后勾包时，如果采用中断方式，则RawInt和Status取g_stHdlcRegSaveInfo保存的值 */
            if( VOS_TRUE == ulEnableInterrupt )
            {
                pstRegConfig->ulHdlcDefRawInt   = g_stHdlcRegSaveInfo.ulHdlcDefRawInt;
                pstRegConfig->ulHdlcDefStatus   = g_stHdlcRegSaveInfo.ulHdlcDefStatus;
            }
            PPP_HDLC_HARD_MntnTraceMsg((HDLC_MNTN_TRACE_HEAD_STRU *)pstRegConfig,
                                       ID_HDLC_MNTN_DEF_REG_AFTER_EN, ulDataLen);
        }
    }

    return;
}

/*****************************************************************************
 函 数 名  : PPP_HDLC_HARD_DefCfgGoOnReg
 功能描述  : 根据HDLC暂停状态，配置GO_ON寄存器对应比特位
 输入参数  : ulDefStatus  -   解封装状态
 输出参数  : 无
 返 回 值  : 无
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2012年4月10日
    作    者   : l00164359
    修改内容   : 新生成函数

*****************************************************************************/
VOS_VOID PPP_HDLC_HARD_DefCfgGoOnReg
(
    VOS_UINT32          ulDefStatus
)
{
    /*
    hdlc_def_go_on  (0x84)
     31                  17  16  15    9   8  7   1  0
    |----------------------|----|-------|----|-----|----|
    |         Rsv          |Goon|  Rsv  |Goon| Rsv |Goon|
    Reserved             [31:17] 15'b0   h/s R/W  保留位。读时返回0。写时无影响。
    def_rpt_ful_goon     [16]    1'b0    h/s WO   外部解封装有效帧信息上报空间存满暂停解除
    Reserved             [15:9]  7'b0    h/s R/W  保留位。读时返回0。写时无影响。
    def_outspc_ful_goon  [8]     1'b0    h/s WO   外部解封装输出数据存储空间存满暂停状态清除
    Reserved             [7:1]   7'b0    h/s R/W  保留位。读时返回0。写时无影响。
    def_lcp_goon         [0]     1'b0    h/s WO   解出一个合法LCP帧导致的硬件暂停状态清除。当解封装模块未处理完一组待解封装的数据（<=2KB(def_in_pkt_len_max)），解出一个合法LCP帧，则会暂停解帧，等待此软件向此寄存器写"1"，再继续处理剩余的数据。
    */

    /* GO_ON前清除上次解封装的原始中断 */
    PPP_HDLC_WRITE_32REG(SOC_ARM_HDLC_DEF_INT_CLR_ADDR(HDLC_IP_BASE_ADDR), 0xFFFFFFFFU);

    if (HDLC_DEF_STATUS_PAUSE_RPT_SPACE_FULL == ulDefStatus )
    {
        PPP_HDLC_WRITE_32REG(SOC_ARM_HDLC_DEF_GO_ON_ADDR(HDLC_IP_BASE_ADDR),
                        (VOS_UINT32)0x10000);
    }
    else if (HDLC_DEF_STATUS_PAUSE_OUTPUT_SPACE_FULL == ulDefStatus )
    {
        PPP_HDLC_WRITE_32REG(SOC_ARM_HDLC_DEF_GO_ON_ADDR(HDLC_IP_BASE_ADDR),
                        (VOS_UINT32)0x100);
    }
    else if (HDLC_DEF_STATUS_PAUSE_LCP == ulDefStatus )
    {
        PPP_HDLC_WRITE_32REG(SOC_ARM_HDLC_DEF_GO_ON_ADDR(HDLC_IP_BASE_ADDR),
                        (VOS_UINT32)0x1);
    }
    else
    {
        PPP_HDLC_ERROR_LOG1("PPP_HDLC_HARD_DefCfgGoOnReg, ERROR, Wrong ulDefStatus %d!\r\n", ulDefStatus);
    }

    /* PC上使用HDLC模拟器 */
#if (VOS_OS_VER == VOS_WIN32)
    VHW_HDLC_Task();
#endif

    return;
}

/*****************************************************************************
 函 数 名  : PPP_HDLC_HARD_MntnDefTraceUncompleteInfo
 功能描述  : 勾取解封装输出的非完整帧信息
 输入参数  : pstUncompletedInfo -   非完整帧信息
 输出参数  : 无
 返 回 值  : 无
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2012年4月10日
    作    者   : l00164359
    修改内容   : 新生成函数

*****************************************************************************/
VOS_VOID PPP_HDLC_HARD_MntnDefTraceUncompleteInfo
(
    HDLC_DEF_UNCOMPLETED_INFO_STRU     *pstUncompletedInfo
)
{
    HDLC_MNTN_DEF_UNCOMPLETED_INFO_STRU stMntnUncompletedInfo;


    VOS_MemCpy(&stMntnUncompletedInfo.stUncompletedInfo,
               pstUncompletedInfo, sizeof(HDLC_DEF_UNCOMPLETED_INFO_STRU));

    PPP_HDLC_HARD_MntnTraceMsg((HDLC_MNTN_TRACE_HEAD_STRU *)&stMntnUncompletedInfo,
                               ID_HDLC_MNTN_DEF_UNCOMPLETED_INFO,
                               sizeof(HDLC_MNTN_DEF_UNCOMPLETED_INFO_STRU));
    return;
}

/*****************************************************************************
 函 数 名  : PPP_HDLC_HARD_MntnShowFrmReg
 功能描述  : 打印封装寄存器当前数据
 输入参数  : 无
 输出参数  : 无
 返 回 值  : 无
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2013年1月30日
    作    者   : c00191211
    修改内容   : 新生成函数

*****************************************************************************/
VOS_VOID PPP_HDLC_HARD_MntnShowFrmReg(VOS_VOID)
{
    HDLC_MNTN_FRM_REG_CONFIG_STRU           stRegConfig;
    HDLC_MNTN_FRM_REG_CONFIG_STRU          *pstRegConfig = &stRegConfig;


    /* 拷贝全部寄存器内容 */
    pstRegConfig->ulStateSwRst          = PPP_HDLC_READ_32REG(SOC_ARM_HDLC_STATE_SW_RST_ADDR(HDLC_IP_BASE_ADDR));
    pstRegConfig->ulPriorTimeoutCtrl    = PPP_HDLC_READ_32REG(SOC_ARM_HDLC_PRIROR_TIMEOUT_CTRL_ADDR(HDLC_IP_BASE_ADDR));
    pstRegConfig->ulRdErrCurrAddr       = PPP_HDLC_READ_32REG(SOC_ARM_HDLC_RD_ERR_CURR_ADDR(HDLC_IP_BASE_ADDR));
    pstRegConfig->ulWrErrCurrAddr       = PPP_HDLC_READ_32REG(SOC_ARM_HDLC_WR_ERR_CURR_ADDR(HDLC_IP_BASE_ADDR));
    pstRegConfig->ulHdlcFrmEn           = PPP_HDLC_READ_32REG(SOC_ARM_HDLC_FRM_EN_ADDR(HDLC_IP_BASE_ADDR));
    pstRegConfig->ulHdlcFrmRawInt       = PPP_HDLC_READ_32REG(SOC_ARM_HDLC_FRM_RAW_INT_ADDR(HDLC_IP_BASE_ADDR));
    pstRegConfig->ulHdlcFrmIntStatus    = PPP_HDLC_READ_32REG(SOC_ARM_HDLC_FRM_INT_STATUS_ADDR(HDLC_IP_BASE_ADDR));
    pstRegConfig->ulHdlcFrmIntClr       = PPP_HDLC_READ_32REG(SOC_ARM_HDLC_FRM_INT_CLR_ADDR(HDLC_IP_BASE_ADDR));
    pstRegConfig->ulHdlcFrmCfg          = PPP_HDLC_READ_32REG(SOC_ARM_HDLC_FRM_CFG_ADDR(HDLC_IP_BASE_ADDR));
    pstRegConfig->ulHdlcFrmAccm         = PPP_HDLC_READ_32REG(SOC_ARM_HDLC_FRM_ACCM_ADDR(HDLC_IP_BASE_ADDR));
    pstRegConfig->ulHdlcFrmStatus       = PPP_HDLC_READ_32REG(SOC_ARM_HDLC_FRM_STATUS_ADDR(HDLC_IP_BASE_ADDR));
    pstRegConfig->ulFrmInLliAddr        = PPP_HDLC_READ_32REG(SOC_ARM_HDLC_FRM_IN_LLI_ADDR(HDLC_IP_BASE_ADDR));
    pstRegConfig->ulFrmInSublliAddr     = PPP_HDLC_READ_32REG(SOC_ARM_HDLC_FRM_IN_SUBLLI_ADDR(HDLC_IP_BASE_ADDR));
    pstRegConfig->ulFrmInPktLen         = PPP_HDLC_READ_32REG(SOC_ARM_HDLC_FRM_IN_PKT_LEN_ADDR(HDLC_IP_BASE_ADDR));
    pstRegConfig->ulFrmInBlkAddr        = PPP_HDLC_READ_32REG(SOC_ARM_HDLC_FRM_IN_BLK_ADDR(HDLC_IP_BASE_ADDR));
    pstRegConfig->ulFrmInBlkLen         = PPP_HDLC_READ_32REG(SOC_ARM_HDLC_FRM_IN_BLK_LEN_ADDR(HDLC_IP_BASE_ADDR));
    pstRegConfig->ulFrmOutLliAddr       = PPP_HDLC_READ_32REG(SOC_ARM_HDLC_FRM_OUT_LLI_ADDR(HDLC_IP_BASE_ADDR));
    pstRegConfig->ulFrmOutSpaceAddr     = PPP_HDLC_READ_32REG(SOC_ARM_HDLC_FRM_OUT_SPACE_ADDR(HDLC_IP_BASE_ADDR));
    pstRegConfig->ulFrmOutSpaceDep      = PPP_HDLC_READ_32REG(SOC_ARM_HDLC_FRM_OUT_SPACE_DEP_ADDR(HDLC_IP_BASE_ADDR));
    pstRegConfig->ulFrmRptAddr          = PPP_HDLC_READ_32REG(SOC_ARM_HDLC_FRM_RPT_ADDR(HDLC_IP_BASE_ADDR));
    pstRegConfig->ulFrmRptDep           = PPP_HDLC_READ_32REG(SOC_ARM_HDLC_FRM_RPT_DEP_ADDR(HDLC_IP_BASE_ADDR));

    vos_printf("\n================HDLC Hardware ShowFrmReg Begin==========================\n");

    vos_printf("ulStateSwRst                    = 0x%x\n", pstRegConfig->ulStateSwRst);
    vos_printf("ulPriorTimeoutCtrl              = 0x%x\n", pstRegConfig->ulPriorTimeoutCtrl);
    vos_printf("ulRdErrCurrAddr                 = 0x%x\n", pstRegConfig->ulRdErrCurrAddr);
    vos_printf("ulWrErrCurrAddr                 = 0x%x\n", pstRegConfig->ulWrErrCurrAddr);
    vos_printf("ulHdlcFrmEn                     = 0x%x\n", pstRegConfig->ulHdlcFrmEn);
    vos_printf("ulHdlcFrmRawInt                 = 0x%x\n", pstRegConfig->ulHdlcFrmRawInt);
    vos_printf("ulHdlcFrmIntStatus              = 0x%x\n", pstRegConfig->ulHdlcFrmIntStatus);
    vos_printf("ulHdlcFrmIntClr                 = 0x%x\n", pstRegConfig->ulHdlcFrmIntClr);
    vos_printf("ulHdlcFrmCfg                    = 0x%x\n", pstRegConfig->ulHdlcFrmCfg);
    vos_printf("ulHdlcFrmAccm                   = 0x%x\n", pstRegConfig->ulHdlcFrmAccm);
    vos_printf("ulHdlcFrmStatus                 = 0x%x\n", pstRegConfig->ulHdlcFrmStatus);
    vos_printf("ulFrmInLliAddr                  = 0x%x\n", pstRegConfig->ulFrmInLliAddr);
    vos_printf("ulFrmInSublliAddr               = 0x%x\n", pstRegConfig->ulFrmInSublliAddr);
    vos_printf("ulFrmInPktLen                   = 0x%x\n", pstRegConfig->ulFrmInPktLen);
    vos_printf("ulFrmInBlkAddr                  = 0x%x\n", pstRegConfig->ulFrmInBlkAddr);
    vos_printf("ulFrmInBlkLen                   = 0x%x\n", pstRegConfig->ulFrmInBlkLen);
    vos_printf("ulFrmOutLliAddr                 = 0x%x\n", pstRegConfig->ulFrmOutLliAddr);
    vos_printf("ulFrmOutSpaceAddr               = 0x%x\n", pstRegConfig->ulFrmOutSpaceAddr);
    vos_printf("ulFrmOutSpaceDep                = 0x%x\n", pstRegConfig->ulFrmOutSpaceDep);
    vos_printf("ulFrmRptAddr                    = 0x%x\n", pstRegConfig->ulFrmRptAddr);
    vos_printf("ulFrmRptDep                     = 0x%x\n", pstRegConfig->ulFrmRptDep);

    vos_printf("\n================HDLC Hardware ShowFrmReg End==========================\n");

    return;
}

/*****************************************************************************
 函 数 名  : PPP_HDLC_HARD_MntnShowDefReg
 功能描述  : 打印解封装寄存器当前数据
 输入参数  : 无
 输出参数  : 无
 返 回 值  : 无
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2013年1月30日
    作    者   : c00191211
    修改内容   : 新生成函数

*****************************************************************************/
VOS_VOID PPP_HDLC_HARD_MntnShowDefReg(VOS_VOID)
{
    HDLC_MNTN_DEF_REG_CONFIG_STRU           stRegConfig;
    HDLC_MNTN_DEF_REG_CONFIG_STRU          *pstRegConfig = &stRegConfig;


    /* 拷贝全部寄存器内容 */
    pstRegConfig->ulStateSwRst             = PPP_HDLC_READ_32REG(SOC_ARM_HDLC_STATE_SW_RST_ADDR(HDLC_IP_BASE_ADDR));
    pstRegConfig->ulPriorTimeoutCtrl       = PPP_HDLC_READ_32REG(SOC_ARM_HDLC_PRIROR_TIMEOUT_CTRL_ADDR(HDLC_IP_BASE_ADDR));
    pstRegConfig->ulRdErrCurrAddr          = PPP_HDLC_READ_32REG(SOC_ARM_HDLC_RD_ERR_CURR_ADDR(HDLC_IP_BASE_ADDR));
    pstRegConfig->ulWrErrCurrAddr          = PPP_HDLC_READ_32REG(SOC_ARM_HDLC_WR_ERR_CURR_ADDR(HDLC_IP_BASE_ADDR));
    pstRegConfig->ulHdlcDefEn              = PPP_HDLC_READ_32REG(SOC_ARM_HDLC_DEF_EN_ADDR(HDLC_IP_BASE_ADDR));
    pstRegConfig->ulHdlcDefRawInt          = PPP_HDLC_READ_32REG(SOC_ARM_HDLC_DEF_RAW_INT_ADDR(HDLC_IP_BASE_ADDR));
    pstRegConfig->ulHdlcDefIntStatus       = PPP_HDLC_READ_32REG(SOC_ARM_HDLC_DEF_INT_STATUS_ADDR(HDLC_IP_BASE_ADDR));
    pstRegConfig->ulHdlcDefIntClr          = PPP_HDLC_READ_32REG(SOC_ARM_HDLC_DEF_INT_CLR_ADDR(HDLC_IP_BASE_ADDR));
    pstRegConfig->ulHdlcDefCfg             = PPP_HDLC_READ_32REG(SOC_ARM_HDLC_DEF_CFG_ADDR(HDLC_IP_BASE_ADDR));
    pstRegConfig->ulDefUncompletedLen      = PPP_HDLC_READ_32REG(SOC_ARM_HDLC_DEF_UNCOMPLETED_LEN_ADDR(HDLC_IP_BASE_ADDR));
    pstRegConfig->ulDefUncompletedPro      = PPP_HDLC_READ_32REG(SOC_ARM_HDLC_DEF_UNCOMPLETED_PRO_ADDR(HDLC_IP_BASE_ADDR));
    pstRegConfig->ulDefUncompletedAddr     = PPP_HDLC_READ_32REG(SOC_ARM_HDLC_DEF_UNCOMPLETED_ADDR(HDLC_IP_BASE_ADDR));
    pstRegConfig->ulDefUncompleteStAgo     = PPP_HDLC_READ_32REG(SOC_ARM_HDLC_DEF_UNCOMPLETED_ST_AGO_ADDR(HDLC_IP_BASE_ADDR));
    pstRegConfig->ulHdlcDefGoOn            = PPP_HDLC_READ_32REG(SOC_ARM_HDLC_DEF_GO_ON_ADDR(HDLC_IP_BASE_ADDR));
    pstRegConfig->ulHdlcDefStatus          = PPP_HDLC_READ_32REG(SOC_ARM_HDLC_DEF_STATUS_ADDR(HDLC_IP_BASE_ADDR));
    pstRegConfig->ulDefUncompletStNow      = PPP_HDLC_READ_32REG(SOC_ARM_HDLC_DEF_UNCOMPLETED_ST_NOW_ADDR(HDLC_IP_BASE_ADDR));
    pstRegConfig->ulDefInLliAddr           = PPP_HDLC_READ_32REG(SOC_ARM_HDLC_DEF_IN_LLI_ADDR(HDLC_IP_BASE_ADDR));
    pstRegConfig->ulDefInPktAddr           = PPP_HDLC_READ_32REG(SOC_ARM_HDLC_DEF_IN_PKT_ADDR(HDLC_IP_BASE_ADDR));
    pstRegConfig->ulDefInPktLen            = PPP_HDLC_READ_32REG(SOC_ARM_HDLC_DEF_IN_PKT_LEN_ADDR(HDLC_IP_BASE_ADDR));
    pstRegConfig->ulDefInPktLenMax         = PPP_HDLC_READ_32REG(SOC_ARM_HDLC_DEF_IN_PKT_LEN_MAX_ADDR(HDLC_IP_BASE_ADDR));
    pstRegConfig->ulDefOutSpcAddr          = PPP_HDLC_READ_32REG(SOC_ARM_HDLC_DEF_OUT_SPC_ADDR(HDLC_IP_BASE_ADDR));
    pstRegConfig->ulDefOutSpaceDep         = PPP_HDLC_READ_32REG(SOC_ARM_HDLC_DEF_OUT_SPACE_DEP_ADDR(HDLC_IP_BASE_ADDR));
    pstRegConfig->ulDefRptAddr             = PPP_HDLC_READ_32REG(SOC_ARM_HDLC_DEF_RPT_ADDR(HDLC_IP_BASE_ADDR));
    pstRegConfig->ulDefRptDep              = PPP_HDLC_READ_32REG(SOC_ARM_HDLC_DEF_RPT_DEP_ADDR(HDLC_IP_BASE_ADDR));
    pstRegConfig->ulHdlcDefErrInfor0       = PPP_HDLC_READ_32REG(SOC_ARM_HDLC_DEF_ERR_INFO_0_ADDR(HDLC_IP_BASE_ADDR));
    pstRegConfig->ulHdlcDefErrInfor1       = PPP_HDLC_READ_32REG(SOC_ARM_HDLC_DEF_ERR_INFO_1_ADDR(HDLC_IP_BASE_ADDR));
    pstRegConfig->ulHdlcDefErrInfor2       = PPP_HDLC_READ_32REG(SOC_ARM_HDLC_DEF_ERR_INFO_2_ADDR(HDLC_IP_BASE_ADDR));
    pstRegConfig->ulHdlcDefErrInfor3       = PPP_HDLC_READ_32REG(SOC_ARM_HDLC_DEF_ERR_INFO_3_ADDR(HDLC_IP_BASE_ADDR));
    pstRegConfig->ulDefInfoFr1CntAgo       = PPP_HDLC_READ_32REG(SOC_ARM_HDLC_DEF_INFO_FRL_CNT_AGO_ADDR(HDLC_IP_BASE_ADDR));
    pstRegConfig->ulDefInfoFr1CntNow       = PPP_HDLC_READ_32REG(SOC_ARM_HDLC_DEF_INFO_FRL_CNT_NOW_ADDR(HDLC_IP_BASE_ADDR));

    vos_printf("\n================HDLC Hardware ShowDefReg Begin==========================\n");

    vos_printf("ulStateSwRst             = 0x%x\n", pstRegConfig->ulStateSwRst);
    vos_printf("ulPriorTimeoutCtrl       = 0x%x\n", pstRegConfig->ulPriorTimeoutCtrl);
    vos_printf("ulRdErrCurrAddr          = 0x%x\n", pstRegConfig->ulRdErrCurrAddr);
    vos_printf("ulWrErrCurrAddr          = 0x%x\n", pstRegConfig->ulWrErrCurrAddr);
    vos_printf("ulHdlcDefEn              = 0x%x\n", pstRegConfig->ulHdlcDefEn);
    vos_printf("ulHdlcDefRawInt          = 0x%x\n", pstRegConfig->ulHdlcDefRawInt);
    vos_printf("ulHdlcDefIntStatus       = 0x%x\n", pstRegConfig->ulHdlcDefIntStatus);
    vos_printf("ulHdlcDefIntClr          = 0x%x\n", pstRegConfig->ulHdlcDefIntClr);
    vos_printf("ulHdlcDefCfg             = 0x%x\n", pstRegConfig->ulHdlcDefCfg);
    vos_printf("ulDefUncompletedLen      = 0x%x\n", pstRegConfig->ulDefUncompletedLen);
    vos_printf("ulDefUncompletedPro      = 0x%x\n", pstRegConfig->ulDefUncompletedPro);
    vos_printf("ulDefUncompletedAddr     = 0x%x\n", pstRegConfig->ulDefUncompletedAddr);
    vos_printf("ulDefUncompleteStAgo     = 0x%x\n", pstRegConfig->ulDefUncompleteStAgo);
    vos_printf("ulHdlcDefGoOn            = 0x%x\n", pstRegConfig->ulHdlcDefGoOn);
    vos_printf("ulHdlcDefStatus          = 0x%x\n", pstRegConfig->ulHdlcDefStatus);
    vos_printf("ulDefUncompletStNow      = 0x%x\n", pstRegConfig->ulDefUncompletStNow);
    vos_printf("ulDefInLliAddr           = 0x%x\n", pstRegConfig->ulDefInLliAddr);
    vos_printf("ulDefInPktAddr           = 0x%x\n", pstRegConfig->ulDefInPktAddr);
    vos_printf("ulDefInPktLen            = 0x%x\n", pstRegConfig->ulDefInPktLen);
    vos_printf("ulDefInPktLenMax         = 0x%x\n", pstRegConfig->ulDefInPktLenMax);
    vos_printf("ulDefOutSpcAddr          = 0x%x\n", pstRegConfig->ulDefOutSpcAddr);
    vos_printf("ulDefOutSpaceDep         = 0x%x\n", pstRegConfig->ulDefOutSpaceDep);
    vos_printf("ulDefRptAddr             = 0x%x\n", pstRegConfig->ulDefRptAddr);
    vos_printf("ulDefRptDep              = 0x%x\n", pstRegConfig->ulDefRptDep);
    vos_printf("ulHdlcDefErrInfor0       = 0x%x\n", pstRegConfig->ulHdlcDefErrInfor0);
    vos_printf("ulHdlcDefErrInfor1       = 0x%x\n", pstRegConfig->ulHdlcDefErrInfor1);
    vos_printf("ulHdlcDefErrInfor2       = 0x%x\n", pstRegConfig->ulHdlcDefErrInfor2);
    vos_printf("ulHdlcDefErrInfor3       = 0x%x\n", pstRegConfig->ulHdlcDefErrInfor3);
    vos_printf("ulDefInfoFr1CntAgo       = 0x%x\n", pstRegConfig->ulDefInfoFr1CntAgo);
    vos_printf("ulDefInfoFr1CntNow       = 0x%x\n", pstRegConfig->ulDefInfoFr1CntNow);

    vos_printf("\n================HDLC Hardware ShowDefReg End==========================\n");

}

/*****************************************************************************
 函 数 名  : PPP_HDLC_HARD_FrmProcException
 功能描述  : 异常处理
 输入参数  : ulStatus           -   异常状态
             ulEnableInterrupt  - 中断方式还是轮询方式
 输出参数  : 无
 返 回 值  : 无
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2012年4月20日
    作    者   : l00164359
    修改内容   : 新生成函数

*****************************************************************************/
/*lint -e438*/
/*lint -e550*/
VOS_VOID PPP_HDLC_HARD_FrmProcException
(
    VOS_UINT32          ulStatus,
    VOS_UINT32          ulEnableInterrupt
)
{
    VOS_UINT32                          ulRawInt;


    if( VOS_TRUE == ulEnableInterrupt )
    {
        /* 由于在中断服务程序中进行了清中断操作，故此处取保存在g_stHdlcRegSaveInfo中的原始中断寄存器值 */
        ulRawInt                        =   g_stHdlcRegSaveInfo.ulHdlcFrmRawInt;
        g_PppHdlcHardStat.usFrmExpInfo |=   (1 << HDLC_INTERRUPT_IND_BITPOS);
    }
    else
    {
        ulRawInt  =   PPP_HDLC_READ_32REG(SOC_ARM_HDLC_FRM_RAW_INT_ADDR(HDLC_IP_BASE_ADDR));
    }

    PPP_HDLC_ERROR_LOG2("PPP_HDLC_HARD_FrmProcException, ERROR, Exception ocurr status 0x%x RAW_INT 0x%x\r\n", ulStatus, ulRawInt);
    PPP_HDLC_HARD_MntnShowFrmReg();
    PPP_HDLC_HARD_MntnShowDefReg();

    g_PppHdlcHardStat.usFrmExpInfo |=   (1 << HDLC_EXCEPTION_IND_BITPOS);

    /* 复位前先Delay 1s保证可维可测正常输出 */
    VOS_TaskDelay(1000);

    /* 如果HDLC出现异常，则单板异常重启 */
    mdrv_om_system_error(HDLC_FRM_SYSTEM_ERROR_ID, __LINE__, (VOS_INT)g_PppHdlcHardStat.usFrmExpInfo,
                         (VOS_CHAR *)&g_stHdlcRegSaveInfo,
                         sizeof(HDLC_REG_SAVE_INFO_STRU));

    return;
}
/*lint +e438*/
/*lint +e550*/

/*****************************************************************************
 函 数 名  : PPP_HDLC_HARD_MntnFrmTraceRegConfig
 功能描述  : 勾取寄存器配置数据
 输入参数  : ulEnable   -   封装解封装使能前还是使能后，VOS_TRUE: 使能后,VOS_FALSE: 使能前
             ulValue    -   使能寄存器配置的值
             ulEnableInterrupt - 中断方式还是轮询方式，仅在使能后勾取寄存器时生效
 输出参数  : 无
 返 回 值  : 无
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2012年4月20日
    作    者   : l00164359
    修改内容   : 新生成函数

*****************************************************************************/
VOS_VOID PPP_HDLC_HARD_MntnFrmTraceRegConfig
(
    VOS_UINT32      ulEnable,
    VOS_UINT32      ulValue,
    VOS_UINT32      ulEnableInterrupt
)
{
    HDLC_MNTN_FRM_REG_CONFIG_STRU           stRegConfig;
    HDLC_MNTN_FRM_REG_CONFIG_STRU          *pstRegConfig = &stRegConfig;
    VOS_UINT32                              ulDataLen;

    if ((g_stHdlcConfigInfo.ulHdlcMntnTraceCfg & PPP_HDLC_MNTN_TRACE_REG) != 0)
    {
        ulDataLen    = sizeof(HDLC_MNTN_FRM_REG_CONFIG_STRU);

        /* 拷贝全部寄存器内容 */
        pstRegConfig->ulStateSwRst          = PPP_HDLC_READ_32REG(SOC_ARM_HDLC_STATE_SW_RST_ADDR(HDLC_IP_BASE_ADDR));
        pstRegConfig->ulPriorTimeoutCtrl    = PPP_HDLC_READ_32REG(SOC_ARM_HDLC_PRIROR_TIMEOUT_CTRL_ADDR(HDLC_IP_BASE_ADDR));
        pstRegConfig->ulRdErrCurrAddr       = PPP_HDLC_READ_32REG(SOC_ARM_HDLC_RD_ERR_CURR_ADDR(HDLC_IP_BASE_ADDR));
        pstRegConfig->ulWrErrCurrAddr       = PPP_HDLC_READ_32REG(SOC_ARM_HDLC_WR_ERR_CURR_ADDR(HDLC_IP_BASE_ADDR));
        pstRegConfig->ulHdlcFrmEn           = PPP_HDLC_READ_32REG(SOC_ARM_HDLC_FRM_EN_ADDR(HDLC_IP_BASE_ADDR));
        pstRegConfig->ulHdlcFrmRawInt       = PPP_HDLC_READ_32REG(SOC_ARM_HDLC_FRM_RAW_INT_ADDR(HDLC_IP_BASE_ADDR));
        pstRegConfig->ulHdlcFrmIntStatus    = PPP_HDLC_READ_32REG(SOC_ARM_HDLC_FRM_INT_STATUS_ADDR(HDLC_IP_BASE_ADDR));
        pstRegConfig->ulHdlcFrmIntClr       = PPP_HDLC_READ_32REG(SOC_ARM_HDLC_FRM_INT_CLR_ADDR(HDLC_IP_BASE_ADDR));
        pstRegConfig->ulHdlcFrmCfg          = PPP_HDLC_READ_32REG(SOC_ARM_HDLC_FRM_CFG_ADDR(HDLC_IP_BASE_ADDR));
        pstRegConfig->ulHdlcFrmAccm         = PPP_HDLC_READ_32REG(SOC_ARM_HDLC_FRM_ACCM_ADDR(HDLC_IP_BASE_ADDR));
        pstRegConfig->ulHdlcFrmStatus       = PPP_HDLC_READ_32REG(SOC_ARM_HDLC_FRM_STATUS_ADDR(HDLC_IP_BASE_ADDR));
        pstRegConfig->ulFrmInLliAddr        = PPP_HDLC_READ_32REG(SOC_ARM_HDLC_FRM_IN_LLI_ADDR(HDLC_IP_BASE_ADDR));
        pstRegConfig->ulFrmInSublliAddr     = PPP_HDLC_READ_32REG(SOC_ARM_HDLC_FRM_IN_SUBLLI_ADDR(HDLC_IP_BASE_ADDR));
        pstRegConfig->ulFrmInPktLen         = PPP_HDLC_READ_32REG(SOC_ARM_HDLC_FRM_IN_PKT_LEN_ADDR(HDLC_IP_BASE_ADDR));
        pstRegConfig->ulFrmInBlkAddr        = PPP_HDLC_READ_32REG(SOC_ARM_HDLC_FRM_IN_BLK_ADDR(HDLC_IP_BASE_ADDR));
        pstRegConfig->ulFrmInBlkLen         = PPP_HDLC_READ_32REG(SOC_ARM_HDLC_FRM_IN_BLK_LEN_ADDR(HDLC_IP_BASE_ADDR));
        pstRegConfig->ulFrmOutLliAddr       = PPP_HDLC_READ_32REG(SOC_ARM_HDLC_FRM_OUT_LLI_ADDR(HDLC_IP_BASE_ADDR));
        pstRegConfig->ulFrmOutSpaceAddr     = PPP_HDLC_READ_32REG(SOC_ARM_HDLC_FRM_OUT_SPACE_ADDR(HDLC_IP_BASE_ADDR));
        pstRegConfig->ulFrmOutSpaceDep      = PPP_HDLC_READ_32REG(SOC_ARM_HDLC_FRM_OUT_SPACE_DEP_ADDR(HDLC_IP_BASE_ADDR));
        pstRegConfig->ulFrmRptAddr          = PPP_HDLC_READ_32REG(SOC_ARM_HDLC_FRM_RPT_ADDR(HDLC_IP_BASE_ADDR));
        pstRegConfig->ulFrmRptDep           = PPP_HDLC_READ_32REG(SOC_ARM_HDLC_FRM_RPT_DEP_ADDR(HDLC_IP_BASE_ADDR));

        /* 使能前勾包，使能寄存器还没有配置，因为配置之后HDLC会开始工作，会改变其他寄存器的值 */
        if( VOS_FALSE == ulEnable )
        {
            pstRegConfig->ulHdlcFrmEn    = ulValue;
            PPP_HDLC_HARD_MntnTraceMsg((HDLC_MNTN_TRACE_HEAD_STRU *)pstRegConfig,
                                       ID_HDLC_MNTN_FRM_REG_BEFORE_EN, ulDataLen);
        }
        else
        {
            /* 使能后勾包时，如果采用中断方式，则RawInt和Status取g_stHdlcRegSaveInfo保存的值 */
            if( VOS_TRUE == ulEnableInterrupt )
            {
                pstRegConfig->ulHdlcFrmRawInt   = g_stHdlcRegSaveInfo.ulHdlcFrmRawInt;
                pstRegConfig->ulHdlcFrmStatus   = g_stHdlcRegSaveInfo.ulHdlcFrmStatus;
            }
            PPP_HDLC_HARD_MntnTraceMsg((HDLC_MNTN_TRACE_HEAD_STRU *)pstRegConfig,
                                       ID_HDLC_MNTN_FRM_REG_AFTER_EN, ulDataLen);
        }
    }

    return;
}

/*****************************************************************************
 函 数 名  : PPP_HDLC_HARD_FrmCfgBufReg
 功能描述  : 配置使能寄存器，并上报使能前寄存器可维可测
 输入参数  : ulTotalLen --待封装数据包的总长度
 输出参数  :
 返 回 值  : VOS_TRUE   - 采用中断模式
             VOS_FALSE  - 采用轮询模式
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2012年4月20日
    作    者   : c00191211
    修改内容   : 新生成函数

*****************************************************************************/
VOS_UINT32 PPP_HDLC_HARD_FrmCfgEnReg(VOS_UINT32   ulTotalLen)
{
    /*
    1.hdlc_frm_en   (0x10)
      31   25 24  23 18 17  16  15  14  13  12  11  10   9   8  7    1  0
    |--------|---|-----|---|---|---|---|---|---|---|---|---|---|------|---|
    |   Rsv  |en | Rsv |en |en |en |en |en |en |en |en |en |en |  Rsv |en |

    Reserved            [31:25] 7'b0    h/s R/W  保留位。读时返回0。写时无影响。
    frm_over_int_en     [24]    1'b0    h/s R/W  一套链表封装结束中断使能;0：中断禁止;1：中断使能;
    Reserved            [23:18] 6'b0    h/s R/W  保留位。读时返回0。写时无影响。
    frm_rpt_dep_err_en  [17]    1'b0    h/s R/W  封装外部正确帧长度上报空间不足中断使能;0：中断禁止;1：中断使能;
    frm_out_spc_err_en  [16]    1'b0    h/s R/W  封装外部输出存储空间不足中断使能;0：中断禁止;1：中断使能
    frm_rpt_prm_err_en  [15]    1'b0    h/s R/W  封装上报空间相关参数错误中断使能;0：中断禁止;1：中断使能
    frm_out_prm_err_en  [14]    1'b0    h/s R/W  封装输出链表相关参数错误中断使能;0：中断禁止;1：中断使能
    frm_in_prm_err_en   [13]    1'b0    h/s R/W  封装输入链表相关参数错误中断使能;0：中断禁止;1：中断使能
    frm_cfg_err_en      [12]    1'b0    h/s R/W  封装协议及其压缩指示配置错误中断使能;0：中断禁止;1：中断使能
    frm_wr_timeout_en   [11]    1'b0    h/s R/W  封装时AXI总线写请求timeout中断使能;0：中断禁止;1：中断使能
    frm_rd_timeout_en   [10]    1'b0    h/s R/W  封装时AXI总线读请求timeout中断使能;0：中断禁止;1：中断使能
    frm_wr_err_en       [9]     1'b0    h/s R/W  封装时AXI总线写操作错误中断使能;0：中断禁止;1：中断使能
    frm_rd_err_en       [8]     1'b0    h/s R/W  封装时AXI总线读操作错误中断使能;0：中断禁止;1：中断使能
    Reserved            [7:1]   7'b0    h/s R/W  保留位。读时返回0。写时无影响。
    frm_en              [0]     1'b0    h/s R/W  一套链表封装使能，软件向frm_en写入1'b1启动封装工作;一套链表封装完成后，由硬件自动对frm_en清零；
                                                 封装过程出错时，硬件也会对frm_en自动清零，使内部状态机返回IDLE状态；
                                                 写时设置一套链表封装使能;0：不使能封装处理;1：使能封装处理;
                                                 读时返回一套链表封装处理状态;0：没在进行封装处理;1：正在进行封装处理。
    */

    VOS_UINT32          ulEnableInterrupt;
    VOS_UINT32          ulValue;
    const VOS_UINT32    ulInterruptValue    = 0x0103FF01;   /* 使用中断方式时配置使能寄存器的值 */
    const VOS_UINT32    ulPollValue         = 0x01;         /* 使用轮询方式时配置使能寄存器的值 */


    /* 判断待封装数据的总长度，若大于门限则使用中断方式，否则使用轮询方式 */
    if( ulTotalLen > HDLC_FRM_INTERRUPT_LIMIT )
    {
        /* 配置封装相关使能寄存器hdlc_frm_en的[31:0]位为0x0103FF01 */
        ulValue             = ulInterruptValue;
        ulEnableInterrupt   = VOS_TRUE;

        g_PppHdlcHardStat.ulFrmWaitIntCnt++;
    }
    else
    {
        /* 配置封装相关使能寄存器hdlc_frm_en的[31:0]位为0x01 */
        ulValue             = ulPollValue;
        ulEnableInterrupt   = VOS_FALSE;

        g_PppHdlcHardStat.ulFrmWaitQueryCnt++;
    }

    /* 使能前清除上次封装、解封装的原始中断 */
    PPP_HDLC_WRITE_32REG(SOC_ARM_HDLC_DEF_INT_CLR_ADDR(HDLC_IP_BASE_ADDR), 0xFFFFFFFFU);
    PPP_HDLC_WRITE_32REG(SOC_ARM_HDLC_FRM_INT_CLR_ADDR(HDLC_IP_BASE_ADDR), 0xFFFFFFFFU);

    /* 上报寄存器可维可测 */
    PPP_HDLC_HARD_MntnFrmTraceRegConfig(VOS_FALSE, ulValue, ulEnableInterrupt);

    /* 使能硬件之前先强制ARM顺序执行结束前面的指针 */
    TTF_FORCE_ARM_INSTUCTION();

    PPP_HDLC_WRITE_32REG(SOC_ARM_HDLC_FRM_EN_ADDR(HDLC_IP_BASE_ADDR), ulValue);

    /* PC上使用HDLC模拟器 */
#if (VOS_OS_VER == VOS_WIN32)
    VHW_HDLC_Task();
#endif

    return ulEnableInterrupt;
}

/*****************************************************************************
 函 数 名  : PPP_HDLC_HARD_FrmStartTimer
 功能描述  : 申请封装目的空间失败开启定时器
 输入参数  : pstBuildPara   -   构造链表所需的参数
 输出参数  : 无
 返 回 值  : 无
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2012年4月20日
    作    者   : c00191211
    修改内容   : 新生成函数

*****************************************************************************/
VOS_VOID PPP_HDLC_HARD_FrmStartTimer
(
    HDLC_PARA_LINK_BUILD_PARA_STRU      *pstBuildPara
)
{
    if( VOS_NULL_PTR != g_stHdlcConfigInfo.stHdlcFrmTimerHandle )
    {
        return;
    }

    if (VOS_OK != VOS_StartRelTimer(&g_stHdlcConfigInfo.stHdlcFrmTimerHandle, PS_PID_PPP_HDLC,
                     HDLC_FRM_TIME_INTERVAL,
                     pstBuildPara->usPppId,
                     HDLC_FRM_OUTPUT_SPACE_ALLOC_FAIL,
                     VOS_RELTIMER_NOLOOP, VOS_TIMER_PRECISION_0))
    {
        PPP_HDLC_WARNING_LOG("PPP_HDLC_HARD_FrmStartTimer, Warning, start reltimer error\r\n");
    }

    return;
}

/*****************************************************************************
 函 数 名  : PPP_HDLC_HARD_DefProcException
 功能描述  : 异常处理
 输入参数  : ulStatus           -   异常状态
             ulEnableInterrupt  - 中断方式还是轮询方式
 输出参数  : 无
 返 回 值  : 无
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2012年4月10日
    作    者   : l00164359
    修改内容   : 新生成函数

*****************************************************************************/
/*lint -e438*/
/*lint -e550*/
VOS_VOID PPP_HDLC_HARD_DefProcException
(
    VOS_UINT32          ulStatus,
    VOS_UINT32          ulEnableInterrupt
)
{
    VOS_UINT32                          ulRawInt;


    if( VOS_TRUE == ulEnableInterrupt )
    {
        /* 由于在中断服务程序中进行了清中断操作，故此处取保存在g_stHdlcRegSaveInfo中的原始中断寄存器值 */
        ulRawInt                        =   g_stHdlcRegSaveInfo.ulHdlcDefRawInt;
        g_PppHdlcHardStat.usDefExpInfo |=   (1 << HDLC_INTERRUPT_IND_BITPOS);
    }
    else
    {
        ulRawInt  =   PPP_HDLC_READ_32REG(SOC_ARM_HDLC_DEF_RAW_INT_ADDR(HDLC_IP_BASE_ADDR));
    }

    PPP_HDLC_ERROR_LOG2("PPP_HDLC_HARD_DefProcException, ERROR, Exception ocurr status 0x%x RAW_INT 0x%x\r\n", ulStatus, ulRawInt);
    PPP_HDLC_HARD_MntnShowFrmReg();
    PPP_HDLC_HARD_MntnShowDefReg();

    g_PppHdlcHardStat.usDefExpInfo |=   (1 << HDLC_EXCEPTION_IND_BITPOS);

    /* 如果HDLC出现异常，则单板异常重启 */
    mdrv_om_system_error(HDLC_DEF_SYSTEM_ERROR_ID, __LINE__, (VOS_INT)g_PppHdlcHardStat.usDefExpInfo,
                         (VOS_CHAR *)&g_stHdlcRegSaveInfo,
                         sizeof(HDLC_REG_SAVE_INFO_STRU));

    return;
}
/*lint +e438*/
/*lint +e550*/
/*****************************************************************************
 函 数 名  : PPP_HDLC_HARD_CommWaitSem
 功能描述  : 等待封装解封装暂停或完成
 输入参数  : ulHdlcMasterSem  -
 输出参数  :
 返 回 值  : 无
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2012年4月10日
    作    者   : l00164359
    修改内容   : 新生成函数

*****************************************************************************/
VOS_UINT32 PPP_HDLC_HARD_CommWaitSem
(
    VOS_UINT32          ulHdlcMasterSem,
    VOS_UINT32          ulSemTimeoutLen
)
{
    VOS_UINT32                          ulResult;

    /* 等待封装或解封装完成 */
    ulResult = VOS_SmP(ulHdlcMasterSem, ulSemTimeoutLen);

    if (VOS_OK != ulResult)
    {
        PPP_HDLC_WARNING_LOG2("PPP_HDLC_HARD_CommWaitSem, WARNING, VOS_SmP ulHdlcMasterSem 0x%x failed! ErrorNo = 0x%x\r\n",
                      ulHdlcMasterSem, ulResult);

        g_PppHdlcHardStat.usDefExpInfo |=   (1 << HDLC_SEM_TIMEOUT_IND_BITPOS);
        g_PppHdlcHardStat.usFrmExpInfo |=   (1 << HDLC_SEM_TIMEOUT_IND_BITPOS);

        return VOS_ERR;
    }

    return VOS_OK;
}

/*****************************************************************************
 函 数 名  : PPP_HDLC_HARD_DefIsr
 功能描述  : HDLC解封装中断完成通知服务程序
 输入参数  : 无
 输出参数  : 无
 返 回 值  :
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2012年4月10日
    作    者   : l00164359
    修改内容   : 新生成函数

*****************************************************************************/
VOS_UINT32 PPP_HDLC_HARD_DefIsr(unsigned int ulPara)
{
    g_stHdlcRegSaveInfo.ulHdlcDefRawInt = PPP_HDLC_READ_32REG(SOC_ARM_HDLC_DEF_RAW_INT_ADDR(HDLC_IP_BASE_ADDR));
    g_stHdlcRegSaveInfo.ulHdlcDefStatus = PPP_HDLC_READ_32REG(SOC_ARM_HDLC_DEF_STATUS_ADDR(HDLC_IP_BASE_ADDR));

    /* 收到一次中断后清除原始中断 */
    PPP_HDLC_WRITE_32REG(SOC_ARM_HDLC_DEF_INT_CLR_ADDR(HDLC_IP_BASE_ADDR), 0xFFFFFFFFU);

    /* 释放封装完成信号量 */
    VOS_SmV(g_stHdlcConfigInfo.ulHdlcDefMasterSem);

    g_PppHdlcHardStat.ulDefIsrCnt++;


    /* drv提供的接口不关心返回值 */
    return 1; /* IRQ_HANDLED; */
}

/*****************************************************************************
 函 数 名  : PPP_HDLC_HARD_FrmIsr
 功能描述  : HDLC封装中断完成通知服务程序
 输入参数  : 无
 输出参数  : 无
 返 回 值  :
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2012年4月10日
    作    者   : l00164359
    修改内容   : 新生成函数

*****************************************************************************/
VOS_UINT32 PPP_HDLC_HARD_FrmIsr(unsigned int ulPara)
{
    g_stHdlcRegSaveInfo.ulHdlcFrmRawInt = PPP_HDLC_READ_32REG(SOC_ARM_HDLC_FRM_RAW_INT_ADDR(HDLC_IP_BASE_ADDR));
    g_stHdlcRegSaveInfo.ulHdlcFrmStatus = PPP_HDLC_READ_32REG(SOC_ARM_HDLC_FRM_STATUS_ADDR(HDLC_IP_BASE_ADDR));

    /* 收到一次中断后清除原始中断 */
    PPP_HDLC_WRITE_32REG(SOC_ARM_HDLC_FRM_INT_CLR_ADDR(HDLC_IP_BASE_ADDR), 0xFFFFFFFFU);

    /* 释放封装完成信号量 */
    VOS_SmV(g_stHdlcConfigInfo.ulHdlcFrmMasterSem);

    g_PppHdlcHardStat.ulFrmIsrCnt++;

    /* drv提供的接口不关心返回值 */
    return 1; /* IRQ_HANDLED; */
}

/*****************************************************************************
 函 数 名  : PPP_HDLC_HARD_DefWaitStatusChange
 功能描述  : 轮询状态寄存器
 输入参数  : 无
 输出参数  :
 返 回 值  : 无
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2012年4月10日
    作    者   : l00164359
    修改内容   : 新生成函数

*****************************************************************************/
VOS_UINT32 PPP_HDLC_HARD_DefWaitStatusChange(VOS_VOID)
{
    /*
    hdlc_def_status  (0x88)
      31 30   24 23   8 7 6  5   4   3   2  1  0
    |---|-------|------|---|---|---|---|---|----|
    |Rsv|  Type |  Num |Rsv|Idx|Ful|Ful|Now|Stat|
    Reserved             [31]    1'b0    h/s R/W  保留位。读时返回0。写时无影响。
    def_err_type         [30:24] 7'b0    h/s RO   有帧上报时，错误帧类型，对应的bit位为1即表明发生该类型错误：
                                                  bit 30：错误类型6，转义字符0x7D后紧接一个Flag域；
                                                  bit 29：错误类型5，当AC域无压缩时，Address域值非0xFF；
                                                  bit 28：错误类型4，当AC域无压缩时，Control域值非0x03；
                                                  bit 27：错误类型3，当P域需剥离时，收到非法的Protocol域值；
                                                  bit 26：错误类型2，解封装后帧字节数小于4bites；
                                                  bit 25：错误类型1，解封装后帧字节数大于1502bytes（PPP帧的Information域不超过1500Bytes，加上协议域不超过1502Bytes）；
                                                  bit 24：错误类型0， CRC校验错误。
    def_valid_num        [23:8]  16'b0   h/s RO   有帧上报时，有效帧数目；（不包括最后一个可能的非完整帧）
    Reserved             [7:6]   2'b0    h/s R/W  保留位。读时返回0。写时无影响。
    def_error_index      [5]     1'b0    h/s RO   解封装发生错误指示
    def_rpt_ful          [4]     1'b0    h/s RO   解封装外部正确帧信息上报空间存满暂停指示
    def_out_spc_ful      [3]     1'b0    h/s RO   解封装外部输出存储空间存满暂停指示
    def_uncompleted_now  [2]     1'b0    h/s RO   用于指示当前链表是否有解出非完整帧，为了支持多个PPP/IP拨号而增加的配置：0，没有；1，有
    def_all_pkt_pro_stat [1:0]   2'b0    h/s RO   一套输入链表处理状态：00：未完成一套输入链表处理；01：未完成一套输入链表处理，已解出LCP帧，硬件处于暂停状态；
                                                  10：完成一套输入链表处理，但无帧上报；11: 完成一套输入链表处理，且有帧上报；
    */
    VOS_UINT32              ulRsltWaitNum;           /* 防止硬件异常的保护变量 */
    volatile VOS_UINT32     ulStatus;                /* 解封装状态 */

   /* 查询hdlc_frm_status (0x28)的第[0]位和第[1]位，任何一个为1或者超时则返回 */

    ulRsltWaitNum = 0UL;

    while (ulRsltWaitNum < HDLC_DEF_MAX_WAIT_RESULT_NUM)
    {
        /* 查询状态寄存器hdlc_def_status (0x88)的0-1和3-5位，任何一位变为1表示解封装模块暂停或停止 */
        ulStatus  =   PPP_HDLC_READ_32REG(SOC_ARM_HDLC_DEF_STATUS_ADDR(HDLC_IP_BASE_ADDR));

        if (HDLC_DEF_STATUS_DOING != (ulStatus & HDLC_DEF_STATUS_MASK))
        {
            break;
        }

        ulRsltWaitNum++;
    }

    if ( HDLC_DEF_MAX_WAIT_RESULT_NUM <= ulRsltWaitNum )
    {
        PPP_HDLC_WARNING_LOG2("PPP_HDLC_HARD_DefWaitStatusChange, WARNING, wait hdlc_def_status timeout %d status 0x%x!\r\n",
                      ulRsltWaitNum, ulStatus);

        g_PppHdlcHardStat.usDefExpInfo |=   (1 << HDLC_WAIT_STATUS_TIMEOUT_IND_BITPOS);

        return VOS_ERR;
    }

    g_PppHdlcHardStat.ulDefMaxQueryCnt = TTF_MAX(g_PppHdlcHardStat.ulDefMaxQueryCnt, ulRsltWaitNum);

    return VOS_OK;
}

/*****************************************************************************
 函 数 名  : PPP_HDLC_HARD_FrmWaitStatusChange
 功能描述  : 轮询状态寄存器
 输入参数  : 无
 输出参数  :
 返 回 值  : 无
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2012年4月10日
    作    者   : l00164359
    修改内容   : 新生成函数

*****************************************************************************/
VOS_UINT32 PPP_HDLC_HARD_FrmWaitStatusChange(VOS_VOID)
{
    VOS_UINT32              ulFrmRsltWaitNum;           /* 防止硬件异常的保护变量 */
    volatile VOS_UINT32     ulFrmStatus;                /* 封装状态 */


   /* 查询hdlc_frm_status (0x28)的第[0]位和第[1]位，任何一个为1或者超时则返回 */
    ulFrmRsltWaitNum = 0UL;

    while (ulFrmRsltWaitNum < HDLC_FRM_MAX_WAIT_RESULT_NUM)
    {
        /* 读取 hdlc_frm_status的[0][1]位 */
        ulFrmStatus  =   PPP_HDLC_READ_32REG(SOC_ARM_HDLC_FRM_STATUS_ADDR(HDLC_IP_BASE_ADDR));

        if (HDLC_FRM_ALL_PKT_DOING != (ulFrmStatus & HDLC_FRM_STATUS_MASK))
        {
            break;
        }

        ulFrmRsltWaitNum++;
    }

    if ( HDLC_FRM_MAX_WAIT_RESULT_NUM <= ulFrmRsltWaitNum )
    {
        PPP_HDLC_WARNING_LOG2("PPP_HDLC_HARD_FrmWaitStatusChange, WARNING, wait hdlc_frm_status timeout %d status 0x%x!\r\n",
                      ulFrmRsltWaitNum, ulFrmStatus);

        g_PppHdlcHardStat.usFrmExpInfo |=   (1 << HDLC_WAIT_STATUS_TIMEOUT_IND_BITPOS);

        return VOS_ERR;
    }

    g_PppHdlcHardStat.ulFrmMaxQueryCnt = TTF_MAX(g_PppHdlcHardStat.ulFrmMaxQueryCnt, ulFrmRsltWaitNum);

    return VOS_OK;
}

/*****************************************************************************
 函 数 名  : PPP_HDLC_HARD_FrmWaitResult
 功能描述  : 等待封装暂停或完成
 输入参数  : ulEnableInterrupt  -   中断是否使能
 输出参数  : 无
 返 回 值  : 封装状态
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2012年4月20日
    作    者   : c00191211
    修改内容   : 新生成函数

*****************************************************************************/
VOS_UINT32 PPP_HDLC_HARD_FrmWaitResult
(
    VOS_UINT32          ulEnableInterrupt
)
{
    VOS_UINT32              ulFrmStatus;        /* 封装状态 */
    VOS_UINT32              ulResult;


    if (VOS_TRUE == ulEnableInterrupt)
    {
        /* 等待中断得到出错或完成状态 */
        ulResult = PPP_HDLC_HARD_CommWaitSem(g_stHdlcConfigInfo.ulHdlcFrmMasterSem, HDLC_FRM_MASTER_INT_TIMER_LEN);

        /* 由于在中断服务程序中进行了清中断操作，而Status指示是否出错的bit由原始中断寄存器
           决定，故此处取保存在g_stHdlcRegSaveInfo中的状态值 */
        ulFrmStatus = g_stHdlcRegSaveInfo.ulHdlcFrmStatus;
    }
    else
    {
        /* 轮询得到出错或完成 */
        ulResult = PPP_HDLC_HARD_FrmWaitStatusChange();

        /* 查询hdlc_frm_status (0x28)获取封装状态并将其返回 */
        ulFrmStatus  =  PPP_HDLC_READ_32REG(SOC_ARM_HDLC_FRM_STATUS_ADDR(HDLC_IP_BASE_ADDR));
    }

    /* 上报寄存器可维可测 */
    PPP_HDLC_HARD_MntnFrmTraceRegConfig(VOS_TRUE, 0, ulEnableInterrupt);

    /* 等不到说明HDLC还在工作 */
    if (VOS_OK != ulResult)
    {
        return HDLC_FRM_ALL_PKT_DOING;
    }

    ulFrmStatus &=  HDLC_FRM_STATUS_MASK;

    return ulFrmStatus;
}

/*****************************************************************************
 函 数 名  : PPP_HDLC_HARD_DefWaitResult
 功能描述  : 等待解封装暂停或完成
 输入参数  : ulEnableInterrupt  -   中断是否使能
 输出参数  : 解封装状态
 返 回 值  : 无
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2012年4月10日
    作    者   : l00164359
    修改内容   : 新生成函数

*****************************************************************************/
VOS_UINT32 PPP_HDLC_HARD_DefWaitResult
(
    VOS_UINT32          ulEnableInterrupt
)
{
    VOS_UINT32                          ulStatus;                /* 解封装状态 */
    VOS_UINT32                          ulResult;


    if (VOS_TRUE == ulEnableInterrupt)
    {
        /* 等待中断得到暂停或完成状态 */
        ulResult = PPP_HDLC_HARD_CommWaitSem(g_stHdlcConfigInfo.ulHdlcDefMasterSem, HDLC_DEF_MASTER_INT_TIMER_LEN);

        /* 由于在中断服务程序中进行了清中断操作，而Status指示是否出错的bit由原始
           中断寄存器决定，故此处取保存在g_stHdlcRegSaveInfo中的状态值 */
        ulStatus = g_stHdlcRegSaveInfo.ulHdlcDefStatus;

    }
    else
    {
        /* 轮询得到暂停或完成 */
        ulResult = PPP_HDLC_HARD_DefWaitStatusChange();

        /* 查询hdlc_def_status (0x88)获取解封装状态并将其返回 */
        ulStatus  =  PPP_HDLC_READ_32REG(SOC_ARM_HDLC_DEF_STATUS_ADDR(HDLC_IP_BASE_ADDR));
    }

    /* 上报寄存器可维可测 */
    PPP_HDLC_HARD_MntnDefTraceRegConfig(VOS_TRUE, 0, ulEnableInterrupt);

    /* 等不到说明HDLC还在工作 */
    if (VOS_OK != ulResult)
    {
        return HDLC_DEF_STATUS_DOING;
    }

    ulStatus &=  HDLC_DEF_STATUS_MASK;

    return ulStatus;
}

/*****************************************************************************
 函 数 名  : PPP_HDLC_HARD_DefCfgEnReg
 功能描述  : 根据本次解封装数据量大小，决定使用何况方式等待HDLC的结果
 输入参数  : ulLinkTotalSize     -   本次解封装参数链表内的总数据量(单位字节)
 输出参数  : 无
 返 回 值  : 无
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2012年4月10日
    作    者   : l00164359
    修改内容   : 新生成函数

*****************************************************************************/
VOS_UINT32 PPP_HDLC_HARD_DefCfgEnReg
(
    VOS_UINT32                      ulTotalLen
)
{
    /*
    hdlc_def_en   (0x60)
      31   25 24  23 19 18  17  16  15  14  13  12  11  10   9   8   7   1  0
    |--------|---|-----|---|---|---|---|---|---|---|---|---|---|---|------|---|
    |   Rsv  |en | Rsv |en |en |en |en |en |en |en |en |en |en |en |  Rsv |en |

    Reserved            [31:25] 7'b0    h/s R/W  保留位。读时返回0。写时无影响。
    def_over_int_en     [24]    1'b0    h/s R/W  一套链表解封装结束中断使能;0：中断禁止;1：中断使能;
    Reserved            [23:19] 5'b0    h/s R/W  保留位。读时返回0。写时无影响。
    def_rpt_ful_en      [18]    1'b0    h/s R/W  解封装外部正确帧信息上报空间存满暂停中断使能;0：中断禁止;1：中断使能;
    def_out_spc_ful_en  [17]    1'b0    h/s R/W  解封装外部输出存储空间存满暂停中断使能;0：中断禁止;1：中断使能
    def_lcp_int_en      [16]    1'b0    h/s R/W  解封装解出有效LCP帧暂停中断上报使能;0：中断禁止;1：中断使能
    def_rpt_prm_err_en  [15]    1'b0    h/s R/W  解封装上报空间相关参数错误中断使能;0：中断禁止;1：中断使能
    def_out_prm_err_en  [14]    1'b0    h/s R/W  解封装输出空间相关参数错误中断使能;0：中断禁止;1：中断使能
    def_in_prm_err_en   [13]    1'b0    h/s R/W  解封装输入链表相关参数错误中断使能;0：中断禁止;1：中断使能
    def_cfg_err_en      [12]    1'b0    h/s R/W  解封装协议压缩指示配置错误中断使能;0：中断禁止;1：中断使能
    def_wr_timeout_en   [11]    1'b0    h/s R/W  解封装时AXI总线写请求timeout中断使能;0：中断禁止;1：中断使能
    def_rd_timeout _en  [10]    1'b0    h/s R/W  解封装时AXI总线读请求timeout中断使能;0：中断禁止;1：中断使能
    def_wr_err_en       [9]     1'b0    h/s R/W  解封装时AXI总线写操作错误中断使能;0：中断禁止;1：中断使能
    def_rd_err_en       [8]     1'b0    h/s R/W  解封装时AXI总线读操作错误中断使能;0：中断禁止;1：中断使能
    Reserved            [7:1]   7'b0    h/s R/W  保留位。读时返回0。写时无影响。
    def_en              [0]     1'b0    h/s R/W  一套输入链表解封装使能，软件向def_en写入1'b1启动解封装工作；一套输入链表解封装完成后，由硬件自动对def_en清零；
                                                 解封装过程出错时，硬件也会对def_en自动清零，使内部状态机返回IDLE状态；读该寄存器返回解封装处理状态。
                                                 写时设置一套输入链表解封装使能：0：不使能解封装处理；1：使能解封装处理；
                                                 读时返回一套输入链表解封装处理状态：0：没在进行解封装处理；1：正在进行解封装处理。
    */
    VOS_UINT32          ulEnableInterrupt;
    VOS_UINT32          ulValue;
    const VOS_UINT32    ulInterruptValue    = 0x0107FF01;   /* 使用中断方式时配置使能寄存器的值 */
    const VOS_UINT32    ulPollValue         = 0x01;         /* 使用轮询方式时配置使能寄存器的值 */


    if( ulTotalLen > HDLC_DEF_INTERRUPT_LIMIT )
    {
        /* 配置封装相关使能寄存器hdlc_def_en的[31:0]位为0x0107FF01 */
        ulValue             = ulInterruptValue;
        ulEnableInterrupt   = VOS_TRUE;

        g_PppHdlcHardStat.ulDefWaitIntCnt++;
    }
    else
    {
        /* 配置封装相关使能寄存器hdlc_frm_en的[31:0]位为0x01 */
        ulValue             = ulPollValue;
        ulEnableInterrupt   = VOS_FALSE;

        g_PppHdlcHardStat.ulDefWaitQueryCnt++;
    }

    /* 使能前清除上次封装、解封装的原始中断 */
    PPP_HDLC_WRITE_32REG(SOC_ARM_HDLC_DEF_INT_CLR_ADDR(HDLC_IP_BASE_ADDR), 0xFFFFFFFFU);
    PPP_HDLC_WRITE_32REG(SOC_ARM_HDLC_FRM_INT_CLR_ADDR(HDLC_IP_BASE_ADDR), 0xFFFFFFFFU);

    /* 上报寄存器可维可测 */
    PPP_HDLC_HARD_MntnDefTraceRegConfig(VOS_FALSE, ulValue, ulEnableInterrupt);

    /* 使能硬件之前先强制ARM顺序执行结束前面的指针 */
    TTF_FORCE_ARM_INSTUCTION();

    PPP_HDLC_WRITE_32REG(SOC_ARM_HDLC_DEF_EN_ADDR(HDLC_IP_BASE_ADDR), ulValue);

    /* PC上使用HDLC模拟器 */
#if (VOS_OS_VER == VOS_WIN32)
    VHW_HDLC_Task();
#endif

    return ulEnableInterrupt;
}

/*****************************************************************************
 函 数 名  : PPP_HDLC_HARD_CommCfgReg
 功能描述  : 配置通用寄存器
 输入参数  : 无
 输出参数  : 无
 返 回 值  : 无
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2012年4月10日
    作    者   : l00164359
    修改内容   : 新生成函数

*****************************************************************************/
VOS_VOID PPP_HDLC_HARD_CommCfgReg(VOS_VOID)
{
    /*
    prior_timeout_ctrl(0x04)
      31  24   23                16   15  9         8             7   2    1          0
    |--------|----------------------|-------|-------------------|-------|---------------|
    |   Rsv  | axireq_timeout_value |  Rsv  | axireq_timeout_en |  Rsv  |hdlc_prior_ctrl|

    Reserved             [31:24] 8'b0   h/s R/W  保留位。读时返回0。写时无影响。
    axireq_timeout_value [23:16] 8'b0   h/s R/W  软件配置AXI总线读写请求超时的判断值
    Reserved             [15:9]  2'b0   h/s R/W  保留位。读时返回0。写时无影响。
    axireq_timeout_en    [8]     1'b0   h/s R/W  是否允许硬件判断AXI总线读写请求超时，由软件配置：
                                                   0不允许
                                                   1允许
    Reserved             [7:2]   1'b0   h/s R/W  保留位。读时返回0。写时无影响。
    hdlc_prior_ctrl      [1:0]   1'b0   h/s R/W  HDLC封装、解封装优先级配置寄存器：
                                                    00：一个在工作中，另一个也被使能情况下，先将已处于工作中的那个处理完，
                                                        即谁先被使能则先将谁处理完；
                                                    01：下行封装优先级高；
                                                    10：上行解封装优先级高；
                                                    11：无效。
                                                    (HDLC内部控制被暂停者的继续开始工作：当解封装被暂停，封装整套链表被处理完后，
                                                    解封装就开始继续工作；当封装被暂停，解封装整个数据包被处理完后，封装就开始继续工作。)
    */

    VOS_UINT32                          ulValue = 0x0;


    /* 使能AXI请求超时判断，debug时使用，由于HDLC设置超时时间过短，故正常功能模式下不开启 */
/*    SET_BIT_TO_DWORD(ulValue, 8); */

    /* 设置AXI请求超时时长，该值由SoC提供，并且保证无平台差异 */
    ulValue |= (HDLC_AXI_REQ_TIMEOUT_VALUE << 16);

    PPP_HDLC_WRITE_32REG(SOC_ARM_HDLC_PRIROR_TIMEOUT_CTRL_ADDR(HDLC_IP_BASE_ADDR), ulValue);

    return;
}

/*****************************************************************************
 函 数 名  : PPP_HDLC_HARD_MntnShowConfigInfo
 功能描述  : 打印配置信息
 输入参数  : 无
 输出参数  : 无
 返 回 值  : 无
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2012年4月10日
    作    者   : l00164359
    修改内容   : 新生成函数

*****************************************************************************/
VOS_VOID PPP_HDLC_HARD_MntnShowConfigInfo(VOS_VOID)
{
    /* 输出IP相关信息 */
    PPP_HDLC_WARNING_LOG3("HDLC Hardware Info: g_ulHDLCIPBaseAddr 0x%x g_slHdlcISRDef %d g_slHdlcISRFrm %d\r\n",
                  HDLC_IP_BASE_ADDR, g_stHdlcConfigInfo.slHdlcISRDef, g_stHdlcConfigInfo.slHdlcISRFrm);
    PPP_HDLC_WARNING_LOG2("HDLC Hardware Info: g_ulHdlcDefMasterSem 0x%x g_ulHdlcFrmMasterSem 0x%x\r\n",
                  g_stHdlcConfigInfo.ulHdlcDefMasterSem, g_stHdlcConfigInfo.ulHdlcFrmMasterSem);

    /* 输出内存相关信息 */
    PPP_HDLC_WARNING_LOG2("HDLC Memory Info: g_pstHdlcDefBufInfo 0x%x TTF_HDLC_MASTER_DEF_BUF_LEN %d\r\n",
                  g_pstHdlcDefBufInfo, TTF_HDLC_MASTER_DEF_BUF_LEN);
    PPP_HDLC_WARNING_LOG2("HDLC Memory Info: g_pstHdlcFrmBufInfo 0x%x TTF_HDLC_MASTER_FRM_BUF_LEN %d\r\n",
                  g_pstHdlcFrmBufInfo, TTF_HDLC_MASTER_FRM_BUF_LEN);

    return;
}

/*****************************************************************************
 函 数 名  : PPP_HDLC_HARD_MntnShowStatInfo
 功能描述  : 打印统计信息
 输入参数  : 无
 输出参数  : 无
 返 回 值  : 无
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2012年4月10日
    作    者   : l00164359
    修改内容   : 新生成函数

*****************************************************************************/
VOS_VOID PPP_HDLC_HARD_MntnShowStatInfo(VOS_VOID)
{
    vos_printf("\n================HDLC Hardware STAT INFO Begin==========================\n");

    vos_printf("解封装处理IP类型包个数            = %d\n", g_PppHdlcHardStat.ulDefIpDataProcCnt);
    vos_printf("解封装处理PPP类型包个数           = %d\n", g_PppHdlcHardStat.ulDefPppDataProcCnt);
    vos_printf("解封装输出非完整帧个数            = %d\n", g_PppHdlcHardStat.ulDefUncompleteCnt);
    vos_printf("解封装等待中断次数                = %d\n", g_PppHdlcHardStat.ulDefWaitIntCnt);
    vos_printf("解封装轮询次数                    = %d\n", g_PppHdlcHardStat.ulDefWaitQueryCnt);
    vos_printf("解封装中断次数                    = %d\n", g_PppHdlcHardStat.ulDefIsrCnt);
    vos_printf("解封装LCP帧暂停次数               = %d\n", g_PppHdlcHardStat.ulDefLcpPauseCnt);
    vos_printf("解封装空间满暂停次数              = %d\n", g_PppHdlcHardStat.ulDefFullPauseCnt);
    vos_printf("解封装丢弃错误数据包个数          = %d\n", g_PppHdlcHardStat.ulDefInputDiscardCnt);

    vos_printf("封装处理IP类型包个数              = %d\n", g_PppHdlcHardStat.ulFrmIpDataProcCnt);
    vos_printf("封装处理PPP类型包个数             = %d\n", g_PppHdlcHardStat.ulFrmPppDataProcCnt);
    vos_printf("封装等待中断次数                  = %d\n", g_PppHdlcHardStat.ulFrmWaitIntCnt);
    vos_printf("封装轮询次数                      = %d\n", g_PppHdlcHardStat.ulFrmWaitQueryCnt);
    vos_printf("封装中断次数                      = %d\n", g_PppHdlcHardStat.ulFrmIsrCnt);
    vos_printf("封装申请目的空间内存失败次数      = %d\n", g_PppHdlcHardStat.ulFrmAllocOutputMemFailCnt);
    vos_printf("封装申请第一个目的空间内存失败次数= %d\n", g_PppHdlcHardStat.ulFrmAllocFirstMemFailCnt);
    vos_printf("封装输出参数链表满次数            = %d\n", g_PppHdlcHardStat.ulFrmOutputLinkFullCnt);
    vos_printf("封装丢弃错误数据包个数            = %d\n", g_PppHdlcHardStat.ulFrmInputDiscardCnt);

    vos_printf("解封装输入链表最大节点数          = %d\n", g_PppHdlcHardStat.ulDefMaxInputCntOnce);
    vos_printf("解封装输入链表最大总长度          = %d\n", g_PppHdlcHardStat.ulDefMaxInputSizeOnce);
    vos_printf("解封装输出有效帧最大个数          = %d\n", g_PppHdlcHardStat.ulDefMaxValidCntOnce);
    vos_printf("解封装轮询最大次数                = %d\n", g_PppHdlcHardStat.ulDefMaxQueryCnt);

    vos_printf("封装输入链表最大节点数            = %d\n", g_PppHdlcHardStat.ulFrmMaxInputCntOnce);
    vos_printf("封装输入链表最大总长度            = %d\n", g_PppHdlcHardStat.ulFrmMaxInputSizeOnce);
    vos_printf("封装输出使用最大节点个数          = %d\n", g_PppHdlcHardStat.ulFrmMaxOutputCntOnce);
    vos_printf("封装输出使用最大节点总长度        = %d\n", g_PppHdlcHardStat.ulFrmMaxOutputCntOnce);
    vos_printf("封装轮询最大次数                  = %d\n", g_PppHdlcHardStat.ulFrmMaxQueryCnt);

    vos_printf("单次处理最大节点数                = %d\n", g_PppHdlcHardStat.ulMaxCntOnce);
    vos_printf("处理总节点数                      = %d\n", g_PppHdlcHardStat.ulHdlcHardProcCnt);
    vos_printf("continue次数                      = %d\n", g_PppHdlcHardStat.ulContinueCnt);
    vos_printf("usDefExpInfo标识                  = %d\n", g_PppHdlcHardStat.usDefExpInfo);
    vos_printf("usFrmExpInfo标识                  = %d\n", g_PppHdlcHardStat.usFrmExpInfo);

    vos_printf("规避HDLC BUG不拷贝数据次数        = %d\n", g_PppHdlcHardStat.ulForbidHdlcBugNoCpy);
    vos_printf("规避HDLC BUG拷贝数据次数          = %d\n", g_PppHdlcHardStat.ulForbidHdlcBugCpy);


    vos_printf("================HDLC Hardware STAT INFO End==========================\n");

    return;
}

/*****************************************************************************
 函 数 名  : PPP_HDLC_HARD_MntnTraceSingleData
 功能描述  : 勾取单个数据
 输入参数  : usDataLen   -   单个数据长度
             pucDataAddr -   数据首地址
             ulEventType -   数据类型
             ulNodeIndex -   数据所在链表结点的下标
 输出参数  : 无
 返 回 值  : 无
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2012年4月10日
    作    者   : l00164359
    修改内容   : 新生成函数

*****************************************************************************/
VOS_VOID PPP_HDLC_HARD_MntnTraceSingleData
(
    VOS_UINT16                          usDataLen,
    VOS_UINT8                          *pucDataAddr,
    HDLC_MNTN_EVENT_TYPE_ENUM_UINT32    ulEventType,
    VOS_UINT32                          ulNodeIndex
)
{
    VOS_UINT32                          ulDataLen;
    HDLC_MNTN_NODE_DATA_STRU           *pstNodeData;
    VOS_UINT32                          ulAllocDataLen;


    ulAllocDataLen = TTF_MIN(usDataLen, HDLC_MNTN_ALLOC_MEM_MAX_SIZE);

    /* 消息长度等于消息结构大小加数据内容长度 */
    ulDataLen   = ulAllocDataLen + sizeof(HDLC_MNTN_NODE_DATA_STRU);

    pstNodeData = (HDLC_MNTN_NODE_DATA_STRU *)PS_MEM_ALLOC(PS_PID_PPP_HDLC, ulDataLen);

    if (VOS_NULL_PTR == pstNodeData)
    {
        PPP_HDLC_NORMAL_LOG1("PPP_HDLC_HARD_MntnTraceSingleData, NORMAL, Alloc mem failed, ulEventType %d!\r\n",
                      ulEventType);
        return;
    }

    /* 用于标识这是一组输入链表中的第几个IP包 */
    pstNodeData->usNodeIndex = (VOS_UINT16)ulNodeIndex;
    pstNodeData->usLen       = usDataLen;

    PPP_MemSingleCopy((VOS_UINT8 *)(pstNodeData + 1), pucDataAddr, ulAllocDataLen);

    PPP_HDLC_HARD_MntnTraceMsg((HDLC_MNTN_TRACE_HEAD_STRU *)pstNodeData,
                               ulEventType, ulDataLen);

    PS_MEM_FREE(PS_PID_PPP_HDLC, pstNodeData);

    return;
}

/*****************************************************************************
 函 数 名  : PPP_HDLC_HARD_MntnTraceInputParaLink
 功能描述  : 勾取输入参数链表内容
 输入参数  : ulEventType        - 数据类型,
             ulLinkNodeCnt      - 输入参数结点个数,
             ulLinkTotalSize    - 输入数据总长度,
             pastLinkNodeBuf    - 输入参数链表首地址
 输出参数  : 无
 返 回 值  : 无
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2012年4月10日
    作    者   : l00164359
    修改内容   : 新生成函数

*****************************************************************************/
VOS_VOID PPP_HDLC_HARD_MntnTraceInputParaLink
(
    HDLC_MNTN_EVENT_TYPE_ENUM_UINT32    ulEventType,
    VOS_UINT32                          ulLinkNodeCnt,
    VOS_UINT32                          ulLinkTotalSize,
    HDLC_PARA_LINK_NODE_STRU           *pastLinkNodeBuf
)
{
    HDLC_MNTN_INPUT_PARA_LINK_STRU      stInputPara;
    HDLC_MNTN_INPUT_PARA_LINK_STRU     *pstInputPara = &stInputPara;
    VOS_UINT32                          ulDataLen;


    ulDataLen = sizeof(HDLC_MNTN_INPUT_PARA_LINK_STRU);

    /* 记录并上报参数链表所有节点的信息*/
    pstInputPara->ulInputLinkNodeCnt   = ulLinkNodeCnt;
    pstInputPara->ulInputLinkTotalSize = ulLinkTotalSize;

    /* 参数链表每个节点的内容 */
    VOS_MemCpy((VOS_UINT8 *)(&pstInputPara->astInputParaLinkNodeBuf[0]),
               (VOS_UINT8 *)(pastLinkNodeBuf),
               ulLinkNodeCnt * sizeof(HDLC_PARA_LINK_NODE_STRU));

    PPP_HDLC_HARD_MntnTraceMsg((HDLC_MNTN_TRACE_HEAD_STRU *)pstInputPara,
                               ulEventType, ulDataLen);

    return;
}

/*****************************************************************************
 函 数 名  : PPP_HDLC_HARD_DefIsEnabled
 功能描述  : 查询当前解封装模块是否使能
 输入参数  : 无
 输出参数  : 无
 返 回 值  : VOS_TRUE  - 已使能
             VOS_FALSE - 未使能
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2012年4月10日
    作    者   : l00164359
    修改内容   : 新生成函数

*****************************************************************************/
VOS_UINT32 PPP_HDLC_HARD_DefIsEnabled(VOS_VOID)
{
    VOS_UINT32                          ulValue;


    /* SoC会在处理完一套输入链表的时候自动将使能位清零 */
    ulValue = PPP_HDLC_READ_32REG(SOC_ARM_HDLC_DEF_EN_ADDR(HDLC_IP_BASE_ADDR));

    if (0x01 == (ulValue & 0x01))
    {
        return VOS_TRUE;
    }
    else
    {
        return VOS_FALSE;
    }
}

/*****************************************************************************
 函 数 名  : PPP_HDLC_HARD_FrmIsEnabled
 功能描述  : 查询当前封装模块是否使能
 输入参数  : 无
 输出参数  : 无
 返 回 值  : VOS_TRUE  - 已使能
             VOS_FALSE - 未使能
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2012年4月10日
    作    者   : l00164359
    修改内容   : 新生成函数

*****************************************************************************/
VOS_UINT32 PPP_HDLC_HARD_FrmIsEnabled(VOS_VOID)
{
    VOS_UINT32                          ulValue;


    /* SoC会在处理完一套输入链表的时候自动将使能位清零 */
    ulValue = PPP_HDLC_READ_32REG(SOC_ARM_HDLC_FRM_EN_ADDR(HDLC_IP_BASE_ADDR));

    if (0x01 == (ulValue & 0x01))
    {
        return VOS_TRUE;
    }
    else
    {
        return VOS_FALSE;
    }
}

/*****************************************************************************
 函 数 名  : PPP_HDLC_HARD_SetUp
 功能描述  : 初始化该路PPP链接，如清空非完整帧信息
 输入参数  : usPppId - PPP ID
 输出参数  : 无
 返 回 值  : 无
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2012年4月10日
    作    者   : l00164359
    修改内容   : 新生成函数

*****************************************************************************/
VOS_VOID PPP_HDLC_HARD_SetUp(PPP_ID usPppId)
{
    HDLC_DEF_UNCOMPLETED_INFO_STRU      *pstUncompletedInfo;


    pstUncompletedInfo = HDLC_DEF_GET_UNCOMPLETED_INFO(usPppId);

    VOS_MemSet(pstUncompletedInfo, 0, sizeof(HDLC_DEF_UNCOMPLETED_INFO_STRU));

    return;
}

/*****************************************************************************
 函 数 名  : PPP_HDLC_HARD_Disable
 功能描述  : 对HDLC进行去使能
 输入参数  : 无
 输出参数  : 无
 返 回 值  : 无
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2012年4月10日
    作    者   : l00164359
    修改内容   : 新生成函数

*****************************************************************************/
VOS_VOID PPP_HDLC_HARD_Disable(VOS_VOID)
{
    /* 暂无操作，因为HDLC优化后，一套链表封装或解封装完成时，由硬件自动对frm_en或def_en清零；
       封装或解封装过程出错时，硬件也会自动清零，使内部状态机返回IDLE状态；*/
}

/*****************************************************************************
 函 数 名  : PPP_HDLC_HARD_Init
 功能描述  : 对HDLC进行初始化: HDLC配置发生异常时, 对异常中断上报的控制
 输入参数  : 无
 输出参数  : 无
 返 回 值  : 无
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2012年4月10日
    作    者   : l00164359
    修改内容   : 新生成函数

*****************************************************************************/
VOS_UINT32 PPP_HDLC_HARD_Init(VOS_VOID)
{
    VOS_UINT_PTR                          ulBaseAddr;

    /* 获取HDLC基地址 */
    ulBaseAddr              = (VOS_UINT_PTR)mdrv_misc_get_ip_baseaddr(BSP_IP_TYPE_HDLC);

    HDLC_IP_BASE_ADDR       = (VOS_UINT_PTR)PPP_IO_ADDRESS(ulBaseAddr);

    if (VOS_NULL_PTR == HDLC_IP_BASE_ADDR)
    {
        PPP_HDLC_ERROR_LOG1("PPP_HDLC_HARD_Init HDLC base addr is null,0x%x\r\n",
                      ulBaseAddr);
        return VOS_ERR;
    }

#if (VOS_OS_VER == VOS_WIN32)
    g_ulHdlcScCtrlBaseAddr  = g_ucScCtrlRegAddr;
#else

#if ((SC_CTRL_MOD_P532 == SC_CTRL_MOD) || (SC_CTRL_MOD_6950_SFT == SC_CTRL_MOD) || (SC_CTRL_MOD_6932_SFT == SC_CTRL_MOD))
    ulBaseAddr              = (VOS_UINT_PTR)mdrv_misc_get_ip_baseaddr(BSP_IP_TYPE_SYSCTRL_PD);
#elif (SC_CTRL_MOD_6250_SFT == SC_CTRL_MOD)
    /* =========dallas中使用: HDLC寄存器基地址位置======== */
    ulBaseAddr              = (VOS_UINT_PTR)mdrv_misc_get_ip_baseaddr(BSP_IP_TYPE_SYSCTRL_MDM);
#else
    ulBaseAddr              = (VOS_UINT_PTR)mdrv_misc_get_ip_baseaddr(BSP_IP_TYPE_SYSCTRL);
#endif

    g_ulHdlcScCtrlBaseAddr  = (VOS_UINT_PTR)PPP_IO_ADDRESS(ulBaseAddr);

#endif
    if (VOS_NULL_PTR == g_ulHdlcScCtrlBaseAddr)
    {
        PPP_HDLC_ERROR_LOG1("PPP_HDLC_HARD_Init HDLC SCCTRL base addr is null,0x%x\r\n",
                      ulBaseAddr);
        return VOS_ERR;
    }

    /* 关闭HDLC时钟 */
    PPP_HDLC_HARD_PeriphClkClose();

    /*获取HDLC解封装中断号*/
    g_stHdlcConfigInfo.slHdlcISRDef   = mdrv_int_get_num(BSP_INT_TYPE_HDLC_DEF);

    /*获取HDLC封装中断号*/
    g_stHdlcConfigInfo.slHdlcISRFrm   = mdrv_int_get_num(BSP_INT_TYPE_HDLC_FRM);

    /* 初始化内存 */
    if (VOS_OK != PPP_HDLC_HARD_InitBuf())
    {
        return VOS_ERR;
    }

    if ( VOS_OK != VOS_SmBCreate("HdlcDefMasterSem", 0, VOS_SEMA4_FIFO, (VOS_SEM *)&g_stHdlcConfigInfo.ulHdlcDefMasterSem) )
    {
        PPP_HDLC_ERROR_LOG("PPP_HDLC_HARD_Init, ERROR, Create g_ulHdlcDefMasterSem failed!\r\n");
        return VOS_ERR;
    }

    if ( VOS_OK != VOS_SmBCreate("HdlcFrmMasterSem", 0, VOS_SEMA4_FIFO, (VOS_SEM *)&g_stHdlcConfigInfo.ulHdlcFrmMasterSem) )
    {
        PPP_HDLC_ERROR_LOG("PPP_HDLC_HARD_Init, ERROR, Create g_ulHdlcFrmMasterSem failed!\r\n");
        return VOS_ERR;
    }

    /* 中断挂接 */
    if (VOS_OK != mdrv_int_connect(g_stHdlcConfigInfo.slHdlcISRDef, (VOIDFUNCPTR)PPP_HDLC_HARD_DefIsr, 0))
    {
        PPP_HDLC_ERROR_LOG1("PPP_HDLC_HARD_Init, ERROR, Connect slHdlcISRDef %d to PPP_HDLC_HARD_DefIsr failed!\r\n",
                      g_stHdlcConfigInfo.slHdlcISRDef);
        return VOS_ERR;
    }

    /* 中断使能 */
    if (VOS_OK != mdrv_int_enable(g_stHdlcConfigInfo.slHdlcISRDef))
    {
        PPP_HDLC_ERROR_LOG1("PPP_HDLC_HARD_Init, ERROR, Enable slHdlcISRDef %d failed!\r\n",
                      g_stHdlcConfigInfo.slHdlcISRDef);
        return VOS_ERR;
    }

    /* 中断挂接 */
    if (VOS_OK != mdrv_int_connect(g_stHdlcConfigInfo.slHdlcISRFrm, (VOIDFUNCPTR)PPP_HDLC_HARD_FrmIsr, 0))
    {
        PPP_HDLC_ERROR_LOG1("PPP_HDLC_HARD_Init, ERROR, Connect slHdlcISRFrm %d to PPP_HDLC_HARD_FrmIsr failed!\r\n",
                      g_stHdlcConfigInfo.slHdlcISRFrm);
        return VOS_ERR;
    }

    if (VOS_OK != mdrv_int_enable(g_stHdlcConfigInfo.slHdlcISRFrm))
    {
        PPP_HDLC_ERROR_LOG1("PPP_HDLC_HARD_Init, ERROR, Enable slHdlcISRFrm %d failed!\r\n",
                      g_stHdlcConfigInfo.slHdlcISRFrm);
        return VOS_ERR;
    }

    return VOS_OK;
}    /* link_HDLCInit */

/*****************************************************************************
 函 数 名  : PPP_Help
 功能描述  : 帮助打印
 输入参数  : 无
 输出参数  : 无
 返 回 值  : 无
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2013年9月25日
    作    者   : x59651
    修改内容   : 新生成函数

*****************************************************************************/
VOS_VOID PPP_Help(VOS_VOID)
{
    vos_printf("********************PPP软调信息************************\n");
    vos_printf("PPP_HDLC_HARD_MntnShowStatInfo      打印统计信息\n");
    vos_printf("PPP_INPUT_ShowStatInfo              打印 g_PppDataQCtrl信息\n");
    vos_printf("PPP_HDLC_HARD_MntnSetConfig         设置可维可测等级:\n");
    vos_printf("                                    1--参数；2--寄存器；4--数据\n");
    vos_printf("PPP_HDLC_HARD_MntnShowDefReg        打印解封装寄存器信息\n");
    vos_printf("PPP_HDLC_HARD_MntnShowFrmReg        打印封装寄存器信息\n");
    vos_printf("PPP_HDLC_HARD_MntnSetDefIntLimit    设置解封装中断水线\n");
    vos_printf("PPP_HDLC_HARD_MntnSetFrmIntLimit    设置封装中断水线\n");
    vos_printf("PPP_HDLC_HARD_MntnShowConfigInfo    打印配置信息\n");

    vos_printf("PPP_Info                            虚地址  :0x%x\n", g_ulPppVirtAddr);
    vos_printf("PPP_Info                            物理地址:0x%x\n", g_ulPppPhyAddr);
    vos_printf("PPP_Info                            内存长度:0x%x\n", g_ulPppTotalBufLen);

    return;
}

#if (VOS_RTOSCK == VOS_OS_VER)

/*****************************************************************************
 函 数 名  : PPP_HDLC_HARD_InitBuf
 功能描述  : 初始化HDLC需要的内存
 输入参数  : 无
 输出参数  : 无
 返 回 值  : 无
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2012年4月10日
    作    者   : l00164359
    修改内容   : 新生成函数

*****************************************************************************/
VOS_UINT32 PPP_HDLC_HARD_InitBuf(VOS_VOID)
{
    /* 计算内存长度，实际使用长度为0x6140，申请按照0x8000(32K) */
    /* C核32字节对齐即可 */
    g_ulPppTotalBufLen = TTF_DATA_ALIGN(TTF_HDLC_MASTER_LINK_TOTAL_LEN);

    /* 内存申请 */
    g_ulPppPhyAddr     = TTF_GetHdlcMemSection();

    /* 在C核虚实地址相同 */
    g_ulPppVirtAddr = g_ulPppPhyAddr;
    if (!g_ulPppVirtAddr)
    {
        PPP_HDLC_ERROR_LOG("PPP_HDLC_HARD_InitBuf, ERROR, VOS_UnCacheMemAlloc Fail\r\n");
        return VOS_ERR;
    }

    memset((void *)g_ulPppVirtAddr, 0, g_ulPppTotalBufLen);

    /* 根据TtfMemoryMap.h初始化HDLC所需内存 */
    g_pstHdlcDefBufInfo = (HDLC_DEF_BUFF_INFO_STRU *)g_ulPppVirtAddr;
    g_pstHdlcFrmBufInfo = (HDLC_FRM_BUFF_INFO_STRU *)(g_ulPppVirtAddr + sizeof(HDLC_DEF_BUFF_INFO_STRU));

    /*lint -e506 -e774*/
    /* TTF_HDLC_MASTER_DEF_BUF_LEN必须与结构HDLC_DEF_BUFF_INFO_STRU的大小一致 */
    if (TTF_HDLC_MASTER_DEF_BUF_LEN != sizeof(HDLC_DEF_BUFF_INFO_STRU))
    {
        PPP_HDLC_WARNING_LOG2("PPP_HDLC_HARD_InitBuf, ERROR, TTF_HDLC_MASTER_DEF_BUF_LEN %d sizeof(HDLC_DEF_BUFF_INFO_STRU) %d\r\n",
                      TTF_HDLC_MASTER_DEF_BUF_LEN, sizeof(HDLC_DEF_BUFF_INFO_STRU));
        return VOS_ERR;
    }

    /* TTF_HDLC_MASTER_FRM_BUF_LEN收必须与结构HDLC_FRM_BUFF_INFO_STRU的大小一致 */
    if (TTF_HDLC_MASTER_FRM_BUF_LEN != sizeof(HDLC_FRM_BUFF_INFO_STRU))
    {
        PPP_HDLC_WARNING_LOG2("PPP_HDLC_HARD_InitBuf, ERROR, TTF_HDLC_MASTER_FRM_BUF_LEN %d sizeof(HDLC_FRM_BUFF_INFO_STRU) %d\r\n",
                      TTF_HDLC_MASTER_FRM_BUF_LEN, sizeof(HDLC_FRM_BUFF_INFO_STRU));
        return VOS_ERR;
    }
    /*lint +e506 +e774*/

    return VOS_OK;
}

/*****************************************************************************
 函 数 名  : PPPC_HDLC_HARD_CommReleaseLink
 功能描述  : 释放存储的PPP_ZC_STRU结构
 输入参数  : ppstLinkNode   -- 存储PPP_ZC_STRU指针的数组
             ulRelCnt       -- 待释放的个数
 输出参数  : 无
 返 回 值  : 无
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2012年4月10日
    作    者   : l00164359
    修改内容   : 新生成函数

*****************************************************************************/
VOS_VOID PPPC_HDLC_HARD_CommReleaseLink
(
    PPPC_DATA_LINK_NODE_STRU          **ppstLinkNode,
    VOS_UINT32                          ulRelCnt
)
{
    VOS_UINT32                          ulNodeLoop;


    for ( ulNodeLoop = 0; ulNodeLoop < ulRelCnt; ulNodeLoop++ )
    {
        PPP_MemFree(ppstLinkNode[ulNodeLoop]);

        ppstLinkNode[ulNodeLoop] = VOS_NULL_PTR;
    }

    return;
}

/*****************************************************************************
 函 数 名  : PPPC_HDLC_HARD_DefProcErrorFrames
 功能描述  : 处理错误帧
 输入参数  : usPppId    -   PPP链路信息
 输出参数  : 无
 返 回 值  : 无
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2012年4月10日
    作    者   : l00164359
    修改内容   : 新生成函数

*****************************************************************************/
VOS_VOID PPPC_HDLC_HARD_DefProcErrorFrames
(
    VOS_UINT16                          usPppId
)
{
    VOS_UINT8                           ucErrType;
    VOS_UINT8                           ucMask;
    VOS_UINT32                          ulErrTypeLoop;
    VOS_UINT8                           ucResult;
    HDLC_DEF_ERR_FRAMES_CNT_STRU        stErrCnt;
    PPPINFO_S                          *pstPppInfo = VOS_NULL_PTR;


    /* 查询状态寄存器hdlc_def_status (0x88)的第24:30对应比特位为1表示有某种错误帧输出，
       为0表示无帧输出 */
    ucErrType = (VOS_UINT8)TTF_Read32RegByBit(SOC_ARM_HDLC_DEF_STATUS_ADDR(HDLC_IP_BASE_ADDR) , 24, 30);

    if (0 == ucErrType)
    {
        return;
    }

    GETPPPINFOPTRBYRP(pstPppInfo, usPppId);
    if (VOS_NULL_PTR == pstPppInfo)
    {
        PPP_HDLC_WARNING_LOG1("PPPC_HDLC_HARD_DefProcErrorFrames, Get PPP Ent Fail %d\r\n", usPppId);
        return;
    }

    /*lint -e734*/
    /* get fcs error count */
    stErrCnt.usFCSErrCnt        = (VOS_UINT16)TTF_Read32RegByBit(SOC_ARM_HDLC_DEF_ERR_INFO_0_ADDR(HDLC_IP_BASE_ADDR), 0, 15);

    /* get frame too long error count */
    stErrCnt.usLenLongCnt       = (VOS_UINT16)TTF_Read32RegByBit(SOC_ARM_HDLC_DEF_ERR_INFO_0_ADDR(HDLC_IP_BASE_ADDR), 16, 31);

    /* get frame too short error count */
    stErrCnt.usLenShortCnt      = (VOS_UINT16)TTF_Read32RegByBit(SOC_ARM_HDLC_DEF_ERR_INFO_1_ADDR(HDLC_IP_BASE_ADDR), 0, 15);

    /* get error protocol count */
    stErrCnt.usErrProtocolCnt   = (VOS_UINT16)TTF_Read32RegByBit(SOC_ARM_HDLC_DEF_ERR_INFO_1_ADDR(HDLC_IP_BASE_ADDR), 16, 31);

    /* get error control count */
    stErrCnt.usErrCtrlCnt       = (VOS_UINT16)TTF_Read32RegByBit(SOC_ARM_HDLC_DEF_ERR_INFO_2_ADDR(HDLC_IP_BASE_ADDR), 0, 15);

    /* get error address count */
    stErrCnt.usErrAddrCnt       = (VOS_UINT16)TTF_Read32RegByBit(SOC_ARM_HDLC_DEF_ERR_INFO_2_ADDR(HDLC_IP_BASE_ADDR), 16, 31);

    /* get error flag position count */
    stErrCnt.usFlagPosErrCnt    = (VOS_UINT16)TTF_Read32RegByBit(SOC_ARM_HDLC_DEF_ERR_INFO_3_ADDR(HDLC_IP_BASE_ADDR), 0, 15);
    /*lint +e734*/
    for (ulErrTypeLoop = 0UL; ulErrTypeLoop < HDLC_DEF_MAX_TYPE_CNT; ulErrTypeLoop++)
    {
        ucMask   = SET_BITS_VALUE_TO_BYTE(0x01, ulErrTypeLoop);    /* 构造掩码 */
        ucResult = (VOS_UINT8)GET_BITS_FROM_BYTE(ucErrType, ucMask);

        if (0 != ucResult)      /* 存在此类错误 */
        {
            if (0UL == ulErrTypeLoop)   /* 错误类型0: CRC校验错误 */
            {
                ((PPPC_HDLC_STRU *)(pstPppInfo->pstHdlcInfo))->stats.badfcs       += stErrCnt.usFCSErrCnt;
                ((PPPC_HDLC_STRU *)(pstPppInfo->pstHdlcInfo))->SaveInErrors   += stErrCnt.usFCSErrCnt;
                PPP_HDLC_WARNING_LOG("bad hdlc fcs\r\n");
            }
            else if (1UL == ulErrTypeLoop)    /* 错误类型1: 解封装后帧字节数大于1502bytes */
            {
                ((PPPC_HDLC_STRU *)(pstPppInfo->pstHdlcInfo))->SaveInErrors += stErrCnt.usLenLongCnt;
                PPP_HDLC_WARNING_LOG1("bad hdlc frame length too long\r\n", stErrCnt.usLenLongCnt);
            }
            else if (2UL == ulErrTypeLoop)    /* 错误类型2: 解封装后帧字节数小于4bytes */
            {
                ((PPPC_HDLC_STRU *)(pstPppInfo->pstHdlcInfo))->SaveInErrors += stErrCnt.usLenShortCnt;
                PPP_HDLC_WARNING_LOG("bad hdlc frame length too short\r\n");
            }
            else if (3UL == ulErrTypeLoop)    /* 错误类型3: 当P域需剥离时, 收到非法的Protocol域值(非*******0 *******1形式) */
            {
                ((PPPC_HDLC_STRU *)(pstPppInfo->pstHdlcInfo))->SaveInErrors += stErrCnt.usErrProtocolCnt;
                PPP_HDLC_WARNING_LOG("bad hdlc frame protocol\r\n");
            }
            else if (4UL == ulErrTypeLoop)    /* 错误类型4: 当AC域无压缩时, Control域值非0x03 */
            {
                ((PPPC_HDLC_STRU *)(pstPppInfo->pstHdlcInfo))->SaveInErrors += stErrCnt.usErrCtrlCnt;
                ((PPPC_HDLC_STRU *)(pstPppInfo->pstHdlcInfo))->stats.badcommand += stErrCnt.usErrCtrlCnt;
                PPP_HDLC_WARNING_LOG("bad hdlc frame control\r\n");
            }
            else if (5UL == ulErrTypeLoop)    /* 错误类型5: 当AC域无压缩时, Address域值非0xFF */
            {
                ((PPPC_HDLC_STRU *)(pstPppInfo->pstHdlcInfo))->SaveInErrors += stErrCnt.usErrAddrCnt;
                ((PPPC_HDLC_STRU *)(pstPppInfo->pstHdlcInfo))->stats.badaddr    += stErrCnt.usErrAddrCnt;
                PPP_HDLC_WARNING_LOG("bad hdlc frame address\r\n");
            }
            else if (6UL == ulErrTypeLoop)    /* 错误类型6: 转义字符0x7D后紧接一个Flag域 */
            {
                ((PPPC_HDLC_STRU *)(pstPppInfo->pstHdlcInfo))->SaveInErrors += stErrCnt.usFlagPosErrCnt;
                PPP_HDLC_WARNING_LOG("bad hdlc frame flag position\r\n");
            }
            else
            {
                PPP_HDLC_WARNING_LOG("link_HDLCDefDealErr err\r\n");
            }
        }
    }

    return;
}

/*****************************************************************************
 函 数 名  : PPPC_HDLC_HARD_DefSaveUncompletedInfo
 功能描述  : 根据非完整帧指示，保存非完整帧信息
 输入参数  : usPppId    -   PPP实体ID
 输出参数  : 无
 返 回 值  : 无
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2012年4月10日
    作    者   : l00164359
    修改内容   : 新生成函数

*****************************************************************************/
VOS_VOID PPPC_HDLC_HARD_DefSaveUncompletedInfo
(
    PPP_ID          usPppId
)
{
    HDLC_DEF_UNCOMPLETED_INFO_STRU     *pstUncompletedInfo;
    VOS_UINT32                          ulStatus;                /* 解封装状态 */
    HDLC_DEF_BUFF_INFO_STRU            *pstDefBuffInfo;
    VOS_UINT32                          ulValidNum;
    VOS_UINT8                          *pucDefOutOneAddr;
    HDLC_DEF_RPT_NODE_STRU             *pstRptNode;


    pstDefBuffInfo     = HDLC_DEF_GET_BUF_INFO(usPppId);
    pstUncompletedInfo = HDLC_DEF_GET_UNCOMPLETED_INFO(usPppId);

    ulStatus  =   PPP_HDLC_READ_32REG(SOC_ARM_HDLC_DEF_STATUS_ADDR(HDLC_IP_BASE_ADDR));

    /* 查询状态寄存器hdlc_def_status (0x88)的第2位
       为1表示本次解封装有非完整帧输出，
       为0表示无非完整帧输出 */
    if (0 == (ulStatus & 0x4))
    {
        pstUncompletedInfo->ucExistFlag = HDLC_DEF_UNCOMPLETED_NOT_EXIST;

        return;
    }

    g_PppHdlcHardStat.ulDefUncompleteCnt++;

    /* def_valid_num        [23:8]  16'b0   h/s RO   有帧上报时，有效帧数目；（不包括最后一个可能的非完整帧） */
    ulValidNum = (ulStatus & 0xFFFF00) >> 8;

    /* 非完整帧的上报信息在有效帧后面，但是不算在有效帧数目内 */
    if (TTF_HDLC_DEF_RPT_MAX_NUM <= ulValidNum)
    {
        PPP_HDLC_WARNING_LOG2("PPP_HDLC_HARD_DefSaveUncompletedInfo, ERROR, ulValidNum %d >= TTF_HDLC_DEF_RPT_MAX_NUM %d!\r\n",
                     ulValidNum, TTF_HDLC_DEF_RPT_MAX_NUM);

        pstUncompletedInfo->ucExistFlag = HDLC_DEF_UNCOMPLETED_NOT_EXIST;

        return;
    }

    /* 有非完整帧时需要读取并保存def_uncomplet_st_now(0x8C)、def_info_frl_cnt_now(0xC4)
       读取并保存上报空间有效帧之后的非完整帧长度、协议和数据地址 */
    pstUncompletedInfo->ucExistFlag = HDLC_DEF_UNCOMPLETED_EXIST;

    pstRptNode = &(pstDefBuffInfo->astRptNodeBuf[ulValidNum]);

    pucDefOutOneAddr = pstRptNode->pucDefOutOneAddr;


    if (pucDefOutOneAddr != HDLC_DEF_OUTPUT_BUF_START_ADDR)
    {
        if ((pucDefOutOneAddr - HDLC_DEF_OUTPUT_BUF_START_ADDR) >= pstRptNode->usDefOutOneLen)
        {
            mdrv_memcpy(HDLC_DEF_OUTPUT_BUF_START_ADDR, pucDefOutOneAddr, pstRptNode->usDefOutOneLen);
        }
        else
        {
            PS_MEM_MOVE(HDLC_DEF_OUTPUT_BUF_START_ADDR, pucDefOutOneAddr, pstRptNode->usDefOutOneLen);
        }

        pstRptNode->pucDefOutOneAddr = HDLC_DEF_OUTPUT_BUF_START_ADDR;

    }


    /* 非完整帧的协议、长度和在存储空间的地址，软件只是暂存这些信息，等下解封装的时候再原样配给HDLC */
    pstUncompletedInfo->usDefOutOnePro   = pstRptNode->usDefOutOnePro;
    pstUncompletedInfo->usDefOutOneLen   = pstRptNode->usDefOutOneLen;
    pstUncompletedInfo->pucDefOutOneAddr = pstRptNode->pucDefOutOneAddr;

    /* 软件只是暂存这些信息，等下解封装的时候再原样配给HDLC */
    pstUncompletedInfo->ulDefStAgo         = PPP_HDLC_READ_32REG(SOC_ARM_HDLC_DEF_UNCOMPLETED_ST_NOW_ADDR(HDLC_IP_BASE_ADDR));
    pstUncompletedInfo->ulDefInfoFrlCntAgo = PPP_HDLC_READ_32REG(SOC_ARM_HDLC_DEF_INFO_FRL_CNT_NOW_ADDR(HDLC_IP_BASE_ADDR));

    PPP_HDLC_HARD_MntnDefTraceUncompleteInfo(pstUncompletedInfo);

    return;
}

/*****************************************************************************
 函 数 名  : PPPC_HDLC_HARD_MntnDefTraceOutput
 功能描述  : 勾取解封装输出数据
 输入参数  : pstBuildInfo    -   存放输入数据
             usValidFrameNum -   有效帧个数
 输出参数  : 无
 返 回 值  : 无
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2012年4月10日
    作    者   : l00164359
    修改内容   : 新生成函数

*****************************************************************************/
VOS_VOID PPPC_HDLC_HARD_MntnDefTraceOutput
(
    VOS_UINT16                          usValidFrameNum,
    HDLC_DEF_BUFF_INFO_STRU            *pstDefBuffInfo
)
{
    HDLC_MNTN_DEF_OUTPUT_PARA_STRU     *pstOutputPara;
    VOS_UINT32                          ulDataLen;
    VOS_UINT32                          ulNodeLoop;
    HDLC_DEF_RPT_NODE_STRU             *pstRptNode;
    VOS_UINT16                          usMaxFrameNum;


    /* 解封装上报空间可维可测 */
    if ((g_stHdlcConfigInfo.ulHdlcMntnTraceCfg & PPP_HDLC_MNTN_TRACE_PARA) != 0)
    {
        usMaxFrameNum = (HDLC_MNTN_ALLOC_MEM_MAX_SIZE - sizeof(HDLC_MNTN_DEF_OUTPUT_PARA_STRU)) /
                         sizeof(HDLC_DEF_RPT_NODE_STRU);
        usMaxFrameNum = TTF_MIN(usMaxFrameNum, usValidFrameNum);

        ulDataLen     = sizeof(HDLC_MNTN_DEF_OUTPUT_PARA_STRU) + usMaxFrameNum * sizeof(HDLC_DEF_RPT_NODE_STRU);
        pstOutputPara = (HDLC_MNTN_DEF_OUTPUT_PARA_STRU *)PS_MEM_ALLOC(PS_PID_PPP_HDLC, ulDataLen);

        if (VOS_NULL_PTR == pstOutputPara)
        {
            PPP_HDLC_WARNING_LOG1("PPP_HDLC_HARD_MntnDefTraceOutput, NORMAL, Alloc mem failed ulDataLen %d!\r\n", ulDataLen);
            return;
        }

        pstOutputPara->usDefValidNum = usValidFrameNum;
        pstOutputPara->usTraceNum    = usMaxFrameNum;

        VOS_MemCpy((VOS_UINT8 *)(pstOutputPara + 1),
                   (VOS_UINT8 *)(&(pstDefBuffInfo->astRptNodeBuf[0])),
                   usMaxFrameNum * sizeof(HDLC_DEF_RPT_NODE_STRU));

        PPP_HDLC_HARD_MntnTraceMsg((HDLC_MNTN_TRACE_HEAD_STRU *)pstOutputPara,
                                   ID_HDLC_MNTN_DEF_OUTPUT_PARA, ulDataLen);

        PS_MEM_FREE(PS_PID_PPP_HDLC, pstOutputPara);
    }

    /* 解封装目的空间中每个有效帧可维可测 */
    if ((g_stHdlcConfigInfo.ulHdlcMntnTraceCfg & PPP_HDLC_MNTN_TRACE_DATA) != 0)
    {
        for ( ulNodeLoop = 0; ulNodeLoop < usValidFrameNum; ulNodeLoop++ )
        {
            pstRptNode = &(pstDefBuffInfo->astRptNodeBuf[ulNodeLoop]);

            PPP_HDLC_HARD_MntnTraceSingleData(pstRptNode->usDefOutOneLen, pstRptNode->pucDefOutOneAddr,
                                              ID_HDLC_MNTN_DEF_OUTPUT_DATA, ulNodeLoop);
        }
    }

    return;
}

/*****************************************************************************
 函 数 名  : PPPC_HDLC_HARD_DefProcRptNode
 功能描述  : 根据上报信息地址和长度，申请零拷贝内存，并拷贝数据
 输入参数  : pstRptNode   -   上报信息
 输出参数  : 无
 返 回 值  : 无
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2012年4月10日
    作    者   : l00164359
    修改内容   : 新生成函数

*****************************************************************************/
PPPC_DATA_LINK_NODE_STRU * PPPC_HDLC_HARD_DefProcRptNode
(
    HDLC_DEF_RPT_NODE_STRU             *pstRptNode
)
{
    PPPC_DATA_LINK_NODE_STRU           *pstMem;
    VOS_UINT16                          usFistSegLen;
    VOS_UINT8                          *pucDefOutOneAddr;
    VOS_UINT8                           aucHeadData[4];


    if ( (0 == pstRptNode->usDefOutOneLen) || (HDLC_DEF_OUT_PER_MAX_CNT < pstRptNode->usDefOutOneLen) )
    {
        PPP_HDLC_WARNING_LOG1("PPP_HDLC_HARD_DefProcValidFrames, WARNING, invalid usDefOutOneLen %d\r\n",
                      pstRptNode->usDefOutOneLen);

        return VOS_NULL_PTR;
    }

    pstMem = PPP_MemAlloc(sizeof(aucHeadData) + pstRptNode->usDefOutOneLen, TTF_MEM_POOL_ID_DL_PDU);

    if (VOS_NULL_PTR == pstMem)
    {
        PPP_HDLC_WARNING_LOG1("\r\nPPPC_HDLC_HARD_DefProcRptNode allocMemlen:%d\r\n", pstRptNode->usDefOutOneLen);
        return VOS_NULL_PTR;
    }

    /* 地址与控制域 */
    aucHeadData[0] = 0xff;
    aucHeadData[1] = 0x03;
    /* 协议域 */
    aucHeadData[2] = (VOS_UINT8)((pstRptNode->usDefOutOnePro >> 8) & 0x00FF);
    aucHeadData[3] = (VOS_UINT8)(pstRptNode->usDefOutOnePro & 0x00FF);

    VOS_MemCpy(&pstMem->pstPduMem->pData[pstMem->pstPduMem->usUsed], aucHeadData, sizeof(aucHeadData));
    pstMem->pstPduMem->usUsed   += sizeof(aucHeadData);

    pucDefOutOneAddr    = pstRptNode->pucDefOutOneAddr;
    /* 判断该帧起始加长度是否超过输出空间尾部，超出后按绕回处理 */
    if ((pucDefOutOneAddr + pstRptNode->usDefOutOneLen) >
        HDLC_DEF_OUTPUT_BUF_END_ADDR)
    {
        if (pucDefOutOneAddr <= HDLC_DEF_OUTPUT_BUF_END_ADDR)
        {
            usFistSegLen = (VOS_UINT16)(HDLC_DEF_OUTPUT_BUF_END_ADDR - pucDefOutOneAddr);

            /* 拷贝从起始地址至输出空间尾部的数据 */
            VOS_MemCpy(&pstMem->pstPduMem->pData[pstMem->pstPduMem->usUsed], pucDefOutOneAddr, usFistSegLen);
            pstMem->pstPduMem->usUsed   += usFistSegLen;

            /* 拷贝在输出空间首部的剩余数据 */
            VOS_MemCpy(&pstMem->pstPduMem->pData[pstMem->pstPduMem->usUsed],
                HDLC_DEF_OUTPUT_BUF_START_ADDR, pstRptNode->usDefOutOneLen - usFistSegLen);
            pstMem->pstPduMem->usUsed   += pstRptNode->usDefOutOneLen - usFistSegLen;
        }
        else
        {
            PPP_MemFree(pstMem);

            PPP_HDLC_WARNING_LOG2("\r\nPPP, PPP_HDLC_HARD_DefProcRptNode, ERROR, Error pucDefOutOneAddr.\r\n", pucDefOutOneAddr, HDLC_DEF_OUTPUT_BUF_END_ADDR);

            PPP_HDLC_HARD_MntnShowDefReg();

            return VOS_NULL_PTR;
        }
    }
    else
    {
        VOS_MemCpy(&pstMem->pstPduMem->pData[pstMem->pstPduMem->usUsed], pucDefOutOneAddr, pstRptNode->usDefOutOneLen);
        pstMem->pstPduMem->usUsed   += pstRptNode->usDefOutOneLen;
    }

    return pstMem;
}

/*****************************************************************************
 函 数 名  : PPPC_HDLC_HARD_DefProcValidFrames
 功能描述  : 处理有效帧
 输入参数  : ucRatMode  -   速率模式1X/HRPD
             usPppId    -   PPP实体ID
             pstLink    -   PPP链路信息
 输出参数  : 无
 返 回 值  : 无
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2012年4月10日
    作    者   : l00164359
    修改内容   : 新生成函数

*****************************************************************************/
VOS_VOID PPPC_HDLC_HARD_DefProcValidFrames
(
    VOS_UINT8                           ucRatMode,
    PPP_ID                              usPppId
)
{
    VOS_UINT16                          usValidFrameNum;
    HDLC_DEF_BUFF_INFO_STRU            *pstDefBuffInfo;
    VOS_UINT32                          ulFrameLoop;
    HDLC_DEF_RPT_NODE_STRU             *pstRptNode;
    PPPC_DATA_LINK_NODE_STRU           *pstMem;


    pstDefBuffInfo  = HDLC_DEF_GET_BUF_INFO(usPppId);
    usValidFrameNum = (VOS_UINT16)TTF_Read32RegByBit(SOC_ARM_HDLC_DEF_STATUS_ADDR(HDLC_IP_BASE_ADDR), 8, 23);

    /* 上报解封装后数据可维可测:上报空间信息、输出内容 */
    PPPC_HDLC_HARD_MntnDefTraceOutput(usValidFrameNum, pstDefBuffInfo);

    /* 有效帧数最大值检查 */
    if (TTF_HDLC_DEF_RPT_MAX_NUM < usValidFrameNum)
    {
        PPP_HDLC_WARNING_LOG2("PPP_HDLC_HARD_DefProcValidFrames, WARNING, usValidFrameNum = %d > TTF_HDLC_DEF_RPT_MAX_NUM = %d",
                      usValidFrameNum, TTF_HDLC_DEF_RPT_MAX_NUM);
        return;
    }

    g_PppHdlcHardStat.ulDefMaxValidCntOnce = TTF_MAX(g_PppHdlcHardStat.ulDefMaxValidCntOnce, usValidFrameNum);

    /* 将目的空间的有效帧数据拷贝至零拷贝内存，根据拨号类型调用上行发数接口 */
    for ( ulFrameLoop = 0 ; ulFrameLoop < usValidFrameNum; ulFrameLoop++ )
    {
        pstRptNode = &(pstDefBuffInfo->astRptNodeBuf[ulFrameLoop]);

        pstMem = PPPC_HDLC_HARD_DefProcRptNode(pstRptNode);

        /* 申请不到内容或上报信息错误，丢弃该有效帧 */
        if (VOS_NULL_PTR == pstMem)
        {
            continue;
        }

        #ifdef PPPC_HDLC_ST_TEST
        PPPC_STUB_ProcDlData(pstMem);
        #else
        FWD_PppDecap(0, 0, pstMem->pstPduMem, ucRatMode, (VOS_UINT8)usPppId);
        pstMem->pstPduMem = VOS_NULL_PTR;
        /* 释放零拷贝内存 */
        TTF_NODE_MEM_FREE(PS_PID_PPP_HDLC, pstMem);

        #endif
        g_stPppcDataQueueStats.ulDownlinkSndDataCnt++;
    }

    return;
}

/*****************************************************************************
 函 数 名  : PPP_HDLC_HARD_DefCfgReg
 功能描述  : 配置解封装配置寄存器
 输入参数  : pstLink    -   PPP链路信息
             pstDefUncompletedInfo  -   该路PPP链接上次解封装输出非完整帧信息
 输出参数  : 无
 返 回 值  : 无
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2012年4月10日
    作    者   : l00164359
    修改内容   : 新生成函数

*****************************************************************************/
VOS_UINT32 PPPC_HDLC_HARD_DefCfgReg
(
    VOS_UINT16                      usPppId,
    HDLC_DEF_UNCOMPLETED_INFO_STRU *pstDefUncompletedInfo
)
{
    VOS_UINT32                          ulPppAcFlag = 0;    /* AC域默认无压缩 */
    VOS_UINT32                          ulPppPcFlag = 0;    /* P域默认无压缩 */


    /*
        hdlc_def_cfg  (0x70)
         31                           4 3     2   1     0
        |-------------------------------|-------|-----|-----|
        |              Rsv              |  Pfc  | Acfc| ago |
        Reserved             [31:4]  28'b0   h/s R/W  保留位。读时返回0。写时无影响。
        def_pfc              [3:2]   2'b0    h/s R/W  P域压缩指示：00：P域无压缩，需剥离；01：P域压缩，需剥离；11：P域不剥离；其他：无效；
        def_acfc             [1]     1'b0    h/s R/W  AC域压缩指示：0：AC域无压缩；1：表示AC域压缩；
        def_uncompleted_ago  [0]     1'b0    h/s R/W  用于指示对应当前解封装输入链表，同一PPP/IP拨号的以前最近解封装输入链表是否有解出非完整帧，
                                                      为了支持多个PPP/IP拨号而增加的配置：0，没有；1，有
        */

    VOS_UINT32       ulDeframerCfg;
    VOS_UINT8        ucACComp;
    VOS_UINT8        ucPComp;
    VOS_UINT8        ucLowByte;
    VOS_UINT16       usLowWord;

    /* 1.根据ulMode、P域和AC域是否压缩配置hdlc_def_cfg (0x70) */

    /* 获取AC域压缩指示, P域压缩指示 */
    (VOS_VOID)FWD_PppGetWantLcpAcfcFlag((VOS_UINT8)usPppId, &ulPppAcFlag);
    (VOS_VOID)FWD_PppGetWantLcpFcFlag((VOS_UINT8)usPppId, &ulPppPcFlag);

    ucACComp = (1 == ulPppAcFlag) ? 1 : 0;

    ucPComp = (1 == ulPppPcFlag)
               ? HDLC_PROTOCOL_REMOVE_WITH_COMPRESS
               : HDLC_PROTOCOL_REMOVE_WITHOUT_COMPRESS;

    /* 将ucPComp设置到一个字节的第2, 3位上 */
    ucLowByte = SET_BITS_VALUE_TO_BYTE(ucPComp, HDLC_DEF_PFC_BITPOS);

    if (1 == ucACComp)  /* AC域压缩 */
    {
        SET_BIT_TO_BYTE(ucLowByte, HDLC_DEF_ACFC_BITPOS);
    }

    /* 2.设置非完整帧相关信息 */
    if ( (VOS_NULL_PTR != pstDefUncompletedInfo) &&
        (HDLC_DEF_UNCOMPLETED_EXIST == pstDefUncompletedInfo->ucExistFlag) )
    {
        /* def_uncompleted_ago置1表示有上次输出的非完整帧参与本次解封装 */
        SET_BIT_TO_BYTE(ucLowByte, HDLC_DEF_IS_UNCOMPLETED_AGO_BITPOS);

        /*
        def_uncompleted_len  (0x74)
         31                 16  15                  0
        |---------------------|----------------------|
        |         Rsv         |         Len          |
        Reserved             [31:16] 16'b0   h/s R/W  保留位。读时返回0。写时无影响。
        def_uncompleted_len  [15:0]  16'b0   h/s R/W  对应当前解封装输入链表，同一PPP/IP拨号的以前最近解封装输入链表解出非完整帧的长度，为了支持多个PPP/IP拨号而增加的配置
        */
        PPP_HDLC_WRITE_32REG(SOC_ARM_HDLC_DEF_UNCOMPLETED_LEN_ADDR(HDLC_IP_BASE_ADDR),
                        (VOS_UINT32)pstDefUncompletedInfo->usDefOutOneLen & 0xFFFF);

        /*
        def_uncompleted_pro  (0x78)
         31                 16  15                  0
        |---------------------|----------------------|
        |         Rsv         |         Pro          |
        Reserved             [31:16] 16'b0   h/s R/W  保留位。读时返回0。写时无影响。
        def_uncompleted_pro  [15:0]  16'b0   h/s R/W  对应当前解封装输入链表，同一PPP/IP拨号的以前最近解封装输入链表解出非完整帧的
                                                      协议，为了支持多个PPP/IP拨号而增加的配置（可能其中的0Byte、1Byte或2Byte有效）
        */
        PPP_HDLC_WRITE_32REG(SOC_ARM_HDLC_DEF_UNCOMPLETED_PRO_ADDR(HDLC_IP_BASE_ADDR),
                        (VOS_UINT32)pstDefUncompletedInfo->usDefOutOnePro & 0xFFFF);

        /*
        def_uncompleted_addr  (0x7C)
         31                  0
        |----------------------|
        |         Addr         |
        def_uncompleted_addr [31:0]  32'b0   h/s R/W  对应当前解封装输入链表，同一PPP/IP拨号的以前最近解封装输入链表解出非完整帧的
                                                      外部存储起始地址，为了支持多个PPP/IP拨号而增加的配置（该地址可能是与原来上报不同的新地址）
        */
        PPP_HDLC_WRITE_32REG(SOC_ARM_HDLC_DEF_UNCOMPLETED_ADDR(HDLC_IP_BASE_ADDR),
                        (VOS_UINT32)pstDefUncompletedInfo->pucDefOutOneAddr);

        /*
        def_uncomplet_st_ago  (0x80)
         31                  16 15             5 4     0
        |----------------------|----------------|-------|
        |         Ago          |       Rsv      |  Ago  |
        crc16_result_ago     [31:16] 16'b0   h/s R/W  与当前解封装输入链表同一PPP/IP拨号的以前最近那套解封装输入链表处理完解出非完整帧时的CRC校验值
        Reserved             [15:5]  11'b0   h/s R/W  保留位。读时返回0。写时无影响。
        def_data_st_curr_ago [4:0]   5'b0    h/s R/W  与当前解封装输入链表同一PPP/IP拨号的以前最近那套解封装输入链表处理完解出非完整帧时的数据状态机当前状态
        */
        PPP_HDLC_WRITE_32REG(SOC_ARM_HDLC_DEF_UNCOMPLETED_ST_AGO_ADDR(HDLC_IP_BASE_ADDR),
                        (VOS_UINT32)pstDefUncompletedInfo->ulDefStAgo);

        /*
        def_info_frl_cnt_ago  (0xC0)
         31        27 26                 16 15   11 10              0
        |------------|---------------------|-------|-----------------|
        |    Rsv     |         Ago         |  Rsv  |       Ago       |
        Reserved             [31:27] 5'b0    h/s R/W  保留位。读时返回0。写时无影响。
        def_framel_cnt_ago   [26:16] 11'b0   h/s R/W  与当前解封装输入链表同一PPP/IP拨号的以前最近那套解封装输入链表处理完解出非完整帧时的帧长度
        Reserved             [15:11] 5'b0    h/s R/W  保留位。读时返回0。写时无影响。
        def_info_cnt_ago     [10:0]  11'b0   h/s R/W  与当前解封装输入链表同一PPP/IP拨号的以前最近那套解封装输入链表处理完解出非完整帧时的信息长度
        */
        PPP_HDLC_WRITE_32REG(SOC_ARM_HDLC_DEF_INFO_FRL_CNT_AGO_ADDR(HDLC_IP_BASE_ADDR),
                        (VOS_UINT32)pstDefUncompletedInfo->ulDefInfoFrlCntAgo);
    }

    usLowWord     = HDLC_MAKE_WORD(0x00, ucLowByte);
    ulDeframerCfg = HDLC_MAKE_DWORD(0x00, usLowWord);

    /* 将配置结果写入寄存器 */
    PPP_HDLC_WRITE_32REG(SOC_ARM_HDLC_DEF_CFG_ADDR(HDLC_IP_BASE_ADDR),ulDeframerCfg);

    /* 设置输入数据最大单包长度 */
    PPP_HDLC_WRITE_32REG(SOC_ARM_HDLC_DEF_IN_PKT_LEN_MAX_ADDR(HDLC_IP_BASE_ADDR),
                    (VOS_UINT32)HDLC_DEF_IN_PER_MAX_CNT);

    return VOS_OK;
}

/*****************************************************************************
 函 数 名  : PPPC_HDLC_HARD_DefWaitAndProc
 功能描述  : 等待解封装暂停或完成，然后处理输出数据，可能会有多次停等的过程
 输入参数  : ucRatMode  -   速率模式1X/HRPD
             ulEnableInterrupt  -   中断是否使能
             usPppId    -   PPP实体ID
             pstLink    -   PPP链路信息
 输出参数  : 无
 返 回 值  : 无
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2012年4月10日
    作    者   : l00164359
    修改内容   : 新生成函数

*****************************************************************************/
VOS_VOID PPPC_HDLC_HARD_DefWaitAndProc
(
    VOS_UINT8                           ucRatMode,
    VOS_UINT32                          ulEnableInterrupt,
    PPP_ID                              usPppId
)
{
    VOS_UINT32                          ulDefStatus;
    VOS_UINT32                          ulContinue;

    for (; ;)
    {
        /* 使能中断，则等待中断辅程序释放信号量；否则轮询解封装状态寄存器 */
        ulDefStatus = PPP_HDLC_HARD_DefWaitResult(ulEnableInterrupt);

        switch ( ulDefStatus )
        {
            case HDLC_DEF_STATUS_PAUSE_RPT_SPACE_FULL :
            case HDLC_DEF_STATUS_PAUSE_OUTPUT_SPACE_FULL :
                /* 处理有效帧，配置GO_ON寄存器 */
                PPPC_HDLC_HARD_DefProcValidFrames(ucRatMode, usPppId);
                PPP_HDLC_HARD_DefCfgGoOnReg(ulDefStatus);

                ulContinue = VOS_TRUE;
                g_PppHdlcHardStat.ulDefFullPauseCnt++;
                break;
            case HDLC_DEF_STATUS_PAUSE_LCP :
                /* 处理有效帧和LCP帧，更新配置寄存器，配置GO_ON寄存器 */
                PPPC_HDLC_HARD_DefProcValidFrames(ucRatMode, usPppId);
                PPPC_HDLC_HARD_DefCfgReg(usPppId, VOS_NULL_PTR);
                PPP_HDLC_HARD_DefCfgGoOnReg(ulDefStatus);

                ulContinue = VOS_TRUE;
                g_PppHdlcHardStat.ulDefLcpPauseCnt++;
                break;
            case HDLC_DEF_STATUS_DONE_WITHOUT_FRAMES :
                /* 根据非完整帧指示，保存非完整帧信息 */
                PPPC_HDLC_HARD_DefSaveUncompletedInfo(usPppId);

                ulContinue = VOS_FALSE;
                break;
            case HDLC_DEF_STATUS_DONE_WITH_FRAMES :
                /* 处理有效帧、错误帧和LCP帧(可能是最后一帧)，根据非完整帧指示，保存非完整帧信息 */
                PPPC_HDLC_HARD_DefProcValidFrames(ucRatMode, usPppId);
                PPPC_HDLC_HARD_DefProcErrorFrames(usPppId);
                PPPC_HDLC_HARD_DefSaveUncompletedInfo(usPppId);
                ulContinue = VOS_FALSE;
                break;
            case HDLC_DEF_STATUS_DOING :
            default:
                /* 打印异常日志，挂起PPP任务 */
                PPP_HDLC_HARD_DefProcException(ulDefStatus, ulEnableInterrupt);

                ulContinue = VOS_FALSE;
                break;
        }

        /* 暂停状态需要继续处理，其他状态解封装完成退出 */
        if (VOS_TRUE != ulContinue)
        {
            break;
        }
    }

    g_stHdlcRegSaveInfo.ulHdlcDefRawInt = 0xFFFFFFFFU;
    g_stHdlcRegSaveInfo.ulHdlcDefStatus = 0xFFFFFFFFU;

    return;
}

/************************************************************,*****************
 函 数 名  : PPPC_HDLC_HARD_DefCfgBufReg
 功能描述  : 配置解封装使用的内存至相关寄存器
 输入参数  : pstDefBuffInfo    -   解封装使用的内存信息
 输出参数  : 无
 返 回 值  : 无
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2012年4月10日
    作    者   : l00164359
    修改内容   : 新生成函数

*****************************************************************************/
VOS_VOID PPPC_HDLC_HARD_DefCfgBufReg(HDLC_DEF_BUFF_INFO_STRU *pstDefBuffInfo)
{
    /* 将封装输入参数链表的起始地址配置给寄存器def_in_lli_addr(0x90) */
    PPP_HDLC_WRITE_32REG(SOC_ARM_HDLC_DEF_IN_LLI_ADDR(HDLC_IP_BASE_ADDR),
                    (VOS_UINT32)&(pstDefBuffInfo->astInputParaLinkNodeBuf[0]));

    /* 将封装输出参数链表的起始地址配置给寄存器def_out_spc_addr(0xA0) */
    PPP_HDLC_WRITE_32REG(SOC_ARM_HDLC_DEF_OUT_SPC_ADDR(HDLC_IP_BASE_ADDR),
                    (VOS_UINT32)&(pstDefBuffInfo->aucOutputDataBuf[0]));

    /* 将封装输出参数链表的起始地址配置给寄存器def_out_space_dep(0xA4)低16位 */
    PPP_HDLC_WRITE_32REG(SOC_ARM_HDLC_DEF_OUT_SPACE_DEP_ADDR(HDLC_IP_BASE_ADDR),
                    (VOS_UINT32)TTF_HDLC_DEF_OUTPUT_DATA_BUF_LEN & 0xFFFF);

    /* 将封装有效帧结果信息上报空间起始地址配置给寄存器def_rpt_addr(0xA8) */
    PPP_HDLC_WRITE_32REG(SOC_ARM_HDLC_DEF_RPT_ADDR(HDLC_IP_BASE_ADDR),
                    (VOS_UINT32)&(pstDefBuffInfo->astRptNodeBuf[0]));

    /* 将封装有效帧结果信息上报空间深度配置给寄存器def_rpt_dep (0xAC)低16位 */
    PPP_HDLC_WRITE_32REG(SOC_ARM_HDLC_DEF_RPT_DEP_ADDR(HDLC_IP_BASE_ADDR),
                    (VOS_UINT32)TTF_HDLC_DEF_RPT_BUF_LEN & 0xFFFF);

    return;
}

/*****************************************************************************
 函 数 名  : PPPC_HDLC_HARD_MntnDefTraceInput
 功能描述  : 勾取解封装输入参数链表和数据
 输入参数  : pstFrmBuffInfo -   封装使用的内存
             pstBuildInfo   -   存放输入数据
 输出参数  : 无
 返 回 值  : 无
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2012年4月10日
    作    者   : l00164359
    修改内容   : 新生成函数

*****************************************************************************/
VOS_VOID PPPC_HDLC_HARD_MntnDefTraceInput
(
    HDLC_DEF_BUFF_INFO_STRU         *pstDefBuffInfo,
    HDLC_PARA_LINK_BUILD_INFO_STRU  *pstBuildInfo
)
{
    VOS_UINT32                          ulNodeLoop;
    HDLC_PARA_LINK_NODE_STRU           *pstParaNode;


    if ((g_stHdlcConfigInfo.ulHdlcMntnTraceCfg & PPP_HDLC_MNTN_TRACE_PARA) != 0)
    {
        PPP_HDLC_HARD_MntnTraceInputParaLink(ID_HDLC_MNTN_DEF_INPUT_PARA,
                                             pstBuildInfo->ulInputLinkNodeCnt,
                                             pstBuildInfo->ulInputLinkTotalSize,
                                             &(pstDefBuffInfo->astInputParaLinkNodeBuf[0]));
    }

    if ((g_stHdlcConfigInfo.ulHdlcMntnTraceCfg & PPP_HDLC_MNTN_TRACE_DATA) != 0)
    {
        /* 记录并上报参数链表所有节点的数据内容，每个节点是一个IP包 */
        for ( ulNodeLoop = 0; ulNodeLoop < pstBuildInfo->ulInputLinkNodeCnt; ulNodeLoop++ )
        {
            pstParaNode = &(pstDefBuffInfo->astInputParaLinkNodeBuf[ulNodeLoop]);

            PPP_HDLC_HARD_MntnTraceSingleData(pstParaNode->usDataLen,
                            (VOS_UINT8*)pstParaNode->pucDataAddr,
                            ID_HDLC_MNTN_DEF_INPUT_DATA, ulNodeLoop);
        }
    }

    return;
}

/*****************************************************************************
 函 数 名  : PPPC_HDLC_HARD_ForbiddenHdlcBug
 功能描述  : 规避HDLC硬件Bug,具体参见问题单DTS2014060907737
 输入参数  : ppstNode     -   待解封装数据包指针

 输出参数  : ppstNode  规避之后数据
 返 回 值  : 无
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2014年06月17日
    作    者   : t00148005
    修改内容   : 新生成函数

*****************************************************************************/
VOS_UINT32 PPPC_HDLC_HARD_ForbiddenHdlcBug(PPPC_DATA_LINK_NODE_STRU **ppstNode)
{
    PPPC_DATA_LINK_NODE_STRU           *pstDataNode;
    TTF_MEM_ST                         *pstSdu;
    VOS_UINT8                          *pstData;
    VOS_UINT16                          usLen;
    const VOS_UINT8                     ucEndByte = 0x7e;


    pstDataNode  = *ppstNode;

    if (VOS_NULL_PTR == pstDataNode)
    {
        return VOS_ERR;
    }

    usLen   = TTF_MemGetLen(PS_PID_PPP_HDLC, pstDataNode->pstPduMem);
    pstData = pstDataNode->pstPduMem->pData;

    if (usLen <= 1)
    {
        return VOS_OK;
    }

    if (ucEndByte != pstData[usLen - 2])
    {
        /* 倒数第二个字节不为7e不用处理 */
        return VOS_OK;
    }
    else if ((usLen >= 3) && (ucEndByte == pstData[usLen - 3]))
    {
        /* 倒数第三个字节为7e不用处理 */
        return VOS_OK;
    }
    else
    {
        /* 本分支有两种情况:
            1. usLen长度为2，第一个字节为7e;
            2. usLen长度大于2，倒数第二个字节为7e,倒数第三个字节不为7e;
         */
        /* 处理方法: 将最后一个字节取出来放入新申请的TTF内存中，
                     原来的TTF内存字节数减1，新申请的TTF内存挂载在原来的TTF内存后面 */
        pstSdu = TTF_MemBlkAlloc(PS_PID_PPP_HDLC, TTF_MEM_POOL_ID_DL_PDU, 1);
        if (VOS_NULL_PTR != pstSdu)
        {
            pstSdu->usUsed                  = 1;
            pstSdu->pData[0]                = pstDataNode->pstPduMem->pData[usLen - 1];
            pstDataNode->pstPduMem->usUsed -= 1;

            pstDataNode->pstPduMem->pNext   = pstSdu;

            return VOS_OK;
        }
        else
        {
            /* 更新下行申请失败次数 */
            g_stPppcDataQueueStats.ulMemAllocDownlinkFailCnt++;
            return VOS_ERR;
        }
    }


}

/*****************************************************************************
 函 数 名  : PPPC_HDLC_HARD_DefCheckPara
 功能描述  : 检查构造输入参数链表相关参数是否合法
 输入参数  : pstMem     -   待封装数据包
 输出参数  : 无
 返 回 值  : PPP_HDLC_PARA_CHECK_RESULT_ENUM_UINT32
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2012年4月20日
    作    者   : l00164359
    修改内容   : 新生成函数

*****************************************************************************/
PPP_HDLC_PARA_CHECK_RESULT_ENUM_UINT32 PPPC_HDLC_HARD_DefCheckPara
(
    PPPC_DATA_LINK_NODE_STRU           *pstMem
)
{
    VOS_UINT32                          ulDataLen;


    /* 内部调用，已保证pstMem非空 */


    ulDataLen   = (VOS_UINT32)TTF_MemGetLen(PS_PID_PPP_HDLC, pstMem->pstPduMem);

    /* 解封装最大输入长度是内存模块允许的最大长度，目前是1536B */
    if ((0 == ulDataLen) || (PPP_ZC_MAX_DATA_LEN < ulDataLen))
    {
        PPP_HDLC_WARNING_LOG1("PPP_HDLC_HARD_DefCheckPara, NORMAL, invalid data length %d\r\n", ulDataLen);

        return PPP_HDLC_PARA_CHECK_FAIL_DISCARD;
    }

    return PPP_HDLC_PARA_CHECK_PASS;
}

/*****************************************************************************
 函 数 名  : PPPC_HDLC_HARD_DefBuildInputParaLink
 功能描述  : 构造解封装输入参数链表
 输入参数  : pstBuildPara   -   构造链表所需的参数
 输出参数  : pstBuildInfo   -   构造链表的结果信息，保存输入链表长度、节点个数、零拷贝内存指针
 返 回 值  : 无
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2012年4月10日
    作    者   : l00164359
    修改内容   : 新生成函数

*****************************************************************************/
VOS_UINT32 PPPC_HDLC_HARD_DefBuildInputParaLink
(
    HDLC_PARA_LINK_BUILD_PARA_STRU  *pstBuildPara,
    HDLC_PARA_LINK_BUILD_INFO_STRU  *pstBuildInfo
)
{
    PPPC_DATA_LINK_NODE_STRU               *pstDataNode;
    PPP_HDLC_PARA_CHECK_RESULT_ENUM_UINT32  enCheckResult;
    VOS_UINT16                              usDataLen;
    HDLC_PARA_LINK_NODE_STRU               *pstParaNode;
    VOS_UINT32                              ulNodeIndex = 0;
    HDLC_DEF_BUFF_INFO_STRU                *pstDefBuffInfo;
    HDLC_DEF_UNCOMPLETED_INFO_STRU         *pstUncompletedInfo;
    VOS_UINT32                              ulMaxDataLen1Time = TTF_HDLC_DEF_INPUT_PARA_LINK_MAX_SIZE;
    VOS_UINT32                              ulRemainCnt;
    TTF_MEM_ST                             *pstSdu;


    /* 清空输出信息 */
    VOS_MemSet(pstBuildInfo, 0, sizeof(HDLC_PARA_LINK_BUILD_INFO_STRU));

    pstUncompletedInfo = HDLC_DEF_GET_UNCOMPLETED_INFO(pstBuildPara->usPppId);

    if (HDLC_DEF_UNCOMPLETED_EXIST == pstUncompletedInfo->ucExistFlag)
    {
        ulMaxDataLen1Time = TTF_HDLC_DEF_INPUT_PARA_LINK_MAX_SIZE - pstUncompletedInfo->usDefOutOneLen;
    }


    /* 根据usPppId找到对应的内存  */
    pstDefBuffInfo = HDLC_DEF_GET_BUF_INFO(pstBuildPara->usPppId);

    for (; pstBuildInfo->ulInputLinkNodeCnt < TTF_HDLC_DEF_INPUT_PARA_LINK_MAX_NUM;)
    {
        pstDataNode  = (PPPC_DATA_LINK_NODE_STRU *)TTF_LinkPeekHead(PS_PID_PPP_HDLC,
                        pstBuildPara->pstDlDataQ);

        /* 还没有到最大节点数，但是队列中已经没有数据 */
        if (VOS_NULL_PTR == pstDataNode)
        {
            break;
        }

        enCheckResult = PPPC_HDLC_HARD_DefCheckPara(pstDataNode);

        if ( PPP_HDLC_PARA_CHECK_FAIL_DISCARD == enCheckResult )
        {
            pstDataNode = (PPPC_DATA_LINK_NODE_STRU *)TTF_LinkSafeRemoveHead(
                        PS_PID_PPP_HDLC, pstBuildPara->pstDlDataQ, &ulRemainCnt);

            /* 释放节点和TTFMemory */
            PPP_MemFree(pstDataNode);
            pstDataNode = VOS_NULL_PTR;

            pstBuildInfo->ulDealCnt++;

            g_PppHdlcHardStat.ulDefInputDiscardCnt++;
            continue;
        }

        if ( PPP_HDLC_PARA_CHECK_FAIL_KEEP == enCheckResult )
        {
            break;
        }

        /* 规避HDLC BUG,在发现HDLC BUG场景下对原有数据进行替换,
           后面的pstMem为替换后的内存指针,原始内存指针可能已经被释放
         */
        /* 替换内存的时候申请内存失败,下次再处理  */
        if (VOS_OK != PPPC_HDLC_HARD_ForbiddenHdlcBug(&pstDataNode))
        {
            break;
        }

        /* 内存可能发生替换,重新取长度 */
        usDataLen = TTF_MemGetLen(PS_PID_PPP_HDLC, pstDataNode->pstPduMem);

        /* 一次配链表过程中待封装数据包总长不能超过15KB */
        /* 规避HDLC BUG,后面数据被修改过,可能扩大了1字节,需要放到后面判断 */
        if( pstBuildInfo->ulInputLinkTotalSize + usDataLen  > ulMaxDataLen1Time )
        {
            /* 下次再处理 */
            break;
        }

        /* 规避HDLC BUG后，Node节点中有两个TTF内存，但输入队列只剩下一个节点 */
        if ((VOS_NULL_PTR != pstDataNode->pstPduMem->pNext)
            && (pstBuildInfo->ulInputLinkNodeCnt == (TTF_HDLC_DEF_INPUT_PARA_LINK_MAX_NUM - 1)))
        {
            /* 下次再处理 */
            break;
        }

        /* 从PPP队列取出头结点，并插入输入队列 pstBuildInfo->apstInputLinkNode */
        pstDataNode  = (PPPC_DATA_LINK_NODE_STRU *)TTF_LinkSafeRemoveHead(
                        PS_PID_PPP_HDLC, pstBuildPara->pstDlDataQ, &ulRemainCnt);

        pstSdu  = pstDataNode->pstPduMem;
        while (VOS_NULL_PTR != pstSdu)
        {
            /* 获取当前要添加节点的下标 */
            ulNodeIndex = pstBuildInfo->ulInputLinkNodeCnt;

            /* 本次要构造的参数节点 */
            pstParaNode = &(pstDefBuffInfo->astInputParaLinkNodeBuf[ulNodeIndex]);

            /* 把节点组成链表 */
            if( 0 != ulNodeIndex )
            {
                pstDefBuffInfo->astInputParaLinkNodeBuf[ulNodeIndex - 1].pstNextNode
                    = (HDLC_PARA_LINK_NODE_STRU *)(VOS_UINT32)pstParaNode;
            }

            /* 填写输入参数链表结点相关域 */
            pstParaNode->pucDataAddr = (VOS_UINT8*)(pstSdu->pData);
            pstParaNode->usDataLen   = pstSdu->usUsed;
            pstParaNode->pstNextNode = VOS_NULL_PTR;

            pstBuildInfo->apstInputLinkNode[ulNodeIndex] = VOS_NULL_PTR;
            pstBuildInfo->ulInputLinkNodeCnt++;

            pstSdu = pstSdu->pNext;
        }

        pstBuildInfo->apstInputLinkNode[ulNodeIndex] = pstDataNode;

        pstBuildInfo->ulInputLinkTotalSize          += (VOS_UINT32)usDataLen;
        pstBuildInfo->ucRatMode                      = pstDataNode->enRatMode;
        pstBuildInfo->ulDealCnt++;
    }

    if (0 == pstBuildInfo->ulInputLinkNodeCnt)
    {
        return VOS_ERR;
    }

    /* 上报输入参数链表内容可维可测 */
    PPPC_HDLC_HARD_MntnDefTraceInput(pstDefBuffInfo, pstBuildInfo);

    return VOS_OK;
}

/*****************************************************************************
 函 数 名  : PPPC_HDLC_HARD_DefPacket
 功能描述  : 硬件方式IP类型解封装
 输入参数  : pstDataQ   -   PPP数据队列
             ulDealCnt  -   本次处理数据包个数
 输出参数  : 参见PPP_HDLC_RESULT_TYPE_ENUM_UINT32
 返 回 值  : 无
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2012年4月10日
    作    者   : l00164359
    修改内容   : 新生成函数

*****************************************************************************/
VOS_UINT32 PPPC_HDLC_HARD_DefPacket
(
    TTF_LINK_ST                        *pstDlDataQ,
    VOS_UINT16                          usPppId,
    VOS_UINT32                         *pulDealCnt
)
{
    VOS_UINT32                          ulEnableInterrupt;
    HDLC_PARA_LINK_BUILD_INFO_STRU      stBuildInfo;
    HDLC_PARA_LINK_BUILD_PARA_STRU      stBuildPara;
    VOS_UINT32                          ulBuildResult;
    HDLC_DEF_BUFF_INFO_STRU            *pstDefBuffInfo;


    pstDefBuffInfo = HDLC_DEF_GET_BUF_INFO(usPppId);

    stBuildPara.ucDataType = PPP_PUSH_PACKET_TYPE;
    stBuildPara.usProtocol = PPP_IP;
    stBuildPara.usPppId    = usPppId;
    stBuildPara.pstDlDataQ = pstDlDataQ;

    /* 构造输入参数链表，并上报链表内存可维可测 */
    ulBuildResult = PPPC_HDLC_HARD_DefBuildInputParaLink(&stBuildPara, &stBuildInfo);

    *pulDealCnt = stBuildInfo.ulDealCnt;

    if (VOS_OK != ulBuildResult)
    {
        PPP_HDLC_WARNING_LOG1("Build input parameter fail!\r\n", usPppId);
        PPPC_ClearDlDataQ();
        return ulBuildResult;
    }

    g_PppHdlcHardStat.ulDefMaxInputCntOnce  = TTF_MAX(g_PppHdlcHardStat.ulDefMaxInputCntOnce, stBuildInfo.ulInputLinkNodeCnt);
    g_PppHdlcHardStat.ulDefMaxInputSizeOnce = TTF_MAX(g_PppHdlcHardStat.ulDefMaxInputSizeOnce, stBuildInfo.ulInputLinkTotalSize);

    /* 配置封装、解封装通用寄存器 */
    PPP_HDLC_HARD_CommCfgReg();

    /* 配置内存相关寄存器 */
    PPPC_HDLC_HARD_DefCfgBufReg(pstDefBuffInfo);

    /* 配置压缩指示、非完整帧相关信息寄存器 */
    PPPC_HDLC_HARD_DefCfgReg(usPppId, HDLC_DEF_GET_UNCOMPLETED_INFO(usPppId));

    /* 配置使能寄存器，并上报使能前寄存器可维可测 */
    ulEnableInterrupt = PPP_HDLC_HARD_DefCfgEnReg(stBuildInfo.ulInputLinkTotalSize);

    /* 等待解封装暂停或完成，然后处理输出数据，可能会有多次停等的过程 */
    PPPC_HDLC_HARD_DefWaitAndProc(stBuildInfo.ucRatMode, ulEnableInterrupt, usPppId);

    /* 释放已解封装完成的数据 */
    PPPC_HDLC_HARD_CommReleaseLink(stBuildInfo.apstInputLinkNode, stBuildInfo.ulInputLinkNodeCnt);

    return VOS_OK;
}

/*****************************************************************************
 函 数 名  : PPPC_HDLC_HARD_FrmCfgBufReg
 功能描述  : 配置封装使用的内存至相关寄存器
 输入参数  : pstFrmBuffInfo -   封装使用的内存信息
 输出参数  : 无
 返 回 值  : 无
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2012年4月20日
    作    者   : c00191211
    修改内容   : 新生成函数

*****************************************************************************/
VOS_VOID PPPC_HDLC_HARD_FrmCfgBufReg(HDLC_FRM_BUFF_INFO_STRU *pstFrmBuffInfo)
{
    /* 将封装输入参数链表的起始地址配置给寄存器frm_in_lli_addr */
    PPP_HDLC_WRITE_32REG(SOC_ARM_HDLC_FRM_IN_LLI_ADDR(HDLC_IP_BASE_ADDR),
                    (VOS_UINT32)&(pstFrmBuffInfo->astInputParaLinkNodeBuf[0]));

    /* 将封装输出参数链表的起始地址配置给寄存器frm_out_lli_addr */
    PPP_HDLC_WRITE_32REG(SOC_ARM_HDLC_FRM_OUT_LLI_ADDR(HDLC_IP_BASE_ADDR),
                    (VOS_UINT32)&(pstFrmBuffInfo->astOutputParaLinkNodeBuf[0]));

    /* 将封装有效帧结果信息上报空间起始地址配置给寄存器frm_rpt_addr */
    PPP_HDLC_WRITE_32REG(SOC_ARM_HDLC_FRM_RPT_ADDR(HDLC_IP_BASE_ADDR),
                    (VOS_UINT32)&(pstFrmBuffInfo->astRptNodeBuf[0]));

    /* 将封装有效帧结果信息上报空间深度配置给寄存器frm_rpt_dep的[15:0]位 */
    PPP_HDLC_WRITE_32REG(SOC_ARM_HDLC_FRM_RPT_DEP_ADDR(HDLC_IP_BASE_ADDR),
                    (VOS_UINT32)TTF_HDLC_FRM_RPT_BUF_LEN & 0xFFFF);

    return;
}

/*****************************************************************************
 函 数 名  : PPP_HDLC_HARD_FrmCfgReg
 功能描述  : IP模式下配置封装相关寄存器
 输入参数  : usPppId    - PPP链路信息
             usProtocol - 待封装的协议值
 输出参数  :
 返 回 值  :
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2012年4月20日
    作    者   : c00191211
    修改内容   : 新生成函数

*****************************************************************************/
VOS_VOID PPPC_HDLC_HARD_FrmCfgReg
(
    VOS_UINT16                          usPppId,
    VOS_UINT16                          usProtocol
)
{
    /*
    hdlc_frm_cfg   (0x20)
      31              16 15           4 3      2   1      0
    |-------------------|--------------|--------|------|------|
    |      protocol     |      Rsv     |   Pfc  | Acfc |1dor2d|

    frm_protocol         [31:16] 16'b0   h/s R/W  封装协议值。有效协议值规定参见规格列表。
    Reserved             [15:4]  12'b0   h/s R/W  保留位。读时返回0。写时无影响。
    frm_pfc              [3:2]   2'b0    h/s R/W  P域压缩指示：00：硬件模块添加P域，P域无压缩;
                                                               01：硬件模块添加P域，P域压缩;
                                                               11：硬件模块不添加P域;
                                                               其他：无效;
    frm_acfc             [1]     1'b0    h/s R/W  AC域压缩指示：0：AC域无压缩;1：表示AC域压缩;
    frm_in_lli_1dor2d    [0]     1'b0    h/s R/W  封装输入一维或二维链表选择指示寄存器：
                                                                0为一维;1为二维;

    IP模式一定添加P域,PPP模式一定不添加P域
      LCP帧: AC域不压缩，P域不压缩
    */

    VOS_UINT32                          ulFrmCfg;
    VOS_UINT32                          ulPppAcFlag = 0;
    VOS_UINT32                          ulPppPcFlag = 0;
    VOS_UINT32                          ulAccmFlag  = 0;


    /* 将寄存器hdlc_frm_cfg的[0]位frm_in_lli_1dor2d配置为0 */
    ulFrmCfg = 0x0;

    /* 配置hdlc_frm_cfg的 P域和 AC域 */
    if (PPP_LCP != usProtocol)
    {
        /* 获取AC域压缩指示, P域压缩指示 */
        (VOS_VOID)FWD_PppGetHisLcpAcfcFlag((VOS_UINT8)usPppId, &ulPppAcFlag);
        (VOS_VOID)FWD_PppGetHisLcpFcFlag((VOS_UINT8)usPppId, &ulPppPcFlag);
        (VOS_VOID)FWD_PppGetHisAccm((VOS_UINT8)usPppId, &ulAccmFlag);
        if ( 1 == ulPppAcFlag )
        {
            ulFrmCfg |= (1 << HDLC_FRM_ACFC_BITPOS);
        }

        if ( 1 == ulPppPcFlag )
        {
            ulFrmCfg |= (1 << HDLC_FRM_PFC_BITPOS);
        }

        /* 配置hdlc_frm_accm */
        PPP_HDLC_WRITE_32REG(SOC_ARM_HDLC_FRM_ACCM_ADDR(HDLC_IP_BASE_ADDR),
                            ulAccmFlag);
    }
    else
    {
        PPP_HDLC_WRITE_32REG(SOC_ARM_HDLC_FRM_ACCM_ADDR(HDLC_IP_BASE_ADDR), 0xFFFFFFFFU);
    }

    /* 配置寄存器hdlc_frm_cfg的[31:16]位frm_protocol为usProtocol */
    ulFrmCfg |= ( ((VOS_UINT32)usProtocol) << 16 );

    PPP_HDLC_WRITE_32REG(SOC_ARM_HDLC_FRM_CFG_ADDR(HDLC_IP_BASE_ADDR), ulFrmCfg);

    return;
}

/*****************************************************************************
 函 数 名  : PPPC_HDLC_HARD_MntnFrmTraceOutput
 功能描述  : 勾取封装输出参数链表和数据
 输入参数  : ucFrmValidNum  -   有效帧个数
             usFrmOutSegNum -   有效帧分段个数
             pstFrmBuffInfo -   封装相关内存地址
             pstBuildInfo   -   存放输入数据
 输出参数  : 无
 返 回 值  : 无
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2012年4月10日
    作    者   : l00164359
    修改内容   : 新生成函数

*****************************************************************************/
VOS_VOID PPPC_HDLC_HARD_MntnFrmTraceOutput
(
    VOS_UINT8                           ucFrmValidNum,
    VOS_UINT16                          usFrmOutSegNum,
    HDLC_FRM_BUFF_INFO_STRU            *pstFrmBuffInfo,
    HDLC_PARA_LINK_BUILD_INFO_STRU     *pstBuildInfo
)
{
    HDLC_MNTN_FRM_OUTPUT_PARA_STRU      stOutputPara;
    HDLC_MNTN_FRM_OUTPUT_PARA_STRU     *pstOutputPara = &stOutputPara;
    VOS_UINT32                          ulDataLen;
    VOS_UINT32                          ulNodeLoop;
    HDLC_PARA_LINK_NODE_STRU           *pstParaNode;

    if ((g_stHdlcConfigInfo.ulHdlcMntnTraceCfg & PPP_HDLC_MNTN_TRACE_PARA) != 0)
    {
        ulDataLen     = sizeof(HDLC_MNTN_FRM_OUTPUT_PARA_STRU);

        pstOutputPara->ulOutputLinkNodeCnt   = pstBuildInfo->ulOutputLinkNodeCnt;
        pstOutputPara->ulOutputLinkTotalSize = pstBuildInfo->ulOutputLinkTotalSize;
        pstOutputPara->ucFrmValidNum         = ucFrmValidNum;
        pstOutputPara->usOutputNodeUsedCnt   = usFrmOutSegNum;

        VOS_MemCpy((VOS_UINT8 *)(&(pstOutputPara->astOutputParaLinkNodeBuf[0])),
                   (VOS_UINT8 *)(&(pstFrmBuffInfo->astOutputParaLinkNodeBuf[0])),
                   TTF_HDLC_FRM_OUTPUT_PARA_LINK_MAX_NUM * sizeof(HDLC_PARA_LINK_NODE_STRU));

        VOS_MemCpy((VOS_UINT8 *)(&(pstOutputPara->astRptNodeBuf[0])),
                   (VOS_UINT8 *)(&(pstFrmBuffInfo->astRptNodeBuf[0])),
                   TTF_HDLC_FRM_RPT_MAX_NUM * sizeof(HDLC_FRM_RPT_NODE_STRU));

        PPP_HDLC_HARD_MntnTraceMsg((HDLC_MNTN_TRACE_HEAD_STRU *)pstOutputPara,
                                        ID_HDLC_MNTN_FRM_OUTPUT_PARA, ulDataLen);
    }

    if ((g_stHdlcConfigInfo.ulHdlcMntnTraceCfg & PPP_HDLC_MNTN_TRACE_DATA) != 0)
    {
        for ( ulNodeLoop = 0; ulNodeLoop < usFrmOutSegNum; ulNodeLoop++ )
        {
            pstParaNode = &(pstFrmBuffInfo->astOutputParaLinkNodeBuf[ulNodeLoop]);

            PPP_HDLC_HARD_MntnTraceSingleData(pstParaNode->usDataLen, pstParaNode->pucDataAddr,
                                              ID_HDLC_MNTN_FRM_OUTPUT_DATA, ulNodeLoop);
        }
    }

    return;
}

/*****************************************************************************
 函 数 名  : PPPC_HDLC_HARD_FrmProcValidFram
 功能描述  : 处理有效帧，并释放剩余内存
 输入参数  : usPppId        -   PPP实体ID
 输出参数  : pstBuildInfo   -   构造链表的结果信息，保存输入链表长度、节点个数、零拷贝内存指针
 返 回 值  : 无
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2012年4月20日
    作    者   : c00191211
    修改内容   : 新生成函数

*****************************************************************************/
VOS_VOID PPPC_HDLC_HARD_FrmProcValidFrames
(
    PPP_ID                               usPppId,
    HDLC_PARA_LINK_BUILD_INFO_STRU      *pstBuildInfo
)
{
    PPPC_DATA_LINK_NODE_STRU           *pstMem;
    VOS_UINT16                          usFrmOutSegNum;
    VOS_UINT8                           ucFrmValidNum;
    VOS_UINT32                          ulFrmOutSpaceCnt;
    HDLC_FRM_BUFF_INFO_STRU            *pstFrmBuffInfo;
    HDLC_PARA_LINK_NODE_STRU           *pstOutputParaLink;
    HDLC_FRM_RPT_NODE_STRU             *pstFrmRptNodeStru;
    PPPC_DATA_LINK_NODE_STRU          **ppstInputLinkNode;
    PPPC_DATA_LINK_NODE_STRU          **ppstOutputLinkNode;
    VOS_UINT32                          ucRptSpaceIndex;
    VOS_UINT32                          ulOutputLinkIndex;
    VOS_UINT8                          *pucFrmOutAddr;
    VOS_UINT16                          usFrmOutLen;
    VOS_UINT16                          usDataLen;
    PPP_RLP_1X_TRANS_DATA_STRU          stRlpSdu;
    PPP_RLP_HRPD_TRANS_DATA_STRU        stHrpdSdu;
    CTTF_HRPD_PA_APPLICATION_TYPE_ENUM_UINT16 enAppType;
    VOS_UINT8                           ucPdnId = 0;
    IP_DATA_TYPE_ENUM_UINT8             enIpDataType;


    pstFrmBuffInfo     = HDLC_FRM_GET_BUF_INFO(usPppId);                   /* 根据usPppId找到对应的内存  */
    pstFrmRptNodeStru  = &(pstFrmBuffInfo->astRptNodeBuf[0]);              /* 封装上报空间首地址 */
    pstOutputParaLink  = &(pstFrmBuffInfo->astOutputParaLinkNodeBuf[0]);   /* 封装输出链表首地址 */
    ppstInputLinkNode  = &(pstBuildInfo->apstInputLinkNode[0]);            /* 封装输入链表节点对应零拷贝内存链表首地址 */
    ppstOutputLinkNode = &(pstBuildInfo->apstOutputLinkNode[0]);           /* 封装输出链表节点对应零拷贝内存链表首地址 */
    ulFrmOutSpaceCnt   = pstBuildInfo->ulOutputLinkNodeCnt;                /* 封装输出链表节点的个数 */

    /* 有效帧存放占用片段个数usFrmOutSegNum= hdlc_frm_status寄存器[31:16]位的值 */
    usFrmOutSegNum = (VOS_UINT16)TTF_Read32RegByBit(SOC_ARM_HDLC_FRM_STATUS_ADDR(HDLC_IP_BASE_ADDR), 16, 31);

    /* 有效帧个数usFrmValidNum= hdlc_frm_status寄存器[15:8]位的值 */
    ucFrmValidNum  = (VOS_UINT8)TTF_Read32RegByBit(SOC_ARM_HDLC_FRM_STATUS_ADDR(HDLC_IP_BASE_ADDR), 8, 15);

    /* 上报封装后数据可维可测:上报空间信息、输出链表内容 */
    PPPC_HDLC_HARD_MntnFrmTraceOutput(ucFrmValidNum, usFrmOutSegNum, pstFrmBuffInfo, pstBuildInfo);

    /* ucFrmValidNum肯定要小于等于使用的内存块数usFrmOutSegNum */
    if( ucFrmValidNum > usFrmOutSegNum )
    {
        PPP_HDLC_WARNING_LOG2("PPP_HDLC_HARD_FrmProcValidFram, ERROR, frm_valid_num = %d > usFrmOutSegNum = %d",
                      ucFrmValidNum, usFrmOutSegNum);
        PPPC_HDLC_HARD_CommReleaseLink(ppstOutputLinkNode, ulFrmOutSpaceCnt);
        return;
    }

    /* ucFrmValidNum应该与输入数据相同ulInputLinkNodeCnt，如果解封装出错可能会比后者小 */
    if( ucFrmValidNum > pstBuildInfo->ulInputLinkNodeCnt )
    {
        PPP_HDLC_WARNING_LOG2("PPP_HDLC_HARD_FrmProcValidFram, ERROR, frm_valid_num = %d > InputLinkNodeCnt = %d",
                      ucFrmValidNum, pstBuildInfo->ulInputLinkNodeCnt);
        PPPC_HDLC_HARD_CommReleaseLink(ppstOutputLinkNode, ulFrmOutSpaceCnt);
        return;
    }

    /* usFrmOutSegNum使用的内存块数肯定小于等于ulOutputLinkNodeCnt */
    if( usFrmOutSegNum  > ulFrmOutSpaceCnt )
    {
        PPP_HDLC_WARNING_LOG2("PPP_HDLC_HARD_FrmProcValidFram, ERROR, frm_out_seg_num = %d > OutputLinkNodeCnt = %d",
                      usFrmOutSegNum, ulFrmOutSpaceCnt);
        PPPC_HDLC_HARD_CommReleaseLink(ppstOutputLinkNode, ulFrmOutSpaceCnt);
        return;
    }

    ucRptSpaceIndex   = 0;
    ulOutputLinkIndex = 0;
    (VOS_VOID)PPPC_1XHrpdGetPdnId(usPppId, &ucPdnId);

    while( ucRptSpaceIndex < ucFrmValidNum )
    {
        pucFrmOutAddr    = pstFrmRptNodeStru[ucRptSpaceIndex].pucFrmOutOneAddr;
        usFrmOutLen      = pstFrmRptNodeStru[ucRptSpaceIndex].usFrmOutOneLen;

        if ( (0 == usFrmOutLen) || (HDLC_FRM_OUT_PER_MAX_CNT < usFrmOutLen) )
        {
            PPP_HDLC_WARNING_LOG1("PPP_HDLC_HARD_FrmProcValidFrames, ERROR, invalid usFrmOutOneLen %d\r\n",
                          usFrmOutLen);

            /* 释放申请的目的空间 */
            PPPC_HDLC_HARD_CommReleaseLink(ppstOutputLinkNode + ulOutputLinkIndex,
                                          ulFrmOutSpaceCnt - ulOutputLinkIndex);
            return;
        }

        pstMem          = ppstOutputLinkNode[ulOutputLinkIndex];
        enIpDataType    = ppstInputLinkNode[ucRptSpaceIndex]->enIpDataType;

        if( pucFrmOutAddr != pstMem->pstPduMem->pData )
        {
            PPP_HDLC_WARNING_LOG("PPP_HDLC_HARD_FrmProcValidFram, ERROR, SOC copy error!\r\n");

            /* 释放申请的目的空间 */
            PPPC_HDLC_HARD_CommReleaseLink(ppstOutputLinkNode + ulOutputLinkIndex,
                                          ulFrmOutSpaceCnt - ulOutputLinkIndex);
            return;
        }

        PPP_MemSet(&stRlpSdu, 0, sizeof(stRlpSdu));
        PPP_MemSet(&stHrpdSdu, 0, sizeof(stHrpdSdu));
        stRlpSdu.enIpDataType       = enIpDataType;
        stRlpSdu.ucTotalPppFrgmt    = 1;
        stHrpdSdu.enIpDataType      = enIpDataType;
        stHrpdSdu.ucTotalPppFrgmt   = 1;

        while( usFrmOutLen > 0 )
        {
            /* 从pstBuildInfo->apstOutputLinkNode取出头结点 pstMem */
            pstMem    = ppstOutputLinkNode[ulOutputLinkIndex];

            /* 单个输出链表结点所指目的空间的大小 */
            usDataLen = pstOutputParaLink[ulOutputLinkIndex].usDataLen;

            if( usFrmOutLen > usDataLen )
            {
                pstMem->pstPduMem->usUsed   = usDataLen;
                usFrmOutLen                 -= usDataLen;
                stRlpSdu.ucTotalPppFrgmt    = 2;
                stRlpSdu.ucCurrPppFrgmt     = 0;
                stHrpdSdu.ucTotalPppFrgmt   = 2;
                stHrpdSdu.ucCurrPppFrgmt    = 0;
            }
            else
            {
                pstMem->pstPduMem->usUsed   = usFrmOutLen;
                usFrmOutLen                 = 0;
                stRlpSdu.ucCurrPppFrgmt     = (2 == stRlpSdu.ucTotalPppFrgmt) ? (1) : (0);
                stHrpdSdu.ucCurrPppFrgmt    = (2 == stHrpdSdu.ucTotalPppFrgmt) ? (1) : (0);
            }

            #ifdef PPPC_HDLC_ST_TEST
            PPPC_STUB_ProcUlData(pstMem, usDataLen);
            #else

            if (PPPC_RAT_MODE_1X == pstBuildInfo->ucRatMode)
            {
                /* 上行数据报文发送到RLP */
                stRlpSdu.ucPdnId    = ucPdnId;
                stRlpSdu.ulSduLen   = pstMem->pstPduMem->usUsed;
                stRlpSdu.pstSdu     = pstMem->pstPduMem;

                CTTF_1X_RLP_ReverseLink_DataReq(&stRlpSdu);

                /* 上行IP包报文计数加1 */
                g_stPppcDataQueueStats.ul1xUlIPDataSndCnt++;
            }
            else
            {
                /* 获取stream2的应用绑定信息 */
                enAppType                   = PPPC_HRPD_GetAppType();

                stHrpdSdu.ucStreamNumber    = PPPC_HRPD_GetStreamNumber((VOS_UINT8)usPppId);
                stHrpdSdu.ucReservationLabel= PPPC_HRPD_PaAgentGetResvLabel(enAppType);
                stHrpdSdu.ulSduLen          = pstMem->pstPduMem->usUsed;
                stHrpdSdu.pstSdu            = pstMem->pstPduMem;
                stHrpdSdu.enStreamMode      = PPP_RLP_HRPD_STREAM_MODE_OCTET_BASED;

                CTTF_HRPD_RPA_AddToRlpTxQueue(&stHrpdSdu);

                /* 上行IP包报文计数加1 */
                g_stPppcDataQueueStats.ulHrpdUlIPDataSndCnt++;
            }
            /* 释放节点 */
            pstMem->pstPduMem   = VOS_NULL_PTR;
            TTF_NODE_MEM_FREE(PS_PID_PPP_HDLC, pstMem);
            #endif

            g_stPppcDataQueueStats.ulUplinkSndDataCnt++;

            /* 将发送完的数据包从apstOutputLinkNode中清空 */
            ppstOutputLinkNode[ulOutputLinkIndex] = VOS_NULL_PTR;

            ulOutputLinkIndex++;
        }

        ucRptSpaceIndex++;
    }

#ifndef PPPC_HDLC_ST_TEST
    if (PPPC_RAT_MODE_1X == pstBuildInfo->ucRatMode)
    {
        /* 触发RLP处理上行报文 */
        CTTF_1X_RLP_ReverseLink_TriggerDataProc();
    }
#endif

    /* 释放剩余未利用的目的空间 */
    PPPC_HDLC_HARD_CommReleaseLink(ppstOutputLinkNode + ulOutputLinkIndex,
                                  ulFrmOutSpaceCnt - ulOutputLinkIndex);

    return;
}

/*****************************************************************************
 函 数 名  : PPPC_HDLC_HARD_FrmWaitAndProc
 功能描述  : 等待封装完成，然后处理输出数据,释放多余的目的空间内存
 输入参数  : ulEnableInterrupt  -   中断是否使能
             usPppId    -   PPP实体ID
             pstLink    -   PPP链路信息
 输出参数  : pstBuildInfo   -   构造链表的结果信息，保存输入链表长度、节点个数、零拷贝内存指针
 返 回 值  :
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2012年4月20日
    作    者   : c00191211
    修改内容   : 新生成函数

*****************************************************************************/
VOS_VOID PPPC_HDLC_HARD_FrmWaitAndProc
(
    VOS_UINT32                           ulEnableInterrupt,
    PPP_ID                               usPppId,
    HDLC_PARA_LINK_BUILD_INFO_STRU      *pstBuildInfo
)
{
    VOS_UINT32                          ulFrmStatus;


    /* 使能中断，则等待中断辅程序释放信号量；否则轮询解封装状态寄存器 */
    ulFrmStatus = PPP_HDLC_HARD_FrmWaitResult(ulEnableInterrupt);

    if ( HDLC_FRM_ALL_PKT_DONE == ulFrmStatus )
    {
        /* 处理有效帧，并释放剩余内存 */
        PPPC_HDLC_HARD_FrmProcValidFrames(usPppId, pstBuildInfo);
    }
    else
    {
        /* 释放申请的目的空间 */
        PPPC_HDLC_HARD_CommReleaseLink(pstBuildInfo->apstOutputLinkNode, pstBuildInfo->ulOutputLinkNodeCnt);

        /* 打印异常日志，挂起PPP任务 */
        PPP_HDLC_HARD_FrmProcException(ulFrmStatus, ulEnableInterrupt);
    }

    g_stHdlcRegSaveInfo.ulHdlcFrmRawInt = 0xFFFFFFFFU;
    g_stHdlcRegSaveInfo.ulHdlcFrmStatus = 0xFFFFFFFFU;

    return;
}

/*****************************************************************************
 函 数 名  : PPPC_HDLC_HARD_FrmUpdateLink
 功能描述  : 申请一块内存后更新链表相关结构信息
 输入参数  : ulAllocMemCnt      - 本次申请的内存块个数
             aulAllocLen        - 记录本次申请的各个内存块的长度
             papstAllocedMem    - 记录本次申请的各个内存块控制结构指针
             pstBuildPara       -   构造链表所需的参数
 输出参数  : pstBuildInfo       -   构造链表的结果信息，保存输入链表长度、节点个数、零拷贝内存指针
 返 回 值  :
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2012年4月20日
    作    者   : c00191211
    修改内容   : 新生成函数

*****************************************************************************/
VOS_UINT32 PPPC_HDLC_HARD_FrmUpdateLink
(
    VOS_UINT32                      ulAllocMemCnt,
    VOS_UINT32 *                    aulAllocLen,
    PPPC_DATA_LINK_NODE_STRU      **ppstAllocedMem,
    HDLC_PARA_LINK_BUILD_PARA_STRU *pstBuildPara,
    HDLC_PARA_LINK_BUILD_INFO_STRU *pstBuildInfo
)
{
    VOS_UINT32                          ulMemLoop;
    VOS_UINT32                          ulNodeIndex;
    HDLC_PARA_LINK_NODE_STRU           *pstOutputParaNode;
    HDLC_FRM_BUFF_INFO_STRU            *pstFrmBuffInfo;


    /* 根据usPppId找到对应的内存  */
    pstFrmBuffInfo          = HDLC_FRM_GET_BUF_INFO(pstBuildPara->usPppId);

    if( (pstBuildInfo->ulOutputLinkNodeCnt + ulAllocMemCnt) > TTF_HDLC_FRM_OUTPUT_PARA_LINK_MAX_NUM )
    {
        g_PppHdlcHardStat.ulFrmOutputLinkFullCnt++;

        PPPC_HDLC_HARD_CommReleaseLink(ppstAllocedMem, ulAllocMemCnt);

        return VOS_ERR;
    }

    /* 更新目的空间数组 apstOutputLinkNode，用于释放目的空间 */
    VOS_MemCpy(&(pstBuildInfo->apstOutputLinkNode[pstBuildInfo->ulOutputLinkNodeCnt]),
               &(ppstAllocedMem[0]),
               ulAllocMemCnt * sizeof(PPPC_DATA_LINK_NODE_STRU *));

    /* 给封装输出参数链表结点的各个成员赋值 */
    for ( ulMemLoop = 0; ulMemLoop < ulAllocMemCnt; ulMemLoop++ )
    {
        ulNodeIndex = pstBuildInfo->ulOutputLinkNodeCnt;

        pstOutputParaNode = &(pstFrmBuffInfo->astOutputParaLinkNodeBuf[ulNodeIndex]);

        /* 更新上个输入参数链表结点的pstNextNode域 */
        if (0 != ulNodeIndex)
        {
            pstFrmBuffInfo->astOutputParaLinkNodeBuf[ulNodeIndex - 1].pstNextNode = pstOutputParaNode;
        }

        pstOutputParaNode->pucDataAddr = ppstAllocedMem[ulMemLoop]->pstPduMem->pData;
        pstOutputParaNode->usDataLen   = (VOS_UINT16)aulAllocLen[ulMemLoop];
        pstOutputParaNode->pstNextNode = VOS_NULL_PTR;

        pstBuildInfo->ulOutputLinkNodeCnt++;
        pstBuildInfo->ulOutputLinkTotalSize += aulAllocLen[ulMemLoop];
    }

    return VOS_OK;
}

/*****************************************************************************
 函 数 名  : PPPC_HDLC_HARD_OutputMemAlloc
 功能描述  : 封装输出目的空间申请
 输入参数  : usLen          -   待申请的内存长度
             pstBuildPara   -   构造链表所需的参数
 输出参数  : pstBuildInfo   -   构造链表的结果信息，保存输入链表长度、节点个数、零拷贝内存指针
 返 回 值  : VOS_OK/VOS_ERR
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2012年4月20日
    作    者   : c00191211
    修改内容   : 新生成函数

*****************************************************************************/
VOS_UINT32 PPPC_HDLC_HARD_FrmOutputMemAlloc
(
    VOS_UINT16                           usLen,
    HDLC_PARA_LINK_BUILD_PARA_STRU      *pstBuildPara,
    HDLC_PARA_LINK_BUILD_INFO_STRU      *pstBuildInfo
)
{
    VOS_UINT16                  usFrmedMaxLen;                                  /* 封装后的可能的最大长度 */
    VOS_UINT16                  usAllocLen;
    VOS_UINT32                  ulAllocLoop;
    VOS_UINT32                  ulLoopCnt;
    VOS_UINT32                  ulAllocMemCnt;                                  /* 本次申请的内存块数 */
    VOS_UINT32                  aulAllocLen[HDLC_OUTPUT_PARA_LINK_MAX_SIZE] = {0};    /* 记录本次申请的各个内存块长度 */
    PPPC_DATA_LINK_NODE_STRU   *apstAllocedMem[HDLC_OUTPUT_PARA_LINK_MAX_SIZE]; /* 记录本次申请的各个内存块指针 */
    PPPC_DATA_LINK_NODE_STRU   *pstMem;

    PS_MEM_SET(apstAllocedMem, 0, HDLC_OUTPUT_PARA_LINK_MAX_SIZE * sizeof(PPPC_DATA_LINK_NODE_STRU *));

    /* 封装后可能的最大数据长度(2*原始数据长度+13B) */
    usFrmedMaxLen = (VOS_UINT16)HDLC_FRM_GET_MAX_FRAMED_LEN(usLen);
    ulAllocMemCnt = 0;
    ulLoopCnt     = TTF_CEIL(usFrmedMaxLen, PPP_ZC_MAX_DATA_LEN);

    for ( ulAllocLoop = 0 ; ulAllocLoop < ulLoopCnt; ulAllocLoop++ )
    {
        if (ulAllocLoop != (ulLoopCnt - 1) )
        {
            usAllocLen = PPP_ZC_MAX_DATA_LEN;
        }
        else
        {
            usAllocLen = (VOS_UINT16)(usFrmedMaxLen - ulAllocLoop*PPP_ZC_MAX_DATA_LEN);
        }

        pstMem = PPP_MemAlloc(usAllocLen, TTF_MEM_POOL_ID_UL_DATA);

        if (VOS_NULL_PTR == pstMem)
        {
            PPP_HDLC_WARNING_LOG1("alloc memory fail. allocMemlen:%d\n", usAllocLen);
            break;
        }

        ulAllocMemCnt++;
        aulAllocLen[ulAllocLoop]    = usAllocLen;
        apstAllocedMem[ulAllocLoop] = pstMem;
    }

    /* 如果有申请内存失败的情况，则释放本次已经申请的内存 */
    if (ulLoopCnt > ulAllocMemCnt)
    {
        PPPC_HDLC_HARD_CommReleaseLink(&(apstAllocedMem[0]), ulAllocMemCnt);
        return VOS_ERR;
    }

    return PPPC_HDLC_HARD_FrmUpdateLink(ulAllocMemCnt,
                                       &(aulAllocLen[0]), &(apstAllocedMem[0]),
                                       pstBuildPara, pstBuildInfo);
}

/*****************************************************************************
 函 数 名  : PPPC_HDLC_HARD_MntnFrmTraceInput
 功能描述  : 勾取封装输入参数链表和数据
 输入参数  : pstFrmBuffInfo -   封装使用的内存
             pstBuildInfo   -   存放输入数据
 输出参数  : 无
 返 回 值  : 无
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2012年4月10日
    作    者   : l00164359
    修改内容   : 新生成函数

*****************************************************************************/
VOS_VOID PPPC_HDLC_HARD_MntnFrmTraceInput
(
    HDLC_FRM_BUFF_INFO_STRU         *pstFrmBuffInfo,
    HDLC_PARA_LINK_BUILD_INFO_STRU  *pstBuildInfo
)
{
    VOS_UINT32                          ulNodeLoop;
    HDLC_PARA_LINK_NODE_STRU           *pstParaNode;


    if ((g_stHdlcConfigInfo.ulHdlcMntnTraceCfg & PPP_HDLC_MNTN_TRACE_PARA) != 0)
    {
        PPP_HDLC_HARD_MntnTraceInputParaLink(ID_HDLC_MNTN_FRM_INPUT_PARA,
                                             pstBuildInfo->ulInputLinkNodeCnt,
                                             pstBuildInfo->ulInputLinkTotalSize,
                                             &(pstFrmBuffInfo->astInputParaLinkNodeBuf[0]));
    }

    if ((g_stHdlcConfigInfo.ulHdlcMntnTraceCfg & PPP_HDLC_MNTN_TRACE_DATA) != 0)
    {
        /* 记录并上报参数链表所有节点的数据内容，每个节点是一个IP包 */
        for ( ulNodeLoop = 0; ulNodeLoop < pstBuildInfo->ulInputLinkNodeCnt; ulNodeLoop++ )
        {
            pstParaNode = &(pstFrmBuffInfo->astInputParaLinkNodeBuf[ulNodeLoop]);

            PPP_HDLC_HARD_MntnTraceSingleData(pstParaNode->usDataLen, pstParaNode->pucDataAddr,
                                              ID_HDLC_MNTN_FRM_INPUT_DATA, ulNodeLoop);
        }
    }

    return;
}

/*****************************************************************************
 函 数 名  : PPPC_HDLC_HARD_FrmBuildParaLink
 功能描述  : 检查构造输入输出参数链表相关参数是否合法
 输入参数  : pstMem     -   待封装数据包
             ulDataLen  -   待封装数据包长度
             ucDataType -   待封装数据包类型
             usProtocol -   待封装数据包协议类型
 输出参数  : 无
 返 回 值  : PPP_HDLC_PARA_CHECK_RESULT_ENUM_UINT32
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2012年4月20日
    作    者   : c00191211
    修改内容   : 新生成函数

*****************************************************************************/
PPP_HDLC_PARA_CHECK_RESULT_ENUM_UINT32 PPPC_HDLC_HARD_FrmCheckPara
(
    PPPC_DATA_LINK_NODE_STRU           *pstMem,
    VOS_UINT32                          ulDataLen,
    VOS_UINT16                          usProtocol
)
{
#if 0
    PPP_DATA_TYPE_ENUM_UINT8            ucCurrDataType;
    VOS_UINT32                          ulRlst;
    VOS_UINT16                          usCurrProtocol;
#endif

    /* 待封装数据包长度异常 */
    if ( (0 == ulDataLen) || (HDLC_FRM_IN_PER_MAX_CNT < ulDataLen) )
    {
        PPP_HDLC_WARNING_LOG1("PPP_HDLC_HARD_FrmCheckPara,IP mode framer data len wrong %d\r\n", ulDataLen);

        return PPP_HDLC_PARA_CHECK_FAIL_DISCARD;
    }

#if 0
    /* 如果不是PPP模式 */
    if( PPP_PUSH_RAW_DATA_TYPE != ucCurrDataType )
    {
        return PPP_HDLC_PARA_CHECK_PASS;
    }

    ulRlst  = PPP_HDLC_HARD_FrmGetProtocol(pstMem, &usCurrProtocol);

    if( VOS_OK != ulRlst )
    {
        PPP_HDLC_WARNING_LOG("PPP_HDLC_HARD_FrmCheckPara, Warning, PPP mode get framer data protocol error\r\n");
        return PPP_HDLC_PARA_CHECK_FAIL_DISCARD;
    }

    /* 保证一次链表配置过程中封装协议值一致 */
    if( usProtocol != usCurrProtocol )
    {
        return PPP_HDLC_PARA_CHECK_FAIL_KEEP;
    }
#endif
    return PPP_HDLC_PARA_CHECK_PASS;
}

/*****************************************************************************
 函 数 名  : PPPC_HDLC_HARD_FrmBuildParaLink
 功能描述  : 构造输入输出参数链表，并上报链表内存可维可测
 输入参数  : pstBuildPara   -   构造链表所需的参数
 输出参数  : pstBuildInfo   -   构造链表的结果信息，保存输入链表长度、节点个数、零拷贝内存指针
 返 回 值  : VOS_OK/VOS_ERR
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2012年4月20日
    作    者   : c00191211
    修改内容   : 新生成函数

*****************************************************************************/
VOS_UINT32 PPPC_HDLC_HARD_FrmBuildParaLink
(
    HDLC_PARA_LINK_BUILD_PARA_STRU         *pstBuildPara,
    HDLC_PARA_LINK_BUILD_INFO_STRU         *pstBuildInfo
)
{
    PPPC_DATA_LINK_NODE_STRU               *pstMem;
    VOS_UINT32                              ulLoop;
    VOS_UINT16                              usUnFrmLen;
    VOS_UINT32                              ulAllocResult;
    HDLC_PARA_LINK_NODE_STRU               *pstParaNode;
    VOS_UINT32                              ulNodeIndex;
    PPP_HDLC_PARA_CHECK_RESULT_ENUM_UINT32  enCheckResult;
    VOS_UINT32                              ulAllocMemFail;
    HDLC_FRM_BUFF_INFO_STRU                *pstFrmBuffInfo;
    VOS_UINT32                              ulRemainCnt;


    VOS_MemSet(pstBuildInfo, 0, sizeof(HDLC_PARA_LINK_BUILD_INFO_STRU));

    /* 根据usPppId找到对应的内存  */
    pstFrmBuffInfo = HDLC_FRM_GET_BUF_INFO(pstBuildPara->usPppId);
    ulAllocMemFail = VOS_FALSE;

    for(ulLoop = 0; ulLoop < 1 /*TTF_HDLC_FRM_INPUT_PARA_LINK_MAX_NUM*/; ulLoop++)
    {
        pstMem = (PPPC_DATA_LINK_NODE_STRU *)TTF_LinkPeekHead(PS_PID_PPP_HDLC,
                        pstBuildPara->pstUlDataQ);

        if( VOS_NULL_PTR == pstMem )
        {
            break;
        }

        usUnFrmLen    = TTF_MemGetLen(PS_PID_PPP_HDLC, pstMem->pstPduMem);
        enCheckResult = PPPC_HDLC_HARD_FrmCheckPara(pstMem, usUnFrmLen,
                                                   pstBuildPara->usProtocol);

        if( PPP_HDLC_PARA_CHECK_FAIL_DISCARD == enCheckResult )
        {
            pstMem = (PPPC_DATA_LINK_NODE_STRU *)TTF_LinkSafeRemoveHead(
                    PS_PID_PPP_HDLC, pstBuildPara->pstUlDataQ, &ulRemainCnt);
            /* 释放节点和TTFMemory */
            PPP_MemFree(pstMem);
            pstMem = VOS_NULL_PTR;

            pstBuildInfo->ulDealCnt++;

            g_PppHdlcHardStat.ulFrmInputDiscardCnt++;
            continue;
        }

        if( PPP_HDLC_PARA_CHECK_FAIL_KEEP == enCheckResult )
        {
            break;
        }

        /* 一次配链表过程中待封装数据包总长不能超过15KB */
        if( pstBuildInfo->ulInputLinkTotalSize + usUnFrmLen > TTF_HDLC_FRM_INPUT_PARA_LINK_MAX_SIZE )
        {
            break;
        }

        /* 申请封装目的空间 */
        ulAllocResult = PPPC_HDLC_HARD_FrmOutputMemAlloc(usUnFrmLen, pstBuildPara, pstBuildInfo);

        if( VOS_OK != ulAllocResult )
        {
            ulAllocMemFail = VOS_TRUE;

            g_PppHdlcHardStat.ulFrmAllocOutputMemFailCnt++;
            break;
        }

        /* 从PPP队列取出头结点，并插入输入队列 pstBuildInfo->apstInputLinkNode */
        pstMem = (PPPC_DATA_LINK_NODE_STRU *)TTF_LinkSafeRemoveHead(
                    PS_PID_PPP_HDLC, pstBuildPara->pstUlDataQ, &ulRemainCnt);

        /* 获取当前要添加节点的下标 */
        ulNodeIndex = pstBuildInfo->ulInputLinkNodeCnt;

        /* 本次要构造的参数节点 */
        pstParaNode = &(pstFrmBuffInfo->astInputParaLinkNodeBuf[ulNodeIndex]);

        /* 填写输入参数链表结点相关域 */
        if( 0 != ulNodeIndex )
        {
            pstFrmBuffInfo->astInputParaLinkNodeBuf[ulNodeIndex - 1].pstNextNode = pstParaNode;
        }

        pstParaNode->pucDataAddr = pstMem->pstPduMem->pData;
        pstParaNode->usDataLen   = usUnFrmLen;
        pstParaNode->pstNextNode = VOS_NULL_PTR;

        pstBuildInfo->apstInputLinkNode[ulNodeIndex] = pstMem;
        pstBuildInfo->ulInputLinkTotalSize          += (VOS_UINT32)usUnFrmLen;
        pstBuildInfo->ucRatMode                      = pstMem->enRatMode;
        pstBuildInfo->ulInputLinkNodeCnt++;
        pstBuildInfo->ulDealCnt++;
    }

    if (0 == pstBuildInfo->ulInputLinkNodeCnt)
    {
        if (VOS_TRUE == ulAllocMemFail)
        {
            /* 等待一段时间后，重新尝试申请内存再封装 */
            PPP_HDLC_HARD_FrmStartTimer(pstBuildPara);

            g_PppHdlcHardStat.ulFrmAllocFirstMemFailCnt++;
        }

        return VOS_ERR;
    }

    /* 报输入输出参数链表内容可维可测 */
    PPPC_HDLC_HARD_MntnFrmTraceInput(pstFrmBuffInfo, pstBuildInfo);

    return VOS_OK;
}

/*****************************************************************************
 函 数 名  : PPPC_HDLC_HARD_FrmPacket
 功能描述  : IP模式下行封装处理流程
 输入参数  : usPppId        -   PPP实体ID
             usProtocol     -   待封装协议
             pstLink        -   PPP链路信息
             pstDataQ       -   PPP数据队列
 输出参数  : *pulDealCurCnt  -  指向当前处理的PPP队列中的结点个数
 返 回 值  : 无
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2012年4月20日
    作    者   : c00191211
    修改内容   : 新生成函数

*****************************************************************************/
VOS_UINT32 PPPC_HDLC_HARD_FrmPacket
(
    PPP_ID                              usPppId,
    VOS_UINT16                          usProtocol,
    TTF_LINK_ST                        *pstUlDataQ,
    VOS_UINT32                         *pulDealCurCnt
)
{
    VOS_UINT32                          ulEnableInterrupt;
    HDLC_PARA_LINK_BUILD_INFO_STRU      stBuildInfo;
    HDLC_PARA_LINK_BUILD_PARA_STRU      stBuildPara;
    VOS_UINT32                          ulBuildResult;
    HDLC_FRM_BUFF_INFO_STRU            *pstFrmBuffInfo;


    stBuildPara.ucDataType = PPP_PULL_PACKET_TYPE;
    stBuildPara.usProtocol = usProtocol;
    stBuildPara.usPppId    = usPppId;
    stBuildPara.pstUlDataQ = pstUlDataQ;

    /* 根据usPppId找到对应的内存 */
    pstFrmBuffInfo = HDLC_FRM_GET_BUF_INFO(usPppId);

    /* 构造输入输出参数链表，并上报链表内存可维可测 */
    ulBuildResult  = PPPC_HDLC_HARD_FrmBuildParaLink(&stBuildPara, &stBuildInfo);

    *pulDealCurCnt = stBuildInfo.ulDealCnt;

    if (VOS_OK != ulBuildResult)
    {
        PPP_HDLC_WARNING_LOG("PPP_HDLC_HARD_FrmPacket, WARNING, BuildParaLink Fail.\r\n");
        return ulBuildResult;
    }

    g_PppHdlcHardStat.ulFrmMaxInputCntOnce   = TTF_MAX(g_PppHdlcHardStat.ulFrmMaxInputCntOnce, stBuildInfo.ulInputLinkNodeCnt);
    g_PppHdlcHardStat.ulFrmMaxInputSizeOnce  = TTF_MAX(g_PppHdlcHardStat.ulFrmMaxInputSizeOnce, stBuildInfo.ulInputLinkTotalSize);
    g_PppHdlcHardStat.ulFrmMaxOutputCntOnce  = TTF_MAX(g_PppHdlcHardStat.ulFrmMaxOutputCntOnce, stBuildInfo.ulOutputLinkNodeCnt);
    g_PppHdlcHardStat.ulFrmMaxOutputSizeOnce = TTF_MAX(g_PppHdlcHardStat.ulFrmMaxOutputSizeOnce, stBuildInfo.ulOutputLinkTotalSize);

    /* 配置封装、解封装通用寄存器 */
    PPP_HDLC_HARD_CommCfgReg();

    /* 配置内存相关寄存器 */
    PPPC_HDLC_HARD_FrmCfgBufReg(pstFrmBuffInfo);

    /* 配置封装相关寄存器 */
    PPPC_HDLC_HARD_FrmCfgReg(usPppId, usProtocol);

    /* 配置使能寄存器，并上报使能前寄存器可维可测 */
    ulEnableInterrupt = PPP_HDLC_HARD_FrmCfgEnReg(stBuildInfo.ulInputLinkTotalSize);

    /* 等待封装完成，然后处理输出数据,释放多余的目的空间内存 */
    PPPC_HDLC_HARD_FrmWaitAndProc(ulEnableInterrupt, usPppId, &stBuildInfo);

    /* 释放pstBuildInfo->apstInputLinkNode中的结点内存 */
    PPPC_HDLC_HARD_CommReleaseLink(stBuildInfo.apstInputLinkNode, stBuildInfo.ulInputLinkNodeCnt);

    return VOS_OK;
}

/*****************************************************************************
 函 数 名  : PPPC_HDLC_HARD_SendAsFrmPacketMsg
 功能描述  : 消息发送函数
 输入参数  : usPppId        -- PPP实体ID
             usProtocol     -- 待封装协议值
             pstMem         -- 待封装数据包
 输出参数  : 无
 返 回 值  : 无
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2012年4月10日
    作    者   : l00164359
    修改内容   : 新生成函数

*****************************************************************************/
VOS_UINT32 PPPC_HDLC_HARD_SendAsFrmPacketMsg
(
    VOS_UINT16                          usPppId,
    VOS_UINT16                          usProtocol,
    TTF_MEM_ST                         *pstMem
)
{
    HDLC_PROC_AS_FRM_PACKET_IND_MSG_STRU    *pstMsg;
    VOS_UINT32                               ulLength;


    ulLength    = sizeof(HDLC_PROC_AS_FRM_PACKET_IND_MSG_STRU) - VOS_MSG_HEAD_LENGTH;
    pstMsg      = (HDLC_PROC_AS_FRM_PACKET_IND_MSG_STRU *)PS_ALLOC_MSG(PS_PID_PPP_HDLC, ulLength);

    if (VOS_NULL_PTR == pstMsg)
    {
        /*打印出错信息---申请消息包失败:*/
        PPP_HDLC_WARNING_LOG("PPP_HDLC_HARD_SendMsg, ERROR: PS_ALLOC_MSG Failed!\r\n");
        return VOS_ERR;
    }

    /*填写消息头:*/
    pstMsg->MsgHeader.ulSenderCpuId   = VOS_LOCAL_CPUID;
    pstMsg->MsgHeader.ulSenderPid     = PS_PID_PPP_HDLC;
    pstMsg->MsgHeader.ulReceiverCpuId = VOS_LOCAL_CPUID;
    pstMsg->MsgHeader.ulReceiverPid   = PS_PID_PPP_HDLC;
    pstMsg->MsgHeader.ulLength        = ulLength;

    pstMsg->MsgHeader.ulMsgName       = PPPC_HDLC_PROC_AS_FRM_PACKET_IND;
    /*填写消息体:*/
    pstMsg->usPppId                   = usPppId;
    pstMsg->usProtocol                = usProtocol;
    pstMsg->pstMem                    = pstMem;

    /*发送该消息*/
    if (VOS_OK != PS_SEND_MSG(PS_PID_PPP_HDLC, pstMsg))
    {
        /*打印警告信息---发送消息失败:*/
        PPP_HDLC_WARNING_LOG("PPP_HDLC_HARD_SendAsFrmPacketMsg, ERROR : PS_SEND_MSG Failed!");
        TTF_MemFree(PS_PID_PPP_HDLC, pstMem);
        return VOS_ERR;
    }

    return VOS_OK;
}

/*****************************************************************************
 函 数 名  : PPPC_HDLC_HARD_ProcAsFrmPacket
 功能描述  : 当做下行封装处理
 输入参数  : usPppId        -- PPP实体ID
             usProtocol     -- 待封装协议值
             pstMem         -- 待封装数据包
 输出参数  : 无
 返 回 值  : 无
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2012年4月10日
    作    者   : l00164359
    修改内容   : 新生成函数

*****************************************************************************/
VOS_VOID PPPC_HDLC_HARD_ProcAsFrmPacket
(
    VOS_UINT16       usPppId,
    VOS_UINT16       usProtocol,
    TTF_MEM_ST      *pstMem
)
{
    VOS_UINT32                          ulDealCurCnt;
    TTF_LINK_ST                         stDataQ;
    VOS_UINT32                          ulDealResult;
    PPPC_DATA_LINK_NODE_STRU           *pstNode = VOS_NULL_PTR;
    VOS_UINT32                          ulNonEmptyEvent;   /* 记录队列是否发生了由空到非空的转变 */
    VOS_UINT32                          ulRet;

    ulDealCurCnt = 0;

    /* 初始化队列stDataQ, 并将 pstMem 入队 */
    PS_MEM_SET(&stDataQ, 0, sizeof(stDataQ));

    TTF_LinkInit(PS_PID_PPP_HDLC, &stDataQ);

    pstNode = (PPPC_DATA_LINK_NODE_STRU *)TTF_NODE_MEM_ALLOC(PS_PID_PPP_HDLC, sizeof(PPPC_DATA_LINK_NODE_STRU));
    if (VOS_NULL_PTR == pstNode)
    {
        TTF_MemFree(PS_PID_PPP_HDLC, pstMem);
        return;
    }

    PPP_MemSet(pstNode, 0, sizeof(PPPC_DATA_LINK_NODE_STRU));
    pstNode->pstPduMem    = pstMem;
    pstNode->ulTimeStamp  = mdrv_timer_get_normal_timestamp();
    TTF_NodeInit(&(pstNode->stNode));

    /* 将数据结点插入队列尾部 */
    ulRet = TTF_LinkSafeInsertTail(PS_PID_PPP_HDLC, &stDataQ,
            &(pstNode->stNode), &ulNonEmptyEvent);
    if (VOS_OK != ulRet)
    {
        TTF_MemFree(PS_PID_PPP_HDLC, pstMem);
        /* 释放节点 */
        TTF_NODE_MEM_FREE(PS_PID_PPP_HDLC, pstNode);
        return;
    }

    /* 直接将该数据包封装后发送给PC */
    ulDealResult = PPPC_HDLC_HARD_FrmPacket(usPppId, usProtocol, &stDataQ, &ulDealCurCnt);

    if ((VOS_OK != ulDealResult) || (1 != ulDealCurCnt))
    {
        PPP_HDLC_WARNING_LOG2("PPP_HDLC_HARD_MakeFrmPacket, ERROR, ulDealResult %d ulDealCurCnt %d!\r\n",
                      ulDealResult, ulDealCurCnt);
#if 0
        /* 说明因某种错误导致数据没有从队列中移出，需要释放 */
        if (0 < PPP_ZC_GET_QUEUE_LEN(&stDataQ))
        {
            PPP_MemFree(pstMem);
        }
#endif
        return;
    }

    g_PppHdlcHardStat.ulFrmIpDataProcCnt++;

    return;
}

/*****************************************************************************
 函 数 名  : PPPC_HDLC_HARD_ProcProtocolPacket
 功能描述  : 硬件封装PPP协议栈输出的协议包
 输入参数  : pstLink    -   PPP链路信息
             pstMbuf    -   PPP协议栈输出的协议包
             ulPri      -   优先级,默认填0
             usProto    -   数据包对应的协议
 输出参数  : 无
 返 回 值  : 无
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2012年4月10日
    作    者   : l00164359
    修改内容   : 新生成函数

*****************************************************************************/
VOS_UINT32 PPPC_HDLC_HARD_ProcProtocolPacket
(
    VOS_UINT32                          ulPppId,
    PMBUF_S                            *pstMbuf,
    VOS_INT32                           ulPri,
    VOS_UINT16                          usProtocol
)
{
    TTF_MEM_ST                         *pstTtfMem;
    VOS_UINT32                          ulFrmResult;
    VOS_UINT32                          ulDefResult;


    pstTtfMem = PPPC_AdapterMBuftoTtfMemory(pstMbuf, TTF_MEM_POOL_ID_UL_DATA, 0, pstMbuf->ulTotalDataLength);

    PMBUF_Destroy(pstMbuf);

    if (VOS_NULL_PTR == pstTtfMem)
    {
        PPP_HDLC_WARNING_LOG("PPP_HDLC_HARD_ProcProtocolPacket, WARNING, pstMem is NULL!\r\n");
        return VOS_ERR;
    }

    /* PPP协议栈回复的协商包需要封装后发给PC，确认此时是否封装与解封装都已经完成 */
    ulFrmResult     = PPP_HDLC_HARD_FrmIsEnabled();
    ulDefResult     = PPP_HDLC_HARD_DefIsEnabled();

    /* 此函数在上行解出协商包时，PPP协议栈产生应答，这个时候封装不应该使能 */
    if( (VOS_TRUE == ulFrmResult) || (VOS_TRUE == ulDefResult) )
    {
        PPP_HDLC_WARNING_LOG2("PPP_HDLC_HARD_ProcProtocolPacket, WARNING, ulFrmResult %d, ulDefResult %d!\r\n",
                      ulFrmResult, ulDefResult);
        PPPC_HDLC_HARD_SendAsFrmPacketMsg((VOS_UINT16)ulPppId, usProtocol, pstTtfMem);

        return VOS_OK;
    }

    /* 下次PPP任务调度的时候再封装此协商，那时封装与解封装都未使能 */
    PPPC_HDLC_HARD_ProcAsFrmPacket((VOS_UINT16)ulPppId, usProtocol, pstTtfMem);

    return VOS_OK;
}


#else

extern PPP_DATA_Q_CTRL_ST     g_PppDataQCtrl;

/*****************************************************************************
 函 数 名  : PPP_HDLC_HARD_InitBuf
 功能描述  : 初始化HDLC需要的内存
 输入参数  : 无
 输出参数  : 无
 返 回 值  : 无
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2012年4月10日
    作    者   : l00164359
    修改内容   : 新生成函数

*****************************************************************************/
VOS_UINT32 PPP_HDLC_HARD_InitBuf(VOS_VOID)
{
    /* 计算内存长度，实际使用长度为0x6140，申请按照0x8000(32K) */
    g_ulPppTotalBufLen = PAGE_ALIGN(TTF_HDLC_MASTER_LINK_TOTAL_LEN + PAGE_SIZE);

    /* 调用系统接口dma_alloc_coherent申请uncache内存 */
    g_ulPppVirtAddr = (VOS_UINT32)VOS_UnCacheMemAlloc(g_ulPppTotalBufLen, (VOS_UINT_PTR *)&g_ulPppPhyAddr);
    if (!g_ulPppVirtAddr)
    {
        PPP_HDLC_ERROR_LOG("PPP_HDLC_HARD_InitBuf, ERROR, VOS_UnCacheMemAlloc Fail\r\n");
        return VOS_ERR;
    }

    memset((void *)g_ulPppVirtAddr, 0, g_ulPppTotalBufLen);

    /* 根据TtfMemoryMap.h初始化HDLC所需内存 */
    g_pstHdlcDefBufInfo = (HDLC_DEF_BUFF_INFO_STRU *)g_ulPppVirtAddr;
    g_pstHdlcFrmBufInfo = (HDLC_FRM_BUFF_INFO_STRU *)(g_ulPppVirtAddr + sizeof(HDLC_DEF_BUFF_INFO_STRU));

    /*lint -e506 -e774*/
    /* TTF_HDLC_MASTER_DEF_BUF_LEN必须与结构HDLC_DEF_BUFF_INFO_STRU的大小一致 */
    if (TTF_HDLC_MASTER_DEF_BUF_LEN != sizeof(HDLC_DEF_BUFF_INFO_STRU))
    {
        PPP_HDLC_ERROR_LOG2("PPP_HDLC_HARD_InitBuf, ERROR, TTF_HDLC_MASTER_DEF_BUF_LEN %d sizeof(HDLC_DEF_BUFF_INFO_STRU) %d\r\n",
                      TTF_HDLC_MASTER_DEF_BUF_LEN, sizeof(HDLC_DEF_BUFF_INFO_STRU));
        return VOS_ERR;
    }

    /* TTF_HDLC_MASTER_FRM_BUF_LEN收必须与结构HDLC_FRM_BUFF_INFO_STRU的大小一致 */
    if (TTF_HDLC_MASTER_FRM_BUF_LEN != sizeof(HDLC_FRM_BUFF_INFO_STRU))
    {
        PPP_HDLC_ERROR_LOG2("PPP_HDLC_HARD_InitBuf, ERROR, TTF_HDLC_MASTER_FRM_BUF_LEN %d sizeof(HDLC_FRM_BUFF_INFO_STRU) %d\r\n",
                      TTF_HDLC_MASTER_FRM_BUF_LEN, sizeof(HDLC_FRM_BUFF_INFO_STRU));
        return VOS_ERR;
    }
    /*lint +e506 +e774*/

    return VOS_OK;
}

/*****************************************************************************
 函 数 名  : PPP_HDLC_HARD_MntnDefTraceInput
 功能描述  : 勾取解封装输入参数链表和数据
 输入参数  : pstFrmBuffInfo -   封装使用的内存
             pstBuildInfo   -   存放输入数据
 输出参数  : 无
 返 回 值  : 无
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2012年4月10日
    作    者   : l00164359
    修改内容   : 新生成函数

*****************************************************************************/
VOS_VOID PPP_HDLC_HARD_MntnDefTraceInput
(
    HDLC_DEF_BUFF_INFO_STRU         *pstDefBuffInfo,
    HDLC_PARA_LINK_BUILD_INFO_STRU  *pstBuildInfo
)
{
    VOS_UINT32                          ulNodeLoop;
    HDLC_PARA_LINK_NODE_STRU           *pstParaNode;


    if ((g_stHdlcConfigInfo.ulHdlcMntnTraceCfg & PPP_HDLC_MNTN_TRACE_PARA) != 0)
    {
        PPP_HDLC_HARD_MntnTraceInputParaLink(ID_HDLC_MNTN_DEF_INPUT_PARA,
                                             pstBuildInfo->ulInputLinkNodeCnt,
                                             pstBuildInfo->ulInputLinkTotalSize,
                                             &(pstDefBuffInfo->astInputParaLinkNodeBuf[0]));
    }

    if ((g_stHdlcConfigInfo.ulHdlcMntnTraceCfg & PPP_HDLC_MNTN_TRACE_DATA) != 0)
    {
        /* 记录并上报参数链表所有节点的数据内容，每个节点是一个IP包 */
        for ( ulNodeLoop = 0; ulNodeLoop < pstBuildInfo->ulInputLinkNodeCnt; ulNodeLoop++ )
        {
            pstParaNode = &(pstDefBuffInfo->astInputParaLinkNodeBuf[ulNodeLoop]);

            PPP_HDLC_HARD_MntnTraceSingleData(pstParaNode->usDataLen, (VOS_UINT8*)PPP_PHY_TO_VIRT((VOS_UINT32)(pstParaNode->pucDataAddr)),
                                              ID_HDLC_MNTN_DEF_INPUT_DATA, ulNodeLoop);

            /* 需要将数据写回DDR，HDLC从DDR中读数据 */
            PPP_HDLC_CACHE_FLUSH((VOS_UINT8*)PPP_PHY_TO_VIRT((VOS_UINT32)(pstParaNode->pucDataAddr)), pstParaNode->usDataLen);
        }
    }

    return;
}

/*****************************************************************************
 函 数 名  : PPP_HDLC_HARD_MntnDefTraceOutput
 功能描述  : 勾取解封装输出数据
 输入参数  : pstBuildInfo    -   存放输入数据
             usValidFrameNum -   有效帧个数
 输出参数  : 无
 返 回 值  : 无
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2012年4月10日
    作    者   : l00164359
    修改内容   : 新生成函数

*****************************************************************************/
VOS_VOID PPP_HDLC_HARD_MntnDefTraceOutput
(
    VOS_UINT16                          usValidFrameNum,
    HDLC_DEF_BUFF_INFO_STRU            *pstDefBuffInfo
)
{
    HDLC_MNTN_DEF_OUTPUT_PARA_STRU     *pstOutputPara;
    VOS_UINT32                          ulDataLen;
    VOS_UINT32                          ulNodeLoop;
    HDLC_DEF_RPT_NODE_STRU             *pstRptNode;
    VOS_UINT16                          usMaxFrameNum;


    /* 解封装上报空间可维可测 */
    if ((g_stHdlcConfigInfo.ulHdlcMntnTraceCfg & PPP_HDLC_MNTN_TRACE_PARA) != 0)
    {
        usMaxFrameNum = (HDLC_MNTN_ALLOC_MEM_MAX_SIZE - sizeof(HDLC_MNTN_DEF_OUTPUT_PARA_STRU)) /
                         sizeof(HDLC_DEF_RPT_NODE_STRU);
        usMaxFrameNum = TTF_MIN(usMaxFrameNum, usValidFrameNum);

        ulDataLen     = sizeof(HDLC_MNTN_DEF_OUTPUT_PARA_STRU) + usMaxFrameNum * sizeof(HDLC_DEF_RPT_NODE_STRU);
        pstOutputPara = (HDLC_MNTN_DEF_OUTPUT_PARA_STRU *)PS_MEM_ALLOC(PS_PID_PPP_HDLC, ulDataLen);

        if (VOS_NULL_PTR == pstOutputPara)
        {
            PPP_HDLC_NORMAL_LOG1("PPP_HDLC_HARD_MntnDefTraceOutput, NORMAL, Alloc mem failed ulDataLen %!\r\n", ulDataLen);
            return;
        }

        pstOutputPara->usDefValidNum = usValidFrameNum;
        pstOutputPara->usTraceNum    = usMaxFrameNum;

        VOS_MemCpy((VOS_UINT8 *)(pstOutputPara + 1),
                   (VOS_UINT8 *)(&(pstDefBuffInfo->astRptNodeBuf[0])),
                   usMaxFrameNum * sizeof(HDLC_DEF_RPT_NODE_STRU));

        PPP_HDLC_HARD_MntnTraceMsg((HDLC_MNTN_TRACE_HEAD_STRU *)pstOutputPara,
                                   ID_HDLC_MNTN_DEF_OUTPUT_PARA, ulDataLen);

        PS_MEM_FREE(PS_PID_PPP_HDLC, pstOutputPara);
    }

    /* 解封装目的空间中每个有效帧可维可测 */
    if ((g_stHdlcConfigInfo.ulHdlcMntnTraceCfg & PPP_HDLC_MNTN_TRACE_DATA) != 0)
    {
        for ( ulNodeLoop = 0; ulNodeLoop < usValidFrameNum; ulNodeLoop++ )
        {
            pstRptNode = &(pstDefBuffInfo->astRptNodeBuf[ulNodeLoop]);

            PPP_HDLC_HARD_MntnTraceSingleData(pstRptNode->usDefOutOneLen, (VOS_UINT8*)PPP_HDLC_NODE_PHY_TO_VIRT((VOS_UINT32)(pstRptNode->pucDefOutOneAddr)),
                                              ID_HDLC_MNTN_DEF_OUTPUT_DATA, ulNodeLoop);
        }
    }

    return;
}

/*****************************************************************************
 函 数 名  : PPP_HDLC_HARD_MntnFrmTraceInput
 功能描述  : 勾取封装输入参数链表和数据
 输入参数  : pstFrmBuffInfo -   封装使用的内存
             pstBuildInfo   -   存放输入数据
 输出参数  : 无
 返 回 值  : 无
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2012年4月10日
    作    者   : l00164359
    修改内容   : 新生成函数

*****************************************************************************/
VOS_VOID PPP_HDLC_HARD_MntnFrmTraceInput
(
    HDLC_FRM_BUFF_INFO_STRU         *pstFrmBuffInfo,
    HDLC_PARA_LINK_BUILD_INFO_STRU  *pstBuildInfo
)
{
    VOS_UINT32                          ulNodeLoop;
    HDLC_PARA_LINK_NODE_STRU           *pstParaNode;


    if ((g_stHdlcConfigInfo.ulHdlcMntnTraceCfg & PPP_HDLC_MNTN_TRACE_PARA) != 0)
    {
        PPP_HDLC_HARD_MntnTraceInputParaLink(ID_HDLC_MNTN_FRM_INPUT_PARA,
                                             pstBuildInfo->ulInputLinkNodeCnt,
                                             pstBuildInfo->ulInputLinkTotalSize,
                                             &(pstFrmBuffInfo->astInputParaLinkNodeBuf[0]));
    }

    if ((g_stHdlcConfigInfo.ulHdlcMntnTraceCfg & PPP_HDLC_MNTN_TRACE_DATA) != 0)
    {
        /* 记录并上报参数链表所有节点的数据内容，每个节点是一个IP包 */
        for ( ulNodeLoop = 0; ulNodeLoop < pstBuildInfo->ulInputLinkNodeCnt; ulNodeLoop++ )
        {
            pstParaNode = &(pstFrmBuffInfo->astInputParaLinkNodeBuf[ulNodeLoop]);

            PPP_HDLC_HARD_MntnTraceSingleData(pstParaNode->usDataLen, (VOS_UINT8*)PPP_PHY_TO_VIRT((VOS_UINT32)(pstParaNode->pucDataAddr)),
                                              ID_HDLC_MNTN_FRM_INPUT_DATA, ulNodeLoop);

            /* 需要将数据写回DDR，HDLC从DDR中读数据 */
            PPP_HDLC_CACHE_FLUSH((VOS_UINT8*)PPP_PHY_TO_VIRT((VOS_UINT32)(pstParaNode->pucDataAddr)), pstParaNode->usDataLen);
        }
    }

    return;
}

/*****************************************************************************
 函 数 名  : PPP_HDLC_HARD_MntnFrmTraceOutput
 功能描述  : 勾取封装输出参数链表和数据
 输入参数  : ucFrmValidNum  -   有效帧个数
             usFrmOutSegNum -   有效帧分段个数
             pstFrmBuffInfo -   封装相关内存地址
             pstBuildInfo   -   存放输入数据
 输出参数  : 无
 返 回 值  : 无
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2012年4月10日
    作    者   : l00164359
    修改内容   : 新生成函数

*****************************************************************************/
VOS_VOID PPP_HDLC_HARD_MntnFrmTraceOutput
(
    VOS_UINT8                           ucFrmValidNum,
    VOS_UINT16                          usFrmOutSegNum,
    HDLC_FRM_BUFF_INFO_STRU            *pstFrmBuffInfo,
    HDLC_PARA_LINK_BUILD_INFO_STRU     *pstBuildInfo
)
{
    HDLC_MNTN_FRM_OUTPUT_PARA_STRU      stOutputPara;
    HDLC_MNTN_FRM_OUTPUT_PARA_STRU     *pstOutputPara = &stOutputPara;
    VOS_UINT32                          ulDataLen;
    VOS_UINT32                          ulNodeLoop;
    HDLC_PARA_LINK_NODE_STRU           *pstParaNode;

    if ((g_stHdlcConfigInfo.ulHdlcMntnTraceCfg & PPP_HDLC_MNTN_TRACE_PARA) != 0)
    {
        ulDataLen     = sizeof(HDLC_MNTN_FRM_OUTPUT_PARA_STRU);

        pstOutputPara->ulOutputLinkNodeCnt   = pstBuildInfo->ulOutputLinkNodeCnt;
        pstOutputPara->ulOutputLinkTotalSize = pstBuildInfo->ulOutputLinkTotalSize;
        pstOutputPara->ucFrmValidNum         = ucFrmValidNum;
        pstOutputPara->usOutputNodeUsedCnt   = usFrmOutSegNum;

        VOS_MemCpy((VOS_UINT8 *)(&(pstOutputPara->astOutputParaLinkNodeBuf[0])),
                   (VOS_UINT8 *)(&(pstFrmBuffInfo->astOutputParaLinkNodeBuf[0])),
                   TTF_HDLC_FRM_OUTPUT_PARA_LINK_MAX_NUM * sizeof(HDLC_PARA_LINK_NODE_STRU));

        VOS_MemCpy((VOS_UINT8 *)(&(pstOutputPara->astRptNodeBuf[0])),
                   (VOS_UINT8 *)(&(pstFrmBuffInfo->astRptNodeBuf[0])),
                   TTF_HDLC_FRM_RPT_MAX_NUM * sizeof(HDLC_FRM_RPT_NODE_STRU));

        PPP_HDLC_HARD_MntnTraceMsg((HDLC_MNTN_TRACE_HEAD_STRU *)pstOutputPara,
                                        ID_HDLC_MNTN_FRM_OUTPUT_PARA, ulDataLen);
    }

    if ((g_stHdlcConfigInfo.ulHdlcMntnTraceCfg & PPP_HDLC_MNTN_TRACE_DATA) != 0)
    {
        for ( ulNodeLoop = 0; ulNodeLoop < usFrmOutSegNum; ulNodeLoop++ )
        {
            pstParaNode = &(pstFrmBuffInfo->astOutputParaLinkNodeBuf[ulNodeLoop]);

            PPP_HDLC_HARD_MntnTraceSingleData(pstParaNode->usDataLen, (VOS_UINT8*)PPP_PHY_TO_VIRT((VOS_UINT32)(pstParaNode->pucDataAddr)),
                                              ID_HDLC_MNTN_FRM_OUTPUT_DATA, ulNodeLoop);
        }
    }

    return;
}

/*****************************************************************************
 函 数 名  : PPP_HDLC_HARD_CommReleaseInputData
 功能描述  : 释放存储的PPP_ZC_STRU结构
 输入参数  : ppstLinkNode   -- 存储PPP_ZC_STRU指针的数组
             ulRelCnt       -- 待释放的个数
 输出参数  : 无
 返 回 值  : 无
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2012年4月10日
    作    者   : l00164359
    修改内容   : 新生成函数

*****************************************************************************/
VOS_VOID PPP_HDLC_HARD_CommReleaseLink
(
    PPP_ZC_STRU     **ppstLinkNode,
    VOS_UINT32        ulRelCnt
)
{
    VOS_UINT32                          ulNodeLoop;


    for ( ulNodeLoop = 0; ulNodeLoop < ulRelCnt; ulNodeLoop++ )
    {
        PPP_MemFree(ppstLinkNode[ulNodeLoop]);

        ppstLinkNode[ulNodeLoop] = VOS_NULL_PTR;
    }

    return;
}

/*****************************************************************************
 函 数 名  : PPP_HDLC_HARD_DefProcRptNode
 功能描述  : 根据上报信息地址和长度，申请零拷贝内存，并拷贝数据
 输入参数  : pstRptNode   -   上报信息
 输出参数  : 无
 返 回 值  : 无
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2012年4月10日
    作    者   : l00164359
    修改内容   : 新生成函数

*****************************************************************************/
PPP_ZC_STRU * PPP_HDLC_HARD_DefProcRptNode
(
    HDLC_DEF_RPT_NODE_STRU             *pstRptNode
)
{
    PPP_ZC_STRU                        *pstMem;
    VOS_UINT32                          usFistSegLen;
    VOS_UINT8                          *pucDefOutOneAddr;


    if ( (0 == pstRptNode->usDefOutOneLen) || (HDLC_DEF_OUT_PER_MAX_CNT < pstRptNode->usDefOutOneLen) )
    {
        PPP_HDLC_WARNING_LOG1("PPP_HDLC_HARD_DefProcValidFrames, WARNING, invalid usDefOutOneLen %d\r\n",
                      pstRptNode->usDefOutOneLen);

        return VOS_NULL_PTR;
    }

    pstMem = PPP_MemAlloc(pstRptNode->usDefOutOneLen, PPP_ZC_UL_RESERVE_LEN);

    if (VOS_NULL_PTR == pstMem)
    {
        return VOS_NULL_PTR;
    }

    pucDefOutOneAddr    = (VOS_UINT8*)PPP_HDLC_NODE_PHY_TO_VIRT((VOS_UINT32)pstRptNode->pucDefOutOneAddr);
    /* 判断该帧起始加长度是否超过输出空间尾部，超出后按绕回处理 */
    if ((pucDefOutOneAddr + pstRptNode->usDefOutOneLen) >
        HDLC_DEF_OUTPUT_BUF_END_ADDR)
    {
        if (pucDefOutOneAddr <= HDLC_DEF_OUTPUT_BUF_END_ADDR)
        {
            usFistSegLen = (VOS_UINT32)(HDLC_DEF_OUTPUT_BUF_END_ADDR - pucDefOutOneAddr);

            /* 拷贝从起始地址至输出空间尾部的数据 */
            PPP_MemSingleCopy(PPP_ZC_GET_DATA_PTR(pstMem), pucDefOutOneAddr,
                              usFistSegLen);

            /* 拷贝在输出空间首部的剩余数据 */
            PPP_MemSingleCopy(PPP_ZC_GET_DATA_PTR(pstMem) + usFistSegLen, HDLC_DEF_OUTPUT_BUF_START_ADDR,
                              pstRptNode->usDefOutOneLen - usFistSegLen);
        }
        else
        {
            PPP_MemFree(pstMem);

            PPP_HDLC_ERROR_LOG2("\r\nPPP, PPP_HDLC_HARD_DefProcRptNode, ERROR, Error pucDefOutOneAddr.\r\n",
                    pucDefOutOneAddr, HDLC_DEF_OUTPUT_BUF_END_ADDR);

            PPP_HDLC_HARD_MntnShowDefReg();

            return VOS_NULL_PTR;
        }
    }
    else
    {
        PPP_MemSingleCopy(PPP_ZC_GET_DATA_PTR(pstMem), pucDefOutOneAddr,
                          pstRptNode->usDefOutOneLen);
    }

    /* 设置零拷贝数据长度 */
    PPP_ZC_SET_DATA_LEN(pstMem, pstRptNode->usDefOutOneLen);

    return pstMem;
}

/*****************************************************************************
 函 数 名  : PPP_HDLC_HARD_DefProcValidFrames
 功能描述  : 处理有效帧
 输入参数  : ulMode       -   模式，IP或PPP
             usPppId    -   PPP实体ID
             pstLink    -   PPP链路信息
 输出参数  : 无
 返 回 值  : 无
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2012年4月10日
    作    者   : l00164359
    修改内容   : 新生成函数

*****************************************************************************/
VOS_VOID PPP_HDLC_HARD_DefProcValidFrames
(
    VOS_UINT32          ulMode,
        PPP_ID          usPppId,
    struct link        *pstLink
)
{
    VOS_UINT16                          usValidFrameNum;
    HDLC_DEF_BUFF_INFO_STRU            *pstDefBuffInfo;
    VOS_UINT32                          ulFrameLoop;
    HDLC_DEF_RPT_NODE_STRU             *pstRptNode;
    PPP_ZC_STRU                        *pstMem;


    pstDefBuffInfo  = HDLC_DEF_GET_BUF_INFO(usPppId);
    usValidFrameNum = (VOS_UINT16)TTF_Read32RegByBit(SOC_ARM_HDLC_DEF_STATUS_ADDR(HDLC_IP_BASE_ADDR), 8, 23);

    /* 上报解封装后数据可维可测:上报空间信息、输出内容 */
    PPP_HDLC_HARD_MntnDefTraceOutput(usValidFrameNum, pstDefBuffInfo);

    /* 有效帧数最大值检查 */
    if (TTF_HDLC_DEF_RPT_MAX_NUM < usValidFrameNum)
    {
        PPP_HDLC_WARNING_LOG2("PPP_HDLC_HARD_DefProcValidFrames, WARNING, usValidFrameNum = %d > TTF_HDLC_DEF_RPT_MAX_NUM = %d",
                      usValidFrameNum, TTF_HDLC_DEF_RPT_MAX_NUM);
        return;
    }

    g_PppHdlcHardStat.ulDefMaxValidCntOnce = TTF_MAX(g_PppHdlcHardStat.ulDefMaxValidCntOnce, usValidFrameNum);

    /* 将目的空间的有效帧数据拷贝至零拷贝内存，根据拨号类型调用上行发数接口 */
    for ( ulFrameLoop = 0 ; ulFrameLoop < usValidFrameNum; ulFrameLoop++ )
    {
        pstRptNode = &(pstDefBuffInfo->astRptNodeBuf[ulFrameLoop]);

        pstMem = PPP_HDLC_HARD_DefProcRptNode(pstRptNode);

        /* 申请不到内容或上报信息错误，丢弃该有效帧 */
        if (VOS_NULL_PTR == pstMem)
        {
            continue;
        }

        if (HDLC_IP_MODE == ulMode)
        {
            PPP_HDLC_ProcIpModeUlData(pstLink, pstMem, pstRptNode->usDefOutOnePro);
        }
        else
        {
            PPP_HDLC_ProcPppModeUlData(usPppId, pstMem);
        }
    }

    return;
}

/*****************************************************************************
 函 数 名  : PPP_HDLC_HARD_DefProcErrorFrames
 功能描述  : 处理错误帧
 输入参数  : pstLink    -   PPP链路信息
 输出参数  : 无
 返 回 值  : 无
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2012年4月10日
    作    者   : l00164359
    修改内容   : 新生成函数

*****************************************************************************/
VOS_VOID PPP_HDLC_HARD_DefProcErrorFrames
(
    struct link        *pstLink
)
{
    VOS_UINT8                           ucErrType;
    VOS_UINT8                           ucMask;
    VOS_UINT32                          ulErrTypeLoop;
    VOS_UINT8                           ucResult;
    HDLC_DEF_ERR_FRAMES_CNT_STRU        stErrCnt;


    /* 查询状态寄存器hdlc_def_status (0x88)的第24:30对应比特位为1表示有某种错误帧输出，
       为0表示无帧输出 */
    ucErrType = (VOS_UINT8)TTF_Read32RegByBit(SOC_ARM_HDLC_DEF_STATUS_ADDR(HDLC_IP_BASE_ADDR) , 24, 30);

    if (0 == ucErrType)
    {
        return;
    }

    /*lint -e734*/
    /* get fcs error count */
    stErrCnt.usFCSErrCnt        = (VOS_UINT16)TTF_Read32RegByBit(SOC_ARM_HDLC_DEF_ERR_INFO_0_ADDR(HDLC_IP_BASE_ADDR), 0, 15);

    /* get frame too long error count */
    stErrCnt.usLenLongCnt       = (VOS_UINT16)TTF_Read32RegByBit(SOC_ARM_HDLC_DEF_ERR_INFO_0_ADDR(HDLC_IP_BASE_ADDR), 16, 31);

    /* get frame too short error count */
    stErrCnt.usLenShortCnt      = (VOS_UINT16)TTF_Read32RegByBit(SOC_ARM_HDLC_DEF_ERR_INFO_1_ADDR(HDLC_IP_BASE_ADDR), 0, 15);

    /* get error protocol count */
    stErrCnt.usErrProtocolCnt   = (VOS_UINT16)TTF_Read32RegByBit(SOC_ARM_HDLC_DEF_ERR_INFO_1_ADDR(HDLC_IP_BASE_ADDR), 16, 31);

    /* get error control count */
    stErrCnt.usErrCtrlCnt       = (VOS_UINT16)TTF_Read32RegByBit(SOC_ARM_HDLC_DEF_ERR_INFO_2_ADDR(HDLC_IP_BASE_ADDR), 0, 15);

    /* get error address count */
    stErrCnt.usErrAddrCnt       = (VOS_UINT16)TTF_Read32RegByBit(SOC_ARM_HDLC_DEF_ERR_INFO_2_ADDR(HDLC_IP_BASE_ADDR), 16, 31);

    /* get error flag position count */
    stErrCnt.usFlagPosErrCnt    = (VOS_UINT16)TTF_Read32RegByBit(SOC_ARM_HDLC_DEF_ERR_INFO_3_ADDR(HDLC_IP_BASE_ADDR), 0, 15);
    /*lint +e734*/
    for (ulErrTypeLoop = 0UL; ulErrTypeLoop < HDLC_DEF_MAX_TYPE_CNT; ulErrTypeLoop++)
    {
        ucMask   = SET_BITS_VALUE_TO_BYTE(0x01, ulErrTypeLoop);    /* 构造掩码 */
        ucResult = (VOS_UINT8)GET_BITS_FROM_BYTE(ucErrType, ucMask);

        if (0 != ucResult)      /* 存在此类错误 */
        {
            if (0UL == ulErrTypeLoop)   /* 错误类型0: CRC校验错误 */
            {
                pstLink->hdlc.stats.badfcs       += stErrCnt.usFCSErrCnt;
                pstLink->hdlc.lqm.SaveInErrors   += stErrCnt.usFCSErrCnt;
                PPP_HDLC_WARNING_LOG("bad hdlc fcs\r\n");
            }
            else if (1UL == ulErrTypeLoop)    /* 错误类型1: 解封装后帧字节数大于1502bytes */
            {
                pstLink->hdlc.lqm.SaveInErrors += stErrCnt.usLenLongCnt;
                PPP_HDLC_WARNING_LOG("bad hdlc frame length too long\r\n");
            }
            else if (2UL == ulErrTypeLoop)    /* 错误类型2: 解封装后帧字节数小于4bytes */
            {
                pstLink->hdlc.lqm.SaveInErrors += stErrCnt.usLenShortCnt;
                PPP_HDLC_WARNING_LOG("bad hdlc frame length too short\r\n");
            }
            else if (3UL == ulErrTypeLoop)    /* 错误类型3: 当P域需剥离时, 收到非法的Protocol域值(非*******0 *******1形式) */
            {
                pstLink->hdlc.lqm.SaveInErrors += stErrCnt.usErrProtocolCnt;
                PPP_HDLC_WARNING_LOG("bad hdlc frame protocol\r\n");
            }
            else if (4UL == ulErrTypeLoop)    /* 错误类型4: 当AC域无压缩时, Control域值非0x03 */
            {
                pstLink->hdlc.lqm.SaveInErrors += stErrCnt.usErrCtrlCnt;
                pstLink->hdlc.stats.badcommand += stErrCnt.usErrCtrlCnt;
                PPP_HDLC_NORMAL_LOG("bad hdlc frame control\r\n");
            }
            else if (5UL == ulErrTypeLoop)    /* 错误类型5: 当AC域无压缩时, Address域值非0xFF */
            {
                pstLink->hdlc.lqm.SaveInErrors += stErrCnt.usErrAddrCnt;
                pstLink->hdlc.stats.badaddr    += stErrCnt.usErrAddrCnt;
                PPP_HDLC_NORMAL_LOG("bad hdlc frame address\r\n");
            }
            else if (6UL == ulErrTypeLoop)    /* 错误类型6: 转义字符0x7D后紧接一个Flag域 */
            {
                pstLink->hdlc.lqm.SaveInErrors += stErrCnt.usFlagPosErrCnt;
                PPP_HDLC_NORMAL_LOG("bad hdlc frame flag position\r\n");
            }
            else
            {
                PPP_HDLC_NORMAL_LOG("link_HDLCDefDealErr err\r\n");
            }
        }
    }

    return;
}

/*****************************************************************************
 函 数 名  : PPP_HDLC_HARD_DefCfgReg
 功能描述  : 配置解封装配置寄存器
 输入参数  : ulMode     -   IP或PPP模式
             pstLink    -   PPP链路信息
             pstDefUncompletedInfo  -   该路PPP链接上次解封装输出非完整帧信息
 输出参数  : 无
 返 回 值  : 无
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2012年4月10日
    作    者   : l00164359
    修改内容   : 新生成函数

*****************************************************************************/
VOS_UINT32 PPP_HDLC_HARD_DefCfgReg
(
    VOS_UINT32                      ulMode,
    struct link                    *pstLink,
    HDLC_DEF_UNCOMPLETED_INFO_STRU *pstDefUncompletedInfo
)
{
    /*
        hdlc_def_cfg  (0x70)
         31                           4 3     2   1     0
        |-------------------------------|-------|-----|-----|
        |              Rsv              |  Pfc  | Acfc| ago |
        Reserved             [31:4]  28'b0   h/s R/W  保留位。读时返回0。写时无影响。
        def_pfc              [3:2]   2'b0    h/s R/W  P域压缩指示：00：P域无压缩，需剥离；01：P域压缩，需剥离；11：P域不剥离；其他：无效；
        def_acfc             [1]     1'b0    h/s R/W  AC域压缩指示：0：AC域无压缩；1：表示AC域压缩；
        def_uncompleted_ago  [0]     1'b0    h/s R/W  用于指示对应当前解封装输入链表，同一PPP/IP拨号的以前最近解封装输入链表是否有解出非完整帧，
                                                      为了支持多个PPP/IP拨号而增加的配置：0，没有；1，有
        */

    VOS_UINT32       ulDeframerCfg;
    VOS_UINT8        ucACComp;
    VOS_UINT8        ucPComp;
    VOS_UINT8        ucLowByte;
    VOS_UINT16       usLowWord;

    /* 1.根据ulMode、P域和AC域是否压缩配置hdlc_def_cfg (0x70) */

    /* 获取AC域压缩指示, P域压缩指示 */
    ucACComp = (1 == pstLink->lcp.want_acfcomp) ? 1 : 0;

    if (HDLC_IP_MODE == ulMode) /* IP模式: P域不合入 */
    {
        ucPComp = (1 == pstLink->lcp.want_protocomp)
                   ? HDLC_PROTOCOL_REMOVE_WITH_COMPRESS
                   : HDLC_PROTOCOL_REMOVE_WITHOUT_COMPRESS;
    }
    else                        /* PPP模式: P域合入 */
    {
        ucPComp = HDLC_PROTOCOL_NO_REMOVE;
    }

    /* 将ucPComp设置到一个字节的第2, 3位上 */
    ucLowByte = SET_BITS_VALUE_TO_BYTE(ucPComp, HDLC_DEF_PFC_BITPOS);

    if (1 == ucACComp)  /* AC域压缩 */
    {
        SET_BIT_TO_BYTE(ucLowByte, HDLC_DEF_ACFC_BITPOS);
    }

    /* 2.设置非完整帧相关信息 */
    if ( (VOS_NULL_PTR != pstDefUncompletedInfo) &&
        (HDLC_DEF_UNCOMPLETED_EXIST == pstDefUncompletedInfo->ucExistFlag) )
    {
        /* def_uncompleted_ago置1表示有上次输出的非完整帧参与本次解封装 */
        SET_BIT_TO_BYTE(ucLowByte, HDLC_DEF_IS_UNCOMPLETED_AGO_BITPOS);

        /*
        def_uncompleted_len  (0x74)
         31                 16  15                  0
        |---------------------|----------------------|
        |         Rsv         |         Len          |
        Reserved             [31:16] 16'b0   h/s R/W  保留位。读时返回0。写时无影响。
        def_uncompleted_len  [15:0]  16'b0   h/s R/W  对应当前解封装输入链表，同一PPP/IP拨号的以前最近解封装输入链表解出非完整帧的长度，为了支持多个PPP/IP拨号而增加的配置
        */
        PPP_HDLC_WRITE_32REG(SOC_ARM_HDLC_DEF_UNCOMPLETED_LEN_ADDR(HDLC_IP_BASE_ADDR),
                        (VOS_UINT32)pstDefUncompletedInfo->usDefOutOneLen & 0xFFFF);

        /*
        def_uncompleted_pro  (0x78)
         31                 16  15                  0
        |---------------------|----------------------|
        |         Rsv         |         Pro          |
        Reserved             [31:16] 16'b0   h/s R/W  保留位。读时返回0。写时无影响。
        def_uncompleted_pro  [15:0]  16'b0   h/s R/W  对应当前解封装输入链表，同一PPP/IP拨号的以前最近解封装输入链表解出非完整帧的
                                                      协议，为了支持多个PPP/IP拨号而增加的配置（可能其中的0Byte、1Byte或2Byte有效）
        */
        PPP_HDLC_WRITE_32REG(SOC_ARM_HDLC_DEF_UNCOMPLETED_PRO_ADDR(HDLC_IP_BASE_ADDR),
                        (VOS_UINT32)pstDefUncompletedInfo->usDefOutOnePro & 0xFFFF);

        /*
        def_uncompleted_addr  (0x7C)
         31                  0
        |----------------------|
        |         Addr         |
        def_uncompleted_addr [31:0]  32'b0   h/s R/W  对应当前解封装输入链表，同一PPP/IP拨号的以前最近解封装输入链表解出非完整帧的
                                                      外部存储起始地址，为了支持多个PPP/IP拨号而增加的配置（该地址可能是与原来上报不同的新地址）
        */
        PPP_HDLC_WRITE_32REG(SOC_ARM_HDLC_DEF_UNCOMPLETED_ADDR(HDLC_IP_BASE_ADDR),
                        (VOS_UINT32)pstDefUncompletedInfo->pucDefOutOneAddr);

        /*
        def_uncomplet_st_ago  (0x80)
         31                  16 15             5 4     0
        |----------------------|----------------|-------|
        |         Ago          |       Rsv      |  Ago  |
        crc16_result_ago     [31:16] 16'b0   h/s R/W  与当前解封装输入链表同一PPP/IP拨号的以前最近那套解封装输入链表处理完解出非完整帧时的CRC校验值
        Reserved             [15:5]  11'b0   h/s R/W  保留位。读时返回0。写时无影响。
        def_data_st_curr_ago [4:0]   5'b0    h/s R/W  与当前解封装输入链表同一PPP/IP拨号的以前最近那套解封装输入链表处理完解出非完整帧时的数据状态机当前状态
        */
        PPP_HDLC_WRITE_32REG(SOC_ARM_HDLC_DEF_UNCOMPLETED_ST_AGO_ADDR(HDLC_IP_BASE_ADDR),
                        (VOS_UINT32)pstDefUncompletedInfo->ulDefStAgo);

        /*
        def_info_frl_cnt_ago  (0xC0)
         31        27 26                 16 15   11 10              0
        |------------|---------------------|-------|-----------------|
        |    Rsv     |         Ago         |  Rsv  |       Ago       |
        Reserved             [31:27] 5'b0    h/s R/W  保留位。读时返回0。写时无影响。
        def_framel_cnt_ago   [26:16] 11'b0   h/s R/W  与当前解封装输入链表同一PPP/IP拨号的以前最近那套解封装输入链表处理完解出非完整帧时的帧长度
        Reserved             [15:11] 5'b0    h/s R/W  保留位。读时返回0。写时无影响。
        def_info_cnt_ago     [10:0]  11'b0   h/s R/W  与当前解封装输入链表同一PPP/IP拨号的以前最近那套解封装输入链表处理完解出非完整帧时的信息长度
        */
        PPP_HDLC_WRITE_32REG(SOC_ARM_HDLC_DEF_INFO_FRL_CNT_AGO_ADDR(HDLC_IP_BASE_ADDR),
                        (VOS_UINT32)pstDefUncompletedInfo->ulDefInfoFrlCntAgo);
    }

    usLowWord     = HDLC_MAKE_WORD(0x00, ucLowByte);
    ulDeframerCfg = HDLC_MAKE_DWORD(0x00, usLowWord);

    /* 将配置结果写入寄存器 */
    PPP_HDLC_WRITE_32REG(SOC_ARM_HDLC_DEF_CFG_ADDR(HDLC_IP_BASE_ADDR),ulDeframerCfg);

    /* 设置输入数据最大单包长度 */
    PPP_HDLC_WRITE_32REG(SOC_ARM_HDLC_DEF_IN_PKT_LEN_MAX_ADDR(HDLC_IP_BASE_ADDR),
                    (VOS_UINT32)HDLC_DEF_IN_PER_MAX_CNT);

    return VOS_OK;
}

/*****************************************************************************
 函 数 名  : PPP_HDLC_HARD_DefSaveUncompletedInfo
 功能描述  : 根据非完整帧指示，保存非完整帧信息
 输入参数  : usPppId    -   PPP实体ID
 输出参数  : 无
 返 回 值  : 无
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2012年4月10日
    作    者   : l00164359
    修改内容   : 新生成函数

*****************************************************************************/
VOS_VOID PPP_HDLC_HARD_DefSaveUncompletedInfo
(
    PPP_ID          usPppId
)
{
    HDLC_DEF_UNCOMPLETED_INFO_STRU     *pstUncompletedInfo;
    VOS_UINT32                          ulStatus;                /* 解封装状态 */
    HDLC_DEF_BUFF_INFO_STRU            *pstDefBuffInfo;
    VOS_UINT32                          ulValidNum;
    VOS_UINT8                          *pucDefOutOneAddr;
    HDLC_DEF_RPT_NODE_STRU             *pstRptNode;


    pstDefBuffInfo     = HDLC_DEF_GET_BUF_INFO(usPppId);
    pstUncompletedInfo = HDLC_DEF_GET_UNCOMPLETED_INFO(usPppId);

    ulStatus  =   PPP_HDLC_READ_32REG(SOC_ARM_HDLC_DEF_STATUS_ADDR(HDLC_IP_BASE_ADDR));

    /* 查询状态寄存器hdlc_def_status (0x88)的第2位
       为1表示本次解封装有非完整帧输出，
       为0表示无非完整帧输出 */
    if (0 == (ulStatus & 0x4))
    {
        pstUncompletedInfo->ucExistFlag = HDLC_DEF_UNCOMPLETED_NOT_EXIST;

        return;
    }

    g_PppHdlcHardStat.ulDefUncompleteCnt++;

    /* def_valid_num        [23:8]  16'b0   h/s RO   有帧上报时，有效帧数目；（不包括最后一个可能的非完整帧） */
    ulValidNum = (ulStatus & 0xFFFF00) >> 8;

    /* 非完整帧的上报信息在有效帧后面，但是不算在有效帧数目内 */
    if (TTF_HDLC_DEF_RPT_MAX_NUM <= ulValidNum)
    {
        PPP_HDLC_ERROR_LOG2("PPP_HDLC_HARD_DefSaveUncompletedInfo, ERROR, ulValidNum %d >= TTF_HDLC_DEF_RPT_MAX_NUM %d!\r\n",
                     ulValidNum, TTF_HDLC_DEF_RPT_MAX_NUM);

        pstUncompletedInfo->ucExistFlag = HDLC_DEF_UNCOMPLETED_NOT_EXIST;

        return;
    }

    /* 有非完整帧时需要读取并保存def_uncomplet_st_now(0x8C)、def_info_frl_cnt_now(0xC4)
       读取并保存上报空间有效帧之后的非完整帧长度、协议和数据地址 */
    pstUncompletedInfo->ucExistFlag = HDLC_DEF_UNCOMPLETED_EXIST;

    pstRptNode = &(pstDefBuffInfo->astRptNodeBuf[ulValidNum]);

    pucDefOutOneAddr = (VOS_UINT8*)PPP_HDLC_NODE_PHY_TO_VIRT((VOS_UINT32)pstRptNode->pucDefOutOneAddr);


    if (pucDefOutOneAddr != HDLC_DEF_OUTPUT_BUF_START_ADDR)
    {
        if ((pucDefOutOneAddr - HDLC_DEF_OUTPUT_BUF_START_ADDR) >= pstRptNode->usDefOutOneLen)
        {
            mdrv_memcpy(HDLC_DEF_OUTPUT_BUF_START_ADDR, pucDefOutOneAddr, pstRptNode->usDefOutOneLen);
        }
        else
        {
            PS_MEM_MOVE(HDLC_DEF_OUTPUT_BUF_START_ADDR, pucDefOutOneAddr, pstRptNode->usDefOutOneLen);
        }
#ifndef PPP_ST_TEST
        pstRptNode->pucDefOutOneAddr = (VOS_UINT8*)PPP_HDLC_NODE_VIRT_TO_PHY((VOS_UINT32)HDLC_DEF_OUTPUT_BUF_START_ADDR);
#endif
    }


    /* 非完整帧的协议、长度和在存储空间的地址，软件只是暂存这些信息，等下解封装的时候再原样配给HDLC */
    pstUncompletedInfo->usDefOutOnePro   = pstRptNode->usDefOutOnePro;
    pstUncompletedInfo->usDefOutOneLen   = pstRptNode->usDefOutOneLen;
    pstUncompletedInfo->pucDefOutOneAddr = pstRptNode->pucDefOutOneAddr;

    /* 软件只是暂存这些信息，等下解封装的时候再原样配给HDLC */
    pstUncompletedInfo->ulDefStAgo         = PPP_HDLC_READ_32REG(SOC_ARM_HDLC_DEF_UNCOMPLETED_ST_NOW_ADDR(HDLC_IP_BASE_ADDR));
    pstUncompletedInfo->ulDefInfoFrlCntAgo = PPP_HDLC_READ_32REG(SOC_ARM_HDLC_DEF_INFO_FRL_CNT_NOW_ADDR(HDLC_IP_BASE_ADDR));

    PPP_HDLC_HARD_MntnDefTraceUncompleteInfo(pstUncompletedInfo);

    return;
}

/*****************************************************************************
 函 数 名  : PPP_HDLC_HARD_DefWaitAndProc
 功能描述  : 等待解封装暂停或完成，然后处理输出数据，可能会有多次停等的过程
 输入参数  : ulMode     -   模式，IP或PPP
             ulEnableInterrupt  -   中断是否使能
             usPppId    -   PPP实体ID
             pstLink    -   PPP链路信息
 输出参数  : 无
 返 回 值  : 无
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2012年4月10日
    作    者   : l00164359
    修改内容   : 新生成函数

*****************************************************************************/
VOS_VOID PPP_HDLC_HARD_DefWaitAndProc
(
    VOS_UINT32          ulMode,
    VOS_UINT32          ulEnableInterrupt,
    PPP_ID              usPppId,
    struct link        *pstLink
)
{
    VOS_UINT32                          ulDefStatus;
    VOS_UINT32                          ulContinue;

    for (; ;)
    {
        /* 使能中断，则等待中断辅程序释放信号量；否则轮询解封装状态寄存器 */
        ulDefStatus = PPP_HDLC_HARD_DefWaitResult(ulEnableInterrupt);

        switch ( ulDefStatus )
        {
            case HDLC_DEF_STATUS_PAUSE_RPT_SPACE_FULL :
            case HDLC_DEF_STATUS_PAUSE_OUTPUT_SPACE_FULL :
                /* 处理有效帧，配置GO_ON寄存器 */
                PPP_HDLC_HARD_DefProcValidFrames(ulMode, usPppId, pstLink);
                PPP_HDLC_HARD_DefCfgGoOnReg(ulDefStatus);

                ulContinue = VOS_TRUE;
                g_PppHdlcHardStat.ulDefFullPauseCnt++;
                break;
            case HDLC_DEF_STATUS_PAUSE_LCP :
                /* 处理有效帧和LCP帧，更新配置寄存器，配置GO_ON寄存器 */
                PPP_HDLC_HARD_DefProcValidFrames(ulMode, usPppId, pstLink);
                PPP_HDLC_HARD_DefCfgReg(ulMode, pstLink, VOS_NULL_PTR);
                PPP_HDLC_HARD_DefCfgGoOnReg(ulDefStatus);

                ulContinue = VOS_TRUE;
                g_PppHdlcHardStat.ulDefLcpPauseCnt++;
                break;
            case HDLC_DEF_STATUS_DONE_WITHOUT_FRAMES :
                /* 根据非完整帧指示，保存非完整帧信息 */
                PPP_HDLC_HARD_DefSaveUncompletedInfo(usPppId);

                ulContinue = VOS_FALSE;
                break;
            case HDLC_DEF_STATUS_DONE_WITH_FRAMES :
                /* 处理有效帧、错误帧和LCP帧(可能是最后一帧)，根据非完整帧指示，保存非完整帧信息 */
                PPP_HDLC_HARD_DefProcValidFrames(ulMode, usPppId, pstLink);
                PPP_HDLC_HARD_DefProcErrorFrames(pstLink);
                PPP_HDLC_HARD_DefSaveUncompletedInfo(usPppId);
                ulContinue = VOS_FALSE;
                break;
            case HDLC_DEF_STATUS_DOING :
            default:
                /* 打印异常日志，挂起PPP任务 */
                PPP_HDLC_HARD_DefProcException(ulDefStatus, ulEnableInterrupt);

                ulContinue = VOS_FALSE;
                break;
        }

        /* 暂停状态需要继续处理，其他状态解封装完成退出 */
        if (VOS_TRUE != ulContinue)
        {
            break;
        }
    }

    g_stHdlcRegSaveInfo.ulHdlcDefRawInt = 0xFFFFFFFFU;
    g_stHdlcRegSaveInfo.ulHdlcDefStatus = 0xFFFFFFFFU;

    return;
}

/*****************************************************************************
 函 数 名  : PPP_HDLC_HARD_DefCheckPara
 功能描述  : 检查构造输入参数链表相关参数是否合法
 输入参数  : pstMem     -   待封装数据包
             ulDataLen  -   待封装数据包长度
             ucDataType -   待封装数据包类型
 输出参数  : 无
 返 回 值  : PPP_HDLC_PARA_CHECK_RESULT_ENUM_UINT32
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2012年4月20日
    作    者   : l00164359
    修改内容   : 新生成函数

*****************************************************************************/
PPP_HDLC_PARA_CHECK_RESULT_ENUM_UINT32 PPP_HDLC_HARD_DefCheckPara
(
    PPP_ZC_STRU                 *pstMem,
    VOS_UINT32                   ulDataLen,
    PPP_DATA_TYPE_ENUM_UINT8     ucDataType
)
{
    PPP_DATA_TYPE_ENUM_UINT8     ucCurrDataType;


    /* 获取待封装数据包类型 */
    ucCurrDataType = (PPP_ZC_GET_DATA_APP(pstMem) & 0x00FF);

    if ( ucDataType != ucCurrDataType )
    {
        return PPP_HDLC_PARA_CHECK_FAIL_KEEP;
    }

    /* 解封装最大输入长度是内存模块允许的最大长度，目前是1536B */
    /* 规避HDLC Bug内存可能扩大1 */
    if ( (0 == ulDataLen) || (PPP_ZC_MAX_DATA_LEN < ulDataLen) )
    {
        PPP_HDLC_NORMAL_LOG1("PPP_HDLC_HARD_DefCheckPara, NORMAL, invalid data length %d\r\n", ulDataLen);

        return PPP_HDLC_PARA_CHECK_FAIL_DISCARD;
    }

    return PPP_HDLC_PARA_CHECK_PASS;
}


/*****************************************************************************
 函 数 名  : PPP_HDLC_HARD_ForbiddenHdlcBug
 功能描述  : 规避HDLC硬件Bug,具体参见问题单DTS2014060907737
 输入参数  : ppstMem     -   待解封装数据包指针

 输出参数  : ppstMem  规避之后数据
 返 回 值  : 无
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2014年06月17日
    作    者   : t00148005
    修改内容   : 新生成函数

*****************************************************************************/
VOS_VOID PPP_HDLC_HARD_ForbiddenHdlcBug(PPP_ZC_STRU **ppstMem)
{
    PPP_ZC_STRU *pstMem;
    PPP_ZC_STRU *pstTmpMem;
    VOS_UINT8   *pstData;
    VOS_UINT16   usLen;
    const VOS_UINT8    ucEndByte = 0x7e;

    pstMem  = *ppstMem;

    if (VOS_NULL_PTR == pstMem)
    {
        return;
    }

    usLen   = PPP_ZC_GET_DATA_LEN(pstMem);
    pstData = PPP_ZC_GET_DATA_PTR(pstMem);

    if (usLen <= 1)
    {
        return;
    }

    if (ucEndByte != pstData[usLen - 2])
    {
        /* 倒数第二个字节不为7e不用处理 */
        return;
    }
    else if ((usLen >= 3) && (ucEndByte == pstData[usLen - 3]))
    {
        /* 倒数第三个字节为7e不用处理 */
        return;
    }
    else
    {
        /*
            倒数第二个字节为7e,倒数第三个字节不为7e的场景
            将最后一个字节后向移一个字节,同时内存的长度+1

            skb申请的内存结构如下
           |--------data(uslen)--------|----32bytes align(0~31)-----|--skb_share_info(256)----|
        */
        if (PPP_ZC_GET_RESERVE_ROOM(pstMem) > 0)
        {
            INSERT_BYTE_LAST(pstMem, pstData, usLen, ucEndByte);
            g_PppHdlcHardStat.ulForbidHdlcBugNoCpy++;
        }
        else
        {
            /* 申请一个保留1字节的内存 */

            pstTmpMem = PPP_MemAlloc(usLen + 1, 0);
            if (VOS_NULL_PTR != pstTmpMem)
            {
                PPP_MemWriteData(pstTmpMem, pstData, usLen);

                pstData = PPP_ZC_GET_DATA_PTR(pstTmpMem);

                INSERT_BYTE_LAST(pstTmpMem, pstData, usLen, ucEndByte);
                g_PppHdlcHardStat.ulForbidHdlcBugCpy++;
            }

            /* 不管新申请的内存是否为空都传出去,在外面处理 */
            *ppstMem = pstTmpMem;

            /* 将原内存释放 */
            PPP_MemFree(pstMem);
        }
    }
}

/*****************************************************************************
 函 数 名  : PPP_HDLC_HARD_DefBuildInputParaLink
 功能描述  : 构造解封装输入参数链表
 输入参数  : pstBuildPara   -   构造链表所需的参数
 输出参数  : pstBuildInfo   -   构造链表的结果信息，保存输入链表长度、节点个数、零拷贝内存指针
 返 回 值  : 无
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2012年4月10日
    作    者   : l00164359
    修改内容   : 新生成函数

*****************************************************************************/
VOS_UINT32 PPP_HDLC_HARD_DefBuildInputParaLink
(
    HDLC_PARA_LINK_BUILD_PARA_STRU  *pstBuildPara,
    HDLC_PARA_LINK_BUILD_INFO_STRU  *pstBuildInfo
)
{
    VOS_UINT32                              ulLinkLoop;
    PPP_ZC_STRU                            *pstMem;
    PPP_DATA_TYPE_ENUM_UINT8                ucDataType;
    PPP_HDLC_PARA_CHECK_RESULT_ENUM_UINT32  enCheckResult;
    VOS_UINT16                              usDataLen;
    HDLC_PARA_LINK_NODE_STRU               *pstParaNode;
    VOS_UINT32                              ulNodeIndex;
    HDLC_DEF_BUFF_INFO_STRU                *pstDefBuffInfo;
    HDLC_DEF_UNCOMPLETED_INFO_STRU         *pstUncompletedInfo;
    VOS_UINT32                              ulMaxDataLen1Time = TTF_HDLC_DEF_INPUT_PARA_LINK_MAX_SIZE;


    /* 清空输出信息 */
    VOS_MemSet(pstBuildInfo, 0, sizeof(HDLC_PARA_LINK_BUILD_INFO_STRU));

    pstUncompletedInfo = HDLC_DEF_GET_UNCOMPLETED_INFO(pstBuildPara->usPppId);

    if (HDLC_DEF_UNCOMPLETED_EXIST == pstUncompletedInfo->ucExistFlag)
    {
        ulMaxDataLen1Time = TTF_HDLC_DEF_INPUT_PARA_LINK_MAX_SIZE - pstUncompletedInfo->usDefOutOneLen;
    }


    /* 根据usPppId找到对应的内存  */
    pstDefBuffInfo = HDLC_DEF_GET_BUF_INFO(pstBuildPara->usPppId);
    ucDataType     = pstBuildPara->ucDataType;

    for ( ulLinkLoop = 0 ; ulLinkLoop < TTF_HDLC_DEF_INPUT_PARA_LINK_MAX_NUM; ulLinkLoop++ )
    {
        pstMem     = (PPP_ZC_STRU *)PPP_ZC_PEEK_QUEUE_HEAD(pstBuildPara->pstDataQ);

        /* 还没有到最大节点数，但是队列中已经没有数据 */
        if( VOS_NULL_PTR == pstMem )
        {
            break;
        }

        usDataLen     = PPP_ZC_GET_DATA_LEN(pstMem);
        enCheckResult = PPP_HDLC_HARD_DefCheckPara(pstMem, usDataLen, ucDataType);

        if( PPP_HDLC_PARA_CHECK_FAIL_DISCARD == enCheckResult )
        {
            pstMem = PPP_ZC_DEQUEUE_HEAD(pstBuildPara->pstDataQ);
            PPP_MemFree(pstMem);
            pstBuildInfo->ulDealCnt++;

            g_PppHdlcHardStat.ulDefInputDiscardCnt++;
            continue;
        }

        if( PPP_HDLC_PARA_CHECK_FAIL_KEEP == enCheckResult )
        {
            break;
        }


        /* 从PPP队列取出头结点，并插入输入队列 pstBuildInfo->apstInputLinkNode */
        pstMem  = PPP_ZC_DEQUEUE_HEAD(pstBuildPara->pstDataQ);

        /* 规避HDLC BUG,在发现HDLC BUG场景下对原有数据进行替换,
           后面的pstMem为替换后的内存指针,原始内存指针可能已经被释放
         */
        PPP_HDLC_HARD_ForbiddenHdlcBug(&pstMem);

        /* 替换内存的时候申请内存失败,直接处理下一块数据  */
        if (VOS_NULL_PTR == pstMem)
        {
            continue;
        }

        /* 内存可能发生替换,重新取长度 */
        usDataLen = PPP_ZC_GET_DATA_LEN(pstMem);

        /* 一次配链表过程中待封装数据包总长不能超过15KB */
        /* 规避HDLC BUG,后面数据被修改过,可能扩大了1字节,需要放到后面判断 */
        if( pstBuildInfo->ulInputLinkTotalSize + usDataLen  > ulMaxDataLen1Time )
        {
            /* 内存放回队列,下次再处理 */
            PPP_ZC_ENQUEUE_HEAD(pstBuildPara->pstDataQ, pstMem);

            break;
        }

        /* 获取当前要添加节点的下标 */
        ulNodeIndex = pstBuildInfo->ulInputLinkNodeCnt;

        /* 本次要构造的参数节点 */
        pstParaNode = &(pstDefBuffInfo->astInputParaLinkNodeBuf[ulNodeIndex]);

        /* 把节点组成链表 */
        if( 0 != ulNodeIndex )
        {
            pstDefBuffInfo->astInputParaLinkNodeBuf[ulNodeIndex - 1].pstNextNode = (HDLC_PARA_LINK_NODE_STRU *)PPP_HDLC_NODE_VIRT_TO_PHY((VOS_UINT32)pstParaNode);
        }

        /* 填写输入参数链表结点相关域 */
        pstParaNode->pucDataAddr = (VOS_UINT8*)PPP_VIRT_TO_PHY((VOS_UINT_PTR)PPP_ZC_GET_DATA_PTR(pstMem));
        pstParaNode->usDataLen   = usDataLen;
        pstParaNode->pstNextNode = VOS_NULL_PTR;

        pstBuildInfo->apstInputLinkNode[ulNodeIndex] = pstMem;
        pstBuildInfo->ulInputLinkTotalSize          += (VOS_UINT32)usDataLen;
        pstBuildInfo->ulInputLinkNodeCnt++;
        pstBuildInfo->ulDealCnt++;

        /* 需要将数据写回DDR，HDLC从DDR中读数据 */
        PPP_HDLC_CACHE_FLUSH(PPP_ZC_GET_DATA_PTR(pstMem), PPP_ZC_GET_DATA_LEN(pstMem));
    }

    if (0 == pstBuildInfo->ulInputLinkNodeCnt)
    {
        return VOS_ERR;
    }

    /* 上报输入参数链表内容可维可测 */
    PPP_HDLC_HARD_MntnDefTraceInput(pstDefBuffInfo, pstBuildInfo);

    return VOS_OK;
}

/************************************************************,*****************
 函 数 名  : PPP_HDLC_HARD_DefCfgBufReg
 功能描述  : 配置解封装使用的内存至相关寄存器
 输入参数  : pstDefBuffInfo    -   解封装使用的内存信息
 输出参数  : 无
 返 回 值  : 无
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2012年4月10日
    作    者   : l00164359
    修改内容   : 新生成函数

*****************************************************************************/
VOS_VOID PPP_HDLC_HARD_DefCfgBufReg(HDLC_DEF_BUFF_INFO_STRU *pstDefBuffInfo)
{
    /* 将封装输入参数链表的起始地址配置给寄存器def_in_lli_addr(0x90) */
    PPP_HDLC_WRITE_32REG(SOC_ARM_HDLC_DEF_IN_LLI_ADDR(HDLC_IP_BASE_ADDR),
                    PPP_HDLC_NODE_VIRT_TO_PHY((VOS_UINT32)&(pstDefBuffInfo->astInputParaLinkNodeBuf[0])));

    /* 将封装输出参数链表的起始地址配置给寄存器def_out_spc_addr(0xA0) */
    PPP_HDLC_WRITE_32REG(SOC_ARM_HDLC_DEF_OUT_SPC_ADDR(HDLC_IP_BASE_ADDR),
                    PPP_HDLC_NODE_VIRT_TO_PHY((VOS_UINT32)&(pstDefBuffInfo->aucOutputDataBuf[0])));

    /* 将封装输出参数链表的起始地址配置给寄存器def_out_space_dep(0xA4)低16位 */
    PPP_HDLC_WRITE_32REG(SOC_ARM_HDLC_DEF_OUT_SPACE_DEP_ADDR(HDLC_IP_BASE_ADDR),
                    (VOS_UINT32)TTF_HDLC_DEF_OUTPUT_DATA_BUF_LEN & 0xFFFF);

    /* 将封装有效帧结果信息上报空间起始地址配置给寄存器def_rpt_addr(0xA8) */
    PPP_HDLC_WRITE_32REG(SOC_ARM_HDLC_DEF_RPT_ADDR(HDLC_IP_BASE_ADDR),
                    PPP_HDLC_NODE_VIRT_TO_PHY((VOS_UINT32)&(pstDefBuffInfo->astRptNodeBuf[0])));

    /* 将封装有效帧结果信息上报空间深度配置给寄存器def_rpt_dep (0xAC)低16位 */
    PPP_HDLC_WRITE_32REG(SOC_ARM_HDLC_DEF_RPT_DEP_ADDR(HDLC_IP_BASE_ADDR),
                    (VOS_UINT32)TTF_HDLC_DEF_RPT_BUF_LEN & 0xFFFF);

    return;
}

/*****************************************************************************
 函 数 名  : PPP_HDLC_HARD_DefPacket
 功能描述  : 硬件方式IP类型解封装
 输入参数  : usPppId    -   PPP实体ID
             pstLink    -   PPP链路信息
             pstDataQ   -   PPP数据队列
             ulDealCnt  -   本次处理数据包个数
 输出参数  : 参见PPP_HDLC_RESULT_TYPE_ENUM_UINT32
 返 回 值  : 无
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2012年4月10日
    作    者   : l00164359
    修改内容   : 新生成函数

*****************************************************************************/
VOS_UINT32 PPP_HDLC_HARD_DefPacket
(
    PPP_ID              usPppId,
    struct link        *pstLink,
    PPP_ZC_QUEUE_STRU  *pstDataQ,
    VOS_UINT32         *pulDealCnt
)
{
    VOS_UINT32                          ulEnableInterrupt;
    HDLC_PARA_LINK_BUILD_INFO_STRU      stBuildInfo;
    HDLC_PARA_LINK_BUILD_PARA_STRU      stBuildPara;
    VOS_UINT32                          ulBuildResult;
    HDLC_DEF_BUFF_INFO_STRU            *pstDefBuffInfo;


    pstDefBuffInfo = HDLC_DEF_GET_BUF_INFO(usPppId);

    stBuildPara.ucDataType = PPP_PULL_PACKET_TYPE;
    stBuildPara.usProtocol = PROTO_IP;
    stBuildPara.pstDataQ   = pstDataQ;

    /* 构造输入参数链表，并上报链表内存可维可测 */
    ulBuildResult = PPP_HDLC_HARD_DefBuildInputParaLink(&stBuildPara, &stBuildInfo);

    *pulDealCnt = stBuildInfo.ulDealCnt;

    if (VOS_OK != ulBuildResult)
    {
        return ulBuildResult;
    }

    g_PppHdlcHardStat.ulDefMaxInputCntOnce  = TTF_MAX(g_PppHdlcHardStat.ulDefMaxInputCntOnce, stBuildInfo.ulInputLinkNodeCnt);
    g_PppHdlcHardStat.ulDefMaxInputSizeOnce = TTF_MAX(g_PppHdlcHardStat.ulDefMaxInputSizeOnce, stBuildInfo.ulInputLinkTotalSize);

    /* 配置封装、解封装通用寄存器 */
    PPP_HDLC_HARD_CommCfgReg();

    /* 配置内存相关寄存器 */
    PPP_HDLC_HARD_DefCfgBufReg(pstDefBuffInfo);

    /* 配置压缩指示、非完整帧相关信息寄存器 */
    PPP_HDLC_HARD_DefCfgReg(HDLC_IP_MODE, pstLink, HDLC_DEF_GET_UNCOMPLETED_INFO(usPppId));

    /* 配置使能寄存器，并上报使能前寄存器可维可测 */
    ulEnableInterrupt = PPP_HDLC_HARD_DefCfgEnReg(stBuildInfo.ulInputLinkTotalSize);

    /* 等待解封装暂停或完成，然后处理输出数据，可能会有多次停等的过程 */
    PPP_HDLC_HARD_DefWaitAndProc(HDLC_IP_MODE, ulEnableInterrupt, usPppId, pstLink);

    /* 释放已解封装完成的数据 */
    PPP_HDLC_HARD_CommReleaseLink(stBuildInfo.apstInputLinkNode, stBuildInfo.ulInputLinkNodeCnt);

    return VOS_OK;
}

/*****************************************************************************
 函 数 名  : PPP_HDLC_HARD_DefRawData
 功能描述  : 硬件方式PPP类型解封装
 输入参数  : usPppId    -   PPP实体ID
             pstLink    -   PPP链路信息
             pstDataQ   -   PPP数据队列
             ulDealCnt  -   本次处理数据包个数
 输出参数  : 参见PPP_HDLC_RESULT_TYPE_ENUM_UINT32
 返 回 值  : 无
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2012年4月10日
    作    者   : l00164359
    修改内容   : 新生成函数

*****************************************************************************/
VOS_UINT32 PPP_HDLC_HARD_DefRawData
(
    PPP_ID              usPppId,
    struct link        *pstLink,
    PPP_ZC_QUEUE_STRU  *pstDataQ,
    VOS_UINT32         *pulDealCnt
)
{
    VOS_UINT32                          ulEnableInterrupt;
    HDLC_PARA_LINK_BUILD_INFO_STRU      stBuildInfo;
    HDLC_PARA_LINK_BUILD_PARA_STRU      stBuildPara;
    VOS_UINT32                          ulBuildResult;
    HDLC_DEF_BUFF_INFO_STRU            *pstDefBuffInfo;


    pstDefBuffInfo = HDLC_DEF_GET_BUF_INFO(usPppId);

    VOS_MemSet(&stBuildInfo, 0, sizeof(HDLC_PARA_LINK_BUILD_INFO_STRU));

    stBuildPara.ucDataType = PPP_PULL_RAW_DATA_TYPE;
    stBuildPara.usProtocol = PROTO_IP;
    stBuildPara.pstDataQ   = pstDataQ;

    /* 构造输入参数链表，并上报链表内存可维可测 */
    ulBuildResult = PPP_HDLC_HARD_DefBuildInputParaLink(&stBuildPara, &stBuildInfo);

    *pulDealCnt = stBuildInfo.ulDealCnt;

    if (VOS_OK != ulBuildResult)
    {
        return ulBuildResult;
    }

    g_PppHdlcHardStat.ulDefMaxInputCntOnce  = TTF_MAX(g_PppHdlcHardStat.ulDefMaxInputCntOnce, stBuildInfo.ulInputLinkNodeCnt);
    g_PppHdlcHardStat.ulDefMaxInputSizeOnce = TTF_MAX(g_PppHdlcHardStat.ulDefMaxInputSizeOnce, stBuildInfo.ulInputLinkTotalSize);

    /* 配置封装、解封装通用寄存器 */
    PPP_HDLC_HARD_CommCfgReg();

    /* 配置内存相关寄存器 */
    PPP_HDLC_HARD_DefCfgBufReg(pstDefBuffInfo);

    /* 配置压缩指示、非完整帧相关信息寄存器 */
    PPP_HDLC_HARD_DefCfgReg(HDLC_PPP_MODE, pstLink, HDLC_DEF_GET_UNCOMPLETED_INFO(usPppId));

    /* 配置使能寄存器，并上报使能前寄存器可维可测 */
    ulEnableInterrupt = PPP_HDLC_HARD_DefCfgEnReg(stBuildInfo.ulInputLinkTotalSize);

    /* 等待解封装暂停或完成，然后处理输出数据，可能会有多次停等的过程 */
    PPP_HDLC_HARD_DefWaitAndProc(HDLC_PPP_MODE, ulEnableInterrupt, usPppId, pstLink);

    /* 释放已解封装完成的数据 */
    PPP_HDLC_HARD_CommReleaseLink(stBuildInfo.apstInputLinkNode, stBuildInfo.ulInputLinkNodeCnt);

    return VOS_OK;
}

/*****************************************************************************
 函 数 名  : PPP_HDLC_HARD_FrmUpdateLink
 功能描述  : 申请一块内存后更新链表相关结构信息
 输入参数  : ulAllocMemCnt      - 本次申请的内存块个数
             aulAllocLen        - 记录本次申请的各个内存块的长度
             papstAllocedMem    - 记录本次申请的各个内存块控制结构指针
             pstBuildPara       -   构造链表所需的参数
 输出参数  : pstBuildInfo       -   构造链表的结果信息，保存输入链表长度、节点个数、零拷贝内存指针
 返 回 值  :
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2012年4月20日
    作    者   : c00191211
    修改内容   : 新生成函数

*****************************************************************************/
VOS_UINT32 PPP_HDLC_HARD_FrmUpdateLink
(
    VOS_UINT32                      ulAllocMemCnt,
    VOS_UINT32 *                    aulAllocLen,
    PPP_ZC_STRU                   **ppstAllocedMem,
    HDLC_PARA_LINK_BUILD_PARA_STRU *pstBuildPara,
    HDLC_PARA_LINK_BUILD_INFO_STRU *pstBuildInfo
)
{
    VOS_UINT32                          ulMemLoop;
    VOS_UINT32                          ulNodeIndex;
    HDLC_PARA_LINK_NODE_STRU           *pstOutputParaNode;
    HDLC_FRM_BUFF_INFO_STRU            *pstFrmBuffInfo;


    /* 根据usPppId找到对应的内存  */
    pstFrmBuffInfo          = HDLC_FRM_GET_BUF_INFO(pstBuildPara->usPppId);

    if( (pstBuildInfo->ulOutputLinkNodeCnt + ulAllocMemCnt) > TTF_HDLC_FRM_OUTPUT_PARA_LINK_MAX_NUM )
    {
        g_PppHdlcHardStat.ulFrmOutputLinkFullCnt++;

        PPP_HDLC_HARD_CommReleaseLink(ppstAllocedMem, ulAllocMemCnt);

        return VOS_ERR;
    }

    /* 更新目的空间数组 apstOutputLinkNode，用于释放目的空间 */
    VOS_MemCpy(&(pstBuildInfo->apstOutputLinkNode[pstBuildInfo->ulOutputLinkNodeCnt]),
               &(ppstAllocedMem[0]),
               ulAllocMemCnt * sizeof(PPP_ZC_STRU *));

    /* 给封装输出参数链表结点的各个成员赋值 */
    for ( ulMemLoop = 0; ulMemLoop < ulAllocMemCnt; ulMemLoop++ )
    {
        ulNodeIndex = pstBuildInfo->ulOutputLinkNodeCnt;

        pstOutputParaNode = &(pstFrmBuffInfo->astOutputParaLinkNodeBuf[ulNodeIndex]);

        /* 更新上个输入参数链表结点的pstNextNode域 */
        if (0 != ulNodeIndex)
        {
            pstFrmBuffInfo->astOutputParaLinkNodeBuf[ulNodeIndex - 1].pstNextNode = (HDLC_PARA_LINK_NODE_STRU*)PPP_HDLC_NODE_VIRT_TO_PHY((VOS_UINT32)pstOutputParaNode);
        }

        pstOutputParaNode->pucDataAddr = (VOS_UINT8*)PPP_VIRT_TO_PHY((VOS_UINT_PTR)PPP_ZC_GET_DATA_PTR(ppstAllocedMem[ulMemLoop]));
        pstOutputParaNode->usDataLen   = (VOS_UINT16)aulAllocLen[ulMemLoop];
        pstOutputParaNode->pstNextNode = VOS_NULL_PTR;

        pstBuildInfo->ulOutputLinkNodeCnt++;
        pstBuildInfo->ulOutputLinkTotalSize += aulAllocLen[ulMemLoop];

        PPP_HDLC_CACHE_INVALID((VOS_UINT8*)PPP_PHY_TO_VIRT((VOS_UINT32)(pstOutputParaNode->pucDataAddr)), pstOutputParaNode->usDataLen);
    }

    return VOS_OK;
}

/*****************************************************************************
 函 数 名  : PPP_HDLC_HARD_OutputMemAlloc
 功能描述  : 封装输出目的空间申请
 输入参数  : usLen          -   待申请的内存长度
             pstBuildPara   -   构造链表所需的参数
 输出参数  : pstBuildInfo   -   构造链表的结果信息，保存输入链表长度、节点个数、零拷贝内存指针
 返 回 值  : VOS_OK/VOS_ERR
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2012年4月20日
    作    者   : c00191211
    修改内容   : 新生成函数

*****************************************************************************/
VOS_UINT32 PPP_HDLC_HARD_FrmOutputMemAlloc
(
    VOS_UINT16                           usLen,
    HDLC_PARA_LINK_BUILD_PARA_STRU      *pstBuildPara,
    HDLC_PARA_LINK_BUILD_INFO_STRU      *pstBuildInfo
)
{
    VOS_UINT16                  usFrmedMaxLen;                                  /* 封装后的可能的最大长度 */
    VOS_UINT16                  usAllocLen;
    VOS_UINT32                  ulAllocLoop;
    VOS_UINT32                  ulLoopCnt;
    VOS_UINT32                  ulAllocMemCnt;                                  /* 本次申请的内存块数 */
    VOS_UINT32                  aulAllocLen[HDLC_OUTPUT_PARA_LINK_MAX_SIZE];    /* 记录本次申请的各个内存块长度 */
    PPP_ZC_STRU *               apstAllocedMem[HDLC_OUTPUT_PARA_LINK_MAX_SIZE]; /* 记录本次申请的各个内存块指针 */
    PPP_ZC_STRU                *pstMem;


    /* 封装后可能的最大数据长度(2*原始数据长度+13B) */
    usFrmedMaxLen = (VOS_UINT16)HDLC_FRM_GET_MAX_FRAMED_LEN(usLen);
    ulAllocMemCnt = 0;
    ulLoopCnt     = TTF_CEIL(usFrmedMaxLen, PPP_ZC_MAX_DATA_LEN);

    for ( ulAllocLoop = 0 ; ulAllocLoop < ulLoopCnt; ulAllocLoop++ )
    {
        if (ulAllocLoop != (ulLoopCnt - 1) )
        {
            usAllocLen = PPP_ZC_MAX_DATA_LEN;
        }
        else
        {
            usAllocLen = (VOS_UINT16)(usFrmedMaxLen - ulAllocLoop*PPP_ZC_MAX_DATA_LEN);
        }

        pstMem = PPP_MemAlloc(usAllocLen, PPP_ZC_DL_RESERVE_LEN);

        if (VOS_NULL_PTR == pstMem)
        {
            break;
        }

        ulAllocMemCnt++;
        aulAllocLen[ulAllocLoop]    = usAllocLen;
        apstAllocedMem[ulAllocLoop] = pstMem;
    }

    /* 如果有申请内存失败的情况，则释放本次已经申请的内存 */
    if (ulLoopCnt > ulAllocMemCnt)
    {
        PPP_HDLC_HARD_CommReleaseLink(&(apstAllocedMem[0]), ulAllocMemCnt);
        return VOS_ERR;
    }

    return PPP_HDLC_HARD_FrmUpdateLink(ulAllocMemCnt,
                                       &(aulAllocLen[0]), &(apstAllocedMem[0]),
                                       pstBuildPara, pstBuildInfo);
}


/*****************************************************************************
 函 数 名  : PPP_HDLC_HARD_FrmGetProtocol
 功能描述  : PPP模式下获取待封装数据包协议值
 输入参数  : pstMem         -   待封装数据包
 输出参数  : pusProtocol    -   待封装数据包协议值
 返 回 值  : VOS_OK/VOS_ERR
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2012年4月20日
    作    者   : c00191211
    修改内容   : 新生成函数

*****************************************************************************/
VOS_UINT32 PPP_HDLC_HARD_FrmGetProtocol
(
    PPP_ZC_STRU     *pstMem,
    VOS_UINT16      *pusProtocol
)
{
    VOS_UINT8           aucProto[2] = {0, 0};
    VOS_UINT32          ulRtn;


    ulRtn = PPP_MemGet(pstMem, 0, aucProto, 2);

    if ( PS_FAIL == ulRtn )
    {
        return VOS_ERR;
    }

    if ( 0x01 == GET_BITS_FROM_BYTE(aucProto[0], 0x01) )
    {
        *pusProtocol = HDLC_MAKE_WORD(0x00, aucProto[0]);
    }
    else
    {
        if ( 0x01 == GET_BITS_FROM_BYTE(aucProto[1], 0x01) )
        {
            *pusProtocol = HDLC_MAKE_WORD(aucProto[0], aucProto[1]);
        }
        else
        {
            PPP_HDLC_WARNING_LOG("PPP_HDLC_HARD_FrmGetProtocol, Warning, PPP mode framer data protocol error\r\n");
            return VOS_ERR;
        }
    }

    return VOS_OK;
}

/*****************************************************************************
 函 数 名  : PPP_HDLC_HARD_FrmBuildParaLink
 功能描述  : 检查构造输入输出参数链表相关参数是否合法
 输入参数  : pstMem     -   待封装数据包
             ulDataLen  -   待封装数据包长度
             ucDataType -   待封装数据包类型
             usProtocol -   待封装数据包协议类型
 输出参数  : 无
 返 回 值  : PPP_HDLC_PARA_CHECK_RESULT_ENUM_UINT32
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2012年4月20日
    作    者   : c00191211
    修改内容   : 新生成函数

*****************************************************************************/
PPP_HDLC_PARA_CHECK_RESULT_ENUM_UINT32 PPP_HDLC_HARD_FrmCheckPara
(
    PPP_ZC_STRU                 *pstMem,
    VOS_UINT32                   ulDataLen,
    PPP_DATA_TYPE_ENUM_UINT8     ucDataType,
    VOS_UINT16                   usProtocol
)
{
    PPP_DATA_TYPE_ENUM_UINT8     ucCurrDataType;
    VOS_UINT32                   ulRlst;
    VOS_UINT16                   usCurrProtocol;


    /* 获取待封装数据包类型 */
    ucCurrDataType = (PPP_ZC_GET_DATA_APP(pstMem) & 0x00FF);

    if ( ucDataType != ucCurrDataType )
    {
        return PPP_HDLC_PARA_CHECK_FAIL_KEEP;
    }

    /* 待封装数据包长度异常 */
    if ( (0 == ulDataLen) || (HDLC_FRM_IN_PER_MAX_CNT < ulDataLen) )
    {
        PPP_HDLC_NORMAL_LOG1("PPP_HDLC_HARD_FrmCheckPara,IP mode framer data len wrong %d\r\n", ulDataLen);

        return PPP_HDLC_PARA_CHECK_FAIL_DISCARD;
    }

    /* 如果不是PPP模式 */
    if( PPP_PUSH_RAW_DATA_TYPE != ucCurrDataType )
    {
        return PPP_HDLC_PARA_CHECK_PASS;
    }

    ulRlst  = PPP_HDLC_HARD_FrmGetProtocol(pstMem, &usCurrProtocol);

    if( VOS_OK != ulRlst )
    {
        PPP_HDLC_WARNING_LOG("PPP_HDLC_HARD_FrmCheckPara, Warning, PPP mode get framer data protocol error\r\n");
        return PPP_HDLC_PARA_CHECK_FAIL_DISCARD;
    }

    /* 保证一次链表配置过程中封装协议值一致 */
    if( usProtocol != usCurrProtocol )
    {
        return PPP_HDLC_PARA_CHECK_FAIL_KEEP;
    }

    return PPP_HDLC_PARA_CHECK_PASS;
}

/*****************************************************************************
 函 数 名  : PPP_HDLC_HARD_FrmBuildParaLink
 功能描述  : 构造输入输出参数链表，并上报链表内存可维可测
 输入参数  : pstBuildPara   -   构造链表所需的参数
 输出参数  : pstBuildInfo   -   构造链表的结果信息，保存输入链表长度、节点个数、零拷贝内存指针
 返 回 值  : VOS_OK/VOS_ERR
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2012年4月20日
    作    者   : c00191211
    修改内容   : 新生成函数

*****************************************************************************/
VOS_UINT32 PPP_HDLC_HARD_FrmBuildParaLink
(
 HDLC_PARA_LINK_BUILD_PARA_STRU      *pstBuildPara,
 HDLC_PARA_LINK_BUILD_INFO_STRU      *pstBuildInfo
 )
{
    PPP_ZC_STRU                             *pstMem;
    VOS_UINT32                               ulLoop;
    VOS_UINT16                               usUnFrmLen;
    VOS_UINT32                               ulAllocResult;
    HDLC_PARA_LINK_NODE_STRU                *pstParaNode;
    VOS_UINT32                               ulNodeIndex;
    PPP_HDLC_PARA_CHECK_RESULT_ENUM_UINT32   enCheckResult;
    VOS_UINT32                               ulAllocMemFail;
    HDLC_FRM_BUFF_INFO_STRU                 *pstFrmBuffInfo;


    VOS_MemSet(pstBuildInfo, 0, sizeof(HDLC_PARA_LINK_BUILD_INFO_STRU));

    /* 根据usPppId找到对应的内存  */
    pstFrmBuffInfo = HDLC_FRM_GET_BUF_INFO(pstBuildPara->usPppId);
    ulAllocMemFail = VOS_FALSE;

    for(ulLoop = 0; ulLoop < TTF_HDLC_FRM_INPUT_PARA_LINK_MAX_NUM; ulLoop++)
    {
        pstMem = (PPP_ZC_STRU *)PPP_ZC_PEEK_QUEUE_HEAD(pstBuildPara->pstDataQ);

        if( VOS_NULL_PTR == pstMem )
        {
            break;
        }

        usUnFrmLen    = PPP_ZC_GET_DATA_LEN(pstMem);
        enCheckResult = PPP_HDLC_HARD_FrmCheckPara(pstMem, usUnFrmLen,
                                                   pstBuildPara->ucDataType,
                                                   pstBuildPara->usProtocol);

        if( PPP_HDLC_PARA_CHECK_FAIL_DISCARD == enCheckResult )
        {
            pstMem = PPP_ZC_DEQUEUE_HEAD(pstBuildPara->pstDataQ);
            PPP_MemFree(pstMem);
            pstBuildInfo->ulDealCnt++;

            g_PppHdlcHardStat.ulFrmInputDiscardCnt++;
            continue;
        }

        if( PPP_HDLC_PARA_CHECK_FAIL_KEEP == enCheckResult )
        {
            break;
        }

        /* 一次配链表过程中待封装数据包总长不能超过15KB */
        if( pstBuildInfo->ulInputLinkTotalSize + usUnFrmLen > TTF_HDLC_FRM_INPUT_PARA_LINK_MAX_SIZE )
        {
            break;
        }

        /* 申请封装目的空间 */
        ulAllocResult = PPP_HDLC_HARD_FrmOutputMemAlloc(usUnFrmLen, pstBuildPara, pstBuildInfo);

        if( VOS_OK != ulAllocResult )
        {
            ulAllocMemFail = VOS_TRUE;

            g_PppHdlcHardStat.ulFrmAllocOutputMemFailCnt++;
            break;
        }

        /* 从PPP队列取出头结点，并插入输入队列 pstBuildInfo->apstInputLinkNode */
        pstMem = PPP_ZC_DEQUEUE_HEAD(pstBuildPara->pstDataQ);

        /* 获取当前要添加节点的下标 */
        ulNodeIndex = pstBuildInfo->ulInputLinkNodeCnt;

        /* 本次要构造的参数节点 */
        pstParaNode = &(pstFrmBuffInfo->astInputParaLinkNodeBuf[ulNodeIndex]);

        /* 填写输入参数链表结点相关域 */
        if( 0 != ulNodeIndex )
        {
            pstFrmBuffInfo->astInputParaLinkNodeBuf[ulNodeIndex - 1].pstNextNode = (HDLC_PARA_LINK_NODE_STRU*)PPP_HDLC_NODE_VIRT_TO_PHY((VOS_UINT32)pstParaNode);
        }

        pstParaNode->pucDataAddr = (VOS_UINT8*)PPP_VIRT_TO_PHY((VOS_UINT_PTR)PPP_ZC_GET_DATA_PTR(pstMem));
        pstParaNode->usDataLen   = usUnFrmLen;
        pstParaNode->pstNextNode = VOS_NULL_PTR;

        pstBuildInfo->apstInputLinkNode[ulNodeIndex] = pstMem;
        pstBuildInfo->ulInputLinkTotalSize          += (VOS_UINT32)usUnFrmLen;
        pstBuildInfo->ulInputLinkNodeCnt++;
        pstBuildInfo->ulDealCnt++;

        /* 需要将数据写回DDR，HDLC从DDR中读数据 */
        PPP_HDLC_CACHE_FLUSH(PPP_ZC_GET_DATA_PTR(pstMem), PPP_ZC_GET_DATA_LEN(pstMem));
    }

    if (0 == pstBuildInfo->ulInputLinkNodeCnt)
    {
        if (VOS_TRUE == ulAllocMemFail)
        {
            /* 等待一段时间后，重新尝试申请内存再封装 */
            PPP_HDLC_HARD_FrmStartTimer(pstBuildPara);

            g_PppHdlcHardStat.ulFrmAllocFirstMemFailCnt++;
        }

        return VOS_ERR;
    }

    /* 报输入输出参数链表内容可维可测 */
    PPP_HDLC_HARD_MntnFrmTraceInput(pstFrmBuffInfo, pstBuildInfo);

    return VOS_OK;
}

/*****************************************************************************
 函 数 名  : PPP_HDLC_HARD_FrmCfgBufReg
 功能描述  : 配置封装使用的内存至相关寄存器
 输入参数  : pstFrmBuffInfo -   封装使用的内存信息
 输出参数  : 无
 返 回 值  : 无
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2012年4月20日
    作    者   : c00191211
    修改内容   : 新生成函数

*****************************************************************************/
VOS_VOID PPP_HDLC_HARD_FrmCfgBufReg(HDLC_FRM_BUFF_INFO_STRU *pstFrmBuffInfo)
{
    /* 将封装输入参数链表的起始地址配置给寄存器frm_in_lli_addr */
    PPP_HDLC_WRITE_32REG(SOC_ARM_HDLC_FRM_IN_LLI_ADDR(HDLC_IP_BASE_ADDR),
                    PPP_HDLC_NODE_VIRT_TO_PHY((VOS_UINT32)&(pstFrmBuffInfo->astInputParaLinkNodeBuf[0])));

    /* 将封装输出参数链表的起始地址配置给寄存器frm_out_lli_addr */
    PPP_HDLC_WRITE_32REG(SOC_ARM_HDLC_FRM_OUT_LLI_ADDR(HDLC_IP_BASE_ADDR),
                    PPP_HDLC_NODE_VIRT_TO_PHY((VOS_UINT32)&(pstFrmBuffInfo->astOutputParaLinkNodeBuf[0])));

    /* 将封装有效帧结果信息上报空间起始地址配置给寄存器frm_rpt_addr */
    PPP_HDLC_WRITE_32REG(SOC_ARM_HDLC_FRM_RPT_ADDR(HDLC_IP_BASE_ADDR),
                    PPP_HDLC_NODE_VIRT_TO_PHY((VOS_UINT32)&(pstFrmBuffInfo->astRptNodeBuf[0])));

    /* 将封装有效帧结果信息上报空间深度配置给寄存器frm_rpt_dep的[15:0]位 */
    PPP_HDLC_WRITE_32REG(SOC_ARM_HDLC_FRM_RPT_DEP_ADDR(HDLC_IP_BASE_ADDR),
                    (VOS_UINT32)TTF_HDLC_FRM_RPT_BUF_LEN & 0xFFFF);

    return;
}

/*****************************************************************************
 函 数 名  : PPP_HDLC_HARD_FrmCfgReg
 功能描述  : IP模式下配置封装相关寄存器
 输入参数  : pstLink    - PPP链路信息
             usProtocol - 待封装的协议值
 输出参数  :
 返 回 值  :
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2012年4月20日
    作    者   : c00191211
    修改内容   : 新生成函数

*****************************************************************************/
VOS_VOID PPP_HDLC_HARD_FrmCfgReg
(
    struct link        *pstLink,
    VOS_UINT16          usProtocol
)
{
    /*
    hdlc_frm_cfg   (0x20)
      31              16 15           4 3      2   1      0
    |-------------------|--------------|--------|------|------|
    |      protocol     |      Rsv     |   Pfc  | Acfc |1dor2d|

    frm_protocol         [31:16] 16'b0   h/s R/W  封装协议值。有效协议值规定参见规格列表。
    Reserved             [15:4]  12'b0   h/s R/W  保留位。读时返回0。写时无影响。
    frm_pfc              [3:2]   2'b0    h/s R/W  P域压缩指示：00：硬件模块添加P域，P域无压缩;
                                                               01：硬件模块添加P域，P域压缩;
                                                               11：硬件模块不添加P域;
                                                               其他：无效;
    frm_acfc             [1]     1'b0    h/s R/W  AC域压缩指示：0：AC域无压缩;1：表示AC域压缩;
    frm_in_lli_1dor2d    [0]     1'b0    h/s R/W  封装输入一维或二维链表选择指示寄存器：
                                                                0为一维;1为二维;

    IP模式一定添加P域,PPP模式一定不添加P域
      LCP帧: AC域不压缩，P域不压缩
    */

    VOS_UINT32              ulFrmCfg;


    /* 将寄存器hdlc_frm_cfg的[0]位frm_in_lli_1dor2d配置为0 */
    ulFrmCfg = 0x0;

    /* 配置hdlc_frm_cfg的 P域和 AC域 */
    if (PROTO_LCP != usProtocol)
    {
        if ( 1 == pstLink->lcp.his_acfcomp )
        {
            ulFrmCfg |= (1 << HDLC_FRM_ACFC_BITPOS);
        }

        if ( 1 == pstLink->lcp.his_protocomp )
        {
            ulFrmCfg |= (1 << HDLC_FRM_PFC_BITPOS);
        }

        /* 配置hdlc_frm_accm */
        PPP_HDLC_WRITE_32REG(SOC_ARM_HDLC_FRM_ACCM_ADDR(HDLC_IP_BASE_ADDR),
                            pstLink->lcp.his_accmap);
    }
    else
    {
        PPP_HDLC_WRITE_32REG(SOC_ARM_HDLC_FRM_ACCM_ADDR(HDLC_IP_BASE_ADDR), 0xFFFFFFFFU);
    }

    /* 配置寄存器hdlc_frm_cfg的[31:16]位frm_protocol为usProtocol */
    ulFrmCfg |= ( ((VOS_UINT32)usProtocol) << 16 );

    PPP_HDLC_WRITE_32REG(SOC_ARM_HDLC_FRM_CFG_ADDR(HDLC_IP_BASE_ADDR), ulFrmCfg);

    return;
}

/*****************************************************************************
 函 数 名  : PPP_HDLC_HARD_FrmCfgReg
 功能描述  : PPP模式下配置封装相关寄存器
 输入参数  : pstLink    - PPP链路信息
             usProtocol - 待封装的协议值
 输出参数  :
 返 回 值  :
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2012年4月20日
    作    者   : c00191211
    修改内容   : 新生成函数

*****************************************************************************/
VOS_VOID PPP_HDLC_HARD_FrmRawCfgReg
(
    struct link        *pstLink,
    VOS_UINT16          usProtocol
)
{
    /*
    hdlc_frm_cfg   (0x20)
      31              16 15           4 3      2   1      0
    |-------------------|--------------|--------|------|------|
    |      protocol     |      Rsv     |   Pfc  | Acfc |1dor2d|

    frm_protocol         [31:16] 16'b0   h/s R/W  封装协议值。有效协议值规定参见规格列表。
    Reserved             [15:4]  12'b0   h/s R/W  保留位。读时返回0。写时无影响。
    frm_pfc              [3:2]   2'b0    h/s R/W  P域压缩指示：00：硬件模块添加P域，P域无压缩;
                                                               01：硬件模块添加P域，P域压缩;
                                                               11：硬件模块不添加P域;
                                                               其他：无效;
    frm_acfc             [1]     1'b0    h/s R/W  AC域压缩指示：0：AC域无压缩;1：表示AC域压缩;
    frm_in_lli_1dor2d    [0]     1'b0    h/s R/W  封装输入一维或二维链表选择指示寄存器：
                                                                0为一维;1为二维;

    IP模式一定添加P域,PPP模式一定不添加P域
      LCP帧: AC域不压缩，P域不压缩
    */

    VOS_UINT32              ulFrmCfg;
    /*PS_BOOL_ENUM_UINT8      enPComp;       是否压缩协议字段, 是 - PS_TRUE */
    PS_BOOL_ENUM_UINT8      enACComp;     /* 是否压缩地址和控制字段, 是 - PS_TRUE */
    VOS_UINT32              ulACCM;
    VOS_UINT8               ucACComp;
    VOS_UINT8               ucPComp;
    VOS_UINT8               ucLowByte;
    VOS_UINT16              usLowWord;


    /* 将寄存器hdlc_frm_cfg的[0]位frm_in_lli_1dor2d配置为0 */
    ulFrmCfg    = 0x0;

    if (PROTO_LCP == usProtocol)
    {
        /* LCP帧P不压缩, AC不压缩, ACCM为全转义 */
        /*enPComp     = PS_FALSE; */
        enACComp    = PS_FALSE;
        ulACCM      = 0xFFFFFFFFU;
    }
    else
    {
        /* 使用默认值 */
        /*enPComp     = (1 == pstLink->lcp.his_protocomp) ? PS_TRUE : PS_FALSE; */
        enACComp    = (1 == pstLink->lcp.his_acfcomp) ? PS_TRUE : PS_FALSE;
        /* 由于PPP拨号不知道ACCM, 故设置为协议默认值 */
        ulACCM      = 0xFFFFFFFFU;
    }

    /* 获取AC域压缩指示, P域压缩指示, 协议值, ACCM */
    ucACComp = (PS_TRUE == enACComp) ? 1 : 0;
    ucPComp = HDLC_PROTOCOL_NO_ADD;

    /* 设置accm */
    PPP_HDLC_WRITE_32REG(SOC_ARM_HDLC_FRM_ACCM_ADDR(HDLC_IP_BASE_ADDR),ulACCM);

    /* 将ucPComp设置到一个字节的第2, 3位上 */
    ucLowByte = SET_BITS_VALUE_TO_BYTE(ucPComp, HDLC_FRM_PFC_BITPOS);

    if (1 == ucACComp)  /* AC域压缩 */
    {
        SET_BIT_TO_BYTE(ucLowByte, HDLC_FRM_ACFC_BITPOS);
    }
    else
    {
        CLEAR_BIT_TO_BYTE(ucLowByte, HDLC_FRM_ACFC_BITPOS);
    }

    usLowWord   = HDLC_MAKE_WORD(0x00, ucLowByte);
    ulFrmCfg    = HDLC_MAKE_DWORD(usProtocol, usLowWord);

    /* 设置AC域压缩指示, P域压缩指示, 协议值和使能封装标记, accm */
    PPP_HDLC_WRITE_32REG(SOC_ARM_HDLC_FRM_CFG_ADDR(HDLC_IP_BASE_ADDR),ulFrmCfg);

    return;
}

/*****************************************************************************
 函 数 名  : PPP_HDLC_HARD_FrmProcValidFram
 功能描述  : 处理有效帧，并释放剩余内存
 输入参数  : usPppId        -   PPP实体ID
 输出参数  : pstBuildInfo   -   构造链表的结果信息，保存输入链表长度、节点个数、零拷贝内存指针
 返 回 值  : 无
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2012年4月20日
    作    者   : c00191211
    修改内容   : 新生成函数

*****************************************************************************/
VOS_VOID PPP_HDLC_HARD_FrmProcValidFrames
(
    PPP_ID                               usPppId,
    HDLC_PARA_LINK_BUILD_INFO_STRU      *pstBuildInfo
)
{
    PPP_ZC_STRU                        *pstMem;
    VOS_UINT16                          usFrmOutSegNum;
    VOS_UINT8                           ucFrmValidNum;
    VOS_UINT32                          ulFrmOutSpaceCnt;
    HDLC_FRM_BUFF_INFO_STRU            *pstFrmBuffInfo;
    HDLC_PARA_LINK_NODE_STRU           *pstOutputParaLink;
    HDLC_FRM_RPT_NODE_STRU             *pstFrmRptNodeStru;
    PPP_ZC_STRU                       **ppstOutputLinkNode;
    VOS_UINT32                          ucRptSpaceIndex;
    VOS_UINT32                          ulOutputLinkIndex;
    VOS_UINT8                          *pucFrmOutAddr;
    VOS_UINT16                          usFrmOutLen;
    VOS_UINT16                          usDataLen;


    pstFrmBuffInfo     = HDLC_FRM_GET_BUF_INFO(usPppId);                   /* 根据usPppId找到对应的内存  */
    pstFrmRptNodeStru  = &(pstFrmBuffInfo->astRptNodeBuf[0]);              /* 封装上报空间首地址 */
    pstOutputParaLink  = &(pstFrmBuffInfo->astOutputParaLinkNodeBuf[0]);   /* 封装输出链表首地址 */
    ppstOutputLinkNode = &(pstBuildInfo->apstOutputLinkNode[0]);           /* 封装输出链表节点对应零拷贝内存链表首地址 */
    ulFrmOutSpaceCnt   = pstBuildInfo->ulOutputLinkNodeCnt;                /* 封装输出链表节点的个数 */

    /* 有效帧存放占用片段个数usFrmOutSegNum= hdlc_frm_status寄存器[31:16]位的值 */
    usFrmOutSegNum = (VOS_UINT16)TTF_Read32RegByBit(SOC_ARM_HDLC_FRM_STATUS_ADDR(HDLC_IP_BASE_ADDR), 16, 31);

    /* 有效帧个数usFrmValidNum= hdlc_frm_status寄存器[15:8]位的值 */
    ucFrmValidNum  = (VOS_UINT8)TTF_Read32RegByBit(SOC_ARM_HDLC_FRM_STATUS_ADDR(HDLC_IP_BASE_ADDR), 8, 15);

    /* 上报封装后数据可维可测:上报空间信息、输出链表内容 */
    PPP_HDLC_HARD_MntnFrmTraceOutput(ucFrmValidNum, usFrmOutSegNum, pstFrmBuffInfo, pstBuildInfo);

    /* ucFrmValidNum肯定要小于等于使用的内存块数usFrmOutSegNum */
    if( ucFrmValidNum > usFrmOutSegNum )
    {
        PPP_HDLC_ERROR_LOG2("PPP_HDLC_HARD_FrmProcValidFram, ERROR, frm_valid_num = %d > usFrmOutSegNum = %d",
                      ucFrmValidNum, usFrmOutSegNum);
        PPP_HDLC_HARD_CommReleaseLink(ppstOutputLinkNode, ulFrmOutSpaceCnt);
        return;
    }

    /* ucFrmValidNum应该与输入数据相同ulInputLinkNodeCnt，如果解封装出错可能会比后者小 */
    if( ucFrmValidNum > pstBuildInfo->ulInputLinkNodeCnt )
    {
        PPP_HDLC_ERROR_LOG2("PPP_HDLC_HARD_FrmProcValidFram, ERROR, frm_valid_num = %d > InputLinkNodeCnt = %d",
                      ucFrmValidNum, pstBuildInfo->ulInputLinkNodeCnt);
        PPP_HDLC_HARD_CommReleaseLink(ppstOutputLinkNode, ulFrmOutSpaceCnt);
        return;
    }

    /* usFrmOutSegNum使用的内存块数肯定小于等于ulOutputLinkNodeCnt */
    if( usFrmOutSegNum  > ulFrmOutSpaceCnt )
    {
        PPP_HDLC_ERROR_LOG2("PPP_HDLC_HARD_FrmProcValidFram, ERROR, frm_out_seg_num = %d > OutputLinkNodeCnt = %d",
                      usFrmOutSegNum, ulFrmOutSpaceCnt);
        PPP_HDLC_HARD_CommReleaseLink(ppstOutputLinkNode, ulFrmOutSpaceCnt);
        return;
    }

    ucRptSpaceIndex   = 0;
    ulOutputLinkIndex = 0;

    while( ucRptSpaceIndex < ucFrmValidNum )
    {
        pucFrmOutAddr    = (VOS_UINT8*)PPP_PHY_TO_VIRT((VOS_UINT32)pstFrmRptNodeStru[ucRptSpaceIndex].pucFrmOutOneAddr);
        usFrmOutLen      = pstFrmRptNodeStru[ucRptSpaceIndex].usFrmOutOneLen;

        if ( (0 == usFrmOutLen) || (HDLC_FRM_OUT_PER_MAX_CNT < usFrmOutLen) )
        {
            PPP_HDLC_ERROR_LOG1("PPP_HDLC_HARD_FrmProcValidFrames, ERROR, invalid usFrmOutOneLen %d\r\n", usFrmOutLen);

            /* 释放申请的目的空间 */
            PPP_HDLC_HARD_CommReleaseLink(ppstOutputLinkNode + ulOutputLinkIndex,
                                          ulFrmOutSpaceCnt - ulOutputLinkIndex);
            return;
        }

        pstMem      = ppstOutputLinkNode[ulOutputLinkIndex];

        if( pucFrmOutAddr != PPP_ZC_GET_DATA_PTR(pstMem) )
        {
            PPP_HDLC_ERROR_LOG("PPP_HDLC_HARD_FrmProcValidFram, ERROR, SOC copy error!\r\n");

            /* 释放申请的目的空间 */
            PPP_HDLC_HARD_CommReleaseLink(ppstOutputLinkNode + ulOutputLinkIndex,
                                          ulFrmOutSpaceCnt - ulOutputLinkIndex);
            return;
        }

        while( usFrmOutLen > 0 )
        {
            /* 从pstBuildInfo->apstOutputLinkNode取出头结点 pstMem */
            pstMem    = ppstOutputLinkNode[ulOutputLinkIndex];

            /* 单个输出链表结点所指目的空间的大小 */
            usDataLen = pstOutputParaLink[ulOutputLinkIndex].usDataLen;

            if( usFrmOutLen > usDataLen )
            {
                PPP_ZC_SET_DATA_LEN(pstMem, usDataLen);
                usFrmOutLen -= usDataLen;
            }
            else
            {
                PPP_ZC_SET_DATA_LEN(pstMem, usFrmOutLen);
                usFrmOutLen  = 0;
            }

            PPP_HDLC_ProcDlData(usPppId, pstMem);

            g_PppDataQCtrl.stStat.ulDownlinkSndDataCnt++;

            /* 将发送完的数据包从apstOutputLinkNode中清空 */
            ppstOutputLinkNode[ulOutputLinkIndex] = VOS_NULL_PTR;

            ulOutputLinkIndex++;
        }

        ucRptSpaceIndex++;
    }

    /* 释放剩余未利用的目的空间 */
    PPP_HDLC_HARD_CommReleaseLink(ppstOutputLinkNode + ulOutputLinkIndex,
                                  ulFrmOutSpaceCnt - ulOutputLinkIndex);

    return;
}

/*****************************************************************************
 函 数 名  : PPP_HDLC_HARD_FrmWaitAndProc
 功能描述  : 等待封装完成，然后处理输出数据,释放多余的目的空间内存
 输入参数  : ulEnableInterrupt  -   中断是否使能
             usPppId    -   PPP实体ID
             pstLink    -   PPP链路信息
 输出参数  : pstBuildInfo   -   构造链表的结果信息，保存输入链表长度、节点个数、零拷贝内存指针
 返 回 值  :
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2012年4月20日
    作    者   : c00191211
    修改内容   : 新生成函数

*****************************************************************************/
VOS_VOID PPP_HDLC_HARD_FrmWaitAndProc
(
    VOS_UINT32                           ulEnableInterrupt,
    PPP_ID                               usPppId,
    struct link                         *pstLink,
    HDLC_PARA_LINK_BUILD_INFO_STRU      *pstBuildInfo
)
{
    VOS_UINT32                          ulFrmStatus;


    /* 使能中断，则等待中断辅程序释放信号量；否则轮询解封装状态寄存器 */
    ulFrmStatus = PPP_HDLC_HARD_FrmWaitResult(ulEnableInterrupt);

    if ( HDLC_FRM_ALL_PKT_DONE == ulFrmStatus )
    {
        /* 处理有效帧，并释放剩余内存 */
        PPP_HDLC_HARD_FrmProcValidFrames(usPppId, pstBuildInfo);
    }
    else
    {
        /* 释放申请的目的空间 */
        PPP_HDLC_HARD_CommReleaseLink(pstBuildInfo->apstOutputLinkNode, pstBuildInfo->ulOutputLinkNodeCnt);

        /* 打印异常日志，挂起PPP任务 */
        PPP_HDLC_HARD_FrmProcException(ulFrmStatus, ulEnableInterrupt);
    }

    g_stHdlcRegSaveInfo.ulHdlcFrmRawInt = 0xFFFFFFFFU;
    g_stHdlcRegSaveInfo.ulHdlcFrmStatus = 0xFFFFFFFFU;

    return;
}

/*****************************************************************************
 函 数 名  : PPP_HDLC_HARD_FrmPacket
 功能描述  : IP模式下行封装处理流程
 输入参数  : usPppId        -   PPP实体ID
             usProtocol     -   待封装协议
             pstLink        -   PPP链路信息
             pstDataQ       -   PPP数据队列
 输出参数  : *pulDealCurCnt  -  指向当前处理的PPP队列中的结点个数
 返 回 值  : 无
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2012年4月20日
    作    者   : c00191211
    修改内容   : 新生成函数

*****************************************************************************/
VOS_UINT32 PPP_HDLC_HARD_FrmPacket
(
    PPP_ID              usPppId,
    VOS_UINT16          usProtocol,
    struct link        *pstLink,
    PPP_ZC_QUEUE_STRU  *pstDataQ,
    VOS_UINT32         *pulDealCurCnt
)
{
    VOS_UINT32                          ulEnableInterrupt;
    HDLC_PARA_LINK_BUILD_INFO_STRU      stBuildInfo;
    HDLC_PARA_LINK_BUILD_PARA_STRU      stBuildPara;
    VOS_UINT32                          ulBuildResult;
    HDLC_FRM_BUFF_INFO_STRU            *pstFrmBuffInfo;


    stBuildPara.ucDataType = PPP_PUSH_PACKET_TYPE;
    stBuildPara.usProtocol = usProtocol;
    stBuildPara.usPppId    = usPppId;
    stBuildPara.pstDataQ   = pstDataQ;

    /* 根据usPppId找到对应的内存 */
    pstFrmBuffInfo = HDLC_FRM_GET_BUF_INFO(usPppId);

    /* 构造输入输出参数链表，并上报链表内存可维可测 */
    ulBuildResult  = PPP_HDLC_HARD_FrmBuildParaLink(&stBuildPara, &stBuildInfo);

    *pulDealCurCnt = stBuildInfo.ulDealCnt;

    if (VOS_OK != ulBuildResult)
    {
        PPP_HDLC_WARNING_LOG("PPP_HDLC_HARD_FrmPacket, WARNING, BuildParaLink Fail.\r\n");
        return ulBuildResult;
    }

    g_PppHdlcHardStat.ulFrmMaxInputCntOnce   = TTF_MAX(g_PppHdlcHardStat.ulFrmMaxInputCntOnce, stBuildInfo.ulInputLinkNodeCnt);
    g_PppHdlcHardStat.ulFrmMaxInputSizeOnce  = TTF_MAX(g_PppHdlcHardStat.ulFrmMaxInputSizeOnce, stBuildInfo.ulInputLinkTotalSize);
    g_PppHdlcHardStat.ulFrmMaxOutputCntOnce  = TTF_MAX(g_PppHdlcHardStat.ulFrmMaxOutputCntOnce, stBuildInfo.ulOutputLinkNodeCnt);
    g_PppHdlcHardStat.ulFrmMaxOutputSizeOnce = TTF_MAX(g_PppHdlcHardStat.ulFrmMaxOutputSizeOnce, stBuildInfo.ulOutputLinkTotalSize);

    /* 配置封装、解封装通用寄存器 */
    PPP_HDLC_HARD_CommCfgReg();

    /* 配置内存相关寄存器 */
    PPP_HDLC_HARD_FrmCfgBufReg(pstFrmBuffInfo);

    /* 配置封装相关寄存器 */
    PPP_HDLC_HARD_FrmCfgReg(pstLink, usProtocol);

    /* 配置使能寄存器，并上报使能前寄存器可维可测 */
    ulEnableInterrupt = PPP_HDLC_HARD_FrmCfgEnReg(stBuildInfo.ulInputLinkTotalSize);

    /* 等待封装完成，然后处理输出数据,释放多余的目的空间内存 */
    PPP_HDLC_HARD_FrmWaitAndProc(ulEnableInterrupt, usPppId, pstLink, &stBuildInfo);

    /* 释放pstBuildInfo->apstInputLinkNode中的结点内存 */
    PPP_HDLC_HARD_CommReleaseLink(stBuildInfo.apstInputLinkNode, stBuildInfo.ulInputLinkNodeCnt);

    return VOS_OK;
}

/*****************************************************************************
 函 数 名  : PPP_HDLC_HARD_FrmRawPacket
 功能描述  : PPP模式下行封装处理流程
 输入参数  : usPppId        -   PPP实体ID
             usProtocol     -   待封装数据包协议
             pstLink        -   PPP链路信息
             pstDataQ       -   PPP数据队列
 输出参数  : *pulDealCurCnt  -  指向当前处理的PPP队列中的结点个数
 返 回 值  : 无
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2012年4月20日
    作    者   : c00191211
    修改内容   : 新生成函数

*****************************************************************************/
VOS_UINT32 PPP_HDLC_HARD_FrmRawData
(
    PPP_ID              usPppId,
    VOS_UINT16          usProtocol,
    struct link        *pstLink,
    PPP_ZC_QUEUE_STRU  *pstDataQ,
    VOS_UINT32         *pulDealCurCnt
)
{
    VOS_UINT32                          ulEnableInterrupt;
    HDLC_PARA_LINK_BUILD_INFO_STRU      stBuildInfo;
    HDLC_PARA_LINK_BUILD_PARA_STRU      stBuildPara;
    VOS_UINT32                          ulBuildResult;
    HDLC_FRM_BUFF_INFO_STRU            *pstFrmBuffInfo;


    stBuildPara.ucDataType = PPP_PUSH_RAW_DATA_TYPE;
    stBuildPara.usProtocol = usProtocol;
    stBuildPara.usPppId    = usPppId;
    stBuildPara.pstDataQ   = pstDataQ;

    /* 根据usPppId找到对应的内存  */
    pstFrmBuffInfo         = HDLC_FRM_GET_BUF_INFO(usPppId);

    /* 构造输入输出参数链表，并上报链表内存可维可测 */
    ulBuildResult  = PPP_HDLC_HARD_FrmBuildParaLink(&stBuildPara, &stBuildInfo);

    *pulDealCurCnt = stBuildInfo.ulDealCnt;

    if (VOS_OK != ulBuildResult)
    {
        return ulBuildResult;
    }


    g_PppHdlcHardStat.ulFrmMaxInputCntOnce   = TTF_MAX(g_PppHdlcHardStat.ulFrmMaxInputCntOnce, stBuildInfo.ulInputLinkNodeCnt);
    g_PppHdlcHardStat.ulFrmMaxInputSizeOnce  = TTF_MAX(g_PppHdlcHardStat.ulFrmMaxInputSizeOnce, stBuildInfo.ulInputLinkTotalSize);
    g_PppHdlcHardStat.ulFrmMaxOutputCntOnce  = TTF_MAX(g_PppHdlcHardStat.ulFrmMaxOutputCntOnce, stBuildInfo.ulOutputLinkNodeCnt);
    g_PppHdlcHardStat.ulFrmMaxOutputSizeOnce = TTF_MAX(g_PppHdlcHardStat.ulFrmMaxOutputSizeOnce, stBuildInfo.ulOutputLinkTotalSize);

    /* 配置封装、解封装通用寄存器 */
    PPP_HDLC_HARD_CommCfgReg();

    /* 配置内存相关寄存器 */
    PPP_HDLC_HARD_FrmCfgBufReg(pstFrmBuffInfo);

    /* 配置封装相关寄存器 */
    PPP_HDLC_HARD_FrmRawCfgReg(pstLink, usProtocol);

    /* 配置使能寄存器，并上报使能前寄存器可维可测 */
    ulEnableInterrupt = PPP_HDLC_HARD_FrmCfgEnReg(stBuildInfo.ulInputLinkTotalSize);

    /* 等待封装完成，然后处理输出数据,释放多余的目的空间内存 */
    PPP_HDLC_HARD_FrmWaitAndProc(ulEnableInterrupt, usPppId, pstLink, &stBuildInfo);

    /* 释放pstBuildInfo->apstInputLinkNode中的结点内存 */
    PPP_HDLC_HARD_CommReleaseLink(stBuildInfo.apstInputLinkNode, stBuildInfo.ulInputLinkNodeCnt);

    return VOS_OK;
}

/*****************************************************************************
 函 数 名  : PPP_HDLC_PROC_FUNC
 功能描述  : 硬件HDLC处理函数，在创建PPP实体的时候，根据需要可以灵活地将
             软件或硬件的实现与该实体关联
 输入参数  : usPppId    -   PPP实体ID
             pstLink    -   PPP链路信息
             pstDataQ   -   PPP数据队列
 输出参数  :
 返 回 值  : PPP_HDLC_RESULT_TYPE_ENUM_UINT32
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2012年4月10日
    作    者   : l00164359
    修改内容   : 新生成函数

*****************************************************************************/
PPP_HDLC_RESULT_TYPE_ENUM_UINT32 PPP_HDLC_HARD_ProcData
(
    PPP_ID              usPppId,
    struct link        *pstLink,
    PPP_ZC_QUEUE_STRU  *pstDataQ
)
{
    PPP_ZC_STRU                        *pstMem;
    VOS_UINT32                          ulDealTotalCnt;
    VOS_UINT32                          ulDealCurCnt;
    VOS_UINT32                          ulDealResult;
    VOS_UINT16                          usProtocol;
    PPP_DATA_TYPE_ENUM_UINT8            ucDataType;


    g_PppHdlcHardStat.ulHdlcHardProcCnt++;

    ulDealTotalCnt  = 0;
    ulDealCurCnt    = 0;

    for (;;)
    {
        pstMem  = (PPP_ZC_STRU *)PPP_ZC_PEEK_QUEUE_HEAD(pstDataQ);

        /* 队列为空的时候返回空指针 */
        if ( VOS_NULL_PTR == pstMem )
        {
            return PPP_HDLC_RESULT_COMM_FINISH;
        }

        /*处理该结点(结点的释放动作已经在各处理函数内部完成，无需再释放结点)*/
        ucDataType   = (PPP_ZC_GET_DATA_APP(pstMem) & 0x00FF);
        ulDealResult = VOS_OK;
        ulDealCurCnt = 0;

        switch ( ucDataType )
        {
            case PPP_PULL_PACKET_TYPE:

                ulDealResult = PPP_HDLC_HARD_DefPacket(usPppId, pstLink, pstDataQ, &ulDealCurCnt);

                g_PppHdlcHardStat.ulDefIpDataProcCnt += ulDealCurCnt;
                break;
            case PPP_PUSH_PACKET_TYPE:

                ulDealResult = PPP_HDLC_HARD_FrmPacket(usPppId, PROTO_IP, pstLink, pstDataQ, &ulDealCurCnt);

                g_PppHdlcHardStat.ulFrmIpDataProcCnt += ulDealCurCnt;
                break;
            case PPP_PULL_RAW_DATA_TYPE:

                ulDealResult = PPP_HDLC_HARD_DefRawData(usPppId, pstLink, pstDataQ, &ulDealCurCnt);

                g_PppHdlcHardStat.ulDefIpDataProcCnt += ulDealCurCnt;
                break;
            case PPP_PUSH_RAW_DATA_TYPE:

                /* 获取待封装数据包的协议值usProtocol */
                if (VOS_OK == PPP_HDLC_HARD_FrmGetProtocol(pstMem, &usProtocol))
                {
                    ulDealResult = PPP_HDLC_HARD_FrmRawData(usPppId, usProtocol, pstLink, pstDataQ, &ulDealCurCnt);

                    g_PppHdlcHardStat.ulFrmPppDataProcCnt += ulDealCurCnt;
                }
                else
                {
                    pstMem  = (PPP_ZC_STRU *)PPP_ZC_DEQUEUE_HEAD(pstDataQ);
                    PPP_MemFree(pstMem);
                }
                break;
            default:
                pstMem  = (PPP_ZC_STRU *)PPP_ZC_DEQUEUE_HEAD(pstDataQ);
                PPP_MemFree(pstMem);
                PPP_HDLC_WARNING_LOG1("PPP_HDLC_HARD_ProcData, WARNING, ucDataType %d is Abnormal!", ucDataType);
                break;
        }

        /*统计*/
        ulDealTotalCnt += ulDealCurCnt;

        if ( ulDealTotalCnt > g_PppHdlcHardStat.ulMaxCntOnce )
        {
            g_PppHdlcHardStat.ulMaxCntOnce = ulDealTotalCnt;
        }

        if (VOS_OK != ulDealResult)
        {
            PPP_HDLC_WARNING_LOG("PPP_HDLC_HARD_ProcData, WARNING, ulDealResult = ERROR!");
            break;
        }

        /*如果循环处理的结点个数超出了队列一次允许处理最大结点数，
          则退出循环并发送PPP_DATA_PROC_NOTIFY消息*/
        if ( (ulDealTotalCnt >= PPP_ONCE_DEAL_MAX_CNT) )
        {
            g_PppHdlcHardStat.ulContinueCnt++;
            return PPP_HDLC_RESULT_COMM_CONTINUE;
        }
    } /* for (;;) */

    return PPP_HDLC_RESULT_COMM_ERROR;
}

/*****************************************************************************
 函 数 名  : PPP_HDLC_HARD_SendAsFrmPacketMsg
 功能描述  : 消息发送函数
 输入参数  : usPppId        -- PPP实体ID
             usProtocol     -- 待封装协议值
             pstMem         -- 待封装数据包
 输出参数  : 无
 返 回 值  : 无
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2012年4月10日
    作    者   : l00164359
    修改内容   : 新生成函数

*****************************************************************************/
VOS_UINT32 PPP_HDLC_HARD_SendAsFrmPacketMsg
(
    VOS_UINT16       usPppId,
    VOS_UINT16       usProtocol,
    PPP_ZC_STRU     *pstMem
)
{
    HDLC_PROC_AS_FRM_PACKET_IND_MSG_STRU    *pstMsg;
    VOS_UINT32                               ulLength;


    ulLength    = sizeof(HDLC_PROC_AS_FRM_PACKET_IND_MSG_STRU) - VOS_MSG_HEAD_LENGTH;
    pstMsg      = (HDLC_PROC_AS_FRM_PACKET_IND_MSG_STRU *)PS_ALLOC_MSG(PS_PID_PPP_HDLC, ulLength);

    if (VOS_NULL_PTR == pstMsg)
    {
        /*打印出错信息---申请消息包失败:*/
        PPP_HDLC_ERROR_LOG("PPP_HDLC_HARD_SendMsg, ERROR: PS_ALLOC_MSG Failed!\r\n");
        return VOS_ERR;
    }

    /*填写消息头:*/
    pstMsg->MsgHeader.ulSenderCpuId   = VOS_LOCAL_CPUID;
    pstMsg->MsgHeader.ulSenderPid     = PS_PID_PPP_HDLC;
    pstMsg->MsgHeader.ulReceiverCpuId = VOS_LOCAL_CPUID;
    pstMsg->MsgHeader.ulReceiverPid   = PS_PID_PPP_HDLC;
    pstMsg->MsgHeader.ulLength        = ulLength;

    pstMsg->MsgHeader.ulMsgName       = PPP_HDLC_PROC_AS_FRM_PACKET_IND;
    /*填写消息体:*/
    pstMsg->usPppId                   = usPppId;
    pstMsg->usProtocol                = usProtocol;
    pstMsg->pstMem                    = pstMem;

    /*发送该消息*/
    if (VOS_OK != PS_SEND_MSG(PS_PID_PPP_HDLC, pstMsg))
    {
        /*打印警告信息---发送消息失败:*/
        PPP_HDLC_ERROR_LOG("PPP_HDLC_HARD_SendAsFrmPacketMsg, ERROR : PS_SEND_MSG Failed!");
        PPP_MemFree(pstMem);
        return VOS_ERR;
    }

    return VOS_OK;
}

/*****************************************************************************
 函 数 名  : PPP_HDLC_HARD_ProcProtocolPacket
 功能描述  : 当做下行封装处理
 输入参数  : usPppId        -- PPP实体ID
             usProtocol     -- 待封装协议值
             pstMem         -- 待封装数据包
 输出参数  : 无
 返 回 值  : 无
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2012年4月10日
    作    者   : l00164359
    修改内容   : 新生成函数

*****************************************************************************/
VOS_VOID PPP_HDLC_HARD_ProcAsFrmPacket
(
    VOS_UINT16       usPppId,
    VOS_UINT16       usProtocol,
    PPP_ZC_STRU     *pstMem
)
{
    VOS_UINT32              ulDealCurCnt;
    PPP_ZC_QUEUE_STRU       stDataQ;
    struct link            *pstLink;
    VOS_UINT32              ulDealResult;

    pstLink = PPP_LINK(usPppId);

    ulDealCurCnt = 0;

    /* 封装成下行IP类型数据包 */
    PPP_ZC_SET_DATA_APP(pstMem, (VOS_UINT16)(usPppId << 8) | (VOS_UINT16)PPP_PUSH_PACKET_TYPE);

    /* 初始化队列stDataQ, 并将 pstMem 入队 */
    PPP_ZC_QUEUE_INIT(&stDataQ);
    PPP_ZC_ENQUEUE_TAIL(&stDataQ, pstMem);

    /* 直接将该数据包封装后发送给PC */
    ulDealResult = PPP_HDLC_HARD_FrmPacket(usPppId, usProtocol, pstLink, &stDataQ, &ulDealCurCnt);

    if ((VOS_OK != ulDealResult) || (1 != ulDealCurCnt))
    {
        PPP_HDLC_ERROR_LOG2("PPP_HDLC_HARD_MakeFrmPacket, ERROR, ulDealResult %d ulDealCurCnt %d!\r\n",
                      ulDealResult, ulDealCurCnt);

        /* 说明因某种错误导致数据没有从队列中移出，需要释放 */
        if (0 < PPP_ZC_GET_QUEUE_LEN(&stDataQ))
        {
            PPP_MemFree(pstMem);
        }

        return;
    }

    g_PppHdlcHardStat.ulFrmIpDataProcCnt++;

    return;
}

/*****************************************************************************
 函 数 名  : PPP_HDLC_HARD_ProcProtocolPacket
 功能描述  : 硬件封装PPP协议栈输出的协议包
 输入参数  : pstLink    -   PPP链路信息
             pstMbuf    -   PPP协议栈输出的协议包
             ulPri      -   优先级
             usProto    -   数据包对应的协议
 输出参数  : 无
 返 回 值  : 无
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2012年4月10日
    作    者   : l00164359
    修改内容   : 新生成函数

*****************************************************************************/
VOS_VOID PPP_HDLC_HARD_ProcProtocolPacket
(
    struct link     *pstLink,
    struct ppp_mbuf *pstMbuf,
    VOS_INT32        ulPri,
    VOS_UINT16       usProtocol
)
{
    PPP_ZC_STRU            *pstMem;
    VOS_UINT16              usPppId;
    VOS_UINT32              ulFrmResult;
    VOS_UINT32              ulDefResult;


    usPppId = (VOS_UINT16)PPP_LINK_TO_ID(pstLink);

    pstMem  = ppp_m_alloc_ttfmem_from_mbuf(pstMbuf);

    ppp_m_freem(pstMbuf);
    pstMbuf  = VOS_NULL_PTR;

    /* for lint 438 */
    (VOS_VOID)pstMbuf;

    if (VOS_NULL_PTR == pstMem)
    {
        PPP_HDLC_WARNING_LOG("PPP_HDLC_HARD_ProcProtocolPacket, WARNING, pstMem is NULL!\r\n");
        return;
    }

    /* PPP协议栈回复的协商包需要封装后发给PC，确认此时是否封装与解封装都已经完成 */
    ulFrmResult     = PPP_HDLC_HARD_FrmIsEnabled();
    ulDefResult     = PPP_HDLC_HARD_DefIsEnabled();

    /* 此函数在上行解出协商包时，PPP协议栈产生应答，这个时候封装不应该使能 */
    if( (VOS_TRUE == ulFrmResult) || (VOS_TRUE == ulDefResult) )
    {
        PPP_HDLC_WARNING_LOG2("PPP_HDLC_HARD_ProcProtocolPacket, WARNING, ulFrmResult %d, ulDefResult %d!\r\n",
                      ulFrmResult, ulDefResult);
        PPP_HDLC_HARD_SendAsFrmPacketMsg(usPppId, usProtocol, pstMem);

        return;
    }

    /* 下次PPP任务调度的时候再封装此协商，那时封装与解封装都未使能 */
    PPP_HDLC_HARD_ProcAsFrmPacket(usPppId, usProtocol, pstMem);

    return;
}

/*****************************************************************************
 函 数 名  : PPP_PHY_TO_VIRT
 功能描述  : 将PPP中的物理地址转换为虚地址
 输入参数  : unsigned int ulPAddr   需要转换的物理地址
             g_ulPppPhyAddr         PPP物理地址基地址
 输出参数  : 无
 返 回 值  : 对应的虚地址
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2013年9月25日
    作    者   : x59651
    修改内容   : 新生成函数

*****************************************************************************/
VOS_UINT32 PPP_PHY_TO_VIRT(unsigned int ulPAddr)
{
    return (VOS_UINT32)phys_to_virt(ulPAddr);
}

/*****************************************************************************
 函 数 名  : PPP_VIRT_TO_PHY
 功能描述  : 将PPP中的虚地址转换为物理地址
 输入参数  : VOS_UINT_PTR ulVAddr   需要转换的虚地址
             g_ulPppVirtAddr        PPP虚地址基地址
 输出参数  : 无
 返 回 值  : 对应的物理地址
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2013年9月25日
    作    者   : x59651
    修改内容   : 新生成函数

*****************************************************************************/
VOS_UINT_PTR PPP_VIRT_TO_PHY(VOS_UINT_PTR ulVAddr)
{
    return virt_to_phys((void *)ulVAddr);
}

/*****************************************************************************
 函 数 名  : PPP_HDLC_NODE_PHY_TO_VIRT
 功能描述  : 将PPP中封装解封装的物理地址转换为虚地址
 输入参数  : unsigned int ulPAddr   需要转换的物理地址
 输出参数  : 无
 返 回 值  : 对应的虚地址
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2014年08月14日
    作    者   : g00178567
    修改内容   : 新生成函数

*****************************************************************************/
VOS_UINT32 PPP_HDLC_NODE_PHY_TO_VIRT(unsigned int ulPAddr)
{
    if ((ulPAddr >= g_ulPppPhyAddr) && (ulPAddr < (g_ulPppPhyAddr + TTF_HDLC_MASTER_LINK_TOTAL_LEN)))
    {
        return HDLC_DMA_PHY_TO_VIRT(ulPAddr);
    }
    else
    {
        PPP_HDLC_WARNING_LOG1("PPP_HDLC_NODE_PHY_TO_VIRT, WARNING, invalid ulPAddr 0x%x\r\n", ulPAddr);
        return g_ulPppPhyAddr;
    }
}


/*****************************************************************************
 函 数 名  : PPP_HDLC_NODE_VIRT_TO_PHY
 功能描述  : 将PPP中封装解封装的虚地址转换为物理地址
 输入参数  : unsigned int ulVAddr   需要转换的虚地址
 输出参数  : 无
 返 回 值  : 对应的物理地址
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2014年08月14日
    作    者   : g00178567
    修改内容   : 新生成函数

*****************************************************************************/
VOS_UINT32 PPP_HDLC_NODE_VIRT_TO_PHY(unsigned int ulVAddr)
{
    if ((ulVAddr >= g_ulPppVirtAddr) && (ulVAddr < (g_ulPppVirtAddr + TTF_HDLC_MASTER_LINK_TOTAL_LEN)))
    {
        return HDLC_DMA_VIRT_TO_PHY(ulVAddr);
    }
    else
    {
        PPP_HDLC_WARNING_LOG1("PPP_HDLC_NODE_VIRT_TO_PHY, WARNING, invalid ulVAddr 0x%x\r\n", ulVAddr);
        return g_ulPppVirtAddr;
    }
}


/*lint +e732*/
/*lint +e40*/
/*lint +e718*/
/*lint +e746*/

#endif

#ifdef __cplusplus
    #if __cplusplus
        }
    #endif
#endif


