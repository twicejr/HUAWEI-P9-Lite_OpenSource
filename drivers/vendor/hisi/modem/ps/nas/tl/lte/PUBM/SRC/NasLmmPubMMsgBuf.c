/******************************************************************************

        @(#)Copyright(C)2008,Hisilicon Co. LTD.

 ******************************************************************************
    File name   : NasLmmPubMMsgBuf.c
    Description :
    History     :
      1.hanlufeng 41410 2008-10-25 Draft Enact
      2.zhengjunyan 00148421   2011-05-28 文件名由 NasMmPubMMsgBuf.c修改为
                                           NasLmmPubMMsgBuf.c
******************************************************************************/


/*****************************************************************************
  1 Include HeadFile
*****************************************************************************/
#include    "NasLmmPubMInclude.h"
#include    "NasCommBuffer.h"

/*lint -e767*/
#define    THIS_FILE_ID            PS_FILE_ID_NASMMPUBMMSGBUF_C
#define    THIS_NAS_FILE_ID        NAS_FILE_ID_NASMMPUBMMSGBUF_C
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
 Function Name   : NAS_LMM_ExistMsgInFsmQue
 Description     : 判断QUE中是否有消息存在
 Input           : None
 Output          : None
 Return          : VOS_BOOL

 History         :
    1.    leili  00132387      2010-4-8  Draft Enact

*****************************************************************************/
VOS_UINT32  NAS_LMM_ExistMsgInFsmQue(NAS_LMM_PARALLEL_FSM_ENUM_UINT16 enParalFsmId,
                                 VOS_UINT32                 ulPriLevel)
{
    NAS_LMM_FSM_MSG_BUF_STRU             *pstFsmMsgBuffAddr = NAS_LMM_NULL_PTR;
    VOS_UINT8                           ucMsgCont = NAS_EMM_MSG_BUF_EMPTY;
    VOS_UINT32                          ulRsltExistMsgInQue = NAS_LMM_FAIL;


    /* 获取缓存 FSM Buffer的地址 */
    pstFsmMsgBuffAddr                   = NAS_LMM_GetFsmBufAddr( enParalFsmId );
    if(NAS_LMM_NULL_PTR                  == pstFsmMsgBuffAddr)
    {
        NAS_LMM_PUBM_LOG_WARN(           "NAS_LMM_ExistMsgInFsmQue, Get pstFsmMsgBuffAddr Fail!");
        TLPS_PRINT2LAYER_WARNING(NAS_LMM_ExistMsgInFsmQue_ENUM
,LNAS_NULL_PTR);
        return  NAS_LMM_FAIL;

    }
    if (NAS_LMM_STORE_HIGH_PRIO_MSG == ulPriLevel)
    {
        NAS_LMM_PUBM_LOG_NORM("NAS_LMM_ExistMsgInFsmQue: HIGH PRIO QUE!");
        TLPS_PRINT2LAYER_INFO(NAS_LMM_ExistMsgInFsmQue_ENUM
,LNAS_FUNCTION_LABEL1);
        ucMsgCont                       = pstFsmMsgBuffAddr->ucHighPrioCnt;
    }
    else if (NAS_LMM_STORE_LOW_PRIO_MSG == ulPriLevel)
    {
        NAS_LMM_PUBM_LOG_NORM("NAS_LMM_ExistMsgInFsmQue: LOW PRIO QUE!");
        TLPS_PRINT2LAYER_INFO(NAS_LMM_ExistMsgInFsmQue_ENUM
,LNAS_FUNCTION_LABEL2);
        ucMsgCont                       = pstFsmMsgBuffAddr->ucLowPrioCnt;
    }
    else
    {
        NAS_LMM_PUBM_LOG_WARN("NAS_LMM_ExistMsgInFsmQue: OTHER PRIO QUE!");
        TLPS_PRINT2LAYER_WARNING(NAS_LMM_ExistMsgInFsmQue_ENUM
,LNAS_FUNCTION_LABEL3);
    }

    if (NAS_EMM_MSG_BUF_EMPTY != ucMsgCont)
    {
        NAS_LMM_PUBM_LOG_NORM("NAS_ExistMsgInFsmQue: EXIST MSG IN QUE!");
        TLPS_PRINT2LAYER_INFO(NAS_LMM_ExistMsgInFsmQue_ENUM
,LNAS_FUNCTION_LABEL4);
        ulRsltExistMsgInQue = NAS_LMM_SUCC;
    }

    return ulRsltExistMsgInQue;
}




/*****************************************************************************
 Function Name   : NAS_LMM_RemoveMsgFromFsmQue
 Description     : 如果需要缓存的消息在Que中，需要先释放旧的
 Input           : None
 Output          : None
 Return          : VOS_VOID

 History         :
    1.X00148705    2010-4-6  Draft Enact

*****************************************************************************/
/*lint -e960*/
/*lint -e961*/
VOS_VOID  NAS_LMM_RemoveMsgFromFsmQue(
    NAS_LMM_FSM_MSG_BUF_STRU*            pstFsmMsgBuffAddr,
    VOS_UINT32                          ulMsgType,
    VOS_UINT32                          ulPriLevel)

