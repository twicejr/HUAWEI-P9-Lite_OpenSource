


#ifdef __cplusplus
#if __cplusplus
extern "C" {
#endif
#endif


/*****************************************************************************
  1 Include HeadFile
*****************************************************************************/
#include  "mdrv.h"
#include  "msp_debug.h"
#include  "diag_common.h"
#if(VOS_OS_VER == VOS_LINUX)
#include  "omprivate.h"
#include  "OmCommonPpm.h"
#endif
#include  "diag_cfg.h"


/*lint --e{545}*/

/*****************************************************************************
  2 Declare the Global Variable
*****************************************************************************/

/*lint -save -e767 原因:Log打印*/
#define    THIS_FILE_ID        MSP_FILE_ID_MSP_DEBUG_C
/*lint -restore +e767*/

/*****************************************************************************
  3 Function
*****************************************************************************/

/*****************************************************************************
 Function Name   : PTR : Process Trace Record (流程跟踪记录)
 Description     : 跟踪整个处理流程
*****************************************************************************/
#if(VOS_OS_VER == VOS_LINUX)
DIAG_PTR_INFO_STRU g_stPtrInfo = {0};

/*****************************************************************************
 Function Name   : diag_PTR
 Description     : DIAG打点信息记录接口

 History         :
    1.c00326366    2015-06-21 Draft Enact

*****************************************************************************/
VOS_VOID diag_PTR(DIAG_PTR_ID_ENUM enType)
{
    g_stPtrInfo.stPtr[g_stPtrInfo.ulCur].enStep = enType;
    g_stPtrInfo.stPtr[g_stPtrInfo.ulCur].ulTime = VOS_GetSlice();
    g_stPtrInfo.ulCur = (g_stPtrInfo.ulCur + 1) % DIAG_PTR_NUMBER;
}


/*****************************************************************************
 Function Name   : DIAG_DebugPTR
 Description     : DIAG处理流程的打点信息

 History         :
    1.c00326366    2015-06-21 Draft Enact

*****************************************************************************/
VOS_VOID DIAG_DebugPTR(VOS_VOID)
{
    void *pFile;
    VOS_UINT32 ret;
    VOS_UINT32 ulValue;
    VOS_CHAR *DirPath = "/modem_log/DIAG";
    VOS_CHAR *FilePath = "/modem_log/DIAG/DIAG_PTR.bin";

    /* 如果DIAG目录不存在则先创建目录 */
    if (VOS_OK != mdrv_file_access(DirPath, 0))
    {
        if (VOS_OK != mdrv_file_mkdir(DirPath))
        {
            vos_printf(" mdrv_file_mkdir /modem_log/DIAG failed.\n");
            return ;
        }
    }

    pFile = mdrv_file_open(FilePath, "wb+");
    if(pFile == 0)
    {
        vos_printf(" mdrv_file_open failed.\n");

        return ;
    }

    ret = DIAG_DebugFileHeader(pFile);
    if(VOS_OK != ret)
    {
        vos_printf(" DIAG_DebugFileHeader failed .\n");
        mdrv_file_close(pFile);
        return ;
    }

    /* 打点信息长度 */
    ulValue = DIAG_DEBUG_SIZE_FLAG | sizeof(g_stPtrInfo);
    ret = mdrv_file_write(&ulValue, 1, sizeof(ulValue), pFile);
    if(ret != sizeof(ulValue))
    {
        vos_printf(" mdrv_file_write sizeof g_stPtrInfo failed.\n");
    }
    
    /* 再写入打点信息 */
    ret = mdrv_file_write(&g_stPtrInfo, 1, sizeof(g_stPtrInfo), pFile);
    if(ret != sizeof(g_stPtrInfo))
    {
        vos_printf(" mdrv_file_write g_stPtrInfo failed.\n");
    }

    DIAG_DebugFileTail(pFile, FilePath);

    mdrv_file_close(pFile);

    return ;
}


VOS_VOID DIAG_DebugShowPTR(VOS_UINT32 ulnum)
{
    VOS_UINT32 i, cur;
    VOS_UINT32 ulCurTime;
    DIAG_PTR_INFO_STRU *pPtrTmp;
    
    VOS_CHAR *cName[EN_DIAG_PTR_PPM_PORTSEND+1] = 
    {
        "begin",    "ppm_rcv",  "cpm_rcv",  "scm_soft", "scm_self", "scm_rcv",  "scm_rcv1", "scm_disp", 
        "mspsvic1", "mspsvic2", "diagsvc1", "diagsvc2", "diagmsg1", "diagmsg2", "msgmsp1",  "msptrans", 
        "msp_ps1",  "msp_ps2",  "connect",  "disconn",  "msg_rpt",  "svicpack", "snd_code", "scm_code", 
        "code_dst", "scm_send", "cpm_send", "ppm_send"
    };

    ulCurTime = VOS_GetSlice();

    vos_printf("current time %d ms.\n", (ulCurTime/33));

    for(i = 0; i < (EN_DIAG_PTR_PPM_PORTSEND+1); i++)
    {
        if(0 == (i % 8))
        {
            vos_printf("\n");
        }
        vos_printf("%02d %8s | ", i, cName[i]);
    }
    vos_printf("\n");

    pPtrTmp = (DIAG_PTR_INFO_STRU *)VOS_MemAlloc(MSP_PID_DIAG_APP_AGENT, DYNAMIC_MEM_PT, sizeof(g_stPtrInfo));
    if(VOS_NULL == pPtrTmp)
    {
        return;
    }

    VOS_MemCpy(pPtrTmp, &g_stPtrInfo, sizeof(g_stPtrInfo));

    cur = pPtrTmp->ulCur;

    for(i = 0; i < ulnum; i++)
    {
        if(0 != pPtrTmp->stPtr[cur].ulTime)
        {
            if(0 == (i % 20))
            {
                vos_printf("\n");
                VOS_TaskDelay(10);
            }
            
            vos_printf("%02d %08d ms | ", pPtrTmp->stPtr[cur].enStep, (pPtrTmp->stPtr[cur].ulTime/33));
        }
        
        cur = (cur + 1) % DIAG_PTR_NUMBER;
    }
    vos_printf("\n i = %d, over!\n", i);

    VOS_MemFree(MSP_PID_DIAG_APP_AGENT, pPtrTmp);
    
    return ;
}

extern OM_ACPU_DEBUG_INFO g_stAcpuDebugInfo;

extern OM_CHANNLE_PORT_CFG_STRU g_stPortCfg;

extern OM_VCOM_DEBUG_INFO g_stVComDebugInfo[3];

extern VOS_UINT32 g_ulDiagCfgInfo;

/*****************************************************************************
 Function Name   : DIAG_DebugCommon
 Description     : DIAG通用的可维可测信息

 History         :
    1.c00326366    2015-06-21 Draft Enact

*****************************************************************************/
VOS_VOID DIAG_DebugCommon(VOS_VOID)
{
    void *pFile;
    VOS_UINT32 ret;
    VOS_CHAR *DirPath = "/modem_log/DIAG";
    VOS_CHAR *FilePath = "/modem_log/DIAG/DIAG_DebugCommon.bin";
    VOS_UINT32 ulValue;
    VOS_UINT8 *pData;
    VOS_UINT32 ullen,offset;
    VOS_CHAR   aucInfo[DIAG_DEBUG_INFO_LEN];

    /* 前两个U32保存A/C核PID个数 */
    ullen =   sizeof(g_ulDiagCfgInfo)
            + sizeof(g_stPortCfg)
            + sizeof(VOS_UINT32) + sizeof(g_stAcpuDebugInfo)
            + sizeof(VOS_UINT32) + sizeof(g_stVComDebugInfo);

    pData = (VOS_UINT8 *)VOS_MemAlloc(DIAG_AGENT_PID, DYNAMIC_MEM_PT, ullen);
    if(VOS_NULL == pData)
    {
        return;
    }

    /* 如果DIAG目录不存在则先创建目录 */
    if (VOS_OK != mdrv_file_access(DirPath, 0))
    {
        if (VOS_OK != mdrv_file_mkdir(DirPath))
        {
            vos_printf(" mdrv_file_mkdir /modem_log/DIAG failed.\n");
            return ;
        }
    }

    pFile = mdrv_file_open(FilePath, "wb+");
    if(pFile == 0)
    {
        vos_printf(" mdrv_file_open failed.\n");

        return ;
    }

    ret = DIAG_DebugFileHeader(pFile);
    if(VOS_OK != ret)
    {
        vos_printf(" DIAG_DebugFileHeader failed .\n");
        mdrv_file_close(pFile);
        return ;
    }

    VOS_MemSet(aucInfo, 0, DIAG_DEBUG_INFO_LEN);
    VOS_StrCpy(aucInfo, "DIAG common info");

    /* 通用信息 */
    ret = mdrv_file_write(aucInfo, 1, DIAG_DEBUG_INFO_LEN, pFile);
    if(ret != DIAG_DEBUG_INFO_LEN)
    {
        vos_printf(" mdrv_file_write DIAG number info failed.\n");
    }

    offset  = 0;
    
    /* 当前DIAG的连接状态 */
    VOS_MemCpy((pData + offset), &g_ulDiagCfgInfo, sizeof(g_ulDiagCfgInfo));
    offset += sizeof(g_ulDiagCfgInfo);
    
    /* CPM记录的当前连接的通道 */
    VOS_MemCpy((pData + offset), &g_stPortCfg, sizeof(g_stPortCfg));
    offset += sizeof(g_stPortCfg);
    
    /* USB端口的相关可维可测信息 */
    ulValue = DIAG_DEBUG_SIZE_FLAG | sizeof(g_stAcpuDebugInfo);
    VOS_MemCpy((pData + offset), &ulValue, sizeof(ulValue));
    offset += sizeof(ulValue);
    
    VOS_MemCpy((pData + offset), &g_stAcpuDebugInfo, sizeof(g_stAcpuDebugInfo));
    offset += sizeof(g_stAcpuDebugInfo);
    
    /* netlink端口的相关可维可测信息 */
    ulValue = DIAG_DEBUG_SIZE_FLAG | sizeof(g_stVComDebugInfo);
    VOS_MemCpy((pData + offset), &ulValue, sizeof(ulValue));
    offset += sizeof(ulValue);
    
    VOS_MemCpy((pData + offset), &g_stVComDebugInfo, sizeof(g_stVComDebugInfo));
    offset += sizeof(g_stVComDebugInfo);

    ret = mdrv_file_write(pData, 1, offset, pFile);
    if(ret != offset)
    {
        vos_printf(" mdrv_file_write pData failed.\n");
    }

    DIAG_DebugFileTail(pFile, FilePath);

    mdrv_file_close(pFile);

    return ;
}

#endif


/*****************************************************************************
 Function Name   : DIAG_DebugFileHeader
 Description     : 给debug文件写上文件头

 History         :
    1.c00326366    2015-06-21 Draft Enact

*****************************************************************************/
VOS_UINT32 DIAG_DebugFileHeader(void *pFile)
{
    VOS_UINT32 ret;
    VOS_UINT32 ulValue;
    
    ret = (VOS_UINT32)mdrv_file_seek(pFile, 0, DRV_SEEK_SET);
    if(VOS_OK != ret)
    {
        vos_printf(" mdrv_file_seek failed .\n");
        return ERR_MSP_FAILURE;
    }

    ulValue = DIAG_DEBUG_START;

    /* file start flag */
    ret = (VOS_UINT32)mdrv_file_write(&ulValue, 1, sizeof(ulValue), pFile);
    if(ret != sizeof(ulValue))
    {
        vos_printf(" mdrv_file_write start flag failed.\n");
        return ERR_MSP_FAILURE;
    }

    ulValue = DIAG_DEBUG_VERSION;

    /* debug version */
    ret = (VOS_UINT32)mdrv_file_write(&ulValue, 1, sizeof(ulValue), pFile);
    if(ret != sizeof(ulValue))
    {
        vos_printf(" mdrv_file_write debug version failed.\n");
        return ERR_MSP_FAILURE;
    }

    ulValue = 0;

    /* file size */
    ret = (VOS_UINT32)mdrv_file_write(&ulValue, 1, sizeof(ulValue), pFile);
    if(ret != sizeof(ulValue))
    {
        vos_printf(" mdrv_file_write file size failed.\n");
        return ERR_MSP_FAILURE;
    }

    ulValue = VOS_GetSlice();

    /* 当前的slice */
    ret = (VOS_UINT32)mdrv_file_write(&ulValue, 1, sizeof(ulValue), pFile);
    if(ret != sizeof(ulValue))
    {
        vos_printf(" mdrv_file_write ulTime failed.\n");
        return ERR_MSP_FAILURE;
    }
    
    return ERR_MSP_SUCCESS;
}


/*****************************************************************************
 Function Name   : DIAG_DebugFileTail
 Description     : 给debug文件写上文件尾

 History         :
    1.c00326366    2015-06-21 Draft Enact

*****************************************************************************/
VOS_VOID DIAG_DebugFileTail(void *pFile, VOS_CHAR *FilePath)
{
    VOS_UINT32 ret;
    VOS_UINT32 ulValue;

    /* file end flag */
    ulValue = DIAG_DEBUG_END;
    ret = (VOS_UINT32)mdrv_file_write(&ulValue, 1, sizeof(ulValue), pFile);
    if(ret != sizeof(ulValue))
    {
        vos_printf(" mdrv_file_write start flag failed.\n");
    }
    
}


extern VOS_UINT8 g_EventModuleCfg[DIAG_CFG_PID_NUM];

extern DIAG_CBT_INFO_TBL_STRU g_astCBTInfoTbl[EN_DIAG_DEBUG_INFO_MAX];


/*****************************************************************************
 Function Name   : diag_numberinfo
 Description     : 保存DIAG统计次数信息

 History         :
    1.c00326366    2015-06-21 Draft Enact

*****************************************************************************/
VOS_VOID diag_numberinfo(void *pFile)
{
    VOS_UINT32 ret;
    VOS_UINT32 ulValue;
    VOS_CHAR   aucInfo[DIAG_DEBUG_INFO_LEN];

    VOS_MemSet(aucInfo, 0, DIAG_DEBUG_INFO_LEN);
    VOS_StrCpy(aucInfo, "DIAG number info");

    /* 上报次数信息 */
    ret = (VOS_UINT32)mdrv_file_write(aucInfo, 1, DIAG_DEBUG_INFO_LEN, pFile);
    if(ret != DIAG_DEBUG_INFO_LEN)
    {
        vos_printf(" mdrv_file_write DIAG number info failed.\n");
    }

    /* 当前的slice */
    ulValue = VOS_GetSlice();
    ret = (VOS_UINT32)mdrv_file_write(&ulValue, 1, sizeof(ulValue), pFile);
    if(ret != sizeof(ulValue))
    {
        vos_printf(" mdrv_file_write ulTime failed.\n");
    }
    
    /* 变量的size */
    ulValue = DIAG_DEBUG_SIZE_FLAG | sizeof(g_astCBTInfoTbl);
    ret = (VOS_UINT32)mdrv_file_write(&ulValue, 1, sizeof(ulValue), pFile);
    if(ret != sizeof(ulValue))
    {
        vos_printf(" mdrv_file_write ulTime failed.\n");
    }
    
    /* 各上报次数统计量 */
    ret = (VOS_UINT32)mdrv_file_write(&g_astCBTInfoTbl, 1, sizeof(g_astCBTInfoTbl), pFile);
    if(ret != sizeof(g_astCBTInfoTbl))
    {
        vos_printf(" mdrv_file_write g_astCBTInfoTbl failed.\n");
    }
}

/*****************************************************************************
 Function Name   : DIAG_DebugNoIndLog
 Description     : LOG不上报的可维可测信息

 History         :
    1.c00326366    2015-06-21 Draft Enact

*****************************************************************************/
VOS_VOID DIAG_DebugNoIndLog(VOS_VOID)
{
    void *pFile;
    VOS_UINT32 ret;
    VOS_CHAR *DirPath = "/modem_log/DIAG";
#if(VOS_OS_VER == VOS_LINUX)
    VOS_CHAR *FilePath = "/modem_log/DIAG/DIAG_AcoreNoIndLog.bin";
#else
    VOS_CHAR *FilePath = "/modem_log/DIAG/DIAG_CcoreNoIndLog.bin";
#endif
    VOS_UINT32 ulValue;
    VOS_CHAR   aucInfo[DIAG_DEBUG_INFO_LEN];
    VOS_UINT8 *pData;
    VOS_UINT32 ullen,offset;

    /* 前两个U32保存A/C核PID个数 */
    ullen = (2 * sizeof(VOS_UINT32))
            + sizeof(VOS_UINT32) + sizeof(g_ALayerSrcModuleCfg)
            + sizeof(VOS_UINT32) + sizeof(g_CLayerSrcModuleCfg)
            + sizeof(VOS_UINT32) + sizeof(g_ALayerDstModuleCfg)
            + sizeof(VOS_UINT32) + sizeof(g_CLayerDstModuleCfg)
            + sizeof(VOS_UINT32) + sizeof(g_stMsgCfg)
            + sizeof(VOS_UINT32) + sizeof(g_EventModuleCfg)
            + sizeof(VOS_UINT32) + sizeof(g_PrintTotalCfg)
            + sizeof(VOS_UINT32) + sizeof(g_PrintModuleCfg);

    pData = VOS_MemAlloc(DIAG_AGENT_PID, DYNAMIC_MEM_PT, ullen);
    if(VOS_NULL == pData)
    {
        return;
    }

    /* 如果DIAG目录不存在则先创建目录 */
    if (VOS_OK != mdrv_file_access(DirPath, 0))
    {
        if (VOS_OK != mdrv_file_mkdir(DirPath))
        {
            vos_printf(" mdrv_file_mkdir /modem_log/DIAG failed.\n");
            return ;
        }
    }

    pFile = mdrv_file_open(FilePath, "wb+");
    if(pFile == 0)
    {
        vos_printf(" mdrv_file_open failed.\n");

        return ;
    }

    ret = DIAG_DebugFileHeader(pFile);
    if(VOS_OK != ret)
    {
        vos_printf(" DIAG_DebugFileHeader failed .\n");
        mdrv_file_close(pFile);
        return ;
    }

    VOS_MemSet(aucInfo, 0, DIAG_DEBUG_INFO_LEN);
    VOS_StrCpy(aucInfo, "DIAG config info");

    /* 配置开关信息 */
    ret = (VOS_UINT32)mdrv_file_write(aucInfo, 1, DIAG_DEBUG_INFO_LEN, pFile);
    if(ret != DIAG_DEBUG_INFO_LEN)
    {
        vos_printf(" mdrv_file_write DIAG config info failed.\n");
    }

    offset  = 0;

    /* A核PID个数 */
    ulValue = VOS_CPU_ID_1_PID_BUTT - VOS_PID_CPU_ID_1_DOPRAEND;
    VOS_MemCpy((pData + offset), &ulValue, sizeof(ulValue));
    offset += sizeof(ulValue);
    
    /* C核PID个数 */
    ulValue = VOS_CPU_ID_0_PID_BUTT - VOS_PID_CPU_ID_0_DOPRAEND;
    VOS_MemCpy((pData + offset), &ulValue, sizeof(ulValue));
    offset += sizeof(ulValue);
    
    ulValue = DIAG_DEBUG_SIZE_FLAG | sizeof(g_ALayerSrcModuleCfg);
    VOS_MemCpy((pData + offset), &ulValue, sizeof(ulValue));
    offset += sizeof(ulValue);
    
    VOS_MemCpy((pData + offset), &g_ALayerSrcModuleCfg, sizeof(g_ALayerSrcModuleCfg));
    offset += sizeof(g_ALayerSrcModuleCfg);
    
    ulValue = DIAG_DEBUG_SIZE_FLAG | sizeof(g_CLayerSrcModuleCfg);
    VOS_MemCpy((pData + offset), &ulValue, sizeof(ulValue));
    offset += sizeof(ulValue);
    
    VOS_MemCpy((pData + offset), &g_CLayerSrcModuleCfg, sizeof(g_CLayerSrcModuleCfg));
    offset += sizeof(g_CLayerSrcModuleCfg);
    
    ulValue = DIAG_DEBUG_SIZE_FLAG | sizeof(g_ALayerDstModuleCfg);
    VOS_MemCpy((pData + offset), &ulValue, sizeof(ulValue));
    offset += sizeof(ulValue);
    
    VOS_MemCpy((pData + offset), &g_ALayerDstModuleCfg, sizeof(g_ALayerDstModuleCfg));
    offset += sizeof(g_ALayerDstModuleCfg);
    
    ulValue = DIAG_DEBUG_SIZE_FLAG | sizeof(g_CLayerDstModuleCfg);
    VOS_MemCpy((pData + offset), &ulValue, sizeof(ulValue));
    offset += sizeof(ulValue);
    
    VOS_MemCpy((pData + offset), &g_CLayerDstModuleCfg, sizeof(g_CLayerDstModuleCfg));
    offset += sizeof(g_CLayerDstModuleCfg);
    
    ulValue = DIAG_DEBUG_SIZE_FLAG | sizeof(g_stMsgCfg);
    VOS_MemCpy((pData + offset), &ulValue, sizeof(ulValue));
    offset += sizeof(ulValue);
    
    VOS_MemCpy((pData + offset), &g_stMsgCfg, sizeof(g_stMsgCfg));
    offset += sizeof(g_stMsgCfg);
    
    ulValue = DIAG_DEBUG_SIZE_FLAG | sizeof(g_EventModuleCfg);
    VOS_MemCpy((pData + offset), &ulValue, sizeof(ulValue));
    offset += sizeof(ulValue);
    
    VOS_MemCpy((pData + offset), &g_EventModuleCfg, sizeof(g_EventModuleCfg));
    offset += sizeof(g_EventModuleCfg);
    
    ulValue = DIAG_DEBUG_SIZE_FLAG | sizeof(g_PrintTotalCfg);
    VOS_MemCpy((pData + offset), &ulValue, sizeof(ulValue));
    offset += sizeof(ulValue);
    
    VOS_MemCpy((pData + offset), &g_PrintTotalCfg, sizeof(g_PrintTotalCfg));
    offset += sizeof(g_PrintTotalCfg);
    
    ulValue = DIAG_DEBUG_SIZE_FLAG | sizeof(g_PrintModuleCfg);
    VOS_MemCpy((pData + offset), &ulValue, sizeof(ulValue));
    offset += sizeof(ulValue);
    
    VOS_MemCpy((pData + offset), &g_PrintModuleCfg, sizeof(g_PrintModuleCfg));
    offset += sizeof(g_PrintModuleCfg);
    
    ret = (VOS_UINT32)mdrv_file_write(pData, 1, offset, pFile);
    if(ret != offset)
    {
        vos_printf(" mdrv_file_write pData failed.\n");
    }

    diag_numberinfo(pFile);

    /* 延迟5秒后再统计一次 */
    VOS_TaskDelay(5000);

    diag_numberinfo(pFile);

    DIAG_DebugFileTail(pFile, FilePath);

    mdrv_file_close(pFile);

    return ;
}


#ifdef __cplusplus
    #if __cplusplus
        }
    #endif
#endif

