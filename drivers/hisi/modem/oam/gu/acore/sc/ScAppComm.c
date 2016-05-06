

/******************************************************************************

                  版权所有 (C), 2001-2012, 华为技术有限公司

 ******************************************************************************
  文 件 名      : ScAppComm.c
  版 本 号      : 初稿
  作    者      : d00212987
  生成日期      : 2015年08月10日
  最近修改      :
  功能描述      : 该C文件给出了ScComm模块的实现
  函数列表      :
  修改历史      :
  1.日    期    : 2015年08月10日
    作    者    : d00212987
    修改内容    : 创建文件

******************************************************************************/
/*****************************************************************************
  1 头文件包含
*****************************************************************************/
#include "mdrv.h"
#include "ScInterface.h"
#include "ScCommCtx.h"


#ifdef __cplusplus
  #if __cplusplus
  extern "C"{
  #endif
#endif

/*lint -e767 修改人:d00212987;原因:Log打印 */
#define    THIS_FILE_ID        PS_FILE_ID_SC_APP_COMM_C
/*lint +e767 修改人:d00212987;*/

#define SC_IMEI_LOG_FILE_PATH   "/modem_log/OAM_IMEI_ACORE_Log.bin"

#if (VOS_WIN32 != VOS_OS_VER)
/*****************************************************************************
函 数 名  : SC_COMM_CloseAllFile
功能描述  : SC关闭非空文件
输入参数  :

输出参数  :无
返 回 值  :

被调函数  :
修订记录  :
1.日    期   : 2014年6月5日
  作    者   : d00212987
  修改内容   : SC备份到底软NV备份的扩展分区
*****************************************************************************/
VOS_VOID SC_COMM_CloseAllFile(FILE *fp[SC_SECRET_FILE_TYPE_BUTT*2])
{
    VOS_UINT32                          i;

    for (i=0;i<SC_SECRET_FILE_TYPE_BUTT*2;i++)
    {
        if (VOS_NULL_PTR != fp[i])
        {
             /*lint -e534*/
             mdrv_file_close(fp[i]);
             /*lint +e534*/
        }
        else
        {
          continue;
        }
    }
    return;
}

/*****************************************************************************
函 数 名  : SC_COMM_Backup
功能描述  : SC文件备份到底软SC备份区
输入参数  :

输出参数  : 无
返 回 值  : VOS_UINT32

被调函数  :
修订记录  :
1.日    期   : 2014年6月27日
  作    者   : d00212987
  修改内容   : SC备份到底软NV备份的扩展分区
*****************************************************************************/
VOS_UINT32 SC_COMM_Backup(VOS_VOID)
{
    FILE                               *fp[SC_SECRET_FILE_TYPE_BUTT*2] = {VOS_NULL_PTR};
    SC_BACKUP_FILE_INFO_STRU           *pstFileInfo;
    SC_BACKUP_FILE_INFO_STRU           *pstFileInfoTemp;
    SC_COMM_GLOBAL_STRU                *pstCommGlobal;
    VOS_INT32                           lReadSize;
    VOS_UINT32                          i;

    pstFileInfoTemp = (SC_BACKUP_FILE_INFO_STRU*)VOS_MemAlloc(ACPU_PID_PAM_OM, DYNAMIC_MEM_PT,
                                                             sizeof(SC_BACKUP_FILE_INFO_STRU));
    if(VOS_NULL_PTR == pstFileInfoTemp)
    {
        SC_Printf("SC_COMM_Backup: alloc mem1 fail!\r\n");
        return SC_ERROR_CODE_ALLOC_MEM_FAIL;
    }

    /*lint -e534*/
    VOS_MemSet((VOS_CHAR*)pstFileInfoTemp, 0, sizeof(SC_BACKUP_FILE_INFO_STRU));
    /*lint +e534*/

    pstFileInfoTemp->ulBackMagicMUM = SC_FILE_PACKET_MAGIC;
    pstFileInfoTemp->ulTotaleSize   = (sizeof(SC_BACKUP_FILE_INFO_STRU) - 4*sizeof(VOS_CHAR));

    pstCommGlobal = SC_CTX_GetCommGlobalVarAddr();

    /* 打开SC文件 */
    for (i=0; i<SC_SECRET_FILE_TYPE_BUTT; i++)
    {
        fp[i] = mdrv_file_open(pstCommGlobal->acSecretFileName[i], "rb");

        if (VOS_NULL_PTR != fp[i])
        {
            pstFileInfoTemp->astSCEachFileInfo[i].ulFileMagicMUM = SC_FILE_EXIST_MAGIC;
            /*lint -e534*/
            VOS_StrNCpy(pstFileInfoTemp->astSCEachFileInfo[i].acFilePath,
                        pstCommGlobal->acSecretFileName[i], SC_FILE_PATH_LEN -1);
            /*lint +e534*/
        }
    }

    /* 打开签名文件 */
    for (i=0; i<SC_SECRET_FILE_TYPE_BUTT; i++)
    {
        fp[i+SC_SECRET_FILE_TYPE_BUTT] = mdrv_file_open(pstCommGlobal->acSignFileName[i], "rb");

        if (VOS_NULL_PTR != fp[i+SC_SECRET_FILE_TYPE_BUTT])
        {
            pstFileInfoTemp->astSCEachFileInfo[i+SC_SECRET_FILE_TYPE_BUTT].ulFileMagicMUM = SC_FILE_EXIST_MAGIC;
            /*lint -e534*/
            VOS_StrNCpy(pstFileInfoTemp->astSCEachFileInfo[i+SC_SECRET_FILE_TYPE_BUTT].acFilePath,
                        pstCommGlobal->acSignFileName[i], SC_FILE_PATH_LEN-1);
            /*lint +e534*/
        }
    }

    /* 计算所有文件大小 */
    for (i=0; i<SC_SECRET_FILE_TYPE_BUTT*2; i++)
    {
        if (SC_FILE_EXIST_MAGIC != pstFileInfoTemp->astSCEachFileInfo[i].ulFileMagicMUM)
        {
            continue;
        }

        (VOS_VOID)mdrv_file_seek(fp[i], 0, SC_FILE_SEEK_END);
        pstFileInfoTemp->astSCEachFileInfo[i].ulFileLen    = (VOS_UINT32)mdrv_file_tell(fp[i]);
        pstFileInfoTemp->astSCEachFileInfo[i].ulFileOffset = pstFileInfoTemp->ulTotaleSize;
        pstFileInfoTemp->ulTotaleSize += pstFileInfoTemp->astSCEachFileInfo[i].ulFileLen;
        (VOS_VOID)mdrv_file_seek(fp[i], 0, SC_FILE_SEEK_SET);
    }

    pstFileInfo =(SC_BACKUP_FILE_INFO_STRU*)VOS_MemAlloc(ACPU_PID_PAM_OM,
                                                         DYNAMIC_MEM_PT,
                                                         pstFileInfoTemp->ulTotaleSize);
    if (VOS_NULL_PTR == pstFileInfo)
    {
        /*lint -e534*/
        VOS_MemFree(ACPU_PID_PAM_OM, pstFileInfoTemp);
        /*lint +e534*/
        SC_COMM_CloseAllFile(fp);

        SC_Printf("SC_COMM_Backup: alloc mem2 fail!\r\n");

        return SC_ERROR_CODE_ALLOC_MEM_FAIL;
    }

    /* 写内文件头信息 */
    /*lint -e534*/
    VOS_MemCpy((VOS_CHAR*)pstFileInfo,
               (VOS_CHAR*)pstFileInfoTemp,
               sizeof(SC_BACKUP_FILE_INFO_STRU) - 4*sizeof(VOS_CHAR));

    VOS_MemFree(ACPU_PID_PAM_OM, pstFileInfoTemp);
    /*lint +e534*/

    for (i=0;i<SC_SECRET_FILE_TYPE_BUTT*2; i++)
    {
        if (SC_FILE_EXIST_MAGIC != pstFileInfo->astSCEachFileInfo[i].ulFileMagicMUM)
        {
            continue;
        }

        lReadSize = mdrv_file_read((VOS_CHAR*)pstFileInfo + pstFileInfo->astSCEachFileInfo[i].ulFileOffset,
                                  sizeof(VOS_CHAR),
                                  pstFileInfo->astSCEachFileInfo[i].ulFileLen,
                                  fp[i]);

        if(lReadSize != pstFileInfo->astSCEachFileInfo[i].ulFileLen)
        {
            /* 读失败，释放句柄和内存*/
            SC_COMM_CloseAllFile(fp);
            /*lint -e534*/
            VOS_MemFree(ACPU_PID_PAM_OM, pstFileInfo);
            /*lint +e534*/

            SC_Printf("SC_COMM_Backup: mdrv_file_read fail!\r\n");

            return SC_ERROR_CODE_READ_FILE_FAIL;
        }

    }

    /* 文件读写完毕，关闭句柄 */
    SC_COMM_CloseAllFile(fp);

    /* 写入底软SC备份区 */
    if (SC_ERROR_CODE_NO_ERROR != mdrv_misc_scbackup_ext_write((VOS_UINT8*)pstFileInfo, pstFileInfo->ulTotaleSize))
    {
        /*lint -e534*/
        VOS_MemFree(ACPU_PID_PAM_OM, pstFileInfo);
        /*lint +e534*/
        SC_Printf("SC_COMM_Backup: scbackup_ext_write fail!\r\n");

        return SC_ERROR_CODE_SCCONTENT_WRITE_FAIL;
    }

    /*lint -e534*/
    VOS_MemFree(ACPU_PID_PAM_OM, pstFileInfo);
    /*lint +e534*/

    return SC_ERROR_CODE_NO_ERROR;
}

/*****************************************************************************
函 数 名  : SC_COMM_RestoreCheck
功能描述  : SC文件关键文件是否存在性检查
输入参数  : 无

输出参数  : 无
返 回 值  : VOS_BOOL

被调函数  :
修订记录  :
1.日    期   : 2015年8月10日
  作    者   : d00212987
  修改内容   : SC恢复前检查
*****************************************************************************/
VOS_BOOL SC_COMM_RestoreCheck(VOS_VOID)
{
    SC_COMM_GLOBAL_STRU                *pstCommGlobal;
    VOS_UINT32                          ulCheckStatus = 0;

    /* 说明: 只有关键文件都不存在才执行恢复操作，关键文件暂定 CK-FILE PI-FILE
              有个例文件丢失正向定位 */

    pstCommGlobal = SC_CTX_GetCommGlobalVarAddr();

    if (VOS_OK != mdrv_file_access(pstCommGlobal->acSecretFileName[SC_SECRET_FILE_TYPE_CK], SC_FILE_EXIST_OK))
    {
        ulCheckStatus++;
    }

    if (VOS_OK != mdrv_file_access(pstCommGlobal->acSecretFileName[SC_SECRET_FILE_TYPE_PI], SC_FILE_EXIST_OK))
    {
        ulCheckStatus++;
    }

    if (2 == ulCheckStatus)
    {
        /* 关键文件都不存在，则执行恢复 */
        SC_Printf("SC_COMM_RestoreCheck: sc need restore!!\r\n");

        return VOS_TRUE;
    }

    return VOS_FALSE;
}

/*****************************************************************************
函 数 名  : SC_COMM_WriteScFile
功能描述  : SC文件写入使用区
输入参数  : 无

输出参数  : 无
返 回 值  : VOS_INT

被调函数  :
修订记录  :
1.日    期   : 2015年8月10日
  作    者   : d00212987
  修改内容   : SC文件恢复到使用分区
*****************************************************************************/
VOS_UINT32 SC_COMM_WriteScFile(SC_BACKUP_FILE_INFO_STRU     *pstFileInfo)
{
    FILE                               *fp;
    VOS_INT32                           lWriteSize;
    VOS_UINT32                          i;

    for (i=0; i<(SC_SECRET_FILE_TYPE_BUTT * 2); i++)
    {
         /* 判断魔术数字是否正确 */
        if (SC_FILE_EXIST_MAGIC != pstFileInfo->astSCEachFileInfo[i].ulFileMagicMUM)
        {
            continue;
        }

        /* 写文件 */
        fp = mdrv_file_open(pstFileInfo->astSCEachFileInfo[i].acFilePath, "wb+");

        if (VOS_NULL_PTR == fp)
        {
            SC_Printf("SC_COMM_WriteScFile: sc create file fail!");

            return SC_ERROR_CODE_OPEN_FILE_FAIL;
        }

        lWriteSize = mdrv_file_write_sync((VOS_CHAR*)pstFileInfo + pstFileInfo->astSCEachFileInfo[i].ulFileOffset,
                                     sizeof(VOS_CHAR),
                                     pstFileInfo->astSCEachFileInfo[i].ulFileLen,
                                     fp);

        (VOS_VOID)mdrv_file_close(fp);

        if (lWriteSize != pstFileInfo->astSCEachFileInfo[i].ulFileLen)
        {
            SC_Printf("SC_COMM_WriteScFile: sc write file fail!");

            return SC_ERROR_CODE_WRITE_FILE_FAIL;
        }
    }

    return SC_ERROR_CODE_NO_ERROR;
}

/*****************************************************************************
函 数 名  : SC_COMM_Restore
功能描述  : SC文件恢复
输入参数  : 无

输出参数  : 无
返 回 值  : VOS_UINT32

被调函数  :
修订记录  :
1.日    期   : 2015年8月10日
  作    者   : d00212987
  修改内容   : SC文件恢复到使用分区
*****************************************************************************/
VOS_UINT32 SC_COMM_Restore(VOS_VOID)
{
    SC_BACKUP_FILE_INFO_STRU           *pstFileInfoTemp;
    SC_BACKUP_FILE_INFO_STRU           *pstFileInfo;

    if (VOS_FALSE == SC_COMM_RestoreCheck())
    {
        return SC_ERROR_CODE_SC_NO_NEED_RESTORE;
    }

    pstFileInfoTemp = (SC_BACKUP_FILE_INFO_STRU*)VOS_MemAlloc(ACPU_PID_PAM_OM,
                                                               DYNAMIC_MEM_PT,
                                                               sizeof(SC_BACKUP_FILE_INFO_STRU));
    if (VOS_NULL_PTR == pstFileInfoTemp)
    {
        SC_Printf("SC_COMM_Restore: alloc mem1 fail!\r\n");

        return SC_ERROR_CODE_ALLOC_MEM_FAIL;
    }

    if (VOS_OK != mdrv_misc_scbackup_ext_read((VOS_UINT8*)pstFileInfoTemp, sizeof(SC_BACKUP_FILE_INFO_STRU)))
    {
        (VOS_VOID)VOS_MemFree(ACPU_PID_PAM_OM, pstFileInfoTemp);

        SC_Printf("SC_COMM_Restore: sc backup read fail 1!\r\n");

        return SC_ERROR_CODE_SCBACKUP_READ_FAIL;
    }

    /* 判断魔术数字是否正确 */
    if (SC_FILE_PACKET_MAGIC != pstFileInfoTemp->ulBackMagicMUM)
    {
        (VOS_VOID)VOS_MemFree(ACPU_PID_PAM_OM, pstFileInfoTemp);

        SC_Printf("SC_COMM_Restore: sc backup magic number error!\r\n");

        return SC_ERROR_CODE_MAGNUM_CMP_FAIL;
    }

    /* 判断目标文件夹是否存在 */
    if (SC_ERROR_CODE_NO_ERROR != mdrv_file_access("/mnvm2:0/SC", SC_FILE_EXIST_OK))
    {
        (VOS_VOID)mdrv_file_mkdir("/mnvm2:0/SC");
    }

    if (SC_ERROR_CODE_NO_ERROR != mdrv_file_access("/mnvm2:0/SC/Pers", SC_FILE_EXIST_OK))
    {
        (VOS_VOID)mdrv_file_mkdir("/mnvm2:0/SC/Pers");
    }

    /* 根据长度申请内存 */
    pstFileInfo = (SC_BACKUP_FILE_INFO_STRU*)VOS_MemAlloc(ACPU_PID_PAM_OM,
                                                          DYNAMIC_MEM_PT,
                                                          pstFileInfoTemp->ulTotaleSize);
    if (VOS_NULL_PTR == pstFileInfo)
    {
        (VOS_VOID)VOS_MemFree(ACPU_PID_PAM_OM, pstFileInfoTemp);

        SC_Printf("SC_COMM_Restore: alloc mem2 fail!\r\n");

        return SC_ERROR_CODE_ALLOC_MEM_FAIL;
    }

    /* 读取全部内容 */
    if (VOS_OK != mdrv_misc_scbackup_ext_read((VOS_UINT8*)pstFileInfo, pstFileInfoTemp->ulTotaleSize))
    {
        (VOS_VOID)VOS_MemFree(ACPU_PID_PAM_OM, pstFileInfoTemp);
        (VOS_VOID)VOS_MemFree(ACPU_PID_PAM_OM, pstFileInfo);

        SC_Printf("SC_COMM_Restore: sc backup read fail 2!\r\n");

        return SC_ERROR_CODE_SCBACKUP_READ_FAIL;
    }

    (VOS_VOID)VOS_MemFree(ACPU_PID_PAM_OM, pstFileInfoTemp);

    if (VOS_OK != SC_COMM_WriteScFile(pstFileInfo))
    {
        (VOS_VOID)VOS_MemFree(ACPU_PID_PAM_OM, pstFileInfo);

        return SC_ERROR_CODE_SCFILE_RESTORE_FAIL;
    }

    (VOS_VOID)VOS_MemFree(ACPU_PID_PAM_OM, pstFileInfo);

    return SC_ERROR_CODE_NO_ERROR;
}

/*****************************************************************************
函 数 名  :SC_Printf
功能描述  :Log打印,可变参数
*****************************************************************************/
VOS_VOID SC_Printf(VOS_CHAR *pcData)
{
    FILE                               *fp;
    VOS_UINT32                          ulRetLen;
    VOS_UINT32                          ulFileSize;

    ulRetLen = VOS_StrLen(pcData);

    if ((SC_LOG_MAX_LEN < ulRetLen) || (0 == ulRetLen))
    {
        return ;
    }

    fp = mdrv_file_open(SC_IMEI_LOG_FILE_PATH, "a");

    if (VOS_NULL_PTR == fp)
    {
        return ;
    }

    if (VOS_OK != mdrv_file_seek(fp, 0, SC_FILE_SEEK_END))
    {
        return;
    }

    ulFileSize = (VOS_UINT32)mdrv_file_tell(fp);

    /* If the log file is too large, we need empty it. */
    if (ulFileSize > SC_LOG_FILE_MAX_SIZE)
    {
        /*lint -e534*/
        mdrv_file_close(fp);
        /*lint +e534*/
        fp = mdrv_file_open(SC_IMEI_LOG_FILE_PATH, "w");

        if (VOS_NULL_PTR == fp)
        {
            return ;
        }
    }

    /*lint -e534*/
    (VOS_VOID)mdrv_file_write(pcData, ulRetLen, 1, fp);

    (VOS_VOID)mdrv_file_close(fp);
    /*lint +e534*/

    return ;
}
#endif

#ifdef __cplusplus
    #if __cplusplus
        }
    #endif
#endif

