/*
 * 
 * All rights reserved.
 *
 * This software is available to you under a choice of one of two
 * licenses. You may choose this file to be licensed under the terms
 * of the GNU General Public License (GPL) Version 2 or the 2-clause
 * BSD license listed below:
 *
 * Redistribution and use in source and binary forms, with or without
 * modification, are permitted provided that the following conditions
 * are met:
 * 1. Redistributions of source code must retain the above copyright
 *    notice, this list of conditions and the following disclaimer.
 * 2. Redistributions in binary form must reproduce the above copyright
 *    notice, this list of conditions and the following disclaimer in the
 *    documentation and/or other materials provided with the distribution.
 *
 * THIS SOFTWARE IS PROVIDED BY THE AUTHOR AND CONTRIBUTORS "AS IS" AND
 * ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE
 * IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE
 * ARE DISCLAIMED.  IN NO EVENT SHALL THE AUTHOR OR CONTRIBUTORS BE LIABLE
 * FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL
 * DAMAGES (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS
 * OR SERVICES; LOSS OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION)
 * HOWEVER CAUSED AND ON ANY THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT
 * LIABILITY, OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY
 * OUT OF THE USE OF THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF
 * SUCH DAMAGE.
 *
 */

/******************************************************************************
   头文件包含
******************************************************************************/
#include "PPP/Inc/hdlc_software.h"