{
    VOS_UINT8                           ucCnt;
    NAS_LMM_BUFF_MSG_STRU*              pstMsgQue         = NAS_LMM_NULL_PTR;
    VOS_BOOL                            bRsltRemoveMsgFromQue = VOS_FALSE;


    /* 参数检查  */

    if(NAS_LMM_NULL_PTR                  == pstFsmMsgBuffAddr)
    {
        NAS_LMM_PUBM_LOG_WARN(           "NAS_LMM_RemoveMsgFromFsmQue, Get pstFsmMsgBuffAddr Fail!");
        TLPS_PRINT2LAYER_WARNING(NAS_LMM_RemoveMsgFromFsmQue_ENUM
,LNAS_NULL_PTR);
        return;

    }
    if( (NAS_LMM_STORE_HIGH_PRIO_MSG != ulPriLevel) &&
        (NAS_LMM_STORE_LOW_PRIO_MSG  != ulPriLevel))
    {
        NAS_LMM_PUBM_LOG1_WARN(           "NAS_LMM_RemoveMsgFromFsmQue, PRIO Fail!",ulPriLevel);
        TLPS_PRINT2LAYER_WARNING(NAS_LMM_RemoveMsgFromFsmQue_ENUM
,LNAS_FAIL);
        return;

    }
    /* 在高优先级和低优先级中查找ulMsgType，如果已有，需要释放  */

    pstMsgQue                           = pstFsmMsgBuffAddr->astHighPrioBufQue;
    ucCnt                               = pstFsmMsgBuffAddr->ucHighPrioCnt;
    bRsltRemoveMsgFromQue               = NAS_LMM_RemoveMsgFromQue( pstMsgQue,
                                                                ucCnt,
                                                                ulMsgType);
    /*消息成功释放，更新MSG COUNT */
    if( bRsltRemoveMsgFromQue )
    {
        pstFsmMsgBuffAddr->ucHighPrioCnt-=1;
    }

    /*低优先级 */
    pstMsgQue                           = pstFsmMsgBuffAddr->astLowPrioBufQue;
    ucCnt                               = pstFsmMsgBuffAddr->ucLowPrioCnt;

    bRsltRemoveMsgFromQue               = NAS_LMM_RemoveMsgFromQue( pstMsgQue,
                                                                ucCnt,
                                                                ulMsgType);

    /*消息成功释放，更新MSG COUNT */
    if( bRsltRemoveMsgFromQue )
    {
        pstFsmMsgBuffAddr->ucLowPrioCnt-=1;
    }

    return;
}


VOS_BOOL  NAS_LMM_RemoveMsgFromQue(
    NAS_LMM_BUFF_MSG_STRU*              pstMsgQue ,
    VOS_UINT8                           ucCnt,
    VOS_UINT32                          ulMsgType
                                           )
{
    VOS_UINT8                           ucMoveCnt;
    VOS_UINT32                          ulBufMsgType;
    VOS_UINT8                           ucSearchCnt = 0;
    VOS_BOOL                            bFlag = VOS_FALSE;
    NAS_LMM_BUFF_MSG_STRU*              pstBufMsg =  NAS_LMM_NULL_PTR;
    VOS_UINT32                          ulRslt;

    /*参数检查  */

    if(NAS_LMM_NULL_PTR                  == pstMsgQue)
    {
        NAS_LMM_PUBM_LOG_WARN(           "NAS_LMM_RemoveMsgFromQue, pstMsgQue == NAS_LMM_NULL_PTR");
        TLPS_PRINT2LAYER_WARNING(NAS_LMM_RemoveMsgFromQue_ENUM
,LNAS_NULL_PTR);
        return(VOS_FALSE);

    }
    /*在Queue中查找ulMsgType  */
    for(ucSearchCnt = 0 ; (ucSearchCnt < ucCnt) && (ucSearchCnt < NAS_EMM_BUF_MSG_MAX_NUM);
        ucSearchCnt++ )
    {
        pstBufMsg    = (pstMsgQue+ucSearchCnt);
        ulBufMsgType = pstBufMsg->ulEvtType;

        /* 判断消息是否已存在 */
        if( ulBufMsgType                == ulMsgType )
        {
            bFlag = VOS_TRUE;
            break;
        }
    }

    /* 如果消息存在*/
    if(bFlag)
    {
        /*释放已存在的消息 */
        if((pstBufMsg != NAS_LMM_NULL_PTR) &&
           (pstBufMsg->pBuffMsg != NAS_LMM_NULL_PTR) )
        {
            ulRslt = NAS_COMM_FreeBuffItem( NAS_COMM_BUFF_TYPE_EMM, pstBufMsg->pBuffMsg );

            if (NAS_COMM_BUFF_SUCCESS != ulRslt)
            {
                NAS_LMM_PUBM_LOG_WARN("NAS_LMM_RemoveMsgFromQue, Memory Free is not succ");
                TLPS_PRINT2LAYER_WARNING(NAS_LMM_RemoveMsgFromQue_ENUM
,LNAS_FAIL);

            }
        }

        /*把后面的消息前移  */

        /* 如果消息不在最后 */

        if(ucSearchCnt < (ucCnt-1) )
        {
            for(ucMoveCnt = ucSearchCnt; (ucMoveCnt < (ucCnt-1)) && (ucMoveCnt < (NAS_EMM_BUF_MSG_MAX_NUM-1));
                ucMoveCnt++ )
            {
                pstMsgQue[ucMoveCnt].pBuffMsg
                                            = pstMsgQue[ucMoveCnt+1].pBuffMsg;
                pstMsgQue[ucMoveCnt].ulEvtType
                                            = pstMsgQue[ucMoveCnt+1].ulEvtType;
            }
        }

        pstMsgQue[ucCnt-1].pBuffMsg = NAS_LMM_NULL_PTR;
        pstMsgQue[ucCnt-1].ulEvtType= 0;

        return(VOS_TRUE);
    }

    return(VOS_FALSE);
}


