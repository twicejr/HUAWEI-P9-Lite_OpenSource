

/*****************************************************************************
  1 头文件包含
*****************************************************************************/
#include "vos.h"

#include "RnicDemandDialFileIO.h"
#include "RnicCtx.h"
#include "RnicLog.h"
#include "RnicProcMsg.h"
#include "PsLib.h"

#if (VOS_OS_VER == VOS_LINUX)
#include <linux/namei.h>
#include <linux/fs.h>
#include <linux/module.h>
#include <linux/proc_fs.h>
#include <linux/kallsyms.h>
#include <asm/uaccess.h>
#include <asm-generic/errno-base.h>
#include <kernel.h>
#endif


#ifdef __cplusplus
#if __cplusplus
extern "C" {
#endif
#endif

/*****************************************************************************
    协议栈打印打点方式下的.C文件宏定义
*****************************************************************************/
/*lint -e960*/
#define    THIS_FILE_ID        PS_FILE_ID_RNIC_DEMAND_DIAL_FILE_IO_C
/*lint +e960*/


/*****************************************************************************
  2 全局变量定义
*****************************************************************************/
#if (VOS_OS_VER == VOS_LINUX)

static const struct file_operations g_stOnDemandFileOps        =
{
    .owner      = THIS_MODULE,
    .write      = RNIC_WriteOnDemandFile,
    .read       = RNIC_ReadOnDemandFile,
};

static const struct file_operations g_stIdleTimerOutFileOps    =
{
    .owner      = THIS_MODULE,
    .write      = RNIC_WriteIdleTimerOutFile,
    .read       = RNIC_ReadIdleTimerOutFile,
};

static const struct file_operations g_stDialEventReportFileOps =
{
    .owner      = THIS_MODULE,
    .write      = RNIC_WriteDialEventReportFile,
    .read       = RNIC_ReadDialEventReportFile,
};
#else
static const struct file_operations g_stOnDemandFileOps ;
static const struct file_operations g_stIdleTimerOutFileOps ;
static const struct file_operations g_stDialEventReportFileOps;
#endif
/*****************************************************************************
  3 函数实现
*****************************************************************************/
/*****************************************************************************
 函 数 名  : RNIC_TransferStringToInt
 功能描述  : 将app输入的字串转换为数字
 输入参数  : VOS_CHAR *pcString
 输出参数  : 无
 返 回 值  : VOS_UINT32
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2012年2月10日
    作    者   : w00199382
    修改内容   : 新生成函数

*****************************************************************************/
VOS_UINT32 RNIC_TransferStringToInt(VOS_CHAR *pcString)
{
    VOS_UINT32                          ulStrLen;
    VOS_UINT32                          i;
    VOS_UINT32                          ulRst;

    ulStrLen                            = 0;
    ulRst                               = 0;

    ulStrLen = VOS_StrLen(pcString);


    for ( i = 0; i < ulStrLen; i++ )
    {
        if ( (pcString[i] >= '0') && (pcString[i] <= '9') )
        {
            ulRst = (ulRst * 10) + (pcString[i] - '0');
        }
    }

    return ulRst;
}

/*****************************************************************************
 函 数 名  : RNIC_ReadOnDemandFile
 功能描述  : OnDemand虚拟文件读实现
 输入参数  : file --- 文件句柄
             buf  --- 用户空间
             ppos --- 文件偏移，参数未使用
 输出参数  : 无
 返 回 值  : 成功或失败

 修改历史      :
  1.日    期   : 2012年01月30日
    作    者   : S62952
    修改内容   : 新生成函数

*****************************************************************************/
ssize_t RNIC_ReadOnDemandFile(
    struct file                        *file,
    char __user                        *buf,
    size_t                              len,
    loff_t                             *ppos
)
{
    RNIC_DIAL_MODE_STRU                *pstDialMode;
    VOS_CHAR                            acModeTemp[RNIC_ONDEMAND_FILE_LEN];
    VOS_UINT32                          ulDialModeLen;

    if (*ppos > 0)
    {
        RNIC_ERROR_LOG(ACPU_PID_RNIC, "RNIC_ReadOnDemandFile:ppos is err!");
        return 0;
    }

    PS_MEM_SET(acModeTemp, 0x00, RNIC_ONDEMAND_FILE_LEN);

    /* 获取按需拨号的模式以及时长的地址 */
    pstDialMode                         = RNIC_GetDialModeAddr();

    VOS_sprintf((VOS_CHAR *)acModeTemp, "%d", pstDialMode->enDialMode);

    ulDialModeLen = VOS_StrLen(acModeTemp);

    len             = PS_MIN(len, ulDialModeLen);

    /*拷贝内核空间数据到用户空间上面*/
    if (0 == copy_to_user(buf,(VOS_VOID *)acModeTemp, len))
    {
        *ppos += (loff_t)len;

        return (ssize_t)len;
    }
    else
    {
        RNIC_ERROR_LOG(ACPU_PID_RNIC, "RNIC_ReadOnDemandFile:copy_to_user fail!");
        return -EPERM;
    }
}


/*****************************************************************************
 函 数 名  : RNIC_WriteOnDemandFile
 功能描述  : OnDemand虚拟文件写实现
 输入参数  : file ----- 文件句柄
             buf  ----- 用户空间数据
             lLength -- 用户数据长度
             ppos - ----文件偏移，参数未使用
 输出参数  : 无
 返 回 值  : 成功或失败

 修改历史      :
  1.日    期   : 2012年01月30日
    作    者   : S62952
    修改内容   : 新生成函数
  2.日    期   : 2012年8月10日
    作    者   : y00213812
    修改内容   : DTS2012082204471, TQE清理，代码冗余
*****************************************************************************/
ssize_t RNIC_WriteOnDemandFile(
    struct file                        *file,
    const char __user                  *buf,
    size_t                              len,
    loff_t                             *ppos
)
{
    RNIC_DIAL_MODE_STRU                *pstDialMode;
    RNIC_DIAL_MODE_STRU                 stDialMode;
    VOS_CHAR                            acModeTemp[RNIC_ONDEMAND_FILE_LEN];

    PS_MEM_SET(acModeTemp, 0x00, RNIC_ONDEMAND_FILE_LEN);

    /* 获取按需拨号的模式以及时长的地址 */
    pstDialMode                         = RNIC_GetDialModeAddr();

    if (NULL == buf)
    {
        RNIC_ERROR_LOG(ACPU_PID_RNIC, "RNIC_WriteOnDemandFile:buff is null");
        return -EFAULT;
    }

    if (len >= RNIC_ONDEMAND_FILE_LEN)
    {
        RNIC_ERROR_LOG1(ACPU_PID_RNIC, "RNIC_WriteOnDemandFile:len is!", len);
        return -ENOSPC;
    }

    /*拷贝用户空间数据到内核空间上面*/
    if (copy_from_user((VOS_VOID *)acModeTemp, (VOS_VOID *)buf, len)  > 0)
    {
        RNIC_ERROR_LOG(ACPU_PID_RNIC, "RNIC_WriteOnDemandFile:copy_from_user ERR!");
        return -EFAULT;
    }

    acModeTemp[len] = '\0';

    PS_PRINTF("RNIC_WriteOnDemandFile:acModeTemp %s len is %d\r\n", acModeTemp, len);

    stDialMode.enDialMode = RNIC_TransferStringToInt(acModeTemp);

    /* 按需拨号 */
    if (RNIC_DIAL_MODE_DEMAND_CONNECT == stDialMode.enDialMode)
    {
        RNIC_StartTimer(TI_RNIC_DEMAND_DIAL_DISCONNECT, TI_RNIC_DEMAND_DIAL_DISCONNECT_LEN);
    }
    else
    {
        RNIC_StopTimer(TI_RNIC_DEMAND_DIAL_DISCONNECT);
    }

    /* 保存拨号模式上下文中 */
    pstDialMode->enDialMode             = stDialMode.enDialMode;


    RNIC_SendDialInfoMsg(ID_RNIC_MNTN_DIAL_MODE_INFO);

    return (ssize_t)len;
}

/*****************************************************************************
 函 数 名  : RNIC_InitOnDemandFile
 功能描述  : OnDemand虚拟文件初始化
 输入参数  : proc_dir_entry *pstParentFileDirEntry -- 父目录的入口
 输出参数  : 无
 返 回 值  : 初始化结果

 修改历史      :
  1.日    期   : 2012年01月30日
    作    者   : S62952
    修改内容   : 新生成函数

*****************************************************************************/
VOS_UINT32 RNIC_InitOnDemandFile(struct proc_dir_entry *pstParentFileDirEntry)
{
    struct proc_dir_entry              *pstOnDemandEntry;

    if (VOS_NULL_PTR == pstParentFileDirEntry)
    {
        /*创建OnDemand虚拟文件*/
        pstOnDemandEntry                   = proc_create("dial/ondemand",
                                                        /*lint -e960 修改人:l60609;原因:64bit*/
                                                        RNIC_VFILE_CRT_LEVEL,
                                                        /*lint +e960 修改人:l60609;原因:64bit*/
                                                        pstParentFileDirEntry,
                                                        &g_stOnDemandFileOps);

        if (VOS_NULL_PTR == pstOnDemandEntry)
        {
            RNIC_WARNING_LOG(ACPU_PID_RNIC,
                            "RNIC_OnDemandVf_Init: proc_create Return NULL");

            return VOS_ERR;
        }
    }
    else
    {
        /*创建OnDemand虚拟文件*/
        pstOnDemandEntry                   = proc_create("ondemand",
                                                        /*lint -e960 修改人:l60609;原因:64bit*/
                                                        RNIC_VFILE_CRT_LEVEL,
                                                        /*lint +e960 修改人:l60609;原因:64bit*/
                                                        pstParentFileDirEntry,
                                                        &g_stOnDemandFileOps);

        if (VOS_NULL_PTR == pstOnDemandEntry)
        {
            RNIC_WARNING_LOG(ACPU_PID_RNIC,
                            "RNIC_OnDemandVf_Init: proc_create Return NULL");

            return VOS_ERR;
        }
    }

    return VOS_OK;
}

/*****************************************************************************
 函 数 名  : RNIC_ReadIdleTimerOutFile
 功能描述  : ideltimerout虚拟文件读实现
 输入参数  : file --- 文件句柄
             buf  --- 用户空间
             ppos --- 文件偏移，参数未使用
 输出参数  : 无
 返 回 值  : 成功或失败

 修改历史      :
  1.日    期   : 2012年01月30日
    作    者   : S62952
    修改内容   : 新生成函数

*****************************************************************************/
ssize_t RNIC_ReadIdleTimerOutFile(
    struct file                        *file,
    char __user                        *buf,
    size_t                              len,
    loff_t                             *ppos
)
{
    RNIC_DIAL_MODE_STRU                *pstDialMode;
    VOS_CHAR                            acIdleTimeTemp[RNIC_IDLETIMEROUT_FILE_LEN];
    VOS_UINT32                          ulIdleTimeLen;

    if (*ppos > 0)
    {
        RNIC_ERROR_LOG(ACPU_PID_RNIC, "RNIC_ReadIdleTimerOutFile:ppos ERR!");
        return 0;
    }

    PS_MEM_SET(acIdleTimeTemp, 0x00, RNIC_IDLETIMEROUT_FILE_LEN);


    /* 获取按需拨号的模式以及时长的地址 */
    pstDialMode                         = RNIC_GetDialModeAddr();

    VOS_sprintf(acIdleTimeTemp, "%d", pstDialMode->ulIdleTime);

    ulIdleTimeLen  = VOS_StrLen(acIdleTimeTemp);

    len            = PS_MIN(len, ulIdleTimeLen);

    /*拷贝内核空间数据到用户空间上面*/
    if (0 == copy_to_user(buf,(VOS_VOID *)acIdleTimeTemp, len))
    {
        *ppos += (loff_t)len;

        return (ssize_t)len;
    }
    else
    {
        RNIC_ERROR_LOG(ACPU_PID_RNIC, "RNIC_ReadIdleTimerOutFile:copy_to_user ERR!");
        return -EPERM;
    }
}


/*****************************************************************************
 函 数 名  : RNIC_WriteIdleTimerOutFile
 功能描述  : idel_timerout虚拟文件写实现
 输入参数  : file ----- 文件句柄
             buf  ----- 用户空间数据
             lLength -- 用户数据长度
             ppos - ----文件偏移，参数未使用
 输出参数  : 无
 返 回 值  : 成功或失败

 修改历史      :
  1.日    期   : 2012年01月30日
    作    者   : S62952
    修改内容   : 新生成函数
  2.日    期   : 2012年8月10日
    作    者   : y00213812
    修改内容   : DTS2012082204471, TQE清理，代码冗余
*****************************************************************************/
ssize_t RNIC_WriteIdleTimerOutFile(
    struct file                        *file,
    const char __user                  *buf,
    size_t                              len,
    loff_t                             *ppos
)
{
    RNIC_DIAL_MODE_STRU                *pstDialMode;
    RNIC_DIAL_MODE_STRU                 stDialMode;
    VOS_CHAR                            acIdleTimeTemp[RNIC_IDLETIMEROUT_FILE_LEN];

    PS_MEM_SET(acIdleTimeTemp, 0x00, RNIC_IDLETIMEROUT_FILE_LEN);

    if (NULL == buf)
    {
        RNIC_ERROR_LOG(ACPU_PID_RNIC, "RNIC_WriteIdleTimerOutFile:buff is null");
        return -EFAULT;
    }

    if (len >= RNIC_IDLETIMEROUT_FILE_LEN)
    {
        RNIC_ERROR_LOG1(ACPU_PID_RNIC, "RNIC_WriteIdleTimerOutFile:len is!", len);
        return -ENOSPC;
    }

    /*拷贝用户空间数据到内核空间上面*/
    if (copy_from_user((VOS_VOID *)acIdleTimeTemp, (VOS_VOID *)buf, len) > 0)
    {
        RNIC_ERROR_LOG(ACPU_PID_RNIC, "RNIC_WriteIdleTimerOutFile:copy_from_user ERR!");
        return -EFAULT;
    }

    acIdleTimeTemp[len]= '\0';

    stDialMode.ulIdleTime = RNIC_TransferStringToInt(acIdleTimeTemp);

    /* 获取按需拨号的模式以及时长的地址 */
    pstDialMode                         = RNIC_GetDialModeAddr();

    if (RNIC_DIAL_MODE_DEMAND_DISCONNECT == pstDialMode->enDialMode)
    {

        /* PDP激活，且与上次设置的时长不一致，需要启动拨号断开定时器 */
        if ( pstDialMode->ulIdleTime != stDialMode.ulIdleTime)
        {
            RNIC_StopTimer(TI_RNIC_DEMAND_DIAL_DISCONNECT);
            RNIC_StartTimer(TI_RNIC_DEMAND_DIAL_DISCONNECT, TI_RNIC_DEMAND_DIAL_DISCONNECT_LEN);
        }
    }

    pstDialMode->ulIdleTime             = stDialMode.ulIdleTime;


    RNIC_SendDialInfoMsg(ID_RNIC_MNTN_IDLE_TIMEOUT_INFO);

    return (ssize_t)len;
}

/*****************************************************************************
 函 数 名  : RNIC_InitIdleTimerOutFile
 功能描述  : ideltimerout虚拟文件初始化
 输入参数  : proc_dir_entry *pstParentFileDirEntry -- 父目录的入口
 输出参数  : 无
 返 回 值  : 初始化结果

 修改历史      :
  1.日    期   : 2012年01月30日
    作    者   : S62952
    修改内容   : 新生成函数

*****************************************************************************/
VOS_UINT32 RNIC_InitIdleTimerOutFile(struct proc_dir_entry *pstParentFileDirEntry)
{
    struct proc_dir_entry              *pstIdleTimeOutEntry;

    if (VOS_NULL_PTR == pstParentFileDirEntry )
    {
        /*创建IdleTimeOut虚拟文件*/
        pstIdleTimeOutEntry                 = proc_create("dial/idle_timeout",
                                                         /*lint -e960 修改人:l60609;原因:64bit*/
                                                         RNIC_VFILE_CRT_LEVEL,
                                                         /*lint +e960 修改人:l60609;原因:64bit*/
                                                         pstParentFileDirEntry,
                                                         &g_stIdleTimerOutFileOps);

        if (VOS_NULL_PTR == pstIdleTimeOutEntry)
        {
            RNIC_ERROR_LOG(ACPU_PID_RNIC, "RNIC_InitIdleTimerOutFile:pstIdleTimeOutEntry is null!");

            return VOS_ERR;
        }
    }
    else
    {
        /*创建IdleTimeOut虚拟文件*/
        pstIdleTimeOutEntry                 = proc_create("idle_timeout",
                                                         /*lint -e960 修改人:l60609;原因:64bit*/
                                                         RNIC_VFILE_CRT_LEVEL,
                                                         /*lint +e960 修改人:l60609;原因:64bit*/
                                                         pstParentFileDirEntry,
                                                         &g_stIdleTimerOutFileOps);

        if (VOS_NULL_PTR == pstIdleTimeOutEntry)
        {
            RNIC_ERROR_LOG(ACPU_PID_RNIC, "RNIC_InitIdleTimerOutFile:pstIdleTimeOutEntry is null!");

            return VOS_ERR;
        }
    }

    return VOS_OK;
}

/*****************************************************************************
 函 数 名  : RNIC_ReadDialEventReportFile
 功能描述  : dial_event_report虚拟文件读实现
 输入参数  : file --- 文件句柄
             buf  --- 用户空间
             ppos --- 文件偏移，参数未使用
 输出参数  : 无
 返 回 值  : 成功或失败

 修改历史      :
  1.日    期   : 2012年01月30日
    作    者   : S62952
    修改内容   : 新生成函数

*****************************************************************************/
ssize_t RNIC_ReadDialEventReportFile(
    struct file                        *file,
    char __user                        *buf,
    size_t                              len,
    loff_t                             *ppos
)
{
    RNIC_DIAL_MODE_STRU                *pstDialMode;
    VOS_CHAR                            acDialEventTemp[RNIC_EVENTFLAG_FILE_LEN];
    VOS_UINT32                          ulDialEventLen;

    if (*ppos > 0)
    {
        RNIC_ERROR_LOG(ACPU_PID_RNIC, "RNIC_ReadDialEventReportFile:ppos err!");
        return 0;
    }

    PS_MEM_SET(acDialEventTemp, 0x00, RNIC_EVENTFLAG_FILE_LEN);


    /* 获取按需拨号的模式以及时长的地址 */
    pstDialMode                         = RNIC_GetDialModeAddr();

    VOS_sprintf(acDialEventTemp, "%d", pstDialMode->enEventReportFlag);

    ulDialEventLen = VOS_StrLen(acDialEventTemp);

    len            = PS_MIN(len, ulDialEventLen);

    /*拷贝内核空间数据到用户空间上面*/
    if (0 == copy_to_user(buf, (VOS_VOID *)acDialEventTemp, len))
    {
        *ppos += (loff_t)len;

        return (ssize_t)len;
    }
    else
    {
        RNIC_ERROR_LOG(ACPU_PID_RNIC, "RNIC_ReadDialEventReportFile:copy_to_user err!");
        return -EPERM;
    }

}


/*****************************************************************************
 函 数 名  : RNIC_WriteDialEventReportFile
 功能描述  : dialeventreport虚拟文件写实现
 输入参数  : file ----- 文件句柄
             buf  ----- 用户空间数据
             lLength -- 用户数据长度
             ppos - ----文件偏移，参数未使用
 输出参数  : 无
 返 回 值  : 成功或失败

 修改历史      :
  1.日    期   : 2012年01月30日
    作    者   : S62952
    修改内容   : 新生成函数
  2.日    期   : 2012年8月10日
    作    者   : y00213812
    修改内容   : DTS2012082204471, TQE清理，代码冗余
*****************************************************************************/
ssize_t RNIC_WriteDialEventReportFile(
    struct file                        *file,
    const char __user                  *buf,
    size_t                              len,
    loff_t                             *ppos
)
{
    RNIC_DIAL_MODE_STRU                *pstDialMode;
    RNIC_DIAL_MODE_STRU                 stDialMode;
    VOS_CHAR                            acDialEventTemp[RNIC_EVENTFLAG_FILE_LEN];

    PS_MEM_SET(acDialEventTemp, 0x00, RNIC_EVENTFLAG_FILE_LEN);

    if (NULL == buf)
    {
        RNIC_ERROR_LOG(ACPU_PID_RNIC, "RNIC_WriteDialEventReportFile:buff is null");
        return -EFAULT;
    }

    if (len >= RNIC_EVENTFLAG_FILE_LEN)
    {
        RNIC_ERROR_LOG1(ACPU_PID_RNIC, "RNIC_WriteDialEventReportFile:len is!",len);
        return -ENOSPC;
    }

    /*拷贝用户空间数据到内核空间上面*/
    if (copy_from_user((VOS_VOID *)acDialEventTemp, (VOS_VOID *)buf, len) > 0)
    {
        RNIC_ERROR_LOG(ACPU_PID_RNIC, "RNIC_WriteDialEventReportFile:copy_from_user ERR!");
        return -EFAULT;
    }

    acDialEventTemp[len] = '\0';

    PS_PRINTF("RNIC_WriteDialEventReportFile:acDialEventTemp %s len is %d\r\n", acDialEventTemp, len);

    stDialMode.enEventReportFlag    = RNIC_TransferStringToInt(acDialEventTemp);

    /* 获取按需拨号的模式以及时长的地址 */
    pstDialMode                         = RNIC_GetDialModeAddr();

    /* 保存拨号模式到上下文中 */
    pstDialMode->enEventReportFlag      = stDialMode.enEventReportFlag;

    RNIC_SendDialInfoMsg(ID_RNIC_MNTN_EVENT_REPORT_INFO);

    return (ssize_t)len;
}
/*****************************************************************************
 函 数 名  : RNIC_InitDialEventReportFiles
 功能描述  : proc_dir_entry *pstParentFileDirEntry -- 父目录的入口
 输入参数  : proc_dir_entry *pstParentFileDirEntry
 输出参数  : 无
 返 回 值  : 初始化结果

 修改历史      :
  1.日    期   : 2012年01月30日
    作    者   : S62952
    修改内容   : 新生成函数

*****************************************************************************/
VOS_UINT32 RNIC_InitDialEventReportFile(struct proc_dir_entry *pstParentFileDirEntry)
{
    struct proc_dir_entry              *pstDialEventReportEntry;

    if (VOS_NULL_PTR == pstParentFileDirEntry)
    {
        /*创建dial_event_report虚拟文件*/
        pstDialEventReportEntry             = proc_create("dial/dial_event_report",
                                                          /*lint -e960 修改人:l60609;原因:64bit*/
                                                          RNIC_VFILE_CRT_LEVEL,
                                                          /*lint +e960 修改人:l60609;原因:64bit*/
                                                          pstParentFileDirEntry,
                                                          &g_stDialEventReportFileOps);

        if (VOS_NULL_PTR == pstDialEventReportEntry)
        {
            RNIC_ERROR_LOG(ACPU_PID_RNIC, "RNIC_InitDialEventReportFile:pstDialEventReportEntry is null!");

            return VOS_ERR;
        }

    }
    else
    {

        /*创建dial_event_report虚拟文件*/
        pstDialEventReportEntry             = proc_create("dial_event_report",
                                                          /*lint -e960 修改人:l60609;原因:64bit*/
                                                          RNIC_VFILE_CRT_LEVEL,
                                                          /*lint +e960 修改人:l60609;原因:64bit*/
                                                          pstParentFileDirEntry,
                                                          &g_stDialEventReportFileOps);

        if (VOS_NULL_PTR == pstDialEventReportEntry)
        {
            RNIC_ERROR_LOG(ACPU_PID_RNIC, "RNIC_InitDialEventReportFile:pstDialEventReportEntry is null!");

            return VOS_ERR;
        }
    }

    return VOS_OK;
}

/*****************************************************************************
 函 数 名  : RNIC_InitDemandDialFile
 功能描述  : 初始化按需拨文件
 输入参数  : VOS_VOID
 输出参数  : 无
 返 回 值  : VOS_UINT32
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2012年2月1日
    作    者   : w00199382
    修改内容   : 新生成函数

*****************************************************************************/
VOS_UINT32 RNIC_InitDemandDialFile(VOS_VOID)
{
    struct proc_dir_entry              *stProcDemandDialDir;
    VOS_UINT32                          ulRlst;
    struct path                         path;
    int                                 error = 0;

    error = kern_path("/proc/dial", LOOKUP_FOLLOW, &path);
    if (error)
    {

        stProcDemandDialDir = proc_mkdir("dial", VOS_NULL_PTR);
        if (VOS_NULL_PTR == stProcDemandDialDir)
        {
            RNIC_ERROR_LOG(ACPU_PID_RNIC, "RNIC_InitDemandDialFile:proc_mkdir Fail!");
            return VOS_ERR;
        }
    }
    else
    {
        stProcDemandDialDir = VOS_NULL_PTR;
        RNIC_NORMAL_LOG(ACPU_PID_RNIC, "RNIC_InitDemandDialFile:kern_path proc/dial is exist!");
    }

    ulRlst                              = RNIC_InitOnDemandFile(stProcDemandDialDir);

    if (VOS_ERR == ulRlst)
    {

        RNIC_ERROR_LOG(ACPU_PID_RNIC, "RNIC_InitDialEventReportFile:RNIC_InitOnDemandFile err!");

        return VOS_ERR;
    }

    ulRlst                              = RNIC_InitIdleTimerOutFile(stProcDemandDialDir);

    if (VOS_ERR == ulRlst)
    {


        RNIC_ERROR_LOG(ACPU_PID_RNIC, "RNIC_InitDialEventReportFile:RNIC_InitIdleTimerOutFile err!");

        return VOS_ERR;
    }

    ulRlst                              = RNIC_InitDialEventReportFile(stProcDemandDialDir);

    if (VOS_ERR == ulRlst)
    {

        RNIC_ERROR_LOG(ACPU_PID_RNIC, "RNIC_InitDialEventReportFile:RNIC_InitDialEventReportFile err!");

        return VOS_ERR;
    }

    return VOS_OK;
}


#ifdef __cplusplus
    #if __cplusplus
        }
    #endif
#endif
