/******************************************************************************

        @(#)Copyright(C)2008,Hisilicon Co. LTD.

 ******************************************************************************
    File name   : NasLmmPubMIntraMsg.c
    Description : MM模块内部消息操作
    History     :
      1.  Name+ID  yyyy-mm-dd  Draft Enact
      2.zhengjunyan 00148421   2011-05-28 文件名由 NasMmPubMIntraMsg.c修改为
                                           NasLmmPubMIntraMsg.c
******************************************************************************/

/*****************************************************************************
  1 Include HeadFile
*****************************************************************************/
#include    "NasLmmPubMInclude.h"
#include    "NasMmlMsgProc.h"

/*lint -e767*/
#define    THIS_FILE_ID            PS_FILE_ID_NASMMPUBMINTRAMSG_C
#define    THIS_NAS_FILE_ID        NAS_FILE_ID_NASMMPUBMINTRAMSG_C
/*lint +e767*/

/*****************************************************************************
  1.1 Cplusplus Announce
*****************************************************************************/
#ifdef __cplusplus
#if __cplusplus
extern "C" {
#endif
#endif
/*****************************************************************************
  2 Declare the Global Variable
*****************************************************************************/



/*****************************************************************************
  3 Function
*****************************************************************************/



/*****************************************************************************
 Function Name  : NAS_LMM_GetSendIntraMsgBuffAddr
 Discription    : 获取发送内部消息的地址
                  发送内部消息的过程为:
                    1.申请内部消息地址,
                    2.填充内部消息内容
                    3.发送内部消息
 Input          : 消息长度:该长度含义同DOPRA申请消息时的长度，即不包括
                    消息头 VOS_MSG_HEADER的长度
 Output         : None
 Return         : 消息地址，NasMmIntraMsgBlock 指针类型
 History:
*****************************************************************************/
/*lint -e960*/
/*lint -e961*/
NasMmIntraMsgBlock * NAS_LMM_GetSendIntraMsgBuffAddr( VOS_UINT32 ulBuffSize )
{
    VOS_UINT16                          usQueHeaderPos;
    VOS_UINT16                          usQueTailPos;
    NAS_LMM_INTRA_MSG_QUEUE_STRU        *pstMsgQue;
    VOS_UINT8                          *pucMsgBuff;

    NAS_LMM_INTRA_MSG_STRU  *pstIntraMsgHeader = NAS_LMM_NULL_PTR;

    if ( (0 == ulBuffSize) || (NAS_EMM_INTRA_MSG_MAX_SIZE < ulBuffSize ) )
    {
        /* 打印错误信息 */
        NAS_LMM_PUBM_LOG1_ERR("NAS_LMM_GetSendIntraMsgBuffAddr, Size error, ", ulBuffSize);
        TLPS_PRINT2LAYER_ERROR1(NAS_LMM_GetSendIntraMsgBuffAddr_ENUM
,LNAS_ERROR,ulBuffSize);

        return NAS_LMM_NULL_PTR;
    }

    /* 获取队列地址 */
    pstMsgQue      = NAS_LMM_GetMmIntrMsgQueueAddr();


    /* 队头队尾位置 */
    usQueHeaderPos = pstMsgQue->usHeader % NAS_LMM_INTRA_MSG_MAX_NUM;
    usQueTailPos   = pstMsgQue->usTail % NAS_LMM_INTRA_MSG_MAX_NUM;

    /* 验证是否队列满,连续两次+1, 预留一个队列空间不能分配, 有可能该消息正在处理 */
    if ( ((usQueTailPos + 1 + 1) % NAS_LMM_INTRA_MSG_MAX_NUM) != usQueHeaderPos )
    {
        pucMsgBuff = pstMsgQue->aucMsgBuff[(usQueTailPos) % NAS_LMM_INTRA_MSG_MAX_NUM];

        /* 将申请的缓冲区清0 */
        NAS_LMM_MEM_SET_S(pucMsgBuff, NAS_EMM_INTRA_MSG_MAX_SIZE, 0, NAS_EMM_INTRA_MSG_MAX_SIZE);


        pstIntraMsgHeader                = (NAS_LMM_INTRA_MSG_STRU *)pucMsgBuff;

        /* 填写内部消息消息头中的长度域 */
        pstIntraMsgHeader->ulLength      = ulBuffSize;

        return (NasMmIntraMsgBlock *)pucMsgBuff;
    }
    else
    {
        /* 打印错误信息 */
        NAS_LMM_PUBM_LOG_ERR("NAS_LMM_GetSendIntraMsgBuffAddr, Queue full!");
        TLPS_PRINT2LAYER_ERROR(NAS_LMM_GetSendIntraMsgBuffAddr_ENUM
,LNAS_FUNCTION_LABEL1);

        return NAS_LMM_NULL_PTR;
    }
}


/*****************************************************************************
 Function Name  : NAS_EMM_SendIntraMsg
 Discription    : 发送内部消息函数
                  使用方法:先申请消息包(RRC_MAIN_GetSendIntraMsgBuffAddr),
                           返回地址,根据地址填写消息内容,然后调用该函数
                   该函数的实质是:使前面在内部消息队列申请消息包,填充消息
                   包的操作生效;
 Input          : pucIntraMsg   :指向内部消息的指针
 Output         : None
 Return         : 成功 失败
 History:
*****************************************************************************/
VOS_UINT32 NAS_LMM_MMSendIntraMsg(  VOS_VOID          **pucIntraMsg )/*lint -e818*/
{

    if ( NAS_LMM_NULL_PTR == pucIntraMsg )
    {
        /* 打印出错信息 */
        NAS_LMM_PUBM_LOG_ERR("NAS_LMM_SendIntraMsg, IntraMsg Null Pointer.");
        TLPS_PRINT2LAYER_ERROR(NAS_LMM_MMSendIntraMsg_ENUM
,LNAS_NULL_PTR);

        return  NAS_LMM_ERR_CODE_PTR_NULL;
    }


    /* 消息入队列 */
    NAS_LMM_MAIN_EnQueue();

    return  NAS_EMM_SUCC;
}/*lint +e818*/

/*****************************************************************************
 Function Name  : NAS_LMM_MAIN_EnQueue
 Discription    : 消息入队列,
                  调用OM的钩子函数，在OM中跟踪出来;
                  只给PUB模块使用，其他模块若需要用自己封装
 Input          : None
 Output         : None
 Return         :

 History:
      1. hanlufeng 41410  2008-02-25  移植代码
*****************************************************************************/
VOS_VOID    NAS_LMM_MAIN_EnQueue(VOS_VOID)
{
    NAS_LMM_INTRA_MSG_QUEUE_STRU            *pstMsgQue;

    /* 获取队列地址 */
    pstMsgQue         = NAS_LMM_GetMmIntrMsgQueueAddr();


    /* 调用OM的钩子函数，在OM中跟踪出来 */


    /* 循环队列的队尾指向下一个位置 */
    pstMsgQue->usTail = (pstMsgQue->usTail + 1) % NAS_LMM_INTRA_MSG_MAX_NUM;

    return;
}


/*****************************************************************************
 Function Name  : NAS_LMM_GetIntraMsgFromQueue
 Discription    : 在PUBLIC处理完外来消息后,接着检查是否有内部消息待处理,
                  如果有,则指向下一条待处理的内部消息,同时将该消息出队,
                  即:此消息将从消息队列中被删除,而不关心该消息是否已被
                  正确处理;
                  若该消息无法被当前状态处理,则MM将其排入消息缓存队列;
                  若该消息处理过程出错,例如消息参数有错,该消息队列不关心;
 Input          : None
 Output         : None
 Return         : NULL: 表示没有内部消息待处理
                  否则: 指向待处理的内部消息
 History:
*****************************************************************************/
VOS_UINT8 * NAS_LMM_GetIntraMsgFromQueue( VOS_VOID  )
{
    VOS_UINT16                          usQueHeaderPos;
    VOS_UINT16                          usQueTailPos;
    VOS_UINT8                          *pucMsg     = NAS_LMM_NULL_PTR;
    NAS_LMM_INTRA_MSG_QUEUE_STRU        *pstMsgQue  = NAS_LMM_NULL_PTR;

    /* 获取队列地址 */
    pstMsgQue      = NAS_LMM_GetMmIntrMsgQueueAddr();

    /* 队头队尾位置 */
    usQueHeaderPos = pstMsgQue->usHeader % NAS_LMM_INTRA_MSG_MAX_NUM;
    usQueTailPos   = pstMsgQue->usTail % NAS_LMM_INTRA_MSG_MAX_NUM;

    /* 队列为空 */
    if ( usQueHeaderPos == usQueTailPos )
    {
        return NAS_LMM_NULL_PTR;
    }

    /* 消息地址 */
    pucMsg = (pstMsgQue->aucMsgBuff)[usQueHeaderPos];

    /* 消息出队列 */
    NAS_LMM_DeQueue();

    return pucMsg;
}

/*****************************************************************************
 Function Name  : NAS_LMM_DeQueue
 Discription    : 消息出队列
 Input          : None
 Output         : None
 Return         :

 History:
*****************************************************************************/
VOS_VOID NAS_LMM_DeQueue(VOS_VOID)
{
    NAS_LMM_INTRA_MSG_QUEUE_STRU *pstMsgQue = NAS_LMM_NULL_PTR;


    /* 获取队列地址 */
    pstMsgQue           = NAS_LMM_GetMmIntrMsgQueueAddr();

    pstMsgQue->usHeader = (pstMsgQue->usHeader + 1) % NAS_LMM_INTRA_MSG_MAX_NUM;

    return;
}

/*****************************************************************************
 Function Name   : NAS_LMM_GetLmmMmcMsgBuf
 Description     : LMM发给MMC的消息通过该函数申请MMC内部消息队列的地址
                   PC环境下:仍然申请Dopra消息队列
                   单板环境下:申请MMC内部消息队列
 Input           : None
 Output          : None
 Return          : VOS_UINT32

 History         :
    1.zhengjunyan 00148421      2011-12-27  Draft Enact

*****************************************************************************/
MsgBlock *  NAS_LMM_GetLmmMmcMsgBuf( VOS_UINT32 ulBuffSize )
{
    MsgBlock                           *pstLmmMmcIntraMsg = VOS_NULL_PTR;

    NAS_LMM_PUBM_LOG_INFO("NAS_LMM_GetLmmMmcMsgBuf entered.");
    TLPS_PRINT2LAYER_INFO(NAS_LMM_GetLmmMmcMsgBuf_ENUM
,LNAS_ENTRY);

/* PC环境下，申请Dopra消息队列*/
#if(VOS_WIN32 == VOS_OS_VER)

    pstLmmMmcIntraMsg = (VOS_VOID *)NAS_LMM_ALLOC_MSG(ulBuffSize);

/* 单板环境下，申请MMC内部消息*/
#else
    pstLmmMmcIntraMsg = (VOS_VOID *)NAS_MML_GetIntMsgSendBuf(ulBuffSize);

#endif

    return pstLmmMmcIntraMsg;
}

/*****************************************************************************
 Function Name   : NAS_LMM_SendMmcIntraMsgBuf
 Description     : 发送LMM->MMC的消息
                   PC环境下:调用Dopra消息发送函数
                   单板环境下:调用MMC内部消息发送函数
 Input           : None
 Output          : None
 Return          : VOS_UINT32

 History         :
    1.zhengjunyan 00148421      2011-12-27  Draft Enact

*****************************************************************************/
VOS_VOID  NAS_LMM_SendLmmMmcMsg( const VOS_VOID *pstLmmMmcMsg )
{
    NAS_LMM_PUBM_LOG_INFO("NAS_LMM_SendLmmMmcMsg entered.");
    TLPS_PRINT2LAYER_INFO(NAS_LMM_SendLmmMmcMsg_ENUM
,LNAS_ENTRY);

/* PC环境下，发送Dopra消息队列*/
#if(VOS_WIN32 == VOS_OS_VER)

    NAS_LMM_SEND_MSG(pstLmmMmcMsg);
/* 单板环境下，发送MMC内部消息队列*/
#else
    #ifndef __PS_WIN32_RECUR__
    NAS_LMM_PUBM_PrintSendMsg((const PS_MSG_HEADER_STRU *)pstLmmMmcMsg,NAS_COMM_GET_MM_PRINT_BUF());

    NAS_MML_SndInternalMsg((VOS_VOID *)pstLmmMmcMsg);
    #else
    NAS_LMM_SEND_MSG(pstLmmMmcMsg);
    #endif

#endif
}
/*lint +e961*/
/*lint +e960*/
/*****************************************************************************
 Function Name  :
 Discription    :
 Input          :
 Output         : None
 Return         : None
 History:
      1.  Name+ID  yyyy-mm-dd  Draft Enact
*****************************************************************************/




#ifdef __cplusplus
    #if __cplusplus
        }
    #endif
#endif
/* end of 子系统+模块+文件名.c */
