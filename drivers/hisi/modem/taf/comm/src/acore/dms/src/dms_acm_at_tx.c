

/*****************************************************************************
  1 头文件包含
*****************************************************************************/

#include "msp_errno.h"
#include <dms.h>
#include "dms_core.h"
#include "vos.h"


#ifdef __cplusplus
    #if __cplusplus
    extern "C" {
    #endif
#endif


/*****************************************************************************
    协议栈打印打点方式下的.C文件宏定义
*****************************************************************************/

/*lint -e767 -e960*/
#define THIS_FILE_ID                    PS_FILE_ID_DMS_ACM_AT_TX_C
/*lint +e767 +e960*/


/*****************************************************************************
  2 全局变量定义
*****************************************************************************/

DMS_STATIC_BUF_STRU                     stDmsStaticBufInfo ;

#if (VOS_WIN32== VOS_OS_VER)
VOS_UINT8                               aucStaticBuf[DMS_LOG_STATIC_ONE_BUF_SIZE*DMS_LOG_STATIC_BUF_NUM + 32] = {0};
#endif
VOS_UINT8                              *g_aucStaticBuf = NULL;


/*****************************************************************************
  3 函数实现
*****************************************************************************/

/*****************************************************************************
 函 数 名  : DMS_WriteData
 功能描述  : AT写数据总入口
 输入参数  : ucPortNo: 通道ID
             pData: 发送数据指针
             uslength:发送长度
 输出参数  :
 返 回 值  : ERR_MSP_FAILURE/ERR_MSP_SUCCESS
 调用函数  :
 被调函数  :
 修改历史  :
   1.日    期  : 2012年8月27日
     作    者  : heliping
     修改内容  : Creat Function

   2.日    期   : 2015年6月25日
     作    者   : l00198894
     修改内容   : TSTS
*****************************************************************************/
VOS_INT32 DMS_WriteData(DMS_PHY_BEAR_ENUM enPhyBear, VOS_UINT8 *pucData, VOS_UINT16 usLen)
{
    VOS_UINT8                          *pucSenBuf = NULL;
    VOS_INT32                           lRet      = VOS_ERROR;

    if ((NULL == pucData) || (0 == usLen))
    {
        return VOS_ERROR;
    }

    DMS_LOG_INFO("DMS_WriteData: PortNo = %d, len = %d, buf = %s\n", enPhyBear, usLen, pucData);

    if ( (DMS_PHY_BEAR_USB_PCUI == enPhyBear)
      || (DMS_PHY_BEAR_USB_CTRL == enPhyBear)
      || (DMS_PHY_BEAR_USB_PCUI2 == enPhyBear) )
    {
        pucSenBuf = Dms_GetStaticBuf(usLen);

        if (NULL == pucSenBuf)
        {
            return VOS_ERROR;
        }

        VOS_MemCpy(pucSenBuf, pucData, usLen);

        lRet = (VOS_INT32)DMS_VcomWriteAsync(enPhyBear, pucSenBuf, usLen);

        if (ERR_MSP_SUCCESS != lRet)
        {
            Dms_FreeStaticBuf(pucSenBuf);
        }

    }
    else if (DMS_PHY_BEAR_USB_NCM == enPhyBear)
    {
        pucSenBuf = Dms_GetStaticBuf(usLen);

        if (NULL == pucSenBuf)
        {
            return VOS_ERROR;
        }

        VOS_MemCpy(pucSenBuf, pucData, usLen);

        lRet = (VOS_INT32)DMS_NcmSendData(pucSenBuf, usLen);

        if (ERR_MSP_SUCCESS != lRet)
        {
            Dms_FreeStaticBuf(pucSenBuf);
        }
    }
    else
    {
        lRet = VOS_ERROR;
    }

    return lRet;
}

/*****************************************************************************
 函 数 名  : Dms_StaticBufInit
 功能描述  : AT发送静态buf初始化
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
VOS_VOID Dms_StaticBufInit(VOS_VOID)
{
    VOS_UINT32 i = 0;
    VOS_UINT8 * pTemp = NULL;

#if (VOS_LINUX== VOS_OS_VER)
    VOS_UINT32 ulBufSize;

    ulBufSize = (DMS_LOG_STATIC_ONE_BUF_SIZE*DMS_LOG_STATIC_BUF_NUM + 32);
    g_aucStaticBuf = kmalloc(ulBufSize, GFP_KERNEL|__GFP_DMA);

    if(g_aucStaticBuf == VOS_NULL)
    {
        return ;
    }
#endif

#if (VOS_WIN32== VOS_OS_VER)
    g_aucStaticBuf = aucStaticBuf;
#endif

    /*取32字节对齐的地址*/
    pTemp = g_aucStaticBuf + (32 - ((VOS_ULONG )g_aucStaticBuf%32));

    stDmsStaticBufInfo.enBufType      = DMS_BUF_TYP_DYMIC;

    /* 初始化缓冲信息*/
    for (i = 0; i < DMS_LOG_STATIC_BUF_NUM; i++)
    {
        stDmsStaticBufInfo.stBufSta[i].pcuBuf = (VOS_UINT8 *)((VOS_ULONG)i * DMS_LOG_STATIC_ONE_BUF_SIZE + pTemp);
        stDmsStaticBufInfo.stBufSta[i].enBusy = STATIC_BUF_STA_IDLE;
    }

    return ;

}
/*****************************************************************************
函 数 名  : Dms_GetStaticBuf
功能描述  : AT发送获取静态buf
输入参数  : ulLen :需要buf的长度

输出参数  :
返 回 值  : VOS_NULL/addr
调用函数  :
被调函数  :
修改历史  :
 1.日    期  : 2012年8月27日
   作    者  : heliping
   修改内容  : Creat Function
*****************************************************************************/
VOS_UINT8* Dms_GetStaticBuf(VOS_UINT32 ulLen)
{
    VOS_UINT32 i = 0;
    VOS_UINT32 *buf = NULL;

    /*数据长度超过静态buf最大size，动态申请buf*/
    if(ulLen >DMS_LOG_STATIC_ONE_BUF_SIZE )
    {

#if (VOS_LINUX== VOS_OS_VER)
        buf = kmalloc(ulLen, GFP_KERNEL|__GFP_DMA);
#else
        buf = VOS_NULL;
#endif
        return (VOS_UINT8* )buf;
    }

    for (i = 0; i < DMS_LOG_STATIC_BUF_NUM; i++)
    {
        if (stDmsStaticBufInfo.stBufSta[i].enBusy == STATIC_BUF_STA_IDLE)
        {
            stDmsStaticBufInfo.stBufSta[i].enBusy = STATIC_BUF_STA_BUSY;

            return  stDmsStaticBufInfo.stBufSta[i].pcuBuf;
        }
    }

    /*极限场景下 如果静态buf用完，申请动态内存使用*/
#if (VOS_LINUX== VOS_OS_VER)
    buf = kmalloc(ulLen, GFP_KERNEL|__GFP_DMA);
#else
    buf = VOS_NULL;
#endif

    return (VOS_UINT8* )buf;

}

