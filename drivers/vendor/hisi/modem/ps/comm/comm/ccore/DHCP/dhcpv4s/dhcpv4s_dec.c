
#include "dhcp_inc.h"
#include "dhcpc_def.h"
#include "dhcpv4s_def.h"
#include "dhcpv4s_type.h"
#include "dhcpv4s_var.h"
#include "dhcpv4s_fun.h"
#include "dhcpv4s_comp.h"
#include "dhcpv4s_dbgcmd.h"


/*****************************************************************************
     协议栈打印打点方式下的.C文件宏定义
*****************************************************************************/
/*lint -e767*/
#define    THIS_FILE_ID          PS_FILE_ID_DHCPV4S_DEC_C
/*lint +e767*/

 

ULONG DHCPS_DEC_ParseOption (DHCPS_ANALYZEDPACKET_S *pstAnalyzedPacket, UCHAR *pucBuffer,USHORT usLen)
{
    UCHAR    *pucPoint = NULL;
    USHORT    usLenCounter = 0;
    UCHAR  ucTempLen = 0;
    UCHAR *pucTemp = NULL;

    if ((NULL == pucBuffer) || (NULL == pstAnalyzedPacket))
    {
        DHCPS_DebugPrint(PTM_LOG_DEBUG, "\r\n DHCPS_DEC_ParseOption: input err!");
        /*增加异常计数，下同*/
        DHCPS_InternalBranchCounter(DHCPS_INTERNAL_BRANCH_175);
        return VOS_ERR;
    }
    usLenCounter = 0;
    pucPoint = pucBuffer;

    /*遍历所有的缓冲区的空间 */
    while(usLenCounter < usLen)
    {
        if ( DHCP_OPTION_END == * pucPoint )
        {
            /* 发现结束字，则返回*/
            return VOS_OK;
        }
        else if ( DHCP_OPTION_PAD == * pucPoint )
        {
            /*如果是填充字符，则跳过 */
            pucPoint ++;
            usLenCounter++;
            continue;
        }

        switch ( * pucPoint )
        {
            /*根据 OPTION 的类别分别进行处理 */
            case DHCP_OPTION_MESSAGE_TYPE:
                pstAnalyzedPacket->ucPacketType = *(pucPoint+2) ;
                /* 与 OPTIONS 相关的长度在类别后第二字节 */
                break;
            case DHCP_OPTION_REQUESTED_IP:
                VOS_MemCpy(&(pstAnalyzedPacket->ulRequestedAddr), (pucPoint+2), sizeof(ULONG));
                pstAnalyzedPacket->ulRequestedAddr = pstAnalyzedPacket->ulRequestedAddr;
                break;
            case DHCP_OPTION_OVERLOAD:
                pstAnalyzedPacket->ucOptionOverload =  *(pucPoint+2);
                break;
            case DHCP_OPTION_MAXMESSAGE_SIZE:
                VOS_MemCpy(&(pstAnalyzedPacket->usMaxDhcpSize), (pucPoint+2), sizeof(USHORT));
                pstAnalyzedPacket->usMaxDhcpSize = (USHORT) VOS_NTOHS(pstAnalyzedPacket->usMaxDhcpSize);
                if(pstAnalyzedPacket->usMaxDhcpSize < DHCP_MIN_LEN)
                {
                    pstAnalyzedPacket->usMaxDhcpSize = DHCP_MIN_LEN;
                }
                break;
            case DHCP_OPTION_SERVERID:
                VOS_MemCpy(&(pstAnalyzedPacket->ulServerId), (pucPoint+2), sizeof(ULONG));
                pstAnalyzedPacket->ulServerId = pstAnalyzedPacket->ulServerId;
                break;
            case DHCP_OPTION_PARAMETER_REQUEST_LIST:
                VOS_MemSet(pstAnalyzedPacket->aucParaReqList, 0, sizeof(UCHAR)*256);/*初始化数组的初值*/
                ucTempLen=*(pucPoint+1);/*取出OPTION55里面的内容的个数*/
                pucTemp = (pucPoint+2);
                VOS_MemCpy(pstAnalyzedPacket->aucParaReqList, pucTemp, ucTempLen);
                pstAnalyzedPacket->ucParaReqLen = ucTempLen;
                break;
            case DHCP_OPTION_RAPID_COMMIT:
                pstAnalyzedPacket->ucRapidCommitFlag = 1;
                break;
            default:
                /*其他的Option都先不考虑了*/
                break;
        }
        /* 与 OPTIONS 相关的长度在类别后第一字节 */
        usLenCounter = usLenCounter + 2 + *(pucPoint+1);
        pucPoint  = pucPoint + 2 + *(pucPoint+1);
    }
    DHCPS_InternalBranchCounter(DHCPS_INTERNAL_BRANCH_176);
    return VOS_ERR;
}




