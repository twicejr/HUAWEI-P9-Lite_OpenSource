/******************************************************************************

                  版权所有 (C), 2001-2015, 华为技术有限公司

 ******************************************************************************
  文 件 名   : DhcpLog.c
  版 本 号   : 初稿
  作    者   : w00316385
  生成日期   : 2015年9月30日
  最近修改   :
  功能描述   : DHCP trace保存输出
  函数列表   :
  修改历史   :
  1.日    期   : 2015年9月30日
    作    者   : w00316385
    修改内容   : 创建文件

******************************************************************************/



/*****************************************************************************
  1 头文件包含
*****************************************************************************/
#include "DhcpLog.h"
#include "msp_diag_comm.h"


/*****************************************************************************
    协议栈打印打点方式下的.C文件宏定义
*****************************************************************************/
#define    THIS_FILE_ID        PS_FILE_ID_DHCP_LOG_C


#ifdef __cplusplus
#if __cplusplus
extern "C" {
#endif
#endif


/*****************************************************************************
  2 全局变量定义
*****************************************************************************/
DHCP_LOG_ENT_STRU                   g_stDhcpLogEnt;                             /* DHCP任务打印实体 */


/*****************************************************************************
  3 函数实现
*****************************************************************************/
/*lint -save -e958 */

/*****************************************************************************
 函 数 名  : DHCP_MNTN_InitLogEnt
 功能描述  : 初始化LOG实体记录信息
 输入参数  : DHCP_LOG_ENT_STRU *pstLogEnt  LOG实体地址
 输出参数  :
 返 回 值  :
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2015年9月30日
    作    者   : w00316385
    修改内容   : 新生成函数

*****************************************************************************/
VOS_VOID DHCP_MNTN_InitLogEnt(DHCP_LOG_ENT_STRU *pstLogEnt)
{
    VOS_INT32                          lLockKey;

    /* 加锁 */
    lLockKey            = VOS_SplIMP();

    pstLogEnt->ulCnt    = 0;

    /* 解锁 */
    VOS_Splx(lLockKey);

    return;
}

/*****************************************************************************
 函 数 名  : DHCP_MNTN_LogSave
 功能描述  : 保存1条LOG记录信息
 输入参数  :
            DHCP_LOG_ENT_STRU              *pstLogEnt,  LOG实体地址
            VOS_UINT32                      ulPid,      当前待输出LOG记录所属PID
            LOG_LEVEL_EN                    enLevel,    LOG记录告警级别
            PS_FILE_ID_DEFINE_ENUM_UINT32   enFile,     LOG记录所属文件名
            VOS_UINT32                      ulLine,     LOG记录所属文件行号
            VOS_INT32                       lpara1,     LOG记录携带参数
            VOS_INT32                       lpara2,     LOG记录携带参数
            VOS_INT32                       lpara3,     LOG记录携带参数
            VOS_INT32                       lpara4      LOG记录携带参数
 输出参数  :
 返 回 值  :
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2015年9月30日
    作    者   : w00316385
    修改内容   : 新生成函数

*****************************************************************************/
VOS_VOID DHCP_MNTN_LogSave
(
    DHCP_LOG_ENT_STRU              *pstLogEnt,
    VOS_UINT32                      ulPid,
    LOG_LEVEL_EN                    enLevel,
    PS_FILE_ID_DEFINE_ENUM_UINT32   enFile,
    VOS_UINT32                      ulLine,
    VOS_INT32                       lpara1,
    VOS_INT32                       lpara2,
    VOS_INT32                       lpara3,
    VOS_INT32                       lpara4
)
{
    VOS_UINT32                      ulCnt;
    VOS_UINT32                      ulCurrentSlice;
    VOS_INT32                       lLockKey;

    /* 加锁 */
    lLockKey        = VOS_SplIMP();

    ulCnt           = pstLogEnt->ulCnt;

    ulCurrentSlice  = mdrv_timer_get_normal_timestamp();
    if( ulCnt < DHCP_LOG_RECORD_MAX_NUM )
    {
        pstLogEnt->astData[ulCnt].ulTick        = ulCurrentSlice;
        pstLogEnt->astData[ulCnt].enFile        = enFile;
        pstLogEnt->astData[ulCnt].ulLine        = ulLine;
        pstLogEnt->astData[ulCnt].enLevel       = enLevel;
        pstLogEnt->astData[ulCnt].alPara[0]     = lpara1;
        pstLogEnt->astData[ulCnt].alPara[1]     = lpara2;
        pstLogEnt->astData[ulCnt].alPara[2]     = lpara3;
        pstLogEnt->astData[ulCnt].alPara[3]     = lpara4;
        ulCnt++;
        pstLogEnt->ulCnt                        = ulCnt;
    }

    /* 解锁 */
    VOS_Splx(lLockKey);

    /* 记录满了，自动发送 */
    if( ulCnt >= DHCP_LOG_RECORD_MAX_NUM )
    {
        DHCP_MNTN_LogOutput(pstLogEnt, ulPid);
    }

    return;
}

/*****************************************************************************
 函 数 名  : DHCP_MNTN_LogOutput
 功能描述  : 输出LOG记录信息
 输入参数  :
            DHCP_LOG_ENT_STRU              *pstLogEnt,  LOG实体地址
            VOS_UINT32                      ulPid,      当前待输出LOG记录所属PID
 输出参数  :
 返 回 值  :
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2015年9月30日
    作    者   : w00316385
    修改内容   : 新生成函数

*****************************************************************************/
VOS_VOID DHCP_MNTN_LogOutput(DHCP_LOG_ENT_STRU *pstLogEnt, VOS_UINT32 ulPid)
{
    CTTF_DHCP_TRACE_LOG_MSG_STRU        stDhcpTraceLogMsg;


    /*  避免递归死循环 */
    if( (pstLogEnt->ulCnt > DHCP_LOG_RECORD_MAX_NUM) || (0 == pstLogEnt->ulCnt) )
    {
        DHCP_MNTN_InitLogEnt(pstLogEnt);
        return ;
    }

    stDhcpTraceLogMsg.ulSenderCpuId     = VOS_LOCAL_CPUID;
    stDhcpTraceLogMsg.ulSenderPid       = ulPid;
    stDhcpTraceLogMsg.ulReceiverCpuId   = VOS_LOCAL_CPUID;
    stDhcpTraceLogMsg.ulReceiverPid     = ulPid;
    stDhcpTraceLogMsg.ulLength          = (sizeof(CTTF_DHCP_TRACE_LOG_MSG_STRU) - VOS_MSG_HEAD_LENGTH);
    stDhcpTraceLogMsg.usMsgType         = ID_CTTF_DHCP_TRACE_LOG_MSG;
    stDhcpTraceLogMsg.usTransId         = 0;

    (VOS_VOID)mdrv_memcpy( &stDhcpTraceLogMsg.stLogMsgCont, pstLogEnt, sizeof(DHCP_LOG_ENT_STRU) );

    (VOS_VOID)DIAG_TraceReport(&stDhcpTraceLogMsg);

    DHCP_MNTN_InitLogEnt(pstLogEnt);

    return ;
}




/*lint -restore */

#ifdef __cplusplus
    #if __cplusplus
        }
    #endif
#endif