/*****************************************************************************
函 数 名  : Dms_IsStaticBuf
功能描述  : 判断是否是静态地址
输入参数  : buf: buf地址

输出参数  :
返 回 值  : TRUE/FALSE
调用函数  :
被调函数  :
修改历史  :
1.日    期  : 2012年8月27日
  作    者  : heliping
  修改内容  : Creat Function
*****************************************************************************/

 VOS_BOOL Dms_IsStaticBuf(VOS_UINT8 *buf)
 {

    if(( buf >= g_aucStaticBuf )
        &&(buf < g_aucStaticBuf +DMS_LOG_STATIC_ONE_BUF_SIZE * DMS_LOG_STATIC_BUF_NUM  +32))
    {
        return VOS_TRUE;
    }
    else
    {
        return VOS_FALSE;
    }

}

/*****************************************************************************
 函 数 名  : Dms_FreeStaticBuf
 功能描述  : 释放静态空间
 输入参数  : buf: 被释放的buf地址

 输出参数  :
 返 回 值  :
 调用函数  :
 被调函数  :
 修改历史  :
   1.日    期  : 2012年8月27日
     作    者  : heliping
     修改内容  : Creat Function
*****************************************************************************/
VOS_VOID Dms_FreeStaticBuf( VOS_UINT8 * buf)
{
    VOS_UINT32 i = 0;

    if (NULL == buf)
    {
        return ;
    }

    /*静态buf释放*/
    for (i = 0; i < DMS_LOG_STATIC_BUF_NUM; i++)
    {
        if (stDmsStaticBufInfo.stBufSta[i].pcuBuf == buf)
        {
            stDmsStaticBufInfo.stBufSta[i].enBusy = STATIC_BUF_STA_IDLE;
            return ;
        }
    }

    /*动态buf释放*/
    if(i == DMS_LOG_STATIC_BUF_NUM)
    {
#if (VOS_LINUX== VOS_OS_VER)
        kfree(buf );
#endif
    }


    return ;
}
/*****************************************************************************
 函 数 名  : DMS_VcomWriteAsync
 功能描述  : USB异步写接口
 输入参数  : VcomId: 通道ID
             pucDataBuf: 发送指针
             slLen:发送长度
 输出参数  :
 返 回 值  : ERR_MSP_FAILURE/ERR_MSP_SUCCESS
 调用函数  :
 被调函数  :
 修改历史  :
   1.日    期  : 2012年8月27日
     作    者  : heliping
     修改内容  : Creat Function
*****************************************************************************/
VOS_UINT32 DMS_VcomWriteAsync(
    DMS_PHY_BEAR_ENUM                   enPhyBear,
    VOS_UINT8                          *pucDataBuf,
    VOS_UINT32                          ulLen
)
{
    DMS_PHY_BEAR_PROPERTY_STRU         *pstPhyBearProp = NULL;
    ACM_WR_ASYNC_INFO                   stAcmInfo = {0};
    UDI_HANDLE                          lHandle = UDI_INVALID_HANDLE;
    VOS_INT32                           lRet = ERR_MSP_SUCCESS;
#ifdef CONFIG_ARM64
    struct device                       dev;
    VOS_UINT64                          dma_mask = 0xffffffffULL;

    VOS_MemSet(&dev, 0, (VOS_SIZE_T)sizeof(dev));

    dev.dma_mask = &(dma_mask);
#endif

    stAcmInfo.pVirAddr = (VOS_CHAR *)pucDataBuf;

#ifdef CONFIG_ARM64
    stAcmInfo.pPhyAddr = (VOS_CHAR *)DMS_CACHE_FLUSH_WITH_DEV(&dev, (VOS_CHAR *)pucDataBuf, ulLen);
#else
    stAcmInfo.pPhyAddr = (VOS_CHAR *)DMS_CACHE_FLUSH((VOS_CHAR *)pucDataBuf, ulLen);
#endif

    stAcmInfo.u32Size  = ulLen;

    pstPhyBearProp = DMS_GetPhyBearProperty(enPhyBear);

    lHandle = pstPhyBearProp->lPortHandle;
    if (UDI_INVALID_HANDLE == lHandle)
    {
        DMS_LOG_INFO("DMS_VcomWriteAsync[%d]: INVALID HANDLE.\n", enPhyBear);
        return ERR_MSP_FAILURE;
    }

    if (ACM_EVT_DEV_SUSPEND == pstPhyBearProp->ucChanStat)
    {
        DMS_LOG_INFO("DMS_VcomWriteAsync[%d]: DEV SUSPEND.\n", enPhyBear);
        return ERR_MSP_FAILURE;
    }

    DMS_DBG_SDM_FUN((DMS_SDM_MSG_ID_ENUM)(DMS_SDM_VCOM_WRT_BEGIN + (VOS_UINT32)enPhyBear),\
                    ulLen, 0, 0);

    lRet = mdrv_udi_ioctl(lHandle, ACM_IOCTL_WRITE_ASYNC, &stAcmInfo);
    if (ERR_MSP_SUCCESS == lRet)
    {
        DMS_DBG_SDM_FUN((DMS_SDM_MSG_ID_ENUM)(DMS_SDM_VCOM_WRT_SUSS_BEGIN + (VOS_UINT32)enPhyBear),\
                        ulLen, 0, 0);
    }

    return (VOS_UINT32)lRet;
}


#ifdef __cplusplus
    #if __cplusplus
        }
    #endif
#endif

