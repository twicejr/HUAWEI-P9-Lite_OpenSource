/******************************************************************************

                  版权所有 (C), 2001-2011, 华为技术有限公司

 ******************************************************************************
  文 件 名   : ImsNic.c
  版 本 号   : 初稿
  作    者   : caikai
  生成日期   : 2013年7月22日
  最近修改   :
  功能描述   : VoLTE特性中IMS虚拟网卡的处理
  函数列表   :
  修改历史   :
  1.日    期   : 2013年7月22日
    作    者   : caikai
    修改内容   : 创建文件

******************************************************************************/

#ifdef __cplusplus
#if __cplusplus
extern "C" {
#endif
#endif


/*****************************************************************************
  1 头文件包含
*****************************************************************************/
#include "IpsMntnCCore.h"

#if ( FEATURE_ON == FEATURE_IMS )
#include "mdrv.h"
#include <stdio.h>

#if ((VOS_OS_VER == VOS_WIN32) && (VOS_PC_TEST == VOS_RTOSCK))
#include "VxWorksStub.h"
#include "tcpip/public/tcpip_sock.h"
#elif (VOS_OS_VER == VOS_WIN32)
#include "VxWorksStub.h"
#elif (VOS_OS_VER == VOS_RTOSCK)
#include "v_sock.h"
#else
#include "muxLib.h"
#include "endLib.h"
#include "v_sock.h"
#endif

/*lint -e534*/
/*****************************************************************************
    协议栈打印打点方式下的.C文件宏定义
*****************************************************************************/
#define         THIS_FILE_ID            PS_FILE_ID_IMS_NIC_C

#define         IMS_NIC_OK              (0)
#define         IMS_NIC_ERR             (1)
#define         IMS_NIC_ERROR           (-1)

/* 调试时使用的打印开关 */
VOS_UINT8       g_ucImsNicDebugPrint    = 0;

/* 调试打印 */
#define IMS_NIC_DEBUG_PRINT(...)\
        {\
            if ( 1 ==  g_ucImsNicDebugPrint)\
            {\
                (VOS_VOID)vos_printf(__VA_ARGS__);\
            }\
        }

/*****************************************************************************
  2 全局变量定义
*****************************************************************************/
IMS_NIC_ENTITY_STRU                     g_astImsNicEntity[IMS_NIC_MODEM_ID_BUTT] = {{0}};  /* IMS虚拟网卡实体信息 */

const IMS_NIC_MANAGE_TBL_STRU           g_stImsNicManageTbl    =
{
    "ims_nic0",
    {
        {
            {
                {
                    0x58, 0x02, 0x03, 0x04, 0x05, 0x06
                },
                {
                    0x00, 0x11, 0x09, 0x64, 0x01, 0x01
                },
                0x0008
            },
            {
                {
                    0x58, 0x02, 0x03, 0x04, 0x05, 0x06
                },
                {
                    0x00, 0x11, 0x09, 0x64, 0x01, 0x01
                },
                0xDD86
            }
        }
    }
};


IMS_NIC_CTX_STRU    g_stImsNicCtx   =
{
    IMS_NIC_MTU_DEFAULT_VALUE,
    0,
    0,
    {
        VOS_NULL_PTR
    }
};

IMS_NIC_DEV_STRU                        g_astImsNicDev[IMS_NIC_MODEM_ID_BUTT];                  /* 虚拟网卡设备空间 */

/* DNS系统变量名 */
VOS_CHAR                               *g_pcDnsSSysVarName[IMS_NIC_MAX_DNS_SERVER_NUM] =
{
        "ipdnsc.primaryns",
        "ipdnsc.secondaryns",
        "ipdnsc.tertiaryns",
        "ipdnsc.quaternaryns",
        "ipdnsc.quinaryns",
        "ipdnsc.senaryns"
};

/*****************************************************************************
  3 函数实现
*****************************************************************************/
/*lint -save -e958 */

#ifdef  ST_IMS_NIC
extern VOS_VOID  ST_IMS_NIC_InitQ(VOS_VOID);
extern VOS_UINT32  ST_IMS_NIC_PrintData( VOS_UINT8 *pData, VOS_UINT16 usLen );
#endif


/*****************************************************************************
 函 数 名  : IMS_NIC_MNTN_InitLogCnt
 功能描述  : 初始化LOG实体记录信息
 输入参数  : IMS_NIC_LOG_ENT_STRU *pstLogEnt  LOG实体地址
 输出参数  :
 返 回 值  :
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2013年8月9日
    作    者   : t00148005
    修改内容   : 新生成函数

*****************************************************************************/
VOS_VOID IMS_NIC_MNTN_InitLogCnt(IMS_NIC_LOG_ENT_STRU *pstLogEnt)
{
    if(VOS_OK != VOS_SmP(g_stImsNicCtx.ulInitLogMutexSem, 0))
    {
        return;
    }

    pstLogEnt->ulCnt = 0;

    (VOS_VOID)VOS_SmV(g_stImsNicCtx.ulInitLogMutexSem);

    return;
}

/*****************************************************************************
 函 数 名  : IMS_NIC_MNTN_LogOutput
 功能描述  : 输出LOG记录信息
 输入参数  :
             IMS_NIC_LOG_ENT_STRU           *pstLogEnt,  LOG实体地址
             VOS_UINT32                      ulPid,      当前待输出LOG记录所属PID
 输出参数  :
 返 回 值  :
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2013年8月9日
    作    者   : t00148005
    修改内容   : 新生成函数

*****************************************************************************/
VOS_VOID IMS_NIC_MNTN_LogOutput(IMS_NIC_LOG_ENT_STRU *pstLogEnt, VOS_UINT32 ulPid)
{
    IMS_NIC_TRACE_LOG_MSG_STRU          stImsTraceLogMsg;


    /*  避免递归死循环 */
    if( (pstLogEnt->ulCnt > IMS_NIC_LOG_RECORD_MAX_NUM) || (0 == pstLogEnt->ulCnt) )
    {
        IMS_NIC_MNTN_InitLogCnt(pstLogEnt);

        return;
    }

    stImsTraceLogMsg.ulSenderCpuId     = VOS_LOCAL_CPUID;
    stImsTraceLogMsg.ulSenderPid       = ulPid;
    stImsTraceLogMsg.ulReceiverCpuId   = VOS_LOCAL_CPUID;
    stImsTraceLogMsg.ulReceiverPid     = ulPid;
    stImsTraceLogMsg.ulLength          = (sizeof(IMS_NIC_TRACE_LOG_MSG_STRU) - VOS_MSG_HEAD_LENGTH);

    stImsTraceLogMsg.usMsgType         = ID_IMS_NIC_MNTN_TRACE_LOG_MSG;
    stImsTraceLogMsg.usTransId         = 0;

    (VOS_VOID)mdrv_memcpy( &stImsTraceLogMsg.stLogMsgCont, pstLogEnt, sizeof(IMS_NIC_LOG_ENT_STRU) );

    DIAG_TraceReport(&stImsTraceLogMsg);

    IMS_NIC_MNTN_InitLogCnt(pstLogEnt);

    return ;
}


/*****************************************************************************
 函 数 名  : IMS_NIC_MNTN_LogSave
 功能描述  : 保存1条LOG记录信息
 输入参数  :
            IMS_NIC_LOG_ENT_STRU           *pstLogEnt,  LOG实体地址
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
  1.日    期   : 2011年11月23日
    作    者   : t00148005
    修改内容   : 新生成函数

*****************************************************************************/
VOS_VOID IMS_NIC_MNTN_LogSave
(
    IMS_NIC_LOG_ENT_STRU           *pstLogEnt,
    VOS_UINT32                      ulPid,
    VOS_UINT32                      enLevel,
    PS_FILE_ID_DEFINE_ENUM_UINT32   enFile,
    VOS_UINT32                      ulLine,
    VOS_INT32                       lpara1,
    VOS_INT32                       lpara2,
    VOS_INT32                       lpara3,
    VOS_INT32                       lpara4
)
{
    VOS_UINT32      ulCnt;
    VOS_UINT32      ulCurrentSlice;

    ulCurrentSlice  = mdrv_timer_get_normal_timestamp();

    if(VOS_OK != VOS_SmP(g_stImsNicCtx.ulSaveLogMutexSem, 0))
    {
        return;
    }

    ulCnt           = pstLogEnt->ulCnt;

    if( ulCnt < IMS_NIC_LOG_RECORD_MAX_NUM )
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

    VOS_SmV(g_stImsNicCtx.ulSaveLogMutexSem);

    /* 记录满了，自动发送 */
    if( ulCnt >= IMS_NIC_LOG_RECORD_MAX_NUM )
    {
        IMS_NIC_MNTN_LogOutput(pstLogEnt, ulPid);
    }

    return;
}

/*****************************************************************************
 函 数 名  : IMS_NIC_MntnTrace
 功能描述  : 可维可测，将数据TRACE到SDT
 输入参数  : VOS_UINT16 usMsgId     消息ID
             VOS_UINT8  *pucData    消息内容指针
             VOS_UINT32 ulLen       消息数据内容长度

 输出参数  : 无
 返 回 值  : 无
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2013年7月16日
    作    者   : t00148005
    修改内容   : 新生成函数
*****************************************************************************/
VOS_VOID IMS_NIC_MntnTrace(VOS_UINT16 usMsgId, VOS_UINT8 *pucData, VOS_UINT32 ulLen, VOS_UINT32 ulPara1, VOS_UINT32 ulPara2)
{
    IMS_NIC_MNTN_TRACE_MSG_STRU *pstMntnTrace;
    VOS_UINT32                   ulMsgLen;


    ulMsgLen = IMS_NIC_MNTN_TRACE_DATA_OFFSET_LEN + ulLen;

    pstMntnTrace = (IMS_NIC_MNTN_TRACE_MSG_STRU *)PS_MEM_ALLOC(UEPS_PID_IMSNIC, ulMsgLen);

    if (VOS_NULL_PTR == pstMntnTrace)
    {
        IMS_NIC_WARNING_LOG(UEPS_PID_IMSNIC, "IMS_NIC_MntnTrace, WARNING, Alloc msg fail.");

        return;
    }

    pstMntnTrace->ulReceiverPid        = UEPS_PID_IMSNIC;
    pstMntnTrace->ulSenderPid          = UEPS_PID_IMSNIC;
    pstMntnTrace->ulSenderCpuId        = VOS_LOCAL_CPUID;
    pstMntnTrace->ulReceiverCpuId      = VOS_LOCAL_CPUID;
    pstMntnTrace->ulLength             = ulMsgLen - VOS_MSG_HEAD_LENGTH;
    pstMntnTrace->usMsgId              = usMsgId;
    pstMntnTrace->ulPara1              = ulPara1;
    pstMntnTrace->ulPara2              = ulPara2;

    if (VOS_NULL_PTR != pucData)
    {
        (VOS_VOID)mdrv_memcpy(pstMntnTrace->aucData, pucData, ulLen);
    }

    DIAG_TraceReport(pstMntnTrace);

    PS_MEM_FREE(UEPS_PID_IMSNIC, pstMntnTrace);
}

/*****************************************************************************
 函 数 名  : IMS_NIC_MNTN_LogEntInit
 功能描述  : 创建互斥信号量,LOG实体初始化
 输入参数  :
 输出参数  : 无
 返 回 值  : VOS_OK/VOS_ERR
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2013年8月9日
    作    者   : t00148005
    修改内容   : 新生成函数

*****************************************************************************/
VOS_UINT32 IMS_NIC_MNTN_LogEntInit(VOS_UINT32 ulPid)
{
    VOS_UINT32      ulResult;


    PS_MEM_SET(&g_stImsNicCtx.stLogEnt, 0, sizeof(IMS_NIC_LOG_ENT_STRU));

    ulResult    = VOS_SmMCreate("INIT", VOS_SEMA4_FIFO,
                    (VOS_SEM *)(&g_stImsNicCtx.ulInitLogMutexSem));

    if ( VOS_OK != ulResult )
    {
        IMS_NIC_INIT_LOG_PRINT1(ulPid, "IMS_NIC_MNTN_CreateMutexSem: Create g_ulInitLogMutexSem fail!", ulResult);

        return VOS_ERR;
    }

    ulResult    = VOS_SmMCreate("SAVE", VOS_SEMA4_FIFO,
                    (VOS_SEM *)(&g_stImsNicCtx.ulSaveLogMutexSem));

    if ( VOS_OK != ulResult )
    {
        IMS_NIC_INIT_LOG_PRINT1(ulPid, "IMS_NIC_MNTN_CreateMutexSem: Create g_ulLogSaveMutexSem fail!", ulResult);

        return VOS_ERR;
    }

    return VOS_OK;
}

/*****************************************************************************
 函 数 名  : IMS_NIC_I2A
 功能描述  : 根据转换基数(10或16), 将整数转换为ASCII码, 将结果输出至字符串
 输入参数  : usValue    - 待转换为ASCII码的整数
             pcStr      - 输出结果的字符串
             usRadix    - 转换基数
 输出参数  : 无
 返 回 值  : VOS_CHAR*
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2013年7月16日
    作    者   : caikai
    修改内容   : 新生成函数
*****************************************************************************/
VOS_CHAR* IMS_NIC_I2A(VOS_UINT16 usValue, VOS_CHAR *pcStr, VOS_UINT16 usRadix)
{
    if (IMS_NIC_TYPE_HEX == usRadix)
    {
        pcStr += VOS_sprintf(pcStr, "%x", usValue);
    }
    else if(IMS_NIC_TYPE_DEC == usRadix)
    {
        pcStr += VOS_sprintf(pcStr, "%d", usValue);
    }
    else
    {
        IMS_NIC_WARNING_LOG1(UEPS_PID_IMSNIC, "IMS_NIC_I2A, WARNING, usRadix is Invalid", usRadix);
    }

    return pcStr;
}

/*****************************************************************************
 函 数 名  : IMS_NIC_FindIpv6AddrZeroFieldsToBeCompressed
 功能描述  : 找出需要使用"::"表示的IP地址段的起始位置
 输入参数  : ausAddrValue[]     - IPV6地址段数组
             ucTokensNum        - 地址段个数
 输出参数  : pucZeroFieldStart  - 数值连续为0的IP地址段起始位置
             pucZeroFieldCount  - 数值连续为0的IP地址段个数
 返 回 值  : VOS_VOID
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2013年7月16日
    作    者   : caikai
    修改内容   : 新生成函数

*****************************************************************************/
VOS_VOID IMS_NIC_FindIpv6AddrZeroFieldsToBeCompressed(
    VOS_UINT8                          *pucZeroFieldStart,
    VOS_UINT8                          *pucZeroFieldCount,
    VOS_UINT16                         *pusAddrValue,
    VOS_UINT8                           ucTokensNum
)
{
    VOS_UINT32                          ulIndx;
    VOS_UINT8                           ucStart;
    VOS_UINT8                           ucCount;


    ucStart                             = 0xFF;
    ucCount                             = 0;

    for (ulIndx = 0; ulIndx < (VOS_UINT32)(ucTokensNum - 1); ulIndx++)
    {
        if ( (0x0000 == pusAddrValue[ulIndx])
          && (0x0000 == pusAddrValue[ulIndx + 1]) )
        {
            /* 记录数值连续为0的IP地址段起始位置 */
            if (0xFF == ucStart)
            {
                ucStart = (VOS_UINT8)ulIndx;
            }

            /* 更新数值连续为0的IP地址段个数 */
            ucCount++;
        }
        else
        {
            /* 更新待压缩的IP地址段位置, 以及IP地址段个数 */
            if (0xFF != ucStart)
            {
                if (ucCount > *pucZeroFieldCount)
                {
                    *pucZeroFieldStart = ucStart;
                    *pucZeroFieldCount = ucCount;
                }

                ucStart = 0xFF;
                ucCount = 0;
            }
        }
    }

    /* 数值连续为0的IP地址段在结尾时, 需要更新一次待压缩的IP地址段位置,
       以及IP地址段个数 */
    if (0xFF != ucStart)
    {
        if (ucCount > *pucZeroFieldCount)
        {
            *pucZeroFieldStart = ucStart;
            *pucZeroFieldCount = ucCount;
        }
    }
}


/*****************************************************************************
 函 数 名  : IMS_NIC_ConvertIpv6AddrToCompressedStr
 功能描述  : 将IPV6地址格式转换为字符串压缩格式
 输入参数  : aucIpAddr[]    - IPV6地址(协议格式)
             ucTokensNum    - 地址段个数
 输出参数  : aucAddrStr[]   - IPV6地址(字符串格式)
 返 回 值  : VOS_VOID
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2013年7月16日
    作    者   : caikai
    修改内容   : 新生成函数

*****************************************************************************/
VOS_VOID IMS_NIC_ConvertIpv6AddrToCompressedStr(
    VOS_UINT8                          *pucAddrStr,
    VOS_UINT8                          *pucIpAddr,
    VOS_UINT8                           ucTokensNum
)
{
    VOS_UINT8                          *pucBuffer;
    VOS_UINT32                          ulIndx;
    VOS_UINT16                          ausAddrValue[IMS_NIC_IPV6_STR_RFC2373_TOKENS]; /* IMS_NIC_IPV6_STR_RFC2373_TOKENS]; */
    VOS_UINT16                          usAddrNum;
    VOS_UINT8                           ucDelimiter;
    VOS_UINT8                           ucRadix;
    VOS_UINT8                           ucZeroFieldStart;
    VOS_UINT8                           ucZeroFieldCount;


    PS_MEM_SET(ausAddrValue, 0x00, sizeof(ausAddrValue));

    pucBuffer                           = pucAddrStr;
    ucDelimiter                         = IMS_NIC_IPV6_STR_DELIMITER;
    ucRadix                             = IMS_NIC_TYPE_HEX;
    ucZeroFieldStart                    = 0xFF;
    ucZeroFieldCount                    = 0;

    /* 根据IP字符串格式表达类型, 获取分段的IP地址数值 */
    for (ulIndx = 0; ulIndx < ucTokensNum; ulIndx++)
    {
        usAddrNum = *pucIpAddr++;

        usAddrNum <<= 8;
        usAddrNum  |= *pucIpAddr++;

        ausAddrValue[ulIndx] = usAddrNum;
    }

    /* 找出需要使用"::"表示的IP地址段的起始位置  */
    IMS_NIC_FindIpv6AddrZeroFieldsToBeCompressed(&ucZeroFieldStart, &ucZeroFieldCount, ausAddrValue, ucTokensNum);

    /* 遍历IP地址分段, 创建有分隔符标记的IP地址字符串 */
    for (ulIndx = 0; ulIndx < ucTokensNum; ulIndx++)
    {
        if (ucZeroFieldStart == ulIndx)
        {
            *pucBuffer++ = ucDelimiter;

            ulIndx += ucZeroFieldCount;

            /* 如果已到IP地址分段的最后一段, 需要补充分隔符 */
            if ((ucTokensNum - 1) == ulIndx)
            {
                *pucBuffer++ = ucDelimiter;
            }
        }
        else
        {
            /* 如果是IP地址分段的第一段, 不需要补充分隔符 */
            if (0 != ulIndx)
            {
                *pucBuffer++ = ucDelimiter;
            }

            pucBuffer    = (VOS_UINT8 *)IMS_NIC_I2A(ausAddrValue[ulIndx], (VOS_CHAR*)pucBuffer, ucRadix);
        }
    }

    /* 补充字符串结束符 */
    if (pucAddrStr != pucBuffer)
    {
        *pucBuffer = '\0';
    }
}

/*****************************************************************************
 函 数 名  : IMS_NIC_IsSameIpAddr
 功能描述  : 根据IPv4,IPv6地址对比两个地址是否相同
 输入参数  : pucIpAddr1            -- 需要比较的地址1
             pucIpAddr2            -- 需要比较的地址2
             ucIpAddrLen           -- IP地址长度
 输出参数  : 无
 返 回 值  : 相等返回1，不相等返回0
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2013年7月16日
    作    者   : caikai
    修改内容   : 新生成函数

*****************************************************************************/
VOS_UINT32 IMS_NIC_IsSameIpAddr(VOS_UINT8 *pucIpAddr1, VOS_UINT8 *pucIpAddr2, VOS_UINT8 ucIpAddrLen)
{
    VOS_UINT32 *pulIpAddrTmp1 = (VOS_UINT32 *)pucIpAddr1;
    VOS_UINT32 *pulIpAddrTmp2 = (VOS_UINT32 *)pucIpAddr2;


    if ((VOS_NULL_PTR == pucIpAddr1) || (VOS_NULL_PTR == pucIpAddr2))
    {
        IMS_NIC_ERROR_LOG2(UEPS_PID_IMSNIC, "IMS_NIC_IsSameIpAddr, ERROR, Input para is NULL.", pucIpAddr1, pucIpAddr2);

        return 0;
    }

    if (IMS_NIC_IPV4_ADDR_LENGTH == ucIpAddrLen)
    {
        return (*(pulIpAddrTmp1) == *(pulIpAddrTmp2));
    }
    else
    {
        return !((pulIpAddrTmp1[0]^pulIpAddrTmp2[0]) | (pulIpAddrTmp1[1]^pulIpAddrTmp2[1])
        | (pulIpAddrTmp1[2]^pulIpAddrTmp2[2]) | (pulIpAddrTmp1[3]^pulIpAddrTmp2[3]));
    }
}

/*****************************************************************************
 函 数 名  : IMS_NIC_DnsAddrCheck
 功能描述  : 检查待配置的DNS服务器地址是否已经配置过
 输入参数  : pucIpAddr              -- 欲配置的DNS服务器IP
             ulIpAddrLen            -- IP地址长度
             pstImsNicDnsInfo       -- 内部存储的DNS配置信息
 输出参数  : pucDnsIndx             -- 配置过则返回DNS服务器的索引，没配置过则返回可配置的DNS服务器的索引
 返 回 值  : 配置过为VOS_TRUE，没有配置过为VOS_FALSE
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2013年7月16日
    作    者   : caikai
    修改内容   : 新生成函数

*****************************************************************************/
VOS_UINT32 IMS_NIC_DnsAddrCheck (VOS_UINT8 *pucIpAddr, VOS_UINT8 ucIpAddrLen, IMS_NIC_DNS_INFO_STRU *pstDnsInfo, VOS_UINT8 *pucDnsIndx)
{
    VOS_UINT8                           ucIndex;
    VOS_UINT8                           aucIdle[IMS_NIC_MAX_DNS_SERVER_NUM] = {0};
    VOS_UINT8                           ucIdleNum;


    ucIdleNum   = 0;

    if ((VOS_NULL_PTR == pucIpAddr) || (VOS_NULL_PTR == pucDnsIndx) || (VOS_NULL_PTR == pstDnsInfo))
    {
        IMS_NIC_ERROR_LOG(UEPS_PID_IMSNIC, "IMS_NIC_DnsAddrCheck, ERROR, Input para is NULL.");

        return IMS_NIC_DNS_NOT_CFGED;
    }

    /* 遍历pstDnsInfo中存储的DNS信息 */
    for (ucIndex = 0; ucIndex < IMS_NIC_MAX_DNS_SERVER_NUM; ucIndex++)
    {
        if ( pstDnsInfo->astImsNicDnsInfo[ucIndex].cDnsRef > 0)
        {
            if (pstDnsInfo->astImsNicDnsInfo[ucIndex].ucIpAddrLen == ucIpAddrLen)
            {
                /*  比较pucIpAddr和pstDnsInfo->astImsNicDnsInfo[ucIndex].aucDnsAddr的内存(长度ucIpAddrLen) */
                if ( IMS_NIC_IsSameIpAddr(pucIpAddr, pstDnsInfo->astImsNicDnsInfo[ucIndex].aucDnsAddr, ucIpAddrLen) )
                {
                    /* 取当前索引 */
                    *pucDnsIndx  = ucIndex;

                    return IMS_NIC_DNS_CFGED;
                }
            }
        }
        else
        {
            /* 记录当前空闲的DNS编号 */
            aucIdle[ucIdleNum]   = ucIndex;
            ucIdleNum++;
        }
    }

    /* 取第一个空闲索引 */
    *pucDnsIndx  = aucIdle[0];

    return IMS_NIC_DNS_NOT_CFGED;

}

/*****************************************************************************
 函 数 名  : IMS_NIC_DnsConfig
 功能描述  : 配置DNS服务器
 输入参数  : pucIpAddr              -- 欲配置的DNS服务器IP
             ulIpAddrLen            -- IP地址长度
             pstImsNicDnsInfo       -- 内部存储的DNS配置信息
             pstImsNicPdnInfo       -- 内部存储的对应承载上虚拟网卡的配置信息
 输出参数  : 无
 返 回 值  : 成功:IMS_NIC_SUCC，失败为对应的错误码
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2013年7月16日
    作    者   : caikai
    修改内容   : 新生成函数

*****************************************************************************/
VOS_UINT32 IMS_NIC_DnsConfig (VOS_UINT8 *pucIpAddr, VOS_UINT8 ucIpAddrLen, IMS_NIC_DNS_INFO_STRU *pstDnsInfo, IMS_NIC_SINGLE_PDN_INFO_STRU *pstSinglePdnInfo)
{
    VOS_UINT8               ucDnsIndx;
    VOS_UINT32              ulResult;


    ucDnsIndx = 0;

    if (VOS_NULL_PTR == pucIpAddr)
    {
        IMS_NIC_ERROR_LOG(UEPS_PID_IMSNIC, "IMS_NIC_DnsConfig, ERROR, pucIpAddr is Null Ptr.");

        return IMS_NIC_CONFIG_PTR_NULL;
    }

    if (VOS_NULL_PTR == pstDnsInfo)
    {
        IMS_NIC_ERROR_LOG(UEPS_PID_IMSNIC, "IMS_NIC_DnsConfig, ERROR, pstDnsInfo is Null Ptr.");

        return IMS_NIC_CONFIG_PTR_NULL;
    }

    if (VOS_NULL_PTR == pstSinglePdnInfo)
    {
        IMS_NIC_ERROR_LOG(UEPS_PID_IMSNIC, "IMS_NIC_DnsConfig, ERROR, pstSinglePdnInfo is Null Ptr.");

        return IMS_NIC_CONFIG_PTR_NULL;
    }

    /* 判断当前欲配置的DNS服务器是否已经配置过 */
    ulResult     = IMS_NIC_DnsAddrCheck(pucIpAddr, ucIpAddrLen, pstDnsInfo, &ucDnsIndx);

    /* 该DNS服务器没有配置过 */
    if ( IMS_NIC_DNS_CFGED != ulResult )
    {
        if ( pstDnsInfo->ucDnsServerCnt < IMS_NIC_MAX_DNS_SERVER_NUM )
        {
            IMS_NIC_DnsConfigtoIpStack(ucIpAddrLen, ucDnsIndx, pucIpAddr);

            (VOS_VOID)mdrv_memcpy(pstDnsInfo->astImsNicDnsInfo[ucDnsIndx].aucDnsAddr, pucIpAddr, ucIpAddrLen);
            pstDnsInfo->astImsNicDnsInfo[ucDnsIndx].ucIpAddrLen  = ucIpAddrLen;
            pstDnsInfo->ucDnsServerCnt++;
        }
        else
        {
            IMS_NIC_STATS_INC(IMS_NIC_STATS_CFG_DNS_SERVER_FULL, 1, IMS_NIC_MODEM_ID_0);

            return IMS_NIC_DNS_SERVER_FULL;
        }
    }

    /* 如果服务器已经配置过，或配置成功将引用加上 */
    pstSinglePdnInfo->aucDnsFlag[ucDnsIndx]  = VOS_TRUE;

    /* 将该DNS服务器对应的引用计数加1 */
    pstDnsInfo->astImsNicDnsInfo[ucDnsIndx].cDnsRef++;

    return IMS_NIC_SUCC;
}


/*****************************************************************************
 函 数 名  : IMS_NIC_RecfgUncfgedDnsIpv4
 功能描述  : 将之前保存的因为Interpeak DNSS满没有配给Interpeak的DNS IP配给Interpeak
 输入参数  : IMS_NIC_PDN_INFO_STRU *pstPdnInfo 保存的PDN信息

 输出参数  : 无
 返 回 值  : 成功:IMS_NIC_SUCC，失败为对应的错误码
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2013年8月07日
    作    者   : t00148005
    修改内容   : 新生成函数

*****************************************************************************/
VOS_UINT32 IMS_NIC_RecfgUncfgedDnsIpv4(IMS_NIC_SINGLE_PDN_INFO_STRU *pstSinglePdnInfo, IMS_NIC_DNS_INFO_STRU *pstDnsInfo)
{
    VOS_UINT32 ulRst;


    ulRst = IMS_NIC_SUCC;

    if (VOS_NULL_PTR == pstSinglePdnInfo || VOS_NULL_PTR == pstDnsInfo)
    {
        IMS_NIC_WARNING_LOG(UEPS_PID_IMSNIC, "IMS_NIC_RecfgUncfgedDns, ERROR, Input para is NULL.");

        return IMS_NIC_CONFIG_PTR_NULL;
    }

    if ((VOS_TRUE == pstSinglePdnInfo->stIpv4PdnInfo.bitOpDnsPrim)
        && (VOS_FALSE == pstSinglePdnInfo->bitOpIpv4DnsPrimCfged))
    {
        /* 配置DNS到Interpeak中 */
        ulRst = IMS_NIC_IPV4_DNS_CONFIG(pstSinglePdnInfo->stIpv4PdnInfo.aucDnsPrimAddr, pstDnsInfo, pstSinglePdnInfo);

        /* 配置成功表示该DNS已经被配置到Interpeak中,否则因为DNS已经配置满，当前DNS未配置到Interpeak */
        pstSinglePdnInfo->bitOpIpv4DnsPrimCfged = ((IMS_NIC_SUCC == ulRst) ? VOS_TRUE : VOS_FALSE);
    }

    if ((VOS_TRUE == pstSinglePdnInfo->stIpv4PdnInfo.bitOpDnsSec)
        && (VOS_FALSE == pstSinglePdnInfo->bitOpIpv4DnsSecCfged))
    {
        /* 配置DNS到Interpeak中 */
        ulRst = IMS_NIC_IPV4_DNS_CONFIG(pstSinglePdnInfo->stIpv4PdnInfo.aucDnsSecAddr, pstDnsInfo, pstSinglePdnInfo);

        /* 配置成功表示该DNS已经被配置到Interpeak中,否则因为DNS已经配置满，当前DNS未配置到Interpeak */
        pstSinglePdnInfo->bitOpIpv4DnsSecCfged = ((IMS_NIC_SUCC == ulRst) ? VOS_TRUE : VOS_FALSE);
    }

    return ulRst;
}


/*****************************************************************************
 函 数 名  : IMS_NIC_RecfgUncfgedDnsIpv6
 功能描述  : 将之前保存的因为Interpeak DNSS满没有配给Interpeak的DNS IP配给Interpeak
 输入参数  : IMS_NIC_PDN_INFO_STRU *pstPdnInfo 保存的PDN信息

 输出参数  : 无
 返 回 值  : 成功:IMS_NIC_SUCC，失败为对应的错误码
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2013年8月07日
    作    者   : t00148005
    修改内容   : 新生成函数

*****************************************************************************/
VOS_UINT32 IMS_NIC_RecfgUncfgedDnsIpv6(IMS_NIC_SINGLE_PDN_INFO_STRU *pstSinglePdnInfo, IMS_NIC_DNS_INFO_STRU *pstDnsInfo)
{
    VOS_UINT32 ulRst;


    ulRst = IMS_NIC_SUCC;

    if (VOS_NULL_PTR == pstSinglePdnInfo || VOS_NULL_PTR == pstDnsInfo)
    {
        IMS_NIC_WARNING_LOG(UEPS_PID_IMSNIC, "IMS_NIC_RecfgUncfgedDns, ERROR, Input para is NULL.");

        return IMS_NIC_CONFIG_PTR_NULL;
    }

    if ((VOS_TRUE == pstSinglePdnInfo->stIpv6PdnInfo.bitOpDnsPrim)
        && (VOS_FALSE == pstSinglePdnInfo->bitOpIpv6DnsPrimCfged))
    {
        /* 配置DNS到Interpeak中 */
        ulRst = IMS_NIC_IPV6_DNS_CONFIG(pstSinglePdnInfo->stIpv6PdnInfo.aucDnsPrimAddr, pstDnsInfo, pstSinglePdnInfo);

        /* 配置成功表示该DNS已经被配置到Interpeak中,否则因为DNS已经配置满，当前DNS未配置到Interpeak */
        pstSinglePdnInfo->bitOpIpv6DnsPrimCfged = ((IMS_NIC_SUCC == ulRst) ? VOS_TRUE : VOS_FALSE);
    }

    if ((VOS_TRUE == pstSinglePdnInfo->stIpv6PdnInfo.bitOpDnsSec)
        && (VOS_FALSE == pstSinglePdnInfo->bitOpIpv6DnsSecCfged))
    {
        /* 配置DNS到Interpeak中 */
        ulRst = IMS_NIC_IPV6_DNS_CONFIG(pstSinglePdnInfo->stIpv6PdnInfo.aucDnsSecAddr, pstDnsInfo, pstSinglePdnInfo);

        /* 配置成功表示该DNS已经被配置到Interpeak中,否则因为DNS已经配置满，当前DNS未配置到Interpeak */
        pstSinglePdnInfo->bitOpIpv6DnsSecCfged = ((IMS_NIC_SUCC == ulRst) ? VOS_TRUE : VOS_FALSE);
    }

    return ulRst;
}


/*****************************************************************************
 函 数 名  : IMS_NIC_RecfgUncfgedDns
 功能描述  : 将之前保存的因为Interpeak DNSS满没有配给Interpeak的DNS IP配给Interpeak
 输入参数  : IMS_NIC_PDN_INFO_STRU *pstPdnInfo 保存的PDN信息

 输出参数  : 无
 返 回 值  : 成功:IMS_NIC_SUCC，失败为对应的错误码
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2013年8月07日
    作    者   : t00148005
    修改内容   : 新生成函数

*****************************************************************************/
VOS_VOID  IMS_NIC_RecfgUncfgedDns(IMS_NIC_PDN_INFO_STRU *pstPdnInfo)
{
    VOS_UINT32                      ulIndx;
    IMS_NIC_SINGLE_PDN_INFO_STRU   *pstSinglePdnInfo;


    if (VOS_NULL_PTR == pstPdnInfo)
    {
        IMS_NIC_ERROR_LOG(UEPS_PID_IMSNIC, "IMS_NIC_RecfgUncfgedDns, ERROR, Input para is NULL.");

        return;
    }

    for(ulIndx = 0; ulIndx < IMS_NIC_RAB_ID_MAX_NUM; ulIndx++)
    {
        pstSinglePdnInfo = &pstPdnInfo->astImsNicPdnInfo[ulIndx];

        if (VOS_TRUE == pstSinglePdnInfo->bitOpIpv4PdnInfo)
        {
            /* 一旦不成功就不用再找了,退出循环 */
            if (IMS_NIC_SUCC != IMS_NIC_RecfgUncfgedDnsIpv4(pstSinglePdnInfo, &pstPdnInfo->stImsNicDnsInfo))
            {
                break;
            }
        }

        if (VOS_TRUE == pstSinglePdnInfo->bitOpIpv6PdnInfo)
        {
            /* 一旦不成功就不用再找了,退出循环 */
            if (IMS_NIC_SUCC != IMS_NIC_RecfgUncfgedDnsIpv6(pstSinglePdnInfo, &pstPdnInfo->stImsNicDnsInfo))
            {
                break;
            }
        }
    }
}

/*****************************************************************************
 函 数 名  : IMS_NIC_DnsInfoDel
 功能描述  : 从Interpeak中删除配置的DNS Server IP
 输入参数  : IMS_NIC_PDN_INFO_STRU *pstPdnInfo 保存的PDN信息
             VOS_UINT8 ucRabId                 要删除的rabid

 输出参数  : 无
 返 回 值  : 无
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2013年8月07日
    作    者   : t00148005
    修改内容   : 新生成函数

*****************************************************************************/
VOS_VOID IMS_NIC_DnsInfoDel(IMS_NIC_PDN_INFO_STRU *pstPdnInfo, VOS_UINT8 ucRabId)
{
    VOS_UINT32                           ulIndx;
    IMS_NIC_SINGLE_PDN_INFO_STRU        *pstSinglePdnInfo;
    IMS_NIC_DNS_INFO_STRU               *pstDnsInfo;


    if (VOS_NULL_PTR == pstPdnInfo)
    {
        IMS_NIC_ERROR_LOG(UEPS_PID_IMSNIC, "IMS_NIC_DnsInfoDel, ERROR, Input para is NULL.");

        return;
    }

    pstSinglePdnInfo = &(pstPdnInfo->astImsNicPdnInfo[ucRabId - IMS_NIC_RAB_ID_OFFSET]);
    pstDnsInfo       = &(pstPdnInfo->stImsNicDnsInfo);

    for (ulIndx = 0; ulIndx < IMS_NIC_MAX_DNS_SERVER_NUM; ulIndx++)
    {
        /* 找到对应的dns索引 */
        if (VOS_TRUE == pstSinglePdnInfo->aucDnsFlag[ulIndx])
        {
            pstDnsInfo->astImsNicDnsInfo[ulIndx].cDnsRef--;
            pstSinglePdnInfo->aucDnsFlag[ulIndx]    = VOS_FALSE;

            /* 如果当前DNS已经没有人引用，从Interpeak中删除 */
            if (0 >= pstDnsInfo->astImsNicDnsInfo[ulIndx].cDnsRef)
            {
                IMS_NIC_DnsDeltoIpStack(ulIndx, ucRabId, pstDnsInfo);

                PS_MEM_SET(&pstDnsInfo->astImsNicDnsInfo[ulIndx], 0, sizeof(IMS_NIC_SINGLE_DNS_INFO_STRU));
                pstDnsInfo->ucDnsServerCnt--;
            }
        }
    }

    /* 如果有从Interpeak中删除DNS Server，查找之前的配置看是否有未配置成功的DNS,将其配到Interpeak中 */
    if (pstDnsInfo->ucDnsServerCnt < IMS_NIC_MAX_DNS_SERVER_NUM)
    {
        IMS_NIC_RecfgUncfgedDns(pstPdnInfo);
    }

    return;
}

/*****************************************************************************
 函 数 名  : IMS_NIC_PdnInfoDel
 功能描述  : IMS虚拟网卡PDN配置信息删除，由IMSA模块在PDN去激活后调用
 输入参数  : ucRabId        承载号
             enModemId      当前modemID
 输出参数  : 无
 返 回 值  : 成功:IMS_NIC_SUCC，失败为对应的错误码
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2013年7月16日
    作    者   : caikai
    修改内容   : 新生成函数

*****************************************************************************/
VOS_UINT32 IMS_NIC_PdnInfoDel(VOS_UINT8 ucRabId, MODEM_ID_ENUM_UINT16 enModemId)
{
    IMS_NIC_ENTITY_STRU                 *pstImsNicEntity;
    IMS_NIC_SINGLE_PDN_INFO_STRU        *pstSinglePdnInfo;
    IMS_NIC_PDN_INFO_STRU               *pstPdnInfo;


    IMS_NIC_MNTN_TRACE_NO_DATA(ID_IMS_NIC_MNTN_TRACE_RCV_CONFIG_DEL, enModemId, ucRabId);

    if ( enModemId >= IMS_NIC_MODEM_ID_BUTT )
    {
        IMS_NIC_STATS_INC(IMS_NIC_STATS_CFG_DEL_MODEM_ID_ERR, 1, IMS_NIC_MODEM_ID_0);

        IMS_NIC_ERROR_LOG1(UEPS_PID_IMSNIC, "IMS_NIC_PdnInfoDel, ERROR Input modem id invalid!\n", enModemId);

        return IMS_NIC_MODEM_ID_INVALID;
    }

    /* 检查承载号是否有效，取值范围[5, 15] */
    if ( !IMS_NIC_IS_RAB_VALID(ucRabId) )
    {
        IMS_NIC_STATS_INC(IMS_NIC_STATS_CFG_DEL_RAB_ID_ERR, 1, enModemId);

        IMS_NIC_ERROR_LOG1(UEPS_PID_IMSNIC, "IMS_NIC_PdnInfoDel, ERROR Input Rab id invalid!\n", ucRabId);

        return IMS_NIC_RABID_INVALID;
    }


    pstImsNicEntity     = IMS_NIC_GET_ENTITY_STRU(enModemId);
    pstPdnInfo          = &(pstImsNicEntity->stImsNicPdnInfo);
    pstSinglePdnInfo    = &(pstPdnInfo->astImsNicPdnInfo[ucRabId - IMS_NIC_RAB_ID_OFFSET]);

    if (VOS_FALSE == (pstSinglePdnInfo->bitOpIpv4PdnInfo | pstSinglePdnInfo->bitOpIpv6PdnInfo))
    {
        IMS_NIC_STATS_INC(IMS_NIC_STATS_CFG_DEL_NO_PDN, 1, enModemId);

        IMS_NIC_WARNING_LOG2(UEPS_PID_IMSNIC, "IMS_NIC_PdnInfoDel, ERROR No Cfged PDN!\n", enModemId, ucRabId);

        return IMS_NIC_NO_CFG_PDN;
    }

    if (0 >= pstPdnInfo->iPdnCfgCnt)
    {
        IMS_NIC_STATS_INC(IMS_NIC_STATS_NO_CFGED_PDN, 1, enModemId);

        IMS_NIC_WARNING_LOG2(UEPS_PID_IMSNIC, "IMS_NIC_PdnInfoDel, ERROR Input Rab id invalid!\n", enModemId, ucRabId);

        /* 该场景可能异常，清一下状态 */
        IMS_NIC_ResetAll(enModemId);

        return IMS_NIC_NO_CFG_PDN;
    }


    if ( VOS_TRUE == pstSinglePdnInfo->bitOpIpv4PdnInfo )
    {
       IMS_NIC_PdnInfoDelIpv4(ucRabId, enModemId);
    }

    if ( VOS_TRUE == pstSinglePdnInfo->bitOpIpv6PdnInfo )
    {
        IMS_NIC_PdnInfoDelIpv6(ucRabId, enModemId);
    }

    IMS_NIC_DnsInfoDel(pstPdnInfo, ucRabId);

    pstPdnInfo->iPdnCfgCnt--;

    if (0 >= pstPdnInfo->iPdnCfgCnt)
    {
        IMS_NIC_ResetAll(enModemId);
    }

    IMS_NIC_MNTN_TRACE2(ID_IMS_NIC_MNTN_TRACE_RCV_CONFIG_DEL_RSLT, pstPdnInfo, sizeof(IMS_NIC_PDN_INFO_STRU), enModemId, ucRabId);

    return IMS_NIC_SUCC;
}

/*****************************************************************************
 函 数 名  : IMS_NIC_PdnInfoConfigIpv4
 功能描述  : IMS虚拟网卡IPv4配置接口
 输入参数  : pstConfigInfo   IMS虚拟网卡配置信息
 输出参数  : 无
 返 回 值  : 成功:IMS_NIC_SUCC，失败为对应的错误码
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2013年7月16日
    作    者   : caikai
    修改内容   : 新生成函数

*****************************************************************************/
VOS_UINT32 IMS_NIC_PdnInfoConfigIpv4(IMS_NIC_PDN_INFO_CONFIG_STRU *pstConfigInfo)
{
    VOS_UINT32                          ulRst;
    IMS_NIC_ENTITY_STRU                *pstImsNicEntity;
    IMS_NIC_SINGLE_PDN_INFO_STRU       *pstSinglePdnInfo;
    IMS_NIC_DNS_INFO_STRU              *pstDnsInfo;


    ulRst = IMS_NIC_SUCC;

    if (VOS_NULL_PTR == pstConfigInfo)
    {
        IMS_NIC_ERROR_LOG(UEPS_PID_IMSNIC, "IMS_NIC_PdnInfoConfigIpv4, ERROR, Input Null Ptr.");

        return IMS_NIC_CONFIG_PTR_NULL;
    }

    pstImsNicEntity     = IMS_NIC_GET_ENTITY_STRU(pstConfigInfo->enModemId);
    pstSinglePdnInfo    = &(pstImsNicEntity->stImsNicPdnInfo.astImsNicPdnInfo[pstConfigInfo->ucRabId  - IMS_NIC_RAB_ID_OFFSET]);
    pstDnsInfo          = &(pstImsNicEntity->stImsNicPdnInfo.stImsNicDnsInfo);

    pstSinglePdnInfo->bitOpIpv4PdnInfo  = VOS_TRUE;
    (VOS_VOID)mdrv_memcpy(pstSinglePdnInfo->stIpv4PdnInfo.aucIpV4Addr, pstConfigInfo->stIpv4PdnInfo.aucIpV4Addr, IMS_NIC_IPV4_ADDR_LENGTH);

    /* 配置ipv4网卡 */
    IMS_NIC_ConfigIpv4Addr(pstConfigInfo->enModemId, pstConfigInfo->stIpv4PdnInfo.aucIpV4Addr);

    if (VOS_TRUE == pstConfigInfo->stIpv4PdnInfo.bitOpDnsPrim)
    {
        /* 保存DNS地址信息 */
        (VOS_VOID)mdrv_memcpy(pstSinglePdnInfo->stIpv4PdnInfo.aucDnsPrimAddr, pstConfigInfo->stIpv4PdnInfo.aucDnsPrimAddr, IMS_NIC_IPV4_ADDR_LENGTH);
        pstSinglePdnInfo->stIpv4PdnInfo.bitOpDnsPrim = VOS_TRUE;

        /* 配置DNS到Interpeak中 */
        ulRst = IMS_NIC_IPV4_DNS_CONFIG(pstConfigInfo->stIpv4PdnInfo.aucDnsPrimAddr, pstDnsInfo, pstSinglePdnInfo);

        /* 配置成功表示该DNS已经被配置到Interpeak中,否则因为DNS已经配置满，当前DNS未配置到Interpeak */
        pstSinglePdnInfo->bitOpIpv4DnsPrimCfged = ((IMS_NIC_SUCC == ulRst) ? VOS_TRUE : VOS_FALSE);
    }

    if (VOS_TRUE == pstConfigInfo->stIpv4PdnInfo.bitOpDnsSec)
    {
        /* 保存DNS地址信息 */
        (VOS_VOID)mdrv_memcpy(pstSinglePdnInfo->stIpv4PdnInfo.aucDnsSecAddr, pstConfigInfo->stIpv4PdnInfo.aucDnsSecAddr, IMS_NIC_IPV4_ADDR_LENGTH);
        pstSinglePdnInfo->stIpv4PdnInfo.bitOpDnsSec = VOS_TRUE;

        /* 配置DNS到Interpeak中 */
        ulRst = IMS_NIC_IPV4_DNS_CONFIG(pstConfigInfo->stIpv4PdnInfo.aucDnsSecAddr, pstDnsInfo, pstSinglePdnInfo);

        /* 配置成功表示该DNS已经被配置到Interpeak中,否则因为DNS已经配置满，当前DNS未配置到Interpeak */
        pstSinglePdnInfo->bitOpIpv4DnsSecCfged = ((IMS_NIC_SUCC == ulRst) ? VOS_TRUE : VOS_FALSE);
    }

    return ulRst;
}

/*****************************************************************************
 函 数 名  : IMS_NIC_PdnInfoConfigIpv6
 功能描述  : IMS虚拟网卡IPv6配置接口
 输入参数  : pstConfigInfo   IMS虚拟网卡配置信息
 输出参数  : 无
 返 回 值  : 成功:IMS_NIC_SUCC，失败为对应的错误码
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2013年7月16日
    作    者   : caikai
    修改内容   : 新生成函数

*****************************************************************************/
VOS_UINT32 IMS_NIC_PdnInfoConfigIpv6(IMS_NIC_PDN_INFO_CONFIG_STRU *pstConfigInfo)
{
    VOS_UINT8                           aucIpAddrStr[IMS_NIC_IPV6_ADDR_STR_LEN + 1] = {0};
    VOS_UINT32                          ulRst;
    IMS_NIC_ENTITY_STRU                *pstImsNicEntity;
    IMS_NIC_SINGLE_PDN_INFO_STRU       *pstSinglePdnInfo;
    IMS_NIC_DNS_INFO_STRU              *pstDnsInfo;


    ulRst  = IMS_NIC_SUCC;

    if (VOS_NULL_PTR == pstConfigInfo)
    {
        IMS_NIC_ERROR_LOG(UEPS_PID_IMSNIC, "IMS_NIC_PdnInfoConfigIpv6, ERROR, Input Null Ptr.");

        return IMS_NIC_CONFIG_PTR_NULL;
    }

    if (pstConfigInfo->stIpv6PdnInfo.ulBitPrefixLen > IMS_NIC_IPV6_ADDR_BIT_LEN)
    {
        IMS_NIC_ERROR_LOG1(UEPS_PID_IMSNIC, "IMS_NIC_PdnInfoConfigIpv6, ERROR, Invalid Prefixlen.", pstConfigInfo->stIpv6PdnInfo.ulBitPrefixLen);

        IMS_NIC_STATS_INC(IMS_NIC_STATS_INVALID_IPV6_PREFIX_LEN, 1, pstConfigInfo->enModemId);

        return IMS_NIC_PREFIXLEN_INVALID;
    }

    pstImsNicEntity     = IMS_NIC_GET_ENTITY_STRU(pstConfigInfo->enModemId);
    pstSinglePdnInfo    = &(pstImsNicEntity->stImsNicPdnInfo.astImsNicPdnInfo[pstConfigInfo->ucRabId  - IMS_NIC_RAB_ID_OFFSET]);
    pstDnsInfo          = &(pstImsNicEntity->stImsNicPdnInfo.stImsNicDnsInfo);

    pstSinglePdnInfo->bitOpIpv6PdnInfo  = VOS_TRUE;
    pstSinglePdnInfo->stIpv6PdnInfo.ulBitPrefixLen    = pstConfigInfo->stIpv6PdnInfo.ulBitPrefixLen;
    (VOS_VOID)mdrv_memcpy(pstSinglePdnInfo->stIpv6PdnInfo.aucIpV6Addr, pstConfigInfo->stIpv6PdnInfo.aucIpV6Addr, IMS_NIC_IPV6_ADDR_LENGTH);

    IMS_NIC_ConvertIpv6AddrToCompressedStr((VOS_UINT8 *)aucIpAddrStr, pstConfigInfo->stIpv6PdnInfo.aucIpV6Addr, IMS_NIC_IPV6_STR_RFC2373_TOKENS);

    /* 配置ipv6网卡 */
    IMS_NIC_ConfigIpv6Addr(pstConfigInfo->enModemId, aucIpAddrStr, pstConfigInfo->stIpv6PdnInfo.ulBitPrefixLen);

    if (VOS_TRUE == pstConfigInfo->stIpv6PdnInfo.bitOpDnsPrim)
    {
        /* 保存DNS地址信息 */
        (VOS_VOID)mdrv_memcpy(pstSinglePdnInfo->stIpv6PdnInfo.aucDnsPrimAddr, pstConfigInfo->stIpv6PdnInfo.aucDnsPrimAddr, IMS_NIC_IPV6_ADDR_LENGTH);
        pstSinglePdnInfo->stIpv6PdnInfo.bitOpDnsPrim = VOS_TRUE;

        /* 配置主DNS到Interpeak中 */
        ulRst = IMS_NIC_IPV6_DNS_CONFIG(pstConfigInfo->stIpv6PdnInfo.aucDnsPrimAddr, pstDnsInfo, pstSinglePdnInfo);

        /* 配置成功表示该DNS已经被配置到Interpeak中,否则因为DNS已经配置满，当前DNS未配置到Interpeak */
        pstSinglePdnInfo->bitOpIpv6DnsPrimCfged = ((IMS_NIC_SUCC == ulRst) ? VOS_TRUE : VOS_FALSE);
    }

    if (VOS_TRUE == pstConfigInfo->stIpv6PdnInfo.bitOpDnsSec)
    {
        /* 保存DNS地址信息 */
        (VOS_VOID)mdrv_memcpy(pstSinglePdnInfo->stIpv6PdnInfo.aucDnsSecAddr, pstConfigInfo->stIpv6PdnInfo.aucDnsSecAddr, IMS_NIC_IPV6_ADDR_LENGTH);
        pstSinglePdnInfo->stIpv6PdnInfo.bitOpDnsSec = VOS_TRUE;

        /* 配置辅DNS到Interpeak中 */
        ulRst = IMS_NIC_IPV6_DNS_CONFIG(pstConfigInfo->stIpv6PdnInfo.aucDnsSecAddr, pstDnsInfo, pstSinglePdnInfo);

        /* 配置成功表示该DNS已经被配置到Interpeak中,否则因为DNS已经配置满，当前DNS未配置到Interpeak */
        pstSinglePdnInfo->bitOpIpv6DnsSecCfged = ((IMS_NIC_SUCC == ulRst) ? VOS_TRUE : VOS_FALSE);
    }

    return ulRst;
}

/*****************************************************************************
 函 数 名  : IMS_NIC_PdnInfoConfig
 功能描述  : IMS虚拟网卡配置接口,由IMSA模块调用
 输入参数  : pstConfigInfo   IMS虚拟网卡配置信息
 输出参数  : 无
 返 回 值  : 成功:IMS_NIC_SUCC，失败为对应的错误码
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2013年7月16日
    作    者   : caikai
    修改内容   : 新生成函数

*****************************************************************************/
VOS_UINT32 IMS_NIC_PdnInfoConfig (IMS_NIC_PDN_INFO_CONFIG_STRU *pstConfigInfo)
{
    IMS_NIC_ENTITY_STRU                 *pstImsNicEntity;
    IMS_NIC_SINGLE_PDN_INFO_STRU        *pstSinglePdnInfo;
    IMS_NIC_PDN_INFO_STRU               *pstPdnInfo;
    VOS_UINT32                           ulResult;
    VOS_UINT32                           ulIsNewConfig;


    ulResult        = IMS_NIC_SUCC;
    ulIsNewConfig   = VOS_FALSE;

    if ( VOS_NULL_PTR == pstConfigInfo )
    {
        IMS_NIC_STATS_INC(IMS_NIC_STATS_CFG_INPUT_NULL_PTR, 1, IMS_NIC_MODEM_ID_0);

        IMS_NIC_ERROR_LOG(UEPS_PID_IMSNIC, "IMS_NIC_PdnInfoConfig, ERROR, Input NULL PTR!");

        return IMS_NIC_CONFIG_PTR_NULL;
    }

    /* 可维可测 */
    IMS_NIC_MNTN_TRACE(ID_IMS_NIC_MNTN_TRACE_RCV_CONFIG_INFO, pstConfigInfo, sizeof(IMS_NIC_PDN_INFO_CONFIG_STRU));

    if ( pstConfigInfo->enModemId >= IMS_NIC_MODEM_ID_BUTT )
    {
        IMS_NIC_STATS_INC(IMS_NIC_STATS_CFG_ADD_RAB_ID_ERR, 1, IMS_NIC_MODEM_ID_0);

        IMS_NIC_ERROR_LOG1(UEPS_PID_IMSNIC, "IMS_NIC_PdnInfoConfig, ERROR, Input Modem id invalid!", pstConfigInfo->enModemId);

        return IMS_NIC_MODEM_ID_INVALID;
    }

    /* 检查承载号是否有效，取值范围[5, 15] */
    if ( !IMS_NIC_IS_RAB_VALID(pstConfigInfo->ucRabId) )
    {
        IMS_NIC_STATS_INC(IMS_NIC_STATS_CFG_ADD_MODEM_ID_ERR, 1, pstConfigInfo->enModemId);

        IMS_NIC_ERROR_LOG1(UEPS_PID_IMSNIC, "IMS_NIC_PdnInfoConfig, ERROR Input Rab id invalid!\n", pstConfigInfo->ucRabId);

        return IMS_NIC_RABID_INVALID;
    }

    if (VOS_FALSE == (pstConfigInfo->bitOpIpv4PdnInfo | pstConfigInfo->bitOpIpv6PdnInfo))
    {
        IMS_NIC_STATS_INC(IMS_NIC_STATS_CFG_ADD_NO_PDN, 1, pstConfigInfo->enModemId);

        IMS_NIC_ERROR_LOG(UEPS_PID_IMSNIC, "IMS_NIC_PdnInfoConfig, ERROR No IPv4 and IPv6 info cfged!\n");

        return IMS_NIC_NO_CFG_PDN;
    }


    pstImsNicEntity     = IMS_NIC_GET_ENTITY_STRU(pstConfigInfo->enModemId);
    pstPdnInfo          = &(pstImsNicEntity->stImsNicPdnInfo);
    pstSinglePdnInfo    = &(pstPdnInfo->astImsNicPdnInfo[pstConfigInfo->ucRabId - IMS_NIC_RAB_ID_OFFSET]);

    /* 检查当前承载上是否还存在旧的无效配置 */
    if ( ((pstConfigInfo->bitOpIpv4PdnInfo) & (pstSinglePdnInfo->bitOpIpv4PdnInfo))
        | ((pstConfigInfo->bitOpIpv6PdnInfo) & (pstSinglePdnInfo->bitOpIpv6PdnInfo)))
    {
        /* 删除该承载上的配置 */
        (VOS_VOID)IMS_NIC_PdnInfoDel(pstConfigInfo->ucRabId, pstConfigInfo->enModemId);
    }

    /* 新配置一个PDN的时候才需要cfgCnt++，这里主要是通过本地保存的状态确认该rab上是否有被配置过 */
    /* 放到删除之后再判断，可以保证该rab上的配置是处于最新状态 */
    if (VOS_FALSE == (pstSinglePdnInfo->bitOpIpv4PdnInfo | pstSinglePdnInfo->bitOpIpv6PdnInfo))
    {
        ulIsNewConfig = VOS_TRUE;
    }

    /* 配置IPV4相关 */
    if ( VOS_TRUE == pstConfigInfo->bitOpIpv4PdnInfo )
    {
        ulResult = IMS_NIC_PdnInfoConfigIpv4(pstConfigInfo);
    }

    /* 配置IPV6相关 */
    if ( VOS_TRUE == pstConfigInfo->bitOpIpv6PdnInfo )
    {
        ulResult |= IMS_NIC_PdnInfoConfigIpv6(pstConfigInfo);
    }

    if (0 == pstImsNicEntity->stImsNicPdnInfo.iPdnCfgCnt)
    {
        /* 配置默认路由 */
        IMS_NIC_SetDefaultRoute(pstConfigInfo->enModemId);

        /* 端口限制仅在网卡第一次激活时配置一次，重配需先删除网卡 */
        if (VOS_TRUE == pstConfigInfo->bitOpSockPortInfo)
        {
            /* 配置Socket端口 */
            ulResult |= IMS_NIC_SetSocketPort(pstConfigInfo->stSockPortInfo.usSockMinPort,
                pstConfigInfo->stSockPortInfo.usSockMaxPort, pstConfigInfo->enModemId);
        }
    }

    if (VOS_TRUE == ulIsNewConfig)
    {
        pstPdnInfo->iPdnCfgCnt++;
    }

    /* 前面的可维可测是抓的外部配置信息，这里抓取本模块维护的状态信息 */
    IMS_NIC_MNTN_TRACE2(ID_IMS_NIC_MNTN_TRACE_CONFIG_PROC_RSLT, pstPdnInfo, sizeof(IMS_NIC_PDN_INFO_STRU), ulResult, ulIsNewConfig);

    return ulResult;
}


/*****************************************************************************
 函 数 名  : IMS_NIC_RegUlDataSendCb
 功能描述  : 注册IMS虚拟网卡上行数据发送回调函数，由CDS模块调用
 输入参数  : pFunc        上行数据发送回调接口
             enModemId    当前modemID
 输出参数  : 无
 返 回 值  : 成功:IMS_NIC_SUCC，失败:IMS_NIC_FAIL
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2013年7月16日
    作    者   : caikai
    修改内容   : 新生成函数

*****************************************************************************/
VOS_UINT32 IMS_NIC_RegUlDataSendCb(IMS_NIC_SEND_UL_DATA_FUNC pFunc, MODEM_ID_ENUM_UINT16 enModemId)
{
    IMS_NIC_ENTITY_STRU     *pstImsNicEntity;


    if ( enModemId >= IMS_NIC_MODEM_ID_BUTT )
    {
        /* 默认记录到Modem0的实体中 */;
        IMS_NIC_STATS_INC(IMS_NIC_STATS_MODEM_ID_ERR_IN_REG_CB, 1, IMS_NIC_MODEM_ID_0);

        return IMS_NIC_MODEM_ID_INVALID;
    }

    pstImsNicEntity     = IMS_NIC_GET_ENTITY_STRU(enModemId);

    /* 该虚拟网卡没有初始化 */
    if ( VOS_TRUE != pstImsNicEntity->ulImsNicInitFlag )
    {
        IMS_NIC_SAVE_UL_DATA_FUNC(enModemId, pFunc);
    }
    else
    {
        pstImsNicEntity->pUlDataSendFunc = pFunc;
    }

    return IMS_NIC_SUCC;
}

/*****************************************************************************
 函 数 名  : IMS_NIC_DlParaCheck
 功能描述  : IMS虚拟网卡下行数据接收参数检查
 输入参数  : pucData      IP包数据
             usLen        IP包长度
             enModemId    当前modemID
 输出参数  :
 返 回 值  : 成功:IMS_NIC_SUCC，失败:IMS_NIC_FAIL
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2013年7月16日
    作    者   : caikai
    修改内容   : 新生成函数

*****************************************************************************/
VOS_UINT32 IMS_NIC_DlParaCheck(VOS_UINT8 *pucData, VOS_UINT16 usLen, MODEM_ID_ENUM_UINT16 enModemId)
{

    if ( enModemId >= IMS_NIC_MODEM_ID_BUTT )
    {
        /* 默认记录到Modem0的实体中 */;
        IMS_NIC_STATS_INC(IMS_NIC_STATS_MODE_ID_ERR_IN_DL_PROC, 1, IMS_NIC_MODEM_ID_0);

        IMS_NIC_ERROR_LOG1(UEPS_PID_IMSNIC, "IMS_NIC_DlParaCheck, ERROR, Input modem id invalid!\n", enModemId);

        return IMS_NIC_FAIL;
    }

    if ( VOS_NULL_PTR == pucData )
    {
        IMS_NIC_STATS_INC(IMS_NIC_STATS_DL_INPUT_NULL_PTR, 1, enModemId);

        IMS_NIC_ERROR_LOG(UEPS_PID_IMSNIC, "IMS_NIC_DlParaCheck, ERROR, input pucData is NULL!\n");

        return IMS_NIC_FAIL;
    }

    /* usLen值不在有效值范围内 */
    if ( (usLen < IMS_NIC_MIN_IPPKT_LEN) || (usLen > IMS_NIC_MAX_IPPKT_LEN))
    {
        IMS_NIC_STATS_INC(IMS_NIC_STATS_DL_RCV_DATA_LEN_ERR, 1, enModemId);

        IMS_NIC_ERROR_LOG1(UEPS_PID_IMSNIC, "IMS_NIC_DlParaCheck, ERROR, usLen is invalid! usLen = %d\n", usLen);

        return IMS_NIC_FAIL;
    }

    return IMS_NIC_SUCC;

}


/*****************************************************************************
 函 数 名  : IMS_NIC_UlDataSend
 功能描述  : 该函数负责将MUX层出来的数据交给CDS
 输入参数  : pucData      IP包数据
             usLen        IP包长度
             enModemId    当前modemID
 输出参数  : 无
 返 回 值  : 成功:IMS_NIC_SUCC，失败为IMS_NIC_FAIL
 被调函数  :

 修改历史      :
  1.日    期   : 2013年7月16日
    作    者   : caikai
    修改内容   : 新生成函数

*****************************************************************************/
VOS_UINT32 IMS_NIC_UlDataSend(VOS_UINT8 *pucData, VOS_UINT16 usLen, MODEM_ID_ENUM_UINT16 enModemId)
{
    IMS_NIC_ENTITY_STRU                     *pstImsNicEntity;
    IMS_NIC_ETH_HEADER_STRU                 *pstEthHdr;
    VOS_UINT8                               *pucIpData;
    VOS_UINT16                               usIpDataLen;
    VOS_UINT32                               ulResult;
    VOS_UINT16                               usEtherType;

    /* 数据指针为空 */
    if ( VOS_NULL_PTR == pucData )
    {
        IMS_NIC_STATS_INC(IMS_NIC_STATS_UL_INPUT_NULL_PTR, 1, enModemId);

        IMS_NIC_ERROR_LOG_MSG(UEPS_PID_IMSNIC, "IMS_NIC_UlDataSend, ERROR, Input data is NULL!\n");

        return IMS_NIC_FAIL;
    }

    /* 数据报文长度不在有效值范围内，即[MIN + OFFSET, MTU + OFFSET],
        其中MIN为最小IP包大小，OFFSET为14个字节(14字节以太网包头长度) */
    if ( (usLen < (IMS_NIC_MIN_IPPKT_LEN + IMS_NIC_ETH_HDR_SIZE)) ||
        (usLen > (IMS_NIC_GET_MTU + IMS_NIC_ETH_HDR_SIZE)) )
    {
        IMS_NIC_STATS_INC(IMS_NIC_STATS_UL_RCV_DATA_LEN_ERR, 1, enModemId);

        IMS_NIC_ERROR_LOG_MSG2(UEPS_PID_IMSNIC, "IMS_NIC_UlDataSend, ERROR, Input data len =%d mtu = %d is invalid!\n", (VOS_INT32)usLen, (VOS_INT32)IMS_NIC_GET_MTU);

        return IMS_NIC_FAIL;
    }

    pstEthHdr   = (IMS_NIC_ETH_HEADER_STRU *)pucData;

    /* 网络序转换为主机序 */
    usEtherType   = VOS_NTOHS(pstEthHdr->usEtherType);

    switch (usEtherType)
    {
        case IMS_NIC_ETHERTYPE_IPV4:
            IMS_NIC_STATS_INC(IMS_NIC_STATS_UL_RCV_IPV4_PKT, 1, enModemId);
            break;

        case IMS_NIC_ETHERTYPE_IPV6:
            IMS_NIC_STATS_INC(IMS_NIC_STATS_UL_RCV_IPV6_PKT, 1, enModemId);
            break;

        /* 网卡配置为NOARP, 收到ARP包不进行递交，直接返回 */
        case IMS_NIC_ETHERTYPE_ARP:
            IMS_NIC_STATS_INC(IMS_NIC_STATS_UL_RCV_ARP_PKT, 1, enModemId);
            return IMS_NIC_SUCC;

        default:
            IMS_NIC_STATS_INC(IMS_NIC_STATS_UL_RCV_ERR_PKT, 1, enModemId);
            IMS_NIC_ERROR_LOG_MSG1(UEPS_PID_IMSNIC, "IMS_NIC_UlDataSend, ERROR, receive err pkt, the usEthType = 0x%x!\n", (VOS_INT32)usEtherType);
            return IMS_NIC_FAIL;
    }

    /* 剥离MAC头及偏移地址 */
    pucIpData           = pucData + IMS_NIC_ETH_HDR_SIZE;
    usIpDataLen         = usLen - IMS_NIC_ETH_HDR_SIZE;

    pstImsNicEntity     = IMS_NIC_GET_ENTITY_STRU(enModemId);
    if ( VOS_NULL_PTR   == pstImsNicEntity->pUlDataSendFunc )
    {
        IMS_NIC_STATS_INC(IMS_NIC_STATS_UL_CB_FUN_NOT_REG, 1, enModemId);

        IMS_NIC_ERROR_LOG_MSG(UEPS_PID_IMSNIC, "IMS_NIC_UlDataSend, pUlDataSendFunc is NULL!\n");

        return IMS_NIC_FAIL;
    }

    /* 调用CDS注册的上行数据发送函数 */
    ulResult    = pstImsNicEntity->pUlDataSendFunc(pucIpData, usIpDataLen, enModemId);
    if( IMS_NIC_SUCC != ulResult )
    {
        IMS_NIC_STATS_INC(IMS_NIC_STATS_UL_CALL_CB_FUN_FAIL, 1, enModemId);

        IMS_NIC_ERROR_LOG_MSG(UEPS_PID_IMSNIC, "IMS_NIC_UlDataSend, ERROR, call pUlDataSendFunc fail!\n");

        return IMS_NIC_FAIL;
    }

    /* 上行发送数据统计 */
    IMS_NIC_STATS_INC(IMS_NIC_STATS_UL_SEND_PKT, 1, enModemId);

    /* 更新网卡上行数据发送字节数 */
    IMS_NIC_STATS_INC(IMS_NIC_STATS_UL_SEND_BYTES, usIpDataLen, enModemId);

    return IMS_NIC_SUCC;
}

/*****************************************************************************
 函 数 名  : IMS_NIC_InitAll
 功能描述  : 初始化所有的IMS虚拟网卡
 输入参数  : 无
 输出参数  : 无
 返 回 值  : 成功:IMS_NIC_SUCC，失败为IMS_NIC_FAIL
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2013年7月16日
    作    者   : caikai
    修改内容   : 新生成函数

*****************************************************************************/
VOS_UINT32 IMS_NIC_InitAll(VOS_VOID)
{
    VOS_UINT32      ulResult;
    VOS_UINT16      usIndex;


    if (VOS_OK != IMS_NIC_MNTN_LogEntInit(UEPS_PID_IMSNIC))
    {
        IMS_NIC_INIT_LOG_PRINT(UEPS_PID_IMSNIC, "IMS_NIC_InitAll, ERROR, muxDevStart failed! iResult = %d\n");

        return IMS_NIC_FAIL;
    }

    /* 初始化IMS虚拟网卡 */
    for (usIndex = 0 ; usIndex < IMS_NIC_MODEM_ID_BUTT ; usIndex++)
    {
        ulResult    = IMS_NIC_Init(usIndex);
        if ( IMS_NIC_SUCC != ulResult )
        {
            /* 打印出ulResult的值 */
            IMS_NIC_INIT_LOG_PRINT2(UEPS_PID_IMSNIC, "IMS_NIC_InitAll, ERROR, IMS_NIC_Init Failed, usIndex=%d, ulResult=0x%x\n", usIndex, ulResult);
            return IMS_NIC_FAIL;
        }
    }

#ifdef  ST_IMS_NIC
    ST_IMS_NIC_InitQ();
#endif

    return IMS_NIC_SUCC;
}

/*****************************************************************************
 函 数 名  : IMS_NIC_Addr_Util_GetUnsetBitsInByte
 功能描述  : VISP内存裁剪后不支持地址选择，网卡地址选择在IMS实现。方法由VISP提供
 输入参数  : ucAddressByte          IP地址字节数
             pulLeftUnsetBits

 输出参数  : pulLeftUnsetBits
 返 回 值  : VOS_UINT32
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2015年06月09日
    作    者   : g00178567
    修改内容   : 新生成函数

*****************************************************************************/
VOS_UINT32 IMS_NIC_Addr_Util_GetUnsetBitsInByte(VOS_UINT8 ucAddressByte, VOS_UINT32 *pulLeftUnsetBits)
{
    VOS_UINT32  ulLoopIndex;
    VOS_UINT32  ulCountBits = 0;
    VOS_UINT8   ucAddrByteComplement;
    VOS_UINT8   ucMask = 0x80;

    /* Complement the Byte so that all 0s are converted to 1's and Vice-Versa */
    ucAddrByteComplement = (VOS_UINT8)(~(ucAddressByte));

    for (ulLoopIndex = 0; ulLoopIndex < 8; ulLoopIndex++)
    {
        /* If the result of AND operation between the Mask and the Complemented
           byte is Non-Zero then the count has to be Incremented */
        if (ucMask & ucAddrByteComplement)
        {
            ulCountBits++;
        }
        else
        {
            break;
        }

        /* Right Shift the Mask by 1 */
        ucMask = (VOS_UINT8)(ucMask >> 1);
    }

    *pulLeftUnsetBits = ulCountBits;

    return ADDRADP_OK;
}

/*****************************************************************************
 函 数 名  : IMS_NIC_Addr_Util_GetNumOfMatchingBits
 功能描述  : VISP内存裁剪后不支持地址选择，网卡地址选择在IMS实现。获取匹配bit数
             方法由VISP提供
 输入参数  : pstIP6Addr1
             pstIP6Addr2
             pulMatchBitsNum

 输出参数  : pulLeftUnsetBits
 返 回 值  : VOS_UINT32
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2015年06月09日
    作    者   : g00178567
    修改内容   : 新生成函数

*****************************************************************************/
VOS_UINT32 IMS_NIC_Addr_Util_GetNumOfMatchingBits(const IN6ADDR_S *pstIP6Addr1,
                                         const IN6ADDR_S *pstIP6Addr2,
                                         VOS_UINT32 *pulMatchBitsNum)
{
    IN6ADDR_S       stXoredPattern;
    VOS_UINT32      ulMatchBitsCount = 0;
    VOS_UINT32      ulLoopIndex;
    VOS_UINT32      ulLoopIndex1;
    VOS_UINT8       ucAddrPos = 0;
    VOS_UINT32      ulLeftUnsetBits = 0;

    IMS_NIC_IP6_ADDR_XOR_ADDRESSES(pstIP6Addr1, pstIP6Addr2, stXoredPattern)

    for (ulLoopIndex = 0; ulLoopIndex < 4; ulLoopIndex++)
    {
        if (0 == stXoredPattern.s6_addr32[ulLoopIndex])
        {
            /* Since the complete VOS_UINT32 value is Zero, so increase the number
               of matching bits by 32 */
            ulMatchBitsCount += 32;
        }
        else
        {
            /* The following part of code finds Leftmost Unset bits in a
               VOS_UINT32 */
            for (ulLoopIndex1 = (ulLoopIndex * 4);
                 (0 == (ucAddrPos = stXoredPattern.s6_addr8[ulLoopIndex1]));
                 ulLoopIndex1++)
            {
                ulMatchBitsCount += 8;
            }

            (VOS_VOID)IMS_NIC_Addr_Util_GetUnsetBitsInByte(ucAddrPos, &ulLeftUnsetBits);
            ulMatchBitsCount += ulLeftUnsetBits;

            /* Since Number of matching bits are computed so break and return
              the number of matching bits to the caller */
            break;
        }
    }

    *pulMatchBitsNum = ulMatchBitsCount;

    return ADDRADP_OK;
}

/*****************************************************************************
 函 数 名  : IMS_NIC_MatchSrcAddr
 功能描述  : VISP内存裁剪后不支持地址选择，网卡地址选择在IMS实现。选择源地址
             方法由VISP提供
 输入参数  : pstMatchSrcAddr

 输出参数  : pstMatchSrcAddr
 返 回 值  : VOS_UINT32
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2015年06月09日
    作    者   : g00178567
    修改内容   : 新生成函数

*****************************************************************************/
ULONG IMS_NIC_MatchSrcAddr(TCPIP_ADDR_INFO_S *pstMatchSrcAddr)
{
    VOS_UINT32                          ulCount;
    VOS_UINT32                          ulMatchBitsNum;
    VOS_UINT32                          ulSrcAddrBitsMatch          = 0;
    IN6ADDR_S                           *pstIp6CurIfAddrSel         = VOS_NULL;
    IMS_NIC_ENTITY_STRU                 *pstImsNicEntity;
    IMS_NIC_SINGLE_PDN_INFO_STRU        *pstSinglePdnInfo;
    IMS_NIC_PDN_INFO_STRU               *pstPdnInfo;

    /*目的地址为0,linklocal,多播地址，当前不支持，后续有场景需支持，此处放开*/
    if ( IMS_NIC_IN6_IS_LINKLOCAL(&pstMatchSrcAddr->stDestAddr) ||
         IMS_NIC_IN6_IS_MULTICAST(&pstMatchSrcAddr->stDestAddr) ||
         IMS_NIC_IN6_IS_UNSPECIFIED(&pstMatchSrcAddr->stDestAddr) )
    {
        IMS_NIC_STATS_INC(IMS_NIC_STATS_MATCH_IPV6_ADDR_FAIL, 1, IMS_NIC_MODEM_ID_0);
        return ADDRADP_ERR;
    }

    pstImsNicEntity     = IMS_NIC_GET_ENTITY_STRU(IMS_NIC_MODEM_ID_0);
    pstPdnInfo          = &(pstImsNicEntity->stImsNicPdnInfo);

    /*多网卡，需要遍历网卡*/
    for (ulCount = 0; ulCount < IMS_NIC_RAB_ID_MAX_NUM; ulCount++)
    {
        pstSinglePdnInfo    = &(pstPdnInfo->astImsNicPdnInfo[ulCount]);

        if (VOS_FALSE == pstSinglePdnInfo->bitOpIpv6PdnInfo)
        {
            continue;
        }

        ulMatchBitsNum      = 0;
        (VOS_VOID)IMS_NIC_Addr_Util_GetNumOfMatchingBits(
                                        (const IN6ADDR_S *)pstSinglePdnInfo->stIpv6PdnInfo.aucIpV6Addr,
                                        (const IN6ADDR_S *)&pstMatchSrcAddr->stDestAddr,
                                        &ulMatchBitsNum);

        if (ulMatchBitsNum > ulSrcAddrBitsMatch)
        {
            ulSrcAddrBitsMatch = ulMatchBitsNum;
            pstIp6CurIfAddrSel = (IN6ADDR_S *)pstSinglePdnInfo->stIpv6PdnInfo.aucIpV6Addr;
        }
    }

    if (VOS_NULL != pstIp6CurIfAddrSel)
    {
        PS_MEM_CPY(&pstMatchSrcAddr->stSrcAddr, pstIp6CurIfAddrSel, sizeof(IN6ADDR_S));

        IMS_NIC_STATS_INC(IMS_NIC_STATS_MATCH_IPV6_ADDR_SUCC, 1, IMS_NIC_MODEM_ID_0);

        return ADDRADP_OK;
    }

    IMS_NIC_STATS_INC(IMS_NIC_STATS_MATCH_IPV6_ADDR_FAIL, 1, IMS_NIC_MODEM_ID_0);

    return ADDRADP_ERR;
}

/*****************************************************************************
 函 数 名  : IMS_NIC_IsLocalAddr
 功能描述  : VISP内存裁剪后不支持地址选择，网卡地址选择在IMS实现。判断是否为本地地址
             方法由VISP提供
 输入参数  : pstMatchSrcAddr

 输出参数  : pstMatchSrcAddr
 返 回 值  : VOS_UINT32
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2015年06月09日
    作    者   : g00178567
    修改内容   : 新生成函数

*****************************************************************************/
ULONG IMS_NIC_IsLocalAddr(TCPIP_ADDR_INFO_S *pstMatchSrcAddr)
{
    VOS_UINT32                          ulCount;
    IMS_NIC_ENTITY_STRU                 *pstImsNicEntity;
    IMS_NIC_SINGLE_PDN_INFO_STRU        *pstSinglePdnInfo;
    IMS_NIC_PDN_INFO_STRU               *pstPdnInfo;

    /*目的地址为0,linklocal,多播地址，当前不支持，后续有场景需支持，此处放开*/
    if ( IMS_NIC_IN6_IS_LINKLOCAL(&pstMatchSrcAddr->stDestAddr) ||
         IMS_NIC_IN6_IS_MULTICAST(&pstMatchSrcAddr->stDestAddr) ||
         IMS_NIC_IN6_IS_UNSPECIFIED(&pstMatchSrcAddr->stDestAddr) )
    {
        IMS_NIC_STATS_INC(IMS_NIC_STATS_MATCH_IPV6_ADDR_FAIL, 1, IMS_NIC_MODEM_ID_0);
        return ADDRADP_ERR;
    }

    pstImsNicEntity     = IMS_NIC_GET_ENTITY_STRU(IMS_NIC_MODEM_ID_0);
    pstPdnInfo          = &(pstImsNicEntity->stImsNicPdnInfo);

    if (pstMatchSrcAddr->ulIfIndex)
    {
        if (pstImsNicEntity->ulIfIndex != pstMatchSrcAddr->ulIfIndex)
        {
            IMS_NIC_STATS_INC(IMS_NIC_STATS_LOCAL_IPV6_ADDR_FAIL, 1, IMS_NIC_MODEM_ID_0);

            return ADDRADP_ERR;
        }

        for (ulCount = 0; ulCount < IMS_NIC_RAB_ID_MAX_NUM; ulCount++)
        {
            pstSinglePdnInfo    = &(pstPdnInfo->astImsNicPdnInfo[ulCount]);

            if (VOS_FALSE == pstSinglePdnInfo->bitOpIpv6PdnInfo)
            {
                continue;
            }

            if (0 == PS_MEM_CMP(&pstMatchSrcAddr->stDestAddr, pstSinglePdnInfo->stIpv6PdnInfo.aucIpV6Addr, sizeof(IN6ADDR_S)))
            {
                IMS_NIC_STATS_INC(IMS_NIC_STATS_LOCAL_IPV6_ADDR_SUCC, 1, IMS_NIC_MODEM_ID_0);

                return ADDRADP_OK;
            }
        }
    }
    else
    {
        /*多网卡，需要遍历网卡*/

        for (ulCount = 0; ulCount < IMS_NIC_RAB_ID_MAX_NUM; ulCount++)
        {
            pstSinglePdnInfo    = &(pstPdnInfo->astImsNicPdnInfo[ulCount]);

            if (VOS_FALSE == pstSinglePdnInfo->bitOpIpv6PdnInfo)
            {
                continue;
            }

            if (0 == PS_MEM_CMP(&pstMatchSrcAddr->stDestAddr, pstSinglePdnInfo->stIpv6PdnInfo.aucIpV6Addr, sizeof(IN6ADDR_S)))
            {
                IMS_NIC_STATS_INC(IMS_NIC_STATS_LOCAL_IPV6_ADDR_SUCC, 1, IMS_NIC_MODEM_ID_0);

                return ADDRADP_OK;
            }
        }
    }

    IMS_NIC_STATS_INC(IMS_NIC_STATS_LOCAL_IPV6_ADDR_FAIL, 1, IMS_NIC_MODEM_ID_0);

    return ADDRADP_ERR;
}

/*****************************************************************************
 函 数 名  : IMS_NIC_HaveAddrCheck
 功能描述  : VISP内存裁剪后不支持地址选择，网卡地址选择在IMS实现。地址检查
             方法由VISP提供
 输入参数  : pstMatchSrcAddr

 输出参数  : pstMatchSrcAddr
 返 回 值  : VOS_UINT32
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2015年06月09日
    作    者   : g00178567
    修改内容   : 新生成函数

*****************************************************************************/
ULONG IMS_NIC_HaveAddrCheck(TCPIP_ADDR_INFO_S *pstMatchSrcAddr)
{
    VOS_UINT32                          ulCount;
    IN6ADDR_S                           stZeroAddr;
    IMS_NIC_ENTITY_STRU                 *pstImsNicEntity;
    IMS_NIC_SINGLE_PDN_INFO_STRU        *pstSinglePdnInfo;
    IMS_NIC_PDN_INFO_STRU               *pstPdnInfo;

    pstImsNicEntity     = IMS_NIC_GET_ENTITY_STRU(IMS_NIC_MODEM_ID_0);
    pstPdnInfo          = &(pstImsNicEntity->stImsNicPdnInfo);

    PS_MEM_SET(&stZeroAddr, 0, sizeof(IN6ADDR_S));

    if (pstImsNicEntity->ulIfIndex != pstMatchSrcAddr->ulIfIndex)
    {
        IMS_NIC_STATS_INC(IMS_NIC_STATS_HAVE_IPV6_ADDR_FAIL, 1, IMS_NIC_MODEM_ID_0);

        return ADDRADP_ERR;
    }

    /* 接口是否存在linklocal地址check */
    if (TCPIP_ADDR_LINKLOCAL_FLAG == pstMatchSrcAddr->ulFlag)
    {
        if (0 != PS_MEM_CMP(pstImsNicEntity->aucIpV6LinkLocalAddr, &stZeroAddr, sizeof(IN6ADDR_S)))
        {
            IMS_NIC_STATS_INC(IMS_NIC_STATS_HAVE_IPV6_ADDR_SUCC, 1, IMS_NIC_MODEM_ID_0);

            return ADDRADP_OK;
        }
    }
    else
    {
        for (ulCount = 0; ulCount < IMS_NIC_RAB_ID_MAX_NUM; ulCount++)
        {
            pstSinglePdnInfo    = &(pstPdnInfo->astImsNicPdnInfo[ulCount]);

            if (VOS_FALSE == pstSinglePdnInfo->bitOpIpv6PdnInfo)
            {
                continue;
            }

            if (0 != PS_MEM_CMP(pstSinglePdnInfo->stIpv6PdnInfo.aucIpV6Addr, &stZeroAddr, sizeof(IN6ADDR_S)))
            {
                IMS_NIC_STATS_INC(IMS_NIC_STATS_HAVE_IPV6_ADDR_SUCC, 1, IMS_NIC_MODEM_ID_0);

                return ADDRADP_OK;
            }
        }
    }

    IMS_NIC_STATS_INC(IMS_NIC_STATS_HAVE_IPV6_ADDR_FAIL, 1, IMS_NIC_MODEM_ID_0);

    return ADDRADP_ERR;
}

/*****************************************************************************
 函 数 名  : IMS_NIC_SetLinklocalAddr
 功能描述  : VISP内存裁剪后不支持地址选择，网卡地址选择在IMS实现。设置本地地址
             方法由VISP提供
 输入参数  : pstLinkLocalAddr
             pData

 输出参数  : pstLinkLocalAddr
 返 回 值  : VOS_UINT32
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2015年06月09日
    作    者   : g00178567
    修改内容   : 新生成函数

*****************************************************************************/
VOS_VOID IMS_NIC_SetLinklocalAddr(IN6ADDR_S *pstLinkLocalAddr, VOS_UINT8 *pData)
{
    VOS_UINT8               ucInterfaceID[8];   /* 接口ID */
    IMS_NIC_INTERFACEID_S   stInterfaceId;

    (VOS_VOID)PS_MEM_SET((VOS_UINT8 *)&stInterfaceId, 0, sizeof(IMS_NIC_INTERFACEID_S));
    IMS_NIC_MAP_MAC_INTERFACEID((VOS_UINT8 *)pData, (VOS_UINT8 *)ucInterfaceID);

    (VOS_VOID)PS_MEM_CPY((VOS_UINT8 *)&stInterfaceId, ucInterfaceID, 8);

    pstLinkLocalAddr->s6_addr8[0]   = 0xfe;
    pstLinkLocalAddr->s6_addr8[1]   = 0x80;
    pstLinkLocalAddr->s6_addr16[1]  = 0;
    pstLinkLocalAddr->s6_addr32[1]  = 0;
    pstLinkLocalAddr->s6_addr32[2]  = stInterfaceId.ip6_ifid32[0];
    pstLinkLocalAddr->s6_addr32[3]  = stInterfaceId.ip6_ifid32[1];

    return;
}

/*****************************************************************************
 结构名    : stAddrHook
 协议表格  :
 ASN.1描述 :
 结构说明  : 用于地址选择
*****************************************************************************/
TCPIP_ADDR_HOOK_S stAddrHook =
{
    IMS_NIC_MatchSrcAddr,
    IMS_NIC_IsLocalAddr,
    IMS_NIC_HaveAddrCheck
};

/*****************************************************************************
 函 数 名  : IMS_NIC_ConfigIpv6Addr
 功能描述  : 配置IPV6地址到协议栈
 输入参数  : pucIpAddr      IP地址
             enModemId      当前modemID
             ulBitPrefixLen IPV6前缀长度,单位为bit

 输出参数  : 无
 返 回 值  : VOS_VOID
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2014年3月26日
    作    者   : c00184031
    修改内容   : 新生成函数

*****************************************************************************/
VOS_VOID   IMS_NIC_ConfigIpv6Addr
(
    MODEM_ID_ENUM_UINT16                enModemId,
    VOS_UINT8                          *pucIpAddr,
    VOS_UINT32                          ulBitPrefixLen
)
{
    VOS_INT8                            aucIfName[IMS_NIC_TCPIP_INPUT_LEN]   = {0};
    VOS_UINT8                           aucInput[IMS_NIC_TCPIP_INPUT_LEN];
    VOS_UINT32                          ulRet;
    IMS_NIC_ENTITY_STRU                *pstImsNicEntity;

    /* 外部已检查指针非空 */
    pstImsNicEntity     = IMS_NIC_GET_ENTITY_STRU(enModemId);

    ulRet = TCPIP_GetFullNameByIfIndex(pstImsNicEntity->ulIfIndex, (CHAR *)aucIfName);
    if ( VOS_OK != ulRet )
    {
        IMS_NIC_STATS_INC(IMS_NIC_STATS_GET_IF_NAME_BY_INDEX_FAIL, 1, enModemId);

        /* 可维可测 */
        PS_MEM_SET(aucInput, 0, sizeof(aucInput));

        (VOS_VOID)IMS_NIC_TCPIP_INPUT_STR_LOG2(aucInput, TCPIP_GetFullNameByIfIndex,
            pstImsNicEntity->ulIfIndex, aucIfName, ulRet);

        IMS_NIC_MNTN_TRACE(ID_IMS_NIC_MNTN_TRACE_TCPIP_INPUT_LOG, aucInput, sizeof(aucInput));

        return;
    }

    ulRet             = TCPIP_ShutDownIf(pstImsNicEntity->ulIfIndex);
    if ( (VRP_IFNET_NOERR != ulRet) && (VRP_IFNET_NO_HAVE_BEEN_DOWN != ulRet))
    {
        IMS_NIC_STATS_INC(IMS_NIC_STATS_RESUME_IF_FAIL, 1, enModemId);
    }

    ulRet             = TCPIP_ResumeIf(pstImsNicEntity->ulIfIndex);
    if ( (VRP_IFNET_NOERR != ulRet) && (VRP_IFNET_NO_HAVE_BEEN_DOWN != ulRet))
    {
        IMS_NIC_STATS_INC(IMS_NIC_STATS_RESUME_IF_FAIL, 1, enModemId);
    }

    PS_MEM_SET(aucInput, 0, sizeof(aucInput));

    /* 可维可测 */
    IMS_NIC_TCPIP_INPUT_STR_LOG4(aucInput, IMS_NIC_ConfigIpv6Addr,
        aucIfName, pucIpAddr, IMS_NIC_DEFAULT_IPV6_MASK_LEN, IMS_NIC_TCPIP_GLOBAL_ADDR_FLAG, ulRet);

    IMS_NIC_MNTN_TRACE(ID_IMS_NIC_MNTN_TRACE_TCPIP_INPUT_LOG, aucInput, sizeof(aucInput));

    return;
}

/*****************************************************************************
 函 数 名  : IMS_NIC_ConfigIpv4Addr
 功能描述  : 配置IPV4地址到协议栈
 输入参数  : pucIpAddr      IP地址
             enModemId      当前modemID

 输出参数  : 无
 返 回 值  : VOS_VOID
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2014年3月26日
    作    者   : c00184031
    修改内容   : 新生成函数

*****************************************************************************/
VOS_VOID   IMS_NIC_ConfigIpv4Addr(MODEM_ID_ENUM_UINT16 enModemId, VOS_UINT8 *pucIpAddr)
{
    VOS_UINT32                          ulRet;
    VOS_UINT32                          ulIpAddr;
    VOS_UINT32                          ulMask;
    IMS_NIC_ENTITY_STRU                *pstImsNicEntity;
    VOS_UINT8                           aucInput[IMS_NIC_TCPIP_INPUT_LEN];


    /* 外部已检查指针非空 */

    ulIpAddr        = vrp_ntohl(*(VOS_UINT32 *)pucIpAddr);
    ulMask          = IMS_NIC_TCPIP_DEFAULT_SUBNET_MASK;
    pstImsNicEntity = IMS_NIC_GET_ENTITY_STRU(enModemId);

    ulRet           = TCPIP_ResumeIf(pstImsNicEntity->ulIfIndex);
    if ( (VRP_IFNET_NOERR != ulRet) && (VRP_IFNET_NO_HAVE_BEEN_DOWN != ulRet))
    {
        IMS_NIC_STATS_INC(IMS_NIC_STATS_RESUME_IF_FAIL, 1, enModemId);
    }

    /* 可维可测 */
    PS_MEM_SET(aucInput, 0, sizeof(aucInput));
    (VOS_VOID)IMS_NIC_TCPIP_INPUT_LOG1(aucInput, TCPIP_ResumeIf, pstImsNicEntity->ulIfIndex, ulRet);

    IMS_NIC_MNTN_TRACE(ID_IMS_NIC_MNTN_TRACE_TCPIP_INPUT_LOG, aucInput, sizeof(aucInput));

    ulRet           = TCPIP_AddIpAddr(ulIpAddr, ulMask, pstImsNicEntity->ulIfIndex);

    /* 可维可测 */
    PS_MEM_SET(aucInput, 0, sizeof(aucInput));
    (VOS_VOID)IMS_NIC_TCPIP_INPUT_LOG3(aucInput, TCPIP_AddIpAddr, ulIpAddr,
        ulMask, pstImsNicEntity->ulIfIndex, ulRet);

    IMS_NIC_MNTN_TRACE(ID_IMS_NIC_MNTN_TRACE_TCPIP_INPUT_LOG, aucInput, sizeof(aucInput));

    if ( ERR_AM4_OK != ulRet )
    {
        IMS_NIC_STATS_INC(IMS_NIC_STATS_ADD_IPV4_ADDR_FAIL, 1, enModemId);
    }

    return;
}

/*****************************************************************************
 函 数 名  : IMS_NIC_PdnInfoDelIpv6
 功能描述  : IMS虚拟网卡PDN IPv6配置信息删除
 输入参数  : ucRabId        承载号
             enModemId      当前modemID

 输出参数  : 无
 返 回 值  : VOS_VOID
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2013年7月16日
    作    者   : caikai
    修改内容   : 新生成函数

*****************************************************************************/
VOS_VOID   IMS_NIC_PdnInfoDelIpv6(VOS_UINT8 ucRabId, MODEM_ID_ENUM_UINT16 enModemId)
{
    VOS_INT8                            acIpAddrStr[IMS_NIC_IPV6_ADDR_STR_LEN + 1] = {0};
    VOS_INT8                            acIfName[IMS_NIC_TCPIP_INPUT_LEN]   = {0};
    VOS_UINT8                           aucInput[IMS_NIC_TCPIP_INPUT_LEN]    = {0};
    VOS_UINT32                          ulIfIndex;
    VOS_UINT32                          ulRet;
    IMS_NIC_ENTITY_STRU                *pstImsNicEntity;
    IMS_NIC_SINGLE_PDN_INFO_STRU       *pstSinglePdnInfo;
    IMS_NIC_PDN_INFO_STRU              *pstPdnInfo;

    pstImsNicEntity     = IMS_NIC_GET_ENTITY_STRU(enModemId);
    pstPdnInfo          = &(pstImsNicEntity->stImsNicPdnInfo);
    pstSinglePdnInfo    = &(pstPdnInfo->astImsNicPdnInfo[ucRabId - IMS_NIC_RAB_ID_OFFSET]);

    IMS_NIC_ConvertIpv6AddrToCompressedStr((VOS_UINT8 *)acIpAddrStr, pstSinglePdnInfo->stIpv6PdnInfo.aucIpV6Addr, IMS_NIC_IPV6_STR_RFC2373_TOKENS);

    ulIfIndex       = pstImsNicEntity->ulIfIndex;

    ulRet = TCPIP_GetFullNameByIfIndex(ulIfIndex, (CHAR *)acIfName);
    if ( VOS_OK != ulRet )
    {
        IMS_NIC_STATS_INC(IMS_NIC_STATS_GET_IF_NAME_BY_INDEX_FAIL, 1, enModemId);
        return;
    }

    PS_MEM_SET(aucInput, 0, sizeof(aucInput));

    /* 可维可测 */
    IMS_NIC_TCPIP_INPUT_STR_LOG4(aucInput, IMS_NIC_PdnInfoDelIpv6,
        acIfName, acIpAddrStr, IMS_NIC_DEFAULT_IPV6_MASK_LEN, IMS_NIC_TCPIP_GLOBAL_ADDR_FLAG, ulRet);

    IMS_NIC_MNTN_TRACE(ID_IMS_NIC_MNTN_TRACE_TCPIP_INPUT_LOG, aucInput, sizeof(aucInput));

    /* 先清状态，再清除记录的IP信息 */
    pstSinglePdnInfo->bitOpIpv6PdnInfo      = VOS_FALSE;
    pstSinglePdnInfo->bitOpIpv6DnsPrimCfged = VOS_FALSE;
    pstSinglePdnInfo->bitOpIpv6DnsSecCfged  = VOS_FALSE;

    PS_MEM_SET(&(pstSinglePdnInfo->stIpv6PdnInfo), 0, sizeof(IMS_NIC_IPV6_PDN_INFO_STRU));

    return;
}

/*****************************************************************************
 函 数 名  : IMS_NIC_PdnInfoDelIpv4
 功能描述  : IMS虚拟网卡PDN IPv4配置信息删除
 输入参数  : ucRabId        承载号
             enModemId      当前modemID

 输出参数  : 无
 返 回 值  : VOS_VOID
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2014年3月26日
    作    者   : c00184031
    修改内容   : 新生成函数

*****************************************************************************/
VOS_VOID   IMS_NIC_PdnInfoDelIpv4(VOS_UINT8 ucRabId, MODEM_ID_ENUM_UINT16 enModemId)
{
    IMS_NIC_ENTITY_STRU                *pstImsNicEntity;
    IMS_NIC_SINGLE_PDN_INFO_STRU       *pstSinglePdnInfo;
    IMS_NIC_PDN_INFO_STRU              *pstPdnInfo;
    VOS_UINT32                          ulRet;
    VOS_UINT32                          ulIpAddr;
    VOS_UINT32                          ulMask;
    VOS_UINT8                           aucInput[IMS_NIC_TCPIP_INPUT_LEN] = {0};


    pstImsNicEntity     = IMS_NIC_GET_ENTITY_STRU(enModemId);
    pstPdnInfo          = &(pstImsNicEntity->stImsNicPdnInfo);
    pstSinglePdnInfo    = &(pstPdnInfo->astImsNicPdnInfo[ucRabId - IMS_NIC_RAB_ID_OFFSET]);
    ulIpAddr            = vrp_ntohl(*(VOS_UINT32 *)pstSinglePdnInfo->stIpv4PdnInfo.aucIpV4Addr);
    ulMask              = IMS_NIC_TCPIP_DEFAULT_SUBNET_MASK;

    ulRet = TCPIP_DelIpAddr(ulIpAddr, ulMask, pstImsNicEntity->ulIfIndex);

    /* 可维可测 */
    (VOS_VOID)IMS_NIC_TCPIP_INPUT_LOG3(aucInput, TCPIP_DelIpAddr,
        ulIpAddr, ulMask, pstImsNicEntity->ulIfIndex, ulRet);

    IMS_NIC_MNTN_TRACE(ID_IMS_NIC_MNTN_TRACE_TCPIP_INPUT_LOG, aucInput, sizeof(aucInput));

    if ( ERR_AM4_OK != ulRet )
    {
        IMS_NIC_STATS_INC(IMS_NIC_STATS_DEL_IPV4_ADDR_FAIL, 1, enModemId);
        return;
    }

    /* 先清状态，再清除记录的IP信息 */
    pstSinglePdnInfo->bitOpIpv4PdnInfo      = VOS_FALSE;
    pstSinglePdnInfo->bitOpIpv4DnsPrimCfged = VOS_FALSE;
    pstSinglePdnInfo->bitOpIpv4DnsSecCfged  = VOS_FALSE;

    PS_MEM_SET(&(pstSinglePdnInfo->stIpv4PdnInfo), 0, sizeof(IMS_NIC_IPV4_PDN_INFO_STRU));

    return;
}

/*****************************************************************************
 函 数 名  : IMS_NIC_DnsConfigtoIpStack
 功能描述  : 配置DNS服务器到协议栈
 输入参数  : ucIpAddrLen              -- IP地址长度
             ucDnsIndx                -- 空闲DNS服务器索引
             pucIpAddr                -- 欲配置的DNS服务器IP
 输出参数  : 无
 返 回 值  : 成功:IMS_NIC_SUCC，失败为对应的错误码
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2014年c月26日
    作    者   : c00184031
    修改内容   : 新生成函数

*****************************************************************************/
VOS_VOID IMS_NIC_DnsConfigtoIpStack
(
    VOS_UINT8                           ucIpAddrLen,
    VOS_UINT8                           ucDnsIndx,
    VOS_UINT8                          *pucIpAddr
)
{
    VOS_INT8                            acIpAddrStr[IMS_NIC_IPV6_ADDR_STR_LEN + 1] = {0};
    VOS_UINT8                           aucInput[IMS_NIC_TCPIP_INPUT_LEN] = {0};
    VOS_INT                             iLen;
    VOS_UINT32                          ulRet;


    /* 外部已检查指针非空 */

    if (IMS_NIC_IPV6_ADDR_LENGTH == ucIpAddrLen)
    {
        /* IPv6地址转为字符串 */
        IMS_NIC_ConvertIpv6AddrToCompressedStr((VOS_UINT8 *)acIpAddrStr, pucIpAddr, IMS_NIC_IPV6_STR_RFC2373_TOKENS);

        /* 根据IP地址字符串配置DNS Server到协议栈 */
        ulRet = TCPIP_SetDnsServer(IMS_NIC_TCPIP_ADD_DNS_OP, (CHAR *)acIpAddrStr, IMS_NIC_TCPIP_DNS_CONFIG_IPV6_FLAG);

        /* 可维可测 */
        (VOS_VOID)IMS_NIC_TCPIP_INPUT_STR_LOG3(aucInput, TCPIP_SetDnsServer,
            IMS_NIC_TCPIP_ADD_DNS_OP, IMS_NIC_TCPIP_DNS_CONFIG_IPV6_FLAG, acIpAddrStr, ulRet);

        IMS_NIC_MNTN_TRACE(ID_IMS_NIC_MNTN_TRACE_TCPIP_INPUT_LOG, aucInput, sizeof(aucInput));

        if ( DNSC_SUCCESS != ulRet )
        {
            IMS_NIC_ERROR_LOG_MSG1(UEPS_PID_IMSNIC, "SetDnsServer IPV6 Failed!\n", (VOS_INT32)ulRet);
        }
    }
    else
    {
        /* IPv4地址转为字符串 */
        iLen = IMS_NIC_IP4_TO_STR(acIpAddrStr, pucIpAddr);
        IMS_NIC_SET_CMD_END(acIpAddrStr, iLen);

        /* 根据IP地址字符串配置DNS Server到协议栈 */
        ulRet = TCPIP_SetDnsServer(IMS_NIC_TCPIP_ADD_DNS_OP, (CHAR *)acIpAddrStr, IMS_NIC_TCPIP_DNS_CONFIG_IPV4_FLAG);

        /* 可维可测 */
        (VOS_VOID)IMS_NIC_TCPIP_INPUT_STR_LOG3(aucInput, TCPIP_SetDnsServer,
            IMS_NIC_TCPIP_ADD_DNS_OP, IMS_NIC_TCPIP_DNS_CONFIG_IPV4_FLAG, acIpAddrStr, ulRet);

        IMS_NIC_MNTN_TRACE(ID_IMS_NIC_MNTN_TRACE_TCPIP_INPUT_LOG, aucInput, sizeof(aucInput));

        if ( DNSC_SUCCESS != ulRet )
        {
            IMS_NIC_ERROR_LOG_MSG1(UEPS_PID_IMSNIC, "SetDnsServer IPV4 Failed!\n", (VOS_INT32)ulRet);
        }
    }

    return;
}

/*****************************************************************************
 函 数 名  : IMS_NIC_DnsDeltoIpStack
 功能描述  : 删除DNS服务器到协议栈
 输入参数  : ulIndx           要删除的DNS服务器索引
 输出参数  : 无
 返 回 值  : 成功:IMS_NIC_SUCC，失败为对应的错误码
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2014年c月26日
    作    者   : c00184031
    修改内容   : 新生成函数

*****************************************************************************/
VOS_VOID IMS_NIC_DnsDeltoIpStack
(
    VOS_UINT32                          ulIndx,
    VOS_UINT8                           ucRabId,
    IMS_NIC_DNS_INFO_STRU              *pstDnsInfo
)
{
    VOS_UINT8                           aucInput[IMS_NIC_TCPIP_INPUT_LEN] = {0};
    VOS_INT8                            acIpAddrStr[IMS_NIC_IPV6_ADDR_STR_LEN + 1] = {0};
    VOS_UINT32                          ulRet;
    VOS_INT                             iLen;


    /* 前面已经检查ucRabId合法性和指针非空 */

    if (IMS_NIC_IPV6_ADDR_LENGTH == pstDnsInfo->astImsNicDnsInfo[ulIndx].ucIpAddrLen)
    {
        /* IPv6地址转为字符串 */
        IMS_NIC_ConvertIpv6AddrToCompressedStr((VOS_UINT8 *)acIpAddrStr,
            pstDnsInfo->astImsNicDnsInfo[ulIndx].aucDnsAddr, IMS_NIC_IPV6_STR_RFC2373_TOKENS);

        /* 根据IP地址字符串配置DNS Server到协议栈 */
        ulRet = TCPIP_SetDnsServer(IMS_NIC_TCPIP_DEL_DNS_OP, (CHAR *)acIpAddrStr, IMS_NIC_TCPIP_DNS_CONFIG_IPV6_FLAG);
        if ( DNSC_SUCCESS != ulRet )
        {
            IMS_NIC_ERROR_LOG_MSG1(UEPS_PID_IMSNIC, "SetDnsServer IPV6 Failed!\n", (VOS_INT32)ulRet);
        }

        /* 可维可测 */
        (VOS_VOID)IMS_NIC_TCPIP_INPUT_STR_LOG3(aucInput, TCPIP_SetDnsServer,
            IMS_NIC_TCPIP_DEL_DNS_OP, IMS_NIC_TCPIP_DNS_CONFIG_IPV6_FLAG, acIpAddrStr, ulRet);

        IMS_NIC_MNTN_TRACE(ID_IMS_NIC_MNTN_TRACE_TCPIP_INPUT_LOG, aucInput, sizeof(aucInput));
    }
    else
    {
        /* IPv4地址转为字符串 */
        iLen = IMS_NIC_IP4_TO_STR(acIpAddrStr, pstDnsInfo->astImsNicDnsInfo[ulIndx].aucDnsAddr);
        IMS_NIC_SET_CMD_END(acIpAddrStr, iLen);

        /* 根据IP地址字符串配置DNS Server到协议栈 */
        ulRet = TCPIP_SetDnsServer(IMS_NIC_TCPIP_DEL_DNS_OP, (CHAR *)acIpAddrStr, IMS_NIC_TCPIP_DNS_CONFIG_IPV4_FLAG);
        if ( DNSC_SUCCESS != ulRet )
        {
            IMS_NIC_ERROR_LOG_MSG1(UEPS_PID_IMSNIC, "SetDnsServer IPV4 Failed!\n", (VOS_INT32)ulRet);
        }

        /* 可维可测 */
        (VOS_VOID)IMS_NIC_TCPIP_INPUT_STR_LOG3(aucInput, TCPIP_SetDnsServer,
            IMS_NIC_TCPIP_DEL_DNS_OP, IMS_NIC_TCPIP_DNS_CONFIG_IPV4_FLAG, acIpAddrStr, ulRet);

        IMS_NIC_MNTN_TRACE(ID_IMS_NIC_MNTN_TRACE_TCPIP_INPUT_LOG, aucInput, sizeof(aucInput));
    }

    return;
}

/*****************************************************************************
 函 数 名  : IMS_NIC_ResetAll
 功能描述  : 将IMS NIC模块设置到初始状态
 输入参数  : MODEM_ID_ENUM_UINT16 enModemId MODEM ID号

 输出参数  : 无
 返 回 值  : 无
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2014年3月26日
    作    者   : c00184031
    修改内容   : 新生成函数
*****************************************************************************/
VOS_VOID IMS_NIC_ResetAll(MODEM_ID_ENUM_UINT16 enModemId)
{
    IMS_NIC_ENTITY_STRU                *pstImsNicEntity;
    VOS_UINT8                           aucInput[IMS_NIC_TCPIP_INPUT_LEN] = {0};
    VOS_UINT32                          ulRet;


    pstImsNicEntity     = IMS_NIC_GET_ENTITY_STRU(enModemId);

    ulRet = TCPIP_ShutDownIf(pstImsNicEntity->ulIfIndex);
    if ( VRP_IFNET_NOERR != ulRet )
    {
        IMS_NIC_STATS_INC(IMS_NIC_STATS_NETIF_RESET_FAIL, 1, enModemId);
    }

    /* 可维可测 */
    (VOS_VOID)IMS_NIC_TCPIP_INPUT_LOG1(aucInput, TCPIP_ShutDownIf, pstImsNicEntity->ulIfIndex, ulRet);

    IMS_NIC_MNTN_TRACE(ID_IMS_NIC_MNTN_TRACE_TCPIP_INPUT_LOG, aucInput, sizeof(aucInput));

    PS_MEM_SET(&(pstImsNicEntity->stImsNicPdnInfo), 0, sizeof(IMS_NIC_PDN_INFO_STRU));

    return;
}

/*****************************************************************************
 函 数 名  : IMS_NIC_SetDefaultRoute
 功能描述  : 配置默认路由
 输入参数  : enModemId   Modem编号
 输出参数  : 无
 返 回 值  : 无
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2014年3月29日
    作    者   : c00184031
    修改内容   : 新生成函数

*****************************************************************************/
VOS_VOID IMS_NIC_SetDefaultRoute(MODEM_ID_ENUM_UINT16 enModemId)
{
    VOS_UINT8                           aucInput[IMS_NIC_TCPIP_INPUT_LEN];
    VOS_INT8                            acIfName[IMS_NIC_TCPIP_INPUT_LEN] = {0};
    VOS_UINT32                          ulRet;
    IMS_NIC_ENTITY_STRU                *pstImsNicEntity;

    pstImsNicEntity     = IMS_NIC_GET_ENTITY_STRU(enModemId);

    /* 配置IPV4默认路由到虚拟网卡上 */
    /* 默认路由IP地址和掩码长度设为0 */
    ulRet = TCPIP_RouteAdd(0, 0, IMS_NIC_DEFAULT_ROUTE_GATEWAY, pstImsNicEntity->ulIfIndex, IMS_NIC_TCPIP_DEFAULT_ROUTE_PRIORITY);

    /* 可维可测 */
    PS_MEM_SET(aucInput, 0, sizeof(aucInput));
    (VOS_VOID)IMS_NIC_TCPIP_INPUT_LOG3(aucInput, TCPIP_RouteAdd,
        IMS_NIC_DEFAULT_ROUTE_GATEWAY,
        pstImsNicEntity->ulIfIndex, IMS_NIC_TCPIP_DEFAULT_ROUTE_PRIORITY, ulRet);

    IMS_NIC_MNTN_TRACE(ID_IMS_NIC_MNTN_TRACE_TCPIP_INPUT_LOG, aucInput, sizeof(aucInput));

    if ( VOS_OK != ulRet )
    {
        IMS_NIC_STATS_INC(IMS_NIC_STATS_CONFIG_IPV4_ROUTE_FAIL, 1, enModemId);
        return;
    }

    /* 配置IPV6默认路由到虚拟网卡上 */
    ulRet = TCPIP_GetFullNameByIfIndex(pstImsNicEntity->ulIfIndex, (CHAR *)acIfName);

    /* 可维可测 */
    PS_MEM_SET(aucInput, 0, sizeof(aucInput));
    (VOS_VOID)IMS_NIC_TCPIP_INPUT_STR_LOG2(aucInput, TCPIP_GetFullNameByIfIndex,
        pstImsNicEntity->ulIfIndex, acIfName, ulRet);

    IMS_NIC_MNTN_TRACE(ID_IMS_NIC_MNTN_TRACE_TCPIP_INPUT_LOG, aucInput, sizeof(aucInput));

    if ( VOS_OK != ulRet )
    {
        IMS_NIC_STATS_INC(IMS_NIC_STATS_GET_IF_NAME_BY_INDEX_FAIL, 1, enModemId);
        return;
    }

    return;
}

/*****************************************************************************
 函 数 名  : IMS_NIC_SetSocketPort
 功能描述  : 配置Socket端口上下限
 输入参数  : usMinPort   端口下限
             usMaxPort   端口上限
             enModemId   当前网卡
 输出参数  : 无
 返 回 值  : 无
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2014年1月13日
    作    者   : c00184031
    修改内容   : 新生成函数

*****************************************************************************/
VOS_UINT32 IMS_NIC_SetSocketPort
(
    VOS_UINT16                          usMinPort,
    VOS_UINT16                          usMaxPort,
    MODEM_ID_ENUM_UINT16                enModemId
)
{
    VOS_UINT8                           aucInput[IMS_NIC_TCPIP_INPUT_LEN] = {0};
    VOS_UINT32                          ulRet;
    SOCK_GLOBLE_S                       stSockGlobal;


    stSockGlobal.usAutoPortStart   = usMinPort;
    stSockGlobal.usAutoPortEnd     = usMaxPort;

    if (usMinPort > usMaxPort)
    {
        IMS_NIC_ERROR_LOG2(UEPS_PID_IMSNIC,
            "IMS_NIC_SetSocketPort, ERROR, min, max", usMinPort, usMaxPort);

        IMS_NIC_STATS_INC(IMS_NIC_STATS_PORT_CONFIG_INVALID, 1, enModemId);

        return IMS_NIC_FAIL;
    }

    ulRet = TCPIP_SetSockGlobleConfig(&stSockGlobal);
    if ( VOS_OK != ulRet )
    {
        IMS_NIC_ERROR_LOG3(UEPS_PID_IMSNIC,
            "IMS_NIC_SetSocketPort, ERROR, min, max", usMinPort, usMaxPort, ulRet);
    }

    /* 可维可测 */
    (VOS_VOID)IMS_NIC_TCPIP_INPUT_LOG2(aucInput, TCPIP_SetSockGlobleConfig,
        stSockGlobal.usAutoPortStart, stSockGlobal.usAutoPortEnd, ulRet);

    IMS_NIC_MNTN_TRACE(ID_IMS_NIC_MNTN_TRACE_TCPIP_INPUT_LOG, aucInput, sizeof(aucInput));

    return ulRet;
}

/*****************************************************************************
 函 数 名  : IMS_NIC_MtuSet
 功能描述  : IMS虚拟网卡MTU设置
 输入参数  : ulMtu        最大发送单元
 输出参数  : 无
 返 回 值  : 成功:IMS_NIC_SUCC，失败为对应的错误码
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2014年3月14日
    作    者   : lvcunpai
    修改内容   : 新生成函数

*****************************************************************************/
VOS_UINT32 IMS_NIC_MtuSet(VOS_UINT32 ulMtu)
{
    VOS_UINT16                          usIndex;
    IMS_NIC_ENTITY_STRU                *pstImsNicEntity;
    VOS_UINT32                          ulRet;
    VOS_UINT8                           aucInput[IMS_NIC_TCPIP_INPUT_LEN] = {0};


    /* ulMtu长度不在有效范围内 */
    if ( (ulMtu < IMS_NIC_MIN_IPPKT_LEN) || (ulMtu > IMS_NIC_MAX_IPPKT_LEN) )
    {
        /* 默认记录到Modem0的实体中 */;
        IMS_NIC_STATS_INC(IMS_NIC_STATS_MTU_INVALID, 1, IMS_NIC_MODEM_ID_0);

        return IMS_NIC_MTU_INVALID;
    }

    for (usIndex = 0 ; usIndex < IMS_NIC_MODEM_ID_BUTT ; usIndex++)
    {
        pstImsNicEntity     = IMS_NIC_GET_ENTITY_STRU(usIndex);

        /* 虚拟网卡已经初始化，调用ifconfig命令配置MTU */
        if ( VOS_TRUE == pstImsNicEntity->ulImsNicInitFlag )
        {
            ulRet = TCPIP_SetLinkMtu(pstImsNicEntity->ulIfIndex, ulMtu);

            /* 可维可测 */
            (VOS_VOID)IMS_NIC_TCPIP_INPUT_LOG2(aucInput, TCPIP_SetLinkMtu,
                pstImsNicEntity->ulIfIndex, ulMtu, ulRet);

            IMS_NIC_MNTN_TRACE(ID_IMS_NIC_MNTN_TRACE_TCPIP_INPUT_LOG, aucInput, sizeof(aucInput));

            if ( VRP_IFNET_NOERR != ulRet )
            {
                IMS_NIC_STATS_INC(IMS_NIC_STATS_MTU_CONFIG_FAIL, 1, usIndex);
            }

            ulRet = ADDR_Set_Mtu(pstImsNicEntity->ulIfIndex, ulMtu);

            /* 可维可测 */
            PS_MEM_SET(aucInput, 0, sizeof(aucInput));
            (VOS_VOID)IMS_NIC_TCPIP_INPUT_LOG2(aucInput, ADDR_Set_Mtu,
                pstImsNicEntity->ulIfIndex, ulMtu, ulRet);

            IMS_NIC_MNTN_TRACE(ID_IMS_NIC_MNTN_TRACE_TCPIP_INPUT_LOG, aucInput, sizeof(aucInput));

            if ( VOS_OK != ulRet )
            {
                IMS_NIC_STATS_INC(IMS_NIC_STATS_MTU_CONFIG_FAIL, 1, usIndex);
                continue;
            }
        }

        /* 修改IMS_NIC_MTU_VALUE的值，虚拟网卡初始化时会设置该值为MTU大小 */
        IMS_NIC_SET_MTU(ulMtu);
    }

    return IMS_NIC_SUCC;
}


/*****************************************************************************
 函 数 名  : IMS_NIC_DlDataRcv
 功能描述  : IMS虚拟网卡下行数据接收接口，提供给CDS调用
 输入参数  : pucData      IP包数据
             usLen        IP包长度
             enModemId    当前modemID
 输出参数  :
 返 回 值  : 成功:IMS_NIC_SUCC，失败:IMS_NIC_FAIL
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2014年3月14日
    作    者   : lvcunpai
    修改内容   : 新生成函数

*****************************************************************************/
VOS_UINT32 IMS_NIC_DlDataRcv(VOS_UINT8 *pucData, VOS_UINT16 usLen, MODEM_ID_ENUM_UINT16 enModemId)
{
    MBUF_S                             *pMbuf;
    IMS_NIC_ENTITY_STRU                *pstImsNicEntity;
    VOS_UINT32                          ulResult;
    VOS_UINT32                          ulQueueId;
    VOS_UINT8                           ucIpType;

    /* 入参检查 */
    ulResult        = IMS_NIC_DlParaCheck(pucData, usLen, enModemId);
    if ( IMS_NIC_SUCC != ulResult )
    {
        IMS_NIC_ERROR_LOG(UEPS_PID_IMSNIC, "IMS_NIC_DlDataRcv, ERROR, input para invalid!\n");
        IMS_NIC_STATS_INC(IMS_NIC_STATS_DL_RCV_ERR_PKT, 1, enModemId);

        return IMS_NIC_FAIL;
    }

    /* 解析IP包的版本号 */
    ucIpType    = ((pucData[0] >> IMS_NIC_IP_VERSION_POS) & IMS_NIC_IP_VERSION_MASK);

    switch (ucIpType)
    {
        case IMS_NIC_IPV4_VERSION:
            IMS_NIC_STATS_INC(IMS_NIC_STATS_DL_RCV_IPV4_PKT, 1, enModemId);
            ulQueueId = QUE_IP_INPUT;
            break;

        case IMS_NIC_IPV6_VERSION:
            IMS_NIC_STATS_INC(IMS_NIC_STATS_DL_RCV_IPV6_PKT, 1, enModemId);
            ulQueueId = QUE_IPV6_INPUT;
            break;

        default:
            IMS_NIC_STATS_INC(IMS_NIC_STATS_DL_RCV_ERR_PKT, 1, enModemId);

            IMS_NIC_ERROR_LOG1(UEPS_PID_IMSNIC, "IMS_NIC_DlDataRcv, ERROR, ucIpType=%d error!\n", ucIpType);
            return IMS_NIC_FAIL;
    }

    /* 申请MBUF内存并将数据拷入 */
    pMbuf = MBUF_CreateByCopyBuffer(IMS_NIC_TCPIP_HEADER_RESERVE_LEN, usLen, pucData, MBUF_TYPE_DATA, 0);
    if ( VOS_NULL_PTR == pMbuf )
    {
        IMS_NIC_ERROR_LOG(UEPS_PID_IMSNIC, "CreateByCopyBuffer Fail!\n");

        return IMS_NIC_FAIL;
    }

    pstImsNicEntity     = IMS_NIC_GET_ENTITY_STRU(enModemId);

    /* IP报文入队 */
    ulResult            = TCPIP_EnMBufQueue(pMbuf, ulQueueId, pstImsNicEntity->ulIfIndex);
    if ( VRP_IFNET_NOERR != ulResult)
    {
        IMS_NIC_ERROR_LOG(UEPS_PID_IMSNIC, "EnMBufQueue Fail!\n");

        return IMS_NIC_FAIL;
    }

    /* 下行发送数据统计 */
    IMS_NIC_STATS_INC(IMS_NIC_STATS_DL_SEND_PKT, 1, enModemId);

    /* 更新网卡下行数据接收字节数 */
    IMS_NIC_STATS_INC(IMS_NIC_STATS_DL_RCV_BYTES, usLen, enModemId);

    return IMS_NIC_SUCC;
}

/*****************************************************************************
 函 数 名  : IMS_NIC_Delete
 功能描述  : IMS虚拟网卡卸载函数
 输入参数  : enModemId      --当前Modem号
 输出参数  : 无
 返 回 值  : 成功:IMS_NIC_SUCC，失败为对应的错误码
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2014年3月14日
    作    者   : lvcunpai
    修改内容   : 新生成函数

*****************************************************************************/
VOS_UINT32 IMS_NIC_Delete (MODEM_ID_ENUM_UINT16 enModemId)
{
    VOS_UINT32                          ulIfIndex;
    VOS_UINT32                          ulRet;
    IMS_NIC_ENTITY_STRU                *pstImsNicEntity;
    VOS_UINT8                           aucInput[IMS_NIC_TCPIP_INPUT_LEN] = {0};


    if ( enModemId >= IMS_NIC_MODEM_ID_BUTT )
    {
        /* 默认记录到Modem0的实体中 */;
        IMS_NIC_STATS_INC(IMS_NIC_STATS_MODEM_ID_ERR_OTHER, 1, IMS_NIC_MODEM_ID_0);

        IMS_NIC_ERROR_LOG1(UEPS_PID_IMSNIC, "IMS_NIC_Free, ERROR, Input modem id invalid!\n", enModemId);

        return IMS_NIC_MODEM_ID_INVALID;
    }

    /* 根据modem id找到IfIndex */
    pstImsNicEntity     = IMS_NIC_GET_ENTITY_STRU(enModemId);
    ulIfIndex           = pstImsNicEntity->ulIfIndex;

    /* 该虚拟网卡没有初始化 */
    if ( VOS_TRUE != pstImsNicEntity->ulImsNicInitFlag )
    {
        IMS_NIC_STATS_INC(IMS_NIC_STATS_NOT_INITED_ERR, 1, enModemId);

        return IMS_NIC_NOT_INITED;
    }

    ulRet = TCPIP_DeleteIF(ulIfIndex);

    /* 可维可测 */
    (VOS_VOID)IMS_NIC_TCPIP_INPUT_LOG1(aucInput, TCPIP_DeleteIF, pstImsNicEntity->ulIfIndex, ulRet);

    IMS_NIC_MNTN_TRACE(ID_IMS_NIC_MNTN_TRACE_TCPIP_INPUT_LOG, aucInput, sizeof(aucInput));

    if (VRP_IFNET_NOERR != ulRet)
    {
        IMS_NIC_STATS_INC(IMS_NIC_STATS_SYS_CALL_FAIL, 1, enModemId);

        IMS_NIC_ERROR_LOG1(UEPS_PID_IMSNIC, "IMS_NIC_Free, ERROR, call DeleteIF fail!\n", enModemId);

        return IMS_NIC_SYSCALLFAIL;
    }

    pstImsNicEntity->ulImsNicInitFlag = VOS_FALSE;

    return IMS_NIC_SUCC;
}

/*****************************************************************************
 函 数 名  : IMS_NIC_UL_IPDataSend
 功能描述  : 该函数负责将MUX层出来的数据交给CDS
 输入参数  : pucData      IP包数据
             usLen        IP包长度
             enModemId    当前modemID
 输出参数  : 无
 返 回 值  : 成功:IMS_NIC_SUCC，失败为IMS_NIC_FAIL
 被调函数  :

 修改历史      :
  1.日    期   : 2013年7月16日
    作    者   : caikai
    修改内容   : 新生成函数

*****************************************************************************/
VOS_UINT32 IMS_NIC_UL_IPDataSend(VOS_UINT8 *pucData, VOS_UINT16 usLen, MODEM_ID_ENUM_UINT16 enModemId)
{
    IMS_NIC_ENTITY_STRU                     *pstImsNicEntity;
    VOS_UINT32                               ulResult;
    VOS_UINT8                                ucIpType;

    /* 数据报文长度不在有效值范围内，即[MIN, MTU], 其中MIN为最小IP包大小 */
    if ( VOS_NULL_PTR == pucData )
    {
        IMS_NIC_STATS_INC(IMS_NIC_STATS_UL_INPUT_NULL_PTR, 1, enModemId);

        IMS_NIC_ERROR_LOG(UEPS_PID_IMSNIC, "IMS_NIC_UL_IPDataSend, ERROR, Input data  is invalid!\n");

        return IMS_NIC_FAIL;
    }

    /* 数据报文长度不在有效值范围内，即[MIN, MTU], 其中MIN为最小IP包大小 */
    if ( (usLen < IMS_NIC_MIN_IPPKT_LEN) || (usLen > IMS_NIC_GET_MTU) )
    {
        IMS_NIC_STATS_INC(IMS_NIC_STATS_UL_RCV_DATA_LEN_ERR, 1, enModemId);

        IMS_NIC_ERROR_LOG2(UEPS_PID_IMSNIC, "IMS_NIC_UL_IPDataSend, ERROR, Input data len =%d mtu = %d is invalid!\n", (VOS_INT32)usLen, (VOS_INT32)IMS_NIC_GET_MTU);

        return IMS_NIC_FAIL;
    }

    pstImsNicEntity     = IMS_NIC_GET_ENTITY_STRU(enModemId);
    if ( VOS_NULL_PTR   == pstImsNicEntity->pUlDataSendFunc )
    {
        IMS_NIC_STATS_INC(IMS_NIC_STATS_UL_CB_FUN_NOT_REG, 1, enModemId);

        IMS_NIC_ERROR_LOG(UEPS_PID_IMSNIC, "IMS_NIC_UL_IPDataSend, pUlDataSendFunc is NULL!\n");

        return IMS_NIC_FAIL;
    }

    /* 解析IP包的版本号 */
    ucIpType    = ((pucData[0] >> IMS_NIC_IP_VERSION_POS) & IMS_NIC_IP_VERSION_MASK);
    switch (ucIpType)
    {
        case IMS_NIC_IPV4_VERSION:
            IMS_NIC_STATS_INC(IMS_NIC_STATS_UL_RCV_IPV4_PKT, 1, enModemId);
            break;

        case IMS_NIC_IPV6_VERSION:
            IMS_NIC_STATS_INC(IMS_NIC_STATS_UL_RCV_IPV6_PKT, 1, enModemId);
            break;

        default:
            IMS_NIC_STATS_INC(IMS_NIC_STATS_UL_RCV_ERR_PKT, 1, enModemId);

            IMS_NIC_ERROR_LOG1(UEPS_PID_IMSNIC, "IMS_NIC_UL_IPDataSend, ERROR, ucIpType=%d error!\n", ucIpType);

            return IMS_NIC_FAIL;
    }

    /* 调用CDS注册的上行数据发送函数 */
    ulResult    = pstImsNicEntity->pUlDataSendFunc(pucData, usLen, enModemId);
    if( IMS_NIC_SUCC != ulResult )
    {
        IMS_NIC_STATS_INC(IMS_NIC_STATS_UL_CALL_CB_FUN_FAIL, 1, enModemId);

        IMS_NIC_ERROR_LOG(UEPS_PID_IMSNIC, "IMS_NIC_UL_IPDataSend, ERROR, call pUlDataSendFunc fail!\n");

        return IMS_NIC_FAIL;
    }

    /* 上行发送数据统计 */
    IMS_NIC_STATS_INC(IMS_NIC_STATS_UL_SEND_PKT, 1, enModemId);

    /* 更新网卡上行数据发送字节数 */
    IMS_NIC_STATS_INC(IMS_NIC_STATS_UL_SEND_BYTES, usLen, enModemId);

    return IMS_NIC_SUCC;
}

/*****************************************************************************
 函 数 名  : IMS_NIC_Send
 功能描述  : 该函数负责将MUX层出来的数据交给CDS
 输入参数  : VOS_UINT32 ulPhyLink   --  底层控制块指针
             MBUF_S * pMbuf         --  以太报文,请参考MBUF结构体
 输出参数  : 无
 返 回 值  : 2                      --  需求通知VISP已经处理完成，否则VISP内部还要继续处理数据
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2014年3月14日
    作    者   : lvcunpai
    修改内容   : 新生成函数

*****************************************************************************/
VOS_UINT32 IMS_NIC_Send (VOS_UINT32 ulPhyLink, MBUF_S * pMbuf)
{
    VOS_UINT32                          ulResult;
    VOS_UINT32                          ulIndex;
    VOS_UINT16                          usDataLen;
    VOS_UINT16                          usRemainlen;
    IMS_NIC_DEV_STRU                   *pstImsNicDev;

    if ( VOS_NULL_PTR == pMbuf )
    {
        IMS_NIC_STATS_INC(IMS_NIC_STATS_UL_INPUT_NULL_PTR, 1, IMS_NIC_MODEM_ID_0);

        return IMS_NIC_ERR;
    }

    pstImsNicDev    = IMS_NIC_GET_DEV_STRU_PTR(IMS_NIC_MODEM_ID_0);
    usRemainlen     = (VOS_UINT16)pMbuf->ulTotalDataLength;
    ulIndex         = 0;

    while ( usRemainlen > 0 )
    {
        if ( usRemainlen > IMS_NIC_MAX_IPPKT_LEN )
        {
            usDataLen       = IMS_NIC_MAX_IPPKT_LEN;
            usRemainlen    -= IMS_NIC_MAX_IPPKT_LEN;
        }
        else
        {
            usDataLen       = usRemainlen;
            usRemainlen     = 0;
        }

        ulResult    = MBUF_CopyDataFromMBufToBuffer(pMbuf, ulIndex * IMS_NIC_MAX_IPPKT_LEN,
                            usDataLen, pstImsNicDev->aucSendBuf);
        ulIndex++;

        if ( VOS_OK != ulResult )
        {
            IMS_NIC_STATS_INC(IMS_NIC_STATS_COPY_DATA_FROM_MBUF_FAIL, 1, IMS_NIC_MODEM_ID_0);
            continue;
        }

        /* 上行数据处理 */
        ulResult    = IMS_NIC_UL_IPDataSend(pstImsNicDev->aucSendBuf, usDataLen, IMS_NIC_MODEM_ID_0);
        if ( IMS_NIC_SUCC != ulResult )
        {
            IMS_NIC_ERROR_LOG(UEPS_PID_IMSNIC, "IMS_NIC_Send, call IMS_NIC_UlDataSend!\n");
        }
    }

    /* 调用系统函数释放该MBUF内存 */
    MBUF_Destroy(pMbuf);

    return IMS_NIC_OK;
}

/*****************************************************************************
 函 数 名  : IMS_NIC_Ioctl
 功能描述  : 该函数负责执行IO控制命令
 输入参数  : VOS_UINT32 ulPhyLink       --  底层控制块指针
             VOS_UINT32 ulCmdIndex      --  控制命令字
             char *pData                --  控制参数
 输出参数  : 无
 返 回 值  : VOS_UINT32
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2014年3月14日
    作    者   : lvcunpai
    修改内容   : 新生成函数

*****************************************************************************/
VOS_UINT32 IMS_NIC_Ioctl(VOS_UINT32 ulPhyLink, VOS_UINT32 ulCmdIndex, VOS_CHAR *pData)
{
    IMS_NIC_ENTITY_STRU                *pstImsNicEntity;
    VOS_UINT32                          ulRet;
    IMS_NIC_ELEMENT_TAB_STRU           *pstImsNicElementTbl;
    VOS_UINT8                           aucMacAddr[IMS_NIC_ETHER_ADDR_LEN];

    pstImsNicEntity     = IMS_NIC_GET_ENTITY_STRU(IMS_NIC_MODEM_ID_0);

    switch ( ulCmdIndex )
    {
        case PHY_SHUTDOWN :
            /*底层记录该接口被shutdown标记*/
            /*该标记主要应用于，当底层状态发送变化或有数据报文上送时，如果该接口已经被shutdown，
              则不应该上报底层状态或数据报文*/
            /*此处驱动完成接口Down的处理*/
            ulRet   = TCPIP_IF_LinkIoCtl(pstImsNicEntity->ulIfIndex, ISLDOWN, VOS_NULL_PTR);
            if (VRP_IFNET_NOERR != ulRet)
            {
                IMS_NIC_STATS_INC(IMS_NIC_STATS_ISLUP_FAIL, 1, IMS_NIC_MODEM_ID_0);
            }
            break;

        case PHY_NO_SHUT :
            /*如果底层记录该接口已被shutdown，则清除shutdown标记*/
            /*检查底层是否UP，如果UP，必须上报协议栈底层UP事件*/
            /*此处驱动完成接口noshutdown的处理*/
            ulRet   = TCPIP_IF_LinkIoCtl(pstImsNicEntity->ulIfIndex, ISLUP, VOS_NULL_PTR);
            if (VRP_IFNET_NOERR != ulRet)
            {
                IMS_NIC_STATS_INC(IMS_NIC_STATS_ISLUP_FAIL, 1, IMS_NIC_MODEM_ID_0);
            }
            break;

        case PHY_POWERUP :
            /* 在系统启动时已经初始化了TSEC，此处可以不作任何处理*/
            ulRet   = TCPIP_IF_LinkIoCtl(pstImsNicEntity->ulIfIndex, ISLUP, VOS_NULL_PTR);
            if (VRP_IFNET_NOERR != ulRet)
            {
                IMS_NIC_INIT_LOG_PRINT1(UEPS_PID_IMSNIC,
                    "TCPIP_IF_LinkIoCtl, ISLUP Retrun Value Error!\n", ulRet);

                IMS_NIC_STATS_INC(IMS_NIC_STATS_ISLUP_FAIL, 1, IMS_NIC_MODEM_ID_0);
            }

            /* 向DOPRA IP上报MAC地址，产品首先需要获取接口的MAC地址 */
            /* 每个modem id固定一个MAC地址，这里填的是目的地址 */
            pstImsNicElementTbl = (IMS_NIC_ELEMENT_TAB_STRU *)IMS_NIC_GET_ELEMENT_TABLE(IMS_NIC_MODEM_ID_0);
            PS_MEM_CPY(aucMacAddr, pstImsNicElementTbl->stIpv4Ethhead.aucEtherShost, IMS_NIC_ETHER_ADDR_LEN);

            ulRet = TCPIP_IF_LinkIoCtl(pstImsNicEntity->ulIfIndex, ISLSETMAC, (CHAR *)aucMacAddr);
            if (VRP_IFNET_NOERR != ulRet)
            {
                IMS_NIC_INIT_LOG_PRINT1(UEPS_PID_IMSNIC,
                    "TCPIP_IF_LinkIoCtl, ISLSETMAC Retrun Value Error!\n", ulRet);

                return IMS_NIC_FAIL;
            }

            IMS_NIC_STATS_INC(IMS_NIC_STATS_ISLUP_SUCC, 1, IMS_NIC_MODEM_ID_0);

            break;

        case PHY_JOINMULTI :
            /* 此处驱动将多播地址添加到网卡的多播接收列表中 */
            break;

        case PHY_LEAVEMULTI :
            /* 此处驱动将多播地址从网卡的多播接收列表中删除 */
            break;

        case PHY_DELETE :
            /* 底层删除接口，释放相关资源*/
            return IMS_NIC_SUCC;

        case PHY_SETMACADDR :
            /*增加MAC地址动态设置*/
            break;

        default:
            /* 其他 */;
            return IMS_NIC_FAIL;/* 返回驱动不支持该操作 */
    }

    return IMS_NIC_SUCC;
}

/*****************************************************************************
 函 数 名  : IMS_NIC_Load
 功能描述  : 接口初始化函数
 输入参数  : DEVLINK_S *pstDev      --  网卡设备指针
             VOS_UINT32 *pulIfIndex --  接口索引指针
             VOS_UINT32 *pulSlot    --  当前未使用
             VOS_UINT32 ulSlotNum   --  当前未使用
 输出参数  : 无
 返 回 值  : VOS_UINT32
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2014年3月14日
    作    者   : lvcunpai
    修改内容   : 新生成函数

*****************************************************************************/
VOS_UINT32 IMS_NIC_Load(DEVLINK_S *pstDev, VOS_UINT32 *pulIfIndex, VOS_UINT32 *pulSlot, VOS_UINT32 ulSlotNum)
{
    VOS_UINT32                          ulRet;

    if ( VOS_NULL_PTR == pulIfIndex )
    {
        IMS_NIC_INIT_LOG_PRINT(UEPS_PID_IMSNIC, "IMS_NIC_Load: Null Input Ptr!");

        return IMS_NIC_ERR;
    }

    ulRet = TCPIP_RegFuncPhyIoCtlHook(*pulIfIndex, (IF_PHYIOCTL_FUNC)IMS_NIC_Ioctl);
    if (VRP_IFNET_NOERR != ulRet)
    {
        IMS_NIC_INIT_LOG_PRINT1(UEPS_PID_IMSNIC, "TCPIP_RegFuncPhyIoCtlHook: Error!", ulRet);

        return IMS_NIC_ERR;
    }

    ulRet = TCPIP_RegFuncPhyTransmitHook(*pulIfIndex, (IF_TRANSMIT_FUNC)IMS_NIC_Send);
    if (VRP_IFNET_NOERR != ulRet)
    {
        IMS_NIC_INIT_LOG_PRINT1(UEPS_PID_IMSNIC, "TCPIP_RegFuncPhyTransmitHook: Error!", ulRet);

        return IMS_NIC_ERR;
    }

    return VOS_OK;
}

/*****************************************************************************
 函 数 名  : IMS_NIC_Init
 功能描述  : 创建一维以太设备接口
 输入参数  : enModemId      --当前Modem号
 输出参数  : 无
 返 回 值  : 成功:IMS_NIC_SUCC，失败为对应的错误码
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2014年3月14日
    作    者   : lvcunpai
    修改内容   : 新生成函数
  2.日    期   : 2015年9月5日
    作    者   : w00146666
    修改内容   : 静态告警清理

*****************************************************************************/
VOS_UINT32 IMS_NIC_Init (MODEM_ID_ENUM_UINT16 enModemId)
{
    VOS_UINT32                          ulIfIndex;
    VOS_UINT32                          ulRet;
    DEVLINK_S                           strDev;
    VOS_UINT8                           aucMacAddr[IMS_NIC_ETHER_ADDR_LEN] = {0};
    VOS_UINT32                          ulPortNo;
    const IMS_NIC_ELEMENT_TAB_STRU     *pstImsNicElementTbl;
    IMS_NIC_SEND_UL_DATA_FUNC           pFunc;
    IMS_NIC_ENTITY_STRU                *pstImsNicEntity;
    IN6ADDR_S                           stAddr;

    if ( enModemId >= IMS_NIC_MODEM_ID_BUTT )
    {
        /* 默认记录到Modem0的实体中 */;
        IMS_NIC_INIT_LOG_PRINT1(UEPS_PID_IMSNIC, "IMS_NIC_Init, ERROR, Input modem id invalid!\n", enModemId);

        return IMS_NIC_MODEM_ID_INVALID;
    }

    pstImsNicEntity     = IMS_NIC_GET_ENTITY_STRU(enModemId);

    /* 该虚拟网卡已经初始化 */
    if ( VOS_TRUE == pstImsNicEntity->ulImsNicInitFlag )
    {
        IMS_NIC_INIT_LOG_PRINT(UEPS_PID_IMSNIC, "IMS_NIC_Init, WARNNING, IMS NIC is already initialed!\n");
        return IMS_NIC_ALREADY_INITED;
    }

    /* 初始化虚拟网卡实体pstImsNicEntity */
    PS_MEM_SET(pstImsNicEntity, 0, sizeof(IMS_NIC_ENTITY_STRU));

    pFunc   = IMS_NIC_GET_SAVED_UL_DATA_FUNC(enModemId);

    /* 将保存的上行数据发送回调函数赋值到实体中 */
    pstImsNicEntity->pUlDataSendFunc    = pFunc;

    /* 清零设备节点*/
    PS_MEM_SET( &strDev, 0, sizeof( DEVLINK_S ));

    /* 每个modem id固定一个port no，它只是用来张网卡赋名 */
    ulPortNo = (VOS_UINT32)enModemId;

    /* 初始化设备节点，DEVLINK_S的dev_pDeviceName和dev_pfInitial两个成员的初始化是必须的*/
    (VOS_VOID)VOS_sprintf(strDev.dev_pDeviceName, "UI%d", ulPortNo);
    strDev.dev_pfInitial = (FUNC_PHY_INITIAL)IMS_NIC_Load;

    /* 调用DOPRA IP 接口创建设备的IFNET结构 */
    ulRet = TCPIP_CreateIFByDev(&strDev, (ULONG *)&ulIfIndex);
    if( VRP_IFNET_NOERR != ulRet )
    {
        IMS_NIC_INIT_LOG_PRINT1(UEPS_PID_IMSNIC, "CreateIFByDev ERROR!\n", ulRet);

        return IMS_NIC_FAIL;
    }

    /* 输出IFNET的索引值 */
    /* 索引值保存下来，后面用它来找到创建的网卡 */
    pstImsNicEntity->ulIfIndex = ulIfIndex;

    /* 向DOPRA IP上报MAC地址，产品首先需要获取接口的MAC地址 */
    /* 每个modem id固定一个MAC地址，这里填的是目的地址 */
    pstImsNicElementTbl = (IMS_NIC_ELEMENT_TAB_STRU *)IMS_NIC_GET_ELEMENT_TABLE(enModemId);
    PS_MEM_CPY(aucMacAddr, pstImsNicElementTbl->stIpv4Ethhead.aucEtherShost, IMS_NIC_ETHER_ADDR_LEN);

    IMS_NIC_SetLinklocalAddr(&stAddr, aucMacAddr);
    PS_MEM_CPY(pstImsNicEntity->aucIpV6LinkLocalAddr, &stAddr, sizeof(IN6ADDR_S));

    /* 置上初始化标记 */
    pstImsNicEntity->ulImsNicInitFlag = VOS_TRUE;

    /* 配置MTU,IPV4和IPV6需要用不同接口 */
    ulRet = TCPIP_SetLinkMtu(ulIfIndex, IMS_NIC_GET_MTU);
    if (VRP_IFNET_NOERR != ulRet)
    {
        IMS_NIC_INIT_LOG_PRINT1(UEPS_PID_IMSNIC,
            "TCPIP_SetLinkMtu, Set IPV4 Mtu Fail!\n", ulRet);

        return IMS_NIC_FAIL;
    }

    ulRet = ADDR_IPv6EnableOnIntf_Host((CHAR *)strDev.dev_pDeviceName, IMS_NIC_ENABLE_HOST_MODE);
    if ( ADDRADP_OK != ulRet)
    {
        IMS_NIC_INIT_LOG_PRINT1(UEPS_PID_IMSNIC,
            "ADDR_IPv6EnableOnIntf_Host, Enable Ipv6 Interface Fail!\n", ulRet);
        return IMS_NIC_FAIL;
    }

    ulRet = ADDR_Set_Mtu(ulIfIndex, IMS_NIC_GET_MTU);
    if (VOS_OK != ulRet)
    {
        IMS_NIC_INIT_LOG_PRINT1(UEPS_PID_IMSNIC,
            "ADDR_Set_Mtu, Set IPV6 Mtu Fail!\n", ulRet);

        return IMS_NIC_FAIL;
    }

    /* 关闭串口的VISP打印 */
    TCPIP_OutputToCOM(0);

    return IMS_NIC_SUCC;
}


/*****************************************************************************
 函 数 名  : IMS_NIC_GetMntnInfo
 功能描述  : 获取IMS虚拟网卡的统计信息，用于周期性上报
 输入参数  : usType         -- 可维可测消息类型
 输出参数  : pucData        -- 存储数据的内存
             pulLen         -- 数据长度
 返 回 值  : 成功:IMS_NIC_OK，失败为IMS_NIC_FAIL
 被调函数  :

 修改历史      :
  1.日    期   : 2013年7月16日
    作    者   : caikai
    修改内容   : 新生成函数

*****************************************************************************/
VOS_UINT32 IMS_NIC_GetMntnInfo
(
    VOS_UINT8                       *pucData,
    VOS_UINT32                      *pulLen,
    VOS_UINT16                       usType
)
{
    VOS_UINT16                      usIndex;
    IMS_NIC_ENTITY_STRU            *pstImsNicEntity;
    VOS_UINT32                      ulModemCnt;


    if ( VOS_NULL_PTR == pucData )
    {
        IMS_NIC_ERROR_LOG(UEPS_PID_IMSNIC, "IMS_NIC_GetMntnInfo, ERROR, Input pucData id null!\n");
        return IMS_NIC_FAIL;
    }

    if ( VOS_NULL_PTR == pulLen )
    {
        IMS_NIC_ERROR_LOG(UEPS_PID_IMSNIC, "IMS_NIC_GetMntnInfo, ERROR, Input pulLen id null!\n");
        return IMS_NIC_FAIL;
    }

    *pulLen     = 0;

    /* 填写Modem个数 */
    ulModemCnt  = (VOS_UINT32)IMS_NIC_MODEM_ID_BUTT;
    (VOS_VOID)mdrv_memcpy(pucData, &ulModemCnt, sizeof(ulModemCnt));
    pucData     += sizeof(ulModemCnt);

    for (usIndex = 0 ; usIndex < IMS_NIC_MODEM_ID_BUTT ; usIndex++)
    {
        pstImsNicEntity     = IMS_NIC_GET_ENTITY_STRU(usIndex);

        /* 填写modemId */
        (VOS_VOID)mdrv_memcpy(pucData, &usIndex, IMS_NIC_MODEM_ID_LEN);
        pucData     += IMS_NIC_MODEM_ID_OFFSET;
        *pulLen     += IMS_NIC_MODEM_ID_OFFSET;

        /* 拷贝统计信息 */
        (VOS_VOID)mdrv_memcpy(pucData, (VOS_UINT8 *)(&(pstImsNicEntity->stImsNicStatsInfo)), sizeof(IMS_NIC_STATS_INFO_STRU));
        pucData     += sizeof(IMS_NIC_STATS_INFO_STRU);
        *pulLen     += sizeof(IMS_NIC_STATS_INFO_STRU);
    }

    return IMS_NIC_SUCC;
}

/*****************************************************************************
 函 数 名  : IMS_NIC_Help
 功能描述  : 显示网卡所有Debug函数
 输入参数  :
 输出参数  : 无
 返 回 值  : 无
 被调函数  :

 修改历史      :
  1.日    期   : 2013年7月16日
    作    者   : t00148005
    修改内容   : 新生成函数

*****************************************************************************/
VOS_VOID IMS_NIC_Help(VOS_VOID)
{
    (VOS_VOID)vos_printf("打印网卡状态信息：IMS_NIC_ShowEntityState \n");
    (VOS_VOID)vos_printf("打印网卡统计信息：IMS_NIC_ShowStats \n");
    (VOS_VOID)vos_printf("MuxShow：IMS_NIC_MuxShow \n");
}


/*****************************************************************************
 函 数 名  : IMS_NIC_ShowEntityState
 功能描述  : 显示网卡状态信息,配置的IP, DNS等
 输入参数  :
 输出参数  : 无
 返 回 值  : 无
 被调函数  :

 修改历史      :
  1.日    期   : 2013年7月16日
    作    者   : t00148005
    修改内容   : 新生成函数

*****************************************************************************/
VOS_VOID IMS_NIC_ShowEntityState(VOS_VOID)
{
    VOS_UINT8                       ucRabId;
    VOS_INT32                       iIndx1;
    VOS_INT32                       iIndx2;
    VOS_INT32                       iIndx3;
    VOS_UINT16                     *pusIpv6;
    VOS_UINT8                      *pucIpv4;
    IMS_NIC_ENTITY_STRU            *pstImsNicEntity;
    IMS_NIC_SINGLE_DNS_INFO_STRU   *pstSingleDnsInfo;
    IMS_NIC_SINGLE_PDN_INFO_STRU   *pstSinglePdnInfo;


    for (iIndx1 = 0; iIndx1 < IMS_NIC_MODEM_ID_BUTT; iIndx1++)
    {
        pstImsNicEntity = IMS_NIC_GET_ENTITY_STRU(iIndx1);
        (VOS_VOID)vos_printf("======================Entity info for Modem %d ======================\n", iIndx1);
        (VOS_VOID)vos_printf("实体初始化状态:             %d \n", pstImsNicEntity->ulImsNicInitFlag);
        (VOS_VOID)vos_printf("上行发数回调函数指针地址:   0x%x \n", pstImsNicEntity->pUlDataSendFunc);
        (VOS_VOID)vos_printf("当前配置PDN个数:            %d \n", pstImsNicEntity->stImsNicPdnInfo.iPdnCfgCnt);
        (VOS_VOID)vos_printf("当前配置的DNS个数:          %d \n", pstImsNicEntity->stImsNicPdnInfo.stImsNicDnsInfo.ucDnsServerCnt);

        for (iIndx2 = 0; iIndx2 < IMS_NIC_MAX_DNS_SERVER_NUM; iIndx2++)
        {
            pstSingleDnsInfo = &pstImsNicEntity->stImsNicPdnInfo.stImsNicDnsInfo.astImsNicDnsInfo[iIndx2];
            if (IMS_NIC_IPV6_ADDR_LENGTH == pstSingleDnsInfo->ucIpAddrLen)
            {
                pusIpv6 = (VOS_UINT16 *)pstSingleDnsInfo->aucDnsAddr;

                (VOS_VOID)vos_printf("%s 的引用次数:%d, 地址长度:%d, 地址:%x:%x:%x:%x:%x:%x:%x:%x \n",
                            g_pcDnsSSysVarName[iIndx2], pstSingleDnsInfo->cDnsRef, pstSingleDnsInfo->ucIpAddrLen,
                            VOS_HTONS(pusIpv6[0]), VOS_HTONS(pusIpv6[1]), VOS_HTONS(pusIpv6[2]), VOS_HTONS(pusIpv6[3]), VOS_HTONS(pusIpv6[4]), VOS_HTONS(pusIpv6[5]), VOS_HTONS(pusIpv6[6]), VOS_HTONS(pusIpv6[7]));
            }
            else if (IMS_NIC_IPV4_ADDR_LENGTH == pstSingleDnsInfo->ucIpAddrLen)
            {
                pucIpv4 = pstSingleDnsInfo->aucDnsAddr;

                (VOS_VOID)vos_printf("%s 的引用次数:%d, 地址长度:%d, 地址:%d.%d.%d.%d \n",
                            g_pcDnsSSysVarName[iIndx2], pstSingleDnsInfo->cDnsRef, pstSingleDnsInfo->ucIpAddrLen,
                            pucIpv4[0], pucIpv4[1], pucIpv4[2], pucIpv4[3]);
            }
            else
            {
                (VOS_VOID)vos_printf("%s 的引用次数:%d, 地址长度:%d \n", g_pcDnsSSysVarName[iIndx2], pstSingleDnsInfo->cDnsRef, pstSingleDnsInfo->ucIpAddrLen);
            }

        }

        for (iIndx3 = 0; iIndx3 < IMS_NIC_RAB_ID_MAX_NUM; iIndx3++)
        {
            pstSinglePdnInfo = &pstImsNicEntity->stImsNicPdnInfo.astImsNicPdnInfo[iIndx3];

            ucRabId = (VOS_UINT8)iIndx3 + IMS_NIC_RAB_ID_OFFSET;

            (VOS_VOID)vos_printf("PDN %d DNS 配置索引[primaryns]:%d, [secondaryns]:%d, [tertiaryns]:%d, [quaternaryns]:%d \n", ucRabId, pstSinglePdnInfo->aucDnsFlag[0], pstSinglePdnInfo->aucDnsFlag[1], pstSinglePdnInfo->aucDnsFlag[2], pstSinglePdnInfo->aucDnsFlag[3]);
            (VOS_VOID)vos_printf("PDN %d 是否配置IPv4:%d \n", ucRabId, pstSinglePdnInfo->bitOpIpv4PdnInfo);

            if (VOS_TRUE == pstSinglePdnInfo->bitOpIpv4PdnInfo)
            {
                pucIpv4 = pstSinglePdnInfo->stIpv4PdnInfo.aucIpV4Addr;

                (VOS_VOID)vos_printf("PDN %d IPv4地址:%d.%d.%d.%d \n", ucRabId, pucIpv4[0], pucIpv4[1], pucIpv4[2], pucIpv4[3]);
                (VOS_VOID)vos_printf("PDN %d IPv4主DNS信息, bitOpDnsPrim:%d, bitOpDnsPrimCfged:%d \n", ucRabId, pstSinglePdnInfo->stIpv4PdnInfo.bitOpDnsPrim, pstSinglePdnInfo->bitOpIpv4DnsPrimCfged);

                pucIpv4 = pstSinglePdnInfo->stIpv4PdnInfo.aucDnsPrimAddr;
                (VOS_VOID)vos_printf("PDN %d IPv4主DNS地址:%d.%d.%d.%d \n", ucRabId, pucIpv4[0], pucIpv4[1], pucIpv4[2], pucIpv4[3]);

                (VOS_VOID)vos_printf("PDN %d IPv4辅DNS信息, bitOpDnsPrim:%d, bitOpDnsPrimCfged:%d \n", ucRabId, pstSinglePdnInfo->stIpv4PdnInfo.bitOpDnsSec, pstSinglePdnInfo->bitOpIpv4DnsSecCfged);

                pucIpv4 = pstSinglePdnInfo->stIpv4PdnInfo.aucDnsSecAddr;
                (VOS_VOID)vos_printf("PDN %d IPv4主DNS地址:%d.%d.%d.%d \n", ucRabId, pucIpv4[0], pucIpv4[1], pucIpv4[2], pucIpv4[3]);
            }

            (VOS_VOID)vos_printf("PDN %d 是否配置IPv6:%d \n", ucRabId, pstSinglePdnInfo->bitOpIpv6PdnInfo);

            if (VOS_TRUE == pstSinglePdnInfo->bitOpIpv6PdnInfo)
            {
                pusIpv6 = (VOS_UINT16 *)pstSinglePdnInfo->stIpv6PdnInfo.aucIpV6Addr;

                (VOS_VOID)vos_printf("PDN %d IPv6地址:%x:%x:%x:%x:%x:%x:%x:%x \n", ucRabId, VOS_HTONS(pusIpv6[0]), VOS_HTONS(pusIpv6[1]), VOS_HTONS(pusIpv6[2]), VOS_HTONS(pusIpv6[3]), VOS_HTONS(pusIpv6[4]), VOS_HTONS(pusIpv6[5]), VOS_HTONS(pusIpv6[6]), VOS_HTONS(pusIpv6[7]));
                (VOS_VOID)vos_printf("PDN %d IPv6主DNS信息, bitOpDnsPrim:%d, bitOpDnsPrimCfged%d \n", ucRabId, pstSinglePdnInfo->stIpv6PdnInfo.bitOpDnsPrim, pstSinglePdnInfo->bitOpIpv6DnsPrimCfged);

                pusIpv6 = (VOS_UINT16 *)pstSinglePdnInfo->stIpv6PdnInfo.aucDnsPrimAddr;
                (VOS_VOID)vos_printf("PDN %d IPv6主DNS地址:%x:%x:%x:%x:%x:%x:%x:%x \n", ucRabId, VOS_HTONS(pusIpv6[0]), VOS_HTONS(pusIpv6[1]), VOS_HTONS(pusIpv6[2]), VOS_HTONS(pusIpv6[3]), VOS_HTONS(pusIpv6[4]), VOS_HTONS(pusIpv6[5]), VOS_HTONS(pusIpv6[6]), VOS_HTONS(pusIpv6[7]));

                (VOS_VOID)vos_printf("PDN %d IPv6辅DNS信息, bitOpDnsPrim:%d, bitOpDnsPrimCfged:%d \n", ucRabId, pstSinglePdnInfo->stIpv6PdnInfo.bitOpDnsSec, pstSinglePdnInfo->bitOpIpv6DnsSecCfged);

                pusIpv6 = (VOS_UINT16 *)pstSinglePdnInfo->stIpv6PdnInfo.aucDnsSecAddr;
                (VOS_VOID)vos_printf("PDN %d IPv6主DNS地址:%x:%x:%x:%x:%x:%x:%x:%x \n", ucRabId, VOS_HTONS(pusIpv6[0]), VOS_HTONS(pusIpv6[1]), VOS_HTONS(pusIpv6[2]), VOS_HTONS(pusIpv6[3]), VOS_HTONS(pusIpv6[4]), VOS_HTONS(pusIpv6[5]), VOS_HTONS(pusIpv6[6]), VOS_HTONS(pusIpv6[7]));
            }
            (VOS_VOID)vos_printf("\n");
        }
    }
}

/*****************************************************************************
 函 数 名  : IMS_NIC_ShowEntityState
 功能描述  : 显示网卡统计信息，收发包情况，异常统计信息等
 输入参数  :
 输出参数  : 无
 返 回 值  : 无
 被调函数  :

 修改历史      :
  1.日    期   : 2013年7月16日
    作    者   : t00148005
    修改内容   : 新生成函数

*****************************************************************************/
VOS_VOID IMS_NIC_ShowStats(VOS_VOID)
{
    VOS_INT32                i;


    for (i = 0; i < IMS_NIC_MODEM_ID_BUTT; i++)
    {
        (VOS_VOID)vos_printf("======================Debug info for Modem %d ======================\n", i);

        IMS_INC_STATS_SHOW(IMS_NIC_STATS_DL_RCV_IPV4_PKT, i);
        IMS_INC_STATS_SHOW(IMS_NIC_STATS_DL_RCV_IPV6_PKT, i);
        IMS_INC_STATS_SHOW(IMS_NIC_STATS_DL_SEND_PKT, i);
        IMS_INC_STATS_SHOW(IMS_NIC_STATS_DL_RCV_BYTES, i);
        IMS_INC_STATS_SHOW(IMS_NIC_STATS_DL_RCV_ERR_PKT, i);
        IMS_INC_STATS_SHOW(IMS_NIC_STATS_DL_INPUT_NULL_PTR, i);
        IMS_INC_STATS_SHOW(IMS_NIC_STATS_DL_RCV_DATA_LEN_ERR, i);

        IMS_INC_STATS_SHOW(IMS_NIC_STATS_UL_RCV_IPV4_PKT, i);
        IMS_INC_STATS_SHOW(IMS_NIC_STATS_UL_RCV_IPV6_PKT, i);
        IMS_INC_STATS_SHOW(IMS_NIC_STATS_UL_SEND_PKT, i);
        IMS_INC_STATS_SHOW(IMS_NIC_STATS_UL_SEND_BYTES, i);
        IMS_INC_STATS_SHOW(IMS_NIC_STATS_UL_RCV_ERR_PKT, i);
        IMS_INC_STATS_SHOW(IMS_NIC_STATS_UL_RCV_ARP_PKT, i);
        IMS_INC_STATS_SHOW(IMS_NIC_STATS_UL_INPUT_NULL_PTR, i);
        IMS_INC_STATS_SHOW(IMS_NIC_STATS_UL_RCV_DATA_LEN_ERR, i);
        IMS_INC_STATS_SHOW(IMS_NIC_STATS_UL_CB_FUN_NOT_REG, i);
        IMS_INC_STATS_SHOW(IMS_NIC_STATS_UL_CALL_CB_FUN_FAIL, i);
        IMS_INC_STATS_SHOW(IMS_NIC_STATS_UL_PKT_MEM_SEG, i);

        IMS_INC_STATS_SHOW(IMS_NIC_STATS_CFG_DNS_SERVER_FULL, i);
        IMS_INC_STATS_SHOW(IMS_NIC_STATS_CFG_INPUT_NULL_PTR, i);
        IMS_INC_STATS_SHOW(IMS_NIC_STATS_CFG_ADD_MODEM_ID_ERR, i);
        IMS_INC_STATS_SHOW(IMS_NIC_STATS_CFG_DEL_MODEM_ID_ERR, i);

        IMS_INC_STATS_SHOW(IMS_NIC_STATS_CFG_ADD_RAB_ID_ERR, i);
        IMS_INC_STATS_SHOW(IMS_NIC_STATS_CFG_DEL_RAB_ID_ERR, i);

        IMS_INC_STATS_SHOW(IMS_NIC_STATS_GET_CLUSTER_FAIL, i);
        IMS_INC_STATS_SHOW(IMS_NIC_STATS_GET_CLBLK_FAIL, i);
        IMS_INC_STATS_SHOW(IMS_NIC_STATS_GET_MBLK_FAIL, i);
        IMS_INC_STATS_SHOW(IMS_NIC_STATS_MBLK_COPY_ERR, i);
        IMS_INC_STATS_SHOW(IMS_NIC_STATS_NOT_INITED_ERR, i);
        IMS_INC_STATS_SHOW(IMS_NIC_STATS_SYS_CALL_FAIL, i);
        IMS_INC_STATS_SHOW(IMS_NIC_STATS_FIND_DEV_FAIL, i);
        IMS_INC_STATS_SHOW(IMS_NIC_STATS_NO_CFGED_PDN, i);
        IMS_INC_STATS_SHOW(IMS_NIC_STATS_CFG_ADD_NO_PDN, i);
        IMS_INC_STATS_SHOW(IMS_NIC_STATS_CFG_DEL_NO_PDN, i);

        IMS_INC_STATS_SHOW(IMS_NIC_STATS_MODEM_ID_ERR_OTHER, i);
        IMS_INC_STATS_SHOW(IMS_NIC_STATS_MODEM_ID_ERR_IN_REG_CB, i);
        IMS_INC_STATS_SHOW(IMS_NIC_STATS_MODE_ID_ERR_IN_DL_PROC, i);
        IMS_INC_STATS_SHOW(IMS_NIC_STATS_MODE_ID_ERR_IN_UL_PROC, i);

        IMS_INC_STATS_SHOW(IMS_NIC_STATS_MTU_INVALID, i);
        IMS_INC_STATS_SHOW(IMS_NIC_STATS_INVALID_IPV6_PREFIX_LEN, i);
        IMS_INC_STATS_SHOW(IMS_NIC_STATS_MTU_CONFIG_FAIL, i);
        IMS_INC_STATS_SHOW(IMS_NIC_STATS_PORT_CONFIG_INVALID, i);
        IMS_INC_STATS_SHOW(IMS_NIC_STATS_NETIF_RESET_FAIL, i);
        IMS_INC_STATS_SHOW(IMS_NIC_STATS_DEL_IPV4_ADDR_FAIL, i);
        IMS_INC_STATS_SHOW(IMS_NIC_STATS_DEL_IPV6_ADDR_FAIL, i);
        IMS_INC_STATS_SHOW(IMS_NIC_STATS_GET_IF_NAME_BY_INDEX_FAIL, i);
        IMS_INC_STATS_SHOW(IMS_NIC_STATS_ADD_IPV4_ADDR_FAIL, i);
        IMS_INC_STATS_SHOW(IMS_NIC_STATS_ADD_IPV6_ADDR_FAIL, i);
        IMS_INC_STATS_SHOW(IMS_NIC_STATS_CONFIG_IPV4_ROUTE_FAIL, i);
        IMS_INC_STATS_SHOW(IMS_NIC_STATS_CONFIG_IPV6_ROUTE_FAIL, i);
        IMS_INC_STATS_SHOW(IMS_NIC_STATS_COPY_DATA_FROM_MBUF_FAIL, i);
        IMS_INC_STATS_SHOW(IMS_NIC_STATS_RESUME_IF_FAIL, i);
        IMS_INC_STATS_SHOW(IMS_NIC_STATS_SET_STATIC_ARP_FAIL, i);
        IMS_INC_STATS_SHOW(IMS_NIC_STATS_SET_STATIC_ND_FAIL, i);
        IMS_INC_STATS_SHOW(IMS_NIC_STATS_ENABLE_HOST_FAIL, i);
        IMS_INC_STATS_SHOW(IMS_NIC_STATS_ISLUP_SUCC, i);
        IMS_INC_STATS_SHOW(IMS_NIC_STATS_ISLUP_FAIL, i);
        IMS_INC_STATS_SHOW(IMS_NIC_STATS_MATCH_IPV6_ADDR_SUCC, i);
        IMS_INC_STATS_SHOW(IMS_NIC_STATS_MATCH_IPV6_ADDR_FAIL, i);
        IMS_INC_STATS_SHOW(IMS_NIC_STATS_LOCAL_IPV6_ADDR_SUCC, i);
        IMS_INC_STATS_SHOW(IMS_NIC_STATS_LOCAL_IPV6_ADDR_FAIL, i);
        IMS_INC_STATS_SHOW(IMS_NIC_STATS_HAVE_IPV6_ADDR_SUCC, i);
        IMS_INC_STATS_SHOW(IMS_NIC_STATS_HAVE_IPV6_ADDR_FAIL, i);

        (VOS_VOID)vos_printf("\n\n");
    }
}

#ifdef IMS_NIC_DEBUG
VOS_VOID IMS_NIC_TestSdt(VOS_VOID)
{
    IMS_NIC_PDN_INFO_CONFIG_STRU    stConfigInfo;
    VOS_UINT8                       aucDstIpAddr1[4]            = {0x2, 0x1, 0x15, 0x27};
    VOS_UINT32                      ulResult;
    VOS_UINT8   ucRabId1    = 5;
    char *cmd_str1           = "ifconfig -a";
    char *cmd_str2           = "route -n show";

    VOS_MemSet(&stConfigInfo, 0, sizeof(IMS_NIC_PDN_INFO_CONFIG_STRU));

    stConfigInfo.bitOpIpv4PdnInfo   = PS_TRUE;
    stConfigInfo.bitOpIpv6PdnInfo   = PS_FALSE;
    stConfigInfo.enModemId          = 0;
    stConfigInfo.ucRabId            = ucRabId1;
    VOS_MemCpy(stConfigInfo.stIpv4PdnInfo.aucIpV4Addr, aucDstIpAddr1, 4);

    stConfigInfo.stIpv4PdnInfo.bitOpDnsPrim         = PS_FALSE;
    stConfigInfo.stIpv4PdnInfo.bitOpDnsSec          = PS_FALSE;

    ulResult    = IMS_NIC_PdnInfoConfig (&stConfigInfo);
    if (IMS_NIC_SUCC != ulResult)
    {
        (VOS_VOID)vos_printf("ST_DL_RCV_001: config pdn fail! ulResult = %d\n", ulResult);
        return;
    }

    ipcom_run_cmd(cmd_str1);
    ipcom_run_cmd(cmd_str2);

    /* 删除虚拟网卡配置 */
    IMS_NIC_PdnInfoDel(stConfigInfo.ucRabId, 0);

    ipcom_run_cmd(cmd_str1);
    ipcom_run_cmd(cmd_str2);

    return;
}
#endif
#endif  /*FEATURE_ON == FEATURE_IMS*/
/*lint -restore */

/*lint +e534*/

#ifdef __cplusplus
    #if __cplusplus
        }
    #endif
#endif