VOS_VOID  NAS_LMM_BufMsgQueFree( VOS_VOID )
{
    /* 当前只考虑释放EMM和MMC的高低优先级；如果以后用到其它的Que或中优先级，
    ** 需要添加对应的资源的处理 */

    NAS_LMM_PUBM_LOG_NORM( "NAS_LMM_BufMsgQueFree" );
    TLPS_PRINT2LAYER_WARNING(NAS_LMM_BufMsgQueFree_ENUM
,LNAS_ENTRY);

    NAS_LMM_ClearBufMsgQue( NAS_LMM_PARALLEL_FSM_EMM , NAS_LMM_STORE_HIGH_PRIO_MSG );
    NAS_LMM_ClearBufMsgQue( NAS_LMM_PARALLEL_FSM_EMM , NAS_LMM_STORE_LOW_PRIO_MSG );
    /*NAS_LMM_ClearBufMsgQue( NAS_LMM_PARALLEL_FSM_MMC , NAS_LMM_STORE_HIGH_PRIO_MSG );
    NAS_LMM_ClearBufMsgQue( NAS_LMM_PARALLEL_FSM_MMC , NAS_LMM_STORE_LOW_PRIO_MSG );*/
    NAS_LMM_ClearBufMsgQue( NAS_LMM_PARALLEL_FSM_SECU , NAS_LMM_STORE_HIGH_PRIO_MSG );
    NAS_LMM_ClearBufMsgQue( NAS_LMM_PARALLEL_FSM_SECU , NAS_LMM_STORE_LOW_PRIO_MSG );
}


/*****************************************************************************
 Function Name   : NAS_LMM_BufMsgInQue
 Description     :
 Input           : FSM的缓存Buffer的地址，优先级号
 Output          : None
 Return          : OK,ERROR

 History         :
    1.X00148705    2010-4-6  Draft Enact

*****************************************************************************/
VOS_UINT32  NAS_LMM_BufMsgInQue(
    NAS_LMM_FSM_MSG_BUF_STRU*            pstFsmAddr,
    VOS_UINT32                          ulPriLevel)

{
    VOS_UINT32                          ulRslt = NAS_LMM_FAIL;
    VOS_UINT8                           *pucCnt = NAS_LMM_NULL_PTR;

    /* 入参检查出错 */
    /* 打印错误信息 */

    if ( (ulPriLevel < NAS_LMM_STORE_HIGH_PRIO_MSG ) ||
         (ulPriLevel > NAS_LMM_STORE_LOW_PRIO_MSG ))
    {
        NAS_LMM_PUBM_LOG1_ERR("NAS_LMM_BufMsgInQue, error: ... ",ulPriLevel);
        TLPS_PRINT2LAYER_ERROR1(NAS_LMM_BufMsgInQue_ENUM
,LNAS_FUNCTION_LABEL1,ulPriLevel);
        return NAS_LMM_FAIL;
    }

    if(NAS_LMM_NULL_PTR == pstFsmAddr)
    {
        NAS_LMM_PUBM_LOG_ERR("NAS_LMM_BufMsgInQue, error: NAS_LMM_NULL_PTR == pstFsmAddr ");
        TLPS_PRINT2LAYER_ERROR(NAS_LMM_BufMsgInQue_ENUM
,LNAS_FUNCTION_LABEL2);
        return NAS_LMM_FAIL;
    }

    /* 依据优先级更新Queue的信息 */
    if( NAS_LMM_STORE_HIGH_PRIO_MSG      == ulPriLevel )
    {
        pucCnt                           = &(pstFsmAddr->ucHighPrioCnt);
    }
    else if( NAS_LMM_STORE_LOW_PRIO_MSG  == ulPriLevel )
    {
        pucCnt                           = &(pstFsmAddr->ucLowPrioCnt);
    }
    else
    {
        NAS_LMM_PUBM_LOG_NORM("NAS_LMM_BufMsgInQue: OTHER PRIO QUE ");
        TLPS_PRINT2LAYER_INFO(NAS_LMM_BufMsgInQue_ENUM
,LNAS_FUNCTION_LABEL3);
    }

    /* 更新Count的值 */
    if( NAS_LMM_NULL_PTR                 != pucCnt )
    {
        *pucCnt                          += 1;
        if( *pucCnt                      <= NAS_EMM_BUF_MSG_MAX_NUM )
        {
            ulRslt                      = NAS_LMM_SUCC;
        }
        else
        {
            NAS_LMM_PUBM_LOG_NORM("NAS_LMM_BufMsgInQue: QUE is overflow ");
            TLPS_PRINT2LAYER_INFO(NAS_LMM_BufMsgInQue_ENUM
,LNAS_FUNCTION_LABEL4);
        }

    }

    return( ulRslt );
}


