
/*******************************************************************************
*
*
*                Copyright 2008, Huawei Technologies Co. Ltd.
*                            ALL RIGHTS RESERVED
*
*-------------------------------------------------------------------------------
*
*                              ipoa_def.h
*
*  Project Code: node
*   Module Name:   
*  Date Created: 2008-07-24
*        Author: wangbin (62223)
*   Description: 
*
*-------------------------------------------------------------------------------
*  Modification History
*  DATE         NAME                    DESCRIPTION
*  -----------------------------------------------------------------------------
*  2008-07-24   wangbin (62223)         Create
*
*******************************************************************************/
#ifndef _IPOA_DEF_H_
#define _IPOA_DEF_H_

#ifdef __cplusplus
extern "C"{
#endif /* __cplusplus */
#include"tcpip/ipoa/include/ipoa_api.h"
#define     IPOA_UP         1           /* 表示接口、协议、VC等状态UP */
#define     IPOA_DOWN       0           /* 表示接口、协议、VC等状态DOWN */
#define     IPOA_PAC_IN     1           /* 收到报文 */
#define     IPOA_PAC_OUT    2           /* 发送报文 */


#define IPOA_VC_VPI_MAX              255
#define IPOA_VC_VCI_MAX              2048
#define IPOA_DEFAULT_VPIVCI          0xFFFF    /* 默认vpi、vci值 */
#define IPOA_LEN_256                 256       /* 256字节,用于数组申请内存*/
#define IPOA_PVC_FLAG                1         /* PVC级调试开关 */
#define IPOA_NO_PVC_FLAG             0         /* 接口级调试开关 */
#define IPOA_BUFFER_MIN_LEN          1024      /* API中输入的内存最小长度*/

#define IPOA_HASH_SEED               1379
#define IPOA_MAX_QUE_LEN             150
#define IPOA_QUE_MAX_DEAL_NUMBER         200     /* 一次处理报文最大数 */

#define IPOA_MAX_PVC_NUM_ON_SUBIF    256
#define IPOA_MAX_PVC_NUM_PER_PORT    2048

#define IPOA_MAX_MAP_NUM_ON_PVC      32     /* 单个PVC上允许配置的MAP数量限制 */
#define IPOA_MAX_MAP_NUM_ON_SUBIF    1024    /* 单个子接口上允许配置的MAP数目限制 */
#define IPOA_MAX_MAP_NUM_ON_PORT     2048

#define  IPOA_DEFAULT_INARP_INTERVAL    1      /* 分钟 */


#define IPOA_INARP_CMD_START             0x01    
#define IPOA_INARP_CMD_STOP              0x02    
#define IPOA_INARP_CMD_INTERVAL_CHANGE   0x04    

#define IPOA_INARP_INITIAL               0x00
#define IPOA_INARP_REQUEST_SENT          0x01
#define IPOA_INARP_REPLY_RECEIVED        0x02
#define IPOA_INARP_REQUEST_REVEIVED      0x04
#define IPOA_INARP_REPLY_SENT            0x08
#define IPOA_INARP_START                 0x10

#define IPOA_INARP_TYPE_REQUEST           0x08    /* INARP OP CODE，兼做类型定义 */
#define IPOA_INARP_TYPE_REPLY             0x09    /* INARP OP CODE，兼做类型定义 */





#define IPOA_INARP_SEND_PAC_MAX_LEN          20     /* 带目标地址时20字节 */
#define IPOA_INARP_SEND_PAC_LEN_WITH_DST_IP  20     /* 带目标地址时20字节 */
#define IPOA_INARP_SEND_PAC_LEN_NO_DST_IP    16     /* 不带目标地址时16字节 */

#define IPOA_PKT_RESERVED_HEAD_LEN           48
#define IPOA_PKT_RESERVED_TAIL_LEN           48


#define IPOA_MAX_PACKET_HEADER_LEN       10      /* 最长的报文头有10个字节，用以保证报文连续性 */


#define IPOA_DROP_PAKET_OF_CB        1
#define IPOA_DROP_PAKET_OF_INTF      2
#define IPOA_DROP_PAKET_OF_PVC       3

/*******************************************************************************
IPOA队列Drop命令字定义
*******************************************************************************/
#define IPOA_QUE_DROP_PAC_OF_PVC         1
#define IPOA_QUE_DROP_PAC_OF_INTF        2
#define IPOA_QUE_DROP_PAC_OF_CB          3


#define IPOA_INARP_HARD_TYPE                 0x0013
#define IPOA_INARP_IP_PROT_TYPE              0x0800



#define IPOA_CFG_SETDBGFLAG(ulTargetFlag, ulFlagToSet, bSetFlag) ((ulTargetFlag) = (bSetFlag)?((ulTargetFlag) | (ulFlagToSet)):((ulTargetFlag) & ~(ulFlagToSet)))

#define IPOA_INTF_STATE(pstIpoaIntf) (((pstIpoaIntf->ucPhyState == IPOA_UP) \
                                        && (pstIpoaIntf->bShutdown == BOOL_FALSE)) \
                                        ? IPOA_UP : IPOA_DOWN \
                                      )


#define IPOA_PVC_STATE(pstPVC) (((pstPVC->ucPhyState == IPOA_UP) \
                                  && (pstPVC->bShutdown == BOOL_FALSE)) \
                                  ? IPOA_UP : IPOA_DOWN \
                                )


#define IPOA_DBG_PKT_HEAD_SNAPSHOT_LEN    64

typedef struct tagIPOA_DBG_PKT_INFO
{
    UCHAR           ucInOut;        /* 报文是收还是发 */
    UCHAR           ucPacType;      /* 报文类型 */
    UCHAR           ucEncType;      /* 报文封装类型 */
    UCHAR           ucInARPType;    /* INARP类型：请求ATM_INARP_TYPE_REQUEST, 应答ATM_INARP_TYPE_REPLY */
    USHORT          usLen;          /* 报文长度 */
    USHORT          usHeaderLen;    /* 报文头长度 */
    ULONG           ulSrcIP;   /* INARP报文源地址 */
    ULONG           ulDstIP;   /* INARP报文目的地址 */
    ULONG           ulErrCode;      /* 报文错误码 */
    UCHAR           ucHeader_a[IPOA_DBG_PKT_HEAD_SNAPSHOT_LEN];      /* 报文头字节序列 */
}IPOA_DBG_PKT_INFO_S;


#ifdef __cplusplus
}
#endif /* __cplusplus */

#endif /* _IPOA_DEF_H_ */


