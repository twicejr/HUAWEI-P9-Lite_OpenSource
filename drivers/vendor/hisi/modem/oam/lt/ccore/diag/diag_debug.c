


#ifdef __cplusplus
#if __cplusplus
extern "C" {
#endif
#endif

/*lint --e{586}*/
/*****************************************************************************
  1 Include HeadFile
*****************************************************************************/
#include  "msp_debug.h"
#include  "diag_debug.h"
#include  "diag_api.h"
#include  "diag_cfg.h"
#include  "omnvinterface.h"
#include  "SysNvId.h"
#if (VOS_LINUX == VOS_OS_VER)
#include  "OmSocketPpm.h"
#include  "OmVcomPpm.h"
#endif

/*lint -save -e767 原因:Log打印*/
#define    THIS_FILE_ID        MSP_FILE_ID_DIAG_DEBUG_C
/*lint -restore +e767*/

extern VOS_UINT8 g_EventModuleCfg[DIAG_CFG_PID_NUM];

/*****************************************************************************
  2 Declare the Global Variable
*****************************************************************************/

/*****************************************************************************
  3 Function
*****************************************************************************/

/*****************************************************************************
 Function Name   : CBT : Count Branch Timestamp (计数、分支、时间戳定位功能)
 Description     : 用于统计次数和所走分支的问题定位
*****************************************************************************/

DIAG_CBT_INFO_TBL_STRU g_astCBTInfoTbl[EN_DIAG_DEBUG_INFO_MAX] = {{0}};

DIAG_CBT_INFO_TBL_STRU* diag_DebugGetInfo(VOS_VOID)
{
   return g_astCBTInfoTbl;
}

/*****************************************************************************
 Function Name   : diag_CBT
 Description     :
 Input           :DIAG_CBT_ID_ENUM ulType
                VOS_UINT32 ulRserved1
                VOS_UINT32 ulRserved2
                VOS_UINT32 ulRserved3
*****************************************************************************/
VOS_VOID diag_CBT(DIAG_CBT_ID_ENUM ulType,
                     VOS_UINT32 ulRserved1, VOS_UINT32 ulRserved2, VOS_UINT32 ulRserved3)
{
    g_astCBTInfoTbl[ulType].ulCalledNum += 1;
    g_astCBTInfoTbl[ulType].ulRserved1 = ulRserved1;
    g_astCBTInfoTbl[ulType].ulRserved2 = ulRserved2;
    g_astCBTInfoTbl[ulType].ulRserved3 = ulRserved3;
    g_astCBTInfoTbl[ulType].ulRtcTime  = VOS_GetTick();
}


/*****************************************************************************
 Function Name   : LNR : Last N Ring buffer store (最后N条信息循环存储功能)
 Description     : 保存最近的N条信息
*****************************************************************************/

DIAG_LNR_INFO_TBL_STRU g_astLNRInfoTbl[EN_DIAG_LNR_INFO_MAX] = {{0}};

/*****************************************************************************
 Function Name   : diag_LNR
 Description     : 最后NV条信息的记录接口

 History         :
    1.c00326366    2015-06-21 Draft Enact

*****************************************************************************/
VOS_VOID diag_LNR(DIAG_LNR_ID_ENUM ulType, VOS_UINT32 ulRserved1, VOS_UINT32 ulRserved2)
{
    g_astLNRInfoTbl[ulType].ulRserved1[g_astLNRInfoTbl[ulType].ulCur] = ulRserved1;
    g_astLNRInfoTbl[ulType].ulRserved2[g_astLNRInfoTbl[ulType].ulCur] = ulRserved2;
    g_astLNRInfoTbl[ulType].ulCur = (g_astLNRInfoTbl[ulType].ulCur+1)%DIAG_LNR_NUMBER;
}

VOS_VOID DIAG_ShowLNR(DIAG_LNR_ID_ENUM ulType, VOS_UINT32 n)
{
    VOS_UINT32 i;
    VOS_UINT32 cur;

    cur = (g_astLNRInfoTbl[ulType].ulCur + DIAG_LNR_NUMBER - n)%DIAG_LNR_NUMBER;

    for(i = 0; i <n; i++)
    {
        diag_printf("0x%x, 0x%x.\n", g_astLNRInfoTbl[ulType].ulRserved1[cur], g_astLNRInfoTbl[ulType].ulRserved2[cur]);
        cur = (cur + 1)%DIAG_LNR_NUMBER;
    }
}


/*****************************************************************************
 Function Name   : diag_CreateDFR
 Description     : 创建码流录制录制的缓存buffer(初始化时调用)
                    申请的空间长度必须四字节对齐

 History         :
    1.c00326366    2015-06-21 Draft Enact

*****************************************************************************/
VOS_UINT32 diag_CreateDFR(VOS_CHAR *name, VOS_UINT32 ulLen, DIAG_DFR_INFO_STRU *pDfr)
{
    if((VOS_NULL == name)
        || (VOS_NULL == pDfr)
        || (0 == ulLen)
        || (ulLen%4)
        || (ulLen > DIAG_DFR_BUFFER_MAX))
    {
        diag_printf("%s %d.\n", __FUNCTION__, __LINE__);
        return ERR_MSP_FAILURE;
    }

    if (VOS_OK != VOS_SmMCreate("DFR", VOS_SEMA4_PRIOR | VOS_SEMA4_INVERSION_SAFE, &pDfr->semid))
    {
        diag_printf("%s %d.\n", __FUNCTION__, __LINE__);
        return ERR_MSP_FAILURE;
    }

    pDfr->pData = VOS_CacheMemAlloc(ulLen);
    if(VOS_NULL == pDfr->pData)
    {
        diag_printf("%s %d.\n", __FUNCTION__, __LINE__);
        return ERR_MSP_FAILURE;
    }

    (VOS_VOID)VOS_MemSet(pDfr->pData, 0, ulLen);

    (VOS_VOID)VOS_MemCpy(pDfr->name, name, DIAG_DFR_NAME_MAX);
    pDfr->name[DIAG_DFR_NAME_MAX-1]=0;

    pDfr->ulCur = 0;
    pDfr->ulLen = ulLen;
    pDfr->ulMagicNum = DIAG_DFR_MAGIC_NUM;

    return ERR_MSP_SUCCESS;
}


/*****************************************************************************
 Function Name   : diag_SaveDFR
 Description     : 码流录制接口(接收命令和上报命令时调用)

 History         :
    1.c00326366    2015-06-21 Draft Enact

*****************************************************************************/
VOS_VOID diag_SaveDFR(DIAG_DFR_INFO_STRU *pDfr, VOS_UINT8 *pData, VOS_UINT32 ulLen)
{
    VOS_UINT32 ulSize;
    DIAG_DFR_HEADER_STRU stDfrHeader;

    if((VOS_NULL== pDfr)
        || (VOS_NULL == pData)
        || (DIAG_DFR_MAGIC_NUM != pDfr->ulMagicNum)
        || (ulLen > DIAG_DFR_BUFFER_MAX)
        || (pDfr->ulLen > DIAG_DFR_BUFFER_MAX))
    {
        return ;
    }

    /* 如果有任务正在进行中，需要等待其完成 */
    if (VOS_OK != VOS_SmP(pDfr->semid, 0))
    {
        return ;
    }

    stDfrHeader.ulStart = DIAG_DFR_START_NUM;
    stDfrHeader.ulTime  = VOS_GetSlice();

    /* 拷贝开始标记和时间戳 */
    if((pDfr->ulCur + sizeof(DIAG_DFR_HEADER_STRU)) <= pDfr->ulLen)
    {
        (VOS_VOID)VOS_MemCpy(&(pDfr->pData[pDfr->ulCur]), &stDfrHeader, sizeof(DIAG_DFR_HEADER_STRU));
    }
    else
    {
        ulSize = (pDfr->ulLen - pDfr->ulCur);
        (VOS_VOID)VOS_MemCpy(&(pDfr->pData[pDfr->ulCur]), &stDfrHeader, ulSize);
        (VOS_VOID)VOS_MemCpy(&(pDfr->pData[0]), (((VOS_UINT8*)&stDfrHeader) + ulSize), (sizeof(DIAG_DFR_HEADER_STRU) - ulSize));
    }
    pDfr->ulCur = (DFR_ALIGN_WITH_4BYTE(pDfr->ulCur + sizeof(DIAG_DFR_HEADER_STRU))) % pDfr->ulLen;

    /* 拷贝码流 */
    if((pDfr->ulCur + ulLen) <= pDfr->ulLen)
    {
        (VOS_VOID)VOS_MemCpy(&(pDfr->pData[pDfr->ulCur]), pData, ulLen);
    }
    else
    {
        ulSize = (pDfr->ulLen - pDfr->ulCur);
        (VOS_VOID)VOS_MemCpy(&(pDfr->pData[pDfr->ulCur]), pData, ulSize);
        (VOS_VOID)VOS_MemCpy(&(pDfr->pData[0]), (pData + ulSize), (ulLen - ulSize));
    }
    pDfr->ulCur = (DFR_ALIGN_WITH_4BYTE(pDfr->ulCur + ulLen)) % pDfr->ulLen;

    (VOS_VOID)VOS_SmV(pDfr->semid);

    return ;
}


/*****************************************************************************
 Function Name   : diag_GetDFR
 Description     : 码流录制接口(接收命令和上报命令时调用)

 History         :
    1.c00326366    2015-06-21 Draft Enact

*****************************************************************************/
VOS_VOID diag_GetDFR(DIAG_DFR_INFO_STRU *pDfr)
{
    void *pFile;
    VOS_UINT32 ret, len;
    VOS_CHAR FilePath[32] = {0};
    VOS_CHAR *DirPath = "/modem_log/DIAG";
    VOS_CHAR aucInfo[DIAG_DEBUG_INFO_LEN];

    if((VOS_NULL == pDfr) || (DIAG_DFR_MAGIC_NUM != pDfr->ulMagicNum))
    {
        diag_printf("%s %d.\n", __FUNCTION__, __LINE__);
        return ;
    }

    /* 如果DIAG目录不存在则先创建目录 */
    if (VOS_OK != mdrv_file_access(DirPath, 0))
    {
        if (VOS_OK != mdrv_file_mkdir(DirPath))
        {
            (VOS_VOID)vos_printf(" mdrv_file_mkdir /modem_log/DIAG failed.\n");
            return ;
        }
    }

    len = VOS_StrLen("/modem_log/DIAG/");

    (VOS_VOID)VOS_MemCpy(FilePath, "/modem_log/DIAG/", len);

    (VOS_VOID)VOS_MemCpy((FilePath+len), pDfr->name, VOS_StrLen(pDfr->name));

    pFile = mdrv_file_open(FilePath, "wb+");
    if(pFile == 0)
    {
        diag_printf(" mdrv_file_open failed.\n");

        return ;
    }

    ret = DIAG_DebugFileHeader(pFile);
    if(VOS_OK != ret)
    {
        (VOS_VOID)vos_printf(" DIAG_DebugFileHeader failed .\n");
        (VOS_VOID)mdrv_file_close(pFile);
        return ;
    }

    (VOS_VOID)VOS_MemSet(aucInfo, 0, DIAG_DEBUG_INFO_LEN);
    (VOS_VOID)VOS_StrCpy(aucInfo, "DIAG DFR info");

    /* 通用信息 */
    ret = (VOS_UINT32)mdrv_file_write(aucInfo, 1, DIAG_DEBUG_INFO_LEN, pFile);
    if(ret != DIAG_DEBUG_INFO_LEN)
    {
        (VOS_VOID)vos_printf(" mdrv_file_write DIAG number info failed.\n");
    }

    /* 当前指针 */
    ret = (VOS_UINT32)mdrv_file_write(&pDfr->ulCur, 1, sizeof(pDfr->ulCur), pFile);
    if(ret != sizeof(pDfr->ulCur))
    {
        diag_printf(" mdrv_file_write failed 1.\n");
    }

    /* 缓冲区长度 */
    ret = (VOS_UINT32)mdrv_file_write(&pDfr->ulLen, 1, sizeof(pDfr->ulCur), pFile);
    if(ret != sizeof(pDfr->ulCur))
    {
        diag_printf(" mdrv_file_write failed 1.\n");
    }

    ret = (VOS_UINT32)mdrv_file_write(pDfr->pData, 1, pDfr->ulLen, pFile);
    if(ret != pDfr->ulLen)
    {
        diag_printf(" mdrv_file_write failed 2.\n");
    }

    DIAG_DebugFileTail(pFile, FilePath);

    (VOS_VOID)mdrv_file_close(pFile);

    return ;
}


DIAG_THRPUT_INFO_STRU g_astThroughput[EN_DIAG_THRPUT_MAX] = {{0,0,0,0,{{0,0},}}};

/*****************************************************************************
 Function Name   : diag_ThroughputIn
 Description     : 吞吐率记录

 History         :
    1.c00326366    2015-07-11 Draft Enact

*****************************************************************************/
VOS_VOID diag_ThroughputSave(DIAG_THRPUT_ID_ENUM enChn, VOS_UINT32 bytes)
{
    VOS_UINT32 slice = mdrv_timer_get_normal_timestamp();
    VOS_UINT32 ptr;

    g_astThroughput[enChn].ulBytes += bytes;

    if(slice >= g_astThroughput[enChn].ulSlice)
    {
        /* 每次统计吞吐率最少间隔5秒以上 */
        if((slice - g_astThroughput[enChn].ulSlice) > DIAG_THRPUT_DEBUG_LEN)
        {
            ptr = g_astThroughput[enChn].ulPtr;

            g_astThroughput[enChn].stNode[ptr].ulSlice = slice;
            g_astThroughput[enChn].stNode[ptr].ulThroughput = \
                g_astThroughput[enChn].ulBytes/((slice - g_astThroughput[enChn].ulSlice)/32768);

            g_astThroughput[enChn].ulSlice = slice;

            if(g_astThroughput[enChn].ulMax < g_astThroughput[enChn].stNode[ptr].ulThroughput)
            {
                g_astThroughput[enChn].ulMax = g_astThroughput[enChn].stNode[ptr].ulThroughput;
            }

            if((++g_astThroughput[enChn].ulPtr) >= DIAG_THRPUT_DEBUG_NUM)
            {
                g_astThroughput[enChn].ulPtr = 0;
            }

            g_astThroughput[enChn].ulBytes = 0;
        }
    }
    else    /* 如果反转则清零，重新统计 */
    {
        g_astThroughput[enChn].ulSlice = slice;
        g_astThroughput[enChn].ulBytes = 0;
    }
}

VOS_VOID DIAG_ShowThroughput(VOS_UINT32 ulIndex)
{
    VOS_UINT32 i;

    if(ulIndex >= EN_DIAG_THRPUT_MAX)
    {
        (VOS_VOID)vos_printf("ulIndex %d.\n", ulIndex);
        return ;
    }

    (VOS_VOID)vos_printf("max throughput 0x%x Bytes/s.\n", g_astThroughput[ulIndex].ulMax);

    for(i = 0; i < DIAG_THRPUT_DEBUG_NUM; i++)
    {
        (VOS_VOID)vos_printf("slice 0x%x, throughput 0x%x Bytes/s.\n",
            g_astThroughput[ulIndex].stNode[i].ulSlice,
            g_astThroughput[ulIndex].stNode[i].ulThroughput);
    }
}

/*****************************************************************************
 Function Name   : DIAG_ShowLogCfg
 Description     : 根据输入的任务PID查询log配置开关信息
*****************************************************************************/
VOS_VOID DIAG_ShowLogCfg(VOS_UINT32 ulModuleId)
{
    VOS_UINT32 level;

    /*检查DIAG是否初始化且HSO是否连接上*/
    if(!DIAG_IS_CONN_ON)
    {
        diag_printf("未连接工具软件!\n");
    }

    if(DIAG_CFG_MODULE_IS_INVALID((VOS_INT32)ulModuleId))
    {
        diag_printf("非法PID. PID范围(%d -- %d)!\n", VOS_PID_DOPRAEND, VOS_PID_BUTT);
        return;
    }

    diag_printf("打印总开关 0x%x, 全FF表示无效.\n", g_PrintTotalCfg);

    /* level中存储的值(0|ERROR|WARNING|NORMAL|INFO|0|0|0) bit 6-3 分别表示ERROR-INFO */
    level = g_PrintModuleCfg[ulModuleId - VOS_PID_DOPRAEND];
    if(level & 0x08)
    {
        diag_printf("PID %d 的打印级别为 info.\n", ulModuleId);
    }
    else if(level & 0x10)
    {
        diag_printf("PID %d 的打印级别为 normal.\n", ulModuleId);
    }
    else if(level & 0x20)
    {
        diag_printf("PID %d 的打印级别为 warning.\n", ulModuleId);
    }
    else if(level & 0x40)
    {
        diag_printf("PID %d 的打印级别为 error.\n", ulModuleId);
    }
    else
    {
        diag_printf("PID %d 的打印级别为 off.\n", ulModuleId);
    }

    diag_printf("打印失败总次数 %d.\n", g_astCBTInfoTbl[EN_DIAG_CBT_API_PRINTFV_ERR].ulCalledNum);
    diag_printf("打印成功总次数 %d.\n", g_astCBTInfoTbl[EN_DIAG_CBT_API_PRINTFV_OK].ulCalledNum);
}

/*****************************************************************************
 Function Name   : DIAG_ShowEventCfg
 Description     : 查询EVENT配置开关信息
*****************************************************************************/
VOS_VOID DIAG_ShowEventCfg(VOS_UINT32 ulpid)
{
    /*检查DIAG是否初始化且HSO是否连接上*/
    if(!DIAG_IS_CONN_ON)
    {
        diag_printf("未连接工具软件!\n");
    }
    else if(!DIAG_IS_EVENT_ON)
    {
        diag_printf("event总开关未打开!\n");
    }
    else
    {
        if(DIAG_CFG_MODULE_IS_INVALID(ulpid))
        {
            diag_printf("非法PID: A(%d -- %d), C(%d -- %d)!\n",
                VOS_PID_CPU_ID_1_DOPRAEND, VOS_CPU_ID_1_PID_BUTT,
                VOS_PID_CPU_ID_0_DOPRAEND, VOS_CPU_ID_0_PID_BUTT);
        }
        else
        {
            if(g_EventModuleCfg[ulpid - VOS_PID_DOPRAEND])
            {
                diag_printf("ulpid %d event开关已打开!\n", ulpid);
            }
            else
            {
                diag_printf("ulpid %d event开关已打开!\n", ulpid);
            }
        }
    }

    diag_printf("Event上报失败总次数 %d.\n", g_astCBTInfoTbl[EN_DIAG_CBT_API_EVENT_ERR].ulCalledNum);
    diag_printf("Event上报成功总次数 %d.\n", g_astCBTInfoTbl[EN_DIAG_CBT_API_EVENT_OK].ulCalledNum);
}

/*****************************************************************************
 Function Name   : DIAG_ShowAirCfg
 Description     : 查询空口配置开关信息
*****************************************************************************/
VOS_VOID DIAG_ShowAirCfg(VOS_VOID)
{
    /*检查DIAG是否初始化且HSO是否连接上*/
    if(!DIAG_IS_CONN_ON)
    {
        diag_printf("未连接工具软件!\n");
    }
    else if(!DIAG_IS_LT_AIR_ON)
    {
        diag_printf("空口开关未打开!\n");
    }
    else
    {
        diag_printf("空口开关已打开!\n");
    }
    diag_printf("空口消息上报失败总次数 %d.\n", g_astCBTInfoTbl[EN_DIAG_CBT_API_AIR_ERR].ulCalledNum);
    diag_printf("空口消息上报成功总次数 %d.\n", g_astCBTInfoTbl[EN_DIAG_CBT_API_AIR_OK].ulCalledNum);
}


/*****************************************************************************
 Function Name   : DIAG_ShowLayerCfg
 Description     : 根据输入的任务PID查询层间消息配置开关信息
*****************************************************************************/
VOS_VOID DIAG_ShowLayerCfg(VOS_UINT32 ulModuleId, VOS_UINT32 ulSrcDst)
{
    VOS_UINT32 ulOffset = 0;
    VOS_UINT32 ulState = 0;

    /*检查DIAG是否初始化且HSO是否连接上*/
    if(!DIAG_IS_CONN_ON)
    {
        diag_printf("未连接工具软件!\n");
    }

    /* 0表示源模块 */
    if(DIAG_CMD_LAYER_MOD_SRC == ulSrcDst)
    {
        if(DIAG_CFG_LAYER_MODULE_IS_ACORE(ulModuleId))
        {
            ulOffset = DIAG_CFG_LAYER_MODULE_ACORE_OFFSET(ulModuleId);

            if(g_ALayerSrcModuleCfg[ulOffset])
            {
                ulState = 1;
            }
        }
        else if(DIAG_CFG_LAYER_MODULE_IS_CCORE(ulModuleId))
        {
            ulOffset = DIAG_CFG_LAYER_MODULE_CCORE_OFFSET(ulModuleId);

            if(g_CLayerSrcModuleCfg[ulOffset])
            {
                ulState = 1;
            }
        }
        else
        {
            diag_printf("非法PID: A(%d -- %d), C(%d -- %d)!\n",
                VOS_PID_CPU_ID_1_DOPRAEND, VOS_CPU_ID_1_PID_BUTT,
                VOS_PID_CPU_ID_0_DOPRAEND, VOS_CPU_ID_0_PID_BUTT);

            return ;
        }

        diag_printf("源模块%d开关为 %s .\n", ulModuleId, ulState ? "打开状态":"关闭状态");
    }
    else
    {
        if(DIAG_CFG_LAYER_MODULE_IS_ACORE(ulModuleId))
        {
            ulOffset = DIAG_CFG_LAYER_MODULE_ACORE_OFFSET(ulModuleId);

            if(g_ALayerDstModuleCfg[ulOffset])
            {
                ulState = 1;
            }
        }
        else if(DIAG_CFG_LAYER_MODULE_IS_CCORE(ulModuleId))
        {
            ulOffset = DIAG_CFG_LAYER_MODULE_CCORE_OFFSET(ulModuleId);

            if(g_CLayerDstModuleCfg[ulOffset])
            {
                ulState = 1;
            }
        }
        else
        {
            diag_printf("非法PID: A(%d -- %d), C(%d -- %d)!\n",
                VOS_PID_CPU_ID_1_DOPRAEND, VOS_CPU_ID_1_PID_BUTT,
                VOS_PID_CPU_ID_0_DOPRAEND, VOS_CPU_ID_0_PID_BUTT);

            return ;
        }

        diag_printf("目的模块%d开关为 %s .\n", ulModuleId, ulState ? "打开状态":"关闭状态");
    }

    diag_printf("层间消息上报失败总次数 %d.\n", g_astCBTInfoTbl[EN_DIAG_CBT_API_TRACE_ERR].ulCalledNum);
    diag_printf("层间消息过滤次数 %d: srcid 0x%x, dstid 0x%x, msgid 0x%x.\n",
        g_astCBTInfoTbl[EN_DIAG_CBT_API_TRACE_FILTER].ulCalledNum,
        g_astCBTInfoTbl[EN_DIAG_CBT_API_TRACE_FILTER].ulRserved1,
        g_astCBTInfoTbl[EN_DIAG_CBT_API_TRACE_FILTER].ulRserved2,
        g_astCBTInfoTbl[EN_DIAG_CBT_API_TRACE_FILTER].ulRserved3);
    diag_printf("层间消息上报成功总次数 %d.\n", g_astCBTInfoTbl[EN_DIAG_CBT_API_TRACE_OK].ulCalledNum);
}

/*****************************************************************************
 Function Name   : DIAG_ShowUsrCfg
 Description     : 查询用户面配置开关信息
*****************************************************************************/
VOS_VOID DIAG_ShowUsrCfg(VOS_VOID)
{
    diag_printf("用户面消息上报失败总次数 %d.\n", g_astCBTInfoTbl[EN_DIAG_CBT_API_USER_ERR].ulCalledNum);
    diag_printf("用户面消息上报成功总次数 %d.\n", g_astCBTInfoTbl[EN_DIAG_CBT_API_USER_OK].ulCalledNum);
}

/*****************************************************************************
 Function Name   : DIAG_ShowTrans
 Description     : 查询最后n个透传上报相关信息
*****************************************************************************/
VOS_VOID DIAG_ShowTrans(VOS_UINT32 n)
{
    diag_printf("透传消息上报失败总次数 %d.\n", g_astCBTInfoTbl[EN_DIAG_CBT_API_TRANS_ERR].ulCalledNum);
    diag_printf("透传消息上报成功总次数 %d.\n", g_astCBTInfoTbl[EN_DIAG_CBT_API_TRANS_OK].ulCalledNum);

    diag_printf("最后 %d 个透传上报的信息如下:\n", n);

    DIAG_ShowLNR(EN_DIAG_LNR_TRANS_IND, n);

}

/*****************************************************************************
 Function Name   : DIAG_ShowTrans
 Description     : 查询最后n个透传上报相关信息
*****************************************************************************/
VOS_VOID DIAG_ShowPsTransCmd(VOS_UINT32 n)
{
    diag_printf("最后 %d 个透传上报的信息如下:\n", n);
    DIAG_ShowLNR(EN_DIAG_LNR_PS_TRANS, n);
}

/*****************************************************************************
 Function Name   : DIAG_ShowLost
 Description     : 查询上报失败丢包的信息
*****************************************************************************/
VOS_VOID DIAG_ShowLost(VOS_VOID)
{
    diag_printf("封包、调用socp接口上报，失败次数 %d.\n", g_astCBTInfoTbl[EN_DIAG_CBT_API_PACKET_ERR_REQ].ulCalledNum);
    diag_printf("最后一次的失败的错误码 %d, 行号 %d.\n",
        g_astCBTInfoTbl[EN_DIAG_CBT_API_PACKET_ERR_REQ].ulRserved1, g_astCBTInfoTbl[EN_DIAG_CBT_API_PACKET_ERR_REQ].ulRserved2);
}


VOS_UINT32 g_ulMntnSn = 0;
/*****************************************************************************
 Function Name   : diag_ReportMntn
 Description     : 通过控制通道定时上报可维可测信息
*****************************************************************************/
VOS_VOID diag_ReportMntn(VOS_VOID)
{
    VOS_UINT32          ulRet;
    VOS_UINT32          ulDataLen;
    VOS_UINT32          ulptr;
    VOS_ULONG           ulLockLevel;
    DIAG_DEBUG_MNTN_STRU stDiagInfo = {};
    SOCP_BUFFER_RW_STRU stSocpBuff  = {VOS_NULL};
    SOCP_BUFFER_RW_STRU stSocpBuf   = {VOS_NULL, VOS_NULL, 0, 0};
    SCM_CODER_SRC_MEMCPY_STRU stCpy;
    SCM_CODER_SRC_PACKET_HEADER_STRU* pstCoderSrc;

    /* HIDS未连接 */
    if(!DIAG_IS_CONN_ON)
    {
        return ;
    }

    (VOS_VOID)mdrv_timer_get_accuracy_timestamp((VOS_UINT32*)&(stDiagInfo.pstFrameInfo.stService.aucTimeStamp[4]),\
                                                (VOS_UINT32*)&(stDiagInfo.pstFrameInfo.stService.aucTimeStamp[0]));

    stDiagInfo.pstFrameInfo.stService.sid8b       = MSP_SID_DIAG_SERVICE;
    stDiagInfo.pstFrameInfo.stService.ssid4b      = DIAG_SSID_CPU;
    stDiagInfo.pstFrameInfo.stService.mdmid3b     = DIAG_MODEM_0;
    stDiagInfo.pstFrameInfo.stService.rsv1b       = 0;
    stDiagInfo.pstFrameInfo.stService.sessionid8b = MSP_SERVICE_SESSION_ID;

    stDiagInfo.pstFrameInfo.stService.ff1b         = 0;
    stDiagInfo.pstFrameInfo.stService.eof1b        = 0;
    stDiagInfo.pstFrameInfo.stService.index4b      = 0;

    stDiagInfo.pstFrameInfo.stService.mt2b         = DIAG_MT_IND;
    stDiagInfo.pstFrameInfo.stService.ulMsgTransId = g_ulTransId++;
    stDiagInfo.pstFrameInfo.stID.pri4b             = DIAG_MSG_TYPE_MSP;
    stDiagInfo.pstFrameInfo.stID.mode4b            = DIAG_MODE_COMM;
    stDiagInfo.pstFrameInfo.stID.sec5b             = DIAG_MSG_STAT;
    stDiagInfo.pstFrameInfo.stID.cmdid19b          = DIAG_DEBUG_MNTN_CMDID;
    stDiagInfo.pstFrameInfo.ulMsgLen               = sizeof(DIAG_DEBUG_MNTN_STRU);

    stDiagInfo.pstMntnInfo.ulModuleId       = DIAG_AGENT_PID;
    stDiagInfo.pstMntnInfo.ulNo             = g_ulMntnSn++;
    stDiagInfo.pstMntnInfo.ulTraceNum       = g_astCBTInfoTbl[EN_DIAG_CBT_API_TRACE_OK].ulCalledNum;
    stDiagInfo.pstMntnInfo.ulEventNum       = g_astCBTInfoTbl[EN_DIAG_CBT_API_EVENT_OK].ulCalledNum;
    stDiagInfo.pstMntnInfo.ulLogNum         = g_astCBTInfoTbl[EN_DIAG_CBT_API_PRINTFV_OK].ulCalledNum;
    stDiagInfo.pstMntnInfo.ulAirNum         = g_astCBTInfoTbl[EN_DIAG_CBT_API_AIR_OK].ulCalledNum;
    stDiagInfo.pstMntnInfo.ulTransNum       = g_astCBTInfoTbl[EN_DIAG_CBT_API_TRANS_OK].ulCalledNum;

    ulptr = g_astThroughput[EN_DIAG_THRPUT_DATA_CHN_ENC].ulPtr;
    ulptr = (0 == ulptr) ? (DIAG_THRPUT_DEBUG_NUM - 1) : (ulptr - 1);
    stDiagInfo.pstMntnInfo.ulThrputEnc      = g_astThroughput[EN_DIAG_THRPUT_DATA_CHN_ENC].stNode[ulptr].ulThroughput;

#if (VOS_OS_VER == VOS_LINUX)

    ulptr = g_astThroughput[EN_DIAG_THRPUT_DATA_CHN_PHY].ulPtr;
    ulptr = (0 == ulptr) ? (DIAG_THRPUT_DEBUG_NUM-1) : (ulptr - 1);
    stDiagInfo.pstMntnInfo.ulThrputPhy      = g_astThroughput[EN_DIAG_THRPUT_DATA_CHN_PHY].stNode[ulptr].ulThroughput;
    
    ulptr = g_astThroughput[EN_DIAG_THRPUT_DATA_CHN_CB].ulPtr;
    ulptr = (0 == ulptr) ? (DIAG_THRPUT_DEBUG_NUM-1) : (ulptr - 1);
    stDiagInfo.pstMntnInfo.ulThrputCb       = g_astThroughput[EN_DIAG_THRPUT_DATA_CHN_CB].stNode[ulptr].ulThroughput;

    stDiagInfo.pstMntnInfo.ulTotalSocpDstLen= SCM_GetDebugLogInfo()->ulCoderDstIndLen;
    stDiagInfo.pstMntnInfo.ulTotalUSBLen    = PPM_ComPpmGetDebugInfo()->stIndDebugInfo.ulUSBSendLen;
    stDiagInfo.pstMntnInfo.ulTotalUSBFreeLen= PPM_ComPpmGetSyncInfo()->ulLen;
    stDiagInfo.pstMntnInfo.ulTotalVCOMLen   = PPM_VComGetIndInfo()->ulVCOMSendLen;
    stDiagInfo.pstMntnInfo.ulTotalVCOMErrLen= PPM_VComGetIndInfo()->ulVCOMSendErrLen;
    stDiagInfo.pstMntnInfo.ulVCOMMaxTimeLen = PPM_VComGetIndInfo()->ulMaxTimeLen;
    
#if (FEATURE_HISOCKET == FEATURE_ON)
    stDiagInfo.pstMntnInfo.ulTotalSOCKETLen = PPM_SocketGetUdpInfo();
#endif

    (VOS_VOID)mdrv_socp_get_write_buff(SCM_CODER_SRC_LOM_IND, &stSocpBuff);
    stDiagInfo.pstMntnInfo.ulSrcChnSize     = stSocpBuff.u32Size + stSocpBuff.u32RbSize;

    (VOS_VOID)BSP_SOCP_GetReadBuff(SOCP_CODER_DST_OM_IND, &stSocpBuff);
    stDiagInfo.pstMntnInfo.ulDstChnSize     = stSocpBuff.u32Size + stSocpBuff.u32RbSize;
#else
    (VOS_VOID)mdrv_socp_get_write_buff(SCM_CODER_SRC_LOM_IND, &stSocpBuff);
    stDiagInfo.pstMntnInfo.ulSrcChnSize     = stSocpBuff.u32Size + stSocpBuff.u32RbSize;
#endif

    /*申请源buffer*/
    SCM_SPINLOCK_INTLOCK(ulLockLevel);

    ulDataLen = ALIGN_DDR_WITH_8BYTE(sizeof(stDiagInfo));

    ulRet = SCM_GetCoderChnSrcBuff(SCM_CODER_SRC_LOM_IND, ulDataLen, &pstCoderSrc, &stSocpBuf);

    if(ERR_MSP_SUCCESS != ulRet)
    {
        SCM_SPINUNLOCK_INTUNLOCK(ulLockLevel);
        return;
    }

    stCpy.pHeader   = pstCoderSrc;
    stCpy.pSrc      = &stDiagInfo;
    stCpy.uloffset  = SCM_HISI_HEADER_LENGTH;
    stCpy.ulLen     = ulDataLen;
    SCM_CoderSrcMemcpy(SCM_CODER_SRC_LOM_IND, &stCpy, &stSocpBuf);

    (VOS_VOID)SCM_SendCoderSrc(SCM_CODER_SRC_LOM_IND,(VOS_UINT8*)pstCoderSrc, ulDataLen);

    SCM_SPINUNLOCK_INTUNLOCK(ulLockLevel);

    return ;
}

DIAG_DEBUG_LOST_STRU g_stLostInfo = {};

/*****************************************************************************
 Function Name   : diag_ReportLost
 Description     : 通过控制通道上报丢包信息
*****************************************************************************/
VOS_VOID diag_ReportLost(DIAG_LOST_ID_ENUM enLostId)
{
    static VOS_UINT32   ulLastSlice = 0;
    VOS_UINT32          i;
    VOS_UINT32          ulCurSlice;
    VOS_UINT32          ulRet;
    VOS_UINT32          ulDataLen;
    VOS_ULONG           ulLockLevel;
    SOCP_BUFFER_RW_STRU stSocpBuff = {VOS_NULL};
    SOCP_BUFFER_RW_STRU stSocpBuf = {VOS_NULL, VOS_NULL, 0, 0};
    SCM_CODER_SRC_MEMCPY_STRU stCpy;
    SCM_CODER_SRC_PACKET_HEADER_STRU* pstCoderSrc;
    OM_CHANNLE_PORT_CFG_STRU stPortCfg;

    ulRet = NV_Read(en_NV_Item_Om_Port_Type, &stPortCfg, sizeof(OM_CHANNLE_PORT_CFG_STRU));

    /* 如果是连接HIDP则不上报 */
    if((VOS_OK == ulRet) && (CPM_OM_PORT_TYPE_VCOM == stPortCfg.enPortNum))
    {
        return ;
    }

    /* HIDS未连接 */
    if(!DIAG_IS_CONN_ON)
    {
        return ;
    }

    g_stLostInfo.pstLostInfo.ulLostTotalNum++;
    g_stLostInfo.pstLostInfo.aulCurFailNum[enLostId]++;

    /* 两条消息之间的间隔不小于5s */
    ulCurSlice = mdrv_timer_get_normal_timestamp();
    if((ulCurSlice - ulLastSlice) < DIAG_DEBUG_LOST_LEN)
    {
        return ;
    }

    ulLastSlice = ulCurSlice;

    (VOS_VOID)mdrv_timer_get_accuracy_timestamp((VOS_UINT32*)&(g_stLostInfo.pstFrameInfo.stService.aucTimeStamp[4]),\
                                                (VOS_UINT32*)&(g_stLostInfo.pstFrameInfo.stService.aucTimeStamp[0]));

    g_stLostInfo.pstFrameInfo.stService.sid8b       = MSP_SID_DIAG_SERVICE;
    g_stLostInfo.pstFrameInfo.stService.ssid4b      = DIAG_SSID_CPU;
    g_stLostInfo.pstFrameInfo.stService.mdmid3b     = DIAG_MODEM_0;
    g_stLostInfo.pstFrameInfo.stService.rsv1b       = 0;
    g_stLostInfo.pstFrameInfo.stService.sessionid8b = MSP_SERVICE_SESSION_ID;

    g_stLostInfo.pstFrameInfo.stService.ff1b         = 0;
    g_stLostInfo.pstFrameInfo.stService.eof1b        = 0;
    g_stLostInfo.pstFrameInfo.stService.index4b      = 0;

    g_stLostInfo.pstFrameInfo.stService.mt2b         = DIAG_MT_IND;
    g_stLostInfo.pstFrameInfo.stService.ulMsgTransId = g_ulTransId++;
    g_stLostInfo.pstFrameInfo.stID.pri4b             = DIAG_MSG_TYPE_MSP;
    g_stLostInfo.pstFrameInfo.stID.mode4b            = DIAG_MODE_COMM;
    g_stLostInfo.pstFrameInfo.stID.sec5b             = DIAG_MSG_STAT;
    g_stLostInfo.pstFrameInfo.stID.cmdid19b          = DIAG_DEBUG_LOST_CMDID;
    g_stLostInfo.pstFrameInfo.ulMsgLen               = sizeof(DIAG_DEBUG_MNTN_STRU);

    g_stLostInfo.pstLostInfo.ulModuleId              = DIAG_AGENT_PID;
    g_stLostInfo.pstLostInfo.ulNo++;

    (VOS_VOID)mdrv_socp_get_write_buff(SCM_CODER_SRC_LOM_IND, &stSocpBuff);
    g_stLostInfo.pstLostInfo.ulSrcChnSize     = stSocpBuff.u32Size + stSocpBuff.u32RbSize;

    (VOS_VOID)BSP_SOCP_GetReadBuff(SOCP_CODER_DST_OM_IND, &stSocpBuff);
    g_stLostInfo.pstLostInfo.ulDstChnSize     = stSocpBuff.u32Size + stSocpBuff.u32RbSize;
    
#if ((VOS_OS_VER == VOS_RTOSCK) || (VOS_OS_VER == VOS_VXWORKS))
    (VOS_VOID)mdrv_socp_get_write_buff(SOCP_CODER_SRC_LDSP1, &stSocpBuff);
    g_stLostInfo.pstLostInfo.ulDSPChnSize     = stSocpBuff.u32Size + stSocpBuff.u32RbSize;
#endif

    /*申请源buffer*/
    SCM_SPINLOCK_INTLOCK(ulLockLevel);

    ulDataLen = ALIGN_DDR_WITH_8BYTE(sizeof(g_stLostInfo));

    ulRet = SCM_GetCoderChnSrcBuff(SCM_CODER_SRC_LOM_CNF, ulDataLen, &pstCoderSrc, &stSocpBuf);

    if(ERR_MSP_SUCCESS != ulRet)
    {
        SCM_SPINUNLOCK_INTUNLOCK(ulLockLevel);
        return;
    }

    stCpy.pHeader   = pstCoderSrc;
    stCpy.pSrc      = &g_stLostInfo;
    stCpy.uloffset  = SCM_HISI_HEADER_LENGTH;
    stCpy.ulLen     = ulDataLen;
    SCM_CoderSrcMemcpy(SCM_CODER_SRC_LOM_CNF, &stCpy, &stSocpBuf);

    (VOS_VOID)SCM_SendCoderSrc(SCM_CODER_SRC_LOM_CNF,(VOS_UINT8*)pstCoderSrc, ulDataLen);

    for(i = 0; i < EN_DIAG_LOST_MAX; i++)
    {
        g_stLostInfo.pstLostInfo.aulCurFailNum[i] = 0;
    }

    SCM_SPINUNLOCK_INTUNLOCK(ulLockLevel);

    return ;
}


#if ((VOS_OS_VER == VOS_RTOSCK) || (VOS_OS_VER == VOS_VXWORKS))
/*****************************************************************************
 Function Name   : diag_DebugMsgProc
 Description     : 处理A核发过来的保存debug信息的请求

 History         :
    1.c00326366    2015-06-21 Draft Enact

*****************************************************************************/
VOS_UINT32 diag_DebugMsgProc(MsgBlock* pMsgBlock)
{
    DIAG_A_DEBUG_C_REQ_STRU *pstFlag;

    if(pMsgBlock->ulSenderPid != MSP_PID_DIAG_APP_AGENT)
    {
        return ERR_MSP_FAILURE;
    }

    pstFlag = (DIAG_A_DEBUG_C_REQ_STRU *)pMsgBlock;

    /* 保存码流 */
    if(pstFlag->ulFlag & DIAG_DEBUG_DFR_BIT)
    {
        DIAG_DebugDFR();
    }

    /* 保存不上报的可维可测信息 */
    if(pstFlag->ulFlag & DIAG_DEBUG_NIL_BIT)
    {
        DIAG_DebugNoIndLog();
    }

    return ERR_MSP_SUCCESS;
}
#endif

/* EVENT上报调测接口 */
VOS_VOID DIAG_DebugEventReport(VOS_UINT32 ulpid)
{
    DIAG_EVENT_IND_STRU stEvent = {0};
    VOS_UINT32 aulData[4] = {0x12345678, 0x34567890, 0xabcdef00, 0x12345678};

    stEvent.ulModule    = DIAG_GEN_MODULE(1, 2);
    stEvent.ulPid       = ulpid;
    stEvent.ulEventId   = 0x13579;
    stEvent.ulLength    = 16;
    stEvent.pData       = aulData;

    (VOS_VOID)DIAG_EventReport(&stEvent);
}


/* 层间消息上报调测接口 */
VOS_VOID DIAG_DebugLayerReport(VOS_VOID)
{
    DIAG_DATA_MSG_STRU *pDataMsg;
    VOS_UINT32 aulData[4] = {0x12345678, 0x34567890, 0xabcdef00, 0x12345678};

    (VOS_VOID)vos_printf("MSP_PID_DIAG_AGENT %d, MSP_PID_DIAG_APP_AGENT %d.\n", MSP_PID_DIAG_AGENT, MSP_PID_DIAG_APP_AGENT);

#if ((VOS_OS_VER == VOS_RTOSCK) || (VOS_OS_VER == VOS_VXWORKS))
    pDataMsg = (DIAG_DATA_MSG_STRU*)VOS_AllocMsg(MSP_PID_DIAG_AGENT, (sizeof(DIAG_DATA_MSG_STRU)+ 16 - VOS_MSG_HEAD_LENGTH));
#else
    pDataMsg = (DIAG_DATA_MSG_STRU*)VOS_AllocMsg(MSP_PID_DIAG_APP_AGENT, (sizeof(DIAG_DATA_MSG_STRU)+ 16 - VOS_MSG_HEAD_LENGTH));
#endif

    if (pDataMsg != NULL)
    {
#if ((VOS_OS_VER == VOS_RTOSCK) || (VOS_OS_VER == VOS_VXWORKS))
        pDataMsg->ulReceiverPid = MSP_PID_DIAG_APP_AGENT;
#else
        pDataMsg->ulReceiverPid = MSP_PID_DIAG_AGENT;
#endif

        pDataMsg->ulMsgId    = 0x2468;
        pDataMsg->ulLen      = 16;
        (VOS_VOID)VOS_MemCpy(pDataMsg->pContext,aulData,16);

        DIAG_TraceReport(pDataMsg);

#if ((VOS_OS_VER == VOS_RTOSCK) || (VOS_OS_VER == VOS_VXWORKS))
        (VOS_VOID)VOS_FreeMsg(MSP_PID_DIAG_AGENT, pDataMsg);
#else
        (VOS_VOID)VOS_FreeMsg(MSP_PID_DIAG_APP_AGENT, pDataMsg);
#endif
    }

}


/* log上报调测接口 */
VOS_VOID DIAG_DebugLogReport(VOS_UINT32 ulpid, VOS_UINT32 level)
{
    VOS_UINT32 ulMod = DIAG_GEN_LOG_MODULE(1, 2, level);
    (VOS_VOID)DIAG_LogReport(ulMod, ulpid, __FILE__, __LINE__, "DIAG TEST.\n");
}


/* 透传上报调测接口 */
VOS_VOID DIAG_DebugTransReport(VOS_UINT32 ulpid)
{
    DIAG_TRANS_IND_STRU std;
    VOS_UINT32 aulData[80] = {0x12345678, 0x34567890, 0xabcdef00, 0x12345678};

    std.ulModule    = DIAG_GEN_MODULE(1, 2);;
    std.ulPid       = ulpid;
    std.ulMsgId     = 0x9753;
    std.ulLength    = 80;
    std.pData       = aulData;

    (VOS_VOID)DIAG_TransReport(&std);
}


/* 层间开关调测接口 */
VOS_VOID DIAG_DebugLayerCfg(VOS_UINT32 ulModuleId, VOS_UINT8 ucFlag)
{
    VOS_UINT32 ulOffset = 0;

    /* 源模块 */
    if(DIAG_CFG_LAYER_MODULE_IS_ACORE(ulModuleId))
    {
        ulOffset = DIAG_CFG_LAYER_MODULE_ACORE_OFFSET(ulModuleId);

        g_ALayerSrcModuleCfg[ulOffset] = ucFlag;
    }
    else if(DIAG_CFG_LAYER_MODULE_IS_CCORE(ulModuleId))
    {
        ulOffset = DIAG_CFG_LAYER_MODULE_CCORE_OFFSET(ulModuleId);

        g_CLayerSrcModuleCfg[ulOffset] = ucFlag;
    }
    else
    {
        diag_printf("非法PID: A(%d -- %d), C(%d -- %d)!\n",
            VOS_PID_CPU_ID_1_DOPRAEND, VOS_CPU_ID_1_PID_BUTT,
            VOS_PID_CPU_ID_0_DOPRAEND, VOS_CPU_ID_0_PID_BUTT);

        return ;
    }

    /* 目的模块 */
    if(DIAG_CFG_LAYER_MODULE_IS_ACORE(ulModuleId))
    {
        ulOffset = DIAG_CFG_LAYER_MODULE_ACORE_OFFSET(ulModuleId);

        g_ALayerDstModuleCfg[ulOffset] = ucFlag;
    }
    else if(DIAG_CFG_LAYER_MODULE_IS_CCORE(ulModuleId))
    {
        ulOffset = DIAG_CFG_LAYER_MODULE_CCORE_OFFSET(ulModuleId);

        g_CLayerDstModuleCfg[ulOffset] = ucFlag;
    }
    else
    {
        diag_printf("非法PID: A(%d -- %d), C(%d -- %d)!\n",
            VOS_PID_CPU_ID_1_DOPRAEND, VOS_CPU_ID_1_PID_BUTT,
            VOS_PID_CPU_ID_0_DOPRAEND, VOS_CPU_ID_0_PID_BUTT);
    }

}


#ifdef __cplusplus
    #if __cplusplus
        }
    #endif
#endif