ULONG DHCPS_DEC_Decode (UCHAR *pucUdpBuf, USHORT usUdpBufLen ,DHCPS_ANALYZEDPACKET_S *pstAnalyzedPacket)
{
    DHCPS_PACKET_S stDhcpPacket;

    if ((NULL == pucUdpBuf) || (NULL == pstAnalyzedPacket))
    {
        DHCPS_DebugPrint(PTM_LOG_DEBUG, "\r\n DHCPS_DEC_Decode: pstMbuf NULL!");
        DHCPS_InternalBranchCounter(DHCPS_INTERNAL_BRANCH_177);
        return VOS_ERR;
    }

    if(usUdpBufLen < (DHCPS_HEAD_LEN + 5))
    {
        DHCPS_DebugPrint(PTM_LOG_DEBUG, "\r\n DHCPS_DEC_Decode: usUdpBufLen %u",
                          usUdpBufLen);

        DHCPS_InternalBranchCounter(DHCPS_INTERNAL_BRANCH_178);
        /* Option部分最小也要包括一个COOKIE和结束标志，即5字节
        所以输入参数小于 DHCP_HEAD_LEN + 5 的情况是异常的*/
        return VOS_ERR;
    }

    PGP_MemZero(&stDhcpPacket,  sizeof(DHCPS_PACKET_S));
    stDhcpPacket.pstHead = (DHCPS_PACKET_HEAD_S *) pucUdpBuf;
    stDhcpPacket.pucOptions = pucUdpBuf + DHCPS_HEAD_LEN;

    /* op 字段是否也要检查???*/

    /* 检查DHCP报文的option部分的前四个字节是否为 magic cookie */
    if (VOS_OK != VOS_MemCmp (stDhcpPacket.pucOptions, DHCPS_OPTIONS_COOKIE, 4))
    {
        DHCPS_InternalBranchCounter(DHCPS_INTERNAL_BRANCH_180);
        /*比较结果，二者不同。说明非 Magic Cookie 字符，该数据包出错无效*/
        return VOS_ERR;
    }

    /* 待填写的pstAnalyzedPacket的空间先清零*/
    (VOID)VOS_MemSet((VOID *)pstAnalyzedPacket, 0, sizeof(DHCPS_ANALYZEDPACKET_S));

    /* pstAnalyzedPacket中相关参数的赋值 */

    pstAnalyzedPacket->usPacketLength   = usUdpBufLen;
    /*请求和应答匹配即可,不考虑一个用户所有消息是否都用同一个Xid*/
    pstAnalyzedPacket->ulXid = VOS_NTOHL(stDhcpPacket.pstHead->ulXid);
    pstAnalyzedPacket->usFlags = VOS_NTOHS(stDhcpPacket.pstHead->usFlags);
    pstAnalyzedPacket->ulCiaddr = stDhcpPacket.pstHead->ulCiaddr;
    pstAnalyzedPacket->ulGiaddr = stDhcpPacket.pstHead->ulGiaddr;
    pstAnalyzedPacket->ulYiaddr = stDhcpPacket.pstHead->ulYiaddr;

    pstAnalyzedPacket->ucHtype = stDhcpPacket.pstHead->ucHtype;
    (VOID)VOS_MemCpy(pstAnalyzedPacket->pucChaddr, stDhcpPacket.pstHead->pucChaddr, DHCPS_CHADDR_LEN);

    /*初始化最大dhcp数据包长度*/
    pstAnalyzedPacket->usMaxDhcpSize = DHCPS_OPTION_MAXLEN + DHCPS_HEAD_LEN;

    /* 分析option域(先不考虑Option字段的overload情况)*/
    if(VOS_OK!=DHCPS_DEC_ParseOption (pstAnalyzedPacket, stDhcpPacket.pucOptions+4 , (USHORT)(pstAnalyzedPacket->usPacketLength-DHCPS_HEAD_LEN- 4)))
    {
        DHCPS_InternalBranchCounter(DHCPS_INTERNAL_BRANCH_181);
        /*分析 Options 有错误，返回*/
        return VOS_ERR;
    }

    /*如果有option overload的选项，则继续分析overload字段部分的Option */
    if ( (DHCP_OPTION_PAD != *(stDhcpPacket.pstHead->pcFile))
        && (pstAnalyzedPacket->ucOptionOverload & DHCP_OVERLOAD_FILE_FLAG) )
    {
        if(VOS_OK!=DHCPS_DEC_ParseOption(pstAnalyzedPacket, (UCHAR *)stDhcpPacket.pstHead->pcFile, DHCPS_FILE_LEN))
        {
            DHCPS_InternalBranchCounter(DHCPS_INTERNAL_BRANCH_182);
            /*分析 Options 有错误，返回*/
            return VOS_ERR;
        }
    }
    if ( (DHCP_OPTION_PAD != *(stDhcpPacket.pstHead->pcSname))
        && (pstAnalyzedPacket->ucOptionOverload & DHCP_OVERLOAD_SNAME_FLAG) )
    {
        if(VOS_OK!=DHCPS_DEC_ParseOption(pstAnalyzedPacket, (UCHAR *)stDhcpPacket.pstHead->pcSname, DHCPS_SNAME_LEN))
        {
            DHCPS_InternalBranchCounter(DHCPS_INTERNAL_BRANCH_183);
            /*分析 Options 有错误，返回*/
            return VOS_ERR;
        }
    }

    DHCPS_DebugPrint(PTM_LOG_DEBUG, "\r\n DHCPS_DEC_Decode : OK");
    return VOS_OK;

}


USHORT DHCPS_IpCkSum(USHORT* pusIpMsg,ULONG ulWordNum)
{
    ULONG ulSum = 0;  /* 检验和 */
     USHORT usSum;

    if (pusIpMsg == NULL)
    {
        DHCPS_DebugPrint(PTM_LOG_DEBUG, "\r\n DHCPS_IpCkSum: input Error.");
        DHCPS_InternalBranchCounter(DHCPS_INTERNAL_BRANCH_144);
        return VOS_ERR;
    }

    while (ulWordNum > 0)
    {
        ulSum += *pusIpMsg++;
        ulWordNum --;
    }

    ulSum = (ulSum >> 16) + (ulSum & 0xffff);   /* 高16位与低16位相加 */
    ulSum += (ulSum >> 16);        /* 加进位位 */
    usSum = (USHORT)(~ulSum);

    return (usSum);
}