/*****************************************************************************
 Function Name  : NAS_GetStoreBufMsgAddr
 Discription    : 获取将消息缓存到的地址
 Input          :
 Output         : None
 Return         :
 History:
      1.  hanlufeng 41410 2008-10-25 Draft Enact
      2.  X00148705       2009-04-06 修改消息缓存的方法
*****************************************************************************/
NAS_LMM_BUFF_MSG_STRU * NAS_LMM_GetStoreBufMsgAddr(
                NAS_LMM_FSM_MSG_BUF_STRU*        pstFsmAddr,
                VOS_UINT32                      ulPriLevel)
{
    NAS_LMM_BUFF_MSG_STRU               *pstMsgBuffAddr = NAS_LMM_NULL_PTR;
    VOS_UINT8                           ucCnt;

    /* 入参检查出错 */
    /* 打印错误信息 */
    if ( (ulPriLevel < NAS_LMM_STORE_HIGH_PRIO_MSG ) ||
         (ulPriLevel > NAS_LMM_STORE_LOW_PRIO_MSG ))
    {
        NAS_LMM_PUBM_LOG1_ERR("NAS_GetStoreBufMsgAddr, error: ... ",ulPriLevel);
        TLPS_PRINT2LAYER_ERROR1(NAS_LMM_GetStoreBufMsgAddr_ENUM
,LNAS_FUNCTION_LABEL1,ulPriLevel);
        return NAS_LMM_NULL_PTR;
    }

    if(NAS_LMM_NULL_PTR == pstFsmAddr)
    {
        NAS_LMM_PUBM_LOG_ERR("NAS_GetStoreBufMsgAddr, error: NAS_LMM_NULL_PTR == pstFsmAddr ");
        TLPS_PRINT2LAYER_ERROR(NAS_LMM_GetStoreBufMsgAddr_ENUM
,LNAS_FUNCTION_LABEL2);
        return NAS_LMM_NULL_PTR;
    }

    /* 依据优先级获得缓存Buffer的地址*/

    if( NAS_LMM_STORE_HIGH_PRIO_MSG == ulPriLevel )
    {
        ucCnt = pstFsmAddr->ucHighPrioCnt;
        if(ucCnt < NAS_EMM_BUF_MSG_MAX_NUM)
        {
            pstMsgBuffAddr = (pstFsmAddr->astHighPrioBufQue+ucCnt);
        }
    }
    else if( NAS_LMM_STORE_LOW_PRIO_MSG == ulPriLevel )
    {
        ucCnt = pstFsmAddr->ucLowPrioCnt;
        if(ucCnt < NAS_EMM_BUF_MSG_MAX_NUM)
        {
            pstMsgBuffAddr = (pstFsmAddr->astLowPrioBufQue+ucCnt);
        }
    }
    else
    {
        NAS_LMM_PUBM_LOG_NORM("NAS_GetStoreBufMsgAddr: OTHER QUE ADDR");
        TLPS_PRINT2LAYER_INFO(NAS_LMM_GetStoreBufMsgAddr_ENUM
,LNAS_FUNCTION_LABEL3);
    }
    return( pstMsgBuffAddr );
}


NAS_LMM_FSM_MSG_BUF_STRU* NAS_LMM_GetFsmBufAddr( NAS_LMM_PARALLEL_FSM_ENUM_UINT16
                                                          enParalFsmId )
{
    if(enParalFsmId >= NAS_LMM_PARALLEL_FSM_BUTT)
    {
        NAS_LMM_PUBM_LOG1_ERR( "NAS_LMM_GetFsmBufAddr: Error enParalFsmId:",enParalFsmId);
        TLPS_PRINT2LAYER_ERROR1(NAS_LMM_GetFsmBufAddr_ENUM
                            ,LNAS_FUNCTION_LABEL1,enParalFsmId);
        return(NAS_LMM_NULL_PTR);
    }
    else
    {
        return(NAS_LMM_GetFsmBufQueueAddr(enParalFsmId));
    }
}