#ifdef __cplusplus
    #if __cplusplus
        extern "C" {
    #endif
#endif

#if(FEATURE_ON == FEATURE_PPP)

/*****************************************************************************
   1 协议栈打印打点方式下的.C文件宏定义
*****************************************************************************/
/*lint -e767 */
#define    THIS_FILE_ID        PS_FILE_ID_HDLC_SOFTWARE_C
/*lint +e767 */

/******************************************************************************
   2 外部函数变量声明
******************************************************************************/
extern struct ppp_mbuf *
async_TtfMemLayerPush(struct link *l, VOS_UINT8 *pHdr, VOS_UINT16 usHdrLen, PPP_ZC_STRU *bp,
                VOS_INT32 pri, VOS_UINT16 *proto);

extern PPP_ZC_STRU *
hdlc_LayerPull(/*struct bundle *b, */struct link *l, PPP_ZC_STRU *bp,
               VOS_UINT16 *proto);

extern PPP_ZC_STRU *
async_Decode(struct async *async, VOS_CHAR c);

extern PPP_ZC_STRU *
acf_LayerPull(/*struct bundle *b, */struct link *l, PPP_ZC_STRU *bp, VOS_UINT16 *proto);

extern PPP_ZC_STRU *proto_LayerPull(/*struct bundle *b, */struct link *l, PPP_ZC_STRU *pstMem,
                VOS_UINT16 *pusProto);

extern struct ppp_mbuf *
proto_LayerPush(/*struct bundle *b, */struct link *l, struct ppp_mbuf *bp,
                VOS_INT32 pri, VOS_UINT16 *proto);
extern struct ppp_mbuf *
acf_LayerPush(/*struct bundle *b, */struct link *l, struct ppp_mbuf *bp,
              VOS_INT32 pri, VOS_UINT16 *proto);

extern struct ppp_mbuf *
async_LayerPush(/*struct bundle *bundle, */struct link *l, struct ppp_mbuf *bp,
                VOS_INT32 pri, VOS_UINT16 *proto);

extern VOS_UINT32 PPP_SendPushedData(VOS_UINT16 usPppId, VOS_UINT8 *pucDataBuf, VOS_UINT16 usLen);


/*****************************************************************************
   3 私有定义
*****************************************************************************/
typedef struct
{
    VOS_UINT32                  ulUplinkIpDataProcCnt;             /* 上行IP数据包处理个数 */
    VOS_UINT32                  ulUplinkPppDataProcCnt;            /* 上行简单PPP帧处理个数 */

    VOS_UINT32                  ulDownlinkIpDataProcCnt;           /* 下行IP数据包处理个数 */
    VOS_UINT32                  ulDownlinkPppDataProcCnt;          /* 下行简单PPP帧处理个数 */

    VOS_UINT32                  ulMaxCntOnce;                      /* PPP一次最多处理的结点个数 */
} PPP_HDLC_SOFT_DATA_PROC_STAT_ST;


/*****************************************************************************
   4 全局变量定义
*****************************************************************************/
PPP_HDLC_SOFT_DATA_PROC_STAT_ST g_PppHdlcSoftStat = {0};


/******************************************************************************
   5 函数实现
******************************************************************************/
VOS_VOID PPP_HDLC_SOFT_MntnShowStatInfo(VOS_VOID)
{
    vos_printf("\n================HDLC Software STAT INFO Begin==========================\n");

    vos_printf("处理上行IP类型数据个数    = %d\n", g_PppHdlcSoftStat.ulUplinkIpDataProcCnt);
    vos_printf("处理上行PPP类型数据个数   = %d\n", g_PppHdlcSoftStat.ulUplinkPppDataProcCnt);
    vos_printf("处理下行IP类型数据个数    = %d\n", g_PppHdlcSoftStat.ulDownlinkIpDataProcCnt);
    vos_printf("处理下行PPP类型数据个数   = %d\n", g_PppHdlcSoftStat.ulDownlinkPppDataProcCnt);
    vos_printf("单次处理数据最大个数   = %d\n", g_PppHdlcSoftStat.ulMaxCntOnce);

    vos_printf("================HDLC Software STAT INFO End==========================\n");
}

/*lint -e574*/
void link_PushTtfMemPacket(struct link *l, PPP_ZC_STRU *bp, VOS_INT32 pri, VOS_UINT16 proto)
{
    VOS_UINT8   aucPppDataHdr[4];
    VOS_UINT16  usHdrLen=0;


    /*
    * When we ``push'' a packet into the link, it gets processed by the
    * ``push'' function in each layer starting at the top.
    * We never expect the result of a ``push'' to be more than one
    * packet (as we do with ``pull''s).
    */

    if( (pri < 0) || (pri >= LINK_QUEUES(l)) )
    {
        pri = 0;
    }

    /*
    bp = proto_LayerPush(l, bp, pri, &proto);
    bp = acf_LayerPush(l, bp, pri, &proto);
    bp = async_LayerPush(l, bp, pri, &proto);
    */


    /* Address and Control */
    if ( (proto == PROTO_LCP) || (l->lcp.his_acfcomp == 0) )
    {
        aucPppDataHdr[usHdrLen++] = HDLC_ADDR;
        aucPppDataHdr[usHdrLen++] = HDLC_UI;
    }

    /* 如果头部协议压缩支持压缩 */
    /*如果可以压缩协议字段，只需一个字节*/
    if ( (l->lcp.his_protocomp) && (((VOS_UINT8)(proto >> 8)) == 0))
    {
        aucPppDataHdr[usHdrLen++]   = proto & 0xff;
    }
    else
    {
        aucPppDataHdr[usHdrLen++]   = proto >> 8;
        aucPppDataHdr[usHdrLen++]   = proto & 0xff;
    }

    async_TtfMemLayerPush(l, aucPppDataHdr, usHdrLen, bp, pri, &proto);

} /* link_PushTtfMemPacket */
/*lint +e574*/

void link_PullMemPacket(struct link *l, PPP_ZC_STRU *pstMem)
{
    PPP_ZC_STRU      *pLastMem;
    PPP_ZC_STRU      *pTmpMem;
    VOS_UINT32        ulCnt;
    VOS_UINT16        usProto;
    VOS_UINT16        usLen;
    VOS_UINT8        *pucData;


    /*
    while (VOS_NULL_PTR != pstMem)
    {
    */
        usLen = PPP_ZC_GET_DATA_LEN(pstMem);

        for (ulCnt = 0; ulCnt < usLen; ulCnt++)
        {
            pucData     = PPP_ZC_GET_DATA_PTR(pstMem);
            pLastMem    = async_Decode(&l->async, (VOS_CHAR)(pucData[ulCnt]));

            /* 找到一个完整的PPP帧，进行HDLC->ACF->Protocol各层处理，然后分发 */
            if (VOS_NULL_PTR != pLastMem)
            {
                pLastMem    = hdlc_LayerPull(l, pLastMem, &usProto);

                if (VOS_NULL_PTR != pLastMem)
                {
                    pLastMem    = acf_LayerPull(l, pLastMem, &usProto);
                }

                if (VOS_NULL_PTR != pLastMem)
                {
                    pLastMem    = proto_LayerPull(l, pLastMem, &usProto);
                }

                if (VOS_NULL_PTR != pLastMem)
                {
                    /* 零拷贝结构数据指针做过偏移，向上行方向需要发送时需要重新申请，
                       并且预留MAC头，保持与NDIS一致 */

                    pTmpMem = pLastMem;

                    pLastMem = PPP_MemCopyAlloc(PPP_ZC_GET_DATA_PTR(pTmpMem),
                                            PPP_ZC_GET_DATA_LEN(pTmpMem),
                                            PPP_ZC_UL_RESERVE_LEN);

                    PPP_MemFree(pTmpMem);
                }

                if (VOS_NULL_PTR != pLastMem)
                {
                    PPP_HDLC_ProcIpModeUlData(/*b, */l, pLastMem, usProto);
                }
            }
        } /* for cnt */

        PPP_MemFree(pstMem);
    /*
    }
    */
}

#if (PPP_FEATURE == PPP_FEATURE_PPP)
/*****************************************************************************
 Prototype      : Ppp_FrameEncap
 Description    : 对于PPP类型的激活，对于从网侧发送来的简单的PPP报文，对其
                  进行封装然后发送到TE侧。

 Input          : ---
 Output         : ---返回空
 Return Value   : ---
 Calls          : ---
 Called By      : ---

 History        : ---
  1.Date        : 2006-5-25
    Author      : ---
    Modification: Created function
*****************************************************************************/
VOS_UINT32 Ppp_FrameEncap(PPP_ID PppId, PPP_ZC_STRU *pstData)
{
    VOS_UINT16          proto;
    VOS_UINT8           aucProto[2];
    VOS_UINT32          ulRtn;


    /* 先获取协议字段，1个或2个字节 */
    ulRtn   = PPP_MemCutHeadData(&pstData, &aucProto[0], 1);

    if (PS_FAIL == ulRtn)
    {
        PPP_MemFree(pstData);
        return VOS_ERR;
    }

    if ( 0x01 == (aucProto[0] & 0x01) )     /* 第一个字节LSB为1，说明协议字段经过了压缩，只有一个字节 */
    {
        proto = ((VOS_UINT16)(aucProto[0]));
        PPP_LINK(PppId)->lcp.his_protocomp  = 1;
    }
    else
    {
        ulRtn   = PPP_MemCutHeadData(&pstData, &aucProto[1], 1);

        if (PS_FAIL == ulRtn)
        {
            PPP_MemFree(pstData);
            return VOS_ERR;
        }

        proto = ( (((VOS_UINT16)(aucProto[0]))<<8) | (aucProto[1]) );
        PPP_LINK(PppId)->lcp.his_protocomp  = 0;
    }

    if (VOS_NULL_PTR == pstData)
    {
        return VOS_ERR;
    }


    /* 剔除协议字段后，报文就和普通的IP报文类似了，可以统一处理 */
    link_PushTtfMemPacket(PPP_LINK(PppId), pstData, 0, proto);

    return VOS_OK;
}



/*****************************************************************************
 Prototype      : Ppp_FrameDecap
 Description    : 对于PPP类型的激活，对于从TE发送来的复杂的PPP报文，对
                  其进行解封装然后发送到网侧。

 Input          : ---
 Output         :
 Return Value   : VOS_NULL                       //失败
                  ppp_mbuf *bp                   //成功，返回数据指针
 Calls          : ---
 Called By      : ---

 History        : ---
  1.Date        : 2006-5-25
    Author      : ---
    Modification: Created function
*****************************************************************************/
VOS_UINT32 Ppp_FrameDecap(PPP_ID PppId, PPP_ZC_STRU *pstMem)
{
    PPP_ZC_STRU      *pLastMem;
    VOS_UINT16        usCnt;
    VOS_UINT16        usProto;
    struct link      *l;
    VOS_UINT16        usLen;


    l     = PPP_LINK(PppId);
    usLen = PPP_ZC_GET_DATA_LEN(pstMem);

    /*
    while (VOS_NULL_PTR != pstMem)
    {
    */
        for (usCnt = 0; usCnt < usLen; usCnt++)
        {
            pLastMem = async_Decode(&l->async, (VOS_CHAR)(PPP_ZC_GET_DATA_PTR(pstMem)[usCnt]));

            if (pLastMem != VOS_NULL_PTR)
            {
                /* 找到一个完整的PPP帧，进行HDLC->ACF各层处理，
                因为PPP类型PDP激活不能去除协议头，所以不能进行Protocol协议层处理 */
                pLastMem    = hdlc_LayerPull(l, pLastMem, &usProto);

                if (VOS_NULL_PTR != pLastMem)
                {
                    pLastMem    = acf_LayerPull(l, pLastMem, &usProto);
                }

                if (VOS_NULL_PTR != pLastMem)
                {
                    PPP_HDLC_ProcPppModeUlData(PppId, pLastMem);
                }
            }
        } /* for cnt */

        PPP_MemFree(pstMem);
    /*
    }
    */

    return VOS_OK;
}

#else
void
link_PullPacket(struct link *l, VOS_CHAR *buf, VOS_UINT32 len)
{
  struct ppp_mbuf *bp, *lbp[LAYER_MAX];
  VOS_UINT16 lproto[LAYER_MAX], proto;
  VOS_INT32 layer;
  PPP_ZC_STRU   *pstMem;


  if (!l)
  {
    PPP_MNTN_LOG(PS_PID_APP_PPP, 0, PS_PRINT_WARNING, "link_PullPacket:Can't Pull an async packet from a logical link\r\n");
    return;
  }

  PS_MEM_SET(lbp, '\0', sizeof lbp);

    lbp[0] = ppp_m_get((VOS_INT32)len);

  if(lbp[0] == VOS_NULL)
  {
    return;
  }

  PS_MEM_CPY(PPP_MBUF_CTOP(lbp[0]), buf, len);


  lproto[0] = 0;
  layer = 0;

  while (layer || lbp[layer]) {
    if (lbp[layer] == VOS_NULL_PTR) {
      layer--;
      continue;
    }
    bp = lbp[layer];
    lbp[layer] = bp->m_nextpkt;
    bp->m_nextpkt = VOS_NULL_PTR;
    proto = lproto[layer];

    if (l->layer[layer]->pull != VOS_NULL_PTR)
      bp = (*l->layer[layer]->pull)(/*b, */l, bp, &proto);

    if (layer == (l->nlayers - 1)) {
      /* We've just done the top layer, despatch the packet(s) */
      if (bp) {
        pstMem  = ppp_m_alloc_ttfmem_from_mbuf(bp);
        ppp_m_freem(bp);

        if (VOS_NULL_PTR != pstMem)
        {
          PPP_HDLC_ProcIpModeUlData(/*b, */l, pstMem, proto);
        }
      }
    } else {
      lbp[++layer] = bp;
      lproto[layer] = proto;
    }
  }
}


/*****************************************************************************
 Prototype      : PPP_RcvPPPoEDataIndIPType
 Description    : 对于IP类型的激活，对于从GGSN发送来的IP报文，对
                  其进行封装后发送到PPPoE继续封装。

 Input          : ---
 Output         : ---
 Return Value   : ---
 Calls          : ---
 Called By      : ---

 History        : ---
  1.Date        : 2006-5-25
    Author      : ---
    Modification: Created function
*****************************************************************************/
VOS_UINT32 PPP_RcvPPPoEDataIndIPType(PPP_ID PppId, VOS_UINT8 * pucData, VOS_UINT16 usLen)
{
    struct ppp_mbuf *bp;

    bp = ppp_m_get(usLen + PPP_RECIEVE_RESERVE_FOR_HEAD + PPP_RECIEVE_RESERVE_FOR_TAIL);

    if(bp == VOS_NULL)
    {
        PPP_MNTN_LOG(PS_PID_APP_PPP, 0, PS_PRINT_WARNING, "no mbuf\r\n");
        return VOS_ERR;
    }
    /*预留头部*/
    bp->m_offset = PPP_RECIEVE_RESERVE_FOR_HEAD;

    /*头部与尾部都留出来了*/
    bp->m_len = usLen;

    /*拷贝数据*/
    PS_MEM_CPY(PPP_MBUF_CTOP(bp), pucData, usLen);
    link_PushPacket(PPP_LINK(PppId),bp,0,PROTO_IP);
    return VOS_OK;


}

/*****************************************************************************
 Prototype      : PPP_RcvPPPoEDataReqIPType
 Description    : 对于IP类型的激活，对于从PPPoE发来的从TE来的简单的PPP帧，进行
                  处理 。

 Input          : ---
 Output         : ---
 Return Value   : ---
 Calls          : ---
 Called By      : ---

 History        : ---
  1.Date        : 2006-5-25
    Author      : ---
    Modification: Created function
*****************************************************************************/
VOS_UINT32 PPP_RcvPPPoEDataReqIPType(PPP_ID PppId, VOS_UINT8 * pucData, VOS_UINT16 usLen)
{
    link_PullPacket(PPP_LINK(PppId),(VOS_CHAR *)pucData,usLen);
    return VOS_OK;

}
#endif

PPP_HDLC_RESULT_TYPE_ENUM_UINT32 PPP_HDLC_SOFT_ProcData
(
    PPP_ID usPppId,
    struct link *pstLink,
    PPP_ZC_QUEUE_STRU *pstDataQ
)
{
    PPP_ZC_STRU                        *pstMem;
    VOS_UINT32                          ulDealCnt = 0;
    PPP_DATA_TYPE_ENUM_UINT8            ucDataType;

    for (;;)
    {
        pstMem  = (PPP_ZC_STRU *)PPP_ZC_DEQUEUE_HEAD(pstDataQ);

        /* 队列为空的时候返回空指针 */
        if ( VOS_NULL_PTR == pstMem )
        {
            return PPP_HDLC_RESULT_COMM_FINISH;
        }

        /*处理该结点(结点的释放动作已经在各处理函数内部完成，无需再释放结点)*/
        ucDataType = (PPP_ZC_GET_DATA_APP(pstMem) & 0x00FF);

        switch ( ucDataType )
        {
            case PPP_PULL_PACKET_TYPE:
                g_PppHdlcSoftStat.ulUplinkIpDataProcCnt++;

                link_PullMemPacket(pstLink, pstMem);
                break;
            case PPP_PUSH_PACKET_TYPE:
                g_PppHdlcSoftStat.ulDownlinkIpDataProcCnt++;

                link_PushTtfMemPacket(pstLink, pstMem, 0, PROTO_IP);
                break;
            case PPP_PULL_RAW_DATA_TYPE:
                g_PppHdlcSoftStat.ulUplinkPppDataProcCnt++;

                Ppp_FrameDecap(usPppId, pstMem);
                break;
            case PPP_PUSH_RAW_DATA_TYPE:
                g_PppHdlcSoftStat.ulDownlinkPppDataProcCnt++;

                Ppp_FrameEncap(usPppId, pstMem);
                break;
            default:
                PPP_MemFree(pstMem);
                PPP_MNTN_LOG1(PS_PID_APP_PPP, 0, LOG_LEVEL_WARNING,
                              "PPP_ProcDataNotify, WARNING, ucDataType %d is Abnormal!", ucDataType);
                break;
        }

        /*统计*/
        ulDealCnt++;

        if ( ulDealCnt > g_PppHdlcSoftStat.ulMaxCntOnce )
        {
            g_PppHdlcSoftStat.ulMaxCntOnce = ulDealCnt;
        }

        /*如果循环处理的结点个数超出了队列一次允许处理最大结点数，
          则退出循环并发送PPP_DATA_PROC_NOTIFY消息*/
        if ( ulDealCnt >= PPP_ONCE_DEAL_MAX_CNT )
        {
            return PPP_HDLC_RESULT_COMM_CONTINUE;
        }
    } /* for (;;) */
}

/*****************************************************************************
 函 数 名  : PPP_HDLC_SOFT_ProcProtocolPacket
 功能描述  : 软件封装PPP协议栈输出的协议包
 输入参数  : pstLink    -   PPP链路信息
             pstMbuf    -   PPP协议栈输出的协议包
             ulPri      -   优先级
             usProto    -   数据包对应的协议
 输出参数  : 无
 返 回 值  : 无
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2012年4月10日
    作    者   : l00164359
    修改内容   : 新生成函数

*****************************************************************************/
VOS_VOID PPP_HDLC_SOFT_ProcProtocolPacket
(
    struct link     *l,
    struct ppp_mbuf *bp,
    VOS_INT32       pri,
    VOS_UINT16      proto
)
{
    /*
    * When we ``push'' a packet into the link, it gets processed by the
    * ``push'' function in each layer starting at the top.
    * We never expect the result of a ``push'' to be more than one
    * packet (as we do with ``pull''s).
    */
    /*lint  -e574 -e960*/
    if(pri < 0 || pri >= LINK_QUEUES(l))
        pri = 0;
    /*lint  +e574 +e960*/

    #if 0
    for (layer = l->nlayers; layer && bp; layer--)
        if (l->layer[layer - 1]->push != VOS_NULL_PTR)
            bp = (*l->layer[layer - 1]->push)(/*b, */l, bp, pri, &proto);
    #else
    bp = proto_LayerPush(l, bp, pri, &proto);
    bp = acf_LayerPush(l, bp, pri, &proto);
    (VOS_VOID)async_LayerPush(l, bp, pri, &proto);
    #endif


    return;
}
#endif

#ifdef __cplusplus
    #if __cplusplus
        }
    #endif
#endif


