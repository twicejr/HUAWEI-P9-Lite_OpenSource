

#ifdef __cplusplus
#if __cplusplus
extern "C" {
#endif
#endif


/*****************************************************************************
  1 Include HeadFile
*****************************************************************************/
/*lint -save -e537*/
#include  "vos.h"
#include  "msp_errno.h"
#include  "diag_fs_proc.h"
#include  "diag_common.h"
/*lint -restore*/

/*lint -save -e767 原因:Log打印*/
#define    THIS_FILE_ID        MSP_FILE_ID_DIAG_FS_PROC_C
/*lint -restore +e767*/

/*****************************************************************************
  2 Declare the Global Variable
*****************************************************************************/
const VOS_CHAR g_acDiagRootPath[] = "/";
const VOS_CHAR g_acDiagLockedRootPath[] = "/modem_log"; /* 锁定状态下的根目录 */
const VOS_CHAR g_acDiagDumpDir[] = "/modem_log";
const VOS_CHAR g_acDiagLogDir[] = "/modem_log";

DIAG_FILE_INFO_STRU g_stDiagFileInfo = {DIAG_FILE_NULL, DIAG_FS_FOLDER_BUTT, VOS_NULL_PTR};

extern VOS_BOOL g_bAtDataLocked;
/*****************************************************************************
  3 Function
*****************************************************************************/

/*****************************************************************************
 Function Name   : diag_FsClose
 Description     : 关闭文件
 Input           :VOS_VOID
 Output          : None
 Return          : VOS_UINT32

 History         :
    1.w00182550      2013-1-29  Draft Enact
    2.c64416         2014-11-18  适配新的诊断架构

*****************************************************************************/
VOS_VOID diag_FsClose(VOS_VOID)
{
    mm_segment_t old_fs;

    old_fs = get_fs();
    set_fs(KERNEL_DS);

    if (DIAG_FILE_NULL != g_stDiagFileInfo.lFile)
    {
        DIAG_FS_CLOSE(g_stDiagFileInfo.lFile);
        g_stDiagFileInfo.lFile = DIAG_FILE_NULL;
    }

    (VOS_VOID)DIAG_FS_FILE_SYNC(g_stDiagFileInfo.lFile);
    set_fs(old_fs);
}


/*****************************************************************************
 Function Name   : diag_FsGetDirInfo
 Description     : 获取文件、文件夹数目
 Input           :VOS_CHAR *pDirName
                VOS_UINT32 *pulTotalNum
 Output          : None
 Return          : VOS_UINT32

 History         :
    1.w00182550      2013-1-29  Draft Enact
    2.c64416         2014-11-18  适配新的诊断架构

*****************************************************************************/
VOS_UINT32  diag_FsGetDirInfo(VOS_CHAR *pDirName, VOS_UINT32 *pulTotalNum)
{
    VOS_INT32 				dir_handle =0;
	VOS_INT32				nRead =0;
	VOS_INT32				nCount =0;
	VOS_UINT32				i=0;
	VOS_UINT8*				buf =NULL;

    DIAG_DIRENT_STRU        *pstTmpDirent;
    mm_segment_t old_fs;

    old_fs = get_fs();
    set_fs(KERNEL_DS);

    /*打开目录*/
    if((dir_handle = DIAG_FS_OPENDIR((VOS_CHAR*)pDirName,DIAG_FS_RDONLY|DIAG_FS_DIRECTORY,0))< 0)
    {
        set_fs(old_fs);
		diag_printf( "[%s]DIAG_FS_OPENDIR error!",__FUNCTION__);
        return VOS_ERR;
    }

	buf =(VOS_UINT8*)VOS_MemAlloc(MSP_PID_DIAG_APP_AGENT, DYNAMIC_MEM_PT,MSP_DF_DIR_BUF_LEN);
    if(NULL == buf)
    {
        diag_printf( "[%s]Alloc mem error!",__FUNCTION__);
		DIAG_FS_CLOSEDIR(dir_handle);
		set_fs(old_fs);
        return VOS_ERR;
    }
	nRead = DIAG_FS_GETDENTS(dir_handle, (struct linux_dirent __user *)buf, MSP_DF_DIR_BUF_LEN);

	if(-1 == nRead)
	{
		diag_printf("[%s]dents error,nRead=%d!\n",__FUNCTION__,(VOS_INT)nRead);
		*pulTotalNum =0;
		VOS_MemFree(MSP_PID_DIAG_APP_AGENT, buf);
		DIAG_FS_CLOSEDIR(dir_handle);
		set_fs(old_fs);
		return VOS_ERR;
	}

	if(0 == nRead)
	{
        /*lint -save -e717*/
		diag_printf("[%s]dents zero!\n",__FUNCTION__);
        /*lint -restore*/
		*pulTotalNum = 0;
		VOS_MemFree(MSP_PID_DIAG_APP_AGENT, buf);
		DIAG_FS_CLOSEDIR(dir_handle);
		set_fs(old_fs);
		return VOS_OK;
	}

	for(i=0; i<(VOS_UINT32)nRead;)
	{
	    pstTmpDirent = (DIAG_DIRENT_STRU*)(buf + i);
		i += pstTmpDirent->d_reclen;

		if((0 == VOS_StrCmp((char *) pstTmpDirent->d_name, "."))
			||(0 == VOS_StrCmp ((char *) pstTmpDirent->d_name, "..")))
        {
            /*lint -save -e717*/
        	diag_printf("diag_FsGetDirInfo:d_name=%S!\n",pstTmpDirent->d_name);
            /*lint -restore*/
            continue;
        }
#if 0
	    if (nCount>=FILENAME_NUM_MAX)
        {
        	DIAG_FS_CLOSEDIR(dir_handle);
	        set_fs(old_fs);
            return VOS_ERR;
        }
#endif
		nCount++;
	}

	*pulTotalNum = nCount;

     /*关闭目录*/
    if (DIAG_FS_ERROR == DIAG_FS_CLOSEDIR(dir_handle))
    {
        VOS_MemFree(MSP_PID_DIAG_APP_AGENT, buf);
    	diag_printf("[%s]DIAG_FS_CLOSEDIR zero!\n",__FUNCTION__);
        set_fs(old_fs);
        return VOS_ERR;
    }

    VOS_MemFree(MSP_PID_DIAG_APP_AGENT, buf);

    set_fs(old_fs);
    return VOS_OK;
}

/*****************************************************************************
 Function Name   : diag_FsGetItemInfo
 Description     : 获取文件或文件夹信息
               VOS_CHAR *pDirName
               DIAG_DIR_FILE_INFO_STRU *pstDirFileInfo
 Output          : None
 Return          : VOS_UINT32

 History         :
    1.w00182550      2013-1-29  Draft Enact
    2.c64416         2014-11-18  适配新的诊断架构

*****************************************************************************/
VOS_UINT32 diag_FsGetItemInfo(VOS_CHAR *pDirectory,DIAG_DIR_FILE_INFO_STRU *pstDirFileInfo)
{
    DIAG_DIRENT_STRU        *pstTmpDirent;
    DIAG_STAT_STRU           stStat;
    VOS_UINT8               ucDirName[MSP_DF_DIR_MAX_LEN];
    VOS_INT32 				dir_handle =0;
	VOS_INT32				nRead =0;
	VOS_INT32				i=0;
	VOS_UINT8*				buf =NULL;
    mm_segment_t old_fs;

    old_fs = get_fs();
    set_fs(KERNEL_DS);

    /*再次打开目录*/
    if((dir_handle = DIAG_FS_OPENDIR(pDirectory,DIAG_FS_RDONLY|DIAG_FS_DIRECTORY,0))< 0)
    {
    	diag_printf( "[%s]DIAG_FS_OPENDIR error!",__FUNCTION__);
        set_fs(old_fs);
        return VOS_ERR;

    }

	buf =(VOS_UINT8*)VOS_MemAlloc(MSP_PID_DIAG_APP_AGENT, DYNAMIC_MEM_PT,MSP_DF_DIR_BUF_LEN);
    if(NULL == buf)
    {
        diag_printf( "[%s]Alloc mem error!",__FUNCTION__);
		DIAG_FS_CLOSEDIR(dir_handle);
		set_fs(old_fs);
        return VOS_ERR;
    }
	nRead = DIAG_FS_GETDENTS(dir_handle, (struct linux_dirent __user *)buf, MSP_DF_DIR_BUF_LEN);
	if((-1 == nRead)||(0 == nRead))
	{
		diag_printf("[%s]dents error,nRead=%d!\n",__FUNCTION__,(VOS_INT)nRead);
		VOS_MemFree(MSP_PID_DIAG_APP_AGENT, buf);
		DIAG_FS_CLOSEDIR(dir_handle);
		set_fs(old_fs);
		return VOS_ERR;
	}

	/*轮询文件夹将所有文件名保存至全局变量*/
	for(i=0; i<nRead; )
	{
		pstTmpDirent = (DIAG_DIRENT_STRU*)(buf + i);
		i += pstTmpDirent->d_reclen;

		if((0 == VOS_StrCmp((char *) pstTmpDirent->d_name, "."))
			||(0 == VOS_StrCmp ((char *) pstTmpDirent->d_name, "..")))
		{
            /*lint -save -e717*/
			diag_printf("[%s]:d_name=%S!\n",__FUNCTION__,pstTmpDirent->d_name);
            /*lint -restore*/
			continue;
		}

		VOS_StrCpy((VOS_CHAR *)ucDirName, pDirectory);
		strncat((VOS_CHAR *)ucDirName, "/",sizeof(VOS_CHAR));
        strncat((VOS_CHAR *)ucDirName, pstTmpDirent->d_name,strlen(pstTmpDirent->d_name));

        /*通过stat获取文件或文件夹的信息*/
        if (DIAG_FS_ERROR == DIAG_FS_STAT((VOS_CHAR *)ucDirName, &stStat))
        {
        	diag_printf("DIAG_FS_STAT: error!\n");
            pstDirFileInfo->ulItemType = DIAG_FS_ITEM_FILE;
            pstDirFileInfo->st_size    = 0;
            pstDirFileInfo->st_mode    = 0;
            pstDirFileInfo->st_atime   = 0;
            pstDirFileInfo->st_mtime   = 0;
            pstDirFileInfo->st_ctime   = 0;
        }
        else
        {
            /*目录*/

            if (0 != (DIAG_IF_DIR&stStat.mode))
            {

                pstDirFileInfo->ulItemType = DIAG_FS_ITEM_FOLDER;
            }
            /*文件*/
            else
            {
                pstDirFileInfo->ulItemType = DIAG_FS_ITEM_FILE;
            }
            pstDirFileInfo->st_size   = (stStat.size & 0xFFFFFFFF);/* 目前文件大小不会超过32位大小 */
            pstDirFileInfo->st_atime  = stStat.atime.tv_sec;
            pstDirFileInfo->st_mtime  = stStat.mtime.tv_sec;
            pstDirFileInfo->st_ctime  = stStat.ctime.tv_sec;
            pstDirFileInfo->st_mode   = stStat.mode;
        }

        /*文件或文件夹名*/
        (VOS_VOID)VOS_MemSet(pstDirFileInfo->aucDirName, 0,DIAG_CMD_FILE_NAME_LEN);
        VOS_StrCpy(pstDirFileInfo->aucDirName, pstTmpDirent->d_name);

        pstDirFileInfo++;

 	}

    VOS_MemFree(MSP_PID_DIAG_APP_AGENT, buf);
    DIAG_FS_CLOSEDIR(dir_handle);
    set_fs(old_fs);

    return VOS_OK;

}

VOS_INT32 diag_FsOpen(const VOS_CHAR *pcFileName, VOS_INT lFlag)
{
    VOS_INT32  fp = 0;
    mm_segment_t old_fs;

    old_fs = get_fs();
    set_fs(KERNEL_DS);

    fp = DIAG_FS_OPEN(pcFileName, lFlag,0755);
	diag_fs_log();

    set_fs(old_fs);

    return (VOS_INT32)fp;
}

/*****************************************************************************
 Function Name   : diag_FsQueryProc
 Description     : 查询根目录
 Input           :VOS_UINT8* pstReq
                VOS_UINT32 ulCmdId
 Output          : None
 Return          : VOS_UINT32

 History         :
    1.w00182550      2013-1-29  Draft Enact
    2.c64416         2014-11-18  适配新的诊断架构

*****************************************************************************/
VOS_UINT32 diag_FsQueryProc(VOS_UINT8* pstReq)
{
    DIAG_CMD_FS_QUERY_REQ* pstFsReq = NULL;
    DIAG_CMD_FS_QUERY_CNF stFsCnf = {0};
    VOS_UINT32 ret = ERR_MSP_SUCCESS;
    DIAG_FRAME_INFO_STRU *pstDiagHead = NULL;
    MSP_DIAG_CNF_INFO_STRU stDiagInfo = {0};

    pstDiagHead = (DIAG_FRAME_INFO_STRU*)(pstReq);

    pstFsReq = (DIAG_CMD_FS_QUERY_REQ*)(pstReq + DIAG_MESSAGE_DATA_HEADER_LEN);

    if (DIAG_FS_ROOT_FOLDER == pstFsReq->ulFolderType)
    {
        /* 锁定状态下，根目录受限制 */
        if(g_bAtDataLocked)
        {
            stFsCnf.ulLength = VOS_StrLen((VOS_CHAR*)g_acDiagLockedRootPath);
            (VOS_VOID)VOS_MemCpy(stFsCnf.aucDirPath,g_acDiagLockedRootPath, stFsCnf.ulLength);
        }
        else
        {
            stFsCnf.ulLength = VOS_StrLen((VOS_CHAR*)g_acDiagRootPath);
            (VOS_VOID)VOS_MemCpy(stFsCnf.aucDirPath,g_acDiagRootPath, stFsCnf.ulLength);
        }
        g_stDiagFileInfo.ulFileType = DIAG_FS_ROOT_FOLDER;

    }
    else if (DIAG_FS_LOG_FOLDER == pstFsReq->ulFolderType)
    {
        stFsCnf.ulLength = VOS_StrLen((VOS_CHAR*)g_acDiagLogDir);
        (VOS_VOID)VOS_MemCpy(stFsCnf.aucDirPath,g_acDiagLogDir, stFsCnf.ulLength);
        g_stDiagFileInfo.ulFileType = DIAG_FS_LOG_FOLDER;
    }
    /*临终遗言文件所在的路径*/
    else if (DIAG_FS_DUMP_FOLDER == pstFsReq->ulFolderType)
    {
        stFsCnf.ulLength = VOS_StrLen((VOS_CHAR*)g_acDiagDumpDir);
        (VOS_VOID)VOS_MemCpy(stFsCnf.aucDirPath, g_acDiagDumpDir, stFsCnf.ulLength);
        g_stDiagFileInfo.ulFileType = DIAG_FS_DUMP_FOLDER;
    }
    else
    {
        ret = ERR_MSP_FAILURE;
    }
    stFsCnf.ulRet = ret;

    DIAG_MSG_COMMON_PROC(stDiagInfo, stFsCnf, pstDiagHead);

    stDiagInfo.ulMsgType    = DIAG_MSG_TYPE_BSP;

    return DIAG_MsgReport(&stDiagInfo, &stFsCnf, sizeof(stFsCnf));
}


/*****************************************************************************
 Function Name   : diag_FsScanProc
 Description     : 扫描所有文件或文件夹信息
 Input           :VOS_UINT8* pstReq
                VOS_UINT32 ulCmdId
 Output          : None
 Return          : VOS_UINT32

 History         :
    1.w00182550      2013-1-29  Draft Enact
    2.c64416         2014-11-18  适配新的诊断架构

*****************************************************************************/
VOS_UINT32 diag_FsScanProc(VOS_UINT8* pstReq)
{
    DIAG_CMD_FS_SCAN_DIR_REQ* pstFsReq = NULL;
    DIAG_CMD_FS_SCAN_DIR_CNF* pstFsCnf = NULL;
    VOS_UINT32 ret = ERR_MSP_SUCCESS;
    VOS_UINT32              ulTotalNum;
    VOS_UINT32              ulTotalSize;
    DIAG_FRAME_INFO_STRU *pstDiagHead = NULL;
    MSP_DIAG_CNF_INFO_STRU stDiagInfo = {0};

    pstDiagHead = (DIAG_FRAME_INFO_STRU*)(pstReq);

    pstFsReq = (DIAG_CMD_FS_SCAN_DIR_REQ*)(pstReq + DIAG_MESSAGE_DATA_HEADER_LEN);

   /*得到目录内，文件和文件夹的总个数、总的名字长度*/
    if(VOS_OK != diag_FsGetDirInfo(pstFsReq->szDirectory,&ulTotalNum))
    {
        return VOS_ERR;
    }

    /*计算返回给工具侧消息包的长度*/
    ulTotalSize = (ulTotalNum* sizeof(DIAG_DIR_FILE_INFO_STRU)+ sizeof(DIAG_CMD_FS_SCAN_DIR_CNF));

    pstFsCnf = (DIAG_CMD_FS_SCAN_DIR_CNF*)VOS_MemAlloc(MSP_PID_DIAG_APP_AGENT, DYNAMIC_MEM_PT, ulTotalSize);
    if (VOS_NULL_PTR == pstFsCnf)
    {
        return VOS_ERR;
    }

    /*获取每个文件和文件夹的信息*/
    /*lint -save -e539*/
	if(ulTotalNum>0)
	{
    	ret = diag_FsGetItemInfo(pstFsReq->szDirectory,pstFsCnf->stDirInfo);
	}
    /*lint -restore*/

    pstFsCnf->ulRet = ret;
    pstFsCnf->ulDirNum= ulTotalNum;
    pstFsCnf->ulDirInfoLen= ulTotalNum * sizeof(DIAG_DIR_FILE_INFO_STRU);

    DIAG_MSG_COMMON_PROC(stDiagInfo, (*pstFsCnf), pstDiagHead);

    stDiagInfo.ulMsgType    = DIAG_MSG_TYPE_BSP;

    ret = DIAG_MsgReport(&stDiagInfo, pstFsCnf, ulTotalSize);

    VOS_MemFree(MSP_PID_DIAG_APP_AGENT, pstFsCnf);

    return ret;

}

/*****************************************************************************
 Function Name   : diag_FsMkdirProc
 Description     : 创建目录
 Input           :VOS_UINT8* pstReq
                VOS_UINT32 ulCmdId
 Output          : None
 Return          : VOS_UINT32

 History         :
    1.w00182550      2013-1-29  Draft Enact
    2.c64416         2014-11-18  适配新的诊断架构

*****************************************************************************/
VOS_UINT32 diag_FsMkdirProc(VOS_UINT8* pstReq)
{
    DIAG_CMD_FS_MAKE_DIR_REQ* pstFsReq = NULL;
    DIAG_CMD_FS_MAKE_DIR_CNF stFsCnf = {0};
    VOS_UINT32 ret = ERR_MSP_SUCCESS;
    DIAG_FRAME_INFO_STRU *pstDiagHead = NULL;
    MSP_DIAG_CNF_INFO_STRU stDiagInfo = {0};

    mm_segment_t old_fs;

    pstDiagHead = (DIAG_FRAME_INFO_STRU*)(pstReq);

    pstFsReq = (DIAG_CMD_FS_MAKE_DIR_REQ*)(pstReq + DIAG_MESSAGE_DATA_HEADER_LEN);

    old_fs = get_fs();
    set_fs(KERNEL_DS);

    ret = (VOS_UINT32)DIAG_FS_MKDIR((VOS_CHAR*)pstFsReq->szDirectory,0755);

    stFsCnf.ulRet = ret;

    set_fs(old_fs);

    DIAG_MSG_COMMON_PROC(stDiagInfo, stFsCnf, pstDiagHead);

    stDiagInfo.ulMsgType    = DIAG_MSG_TYPE_BSP;

    return DIAG_MsgReport(&stDiagInfo, &stFsCnf, sizeof(stFsCnf));
}

/*****************************************************************************
 Function Name   : diag_FsOpenProc
 Description     : 打开或创建文件
 Input           :VOS_UINT8* pstReq
                VOS_UINT32 ulCmdId
 Output          : None
 Return          : VOS_UINT32

 History         :
    1.w00182550      2013-1-29  Draft Enact
    2.c64416         2014-11-18  适配新的诊断架构

*****************************************************************************/
VOS_UINT32 diag_FsOpenProc(VOS_UINT8* pstReq)
{
    DIAG_CMD_FS_OPEN_REQ* pstFsReq = NULL;
    DIAG_CMD_FS_OPEN_CNF stFsCnf = {0};
    VOS_UINT32 ret = ERR_MSP_SUCCESS;
    DIAG_FRAME_INFO_STRU *pstDiagHead = NULL;
    MSP_DIAG_CNF_INFO_STRU stDiagInfo = {0};

    pstDiagHead = (DIAG_FRAME_INFO_STRU*)(pstReq);

    pstFsReq = (DIAG_CMD_FS_OPEN_REQ*)(pstReq + DIAG_MESSAGE_DATA_HEADER_LEN);

    /*不支持操作文件的重入操作*/
    if (DIAG_FILE_NULL != g_stDiagFileInfo.lFile)
    {
        /* 文件导出过程中可能文件size还在增加，导致上一个文件没读完工具就开始新的文件导出 */
        diag_FsClose();
    }
    /*lint -save -e539*/
	diag_fs_log();
    /*lint -restore*/
    g_stDiagFileInfo.lFile = diag_FsOpen(pstFsReq->szDirectory, (VOS_INT)(pstFsReq->ulMode));

    if (g_stDiagFileInfo.lFile < 0)
    {
    	g_stDiagFileInfo.lFile = DIAG_FILE_NULL;
        ret = VOS_ERR;
    }
	else
	{
#if 0
	    /*启动定时器*/
	    g_stDiagFileInfo.hTimer = VOS_NULL_PTR;

	    ret = VOS_StartRelTimer(&g_stDiagFileInfo.hTimer, MSP_PID_DIAG_APP_AGENT, DIAG_CMD_FILE_OPS_TIME_OUT_LEN, 0, DIAG_TMR_FILE_OP_TIMEOUT_PARAM,VOS_RELTIMER_NOLOOP, VOS_TIMER_NO_PRECISION);
        if(ret != ERR_MSP_SUCCESS)
        {
            /*lint -save -e717*/
            diag_printf("VOS_StartRelTimer fail [%s]\n",__func__);
            /*lint -restore*/
        }
#endif
        diag_fs_log();
	}
    stFsCnf.ulRet = ret;

    DIAG_MSG_COMMON_PROC(stDiagInfo, stFsCnf, pstDiagHead);

    stDiagInfo.ulMsgType    = DIAG_MSG_TYPE_BSP;

	diag_fs_log();

    return DIAG_MsgReport(&stDiagInfo, &stFsCnf, sizeof(stFsCnf));
}

/*****************************************************************************
 Function Name   : diag_FsImportProc
 Description     : 导入文件
 Input           :VOS_UINT8* pstReq
                VOS_UINT32 ulCmdId
 Output          : None
 Return          : VOS_UINT32

 History         :
    1.w00182550      2013-1-29  Draft Enact
    2.c64416         2014-11-18  适配新的诊断架构

*****************************************************************************/
VOS_UINT32 diag_FsImportProc(VOS_UINT8* pstReq)
{
    DIAG_CMD_FS_IMPORT_REQ* pstFsReq = NULL;
    DIAG_CMD_FS_IMPORT_CNF stFsCnf = {0};
    VOS_UINT32 ret = ERR_MSP_SUCCESS;
    VOS_INT32 lResult =0;
    mm_segment_t old_fs;
    DIAG_FRAME_INFO_STRU *pstDiagHead = NULL;
    MSP_DIAG_CNF_INFO_STRU stDiagInfo = {0};

    pstDiagHead = (DIAG_FRAME_INFO_STRU*)(pstReq);

    pstFsReq = (DIAG_CMD_FS_IMPORT_REQ*)(pstReq + DIAG_MESSAGE_DATA_HEADER_LEN);

    if (DIAG_FILE_NULL == g_stDiagFileInfo.lFile)
    {
        return ERR_MSP_FAILURE;
    }
    /*lint -save -e539*/
	diag_fs_log();
    /*lint -restore*/
#if 0
    /*停止定时器*/
    VOS_StopRelTimer(&g_stDiagFileInfo.hTimer);
#endif
    /*写文件完毕，关闭文件*/
    if (0 == pstFsReq->ulSize)
    {
		diag_fs_log();
        diag_FsClose();
        /*打包回复给FW*/
        stFsCnf.ulRet = ERR_MSP_SUCCESS;

        DIAG_MSG_COMMON_PROC(stDiagInfo, stFsCnf, pstDiagHead);

        stDiagInfo.ulMsgType    = DIAG_MSG_TYPE_BSP;

        return DIAG_MsgReport(&stDiagInfo, &stFsCnf, sizeof(stFsCnf));
    }

    old_fs = get_fs();
    set_fs(KERNEL_DS);
    lResult = DIAG_FS_WRITE(g_stDiagFileInfo.lFile, pstFsReq->acContent, pstFsReq->ulSize);

    set_fs(old_fs);

    /*写文件操作失败或者写入长度不正确*/
    if ((DIAG_FS_ERROR == lResult)||(lResult != (VOS_INT32)(pstFsReq->ulSize)))
    {
		diag_fs_log();
        /*lint -save -e717*/
		diag_printf("[%s]!,lResult=%d\n",__FUNCTION__,lResult);
        /*lint -restore*/
		diag_FsClose();
        return VOS_ERR;
    }
#if 0
    /*启动定时器*/
    ret = VOS_StartRelTimer(&g_stDiagFileInfo.hTimer, MSP_PID_DIAG_APP_AGENT,DIAG_CMD_FILE_OPS_TIME_OUT_LEN,0,DIAG_TMR_FILE_OP_TIMEOUT_PARAM,VOS_RELTIMER_NOLOOP, VOS_TIMER_NO_PRECISION);
    if(ret != ERR_MSP_SUCCESS)
    {
        /*lint -save -e717*/
        diag_printf("VOS_StartRelTimer fail [%s]\n",__func__);
        /*lint -restore*/
    }
#endif
    stFsCnf.ulRet = ret;

    DIAG_MSG_COMMON_PROC(stDiagInfo, stFsCnf, pstDiagHead);

    stDiagInfo.ulMsgType    = DIAG_MSG_TYPE_BSP;

    return DIAG_MsgReport(&stDiagInfo, &stFsCnf, sizeof(stFsCnf));
}

/*****************************************************************************
 Function Name   : diag_FsExportProc
 Description     : 导出文件
 Input           :VOS_UINT8* pstReq
                VOS_UINT32 ulCmdId
 Output          : None
 Return          : VOS_UINT32

 History         :
    1.w00182550      2013-1-29  Draft Enact
    2.c64416         2014-11-18  适配新的诊断架构

*****************************************************************************/
VOS_UINT32 diag_FsExportProc(VOS_UINT8* pstReq)
{
    DIAG_CMD_FS_EXPORT_CNF *pstFsCnf = NULL;
    VOS_UINT32 ret = ERR_MSP_SUCCESS;
    VOS_UINT32 ulReadSize = 0;
    mm_segment_t old_fs;
    DIAG_FRAME_INFO_STRU *pstDiagHead = NULL;
    MSP_DIAG_CNF_INFO_STRU stDiagInfo = {0};

    pstDiagHead = (DIAG_FRAME_INFO_STRU*)(pstReq);

    if (DIAG_FILE_NULL == g_stDiagFileInfo.lFile)
    {
		diag_fs_log();
         return ERR_MSP_FAILURE;
    }

#if 0
    /*停止定时器*/
    VOS_StopRelTimer(&g_stDiagFileInfo.hTimer);
	diag_fs_log();
#endif

    pstFsCnf = (DIAG_CMD_FS_EXPORT_CNF*)VOS_MemAlloc(MSP_PID_DIAG_APP_AGENT, DYNAMIC_MEM_PT, sizeof(DIAG_CMD_FS_EXPORT_CNF)+DIAG_TRANSFER_BLOCK_MAX_SIZE);
    if (VOS_NULL_PTR == pstFsCnf)
    {

		diag_fs_log();
        diag_FsClose();
        return ERR_MSP_FAILURE;

    }

    old_fs = get_fs();
    set_fs(KERNEL_DS);

    ulReadSize = (VOS_UINT32)DIAG_FS_READ(g_stDiagFileInfo.lFile,(VOS_CHAR*)pstFsCnf + sizeof(DIAG_CMD_FS_EXPORT_CNF), DIAG_TRANSFER_BLOCK_MAX_SIZE);

    set_fs(old_fs);

    /*读取文件出现错误*/
    if (DIAG_FS_ERROR == (VOS_INT32)ulReadSize)
    {
		diag_fs_log();
        /*lint -save -e50*/
        VOS_MemFree(MSP_PID_DIAG_APP_AGENT, pstFsCnf);
        /*lint -restore*/
        diag_FsClose();
        return ERR_MSP_FAILURE;
    }

    /*表明已经没有内容可以读取，文件内容全部读完*/
    if (0 == ulReadSize)
    {
		diag_fs_log();
        diag_FsClose();
    }
    else
    {
		diag_fs_log();
#if 0
        /*启动定时器*/
        g_stDiagFileInfo.hTimer = VOS_NULL_PTR;
        ret = VOS_StartRelTimer(&g_stDiagFileInfo.hTimer, MSP_PID_DIAG_APP_AGENT, DIAG_CMD_FILE_OPS_TIME_OUT_LEN, 0, DIAG_TMR_FILE_OP_TIMEOUT_PARAM, VOS_RELTIMER_NOLOOP, VOS_TIMER_NO_PRECISION);
        if(ret != ERR_MSP_SUCCESS)
        {
            /*lint -save -e717*/
            diag_printf("VOS_StartRelTimer fail [%s]\n", __func__);
            /*lint -restore*/
        }
#endif
	}

    pstFsCnf->ulRet = ret;
    pstFsCnf->ulSize = ulReadSize;

    DIAG_MSG_COMMON_PROC(stDiagInfo, (*pstFsCnf), pstDiagHead);

    stDiagInfo.ulMsgType  = DIAG_MSG_TYPE_BSP;

    ret = DIAG_MsgReport(&stDiagInfo, pstFsCnf, (sizeof(DIAG_CMD_FS_EXPORT_CNF) + ulReadSize));

    /*lint -save -e50*/
    VOS_MemFree(MSP_PID_DIAG_APP_AGENT, pstFsCnf);
    /*lint -restore*/
	diag_fs_log();
    return ret;
}

/*****************************************************************************
 Function Name   : diag_FsDeleteProc
 Description     : 删除文件或文件夹
 Input           :VOS_UINT8* pstReq
                VOS_UINT32 ulCmdId
 Output          : None
 Return          : VOS_UINT32

 History         :
    1.w00182550      2013-1-29  Draft Enact
    2.c64416         2014-11-18  适配新的诊断架构

*****************************************************************************/
VOS_UINT32 diag_FsDeleteProc(VOS_UINT8* pstReq)
{
    DIAG_CMD_FS_DELETE_REQ* pstFsReq = NULL;
    DIAG_CMD_FS_DELETE_CNF stFsCnf = {0};
    VOS_UINT32 ret = ERR_MSP_SUCCESS;
    mm_segment_t old_fs;
    DIAG_FRAME_INFO_STRU *pstDiagHead = NULL;
    MSP_DIAG_CNF_INFO_STRU stDiagInfo = {0};

    pstDiagHead = (DIAG_FRAME_INFO_STRU*)(pstReq);

    pstFsReq = (DIAG_CMD_FS_DELETE_REQ*)(pstReq + DIAG_MESSAGE_DATA_HEADER_LEN);

    old_fs = get_fs();
    set_fs(KERNEL_DS);

    if (DIAG_FS_ITEM_FOLDER == pstFsReq->ulItemType)
    {
        ret = (VOS_UINT32)DIAG_FS_RMDIR(pstFsReq->szDirectory);
    }
    else if (DIAG_FS_ITEM_FILE == pstFsReq->ulItemType)
    {
        ret = (VOS_UINT32)DIAG_FS_RMFILE(pstFsReq->szDirectory);
    }

    set_fs(old_fs);

    stFsCnf.ulRet = ret;

    DIAG_MSG_COMMON_PROC(stDiagInfo, stFsCnf, pstDiagHead);

    stDiagInfo.ulMsgType  = DIAG_MSG_TYPE_BSP;

    return DIAG_MsgReport(&stDiagInfo, &stFsCnf, sizeof(stFsCnf));
}

/*****************************************************************************
 Function Name   : diag_FsSpaceProc
 Description     : 查询使用及可用空间
 Input           :VOS_UINT8* pstReq
                VOS_UINT32 ulCmdId
 Output          : None
 Return          : VOS_UINT32

 History         :
    1.w00182550      2013-1-29  Draft Enact
    2.c64416         2014-11-18  适配新的诊断架构

*****************************************************************************/
VOS_UINT32 diag_FsSpaceProc(VOS_UINT8* pstReq)
{
    DIAG_CMD_FS_SPACE_REQ* pstFsReq = NULL;
    DIAG_CMD_FS_SPACE_CNF stFsCnf = {0};
    VOS_UINT32 ret = ERR_MSP_SUCCESS;
    mm_segment_t old_fs;
    DIAG_FRAME_INFO_STRU *pstDiagHead = NULL;
    MSP_DIAG_CNF_INFO_STRU stDiagInfo = {0};

    pstDiagHead = (DIAG_FRAME_INFO_STRU*)(pstReq);

    pstFsReq = (DIAG_CMD_FS_SPACE_REQ*)(pstReq + DIAG_MESSAGE_DATA_HEADER_LEN);

    old_fs = get_fs();
    set_fs(KERNEL_DS);

    ret = (VOS_UINT32)DRV_FILE_GET_DISKSPACE((VOS_CHAR*)(pstFsReq->szDirectory),(VOS_UINT*)&stFsCnf.ulDiskSpace,
                    (VOS_UINT*)&stFsCnf.ulUsedSpace,(VOS_UINT*)&stFsCnf.ulValidSpace);

    stFsCnf.ulRet = ret;
    set_fs(old_fs);

    DIAG_MSG_COMMON_PROC(stDiagInfo, stFsCnf, pstDiagHead);

    stDiagInfo.ulMsgType  = DIAG_MSG_TYPE_BSP;

    return DIAG_MsgReport(&stDiagInfo, &stFsCnf, sizeof(stFsCnf));
}


/*lint -restore*/


#ifdef __cplusplus
    #if __cplusplus
        }
    #endif
#endif