/*****************************************************************************
 Function Name  : NAS_LMM_StoreMsgToQue
 Discription    : 将消息缓存至指定的并行状态机的消息缓存队列中
                  UE 1.0不区分优先级，一律放入高优先级队列
 Input          : 并行状态机ID 事件类型 处理标志 消息指针
 Output         : None
 Return         :
 History:
      1.  hanlufeng 41410 2008-10-25 Draft Enact
      2.  X00148705 2010-04-06 修改消息缓存的方法

*****************************************************************************/
VOS_UINT32  NAS_LMM_StoreMsgToQue(
                NAS_LMM_PARALLEL_FSM_ENUM_UINT16   enParalFsmId,
                VOS_UINT32                        ulBufPriLevel,
                VOS_UINT32                        ulMsgType,
                const VOS_VOID                    *pMsg )
{
    VOS_UINT32                          ulLength;
    VOS_UINT8                          *pucMsgBuff          = NAS_LMM_NULL_PTR;
    NAS_LMM_BUFF_MSG_STRU              *pstBuffer           = NAS_LMM_NULL_PTR;
    NAS_LMM_FSM_MSG_BUF_STRU            *pstFsmMsgBuffAddr   = NAS_LMM_NULL_PTR;
    VOS_UINT32                          ulRslt;

    /* 入口检查 ，为了避免内存泄漏，当前只支持EMM,如果需要支持MMC，可以修改以下条件即可,
    ** 并且在对应的模块需要添加相应的处理;另外对于中优先级的缓存，也不支持;*/
    if ( enParalFsmId != NAS_LMM_PARALLEL_FSM_EMM )
    {
        NAS_LMM_PUBM_LOG1_ERR("NAS_LMM_StoreMsgToQue, FsmId error, FsmId:", enParalFsmId);
        TLPS_PRINT2LAYER_ERROR1(NAS_LMM_StoreMsgToQue_ENUM
,LNAS_FUNCTION_LABEL1,enParalFsmId);
        return  NAS_LMM_ERR_CODE_ARRAY_OVERFLOW;
    }

    if ( NAS_LMM_NULL_PTR == pMsg )
    {
        NAS_LMM_PUBM_LOG_WARN("NAS_LMM_StoreMsgToQue, Msg is NULL!");
        TLPS_PRINT2LAYER_WARNING(NAS_LMM_StoreMsgToQue_ENUM
,LNAS_FUNCTION_LABEL2);
        return  NAS_LMM_ERR_CODE_PTR_NULL;
    }
    if( (NAS_LMM_STORE_HIGH_PRIO_MSG != ulBufPriLevel) &&
        (NAS_LMM_STORE_LOW_PRIO_MSG  != ulBufPriLevel))
    {
        NAS_LMM_PUBM_LOG1_WARN("NAS_LMM_StoreMsgToQue, Prio err!",ulBufPriLevel);
        TLPS_PRINT2LAYER_WARNING1(NAS_LMM_StoreMsgToQue_ENUM
,LNAS_FUNCTION_LABEL3,ulBufPriLevel);
        return  NAS_LMM_ERR_CODE_PARA_INVALID;
    }

    /* 获取缓存Buffer的地址 */
    pstFsmMsgBuffAddr                   = NAS_LMM_GetFsmBufAddr( enParalFsmId );
    if(NAS_LMM_NULL_PTR                  == pstFsmMsgBuffAddr)
    {
        NAS_LMM_PUBM_LOG_WARN(           "NAS_LMM_StoreMsgToQue, Get pstFsmMsgBuffAddr Fail!");
        TLPS_PRINT2LAYER_WARNING(NAS_LMM_StoreMsgToQue_ENUM
,LNAS_FUNCTION_LABEL4);
        return  NAS_LMM_ERR_CODE_PTR_NULL;

    }

    /*如果消息存在，移去该消息 */
    NAS_LMM_RemoveMsgFromFsmQue( pstFsmMsgBuffAddr, ulMsgType, ulBufPriLevel );


    pstBuffer = NAS_LMM_GetStoreBufMsgAddr( pstFsmMsgBuffAddr, ulBufPriLevel );
    if(NAS_LMM_NULL_PTR                  == pstBuffer)
    {
        NAS_LMM_PUBM_LOG_WARN(           "NAS_LMM_StoreMsgToQue, GetStoreBufMsgAddr Fail!");
        TLPS_PRINT2LAYER_WARNING(NAS_LMM_StoreMsgToQue_ENUM
,LNAS_FUNCTION_LABEL5);
        return  NAS_LMM_ERR_CODE_PTR_NULL;

    }

    /* 获取消息长度  */
    ulLength  = ((NAS_LMM_MSG_HEADER_STRU *)pMsg)->ulLength
                            + NAS_EMM_PUB_VOS_MSG_HEADER_LEN;

    /* 动态分配缓存空间 */
    pucMsgBuff                          = NAS_COMM_AllocBuffItem(NAS_COMM_BUFF_TYPE_EMM, ulLength);
    if(NAS_LMM_NULL_PTR                  == pucMsgBuff )
    {
        NAS_LMM_PUBM_LOG_WARN(           "NAS_LMM_StoreMsgToQue, Msg Allocate Fail!");
        TLPS_PRINT2LAYER_WARNING(NAS_LMM_StoreMsgToQue_ENUM
,LNAS_FUNCTION_LABEL6);
        return  NAS_LMM_ERR_CODE_PTR_NULL;
    }

    /* 把需要缓存的消息拷贝到申请到的地址中 */
    NAS_LMM_MEM_CPY_S( pucMsgBuff, ulLength, pMsg, ulLength );

    /* 消息入队 */
    pstBuffer->pBuffMsg                 = (VOS_VOID*)(pucMsgBuff);
    pstBuffer->ulEvtType                = ulMsgType;
    ulRslt                              = NAS_LMM_BufMsgInQue( pstFsmMsgBuffAddr,ulBufPriLevel );

    if( NAS_LMM_FAIL                     == ulRslt)
    {
        NAS_LMM_PUBM_LOG_WARN(           "NAS_LMM_StoreMsgToQue, In Queue Fail!");
        TLPS_PRINT2LAYER_WARNING(NAS_LMM_StoreMsgToQue_ENUM
,LNAS_FUNCTION_LABEL7);
        ulRslt = NAS_COMM_FreeBuffItem(NAS_COMM_BUFF_TYPE_EMM, pucMsgBuff);

        if (NAS_COMM_BUFF_SUCCESS != ulRslt)
        {
            NAS_LMM_PUBM_LOG_WARN("NAS_LMM_StoreMsgToQue, Memory Free is not succ");
            TLPS_PRINT2LAYER_WARNING(NAS_LMM_StoreMsgToQue_ENUM
,LNAS_FUNCTION_LABEL8);
        }

        pstBuffer->pBuffMsg             = NAS_LMM_NULL_PTR;
        pstBuffer->ulEvtType            = 0;
        return  NAS_LMM_ERR_CODE_PTR_NULL;
    }

    return  NAS_LMM_SUCC;
}


