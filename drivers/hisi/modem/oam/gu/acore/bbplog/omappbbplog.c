

/******************************************************************************

                  版权所有 (C), 2001-2013, 华为技术有限公司

 ******************************************************************************
  文 件 名      : ombbplogapp.c
  版 本 号      : 初稿
  作    者      : 蒋德彬 00174725
  生成日期      : 2012年11月16日
  最近修改      :
  功能描述      : BBP采数与可维可测相关函数实现
  函数列表      :
  修改历史      :
  1.日    期    : 2012年11月16日
    作    者    : 蒋德彬 00174725
    修改内容    : 创建文件

******************************************************************************/
/*****************************************************************************
  1 头文件包含
*****************************************************************************/
#include "vos.h"
#include "omprivate.h"
#include "ombbplog.h"
#include "phyoaminterface.h"
#include "pamappom.h"

#ifdef __cplusplus
#if __cplusplus
extern "C"{
#endif
#endif


/*lint -e767 修改人：蒋德彬 */
#define    THIS_FILE_ID        PS_FILE_ID_OM_APP_BBP_LOG_C
/*lint +e767 修改人：蒋德彬 */

/*****************************************************************************
  2 全局变量定义
*****************************************************************************/
/* 记录从底软获取到的DUMP内存地址和大小 */
BBP_DUMP_GET_FIX_DDR_ADDR               g_stBbpDumpFixDdr;

/*****************************************************************************
  3 外部函数声明
*****************************************************************************/


/*****************************************************************************
  4 消息处理函数映射表
*****************************************************************************/


/*****************************************************************************
  5 函数实现
*****************************************************************************/

/*****************************************************************************
 函 数 名  : Om_AcpuQueryDumpMsgProc
 功能描述  : CCpu查询Dump信息响应函数
 输入参数  : pMsg

 输出参数  : NA

 返 回 值  : VOS_VOID

 修改历史      :
  1.日    期   : 2014年10月08日
    作    者   : d00212987
    修改内容   : BBP采数项目新增
*****************************************************************************/
VOS_VOID Om_AcpuQueryDumpMsgProc(MsgBlock* pMsg)
{
    BBP_DUMP_MSG_STRU                  *pstBbpDumpMsg;
    VOS_UINT16                          usPrimId;

    usPrimId = *(VOS_UINT16*)(pMsg->aucValue);
    if (BBP_QUERY_DUMP_INFO_REQ == usPrimId)
    {
        /* 申请消息发送给CCPU */
        pstBbpDumpMsg = (BBP_DUMP_MSG_STRU*)VOS_AllocMsg(ACPU_PID_PAM_OM,
                                sizeof(BBP_DUMP_MSG_STRU) - VOS_MSG_HEAD_LENGTH);

        /* 分配消息失败 */
        if (VOS_NULL_PTR == pstBbpDumpMsg)
        {
            return;
        }

        pstBbpDumpMsg->ulReceiverPid           = CCPU_PID_PAM_OM;
        pstBbpDumpMsg->usPrimId                = BBP_QUERY_DUMP_INFO_CNF;
        pstBbpDumpMsg->stDumpDdrInfo.ulPhyAddr = g_stBbpDumpFixDdr.ulPhyAddr;
        pstBbpDumpMsg->stDumpDdrInfo.ulPhySize = g_stBbpDumpFixDdr.ulPhySize;

        (VOS_VOID)VOS_SendMsg(ACPU_PID_PAM_OM, pstBbpDumpMsg);
    }

    return;
}

/*lint -save -e102 -e10 -e2 -e40 -e533 -e31 -e830 -e522 -e718 -e746 -e702 -e565  -e64 -e23 -e63 -e26 -e578 -e132 -e19 -e18 -e34 -e35 -e713*/
extern unsigned long simple_strtoul(const char *cp, char **endp, unsigned int base);

#if (!defined(DMT)) && (VOS_WIN32 != VOS_OS_VER)
/*****************************************************************************
* 函 数 名  : Om_QueryDumpPhyAddr
*
* 功能描述  : 在代码编译阶段将CMD LINE中的DumpPhyAddr地址解析出来
*
* 输入参数  : 无
*
* 输出参数  : 无
*
* 返 回 值  : 无
*****************************************************************************/
VOS_INT __init Om_QueryDumpPhyAddr(VOS_CHAR *pucChar)
{
    g_stBbpDumpFixDdr.ulPhyAddr = (VOS_UINT32)simple_strtoul(pucChar, VOS_NULL, VOS_NULL);

    /* 物理地址是32位的实地址并且是8字节对齐的 */
    if ((VOS_NULL != (g_stBbpDumpFixDdr.ulPhyAddr % 4))
        || (VOS_NULL == g_stBbpDumpFixDdr.ulPhyAddr))
    {
        g_stBbpDumpFixDdr.ulPhyAddr = VOS_NULL;
    }

    return 0;
}

early_param("mdmreglogbase", Om_QueryDumpPhyAddr);
#endif

#if (!defined(DMT)) && (VOS_WIN32 != VOS_OS_VER)
/*****************************************************************************
* 函 数 名  : SocpLogTimeoutParse
*
* 功能描述  : 在代码编译阶段将CMD LINE中的TIMEOUT大小参数解析出来
*
* 输入参数  : 无
*
* 输出参数  : 无
*
* 返 回 值  : 无
*****************************************************************************/
VOS_INT __init Om_QueryDumpPhySize(VOS_CHAR *pucChar)
{
    /* Buffer的大小以Byte为单位 */
    g_stBbpDumpFixDdr.ulPhySize = (VOS_UINT32)simple_strtoul(pucChar, VOS_NULL, VOS_NULL);

    return 0;
}

early_param("mdmreglogsize", Om_QueryDumpPhySize);
#endif
/*lint -restore */

/*****************************************************************************
 函 数 名  : Om_AcpuPhyMsgProc
 功能描述  :
 输入参数  : MsgBlock* pMsg
 输出参数  : 无
 返 回 值  :
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2015年1月22日
    作    者   : s00207770
    修改内容   : 新生成函数

*****************************************************************************/
VOS_VOID  Om_AcpuPhyMsgProc( MsgBlock* pMsg )
{
    WPHY_OAM_QUERY_SAMPLE_REQ_STRU     *pstReqMsg;
    WPHY_OAM_QUERY_SAMPLE_CNF_STRU     *pstCnfMsg;

    pstReqMsg   = (WPHY_OAM_QUERY_SAMPLE_REQ_STRU*)pMsg;

    if (ID_OAM_WPHY_QUERY_SAMPLE_REQ == pstReqMsg->enMsgId)
    {
        pstCnfMsg   = (WPHY_OAM_QUERY_SAMPLE_CNF_STRU*)VOS_AllocMsg(ACPU_PID_PAM_OM, sizeof(WPHY_OAM_QUERY_SAMPLE_CNF_STRU) - VOS_MSG_HEAD_LENGTH);

        if (VOS_NULL_PTR == pstCnfMsg)
        {
            PS_LOG(ACPU_PID_PAM_OM, 0, PS_PRINT_ERROR,
                "Om_AcpuPhyMsgProc: Msg alloc Error.\n");
            return;
        }

        pstCnfMsg->ulReceiverPid    = pstReqMsg->ulSenderPid;
        pstCnfMsg->enMsgId          = ID_WPHY_OAM_QUERY_SAMPLE_CNF;

        if (VOS_NULL_PTR != g_stBbpDumpFixDdr.ulPhyAddr)
        {
            pstCnfMsg->esRslt       = VOS_TRUE;
            pstCnfMsg->ulPhyAddr    = g_stBbpDumpFixDdr.ulPhyAddr;
            pstCnfMsg->ulPhySize    = g_stBbpDumpFixDdr.ulPhySize;
        }
        else
        {
            pstCnfMsg->esRslt   = VOS_FALSE;
        }

        if (VOS_OK != VOS_SendMsg(ACPU_PID_PAM_OM, pstCnfMsg))
        {
            PS_LOG(ACPU_PID_PAM_OM, 0, PS_PRINT_ERROR,
                "Om_AcpuPhyMsgProc: Send Msg Error.\n");
        }

        return;
    }

    return;
}

#ifdef __cplusplus
#if __cplusplus
}
#endif
#endif

