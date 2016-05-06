

/******************************************************************************

                  版权所有 (C), 2001-2011, 华为技术有限公司

 ******************************************************************************
  文 件 名   : SCMSoftDecode.c
  版 本 号   : 初稿
  作    者   :
  生成日期   :
  最近修改   :
  功能描述   :
  函数列表   :
  修改历史   :
  1.日    期   : 2014年5月25日
    作    者   : L00256032
    修改内容   : V8R1 OM_Optimize项目新增

***************************************************************************** */

/*****************************************************************************
  1 头文件包含
**************************************************************************** */
#include "PamOamSpecTaskDef.h"
#include "SCMProc.h"
#include "SCMSoftDecode.h"
#include "ombufmngr.h"
#include "OmHdlcInterface.h"


#ifdef __cplusplus
#if __cplusplus
extern "C" {
#endif
#endif

/* lint -e767  */
#define    THIS_FILE_ID        PS_FILE_ID_CBT_SCM_SOFT_DECODE_C
/* lint +e767  */

/* ****************************************************************************
  2 全局变量定义
**************************************************************************** */
/* 自旋锁，用来作CBT数据接收的临界资源保护 */
VOS_SPINLOCK             g_stCbtScmDataRcvSpinLock;

/* HDLC控制结构 */
OM_HDLC_STRU             g_stCbtScmHdlcSoftDecodeEntity;

/* SCM数据接收数据缓冲区 */
VOS_CHAR                 g_aucCbtScmDataRcvBuffer[SCM_DATA_RCV_PKT_SIZE];

/* SCM数据接收任务控制结构 */
SCM_DATA_RCV_CTRL_STRU   g_stCbtScmDataRcvTaskCtrlInfo;

SCM_SOFTDECODE_INFO_STRU   g_stCbtScmSoftDecodeInfo;


/*****************************************************************************
  3 外部引用声明
*****************************************************************************/
extern SCM_SOFTDECODE_INFO_STRU   g_stScmSoftDecodeInfo;

extern VOS_UINT32 CBT_AcpuRcvData(VOS_UINT8 *pucData, VOS_UINT32 ulSize);

/*****************************************************************************
  4 函数实现
*****************************************************************************/

/*****************************************************************************
 函 数 名  : CBTSCM_SoftDecodeDataRcvProc
 功能描述  : SCM软解码数据接收函数
 输入参数  : pucBuffer:数据内容
             ulLen:数据长度
 输出参数  : 无
 返 回 值  : VOS_OK/VOS_ERR
 修改历史  :
   1.日    期  : 2014年5月21日
     作    者  : h59254
     修改内容  : Creat Function
*****************************************************************************/
VOS_UINT32 CBTSCM_SoftDecodeDataRcvProc(VOS_UINT8 *pucBuffer, VOS_UINT32 ulLen)
{
    VOS_INT32                           sRet;

    if (ulLen > (VOS_UINT32)OM_RingBufferFreeBytes(g_stCbtScmDataRcvTaskCtrlInfo.rngOmRbufId))
    {
        g_stCbtScmSoftDecodeInfo.stRbInfo.ulBufferNotEnough++;

        return VOS_ERR;
    }

    sRet = OM_RingBufferPut(g_stCbtScmDataRcvTaskCtrlInfo.rngOmRbufId,
                            (VOS_CHAR *)pucBuffer,
                            (VOS_INT)ulLen);



    if (ulLen == (VOS_UINT32)sRet)
    {
        if (VOS_OK == VOS_SmV(g_stCbtScmDataRcvTaskCtrlInfo.SmID))
        {
            g_stCbtScmSoftDecodeInfo.stPutInfo.ulDataLen += sRet;
            g_stCbtScmSoftDecodeInfo.stPutInfo.ulNum++;

            return VOS_OK;
        }
    }

    return VOS_ERR;

}

/*****************************************************************************
 函 数 名  : CBTSCM_SoftDecodeDataRcv
 功能描述  : GU CBT数据接收函数
 输入参数  : pucBuffer:数据内容
             ulLen:数据长度
 输出参数  : 无
 返 回 值  : 无
 修改历史  :
   1.日    期  : 2014年5月21日
     作    者  : h59254
     修改内容  : Creat Function
*****************************************************************************/
VOS_UINT32 CBTSCM_SoftDecodeDataRcv(VOS_UINT8 *pucBuffer, VOS_UINT32 ulLen)
{
    VOS_UINT32                          ulRstl;
    VOS_ULONG                           ulLockLevel;

    VOS_SpinLockIntLock(&g_stCbtScmDataRcvSpinLock, ulLockLevel);

    ulRstl = CBTSCM_SoftDecodeDataRcvProc(pucBuffer, ulLen);

    VOS_SpinUnlockIntUnlock(&g_stCbtScmDataRcvSpinLock, ulLockLevel);

    return ulRstl;
}

/*****************************************************************************
 函 数 名  : CBTSCM_SoftDecodeAcpuRcvData
 功能描述  : SCM软解码CBT数据接收函数
 输入参数  : pstHdlcCtrl: HDLC控制结构
             pucData:   需要发送的数据内容
             ulLen: 数据长度
 输出参数  : 无
 返 回 值  : VOS_ERR/VOS_OK
 修改历史  :
   1.日    期  : 2014年5月21日
     作    者  : h59254
     修改内容  : Creat Function
*****************************************************************************/
VOS_UINT32 CBTSCM_SoftDecodeAcpuRcvData(
    OM_HDLC_STRU                       *pstHdlcCtrl,
    VOS_UINT8                          *pucData,
    VOS_UINT32                          ulLen)
{
    VOS_UINT32                          i;
    VOS_UINT32                          ulResult;
    VOS_UINT8                           ucChar;

    ulResult = VOS_ERR;

    for( i = 0; i < ulLen; i++ )
    {
        ucChar = (VOS_UINT8)pucData[i];

        ulResult = Om_HdlcDecap(pstHdlcCtrl, ucChar);

        if ( HDLC_SUCC == ulResult )
        {
            g_stCbtScmSoftDecodeInfo.stHdlcDecapData.ulDataLen += pstHdlcCtrl->ulInfoLen;
            g_stCbtScmSoftDecodeInfo.stHdlcDecapData.ulNum++;

            /* GU CBT数据不需要DATATYPE字段，删除 */
            if (VOS_OK != CBT_AcpuRcvData(pstHdlcCtrl->pucDecapBuff + 1,
                            pstHdlcCtrl->ulInfoLen - 1))
            {
            }
        }
        else if (HDLC_NOT_HDLC_FRAME == ulResult)
        {
            /*不是完整分帧,继续HDLC解封装*/
        }
        else
        {
            g_stCbtScmSoftDecodeInfo.ulFrameDecapErr++;
        }
    }

    return VOS_OK;
}

/*****************************************************************************
 函 数 名  : CBTSCM_SoftDecodeHdlcInit
 功能描述  : CBT数据SCM软解码HDLC解封装初始化函数
 输入参数  : pstHdlc:指向HDLC控制结构的指针
 输出参数  : 无
 返 回 值  : VOS_OK/VOS_ERR
 修改历史  :
   1.日    期  : 2014年5月21日
     作    者  : h59254
     修改内容  : Creat Function
*****************************************************************************/
VOS_UINT32 CBTSCM_SoftDecodeHdlcInit(OM_HDLC_STRU *pstHdlc)
{
    /* 申请用于HDLC解封装的缓存 */
    pstHdlc->pucDecapBuff    = (VOS_UINT8 *)VOS_MemAlloc(ACPU_PID_CBT, STATIC_MEM_PT, SCM_DATA_RCV_PKT_SIZE);

    if (VOS_NULL_PTR == pstHdlc->pucDecapBuff)
    {
        /*lint -e534*/
        vos_printf("CBTSCM_SoftDecodeHdlcInit: Alloc Decapsulate buffer fail!");
        /*lint +e534*/

        return VOS_ERR;
    }

    /* HDLC解封装缓存长度赋值 */
    pstHdlc->ulDecapBuffSize = SCM_DATA_RCV_PKT_SIZE;

    /* 初始化HDLC解封装控制上下文 */
    Om_HdlcInit(pstHdlc);

    return VOS_OK;
}

/*****************************************************************************
 函 数 名  : CBTSCM_SoftDecodeReqRcvSelfTask
 功能描述  : SCM软解码CBT数据接收任务
 输入参数  : ulPara1:参数1
             ulPara2:参数2
             ulPara3:参数3
             ulPara4:参数4
 输出参数  : 无
 返 回 值  : 无
 修改历史  :
   1.日    期  : 2014年5月21日
     作    者  : h59254
     修改内容  : Creat Function
*****************************************************************************/
VOS_VOID CBTSCM_SoftDecodeReqRcvSelfTask(
    VOS_UINT32                          ulPara1,
    VOS_UINT32                          ulPara2,
    VOS_UINT32                          ulPara3,
    VOS_UINT32                          ulPara4)
{
    VOS_INT32                           sRet;
    VOS_INT32                           lLen;
    VOS_INT32                           lRemainlen;
    VOS_INT32                           lReadLen;
    VOS_UINT32                          ulPktNum;
    VOS_UINT32                          i;
    VOS_ULONG                           ulLockLevel;

    ulPara1 = ulPara1;
    ulPara2 = ulPara2;
    ulPara3 = ulPara3;
    ulPara4 = ulPara4;

    for (;;)
    {
        if (VOS_OK != VOS_SmP(g_stCbtScmDataRcvTaskCtrlInfo.SmID, 0))
        {
            continue;
        }

        lLen = OM_RingBufferNBytes(g_stCbtScmDataRcvTaskCtrlInfo.rngOmRbufId);

        if (lLen <= 0)
        {
            continue;
        }

        ulPktNum = (VOS_UINT32)((lLen + SCM_DATA_RCV_PKT_SIZE - 1) / SCM_DATA_RCV_PKT_SIZE);

        lRemainlen = lLen;

        for (i = 0; i < ulPktNum; i++)
        {
            if (SCM_DATA_RCV_PKT_SIZE < lRemainlen)
            {
                lReadLen = SCM_DATA_RCV_PKT_SIZE;

                sRet = OM_RingBufferGet(g_stCbtScmDataRcvTaskCtrlInfo.rngOmRbufId,
                                        g_stCbtScmDataRcvTaskCtrlInfo.pucBuffer,
                                        SCM_DATA_RCV_PKT_SIZE);
            }
            else
            {
                lReadLen = lRemainlen;

                sRet = OM_RingBufferGet(g_stCbtScmDataRcvTaskCtrlInfo.rngOmRbufId,
                                        g_stCbtScmDataRcvTaskCtrlInfo.pucBuffer,
                                        lRemainlen);
            }

            if (sRet != lReadLen)
            {
                VOS_SpinLockIntLock(&g_stCbtScmDataRcvSpinLock, ulLockLevel);

                OM_RingBufferFlush(g_stCbtScmDataRcvTaskCtrlInfo.rngOmRbufId);

                VOS_SpinUnlockIntUnlock(&g_stCbtScmDataRcvSpinLock, ulLockLevel);

                g_stCbtScmSoftDecodeInfo.stRbInfo.ulRingBufferFlush++;

                continue;
            }

            lRemainlen -= lReadLen;

            /* 调用HDLC解封装函数 */
            if (VOS_OK != CBTSCM_SoftDecodeAcpuRcvData(&g_stCbtScmHdlcSoftDecodeEntity,
                                                        (VOS_UINT8 *)g_stCbtScmDataRcvTaskCtrlInfo.pucBuffer,
                                                        (VOS_UINT32)lReadLen))
            {
                /*lint -e534*/
                vos_printf("CBTSCM_SoftDecodeReqRcvSelfTask: CBTSCM_SoftDecodeAcpuRcvData Fail");
                /*lint +e534*/

                g_stCbtScmSoftDecodeInfo.stGetInfo.ulDataLen += lReadLen;
            }

        }

#if (defined(DMT))
        return;
#endif
    }
}

/*****************************************************************************
 函 数 名  : CBTSCM_SoftDecodeReqRcvTaskInit
 功能描述  : SCM软解码CBT数据接收函数初始化
 输入参数  : 无
 输出参数  : 无
 返 回 值  : VOS_OK/VOS_ERR
 修改历史  :
   1.日    期  : 2014年5月21日
     作    者  : h59254
     修改内容  : Creat Function
*****************************************************************************/
VOS_UINT32 CBTSCM_SoftDecodeReqRcvTaskInit(VOS_VOID)
{
    VOS_UINT32                              ulRslt;

    /* 注册CBT数据接收自处理任务 */
    ulRslt = VOS_RegisterSelfTaskPrio(ACPU_FID_CBT,
                                      (VOS_TASK_ENTRY_TYPE)CBTSCM_SoftDecodeReqRcvSelfTask,
                                      SCM_DATA_RCV_SELFTASK_PRIO,
                                      SCM_CBT_REQ_TASK_STACK_SIZE);
    if ( VOS_NULL_BYTE == ulRslt )
    {
        return VOS_ERR;
    }

    /*lint -e534*/
    VOS_MemSet(&g_stCbtScmSoftDecodeInfo, 0, sizeof(g_stCbtScmSoftDecodeInfo));
    /*lint +e534*/

    if (VOS_OK != VOS_SmCCreate("CBT", 0, VOS_SEMA4_FIFO, &(g_stCbtScmDataRcvTaskCtrlInfo.SmID)))
    {
        /*lint -e534*/
        vos_printf("CBTSCM_SoftDecodeReqRcvTaskInit: Error, CBT semCCreate Fail");
        /*lint +e534*/

        g_stCbtScmSoftDecodeInfo.stRbInfo.ulSemCreatErr++;

        return VOS_ERR;
    }

    if (VOS_OK != CBTSCM_SoftDecodeHdlcInit(&g_stCbtScmHdlcSoftDecodeEntity))
    {
        /*lint -e534*/
        vos_printf("CBTSCM_SoftDecodeReqRcvTaskInit: Error, HDLC Init Fail");
        /*lint +e534*/

        return VOS_ERR;
    }

    g_stCbtScmDataRcvTaskCtrlInfo.rngOmRbufId = OM_RingBufferCreate(SCM_DATA_RCV_BUFFER_SIZE);

    if (VOS_NULL_PTR == g_stCbtScmDataRcvTaskCtrlInfo.rngOmRbufId)
    {
        /*lint -e534*/
        vos_printf("CBTSCM_SoftDecodeReqRcvTaskInit: Error, Creat CBT ringBuffer Fail");
        /*lint +e534*/

        g_stCbtScmSoftDecodeInfo.stRbInfo.ulRingBufferCreatErr++;

        /*lint -e534*/
        VOS_MemFree(ACPU_PID_CBT, g_stCbtScmHdlcSoftDecodeEntity.pucDecapBuff);
        /*lint +e534*/

        return VOS_ERR;
    }

    g_stCbtScmDataRcvTaskCtrlInfo.pucBuffer = &g_aucCbtScmDataRcvBuffer[0];

    VOS_SpinLockInit(&g_stCbtScmDataRcvSpinLock);

    return VOS_OK;
}

VOS_VOID CBTSCM_SoftDecodeInfoShow(VOS_VOID)
{
    /*lint -e534*/
    vos_printf("\r\nSCM_SoftDecodeInfoShow:\r\n");

    vos_printf("\r\nSem Creat Error %d:\r\n",                   g_stCbtScmSoftDecodeInfo.stRbInfo.ulSemCreatErr);
    vos_printf("\r\nSem Give Error %d:\r\n",                    g_stCbtScmSoftDecodeInfo.stRbInfo.ulSemGiveErr);
    vos_printf("\r\nRing Buffer Creat Error %d:\r\n",           g_stCbtScmSoftDecodeInfo.stRbInfo.ulRingBufferCreatErr);
    vos_printf("\r\nTask Id Error %d:\r\n",                     g_stCbtScmSoftDecodeInfo.stRbInfo.ulTaskIdErr);
    vos_printf("\r\nRing Buffer not Enough %d:\r\n",            g_stCbtScmSoftDecodeInfo.stRbInfo.ulBufferNotEnough);
    vos_printf("\r\nRing Buffer Flush %d:\r\n",                 g_stCbtScmSoftDecodeInfo.stRbInfo.ulRingBufferFlush);
    vos_printf("\r\nRing Buffer Put Error %d:\r\n",             g_stCbtScmSoftDecodeInfo.stRbInfo.ulRingBufferPutErr);

    vos_printf("\r\nRing Buffer Put Success Times %d:\r\n",     g_stCbtScmSoftDecodeInfo.stPutInfo.ulNum);
    vos_printf("\r\nRing Buffer Put Success Bytes %d:\r\n",     g_stCbtScmSoftDecodeInfo.stPutInfo.ulDataLen);

    vos_printf("\r\nRing Buffer Get Success Times %d:\r\n",     g_stCbtScmSoftDecodeInfo.stGetInfo.ulNum);
    vos_printf("\r\nRing Buffer Get Success Bytes %d:\r\n",     g_stCbtScmSoftDecodeInfo.stGetInfo.ulDataLen);

    vos_printf("\r\nHDLC Decode Success Times %d:\r\n",         g_stCbtScmSoftDecodeInfo.stHdlcDecapData.ulNum);
    vos_printf("\r\nHDLC Decode Success Bytes %d:\r\n",         g_stCbtScmSoftDecodeInfo.stHdlcDecapData.ulDataLen);

    vos_printf("\r\nHDLC Decode Error Times %d:\r\n",           g_stCbtScmSoftDecodeInfo.ulFrameDecapErr);

    vos_printf("\r\nHDLC Init Error Times %d:\r\n",             g_stCbtScmSoftDecodeInfo.ulHdlcInitErr);

    vos_printf("\r\nHDLC Decode Data Type Error Times %d:\r\n", g_stCbtScmSoftDecodeInfo.ulDataTypeErr);
    /*lint +e534*/
}

#ifdef __cplusplus
#if __cplusplus
    }
#endif
#endif