/*****************************************************************************
 Function Name  : NAS_EMM_OutMsgFromBuffer
 Discription    : 从状态机缓存队列中出队一个消息
                  外部消息和内部消息队列理的消息处理完成后，检查是否有缓存的消息
                  需要处理，
                  即，有些状态下收到某些消息后，暂时不处理，而是缓存起来，等进入
                  合适的状态后再处理;
                  包括两步操作:
                                获取出队消息地址;
                                消息出队;
 Input          : 并行状态机ID
                  ulBufPriLevel
 Output         :
 Return         : 消息指针
                  VOS_NULL  :队列中没有缓存消息
 History:
      1.  hanlufeng 41410 2008-10-25 Draft Enact
      2.  leili 00132387    2010-04-06  modify
*****************************************************************************/
VOS_UINT32 NAS_LMM_OutMsgFromQue( NAS_LMM_PARALLEL_FSM_ENUM_UINT16 enParalFsmId,
                                        VOS_UINT32         ulBufPriLevel,
                                        NAS_LMM_BUFF_MSG_STRU   *pstGetMsg)
{
    VOS_UINT32                          ulLoop;
    VOS_UINT8                           *pucMsgCnt          = NAS_LMM_NULL_PTR;
    NAS_LMM_BUFF_MSG_STRU               *pstBuffer          = NAS_LMM_NULL_PTR;
    NAS_LMM_FSM_MSG_BUF_STRU             *pstFsmMsgBuffAddr  = NAS_LMM_NULL_PTR;
    VOS_UINT32                          ulRslt              = NAS_LMM_NOT_TRAVEL_BUFFER_MSG;


    /* 参数检查*/
    if (enParalFsmId != NAS_LMM_PARALLEL_FSM_EMM )
    {
        NAS_LMM_PUBM_LOG1_WARN("NAS_LMM_OutMsgFromQue: FsmId error, FsmId:", enParalFsmId);
        TLPS_PRINT2LAYER_WARNING1(NAS_LMM_OutMsgFromQue_ENUM
,LNAS_FUNCTION_LABEL1,enParalFsmId);
        return ulRslt;
    }

    if (NAS_LMM_NULL_PTR == pstGetMsg)
    {
        NAS_LMM_PUBM_LOG_WARN("NAS_LMM_OutMsgFromQue: pstGetMsg is null");
        TLPS_PRINT2LAYER_WARNING(NAS_LMM_OutMsgFromQue_ENUM
,LNAS_FUNCTION_LABEL2);
        return ulRslt;
    }

    /* 获取缓存FSM Buffer的地址 */

    pstFsmMsgBuffAddr                   = NAS_LMM_GetFsmBufAddr( enParalFsmId );
    if(NAS_LMM_NULL_PTR                  == pstFsmMsgBuffAddr)
    {
        NAS_LMM_PUBM_LOG_WARN(           "NAS_LMM_OutMsgFromQue, Get pstFsmMsgBuffAddr Fail!");
        TLPS_PRINT2LAYER_WARNING(NAS_LMM_OutMsgFromQue_ENUM
,LNAS_FUNCTION_LABEL3);
        return  ulRslt;

    }

    /* 依据优先级取相关参数*/

    if (NAS_LMM_STORE_HIGH_PRIO_MSG == ulBufPriLevel)
    {
        NAS_LMM_PUBM_LOG_NORM("NAS_LMM_OutMsgFromQue: high prio buff");
        TLPS_PRINT2LAYER_INFO(NAS_LMM_OutMsgFromQue_ENUM
,LNAS_FUNCTION_LABEL4);
        pstBuffer = pstFsmMsgBuffAddr->astHighPrioBufQue;
        pucMsgCnt = &(pstFsmMsgBuffAddr->ucHighPrioCnt);

    }
    else if (NAS_LMM_STORE_LOW_PRIO_MSG == ulBufPriLevel)
    {

        NAS_LMM_PUBM_LOG_NORM("NAS_LMM_OutMsgFromQue: low prio buff");
        TLPS_PRINT2LAYER_INFO(NAS_LMM_OutMsgFromQue_ENUM
,LNAS_FUNCTION_LABEL5);
        pstBuffer = pstFsmMsgBuffAddr->astLowPrioBufQue;
        pucMsgCnt = &(pstFsmMsgBuffAddr->ucLowPrioCnt);
    }
    else
    {
        NAS_LMM_PUBM_LOG_WARN("NAS_LMM_OutMsgFromQue is entered");
        TLPS_PRINT2LAYER_INFO(NAS_LMM_OutMsgFromQue_ENUM
,LNAS_FUNCTION_LABEL6);
        return ulRslt;
    }


    /* 队列中有消息存在 */

    if ((*pucMsgCnt > 0) && (*pucMsgCnt <= NAS_EMM_BUF_MSG_MAX_NUM))
    {
        NAS_LMM_PUBM_LOG1_NORM("NAS_LMM_OutMsgFromQue: ucMsgCnt valid, *pucMsgCnt = ",*pucMsgCnt);
        TLPS_PRINT2LAYER_INFO1(NAS_LMM_OutMsgFromQue_ENUM
,LNAS_FUNCTION_LABEL7,*pucMsgCnt);

        /* 将第一个发送出来 */
        pstGetMsg->ulEvtType = pstBuffer[0].ulEvtType;
        pstGetMsg->pBuffMsg = pstBuffer[0].pBuffMsg;

        /* 后面的依次前移 */
        for (ulLoop = 1; ulLoop < *pucMsgCnt; ulLoop++)
        {
            pstBuffer[ulLoop - 1].pBuffMsg  = pstBuffer[ulLoop].pBuffMsg;
            pstBuffer[ulLoop - 1].ulEvtType = pstBuffer[ulLoop].ulEvtType;
        }

        /* 将消息缓存指针置空 */
        pstBuffer[*pucMsgCnt - 1].pBuffMsg = VOS_NULL_PTR;
        pstBuffer[*pucMsgCnt - 1].ulEvtType = 0;

        /* 数目-1 */
        (*pucMsgCnt) --;

        ulRslt = NAS_LMM_TRAVEL_BUFFER_MSG;

    }
    else
    {
        NAS_LMM_PUBM_LOG_NORM("NAS_LMM_OutMsgFromQue: *pucMsgCnt is invalid");
        TLPS_PRINT2LAYER_INFO(NAS_LMM_OutMsgFromQue_ENUM
,LNAS_FUNCTION_LABEL8);
    }

    return ulRslt;
}

