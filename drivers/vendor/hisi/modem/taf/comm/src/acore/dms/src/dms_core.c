

/*****************************************************************************
  1 头文件包含
*****************************************************************************/

#include "vos.h"
#include "msp_errno.h"
#include <dms.h>
#include "dms_core.h"
#include "PsLib.h"
#include "TafNvInterface.h"
#include "NVIM_Interface.h"
#include <product_config.h>


#ifdef __cplusplus
#if __cplusplus
extern "C" {
#endif
#endif


/*****************************************************************************
    协议栈打印打点方式下的.C文件宏定义
*****************************************************************************/

/*lint -e767 -e960*/
#define THIS_FILE_ID                    PS_FILE_ID_DMS_CORE_C
/*lint +e767 +e960*/


/*****************************************************************************
  2 全局变量定义
*****************************************************************************/

DMS_MAIN_INFO                           g_stDmsMainInfo = {0};

#if (VOS_OS_VER == VOS_WIN32)
static const struct file_operations     g_stPortCfgOps;
#else
static const struct file_operations     g_stPortCfgOps =
{
    .owner      = THIS_MODULE,
    .write      = DMS_WritePortCfgFile,
    .read       = DMS_ReadPortCfgFile,
};
#endif

#if (VOS_OS_VER == VOS_WIN32)
static const struct file_operations g_stGetSliceOps;
#else
static const struct file_operations g_stGetSliceOps      =
{
    .owner      = THIS_MODULE,
    .read       = DMS_ReadGetSliceFile,
};
#endif

#if (VOS_OS_VER == VOS_WIN32)
static const struct file_operations     g_stModemStatus;
#else
static const struct file_operations     g_stModemStatus =
{
    .owner      = THIS_MODULE,
    .read       = DMS_ReadModemStatusFile,
};
#endif

DMS_NLK_ENTITY_STRU                     g_stDmsNlkEntity = {0};

#if (VOS_OS_VER == VOS_WIN32)
static struct netlink_kernel_cfg        g_stDmsNlkCfg;
#else
#if (LINUX_VERSION_CODE >= KERNEL_VERSION(3, 10, 0))
static struct netlink_kernel_cfg        g_stDmsNlkCfg =
{
    .input      = DMS_NLK_Input,
};
#endif /* LINUX_VERSION_CODE >= KERNEL_VERSION(3, 10, 0) */
#endif /* VOS_OS_VER == VOS_WIN32 */

VOS_UINT8                               g_ucDmsPrintModemLogType = 0;

/*****************************************************************************
  3 外部函数声明
*****************************************************************************/

extern VOS_VOID At_MsgProc(MsgBlock* pMsg);
extern VOS_UINT32 At_PidInit(enum VOS_INIT_PHASE_DEFINE enPhase);
extern void *hisi_io_memcpy(void *dest, const void *src, unsigned int count);
/* 解决pclint问题 */

/*****************************************************************************
  3 函数实现
*****************************************************************************/
/*****************************************************************************
 函 数 名  : DMS_ReadPortDebugCfgNV
 功能描述  : 读取端口 Debug 配置相关的NV项
 输入参数  : 无
 输出参数  : 无
 返 回 值  : VOS_VOID
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2014年06月03日
    作    者   : n00269697
    修改内容   : 新生成函数
*****************************************************************************/
VOS_VOID DMS_ReadPortDebugCfgNV(VOS_VOID)
{
    TAF_NV_PORT_DEBUG_CFG_STRU          stPortDebugNVCfg;
    VOS_UINT32                          ulAppVcomPortIdMask;
    VOS_UINT32                          ulDebugLevel;

    VOS_MemSet(&stPortDebugNVCfg, 0, sizeof(TAF_NV_PORT_DEBUG_CFG_STRU));

    /* 读取NV项 */
    if (NV_OK != NV_ReadEx(MODEM_ID_0,
                           en_NV_Item_DMS_DEBUG_CFG,
                          &stPortDebugNVCfg,
                           sizeof(TAF_NV_PORT_DEBUG_CFG_STRU)))
    {
        return;
    }

    ulAppVcomPortIdMask = stPortDebugNVCfg.ulAppVcomPortIdMask;
    ulDebugLevel        = stPortDebugNVCfg.ulDebugLevel;

    APP_VCOM_SendDebugNvCfg(ulAppVcomPortIdMask, ulDebugLevel);

    return;
}

/*****************************************************************************
 函 数 名  : DMS_ReadGetModemLogCfgNV
 功能描述  : 读取配置是否可以得到modem log的NV项中的值
 输入参数  : 无
 输出参数  : 无
 返 回 值  : VOS_VOID
 调用函数  :
 被调函数  :

 修改历史     :
 1.日    期   : 2015年10月17日
   作    者   : w00316404
   修改内容   : 新生成函数
*****************************************************************************/
VOS_VOID DMS_ReadGetModemLogCfgNV(VOS_VOID)
{
    TAF_NV_PRINT_MODEM_LOG_TYPE_STRU    stPrintModemLogType;

    VOS_MemSet(&stPrintModemLogType, 0x00, sizeof(stPrintModemLogType));

    /* 读取NV项 */
    if (NV_OK != NV_Read(en_NV_Item_Print_Modem_Log_Type,
                         &stPrintModemLogType,
                         sizeof(TAF_NV_PRINT_MODEM_LOG_TYPE_STRU)))
    {
        return;
    }

    DMS_SET_PRINT_MODEM_LOG_TYPE(stPrintModemLogType.ucPrintModemLogType);

    return;
}

/*****************************************************************************
 函 数 名  : initDmsMainInfo
 功能描述  : 初始化DMS全局变量
 输入参数  :

 输出参数  :
 返 回 值  :
 调用函数  :
 被调函数  :
 修改历史  :
   1.日    期  : 2012年8月27日
     作    者  : heliping
     修改内容  : Creat Function
   2.日    期  : 2013年07月222日
     作    者  : j00177245
     修改内容  : 清理编译warning
   3.日    期  : 2013年09月03日
     作    者  : z60575
     修改内容  : DTS2013090208292,NVE初始化只做一次
   4.日    期  : 2014年08月25日
     作    者  : j00174725
     修改内容  : DTS2014082200355 proc/portcfg权限修改
   5.日    期   : 2015年6月25日
     作    者   : l00198894
     修改内容   : TSTS
   6.日    期   : 2015年10月17日
     作    者   : w00316404
     修改内容   : 控制是否打印modem log
   7.日    期   : 2016年01月22日
     作    者   : z00301431
     修改内容   : DTS2015103001118,set modemstatus
*****************************************************************************/
VOS_VOID DMS_Init(VOS_VOID)
{
    VOS_UINT32                          ulport;

    VOS_MemSet(g_astDmsSdmInfoTable, 0, sizeof(g_astDmsSdmInfoTable));

    g_stDmsMainInfo.pfnRdDataCallback  = NULL;
    g_stDmsMainInfo.pfnConnectCallBack = NULL;

    /*初始化所有端口的handle*/
    for (ulport = 0; ulport < DMS_PHY_BEAR_LAST; ulport++)
    {
        g_stDmsMainInfo.stPhyProperty[ulport].lPortHandle = UDI_INVALID_HANDLE;
    }

    /*物理通道默认属性，存在多个物理通道有能力对应一个逻辑通道*/
    g_stDmsMainInfo.stPhyProperty[DMS_PHY_BEAR_USB_PCUI].enLogicChan  = DMS_CHANNEL_AT;
    g_stDmsMainInfo.stPhyProperty[DMS_PHY_BEAR_USB_CTRL].enLogicChan  = DMS_CHANNEL_AT;
    g_stDmsMainInfo.stPhyProperty[DMS_PHY_BEAR_USB_PCUI2].enLogicChan = DMS_CHANNEL_AT;



    /* 初始化AT通道使用的静态内存 */
    Dms_StaticBufInit();


    DMS_ReadPortDebugCfgNV();

    mdrv_usb_reg_enablecb(DMS_UsbEnableCB);
    mdrv_usb_reg_disablecb(DMS_UsbDisableCB);

    wake_lock_init(&g_stDmsMainInfo.stwakelock, WAKE_LOCK_SUSPEND, "dms_wakelock");

    DMS_ReadGetModemLogCfgNV();

    return;
}


/*****************************************************************************
 函 数 名  : DMS_GetConnStaFun
 功能描述  : 获取通道连接处理函数
 输入参数  :

 输出参数  :
 返 回 值  : VOS_NULL/回调函数
 调用函数  :
 被调函数  :
 修改历史  :
   1.日    期  : 2012年8月27日
     作    者  : heliping
     修改内容  : Creat Function
*****************************************************************************/
DMS_CONNECT_STA_PFN DMS_GetConnStaFun(VOS_VOID)
{
    return (DMS_GetMainInfo()->pfnConnectCallBack);
}

/*****************************************************************************
 函 数 名  : DMS_SetConnStaCB
 功能描述  : 通道连接事件处理注册函数
 输入参数  : pfnReg: 回调函数指针

 输出参数  :
 返 回 值  :
 调用函数  :
 被调函数  :
 修改历史  :
   1.日    期  : 2012年8月27日
     作    者  : heliping
     修改内容  : Creat Function
*****************************************************************************/
VOS_VOID DMS_SetConnStaCB(DMS_CONNECT_STA_PFN pfnReg)
{
    DMS_MAIN_INFO                      *pstMainInfo = DMS_GetMainInfo();

    if (NULL == pfnReg)
    {
        return;
    }

    pstMainInfo->pfnConnectCallBack = pfnReg;
    return;
}

/*****************************************************************************
 函 数 名  : DMS_GetDataReadFun
 功能描述  : 获取读回调函数
 输入参数  :
 输出参数  :
 返 回 值  : 回调函数指针
 调用函数  :
 被调函数  :
 修改历史  :
   1.日    期  : 2012年8月27日
     作    者  : heliping
     修改内容  : Creat Function
*****************************************************************************/
DMS_READ_DATA_PFN DMS_GetDataReadFun(VOS_VOID)
{
    return g_stDmsMainInfo.pfnRdDataCallback;
}

/*****************************************************************************
 函 数 名  : DMS_GetMainInfo
 功能描述  : 获取DMS全局变量指针
 输入参数  :
 输出参数  :
 返 回 值  : 全局变量指针
 调用函数  :
 被调函数  :
 修改历史  :
   1.日    期  : 2012年8月27日
     作    者  : heliping
     修改内容  : Creat Function
*****************************************************************************/
DMS_MAIN_INFO* DMS_GetMainInfo(VOS_VOID)
{
    return &g_stDmsMainInfo;
}

/*****************************************************************************
 函 数 名  : DMS_GetPhyBearProperty
 功能描述  : 获取物理通道数据结构指针
 输入参数  :
 输出参数  :
 返 回 值  : 结构体指针
 调用函数  :
 被调函数  :
   1.日    期  : 2012年8月27日
     作    者  : heliping
     修改内容  : Creat Function
*****************************************************************************/
 DMS_PHY_BEAR_PROPERTY_STRU* DMS_GetPhyBearProperty(DMS_PHY_BEAR_ENUM enPhyBear)
{
    return &(DMS_GetMainInfo()->stPhyProperty[enPhyBear]);
}

/*****************************************************************************
 函 数 名  : DMS_UsbDisableCB
 功能描述  : USB拔出事件处理函数
 输入参数  :
 输出参数  :
 返 回 值  :
 调用函数  :
 被调函数  :
 修改历史  :
   1.日    期  : 2012年8月27日
     作    者  : heliping
     修改内容  : Creat Function
   2.日    期  : 2012年8月27日
     作    者  : marenkun
     修改内容  : 读取at server nv项，判断是否关闭pcui&Ctrl口
   3.日    期  : 2013年09月03日
     作    者  : z60575
     修改内容  : DTS2013090208292,NVE初始化只做一次
   4.日    期   : 2015年5月22日
     作    者   : l00198894
     修改内容   : TSTS
*****************************************************************************/
VOS_VOID DMS_UsbDisableCB(VOS_VOID)
{
    VOS_UINT32                          ulRet;

    DMS_DBG_SDM_FUN(DMS_SDM_USB_DISABLE, 0, 0, 0);

    /* nv值为1表示有at sever，非1表示无at sever，无at sever关闭pcui和ctrl口 */
    if (VOS_TRUE == g_stDmsMainInfo.bPortOpenFlg)
    {
        /* 关闭PCUI通道 */
        ulRet = DMS_VcomPcuiClose();
        if(ERR_MSP_SUCCESS!=ulRet)
        {
            DMS_DBG_SDM_FUN(DMS_SDM_USB_DISABLE_ERR,0, 0, 3);
        }

        /* 关闭CTRL通道 */
        ulRet = DMS_VcomCtrlClose();
        if(ERR_MSP_SUCCESS!=ulRet)
        {
            DMS_DBG_SDM_FUN(DMS_SDM_USB_DISABLE_ERR,0, 0, 5);
        }

        /* 关闭PCUI2通道 */
        ulRet = DMS_VcomPcui2Close();
        if(ERR_MSP_SUCCESS != ulRet)
        {
            DMS_DBG_SDM_FUN(DMS_SDM_USB_DISABLE_ERR,0, 0, 6);
        }

    }

    /* 关闭NDIS CTRL通道 */
    ulRet =  DMS_NcmClose();
    if(ERR_MSP_SUCCESS!=ulRet)
    {
        DMS_DBG_SDM_FUN(DMS_SDM_USB_DISABLE_ERR,0, 0, 4);
    }

    return ;
}

/*****************************************************************************
 函 数 名  : DMS_UsbEnableCB
 功能描述  : USB枚举完成处理函数
 输入参数  :
 输出参数  :
 返 回 值  :
 调用函数  :
 被调函数  :
 修改历史  :
   1.日    期  : 2012年8月27日
     作    者  : heliping
     修改内容  : Creat Function
   2.日    期  : 2012年8月27日
     作    者  : marenkun
     修改内容  : 读取at server nv项，判断是否打开pcui&Ctrl口
   3.日    期  : 2013年09月03日
     作    者  : z60575
     修改内容  : DTS2013090208292,NVE初始化只做一次
   4.日    期   : 2015年5月22日
     作    者   : l00198894
     修改内容   : TSTS
*****************************************************************************/
VOS_VOID DMS_UsbEnableCB(VOS_VOID)
{
    VOS_UINT32                          ulRet;
    NVE_INFO_S                          stAtServerNv;
#if defined (CHIP_BB_HI6210)
    VOS_INT32                           lReadNvRet;
#endif

    VOS_MemSet(&stAtServerNv, 0, sizeof(NVE_INFO_S));
    VOS_MemCpy(stAtServerNv.nv_name, "ATSERV", sizeof("ATSERV"));
    stAtServerNv.nv_number      = NVE_AT_SERVER_INDEX;
    stAtServerNv.nv_operation   = NVE_READ_OPERATE;
    stAtServerNv.valid_size     = 1;

    DMS_DBG_SDM_FUN(DMS_SDM_USB_ENABLE, 0, 0, 0);

    /* NVE只读取一次，读取后不再读取 */
    if (VOS_FALSE == g_stDmsMainInfo.bPortCfgFlg)
    {
#if defined (CHIP_BB_HI6210)
        lReadNvRet = DRV_NVE_ACCESS(&stAtServerNv);
        g_dms_debug_atserv_nv_info.lOperatRet       = lReadNvRet;
#endif
        g_dms_debug_atserv_nv_info.ulNvValue        = stAtServerNv.nv_data[0];

        g_stDmsMainInfo.bPortCfgFlg                 = VOS_TRUE;

        /* nv值为1表示有at sever，非1表示无at sever，无at sever打开pcui和ctrl口 */
        if ((1 != stAtServerNv.nv_data[0])
#if defined (CHIP_BB_HI6210)
            || (ERR_MSP_SUCCESS != lReadNvRet)
#endif
            )
        {
            g_stDmsMainInfo.ulPortCfgValue = DMS_TEST_MODE;
        }
        else
        {
            g_stDmsMainInfo.ulPortCfgValue = DMS_NORMAL_MODE;
        }
    }

    if (DMS_TEST_MODE == g_stDmsMainInfo.ulPortCfgValue)
    {
        g_stDmsMainInfo.bPortOpenFlg = VOS_TRUE;

        /*打开 AT PCUI 通道*/
        ulRet = DMS_VcomPcuiOpen();
        if (ERR_MSP_SUCCESS != ulRet)
        {
            DMS_DBG_SDM_FUN(DMS_SDM_USB_ENABLE_ERR, 0, 0, 3);
        }

        /*打开 AT CTRL 通道*/
        ulRet = DMS_VcomCtrlOpen();
        if (ERR_MSP_SUCCESS != ulRet)
        {
            DMS_DBG_SDM_FUN(DMS_SDM_USB_ENABLE_ERR, 0, 0, 5);
        }

        /*打开 AT PCUI2 通道*/
        ulRet = DMS_VcomPcui2Open();
        if (ERR_MSP_SUCCESS != ulRet)
        {
            DMS_DBG_SDM_FUN(DMS_SDM_USB_ENABLE_ERR, 0, 0, 6);
        }
    }

    /*打开 NDIS CTRL 通道*/
    ulRet = DMS_NcmOpen();
    if (ERR_MSP_SUCCESS != ulRet)
    {
        DMS_DBG_SDM_FUN(DMS_SDM_USB_ENABLE_ERR, 0, 0, 4);
    }

    g_ulNdisCfgFlag = 1;

    return ;
}

/*****************************************************************************
 函 数 名  : DMS_GetPortHandle
 功能描述  : 获取物理端口句柄
 输入参数  : enPhyBear --- 物理端口号
 输出参数  : 无
 返 回 值  : UDI_HANDLE
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2014年5月4日
    作    者   : A00165503
    修改内容   : 新生成函数
*****************************************************************************/
UDI_HANDLE DMS_GetPortHandle(DMS_PHY_BEAR_ENUM enPhyBear)
{
    return (DMS_GetMainInfo()->stPhyProperty[enPhyBear].lPortHandle);
}

/*****************************************************************************
 函 数 名  : DMS_DsFidInit
 功能描述  : dms FID 初始化函数
 输入参数  :

 输出参数  :
 返 回 值  :
 调用函数  :
 被调函数  :
 修改历史  :
   1.日    期  : 2012年8月27日
     作    者  : heliping
     修改内容  : Creat Function
*****************************************************************************/
VOS_UINT32 DMS_DsFidInit(enum VOS_INIT_PHASE_DEFINE ip)
{
    VOS_UINT32 ulRelVal = 0;

    switch (ip)
    {
    case VOS_IP_LOAD_CONFIG:

        DMS_Init();

        ulRelVal = VOS_RegisterPIDInfo(WUEPS_PID_AT, (Init_Fun_Type) At_PidInit, (Msg_Fun_Type) At_MsgProc);
        if (ulRelVal != VOS_OK)
        {
            return VOS_ERR;
        }

        ulRelVal = VOS_RegisterTaskPrio(MSP_APP_DS_FID, DMS_APP_DS_TASK_PRIORITY);
        if (ulRelVal != VOS_OK)
        {
            return VOS_ERR;
        }

        break;

    default:
        break;
    }

    return VOS_OK;
}

/*****************************************************************************
 函 数 名  : DMS_InitPorCfgFile
 功能描述  : OnDemand虚拟文件读实现
 输入参数  : 无
 输出参数  : 无
 返 回 值  : 成功或失败

 修改历史      :
  1.日    期   : 2013年10月25日
    作    者   : z60575
    修改内容   : 新生成函数
  2.日    期   : 2014年08月25日
    作    者   : j00174725
    修改内容   : DTS2014082200355
*****************************************************************************/
VOS_INT __init DMS_InitPorCfgFile(VOS_VOID)
{
    printk("DMS_InitPorCfgFile,entry,%u",VOS_GetSlice());

    g_stDmsMainInfo.bPortCfgFlg     = VOS_FALSE;
    g_stDmsMainInfo.bPortOpenFlg    = VOS_FALSE;
    g_stDmsMainInfo.ulPortCfgValue  = DMS_TEST_MODE;

    /*lint -e960 */
    if (VOS_NULL_PTR == proc_create("portcfg", DMS_VFILE_CRT_LEVEL, VOS_NULL_PTR, &g_stPortCfgOps))
    {
        DMS_LOG_ERROR("DMS_InitPorCfgFile: proc_create return NULL.\n");
        return -ENOMEM;
    }
    /*lint +e960 */

    printk("DMS_InitPorCfgFile,exit,%u",VOS_GetSlice());

    return 0;
}

/*****************************************************************************
 函 数 名  : DMS_ReadPortCfgFile
 功能描述  : PortCfg虚拟文件读实现
 输入参数  : file --- 文件句柄
             buf  --- 用户空间
             ppos --- 文件偏移，参数未使用
 输出参数  : 无
 返 回 值  : 成功或失败

 修改历史      :
  1.日    期   : 2013年10月25日
    作    者   : z6057
    修改内容   : 新生成函数
*****************************************************************************/
ssize_t DMS_ReadPortCfgFile(
    struct file                        *file,
    char __user                        *buf,
    size_t                              len,
    loff_t                             *ppos
)
{
    VOS_CHAR                            acModeTemp[DMS_PORTCFG_FILE_LEN];
    VOS_UINT32                          ulLength;

    if (*ppos > 0)
    {
        return 0;
    }

    VOS_MemSet(acModeTemp, 0x00, DMS_PORTCFG_FILE_LEN);

    VOS_sprintf((VOS_CHAR *)acModeTemp, "%d", g_stDmsMainInfo.ulPortCfgValue);

    ulLength        = VOS_StrLen(acModeTemp);
    len             = PS_MIN(len, ulLength);

    /*拷贝内核空间数据到用户空间上面*/
    if (0 == copy_to_user(buf,(VOS_VOID *)acModeTemp, (VOS_ULONG)len))
    {
        *ppos += (loff_t)len;

        return (ssize_t)len;
    }
    else
    {
        return -EPERM;
    }

}

/*****************************************************************************
 函 数 名  : DMS_WritePortCfgFile
 功能描述  : PortCfg虚拟文件写实现
 输入参数  : file ----- 文件句柄
             buf  ----- 用户空间数据
             lLength -- 用户数据长度
             ppos - ----文件偏移，参数未使用
 输出参数  : 无
 返 回 值  : 成功或失败

 修改历史      :
  1.日    期   : 2013年10月25日
    作    者   : z6057
    修改内容   : 新生成函数
*****************************************************************************/
ssize_t DMS_WritePortCfgFile(
    struct file                        *file,
    const char __user                  *buf,
    size_t                              len,
    loff_t                             *ppos
)
{
    VOS_CHAR                            acModeTemp[DMS_PORTCFG_FILE_LEN];
    VOS_UINT32                          ulStrLen;
    VOS_UINT32                          i;
    VOS_UINT32                          ulValue;

    ulValue = 0;
    VOS_MemSet(acModeTemp, 0x00, DMS_PORTCFG_FILE_LEN);

    if (NULL == buf)
    {
        return -EFAULT;
    }

    if (len >= DMS_PORTCFG_FILE_LEN)
    {
        return -ENOSPC;
    }

    /*拷贝用户空间数据到内核空间上面*/
    if (copy_from_user((VOS_VOID *)acModeTemp, (VOS_VOID *)buf, (VOS_ULONG)len) > 0)
    {
        return -EFAULT;
    }

    acModeTemp[len] = '\0';

    ulStrLen = VOS_StrLen(acModeTemp);

    for ( i = 0; i < ulStrLen; i++ )
    {
        if ( (acModeTemp[i] >= '0') && (acModeTemp[i] <= '9') )
        {
            ulValue = (ulValue * 10) + (acModeTemp[i] - '0');
        }
    }

    g_stDmsMainInfo.ulPortCfgValue  = ulValue;

    /* 如果已经写过这个文件，则以写的值为准，后续不需要再读NVE */
    g_stDmsMainInfo.bPortCfgFlg     = TRUE;

    return (ssize_t)len;
}

#if (VOS_LINUX == VOS_OS_VER)
#if (FEATURE_ON == FEATURE_DELAY_MODEM_INIT)
module_init(DMS_InitPorCfgFile);
module_init(DMS_InitGetSliceFile);
#endif
#endif

/*****************************************************************************
 函 数 名  : DMS_RegOmChanDataReadCB
 功能描述  : 注册OM通道数据接收回调
 输入参数  : enChan --- 逻辑通道
             pFunc  --- 函数指针
 输出参数  : 无
 返 回 值  : VOS_ERR/VOS_OK
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2014年7月5日
    作    者   : A00165503
    修改内容   : 新生成函数
*****************************************************************************/
VOS_UINT32 DMS_RegOmChanDataReadCB(
    DMS_OM_CHAN_ENUM_UINT32             enChan,
    DMS_OM_CHAN_DATA_READ_CB_FUNC       pFunc
)
{
    DMS_NLK_OM_CHAN_PROPERTY_STRU      *pstOmChanProp = VOS_NULL_PTR;

    /* 检查通道号和函数指针 */
    if ((enChan >= DMS_OM_CHAN_BUTT) || (VOS_NULL_PTR == pFunc))
    {
        printk(KERN_ERR "[%s][LINE: %d] Invalid channel %d.\n",
            __func__, __LINE__, (VOS_INT)enChan);
        return VOS_ERR;
    }

    /* 设置通道数据回调函数 */
    pstOmChanProp = DMS_GET_NLK_OM_CHAN_PROP(enChan);
    pstOmChanProp->pDataFunc = pFunc;

    return VOS_OK;
}

/*****************************************************************************
 函 数 名  : DMS_RegOmChanEventCB
 功能描述  : 注册OM通道事件接收回调
 输入参数  : enChan --- 逻辑通道
             pFunc  --- 函数指针
 输出参数  : 无
 返 回 值  : VOS_ERR/VOS_OK
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2014年7月5日
    作    者   : A00165503
    修改内容   : 新生成函数
*****************************************************************************/
VOS_UINT32 DMS_RegOmChanEventCB(
    DMS_OM_CHAN_ENUM_UINT32             enChan,
    DMS_OM_CHAN_EVENT_CB_FUNC           pFunc
)
{
    DMS_NLK_OM_CHAN_PROPERTY_STRU      *pstOmChanProp = VOS_NULL_PTR;

    /* 检查通道号 */
    if ((enChan >= DMS_OM_CHAN_BUTT) || (VOS_NULL_PTR == pFunc))
    {
        printk(KERN_ERR "[%s][LINE: %d] Invalid channel %d.\n",
            __func__, __LINE__, (VOS_INT)enChan);
        return VOS_ERR;
    }

    /* 设置通道事件回调函数 */
    pstOmChanProp = DMS_GET_NLK_OM_CHAN_PROP(enChan);
    pstOmChanProp->pEvtFunc = pFunc;

    return VOS_OK;
}

/*****************************************************************************
 函 数 名  : DMS_WriteOmData
 功能描述  : 写OM通道数据
 输入参数  : enChan   --- 逻辑通道
             pucData  --- 数据地址
             ulLength --- 数据长度
 输出参数  : 无
 返 回 值  : VOS_ERR/VOS_OK
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2014年7月5日
    作    者   : A00165503
    修改内容   : 新生成函数

  2.日    期   : 2015年10月17日
    作    者   : W00316404
    修改内容   : 控制是否打印modem log
*****************************************************************************/
VOS_UINT32 DMS_WriteOmData(
    DMS_OM_CHAN_ENUM_UINT32             enChan,
    VOS_UINT8                          *pucData,
    VOS_UINT32                          ulLength
)
{
    VOS_UINT8                          *pucMem = VOS_NULL_PTR;
    VOS_UINT32                          ulMemNum;
    VOS_UINT32                          ulLastMemSize;
    VOS_UINT32                          ulCnt;

    if (DMS_GET_PRINT_MODEM_LOG_TYPE())
    {
        DMS_DBG_NLK_UL_UNSUPPORT_WRITE_LOG_NUM(1);
        return VOS_ERR;
    }

    DMS_DBG_NLK_DL_TOTAL_PKT_NUM(1);

    /* 检查通道 */
    if (enChan >= DMS_OM_CHAN_BUTT)
    {
        DMS_DBG_NLK_DL_ERR_CHAN_PKT_NUM(1);
        return VOS_ERR;
    }

    /* 检查数据 */
    if ((VOS_NULL_PTR == pucData) || (0 == ulLength))
    {
        DMS_DBG_NLK_DL_ERR_PARA_PKT_NUM(1);
        return VOS_ERR;
    }

    DMS_DBG_NLK_DL_NORM_CHAN_PKT_NUM(enChan, 1);

    /* 对数据分块, 避免一次发送过多数据 */
    pucMem        = pucData;
    ulMemNum      = (ulLength >= DMS_GET_NLK_THRESH_SIZE())?(ulLength / DMS_GET_NLK_DATA_SIZE()):0;
    ulLastMemSize = (ulLength >= DMS_GET_NLK_THRESH_SIZE())?(ulLength % DMS_GET_NLK_DATA_SIZE()):ulLength;

    wake_lock(&g_stDmsMainInfo.stwakelock);

    /* 发送固定大小数据块 */
    for (ulCnt = 0; ulCnt < ulMemNum; ulCnt++)
    {
        DMS_NLK_Send(DMS_GET_NLK_PHY_BEAR(enChan), DMS_GET_NLK_MSG_TYPE(enChan), pucMem, DMS_GET_NLK_DATA_SIZE());
        pucMem += DMS_GET_NLK_DATA_SIZE();
    }

    /* 发送最后一块数据块 */
    if (0 != ulLastMemSize)
    {
        DMS_NLK_Send(DMS_GET_NLK_PHY_BEAR(enChan), DMS_GET_NLK_MSG_TYPE(enChan), pucMem, ulLastMemSize);
    }

    wake_unlock(&g_stDmsMainInfo.stwakelock);

    return VOS_OK;
}

/*****************************************************************************
 函 数 名  : DMS_NLK_InitEntity
 功能描述  : 初始化 netlink 实体
 输入参数  : VOS_VOID
 输出参数  : 无
 返 回 值  : VOS_VOID
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2014年7月5日
    作    者   : A00165503
    修改内容   : 新生成函数

  2.日    期   : 2015年5月8日
    作    者   : A00165503
    修改内容   : DTS2015050806031: 删除函数指针初始化, 防止错误清除
*****************************************************************************/
VOS_VOID DMS_NLK_InitEntity(VOS_VOID)
{
    DMS_NLK_ENTITY_STRU                *pstNlkEntity = VOS_NULL_PTR;

    pstNlkEntity = DMS_GET_NLK_ENTITY();

    /* netlink socket */
    pstNlkEntity->pstSock    = VOS_NULL_PTR;

    /* netlink 消息数据块大小 */
    pstNlkEntity->ulDataSize   = DMS_NLK_DEFUALT_DATA_SIZE;

    /* netlink 消息数据块大小 */
    pstNlkEntity->ulThreshSize = DMS_NLK_DEFUALT_DATA_SIZE * 2;

    /* netlink 物理承载进程号 */
    pstNlkEntity->astPhyBearProp[DMS_NLK_PHY_BEAR_LTE].lPid     = DMS_NLK_INVALID_PID;
    pstNlkEntity->astPhyBearProp[DMS_NLK_PHY_BEAR_GU].lPid      = DMS_NLK_INVALID_PID;

    /* netlink 逻辑通道属性(LTE CLTR) */
    pstNlkEntity->astOmChanProp[DMS_OM_CHAN_LTE_CTRL].enPhyBear = DMS_NLK_PHY_BEAR_LTE;
    pstNlkEntity->astOmChanProp[DMS_OM_CHAN_LTE_CTRL].enMsgType = DMS_NLK_MSG_TYPE_LTE_CTRL;

    /* netlink 逻辑通道属性(LTE DATA) */
    pstNlkEntity->astOmChanProp[DMS_OM_CHAN_LTE_DATA].enPhyBear = DMS_NLK_PHY_BEAR_LTE;
    pstNlkEntity->astOmChanProp[DMS_OM_CHAN_LTE_DATA].enMsgType = DMS_NLK_MSG_TYPE_LTE_DATA;

    /* netlink 逻辑通道属性(GU DATA) */
    pstNlkEntity->astOmChanProp[DMS_OM_CHAN_GU_DATA].enPhyBear  = DMS_NLK_PHY_BEAR_GU;
    pstNlkEntity->astOmChanProp[DMS_OM_CHAN_GU_DATA].enMsgType  = DMS_NLK_MSG_TYPE_GU_DATA;

    return;
}

/*****************************************************************************
 函 数 名  : DMS_NLK_CfgOpen
 功能描述  : 打开逻辑通道
 输入参数  : pstNlkHdr --- netlink 消息
             enBear    --- 物理承载
 输出参数  : 无
 返 回 值  : VOS_OK/VOS_ERR
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2014年7月5日
    作    者   : A00165503
    修改内容   : 新生成函数
*****************************************************************************/
VOS_UINT32 DMS_NLK_CfgOpen(
    struct nlmsghdr                    *pstNlkHdr,
    DMS_NLK_PHY_BEAR_ENUM_UINT32        enPhyBear
)
{
    DMS_NLK_PHY_BEAR_PROPERTY_STRU     *pstPhyBearProp = VOS_NULL_PTR;
    DMS_OM_CHAN_EVENT_CB_FUNC           pEvtFunc       = VOS_NULL_PTR;
    DMS_OM_CHAN_ENUM_UINT32             enChan;

    /* 检查承载号 */
    if (enPhyBear >= DMS_NLK_PHY_BEAR_BUTT)
    {
        printk("[%s][LINE: %d] Invalid PHY bearer %d.\n",
            __func__, __LINE__, (VOS_INT)enPhyBear);
        return VOS_ERR;
    }

    /* 设置承载PID */
    pstPhyBearProp = DMS_GET_NLK_PHY_BEAR_PROP(enPhyBear);
    pstPhyBearProp->lPid = pstNlkHdr->nlmsg_pid;

    /* 遍历所有与该承载关联的通道 */
    for (enChan = 0; enChan < DMS_OM_CHAN_BUTT; enChan++)
    {
        pEvtFunc = DMS_GET_NLK_OM_CHAN_EVT_CB_FUNC(enChan);

        /* 通知物理承载相同的逻辑通道使用者通道打开 */
        if ((enPhyBear == DMS_GET_NLK_PHY_BEAR(enChan)) && (VOS_NULL_PTR != pEvtFunc))
        {
            pEvtFunc(enChan, DMS_CHAN_EVT_OPEN);
        }
    }

    return VOS_OK;
}

/*****************************************************************************
 函 数 名  : DMS_NLK_CfgClose
 功能描述  : 关闭逻辑通道
 输入参数  : pstNlkHdr --- netlink 消息
             enBear    --- 物理承载
 输出参数  : 无
 返 回 值  : VOS_OK/VOS_ERR
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2014年7月5日
    作    者   : A00165503
    修改内容   : 新生成函数
*****************************************************************************/
VOS_UINT32 DMS_NLK_CfgClose(
    struct nlmsghdr                    *pstNlkHdr,
    DMS_NLK_PHY_BEAR_ENUM_UINT32        enBear
)
{
    DMS_NLK_PHY_BEAR_PROPERTY_STRU     *pstPhyBearProp = VOS_NULL_PTR;
    DMS_OM_CHAN_EVENT_CB_FUNC           pEvtFunc       = VOS_NULL_PTR;
    DMS_OM_CHAN_ENUM_UINT32             enChan;

    /* 检查承载号 */
    if (enBear >= DMS_NLK_PHY_BEAR_BUTT)
    {
        printk("[%s][LINE: %d] Invalid PHY bearer %d.\n",
            __func__, __LINE__, (VOS_INT)enBear);
        return VOS_ERR;
    }

    /* 设置承载PID */
    pstPhyBearProp = DMS_GET_NLK_PHY_BEAR_PROP(enBear);
    pstPhyBearProp->lPid = DMS_NLK_INVALID_PID;

    /* 遍历所有与该承载关联的通道 */
    for (enChan = 0; enChan < DMS_OM_CHAN_BUTT; enChan++)
    {
        pEvtFunc = DMS_GET_NLK_OM_CHAN_EVT_CB_FUNC(enChan);

        /* 通知物理承载相同的逻辑通道使用者通道关闭 */
        if ((enBear == DMS_GET_NLK_PHY_BEAR(enChan)) && (VOS_NULL_PTR != pEvtFunc))
        {
            pEvtFunc(enChan, DMS_CHAN_EVT_CLOSE);
        }
    }

    return VOS_OK;
}

/*****************************************************************************
 函 数 名  : DMS_NLK_ProcLteCfgMsg
 功能描述  : 处理LTE CFG消息
 输入参数  : pstNlkHdr --- netlink 消息
 输出参数  : 无
 返 回 值  : VOS_VOID
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2014年7月5日
    作    者   : A00165503
    修改内容   : 新生成函数
*****************************************************************************/
VOS_VOID DMS_NLK_ProcLteCfgMsg(struct nlmsghdr *pstNlkHdr)
{
    DMS_NLK_CFG_STRU                   *pstMsg = VOS_NULL_PTR;

    pstMsg = nlmsg_data(pstNlkHdr);

    switch (pstMsg->enCfg)
    {
        case DMS_NLK_CFG_TYPE_OPEN:
            (VOS_VOID)DMS_NLK_CfgOpen(pstNlkHdr, DMS_NLK_PHY_BEAR_LTE);
            DMS_DBG_NLK_UL_SEND_MSG_NUM(pstNlkHdr->nlmsg_type, 1);
            break;

        case DMS_NLK_CFG_TYPE_CLOSE:
            (VOS_VOID)DMS_NLK_CfgClose(pstNlkHdr, DMS_NLK_PHY_BEAR_LTE);
            DMS_DBG_NLK_UL_SEND_MSG_NUM(pstNlkHdr->nlmsg_type, 1);
            break;

        default:
            DMS_DBG_NLK_UL_FREE_MSG_NUM(pstNlkHdr->nlmsg_type, 1);
            break;
    }

    return;
}

/*****************************************************************************
 函 数 名  : DMS_NLK_ProcGuCfgMsg
 功能描述  : 处理GU CFG消息
 输入参数  : pstNlkHdr --- netlink 消息
 输出参数  : 无
 返 回 值  : VOS_VOID
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2014年7月5日
    作    者   : A00165503
    修改内容   : 新生成函数
*****************************************************************************/
VOS_VOID DMS_NLK_ProcGuCfgMsg(struct nlmsghdr *pstNlkHdr)
{
    DMS_NLK_CFG_STRU                   *pstMsg = VOS_NULL_PTR;

    pstMsg = nlmsg_data(pstNlkHdr);

    switch (pstMsg->enCfg)
    {
        case DMS_NLK_CFG_TYPE_OPEN:
            (VOS_VOID)DMS_NLK_CfgOpen(pstNlkHdr, DMS_NLK_PHY_BEAR_GU);
            DMS_DBG_NLK_UL_SEND_MSG_NUM(pstNlkHdr->nlmsg_type, 1);
            break;

        case DMS_NLK_CFG_TYPE_CLOSE:
            (VOS_VOID)DMS_NLK_CfgClose(pstNlkHdr, DMS_NLK_PHY_BEAR_GU);
            DMS_DBG_NLK_UL_SEND_MSG_NUM(pstNlkHdr->nlmsg_type, 1);
            break;

        default:
            DMS_DBG_NLK_UL_FREE_MSG_NUM(pstNlkHdr->nlmsg_type, 1);
            break;
    }

    return;
}

/*****************************************************************************
 函 数 名  : DMS_NLK_ProcLteCtrlMsg
 功能描述  : 处理LTE CTRL消息
 输入参数  : pstNlkHdr --- netlink 消息
 输出参数  : 无
 返 回 值  : VOS_VOID
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2014年7月5日
    作    者   : A00165503
    修改内容   : 新生成函数
*****************************************************************************/
VOS_VOID DMS_NLK_ProcLteCtrlMsg(struct nlmsghdr *pstNlkHdr)
{
    DMS_OM_CHAN_DATA_READ_CB_FUNC       pDataFunc  = VOS_NULL_PTR;
    DMS_NLK_PAYLOAD_STRU               *pstPayload = VOS_NULL_PTR;

    /* 获取通道注册的回调 */
    pDataFunc = DMS_GET_NLK_OM_CHAN_DATA_CB_FUNC(DMS_OM_CHAN_LTE_CTRL);
    if (VOS_NULL_PTR != pDataFunc)
    {
        /* 透传数据内容 */
        pstPayload = nlmsg_data(pstNlkHdr);
        (VOS_VOID)pDataFunc(DMS_OM_CHAN_LTE_CTRL, pstPayload->aucData, pstPayload->ulLength);
        DMS_DBG_NLK_UL_SEND_MSG_NUM(pstNlkHdr->nlmsg_type, 1);
    }
    else
    {
        DMS_DBG_NLK_UL_FREE_MSG_NUM(pstNlkHdr->nlmsg_type, 1);
    }

    return;
}

/*****************************************************************************
 函 数 名  : DMS_NLK_ProcLteDataMsg
 功能描述  : 处理LTE DATA消息
 输入参数  : pstNlkHdr --- netlink 消息
 输出参数  : 无
 返 回 值  : VOS_VOID
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2014年7月5日
    作    者   : A00165503
    修改内容   : 新生成函数
*****************************************************************************/
VOS_VOID DMS_NLK_ProcLteDataMsg(struct nlmsghdr *pstNlkHdr)
{
    DMS_OM_CHAN_DATA_READ_CB_FUNC       pDataFunc  = VOS_NULL_PTR;
    DMS_NLK_PAYLOAD_STRU               *pstPayload = VOS_NULL_PTR;

    /* 获取通道注册的回调 */
    pDataFunc = DMS_GET_NLK_OM_CHAN_DATA_CB_FUNC(DMS_OM_CHAN_LTE_DATA);
    if (VOS_NULL_PTR != pDataFunc)
    {
        /* 透传数据内容 */
        pstPayload = nlmsg_data(pstNlkHdr);
        (VOS_VOID)pDataFunc(DMS_OM_CHAN_LTE_DATA, pstPayload->aucData, pstPayload->ulLength);
        DMS_DBG_NLK_UL_SEND_MSG_NUM(pstNlkHdr->nlmsg_type, 1);
    }
    else
    {
        DMS_DBG_NLK_UL_FREE_MSG_NUM(pstNlkHdr->nlmsg_type, 1);
    }

    return;
}

/*****************************************************************************
 函 数 名  : DMS_NLK_ProcGuDataMsg
 功能描述  : 处理GU DATA消息
 输入参数  : pstNlkHdr --- netlink 消息
 输出参数  : 无
 返 回 值  : VOS_VOID
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2014年7月5日
    作    者   : A00165503
    修改内容   : 新生成函数
*****************************************************************************/
VOS_VOID DMS_NLK_ProcGuDataMsg(struct nlmsghdr *pstNlkHdr)
{
    DMS_OM_CHAN_DATA_READ_CB_FUNC       pDataFunc = VOS_NULL_PTR;
    DMS_NLK_PAYLOAD_STRU               *pstPayload = VOS_NULL_PTR;

    /* 获取通道注册的回调 */
    pDataFunc = DMS_GET_NLK_OM_CHAN_DATA_CB_FUNC(DMS_OM_CHAN_GU_DATA);
    if (VOS_NULL_PTR != pDataFunc)
    {
        /* 透传数据内容 */
        pstPayload = nlmsg_data(pstNlkHdr);
        (VOS_VOID)pDataFunc(DMS_OM_CHAN_GU_DATA, pstPayload->aucData, pstPayload->ulLength);
        DMS_DBG_NLK_UL_SEND_MSG_NUM(pstNlkHdr->nlmsg_type, 1);
    }
    else
    {
        DMS_DBG_NLK_UL_FREE_MSG_NUM(pstNlkHdr->nlmsg_type, 1);
    }

    return;
}

/*****************************************************************************
 函 数 名  : DMS_NLK_Send
 功能描述  : 发送 netlink 消息
 输入参数  : enPhyBear --- 物理承载号
             enMsgType --- 消息类型
             pucData   --- 数据指针
             ulLength  --- 数据长度
 输出参数  : 无
 返 回 值  : VOS_INT
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2014年7月5日
    作    者   : A00165503
    修改内容   : 新生成函数
*****************************************************************************/
VOS_INT DMS_NLK_Send(
    DMS_NLK_PHY_BEAR_ENUM_UINT32        enPhyBear,
    DMS_NLK_MSG_TYPE_ENUM_UINT32        enMsgType,
    VOS_UINT8                          *pucData,
    VOS_UINT32                          ulLength
)
{
    struct sk_buff                     *pstSkb      = VOS_NULL_PTR;
    struct nlmsghdr                    *pstNlkHdr   = VOS_NULL_PTR;
    DMS_NLK_PAYLOAD_STRU               *pstPlayload = VOS_NULL_PTR;
    VOS_UINT                            ulMsgSize;
    VOS_UINT                            ulPayloadSize;
    VOS_INT                             lRet;

    DMS_DBG_NLK_DL_TOTAL_MSG_NUM(1);

    /* 检查 netlink socket */
    if (VOS_NULL_PTR == DMS_GET_NLK_SOCK())
    {
        DMS_DBG_NLK_DL_ERR_SOCK_MSG_NUM(1);
        return -EIO;
    }

    /* 检查物理承载状态 */
    if (DMS_NLK_INVALID_PID == DMS_GET_NLK_PHY_PID(enPhyBear))
    {
        DMS_DBG_NLK_DL_ERR_PID_MSG_NUM(1);
        return -EINVAL;
    }

    /* 申请 netlink 消息 */
    ulPayloadSize = sizeof(DMS_NLK_PAYLOAD_STRU) + ulLength;
    ulMsgSize = NLMSG_SPACE(ulPayloadSize);

    pstSkb = nlmsg_new(ulPayloadSize, GFP_ATOMIC);
    if (VOS_NULL_PTR == pstSkb)
    {
        DMS_DBG_NLK_DL_ALLOC_MSG_FAIL_NUM(1);
        return -ENOBUFS;
    }

    /* 填充 netlink 消息头 */
    /* Use "ulMsgSize - sizeof(*pstNlkHdr)" here (incluing align pads) */
    pstNlkHdr = nlmsg_put(pstSkb, 0, 0, (VOS_INT)enMsgType,
                    (VOS_INT)(ulMsgSize - sizeof(struct nlmsghdr)), 0);
    if (VOS_NULL_PTR == pstNlkHdr)
    {
        kfree_skb(pstSkb);
        DMS_DBG_NLK_DL_PUT_MSG_FAIL_NUM(1);
        return -EMSGSIZE;
    }

    /* 填充 netlink 消息接收PID */
    /*lint -e545*/
#if ((LINUX_VERSION_CODE >= KERNEL_VERSION(3, 10, 0)) || (VOS_OS_VER == VOS_WIN32))
    NETLINK_CB(pstSkb).portid = DMS_GET_NLK_PHY_PID(enPhyBear);
#else
    NETLINK_CB(pstSkb).pid = DMS_GET_NLK_PHY_PID(enPhyBear);
#endif
    NETLINK_CB(pstSkb).dst_group = 0;
    /*lint +e545*/

    /* 填充 netlink 消息内容 */
    pstPlayload = nlmsg_data(pstNlkHdr);
    pstPlayload->ulLength = ulLength;

    memcpy(pstPlayload->aucData, pucData, ulLength);

    /* 发送 netlink 消息 */
    /*lint -e545*/
#if ((LINUX_VERSION_CODE >= KERNEL_VERSION(3, 10, 0)) || (VOS_OS_VER == VOS_WIN32))
    lRet = netlink_unicast(DMS_GET_NLK_SOCK(), pstSkb, NETLINK_CB(pstSkb).portid, 0);
#else
    lRet = netlink_unicast(DMS_GET_NLK_SOCK(), pstSkb, NETLINK_CB(pstSkb).pid, 0);
#endif

    /*lint +e545*/
    if (lRet < 0)
    {
        DMS_DBG_NLK_DL_UNICAST_MSG_FAIL_NUM(1);
        return lRet;
    }

    DMS_DBG_NLK_DL_UNICAST_MSG_SUCC_NUM(1);
    return 0;
}

/*****************************************************************************
 函 数 名  : DMS_NLK_Input
 功能描述  : netlink 消息入口
 输入参数  : pstSkb --- skb buff
 输出参数  : 无
 返 回 值  : VOS_VOID
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2014年7月5日
    作    者   : A00165503
    修改内容   : 新生成函数

  2.日    期   : 2015年10月17日
    作    者   : W00316404
    修改内容   : 控制是否打印modem log
*****************************************************************************/
VOS_VOID DMS_NLK_Input(struct sk_buff *pstSkb)
{
    struct nlmsghdr                    *pstNlkHdr = VOS_NULL_PTR;

    if (DMS_GET_PRINT_MODEM_LOG_TYPE())
    {
        DMS_DBG_NLK_UL_UNSUPPORT_INPUT_LOG_NUM(1);
        return;
    }

    DMS_DBG_NLK_UL_TOTAL_MSG_NUM(1);

    /* 获取 netlink 消息 */
    pstNlkHdr = nlmsg_hdr(pstSkb);

    /* 检查 netlink 消息是否合法 */
    if (!NLMSG_OK(pstNlkHdr, pstSkb->len))
    {
        DMS_DBG_NLK_UL_ERR_MSG_NUM(1);
        return;
    }

    /* 处理 netlink 消息 */
    switch (pstNlkHdr->nlmsg_type)
    {
        case DMS_NLK_MSG_TYPE_LTE_CFG:
            DMS_NLK_ProcLteCfgMsg(pstNlkHdr);
            break;

        case DMS_NLK_MSG_TYPE_LTE_CTRL:
            DMS_NLK_ProcLteCtrlMsg(pstNlkHdr);
            break;

        case DMS_NLK_MSG_TYPE_LTE_DATA:
            DMS_NLK_ProcLteDataMsg(pstNlkHdr);
            break;

        case DMS_NLK_MSG_TYPE_GU_CFG:
            DMS_NLK_ProcGuCfgMsg(pstNlkHdr);
            break;

        case DMS_NLK_MSG_TYPE_GU_DATA:
            DMS_NLK_ProcGuDataMsg(pstNlkHdr);
            break;

        default:
            DMS_DBG_NLK_UL_UNKNOWN_MSG_NUM(1);
            break;
    }

    return;
}

/*****************************************************************************
 函 数 名  : DMS_NLK_Init
 功能描述  : netlink 加载
 输入参数  : VOS_VOID
 输出参数  : 无
 返 回 值  : VOS_INT __init
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2014年7月5日
    作    者   : A00165503
    修改内容   : 新生成函数
*****************************************************************************/
VOS_INT __init DMS_NLK_Init(VOS_VOID)
{
    struct sock                        *pstSock      = VOS_NULL_PTR;
    DMS_NLK_ENTITY_STRU                *pstNlkEntity = VOS_NULL_PTR;

    printk("DMS_NLK_Init,entry,%u",VOS_GetSlice());

    /* 初始化 netlink 实体 */
    DMS_NLK_InitEntity();

    /* 在内核态创建一个 netlink socket */
#if ((LINUX_VERSION_CODE >= KERNEL_VERSION(3, 10, 0)) || (VOS_OS_VER == VOS_WIN32))
    pstSock = netlink_kernel_create(&init_net, NETLINK_HW_LOGCAT, &g_stDmsNlkCfg);
#else
    pstSock = netlink_kernel_create(&init_net, NETLINK_HW_LOGCAT, 0,
                                DMS_NLK_Input, NULL, THIS_MODULE);
#endif

    if (VOS_NULL_PTR == pstSock)
    {
        printk(KERN_ERR "[%s][LINE: %d] Fail to create netlink socket.\n",
            __func__, __LINE__);
        DMS_DBG_NLK_CREATE_SOCK_FAIL_NUM(1);
        return -ENOMEM;
    }

    /* 保存 socket */
    pstNlkEntity = DMS_GET_NLK_ENTITY();
    pstNlkEntity->pstSock = pstSock;

    printk("DMS_NLK_Init,exit,%u",VOS_GetSlice());

    return 0;
}

/*****************************************************************************
 函 数 名  : DMS_NLK_Exit
 功能描述  : netlink 卸载
 输入参数  : VOS_VOID
 输出参数  : 无
 返 回 值  : VOS_VOID __exit
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2014年7月5日
    作    者   : A00165503
    修改内容   : 新生成函数
*****************************************************************************/
VOS_VOID __exit DMS_NLK_Exit(VOS_VOID)
{
    /* 释放 netlink socket */
    netlink_kernel_release(DMS_GET_NLK_SOCK());
    DMS_NLK_InitEntity();
    return;
}

/*****************************************************************************
 函 数 名  : DMS_InitGetSliceFile
 功能描述  : Get Slice虚拟文件初始化
 输入参数  : 无
 输出参数  : 无
 返 回 值  : 成功或失败

 修改历史      :
  1.日    期   : 2015年1月04日
    作    者   : j00174725
    修改内容   : 新生成函数
*****************************************************************************/
VOS_INT __init DMS_InitGetSliceFile(VOS_VOID)
{
    /*lint -e960 */
    if (VOS_NULL_PTR == proc_create("getslice", DMS_VFILE_CRT_LEVEL, VOS_NULL_PTR, &g_stGetSliceOps))
    {
        DMS_LOG_ERROR("DMS_InitGetSliceFile: proc_create return NULL.\n");
        return VOS_ERR;
    }
    /*lint +e960 */

    return VOS_OK;
}

/*****************************************************************************
 函 数 名  : DMS_ReadGetSliceFile
 功能描述  : getslice虚拟文件读实现
 输入参数  : file --- 文件句柄
             buf  --- 用户空间
             ppos --- 文件偏移，参数未使用
 输出参数  : 无
 返 回 值  : 成功或失败

修改历史      :
 1.日    期   : 2015年1月04日
   作    者   : j00174725
   修改内容   : 新生成函数

*****************************************************************************/
ssize_t DMS_ReadGetSliceFile(
    struct file                        *file,
    char __user                        *buf,
    size_t                              len,
    loff_t                             *ppos
)
{
    VOS_CHAR                            acModeTemp[DMS_GET_SLICE_FILE_LEN];
    VOS_UINT32                          ulLength;
    VOS_UINT32                          ulHigh32bitValue;
    VOS_UINT32                          ulLow32bitValue;

    if (*ppos > 0)
    {
        return 0;
    }

    /* 初始化 */
    ulLength            = 0;
    ulHigh32bitValue    = 0;
    ulLow32bitValue     = 0;

    VOS_MemSet(acModeTemp, 0x00, DMS_GET_SLICE_FILE_LEN);

    /* 获取时间  Seattle 和 Portland不一样 */
    (VOS_VOID)mdrv_timer_get_accuracy_timestamp(&ulHigh32bitValue, &ulLow32bitValue);

    if (ulHigh32bitValue != 0)
    {
        VOS_sprintf((VOS_CHAR *)acModeTemp, "%x%08x", ulHigh32bitValue, ulLow32bitValue);
    }
    else
    {
        VOS_sprintf((VOS_CHAR *)acModeTemp, "%x", ulLow32bitValue);
    }

    ulLength        = VOS_StrLen(acModeTemp);
    len             = PS_MIN(len, ulLength);

    /*拷贝内核空间数据到用户空间上面*/
    if (0 == copy_to_user(buf,(VOS_VOID *)acModeTemp, (VOS_ULONG)len))
    {
        *ppos += (loff_t)len;

        return (ssize_t)len;
    }
    else
    {
        return -EPERM;
    }

}

/*****************************************************************************
 函 数 名  : DMS_InitModemStatusFile
 功能描述  : ModemStatus节点初始化
 输入参数  : 无
 输出参数  : 无
 返 回 值  : VOS_VIOD

 修改历史      :
  1.日    期   : 2016年1月20日
    作    者   : z00301431
    修改内容   : 新生成函数
*****************************************************************************/
VOS_INT __init DMS_InitModemStatusFile(VOS_VOID)
{
    DMS_LOG_INFO("DMS_InitModemStatusFile,entry,%u \n",VOS_GetSlice());

    DMS_InitModemStatus();

    /*lint -e960 */
    if (VOS_NULL_PTR == proc_create("modemstatus", DMS_VFILE_CRT_LEVEL, VOS_NULL_PTR, &g_stModemStatus))
    {
        DMS_LOG_ERROR("DMS_InitModemStatusFile: proc_create return NULL.\n");
        return -ENOMEM;
    }
    /*lint +e960 */

    DMS_LOG_INFO("DMS_InitModemStatusFile,exit,%u \n",VOS_GetSlice());

    return 0;
}

/*****************************************************************************
 函 数 名  : DMS_ReadModemStatusFile
 功能描述  : ModemStatusFile0虚拟文件读实现
 输入参数  : file --- 文件句柄
             buf  --- 用户空间
             ppos --- 文件偏移，参数未使用
 输出参数  : 无
 返 回 值  : 成功或失败

修改历史      :
 1.日    期   : 2016年1月20日
   作    者   : z00301431
   修改内容   : 新生成函数
*****************************************************************************/
ssize_t DMS_ReadModemStatusFile(
    struct file                        *file,
    char __user                        *buf,
    size_t                              len,
    loff_t                             *ppos
)
{
    VOS_CHAR                            acStatus[DMS_MODEM_STATUS_FILE_LEN];
    VOS_UINT32                          ulStatusLen;

    if (*ppos > 0)
    {
        return 0;
    }

    VOS_MemSet(acStatus, 0x00, DMS_MODEM_STATUS_FILE_LEN);

    DMS_LOG_INFO("DMS_ReadModemStatusFile entry,time: %u, status: %d, %d, %d\n",
                 VOS_GetSlice(),
                 g_stDmsMainInfo.aucModemStatus[0],
                 g_stDmsMainInfo.aucModemStatus[1],
                 g_stDmsMainInfo.aucModemStatus[2]);

    /* 获取按需拨号的模式以及时长的地址 */
    VOS_sprintf((VOS_CHAR *)acStatus, "%s", g_stDmsMainInfo.aucModemStatus);

    ulStatusLen = VOS_StrLen(acStatus);

    len = PS_MIN(len, ulStatusLen);

    /*拷贝内核空间数据到用户空间上面*/
    if (0 == copy_to_user(buf,(VOS_VOID *)acStatus, (VOS_ULONG)len))
    {
        *ppos += (loff_t)len;

        return (ssize_t)len;
    }
    else
    {
        DMS_LOG_ERROR("DMS_ReadModemStatusFile copy to user fail %u \n",VOS_GetSlice());
        return -EPERM;
    }
}

/*****************************************************************************
 函 数 名  : DMS_SetModemStatus
 功能描述  : 根据MODEM ID设置ModemStatus
 输入参数  : MODEM_ID_ENUM_UINT16 enModemId
 输出参数  : 无
 返 回 值  : VOS_VOID

修改历史      :
 1.日    期   : 2016年1月20日
   作    者   : z00301431
   修改内容   : 新生成函数
*****************************************************************************/
VOS_VOID DMS_SetModemStatus(MODEM_ID_ENUM_UINT16 enModemId)
{
    if (enModemId >= MODEM_ID_BUTT)
    {
        DMS_LOG_ERROR("DMS_SetModemStatus ModemId error %d \n",enModemId);
        return;
    }

    g_stDmsMainInfo.aucModemStatus[enModemId] = VOS_TRUE;
}

/*****************************************************************************
 函 数 名  : DMS_GetModemStatus
 功能描述  : 获取ModemStatus
 输入参数  : MODEM_ID_ENUM_UINT16 enModemId
 输出参数  : 无
 返 回 值  : VOS_UINT32

修改历史      :
 1.日    期   : 2016年1月20日
   作    者   : z00301431
   修改内容   : 新生成函数
*****************************************************************************/
VOS_UINT8 DMS_GetModemStatus(MODEM_ID_ENUM_UINT16 enModemId)
{
    if (enModemId >= MODEM_ID_BUTT)
    {
        DMS_LOG_ERROR("DMS_GetModemStatus ModemId error %d \n",enModemId);
        return g_stDmsMainInfo.aucModemStatus[0];
    }

    return g_stDmsMainInfo.aucModemStatus[enModemId];
}

/*****************************************************************************
 函 数 名  : DMS_InitModemStatus
 功能描述  : 初始化所有的ModemStatus
 输入参数  : VOS_VOID
 输出参数  : 无
 返 回 值  : VOS_VOID

修改历史      :
 1.日    期   : 2016年1月20日
   作    者   : z00301431
   修改内容   : 新生成函数
*****************************************************************************/
VOS_VOID DMS_InitModemStatus(VOS_VOID)
{
    VOS_MemSet(g_stDmsMainInfo.aucModemStatus, 0x00, sizeof(g_stDmsMainInfo.aucModemStatus));
}


#ifndef _lint
/* This function is called on driver initialization and exit */
module_init(DMS_InitModemStatusFile);
module_init(DMS_NLK_Init);
module_exit(DMS_NLK_Exit);
#endif


#ifdef __cplusplus
    #if __cplusplus
        }
    #endif
#endif

