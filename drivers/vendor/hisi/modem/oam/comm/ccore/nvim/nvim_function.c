/*****************************************************************************/
/*                                                                           */
/*                Copyright 1999 - 2003, Huawei Tech. Co., Ltd.              */
/*                           ALL RIGHTS RESERVED                             */
/*                                                                           */
/* FileName: NVIM_Function.c                                                 */
/*                                                                           */
/* Author: Jiang kaibo                                                       */
/*                                                                           */
/* Version: 1.0                                                              */
/*                                                                           */
/* Date: 2008-06                                                             */
/*                                                                           */
/* Description: implement NV subroutine                                      */
/*                                                                           */
/* Others:                                                                   */
/*                                                                           */
/* History:                                                                  */
/* 1. Date: 2008-06                                                          */
/*    Author: Jiang kaibo                                                    */
/*    Modification: Create this file                                         */
/*                                                                           */
/*****************************************************************************/

#include "nvim_internalfunc.h"
#include "nvim_fileoperateinterface.h"
#include "NVIM_ResumeId.h"
#include "mdrv.h"
#include "NvIdList.h"

#ifdef __cplusplus
    #if __cplusplus
        extern "C" {
    #endif
#endif

/* Macro of log */
/*lint -e767 -e960 修改人:蒋开波 00105005;检视人:徐铖 51137;原因:Log打印 */
#define THIS_FILE_ID PS_FILE_ID_NVIM_FUNCTION_C
/*lint +e767 +e960 修改人:蒋开波 00105005;检视人:徐铖 51137; */

#define  NV_IMEI_LEN           (15)        /* IMEI NV长度 */
/* 机要数据相关 */
#define NV_FILE_CFD_NAME       "CFDNVTable.bin"
extern  VOS_UINT32              g_ulCFDNvFileId;

/* NV 写操作是否需要记录slice标记 */
extern  VOS_UINT32              g_ulRecordNvFlag;

/*NV Memory ADDR*/
VOS_UINT_PTR                    g_ulNVMemAddr       = 0;

/* Reslut of restore Manufacture & User NV data */
VOS_UINT32  g_ulRestoreResult = NV_RESTORE_RESULT_INIT;

/* 存放NV数据的内存块 */
NV_CONTROL_FILE_INFO_STRU *g_pstNVDataBuf = VOS_NULL_PTR;

/* NV Restore Info */
NV_CONTROL_FILE_INFO_STRU          *g_pstNVMemoryFileInfo = VOS_NULL_PTR;

/* NV's ID coms from 1 to 20 */
NV_FILE_HANDLE_STRU    g_astNvFileHandle[NV_BACKUP_FILE_MAX_NUM+1];

/* NV's ID coms from 1 to 20 */
NV_FILE_HANDLE_STRU    g_astBackupNvFileHandle[NV_BACKUP_FILE_MAX_NUM+1];

/* NV恢复时一次打开所有的bin， NV's ID coms from 1 to 20 */
NV_RESUME_FILE_HANDLE_STRU  g_astResumFileHandle[NV_BACKUP_FILE_MAX_NUM+1];

/* 控制NV写操作的互斥信号量 */
VOS_SEM                g_ulNVWriteSem;

/*lint -e606 修改人:蒋开波 00105005;检视人:徐铖 51137;原因:使用绝对路径对NV文件进行操作*/

#if((VOS_WIN32 == VOS_OS_VER) || (defined __PS_WIN32_RECUR__))

/* Absolute Path for Operating NV file */
VOS_CHAR *g_aucNvBackupFile   = "NvBackupFile.bin"; /* For MTT only */

VOS_CHAR *g_aucNvFolderPath   = ".\\yaffs0\\NvimUse\\"; /* NV File path */
VOS_CHAR *g_aucNvCtrlFilePath = ".\\yaffs0\\NvimUse\\NvimCtrl.bin"; /* NV Ctrl File */
/* Absolute Path for Operating NV Backup file */
VOS_CHAR *g_aucNvBackupFolder       = ".\\yaffs0\\NvimBackup"; /* NV backup file Dir */
VOS_CHAR *g_aucNvBackupFolderPath   = ".\\yaffs0\\NvimBackup\\"; /* NV backup file path */
VOS_CHAR *g_aucNvBackupCtrlFilePath = ".\\yaffs0\\NvimBackup\\NvimCtrl.bin"; /* NV Backup Ctrl File */

VOS_CHAR g_acNvUseDir[]       = ".\\yaffs0\\NvimUse";

#if (FEATURE_ON == FEATURE_S_SKU_M_OPERATORS)
VOS_CHAR g_acNvUpdateDir[NV_MAX_UPDEATE_PATH_LEN]   = {0};
VOS_CHAR g_acNvDefaultDir[NV_MAX_DEFAULT_PATH_LEN]  = {0};
VOS_CHAR g_acNvSkuDir[]                             = ".\\yaffs0\\sku";
#else
VOS_CHAR g_acNvUpdateDir[]   = ".\\yaffs0\\NvimUp";
VOS_CHAR g_acNvDefaultDir[]  = ".\\yaffs0\\NvimDef";
#endif

const VOS_CHAR g_acNvUpdateFile[]  = "\\NVUpdate.bin";
const VOS_CHAR g_acNvBackupFile[]  = "\\NVBackup.bin";
const VOS_CHAR g_acNvCfdFile[]     = "\\CFDNVTable.bin";

const VOS_CHAR g_acNvLogFilePath[] = ".\\NVLog.bin";

/*FlashLess文件接口定义*/
const VOS_CHAR g_aucNvFilePath[]   = ".\\yaffs0\\Nvim.bin";  /* NV Ctrl File */

#elif ( (VOS_VXWORKS == VOS_OS_VER) || (VOS_RTOSCK == VOS_OS_VER) )
/* 以下几个目录存在于内存中，与文件系统无关 */
/* Absolute Path for Operating NV Backup file */
const VOS_CHAR g_aucNvBackupFolder[]       = "/yaffs0/NvimBackup"; /* NV backup file Dir */
const VOS_CHAR g_aucNvBackupFolderPath[]   = "/yaffs0/NvimBackup/"; /* NV backup file path */
const VOS_CHAR g_aucNvBackupCtrlFilePath[] = "/yaffs0/NvimBackup/NvimCtrl.bin"; /* NV Backup Ctrl File */

const VOS_CHAR g_acNvUpdateFile[]    = "/NVUpdate.bin";
const VOS_CHAR g_acNvBackupFile[]    = "/NVBackup.bin";
const VOS_CHAR g_acNvCfdFile[]       = "/CFDNVTable.bin";

/*FlashLess文件接口定义*//* V9R1 SFT多文件系统不会出现flashbess，暂时没有定这个路径 */
const VOS_CHAR g_aucNvFilePath[]     = "/yaffs0/Nvim/Nvim.bin";  /* NV Ctrl File */


const VOS_CHAR g_acNvLogFilePath[]   = "/mnvm2:0/NVLog.bin";

/* Absolute Path for Operating NV file */
const VOS_CHAR g_aucNvFolderPath[]   = "/mnvm2:0/NvimUse/"; /* NV File path */
const VOS_CHAR g_aucNvCtrlFilePath[] = "/mnvm2:0/NvimUse/NvimCtrl.bin"; /* NV Ctrl File */

VOS_CHAR g_acNvUseDir[]              = "/mnvm2:0/NvimUse";

#if (FEATURE_ON == FEATURE_S_SKU_M_OPERATORS)
VOS_CHAR g_acNvUpdateDir[NV_MAX_UPDEATE_PATH_LEN]  = {0};
VOS_CHAR g_acNvDefaultDir[NV_MAX_DEFAULT_PATH_LEN] = {0};
VOS_CHAR g_acNvSkuDir[]                            = "/mnvm1:0/sku";
#else
VOS_CHAR g_acNvUpdateDir[]           = "/mnvm1:0/Nvim";
VOS_CHAR g_acNvDefaultDir[]          = "/mnvm3:0/NvimDef";
#endif

#endif
NV_PRIORITY_THRESHOLD_STRU g_stNvPriThreshold; /*存放从NV项中读出中优先级对应阈值*/

NV_PRIORITY_THRESHOLD_STRU g_stNvPriThresholdCur;/*存放当前中优先级NV项对应阈值*/

/* 可维可测信息，记录NV初始化时间 */
VOS_UINT32      g_ulNVInitStartSlice = 0;

/* 可维可测信息，记录NV结束时间 */
VOS_UINT32      g_ulNVInitEndSlice   = 0;

extern VOS_VOID XML_DecodeMain(VOS_BOOL *pbIsDecodeXml); /* XML Decode处理 */
extern VOS_VOID XML_DeleteFile(VOS_VOID);
/*****************************************************************************
 函 数 名  : NV_WriteDataEvent
 功能描述  : NV_WriteDataEvent事件上报
 输入参数  : VOS_UINT16 usID -> NV ID
             VOS_UINT32 ulOffset-> 相对buffer偏移量
             VOS_VOID *pItem -> NV data buffer
             VOS_UINT32 ulLength -> buffer length
             VOS_UINT32 ulResult-> 结果
 输出参数  :
 返 回 值  : VOS_VOID
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2012年05月24日
    作    者   : z00100318
    修改内容   :  V7R1C50 Flashless PhaseI项目新增函数
*****************************************************************************/
VOS_VOID NV_WriteDataEvent(VOS_UINT16      usID,
                            VOS_UINT32          ulOffset,
                            VOS_VOID            *pItem,
                            VOS_UINT32          ulLength,
                            VOS_UINT32          ulResult
)
{
    return;

#if 0
    PS_OM_EVENT_IND_STRU    *pstEvent;
    NVIM_FL_EVENT_DATA_STRU *pstData;
    VOS_UINT32              ulCpyLen;

    if(BSP_MODULE_SUPPORT == DRV_GET_LOCAL_FLASH_SUPPORT())
    {
        return;
    }

    pstEvent = (PS_OM_EVENT_IND_STRU*)VOS_MemAlloc(WUEPS_PID_OM, DYNAMIC_MEM_PT,
                                (sizeof(PS_OM_EVENT_IND_STRU)+sizeof(NVIM_FL_EVENT_DATA_STRU)));

    if(VOS_NULL_PTR == pstEvent)
    {
        return;
    }

    /* ulLength 指从usEventId开始到包尾的长度 */
    pstEvent->ulLength        = NV_MSG_HEADER_LEN + sizeof(NVIM_FL_EVENT_DATA_STRU);
    pstEvent->usEventId       = NVIM_EVENT_WRITE;
    pstEvent->usReserved      = 0;
    pstEvent->ulModuleId      = WUEPS_PID_OM;

    pstData = (NVIM_FL_EVENT_DATA_STRU *)pstEvent->aucData;

    pstData->usNVId         = usID;
    pstData->usOffset       = (VOS_UINT16)ulOffset;
    pstData->ulResult       = ulResult;
    pstData->ulNVDataLen    = ulLength;

    if(ulLength > NVIM_FL_EVENT_DATA_LEN)
    {
        ulCpyLen    = NVIM_FL_EVENT_DATA_LEN;
    }
    else
    {
        ulCpyLen    = ulLength;
    }

    if(VOS_NULL != ulCpyLen)
    {
        /*lint -e534*/
        VOS_MemCpy(pstData->aucData, pItem, ulCpyLen);
        /*lint +e534*/
    }

    OM_Event(pstEvent);

    /*lint -e534*/
    VOS_MemFree(WUEPS_PID_OM, pstEvent);
    /*lint +e534*/

    return;
#endif
}

/*****************************************************************************
Function   : NV_WriteDDR
Description: Write NV to the DDR only.
Input      : VOS_UINT16 usID -> NV ID
             VOS_VOID *pItem -> NV data buffer
             VOS_UINT32 ulLength -> buffer length
Return     : Ok or Err.
Other      :
*****************************************************************************/
VOS_UINT32 NV_WriteDDR(VOS_UINT32 ulFileId, VOS_UINT32 ulTotalOffset, VOS_VOID *pItem,VOS_UINT32 ulLength)
{
    /*lint -e40 *//*加入vxworks的头问题引入lint问题，走读人徐铖*/
    if((VOS_YES == mdrv_crypto_check_sec()) && (g_ulCFDNvFileId == ulFileId))
    {
        /* Forbid write seure NV file when seure version */
        PS_LOG(WUEPS_PID_USIM, 0, PS_PRINT_ERROR,
                "NV_WriteDDR:NV ID is secured:");
        return NV_WRITE_SECURE_FAIL;
    }
    /*lint +e40 *//*加入vxworks的头问题引入lint问题，走读人徐铖*/

    /* 更新缓存中的NV数据 */
    NV_SetAreaAccessable(NV_AREA_WRITABLE);
    /*lint -e534*/
    VOS_MemCpy(((VOS_CHAR*)g_pstNVDataBuf + ulTotalOffset), (VOS_CHAR*)pItem, ulLength);
    /*lint +e534*/
    NV_SetAreaAccessable(NV_AREA_NO_WRITABLE);

    return VOS_OK;
}


/*****************************************************************************
Function   : NV_WriteContent
Description: Write NV to the file without open file.
Input      : VOS_UINT16 usID -> NV ID
             VOS_VOID *pItem -> NV data buffer
             VOS_UINT32 ulLength -> buffer length
Return     : Ok or Err.
Other      :
*****************************************************************************/
VOS_UINT32 NV_WriteContent(VOS_UINT32 ulFileId,      VOS_UINT32 ulNvOffset,
                                  VOS_UINT32 ulTotalOffset, VOS_VOID   *pItem,
                                  VOS_UINT32 ulLength)
{
    FILE                       *fp;
    VOS_UINT32                  ulRslt = VOS_OK;

    /*lint -e40 *//*加入vxworks的头问题引入lint问题，走读人徐铖*/
    if((VOS_YES == mdrv_crypto_check_sec()) && (g_ulCFDNvFileId == ulFileId))
    {
        /* Forbid write seure NV file when seure version */
        PS_LOG(WUEPS_PID_USIM, 0, PS_PRINT_ERROR,
                "NV_WriteContent:NV ID is secured:");
        return NV_WRITE_SECURE_FAIL;
    }
    /*lint +e40 *//*加入vxworks的头问题引入lint问题，走读人徐铖*/

    /* no flashless case */
    if (BSP_MODULE_SUPPORT == mdrv_misc_support_check(BSP_MODULE_TYPE_LOCALFLASH))
    {
        /* read File Handle */
        fp = g_astResumFileHandle[ulFileId].fp;

        /*lint -e413 *//* make pclint happy */
        ulRslt = NV_WriteDataToFile(fp, pItem, ulLength, (VOS_INT32)ulNvOffset);
        /*lint +e13 *//* make pclint happy */
    }
    else /* flashless */
    {
        /* read File Handle */
        fp = g_astResumFileHandle[0].fp;

        /*lint -e413 *//* make pclint happy */
        ulRslt = NV_WriteDataToFile(fp, pItem, ulLength, (VOS_INT32)ulTotalOffset);
        /*lint +e13 *//* make pclint happy */
    }

    return ulRslt;
}

/*****************************************************************************
Function   : NV_WriteDirect
Description: Write NV to the file without open file.
Input      : VOS_UINT16 usID -> NV ID
             VOS_VOID *pItem -> NV data buffer
             VOS_UINT32 ulLength -> buffer length
Return     : Ok or Err.
Other      :
*****************************************************************************/
VOS_UINT32 NV_WriteDirect(MODEM_ID_ENUM_UINT16 enModemID,VOS_UINT16 usID,VOS_VOID *pItem,VOS_UINT32 ulLength)
{
    VOS_UINT32                          ulRslt = VOS_OK;
    NV_ID_RETUEN_INFO_STRU              stNvIdReturnInfo;

    ulRslt = NV_NvIdCheck(enModemID, usID, 0, pItem, ulLength, &stNvIdReturnInfo);
    if(NV_OK != ulRslt)
    {
        PS_LOG(WUEPS_PID_USIM, 0, PS_PRINT_ERROR,
                "NV_WriteDirect:NV ID check fail.\n");
        return ulRslt;
    }

    ulRslt = NV_WriteDDR((VOS_UINT32)stNvIdReturnInfo.usFileId,
                          stNvIdReturnInfo.ulTotalOffset, pItem, ulLength);

    if(NV_OK != ulRslt)
    {
        PS_LOG(WUEPS_PID_USIM, 0, PS_PRINT_ERROR,
                "NV_WriteDirect:write nv content fail.\n");
    }

    return ulRslt;
}

/*****************************************************************************
Function   : NV_WriteDirectAll
Description: Write NV to the file without open file.
Input      : VOS_UINT16 usID -> NV ID
             VOS_VOID *pItem -> NV data buffer
             VOS_UINT32 ulLength -> buffer length
Return     : Ok or Err.
Other      :
*****************************************************************************/
VOS_UINT32 NV_WriteDirectAll(VOS_UINT16 usID,VOS_VOID *pItem,VOS_UINT32 ulLength)
{
    VOS_UINT32                  ulRslt = VOS_OK;
    NV_FILE_LIST_INFO_STRU      stFileListInfo;
    NV_REFERENCE_DATA_INFO_STRU stNvIdInfo;

    if(VOS_OK != NV_Ctrl_File_Search_InMemory(usID,g_pstNVDataBuf,&stFileListInfo,&stNvIdInfo))
    {
        /* ID not exist */
        PS_LOG1(WUEPS_PID_USIM, 0, PS_PRINT_ERROR,
                "NV_WriteDirectAll:NV ID not exist.\n",usID);
        return NV_ID_NOT_EXIST;
    }


    /*lint -e539 -e525 -e830*/
    if(ulLength > (VOS_UINT32)(stNvIdInfo.usNvLength*stNvIdInfo.ucModemNum))
    {
        /* Buffer not enough */
        PS_LOG(WUEPS_PID_USIM, 0, PS_PRINT_ERROR,
                        "NV_WriteDirectAll:The Buffer is too long.\n");
        return NV_BUFFER_TOO_LONG;
    }
    /*lint +e539 +e525 +e830*/

    ulRslt = NV_WriteDDR(stFileListInfo.ulFileId,
                         (g_astNvFileHandle[stNvIdInfo.usFileId].ulOffset + stNvIdInfo.ulNvOffset),
                         pItem, ulLength);

    if(NV_OK != ulRslt)
    {
        PS_LOG(WUEPS_PID_USIM, 0, PS_PRINT_ERROR,
                "NV_WriteDirectAll:write nv content fail.\n");
    }

    return ulRslt;
}

/* nv模块下移，不再支持通过给任务发消息写 */
#if 0
/*****************************************************************************
 函 数 名  : NV_SendMsgToNvFlush
 功能描述  : NV_SendMsgToNvFlush 给NV_Flush任务发送消息
 输入参数  :
 输出参数  :
 返 回 值  : VOS_UINT32
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2012年05月24日
    作    者   : d00212987
    修改内容   :  V7R1C50 Flashless PhaseII项目新增函数
*****************************************************************************/
VOS_UINT32 NV_SendMsgToNvFlush(VOS_VOID)
{
    NVIM_FLUSH_MSG_STRU *pstNvFlushMsg;

    pstNvFlushMsg = (NVIM_FLUSH_MSG_STRU*)VOS_AllocMsg(WUEPS_PID_NVIM_FLUSH,
                     sizeof(NVIM_FLUSH_MSG_STRU) - VOS_MSG_HEAD_LENGTH);

    if (VOS_NULL_PTR == pstNvFlushMsg)
    {
        PS_LOG(WUEPS_PID_NVIM_FLUSH, 0, PS_PRINT_ERROR,
                "WUEPS_PID_NVIM_FLUSH Alloc pstNvFlushMsg Error.");

        return NV_ALLOC_BUFFER_FAIL;
    }

    /* 填充消息头 */
    pstNvFlushMsg->ulReceiverPid = WUEPS_PID_NVIM_FLUSH;
    pstNvFlushMsg->ulMsgName     = NV_FLUSH_NOTIFY_IND;

    if (VOS_OK != VOS_SendMsg(WUEPS_PID_NVIM_FLUSH, pstNvFlushMsg))
    {
        PS_LOG(WUEPS_PID_NVIM_FLUSH, 0, PS_PRINT_ERROR,
                "WUEPS_PID_NVIM_FLUSH Send Msg TO NvimFL_MsgProc Error.");

        return NV_SEND_MSG_FAIL;
    }

    return NV_OK;
}
#endif

/*****************************************************************************
 函 数 名  : NV_FlushMemoryToFile
 功能描述  : 把内存刷新到文件中
 输入参数  : pcFilePath: 文件路径
             pData     : 写入内容
             ulDataLen : 写入内容长度
 输出参数  :
 返 回 值  : VOS_UINT32
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2013年07月18日
    作    者   : d00212987
    修改内容   : 新增函数
*****************************************************************************/
VOS_UINT32 NV_FlushMemoryToFile(VOS_CHAR *pcFilePath, VOS_VOID *pData,VOS_UINT32 ulDataLen)
{
    FILE                               *fp;

    fp = NV_File_Open(pcFilePath, NV_FILE_OPEN_MODE_RW);

    if (VOS_NULL_PTR == fp)
    {
        NV_WriteDataEvent(NV_FULSH_ID, 0, pData, 0, NV_OPEN_FILE_FAIL);
        return NV_OPEN_FILE_FAIL;
    }

    /* 调用fwrite 更新整个NV文件 */
    if (MDRV_ERROR == NV_File_Write(pData, ulDataLen, 1, fp))
    {
        NV_File_Close(fp);
        NV_WriteDataEvent(NV_FULSH_ID, 0, pData, 0, NV_WRITE_FLASH_FAIL);
        return NV_WRITE_FLASH_FAIL;
    }

    /* 调用fclose 关闭V文件 */
    NV_File_Close(fp);

    /*发送Trace数据*/
    NV_WriteDataEvent(NV_FULSH_ID, 0, pData, ulDataLen, NV_OK);

    return VOS_OK;
}

/*****************************************************************************
 函 数 名  : NV_FlushDdrProc
 功能描述  : 升级过程中所有写nv操作，都只写到ddr中，最后靠该函数把ddr刷入文件
 输入参数  : bIsCreatefile : 是否需要创建标记文件
             bIsDecodeXml  : 是否解析XML文件
 输出参数  :
 返 回 值  : VOS_UINT32
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2012年05月23日
    作    者   : d00212987
    修改内容   : 新增函数
*****************************************************************************/
VOS_UINT32 NV_FlushDdrProc(VOS_BOOL bIsCreatefile, VOS_BOOL bIsDecodeXml)
{
    NV_FILE_LIST_INFO_STRU             *pstFileListInfo;
    VOS_CHAR                            aucFilePath[NV_ABSLT_PATH_LEN] = {0};
    VOS_UINT32                          ulFileId;
    VOS_UINT32                          ulRstult;
    VOS_UINT32                          ulLength = 0;
    VOS_UINT32                          i;

    /* 如没有备份恢复且没有XML需解析则无需把ddr刷写到NV文件中 */
    if ((VOS_TRUE != bIsCreatefile) && (VOS_TRUE != bIsDecodeXml))
    {
        return NV_OK;
    }

    /* 获取NV更新互斥信号量 */
    if (VOS_OK != VOS_SmP(g_ulNVWriteSem, 0))
    {
        /* log 打印 */
        NV_Printf("NV_FlushDdrToFile:VOS_SmP failed.\n");
        return NV_TAKE_SEM_FAIL;
    }

    /* 获取IPC硬件锁 */
    if (MDRV_OK != mdrv_ipc_sem_take(IPC_SEM_NVIM, NV_IPC_TIME_FOREVER))
    {
        /*lint -e534*/
        VOS_SmV(g_ulNVWriteSem);
        /*lint +e534*/
        NV_Printf("NV_FlushDdrToFile:get drv IPC semtake failed.\n");
        return NV_SMP_ERR;
    }

    /* 是否是远程文件系统，不是直接返回OK */
    if (BSP_MODULE_SUPPORT == mdrv_misc_support_check(BSP_MODULE_TYPE_LOCALFLASH))
    {
        pstFileListInfo = (NV_FILE_LIST_INFO_STRU *)((VOS_CHAR*)g_pstNVDataBuf + sizeof(NV_CONTROL_FILE_INFO_STRU));
        for (i = 0; i < g_pstNVDataBuf->ulFileListNum; i++)
        {
            ulFileId = pstFileListInfo[i].ulFileId;

            if (0 == ulFileId)
            {
                NV_Printf("NV_FlushDdrToFile:nv file id is error 0\r\n");

                /* 释放IPC硬件锁 */
                mdrv_ipc_sem_give(IPC_SEM_NVIM);
                /*lint -e534*/
                VOS_SmV(g_ulNVWriteSem);
                /*lint +e534*/
                return NV_FILE_ID_ERR;
            }

            /* 查找机要文件 FileID */
            if ((VOS_YES == mdrv_crypto_check_sec()) && (g_ulCFDNvFileId == ulFileId))
            {
                /* 安全版本不能修改机要NV文件 */
                continue;
            }

            /* 拼文件的绝对路径 */
            NV_GetFileAbsltPath(g_aucNvFolderPath,
                                (VOS_CHAR*)(pstFileListInfo[i].aucFileName),
                                aucFilePath, NV_ABSLT_PATH_LEN);

            /* offset需要取后一个，第一个是ctrl.bin */
            ulRstult = NV_FlushMemoryToFile(aucFilePath, ((VOS_VOID *)((VOS_CHAR *)g_pstNVDataBuf +  g_astNvFileHandle[i + 1].ulOffset)),
                                            g_astNvFileHandle[i + 1].ulSize);
            if (VOS_OK != ulRstult)
            {
                NV_Printf("NV_FlushDdrToFile:Flush %s is fail\r\n", pstFileListInfo[i].aucFileName);

                /* 释放IPC硬件锁 */
                mdrv_ipc_sem_give(IPC_SEM_NVIM);
                /*lint -e534*/
                VOS_SmV(g_ulNVWriteSem);
                /*lint +e534*/
                return ulRstult;
            }
        }
    }
    else
    {
        for (i=0; i<= g_pstNVDataBuf->ulFileListNum; i++)
        {
            ulLength += g_astNvFileHandle[i].ulSize;
        }

        ulRstult = NV_FlushMemoryToFile((VOS_CHAR*)g_aucNvFilePath, (VOS_VOID*)g_pstNVDataBuf, ulLength);
        if (VOS_OK != ulRstult)
        {
            NV_Printf("NV_FlushDdrToFile:Flush %s is fail\r\n", g_aucNvFilePath);

            /* 释放IPC硬件锁 */
            mdrv_ipc_sem_give(IPC_SEM_NVIM);
            /*lint -e534*/
            VOS_SmV(g_ulNVWriteSem);
            /*lint +e534*/
            return ulRstult;
        }
    }

    /* 释放IPC硬件锁 */
    mdrv_ipc_sem_give(IPC_SEM_NVIM);
    /*lint -e534*/
    VOS_SmV(g_ulNVWriteSem);
    /*lint +e534*/

    /* 删除 xml */
    XML_DeleteFile();

    if(VOS_TRUE == bIsCreatefile)
    {
        NV_File_Create((VOS_CHAR*)g_acNvUseDir, (VOS_CHAR*)g_acNvBackupFile);
    }

    return NV_OK;
}

/*****************************************************************************
Function   : NV_GetLengthAll
Description: Get NV All Data length from the file without Auth.
Input      : VOS_UINT16 usID -> NV ID
             VOS_UINT32 *pulLength -> buffer to save NV len.
Return     : Ok or Err.
Other      :
*****************************************************************************/
VOS_UINT32 NV_GetLengthAll(VOS_UINT16 usID, NV_CONTROL_FILE_INFO_STRU  *pstNVCtrlInfo,VOS_UINT32 *pulLength)
{
    NV_FILE_LIST_INFO_STRU      stFileListInfo;
    NV_REFERENCE_DATA_INFO_STRU stNvIdInfo;

    if(VOS_OK != NV_Ctrl_File_Search_InMemory(usID,pstNVCtrlInfo,&stFileListInfo,&stNvIdInfo))
    {
        /* ID not exist */
        PS_LOG1(WUEPS_PID_USIM, 0, PS_PRINT_ERROR,
                "NV_GetLength:NV ID not exist.\n",usID);
        return NV_ID_NOT_EXIST;
    }

    *pulLength = (VOS_UINT32)(stNvIdInfo.usNvLength * stNvIdInfo.ucModemNum);

    return NV_OK;
}

/*****************************************************************************
 函 数 名  : NV_NVBackupOption
 功能描述  : 使用区原有NV文件备份到Falsh区域
 输入参数  : enBackupWrite 需要备份到的分区

 输出参数  : 无

 返 回 值  : VOS_UINT32

 修改历史      :
  1.日    期   : 2013年10月26日
    作    者   : d00212987
    修改内容   : BalongV9R1 NV备份数据丢失容错&恢复
*****************************************************************************/
VOS_UINT32 NV_BackupOption(NVIM_BACKUP_WRITE_FLASH_ENUM_UINT32 enBackupWrite)
{
    VOS_UINT32                          ulBackupTotalLen;

    /* 所有NV数据文件的大小 + NvimCtrl.bin文件的大小 */
    ulBackupTotalLen = g_astNvFileHandle[g_pstNVDataBuf->ulFileListNum].ulOffset
                     + g_astNvFileHandle[g_pstNVDataBuf->ulFileListNum].ulSize;

    /* Call DRV API to copy Backup buffer to Flash */
    if(VOS_OK != DRV_NVBACKUP_WRITE((VOS_UINT8*)g_pstNVDataBuf,ulBackupTotalLen))
    {
        PS_LOG(WUEPS_PID_USIM, 0, PS_PRINT_ERROR,
                "NV_BaseNvBackup:Write Flash fail.\n");

        return NV_WRITE_FLASH_FAIL;
    }

    if(NVIM_BACKUP_WRITE_BASE_AND_EXT_SPACE == enBackupWrite)
    {
        /* Call DRV API to copy Backup buffer to Ex Flash */
        if(VOS_OK != DRV_NVBACKUP_EXT_WRITE((VOS_UINT8*)g_pstNVDataBuf,ulBackupTotalLen))
        {
            PS_LOG(WUEPS_PID_USIM, 0, PS_PRINT_ERROR,
                    "NV_BaseNvBackup:Write Ex Flash fail.\n");

            return NV_WRITE_EXT_FLASH_FAIL;
        }
    }

    return NV_OK;
}

/*****************************************************************************
Function   : NV_Backup
Description: 仅供AT^NVBACKUP使用，把内存区NV数据备份到底软两块Flash区
Input      : none
Return     : Ok or Err.
Other      :
*****************************************************************************/
VOS_UINT32 NV_Backup(VOS_VOID)
{
     /* 原有NV备份到Flash */
    if (NV_OK != NV_BackupOption(NVIM_BACKUP_WRITE_BASE_AND_EXT_SPACE))
    {
        NV_Printf("NV_Backup:Backup base NV fail.\n");
        return NV_WRITE_FLASH_FAIL;
    }

#if (FEATURE_ON == FEATURE_S_SKU_M_OPERATORS)

    /* SKU形态备份user.bin和spec.bin */
    if (NV_OK != NV_SkuBackupNvFile())
    {
        NV_Printf("NV_Backup:Backup Sku NvFile fail.\n");
        return NV_SKU_WRITE_FILE_FAIL;
    }

#endif
    return NV_OK;
}

/*****************************************************************************
Function   : NV_ExNoBackup
Description: 内部使用接口，只备份到原有底软Flash区，不备份到底软扩展Flash区
Input      : none
Return     : Ok or Err.
Other      :
*****************************************************************************/
VOS_UINT32 NV_ExNoBackup(VOS_VOID)
{
     /* 原有NV备份到Flash */
    if (NV_OK != NV_BackupOption(NVIM_BACKUP_WRITE_BASE_SPACE))
    {
        NV_Printf("NV_ExNoBackup:Backup base NV fail.\n");
        return NV_WRITE_FLASH_FAIL;
    }

#if (FEATURE_ON == FEATURE_S_SKU_M_OPERATORS)

    /* SKU形态备份user.bin和spec.bin */
    if (NV_OK != NV_SkuBackupNvFile())
    {
        NV_Printf("NV_ExNoBackup:Backup Sku NvFile fail.\n");
        return NV_SKU_WRITE_FILE_FAIL;
    }

#endif
    return NV_OK;
}

/*****************************************************************************
Function   : NV_BackupCheckRead
Description: Check whether Flash has NV backup data
Input      :
Return     : Ok or Err.
Other      :
*****************************************************************************/
VOS_UINT32 NV_BackupCheckRead(NVIM_BACKUP_READ_FLASH_ENUM_UINT32 enBackupRead)
{
    NV_CONTROL_FILE_INFO_STRU           stCtrlInfo;
    VOS_INT                             lRest = VOS_ERR;

    /*lint -e534*/
    VOS_MemSet(&stCtrlInfo, 0, sizeof(NV_CONTROL_FILE_INFO_STRU));
    /*lint +e534*/

    if(NVIM_BACKUP_READ_EXT_SPACE == enBackupRead)
    {
        lRest = DRV_NVBACKUP_EXT_READ((VOS_UINT8*)&stCtrlInfo, sizeof(NV_CONTROL_FILE_INFO_STRU));
    }
    else if(NVIM_BACKUP_READ_BASE_SPACE == enBackupRead)
    {
        lRest = DRV_NVBACKUP_READ((VOS_UINT8*)&stCtrlInfo, sizeof(NV_CONTROL_FILE_INFO_STRU));
    }
    else
    {
        NV_Printf("NV_BackupCheckRead:enBackupRead type error.\n");
    }

    /* Get file num from Flash */
    if(NV_OK !=  lRest)
    {
        NV_Printf("NV_BackupCheckRead:Backup Read check fail,read type %d.\n", enBackupRead);

        return NV_NO_BACKUP;
    }

    if(NV_CTRL_FILE_MAGIC_NUM != stCtrlInfo.ulMagicNum)
    {
        PS_LOG(WUEPS_PID_USIM, 0, PS_PRINT_ERROR,
                "NV_BackupCheckRead:Magic num is wrong.\n");

        NV_Printf("NV_BackupCheckRead:Magic num is wrong num=%0x ,read type %d\n",
                   stCtrlInfo.ulMagicNum, enBackupRead);

        return NV_NO_BACKUP;
    }

    /* According to file num to check whether Flash has NV backup data */
    if(( NV_BACKUP_FILE_MIN_NUM <= stCtrlInfo.ulFileListNum)&&( NV_BACKUP_FILE_MAX_NUM >= stCtrlInfo.ulFileListNum ))
    {
        /* Flash has NV backup data */
        return NV_OK;
    }

    NV_Printf("NV_BackupCheckRead:There is no NV backup data,read type %d.\n", enBackupRead);

    return NV_NO_BACKUP;
}

/*****************************************************************************
Function   : NV_BackupCheck
Description: Check whether Flash has NV backup data
Input      :
Return     : Ok or Err.
Other      :
*****************************************************************************/
VOS_UINT32 NV_BackupCheck(VOS_VOID)
{
    VOS_UINT32                          ulRest;

    ulRest = NV_BackupCheckRead(NVIM_BACKUP_READ_BASE_SPACE);
    if(NV_OK != ulRest)
    {
        NV_Printf("NV_BackupCheck:return fail %d.\n", ulRest);
    }

    return ulRest;
}

/*****************************************************************************
Function   : NV_ResumeBackupRead
Description: Resume NV common file and NV Ctrl file from Flash
Input      :
Return     : Ok or Err.
Other      :
*****************************************************************************/
VOS_UINT32 NV_ResumeBackupRead(NVIM_BACKUP_READ_FLASH_ENUM_UINT32 enBackupRead)
{
    VOS_UINT32                          ulOffset = 0;
    NV_FILE_LIST_INFO_STRU             *pstFileListInfo;
    VOS_INT                             lRest = VOS_ERR;
    VOS_UINT32                          i;

    /* Copy NV backup data to 384k buffer */
    g_pstNVMemoryFileInfo = (NV_CONTROL_FILE_INFO_STRU*)VOS_MemAlloc(WUEPS_PID_USIM,
                                               DYNAMIC_MEM_PT, NV_BACKUP_BUFFER_SIZE);
    if(VOS_NULL_PTR == g_pstNVMemoryFileInfo)
    {
        PS_LOG(WUEPS_PID_USIM, 0, PS_PRINT_ERROR,
                "NV_ResumeBackupRead:Alloc NV Backup Buffer fail.\n");

        NV_Printf("NV_ResumeBackupRead:Alloc NV Backup Buffer fail,read type %d.\n", enBackupRead);

        return NV_ALLOC_BUFFER_FAIL;
    }

    /* First read out backup buffer ctrl file header info,then get file list size */
    if(NVIM_BACKUP_READ_EXT_SPACE == enBackupRead)
    {
        lRest = DRV_NVBACKUP_EXT_READ((VOS_UINT8*)g_pstNVMemoryFileInfo,
                                        NV_BACKUP_BUFFER_SIZE);
    }
    else if(NVIM_BACKUP_READ_BASE_SPACE == enBackupRead)
    {
        lRest = DRV_NVBACKUP_READ((VOS_UINT8*)g_pstNVMemoryFileInfo,
                                        NV_BACKUP_BUFFER_SIZE);
    }
    else
    {
        NV_Printf("NV_ResumeBackupRead:enBackupRead type error.\n");
    }

    if(VOS_OK != lRest)
    {
        /* Read flash fail */
        NV_Printf("NV_ResumeBackupRead:Read out File List info fail,read type %d.\n", enBackupRead);
        /*lint -e534*/
        VOS_MemFree(WUEPS_PID_USIM, g_pstNVMemoryFileInfo);
        /*lint +e534*/

        return VOS_ERR;
    }

    g_astBackupNvFileHandle[0].ulOffset = ulOffset;
    g_astBackupNvFileHandle[0].ulSize = g_pstNVMemoryFileInfo->ulCtrlFileSize;

    ulOffset += g_astBackupNvFileHandle[0].ulSize;

    pstFileListInfo = (NV_FILE_LIST_INFO_STRU *)((VOS_CHAR *)g_pstNVMemoryFileInfo + sizeof(NV_CONTROL_FILE_INFO_STRU));

    for(i = 1; i <= g_pstNVMemoryFileInfo->ulFileListNum; i++)
    {
        g_astBackupNvFileHandle[i].ulOffset = ulOffset;
        g_astBackupNvFileHandle[i].ulSize = pstFileListInfo[i-1].ulFileSize;

        ulOffset += pstFileListInfo[i-1].ulFileSize;
    }

    return VOS_OK;
}

/*****************************************************************************
Function   : NV_BackupImeiRead
Description: read Imei from backup Flash
Input      :
Return     : Ok or Err.
Other      :
*****************************************************************************/
VOS_UINT32 NV_BackupImeiRead(VOS_UINT8 *pucImei, NVIM_BACKUP_READ_FLASH_ENUM_UINT32 enBackupRead)
{
    NV_FILE_LIST_INFO_STRU             *pstFileListInfo;
    NV_REFERENCE_DATA_INFO_STRU        *pstNvIdInfo;
    NV_CONTROL_FILE_INFO_STRU          *pstNVMemoryFileInfo;
    NV_FILE_HANDLE_STRU                 astBackupNvFileImeiHandle[NV_BACKUP_FILE_MAX_NUM+1];
    VOS_UINT32                          ulOffset = 0;
    VOS_UINT32                          ulTotalOffset = 0;
    VOS_INT                             lRest = VOS_ERR;
    VOS_UINT32                          i;

    /* Copy NV backup data to 384k buffer */
    pstNVMemoryFileInfo = (NV_CONTROL_FILE_INFO_STRU*)VOS_MemAlloc(WUEPS_PID_USIM,
                                                   DYNAMIC_MEM_PT, NV_BACKUP_BUFFER_SIZE);
    if(VOS_NULL_PTR == pstNVMemoryFileInfo)
    {
        NV_Printf("NV_BackupImeiRead:Alloc NV Backup Buffer fail,read type %d.\n", enBackupRead);

        return NV_ALLOC_BUFFER_FAIL;
    }

    if(NVIM_BACKUP_READ_EXT_SPACE == enBackupRead)
    {
        lRest = DRV_NVBACKUP_EXT_READ((VOS_UINT8*)pstNVMemoryFileInfo,
                                        NV_BACKUP_BUFFER_SIZE);
    }
    else if(NVIM_BACKUP_READ_BASE_SPACE == enBackupRead)
    {
        lRest = DRV_NVBACKUP_READ((VOS_UINT8*)pstNVMemoryFileInfo,
                                        NV_BACKUP_BUFFER_SIZE);
    }
    else
    {
        NV_Printf("NV_BackupImeiRead:enBackupRead type error.\n");
    }

    if(VOS_OK != lRest)
    {
        /* Read flash fail */
        NV_Printf("NV_BackupImeiRead:Read out File List info fail,read type %d.\n", enBackupRead);
        /*lint -e534*/
        VOS_MemFree(WUEPS_PID_USIM, pstNVMemoryFileInfo);
        /*lint +e534*/

        return VOS_ERR;
    }

    /*lint -e534*/
    VOS_MemSet(astBackupNvFileImeiHandle, 0, sizeof(astBackupNvFileImeiHandle));
    /*lint +e534*/

    astBackupNvFileImeiHandle[0].ulOffset = ulOffset;
    astBackupNvFileImeiHandle[0].ulSize = pstNVMemoryFileInfo->ulCtrlFileSize;

    ulOffset += astBackupNvFileImeiHandle[0].ulSize;

    pstFileListInfo = (NV_FILE_LIST_INFO_STRU *)((VOS_CHAR *)pstNVMemoryFileInfo + sizeof(NV_CONTROL_FILE_INFO_STRU));

    for(i = 1; i <= pstNVMemoryFileInfo->ulFileListNum; i++)
    {
        astBackupNvFileImeiHandle[i].ulOffset = ulOffset;
        astBackupNvFileImeiHandle[i].ulSize = pstFileListInfo[i-1].ulFileSize;

        ulOffset += pstFileListInfo[i-1].ulFileSize;
    }

    pstNvIdInfo = (NV_REFERENCE_DATA_INFO_STRU*)((VOS_CHAR*)pstNVMemoryFileInfo + pstNVMemoryFileInfo->ulNvRefOffset);

    /* 获取IMEI的偏移量 */
    /* 缓存中的偏移量 = XXNV.bin在缓存中的偏移量 + NVID在XXNV.bin中的偏移量 */
    ulTotalOffset = (astBackupNvFileImeiHandle[pstNvIdInfo->usFileId].ulOffset + pstNvIdInfo->ulNvOffset);

    /*lint -e534*/
    VOS_MemCpy((VOS_VOID*)pucImei, (VOS_VOID*)((VOS_CHAR *)pstNVMemoryFileInfo + ulTotalOffset), NV_IMEI_LEN);

    VOS_MemFree(WUEPS_PID_USIM, pstNVMemoryFileInfo);
    /*lint +e534*/

    return VOS_OK;
}

/*****************************************************************************
Function   : NV_ResumeNvFile
Description: Resume NV common file and NV Ctrl file from Flash
Input      :
Return     : Ok or Err.
Other      :
*****************************************************************************/
VOS_UINT32 NV_ResumeNvFile(VOS_VOID)
{
    NVIM_BACKUP_READ_FLASH_ENUM_UINT32  enBackupRead = NVIM_BACKUP_READ_SPACE_BUTT;
    VOS_UINT8                           aucNvImei[NV_IMEI_LEN]  = {0};
    VOS_UINT8                           aucNvExImei[NV_IMEI_LEN]  = {0};
    VOS_UINT32                          ulRest;

    /* 判断NVBackUp2分区是否存在，不存在读直接恢复NVBackup分区 */
    if(NV_OK != NV_BackupCheckRead(NVIM_BACKUP_READ_EXT_SPACE))
    {
        NV_Printf("NV_ResumeNvFile:#info:There is no NV Ex backup data.\n");
    }
    else
    {
        enBackupRead = NVIM_BACKUP_READ_EXT_SPACE;
    }

    /* Check whether Flash has NV backup data */
    if(NV_OK != NV_BackupCheckRead(NVIM_BACKUP_READ_BASE_SPACE))
    {
        /* No NV Backup data */
        NV_Printf("NV_ResumeNvFile:There is no NV backup data.\n");
        return NV_NO_BACKUP;
    }

    if(NVIM_BACKUP_READ_EXT_SPACE == enBackupRead)
    {
        if(NV_OK != NV_BackupImeiRead(aucNvImei, NVIM_BACKUP_READ_BASE_SPACE))
        {
            NV_Printf("NV_ResumeNvFile:read base Imei nv fail.\n");
            return NV_Read_BASE_IMEI_FAIL;
        }

        if(NV_OK != NV_BackupImeiRead(aucNvExImei, NVIM_BACKUP_READ_EXT_SPACE))
        {
            NV_Printf("NV_ResumeNvFile:read Ext Imei nv fail.\n");
            return NV_Read_EXT_IMEI_FAIL;
        }

        if(VOS_OK != VOS_MemCmp(aucNvImei, aucNvExImei, NV_IMEI_LEN))
        {
            /* 使用扩展分区 */
            ulRest = NV_ResumeBackupRead(NVIM_BACKUP_READ_EXT_SPACE);
            if(NV_OK != ulRest)
            {
                NV_Printf("NV_ResumeNvFile:read NV Ex backup data fail.\n");
            }

            return ulRest;
        }
    }

    /* 使用原有分区 */
    ulRest = NV_ResumeBackupRead(NVIM_BACKUP_READ_BASE_SPACE);
    if(NV_OK != ulRest)
    {
        NV_Printf("NV_ResumeNvFile:read NV base backup data fail.\n");
        return ulRest;
    }

    return NV_OK;
}

/*****************************************************************************
Function   : NV_Old_ReadAll
Description: Read NV from Old NV common file without Auth. for restore
Input      : VOS_UINT16 usID -> NV ID
             VOS_VOID *pItem -> Save NV data buffer
             VOS_UINT32 ulLength -> buffer length
Return     : Ok or Err.
Other      :
*****************************************************************************/
VOS_UINT32 NV_Old_ReadAll(VOS_UINT16 usID,VOS_VOID *pItem,VOS_UINT32 ulLength)
{
    NV_FILE_LIST_INFO_STRU      stFileListInfo;
    NV_REFERENCE_DATA_INFO_STRU stNvIdInfo;
    VOS_UINT32                  ulTotalOffset;

    if(VOS_OK != NV_Ctrl_File_Search_InMemory(usID,g_pstNVMemoryFileInfo,
                                        &stFileListInfo,&stNvIdInfo))
    {
        /* ID not exist */
        PS_LOG1(WUEPS_PID_USIM, 0, PS_PRINT_ERROR,
                "NV_Old_Read:NV ID not exist.\n",usID);
        return NV_ID_NOT_EXIST;
    }

    /*lint -e539 -e525 -e830*/
    if(ulLength > (VOS_UINT32)(stNvIdInfo.usNvLength * stNvIdInfo.ucModemNum))
    {
        /* Buffer not enough */
        PS_LOG(WUEPS_PID_USIM, 0, PS_PRINT_ERROR,
                        "NV_Old_Read:The Buffer is not enough.\n");
        return NV_BUFFER_TOO_LONG;
    }
    /*lint +e539 +e525 +e830*/

    /* 缓存中的偏移量 = XXNV.bin在缓存中的偏移量 + NVID在XXNV.bin中的偏移量 */
    ulTotalOffset = g_astBackupNvFileHandle[stNvIdInfo.usFileId].ulOffset + stNvIdInfo.ulNvOffset;

    /* Read NV ID data and save to the buffer */
    /*lint -e534*/
    VOS_MemCpy(pItem, (VOS_CHAR *)g_pstNVMemoryFileInfo + ulTotalOffset, (stNvIdInfo.usNvLength*stNvIdInfo.ucModemNum));
    /*lint +e534*/

    return VOS_OK;
}

/*****************************************************************************
Function   : NV_Close_ALL_NV_File
Description: Close all NV file.
Input      :
Return     : Ok or Err.
Other      :
*****************************************************************************/
VOS_UINT32 NV_Close_ALL_NV_File(VOS_VOID)
{
    VOS_UINT32                  i;
    VOS_BOOL                    ulFlag = VOS_FALSE;

    /* Close All NV File */
    for (i=1; i<NV_BACKUP_FILE_MAX_NUM+1; i++)
    {
        if (VOS_NULL_PTR == g_astResumFileHandle[i].fp)
        {
            continue;
        }

        if (VOS_OK != NV_File_Close(g_astResumFileHandle[i].fp))
        {
            ulFlag = VOS_TRUE;
        }
    }

    for (i=1; i<NV_BACKUP_FILE_MAX_NUM+1; i++)
    {
        g_astResumFileHandle[i].fp = VOS_NULL_PTR;
    }

    if ( VOS_TRUE == ulFlag )
    {
        return VOS_ERR;
    }

    return VOS_OK;
}

/*****************************************************************************
Function   : NV_Open_ALL_NV_File
Description: Open all NV file. just open common nv file
Input      :
Return     : Ok or Err.
Other      :
*****************************************************************************/
VOS_UINT32 NV_Open_ALL_NV_File(VOS_VOID)
{
    VOS_UINT32                  i;
    VOS_CHAR                    aucFilePath[NV_ABSLT_PATH_LEN] = {0};
    NV_FILE_LIST_INFO_STRU      *pstFileListInfo;

    pstFileListInfo = (NV_FILE_LIST_INFO_STRU *)((VOS_CHAR *)g_pstNVDataBuf + sizeof(NV_CONTROL_FILE_INFO_STRU));

    /* no flashless case */
    if (BSP_MODULE_SUPPORT == mdrv_misc_support_check(BSP_MODULE_TYPE_LOCALFLASH))
    {
        /* 此处只打开普通文件 g_astResumFileHandle数组下标0保留不用 */
        for (i=0; i<(g_pstNVDataBuf->ulFileListNum); i++)
        {
            /* 拼文件的绝对路径 */
            NV_GetFileAbsltPath(g_aucNvFolderPath,
                                (VOS_CHAR*)(pstFileListInfo[i].aucFileName),
                                aucFilePath, NV_ABSLT_PATH_LEN);

            /* Open NV File and Record File Handle */
            g_astResumFileHandle[pstFileListInfo[i].ulFileId].fp = NV_File_Open(aucFilePath, NV_FILE_OPEN_MODE_RW);/*[false alarm]*/

            if (VOS_NULL_PTR == g_astResumFileHandle[pstFileListInfo[i].ulFileId].fp)
            {
                /* Close file */
                NV_Close_ALL_NV_File();

                return VOS_ERR;
            }
        }
    }
    else
    {
        g_astResumFileHandle[0].fp = NV_File_Open((VOS_CHAR*)g_aucNvFilePath, NV_FILE_OPEN_MODE_RW);

        if (VOS_NULL_PTR == g_astResumFileHandle[0].fp)
        {
            /* Close file */
            NV_Close_ALL_NV_File();

            return VOS_ERR;
        }
    }

    return VOS_OK;
}


/*****************************************************************************
Function   : NV_ResumeNvData
Description: Resume old NV data to new NV file
Input      : VOS_UINT32 ulNvNumLen -> NV num
             VOS_UINT16 *pusNvId -> ID list
Return     : Ok or Err.
Other      :
*****************************************************************************/
VOS_UINT32 NV_ResumeNvData(VOS_UINT32 ulNvNum,VOS_UINT16 *pusNvId)
{
    VOS_UINT32 i;
    VOS_UINT16 usID;
    VOS_UINT32 ulOldLength;
    VOS_UINT32 ulNewLength;
    VOS_UINT8 *pucDataBuf;
    VOS_UINT16 *pusItem;
    VOS_UINT32 ulRet;

    pusItem = pusNvId;

    for(i=0;i< ulNvNum;i++)
    {
        /* Get NV ID */
        usID = *pusItem;
        pusItem++;

        /* First get NV data from Old NV file */
        ulRet = NV_GetLengthAll(usID,g_pstNVMemoryFileInfo,&ulOldLength);

        if( VOS_OK != ulRet )
        {
            if( NV_ID_NOT_EXIST == ulRet )
            {
                /* a new NV,no need to resume */
                PS_LOG1(WUEPS_PID_USIM, 0, PS_PRINT_INFO,
                    "NV_ResumeNvData:New NV 0x%x \r\n",usID);
                continue;
            }
            else
            {
                /* Get old Nv data len. fail */
                PS_LOG1(WUEPS_PID_USIM, 0, PS_PRINT_ERROR,
                    "NV_ResumeNvData:Get old NV 0x%x len. fail\r\n",usID);

                return VOS_ERR;
             }
        }

        /* Get new Nv data len. from new NV Ctrl file */
        if(VOS_OK != NV_GetLengthAll(usID, g_pstNVDataBuf, &ulNewLength))
        {
            /* Get new NV data len. fail */
            PS_LOG1(WUEPS_PID_USIM, 0, PS_PRINT_ERROR,
                    "NV_ResumeNvData:Get new NV 0x%x len. fail\r\n",usID);

            return VOS_ERR;
        }

        /* check NV data len. */
        if(ulOldLength != ulNewLength)
        {
            PS_LOG1(WUEPS_PID_USIM, 0, PS_PRINT_ERROR,
                        "NV_ResumeNvData:NV 0x%x data len error\r\n",usID);

            return VOS_ERR;
        }

        pucDataBuf = (VOS_UINT8*)VOS_MemAlloc(WUEPS_PID_USIM,
                                               DYNAMIC_MEM_PT,ulOldLength);
        if(VOS_NULL_PTR == pucDataBuf)
        {
            PS_LOG(WUEPS_PID_USIM, 0, PS_PRINT_ERROR,
                    "NV_ResumeNvData:Alloc buffer fail\n");

            return VOS_ERR;
        }

        if(VOS_OK != NV_Old_ReadAll(usID,(VOS_VOID*) pucDataBuf,ulOldLength))
        {
            /* Get old NV data fail */
            PS_LOG1(WUEPS_PID_USIM, 0, PS_PRINT_ERROR,
                        "NV_ResumeNvData:Get old NV 0x%x data fail\r\n",usID);
            /*lint -e534*/
            VOS_MemFree(WUEPS_PID_USIM,pucDataBuf);
            /*lint +e534*/

            return VOS_ERR;
        }

        ulRet = NV_WriteDirectAll(usID,(VOS_VOID*)pucDataBuf,ulOldLength);

        /* 对返回值的判断中增加写硬加密NV项导致错误的处理 */
        if((VOS_OK != ulRet) && (NV_WRITE_SECURE_FAIL != ulRet))
        {
            /* Write new NV file fail */
            PS_LOG1(WUEPS_PID_USIM, 0, PS_PRINT_ERROR,
                        "NV_ResumeNvData:Write new NV 0x%x data fail\r\n",usID);

            /*lint -e534*/
            VOS_MemFree(WUEPS_PID_USIM,pucDataBuf);
            /*lint +e534*/

            return VOS_ERR;
        }

        /*lint -e534*/
        VOS_MemFree(WUEPS_PID_USIM,pucDataBuf);
        /*lint +e534*/

    }

    return VOS_OK;
}

/*****************************************************************************
Function   : NV_Del_Old
Description: Del old NV common file and old NV Ctrl file
Input      :
Return     : Ok or Err.
Other      :
*****************************************************************************/
VOS_UINT32 NV_Del_Old(VOS_VOID)
{
    if(VOS_NULL_PTR != g_pstNVMemoryFileInfo)
    {
        /*lint -e534*/
        VOS_MemFree(WUEPS_PID_USIM, g_pstNVMemoryFileInfo);
        /*lint +e534*/

        g_pstNVMemoryFileInfo = VOS_NULL_PTR;
    }

    return VOS_OK;
}

/*****************************************************************************
Function   : NV_PowerOffWriteNV
Description: 关机时把关机写的NV写入文件
Input      :

Return     : Ok or Err.
Other      :
*****************************************************************************/
VOS_UINT32 NV_PowerOffWriteNV(VOS_VOID)
{
    NV_REFERENCE_DATA_INFO_STRU        *pstNvIdInfo;
    VOS_UINT32                          ulTotalOffset;
    VOS_UINT32                          ulRslt;
    VOS_UINT32                          i;

    for(i=0; i< g_pstNVDataBuf->ulNvRefCount; i++)
    {
        /* Get NV ID */
        pstNvIdInfo = (NV_REFERENCE_DATA_INFO_STRU*)((VOS_CHAR*)g_pstNVDataBuf+(g_pstNVDataBuf->ulNvRefOffset + (i * sizeof(NV_REFERENCE_DATA_INFO_STRU))));

        /* 判断是否属于安全NV */
        if((VOS_YES == mdrv_crypto_check_sec()) && (g_ulCFDNvFileId == pstNvIdInfo->usFileId))
        {
            /* Forbid write seure NV file when seure version */
            PS_LOG1(WUEPS_PID_USIM, 0, PS_PRINT_ERROR,
                    "NV_PowerOffWriteNV:NV ID is secured:", pstNvIdInfo->usNvId);
            continue;
        }

        /* 获取低三位有效的权限 */
        if(NV_PRIORITY_LOW != NV_GET_AVAILABE_RIGHT_BITS(pstNvIdInfo->usProperty))
        {
            continue;
        }

        /*从缓存中读取NV数据*/
        /* 缓存中的偏移量 = XXNV.bin在缓存中的偏移量 + NVID在XXNV.bin中的偏移量 */
        ulTotalOffset = (g_astNvFileHandle[pstNvIdInfo->usFileId].ulOffset + pstNvIdInfo->ulNvOffset);

        ulRslt = NV_WriteContent(pstNvIdInfo->usFileId, pstNvIdInfo->ulNvOffset, ulTotalOffset,
                                 (VOS_VOID*)((VOS_CHAR *)g_pstNVDataBuf + ulTotalOffset),
                                 (pstNvIdInfo->usNvLength * pstNvIdInfo->ucModemNum));

        if(NV_OK != ulRslt)
        {
            PS_LOG(WUEPS_PID_USIM, 0, PS_PRINT_ERROR,
                    "NV_PowerOffWriteNV:write nv content fail.\n");
        }

    }

    return VOS_OK;
}


/*****************************************************************************
 函 数 名  : NV_Flush
 功能描述  : NV_Flush写入接口函数
 输入参数  :
 输出参数  :
 返 回 值  : VOS_UINT32
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2012年05月23日
    作    者   : d00212987
    修改内容   :  V7R1C50 Flashless PhaseII项目新增函数
*****************************************************************************/
VOS_UINT32 NV_Flush(VOS_VOID)
{
    VOS_UINT32                          ulRslt;

    /* 打开文件 */
    if ( VOS_OK != VOS_SmP(g_ulNVWriteSem, 0))
    {
        PS_LOG(WUEPS_PID_USIM, 0, PS_PRINT_ERROR, "NV_Flush:VOS_SmP failed.");
        return VOS_ERR;
    }

    /* 获取IPC硬件锁 */
    if(MDRV_OK != mdrv_ipc_sem_take(IPC_SEM_NVIM, NV_IPC_TIME_FOREVER))
    {
        /*lint -e534*/
        VOS_SmV(g_ulNVWriteSem);
        /*lint +e534*/
        return NV_SMP_ERR;
    }

    if ( VOS_ERR == NV_Open_ALL_NV_File() )
    {
        /* 释放IPC硬件锁 */
        mdrv_ipc_sem_give(IPC_SEM_NVIM);

        /*lint -e534*/
        VOS_SmV(g_ulNVWriteSem);
        /*lint +e534*/

        PS_LOG(WUEPS_PID_USIM, 0, PS_PRINT_ERROR, "NV_Flush:Open failed.");
        return VOS_ERR;
    }

    /* 遍历所有NV项 */
    ulRslt = NV_PowerOffWriteNV();
    if(VOS_OK != ulRslt)
    {
        PS_LOG(WUEPS_PID_USIM, 0, PS_PRINT_ERROR, "NV_Flush:write nv to file failed.");
    }

    if(VOS_ERR == NV_Close_ALL_NV_File())
    {
        /* 释放IPC硬件锁 */
        mdrv_ipc_sem_give(IPC_SEM_NVIM);

        /*lint -e534*/
        VOS_SmV(g_ulNVWriteSem);
        /*lint +e534*/

        PS_LOG(WUEPS_PID_USIM, 0, PS_PRINT_ERROR, "NV_Flush:close failed.");
        return VOS_ERR;
    }

    /* 释放IPC硬件锁 */
    mdrv_ipc_sem_give(IPC_SEM_NVIM);

    /*lint -e534*/
    VOS_SmV(g_ulNVWriteSem);
    /*lint +e534*/

    return ulRslt;
}

/*****************************************************************************
Function   : NV_Copy_Data_To_Memory
Description: copy NV data to memory
Input      :
Return     : Ok or Err.
Other      :
*****************************************************************************/
VOS_UINT32 NV_Copy_Data_To_Memory(VOS_VOID)
{
    VOS_UINT32                          i;
    VOS_UINT32                          ulFileId;
    FILE                               *fp;
    VOS_CHAR                            aucFilePath[NV_ABSLT_PATH_LEN] = {0};
    VOS_UINT32                          ulLength;
    VOS_UINT32                          ulOffset = 0;
    NV_FILE_LIST_INFO_STRU             *pstFileListInfo;

    g_pstNVDataBuf = (NV_CONTROL_FILE_INFO_STRU *)NV_DATA_BASE_ADDR;

    /* no flashless case */
    if (BSP_MODULE_SUPPORT == mdrv_misc_support_check(BSP_MODULE_TYPE_LOCALFLASH))
    {
        fp = NV_File_Open((VOS_CHAR*)g_aucNvCtrlFilePath, NV_FILE_OPEN_MODE_R);
    }
    else
    {
        fp = NV_File_Open((VOS_CHAR*)g_aucNvFilePath, NV_FILE_OPEN_MODE_RW);
    }

    if ( VOS_NULL_PTR == fp )
    {
        NV_Printf("NV_Copy_Data_To_Memory: Open NV Ctrl file is failed.\r\n");

        return NV_OPEN_FILE_FAIL;
    }

    /* flashless case:get the whole file len,other case: Get NV Ctrl File len*/
    NV_File_Seek(fp, 0, NV_FILE_SEEK_END);

    ulLength = (VOS_UINT32)NV_File_Tell(fp);

    /* 获取的文件超过分配的内存大小 */
    if (ulLength > NV_BUFFER_SIZE)
    {
        NV_File_Close(fp);

        NV_Printf("NV_Copy_Data_To_Memory:NV_FILE_TOO_LARGE\r\n");
        return NV_FILE_TOO_LARGE;
    }

    NV_File_Seek(fp, 0, NV_FILE_SEEK_SET);

    NV_SetAreaAccessable(NV_AREA_WRITABLE);

    /*lint -e662 */
    NV_File_Read((VOS_UINT8*)g_pstNVDataBuf, ulLength, 1, fp);
    /*lint +e662 */

    NV_File_Close(fp);

    /* 记录ctrlNV.BIN数据在内存BUFFER的偏移量及大小 */
    g_astNvFileHandle[0].ulOffset = ulOffset;
    g_astNvFileHandle[0].ulSize = g_pstNVDataBuf->ulCtrlFileSize;

    ulOffset += g_pstNVDataBuf->ulCtrlFileSize;

    pstFileListInfo = (NV_FILE_LIST_INFO_STRU *)((VOS_CHAR*)g_pstNVDataBuf + sizeof(NV_CONTROL_FILE_INFO_STRU));

    /* 将所有NV.bin 读入内存BUFFER中 */
    for(i = 0; i < g_pstNVDataBuf->ulFileListNum; i++)
    {
        ulFileId = pstFileListInfo[i].ulFileId;

        NV_Printf("NV_Copy_Data_To_Memory:FILE ID = %d\r\n", ulFileId);

        if(0 == ulFileId)
        {
            NV_SetAreaAccessable(NV_AREA_NO_WRITABLE);

            NV_Printf("NV_Copy_Data_To_Memory:NV_FILE_ID_ERR\r\n");

            return NV_FILE_ID_ERR;
        }

        /* 查找机要文件 FileID */
        if (VOS_OK == VOS_StrCmp((VOS_CHAR*)pstFileListInfo[i].aucFileName, (VOS_CHAR*)NV_FILE_CFD_NAME))
        {
            g_ulCFDNvFileId = ulFileId;
        }

        if ((NV_BACKUP_BUFFER_SIZE < pstFileListInfo[i].ulFileSize)
             ||(NV_BACKUP_BUFFER_SIZE < (ulOffset + pstFileListInfo[i].ulFileSize)))
        {
            NV_SetAreaAccessable(NV_AREA_NO_WRITABLE);

            NV_Printf("NV_Copy_Data_To_Memory: NV files are too large, ulOffset: %d, ulLength: %d.\r\n", ulOffset, ulLength);

            return NV_FILE_TOO_LARGE;
        }

        /* no flashless case */
        if (BSP_MODULE_SUPPORT == mdrv_misc_support_check(BSP_MODULE_TYPE_LOCALFLASH))
        {
            /* 拼文件的绝对路径 */
            NV_GetFileAbsltPath(g_aucNvFolderPath,
                                (VOS_CHAR*)(pstFileListInfo[i].aucFileName),
                                aucFilePath, NV_ABSLT_PATH_LEN);

            /* 打开XXXNVTable.BIN 文件  */
            fp = NV_File_Open(aucFilePath, NV_FILE_OPEN_MODE_R);

            if(VOS_NULL_PTR == fp)
            {
                NV_Printf("NV_Copy_Data_To_Memory: Open %s is failed.\r\n", aucFilePath);

                NV_SetAreaAccessable(NV_AREA_NO_WRITABLE);

                return NV_OPEN_FILE_FAIL;
            }

            NV_File_Seek(fp, 0, NV_FILE_SEEK_SET);

            /* 拷贝XXXNV.BIN数据到内存BUFFER中 */
            /*lint -e662 */
            NV_File_Read(((VOS_CHAR *)g_pstNVDataBuf + ulOffset), sizeof(VOS_CHAR), pstFileListInfo[i].ulFileSize, fp);
            /*lint +e662 */

            /* 关闭XXXNVTable.BIN 文件  */
            NV_File_Close(fp);
        }

        /* File id 不能大于20 */
        if (ulFileId > NV_BACKUP_FILE_MAX_NUM)
        {
            return NV_FILE_ID_ERR;
        }

        /* 记录XXXNV.BIN数据在内存BUFFER的偏移量 */
        g_astNvFileHandle[ulFileId].ulOffset   = ulOffset;

        /* 记录XXXNV.BIN数据在内存BUFFER的大小 */
        g_astNvFileHandle[ulFileId].ulSize     = pstFileListInfo[i].ulFileSize;

        ulOffset += g_astNvFileHandle[ulFileId].ulSize;
    }

    NV_SetAreaAccessable(NV_AREA_NO_WRITABLE);

    return NV_OK;
}

/*****************************************************************************
Function   : NV_GetMulitModemFlag
Description: NV Get MulitModem Flag.
Input      :
Return     : Ok or Err.
Other      :
*****************************************************************************/
VOS_UINT32 NV_CheckMulitModem(VOS_VOID)
{
    VOS_UINT8          ucFlag = 0;

#if (VOS_WIN32 == VOS_OS_VER)
    ucFlag = NV_OK;

    return ucFlag;

#else
    ucFlag = g_pstNVDataBuf->ucModemNum;

    NV_Printf("NV_CheckMulitModem: NV Supprot instance is :%d\r\n", g_pstNVDataBuf->ucModemNum);

#if ( FEATURE_MULTI_MODEM == FEATURE_ON )
    if((MODEM_ID_0 + 1) == ucFlag)
    {
        NV_Printf("NV_CheckMulitModem: FEATURE_MULTI_MODEM is ON, But Nv File Not\r\n");
        return NV_FILE_HANDLE_ERR;
    }

    return NV_OK;
#else
    if((MODEM_ID_0 + 1) != ucFlag)
    {
        NV_Printf("NV_CheckMulitModem: FEATURE_MULTI_MODEM is OFF, But Nv File Not\r\n");
        return NV_FILE_HANDLE_ERR;
    }

    return NV_OK;
#endif  /*( FEATURE_MULTI_MODEM == FEATURE_ON )*/
#endif  /*(VOS_WIN32 == VOS_OS_VER)*/
}


/*****************************************************************************
Function   : NV_Init
Description: NV init.
Input      :
Return     : Ok or Err.
Other      :
*****************************************************************************/
VOS_UINT32 NV_Init(VOS_VOID)
{
    VOS_UINT8                           aucMagicNum[NV_MAGIC_NUM_LEN];
    VOS_UINT8                           aucTemp[NV_MAGIC_NUM_LEN];
    VOS_CHAR                            aucVersionBuff[30]={0};
    VOS_UINT32                          ulSize;
    BSP_DDR_SECT_INFO_S                 stNVMemInfo;
    BSP_DDR_SECT_QUERY_S                stNVMemQuery;
    VOS_UINT32                          ulResult = NV_NOT_INIT;
    VOS_BOOL                            bIsSetResult = VOS_FALSE;

    g_ulNVInitStartSlice = mdrv_timer_get_normal_timestamp();

    /*lint -e534*/
    VOS_MemSet(aucMagicNum, NV_MAGIC_NUM, NV_MAGIC_NUM_LEN);

    VOS_MemSet(g_astResumFileHandle, 0, sizeof(g_astResumFileHandle));
    VOS_MemSet(g_astNvFileHandle, 0, sizeof(g_astNvFileHandle));
    /*lint +e534*/

    stNVMemQuery.enSectType = BSP_DDR_SECT_TYPE_NV;
    stNVMemQuery.ulSectSize = NV_BUFFER_SIZE;
    stNVMemQuery.enSectAttr = BSP_DDR_SECT_ATTR_NONCACHEABLE;

    if(MDRV_OK != mdrv_get_fix_ddr_addr(&stNVMemQuery, &stNVMemInfo))
    {
        NV_Printf("NV_Init: Ccpu mdrv_get_fix_ddr_addr Failed\r\n");

        mdrv_om_system_error(NV_INIT_ERROR, NV_GET_DRV_FIX_DDR_ADDR_FAIL,
                             0, (VOS_CHAR *)VOS_NULL_PTR, 0);

        return NV_INIT_FAIL;
    }

    g_ulNVMemAddr = (VOS_UINT_PTR)stNVMemInfo.pSectVirtAddr;    /*上层使用虚地址*/

    NV_Printf("----------------C Core NV_INIT begin------------------------\r\n");

    /* 创建NV写操作保护信号量 */
    if(VOS_OK != VOS_SmMCreate("NV", VOS_SEMA4_PRIOR | VOS_SEMA4_INVERSION_SAFE,
                                &g_ulNVWriteSem))
    {
        return VOS_ERR;
    }

    if(MDRV_OK != mdrv_ipc_sem_create(IPC_SEM_NVIM))
    {
        NV_Printf("NV_Init: Ccpu mdrv_ipc_sem_create Failed\r\n");

        return NV_INIT_FAIL;
    }

#if (FEATURE_ON == FEATURE_S_SKU_M_OPERATORS)

    /* SKU形态 运营商切换流程 */
    if(VOS_OK != NV_SkuSwitchProc())
    {
        NV_Printf("NV_Init:Sku Switch Proc fail.\r\n");
        return VOS_ERR;
    }
#endif

    /* 判断是否是C核单独复位 */
    /*lint -e534*/
    VOS_MemCpy(aucTemp, (VOS_VOID*)NV_MAGICNUM_ADDR, NV_MAGIC_NUM_LEN);  /*从share memory读取标志字节*/
    /*lint +e534*/

    if(VOS_OK == VOS_MemCmp(aucMagicNum, aucTemp, NV_MAGIC_NUM_LEN))    /*Ccpu的Nv项已经初始化成功*/
    {
        NV_BuildGlobalVar();
    }
    else
    {
        /* NV update process. */
        ulResult = NV_UpdateProc();

        if (NV_RESTORE_RUNNING == g_ulRestoreResult)
        {
            g_ulRestoreResult = ulResult;

            /* 可以更新NV恢复结果 */
            bIsSetResult = VOS_TRUE;

            if (NV_OK != ulResult)
            {
                PS_TURN_ON_UPDATE_VERSION_NVFAIL_LED();
            }
            else
            {
                PS_TURN_ON_UPDATE_VERSION_SUCCESS_LED();
            }
        }

        if (NV_OK != ulResult)
        {
            VOS_SmDelete(g_ulNVWriteSem);
            mdrv_om_system_error(NV_INIT_ERROR, (VOS_INT)PS_FILE_ID_NVIM_FUNCTION_C,
                                 (VOS_INT)__LINE__, (VOS_CHAR *)VOS_NULL_PTR, 0);
            return VOS_ERR;
        }

#if (FEATURE_ON == FEATURE_S_SKU_M_OPERATORS)

        /* 切换标记更新,失败打印log */
        if (VOS_OK != NV_SkuUpdateSwitchFlag())
        {
            NV_Printf("NV_Init:update Switch falg fail.\r\n");
        }

#endif

        if(NV_OK != NV_CheckMulitModem())
        {
            NV_Printf("NV_Init: Ccpu Check NV File Failed\r\n");

            mdrv_om_system_error(NV_INIT_ERROR, (VOS_INT)PS_FILE_ID_NVIM_FUNCTION_C,
                                 (VOS_INT)__LINE__, (VOS_CHAR *)VOS_NULL_PTR, 0);

            return NV_INIT_FAIL;
        }


        /* Write magic num to inform NV is ready. */
        NV_SetAreaAccessable(NV_AREA_WRITABLE);

        /*lint -e534*/
        VOS_MemSet((VOS_VOID*)NV_MAGICNUM_ADDR, NV_MAGIC_NUM, NV_MAGIC_NUM_LEN);
        /*lint +e534*/

        NV_SetAreaAccessable(NV_AREA_NO_WRITABLE);

        /* 通知A核C核NV初始化完毕 */
        mdrv_ipc_int_send(IPC_CORE_ACPU, (IPC_INT_LEV_E)IPC_ACPU_INT_SRC_CCPU_NVIM);
    }

    NV_Printf("\r\n----------------C Core NV_INIT end, Success------------------------\r\n");

    /* Write NV version. */
    ulSize = sizeof(g_pstNVDataBuf->usVersionInfo);

    /*lint -e534*/
    VOS_MemCpy(aucVersionBuff, (VOS_CHAR *)&(g_pstNVDataBuf->usVersionInfo), ulSize);

    VOS_MemCpy(aucVersionBuff+ulSize, g_pstNVDataBuf->aulTimeTag,
        sizeof(g_pstNVDataBuf->aulTimeTag));
    /*lint +e534*/

    mdrv_ver_memberctrl((VOS_INT8*)aucVersionBuff, VER_MAX_LENGTH, VER_NV, VERIONWRITEMODE);

    g_ulNVInitEndSlice = mdrv_timer_get_normal_timestamp();

    /* 将NV读写接口注册给底软使用 */
    DRV_MSP_PROC_REG(OM_READ_NV_PROC, (BSP_MspProc)NV_ReadEx);
    DRV_MSP_PROC_REG(OM_WRITE_NV_PROC, (BSP_MspProc)NV_WriteEx);

    if (VOS_TRUE == bIsSetResult)
    {
        /* Input the update result to DRV. */
        DRV_UPGRADE_NV_SET_RESULT((VOS_INT)ulResult);
        NV_Printf("NV_Init:nv update Result is %d \r\n",ulResult);
    }

    /* 检测是否开启NV写操作记录跟踪 */
    ulResult = NV_ReadEx(MODEM_ID_0, en_NV_Item_Write_Slice_Record_Flag, (VOS_VOID*)&g_ulRecordNvFlag, sizeof(g_ulRecordNvFlag));
    if (NV_OK != ulResult)
    {
        g_ulRecordNvFlag = 0;
    }

    return VOS_OK;
}

/*****************************************************************************
Function   : NV_SpecialNvIdBackup
Description: Backup particular NV data to backup zone
Input      : VOS_UINT16 usID -> NV ID
             VOS_VOID *pItem -> content of NV Id
             VOS_UINT32 ulLength ->NV length
Return     : Ok or Err.
Other      :
Auth       : x51137
*****************************************************************************/
VOS_UINT32 NV_SpecialNvIdBackup(VOS_UINT16 usID,VOS_VOID *pItem,VOS_UINT32 ulLength)
{
    NV_ID_RETUEN_INFO_STRU              stNvIdReturnInfo;
    VOS_UINT32                          ulOffset;
    VOS_CHAR                           *pcTemp;
    VOS_UINT32                          ulResult;

    ulResult = NV_NvIdCheck(MODEM_ID_0, usID, 0, pItem, ulLength, &stNvIdReturnInfo);

    if(NV_OK != ulResult)
    {
        PS_LOG(WUEPS_PID_USIM, 0, PS_PRINT_ERROR,
                "NV_SpecialNvIdBackup:NV ID check fail.\n");
        return ulResult;
    }

    /* NV数据的起始地址 */
    pcTemp = ((VOS_CHAR*)g_pstNVDataBuf + stNvIdReturnInfo.ulTotalOffset);

    /* 计算相对于备份区的起始地址 */
    ulOffset = (VOS_UINT32)pcTemp - (VOS_UINT32)g_pstNVDataBuf;

    /*call drv interface write function*/
    if(VOS_OK != DRV_NV_FLASH_WRITE((VOS_UCHAR*)pItem, ulOffset, ulLength))
    {
        return NV_WRITE_FLASH_FAIL;
    }

    return NV_OK;
}

/* NV模块下移，不再支持发消息写 */
#if 0
/*****************************************************************************
 函 数 名  : NvimFL_MsgProc
 功能描述  : 处理FLUSH的消息
 输入参数  : MsgBlock

 输出参数  : 无
 返 回 值  : 无
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2012年05月23日
    作    者   : w00184875
    修改内容   : V7R1C50 Flashless PhaseII项目新增函数

*****************************************************************************/
VOS_VOID NvimFL_MsgProc(MsgBlock* pstMsg)
{
    NVIM_FLUSH_MSG_STRU                *pstNvFlushMsg;

    /* 判断指针是否为空 */
    if (VOS_NULL_PTR == pstMsg)
    {
        PS_LOG(WUEPS_PID_NVIM_FLUSH, 0, PS_PRINT_ERROR, "NvimFL_MsgProc:pMsg is empty.");
        return;
    }

    /* 判断消息原语 */
    pstNvFlushMsg = (NVIM_FLUSH_MSG_STRU*)pstMsg;

    switch (pstNvFlushMsg->ulSenderPid)
    {
        case WUEPS_PID_NVIM_FLUSH:
            if (NV_FLUSH_NOTIFY_IND == pstNvFlushMsg->ulMsgName)
            {
                NV_Flush();
            }
            else
            {
                PS_LOG1(WUEPS_PID_NVIM_FLUSH, 0, PS_PRINT_ERROR,
                        "NvimFL_MsgProc: SenderPid is WUEPS_PID_NVIM_FLUSH, Msg Name (value:%d) is unknown.",
                        (VOS_INT32)pstNvFlushMsg->ulMsgName);
            }

            break;
        default:
            PS_LOG2(WUEPS_PID_NVIM_FLUSH, 0, PS_PRINT_ERROR,
                "NvimFL_MsgProc: SenderPid: %d, Msg Name (value:%d) is unknown.",
                (VOS_INT32)pstNvFlushMsg->ulSenderPid, (VOS_INT32)pstNvFlushMsg->ulMsgName);
            break;
    }

    return;
}

/*****************************************************************************
 函 数 名  : NvimFLInit
 功能描述  : 读取flush阈值
 输入参数  : 无

 输出参数  : 无
 返 回 值  : VOS_UINT32
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2012年05月23日
    作    者   : w00184875
    修改内容   : V7R1C50 Flashless PhaseII项目新增函数

*****************************************************************************/
VOS_UINT32 NvimFLInit(VOS_VOID)
{
    /* 读取NV项中的flush阈值 */
    if (NV_OK != NV_Read(en_NV_Item_NV_PRIORITY_THRESHOLD,
                         &g_stNvPriThreshold,
                         sizeof(NV_PRIORITY_THRESHOLD_STRU)))
    {
        /* LOG */
        PS_LOG(WUEPS_PID_NVIM_FLUSH, 0, PS_PRINT_ERROR, "NvimFLInit:NV_Read is failed.");
        return VOS_ERR;
    }

    /* 初始化阈值 */
    /*lint -e534*/
    VOS_MemSet(&g_stNvPriThresholdCur, 0, sizeof(NV_PRIORITY_THRESHOLD_STRU));
    /*lint +e534*/

    return VOS_OK;
}

/*****************************************************************************
 函 数 名  : NvimFLPidInit
 功能描述  : NVIM_FLUSH PID初始化函数
 输入参数  : VOS_INIT_PHASE_DEFINE

 输出参数  : 无
 返 回 值  : VOS_UINT32
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2012年05月23日
    作    者   : w00184875
    修改内容   : V7R1C50 Flashless PhaseII项目新增函数

*****************************************************************************/
VOS_UINT32 NvimFLPidInit(enum VOS_INIT_PHASE_DEFINE ip)
{
    switch ( ip )
    {
        case VOS_IP_LOAD_CONFIG:
            return NvimFLInit();

        default:
            break;
    }

    return VOS_OK;
}

/*****************************************************************************
 函 数 名  : NVIM_FLUSH_FID_Init
 功能描述  : NVIM_FLUSH任务初始化函数
 输入参数  : VOS_INIT_PHASE_DEFINE

 输出参数  : 无
 返 回 值  : VOS_UINT32
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2012年05月23日
    作    者   : w00184875
    修改内容   : V7R1C50 Flashless PhaseII项目新增函数

*****************************************************************************/
VOS_UINT32 NVIM_FLUSH_FID_Init(enum VOS_INIT_PHASE_DEFINE ip)
{
    VOS_UINT32                          ulRslt;

    switch ( ip )
    {
        case VOS_IP_LOAD_CONFIG:
        {
            /* 注册PID消息处理函数 */
            ulRslt = VOS_RegisterPIDInfo(WUEPS_PID_NVIM_FLUSH,
                                         (Init_Fun_Type)NvimFLPidInit,
                                         (Msg_Fun_Type)NvimFL_MsgProc);
            if (VOS_OK != ulRslt)
            {
               return VOS_ERR;
            }

            /* 注册任务优先级 */
            ulRslt = VOS_RegisterTaskPrio(WUEPS_FID_NVIM_FLUSH, NV_FLUSH_TASK_PRIORITY_LOW);

            if (VOS_OK != ulRslt)
            {
               return VOS_ERR;
            }

            break;
        }
        default:
            break;
    }

    return VOS_OK;

}
#endif

/*****************************************************************************
Function   : NV_GetOnlyNVIdList
Description: 读取所有NV ID
Input      :
Return     : Ok or Err.
Other      :
*****************************************************************************/
VOS_VOID NV_GetOnlyNVIdList(VOS_UINT16 *pusNvIdList, VOS_UINT32 *pulCfdNum)
{
    NV_REFERENCE_DATA_INFO_STRU        *pstSrc;
    VOS_UINT32                          i;
    VOS_UINT32                          ulOffset;
    VOS_UINT16                         *pucDest;
    VOS_UINT32                          ulCfdNum = 0;

    ulOffset = sizeof(NV_CONTROL_FILE_INFO_STRU)
                + (sizeof(NV_FILE_LIST_INFO_STRU) * (g_pstNVDataBuf->ulFileListNum));

    pucDest  = pusNvIdList;
    pstSrc   = (NV_REFERENCE_DATA_INFO_STRU *)((VOS_CHAR *)g_pstNVDataBuf + ulOffset);

    for (i = 0; i < g_pstNVDataBuf->ulNvRefCount; i++)
    {
/*lint -e40 *//*加入vxworks的头问题引入lint问题，走读人徐铖*/
        if(g_ulCFDNvFileId == pstSrc->usFileId)
        {
            ulCfdNum++;

            pstSrc++;

            continue;   /*机要数据NV项不进行恢复*/
        }
/*lint +e40 *//*加入vxworks的头问题引入lint问题，走读人徐铖*/

        *pucDest++ = pstSrc->usNvId;
        pstSrc++;
    }

    *pulCfdNum = ulCfdNum;

    return ;
}

/*****************************************************************************
Function   : NV_RestoreAll
Description: Resstore manufacture and user NV data
Input      :
Return     : Ok or Err.
Other      :
*****************************************************************************/
VOS_UINT32 NV_RestoreAll(VOS_VOID)
{
    return NV_OK;
}


/*****************************************************************************
Function   : NV_RestoreManufacture
Description: Restore manufacture NV data
Input      :
Return     : Ok or Err.
Other      :
*****************************************************************************/
VOS_UINT32 NV_RestoreManufacture(VOS_VOID)
{
    return NV_OK;
}

/*****************************************************************************
Function   : NV_RestoreResult
Description: Return restore NV data result
Input      :
Return     : Ok or Err.
Other      :
*****************************************************************************/
VOS_UINT32 NV_RestoreResult(VOS_VOID)
{
    VOS_UINT32 ulReturn;

    ulReturn   = g_ulRestoreResult;

    return ulReturn;
}

/*****************************************************************************
Function   : NV_CheckFactoryVer
Description: Check the current version is factory version.
Input      : void
Return     : Ok or Err.
Other      :
*****************************************************************************/
VOS_UINT32 NV_CheckFactoryVer(VOS_VOID)
{
    VOS_UINT32                          ulResult;

    /* If the NV-Use directory is not exist, and the backup-zone is incorrect,
        the board is factory version. */
    if (NV_OK != NV_File_Exist((VOS_CHAR*)g_acNvUseDir, VOS_NULL_PTR))
    {
        ulResult = (VOS_UINT32)NV_Mkdir((VOS_CHAR*)g_acNvUseDir);

        if (NV_OK != ulResult)
        {
            return ulResult;
        }
    }

    if (NV_OK != NV_BackupCheck())
    {
        NV_File_Create((VOS_CHAR*)g_acNvUseDir, (VOS_CHAR*)g_acNvBackupFile);
    }

    return NV_OK;
}

/*****************************************************************************
Function   : NV_BackupProc
Description: NV's backup process.
Input      : void
Return     : Ok or Err.
Other      :
*****************************************************************************/
VOS_UINT32 NV_BackupProc(VOS_VOID)
{
    VOS_UINT32                          ulResult;

    /* Enter update procedure when NVUpdate.bin is exist in NV-Update zone. */
    if (NV_OK != NV_File_Exist((VOS_CHAR*)g_acNvUpdateDir, (VOS_CHAR*)g_acNvUpdateFile))
    {
        return NV_OK;
    }

    g_ulRestoreResult = NV_RESTORE_RUNNING;

    NV_Printf("\r\nNV_BackupProc is begining.\r\n");

    /* Init NV-Update zone nv files into memory. */
    /* Add by z00100318 for V7R1C50 Flashless PhaseI项目 begin */
    ulResult = NV_Copy_Data_To_Memory();

    if ((NV_OK != ulResult) && (NV_OPEN_FILE_FAIL != ulResult))        /* 将NV数据读进内存BUFFER中 */
    {
        return ulResult;
    }

    /* 确保后面不再进行Backup操作*/
    if (NV_OPEN_FILE_FAIL == ulResult)
    {
        NV_File_Remove((VOS_CHAR*)g_acNvUseDir, (VOS_CHAR*)g_acNvBackupFile);
    }

    /* Add by z00100318 for V7R1C50 Flashless PhaseI项目 end */
    PS_TURN_ON_UPDATE_VERSION_LED();

    /* Check NV security file in NV-Update zone.*/
    if (NV_OK != NV_File_Check((VOS_CHAR*)g_acNvUpdateDir, (VOS_CHAR*)g_acNvCfdFile))
    {
        NV_Printf("NV_BackupProc: NV_File_Check %s%s is failed.\r\n", g_acNvUpdateDir, g_acNvCfdFile);

        return NV_UPDATE_SEC_FILE_ERR;
    }

    /* Copy NV-Update zone files to NV-Default zone. */
    if (NV_OK != NV_Xcopy((VOS_CHAR*)g_acNvUpdateDir, (VOS_CHAR*)g_acNvDefaultDir))
    {
        NV_Printf("NV_BackupProc: NV_Xcopy %s to %s is failed.\r\n", g_acNvUpdateDir, g_acNvDefaultDir);

        return NV_XCOPY_DEF_FAIL;
    }

    /* Last NV restore is successful when NV-Use zone's backup file is exist. */
    if (NV_OK == NV_File_Exist((VOS_CHAR*)g_acNvUseDir, (VOS_CHAR*)g_acNvBackupFile))
    {
        NV_Printf("NV_BackupProc: Execute backup operation.\r\n");

        ulResult = NV_ExNoBackup();
        if (NV_OK != ulResult)
        {
            NV_Printf("NV_BackupProc:nv Backup fail. \r\n");
            return ulResult;
        }

        NV_File_Remove((VOS_CHAR*)g_acNvUseDir, (VOS_CHAR*)g_acNvBackupFile);
        NV_Printf("\r\nNV_BackupProc is end.\r\n");
    }
    else
    {
        /* Check the current version is factory version. */
        ulResult = NV_CheckFactoryVer();

        if (NV_OK != ulResult)
        {
            NV_Printf("NV_BackupProc:NV_CheckFactoryVer fail. \r\n");
            return ulResult;
        }
    }

    /* Delete all xml files */
    NV_DeleteFilesBySuffix((VOS_CHAR*)g_aucNvFolderPath, ".xml");

    /* Copy NV-Update zone files to NV-Use zone. */
    if (VOS_OK != NV_Xcopy((VOS_CHAR*)g_acNvUpdateDir, (VOS_CHAR*)g_acNvUseDir))
    {
        NV_Printf("NV_BackupProc: NV_Xcopy %s to %s is failed.\r\n", g_acNvUpdateDir, g_acNvUseDir);

        return NV_XCOPY_USE_FAIL;
    }

    NV_File_Remove((VOS_CHAR*)g_acNvUpdateDir, (VOS_CHAR*)g_acNvUpdateFile);

    return NV_OK;
}

/*****************************************************************************
Function   : NV_RestoreProc
Description: NV's restoring process.
Input      : bIsDefault - VOS_TRUE: Resume the factory setting.
                          VOS_FALSE:Others
Return     : Ok or Err.
Other      :
*****************************************************************************/
VOS_UINT32 NV_RestoreProc(NVIM_RESTORE_TYPE_ENUM_UINT32 enRestoreType,
                          VOS_BOOL                      bIsDefault,
                          VOS_BOOL                     *pbIsCreatefile)
{
    VOS_UINT32                          ulResult;
    VOS_UINT32                          ulRslt1;
    VOS_UINT32                          ulRslt2 = VOS_OK;
    VOS_UINT32                          ulRslt3 = VOS_OK;

    if(NVIM_RESTORE_BASE_SPACE == enRestoreType)
    {
        if (NV_OK == NV_File_Exist((VOS_CHAR*)g_acNvUseDir, (VOS_CHAR*)g_acNvBackupFile))
        {
            return NV_OK;
        }

        NV_Printf("NV_RestoreProc Def is begining. restore type is %d.\r\n", enRestoreType);

        /* Def resume old NV file */
        ulResult = NV_ResumeNvFile();

    }
    else
    {
        NV_Printf("NV_RestoreProc Ext is begining. restore type is %d.\r\n", enRestoreType);

        /* Ext resume old NV file */
        ulResult =  NV_ResumeBackupRead(NVIM_BACKUP_READ_EXT_SPACE);
    }

    if(NV_OK != ulResult)
    {
        /* Resume fail */
        NV_Printf("NV_RestoreProc:Resume old NV file fail. restore type is %d.\r\n", enRestoreType);
        NV_Del_Old();

        return ulResult;
    }

    NV_Printf("NV_RestoreProc:The Old Flag is %d , New Flag is %d. \r\n", g_pstNVMemoryFileInfo->ucModemNum, g_pstNVDataBuf->ucModemNum);

    /* 判断旧实例数和新实例数是否相同 */
    if(g_pstNVDataBuf->ucModemNum != g_pstNVMemoryFileInfo->ucModemNum)
    {
        NV_Printf("NV_RestoreProc:The Old Flag not euqal New Flag, Resume Flow break offrestore type is %d.\r\n", enRestoreType);

        NV_Del_Old();

        return NV_OK;
    }

    ulRslt1 = NV_ResumeNvData(NV_GetResumeNvIdNum(NV_MANUFACTURE_ITEM),
                                         g_ausNvResumeManufactureIdList);

#if (FEATURE_ON == FEATURE_S_SKU_M_OPERATORS)

    ulRslt2     = NV_SkuRestoreNvFile(bIsDefault);
    if (VOS_OK != ulRslt2)
    {
        /* Log 记录 */
        NV_Printf("NV_RestoreProc: NV_SkuRestoreNvFile fail return %d.\r\n", ulRslt2);
    }

#else

    /* Don't resume user's NV in default process. */
    if (VOS_TRUE != bIsDefault)
    {
        ulRslt2 = NV_ResumeNvData(NV_GetResumeNvIdNum(NV_USER_ITEM),
                                         g_ausNvResumeUserIdList);
    }

#endif
    /* 值为VOS_NO表示为非安全版本 */
    if( VOS_NO == mdrv_crypto_check_sec())
    {
        ulRslt3 = NV_ResumeNvData(NV_GetResumeNvIdNum(NV_SECURE_ITEM),
                                         g_ausNvResumeSecureIdList);
    }

    if((VOS_OK == ulRslt1) && (VOS_OK == ulRslt2) && (VOS_OK == ulRslt3))
    {
        if (VOS_OK == DRV_BACKUP_SYS_FILE())
        {
            /* Restore success */
            NV_Del_Old();

            *pbIsCreatefile = VOS_TRUE;

            NV_Printf("NV_RestoreProc is end, restore type is %d.\r\n", enRestoreType);
            return NV_OK;
        }
    }

    NV_Del_Old();

    return NV_RESUME_NV_FAIL;
}

/*****************************************************************************
Function   : NV_UpdateProc
Description: NV_UpdateProc.
Input      :
Return     : Ok or Err.
Other      :
*****************************************************************************/
VOS_UINT32 NV_UpdateProc(VOS_VOID)
{
    VOS_UINT32                          ulResult;
    VOS_BOOL                            bIsCreatefile = VOS_FALSE;
    VOS_BOOL                            bIsDecodeXml  = VOS_FALSE;

    /* Enter NV backup process. */
    ulResult = NV_BackupProc();

    if (NV_OK != ulResult)
    {
        PS_TURN_ON_UPDATE_VERSION_FAIL_LED();

        return ulResult;
    }

    /* Check if NV-Use zone security file is corret. */
    if (VOS_OK != NV_File_Check((VOS_CHAR*)g_acNvUseDir, (VOS_CHAR*)g_acNvCfdFile))
    {
        NV_Printf("NV_BackupProc: NV_File_Check %s%s is failed.\r\n", g_acNvUseDir, g_acNvCfdFile);

        return NV_USE_SEC_FILE_ERR;
    }

    ulResult = NV_Copy_Data_To_Memory();

    if (NV_OK != ulResult)          /* 将NV数据读进内存BUFFER中 */
    {
        NV_Printf("NV_UpdateProc:NV_Copy_Data_To_Memory fail. \r\n");
        return ulResult;
    }

    XML_DecodeMain(&bIsDecodeXml);

    /* Enter NV restore process. */
    ulResult = NV_RestoreProc(NVIM_RESTORE_BASE_SPACE, VOS_FALSE, &bIsCreatefile);
    if (NV_OK != ulResult)
    {
        NV_Printf("NV_UpdateProc:NV_RestoreProc fail. return %d\r\n", ulResult);
        return ulResult;
    }

    /* NV初始化前面NV所有操作，只写入到ddr,靠NV_FlushDdrToFile刷入文件 */
    ulResult = NV_FlushDdrProc(bIsCreatefile, bIsDecodeXml);
    if (NV_OK != ulResult)
    {
        NV_Printf("NV_UpdateProc:NV_FlushDdr fail. return %d\r\n", ulResult);
    }

    return NV_OK;
}

/*****************************************************************************
 Prototype       : NV_RestoreManufactureProc
 Description     : 恢复出厂设置
 Input           : enRestoreType 恢复类型
 Output          : None
 Return Value    : VOS_UINT32

 History         : ---
 Date         :
 Author       :
 Modification : Created function
 *****************************************************************************/
VOS_UINT32 NV_RestoreManufactureProc(NVIM_RESTORE_TYPE_ENUM_UINT32 enRestoreType)
{
    VOS_UINT32                          ulResult;
    VOS_BOOL                            bIsCreatefile = VOS_FALSE;
    VOS_BOOL                            bIsDecodeXml  = VOS_FALSE;

    /* Firstly, need to check NV-Default zone is correct. */
    if (NV_OK != NV_File_Exist((VOS_CHAR*)g_acNvDefaultDir, (VOS_CHAR*)g_acNvUpdateFile))
    {
        return NV_DEFAULT_NOT_EXIST;
    }

    NV_Printf("NV_RestoreManufactureProc is begining. restore type is %d.\r\n", enRestoreType);

    /* 恢复默认出厂设置 */
    if(NVIM_RESTORE_BASE_SPACE == enRestoreType)
    {
        /* Make sure last update is correct. */
        if (NV_OK == NV_File_Exist((VOS_CHAR*)g_acNvUseDir, (VOS_CHAR*)g_acNvBackupFile))
        {
            NV_Printf("NV_RestoreManufactureProc: Execute default operation.\r\n");

            ulResult = NV_ExNoBackup();

            if (NV_OK != ulResult)
            {
                return ulResult;
            }

            NV_File_Remove((VOS_CHAR*)g_acNvUseDir, (VOS_CHAR*)g_acNvBackupFile);
        }
    }

    /* Copy NV-Update zone files to NV-Default zone. */
    if (NV_OK != NV_Xcopy((VOS_CHAR*)g_acNvDefaultDir, (VOS_CHAR*)g_acNvUseDir))
    {
        NV_Printf("NV_RestoreManufactureProc: NV_Xcopy %s to %s is failed.\r\n", g_acNvDefaultDir, g_acNvUseDir);

        return NV_XCOPY_USE_FAIL;
    }

    /* Read NV-Use zone files to memory. */
    ulResult = NV_Copy_Data_To_Memory();

    if (NV_OK != ulResult)          /* 将NV数据读进内存BUFFER中 */
    {
        return ulResult;
    }

    XML_DecodeMain(&bIsDecodeXml);

    /* Enter NV restoring process. */
    ulResult = NV_RestoreProc(enRestoreType, VOS_TRUE, &bIsCreatefile);

    if (NV_OK != ulResult)
    {
        NV_Printf("NV_RestoreManufactureProc:NV_RestoreProc fail. return %d\r\n", ulResult);

        return ulResult;
    }

    /* NV初始化前面NV所有操作，只写入到ddr,靠NV_FlushDdrToFile刷入文件 */
    ulResult = NV_FlushDdrProc(bIsCreatefile, bIsDecodeXml);
    if (NV_OK != ulResult)
    {
        NV_Printf("NV_RestoreManufactureProc:NV_FlushDdr fail. return %d\r\n", ulResult);
    }
    return NV_OK;
}

/*****************************************************************************
 Prototype       : NV_RestoreManufactureDefault
 Description     : 恢复所有NV项为出厂设置
 Input           : None
 Output          : None
 Return Value    : VOS_UINT32

 History         : ---
 Date         :
 Author       :
 Modification : Created function
 *****************************************************************************/
VOS_UINT32 NV_RestoreManufactureDefault(VOS_VOID)
{
    VOS_UINT32                          ulRest;

    ulRest = NV_RestoreManufactureProc(NVIM_RESTORE_BASE_SPACE);
    if(NV_OK != ulRest)
    {
        NV_Printf("NV_RestoreManufactureDefault: nv restore default fail! %d\r\n", ulRest);
        return ulRest;
    }

    return NV_OK;
}

/*****************************************************************************
 Prototype       : NV_RestoreManufactureExt
 Description     : 只提供对外AT^NVMANUFACTUREEXT命令使用，强制从扩展分区恢复出厂设置
 Input           : None
 Output          : None
 Return Value    : VOS_UINT32

 History         : ---
 Date         :
 Author       :
 Modification : Created function
 *****************************************************************************/
VOS_UINT32 NV_RestoreManufactureExt(VOS_VOID)
{
    VOS_UINT32                          ulRest;

    ulRest = NV_BackupCheckRead(NVIM_BACKUP_READ_EXT_SPACE);
    if(NV_OK != ulRest)
    {
        NV_Printf("NV_RestoreManufactureExt:There is no NV Ex backup data.\n");
        return ulRest;
    }

    NV_File_Remove((VOS_CHAR*)g_acNvUseDir, (VOS_CHAR*)g_acNvBackupFile);

    ulRest = NV_RestoreManufactureProc(NVIM_RESTORE_EXT_SPACE);
    if(NV_OK != ulRest)
    {
        NV_Printf("NV_RestoreManufactureExt: nv restore ext fail! %d\r\n", ulRest);
        return ulRest;
    }
    return NV_OK;
}

/*****************************************************************************
Function   : NV_QueryRestoreResult
Description: Return restore NV data result & NV's ID which is 4
Input      :
Return     : Ok or Err.
Other      : used by V3R2 AT only
*****************************************************************************/
VOS_UINT32 NV_QueryRestoreResult(VOS_VOID)
{
    VOS_INT      lLockValue;
    VOS_UINT32   ulReturn;

    lLockValue = VOS_SplIMP();
    ulReturn   = g_ulRestoreResult;
    VOS_Splx(lLockValue);

    return ulReturn;
}

#if (FEATURE_ON == FEATURE_BROWSER_NV_FILE_IMEI_PROTECT)
/*****************************************************************************
 函 数 名  : NV_FileDirCmp
 功能描述  : 文件所在文件夹路路径比较
 输入参数  : pcNvFileDir  : NV所在文件夹路径
             pcFilePath   : 待判断文件路径，确认是否属于NV文件路径

 输出参数  : 无
 返 回 值  : VOS_BOOL

 修改历史      :
  1.日    期   : 2013年5月7日
    作    者   : d00212987
    修改内容   : FileBrowser 访问modem文件需IMEI验证 新增
*****************************************************************************/
VOS_BOOL NV_FileDirCmp(VOS_CHAR  *pcNvFileDir, VOS_CHAR  *pcFilePath)
{
    VOS_CHAR                            acDilms[] = "/";

#if ( VOS_WIN32 == VOS_OS_VER )
    acDilms[0] = '\\';
#endif

    if (VOS_StrLen(pcNvFileDir) >= VOS_StrLen(pcFilePath))
    {
        NV_Printf("#info:NV_FileDirCmp: Dir is %s. filePath is %s.\r\n", pcNvFileDir, pcNvFileDir);
        return VOS_FALSE;
    }

    if(VOS_OK == VOS_StrNCmp(pcNvFileDir, pcFilePath, VOS_StrLen(pcNvFileDir)))
    {
        /* 增加保护 防止
            NvimUse       ---- 是NV文件夹
            NvimUseTemp   ---- 不是NV文件夹
            会把NvimUseTemp 也当成NV文件夹, 判断文件夹路径最后是否是 "/"
         */
        if(VOS_OK == VOS_MemCmp(pcFilePath + VOS_StrLen(pcNvFileDir), acDilms, VOS_StrLen(acDilms)))
        {
            return VOS_TRUE;
        }
    }
    return VOS_FALSE;
}

static NV_DIR_PATH_STRU g_astNvDirCPathTbl[] =
{
#if (FEATURE_ON == FEATURE_S_SKU_M_OPERATORS)
    /* 涉及SKU形态 sku 目录都当做NV文件 */
    g_acNvSkuDir,
#endif
    g_acNvUseDir,
    g_acNvUpdateDir,
    g_acNvDefaultDir
};

/*****************************************************************************
 函 数 名  : NV_CheckNVFile
 功能描述  : 根据文件路径判断是否属于NV 相关文件
 输入参数  : pcFilePath   : 文件路径

 输出参数  : 无
 返 回 值  : VOS_BOOL

 修改历史      :
  1.日    期   : 2013年5月7日
    作    者   : d00212987
    修改内容   : FileBrowser 访问modem文件需IMEI验证 新增
*****************************************************************************/
VOS_BOOL NV_CheckNVFile(VOS_CHAR  *pcFilePath)
{
    VOS_UINT32                          ulIndex;
    VOS_UINT32                          ulTotalNum;
    VOS_BOOL                            bResult = VOS_FALSE;

    ulTotalNum = sizeof(g_astNvDirCPathTbl)/sizeof(NV_DIR_PATH_STRU);

    for (ulIndex = 0; ulIndex < ulTotalNum; ulIndex++)
    {
        /* 判断属于NV 文件 */
        if(VOS_TRUE == NV_FileDirCmp(g_astNvDirCPathTbl[ulIndex].pDirPath, pcFilePath))
        {
            bResult = VOS_TRUE;
            break;
        }
    }
    return bResult;
}
#endif

#ifdef __cplusplus
    #if __cplusplus
        }
    #endif
#endif