/*****************************************************************************
 Function Name  : NAS_LMM_ClearBufMsgQue
 Discription    : 释放队列中存放的内存
 Input          :
 Output         : None
 Return         : None
 History:
      1.  X00148705 2010-04-06 修改消息缓存的方法
*****************************************************************************/
VOS_VOID    NAS_LMM_ClearBufMsgQue(
                NAS_LMM_PARALLEL_FSM_ENUM_UINT16     enParalFsmId,
                VOS_UINT32                          ulBufPriLevel)
{

    NAS_LMM_FSM_MSG_BUF_STRU             *pstFsmMsgBuffAddr  = NAS_LMM_NULL_PTR;
    NAS_LMM_BUFF_MSG_STRU               *pstBuffer          = NAS_LMM_NULL_PTR;
    NAS_LMM_BUFF_MSG_STRU               *pstQueMsg          = NAS_LMM_NULL_PTR;
    VOS_UINT8                           *pucCnt             = NAS_LMM_NULL_PTR;
    VOS_UINT8                           ucFreeCnt;
    VOS_UINT32                          ulRslt;

    /* 获取缓存FSM Buffer的地址 */
    pstFsmMsgBuffAddr                   = NAS_LMM_GetFsmBufAddr( enParalFsmId );
    if(NAS_LMM_NULL_PTR                  == pstFsmMsgBuffAddr)
    {
        NAS_LMM_PUBM_LOG_WARN(           "NAS_LMM_ClearBufMsgQue, Get pstFsmMsgBuffAddr Fail!");
        TLPS_PRINT2LAYER_WARNING(NAS_LMM_ClearBufMsgQue_ENUM
,LNAS_NULL_PTR);
        return;

    }

    /* 依据优先级取消息  */
    if (NAS_LMM_STORE_HIGH_PRIO_MSG      == ulBufPriLevel)
    {
        pucCnt                           = &(pstFsmMsgBuffAddr->ucHighPrioCnt);
        pstQueMsg                        = pstFsmMsgBuffAddr->astHighPrioBufQue;
    }
    else if (NAS_LMM_STORE_LOW_PRIO_MSG      == ulBufPriLevel)
    {
        pucCnt                           = &(pstFsmMsgBuffAddr->ucLowPrioCnt );
        pstQueMsg                        = pstFsmMsgBuffAddr->astLowPrioBufQue;
    }
    else
    {
        NAS_LMM_PUBM_LOG_NORM("NAS_LMM_ClearBufMsgQue: OTHER QUE");
        TLPS_PRINT2LAYER_INFO(NAS_LMM_ClearBufMsgQue_ENUM
,LNAS_FUNCTION_LABEL1);
    }

    /* 释放消息*/
    if ( (pucCnt != NAS_LMM_NULL_PTR) && (pstQueMsg != NAS_LMM_NULL_PTR) )
    {
        for(ucFreeCnt = 0 ; (ucFreeCnt < *pucCnt) && (ucFreeCnt < NAS_EMM_BUF_MSG_MAX_NUM) ; ucFreeCnt++)
        {
            pstBuffer                   = pstQueMsg[ucFreeCnt].pBuffMsg;
            ulRslt = NAS_COMM_FreeBuffItem(NAS_COMM_BUFF_TYPE_EMM, pstBuffer);

            if (NAS_COMM_BUFF_SUCCESS != ulRslt)
            {
                NAS_LMM_PUBM_LOG_WARN("NAS_LMM_ClearBufMsgQue, Memory Free is not succ");
                TLPS_PRINT2LAYER_WARNING(NAS_LMM_ClearBufMsgQue_ENUM
,LNAS_FUNCTION_LABEL2);
            }

            /* 赋初值   */
            pstQueMsg[ucFreeCnt].pBuffMsg
                                        = NAS_LMM_NULL_PTR;
            pstQueMsg[ucFreeCnt].ulEvtType
                                        = 0;

            NAS_LMM_PUBM_LOG3_NORM(       "NAS_LMM_ClearBufMsgQue: Free Msg: enParalFsmId:,ulBufPriLevel,*pucCnt",
                                          enParalFsmId,ulBufPriLevel,*pucCnt);
            TLPS_PRINT2LAYER_INFO1(NAS_LMM_ClearBufMsgQue_ENUM
,LNAS_FUNCTION_LABEL3,
                                          enParalFsmId);
            TLPS_PRINT2LAYER_INFO2(NAS_LMM_ClearBufMsgQue_ENUM
,LNAS_FUNCTION_LABEL4,
                                          ulBufPriLevel,*pucCnt);

        }

        *pucCnt                         = 0;
    }

    return;
}
/*lint +e961*/
/*lint +e960*/

