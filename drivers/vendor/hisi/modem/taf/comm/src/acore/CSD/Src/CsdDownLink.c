

/*****************************************************************************
  1 头文件包含
*****************************************************************************/
#include "CsdDownLink.h"
#include "CsdDebug.h"


#ifdef __cplusplus
#if __cplusplus
extern "C" {
#endif
#endif

/*****************************************************************************
    协议栈打印打点方式下的.C文件宏定义
*****************************************************************************/
/*lint -e767 */
#define    THIS_FILE_ID                 PS_FILE_ID_CSD_DOWN_LINK_C
/*lint -e767 */

#if( FEATURE_ON == FEATURE_CSD )
/*****************************************************************************
  2 全局变量定义
*****************************************************************************/
extern VOS_UINT32 AT_SendCsdZcDataToModem(
    VOS_UINT8                           ucIndex,
    IMM_ZC_STRU                        *pstDataBuf
);


/*****************************************************************************
  3 函数实现
*****************************************************************************/


VOS_VOID CSD_DL_ProcIsr(VOS_VOID)
{
    VOS_SEM                             hDLDataSem = VOS_NULL_PTR;

    hDLDataSem  = CSD_GetDownLinkDataSem();

#if 0
    /*DICC关闭中断*/
    DICC_DisableIsr(ACPU_PID_CSD, DICC_SERVICE_TYPE_CSD_DATA, DICC_CPU_ID_ACPU);
#endif
    /*释放下行取数据信号量*/
    VOS_SmV(hDLDataSem);
}


VOS_VOID CSD_DL_SendData(VOS_VOID)
{
    IMM_ZC_STRU                        *pstCsdDLMem;
    CST_CSD_DATA_IND_STRU               stDLData;
    VOS_UINT32                          ulDICCNodeCnt;
    VOS_UINT32                          ulRslt;
    VOS_CHAR                           *ImmZcData;


    for ( ; ; )
    {
        /*获取DICC通道发送来数据的个数*/
        ulDICCNodeCnt = DICC_GetChannelCurrDataCnt(ACPU_PID_CSD,
                                                   DICC_CHAN_ID_DL_CSD_DATA_CHAN,
                                                   DICC_CPU_ID_ACPU);

        if ( DICC_INVALID_VALUE == ulDICCNodeCnt )
        {
            CSD_ERROR_LOG1(ACPU_PID_CSD,
                           "CSD_DL_SendData :: DICC_GetChannelCurrDataCnt is Wrong",
                           ulDICCNodeCnt);
            break;
        }

        if (0 != ulDICCNodeCnt )
        {
           /*从DICC通道中移出数据*/
            ulRslt      = DICC_RemoveChannelData(ACPU_PID_CSD,
                                                 DICC_CHAN_ID_DL_CSD_DATA_CHAN,
                                                 (VOS_UINT8 *)(&stDLData),
                                                 DICC_CPU_ID_ACPU);

            if (DICC_OK != ulRslt)
            {
                CSD_ERROR_LOG1(ACPU_PID_CSD,
                              "CSD_DL_SendData:: enMsgId Illage",
                              ulRslt);
                break;
            }

            if (VOS_NULL_PTR == stDLData.pGarbage)
            {
                CSD_ERROR_LOG(ACPU_PID_CSD,
                              "CSD_DL_SendData:: stDLData.pGarbage Is Null");
                break;
            }

            CSD_DBG_DL_RECV_PKT_NUM(1);

            /*申请sk_buffer内存*/
            pstCsdDLMem = IMM_ZcStaticAlloc(stDLData.usLen);

            if (VOS_NULL_PTR == pstCsdDLMem)
            {
                CSD_ERROR_LOG1(ACPU_PID_CSD,
                              "CSD_DL_SendData:: pstCsdDLMem Is Null IMM_ZcStaticAlloc Fail",
                              pstCsdDLMem);

                /*通知cCpu释放TTFmem*/
                IMM_RemoteFreeTtfMem(stDLData.pGarbage);

                /*此处用continue可能导致死循环*/
                break;

            }

            /*此步骤不能少用来偏移数据尾指针*/
            ImmZcData = (VOS_CHAR *)IMM_ZcPut(pstCsdDLMem, stDLData.usLen);

            PS_MEM_CPY(ImmZcData, (VOS_UINT8 *)TTF_PHY_TO_VIRT((VOS_VOID *)(stDLData.pucData)), stDLData.usLen);

            /*发送数据到驱动,第一个参数为pppid目前不使用，由于失败AT会释放内存，
            所以此处不需要另行释放a核内存*/
            ulRslt      = AT_SendCsdZcDataToModem(CSD_UL_GetAtClientIndex(), pstCsdDLMem);

            if (VOS_OK != ulRslt)
            {
                CSD_DBG_DL_SEND_FAIL_NUM(1);

                CSD_ERROR_LOG(ACPU_PID_CSD,
                              "CSD_DL_SendData:: AT_SendZcDataToModem  Fail");

                /*通知cCpu释放TTFmem*/
                IMM_RemoteFreeTtfMem(stDLData.pGarbage);

                /*此处用continue可能导致死循环*/
                break;
            }
            CSD_DBG_DL_SEND_PKT_NUM(1);

            /*通知cCpu释放TTFmem*/
            IMM_RemoteFreeTtfMem(stDLData.pGarbage);

        }
        else
        {

            /*通道内数据发送完*/
            CSD_NORMAL_LOG1(ACPU_PID_CSD,
                            "CSD_DL_SendData Queue is Null",
                            ulDICCNodeCnt);

            break;
        }

        CSD_NORMAL_LOG1(ACPU_PID_CSD,
                        "CSD_DL_SendData Done",
                        ulDICCNodeCnt);

    }

}

VOS_VOID CSD_DL_ClearData(VOS_VOID)
{
    VOS_UINT32                          ulDICCNodeCnt;
    VOS_UINT32                          ulRslt;
    CST_CSD_DATA_IND_STRU               stDLData;


    /*获取DICC通道发送来数据的个数*/
    ulDICCNodeCnt   = DICC_GetChannelCurrDataCnt(ACPU_PID_CSD,
                                                 DICC_CHAN_ID_DL_CSD_DATA_CHAN,
                                                 DICC_CPU_ID_ACPU);
    if ( DICC_INVALID_VALUE == ulDICCNodeCnt )
    {
        CSD_ERROR_LOG1(ACPU_PID_CSD,
                       "CSD_DL_ClearData :: DICC_GetChannelCurrDataCnt is Wrong",
                       ulDICCNodeCnt);
        return;
    }

    while ((0 != ulDICCNodeCnt))
    {

        /*从DICC通道中移出数据*/
        ulRslt      = DICC_RemoveChannelData(ACPU_PID_CSD,
                                             DICC_CHAN_ID_DL_CSD_DATA_CHAN,
                                             (VOS_UINT8 *)(&stDLData),
                                             DICC_CPU_ID_ACPU);

        if (DICC_OK != ulRslt)
        {
            CSD_ERROR_LOG1(ACPU_PID_CSD,
                          "CSD_DL_ClearData:: DICC_RemoveChannelData Fail",
                          ulRslt);
            break;
        }

        ulDICCNodeCnt-- ;

        /*通知cCpu释放TTFmem*/
        IMM_RemoteFreeTtfMem(stDLData.pGarbage);
    }

    CSD_NORMAL_LOG(ACPU_PID_CSD,"CSD_DL_ClearData Done");
}

VOS_VOID CSD_DL_ProcDataTask(VOS_VOID)
{
    VOS_SEM                             hDownLinkSem;

    hDownLinkSem = CSD_GetDownLinkDataSem();

    for ( ; ; )
    {

        /* 获取下行取数据信号量 */
        if (VOS_OK != VOS_SmP(hDownLinkSem, 0 ))
        {
            CSD_NORMAL_LOG(ACPU_PID_CSD,
                "CSD_DL_ProcDataTask:: VOS_SmP pulDownLinkSem then continue !");


#ifdef __PC_UT__
            break;
#else
            continue;
#endif
        }

        /*获取当前是否挂断电话*/
        if (AT_CSD_CALL_STATE_ON != CSD_GetCallState())
        {
            /*释放数据*/
            CSD_DL_ClearData();
#if 0
            /*使能中断*/
            DICC_EnableIsr(ACPU_PID_CSD,
                           DICC_SERVICE_TYPE_CSD_DATA,
                           DICC_CPU_ID_ACPU);
#endif

            CSD_ERROR_LOG(ACPU_PID_CSD,
                          "CSD_DL_ProcDataTask:: AT_CSD_CALL_STATE_OFF Receive ISR");


#ifdef __PC_UT__
            break;
#else
            continue;
#endif

        }

        CSD_DL_SendData();
#if 0
        /* 使能中断 */
        DICC_EnableIsr(ACPU_PID_CSD,
                       DICC_SERVICE_TYPE_CSD_DATA,
                       DICC_CPU_ID_ACPU);
#endif
#ifdef __PC_UT__
            break;
#endif
    }
}

#endif /*FEATURE_CSD*/






#ifdef __cplusplus
    #if __cplusplus
        }
    #endif
#endif
