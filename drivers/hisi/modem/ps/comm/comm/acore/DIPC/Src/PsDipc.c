

#ifdef __cplusplus
#if __cplusplus
extern "C" {
#endif
#endif

/*lint -e767*/
#define    THIS_FILE_ID        PS_FILE_ID_PSDIPC_C
/*lint +e767*/

/*****************************************************************************
  1 头文件包含
*****************************************************************************/
#include "product_config.h"

#if (FEATURE_ON == FEATURE_AT_HSIC)
#include "PsTypeDef.h"
#include "PsDipc.h"
#include "PsCommonDef.h"

/*****************************************************************************
  2 全局变量定义
*****************************************************************************/

/* 打印开关 */
VOS_UINT32                              g_ulDipcPrintFlag   = PS_FALSE;

/* 消息跟踪开关 */
VOS_UINT32                              g_ulDipcTraceFlag   = PS_FALSE;

/*勾包使用全局变量,之所以用2个，是因为DIPC为API模式，上下行在2个任务中运行*/
TRACE_UL_DIPC_DATA_MSG                  *g_pstDipcTraceUlData;
TRACE_DL_DIPC_DATA_MSG                  *g_pstDipcTraceDlData;

/* DIPC通道的统计信息 */
DIPC_STATIC_INFO_STRU                   g_stDipcStaticInfo;

/* 设备的信息，包括设备内部信息和设备到SERVICE之间的映射关系 */
DEV_INFO_STRU                           g_astDevInfo[DIPC_DEV_NUM];

/* 设备到服务之间的映射关系，上行使用 */
DEV_SERVICE_INFO_STRU                   g_astDevService[DIPC_DEV_NUM];

/* RAB ID到Service之间的映射关系，下行使用 */
RAB_SERVICE_INFO_STRU                   g_astRabService[RAB_MAX_NUM];

/* SERVICE信息 */
TOTAL_SERVICE_INFO_STRU                 g_stTotalServiceInfo;

/* DIPC数据队列 */
DIPC_DATA_Q_CTRL_ST                     g_stDipcDataQ;


/*****************************************************************************
  3 函数实现
*****************************************************************************/
/*****************************************************************************
函 数 名  : DIPC_PrintLog
功能描述  : 目前临时使用DIPC打印函数，后续等A核打印可用后切换为TTF_LOG，打印没有参数的打印
输入参数  : VOS_UINT32  ulModuleId      打印模块名
            VOS_UINT32  ulSubMod        打印子模块名
            VOS_UINT32  ulLevel         打印级别
            VOS_CHAR   *pcString        打印内容
            VOS_INT32   lPara1          打印参数
输出参数  : 无
返 回 值  : 无

修改历史      :
 1.日    期   : 2012年2月13日
   作    者   : x59651
   修改内容   : 新生成函数

*****************************************************************************/
VOS_VOID DIPC_PrintLog
(
    VOS_UINT32      ulModuleId,
    VOS_UINT32      ulSubMod,
    VOS_UINT32      ulLevel,
    VOS_CHAR       *pcString
)
{
    if (PS_TRUE == g_ulDipcPrintFlag)
    {
        vos_printf(pcString);
    }

    return;
}


/*****************************************************************************
函 数 名  : DIPC_PrintLog1
功能描述  : 目前临时使用DIPC打印函数，后续等A核打印可用后切换为TTF_LOG，打印有1个参数的打印
输入参数  : VOS_UINT32  ulModuleId      打印模块名
            VOS_UINT32  ulSubMod        打印子模块名
            VOS_UINT32  ulLevel         打印级别
            VOS_CHAR   *pcString        打印内容
            VOS_INT32   lPara1          打印参数
调用函数  :
被调函数  :

修改历史      :
 1.日    期   : 2012年2月13日
   作    者   : x59651
   修改内容   : 新生成函数

*****************************************************************************/
VOS_VOID DIPC_PrintLog1
(
    VOS_UINT32      ulModuleId,
    VOS_UINT32      ulSubMod,
    VOS_UINT32      ulLevel,
    VOS_CHAR       *pcString,
    VOS_INT32       lPara1
)
{
    if (PS_TRUE == g_ulDipcPrintFlag)
    {
        vos_printf(pcString, lPara1);
    }

    return;
}


/*****************************************************************************
函 数 名  : DIPC_PrintLog2
功能描述  : 目前临时使用DIPC打印函数，后续等A核打印可用后切换为TTF_LOG，打印有2个参数的打印
输入参数  : VOS_UINT32  ulModuleId      打印模块名
            VOS_UINT32  ulSubMod        打印子模块名
            VOS_UINT32  ulLevel         打印级别
            VOS_CHAR   *pcString        打印内容
            VOS_INT32   lPara1          打印参数
            VOS_INT32   lPara2          打印参数2
输出参数  : 无
返 回 值  : 无

修改历史      :
 1.日    期   : 2012年2月13日
   作    者   : x59651
   修改内容   : 新生成函数

*****************************************************************************/
VOS_VOID DIPC_PrintLog2
(
    VOS_UINT32      ulModuleId,
    VOS_UINT32      ulSubMod,
    VOS_UINT32      ulLevel,
    VOS_CHAR       *pcString,
    VOS_INT32       lPara1,
    VOS_INT32       lPara2
)
{
    if (PS_TRUE == g_ulDipcPrintFlag)
    {
        vos_printf(pcString, lPara1, lPara2);
    }

    return;
}

/******************************************************************************
 Prototype       : DIPC_Snd1stDataNotify
 Description     : DIPC数据队列内结点个数为0时，向DIPC发送数据处理指示ID_DIPC_DATA_NOTIFY_REQ消息
 Input           :
 Output          : NONE
 Return Value    : PS_SUCC   --- 成功
                   PS_FAIL   --- 失败
 History         :
   1.Date        : 2013-03-20
     Author      : x59651
     Modification: 增加PPP数据队列处理机制
******************************************************************************/
VOS_UINT32  DIPC_Snd1stDataNotify(VOS_VOID)
{
    DIPC_DATA_PROC_NOTIFY_MSG    *pMsg;
    VOS_INT32                    lLockKey;


    /*申请消息内存:*/
    pMsg = (DIPC_DATA_PROC_NOTIFY_MSG *) PS_ALLOC_MSG( PS_PID_APP_DIPC,
        sizeof(DIPC_DATA_PROC_NOTIFY_MSG) - VOS_MSG_HEAD_LENGTH );

    if (VOS_NULL_PTR == pMsg)
    {
        /*打印出错信息---申请消息包失败:*/
        DIPC_PrintLog( PS_PID_APP_DIPC, 0, PS_PRINT_WARNING,
            "DIPC_Snd1stDataNotify:WARNING:Allocates message for DIPC_Snd1stDataNotify FAIL!\r\n" );
        return PS_FAIL;
    }

    /*填写消息内容:*/
    pMsg->ulReceiverCpuId   = VOS_LOCAL_CPUID;
    pMsg->ulReceiverPid     = PS_PID_APP_DIPC;
    pMsg->enMsgType         = ID_DIPC_DATA_NOTIFY_REQ;

    lLockKey = VOS_SplIMP();
    g_stDipcDataQ.ulNotifyMsgCnt++;
    VOS_Splx(lLockKey);

    /*发送消息:*/
    if (VOS_OK != PS_SEND_MSG(PS_PID_APP_DIPC, pMsg))
    {
        /*打印警告信息---发送消息失败:*/
        DIPC_PrintLog( PS_PID_APP_DIPC, 0, PS_PRINT_WARNING, "SEND DIPC_Snd1stDataNotify msg FAIL!\r\n" );
        return PS_FAIL;
    }

    return PS_SUCC;
}

/*****************************************************************************
 Prototype      : DIPC_DataQClear
 Description    : 清除DIPC数据队列内容
 Input          : VOS_VOID
 Output         :
 Return Value   : VOID
 Calls          :
 Called By      :
 History        :
   1.Date        : 2013-3-20
     Author      : x59651
     Modification: Created function
*****************************************************************************/
VOS_VOID DIPC_ClearDataQ(VOS_VOID)
{
    IMM_ZC_STRU    *pstMem;
    VOS_INT32       lLockKey;

    for(;;)
    {
        lLockKey    = VOS_SplIMP();

        if ( 0 == IMM_ZcQueueLen(&g_stDipcDataQ.stDipcDataQ) )
        {
            VOS_Splx(lLockKey);
            break;
        }

        VOS_Splx(lLockKey);

        pstMem  = (IMM_ZC_STRU *)IMM_ZcDequeueHead(&g_stDipcDataQ.stDipcDataQ);

        IMM_ZcFree(pstMem);
    }

    return;
}

/******************************************************************************
 Prototype       : DIPC_EnqueueData
 Description     : 将上下行数据放入DIPC数据队列，如果队列从空到非空，并发送消息通知DIPC模块
 Input           :
 Output          : NONE
 Return Value    : PS_SUCC   --- 成功
                   PS_FAIL   --- 失败
 History         :
   1.Date        : 2013-3-20
     Author      : x59651
     Modification: Created function
******************************************************************************/
VOS_UINT32  DIPC_EnqueueData(IMM_ZC_STRU *pstImmZc)
{
    VOS_UINT32                          ulNonEmptyEvent = PS_FALSE;    /* 记录队列是否发生了由空到非空的转变 */
    IMM_ZC_HEAD_STRU                   *pstDataQ;
    VOS_INT32                           lLockKey;

    pstDataQ   = &g_stDipcDataQ.stDipcDataQ;

    /* A核任务调试不够实时，之前获取长度和入列分开锁中断，会出现上行数据入队时
       判断队列不为空，但紧接着DIPC任务得到调度，把队列取空后再接着入队的情况。
       因为将获取队列数据个数和入队包含在一个锁中断中 */
    lLockKey = VOS_SplIMP();
    if (( 0 == IMM_ZcQueueLen(pstDataQ)) && (0 == g_stDipcDataQ.ulNotifyMsgCnt))
    {
        ulNonEmptyEvent = PS_TRUE;
    }

    /*将数据结点插入队列尾部*/
    IMM_ZcQueueTail(pstDataQ, pstImmZc);
    VOS_Splx(lLockKey);

    if (PS_TRUE == ulNonEmptyEvent)
    {
        /*向DIPC发送数据处理指示*/
       if (PS_SUCC != DIPC_Snd1stDataNotify())
       {
            /* 发送消息通知失败，需要清空整个队列 */
            DIPC_ClearDataQ();
            DIPC_PrintLog(PS_PID_APP_DIPC, 0, PS_PRINT_WARNING,
                "DIPC, DIPC_EnqueueData, WARNING, DIPC_Snd1stDataNotify fail!\r\n");
            return PS_FAIL;
       }
    }

    return PS_SUCC;
} /* DIPC_EnqueueData */



/*****************************************************************************
 函 数 名  : DIPC_DEV_HsicAcmFreeDlDataCB
 功能描述  : 向底软注册ACM下HSIC用户面通道下行数据释放回调函数
 输入参数  : IMM_ZC_STRU *pstBuf    需要释放的内存结构，为sk_buff类型

 输出参数  : 无
 返 回 值  : VOS_VOID

 修改历史      :
  1.日    期   : 2012年2月13日
    作    者   : x59651
    修改内容   : 新生成函数

*****************************************************************************/
VOS_VOID DIPC_DEV_HsicAcmFreeDlDataCB(IMM_ZC_STRU *pstBuf)
{
    IMM_ZcFree(pstBuf);
    return;
}


/*****************************************************************************
 函 数 名  : DIPC_DEV_AcmOpenDevice
 功能描述  : DIPC使用的ACM下HSIC用户面数据设备初始化
 输入参数  : DEV_INFO_STRU *pstDevInfo  设备相关结构
 输出参数  : 无
 返 回 值  : PS_SUCC:成功；
             PS_FAIL:失败

 修改历史      :
  1.日    期   : 2012年2月13日
    作    者   : x59651
    修改内容   : 新生成函数

*****************************************************************************/
VOS_UINT32 DIPC_DEV_AcmOpenDevice(DEV_INFO_STRU *pstDevInfo)
{
    UDI_OPEN_PARAM_S        stParam;

    stParam.devid   = pstDevInfo->enUdiDevId;
    pstDevInfo->slUdiHsicHdl = mdrv_udi_open(&stParam);

    if (UDI_INVAL_DEV_ID == pstDevInfo->slUdiHsicHdl)
    {
        DIPC_PrintLog(PS_PID_APP_DIPC, 0, PS_PRINT_ERROR,
            "DIPC, DIPC_DEV_AcmOpenDevice, Call mdrv_udi_open return UDI_INVAL_DEV_ID.\n");
        return PS_FAIL;
    }

    /* 注册HSIC ACM 用户面通道上行数据接收回调 */
    if (VOS_OK != mdrv_udi_ioctl (pstDevInfo->slUdiHsicHdl, ACM_IOCTL_SET_READ_CB, pstDevInfo->pRxFunc.pAcmRxFunc))
    {
        DIPC_PrintLog(PS_PID_APP_DIPC, 0, PS_PRINT_ERROR,
            "DIPC, DIPC_DEV_AcmOpenDevice, ERROR, Set HSIC ACM data read callback failed!\n");
        return PS_FAIL;
    }

    /* 注册HSIC ACM 用户面通道下行数据内存释放接口 */
    if (VOS_OK != mdrv_udi_ioctl (pstDevInfo->slUdiHsicHdl, ACM_IOCTL_SET_FREE_CB, DIPC_DEV_HsicAcmFreeDlDataCB))
    {
        DIPC_PrintLog(PS_PID_APP_DIPC, 0, PS_PRINT_ERROR,
            "DIPC, DIPC_DEV_AcmOpenDevice, ERROR, Set HSIC ACM memory free callback failed!\n");
        return PS_FAIL;
    }

    return PS_SUCC;
}


/*****************************************************************************
 函 数 名  : DIPC_DEV_NcmOpenDevice
 功能描述  : DIPC使用的NCM下HSIC用户面数据设备初始化
 输入参数  : DEV_INFO_STRU *pstDevInfo  设备相关结构

 输出参数  : 无

 返 回 值  : PS_SUCC:成功；
             PS_FAIL:失败

 修改历史      :
  1.日    期   : 2012年8月30日
    作    者   : x59651
    修改内容   : 新生成函数

*****************************************************************************/
VOS_UINT32 DIPC_DEV_NcmOpenDevice(DEV_INFO_STRU *pstDevInfo)
{
    UDI_OPEN_PARAM_S                      stParam;

    stParam.devid   = pstDevInfo->enUdiDevId;
    pstDevInfo->slUdiHsicHdl = mdrv_udi_open(&stParam);

    if (UDI_INVAL_DEV_ID == pstDevInfo->slUdiHsicHdl)
    {
        DIPC_PrintLog(PS_PID_APP_DIPC, 0, PS_PRINT_ERROR,
            "DIPC, DIPC_DEV_NcmOpenDevice, Call mdrv_udi_open return UDI_INVAL_DEV_ID.\n");
        return PS_FAIL;
    }

    /* 注册HSIC NCM 用户面通道上行数据接收回调 */
    if (VOS_OK != mdrv_udi_ioctl (pstDevInfo->slUdiHsicHdl, NCM_IOCTL_REG_UPLINK_RX_FUNC, pstDevInfo->pRxFunc.pNcmRxFunc))
    {
        DIPC_PrintLog(PS_PID_APP_DIPC, 0, PS_PRINT_ERROR,"DIPC_DEV_NcmOpenDevice, regist RxFunc fail!");
        return PS_FAIL;
    }

    return PS_SUCC;
}


/*****************************************************************************
 函 数 名  : DIPC_DEV_AcmGetUlDataBuf
 功能描述  : 封装从HSIC ACM设备读数据的接口
 输入参数  : UDI_HANDLE slUdiHsicAcmHdl ACM设备的句柄
             IMM_ZC_STRU **ppstBuf      用来指向输出的上行数据Buf指针

 输出参数  : IMM_ZC_STRU **ppstBuf      用来指向输出的上行数据Buf指针中指向的内容

 返 回 值  : PS_SUCC:成功
             PS_FAIL:失败

 修改历史      :
  1.日    期   : 2012年2月15日
    作    者   : x59651
    修改内容   : 新生成函数
*****************************************************************************/
VOS_UINT32 DIPC_DEV_AcmGetUlDataBuf(UDI_HANDLE slUdiHsicAcmHdl, IMM_ZC_STRU **ppstBuf)
{
    ACM_WR_ASYNC_INFO                   stCtlParam;
    VOS_INT32                           lResult;

    stCtlParam.pVirAddr = VOS_NULL_PTR;
    stCtlParam.pPhyAddr = VOS_NULL_PTR;

    /* 获取底软上行数据buffer */
    lResult= mdrv_udi_ioctl(slUdiHsicAcmHdl, ACM_IOCTL_GET_RD_BUFF, &stCtlParam);
    if ( VOS_OK != lResult )
    {
        DIPC_PrintLog1(PS_PID_APP_DIPC, 0, PS_PRINT_WARNING,
            "DIPC, DIPC_DEV_AcmGetUlDataBuf, WARNING, Get modem buffer failed code <1>!\r\n",
            lResult);
        return PS_FAIL;
    }

    if (VOS_NULL_PTR == stCtlParam.pVirAddr)
    {
        DIPC_PrintLog(PS_PID_APP_DIPC, 0, PS_PRINT_WARNING,
            "DIPC, DIPC_DEV_AcmGetUlDataBuf, WARNING, Data buffer is NULL!\r\n");
        return PS_FAIL;
    }

    *ppstBuf = (IMM_ZC_STRU *)stCtlParam.pVirAddr;

    return PS_SUCC;
}


/*****************************************************************************
 函 数 名  : DIPC_DEV_UsbAcmReadUlData
 功能描述  : 底软上报数据的上行数据接收函数
 输入参数  : DIPC_DEV_ACM_ID_ENUM_UINT32 enDeviceId  通知有上行数据的设备id,使用的为内部ID
 输出参数  : 无
 返 回 值  : PS_SUCC    数据成功接收和转发
             PS_FAIL    数据接收或者转发失败

 修改历史      :
  1.日    期   : 2012年2月15日
    作    者   : x59651
    修改内容   : 新生成函数

*****************************************************************************/
VOS_UINT32 DIPC_DEV_UsbAcmReadUlData(DIPC_DEV_ID_ENUM_UINT32 enDeviceId)
{
    UDI_HANDLE                          slUdiHandle;
    IMM_ZC_STRU                        *pstBuf;

    slUdiHandle = DIPC_DRV_GetDevHandleByDevId(enDeviceId);
    if (UDI_INVAL_DEV_ID == slUdiHandle)
    {
        g_stDipcStaticInfo.astDipcDevStaticInfo[enDeviceId].ulGetDataFailNums++;
        DIPC_PrintLog1(PS_PID_APP_DIPC, 0, PS_PRINT_WARNING,
            "DIPC, DIPC_DEV_UsbAcmReadUlData, can not get the slUdiHandle,ulDeviceId <1>",
            (VOS_INT32)enDeviceId);
        return PS_FAIL;
    }

    /* 底软现有接口，如果不取出数据会影响下一个数据的接收 */
    if (PS_SUCC != DIPC_DEV_AcmGetUlDataBuf(slUdiHandle, &pstBuf))
    {
        g_stDipcStaticInfo.astDipcDevStaticInfo[enDeviceId].ulGetDataFailNums++;
        DIPC_PrintLog(PS_PID_APP_DIPC, 0, PS_PRINT_WARNING,
            "DIPC, DIPC_DEV_UsbAcmReadUlData, call DIPC_DEV_UsbAcmReadUlData return fail!\n");
        return PS_FAIL;
    }

    g_stDipcStaticInfo.astDipcDevStaticInfo[enDeviceId].ulSuccGetUlPacketNums++;

    return DIPC_DEV_UlDataProc(enDeviceId, pstBuf);
}


/*****************************************************************************
 函 数 名  : DIPC_DEV_UsbAcm1ReadUlData
 功能描述  : ACM1设备上上报的上行数据回调函数
 输入参数  : 无
 输出参数  : 无
 返 回 值  : PS_SUCC    数据成功接收和转发
             PS_FAIL    数据接收或者转发失败

 修改历史      :
  1.日    期   : 2012年2月15日
    作    者   : x59651
    修改内容   : 新生成函数

*****************************************************************************/
VOS_UINT32 DIPC_DEV_UsbAcm1ReadUlData( VOS_VOID)
{
    DIPC_DEV_UsbAcmReadUlData(DIPC_DEV_ID1);
    return VOS_OK;
}


/*****************************************************************************
 函 数 名  : DIPC_DEV_UsbAcm3ReadUlData
 功能描述  : ACM3设备上上报的上行数据回调函数
 输入参数  : 无
 输出参数  : 无
 返 回 值  : PS_SUCC    数据成功接收和转发
             PS_FAIL    数据接收或者转发失败

 修改历史      :
  1.日    期   : 2012年2月15日
    作    者   : x59651
    修改内容   : 新生成函数

*****************************************************************************/
VOS_UINT32 DIPC_DEV_UsbAcm3ReadUlData( VOS_VOID)
{
    DIPC_DEV_UsbAcmReadUlData(DIPC_DEV_ID2);
    return VOS_OK;
}


/*****************************************************************************
 函 数 名  : DIPC_DEV_UsbAcm5ReadUlData
 功能描述  : ACM5设备上上报的上行数据回调函数
 输入参数  : 无
 输出参数  : 无
 返 回 值  : PS_SUCC    数据成功接收和转发
             PS_FAIL    数据接收或者转发失败

 修改历史      :
  1.日    期   : 2012年2月15日
    作    者   : x59651
    修改内容   : 新生成函数

*****************************************************************************/
VOS_UINT32 DIPC_DEV_UsbAcm5ReadUlData( VOS_VOID)
{
    DIPC_DEV_UsbAcmReadUlData(DIPC_DEV_ID3);
    return VOS_OK;
}


/*****************************************************************************
 函 数 名  : DIPC_DEV_UsbAcmWriteData
 功能描述  : 通过HSIC对应的ACM口将数据发送给底软
 输入参数  : UDI_HANDLE slUdiHandle 待写数据所在设备的句柄
             IMM_ZC_STRU *pstBuf    待写数据所在结构的指针
 输出参数  : 无
 返 回 值  : VOS_UINT32

 修改历史      :
  1.日    期   : 2012年2月15日
    作    者   : x59651
    修改内容   : 新生成函数

*****************************************************************************/
VOS_UINT32 DIPC_DEV_UsbAcmWriteData(UDI_HANDLE slUdiHandle, IMM_ZC_STRU *pstBuf)
{
    ACM_WR_ASYNC_INFO                   stCtlParam;
    VOS_INT32                           ulResult;


    /* 待写入数据内存地址 */
    stCtlParam.pVirAddr                 = (VOS_CHAR*)pstBuf;
    stCtlParam.pPhyAddr                 = VOS_NULL_PTR;
    stCtlParam.u32Size                  = 0;
    stCtlParam.pDrvPriv                 = VOS_NULL_PTR;

    /* 异步方式写数，*/
    ulResult = mdrv_udi_ioctl(slUdiHandle, ACM_IOCTL_WRITE_ASYNC, &stCtlParam);

    if ( VOS_OK != ulResult )
    {
        DIPC_PrintLog1(PS_PID_APP_DIPC, 0, PS_PRINT_WARNING,
            "DIPC_DEV_UsbAcmWriteData, Error, Write data failed with code <1>!",
            ulResult);

        return PS_FAIL;
    }

    return PS_SUCC;
}


/*****************************************************************************
 函 数 名  : DIPC_DEV_UsbNcm0ReadUlData
 功能描述  : NCM0设备上上报的上行数据回调函数
 输入参数  : UDI_HANDLE slUdiHandle 底软回调函数输入的数据对应的设备句柄
             VOS_VOID *pPktNodes    底软会点函数输入的数据所在结构的指针
 输出参数  : 无
 返 回 值  : PS_SUCC    数据成功接收和转发
             PS_FAIL    数据接收或者转发失败

 修改历史      :
  1.日    期   : 2012年8月30日
    作    者   : x59651
    修改内容   : 新生成函数

*****************************************************************************/
VOS_UINT32 DIPC_DEV_UsbNcm0ReadUlData(UDI_HANDLE ulhandle, VOS_VOID *pPktNode)
{
    UDI_HANDLE              slUdiHandle;
    IMM_ZC_STRU            *pstImmZcData = (IMM_ZC_STRU*)pPktNode;  /*ImmZc和sk_buff完全一致，直接强转*/


    slUdiHandle = DIPC_DRV_GetDevHandleByDevId(DIPC_DEV_ID1);
    if (UDI_INVAL_DEV_ID == slUdiHandle)
    {
        g_stDipcStaticInfo.astDipcDevStaticInfo[DIPC_DEV_ID1].ulGetDataFailNums++;
        DIPC_PrintLog(PS_PID_APP_DIPC, 0, PS_PRINT_WARNING,
            "DIPC, DIPC_UsbNcm0ReadUlData, can not get the slUdiHandle, DIPC_DEV_ID1.");
        IMM_ZcFree(pstImmZcData);
        return PS_FAIL;
    }

    if (ulhandle != slUdiHandle)
    {
        g_stDipcStaticInfo.astDipcDevStaticInfo[DIPC_DEV_ID1].ulGetDataFailNums++;
        DIPC_PrintLog2(PS_PID_APP_DIPC, 0, PS_PRINT_WARNING,
            "DIPC, DIPC_UsbNcm0ReadUlData, Drv Handle <1> is not same as DevID1 Handle <2>.",
            ulhandle, slUdiHandle);
        IMM_ZcFree(pstImmZcData);
        return PS_FAIL;
    }

    g_stDipcStaticInfo.astDipcDevStaticInfo[DIPC_DEV_ID1].ulSuccGetUlPacketNums++;

    DIPC_DEV_UlDataProc(DIPC_DEV_ID1, pstImmZcData);
    return PS_SUCC;
}


/*****************************************************************************
 函 数 名  : DIPC_DEV_UsbNcm1ReadUlData
 功能描述  : NCM1设备上上报的上行数据回调函数
 输入参数  : UDI_HANDLE slUdiHandle 底软回调函数输入的数据对应的设备句柄
             VOS_VOID *pPktNodes    底软会点函数输入的数据所在结构的指针
 输出参数  : 无
 返 回 值  : PS_SUCC    数据成功接收和转发
             PS_FAIL    数据接收或者转发失败

 修改历史      :
  1.日    期   : 2012年8月30日
    作    者   : x59651
    修改内容   : 新生成函数

*****************************************************************************/
VOS_UINT32 DIPC_DEV_UsbNcm1ReadUlData(UDI_HANDLE ulhandle, VOS_VOID *pPktNode)
{
    UDI_HANDLE              slUdiHandle;
    IMM_ZC_STRU            *pstImmZcData = (IMM_ZC_STRU*)pPktNode;  /*ImmZc和sk_buff完全一致，直接强转*/


    slUdiHandle = DIPC_DRV_GetDevHandleByDevId(DIPC_DEV_ID2);
    if (UDI_INVAL_DEV_ID == slUdiHandle)
    {
        g_stDipcStaticInfo.astDipcDevStaticInfo[DIPC_DEV_ID2].ulGetDataFailNums++;
        DIPC_PrintLog(PS_PID_APP_DIPC, 0, PS_PRINT_WARNING,
            "DIPC, DIPC_UsbNcm1ReadUlData, can not get the slUdiHandle, DIPC_DEV_ID2.");
        IMM_ZcFree(pstImmZcData);
        return PS_FAIL;
    }

    if (ulhandle != slUdiHandle)
    {
        g_stDipcStaticInfo.astDipcDevStaticInfo[DIPC_DEV_ID2].ulGetDataFailNums++;
        DIPC_PrintLog2(PS_PID_APP_DIPC, 0, PS_PRINT_WARNING,
            "DIPC, DIPC_UsbNcm1ReadUlData, Drv Handle <1> is not same as DevID2 Handle <2>.",
            ulhandle, slUdiHandle);
        IMM_ZcFree(pstImmZcData);
        return PS_FAIL;
    }

    g_stDipcStaticInfo.astDipcDevStaticInfo[DIPC_DEV_ID2].ulSuccGetUlPacketNums++;

    DIPC_DEV_UlDataProc(DIPC_DEV_ID2, pstImmZcData);
    return PS_SUCC;
}


/*****************************************************************************
 函 数 名  : DIPC_DEV_UsbNcm2ReadUlData
 功能描述  : NCM2设备上上报的上行数据回调函数
 输入参数  : UDI_HANDLE slUdiHandle 底软回调函数输入的数据对应的设备句柄
             VOS_VOID *pPktNodes    底软会点函数输入的数据所在结构的指针
 输出参数  : 无
 返 回 值  : PS_SUCC    数据成功接收和转发
             PS_FAIL    数据接收或者转发失败

 修改历史      :
  1.日    期   : 2012年8月30日
    作    者   : x59651
    修改内容   : 新生成函数

*****************************************************************************/
VOS_UINT32 DIPC_DEV_UsbNcm2ReadUlData(UDI_HANDLE ulhandle, VOS_VOID *pPktNode)
{
    UDI_HANDLE              slUdiHandle;
    IMM_ZC_STRU            *pstImmZcData = (IMM_ZC_STRU*)pPktNode;  /*ImmZc和sk_buff完全一致，直接强转*/


    slUdiHandle = DIPC_DRV_GetDevHandleByDevId(DIPC_DEV_ID3);
    if (UDI_INVAL_DEV_ID == slUdiHandle)
    {
        g_stDipcStaticInfo.astDipcDevStaticInfo[DIPC_DEV_ID3].ulGetDataFailNums++;
        DIPC_PrintLog(PS_PID_APP_DIPC, 0, PS_PRINT_WARNING,
            "DIPC, DIPC_UsbNcm2ReadUlData, can not get the slUdiHandle, DIPC_DEV_ID3.");
        IMM_ZcFree(pstImmZcData);
        return PS_FAIL;
    }

    if (ulhandle != slUdiHandle)
    {
        g_stDipcStaticInfo.astDipcDevStaticInfo[DIPC_DEV_ID3].ulGetDataFailNums++;
        DIPC_PrintLog2(PS_PID_APP_DIPC, 0, PS_PRINT_WARNING,
            "DIPC, DIPC_UsbNcm2ReadUlData, Drv Handle <1> is not same as DevID3 Handle <2>.",
            ulhandle, slUdiHandle);
        IMM_ZcFree(pstImmZcData);
        return PS_FAIL;
    }

    g_stDipcStaticInfo.astDipcDevStaticInfo[DIPC_DEV_ID3].ulSuccGetUlPacketNums++;

    DIPC_DEV_UlDataProc(DIPC_DEV_ID3, pstImmZcData);
    return PS_SUCC;
}


/*****************************************************************************
 函 数 名  : DIPC_DEV_UsbNcmWriteData
 功能描述  : 通过HSIC对应的NCM口将数据发送给底软
 输入参数  : UDI_HANDLE     slUdiHandle 待写数据所在设备的句柄
             IMM_ZC_STRU   *pstBuf      待写数据所在结构的指针
 输出参数  : 无
 返 回 值  : VOS_UINT32

 修改历史      :
  1.日    期   : 2012年8月30日
    作    者   : x59651
    修改内容   : 新生成函数

*****************************************************************************/
VOS_UINT32 DIPC_DEV_UsbNcmWriteData(UDI_HANDLE slUdiHandle, IMM_ZC_STRU *pstBuf)
{
    VOS_INT32                           ulResult;
    VOS_UINT32                          ulSize = IMM_ZcGetUsedLen(pstBuf);

    /* 为了减少AP侧一次拷贝，所以此处预留14字节，便于AP侧添加MAC头部 */
    IMM_ZcPush(pstBuf,IMM_MAC_HEADER_RES_LEN);

    /* 异步方式写数*/
    ulResult = mdrv_udi_write(slUdiHandle, pstBuf, ulSize);

    if ( VOS_OK != ulResult )
    {
        DIPC_PrintLog1(PS_PID_APP_DIPC, 0, PS_PRINT_WARNING,
            "DIPC_DEV_UsbNcmWriteData, Error, Write data failed with code <1>!",
            ulResult);
        return PS_FAIL;
    }

    return PS_SUCC;
}


/*****************************************************************************
 函 数 名  : DIPC_DEV_UsbWriteData
 功能描述  : 通过HSIC对应的NCM口将数据发送给底软
 输入参数  : DIPC_DEV_ID_ENUM enDipcDevId   设备内部ID
             IMM_ZC_STRU *pstBuf            待写数据所在结构的指针
 输出参数  : 无
 返 回 值  : VOS_UINT32

 修改历史      :
  1.日    期   : 2012年8月30日
    作    者   : x59651
    修改内容   : 新生成函数

*****************************************************************************/
VOS_UINT32 DIPC_DEV_UsbWriteData(DIPC_DEV_ID_ENUM_UINT32 enDipcDevId, IMM_ZC_STRU *pstBuf)
{
    DEV_INFO_STRU                           *pstDevInfo;

    pstDevInfo  = &g_astDevInfo[enDipcDevId];

    if (VOS_NULL_PTR == pstDevInfo->pTxFunc)
    {
        return PS_FAIL;
    }

    return pstDevInfo->pTxFunc(pstDevInfo->slUdiHsicHdl, pstBuf);
}


/*****************************************************************************
 函 数 名  : DIPC_DEV_PortInit
 功能描述  : A核 DIPC功能端口初始化函数
 输入参数  : VOS_VOID
 输出参数  : 无
 返 回 值  : VOS_OK  初始化成功
             VOS_ERR 初始化失败

 修改历史      :
  1.日    期   : 2012年2月16日
    作    者   : x59651
    修改内容   : 新生成函数

*****************************************************************************/
VOS_UINT32 DIPC_DEV_PortInit( VOS_VOID )
{
    DIPC_DEV_ID_ENUM_UINT32         enDipcDevId;
    DEV_INFO_STRU                  *pstDevInfo;


    /*  产品不支持HSIC特性，直接初始化成功 */
    if (BSP_MODULE_SUPPORT != mdrv_misc_support_check(BSP_MODULE_TYPE_HSIC))
    {
        return VOS_OK;
    }

    if (BSP_MODULE_SUPPORT == mdrv_misc_support_check(BSP_MODULE_TYPE_HSIC_NCM))
    {
        g_astDevInfo[DIPC_DEV_ID1].enUdiDevId           = UDI_NCM_HSIC_NCM0_ID;
        g_astDevInfo[DIPC_DEV_ID1].pRxFunc.pNcmRxFunc   = DIPC_DEV_UsbNcm0ReadUlData;
        g_astDevInfo[DIPC_DEV_ID1].pTxFunc              = DIPC_DEV_UsbNcmWriteData;

        g_astDevInfo[DIPC_DEV_ID2].enUdiDevId           = UDI_NCM_HSIC_NCM1_ID;
        g_astDevInfo[DIPC_DEV_ID2].pRxFunc.pNcmRxFunc   = DIPC_DEV_UsbNcm1ReadUlData;
        g_astDevInfo[DIPC_DEV_ID2].pTxFunc              = DIPC_DEV_UsbNcmWriteData;

        g_astDevInfo[DIPC_DEV_ID3].enUdiDevId           = UDI_NCM_HSIC_NCM2_ID;
        g_astDevInfo[DIPC_DEV_ID3].pRxFunc.pNcmRxFunc   = DIPC_DEV_UsbNcm2ReadUlData;
        g_astDevInfo[DIPC_DEV_ID3].pTxFunc              = DIPC_DEV_UsbNcmWriteData;

        for(enDipcDevId = 0; enDipcDevId < DIPC_DEV_NUM; enDipcDevId++)
        {
            pstDevInfo = &g_astDevInfo[enDipcDevId];
            pstDevInfo->slUdiHsicHdl    = UDI_INVAL_DEV_ID;

            /* 本端口打开失败，继续打开下一个端口 */
            if (PS_SUCC != DIPC_DEV_NcmOpenDevice(pstDevInfo))
            {
                DIPC_PrintLog1(PS_PID_APP_DIPC, 0, PS_PRINT_WARNING,
                    "DIPC_DEV_PortInit, Open Device <1> fail.\n", (VOS_INT32)enDipcDevId);
            }
        }
    }
    else
    {
        g_astDevInfo[DIPC_DEV_ID1].enUdiDevId           = UDI_ACM_HSIC_ACM1_ID;
        g_astDevInfo[DIPC_DEV_ID1].pRxFunc.pAcmRxFunc   = DIPC_DEV_UsbAcm1ReadUlData;
        g_astDevInfo[DIPC_DEV_ID1].pTxFunc              = DIPC_DEV_UsbAcmWriteData;

        g_astDevInfo[DIPC_DEV_ID2].enUdiDevId           = UDI_ACM_HSIC_ACM3_ID;
        g_astDevInfo[DIPC_DEV_ID2].pRxFunc.pAcmRxFunc   = DIPC_DEV_UsbAcm3ReadUlData;
        g_astDevInfo[DIPC_DEV_ID2].pTxFunc              = DIPC_DEV_UsbAcmWriteData;

        g_astDevInfo[DIPC_DEV_ID3].enUdiDevId           = UDI_ACM_HSIC_ACM5_ID;
        g_astDevInfo[DIPC_DEV_ID3].pRxFunc.pAcmRxFunc   = DIPC_DEV_UsbAcm5ReadUlData;
        g_astDevInfo[DIPC_DEV_ID3].pTxFunc              = DIPC_DEV_UsbAcmWriteData;

        for(enDipcDevId = 0; enDipcDevId < DIPC_DEV_NUM; enDipcDevId++)
        {
            pstDevInfo = &g_astDevInfo[enDipcDevId];
            pstDevInfo->slUdiHsicHdl    = UDI_INVAL_DEV_ID;

            /* 本端口打开失败，继续打开下一个端口 */
            if (PS_SUCC != DIPC_DEV_AcmOpenDevice(pstDevInfo))
            {
                DIPC_PrintLog1(PS_PID_APP_DIPC, 0, PS_PRINT_WARNING,
                    "DIPC_DEV_PortInit, Open Device <1> fail.\n", (VOS_INT32)enDipcDevId);
            }
        }
    }

    return VOS_OK;
}


/*****************************************************************************
 函 数 名  : DIPC_DEV_AddNewIpTypeService
 功能描述  : DIPC模块添加新的设备对应的IP类型服务
 输入参数  : DIPC_DEV_ID_ENUM_UINT32 enDevId                    内部设备ID
             DIPC_SERVICE_TYPE_ENUM_UINT32 enDipcServiceTypes   服务类型
             DEV_SERVICE_INFO_STRU *pstDevServiceInfo           设备服务结构

 输出参数  : 无
 返 回 值  : 无

 修改历史      :
  1.日    期   : 2012年12月15日
    作    者   : x59651
    修改内容   : 新生成函数
*****************************************************************************/
VOS_VOID DIPC_DEV_AddNewIpTypeService(DIPC_DEV_ID_ENUM_UINT32 enDevId,
    DIPC_SERVICE_TYPE_ENUM_UINT32 enDipcServiceType, SERVICE_INFO_STRU *pstServiceInfo)
{
    DEV_SERVICE_INFO_STRU          *pstDevServiceInfo;

    pstDevServiceInfo = &g_astDevService[enDevId];

    pstDevServiceInfo->apstServiceInfo[enDipcServiceType] = pstServiceInfo;
    DIPC_SET_SERVICE_REG(pstDevServiceInfo->ulServiceMask, enDipcServiceType);

    pstDevServiceInfo->ulServiceCnt++;

    return;
}

/*****************************************************************************
 函 数 名  : DIPC_DEV_DelIpTypeService
 功能描述  : DIPC模块删除该设备上对应的服务
 输入参数  : DIPC_DEV_ID_ENUM_UINT32        enDevId             DIPC内部使用的设备ID
             DIPC_SERVICE_TYPE_ENUM_UINT32  enDipcServiceType   对应服务的类型
 输出参数  : 无
 返 回 值  : PS_SUCC 删除成功
             PS_FAIL删除失败

 修改历史      :
  1.日    期   : 2012年12月15日
    作    者   : x59651
    修改内容   : 新生成函数
*****************************************************************************/
VOS_UINT32 DIPC_DEV_DelIpTypeService(DIPC_DEV_ID_ENUM_UINT32 enDevId,
    DIPC_SERVICE_TYPE_ENUM_UINT32 enDipcServiceType)
{
    DEV_SERVICE_INFO_STRU          *pstDevServiceInfo;

    pstDevServiceInfo = &g_astDevService[enDevId];
    pstDevServiceInfo->apstServiceInfo[enDipcServiceType] = VOS_NULL_PTR;
    DIPC_CLR_SERVICE_REG(pstDevServiceInfo->ulServiceMask, enDipcServiceType);
    pstDevServiceInfo->ulServiceCnt--;

    return PS_SUCC;
}


/*****************************************************************************
 函 数 名  : DIPC_DEV_GetDevIdByUdiId
 功能描述  : 通过外部设备ID获取内部设备ID
 输入参数  : UDI_DEVICE_ID_E enUdiDevId   底软使用设备ID

 输出参数  : 无
 返 回 值  : DIPC_DEV_ID_ENUM_UINT32    对应的内部设备ID，无效时为DIPC_DEV_BUTT

 修改历史      :
  1.日    期   : 2012年2月15日
    作    者   : x59651
    修改内容   : 新生成函数

*****************************************************************************/
DIPC_DEV_ID_ENUM_UINT32 DIPC_DEV_GetDevIdByUdiId(UDI_DEVICE_ID_E enUdiDevId)
{
    DIPC_DEV_ID_ENUM_UINT32             enDevId;

    if ((UDI_ACM_HSIC_ACM1_ID != enUdiDevId)
        && (UDI_ACM_HSIC_ACM3_ID != enUdiDevId)
        && (UDI_ACM_HSIC_ACM5_ID != enUdiDevId)
        && (UDI_NCM_HSIC_NCM0_ID != enUdiDevId)
        && (UDI_NCM_HSIC_NCM1_ID != enUdiDevId)
        && (UDI_NCM_HSIC_NCM2_ID != enUdiDevId))
    {
        return DIPC_DEV_BUTT;
    }

    for (enDevId = DIPC_DEV_ID1; enDevId < DIPC_DEV_BUTT; enDevId++)
    {
        if (g_astDevInfo[enDevId].enUdiDevId == enUdiDevId)
        {
            break;
        }
    }

    return enDevId;
}


/*****************************************************************************
 函 数 名  : DIPC_DRV_GetDevHandleByDevId
 功能描述  : 通过内部使用设备ID获取设备句柄
 输入参数  : DIPC_DEV_ACM_ID_ENUM_UINT32 ulDeviceId  内部使用设备ID

 输出参数  : 无
 返 回 值  : DevId对应的句柄,无效时为UDI_INVALID_HANDLE

 修改历史      :
  1.日    期   : 2012年2月15日
    作    者   : x59651
    修改内容   : 新生成函数

*****************************************************************************/
UDI_HANDLE DIPC_DRV_GetDevHandleByDevId(DIPC_DEV_ID_ENUM_UINT32 enDevId)
{
    if (DIPC_DEV_BUTT <= enDevId)
    {
        DIPC_PrintLog1(PS_PID_APP_DIPC, 0, PS_PRINT_WARNING,
            "DIPC, DIPC_DRV_GetDevHandleByDevId, enDevId <1> exceed the range.\n",
            (VOS_INT32)enDevId);
        return INVALID_RABID_VALUE;
    }

    return g_astDevInfo[enDevId].slUdiHsicHdl;
}

/*****************************************************************************
 函 数 名  : DIPC_DEV_CheckUdiDevIdPara
 功能描述  : 外部使用设备ID是否合法检查
 输入参数  : UDI_DEVICE_ID_E enUdiDevId  AT发来的PDP激活消息指针
 输出参数  : 无
 返 回 值  : VOS_UINT32 VOS_OK:无错误,VOS_ERR:有错误

 修改历史      :
  1.日    期   : 2012年12月15日
    作    者   : x59651
    修改内容   : 新生成函数

*****************************************************************************/
VOS_UINT32 DIPC_DEV_CheckUdiDevIdPara(UDI_DEVICE_ID_E enUdiDevId)
{
    if (BSP_MODULE_SUPPORT == mdrv_misc_support_check(BSP_MODULE_TYPE_HSIC_NCM))
    {
        if ((UDI_NCM_HSIC_NCM0_ID != enUdiDevId)
            && (UDI_NCM_HSIC_NCM1_ID != enUdiDevId)
            && (UDI_NCM_HSIC_NCM2_ID != enUdiDevId))
        {
            return VOS_ERR;
        }

    }
    else
    {
        if ((UDI_ACM_HSIC_ACM1_ID != enUdiDevId)
            && (UDI_ACM_HSIC_ACM3_ID != enUdiDevId)
            && (UDI_ACM_HSIC_ACM5_ID != enUdiDevId))
        {
            return VOS_ERR;
        }
    }

    return VOS_OK;
}

/*****************************************************************************
 函 数 名  : DIPC_DEV_UlDataProc
 功能描述  : DIPC模块上行数据处理
 输入参数  : DIPC_DEV_ID_ENUM_UINT32 enDeviceId 设备ID
             IMM_ZC_STRU *pstBuf                用来指向输出的上行数据Buf指针

 输出参数  : IMM_ZC_STRU *pstBuf      用来指向输出的上行数据Buf指针中指向的内容

 返 回 值  : PS_SUCC:成功
             PS_FAIL:失败

 修改历史      :
  1.日    期   : 2012年12月15日
    作    者   : x59651
    修改内容   : 新生成函数
*****************************************************************************/
VOS_UINT32 DIPC_DEV_UlDataProc(DIPC_DEV_ID_ENUM_UINT32 enDeviceId, IMM_ZC_STRU *pstBuf)
{
    VOS_UINT16  usApp;      /* 使用skb_buff结构中已有字段传递上下行和参数信息 */

    if (VOS_NULL_PTR == pstBuf)
    {
        return PS_FAIL;
    }

    usApp = DIPC_SET_APP(ID_DIPC_UL_DATA, enDeviceId);

    IMM_ZcSetUserApp(pstBuf, usApp);

    return DIPC_EnqueueData(pstBuf);
}

/*****************************************************************************
 函 数 名  : DIPC_MGR_RegNewService
 功能描述  : 注册一个新的Service
 输入参数  : SERVICE_INFO_STRU *pstServInputInfo    输入的服务信息
 输出参数  : 无

 返 回 值  : SERVICE_INFO_STRU  获取的服务对应结构的指针,无法注册时为VOS_NULL_PTR

 修改历史      :
  1.日    期   : 2012年12月15日
    作    者   : x59651
    修改内容   : 新生成函数
*****************************************************************************/
SERVICE_INFO_STRU* DIPC_MGR_RegNewService(SERVICE_INFO_STRU *pstServInputInfo)
{
    SERVICE_INFO_STRU  *pstGetServInfo;
    VOS_UINT8           ucServiceNo;

    if (SERVICE_MAX_NUM <= g_stTotalServiceInfo.ulServiceNum)
    {
        DIPC_PrintLog(PS_PID_APP_DIPC, 0, PS_PRINT_WARNING,
            "DIPC, DIPC_MGR_RegNewService, WARNING, Service is FULL!\r\n");
        return VOS_NULL_PTR;
    }

    for (ucServiceNo = 0; ucServiceNo < SERVICE_MAX_NUM; ucServiceNo ++)
    {
        if (0 == DIPC_GET_SERVICE_STRU_USE(g_stTotalServiceInfo.ulServiceMask, ucServiceNo))
        {
            break;
        }
    }

    if (SERVICE_MAX_NUM == ucServiceNo)
    {
        DIPC_PrintLog2(PS_PID_APP_DIPC, 0, PS_PRINT_WARNING,
            "DIPC, DIPC_MGR_RegNewService, WARNING, Service Mask <1> is FULL, but ServiceNum <2> is not full!\r\n",
            (VOS_INT32)g_stTotalServiceInfo.ulServiceMask, (VOS_INT32)g_stTotalServiceInfo.ulServiceNum);
        return VOS_NULL_PTR;
    }

    pstGetServInfo = &g_stTotalServiceInfo.astServiceInfo[ucServiceNo];

    pstGetServInfo->ucServiceIndex  = ucServiceNo;
    pstGetServInfo->ucRabId         = pstServInputInfo->ucRabId;
    pstGetServInfo->enDipcDevId     = pstServInputInfo->enDipcDevId;
    pstGetServInfo->pUlMatchFunc    = pstServInputInfo->pUlMatchFunc;
    pstGetServInfo->pDlMatchFunc    = pstServInputInfo->pDlMatchFunc;
    pstGetServInfo->pUlCallFunc     = pstServInputInfo->pUlCallFunc;
    pstGetServInfo->pDlCallFunc     = pstServInputInfo->pDlCallFunc;

    DIPC_SET_SERVICE_STRU_REG(g_stTotalServiceInfo.ulServiceMask, ucServiceNo);
    g_stTotalServiceInfo.ulServiceNum ++;

    return pstGetServInfo;
}


/*****************************************************************************
 函 数 名  : DIPC_MGR_DeregService
 功能描述  : 去注册一个新的Service
 输入参数  : SERVICE_INFO_STRU *pstServiceInfo  去注册的服务结构指针
 输出参数  : 无

 返 回 值  :

 修改历史      :
  1.日    期   : 2012年12月15日
    作    者   : x59651
    修改内容   : 新生成函数
*****************************************************************************/
VOS_VOID DIPC_MGR_DeregService(SERVICE_INFO_STRU *pstServiceInfo)
{
    DIPC_CLR_SERVICE_STRU_REG(g_stTotalServiceInfo.ulServiceMask, pstServiceInfo->ucServiceIndex);
    g_stTotalServiceInfo.ulServiceNum --;

    pstServiceInfo->ucServiceIndex  = 0;
    pstServiceInfo->ucRabId         = 0;
    pstServiceInfo->enDipcDevId     = DIPC_DEV_BUTT;
    pstServiceInfo->pUlMatchFunc    = VOS_NULL_PTR;
    pstServiceInfo->pDlMatchFunc    = VOS_NULL_PTR;
    pstServiceInfo->pUlCallFunc     = VOS_NULL_PTR;
    pstServiceInfo->pDlCallFunc     = VOS_NULL_PTR;

    return;
}


/*****************************************************************************
 函 数 名  : DIPC_MGR_UlDataProc
 功能描述  : DIPC模块上行数据处理
 输入参数  : DIPC_DEV_ID_ENUM_UINT32 enDeviceId 设备ID
             IMM_ZC_STRU *pstBuf                用来指向输出的上行数据Buf指针

 输出参数  : IMM_ZC_STRU *pstBuf      用来指向输出的上行数据Buf指针中指向的内容

 返 回 值  : PS_SUCC:成功
             PS_FAIL:失败

 修改历史      :
  1.日    期   : 2012年12月15日
    作    者   : x59651
    修改内容   : 新生成函数
*****************************************************************************/
VOS_UINT32 DIPC_MGR_UlDataProc(DIPC_DEV_ID_ENUM_UINT32 enDeviceId, IMM_ZC_STRU *pstBuf)
{
    DEV_SERVICE_INFO_STRU              *pstDevServiceInfo;
    DIPC_SERVICE_TYPE_ENUM_UINT32       enServiceType;
    SERVICE_INFO_STRU                  *pstServInfo;

    DIPC_TraceUlData(enDeviceId, pstBuf);

    pstDevServiceInfo = &g_astDevService[enDeviceId];

    for (enServiceType = 0; enServiceType < DIPC_SERVICE_TYPE_MAX_NUM; enServiceType++)
    {
        if (PS_TRUE == DIPC_GET_SERVICE_REG(pstDevServiceInfo->ulServiceMask, enServiceType))
        {
            pstServInfo = pstDevServiceInfo->apstServiceInfo[enServiceType];

            /* 因为上行数据需要根据数据内容确定Rab Id，所以需要进行Match操作，下行不需要 */
            if (VOS_NULL_PTR == pstServInfo->pUlMatchFunc)
            {
                DIPC_PrintLog2(PS_PID_APP_DIPC, 0, PS_PRINT_WARNING,
                    "DIPC, DIPC_MGR_UlDataProc, pUlMatchFunc is NULL,enServiceType <1>, enDeviceId<2>",
                    (VOS_INT32)enServiceType, (VOS_INT32)enDeviceId);
                IMM_ZcFree(pstBuf);
                return PS_FAIL;
            }

            if (PS_SUCC == pstServInfo->pUlMatchFunc(pstBuf))
            {
                if (VOS_NULL_PTR == pstServInfo->pUlCallFunc)
                {
                    DIPC_PrintLog2(PS_PID_APP_DIPC, 0, PS_PRINT_WARNING,
                        "DIPC, DIPC_MGR_UlDataProc, pUlCallFunc is NULL,enServiceType <1>, enDeviceId<2>",
                        (VOS_INT32)enServiceType, (VOS_INT32)enDeviceId);
                    IMM_ZcFree(pstBuf);
                    return PS_FAIL;
                }

                if (VOS_OK != pstServInfo->pUlCallFunc(pstBuf, pstServInfo->ucRabId))
                {
                    DIPC_PrintLog2(PS_PID_APP_DIPC, 0, PS_PRINT_WARNING,
                        "DIPC, DIPC_MGR_UlDataProc, call pUlFunc return fail,ulDeviceId <1>, ucRabID",
                        (VOS_INT32)enDeviceId, (VOS_INT32)pstServInfo->ucRabId);
                    IMM_ZcFree(pstBuf);
                    g_stDipcStaticInfo.astDipcDevStaticInfo[enDeviceId].ulFailSendUlPacketNums++;
                    return PS_FAIL;
                }

                /* 成功接收，则退出并记录 */
                g_stDipcStaticInfo.astDipcDevStaticInfo[enDeviceId].ulSuccSendUlPacketNums++;
                return PS_SUCC;
            }
        }
    }

    /* 该设备上没有找到对应的服务，释放数据 */
    IMM_ZcFree(pstBuf);
    g_stDipcStaticInfo.astDipcDevStaticInfo[enDeviceId].ulFailMatchUlPacketNums++;
    return PS_FAIL;
}


/*****************************************************************************
 函 数 名  : DIPC_MGR_IpV4Match
 功能描述  : 检测收到的数据为ipV4类型
 输入参数  : IMM_ZC_STRU *pstImmZcData  收到的上行数据IMM内存指针

 输出参数  : 无
 返 回 值  : PS_SUCC,匹配成功
             PS_FAIL,匹配失败

 修改历史      :
  1.日    期   : 2012年12月15日
    作    者   : x59651
    修改内容   : 新生成函数
*****************************************************************************/
VOS_UINT32 DIPC_MGR_IpV4Match(IMM_ZC_STRU *pstImmZcData)
{
    VOS_UINT8                          *pucIpData;
    DIPC_IPHDR_STRU                    *pstIpPkt;

    pucIpData = IMM_ZcGetDataPtr(pstImmZcData);
    pstIpPkt = (DIPC_IPHDR_STRU *)pucIpData;

    if (DIPC_IP_VER_IPV4 == pstIpPkt->ucIpVer)
    {
        return PS_SUCC;
    }

    return PS_FAIL;
}


/*****************************************************************************
 函 数 名  : DIPC_MGR_IpV6Match
 功能描述  : 检测收到的数据为ipV6类型
 输入参数  : IMM_ZC_STRU *pstImmZcData  收到的上行数据IMM内存指针

 输出参数  : 无
 返 回 值  : PS_SUCC,匹配成功
             PS_FAIL,匹配失败

 修改历史      :
  1.日    期   : 2012年12月15日
    作    者   : x59651
    修改内容   : 新生成函数
*****************************************************************************/
VOS_UINT32 DIPC_MGR_IpV6Match(IMM_ZC_STRU *pstImmZcData)
{
    VOS_UINT8                          *pucIpData;
    DIPC_IPHDR_STRU                    *pstIpPkt;

    pucIpData = IMM_ZcGetDataPtr(pstImmZcData);
    pstIpPkt = (DIPC_IPHDR_STRU *)pucIpData;

    if (DIPC_IP_VER_IPV6 == pstIpPkt->ucIpVer)
    {
        return PS_SUCC;
    }

    return PS_FAIL;
}


/*****************************************************************************
 函 数 名  : DIPC_MGR_AddNewIpService
 功能描述  : DIPC模块添加新的RabId对应的IP类型服务
 输入参数  : VOS_UINT8 ucRabId                              对应的RabId
             DIPC_DEV_ID_ENUM_UINT32 enDevId                对应的设备Id
             DIPC_SERVICE_TYPE_ENUM_UINT32 enDipcServiceId  对应的服务类型
             DIPC_SERV_ULDATA_MATCHFUNC pServiceUlDataMatchFunc 类型对应的匹配上行函数指针
             DIPC_SERV_DLDATA_MATCHFUNC pServiceDlDataMatchFunc 类型对应的匹配下行函数指针

 输出参数  : 无
 返 回 值  : PS_SUCC 匹配成功
             PS_FAIL 匹配失败

 修改历史      :
  1.日    期   : 2012年12月15日
    作    者   : x59651
    修改内容   : 新生成函数

*****************************************************************************/
VOS_UINT32 DIPC_MGR_AddNewIpService(VOS_UINT8 ucRabId,
    DIPC_DEV_ID_ENUM_UINT32 enDevId, DIPC_SERVICE_TYPE_ENUM_UINT32 enDipcServiceType,
    DIPC_SERV_ULDATA_MATCHFUNC pServiceUlDataMatchFunc,     DIPC_SERV_DLDATA_MATCHFUNC pServiceDlDataMatchFunc)
{
    SERVICE_INFO_STRU               stServiceInfo;  /* 带有准备注册的服务的全部信息的结构 */
    SERVICE_INFO_STRU              *pstServiceInfo; /* 注册后的返回服务结构指针 */

    stServiceInfo.ucRabId       = ucRabId;
    stServiceInfo.enDipcDevId   = enDevId;
    stServiceInfo.pUlMatchFunc  = pServiceUlDataMatchFunc;
    stServiceInfo.pDlMatchFunc  = pServiceDlDataMatchFunc;
    stServiceInfo.pUlCallFunc   = ADS_UL_SendPacket;
    stServiceInfo.pDlCallFunc   = DIPC_DEV_UsbWriteData;

    /* 注册服务 */
    pstServiceInfo = DIPC_MGR_RegNewService(&stServiceInfo);
    if (VOS_NULL_PTR == pstServiceInfo)
    {
        return PS_FAIL;
    }

    /* 注册服务和设备之间的映射关系，供上行接收时使用 */
    DIPC_DEV_AddNewIpTypeService(enDevId, enDipcServiceType, pstServiceInfo);

    /* 注册服务和Rab之间的映射关系，供上行接收时使用 */
    DIPC_MGR_AddNewIpTypeService(ucRabId, enDipcServiceType, pstServiceInfo);

    return PS_SUCC;
}


/*****************************************************************************
 函 数 名  : DIPC_MGR_DelIpVService
 功能描述  : DIPC模块添加新的RabId对应的IP类型服务
 输入参数  : VOS_UINT8 ucRabId                              要删除的RabID
             DIPC_BEARER_TYPE_ENUM_UINT8 enDipcServiceType  该RabID上对应的服务类型
 输出参数  : 无
 返 回 值  : PS_SUCC:删除成功
             PS_FAIL:删除失败

 修改历史      :
  1.日    期   : 2012年12月15日
    作    者   : x59651
    修改内容   : 新生成函数

*****************************************************************************/
VOS_UINT32 DIPC_MGR_DelIpVService(VOS_UINT8 ucRabId, DIPC_SERVICE_TYPE_ENUM_UINT32 enDipcServiceType)
{
    SERVICE_INFO_STRU             *pstServiceInfo;

    /* 先找到该RabId的服务 */
    pstServiceInfo = DIPC_MGR_GetServiceByRabId(ucRabId, enDipcServiceType);
    if (VOS_NULL_PTR == pstServiceInfo)
    {
        return PS_FAIL;
    }

    /* 删除Rab和服务之间的映射关系，供上行接收时使用 */
    DIPC_MGR_DelIpTypeService(pstServiceInfo->ucRabId, enDipcServiceType);

    /* 去注册服务和设备之间的映射关系，供上行接收时使用 */
    DIPC_DEV_DelIpTypeService(pstServiceInfo->enDipcDevId, enDipcServiceType);

    /* 去注册服务 */
    DIPC_MGR_DeregService(pstServiceInfo);

    return PS_SUCC;
}


/*****************************************************************************
 函 数 名  : DIPC_MGR_AddNewService
 功能描述  : DIPC模块添加新的RabId对应的服务
 输入参数  : DIPC_DEV_ID_ENUM_UINT32 enDevId                    设备ID
             VOS_UINT8 ucRabId                                  对应的Rab Id
             DIPC_SERVICE_TYPE_ENUM_UINT32 enDipcServiceType    对应的服务类型
 输出参数  : 无
 返 回 值  : PS_SUCC:成功
             PS_FAIL:失败
 修改历史      :
  1.日    期   : 2012年12月15日
    作    者   : x59651
    修改内容   : 新生成函数

*****************************************************************************/
VOS_UINT32 DIPC_MGR_AddNewService(DIPC_DEV_ID_ENUM_UINT32 enDevId,
    VOS_UINT8 ucRabId, DIPC_SERVICE_TYPE_ENUM_UINT32 enDipcServiceType)
{
    VOS_UINT32              ulRsult;

    switch (enDipcServiceType)
    {
        case DIPC_SERVICE_TYPE_IPV4:
            ulRsult = DIPC_MGR_AddNewIpService(ucRabId, enDevId,
                DIPC_SERVICE_TYPE_IPV4, DIPC_MGR_IpV4Match, DIPC_MGR_IpV4Match);
            break;

        case DIPC_SERVICE_TYPE_IPV6:
            ulRsult = DIPC_MGR_AddNewIpService(ucRabId, enDevId,
                DIPC_SERVICE_TYPE_IPV6, DIPC_MGR_IpV6Match, DIPC_MGR_IpV6Match);
            break;

        default:
            /* 和NAS确定DIPC_BEARER_TYPE_IPV4V6类型的消息NAS会分为一次IPV4和一次IPV6发送过来 */
            ulRsult = PS_FAIL;
            break;
    }

    return ulRsult;
}




/*****************************************************************************
 函 数 名  : DIPC_DlAdsDataRcv
 功能描述  : DIPC注册的下行数据接收回调函数
 输入参数  : VOS_UINT8               ucRabId    RabId信息
             IMM_ZC_STRU            *pData      输入数据指针
 输出参数  : 无
 返 回 值  : 无

 修改历史      :
  1.日    期   : 2012年2月15日
    作    者   : x59651
    修改内容   : 新生成函数

*****************************************************************************/
VOS_UINT32 DIPC_MGR_DlAdsDataRcv(VOS_UINT8 ucRabId, IMM_ZC_STRU *pData)
{
    RAB_SERVICE_INFO_STRU              *pstRabServiceInfo;
    DIPC_SERVICE_TYPE_ENUM_UINT32       enServiceType;
    SERVICE_INFO_STRU                  *pstServInfo;

    DIPC_TraceDlData(ucRabId, pData);

    pstRabServiceInfo = &g_astRabService[ucRabId];

    for (enServiceType = 0; enServiceType < DIPC_SERVICE_TYPE_MAX_NUM; enServiceType++)
    {
        if (PS_TRUE == DIPC_GET_SERVICE_REG(pstRabServiceInfo->ulServiceMask, enServiceType))
        {
            pstServInfo = pstRabServiceInfo->apstServiceInfo[enServiceType];

            if (PS_SUCC == pstServInfo->pDlMatchFunc(pData))
            {
                if (VOS_OK != pstServInfo->pDlCallFunc(pstServInfo->enDipcDevId, pData))
                {
                    DIPC_PrintLog2(PS_PID_APP_DIPC, 0, PS_PRINT_WARNING,
                        "DIPC, DIPC_MGR_DlAdsDataRcv, call pDlFunc return fail,ulDeviceId <1>, ucRabID",
                        (VOS_INT32)pstServInfo->enDipcDevId, (VOS_INT32)pstServInfo->ucRabId);
                    IMM_ZcFree(pData);
                    g_stDipcStaticInfo.astDipcDevStaticInfo[pstServInfo->enDipcDevId].ulFailSendDlPacketNums++;
                    return PS_FAIL;
                }

                /* 成功接收，则退出并记录 */
                g_stDipcStaticInfo.astDipcDevStaticInfo[pstServInfo->enDipcDevId].ulSuccSendDlPacketNums++;
                return PS_SUCC;
            }
        }
    }

    /* 该设备上没有找到对应的服务，释放数据 */
    g_stDipcStaticInfo.ulFailMatchDlPacketNums++;
    IMM_ZcFree(pData);
    return PS_FAIL;
}


/*****************************************************************************
 函 数 名  : DIPC_MGR_GetServiceByRabId
 功能描述  : 通过RabId获取服务
 输入参数  : VOS_UINT8 ucRabId                                  用来查询设备句柄的Rab Id
             DIPC_SERVICE_TYPE_ENUM_UINT32 enDipcServiceType    服务类型

 输出参数  : 无
 返 回 值  : 服务对应数据结构的指针

 修改历史      :
  1.日    期   : 2012年2月15日
    作    者   : x59651
    修改内容   : 新生成函数

*****************************************************************************/
SERVICE_INFO_STRU* DIPC_MGR_GetServiceByRabId(VOS_UINT8 ucRabId,
    DIPC_SERVICE_TYPE_ENUM_UINT32 enDipcServiceType)
{
    RAB_SERVICE_INFO_STRU          *pstRabServiceInfo;

    pstRabServiceInfo = &g_astRabService[ucRabId];

    /* 如果对应的服务类型没有注册，则报错 */
    if (PS_TRUE != DIPC_GET_SERVICE_REG(pstRabServiceInfo->ulServiceMask, enDipcServiceType))
    {
        DIPC_PrintLog(PS_PID_APP_DIPC, 0, PS_PRINT_WARNING,
            "DIPC, DIPC_MGR_GetServiceByRabId, no service.\n");
        return VOS_NULL_PTR;
    }

    /* 如果掩码说明服务注册了但是没有对应的服务结构，说明内部维护错误 */
    if (VOS_NULL_PTR == pstRabServiceInfo->apstServiceInfo[enDipcServiceType])
    {
        DIPC_PrintLog(PS_PID_APP_DIPC, 0, PS_PRINT_WARNING,
            "DIPC, DIPC_MGR_GetServiceByRabId, no service but with mask.\n");
        return VOS_NULL_PTR;
    }

    return pstRabServiceInfo->apstServiceInfo[enDipcServiceType];
}

/*****************************************************************************
 函 数 名  : DIPC_MGR_AddNewIpTypeService
 功能描述  : DIPC模块添加新的RAB对应的IP类型服务
 输入参数  : VOS_UINT8 ucRabId                                  Rab Id
             DIPC_SERVICE_TYPE_ENUM_UINT32 enDipcServiceTypes   服务类型
             DEV_SERVICE_INFO_STRU *pstDevServiceInfo           设备服务结构

 输出参数  : 无
 返 回 值  : 无

 修改历史      :
  1.日    期   : 2013年2月19日
    作    者   : x59651
    修改内容   : 新生成函数
*****************************************************************************/
VOS_VOID DIPC_MGR_AddNewIpTypeService(VOS_UINT8 ucRabId,
    DIPC_SERVICE_TYPE_ENUM_UINT32 enDipcServiceType, SERVICE_INFO_STRU *pstServiceInfo)
{
    RAB_SERVICE_INFO_STRU          *pstRabServiceInfo;

    pstRabServiceInfo = &g_astRabService[ucRabId];

    pstRabServiceInfo->apstServiceInfo[enDipcServiceType] = pstServiceInfo;
    DIPC_SET_SERVICE_REG(pstRabServiceInfo->ulServiceMask, enDipcServiceType);

    pstRabServiceInfo->ulServiceCnt++;

    return;
}

/*****************************************************************************
 函 数 名  : DIPC_MGR_DelIpTypeService
 功能描述  : DIPC模块删除该RAB上对应的服务
 输入参数  : VOS_UINT8                      ucRabId             对应的Rab Id
             DIPC_SERVICE_TYPE_ENUM_UINT32  enDipcServiceType   对应服务的类型
 输出参数  : 无
 返 回 值  : 无

 修改历史      :
  1.日    期   : 2012年12月15日
    作    者   : x59651
    修改内容   : 新生成函数
*****************************************************************************/
VOS_VOID DIPC_MGR_DelIpTypeService(VOS_UINT8 ucRabId,
    DIPC_SERVICE_TYPE_ENUM_UINT32 enDipcServiceType)
{
    RAB_SERVICE_INFO_STRU          *pstRabServiceInfo;

    pstRabServiceInfo = &g_astRabService[ucRabId];

    pstRabServiceInfo->apstServiceInfo[enDipcServiceType] = VOS_NULL_PTR;
    DIPC_CLR_SERVICE_REG(pstRabServiceInfo->ulServiceMask, enDipcServiceType);

    pstRabServiceInfo->ulServiceCnt--;

    return;
}

/*****************************************************************************
 函 数 名  : DIPC_GetDevIdByRabId
 功能描述  : 通过RabId获取内部使用的DEV Id
 输入参数  : VOS_UINT8 ucRabId  用来查询设备句柄的Rab Id

 输出参数  : 无
 返 回 值  : RabId对应的内部使用设备Id,无效时为DIPC_DEV_BUTT

 修改历史      :
  1.日    期   : 2013年2月19日
    作    者   : x59651
    修改内容   : 新生成函数

*****************************************************************************/
DIPC_DEV_ID_ENUM_UINT32 DIPC_GetDevIdByRabId(VOS_UINT8 ucRabId)
{
    RAB_SERVICE_INFO_STRU              *pstRabServiceInfo;
    DIPC_SERVICE_TYPE_ENUM_UINT32       enServiceNum;
    SERVICE_INFO_STRU                  *pstServInfo = VOS_NULL_PTR;

    pstRabServiceInfo = &g_astRabService[ucRabId];

    for (enServiceNum = 0; enServiceNum < DIPC_SERVICE_TYPE_MAX_NUM; enServiceNum++)
    {
        if (PS_TRUE == DIPC_GET_SERVICE_REG(pstRabServiceInfo->ulServiceMask, enServiceNum))
        {
            pstServInfo = pstRabServiceInfo->apstServiceInfo[enServiceNum];
            break;
        }
    }

    if (VOS_NULL_PTR != pstServInfo)
    {
        return (pstServInfo->enDipcDevId);
    }

    return  DIPC_DEV_BUTT;
}


/*****************************************************************************
 函 数 名  : DIPC_GetDevHandleByRabId
 功能描述  : 通过RabId获取设备句柄，此函数是给AT使用
 输入参数  : VOS_UINT8 ucRabId  用来查询设备句柄的Rab Id

 输出参数  : 无
 返 回 值  : RabId对应的句柄,无效时为UDI_INVALID_HANDLE

 修改历史      :
  1.日    期   : 2012年2月15日
    作    者   : x59651
    修改内容   : 新生成函数

*****************************************************************************/
UDI_HANDLE DIPC_GetDevHandleByRabId(VOS_UINT8 ucRabId)
{
    DIPC_DEV_ID_ENUM_UINT32             enDipcDevId;

    if ((ucRabId < MIN_RAB_ID) || (ucRabId > MAX_RAB_ID))
    {
        DIPC_PrintLog1(PS_PID_APP_DIPC, 0, PS_PRINT_WARNING,
            "DIPC, DIPC_GetDevHandleByRabId, ucRabId <1> exceed the range.\n", ucRabId);
        return UDI_INVAL_DEV_ID;
    }

    enDipcDevId  = DIPC_GetDevIdByRabId(ucRabId);

    if (DIPC_DEV_BUTT == enDipcDevId)
    {
        return UDI_INVAL_DEV_ID;
    }

    return g_astDevInfo[enDipcDevId].slUdiHsicHdl;
}

/*****************************************************************************
 函 数 名  : DIPC_CheckRelation
 功能描述  : 检查RabId和Dev Id之间的关系是否正确
             认为为正确的情况包括:
             一个Dev对应2个Rab，分别为IPV4和IPV6
             一个Dev对应1个Rab，上面同时支持IPV4和IPV6，
             一个Dev对应1个Rab，为IPV4
             一个Dev对应1个Rab，为IPV6

             认为为错误的情况包括:
             2个Dev对应一个Rab的情况
             已经有一个Dev对应一个Rab，又被重复配置了一次
 输入参数  : AT_DIPC_PDP_ACT_STRU *pstAtDipcPdpActMsg   消息
 输出参数  : 无
 返 回 值  : VOS_OK:无错误
             VOS_ERR:有错误

 修改历史      :
  1.日    期   : 2013年2月19日
    作    者   : x59651
    修改内容   : 新生成函数

*****************************************************************************/
VOS_UINT32 DIPC_CheckRelation(AT_DIPC_PDP_ACT_STRU *pstAtDipcPdpActMsg)
{
    RAB_SERVICE_INFO_STRU              *pstRabServiceInfo;
    DIPC_SERVICE_TYPE_ENUM_UINT32       enServiceNum;
    SERVICE_INFO_STRU                  *pstServInfo = VOS_NULL_PTR;
    UDI_DEVICE_ID_E                       enUdiDevId;
    DIPC_SERVICE_TYPE_ENUM_UINT32       enDipcServiceType;
    DEV_SERVICE_INFO_STRU              *pstDevServiceInfo;

    enDipcServiceType = DIPC_GET_SERVICE_TYPE_BY_BEARER_TYPE(pstAtDipcPdpActMsg->enBearerType);
    pstRabServiceInfo = &g_astRabService[pstAtDipcPdpActMsg->ucRabId];

    /* 之前没有注册，认为为正确情况 */
    if (0 == pstRabServiceInfo->ulServiceCnt)
    {
        return VOS_OK;
    }

    /*  如果ServiceCnt为0，但是ServiceMask不为0，则认为内部异常，不处理后续消息 */
    if (0 == pstRabServiceInfo->ulServiceMask)
    {
        DIPC_PrintLog1(PS_PID_APP_DIPC, 0, PS_PRINT_WARNING,
            "DIPC, DIPC_CheckRelation, Rab <1> Service is wrong.", pstAtDipcPdpActMsg->ucRabId);
        return VOS_ERR;
    }

    /* 如果该Rab上已经有对应类型的服务，认为为错误 */
    if (PS_TRUE == DIPC_GET_SERVICE_REG(pstRabServiceInfo->ulServiceMask, enDipcServiceType))
    {
        DIPC_PrintLog2(PS_PID_APP_DIPC, 0, PS_PRINT_WARNING,
            "DIPC, DIPC_CheckRelation, Rab <1> type<2> is already reg.",
            pstAtDipcPdpActMsg->ucRabId, pstAtDipcPdpActMsg->enBearerType);
        return VOS_ERR;
    }


    for (enServiceNum = 0; enServiceNum < DIPC_SERVICE_TYPE_MAX_NUM; enServiceNum++)
    {
        if (PS_TRUE == DIPC_GET_SERVICE_REG(pstRabServiceInfo->ulServiceMask, enServiceNum))
        {
            pstServInfo = pstRabServiceInfo->apstServiceInfo[enServiceNum];
            break;
        }
    }

    /* 如果pstRabServiceInfo->ulServiceCnt不为0，理论上不会出现pstServInfo为空的情况，
    此处是为了消除PC LINT告警 */
    if (VOS_NULL_PTR == pstServInfo)
    {
        return VOS_ERR;
    }

    /* 如果该Rab上已经有其它类型的服务，认为对应的设备Id要和新的消息中的一致 */
    enUdiDevId = g_astDevInfo[pstServInfo->enDipcDevId].enUdiDevId;
    if (pstAtDipcPdpActMsg->enUdiDevId != enUdiDevId)
    {
        DIPC_PrintLog2(PS_PID_APP_DIPC, 0, PS_PRINT_WARNING,
            "DIPC, DIPC_CheckRelation, pstAtDipcPdpActMsg->enUdiDevId <1> not with enUdiDevId <2>.",
            pstAtDipcPdpActMsg->enUdiDevId, enUdiDevId);
        return VOS_ERR;
    }

    /* 如果该设备上已经有对应类型的服务，认为为错误 */
    pstDevServiceInfo = &(g_astDevService[pstServInfo->enDipcDevId]);
    if (PS_TRUE == DIPC_GET_SERVICE_REG(pstDevServiceInfo->ulServiceMask, enDipcServiceType))
    {
        DIPC_PrintLog2(PS_PID_APP_DIPC, 0, PS_PRINT_WARNING,
            "DIPC, DIPC_CheckRelation, Dev <1> type<2> is already reg.",
            pstAtDipcPdpActMsg->enUdiDevId, pstAtDipcPdpActMsg->enBearerType);
        return VOS_ERR;
    }

    return VOS_OK;
}

/*****************************************************************************
 函 数 名  : DIPC_MGR_CheckPdpActPara
 功能描述  : PDP激活消息参数检查
 输入参数  : AT_DIPC_PDP_ACT_STRU  *pstAtDipcPdpActMsg  AT发来的PDP激活消息指针
 输出参数  : 无
 返 回 值  : VOS_OK:无错误
             VOS_ERR:有错误

 修改历史      :
  1.日    期   : 2012年12月15日
    作    者   : x59651
    修改内容   : 新生成函数

*****************************************************************************/
VOS_UINT32 DIPC_CheckPdpActPara(AT_DIPC_PDP_ACT_STRU *pstAtDipcPdpActMsg)
{
    if ((pstAtDipcPdpActMsg->ucRabId < MIN_RAB_ID) || (pstAtDipcPdpActMsg->ucRabId > MAX_RAB_ID))
    {
        DIPC_PrintLog1(PS_PID_APP_DIPC, 0, PS_PRINT_WARNING,
            "DIPC, DIPC_CheckPdpActPara, Rab Id exceed the range!\n",
            pstAtDipcPdpActMsg->ucRabId);
        return VOS_ERR;
    }

    /* 和NAS协商如果一个RabId上既有IPV4又有IPV6，需要分2次下发，DIPC_BEARER_TYPE_IPV4V6保留是给NAS内部使用 */
    if (DIPC_BEARER_TYPE_IPV4V6 <= pstAtDipcPdpActMsg->enBearerType)
    {
        DIPC_PrintLog1(PS_PID_APP_DIPC, 0, PS_PRINT_WARNING,
            "DIPC, DIPC_CheckPdpActPara, pstAtDipcPdpActMsg->enBearerType <1> exceed the ranger.",
            pstAtDipcPdpActMsg->enBearerType);
        return VOS_ERR;
    }

    if (VOS_OK != DIPC_DEV_CheckUdiDevIdPara(pstAtDipcPdpActMsg->enUdiDevId))
    {
        DIPC_PrintLog1(PS_PID_APP_DIPC, 0, PS_PRINT_WARNING,
            "DIPC, DIPC_CheckPdpActPara, pstAtDipcPdpActMsg->enUdiDevId <1> exceed the ranger.",
            pstAtDipcPdpActMsg->enUdiDevId);
        return VOS_ERR;
    }

    if (VOS_OK != DIPC_CheckRelation(pstAtDipcPdpActMsg))
    {
        return VOS_ERR;
    }

    return VOS_OK;
}

/*****************************************************************************
 函 数 名  : DIPC_RcvAtPdpActIndProc
 功能描述  : DIPC接收来自AT模块ID_AT_DIPC_PDP_ACT_IND的消息处理函数
 输入参数  : AT_DIPC_PDP_ACT_STRU *pstAtDipcPdpActMsg    AT发来的PDP激活消息指针
 输出参数  : 无
 返 回 值  : 无

 修改历史      :
  1.日    期   : 2012年2月15日
    作    者   : x59651
    修改内容   : 新生成函数

*****************************************************************************/
VOS_VOID DIPC_RcvAtPdpActIndProc(AT_DIPC_PDP_ACT_STRU *pstAtDipcPdpActMsg)
{
    VOS_UINT32                          ulRslt;
    DIPC_DEV_ID_ENUM_UINT32             enDevId;

    if (VOS_OK != DIPC_CheckPdpActPara(pstAtDipcPdpActMsg))
    {
        DIPC_PrintLog(PS_PID_APP_DIPC, 0, PS_PRINT_WARNING,
            "DIPC, DIPC_RcvAtPdpActIndProc, receive error message.\n");
        return;
    }

    /* 通过NAS使用的外部设备ID获取内部设备ID */
    enDevId = DIPC_DEV_GetDevIdByUdiId(pstAtDipcPdpActMsg->enUdiDevId);
    if (DIPC_DEV_BUTT <= enDevId)    /* 如果对应的设备ID不存在 */
    {
        DIPC_PrintLog(PS_PID_APP_DIPC, 0, PS_PRINT_WARNING,
            "DIPC, DIPC_RcvAtPdpActIndProc, can not find the device.\n");
        return;
    }

    /* 在DIPC内部注册一个新的服务 */
    ulRslt = DIPC_MGR_AddNewService(enDevId, pstAtDipcPdpActMsg->ucRabId,
        DIPC_GET_SERVICE_TYPE_BY_BEARER_TYPE(pstAtDipcPdpActMsg->enBearerType));

    if (PS_SUCC != ulRslt)
    {
        DIPC_MappingInfoTrace(ID_DIPC_ADD_NEW_MAPPING_INFO_FAIL);
        return;
    }

    if (VOS_OK != (ADS_DL_RegDlDataCallback(pstAtDipcPdpActMsg->ucRabId, DIPC_DlAdsDataRcv, 0)))
    {
        DIPC_PrintLog(PS_PID_APP_DIPC, 0, PS_PRINT_WARNING,
            "DIPC_RcvAtPdpActIndProc, call ADS_DL_RegDlDataCallback fail!\n");
        DIPC_MappingInfoTrace(ID_DIPC_REG_ADS_DL_DATA_CALLBACK_FAIL);
        return;
    }

    DIPC_MappingInfoTrace(ID_DIPC_PDP_ACT_SUCC);

    return;
}

/*****************************************************************************
 函 数 名  : DIPC_MGR_CheckPdpActPara
 功能描述  : 检查PDP去激活消息参数是否正确
 输入参数  : AT_DIPC_PDP_DEACT_STRU  *pstAtDipcPdpDeactMsg  AT发来的PDP去激活消息指针
 输出参数  : 无
 返 回 值  : VOS_UINT32 VOS_OK:无错误,VOS_ERR:有错误

 修改历史      :
  1.日    期   : 2012年12月15日
    作    者   : x59651
    修改内容   : 新生成函数

*****************************************************************************/
VOS_UINT32 DIPC_CheckPdpRelPara(AT_DIPC_PDP_DEACT_STRU *pstAtDipcPdpDeactMsg)
{
    if ((pstAtDipcPdpDeactMsg->ucRabId < MIN_RAB_ID) || (pstAtDipcPdpDeactMsg->ucRabId > MAX_RAB_ID))
    {
        DIPC_PrintLog1(PS_PID_APP_DIPC, 0, PS_PRINT_WARNING,
            "DIPC, DIPC_CheckPdpRelPara, Rab Id exceed the range!\n"
            , pstAtDipcPdpDeactMsg->ucRabId);
        return VOS_ERR;
    }

    if (DIPC_BEARER_TYPE_IPV4V6 <= pstAtDipcPdpDeactMsg->enBearerType)
    {
        DIPC_PrintLog1(PS_PID_APP_DIPC, 0, PS_PRINT_WARNING,
            "DIPC, DIPC_CheckPdpRelPara, pstAtDipcPdpDeactMsg->enBearerType <1> exceed the ranger.",
            pstAtDipcPdpDeactMsg->enBearerType);
        return VOS_ERR;
    }

    /* 如果对应的Rab Id没有注册服务 */
    if (VOS_NULL_PTR == DIPC_MGR_GetServiceByRabId(pstAtDipcPdpDeactMsg->ucRabId,
        DIPC_GET_SERVICE_TYPE_BY_BEARER_TYPE(pstAtDipcPdpDeactMsg->enBearerType)))
    {
        DIPC_PrintLog1(PS_PID_APP_DIPC, 0, PS_PRINT_WARNING,
            "DIPC, DIPC_CheckPdpRelPara, Rab Id <1> not exist!\n"
            , pstAtDipcPdpDeactMsg->ucRabId);
        return VOS_ERR;
    }

    return VOS_OK;
}

/*****************************************************************************
 函 数 名  : DIPC_RcvAtPdpRelIndProc
 功能描述  : DIPC接收来自AT模块ID_AT_DIPC_PDP_REL_IND的消息处理函数
 输入参数  : AT_DIPC_PDP_DEACT_STRU *pstAtDipcPdpDeactMsg    AT发来的PDP去激活消息指针
 输出参数  : 无
 返 回 值  : 无

 修改历史      :
  1.日    期   : 2012年2月15日
    作    者   : x59651
    修改内容   : 新生成函数

*****************************************************************************/
VOS_VOID DIPC_RcvAtPdpRelIndProc(AT_DIPC_PDP_DEACT_STRU *pstAtDipcPdpDeactMsg)
{
    VOS_UINT32              ulRslt;

    if (VOS_OK != DIPC_CheckPdpRelPara(pstAtDipcPdpDeactMsg))
    {
        DIPC_PrintLog(PS_PID_APP_DIPC, 0, PS_PRINT_WARNING,
            "DIPC, DIPC_RcvAtPdpRelIndProc, receive error message.\n");
        return;
    }

    ulRslt = DIPC_MGR_DelIpVService(pstAtDipcPdpDeactMsg->ucRabId, DIPC_GET_SERVICE_TYPE_BY_BEARER_TYPE(pstAtDipcPdpDeactMsg->enBearerType));

    if (PS_SUCC != ulRslt)
    {
        DIPC_MappingInfoTrace(ID_DIPC_DEL_MAPPING_INFO_FAIL);
        return;
    }

    if (VOS_OK != (ADS_DL_RegDlDataCallback(pstAtDipcPdpDeactMsg->ucRabId, VOS_NULL_PTR, 0)))
    {
        DIPC_PrintLog(PS_PID_APP_DIPC, 0, PS_PRINT_WARNING,
            "DIPC_RcvAtPdpRelIndProc, call ADS_DL_RegDlDataCallback fail!\n");
        DIPC_MappingInfoTrace(ID_DIPC_DEREG_ADS_DL_DATA_CALLBACK_FAIL);
        return;
    }

    DIPC_MappingInfoTrace(ID_DIPC_PDP_DEACT_SUCC);

    return;
}


/*****************************************************************************
 函 数 名  : DIPC_DlAdsDataRcv
 功能描述  : DIPC注册的下行数据接收回调函数
 输入参数  : VOS_UINT8               ucRabId    RabId信息
             IMM_ZC_STRU            *pData      输入数据指针
             ADS_PKT_TYPE_ENUM_UINT8 enPktType  没有使用，只是为了兼容NDIS模式，PPP也有该入参，没有使用
 输出参数  : 无
 返 回 值  : 无

 修改历史      :
  1.日    期   : 2012年2月15日
    作    者   : x59651
    修改内容   : 新生成函数

*****************************************************************************/
VOS_UINT32 DIPC_DlAdsDataRcv(VOS_UINT8 ucRabId, IMM_ZC_STRU *pData,
    ADS_PKT_TYPE_ENUM_UINT8 enPktType, VOS_UINT32 ulExParam)
{
    VOS_UINT16  usApp;      /* 使用skb_buff结构中已有字段传递上下行和参数信息 */

    if (VOS_NULL_PTR == pData)
    {
        g_stDipcStaticInfo.ulNullDlPacketNums++;
        DIPC_PrintLog(PS_PID_APP_DIPC, 0, PS_PRINT_WARNING,
            "DIPC, DIPC_DlAdsDataRcv, pData is null.\n");
        return PS_FAIL;
    }

    g_stDipcStaticInfo.ulSuccGetDlPacketNums++;

    usApp = DIPC_SET_APP(ID_DIPC_DL_DATA, ucRabId);

    IMM_ZcSetUserApp(pData, usApp);

    return DIPC_EnqueueData(pData);
}

/*****************************************************************************
 Prototype      : DIPC_ProcDataNotify
 Description    : 处理DIPC_DATA_PROC_NOTIFY数据指示
 Input          : VOS_VOID
 Output         : ---
 Return Value   : PS_SUCC   --- 成功
                  PS_FAIL   --- 失败
 Calls          : ---
 Called By      : ---

 History        : ---
  1.Date        : 2013-03-20
    Author      : x59651
    Modification: Created function
*****************************************************************************/
VOS_VOID  DIPC_ProcDataNotify(VOS_VOID)
{
    IMM_ZC_STRU                *pstMem;
    VOS_INT32                   lLockKey;
    VOS_UINT16                  usApp;
    VOS_UINT8                   ucDir;

    lLockKey = VOS_SplIMP();
    g_stDipcDataQ.ulNotifyMsgCnt--;
    VOS_Splx(lLockKey);

    for (;;)
    {
        pstMem  = (IMM_ZC_STRU *)IMM_ZcDequeueHead(&g_stDipcDataQ.stDipcDataQ);

        /* 队列为空的时候返回空指针 */
        if ( VOS_NULL_PTR == pstMem )
        {
            return;
        }

        /*处理该结点(结点的释放动作已经在各处理函数内部完成，无需再释放结点)*/

        usApp = IMM_ZcGetUserApp(pstMem);

        ucDir = (VOS_UINT8)DIPC_GET_DIR(usApp);

        switch ( ucDir )
        {
            case ID_DIPC_UL_DATA:
                DIPC_MGR_UlDataProc(DIPC_GET_PARA(usApp),pstMem);
                break;

            case ID_DIPC_DL_DATA:
                DIPC_MGR_DlAdsDataRcv(DIPC_GET_PARA(usApp),pstMem);
                break;

            default:
                IMM_ZcFree(pstMem);
                DIPC_PrintLog1(PS_PID_APP_DIPC, 0, PS_PRINT_WARNING,
                    "DIPC_ProcDataNotify, WARNING, ucDir %d is Abnormal!", ucDir);
                break;
        }
    } /* for (;;) */
} /* DIPC_ProcDataNotify */


/*****************************************************************************
 函 数 名  : DIPC_MsgProc
 功能描述  : DIPC的消息处理函数
 输入参数  : MsgBlock *pMsgBlock    从AT发来的消息

 输出参数  : 无
 返 回 值  : VOS_UINT32

 修改历史      :
  1.日    期   : 2012年2月15日
    作    者   : x59651
    修改内容   : 新生成函数

*****************************************************************************/
VOS_UINT32 DIPC_AtMsgProc( const MsgBlock *pMsgBlock )
{
    TTF_U32MSG_COMM_HEAD_STRU  *pstHsicCtrlMsg    = (TTF_U32MSG_COMM_HEAD_STRU *)pMsgBlock;

    if (WUEPS_PID_AT == pstHsicCtrlMsg->ulSenderPid)
    {
        switch (pstHsicCtrlMsg->ulMsgType)
        {
            case ID_AT_DIPC_PDP_ACT_IND:
                DIPC_RcvAtPdpActIndProc((AT_DIPC_PDP_ACT_STRU *)pMsgBlock);
                break;

            case ID_AT_DIPC_PDP_REL_IND:
                DIPC_RcvAtPdpRelIndProc((AT_DIPC_PDP_DEACT_STRU *)pMsgBlock);
                break;

            default:
                DIPC_PrintLog1(PS_PID_APP_DIPC, 0, PS_PRINT_WARNING,
                    "DIPC, DIPC_AtMsgProc, received msg ulMsgType <1>",
                    (VOS_INT32)pstHsicCtrlMsg->ulMsgType);
                return VOS_ERR;
        }
    }
    else if (PS_PID_APP_DIPC == pstHsicCtrlMsg->ulSenderPid)
    {
        if (ID_DIPC_DATA_NOTIFY_REQ == pstHsicCtrlMsg->ulMsgType)
        {
            DIPC_ProcDataNotify();
        }
        else
        {
            DIPC_PrintLog2(PS_PID_APP_DIPC, 0, PS_PRINT_WARNING,
                "DIPC, DIPC_AtMsgProc, received msg ulSenderPid<1> , ulMsgType <2>",
                (VOS_INT32)pstHsicCtrlMsg->ulSenderPid,
                (VOS_INT32)pstHsicCtrlMsg->ulMsgType);
            return VOS_ERR;
        }
    }
    else
    {
        DIPC_PrintLog1(PS_PID_APP_DIPC, 0, PS_PRINT_WARNING,
            "DIPC, DIPC_AtMsgProc, received msg ulSenderPid<1> ",
            (VOS_INT32)pstHsicCtrlMsg->ulSenderPid);
        return VOS_ERR;
    }

    return VOS_OK;
}


/*****************************************************************************
 Prototype      : DIPC_DataQInit()
 Description    : DIPC数据队列的初始化
 Input          : VOS_VOID
 Output         :
 Return Value   : VOID
 Calls          :
 Called By      :
 History        :
  1.Date        : 2008-07-16
    Author      : L47619
    Modification: Created function
*****************************************************************************/
VOS_VOID DIPC_DataQInit(VOS_VOID)
{
    IMM_ZC_HEAD_STRU                    *pstDataQ;


    pstDataQ    = &(g_stDipcDataQ.stDipcDataQ);

    VOS_MemSet(&g_stDipcDataQ, 0, sizeof(g_stDipcDataQ));

    IMM_ZcQueueHeadInit(pstDataQ);

    return;
}

/*****************************************************************************
 函 数 名  : DIPC_Init
 功能描述  : APP核 DIPC功能的初始化函数
 输入参数  : VOS_VOID
 输出参数  : 无
 返 回 值  : VOS_OK  初始化成功

 修改历史      :
  1.日    期   : 2012年2月16日
    作    者   : x59651
    修改内容   : 新生成函数

*****************************************************************************/
VOS_UINT32 DIPC_Init( VOS_VOID )
{
    VOS_UINT8                       ucRabId;
    VOS_UINT32                      ulServiceId;
    SERVICE_INFO_STRU              *pstServiceInfo;
    DIPC_DEV_ID_ENUM_UINT32         enDevId;
    DIPC_SERVICE_TYPE_ENUM_UINT32   enServiceType;

    /* 初始化Rab到服务的映射表 */
    for (ucRabId = 0; ucRabId < RAB_MAX_NUM; ucRabId++)
    {
        for (enServiceType = DIPC_SERVICE_TYPE_IPV4; enServiceType < DIPC_SERVICE_TYPE_BUTT; enServiceType++)
        {
            g_astRabService[ucRabId].apstServiceInfo[enServiceType] = VOS_NULL_PTR;
        }
        g_astRabService[ucRabId].ulServiceCnt   = 0;
        g_astRabService[ucRabId].ulServiceMask  = 0;
    }

    /* 初始化服务信息表*/
    for (ulServiceId = 0; ulServiceId < SERVICE_MAX_NUM; ulServiceId++)
    {
        pstServiceInfo = &g_stTotalServiceInfo.astServiceInfo[ulServiceId];
        pstServiceInfo->enDipcDevId     = DIPC_DEV_BUTT;
        pstServiceInfo->ucRabId         = 0;
        pstServiceInfo->pDlCallFunc     = VOS_NULL_PTR;
        pstServiceInfo->pUlCallFunc     = VOS_NULL_PTR;
        pstServiceInfo->pUlMatchFunc    = VOS_NULL_PTR;
    }
    g_stTotalServiceInfo.ulServiceNum   = 0;
    g_stTotalServiceInfo.ulServiceMask  = 0;

    /* 初始化设备到服务的映射表 */
    for (enDevId = DIPC_DEV_ID1; enDevId < DIPC_DEV_BUTT; enDevId++)
    {
        for (enServiceType = DIPC_SERVICE_TYPE_IPV4; enServiceType < DIPC_SERVICE_TYPE_BUTT; enServiceType++)
        {
            g_astDevService[enDevId].apstServiceInfo[enServiceType] = VOS_NULL_PTR;
        }
        g_astDevService[enDevId].ulServiceCnt   = 0;
        g_astDevService[enDevId].ulServiceMask  = 0;
    }

    /* 如果HSIC通道已经枚举成功，则由协议栈执行初始化操作；否则将初始化函数注册至底软，
        由底软在HSIC枚举成功后调用以进行初始化*/
    if (VOS_TRUE == DRV_GET_HSIC_ENUM_STATUS())
    {
        DIPC_DEV_PortInit();
    }
    else
    {
        DRV_HSIC_REGUDI_ENABLECB((HSIC_UDI_ENABLE_CB_T)DIPC_DEV_PortInit);
    }

    DIPC_StaticInfoInit();

    DIPC_DataQInit();

    return VOS_OK;
}


/*****************************************************************************
 函 数 名  : DIPC_Pid_InitFunc
 功能描述  : DIPC PID初始化
 输入参数  : VOS_INIT_PHASE_DEFINE ip   初始化类型
 输出参数  : 无
 返 回 值  : VOS_UINT32

 修改历史      :
  1.日    期   : 2012年2月16日
    作    者   : x59651
    修改内容   : 新生成函数
*****************************************************************************/
VOS_UINT32 DIPC_Pid_InitFunc( enum VOS_INIT_PHASE_DEFINE ip )
{
    switch( ip )
    {
        case VOS_IP_LOAD_CONFIG:
            DIPC_Init();
            break;
        case VOS_IP_FARMALLOC:
        case VOS_IP_INITIAL:
        case VOS_IP_ENROLLMENT:
        case VOS_IP_LOAD_DATA:
        case VOS_IP_FETCH_DATA:
        case VOS_IP_STARTUP:
        case VOS_IP_RIVAL:
        case VOS_IP_KICKOFF:
        case VOS_IP_STANDBY:
        case VOS_IP_BROADCAST_STATE:
        case VOS_IP_RESTART:
            break;
        default:
            break;
    }

    return PS_SUCC;
}


/*****************************************************************************
 函 数 名  : DIPC_TraceUlData
 功能描述  : DIPC模块对于底软上报的数据进行勾包，是否输出使用全局变量控制
 输入参数  : DIPC_DEV_ACM_ID_ENUM_UINT32 ulDeviceId  通知有上行数据的设备id,使用的为内部ID
             IMM_ZC_STRU *pstData   上行数据地址
 输出参数  : 无
 返 回 值  : 无

 修改历史      :
  1.日    期   : 2012年2月16日
    作    者   : x59651
    修改内容   : 新生成函数

*****************************************************************************/
VOS_VOID DIPC_TraceUlData(DIPC_DEV_ID_ENUM_UINT32 ulDeviceId, IMM_ZC_STRU *pstData)
{
    TRACE_UL_DIPC_DATA_MSG             *pstTraceUlData;
    VOS_UINT32                          ulDataLen;
    VOS_UINT8                          *pucData;
    IMM_ZC_STRU                        *pstDataNode;


    if (PS_TRUE != g_ulDipcTraceFlag)
    {
        return;
    }

    pstDataNode = pstData;

    while(VOS_NULL_PTR != pstDataNode)
    {
        pstTraceUlData  = g_pstDipcTraceUlData;
        pstTraceUlData->ulSenderCpuId   = VOS_LOCAL_CPUID;
        pstTraceUlData->ulSenderPid     = PS_PID_APP_DIPC;
        pstTraceUlData->ulReceiverCpuId = VOS_LOCAL_CPUID;
        pstTraceUlData->ulReceiverPid   = PS_PID_APP_DIPC;
        pstTraceUlData->enMsgType       = ID_DIPC_TRACE_UL_DATA;
        pstTraceUlData->enDevId         = ulDeviceId;

        ulDataLen   = IMM_ZcGetUsedLen(pstDataNode);
        pucData     = IMM_ZcGetDataPtr(pstDataNode);
        pstTraceUlData->ulDataLen       = ulDataLen;
        pstTraceUlData->ulLength        = (((sizeof(TRACE_UL_DIPC_DATA_MSG) - VOS_MSG_HEAD_LENGTH) - DIPC_DATA_MAX_DATA_LEN) + ulDataLen);
        mdrv_memcpy(pstTraceUlData->aucData, pucData, ulDataLen);
        DIAG_TraceReport(pstTraceUlData);

        pstDataNode = pstDataNode->next;
    }

    return;
}


/*****************************************************************************
 函 数 名  : DIPC_TraceDlData
 功能描述  : DIPC模块对于底软上报的数据进行勾包，是否输出使用全局变量控制
 输入参数  : VOS_UINT8    ucRabId       RabId信息
             IMM_ZC_STRU *pstData       上行数据地址
 输出参数  : 无
 返 回 值  : 无

 修改历史      :
  1.日    期   : 2012年2月16日
    作    者   : x59651
    修改内容   : 新生成函数

*****************************************************************************/
VOS_VOID DIPC_TraceDlData(VOS_UINT8 ucRabId, IMM_ZC_STRU *pstData)
{
    TRACE_DL_DIPC_DATA_MSG             *pstTraceDlData;
    VOS_UINT32                          ulDataLen;
    VOS_UINT8                          *pucData;


    if (PS_TRUE != g_ulDipcTraceFlag)
    {
        return;
    }

    while(VOS_NULL_PTR != pstData)
    {
        pstTraceDlData  = g_pstDipcTraceDlData;
        pstTraceDlData->ulSenderCpuId   = VOS_LOCAL_CPUID;
        pstTraceDlData->ulSenderPid     = PS_PID_APP_DIPC;
        pstTraceDlData->ulReceiverCpuId = VOS_LOCAL_CPUID;
        pstTraceDlData->ulReceiverPid   = PS_PID_APP_DIPC;
        pstTraceDlData->enMsgType       = ID_DIPC_TRACE_DL_DATA;
        pstTraceDlData->ucRabId         = ucRabId;

        ulDataLen   = IMM_ZcGetUsedLen(pstData);
        pucData     = IMM_ZcGetDataPtr(pstData);
        pstTraceDlData->ulDataLen       = ulDataLen;
        pstTraceDlData->ulLength        = (((sizeof(TRACE_DL_DIPC_DATA_MSG) - VOS_MSG_HEAD_LENGTH) - DIPC_DATA_MAX_DATA_LEN) + ulDataLen);
        mdrv_memcpy(pstTraceDlData->aucData, pucData, ulDataLen);
        DIAG_TraceReport(pstTraceDlData);

        pstData = pstData->next;
    }

    return;
}


/*****************************************************************************
 函 数 名  : DIPC_MappingInfoTrace
 功能描述  : DIPC模块Mapping信息勾包
 输入参数  : DIPC_TRACE_MSG_TYPE_ENUM_UINT32 enDipcTraceMsgType 引发映射信息勾包的事件
 输出参数  : 无
 返 回 值  : 无

 修改历史      :
  1.日    期   : 2012年2月16日
    作    者   : x59651
    修改内容   : 新生成函数

*****************************************************************************/
VOS_VOID DIPC_MappingInfoTrace(DIPC_TRACE_MSG_TYPE_ENUM_UINT32 enDipcTraceMsgType)
{
    DIPC_DEV_SUITE_INFO_MSG                 stDevTotalInfo;
    DIPC_DEV_INFO_STRU                     *pstDipcDevSingleInfo;
    DIPC_DEV_ID_ENUM_UINT32                 enDeviceId;
    DIPC_SERVICE_TYPE_ENUM_UINT32           enDipcServiceType;
    SERVICE_INFO_STRU                      *pstServInfo;

    stDevTotalInfo.ulSenderCpuId    = VOS_LOCAL_CPUID;
    stDevTotalInfo.ulSenderPid      = PS_PID_APP_DIPC;
    stDevTotalInfo.ulReceiverCpuId  = VOS_LOCAL_CPUID;
    stDevTotalInfo.ulReceiverPid    = PS_PID_APP_DIPC;
    stDevTotalInfo.ulLength         = sizeof(DIPC_DEV_SUITE_INFO_MSG) - VOS_MSG_HEAD_LENGTH;
    stDevTotalInfo.enMsgType        = enDipcTraceMsgType;

    for (enDeviceId = DIPC_DEV_ID1; enDeviceId < DIPC_DEV_BUTT; enDeviceId++)
    {
        pstDipcDevSingleInfo  = &(stDevTotalInfo.astDipcDevData[enDeviceId]);

        for (enDipcServiceType = DIPC_SERVICE_TYPE_IPV4;
            enDipcServiceType < DIPC_SERVICE_TYPE_BUTT;
            enDipcServiceType++)
        {
            pstDipcDevSingleInfo->enServiceType = enDipcServiceType;

            pstServInfo = g_astDevService[enDeviceId].apstServiceInfo[enDipcServiceType];
            if (VOS_NULL_PTR == pstServInfo)
            {
                pstDipcDevSingleInfo->ucRabId       = INVALID_RABID_VALUE;
            }
            else
            {
                pstDipcDevSingleInfo->ucRabId       = pstDipcDevSingleInfo->ucRabId;
            }
        }
    }

    DIAG_TraceReport(&stDevTotalInfo);

    return;
}


/*****************************************************************************
 函 数 名  : DIPC_StaticInfoInit
 功能描述  : A核 DIPC功能统计信息初始化
 输入参数  : VOS_VOID
 输出参数  : 无
 返 回 值  : 无

 修改历史      :
  1.日    期   : 2012年2月16日
    作    者   : x59651
    修改内容   : 新生成函数

*****************************************************************************/
VOS_VOID DIPC_StaticInfoInit( VOS_VOID )
{
    PS_MEM_SET(&g_stDipcStaticInfo, 0, sizeof(DIPC_STATIC_INFO_STRU));

    g_pstDipcTraceUlData = PS_ALLOC_STATIC_MEM(PS_PID_APP_DIPC, sizeof(TRACE_UL_DIPC_DATA_MSG));
    g_pstDipcTraceDlData = PS_ALLOC_STATIC_MEM(PS_PID_APP_DIPC, sizeof(TRACE_DL_DIPC_DATA_MSG));

    return;
}


/*****************************************************************************
 函 数 名  : DIPC_ShowStat
 功能描述  : A核 DIPC统计信息打印
 输入参数  : VOS_VOID
 输出参数  : 无
 返 回 值  : 无

 修改历史      :
  1.日    期   : 2012年2月16日
    作    者   : x59651
    修改内容   : 新生成函数

*****************************************************************************/
VOS_VOID DIPC_ShowStat( VOS_VOID )
{
    DIPC_DEV_ID_ENUM_UINT32         enDipcDevId;


    DIPC_MappingInfoTrace(ID_DIPC_SHOW_MAPPING_INFO);

    vos_printf("===========DIPC_ShowStat============");

    vos_printf("DIPC Rab Info.\r\n");
    vos_printf("DIPC Get Null Data From ADS, Num = %d.\r\n", g_stDipcStaticInfo.ulNullDlPacketNums);
    vos_printf("DIPC Dl Succ Get PacketNum = %d.\r\n", g_stDipcStaticInfo.ulSuccGetDlPacketNums);
    vos_printf("DIPC Dl FailMatch PacketNum = %d.\r\n", g_stDipcStaticInfo.ulFailMatchDlPacketNums);
    vos_printf("DIPC Dev Static Info.\r\n");

    for(enDipcDevId = 0; enDipcDevId < DIPC_DEV_NUM; enDipcDevId++)
    {
        vos_printf("DIPC Ul Get Fail Nums = %u\r\n",
            g_stDipcStaticInfo.astDipcDevStaticInfo[enDipcDevId].ulGetDataFailNums);
        vos_printf("DIPC Ul Succ Get PacketNum = %u\r\n",
            g_stDipcStaticInfo.astDipcDevStaticInfo[enDipcDevId].ulSuccGetUlPacketNums);
        vos_printf("DIPC Ul FailSend PacketNum = %u\r\n",
            g_stDipcStaticInfo.astDipcDevStaticInfo[enDipcDevId].ulFailSendUlPacketNums);
        vos_printf("DIPC Ul SuccSend PacketNum = %u\r\n",
            g_stDipcStaticInfo.astDipcDevStaticInfo[enDipcDevId].ulSuccSendUlPacketNums);
        vos_printf("DIPC Ul FailMatch PacketNum = %u\r\n",
            g_stDipcStaticInfo.astDipcDevStaticInfo[enDipcDevId].ulFailMatchUlPacketNums);
        vos_printf("DIPC Dl FailSend PacketNum = %u\r\n",
            g_stDipcStaticInfo.astDipcDevStaticInfo[enDipcDevId].ulFailSendDlPacketNums);
        vos_printf("DIPC Dl SuccSend PacketNum = %u\r\n",
            g_stDipcStaticInfo.astDipcDevStaticInfo[enDipcDevId].ulSuccSendDlPacketNums);
        vos_printf("\r\n");
    }

    return;
}


/*****************************************************************************
 函 数 名  : DIPC_ShowMappingInfo
 功能描述  : A核 DIPC显示映射信息
 输入参数  : VOS_VOID
 输出参数  : 无
 返 回 值  : 无

 修改历史      :
  1.日    期   : 2012年2月24日
    作    者   : x59651
    修改内容   : 新生成函数

*****************************************************************************/
VOS_VOID DIPC_ShowMappingInfo( VOS_VOID )
{
    DIPC_DEV_ID_ENUM_UINT32                 enDeviceId;
    DIPC_SERVICE_TYPE_ENUM_UINT32           enDipcServiceType;
    SERVICE_INFO_STRU                      *pstServInfo;

    for (enDeviceId = DIPC_DEV_ID1; enDeviceId < DIPC_DEV_BUTT; enDeviceId++)
    {
        vos_printf("enDeviceId = %d,begin\r\n", enDeviceId);

        for (enDipcServiceType = DIPC_SERVICE_TYPE_IPV4;
            enDipcServiceType < DIPC_SERVICE_TYPE_BUTT;
            enDipcServiceType++)
        {
            pstServInfo = g_astDevService[enDeviceId].apstServiceInfo[enDipcServiceType];
            if (VOS_NULL_PTR != pstServInfo)
            {
                vos_printf("Service Type %d, Rab Id %d\n",
                    enDipcServiceType, pstServInfo->ucRabId);
            }
        }
        vos_printf("enDeviceId = %d,end\r\n", enDeviceId);
    }

    return;
}


/*****************************************************************************
 函 数 名  : DIPC_SetTraceFlag
 功能描述  : DIPC Trace开关打开
 输入参数  : VOS_UINT32  ulFlag 输入参数修改标识
 输出参数  : 无
 返 回 值  : 无

 修改历史      :
  1.日    期   : 2012年2月24日
    作    者   : x59651
    修改内容   : 新生成函数

*****************************************************************************/
VOS_VOID DIPC_SetTraceFlag( VOS_UINT32  ulFlag )
{
    g_ulDipcTraceFlag   = ulFlag;

    return;
}


/*****************************************************************************
 函 数 名  : DIPC_SetLogFlag
 功能描述  : DIPC Log开关打开
 输入参数  : VOS_UINT32  ulFlag 输入参数修改标识
 输出参数  : 无
 返 回 值  : 无

 修改历史      :
  1.日    期   : 2012年2月24日
    作    者   : x59651
    修改内容   : 新生成函数

*****************************************************************************/
VOS_VOID DIPC_SetLogFlag( VOS_UINT32  ulFlag )
{
    g_ulDipcPrintFlag   = ulFlag;

    return;
}


#else   /* for feature */

/*****************************************************************************
  1 头文件包含
*****************************************************************************/
#include "PsTypeDef.h"
#include "mdrv.h"

/*****************************************************************************
  3 函数实现
*****************************************************************************/
/*****************************************************************************
 函 数 名  : DIPC_GetDevHandleByRabId
 功能描述  : 通过RabId获取设备句柄，此函数是给AT使用 (STUB !!!)
 输入参数  : VOS_UINT8 ucRabId  用来查询设备句柄的Rab Id

 输出参数  : 无
 返 回 值  : RabId对应的句柄,无效时为UDI_INVALID_HANDLE

 修改历史      :
  1.日    期   : 2012年2月15日
    作    者   : x59651
    修改内容   : 新生成函数

*****************************************************************************/
UDI_HANDLE DIPC_GetDevHandleByRabId(VOS_UINT8 ucRabId)
{
    return UDI_INVAL_DEV_ID;
}

/*****************************************************************************
 函 数 名  : DIPC_Pid_InitFunc
 功能描述  : DIPC PID初始化
 输入参数  : VOS_INIT_PHASE_DEFINE ip   初始化类型
 输出参数  : 无
 返 回 值  : VOS_UINT32

 修改历史      :
  1.日    期   : 2012年2月16日
    作    者   : x59651
    修改内容   : 新生成函数
*****************************************************************************/
VOS_UINT32 DIPC_Pid_InitFunc( enum VOS_INIT_PHASE_DEFINE ip )
{
    return PS_SUCC;
}

/*****************************************************************************
 函 数 名  : DIPC_MsgProc
 功能描述  : DIPC的消息处理函数
 输入参数  : MsgBlock *pMsgBlock    从AT发来的消息

 输出参数  : 无
 返 回 值  : VOS_UINT32

 修改历史      :
  1.日    期   : 2012年2月15日
    作    者   : x59651
    修改内容   : 新生成函数

*****************************************************************************/
VOS_UINT32 DIPC_AtMsgProc( const MsgBlock *pMsgBlock )
{
    return VOS_OK;
}


#endif    /* end for feature */

#ifdef __cplusplus
    #if __cplusplus
        }
    #endif
#endif