/*****************************************************************************
 Function Name   : NAS_LMM_InitBufMsgQue
 Description     : 不释放内存，只是全局变量赋值
 Input           : None
 Output          : None
 Return          : VOS_VOID

 History         :
    1.X00148705     2010-4-7  Draft Enact

*****************************************************************************/
VOS_VOID  NAS_EMM_InitBufMsgQue( VOS_VOID )
{
    VOS_UINT32                          ulCont;
    NAS_LMM_FSM_MSG_BUF_STRU             *pstEmmFsmMsgBuf;

    NAS_LMM_PUBM_LOG_NORM(
    "NAS_EMM_InitBufMsgQue              START INIT...");
    TLPS_PRINT2LAYER_INFO(NAS_EMM_InitBufMsgQue_ENUM
,LNAS_BEGIN);

    /* 当前状态初始化 */
    /* 缓存消息队列初始化 */
    pstEmmFsmMsgBuf                     = NAS_LMM_GetFsmBufQueueAddr(NAS_LMM_PARALLEL_FSM_EMM);
    pstEmmFsmMsgBuf->ucHighPrioCnt      = NAS_EMM_MSG_BUF_EMPTY;
    pstEmmFsmMsgBuf->ucMidPrioCnt       = NAS_EMM_MSG_BUF_EMPTY;
    pstEmmFsmMsgBuf->ucLowPrioCnt       = NAS_EMM_MSG_BUF_EMPTY;
    for ( ulCont = 0; ulCont < NAS_EMM_BUF_MSG_MAX_NUM; ulCont++ )
    {
        pstEmmFsmMsgBuf->astHighPrioBufQue[ulCont].pBuffMsg = NAS_LMM_NULL_PTR;
        pstEmmFsmMsgBuf->astMidPrioBufQue[ulCont].pBuffMsg = NAS_LMM_NULL_PTR;
        pstEmmFsmMsgBuf->astLowPrioBufQue[ulCont].pBuffMsg = NAS_LMM_NULL_PTR;
    }

}


/*****************************************************************************
 Function Name   : NAS_EMMC_InitBufMsgQue
 Description     : 不释放内存，只是全局变量赋值
 Input           : None
 Output          : None
 Return          : VOS_UINT32

 History         :
    1.X00148705     2010-4-7  Draft Enact

*****************************************************************************/
VOS_VOID  NAS_EMMC_InitBufMsgQue( VOS_VOID )
{

}

/*****************************************************************************
*****************************************************************************/


#ifdef __cplusplus
    #if __cplusplus
        }
    #endif
#endif

/* end of 子系统+模块+文件名.c */
