



#ifdef __cplusplus
#if __cplusplus
extern "C" {
#endif /* __cpluscplus */
#endif /* __cpluscplus */

#include <mdrv.h>
#include "diag_msgbsp.h"
#include "diag_debug.h"
#include "msp_diag_comm.h"
#if (VOS_OS_VER == VOS_LINUX)
#include "diag_fs_proc.h"
#include "TafNvInterface.h"
#endif

#define    THIS_FILE_ID        MSP_FILE_ID_DIAG_MSGBSP_C


DIAG_BSP_PROC_FUN_STRU g_DiagBspFunc[] = {
    {diag_BspAxiMonDataConfig       ,DIAG_CMD_AXI_DATA_CONFIG   ,0},
    {diag_BspAxiMonConfig           ,DIAG_CMD_AXI_MON_CONFIG    ,0},
    {diag_BspAxiMonTerminate        ,DIAG_CMD_AXI_MON_TERMINATE ,0},
    {diag_BspAxiMonRegConfig        ,DIAG_CMD_AXI_REG_CONFIG    ,0},
    {diag_BspAxiMonDataCtrl         ,DIAG_CMD_AXI_DATA_CTRL     ,0},
    {diag_BspUtraceStart            ,DIAG_CMD_UTRACE_START      ,0},
    {diag_BspUtraceStop             ,DIAG_CMD_UTRACE_TERMINATE  ,0},
    {diag_BspLogProcEntry           ,DIAG_CMD_BSP_LOG_SET       ,0},
    {diag_BspSysviewProc            ,DIAG_CMD_BSP_SYSVIEW_SWT   ,0},
    {diag_BspSysviewProc            ,DIAG_CMD_BSP_CPU_SWT       ,0},
    #if (VOS_OS_VER == VOS_LINUX)
    {diag_FsQueryProc               ,DIAG_CMD_FS_QUERY_DIR      ,0},
    {diag_FsScanProc                ,DIAG_CMD_FS_SCAN_DIR       ,0},
    {diag_FsMkdirProc               ,DIAG_CMD_FS_MAKE_DIR       ,0},
    {diag_FsOpenProc                ,DIAG_CMD_FS_OPEN           ,0},
    {diag_FsImportProc              ,DIAG_CMD_FS_IMPORT         ,0},
    {diag_FsExportProc              ,DIAG_CMD_FS_EXPORT         ,0},
    {diag_FsDeleteProc              ,DIAG_CMD_FS_DELETE         ,0},
    {diag_FsSpaceProc               ,DIAG_CMD_FS_SPACE          ,0},
    {diag_NvRdProc                  ,DIAG_CMD_NV_RD             ,0},
    {diag_GetNvListProc             ,DIAG_CMD_GET_NV_LIST       ,0},
    {diag_NvWrProc                  ,DIAG_CMD_NV_WR             ,0},
    #endif
    {diag_NvAuthProc                ,DIAG_CMD_NV_AUTH           ,0},
};

#if (VOS_OS_VER == VOS_RTOSCK) || (VOS_OS_VER == VOS_VXWORKS)

extern VOS_UINT32 MMA_VerifyOperatorLockPwd(VOS_UINT8 *pucPwd);
#endif

#if (VOS_OS_VER == VOS_LINUX)

static VOS_UINT32 g_ulPrivilegeLevel = DIAG_LEVEL_NORMAL;

VOS_UINT32 g_aulNvAuthIdList[] =
{
    en_NV_Item_IMEI,
    en_NV_Item_USB_Enum_Status,
    en_NV_Item_CustomizeSimLockPlmnInfo,
    en_NV_Item_CardlockStatus,
    en_NV_Item_CustomizeSimLockMaxTimes,
    en_NV_Item_CustomizeService,
    en_NV_Item_PRODUCT_ID,
    en_NV_Item_PREVENT_TEST_IMSI_REG,
    en_NV_Item_AT_SHELL_OPEN_FLAG,
};

/*****************************************************************************
 Function Name   : NvRdProc
 Description     : 该函数用于处理从NvProcEntry传进来的读NV命令
 Input           : pstReq 待处理数据
 Output          : None
 Return          : VOS_UINT32

 History         :
    1.y00228784      2012-11-22  Draft Enact
    2.c64416         2014-11-18  适配新的诊断架构
    2.c00326366      2015-06-10  新增多条NV的读取处理

*****************************************************************************/
VOS_UINT32 diag_NvRdProc(VOS_UINT8* pstReq)
{
    VOS_UINT32 ret = ERR_MSP_SUCCESS;
    DIAG_CMD_NV_QRY_REQ_STRU* pstNVQryReq = NULL;
    DIAG_CMD_NV_QRY_CNF_STRU* pstNVQryCnf = NULL;
    VOS_UINT32 ulNVLen = 0, i = 0;
    VOS_UINT32 ulTotalSize = 0, ulOffset = 0;
    VOS_UINT8 *pData;
    MSP_DIAG_CNF_INFO_STRU stDiagInfo = {0};
    DIAG_FRAME_INFO_STRU *pstDiagHead = NULL;

    pstDiagHead = (DIAG_FRAME_INFO_STRU*)(pstReq);

    stDiagInfo.ulMsgType = DIAG_MSG_TYPE_BSP;

    pstNVQryReq = (DIAG_CMD_NV_QRY_REQ_STRU*)(pstDiagHead->aucData + sizeof(MSP_DIAG_DATA_REQ_STRU));

    for(i = 0; i < pstNVQryReq->ulCount; i++)
    {
        /*根据请求ID获取NV项长度*/
        ret = NV_GetLength(pstNVQryReq->ulNVId[i], &ulNVLen);
        if(ERR_MSP_SUCCESS != ret)
        {
            diag_printf("[%s]:ulNVId=0x%x,ulNVLen=%d!\n",__FUNCTION__, pstNVQryReq->ulNVId[i], ulNVLen);
            return ERR_MSP_FAILURE;
        }

        ulTotalSize += ulNVLen + sizeof(VOS_UINT32) + sizeof(VOS_UINT32); /* NV内容的长度加上(NVID和len各占用四字节) */
    }

    /* DIAG_CMD_NV_QRY_CNF_STRU的实际长度 */
    ulTotalSize += (sizeof(DIAG_CMD_NV_QRY_CNF_STRU) - sizeof(VOS_UINT32) - sizeof(VOS_UINT32));

    pstNVQryCnf = VOS_MemAlloc(MSP_PID_DIAG_APP_AGENT, DYNAMIC_MEM_PT, ulTotalSize );

    if(NULL  == pstNVQryCnf)
    {
        diag_printf("[%s]:malloc error!\n",__FUNCTION__);
        return ERR_MSP_MALLOC_FAILUE;
    }

    pstNVQryCnf->ulModemid = pstNVQryReq->ulModemid;
    pstNVQryCnf->ulCount   = pstNVQryReq->ulCount;

    pData = (VOS_UINT8*)(&pstNVQryCnf->ulNVId);
    ulOffset = 0;

    for(i = 0; i < pstNVQryReq->ulCount; i++)
    {
        /*根据请求ID获取NV项长度*/
        ret = NV_GetLength(pstNVQryReq->ulNVId[i], &ulNVLen);
        if(ERR_MSP_SUCCESS != ret)
        {
            diag_printf("[%s]:ulNVId=0x%x,ulNVLen=%d!\n",__FUNCTION__, pstNVQryReq->ulNVId[i], ulNVLen);
            goto DIAG_ERROR;
        }

        *(VOS_UINT32*)(pData + ulOffset) = pstNVQryReq->ulNVId[i]; /* [false alarm]:屏蔽Fortify */
        ulOffset += sizeof(VOS_UINT32);

        *(VOS_UINT32*)(pData + ulOffset) = ulNVLen; /* [false alarm]:屏蔽Fortify */
        ulOffset += sizeof(VOS_UINT32);

        ret = NV_ReadEx(pstNVQryReq->ulModemid, pstNVQryReq->ulNVId[i], (pData + ulOffset), ulNVLen);
        if(ret != ERR_MSP_SUCCESS)
        {
            diag_printf("[%s]:NV READ ERR 0x%x,ulNVId=0x%x\n",__FUNCTION__, ret, pstNVQryReq->ulNVId[i]);
            goto DIAG_ERROR;
        }

        ulOffset += ulNVLen;
    }

    DIAG_MSG_COMMON_PROC(stDiagInfo, (*pstNVQryCnf), pstDiagHead);

    pstNVQryCnf->ulRc    = ret;

    ret = DIAG_MsgReport(&stDiagInfo, pstNVQryCnf, ulTotalSize);

    VOS_MemFree(MSP_PID_DIAG_APP_AGENT, pstNVQryCnf);

    return ret;

DIAG_ERROR:
    DIAG_MSG_COMMON_PROC(stDiagInfo, (*pstNVQryCnf), pstDiagHead);

    pstNVQryCnf->ulRc    = ERR_MSP_FAILURE;
    pstNVQryCnf->ulCount = 0;

    ret = DIAG_MsgReport(&stDiagInfo, pstNVQryCnf, sizeof(DIAG_CMD_NV_QRY_CNF_STRU));

    VOS_MemFree(MSP_PID_DIAG_APP_AGENT, pstNVQryCnf);

    return ret;
}


/*****************************************************************************
 Function Name   : diag_GetNvListProc
 Description     : HIMS获取NV list命令的处理接口
 Input           : pstReq 待处理数据
 Output          : None
 Return          : VOS_UINT32

 History         :
    1.c00326366      2012-11-22  Draft Enact

*****************************************************************************/
VOS_UINT32 diag_GetNvListProc(VOS_UINT8* pstReq)
{
    VOS_UINT32 ret, ulNvNum, ulTotalLen;
    DIAG_CMD_NV_LIST_CNF_STRU* pstNVCnf = NULL;
    DIAG_CMD_NV_LIST_CNF_STRU stNVCnf = {0};
    MSP_DIAG_CNF_INFO_STRU stDiagInfo = {0};
    DIAG_FRAME_INFO_STRU *pstDiagHead;

    pstDiagHead = (DIAG_FRAME_INFO_STRU*)(pstReq);

    stDiagInfo.ulMsgType = DIAG_MSG_TYPE_BSP;

    ulNvNum = NV_GetNVIdListNum();
    if (0 == ulNvNum)
    {
        diag_printf("[%s]: ulNvNum=%d!\n",__FUNCTION__, ulNvNum);
        goto DIAG_ERROR;
    }

    /*APP_HEAD + Result + NV nums + NV ID/LEN lists*/
    ulTotalLen = sizeof(DIAG_CMD_NV_LIST_CNF_STRU) + (ulNvNum*sizeof(NV_LIST_INFO_STRU));

    pstNVCnf = (DIAG_CMD_NV_LIST_CNF_STRU*)VOS_MemAlloc(MSP_PID_DIAG_APP_AGENT, DYNAMIC_MEM_PT, ulTotalLen);

    if (VOS_NULL_PTR == pstNVCnf)
    {
        diag_printf("[%s]:malloc error!\n",__FUNCTION__);
        goto DIAG_ERROR;
    }

    /*获取每个NV项的ID和长度*/
    ret = NV_GetNVIdList(pstNVCnf->astNvList);
    if (NV_OK != ret)
    {
        VOS_MemFree(MSP_PID_DIAG_APP_AGENT, pstNVCnf);
        goto DIAG_ERROR;
    }

    DIAG_MSG_COMMON_PROC(stDiagInfo, (*pstNVCnf), pstDiagHead);

    pstNVCnf->ulCount    = ulNvNum;
    pstNVCnf->ulRc       = ERR_MSP_SUCCESS;

    ret = DIAG_MsgReport(&stDiagInfo, pstNVCnf, ulTotalLen);

    VOS_MemFree(MSP_PID_DIAG_APP_AGENT, pstNVCnf);

    return ret;

DIAG_ERROR:

    DIAG_MSG_COMMON_PROC(stDiagInfo, stNVCnf, pstDiagHead);

    stNVCnf.ulCount      = 0;
    stNVCnf.ulRc         = ERR_MSP_FAILURE;

    ret = DIAG_MsgReport(&stDiagInfo, &stNVCnf, sizeof(stNVCnf));

    return ret;
}

/*****************************************************************************
 Function Name   : diag_NvAuthProc
 Description     : 初始化鉴权全局变量
 Input           : None
 Output          : None
 Return          : VOS_VOID

 History         :
    1.c00326366      2012-11-22  Draft Enact

*****************************************************************************/
VOS_VOID diag_InitAuthVariable(VOS_VOID)
{
    IMEI_STRU stIMEI;
    VOS_UINT8 aucDefaultIMEI[] = {0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0};

    /*假如IMEI为默认值，则不需要鉴权*/
    if (NV_OK == NV_Read(en_NV_Item_IMEI, (VOS_VOID*)&stIMEI, sizeof(stIMEI)))
    {
        if (0 == VOS_MemCmp((VOS_CHAR*)aucDefaultIMEI, &stIMEI, sizeof(stIMEI)))
        {
            g_ulPrivilegeLevel = DIAG_LEVEL_ADVANCED;
        }
    }

    return;
}

/*****************************************************************************
 Function Name   : diag_NvAuthProc
 Description     : 判断此NV项是否可以进行修改
 Input           : ulNvId
 Output          : None
 Return          : VOS_UINT32

 History         :
    1.c00326366      2012-11-22  Draft Enact

*****************************************************************************/
VOS_UINT32 diag_IsAuthNv(VOS_UINT32 ulNvId)
{
    VOS_UINT32 i;

    for (i = 0; i < (sizeof(g_aulNvAuthIdList)/sizeof(VOS_UINT32)); i++)
    {
        if (ulNvId == g_aulNvAuthIdList[i])
        {
            if (DIAG_LEVEL_ADVANCED == g_ulPrivilegeLevel)
            {
                return VOS_YES;
            }
            return VOS_NO;
        }
    }

    return VOS_YES;
}


VOS_VOID diag_AuthNvCfg(MsgBlock* pMsgBlock)
{
    DIAG_BSP_NV_AUTH_STRU *pstMsg = (DIAG_BSP_NV_AUTH_STRU *)pMsgBlock;
    g_ulPrivilegeLevel = pstMsg->ulLevel;
}

/*****************************************************************************
 Function Name   : diag_NvWrProc
 Description     : 该函数用于处理从NvProcEntry传进来的写NV命令
 Input           : pstReq 待处理数据
 Output          : None
 Return          : VOS_UINT32

 History         :
    1.y00228784      2012-11-22  Draft Enact
    2.c64416         2014-11-18  适配新的诊断架构
    2.c00326366      2015-06-10  新增多条NV的写处理，并把写操作转到C核处理
                     转到C核处理的原因: 1. 避免NV写接口阻塞导致其他DIAG命令处理延迟
                                        2. NV鉴权的操作在C核，鉴权状态在C核记录

*****************************************************************************/
VOS_UINT32 diag_NvWrProc(VOS_UINT8* pstReq)
{
    VOS_UINT32 ret;
    MSP_DIAG_CNF_INFO_STRU stDiagInfo = {0};
    DIAG_CMD_NV_WR_REQ_STRU* pstNVWRReq = NULL;
    DIAG_FRAME_INFO_STRU *pstDiagHead = NULL;
    DIAG_CMD_NV_WR_CNF_STRU stNVWRCnf = {0};
    VOS_UINT32 i = 0;
    VOS_UINT32 ulOffset = 0;
    VOS_UINT32 ulNvid, ulLen;
    VOS_UINT8 *pData;

    pstDiagHead = (DIAG_FRAME_INFO_STRU*)(pstReq);

    pstNVWRReq = (DIAG_CMD_NV_WR_REQ_STRU*)(pstDiagHead->aucData + sizeof(MSP_DIAG_DATA_REQ_STRU));

    stDiagInfo.ulMsgType = DIAG_MSG_TYPE_BSP;

    pData = (VOS_UINT8*)(&pstNVWRReq->ulNVId);

    for(i = 0; i < pstNVWRReq->ulCount; i++)
    {
        ulNvid    = *(VOS_UINT32*)(pData + ulOffset);
        ulOffset += sizeof(VOS_UINT32);

        ulLen     = *(VOS_UINT32*)(pData + ulOffset);
        ulOffset += sizeof(VOS_UINT32);

        if (VOS_YES != diag_IsAuthNv(ulNvid))
        {
            goto DIAG_ERROR2;
        }

        printk(KERN_ERR "NV Write ulNVId=0x%x\n", ulNvid);

        /*写入NV项*/
        ret = NV_WriteEx(pstNVWRReq->ulModemid, ulNvid, (pData + ulOffset), ulLen);
        if(ret != ERR_MSP_SUCCESS)
        {
           printk(KERN_ERR "[%s]:NV Write ERR 0x%x,ulNVId=0x%x\n",__FUNCTION__, ret, ulNvid);
           goto DIAG_ERROR2;
        }
        ulOffset += ulLen;
    }

    DIAG_MSG_COMMON_PROC(stDiagInfo, stNVWRCnf, pstDiagHead);

    stNVWRCnf.ulModemid  = pstNVWRReq->ulModemid;
    stNVWRCnf.ulRc       = ret;

    ret = DIAG_MsgReport(&stDiagInfo, &stNVWRCnf, sizeof(stNVWRCnf));

    return ret;

DIAG_ERROR2:

    DIAG_MSG_COMMON_PROC(stDiagInfo, stNVWRCnf, pstDiagHead);

    stNVWRCnf.ulModemid  = pstNVWRReq->ulModemid;
    stNVWRCnf.ulRc       = ERR_MSP_FAILURE;

    ret = DIAG_MsgReport(&stDiagInfo, &stNVWRCnf, sizeof(stNVWRCnf));

    return ret;
}

#else
/*****************************************************************************
 Function Name   : diag_NvAuthSendAcore
 Description     : 向A核发送NV鉴权结果
 Input           : ulLev

 History         :
    1.c00326366      2015-08-04  Draft Enact

*****************************************************************************/
VOS_UINT32 diag_NvAuthSendAcore(VOS_UINT32 ulLev)
{
    DIAG_BSP_NV_AUTH_STRU *pstNvAuth;

    pstNvAuth = (DIAG_BSP_NV_AUTH_STRU *)VOS_AllocMsg(MSP_PID_DIAG_AGENT,
                        (sizeof(DIAG_BSP_NV_AUTH_STRU) - VOS_MSG_HEAD_LENGTH));
    if(pstNvAuth == NULL)
    {
        diag_printf("%s: alloc msg fail\n", __FUNCTION__);
        return ERR_MSP_FAILURE;
    }
    pstNvAuth->ulReceiverPid  = MSP_PID_DIAG_APP_AGENT;
    pstNvAuth->ulMsgId        = DIAG_MSG_BSP_NV_AUTH_REQ;
    pstNvAuth->ulLevel        = ulLev;

    if(ERR_MSP_SUCCESS != VOS_SendMsg(MSP_PID_DIAG_AGENT, pstNvAuth))
    {
        diag_printf("%s: send msg fail\n", __FUNCTION__);
        return ERR_MSP_FAILURE;
    }

    return ERR_MSP_SUCCESS;
}
#endif

/*****************************************************************************
 Function Name   : diag_NvAuthProc
 Description     : HIMS获取NV鉴权命令的处理接口
 Input           : pstReq 待处理数据
 Output          : None
 Return          : VOS_UINT32

 History         :
    1.c00326366      2012-11-22  Draft Enact

*****************************************************************************/
VOS_UINT32 diag_NvAuthProc(VOS_UINT8* pstReq)
{
    VOS_UINT32 ulRet;
    MSP_DIAG_CNF_INFO_STRU     stDiagInfo = {0};
    DIAG_FRAME_INFO_STRU *pstDiagHead;

#if (VOS_LINUX == VOS_OS_VER)
    VOS_UINT32 ulLen;
    DIAG_BSP_MSG_A_TRANS_C_STRU *pstInfo;
    DIAG_BSP_COMM_CNF_STRU stCommCnf;
#endif

    pstDiagHead = (DIAG_FRAME_INFO_STRU*)(pstReq);

    stDiagInfo.ulMsgType = DIAG_MSG_TYPE_BSP;

#if (VOS_LINUX == VOS_OS_VER)
    DIAG_MSG_BSP_ACORE_CFG_PROC(ulLen, pstDiagHead, pstInfo, ulRet);

    return ulRet;

DIAG_ERROR:
    stCommCnf.ulRet = ulRet;
    DIAG_MSG_COMMON_PROC(stDiagInfo, stCommCnf, pstDiagHead);

    ulRet = DIAG_MsgReport(&stDiagInfo, &stCommCnf, sizeof(DIAG_BSP_COMM_CNF_STRU));

    return ulRet;

#else

    DIAG_CMD_NV_AUTH_REQ_STRU *pstAuthReq;
    DIAG_CMD_NV_AUTH_CNF_STRU  stAuthCnf = {0};

    pstAuthReq = (DIAG_CMD_NV_AUTH_REQ_STRU*)(pstDiagHead->aucData + sizeof(MSP_DIAG_DATA_REQ_STRU));

    /*获取当前的解锁码*/
    if (VOS_OK != MMA_VerifyOperatorLockPwd(pstAuthReq->aucAuth))
    {
        (VOS_VOID)diag_NvAuthSendAcore(DIAG_LEVEL_NORMAL);
        stAuthCnf.ulRc = VOS_ERR;
    }
    else
    {
        stAuthCnf.ulRc = diag_NvAuthSendAcore(DIAG_LEVEL_ADVANCED);
    }

    DIAG_MSG_COMMON_PROC(stDiagInfo, stAuthCnf, pstDiagHead);

    ulRet = DIAG_MsgReport(&stDiagInfo, &stAuthCnf, sizeof(stAuthCnf));

    return ulRet;
#endif
}


/*****************************************************************************
 Function Name   : diag_BspAxiMonDataConfig
 Description     : 该函数为处理AXI Monitor采集配置命令接口
 Input           : pstReq 待处理数据
                   		ulCmdId 命令ID
 Output          : None
 Return          : VOS_UINT32

 History         :

*****************************************************************************/
VOS_UINT32 diag_BspAxiMonDataConfig(VOS_UINT8* pstReq)
{
    VOS_UINT32  ulRet = ERR_MSP_SUCCESS;

#if (VOS_LINUX == VOS_OS_VER)
    VOS_UINT32 ulLen;
    DIAG_BSP_MSG_A_TRANS_C_STRU *pstInfo;
    MSP_DIAG_CNF_INFO_STRU stDiagInfo = {0};
    DIAG_BSP_COMM_CNF_STRU stAxiCnf;

    DIAG_FRAME_INFO_STRU *pData;
    pData = (DIAG_FRAME_INFO_STRU *)pstReq;


    DIAG_MSG_BSP_ACORE_CFG_PROC(ulLen, pData, pstInfo, ulRet);

    return ulRet;

DIAG_ERROR:
    stAxiCnf.ulRet = ulRet;
    DIAG_MSG_COMMON_PROC(stDiagInfo,stAxiCnf,pData);

    ulRet = DIAG_MsgReport(&stDiagInfo,&stAxiCnf, sizeof(DIAG_BSP_COMM_CNF_STRU));

    return ulRet;

#else
#if 0
    VOS_UINT32 cnf_data_len = 0;
    VOS_UINT8 *pdata =NULL;
    AXI_DATA_CONFIG_CNF_STRU * axi_data_config_cnf = NULL;
    MSP_DIAG_CNF_INFO_STRU stDiagInfo;
    DIAG_BSP_COMM_AXI_CNF_STRU* stAxiCnf;

    pdata = (VOS_UINT8*)(pData->aucData)+sizeof(MSP_DIAG_DATA_REQ_STRU);
    axi_data_config_cnf = DRV_AXI_DATA_CONFIG(pdata, (VOS_UINT*)&cnf_data_len);

    if(VOS_NULL != axi_data_config_cnf)
    {
        cnf_data_len += sizeof(DIAG_BSP_COMM_AXI_CNF_STRU);
        stAxiCnf = (DIAG_BSP_COMM_AXI_CNF_STRU*)VOS_MemAlloc(MSP_PID_DIAG_AGENT, DYNAMIC_MEM_PT,cnf_data_len);
        if(VOS_NULL == stAxiCnf)
        {
            return ERR_MSP_MALLOC_FAILUE;
        }

        DIAG_MSG_COMMON_PROC(stDiagInfo,(*stAxiCnf),pData);

        (VOS_VOID)VOS_MemCpy(stAxiCnf.ucData,axi_data_config_cnf,cnf_data_len - sizeof(DIAG_BSP_COMM_AXI_CNF_STRU));

        ulRet = DIAG_MsgReport(&stDiagInfo,stAxiCnf, cnf_data_len);

        VOS_MemFree(MSP_PID_DIAG_AGENT, stAxiCnf);
    }
    else
    {
        ulRet = ERR_MSP_FAILURE;
    }
#endif
    return ulRet;
#endif


}

/*****************************************************************************
 Function Name   : diag_BspAxiMonConfig
 Description     : 该函数为处理AXI Monitor监控配置命令接口
 Input           : pstReq 待处理数据
                   ulCmdId 命令ID
 Output          : None
 Return          : VOS_UINT32

 History         :

*****************************************************************************/
VOS_UINT32 diag_BspAxiMonConfig(VOS_UINT8* pstReq)
{
    VOS_UINT32  ulRet = ERR_MSP_SUCCESS;

#if (VOS_LINUX == VOS_OS_VER)
    VOS_UINT32 ulLen;
    DIAG_BSP_MSG_A_TRANS_C_STRU *pstInfo;
    MSP_DIAG_CNF_INFO_STRU stDiagInfo = {0};
    DIAG_BSP_COMM_CNF_STRU stAxiCnf;

    DIAG_FRAME_INFO_STRU *pData;
    pData = (DIAG_FRAME_INFO_STRU *)pstReq;

    DIAG_MSG_BSP_ACORE_CFG_PROC(ulLen, pData, pstInfo, ulRet);

    return ulRet;

DIAG_ERROR:
    stAxiCnf.ulRet = ulRet;
    DIAG_MSG_COMMON_PROC(stDiagInfo,stAxiCnf,pData);

    ulRet = DIAG_MsgReport(&stDiagInfo,&stAxiCnf, sizeof(DIAG_BSP_COMM_CNF_STRU));

    return ulRet;

#else
#if 0
    VOS_UINT32 cnf_data_len = 0;
    VOS_UINT8 *pdata =NULL;
    AXI_MON_CONFIG_CNF_STRU * axi_mon_config_cnf = NULL;
    MSP_DIAG_CNF_INFO_STRU stDiagInfo;
    DIAG_BSP_COMM_AXI_CNF_STRU* stAxiCnf;

    pdata = (VOS_UINT8*)(pData->aucData)+sizeof(MSP_DIAG_DATA_REQ_STRU);
    axi_mon_config_cnf = DRV_AXI_MON_CONFIG(pdata, (VOS_UINT*)&cnf_data_len);

    if(VOS_NULL != axi_mon_config_cnf)
    {
        cnf_data_len += sizeof(DIAG_BSP_COMM_AXI_CNF_STRU);
        stAxiCnf = (DIAG_BSP_COMM_AXI_CNF_STRU*)VOS_MemAlloc(MSP_PID_DIAG_AGENT, DYNAMIC_MEM_PT,cnf_data_len);
        if(VOS_NULL == stAxiCnf)
        {
            return ERR_MSP_MALLOC_FAILUE;
        }

        DIAG_MSG_COMMON_PROC(stDiagInfo,(*stAxiCnf),pData);

        (VOS_VOID)VOS_MemCpy(stAxiCnf.ucData,axi_mon_config_cnf,cnf_data_len - sizeof(DIAG_BSP_COMM_AXI_CNF_STRU));

        ulRet = DIAG_MsgReport(&stDiagInfo,stAxiCnf, cnf_data_len);

        VOS_MemFree(MSP_PID_DIAG_AGENT, stAxiCnf);
    }
    else
    {
        ulRet = ERR_MSP_FAILURE;
    }
#endif
    return ulRet;
#endif
}

/*****************************************************************************
 Function Name   : diag_BspAxiMonTerminate
 Description     : 该函数为处理AXI Monitor监控终止命令接口
 Input           : pstReq 待处理数据
                   ulCmdId 命令ID
 Output          : None
 Return          : VOS_UINT32

 History         :

*****************************************************************************/
VOS_UINT32 diag_BspAxiMonTerminate(VOS_UINT8* pstReq)
{
    VOS_UINT32 ulRet = ERR_MSP_SUCCESS;
    DIAG_FRAME_INFO_STRU *pData;

#if (VOS_LINUX == VOS_OS_VER)
    VOS_UINT32 ulLen;
    DIAG_BSP_MSG_A_TRANS_C_STRU *pstInfo;
    MSP_DIAG_CNF_INFO_STRU stDiagInfo = {0};
    DIAG_BSP_COMM_CNF_STRU stAxiCnf;

    pData = (DIAG_FRAME_INFO_STRU *)pstReq;

    DIAG_MSG_BSP_ACORE_CFG_PROC(ulLen, pData, pstInfo, ulRet);

    return ulRet;

DIAG_ERROR:
    stAxiCnf.ulRet = ulRet;
    DIAG_MSG_COMMON_PROC(stDiagInfo,stAxiCnf,pData);

    ulRet = DIAG_MsgReport(&stDiagInfo,&stAxiCnf, sizeof(DIAG_BSP_COMM_CNF_STRU));

    return ulRet;

#else

	DIAG_BSP_COMM_CNF_STRU stAxiCnf ={0};

    MSP_DIAG_CNF_INFO_STRU stDiagInfo = {0};

    pData = (DIAG_FRAME_INFO_STRU *)pstReq;

	stAxiCnf.ulRet  = ERR_MSP_SUCCESS;

    DIAG_MSG_COMMON_PROC(stDiagInfo,stAxiCnf,pData);

    ulRet = DIAG_MsgReport(&stDiagInfo,&stAxiCnf, sizeof(DIAG_BSP_COMM_CNF_STRU));

    return ulRet;

#endif
}

/*****************************************************************************
 Function Name   : diag_BspAxiMonRegConfig
 Description     : AXI Monitor采集寄存器配置接口
 Input           : pstReq 待处理数据
                   ulCmdId 命令ID
 Output          : None
 Return          : VOS_UINT32

 History         :

*****************************************************************************/
VOS_UINT32 diag_BspAxiMonRegConfig(VOS_UINT8* pstReq)
{
    VOS_UINT32 ulRet = ERR_MSP_SUCCESS;
    DIAG_FRAME_INFO_STRU *pData;

#if (VOS_LINUX == VOS_OS_VER)
    VOS_UINT32 ulLen;
    DIAG_BSP_MSG_A_TRANS_C_STRU *pstInfo;
    MSP_DIAG_CNF_INFO_STRU stDiagInfo = {0};
    DIAG_BSP_COMM_CNF_STRU stAxiCnf;

    pData = (DIAG_FRAME_INFO_STRU *)pstReq;


    DIAG_MSG_BSP_ACORE_CFG_PROC(ulLen, pData, pstInfo, ulRet);

    return ulRet;

DIAG_ERROR:
    stAxiCnf.ulRet = ulRet;
    DIAG_MSG_COMMON_PROC(stDiagInfo,stAxiCnf,pData);

    ulRet = DIAG_MsgReport(&stDiagInfo,&stAxiCnf, sizeof(DIAG_BSP_COMM_CNF_STRU));

    return ulRet;

#else
	DIAG_BSP_COMM_CNF_STRU stAxiCnf ={0};
    MSP_DIAG_CNF_INFO_STRU stDiagInfo = {0};
    pData = (DIAG_FRAME_INFO_STRU *)pstReq;

	stAxiCnf.ulRet = 0;//DRV_AXI_REG_CONFIG(((VOS_UINT8*)(pData->aucData)+sizeof(MSP_DIAG_DATA_REQ_STRU)));

    DIAG_MSG_COMMON_PROC(stDiagInfo,stAxiCnf,pData);

    ulRet = DIAG_MsgReport(&stDiagInfo,&stAxiCnf, sizeof(DIAG_BSP_COMM_CNF_STRU));

    return ulRet;
#endif
}

/*****************************************************************************
 Function Name   : diag_BspAxiMonDataCtrl
 Description     : AXI Monitor采集控制命令接口:启动、停止、导出
 Input           : pstReq 待处理数据
                   ulCmdId 命令ID
 Output          : None
 Return          : VOS_UINT32

 History         :

*****************************************************************************/
VOS_UINT32 diag_BspAxiMonDataCtrl(VOS_UINT8* pstReq)
{
    VOS_UINT32 ulRet = ERR_MSP_SUCCESS;
    DIAG_FRAME_INFO_STRU *pData;

#if (VOS_LINUX == VOS_OS_VER)
    VOS_UINT32 ulLen;
    DIAG_BSP_MSG_A_TRANS_C_STRU *pstInfo;
    MSP_DIAG_CNF_INFO_STRU stDiagInfo = {0};
    DIAG_BSP_COMM_CNF_STRU stAxiCnf;

    pData = (DIAG_FRAME_INFO_STRU *)pstReq;


    DIAG_MSG_BSP_ACORE_CFG_PROC(ulLen, pData, pstInfo, ulRet);

    return ulRet;

DIAG_ERROR:
    stAxiCnf.ulRet = ulRet;
    DIAG_MSG_COMMON_PROC(stDiagInfo,stAxiCnf,pData);

    ulRet = DIAG_MsgReport(&stDiagInfo,&stAxiCnf, sizeof(DIAG_BSP_COMM_CNF_STRU));

    return ulRet;

#else
	DIAG_BSP_COMM_CNF_STRU stAxiCnf ={0};
    MSP_DIAG_CNF_INFO_STRU stDiagInfo = {0};

    pData = (DIAG_FRAME_INFO_STRU *)pstReq;

	stAxiCnf.ulRet = 0;//DRV_AXI_DATA_CTRL(((VOS_UINT8*)(pData->aucData)+sizeof(MSP_DIAG_DATA_REQ_STRU)));

    DIAG_MSG_COMMON_PROC(stDiagInfo,stAxiCnf,pData);

    ulRet = DIAG_MsgReport(&stDiagInfo,&stAxiCnf, sizeof(DIAG_BSP_COMM_CNF_STRU));

    return ulRet;
#endif
}

/*****************************************************************************
 Function Name   : diag_BspAxiMonStart
 Description     : AXI Monitor监控启动接口
 Input           : pstReq 待处理数据
                   ulCmdId 命令ID
 Output          : None
 Return          : VOS_UINT32

 History         :

*****************************************************************************/
VOS_UINT32 diag_BspAxiMonStart(VOS_UINT8* pstReq)
{
    VOS_UINT32 ulRet = ERR_MSP_SUCCESS;
    DIAG_FRAME_INFO_STRU *pData;

#if (VOS_LINUX == VOS_OS_VER)
    VOS_UINT32 ulLen;
    DIAG_BSP_MSG_A_TRANS_C_STRU *pstInfo;
    MSP_DIAG_CNF_INFO_STRU stDiagInfo = {0};
    DIAG_BSP_COMM_CNF_STRU stAxiCnf;
    pData = (DIAG_FRAME_INFO_STRU *)pstReq;

    DIAG_MSG_BSP_ACORE_CFG_PROC(ulLen, pData, pstInfo, ulRet);

    return ulRet;

DIAG_ERROR:
    stAxiCnf.ulRet = ulRet;
    DIAG_MSG_COMMON_PROC(stDiagInfo,stAxiCnf,pData);

    ulRet = DIAG_MsgReport(&stDiagInfo,&stAxiCnf, sizeof(DIAG_BSP_COMM_CNF_STRU));

    return ulRet;

#else
	DIAG_BSP_COMM_CNF_STRU stAxiCnf ={0};
    MSP_DIAG_CNF_INFO_STRU stDiagInfo = {0};
    pData = (DIAG_FRAME_INFO_STRU *)pstReq;

	stAxiCnf.ulRet = 0;//DRV_AXI_MON_START(((VOS_UINT8*)(pData->aucData)+sizeof(MSP_DIAG_DATA_REQ_STRU)));

    DIAG_MSG_COMMON_PROC(stDiagInfo,stAxiCnf,pData);
    ulRet = DIAG_MsgReport(&stDiagInfo,&stAxiCnf, sizeof(DIAG_BSP_COMM_CNF_STRU));

    return ulRet;
#endif
}

/*****************************************************************************
 Function Name   : diag_BspUtraceStart
 Description     : USB Trace命令处理入口
 Input           :VOS_UINT8* pstReq
                VOS_UINT32 ulCmdId
 Output          : None
 Return          : VOS_UINT32

 History         :
    1.w00182550      2013-3-5  Draft Enact

*****************************************************************************/
VOS_UINT32 diag_BspUtraceStart(VOS_UINT8* pstReq)
{
    VOS_UINT32 ulRet = ERR_MSP_SUCCESS;
#if (VOS_LINUX == VOS_OS_VER)
	DIAG_BSP_COMM_CNF_STRU stUtraceCnf ={0};
    MSP_DIAG_CNF_INFO_STRU stDiagInfo = {0};
    DIAG_FRAME_INFO_STRU *pData;
    pData = (DIAG_FRAME_INFO_STRU *)pstReq;


	stUtraceCnf.ulRet = 0;//DRV_UTRACE_START(((VOS_UINT8*)(pData->aucData)+sizeof(MSP_DIAG_DATA_REQ_STRU)));


    DIAG_MSG_COMMON_PROC(stDiagInfo,stUtraceCnf,pData);


    ulRet = DIAG_MsgReport(&stDiagInfo,&stUtraceCnf, sizeof(DIAG_BSP_COMM_CNF_STRU));
#endif
    return ulRet;
}

/*****************************************************************************
 Function Name   : diag_BspUtraceStop
 Description     : USB Trace命令处理入口
 Input           :VOS_UINT8* pstReq
                VOS_UINT32 ulCmdId
 Output          : None
 Return          : VOS_UINT32

 History         :
    1.w00182550      2013-3-5  Draft Enact

*****************************************************************************/
VOS_UINT32 diag_BspUtraceStop(VOS_UINT8* pstReq)
{
    VOS_UINT32 ulRet = ERR_MSP_SUCCESS;
#if (VOS_OS_VER == VOS_LINUX)
	DIAG_BSP_COMM_CNF_STRU stUtraceCnf ={0};
    MSP_DIAG_CNF_INFO_STRU stDiagInfo = {0};
    DIAG_FRAME_INFO_STRU *pData;
    pData = (DIAG_FRAME_INFO_STRU *)pstReq;


	stUtraceCnf.ulRet = 0;//DRV_UTRACE_TERMINATE(((VOS_UINT8*)(pData->aucData)+sizeof(MSP_DIAG_DATA_REQ_STRU)));

    DIAG_MSG_COMMON_PROC(stDiagInfo,stUtraceCnf,pData);

    ulRet = DIAG_MsgReport(&stDiagInfo,&stUtraceCnf, sizeof(DIAG_BSP_COMM_CNF_STRU));
#endif
    return ulRet;
}


/*****************************************************************************
 Function Name   : diag_BspLogProcEntry
 Description     : 该函数为处理DIAG FW发过来的BSP配置命令的处理入口
 Input           : pstReq 待处理数据
                   		ulCmdId 命令ID
 Output          : None
 Return          : VOS_UINT32

 History         :

*****************************************************************************/
VOS_UINT32 diag_BspLogProcEntry(VOS_UINT8* pstReq)
{
    DIAG_BSP_COMM_CNF_STRU  stLogSetCnf  = {0};
    MSP_DIAG_CNF_INFO_STRU stDiagInfo = {0};
    VOS_UINT32 ulRet = ERR_MSP_SUCCESS;
    DIAG_FRAME_INFO_STRU *pData;
#if (VOS_LINUX == VOS_OS_VER)
    VOS_UINT32 ulLen;
    DIAG_BSP_MSG_A_TRANS_C_STRU *pstInfo;
#endif

    pData = (DIAG_FRAME_INFO_STRU *)pstReq;

#if (VOS_LINUX == VOS_OS_VER)
    stLogSetCnf.ulRet = ulRet;
    DIAG_MSG_BSP_ACORE_CFG_PROC(ulLen, pData, pstInfo, ulRet);
    return ulRet;
DIAG_ERROR:
#endif


    DIAG_MSG_COMMON_PROC(stDiagInfo,stLogSetCnf,pData);

    //TODO:
    stLogSetCnf.ulRet = ulRet;

    ulRet = DIAG_MsgReport(&stDiagInfo,&stLogSetCnf, sizeof(DIAG_BSP_COMM_CNF_STRU));

	return ulRet;

}

/*****************************************************************************
 Function Name   : diag_BspSysviewProc
 Description     :
 Input           : pstReq 待处理数据
                   		ulCmdId 命令ID
 Output          : None
 Return          : VOS_UINT32

 History         :

*****************************************************************************/
VOS_UINT32 diag_BspSysviewProc(VOS_UINT8* pstReq)
{
    VOS_UINT32  ulRet = ERR_MSP_SUCCESS;
#if (VOS_LINUX == VOS_OS_VER)
    VOS_UINT32 ulLen;
    DIAG_BSP_MSG_A_TRANS_C_STRU *pstInfo;

    DIAG_FRAME_INFO_STRU *pData;
    pData = (DIAG_FRAME_INFO_STRU *)pstReq;

    //TODO:

    DIAG_MSG_BSP_ACORE_CFG_PROC(ulLen, pData, pstInfo, ulRet);
    return ulRet;
DIAG_ERROR:
    return ulRet;
#else

#endif
#if 0
    VOS_UINT32 cnf_data_len = 0;
    DIAG_BSP_SYVIEW_SWT_CFG_STRU *pstSysviewSet = VOS_NULL;
    DIAG_BSP_SYVIEW_SWT_CNF_STRU  *pstLogSysviewCnf  = {0};
    MSP_DIAG_CNF_INFO_STRU stDiagInfo;

    pstSysviewSet = (DIAG_BSP_SYVIEW_SWT_CFG_STRU *)((VOS_UINT8*)(pData->aucData)+sizeof(MSP_DIAG_DATA_REQ_STRU));

    ulRet= mdrv_om_set_sysview_swt(pstSysviewSet->trace_type,pstSysviewSet->trace_swt,pstSysviewSet->period);

    if(ulRet  == ERR_MSP_SUCCESS)
    {
        if((pstSysviewSet->trace_type ==SYSVIEW_TASK_INFO )&&(pstSysviewSet->trace_swt ==1 ))
        {
            cnf_data_len = sizeof(DIAG_BSP_SYVIEW_SWT_CNF_STRU)+sizeof(DIAG_BSP_TASK_INFO_STRU)*128;
            pstLogSysviewCnf =(DIAG_BSP_SYVIEW_SWT_CNF_STRU*)VOS_MemAlloc(MSP_PID_DIAG_AGENT, DYNAMIC_MEM_PT,cnf_data_len);
            if(VOS_NULL == pstLogSysviewCnf)
            {
                return ERR_MSP_MALLOC_FAILUE;
            }
            pstLogSysviewCnf->ullen = sizeof(DIAG_BSP_TASK_INFO_STRU)*128;
            mdrv_om_get_alltaskinfo((pstLogSysviewCnf->st_task_info), sizeof(DIAG_BSP_TASK_INFO_STRU)*128);
        }
        else
        {
            cnf_data_len = sizeof(DIAG_BSP_SYVIEW_SWT_CNF_STRU);
            pstLogSysviewCnf =(DIAG_BSP_SYVIEW_SWT_CNF_STRU*)VOS_MemAlloc(MSP_PID_DIAG_AGENT, DYNAMIC_MEM_PT,cnf_data_len);
            if(VOS_NULL == pstLogSysviewCnf)
            {
                return ERR_MSP_MALLOC_FAILUE;
            }
            pstLogSysviewCnf->ullen  = 0;
        }
    }
    else
    {
        cnf_data_len = sizeof(DIAG_BSP_SYVIEW_SWT_CNF_STRU);
        pstLogSysviewCnf =(DIAG_BSP_SYVIEW_SWT_CNF_STRU*)VOS_MemAlloc(MSP_PID_DIAG_AGENT, DYNAMIC_MEM_PT,cnf_data_len);
        if(VOS_NULL == pstLogSysviewCnf)
        {
            return ERR_MSP_MALLOC_FAILUE;
        }
        pstLogSysviewCnf->ullen  = 0;

    }

    pstLogSysviewCnf->ulRet = ulRet;
    pstLogSysviewCnf->trace_type =pstSysviewSet->trace_type;

    DIAG_MSG_COMMON_PROC(stDiagInfo,(*pstLogSysviewCnf),pData);

    ulRet = DIAG_MsgReport(&stDiagInfo,(VOS_UINT8 *)pstLogSysviewCnf,cnf_data_len);

    VOS_MemFree(MSP_PID_DIAG_AGENT, pstLogSysviewCnf);
#endif
    return ulRet;
}


/*****************************************************************************
 Function Name   : diag_BspMsgProc
 Description     : bsp处理消息处理包括连接断开
 Input           : None
 Output          : None
 Return          : None
 History         :

*****************************************************************************/
VOS_UINT32 diag_BspMsgProc(DIAG_FRAME_INFO_STRU *pData)
{
    VOS_UINT32 ulRet = ERR_MSP_INVALID_PARAMETER ;
    VOS_UINT32 i = 0;
    if(DIAG_MSG_TYPE_BSP != pData->stID.pri4b)
    {
        diag_printf("%s Rcv Error Msg Id 0x%x\n",__FUNCTION__,pData->ulCmdId);
        return ulRet;
    }

    for(i = 0; i< sizeof(g_DiagBspFunc)/sizeof(g_DiagBspFunc[0]);i++)
    {
        if(g_DiagBspFunc[i].ulCmdId == pData->ulCmdId)
        {
            g_DiagBspFunc[i].ulReserve ++;
            ulRet = g_DiagBspFunc[i].pFunc((VOS_UINT8*)pData);
            return ulRet;
        }
    }

    return ulRet;
}

VOS_VOID diag_BspShowDebugInfo(VOS_VOID)
{
    VOS_UINT32 i = 0;

    for(i=0;i<sizeof(g_DiagBspFunc)/sizeof(DIAG_BSP_PROC_FUN_STRU);i++)
    {
        diag_printf("Command ID :0x%x ,Ops Num %d\n",g_DiagBspFunc[i].ulCmdId,g_DiagBspFunc[i].ulReserve);
    }
}

#if (VOS_OS_VER != VOS_LINUX)
/*****************************************************************************
 Function Name   : diag_AppTransBspProc
 Description     : A核发过来的bsp诊断命令处理
 Input           : pMsgBlock    诊断命令请求的内容
 Output          : None
 Return          : VOS_UINT32

 History         :
    1.c64416      2014-11-18  Draft Enact

*****************************************************************************/
VOS_UINT32 diag_AppTransBspProc(MsgBlock* pMsgBlock)
{
    DIAG_BSP_MSG_A_TRANS_C_STRU *pstInfo;

    pstInfo = (DIAG_BSP_MSG_A_TRANS_C_STRU *)pMsgBlock;

    return diag_BspMsgProc(&pstInfo->stInfo);
}
#else
/*****************************************************************************
 Function Name   : diag_BspMsgInit
 Description     : MSP dsp部分初始化
 Input           : None
 Output          : None
 Return          : None
 History         :

*****************************************************************************/
VOS_VOID diag_BspMsgInit(VOS_VOID)
{
    /*注册message消息回调*/
    DIAG_MsgProcReg(DIAG_MSG_TYPE_BSP,diag_BspMsgProc);
}
#endif

#ifdef __cplusplus
#if __cplusplus
}
#endif /* __cpluscplus */
#endif /* __cpluscplus */



